#pragma once

#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Json.hpp>

namespace hstd {

template <IsVariant V>
struct JsonSerde<V> {
    static json to_json(V const& it) {
        auto result     = json::object();
        result["index"] = JsonSerde<int>::to_json(it.index());
        std::visit(
            [&]<typename T>(T const& value) {
                result["value"] = JsonSerde<T>::to_json(value);
            },
            it);

        return result;
    }
    static V from_json(json const& j) {
        V result = variant_from_index<V>(j["index"].get<int>());
        std::visit(
            [&]<typename T>(T& value) {
                value = JsonSerde<T>::from_json(j["value"]);
            },
            result);
    }
};

} // namespace hstd
