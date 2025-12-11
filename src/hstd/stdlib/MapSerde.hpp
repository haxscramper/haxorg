#pragma once

#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/Json.hpp>

namespace hstd {
template <typename K, typename V>
struct JsonSerde<UnorderedMap<K, V>> {
    static json to_json(UnorderedMap<K, V> const& it) {
        auto result = json::array();
        for (auto const& [key, val] : it) {
            result.push_back(json::object({
                {"key", JsonSerde<K>::to_json(key)},
                {"value", JsonSerde<V>::to_json(val)},
            }));
        }

        return result;
    }
    static UnorderedMap<K, V> from_json(json const& j) {
        UnorderedMap<K, V> result;
        for (auto const& i : j) {
            result.insert_or_assign(
                JsonSerde<K>::from_json(i["key"]),
                JsonSerde<V>::from_json(i["value"]));
        }
        return result;
    }
};
} // namespace hstd
