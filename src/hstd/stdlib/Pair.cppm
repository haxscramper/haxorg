module;

#include <boost/container_hash/hash.hpp>

export module hstd.stdlib.Pair;
export import std;

export {
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
}
