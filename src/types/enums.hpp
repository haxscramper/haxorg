#pragma once

enum class OrgHorizontalDirection : short int
{
    ohdNone,   ///  No specific positioning requirements
    ohdLeft,   ///  Align to the left
    ohdRight,  ///  Align to the right
    ohdCenter, ///  Align to the center
};

enum class OrgVerticalDirection : short int
{
    ovdNone,   ///  No specific positioning
    ovdTop,    ///  Align to the top
    ovdCenter, ///  Center
    ovdBottom, ///  Bottom
};

enum class OrgSpecName
{
    Unnamed,
    Result,
    Year,
    Day,
    Clock,
    Repeater,
    Link,
    Tags,
    Protocol,
    Desc,
    Times,
    Drawer,
    Args,
    Name,
    Definition,
    Body,
    HeaderArgs,
    File,
    Kind,
    Lang,
    Prefix,
    Text,
    Todo,
    Urgency,
    Title,
    Completion,
    Head,
    Subnodes,
    Properties,
    Logbook,
    Description,
    Logs,
    Newstate,
    Oldstate,
    Time,
    From,
    EndArgs,
    Flags,
    Value,
    Assoc,
    Main,
    Hash,
    Bullet,
    Counter,
    Checkbox,
    Header,
    To,
    Diff,
    Property,
    Subname,
    Values,
    Cells,
    Rows,
    Lines,
    Chunks,
};


enum class OrgNodeKind : short int
{
    None,     /// Default valye for node - invalid state
    Document, /*!Toplevel part of the ast, not created by parser, and
                        only used in `semorg` stage */
    UserNode, /// User-defined node [[code:OrgUserNode]]
    Empty,    /// Empty node - valid state that does not contain any value

