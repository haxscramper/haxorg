#pragma once

#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Json.hpp>

namespace hstd {
template <typename T>
struct JsonSerde<std::optional<T>> {
    static json to_json(std::optional<T> const& it) {
        if (it) {
            return JsonSerde<T>::to_json(*it);
        } else {
            return json();
        }
    }
    static std::optional<T> from_json(json const& j) {
        if (j.is_null()) {
            return std::nullopt;
        } else {
            return std::make_optional<T>(JsonSerde<T>::from_json(j));
        }
    }
};
}
