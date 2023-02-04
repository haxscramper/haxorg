#pragma once

#include <hstd/stdlib/charsets.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Vec.hpp>

inline std::string right_aligned(
    CR<std::string> str,
    int             n,
    char            c = ' ') {
    std::string res;
    if (str.size() < n) {
        res.append(n - str.size(), c);
    }
    res.append(str);
    return res;
}

inline std::string left_aligned(CR<std::string> str, int n, char c = ' ') {
    auto s = str;
    if (s.size() < n) {
        s.append(n - s.size(), c);
    }
    return s;
}

inline Vec<Str> split(CR<Str> str, char separator) {
    Vec<Str> strings;

    int startIndex = 0, endIndex = 0;
    for (int i = 0; i <= str.size(); i++) {
        if (str[i] == separator || i == str.size()) {
            endIndex = i;
            Str temp;
            temp.append(str, startIndex, endIndex - startIndex);
            strings.push_back(temp);
            startIndex = endIndex + 1;
        }
    }
    return strings;
}

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


inline Str indent(CR<Str> str, int spaces, char space = ' ') {
    auto lines = split(str, '\n');
    for (auto& line : lines) {
        line = repeat(Str(space), spaces) + line;
    }
    return join("\n", lines);
}
