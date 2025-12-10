#pragma once
#include <haxorg/sem/ImmOrg.hpp>
#include <hstd/stdlib/Ranges.hpp>

template <typename T>
std::size_t get_std_hash(T const& it) {
    return std::hash<T>{}(it);
}

template <typename T>
struct std::hash<hstd::ext::ImmBox<T>> {
    std::size_t operator()(hstd::ext::ImmBox<T> const& it) const noexcept {
        return std::hash<T>{}(it);
    }
};

template <typename K, typename V>
struct std::hash<hstd::ext::ImmMap<K, V>> {
    std::size_t operator()(
        hstd::ext::ImmMap<K, V> const& it) const noexcept {
        std::size_t  result = 0;
        hstd::Vec<K> keys;
        for (auto const& [key, _] : it) { keys.push_back(key); }
        hstd::rs::sort(keys);
        for (auto const& key : keys) {
            hstd::hax_hash_combine(result, get_std_hash<K>(key));
            hstd::hax_hash_combine(result, get_std_hash<V>(it[key]));
        }
        return result;
    }
};
