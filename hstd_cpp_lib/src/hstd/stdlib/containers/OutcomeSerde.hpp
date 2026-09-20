#pragma once

#include <hstd_cpp_lib/stdlib/containers/Outcome.hpp>
#include <hstd_cpp_lib/stdlib/serde/JsonSerde.hpp>

namespace hstd {
template <typename Value, typename Error, class NoValuePolicy>
struct JsonSerde<hstd::Result<Value, Error, NoValuePolicy>> {
    static hstd::Result<Value, Error, NoValuePolicy> from_json(json const& j) {
        if (j.contains("error")) {
            return boost::outcome_v2::failure(
                hstd::JsonSerde<Error>::from_json(j["error"]));
        } else {
            return boost::outcome_v2::success(
                hstd::JsonSerde<Value>::from_json(j["value"]));
        }
    }

    static json to_json(hstd::Result<Value, Error, NoValuePolicy> value) {
        if (value.has_value()) {
            return json::object(
                {{"value", hstd::JsonSerde<Value>::to_json(value.value())}});
        } else {
            return json::object(
                {{"error", hstd::JsonSerde<Error>::to_json(value.error())}});
        }
    }
};

template <typename Error, class NoValuePolicy>
struct JsonSerde<hstd::Result<void, Error, NoValuePolicy>> {
    static hstd::Result<void, Error, NoValuePolicy> from_json(json const& j) {
        if (j.contains("error")) {
            return boost::outcome_v2::failure(
                hstd::JsonSerde<Error>::from_json(j["error"]));
        } else {
            return boost::outcome_v2::success();
        }
    }

    static json to_json(hstd::Result<void, Error, NoValuePolicy> value) {
        if (value.has_value()) {
            return json::object();
        } else {
            return json::object(
                {{"error", hstd::JsonSerde<Error>::to_json(value.error())}});
        }
    }
};


} // namespace hstd
