#pragma once

#include <hstd/stdlib/charsets.hpp>
#include <hstd/stdlib/Str.hpp>

inline Str normalize(CR<Str> in) {
    Str res;
    for (char c : in) {
        if (!(c == '_' || c == '-')) {
            if (charsets::LowerAsciiLetters.contains(c)) {
                res += c;
            } else if (charsets::HighAsciiLetters.contains(c)) {
                res += tolower(c);
            }
        }
    }
    return res;
}

inline Str repeat(CR<Str> str, int count) {
    Str res;
    res.reserve(str.size() * count);
    for (int i = 0; i < count; ++i) {
        res += str;
    }
    return res;
}


template <typename Iterable>
void join(std::ostream& os, CR<Str> sep, Iterable list) {
    int index = 0;
    for (const auto& it : list) {
        if (0 < index) {
            os << sep;
        }
        os << it;
        ++index;
    }
}

template <typename Iterable>
std::string join(CR<Str> sep, Iterable list) {
    std::stringstream os;
    join(os, sep, list);
    return os.str();
}
