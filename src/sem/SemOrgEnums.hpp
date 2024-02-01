/* clang-format off */
#pragma once
#include <hstd/system/basic_templates.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/Opt.hpp>
#define EACH_SEM_ORG_KIND(__IMPL) \
    __IMPL(StmtList) \
    __IMPL(Empty) \
    __IMPL(Row) \
    __IMPL(Table) \
    __IMPL(HashTag) \
    __IMPL(Footnote) \
    __IMPL(Completion) \
    __IMPL(Paragraph) \
    __IMPL(Center) \
    __IMPL(Caption) \
    __IMPL(CommandGroup) \
    __IMPL(Quote) \
    __IMPL(Example) \
    __IMPL(CmdArguments) \
    __IMPL(CmdArgument) \
    __IMPL(Export) \
    __IMPL(AdmonitionBlock) \
    __IMPL(Code) \
    __IMPL(Time) \
    __IMPL(TimeRange) \
    __IMPL(Macro) \
    __IMPL(Symbol) \
    __IMPL(SubtreeLog) \
    __IMPL(Subtree) \
    __IMPL(InlineMath) \
    __IMPL(Escaped) \
    __IMPL(Newline) \
    __IMPL(Space) \
    __IMPL(Word) \
    __IMPL(AtMention) \
    __IMPL(RawText) \
    __IMPL(Punctuation) \
    __IMPL(Placeholder) \
    __IMPL(BigIdent) \
    __IMPL(Bold) \
    __IMPL(Underline) \
    __IMPL(Monospace) \
    __IMPL(MarkQuote) \
    __IMPL(Verbatim) \
    __IMPL(Italic) \
    __IMPL(Strike) \
    __IMPL(Par) \
    __IMPL(List) \
    __IMPL(ListItem) \
    __IMPL(Link) \
    __IMPL(Document) \
    __IMPL(ParseError) \
    __IMPL(FileTarget) \
    __IMPL(TextSeparator) \
    __IMPL(Include) \
    __IMPL(DocumentOptions) \
    __IMPL(DocumentGroup)
enum class OrgSpecName : short int { Unnamed, Result, Year, Day, Clock, Repeater, Zone, Link, Tags, Tag, State, Protocol, Desc, Times, Drawer, Args, Name, Definition, Body, HeaderArgs, File, Kind, Lang, Prefix, Text, Todo, Urgency, Title, Completion, Head, Subnodes, Properties, Logbook, Description, Logs, Newstate, Oldstate, Time, From, EndArgs, Flags, Value, Assoc, Main, Hash, Bullet, Counter, Checkbox, Header, To, Diff, Property, Subname, Values, Cells, Rows, Lines, Chunks, InheritanceMode, MainSetRule, SubSetRule, };
template <>
struct enum_serde<OrgSpecName> {
  static Opt<OrgSpecName> from_string(std::string value);
  static std::string to_string(OrgSpecName value);
};

template <>
struct value_domain<OrgSpecName> : public value_domain_ungapped<OrgSpecName,
                                                                OrgSpecName::Unnamed,
                                                                OrgSpecName::SubSetRule> {};

