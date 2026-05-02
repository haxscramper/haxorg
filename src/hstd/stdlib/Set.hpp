#pragma once

#include <hstd/system/all.hpp>
#include <hstd/stdlib/SetCommon.hpp>
#include <unordered_set>
#include <hstd/stdlib/Vec.hpp>

namespace hstd {

template <typename T>
struct UnorderedSet
    : public std::unordered_set<T>
    , public SetBase<UnorderedSet<T>, T> {
    using Base = std::unordered_set<T>;
    using API  = SetBase<UnorderedSet<T>, T>;
    using API::operator-;
    using API::operator&;
    using API::operator^;
    using API::operator|;
    using API::operator+;
    using API::operator<;
    using API::operator<=;

    using Base::Base;
    using Base::begin;
    using Base::count;
    using Base::end;
    using Base::erase;
    using Base::insert;


    inline bool contains(T const& key) const { return count(key) != 0; }
    void        incl(T const& value) { insert(value); }
    void        excl(T const& value) { erase(value); }

    void incl(UnorderedSet<T> const& other) {
        for (const auto& it : other) { this->incl(it); }
    }

    void excl(UnorderedSet<T> const& value) {
        for (const auto& it : value) { this->erase(it); }
    }

    hstd::Vec<T> items() const { return hstd::Vec<T>{begin(), end()}; }
};


} // namespace hstd


namespace hstd {
template <typename T>
struct value_metadata<hstd::UnorderedSet<T>> {
    static bool isEmpty(UnorderedSet<T> const& value) {
        return value.empty();
    }
};
} // namespace hstd
