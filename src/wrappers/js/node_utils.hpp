#pragma once

#include <optional>
#include <string>
#include <tuple>
#include <stdexcept>
#include <typeindex>
#include <utility>
#include <hstd/system/reflection.hpp>
#include <haxorg/sem/SemOrg.hpp>
#include <haxorg/sem/SemBaseApi.hpp>
#include <hstd/stdlib/Exception.hpp>
#include <utility>

#include <emscripten.h>
#include <emscripten/bind.h>


template <typename T>
struct emscripten::smart_ptr_trait<org::sem::SemId<T>> {
    using PointerType  = org::sem::SemId<T>;
    using element_type = T;

    static T* get(PointerType const& ptr) {
        return const_cast<T*>(ptr.get());
    }

    static sharing_policy get_sharing_policy() {
        return sharing_policy::BY_EMVAL;
    }

    static PointerType* share(T* p, EM_VAL v) {
        return new PointerType(
            std::shared_ptr<T>(p, val_deleter(val::take_ownership(v))));
    }

    static PointerType* construct_null() { return new PointerType(); }

    class val_deleter {
      public:
        val_deleter() = delete;
        explicit val_deleter(val v) : v(v) {}
        void operator()(void const*) {
            v();
            // eventually we'll need to support emptied out val
            v = val::undefined();
        }

      private:
        val v;
    };
};


namespace org::bind::js {

struct type_registration_guard {
    hstd::UnorderedSet<std::size_t> idx;
    template <typename T>
    bool can_add() {
        if (idx.contains(typeid(T).hash_code())) {
            return false;
        } else {
            idx.incl(typeid(T).hash_code());
            return true;
        }
    }
};

template <hstd::DescribedEnum E>
void bind_enum(std::string const& name) {
    auto&& e = emscripten::enum_<E>(name.c_str());
    for (hstd::EnumFieldDesc<E> const& d :
         hstd::describe_enumerators<E>()) {
        e = e.value(d.name.c_str(), d.value);
    }

    emscripten::function(
        ("format_" + name).c_str(),
        +[](E const& value) -> std::string { return hstd::fmt1(value); });
}

template <typename T>
void immerbox_bind(type_registration_guard& g, std::string const& name) {}

template <typename T>
void immerflex_vector_bind(
    type_registration_guard& g,
    std::string const&       name) {}

template <typename T>
void hstdVec_bind(type_registration_guard& g, std::string const& name) {
    using VT = hstd::Vec<T>;
    if (g.can_add<VT>()) {
        emscripten::class_<VT>(name.c_str())
            .function("size", &VT::size)
            .function(
                "push_back",
                static_cast<void (VT::*)(T const&)>(&VT::push_back))
            .function("pop_back", &VT::pop_back)
            .function("clear", &VT::clear)
            .function(
                "empty", static_cast<bool (VT::*)() const>(&VT::empty))
            .function("reserve", &VT::reserve)
            .function(
                "resize_with_value",
                static_cast<void (VT::*)(size_t, T const&)>(&VT::resize))
            .function(
                "at", static_cast<T const& (VT::*)(int) const>(&VT::at))
            .function(
                "front", static_cast<T const& (VT::*)() const>(&VT::front))
            .function(
                "back", static_cast<T const& (VT::*)() const>(&VT::back))
            .function(
                "toArray",
                +[](const hstd::Vec<T>& self) -> emscripten::val {
                    emscripten::val result = emscripten::val::global(
                                                 "Array")
                                                 .new_();
                    for (size_t i = 0; i < self.size(); ++i) {
                        result.call<void>("push", self[i]);
                    }
                    return result;
                });
    }
}

template <typename T>
void hstdIntSet_bind(type_registration_guard& g, std::string const& name) {
}

template <typename K, typename V>
void hstdUnorderedMap_bind(
    type_registration_guard& g,
    std::string const&       name) {}


template <typename T>
void stdoptional_bind(
    type_registration_guard& g,
    std::string const&       name) {
    if (g.can_add<std::optional<T>>()) {
        emscripten::class_<std::optional<T>>(name.c_str()) //
            .function(
                "value",
                +[](std::optional<T> const& opt) -> T const& {
                    return opt.value();
                })
            .function(
                "has_value", +[](std::optional<T> const& opt) -> bool {
                    return opt.has_value();
                });
    }
}


template <typename T>
void hstdOpt_bind(type_registration_guard& g, std::string const& name) {
    stdoptional_bind<T>(g, name);
}

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


} // namespace org::bind::js
