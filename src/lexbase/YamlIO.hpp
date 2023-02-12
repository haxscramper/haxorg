#pragma once

#include <unordered_set>

#include <yaml-cpp/yaml.h>
#include <lexbase/Node.hpp>
#include <lexbase/Token.hpp>
#include <lexbase/AstSpec.hpp>

template <typename T>
std::unordered_set<T> set_difference(
    std::unordered_set<T>     lhs,
    CR<std::unordered_set<T>> rhs) {
    for (const auto& it : rhs) {
        lhs.erase(it);
    }
    return lhs;
}

template <typename T>
std::ostream& operator<<(
    std::ostream&                os,
    std::unordered_set<T> const& value) {
    return os << "{" << join(os, ", ", value) << "}";
}

template <typename T>
std::string to_string(std::unordered_set<T> const& value) {
    std::stringstream os;
    os << value;
    return os.str();
}

template <typename N, typename K>
YAML::Node yamlRepr(NodeAdapter<N, K> node) {
    YAML::Node result;
    auto       g   = node.group;
    result["kind"] = to_string(node.get().kind);
    result["idx"]  = to_string(node.id.getIndex());
    if (node.get().isTerminal()) {
        result["str"]           = g->strVal(node.id).toBase();
        TokenId<K>      tokenId = g->at(node.id).getToken();
        Token<K> const& token   = g->tokens->at(tokenId);
        result["tok"]           = to_string(token.kind);
        result["tok_idx"]       = to_string(tokenId.getIndex());
    } else {
        for (NodeAdapter<N, K> const& sub : node.items()) {
            result["sub"].push_back(yamlRepr(sub));
        }
    }
    return result;
}


template <typename A, typename B>
generator<Pair<typename A::value_type const*, typename B::value_type const*>> carthesian(
    CR<A> lhs,
    CR<B> rhs) {
    for (const auto& lhsIt : lhs) {
        for (const auto& rhsIt : rhs) {
            co_yield {&lhsIt, &rhsIt};
        }
    }
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
        result["str"]           = g->strVal(node.id).toBase();
        TokenId<K>      tokenId = g->at(node.id).getToken();
        Token<K> const& token   = g->tokens->at(tokenId);
        result["tok"]           = to_string(token.kind);
        result["tok_idx"]       = to_string(tokenId.getIndex());
    } else {
        Table<Str, astspec::AstRange> fields = spec.nodeFields(
            node.get().kind);
        int size = node.size();
        if (size == 0 && fields.size() == 0) {
            return result;
        }

        Vec<Pair<Str, Slice<int>>> expanded;

        for (const auto& [name, range] : fields) {
            auto slice = range.toSlice(size);
            if (slice.has_value()) {
                expanded.push_back({name, slice.value()});
            }
        }

        expanded.sort([](CR<Pair<Str, Slice<int>>> lhs,
                         CR<Pair<Str, Slice<int>>> rhs) {
            return lhs.first < rhs.first;
        });

        for (const auto& [lhs, rhs] : carthesian(expanded, expanded)) {
            if (lhs == rhs) {
                continue;
            }

            auto overlap = lhs->second.overlap(rhs->second);
            if (overlap.has_value()) {
                throw astspec::FieldAccessError(
                    "Cannot access field with overlapping ranges '$#' and "
                    "'$#' had ast ranges specified as '$#' and '$#' "
                    "respectively which resolved to $# and $# for node of "
                    "size $# kind $#"
                    % to_string_vec(
                        lhs->first,
                        rhs->first,
                        fields[lhs->first],
                        fields[rhs->first],
                        lhs->second,
                        rhs->second,
                        size,
                        to_string(node.get().kind)));
            }
        }

        int                     max = expanded.back().second.last;
        std::unordered_set<int> visited;
        for (const auto& [_, range] : expanded) {
            max = std::max(max, range.last);
            std::cout << range << "\n";
            for (const auto& value : range) {
                visited.insert(value);
            }
        }
        std::unordered_set<int> all;
        for (int i = 0; i < max; ++i) {
            all.insert(i);
        }
        auto diff = set_difference(all, visited);
        if (!diff.empty()) {
            throw astspec::FieldAccessError(
                "Indices missing from the field description $# are not "
                "covered in spec for node $#"
                % to_string_vec(
                    to_string(diff), to_string(node.get().kind)));
        }

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
YAML::Node yamlRepr(CR<NodeGroup<N, K>> group, bool withStrings = true) {
    YAML::Node out;
    for (const auto& [id, node] : group.nodes.pairs()) {
        YAML::Node item;
        item["kind"] = to_string(node->kind);
        if (node->isTerminal()) {
            TokenId<K> tokenId = node->getToken();
            item["tok_idx"]    = tokenId.getIndex();
            if (withStrings) {
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
        item["str"]  = token->strVal().toBase();
        out.push_back(item);
    }
    return out;
}
