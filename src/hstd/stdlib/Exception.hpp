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