    /// Failed node parse - technically there are no /wrong/ syntax in the
    /// org-mode document because everything can be considered a one large
    /// word or a paragraph with flat `Word` content.
    ///
    /// Error node's extent covers all subnodes that were constructed
    /// during nested content parsing plus ErrorTerminator node with error
    /// token (description of the parsing failure). So failure node will be
    /// structured as `[Error <some content> <ErrorToken>
    /// <ErrorTermiator>]`. Second-to-last is the invalid token itself,
    /// error terminator will hold fake token that referes to an error.
    ///
    /// Error node can be produced by any parsing routine, although it is
    /// mostly used in the low-level text elements, since high-level
    /// structures are mostly detected based on the correct syntax - for
    /// example, `*** subtree` (and any title variations) can never be an
    /// error in itself. Title /text/ might contain an error, but invalid
    /// it is not possible to write an invalid subtree - it is either `*
    /// ANYTHING` or not a subtree at all.
    Error,
    /// Terminator node for failure in nested structure parsing
    ErrorTerminator,
    /// Single invalid token
    ErrorToken,
    InlineStmtList,
    StmtList, /// List of statements, possibly recursive. Used as toplevel
              /// part of the document, in recursive parsing of subtrees,
              /// or as regular list, in cases where multiple subnodes have
              /// to be grouped together.
    AssocStmtList,
    /// Associated list of statements - AST elements like commands and
    /// links are grouped together if placed on adjacent lines
    Subtree,      /// Section subtree
    SubtreeTimes, /// Time? associated with subtree entry
    SubtreeStars,
    Completion, /// Task compleation cookie, indicated either in percents
                /// of completion, or as `<done>/<todo>` ratio.
    Checkbox,   /// Single checkbox item like `[X]` or `[-]`
    List,
    Bullet, /// List item prefix
    ListItem,
    ListTag, /// Auxilliary wrapper for the paragraph placed at the start
             /// of the description list.
    Counter,
    Comment,
    /// Inline or trailling comment. Can be used addition to `#+comment:`
    /// line or `#+begin-comment` section. Nested comment syntax is allowed
    /// (`#[ level1 #[ level2 ]# ]#`), but only outermost one is
    /// represented as separate AST node, everything else is a `.text`
    RawText,
    /// Raw string of text from input buffer. Things like particular syntax
    /// details of every single command, link formats are not handled in
    /// parser, deferring formatting to future processing layers
    Unparsed,
    /// Part of the org-mode document that is yet to be parsed. This node
    /// should not be created manually, it is only used for handling
    /// mutually recursive DSLs such as tables, which might include lists,
    /// which in turn might contain more tables in different bullet points.
    Command, /// Undefined single-line command -- most likely custom
             /// user-provided oe
    CommandArguments, /// Arguments for the command block
    CommandTitle,     /// `#+title:` - full document title
    CommandAuthor,    /// `#+author:` Document author
    CommandCreator,   /// `#+creator:` Document creator
    CommandInclude,
    /// `#+include:` - include other org-mode document (or subsection of
    /// it), source code or backend-specific chunk.
    CommandLanguage, /// `#+language:`
    CommandAttrHtml, /// `#+attr_html:`
    CommandName,     /// `#+name:` - name of the associated entry
    CommandHeader,
    /// `#+header:` - extended list of parameters passed to associated block
    CommandOptions, /// `#+options:` - document-wide formatting options
    CommandBackendOptions,
    /// Backend-specific configuration options like `#+latex_header`,
    /// `#+latex_class` etc.
    AttrImg,
    CommandCaption, /// `#+caption:` command
    File,
    ExportCommand,
    MultilineCommand,
    /// Multiline command such as code block, latex equation, large block
    /// of passthrough code. Some built-in org-mode commands do not
    /// requires `#+begin` prefix, (such as `#+quote` or `#+example`) are
    /// represented by this type of block as well.
    Result, /// Command evaluation result
    Ident,
    /// regular identifier - `alnum + [-_]` characters for punctuation.
    /// Identifiers are compared and parsed in style-insensetive manner,
    /// meaning `CODE_BLOCK`, `code-block` and `codeblock` are identical.
    BareIdent, /// Bare identifier - any characters are allowed
    AdmonitionTag,
    /// Big ident used in conjunction with colon at the start of paragraph
    /// is considered an admonition tag: `NOTE: Text`, `WARNING: text` etc.
    BigIdent, /// full-uppsercase identifier such as `MUST` or `TODO`
    VerbatimMultilineBlock,
    /// Verbatim mulitiline block that *might* be a part of
    /// `orgMultilineCommand` (in case of `#+begin-src`), but not
    /// necessarily. Can also be a part of =quote= and =example= multiline
    /// blocks.
    CodeLine,    /// Single line of source code
    CodeText,    /// Block of source code text
    CodeTangle,  /// Single tangle target in the code block
    CodeCallout, /// `(refs:` callout in the source code
    QuoteBlock,  /// `#+quote:` block in code
    AdmonitionBlock,
    CenterBlock,
    Example, /// Verbatim example text block
    SrcCode, /// Block of source code - can be multiline, single-line and
    SrcInlineCode,
    /// inline piece of code (such as `src_nim`). Latter is different from
    /// regular monospaced text inside of `~~` pair as it contains
    /// additional internal structure, optional parameter for code
    /// evaluation etc.
    CallCode,
    /// Call to named source code block. Inline, multiline, or single-line.
    PassCode,
    /// Passthrough block. Inline, multiline, or single-line. Syntax is
    /// `@@<backend-name>:<any-body>@@`. Has line and block syntax
    /// respectively
    CmdArguments, /// Command arguments
    CmdFlag,
    /// Flag for source code block. For example `-n`, which is used to to
    /// make source code block export with lines
    CmdKey,
    CmdValue,
    CmdNamedValue, /// Key-value pair for source code block call.
    UrgencyStatus,
    /// Subtree importance level, such as `[#A]` or `[#B]`. Default
    /// org-mode only allows single character for contents inside of `[]`,
    /// but this parser makes it possible to use any regular identifier,
    /// such as `[#urgent]`.
    TextSeparator, /// Long horizontal line `----`
    /// Single 'paragraph' of text. Used as generic container for any place
    /// in AST where unordered sentence might be encountered - not limited
    /// to actual paragraph

    Paragraph,
    /// Annotated paragraph -- a wrapper around a regular paragraph kind
    /// with added admonition, footnote, list tag prefix and similar types.
    /// `[fn:ID] Some Text` is an annotated paragraph, just like `NOTE:
    /// Text` or `- Prefix :: Body` (in this case list header is an
    /// annotated paragraph)
    AnnotatedParagraph,


