#pragma once

#include <nlohmann/json.hpp>

#include <boost/describe.hpp>
#include <hstd_cpp_lib/stdlib/formatting/Formatter.hpp>
#include <hstd_cpp_lib/stdlib/serde/Json.hpp>
#include <hstd_cpp_lib/system/reflection.hpp>


template <>
struct fmt::formatter<json> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(json const& p, fmt::format_context& ctx) const {
        return hstd::fmt_ctx(p.dump(), ctx);
    }
};

extern template class nlohmann::basic_json<>;
