#pragma once

#include <hstd/stdlib/ColText.hpp>
#include <hstd/stdlib/Formatter.hpp>


template <>
struct std::formatter<hstd::ColRune> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const hstd::ColRune& p, FormatContext& ctx) const {
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
struct std::formatter<hstd::ColText> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const hstd::ColText& p, FormatContext& ctx) const {
        return std::formatter<std::string>{}.format(
            p.toString(false), ctx);
    }
};
