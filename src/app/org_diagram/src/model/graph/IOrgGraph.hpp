#pragma once

#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/stdlib/dod_base.hpp>
#include <boost/serialization/strong_typedef.hpp>
#include <hstd/ext/bimap_wrap.hpp>
#include <hstd/ext/graphviz.hpp>
#include <hstd/stdlib/Set.hpp>
#include <hstd/stdlib/JsonSerde.hpp>

namespace hstd {
template <typename ID, typename T>
struct UnorderedStore {
    hstd::ext::Unordered1to1Bimap<ID, T> store;

    ID add(
        T const&                                 value,
        std::optional<typename ID::id_mask_type> mask = std::nullopt) {
        LOGIC_ASSERTION_CHECK_FMT(
            !store.contains_right(value),
            "Store already contains value {}",
            hstd::fmt1_maybe(value));

        int  current_size = size();
        auto result = mask.has_value()
                        ? ID::FromMaskedIdx(current_size, mask.value())
                        : ID::FromIndex(current_size);
        store.add_unique(result, value);
        return result;
    }

    void add_with_id(T const& value, ID const& result) {
        LOGIC_ASSERTION_CHECK_FMT(
            !store.contains_right(value),
            "Store already contains value {}",
            hstd::fmt1_maybe(value));

        store.add_unique(result, value);
    }

    hstd::Vec<ID> keys() const {
        hstd::Vec<ID> res;
        for (auto const& it : store.get_map()) { res.push_back(it.first); }
        return res;
    }

    ID del(T const& value) {
        ID res = store.at_left(value);
        store.erase_right(value);
        return res;
    }

    T const&  at(ID const& id) const { return store.at_right(id); }
    ID const& at(T const& value) const { return store.at_left(value); }
    int       size() const { return store.get_map().size(); }
};
} // namespace hstd
