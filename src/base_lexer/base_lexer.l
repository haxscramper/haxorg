%top{
#include <string_view>
#include <vector>
#include <locale>
#include <codecvt>
#include <iostream>
#include "base_token.hpp"
%}

%option fast freespace unicode


%class{
  public:
    std::vector<BaseToken> tokens;

    void add(BaseTokenKind token) {
        tokens.emplace_back(BaseToken{token, BaseFill{ matcher().text(), lineno(), columno()}});
    }

    void unknown() {
      std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
      std::u32string utf32_str = conv.from_bytes(matcher().text());
      char32_t codepoint = utf32_str[0];

      std::cerr << std::dec << lineno() << ":" << columno() << " in state " 
                << top_state() 
                << " >" << matcher().text() << "< ("
                << std::hex << (uint32_t)codepoint << ") " << matcher().span() << "\n";
    }
}

%xstate COMMAND
%state COMMAND_TEXT
// Commands with options ave exclusive state for lexing content
%xstate COMMAND_OPTS 
%xstate COMMAND_EXAMPLE

%%

#\+                     { add(BaseTokenKind::LineCommand); push_state(COMMAND); }

<COMMAND>begin_src      { add(BaseTokenKind::CmdBeginSrc); push_state(COMMAND_OPTS); }

<COMMAND_OPTS>:\w+      { add(BaseTokenKind::CmdColonIdent); }
// Drop two levels of command nesting -- at the end of the line exit from `COMMAND_OPTS`
// and from `COMMAND` itself.
<COMMAND_OPTS>\n        { add(BaseTokenKind::Newline); pop_state(); pop_state(); }
<COMMAND_OPTS>\w+       { add(BaseTokenKind::CmdIdent); }
<COMMAND_OPTS>\s+       { add(BaseTokenKind::Whitespace); }
<COMMAND_OPTS>.         { unknown(); }
<COMMAND>end_src        { add(BaseTokenKind::CmdEndSrc); }

<COMMAND>begin_example  { add(BaseTokenKind::CmdBeginExample); }
<COMMAND>end_example    { add(BaseTokenKind::CmdEndExample); }
<COMMAND>begin_quote    { add(BaseTokenKind::CmdBeginQuote); }
<COMMAND>end_quote      { add(BaseTokenKind::CmdEndQuote); }

// Caption command has a regular text lexing content
<COMMAND>caption        { add(BaseTokenKind::CmdCaption); push_state(COMMAND_TEXT); }
<COMMAND_TEXT>\n        { add(BaseTokenKind::Newline); pop_state(); pop_state(); }


<COMMAND>\n             { add(BaseTokenKind::Newline); pop_state(); }
<COMMAND>.              { unknown(); }

"# -*- "                { add(BaseTokenKind::FileVarComment); }
[0-9]+                  { add(BaseTokenKind::Number); }
^\s+                    { add(BaseTokenKind::LeadingSpace); }
\s+                     { add(BaseTokenKind::Whitespace); }
^\*+                    { add(BaseTokenKind::SubtreeStars); }
\[                      { add(BaseTokenKind::BraceOpen); }
\]                      { add(BaseTokenKind::BraceClose); }
\d{4}-\d{2}-\d{2}       { add(BaseTokenKind::Date); }
\d{2}:\d{2}:\d{2}       { add(BaseTokenKind::Time); }
"=>"                    { add(BaseTokenKind::TimeArrow); }
"# .*?$"                { add(BaseTokenKind::Comment); }
":END:"                 { add(BaseTokenKind::TreePropertyEnd); }
":LOGBOOK:"             { add(BaseTokenKind::TreePropertyLogbook); }
":PROPERTIES:"          { add(BaseTokenKind::TreePropertyProperties); }
":\w+:"                 { add(BaseTokenKind::TreePropertyName); }
"CLOCK:"                { add(BaseTokenKind::TreeClock); }
&                       { add(BaseTokenKind::Ampersand); }
!                       { add(BaseTokenKind::Exclamation); }
[,\./?]                 { add(BaseTokenKind::AnyPunct); }
\+                      { add(BaseTokenKind::Plus); }
\-                      { add(BaseTokenKind::Minus); }
\"                      { add(BaseTokenKind::DoubleQuote); }
\'                      { add(BaseTokenKind::SingleQuote); }
\\\\                    { add(BaseTokenKind::DoubleSlash); }
#\w+                    { add(BaseTokenKind::HashIdent); }
##                      { add(BaseTokenKind::DoubleHash); }





\(                      { add(BaseTokenKind::LeftPar); }
\)                      { add(BaseTokenKind::RightPar); }
~                       { add(BaseTokenKind::Tilda); }
=                       { add(BaseTokenKind::Equals); }
\;                      { add(BaseTokenKind::Semicolon); }
\*                      { add(BaseTokenKind::Asterisk); }
<<                      { add(BaseTokenKind::DoubleLeftAngle); }
>>                      { add(BaseTokenKind::DoubleRightAngle); }
<                       { add(BaseTokenKind::LeftAngle); }
>                       { add(BaseTokenKind::RightAngle); }
\^                      { add(BaseTokenKind::Circumflex); }
\{\{\{                  { add(BaseTokenKind::MacroBegin); }
\}\}\}                  { add(BaseTokenKind::MacroEnd); }
\{                      { add(BaseTokenKind::LeftCurly); }
\}                      { add(BaseTokenKind::RightCurly); }
\\.                     { add(BaseTokenKind::EscapedChar); }
\%                      { add(BaseTokenKind::Percent); }
@                       { add(BaseTokenKind::At); }
\|                      { add(BaseTokenKind::Pipe); }
```                     { add(BaseTokenKind::TripleBacktick); }
`                       { add(BaseTokenKind::Backtick); }
\p{Punctuation}         { add(BaseTokenKind::AnyPunct); }
\w+                     { add(BaseTokenKind::Word); }
\$                      { add(BaseTokenKind::Dollar); }

[\x{0256}-\x{10FFFF}]|© { add(BaseTokenKind::MiscUnicode); }

.                       { unknown(); }

%%

std::vector<BaseToken> tokenize(const char* input, int size) {
    base_lexer::Lexer lex(input);
    lex.tokens.reserve(size / 3);
    lex.lex();
    return lex.tokens;
}
