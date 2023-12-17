#pragma once

import hstd.system.all;
import hstd.system.string_convert;
import hstd.stdlib.SetCommon;

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


    inline bool contains(CR<T> key) const { return count(key) != 0; }
    void        incl(CR<T> value) { insert(value); }
    void        excl(CR<T> value) { erase(value); }

    void incl(CR<UnorderedSet<T>> other) {
        for (const auto& it : other) {
            this->incl(it);
        }
    }

    void excl(CR<UnorderedSet<T>> value) {
        for (const auto& it : value) {
            this->erase(it);
        }
    }
};

template <typename T>
struct std::formatter<UnorderedSet<T>> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const UnorderedSet<T>& p, FormatContext& ctx) {
        return "{" << join(", ", p) << "}";
    }
};
