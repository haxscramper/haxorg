

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

<LEAD>"#+"                               { /*24  */ impl.before(__LINE__); impl.add(BaseTokenKind::LineCommand); pop_expect(LEAD, INITIAL); push_expect(INITIAL, COMMAND); impl.after(__LINE__); }
<COMMAND>"columns"                       { /*32  */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdColumns); push_expect(COMMAND, COMMAND_COLUMNS); impl.after(__LINE__); }
<COMMAND_COLUMNS>"%"                     { /*38  */ impl.before(__LINE__); impl.add(BaseTokenKind::Percent);  impl.after(__LINE__); }
<COMMAND_COLUMNS>\d+                     { /*39  */ impl.before(__LINE__); impl.add(BaseTokenKind::Digit);  impl.after(__LINE__); }
<COMMAND_COLUMNS>[a-zA-Z_]+              { /*40  */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdIdent);  impl.after(__LINE__); }
<COMMAND_COLUMNS>"("                     { /*41  */ impl.before(__LINE__); impl.add(BaseTokenKind::LeftPar);  impl.after(__LINE__); }
<COMMAND_COLUMNS>")"                     { /*42  */ impl.before(__LINE__); impl.add(BaseTokenKind::RightPar);  impl.after(__LINE__); }
<COMMAND_COLUMNS>"{"                     { /*43  */ impl.before(__LINE__); impl.add(BaseTokenKind::LeftCurly);  impl.after(__LINE__); }
<COMMAND_COLUMNS>"}"                     { /*44  */ impl.before(__LINE__); impl.add(BaseTokenKind::RightCurly);  impl.after(__LINE__); }
<COMMAND_COLUMNS>":"                     { /*45  */ impl.before(__LINE__); impl.add(BaseTokenKind::Colon);  impl.after(__LINE__); }
<COMMAND_COLUMNS>\h+                     { /*46  */ impl.before(__LINE__); impl.add(BaseTokenKind::Whitespace);  impl.after(__LINE__); }
<COMMAND_COLUMNS>\n                      { /*48  */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline); pop_expect(COMMAND_COLUMNS, COMMAND); pop_expect(COMMAND, INITIAL); impl.after(__LINE__); }
<COMMAND>"begin_quote"                   { /*56  */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdQuoteBegin); pop_expect(COMMAND, INITIAL); impl.after(__LINE__); }
<COMMAND>"end_quote"                     { /*61  */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdQuoteEnd); pop_expect(COMMAND, INITIAL); impl.after(__LINE__); }
<COMMAND>"begin_example"                 { /*67  */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdExampleBegin); push_expect(COMMAND, COMMAND_EXAMPLE); impl.after(__LINE__); }
<COMMAND_EXAMPLE>^\h*#\+end_example\h*$  { /*72  */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdExampleEnd); pop_expect(COMMAND_EXAMPLE, COMMAND); pop_expect(COMMAND, INITIAL); impl.after(__LINE__); }
<COMMAND_EXAMPLE>^.*$                    { /*79  */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdExampleLine);  impl.after(__LINE__); }
<COMMAND_EXAMPLE>\n                      { /*83  */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline);  impl.after(__LINE__); }
<COMMAND>begin_src                       { /*88  */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdSrcBegin); push_expect(COMMAND, COMMAND_SRC); impl.after(__LINE__); }
<BODY_SRC>^\h*#\+end_src\h*$             { /*92  */ impl.before(__LINE__); impl.add(BaseTokenKind::SrcContentEnd); pop_expect(BODY_SRC, INITIAL); impl.after(__LINE__); }
<COMMAND_SRC>\n                          { /*98  */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline); pop_expect(COMMAND_SRC, COMMAND); pop_expect(COMMAND, INITIAL); push_expect(INITIAL, BODY_SRC); impl.after(__LINE__); }
<BODY_SRC>"<<"                           { /*105 */ impl.before(__LINE__); impl.add(BaseTokenKind::SrcTangleOpen);  impl.after(__LINE__); }
<BODY_SRC>">>"                           { /*106 */ impl.before(__LINE__); impl.add(BaseTokenKind::SrcTangleClose);  impl.after(__LINE__); }
<BODY_SRC>.+                             { /*107 */ impl.before(__LINE__); impl.add(BaseTokenKind::SrcContent);  impl.after(__LINE__); }
<BODY_SRC>\n                             { /*108 */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline);  impl.after(__LINE__); }
<COMMAND_ARGS,COMMAND_SRC>:\w+           { /*111 */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdColonIdent);  impl.after(__LINE__); }
<COMMAND_ARGS,COMMAND_SRC>\w+            { /*112 */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdIdent);  impl.after(__LINE__); }
<COMMAND_ARGS,COMMAND_SRC>\h+            { /*113 */ impl.before(__LINE__); impl.add(BaseTokenKind::Whitespace);  impl.after(__LINE__); }
<COMMAND_ARGS,COMMAND_SRC>\H+            { /*114 */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdRawArg);  impl.after(__LINE__); }
<COMMAND>"caption"                       { /*117 */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdCaption); push_expect(COMMAND, COMMAND_TEXT); impl.after(__LINE__); }
<COMMAND_TEXT>\n                         { /*121 */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline); pop_expect(COMMAND_TEXT, COMMAND); pop_expect(COMMAND, INITIAL); impl.after(__LINE__); }
<COMMAND>"latex_header:"                 { /*129 */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdLatexHeader); push_expect(COMMAND, COMMAND_ARGS); impl.after(__LINE__); }
<COMMAND_ARGS>\n                         { /*133 */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline); pop_expect(COMMAND_ARGS, COMMAND); pop_expect(COMMAND, INITIAL); impl.after(__LINE__); }
<COMMAND>"tblfm:"                        { /*141 */ impl.before(__LINE__); impl.add(BaseTokenKind::CmdTblfm); push_expect(COMMAND, COMMAND_TBLFM); impl.after(__LINE__); }
<COMMAND_TBLFM>\$\d+                     { /*145 */ impl.before(__LINE__); impl.add(BaseTokenKind::TblColumnRef);  impl.after(__LINE__); }
<COMMAND_TBLFM>=                         { /*146 */ impl.before(__LINE__); impl.add(BaseTokenKind::TblAssign);  impl.after(__LINE__); }
<COMMAND_TBLFM>@-?\d+                    { /*147 */ impl.before(__LINE__); impl.add(BaseTokenKind::TblRelativeColumnRef);  impl.after(__LINE__); }
<COMMAND_TBLFM>\n                        { /*149 */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline); pop_expect(COMMAND_TBLFM, COMMAND); pop_expect(COMMAND, INITIAL); impl.after(__LINE__); }
^\*+                                     { /*157 */ impl.before(__LINE__); impl.add(BaseTokenKind::SubtreeStars); push_expect(INITIAL, SUBTREE_HEAD); impl.after(__LINE__); }
<SUBTREE_HEAD>\[#\w\]                    { /*162 */ impl.before(__LINE__); impl.add(BaseTokenKind::SubtreePriority);  impl.after(__LINE__); }
<SUBTREE_HEAD>\n                         { /*166 */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline); pop_expect(SUBTREE_HEAD, INITIAL); impl.after(__LINE__); }
[0-9]+                                   { /*173 */ impl.before(__LINE__); impl.add(BaseTokenKind::Number);  impl.after(__LINE__); }
^\h+                                     { /*174 */ impl.before(__LINE__); impl.add(BaseTokenKind::LeadingSpace); push_expect(INITIAL, LEAD); impl.after(__LINE__); }
\h+                                      { /*179 */ impl.before(__LINE__); impl.add(BaseTokenKind::Whitespace);  impl.after(__LINE__); }
\[                                       { /*180 */ impl.before(__LINE__); impl.add(BaseTokenKind::BraceOpen);  impl.after(__LINE__); }
\]                                       { /*181 */ impl.before(__LINE__); impl.add(BaseTokenKind::BraceClose);  impl.after(__LINE__); }
\d{4}-\d{2}-\d{2}                        { /*182 */ impl.before(__LINE__); impl.add(BaseTokenKind::Date);  impl.after(__LINE__); }
\d{2}:\d{2}:\d{2}                        { /*183 */ impl.before(__LINE__); impl.add(BaseTokenKind::Time);  impl.after(__LINE__); }
=>                                       { /*184 */ impl.before(__LINE__); impl.add(BaseTokenKind::TimeArrow);  impl.after(__LINE__); }
#\h+.*?$                                 { /*185 */ impl.before(__LINE__); impl.add(BaseTokenKind::Comment);  impl.after(__LINE__); }
":LOGBOOK:"                              { /*186 */ impl.before(__LINE__); impl.add(BaseTokenKind::TreePropertyLogbook);  impl.after(__LINE__); }
<LEAD>":PROPERTIES:"                     { /*189 */ impl.before(__LINE__); impl.add(BaseTokenKind::TreePropertyProperties); pop_expect(LEAD, INITIAL); push_expect(INITIAL, PROPERTIES); impl.after(__LINE__); }
<PROPERTIES>\n                           { /*196 */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline);  impl.after(__LINE__); }
<PROPERTIES>^\h+                         { /*200 */ impl.before(__LINE__); impl.add(BaseTokenKind::LeadingSpace); push_expect(PROPERTIES, PROPERTY_LEAD); impl.after(__LINE__); }
<PROPERTY_LEAD>":END:"                   { /*206 */ impl.before(__LINE__); impl.add(BaseTokenKind::TreePropertyEnd); pop_expect(PROPERTY_LEAD, PROPERTIES); pop_expect(PROPERTIES, INITIAL); impl.after(__LINE__); }
<PROPERTY_LEAD>:(id|effort):             { /*213 */ impl.before(__LINE__); impl.add(BaseTokenKind::TreePropertyLiteral); pop_expect(PROPERTY_LEAD, PROPERTIES); push_expect(PROPERTIES, PROPERTY_LITERAL); impl.after(__LINE__); }
<PROPERTY_LITERAL>\h+                    { /*220 */ impl.before(__LINE__); impl.add(BaseTokenKind::Whitespace);  impl.after(__LINE__); }
<PROPERTY_LITERAL>.*$                    { /*224 */ impl.before(__LINE__); impl.add(BaseTokenKind::RawText);  impl.after(__LINE__); }
<PROPERTY_LITERAL>\n                     { /*228 */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline); pop_expect(PROPERTY_LITERAL, PROPERTIES); impl.after(__LINE__); }
<PROPERTY_LEAD>:(created|origin|blocker): { /*235 */ impl.before(__LINE__); impl.add(BaseTokenKind::TreePropertyText); pop_expect(PROPERTY_LEAD, PROPERTIES); push_expect(PROPERTIES, PROPERTY_ANY); impl.after(__LINE__); }
<PROPERTY_ANY>\n                         { /*242 */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline); pop_expect(PROPERTY_ANY, PROPERTIES); impl.after(__LINE__); }
<PROPERTIES>:\w+:                        { /*248 */ impl.before(__LINE__); impl.add(BaseTokenKind::TreePropertyName);  impl.after(__LINE__); }
"CLOCK:"                                 { /*252 */ impl.before(__LINE__); impl.add(BaseTokenKind::TreeClock);  impl.after(__LINE__); }
"&"                                      { /*253 */ impl.before(__LINE__); impl.add(BaseTokenKind::Ampersand);  impl.after(__LINE__); }
"!"                                      { /*254 */ impl.before(__LINE__); impl.add(BaseTokenKind::Exclamation);  impl.after(__LINE__); }
[,\./?]                                  { /*255 */ impl.before(__LINE__); impl.add(BaseTokenKind::AnyPunct);  impl.after(__LINE__); }
\+                                       { /*256 */ impl.before(__LINE__); impl.add(BaseTokenKind::Plus);  impl.after(__LINE__); }
\-                                       { /*257 */ impl.before(__LINE__); impl.add(BaseTokenKind::Minus);  impl.after(__LINE__); }
\"                                       { /*258 */ impl.before(__LINE__); impl.add(BaseTokenKind::DoubleQuote);  impl.after(__LINE__); }
\'                                       { /*259 */ impl.before(__LINE__); impl.add(BaseTokenKind::SingleQuote);  impl.after(__LINE__); }
\\\\                                     { /*260 */ impl.before(__LINE__); impl.add(BaseTokenKind::DoubleSlash);  impl.after(__LINE__); }
#\w+                                     { /*261 */ impl.before(__LINE__); impl.add(BaseTokenKind::HashIdent);  impl.after(__LINE__); }
##                                       { /*262 */ impl.before(__LINE__); impl.add(BaseTokenKind::DoubleHash);  impl.after(__LINE__); }
"("                                      { /*263 */ impl.before(__LINE__); impl.add(BaseTokenKind::LeftPar);  impl.after(__LINE__); }
")"                                      { /*264 */ impl.before(__LINE__); impl.add(BaseTokenKind::RightPar);  impl.after(__LINE__); }
"~"                                      { /*265 */ impl.before(__LINE__); impl.add(BaseTokenKind::Tilda);  impl.after(__LINE__); }
"="                                      { /*266 */ impl.before(__LINE__); impl.add(BaseTokenKind::Equals);  impl.after(__LINE__); }
";"                                      { /*267 */ impl.before(__LINE__); impl.add(BaseTokenKind::Semicolon);  impl.after(__LINE__); }
"*"                                      { /*268 */ impl.before(__LINE__); impl.add(BaseTokenKind::Asterisk);  impl.after(__LINE__); }
"<<"                                     { /*269 */ impl.before(__LINE__); impl.add(BaseTokenKind::DoubleLeftAngle);  impl.after(__LINE__); }
">>"                                     { /*270 */ impl.before(__LINE__); impl.add(BaseTokenKind::DoubleRightAngle);  impl.after(__LINE__); }
"<"                                      { /*271 */ impl.before(__LINE__); impl.add(BaseTokenKind::LeftAngle);  impl.after(__LINE__); }
">"                                      { /*272 */ impl.before(__LINE__); impl.add(BaseTokenKind::RightAngle);  impl.after(__LINE__); }
"^"                                      { /*273 */ impl.before(__LINE__); impl.add(BaseTokenKind::Circumflex);  impl.after(__LINE__); }
":"                                      { /*274 */ impl.before(__LINE__); impl.add(BaseTokenKind::Colon);  impl.after(__LINE__); }
"{{{"                                    { /*275 */ impl.before(__LINE__); impl.add(BaseTokenKind::MacroBegin);  impl.after(__LINE__); }
"}}}"                                    { /*276 */ impl.before(__LINE__); impl.add(BaseTokenKind::MacroEnd);  impl.after(__LINE__); }
"{"                                      { /*277 */ impl.before(__LINE__); impl.add(BaseTokenKind::LeftCurly);  impl.after(__LINE__); }
"}"                                      { /*278 */ impl.before(__LINE__); impl.add(BaseTokenKind::RightCurly);  impl.after(__LINE__); }
\\.                                      { /*279 */ impl.before(__LINE__); impl.add(BaseTokenKind::EscapedChar);  impl.after(__LINE__); }
"%"                                      { /*280 */ impl.before(__LINE__); impl.add(BaseTokenKind::Percent);  impl.after(__LINE__); }
"@"                                      { /*281 */ impl.before(__LINE__); impl.add(BaseTokenKind::At);  impl.after(__LINE__); }
"|"                                      { /*282 */ impl.before(__LINE__); impl.add(BaseTokenKind::Pipe);  impl.after(__LINE__); }
"```"                                    { /*283 */ impl.before(__LINE__); impl.add(BaseTokenKind::TripleBacktick);  impl.after(__LINE__); }
"`"                                      { /*284 */ impl.before(__LINE__); impl.add(BaseTokenKind::Backtick);  impl.after(__LINE__); }
\p{Punctuation}                          { /*285 */ impl.before(__LINE__); impl.add(BaseTokenKind::AnyPunct);  impl.after(__LINE__); }
\w+                                      { /*286 */ impl.before(__LINE__); impl.add(BaseTokenKind::Word);  impl.after(__LINE__); }
\$                                       { /*287 */ impl.before(__LINE__); impl.add(BaseTokenKind::Dollar);  impl.after(__LINE__); }
[\x{0256}-\x{10FFFF}]|©                  { /*288 */ impl.before(__LINE__); impl.add(BaseTokenKind::MiscUnicode);  impl.after(__LINE__); }
<LEAD>\n                                 { /*289 */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline); pop_expect(LEAD, INITIAL); impl.after(__LINE__); }
\n                                       { /*293 */ impl.before(__LINE__); impl.add(BaseTokenKind::Newline);  impl.after(__LINE__); }  

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

    