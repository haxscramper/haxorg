#pragma once

#include "haxorg/base_lexer/base_token.hpp"
#include <unordered_set>
#include <haxorg/lexbase/Node.hpp>
#include <haxorg/lexbase/Token.hpp>
#include <haxorg/lexbase/AstSpec.hpp>
#include <hstd/stdlib/algorithms.hpp>

#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/Yaml.hpp>


template <typename N, typename K, typename V, typename M>
yaml yamlRepr(
    CR<NodeGroup<N, K, V, M>> group,
    bool                      withStrings = true,
    bool                      withId      = false) {
    yaml out;
    for (const auto& [id, node] : group.nodes.pairs()) {
        yaml item;
        item["kind"] = fmt1(node->kind);
        if (withId) { item["id"] = id.getUnmasked(); }

        if (node->isTerminal()) {
            TokenId<K, V> tokenId = node->getToken();
            item["tok_idx"]       = tokenId.getIndex();
            if (withStrings) { item["str"] = group.val(id); }
        } else {
            item["extent"] = node->getExtent();
        }

        item.SetStyle(YAML::EmitterStyle::Flow);
        out.push_back(item);
    }
    return out;
}


template <typename N, typename K, typename V, typename M>
json jsonRepr(CR<NodeGroup<N, K, V, M>> group, bool withStrings = true) {
    json out = json::array();
    for (const auto& [id, node] : group.nodes.pairs()) {
        json item;
        item["kind"] = to_string(node->kind);
        if (node->isTerminal()) {
            TokenId<K, V> tokenId = node->getToken();
            item["tok_idx"]       = tokenId.getIndex();
            if (withStrings && group.hasData(id)) {
                item["str"] = group.strVal(id).toBase();
            }
        } else {
            item["extent"] = node->getExtent();
        }
        out.push_back(item);
    }
    return out;
}

namespace YAML {

template <typename K, typename V>
struct convert<typename ::Token<K, V>> {
    static Node encode(typename ::Token<K, V> const& str) {
        Node result;
        result["kind"] = fmt1(str.kind);
        result["str"]  = str.value;


        return result;
    }

    static bool decode(Node const& in, typename ::Token<K, V>& out) {
        out.kind = enum_serde<K>::from_string(in["kind"].as<Str>())
                       .value();

        if (in["value"]) { out.value = in["value"].as<V>(); }

        return true;
    }
};

template <>
struct convert<OrgFill> {
    static Node encode(OrgFill const& str) {
        Node result;
        result["text"] = str.text;
        result["line"] = str.line;
        result["col"]  = str.col;
        return result;
    }
    static bool decode(Node const& in, OrgFill& out) {
        if (in["text"]) { out.text = in["text"].as<Str>(); }

        if (in["line"]) { out.line = in["line"].as<int>(); }

        if (in["col"]) { out.col = in["col"].as<int>(); }

        return true;
    }
};
template <DescribedEnum E>
struct convert<E> {
    static Node encode(E const& str) {
        return enum_serde<E>::to_string(str);
    }
    static bool decode(Node const& in, E& out) {
        auto   str  = in.as<std::string>();
        Opt<E> conv = enum_serde<E>::from_string(str);
        if (conv) {
            out = conv.value();
        } else {
            throw YAML::RepresentationException(
                in.Mark(),
                fmt("Could not parse {} to {}",
                    str,
                    demangle(typeid(E).name())));
        }

        return true;
    }
};

template <>
struct convert<OrgToken> {
    static Node encode(OrgToken const& str) {
        Node result;
        result["kind"] = fmt1(str.kind);
        if (!str->text.empty()) { result["str"] = str->text; }
        return result;
    }
    static bool decode(Node const& in, OrgToken& out) {
        if (in["str"]) { out->text = in["str"].as<Str>(); }
        if (in["kind"]) { out.kind = in["kind"].as<OrgTokenKind>(); }
        return true;
    }
};

} // namespace YAML


template <typename K, typename V>
yaml yamlRepr(
    TokenId<K, V> const& id,
    Token<K, V> const&   token,
    bool                 withIdx = false) {
    yaml item = YAML::convert<Token<K, V>>::encode(token);
    if (withIdx) { item["idx"] = id.getIndex(); }

    item.SetStyle(YAML::EmitterStyle::Flow);
    return item;
}

template <typename K, typename V>
yaml yamlRepr(CR<TokenGroup<K, V>> group, bool withIdx = false) {
    yaml out;
    for (const auto& [id, token] : group.tokens.pairs()) {
        out.push_back(yamlRepr(id, *token, withIdx));
    }
    return out;
}

template <typename K, typename V>
json jsonRepr(CR<TokenGroup<K, V>> group, bool withIdx = false) {
    json out = json::array();
    for (const auto& [id, token] : group.tokens.pairs()) {
        json item;
        if (withIdx) { item["idx"] = id.getIndex(); }
        item["kind"] = to_string(token->kind);
        if (token->hasData()) { item["str"] = token->strVal().toBase(); }
        out.push_back(item);
    }
    return out;
}

template <typename N, typename K, typename V, typename M>
NodeGroup<N, K, V, M> fromFlatNodes(CR<yaml> node) {
    NodeGroup<N, K, V, M> result;
    result.nodes.resize(
        node.size(),
        Node<N, K, V, M>(value_domain<N>::low(), TokenId<K, V>::Nil()));
    int index = 0;
    for (const auto& it : node) {
        N kind = enum_serde<N>::from_string(it["kind"].as<std::string>())
                     .value();
        if (it["extent"]) {
            result.at(NodeId<N, K, V, M>(index)) = Node<N, K, V, M>(
                kind, it["extent"].as<int>());
        } else {
            result.at(NodeId<N, K, V, M>(index)) = Node<N, K, V, M>(
                kind, TokenId<K, V>(it["tok_idx"].as<int>()));
        }
        ++index;
    }

    return result;
}

template <typename K, typename V>
TokenGroup<K, V> fromFlatTokens(CR<yaml> node, Str& buf) {
    TokenGroup<K, V> result;
    result.tokens.resize(node.size());
    int index = 0;
    for (const auto& it : node) {
        auto start    = buf.size();
        auto id       = TokenId<K, V>(index);
        result.at(id) = it.as<Token<K, V>>();
        ++index;
    }

    return result;
}
