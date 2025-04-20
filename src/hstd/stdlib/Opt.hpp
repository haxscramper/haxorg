#pragma once

#include <optional>
#include <hstd/system/Formatter.hpp>
#include <hstd/stdlib/Exception.hpp>

namespace hstd {

template <typename T>
using Opt = std::optional<T>;


struct nullopt_optional_err : CRTP_hexception<nullopt_optional_err> {};

template <typename T>
T opt_value(
    CR<Opt<T>>  opt,
    CR<Str>     msg,
    int         line     = __builtin_LINE(),
    char const* function = __builtin_FUNCTION(),
    char const* file     = __builtin_FILE()) {
    if (opt) {
        return *opt;
    } else {
        throw nullopt_optional_err::init(
            "cannot unpack nullopt value "_ss + msg, line, function, file);
    }
}

template <
    typename T,
    typename F,
    typename Res = std::invoke_result<T(int)>::type>
Opt<Res> opt_map(CR<Opt<T>> opt, CR<F> cb) {
    if (opt) {
        return cb(*opt);
    } else {
        return std::nullopt;
    }
}

} // namespace hstd


template <typename T>
struct std::formatter<hstd::Opt<T>> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        hstd::Opt<T> const& p,
        FormatContext&      ctx) const {
        std::formatter<std::string> fmt;
        if (p.has_value()) {
            fmt.format("some(", ctx);
            ::hstd::with_std_formatter(p.value());
            std::formatter<T>{}.format(p.value(), ctx);
            return fmt.format(")", ctx);
        } else {
            return fmt.format("none()", ctx);
        }
    }
};

template <>
struct std::formatter<std::nullopt_t> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        std::nullopt_t const& p,
        FormatContext&        ctx) const {
        return fmt_ctx("nullopt", ctx);
    }
};
