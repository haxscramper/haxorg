#pragma once

#include <hstd/system/all.hpp>
#include <hstd/stdlib/Slice.hpp>

#include <vector>
#include <span>
#include <algorithm>

template <typename T>
class Vec : public std::vector<T> {
  public:
    using std::vector<T>::vector; // Inherit constructor from
                                  // std::vector
    using std::vector<T>::size;
    using std::vector<T>::at;
    using std::vector<T>::operator[];
    using std::vector<T>::push_back;
    using std::vector<T>::back;
    using std::vector<T>::pop_back;
    using std::vector<T>::begin;
    using std::vector<T>::end;
    using std::vector<T>::insert;

    /// \brief Append elements from \arg other vector
    void append(CR<Vec<T>> other) {
        insert(end(), other.begin(), other.end());
    }

    /// \brief copy multiple elements referred to by span to the fector
    void append(CR<std::span<T>> other) {
        insert(end(), other.begin(), other.end());
    }

    /// \brief In-place reverse of the vector content
    void reverse() { std::reverse(begin(), end()); }

    /// \brief In-place sort of the vector content
    void sort() { std::sort(begin(), end()); }

    /// \brief Return reversed copy of the vector
    Vec<T> reversed() const {
        Vec<T> result = *this;
        result.reverse();
        return result;
    }

    /// \brief Return sorted copy of the vector
    Vec<T> sorted() const {
        Vec<T> result = *this;
        result.sort();
        return result;
    }

    /// \brief Implicit conversion to the base class
    operator R<std::vector<T>>() {
        return static_cast<std::vector<T>>(*this);
    }

    /// \brief implicit conversion to the base class
    operator CR<std::vector<T>>() const {
        return static_cast<std::vector<T>>(*this);
    }

    /// \brief Check if vector has enough elements to access index \arg idx
    bool has(int idx) const { return idx < size(); }

    /// \brief Access span of elements in mutable vector
    template <typename A, typename B>
    std::span<T> at(CR<HSlice<A, B>> s, bool checkRange = true) {
        const auto [start, end] = getSpan(size(), s, checkRange);
        return std::span(this->data() + start, end - start + 1);
    }

    /// \brief  Access span of elements in immutable vector
    template <typename A, typename B>
    std::span<const T> at(CR<HSlice<A, B>> s, bool checkRange = true)
        const {
        const auto [start, end] = getSpan(size(), s, checkRange);
        return std::span(this->data() + start, end - start + 1);
    }

    template <typename A, typename B>
    std::span<T> operator[](CR<HSlice<A, B>> s) {
#ifdef DEBUG
        return at(s, true);
#else
        return at(s, false);
#endif
    }

    template <typename A, typename B>
    std::span<const T> operator[](CR<HSlice<A, B>> s) const {
#ifdef DEBUG
        return at(s, true);
#else
        return at(s, false);
#endif
    }

    T& operator[](BackwardsIndex idx) {
        return (*this)[this->size() - idx.value];
    }

    T& at(BackwardsIndex idx) {
        return this->at(this->size() - idx.value);
    }

    T pop_back_v() {
        auto result = back();
        pop_back();
        return result;
    }

    int high() const { return size() - 1; }

    int  indexOf(CR<T> item) const { return index_of(*this, item); }
    bool contains(CR<T> item) const { return indexOf(item) != -1; }
};
