

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
%state LEAD
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

"#+"                                     { /*16  */ impl.before(__LINE__); impl.add(BaseTokenKind::LineCommand); push_expect(INITIAL, COMMAND); impl.after(__LINE__); }
<COMMAND>columns                         { /*21  */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdColumns); push_expect(COMMAND, COMMAND_COLUMNS); impl.after(__LINE__); }
<COMMAND_COLUMNS>"%"                     { /*27  */ impl.before(__LINE__); impl.add(BaseTokenKind::Percent);  impl.after(__LINE__); }
<COMMAND_COLUMNS>\d+                     { /*28  */ impl.before(__LINE__); impl.add(BaseTokenKind::Digit);  impl.after(__LINE__); }
<COMMAND_COLUMNS>[a-zA-Z_]+              { /*29  */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdIdent);  impl.after(__LINE__); }
<COMMAND_COLUMNS>"("                     { /*30  */ impl.before(__LINE__); impl.add(BaseTokenKind::LeftPar);  impl.after(__LINE__); }
<COMMAND_COLUMNS>")"                     { /*31  */ impl.before(__LINE__); impl.add(BaseTokenKind::RightPar);  impl.after(__LINE__); }
<COMMAND_COLUMNS>"{"                     { /*32  */ impl.before(__LINE__); impl.add(BaseTokenKind::LeftCurly);  impl.after(__LINE__); }
<COMMAND_COLUMNS>"}"                     { /*33  */ impl.before(__LINE__); impl.add(BaseTokenKind::RightCurly);  impl.after(__LINE__); }
<COMMAND_COLUMNS>":"                     { /*34  */ impl.before(__LINE__); impl.add(BaseTokenKind::Colon);  impl.after(__LINE__); }
<COMMAND_COLUMNS>\h+                     { /*35  */ impl.before(__LINE__); impl.add(BaseTokenKind::Whitespace);  impl.after(__LINE__); }
<COMMAND_COLUMNS>\n                      { /*37  */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline); pop_expect(COMMAND_COLUMNS, COMMAND); pop_expect(COMMAND, INITIAL); impl.after(__LINE__); }
<COMMAND>"begin_quote"                   { /*45  */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdQuoteBegin); pop_expect(COMMAND, INITIAL); impl.after(__LINE__); }
<COMMAND>"end_quote"                     { /*50  */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdQuoteEnd); pop_expect(COMMAND, INITIAL); impl.after(__LINE__); }
<COMMAND>"begin_example"                 { /*56  */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdExampleBegin); push_expect(COMMAND, COMMAND_EXAMPLE); impl.after(__LINE__); }
<COMMAND_EXAMPLE>^\h*#\+end_example\h*$  { /*61  */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdExampleEnd); pop_expect(COMMAND_EXAMPLE, COMMAND); pop_expect(COMMAND, INITIAL); impl.after(__LINE__); }
<COMMAND_EXAMPLE>^.*$                    { /*68  */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdExampleLine);  impl.after(__LINE__); }
<COMMAND_EXAMPLE>\n                      { /*72  */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline);  impl.after(__LINE__); }
<COMMAND>begin_src                       { /*77  */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdSrcBegin); push_expect(COMMAND, COMMAND_SRC); impl.after(__LINE__); }
<BODY_SRC>^\h*#\+end_src\h*$             { /*81  */ impl.before(__LINE__); impl.add(BaseTokenKind::SrcContentEnd); pop_expect(BODY_SRC, INITIAL); impl.after(__LINE__); }
<COMMAND_SRC>\n                          { /*87  */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline); pop_expect(COMMAND_SRC, COMMAND); pop_expect(COMMAND, INITIAL); push_expect(INITIAL, BODY_SRC); impl.after(__LINE__); }
<BODY_SRC>"<<"                           { /*94  */ impl.before(__LINE__); impl.add(BaseTokenKind::SrcTangleOpen);  impl.after(__LINE__); }
<BODY_SRC>">>"                           { /*95  */ impl.before(__LINE__); impl.add(BaseTokenKind::SrcTangleClose);  impl.after(__LINE__); }
<BODY_SRC>.+                             { /*96  */ impl.before(__LINE__); impl.add(BaseTokenKind::SrcContent);  impl.after(__LINE__); }
<BODY_SRC>\n                             { /*97  */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline);  impl.after(__LINE__); }
<COMMAND_SRC>:\w+                        { /*100 */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdColonIdent);  impl.after(__LINE__); }
<COMMAND_SRC>\w+                         { /*101 */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdIdent);  impl.after(__LINE__); }
<COMMAND_SRC>\h+                         { /*102 */ impl.before(__LINE__); impl.add(BaseTokenKind::Whitespace);  impl.after(__LINE__); }
<COMMAND>"caption"                       { /*105 */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdCaption); push_expect(COMMAND, COMMAND_TEXT); impl.after(__LINE__); }
<COMMAND_TEXT>\n                         { /*109 */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline); pop_expect(COMMAND_TEXT, COMMAND); pop_expect(COMMAND, INITIAL); impl.after(__LINE__); }
^\*+                                     { /*116 */ impl.before(__LINE__); impl.add(BaseTokenKind::SubtreeStars); push_expect(INITIAL, SUBTREE_HEAD); impl.after(__LINE__); }
<SUBTREE_HEAD>\[#\w\]                    { /*121 */ impl.before(__LINE__); impl.add(BaseTokenKind::SubtreePriority);  impl.after(__LINE__); }
<SUBTREE_HEAD>\n                         { /*125 */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline); pop_expect(SUBTREE_HEAD, INITIAL); impl.after(__LINE__); }
[0-9]+                                   { /*132 */ impl.before(__LINE__); impl.add(BaseTokenKind::Number);  impl.after(__LINE__); }
^\h+                                     { /*133 */ impl.before(__LINE__); impl.add(BaseTokenKind::LeadingSpace);  impl.after(__LINE__); }
\h+                                      { /*134 */ impl.before(__LINE__); impl.add(BaseTokenKind::Whitespace);  impl.after(__LINE__); }
\[                                       { /*135 */ impl.before(__LINE__); impl.add(BaseTokenKind::BraceOpen);  impl.after(__LINE__); }
\]                                       { /*136 */ impl.before(__LINE__); impl.add(BaseTokenKind::BraceClose);  impl.after(__LINE__); }
\d{4}-\d{2}-\d{2}                        { /*137 */ impl.before(__LINE__); impl.add(BaseTokenKind::Date);  impl.after(__LINE__); }
\d{2}:\d{2}:\d{2}                        { /*138 */ impl.before(__LINE__); impl.add(BaseTokenKind::Time);  impl.after(__LINE__); }
=>                                       { /*139 */ impl.before(__LINE__); impl.add(BaseTokenKind::TimeArrow);  impl.after(__LINE__); }
#\h+.*?$                                 { /*140 */ impl.before(__LINE__); impl.add(BaseTokenKind::Comment);  impl.after(__LINE__); }
":LOGBOOK:"                              { /*141 */ impl.before(__LINE__); impl.add(BaseTokenKind::TreePropertyLogbook);  impl.after(__LINE__); }
":PROPERTIES:"                           { /*143 */ impl.before(__LINE__); impl.add(BaseTokenKind::TreePropertyProperties); push_expect(INITIAL, PROPERTIES); impl.after(__LINE__); }
<PROPERTIES>\n                           { /*148 */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline);  impl.after(__LINE__); }
<PROPERTIES>^\h+                         { /*152 */ impl.before(__LINE__); impl.add(BaseTokenKind::LeadingSpace);  impl.after(__LINE__); }
<PROPERTIES>":END:"                      { /*156 */ impl.before(__LINE__); impl.add(BaseTokenKind::TreePropertyEnd); pop_expect(PROPERTIES, INITIAL); impl.after(__LINE__); }
<PROPERTIES>:(id|effort):                { /*162 */ impl.before(__LINE__); impl.add(BaseTokenKind::TreePropertyLiteral); push_expect(PROPERTIES, PROPERTY_LITERAL); impl.after(__LINE__); }
<PROPERTY_LITERAL>\h+                    { /*168 */ impl.before(__LINE__); impl.add(BaseTokenKind::Whitespace);  impl.after(__LINE__); }
<PROPERTY_LITERAL>.*$                    { /*172 */ impl.before(__LINE__); impl.add(BaseTokenKind::RawText);  impl.after(__LINE__); }
<PROPERTY_LITERAL>\n                     { /*176 */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline); pop_expect(PROPERTY_LITERAL, PROPERTIES); impl.after(__LINE__); }
<PROPERTIES>:(created|origin|blocker):   { /*183 */ impl.before(__LINE__); impl.add(BaseTokenKind::TreePropertyText); push_expect(PROPERTIES, PROPERTY_ANY); impl.after(__LINE__); }
<PROPERTY_ANY>\n                         { /*189 */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline); pop_expect(PROPERTY_ANY, PROPERTIES); impl.after(__LINE__); }
<PROPERTIES>:\w+:                        { /*195 */ impl.before(__LINE__); impl.add(BaseTokenKind::TreePropertyName);  impl.after(__LINE__); }
"CLOCK:"                                 { /*199 */ impl.before(__LINE__); impl.add(BaseTokenKind::TreeClock);  impl.after(__LINE__); }
"&"                                      { /*200 */ impl.before(__LINE__); impl.add(BaseTokenKind::Ampersand);  impl.after(__LINE__); }
"!"                                      { /*201 */ impl.before(__LINE__); impl.add(BaseTokenKind::Exclamation);  impl.after(__LINE__); }
[,\./?]                                  { /*202 */ impl.before(__LINE__); impl.add(BaseTokenKind::AnyPunct);  impl.after(__LINE__); }
\+                                       { /*203 */ impl.before(__LINE__); impl.add(BaseTokenKind::Plus);  impl.after(__LINE__); }
\-                                       { /*204 */ impl.before(__LINE__); impl.add(BaseTokenKind::Minus);  impl.after(__LINE__); }
\"                                       { /*205 */ impl.before(__LINE__); impl.add(BaseTokenKind::DoubleQuote);  impl.after(__LINE__); }
\'                                       { /*206 */ impl.before(__LINE__); impl.add(BaseTokenKind::SingleQuote);  impl.after(__LINE__); }
\\\\                                     { /*207 */ impl.before(__LINE__); impl.add(BaseTokenKind::DoubleSlash);  impl.after(__LINE__); }
#\w+                                     { /*208 */ impl.before(__LINE__); impl.add(BaseTokenKind::HashIdent);  impl.after(__LINE__); }
##                                       { /*209 */ impl.before(__LINE__); impl.add(BaseTokenKind::DoubleHash);  impl.after(__LINE__); }
"("                                      { /*210 */ impl.before(__LINE__); impl.add(BaseTokenKind::LeftPar);  impl.after(__LINE__); }
")"                                      { /*211 */ impl.before(__LINE__); impl.add(BaseTokenKind::RightPar);  impl.after(__LINE__); }
"~"                                      { /*212 */ impl.before(__LINE__); impl.add(BaseTokenKind::Tilda);  impl.after(__LINE__); }
"="                                      { /*213 */ impl.before(__LINE__); impl.add(BaseTokenKind::Equals);  impl.after(__LINE__); }
";"                                      { /*214 */ impl.before(__LINE__); impl.add(BaseTokenKind::Semicolon);  impl.after(__LINE__); }
"*"                                      { /*215 */ impl.before(__LINE__); impl.add(BaseTokenKind::Asterisk);  impl.after(__LINE__); }
"<<"                                     { /*216 */ impl.before(__LINE__); impl.add(BaseTokenKind::DoubleLeftAngle);  impl.after(__LINE__); }
">>"                                     { /*217 */ impl.before(__LINE__); impl.add(BaseTokenKind::DoubleRightAngle);  impl.after(__LINE__); }
"<"                                      { /*218 */ impl.before(__LINE__); impl.add(BaseTokenKind::LeftAngle);  impl.after(__LINE__); }
">"                                      { /*219 */ impl.before(__LINE__); impl.add(BaseTokenKind::RightAngle);  impl.after(__LINE__); }
"^"                                      { /*220 */ impl.before(__LINE__); impl.add(BaseTokenKind::Circumflex);  impl.after(__LINE__); }
":"                                      { /*221 */ impl.before(__LINE__); impl.add(BaseTokenKind::Colon);  impl.after(__LINE__); }
"{{{"                                    { /*222 */ impl.before(__LINE__); impl.add(BaseTokenKind::MacroBegin);  impl.after(__LINE__); }
"}}}"                                    { /*223 */ impl.before(__LINE__); impl.add(BaseTokenKind::MacroEnd);  impl.after(__LINE__); }
"{"                                      { /*224 */ impl.before(__LINE__); impl.add(BaseTokenKind::LeftCurly);  impl.after(__LINE__); }
"}"                                      { /*225 */ impl.before(__LINE__); impl.add(BaseTokenKind::RightCurly);  impl.after(__LINE__); }
\\.                                      { /*226 */ impl.before(__LINE__); impl.add(BaseTokenKind::EscapedChar);  impl.after(__LINE__); }
"%"                                      { /*227 */ impl.before(__LINE__); impl.add(BaseTokenKind::Percent);  impl.after(__LINE__); }
"@"                                      { /*228 */ impl.before(__LINE__); impl.add(BaseTokenKind::At);  impl.after(__LINE__); }
"|"                                      { /*229 */ impl.before(__LINE__); impl.add(BaseTokenKind::Pipe);  impl.after(__LINE__); }
"```"                                    { /*230 */ impl.before(__LINE__); impl.add(BaseTokenKind::TripleBacktick);  impl.after(__LINE__); }
"`"                                      { /*231 */ impl.before(__LINE__); impl.add(BaseTokenKind::Backtick);  impl.after(__LINE__); }
\p{Punctuation}                          { /*232 */ impl.before(__LINE__); impl.add(BaseTokenKind::AnyPunct);  impl.after(__LINE__); }
\w+                                      { /*233 */ impl.before(__LINE__); impl.add(BaseTokenKind::Word);  impl.after(__LINE__); }
\$                                       { /*234 */ impl.before(__LINE__); impl.add(BaseTokenKind::Dollar);  impl.after(__LINE__); }
[\x{0256}-\x{10FFFF}]|©                  { /*235 */ impl.before(__LINE__); impl.add(BaseTokenKind::MiscUnicode);  impl.after(__LINE__); }
\n                                       { /*236 */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline);  impl.after(__LINE__); }  

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

    