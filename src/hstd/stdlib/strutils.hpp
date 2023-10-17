#pragma once

#include <hstd/stdlib/charsets.hpp>
#include <hstd/system/generator.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <sstream>


template <typename T>
std::string join(CR<std::string> sep, generator<T>& list) {
    std::string os;
    int         index = 0;
    for (const auto& it : list) {
        if (0 < index) {
            os += sep;
        }
        os << std::format("{}", it);
        ++index;
    }
    return os;
}


template <typename T>
std::string join(CR<std::string> sep, generator<T>&& list) {
    auto tmp = std::move(list);
    return join(sep, tmp);
}

/// Get visible name of the character.
Pair<std::string, std::string> visibleName(char ch);
Str indent(CR<Str> str, int spaces, char space = ' ', Str prefix = "");

Vec<Str> visibleUnicodeName(std::string str, bool useUnicode = true);
Vec<Str> split_keep_separator(const Str& str, CharSet sep = {' '});
Str      strip(CR<Str> string, CR<CharSet> leading, CR<CharSet> trailing);
Vec<Str> split(CR<Str> str, char ch);
std::string right_aligned(CR<std::string> str, int n, char c = ' ');
std::string left_aligned(CR<std::string> str, int n, char c = ' ');
Str         normalize(CR<Str> in);
Str         repeat(CR<Str> str, int count);
std::string escape_for_write(std::string const& str, bool quote = true);

enum class AsciiStyle
{
    Regular             = 0,
    Inverted            = 1,
    Fraktur             = 2,
    BoldFraktur         = 3,
    DoubleStruck        = 4,
    Bold                = 5,
    Italic              = 6,
    BoldItalic          = 7,
    Script              = 8,
    BoldScript          = 9,
    SansSerif           = 10,
    BoldSansSerif       = 11,
    ItalicSansSerif     = 12,
    ItalicBoldSansSerif = 13,
    Monospace           = 14
};


std::string styledUnicodeMapping(char ch, AsciiStyle style);
std::string styledUnicodeMapping(std::string const& str, AsciiStyle style);

inline char* strdup(std::string const& str) { return strdup(str.c_str()); }
