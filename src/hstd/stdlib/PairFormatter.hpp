#pragma once

#include <hstd/stdlib/Pair.hpp>
#include <hstd/stdlib/Formatter.hpp>

template <typename A, typename B>
struct std::formatter<hstd::Pair<A, B>> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const hstd::Pair<A, B>& p, FormatContext& ctx) const {
        ::hstd::fmt_ctx("(", ctx);
        ::hstd::fmt_ctx(p.first, ctx);
        ::hstd::fmt_ctx(", ", ctx);
        ::hstd::fmt_ctx(p.second, ctx);
        return ::hstd::fmt_ctx(")", ctx);
    }
};

template <typename... Args>
struct std::formatter<std::tuple<Args...>> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const std::tuple<Args...>& t, FormatContext& ctx) const {
        return ::hstd::format_tuple_impl(
            t, ctx, std::index_sequence_for<Args...>{});
    }
};
