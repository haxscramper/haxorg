#pragma once

#include <unordered_map>
#include <map>
#include <optional>

#include <hstd/system/generator.hpp>
#include <hstd/system/all.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/ContainerAPI.hpp>
#include <hstd/stdlib/Formatter.hpp>

namespace hstd {

template <typename Map, typename K, typename V>
struct MapBase : public CRTP_this_method<Map> {
    using CRTP_this_method<Map>::_this;
    inline bool contains(CR<K> key) const {
        return _this()->count(key) != 0;
    }

    V& get_or_insert(K const& key, V const& fallback) {
        if (!_this()->contains(key)) {
            _this()->insert_or_assign(key, fallback);
        }
        return _this()->at(key);
    }

    std::optional<V> pop_opt(K const& key) {
        auto res = get(key);
        if (res) { _this()->erase(key); }
        return res;
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

} // namespace hstd

template <typename K, typename V>
struct std::formatter<std::unordered_map<K, V>>
    : hstd::
          std_kv_tuple_iterator_formatter<K, V, std::unordered_map<K, V>> {
};

template <typename K, typename V>
struct std::formatter<std::map<K, V>>
    : hstd::std_kv_tuple_iterator_formatter<K, V, std::map<K, V>> {};


template <typename K, typename V>
struct std::formatter<hstd::UnorderedMap<K, V>>
    : hstd::
          std_kv_tuple_iterator_formatter<K, V, hstd::UnorderedMap<K, V>> {
};

template <typename K, typename V, typename _Compare>
struct std::formatter<hstd::SortedMap<K, V, _Compare>>
    : hstd::std_kv_tuple_iterator_formatter<
          K,
          V,
          hstd::SortedMap<K, V, _Compare>> {};

namespace hstd {
template <typename K, typename V>
struct value_metadata<hstd::UnorderedMap<K, V>> {
    static bool isEmpty(UnorderedMap<K, V> const& value) {
        return value.empty();
    }

    static std::string typeName() {
        return std::string{"UnorderedMap<"} + value_metadata<K>::typeName()
             + std::string{", "} + value_metadata<V>::typeName()
             + std::string{">"};
    }
};

template <typename K, typename V, typename Container>
class SequentialKvPairContainerAdapter
    : public SequentialContainerAdapterBase<
          SequentialContainerAdapter<Container>,
          Container,
          std::pair<K, V>> {
  public:
    using container_type  = Container;
    using item_value_type = std::pair<K, V>;
    using base_type       = SequentialContainerAdapterBase<
              SequentialContainerAdapter<Container>,
              container_type,
              item_value_type>;

    container_type const* container;

    SequentialKvPairContainerAdapter(const container_type* container)
        : container{container} {}

    auto begin_impl() const { return container->begin(); }
    auto end_impl() const { return container->end(); }

    void add_impl(const item_value_type& value) {
        const_cast<container_type*>(container)->insert(value);
    }

    int size_impl() const { return static_cast<int>(container->size()); }

    void begin_insert_impl() {}
    void end_insert_impl() {}
    void clear_impl() { const_cast<container_type*>(container)->clear(); }
    void reserve_impl(int size) {
        const_cast<container_type*>(container)->reserve(size);
    }
};


template <typename K, typename V>
struct SequentialContainerAdapter<std::unordered_map<K, V>>
    : hstd::SequentialKvPairContainerAdapter<
          K,
          V,
          std::unordered_map<K, V>> {};

template <typename K, typename V>
struct SequentialContainerAdapter<std::map<K, V>>
    : hstd::SequentialKvPairContainerAdapter<K, V, std::map<K, V>> {};


template <typename K, typename V>
struct SequentialContainerAdapter<hstd::UnorderedMap<K, V>>
    : hstd::SequentialKvPairContainerAdapter<
          K,
          V,
          hstd::UnorderedMap<K, V>> {};

template <typename K, typename V, typename _Compare>
struct SequentialContainerAdapter<hstd::SortedMap<K, V, _Compare>>
    : hstd::SequentialKvPairContainerAdapter<
          K,
          V,
          hstd::SortedMap<K, V, _Compare>> {};


template <typename K, typename V, typename Container>
struct AssociativeKvPairContainerAdapter
    : public AssociativeContainerAdapterBase<
          AssociativeContainerAdapter<Container>,
          Container,
          K,
          V>
    , public SequentialContainerAdapter<Container> {
    using pair_key_type   = K;
    using pair_value_type = V;
    using container_type  = Container;

    using assoc_base = AssociativeContainerAdapterBase<
        AssociativeContainerAdapter<Container>,
        Container,
        K,
        V>;

    AssociativeKvPairContainerAdapter(const container_type* container)
        : SequentialContainerAdapter<Container>{container} {}

    void insert_or_assign_impl(
        pair_key_type const&   key,
        pair_value_type const& value) {
        const_cast<container_type*>(this->container)
            ->insert_or_assign(key, value);
    }

    bool contains_impl(K const& key) const {
        return this->container->contains(key);
    }

    V const& at_impl(K const& key) const {
        return this->container->at(key);
    }
};

template <typename K, typename V>
struct AssociativeContainerAdapter<std::unordered_map<K, V>>
    : hstd::AssociativeKvPairContainerAdapter<
          K,
          V,
          std::unordered_map<K, V>> {
    using pair_key_type   = K;
    using pair_value_type = V;
};

template <typename K, typename V>
struct AssociativeContainerAdapter<std::map<K, V>>
    : hstd::AssociativeKvPairContainerAdapter<K, V, std::map<K, V>> {
    using pair_key_type   = K;
    using pair_value_type = V;
};


template <typename K, typename V>
struct AssociativeContainerAdapter<hstd::UnorderedMap<K, V>>
    : hstd::AssociativeKvPairContainerAdapter<
          K,
          V,
          hstd::UnorderedMap<K, V>> {
    using pair_key_type   = K;
    using pair_value_type = V;
};

template <typename K, typename V, typename _Compare>
struct AssociativeContainerAdapter<hstd::SortedMap<K, V, _Compare>>
    : hstd::AssociativeKvPairContainerAdapter<
          K,
          V,
          hstd::SortedMap<K, V, _Compare>> {
    using pair_key_type   = K;
    using pair_value_type = V;
};

template <typename K, typename V, typename Type>
struct std_kv_tuple_iterator_hash {
    std::size_t operator()(Type const& it) const noexcept {
        std::size_t result = 0;

        // sort key-value pairs to stabilize the hashing outcome -- if the
        // unordered map has a different order of iteration it still should
        // have the same final hash as long as the values in the map are
        // the same.
        std::vector<std::size_t> hash_pairs;
        for (auto const& [key, value] : it) {
            std::size_t pair = 0;
            hstd::hax_hash_combine(pair, key);
            hstd::hax_hash_combine(pair, value);
            hash_pairs.push_back(pair);
        }
        std::sort(hash_pairs.begin(), hash_pairs.end());
        for (auto const& it : hash_pairs) {
            hstd::hax_hash_combine(result, it);
        }
        return result;
    }
};
} // namespace hstd

template <typename K, typename V>
struct std::hash<hstd::UnorderedMap<K, V>>
    : hstd::std_kv_tuple_iterator_hash<K, V, hstd::UnorderedMap<K, V>> {};

template <typename K, typename V>
struct std::hash<hstd::SortedMap<K, V>>
    : hstd::std_kv_tuple_iterator_hash<K, V, hstd::SortedMap<K, V>> {};
