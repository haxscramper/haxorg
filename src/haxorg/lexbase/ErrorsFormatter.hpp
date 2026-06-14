#pragma once

#include <haxorg/lexbase/Errors.hpp>
#include <hstd/stdlib/Formatter.hpp>


template <>
struct fmt::formatter<org::parse::SourceLoc> : fmt::formatter<std::string> {

    hstd::fmt_iter format(org::parse::SourceLoc const& p, fmt::format_context& ctx)
        const {
        hstd::fmt_ctx(p.line, ctx);
        hstd::fmt_ctx(":", ctx);
        hstd::fmt_ctx(p.column, ctx);
        hstd::fmt_ctx(":", ctx);
        return hstd::fmt_ctx(p.pos, ctx);
    }
};
