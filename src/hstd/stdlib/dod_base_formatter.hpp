#pragma once

#include <hstd/stdlib/dod_base.hpp>
#include <hstd/stdlib/Formatter.hpp>


template <hstd::dod::IsDescribedDodIdType Id>
struct fmt::formatter<Id> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(Id const& p, fmt::format_context& ctx) const {
        return hstd::fmt_ctx(p.format(), ctx);
    }
};
