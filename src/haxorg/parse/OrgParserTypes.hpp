#pragma once

#include <haxorg/lexbase/Token.hpp>
#include <haxorg/lexbase/TokenStore.hpp>
#include <haxorg/parse/OrgTypes.hpp>
#include <haxorg/lexbase/Lexer.hpp>

namespace org::parse {
using OrgLexer      = LexerCommon<OrgTokenKind, OrgFill>;
using OrgTokenStore = TokenStore<OrgTokenKind, OrgFill>;
using OrgTokenGroup = TokenGroup<OrgTokenKind, OrgFill>;
using OrgLexer      = LexerCommon<OrgTokenKind, OrgFill>;
using OrgTokSet     = hstd::IntSet<OrgTokenKind>;
} // namespace org::parse
