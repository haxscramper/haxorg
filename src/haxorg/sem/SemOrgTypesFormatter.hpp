#pragma once

#include <haxorg/sem/SemOrgTypes.hpp>
#include <hstd/stdlib/Formatter.hpp>

template <>
struct std::formatter<org::sem::SemId<org::sem::Org>>
    : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        const org::sem::SemId<org::sem::Org>& p,
        FormatContext&                        ctx) const {
        return hstd::fmt_ctx(p->getKind(), ctx);
    }
};


template <typename T>
struct std::formatter<org::sem::SemId<T>> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        const org::sem::SemId<T>& p,
        FormatContext&            ctx) const {
        if (p.isNil()) {
            return hstd::fmt_ctx("<nil>", ctx);
        } else {
            return hstd::fmt_ctx(p->getKind(), ctx);
        }
    }
};

template <>
struct std::formatter<org::sem::OrgJson> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const org::sem::OrgJson& p, FormatContext& ctx) const {
        return hstd::fmt_ctx(p.dump(0), ctx);
    }
};
