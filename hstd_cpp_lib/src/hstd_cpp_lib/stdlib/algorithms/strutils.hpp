#pragma once

#include <hstd_cpp_lib/stdlib/Str.hpp>
#include <hstd_cpp_lib/stdlib/charsets.hpp>
#include <hstd_cpp_lib/stdlib/containers/Vec.hpp>
#include <hstd_cpp_lib/system/generator.hpp>

namespace hstd {

template <typename T>
Str join(StrView const& sep, generator<T>& list) {
    Str os;
    int index = 0;
    for (const auto& it : list) {
        if (0 < index) { os += sep; }
        os += fmt::format("{}", it);
        ++index;
    }
    return os;
}


template <typename T>
Str join(StrView const& sep, generator<T>&& list) {
    auto tmp = std::move(list);
    return join(sep, tmp);
}

/// Get visible name of the character.
Pair<Str, Str> visibleName(char ch);
Str            indent(Str const& str, int spaces, char space = ' ', Str prefix = "");
Str            indent_skip_n_lines(
    Str const& str,
    int        spaces,
    int        lines_to_skip,
    char       space  = ' ',
    Str        prefix = "");

Vec<Str>           visibleUnicodeName(hstd::StrView str, bool useUnicode = true);
Vec<Str>           visibleUnicodeName(Str const& str, bool useUnicode = true);
Vec<hstd::StrView> split_keep_separator(
    hstd::StrView str [[clang::lifetimebound]],
    CharSet       sep = {' '});
hstd::StrView strip(
    hstd::StrView  string [[clang::lifetimebound]],
    CharSet const& leading,
    CharSet const& trailing);
hstd::StrView lstrip(hstd::StrView string [[clang::lifetimebound]], CharSet const& chars);
hstd::StrView rstrip(hstd::StrView string [[clang::lifetimebound]], CharSet const& chars);
Vec<hstd::StrView> split(hstd::StrView str [[clang::lifetimebound]], char ch);
Vec<hstd::StrView> split(
    hstd::StrView value [[clang::lifetimebound]],
    hstd::StrView delimiter);

Str  right_aligned(Str const& str, int n, char c = ' ');
Str  left_aligned(Str const& str, int n, char c = ' ');
Str  normalize(StrView in);
Str  lower(StrView in);
Str  repeat(Str const& str, int count);
Str  escape_for_write(hstd::StrView str, bool quote = true);
int  rune_length(StrView str);
bool iequals(std::string const& a, std::string const& b);

std::vector<StrView> rune_chunks(StrView str [[clang::lifetimebound]]);

std::string format_number(double value);
std::string format_table(
    Vec<Vec<Str>> const& rows,
    Str const&           inter_cell_spacing = " | ",
    Str const&           inter_row_spacing  = "-+-",
    char                 row_underline      = '-');


/// \brief Escape string literal, converting newline and other (TODO)
/// control characters into unicode.
std::string escape_literal(std::string const& in);
std::string escape_literal(hstd::StrView const& in);
void        validate_utf8(StrView str);

std::string format_integer_bits(uint64_t value, char fmt, int pad_to = 0);


void replace_all(std::string& str, std::string const& from, std::string const& to);

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

inline char* strdup(std::string const& str) { return ::strdup(str.c_str()); }

} // namespace hstd
