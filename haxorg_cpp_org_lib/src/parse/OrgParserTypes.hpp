#pragma once

#include <haxorg/base_lexer/base_token.hpp>
#include <haxorg/lexbase/Lexer.hpp>
#include <haxorg/lexbase/NodeAdapter.hpp>
#include <haxorg/lexbase/Token.hpp>
#include <haxorg/lexbase/TokenStore.hpp>
#include <haxorg/parse/OrgTypes.hpp>

namespace org::parse {


using OrgToken = Token<OrgTokenKind, OrgFill>;

template <>
struct TokenUtils<OrgTokenKind, OrgFill> {
    static hstd::Opt<SourceLoc> getLocation(OrgToken const& tok) {
        if (tok.value.loc) {
            return tok.value.loc.value();
        } else {
            return std::nullopt;
        }
    }

    static std::string_view getText(OrgToken const& tok) { return tok.value.text(); }
};

using OrgLexer      = LexerCommon<OrgTokenKind, OrgFill>;
using OrgTokenStore = TokenStore<OrgTokenKind, OrgFill>;
using OrgTokenGroup = TokenGroup<OrgTokenKind, OrgFill>;
using OrgLexer      = LexerCommon<OrgTokenKind, OrgFill>;
using OrgTokSet     = hstd::IntSet<OrgTokenKind>;

using OrgNodeGroup = NodeGroup<OrgNodeKind, OrgTokenKind, OrgFill, OrgNodeMono>;


using OrgAdapter = NodeAdapter<OrgNodeKind, OrgTokenKind, OrgFill, OrgNodeMono>;

extern template class NodeGroup<OrgNodeKind, OrgTokenKind, OrgFill, OrgNodeMono>;


using OrgTokenId = TokenId<OrgTokenKind, OrgFill>;

using OrgNode = Node<OrgNodeKind, OrgTokenKind, OrgFill, OrgNodeMono>;
using OrgId   = NodeId<OrgNodeKind, OrgTokenKind, OrgFill, OrgNodeMono>;


} // namespace org::parse
