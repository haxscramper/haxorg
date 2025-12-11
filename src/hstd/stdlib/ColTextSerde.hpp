#pragma once

#include <hstd/stdlib/ColText.hpp>
#include <hstd/stdlib/Json.hpp>

namespace hstd {

json to_formatting_json(const Vec<ColRune>& runes);

template <>
struct JsonSerde<hstd::ColText> {
    static json to_json(hstd::ColText const& it) {
        return hstd::to_formatting_json(it);
    }
    static hstd::ColText from_json(json const& j) {
        throw hstd::logic_unreachable_error::init(
            "Conversion from JSON to colored text is not supported");
    }
};


} // namespace hstd