enum class OrgNodeKind : short int {
  /// \brief Default valye for node - invalid state
  None,
  /// \brief Toplevel part of the ast, not created by parser, and only used in `semorg` stage
  Document,
  /// \brief User-defined node [[code:OrgUserNode]]
  UserNode,
  /// \brief Empty node - valid state that does not contain any value
  Empty,
  /// \brief Failed node parse
  ///
  ///
  ///    Failed node parse - technically there are no /wrong/ syntax in the
  ///    org-mode document because everything can be considered a one large
  ///    word or a paragraph with flat `Word` content.
  ///
  ///    Error node's extent covers all subnodes that were constructed
  ///    during nested content parsing plus ErrorTerminator node with error
  ///    token (description of the parsing failure). So failure node will be
  ///    structured as `[Error <some content> <ErrorToken>
  ///    <ErrorTermiator>]`. Second-to-last is the invalid token itself,
  ///    error terminator will hold fake token that referes to an error.
  ///
  ///    Error node can be produced by any parsing routine, although it is
  ///    mostly used in the low-level text elements, since high-level
  ///    structures are mostly detected based on the correct syntax - for
  ///    example, `*** subtree` (and any title variations) can never be an
  ///    error in itself. Title /text/ might contain an error, but invalid
  ///    it is not possible to write an invalid subtree - it is either `*
  ///    ANYTHING` or not a subtree at all.
  ///
  Error,
  /// \brief Terminator node for failure in nested structure parsing
  ErrorTerminator,
  /// \brief Single invalid token
  ErrorToken,
  InlineStmtList,
  /// \brief List of statements, possibly recursive. Used as toplevel part of the document, in recursive parsing of subtrees, or as regular list, in cases where multiple subnodes have to be grouped together.
  StmtList,
  /// \brief Associated list of statements - AST elements like commands and links are grouped together if placed on adjacent lines
  AssocStmtList,
  /// \brief Section subtree
  Subtree,
  /// \brief Time? associated with subtree entry
  SubtreeTimes,
  SubtreeStars,
  /// \brief Task compleation cookie, indicated either in percents of completion, or as `<done>/<todo>` ratio.
  Completion,
  /// \brief Single checkbox item like `[X]` or `[-]`
  Checkbox,
  List,
  /// \brief List item prefix
  Bullet,
  ListItem,
  /// \brief Auxilliary wrapper for the paragraph placed at the start of the description list.
  ListTag,
  Counter,
  /// \brief Inline or trailling comment. Can be used addition to `#+comment:` line or `#+begin-comment` section. Nested comment syntax is allowed (`#[ level1 #[ level2 ]# ]#`), but only outermost one is represented as separate AST node, everything else is a `.text`
  Comment,
  /// \brief Raw string of text from input buffer. Things like particular syntax details of every single command, link formats are not handled in parser, deferring formatting to future processing layers
  RawText,
  /// \brief Part of the org-mode document that is yet to be parsed. This node should not be created manually, it is only used for handling mutually recursive DSLs such as tables, which might include lists, which in turn might contain more tables in different bullet points.
  Unparsed,
  /// \brief Undefined single-line command -- most likely custom user-provided oe
  Command,
  /// \brief Arguments for the command block
  CommandArguments,
  /// \brief `#+title:` - full document title
  CommandTitle,
  /// \brief `#+author:` Document author
  CommandAuthor,
  /// \brief `#+creator:` Document creator
  CommandCreator,
  /// \brief `#+include:` - include other org-mode document (or subsection of it), source code or backend-specific chunk.
  CommandInclude,
  /// \brief `#+language:`
  CommandLanguage,
  /// \brief `#+attr_html:`
  CommandAttrHtml,
  /// \brief `#+name:` - name of the associated entry
  CommandName,
  /// \brief `#+header:` - extended list of parameters passed to associated block
  CommandHeader,
  /// \brief `#+options:` - document-wide formatting options
  CommandOptions,
  CommandTblfm,
  /// \brief Backend-specific configuration options like `#+latex_header` `#+latex_class` etc.
  CommandBackendOptions,
  AttrImg,
  /// \brief `#+caption:` command
  CommandCaption,
  File,
  BlockExport,
  InlineExport,
  /// \brief Multiline command such as code block, latex equation, large block of passthrough code. Some built-in org-mode commands do not requires `#+begin` prefix, (such as `#+quote` or `#+example`) are represented by this type of block as well.
  MultilineCommand,
  /// \brief Command evaluation result
  Result,
  /// \brief regular identifier - `alnum + [-_]` characters for punctuation. Identifiers are compared and parsed in style-insensetive manner, meaning `CODE_BLOCK`, `code-block` and `codeblock` are identical.
  Ident,
  /// \brief Bare identifier - any characters are allowed
  BareIdent,
  /// \brief Big ident used in conjunction with colon at the start of paragraph is considered an admonition tag: `NOTE: Text`, `WARNING: text` etc.
  AdmonitionTag,
  /// \brief full-uppsercase identifier such as `MUST` or `TODO`
  BigIdent,
  /// \brief Verbatim mulitiline block that *might* be a part of `orgMultilineCommand` (in case of `#+begin-src`), but not necessarily. Can also be a part of =quote= and =example= multiline blocks.
  VerbatimMultilineBlock,
  /// \brief Single line of source code
  CodeLine,
  /// \brief Block of source code text
  CodeText,
  /// \brief Single tangle target in the code block
  CodeTangle,
  /// \brief `(refs:` callout in the source code
  CodeCallout,
  /// \brief `#+quote:` block in code
  QuoteBlock,
  AdmonitionBlock,
  /// \brief '
  CenterBlock,
  /// \brief Verbatim example text block
  Example,
  /// \brief Block of source code - can be multiline, single-line and
  SrcCode,
  /// \brief inline piece of code (such as `src_nim`),. Latter is different from regular monospaced text inside of `~~` pair as it contains additional internal structure, optional parameter for code evaluation etc.
  SrcInlineCode,
  /// \brief Call to named source code block. Inline, multiline, or single-line.
  CallCode,
  /// \brief Passthrough block. Inline, multiline, or single-line. Syntax is `@@<backend-name>:<any-body>@@`. Has line and block syntax respectively
  PassCode,
  /// \brief Command arguments
  CmdArguments,
  /// \brief Flag for source code block. For example `-n`, which is used to to make source code block export with lines
  CmdFlag,
  CmdKey,
  CmdValue,
  /// \brief Key-value pair for source code block call.
  CmdNamedValue,
  /// \brief Subtree importance level, such as `[#A]` or `[#B]`. Default org-mode only allows single character for contents inside of `[]`, but this parser makes it possible to use any regular identifier, such as `[#urgent]`.
  UrgencyStatus,
  /// \brief Long horizontal line `----`
  TextSeparator,
  /// \brief Single 'paragraph' of text. Used as generic container for any place in AST where unordered sentence might be encountered (e.g. caption, link description) - not limited to actual paragraph
  Paragraph,
  /// \brief Annotated paragraph -- a wrapper around a regular paragraph kind with added admonition, footnote, list tag prefix and similar types. `[fn:ID] Some Text` is an annotated paragraph, just like `NOTE: Text` or `- Prefix :: Body` (in this case list header is an annotated paragraph)
  AnnotatedParagraph,
  /// \brief Region of text with formatting, which contains standalone words -
  ///      can itself contain subnodes, which allows to represent nested
  ///      formatting regions, such as `*bold /italic/*` text. Particular type
  ///      of identifier is stored in string form in `str` field for `OrgNode`
  ///      -- bold is represented as `"*"`, italic as `/` and so on. In case
  ///      of explicit open/close pairs only opening one is stored.
  ///      NOTE: when structured sentences are enabled, regular punctuation
  ///      elements like `some text (notes)` are also represented as `Word,
  ///      Word, Markup(str: "(", [Word])` - e.g. structure is not fully flat.
  Bold,
  Italic,
  Verbatim,
  Backtick,
  Underline,
  Strike,
  Quote,
  Angle,
  Monospace,
  Par,
  /// \brief Inline latex math. Contains latex math body - either from `$dollar-wrapped$` or `\(paren-wrapped\)` inline text.
  InlineMath,
  /// \brief Inline display latex math from `$$double-dollar$$` or `\[bracket-wrapped\]` code.
  DisplayMath,
  /// \brief Space or tab character in regular text
  Space,
  Punctuation,
  Colon,
  /// \brief Regular word - technically not different from `orgIdent`, but defined separately to disiguish between places where special syntax is required and free-form text.
  Word,
  /// \brief Escaped formatting character in the text
  Escaped,
  Newline,
  /// \brief Raw unwrapped link that was pasted in text
  RawLink,
  /// \brief External or internal link. Consists of one or two elements - target
  ///      (url, file location etc.) and description (`orgParagraph` of text).
  ///      Description might be empty, and represented as empty node in this
  ///      case. For external links particular formatting of the address is
  ///      not handled by parser and instead contains raw string from input
  ///      text.
  Link,
  /// \brief Org-mode macro replacement - during export each macro is expanded
  ///      and evaluated according to it's environment. Body of the macro is
  ///      not parsed fully during org-mode evaluation, but is checked for
  ///      correct parenthesis balance (as macro might contain elisp code)
  Macro,
  /// \brief Raw content to be passed to a particular backend. This is the most
  ///      compact way of quoting export strings, after `#+<backend>:
  ///      <single-backend-line>` and `#+begin-export <backend>`
  ///      `<multiple-lines>`.
  BackendRaw,
  /// \brief Special symbol that should be exported differently to various backends - greek letters (`lpha`), mathematical notations and so on.
  Symbol,
  /// \brief Time association pair for the subtree deadlines.
  TimeAssoc,
  StaticActiveTime,
  StaticInactiveTime,
  DynamicActiveTime,
  /// \brief Single date and time entry (active or inactive),, possibly with repeater interval. Is not parsed directly, and instead contains `orgRawText` that can be parsed later
  DynamicInactiveTime,
  /// \brief Date and time range format - two `orgDateTime` entries
  TimeRange,
  /// \brief Result of the time range evaluation or trailing annotation a subtree
  SimpleTime,
  /// \brief `#+begin_details`  section
  Details,
  /// \brief `#+begin_summary` section
  Summary,
  /// \brief Org-mode table. Tables can be writtein in different formats, but in
  ///    the end they are all represented using single ast type. NOTE: it is
  ///    not guaranteed that all subnodes for table are exactly
  ///    `orgTableRow` - sometimes additional property metadata might be
  ///    used, making AST like `Table[AssocStmtList[Command[_],
  ///    TableRow[_]]]` possible
  Table,
  /// \brief Horizontal table row
  TableRow,
  /// \brief Single cell in row. Might contain anyting, including other tables, simple text paragraph etc.
  TableCell,
  /// \brief Inline footnote with text placed directly in the node body.
  InlineFootnote,
  /// \brief Footnote entry. Just as regular links - internal content is not parsed, and instead just cut out verbatim into target AST node.
  Footnote,
  /// \brief Horizotal rule. Rule body might contain other subnodes, to represnt `---- some text ----` kind of formatting.
  Horizontal,
  /// \brief `#+filetags:` line command
  Filetags,
  /// \brief Original format of org-mode tags in form of `:tagname:`. Might
  ///    contain one or mode identifgiers, but does not provide support for
  ///    nesting - `:tag1:tag2:`. Can only be placed within restricted set
  ///    of places such as subtree headings and has separate place in AST
  ///    when allowed (`orgSubtree` always has subnode `№4` with either
  ///    `orgEmpty` or `orgOrgTag`)
  OrgTag,
  /// \brief More commonly used `#hashtag` format, with some additional
  ///    extension. Can be placed anywere in the document (including section
  ///    headers), but does not have separate place in AST (e.g. considered
  ///    regular part of the text)
  HashTag,
  /// \brief `\sym{}` with explicit arguments
  MetaSymbol,
  /// \brief `@user`
  AtMention,
  /// \brief Custom extension to org-mode. Similarly to `BigIdent` used to have something like informal keywords `MUST`, `OPTIONAL`, but instead aimed /specifically/ at commit message headers - `[FEATURE]`, `[FIX]` and so on.
  BracTag,
  /// \brief Single enclosed drawer like `:properties: ... :end:` or `:logbook: ... :end:`
  Drawer,
  LatexClass,
  LatexHeader,
  LatexCompiler,
  LatexClassOptions,
  HtmlHead,
  /// \brief `#+columns:` line command for specifying formatting of the org-mode clock table visualization on per-file basis.
  Columns,
  /// \brief `#+property:` command
  CmdPropertyArgs,
  /// \brief `#+property:` command
  CmdPropertyText,
  /// \brief `#+property:` command
  CmdPropertyRaw,
  PropertyList,
  /// \brief `:property:` drawer
  Property,
  /// \brief Placeholder entry in text, usually writte like `<text to replace>`
  Placeholder,
  /// \brief `:description:` entry
  SubtreeDescription,
  SubtreeUrgency,
  /// \brief `:logbook:` entry storing note information
  Logbook,
  LogbookEntry,
  /// \brief Annotation about change in the subtree todo state
  LogbookStateChange,
  /// \brief Timestamped log note on the subtree
  LogbookNote,
  /// \brief `CLOCK` entry in the subtree
  LogbookClock,
  /// \brief `Refile` entry in the subtree logbook drawer
  LogbookRefile,
  /// \brief Change in the subtree priority
  LogbookPriority,
  /// \brief Action to change subtree
  LogbookPriorityChangeAction,
  LogbookReschedule,
  LogbookTagChange,
  LogbookTagChangeAction,
  /// \brief `<<<RADIO>>>`
  RadioTarget,
  /// \brief `<<TARGET>>`
  Target,
};
template <>
struct enum_serde<OrgNodeKind> {
  static Opt<OrgNodeKind> from_string(std::string value);
  static std::string to_string(OrgNodeKind value);
};

