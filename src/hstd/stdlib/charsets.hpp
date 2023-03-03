#pragma once

#include <hstd/stdlib/IntSet.hpp>

using CharSet = IntSet<QChar>;

template <>
inline QChar low() {
    return QChar(low<wchar_t>());
}
template <>
inline QChar high() {
    return QChar(low<wchar_t>());
}

namespace charsets {
/// All character values
Const<CharSet> AllChars{slice(low<QChar>(), high<QChar>())};
/// Arabic digits
Const<CharSet> Digits{slice(QChar('0'), QChar('9'))};
/// Characters that can be used in C++-style identifiers
Const<CharSet> IdentChars{
    slice(QChar('a'), QChar('z')),
    slice(QChar('A'), QChar('Z')),
    slice(QChar('0'), QChar('9')),
    QChar('_')};

/// Characters that can be used as an identifier start
Const<CharSet> IdentStartChars{
    slice(QChar('a'), QChar('z')),
    slice(QChar('A'), QChar('Z')),
    QChar('_')};
/// Lowercase and uppercase latin letters
Const<CharSet> Letters{
    slice(QChar('A'), QChar('Z')),
    slice(QChar('a'), QChar('z'))};
Const<CharSet> Newlines{QChar('\r'), QChar('\n')};
/// Any kind of horizontal or vertical whitespace
Const<CharSet> Whitespace{
    QChar(' '),
    QChar('\t'),
    QChar('\v'),
    QChar('\r'),
    QChar('\n'),
    QChar('\f')};

/// Any character that can be a part of UTF-8 encoded string
Const<CharSet> Utf8Any{slice(QChar('\x80'), QChar('\xFF'))};
/// UTF8 continuation
Const<CharSet> Utf8Continuations{
    slice(QChar(char(0b10000000)), QChar(char(0b10111111)))};
/// Start of the two-byte utf8 rune
Const<CharSet> Utf8Starts2{
    slice(QChar(char(0b11000000)), QChar(char(0b11011111)))};
/// Start of the three-byte utf8 rune
Const<CharSet> Utf8Starts3{
    slice(QChar(char(0b11100000)), QChar(char(0b11101111)))};
/// Start of the four-byte utf8 rune
Const<CharSet> Utf8Starts4{
    slice(QChar(char(0b11110000)), QChar(char(0b11110111)))};
/// Start of any utf8 rune
Const<CharSet> Utf8Starts = Utf8Starts2 + Utf8Starts3 + Utf8Starts4;

Const<CharSet> LowerAsciiLetters{slice(QChar('a'), QChar('z'))};
Const<CharSet> HighAsciiLetters{slice(QChar('A'), QChar('Z'))};
Const<CharSet> AsciiLetters    = LowerAsciiLetters + HighAsciiLetters;
Const<CharSet> AnyRegularAscii = {slice(QChar('\x00'), QChar('\x7F'))};
Const<CharSet> ControlChars    = {
    slice(QChar('\x00'), QChar('\x1F')),
    QChar('\x7F')};
Const<CharSet> MaybeLetters = AsciiLetters + Utf8Any;
Const<CharSet> IntegerStartChars{
    slice(QChar('0'), QChar('9')),
    QChar('-'),
    QChar('+')};
Const<CharSet>
    HexDigitsLow = CharSet{QChar('a'), QChar('b'), QChar('c'), QChar('d'), QChar('e'), QChar('f')}
                 + Digits;
Const<CharSet>
    HexDigitsHigh = CharSet{QChar('A'), QChar('B'), QChar('C'), QChar('D'), QChar('E'), QChar('F')}
                  + Digits;
Const<CharSet> HexDigits = HexDigitsLow + HexDigitsHigh;
Const<CharSet> PunctOpenChars{
    QChar('('),
    QChar('['),
    QChar('{'),
    QChar('<')};
Const<CharSet> PunctCloseChars{
    QChar(')'),
    QChar(']'),
    QChar('}'),
    QChar('>')};
Const<CharSet> PunctSentenceChars{
    QChar(','),
    QChar('.'),
    QChar('?'),
    QChar('!'),
    QChar(';'),
    QChar(':')};
Const<CharSet> MathChars = {
    QChar('+'),
    QChar('/'),
    QChar('%'),
    QChar('*'),
    QChar('=')};
Const<CharSet> PunctChars = PunctOpenChars + PunctCloseChars
                          + PunctSentenceChars;
Const<CharSet> Newline{QChar('\n')};
Const<CharSet> AllSpace        = Whitespace;
Const<CharSet> HorizontalSpace = AllSpace - Newline;
Const<CharSet> DashIdentChars  = LowerAsciiLetters + HighAsciiLetters
                              + CharSet{QChar('_'), QChar('-')};
Const<CharSet> VeritcalSpace = Newline;

// Character found in regular text line. All chars excluding special
// controls (newline, line feed, carriage return etc.). This does include
// tabulation, because it is not uncommon in regular text.
Const<CharSet> TextLineChars = AllChars - ControlChars
                             + CharSet{QChar('\t')};

Const<CharSet> TextChars = MaybeLetters + Digits
                         + CharSet{QChar('.'), QChar(','), QChar('-')};
} // namespace charsets