    ///@{
    ///
    /// Region of text with formatting, which contains standalone words -
    /// can itself contain subnodes, which allows to represent nested
    /// formatting regions, such as `*bold /italic/*` text. Particular type
    /// of identifier is stored in string form in `str` field for `OrgNode`
    /// -- bold is represented as `"*"`, italic as `/` and so on. In case
    /// of explicit open/close pairs only opening one is stored.
    ///
    /// NOTE: when structured sentences are enabled, regular punctuation
    /// elements like `some text (notes)` are also represented as `Word,
    /// Word, Markup(str: "(", [Word])` - e.g. structure is not fully flat.
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
    ///@}

    InlineMath,
    /// Inline latex math. Contains latex math body - either from
    /// `$dollar-wrapped$` or `\(paren-wrapped\)` inline text.
    DisplayMath,
    /// Inline display latex math from `$$double-dollar$$` or
    /// `\[bracket-wrapped\]` code.
    Space, /// Space or tab character in regular text
    Punctuation,
    Colon,
    Word,
    /// Regular word - technically not different from `orgIdent`, but
    /// defined separately to disiguish between places where special syntax
    /// is required and free-form text.
    Escaped, /// Escaped formatting character in the text
    Newline,
    SkipNewline,
    SkipSpace,
    SkipAny,
    RawLink, /// Raw unwrapped link that was pasted in text
    Link,
    /// External or internal link. Consists of one or two elements - target
    /// (url, file location etc.) and description (`orgParagraph` of text).
    /// Description might be empty, and represented as empty node in this
    /// case. For external links particular formatting of the address is
    /// not handled by parser and instead contains raw string from input
    /// text.
    Macro,
    /// Org-mode macro replacement - during export each macro is expanded
    /// and evaluated according to it's environment. Body of the macro is
    /// not parsed fully during org-mode evaluation, but is checked for
    /// correct parenthesis balance (as macro might contain elisp code)
    BackendRaw,
    /// Raw content to be passed to a particular backend. This is the most
    /// compact way of quoting export strings, after `#+<backend>:
    /// <single-backend-line>` and `#+begin-export <backend>`
    /// `<multiple-lines>`.
    Symbol,
    /// Special symbol that should be exported differently to various
    /// backends - greek letters (`\alpha`), mathematical notations and so
    /// on.
    TimeAssoc, /// Time association pair for the subtree deadlines.
    StaticActiveTime,
    StaticInactiveTime,
    DynamicActiveTime,
    DynamicInactiveTime,
    /// Single date and time entry (active or inactive), possibly with
    /// repeater interval. Is not parsed directly, and instead contains
    /// `orgRawText` that can be parsed later
    TimeRange, /// Date and time range format - two `orgDateTime` entries
    SimpleTime,
    /// Result of the time range evaluation or trailing annotation a
    /// subtree
    Details, /// `#+begin_details`  section
    Summary, /// `#+begin_summary` section
    Table,
    /// Org-mode table. Tables can be writtein in different formats, but in
    /// the end they are all represented using single ast type. NOTE: it is
    /// not guaranteed that all subnodes for table are exactly
    /// `orgTableRow` - sometimes additional property metadata might be
    /// used, making AST like `Table[AssocStmtList[Command[_],
    /// TableRow[_]]]` possible
    TableRow, /// Horizontal table row
    TableCell,
    /// Single cell in row. Might contain anyting, including other tables,
    /// simple text paragraph etc.
    InlineFootnote,
    /// Inline footnote with text placed directly in the node body.
    Footnote,
    /// Footnote entry. Just as regular links - internal content is not
    /// parsed, and instead just cut out verbatim into target AST node
    /// .
    Horizontal,
    /// Horizotal rule. Rule body might contain other subnodes, to represnt
    /// `---- some text ----` kind of formatting.
    Filetags, /// `#+filetags:` line command
    OrgTag,
    /// Original format of org-mode tags in form of `:tagname:`. Might
    /// contain one or mode identifgiers, but does not provide support for
    /// nesting - `:tag1:tag2:`. Can only be placed within restricted set
    /// of places such as subtree headings and has separate place in AST
    /// when allowed (`orgSubtree` always has subnode `№4` with either
    /// `orgEmpty` or `orgOrgTag`)
    HashTag,
    /// More commonly used `#hashtag` format, with some additional
    /// extension. Can be placed anywere in the document (including section
    /// headers), but does not have separate place in AST (e.g. considered
    /// regular part of the text)
    MetaSymbol, /// `\sym{}` with explicit arguments
    AtMention,  /// `@user`
    BracTag,
    /// Custom extension to org-mode. Similarly to `BigIdent` used to have
    /// something like informal keywords `MUST`, `OPTIONAL`, but instead
    /// aimed /specifically/ at commit message headers - `[FEATURE]`,
    /// `[FIX]` and so on.
    Drawer,
    /// Single enclosed drawer like `:properties: ... :end:` or `:logbook:
    /// ... :end:`
    LatexClass,
    LatexHeader,
    LatexCompiler,
    Columns,
    /// `#+columns:` line command for specifying formatting of the org-mode
    /// clock table visualization on per-file basis.
    PropertyList,
    Property,
    /// Property entry, either in `#+property:` command, or in `:property:` drawer
    PropertyAdd, /*!Property value extensions - `:property+:` */
    Placeholder,
    /// Placeholder entry in text, usually writte like `<text to replace>`
    SubtreeDescription, /// `:description:` entry
    Logbook,            /// `:logbook:` entry storing note information
    LogbookEntry,
    LogbookStateChange, /// Annotation about change in the subtree todo
                        /// state
    LogbookNote,        /// Timestamped log note on the subtree
    LogbookClock,       /// `CLOCK` entry in the subtree
    LogbookRefile,      /// `Refile` entry in the subtree logbook drawer
    RadioTarget,        /// `<<<RADIO>>>`
    Target,             /// `<<TARGET>>`

