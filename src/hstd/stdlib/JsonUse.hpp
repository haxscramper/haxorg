#pragma once

#include <nlohmann/json.hpp>

#include <boost/describe.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/Formatter.hpp>


template <>
struct std::formatter<json> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const json& p, FormatContext& ctx) const {
        return hstd::fmt_ctx(p.dump(), ctx);
    }
};

extern template class nlohmann::basic_json<>;
