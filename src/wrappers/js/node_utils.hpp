#include <napi.h>
#include <optional>
#include <string>
#include <tuple>
#include <stdexcept>
#include <utility>

namespace org::bind::js {

// Argument specification template
template <typename T>
struct CxxArgSpec {
    std::string      name;
    std::optional<T> defaultValue = std::nullopt;

    using value_type = T;
};

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

// Specialization for standalone functions
template <typename ReturnType, typename... Args>
class Callable<CallableClass<std::monostate>, ReturnType, Args...> {
  public:
    using FunctionType = ReturnType (*)(Args...);
    using ArgsTuple    = std::tuple<CxxArgSpec<std::decay_t<Args>>...>;

    Callable(FunctionType func, ArgsTuple args)
        : function_(func), args_(std::move(args)) {}

    template <typename... CallArgs>
    ReturnType operator()(CallArgs&&... callArgs) const {
        return invoke(
            std::index_sequence_for<Args...>{},
            std::forward<CallArgs>(callArgs)...);
    }

    const ArgsTuple& args() const { return args_; }
    FunctionType     function() const { return function_; }

  private:
    FunctionType function_;
    ArgsTuple    args_;

    template <size_t... Indices, typename... CallArgs>
    ReturnType invoke(
        std::index_sequence<Indices...>,
        CallArgs&&... callArgs) const {
        return function_(std::forward<CallArgs>(callArgs)...);
    }
};

// Specialization for method pointers
template <typename ClassType, typename ReturnType, typename... Args>
class Callable<CallableClass<ClassType>, ReturnType, Args...> {
  public:
    using MethodType = ReturnType (ClassType::*)(Args...);
    using ArgsTuple  = std::tuple<CxxArgSpec<std::decay_t<Args>>...>;

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
    using MethodType = ReturnType (ClassType::*)(Args...) const;
    using ArgsTuple  = std::tuple<CxxArgSpec<std::decay_t<Args>>...>;

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

// Converter template for JS <-> C++ type conversions
template <typename T, typename Enable = void>
struct JsConverter {
    // Default implementations will cause compile errors if not specialized
    static T           from_js_value(const Napi::Value& value);
    static Napi::Value to_js_value(Napi::Env env, const T& value);
};

// Specialization for string
template <>
struct JsConverter<std::string> {
    static std::string from_js_value(const Napi::Value& value) {
        if (value.IsString()) {
            return value.As<Napi::String>().Utf8Value();
        }
        throw Napi::TypeError::New(value.Env(), "String expected");
    }

    static Napi::Value to_js_value(
        Napi::Env          env,
        const std::string& value) {
        return Napi::String::New(env, value);
    }
};

// Specialization for boolean
template <>
struct JsConverter<bool> {
    static bool from_js_value(const Napi::Value& value) {
        if (value.IsBoolean()) {
            return value.As<Napi::Boolean>().Value();
        }
        throw Napi::TypeError::New(value.Env(), "Boolean expected");
    }

    static Napi::Value to_js_value(Napi::Env env, const bool& value) {
        return Napi::Boolean::New(env, value);
    }
};

// Specialization for number (double)
template <>
struct JsConverter<double> {
    static double from_js_value(const Napi::Value& value) {
        if (value.IsNumber()) {
            return value.As<Napi::Number>().DoubleValue();
        }
        throw Napi::TypeError::New(value.Env(), "Number expected");
    }

    static Napi::Value to_js_value(Napi::Env env, const double& value) {
        return Napi::Number::New(env, value);
    }
};

// Specialization for integer
template <>
struct JsConverter<int> {
    static int from_js_value(const Napi::Value& value) {
        if (value.IsNumber()) {
            return value.As<Napi::Number>().Int32Value();
        }
        throw Napi::TypeError::New(value.Env(), "Integer expected");
    }

    static Napi::Value to_js_value(Napi::Env env, const int& value) {
        return Napi::Number::New(env, value);
    }
};

// Generic wrapper function for any Callable
template <typename CallableType, typename ClassInstance, size_t... Indices>
Napi::Value WrapCallableImpl(
    const Napi::CallbackInfo& info,
    const CallableType&       callable,
    ClassInstance             instance,
    std::index_sequence<Indices...>) {
    Napi::Env env = info.Env();

    try {
        // Get the argument specifications
        const auto& argSpecs = callable.args();

        // Convert arguments with proper type checking - now using pack
        // expansion instead of indexing into the tuple at runtime
        auto convertArg = [&info, &argSpecs]<size_t Index>() {
            // Get the type of the argument at compile-time index
            using ArgSpecType = std::
                tuple_element_t<Index, std::decay_t<decltype(argSpecs)>>;
            using ArgType = typename ArgSpecType::value_type;

            const auto& argSpec = std::get<Index>(argSpecs);

            if (Index < info.Length()) {
                return JsConverter<ArgType>::from_js_value(info[Index]);
            } else if (argSpec.defaultValue) {
                return *argSpec.defaultValue;
            } else {
                throw Napi::TypeError::New(
                    info.Env(),
                    "Missing required argument: " + argSpec.name);
            }
        };

        // Invoke the callable with appropriate arguments
        if constexpr (std::is_same_v<ClassInstance, std::nullptr_t>) {
            // Function call (no instance)
            using ReturnType = decltype(callable(
                convertArg.template operator()<Indices>()...));

            if constexpr (std::is_void_v<ReturnType>) {
                callable(convertArg.template operator()<Indices>()...);
                return env.Undefined();
            } else {
                ReturnType result = callable(
                    convertArg.template operator()<Indices>()...);
                return JsConverter<ReturnType>::to_js_value(env, result);
            }
        } else {
            // Method call (with instance)
            using ReturnType = decltype(callable(
                instance, convertArg.template operator()<Indices>()...));

            if constexpr (std::is_void_v<ReturnType>) {
                callable(
                    instance,
                    convertArg.template operator()<Indices>()...);
                return env.Undefined();
            } else {
                ReturnType result = callable(
                    instance,
                    convertArg.template operator()<Indices>()...);
                return JsConverter<ReturnType>::to_js_value(env, result);
            }
        }
    } catch (const Napi::Error& e) {
        // Re-throw Napi errors
        throw e;
    } catch (const std::exception& e) {
        // Convert C++ exceptions to JavaScript errors
        throw Napi::Error::New(env, e.what());
    } catch (...) {
        // Handle unknown exceptions
        throw Napi::Error::New(env, "Unknown C++ exception occurred");
    }
}

// Wrapper for standalone functions
template <typename ReturnType, typename... Args>
Napi::Value WrapFunction(
    const Napi::CallbackInfo& info,
    const Callable<CallableClass<std::monostate>, ReturnType, Args...>&
        callable) {
    return WrapCallableImpl(
        info, callable, nullptr, std::index_sequence_for<Args...>{});
}

// Wrapper for non-const methods
template <typename ClassType, typename ReturnType, typename... Args>
Napi::Value WrapMethod(
    const Napi::CallbackInfo& info,
    ClassType*                instance,
    const Callable<CallableClass<ClassType>, ReturnType, Args...>&
        callable) {
    return WrapCallableImpl(
        info, callable, instance, std::index_sequence_for<Args...>{});
}


// Wrapper for const methods
template <typename ClassType, typename ReturnType, typename... Args>
Napi::Value WrapConstMethod(
    const Napi::CallbackInfo& info,
    const ClassType*          instance,
    const Callable<CallableClass<const ClassType>, ReturnType, Args...>&
        callable) {
    return WrapCallableImpl(
        info, callable, instance, std::index_sequence_for<Args...>{});
}


} // namespace org::bind::js
