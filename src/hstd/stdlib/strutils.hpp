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


inline Str indent(
    CR<Str> str,
    int     spaces,
    char    space  = ' ',
    Str     prefix = "") {
    auto lines = split(str, '\n');
    for (auto& line : lines) {
        line = prefix + repeat(Str(space), spaces) + line;
    }
    return join("\n", lines);
}


template <typename T>
std::ostream& join(
    std::ostream&   os,
    CR<std::string> sep,
    generator<T>&   list) {
    int index = 0;
    for (const auto& it : list) {
        if (0 < index) {
            os << sep;
        }
        os << to_string(it);
        ++index;
    }
    return os;
}

template <typename T>
std::ostream& join(
    std::ostream&   os,
    CR<std::string> sep,
    generator<T>&&  list) {
    auto tmp = std::move(list);
    return join(os, sep, tmp);
}


template <typename T>
std::string join(CR<std::string> sep, generator<T>& list) {
    std::stringstream os;
    join(os, sep, list);
    return os.str();
}


template <typename T>
std::string join(CR<std::string> sep, generator<T>&& list) {
    auto tmp = std::move(list);
    join(sep, tmp);
}

/// Get visible name of the character.
inline Pair<Str, Str> visibleName(char ch) {
    switch (ch) {
        case '\x00': return {"␀", "[NUL]"};
        case '\x01': return {"␁", "[SOH]"};
        case '\x02': return {"␂", "[STX]"};
        case '\x03': return {"␃", "[ETX]"};
        case '\x04': return {"␄", "[EOT]"};
        case '\x05': return {"␅", "[ENQ]"};
        case '\x06': return {"␆", "[ACK]"};
        case '\x07': return {"␇", "[BEL]"};
        case '\x08': return {"␈", "[BS]"};
        case '\x09': return {"␉", "[HT]"};
        case '\x0A': return {"␤", "[LF]"};
        case '\x0B': return {"␋", "[VT]"};
        case '\x0C': return {"␌", "[FF]"};
        case '\x0D': return {"␍", "[CR]"};
        case '\x0E': return {"␎", "[SO]"};
        case '\x0F': return {"␏", "[SI]"};
        case '\x10': return {"␐", "[DLE]"};
        case '\x11': return {"␑", "[DC1]"};
        case '\x12': return {"␒", "[DC2]"};
        case '\x13': return {"␓", "[DC3]"};
        case '\x14': return {"␔", "[DC4]"};
        case '\x15': return {"␕", "[NAK]"};
        case '\x16': return {"␖", "[SYN]"};
        case '\x17': return {"␗", "[ETB]"};
        case '\x18': return {"␘", "[CAN]"};
        case '\x19': return {"␙", "[EM]"};
        case '\x1A': return {"␚", "[SUB]"};
        case '\x1B': return {"␛", "[ESC]"};
        case '\x1C': return {"␜", "[FS]"};
        case '\x1D': return {"␝", "[GS]"};
        case '\x1E': return {"␞", "[RS]"};
        case '\x1F': return {"␟", "[US]"};
        case '\x7f': return {"␡", "[DEL]"};
        case ' ': return {"␣", "[SPC]"}; // Space
        default: return {std::to_string(ch), std::to_string(ch)};
    }
}
