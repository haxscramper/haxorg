#pragma once

#include <nlohmann/json_fwd.hpp>
#include <string>

using json   = nlohmann::json;
namespace ns = nlohmann;

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
