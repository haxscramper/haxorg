/* clang-format off */
#pragma once
#include <hstd/system/basic_templates.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/Opt.hpp>
#define EACH_SEM_ORG_KIND(__IMPL) \
    __IMPL(CmdArgument) \
    __IMPL(CmdArgumentList) \
    __IMPL(CmdArguments) \
    __IMPL(ErrorItem) \
    __IMPL(ErrorGroup) \
    __IMPL(StmtList) \
    __IMPL(Empty) \
    __IMPL(CmdCaption) \
    __IMPL(CmdName) \
    __IMPL(CmdCustomArgs) \
    __IMPL(CmdCustomRaw) \
    __IMPL(CmdCustomText) \
    __IMPL(CmdResults) \
    __IMPL(CmdTblfm) \
    __IMPL(HashTag) \
    __IMPL(Footnote) \
    __IMPL(Time) \
    __IMPL(TimeRange) \
    __IMPL(Macro) \
    __IMPL(Symbol) \
    __IMPL(Escaped) \
    __IMPL(Newline) \
    __IMPL(Space) \
    __IMPL(Word) \
    __IMPL(AtMention) \
    __IMPL(RawText) \
    __IMPL(Punctuation) \
    __IMPL(Placeholder) \
    __IMPL(BigIdent) \
    __IMPL(RadioTarget) \
    __IMPL(TextTarget) \
    __IMPL(Bold) \
    __IMPL(Underline) \
    __IMPL(Monospace) \
    __IMPL(MarkQuote) \
    __IMPL(Verbatim) \
    __IMPL(Italic) \
    __IMPL(Strike) \
    __IMPL(Par) \
    __IMPL(Latex) \
    __IMPL(Link) \
    __IMPL(BlockCenter) \
    __IMPL(BlockQuote) \
    __IMPL(BlockComment) \
    __IMPL(BlockVerse) \
    __IMPL(BlockExample) \
    __IMPL(BlockExport) \
    __IMPL(BlockAdmonition) \
    __IMPL(BlockCode) \
    __IMPL(SubtreeLog) \
    __IMPL(Subtree) \
    __IMPL(SubtreeCompletion) \
    __IMPL(Cell) \
    __IMPL(Row) \
    __IMPL(Table) \
    __IMPL(Paragraph) \
    __IMPL(AnnotatedParagraph) \
    __IMPL(ColonExample) \
    __IMPL(CmdAttr) \
    __IMPL(Call) \
    __IMPL(List) \
    __IMPL(ListItem) \
    __IMPL(DocumentOptions) \
    __IMPL(Document) \
    __IMPL(FileTarget) \
    __IMPL(TextSeparator) \
    __IMPL(Include) \
    __IMPL(DocumentGroup)
