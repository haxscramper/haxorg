#pragma once

#include <haxorg/base_lexer/base_token.hpp>
#include <haxorg/lexbase/TokenStore.hpp>

namespace org::parse {
using OrgTokenGroup = TokenGroup<OrgTokenKind, OrgFill>;

struct LexerParams : hstd::OperationsTracer {
    struct Loc {
        int line;
        int col;
    };
};


OrgTokenGroup tokenize(std::string const& text, LexerParams const& p);


} // namespace org::parse
