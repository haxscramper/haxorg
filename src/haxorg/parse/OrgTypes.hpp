#pragma once

#include <hstd/stdlib/dod_base.hpp>

#include <haxorg/lexbase/Token.hpp>
#include <haxorg/lexbase/Node.hpp>
#include <haxorg/sem/SemOrgEnums.hpp>
#include <haxorg/base_lexer/base_token.hpp>
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

using OrgToken = Token<OrgTokenKind, OrgFill>;

struct OrgNodeMono {
    struct None {
        DESC_FIELDS(None, ());
    };

    struct Error {
        struct Box {
            std::string error;
            int         parserLine;
            std::string parserFunction;
            OrgToken    failToken;
            DESC_FIELDS(
                Box,
                (error, parserLine, parserFunction, failToken));
        };

        SPtr<Box> box;
        DESC_FIELDS(Error, (box));
    };

    SUB_VARIANTS(Kind, Data, data, getKind, None, Error);
    Data data;
    DESC_FIELDS(OrgNodeMono, (data));
};

template <>
struct std::formatter<OrgNodeMono::Error> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const OrgNodeMono::Error& p, FormatContext& ctx) const {
        if (p.box) {
            return fmt_ctx(*p.box, ctx);
        } else {
            return fmt_ctx("Error{}", ctx);
        }
    }
};


using OrgTokenId    = TokenId<OrgTokenKind, OrgFill>;
using OrgTokenStore = TokenStore<OrgTokenKind, OrgFill>;
using OrgTokenGroup = TokenGroup<OrgTokenKind, OrgFill>;
using OrgNode = Node<OrgNodeKind, OrgTokenKind, OrgFill, OrgNodeMono>;
using OrgId   = NodeId<OrgNodeKind, OrgTokenKind, OrgFill, OrgNodeMono>;
using OrgNodeGroup = NodeGroup<
    OrgNodeKind,
    OrgTokenKind,
    OrgFill,
    OrgNodeMono>;
using OrgLexer   = LexerCommon<OrgTokenKind, OrgFill>;
using OrgTokSet  = IntSet<OrgTokenKind>;
using OrgAdapter = NodeAdapter<
    OrgNodeKind,
    OrgTokenKind,
    OrgFill,
    OrgNodeMono>;
using OrgSet = IntSet<OrgNodeKind>;

extern template class NodeGroup<
    OrgNodeKind,
    OrgTokenKind,
    OrgFill,
    OrgNodeMono>;
