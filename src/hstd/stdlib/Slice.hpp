#pragma once

#include <hstd/system/basic_templates.hpp>
#include <hstd/system/string_convert.hpp>

#include <hstd/system/exceptions.hpp>
#include <hstd/stdlib/Pair.hpp>
#include <hstd/stdlib/BackwardsIndex.hpp>
#include <format>

namespace hstd {
template <typename A, typename B>
struct HSlice {
    A first;
    B last;

    bool operator==(CR<HSlice<A, B>> other) const {
        return first == other.first && last == other.last;
    }
};


template <typename T>
struct Slice;

template <typename T>
constexpr Slice<T> slice(CR<T> first, CR<T> last);

template <typename T>
struct Slice : public HSlice<T, T> {
    using HSlice<T, T>::first;
    using HSlice<T, T>::last;
    using HSlice<T, T>::operator==;

    bool     contains(T val) const { return first <= val && val <= last; }
    bool     isValid() const { return first <= last; }
    bool     isPoint() const { return first == last; }
    Slice<T> narrow(Slice<T> const& other) {
        return slice(
            // If the other boundary is in the range then move ot to the
            // right as maximum as possible
            contains(other.first) ? std::max(other.first, first) : first,
            // Move right boundary as left/minimum as possible
            contains(other.last) ? std::min(other.last, last) : last
            //
        );
    }

    bool isBefore(T const& value) const { return value < first; }

    bool isAfter(T const& value) const { return last < value; }

    void expand(T const& other) {
        if (isBefore(other)) {
            first = other;
        } else if (isAfter(other)) {
            last = other;
        }
    }

    Slice<T> expanded(Slice<T> const& other) const {
        return slice(
            // Leftmost of two boundaries -- extend left
            std::min(other.first, first),
            // Rightmost of two boundaries -- extend right
            std::max(other.last, last) //
        );
    }

    /// \brief Both start and end of the other slice are contained in the
    /// *inclusive* range [first, last]
    bool contains(CR<Slice> other) const {
        return contains(other.first) && contains(other.last);
    }

    std::optional<Slice<T>> overlap(const Slice<T>& other) const {
        if (first < other.last && other.first < last) {
            int overlap_start = std::max(first, other.first);
            int overlap_end   = std::min(last, other.last);
            return Slice<int>{overlap_start, overlap_end};
        } else {
            return std::nullopt;
        }
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

        iterator(T value, T _last, bool pastLast = false)
            : now(value), last(_last), pastLast(pastLast) {}
        iterator() : pastLast(true) {}

        T operator*() { return now; }

        iterator& operator++() {
            // If we are on the last element and are trying to move to the
            // "next" position short-circuit all edits into "on the 'past
            // last' element"
            if (now == last || pastLast) {
                pastLast = true;
            } else {
                now = value_domain<T>::succ(now);
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
    iterator end() const { return iterator(first, last, true); }
};

/// Return homogeneous inclusive slice of values
template <typename T>
constexpr Slice<T> slice(CR<T> first, CR<T> last) {
    if (!(first <= last)) {
        if constexpr (std::is_integral_v<T> && sizeof(T) <= sizeof(u64)) {
            if constexpr (std::is_signed_v<T>) {
                throw RangeError::init(
                    "Expected first <= last but got first='"
                    + std::to_string(static_cast<i64>(first)) + "' last='"
                    + std::to_string(static_cast<i64>(last)) + "'");
            } else {
                throw RangeError::init(
                    "Expected first <= last but got first='"
                    + std::to_string(static_cast<u64>(first)) + "' last='"
                    + std::to_string(static_cast<u64>(last)) + "'");
            }

        } else {
            throw RangeError::init(
                "Expected first <= last but got <unformattable type>");
        }
    }
    return {first, last};
}


/// Another construction function for homogeneous slices, should be used if
/// both arguments must be coerced to the same type.
template <typename T>
constexpr Slice<T> slice1(CR<T> first, CR<T> last) {
    return slice(first, last);
}

template <typename T>
constexpr Slice<int> sliceSize(T const& value) {
    return slice<int>(0, value.size() - 1);
}

template <typename T>
constexpr Slice<T> sliceT()
    requires ImplementsLow<T> && ImplementsHigh<T>
{
    return slice1<T>(value_domain<T>::low(), value_domain<T>::high());
}

/// Return heterogeneous inclusive slice of values
template <typename A, typename B>
HSlice<A, B> slice(CR<A> first, CR<B> last) {
    return {.first = first, .last = last};
}

} // namespace hstd


template <typename A, typename B>
struct std::formatter<hstd::HSlice<A, B>> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        hstd::HSlice<A, B> const& p,
        FormatContext&            ctx) const {
        std::formatter<std::string> fmt;
        fmt.format("[", ctx);
        std::format_to(ctx.out(), "{}", p.first);
        fmt.format("..", ctx);
        std::format_to(ctx.out(), "{}", p.last);
        return fmt.format("]", ctx);
    }
};

template <typename T>
struct std::formatter<hstd::Slice<T>> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        hstd::Slice<T> const& p,
        FormatContext&        ctx) const {
        std::formatter<std::string> fmt;
        std::formatter<T>           fmt_t;
        fmt.format("[", ctx);
        fmt_t.format(p.first, ctx);
        fmt.format("..", ctx);
        fmt_t.format(p.last, ctx);
        return fmt.format("]", ctx);
    }
};


template <typename T>
struct std::hash<hstd::Slice<T>> {
    std::size_t operator()(hstd::Slice<T> const& it) const noexcept {
        std::size_t result = 0;
        hax_hash_combine(result, it.first);
        hax_hash_combine(result, it.last);
        return result;
    }
};


namespace hstd {
template <typename A, typename B>
Pair<int, int> getSpan(
    int          containerSize, /// Size of the container to get span over
    HSlice<A, B> s,             /// Span slice
    bool         checkRange = true /// Ensure that slice does not go out of
                                   /// container bounds9
) {
    int        startPos{};
    int        endPos{};
    const auto size = containerSize;

    if constexpr (std::is_same_v<A, BackwardsIndex>) {
        startPos = size - s.first.value;
    } else {
        startPos = s.first;
    }

    if constexpr (std::is_same_v<B, BackwardsIndex>) {
        endPos = size - s.last.value;
    } else {
        endPos = s.last;
    }

    if (checkRange
        && !(
            (0 <= startPos && startPos < size)
            && (0 <= endPos && endPos < size))) {
        throw RangeError::init(std::format(
            "Container index is out of range: real span range is {}..{} "
            "computed from {}, but full extent length is only {}",
            startPos,
            endPos,
            s,
            size));
    }

    return {startPos, endPos};
}

} // namespace hstd
