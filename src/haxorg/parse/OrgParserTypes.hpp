#pragma once

#include <haxorg/lexbase/Token.hpp>
#include <haxorg/lexbase/TokenStore.hpp>
#include <haxorg/parse/OrgTypes.hpp>
#include <haxorg/lexbase/Lexer.hpp>
#include <haxorg/base_lexer/base_token.hpp>
#include <haxorg/lexbase/NodeAdapter.hpp>

namespace org::parse {


using OrgToken = Token<OrgTokenKind, OrgFill>;

using OrgLexer      = LexerCommon<OrgTokenKind, OrgFill>;
using OrgTokenStore = TokenStore<OrgTokenKind, OrgFill>;
using OrgTokenGroup = TokenGroup<OrgTokenKind, OrgFill>;
using OrgLexer      = LexerCommon<OrgTokenKind, OrgFill>;
using OrgTokSet     = hstd::IntSet<OrgTokenKind>;

using OrgNodeGroup = NodeGroup<
    OrgNodeKind,
    OrgTokenKind,
    OrgFill,
    OrgNodeMono>;


using OrgAdapter = NodeAdapter<
    OrgNodeKind,
    OrgTokenKind,
    OrgFill,
    OrgNodeMono>;

extern template class NodeGroup<
    OrgNodeKind,
    OrgTokenKind,
    OrgFill,
    OrgNodeMono>;


using OrgTokenId = TokenId<OrgTokenKind, OrgFill>;

using OrgNode = Node<OrgNodeKind, OrgTokenKind, OrgFill, OrgNodeMono>;
using OrgId   = NodeId<OrgNodeKind, OrgTokenKind, OrgFill, OrgNodeMono>;


} // namespace org::parse
