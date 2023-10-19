#pragma once

#include <unordered_map>
#include <map>
#include <optional>

#include <hstd/system/generator.hpp>
#include <hstd/system/all.hpp>

template <typename Map, typename K, typename V>
struct MapBase : public CRTP_this_method<Map> {
    using CRTP_this_method<Map>::_this;
    inline bool contains(CR<K> key) const {
        return _this()->count(key) != 0;
    }

    std::optional<V> get(K const& key) const {
        if (contains(key)) {
            return _this()->at(key);
        } else {
            return std::nullopt;
        }
    }

    generator<K> keys() const {
        for (const auto& [key, value] : *_this()) {
            co_yield key;
        }
    }
};

template <typename K, typename V, typename Hash = std::hash<K>>
struct UnorderedMap
    : public std::unordered_map<K, V, Hash>
    , public MapBase<UnorderedMap<K, V>, K, V> {
    using Base = std::unordered_map<K, V, Hash>;
    using API  = MapBase<UnorderedMap<K, V>, K, V>;
    using API::contains;
    using API::get;
    using API::keys;
    using Base::Base;
    using Base::begin;
    using Base::end;
    using Base::operator[];
};


template <typename K, typename V>
struct SortedMap
    : public std::map<K, V>
    , public MapBase<SortedMap<K, V>, K, V> {
    using Base = std::map<K, V>;
    using API  = MapBase<SortedMap<K, V>, K, V>;
    using API::contains;
    using API::get;
    using API::keys;
    using Base::Base;
    using Base::operator[];
};


template <typename K, typename V>
struct std::formatter<UnorderedMap<K, V>> : std::formatter<std::string> {
    using FmtType = UnorderedMap<K, V>;
    template <typename FormatContext>
    FormatContext::iterator format(FmtType const& p, FormatContext& ctx)
        const {
        std::formatter<std::string> fmt;
        fmt.format("{", ctx);
        bool first = true;
        for (const auto& [key, value] : p) {
            if (!first) {
                fmt.format(", ", ctx);
            }
            first = false;
            fmt.format(key, ctx);
            fmt.format(": ", ctx);
            fmt.format(value, ctx);
        }
        return fmt.format("}", ctx);
    }
};
