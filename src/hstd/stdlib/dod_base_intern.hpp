#pragma once

#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/dod_base.hpp>


namespace hstd::dod {
/// \brief Stores values with with automatic deduplication
///
/// Interned data store - for values that can be hashed for deduplication.
/// Provided type must be usable as a key for unordered associative
/// continer.
template <IsIdType Id, typename Val>
struct InternStore {
    InternStore() = default;

    /// \brief Reverse ID mapping store
    hstd::UnorderedMap<Val, Id> id_map;
    /// \brief Underlying store for values
    dod::Store<Id, Val> content;

    DESC_FIELDS(InternStore, (id_map, content))

    /// Add value to the store - if the value is already contained can
    /// return previous ID
    [[nodiscard]] auto add(
        Val const&                               in,
        std::optional<typename Id::id_mask_type> mask = std::nullopt) -> Id {
        auto found = id_map.find(in);
        if (found != id_map.end()) {
            LOGIC_ASSERTION_CHECK(
                !found->second.isNil(), "Implementation error, added ID cannot be nil");
            return found->second;
        } else {
            auto result = mask.has_value() ? content.add(in, mask.value())
                                           : content.add(in);
            id_map.insert({in, result});
            LOGIC_ASSERTION_CHECK(
                !result.isNil(), "Implementation error, added ID cannot be nil");
            return result;
        }
    }

    /// \brief Value has already been interned in the store
    auto contains(Val const& in) const -> bool { return id_map.find(in) != id_map.end(); }

    bool empty() const { return size() == 0; }

    /// \brief Number of elements
    auto size() const -> int { return content.size(); }
    /// \brief Get mutable reference at the content pointed at by the ID
    auto at(Id id) -> Val& { return content.at(id); }
    /// \brief Get immutable references at the content pointed at by the ID
    auto at(Id id) const -> Val const& { return content.at(id); }

    /// \brief Insert new value to the store if it has not already been
    /// interned
    ///
    /// \copydoc Store::insert
    void insert(Id id, Val const& value) {
        if (!contains(value)) {
            LOGIC_ASSERTION_CHECK(
                !id.isNil(), "cannot use nil ID for interned store key");
            content.insert(id, value);
            id_map.insert({value, id});
        }
    }

    /// \brief Return generator of the stored indices and values
    auto pairs() const -> generator<std::pair<Id, CP<Val>>> { return content.pairs(); }

    /// \copydoc Store::items
    auto items() const -> generator<CP<Val>> { return content.items(); }
    /// \copydoc Store::items
    auto items() -> generator<Ptr<Val>> { return content.items(); }
};

} // namespace hstd::dod
