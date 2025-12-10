#pragma once

#include <hstd/ext/bimap_wrap.hpp>
#include <hstd/stdlib/Json.hpp>

namespace hstd {
template <typename L, typename R, typename LHash, typename RHash>
struct JsonSerde<hstd::ext::Unordered1to1Bimap<L, R, LHash, RHash>> {
    static json to_json(
        hstd::ext::Unordered1to1Bimap<L, R, LHash, RHash> const& it) {
        auto result = json::array();
        for (auto const& key : it.left_keys()) {
            result.push_back(
                json::object({
                    {"left", JsonSerde<L>::to_json(key)},
                    {"right", JsonSerde<R>::to_json(it.at_right(key))},
                }));
        }

        return result;
    }
    static hstd::ext::Unordered1to1Bimap<L, R, LHash, RHash> from_json(
        json const& j) {
        hstd::ext::Unordered1to1Bimap<L, R, LHash, RHash> result;
        for (auto const& i : j) {
            result.add_unique(
                JsonSerde<L>::from_json(i["left"]),
                JsonSerde<R>::from_json(i["right"]));
        }
        return result;
    }
};
} // namespace hstd
