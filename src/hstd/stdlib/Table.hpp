#pragma once

#include <unordered_map>

template <
    template <typename, typename>
    typename TableType,
    typename K,
    typename V>
struct TableBase : public TableType<K, V> {};

template <typename K, typename V>
struct UnorderedMapAdaptor : std::unordered_map<K, V> {};

template <typename K, typename V>
struct Table : TableBase<UnorderedMapAdaptor, K, V> {};
