#pragma once

#include <hstd/system/aux_templates.hpp>
#include <hstd/system/aux_utils.hpp>
#include <hstd/stdlib/Vec.hpp>

namespace hstd {
template <typename Derived, typename Container, typename ValueType>
struct SequentialContainerAdapterBase : CRTP_this_method<Derived> {
    using container_type = Container;
    using value_type     = ValueType;

    using CRTP_this_method<Derived>::_this;

    auto begin() const { return _this()->begin_impl(); }
    auto end() const { return _this()->end_impl(); }
    int  size() const { return _this()->size_impl(); }
    void add(const value_type& value) { _this()->add_impl(value); }
    void add(value_type&& value) { _this()->add_impl(value); }
    void begin_insert() { _this()->begin_insert_impl(); }
    void end_insert() { _this()->end_insert_impl(); }
    void clear() { _this()->clear_impl(); }
};

template <
    typename Derived,
    typename Container,
    typename KeyType,
    typename ValueType>
struct AssociativeContainerAdapterBase : CRTP_this_method<Derived> {
    using CRTP_this_method<Derived>::_this;

    void insert_or_assign(KeyType const& key, ValueType const& value) {
        _this()->insert_or_assign_impl(key, value);
    }

    bool contains(KeyType const& key) const {
        return _this()->contains_impl(key);
    }

    ValueType const& at(KeyType const& key) {
        return _this()->at_impl(key);
    }

    KeyType const& get_pair_key(
        std::pair<KeyType, ValueType> const& pair) const {
        return pair.first;
    }

    Vec<KeyType> keys() const {
        Vec<KeyType> result;
        for (auto it = _this()->begin(); it != _this()->end(); ++it) {
            result.push_back(_this()->get_pair_key(*it));
        }
        return result;
    }
};

template <typename T>
class SequentialContainerAdapter {};

template <typename T>
class AssociativeContainerAdapter {};


template <typename T>
concept HasSequentialContainerAdapter = requires {
    typename SequentialContainerAdapter<T>::item_value_type;
};

template <typename T>
concept HasAssociativeContainerAdapter = requires {
    typename AssociativeContainerAdapter<T>::item_value_type;
    typename AssociativeContainerAdapter<T>::pair_key_type;
    typename AssociativeContainerAdapter<T>::pair_value_type;
};


template <typename T>
class SequentialContainerAdapter<hstd::Vec<T>>
    : public SequentialContainerAdapterBase<
          SequentialContainerAdapter<hstd::Vec<T>>,
          hstd::Vec<T>,
          T> {
  public:
    using container_type  = hstd::Vec<T>;
    using item_value_type = T;

    container_type const* container = nullptr;

    SequentialContainerAdapter(const container_type* container)
        : container{container} {}

    auto begin_impl() const { return container->begin(); }
    auto end_impl() const { return container->end(); }

    void add_impl(const item_value_type& value) {
        const_cast<container_type*>(container)->push_back(value);
    }

    int size_impl() const { return static_cast<int>(container->size()); }

    void begin_insert_impl() {}
    void end_insert_impl() {}
    void clear_impl() { const_cast<container_type*>(container)->clear(); }
};

template <typename T, int Size>
class SequentialContainerAdapter<hstd::SmallVec<T, Size>>
    : public SequentialContainerAdapterBase<
          SequentialContainerAdapter<hstd::SmallVec<T, Size>>,
          hstd::SmallVec<T, Size>,
          T> {
  public:
    using container_type  = hstd::SmallVec<T, Size>;
    using item_value_type = T;

    container_type const* container = nullptr;

    SequentialContainerAdapter(const container_type* container)
        : container{container} {}

    auto begin_impl() const { return container->begin(); }
    auto end_impl() const { return container->end(); }

    void add_impl(const item_value_type& value) {
        const_cast<container_type*>(container)->push_back(value);
    }

    int size_impl() const { return static_cast<int>(container->size()); }

    void begin_insert_impl() {}
    void end_insert_impl() {}
    void clear_impl() { const_cast<container_type*>(container)->clear(); }
};

} // namespace hstd
