#pragma once

#include <unordered_set>

#include <yaml-cpp/yaml.h>
#include <lexbase/Node.hpp>
#include <lexbase/Token.hpp>
#include <lexbase/AstSpec.hpp>
#include <hstd/stdlib/algorithms.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;


template <typename N, typename K>
YAML::Node yamlRepr(NodeAdapter<N, K> node) {
    YAML::Node result;
    auto       g   = node.group;
    result["kind"] = to_string(node.get().kind);
    result["idx"]  = to_string(node.id.getIndex());
    if (node.get().isTerminal()) {
        if (g->hasData(node.id)) {
            result["str"] = g->strVal(node.id).toBase();
        }
        TokenId<K>      tokenId = g->at(node.id).getToken();
        Token<K> const& token   = g->tokens->at(tokenId);
        result["tok"]           = to_string(token.kind);
        result["tok_idx"]       = to_string(tokenId.getIndex());
        result.SetStyle(YAML::EmitterStyle::Flow);
    } else {
        for (NodeAdapter<N, K> const& sub : node.items()) {
            result["sub"].push_back(yamlRepr(sub));
        }
    }
    return result;
}


template <typename N, typename K>
json jsonRepr(
    CR<astspec::AstSpec<NodeAdapter<N, K>, N>> spec,
    NodeAdapter<N, K>                          node) {
    json result;
    auto g         = node.group;
    result["kind"] = to_string(node.get().kind);
    result["idx"]  = to_string(node.id.getIndex());
    if (node.get().isTerminal()) {
        if (g->hasData(node.id)) {
            result["str"] = g->strVal(node.id).toBase();
        }
        TokenId<K>      tokenId = g->at(node.id).getToken();
        Token<K> const& token   = g->tokens->at(tokenId);
        result["tok"]           = to_string(token.kind);
        result["tok_idx"]       = to_string(tokenId.getIndex());
    } else {
        Vec<Pair<Str, Slice<int>>> expanded = spec.resolveNodeFields(
            node.get().kind, node.size());

        json subnodes = json::object();
        for (const auto& [name, range] : expanded) {
            json items = json::array();
            for (int idx : range) {
                items.push_back(jsonRepr(spec, node.at(idx)));
            }
            subnodes[name.toBase()] = items;
        }
        result["subnodes"] = subnodes;
    }
    return result;
}

template <typename N, typename K>
YAML::Node yamlRepr(
    CR<astspec::AstSpec<NodeAdapter<N, K>, N>> spec,
    NodeAdapter<N, K>                          node) {
    YAML::Node result;
    auto       g   = node.group;
    result["kind"] = to_string(node.get().kind);
    result["idx"]  = to_string(node.id.getIndex());
    if (node.get().isTerminal()) {
        if (g->hasData(node.id)) {
            result["str"] = g->strVal(node.id).toBase();
        }
        TokenId<K>      tokenId = g->at(node.id).getToken();
        Token<K> const& token   = g->tokens->at(tokenId);
        result["tok"]           = to_string(token.kind);
        result["tok_idx"]       = to_string(tokenId.getIndex());
        result.SetStyle(YAML::EmitterStyle::Flow);
    } else {
        Vec<Pair<Str, Slice<int>>> expanded = spec.resolveNodeFields(
            node.get().kind, node.size());

        for (const auto& [name, range] : expanded) {
            for (int idx : range) {
                result[name.toBase()].push_back(
                    yamlRepr(spec, node.at(idx)));
            }
        }
    }
    return result;
}

template <typename N, typename K>
NodeTree<N, K> fromHomogeneous(CR<YAML::Node> node) {
    Opt<N> kind = string_to_enum<N>(node["kind"].as<std::string>());
    if (node["subnodes"]) {
        Vec<NodeTree<N, K>> subnodes;
        for (const auto& it : node["subnodes"]) {
            subnodes.push_back(fromHomogeneous<N, K>(it));
        }
        return NodeTree<N, K>(kind.value(), subnodes);
    } else {
        std::cout << node << std::endl;
        typename NodeTree<N, K>::TreeToken token = {
            .index = node["tok_idx"].as<int>(),
            .str   = node["str"] ? Opt<Str>(node["str"].as<std::string>())
                                 : Opt<Str>(std::nullopt),
            .kind  = string_to_enum<K>(node["tok"].as<std::string>())
                        .value()};

        return NodeTree<N, K>(kind.value(), token);
    }
}


template <typename K>
TokenGroup<K> fromFlatTokens(CR<YAML::Node> node, Str& buf) {
    TokenGroup<K> result;
    result.tokens.resize(node.size());
    int index = 0;
    for (const auto& it : node) {
        auto start         = buf.size();
        auto id            = TokenId<K>(index);
        result.at(id).kind = string_to_enum<K>(
                                 it["kind"].as<std::string>())
                                 .value();

        if (it["str"]) {
            std::string str = it["str"].as<std::string>();
            buf += str;
            result.at(id).text = std::string_view(
                buf.data() + start, str.size());
        }

        ++index;
    }

    return result;
}

template <typename N, typename K>
NodeGroup<N, K> fromFlatNodes(CR<YAML::Node> node) {
    NodeGroup<N, K> result;
    result.nodes.resize(node.size(), Node(low<N>(), TokenId<K>::Nil()));
    int index = 0;
    for (const auto& it : node) {
        N kind = string_to_enum<N>(it["kind"].as<std::string>()).value();
        if (it["extent"]) {
            result.at(NodeId<N, K>(index)) = Node<N, K>(
                kind, it["extent"].as<int>());
        } else {
            result.at(NodeId<N, K>(index)) = Node<N, K>(
                kind, TokenId<K>(it["tok_idx"].as<int>()));
        }
        ++index;
    }

    return result;
}

template <typename N, typename K>
YAML::Node yamlRepr(CR<NodeGroup<N, K>> group, bool withStrings = true) {
    YAML::Node out;
    for (const auto& [id, node] : group.nodes.pairs()) {
        YAML::Node item;
        item["kind"] = to_string(node->kind);
        if (node->isTerminal()) {
            TokenId<K> tokenId = node->getToken();
            item["tok_idx"]    = tokenId.getIndex();
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


template <typename N, typename K>
json jsonRepr(CR<NodeGroup<N, K>> group, bool withStrings = true) {
    json out = json::array();
    for (const auto& [id, node] : group.nodes.pairs()) {
        json item;
        item["kind"] = to_string(node->kind);
        if (node->isTerminal()) {
            TokenId<K> tokenId = node->getToken();
            item["tok_idx"]    = tokenId.getIndex();
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


template <typename K>
YAML::Node yamlRepr(CR<TokenGroup<K>> group) {
    YAML::Node out;
    for (const auto& [id, token] : group.tokens.pairs()) {
        YAML::Node item;
        item["idx"]  = id.getIndex();
        item["kind"] = to_string(token->kind);
        if (token->hasData()) {
            item["str"] = token->strVal().toBase();
        }
        item.SetStyle(YAML::EmitterStyle::Flow);
        out.push_back(item);
    }
    return out;
}

template <typename K>
json jsonRepr(CR<TokenGroup<K>> group) {
    json out = json::array();
    for (const auto& [id, token] : group.tokens.pairs()) {
        json item;
        item["idx"]  = id.getIndex();
        item["kind"] = to_string(token->kind);
        if (token->hasData()) {
            item["str"] = token->strVal().toBase();
        }
        out.push_back(item);
    }
    return out;
}
