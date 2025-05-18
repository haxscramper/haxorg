#pragma once

#include <hstd/stdlib/charsets.hpp>
#include <hstd/system/generator.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <sstream>

namespace hstd {

template <typename T>
Str join(CR<Str> sep, generator<T>& list) {
    Str os;
    int index = 0;
    for (const auto& it : list) {
        if (0 < index) { os += sep; }
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

Vec<Str> visibleUnicodeName(std::string_view str, bool useUnicode = true);
Vec<Str> visibleUnicodeName(Str const& str, bool useUnicode = true);
Vec<Str> split_keep_separator(const Str& str, CharSet sep = {' '});
Str      strip(CR<Str> string, CR<CharSet> leading, CR<CharSet> trailing);
Str      lstrip(CR<Str> string, CR<CharSet> chars);
Str      rstrip(CR<Str> string, CR<CharSet> chars);
Vec<Str> split(CR<Str> str, char ch);
Str      right_aligned(CR<Str> str, int n, char c = ' ');
Str      left_aligned(CR<Str> str, int n, char c = ' ');
Str      normalize(CR<Str> in);
Str      repeat(CR<Str> str, int count);
Str      escape_for_write(Str const& str, bool quote = true);
int      rune_length(const std::string& str);
std::vector<std::string> rune_chunks(const std::string& str);
bool iequals(const std::string& a, const std::string& b);

/// \brief Escape string literal, converting newline and other (TODO)
/// control characters into unicode.
std::string escape_literal(std::string const& in);
std::string escape_literal(std::string_view const& in);
void validate_utf8(const std::string& str);


void replace_all(
    std::string&       str,
    const std::string& from,
    const std::string& to);

Str wrap_text(const Vec<Str>& words, int maxWidth, bool justified);


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

BOOST_DESCRIBE_ENUM(
    AsciiStyle,
    Regular,
    Inverted,
    Fraktur,
    BoldFraktur,
    DoubleStruck,
    Bold,
    Italic,
    BoldItalic,
    Script,
    BoldScript,
    SansSerif,
    BoldSansSerif,
    ItalicSansSerif,
    ItalicBoldSansSerif,
    Monospace);


template <>
struct value_domain<AsciiStyle>
    : public value_domain_ungapped<
          AsciiStyle,
          AsciiStyle::Regular,
          AsciiStyle::Monospace> {};

Str styledUnicodeMapping(char ch, AsciiStyle style);
Str styledUnicodeMapping(Str const& str, AsciiStyle style);

inline char* strdup(std::string const& str) {
    return ::strdup(str.c_str());
}

} // namespace hstd
