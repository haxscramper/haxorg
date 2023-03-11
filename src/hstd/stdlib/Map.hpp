#pragma once

#include <unordered_map>
#include <map>

#include <hstd/system/generator.hpp>
#include <hstd/system/all.hpp>

template <typename Map, typename K, typename V>
struct MapBase : public CRTP_this_method<Map> {
    using CRTP_this_method<Map>::_this;
    inline bool contains(CR<K> key) const {
        return _this()->count(key) != 0;
    }

    generator<K> keys() const {
        for (const auto& [key, value] : *_this()) {
            co_yield key;
        }
    }
};

template <typename K, typename V>
struct UnorderedMap
    : public std::unordered_map<K, V>
    , public MapBase<UnorderedMap<K, V>, K, V> {
    using Base = std::unordered_map<K, V>;
    using API  = MapBase<UnorderedMap<K, V>, K, V>;
    using API::contains;
    using API::keys;
    using Base::Base;
    using Base::begin;
    using Base::end;
};


template <typename K, typename V>
struct SortedMap
    : public std::map<K, V>
    , public MapBase<SortedMap<K, V>, K, V> {
    using Base = std::map<K, V>;
    using API  = MapBase<SortedMap<K, V>, K, V>;
    using API::contains;
    using API::keys;
    using Base::Base;
};

template <typename K, typename V>
QTextStream& operator<<(QTextStream& os, UnorderedMap<K, V> const& map) {
    os << "{";
    bool first = true;
    for (const auto& [key, value] : map) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << key << ": " << value;
    }
    os << "}";
    return os;
}
