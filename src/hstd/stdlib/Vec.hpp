#pragma once

#include <hstd/system/all.hpp>
#include <hstd/stdlib/Slice.hpp>
#include <hstd/stdlib/Span.hpp>

#include <vector>
#include <span>

template <typename T>
class Vec : public std::vector<T> {
  public:
    using Base = std::vector<T>;
    using std::vector<T>::vector; // Inherit constructor from
                                  // std::vector

    using Base::at;
    using Base::operator[];
    using Base::back;
    using Base::begin;
    using Base::end;
    using Base::insert;
    using Base::pop_back;
    using Base::push_back;

    static Vec<T> FromValue(CR<Vec<T>> values) { return values; }


    int size() const {
        return std::clamp(
            Base::size(), 0uz, static_cast<std::size_t>(::high<int>()));
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

    void pop_back() {
        assert(0 < size());
        Base::pop_back();
    }

    T pop_back_v() {
        assert(0 < size());
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
QTextStream& operator<<(QTextStream& os, Vec<T> const& value) {
    os << "[" << join(os, ", ", value) << "]";
    return os;
}

template <typename T>
using CVec = CR<Vec<T>>;
