#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <haxorg/lexbase/Token.hpp>
#include <hstd/system/reflection.hpp>
#include <haxorg/sem/SemOrgEnums.hpp>

namespace org::parse {

struct OrgFill {
    hstd::Str text;
    int       line = -1;
    int       col  = -1;
    bool      isFake() const { return line == -1 && col == -1; }
};

using OrgToken      = Token<OrgTokenKind, OrgFill>;
using OrgTokenGroup = TokenGroup<OrgTokenKind, OrgFill>;
using OrgTokenId    = TokenId<OrgTokenKind, OrgFill>;

struct LexerParams {
    struct Loc {
        int line;
        int col;
    };
    int            maxUnknown      = 100;
    int            visitedUnknown  = 0;
    std::ostream*  traceStream     = nullptr;
    int            indentation     = 0;
    bool           traceStructured = false;
    hstd::Vec<Loc> sub_locations;
};


OrgTokenGroup tokenize(const char* input, int size, LexerParams const& p);


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
        return ctx.out();
    }
};
