#pragma once

#include <hstd/stdlib/dod_base.hpp>
#include <hstd/stdlib/Formatter.hpp>


template <hstd::dod::IsDescribedDodIdType Id>
struct std::formatter<Id> : std::formatter<std::string> {
    using FmtType = Id;
    template <typename FormatContext>
    FormatContext::iterator format(FmtType const& p, FormatContext& ctx)
        const {
        std::formatter<std::string> fmt;
        return fmt.format(p.format(), ctx);
    }
};
