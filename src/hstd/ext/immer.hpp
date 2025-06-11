#pragma once

#include <immer/vector.hpp>
#include <immer/box.hpp>
#include <immer/map.hpp>
#include <immer/set.hpp>
#include <immer/flex_vector.hpp>
#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/reflection_visitor.hpp>
#include <haxorg/sem/SemOrgTypes.hpp>
#include <hstd/stdlib/Array.hpp>


namespace hstd::ext {
template <typename T>
using ImmVec = immer::flex_vector<T>;

template <typename T>
using ImmBox = immer::box<T>;
} // namespace hstd::ext

template <typename T>
struct std::hash<hstd::ext::ImmVec<T>>
    : hstd::std_indexable_hash<hstd::ext::ImmVec<T>> {};

template <typename T>
struct std::hash<immer::vector<T>>
    : hstd::std_indexable_hash<immer::vector<T>> {};

template <typename T>
struct std::formatter<immer::vector<T>>
    : hstd::std_item_iterator_formatter<T, immer::vector<T>> {};

template <typename T>
struct std::formatter<hstd::ext::ImmVec<T>>
    : hstd::std_item_iterator_formatter<T, hstd::ext::ImmVec<T>> {};

namespace hstd::ext {
template <typename K, typename V>
struct ImmMap : immer::map<K, V> {
    using base = immer::map<K, V>;
    using base::at;
    using base::base;
    using base::find;

    ImmMap(base const& val) : base{val} {}

    Opt<V> get(K const& key) const {
        if (auto val = find(key)) {
            return *val;
        } else {
            return std::nullopt;
        }
    }

    bool contains(K const& key) const { return find(key) != nullptr; }

    Vec<K> keys() const {
        Vec<K> result;
        for (const auto& [key, value] : *this) { result.push_back(key); }
        return result;
    }
};

template <typename T>
using ImmSet = immer::set<T>;
} // namespace hstd::ext
