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
