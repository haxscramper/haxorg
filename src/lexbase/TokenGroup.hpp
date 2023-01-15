#pragma once

#include <lexbase/Token.hpp>
#include <hstd/stdlib/dod_base.hpp>

template <typename K>
struct TokenGroup {
    dod::Store<TokenId<K>, Token<K>> tokens;

    // WIP IMPLEMENT use group mask to construct full ID that can be used
    // to refer back to the store.
    int group_mask = 0;

    TokenId<K> push(CR<Token<K>> tok) { return tokens.add(tok); }

    Vec<TokenId<K>> push(CR<Vec<Token<K>>> tok) {
        Vec<TokenId<K>> result;
        for (const auto& t : tok) {
            result.push_back(tokens.add(t));
        }
        return result;
    }

    Vec<TokenId<K>> push(CR<std::span<Token<K>>> tok) {
        Vec<TokenId<K>> result;
        for (const auto& t : tok) {
            result.push_back(tokens.add(t));
        }
        return result;
    }
};

template <typename K>
struct TokenStore {
    Vec<TokenGroup<K>> groups;
};
