#pragma once

#include <boost/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <optional>
#include <stdexcept>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/system/Formatter.hpp>

namespace hstd::ext {

/// \brief Simplified wrapper around boost bimap, providing a simpler
/// interace for 1-1 mapping between two types `L` and `R`.
template <
    typename L,
    typename R,
    typename LHash = std::hash<L>,
    typename RHash = std::hash<R>>
class Unordered1to1Bimap {
    using BoostBimap = boost::bimap<
        boost::bimaps::unordered_set_of<L, LHash>,
        boost::bimaps::unordered_set_of<R, RHash>>;

    BoostBimap bimap;

  public:
    bool contains_left(L const& leftKey) const {
        return bimap.left.find(leftKey) != bimap.left.end();
    }

    bool contains_right(R const& rightKey) const {
        return bimap.right.find(rightKey) != bimap.right.end();
    }

    Opt<L> get_left(R const& rightKey) const {
        auto it = bimap.right.find(rightKey);
        if (it != bimap.right.end()) { return it->second; }
        return std::nullopt;
    }

    Opt<R> get_right(L const& leftKey) const {
        auto it = bimap.left.find(leftKey);
        if (it != bimap.left.end()) { return it->second; }
        return std::nullopt;
    }

    L const& at_left(R const& rightKey) const {
        return bimap.right.at(rightKey);
    }

    R const& at_right(L const& leftKey) const {
        return bimap.left.at(leftKey);
    }

    void add_unique(L const& left, R const& right) {
        if (contains_left(left) || contains_right(right)) {
            throw std::runtime_error(
                "add_unique failed: Keys already exist.");
        }
        bimap.insert({left, right});
    }

    Vec<L> left_keys() const {
        Vec<L> result;
        for (const auto& pair : bimap.left) {
            result.push_back(pair.first);
        }
        return result;
    }

    auto const& get_map() const { return bimap.left; }

    Vec<R> right_keys() const {
        Vec<R> result;
        for (const auto& pair : bimap.right) {
            result.push_back(pair.first);
        }
        return result;
    }
};

} // namespace hstd::ext

template <typename L, typename R>
struct std::formatter<hstd::ext::Unordered1to1Bimap<L, R>>
    : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(
        const hstd::ext::Unordered1to1Bimap<L, R>& p,
        FormatContext&                             ctx) const {
        bool first = true;
        fmt_ctx("{", ctx);
        for (auto const& [left, right] : p.get_map()) {
            if (first) {
                first = false;
            } else {
                fmt_ctx(", ", ctx);
            }
            fmt_ctx(left, ctx);
            fmt_ctx("<>", ctx);
            fmt_ctx(right, ctx);
        }

        return fmt_ctx("}", ctx);
    }
};
