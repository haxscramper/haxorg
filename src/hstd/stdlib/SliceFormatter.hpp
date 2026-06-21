#pragma once

#include <hstd/stdlib/Formatter.hpp>
#include <hstd/stdlib/Slice.hpp>

template <typename T>
struct fmt::formatter<hstd::Slice<T>> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    auto           format(hstd::Slice<T> const& p, fmt::format_context& ctx) const {
        ::hstd::fmt_ctx("[", ctx);
        ::hstd::fmt_ctx(p.first, ctx);
        ::hstd::fmt_ctx("..", ctx);
        ::hstd::fmt_ctx(p.last, ctx);
        return ::hstd::fmt_ctx("]", ctx);
    }
};


template <typename T>
struct std::hash<hstd::Slice<T>> {
    std::size_t operator()(hstd::Slice<T> const& it) const noexcept {
        std::size_t result = 0;
        hax_hash_combine(result, it.first);
        hax_hash_combine(result, it.last);
        return result;
    }
};
