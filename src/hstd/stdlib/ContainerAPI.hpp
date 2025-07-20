#pragma once
#include <hstd/system/aux_utils.hpp>

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

    auto insert_or_assign(KeyType const& key, ValueType const& value) {
        _this()->insert_or_assign_impl(key, value);
    }

    bool contains(KeyType const& key) const {
        _this()->contains_impl(key);
    }
};

template <typename T>
class SequentialContainerAdapter {};

template <typename T>
class AssociativeContainerAdapter {};


template <typename T>
concept HasSequentialContainerAdapter = requires {
    typename SequentialContainerAdapter<T>;
    requires std::is_base_of_v<
        SequentialContainerAdapterBase<
            SequentialContainerAdapter<T>,
            typename SequentialContainerAdapter<T>::container_type,
            typename SequentialContainerAdapter<T>::item_value_type>,
        SequentialContainerAdapter<T>>;
};
} // namespace hstd
