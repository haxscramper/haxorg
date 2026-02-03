#pragma once

#include <haxorg/lexbase/Errors.hpp>
#include <hstd/stdlib/Formatter.hpp>


template <>
struct std::formatter<org::parse::SourceLoc>
    : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        const org::parse::SourceLoc& p,
        FormatContext&               ctx) const {
        hstd::fmt_ctx(p.line, ctx);
        hstd::fmt_ctx(":", ctx);
        hstd::fmt_ctx(p.column, ctx);
        hstd::fmt_ctx(":", ctx);
        return hstd::fmt_ctx(p.pos, ctx);
    }
};