    __LAST
};

enum class OrgSemKind
{
    StmtList,
    Row,
    Table,
    HashTag,
    Completion,
    Paragraph,
    BigIdent,
    Link,
    Bold,
    Italic,
    Strike,
    Monospace,
    Verbatim,
    RawText,
    List,
    ListItem,
    Center,
    Par,
    Quote,
    Example,
    Code,
    Time,
    SubtreeLog,
    TimeRange,
    Subtree,
    Newline,
    Space,
    Word,
    Punctuation,
    MarkQuote,
    Caption,
};


enum class OrgTextContext : short int
{
    otcPlain,
    otcSubtree0,
    otcSubtree1,
    otcSubtree2,
    otcSubtree3,
    otcSubtree4,
    otcSubtree5,
    otcSubtree6,
    otcSubtree7,
    otcSubtree8,
    otcSubtree9,
    otcSubtree10,
    otcSubtree11,
    otcSubtree12,
    otcSubtreeOther,
    otcBold,
    otcItalic,
    otcStrike,
    otcUnderline,
    otcMonospaceInline,
    otcMonospaceBlock,
};

enum class OrgBigIdentKind : short int
{
    obiNone,
    obiMust,
    /// MUST This word, or the terms "REQUIRED" or "SHALL", mean that the
    /// definition is an absolute requirement of the specification.
    obiMustNot,
    /// MUST NOT This phrase, or the phrase "SHALL NOT", mean that the
    /// definition is an absolute prohibition of the specification.
    obiShould,
    /// SHOULD This word, or the adjective "RECOMMENDED", mean that there
    /// may exist valid reasons in particular circumstances to ignore a
    /// particular item, but the full implications must be understood and
    /// carefully weighed before choosing a different course.
    obiShouldNot,
    /// SHOULD NOT This phrase, or the phrase "NOT RECOMMENDED" mean that
    /// there may exist valid reasons in particular circumstances when the
    /// particular behavior is acceptable or even useful, but the full
    /// implications should be understood and the case carefully weighed
    /// before implementing any behavior described with this label.
    obiRequired,
    obiOptional,
    /// MAY This word, or the adjective "OPTIONAL", mean that an item is
    /// truly optional. One vendor may choose to include the item because a
    /// particular marketplace requires it or because the vendor feels that
    /// it enhances the product while another vendor may omit the same
    /// item. An implementation which does not include a particular option
    /// MUST be prepared to interoperate with another implementation which
    /// does include the option, though perhaps with reduced functionality.
    /// In the same vein an implementation which does include a particular
    /// option MUST be prepared to interoperate with another implementation
    /// which does not include the option (except, of course, for the
    /// feature the option provides.)
    obiReallyShouldNot,
    obiOughtTo,
    obiWouldProbably,
    obiMayWishTo,
    obiCould,
    obiMight,
    obiPossible,
    obiTodo,
    obiIdea,
    obiError,
    obiFixme,
    obiDoc,
    obiRefactor,
    obiReview,
    obiHack,
    obiImplement,
    obiExample,
    obiQuestion,
    obiAssume,
    obiInternal,
    obiDesign,
    obiWhy,
    obiWip,
    obiFix,
    obiClean,
    obiFeature,
    obiStyle,
    obiRepo,
    obiSkip,
    obiBreak,
    obiPoc,
    obiNext,
    obiLater,
    obiPostponed,
    obiStalled,
    obiDone,
    obiPartially,
    obiCancelled,
    obiFailed,
    obiNote,
    obiTip,
    obiImportant,
    obiCaution,
    obiWarning,
    obiUserCodeComment, /// User-defined comment message
    obiUserCommitMsg,   /// User-defined commit message ident
    obiUserTaskState,   /// User-defined task state
    obiUserAdmonition,  /// User-defined admonition label
    obiOther,    /// User-defined big-idents, not included in default set.
    obiStructIf, /// @pushgroup{structured-english}
    obiStructAnd,
    obiStructOr,
    obiStructNot,
    obiStructGet,
    obiStructSet,
    obiStructThen,
    obiStructElse,
    obiStructWhile,
    /*!@popgroup{} It is not hard to support
https://en.wikipedia.org/wiki/Structured_English keywords. Maybe I
will merge it with haxdoc somehow, maybe not, for not I just placed
them here as a reminder to myself. My current idea is to overlay
semi-structured explanation in the documenation with actual code.
Structured keywords can be used as an anchor points (e.g. `IF` maps
to real condition, `THEN` to the body and so on).
*/
};
;

