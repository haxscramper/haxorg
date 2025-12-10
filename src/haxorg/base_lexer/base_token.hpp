#pragma once

#include <string>
#include <hstd/stdlib/TraceBase.hpp>
#include <haxorg/lexbase/Token.hpp>
#include <hstd/system/reflection.hpp>
#include <haxorg/sem/SemOrgEnums.hpp>

namespace org::parse {

struct OrgFill {
    hstd::Str text;
    int       line = -1;
    int       col  = -1;
    int       pos  = -1;
    bool      isFake() const { return line == -1 && col == -1; }
    DESC_FIELDS(OrgFill, (text, line, col, pos));
};

using OrgToken   = Token<OrgTokenKind, OrgFill>;
using OrgTokenId = TokenId<OrgTokenKind, OrgFill>;
} // namespace org::parse


template <>
struct std::formatter<org::parse::OrgFill> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        org::parse::OrgFill const& p,
        FormatContext&             ctx) const {
        std::formatter<std::string>{}.format("<", ctx);
        ::hstd::fmt_ctx(escape_for_write(p.text), ctx);
        std::formatter<std::string>{}.format(">:", ctx);
        ::hstd::fmt_ctx(p.line, ctx);
        std::formatter<std::string>{}.format(":", ctx);
        ::hstd::fmt_ctx(p.col, ctx);
        std::formatter<std::string>{}.format(":", ctx);
        ::hstd::fmt_ctx(p.pos, ctx);
        return ctx.out();
    }
};
