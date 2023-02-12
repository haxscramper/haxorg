#pragma once

#include <hstd/stdlib/charsets.hpp>
#include <hstd/system/generator.hpp>
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
        case '\x00': return {"␀", "[NUL]"}; // Null character
        case '\x01': return {"␁", "[SOH]"}; // Start of header
        case '\x02': return {"␂", "[STX]"}; // Start of text
        case '\x03': return {"␃", "[ETX]"}; // End of text
        case '\x04': return {"␄", "[EOT]"}; // End of transmission
        case '\x05': return {"␅", "[ENQ]"}; // Enquiry
        case '\x06': return {"␆", "[ACK]"}; // Acknowledge
        case '\x07': return {"␇", "[BEL]"}; // Bell
        case '\x08': return {"␈", "[BS]"};  // Backspace
        case '\x09': return {"␉", "[HT]"};  // Horizontal tab
        case '\x0A': return {"␤", "[LF]"};  // Line feed
        case '\x0B': return {"␋", "[VT]"};  // Vertical tab
        case '\x0C': return {"␌", "[FF]"};  // Form feed
        case '\x0D': return {"␍", "[CR]"};  // Carriage return
        case '\x0E': return {"␎", "[SO]"};  // Shift out
        case '\x0F': return {"␏", "[SI]"};  // Shift in
        case '\x10': return {"␐", "[DLE]"}; // Data link escape
        case '\x11': return {"␑", "[DC1]"}; // Device control 1
        case '\x12': return {"␒", "[DC2]"}; // Device control 2
        case '\x13': return {"␓", "[DC3]"}; // Device control 3
        case '\x14': return {"␔", "[DC4]"}; // Device control 4
        case '\x15': return {"␕", "[NAK]"}; // Negative acknowledge
        case '\x16': return {"␖", "[SYN]"}; // Synchronous idle
        case '\x17': return {"␗", "[ETB]"}; // End of transmission block
        case '\x18': return {"␘", "[CAN]"}; // Cancel
        case '\x19': return {"␙", "[EM]"};  // End of medium
        case '\x1A': return {"␚", "[SUB]"}; // Substitute
        case '\x1B': return {"␛", "[ESC]"}; // Escape
        case '\x1C': return {"␜", "[FS]"};  // File separator
        case '\x1D': return {"␝", "[GS]"};  // Group separator
        case '\x1E': return {"␞", "[RS]"};  // Record separator
        case '\x1F': return {"␟", "[US]"};  // Unit separator
        case '\x7f': return {"␡", "[DEL]"}; // Delete
        case ' ': return {"␣", "[SPC]"};    // Space
        default: return {std::to_string(ch), std::to_string(ch)};
    }
}

inline Vec<Str> split_keep_separator(
    const Str&   str,
    IntSet<char> sep = {' '}) {
    Vec<Str> result;
    int      prev = 0, curr = 0;
    while (curr < str.length()) {
        if (sep.contains(str[curr])) {
            if (prev != curr) {
                result.push_back(str.substr(prev, curr - prev));
            }
            prev = curr;
            while (curr < str.length() - 1 && str[curr + 1] == str[curr]) {
                curr++;
            }
            result.push_back(str.substr(prev, curr - prev + 1));
            curr++;
            prev = curr;
        } else {
            curr++;
        }
    }
    if (prev < curr) {
        result.push_back(str.substr(prev, curr - prev));
    }
    return result;
}

inline Str strip(
    CR<Str>     string,
    CR<CharSet> leading,
    CR<CharSet> trailing) {
    if (0 < string.size()) {
        Span<char> view = string.toSpan();
        auto       end  = &string.back();
        while (leading.contains(view.at(0))) {
            view.moveStart(1, end);
        }
        while (trailing.contains(view.at(1_B))) {
            view.moveEnd(-1, end);
        }
        return Str(view);
    } else {
        return Str();
    }
}