template <>
struct value_domain<OrgNodeKind> : public value_domain_ungapped<OrgNodeKind,
                                                                OrgNodeKind::None,
                                                                OrgNodeKind::Target> {};

enum class OrgBigIdentKind : short int {
  None,
  /// \brief MUST This word, or the terms "REQUIRED" or "SHALL", mean that the definition is an absolute requirement of the specification.
  Must,
  /// \brief MUST NOT This phrase, or the phrase "SHALL NOT", mean that the definition is an absolute prohibition of the specification.
  MustNot,
  /// \brief SHOULD This word, or the adjective "RECOMMENDED", mean that there
  ///    may exist valid reasons in particular circumstances to ignore a
  ///    particular item, but the full implications must be understood and
  ///    carefully weighed before choosing a different course.
  Should,
  /// \brief SHOULD NOT This phrase, or the phrase "NOT RECOMMENDED" mean that
  ///    there may exist valid reasons in particular circumstances when the
  ///    particular behavior is acceptable or even useful, but the full
  ///    implications should be understood and the case carefully weighed
  ///    before implementing any behavior described with this label.
  ShouldNot,
  Required,
  /// \brief MAY This word, or the adjective "OPTIONAL", mean that an item is
  ///    truly optional. One vendor may choose to include the item because a
  ///    particular marketplace requires it or because the vendor feels that
  ///    it enhances the product while another vendor may omit the same
  ///    item. An implementation which does not include a particular option
  ///    MUST be prepared to interoperate with another implementation which
  ///    does include the option, though perhaps with reduced functionality.
  ///    In the same vein an implementation which does include a particular
  ///    option MUST be prepared to interoperate with another implementation
  ///    which does not include the option (except, of course, for the
  ///    feature the option provides.)
  Optional,
  ReallyShouldNot,
  OughtTo,
  WouldProbably,
  MayWishTo,
  Could,
  Might,
  Possible,
  Todo,
  Idea,
  Error,
  Fixme,
  Doc,
  Refactor,
  Review,
  Hack,
  Implement,
  Example,
  Question,
  Assume,
  Internal,
  Design,
  Why,
  Wip,
  Fix,
  Clean,
  Feature,
  Style,
  Repo,
  Skip,
  Break,
  Poc,
  Next,
  Later,
  Postponed,
  Stalled,
  Done,
  Partially,
  Cancelled,
  Failed,
  Note,
  Tip,
  Important,
  Caution,
  Warning,
  /// \brief User-defined comment message
  UserCodeComment,
  /// \brief User-defined commit message ident
  UserCommitMsg,
  /// \brief User-defined task state
  UserTaskState,
  /// \brief User-defined admonition label
  UserAdmonition,
  /// \brief User-defined big-idents, not included in default set.
  Other,
  StructIf,
  StructAnd,
  StructOr,
  StructNot,
  StructGet,
  StructSet,
  StructThen,
  StructElse,
  StructWhile,
};
template <>
struct enum_serde<OrgBigIdentKind> {
  static Opt<OrgBigIdentKind> from_string(std::string value);
  static std::string to_string(OrgBigIdentKind value);
};

