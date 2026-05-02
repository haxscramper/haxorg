#pragma once

#include <boost/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap/unordered_multiset_of.hpp>
#include <optional>
#include <stdexcept>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Exception.hpp>


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
    void erase_left(L const& leftKey) { bimap.left.erase(leftKey); }
    void erase_right(R const& rightKey) { bimap.right.erase(rightKey); }


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
        if (contains_right(rightKey)) {
            return bimap.right.at(rightKey);
        } else {
            throw hstd::key_error::init(
                hstd::fmt(
                    "right bimap key does not exist {}",
                    hstd::fmt1_maybe(rightKey)));
        }
    }

    R const& at_right(L const& leftKey) const {
        if (contains_left(leftKey)) {
            return bimap.left.at(leftKey);
        } else {
            throw hstd::key_error::init(
                hstd::fmt(
                    "left bimap key does not exist {}",
                    hstd::fmt1_maybe(leftKey)));
        }
    }

    void add_unique(L const& left, R const& right) {
        if (contains_left(left) || contains_right(right)) {
            throw hstd::runtime_error::init(
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

template <
    typename L,
    typename R,
    typename LHash = std::hash<L>,
    typename RHash = std::hash<R>>
class UnorderedNto1Bimap {
    using BoostBimap = boost::bimap<
        boost::bimaps::unordered_set_of<L, LHash>,
        boost::bimaps::unordered_multiset_of<R, RHash>>;

    BoostBimap bimap;

  public:
    void erase_left(L const& leftKey) { bimap.left.erase(leftKey); }
    void erase_right(R const& rightKey) { bimap.right.erase(rightKey); }

    bool contains_left(L const& leftKey) const {
        return bimap.left.find(leftKey) != bimap.left.end();
    }

    bool contains_right(R const& rightKey) const {
        return bimap.right.find(rightKey) != bimap.right.end();
    }

    Vec<L> get_left(R const& rightKey) const {
        Vec<L> result;
        auto [begin, end] = bimap.right.equal_range(rightKey);
        for (auto it = begin; it != end; ++it) {
            result.push_back(it->second);
        }
        return result;
    }

    Opt<R> get_right(L const& leftKey) const {
        auto it = bimap.left.find(leftKey);
        if (it != bimap.left.end()) { return it->second; }
        return std::nullopt;
    }

    Vec<L> at_left(R const& rightKey) const {
        if (!contains_right(rightKey)) {
            throw hstd::runtime_error::init(
                "at_left failed: Right key not found.");
        }
        return get_left(rightKey);
    }

    R const& at_right(L const& leftKey) const {
        return bimap.left.at(leftKey);
    }

    void add_unique(L const& left, R const& right) {
        // bimap::insert natively checks duplicates on both sides:
        // - Rejects if Left already exists (unordered_set_of constraint)
        // - Allows Right to exist multiple times (unordered_multiset_of
        // constraint)
        if (!bimap.insert({left, right}).second) {
            throw hstd::runtime_error::init(
                "add_unique failed: Left key already exists.");
        }
    }

    Vec<L> left_keys() const {
        Vec<L> result;
        for (const auto& pair : bimap.left) {
            result.push_back(pair.first);
        }
        return result;
    }

    Vec<R> right_keys() const {
        Vec<R> result;
        for (const auto& pair : bimap.right) {
            result.push_back(pair.first);
        }
        return result;
    }

    bool reassign(L const& left, R const& new_right) {
        auto it = bimap.left.find(left);
        if (it == bimap.left.end()) { return false; }
        bimap.left.modify_data(
            it, [new_right](R& val) { val = new_right; });
        return true;
    }

    auto const& get_map() const { return bimap.left; }
    auto const& raw() const { return bimap; }
};

} // namespace hstd::ext


template <typename L, typename R, typename LHash, typename RHash>
struct std::formatter<hstd::ext::Unordered1to1Bimap<L, R, LHash, RHash>>
    : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(
        hstd::ext::Unordered1to1Bimap<L, R, LHash, RHash> const& p,
        FormatContext& ctx) const {
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
