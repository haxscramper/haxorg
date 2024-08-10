#pragma once

#include <utility>
#include <boost/container_hash/hash.hpp>
#include <hstd/system/Formatter.hpp>

template <typename A, typename B>
using Pair = std::pair<A, B>;

template <typename A, typename B>
struct std::hash<Pair<A, B>> {
    std::size_t operator()(Pair<A, B> const& it) const noexcept {
        std::size_t result = 0;
        boost::hash_combine(result, it.first);
        boost::hash_combine(result, it.second);
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