#define EACH_SEM_ORG_RECORD_NESTED(__IMPL) \
    __IMPL(Time, Repeat, (Repeat)) \
    __IMPL(Time, Static, (Static)) \
    __IMPL(Time, Dynamic, (Dynamic)) \
    __IMPL(Symbol, Param, (Param)) \
    __IMPL(Link, Raw, (Raw)) \
    __IMPL(Link, Id, (Id)) \
    __IMPL(Link, Person, (Person)) \
    __IMPL(Link, UserProtocol, (UserProtocol)) \
    __IMPL(Link, Internal, (Internal)) \
    __IMPL(Link, Footnote, (Footnote)) \
    __IMPL(Link, File, (File)) \
    __IMPL(Link, Attachment, (Attachment)) \
    __IMPL(BlockCode, Line, (Line)) \
    __IMPL(BlockCode, Line::Part, (Line, Part)) \
    __IMPL(BlockCode, Line::Part::Raw, (Line, Part, Raw)) \
    __IMPL(BlockCode, Line::Part::Callout, (Line, Part, Callout)) \
    __IMPL(BlockCode, Line::Part::Tangle, (Line, Part, Tangle)) \
    __IMPL(BlockCode, Switch, (Switch)) \
    __IMPL(BlockCode, Switch::LineStart, (Switch, LineStart)) \
    __IMPL(BlockCode, Switch::CalloutFormat, (Switch, CalloutFormat)) \
    __IMPL(BlockCode, Switch::RemoveCallout, (Switch, RemoveCallout)) \
    __IMPL(BlockCode, Switch::EmphasizeLine, (Switch, EmphasizeLine)) \
    __IMPL(BlockCode, Switch::Dedent, (Switch, Dedent)) \
    __IMPL(BlockCode, EvalResult, (EvalResult)) \
    __IMPL(BlockCode, EvalResult::None, (EvalResult, None)) \
    __IMPL(BlockCode, EvalResult::OrgValue, (EvalResult, OrgValue)) \
    __IMPL(BlockCode, EvalResult::File, (EvalResult, File)) \
    __IMPL(BlockCode, EvalResult::Raw, (EvalResult, Raw)) \
    __IMPL(SubtreeLog, DescribedLog, (DescribedLog)) \
    __IMPL(SubtreeLog, Priority, (Priority)) \
    __IMPL(SubtreeLog, Note, (Note)) \
    __IMPL(SubtreeLog, Refile, (Refile)) \
    __IMPL(SubtreeLog, Clock, (Clock)) \
    __IMPL(SubtreeLog, State, (State)) \
    __IMPL(SubtreeLog, Tag, (Tag)) \
    __IMPL(SubtreeLog, Unknown, (Unknown)) \
    __IMPL(Subtree, Period, (Period)) \
    __IMPL(Subtree, Property, (Property)) \
    __IMPL(Subtree, Property::Nonblocking, (Property, Nonblocking)) \
    __IMPL(Subtree, Property::Trigger, (Property, Trigger)) \
    __IMPL(Subtree, Property::Origin, (Property, Origin)) \
    __IMPL(Subtree, Property::ExportLatexClass, (Property, ExportLatexClass)) \
    __IMPL(Subtree, Property::ExportLatexClassOptions, (Property, ExportLatexClassOptions)) \
    __IMPL(Subtree, Property::ExportLatexHeader, (Property, ExportLatexHeader)) \
    __IMPL(Subtree, Property::ExportLatexCompiler, (Property, ExportLatexCompiler)) \
    __IMPL(Subtree, Property::Ordered, (Property, Ordered)) \
    __IMPL(Subtree, Property::Effort, (Property, Effort)) \
    __IMPL(Subtree, Property::Visibility, (Property, Visibility)) \
    __IMPL(Subtree, Property::ExportOptions, (Property, ExportOptions)) \
    __IMPL(Subtree, Property::Blocker, (Property, Blocker)) \
    __IMPL(Subtree, Property::Unnumbered, (Property, Unnumbered)) \
    __IMPL(Subtree, Property::Created, (Property, Created)) \
    __IMPL(Subtree, Property::CustomArgs, (Property, CustomArgs)) \
    __IMPL(Subtree, Property::CustomRaw, (Property, CustomRaw)) \
    __IMPL(AnnotatedParagraph, None, (None)) \
    __IMPL(AnnotatedParagraph, Footnote, (Footnote)) \
    __IMPL(AnnotatedParagraph, Admonition, (Admonition)) \
    __IMPL(AnnotatedParagraph, Timestamp, (Timestamp)) \
    __IMPL(DocumentOptions, ExportConfig, (ExportConfig)) \
    __IMPL(DocumentOptions, ExportConfig::TaskExport, (ExportConfig, TaskExport)) \
    __IMPL(DocumentOptions, ExportConfig::DoExport, (ExportConfig, DoExport)) \
    __IMPL(DocumentOptions, ExportConfig::ExportFixed, (ExportConfig, ExportFixed)) \
    __IMPL(Include, Example, (Example)) \
    __IMPL(Include, Export, (Export)) \
    __IMPL(Include, Src, (Src)) \
    __IMPL(Include, OrgDocument, (OrgDocument))
