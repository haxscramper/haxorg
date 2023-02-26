#pragma once

#include <hstd/system/all.hpp>
#include <hstd/stdlib/Slice.hpp>
#include <hstd/stdlib/Span.hpp>

#include <vector>
#include <span>

template <typename T>
class Vec : public std::vector<T> {
  public:
    using std::vector<T>::vector; // Inherit constructor from
                                  // std::vector
    using std::vector<T>::at;
    using std::vector<T>::operator[];
    using std::vector<T>::push_back;
    using std::vector<T>::back;
    using std::vector<T>::pop_back;
    using std::vector<T>::begin;
    using std::vector<T>::end;
    using std::vector<T>::insert;

    static Vec<T> FromValue(CR<Vec<T>> values) { return values; }


    int size() const {
        return std::clamp(
            std::vector<T>::size(),
            0uz,
            static_cast<std::size_t>(::high<int>()));
    }

    Vec() {}
    explicit Vec(int size) : std::vector<T>(size) {}
    Vec(int size, const T& value) : std::vector<T>(size, value) {}

    /// \brief Append elements from \arg other vector
    void append(CR<Vec<T>> other) {
        insert(end(), other.begin(), other.end());
    }

    /// \brief copy multiple elements referred to by span to the fector
    void append(CR<std::span<T>> other) {
        insert(end(), other.begin(), other.end());
    }

    template <typename Indexable>
    bool operator==(CR<Indexable> other) const {
        if (this->size() == other.size()) {
            for (int i = 0; i < size(); ++i) {
                if (at(i) != other.at(i)) {
                    return false;
                }
            }
            return true;
        } else {
            return false;
        }
    }

    Vec<T> operator+(CR<T> other) const {
        auto result = *this;
        result.push_back(other);
        return result;
    }

    Vec<T> operator+(CR<std::span<T>> other) const {
        auto result = *this;
        result.append(other);
        return result;
    }

    Vec<T> operator+(CR<Vec<T>> other) const {
        auto result = *this;
        result.append(other);
        return result;
    }

    /// \brief Implicit conversion to the base class
    operator Ref<std::vector<T>>() {
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
    Span<T> at(CR<HSlice<A, B>> s, bool checkRange = true) {
        const auto [start, end] = getSpan(size(), s, checkRange);
        return Span(this->data() + start, end - start + 1);
    }

    /// \brief  Access span of elements in immutable vector
    template <typename A, typename B>
    Span<const T> at(CR<HSlice<A, B>> s, bool checkRange = true) const {
        const auto [start, end] = getSpan(size(), s, checkRange);
        return Span(this->data() + start, end - start + 1);
    }

    template <typename A, typename B>
    Span<T> operator[](CR<HSlice<A, B>> s) {
#ifdef DEBUG
        return at(s, true);
#else
        return at(s, false);
#endif
    }

    template <typename A, typename B>
    Span<const T> operator[](CR<HSlice<A, B>> s) const {
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

    T const& at(BackwardsIndex idx) const {
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

    Span<T> toSpan() const {
        return Span<T>(const_cast<T*>(this->data()), size());
    }


    std::vector<T> toBase() const { return *this; }
};


template <typename T>
std::ostream& operator<<(std::ostream& os, Vec<T> const& value) {
    os << "[" << join(os, ", ", value) << "]";
    return os;
}

template <typename T>
using CVec = CR<Vec<T>>;
