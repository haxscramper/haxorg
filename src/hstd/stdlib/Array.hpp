#include <hstd/stdlib/Slice.hpp>
#include <hstd/system/all.hpp>

template <typename T, int Size>
struct Array : std::array<T, Size> {
    using std::array<T, Size>::array; // Inherit constructor
    using std::array<T, Size>::size;
    using std::array<T, Size>::at;
    using std::array<T, Size>::operator[];
    using std::array<T, Size>::back;
    using std::array<T, Size>::begin;
    using std::array<T, Size>::end;

    operator R<std::array<T, Size>>() {
        return static_cast<std::array<T, Size>>(*this);
    }

    operator CR<std::array<T, Size>>() const {
        return static_cast<std::array<T, Size>>(*this);
    }

    bool has(int idx) const { return idx < size(); }

    template <typename A, typename B>
    std::span<T> at(CR<HSlice<A, B>> s, bool checkRange = true) {
        const auto [start, end] = getSpan(size(), s, checkRange);
        return std::span(this->data() + start, end - start + 1);
    }

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

    int high() const { return size() - 1; }
    int indexOf(CR<T> item) const { return index_of(*this, item); }
};
