#pragma once
#include <hstd/system/exceptions.hpp>
#include <hstd/stdlib/Str.hpp>

namespace hstd {
struct logic_unhandled_kind_error
    : CRTP_hexception<logic_unhandled_kind_error> {
    template <IsEnum E>
    static logic_unhandled_kind_error init(
        E           kind,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION(),
        char const* file     = __builtin_FILE()) {
        auto result = logic_unhandled_kind_error{};
#if !ORG_BUILD_EMCC
        result.eager = cpptrace::generate_trace();
#endif
        result.msg = "Unexpected kind ";
        result.msg += hstd::enum_to_string(kind);
        result.msg += " ("
                    + std::to_string(
                          static_cast<std::underlying_type_t<E>>(kind))
                    + ")";

        result.line     = line;
        result.file     = file;
        result.function = function;
        return result;
    }
};
} // namespace hstd


namespace hstd {
template <typename T>
void logic_assertion_check_not_nil(
    T const*    ptr,
    int         line     = __builtin_LINE(),
    char const* function = __builtin_FUNCTION(),
    char const* file     = __builtin_FILE()) {
    if (hstd::value_metadata<T const*>::isNil(ptr)) {
        std::string msg = "Expected non-nullptr value for type ";
        msg += hstd::value_metadata<T>::typeName();
        throw ::hstd::logic_assertion_error::init(
            msg, line, function, file);
    }
}

template <typename T>
void logic_assertion_check_not_nil(std::unique_ptr<T> const& p) {
    return logic_assertion_check_not_nil(p.get());
}

template <typename T>
void logic_assertion_check_not_nil(std::shared_ptr<T> const& p) {
    return logic_assertion_check_not_nil(p.get());
}

template <typename T>
void logic_assertion_check_not_nil(std::weak_ptr<T> const& p) {
    return logic_assertion_check_not_nil(p.lock().get());
}

template <typename T>
void logic_assertion_check_not_nil(
    T const&    ptr,
    int         line     = __builtin_LINE(),
    char const* function = __builtin_FUNCTION(),
    char const* file     = __builtin_FILE()) {
    if (hstd::value_metadata<T>::isNil(ptr)) {
        std::string msg = "Expected non-nil value for type ";
        msg += hstd::value_metadata<T>::typeName();
        throw ::hstd::logic_assertion_error::init(
            msg, line, function, file);
    }
}
} // namespace hstd
