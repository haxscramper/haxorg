#pragma once

#include <haxorg_cpp_org_lib/base_lexer/base_token.hpp>
#include <haxorg_cpp_org_lib/lexbase/Lexer.hpp>
#include <haxorg_cpp_org_lib/lexbase/NodeAdapter.hpp>
#include <haxorg_cpp_org_lib/lexbase/Token.hpp>
#include <haxorg_cpp_org_lib/lexbase/TokenStore.hpp>
#include <haxorg_cpp_org_lib/parse/OrgTypes.hpp>

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
