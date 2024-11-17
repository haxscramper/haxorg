#pragma once
#include <haxorg/sem/ImmOrg.hpp>

template <typename T>
std::size_t get_std_hash(T const& it) {
    return std::hash<T>{}(it);
}

template <typename T>
struct std::hash<ImmBox<T>> {
    std::size_t operator()(ImmBox<T> const& it) const noexcept {
        return std::hash<T>{}(it);
    }
};

template <typename K, typename V>
struct std::hash<ImmMap<K, V>> {
    std::size_t operator()(ImmMap<K, V> const& it) const noexcept {
        std::size_t result = 0;
        Vec<K>      keys;
        for (auto const& [key, _] : it) { keys.push_back(key); }
        rs::sort(keys);
        for (auto const& key : keys) {
            boost::hash_combine(result, get_std_hash<K>(key));
            boost::hash_combine(result, get_std_hash<V>(it[key]));
        }
        return result;
    }
};
