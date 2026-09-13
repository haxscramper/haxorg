#pragma once

#include <hstd/ext/hstd_serde.hpp>
#include <hstd/stdlib/JsonSerde.hpp>

namespace hstd {

template <typename E>
struct JsonSerdeProtobufValue {
    static E from_json(json const& j) {
        throw std::runtime_error("cannot deser protobuf values");
    }

    static json to_json(E const& value) {
        return json::parse(hstd::serde::getJString(value));
    }
};


} // namespace hstd
