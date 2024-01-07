#pragma once

#include <hstd/stdlib/charsets.hpp>
#include <hstd/system/generator.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <sstream>


template <typename T>
Str join(CR<Str> sep, generator<T>& list) {
    Str os;
    int index = 0;
    for (const auto& it : list) {
        if (0 < index) {
            os += sep;
        }
        os += std::format("{}", it);
        ++index;
    }
    return os;
}


template <typename T>
Str join(CR<Str> sep, generator<T>&& list) {
    auto tmp = std::move(list);
    return join(sep, tmp);
}

/// Get visible name of the character.
Pair<Str, Str> visibleName(char ch);
Str indent(CR<Str> str, int spaces, char space = ' ', Str prefix = "");

Vec<Str> visibleUnicodeName(Str str, bool useUnicode = true);
Vec<Str> split_keep_separator(const Str& str, CharSet sep = {' '});
Str      strip(CR<Str> string, CR<CharSet> leading, CR<CharSet> trailing);
Vec<Str> split(CR<Str> str, char ch);
Str      right_aligned(CR<Str> str, int n, char c = ' ');
Str      left_aligned(CR<Str> str, int n, char c = ' ');
Str      normalize(CR<Str> in);
Str      repeat(CR<Str> str, int count);
Str      escape_for_write(Str const& str, bool quote = true);
int      rune_length(const std::string& str);
std::vector<std::string> rune_chunks(const std::string& str);


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


template <>
struct value_domain<AsciiStyle>
    : public value_domain_ungapped<
          AsciiStyle,
          AsciiStyle::Regular,
          AsciiStyle::Monospace> {};

Str styledUnicodeMapping(char ch, AsciiStyle style);
Str styledUnicodeMapping(Str const& str, AsciiStyle style);

inline char* strdup(std::string const& str) { return strdup(str.c_str()); }
