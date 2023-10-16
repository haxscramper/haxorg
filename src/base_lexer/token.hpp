#pragma once

#include <string>
#include <string_view>
#include <vector>

enum class TokenKind
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

struct Token {
    std::string value;
    TokenKind   kind;

    Token(std::string v, TokenKind k) : value(v), kind(k) {}
};

std::vector<Token> tokenize(const char* input, int size);
