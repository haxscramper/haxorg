#pragma once

#include <hstd/system/all.hpp>
#include <hstd/stdlib/Slice.hpp>
#include <hstd/system/string_convert.hpp>
#include <span>

template <typename T>
class Span : public std::span<T> {
  public:
    using std::span<T>::span; // Inherit constructor
    using std::span<T>::size;
    using std::span<T>::data;
    using std::span<T>::operator[];

    Span(T* data, std::size_t size) : std::span<T>(data, size) {}

    /// \brief Get data at specified offset from the current 'position' if
    /// it is available (offset fits in size) or `nullptr` otherwise.
    ///
    /// \note This method assumes there is nothing outside of the current
    /// view of the span, which might be incorrect in some scenarios (like
    /// cutting `[1, 2]` out of `[1, 2, 3, 4, 5]`) but avoid creation of
    /// dangling pointers.
    T* dataAtOffset(int offset) {
        if (offset < size() && data() != nullptr) {
            return data() + offset;
        } else {
            return nullptr;
        }
    }

    bool hasData() const { return data() != nullptr && 0 < size(); }

    /// \brief Move current span 'forward', updating data and size by a
    /// certain number of pointer steps.
    void moveStart(
        ///< Number of elements to move step forward
        int steps,
        ///< Whether size of the span should be fixed (moving window) or
        ///< should the end position stay fixed instead (flexible window)
        bool fixSize = false,
        /// Maximum possible end point position
        std::size_t maxEndPos = high<std::size_t>()) {
        if (fixSize) {
            *this = Span<T>(
                dataAtOffset(steps), std::clamp(size(), 0uz, maxEndPos));
        } else {
            *this = Span<T>(
                dataAtOffset(steps),
                std::clamp(
                    std::clamp(size() - steps, 0uz, size()),
                    0uz,
                    maxEndPos));
        }
    }

    /// \brief Move end part of the current span 'forward', updating data
    /// and size in the same manner as `moveStart`.
    void moveEnd(
        /// Number of steps for the end element
        int steps,
        /// Whether size should be fixed. Behavior is exactly the same as
        /// start mover function. Defaults to behavior that provides window
        /// with flexible size: start stays put and end moves in different
        /// directions.
        bool        fixSize   = false,
        std::size_t maxEndPos = high<std::size_t>()) {
        if (fixSize) {
            *this = Span<T>(
                dataAtOffset(steps),
                std::clamp(
                    size() + steps,
                    0uz,
                    std::clamp(size(), 0uz, maxEndPos)));
        } else {
            *this = Span<T>(
                data(),
                std::clamp(
                    std::clamp(size() + steps, 0uz, size()),
                    0uz,
                    maxEndPos));
        }
    }


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
};

template <typename T>
std::ostream& operator<<(std::ostream& os, Span<T> const& value) {
    os << "[" << join(os, ", ", value) << "]";
    return os;
}
