#pragma once

#include <hstd/system/all.hpp>
#include <hstd/stdlib/Slice.hpp>

namespace hstd {

template <typename Set, typename Val>
struct SetBase : public CRTP_this_method<Set> {
    using CRTP_this_method<Set>::_this;
    Set operator&(Set const& other) {
        Set result;
        for (const auto& it : other) {
            if (_this()->contains(it)) { result.incl(it); }
        }
        return result;
    }

    Set operator^(Set const& other) {
        Set result;
        for (const auto& it : other) {
            if (!_this()->contains(it)) { result.incl(it); }
        }
        for (const auto& it : *_this()) {
            if (!other.contains(it)) { result.incl(it); }
        }

        return result;
    }


    Set operator+(Set const& other) const {
        Set result = *_this();
        result.incl(other);
        return result;
    }

    Set operator|(Set const& other) const {
        Set result = *_this();
        result.incl(other);
        return result;
    }

    Set operator-(Set const& other) const {
        Set result = *_this();
        result.excl(other);
        return result;
    }

    constexpr void incl(Slice<Val> const& range) {
        for (const auto val : range) { _this()->incl(val); }
    }

    constexpr void excl(Slice<Val> const& range) {
        for (const auto val : range) { _this()->excl(val); }
    }

    bool operator<(Set const& other) const {
        return other.contains(*_this()) && _this()->size() < other.size();
    }

    bool operator<=(Set const& other) const {
        return other.contains(*_this());
    }
};

} // namespace hstd
