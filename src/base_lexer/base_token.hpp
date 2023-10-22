#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <lexbase/Token.hpp>
#include <hstd/system/reflection.hpp>

// clang-format off
#define EACH_BASE_KIND(__op) \
   __op(Identifier) \
    __op(Keyword) \
    __op(Number) \
    __op(Whitespace) \
    __op(FileVarComment) \
    __op(SubtreeStars) \
    __op(BraceOpen) \
    __op(BraceClose) \
    __op(Date) \
    __op(Time) \
    __op(TimeArrow) \
    __op(Comment) \
    __op(TreePropertyEnd) \
    __op(TreePropertyProperties) \
    __op(TreePropertyLogbook) \
    __op(TreePropertyName) \
    __op(TreeClock) \
    __op(AnyPunct) \
    __op(LeadingSpace) \
    __op(Plus) \
    __op(Minus) \
    __op(SingleQuote) \
    __op(DoubleQuote) \
    __op(DoubleSlash) \
    __op(HashIdent) \
    __op(DoubleHash) \
    __op(EndBlock) \
    __op(BeginBlock) \
    __op(Tilda) \
    __op(LeftPar) \
    __op(RightPar) \
    __op(Equals) \
    __op(Semicolon) \
    __op(LeftAngle) \
    __op(RightAngle) \
    __op(LeftCurly) \
    __op(RightCurly) \
    __op(MacroBegin) \
    __op(MacroEnd) \
    __op(EscapedChar) \
    __op(Percent) \
    __op(LineCommand) \
    __op(At) \
    __op(DoubleLeftAngle) \
    __op(DoubleRightAngle) \
    __op(Asterisk) \
    __op(Ampersand) \
    __op(Exclamation) \
    __op(Word) \
    __op(Dollar) \
    __op(Pipe) \
    __op(TripleBacktick) \
    __op(Backtick) \
    __op(Circumflex) \
    __op(Emoji) \
    __op(MiscUnicode) \
    __op(Newline) \
    __op(CmdBeginSrc) \
    __op(CmdEndSrc) \
    __op(CmdBeginExample) \
    __op(CmdEndExample) \
    __op(CmdBeginQuote) \
    __op(CmdEndQuote) \
    __op(CmdCaption) \
    __op(CmdOptions) \
    __op(CmdColonIdent) \
    __op(CmdIdent) \
    __op(SrcTangleOpen) \
    __op(SrcTangleClose) \
    __op(SrcContent) \
    __op(MacroOpen) \
    __op(MacroClose) \



// clang-format on


enum class BaseTokenKind : u16
{
#define __def(__kind) __kind,
    EACH_BASE_KIND(__def)
#undef __def
};

template <>
struct enum_serde<BaseTokenKind> {
    static inline std::string to_string(BaseTokenKind const& value) {
        switch (value) {
#define __case(__kind)                                                    \
    case BaseTokenKind::__kind: return #__kind;
            EACH_BASE_KIND(__case)
#undef __case
        }
    }
};

struct BaseFill {
    std::string text;
    int         line;
    int         col;
};

using BaseToken = Token<BaseTokenKind, BaseFill>;

std::vector<BaseToken> tokenize(const char* input, int size);
