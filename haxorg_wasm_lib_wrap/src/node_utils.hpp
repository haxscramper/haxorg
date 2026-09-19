#pragma once

#include <cstddef>
#include <haxorg/api/SemBaseApi.hpp>
#include <haxorg/sem/SemOrg.hpp>
#include <hstd/stdlib/Exception.hpp>
#include <hstd/system/reflection.hpp>
#include <optional>
#include <stdexcept>
#include <string>
#include <tuple>
#include <typeindex>
#include <utility>

#include <emscripten.h>
#include <emscripten/bind.h>


template <typename T>
struct emscripten::smart_ptr_trait<org::sem::SemId<T>> {
    using PointerType  = org::sem::SemId<T>;
    using element_type = T;

    static T* get(PointerType const& ptr) { return const_cast<T*>(ptr.get()); }

    static sharing_policy get_sharing_policy() { return sharing_policy::BY_EMVAL; }

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

template <typename T>
struct holder_type_builder {
    template <typename... Args>
    static T init(Args&&... args) {
        return T(std::forward<Args>(args)...);
    }
};

template <typename T>
struct holder_type_builder<std::shared_ptr<T>> {
    template <typename... Args>
    static std::shared_ptr<T> init(Args&&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
};

template <typename T>
struct holder_type_builder<std::unique_ptr<T>> {
    template <typename... Args>
    static std::unique_ptr<T> init(Args&&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
};

template <typename T>
struct holder_type_builder<org::sem::SemId<T>> {
    template <typename... Args>
    static org::sem::SemId<T> init(Args&&... args) {
        return org::sem::SemId<T>::New(std::forward<Args>(args)...);
    }
};

template <typename T, typename... Args>
T holder_type_constructor(Args&&... args) {
    return holder_type_builder<T>::init(std::forward<Args>(args)...);
}

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
    for (hstd::EnumFieldDesc<E> const& d : hstd::describe_enumerators<E>()) {
        e = e.value(d.name.c_str(), d.value);
    }

