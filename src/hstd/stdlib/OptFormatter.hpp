#pragma once

#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Formatter.hpp>

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
