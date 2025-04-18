#include <optional>
#include <string>
#include <tuple>
#include <stdexcept>
#include <utility>
#include <cpptrace.hpp>
#include <hstd/system/reflection.hpp>
#include <haxorg/sem/SemOrg.hpp>
#include <haxorg/sem/SemBaseApi.hpp>
#include <hstd/stdlib/Exception.hpp>

namespace org::bind::js {


template <typename T>
struct org_to_js_type {};

template <typename T>
struct js_to_org_type {};

// Helper to check if a specialization exists
template <typename T, typename = void>
struct has_js_to_org_mapping : std::false_type {};

template <typename T>
struct has_js_to_org_mapping<
    T,
    std::void_t<typename js_to_org_type<T>::type>> : std::true_type {};

template <typename T, typename = void>
struct has_org_to_js_mapping : std::false_type {};

template <typename T>
struct has_org_to_js_mapping<
    T,
    std::void_t<typename org_to_js_type<T>::type>> : std::true_type {};

// Concept to check if a JS type has a mapping to an org type
template <typename JsType>
concept HasOrgMapping = has_js_to_org_mapping<JsType>::value;

// Concept to check if an org type has a mapping to a JS type
template <typename OrgType>
concept HasJsMapping = has_org_to_js_mapping<OrgType>::value;

// Concept to check if a bidirectional mapping exists
template <typename JsType, typename OrgType>
concept HasBidirectionalMapping //
    = HasOrgMapping<JsType>     //
   && HasJsMapping<OrgType>
   && std::is_same_v<typename js_to_org_type<JsType>::type, OrgType>
   && std::is_same_v<typename org_to_js_type<OrgType>::type, JsType>;

// Argument specification template
template <typename T>
struct CxxArgSpec {
    std::string      name;
    std::optional<T> defaultValue = std::nullopt;

    using value_type = T;
};

template <typename Tuple>
constexpr std::size_t count_required_args(const Tuple& args) {
    if constexpr (std::tuple_size_v<std::decay_t<Tuple>> == 0) {
        return 0;
    } else {
        std::size_t count = 0;
        boost::mp11::tuple_for_each(args, [&count](const auto& arg) {
            if (!arg.defaultValue.has_value()) { count++; }
        });
        return count;
    }
}

// CallableClass template for method pointers
template <typename T>
struct CallableClass {
    T* instance;

    explicit CallableClass(T* inst) : instance(inst) {}
};

// Specialization for standalone functions
template <>
struct CallableClass<std::monostate> {
    explicit CallableClass() {}
};

// Primary template for Callable
template <typename ClassType, typename ReturnType, typename... Args>
class Callable {
  private:
    // Static assertion to prevent instantiation of primary template
    static_assert(
        std::is_void<ClassType>::value,
        "This primary template should not be instantiated directly");
};

// Type trait to detect if a type is callable with given arguments
template <typename F, typename... Args>
using is_callable = std::is_invocable<F, Args...>;

// Type trait to get the return type of a callable
template <typename F, typename... Args>
using callable_result_t = std::invoke_result_t<F, Args...>;

// Specialization for standalone functions
template <typename ReturnType, typename... Args>
class Callable<CallableClass<std::monostate>, ReturnType, Args...> {
  public:
    using FunctionType  = ReturnType (*)(Args...);
    using ArgsTuple     = std::tuple<CxxArgSpec<std::decay_t<Args>>...>;
    using ArgsBaseTypes = std::tuple<Args...>;

    Callable(FunctionType func, ArgsTuple args)
        : function_(func), args_(std::move(args)), functor_(nullptr) {}

    // Constructor for functors/lambdas
    template <
        typename Functor,
        typename = std::enable_if_t<
            !std::is_same_v<std::decay_t<Functor>, Callable>
            && is_callable<Functor, Args...>::value
            && std::is_same_v<
                callable_result_t<Functor, Args...>,
                ReturnType>>>
    Callable(Functor&& functor, ArgsTuple args)
        : function_(nullptr)
        , args_(std::move(args))
        , functor_(std::make_shared<FunctorWrapper<std::decay_t<Functor>>>(
              std::forward<Functor>(functor))) {}

    // Constructor for type constructors
    template <
        typename ConstructedType,
        typename = std::enable_if_t<
            std::is_constructible_v<ConstructedType, Args...>
            && std::is_same_v<ReturnType, ConstructedType>>>
    static Callable ForConstructor(ArgsTuple args) {
        auto constructorFunc = [](Args... args) -> ConstructedType {
            return ConstructedType(std::forward<Args>(args)...);
        };
        return Callable(constructorFunc, std::move(args));
    }

    template <typename... CallArgs>
    ReturnType operator()(CallArgs&&... callArgs) const {
        if (function_) {
            return function_(std::forward<CallArgs>(callArgs)...);
        } else if (functor_) {
            return functor_->invoke(std::forward<CallArgs>(callArgs)...);
        } else {
            throw std::runtime_error(
                "Callable has no valid function or functor");
        }
    }

    const ArgsTuple& args() const { return args_; }
    FunctionType     function() const { return function_; }
    bool             isFunctor() const { return functor_ != nullptr; }

    int getRequiredArgsCount() const {
        return count_required_args(args());
    }

