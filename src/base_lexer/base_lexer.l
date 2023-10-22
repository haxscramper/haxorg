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

      std::cerr << lineno() << ":" << columno()
                << " >" << matcher().text() << "< ("
                << std::hex << (uint32_t)codepoint << ")" << matcher().span() << "\n";
    }
}

%%

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
#\+begin_\w+            { add(BaseTokenKind::BeginBlock); }
#\+end_\w+              { add(BaseTokenKind::EndBlock); }
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
#\+\w+:                 { add(BaseTokenKind::LineCommand); }
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
