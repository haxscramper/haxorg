#pragma once

#include <hstd/stdlib/IntSet.hpp>
#include <hstd/stdlib/Json.hpp>


namespace hstd {
template <typename T>
struct JsonSerde<IntSet<T>> {
    static json to_json(IntSet<T> const& it) {
        auto result = json::array();
        for (auto const& item : it) {
            result.push_back(JsonSerde<T>::to_json(item));
        }

        return result;
    }
    static IntSet<T> from_json(json const& j) {
        IntSet<T> result;
        for (auto const& i : j) {
            result.incl(JsonSerde<T>::from_json(i));
        }
        return result;
    }
};
} // namespace hstd
