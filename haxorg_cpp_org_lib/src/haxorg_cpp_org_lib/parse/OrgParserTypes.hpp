#pragma once

#include <haxorg_cpp_org_lib/base_lexer/base_token.hpp>
#include <haxorg_cpp_org_lib/lexbase/Lexer.hpp>
#include <haxorg_cpp_org_lib/lexbase/NodeAdapter.hpp>
#include <haxorg_cpp_org_lib/lexbase/Token.hpp>
#include <haxorg_cpp_org_lib/lexbase/TokenStore.hpp>
#include <haxorg_cpp_org_lib/parse/OrgTypes.hpp>

namespace org::parse {


using OrgToken = Token<org::sem::OrgTokenKind, OrgFill>;

template <>
struct TokenUtils<org::sem::OrgTokenKind, OrgFill> {
    static hstd::Opt<SourceLoc> getLocation(OrgToken const& tok) {
        if (tok.value.loc) {
            return tok.value.loc.value();
        } else {
            return std::nullopt;
        }
    }

    static std::string_view getText(OrgToken const& tok) { return tok.value.text(); }
};

using OrgLexer      = LexerCommon<org::sem::OrgTokenKind, OrgFill>;
using OrgTokenStore = TokenStore<org::sem::OrgTokenKind, OrgFill>;
using OrgTokenGroup = TokenGroup<org::sem::OrgTokenKind, OrgFill>;
using OrgLexer      = LexerCommon<org::sem::OrgTokenKind, OrgFill>;
using OrgTokSet     = hstd::IntSet<org::sem::OrgTokenKind>;

using OrgNodeGroup = NodeGroup<
    org::sem::OrgNodeKind,
    org::sem::OrgTokenKind,
    OrgFill,
    OrgNodeMono>;


using OrgAdapter = NodeAdapter<
    org::sem::OrgNodeKind,
    org::sem::OrgTokenKind,
    OrgFill,
    OrgNodeMono>;

extern template class NodeGroup<
    org::sem::OrgNodeKind,
    org::sem::OrgTokenKind,
    OrgFill,
    OrgNodeMono>;


using OrgTokenId = TokenId<org::sem::OrgTokenKind, OrgFill>;

using OrgNode = Node<org::sem::OrgNodeKind, org::sem::OrgTokenKind, OrgFill, OrgNodeMono>;
using OrgId = NodeId<org::sem::OrgNodeKind, org::sem::OrgTokenKind, OrgFill, OrgNodeMono>;


} // namespace org::parse
