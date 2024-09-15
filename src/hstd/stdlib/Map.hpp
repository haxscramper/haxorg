#pragma once

#include <unordered_map>
#include <map>
#include <optional>

#include <hstd/system/Formatter.hpp>
#include <hstd/system/generator.hpp>
#include <hstd/system/all.hpp>
#include <hstd/stdlib/Vec.hpp>

template <typename Map, typename K, typename V>
struct MapBase : public CRTP_this_method<Map> {
    using CRTP_this_method<Map>::_this;
    inline bool contains(CR<K> key) const {
        return _this()->count(key) != 0;
    }

    std::optional<V> get(K const& key) const {
        if (_this()->contains(key)) {
            return _this()->at(key);
        } else {
            return std::nullopt;
        }
    }

    Vec<K> keys() const {
        Vec<K> result;
        for (const auto& [key, value] : *_this()) {
            result.push_back(key);
        }

        return result;
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


template <typename K, typename V, typename _Compare = std::less<K>>
struct SortedMap
    : public std::map<K, V, _Compare>
    , public MapBase<SortedMap<K, V, _Compare>, K, V> {
    using Base = std::map<K, V, _Compare>;
    using API  = MapBase<SortedMap<K, V, _Compare>, K, V>;
    inline bool contains(CR<K> key) const {
        return Base::find(key) != Base::end();
    }

    using API::get;
    using API::keys;
    using Base::Base;
    using Base::end;
    using Base::operator[];
};


template <typename K, typename V, typename Type>
struct std_kv_tuple_iterator_formatter : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(Type const& p, FormatContext& ctx)
        const {
        fmt_ctx("{", ctx);
        bool first = true;
        for (const auto& [key, value] : p) {
            if (!first) { fmt_ctx(", ", ctx); }
            first = false;
            fmt_ctx(key, ctx);
            fmt_ctx(": ", ctx);
            fmt_ctx(value, ctx);
        }
        return fmt_ctx("}", ctx);
    }
};

template <typename K, typename V>
struct std::formatter<std::unordered_map<K, V>>
    : std_kv_tuple_iterator_formatter<K, V, std::unordered_map<K, V>> {};

template <typename K, typename V>
struct std::formatter<std::map<K, V>>
    : std_kv_tuple_iterator_formatter<K, V, std::map<K, V>> {};


template <typename K, typename V>
struct std::formatter<UnorderedMap<K, V>>
    : std_kv_tuple_iterator_formatter<K, V, UnorderedMap<K, V>> {};

template <typename K, typename V, typename _Compare>
struct std::formatter<SortedMap<K, V, _Compare>>
    : std_kv_tuple_iterator_formatter<K, V, SortedMap<K, V, _Compare>> {};

template <typename K, typename V>
struct value_metadata<UnorderedMap<K, V>> {
    static bool isEmpty(UnorderedMap<K, V> const& value) {
        return value.empty();
    }
};
