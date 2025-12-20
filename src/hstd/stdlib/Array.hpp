#pragma once

#include <hstd/stdlib/Slice.hpp>
#include <hstd/system/all.hpp>
#include <hstd/system/generator.hpp>

#include <span>
#include <array>

namespace hstd {


template <typename T, int Size>
struct Array : std::array<T, Size> {
    using std::array<T, Size>::array; // Inherit constructor
    using std::array<T, Size>::size;
    using std::array<T, Size>::at;
    using std::array<T, Size>::operator[];
    using std::array<T, Size>::back;
    using std::array<T, Size>::begin;
    using std::array<T, Size>::end;

    Array() : std::array<T, Size>() {}

    operator Ref<std::array<T, Size>>() {
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


template <ImplementsOrd Key, typename Val>
    requires(sizeof(Key) <= sizeof(unsigned short))
struct TypArray : public Array<Val, pow_v<2, 8 * sizeof(Key)>::res> {
    using Base = Array<Val, pow_v<2, 8 * sizeof(Key)>::res>;
    using Base::at;
    using Base::operator[];

    TypArray() {}

    TypArray(std::initializer_list<Pair<Key, Val>> items) {
        for (const auto& [key, val] : items) { at(key) = val; }
    }

    Val& at(CR<Key> value) {
        return Base::at(value_domain<Key>::ord(value));
    }

    CR<Val> at(CR<Key> value) const {
        return Base::at(value_domain<Key>::ord(value));
    }

    Val& operator[](CR<Key> value) {
        return Base::operator[](value_domain<Key>::ord(value));
    }

    CR<Val> operator[](CR<Key> value) const {
        return Base::operator[](value_domain<Key>::ord(value));
    }


    generator<Pair<Key, Val const*>> pairs() const {
        for (auto i = value_domain<Key>::low();
             i <= value_domain<Key>::high();
             i = value_domain<Key>::succ(i)) {
            co_yield {i, &this->operator[](i)};
        }
    }

    generator<Pair<Key, Val*>> pairs() {
        for (auto i = value_domain<Key>::low();
             i <= value_domain<Key>::high();
             i = value_domain<Key>::succ(i)) {
            co_yield {i, &this->operator[](i)};
        }
    }
};

} // namespace hstd

template <typename T, int Size>
struct std::formatter<hstd::Array<T, Size>> : std::formatter<std::string> {
    template <typename FormatContext>
    typename FormatContext::iterator format(
        hstd::Array<T, Size> const& p,
        FormatContext&              ctx) const {
        std::formatter<std::string> fmt;
        fmt.format("[", ctx);
        fmt.format(join(", ", p), ctx);
        return fmt.format("]", ctx);
    }
};
