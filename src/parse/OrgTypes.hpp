#pragma once

#include <hstd/stdlib/dod_base.hpp>

#include <lexbase/Token.hpp>
#include <lexbase/Node.hpp>
#include <sem/SemOrgEnums.hpp>


using OrgToken      = Token<OrgTokenKind>;
using OrgTokenId    = TokenId<OrgTokenKind>;
using OrgTokenStore = TokenStore<OrgTokenKind>;
using OrgTokenGroup = TokenGroup<OrgTokenKind>;

using OrgNode      = Node<OrgNodeKind, OrgTokenKind>;
using OrgId        = NodeId<OrgNodeKind, OrgTokenKind>;
using OrgNodeGroup = NodeGroup<OrgNodeKind, OrgTokenKind>;

extern template class NodeGroup<OrgNodeKind, OrgTokenKind>;

using OrgLexer   = LexerCommon<OrgTokenKind>;
using OrgTokSet  = IntSet<OrgTokenKind>;
using OrgAdapter = NodeAdapter<OrgNodeKind, OrgTokenKind>;
using OrgSet     = IntSet<OrgNodeKind>;

extern const OrgSet OrgAttachableCommands;
extern const OrgSet OrgTrailableCommands;
