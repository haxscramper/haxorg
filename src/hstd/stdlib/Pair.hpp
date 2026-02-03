#pragma once

#include <utility>
#include <hstd/system/reflection.hpp>

namespace hstd {

template <typename A, typename B>
using Pair = std::pair<A, B>;


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

template <typename T>
Pair<T, T> pair1(T const& first, T const& second) {
    return Pair<T, T>{first, second};
}

template <typename A, typename B>
Pair<A, B> pair2(A const& first, B const& second) {
    return Pair<A, B>{first, second};
}

} // namespace hstd


template <typename A, typename B>
struct std::hash<hstd::Pair<A, B>> {
    std::size_t operator()(hstd::Pair<A, B> const& it) const noexcept {
        std::size_t result = 0;
        ::hstd::hax_hash_combine(result, it.first);
        ::hstd::hax_hash_combine(result, it.second);
        return result;
    }
};


namespace std {
template <typename A, typename B>
bool operator==(std::pair<A, B> const& lhs, std::pair<A, B> const& rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second;
}
} // namespace std
