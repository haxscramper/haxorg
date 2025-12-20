#pragma once

#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Formatter.hpp>


template <hstd::DescribedSubVariantType V>
struct std::formatter<V> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const V& p, FormatContext& ctx) const {
        ::hstd::fmt_ctx(p.sub_variant_get_kind(), ctx);
        ::hstd::fmt_ctx("(", ctx);
        std::visit(
            [&](auto const& t) { ::hstd::fmt_ctx(t, ctx); },
            p.sub_variant_get_data());
        ::hstd::for_each_field_value_with_bases(
            p, [&](char const* name, auto const& value) {
                if (std::string{name}
                    != std::string{p.sub_variant_get_name()}) {
                    ::hstd::fmt_ctx(", ", ctx);
                    ::hstd::fmt_ctx(".", ctx);
                    ::hstd::fmt_ctx(name, ctx);
                    ::hstd::fmt_ctx(" = ", ctx);
                    ::hstd::fmt_ctx(value, ctx);
                }
            });
        return ::hstd::fmt_ctx(")", ctx);
    }
};


template <hstd::IsVariant V>
struct std::formatter<V> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(const V& p, FormatContext& ctx) const {
        std::string res;
        ::hstd::fmt_ctx("Var(", ctx);
        ::hstd::fmt_ctx(p.index(), ctx);
        ::hstd::fmt_ctx(": ", ctx);
        std::visit(
            [&ctx](const auto& value) { ::hstd::fmt_ctx(value, ctx); }, p);
        return ::hstd::fmt_ctx(")", ctx);
    }
};
