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
#if !ORG_EMCC_BUILD
        result.eager = cpptrace::generate_trace();
#endif
        result.msg = hstd::fmt(
            "Unexpected kind {} (0x{:X}",
            kind,
            static_cast<std::underlying_type_t<E>>(kind));
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
        throw ::hstd::logic_assertion_error::init(
            ::hstd::fmt(
                "Expected non-nullptr value for type {}",
                hstd::value_metadata<T>::typeName()),
            line,
            function,
            file);
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
        throw ::hstd::logic_assertion_error::init(
            ::hstd::fmt(
                "Expected non-nil value for type {}",
                hstd::value_metadata<T>::typeName()),
            line,
            function,
            file);
    }
}
} // namespace hstd