enum class OrgMetaTagKind
{
    smtArg,      /// Procedure argument
    smtParam,    /// Generic entry parameter
    smtRet,      /// Procedure return value
    smtEnum,     /// Reference enum, enum value, or set of values.
    smtGlobal,   /// Reference to global variable or constant
    smtAccs,     /// Documented access to external state (most often global
                 /// variable, file, or environment variable)
    smtField,    /// Entry field
    smtCat,      /// Entry category name
    smtFile,     /// Filesystem filename
    smtDir,      /// Filesystem directory
    smtEnv,      /// Environment variable
    smtKbdChord, /// Keyboard chord (multiple key combinations)
    smtKbdKey,   /// Single keyboard key combination (key + modifiers)
    smtOption,   /// CLI option
    smtSh,       /// Execute (simple) shell command
    smtAbbr,     /// Abbreviation like CPS, CLI
    smtInject,   /// Identifier injected in scope
    smtEDSL, /// Embedded DSL syntax description in Extended BNF notation
    smtPatt,
    smtImport,
    smtUnresolved,
    /*!Unresolved metatag. User-defined tags SHOULD be
converted to `smtOther`. Unresolved tag MIGHT be
treated as error/warning when generating final export.
*/
    smtValue,
    /*!Procedure argument/return value, or field
state that has some additional semantic meaning. For example, exit
codes should ideally be documented using

```org
- @value{-1} :: Documentation for return value `-1`. Might also
`@import{}` or link (using `[[code:]]` or other methods) different
lists/enums (for example if return value is mapped to an enum)
```
*/
    smtOther,
    /*!Undefined metatag
     */
};


enum class OrgTokenKind : short int
{
    None,
    Eof,
    /// Start of the tokenizer token group
    GroupStart,
    /// Tokenizer token group end
    GroupEnd,


