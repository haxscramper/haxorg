#pragma once

#include <hstd/stdlib/dod_base.hpp>

#include <lexbase/Token.hpp>
#include <lexbase/Node.hpp>
#include <sem/SemOrgEnums.hpp>
#include <base_lexer/base_token.hpp>
#include <hstd/system/reflection.hpp>


template <>
struct std::formatter<OrgSpecName> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        OrgSpecName const& p,
        FormatContext&     ctx) const {
        std::formatter<std::string> fmt;
        return fmt.format(enum_serde<OrgSpecName>::to_string(p), ctx);
    }
};


using OrgToken      = Token<OrgTokenKind, OrgFill>;
using OrgTokenId    = TokenId<OrgTokenKind, OrgFill>;
using OrgTokenStore = TokenStore<OrgTokenKind, OrgFill>;
using OrgTokenGroup = TokenGroup<OrgTokenKind, OrgFill>;
using OrgNode       = Node<OrgNodeKind, OrgTokenKind, OrgFill>;
using OrgId         = NodeId<OrgNodeKind, OrgTokenKind, OrgFill>;
using OrgNodeGroup  = NodeGroup<OrgNodeKind, OrgTokenKind, OrgFill>;
using OrgLexer      = LexerCommon<OrgTokenKind, OrgFill>;
using OrgTokSet     = IntSet<OrgTokenKind>;
using OrgAdapter    = NodeAdapter<OrgNodeKind, OrgTokenKind, OrgFill>;
using OrgSet        = IntSet<OrgNodeKind>;

extern template class NodeGroup<OrgNodeKind, OrgTokenKind, OrgFill>;
