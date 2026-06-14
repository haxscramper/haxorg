#pragma once

#include <haxorg/parse/OrgTypes.hpp>
#include <hstd/stdlib/Formatter.hpp>


template <>
struct fmt::formatter<org::parse::OrgNodeMono::Error> : fmt::formatter<std::string> {

    hstd::fmt_iter format(
        org::parse::OrgNodeMono::Error const& p,
        fmt::format_context&                  ctx) const {
        if (p.box) {
            return hstd::fmt_ctx(*p.box, ctx);
        } else {
            return hstd::fmt_ctx("Error{}", ctx);
        }
    }
};
