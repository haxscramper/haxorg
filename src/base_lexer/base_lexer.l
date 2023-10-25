

%top{
#include <string_view>
#include <vector>
#include <locale>
#include <codecvt>
#include <iostream>
#include <format>
#include <absl/log/check.h>
#include "base_token.hpp"
%}

%option fast freespace unicode

%xstate COMMAND
%state COMMAND_TEXT
%xstate COMMAND_OPTS
%xstate COMMAND_EXAMPLE
%xstate COMMAND_SRC
%xstate BODY_SRC

%class{
  public:
    BaseLexerImpl impl;
    void add(BaseTokenKind token) { impl.add(token); }
    void pop_expect_impl(int current, int next, int line) {
        impl.pop_expect_impl(current, next, line);
    }
}

%%

#define pop_expect(current, next) pop_expect_impl(current, next, __LINE__)

#\+                                      { /*10  */ add(BaseTokenKind::LineCommand); push_state(COMMAND); }
<COMMAND>begin_src                       { /*13  */ add(BaseTokenKind::CmdSrcBegin); push_state(COMMAND_SRC); }
<COMMAND_SRC>\n                          { /*17  */ add(BaseTokenKind::Newline); pop_expect(None, COMMAND); pop_expect(None, INITIAL); push_state(BODY_SRC); }
<BODY_SRC>"<<"                           { /*24  */ add(BaseTokenKind::SrcTangleOpen);  }
<BODY_SRC>">>"                           { /*25  */ add(BaseTokenKind::SrcTangleClose);  }
<BODY_SRC>.+                             { /*26  */ add(BaseTokenKind::SrcContent);  }
<COMMAND_OPTS,COMMAND_SRC>:\w+           { /*27  */ add(BaseTokenKind::CmdColonIdent);  }
<COMMAND_OPTS,COMMAND_SRC>\w+            { /*28  */ add(BaseTokenKind::CmdIdent);  }
<COMMAND_OPTS,COMMAND_SRC>[\t ]+         { /*29  */ add(BaseTokenKind::Whitespace);  }
"# -*- "                                 { /*31  */ add(BaseTokenKind::FileVarComment);  }
[0-9]+                                   { /*32  */ add(BaseTokenKind::Number);  }
^\s+                                     { /*33  */ add(BaseTokenKind::LeadingSpace);  }
\s+                                      { /*34  */ add(BaseTokenKind::Whitespace);  }
^\*+                                     { /*35  */ add(BaseTokenKind::SubtreeStars);  }
\[                                       { /*36  */ add(BaseTokenKind::BraceOpen);  }
\]                                       { /*37  */ add(BaseTokenKind::BraceClose);  }
\d{4}-\d{2}-\d{2}                        { /*38  */ add(BaseTokenKind::Date);  }
\d{2}:\d{2}:\d{2}                        { /*39  */ add(BaseTokenKind::Time);  }
=>                                       { /*40  */ add(BaseTokenKind::TimeArrow);  }
# .*?$                                   { /*41  */ add(BaseTokenKind::Comment);  }
:END:                                    { /*42  */ add(BaseTokenKind::TreePropertyEnd);  }
:LOGBOOK:                                { /*43  */ add(BaseTokenKind::TreePropertyLogbook);  }
:PROPERTIES:                             { /*44  */ add(BaseTokenKind::TreePropertyProperties);  }
:\w+:                                    { /*45  */ add(BaseTokenKind::TreePropertyName);  }
CLOCK:                                   { /*46  */ add(BaseTokenKind::TreeClock);  }
&                                        { /*47  */ add(BaseTokenKind::Ampersand);  }
!                                        { /*48  */ add(BaseTokenKind::Exclamation);  }
[,\./?]                                  { /*49  */ add(BaseTokenKind::AnyPunct);  }
\+                                       { /*50  */ add(BaseTokenKind::Plus);  }
\-                                       { /*51  */ add(BaseTokenKind::Minus);  }
\"                                       { /*52  */ add(BaseTokenKind::DoubleQuote);  }
\'                                       { /*53  */ add(BaseTokenKind::SingleQuote);  }
\\\\                                     { /*54  */ add(BaseTokenKind::DoubleSlash);  }
#\w+                                     { /*55  */ add(BaseTokenKind::HashIdent);  }
##                                       { /*56  */ add(BaseTokenKind::DoubleHash);  }
\(                                       { /*57  */ add(BaseTokenKind::LeftPar);  }
\)                                       { /*58  */ add(BaseTokenKind::RightPar);  }
~                                        { /*59  */ add(BaseTokenKind::Tilda);  }
=                                        { /*60  */ add(BaseTokenKind::Equals);  }
\;                                       { /*61  */ add(BaseTokenKind::Semicolon);  }
\*                                       { /*62  */ add(BaseTokenKind::Asterisk);  }
<<                                       { /*63  */ add(BaseTokenKind::DoubleLeftAngle);  }
>>                                       { /*64  */ add(BaseTokenKind::DoubleRightAngle);  }
<                                        { /*65  */ add(BaseTokenKind::LeftAngle);  }
>                                        { /*66  */ add(BaseTokenKind::RightAngle);  }
\^                                       { /*67  */ add(BaseTokenKind::Circumflex);  }
"{{{"                                    { /*68  */ add(BaseTokenKind::MacroBegin);  }
"}}}"                                    { /*69  */ add(BaseTokenKind::MacroEnd);  }
"{"                                      { /*70  */ add(BaseTokenKind::LeftCurly);  }
"}"                                      { /*71  */ add(BaseTokenKind::RightCurly);  }
\\.                                      { /*72  */ add(BaseTokenKind::EscapedChar);  }
\%                                       { /*73  */ add(BaseTokenKind::Percent);  }
@                                        { /*74  */ add(BaseTokenKind::At);  }
\|                                       { /*75  */ add(BaseTokenKind::Pipe);  }
```                                      { /*76  */ add(BaseTokenKind::TripleBacktick);  }
`                                        { /*77  */ add(BaseTokenKind::Backtick);  }
\p{Punctuation}                          { /*78  */ add(BaseTokenKind::AnyPunct);  }
\w+                                      { /*79  */ add(BaseTokenKind::Word);  }
\$                                       { /*80  */ add(BaseTokenKind::Dollar);  }
[\x{0256}-\x{10FFFF}]|©                  { /*81  */ add(BaseTokenKind::MiscUnicode);  }  

%%

std::vector<BaseToken> tokenize(const char* input, int size) {
    base_lexer::Lexer lex(input);
    lex.impl.impl = &lex;
    lex.impl.tokens.reserve(size / 3);
    lex.lex();
    return lex.impl.tokens;
}

    