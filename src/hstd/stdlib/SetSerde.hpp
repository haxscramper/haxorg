#pragma once

#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/JsonSerde.hpp>
#include <hstd/stdlib/Set.hpp>

namespace hstd {
template <typename T>
struct JsonSerde<UnorderedSet<T>> {
    static json to_json(UnorderedSet<T> const& it) {
        auto result = json::array();
        for (auto const& v : it) { result.push_back(JsonSerde<T>::to_json(v)); }

        return result;
    }
    static UnorderedSet<T> from_json(json const& j) {
        UnorderedSet<T> result;
        for (auto const& i : j) { result.incl(JsonSerde<T>::from_json(i)); }
        return result;
    }
};
} // namespace hstd