#define EACH_SEM_ORG_ENUM_NESTED(__IMPL) \
    __IMPL(Time, Repeat::Mode, (Repeat, Mode)) \
    __IMPL(Time, Repeat::Period, (Repeat, Period)) \
    __IMPL(Time, TimeKind, (TimeKind)) \
    __IMPL(Link, Kind, (Kind)) \
    __IMPL(BlockExport, Format, (Format)) \
    __IMPL(BlockCode, Line::Part::Kind, (Line, Part, Kind)) \
    __IMPL(BlockCode, Switch::Kind, (Switch, Kind)) \
    __IMPL(BlockCode, Results, (Results)) \
    __IMPL(BlockCode, Exports, (Exports)) \
    __IMPL(BlockCode, EvalResult::Kind, (EvalResult, Kind)) \
    __IMPL(SubtreeLog, Priority::Action, (Priority, Action)) \
    __IMPL(SubtreeLog, Kind, (Kind)) \
    __IMPL(Subtree, Period::Kind, (Period, Kind)) \
    __IMPL(Subtree, Property::SetMode, (Property, SetMode)) \
    __IMPL(Subtree, Property::InheritanceMode, (Property, InheritanceMode)) \
    __IMPL(Subtree, Property::Visibility::Level, (Property, Visibility, Level)) \
    __IMPL(Subtree, Property::Kind, (Property, Kind)) \
    __IMPL(AnnotatedParagraph, AnnotationKind, (AnnotationKind)) \
    __IMPL(ListItem, Checkbox, (Checkbox)) \
    __IMPL(DocumentOptions, ExportConfig::TagExport, (ExportConfig, TagExport)) \
    __IMPL(DocumentOptions, ExportConfig::TaskFiltering, (ExportConfig, TaskFiltering)) \
    __IMPL(DocumentOptions, ExportConfig::BrokenLinks, (ExportConfig, BrokenLinks)) \
    __IMPL(DocumentOptions, ExportConfig::TocExportKind, (ExportConfig, TocExportKind)) \
    __IMPL(DocumentOptions, Visibility, (Visibility)) \
    __IMPL(Include, Kind, (Kind))
