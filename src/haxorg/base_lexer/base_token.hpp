#pragma once

#include <string>
#include <hstd/stdlib/TraceBase.hpp>
#include <haxorg/lexbase/Token.hpp>
#include <hstd/system/reflection.hpp>
#include <haxorg/sem/SemOrgEnums.hpp>

namespace org::parse {

struct OrgFill {
    hstd::Str                        text;
    hstd::Opt<org::parse::SourceLoc> loc;
    bool isFake() const { return !loc.has_value(); }
    DESC_FIELDS(OrgFill, (text, loc));
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
        std::formatter<std::string>{}.format(">", ctx);
        if (p.loc.has_value()) {
            ::hstd::fmt_ctx(":", ctx);
            ::hstd::fmt_ctx(p.loc->line, ctx);
            std::formatter<std::string>{}.format(":", ctx);
            ::hstd::fmt_ctx(p.loc->column, ctx);
            std::formatter<std::string>{}.format(":", ctx);
            ::hstd::fmt_ctx(p.loc->pos, ctx);
            std::formatter<std::string>{}.format("@", ctx);
            ::hstd::fmt_ctx(p.loc->file_id.format(""), ctx);
        }
        return ctx.out();
    }
};
