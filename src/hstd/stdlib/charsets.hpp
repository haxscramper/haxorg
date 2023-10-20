#pragma once

#include <hstd/stdlib/IntSet.hpp>

using CharSet = IntSet<char>;

template <>
struct value_domain<char> {
    static inline char low() { return char(value_domain<char>::low()); }
    static inline char high() { return char(value_domain<char>::high()); }

    static inline long long int ord(char c) {
        return static_cast<long long int>(c);
    }

    static inline char succ(char c) { return char(c + 1); }
};