enum class OrgSpecName : short int { Unnamed, Result, Year, Day, Clock, Repeater, Zone, Link, Tags, Tag, State, Protocol, Desc, Times, Drawer, Args, Name, Definition, Body, HeaderArgs, File, Kind, Lang, Prefix, Text, Todo, Importance, Title, Completion, Head, Subnodes, Properties, Logbook, Description, Logs, Newstate, Oldstate, Time, From, EndArgs, Flags, Value, Assoc, Main, Hash, Bullet, Counter, Checkbox, Header, To, Diff, Property, Subname, Values, Cells, Rows, Lines, Chunks, InheritanceMode, MainSetRule, SubSetRule, };
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
  /// \brief Empty node - valid state that does not contain any value
  Empty,
  InlineStmtList,
  /// \brief List of statements, possibly recursive. Used as toplevel part of the document, in recursive parsing of subtrees, or as regular list, in cases where multiple subnodes have to be grouped together.
  StmtList,
  /// \brief Single checkbox item like `[X]` or `[-]`
  Checkbox,
  List,
  /// \brief List item prefix
  Bullet,
  ListItem,
  /// \brief Auxilliary wrapper for the paragraph placed at the start of the description list.
  ListTag,
  Counter,
  File,
  /// \brief Colon example block
  ColonExample,
  /// \brief Long horizontal line `----`
  TextSeparator,
  /// \brief Single 'paragraph' of text. Used as generic container for any place in AST where unordered sentence might be encountered (e.g. caption, link description) - not limited to actual paragraph
  Paragraph,
  /// \brief Annotated paragraph -- a wrapper around a regular paragraph kind with added admonition, footnote, list tag prefix and similar types. `[fn:ID] Some Text` is an annotated paragraph, just like `NOTE: Text` or `- Prefix :: Body` (in this case list header is an annotated paragraph)
  AnnotatedParagraph,
  /// \brief Horizontal table row
  TableRow,
  /// \brief Single cell in row. Might contain anyting, including other tables, simple text paragraph etc.
  TableCell,
  /// \brief Org-mode table
  Table,
  /// \brief Inline footnote with text placed directly in the node body.
  InlineFootnote,
  /// \brief Footnote entry. Just as regular links - internal content is not parsed, and instead just cut out verbatim into target AST node.
  Footnote,
  /// \brief Undefined single-line command -- most likely custom user-provided oe
  Cmd,
  /// \brief Arguments for the command block
  CmdArguments,
  /// \brief `#+title:` - full document title
  CmdTitle,
  /// \brief `#+author:` Document author
  CmdAuthor,
  /// \brief `#+creator:` Document creator
  CmdCreator,
  /// \brief `#+include:` - include other org-mode document (or subsection of it), source code or backend-specific chunk.
  CmdInclude,
  /// \brief `#+language:`
  CmdLanguage,
  /// \brief `#+attr_html:`, `#+attr_image` etc.
  CmdAttr,
  /// \brief `#+startup:`
  CmdStartup,
  /// \brief `#+name:` - name of the associated entry
  CmdName,
  /// \brief Line command with parsed text value
  CmdCustomTextCommand,
  /// \brief Line command with parsed argument list
  CmdCustomArgsCommand,
  /// \brief Line command with raw text argument
  CmdCustomRawCommand,
  /// \brief `#+results:` - source code block evaluation results
  CmdResults,
  /// \brief `#+header:` - extended list of parameters passed to associated block
  CmdHeader,
  /// \brief `#+options:` - document-wide formatting options
  CmdOptions,
  CmdTblfm,
  /// \brief `#+caption:` command
  CmdCaption,
  /// \brief Command evaluation result
  CmdResult,
  /// \brief Call to named source code block.
  CmdCallCode,
  /// \brief Flag for source code block. For example `-n`, which is used to to make source code block export with lines
  CmdFlag,
  CmdKey,
  CmdValue,
  /// \brief Key-value pair for source code block call.
  CmdNamedValue,
  CmdLatexClass,
  CmdLatexHeader,
  CmdLatexCompiler,
  CmdLatexClassOptions,
  CmdHtmlHead,
  /// \brief `#+columns:` line command for specifying formatting of the org-mode clock table visualization on per-file basis.
  CmdColumns,
  /// \brief `#+property:` command
  CmdPropertyArgs,
  /// \brief `#+property:` command
  CmdPropertyText,
  /// \brief `#+property:` command
  CmdPropertyRaw,
  /// \brief `#+filetags:` line command
  CmdFiletags,
  /// \brief Verbatim mulitiline block that *might* be a part of `orgMultilineCommand` (in case of `#+begin-src`), but not necessarily. Can also be a part of =quote= and =example= multiline blocks.
  BlockVerbatimMultiline,
  /// \brief Single line of source code
  CodeLine,
  /// \brief Block of source code text
  CodeText,
  /// \brief Single tangle target in the code block
  CodeTangle,
  /// \brief `(refs:` callout in the source code
  CodeCallout,
  BlockCode,
  /// \brief `#+begin_quote:` block in code
  BlockQuote,
  /// \brief `#+begin_comment:` block in code
  BlockComment,
  BlockCenter,
  BlockVerse,
  /// \brief Verbatim example text block
  BlockExample,
  BlockExport,
  /// \brief `#+begin_details`  section
  BlockDetails,
  /// \brief `#+begin_summary` section
  BlockSummary,
  /// \brief regular identifier - `alnum + [-_]` characters for punctuation. Identifiers are compared and parsed in style-insensetive manner, meaning `CODE_BLOCK`, `code-block` and `codeblock` are identical.
  Ident,
  /// \brief full-uppsercase identifier such as `MUST` or `TODO`
  BigIdent,
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
  /// \brief Special symbol that should be exported differently to various backends - greek letters (`lpha`), mathematical notations and so on.
  Symbol,
  StaticActiveTime,
  StaticInactiveTime,
  DynamicActiveTime,
  /// \brief Single date and time entry (active or inactive),, possibly with repeater interval. Is not parsed directly, and instead contains `orgRawText` that can be parsed later
  DynamicInactiveTime,
  /// \brief Date and time range format - two `orgDateTime` entries
  TimeRange,
  /// \brief Result of the time range evaluation or trailing annotation a subtree
  SimpleTime,
  HashTag,
  /// \brief `\sym{}` with explicit arguments
  MetaSymbol,
  /// \brief `@user`
  AtMention,
  /// \brief Placeholder entry in text, usually writte like `<text to replace>`
  Placeholder,
  /// \brief `<<<RADIO>>>`
  RadioTarget,
  /// \brief `<<TARGET>>`
  Target,
  /// \brief inline piece of code (such as `src_nim`),. Latter is different from regular monospaced text inside of `~~` pair as it contains additional internal structure, optional parameter for code evaluation etc.
  SrcInlineCode,
  /// \brief Call to named source code block.
  InlineCallCode,
  /// \brief Passthrough block. Inline, multiline, or single-line. Syntax is `@@<backend-name>:<any-body>@@`. Has line and block syntax respectively
  InlineExport,
  InlineComment,
  /// \brief Raw string of text from input buffer. Things like particular syntax details of every single command, link formats are not handled in parser, deferring formatting to future processing layers
  RawText,
  /// \brief `:description:` entry
  SubtreeDescription,
  SubtreeUrgency,
  /// \brief `:logbook:` entry storing note information
  DrawerLogbook,
  /// \brief Single enclosed drawer like `:properties: ... :end:` or `:logbook: ... :end:`
  Drawer,
  DrawerPropertyList,
  /// \brief `:property:` drawer
  DrawerProperty,
  /// \brief Section subtree
  Subtree,
  /// \brief Time? associated with subtree entry
  SubtreeTimes,
  SubtreeStars,
  /// \brief Task compleation cookie, indicated either in percents of completion, or as `<done>/<todo>` ratio.
  SubtreeCompletion,
  /// \brief Subtree importance level, such as `[#A]` or `[#B]`. Default org-mode only allows single character for contents inside of `[]`, but this parser makes it possible to use any regular identifier, such as `[#urgent]`.
  SubtreeImportance,
};
template <>
struct enum_serde<OrgNodeKind> {
  static Opt<OrgNodeKind> from_string(std::string value);
  static std::string to_string(OrgNodeKind value);
};

