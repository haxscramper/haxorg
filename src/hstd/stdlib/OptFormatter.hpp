#pragma once

#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Formatter.hpp>

template <typename T>
struct fmt::formatter<hstd::Opt<T>> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(hstd::Opt<T> const& p, fmt::format_context& ctx) const {
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
struct fmt::formatter<std::nullopt_t> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(std::nullopt_t const& p, fmt::format_context& ctx) const {
        return ::hstd::fmt_ctx("nullopt", ctx);
    }
};
