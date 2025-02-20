#pragma once

#include <utility>
#include <boost/container_hash/hash.hpp>
#include <hstd/system/Formatter.hpp>
#include <hstd/system/reflection.hpp>

template <typename A, typename B>
using Pair = std::pair<A, B>;

template <typename A, typename B>
struct std::hash<Pair<A, B>> {
    std::size_t operator()(Pair<A, B> const& it) const noexcept {
        std::size_t result = 0;
        hax_hash_combine(result, it.first);
        hax_hash_combine(result, it.second);
        return result;
    }
};

template <typename A, typename B>
struct std::formatter<Pair<A, B>> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const Pair<A, B>& p, FormatContext& ctx) const {
        fmt_ctx("(", ctx);
        fmt_ctx(p.first, ctx);
        fmt_ctx(", ", ctx);
        fmt_ctx(p.second, ctx);
        return fmt_ctx(")", ctx);
    }
};

template <typename Tuple, std::size_t... Is, typename FormatContext>
auto format_tuple_impl(
    const Tuple&   t,
    FormatContext& ctx,
    std::index_sequence<Is...>) {
    fmt_ctx("(", ctx);
    (...,
     (fmt_ctx(std::get<Is>(t), ctx),
      fmt_ctx((Is + 1 == sizeof...(Is) ? "" : ", "), ctx)));
    return fmt_ctx(")", ctx);
}

template <typename... Args>
struct std::formatter<std::tuple<Args...>> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const std::tuple<Args...>& t, FormatContext& ctx) const {
        return format_tuple_impl(
            t, ctx, std::index_sequence_for<Args...>{});
    }
};
