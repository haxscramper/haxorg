#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <lexbase/Token.hpp>

enum class BaseTokenKind
{
    Identifier,
    Keyword,
    Number,
    Whitespace,
    FileVarComment,
    SubtreeStars,
    BraceOpen,
    BraceClose,
    Date,
    Time,
    TimeArrow,
    Comment,
    TreePropertyEnd,
    TreePropertyProperties,
    TreePropertyLogbook,
    TreePropertyName,
    TreeClock,
    AnyPunct,
    LeadingSpace,
    Plus,
    Minus,
    SingleQuote,
    DoubleQuote,
    DoubleSlash,
    HashIdent,
    DoubleHash,
    EndBlock,
    BeginBlock,
    Tilda,
    LeftPar,
    RightPar,
    Equals,
    Semicolon,
    LeftAngle,
    RightAngle,
    LeftCurly,
    RightCurly,
    MacroBegin,
    MacroEnd,
    EscapedChar,
    Percent,
    LineCommand,
    At,
    DoubleLeftAngle,
    DoubleRightAngle,
    Asterisk,
    Ampersand,
    Exclamation,
    Word,
    Dollar,
    Pipe,
    TripleBacktick,
    Backtick,
    Circumflex,
    Emoji,
    MiscUnicode
};

struct BaseFill {
    std::string text;
};

using BaseToken = Token<BaseTokenKind, BaseFill>;

std::vector<BaseToken> tokenize(const char* input, int size);
