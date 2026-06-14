#pragma once

#include <hstd/stdlib/dod_base.hpp>
#include <hstd/stdlib/Formatter.hpp>


template <hstd::dod::IsDescribedDodIdType Id>
struct fmt::formatter<Id> : fmt::formatter<std::string> {
    using FmtType = Id;

    hstd::fmt_iter format(FmtType const& p, fmt::format_context& ctx) const {
        fmt::formatter<std::string> fmt;
        return fmt.format(p.format(), ctx);
    }
};
