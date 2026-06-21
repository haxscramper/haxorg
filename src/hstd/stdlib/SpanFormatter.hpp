#pragma once

#include <hstd/stdlib/Span.hpp>
#include <hstd/stdlib/Formatter.hpp>

template <typename T>
struct fmt::formatter<hstd::Span<T>> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(hstd::Span<T> const& p, fmt::format_context& ctx) const {
        hstd::fmt_ctx("[", ctx);
        for (int i = 0; i < p.size(); ++i) {
            if (0 < i) { hstd::fmt_ctx(", ", ctx); }
            hstd::fmt_ctx(p.at(i), ctx);
        }

        return hstd::fmt_ctx("]", ctx);
    }
};
