#pragma once

#include <hstd/system/basic_templates.hpp>
#include <hstd/system/string_convert.hpp>

#include <hstd/stdlib/Pair.hpp>
#include <hstd/stdlib/BackwardsIndex.hpp>

#include <stdexcept>

template <typename A, typename B>
struct HSlice {
    A first;
    B last;

    bool operator==(CR<HSlice> other) {
        return first == other.first && last == other.last;
    }
};


template <typename T>
struct Slice : public HSlice<T, T> {
    using HSlice<T, T>::first;
    using HSlice<T, T>::last;
    bool contains(T val) const { return first <= val && val <= last; }

    /// \brief Both start and end of the other slice are contained in the
    /// *inclusive* range [first, last]
    bool contains(CR<Slice> other) const {
        return contains(other.first) && contains(other.second);
    }


    class iterator {
      private:
        T now;
        T last;
        // Because ranges are always inclusive but might encompass the
        // whole range of values dedicated 'pastLast' must be added to
        // avoid infinite looping on things such as `slice(char(0),
        // char(255))`
        bool pastLast = false;

      public:
        typedef std::forward_iterator_tag iterator_category;
        typedef T                         value_type;
        typedef T*                        pointer;
        typedef std::ptrdiff_t            difference_type;

        iterator(T value, T _last) : now(value), last(_last) {}
        iterator() : pastLast(true) {}

        T operator*() { return now; }

        iterator& operator++() {
            // If we are on the last element and are trying to move to the
            // "next" position short-circuit all edits into "on the 'past
            // last' element"
            if (now == last || pastLast) {
                pastLast = true;
            } else {
                now = succ(now);
            }
            return *this;
        }

        bool operator!=(const iterator& other) {
            if (pastLast || other.pastLast) {
                return pastLast != other.pastLast;
            } else {
                return now != other.now;
            }
        }
    };


    iterator begin() const { return iterator(first, last); }
    iterator end() const { return iterator(); }
};

/// Return homogeneous inclusive slice of values
template <typename T>
constexpr Slice<T> slice(CR<T> first, CR<T> last) {
    return {first, last};
}

/// Return heterogeneous inclusive slice of values
template <typename A, typename B>
HSlice<A, B> slice(CR<A> first, CR<B> last) {
    return {.first = first, .last = last};
}

template <typename A, typename B>
inline std::ostream& operator<<(
    std::ostream&       os,
    HSlice<A, B> const& value) {
    return os << "[" << value.first << ".." << value.last << "]";
}

template <typename A, typename B>
Pair<A, A> getSpan(
    int          containerSize, /// Size of the container to get span over
    HSlice<A, B> s,             /// Span slice
    bool         checkRange = true /// Ensure that slice does not go out of
                                   /// container bounds
) {
    const A    startPos = s.first;
    A          endPos;
    const auto size = containerSize;
    if constexpr (std::is_same_v<B, BackwardsIndex>) {
        endPos = size - s.last.value;
    } else {
        endPos = s.last;
    }

    if (checkRange
        && !(
            (0 <= startPos && startPos < size)
            && (0 <= endPos && endPos < size))) {
        throw std::out_of_range(
            "Container index is out of range: real span range is "
            + std::to_string(startPos) + ".." + std::to_string(endPos)
            + " computed from " + to_string(s)
            + ", but full extent length is only " + std::to_string(size));
    }

    return {startPos, endPos};
}