    ErrorTerminator,
    CommandPrefix,
    LineCommand,
    CommandBegin,
    /// `#+begin` part of the multiline command. `begin_<block-type>` is
    /// split into two tokens - `begin_` prefix and `ockBegin<block-type>`
    /// section.
    CommandEnd,
    DoubleColon,
    Text,
    StmtList,
    /// Unlexed group of statements - used in the list content to enable
    /// secondary parsing.
    StmtListOpen,  /// Start of the expanded statement list content
    StmtListClose, /// End of the expanded statement list content
    ListStart,     /// Start of the list token group
    ListItemStart, /// Start of the list item element
    ListClock, /// `CLOCK:` entry at the start of the logbook entry list
    ListPlus,
    ListStar,
    ListDescOpen,  /// Start of the description list key,
    ListDescClose, /// End of the description list key `::`
    ListItemEnd,   /// End of the list item
    ListEnd,       /// Complete end of the list token group
    Checkbox,      /// List or subtree checkbox
    SubtreeTodoState,
    SubtreeUrgency,    /// Subtree importance marker
    SubtreeCompletion, /// Subtree completion marker
    SubtreeStars,      /// Subtree prefix
    SubtreeTagSeparator,
    SubtreeTime,
    SubtreeEnd,
    ImplicitTime,
    /// You can write time ranges without any additional formatting for
    /// subtrees that have a diary timestamps. For example, you have a
    /// complex date predicate, but event occurs for `18:00-21:00`, so you
    /// write it in the random place in the subtree.
    TimeDuration,
    /// Time duration for the `effort` property or time range length
    /// evaluation
    InactiveTimeBegin, /// Start of the inactive timestamp (`[2022-03-12]`)
    InactiveTimeEnd,
    ActiveTimeBegin, /// Start of the active timestamp `<2030-02-03>`
    ActiveTimeEnd,
    DynamicTimeContent,  /// Dynamic time content
    StaticTimeDatePart,  /// year-month-day part of the timestamp
    StaticTimeDayPart,   /// weekday part of the timestamp
    StaticTimeClockPart, /// Clock part of the timestamp
    StaticTimeRepeater,  /// Type of the time repeater: `+`, `++`, `.+`

