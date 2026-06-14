#pragma once

#include <hstd/stdlib/ColText.hpp>
#include <hstd/stdlib/Formatter.hpp>


template <>
struct fmt::formatter<hstd::ColRune> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(hstd::ColRune const& p, fmt::format_context& ctx) const {
        hstd::fmt_ctx("{", ctx);
        hstd::fmt_ctx(p.rune, ctx);
        if (p.style.fg != (hstd::TermColorFg8Bit)0) {
            hstd::fmt_ctx(":fg", ctx);
            hstd::fmt_ctx(p.style.fg, ctx);
        }

        if (p.style.bg != (hstd::TermColorBg8Bit)0) {
            hstd::fmt_ctx(":bg", ctx);
            hstd::fmt_ctx(p.style.bg, ctx);
        }

        for (auto const& it : p.style.style) {
            hstd::fmt_ctx(":", ctx);
            hstd::fmt_ctx(it, ctx);
        }

        return hstd::fmt_ctx("}", ctx);
    }
};


template <>
struct fmt::formatter<hstd::ColText> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(hstd::ColText const& p, fmt::format_context& ctx) const {
        return fmt::formatter<std::string>{}.format(p.toString(false), ctx);
    }
};