template <>
struct value_domain<OrgBigIdentKind> : public value_domain_ungapped<OrgBigIdentKind,
                                                                    OrgBigIdentKind::None,
                                                                    OrgBigIdentKind::StructWhile> {};

enum class OrgTokenKind : short int {
  None,
  Eof,
  /// \brief `#+` prefix token for the command
  CmdPrefix,
  /// \brief Generic line command
  CmdLine,
  /// \brief #+title: line command token
  CmdTitle,
  /// \brief #+caption
  CmdCaption,
  /// \brief #+filetags
  CmdFiletags,
  /// \brief #+columns
  CmdColumns,
  /// \brief #+property
  CmdPropertyArgs,
  /// \brief #+property
  CmdPropertyText,
  /// \brief #+property
  CmdPropertyRaw,
  /// \brief #+options
  CmdOptions,
  CmdSetupfile,
  CmdInclude,
  /// \brief `#+attr_latex:`
  CmdAttrLatex,
  /// \brief `#+attr_img:`
  CmdAttrImg,
  /// \brief `#+attr_html:`
  CmdAttrHtml,
  /// \brief `#+html_head:`
  CmdHtmlHead,
  /// \brief `#+language:`
  CmdLanguage,
  /// \brief `#+latex_class_options`
  CmdLatexClassOptions,
  CmdLatexClass,
  CmdLatexCompiler,
  /// \brief `#+author:`
  CmdAuthor,
  /// \brief `#+bind:`
  CmdBind,
  /// \brief `#+creator:`
  CmdCreator,
  /// \brief `#+latex_header`
  CmdLatexHeader,
  /// \brief `#+results:`
  CmdResults,
  /// \brief `#+call:`
  CmdCall,
  /// \brief `#+name:`
  CmdName,
  /// \brief `#+header:`
  CmdHeader,
  /// \brief List of command arguments
  CmdArgumentsBegin,
  /// \brief End of the command arguments list
  CmdArgumentsEnd,
  CmdKey,
  CmdValue,
  CmdFlag,
  /// \brief `#+results[HASH...]`
  CmdBracket,
  /// \brief `#+begin` part of generic multiline command.
  CmdBegin,
  CmdEnd,
  CmdSrcBegin,
  CmdSrcEnd,
  CmdQuoteBegin,
  CmdQuoteEnd,
  CmdCenterBegin,
  CmdCenterEnd,
  CmdTableBegin,
  CmdTableEnd,
  CmdAdmonitionBegin,
  CmdAdmonitionEnd,
  CmdDynamicBegin,
  /// \brief `#+begin:`
  CmdDynamicEnd,
  CmdExampleBegin,
  /// \brief `#+begin:`
  CmdExampleEnd,
  CmdExportBegin,
  /// \brief `#+begin:`
  CmdExportEnd,
  CmdDetailsBegin,
  /// \brief `#+begin:`
  CmdDetailsEnd,
  CmdSummaryBegin,
  /// \brief `#+begin:`
  CmdSummaryEnd,
  /// \brief #+tblfm:
  CmdTblfm,
  /// \brief `#+quote` content
  QuoteContent,
  /// \brief Backend-specific passthrough
  CmdBackendPass,
  /// \brief Content wrapper for the block commands
  CmdContentBegin,
  /// \brief End of content wrapper
  CmdContentEnd,
  /// \brief Block of code inside `#+begin_src`
  CmdSrcCodeContent,
  /// \brief Code before noweb placeholder. Requires separate token to handle `##<<commented>>` - prefix comment should be duplicated for each line of the placeholder expansion.
  CmdSrcTextBlock,
  /// \brief Block of text inside `#+table`
  TblContent,
  TblBegin,
  TblEnd,
  /// \brief Unformatted table cell body
  TblCellBody,
  /// \brief `#+row` command together with parameters
  TblRowSpec,
  /// \brief `#+cell` command with parameters
  TblCellSpec,
  TblPipeBegin,
  /// \brief Vertical pipe (`|`) cell separator
  TblPipeSeparator,
  TblPipeEnd,
  TblPipeCellBegin,
  /// \brief Horizontal dash (`---`, `:---`, `---:` or `:---:`) row separator
  TblDashSeparator,
  /// \brief Corner plus (`+`)
  TblCornerPlus,
  /// \brief Start of the table cell content section
  TblCellContentBegin,
  /// \brief End of the table cell content section
  TblCellContentEnd,
  /// \brief Uninterrupted text span without newlines - either a whole line or sub subsection of it if callout or tangle elements were detected
  CodeText,
  Text,
  /// \brief Unlexed group of statements - used in the list content to enable secondary parsing.
  StmtList,
  /// \brief Start of the expanded statement list content
  StmtListBegin,
  /// \brief End of the expanded statement list content
  StmtListEnd,
  /// \brief Increase in indentation
  Indent,
  /// \brief Decrease in indentation
  Dedent,
  SameIndent,
  NoIndent,
  /// \brief Start of the list token group
  ListBegin,
  /// \brief Start of the list item element
  ListItemBegin,
  /// \brief `CLOCK:` entry at the start of the logbook entry list
  ListClock,
  /// \brief Start of the description list key,
  ListDescBegin,
  /// \brief End of the description list key `::`
  ListDescEnd,
  /// \brief End of the list item
  ListItemEnd,
  /// \brief Complete end of the list token group
  ListEnd,
  /// \brief List or subtree checkbox
  Checkbox,
  SubtreeTodoState,
  /// \brief Subtree importance marker
  SubtreeUrgency,
  /// \brief Subtree completion marker
  SubtreeCompletion,
  /// \brief Subtree prefix
  SubtreeStars,
  SubtreeTagSeparator,
  SubtreeTime,
  SubtreeEnd,
  /// \brief Logbook including content
  LogBook,
  /// \brief Drawer including content
  Drawer,
  /// \brief Literal block with `:`
  ColonLiteral,
  /// \brief Drawer or source code block wrappers with colon-wrapped identifiers. `:results:`, `:end:` etc.
  ColonIdent,
  /// \brief Start of the `:PROPERTIES:` block drawer block
  ColonProperties,
  /// \brief Start of the `:description:` drawer block
  ColonDescription,
  ColonEnd,
  ColonLogbook,
  RawLogbook,
  LogbookBegin,
  LogbookEnd,
  RawProperty,
  /// \brief Properties with raw string literal values
  PropRawKey,
  /// \brief Properties with text (paragraph) values
  PropTextKey,
  /// \brief You can write time ranges without any additional formatting for
  ///    subtrees that have a diary timestamps. For example, you have a
  ///    complex date predicate, but event occurs for `18:00-21:00`, so you
  ///    write it in the random place in the subtree.
  ImplicitTime,
  /// \brief Time duration for the `effort` property or time range length evaluation
  TimeDuration,
  /// \brief Dynamic time content
  DynamicTimeContent,
  /// \brief year-month-day part of the timestamp
  StaticTimeDatePart,
  /// \brief weekday part of the timestamp
  StaticTimeDayPart,
  /// \brief Clock part of the timestamp
  StaticTimeClockPart,
  /// \brief Type of the time repeater: `+`, `++`, `.+`
  StaticTimeRepeater,
  /// \brief Separator dash between two periods in the time range (`<start>--<finish.`)
  TimeDash,
  /// \brief Time range evaluation arrow `[from]--[to] =>`
  TimeArrow,
  /// \brief line or inline comment
  Comment,
  /// \brief Any kind of link
  Link,
  BoldBegin,
  BoldEnd,
  ItalicBegin,
  ItalicEnd,
  VerbatimBegin,
  VerbatimEnd,
  MonospaceBegin,
  MonospaceEnd,
  BacktickBegin,
  BacktickEnd,
  UnderlineBegin,
  UnderlineEnd,
  StrikeBegin,
  StrikeEnd,
  QuoteBegin,
  QuoteEnd,
  Punctuation,
  /// \brief Placeholder Begin
  AngleBegin,
  /// \brief Placeholder End
  AngleEnd,
  /// \brief `<<` - open for noweb or anchor placeholder
  DoubleAngleBegin,
  /// \brief `>>` - close for noweb or anchor placeholder
  DoubleAngleEnd,
  /// \brief `<<<` - radio target Begin
  TripleAngleBegin,
  /// \brief `>>>` - radio target End
  TripleAngleEnd,
  LinkBegin,
  LinkEnd,
  RawUrl,
  LinkTargetBegin,
  LinkTargetEnd,
  /// \brief No protocol is used in the link, it is targeting some internal named entry.
  LinkInternal,
  /// \brief Protocol used by the link - `file:`, `https:` etc.
  LinkProtocol,
  /// \brief Full token for the link, used in cases where it does not make sense to fracture the token - regular https URLs etc.
  LinkFull,
  /// \brief Target of the link protocol that does not follow regular URI encoding scheme - for example `id:`, `elisp`, or `shell` links.
  LinkTarget,
  LinkDescriptionBegin,
  LinkDescriptionEnd,
  TextSeparator,
  /// \brief Fake token inserted by the lexer to delimit start of the paragraph
  ParagraphBegin,
  ParagraphEnd,
  FootnoteBegin,
  /// \brief Regular word in the paragraph
  Word,
  DoubleColon,
  Number,
  /// \brief Escaped character in plain text - `\*`, `\/` etc. Escaped characters and sequences thereof are treated like a regular plain text.
  Escaped,
  /// \brief Put at the end of the lexer first logbook line to separate the  note, otherwise is treated as standalone escaped slash.
  DoubleSlash,
  /// \brief Explicit newline a paragraph
  Newline,
  MaybeWord,
  /// \brief Space in the paragraph
  Space,
  /// \brief `TODO`, `NOTE` and similar capitalized words
  BigIdent,
  /// \brief Unparsed raw text, either as a part of paragraph or some embedded construction such as link address.
  RawText,
  /// \brief Unquoted `\symbol` directly in the text
  SymbolBegin,
  /// \brief Opening dollar inline latex math
  DollarBegin,
  /// \brief Closing dollar for inline latex math
  DollarEnd,
  /// \brief Opening `$` for inline latex
  DoubleDollarBegin,
  /// \brief Closing `$` for inline latex
  DoubleDollarEnd,
  /// \brief Opening `\(` for inline latex math
  LatexParBegin,
  /// \brief Closing `\)` for inline latex math
  LatexParEnd,
  /// \brief Opening `\[` for inline display latex equation
  LatexBraceBegin,
  /// \brief Closing `\]` for inline display latex equation
  LatexBraceEnd,
  /// \brief Content of the brace/par-enclosed math
  LatexInlineRaw,
  /// \brief `@user` mention in the text
  AtMention,
  /// \brief Start of the inline hashtag `#tag`
  HashTag,
  /// \brief Nested hashtag separator
  HashTagSub,
  /// \brief Start of the nested hashtag grop bracket
  HashTagBegin,
  /// \brief End of the nested hashtag group separator
  HashTagEnd,
  /// \brief Comma - punctuation or a syntax element (e.g. for macro arguments)
  Comma,
  /// \brief Paren open - punctuation or a syntax element
  ParBegin,
  /// \brief Paren close - punctuation or a syntax element
  ParEnd,
  /// \brief `[`
  BraceBegin,
  /// \brief `]`
  BraceEnd,
  Colon,
  /// \brief `^` possible superscript in the text
  Circumflex,
  /// \brief Start of the macro call `{{{`
  MacroBegin,
  /// \brief Close of the macro call `}}}`
  MacroEnd,
  /// \brief Start of an inline source code block: `src_nim[]{}`
  InlineSrc,
  /// \brief Start of an inline call block: `call_name[]{}`
  InlineCall,
  /// \brief Start of the curly section of an inline source/call
  CurlyStart,
  /// \brief End of the curly section of an inline source/call
  CurlyEnd,
  /// \brief Inline backend passthrough `@@`
  DoubleAt,
  SrcBegin,
  SrcName,
  SrcArgs,
  SrcBody,
  SrcEnd,
  CallBegin,
  CallName,
  CallInsideHeader,
  CallArgs,
  EndHeader,
  CallEnd,
  CmdArguments,
};
template <>
struct enum_serde<OrgTokenKind> {
  static Opt<OrgTokenKind> from_string(std::string value);
  static std::string to_string(OrgTokenKind value);
};

