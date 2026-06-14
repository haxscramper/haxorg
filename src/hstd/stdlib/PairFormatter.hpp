#pragma once

#include <hstd/stdlib/Pair.hpp>
#include <hstd/stdlib/Formatter.hpp>

namespace hstd {
template <typename Tuple, std::size_t... Is>
hstd::fmt_iter format_tuple_impl(
    Tuple const&         t,
    fmt::format_context& ctx,
    std::index_sequence<Is...>) {
    ::hstd::fmt_ctx("(", ctx);
    (...,
     (::hstd::fmt_ctx(std::get<Is>(t), ctx),
      ::hstd::fmt_ctx((Is + 1 == sizeof...(Is) ? "" : ", "), ctx)));
    return ::hstd::fmt_ctx(")", ctx);
}
} // namespace hstd


template <typename A, typename B>
struct fmt::formatter<hstd::Pair<A, B>> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(hstd::Pair<A, B> const& p, fmt::format_context& ctx) const {
        ::hstd::fmt_ctx("(", ctx);
        ::hstd::fmt_ctx(p.first, ctx);
        ::hstd::fmt_ctx(", ", ctx);
        ::hstd::fmt_ctx(p.second, ctx);
        return ::hstd::fmt_ctx(")", ctx);
    }
};

template <typename... Args>
struct fmt::formatter<std::tuple<Args...>> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(std::tuple<Args...> const& t, fmt::format_context& ctx) const {
        return ::hstd::format_tuple_impl(t, ctx, std::index_sequence_for<Args...>{});
    }
};