    TimeDash,
    /// Separator dash between two periods in the time range
    /// (`<start>--<finish.`)
    TimeArrow,       /// Time range evaluation arrow `[from]--[to] =>`
    Comment,         /// line or inline comment
    ListDoubleColon, /// Double colon between description list tag and body
    CommandArgumentsBegin, /// List of command arguments
    CommandArgumentsEnd,   /// End of the command arguments list
    CommandKey,
    CommandValue,
    CommandFlag,
    CommandBracket, /// `#+results[HASH...]`
    ColonLiteral,   /// Literal block with `:`
    ColonIdent,
    /// Drawer or source code block wrappers with colon-wrapped
    /// identifiers. `:results:`, `:end:` etc.
    ColonAddIdent,    /// Add value to the existing drawer property -
                      /// `:NAME+:`
    ColonProperties,  /// Start of the `:PROPERTIES:` block drawer block
    ColonDescription, /// Start of the `:description:` drawer block
    ColonEnd,
    ColonLogbook,
    RawLogbook,
    LogbookStart,
    LogbookEnd,
    RawProperty,
    Link, /// Any kind of link
    CommandContentStart,
    CommandContentEnd,
    CodeContent,      /// Block of code inside `#+begin_src`
    CodeContentBegin, /// Start of the expanded code content
    CodeContentEnd,   /// End of the expanded code content
    CodeText,
    /// Uninterrupted text span without newlines - either a whole line or
    /// sub subsection of it if callout or tangle elements were detected
    TableContent, /// Block of text inside `#+table`
    QuoteContent, /// `#+quote` content
    BackendPass,  /// Backend-specific passthrough
    LogBook,      /// Logbook including content
    Drawer,       /// Drawer including content
    Indent,       /// Increase in indentation
    Dedent,       /// Decrease in indentation
    SameIndent,
    NoIndent,
    // clang-format off
    BoldOpen,      BoldClose,      BoldInline,      BoldInlineOpen,      BoldInlineClose,
    ItalicOpen,    ItalicClose,    ItalicInline,    ItalicInlineOpen,    ItalicInlineClose,
    VerbatimOpen,  VerbatimClose,  VerbatimInline,  VerbatimInlineOpen,  VerbatimInlineClose,
    MonospaceOpen, MonospaceClose, MonospaceInline, MonospaceInlineOpen, MonospaceInlineClose,
    BacktickOpen,  BacktickClose,  BacktickInline,  BacktickInlineOpen,  BacktickInlineClose,
    UnderlineOpen, UnderlineClose, UnderlineInline, UnderlineInlineOpen, UnderlineInlineClose,
    StrikeOpen,    StrikeClose,    StrikeInline,    StrikeInlineOpen,    StrikeInlineClose,
    // clang-format on
    QuoteOpen,
    QuoteClose,
    Punctuation,
    LinkOpen,
    LinkClose,
    RawUrl,
    LinkTargetOpen,
    LinkTargetClose,
    LinkInternal,
    /// No protocol is used in the link, it is targeting some internal
    /// named entry.
    LinkProtocol,
    /// Protocol used by the link - `file:`, `https:` etc.
    LinkFull,
    /// Full token for the link, used in cases where it does not make sense
    /// to fracture the token - regular https URLs etc.
    LinkHost,
    /// Host part of the URI used in link
    LinkPath,
    /// Path part of the link
    LinkTarget,
    /// Target of the link protocol that does not follow regular URI
    /// encoding scheme - for example `id:`, `elisp`, or `shell` links.
    LinkExtraSeparator,
    /// Separator of the extra content in the link, `::`
    LinkExtra,
    /// Additional parametrization for the link search
    LinkDescriptionOpen,
    LinkDescriptionClose,
    TextSeparator,
    ParagraphStart,
    /// Fake token inserted by the lexer to delimit start of the paragraph
    ParagraphEnd,
    FootnoteStart,
    FootnoteEnd,
    Word,
    /// Regular word in the paragraph
    Escaped,
    /// Escaped character in plain text - `\*`, `\/` etc. Escaped
    /// characters and sequences thereof are treated like a regular plain
    /// text.
    DoubleSlash,
    /// Put at the end of the lexer first logbook line to separate the
    /// note, otherwise is treated as standalone escaped slash.
    Newline,
    /// Explicit newline a paragraph
    SkipSpace,
    SkipNewline,
    SkipAny,

    MaybeWord,
    Space,
    /// Space in the paragraph
    BigIdent,
    /// `TODO`, `NOTE` and similar capitalized words
    RawText,
    /// Unparsed raw text, either as a part of paragraph or some embedded
    /// construction such as link address.
    InlineSrc,   /// Start of an inline source code block: `src_nim[]{}`
    InlineCall,  /// Start of an inline call block: `call_name[]{}`
    CurlyStart,  /// Start of the curly section of an inline source/call
    CurlyEnd,    /// End of the curly section of an inline source/call
    SymbolStart, /// Unquoted `\symbol` directly in the text
    Ident,
    DollarOpen,        /// Opening dollar inline latex math
    DollarClose,       /// Closing dollar for inline latex math
    DoubleDollarOpen,  /// Opening `$` for inline latex
    DoubleDollarClose, /// Closing `$` for inline latex
    LatexParOpen,      /// Opening `\(` for inline latex math
    LatexParClose,     /// Closing `\)` for inline latex math
    LatexBraceOpen,    /// Opening `\[` for inline display latex equation
    LatexBraceClose,   /// Closing `\]` for inline display latex equation
    LatexInlineRaw,    /// Content of the brace/par-enclosed math
    DoubleAt,          /// Inline backend passthrough `@@`
    AtBracket,         /// Inline annotation
    AtMention,         /// `@user` mention in the text
    HashTag,           /// Start of the inline hashtag `#tag`
    HashTagSub,        /// Nested hashtag separator
    HashTagOpen,       /// Start of the nested hashtag grop bracket
    HashTagClose,      /// End of the nested hashtag group separator
    Comma,    /*!Comma - punctuation or a syntax element (e.g. for macro
                 arguments) */
    ParOpen,  /// Paren open - punctuation or a syntax element
    ParClose, /// Paren close - punctuation or a syntax element
    Colon,
    Circumflex, /// `^` possible superscript in the text
    MacroOpen,  /// Start of the macro call `{{{`
    MacroClose, /// Close of the macro call `}}}`
    MetaBraceOpen,
    MetaBraceBody,
    MetaBraceClose,
    MetaArgsOpen,
    MetaArgsBody,
    MetaArgsClose,
    SrcOpen,
    SrcName,
    SrcArgs,
    SrcBody,
    SrcClose,
    CallOpen,
    CallName,
    CallInsideHeader,
    CallArgs,
    EndHeader,
    CallClose,
    CmdArguments,
    TableBegin,
    TableEnd,
    CellBody,     /// Unformatted table cell body
    RowSpec,      /// `#+row` command together with parameters
    CellSpec,     /// `#+cell` command with parameters
    Content,      /// Temporary token created during initial content lexing
    ContentStart, /// Start of the table cell content section
    ContentEnd,   /// End of the table cell content section
    PipeOpen,
    PipeSeparator, /// Vertical pipe (`|`) cell separator
    PipeClose,
    PipeCellOpen,
    DashSeparator, /*!Horizontal dash (`---`, `:---`, `---:` or `:---:`)
                      row separator */
    CornerPlus,    /// Corner plus (`+`)
    Command,
    CommandArgs,
    Body,
    LangName,
    DoubleAngleOpen,  /// `<<` - open for noweb or anchor placeholder
    DoubleAngleClose, /// `>>` - close for noweb or anchor placeholder
    TripleAngleOpen,  /// `<<<` - radio target open
    TripleAngleClose, /// `>>>` - radio target close
    AngleOpen,        /// Placeholder open
    AngleClose,       /// Placeholder close
    TextBlock,
    /// Code before noweb placeholder. Requires separate token to handle
    /// `##<<commented>>` - prefix comment should be duplicated for each
    /// line of the placeholder expansion.
};