template <>
struct value_domain<OrgNodeKind> : public value_domain_ungapped<OrgNodeKind,
                                                                OrgNodeKind::None,
                                                                OrgNodeKind::SubtreeImportance> {};

enum class OrgSemKind : short int { CmdArgument, CmdArgumentList, CmdArguments, ErrorItem, ErrorGroup, StmtList, Empty, CmdCaption, CmdName, CmdCustomArgs, CmdCustomRaw, CmdCustomText, CmdResults, CmdTblfm, HashTag, Footnote, Time, TimeRange, Macro, Symbol, Escaped, Newline, Space, Word, AtMention, RawText, Punctuation, Placeholder, BigIdent, RadioTarget, TextTarget, Bold, Underline, Monospace, MarkQuote, Verbatim, Italic, Strike, Par, Latex, Link, BlockCenter, BlockQuote, BlockComment, BlockVerse, BlockExample, BlockExport, BlockAdmonition, BlockCode, SubtreeLog, Subtree, SubtreeCompletion, Cell, Row, Table, Paragraph, AnnotatedParagraph, ColonExample, CmdAttr, Call, List, ListItem, DocumentOptions, Document, FileTarget, TextSeparator, Include, DocumentGroup, };
template <>
struct enum_serde<OrgSemKind> {
  static Opt<OrgSemKind> from_string(std::string value);
  static std::string to_string(OrgSemKind value);
};

template <>
struct value_domain<OrgSemKind> : public value_domain_ungapped<OrgSemKind,
                                                               OrgSemKind::CmdArgument,
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