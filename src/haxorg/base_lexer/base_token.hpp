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
    bool                             isFake() const { return !loc.has_value(); }
    DESC_FIELDS(OrgFill, (text, loc));
};

using OrgToken   = Token<OrgTokenKind, OrgFill>;
using OrgTokenId = TokenId<OrgTokenKind, OrgFill>;
} // namespace org::parse


template <>
struct fmt::formatter<org::parse::OrgFill> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(org::parse::OrgFill const& p, fmt::format_context& ctx) const {
        ::hstd::fmt_ctx("<", ctx);
        ::hstd::fmt_ctx(escape_for_write(p.text), ctx);
        ::hstd::fmt_ctx(">", ctx);
        if (p.loc.has_value()) {
            ::hstd::fmt_ctx(":", ctx);
            ::hstd::fmt_ctx(p.loc->line, ctx);
            ::hstd::fmt_ctx(":", ctx);
            ::hstd::fmt_ctx(p.loc->column, ctx);
            ::hstd::fmt_ctx(":", ctx);
            ::hstd::fmt_ctx(p.loc->pos, ctx);
            ::hstd::fmt_ctx("@", ctx);
            ::hstd::fmt_ctx(p.loc->file_id.format(), ctx);
        }
        return ctx.out();
    }
};
