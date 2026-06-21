#pragma once

#include <nlohmann/json.hpp>

#include <boost/describe.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/Formatter.hpp>


template <>
struct fmt::formatter<json> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(json const& p, fmt::format_context& ctx) const {
        return hstd::fmt_ctx(p.dump(), ctx);
    }
};

extern template class nlohmann::basic_json<>;
