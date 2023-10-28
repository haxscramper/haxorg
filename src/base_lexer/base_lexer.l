

%top{
#include <string_view>
#include <vector>
#include <locale>
#include <codecvt>
#include <iostream>
#include <format>
#include <absl/log/check.h>
#include "base_token.hpp"

#define pop_expect(current, next) impl.pop_expect_impl(current, next, __LINE__)
#define push_expect(current, next) impl.push_expect_impl(current, next, __LINE__)
%}

%option fast freespace unicode

%state COMMAND_TEXT
%state SUBTREE_HEAD
%state PROPERTY_ANY
%xstate COMMAND
%xstate COMMAND_EXAMPLE
%xstate COMMAND_COLUMNS
%xstate COMMAND_SRC
%xstate BODY_SRC
%xstate PROPERTIES
%xstate PROPERTY_LITERAL

%class{
  public:
    BaseLexerImpl impl;
}

%%

"#+"                                     { /*15  */ impl.before(__LINE__); impl.add(BaseTokenKind::LineCommand); push_expect(INITIAL, COMMAND); impl.after(__LINE__); }
<COMMAND>columns                         { /*20  */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdColumns); push_expect(COMMAND, COMMAND_COLUMNS); impl.after(__LINE__); }
<COMMAND_COLUMNS>"%"                     { /*26  */ impl.before(__LINE__); impl.add(BaseTokenKind::Percent);  impl.after(__LINE__); }
<COMMAND_COLUMNS>\d+                     { /*27  */ impl.before(__LINE__); impl.add(BaseTokenKind::Digit);  impl.after(__LINE__); }
<COMMAND_COLUMNS>[a-zA-Z_]+              { /*28  */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdIdent);  impl.after(__LINE__); }
<COMMAND_COLUMNS>"("                     { /*29  */ impl.before(__LINE__); impl.add(BaseTokenKind::LeftPar);  impl.after(__LINE__); }
<COMMAND_COLUMNS>")"                     { /*30  */ impl.before(__LINE__); impl.add(BaseTokenKind::RightPar);  impl.after(__LINE__); }
<COMMAND_COLUMNS>"{"                     { /*31  */ impl.before(__LINE__); impl.add(BaseTokenKind::LeftCurly);  impl.after(__LINE__); }
<COMMAND_COLUMNS>"}"                     { /*32  */ impl.before(__LINE__); impl.add(BaseTokenKind::RightCurly);  impl.after(__LINE__); }
<COMMAND_COLUMNS>":"                     { /*33  */ impl.before(__LINE__); impl.add(BaseTokenKind::Colon);  impl.after(__LINE__); }
<COMMAND_COLUMNS>\h+                     { /*34  */ impl.before(__LINE__); impl.add(BaseTokenKind::Whitespace);  impl.after(__LINE__); }
<COMMAND_COLUMNS>\n                      { /*36  */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline); pop_expect(COMMAND_COLUMNS, COMMAND); pop_expect(COMMAND, INITIAL); impl.after(__LINE__); }
<COMMAND>begin_src                       { /*44  */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdSrcBegin); push_expect(COMMAND, COMMAND_SRC); impl.after(__LINE__); }
<COMMAND_SRC>\n                          { /*48  */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline); pop_expect(COMMAND_SRC, COMMAND); pop_expect(COMMAND, INITIAL); push_expect(INITIAL, BODY_SRC); impl.after(__LINE__); }
<BODY_SRC>"<<"                           { /*55  */ impl.before(__LINE__); impl.add(BaseTokenKind::SrcTangleOpen);  impl.after(__LINE__); }
<BODY_SRC>">>"                           { /*56  */ impl.before(__LINE__); impl.add(BaseTokenKind::SrcTangleClose);  impl.after(__LINE__); }
<BODY_SRC>\h*#\+src_end                  { /*57  */ impl.before(__LINE__); impl.add(BaseTokenKind::SrcContentEnd);  impl.after(__LINE__); }
<BODY_SRC>.+                             { /*58  */ impl.before(__LINE__); impl.add(BaseTokenKind::SrcContent);  impl.after(__LINE__); }
<COMMAND_SRC>:\w+                        { /*61  */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdColonIdent);  impl.after(__LINE__); }
<COMMAND_SRC>\w+                         { /*62  */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdIdent);  impl.after(__LINE__); }
<COMMAND_SRC>\h+                         { /*63  */ impl.before(__LINE__); impl.add(BaseTokenKind::Whitespace);  impl.after(__LINE__); }
<COMMAND>"caption"                       { /*66  */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdCaption); push_expect(COMMAND, COMMAND_TEXT); impl.after(__LINE__); }
<COMMAND_TEXT>\n                         { /*70  */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline); pop_expect(COMMAND_TEXT, COMMAND); pop_expect(COMMAND, INITIAL); impl.after(__LINE__); }
^\*+                                     { /*77  */ impl.before(__LINE__); impl.add(BaseTokenKind::SubtreeStars); push_expect(INITIAL, SUBTREE_HEAD); impl.after(__LINE__); }
<SUBTREE_HEAD>\[#\w\]                    { /*82  */ impl.before(__LINE__); impl.add(BaseTokenKind::SubtreePriority);  impl.after(__LINE__); }
<SUBTREE_HEAD>\n                         { /*86  */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline); pop_expect(SUBTREE_HEAD, INITIAL); impl.after(__LINE__); }
[0-9]+                                   { /*93  */ impl.before(__LINE__); impl.add(BaseTokenKind::Number);  impl.after(__LINE__); }
^\h+                                     { /*94  */ impl.before(__LINE__); impl.add(BaseTokenKind::LeadingSpace);  impl.after(__LINE__); }
\h+                                      { /*95  */ impl.before(__LINE__); impl.add(BaseTokenKind::Whitespace);  impl.after(__LINE__); }
\[                                       { /*96  */ impl.before(__LINE__); impl.add(BaseTokenKind::BraceOpen);  impl.after(__LINE__); }
\]                                       { /*97  */ impl.before(__LINE__); impl.add(BaseTokenKind::BraceClose);  impl.after(__LINE__); }
\d{4}-\d{2}-\d{2}                        { /*98  */ impl.before(__LINE__); impl.add(BaseTokenKind::Date);  impl.after(__LINE__); }
\d{2}:\d{2}:\d{2}                        { /*99  */ impl.before(__LINE__); impl.add(BaseTokenKind::Time);  impl.after(__LINE__); }
=>                                       { /*100 */ impl.before(__LINE__); impl.add(BaseTokenKind::TimeArrow);  impl.after(__LINE__); }
#\h+.*?$                                 { /*101 */ impl.before(__LINE__); impl.add(BaseTokenKind::Comment);  impl.after(__LINE__); }
":LOGBOOK:"                              { /*102 */ impl.before(__LINE__); impl.add(BaseTokenKind::TreePropertyLogbook);  impl.after(__LINE__); }
":PROPERTIES:"                           { /*104 */ impl.before(__LINE__); impl.add(BaseTokenKind::TreePropertyProperties); push_expect(INITIAL, PROPERTIES); impl.after(__LINE__); }
<PROPERTIES>\n                           { /*109 */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline);  impl.after(__LINE__); }
<PROPERTIES>^\h+                         { /*113 */ impl.before(__LINE__); impl.add(BaseTokenKind::LeadingSpace);  impl.after(__LINE__); }
<PROPERTIES>":END:"                      { /*117 */ impl.before(__LINE__); impl.add(BaseTokenKind::TreePropertyEnd); pop_expect(PROPERTIES, INITIAL); impl.after(__LINE__); }
<PROPERTIES>:(CREATED|created|origin|ORIGIN): { /*123 */ impl.before(__LINE__); impl.add(BaseTokenKind::TreePropertyText); push_expect(PROPERTIES, PROPERTY_ANY); impl.after(__LINE__); }
<PROPERTY_ANY>\n                         { /*129 */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline); pop_expect(PROPERTY_ANY, PROPERTIES); impl.after(__LINE__); }
<PROPERTIES>:\w+:                        { /*135 */ impl.before(__LINE__); impl.add(BaseTokenKind::TreePropertyName);  impl.after(__LINE__); }
"CLOCK:"                                 { /*139 */ impl.before(__LINE__); impl.add(BaseTokenKind::TreeClock);  impl.after(__LINE__); }
"&"                                      { /*140 */ impl.before(__LINE__); impl.add(BaseTokenKind::Ampersand);  impl.after(__LINE__); }
"!"                                      { /*141 */ impl.before(__LINE__); impl.add(BaseTokenKind::Exclamation);  impl.after(__LINE__); }
[,\./?]                                  { /*142 */ impl.before(__LINE__); impl.add(BaseTokenKind::AnyPunct);  impl.after(__LINE__); }
\+                                       { /*143 */ impl.before(__LINE__); impl.add(BaseTokenKind::Plus);  impl.after(__LINE__); }
\-                                       { /*144 */ impl.before(__LINE__); impl.add(BaseTokenKind::Minus);  impl.after(__LINE__); }
\"                                       { /*145 */ impl.before(__LINE__); impl.add(BaseTokenKind::DoubleQuote);  impl.after(__LINE__); }
\'                                       { /*146 */ impl.before(__LINE__); impl.add(BaseTokenKind::SingleQuote);  impl.after(__LINE__); }
\\\\                                     { /*147 */ impl.before(__LINE__); impl.add(BaseTokenKind::DoubleSlash);  impl.after(__LINE__); }
#\w+                                     { /*148 */ impl.before(__LINE__); impl.add(BaseTokenKind::HashIdent);  impl.after(__LINE__); }
##                                       { /*149 */ impl.before(__LINE__); impl.add(BaseTokenKind::DoubleHash);  impl.after(__LINE__); }
"("                                      { /*150 */ impl.before(__LINE__); impl.add(BaseTokenKind::LeftPar);  impl.after(__LINE__); }
")"                                      { /*151 */ impl.before(__LINE__); impl.add(BaseTokenKind::RightPar);  impl.after(__LINE__); }
"~"                                      { /*152 */ impl.before(__LINE__); impl.add(BaseTokenKind::Tilda);  impl.after(__LINE__); }
"="                                      { /*153 */ impl.before(__LINE__); impl.add(BaseTokenKind::Equals);  impl.after(__LINE__); }
";"                                      { /*154 */ impl.before(__LINE__); impl.add(BaseTokenKind::Semicolon);  impl.after(__LINE__); }
"*"                                      { /*155 */ impl.before(__LINE__); impl.add(BaseTokenKind::Asterisk);  impl.after(__LINE__); }
"<<"                                     { /*156 */ impl.before(__LINE__); impl.add(BaseTokenKind::DoubleLeftAngle);  impl.after(__LINE__); }
">>"                                     { /*157 */ impl.before(__LINE__); impl.add(BaseTokenKind::DoubleRightAngle);  impl.after(__LINE__); }
"<"                                      { /*158 */ impl.before(__LINE__); impl.add(BaseTokenKind::LeftAngle);  impl.after(__LINE__); }
">"                                      { /*159 */ impl.before(__LINE__); impl.add(BaseTokenKind::RightAngle);  impl.after(__LINE__); }
"^"                                      { /*160 */ impl.before(__LINE__); impl.add(BaseTokenKind::Circumflex);  impl.after(__LINE__); }
"{{{"                                    { /*161 */ impl.before(__LINE__); impl.add(BaseTokenKind::MacroBegin);  impl.after(__LINE__); }
"}}}"                                    { /*162 */ impl.before(__LINE__); impl.add(BaseTokenKind::MacroEnd);  impl.after(__LINE__); }
"{"                                      { /*163 */ impl.before(__LINE__); impl.add(BaseTokenKind::LeftCurly);  impl.after(__LINE__); }
"}"                                      { /*164 */ impl.before(__LINE__); impl.add(BaseTokenKind::RightCurly);  impl.after(__LINE__); }
\\.                                      { /*165 */ impl.before(__LINE__); impl.add(BaseTokenKind::EscapedChar);  impl.after(__LINE__); }
"%"                                      { /*166 */ impl.before(__LINE__); impl.add(BaseTokenKind::Percent);  impl.after(__LINE__); }
"@"                                      { /*167 */ impl.before(__LINE__); impl.add(BaseTokenKind::At);  impl.after(__LINE__); }
"|"                                      { /*168 */ impl.before(__LINE__); impl.add(BaseTokenKind::Pipe);  impl.after(__LINE__); }
"```"                                    { /*169 */ impl.before(__LINE__); impl.add(BaseTokenKind::TripleBacktick);  impl.after(__LINE__); }
"`"                                      { /*170 */ impl.before(__LINE__); impl.add(BaseTokenKind::Backtick);  impl.after(__LINE__); }
\p{Punctuation}                          { /*171 */ impl.before(__LINE__); impl.add(BaseTokenKind::AnyPunct);  impl.after(__LINE__); }
\w+                                      { /*172 */ impl.before(__LINE__); impl.add(BaseTokenKind::Word);  impl.after(__LINE__); }
\$                                       { /*173 */ impl.before(__LINE__); impl.add(BaseTokenKind::Dollar);  impl.after(__LINE__); }
[\x{0256}-\x{10FFFF}]|©                  { /*174 */ impl.before(__LINE__); impl.add(BaseTokenKind::MiscUnicode);  impl.after(__LINE__); }
\n                                       { /*175 */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline);  impl.after(__LINE__); }  

(.|\n) { impl.unknown(); }
<COMMAND>(.|\n) { impl.unknown(); }
<COMMAND_EXAMPLE>(.|\n) { impl.unknown(); }
<COMMAND_COLUMNS>(.|\n) { impl.unknown(); }
<COMMAND_SRC>(.|\n) { impl.unknown(); }
<PROPERTIES>(.|\n) { impl.unknown(); }
<PROPERTY_LITERAL>(.|\n) { impl.unknown(); }

%%

std::vector<BaseToken> tokenize(const char* input, int size) {
    base_lexer::Lexer lex(input);
    lex.impl.impl = &lex;
    lex.impl.tokens.reserve(size / 3);
    lex.lex();
    return lex.impl.tokens;
}

    