template <>
struct value_domain<OrgTokenKind> : public value_domain_ungapped<OrgTokenKind,
                                                                 OrgTokenKind::None,
                                                                 OrgTokenKind::CmdArguments> {};

enum class OrgSemKind : short int { StmtList, Empty, Row, Table, HashTag, Footnote, Completion, Paragraph, Center, Caption, CommandGroup, Quote, Example, CmdArguments, CmdArgument, Export, AdmonitionBlock, Code, Time, TimeRange, Macro, Symbol, SubtreeLog, Subtree, InlineMath, Escaped, Newline, Space, Word, AtMention, RawText, Punctuation, Placeholder, BigIdent, Bold, Underline, Monospace, MarkQuote, Verbatim, Italic, Strike, Par, List, ListItem, Link, Document, ParseError, FileTarget, TextSeparator, Include, DocumentOptions, DocumentGroup, };
template <>
struct enum_serde<OrgSemKind> {
  static Opt<OrgSemKind> from_string(std::string value);
  static std::string to_string(OrgSemKind value);
};

template <>
struct value_domain<OrgSemKind> : public value_domain_ungapped<OrgSemKind,
                                                               OrgSemKind::StmtList,
                                                               OrgSemKind::DocumentGroup> {};


template <>
struct std::formatter<OrgSemKind> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(OrgSemKind const& p, FormatContext& ctx)
        const {
        std::formatter<std::string> fmt;
        return fmt.format(enum_serde<OrgSemKind>::to_string(p), ctx);
    }
};

/* clang-format on */