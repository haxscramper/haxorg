#pragma once

#include <nlohmann/json.hpp>
#include <string>

#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Vec.hpp>

#include <boost/describe.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/system/Formatter.hpp>

using json   = nlohmann::json;
namespace ns = nlohmann;

template <>
struct std::formatter<json> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const json& p, FormatContext& ctx) const {
        return hstd::fmt_ctx(p.dump(), ctx);
    }
};

extern template class nlohmann::basic_json<>;

namespace hstd {

template <typename T>
struct JsonSerde;

struct JsonFormatOptions {
    int  width            = 80;
    int  indent           = 2;
    int  startIndent      = 0;
    bool stableFieldOrder = false;
};

std::string to_compact_json(
    json const&              j,
    JsonFormatOptions const& options = JsonFormatOptions{});


void filterFields(json& j, const std::vector<std::string>& fieldsToRemove);


} // namespace hstd
