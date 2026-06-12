#pragma once

#include <boost/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap/vector_of.hpp>
#include <boost/bimap/unordered_multiset_of.hpp>
#include <optional>
#include <stdexcept>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Exception.hpp>

namespace hstd::ext {

template <typename Derived, typename BoostBimap, typename L, typename R>
class XtoYBimapBase {
  protected:
    BoostBimap bimap;

    Derived const& self() const { return static_cast<Derived const&>(*this); }

  public:
    void erase_left(L const& leftKey) { bimap.left.erase(leftKey); }
    void erase_right(R const& rightKey) { bimap.right.erase(rightKey); }

    bool contains_left(L const& leftKey) const {
        return bimap.left.find(leftKey) != bimap.left.end();
    }

    bool contains_right(R const& rightKey) const {
        return bimap.right.find(rightKey) != bimap.right.end();
    }

    Vec<L> left_keys() const {
        Vec<L> result;
        for (const auto& pair : bimap.left) { result.push_back(pair.first); }
        return result;
    }

    Vec<R> right_keys() const {
        Vec<R> result;
        for (const auto& pair : bimap.right) { result.push_back(pair.first); }
        return result;
    }

    auto const& get_map() const { return bimap.left; }
    auto const& raw() const { return bimap; }
};

/// \brief Simplified wrapper around boost bimap, providing a simpler
/// interace for 1-1 mapping between two types `L` and `R`.
template <

