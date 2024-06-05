#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Slice.hpp>
#include <hstd/stdlib/Vec.hpp>

#include <hstd/stdlib/Ptrs.hpp>

template <typename T>
class RangeTree {
  public:
    struct Node {
        Slice<T>   range;
        int        rangeIndex;
        UPtr<Node> left;
        UPtr<Node> right = nullptr;
        Node(
            const Slice<T>& r,
            int             rangeIndex,
            UPtrIn<Node>    left  = nullptr,
            UPtrIn<Node>    right = nullptr)
            : range(r)
            , rangeIndex(rangeIndex)
            , left(std::move(left))
            , right(std::move(right)) {}
    };

    RangeTree(const Vec<Slice<T>>& slices = Vec<Slice<T>>()) {
        root = build(slices);
    }


    UPtr<Node> buildRec(const Vec<Slice<T>>& slices, int start, int end) {

        if (start > end) {
            return nullptr;
        } else if (start == end) {
            return std::make_unique<Node>(slices[start], start);
        } else {
            int        mid   = (start + end) / 2;
            UPtr<Node> left  = buildRec(slices, start, mid);
            UPtr<Node> right = buildRec(slices, mid + 1, end);
            return std::make_unique<Node>(
                slices[mid], mid, std::move(left), std::move(right));
        }
    }


    UPtr<Node> build(Vec<Slice<T>> slices) {
        std::sort(
            slices.begin(),
            slices.end(),
            [](CR<Slice<T>> lhs, CR<Slice<T>> rhs) {
                if (lhs.first != rhs.first) {
                    return lhs.first < rhs.first;
                } else if (lhs.last != rhs.last) {
                    // When lhs completely contains rhs, sort lhs first.
                    return rhs.last < lhs.last;
                } else {
                    return true;
                }
            });
        return buildRec(slices, 0, slices.size() - 1);
    }

    Opt<Node*> getNode(CR<T> point) const {
        Node* curr = root.get();

        while (curr != nullptr) {
            if (point < curr->range.first) {
                curr = curr->left.get();
            } else if (curr->range.last < point) {
                curr = curr->right.get();
            } else {
                if (curr->range.contains(point)) { return curr; }
            }
        }

        return std::nullopt;
    }

    Opt<int> getRangeIndex(CR<T> point) const {
        if (auto node = getNode(point)) {
            return (**node).rangeIndex;
        } else {
            return std::nullopt;
        }
    }

    Opt<Slice<T>> query(CR<T> point) const {
        if (auto node = getNode(point)) {
            return (**node).range;
        } else {
            return std::nullopt;
        }
    }

    UPtr<Node> root;
};


template <typename T>
std::ostream& auxPrintNode(
    std::ostream&                      os,
    typename RangeTree<T>::Node const& node) {
    os << node.range << "{ ";
    if (node.left != nullptr) { auxPrintNode<T>(os, *(node.left)); }

    os << ", ";
    if (node.right != nullptr) { auxPrintNode<T>(os, *(node.right)); }
    os << "}";

    return os;
}

template <typename T>
struct std::formatter<RangeTree<T>> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const RangeTree<T>& p, FormatContext& ctx) {
        if (p.root == nullptr) {
            return "nil";
        } else {
            typename RangeTree<T>::Node& node = *(p.root.get());
            std::stringstream            os;
            auxPrintNode<T>(os, node);
            return os.str();
        }
    }
};


extern template class RangeTree<int>;
