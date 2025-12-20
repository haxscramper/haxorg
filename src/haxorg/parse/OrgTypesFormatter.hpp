#pragma once

#include <haxorg/parse/OrgTypes.hpp>
#include <hstd/stdlib/Formatter.hpp>


template <>
struct std::formatter<org::parse::OrgNodeMono::Error>
    : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(
        const org::parse::OrgNodeMono::Error& p,
        FormatContext&                        ctx) const {
        if (p.box) {
            return hstd::fmt_ctx(*p.box, ctx);
        } else {
            return hstd::fmt_ctx("Error{}", ctx);
        }
    }
};