enum class OrgCommandKind
{
    None,
    Include,
    Filetags,
    Setupfile,
    Columns,
    OtherProperty,
    BeginTable,
    EndTable, /// `#+table`
    Row,      /// `#+row`
    Cell,     /// `#+cell`
    BeginAdmonition,
    EndAdmonition,
    BeginDynamic,
    EndDynamic, /// `#+begin:`
    BeginCenter,
    EndCenter, /// `#+begin_center`
    BeginQuote,
    EndQuote, /// `#+quote`
    BeginSrc,
    EndSrc, /// `#+begin_src`
    BeginExport,
    EndExport, /// `#+end_export`
    BeginExample,
    EndExample,
    BeginDetails,
    EndDetails,
    BeginSummary,
    EndSummary,
    LatexClassOptions, /// `#+latex_class_options`
    LatexClass,
    LatexCompiler,
    AttrLatex,   /// `#+attr_latex:`
    AttrImg,     /// `#+attr_img:`
    AttrHtml,    /// `#+attr_html:`
    HtmlHead,    /// `#+html_head:`
    Language,    /// `#+language:`
    Options,     /// `#+options: `
    Title,       /// `#+title:`
    Property,    /// `#+property:`
    Author,      /// `#+author:`
    Bind,        /// `#+bind:`
    Creator,     /// `#+creator:`
    LatexHeader, /// `#+latex_header`
    Results,     /// `#+results:`
    Call,        /// `#+call:`
    Name,        /// `#+name:`
    Caption,     /// `#+caption:`
    Header,      /// `#+header:`
};

enum class OrgPropertyKind : short int
{
    Title,
    Author,
    Date,
    Email,
    Language,
    Url,
    SourceUrl,
    AttrImg,
    Toplevel,
    Blocker,
    Created,
    Unnumbered,
    Trigger,
    Ordered,
    Noblocking,
    ExportOptions,
    BackendExportOptions,
    AttrBackend,
    ColumnSpec,
    Name,
    Caption,
    LinkAbbrev,
    Filetags,
    TagConf,
    LatexHeader,
    OtherProperty,
    Id
};

enum class OrgUnnumberedKind : short int
{
    Notoc,
    True,
    False
};


enum class OrgBlockLexerState : short int
{
    None,
    InHeader,
    InBody,
    Ended,
    Complete,
};
