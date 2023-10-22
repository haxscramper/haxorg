#pragma once

#include <unordered_set>
#include <lexbase/Node.hpp>
#include <lexbase/Token.hpp>
#include <lexbase/AstSpec.hpp>
#include <hstd/stdlib/algorithms.hpp>

#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/Yaml.hpp>


template <typename N, typename K, typename V>
yaml yamlRepr(
    CR<NodeGroup<N, K, V>> group,
    bool                   withStrings = true,
    bool                   withId      = false) {
    yaml out;
    for (const auto& [id, node] : group.nodes.pairs()) {
        yaml item;
        item["kind"] = to_string(node->kind);
        if (withId) {
            item["id"] = id.getUnmasked();
        }

        if (node->isTerminal()) {
            TokenId<K, V> tokenId = node->getToken();
            item["tok_idx"]       = tokenId.getIndex();
            if (withStrings && group.hasData(id)) {
                item["str"] = group.strVal(id).toBase();
            }
        } else {
            item["extent"] = node->getExtent();
        }

        item.SetStyle(YAML::EmitterStyle::Flow);
        out.push_back(item);
    }
    return out;
}


template <typename N, typename K, typename V>
json jsonRepr(CR<NodeGroup<N, K, V>> group, bool withStrings = true) {
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

template <typename K, typename V>
yaml yamlRepr(
    TokenId<K, V> const& id,
    Token<K, V> const&   token,
    bool                 withIdx = false) {
    yaml item;
    if (withIdx) {
        item["idx"] = id.getIndex();
    }
    item["kind"] = to_string(token.kind);
    if (token.hasData()) {
        item["str"] = token.strVal().toBase();
    }
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
        if (withIdx) {
            item["idx"] = id.getIndex();
        }
        item["kind"] = to_string(token->kind);
        if (token->hasData()) {
            item["str"] = token->strVal().toBase();
        }
        out.push_back(item);
    }
    return out;
}

template <typename N, typename K, typename V>
NodeGroup<N, K, V> fromFlatNodes(CR<yaml> node) {
    NodeGroup<N, K, V> result;
    result.nodes.resize(
        node.size(), Node(value_domain<N>::low(), TokenId<K, V>::Nil()));
    int index = 0;
    for (const auto& it : node) {
        N kind = enum_serde<N>::from_string(it["kind"].as<std::string>())
                     .value();
        if (it["extent"]) {
            result.at(NodeId<N, K, V>(index)) = Node<N, K, V>(
                kind, it["extent"].as<int>());
        } else {
            result.at(NodeId<N, K, V>(index)) = Node<N, K, V>(
                kind, TokenId<K, V>(it["tok_idx"].as<int>()));
        }
        ++index;
    }

    return result;
}

template <typename K, typename V>
TokenGroup<K, V> fromFlatTokens(CR<yaml> node, Str& buf) {
    TokenGroup<K, V> result;
    assert(false);
    // TODO
    //    result.tokens.resize(node.size());
    //    int bufferSize = 0;
    //    for (const auto& it : node) {
    //        if (it["str"]) {
    //            bufferSize += it["str"].as<QString>().size();
    //        }
    //    }

    //    buf.reserve(bufferSize);
    //    auto data = buf.data();

    //    int index = 0;
    //    for (const auto& it : node) {
    //        auto start         = buf.size();
    //        auto id            = TokenId<K>(index);
    //        result.at(id).kind = enum_serde<K>::from_string(
    //                                 it["kind"].as<QString>())
    //                                 .value();

    //        if (it["str"]) {
    //            QString str = it["str"].as<QString>();
    //            buf += str;
    //            result.at(id).text = QStringView(data + start,
    //            str.size());
    //        }

    //        ++index;
    //    }

    return result;
}
