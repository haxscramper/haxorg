#pragma once

#include <hstd_cpp_lib/ext/hstd_serde.hpp>
#include <hstd_cpp_lib/stdlib/serde/JsonSerde.hpp>

namespace hstd {
#if ORG_BUILD_WITH_PROTOBUF
template <typename E>
struct JsonSerdeProtobufValue {
    static E from_json(json const& j) {
        throw std::runtime_error("cannot deser protobuf values");
    }

    static json to_json(E const& value) {
        return json::parse(hstd::serde::getJString(value));
    }
};
#endif

} // namespace hstd
