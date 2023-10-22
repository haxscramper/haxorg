#pragma once

#include <hstd/stdlib/dod_base.hpp>

#include <lexbase/Token.hpp>
#include <lexbase/Node.hpp>
#include <sem/SemOrgEnums.hpp>
#include <base_lexer/base_token.hpp>


using OrgToken      = Token<OrgTokenKind, BaseToken>;
using OrgTokenId    = TokenId<OrgTokenKind, BaseToken>;
using OrgTokenStore = TokenStore<OrgTokenKind, BaseToken>;
using OrgTokenGroup = TokenGroup<OrgTokenKind, BaseToken>;

using OrgNode      = Node<OrgNodeKind, OrgTokenKind, BaseToken>;
using OrgId        = NodeId<OrgNodeKind, OrgTokenKind, BaseToken>;
using OrgNodeGroup = NodeGroup<OrgNodeKind, OrgTokenKind, BaseToken>;

extern template class NodeGroup<OrgNodeKind, OrgTokenKind, BaseToken>;

using BaseLexer  = LexerCommon<BaseTokenKind, BaseFill>;
using OrgLexer   = LexerCommon<OrgTokenKind, BaseToken>;
using OrgTokSet  = IntSet<OrgTokenKind>;
using OrgAdapter = NodeAdapter<OrgNodeKind, OrgTokenKind, BaseToken>;
using OrgSet     = IntSet<OrgNodeKind>;

extern const OrgSet OrgAttachableCommands;
extern const OrgSet OrgTrailableCommands;
