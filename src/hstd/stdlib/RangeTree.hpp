#pragma once

#include <iostream>
#include <algorithm>

#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Slice.hpp>
#include <hstd/stdlib/Vec.hpp>

#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/stdlib/Ranges.hpp>

template <typename T>
struct RangeTreeRange {
    Slice<T> range;
    int      index;

    bool contains(CR<T> point) const { return range.contains(point); }

    CR<T> first() const { return range.first; }
    CR<T> last() const { return range.last; }
};


template <typename T>
class RangeTree {
  public:
    using Range = RangeTreeRange<T>;
    struct Node {
        T          center;
        Vec<Range> overlapping;
        UPtr<Node> left  = nullptr;
        UPtr<Node> right = nullptr;
        Node(T center) : center(center) {}

        Vec<Node*> getAllNodes(CR<T> point) const {
            Vec<Node*> result;

            if (rs::any_of(overlapping, [&](CR<Range> r) {
                    return r.contains(point);
                })) {
                result.push_back(const_cast<Node*>(this));
            }

            if (point < center && left != nullptr) {
                result.append(left->getAllNodes(point));
            }

            if (center < point && right != nullptr) {
                result.append(right->getAllNodes(point));
            }

            return result;
        }
    };

    RangeTree(const Vec<Slice<T>>& slices = Vec<Slice<T>>()) {
        root = build(slices);
    }


    UPtr<Node> buildRec(const Vec<Range>& ranges) {
        if (ranges.empty()) { return nullptr; }

        Vec<T> points;
        for (const auto& range : ranges) {
            points.push_back(range.first());
            points.push_back(range.last());
        }
        std::sort(points.begin(), points.end());
        T center = points.at(points.size() / 2);

        auto node = std::make_unique<Node>(center);

        Vec<Range> leftRanges;
        Vec<Range> rightRanges;

        for (const auto& range : ranges) {
            if (range.last() < center) {
                leftRanges.push_back(range);
            } else if (center < range.first()) {
                rightRanges.push_back(range);
            } else {
                node->overlapping.push_back(range);
            }
        }

        node->left  = buildRec(leftRanges);
        node->right = buildRec(rightRanges);

        return node;
    }


    UPtr<Node> build(Vec<Slice<T>> slices) {
        auto ranges  //
            = slices //
            | rv::enumerate
            | rv::transform([](CR<Pair<int, Slice<T>>> pair) -> Range {
                  return Range{
                      .range = pair.second,
                      .index = pair.first,
                  };
              })
            | rs::to<Vec>();

        std::sort(
            ranges.begin(),
            ranges.end(),
            [](CR<Range> lhs, CR<Range> rhs) {
                if (lhs.range.first != rhs.range.first) {
                    return lhs.range.first < rhs.range.first;
                } else if (lhs.range.last != rhs.range.last) {
                    // When lhs completely contains rhs, sort lhs first.
                    return rhs.range.last < lhs.range.last;
                } else {
                    return true;
                }
            });

        return buildRec(ranges);
    }

    Vec<Node*> getNodes(CR<T> point) const {
        return root->getAllNodes(point);
    }

    Vec<Range> getRanges(CR<T> point) const {
        Vec<Range> res;
        for (auto const& node : getNodes(point)) {
            for (auto const& left : node->overlapping) {
                if (left.contains(point)) { res.push_back(left); }
            }
        }

        return res;
    }

    UPtr<Node> root;
};

template <typename T>
struct std::formatter<RangeTreeRange<T>> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const RangeTreeRange<T>& p, FormatContext& ctx) const {
        fmt_ctx("[", ctx);
        fmt_ctx(p.range.first, ctx);
        fmt_ctx("..", ctx);
        fmt_ctx(p.range.last, ctx);
        fmt_ctx("[", ctx);
        fmt_ctx(p.index, ctx);
        return fmt_ctx("]]", ctx);
    }
};


template <typename T>
struct std::formatter<RangeTree<T>> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const RangeTree<T>& p, FormatContext& ctx) const {
        if (p.root == nullptr) {
            return fmt_ctx("nil", ctx);
        } else {
            typename RangeTree<T>::Node& node = *(p.root.get());
            std::stringstream            os;
            Func<void(typename RangeTree<T>::Node const&, int)> aux;

            aux = [&](typename RangeTree<T>::Node const& node, int level) {
                auto indent = Str("  ").repeated(level);
                os << indent;
                os << fmt(
                    "center = {} overlapping = {}",
                    node.center,
                    node.overlapping);

                if (node.left != nullptr) {
                    os << "\n" << indent << "  left = \n";
                    aux(*(node.left), level + 2);
                }

                if (node.right != nullptr) {
                    os << "\n" << indent << "  right = \n";
                    aux(*(node.right), level + 2);
                }
            };

            aux(*p.root, 0);

            return fmt_ctx(os.str(), ctx);
        }
    }
};


extern template class RangeTree<int>;
