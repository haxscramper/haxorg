#pragma once

#include <hstd/stdlib/IntSet.hpp>

using CharSet = IntSet<char>;

template <>
struct value_domain<char> {
    static inline char low() { return char(value_domain<char>::low()); }
    static inline char high() { return char(value_domain<char>::high()); }

    static inline long long int ord(char c) {
        return static_cast<long long int>(c);
    }

    static inline char succ(char c) { return char(c + 1); }
};

namespace charsets {
/// All character values
Const<CharSet> AllChars{slice('\x00', '\x7F')};
/// Arabic digits
Const<CharSet> Digits{slice('0', '9')};
/// Characters that can be used in C++-style identifiers
Const<CharSet> IdentChars{
    slice('a', 'z'),
    slice('A', 'Z'),
    slice('0', '9'),
    '_'};

/// Characters that can be used as an identifier start
Const<CharSet> IdentStartChars{slice('a', 'z'), slice('A', 'Z'), '_'};
/// Lowercase and uppercase latin letters
Const<CharSet> Letters{slice('A', 'Z'), slice('a', 'z')};
Const<CharSet> Newlines{'\r', '\n'};
/// Any kind of horizontal or vertical whitespace
Const<CharSet> Whitespace{' ', '\t', '\v', '\r', '\n', '\f'};

/// Any character that can be a part of UTF-8 encoded string
Const<CharSet> Utf8Any{slice('\x80', '\xFF')};
/// UTF8 continuation
Const<CharSet> Utf8Continuations{
    slice(char(char(0b10000000)), char(char(0b10111111)))};
/// Start of the two-byte utf8 rune
Const<CharSet> Utf8Starts2{
    slice(char(char(0b11000000)), char(char(0b11011111)))};
/// Start of the three-byte utf8 rune
Const<CharSet> Utf8Starts3{
    slice(char(char(0b11100000)), char(char(0b11101111)))};
/// Start of the four-byte utf8 rune
Const<CharSet> Utf8Starts4{
    slice(char(char(0b11110000)), char(char(0b11110111)))};
/// Start of any utf8 rune
Const<CharSet> Utf8Starts = Utf8Starts2 + Utf8Starts3 + Utf8Starts4;

Const<CharSet> LowerAsciiLetters{slice('a', 'z')};
Const<CharSet> HighAsciiLetters{slice('A', 'Z')};
Const<CharSet> AsciiLetters    = LowerAsciiLetters + HighAsciiLetters;
Const<CharSet> AnyRegularAscii = {slice('\x00', '\x7F')};
Const<CharSet> ControlChars    = {slice('\x00', '\x1F'), '\x7F'};
Const<CharSet> MaybeLetters    = AsciiLetters + Utf8Any;
Const<CharSet> IntegerStartChars{slice('0', '9'), '-', '+'};
Const<CharSet> HexDigitsLow = CharSet{'a', 'b', 'c', 'd', 'e', 'f'}
                            + Digits;
Const<CharSet> HexDigitsHigh = CharSet{'A', 'B', 'C', 'D', 'E', 'F'}
                             + Digits;
Const<CharSet> HexDigits = HexDigitsLow + HexDigitsHigh;
Const<CharSet> PunctOpenChars{'(', '[', '{', '<'};
Const<CharSet> PunctCloseChars{')', ']', '}', '>'};
Const<CharSet> PunctSentenceChars{',', '.', '?', '!', ';', ':'};
Const<CharSet> MathChars  = {'+', '/', '%', '*', '='};
Const<CharSet> PunctChars = PunctOpenChars + PunctCloseChars
                          + PunctSentenceChars;
Const<CharSet> Newline{'\n'};
Const<CharSet> AllSpace        = Whitespace;
Const<CharSet> HorizontalSpace = AllSpace - Newline;
Const<CharSet> DashIdentChars  = LowerAsciiLetters + HighAsciiLetters
                              + CharSet{'_', '-'};
Const<CharSet> VeritcalSpace = Newline;

// Character found in regular text line. All chars excluding special
// controls (newline, line feed, carriage return etc.). This does include
// tabulation, because it is not uncommon in regular text.
Const<CharSet> TextLineChars = AllChars - ControlChars + CharSet{'\t'};

Const<CharSet> TextChars = MaybeLetters + Digits + CharSet{'.', ',', '-'};
} // namespace charsets
