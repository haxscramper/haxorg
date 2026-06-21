#pragma once

#include <hstd/stdlib/Slice.hpp>
#include <hstd/system/all.hpp>
#include <hstd/system/aux_templates.hpp>
#include <hstd/system/generator.hpp>

#include <array>
#include <span>

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

    operator std::array<T, Size> const&() const {
        return static_cast<std::array<T, Size>>(*this);
    }

    bool has(int idx) const { return idx < size(); }

    template <typename A, typename B>
    std::span<T> at(HSlice<A, B> const& s, bool checkRange = true) {
        const auto [start, end] = getSpan(size(), s, checkRange);
        return std::span(this->data() + start, end - start + 1);
    }

    template <typename A, typename B>
    std::span<const T> at(HSlice<A, B> const& s, bool checkRange = true) const {
        const auto [start, end] = getSpan(size(), s, checkRange);
        return std::span(this->data() + start, end - start + 1);
    }

    template <typename A, typename B>
    std::span<T> operator[](HSlice<A, B> const& s) {
#ifdef DEBUG
        return at(s, true);
#else
        return at(s, false);
#endif
    }

    template <typename A, typename B>
    std::span<const T> operator[](HSlice<A, B> const& s) const {
#ifdef DEBUG
        return at(s, true);
#else
        return at(s, false);
#endif
    }

    T& operator[](BackwardsIndex idx) { return (*this)[this->size() - idx.value]; }

    T& at(BackwardsIndex idx) { return this->at(this->size() - idx.value); }

    int high() const { return size() - 1; }
    int indexOf(T const& item) const { return index_of(*this, item); }
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

    Val& at(Key const& value) { return Base::at(value_domain<Key>::ord(value)); }

    Val const& at(Key const& value) const {
        return Base::at(value_domain<Key>::ord(value));
    }

    Val& operator[](Key const& value) {
        return Base::operator[](value_domain<Key>::ord(value));
    }

    Val const& operator[](Key const& value) const {
        return Base::operator[](value_domain<Key>::ord(value));
    }


    generator<Pair<Key, Val const*>> pairs() const {
        for (auto i = value_domain<Key>::low(); i <= value_domain<Key>::high();
             i      = value_domain<Key>::succ(i)) {
            co_yield {i, &this->operator[](i)};
        }
    }

    generator<Pair<Key, Val*>> pairs() {
        for (auto i = value_domain<Key>::low(); i <= value_domain<Key>::high();
             i      = value_domain<Key>::succ(i)) {
            co_yield {i, &this->operator[](i)};
        }
    }
};

} // namespace hstd

template <typename T, int Size>
struct fmt::formatter<hstd::Array<T, Size>> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }

    hstd::fmt_iter format(hstd::Array<T, Size> const& p, fmt::format_context& ctx) const {
        ::hstd::fmt_ctx("[", ctx);
        ::hstd::fmt_ctx(join(", ", p), ctx);
        return ::hstd::fmt_ctx("]", ctx);
    }
};
