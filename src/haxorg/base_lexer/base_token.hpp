#pragma once

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
    hstd::fmt_iter format(org::parse::OrgFill const& p, fmt::format_context& ctx) const;
};