    emscripten::function(("format_" + name).c_str(), +[](E const& value) -> std::string {
        return hstd::fmt1(value);
    });
}

template <typename T>
void stdvector_bind(type_registration_guard& g, std::string const& name) {
    using VT = std::vector<T>;
    if (g.can_add<VT>()) {
        emscripten::class_<VT>(name.c_str())
            .function("size", &VT::size)
            .function("push_back", static_cast<void (VT::*)(T const&)>(&VT::push_back))
            .function("pop_back", &VT::pop_back)
            .function("clear", &VT::clear)
            .function("empty", static_cast<bool (VT::*)() const>(&VT::empty))
            .function("reserve", &VT::reserve)
            .function(
                "resize_with_value",
                static_cast<void (VT::*)(size_t, T const&)>(&VT::resize))
            .function("at", static_cast<T const& (VT::*)(std::size_t) const>(&VT::at))
            .function("front", static_cast<T const& (VT::*)() const>(&VT::front))
            .function("back", static_cast<T const& (VT::*)() const>(&VT::back))
            .function(
                "toArray", +[](hstd::Vec<T> const& self) -> emscripten::val {
                    emscripten::val result = emscripten::val::global("Array").new_();
                    for (size_t i = 0; i < self.size(); ++i) {
                        result.call<void>("push", self[i]);
                    }
                    return result;
                });
    }
}

template <typename T>
void hstdVec_bind(type_registration_guard& g, std::string const& name) {
    using VT = hstd::Vec<T>;
    if (g.can_add<VT>()) {
        emscripten::class_<VT>(name.c_str())
            .function("size", &VT::size)
            .function("push_back", static_cast<void (VT::*)(T const&)>(&VT::push_back))
            .function("pop_back", &VT::pop_back)
            .function("clear", &VT::clear)
            .function("empty", static_cast<bool (VT::*)() const>(&VT::empty))
            .function("reserve", &VT::reserve)
            .function(
                "resize_with_value",
                static_cast<void (VT::*)(size_t, T const&)>(&VT::resize))
            .function("at", static_cast<T const& (VT::*)(int) const>(&VT::at))
            .function("front", static_cast<T const& (VT::*)() const>(&VT::front))
            .function("back", static_cast<T const& (VT::*)() const>(&VT::back))
            .function(
                "toArray", +[](hstd::Vec<T> const& self) -> emscripten::val {
                    emscripten::val result = emscripten::val::global("Array").new_();
                    for (size_t i = 0; i < self.size(); ++i) {
                        result.call<void>("push", self[i]);
                    }
                    return result;
                });
    }
}

template <typename T>
void hstdextImmBox_bind(type_registration_guard& g, std::string const& name) {
    using BT = hstd::ext::ImmBox<T>;
    if (g.can_add<BT>()) {
        emscripten::class_<BT>(name.c_str())
            .template constructor<T const&>()
            .function(
                "value", +[](BT const& self) -> T const& { return *self; })
            .function("set", +[](BT const&, T const& value) -> BT { return BT(value); });
    }
}

template <typename T>
void hstdextImmVec_bind(type_registration_guard& g, std::string const& name) {
    using VT = hstd::ext::ImmVec<T>;
    if (g.can_add<VT>()) {
        emscripten::class_<VT>(name.c_str())
            .template constructor<>()
            .function("size", &VT::size)
            .function("empty", &VT::empty)
            .function(
                "at",
                +[](VT const& self, std::size_t idx) -> T const& { return self[idx]; })
            .function(
                "toArray", +[](VT const& self) -> emscripten::val {
                    emscripten::val result = emscripten::val::global("Array").new_();
                    for (std::size_t i = 0; i < self.size(); ++i) {
                        result.call<void>("push", self[i]);
                    }
                    return result;
                });
    }
}

template <typename T>
void immerbox_bind(type_registration_guard& g, std::string const& name) {
    hstdextImmBox_bind<T>(g, name);
}

template <typename T>
void immerflex_vector_bind(type_registration_guard& g, std::string const& name) {
    hstdextImmVec_bind<T>(g, name);
}

template <typename T>
void hstdUnorderedSet_bind(type_registration_guard& g, std::string const& name) {
    using ST = hstd::UnorderedSet<T>;
    if (g.can_add<ST>()) {
        emscripten::class_<ST>(name.c_str())
            .template constructor<>()
            .function("size", &ST::size)
            .function("empty", static_cast<bool (ST::*)() const>(&ST::empty))
            .function("clear", &ST::clear)
            .function("contains", &ST::contains)
            .function("incl", static_cast<void (ST::*)(T const&)>(&ST::incl))
            .function("excl", static_cast<void (ST::*)(T const&)>(&ST::excl))
            .function("items", &ST::items)
            .class_function("fromVec", &ST::FromVec);
    }
}

template <typename A, typename B>
void stdpair_bind(type_registration_guard& g, std::string const& name) {
    using PT = std::pair<A, B>;
    if (g.can_add<PT>()) {
        emscripten::class_<PT>(name.c_str())
            .template constructor<A const&, B const&>()
            .property("first", &PT::first)
            .property("second", &PT::second);
    }
}

template <typename K, typename V>
void stdunordered_map_bind(type_registration_guard& g, std::string const& name) {
    using MT = std::unordered_map<K, V>;
    if (g.can_add<MT>()) {
        emscripten::class_<MT>(name.c_str())
            .template constructor<>()
            .function("size", &MT::size)
            .function("empty", static_cast<bool (MT::*)() const>(&MT::empty))
            .function("clear", &MT::clear)
            .function(
                "erase",
                static_cast<typename MT::size_type (MT::*)(K const&)>(&MT::erase))
            .function(
                "contains",
                +[](MT const& self, K const& key) -> bool {
                    return self.find(key) != self.end();
                })
            .function("at", static_cast<V const& (MT::*)(K const&) const>(&MT::at))
            .function(
                "set",
                +[](MT& self, K const& key, V const& value) {
                    self.insert_or_assign(key, value);
                })
            .function(
                "items", +[](MT const& self) -> hstd::Vec<std::pair<K, V>> {
                    hstd::Vec<std::pair<K, V>> result;
                    result.reserve(self.size());
                    for (auto const& [k, v] : self) {
                        result.push_back(std::make_pair(k, v));
                    }
                    return result;
                });
    }
}

namespace detail {

template <typename Variant, std::size_t Index>
void bind_variant_alternative(emscripten::class_<Variant>& cls) {
    using Alt = std::variant_alternative_t<Index, Variant>;

    cls.function(
        ("is_" + std::to_string(Index)).c_str(),
        +[](Variant const& self) -> bool { return std::holds_alternative<Alt>(self); });

    cls.function(
        ("get_" + std::to_string(Index)).c_str(),
        +[](Variant const& self) -> Alt { return std::get<Alt>(self); });

    cls.class_function(
        ("from_" + std::to_string(Index)).c_str(),
        +[](Alt const& value) -> Variant { return Variant{value}; });
}

template <typename Variant, std::size_t... Indices>
void bind_variant_alternatives(
    emscripten::class_<Variant>& cls,
    std::index_sequence<Indices...>) {
    (bind_variant_alternative<Variant, Indices>(cls), ...);
}

} // namespace detail

template <typename... Ts>
void stdvariant_bind(type_registration_guard& g, std::string const& name) {
    using VT = std::variant<Ts...>;
    if (g.can_add<VT>()) {
        auto cls = emscripten::class_<VT>(name.c_str()).function("index", &VT::index);

        detail::bind_variant_alternatives<VT>(
            cls, std::make_index_sequence<sizeof...(Ts)>{});
    }
}

template <typename T>
void hstdIntSet_bind(type_registration_guard& g, std::string const& name) {}

template <typename K, typename V>
void hstdUnorderedMap_bind(type_registration_guard& g, std::string const& name) {}


template <typename T>
void stdoptional_bind(type_registration_guard& g, std::string const& name) {
    if (g.can_add<std::optional<T>>()) {
        emscripten::class_<std::optional<T>>(name.c_str()) //
            .function(
                "value",
                +[](std::optional<T> const& opt) -> T const& { return opt.value(); })
            .function(
                "has_value",
                +[](std::optional<T> const& opt) -> bool { return opt.has_value(); });
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
constexpr std::size_t count_required_args(Tuple const& args) {
    if constexpr (std::tuple_size_v<std::decay_t<Tuple>> == 0) {
        return 0;
    } else {
        std::size_t count = 0;
        boost::mp11::tuple_for_each(args, [&count](auto const& arg) {
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
            && std::is_same_v<callable_result_t<Functor, Args...>, ReturnType>>>
    Callable(Functor&& functor, ArgsTuple args)
        : function_(nullptr)
        , args_(std::move(args))
        , functor_(
              std::make_shared<FunctorWrapper<std::decay_t<Functor>>>(
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
            throw std::runtime_error("Callable has no valid function or functor");
        }
    }

    const ArgsTuple& args() const { return args_; }
    FunctionType     function() const { return function_; }
    bool             isFunctor() const { return functor_ != nullptr; }

    int getRequiredArgsCount() const { return count_required_args(args()); }

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

        explicit FunctorWrapper(Functor&& f) : functor(std::forward<Functor>(f)) {}

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
    ReturnType operator()(ClassType* instance, CallArgs&&... callArgs) const {
        return invoke(
            instance,
            std::index_sequence_for<Args...>{},
            std::forward<CallArgs>(callArgs)...);
    }

    const ArgsTuple& args() const { return args_; }
    MethodType       method() const { return method_; }

    int getRequiredArgsCount() const { return count_required_args(args()); }


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
    ReturnType operator()(ClassType const* instance, CallArgs&&... callArgs) const {
        return invoke(
            instance,
            std::index_sequence_for<Args...>{},
            std::forward<CallArgs>(callArgs)...);
    }

    const ArgsTuple& args() const { return args_; }
    MethodType       method() const { return method_; }

    int getRequiredArgsCount() const { return count_required_args(args()); }

  private:
    MethodType method_;
    ArgsTuple  args_;

    template <size_t... Indices, typename... CallArgs>
    ReturnType invoke(
        ClassType const* instance,
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
    typename            = std::enable_if_t<is_callable<Functor, Args...>::value>>
auto makeCallable(Functor&& functor, std::tuple<CxxArgSpec<std::decay_t<Args>>...> args) {
    return Callable<CallableClass<std::monostate>, ReturnType, Args...>(
        std::forward<Functor>(functor), std::move(args));
}

// For constructors
template <typename ConstructedType, typename... Args>
auto makeConstructorCallable(std::tuple<CxxArgSpec<std::decay_t<Args>>...> args) {
    return Callable<CallableClass<std::monostate>, ConstructedType, Args...>::
        template ForConstructor<ConstructedType>(std::move(args));
}


} // namespace org::bind::js
