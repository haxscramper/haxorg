#pragma once

#include <hstd/stdlib/IntSet.hpp>

using CharSet = IntSet<char>;

namespace charsets {
/// All character values
C<CharSet> AllChars{slice('\x00', '\xFF')};
/// Arabic digits
C<CharSet> Digits{slice('0', '9')};
/// Characters that can be used in C++-style identifiers
C<CharSet> IdentChars{
    slice('a', 'z'),
    slice('A', 'Z'),
    slice('0', '9'),
    '_'};

/// Characters that can be used as an identifier start
C<CharSet> IdentStartChars{slice('a', 'z'), slice('A', 'Z'), '_'};
/// Lowercase and uppercase latin letters
C<CharSet> Letters{slice('A', 'Z'), slice('a', 'z')};
C<CharSet> Newlines{'\r', '\n'};
/// Any kind of horizontal or vertical whitespace
C<CharSet> Whitespace{' ', '\t', '\v', '\r', '\n', '\f'};

/// Any character that can be a part of UTF-8 encoded string
C<CharSet> Utf8Any{slice('\x80', '\xFF')};
/// UTF8 continuation
C<CharSet> Utf8Continuations{slice(char(0b10000000), char(0b10111111))};
/// Start of the two-byte utf8 rune
C<CharSet> Utf8Starts2{slice(char(0b11000000), char(0b11011111))};
/// Start of the three-byte utf8 rune
C<CharSet> Utf8Starts3{slice(char(0b11100000), char(0b11101111))};
/// Start of the four-byte utf8 rune
C<CharSet> Utf8Starts4{slice(char(0b11110000), char(0b11110111))};
/// Start of any utf8 rune
C<CharSet> Utf8Starts = Utf8Starts2 + Utf8Starts3 + Utf8Starts4;

C<CharSet> LowerAsciiLetters{slice('a', 'z')};
C<CharSet> HighAsciiLetters{slice('A', 'Z')};
C<CharSet> AsciiLetters    = LowerAsciiLetters + HighAsciiLetters;
C<CharSet> AnyRegularAscii = {slice('\x00', '\x7F')};
C<CharSet> ControlChars    = {slice('\x00', '\x1F'), '\x7F'};
C<CharSet> MaybeLetters    = AsciiLetters + Utf8Any;
C<CharSet> IntegerStartChars{slice('0', '9'), '-', '+'};
C<CharSet> HexDigitsLow  = CharSet{'a', 'b', 'c', 'd', 'e', 'f'} + Digits;
C<CharSet> HexDigitsHigh = CharSet{'A', 'B', 'C', 'D', 'E', 'F'} + Digits;
C<CharSet> HexDigits     = HexDigitsLow + HexDigitsHigh;
C<CharSet> PunctOpenChars{'(', '[', '{', '<'};
C<CharSet> PunctCloseChars{')', ']', '}', '>'};
C<CharSet> PunctSentenceChars{',', '.', '?', '!', ';', ':'};
C<CharSet> MathChars  = {'+', '/', '%', '*', '='};
C<CharSet> PunctChars = PunctOpenChars + PunctCloseChars
                      + PunctSentenceChars;
C<CharSet> Newline{'\n'};
C<CharSet> AllSpace        = Whitespace;
C<CharSet> HorizontalSpace = AllSpace - Newline;
C<CharSet> DashIdentChars  = LowerAsciiLetters + HighAsciiLetters
                          + CharSet{'_', '-'};
C<CharSet> VeritcalSpace = Newline;

// Character found in regular text line. All chars excluding special
// controls (newline, line feed, carriage return etc.). This does include
// tabulation, because it is not uncommon in regular text.
C<CharSet> TextLineChars = AllChars - ControlChars + CharSet{'\t'};

C<CharSet> TextChars = MaybeLetters + Digits + CharSet{'.', ',', '-'};
} // namespace charsets
