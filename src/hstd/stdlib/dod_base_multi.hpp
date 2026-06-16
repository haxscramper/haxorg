#pragma once

#include <hstd/stdlib/dod_base_intern.hpp>

namespace hstd::dod {


/// \brief Wrapper for multiple different stores
///
/// Collecting of several different storage types, used as a boilerplate
/// reduction helper - instead of wrapping around multiple `Store<Id, Val>`
/// fields in the class, adding helper methods to access them via add/at
/// you can write a `MultiStore<>` and list all the required data in the
/// template parameter list. Supports both interned and non-interned
/// storage solutions.
template <typename... Args>
struct MultiStore {
    inline MultiStore() {}

    //// \brief Get reference to the store that is associated with
    /// Val
    template <typename Val>
        requires is_in_pack_v<Store<id_type_t<Val>, Val>, Args...>
    auto store() -> Store<id_type_t<Val>, Val>& {
        return std::get<Store<id_type_t<Val>, Val>>(stores);
    }

    /// \brief An overload for the interned store case
    template <typename Val>
        requires is_in_pack_v<InternStore<id_type_t<Val>, Val>, Args...>
    auto store() -> InternStore<id_type_t<Val>, Val>& {
        return std::get<InternStore<id_type_t<Val>, Val>>(stores);
    }

    /// \brief Get reference to the store that is associated with
    /// Val
    template <typename Val>
        requires is_in_pack_v<Store<id_type_t<Val>, Val>, Args...>
    auto store() const -> const Store<id_type_t<Val>, Val>& {
        return std::get<Store<id_type_t<Val>, Val>>(stores);
    }

    /// \brief An overload for the interned store case
    template <typename Val>
        requires is_in_pack_v<InternStore<id_type_t<Val>, Val>, Args...>
    auto store() const -> const InternStore<id_type_t<Val>, Val>& {
        return std::get<InternStore<id_type_t<Val>, Val>>(stores);
    }

    /// Push value on one of the stores, inferring which one based on the
    /// ID
    template <typename Val>
    [[nodiscard]] auto add(Val const& t) -> id_type_t<Val> {
        return store<Val>().add(t);
    }

    /// Get value at one of the associated stores, inferring which one
    /// based on the value type of the ID
    template <dod::IsIdType Id>
    auto at(Id id) -> value_type_t<Id>& {
        return store<value_type_t<Id>>().at(id);
    }

    /// \copydoc Store::at
    template <dod::IsIdType Id>
    auto at(Id id) const -> value_type_t<Id> const& {
        return store<value_type_t<Id>>().at(id);
    }

    /// \copydoc Store::insert
    template <typename Id, typename Val>
    void insert(Id id, Val const& val) {
        return store<Val>().insert(id, val);
    }

  private:
    std::tuple<Args...> stores; /// List of associated storage contianers
};

} // namespace hstd::dod