    typename L,
    typename R,
    typename LHash = std::hash<L>,
    typename RHash = std::hash<R>>
class Unordered1to1Bimap
    : public XtoYBimapBase<
          Unordered1to1Bimap<L, R, LHash, RHash>,
          boost::bimap<
              boost::bimaps::unordered_set_of<L, LHash>,
              boost::bimaps::unordered_set_of<R, RHash>>,
          L,
          R> {
    using BoostBimap = boost::bimap<
        boost::bimaps::unordered_set_of<L, LHash>,
        boost::bimaps::unordered_set_of<R, RHash>>;
    using Base = XtoYBimapBase<Unordered1to1Bimap<L, R, LHash, RHash>, BoostBimap, L, R>;

  public:
    Opt<L> get_left(R const& rightKey) const {
        auto it = this->bimap.right.find(rightKey);
        if (it != this->bimap.right.end()) { return it->second; }
        return std::nullopt;
    }

    Opt<R> get_right(L const& leftKey) const {
        auto it = this->bimap.left.find(leftKey);
        if (it != this->bimap.left.end()) { return it->second; }
        return std::nullopt;
    }

    L const& at_left(R const& rightKey) const {
        if (this->contains_right(rightKey)) {
            return this->bimap.right.at(rightKey);
        } else {
            throw hstd::key_error::init(
                hstd::fmt(
                    "right bimap key does not exist {}", hstd::fmt1_maybe(rightKey)));
        }
    }

    R const& at_right(L const& leftKey) const {
        if (this->contains_left(leftKey)) {
            return this->bimap.left.at(leftKey);
        } else {
            throw hstd::key_error::init(
                hstd::fmt("left bimap key does not exist {}", hstd::fmt1_maybe(leftKey)));
        }
    }

    void add_unique(L const& left, R const& right) {
        if (this->contains_left(left) || this->contains_right(right)) {
            throw hstd::runtime_error::init("add_unique failed: Keys already exist.");
        }
        this->bimap.insert({left, right});
    }
};

template <
    typename L,
    typename R,
    typename LHash = std::hash<L>,
    typename RHash = std::hash<R>>
class UnorderedNto1Bimap
    : public XtoYBimapBase<
          UnorderedNto1Bimap<L, R, LHash, RHash>,
          boost::bimap<
              boost::bimaps::unordered_set_of<L, LHash>,
              boost::bimaps::unordered_multiset_of<R, RHash>>,
          L,
          R> {
    using BoostBimap = boost::bimap<
        boost::bimaps::unordered_set_of<L, LHash>,
        boost::bimaps::unordered_multiset_of<R, RHash>>;
    using Base = XtoYBimapBase<UnorderedNto1Bimap<L, R, LHash, RHash>, BoostBimap, L, R>;

  public:
    Vec<L> get_left(R const& rightKey) const {
        Vec<L> result;
        auto [begin, end] = this->bimap.right.equal_range(rightKey);
        for (auto it = begin; it != end; ++it) { result.push_back(it->second); }
        return result;
    }

    Opt<R> get_right(L const& leftKey) const {
        auto it = this->bimap.left.find(leftKey);
        if (it != this->bimap.left.end()) { return it->second; }
        return std::nullopt;
    }

    Vec<L> at_left(R const& rightKey) const {
        if (!this->contains_right(rightKey)) {
            throw hstd::runtime_error::init("at_left failed: Right key not found.");
        }
        return get_left(rightKey);
    }

    R const& at_right(L const& leftKey) const { return this->bimap.left.at(leftKey); }

    void add_unique(L const& left, R const& right) {
        // bimap::insert natively checks duplicates on both sides:
        // - Rejects if Left already exists (unordered_set_of constraint)
        // - Allows Right to exist multiple times (unordered_multiset_of
        // constraint)
        if (!this->bimap.insert({left, right}).second) {
            throw hstd::runtime_error::init(
                "add_unique failed: Left key already exists.");
        }
    }

    bool reassign(L const& left, R const& new_right) {
        auto it = this->bimap.left.find(left);
        if (it == this->bimap.left.end()) { return false; }
        this->bimap.left.modify_data(it, [new_right](R& val) { val = new_right; });
        return true;
    }
};

template <typename L, typename R, typename RHash = std::hash<R>>
class StableNto1Bimap
    : public XtoYBimapBase<
          StableNto1Bimap<L, R, RHash>,
          boost::bimap<
              boost::bimaps::vector_of<L>,
              boost::bimaps::unordered_multiset_of<R, RHash>>,
          L,
          R> {
    using BoostBimap = boost::bimap<
        boost::bimaps::vector_of<L>,
        boost::bimaps::unordered_multiset_of<R, RHash>>;
    using Base = XtoYBimapBase<StableNto1Bimap<L, R, RHash>, BoostBimap, L, R>;

  public:
    Vec<L> get_left(R const& rightKey) const {
        Vec<L> result;
        auto [begin, end] = this->bimap.right.equal_range(rightKey);
        for (auto it = begin; it != end; ++it) { result.push_back(it->second); }
        return result;
    }

    Opt<R> get_right(L const& leftKey) const {
        auto it = std::find_if(
            this->bimap.left.begin(), this->bimap.left.end(), [&](auto const& pair) {
                return pair.first == leftKey;
            });
        if (it != this->bimap.left.end()) { return it->second; }
        return std::nullopt;
    }

    Vec<L> at_left(R const& rightKey) const {
        if (!this->contains_right(rightKey)) {
            throw hstd::runtime_error::init("at_left failed: Right key not found.");
        }
        return get_left(rightKey);
    }

    R const& at_right(L const& leftKey) const {
        auto it = std::find_if(
            this->bimap.left.begin(), this->bimap.left.end(), [&](auto const& pair) {
                return pair.first == leftKey;
            });
        if (it != this->bimap.left.end()) { return it->second; }
        throw hstd::key_error::init(
            hstd::fmt("left bimap key does not exist {}", hstd::fmt1_maybe(leftKey)));
    }

    void add_unique(L const& left, R const& right) {
        auto it = std::find_if(
            this->bimap.left.begin(), this->bimap.left.end(), [&](auto const& pair) {
                return pair.first == left;
            });
        if (it != this->bimap.left.end()) {
            throw hstd::runtime_error::init(
                "add_unique failed: Left key already exists.");
        }
        this->bimap.insert({left, right});
    }

    bool contains_left(L const& leftKey) const {
        return std::find_if(
                   this->bimap.left.begin(),
                   this->bimap.left.end(),
                   [&](auto const& pair) { return pair.first == leftKey; })
            != this->bimap.left.end();
    }

    void erase_left(L const& leftKey) {
        auto it = std::find_if(
            this->bimap.left.begin(), this->bimap.left.end(), [&](auto const& pair) {
                return pair.first == leftKey;
            });
        if (it != this->bimap.left.end()) { this->bimap.left.erase(it); }
    }

    bool reassign(L const& left, R const& new_right) {
        auto it = std::find_if(
            this->bimap.left.begin(), this->bimap.left.end(), [&](auto const& pair) {
                return pair.first == left;
            });
        if (it == this->bimap.left.end()) { return false; }
        this->bimap.left.modify_data(it, [new_right](R& val) { val = new_right; });
        return true;
    }
};

} // namespace hstd::ext

template <typename L, typename R, typename LHash, typename RHash>
struct std::formatter<hstd::ext::Unordered1to1Bimap<L, R, LHash, RHash>>
    : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(
        hstd::ext::Unordered1to1Bimap<L, R, LHash, RHash> const& p,
        FormatContext&                                           ctx) const {
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
