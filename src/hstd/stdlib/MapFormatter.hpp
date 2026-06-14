#pragma once

#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/Formatter.hpp>


template <typename K, typename V>
struct fmt::formatter<std::unordered_map<K, V>>
    : hstd::std_kv_tuple_iterator_formatter<K, V, std::unordered_map<K, V>> {};

template <typename K, typename V>
struct fmt::formatter<std::map<K, V>>
    : hstd::std_kv_tuple_iterator_formatter<K, V, std::map<K, V>> {};


template <typename K, typename V>
struct fmt::formatter<hstd::UnorderedMap<K, V>>
    : hstd::std_kv_tuple_iterator_formatter<K, V, hstd::UnorderedMap<K, V>> {};

template <typename K, typename V, typename _Compare>
struct fmt::formatter<hstd::SortedMap<K, V, _Compare>>
    : hstd::std_kv_tuple_iterator_formatter<K, V, hstd::SortedMap<K, V, _Compare>> {};
