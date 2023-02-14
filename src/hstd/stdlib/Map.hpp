#pragma once

#include <unordered_map>
#include <hstd/system/generator.hpp>
#include <hstd/system/basic_typedefs.hpp>

template <
    template <typename, typename>
    typename MapType,
    typename K,
    typename V>
struct MapBase : public MapType<K, V> {
    MapBase() {}
    using Base = MapType<K, V>;

    inline V&   operator[](CR<K> key) { return Base::operator[](key); }
    inline bool contains(CR<K> key) const { return Base::count(key) != 0; }
    generator<K> keys() const {
        for (const auto& [key, value] : *this) {
            co_yield key;
        }
    }
};

template <typename K, typename V>
struct UnorderedMapAdaptor : public std::unordered_map<K, V> {
    UnorderedMapAdaptor() : std::unordered_map<K, V>() {}
};

template <typename K, typename V>
struct UnorderedMap : public MapBase<UnorderedMapAdaptor, K, V> {};
