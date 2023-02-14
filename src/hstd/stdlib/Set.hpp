#pragma once

#include <hstd/system/all.hpp>
#include <hstd/system/string_convert.hpp>
#include <unordered_set>
#include <set>

template <typename T>
struct UnorderedSet : public std::unordered_set<T> {
    using Base = std::unordered_set<T>;
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


    UnorderedSet<T> operator&(CR<UnorderedSet<T>> other) {
        UnorderedSet<T> result;
        for (const auto& it : other) {
            if (this->contains(it)) {
                result.incl(it);
            }
        }
        return result;
    }

    UnorderedSet<T> operator^(CR<UnorderedSet<T>> other) {
        UnorderedSet<T> result;
        for (const auto& it : other) {
            if (!this->contains(it)) {
                result.incl(it);
            }
        }
        for (const auto& it : *this) {
            if (!other.contains(it)) {
                result.incl(it);
            }
        }

        return result;
    }

    UnorderedSet<T> operator+(CR<UnorderedSet<T>> other) {
        UnorderedSet<T> result = *this;
        result.incl(other);
        return result;
    }

    UnorderedSet<T> operator-(CR<UnorderedSet<T>> other) {
        UnorderedSet<T> result = *this;
        result.excl(other);
        return result;
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, UnorderedSet<T> const& value) {
    return os << "{" << join(os, ", ", value) << "}";
}
