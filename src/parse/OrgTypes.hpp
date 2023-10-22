#pragma once

#include <hstd/stdlib/dod_base.hpp>

#include <lexbase/Token.hpp>
#include <lexbase/Node.hpp>
#include <sem/SemOrgEnums.hpp>
#include <base_lexer/base_token.hpp>

struct OrgFill {
    Opt<BaseToken> base;
    Str            getText() const { return base.value().text; }
};

using OrgToken      = Token<OrgTokenKind, OrgFill>;
using OrgTokenId    = TokenId<OrgTokenKind, OrgFill>;
using OrgTokenStore = TokenStore<OrgTokenKind, OrgFill>;
using OrgTokenGroup = TokenGroup<OrgTokenKind, OrgFill>;
using OrgNode       = Node<OrgNodeKind, OrgTokenKind, OrgFill>;
using OrgId         = NodeId<OrgNodeKind, OrgTokenKind, OrgFill>;
using OrgNodeGroup  = NodeGroup<OrgNodeKind, OrgTokenKind, OrgFill>;
using BaseLexer     = LexerCommon<BaseTokenKind, BaseFill>;
using OrgLexer      = LexerCommon<OrgTokenKind, OrgFill>;
using OrgTokSet     = IntSet<OrgTokenKind>;
using OrgAdapter    = NodeAdapter<OrgNodeKind, OrgTokenKind, OrgFill>;
using OrgSet        = IntSet<OrgNodeKind>;

extern template class NodeGroup<OrgNodeKind, OrgTokenKind, OrgFill>;
extern const OrgSet OrgAttachableCommands;
extern const OrgSet OrgTrailableCommands;
