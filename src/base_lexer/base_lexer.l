

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
%state PROPERTY_LEAD
%state LOGBOOK_LEAD
%xstate COMMAND
%xstate COMMAND_EXAMPLE
%xstate COMMAND_COLUMNS
%xstate COMMAND_SRC
%xstate COMMAND_ARGS
%xstate COMMAND_TBLFM
%xstate BODY_SRC
%xstate PROPERTIES
%xstate PROPERTY_LITERAL

%class{
  public:
    BaseLexerImpl impl;
}

%%

<LEAD>"#+"                               { /*27  */ impl.before(__LINE__); impl.add(BaseTokenKind::LineCommand); pop_expect(LEAD, INITIAL); push_expect(INITIAL, COMMAND); impl.after(__LINE__); }
<COMMAND>"columns"                       { /*35  */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdColumns); push_expect(COMMAND, COMMAND_COLUMNS); impl.after(__LINE__); }
<COMMAND_COLUMNS>"%"                     { /*41  */ impl.before(__LINE__); impl.add(BaseTokenKind::Percent);  impl.after(__LINE__); }
<COMMAND_COLUMNS>\d+                     { /*42  */ impl.before(__LINE__); impl.add(BaseTokenKind::Digit);  impl.after(__LINE__); }
<COMMAND_COLUMNS>[a-zA-Z_]+              { /*43  */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdIdent);  impl.after(__LINE__); }
<COMMAND_COLUMNS>"("                     { /*44  */ impl.before(__LINE__); impl.add(BaseTokenKind::LeftPar);  impl.after(__LINE__); }
<COMMAND_COLUMNS>")"                     { /*45  */ impl.before(__LINE__); impl.add(BaseTokenKind::RightPar);  impl.after(__LINE__); }
<COMMAND_COLUMNS>"{"                     { /*46  */ impl.before(__LINE__); impl.add(BaseTokenKind::LeftCurly);  impl.after(__LINE__); }
<COMMAND_COLUMNS>"}"                     { /*47  */ impl.before(__LINE__); impl.add(BaseTokenKind::RightCurly);  impl.after(__LINE__); }
<COMMAND_COLUMNS>":"                     { /*48  */ impl.before(__LINE__); impl.add(BaseTokenKind::Colon);  impl.after(__LINE__); }
<COMMAND_COLUMNS>\h+                     { /*49  */ impl.before(__LINE__); impl.add(BaseTokenKind::Whitespace);  impl.after(__LINE__); }
<COMMAND_COLUMNS>\n                      { /*51  */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline); pop_expect(COMMAND_COLUMNS, COMMAND); pop_expect(COMMAND, INITIAL); impl.after(__LINE__); }
<COMMAND>"begin_quote"                   { /*59  */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdQuoteBegin); pop_expect(COMMAND, INITIAL); impl.after(__LINE__); }
<COMMAND>"end_quote"                     { /*64  */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdQuoteEnd); pop_expect(COMMAND, INITIAL); impl.after(__LINE__); }
<COMMAND>"begin_example"                 { /*70  */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdExampleBegin); push_expect(COMMAND, COMMAND_EXAMPLE); impl.after(__LINE__); }
<COMMAND_EXAMPLE>^\h*#\+end_example\h*$  { /*75  */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdExampleEnd); pop_expect(COMMAND_EXAMPLE, COMMAND); pop_expect(COMMAND, INITIAL); impl.after(__LINE__); }
<COMMAND_EXAMPLE>^.*$                    { /*82  */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdExampleLine);  impl.after(__LINE__); }
<COMMAND_EXAMPLE>\n                      { /*86  */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline);  impl.after(__LINE__); }
<COMMAND>begin_src                       { /*91  */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdSrcBegin); push_expect(COMMAND, COMMAND_SRC); impl.after(__LINE__); }
<BODY_SRC>^\h*#\+end_src\h*$             { /*95  */ impl.before(__LINE__); impl.add(BaseTokenKind::SrcContentEnd); pop_expect(BODY_SRC, INITIAL); impl.after(__LINE__); }
<COMMAND_SRC>\n                          { /*101 */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline); pop_expect(COMMAND_SRC, COMMAND); pop_expect(COMMAND, INITIAL); push_expect(INITIAL, BODY_SRC); impl.after(__LINE__); }
<BODY_SRC>"<<"                           { /*108 */ impl.before(__LINE__); impl.add(BaseTokenKind::SrcTangleOpen);  impl.after(__LINE__); }
<BODY_SRC>">>"                           { /*109 */ impl.before(__LINE__); impl.add(BaseTokenKind::SrcTangleClose);  impl.after(__LINE__); }
<BODY_SRC>.+                             { /*110 */ impl.before(__LINE__); impl.add(BaseTokenKind::SrcContent);  impl.after(__LINE__); }
<BODY_SRC>\n                             { /*111 */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline);  impl.after(__LINE__); }
<COMMAND_ARGS,COMMAND_SRC>:\w+           { /*114 */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdColonIdent);  impl.after(__LINE__); }
<COMMAND_ARGS,COMMAND_SRC>\w+            { /*115 */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdIdent);  impl.after(__LINE__); }
<COMMAND_ARGS,COMMAND_SRC>\h+            { /*116 */ impl.before(__LINE__); impl.add(BaseTokenKind::Whitespace);  impl.after(__LINE__); }
<COMMAND_ARGS,COMMAND_SRC>\H+            { /*117 */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdRawArg);  impl.after(__LINE__); }
<COMMAND>"caption"                       { /*120 */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdCaption); push_expect(COMMAND, COMMAND_TEXT); impl.after(__LINE__); }
<COMMAND_TEXT>\n                         { /*124 */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline); pop_expect(COMMAND_TEXT, COMMAND); pop_expect(COMMAND, INITIAL); impl.after(__LINE__); }
<COMMAND>"latex_header:"                 { /*132 */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdLatexHeader); push_expect(COMMAND, COMMAND_ARGS); impl.after(__LINE__); }
<COMMAND_ARGS>\n                         { /*136 */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline); pop_expect(COMMAND_ARGS, COMMAND); pop_expect(COMMAND, INITIAL); impl.after(__LINE__); }
<COMMAND>"tblfm:"                        { /*144 */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdTblfm); push_expect(COMMAND, COMMAND_TBLFM); impl.after(__LINE__); }
<COMMAND_TBLFM>\$\d+                     { /*148 */ impl.before(__LINE__); impl.add(BaseTokenKind::TblColumnRef);  impl.after(__LINE__); }
<COMMAND_TBLFM>=                         { /*149 */ impl.before(__LINE__); impl.add(BaseTokenKind::TblAssign);  impl.after(__LINE__); }
<COMMAND_TBLFM>@-?\d+                    { /*150 */ impl.before(__LINE__); impl.add(BaseTokenKind::TblRelativeColumnRef);  impl.after(__LINE__); }
<COMMAND_TBLFM>\n                        { /*152 */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline); pop_expect(COMMAND_TBLFM, COMMAND); pop_expect(COMMAND, INITIAL); impl.after(__LINE__); }
^\*+                                     { /*160 */ impl.before(__LINE__); impl.add(BaseTokenKind::SubtreeStars); push_expect(INITIAL, SUBTREE_HEAD); impl.after(__LINE__); }
<SUBTREE_HEAD>\[#\w\]                    { /*165 */ impl.before(__LINE__); impl.add(BaseTokenKind::SubtreePriority);  impl.after(__LINE__); }
<SUBTREE_HEAD>\n                         { /*169 */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline); pop_expect(SUBTREE_HEAD, INITIAL); impl.after(__LINE__); }
[0-9]+                                   { /*176 */ impl.before(__LINE__); impl.add(BaseTokenKind::Number);  impl.after(__LINE__); }
^\h+                                     { /*177 */ impl.before(__LINE__); impl.add(BaseTokenKind::LeadingSpace); push_expect(INITIAL, LEAD); impl.after(__LINE__); }
\h+                                      { /*182 */ impl.before(__LINE__); impl.add(BaseTokenKind::Whitespace);  impl.after(__LINE__); }
\[                                       { /*183 */ impl.before(__LINE__); impl.add(BaseTokenKind::BraceOpen);  impl.after(__LINE__); }
\]                                       { /*184 */ impl.before(__LINE__); impl.add(BaseTokenKind::BraceClose);  impl.after(__LINE__); }
\d{4}-\d{2}-\d{2}                        { /*185 */ impl.before(__LINE__); impl.add(BaseTokenKind::Date);  impl.after(__LINE__); }
\d{2}:\d{2}:\d{2}                        { /*186 */ impl.before(__LINE__); impl.add(BaseTokenKind::Time);  impl.after(__LINE__); }
=>                                       { /*187 */ impl.before(__LINE__); impl.add(BaseTokenKind::TimeArrow);  impl.after(__LINE__); }
#\h+.*?$                                 { /*188 */ impl.before(__LINE__); impl.add(BaseTokenKind::Comment);  impl.after(__LINE__); }
":LOGBOOK:"                              { /*189 */ impl.before(__LINE__); impl.add(BaseTokenKind::TreePropertyLogbook);  impl.after(__LINE__); }
<LEAD>":PROPERTIES:"                     { /*192 */ impl.before(__LINE__); impl.add(BaseTokenKind::TreePropertyProperties); pop_expect(LEAD, INITIAL); push_expect(INITIAL, PROPERTIES); impl.after(__LINE__); }
<PROPERTIES>\n                           { /*199 */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline);  impl.after(__LINE__); }
<PROPERTIES>^\h+                         { /*203 */ impl.before(__LINE__); impl.add(BaseTokenKind::LeadingSpace); push_expect(PROPERTIES, PROPERTY_LEAD); impl.after(__LINE__); }
<PROPERTY_LEAD>":END:"                   { /*209 */ impl.before(__LINE__); impl.add(BaseTokenKind::TreePropertyEnd); pop_expect(PROPERTY_LEAD, PROPERTIES); pop_expect(PROPERTIES, INITIAL); impl.after(__LINE__); }
<PROPERTY_LEAD>:(id|effort):             { /*216 */ impl.before(__LINE__); impl.add(BaseTokenKind::TreePropertyLiteral); pop_expect(PROPERTY_LEAD, PROPERTIES); push_expect(PROPERTIES, PROPERTY_LITERAL); impl.after(__LINE__); }
<PROPERTY_LITERAL>\h+                    { /*223 */ impl.before(__LINE__); impl.add(BaseTokenKind::Whitespace);  impl.after(__LINE__); }
<PROPERTY_LITERAL>.*$                    { /*227 */ impl.before(__LINE__); impl.add(BaseTokenKind::RawText);  impl.after(__LINE__); }
<PROPERTY_LITERAL>\n                     { /*231 */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline); pop_expect(PROPERTY_LITERAL, PROPERTIES); impl.after(__LINE__); }
<PROPERTY_LEAD>:(created|origin|blocker): { /*238 */ impl.before(__LINE__); impl.add(BaseTokenKind::TreePropertyText); pop_expect(PROPERTY_LEAD, PROPERTIES); push_expect(PROPERTIES, PROPERTY_ANY); impl.after(__LINE__); }
<PROPERTY_ANY>\n                         { /*245 */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline); pop_expect(PROPERTY_ANY, PROPERTIES); impl.after(__LINE__); }
<PROPERTIES>:\w+:                        { /*251 */ impl.before(__LINE__); impl.add(BaseTokenKind::TreePropertyName);  impl.after(__LINE__); }
"CLOCK:"                                 { /*255 */ impl.before(__LINE__); impl.add(BaseTokenKind::TreeClock);  impl.after(__LINE__); }
"&"                                      { /*256 */ impl.before(__LINE__); impl.add(BaseTokenKind::Ampersand);  impl.after(__LINE__); }
"!"                                      { /*257 */ impl.before(__LINE__); impl.add(BaseTokenKind::Exclamation);  impl.after(__LINE__); }
[,\./?]                                  { /*258 */ impl.before(__LINE__); impl.add(BaseTokenKind::AnyPunct);  impl.after(__LINE__); }
\+                                       { /*259 */ impl.before(__LINE__); impl.add(BaseTokenKind::Plus);  impl.after(__LINE__); }
\-                                       { /*260 */ impl.before(__LINE__); impl.add(BaseTokenKind::Minus);  impl.after(__LINE__); }
\"                                       { /*261 */ impl.before(__LINE__); impl.add(BaseTokenKind::DoubleQuote);  impl.after(__LINE__); }
\'                                       { /*262 */ impl.before(__LINE__); impl.add(BaseTokenKind::SingleQuote);  impl.after(__LINE__); }
\\\\                                     { /*263 */ impl.before(__LINE__); impl.add(BaseTokenKind::DoubleSlash);  impl.after(__LINE__); }
#\w+                                     { /*264 */ impl.before(__LINE__); impl.add(BaseTokenKind::HashIdent);  impl.after(__LINE__); }
##                                       { /*265 */ impl.before(__LINE__); impl.add(BaseTokenKind::DoubleHash);  impl.after(__LINE__); }
"("                                      { /*266 */ impl.before(__LINE__); impl.add(BaseTokenKind::LeftPar);  impl.after(__LINE__); }
")"                                      { /*267 */ impl.before(__LINE__); impl.add(BaseTokenKind::RightPar);  impl.after(__LINE__); }
"~"                                      { /*268 */ impl.before(__LINE__); impl.add(BaseTokenKind::Tilda);  impl.after(__LINE__); }
"="                                      { /*269 */ impl.before(__LINE__); impl.add(BaseTokenKind::Equals);  impl.after(__LINE__); }
";"                                      { /*270 */ impl.before(__LINE__); impl.add(BaseTokenKind::Semicolon);  impl.after(__LINE__); }
"*"                                      { /*271 */ impl.before(__LINE__); impl.add(BaseTokenKind::Asterisk);  impl.after(__LINE__); }
"<<"                                     { /*272 */ impl.before(__LINE__); impl.add(BaseTokenKind::DoubleLeftAngle);  impl.after(__LINE__); }
">>"                                     { /*273 */ impl.before(__LINE__); impl.add(BaseTokenKind::DoubleRightAngle);  impl.after(__LINE__); }
"<"                                      { /*274 */ impl.before(__LINE__); impl.add(BaseTokenKind::LeftAngle);  impl.after(__LINE__); }
">"                                      { /*275 */ impl.before(__LINE__); impl.add(BaseTokenKind::RightAngle);  impl.after(__LINE__); }
"^"                                      { /*276 */ impl.before(__LINE__); impl.add(BaseTokenKind::Circumflex);  impl.after(__LINE__); }
":"                                      { /*277 */ impl.before(__LINE__); impl.add(BaseTokenKind::Colon);  impl.after(__LINE__); }
"{{{"                                    { /*278 */ impl.before(__LINE__); impl.add(BaseTokenKind::MacroBegin);  impl.after(__LINE__); }
"}}}"                                    { /*279 */ impl.before(__LINE__); impl.add(BaseTokenKind::MacroEnd);  impl.after(__LINE__); }
"{"                                      { /*280 */ impl.before(__LINE__); impl.add(BaseTokenKind::LeftCurly);  impl.after(__LINE__); }
"}"                                      { /*281 */ impl.before(__LINE__); impl.add(BaseTokenKind::RightCurly);  impl.after(__LINE__); }
\\.                                      { /*282 */ impl.before(__LINE__); impl.add(BaseTokenKind::EscapedChar);  impl.after(__LINE__); }
"%"                                      { /*283 */ impl.before(__LINE__); impl.add(BaseTokenKind::Percent);  impl.after(__LINE__); }
"@"                                      { /*284 */ impl.before(__LINE__); impl.add(BaseTokenKind::At);  impl.after(__LINE__); }
"|"                                      { /*285 */ impl.before(__LINE__); impl.add(BaseTokenKind::Pipe);  impl.after(__LINE__); }
"```"                                    { /*286 */ impl.before(__LINE__); impl.add(BaseTokenKind::TripleBacktick);  impl.after(__LINE__); }
"`"                                      { /*287 */ impl.before(__LINE__); impl.add(BaseTokenKind::Backtick);  impl.after(__LINE__); }
\p{Punctuation}                          { /*288 */ impl.before(__LINE__); impl.add(BaseTokenKind::AnyPunct);  impl.after(__LINE__); }
\w+                                      { /*289 */ impl.before(__LINE__); impl.add(BaseTokenKind::Word);  impl.after(__LINE__); }
\$                                       { /*290 */ impl.before(__LINE__); impl.add(BaseTokenKind::Dollar);  impl.after(__LINE__); }
[\x{0256}-\x{10FFFF}]|©                  { /*291 */ impl.before(__LINE__); impl.add(BaseTokenKind::MiscUnicode);  impl.after(__LINE__); }
<LEAD>\n                                 { /*292 */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline); pop_expect(LEAD, INITIAL); impl.after(__LINE__); }
\n                                       { /*296 */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline);  impl.after(__LINE__); }  

(.|\n) { impl.unknown(); }
<COMMAND>(.|\n) { impl.unknown(); }
<COMMAND_EXAMPLE>(.|\n) { impl.unknown(); }
<COMMAND_COLUMNS>(.|\n) { impl.unknown(); }
<COMMAND_SRC>(.|\n) { impl.unknown(); }
<COMMAND_ARGS>(.|\n) { impl.unknown(); }
<COMMAND_TBLFM>(.|\n) { impl.unknown(); }
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

    