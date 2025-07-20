#pragma once

#include <immer/vector.hpp>
#include <immer/vector_transient.hpp>
#include <immer/box.hpp>
#include <immer/map.hpp>
#include <immer/map_transient.hpp>
#include <immer/set.hpp>
#include <immer/set_transient.hpp>
#include <immer/flex_vector.hpp>
#include <immer/flex_vector_transient.hpp>
#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/reflection_visitor.hpp>
#include <haxorg/sem/SemOrgTypes.hpp>
#include <hstd/stdlib/Array.hpp>
#include <hstd/stdlib/ContainerAPI.hpp>


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


namespace hstd {
template <typename Derived, typename Container, typename ValueType>
struct SequentialImmerContainerAdapterBase
    : public SequentialContainerAdapterBase<
          Derived,
          Container,
          ValueType> {

    using container_type  = Container;
    using item_value_type = ValueType;
    using base_type       = SequentialContainerAdapterBase<
              Derived,
              Container,
              ValueType>;

    container_type const*                                    container;
    std::shared_ptr<typename container_type::transient_type> transient;

    SequentialImmerContainerAdapterBase(const container_type* container)
        : container{container} {}

    auto begin_impl() const { return container->begin(); }
    auto end_impl() const { return container->end(); }

    int size_impl() const { return static_cast<int>(container->size()); }

    void begin_insert_impl() {
        transient = std::make_unique<
            typename container_type::transient_type>(
            const_cast<container_type*>(container)->transient());
    }

    void end_insert_impl() {
        if (transient) {
            *const_cast<container_type*>(container) = transient
                                                          ->persistent();
            transient.reset();
        }
    }

    void clear_impl() {
        *const_cast<container_type*>(container) = container_type{};
    }

    template <typename F1, typename F2>
    void add_with_transient(
        const item_value_type& value,
        F1&&                   transient_op,
        F2&&                   persistent_op) {
        if (transient) {
            transient_op(transient.get(), value);
        } else {
            *const_cast<container_type*>(container) = persistent_op(
                std::move(*const_cast<container_type*>(container)), value);
        }
    }
};

template <typename T>
struct SequentialContainerAdapter<immer::set<T>>
    : public SequentialImmerContainerAdapterBase<
          SequentialContainerAdapter<immer::set<T>>,
          immer::set<T>,
          T> {
    using container_type  = immer::set<T>;
    using item_value_type = T;
    using base_type       = SequentialImmerContainerAdapterBase<
              SequentialContainerAdapter<immer::set<T>>,
              container_type,
              item_value_type>;

    SequentialContainerAdapter(const container_type* container)
        : base_type{container} {}

    void add_impl(const item_value_type& value) {
        this->add_with_transient(
            value,
            [](auto* trans, const auto& val) { trans->insert(val); },
            [](auto&& cont, const auto& val) {
                return std::move(cont).insert(val);
            });
    }
};

template <typename T>
struct SequentialContainerAdapter<immer::flex_vector<T>>
    : public SequentialImmerContainerAdapterBase<
          SequentialContainerAdapter<immer::flex_vector<T>>,
          immer::flex_vector<T>,
          T> {

    using container_type  = immer::flex_vector<T>;
    using item_value_type = T;
    using base_type       = SequentialImmerContainerAdapterBase<
              SequentialContainerAdapter<immer::flex_vector<T>>,
              container_type,
              item_value_type>;

    SequentialContainerAdapter(const container_type* container)
        : base_type{container} {}

    void add_impl(const item_value_type& value) {
        this->add_with_transient(
            value,
            [](auto* trans, const auto& val) { trans->push_back(val); },
            [](auto&& cont, const auto& val) {
                return std::move(cont).push_back(val);
            });
    }
};

template <typename T>
struct SequentialContainerAdapter<immer::vector<T>>
    : public SequentialImmerContainerAdapterBase<
          SequentialContainerAdapter<immer::vector<T>>,
          immer::vector<T>,
          T> {
    using container_type  = immer::vector<T>;
    using item_value_type = T;
    using base_type       = SequentialImmerContainerAdapterBase<
              SequentialContainerAdapter<immer::vector<T>>,
              container_type,
              item_value_type>;

    SequentialContainerAdapter(const container_type* container)
        : base_type{container} {}

    void add_impl(const item_value_type& value) {
        this->add_with_transient(
            value,
            [](auto* trans, const auto& val) { trans->push_back(val); },
            [](auto&& cont, const auto& val) {
                return std::move(cont).push_back(val);
            });
    }
};

template <typename K, typename V>
struct SequentialContainerAdapter<immer::map<K, V>>
    : public SequentialImmerContainerAdapterBase<
          SequentialContainerAdapter<immer::map<K, V>>,
          immer::map<K, V>,
          std::pair<K, V>> {
    using container_type  = immer::map<K, V>;
    using item_value_type = std::pair<K, V>;
    using base_type       = SequentialImmerContainerAdapterBase<
              SequentialContainerAdapter<immer::map<K, V>>,
              container_type,
              item_value_type>;

    SequentialContainerAdapter(const container_type* container)
        : base_type{container} {}

    void add_impl(const item_value_type& value) {
        this->add_with_transient(
            value,
            [](auto* trans, const auto& val) {
                trans->set(val.first, val.second);
            },
            [](auto&& cont, const auto& val) {
                return std::move(cont).set(val.first, val.second);
            });
    }
};

template <typename K, typename V>
struct SequentialContainerAdapter<ext::ImmMap<K, V>>
    : public SequentialImmerContainerAdapterBase<
          SequentialContainerAdapter<ext::ImmMap<K, V>>,
          ext::ImmMap<K, V>,
          std::pair<K, V>> {
    using container_type  = ext::ImmMap<K, V>;
    using item_value_type = std::pair<K, V>;
    using base_type       = SequentialImmerContainerAdapterBase<
              SequentialContainerAdapter<ext::ImmMap<K, V>>,
              container_type,
              item_value_type>;

    SequentialContainerAdapter(const container_type* container)
        : base_type{container} {}

    void add_impl(const item_value_type& value) {
        this->add_with_transient(
            value,
            [](auto* trans, const auto& val) {
                trans->set(val.first, val.second);
            },
            [](auto&& cont, const auto& val) {
                return std::move(cont).set(val.first, val.second);
            });
    }
};

template <typename K, typename V>
struct AssociativeContainerAdapter<ext::ImmMap<K, V>>
    : public AssociativeContainerAdapterBase<
          AssociativeContainerAdapter<ext::ImmMap<K, V>>,
          ext::ImmMap<K, V>,
          K,
          V>
    , public SequentialContainerAdapter<ext::ImmMap<K, V>> {
    using pair_key_type   = K;
    using pair_value_type = V;
    using container_type  = ext::ImmMap<K, V>;

    AssociativeContainerAdapter(const container_type* container)
        : SequentialContainerAdapter<ext::ImmMap<K, V>>{container} {}

    bool contains_impl(pair_key_type const& key) const {
        return this->container->find(key) != nullptr;
    }

    void insert_or_assign_impl(
        pair_key_type const&   key,
        pair_value_type const& value) {
        if (this->transient) {
            this->transient->set(key, value);
        } else {
            *const_cast<container_type*>(this->container) = //
                const_cast<container_type*>(this->container)
                    ->set(key, value);
        }
    }
};

template <typename K, typename V>
struct AssociativeContainerAdapter<immer::map<K, V>>
    : public AssociativeContainerAdapterBase<
          AssociativeContainerAdapter<immer::map<K, V>>,
          immer::map<K, V>,
          K,
          V>
    , public SequentialContainerAdapter<immer::map<K, V>> {
    using pair_key_type   = K;
    using pair_value_type = V;
    using container_type  = immer::map<K, V>;

    AssociativeContainerAdapter(const container_type* container)
        : SequentialContainerAdapter<immer::map<K, V>>{container} {}

    bool contains_impl(pair_key_type const& key) const {
        return this->container->find(key) != nullptr;
    }

    void insert_or_assign_impl(
        pair_key_type const&   key,
        pair_value_type const& value) {
        if (this->transient) {
            this->transient->set(key, value);
        } else {
            *const_cast<container_type*>(this->container) = //
                const_cast<container_type*>(this->container)
                    ->set(key, value);
        }
    }
};

} // namespace hstd
