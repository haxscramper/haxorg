%top{
#include <string_view>
#include <vector>
#include <locale>
#include <codecvt>
#include <iostream>
#include "token.hpp"  // assuming you've defined the above structures in token.h
%}

%option fast freespace unicode

%class{
  public:
    std::vector<Token> tokens;
    std::vector<int> linenos;
    std::vector<int> columnos;

    void add(TokenKind token) {
      linenos.push_back(lineno());
      columnos.push_back(columno());
      tokens.emplace_back(matcher().text(), token);
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

"# -*- "                { add(TokenKind::FileVarComment); }
[0-9]+                  { add(TokenKind::Number); }
^\s+                    { add(TokenKind::LeadingSpace); }
\s+                     { add(TokenKind::Whitespace); }
^\*+                    { add(TokenKind::SubtreeStars); }
\[                      { add(TokenKind::BraceOpen); }
\]                      { add(TokenKind::BraceClose); }
\d{4}-\d{2}-\d{2}       { add(TokenKind::Date); }
\d{2}:\d{2}:\d{2}       { add(TokenKind::Time); }
"=>"                    { add(TokenKind::TimeArrow); }
"# .*?$"                { add(TokenKind::Comment); }
":END:"                 { add(TokenKind::TreePropertyEnd); }
":LOGBOOK:"             { add(TokenKind::TreePropertyLogbook); }
":PROPERTIES:"          { add(TokenKind::TreePropertyProperties); }
":\w+:"                 { add(TokenKind::TreePropertyName); }
"CLOCK:"                { add(TokenKind::TreeClock); }
&                       { add(TokenKind::Ampersand); }
!                       { add(TokenKind::Exclamation); }
[,\./?]                 { add(TokenKind::AnyPunct); }
\+                      { add(TokenKind::Plus); }
\-                      { add(TokenKind::Minus); }
\"                      { add(TokenKind::DoubleQuote); }
\'                      { add(TokenKind::SingleQuote); }
\\\\                    { add(TokenKind::DoubleSlash); }
#\w+                    { add(TokenKind::HashIdent); }
##                      { add(TokenKind::DoubleHash); }
#\+begin_\w+            { add(TokenKind::BeginBlock); }
#\+end_\w+              { add(TokenKind::EndBlock); }
\(                      { add(TokenKind::LeftPar); }
\)                      { add(TokenKind::RightPar); }
~                       { add(TokenKind::Tilda); }
=                       { add(TokenKind::Equals); }
\;                      { add(TokenKind::Semicolon); }
\*                      { add(TokenKind::Asterisk); }
<<                      { add(TokenKind::DoubleLeftAngle); }
>>                      { add(TokenKind::DoubleRightAngle); }
<                       { add(TokenKind::LeftAngle); }
>                       { add(TokenKind::RightAngle); }
\^                      { add(TokenKind::Circumflex); }
\{\{\{                  { add(TokenKind::MacroBegin); }
\}\}\}                  { add(TokenKind::MacroEnd); }
\{                      { add(TokenKind::LeftCurly); }
\}                      { add(TokenKind::RightCurly); }
\\.                     { add(TokenKind::EscapedChar); }
#\+\w+:                 { add(TokenKind::LineCommand); }
\%                      { add(TokenKind::Percent); }
@                       { add(TokenKind::At); }
\|                      { add(TokenKind::Pipe); }
```                     { add(TokenKind::TripleBacktick); }
`                       { add(TokenKind::Backtick); }
\p{Punctuation}         { add(TokenKind::AnyPunct); }
\w+                     { add(TokenKind::Word); }
\$                      { add(TokenKind::Dollar); }

[\x{0256}-\x{10FFFF}]|© { add(TokenKind::MiscUnicode); }

.                       { unknown(); }

%%

std::vector<Token> tokenize(const char* input, int size) {
    Lexer lex(input);
    lex.tokens.reserve(size / 3);
    lex.linenos.reserve(size / 3);
    lex.columnos.reserve(size / 3);
    lex.lex();
    return lex.tokens;
}
