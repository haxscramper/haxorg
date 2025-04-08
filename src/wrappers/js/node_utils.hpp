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
};

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

// Specialization for int64_t
template <>
struct JsConverter<int64_t> {
    static int64_t from_js_value(const Napi::Value& value) {
        if (value.IsNumber() || value.IsBigInt()) {
            return value.IsBigInt()
                     ? value.As<Napi::BigInt>().Int64Value(nullptr)
                     : static_cast<int64_t>(
                           value.As<Napi::Number>().Int64Value());
        }
        throw Napi::TypeError::New(
            value.Env(), "Integer or BigInt expected");
    }

    static Napi::Value to_js_value(Napi::Env env, const int64_t& value) {
        return Napi::BigInt::New(env, value);
    }
};

// Specialization for arrays using std::vector
template <typename T>
struct JsConverter<std::vector<T>> {
    static std::vector<T> from_js_value(const Napi::Value& value) {
        if (!value.IsArray()) {
            throw Napi::TypeError::New(value.Env(), "Array expected");
        }

        Napi::Array    array = value.As<Napi::Array>();
        std::vector<T> result;
        result.reserve(array.Length());

        for (uint32_t i = 0; i < array.Length(); i++) {
            result.push_back(JsConverter<T>::from_js_value(array[i]));
        }

        return result;
    }

    static Napi::Value to_js_value(
        Napi::Env             env,
        const std::vector<T>& value) {
        Napi::Array array = Napi::Array::New(env, value.size());

        for (size_t i = 0; i < value.size(); i++) {
            array[i] = JsConverter<T>::to_js_value(env, value[i]);
        }

        return array;
    }
};

// Specialization for optional values
template <typename T>
struct JsConverter<std::optional<T>> {
    static std::optional<T> from_js_value(const Napi::Value& value) {
        if (value.IsNull() || value.IsUndefined()) { return std::nullopt; }
        return JsConverter<T>::from_js_value(value);
    }

    static Napi::Value to_js_value(
        Napi::Env               env,
        const std::optional<T>& value) {
        if (!value.has_value()) { return env.Null(); }
        return JsConverter<T>::to_js_value(env, value.value());
    }
};

// Main wrapper function for free functions
template <typename ReturnType, typename... Args, size_t... Indices>
Napi::Value WrapFunctionImpl(
    const Napi::CallbackInfo& info,
    ReturnType (*func)(Args...),
    const std::tuple<CxxArgSpec<std::decay_t<Args>>...>& argSpecs,
    std::index_sequence<Indices...>) {
    Napi::Env env = info.Env();

    try {
        // Convert arguments with proper type checking
        auto convertArg = [&](size_t index, const auto& argSpec) {
            using ArgType = typename std::decay<
                decltype(std::get<Indices...>(
                    std::tuple<Args...>{}))>::type;

            if (index < info.Length()) {
                return JsConverter<ArgType>::from_js_value(info[index]);
            } else if (argSpec.defaultValue) {
                return *argSpec.defaultValue;
            } else {
                throw Napi::TypeError::New(
                    env, "Missing required argument: " + argSpec.name);
            }
        };

        if constexpr (std::is_void_v<ReturnType>) {
            // Call function with void return type
            func(convertArg(Indices, std::get<Indices>(argSpecs))...);
            return env.Undefined();
        } else {
            // Call function with non-void return type
            ReturnType result = func(
                convertArg(Indices, std::get<Indices>(argSpecs))...);
            return JsConverter<ReturnType>::to_js_value(env, result);
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

// Main wrapper function for methods
template <
    typename ClassType,
    typename ReturnType,
    typename... Args,
    size_t... Indices>
Napi::Value WrapMethodImpl(
    const Napi::CallbackInfo& info,
    ClassType*                instance,
    ReturnType (ClassType::*method)(Args...),
    const std::tuple<CxxArgSpec<std::decay_t<Args>>...>& argSpecs,
    std::index_sequence<Indices...>) {
    Napi::Env env = info.Env();

    try {
        // Convert arguments with proper type checking
        auto convertArg = [&](size_t index, const auto& argSpec) {
            using ArgType = typename std::decay<
                decltype(std::get<Indices...>(
                    std::tuple<Args...>{}))>::type;

            if (index < info.Length()) {
                return JsConverter<ArgType>::from_js_value(info[index]);
            } else if (argSpec.defaultValue) {
                return *argSpec.defaultValue;
            } else {
                throw Napi::TypeError::New(
                    env, "Missing required argument: " + argSpec.name);
            }
        };

        if constexpr (std::is_void_v<ReturnType>) {
            // Call method with void return type
            (instance->*method)(
                convertArg(Indices, std::get<Indices>(argSpecs))...);
            return env.Undefined();
        } else {
            // Call method with non-void return type
            ReturnType result = (instance->*method)(
                convertArg(Indices, std::get<Indices>(argSpecs))...);
            return JsConverter<ReturnType>::to_js_value(env, result);
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

// Public API for wrapping free functions
template <typename ReturnType, typename... Args>
Napi::Value WrapFunction(
    const Napi::CallbackInfo& info,
    ReturnType (*func)(Args...),
    const std::tuple<CxxArgSpec<std::decay_t<Args>>...>& argSpecs) {
    return WrapFunctionImpl(
        info, func, argSpecs, std::index_sequence_for<Args...>{});
}

// Public API for wrapping methods
template <typename ClassType, typename ReturnType, typename... Args>
Napi::Value WrapMethod(
    const Napi::CallbackInfo& info,
    ClassType*                instance,
    ReturnType (ClassType::*method)(Args...),
    const std::tuple<CxxArgSpec<std::decay_t<Args>>...>& argSpecs) {
    return WrapMethodImpl(
        info,
        instance,
        method,
        argSpecs,
        std::index_sequence_for<Args...>{});
}

// Helper for const methods
template <typename ClassType, typename ReturnType, typename... Args>
Napi::Value WrapConstMethod(
    const Napi::CallbackInfo& info,
    const ClassType*          instance,
    ReturnType (ClassType::*method)(Args...) const,
    const std::tuple<CxxArgSpec<std::decay_t<Args>>...>& argSpecs) {
    // Convert const method to a compatible form for our implementation
    auto nonConstInstance = const_cast<ClassType*>(instance);
    auto nonConstMethod   = reinterpret_cast<ReturnType (ClassType::*)(
        Args...)>(method);

    return WrapMethodImpl(
        info,
        nonConstInstance,
        nonConstMethod,
        argSpecs,
        std::index_sequence_for<Args...>{});
}

} // namespace org::bind::js
