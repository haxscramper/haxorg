#pragma once

#include <hstd/system/reflection.hpp>
#include <utility>


namespace hstd {

template <typename A, typename B>
using Pair = std::pair<A, B>;


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
