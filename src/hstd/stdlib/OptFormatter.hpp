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
            ::hstd::fmt_ctx("some(", ctx);
            ::hstd::fmt_ctx(p.value(), ctx);
            return ::hstd::fmt_ctx(")", ctx);
        } else {
            return ::hstd::fmt_ctx("none()", ctx);
        }
    }
};

template <>
struct std::formatter<std::nullopt_t> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        std::nullopt_t const& p,
        FormatContext&        ctx) const {
        return ::hstd::fmt_ctx("nullopt", ctx);
    }
};
