#pragma once

#include <memory>
#include <iterator>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Ptrs.hpp>

namespace hstd {

template <typename PathStep>
class RecursivePathTracker {
  private:
    struct Node {
        PathStep         value;
        hstd::SPtr<Node> parent;

        Node(const PathStep& val, hstd::SPtr<Node> p = nullptr)
            : value{val}, parent{std::move(p)} {}
    };

    hstd::SPtr<Node> current;
    int              length;

    // Helper method to traverse to a specific index
    hstd::SPtr<Node> getNodeAt(int index) const {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of range");
        }

        // Calculate how many steps back from current we need to go
        int steps_back = length - 1 - index;

        auto node = current;
        for (int i = 0; i < steps_back; ++i) { node = node->parent; }

        return node;
    }

  public:
    class iterator {
      private:
        const RecursivePathTracker* tracker;
        int                         index;

      public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = PathStep;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const PathStep*;
        using reference         = const PathStep&;

        iterator(const RecursivePathTracker* t, int idx)
            : tracker{t}, index{idx} {}

        reference operator*() const {
            return tracker->getNodeAt(index)->value;
        }

        pointer operator->() const {
            return &(tracker->getNodeAt(index)->value);
        }

        reference operator[](difference_type n) const {
            return tracker->getNodeAt(index + n)->value;
        }

        iterator& operator++() {
            ++index;
            return *this;
        }
        iterator operator++(int) {
            auto tmp = *this;
            ++index;
            return tmp;
        }
        iterator& operator--() {
            --index;
            return *this;
        }
        iterator operator--(int) {
            auto tmp = *this;
            --index;
            return tmp;
        }

        iterator& operator+=(difference_type n) {
            index += n;
            return *this;
        }
        iterator& operator-=(difference_type n) {
            index -= n;
            return *this;
        }
        iterator operator+(difference_type n) const {
            return iterator{tracker, index + n};
        }
        iterator operator-(difference_type n) const {
            return iterator{tracker, index - n};
        }

        difference_type operator-(const iterator& other) const {
            return index - other.index;
        }

        bool operator==(const iterator& other) const {
            return index == other.index;
        }
        bool operator!=(const iterator& other) const {
            return index != other.index;
        }
        bool operator<(const iterator& other) const {
            return index < other.index;
        }
        bool operator<=(const iterator& other) const {
            return index <= other.index;
        }
        bool operator>(const iterator& other) const {
            return index > other.index;
        }
        bool operator>=(const iterator& other) const {
            return index >= other.index;
        }
    };

    using const_iterator = iterator;

    RecursivePathTracker() : current{nullptr}, length{0} {}

    RecursivePathTracker(const RecursivePathTracker& other)
        : current{other.current}, length{other.length} {}

    RecursivePathTracker& operator=(const RecursivePathTracker& other) {
        current = other.current;
        length  = other.length;
        return *this;
    }

    RecursivePathTracker push(const PathStep& step) const {
        RecursivePathTracker result;
        result.current = std::make_shared<Node>(step, current);
        result.length  = length + 1;
        return result;
    }

    RecursivePathTracker pop() const {
        if (!current) { return RecursivePathTracker{}; }
        RecursivePathTracker result;
        result.current = current->parent;
        result.length  = length - 1;
        return result;
    }

    int  size() const { return length; }
    bool empty() const { return length == 0; }

    const PathStep& operator[](int index) const {
        return getNodeAt(index)->value;
    }

    const PathStep& back() const {
        if (!current) {
            throw std::out_of_range("RecursivePathTracker is empty");
        }
        return current->value;
    }

    hstd::Vec<PathStep> toVector() const {
        hstd::Vec<PathStep> result;
        result.reserve(length);

        hstd::Vec<hstd::SPtr<Node>> nodes;
        nodes.reserve(length);

        auto node = current;
        while (node) {
            nodes.push_back(node);
            node = node->parent;
        }

        for (auto it = nodes.rbegin(); it != nodes.rend(); ++it) {
            result.push_back((*it)->value);
        }

        return result;
    }

    operator hstd::Vec<PathStep>() const { return toVector(); }

    iterator begin() const { return iterator{this, 0}; }

    iterator end() const { return iterator{this, length}; }

    const_iterator cbegin() const { return begin(); }
    const_iterator cend() const { return end(); }
};
} // namespace hstd
