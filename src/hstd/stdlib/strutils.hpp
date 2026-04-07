#pragma once

#include <hstd/stdlib/charsets.hpp>
#include <hstd/system/generator.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Vec.hpp>

namespace hstd {

template <typename T>
Str join(Str const& sep, generator<T>& list) {
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
Str join(Str const& sep, generator<T>&& list) {
    auto tmp = std::move(list);
    return join(sep, tmp);
}

/// Get visible name of the character.
Pair<Str, Str> visibleName(char ch);
Str indent(Str const& str, int spaces, char space = ' ', Str prefix = "");

Vec<Str> visibleUnicodeName(std::string_view str, bool useUnicode = true);
Vec<Str> visibleUnicodeName(Str const& str, bool useUnicode = true);
Vec<Str> split_keep_separator(Str const& str, CharSet sep = {' '});
Str      strip(
    Str const&     string,
    CharSet const& leading,
    CharSet const& trailing);
Str      lstrip(Str const& string, CharSet const& chars);
Str      rstrip(Str const& string, CharSet const& chars);
Vec<Str> split(Str const& str, char ch);
Str      right_aligned(Str const& str, int n, char c = ' ');
Str      left_aligned(Str const& str, int n, char c = ' ');
Str      normalize(Str const& in);
Str      repeat(Str const& str, int count);
Str      escape_for_write(Str const& str, bool quote = true);
int      rune_length(std::string const& str);
std::vector<std::string> rune_chunks(std::string const& str);
bool iequals(std::string const& a, std::string const& b);

/// \brief Escape string literal, converting newline and other (TODO)
/// control characters into unicode.
std::string escape_literal(std::string const& in);
std::string escape_literal(std::string_view const& in);
void        validate_utf8(std::string const& str);


void replace_all(
    std::string&       str,
    std::string const& from,
    std::string const& to);

Str wrap_text(Vec<Str> const& words, int maxWidth, bool justified);


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
