#pragma once

#include <hstd/system/all.hpp>
#include <hstd/stdlib/Slice.hpp>
#include <hstd/system/string_convert.hpp>
#include <span>
#include <optional>
#include <hstd/system/Formatter.hpp>


namespace hstd {


template <typename T>
class Span : public std::span<T> {
  public:
    using std::span<T>::span; // Inherit constructor
    using std::span<T>::data;
    using std::span<T>::operator[];


    // Why override to unsigned? Because `size() - 1` should not equal
    // 'crash your app'. Also I guess that span of 2147483647 elements is
    // just abour right for what most people do, and those who don't will
    // use custom data structures that better fit their needs anyway.
    int size() const {
        return std::clamp(
            std::span<T>::size(),
            0uz,
            static_cast<std::size_t>(value_domain<int>::high()));
    }

    Span(T* data, int size) : std::span<T>(data, size) {}
    T const* cdata() const { return data(); }


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
    bool empty() const { return !(0 < size()); }


    int clampSize(int size, T const* data, T const* end) const {
        LOGIC_ASSERTION_CHECK(data <= end, "");
        LOGIC_ASSERTION_CHECK(data != nullptr, "");
        LOGIC_ASSERTION_CHECK(end != nullptr, "");
        auto d_raw    = std::distance(data, end);
        int  distance = static_cast<int>(d_raw + 1);
        return std::clamp<int>(size, 0, distance);
    }

    /// \brief Move current span 'forward', updating data and size by a
    /// certain number of pointer steps.
    void moveStart(
        ///< Number of elements to move step forward
        int steps,
        /// Maximum possible end point position
        T const* maxEnd,
        ///< Whether size of the span should be fixed (moving window) or
        ///< should the end position stay fixed instead (flexible window)
        bool fixSize = false) {
        auto data = dataAtOffset(steps);
        if (data != nullptr) {
            int oldSize = size();
            int newSize = fixSize
                            ? clampSize(size(), data, maxEnd)
                            : clampSize(size() - steps, data, maxEnd);

            assert(0 <= newSize && newSize <= oldSize);

            *this = Span<T>(data, newSize);
        } else {
            *this = Span<T>(nullptr, 0);
        }
    }

    /// \brief Move end part of the current span 'forward', updating data
    /// and size in the same manner as `moveStart`. By default (non-fixed
    /// size) this function effectively acts as `changeSize()`
    void moveEnd(
        /// Number of steps for the end element
        int      steps,
        T const* maxEnd,
        /// Whether size should be fixed. Behavior is exactly the same as
        /// start mover function. Defaults to behavior that provides window
        /// with flexible size: start stays put and end moves in different
        /// directions.
        bool fixSize = false) {
        if (fixSize) {
            auto data = dataAtOffset(steps);
            *this = Span<T>(data, clampSize(size() + steps, data, maxEnd));
        } else {
            *this = Span<T>(
                data(), clampSize(size() + steps, data(), maxEnd));
        }
    }


    /// \brief Access span of elements in mutable vector
    template <typename A, typename B>
    Span<T> at(CR<HSlice<A, B>> s, bool checkRange = true) {
        const auto [start, end] = getSpan(size(), s, checkRange);
        return Span<T>(this->data() + start, end - start + 1);
    }

    /// \brief  Access span of elements in immutable vector
    template <typename A, typename B>
    Span<T> at(CR<HSlice<A, B>> s, bool checkRange = true) const {
        const auto [start, end] = getSpan(size(), s, checkRange);
        return Span<T>(this->data() + start, end - start + 1);
    }

    /// \brief Check if vector has enough elements to access index \arg idx
    bool has(int idx) const { return 0 <= idx && idx < size(); }
    bool has(BackwardsIndex idx) const { return has(size() - idx.value); }


    /// \brief Get reference wrapper to a value at specified index or empty
    /// option if the index is out of range
    std::optional<Rw<T>> get(int index) {
        if (has(index)) {
            return at(index);
        } else {
            return std::nullopt;
        }
    }

    /// \brief Overload for constant vector
    std::optional<CRw<T>> get(int index) const {
        if (has(index)) {
            return at(index);
        } else {
            return std::nullopt;
        }
    }

    int index(BackwardsIndex idx) const {
        return this->size() - idx.value;
    }

    /// \brief Get reference wrapper to a value at specified index or empty
    /// option if the index is out of range
    std::optional<Rw<T>> get(BackwardsIndex idx) {
        return get(index(idx));
    }

    /// \brief Overload for constant vector
    std::optional<CRw<T>> get(BackwardsIndex idx) const {
        return get(index(idx));
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
    Span<T> operator[](CR<HSlice<A, B>> s) const {
#ifdef DEBUG
        return at(s, true);
#else
        return at(s, false);
#endif
    }

    T& operator[](BackwardsIndex idx) {
        return (*this)[this->size() - idx.value];
    }

    T&    at(int idx) { return (*this)[idx]; }
    CR<T> at(int idx) const { return (*this)[idx]; }

    T& at(BackwardsIndex idx) {
        return this->at(this->size() - idx.value);
    }
};


template <std::random_access_iterator Iter>
static auto IteratorSpan(Iter begin, Iter end)
    -> Span<typename Iter::value_type> {
    return Span<typename Iter::value_type>{
        const_cast<Iter::value_type*>(&*begin),
        static_cast<int>(std::distance(begin, end))};
}


} // namespace hstd

template <typename T>
struct std::formatter<hstd::Span<T>> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        const hstd::Span<T>& p,
        FormatContext&       ctx) const {
        hstd::fmt_ctx("[", ctx);
        for (int i = 0; i < p.size(); ++i) {
            if (0 < i) { hstd::fmt_ctx(", ", ctx); }
            hstd::fmt_ctx(p.at(i), ctx);
        }

        return hstd::fmt_ctx("]", ctx);
    }
};
