#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Slice.hpp>
#include <hstd/stdlib/Vec.hpp>

template <typename T>
class RangeTree {
  public:
    struct Node {
        Slice<T> range;
        Node*    left;
        Node*    right;

        Node(
            const Slice<T>& r,
            Node*           left  = nullptr,
            Node*           right = nullptr)
            : range(r), left(left), right(right) {}
    };

    RangeTree(const Vec<Slice<T>>& slices) {
        root = build(slices, 0, slices.size() - 1);
    }

    Node* build(const Vec<Slice<T>>& slices, int start, int end) {
        if (start > end) {
            return nullptr;
        }
        if (start == end) {
            return new Node(slices[start]);
        }

        int   mid   = (start + end) / 2;
        Node* left  = build(slices, start, mid);
        Node* right = build(slices, mid + 1, end);
        return new Node(slices[mid], left, right);
    }

    Opt<Slice<T>> query(CR<T> point) const {
        Node* curr = root;

        while (curr != nullptr) {
            if (point < curr->range.first) {
                curr = curr->left;
            } else if (curr->range.last < point) {
                curr = curr->right;
            } else {
                if (curr->range.contains(point)) {
                    return curr->range;
                }
            }
        }

        // point is not within any range
        return std::nullopt;
    }

  private:
    Node* root;
};

// int main() {
//     Vec<Slice> slices = {Slice(1, 5), Slice(6, 8), Slice(10, 12)};
//     RangeTree     rangeTree(slices);

//     cout << rangeTree.query(3) << endl;  // should output [1, 5]
//     cout << rangeTree.query(7) << endl;  // should output [6, 8]
//     cout << rangeTree.query(9) << endl;  // should output [10, 12]
//     cout << rangeTree.query(13) << endl; // should output [0, 0]

//     return 0;
// }
