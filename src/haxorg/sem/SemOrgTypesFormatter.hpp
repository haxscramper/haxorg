#pragma once

#include <haxorg/sem/SemOrgTypes.hpp>
#include <hstd/stdlib/Formatter.hpp>

template <>
struct fmt::formatter<org::sem::SemId<org::sem::Org>> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(
        org::sem::SemId<org::sem::Org> const& p,
        fmt::format_context&                  ctx) const {
        return hstd::fmt_ctx(p->getKind(), ctx);
    }
};


template <typename T>
struct fmt::formatter<org::sem::SemId<T>> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(org::sem::SemId<T> const& p, fmt::format_context& ctx) const {
        if (p.isNil()) {
            return hstd::fmt_ctx("<nil>", ctx);
        } else {
            return hstd::fmt_ctx(p->getKind(), ctx);
        }
    }
};

template <>
struct fmt::formatter<org::sem::OrgJson> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(org::sem::OrgJson const& p, fmt::format_context& ctx) const {
        return hstd::fmt_ctx(p.dump(0), ctx);
    }
};
