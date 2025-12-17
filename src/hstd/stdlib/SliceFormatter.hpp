#pragma once

#include <hstd/stdlib/Slice.hpp>
#include <hstd/stdlib/Formatter.hpp>


template <typename T>
struct std::formatter<hstd::Span<T>> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        const hstd::Span<T>& p,
        FormatContext&       ctx) const {
        hstd::fmt_ctx("[", ctx);
        for (int i = 0; i < p.size(); ++i) {
            if (0 < i) { hstd::fmt_ctx(", ", ctx); }
            hstd::fmt_ctx(p.at(i), ctx);
        }

        return hstd::fmt_ctx("]", ctx);
    }
};
