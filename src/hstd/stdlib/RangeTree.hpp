#pragma once

#include <iostream>
#include <algorithm>

#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Slice.hpp>
#include <hstd/stdlib/Vec.hpp>

#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/stdlib/Ranges.hpp>

template <typename T>
class RangeTree {
  public:
    struct Range {
        Slice<T> range;
        int      index;

        bool contains(CR<T> point) const { return range.contains(point); }

        CR<T> first() const { return range.first; }
        CR<T> last() const { return range.last; }
    };

    struct Node {
        T          center;
        Vec<Range> leftRanges;
        Vec<Range> rightRanges;
        UPtr<Node> left  = nullptr;
        UPtr<Node> right = nullptr;
        Node(T center) : center(center) {}

        Vec<Node*> getAllNodes(CR<T> point) const {
            Vec<Node*> result;

            if (rs::any_of(
                    leftRanges,
                    [&](CR<Range> r) { return r.contains(point); })
                || rs::any_of(
                    rightRanges,
                    [&](CR<Range> r) { return r.contains(point); })
                //
            ) {
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
        Vec<Range> overlappingRanges;

        for (const auto& range : ranges) {
            if (range.last() < center) {
                leftRanges.push_back(range);
            } else if (range.first() > center) {
                rightRanges.push_back(range);
            } else {
                overlappingRanges.push_back(range);
            }
        }

        node->leftRanges  = overlappingRanges;
        node->rightRanges = overlappingRanges;

        std::sort(
            node->leftRanges.begin(),
            node->leftRanges.end(),
            [](const Range& a, const Range& b) {
                return a.first() < b.first();
            });

        std::sort(
            node->rightRanges.begin(),
            node->rightRanges.end(),
            [](const Range& a, const Range& b) {
                return a.last() < b.last();
            });

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
            for (auto const& left : node->leftRanges) {
                res.push_back(left);
            }

            for (auto const& right : node->rightRanges) {
                res.push_back(right);
            }
        }

        return res;
    }

    UPtr<Node> root;
};


template <typename T>
std::ostream& auxPrintNode(
    std::ostream&                      os,
    typename RangeTree<T>::Node const& node) {
    os << fmt1(node.range) << "{";

    if (node.left != nullptr) {
        os << " left = ";
        auxPrintNode<T>(os, *(node.left));
    }

    if (node.right != nullptr) {
        os << " right = ";
        auxPrintNode<T>(os, *(node.right));
    }

    os << "}";

    return os;
}

template <typename T>
struct std::formatter<RangeTree<T>> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const RangeTree<T>& p, FormatContext& ctx) const {
        if (p.root == nullptr) {
            return fmt_ctx("nil", ctx);
        } else {
            typename RangeTree<T>::Node& node = *(p.root.get());
            std::stringstream            os;
            auxPrintNode<T>(os, node);
            return fmt_ctx(os.str(), ctx);
        }
    }
};


extern template class RangeTree<int>;