  private:
    // Base class for type-erased functor
    struct FunctorBase {
        virtual ~FunctorBase()                        = default;
        virtual ReturnType invoke(Args... args) const = 0;
    };

    // Type-specific functor wrapper
    template <typename Functor>
    struct FunctorWrapper : FunctorBase {
        Functor functor;

        explicit FunctorWrapper(Functor&& f)
            : functor(std::forward<Functor>(f)) {}

        ReturnType invoke(Args... args) const override {
            return functor(std::forward<Args>(args)...);
        }
    };

    FunctionType                       function_;
    ArgsTuple                          args_;
    std::shared_ptr<const FunctorBase> functor_;
};


// Specialization for method pointers
template <typename ClassType, typename ReturnType, typename... Args>
class Callable<CallableClass<ClassType>, ReturnType, Args...> {
  public:
    using MethodType    = ReturnType (ClassType::*)(Args...);
    using ArgsTuple     = std::tuple<CxxArgSpec<std::decay_t<Args>>...>;
    using ArgsBaseTypes = std::tuple<Args...>;

    Callable(MethodType method, ArgsTuple args)
        : method_(method), args_(std::move(args)) {}

    template <typename... CallArgs>
    ReturnType operator()(ClassType* instance, CallArgs&&... callArgs)
        const {
        return invoke(
            instance,
            std::index_sequence_for<Args...>{},
            std::forward<CallArgs>(callArgs)...);
    }

    const ArgsTuple& args() const { return args_; }
    MethodType       method() const { return method_; }

    int getRequiredArgsCount() const {
        return count_required_args(args());
    }


  private:
    MethodType method_;
    ArgsTuple  args_;

    template <size_t... Indices, typename... CallArgs>
    ReturnType invoke(
        ClassType* instance,
        std::index_sequence<Indices...>,
        CallArgs&&... callArgs) const {
        return (instance->*method_)(std::forward<CallArgs>(callArgs)...);
    }
};

// Specialization for const method pointers
template <typename ClassType, typename ReturnType, typename... Args>
class Callable<CallableClass<const ClassType>, ReturnType, Args...> {
  public:
    using MethodType    = ReturnType (ClassType::*)(Args...) const;
    using ArgsTuple     = std::tuple<CxxArgSpec<std::decay_t<Args>>...>;
    using ArgsBaseTypes = std::tuple<Args...>;

    Callable(MethodType method, ArgsTuple args)
        : method_(method), args_(std::move(args)) {}

    template <typename... CallArgs>
    ReturnType operator()(
        const ClassType* instance,
        CallArgs&&... callArgs) const {
        return invoke(
            instance,
            std::index_sequence_for<Args...>{},
            std::forward<CallArgs>(callArgs)...);
    }

    const ArgsTuple& args() const { return args_; }
    MethodType       method() const { return method_; }

    int getRequiredArgsCount() const {
        return count_required_args(args());
    }

  private:
    MethodType method_;
    ArgsTuple  args_;

    template <size_t... Indices, typename... CallArgs>
    ReturnType invoke(
        const ClassType* instance,
        std::index_sequence<Indices...>,
        CallArgs&&... callArgs) const {
        return (instance->*method_)(std::forward<CallArgs>(callArgs)...);
    }
};

// Factory functions for creating Callable objects

// For standalone functions
template <typename ReturnType, typename... Args>
auto makeCallable(
    ReturnType (*func)(Args...),
    std::tuple<CxxArgSpec<std::decay_t<Args>>...> args) {
    return Callable<CallableClass<std::monostate>, ReturnType, Args...>(
        func, std::move(args));
}

// For non-const methods
template <typename ClassType, typename ReturnType, typename... Args>
auto makeCallable(
    ReturnType (ClassType::*method)(Args...),
    std::tuple<CxxArgSpec<std::decay_t<Args>>...> args) {
    return Callable<CallableClass<ClassType>, ReturnType, Args...>(
        method, std::move(args));
}

// For const methods
template <typename ClassType, typename ReturnType, typename... Args>
auto makeCallable(
    ReturnType (ClassType::*method)(Args...) const,
    std::tuple<CxxArgSpec<std::decay_t<Args>>...> args) {
    return Callable<CallableClass<const ClassType>, ReturnType, Args...>(
        method, std::move(args));
}

// For functors and lambdas
template <
    typename Functor,
    typename... Args,
    typename ReturnType = callable_result_t<Functor, Args...>,
    typename = std::enable_if_t<is_callable<Functor, Args...>::value>>
auto makeCallable(
    Functor&&                                     functor,
    std::tuple<CxxArgSpec<std::decay_t<Args>>...> args) {
    return Callable<CallableClass<std::monostate>, ReturnType, Args...>(
        std::forward<Functor>(functor), std::move(args));
}

// For constructors
template <typename ConstructedType, typename... Args>
auto makeConstructorCallable(
    std::tuple<CxxArgSpec<std::decay_t<Args>>...> args) {
    return Callable<
        CallableClass<std::monostate>,
        ConstructedType,
        Args...>::
        template ForConstructor<ConstructedType>(std::move(args));
}

// Converter template for JS <-> C++ type conversions
template <typename T, typename Enable = void>
struct JsConverter {};

} // namespace org::bind::js
