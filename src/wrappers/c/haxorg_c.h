/* clang-format off */
#pragma once
#include <wrappers/c/haxorg_c_api.h>
struct haxorg_SemIdOfOrg;

struct haxorg_HstdVecOfOrgJson;

struct haxorg_HstdVecOfSemIdOfOrg;

struct haxorg_HstdVecOfReport;

struct haxorg_HstdVecOfSemIdOfErrorGroup;

struct haxorg_HstdVecOfInt;

struct haxorg_HstdVecOfImmAdapter;

struct haxorg_HstdVecOfSequenceSegment;

struct haxorg_HstdVecOfSequenceAnnotationTag;

struct haxorg_HstdVecOfImmUniqId;

struct haxorg_HstdVecOfGraphMapLink;

struct haxorg_HstdVecOfGraphMapNode;

struct haxorg_HstdVecOfGraphMapEdge;

struct haxorg_HstdVecOfLispCode;

struct haxorg_HstdVecOfTblfmAssign;

struct haxorg_HstdVecOfTblfmExpr;

struct haxorg_HstdVecOfTblfmAssignFlag;

struct haxorg_HstdVecOfAttrValueDimensionSpan;

struct haxorg_HstdVecOfStr;

struct haxorg_HstdVecOfHashTagFlat;

struct haxorg_HstdVecOfHashTagText;

struct haxorg_HstdVecOfAttrValue;

struct haxorg_HstdVecOfOrgCodeEvalInputVar;

struct haxorg_HstdVecOfColumnViewColumn;

struct haxorg_HstdVecOfBlockCodeLinePart;

struct haxorg_HstdVecOfSemIdOfErrorItem;

struct haxorg_HstdVecOfTimeRepeat;

struct haxorg_HstdVecOfSymbolParam;

struct haxorg_HstdVecOfSemIdOfErrorSkipToken;

struct haxorg_HstdVecOfSubtreePeriod;

struct haxorg_HstdVecOfNamedProperty;

struct haxorg_HstdVecOfSemIdOfHashTag;

struct haxorg_HstdVecOfSemIdOfSubtreeLog;

struct haxorg_HstdVecOfTodoKeyword;

struct haxorg_HstdVecOfSemIdOfBigIdent;

struct haxorg_HstdVecOfUserTime;

struct haxorg_HstdVecOfSemIdOfTime;

struct haxorg_HstdVecOfSemIdOfCell;

struct haxorg_HstdVecOfOrgCodeEvalOutput;

struct haxorg_HstdVecOfSemIdOfBlockCodeEvalResult;

struct haxorg_HstdVecOfBlockCodeLine;

struct haxorg_HstdVecOfSemIdOfRow;

struct haxorg_HstdVecOfAstTrackingGroup;

struct haxorg_HstdVecOfSequenceAnnotation;

struct haxorg_HstdVecOfSequenceSegmentGroup;

struct haxorg_HstdMap;

struct haxorg_ImmMap;

enum class haxorg_CheckboxState : short int { None, Done, Empty, Partial, };
/// \brief Where to take todo completion statistics from
enum class haxorg_SubtreeTodoSource : short int {
  /// \brief Only count checkbox subnodes as a progress completion
  Checkbox,
  /// \brief Use subtrees with todo keywords
  Todo,
  /// \brief Use both subtrees and todo keywords
  Both,
};
enum class haxorg_ListFormattingMode : short int {
  /// \brief Default, no custom formatting
  None,
  /// \brief one column, each table item is an individual row
  Table1D1Col,
  /// \brief for description lists, treat header row as an individual column
  Table1D2Col,
  /// \brief for tables tables with arbitrary column count, treat the first level of items as column names, treat all nested elements in these columns as row values
  Table2DColFirst,
  /// \brief for tables with arbitrary column count, each top-level list item is an individual row, then each item in the nested list is a cell on this row.
  Table2DRowFirst,
};
enum class haxorg_InitialSubtreeVisibility : short int { Overview, Content, ShowAll, Show2Levels, Show3Levels, Show4Levels, Show5Levels, ShowEverything, };
enum class haxorg_OrgSpecName : short int { Unnamed, Result, Year, Day, Clock, Repeater, Warn, Zone, Link, Tags, Tag, State, Protocol, Desc, Times, Drawer, Args, Name, Definition, Body, HeaderArgs, File, Kind, Lang, Prefix, Text, Todo, Importance, Title, Completion, Head, Subnodes, Properties, Logbook, Description, Logs, Newstate, Oldstate, Time, From, EndArgs, Flags, Value, Assoc, Main, Hash, Bullet, Counter, Checkbox, Header, To, Diff, Property, Subname, Values, Cells, Rows, Lines, Chunks, };
enum class haxorg_OrgNodeKind : short int {
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
  Attrs,
  /// \brief :key name=value syntax
  AttrValue,
  /// \brief S-expression as an attribute value value
  AttrLisp,
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
  /// \brief `#+email:`
  CmdEmail,
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
  CmdKeywords,
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
  /// \brief #+begin_<any> section
  BlockDynamicFallback,
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
  /// \brief Error leaf node inserted into the parse tree on failure
  ErrorInfoToken,
  /// \brief Parent node for one or more tokens skipped during error recovery
  ErrorSkipGroup,
  /// \brief Single token node skipped while the parser searched for recovery point
  ErrorSkipToken,
  Italic,
  Verbatim,
  Backtick,
  Underline,
  Strike,
  Quote,
  Angle,
  Monospace,
  Par,
  CriticMarkStructure,
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
enum class haxorg_OrgTokenKind : short int { Ampersand, AngleBegin, AngleEnd, AnyPunct, Asterisk, At, Backtick, BigIdent, BoldBegin, BoldEnd, BoldUnknown, BraceBegin, BraceEnd, Checkbox, Circumflex, CmdAdmonitionEnd, CmdAttr, CmdAuthor, CmdBindRaw, CmdCall, CmdCaption, CmdCategoryRaw, CmdCell, CmdCellBegin, CmdCellEnd, CmdCenterBegin, CmdCenterEnd, CmdColonIdent, CmdColumns, CmdCommentBegin, CmdCommentEnd, CmdConstants, CmdContentBegin, CmdContentEnd, CmdCreator, CmdCustomRaw, CmdDateRaw, CmdDescription, CmdDrawersRaw, CmdDynamicBegin, CmdDynamicBlockBegin, CmdDynamicBlockEnd, CmdDynamicEnd, CmdEmailRaw, CmdExampleBegin, CmdExampleEnd, CmdExampleLine, CmdExcludeTagsRaw, CmdExportBegin, CmdExportEnd, CmdExportLine, CmdFiletags, CmdFlag, CmdHeader, CmdHtmlHeadRaw, CmdInclude, CmdLanguage, CmdLatexClass, CmdLatexClassOptions, CmdLatexCompiler, CmdLatexHeader, CmdLatexHeaderExtraRaw, CmdLinkRaw, CmdMacroRaw, CmdName, CmdOptions, CmdPrefix, CmdPrioritiesRaw, CmdPropertyArgs, CmdPropertyRaw, CmdPropertyText, CmdQuoteBegin, CmdQuoteEnd, CmdRawArg, CmdResults, CmdRow, CmdRowBegin, CmdRowEnd, CmdSelectTagsRaw, CmdSeqTodoRaw, CmdKeywordsRaw, CmdSetupfileRaw, CmdSrcBegin, CmdSrcEnd, CmdStartup, CmdTableBegin, CmdTableEnd, CmdTagsRaw, CmdTblfm, CmdTitle, CmdVerseBegin, CmdVerseEnd, Colon, ColonArgumentsProperty, ColonEnd, ColonExampleLine, ColonLiteralProperty, ColonLogbook, ColonProperties, ColonPropertyText, Comma, Comment, CriticAddBegin, CriticAddEnd, CriticCommentBegin, CriticCommentEnd, CriticDeleteBegin, CriticDeleteEnd, CriticHighlightBegin, CriticHighlightEnd, CriticReplaceBegin, CriticReplaceEnd, CriticReplaceMiddle, CurlyBegin, CurlyEnd, Date, Dedent, Dollar, DoubleAngleBegin, DoubleAngleEnd, DoubleColon, DoubleDash, DoubleHash, DoubleQuote, DoubleSlash, ActiveDynamicTimeContent, InactiveDynamicTimeContent, EndOfFile, Equals, Escaped, Exclamation, FootnoteInlineBegin, FootnoteLinked, ForwardSlash, HashIdent, HashTagBegin, Indent, InlineExportBackend, InlineExportContent, ItalicBegin, ItalicEnd, ItalicUnknown, LatexInlineRaw, LatexParBegin, LatexParEnd, LeadingMinus, LeadingNumber, LeadingPipe, LeadingPlus, LeadingSpace, LineCommand, LinkBegin, LinkDescriptionBegin, LinkDescriptionEnd, LinkEnd, LinkFull, LinkProtocol, LinkProtocolAttachment, LinkProtocolCustomId, LinkProtocolFile, LinkProtocolHttp, LinkProtocolId, LinkProtocolInternal, LinkProtocolTitle, LinkSplit, LinkTarget, LinkTargetBegin, LinkTargetEnd, LinkTargetFile, ListBegin, ListEnd, ListItemBegin, ListItemEnd, LongNewline, MediumNewline, Minus, MiscUnicode, MonospaceBegin, MonospaceEnd, MonospaceUnknown, Newline, Number, ParBegin, ParEnd, Percent, Pipe, Placeholder, Plus, Punctuation, RawText, SameIndent, Semicolon, SingleQuote, SrcContent, StmtListBegin, StmtListEnd, StrikeBegin, StrikeEnd, StrikeUnknown, SubtreeCompletion, SubtreePriority, SubtreeStars, Symbol, TableSeparator, TextSeparator, TextSrcBegin, Tilda, Time, TimeArrow, TimeRepeaterDuration, TimeRepeaterSpec, TimeWarnPeriod, TrailingPipe, TreeClock, TreeTime, TripleAngleBegin, TripleAngleEnd, Underline, UnderlineBegin, UnderlineEnd, UnderlineUnknown, Unknown, VerbatimBegin, VerbatimEnd, VerbatimUnknown, Whitespace, Word, };
enum class haxorg_OrgJsonKind : short int { Null, Object, Array, String, Boolean, Int, Float, };
enum class haxorg_OrgSemKind : short int { NoNode, ErrorItem, ErrorGroup, StmtList, Empty, CmdCaption, CmdCreator, CmdAuthor, CmdEmail, CmdLanguage, CmdColumns, CmdName, CmdCustomArgs, CmdCustomRaw, CmdCustomText, CmdCall, CmdTblfm, HashTag, InlineFootnote, InlineExport, Time, TimeRange, Macro, Symbol, Escaped, Newline, Space, Word, AtMention, RawText, Punctuation, Placeholder, BigIdent, TextTarget, ErrorSkipToken, ErrorSkipGroup, Bold, Underline, Monospace, MarkQuote, Verbatim, Italic, Strike, Par, RadioTarget, Latex, Link, BlockCenter, BlockQuote, BlockComment, BlockVerse, BlockDynamicFallback, BlockExample, BlockExport, BlockAdmonition, BlockCodeEvalResult, BlockCode, SubtreeLog, Subtree, Cell, Row, Table, Paragraph, ColonExample, CmdAttr, CmdExport, Call, List, ListItem, DocumentOptions, DocumentFragment, CriticMarkup, Document, FileTarget, TextSeparator, DocumentGroup, File, Directory, Symlink, CmdInclude, };
enum class haxorg_AstTrackingGroupKind : short int { RadioTarget, Single, TrackedHashtag, };
enum class haxorg_GraphMapLinkKind : short int { Radio, Link, };
struct haxorg_BackwardsIndex;

struct haxorg_HstdStr;

struct haxorg_UserTimeBreakdown;

struct haxorg_UserTime;

struct haxorg_ParseSourceFileId;

struct haxorg_ParseSourceManager;

struct haxorg_ParseSourceLoc;

struct haxorg_OrgJson;

struct haxorg_Org;

struct haxorg_OperationsTracer;

struct haxorg_Cache;

struct haxorg_Report;

struct haxorg_ParseOrgParseFragment;

struct haxorg_OrgParseParameters;

struct haxorg_OrgDirectoryParseParameters;

struct haxorg_ParseContext;

struct haxorg_ImmReflFieldId;

struct haxorg_ImmId;

struct haxorg_ImmOrg;

struct haxorg_ImmPathStep;

struct haxorg_ImmPath;

struct haxorg_ImmUniqId;

struct haxorg_ImmAstReplaceEpoch;

struct haxorg_ImmAstContext;

struct haxorg_ImmAstVersion;

struct haxorg_ImmAdapter;

struct haxorg_ImmAdapterTreeReprConf;

struct haxorg_ImmAdapterVirtualBase;

struct haxorg_OrgYamlExportOpts;

struct haxorg_OrgTreeExportOpts;

struct haxorg_AstTrackingPath;

struct haxorg_AstTrackingAlternatives;

struct haxorg_AstTrackingGroup;

struct haxorg_AstTrackingGroupRadioTarget;

struct haxorg_AstTrackingGroupSingle;

struct haxorg_AstTrackingGroupTrackedHashtag;

struct haxorg_AstTrackingMap;

struct haxorg_SequenceSegment;

struct haxorg_SequenceSegmentGroup;

struct haxorg_SequenceAnnotationTag;

struct haxorg_SequenceAnnotation;

struct haxorg_GraphMapLink;

struct haxorg_GraphMapLinkLink;

struct haxorg_GraphMapLinkRadio;

struct haxorg_GraphMapNodeProp;

struct haxorg_GraphMapEdgeProp;

struct haxorg_GraphMapNode;

struct haxorg_GraphMapEdge;

struct haxorg_GraphMapGraph;

struct haxorg_GraphMapConfig;

struct haxorg_GraphMapGraphState;

struct haxorg_LispCode;

struct haxorg_LispCodeCall;

struct haxorg_LispCodeList;

struct haxorg_LispCodeKeyValue;

struct haxorg_LispCodeNumber;

struct haxorg_LispCodeText;

struct haxorg_LispCodeIdent;

struct haxorg_LispCodeBoolean;

struct haxorg_LispCodeReal;

struct haxorg_Tblfm;

struct haxorg_TblfmExpr;

struct haxorg_TblfmExprAxisRef;

struct haxorg_TblfmExprAxisRefPosition;

struct haxorg_TblfmExprAxisRefPositionIndex;

struct haxorg_TblfmExprAxisRefPositionName;

struct haxorg_TblfmExprAxisName;

struct haxorg_TblfmExprIntLiteral;

struct haxorg_TblfmExprFloatLiteral;

struct haxorg_TblfmExprRangeRef;

struct haxorg_TblfmExprCall;

struct haxorg_TblfmExprElisp;

struct haxorg_TblfmAssign;

struct haxorg_AttrValue;

struct haxorg_AttrValueDimensionSpan;

struct haxorg_AttrValueTextValue;

struct haxorg_AttrValueFileReference;

struct haxorg_AttrValueLispValue;

struct haxorg_HashTagFlat;

struct haxorg_TodoKeyword;

struct haxorg_HashTagText;

struct haxorg_SubtreePath;

struct haxorg_LinkTarget;

struct haxorg_LinkTargetRaw;

struct haxorg_LinkTargetId;

struct haxorg_LinkTargetCustomId;

struct haxorg_LinkTargetSubtreeTitle;

struct haxorg_LinkTargetPerson;

struct haxorg_LinkTargetUserProtocol;

struct haxorg_LinkTargetInternal;

struct haxorg_LinkTargetFootnote;

struct haxorg_LinkTargetFile;

struct haxorg_LinkTargetAttachment;

struct haxorg_SubtreeLogHead;

struct haxorg_SubtreeLogHeadPriority;

struct haxorg_SubtreeLogHeadNote;

struct haxorg_SubtreeLogHeadRefile;

struct haxorg_SubtreeLogHeadClock;

struct haxorg_SubtreeLogHeadState;

struct haxorg_SubtreeLogHeadDeadline;

struct haxorg_SubtreeLogHeadSchedule;

struct haxorg_SubtreeLogHeadTag;

struct haxorg_SubtreeLogHeadUnknown;

struct haxorg_SubtreeCompletion;

struct haxorg_AttrList;

struct haxorg_AttrGroup;

struct haxorg_OrgCodeEvalInput;

struct haxorg_OrgCodeEvalInputVar;

struct haxorg_OrgCodeEvalOutput;

struct haxorg_ColumnView;

struct haxorg_ColumnViewSummary;

struct haxorg_ColumnViewSummaryCheckboxAggregate;

struct haxorg_ColumnViewSummaryMathAggregate;

struct haxorg_ColumnViewColumn;

struct haxorg_BlockCodeLine;

struct haxorg_BlockCodeLinePart;

struct haxorg_BlockCodeLinePartRaw;

struct haxorg_BlockCodeLinePartCallout;

struct haxorg_BlockCodeLinePartTangle;

struct haxorg_DocumentExportConfig;

struct haxorg_DocumentExportConfigTaskExport;

struct haxorg_DocumentExportConfigDoExport;

struct haxorg_DocumentExportConfigExportFixed;

struct haxorg_SubtreePeriod;

struct haxorg_NamedProperty;

struct haxorg_NamedPropertyNonblocking;

struct haxorg_NamedPropertyArchiveTime;

struct haxorg_NamedPropertyArchiveFile;

struct haxorg_NamedPropertyArchiveOlpath;

struct haxorg_NamedPropertyArchiveTarget;

struct haxorg_NamedPropertyArchiveCategory;

struct haxorg_NamedPropertyArchiveTodo;

struct haxorg_NamedPropertyTrigger;

struct haxorg_NamedPropertyExportLatexClass;

struct haxorg_NamedPropertyCookieData;

struct haxorg_NamedPropertyExportLatexClassOptions;

struct haxorg_NamedPropertyExportLatexHeader;

struct haxorg_NamedPropertyExportLatexCompiler;

struct haxorg_NamedPropertyOrdered;

struct haxorg_NamedPropertyEffort;

struct haxorg_NamedPropertyVisibility;

struct haxorg_NamedPropertyExportOptions;

struct haxorg_NamedPropertyBlocker;

struct haxorg_NamedPropertyUnnumbered;

struct haxorg_NamedPropertyCreated;

struct haxorg_NamedPropertyRadioId;

struct haxorg_NamedPropertyHashtagDef;

struct haxorg_NamedPropertyCustomArgs;

struct haxorg_NamedPropertyCustomRaw;

struct haxorg_NamedPropertyCustomId;

struct haxorg_NamedPropertyCustomSubtreeJson;

struct haxorg_NamedPropertyCustomSubtreeFlags;

struct haxorg_OrgDiagnostics;

struct haxorg_OrgDiagnosticsParseTokenError;

struct haxorg_OrgDiagnosticsParseError;

struct haxorg_OrgDiagnosticsIncludeError;

struct haxorg_OrgDiagnosticsConvertError;

struct haxorg_OrgDiagnosticsInternalError;

struct haxorg_NoNode;

struct haxorg_ErrorItem;

struct haxorg_ErrorGroup;

struct haxorg_Stmt;

struct haxorg_Inline;

struct haxorg_StmtList;

struct haxorg_Empty;

struct haxorg_Leaf;

struct haxorg_Time;

struct haxorg_TimeRepeat;

struct haxorg_TimeStatic;

struct haxorg_TimeDynamic;

struct haxorg_TimeRange;

struct haxorg_Macro;

struct haxorg_Symbol;

struct haxorg_SymbolParam;

struct haxorg_ErrorSkipGroup;

struct haxorg_Markup;

struct haxorg_RadioTarget;

struct haxorg_Latex;

struct haxorg_SubtreeLog;

struct haxorg_Subtree;

struct haxorg_ColonExample;

struct haxorg_Call;

struct haxorg_ListItem;

struct haxorg_DocumentOptions;

struct haxorg_DocumentFragment;

struct haxorg_CriticMarkup;

struct haxorg_Document;

struct haxorg_FileTarget;

struct haxorg_TextSeparator;

struct haxorg_DocumentGroup;

struct haxorg_File;

struct haxorg_FileDocument;

struct haxorg_FileAttachment;

struct haxorg_FileSource;

struct haxorg_Directory;

struct haxorg_Symlink;

struct haxorg_CmdInclude;

struct haxorg_CmdIncludeIncludeBase;

struct haxorg_CmdIncludeExample;

struct haxorg_CmdIncludeExport;

struct haxorg_CmdIncludeCustom;

struct haxorg_CmdIncludeSrc;

struct haxorg_CmdIncludeOrgDocument;

struct haxorg_ImmNoNode;

struct haxorg_ImmErrorItem;

struct haxorg_ImmErrorGroup;

struct haxorg_ImmStmt;

struct haxorg_ImmInline;

struct haxorg_ImmStmtList;

struct haxorg_ImmEmpty;

struct haxorg_ImmLeaf;

struct haxorg_ImmTime;

struct haxorg_ImmTimeRepeat;

struct haxorg_ImmTimeStatic;

struct haxorg_ImmTimeDynamic;

struct haxorg_ImmTimeRange;

struct haxorg_ImmMacro;

struct haxorg_ImmSymbol;

struct haxorg_ImmSymbolParam;

struct haxorg_ImmErrorSkipGroup;

struct haxorg_ImmMarkup;

struct haxorg_ImmRadioTarget;

struct haxorg_ImmLatex;

struct haxorg_ImmSubtreeLog;

struct haxorg_ImmSubtree;

struct haxorg_ImmColonExample;

struct haxorg_ImmCall;

struct haxorg_ImmListItem;

struct haxorg_ImmDocumentOptions;

struct haxorg_ImmDocumentFragment;

struct haxorg_ImmCriticMarkup;

struct haxorg_ImmDocument;

struct haxorg_ImmFileTarget;

struct haxorg_ImmTextSeparator;

struct haxorg_ImmDocumentGroup;

struct haxorg_ImmFile;

struct haxorg_ImmFileDocument;

struct haxorg_ImmFileAttachment;

struct haxorg_ImmFileSource;

struct haxorg_ImmDirectory;

struct haxorg_ImmSymlink;

struct haxorg_ImmCmdInclude;

struct haxorg_ImmCmdIncludeIncludeBase;

struct haxorg_ImmCmdIncludeExample;

struct haxorg_ImmCmdIncludeExport;

struct haxorg_ImmCmdIncludeCustom;

struct haxorg_ImmCmdIncludeSrc;

struct haxorg_ImmCmdIncludeOrgDocument;

struct haxorg_ImmAdapterOrgAPI;

struct haxorg_Cmd;

struct haxorg_CmdCustomRaw;

struct haxorg_CmdCustomText;

struct haxorg_Link;

struct haxorg_BlockComment;

struct haxorg_Paragraph;

struct haxorg_List;

struct haxorg_HashTag;

struct haxorg_InlineFootnote;

struct haxorg_InlineExport;

struct haxorg_Escaped;

struct haxorg_Newline;

struct haxorg_Space;

struct haxorg_Word;

struct haxorg_AtMention;

struct haxorg_RawText;

struct haxorg_Punctuation;

struct haxorg_Placeholder;

struct haxorg_BigIdent;

struct haxorg_TextTarget;

struct haxorg_ErrorSkipToken;

struct haxorg_Bold;

struct haxorg_Underline;

struct haxorg_Monospace;

struct haxorg_MarkQuote;

struct haxorg_Verbatim;

struct haxorg_Italic;

struct haxorg_Strike;

struct haxorg_Par;

struct haxorg_ImmCmd;

struct haxorg_ImmCmdCustomRaw;

struct haxorg_ImmCmdCustomText;

struct haxorg_ImmLink;

struct haxorg_ImmBlockComment;

struct haxorg_ImmParagraph;

struct haxorg_ImmList;

struct haxorg_ImmHashTag;

struct haxorg_ImmInlineFootnote;

struct haxorg_ImmInlineExport;

struct haxorg_ImmEscaped;

struct haxorg_ImmNewline;

struct haxorg_ImmSpace;

struct haxorg_ImmWord;

struct haxorg_ImmAtMention;

struct haxorg_ImmRawText;

struct haxorg_ImmPunctuation;

struct haxorg_ImmPlaceholder;

struct haxorg_ImmBigIdent;

struct haxorg_ImmTextTarget;

struct haxorg_ImmErrorSkipToken;

struct haxorg_ImmBold;

struct haxorg_ImmUnderline;

struct haxorg_ImmMonospace;

struct haxorg_ImmMarkQuote;

struct haxorg_ImmVerbatim;

struct haxorg_ImmItalic;

struct haxorg_ImmStrike;

struct haxorg_ImmPar;

struct haxorg_ImmAdapterStmtAPI;

struct haxorg_ImmAdapterSubtreeAPI;

struct haxorg_ImmAdapterNoNodeAPI;

struct haxorg_ImmAdapterAttrAPI;

struct haxorg_ImmAdapterAttrListAPI;

struct haxorg_ImmAdapterAttrsAPI;

struct haxorg_ImmAdapterErrorItemAPI;

struct haxorg_ImmAdapterErrorGroupAPI;

struct haxorg_ImmAdapterErrorSkipGroupAPI;

struct haxorg_ImmAdapterErrorSkipTokenAPI;

struct haxorg_ImmAdapterStmtListAPI;

struct haxorg_ImmAdapterEmptyAPI;

struct haxorg_ImmAdapterInlineAPI;

struct haxorg_ImmAdapterTimeAPI;

struct haxorg_ImmAdapterTimeRangeAPI;

struct haxorg_ImmAdapterMacroAPI;

struct haxorg_ImmAdapterSymbolAPI;

struct haxorg_ImmAdapterLeafAPI;

struct haxorg_ImmAdapterMarkupAPI;

struct haxorg_ImmAdapterLatexAPI;

struct haxorg_ImmAdapterSubtreeLogAPI;

struct haxorg_ImmAdapterColonExampleAPI;

struct haxorg_ImmAdapterCallAPI;

struct haxorg_ImmAdapterFileAPI;

struct haxorg_ImmAdapterDirectoryAPI;

struct haxorg_ImmAdapterSymlinkAPI;

struct haxorg_ImmAdapterDocumentFragmentAPI;

struct haxorg_ImmAdapterCriticMarkupAPI;

struct haxorg_ImmAdapterListItemAPI;

struct haxorg_ImmAdapterDocumentOptionsAPI;

struct haxorg_ImmAdapterDocumentAPI;

struct haxorg_ImmAdapterFileTargetAPI;

struct haxorg_ImmAdapterTextSeparatorAPI;

struct haxorg_ImmAdapterCmdIncludeAPI;

struct haxorg_ImmAdapterDocumentGroupAPI;

struct haxorg_Block;

struct haxorg_LineCommand;

struct haxorg_CmdCreator;

struct haxorg_CmdAuthor;

struct haxorg_CmdEmail;

struct haxorg_CmdLanguage;

struct haxorg_CmdCustomArgs;

struct haxorg_CmdTblfm;

struct haxorg_Cell;

struct haxorg_Row;

struct haxorg_ImmBlock;

struct haxorg_ImmLineCommand;

struct haxorg_ImmCmdCreator;

struct haxorg_ImmCmdAuthor;

struct haxorg_ImmCmdEmail;

struct haxorg_ImmCmdLanguage;

struct haxorg_ImmCmdCustomArgs;

struct haxorg_ImmCmdTblfm;

struct haxorg_ImmCell;

struct haxorg_ImmRow;

struct haxorg_ImmAdapterCmdAPI;

struct haxorg_ImmAdapterCmdCustomRawAPI;

struct haxorg_ImmAdapterCmdCustomTextAPI;

struct haxorg_ImmAdapterLinkAPI;

struct haxorg_ImmAdapterBlockCommentAPI;

struct haxorg_ImmAdapterParagraphAPI;

struct haxorg_ImmAdapterListAPI;

struct haxorg_ImmStmtAdapter;

struct haxorg_ImmSubtreeAdapter;

struct haxorg_ImmNoNodeAdapter;

struct haxorg_ImmErrorItemAdapter;

struct haxorg_ImmErrorGroupAdapter;

struct haxorg_ImmErrorSkipGroupAdapter;

struct haxorg_ImmErrorSkipTokenAdapter;

struct haxorg_ImmStmtListAdapter;

struct haxorg_ImmEmptyAdapter;

struct haxorg_ImmAdapterHashTagAPI;

struct haxorg_ImmAdapterInlineFootnoteAPI;

struct haxorg_ImmAdapterSubtreeCompletionAPI;

struct haxorg_ImmInlineAdapter;

struct haxorg_ImmTimeAdapter;

struct haxorg_ImmTimeRangeAdapter;

struct haxorg_ImmMacroAdapter;

struct haxorg_ImmSymbolAdapter;

struct haxorg_ImmAdapterEscapedAPI;

struct haxorg_ImmAdapterNewlineAPI;

struct haxorg_ImmAdapterSpaceAPI;

struct haxorg_ImmAdapterWordAPI;

struct haxorg_ImmAdapterAtMentionAPI;

struct haxorg_ImmAdapterRawTextAPI;

struct haxorg_ImmAdapterPunctuationAPI;

struct haxorg_ImmAdapterPlaceholderAPI;

struct haxorg_ImmAdapterBigIdentAPI;

struct haxorg_ImmAdapterTextTargetAPI;

struct haxorg_ImmLeafAdapter;

struct haxorg_ImmAdapterBoldAPI;

struct haxorg_ImmAdapterUnderlineAPI;

struct haxorg_ImmAdapterMonospaceAPI;

struct haxorg_ImmAdapterMarkQuoteAPI;

struct haxorg_ImmAdapterRadioTargetAPI;

struct haxorg_ImmAdapterVerbatimAPI;

struct haxorg_ImmAdapterItalicAPI;

struct haxorg_ImmAdapterStrikeAPI;

struct haxorg_ImmAdapterParAPI;

struct haxorg_ImmMarkupAdapter;

struct haxorg_ImmLatexAdapter;

struct haxorg_ImmSubtreeLogAdapter;

struct haxorg_ImmColonExampleAdapter;

struct haxorg_ImmCallAdapter;

struct haxorg_ImmFileAdapter;

struct haxorg_ImmDirectoryAdapter;

struct haxorg_ImmSymlinkAdapter;

struct haxorg_ImmDocumentFragmentAdapter;

struct haxorg_ImmCriticMarkupAdapter;

struct haxorg_ImmListItemAdapter;

struct haxorg_ImmDocumentOptionsAdapter;

struct haxorg_ImmDocumentAdapter;

struct haxorg_ImmFileTargetAdapter;

struct haxorg_ImmTextSeparatorAdapter;

struct haxorg_ImmCmdIncludeAdapter;

struct haxorg_ImmDocumentGroupAdapter;

struct haxorg_BlockCenter;

struct haxorg_BlockQuote;

struct haxorg_BlockVerse;

struct haxorg_BlockDynamicFallback;

struct haxorg_BlockExample;

struct haxorg_BlockExport;

struct haxorg_BlockAdmonition;

struct haxorg_BlockCodeEvalResult;

struct haxorg_BlockCode;

struct haxorg_Table;

struct haxorg_Attached;

struct haxorg_ImmBlockCenter;

struct haxorg_ImmBlockQuote;

struct haxorg_ImmBlockVerse;

struct haxorg_ImmBlockDynamicFallback;

struct haxorg_ImmBlockExample;

struct haxorg_ImmBlockExport;

struct haxorg_ImmBlockAdmonition;

struct haxorg_ImmBlockCodeEvalResult;

struct haxorg_ImmBlockCode;

struct haxorg_ImmTable;

struct haxorg_ImmAttached;

struct haxorg_ImmAdapterLineCommandAPI;

struct haxorg_ImmAdapterCmdCustomArgsAPI;

struct haxorg_ImmAdapterCmdCreatorAPI;

struct haxorg_ImmAdapterCmdAuthorAPI;

struct haxorg_ImmAdapterCmdEmailAPI;

struct haxorg_ImmAdapterCmdLanguageAPI;

struct haxorg_ImmAdapterCmdTblfmAPI;

struct haxorg_ImmAdapterBlockAPI;

struct haxorg_ImmAdapterCellAPI;

struct haxorg_ImmAdapterRowAPI;

struct haxorg_ImmCmdAdapter;

struct haxorg_ImmCmdCustomRawAdapter;

struct haxorg_ImmCmdCustomTextAdapter;

struct haxorg_ImmLinkAdapter;

struct haxorg_ImmBlockCommentAdapter;

struct haxorg_ImmParagraphAdapter;

struct haxorg_ImmListAdapter;

struct haxorg_ImmHashTagAdapter;

struct haxorg_ImmInlineFootnoteAdapter;

struct haxorg_ImmEscapedAdapter;

struct haxorg_ImmNewlineAdapter;

struct haxorg_ImmSpaceAdapter;

struct haxorg_ImmWordAdapter;

struct haxorg_ImmAtMentionAdapter;

struct haxorg_ImmRawTextAdapter;

struct haxorg_ImmPunctuationAdapter;

struct haxorg_ImmPlaceholderAdapter;

struct haxorg_ImmBigIdentAdapter;

struct haxorg_ImmTextTargetAdapter;

struct haxorg_ImmBoldAdapter;

struct haxorg_ImmUnderlineAdapter;

struct haxorg_ImmMonospaceAdapter;

struct haxorg_ImmMarkQuoteAdapter;

struct haxorg_ImmRadioTargetAdapter;

struct haxorg_ImmVerbatimAdapter;

struct haxorg_ImmItalicAdapter;

struct haxorg_ImmStrikeAdapter;

struct haxorg_ImmParAdapter;

struct haxorg_CmdCaption;

struct haxorg_CmdColumns;

struct haxorg_CmdName;

struct haxorg_CmdCall;

struct haxorg_CmdAttr;

struct haxorg_CmdExport;

struct haxorg_ImmCmdCaption;

struct haxorg_ImmCmdColumns;

struct haxorg_ImmCmdName;

struct haxorg_ImmCmdCall;

struct haxorg_ImmCmdAttr;

struct haxorg_ImmCmdExport;

struct haxorg_ImmAdapterAttachedAPI;

struct haxorg_ImmLineCommandAdapter;

struct haxorg_ImmCmdCustomArgsAdapter;

struct haxorg_ImmCmdCreatorAdapter;

struct haxorg_ImmCmdAuthorAdapter;

struct haxorg_ImmCmdEmailAdapter;

struct haxorg_ImmCmdLanguageAdapter;

struct haxorg_ImmCmdTblfmAdapter;

struct haxorg_ImmAdapterBlockCenterAPI;

struct haxorg_ImmAdapterBlockQuoteAPI;

struct haxorg_ImmAdapterBlockVerseAPI;

struct haxorg_ImmAdapterBlockExampleAPI;

struct haxorg_ImmAdapterInlineExportAPI;

struct haxorg_ImmAdapterCmdExportAPI;

struct haxorg_ImmAdapterBlockExportAPI;

struct haxorg_ImmAdapterBlockDynamicFallbackAPI;

struct haxorg_ImmAdapterBlockAdmonitionAPI;

struct haxorg_ImmAdapterBlockCodeEvalResultAPI;

struct haxorg_ImmAdapterBlockCodeAPI;

struct haxorg_ImmAdapterTableAPI;

struct haxorg_ImmBlockAdapter;

struct haxorg_ImmCellAdapter;

struct haxorg_ImmRowAdapter;

struct haxorg_ImmAdapterCmdCaptionAPI;

struct haxorg_ImmAdapterCmdColumnsAPI;

struct haxorg_ImmAdapterCmdNameAPI;

struct haxorg_ImmAdapterCmdCallAPI;

struct haxorg_ImmAdapterCmdResultsAPI;

struct haxorg_ImmAdapterCmdAttrAPI;

struct haxorg_ImmAttachedAdapter;

struct haxorg_ImmBlockCenterAdapter;

struct haxorg_ImmBlockQuoteAdapter;

struct haxorg_ImmBlockVerseAdapter;

struct haxorg_ImmBlockExampleAdapter;

struct haxorg_ImmInlineExportAdapter;

struct haxorg_ImmCmdExportAdapter;

struct haxorg_ImmBlockExportAdapter;

struct haxorg_ImmBlockDynamicFallbackAdapter;

struct haxorg_ImmBlockAdmonitionAdapter;

struct haxorg_ImmBlockCodeEvalResultAdapter;

struct haxorg_ImmBlockCodeAdapter;

struct haxorg_ImmTableAdapter;

struct haxorg_ImmCmdCaptionAdapter;

struct haxorg_ImmCmdColumnsAdapter;

struct haxorg_ImmCmdNameAdapter;

struct haxorg_ImmCmdCallAdapter;

struct haxorg_ImmCmdAttrAdapter;

enum class haxorg_LispCodeKind : short int { Call, List, KeyValue, Number, Text, Ident, Boolean, Real, };
enum class haxorg_TblfmExprAxisRefPositionKind : short int { Index, Name, };
enum class haxorg_TblfmExprKind : short int { AxisRef, AxisName, IntLiteral, FloatLiteral, RangeRef, Call, Elisp, };
/// \brief Flags for table format expression cell formulas
enum class haxorg_TblfmAssignFlag : short int {
  /// \brief Left-align the result
  CellLeftAlign,
  /// \brief Right-align the result
  CellRightAlign,
  /// \brief Center-align the result
  CellCenterAlign,
  /// \brief Convert result to number/currency format
  CellNumber,
  /// \brief Use exponential notation for numbers
  CellExponential,
  /// \brief Use floating point format
  CellFloating,
  /// \brief Unformat values before calculating
  CellUnformat,
  /// \brief Convert result to text
  CellText,
  /// \brief Display boolean values as t/nil
  CellBool,
  /// \brief Fixed format with specified decimal places (e.g., ;D2)
  CellDecimal,
  /// \brief Percentage format
  CellPercentage,
  /// \brief Convert to hours/minutes (HH:MM)
  CellHours,
  /// \brief Display zero as empty cell
  CellZero,
  /// \brief Mark field as invalid if conversion fails
  CellMarkInvalid,
  /// \brief Quote field contents
  CellQuote,
};
enum class haxorg_AttrValueKind : short int { TextValue, FileReference, LispValue, };
enum class haxorg_TodoKeywordTransition : short int { None, NoteWithTimestamp, Timestamp, };
enum class haxorg_LinkTargetKind : short int { Raw, Id, CustomId, SubtreeTitle, Person, UserProtocol, Internal, Footnote, File, Attachment, };
/// \brief Priority change action
enum class haxorg_SubtreeLogHeadPriorityAction : short int {
  /// \brief `Priority B added on [timestamp]`
  Added,
  /// \brief `Priority C removed on [timestamp]`
  Removed,
  /// \brief `Priority B changed from C on [timestamp]`
  Changed,
};
enum class haxorg_SubtreeLogHeadKind : short int { Priority, Note, Refile, Clock, State, Deadline, Schedule, Tag, Unknown, };
/// \brief What context to use for results
enum class haxorg_OrgCodeEvalInputResultType : short int {
  None,
  /// \brief Interpret the results as an Org table. If the result is a single value, create a table with one row and one column.
  Table,
  /// \brief Interpret the results as an Org list. If the result is a single value, create a list of one element.
  List,
  /// \brief Interpret literally and insert as quoted text. Do not create a table.
  Scalar,
  /// \brief Interpret as a filename. Save the results of execution of the code block to that file, then insert a link to it.
  SaveFile,
};
/// \brief How to interpret output from the script
enum class haxorg_OrgCodeEvalInputResultFormat : short int {
  None,
  /// \brief Interpreted as raw Org mode. Inserted directly into the buffer.
  Raw,
  /// \brief Result enclosed in a code block.
  Code,
  /// \brief Results are added directly to the Org file as with ‘raw’, but are wrapped in a ‘RESULTS’ drawer or results macro (for inline code blocks), for later scripting and automated processing.
  Drawer,
  /// \brief Results enclosed in a ‘BEGIN_EXPORT’ block.
  ExportType,
  Link,
};
/// \brief What to do with the final evaluation results
enum class haxorg_OrgCodeEvalInputResultHandling : short int { None, Replace, Silent, Discard, Append, Prepend, };
enum class haxorg_ColumnViewSummaryCheckboxAggregateKind : short int { IfAllNested, AggregateFractionRec, AggregatePercentRec, };
enum class haxorg_ColumnViewSummaryMathAggregateKind : short int { Min, Max, Mean, Sum, LowHighEst, };
enum class haxorg_ColumnViewSummaryKind : short int { CheckboxAggregate, MathAggregate, };
enum class haxorg_BlockCodeLinePartKind : short int { Raw, Callout, Tangle, };
enum class haxorg_DocumentExportConfigTagExport : short int {
  None,
  All,
  /// \brief Export tags in subtree titles but not in the table of content
  NotInToc,
};
enum class haxorg_DocumentExportConfigTaskFiltering : short int {
  /// \brief Include tasks from the whitelist
  Whitelist,
  /// \brief Include tasks marked as done
  Done,
  /// \brief Exclude all task subtrees from export
  None,
  /// \brief Add all task subtrees to export
  All,
};
enum class haxorg_DocumentExportConfigBrokenLinks : short int { None, Mark, Raise, Ignore, };
/// \brief Configure how archived trees are exported
enum class haxorg_DocumentExportConfigArchivedTrees : short int {
  /// \brief Skip archived trees entirely
  Skip,
  /// \brief Export only headlines of archived trees
  Headline,
  /// \brief Export archived trees with full content
  All,
};
enum class haxorg_DocumentExportConfigTocExportKind : short int { DoExport, ExportFixed, };
/// \brief Period kind
enum class haxorg_SubtreePeriodKind : short int {
  /// \brief Time period of the task execution.
  Clocked,
  /// \brief Task marked as closed
  Closed,
  /// \brief Date of task execution start plus it's estimated effort duration. If the latter one is missing then only a single time point is returned
  Scheduled,
  /// \brief Single point or time range used in title. Single point can also be a simple time, such as `12:20`
  Titled,
  /// \brief Date of task completion. Must be a single time point
  Deadline,
  /// \brief When the subtree was created
  Created,
  /// \brief Last repeat time of the recurring tasks
  Repeated,
};
enum class haxorg_NamedPropertyVisibilityLevel : short int { Folded, Children, Content, All, };
enum class haxorg_NamedPropertyKind : short int { Nonblocking, ArchiveTime, ArchiveFile, ArchiveOlpath, ArchiveTarget, ArchiveCategory, ArchiveTodo, Trigger, ExportLatexClass, CookieData, ExportLatexClassOptions, ExportLatexHeader, ExportLatexCompiler, Ordered, Effort, Visibility, ExportOptions, Blocker, Unnumbered, Created, RadioId, HashtagDef, CustomArgs, CustomRaw, CustomId, CustomSubtreeJson, CustomSubtreeFlags, };
enum class haxorg_OrgDiagnosticsKind : short int { ParseTokenError, ParseError, IncludeError, ConvertError, InternalError, };
/// \brief Timestamp repetition mode
enum class haxorg_TimeRepeatMode : short int {
  /// \brief Do not repeat task on completion
  None,
  /// \brief ?
  Exact,
  /// \brief Repeat on the first matching day in the future
  FirstMatch,
  /// \brief Repeat task on the same day next week/month/year
  SameDay,
};
/// \brief Repetition period. Temporary placeholder for now, until I figure out what would be the proper way to represent whatever org can do ... which is to be determined as well
enum class haxorg_TimeRepeatPeriod : short int { Year, Month, Week, Day, Hour, Minute, };
enum class haxorg_TimeTimeKind : short int { Static, Dynamic, };
enum class haxorg_CriticMarkupKind : short int { Deletion, Addition, Substitution, Highlighting, Comment, };
enum class haxorg_FileKind : short int { Document, Attachment, Source, };
enum class haxorg_CmdIncludeKind : short int { Example, Export, Custom, Src, OrgDocument, };
enum class haxorg_ImmTimeTimeKind : short int { Static, Dynamic, };
enum class haxorg_ImmFileKind : short int { Document, Attachment, Source, };
enum class haxorg_ImmCmdIncludeKind : short int { Example, Export, Custom, Src, OrgDocument, };
/// \brief ['org', 'sem', 'SemId', [['org', 'sem', 'Org']]]
struct haxorg_SemIdOfOrg {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'sem', 'OrgJson']]]
struct haxorg_HstdVecOfOrgJson {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'sem', 'SemId', [['org', 'sem', 'Org']]]]]
struct haxorg_HstdVecOfSemIdOfOrg {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['hstd', 'ext', 'Report']]]
struct haxorg_HstdVecOfReport {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'sem', 'SemId', [['org', 'sem', 'ErrorGroup']]]]]
struct haxorg_HstdVecOfSemIdOfErrorGroup {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['int']]]
struct haxorg_HstdVecOfInt {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'imm', 'ImmAdapter']]]
struct haxorg_HstdVecOfImmAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['hstd', 'SequenceSegment']]]
struct haxorg_HstdVecOfSequenceSegment {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['hstd', 'SequenceAnnotationTag']]]
struct haxorg_HstdVecOfSequenceAnnotationTag {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'imm', 'ImmUniqId']]]
struct haxorg_HstdVecOfImmUniqId {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'graph', 'MapLink']]]
struct haxorg_HstdVecOfGraphMapLink {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'graph', 'MapNode']]]
struct haxorg_HstdVecOfGraphMapNode {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'graph', 'MapEdge']]]
struct haxorg_HstdVecOfGraphMapEdge {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'sem', 'LispCode']]]
struct haxorg_HstdVecOfLispCode {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'sem', 'Tblfm', 'Assign']]]
struct haxorg_HstdVecOfTblfmAssign {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'sem', 'Tblfm', 'Expr']]]
struct haxorg_HstdVecOfTblfmExpr {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'sem', 'Tblfm', 'Assign', 'Flag']]]
struct haxorg_HstdVecOfTblfmAssignFlag {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'sem', 'AttrValue', 'DimensionSpan']]]
struct haxorg_HstdVecOfAttrValueDimensionSpan {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['hstd', 'Str']]]
struct haxorg_HstdVecOfStr {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'sem', 'HashTagFlat']]]
struct haxorg_HstdVecOfHashTagFlat {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'sem', 'HashTagText']]]
struct haxorg_HstdVecOfHashTagText {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'sem', 'AttrValue']]]
struct haxorg_HstdVecOfAttrValue {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'sem', 'OrgCodeEvalInput', 'Var']]]
struct haxorg_HstdVecOfOrgCodeEvalInputVar {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'sem', 'ColumnView', 'Column']]]
struct haxorg_HstdVecOfColumnViewColumn {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'sem', 'BlockCodeLine', 'Part']]]
struct haxorg_HstdVecOfBlockCodeLinePart {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'sem', 'SemId', [['org', 'sem', 'ErrorItem']]]]]
struct haxorg_HstdVecOfSemIdOfErrorItem {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'sem', 'Time', 'Repeat']]]
struct haxorg_HstdVecOfTimeRepeat {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'sem', 'Symbol', 'Param']]]
struct haxorg_HstdVecOfSymbolParam {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'sem', 'SemId', [['org', 'sem', 'ErrorSkipToken']]]]]
struct haxorg_HstdVecOfSemIdOfErrorSkipToken {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'sem', 'SubtreePeriod']]]
struct haxorg_HstdVecOfSubtreePeriod {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'sem', 'NamedProperty']]]
struct haxorg_HstdVecOfNamedProperty {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'sem', 'SemId', [['org', 'sem', 'HashTag']]]]]
struct haxorg_HstdVecOfSemIdOfHashTag {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'sem', 'SemId', [['org', 'sem', 'SubtreeLog']]]]]
struct haxorg_HstdVecOfSemIdOfSubtreeLog {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'sem', 'TodoKeyword']]]
struct haxorg_HstdVecOfTodoKeyword {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'sem', 'SemId', [['org', 'sem', 'BigIdent']]]]]
struct haxorg_HstdVecOfSemIdOfBigIdent {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['hstd', 'UserTime']]]
struct haxorg_HstdVecOfUserTime {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'sem', 'SemId', [['org', 'sem', 'Time']]]]]
struct haxorg_HstdVecOfSemIdOfTime {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'sem', 'SemId', [['org', 'sem', 'Cell']]]]]
struct haxorg_HstdVecOfSemIdOfCell {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'sem', 'OrgCodeEvalOutput']]]
struct haxorg_HstdVecOfOrgCodeEvalOutput {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'sem', 'SemId', [['org', 'sem', 'BlockCodeEvalResult']]]]]
struct haxorg_HstdVecOfSemIdOfBlockCodeEvalResult {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'sem', 'BlockCodeLine']]]
struct haxorg_HstdVecOfBlockCodeLine {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'sem', 'SemId', [['org', 'sem', 'Row']]]]]
struct haxorg_HstdVecOfSemIdOfRow {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['org', 'AstTrackingGroup']]]
struct haxorg_HstdVecOfAstTrackingGroup {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['hstd', 'SequenceAnnotation']]]
struct haxorg_HstdVecOfSequenceAnnotation {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Vec', [['hstd', 'SequenceSegmentGroup']]]
struct haxorg_HstdVecOfSequenceSegmentGroup {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'UnorderedMap', [['haxorg_ptr_payload']], [['haxorg_ptr_payload']]]
struct haxorg_HstdMap {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'ext', 'ImmMap', [['haxorg_ptr_payload']], [['haxorg_ptr_payload']]]
struct haxorg_ImmMap {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'BackwardsIndex']
struct haxorg_BackwardsIndex {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'Str']
struct haxorg_HstdStr {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'UserTimeBreakdown']
struct haxorg_UserTimeBreakdown {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'UserTime']
struct haxorg_UserTime {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'parse', 'SourceFileId']
struct haxorg_ParseSourceFileId {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'parse', 'SourceManager']
struct haxorg_ParseSourceManager {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'parse', 'SourceLoc']
struct haxorg_ParseSourceLoc {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'OrgJson']
struct haxorg_OrgJson {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Org']
struct haxorg_Org {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'OperationsTracer']
struct haxorg_OperationsTracer {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'ext', 'Cache']
struct haxorg_Cache {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'ext', 'Report']
struct haxorg_Report {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'parse', 'OrgParseFragment']
struct haxorg_ParseOrgParseFragment {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'parse', 'OrgParseParameters']
struct haxorg_OrgParseParameters {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'parse', 'OrgDirectoryParseParameters']
struct haxorg_OrgDirectoryParseParameters {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'parse', 'ParseContext']
struct haxorg_ParseContext {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmReflFieldId']
struct haxorg_ImmReflFieldId {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmId']
struct haxorg_ImmId {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmOrg']
struct haxorg_ImmOrg {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmPathStep']
struct haxorg_ImmPathStep {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmPath']
struct haxorg_ImmPath {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmUniqId']
struct haxorg_ImmUniqId {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAstReplaceEpoch']
struct haxorg_ImmAstReplaceEpoch {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAstContext']
struct haxorg_ImmAstContext {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAstVersion']
struct haxorg_ImmAstVersion {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapter', 'TreeReprConf']
struct haxorg_ImmAdapterTreeReprConf {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapter']
struct haxorg_ImmAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterVirtualBase']
struct haxorg_ImmAdapterVirtualBase {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'OrgYamlExportOpts']
struct haxorg_OrgYamlExportOpts {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'OrgTreeExportOpts']
struct haxorg_OrgTreeExportOpts {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'AstTrackingPath']
struct haxorg_AstTrackingPath {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'AstTrackingAlternatives']
struct haxorg_AstTrackingAlternatives {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'AstTrackingGroup', 'RadioTarget']
struct haxorg_AstTrackingGroupRadioTarget {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'AstTrackingGroup', 'Single']
struct haxorg_AstTrackingGroupSingle {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'AstTrackingGroup', 'TrackedHashtag']
struct haxorg_AstTrackingGroupTrackedHashtag {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'AstTrackingGroup']
struct haxorg_AstTrackingGroup {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'AstTrackingMap']
struct haxorg_AstTrackingMap {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'SequenceSegment']
struct haxorg_SequenceSegment {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'SequenceSegmentGroup']
struct haxorg_SequenceSegmentGroup {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'SequenceAnnotationTag']
struct haxorg_SequenceAnnotationTag {
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'SequenceAnnotation']
struct haxorg_SequenceAnnotation {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'graph', 'MapLink', 'Link']
struct haxorg_GraphMapLinkLink {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'graph', 'MapLink', 'Radio']
struct haxorg_GraphMapLinkRadio {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'graph', 'MapLink']
struct haxorg_GraphMapLink {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'graph', 'MapNodeProp']
struct haxorg_GraphMapNodeProp {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'graph', 'MapEdgeProp']
struct haxorg_GraphMapEdgeProp {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'graph', 'MapNode']
struct haxorg_GraphMapNode {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'graph', 'MapEdge']
struct haxorg_GraphMapEdge {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'graph', 'MapGraph']
struct haxorg_GraphMapGraph {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'graph', 'MapConfig']
struct haxorg_GraphMapConfig {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'graph', 'MapGraphState']
struct haxorg_GraphMapGraphState {
  haxorg_ptr_payload data;
};

typedef uint64_t haxorg_ImmIdIdType;
typedef uint32_t haxorg_ImmIdNodeIdxT;
typedef haxorg_immer_flex_vector haxorg_ImmPathStore;
/// \brief ['org', 'sem', 'LispCode', 'Call']
struct haxorg_LispCodeCall {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LispCode', 'List']
struct haxorg_LispCodeList {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LispCode', 'KeyValue']
struct haxorg_LispCodeKeyValue {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LispCode', 'Number']
struct haxorg_LispCodeNumber {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LispCode', 'Text']
struct haxorg_LispCodeText {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LispCode', 'Ident']
struct haxorg_LispCodeIdent {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LispCode', 'Boolean']
struct haxorg_LispCodeBoolean {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LispCode', 'Real']
struct haxorg_LispCodeReal {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LispCode']
struct haxorg_LispCode {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr', 'AxisRef', 'Position', 'Index']
struct haxorg_TblfmExprAxisRefPositionIndex {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr', 'AxisRef', 'Position', 'Name']
struct haxorg_TblfmExprAxisRefPositionName {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr', 'AxisRef', 'Position']
struct haxorg_TblfmExprAxisRefPosition {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr', 'AxisRef']
struct haxorg_TblfmExprAxisRef {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr', 'AxisName']
struct haxorg_TblfmExprAxisName {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr', 'IntLiteral']
struct haxorg_TblfmExprIntLiteral {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr', 'FloatLiteral']
struct haxorg_TblfmExprFloatLiteral {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr', 'RangeRef']
struct haxorg_TblfmExprRangeRef {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr', 'Call']
struct haxorg_TblfmExprCall {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr', 'Elisp']
struct haxorg_TblfmExprElisp {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr']
struct haxorg_TblfmExpr {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Assign']
struct haxorg_TblfmAssign {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm']
struct haxorg_Tblfm {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'AttrValue', 'DimensionSpan']
struct haxorg_AttrValueDimensionSpan {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'AttrValue', 'TextValue']
struct haxorg_AttrValueTextValue {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'AttrValue', 'FileReference']
struct haxorg_AttrValueFileReference {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'AttrValue', 'LispValue']
struct haxorg_AttrValueLispValue {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'AttrValue']
struct haxorg_AttrValue {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'HashTagFlat']
struct haxorg_HashTagFlat {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'TodoKeyword']
struct haxorg_TodoKeyword {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'HashTagText']
struct haxorg_HashTagText {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreePath']
struct haxorg_SubtreePath {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget', 'Raw']
struct haxorg_LinkTargetRaw {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget', 'Id']
struct haxorg_LinkTargetId {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget', 'CustomId']
struct haxorg_LinkTargetCustomId {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget', 'SubtreeTitle']
struct haxorg_LinkTargetSubtreeTitle {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget', 'Person']
struct haxorg_LinkTargetPerson {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget', 'UserProtocol']
struct haxorg_LinkTargetUserProtocol {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget', 'Internal']
struct haxorg_LinkTargetInternal {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget', 'Footnote']
struct haxorg_LinkTargetFootnote {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget', 'File']
struct haxorg_LinkTargetFile {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget', 'Attachment']
struct haxorg_LinkTargetAttachment {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget']
struct haxorg_LinkTarget {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLogHead', 'Priority']
struct haxorg_SubtreeLogHeadPriority {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLogHead', 'Note']
struct haxorg_SubtreeLogHeadNote {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLogHead', 'Refile']
struct haxorg_SubtreeLogHeadRefile {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLogHead', 'Clock']
struct haxorg_SubtreeLogHeadClock {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLogHead', 'State']
struct haxorg_SubtreeLogHeadState {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLogHead', 'Deadline']
struct haxorg_SubtreeLogHeadDeadline {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLogHead', 'Schedule']
struct haxorg_SubtreeLogHeadSchedule {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLogHead', 'Tag']
struct haxorg_SubtreeLogHeadTag {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLogHead', 'Unknown']
struct haxorg_SubtreeLogHeadUnknown {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLogHead']
struct haxorg_SubtreeLogHead {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeCompletion']
struct haxorg_SubtreeCompletion {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'AttrList']
struct haxorg_AttrList {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'AttrGroup']
struct haxorg_AttrGroup {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'OrgCodeEvalInput', 'Var']
struct haxorg_OrgCodeEvalInputVar {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'OrgCodeEvalInput']
struct haxorg_OrgCodeEvalInput {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'OrgCodeEvalOutput']
struct haxorg_OrgCodeEvalOutput {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'ColumnView', 'Summary', 'CheckboxAggregate']
struct haxorg_ColumnViewSummaryCheckboxAggregate {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'ColumnView', 'Summary', 'MathAggregate']
struct haxorg_ColumnViewSummaryMathAggregate {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'ColumnView', 'Summary']
struct haxorg_ColumnViewSummary {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'ColumnView', 'Column']
struct haxorg_ColumnViewColumn {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'ColumnView']
struct haxorg_ColumnView {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockCodeLine', 'Part', 'Raw']
struct haxorg_BlockCodeLinePartRaw {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockCodeLine', 'Part', 'Callout']
struct haxorg_BlockCodeLinePartCallout {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockCodeLine', 'Part', 'Tangle']
struct haxorg_BlockCodeLinePartTangle {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockCodeLine', 'Part']
struct haxorg_BlockCodeLinePart {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockCodeLine']
struct haxorg_BlockCodeLine {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'DocumentExportConfig', 'TaskExport']
struct haxorg_DocumentExportConfigTaskExport {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'DocumentExportConfig', 'DoExport']
struct haxorg_DocumentExportConfigDoExport {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'DocumentExportConfig', 'ExportFixed']
struct haxorg_DocumentExportConfigExportFixed {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'DocumentExportConfig']
struct haxorg_DocumentExportConfig {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreePeriod']
struct haxorg_SubtreePeriod {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'Nonblocking']
struct haxorg_NamedPropertyNonblocking {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ArchiveTime']
struct haxorg_NamedPropertyArchiveTime {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ArchiveFile']
struct haxorg_NamedPropertyArchiveFile {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ArchiveOlpath']
struct haxorg_NamedPropertyArchiveOlpath {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ArchiveTarget']
struct haxorg_NamedPropertyArchiveTarget {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ArchiveCategory']
struct haxorg_NamedPropertyArchiveCategory {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ArchiveTodo']
struct haxorg_NamedPropertyArchiveTodo {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'Trigger']
struct haxorg_NamedPropertyTrigger {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ExportLatexClass']
struct haxorg_NamedPropertyExportLatexClass {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'CookieData']
struct haxorg_NamedPropertyCookieData {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ExportLatexClassOptions']
struct haxorg_NamedPropertyExportLatexClassOptions {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ExportLatexHeader']
struct haxorg_NamedPropertyExportLatexHeader {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ExportLatexCompiler']
struct haxorg_NamedPropertyExportLatexCompiler {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'Ordered']
struct haxorg_NamedPropertyOrdered {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'Effort']
struct haxorg_NamedPropertyEffort {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'Visibility']
struct haxorg_NamedPropertyVisibility {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ExportOptions']
struct haxorg_NamedPropertyExportOptions {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'Blocker']
struct haxorg_NamedPropertyBlocker {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'Unnumbered']
struct haxorg_NamedPropertyUnnumbered {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'Created']
struct haxorg_NamedPropertyCreated {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'RadioId']
struct haxorg_NamedPropertyRadioId {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'HashtagDef']
struct haxorg_NamedPropertyHashtagDef {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'CustomArgs']
struct haxorg_NamedPropertyCustomArgs {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'CustomRaw']
struct haxorg_NamedPropertyCustomRaw {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'CustomId']
struct haxorg_NamedPropertyCustomId {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'CustomSubtreeJson']
struct haxorg_NamedPropertyCustomSubtreeJson {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'CustomSubtreeFlags']
struct haxorg_NamedPropertyCustomSubtreeFlags {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty']
struct haxorg_NamedProperty {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'OrgDiagnostics', 'ParseTokenError']
struct haxorg_OrgDiagnosticsParseTokenError {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'OrgDiagnostics', 'ParseError']
struct haxorg_OrgDiagnosticsParseError {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'OrgDiagnostics', 'IncludeError']
struct haxorg_OrgDiagnosticsIncludeError {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'OrgDiagnostics', 'ConvertError']
struct haxorg_OrgDiagnosticsConvertError {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'OrgDiagnostics', 'InternalError']
struct haxorg_OrgDiagnosticsInternalError {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'OrgDiagnostics']
struct haxorg_OrgDiagnostics {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NoNode']
struct haxorg_NoNode {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'ErrorItem']
struct haxorg_ErrorItem {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'ErrorGroup']
struct haxorg_ErrorGroup {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Stmt']
struct haxorg_Stmt {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Inline']
struct haxorg_Inline {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'StmtList']
struct haxorg_StmtList {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Empty']
struct haxorg_Empty {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Leaf']
struct haxorg_Leaf {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Time', 'Repeat']
struct haxorg_TimeRepeat {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Time', 'Static']
struct haxorg_TimeStatic {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Time', 'Dynamic']
struct haxorg_TimeDynamic {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Time']
struct haxorg_Time {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'TimeRange']
struct haxorg_TimeRange {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Macro']
struct haxorg_Macro {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Symbol', 'Param']
struct haxorg_SymbolParam {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Symbol']
struct haxorg_Symbol {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'ErrorSkipGroup']
struct haxorg_ErrorSkipGroup {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Markup']
struct haxorg_Markup {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'RadioTarget']
struct haxorg_RadioTarget {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Latex']
struct haxorg_Latex {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLog']
struct haxorg_SubtreeLog {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Subtree']
struct haxorg_Subtree {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'ColonExample']
struct haxorg_ColonExample {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Call']
struct haxorg_Call {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'ListItem']
struct haxorg_ListItem {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'DocumentOptions']
struct haxorg_DocumentOptions {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'DocumentFragment']
struct haxorg_DocumentFragment {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CriticMarkup']
struct haxorg_CriticMarkup {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Document']
struct haxorg_Document {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'FileTarget']
struct haxorg_FileTarget {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'TextSeparator']
struct haxorg_TextSeparator {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'DocumentGroup']
struct haxorg_DocumentGroup {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'File', 'Document']
struct haxorg_FileDocument {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'File', 'Attachment']
struct haxorg_FileAttachment {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'File', 'Source']
struct haxorg_FileSource {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'File']
struct haxorg_File {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Directory']
struct haxorg_Directory {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Symlink']
struct haxorg_Symlink {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdInclude', 'IncludeBase']
struct haxorg_CmdIncludeIncludeBase {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdInclude', 'Example']
struct haxorg_CmdIncludeExample {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdInclude', 'Export']
struct haxorg_CmdIncludeExport {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdInclude', 'Custom']
struct haxorg_CmdIncludeCustom {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdInclude', 'Src']
struct haxorg_CmdIncludeSrc {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdInclude', 'OrgDocument']
struct haxorg_CmdIncludeOrgDocument {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdInclude']
struct haxorg_CmdInclude {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmNoNode']
struct haxorg_ImmNoNode {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmErrorItem']
struct haxorg_ImmErrorItem {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmErrorGroup']
struct haxorg_ImmErrorGroup {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmStmt']
struct haxorg_ImmStmt {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmInline']
struct haxorg_ImmInline {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmStmtList']
struct haxorg_ImmStmtList {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmEmpty']
struct haxorg_ImmEmpty {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmLeaf']
struct haxorg_ImmLeaf {
  haxorg_ptr_payload data;
};

typedef haxorg_TimeRepeatMode haxorg_ImmTimeRepeatMode;
typedef haxorg_TimeRepeatPeriod haxorg_ImmTimeRepeatPeriod;
/// \brief ['org', 'imm', 'ImmTime', 'Repeat']
struct haxorg_ImmTimeRepeat {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmTime', 'Static']
struct haxorg_ImmTimeStatic {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmTime', 'Dynamic']
struct haxorg_ImmTimeDynamic {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmTime']
struct haxorg_ImmTime {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmTimeRange']
struct haxorg_ImmTimeRange {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmMacro']
struct haxorg_ImmMacro {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmSymbol', 'Param']
struct haxorg_ImmSymbolParam {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmSymbol']
struct haxorg_ImmSymbol {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmErrorSkipGroup']
struct haxorg_ImmErrorSkipGroup {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmMarkup']
struct haxorg_ImmMarkup {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmRadioTarget']
struct haxorg_ImmRadioTarget {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmLatex']
struct haxorg_ImmLatex {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmSubtreeLog']
struct haxorg_ImmSubtreeLog {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmSubtree']
struct haxorg_ImmSubtree {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmColonExample']
struct haxorg_ImmColonExample {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCall']
struct haxorg_ImmCall {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmListItem']
struct haxorg_ImmListItem {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmDocumentOptions']
struct haxorg_ImmDocumentOptions {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmDocumentFragment']
struct haxorg_ImmDocumentFragment {
  haxorg_ptr_payload data;
};

typedef haxorg_CriticMarkupKind haxorg_ImmCriticMarkupKind;
/// \brief ['org', 'imm', 'ImmCriticMarkup']
struct haxorg_ImmCriticMarkup {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmDocument']
struct haxorg_ImmDocument {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmFileTarget']
struct haxorg_ImmFileTarget {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmTextSeparator']
struct haxorg_ImmTextSeparator {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmDocumentGroup']
struct haxorg_ImmDocumentGroup {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmFile', 'Document']
struct haxorg_ImmFileDocument {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmFile', 'Attachment']
struct haxorg_ImmFileAttachment {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmFile', 'Source']
struct haxorg_ImmFileSource {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmFile']
struct haxorg_ImmFile {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmDirectory']
struct haxorg_ImmDirectory {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmSymlink']
struct haxorg_ImmSymlink {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdInclude', 'IncludeBase']
struct haxorg_ImmCmdIncludeIncludeBase {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdInclude', 'Example']
struct haxorg_ImmCmdIncludeExample {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdInclude', 'Export']
struct haxorg_ImmCmdIncludeExport {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdInclude', 'Custom']
struct haxorg_ImmCmdIncludeCustom {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdInclude', 'Src']
struct haxorg_ImmCmdIncludeSrc {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdInclude', 'OrgDocument']
struct haxorg_ImmCmdIncludeOrgDocument {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdInclude']
struct haxorg_ImmCmdInclude {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterOrgAPI']
struct haxorg_ImmAdapterOrgAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Cmd']
struct haxorg_Cmd {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdCustomRaw']
struct haxorg_CmdCustomRaw {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdCustomText']
struct haxorg_CmdCustomText {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Link']
struct haxorg_Link {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockComment']
struct haxorg_BlockComment {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Paragraph']
struct haxorg_Paragraph {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'List']
struct haxorg_List {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'HashTag']
struct haxorg_HashTag {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'InlineFootnote']
struct haxorg_InlineFootnote {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'InlineExport']
struct haxorg_InlineExport {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Escaped']
struct haxorg_Escaped {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Newline']
struct haxorg_Newline {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Space']
struct haxorg_Space {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Word']
struct haxorg_Word {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'AtMention']
struct haxorg_AtMention {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'RawText']
struct haxorg_RawText {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Punctuation']
struct haxorg_Punctuation {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Placeholder']
struct haxorg_Placeholder {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'BigIdent']
struct haxorg_BigIdent {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'TextTarget']
struct haxorg_TextTarget {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'ErrorSkipToken']
struct haxorg_ErrorSkipToken {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Bold']
struct haxorg_Bold {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Underline']
struct haxorg_Underline {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Monospace']
struct haxorg_Monospace {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'MarkQuote']
struct haxorg_MarkQuote {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Verbatim']
struct haxorg_Verbatim {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Italic']
struct haxorg_Italic {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Strike']
struct haxorg_Strike {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Par']
struct haxorg_Par {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmd']
struct haxorg_ImmCmd {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdCustomRaw']
struct haxorg_ImmCmdCustomRaw {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdCustomText']
struct haxorg_ImmCmdCustomText {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmLink']
struct haxorg_ImmLink {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmBlockComment']
struct haxorg_ImmBlockComment {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmParagraph']
struct haxorg_ImmParagraph {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmList']
struct haxorg_ImmList {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmHashTag']
struct haxorg_ImmHashTag {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmInlineFootnote']
struct haxorg_ImmInlineFootnote {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmInlineExport']
struct haxorg_ImmInlineExport {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmEscaped']
struct haxorg_ImmEscaped {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmNewline']
struct haxorg_ImmNewline {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmSpace']
struct haxorg_ImmSpace {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmWord']
struct haxorg_ImmWord {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAtMention']
struct haxorg_ImmAtMention {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmRawText']
struct haxorg_ImmRawText {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmPunctuation']
struct haxorg_ImmPunctuation {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmPlaceholder']
struct haxorg_ImmPlaceholder {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmBigIdent']
struct haxorg_ImmBigIdent {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmTextTarget']
struct haxorg_ImmTextTarget {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmErrorSkipToken']
struct haxorg_ImmErrorSkipToken {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmBold']
struct haxorg_ImmBold {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmUnderline']
struct haxorg_ImmUnderline {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmMonospace']
struct haxorg_ImmMonospace {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmMarkQuote']
struct haxorg_ImmMarkQuote {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmVerbatim']
struct haxorg_ImmVerbatim {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmItalic']
struct haxorg_ImmItalic {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmStrike']
struct haxorg_ImmStrike {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmPar']
struct haxorg_ImmPar {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterStmtAPI']
struct haxorg_ImmAdapterStmtAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterSubtreeAPI']
struct haxorg_ImmAdapterSubtreeAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterNoNodeAPI']
struct haxorg_ImmAdapterNoNodeAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterAttrAPI']
struct haxorg_ImmAdapterAttrAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterAttrListAPI']
struct haxorg_ImmAdapterAttrListAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterAttrsAPI']
struct haxorg_ImmAdapterAttrsAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterErrorItemAPI']
struct haxorg_ImmAdapterErrorItemAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterErrorGroupAPI']
struct haxorg_ImmAdapterErrorGroupAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterErrorSkipGroupAPI']
struct haxorg_ImmAdapterErrorSkipGroupAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterErrorSkipTokenAPI']
struct haxorg_ImmAdapterErrorSkipTokenAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterStmtListAPI']
struct haxorg_ImmAdapterStmtListAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterEmptyAPI']
struct haxorg_ImmAdapterEmptyAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterInlineAPI']
struct haxorg_ImmAdapterInlineAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterTimeAPI']
struct haxorg_ImmAdapterTimeAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterTimeRangeAPI']
struct haxorg_ImmAdapterTimeRangeAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterMacroAPI']
struct haxorg_ImmAdapterMacroAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterSymbolAPI']
struct haxorg_ImmAdapterSymbolAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterLeafAPI']
struct haxorg_ImmAdapterLeafAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterMarkupAPI']
struct haxorg_ImmAdapterMarkupAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterLatexAPI']
struct haxorg_ImmAdapterLatexAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterSubtreeLogAPI']
struct haxorg_ImmAdapterSubtreeLogAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterColonExampleAPI']
struct haxorg_ImmAdapterColonExampleAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterCallAPI']
struct haxorg_ImmAdapterCallAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterFileAPI']
struct haxorg_ImmAdapterFileAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterDirectoryAPI']
struct haxorg_ImmAdapterDirectoryAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterSymlinkAPI']
struct haxorg_ImmAdapterSymlinkAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterDocumentFragmentAPI']
struct haxorg_ImmAdapterDocumentFragmentAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterCriticMarkupAPI']
struct haxorg_ImmAdapterCriticMarkupAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterListItemAPI']
struct haxorg_ImmAdapterListItemAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterDocumentOptionsAPI']
struct haxorg_ImmAdapterDocumentOptionsAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterDocumentAPI']
struct haxorg_ImmAdapterDocumentAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterFileTargetAPI']
struct haxorg_ImmAdapterFileTargetAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterTextSeparatorAPI']
struct haxorg_ImmAdapterTextSeparatorAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterCmdIncludeAPI']
struct haxorg_ImmAdapterCmdIncludeAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterDocumentGroupAPI']
struct haxorg_ImmAdapterDocumentGroupAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Block']
struct haxorg_Block {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LineCommand']
struct haxorg_LineCommand {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdCreator']
struct haxorg_CmdCreator {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdAuthor']
struct haxorg_CmdAuthor {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdEmail']
struct haxorg_CmdEmail {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdLanguage']
struct haxorg_CmdLanguage {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdCustomArgs']
struct haxorg_CmdCustomArgs {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdTblfm']
struct haxorg_CmdTblfm {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Cell']
struct haxorg_Cell {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Row']
struct haxorg_Row {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmBlock']
struct haxorg_ImmBlock {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmLineCommand']
struct haxorg_ImmLineCommand {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdCreator']
struct haxorg_ImmCmdCreator {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdAuthor']
struct haxorg_ImmCmdAuthor {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdEmail']
struct haxorg_ImmCmdEmail {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdLanguage']
struct haxorg_ImmCmdLanguage {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdCustomArgs']
struct haxorg_ImmCmdCustomArgs {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdTblfm']
struct haxorg_ImmCmdTblfm {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCell']
struct haxorg_ImmCell {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmRow']
struct haxorg_ImmRow {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterCmdAPI']
struct haxorg_ImmAdapterCmdAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterCmdCustomRawAPI']
struct haxorg_ImmAdapterCmdCustomRawAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterCmdCustomTextAPI']
struct haxorg_ImmAdapterCmdCustomTextAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterLinkAPI']
struct haxorg_ImmAdapterLinkAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterBlockCommentAPI']
struct haxorg_ImmAdapterBlockCommentAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterParagraphAPI']
struct haxorg_ImmAdapterParagraphAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterListAPI']
struct haxorg_ImmAdapterListAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmStmt']]]
struct haxorg_ImmStmtAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmSubtree']]]
struct haxorg_ImmSubtreeAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmNoNode']]]
struct haxorg_ImmNoNodeAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmErrorItem']]]
struct haxorg_ImmErrorItemAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmErrorGroup']]]
struct haxorg_ImmErrorGroupAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmErrorSkipGroup']]]
struct haxorg_ImmErrorSkipGroupAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmErrorSkipToken']]]
struct haxorg_ImmErrorSkipTokenAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmStmtList']]]
struct haxorg_ImmStmtListAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmEmpty']]]
struct haxorg_ImmEmptyAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterHashTagAPI']
struct haxorg_ImmAdapterHashTagAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterInlineFootnoteAPI']
struct haxorg_ImmAdapterInlineFootnoteAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterSubtreeCompletionAPI']
struct haxorg_ImmAdapterSubtreeCompletionAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmInline']]]
struct haxorg_ImmInlineAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmTime']]]
struct haxorg_ImmTimeAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmTimeRange']]]
struct haxorg_ImmTimeRangeAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmMacro']]]
struct haxorg_ImmMacroAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmSymbol']]]
struct haxorg_ImmSymbolAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterEscapedAPI']
struct haxorg_ImmAdapterEscapedAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterNewlineAPI']
struct haxorg_ImmAdapterNewlineAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterSpaceAPI']
struct haxorg_ImmAdapterSpaceAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterWordAPI']
struct haxorg_ImmAdapterWordAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterAtMentionAPI']
struct haxorg_ImmAdapterAtMentionAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterRawTextAPI']
struct haxorg_ImmAdapterRawTextAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterPunctuationAPI']
struct haxorg_ImmAdapterPunctuationAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterPlaceholderAPI']
struct haxorg_ImmAdapterPlaceholderAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterBigIdentAPI']
struct haxorg_ImmAdapterBigIdentAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterTextTargetAPI']
struct haxorg_ImmAdapterTextTargetAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmLeaf']]]
struct haxorg_ImmLeafAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterBoldAPI']
struct haxorg_ImmAdapterBoldAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterUnderlineAPI']
struct haxorg_ImmAdapterUnderlineAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterMonospaceAPI']
struct haxorg_ImmAdapterMonospaceAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterMarkQuoteAPI']
struct haxorg_ImmAdapterMarkQuoteAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterRadioTargetAPI']
struct haxorg_ImmAdapterRadioTargetAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterVerbatimAPI']
struct haxorg_ImmAdapterVerbatimAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterItalicAPI']
struct haxorg_ImmAdapterItalicAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterStrikeAPI']
struct haxorg_ImmAdapterStrikeAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterParAPI']
struct haxorg_ImmAdapterParAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmMarkup']]]
struct haxorg_ImmMarkupAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmLatex']]]
struct haxorg_ImmLatexAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmSubtreeLog']]]
struct haxorg_ImmSubtreeLogAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmColonExample']]]
struct haxorg_ImmColonExampleAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCall']]]
struct haxorg_ImmCallAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmFile']]]
struct haxorg_ImmFileAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmDirectory']]]
struct haxorg_ImmDirectoryAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmSymlink']]]
struct haxorg_ImmSymlinkAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmDocumentFragment']]]
struct haxorg_ImmDocumentFragmentAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCriticMarkup']]]
struct haxorg_ImmCriticMarkupAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmListItem']]]
struct haxorg_ImmListItemAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmDocumentOptions']]]
struct haxorg_ImmDocumentOptionsAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmDocument']]]
struct haxorg_ImmDocumentAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmFileTarget']]]
struct haxorg_ImmFileTargetAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmTextSeparator']]]
struct haxorg_ImmTextSeparatorAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdInclude']]]
struct haxorg_ImmCmdIncludeAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmDocumentGroup']]]
struct haxorg_ImmDocumentGroupAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockCenter']
struct haxorg_BlockCenter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockQuote']
struct haxorg_BlockQuote {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockVerse']
struct haxorg_BlockVerse {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockDynamicFallback']
struct haxorg_BlockDynamicFallback {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockExample']
struct haxorg_BlockExample {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockExport']
struct haxorg_BlockExport {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockAdmonition']
struct haxorg_BlockAdmonition {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockCodeEvalResult']
struct haxorg_BlockCodeEvalResult {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockCode']
struct haxorg_BlockCode {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Table']
struct haxorg_Table {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Attached']
struct haxorg_Attached {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmBlockCenter']
struct haxorg_ImmBlockCenter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmBlockQuote']
struct haxorg_ImmBlockQuote {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmBlockVerse']
struct haxorg_ImmBlockVerse {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmBlockDynamicFallback']
struct haxorg_ImmBlockDynamicFallback {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmBlockExample']
struct haxorg_ImmBlockExample {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmBlockExport']
struct haxorg_ImmBlockExport {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmBlockAdmonition']
struct haxorg_ImmBlockAdmonition {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmBlockCodeEvalResult']
struct haxorg_ImmBlockCodeEvalResult {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmBlockCode']
struct haxorg_ImmBlockCode {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmTable']
struct haxorg_ImmTable {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAttached']
struct haxorg_ImmAttached {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterLineCommandAPI']
struct haxorg_ImmAdapterLineCommandAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterCmdCustomArgsAPI']
struct haxorg_ImmAdapterCmdCustomArgsAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterCmdCreatorAPI']
struct haxorg_ImmAdapterCmdCreatorAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterCmdAuthorAPI']
struct haxorg_ImmAdapterCmdAuthorAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterCmdEmailAPI']
struct haxorg_ImmAdapterCmdEmailAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterCmdLanguageAPI']
struct haxorg_ImmAdapterCmdLanguageAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterCmdTblfmAPI']
struct haxorg_ImmAdapterCmdTblfmAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterBlockAPI']
struct haxorg_ImmAdapterBlockAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterCellAPI']
struct haxorg_ImmAdapterCellAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterRowAPI']
struct haxorg_ImmAdapterRowAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmd']]]
struct haxorg_ImmCmdAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdCustomRaw']]]
struct haxorg_ImmCmdCustomRawAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdCustomText']]]
struct haxorg_ImmCmdCustomTextAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmLink']]]
struct haxorg_ImmLinkAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlockComment']]]
struct haxorg_ImmBlockCommentAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmParagraph']]]
struct haxorg_ImmParagraphAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmList']]]
struct haxorg_ImmListAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmHashTag']]]
struct haxorg_ImmHashTagAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmInlineFootnote']]]
struct haxorg_ImmInlineFootnoteAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmEscaped']]]
struct haxorg_ImmEscapedAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmNewline']]]
struct haxorg_ImmNewlineAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmSpace']]]
struct haxorg_ImmSpaceAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmWord']]]
struct haxorg_ImmWordAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmAtMention']]]
struct haxorg_ImmAtMentionAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmRawText']]]
struct haxorg_ImmRawTextAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmPunctuation']]]
struct haxorg_ImmPunctuationAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmPlaceholder']]]
struct haxorg_ImmPlaceholderAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBigIdent']]]
struct haxorg_ImmBigIdentAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmTextTarget']]]
struct haxorg_ImmTextTargetAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBold']]]
struct haxorg_ImmBoldAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmUnderline']]]
struct haxorg_ImmUnderlineAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmMonospace']]]
struct haxorg_ImmMonospaceAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmMarkQuote']]]
struct haxorg_ImmMarkQuoteAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmRadioTarget']]]
struct haxorg_ImmRadioTargetAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmVerbatim']]]
struct haxorg_ImmVerbatimAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmItalic']]]
struct haxorg_ImmItalicAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmStrike']]]
struct haxorg_ImmStrikeAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmPar']]]
struct haxorg_ImmParAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdCaption']
struct haxorg_CmdCaption {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdColumns']
struct haxorg_CmdColumns {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdName']
struct haxorg_CmdName {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdCall']
struct haxorg_CmdCall {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdAttr']
struct haxorg_CmdAttr {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdExport']
struct haxorg_CmdExport {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdCaption']
struct haxorg_ImmCmdCaption {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdColumns']
struct haxorg_ImmCmdColumns {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdName']
struct haxorg_ImmCmdName {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdCall']
struct haxorg_ImmCmdCall {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdAttr']
struct haxorg_ImmCmdAttr {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdExport']
struct haxorg_ImmCmdExport {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterAttachedAPI']
struct haxorg_ImmAdapterAttachedAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmLineCommand']]]
struct haxorg_ImmLineCommandAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdCustomArgs']]]
struct haxorg_ImmCmdCustomArgsAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdCreator']]]
struct haxorg_ImmCmdCreatorAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdAuthor']]]
struct haxorg_ImmCmdAuthorAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdEmail']]]
struct haxorg_ImmCmdEmailAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdLanguage']]]
struct haxorg_ImmCmdLanguageAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdTblfm']]]
struct haxorg_ImmCmdTblfmAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterBlockCenterAPI']
struct haxorg_ImmAdapterBlockCenterAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterBlockQuoteAPI']
struct haxorg_ImmAdapterBlockQuoteAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterBlockVerseAPI']
struct haxorg_ImmAdapterBlockVerseAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterBlockExampleAPI']
struct haxorg_ImmAdapterBlockExampleAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterInlineExportAPI']
struct haxorg_ImmAdapterInlineExportAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterCmdExportAPI']
struct haxorg_ImmAdapterCmdExportAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterBlockExportAPI']
struct haxorg_ImmAdapterBlockExportAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterBlockDynamicFallbackAPI']
struct haxorg_ImmAdapterBlockDynamicFallbackAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterBlockAdmonitionAPI']
struct haxorg_ImmAdapterBlockAdmonitionAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterBlockCodeEvalResultAPI']
struct haxorg_ImmAdapterBlockCodeEvalResultAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterBlockCodeAPI']
struct haxorg_ImmAdapterBlockCodeAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterTableAPI']
struct haxorg_ImmAdapterTableAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlock']]]
struct haxorg_ImmBlockAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCell']]]
struct haxorg_ImmCellAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmRow']]]
struct haxorg_ImmRowAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterCmdCaptionAPI']
struct haxorg_ImmAdapterCmdCaptionAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterCmdColumnsAPI']
struct haxorg_ImmAdapterCmdColumnsAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterCmdNameAPI']
struct haxorg_ImmAdapterCmdNameAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterCmdCallAPI']
struct haxorg_ImmAdapterCmdCallAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterCmdResultsAPI']
struct haxorg_ImmAdapterCmdResultsAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterCmdAttrAPI']
struct haxorg_ImmAdapterCmdAttrAPI {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmAttached']]]
struct haxorg_ImmAttachedAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlockCenter']]]
struct haxorg_ImmBlockCenterAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlockQuote']]]
struct haxorg_ImmBlockQuoteAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlockVerse']]]
struct haxorg_ImmBlockVerseAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlockExample']]]
struct haxorg_ImmBlockExampleAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmInlineExport']]]
struct haxorg_ImmInlineExportAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdExport']]]
struct haxorg_ImmCmdExportAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlockExport']]]
struct haxorg_ImmBlockExportAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlockDynamicFallback']]]
struct haxorg_ImmBlockDynamicFallbackAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlockAdmonition']]]
struct haxorg_ImmBlockAdmonitionAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlockCodeEvalResult']]]
struct haxorg_ImmBlockCodeEvalResultAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlockCode']]]
struct haxorg_ImmBlockCodeAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmTable']]]
struct haxorg_ImmTableAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdCaption']]]
struct haxorg_ImmCmdCaptionAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdColumns']]]
struct haxorg_ImmCmdColumnsAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdName']]]
struct haxorg_ImmCmdNameAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdCall']]]
struct haxorg_ImmCmdCallAdapter {
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdAttr']]]
struct haxorg_ImmCmdAttrAdapter {
  haxorg_ptr_payload data;
};

typedef haxorg_HstdVecOfGraphMapNode haxorg_GraphAdjNodesList;
typedef haxorg_HstdMap haxorg_GraphNodeProps;
typedef haxorg_HstdMap haxorg_GraphEdgeProps;
typedef haxorg_HstdMap haxorg_GraphAdjList;
HAXORG_C_API_LINKAGE bool haxorg_SemIdOfOrg_isNil_const(OrgContext* org_context, haxorg_SemIdOfOrg __this);
HAXORG_C_API_LINKAGE bool haxorg_SemIdOfOrg___eq___const(OrgContext* org_context, haxorg_SemIdOfOrg __this, haxorg_SemIdOfOrg other);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_SemIdOfOrg_Nil(OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_Org haxorg_SemIdOfOrg_get(OrgContext* org_context, haxorg_SemIdOfOrg __this);
HAXORG_C_API_LINKAGE haxorg_Org haxorg_SemIdOfOrg_get_const(OrgContext* org_context, haxorg_SemIdOfOrg __this);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_SemIdOfOrg_asOrg_const(OrgContext* org_context, haxorg_SemIdOfOrg __this);
HAXORG_C_API_LINKAGE haxorg_OrgSemKind haxorg_SemIdOfOrg_getNodeKind_const(OrgContext* org_context, haxorg_SemIdOfOrg __this);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_SemIdOfOrg_atIndex(OrgContext* org_context, haxorg_SemIdOfOrg __this, int idx);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_SemIdOfOrg_atIndexBackwards(OrgContext* org_context, haxorg_SemIdOfOrg __this, haxorg_BackwardsIndex idx);
HAXORG_C_API_LINKAGE haxorg_StdOptional haxorg_SemIdOfOrg_getIndex(OrgContext* org_context, haxorg_SemIdOfOrg __this, int idx);
HAXORG_C_API_LINKAGE haxorg_StdOptional haxorg_SemIdOfOrg_getIndexBackwards(OrgContext* org_context, haxorg_SemIdOfOrg __this, haxorg_BackwardsIndex idx);
HAXORG_C_API_LINKAGE int haxorg_SemIdOfOrg_size_const(OrgContext* org_context, haxorg_SemIdOfOrg __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_SemIdOfOrg(OrgContext* org_context, haxorg_SemIdOfOrg* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfOrgJson_size_const(OrgContext* org_context, haxorg_HstdVecOfOrgJson __this);
HAXORG_C_API_LINKAGE haxorg_OrgJson haxorg_HstdVecOfOrgJson_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfOrgJson __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfOrgJson(OrgContext* org_context, haxorg_HstdVecOfOrgJson* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfSemIdOfOrg_size_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfOrg __this);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_HstdVecOfSemIdOfOrg_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfOrg __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfSemIdOfOrg(OrgContext* org_context, haxorg_HstdVecOfSemIdOfOrg* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfReport_size_const(OrgContext* org_context, haxorg_HstdVecOfReport __this);
HAXORG_C_API_LINKAGE haxorg_Report haxorg_HstdVecOfReport_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfReport __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfReport(OrgContext* org_context, haxorg_HstdVecOfReport* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfSemIdOfErrorGroup_size_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfErrorGroup __this);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_HstdVecOfSemIdOfErrorGroup_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfErrorGroup __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfSemIdOfErrorGroup(OrgContext* org_context, haxorg_HstdVecOfSemIdOfErrorGroup* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfInt_size_const(OrgContext* org_context, haxorg_HstdVecOfInt __this);
HAXORG_C_API_LINKAGE int const& haxorg_HstdVecOfInt_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfInt __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfInt(OrgContext* org_context, haxorg_HstdVecOfInt* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfImmAdapter_size_const(OrgContext* org_context, haxorg_HstdVecOfImmAdapter __this);
HAXORG_C_API_LINKAGE haxorg_ImmAdapter haxorg_HstdVecOfImmAdapter_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfImmAdapter __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfImmAdapter(OrgContext* org_context, haxorg_HstdVecOfImmAdapter* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfSequenceSegment_size_const(OrgContext* org_context, haxorg_HstdVecOfSequenceSegment __this);
HAXORG_C_API_LINKAGE haxorg_SequenceSegment haxorg_HstdVecOfSequenceSegment_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSequenceSegment __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfSequenceSegment(OrgContext* org_context, haxorg_HstdVecOfSequenceSegment* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfSequenceAnnotationTag_size_const(OrgContext* org_context, haxorg_HstdVecOfSequenceAnnotationTag __this);
HAXORG_C_API_LINKAGE haxorg_SequenceAnnotationTag haxorg_HstdVecOfSequenceAnnotationTag_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSequenceAnnotationTag __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfSequenceAnnotationTag(OrgContext* org_context, haxorg_HstdVecOfSequenceAnnotationTag* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfImmUniqId_size_const(OrgContext* org_context, haxorg_HstdVecOfImmUniqId __this);
HAXORG_C_API_LINKAGE haxorg_ImmUniqId haxorg_HstdVecOfImmUniqId_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfImmUniqId __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfImmUniqId(OrgContext* org_context, haxorg_HstdVecOfImmUniqId* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfGraphMapLink_size_const(OrgContext* org_context, haxorg_HstdVecOfGraphMapLink __this);
HAXORG_C_API_LINKAGE haxorg_GraphMapLink haxorg_HstdVecOfGraphMapLink_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfGraphMapLink __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfGraphMapLink(OrgContext* org_context, haxorg_HstdVecOfGraphMapLink* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfGraphMapNode_size_const(OrgContext* org_context, haxorg_HstdVecOfGraphMapNode __this);
HAXORG_C_API_LINKAGE haxorg_GraphMapNode haxorg_HstdVecOfGraphMapNode_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfGraphMapNode __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfGraphMapNode(OrgContext* org_context, haxorg_HstdVecOfGraphMapNode* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfGraphMapEdge_size_const(OrgContext* org_context, haxorg_HstdVecOfGraphMapEdge __this);
HAXORG_C_API_LINKAGE haxorg_GraphMapEdge haxorg_HstdVecOfGraphMapEdge_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfGraphMapEdge __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfGraphMapEdge(OrgContext* org_context, haxorg_HstdVecOfGraphMapEdge* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfLispCode_size_const(OrgContext* org_context, haxorg_HstdVecOfLispCode __this);
HAXORG_C_API_LINKAGE haxorg_LispCode haxorg_HstdVecOfLispCode_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfLispCode __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfLispCode(OrgContext* org_context, haxorg_HstdVecOfLispCode* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfTblfmAssign_size_const(OrgContext* org_context, haxorg_HstdVecOfTblfmAssign __this);
HAXORG_C_API_LINKAGE haxorg_TblfmAssign haxorg_HstdVecOfTblfmAssign_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfTblfmAssign __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfTblfmAssign(OrgContext* org_context, haxorg_HstdVecOfTblfmAssign* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfTblfmExpr_size_const(OrgContext* org_context, haxorg_HstdVecOfTblfmExpr __this);
HAXORG_C_API_LINKAGE haxorg_TblfmExpr haxorg_HstdVecOfTblfmExpr_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfTblfmExpr __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfTblfmExpr(OrgContext* org_context, haxorg_HstdVecOfTblfmExpr* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfTblfmAssignFlag_size_const(OrgContext* org_context, haxorg_HstdVecOfTblfmAssignFlag __this);
HAXORG_C_API_LINKAGE haxorg_TblfmAssignFlag haxorg_HstdVecOfTblfmAssignFlag_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfTblfmAssignFlag __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfTblfmAssignFlag(OrgContext* org_context, haxorg_HstdVecOfTblfmAssignFlag* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfAttrValueDimensionSpan_size_const(OrgContext* org_context, haxorg_HstdVecOfAttrValueDimensionSpan __this);
HAXORG_C_API_LINKAGE haxorg_AttrValueDimensionSpan haxorg_HstdVecOfAttrValueDimensionSpan_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfAttrValueDimensionSpan __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfAttrValueDimensionSpan(OrgContext* org_context, haxorg_HstdVecOfAttrValueDimensionSpan* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfStr_size_const(OrgContext* org_context, haxorg_HstdVecOfStr __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_HstdVecOfStr_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfStr __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfStr(OrgContext* org_context, haxorg_HstdVecOfStr* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfHashTagFlat_size_const(OrgContext* org_context, haxorg_HstdVecOfHashTagFlat __this);
HAXORG_C_API_LINKAGE haxorg_HashTagFlat haxorg_HstdVecOfHashTagFlat_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfHashTagFlat __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfHashTagFlat(OrgContext* org_context, haxorg_HstdVecOfHashTagFlat* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfHashTagText_size_const(OrgContext* org_context, haxorg_HstdVecOfHashTagText __this);
HAXORG_C_API_LINKAGE haxorg_HashTagText haxorg_HstdVecOfHashTagText_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfHashTagText __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfHashTagText(OrgContext* org_context, haxorg_HstdVecOfHashTagText* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfAttrValue_size_const(OrgContext* org_context, haxorg_HstdVecOfAttrValue __this);
HAXORG_C_API_LINKAGE haxorg_AttrValue haxorg_HstdVecOfAttrValue_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfAttrValue __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfAttrValue(OrgContext* org_context, haxorg_HstdVecOfAttrValue* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfOrgCodeEvalInputVar_size_const(OrgContext* org_context, haxorg_HstdVecOfOrgCodeEvalInputVar __this);
HAXORG_C_API_LINKAGE haxorg_OrgCodeEvalInputVar haxorg_HstdVecOfOrgCodeEvalInputVar_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfOrgCodeEvalInputVar __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfOrgCodeEvalInputVar(OrgContext* org_context, haxorg_HstdVecOfOrgCodeEvalInputVar* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfColumnViewColumn_size_const(OrgContext* org_context, haxorg_HstdVecOfColumnViewColumn __this);
HAXORG_C_API_LINKAGE haxorg_ColumnViewColumn haxorg_HstdVecOfColumnViewColumn_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfColumnViewColumn __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfColumnViewColumn(OrgContext* org_context, haxorg_HstdVecOfColumnViewColumn* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfBlockCodeLinePart_size_const(OrgContext* org_context, haxorg_HstdVecOfBlockCodeLinePart __this);
HAXORG_C_API_LINKAGE haxorg_BlockCodeLinePart haxorg_HstdVecOfBlockCodeLinePart_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfBlockCodeLinePart __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfBlockCodeLinePart(OrgContext* org_context, haxorg_HstdVecOfBlockCodeLinePart* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfSemIdOfErrorItem_size_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfErrorItem __this);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_HstdVecOfSemIdOfErrorItem_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfErrorItem __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfSemIdOfErrorItem(OrgContext* org_context, haxorg_HstdVecOfSemIdOfErrorItem* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfTimeRepeat_size_const(OrgContext* org_context, haxorg_HstdVecOfTimeRepeat __this);
HAXORG_C_API_LINKAGE haxorg_TimeRepeat haxorg_HstdVecOfTimeRepeat_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfTimeRepeat __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfTimeRepeat(OrgContext* org_context, haxorg_HstdVecOfTimeRepeat* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfSymbolParam_size_const(OrgContext* org_context, haxorg_HstdVecOfSymbolParam __this);
HAXORG_C_API_LINKAGE haxorg_SymbolParam haxorg_HstdVecOfSymbolParam_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSymbolParam __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfSymbolParam(OrgContext* org_context, haxorg_HstdVecOfSymbolParam* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfSemIdOfErrorSkipToken_size_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfErrorSkipToken __this);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_HstdVecOfSemIdOfErrorSkipToken_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfErrorSkipToken __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfSemIdOfErrorSkipToken(OrgContext* org_context, haxorg_HstdVecOfSemIdOfErrorSkipToken* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfSubtreePeriod_size_const(OrgContext* org_context, haxorg_HstdVecOfSubtreePeriod __this);
HAXORG_C_API_LINKAGE haxorg_SubtreePeriod haxorg_HstdVecOfSubtreePeriod_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSubtreePeriod __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfSubtreePeriod(OrgContext* org_context, haxorg_HstdVecOfSubtreePeriod* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfNamedProperty_size_const(OrgContext* org_context, haxorg_HstdVecOfNamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedProperty haxorg_HstdVecOfNamedProperty_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfNamedProperty __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfNamedProperty(OrgContext* org_context, haxorg_HstdVecOfNamedProperty* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfSemIdOfHashTag_size_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfHashTag __this);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_HstdVecOfSemIdOfHashTag_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfHashTag __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfSemIdOfHashTag(OrgContext* org_context, haxorg_HstdVecOfSemIdOfHashTag* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfSemIdOfSubtreeLog_size_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfSubtreeLog __this);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_HstdVecOfSemIdOfSubtreeLog_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfSubtreeLog __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfSemIdOfSubtreeLog(OrgContext* org_context, haxorg_HstdVecOfSemIdOfSubtreeLog* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfTodoKeyword_size_const(OrgContext* org_context, haxorg_HstdVecOfTodoKeyword __this);
HAXORG_C_API_LINKAGE haxorg_TodoKeyword haxorg_HstdVecOfTodoKeyword_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfTodoKeyword __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfTodoKeyword(OrgContext* org_context, haxorg_HstdVecOfTodoKeyword* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfSemIdOfBigIdent_size_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfBigIdent __this);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_HstdVecOfSemIdOfBigIdent_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfBigIdent __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfSemIdOfBigIdent(OrgContext* org_context, haxorg_HstdVecOfSemIdOfBigIdent* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfUserTime_size_const(OrgContext* org_context, haxorg_HstdVecOfUserTime __this);
HAXORG_C_API_LINKAGE haxorg_UserTime haxorg_HstdVecOfUserTime_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfUserTime __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfUserTime(OrgContext* org_context, haxorg_HstdVecOfUserTime* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfSemIdOfTime_size_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfTime __this);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_HstdVecOfSemIdOfTime_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfTime __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfSemIdOfTime(OrgContext* org_context, haxorg_HstdVecOfSemIdOfTime* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfSemIdOfCell_size_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfCell __this);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_HstdVecOfSemIdOfCell_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfCell __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfSemIdOfCell(OrgContext* org_context, haxorg_HstdVecOfSemIdOfCell* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfOrgCodeEvalOutput_size_const(OrgContext* org_context, haxorg_HstdVecOfOrgCodeEvalOutput __this);
HAXORG_C_API_LINKAGE haxorg_OrgCodeEvalOutput haxorg_HstdVecOfOrgCodeEvalOutput_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfOrgCodeEvalOutput __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfOrgCodeEvalOutput(OrgContext* org_context, haxorg_HstdVecOfOrgCodeEvalOutput* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfSemIdOfBlockCodeEvalResult_size_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfBlockCodeEvalResult __this);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_HstdVecOfSemIdOfBlockCodeEvalResult_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfBlockCodeEvalResult __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfSemIdOfBlockCodeEvalResult(OrgContext* org_context, haxorg_HstdVecOfSemIdOfBlockCodeEvalResult* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfBlockCodeLine_size_const(OrgContext* org_context, haxorg_HstdVecOfBlockCodeLine __this);
HAXORG_C_API_LINKAGE haxorg_BlockCodeLine haxorg_HstdVecOfBlockCodeLine_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfBlockCodeLine __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfBlockCodeLine(OrgContext* org_context, haxorg_HstdVecOfBlockCodeLine* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfSemIdOfRow_size_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfRow __this);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_HstdVecOfSemIdOfRow_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfRow __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfSemIdOfRow(OrgContext* org_context, haxorg_HstdVecOfSemIdOfRow* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfAstTrackingGroup_size_const(OrgContext* org_context, haxorg_HstdVecOfAstTrackingGroup __this);
HAXORG_C_API_LINKAGE haxorg_AstTrackingGroup haxorg_HstdVecOfAstTrackingGroup_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfAstTrackingGroup __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfAstTrackingGroup(OrgContext* org_context, haxorg_HstdVecOfAstTrackingGroup* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfSequenceAnnotation_size_const(OrgContext* org_context, haxorg_HstdVecOfSequenceAnnotation __this);
HAXORG_C_API_LINKAGE haxorg_SequenceAnnotation haxorg_HstdVecOfSequenceAnnotation_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSequenceAnnotation __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfSequenceAnnotation(OrgContext* org_context, haxorg_HstdVecOfSequenceAnnotation* obj);
HAXORG_C_API_LINKAGE int haxorg_HstdVecOfSequenceSegmentGroup_size_const(OrgContext* org_context, haxorg_HstdVecOfSequenceSegmentGroup __this);
HAXORG_C_API_LINKAGE haxorg_SequenceSegmentGroup haxorg_HstdVecOfSequenceSegmentGroup_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSequenceSegmentGroup __this, int idx);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdVecOfSequenceSegmentGroup(OrgContext* org_context, haxorg_HstdVecOfSequenceSegmentGroup* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdMap(OrgContext* org_context, haxorg_HstdMap* obj);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmMapOfHaxorg_ptr_payloadHaxorg_ptr_payload_get_const(OrgContext* org_context, haxorg_ImmMap __this, haxorg_ptr_payload const& key);
HAXORG_C_API_LINKAGE bool haxorg_ImmMapOfHaxorg_ptr_payloadHaxorg_ptr_payload_contains_const(OrgContext* org_context, haxorg_ImmMap __this, haxorg_ptr_payload const& key);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfHaxorg_ptr_payload haxorg_ImmMapOfHaxorg_ptr_payloadHaxorg_ptr_payload_keys_const(OrgContext* org_context, haxorg_ImmMap __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmMap(OrgContext* org_context, haxorg_ImmMap* obj);
HAXORG_C_API_LINKAGE int haxorg_BackwardsIndex_get_value(OrgContext* org_context, haxorg_BackwardsIndex __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_BackwardsIndex(OrgContext* org_context, haxorg_BackwardsIndex* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_create_Str_StrFromCString(OrgContext* org_context, char const* conv);
HAXORG_C_API_LINKAGE char* haxorg_Str_data(OrgContext* org_context, haxorg_HstdStr __this);
HAXORG_C_API_LINKAGE char const* haxorg_Str_data_const(OrgContext* org_context, haxorg_HstdStr __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_Str_dropPrefix_const(OrgContext* org_context, haxorg_HstdStr __this, haxorg_HstdStr prefix);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_Str_dropSuffix_const(OrgContext* org_context, haxorg_HstdStr __this, haxorg_HstdStr suffix);
HAXORG_C_API_LINKAGE char haxorg_Str_atIndex_const(OrgContext* org_context, haxorg_HstdStr __this, int pos);
HAXORG_C_API_LINKAGE int haxorg_Str_size_const(OrgContext* org_context, haxorg_HstdStr __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_HstdStr(OrgContext* org_context, haxorg_HstdStr* obj);
HAXORG_C_API_LINKAGE haxorg_StdOptional haxorg_UserTimeBreakdown_get_year(OrgContext* org_context, haxorg_UserTimeBreakdown __this);
HAXORG_C_API_LINKAGE haxorg_StdOptional haxorg_UserTimeBreakdown_get_month(OrgContext* org_context, haxorg_UserTimeBreakdown __this);
HAXORG_C_API_LINKAGE haxorg_StdOptional haxorg_UserTimeBreakdown_get_day(OrgContext* org_context, haxorg_UserTimeBreakdown __this);
HAXORG_C_API_LINKAGE haxorg_StdOptional haxorg_UserTimeBreakdown_get_hour(OrgContext* org_context, haxorg_UserTimeBreakdown __this);
HAXORG_C_API_LINKAGE haxorg_StdOptional haxorg_UserTimeBreakdown_get_minute(OrgContext* org_context, haxorg_UserTimeBreakdown __this);
HAXORG_C_API_LINKAGE haxorg_StdOptional haxorg_UserTimeBreakdown_get_second(OrgContext* org_context, haxorg_UserTimeBreakdown __this);
HAXORG_C_API_LINKAGE haxorg_StdOptional haxorg_UserTimeBreakdown_get_zone(OrgContext* org_context, haxorg_UserTimeBreakdown __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_UserTimeBreakdown(OrgContext* org_context, haxorg_UserTimeBreakdown* obj);
HAXORG_C_API_LINKAGE haxorg_UserTimeBreakdown haxorg_UserTime_getBreakdown_const(OrgContext* org_context, haxorg_UserTime __this);
HAXORG_C_API_LINKAGE haxorg_StdString haxorg_UserTime_format_const(OrgContext* org_context, haxorg_UserTime __this);
HAXORG_C_API_LINKAGE int64_t haxorg_UserTime_getTimeDeltaSeconds_const(OrgContext* org_context, haxorg_UserTime __this, haxorg_UserTime other);
HAXORG_C_API_LINKAGE int64_t haxorg_UserTime_toUnixTimestamp_const(OrgContext* org_context, haxorg_UserTime __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_UserTime(OrgContext* org_context, haxorg_UserTime* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ParseSourceFileId(OrgContext* org_context, haxorg_ParseSourceFileId* obj);
HAXORG_C_API_LINKAGE haxorg_StdString haxorg_ParseSourceManager_getPath_const(OrgContext* org_context, haxorg_ParseSourceManager __this, haxorg_ParseSourceFileId id);
HAXORG_C_API_LINKAGE haxorg_ParseSourceFileId haxorg_ParseSourceManager_getId_const(OrgContext* org_context, haxorg_ParseSourceManager __this, haxorg_StdString path);
HAXORG_C_API_LINKAGE haxorg_StdString haxorg_ParseSourceManager_getSourceContent_const(OrgContext* org_context, haxorg_ParseSourceManager __this, haxorg_ParseSourceFileId id);
HAXORG_C_API_LINKAGE haxorg_StdString haxorg_ParseSourceManager_getContentTextForPath_const(OrgContext* org_context, haxorg_ParseSourceManager __this, haxorg_StdString path);
HAXORG_C_API_LINKAGE haxorg_ParseSourceFileId haxorg_ParseSourceManager_addSource(OrgContext* org_context, haxorg_ParseSourceManager __this, haxorg_StdString path, haxorg_StdString content);
HAXORG_C_API_LINKAGE void haxorg_destroy_ParseSourceManager(OrgContext* org_context, haxorg_ParseSourceManager* obj);
HAXORG_C_API_LINKAGE int haxorg_ParseSourceLoc_get_line(OrgContext* org_context, haxorg_ParseSourceLoc __this);
HAXORG_C_API_LINKAGE int haxorg_ParseSourceLoc_get_column(OrgContext* org_context, haxorg_ParseSourceLoc __this);
HAXORG_C_API_LINKAGE int haxorg_ParseSourceLoc_get_pos(OrgContext* org_context, haxorg_ParseSourceLoc __this);
HAXORG_C_API_LINKAGE haxorg_ParseSourceFileId haxorg_ParseSourceLoc_get_file_id(OrgContext* org_context, haxorg_ParseSourceLoc __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_ParseSourceLoc(OrgContext* org_context, haxorg_ParseSourceLoc* obj);
HAXORG_C_API_LINKAGE haxorg_OrgJsonKind haxorg_OrgJson_getKind_const(OrgContext* org_context, haxorg_OrgJson __this);
HAXORG_C_API_LINKAGE haxorg_StdString haxorg_OrgJson_getJsonString_const(OrgContext* org_context, haxorg_OrgJson __this);
HAXORG_C_API_LINKAGE haxorg_OrgJson haxorg_OrgJson_atIndex_const(OrgContext* org_context, haxorg_OrgJson __this, int idx);
HAXORG_C_API_LINKAGE haxorg_OrgJson haxorg_OrgJson_atField_const(OrgContext* org_context, haxorg_OrgJson __this, haxorg_StdString name);
HAXORG_C_API_LINKAGE haxorg_StdString haxorg_OrgJson_getString_const(OrgContext* org_context, haxorg_OrgJson __this);
HAXORG_C_API_LINKAGE haxorg_OrgJson haxorg_OrgJson_getField_const(OrgContext* org_context, haxorg_OrgJson __this, haxorg_StdString name);
HAXORG_C_API_LINKAGE haxorg_OrgJson haxorg_OrgJson_getItem_const(OrgContext* org_context, haxorg_OrgJson __this, int index);
HAXORG_C_API_LINKAGE int haxorg_OrgJson_getInt_const(OrgContext* org_context, haxorg_OrgJson __this);
HAXORG_C_API_LINKAGE bool haxorg_OrgJson_getBool_const(OrgContext* org_context, haxorg_OrgJson __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfOrgJson haxorg_OrgJson_getArray_const(OrgContext* org_context, haxorg_OrgJson __this);
HAXORG_C_API_LINKAGE haxorg_StdString haxorg_OrgJson_dump_const(OrgContext* org_context, haxorg_OrgJson __this, int indent);
HAXORG_C_API_LINKAGE void haxorg_destroy_OrgJson(OrgContext* org_context, haxorg_OrgJson* obj);
HAXORG_C_API_LINKAGE haxorg_StdOptional haxorg_Org_get_loc(OrgContext* org_context, haxorg_Org __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfSemIdOfOrg haxorg_Org_get_subnodes(OrgContext* org_context, haxorg_Org __this);
HAXORG_C_API_LINKAGE haxorg_OrgSemKind haxorg_Org_getKind_const(OrgContext* org_context, haxorg_Org __this);
HAXORG_C_API_LINKAGE void haxorg_Org_push_back(OrgContext* org_context, haxorg_Org __this, haxorg_SemIdOfOrg sub);
HAXORG_C_API_LINKAGE int haxorg_Org_size_const(OrgContext* org_context, haxorg_Org __this);
HAXORG_C_API_LINKAGE void haxorg_Org_insert(OrgContext* org_context, haxorg_Org __this, int pos, haxorg_SemIdOfOrg node);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_Org_at_const(OrgContext* org_context, haxorg_Org __this, int idx);
HAXORG_C_API_LINKAGE bool haxorg_Org_is_const(OrgContext* org_context, haxorg_Org __this, haxorg_OrgSemKind kind);
HAXORG_C_API_LINKAGE void haxorg_destroy_Org(OrgContext* org_context, haxorg_Org* obj);
HAXORG_C_API_LINKAGE bool haxorg_OperationsTracer_get_TraceState(OrgContext* org_context, haxorg_OperationsTracer __this);
HAXORG_C_API_LINKAGE bool haxorg_OperationsTracer_get_traceToFile(OrgContext* org_context, haxorg_OperationsTracer __this);
HAXORG_C_API_LINKAGE bool haxorg_OperationsTracer_get_traceToBuffer(OrgContext* org_context, haxorg_OperationsTracer __this);
HAXORG_C_API_LINKAGE bool haxorg_OperationsTracer_get_traceStructured(OrgContext* org_context, haxorg_OperationsTracer __this);
HAXORG_C_API_LINKAGE bool haxorg_OperationsTracer_get_traceColored(OrgContext* org_context, haxorg_OperationsTracer __this);
HAXORG_C_API_LINKAGE int haxorg_OperationsTracer_get_activeLevel(OrgContext* org_context, haxorg_OperationsTracer __this);
HAXORG_C_API_LINKAGE haxorg_StdString haxorg_OperationsTracer_get_traceBuffer(OrgContext* org_context, haxorg_OperationsTracer __this);
HAXORG_C_API_LINKAGE void haxorg_OperationsTracer_setTraceFileStr(OrgContext* org_context, haxorg_OperationsTracer __this, haxorg_StdString outfile, bool overwrite);
HAXORG_C_API_LINKAGE void haxorg_OperationsTracer_sendMessage(OrgContext* org_context, haxorg_OperationsTracer __this, haxorg_StdString value, haxorg_StdString function, int line, haxorg_StdString file);
HAXORG_C_API_LINKAGE void haxorg_destroy_OperationsTracer(OrgContext* org_context, haxorg_OperationsTracer* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Cache(OrgContext* org_context, haxorg_Cache* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Report(OrgContext* org_context, haxorg_Report* obj);
HAXORG_C_API_LINKAGE int haxorg_ParseOrgParseFragment_get_baseLine(OrgContext* org_context, haxorg_ParseOrgParseFragment __this);
HAXORG_C_API_LINKAGE int haxorg_ParseOrgParseFragment_get_baseCol(OrgContext* org_context, haxorg_ParseOrgParseFragment __this);
HAXORG_C_API_LINKAGE haxorg_StdString haxorg_ParseOrgParseFragment_get_text(OrgContext* org_context, haxorg_ParseOrgParseFragment __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_ParseOrgParseFragment(OrgContext* org_context, haxorg_ParseOrgParseFragment* obj);
HAXORG_C_API_LINKAGE haxorg_StdOptional haxorg_OrgParseParameters_get_baseTokenTracePath(OrgContext* org_context, haxorg_OrgParseParameters __this);
HAXORG_C_API_LINKAGE haxorg_StdOptional haxorg_OrgParseParameters_get_tokenTracePath(OrgContext* org_context, haxorg_OrgParseParameters __this);
HAXORG_C_API_LINKAGE haxorg_StdOptional haxorg_OrgParseParameters_get_parseTracePath(OrgContext* org_context, haxorg_OrgParseParameters __this);
HAXORG_C_API_LINKAGE haxorg_StdOptional haxorg_OrgParseParameters_get_semTracePath(OrgContext* org_context, haxorg_OrgParseParameters __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_OrgParseParameters(OrgContext* org_context, haxorg_OrgParseParameters* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_OrgDirectoryParseParameters(OrgContext* org_context, haxorg_OrgDirectoryParseParameters* obj);
HAXORG_C_API_LINKAGE haxorg_ParseContext haxorg_create_ParseContext_ParseContextDefault(OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_ParseContext haxorg_create_ParseContext_ParseContextWithManager(OrgContext* org_context, haxorg_ParseSourceManager source);
HAXORG_C_API_LINKAGE haxorg_Cache haxorg_ParseContext_getDiagnosticStrings(OrgContext* org_context, haxorg_ParseContext __this);
HAXORG_C_API_LINKAGE haxorg_ParseSourceFileId haxorg_ParseContext_addSource_const(OrgContext* org_context, haxorg_ParseContext __this, haxorg_StdString path, haxorg_StdString content);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_ParseContext_parseFileOpts(OrgContext* org_context, haxorg_ParseContext __this, haxorg_StdString file, haxorg_OrgParseParameters opts);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_ParseContext_parseFile(OrgContext* org_context, haxorg_ParseContext __this, haxorg_StdString file);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_ParseContext_parseString(OrgContext* org_context, haxorg_ParseContext __this, haxorg_StdString text, haxorg_StdString file_name);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_ParseContext_parseStringOpts(OrgContext* org_context, haxorg_ParseContext __this, haxorg_StdString text, haxorg_StdString file_name, haxorg_OrgParseParameters opts);
HAXORG_C_API_LINKAGE haxorg_StdOptional haxorg_ParseContext_parseDirectory(OrgContext* org_context, haxorg_ParseContext __this, haxorg_StdString path);
HAXORG_C_API_LINKAGE haxorg_StdOptional haxorg_ParseContext_parseDirectoryOpts(OrgContext* org_context, haxorg_ParseContext __this, haxorg_StdString path, haxorg_OrgDirectoryParseParameters opts);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_ParseContext_parseFileWithIncludes(OrgContext* org_context, haxorg_ParseContext __this, haxorg_StdString file, haxorg_OrgDirectoryParseParameters opts);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfReport haxorg_ParseContext_collectDiagnostics(OrgContext* org_context, haxorg_ParseContext __this, haxorg_SemIdOfOrg tree, haxorg_Cache cache);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfSemIdOfErrorGroup haxorg_ParseContext_collectErrorNodes(OrgContext* org_context, haxorg_ParseContext __this, haxorg_SemIdOfOrg tree);
HAXORG_C_API_LINKAGE void haxorg_destroy_ParseContext(OrgContext* org_context, haxorg_ParseContext* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmReflFieldId_getName_const(OrgContext* org_context, haxorg_ImmReflFieldId __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmReflFieldId(OrgContext* org_context, haxorg_ImmReflFieldId* obj);
HAXORG_C_API_LINKAGE haxorg_OrgSemKind haxorg_ImmId_getKind_const(OrgContext* org_context, haxorg_ImmId __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmId_is_const(OrgContext* org_context, haxorg_ImmId __this, haxorg_OrgSemKind kind);
HAXORG_C_API_LINKAGE haxorg_ImmIdNodeIdxT haxorg_ImmId_getNodeIndex_const(OrgContext* org_context, haxorg_ImmId __this);
HAXORG_C_API_LINKAGE haxorg_StdString haxorg_ImmId_getReadableId_const(OrgContext* org_context, haxorg_ImmId __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmId(OrgContext* org_context, haxorg_ImmId* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmOrg(OrgContext* org_context, haxorg_ImmOrg* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmPathStep(OrgContext* org_context, haxorg_ImmPathStep* obj);
HAXORG_C_API_LINKAGE haxorg_ImmId haxorg_ImmPath_get_root(OrgContext* org_context, haxorg_ImmPath __this);
HAXORG_C_API_LINKAGE haxorg_ImmPathStore haxorg_ImmPath_get_path(OrgContext* org_context, haxorg_ImmPath __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmPath_empty_const(OrgContext* org_context, haxorg_ImmPath __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmPath(OrgContext* org_context, haxorg_ImmPath* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmUniqId(OrgContext* org_context, haxorg_ImmUniqId* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAstReplaceEpoch(OrgContext* org_context, haxorg_ImmAstReplaceEpoch* obj);
HAXORG_C_API_LINKAGE haxorg_ImmAstVersion haxorg_ImmAstContext_addRoot(OrgContext* org_context, haxorg_ImmAstContext __this, haxorg_SemIdOfOrg data);
HAXORG_C_API_LINKAGE haxorg_ImmAstVersion haxorg_ImmAstContext_getEmptyVersion(OrgContext* org_context, haxorg_ImmAstContext __this);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_ImmAstContext_get(OrgContext* org_context, haxorg_ImmAstContext __this, haxorg_ImmId id);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAstContext(OrgContext* org_context, haxorg_ImmAstContext* obj);
HAXORG_C_API_LINKAGE haxorg_ImmId haxorg_ImmAstVersion_getRoot_const(OrgContext* org_context, haxorg_ImmAstVersion __this);
HAXORG_C_API_LINKAGE haxorg_ImmAdapter haxorg_ImmAstVersion_getRootAdapter_const(OrgContext* org_context, haxorg_ImmAstVersion __this);
HAXORG_C_API_LINKAGE haxorg_ImmAstContext haxorg_ImmAstVersion_getContext_const(OrgContext* org_context, haxorg_ImmAstVersion __this);
HAXORG_C_API_LINKAGE haxorg_ImmAstReplaceEpoch haxorg_ImmAstVersion_getEpoch_const(OrgContext* org_context, haxorg_ImmAstVersion __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAstVersion(OrgContext* org_context, haxorg_ImmAstVersion* obj);
HAXORG_C_API_LINKAGE int haxorg_ImmAdapter_size_const(OrgContext* org_context, haxorg_ImmAdapter __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmAdapter_isNil_const(OrgContext* org_context, haxorg_ImmAdapter __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmAdapter_isRoot_const(OrgContext* org_context, haxorg_ImmAdapter __this);
HAXORG_C_API_LINKAGE haxorg_OrgSemKind haxorg_ImmAdapter_getKind_const(OrgContext* org_context, haxorg_ImmAdapter __this);
HAXORG_C_API_LINKAGE haxorg_ImmUniqId haxorg_ImmAdapter_uniq_const(OrgContext* org_context, haxorg_ImmAdapter __this);
HAXORG_C_API_LINKAGE haxorg_StdString haxorg_ImmAdapter_treeReprString_const(OrgContext* org_context, haxorg_ImmAdapter __this);
HAXORG_C_API_LINKAGE haxorg_StdString haxorg_ImmAdapter_treeReprStringOpts_const(OrgContext* org_context, haxorg_ImmAdapter __this, haxorg_ImmAdapterTreeReprConf conf);
HAXORG_C_API_LINKAGE bool haxorg_ImmAdapter_isDirectParentOf_const(OrgContext* org_context, haxorg_ImmAdapter __this, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE bool haxorg_ImmAdapter_isIndirectParentOf_const(OrgContext* org_context, haxorg_ImmAdapter __this, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE bool haxorg_ImmAdapter_isSubnodeOf_const(OrgContext* org_context, haxorg_ImmAdapter __this, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE haxorg_StdOptional haxorg_ImmAdapter_getParent_const(OrgContext* org_context, haxorg_ImmAdapter __this);
HAXORG_C_API_LINKAGE int haxorg_ImmAdapter_getSelfIndex_const(OrgContext* org_context, haxorg_ImmAdapter __this);
HAXORG_C_API_LINKAGE haxorg_ImmAdapter haxorg_ImmAdapter_atPathStep_const(OrgContext* org_context, haxorg_ImmAdapter __this, haxorg_ImmId id, haxorg_ImmPathStep idx);
HAXORG_C_API_LINKAGE haxorg_ImmAdapter haxorg_ImmAdapter_atField_const(OrgContext* org_context, haxorg_ImmAdapter __this, haxorg_ImmReflFieldId field);
HAXORG_C_API_LINKAGE haxorg_ImmAdapter haxorg_ImmAdapter_atIndex_const(OrgContext* org_context, haxorg_ImmAdapter __this, int idx, bool withPath);
HAXORG_C_API_LINKAGE haxorg_ImmAdapter haxorg_ImmAdapter_atPath_const(OrgContext* org_context, haxorg_ImmAdapter __this, haxorg_HstdVecOfInt path, bool withPath);
HAXORG_C_API_LINKAGE bool haxorg_ImmAdapter_is_const(OrgContext* org_context, haxorg_ImmAdapter __this, haxorg_OrgSemKind kind);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfImmAdapter haxorg_ImmAdapter_sub_const(OrgContext* org_context, haxorg_ImmAdapter __this, bool withPath);
HAXORG_C_API_LINKAGE int haxorg_ImmAdapterTreeReprConf_get_maxDepth(OrgContext* org_context, haxorg_ImmAdapterTreeReprConf __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmAdapterTreeReprConf_get_withAuxFields(OrgContext* org_context, haxorg_ImmAdapterTreeReprConf __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmAdapterTreeReprConf_get_withReflFields(OrgContext* org_context, haxorg_ImmAdapterTreeReprConf __this);
HAXORG_C_API_LINKAGE haxorg_HstdUnorderedSet haxorg_ImmAdapterTreeReprConf_get_withFieldSubset(OrgContext* org_context, haxorg_ImmAdapterTreeReprConf __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterTreeReprConf(OrgContext* org_context, haxorg_ImmAdapterTreeReprConf* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapter(OrgContext* org_context, haxorg_ImmAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterVirtualBase(OrgContext* org_context, haxorg_ImmAdapterVirtualBase* obj);
HAXORG_C_API_LINKAGE bool haxorg_OrgYamlExportOpts_get_skipNullFields(OrgContext* org_context, haxorg_OrgYamlExportOpts __this);
HAXORG_C_API_LINKAGE bool haxorg_OrgYamlExportOpts_get_skipFalseFields(OrgContext* org_context, haxorg_OrgYamlExportOpts __this);
HAXORG_C_API_LINKAGE bool haxorg_OrgYamlExportOpts_get_skipZeroFields(OrgContext* org_context, haxorg_OrgYamlExportOpts __this);
HAXORG_C_API_LINKAGE bool haxorg_OrgYamlExportOpts_get_skipLocation(OrgContext* org_context, haxorg_OrgYamlExportOpts __this);
HAXORG_C_API_LINKAGE bool haxorg_OrgYamlExportOpts_get_skipId(OrgContext* org_context, haxorg_OrgYamlExportOpts __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_OrgYamlExportOpts(OrgContext* org_context, haxorg_OrgYamlExportOpts* obj);
HAXORG_C_API_LINKAGE bool haxorg_OrgTreeExportOpts_get_withLineCol(OrgContext* org_context, haxorg_OrgTreeExportOpts __this);
HAXORG_C_API_LINKAGE bool haxorg_OrgTreeExportOpts_get_withOriginalId(OrgContext* org_context, haxorg_OrgTreeExportOpts __this);
HAXORG_C_API_LINKAGE bool haxorg_OrgTreeExportOpts_get_withSubnodeIdx(OrgContext* org_context, haxorg_OrgTreeExportOpts __this);
HAXORG_C_API_LINKAGE bool haxorg_OrgTreeExportOpts_get_skipEmptyFields(OrgContext* org_context, haxorg_OrgTreeExportOpts __this);
HAXORG_C_API_LINKAGE int haxorg_OrgTreeExportOpts_get_startLevel(OrgContext* org_context, haxorg_OrgTreeExportOpts __this);
HAXORG_C_API_LINKAGE bool haxorg_OrgTreeExportOpts_get_withColor(OrgContext* org_context, haxorg_OrgTreeExportOpts __this);
HAXORG_C_API_LINKAGE int haxorg_OrgTreeExportOpts_get_maxDepth(OrgContext* org_context, haxorg_OrgTreeExportOpts __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_OrgTreeExportOpts(OrgContext* org_context, haxorg_OrgTreeExportOpts* obj);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfSemIdOfOrg haxorg_AstTrackingPath_get_path(OrgContext* org_context, haxorg_AstTrackingPath __this);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_AstTrackingPath_getParent_const(OrgContext* org_context, haxorg_AstTrackingPath __this, int offset);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_AstTrackingPath_getNode_const(OrgContext* org_context, haxorg_AstTrackingPath __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_AstTrackingPath(OrgContext* org_context, haxorg_AstTrackingPath* obj);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfSemIdOfOrg haxorg_AstTrackingAlternatives_getAllNodes_const(OrgContext* org_context, haxorg_AstTrackingAlternatives __this);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_AstTrackingAlternatives_getNode_const(OrgContext* org_context, haxorg_AstTrackingAlternatives __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_AstTrackingAlternatives(OrgContext* org_context, haxorg_AstTrackingAlternatives* obj);
HAXORG_C_API_LINKAGE haxorg_AstTrackingGroupRadioTarget haxorg_AstTrackingGroup_getRadioTargetConst_const(OrgContext* org_context, haxorg_AstTrackingGroup __this);
HAXORG_C_API_LINKAGE haxorg_AstTrackingGroupTrackedHashtag haxorg_AstTrackingGroup_getTrackedHashtagConst_const(OrgContext* org_context, haxorg_AstTrackingGroup __this);
HAXORG_C_API_LINKAGE haxorg_AstTrackingGroupTrackedHashtag haxorg_AstTrackingGroup_getTrackedHashtagMut(OrgContext* org_context, haxorg_AstTrackingGroup __this);
HAXORG_C_API_LINKAGE haxorg_AstTrackingGroupSingle haxorg_AstTrackingGroup_getSingleConst_const(OrgContext* org_context, haxorg_AstTrackingGroup __this);
HAXORG_C_API_LINKAGE haxorg_AstTrackingGroupRadioTarget haxorg_AstTrackingGroup_getRadioTargetMut(OrgContext* org_context, haxorg_AstTrackingGroup __this);
HAXORG_C_API_LINKAGE haxorg_AstTrackingGroupSingle haxorg_AstTrackingGroup_getSingleMut(OrgContext* org_context, haxorg_AstTrackingGroup __this);
HAXORG_C_API_LINKAGE bool haxorg_AstTrackingGroup_isSingle_const(OrgContext* org_context, haxorg_AstTrackingGroup __this);
HAXORG_C_API_LINKAGE bool haxorg_AstTrackingGroup_isTrackedHashtag_const(OrgContext* org_context, haxorg_AstTrackingGroup __this);
HAXORG_C_API_LINKAGE bool haxorg_AstTrackingGroup_isRadioTarget_const(OrgContext* org_context, haxorg_AstTrackingGroup __this);
HAXORG_C_API_LINKAGE haxorg_AstTrackingPath haxorg_AstTrackingGroupRadioTarget_get_target(OrgContext* org_context, haxorg_AstTrackingGroupRadioTarget __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfSemIdOfOrg haxorg_AstTrackingGroupRadioTarget_get_nodes(OrgContext* org_context, haxorg_AstTrackingGroupRadioTarget __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_AstTrackingGroupRadioTarget(OrgContext* org_context, haxorg_AstTrackingGroupRadioTarget* obj);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_AstTrackingGroupSingle_get_node(OrgContext* org_context, haxorg_AstTrackingGroupSingle __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_AstTrackingGroupSingle(OrgContext* org_context, haxorg_AstTrackingGroupSingle* obj);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_AstTrackingGroupTrackedHashtag_get_tag(OrgContext* org_context, haxorg_AstTrackingGroupTrackedHashtag __this);
HAXORG_C_API_LINKAGE haxorg_HstdMap haxorg_AstTrackingGroupTrackedHashtag_get_targets(OrgContext* org_context, haxorg_AstTrackingGroupTrackedHashtag __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_AstTrackingGroupTrackedHashtag(OrgContext* org_context, haxorg_AstTrackingGroupTrackedHashtag* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_AstTrackingGroup(OrgContext* org_context, haxorg_AstTrackingGroup* obj);
HAXORG_C_API_LINKAGE haxorg_HstdMap haxorg_AstTrackingMap_get_footnotes(OrgContext* org_context, haxorg_AstTrackingMap __this);
HAXORG_C_API_LINKAGE haxorg_HstdMap haxorg_AstTrackingMap_get_subtrees(OrgContext* org_context, haxorg_AstTrackingMap __this);
HAXORG_C_API_LINKAGE haxorg_HstdMap haxorg_AstTrackingMap_get_names(OrgContext* org_context, haxorg_AstTrackingMap __this);
HAXORG_C_API_LINKAGE haxorg_HstdMap haxorg_AstTrackingMap_get_anchorTargets(OrgContext* org_context, haxorg_AstTrackingMap __this);
HAXORG_C_API_LINKAGE haxorg_HstdMap haxorg_AstTrackingMap_get_radioTargets(OrgContext* org_context, haxorg_AstTrackingMap __this);
HAXORG_C_API_LINKAGE haxorg_HstdMap haxorg_AstTrackingMap_get_hashtagDefinitions(OrgContext* org_context, haxorg_AstTrackingMap __this);
HAXORG_C_API_LINKAGE haxorg_StdOptional haxorg_AstTrackingMap_getIdPath_const(OrgContext* org_context, haxorg_AstTrackingMap __this, haxorg_HstdStr id);
HAXORG_C_API_LINKAGE haxorg_StdOptional haxorg_AstTrackingMap_getNamePath_const(OrgContext* org_context, haxorg_AstTrackingMap __this, haxorg_HstdStr id);
HAXORG_C_API_LINKAGE haxorg_StdOptional haxorg_AstTrackingMap_getAnchorTarget_const(OrgContext* org_context, haxorg_AstTrackingMap __this, haxorg_HstdStr id);
HAXORG_C_API_LINKAGE haxorg_StdOptional haxorg_AstTrackingMap_getFootnotePath_const(OrgContext* org_context, haxorg_AstTrackingMap __this, haxorg_HstdStr id);
HAXORG_C_API_LINKAGE void haxorg_destroy_AstTrackingMap(OrgContext* org_context, haxorg_AstTrackingMap* obj);
HAXORG_C_API_LINKAGE int haxorg_SequenceSegment_get_kind(OrgContext* org_context, haxorg_SequenceSegment __this);
HAXORG_C_API_LINKAGE int haxorg_SequenceSegment_get_first(OrgContext* org_context, haxorg_SequenceSegment __this);
HAXORG_C_API_LINKAGE int haxorg_SequenceSegment_get_last(OrgContext* org_context, haxorg_SequenceSegment __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_SequenceSegment(OrgContext* org_context, haxorg_SequenceSegment* obj);
HAXORG_C_API_LINKAGE int haxorg_SequenceSegmentGroup_get_kind(OrgContext* org_context, haxorg_SequenceSegmentGroup __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfSequenceSegment haxorg_SequenceSegmentGroup_get_segments(OrgContext* org_context, haxorg_SequenceSegmentGroup __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_SequenceSegmentGroup(OrgContext* org_context, haxorg_SequenceSegmentGroup* obj);
HAXORG_C_API_LINKAGE int haxorg_SequenceAnnotationTag_get_groupKind(OrgContext* org_context, haxorg_SequenceAnnotationTag __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfInt haxorg_SequenceAnnotationTag_get_segmentKinds(OrgContext* org_context, haxorg_SequenceAnnotationTag __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_SequenceAnnotationTag(OrgContext* org_context, haxorg_SequenceAnnotationTag* obj);
HAXORG_C_API_LINKAGE int haxorg_SequenceAnnotation_get_first(OrgContext* org_context, haxorg_SequenceAnnotation __this);
HAXORG_C_API_LINKAGE int haxorg_SequenceAnnotation_get_last(OrgContext* org_context, haxorg_SequenceAnnotation __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfSequenceAnnotationTag haxorg_SequenceAnnotation_get_annotations(OrgContext* org_context, haxorg_SequenceAnnotation __this);
HAXORG_C_API_LINKAGE bool haxorg_SequenceAnnotation_isAnnotatedWith_const(OrgContext* org_context, haxorg_SequenceAnnotation __this, int groupKind, int segmentKind);
HAXORG_C_API_LINKAGE void haxorg_destroy_SequenceAnnotation(OrgContext* org_context, haxorg_SequenceAnnotation* obj);
HAXORG_C_API_LINKAGE haxorg_GraphMapLinkRadio haxorg_GraphMapLink_getRadio(OrgContext* org_context, haxorg_GraphMapLink __this);
HAXORG_C_API_LINKAGE haxorg_GraphMapLinkRadio haxorg_GraphMapLink_getRadio_const(OrgContext* org_context, haxorg_GraphMapLink __this);
HAXORG_C_API_LINKAGE bool haxorg_GraphMapLink_isRadio_const(OrgContext* org_context, haxorg_GraphMapLink __this);
HAXORG_C_API_LINKAGE haxorg_GraphMapLinkLink haxorg_GraphMapLink_getLink(OrgContext* org_context, haxorg_GraphMapLink __this);
HAXORG_C_API_LINKAGE haxorg_GraphMapLinkLink haxorg_GraphMapLink_getLink_const(OrgContext* org_context, haxorg_GraphMapLink __this);
HAXORG_C_API_LINKAGE bool haxorg_GraphMapLink_isLink_const(OrgContext* org_context, haxorg_GraphMapLink __this);
HAXORG_C_API_LINKAGE haxorg_GraphMapLinkKind haxorg_GraphMapLink_getKind_const(OrgContext* org_context, haxorg_GraphMapLink __this);
HAXORG_C_API_LINKAGE haxorg_ImmUniqId haxorg_GraphMapLinkLink_get_link(OrgContext* org_context, haxorg_GraphMapLinkLink __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfImmUniqId haxorg_GraphMapLinkLink_get_description(OrgContext* org_context, haxorg_GraphMapLinkLink __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_GraphMapLinkLink(OrgContext* org_context, haxorg_GraphMapLinkLink* obj);
HAXORG_C_API_LINKAGE haxorg_ImmUniqId haxorg_GraphMapLinkRadio_get_target(OrgContext* org_context, haxorg_GraphMapLinkRadio __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_GraphMapLinkRadio(OrgContext* org_context, haxorg_GraphMapLinkRadio* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_GraphMapLink(OrgContext* org_context, haxorg_GraphMapLink* obj);
HAXORG_C_API_LINKAGE haxorg_ImmUniqId haxorg_GraphMapNodeProp_get_id(OrgContext* org_context, haxorg_GraphMapNodeProp __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfGraphMapLink haxorg_GraphMapNodeProp_get_unresolved(OrgContext* org_context, haxorg_GraphMapNodeProp __this);
HAXORG_C_API_LINKAGE haxorg_ImmAdapter haxorg_GraphMapNodeProp_getAdapter_const(OrgContext* org_context, haxorg_GraphMapNodeProp __this, haxorg_ImmAstContext context);
HAXORG_C_API_LINKAGE haxorg_StdOptional haxorg_GraphMapNodeProp_getSubtreeId_const(OrgContext* org_context, haxorg_GraphMapNodeProp __this, haxorg_ImmAstContext context);
HAXORG_C_API_LINKAGE haxorg_StdOptional haxorg_GraphMapNodeProp_getFootnoteName_const(OrgContext* org_context, haxorg_GraphMapNodeProp __this, haxorg_ImmAstContext context);
HAXORG_C_API_LINKAGE void haxorg_destroy_GraphMapNodeProp(OrgContext* org_context, haxorg_GraphMapNodeProp* obj);
HAXORG_C_API_LINKAGE haxorg_GraphMapLink haxorg_GraphMapEdgeProp_get_link(OrgContext* org_context, haxorg_GraphMapEdgeProp __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_GraphMapEdgeProp(OrgContext* org_context, haxorg_GraphMapEdgeProp* obj);
HAXORG_C_API_LINKAGE haxorg_ImmUniqId haxorg_GraphMapNode_get_id(OrgContext* org_context, haxorg_GraphMapNode __this);
HAXORG_C_API_LINKAGE bool haxorg_GraphMapNode___eq___const(OrgContext* org_context, haxorg_GraphMapNode __this, haxorg_GraphMapNode other);
HAXORG_C_API_LINKAGE bool haxorg_GraphMapNode___lt___const(OrgContext* org_context, haxorg_GraphMapNode __this, haxorg_GraphMapNode other);
HAXORG_C_API_LINKAGE void haxorg_destroy_GraphMapNode(OrgContext* org_context, haxorg_GraphMapNode* obj);
HAXORG_C_API_LINKAGE haxorg_GraphMapNode haxorg_GraphMapEdge_get_source(OrgContext* org_context, haxorg_GraphMapEdge __this);
HAXORG_C_API_LINKAGE haxorg_GraphMapNode haxorg_GraphMapEdge_get_target(OrgContext* org_context, haxorg_GraphMapEdge __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_GraphMapEdge(OrgContext* org_context, haxorg_GraphMapEdge* obj);
HAXORG_C_API_LINKAGE haxorg_GraphNodeProps haxorg_GraphMapGraph_get_nodeProps(OrgContext* org_context, haxorg_GraphMapGraph __this);
HAXORG_C_API_LINKAGE haxorg_GraphEdgeProps haxorg_GraphMapGraph_get_edgeProps(OrgContext* org_context, haxorg_GraphMapGraph __this);
HAXORG_C_API_LINKAGE haxorg_GraphAdjList haxorg_GraphMapGraph_get_adjList(OrgContext* org_context, haxorg_GraphMapGraph __this);
HAXORG_C_API_LINKAGE haxorg_GraphAdjList haxorg_GraphMapGraph_get_adjListIn(OrgContext* org_context, haxorg_GraphMapGraph __this);
HAXORG_C_API_LINKAGE int haxorg_GraphMapGraph_nodeCount_const(OrgContext* org_context, haxorg_GraphMapGraph __this);
HAXORG_C_API_LINKAGE int haxorg_GraphMapGraph_edgeCount_const(OrgContext* org_context, haxorg_GraphMapGraph __this);
HAXORG_C_API_LINKAGE haxorg_GraphAdjNodesList haxorg_GraphMapGraph_outNodes_const(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapNode node);
HAXORG_C_API_LINKAGE haxorg_GraphAdjNodesList haxorg_GraphMapGraph_inNodes_const(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapNode node);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfGraphMapEdge haxorg_GraphMapGraph_adjEdges_const(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapNode node);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfGraphMapNode haxorg_GraphMapGraph_adjNodes_const(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapNode node);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfGraphMapEdge haxorg_GraphMapGraph_outEdges_const(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapNode node);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfGraphMapEdge haxorg_GraphMapGraph_inEdges_const(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapNode node);
HAXORG_C_API_LINKAGE int haxorg_GraphMapGraph_outDegree_const(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapNode node);
HAXORG_C_API_LINKAGE int haxorg_GraphMapGraph_inDegree_const(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapNode node);
HAXORG_C_API_LINKAGE bool haxorg_GraphMapGraph_isRegisteredNode_const(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapNode id);
HAXORG_C_API_LINKAGE bool haxorg_GraphMapGraph_isRegisteredNodeById_const(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_ImmUniqId id);
HAXORG_C_API_LINKAGE haxorg_GraphMapNodeProp haxorg_GraphMapGraph_atMapNode_const(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapNode node);
HAXORG_C_API_LINKAGE haxorg_GraphMapEdgeProp haxorg_GraphMapGraph_atMapEdge_const(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapEdge edge);
HAXORG_C_API_LINKAGE void haxorg_GraphMapGraph_addEdge(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapEdge edge);
HAXORG_C_API_LINKAGE void haxorg_GraphMapGraph_addEdgeWithProp(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapEdge edge, haxorg_GraphMapEdgeProp prop);
HAXORG_C_API_LINKAGE void haxorg_GraphMapGraph_addNode(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapNode node);
HAXORG_C_API_LINKAGE void haxorg_GraphMapGraph_addNodeWithProp(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapNode node, haxorg_GraphMapNodeProp prop);
HAXORG_C_API_LINKAGE bool haxorg_GraphMapGraph_hasEdge_const(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapNode source, haxorg_GraphMapNode target);
HAXORG_C_API_LINKAGE bool haxorg_GraphMapGraph_hasNode_const(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapNode node);
HAXORG_C_API_LINKAGE bool haxorg_GraphMapGraph_has2AdapterEdge_const(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_ImmAdapter source, haxorg_ImmAdapter target);
HAXORG_C_API_LINKAGE void haxorg_destroy_GraphMapGraph(OrgContext* org_context, haxorg_GraphMapGraph* obj);
HAXORG_C_API_LINKAGE haxorg_OperationsTracer haxorg_GraphMapConfig_get_dbg(OrgContext* org_context, haxorg_GraphMapConfig __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_GraphMapConfig(OrgContext* org_context, haxorg_GraphMapConfig* obj);
HAXORG_C_API_LINKAGE haxorg_GraphMapGraph haxorg_GraphMapGraphState_get_graph(OrgContext* org_context, haxorg_GraphMapGraphState __this);
HAXORG_C_API_LINKAGE haxorg_ImmAstContext haxorg_GraphMapGraphState_get_ast(OrgContext* org_context, haxorg_GraphMapGraphState __this);
HAXORG_C_API_LINKAGE haxorg_GraphMapGraph haxorg_GraphMapGraphState_getGraph_const(OrgContext* org_context, haxorg_GraphMapGraphState __this);
HAXORG_C_API_LINKAGE haxorg_GraphMapGraphState haxorg_GraphMapGraphState_FromAstContext(OrgContext* org_context, haxorg_ImmAstContext ast);
HAXORG_C_API_LINKAGE void haxorg_GraphMapGraphState_registerNode(OrgContext* org_context, haxorg_GraphMapGraphState __this, haxorg_GraphMapNodeProp node, haxorg_GraphMapConfig conf);
HAXORG_C_API_LINKAGE void haxorg_GraphMapGraphState_addNode(OrgContext* org_context, haxorg_GraphMapGraphState __this, haxorg_ImmAdapter node, haxorg_GraphMapConfig conf);
HAXORG_C_API_LINKAGE void haxorg_GraphMapGraphState_addNodeRec(OrgContext* org_context, haxorg_GraphMapGraphState __this, haxorg_ImmAstContext ast, haxorg_ImmAdapter node, haxorg_GraphMapConfig conf);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfGraphMapLink haxorg_GraphMapGraphState_getUnresolvedSubtreeLinks_const(OrgContext* org_context, haxorg_GraphMapGraphState __this, haxorg_ImmSubtreeAdapter node, haxorg_GraphMapConfig conf);
HAXORG_C_API_LINKAGE haxorg_StdOptional haxorg_GraphMapGraphState_getUnresolvedLink_const(OrgContext* org_context, haxorg_GraphMapGraphState __this, haxorg_ImmLinkAdapter node, haxorg_GraphMapConfig conf);
HAXORG_C_API_LINKAGE void haxorg_destroy_GraphMapGraphState(OrgContext* org_context, haxorg_GraphMapGraphState* obj);
HAXORG_C_API_LINKAGE void haxorg_create_LispCode_LispCode(OrgContext* org_context);
HAXORG_C_API_LINKAGE bool haxorg_LispCode___eq___const(OrgContext* org_context, haxorg_LispCode __this, haxorg_LispCode other);
HAXORG_C_API_LINKAGE bool haxorg_LispCode_isCall_const(OrgContext* org_context, haxorg_LispCode __this);
HAXORG_C_API_LINKAGE haxorg_LispCodeCall haxorg_LispCode_getCallConst_const(OrgContext* org_context, haxorg_LispCode __this);
HAXORG_C_API_LINKAGE haxorg_LispCodeCall haxorg_LispCode_getCallMut(OrgContext* org_context, haxorg_LispCode __this);
HAXORG_C_API_LINKAGE bool haxorg_LispCode_isList_const(OrgContext* org_context, haxorg_LispCode __this);
HAXORG_C_API_LINKAGE haxorg_LispCodeList haxorg_LispCode_getListConst_const(OrgContext* org_context, haxorg_LispCode __this);
HAXORG_C_API_LINKAGE haxorg_LispCodeList haxorg_LispCode_getListMut(OrgContext* org_context, haxorg_LispCode __this);
HAXORG_C_API_LINKAGE bool haxorg_LispCode_isKeyValue_const(OrgContext* org_context, haxorg_LispCode __this);
HAXORG_C_API_LINKAGE haxorg_LispCodeKeyValue haxorg_LispCode_getKeyValueConst_const(OrgContext* org_context, haxorg_LispCode __this);
HAXORG_C_API_LINKAGE haxorg_LispCodeKeyValue haxorg_LispCode_getKeyValueMut(OrgContext* org_context, haxorg_LispCode __this);
HAXORG_C_API_LINKAGE bool haxorg_LispCode_isNumber_const(OrgContext* org_context, haxorg_LispCode __this);
HAXORG_C_API_LINKAGE haxorg_LispCodeNumber haxorg_LispCode_getNumberConst_const(OrgContext* org_context, haxorg_LispCode __this);
HAXORG_C_API_LINKAGE haxorg_LispCodeNumber haxorg_LispCode_getNumberMut(OrgContext* org_context, haxorg_LispCode __this);
HAXORG_C_API_LINKAGE bool haxorg_LispCode_isText_const(OrgContext* org_context, haxorg_LispCode __this);
HAXORG_C_API_LINKAGE haxorg_LispCodeText haxorg_LispCode_getTextConst_const(OrgContext* org_context, haxorg_LispCode __this);
HAXORG_C_API_LINKAGE haxorg_LispCodeText haxorg_LispCode_getTextMut(OrgContext* org_context, haxorg_LispCode __this);
HAXORG_C_API_LINKAGE bool haxorg_LispCode_isIdent_const(OrgContext* org_context, haxorg_LispCode __this);
HAXORG_C_API_LINKAGE haxorg_LispCodeIdent haxorg_LispCode_getIdentConst_const(OrgContext* org_context, haxorg_LispCode __this);
HAXORG_C_API_LINKAGE haxorg_LispCodeIdent haxorg_LispCode_getIdentMut(OrgContext* org_context, haxorg_LispCode __this);
HAXORG_C_API_LINKAGE bool haxorg_LispCode_isBoolean_const(OrgContext* org_context, haxorg_LispCode __this);
HAXORG_C_API_LINKAGE haxorg_LispCodeBoolean haxorg_LispCode_getBooleanConst_const(OrgContext* org_context, haxorg_LispCode __this);
HAXORG_C_API_LINKAGE haxorg_LispCodeBoolean haxorg_LispCode_getBooleanMut(OrgContext* org_context, haxorg_LispCode __this);
HAXORG_C_API_LINKAGE bool haxorg_LispCode_isReal_const(OrgContext* org_context, haxorg_LispCode __this);
HAXORG_C_API_LINKAGE haxorg_LispCodeReal haxorg_LispCode_getRealConst_const(OrgContext* org_context, haxorg_LispCode __this);
HAXORG_C_API_LINKAGE haxorg_LispCodeReal haxorg_LispCode_getRealMut(OrgContext* org_context, haxorg_LispCode __this);
HAXORG_C_API_LINKAGE haxorg_LispCodeKind haxorg_LispCode_getKind_const(OrgContext* org_context, haxorg_LispCode __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_LispCodeCall_get_name(OrgContext* org_context, haxorg_LispCodeCall __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfLispCode haxorg_LispCodeCall_get_args(OrgContext* org_context, haxorg_LispCodeCall __this);
HAXORG_C_API_LINKAGE void haxorg_create_LispCodeCall_Call(OrgContext* org_context);
HAXORG_C_API_LINKAGE bool haxorg_LispCodeCall___eq___const(OrgContext* org_context, haxorg_LispCodeCall __this, haxorg_LispCodeCall other);
HAXORG_C_API_LINKAGE void haxorg_destroy_LispCodeCall(OrgContext* org_context, haxorg_LispCodeCall* obj);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfLispCode haxorg_LispCodeList_get_items(OrgContext* org_context, haxorg_LispCodeList __this);
HAXORG_C_API_LINKAGE void haxorg_create_LispCodeList_List(OrgContext* org_context);
HAXORG_C_API_LINKAGE bool haxorg_LispCodeList___eq___const(OrgContext* org_context, haxorg_LispCodeList __this, haxorg_LispCodeList other);
HAXORG_C_API_LINKAGE void haxorg_destroy_LispCodeList(OrgContext* org_context, haxorg_LispCodeList* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_LispCodeKeyValue_get_name(OrgContext* org_context, haxorg_LispCodeKeyValue __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfLispCode haxorg_LispCodeKeyValue_get_value(OrgContext* org_context, haxorg_LispCodeKeyValue __this);
HAXORG_C_API_LINKAGE void haxorg_create_LispCodeKeyValue_KeyValue(OrgContext* org_context);
HAXORG_C_API_LINKAGE bool haxorg_LispCodeKeyValue___eq___const(OrgContext* org_context, haxorg_LispCodeKeyValue __this, haxorg_LispCodeKeyValue other);
HAXORG_C_API_LINKAGE void haxorg_destroy_LispCodeKeyValue(OrgContext* org_context, haxorg_LispCodeKeyValue* obj);
HAXORG_C_API_LINKAGE int haxorg_LispCodeNumber_get_value(OrgContext* org_context, haxorg_LispCodeNumber __this);
HAXORG_C_API_LINKAGE void haxorg_create_LispCodeNumber_Number(OrgContext* org_context);
HAXORG_C_API_LINKAGE bool haxorg_LispCodeNumber___eq___const(OrgContext* org_context, haxorg_LispCodeNumber __this, haxorg_LispCodeNumber other);
HAXORG_C_API_LINKAGE void haxorg_destroy_LispCodeNumber(OrgContext* org_context, haxorg_LispCodeNumber* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_LispCodeText_get_value(OrgContext* org_context, haxorg_LispCodeText __this);
HAXORG_C_API_LINKAGE void haxorg_create_LispCodeText_Text(OrgContext* org_context);
HAXORG_C_API_LINKAGE bool haxorg_LispCodeText___eq___const(OrgContext* org_context, haxorg_LispCodeText __this, haxorg_LispCodeText other);
HAXORG_C_API_LINKAGE void haxorg_destroy_LispCodeText(OrgContext* org_context, haxorg_LispCodeText* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_LispCodeIdent_get_name(OrgContext* org_context, haxorg_LispCodeIdent __this);
HAXORG_C_API_LINKAGE void haxorg_create_LispCodeIdent_Ident(OrgContext* org_context);
HAXORG_C_API_LINKAGE bool haxorg_LispCodeIdent___eq___const(OrgContext* org_context, haxorg_LispCodeIdent __this, haxorg_LispCodeIdent other);
HAXORG_C_API_LINKAGE void haxorg_destroy_LispCodeIdent(OrgContext* org_context, haxorg_LispCodeIdent* obj);
HAXORG_C_API_LINKAGE bool haxorg_LispCodeBoolean_get_value(OrgContext* org_context, haxorg_LispCodeBoolean __this);
HAXORG_C_API_LINKAGE void haxorg_create_LispCodeBoolean_Boolean(OrgContext* org_context);
HAXORG_C_API_LINKAGE bool haxorg_LispCodeBoolean___eq___const(OrgContext* org_context, haxorg_LispCodeBoolean __this, haxorg_LispCodeBoolean other);
HAXORG_C_API_LINKAGE void haxorg_destroy_LispCodeBoolean(OrgContext* org_context, haxorg_LispCodeBoolean* obj);
HAXORG_C_API_LINKAGE float haxorg_LispCodeReal_get_value(OrgContext* org_context, haxorg_LispCodeReal __this);
HAXORG_C_API_LINKAGE void haxorg_create_LispCodeReal_Real(OrgContext* org_context);
HAXORG_C_API_LINKAGE bool haxorg_LispCodeReal___eq___const(OrgContext* org_context, haxorg_LispCodeReal __this, haxorg_LispCodeReal other);
HAXORG_C_API_LINKAGE void haxorg_destroy_LispCodeReal(OrgContext* org_context, haxorg_LispCodeReal* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_LispCode(OrgContext* org_context, haxorg_LispCode* obj);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfTblfmAssign haxorg_Tblfm_get_exprs(OrgContext* org_context, haxorg_Tblfm __this);
HAXORG_C_API_LINKAGE bool haxorg_Tblfm___eq___const(OrgContext* org_context, haxorg_Tblfm __this, haxorg_Tblfm other);
HAXORG_C_API_LINKAGE bool haxorg_TblfmExpr___eq___const(OrgContext* org_context, haxorg_TblfmExpr __this, haxorg_TblfmExpr other);
HAXORG_C_API_LINKAGE bool haxorg_TblfmExpr_isAxisRef_const(OrgContext* org_context, haxorg_TblfmExpr __this);
HAXORG_C_API_LINKAGE haxorg_TblfmExprAxisRef haxorg_TblfmExpr_getAxisRefConst_const(OrgContext* org_context, haxorg_TblfmExpr __this);
HAXORG_C_API_LINKAGE haxorg_TblfmExprAxisRef haxorg_TblfmExpr_getAxisRefMut(OrgContext* org_context, haxorg_TblfmExpr __this);
HAXORG_C_API_LINKAGE bool haxorg_TblfmExpr_isAxisName_const(OrgContext* org_context, haxorg_TblfmExpr __this);
HAXORG_C_API_LINKAGE haxorg_TblfmExprAxisName haxorg_TblfmExpr_getAxisNameConst_const(OrgContext* org_context, haxorg_TblfmExpr __this);
HAXORG_C_API_LINKAGE haxorg_TblfmExprAxisName haxorg_TblfmExpr_getAxisNameMut(OrgContext* org_context, haxorg_TblfmExpr __this);
HAXORG_C_API_LINKAGE bool haxorg_TblfmExpr_isIntLiteral_const(OrgContext* org_context, haxorg_TblfmExpr __this);
HAXORG_C_API_LINKAGE haxorg_TblfmExprIntLiteral haxorg_TblfmExpr_getIntLiteralConst_const(OrgContext* org_context, haxorg_TblfmExpr __this);
HAXORG_C_API_LINKAGE haxorg_TblfmExprIntLiteral haxorg_TblfmExpr_getIntLiteralMut(OrgContext* org_context, haxorg_TblfmExpr __this);
HAXORG_C_API_LINKAGE bool haxorg_TblfmExpr_isFloatLiteral_const(OrgContext* org_context, haxorg_TblfmExpr __this);
HAXORG_C_API_LINKAGE haxorg_TblfmExprFloatLiteral haxorg_TblfmExpr_getFloatLiteralConst_const(OrgContext* org_context, haxorg_TblfmExpr __this);
HAXORG_C_API_LINKAGE haxorg_TblfmExprFloatLiteral haxorg_TblfmExpr_getFloatLiteralMut(OrgContext* org_context, haxorg_TblfmExpr __this);
HAXORG_C_API_LINKAGE bool haxorg_TblfmExpr_isRangeRef_const(OrgContext* org_context, haxorg_TblfmExpr __this);
HAXORG_C_API_LINKAGE haxorg_TblfmExprRangeRef haxorg_TblfmExpr_getRangeRefConst_const(OrgContext* org_context, haxorg_TblfmExpr __this);
HAXORG_C_API_LINKAGE haxorg_TblfmExprRangeRef haxorg_TblfmExpr_getRangeRefMut(OrgContext* org_context, haxorg_TblfmExpr __this);
HAXORG_C_API_LINKAGE bool haxorg_TblfmExpr_isCall_const(OrgContext* org_context, haxorg_TblfmExpr __this);
HAXORG_C_API_LINKAGE haxorg_TblfmExprCall haxorg_TblfmExpr_getCallConst_const(OrgContext* org_context, haxorg_TblfmExpr __this);
HAXORG_C_API_LINKAGE haxorg_TblfmExprCall haxorg_TblfmExpr_getCallMut(OrgContext* org_context, haxorg_TblfmExpr __this);
HAXORG_C_API_LINKAGE bool haxorg_TblfmExpr_isElisp_const(OrgContext* org_context, haxorg_TblfmExpr __this);
HAXORG_C_API_LINKAGE haxorg_TblfmExprElisp haxorg_TblfmExpr_getElispConst_const(OrgContext* org_context, haxorg_TblfmExpr __this);
HAXORG_C_API_LINKAGE haxorg_TblfmExprElisp haxorg_TblfmExpr_getElispMut(OrgContext* org_context, haxorg_TblfmExpr __this);
HAXORG_C_API_LINKAGE haxorg_TblfmExprKind haxorg_TblfmExpr_getKind_const(OrgContext* org_context, haxorg_TblfmExpr __this);
HAXORG_C_API_LINKAGE haxorg_TblfmExprAxisRefPosition haxorg_TblfmExprAxisRef_get_col(OrgContext* org_context, haxorg_TblfmExprAxisRef __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_TblfmExprAxisRef_get_row(OrgContext* org_context, haxorg_TblfmExprAxisRef __this);
HAXORG_C_API_LINKAGE bool haxorg_TblfmExprAxisRef___eq___const(OrgContext* org_context, haxorg_TblfmExprAxisRef __this, haxorg_TblfmExprAxisRef other);
HAXORG_C_API_LINKAGE void haxorg_create_TblfmExprAxisRefPosition_Position(OrgContext* org_context);
HAXORG_C_API_LINKAGE bool haxorg_TblfmExprAxisRefPosition___eq___const(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition __this, haxorg_TblfmExprAxisRefPosition other);
HAXORG_C_API_LINKAGE bool haxorg_TblfmExprAxisRefPosition_isIndex_const(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition __this);
HAXORG_C_API_LINKAGE haxorg_TblfmExprAxisRefPositionIndex haxorg_TblfmExprAxisRefPosition_getIndexConst_const(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition __this);
HAXORG_C_API_LINKAGE haxorg_TblfmExprAxisRefPositionIndex haxorg_TblfmExprAxisRefPosition_getIndexMut(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition __this);
HAXORG_C_API_LINKAGE bool haxorg_TblfmExprAxisRefPosition_isName_const(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition __this);
HAXORG_C_API_LINKAGE haxorg_TblfmExprAxisRefPositionName haxorg_TblfmExprAxisRefPosition_getNameConst_const(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition __this);
HAXORG_C_API_LINKAGE haxorg_TblfmExprAxisRefPositionName haxorg_TblfmExprAxisRefPosition_getNameMut(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition __this);
HAXORG_C_API_LINKAGE haxorg_TblfmExprAxisRefPositionKind haxorg_TblfmExprAxisRefPosition_getKind_const(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition __this);
HAXORG_C_API_LINKAGE int haxorg_TblfmExprAxisRefPositionIndex_get_index(OrgContext* org_context, haxorg_TblfmExprAxisRefPositionIndex __this);
HAXORG_C_API_LINKAGE void haxorg_create_TblfmExprAxisRefPositionIndex_Index(OrgContext* org_context);
HAXORG_C_API_LINKAGE bool haxorg_TblfmExprAxisRefPositionIndex___eq___const(OrgContext* org_context, haxorg_TblfmExprAxisRefPositionIndex __this, haxorg_TblfmExprAxisRefPositionIndex other);
HAXORG_C_API_LINKAGE void haxorg_destroy_TblfmExprAxisRefPositionIndex(OrgContext* org_context, haxorg_TblfmExprAxisRefPositionIndex* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_TblfmExprAxisRefPositionName_get_name(OrgContext* org_context, haxorg_TblfmExprAxisRefPositionName __this);
HAXORG_C_API_LINKAGE void haxorg_create_TblfmExprAxisRefPositionName_Name(OrgContext* org_context);
HAXORG_C_API_LINKAGE bool haxorg_TblfmExprAxisRefPositionName___eq___const(OrgContext* org_context, haxorg_TblfmExprAxisRefPositionName __this, haxorg_TblfmExprAxisRefPositionName other);
HAXORG_C_API_LINKAGE void haxorg_destroy_TblfmExprAxisRefPositionName(OrgContext* org_context, haxorg_TblfmExprAxisRefPositionName* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_TblfmExprAxisRefPosition(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_TblfmExprAxisRef(OrgContext* org_context, haxorg_TblfmExprAxisRef* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_TblfmExprAxisName_get_name(OrgContext* org_context, haxorg_TblfmExprAxisName __this);
HAXORG_C_API_LINKAGE bool haxorg_TblfmExprAxisName___eq___const(OrgContext* org_context, haxorg_TblfmExprAxisName __this, haxorg_TblfmExprAxisName other);
HAXORG_C_API_LINKAGE void haxorg_destroy_TblfmExprAxisName(OrgContext* org_context, haxorg_TblfmExprAxisName* obj);
HAXORG_C_API_LINKAGE int haxorg_TblfmExprIntLiteral_get_value(OrgContext* org_context, haxorg_TblfmExprIntLiteral __this);
HAXORG_C_API_LINKAGE bool haxorg_TblfmExprIntLiteral___eq___const(OrgContext* org_context, haxorg_TblfmExprIntLiteral __this, haxorg_TblfmExprIntLiteral other);
HAXORG_C_API_LINKAGE void haxorg_destroy_TblfmExprIntLiteral(OrgContext* org_context, haxorg_TblfmExprIntLiteral* obj);
HAXORG_C_API_LINKAGE float haxorg_TblfmExprFloatLiteral_get_value(OrgContext* org_context, haxorg_TblfmExprFloatLiteral __this);
HAXORG_C_API_LINKAGE bool haxorg_TblfmExprFloatLiteral___eq___const(OrgContext* org_context, haxorg_TblfmExprFloatLiteral __this, haxorg_TblfmExprFloatLiteral other);
HAXORG_C_API_LINKAGE void haxorg_destroy_TblfmExprFloatLiteral(OrgContext* org_context, haxorg_TblfmExprFloatLiteral* obj);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_TblfmExprRangeRef_get_first(OrgContext* org_context, haxorg_TblfmExprRangeRef __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_TblfmExprRangeRef_get_last(OrgContext* org_context, haxorg_TblfmExprRangeRef __this);
HAXORG_C_API_LINKAGE bool haxorg_TblfmExprRangeRef___eq___const(OrgContext* org_context, haxorg_TblfmExprRangeRef __this, haxorg_TblfmExprRangeRef other);
HAXORG_C_API_LINKAGE void haxorg_destroy_TblfmExprRangeRef(OrgContext* org_context, haxorg_TblfmExprRangeRef* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_TblfmExprCall_get_name(OrgContext* org_context, haxorg_TblfmExprCall __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfTblfmExpr haxorg_TblfmExprCall_get_args(OrgContext* org_context, haxorg_TblfmExprCall __this);
HAXORG_C_API_LINKAGE bool haxorg_TblfmExprCall___eq___const(OrgContext* org_context, haxorg_TblfmExprCall __this, haxorg_TblfmExprCall other);
HAXORG_C_API_LINKAGE void haxorg_destroy_TblfmExprCall(OrgContext* org_context, haxorg_TblfmExprCall* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_TblfmExprElisp_get_value(OrgContext* org_context, haxorg_TblfmExprElisp __this);
HAXORG_C_API_LINKAGE bool haxorg_TblfmExprElisp___eq___const(OrgContext* org_context, haxorg_TblfmExprElisp __this, haxorg_TblfmExprElisp other);
HAXORG_C_API_LINKAGE void haxorg_destroy_TblfmExprElisp(OrgContext* org_context, haxorg_TblfmExprElisp* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_TblfmExpr(OrgContext* org_context, haxorg_TblfmExpr* obj);
HAXORG_C_API_LINKAGE haxorg_TblfmExprAxisRef haxorg_TblfmAssign_get_target(OrgContext* org_context, haxorg_TblfmAssign __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfTblfmExpr haxorg_TblfmAssign_get_expr(OrgContext* org_context, haxorg_TblfmAssign __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfTblfmAssignFlag haxorg_TblfmAssign_get_flags(OrgContext* org_context, haxorg_TblfmAssign __this);
HAXORG_C_API_LINKAGE bool haxorg_TblfmAssign___eq___const(OrgContext* org_context, haxorg_TblfmAssign __this, haxorg_TblfmAssign other);
HAXORG_C_API_LINKAGE void haxorg_destroy_TblfmAssign(OrgContext* org_context, haxorg_TblfmAssign* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Tblfm(OrgContext* org_context, haxorg_Tblfm* obj);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_AttrValue_get_name(OrgContext* org_context, haxorg_AttrValue __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_AttrValue_get_varname(OrgContext* org_context, haxorg_AttrValue __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfAttrValueDimensionSpan haxorg_AttrValue_get_span(OrgContext* org_context, haxorg_AttrValue __this);
HAXORG_C_API_LINKAGE bool haxorg_AttrValue_get_isQuoted(OrgContext* org_context, haxorg_AttrValue __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_AttrValue_getBool_const(OrgContext* org_context, haxorg_AttrValue __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_AttrValue_getInt_const(OrgContext* org_context, haxorg_AttrValue __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_AttrValue_getString_const(OrgContext* org_context, haxorg_AttrValue __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_AttrValue_getDouble_const(OrgContext* org_context, haxorg_AttrValue __this);
HAXORG_C_API_LINKAGE void haxorg_create_AttrValue_AttrValue(OrgContext* org_context);
HAXORG_C_API_LINKAGE bool haxorg_AttrValue___eq___const(OrgContext* org_context, haxorg_AttrValue __this, haxorg_AttrValue other);
HAXORG_C_API_LINKAGE bool haxorg_AttrValue_isTextValue_const(OrgContext* org_context, haxorg_AttrValue __this);
HAXORG_C_API_LINKAGE haxorg_AttrValueTextValue haxorg_AttrValue_getTextValueConst_const(OrgContext* org_context, haxorg_AttrValue __this);
HAXORG_C_API_LINKAGE haxorg_AttrValueTextValue haxorg_AttrValue_getTextValueMut(OrgContext* org_context, haxorg_AttrValue __this);
HAXORG_C_API_LINKAGE bool haxorg_AttrValue_isFileReference_const(OrgContext* org_context, haxorg_AttrValue __this);
HAXORG_C_API_LINKAGE haxorg_AttrValueFileReference haxorg_AttrValue_getFileReferenceConst_const(OrgContext* org_context, haxorg_AttrValue __this);
HAXORG_C_API_LINKAGE haxorg_AttrValueFileReference haxorg_AttrValue_getFileReferenceMut(OrgContext* org_context, haxorg_AttrValue __this);
HAXORG_C_API_LINKAGE bool haxorg_AttrValue_isLispValue_const(OrgContext* org_context, haxorg_AttrValue __this);
HAXORG_C_API_LINKAGE haxorg_AttrValueLispValue haxorg_AttrValue_getLispValueConst_const(OrgContext* org_context, haxorg_AttrValue __this);
HAXORG_C_API_LINKAGE haxorg_AttrValueLispValue haxorg_AttrValue_getLispValueMut(OrgContext* org_context, haxorg_AttrValue __this);
HAXORG_C_API_LINKAGE haxorg_AttrValueKind haxorg_AttrValue_getKind_const(OrgContext* org_context, haxorg_AttrValue __this);
HAXORG_C_API_LINKAGE int haxorg_AttrValueDimensionSpan_get_first(OrgContext* org_context, haxorg_AttrValueDimensionSpan __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_AttrValueDimensionSpan_get_last(OrgContext* org_context, haxorg_AttrValueDimensionSpan __this);
HAXORG_C_API_LINKAGE void haxorg_create_AttrValueDimensionSpan_DimensionSpan(OrgContext* org_context);
HAXORG_C_API_LINKAGE bool haxorg_AttrValueDimensionSpan___eq___const(OrgContext* org_context, haxorg_AttrValueDimensionSpan __this, haxorg_AttrValueDimensionSpan other);
HAXORG_C_API_LINKAGE void haxorg_destroy_AttrValueDimensionSpan(OrgContext* org_context, haxorg_AttrValueDimensionSpan* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_AttrValueTextValue_get_value(OrgContext* org_context, haxorg_AttrValueTextValue __this);
HAXORG_C_API_LINKAGE void haxorg_create_AttrValueTextValue_TextValue(OrgContext* org_context);
HAXORG_C_API_LINKAGE bool haxorg_AttrValueTextValue___eq___const(OrgContext* org_context, haxorg_AttrValueTextValue __this, haxorg_AttrValueTextValue other);
HAXORG_C_API_LINKAGE void haxorg_destroy_AttrValueTextValue(OrgContext* org_context, haxorg_AttrValueTextValue* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_AttrValueFileReference_get_file(OrgContext* org_context, haxorg_AttrValueFileReference __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_AttrValueFileReference_get_reference(OrgContext* org_context, haxorg_AttrValueFileReference __this);
HAXORG_C_API_LINKAGE void haxorg_create_AttrValueFileReference_FileReference(OrgContext* org_context);
HAXORG_C_API_LINKAGE bool haxorg_AttrValueFileReference___eq___const(OrgContext* org_context, haxorg_AttrValueFileReference __this, haxorg_AttrValueFileReference other);
HAXORG_C_API_LINKAGE void haxorg_destroy_AttrValueFileReference(OrgContext* org_context, haxorg_AttrValueFileReference* obj);
HAXORG_C_API_LINKAGE haxorg_LispCode haxorg_AttrValueLispValue_get_code(OrgContext* org_context, haxorg_AttrValueLispValue __this);
HAXORG_C_API_LINKAGE void haxorg_create_AttrValueLispValue_LispValue(OrgContext* org_context);
HAXORG_C_API_LINKAGE bool haxorg_AttrValueLispValue___eq___const(OrgContext* org_context, haxorg_AttrValueLispValue __this, haxorg_AttrValueLispValue other);
HAXORG_C_API_LINKAGE void haxorg_destroy_AttrValueLispValue(OrgContext* org_context, haxorg_AttrValueLispValue* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_AttrValue(OrgContext* org_context, haxorg_AttrValue* obj);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfStr haxorg_HashTagFlat_get_tags(OrgContext* org_context, haxorg_HashTagFlat __this);
HAXORG_C_API_LINKAGE bool haxorg_HashTagFlat___eq___const(OrgContext* org_context, haxorg_HashTagFlat __this, haxorg_HashTagFlat other);
HAXORG_C_API_LINKAGE bool haxorg_HashTagFlat___lt___const(OrgContext* org_context, haxorg_HashTagFlat __this, haxorg_HashTagFlat other);
HAXORG_C_API_LINKAGE void haxorg_destroy_HashTagFlat(OrgContext* org_context, haxorg_HashTagFlat* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_TodoKeyword_get_name(OrgContext* org_context, haxorg_TodoKeyword __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_TodoKeyword_get_shortcut(OrgContext* org_context, haxorg_TodoKeyword __this);
HAXORG_C_API_LINKAGE haxorg_TodoKeywordTransition haxorg_TodoKeyword_get_onEnter(OrgContext* org_context, haxorg_TodoKeyword __this);
HAXORG_C_API_LINKAGE haxorg_TodoKeywordTransition haxorg_TodoKeyword_get_onLeave(OrgContext* org_context, haxorg_TodoKeyword __this);
HAXORG_C_API_LINKAGE bool haxorg_TodoKeyword___eq___const(OrgContext* org_context, haxorg_TodoKeyword __this, haxorg_TodoKeyword other);
HAXORG_C_API_LINKAGE void haxorg_destroy_TodoKeyword(OrgContext* org_context, haxorg_TodoKeyword* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_HashTagText_get_head(OrgContext* org_context, haxorg_HashTagText __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfHashTagText haxorg_HashTagText_get_subtags(OrgContext* org_context, haxorg_HashTagText __this);
HAXORG_C_API_LINKAGE bool haxorg_HashTagText___eq___const(OrgContext* org_context, haxorg_HashTagText __this, haxorg_HashTagText other);
HAXORG_C_API_LINKAGE bool haxorg_HashTagText_prefixMatch_const(OrgContext* org_context, haxorg_HashTagText __this, haxorg_HstdVecOfStr prefix);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfHashTagFlat haxorg_HashTagText_getFlatHashes_const(OrgContext* org_context, haxorg_HashTagText __this, bool withIntermediate);
HAXORG_C_API_LINKAGE void haxorg_destroy_HashTagText(OrgContext* org_context, haxorg_HashTagText* obj);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfStr haxorg_SubtreePath_get_path(OrgContext* org_context, haxorg_SubtreePath __this);
HAXORG_C_API_LINKAGE bool haxorg_SubtreePath___eq___const(OrgContext* org_context, haxorg_SubtreePath __this, haxorg_SubtreePath other);
HAXORG_C_API_LINKAGE void haxorg_destroy_SubtreePath(OrgContext* org_context, haxorg_SubtreePath* obj);
HAXORG_C_API_LINKAGE bool haxorg_LinkTarget___eq___const(OrgContext* org_context, haxorg_LinkTarget __this, haxorg_LinkTarget other);
HAXORG_C_API_LINKAGE bool haxorg_LinkTarget_isRaw_const(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE haxorg_LinkTargetRaw haxorg_LinkTarget_getRawConst_const(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE haxorg_LinkTargetRaw haxorg_LinkTarget_getRawMut(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE bool haxorg_LinkTarget_isId_const(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE haxorg_LinkTargetId haxorg_LinkTarget_getIdConst_const(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE haxorg_LinkTargetId haxorg_LinkTarget_getIdMut(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE bool haxorg_LinkTarget_isCustomId_const(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE haxorg_LinkTargetCustomId haxorg_LinkTarget_getCustomIdConst_const(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE haxorg_LinkTargetCustomId haxorg_LinkTarget_getCustomIdMut(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE bool haxorg_LinkTarget_isSubtreeTitle_const(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE haxorg_LinkTargetSubtreeTitle haxorg_LinkTarget_getSubtreeTitleConst_const(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE haxorg_LinkTargetSubtreeTitle haxorg_LinkTarget_getSubtreeTitleMut(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE bool haxorg_LinkTarget_isPerson_const(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE haxorg_LinkTargetPerson haxorg_LinkTarget_getPersonConst_const(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE haxorg_LinkTargetPerson haxorg_LinkTarget_getPersonMut(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE bool haxorg_LinkTarget_isUserProtocol_const(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE haxorg_LinkTargetUserProtocol haxorg_LinkTarget_getUserProtocolConst_const(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE haxorg_LinkTargetUserProtocol haxorg_LinkTarget_getUserProtocolMut(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE bool haxorg_LinkTarget_isInternal_const(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE haxorg_LinkTargetInternal haxorg_LinkTarget_getInternalConst_const(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE haxorg_LinkTargetInternal haxorg_LinkTarget_getInternalMut(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE bool haxorg_LinkTarget_isFootnote_const(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE haxorg_LinkTargetFootnote haxorg_LinkTarget_getFootnoteConst_const(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE haxorg_LinkTargetFootnote haxorg_LinkTarget_getFootnoteMut(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE bool haxorg_LinkTarget_isFile_const(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE haxorg_LinkTargetFile haxorg_LinkTarget_getFileConst_const(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE haxorg_LinkTargetFile haxorg_LinkTarget_getFileMut(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE bool haxorg_LinkTarget_isAttachment_const(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE haxorg_LinkTargetAttachment haxorg_LinkTarget_getAttachmentConst_const(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE haxorg_LinkTargetAttachment haxorg_LinkTarget_getAttachmentMut(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE haxorg_LinkTargetKind haxorg_LinkTarget_getKind_const(OrgContext* org_context, haxorg_LinkTarget __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_LinkTargetRaw_get_text(OrgContext* org_context, haxorg_LinkTargetRaw __this);
HAXORG_C_API_LINKAGE bool haxorg_LinkTargetRaw___eq___const(OrgContext* org_context, haxorg_LinkTargetRaw __this, haxorg_LinkTargetRaw other);
HAXORG_C_API_LINKAGE void haxorg_destroy_LinkTargetRaw(OrgContext* org_context, haxorg_LinkTargetRaw* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_LinkTargetId_get_text(OrgContext* org_context, haxorg_LinkTargetId __this);
HAXORG_C_API_LINKAGE bool haxorg_LinkTargetId___eq___const(OrgContext* org_context, haxorg_LinkTargetId __this, haxorg_LinkTargetId other);
HAXORG_C_API_LINKAGE void haxorg_destroy_LinkTargetId(OrgContext* org_context, haxorg_LinkTargetId* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_LinkTargetCustomId_get_text(OrgContext* org_context, haxorg_LinkTargetCustomId __this);
HAXORG_C_API_LINKAGE bool haxorg_LinkTargetCustomId___eq___const(OrgContext* org_context, haxorg_LinkTargetCustomId __this, haxorg_LinkTargetCustomId other);
HAXORG_C_API_LINKAGE void haxorg_destroy_LinkTargetCustomId(OrgContext* org_context, haxorg_LinkTargetCustomId* obj);
HAXORG_C_API_LINKAGE haxorg_SubtreePath haxorg_LinkTargetSubtreeTitle_get_title(OrgContext* org_context, haxorg_LinkTargetSubtreeTitle __this);
HAXORG_C_API_LINKAGE int haxorg_LinkTargetSubtreeTitle_get_level(OrgContext* org_context, haxorg_LinkTargetSubtreeTitle __this);
HAXORG_C_API_LINKAGE bool haxorg_LinkTargetSubtreeTitle___eq___const(OrgContext* org_context, haxorg_LinkTargetSubtreeTitle __this, haxorg_LinkTargetSubtreeTitle other);
HAXORG_C_API_LINKAGE void haxorg_destroy_LinkTargetSubtreeTitle(OrgContext* org_context, haxorg_LinkTargetSubtreeTitle* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_LinkTargetPerson_get_name(OrgContext* org_context, haxorg_LinkTargetPerson __this);
HAXORG_C_API_LINKAGE bool haxorg_LinkTargetPerson___eq___const(OrgContext* org_context, haxorg_LinkTargetPerson __this, haxorg_LinkTargetPerson other);
HAXORG_C_API_LINKAGE void haxorg_destroy_LinkTargetPerson(OrgContext* org_context, haxorg_LinkTargetPerson* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_LinkTargetUserProtocol_get_protocol(OrgContext* org_context, haxorg_LinkTargetUserProtocol __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_LinkTargetUserProtocol_get_target(OrgContext* org_context, haxorg_LinkTargetUserProtocol __this);
HAXORG_C_API_LINKAGE bool haxorg_LinkTargetUserProtocol___eq___const(OrgContext* org_context, haxorg_LinkTargetUserProtocol __this, haxorg_LinkTargetUserProtocol other);
HAXORG_C_API_LINKAGE void haxorg_destroy_LinkTargetUserProtocol(OrgContext* org_context, haxorg_LinkTargetUserProtocol* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_LinkTargetInternal_get_target(OrgContext* org_context, haxorg_LinkTargetInternal __this);
HAXORG_C_API_LINKAGE bool haxorg_LinkTargetInternal___eq___const(OrgContext* org_context, haxorg_LinkTargetInternal __this, haxorg_LinkTargetInternal other);
HAXORG_C_API_LINKAGE void haxorg_destroy_LinkTargetInternal(OrgContext* org_context, haxorg_LinkTargetInternal* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_LinkTargetFootnote_get_target(OrgContext* org_context, haxorg_LinkTargetFootnote __this);
HAXORG_C_API_LINKAGE bool haxorg_LinkTargetFootnote___eq___const(OrgContext* org_context, haxorg_LinkTargetFootnote __this, haxorg_LinkTargetFootnote other);
HAXORG_C_API_LINKAGE void haxorg_destroy_LinkTargetFootnote(OrgContext* org_context, haxorg_LinkTargetFootnote* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_LinkTargetFile_get_file(OrgContext* org_context, haxorg_LinkTargetFile __this);
HAXORG_C_API_LINKAGE bool haxorg_LinkTargetFile___eq___const(OrgContext* org_context, haxorg_LinkTargetFile __this, haxorg_LinkTargetFile other);
HAXORG_C_API_LINKAGE void haxorg_destroy_LinkTargetFile(OrgContext* org_context, haxorg_LinkTargetFile* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_LinkTargetAttachment_get_file(OrgContext* org_context, haxorg_LinkTargetAttachment __this);
HAXORG_C_API_LINKAGE bool haxorg_LinkTargetAttachment___eq___const(OrgContext* org_context, haxorg_LinkTargetAttachment __this, haxorg_LinkTargetAttachment other);
HAXORG_C_API_LINKAGE void haxorg_destroy_LinkTargetAttachment(OrgContext* org_context, haxorg_LinkTargetAttachment* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_LinkTarget(OrgContext* org_context, haxorg_LinkTarget* obj);
HAXORG_C_API_LINKAGE bool haxorg_SubtreeLogHead___eq___const(OrgContext* org_context, haxorg_SubtreeLogHead __this, haxorg_SubtreeLogHead other);
HAXORG_C_API_LINKAGE bool haxorg_SubtreeLogHead_isPriority_const(OrgContext* org_context, haxorg_SubtreeLogHead __this);
HAXORG_C_API_LINKAGE haxorg_SubtreeLogHeadPriority haxorg_SubtreeLogHead_getPriorityConst_const(OrgContext* org_context, haxorg_SubtreeLogHead __this);
HAXORG_C_API_LINKAGE haxorg_SubtreeLogHeadPriority haxorg_SubtreeLogHead_getPriorityMut(OrgContext* org_context, haxorg_SubtreeLogHead __this);
HAXORG_C_API_LINKAGE bool haxorg_SubtreeLogHead_isNote_const(OrgContext* org_context, haxorg_SubtreeLogHead __this);
HAXORG_C_API_LINKAGE haxorg_SubtreeLogHeadNote haxorg_SubtreeLogHead_getNoteConst_const(OrgContext* org_context, haxorg_SubtreeLogHead __this);
HAXORG_C_API_LINKAGE haxorg_SubtreeLogHeadNote haxorg_SubtreeLogHead_getNoteMut(OrgContext* org_context, haxorg_SubtreeLogHead __this);
HAXORG_C_API_LINKAGE bool haxorg_SubtreeLogHead_isRefile_const(OrgContext* org_context, haxorg_SubtreeLogHead __this);
HAXORG_C_API_LINKAGE haxorg_SubtreeLogHeadRefile haxorg_SubtreeLogHead_getRefileConst_const(OrgContext* org_context, haxorg_SubtreeLogHead __this);
HAXORG_C_API_LINKAGE haxorg_SubtreeLogHeadRefile haxorg_SubtreeLogHead_getRefileMut(OrgContext* org_context, haxorg_SubtreeLogHead __this);
HAXORG_C_API_LINKAGE bool haxorg_SubtreeLogHead_isClock_const(OrgContext* org_context, haxorg_SubtreeLogHead __this);
HAXORG_C_API_LINKAGE haxorg_SubtreeLogHeadClock haxorg_SubtreeLogHead_getClockConst_const(OrgContext* org_context, haxorg_SubtreeLogHead __this);
HAXORG_C_API_LINKAGE haxorg_SubtreeLogHeadClock haxorg_SubtreeLogHead_getClockMut(OrgContext* org_context, haxorg_SubtreeLogHead __this);
HAXORG_C_API_LINKAGE bool haxorg_SubtreeLogHead_isState_const(OrgContext* org_context, haxorg_SubtreeLogHead __this);
HAXORG_C_API_LINKAGE haxorg_SubtreeLogHeadState haxorg_SubtreeLogHead_getStateConst_const(OrgContext* org_context, haxorg_SubtreeLogHead __this);
HAXORG_C_API_LINKAGE haxorg_SubtreeLogHeadState haxorg_SubtreeLogHead_getStateMut(OrgContext* org_context, haxorg_SubtreeLogHead __this);
HAXORG_C_API_LINKAGE bool haxorg_SubtreeLogHead_isDeadline_const(OrgContext* org_context, haxorg_SubtreeLogHead __this);
HAXORG_C_API_LINKAGE haxorg_SubtreeLogHeadDeadline haxorg_SubtreeLogHead_getDeadlineConst_const(OrgContext* org_context, haxorg_SubtreeLogHead __this);
HAXORG_C_API_LINKAGE haxorg_SubtreeLogHeadDeadline haxorg_SubtreeLogHead_getDeadlineMut(OrgContext* org_context, haxorg_SubtreeLogHead __this);
HAXORG_C_API_LINKAGE bool haxorg_SubtreeLogHead_isSchedule_const(OrgContext* org_context, haxorg_SubtreeLogHead __this);
HAXORG_C_API_LINKAGE haxorg_SubtreeLogHeadSchedule haxorg_SubtreeLogHead_getScheduleConst_const(OrgContext* org_context, haxorg_SubtreeLogHead __this);
HAXORG_C_API_LINKAGE haxorg_SubtreeLogHeadSchedule haxorg_SubtreeLogHead_getScheduleMut(OrgContext* org_context, haxorg_SubtreeLogHead __this);
HAXORG_C_API_LINKAGE bool haxorg_SubtreeLogHead_isTag_const(OrgContext* org_context, haxorg_SubtreeLogHead __this);
HAXORG_C_API_LINKAGE haxorg_SubtreeLogHeadTag haxorg_SubtreeLogHead_getTagConst_const(OrgContext* org_context, haxorg_SubtreeLogHead __this);
HAXORG_C_API_LINKAGE haxorg_SubtreeLogHeadTag haxorg_SubtreeLogHead_getTagMut(OrgContext* org_context, haxorg_SubtreeLogHead __this);
HAXORG_C_API_LINKAGE bool haxorg_SubtreeLogHead_isUnknown_const(OrgContext* org_context, haxorg_SubtreeLogHead __this);
HAXORG_C_API_LINKAGE haxorg_SubtreeLogHeadUnknown haxorg_SubtreeLogHead_getUnknownConst_const(OrgContext* org_context, haxorg_SubtreeLogHead __this);
HAXORG_C_API_LINKAGE haxorg_SubtreeLogHeadUnknown haxorg_SubtreeLogHead_getUnknownMut(OrgContext* org_context, haxorg_SubtreeLogHead __this);
HAXORG_C_API_LINKAGE haxorg_SubtreeLogHeadKind haxorg_SubtreeLogHead_getLogKind_const(OrgContext* org_context, haxorg_SubtreeLogHead __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_SubtreeLogHeadPriority_get_oldPriority(OrgContext* org_context, haxorg_SubtreeLogHeadPriority __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_SubtreeLogHeadPriority_get_newPriority(OrgContext* org_context, haxorg_SubtreeLogHeadPriority __this);
HAXORG_C_API_LINKAGE haxorg_UserTime haxorg_SubtreeLogHeadPriority_get_on(OrgContext* org_context, haxorg_SubtreeLogHeadPriority __this);
HAXORG_C_API_LINKAGE haxorg_SubtreeLogHeadPriorityAction haxorg_SubtreeLogHeadPriority_get_action(OrgContext* org_context, haxorg_SubtreeLogHeadPriority __this);
HAXORG_C_API_LINKAGE bool haxorg_SubtreeLogHeadPriority___eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadPriority __this, haxorg_SubtreeLogHeadPriority other);
HAXORG_C_API_LINKAGE void haxorg_destroy_SubtreeLogHeadPriority(OrgContext* org_context, haxorg_SubtreeLogHeadPriority* obj);
HAXORG_C_API_LINKAGE haxorg_UserTime haxorg_SubtreeLogHeadNote_get_on(OrgContext* org_context, haxorg_SubtreeLogHeadNote __this);
HAXORG_C_API_LINKAGE bool haxorg_SubtreeLogHeadNote___eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadNote __this, haxorg_SubtreeLogHeadNote other);
HAXORG_C_API_LINKAGE void haxorg_destroy_SubtreeLogHeadNote(OrgContext* org_context, haxorg_SubtreeLogHeadNote* obj);
HAXORG_C_API_LINKAGE haxorg_UserTime haxorg_SubtreeLogHeadRefile_get_on(OrgContext* org_context, haxorg_SubtreeLogHeadRefile __this);
HAXORG_C_API_LINKAGE haxorg_LinkTarget haxorg_SubtreeLogHeadRefile_get_from(OrgContext* org_context, haxorg_SubtreeLogHeadRefile __this);
HAXORG_C_API_LINKAGE bool haxorg_SubtreeLogHeadRefile___eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadRefile __this, haxorg_SubtreeLogHeadRefile other);
HAXORG_C_API_LINKAGE void haxorg_destroy_SubtreeLogHeadRefile(OrgContext* org_context, haxorg_SubtreeLogHeadRefile* obj);
HAXORG_C_API_LINKAGE haxorg_UserTime haxorg_SubtreeLogHeadClock_get_from(OrgContext* org_context, haxorg_SubtreeLogHeadClock __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_SubtreeLogHeadClock_get_to(OrgContext* org_context, haxorg_SubtreeLogHeadClock __this);
HAXORG_C_API_LINKAGE bool haxorg_SubtreeLogHeadClock___eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadClock __this, haxorg_SubtreeLogHeadClock other);
HAXORG_C_API_LINKAGE void haxorg_destroy_SubtreeLogHeadClock(OrgContext* org_context, haxorg_SubtreeLogHeadClock* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_SubtreeLogHeadState_get_from(OrgContext* org_context, haxorg_SubtreeLogHeadState __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_SubtreeLogHeadState_get_to(OrgContext* org_context, haxorg_SubtreeLogHeadState __this);
HAXORG_C_API_LINKAGE haxorg_UserTime haxorg_SubtreeLogHeadState_get_on(OrgContext* org_context, haxorg_SubtreeLogHeadState __this);
HAXORG_C_API_LINKAGE bool haxorg_SubtreeLogHeadState___eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadState __this, haxorg_SubtreeLogHeadState other);
HAXORG_C_API_LINKAGE void haxorg_destroy_SubtreeLogHeadState(OrgContext* org_context, haxorg_SubtreeLogHeadState* obj);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_SubtreeLogHeadDeadline_get_from(OrgContext* org_context, haxorg_SubtreeLogHeadDeadline __this);
HAXORG_C_API_LINKAGE haxorg_UserTime haxorg_SubtreeLogHeadDeadline_get_to(OrgContext* org_context, haxorg_SubtreeLogHeadDeadline __this);
HAXORG_C_API_LINKAGE haxorg_UserTime haxorg_SubtreeLogHeadDeadline_get_on(OrgContext* org_context, haxorg_SubtreeLogHeadDeadline __this);
HAXORG_C_API_LINKAGE bool haxorg_SubtreeLogHeadDeadline___eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadDeadline __this, haxorg_SubtreeLogHeadDeadline other);
HAXORG_C_API_LINKAGE void haxorg_destroy_SubtreeLogHeadDeadline(OrgContext* org_context, haxorg_SubtreeLogHeadDeadline* obj);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_SubtreeLogHeadSchedule_get_from(OrgContext* org_context, haxorg_SubtreeLogHeadSchedule __this);
HAXORG_C_API_LINKAGE haxorg_UserTime haxorg_SubtreeLogHeadSchedule_get_to(OrgContext* org_context, haxorg_SubtreeLogHeadSchedule __this);
HAXORG_C_API_LINKAGE haxorg_UserTime haxorg_SubtreeLogHeadSchedule_get_on(OrgContext* org_context, haxorg_SubtreeLogHeadSchedule __this);
HAXORG_C_API_LINKAGE bool haxorg_SubtreeLogHeadSchedule___eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadSchedule __this, haxorg_SubtreeLogHeadSchedule other);
HAXORG_C_API_LINKAGE void haxorg_destroy_SubtreeLogHeadSchedule(OrgContext* org_context, haxorg_SubtreeLogHeadSchedule* obj);
HAXORG_C_API_LINKAGE haxorg_UserTime haxorg_SubtreeLogHeadTag_get_on(OrgContext* org_context, haxorg_SubtreeLogHeadTag __this);
HAXORG_C_API_LINKAGE haxorg_HashTagText haxorg_SubtreeLogHeadTag_get_tag(OrgContext* org_context, haxorg_SubtreeLogHeadTag __this);
HAXORG_C_API_LINKAGE bool haxorg_SubtreeLogHeadTag_get_added(OrgContext* org_context, haxorg_SubtreeLogHeadTag __this);
HAXORG_C_API_LINKAGE bool haxorg_SubtreeLogHeadTag___eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadTag __this, haxorg_SubtreeLogHeadTag other);
HAXORG_C_API_LINKAGE void haxorg_destroy_SubtreeLogHeadTag(OrgContext* org_context, haxorg_SubtreeLogHeadTag* obj);
HAXORG_C_API_LINKAGE bool haxorg_SubtreeLogHeadUnknown___eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadUnknown __this, haxorg_SubtreeLogHeadUnknown other);
HAXORG_C_API_LINKAGE void haxorg_destroy_SubtreeLogHeadUnknown(OrgContext* org_context, haxorg_SubtreeLogHeadUnknown* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_SubtreeLogHead(OrgContext* org_context, haxorg_SubtreeLogHead* obj);
HAXORG_C_API_LINKAGE int haxorg_SubtreeCompletion_get_done(OrgContext* org_context, haxorg_SubtreeCompletion __this);
HAXORG_C_API_LINKAGE int haxorg_SubtreeCompletion_get_full(OrgContext* org_context, haxorg_SubtreeCompletion __this);
HAXORG_C_API_LINKAGE bool haxorg_SubtreeCompletion_get_isPercent(OrgContext* org_context, haxorg_SubtreeCompletion __this);
HAXORG_C_API_LINKAGE bool haxorg_SubtreeCompletion___eq___const(OrgContext* org_context, haxorg_SubtreeCompletion __this, haxorg_SubtreeCompletion other);
HAXORG_C_API_LINKAGE void haxorg_destroy_SubtreeCompletion(OrgContext* org_context, haxorg_SubtreeCompletion* obj);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfAttrValue haxorg_AttrList_get_items(OrgContext* org_context, haxorg_AttrList __this);
HAXORG_C_API_LINKAGE bool haxorg_AttrList___eq___const(OrgContext* org_context, haxorg_AttrList __this, haxorg_AttrList other);
HAXORG_C_API_LINKAGE void haxorg_destroy_AttrList(OrgContext* org_context, haxorg_AttrList* obj);
HAXORG_C_API_LINKAGE haxorg_AttrList haxorg_AttrGroup_get_positional(OrgContext* org_context, haxorg_AttrGroup __this);
HAXORG_C_API_LINKAGE haxorg_HstdMap haxorg_AttrGroup_get_named(OrgContext* org_context, haxorg_AttrGroup __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfAttrValue haxorg_AttrGroup_getFlatArgs_const(OrgContext* org_context, haxorg_AttrGroup __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfAttrValue haxorg_AttrGroup_getAttrs_const(OrgContext* org_context, haxorg_AttrGroup __this, haxorg_HstdOpt key);
HAXORG_C_API_LINKAGE void haxorg_AttrGroup_setNamedAttr(OrgContext* org_context, haxorg_AttrGroup __this, haxorg_HstdStr key, haxorg_HstdVecOfAttrValue attrs);
HAXORG_C_API_LINKAGE void haxorg_AttrGroup_setPositionalAttr(OrgContext* org_context, haxorg_AttrGroup __this, haxorg_HstdVecOfAttrValue items);
HAXORG_C_API_LINKAGE int haxorg_AttrGroup_getPositionalSize_const(OrgContext* org_context, haxorg_AttrGroup __this);
HAXORG_C_API_LINKAGE int haxorg_AttrGroup_getNamedSize_const(OrgContext* org_context, haxorg_AttrGroup __this);
HAXORG_C_API_LINKAGE bool haxorg_AttrGroup_isEmpty_const(OrgContext* org_context, haxorg_AttrGroup __this);
HAXORG_C_API_LINKAGE haxorg_AttrList haxorg_AttrGroup_getAll_const(OrgContext* org_context, haxorg_AttrGroup __this);
HAXORG_C_API_LINKAGE haxorg_AttrValue haxorg_AttrGroup_atPositional_const(OrgContext* org_context, haxorg_AttrGroup __this, int index);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_AttrGroup_getPositional_const(OrgContext* org_context, haxorg_AttrGroup __this, int index);
HAXORG_C_API_LINKAGE haxorg_AttrList haxorg_AttrGroup_atNamed_const(OrgContext* org_context, haxorg_AttrGroup __this, haxorg_HstdStr index);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_AttrGroup_getNamed_const(OrgContext* org_context, haxorg_AttrGroup __this, haxorg_HstdStr index);
HAXORG_C_API_LINKAGE haxorg_AttrValue haxorg_AttrGroup_atFirstNamed_const(OrgContext* org_context, haxorg_AttrGroup __this, haxorg_HstdStr index);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_AttrGroup_getFirstNamed_const(OrgContext* org_context, haxorg_AttrGroup __this, haxorg_HstdStr index);
HAXORG_C_API_LINKAGE haxorg_AttrList haxorg_AttrGroup_atVarNamed_const(OrgContext* org_context, haxorg_AttrGroup __this, haxorg_HstdStr index);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_AttrGroup_getVarNamed_const(OrgContext* org_context, haxorg_AttrGroup __this, haxorg_HstdStr index);
HAXORG_C_API_LINKAGE haxorg_AttrValue haxorg_AttrGroup_atFirstVarNamed_const(OrgContext* org_context, haxorg_AttrGroup __this, haxorg_HstdStr index);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_AttrGroup_getFirstVarNamed_const(OrgContext* org_context, haxorg_AttrGroup __this, haxorg_HstdStr index);
HAXORG_C_API_LINKAGE bool haxorg_AttrGroup___eq___const(OrgContext* org_context, haxorg_AttrGroup __this, haxorg_AttrGroup other);
HAXORG_C_API_LINKAGE void haxorg_destroy_AttrGroup(OrgContext* org_context, haxorg_AttrGroup* obj);
HAXORG_C_API_LINKAGE haxorg_AttrGroup haxorg_OrgCodeEvalInput_get_blockAttrs(OrgContext* org_context, haxorg_OrgCodeEvalInput __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_OrgCodeEvalInput_get_tangledCode(OrgContext* org_context, haxorg_OrgCodeEvalInput __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_OrgCodeEvalInput_get_exportType(OrgContext* org_context, haxorg_OrgCodeEvalInput __this);
HAXORG_C_API_LINKAGE haxorg_OrgCodeEvalInputResultType haxorg_OrgCodeEvalInput_get_resultType(OrgContext* org_context, haxorg_OrgCodeEvalInput __this);
HAXORG_C_API_LINKAGE haxorg_OrgCodeEvalInputResultFormat haxorg_OrgCodeEvalInput_get_resultFormat(OrgContext* org_context, haxorg_OrgCodeEvalInput __this);
HAXORG_C_API_LINKAGE haxorg_OrgCodeEvalInputResultHandling haxorg_OrgCodeEvalInput_get_resultHandling(OrgContext* org_context, haxorg_OrgCodeEvalInput __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_OrgCodeEvalInput_get_language(OrgContext* org_context, haxorg_OrgCodeEvalInput __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfOrgCodeEvalInputVar haxorg_OrgCodeEvalInput_get_argList(OrgContext* org_context, haxorg_OrgCodeEvalInput __this);
HAXORG_C_API_LINKAGE bool haxorg_OrgCodeEvalInput___eq___const(OrgContext* org_context, haxorg_OrgCodeEvalInput __this, haxorg_OrgCodeEvalInput other);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_OrgCodeEvalInput_getVariable_const(OrgContext* org_context, haxorg_OrgCodeEvalInput __this, haxorg_HstdStr name);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_OrgCodeEvalInputVar_get_name(OrgContext* org_context, haxorg_OrgCodeEvalInputVar __this);
HAXORG_C_API_LINKAGE haxorg_OrgJson haxorg_OrgCodeEvalInputVar_get_value(OrgContext* org_context, haxorg_OrgCodeEvalInputVar __this);
HAXORG_C_API_LINKAGE void haxorg_create_OrgCodeEvalInputVar_Var(OrgContext* org_context);
HAXORG_C_API_LINKAGE bool haxorg_OrgCodeEvalInputVar___eq___const(OrgContext* org_context, haxorg_OrgCodeEvalInputVar __this, haxorg_OrgCodeEvalInputVar other);
HAXORG_C_API_LINKAGE void haxorg_destroy_OrgCodeEvalInputVar(OrgContext* org_context, haxorg_OrgCodeEvalInputVar* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_OrgCodeEvalInput(OrgContext* org_context, haxorg_OrgCodeEvalInput* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_OrgCodeEvalOutput_get_stdoutText(OrgContext* org_context, haxorg_OrgCodeEvalOutput __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_OrgCodeEvalOutput_get_stderrText(OrgContext* org_context, haxorg_OrgCodeEvalOutput __this);
HAXORG_C_API_LINKAGE int haxorg_OrgCodeEvalOutput_get_code(OrgContext* org_context, haxorg_OrgCodeEvalOutput __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_OrgCodeEvalOutput_get_cmd(OrgContext* org_context, haxorg_OrgCodeEvalOutput __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfStr haxorg_OrgCodeEvalOutput_get_args(OrgContext* org_context, haxorg_OrgCodeEvalOutput __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_OrgCodeEvalOutput_get_cwd(OrgContext* org_context, haxorg_OrgCodeEvalOutput __this);
HAXORG_C_API_LINKAGE haxorg_AttrGroup haxorg_OrgCodeEvalOutput_get_appliedHeaderArg(OrgContext* org_context, haxorg_OrgCodeEvalOutput __this);
HAXORG_C_API_LINKAGE bool haxorg_OrgCodeEvalOutput___eq___const(OrgContext* org_context, haxorg_OrgCodeEvalOutput __this, haxorg_OrgCodeEvalOutput other);
HAXORG_C_API_LINKAGE void haxorg_destroy_OrgCodeEvalOutput(OrgContext* org_context, haxorg_OrgCodeEvalOutput* obj);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfColumnViewColumn haxorg_ColumnView_get_columns(OrgContext* org_context, haxorg_ColumnView __this);
HAXORG_C_API_LINKAGE bool haxorg_ColumnView___eq___const(OrgContext* org_context, haxorg_ColumnView __this, haxorg_ColumnView other);
HAXORG_C_API_LINKAGE bool haxorg_ColumnViewSummary___eq___const(OrgContext* org_context, haxorg_ColumnViewSummary __this, haxorg_ColumnViewSummary other);
HAXORG_C_API_LINKAGE bool haxorg_ColumnViewSummary_isCheckboxAggregate_const(OrgContext* org_context, haxorg_ColumnViewSummary __this);
HAXORG_C_API_LINKAGE haxorg_ColumnViewSummaryCheckboxAggregate haxorg_ColumnViewSummary_getCheckboxAggregateConst_const(OrgContext* org_context, haxorg_ColumnViewSummary __this);
HAXORG_C_API_LINKAGE haxorg_ColumnViewSummaryCheckboxAggregate haxorg_ColumnViewSummary_getCheckboxAggregateMut(OrgContext* org_context, haxorg_ColumnViewSummary __this);
HAXORG_C_API_LINKAGE bool haxorg_ColumnViewSummary_isMathAggregate_const(OrgContext* org_context, haxorg_ColumnViewSummary __this);
HAXORG_C_API_LINKAGE haxorg_ColumnViewSummaryMathAggregate haxorg_ColumnViewSummary_getMathAggregateConst_const(OrgContext* org_context, haxorg_ColumnViewSummary __this);
HAXORG_C_API_LINKAGE haxorg_ColumnViewSummaryMathAggregate haxorg_ColumnViewSummary_getMathAggregateMut(OrgContext* org_context, haxorg_ColumnViewSummary __this);
HAXORG_C_API_LINKAGE haxorg_ColumnViewSummaryKind haxorg_ColumnViewSummary_getKind_const(OrgContext* org_context, haxorg_ColumnViewSummary __this);
HAXORG_C_API_LINKAGE haxorg_ColumnViewSummaryCheckboxAggregateKind haxorg_ColumnViewSummaryCheckboxAggregate_get_kind(OrgContext* org_context, haxorg_ColumnViewSummaryCheckboxAggregate __this);
HAXORG_C_API_LINKAGE bool haxorg_ColumnViewSummaryCheckboxAggregate___eq___const(OrgContext* org_context, haxorg_ColumnViewSummaryCheckboxAggregate __this, haxorg_ColumnViewSummaryCheckboxAggregate other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ColumnViewSummaryCheckboxAggregate(OrgContext* org_context, haxorg_ColumnViewSummaryCheckboxAggregate* obj);
HAXORG_C_API_LINKAGE haxorg_ColumnViewSummaryMathAggregateKind haxorg_ColumnViewSummaryMathAggregate_get_kind(OrgContext* org_context, haxorg_ColumnViewSummaryMathAggregate __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ColumnViewSummaryMathAggregate_get_formatDigits(OrgContext* org_context, haxorg_ColumnViewSummaryMathAggregate __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ColumnViewSummaryMathAggregate_get_formatPrecision(OrgContext* org_context, haxorg_ColumnViewSummaryMathAggregate __this);
HAXORG_C_API_LINKAGE bool haxorg_ColumnViewSummaryMathAggregate___eq___const(OrgContext* org_context, haxorg_ColumnViewSummaryMathAggregate __this, haxorg_ColumnViewSummaryMathAggregate other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ColumnViewSummaryMathAggregate(OrgContext* org_context, haxorg_ColumnViewSummaryMathAggregate* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ColumnViewSummary(OrgContext* org_context, haxorg_ColumnViewSummary* obj);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ColumnViewColumn_get_summary(OrgContext* org_context, haxorg_ColumnViewColumn __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ColumnViewColumn_get_width(OrgContext* org_context, haxorg_ColumnViewColumn __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ColumnViewColumn_get_property(OrgContext* org_context, haxorg_ColumnViewColumn __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ColumnViewColumn_get_propertyTitle(OrgContext* org_context, haxorg_ColumnViewColumn __this);
HAXORG_C_API_LINKAGE bool haxorg_ColumnViewColumn___eq___const(OrgContext* org_context, haxorg_ColumnViewColumn __this, haxorg_ColumnViewColumn other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ColumnViewColumn(OrgContext* org_context, haxorg_ColumnViewColumn* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ColumnView(OrgContext* org_context, haxorg_ColumnView* obj);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfBlockCodeLinePart haxorg_BlockCodeLine_get_parts(OrgContext* org_context, haxorg_BlockCodeLine __this);
HAXORG_C_API_LINKAGE bool haxorg_BlockCodeLine___eq___const(OrgContext* org_context, haxorg_BlockCodeLine __this, haxorg_BlockCodeLine other);
HAXORG_C_API_LINKAGE bool haxorg_BlockCodeLinePart___eq___const(OrgContext* org_context, haxorg_BlockCodeLinePart __this, haxorg_BlockCodeLinePart other);
HAXORG_C_API_LINKAGE bool haxorg_BlockCodeLinePart_isRaw_const(OrgContext* org_context, haxorg_BlockCodeLinePart __this);
HAXORG_C_API_LINKAGE haxorg_BlockCodeLinePartRaw haxorg_BlockCodeLinePart_getRawConst_const(OrgContext* org_context, haxorg_BlockCodeLinePart __this);
HAXORG_C_API_LINKAGE haxorg_BlockCodeLinePartRaw haxorg_BlockCodeLinePart_getRawMut(OrgContext* org_context, haxorg_BlockCodeLinePart __this);
HAXORG_C_API_LINKAGE bool haxorg_BlockCodeLinePart_isCallout_const(OrgContext* org_context, haxorg_BlockCodeLinePart __this);
HAXORG_C_API_LINKAGE haxorg_BlockCodeLinePartCallout haxorg_BlockCodeLinePart_getCalloutConst_const(OrgContext* org_context, haxorg_BlockCodeLinePart __this);
HAXORG_C_API_LINKAGE haxorg_BlockCodeLinePartCallout haxorg_BlockCodeLinePart_getCalloutMut(OrgContext* org_context, haxorg_BlockCodeLinePart __this);
HAXORG_C_API_LINKAGE bool haxorg_BlockCodeLinePart_isTangle_const(OrgContext* org_context, haxorg_BlockCodeLinePart __this);
HAXORG_C_API_LINKAGE haxorg_BlockCodeLinePartTangle haxorg_BlockCodeLinePart_getTangleConst_const(OrgContext* org_context, haxorg_BlockCodeLinePart __this);
HAXORG_C_API_LINKAGE haxorg_BlockCodeLinePartTangle haxorg_BlockCodeLinePart_getTangleMut(OrgContext* org_context, haxorg_BlockCodeLinePart __this);
HAXORG_C_API_LINKAGE haxorg_BlockCodeLinePartKind haxorg_BlockCodeLinePart_getKind_const(OrgContext* org_context, haxorg_BlockCodeLinePart __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_BlockCodeLinePartRaw_get_code(OrgContext* org_context, haxorg_BlockCodeLinePartRaw __this);
HAXORG_C_API_LINKAGE bool haxorg_BlockCodeLinePartRaw___eq___const(OrgContext* org_context, haxorg_BlockCodeLinePartRaw __this, haxorg_BlockCodeLinePartRaw other);
HAXORG_C_API_LINKAGE void haxorg_destroy_BlockCodeLinePartRaw(OrgContext* org_context, haxorg_BlockCodeLinePartRaw* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_BlockCodeLinePartCallout_get_name(OrgContext* org_context, haxorg_BlockCodeLinePartCallout __this);
HAXORG_C_API_LINKAGE bool haxorg_BlockCodeLinePartCallout___eq___const(OrgContext* org_context, haxorg_BlockCodeLinePartCallout __this, haxorg_BlockCodeLinePartCallout other);
HAXORG_C_API_LINKAGE void haxorg_destroy_BlockCodeLinePartCallout(OrgContext* org_context, haxorg_BlockCodeLinePartCallout* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_BlockCodeLinePartTangle_get_target(OrgContext* org_context, haxorg_BlockCodeLinePartTangle __this);
HAXORG_C_API_LINKAGE bool haxorg_BlockCodeLinePartTangle___eq___const(OrgContext* org_context, haxorg_BlockCodeLinePartTangle __this, haxorg_BlockCodeLinePartTangle other);
HAXORG_C_API_LINKAGE void haxorg_destroy_BlockCodeLinePartTangle(OrgContext* org_context, haxorg_BlockCodeLinePartTangle* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_BlockCodeLinePart(OrgContext* org_context, haxorg_BlockCodeLinePart* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_BlockCodeLine(OrgContext* org_context, haxorg_BlockCodeLine* obj);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentExportConfig_get_inlinetasks(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentExportConfig_get_footnotes(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentExportConfig_get_clock(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentExportConfig_get_author(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentExportConfig_get_emphasis(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentExportConfig_get_specialStrings(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentExportConfig_get_propertyDrawers(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentExportConfig_get_statisticsCookies(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentExportConfig_get_todoText(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentExportConfig_get_smartQuotes(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentExportConfig_get_fixedWidth(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentExportConfig_get_timestamps(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentExportConfig_get_preserveBreaks(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentExportConfig_get_subSuperscripts(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentExportConfig_get_expandLinks(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentExportConfig_get_creator(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentExportConfig_get_drawers(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentExportConfig_get_date(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentExportConfig_get_entities(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentExportConfig_get_email(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentExportConfig_get_sectionNumbers(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentExportConfig_get_planning(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentExportConfig_get_priority(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentExportConfig_get_latex(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentExportConfig_get_timestamp(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentExportConfig_get_title(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentExportConfig_get_tables(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentExportConfig_get_headlineLevels(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_DocumentExportConfigBrokenLinks haxorg_DocumentExportConfig_get_brokenLinks(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_DocumentExportConfigTagExport haxorg_DocumentExportConfig_get_tagExport(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_DocumentExportConfigTaskFiltering haxorg_DocumentExportConfig_get_taskFiltering(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_DocumentExportConfigArchivedTrees haxorg_DocumentExportConfig_get_archivedTrees(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE bool haxorg_DocumentExportConfig___eq___const(OrgContext* org_context, haxorg_DocumentExportConfig __this, haxorg_DocumentExportConfig other);
HAXORG_C_API_LINKAGE bool haxorg_DocumentExportConfig_isDoExport_const(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_DocumentExportConfigDoExport haxorg_DocumentExportConfig_getDoExportConst_const(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_DocumentExportConfigDoExport haxorg_DocumentExportConfig_getDoExportMut(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE bool haxorg_DocumentExportConfig_isExportFixed_const(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_DocumentExportConfigExportFixed haxorg_DocumentExportConfig_getExportFixedConst_const(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_DocumentExportConfigExportFixed haxorg_DocumentExportConfig_getExportFixedMut(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_DocumentExportConfigTocExportKind haxorg_DocumentExportConfig_getTocExportKind_const(OrgContext* org_context, haxorg_DocumentExportConfig __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfStr haxorg_DocumentExportConfigTaskExport_get_taskWhitelist(OrgContext* org_context, haxorg_DocumentExportConfigTaskExport __this);
HAXORG_C_API_LINKAGE bool haxorg_DocumentExportConfigTaskExport___eq___const(OrgContext* org_context, haxorg_DocumentExportConfigTaskExport __this, haxorg_DocumentExportConfigTaskExport other);
HAXORG_C_API_LINKAGE void haxorg_destroy_DocumentExportConfigTaskExport(OrgContext* org_context, haxorg_DocumentExportConfigTaskExport* obj);
HAXORG_C_API_LINKAGE bool haxorg_DocumentExportConfigDoExport_get_exportToc(OrgContext* org_context, haxorg_DocumentExportConfigDoExport __this);
HAXORG_C_API_LINKAGE bool haxorg_DocumentExportConfigDoExport___eq___const(OrgContext* org_context, haxorg_DocumentExportConfigDoExport __this, haxorg_DocumentExportConfigDoExport other);
HAXORG_C_API_LINKAGE void haxorg_destroy_DocumentExportConfigDoExport(OrgContext* org_context, haxorg_DocumentExportConfigDoExport* obj);
HAXORG_C_API_LINKAGE int haxorg_DocumentExportConfigExportFixed_get_exportLevels(OrgContext* org_context, haxorg_DocumentExportConfigExportFixed __this);
HAXORG_C_API_LINKAGE bool haxorg_DocumentExportConfigExportFixed___eq___const(OrgContext* org_context, haxorg_DocumentExportConfigExportFixed __this, haxorg_DocumentExportConfigExportFixed other);
HAXORG_C_API_LINKAGE void haxorg_destroy_DocumentExportConfigExportFixed(OrgContext* org_context, haxorg_DocumentExportConfigExportFixed* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_DocumentExportConfig(OrgContext* org_context, haxorg_DocumentExportConfig* obj);
HAXORG_C_API_LINKAGE haxorg_SubtreePeriodKind haxorg_SubtreePeriod_get_kind(OrgContext* org_context, haxorg_SubtreePeriod __this);
HAXORG_C_API_LINKAGE haxorg_UserTime haxorg_SubtreePeriod_get_from(OrgContext* org_context, haxorg_SubtreePeriod __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_SubtreePeriod_get_to(OrgContext* org_context, haxorg_SubtreePeriod __this);
HAXORG_C_API_LINKAGE bool haxorg_SubtreePeriod___eq___const(OrgContext* org_context, haxorg_SubtreePeriod __this, haxorg_SubtreePeriod other);
HAXORG_C_API_LINKAGE void haxorg_destroy_SubtreePeriod(OrgContext* org_context, haxorg_SubtreePeriod* obj);
HAXORG_C_API_LINKAGE bool haxorg_NamedProperty_isMatching_const(OrgContext* org_context, haxorg_NamedProperty __this, haxorg_HstdStr kind, haxorg_HstdOpt subKind);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_NamedProperty_getName_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_NamedProperty_getSubKind_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedProperty___eq___const(OrgContext* org_context, haxorg_NamedProperty __this, haxorg_NamedProperty other);
HAXORG_C_API_LINKAGE bool haxorg_NamedProperty_isNonblocking_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyNonblocking haxorg_NamedProperty_getNonblockingConst_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyNonblocking haxorg_NamedProperty_getNonblockingMut(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedProperty_isArchiveTime_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyArchiveTime haxorg_NamedProperty_getArchiveTimeConst_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyArchiveTime haxorg_NamedProperty_getArchiveTimeMut(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedProperty_isArchiveFile_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyArchiveFile haxorg_NamedProperty_getArchiveFileConst_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyArchiveFile haxorg_NamedProperty_getArchiveFileMut(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedProperty_isArchiveOlpath_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyArchiveOlpath haxorg_NamedProperty_getArchiveOlpathConst_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyArchiveOlpath haxorg_NamedProperty_getArchiveOlpathMut(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedProperty_isArchiveTarget_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyArchiveTarget haxorg_NamedProperty_getArchiveTargetConst_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyArchiveTarget haxorg_NamedProperty_getArchiveTargetMut(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedProperty_isArchiveCategory_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyArchiveCategory haxorg_NamedProperty_getArchiveCategoryConst_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyArchiveCategory haxorg_NamedProperty_getArchiveCategoryMut(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedProperty_isArchiveTodo_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyArchiveTodo haxorg_NamedProperty_getArchiveTodoConst_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyArchiveTodo haxorg_NamedProperty_getArchiveTodoMut(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedProperty_isTrigger_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyTrigger haxorg_NamedProperty_getTriggerConst_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyTrigger haxorg_NamedProperty_getTriggerMut(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedProperty_isExportLatexClass_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyExportLatexClass haxorg_NamedProperty_getExportLatexClassConst_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyExportLatexClass haxorg_NamedProperty_getExportLatexClassMut(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedProperty_isCookieData_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyCookieData haxorg_NamedProperty_getCookieDataConst_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyCookieData haxorg_NamedProperty_getCookieDataMut(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedProperty_isExportLatexClassOptions_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyExportLatexClassOptions haxorg_NamedProperty_getExportLatexClassOptionsConst_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyExportLatexClassOptions haxorg_NamedProperty_getExportLatexClassOptionsMut(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedProperty_isExportLatexHeader_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyExportLatexHeader haxorg_NamedProperty_getExportLatexHeaderConst_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyExportLatexHeader haxorg_NamedProperty_getExportLatexHeaderMut(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedProperty_isExportLatexCompiler_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyExportLatexCompiler haxorg_NamedProperty_getExportLatexCompilerConst_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyExportLatexCompiler haxorg_NamedProperty_getExportLatexCompilerMut(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedProperty_isOrdered_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyOrdered haxorg_NamedProperty_getOrderedConst_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyOrdered haxorg_NamedProperty_getOrderedMut(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedProperty_isEffort_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyEffort haxorg_NamedProperty_getEffortConst_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyEffort haxorg_NamedProperty_getEffortMut(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedProperty_isVisibility_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyVisibility haxorg_NamedProperty_getVisibilityConst_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyVisibility haxorg_NamedProperty_getVisibilityMut(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedProperty_isExportOptions_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyExportOptions haxorg_NamedProperty_getExportOptionsConst_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyExportOptions haxorg_NamedProperty_getExportOptionsMut(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedProperty_isBlocker_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyBlocker haxorg_NamedProperty_getBlockerConst_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyBlocker haxorg_NamedProperty_getBlockerMut(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedProperty_isUnnumbered_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyUnnumbered haxorg_NamedProperty_getUnnumberedConst_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyUnnumbered haxorg_NamedProperty_getUnnumberedMut(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedProperty_isCreated_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyCreated haxorg_NamedProperty_getCreatedConst_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyCreated haxorg_NamedProperty_getCreatedMut(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedProperty_isRadioId_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyRadioId haxorg_NamedProperty_getRadioIdConst_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyRadioId haxorg_NamedProperty_getRadioIdMut(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedProperty_isHashtagDef_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyHashtagDef haxorg_NamedProperty_getHashtagDefConst_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyHashtagDef haxorg_NamedProperty_getHashtagDefMut(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedProperty_isCustomArgs_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyCustomArgs haxorg_NamedProperty_getCustomArgsConst_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyCustomArgs haxorg_NamedProperty_getCustomArgsMut(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedProperty_isCustomRaw_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyCustomRaw haxorg_NamedProperty_getCustomRawConst_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyCustomRaw haxorg_NamedProperty_getCustomRawMut(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedProperty_isCustomId_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyCustomId haxorg_NamedProperty_getCustomIdConst_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyCustomId haxorg_NamedProperty_getCustomIdMut(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedProperty_isCustomSubtreeJson_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyCustomSubtreeJson haxorg_NamedProperty_getCustomSubtreeJsonConst_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyCustomSubtreeJson haxorg_NamedProperty_getCustomSubtreeJsonMut(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedProperty_isCustomSubtreeFlags_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyCustomSubtreeFlags haxorg_NamedProperty_getCustomSubtreeFlagsConst_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyCustomSubtreeFlags haxorg_NamedProperty_getCustomSubtreeFlagsMut(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyKind haxorg_NamedProperty_getKind_const(OrgContext* org_context, haxorg_NamedProperty __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedPropertyNonblocking_get_isBlocking(OrgContext* org_context, haxorg_NamedPropertyNonblocking __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedPropertyNonblocking___eq___const(OrgContext* org_context, haxorg_NamedPropertyNonblocking __this, haxorg_NamedPropertyNonblocking other);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyNonblocking(OrgContext* org_context, haxorg_NamedPropertyNonblocking* obj);
HAXORG_C_API_LINKAGE haxorg_UserTime haxorg_NamedPropertyArchiveTime_get_time(OrgContext* org_context, haxorg_NamedPropertyArchiveTime __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedPropertyArchiveTime___eq___const(OrgContext* org_context, haxorg_NamedPropertyArchiveTime __this, haxorg_NamedPropertyArchiveTime other);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyArchiveTime(OrgContext* org_context, haxorg_NamedPropertyArchiveTime* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_NamedPropertyArchiveFile_get_file(OrgContext* org_context, haxorg_NamedPropertyArchiveFile __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedPropertyArchiveFile___eq___const(OrgContext* org_context, haxorg_NamedPropertyArchiveFile __this, haxorg_NamedPropertyArchiveFile other);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyArchiveFile(OrgContext* org_context, haxorg_NamedPropertyArchiveFile* obj);
HAXORG_C_API_LINKAGE haxorg_SubtreePath haxorg_NamedPropertyArchiveOlpath_get_path(OrgContext* org_context, haxorg_NamedPropertyArchiveOlpath __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedPropertyArchiveOlpath___eq___const(OrgContext* org_context, haxorg_NamedPropertyArchiveOlpath __this, haxorg_NamedPropertyArchiveOlpath other);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyArchiveOlpath(OrgContext* org_context, haxorg_NamedPropertyArchiveOlpath* obj);
HAXORG_C_API_LINKAGE haxorg_SubtreePath haxorg_NamedPropertyArchiveTarget_get_path(OrgContext* org_context, haxorg_NamedPropertyArchiveTarget __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_NamedPropertyArchiveTarget_get_pattern(OrgContext* org_context, haxorg_NamedPropertyArchiveTarget __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedPropertyArchiveTarget___eq___const(OrgContext* org_context, haxorg_NamedPropertyArchiveTarget __this, haxorg_NamedPropertyArchiveTarget other);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyArchiveTarget(OrgContext* org_context, haxorg_NamedPropertyArchiveTarget* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_NamedPropertyArchiveCategory_get_category(OrgContext* org_context, haxorg_NamedPropertyArchiveCategory __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedPropertyArchiveCategory___eq___const(OrgContext* org_context, haxorg_NamedPropertyArchiveCategory __this, haxorg_NamedPropertyArchiveCategory other);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyArchiveCategory(OrgContext* org_context, haxorg_NamedPropertyArchiveCategory* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_NamedPropertyArchiveTodo_get_todo(OrgContext* org_context, haxorg_NamedPropertyArchiveTodo __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedPropertyArchiveTodo___eq___const(OrgContext* org_context, haxorg_NamedPropertyArchiveTodo __this, haxorg_NamedPropertyArchiveTodo other);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyArchiveTodo(OrgContext* org_context, haxorg_NamedPropertyArchiveTodo* obj);
HAXORG_C_API_LINKAGE bool haxorg_NamedPropertyTrigger___eq___const(OrgContext* org_context, haxorg_NamedPropertyTrigger __this, haxorg_NamedPropertyTrigger other);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyTrigger(OrgContext* org_context, haxorg_NamedPropertyTrigger* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_NamedPropertyExportLatexClass_get_latexClass(OrgContext* org_context, haxorg_NamedPropertyExportLatexClass __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedPropertyExportLatexClass___eq___const(OrgContext* org_context, haxorg_NamedPropertyExportLatexClass __this, haxorg_NamedPropertyExportLatexClass other);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyExportLatexClass(OrgContext* org_context, haxorg_NamedPropertyExportLatexClass* obj);
HAXORG_C_API_LINKAGE bool haxorg_NamedPropertyCookieData_get_isRecursive(OrgContext* org_context, haxorg_NamedPropertyCookieData __this);
HAXORG_C_API_LINKAGE haxorg_SubtreeTodoSource haxorg_NamedPropertyCookieData_get_source(OrgContext* org_context, haxorg_NamedPropertyCookieData __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedPropertyCookieData___eq___const(OrgContext* org_context, haxorg_NamedPropertyCookieData __this, haxorg_NamedPropertyCookieData other);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyCookieData(OrgContext* org_context, haxorg_NamedPropertyCookieData* obj);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfStr haxorg_NamedPropertyExportLatexClassOptions_get_options(OrgContext* org_context, haxorg_NamedPropertyExportLatexClassOptions __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedPropertyExportLatexClassOptions___eq___const(OrgContext* org_context, haxorg_NamedPropertyExportLatexClassOptions __this, haxorg_NamedPropertyExportLatexClassOptions other);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyExportLatexClassOptions(OrgContext* org_context, haxorg_NamedPropertyExportLatexClassOptions* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_NamedPropertyExportLatexHeader_get_header(OrgContext* org_context, haxorg_NamedPropertyExportLatexHeader __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedPropertyExportLatexHeader___eq___const(OrgContext* org_context, haxorg_NamedPropertyExportLatexHeader __this, haxorg_NamedPropertyExportLatexHeader other);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyExportLatexHeader(OrgContext* org_context, haxorg_NamedPropertyExportLatexHeader* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_NamedPropertyExportLatexCompiler_get_compiler(OrgContext* org_context, haxorg_NamedPropertyExportLatexCompiler __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedPropertyExportLatexCompiler___eq___const(OrgContext* org_context, haxorg_NamedPropertyExportLatexCompiler __this, haxorg_NamedPropertyExportLatexCompiler other);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyExportLatexCompiler(OrgContext* org_context, haxorg_NamedPropertyExportLatexCompiler* obj);
HAXORG_C_API_LINKAGE bool haxorg_NamedPropertyOrdered_get_isOrdered(OrgContext* org_context, haxorg_NamedPropertyOrdered __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedPropertyOrdered___eq___const(OrgContext* org_context, haxorg_NamedPropertyOrdered __this, haxorg_NamedPropertyOrdered other);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyOrdered(OrgContext* org_context, haxorg_NamedPropertyOrdered* obj);
HAXORG_C_API_LINKAGE int haxorg_NamedPropertyEffort_get_hours(OrgContext* org_context, haxorg_NamedPropertyEffort __this);
HAXORG_C_API_LINKAGE int haxorg_NamedPropertyEffort_get_minutes(OrgContext* org_context, haxorg_NamedPropertyEffort __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedPropertyEffort___eq___const(OrgContext* org_context, haxorg_NamedPropertyEffort __this, haxorg_NamedPropertyEffort other);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyEffort(OrgContext* org_context, haxorg_NamedPropertyEffort* obj);
HAXORG_C_API_LINKAGE haxorg_NamedPropertyVisibilityLevel haxorg_NamedPropertyVisibility_get_level(OrgContext* org_context, haxorg_NamedPropertyVisibility __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedPropertyVisibility___eq___const(OrgContext* org_context, haxorg_NamedPropertyVisibility __this, haxorg_NamedPropertyVisibility other);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyVisibility(OrgContext* org_context, haxorg_NamedPropertyVisibility* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_NamedPropertyExportOptions_get_backend(OrgContext* org_context, haxorg_NamedPropertyExportOptions __this);
HAXORG_C_API_LINKAGE haxorg_HstdMap haxorg_NamedPropertyExportOptions_get_values(OrgContext* org_context, haxorg_NamedPropertyExportOptions __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedPropertyExportOptions___eq___const(OrgContext* org_context, haxorg_NamedPropertyExportOptions __this, haxorg_NamedPropertyExportOptions other);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyExportOptions(OrgContext* org_context, haxorg_NamedPropertyExportOptions* obj);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfStr haxorg_NamedPropertyBlocker_get_blockers(OrgContext* org_context, haxorg_NamedPropertyBlocker __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedPropertyBlocker___eq___const(OrgContext* org_context, haxorg_NamedPropertyBlocker __this, haxorg_NamedPropertyBlocker other);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyBlocker(OrgContext* org_context, haxorg_NamedPropertyBlocker* obj);
HAXORG_C_API_LINKAGE bool haxorg_NamedPropertyUnnumbered___eq___const(OrgContext* org_context, haxorg_NamedPropertyUnnumbered __this, haxorg_NamedPropertyUnnumbered other);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyUnnumbered(OrgContext* org_context, haxorg_NamedPropertyUnnumbered* obj);
HAXORG_C_API_LINKAGE haxorg_UserTime haxorg_NamedPropertyCreated_get_time(OrgContext* org_context, haxorg_NamedPropertyCreated __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedPropertyCreated___eq___const(OrgContext* org_context, haxorg_NamedPropertyCreated __this, haxorg_NamedPropertyCreated other);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyCreated(OrgContext* org_context, haxorg_NamedPropertyCreated* obj);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfStr haxorg_NamedPropertyRadioId_get_words(OrgContext* org_context, haxorg_NamedPropertyRadioId __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedPropertyRadioId___eq___const(OrgContext* org_context, haxorg_NamedPropertyRadioId __this, haxorg_NamedPropertyRadioId other);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyRadioId(OrgContext* org_context, haxorg_NamedPropertyRadioId* obj);
HAXORG_C_API_LINKAGE haxorg_HashTagText haxorg_NamedPropertyHashtagDef_get_hashtag(OrgContext* org_context, haxorg_NamedPropertyHashtagDef __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedPropertyHashtagDef___eq___const(OrgContext* org_context, haxorg_NamedPropertyHashtagDef __this, haxorg_NamedPropertyHashtagDef other);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyHashtagDef(OrgContext* org_context, haxorg_NamedPropertyHashtagDef* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_NamedPropertyCustomArgs_get_name(OrgContext* org_context, haxorg_NamedPropertyCustomArgs __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_NamedPropertyCustomArgs_get_sub(OrgContext* org_context, haxorg_NamedPropertyCustomArgs __this);
HAXORG_C_API_LINKAGE haxorg_AttrGroup haxorg_NamedPropertyCustomArgs_get_attrs(OrgContext* org_context, haxorg_NamedPropertyCustomArgs __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedPropertyCustomArgs___eq___const(OrgContext* org_context, haxorg_NamedPropertyCustomArgs __this, haxorg_NamedPropertyCustomArgs other);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyCustomArgs(OrgContext* org_context, haxorg_NamedPropertyCustomArgs* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_NamedPropertyCustomRaw_get_name(OrgContext* org_context, haxorg_NamedPropertyCustomRaw __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_NamedPropertyCustomRaw_get_value(OrgContext* org_context, haxorg_NamedPropertyCustomRaw __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedPropertyCustomRaw___eq___const(OrgContext* org_context, haxorg_NamedPropertyCustomRaw __this, haxorg_NamedPropertyCustomRaw other);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyCustomRaw(OrgContext* org_context, haxorg_NamedPropertyCustomRaw* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_NamedPropertyCustomId_get_value(OrgContext* org_context, haxorg_NamedPropertyCustomId __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedPropertyCustomId___eq___const(OrgContext* org_context, haxorg_NamedPropertyCustomId __this, haxorg_NamedPropertyCustomId other);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyCustomId(OrgContext* org_context, haxorg_NamedPropertyCustomId* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_NamedPropertyCustomSubtreeJson_get_name(OrgContext* org_context, haxorg_NamedPropertyCustomSubtreeJson __this);
HAXORG_C_API_LINKAGE haxorg_OrgJson haxorg_NamedPropertyCustomSubtreeJson_get_value(OrgContext* org_context, haxorg_NamedPropertyCustomSubtreeJson __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedPropertyCustomSubtreeJson___eq___const(OrgContext* org_context, haxorg_NamedPropertyCustomSubtreeJson __this, haxorg_NamedPropertyCustomSubtreeJson other);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyCustomSubtreeJson(OrgContext* org_context, haxorg_NamedPropertyCustomSubtreeJson* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_NamedPropertyCustomSubtreeFlags_get_name(OrgContext* org_context, haxorg_NamedPropertyCustomSubtreeFlags __this);
HAXORG_C_API_LINKAGE haxorg_AttrGroup haxorg_NamedPropertyCustomSubtreeFlags_get_value(OrgContext* org_context, haxorg_NamedPropertyCustomSubtreeFlags __this);
HAXORG_C_API_LINKAGE bool haxorg_NamedPropertyCustomSubtreeFlags___eq___const(OrgContext* org_context, haxorg_NamedPropertyCustomSubtreeFlags __this, haxorg_NamedPropertyCustomSubtreeFlags other);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyCustomSubtreeFlags(OrgContext* org_context, haxorg_NamedPropertyCustomSubtreeFlags* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedProperty(OrgContext* org_context, haxorg_NamedProperty* obj);
HAXORG_C_API_LINKAGE bool haxorg_OrgDiagnostics___eq___const(OrgContext* org_context, haxorg_OrgDiagnostics __this, haxorg_OrgDiagnostics other);
HAXORG_C_API_LINKAGE bool haxorg_OrgDiagnostics_isParseTokenError_const(OrgContext* org_context, haxorg_OrgDiagnostics __this);
HAXORG_C_API_LINKAGE haxorg_OrgDiagnosticsParseTokenError haxorg_OrgDiagnostics_getParseTokenErrorConst_const(OrgContext* org_context, haxorg_OrgDiagnostics __this);
HAXORG_C_API_LINKAGE haxorg_OrgDiagnosticsParseTokenError haxorg_OrgDiagnostics_getParseTokenErrorMut(OrgContext* org_context, haxorg_OrgDiagnostics __this);
HAXORG_C_API_LINKAGE bool haxorg_OrgDiagnostics_isParseError_const(OrgContext* org_context, haxorg_OrgDiagnostics __this);
HAXORG_C_API_LINKAGE haxorg_OrgDiagnosticsParseError haxorg_OrgDiagnostics_getParseErrorConst_const(OrgContext* org_context, haxorg_OrgDiagnostics __this);
HAXORG_C_API_LINKAGE haxorg_OrgDiagnosticsParseError haxorg_OrgDiagnostics_getParseErrorMut(OrgContext* org_context, haxorg_OrgDiagnostics __this);
HAXORG_C_API_LINKAGE bool haxorg_OrgDiagnostics_isIncludeError_const(OrgContext* org_context, haxorg_OrgDiagnostics __this);
HAXORG_C_API_LINKAGE haxorg_OrgDiagnosticsIncludeError haxorg_OrgDiagnostics_getIncludeErrorConst_const(OrgContext* org_context, haxorg_OrgDiagnostics __this);
HAXORG_C_API_LINKAGE haxorg_OrgDiagnosticsIncludeError haxorg_OrgDiagnostics_getIncludeErrorMut(OrgContext* org_context, haxorg_OrgDiagnostics __this);
HAXORG_C_API_LINKAGE bool haxorg_OrgDiagnostics_isConvertError_const(OrgContext* org_context, haxorg_OrgDiagnostics __this);
HAXORG_C_API_LINKAGE haxorg_OrgDiagnosticsConvertError haxorg_OrgDiagnostics_getConvertErrorConst_const(OrgContext* org_context, haxorg_OrgDiagnostics __this);
HAXORG_C_API_LINKAGE haxorg_OrgDiagnosticsConvertError haxorg_OrgDiagnostics_getConvertErrorMut(OrgContext* org_context, haxorg_OrgDiagnostics __this);
HAXORG_C_API_LINKAGE bool haxorg_OrgDiagnostics_isInternalError_const(OrgContext* org_context, haxorg_OrgDiagnostics __this);
HAXORG_C_API_LINKAGE haxorg_OrgDiagnosticsInternalError haxorg_OrgDiagnostics_getInternalErrorConst_const(OrgContext* org_context, haxorg_OrgDiagnostics __this);
HAXORG_C_API_LINKAGE haxorg_OrgDiagnosticsInternalError haxorg_OrgDiagnostics_getInternalErrorMut(OrgContext* org_context, haxorg_OrgDiagnostics __this);
HAXORG_C_API_LINKAGE haxorg_OrgDiagnosticsKind haxorg_OrgDiagnostics_getKind_const(OrgContext* org_context, haxorg_OrgDiagnostics __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_OrgDiagnosticsParseTokenError_get_brief(OrgContext* org_context, haxorg_OrgDiagnosticsParseTokenError __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_OrgDiagnosticsParseTokenError_get_detail(OrgContext* org_context, haxorg_OrgDiagnosticsParseTokenError __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_OrgDiagnosticsParseTokenError_get_parserFunction(OrgContext* org_context, haxorg_OrgDiagnosticsParseTokenError __this);
HAXORG_C_API_LINKAGE int haxorg_OrgDiagnosticsParseTokenError_get_parserLine(OrgContext* org_context, haxorg_OrgDiagnosticsParseTokenError __this);
HAXORG_C_API_LINKAGE haxorg_OrgTokenKind haxorg_OrgDiagnosticsParseTokenError_get_tokenKind(OrgContext* org_context, haxorg_OrgDiagnosticsParseTokenError __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_OrgDiagnosticsParseTokenError_get_tokenText(OrgContext* org_context, haxorg_OrgDiagnosticsParseTokenError __this);
HAXORG_C_API_LINKAGE haxorg_ParseSourceLoc haxorg_OrgDiagnosticsParseTokenError_get_loc(OrgContext* org_context, haxorg_OrgDiagnosticsParseTokenError __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_OrgDiagnosticsParseTokenError_get_errName(OrgContext* org_context, haxorg_OrgDiagnosticsParseTokenError __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_OrgDiagnosticsParseTokenError_get_errCode(OrgContext* org_context, haxorg_OrgDiagnosticsParseTokenError __this);
HAXORG_C_API_LINKAGE bool haxorg_OrgDiagnosticsParseTokenError___eq___const(OrgContext* org_context, haxorg_OrgDiagnosticsParseTokenError __this, haxorg_OrgDiagnosticsParseTokenError other);
HAXORG_C_API_LINKAGE void haxorg_destroy_OrgDiagnosticsParseTokenError(OrgContext* org_context, haxorg_OrgDiagnosticsParseTokenError* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_OrgDiagnosticsParseError_get_brief(OrgContext* org_context, haxorg_OrgDiagnosticsParseError __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_OrgDiagnosticsParseError_get_detail(OrgContext* org_context, haxorg_OrgDiagnosticsParseError __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_OrgDiagnosticsParseError_get_parserFunction(OrgContext* org_context, haxorg_OrgDiagnosticsParseError __this);
HAXORG_C_API_LINKAGE int haxorg_OrgDiagnosticsParseError_get_parserLine(OrgContext* org_context, haxorg_OrgDiagnosticsParseError __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_OrgDiagnosticsParseError_get_errName(OrgContext* org_context, haxorg_OrgDiagnosticsParseError __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_OrgDiagnosticsParseError_get_errCode(OrgContext* org_context, haxorg_OrgDiagnosticsParseError __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_OrgDiagnosticsParseError_get_loc(OrgContext* org_context, haxorg_OrgDiagnosticsParseError __this);
HAXORG_C_API_LINKAGE bool haxorg_OrgDiagnosticsParseError___eq___const(OrgContext* org_context, haxorg_OrgDiagnosticsParseError __this, haxorg_OrgDiagnosticsParseError other);
HAXORG_C_API_LINKAGE void haxorg_destroy_OrgDiagnosticsParseError(OrgContext* org_context, haxorg_OrgDiagnosticsParseError* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_OrgDiagnosticsIncludeError_get_brief(OrgContext* org_context, haxorg_OrgDiagnosticsIncludeError __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_OrgDiagnosticsIncludeError_get_targetPath(OrgContext* org_context, haxorg_OrgDiagnosticsIncludeError __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_OrgDiagnosticsIncludeError_get_workingFile(OrgContext* org_context, haxorg_OrgDiagnosticsIncludeError __this);
HAXORG_C_API_LINKAGE bool haxorg_OrgDiagnosticsIncludeError___eq___const(OrgContext* org_context, haxorg_OrgDiagnosticsIncludeError __this, haxorg_OrgDiagnosticsIncludeError other);
HAXORG_C_API_LINKAGE void haxorg_destroy_OrgDiagnosticsIncludeError(OrgContext* org_context, haxorg_OrgDiagnosticsIncludeError* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_OrgDiagnosticsConvertError_get_brief(OrgContext* org_context, haxorg_OrgDiagnosticsConvertError __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_OrgDiagnosticsConvertError_get_detail(OrgContext* org_context, haxorg_OrgDiagnosticsConvertError __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_OrgDiagnosticsConvertError_get_convertFunction(OrgContext* org_context, haxorg_OrgDiagnosticsConvertError __this);
HAXORG_C_API_LINKAGE int haxorg_OrgDiagnosticsConvertError_get_convertLine(OrgContext* org_context, haxorg_OrgDiagnosticsConvertError __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_OrgDiagnosticsConvertError_get_convertFile(OrgContext* org_context, haxorg_OrgDiagnosticsConvertError __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_OrgDiagnosticsConvertError_get_errName(OrgContext* org_context, haxorg_OrgDiagnosticsConvertError __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_OrgDiagnosticsConvertError_get_errCode(OrgContext* org_context, haxorg_OrgDiagnosticsConvertError __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_OrgDiagnosticsConvertError_get_loc(OrgContext* org_context, haxorg_OrgDiagnosticsConvertError __this);
HAXORG_C_API_LINKAGE bool haxorg_OrgDiagnosticsConvertError___eq___const(OrgContext* org_context, haxorg_OrgDiagnosticsConvertError __this, haxorg_OrgDiagnosticsConvertError other);
HAXORG_C_API_LINKAGE void haxorg_destroy_OrgDiagnosticsConvertError(OrgContext* org_context, haxorg_OrgDiagnosticsConvertError* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_OrgDiagnosticsInternalError_get_message(OrgContext* org_context, haxorg_OrgDiagnosticsInternalError __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_OrgDiagnosticsInternalError_get_function(OrgContext* org_context, haxorg_OrgDiagnosticsInternalError __this);
HAXORG_C_API_LINKAGE int haxorg_OrgDiagnosticsInternalError_get_line(OrgContext* org_context, haxorg_OrgDiagnosticsInternalError __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_OrgDiagnosticsInternalError_get_file(OrgContext* org_context, haxorg_OrgDiagnosticsInternalError __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_OrgDiagnosticsInternalError_get_loc(OrgContext* org_context, haxorg_OrgDiagnosticsInternalError __this);
HAXORG_C_API_LINKAGE bool haxorg_OrgDiagnosticsInternalError___eq___const(OrgContext* org_context, haxorg_OrgDiagnosticsInternalError __this, haxorg_OrgDiagnosticsInternalError other);
HAXORG_C_API_LINKAGE void haxorg_destroy_OrgDiagnosticsInternalError(OrgContext* org_context, haxorg_OrgDiagnosticsInternalError* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_OrgDiagnostics(OrgContext* org_context, haxorg_OrgDiagnostics* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NoNode(OrgContext* org_context, haxorg_NoNode* obj);
HAXORG_C_API_LINKAGE haxorg_OrgDiagnostics haxorg_ErrorItem_get_diag(OrgContext* org_context, haxorg_ErrorItem __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_ErrorItem(OrgContext* org_context, haxorg_ErrorItem* obj);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfSemIdOfErrorItem haxorg_ErrorGroup_get_diagnostics(OrgContext* org_context, haxorg_ErrorGroup __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_ErrorGroup(OrgContext* org_context, haxorg_ErrorGroup* obj);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfSemIdOfOrg haxorg_Stmt_get_attached(OrgContext* org_context, haxorg_Stmt __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfSemIdOfOrg haxorg_Stmt_getAttached_const(OrgContext* org_context, haxorg_Stmt __this, haxorg_HstdOpt kind);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfSemIdOfOrg haxorg_Stmt_getCaption_const(OrgContext* org_context, haxorg_Stmt __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfStr haxorg_Stmt_getName_const(OrgContext* org_context, haxorg_Stmt __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfAttrValue haxorg_Stmt_getAttrs_const(OrgContext* org_context, haxorg_Stmt __this, haxorg_HstdOpt kind);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Stmt_getFirstAttr_const(OrgContext* org_context, haxorg_Stmt __this, haxorg_HstdStr kind);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Stmt_getFirstAttrString_const(OrgContext* org_context, haxorg_Stmt __this, haxorg_HstdStr kind);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Stmt_getFirstAttrInt_const(OrgContext* org_context, haxorg_Stmt __this, haxorg_HstdStr kind);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Stmt_getFirstAttrBool_const(OrgContext* org_context, haxorg_Stmt __this, haxorg_HstdStr kind);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Stmt_getFirstAttrDouble_const(OrgContext* org_context, haxorg_Stmt __this, haxorg_HstdStr kind);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Stmt_getFirstAttrLisp_const(OrgContext* org_context, haxorg_Stmt __this, haxorg_HstdStr kind);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Stmt_getFirstAttrKind_const(OrgContext* org_context, haxorg_Stmt __this, haxorg_HstdStr kind);
HAXORG_C_API_LINKAGE void haxorg_destroy_Stmt(OrgContext* org_context, haxorg_Stmt* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Inline(OrgContext* org_context, haxorg_Inline* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_StmtList(OrgContext* org_context, haxorg_StmtList* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Empty(OrgContext* org_context, haxorg_Empty* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_Leaf_get_text(OrgContext* org_context, haxorg_Leaf __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_Leaf_getText_const(OrgContext* org_context, haxorg_Leaf __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_Leaf(OrgContext* org_context, haxorg_Leaf* obj);
HAXORG_C_API_LINKAGE bool haxorg_Time_get_isActive(OrgContext* org_context, haxorg_Time __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Time_getYear_const(OrgContext* org_context, haxorg_Time __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Time_getMonth_const(OrgContext* org_context, haxorg_Time __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Time_getDay_const(OrgContext* org_context, haxorg_Time __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Time_getHour_const(OrgContext* org_context, haxorg_Time __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Time_getMinute_const(OrgContext* org_context, haxorg_Time __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Time_getSecond_const(OrgContext* org_context, haxorg_Time __this);
HAXORG_C_API_LINKAGE haxorg_UserTime haxorg_Time_getStaticTime_const(OrgContext* org_context, haxorg_Time __this);
HAXORG_C_API_LINKAGE bool haxorg_Time_isStatic_const(OrgContext* org_context, haxorg_Time __this);
HAXORG_C_API_LINKAGE haxorg_TimeStatic haxorg_Time_getStaticConst_const(OrgContext* org_context, haxorg_Time __this);
HAXORG_C_API_LINKAGE haxorg_TimeStatic haxorg_Time_getStaticMut(OrgContext* org_context, haxorg_Time __this);
HAXORG_C_API_LINKAGE bool haxorg_Time_isDynamic_const(OrgContext* org_context, haxorg_Time __this);
HAXORG_C_API_LINKAGE haxorg_TimeDynamic haxorg_Time_getDynamicConst_const(OrgContext* org_context, haxorg_Time __this);
HAXORG_C_API_LINKAGE haxorg_TimeDynamic haxorg_Time_getDynamicMut(OrgContext* org_context, haxorg_Time __this);
HAXORG_C_API_LINKAGE haxorg_TimeTimeKind haxorg_Time_getTimeKind_const(OrgContext* org_context, haxorg_Time __this);
HAXORG_C_API_LINKAGE haxorg_TimeRepeatMode haxorg_TimeRepeat_get_mode(OrgContext* org_context, haxorg_TimeRepeat __this);
HAXORG_C_API_LINKAGE haxorg_TimeRepeatPeriod haxorg_TimeRepeat_get_period(OrgContext* org_context, haxorg_TimeRepeat __this);
HAXORG_C_API_LINKAGE int haxorg_TimeRepeat_get_count(OrgContext* org_context, haxorg_TimeRepeat __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_TimeRepeat(OrgContext* org_context, haxorg_TimeRepeat* obj);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfTimeRepeat haxorg_TimeStatic_get_repeat(OrgContext* org_context, haxorg_TimeStatic __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_TimeStatic_get_warn(OrgContext* org_context, haxorg_TimeStatic __this);
HAXORG_C_API_LINKAGE haxorg_UserTime haxorg_TimeStatic_get_time(OrgContext* org_context, haxorg_TimeStatic __this);
HAXORG_C_API_LINKAGE void haxorg_create_TimeStatic_Static(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_TimeStatic(OrgContext* org_context, haxorg_TimeStatic* obj);
HAXORG_C_API_LINKAGE haxorg_LispCode haxorg_TimeDynamic_get_expr(OrgContext* org_context, haxorg_TimeDynamic __this);
HAXORG_C_API_LINKAGE void haxorg_create_TimeDynamic_Dynamic(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_TimeDynamic(OrgContext* org_context, haxorg_TimeDynamic* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Time(OrgContext* org_context, haxorg_Time* obj);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_TimeRange_get_from(OrgContext* org_context, haxorg_TimeRange __this);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_TimeRange_get_to(OrgContext* org_context, haxorg_TimeRange __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_TimeRange_getClockedTimeSeconds_const(OrgContext* org_context, haxorg_TimeRange __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_TimeRange(OrgContext* org_context, haxorg_TimeRange* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_Macro_get_name(OrgContext* org_context, haxorg_Macro __this);
HAXORG_C_API_LINKAGE haxorg_AttrGroup haxorg_Macro_get_attrs(OrgContext* org_context, haxorg_Macro __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_Macro(OrgContext* org_context, haxorg_Macro* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_Symbol_get_name(OrgContext* org_context, haxorg_Symbol __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfSymbolParam haxorg_Symbol_get_parameters(OrgContext* org_context, haxorg_Symbol __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfSemIdOfOrg haxorg_Symbol_get_positional(OrgContext* org_context, haxorg_Symbol __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_SymbolParam_get_key(OrgContext* org_context, haxorg_SymbolParam __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_SymbolParam_get_value(OrgContext* org_context, haxorg_SymbolParam __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_SymbolParam(OrgContext* org_context, haxorg_SymbolParam* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Symbol(OrgContext* org_context, haxorg_Symbol* obj);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfSemIdOfErrorSkipToken haxorg_ErrorSkipGroup_get_skipped(OrgContext* org_context, haxorg_ErrorSkipGroup __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_ErrorSkipGroup(OrgContext* org_context, haxorg_ErrorSkipGroup* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Markup(OrgContext* org_context, haxorg_Markup* obj);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfStr haxorg_RadioTarget_get_words(OrgContext* org_context, haxorg_RadioTarget __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_RadioTarget(OrgContext* org_context, haxorg_RadioTarget* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Latex(OrgContext* org_context, haxorg_Latex* obj);
HAXORG_C_API_LINKAGE haxorg_SubtreeLogHead haxorg_SubtreeLog_get_head(OrgContext* org_context, haxorg_SubtreeLog __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_SubtreeLog_get_desc(OrgContext* org_context, haxorg_SubtreeLog __this);
HAXORG_C_API_LINKAGE void haxorg_SubtreeLog_setDescription(OrgContext* org_context, haxorg_SubtreeLog __this, haxorg_SemIdOfOrg desc);
HAXORG_C_API_LINKAGE void haxorg_destroy_SubtreeLog(OrgContext* org_context, haxorg_SubtreeLog* obj);
HAXORG_C_API_LINKAGE int haxorg_Subtree_get_level(OrgContext* org_context, haxorg_Subtree __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Subtree_get_treeId(OrgContext* org_context, haxorg_Subtree __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Subtree_get_todo(OrgContext* org_context, haxorg_Subtree __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Subtree_get_completion(OrgContext* org_context, haxorg_Subtree __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Subtree_get_description(OrgContext* org_context, haxorg_Subtree __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfSemIdOfHashTag haxorg_Subtree_get_tags(OrgContext* org_context, haxorg_Subtree __this);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_Subtree_get_title(OrgContext* org_context, haxorg_Subtree __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfSemIdOfSubtreeLog haxorg_Subtree_get_logbook(OrgContext* org_context, haxorg_Subtree __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfNamedProperty haxorg_Subtree_get_properties(OrgContext* org_context, haxorg_Subtree __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Subtree_get_closed(OrgContext* org_context, haxorg_Subtree __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Subtree_get_deadline(OrgContext* org_context, haxorg_Subtree __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Subtree_get_scheduled(OrgContext* org_context, haxorg_Subtree __this);
HAXORG_C_API_LINKAGE bool haxorg_Subtree_get_isComment(OrgContext* org_context, haxorg_Subtree __this);
HAXORG_C_API_LINKAGE bool haxorg_Subtree_get_isArchived(OrgContext* org_context, haxorg_Subtree __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Subtree_get_priority(OrgContext* org_context, haxorg_Subtree __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfSubtreePeriod haxorg_Subtree_getTimePeriods_const(OrgContext* org_context, haxorg_Subtree __this, haxorg_HstdIntSet kinds);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfNamedProperty haxorg_Subtree_getProperties_const(OrgContext* org_context, haxorg_Subtree __this, haxorg_HstdStr kind, haxorg_HstdOpt subkind);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Subtree_getProperty_const(OrgContext* org_context, haxorg_Subtree __this, haxorg_HstdStr kind, haxorg_HstdOpt subkind);
HAXORG_C_API_LINKAGE void haxorg_Subtree_removeProperty(OrgContext* org_context, haxorg_Subtree __this, haxorg_HstdStr kind, haxorg_HstdOpt subkind);
HAXORG_C_API_LINKAGE void haxorg_Subtree_setProperty(OrgContext* org_context, haxorg_Subtree __this, haxorg_NamedProperty value);
HAXORG_C_API_LINKAGE void haxorg_Subtree_setPropertyStrValue(OrgContext* org_context, haxorg_Subtree __this, haxorg_HstdStr value, haxorg_HstdStr kind, haxorg_HstdOpt subkind);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_Subtree_getCleanTitle_const(OrgContext* org_context, haxorg_Subtree __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Subtree_getTodoKeyword_const(OrgContext* org_context, haxorg_Subtree __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_Subtree(OrgContext* org_context, haxorg_Subtree* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ColonExample(OrgContext* org_context, haxorg_ColonExample* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_Call_get_name(OrgContext* org_context, haxorg_Call __this);
HAXORG_C_API_LINKAGE haxorg_AttrGroup haxorg_Call_get_attrs(OrgContext* org_context, haxorg_Call __this);
HAXORG_C_API_LINKAGE bool haxorg_Call_get_isCommand(OrgContext* org_context, haxorg_Call __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_Call(OrgContext* org_context, haxorg_Call* obj);
HAXORG_C_API_LINKAGE haxorg_CheckboxState haxorg_ListItem_get_checkbox(OrgContext* org_context, haxorg_ListItem __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ListItem_get_header(OrgContext* org_context, haxorg_ListItem __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ListItem_get_bullet(OrgContext* org_context, haxorg_ListItem __this);
HAXORG_C_API_LINKAGE bool haxorg_ListItem_isDescriptionItem_const(OrgContext* org_context, haxorg_ListItem __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ListItem_getCleanHeader_const(OrgContext* org_context, haxorg_ListItem __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_ListItem(OrgContext* org_context, haxorg_ListItem* obj);
HAXORG_C_API_LINKAGE haxorg_InitialSubtreeVisibility haxorg_DocumentOptions_get_initialVisibility(OrgContext* org_context, haxorg_DocumentOptions __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfNamedProperty haxorg_DocumentOptions_get_properties(OrgContext* org_context, haxorg_DocumentOptions __this);
HAXORG_C_API_LINKAGE haxorg_DocumentExportConfig haxorg_DocumentOptions_get_exportConfig(OrgContext* org_context, haxorg_DocumentOptions __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentOptions_get_fixedWidthSections(OrgContext* org_context, haxorg_DocumentOptions __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentOptions_get_startupIndented(OrgContext* org_context, haxorg_DocumentOptions __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentOptions_get_category(OrgContext* org_context, haxorg_DocumentOptions __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentOptions_get_setupfile(OrgContext* org_context, haxorg_DocumentOptions __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentOptions_get_maxSubtreeLevelExport(OrgContext* org_context, haxorg_DocumentOptions __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentOptions_get_columns(OrgContext* org_context, haxorg_DocumentOptions __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfTodoKeyword haxorg_DocumentOptions_get_todoKeywords(OrgContext* org_context, haxorg_DocumentOptions __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfTodoKeyword haxorg_DocumentOptions_get_doneKeywords(OrgContext* org_context, haxorg_DocumentOptions __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfNamedProperty haxorg_DocumentOptions_getProperties_const(OrgContext* org_context, haxorg_DocumentOptions __this, haxorg_HstdStr kind, haxorg_HstdOpt subKind);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_DocumentOptions_getProperty_const(OrgContext* org_context, haxorg_DocumentOptions __this, haxorg_HstdStr kind, haxorg_HstdOpt subKind);
HAXORG_C_API_LINKAGE void haxorg_destroy_DocumentOptions(OrgContext* org_context, haxorg_DocumentOptions* obj);
HAXORG_C_API_LINKAGE int haxorg_DocumentFragment_get_baseLine(OrgContext* org_context, haxorg_DocumentFragment __this);
HAXORG_C_API_LINKAGE int haxorg_DocumentFragment_get_baseCol(OrgContext* org_context, haxorg_DocumentFragment __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_DocumentFragment(OrgContext* org_context, haxorg_DocumentFragment* obj);
HAXORG_C_API_LINKAGE haxorg_CriticMarkupKind haxorg_CriticMarkup_get_kind(OrgContext* org_context, haxorg_CriticMarkup __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_CriticMarkup(OrgContext* org_context, haxorg_CriticMarkup* obj);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Document_get_title(OrgContext* org_context, haxorg_Document __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Document_get_author(OrgContext* org_context, haxorg_Document __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Document_get_creator(OrgContext* org_context, haxorg_Document __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfSemIdOfHashTag haxorg_Document_get_filetags(OrgContext* org_context, haxorg_Document __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Document_get_email(OrgContext* org_context, haxorg_Document __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfStr haxorg_Document_get_language(OrgContext* org_context, haxorg_Document __this);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_Document_get_options(OrgContext* org_context, haxorg_Document __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Document_get_exportFileName(OrgContext* org_context, haxorg_Document __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfNamedProperty haxorg_Document_getProperties_const(OrgContext* org_context, haxorg_Document __this, haxorg_HstdStr kind, haxorg_HstdOpt subKind);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Document_getProperty_const(OrgContext* org_context, haxorg_Document __this, haxorg_HstdStr kind, haxorg_HstdOpt subKind);
HAXORG_C_API_LINKAGE void haxorg_destroy_Document(OrgContext* org_context, haxorg_Document* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_FileTarget_get_path(OrgContext* org_context, haxorg_FileTarget __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_FileTarget_get_line(OrgContext* org_context, haxorg_FileTarget __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_FileTarget_get_searchTarget(OrgContext* org_context, haxorg_FileTarget __this);
HAXORG_C_API_LINKAGE bool haxorg_FileTarget_get_restrictToHeadlines(OrgContext* org_context, haxorg_FileTarget __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_FileTarget_get_targetId(OrgContext* org_context, haxorg_FileTarget __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_FileTarget_get_regexp(OrgContext* org_context, haxorg_FileTarget __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_FileTarget(OrgContext* org_context, haxorg_FileTarget* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_TextSeparator(OrgContext* org_context, haxorg_TextSeparator* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_DocumentGroup(OrgContext* org_context, haxorg_DocumentGroup* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_File_get_relPath(OrgContext* org_context, haxorg_File __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_File_get_absPath(OrgContext* org_context, haxorg_File __this);
HAXORG_C_API_LINKAGE bool haxorg_File_isDocument_const(OrgContext* org_context, haxorg_File __this);
HAXORG_C_API_LINKAGE haxorg_FileDocument haxorg_File_getDocumentConst_const(OrgContext* org_context, haxorg_File __this);
HAXORG_C_API_LINKAGE haxorg_FileDocument haxorg_File_getDocumentMut(OrgContext* org_context, haxorg_File __this);
HAXORG_C_API_LINKAGE bool haxorg_File_isAttachment_const(OrgContext* org_context, haxorg_File __this);
HAXORG_C_API_LINKAGE haxorg_FileAttachment haxorg_File_getAttachmentConst_const(OrgContext* org_context, haxorg_File __this);
HAXORG_C_API_LINKAGE haxorg_FileAttachment haxorg_File_getAttachmentMut(OrgContext* org_context, haxorg_File __this);
HAXORG_C_API_LINKAGE bool haxorg_File_isSource_const(OrgContext* org_context, haxorg_File __this);
HAXORG_C_API_LINKAGE haxorg_FileSource haxorg_File_getSourceConst_const(OrgContext* org_context, haxorg_File __this);
HAXORG_C_API_LINKAGE haxorg_FileSource haxorg_File_getSourceMut(OrgContext* org_context, haxorg_File __this);
HAXORG_C_API_LINKAGE haxorg_FileKind haxorg_File_getFileKind_const(OrgContext* org_context, haxorg_File __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_FileDocument(OrgContext* org_context, haxorg_FileDocument* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_FileAttachment(OrgContext* org_context, haxorg_FileAttachment* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_FileSource(OrgContext* org_context, haxorg_FileSource* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_File(OrgContext* org_context, haxorg_File* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_Directory_get_relPath(OrgContext* org_context, haxorg_Directory __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_Directory_get_absPath(OrgContext* org_context, haxorg_Directory __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_Directory(OrgContext* org_context, haxorg_Directory* obj);
HAXORG_C_API_LINKAGE bool haxorg_Symlink_get_isDirectory(OrgContext* org_context, haxorg_Symlink __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_Symlink_get_absPath(OrgContext* org_context, haxorg_Symlink __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_Symlink(OrgContext* org_context, haxorg_Symlink* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_CmdInclude_get_path(OrgContext* org_context, haxorg_CmdInclude __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_CmdInclude_get_firstLine(OrgContext* org_context, haxorg_CmdInclude __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_CmdInclude_get_lastLine(OrgContext* org_context, haxorg_CmdInclude __this);
HAXORG_C_API_LINKAGE bool haxorg_CmdInclude_isExample_const(OrgContext* org_context, haxorg_CmdInclude __this);
HAXORG_C_API_LINKAGE haxorg_CmdIncludeExample haxorg_CmdInclude_getExampleConst_const(OrgContext* org_context, haxorg_CmdInclude __this);
HAXORG_C_API_LINKAGE haxorg_CmdIncludeExample haxorg_CmdInclude_getExampleMut(OrgContext* org_context, haxorg_CmdInclude __this);
HAXORG_C_API_LINKAGE bool haxorg_CmdInclude_isExport_const(OrgContext* org_context, haxorg_CmdInclude __this);
HAXORG_C_API_LINKAGE haxorg_CmdIncludeExport haxorg_CmdInclude_getExportConst_const(OrgContext* org_context, haxorg_CmdInclude __this);
HAXORG_C_API_LINKAGE haxorg_CmdIncludeExport haxorg_CmdInclude_getExportMut(OrgContext* org_context, haxorg_CmdInclude __this);
HAXORG_C_API_LINKAGE bool haxorg_CmdInclude_isCustom_const(OrgContext* org_context, haxorg_CmdInclude __this);
HAXORG_C_API_LINKAGE haxorg_CmdIncludeCustom haxorg_CmdInclude_getCustomConst_const(OrgContext* org_context, haxorg_CmdInclude __this);
HAXORG_C_API_LINKAGE haxorg_CmdIncludeCustom haxorg_CmdInclude_getCustomMut(OrgContext* org_context, haxorg_CmdInclude __this);
HAXORG_C_API_LINKAGE bool haxorg_CmdInclude_isSrc_const(OrgContext* org_context, haxorg_CmdInclude __this);
HAXORG_C_API_LINKAGE haxorg_CmdIncludeSrc haxorg_CmdInclude_getSrcConst_const(OrgContext* org_context, haxorg_CmdInclude __this);
HAXORG_C_API_LINKAGE haxorg_CmdIncludeSrc haxorg_CmdInclude_getSrcMut(OrgContext* org_context, haxorg_CmdInclude __this);
HAXORG_C_API_LINKAGE bool haxorg_CmdInclude_isOrgDocument_const(OrgContext* org_context, haxorg_CmdInclude __this);
HAXORG_C_API_LINKAGE haxorg_CmdIncludeOrgDocument haxorg_CmdInclude_getOrgDocumentConst_const(OrgContext* org_context, haxorg_CmdInclude __this);
HAXORG_C_API_LINKAGE haxorg_CmdIncludeOrgDocument haxorg_CmdInclude_getOrgDocumentMut(OrgContext* org_context, haxorg_CmdInclude __this);
HAXORG_C_API_LINKAGE haxorg_CmdIncludeKind haxorg_CmdInclude_getIncludeKind_const(OrgContext* org_context, haxorg_CmdInclude __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdIncludeIncludeBase(OrgContext* org_context, haxorg_CmdIncludeIncludeBase* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdIncludeExample(OrgContext* org_context, haxorg_CmdIncludeExample* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_CmdIncludeExport_get_language(OrgContext* org_context, haxorg_CmdIncludeExport __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdIncludeExport(OrgContext* org_context, haxorg_CmdIncludeExport* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_CmdIncludeCustom_get_blockName(OrgContext* org_context, haxorg_CmdIncludeCustom __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdIncludeCustom(OrgContext* org_context, haxorg_CmdIncludeCustom* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_CmdIncludeSrc_get_language(OrgContext* org_context, haxorg_CmdIncludeSrc __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdIncludeSrc(OrgContext* org_context, haxorg_CmdIncludeSrc* obj);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_CmdIncludeOrgDocument_get_onlyContent(OrgContext* org_context, haxorg_CmdIncludeOrgDocument __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_CmdIncludeOrgDocument_get_subtreePath(OrgContext* org_context, haxorg_CmdIncludeOrgDocument __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_CmdIncludeOrgDocument_get_minLevel(OrgContext* org_context, haxorg_CmdIncludeOrgDocument __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_CmdIncludeOrgDocument_get_customIdTarget(OrgContext* org_context, haxorg_CmdIncludeOrgDocument __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdIncludeOrgDocument(OrgContext* org_context, haxorg_CmdIncludeOrgDocument* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdInclude(OrgContext* org_context, haxorg_CmdInclude* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmNoNode___eq___const(OrgContext* org_context, haxorg_ImmNoNode __this, haxorg_ImmNoNode other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmNoNode(OrgContext* org_context, haxorg_ImmNoNode* obj);
HAXORG_C_API_LINKAGE haxorg_OrgDiagnostics haxorg_ImmErrorItem_get_diag(OrgContext* org_context, haxorg_ImmErrorItem __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmErrorItem___eq___const(OrgContext* org_context, haxorg_ImmErrorItem __this, haxorg_ImmErrorItem other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmErrorItem(OrgContext* org_context, haxorg_ImmErrorItem* obj);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmErrorGroup_get_diagnostics(OrgContext* org_context, haxorg_ImmErrorGroup __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmErrorGroup___eq___const(OrgContext* org_context, haxorg_ImmErrorGroup __this, haxorg_ImmErrorGroup other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmErrorGroup(OrgContext* org_context, haxorg_ImmErrorGroup* obj);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmStmt_get_attached(OrgContext* org_context, haxorg_ImmStmt __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmStmt___eq___const(OrgContext* org_context, haxorg_ImmStmt __this, haxorg_ImmStmt other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmStmt(OrgContext* org_context, haxorg_ImmStmt* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmInline___eq___const(OrgContext* org_context, haxorg_ImmInline __this, haxorg_ImmInline other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmInline(OrgContext* org_context, haxorg_ImmInline* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmStmtList___eq___const(OrgContext* org_context, haxorg_ImmStmtList __this, haxorg_ImmStmtList other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmStmtList(OrgContext* org_context, haxorg_ImmStmtList* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmEmpty___eq___const(OrgContext* org_context, haxorg_ImmEmpty __this, haxorg_ImmEmpty other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmEmpty(OrgContext* org_context, haxorg_ImmEmpty* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmLeaf_get_text(OrgContext* org_context, haxorg_ImmLeaf __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmLeaf___eq___const(OrgContext* org_context, haxorg_ImmLeaf __this, haxorg_ImmLeaf other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmLeaf(OrgContext* org_context, haxorg_ImmLeaf* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmTime_get_isActive(OrgContext* org_context, haxorg_ImmTime __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmTime___eq___const(OrgContext* org_context, haxorg_ImmTime __this, haxorg_ImmTime other);
HAXORG_C_API_LINKAGE bool haxorg_ImmTime_isStatic_const(OrgContext* org_context, haxorg_ImmTime __this);
HAXORG_C_API_LINKAGE haxorg_ImmTimeStatic haxorg_ImmTime_getStaticConst_const(OrgContext* org_context, haxorg_ImmTime __this);
HAXORG_C_API_LINKAGE haxorg_ImmTimeStatic haxorg_ImmTime_getStaticMut(OrgContext* org_context, haxorg_ImmTime __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmTime_isDynamic_const(OrgContext* org_context, haxorg_ImmTime __this);
HAXORG_C_API_LINKAGE haxorg_ImmTimeDynamic haxorg_ImmTime_getDynamicConst_const(OrgContext* org_context, haxorg_ImmTime __this);
HAXORG_C_API_LINKAGE haxorg_ImmTimeDynamic haxorg_ImmTime_getDynamicMut(OrgContext* org_context, haxorg_ImmTime __this);
HAXORG_C_API_LINKAGE haxorg_ImmTimeTimeKind haxorg_ImmTime_getTimeKind_const(OrgContext* org_context, haxorg_ImmTime __this);
HAXORG_C_API_LINKAGE haxorg_ImmTimeRepeatMode haxorg_ImmTimeRepeat_get_mode(OrgContext* org_context, haxorg_ImmTimeRepeat __this);
HAXORG_C_API_LINKAGE haxorg_ImmTimeRepeatPeriod haxorg_ImmTimeRepeat_get_period(OrgContext* org_context, haxorg_ImmTimeRepeat __this);
HAXORG_C_API_LINKAGE int haxorg_ImmTimeRepeat_get_count(OrgContext* org_context, haxorg_ImmTimeRepeat __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmTimeRepeat___eq___const(OrgContext* org_context, haxorg_ImmTimeRepeat __this, haxorg_ImmTimeRepeat other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmTimeRepeat(OrgContext* org_context, haxorg_ImmTimeRepeat* obj);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmTimeStatic_get_repeat(OrgContext* org_context, haxorg_ImmTimeStatic __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmTimeStatic_get_warn(OrgContext* org_context, haxorg_ImmTimeStatic __this);
HAXORG_C_API_LINKAGE haxorg_UserTime haxorg_ImmTimeStatic_get_time(OrgContext* org_context, haxorg_ImmTimeStatic __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmTimeStatic_Static(OrgContext* org_context);
HAXORG_C_API_LINKAGE bool haxorg_ImmTimeStatic___eq___const(OrgContext* org_context, haxorg_ImmTimeStatic __this, haxorg_ImmTimeStatic other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmTimeStatic(OrgContext* org_context, haxorg_ImmTimeStatic* obj);
HAXORG_C_API_LINKAGE haxorg_LispCode haxorg_ImmTimeDynamic_get_expr(OrgContext* org_context, haxorg_ImmTimeDynamic __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmTimeDynamic_Dynamic(OrgContext* org_context);
HAXORG_C_API_LINKAGE bool haxorg_ImmTimeDynamic___eq___const(OrgContext* org_context, haxorg_ImmTimeDynamic __this, haxorg_ImmTimeDynamic other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmTimeDynamic(OrgContext* org_context, haxorg_ImmTimeDynamic* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmTime(OrgContext* org_context, haxorg_ImmTime* obj);
HAXORG_C_API_LINKAGE haxorg_ImmId haxorg_ImmTimeRange_get_from(OrgContext* org_context, haxorg_ImmTimeRange __this);
HAXORG_C_API_LINKAGE haxorg_ImmId haxorg_ImmTimeRange_get_to(OrgContext* org_context, haxorg_ImmTimeRange __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmTimeRange___eq___const(OrgContext* org_context, haxorg_ImmTimeRange __this, haxorg_ImmTimeRange other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmTimeRange(OrgContext* org_context, haxorg_ImmTimeRange* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmMacro_get_name(OrgContext* org_context, haxorg_ImmMacro __this);
HAXORG_C_API_LINKAGE haxorg_AttrGroup haxorg_ImmMacro_get_attrs(OrgContext* org_context, haxorg_ImmMacro __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmMacro___eq___const(OrgContext* org_context, haxorg_ImmMacro __this, haxorg_ImmMacro other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmMacro(OrgContext* org_context, haxorg_ImmMacro* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmSymbol_get_name(OrgContext* org_context, haxorg_ImmSymbol __this);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmSymbol_get_parameters(OrgContext* org_context, haxorg_ImmSymbol __this);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmSymbol_get_positional(OrgContext* org_context, haxorg_ImmSymbol __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmSymbol___eq___const(OrgContext* org_context, haxorg_ImmSymbol __this, haxorg_ImmSymbol other);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmSymbolParam_get_key(OrgContext* org_context, haxorg_ImmSymbolParam __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmSymbolParam_get_value(OrgContext* org_context, haxorg_ImmSymbolParam __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmSymbolParam___eq___const(OrgContext* org_context, haxorg_ImmSymbolParam __this, haxorg_ImmSymbolParam other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmSymbolParam(OrgContext* org_context, haxorg_ImmSymbolParam* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmSymbol(OrgContext* org_context, haxorg_ImmSymbol* obj);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmErrorSkipGroup_get_skipped(OrgContext* org_context, haxorg_ImmErrorSkipGroup __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmErrorSkipGroup___eq___const(OrgContext* org_context, haxorg_ImmErrorSkipGroup __this, haxorg_ImmErrorSkipGroup other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmErrorSkipGroup(OrgContext* org_context, haxorg_ImmErrorSkipGroup* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmMarkup___eq___const(OrgContext* org_context, haxorg_ImmMarkup __this, haxorg_ImmMarkup other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmMarkup(OrgContext* org_context, haxorg_ImmMarkup* obj);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmRadioTarget_get_words(OrgContext* org_context, haxorg_ImmRadioTarget __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmRadioTarget___eq___const(OrgContext* org_context, haxorg_ImmRadioTarget __this, haxorg_ImmRadioTarget other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmRadioTarget(OrgContext* org_context, haxorg_ImmRadioTarget* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmLatex___eq___const(OrgContext* org_context, haxorg_ImmLatex __this, haxorg_ImmLatex other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmLatex(OrgContext* org_context, haxorg_ImmLatex* obj);
HAXORG_C_API_LINKAGE haxorg_SubtreeLogHead haxorg_ImmSubtreeLog_get_head(OrgContext* org_context, haxorg_ImmSubtreeLog __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmSubtreeLog_get_desc(OrgContext* org_context, haxorg_ImmSubtreeLog __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmSubtreeLog___eq___const(OrgContext* org_context, haxorg_ImmSubtreeLog __this, haxorg_ImmSubtreeLog other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmSubtreeLog(OrgContext* org_context, haxorg_ImmSubtreeLog* obj);
HAXORG_C_API_LINKAGE int haxorg_ImmSubtree_get_level(OrgContext* org_context, haxorg_ImmSubtree __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmSubtree_get_treeId(OrgContext* org_context, haxorg_ImmSubtree __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmSubtree_get_todo(OrgContext* org_context, haxorg_ImmSubtree __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmSubtree_get_completion(OrgContext* org_context, haxorg_ImmSubtree __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmSubtree_get_description(OrgContext* org_context, haxorg_ImmSubtree __this);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmSubtree_get_tags(OrgContext* org_context, haxorg_ImmSubtree __this);
HAXORG_C_API_LINKAGE haxorg_ImmId haxorg_ImmSubtree_get_title(OrgContext* org_context, haxorg_ImmSubtree __this);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmSubtree_get_logbook(OrgContext* org_context, haxorg_ImmSubtree __this);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmSubtree_get_properties(OrgContext* org_context, haxorg_ImmSubtree __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmSubtree_get_closed(OrgContext* org_context, haxorg_ImmSubtree __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmSubtree_get_deadline(OrgContext* org_context, haxorg_ImmSubtree __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmSubtree_get_scheduled(OrgContext* org_context, haxorg_ImmSubtree __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmSubtree_get_isComment(OrgContext* org_context, haxorg_ImmSubtree __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmSubtree_get_isArchived(OrgContext* org_context, haxorg_ImmSubtree __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmSubtree_get_priority(OrgContext* org_context, haxorg_ImmSubtree __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmSubtree___eq___const(OrgContext* org_context, haxorg_ImmSubtree __this, haxorg_ImmSubtree other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmSubtree(OrgContext* org_context, haxorg_ImmSubtree* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmColonExample___eq___const(OrgContext* org_context, haxorg_ImmColonExample __this, haxorg_ImmColonExample other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmColonExample(OrgContext* org_context, haxorg_ImmColonExample* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmCall_get_name(OrgContext* org_context, haxorg_ImmCall __this);
HAXORG_C_API_LINKAGE haxorg_AttrGroup haxorg_ImmCall_get_attrs(OrgContext* org_context, haxorg_ImmCall __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCall_get_isCommand(OrgContext* org_context, haxorg_ImmCall __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCall___eq___const(OrgContext* org_context, haxorg_ImmCall __this, haxorg_ImmCall other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCall(OrgContext* org_context, haxorg_ImmCall* obj);
HAXORG_C_API_LINKAGE haxorg_CheckboxState haxorg_ImmListItem_get_checkbox(OrgContext* org_context, haxorg_ImmListItem __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmListItem_get_header(OrgContext* org_context, haxorg_ImmListItem __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmListItem_get_bullet(OrgContext* org_context, haxorg_ImmListItem __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmListItem___eq___const(OrgContext* org_context, haxorg_ImmListItem __this, haxorg_ImmListItem other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmListItem(OrgContext* org_context, haxorg_ImmListItem* obj);
HAXORG_C_API_LINKAGE haxorg_InitialSubtreeVisibility haxorg_ImmDocumentOptions_get_initialVisibility(OrgContext* org_context, haxorg_ImmDocumentOptions __this);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmDocumentOptions_get_properties(OrgContext* org_context, haxorg_ImmDocumentOptions __this);
HAXORG_C_API_LINKAGE haxorg_DocumentExportConfig haxorg_ImmDocumentOptions_get_exportConfig(OrgContext* org_context, haxorg_ImmDocumentOptions __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmDocumentOptions_get_fixedWidthSections(OrgContext* org_context, haxorg_ImmDocumentOptions __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmDocumentOptions_get_startupIndented(OrgContext* org_context, haxorg_ImmDocumentOptions __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmDocumentOptions_get_category(OrgContext* org_context, haxorg_ImmDocumentOptions __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmDocumentOptions_get_setupfile(OrgContext* org_context, haxorg_ImmDocumentOptions __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmDocumentOptions_get_maxSubtreeLevelExport(OrgContext* org_context, haxorg_ImmDocumentOptions __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmDocumentOptions_get_columns(OrgContext* org_context, haxorg_ImmDocumentOptions __this);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmDocumentOptions_get_todoKeywords(OrgContext* org_context, haxorg_ImmDocumentOptions __this);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmDocumentOptions_get_doneKeywords(OrgContext* org_context, haxorg_ImmDocumentOptions __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmDocumentOptions___eq___const(OrgContext* org_context, haxorg_ImmDocumentOptions __this, haxorg_ImmDocumentOptions other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmDocumentOptions(OrgContext* org_context, haxorg_ImmDocumentOptions* obj);
HAXORG_C_API_LINKAGE int haxorg_ImmDocumentFragment_get_baseLine(OrgContext* org_context, haxorg_ImmDocumentFragment __this);
HAXORG_C_API_LINKAGE int haxorg_ImmDocumentFragment_get_baseCol(OrgContext* org_context, haxorg_ImmDocumentFragment __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmDocumentFragment___eq___const(OrgContext* org_context, haxorg_ImmDocumentFragment __this, haxorg_ImmDocumentFragment other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmDocumentFragment(OrgContext* org_context, haxorg_ImmDocumentFragment* obj);
HAXORG_C_API_LINKAGE haxorg_ImmCriticMarkupKind haxorg_ImmCriticMarkup_get_kind(OrgContext* org_context, haxorg_ImmCriticMarkup __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCriticMarkup___eq___const(OrgContext* org_context, haxorg_ImmCriticMarkup __this, haxorg_ImmCriticMarkup other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCriticMarkup(OrgContext* org_context, haxorg_ImmCriticMarkup* obj);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmDocument_get_title(OrgContext* org_context, haxorg_ImmDocument __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmDocument_get_author(OrgContext* org_context, haxorg_ImmDocument __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmDocument_get_creator(OrgContext* org_context, haxorg_ImmDocument __this);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmDocument_get_filetags(OrgContext* org_context, haxorg_ImmDocument __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmDocument_get_email(OrgContext* org_context, haxorg_ImmDocument __this);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmDocument_get_language(OrgContext* org_context, haxorg_ImmDocument __this);
HAXORG_C_API_LINKAGE haxorg_ImmId haxorg_ImmDocument_get_options(OrgContext* org_context, haxorg_ImmDocument __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmDocument_get_exportFileName(OrgContext* org_context, haxorg_ImmDocument __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmDocument___eq___const(OrgContext* org_context, haxorg_ImmDocument __this, haxorg_ImmDocument other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmDocument(OrgContext* org_context, haxorg_ImmDocument* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmFileTarget_get_path(OrgContext* org_context, haxorg_ImmFileTarget __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmFileTarget_get_line(OrgContext* org_context, haxorg_ImmFileTarget __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmFileTarget_get_searchTarget(OrgContext* org_context, haxorg_ImmFileTarget __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmFileTarget_get_restrictToHeadlines(OrgContext* org_context, haxorg_ImmFileTarget __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmFileTarget_get_targetId(OrgContext* org_context, haxorg_ImmFileTarget __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmFileTarget_get_regexp(OrgContext* org_context, haxorg_ImmFileTarget __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmFileTarget___eq___const(OrgContext* org_context, haxorg_ImmFileTarget __this, haxorg_ImmFileTarget other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmFileTarget(OrgContext* org_context, haxorg_ImmFileTarget* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmTextSeparator___eq___const(OrgContext* org_context, haxorg_ImmTextSeparator __this, haxorg_ImmTextSeparator other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmTextSeparator(OrgContext* org_context, haxorg_ImmTextSeparator* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmDocumentGroup___eq___const(OrgContext* org_context, haxorg_ImmDocumentGroup __this, haxorg_ImmDocumentGroup other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmDocumentGroup(OrgContext* org_context, haxorg_ImmDocumentGroup* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmFile_get_relPath(OrgContext* org_context, haxorg_ImmFile __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmFile_get_absPath(OrgContext* org_context, haxorg_ImmFile __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmFile___eq___const(OrgContext* org_context, haxorg_ImmFile __this, haxorg_ImmFile other);
HAXORG_C_API_LINKAGE bool haxorg_ImmFile_isDocument_const(OrgContext* org_context, haxorg_ImmFile __this);
HAXORG_C_API_LINKAGE haxorg_ImmFileDocument haxorg_ImmFile_getDocumentConst_const(OrgContext* org_context, haxorg_ImmFile __this);
HAXORG_C_API_LINKAGE haxorg_ImmFileDocument haxorg_ImmFile_getDocumentMut(OrgContext* org_context, haxorg_ImmFile __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmFile_isAttachment_const(OrgContext* org_context, haxorg_ImmFile __this);
HAXORG_C_API_LINKAGE haxorg_ImmFileAttachment haxorg_ImmFile_getAttachmentConst_const(OrgContext* org_context, haxorg_ImmFile __this);
HAXORG_C_API_LINKAGE haxorg_ImmFileAttachment haxorg_ImmFile_getAttachmentMut(OrgContext* org_context, haxorg_ImmFile __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmFile_isSource_const(OrgContext* org_context, haxorg_ImmFile __this);
HAXORG_C_API_LINKAGE haxorg_ImmFileSource haxorg_ImmFile_getSourceConst_const(OrgContext* org_context, haxorg_ImmFile __this);
HAXORG_C_API_LINKAGE haxorg_ImmFileSource haxorg_ImmFile_getSourceMut(OrgContext* org_context, haxorg_ImmFile __this);
HAXORG_C_API_LINKAGE haxorg_ImmFileKind haxorg_ImmFile_getFileKind_const(OrgContext* org_context, haxorg_ImmFile __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmFileDocument___eq___const(OrgContext* org_context, haxorg_ImmFileDocument __this, haxorg_ImmFileDocument other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmFileDocument(OrgContext* org_context, haxorg_ImmFileDocument* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmFileAttachment___eq___const(OrgContext* org_context, haxorg_ImmFileAttachment __this, haxorg_ImmFileAttachment other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmFileAttachment(OrgContext* org_context, haxorg_ImmFileAttachment* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmFileSource___eq___const(OrgContext* org_context, haxorg_ImmFileSource __this, haxorg_ImmFileSource other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmFileSource(OrgContext* org_context, haxorg_ImmFileSource* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmFile(OrgContext* org_context, haxorg_ImmFile* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmDirectory_get_relPath(OrgContext* org_context, haxorg_ImmDirectory __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmDirectory_get_absPath(OrgContext* org_context, haxorg_ImmDirectory __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmDirectory___eq___const(OrgContext* org_context, haxorg_ImmDirectory __this, haxorg_ImmDirectory other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmDirectory(OrgContext* org_context, haxorg_ImmDirectory* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmSymlink_get_isDirectory(OrgContext* org_context, haxorg_ImmSymlink __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmSymlink_get_absPath(OrgContext* org_context, haxorg_ImmSymlink __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmSymlink___eq___const(OrgContext* org_context, haxorg_ImmSymlink __this, haxorg_ImmSymlink other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmSymlink(OrgContext* org_context, haxorg_ImmSymlink* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmCmdInclude_get_path(OrgContext* org_context, haxorg_ImmCmdInclude __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmCmdInclude_get_firstLine(OrgContext* org_context, haxorg_ImmCmdInclude __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmCmdInclude_get_lastLine(OrgContext* org_context, haxorg_ImmCmdInclude __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCmdInclude___eq___const(OrgContext* org_context, haxorg_ImmCmdInclude __this, haxorg_ImmCmdInclude other);
HAXORG_C_API_LINKAGE bool haxorg_ImmCmdInclude_isExample_const(OrgContext* org_context, haxorg_ImmCmdInclude __this);
HAXORG_C_API_LINKAGE haxorg_ImmCmdIncludeExample haxorg_ImmCmdInclude_getExampleConst_const(OrgContext* org_context, haxorg_ImmCmdInclude __this);
HAXORG_C_API_LINKAGE haxorg_ImmCmdIncludeExample haxorg_ImmCmdInclude_getExampleMut(OrgContext* org_context, haxorg_ImmCmdInclude __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCmdInclude_isExport_const(OrgContext* org_context, haxorg_ImmCmdInclude __this);
HAXORG_C_API_LINKAGE haxorg_ImmCmdIncludeExport haxorg_ImmCmdInclude_getExportConst_const(OrgContext* org_context, haxorg_ImmCmdInclude __this);
HAXORG_C_API_LINKAGE haxorg_ImmCmdIncludeExport haxorg_ImmCmdInclude_getExportMut(OrgContext* org_context, haxorg_ImmCmdInclude __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCmdInclude_isCustom_const(OrgContext* org_context, haxorg_ImmCmdInclude __this);
HAXORG_C_API_LINKAGE haxorg_ImmCmdIncludeCustom haxorg_ImmCmdInclude_getCustomConst_const(OrgContext* org_context, haxorg_ImmCmdInclude __this);
HAXORG_C_API_LINKAGE haxorg_ImmCmdIncludeCustom haxorg_ImmCmdInclude_getCustomMut(OrgContext* org_context, haxorg_ImmCmdInclude __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCmdInclude_isSrc_const(OrgContext* org_context, haxorg_ImmCmdInclude __this);
HAXORG_C_API_LINKAGE haxorg_ImmCmdIncludeSrc haxorg_ImmCmdInclude_getSrcConst_const(OrgContext* org_context, haxorg_ImmCmdInclude __this);
HAXORG_C_API_LINKAGE haxorg_ImmCmdIncludeSrc haxorg_ImmCmdInclude_getSrcMut(OrgContext* org_context, haxorg_ImmCmdInclude __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCmdInclude_isOrgDocument_const(OrgContext* org_context, haxorg_ImmCmdInclude __this);
HAXORG_C_API_LINKAGE haxorg_ImmCmdIncludeOrgDocument haxorg_ImmCmdInclude_getOrgDocumentConst_const(OrgContext* org_context, haxorg_ImmCmdInclude __this);
HAXORG_C_API_LINKAGE haxorg_ImmCmdIncludeOrgDocument haxorg_ImmCmdInclude_getOrgDocumentMut(OrgContext* org_context, haxorg_ImmCmdInclude __this);
HAXORG_C_API_LINKAGE haxorg_ImmCmdIncludeKind haxorg_ImmCmdInclude_getIncludeKind_const(OrgContext* org_context, haxorg_ImmCmdInclude __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCmdIncludeIncludeBase___eq___const(OrgContext* org_context, haxorg_ImmCmdIncludeIncludeBase __this, haxorg_ImmCmdIncludeIncludeBase other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdIncludeIncludeBase(OrgContext* org_context, haxorg_ImmCmdIncludeIncludeBase* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmCmdIncludeExample___eq___const(OrgContext* org_context, haxorg_ImmCmdIncludeExample __this, haxorg_ImmCmdIncludeExample other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdIncludeExample(OrgContext* org_context, haxorg_ImmCmdIncludeExample* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmCmdIncludeExport_get_language(OrgContext* org_context, haxorg_ImmCmdIncludeExport __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCmdIncludeExport___eq___const(OrgContext* org_context, haxorg_ImmCmdIncludeExport __this, haxorg_ImmCmdIncludeExport other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdIncludeExport(OrgContext* org_context, haxorg_ImmCmdIncludeExport* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmCmdIncludeCustom_get_blockName(OrgContext* org_context, haxorg_ImmCmdIncludeCustom __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCmdIncludeCustom___eq___const(OrgContext* org_context, haxorg_ImmCmdIncludeCustom __this, haxorg_ImmCmdIncludeCustom other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdIncludeCustom(OrgContext* org_context, haxorg_ImmCmdIncludeCustom* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmCmdIncludeSrc_get_language(OrgContext* org_context, haxorg_ImmCmdIncludeSrc __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCmdIncludeSrc___eq___const(OrgContext* org_context, haxorg_ImmCmdIncludeSrc __this, haxorg_ImmCmdIncludeSrc other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdIncludeSrc(OrgContext* org_context, haxorg_ImmCmdIncludeSrc* obj);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmCmdIncludeOrgDocument_get_onlyContent(OrgContext* org_context, haxorg_ImmCmdIncludeOrgDocument __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmCmdIncludeOrgDocument_get_subtreePath(OrgContext* org_context, haxorg_ImmCmdIncludeOrgDocument __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmCmdIncludeOrgDocument_get_minLevel(OrgContext* org_context, haxorg_ImmCmdIncludeOrgDocument __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmCmdIncludeOrgDocument_get_customIdTarget(OrgContext* org_context, haxorg_ImmCmdIncludeOrgDocument __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCmdIncludeOrgDocument___eq___const(OrgContext* org_context, haxorg_ImmCmdIncludeOrgDocument __this, haxorg_ImmCmdIncludeOrgDocument other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdIncludeOrgDocument(OrgContext* org_context, haxorg_ImmCmdIncludeOrgDocument* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdInclude(OrgContext* org_context, haxorg_ImmCmdInclude* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterOrgAPI(OrgContext* org_context, haxorg_ImmAdapterOrgAPI* obj);
HAXORG_C_API_LINKAGE haxorg_AttrGroup haxorg_Cmd_get_attrs(OrgContext* org_context, haxorg_Cmd __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfAttrValue haxorg_Cmd_getAttrs_const(OrgContext* org_context, haxorg_Cmd __this, haxorg_HstdOpt key);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Cmd_getFirstAttr_const(OrgContext* org_context, haxorg_Cmd __this, haxorg_HstdStr kind);
HAXORG_C_API_LINKAGE void haxorg_destroy_Cmd(OrgContext* org_context, haxorg_Cmd* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_CmdCustomRaw_get_name(OrgContext* org_context, haxorg_CmdCustomRaw __this);
HAXORG_C_API_LINKAGE bool haxorg_CmdCustomRaw_get_isAttached(OrgContext* org_context, haxorg_CmdCustomRaw __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_CmdCustomRaw_get_text(OrgContext* org_context, haxorg_CmdCustomRaw __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdCustomRaw(OrgContext* org_context, haxorg_CmdCustomRaw* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_CmdCustomText_get_name(OrgContext* org_context, haxorg_CmdCustomText __this);
HAXORG_C_API_LINKAGE bool haxorg_CmdCustomText_get_isAttached(OrgContext* org_context, haxorg_CmdCustomText __this);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_CmdCustomText_get_text(OrgContext* org_context, haxorg_CmdCustomText __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdCustomText(OrgContext* org_context, haxorg_CmdCustomText* obj);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Link_get_description(OrgContext* org_context, haxorg_Link __this);
HAXORG_C_API_LINKAGE haxorg_LinkTarget haxorg_Link_get_target(OrgContext* org_context, haxorg_Link __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_Link(OrgContext* org_context, haxorg_Link* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_BlockComment(OrgContext* org_context, haxorg_BlockComment* obj);
HAXORG_C_API_LINKAGE bool haxorg_Paragraph_isFootnoteDefinition_const(OrgContext* org_context, haxorg_Paragraph __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_Paragraph_getFootnoteName_const(OrgContext* org_context, haxorg_Paragraph __this);
HAXORG_C_API_LINKAGE bool haxorg_Paragraph_hasAdmonition_const(OrgContext* org_context, haxorg_Paragraph __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfStr haxorg_Paragraph_getAdmonitions_const(OrgContext* org_context, haxorg_Paragraph __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfSemIdOfBigIdent haxorg_Paragraph_getAdmonitionNodes_const(OrgContext* org_context, haxorg_Paragraph __this);
HAXORG_C_API_LINKAGE bool haxorg_Paragraph_hasTimestamp_const(OrgContext* org_context, haxorg_Paragraph __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfUserTime haxorg_Paragraph_getTimestamps_const(OrgContext* org_context, haxorg_Paragraph __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfSemIdOfTime haxorg_Paragraph_getTimestampNodes_const(OrgContext* org_context, haxorg_Paragraph __this);
HAXORG_C_API_LINKAGE bool haxorg_Paragraph_hasLeadHashtags_const(OrgContext* org_context, haxorg_Paragraph __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfSemIdOfHashTag haxorg_Paragraph_getLeadHashtags_const(OrgContext* org_context, haxorg_Paragraph __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfSemIdOfOrg haxorg_Paragraph_getBody_const(OrgContext* org_context, haxorg_Paragraph __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_Paragraph(OrgContext* org_context, haxorg_Paragraph* obj);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfAttrValue haxorg_List_getListAttrs_const(OrgContext* org_context, haxorg_List __this, haxorg_HstdStr key);
HAXORG_C_API_LINKAGE haxorg_ListFormattingMode haxorg_List_getListFormattingMode_const(OrgContext* org_context, haxorg_List __this);
HAXORG_C_API_LINKAGE bool haxorg_List_isDescriptionList_const(OrgContext* org_context, haxorg_List __this);
HAXORG_C_API_LINKAGE bool haxorg_List_isNumberedList_const(OrgContext* org_context, haxorg_List __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_List(OrgContext* org_context, haxorg_List* obj);
HAXORG_C_API_LINKAGE haxorg_HashTagText haxorg_HashTag_get_text(OrgContext* org_context, haxorg_HashTag __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_HashTag(OrgContext* org_context, haxorg_HashTag* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_InlineFootnote_get_tag(OrgContext* org_context, haxorg_InlineFootnote __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_InlineFootnote_get_definition(OrgContext* org_context, haxorg_InlineFootnote __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_InlineFootnote(OrgContext* org_context, haxorg_InlineFootnote* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_InlineExport_get_exporter(OrgContext* org_context, haxorg_InlineExport __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_InlineExport_get_content(OrgContext* org_context, haxorg_InlineExport __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_InlineExport(OrgContext* org_context, haxorg_InlineExport* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Escaped(OrgContext* org_context, haxorg_Escaped* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Newline(OrgContext* org_context, haxorg_Newline* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Space(OrgContext* org_context, haxorg_Space* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Word(OrgContext* org_context, haxorg_Word* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_AtMention(OrgContext* org_context, haxorg_AtMention* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_RawText(OrgContext* org_context, haxorg_RawText* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Punctuation(OrgContext* org_context, haxorg_Punctuation* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Placeholder(OrgContext* org_context, haxorg_Placeholder* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_BigIdent(OrgContext* org_context, haxorg_BigIdent* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_TextTarget(OrgContext* org_context, haxorg_TextTarget* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ErrorSkipToken(OrgContext* org_context, haxorg_ErrorSkipToken* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Bold(OrgContext* org_context, haxorg_Bold* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Underline(OrgContext* org_context, haxorg_Underline* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Monospace(OrgContext* org_context, haxorg_Monospace* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_MarkQuote(OrgContext* org_context, haxorg_MarkQuote* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Verbatim(OrgContext* org_context, haxorg_Verbatim* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Italic(OrgContext* org_context, haxorg_Italic* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Strike(OrgContext* org_context, haxorg_Strike* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Par(OrgContext* org_context, haxorg_Par* obj);
HAXORG_C_API_LINKAGE haxorg_AttrGroup haxorg_ImmCmd_get_attrs(OrgContext* org_context, haxorg_ImmCmd __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCmd___eq___const(OrgContext* org_context, haxorg_ImmCmd __this, haxorg_ImmCmd other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmd(OrgContext* org_context, haxorg_ImmCmd* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmCmdCustomRaw_get_name(OrgContext* org_context, haxorg_ImmCmdCustomRaw __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCmdCustomRaw_get_isAttached(OrgContext* org_context, haxorg_ImmCmdCustomRaw __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmCmdCustomRaw_get_text(OrgContext* org_context, haxorg_ImmCmdCustomRaw __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCmdCustomRaw___eq___const(OrgContext* org_context, haxorg_ImmCmdCustomRaw __this, haxorg_ImmCmdCustomRaw other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdCustomRaw(OrgContext* org_context, haxorg_ImmCmdCustomRaw* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmCmdCustomText_get_name(OrgContext* org_context, haxorg_ImmCmdCustomText __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCmdCustomText_get_isAttached(OrgContext* org_context, haxorg_ImmCmdCustomText __this);
HAXORG_C_API_LINKAGE haxorg_ImmId haxorg_ImmCmdCustomText_get_text(OrgContext* org_context, haxorg_ImmCmdCustomText __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCmdCustomText___eq___const(OrgContext* org_context, haxorg_ImmCmdCustomText __this, haxorg_ImmCmdCustomText other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdCustomText(OrgContext* org_context, haxorg_ImmCmdCustomText* obj);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmLink_get_description(OrgContext* org_context, haxorg_ImmLink __this);
HAXORG_C_API_LINKAGE haxorg_LinkTarget haxorg_ImmLink_get_target(OrgContext* org_context, haxorg_ImmLink __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmLink___eq___const(OrgContext* org_context, haxorg_ImmLink __this, haxorg_ImmLink other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmLink(OrgContext* org_context, haxorg_ImmLink* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmBlockComment___eq___const(OrgContext* org_context, haxorg_ImmBlockComment __this, haxorg_ImmBlockComment other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockComment(OrgContext* org_context, haxorg_ImmBlockComment* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmParagraph___eq___const(OrgContext* org_context, haxorg_ImmParagraph __this, haxorg_ImmParagraph other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmParagraph(OrgContext* org_context, haxorg_ImmParagraph* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmList___eq___const(OrgContext* org_context, haxorg_ImmList __this, haxorg_ImmList other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmList(OrgContext* org_context, haxorg_ImmList* obj);
HAXORG_C_API_LINKAGE haxorg_HashTagText haxorg_ImmHashTag_get_text(OrgContext* org_context, haxorg_ImmHashTag __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmHashTag___eq___const(OrgContext* org_context, haxorg_ImmHashTag __this, haxorg_ImmHashTag other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmHashTag(OrgContext* org_context, haxorg_ImmHashTag* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmInlineFootnote_get_tag(OrgContext* org_context, haxorg_ImmInlineFootnote __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmInlineFootnote_get_definition(OrgContext* org_context, haxorg_ImmInlineFootnote __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmInlineFootnote___eq___const(OrgContext* org_context, haxorg_ImmInlineFootnote __this, haxorg_ImmInlineFootnote other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmInlineFootnote(OrgContext* org_context, haxorg_ImmInlineFootnote* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmInlineExport_get_exporter(OrgContext* org_context, haxorg_ImmInlineExport __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmInlineExport_get_content(OrgContext* org_context, haxorg_ImmInlineExport __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmInlineExport___eq___const(OrgContext* org_context, haxorg_ImmInlineExport __this, haxorg_ImmInlineExport other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmInlineExport(OrgContext* org_context, haxorg_ImmInlineExport* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmEscaped___eq___const(OrgContext* org_context, haxorg_ImmEscaped __this, haxorg_ImmEscaped other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmEscaped(OrgContext* org_context, haxorg_ImmEscaped* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmNewline___eq___const(OrgContext* org_context, haxorg_ImmNewline __this, haxorg_ImmNewline other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmNewline(OrgContext* org_context, haxorg_ImmNewline* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmSpace___eq___const(OrgContext* org_context, haxorg_ImmSpace __this, haxorg_ImmSpace other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmSpace(OrgContext* org_context, haxorg_ImmSpace* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmWord___eq___const(OrgContext* org_context, haxorg_ImmWord __this, haxorg_ImmWord other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmWord(OrgContext* org_context, haxorg_ImmWord* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmAtMention___eq___const(OrgContext* org_context, haxorg_ImmAtMention __this, haxorg_ImmAtMention other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAtMention(OrgContext* org_context, haxorg_ImmAtMention* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmRawText___eq___const(OrgContext* org_context, haxorg_ImmRawText __this, haxorg_ImmRawText other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmRawText(OrgContext* org_context, haxorg_ImmRawText* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmPunctuation___eq___const(OrgContext* org_context, haxorg_ImmPunctuation __this, haxorg_ImmPunctuation other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmPunctuation(OrgContext* org_context, haxorg_ImmPunctuation* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmPlaceholder___eq___const(OrgContext* org_context, haxorg_ImmPlaceholder __this, haxorg_ImmPlaceholder other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmPlaceholder(OrgContext* org_context, haxorg_ImmPlaceholder* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmBigIdent___eq___const(OrgContext* org_context, haxorg_ImmBigIdent __this, haxorg_ImmBigIdent other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBigIdent(OrgContext* org_context, haxorg_ImmBigIdent* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmTextTarget___eq___const(OrgContext* org_context, haxorg_ImmTextTarget __this, haxorg_ImmTextTarget other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmTextTarget(OrgContext* org_context, haxorg_ImmTextTarget* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmErrorSkipToken___eq___const(OrgContext* org_context, haxorg_ImmErrorSkipToken __this, haxorg_ImmErrorSkipToken other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmErrorSkipToken(OrgContext* org_context, haxorg_ImmErrorSkipToken* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmBold___eq___const(OrgContext* org_context, haxorg_ImmBold __this, haxorg_ImmBold other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBold(OrgContext* org_context, haxorg_ImmBold* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmUnderline___eq___const(OrgContext* org_context, haxorg_ImmUnderline __this, haxorg_ImmUnderline other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmUnderline(OrgContext* org_context, haxorg_ImmUnderline* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmMonospace___eq___const(OrgContext* org_context, haxorg_ImmMonospace __this, haxorg_ImmMonospace other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmMonospace(OrgContext* org_context, haxorg_ImmMonospace* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmMarkQuote___eq___const(OrgContext* org_context, haxorg_ImmMarkQuote __this, haxorg_ImmMarkQuote other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmMarkQuote(OrgContext* org_context, haxorg_ImmMarkQuote* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmVerbatim___eq___const(OrgContext* org_context, haxorg_ImmVerbatim __this, haxorg_ImmVerbatim other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmVerbatim(OrgContext* org_context, haxorg_ImmVerbatim* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmItalic___eq___const(OrgContext* org_context, haxorg_ImmItalic __this, haxorg_ImmItalic other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmItalic(OrgContext* org_context, haxorg_ImmItalic* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmStrike___eq___const(OrgContext* org_context, haxorg_ImmStrike __this, haxorg_ImmStrike other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmStrike(OrgContext* org_context, haxorg_ImmStrike* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmPar___eq___const(OrgContext* org_context, haxorg_ImmPar __this, haxorg_ImmPar other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmPar(OrgContext* org_context, haxorg_ImmPar* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterStmtAPI(OrgContext* org_context, haxorg_ImmAdapterStmtAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterSubtreeAPI(OrgContext* org_context, haxorg_ImmAdapterSubtreeAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterNoNodeAPI(OrgContext* org_context, haxorg_ImmAdapterNoNodeAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterAttrAPI(OrgContext* org_context, haxorg_ImmAdapterAttrAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterAttrListAPI(OrgContext* org_context, haxorg_ImmAdapterAttrListAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterAttrsAPI(OrgContext* org_context, haxorg_ImmAdapterAttrsAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterErrorItemAPI(OrgContext* org_context, haxorg_ImmAdapterErrorItemAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterErrorGroupAPI(OrgContext* org_context, haxorg_ImmAdapterErrorGroupAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterErrorSkipGroupAPI(OrgContext* org_context, haxorg_ImmAdapterErrorSkipGroupAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterErrorSkipTokenAPI(OrgContext* org_context, haxorg_ImmAdapterErrorSkipTokenAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterStmtListAPI(OrgContext* org_context, haxorg_ImmAdapterStmtListAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterEmptyAPI(OrgContext* org_context, haxorg_ImmAdapterEmptyAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterInlineAPI(OrgContext* org_context, haxorg_ImmAdapterInlineAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterTimeAPI(OrgContext* org_context, haxorg_ImmAdapterTimeAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterTimeRangeAPI(OrgContext* org_context, haxorg_ImmAdapterTimeRangeAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterMacroAPI(OrgContext* org_context, haxorg_ImmAdapterMacroAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterSymbolAPI(OrgContext* org_context, haxorg_ImmAdapterSymbolAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterLeafAPI(OrgContext* org_context, haxorg_ImmAdapterLeafAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterMarkupAPI(OrgContext* org_context, haxorg_ImmAdapterMarkupAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterLatexAPI(OrgContext* org_context, haxorg_ImmAdapterLatexAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterSubtreeLogAPI(OrgContext* org_context, haxorg_ImmAdapterSubtreeLogAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterColonExampleAPI(OrgContext* org_context, haxorg_ImmAdapterColonExampleAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCallAPI(OrgContext* org_context, haxorg_ImmAdapterCallAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterFileAPI(OrgContext* org_context, haxorg_ImmAdapterFileAPI* obj);
HAXORG_C_API_LINKAGE haxorg_StdOptional haxorg_ImmAdapterDirectoryAPI_getFsSubnode_const(OrgContext* org_context, haxorg_ImmAdapterDirectoryAPI __this, haxorg_HstdStr name, bool withPath);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterDirectoryAPI(OrgContext* org_context, haxorg_ImmAdapterDirectoryAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterSymlinkAPI(OrgContext* org_context, haxorg_ImmAdapterSymlinkAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterDocumentFragmentAPI(OrgContext* org_context, haxorg_ImmAdapterDocumentFragmentAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCriticMarkupAPI(OrgContext* org_context, haxorg_ImmAdapterCriticMarkupAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterListItemAPI(OrgContext* org_context, haxorg_ImmAdapterListItemAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterDocumentOptionsAPI(OrgContext* org_context, haxorg_ImmAdapterDocumentOptionsAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterDocumentAPI(OrgContext* org_context, haxorg_ImmAdapterDocumentAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterFileTargetAPI(OrgContext* org_context, haxorg_ImmAdapterFileTargetAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterTextSeparatorAPI(OrgContext* org_context, haxorg_ImmAdapterTextSeparatorAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdIncludeAPI(OrgContext* org_context, haxorg_ImmAdapterCmdIncludeAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterDocumentGroupAPI(OrgContext* org_context, haxorg_ImmAdapterDocumentGroupAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Block(OrgContext* org_context, haxorg_Block* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_LineCommand(OrgContext* org_context, haxorg_LineCommand* obj);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_CmdCreator_get_text(OrgContext* org_context, haxorg_CmdCreator __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdCreator(OrgContext* org_context, haxorg_CmdCreator* obj);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_CmdAuthor_get_text(OrgContext* org_context, haxorg_CmdAuthor __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdAuthor(OrgContext* org_context, haxorg_CmdAuthor* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_CmdEmail_get_text(OrgContext* org_context, haxorg_CmdEmail __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdEmail(OrgContext* org_context, haxorg_CmdEmail* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_CmdLanguage_get_text(OrgContext* org_context, haxorg_CmdLanguage __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdLanguage(OrgContext* org_context, haxorg_CmdLanguage* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_CmdCustomArgs_get_name(OrgContext* org_context, haxorg_CmdCustomArgs __this);
HAXORG_C_API_LINKAGE bool haxorg_CmdCustomArgs_get_isAttached(OrgContext* org_context, haxorg_CmdCustomArgs __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdCustomArgs(OrgContext* org_context, haxorg_CmdCustomArgs* obj);
HAXORG_C_API_LINKAGE haxorg_Tblfm haxorg_CmdTblfm_get_expr(OrgContext* org_context, haxorg_CmdTblfm __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdTblfm(OrgContext* org_context, haxorg_CmdTblfm* obj);
HAXORG_C_API_LINKAGE bool haxorg_Cell_get_isBlock(OrgContext* org_context, haxorg_Cell __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_Cell(OrgContext* org_context, haxorg_Cell* obj);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfSemIdOfCell haxorg_Row_get_cells(OrgContext* org_context, haxorg_Row __this);
HAXORG_C_API_LINKAGE bool haxorg_Row_get_isBlock(OrgContext* org_context, haxorg_Row __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_Row(OrgContext* org_context, haxorg_Row* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmBlock___eq___const(OrgContext* org_context, haxorg_ImmBlock __this, haxorg_ImmBlock other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlock(OrgContext* org_context, haxorg_ImmBlock* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmLineCommand___eq___const(OrgContext* org_context, haxorg_ImmLineCommand __this, haxorg_ImmLineCommand other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmLineCommand(OrgContext* org_context, haxorg_ImmLineCommand* obj);
HAXORG_C_API_LINKAGE haxorg_ImmId haxorg_ImmCmdCreator_get_text(OrgContext* org_context, haxorg_ImmCmdCreator __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCmdCreator___eq___const(OrgContext* org_context, haxorg_ImmCmdCreator __this, haxorg_ImmCmdCreator other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdCreator(OrgContext* org_context, haxorg_ImmCmdCreator* obj);
HAXORG_C_API_LINKAGE haxorg_ImmId haxorg_ImmCmdAuthor_get_text(OrgContext* org_context, haxorg_ImmCmdAuthor __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCmdAuthor___eq___const(OrgContext* org_context, haxorg_ImmCmdAuthor __this, haxorg_ImmCmdAuthor other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdAuthor(OrgContext* org_context, haxorg_ImmCmdAuthor* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmCmdEmail_get_text(OrgContext* org_context, haxorg_ImmCmdEmail __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCmdEmail___eq___const(OrgContext* org_context, haxorg_ImmCmdEmail __this, haxorg_ImmCmdEmail other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdEmail(OrgContext* org_context, haxorg_ImmCmdEmail* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmCmdLanguage_get_text(OrgContext* org_context, haxorg_ImmCmdLanguage __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCmdLanguage___eq___const(OrgContext* org_context, haxorg_ImmCmdLanguage __this, haxorg_ImmCmdLanguage other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdLanguage(OrgContext* org_context, haxorg_ImmCmdLanguage* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmCmdCustomArgs_get_name(OrgContext* org_context, haxorg_ImmCmdCustomArgs __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCmdCustomArgs_get_isAttached(OrgContext* org_context, haxorg_ImmCmdCustomArgs __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCmdCustomArgs___eq___const(OrgContext* org_context, haxorg_ImmCmdCustomArgs __this, haxorg_ImmCmdCustomArgs other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdCustomArgs(OrgContext* org_context, haxorg_ImmCmdCustomArgs* obj);
HAXORG_C_API_LINKAGE haxorg_Tblfm haxorg_ImmCmdTblfm_get_expr(OrgContext* org_context, haxorg_ImmCmdTblfm __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCmdTblfm___eq___const(OrgContext* org_context, haxorg_ImmCmdTblfm __this, haxorg_ImmCmdTblfm other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdTblfm(OrgContext* org_context, haxorg_ImmCmdTblfm* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmCell_get_isBlock(OrgContext* org_context, haxorg_ImmCell __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCell___eq___const(OrgContext* org_context, haxorg_ImmCell __this, haxorg_ImmCell other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCell(OrgContext* org_context, haxorg_ImmCell* obj);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmRow_get_cells(OrgContext* org_context, haxorg_ImmRow __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmRow_get_isBlock(OrgContext* org_context, haxorg_ImmRow __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmRow___eq___const(OrgContext* org_context, haxorg_ImmRow __this, haxorg_ImmRow other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmRow(OrgContext* org_context, haxorg_ImmRow* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdAPI(OrgContext* org_context, haxorg_ImmAdapterCmdAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdCustomRawAPI(OrgContext* org_context, haxorg_ImmAdapterCmdCustomRawAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdCustomTextAPI(OrgContext* org_context, haxorg_ImmAdapterCmdCustomTextAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterLinkAPI(OrgContext* org_context, haxorg_ImmAdapterLinkAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterBlockCommentAPI(OrgContext* org_context, haxorg_ImmAdapterBlockCommentAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterParagraphAPI(OrgContext* org_context, haxorg_ImmAdapterParagraphAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterListAPI(OrgContext* org_context, haxorg_ImmAdapterListAPI* obj);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmAdapterTOfImmStmt_getAttached_const(OrgContext* org_context, haxorg_ImmStmtAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmStmt_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmStmtAdapter(OrgContext* org_context, haxorg_ImmStmtAdapter* obj);
HAXORG_C_API_LINKAGE int haxorg_ImmAdapterTOfImmSubtree_getLevel_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmSubtree_getTreeId_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmSubtree_getTodo_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmSubtree_getCompletion_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmSubtree_getDescription_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter __this);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmAdapterTOfImmSubtree_getTags_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter __this);
HAXORG_C_API_LINKAGE haxorg_ImmAdapter haxorg_ImmAdapterTOfImmSubtree_getTitle_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter __this);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmAdapterTOfImmSubtree_getLogbook_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter __this);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmAdapterTOfImmSubtree_getProperties_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmSubtree_getClosed_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmSubtree_getDeadline_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmSubtree_getScheduled_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmAdapterTOfImmSubtree_getIsComment_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmAdapterTOfImmSubtree_getIsArchived_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmSubtree_getPriority_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmSubtree_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmSubtreeAdapter(OrgContext* org_context, haxorg_ImmSubtreeAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmNoNode_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmNoNodeAdapter(OrgContext* org_context, haxorg_ImmNoNodeAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_OrgDiagnostics haxorg_ImmAdapterTOfImmErrorItem_getDiag_const(OrgContext* org_context, haxorg_ImmErrorItemAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmErrorItem_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmErrorItemAdapter(OrgContext* org_context, haxorg_ImmErrorItemAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmAdapterTOfImmErrorGroup_getDiagnostics_const(OrgContext* org_context, haxorg_ImmErrorGroupAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmErrorGroup_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmErrorGroupAdapter(OrgContext* org_context, haxorg_ImmErrorGroupAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmAdapterTOfImmErrorSkipGroup_getSkipped_const(OrgContext* org_context, haxorg_ImmErrorSkipGroupAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmErrorSkipGroup_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmErrorSkipGroupAdapter(OrgContext* org_context, haxorg_ImmErrorSkipGroupAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmErrorSkipToken_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmErrorSkipTokenAdapter(OrgContext* org_context, haxorg_ImmErrorSkipTokenAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmStmtList_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmStmtListAdapter(OrgContext* org_context, haxorg_ImmStmtListAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmEmpty_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmEmptyAdapter(OrgContext* org_context, haxorg_ImmEmptyAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterHashTagAPI(OrgContext* org_context, haxorg_ImmAdapterHashTagAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterInlineFootnoteAPI(OrgContext* org_context, haxorg_ImmAdapterInlineFootnoteAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterSubtreeCompletionAPI(OrgContext* org_context, haxorg_ImmAdapterSubtreeCompletionAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmInline_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmInlineAdapter(OrgContext* org_context, haxorg_ImmInlineAdapter* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmAdapterTOfImmTime_getIsActive_const(OrgContext* org_context, haxorg_ImmTimeAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmTime_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmTimeAdapter(OrgContext* org_context, haxorg_ImmTimeAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_ImmAdapter haxorg_ImmAdapterTOfImmTimeRange_getFrom_const(OrgContext* org_context, haxorg_ImmTimeRangeAdapter __this);
HAXORG_C_API_LINKAGE haxorg_ImmAdapter haxorg_ImmAdapterTOfImmTimeRange_getTo_const(OrgContext* org_context, haxorg_ImmTimeRangeAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmTimeRange_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmTimeRangeAdapter(OrgContext* org_context, haxorg_ImmTimeRangeAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmAdapterTOfImmMacro_getName_const(OrgContext* org_context, haxorg_ImmMacroAdapter __this);
HAXORG_C_API_LINKAGE haxorg_AttrGroup haxorg_ImmAdapterTOfImmMacro_getAttrs_const(OrgContext* org_context, haxorg_ImmMacroAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmMacro_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmMacroAdapter(OrgContext* org_context, haxorg_ImmMacroAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmAdapterTOfImmSymbol_getName_const(OrgContext* org_context, haxorg_ImmSymbolAdapter __this);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmAdapterTOfImmSymbol_getParameters_const(OrgContext* org_context, haxorg_ImmSymbolAdapter __this);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmAdapterTOfImmSymbol_getPositional_const(OrgContext* org_context, haxorg_ImmSymbolAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmSymbol_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmSymbolAdapter(OrgContext* org_context, haxorg_ImmSymbolAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterEscapedAPI(OrgContext* org_context, haxorg_ImmAdapterEscapedAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterNewlineAPI(OrgContext* org_context, haxorg_ImmAdapterNewlineAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterSpaceAPI(OrgContext* org_context, haxorg_ImmAdapterSpaceAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterWordAPI(OrgContext* org_context, haxorg_ImmAdapterWordAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterAtMentionAPI(OrgContext* org_context, haxorg_ImmAdapterAtMentionAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterRawTextAPI(OrgContext* org_context, haxorg_ImmAdapterRawTextAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterPunctuationAPI(OrgContext* org_context, haxorg_ImmAdapterPunctuationAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterPlaceholderAPI(OrgContext* org_context, haxorg_ImmAdapterPlaceholderAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterBigIdentAPI(OrgContext* org_context, haxorg_ImmAdapterBigIdentAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterTextTargetAPI(OrgContext* org_context, haxorg_ImmAdapterTextTargetAPI* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmAdapterTOfImmLeaf_getText_const(OrgContext* org_context, haxorg_ImmLeafAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmLeaf_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmLeafAdapter(OrgContext* org_context, haxorg_ImmLeafAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterBoldAPI(OrgContext* org_context, haxorg_ImmAdapterBoldAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterUnderlineAPI(OrgContext* org_context, haxorg_ImmAdapterUnderlineAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterMonospaceAPI(OrgContext* org_context, haxorg_ImmAdapterMonospaceAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterMarkQuoteAPI(OrgContext* org_context, haxorg_ImmAdapterMarkQuoteAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterRadioTargetAPI(OrgContext* org_context, haxorg_ImmAdapterRadioTargetAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterVerbatimAPI(OrgContext* org_context, haxorg_ImmAdapterVerbatimAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterItalicAPI(OrgContext* org_context, haxorg_ImmAdapterItalicAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterStrikeAPI(OrgContext* org_context, haxorg_ImmAdapterStrikeAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterParAPI(OrgContext* org_context, haxorg_ImmAdapterParAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmMarkup_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmMarkupAdapter(OrgContext* org_context, haxorg_ImmMarkupAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmLatex_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmLatexAdapter(OrgContext* org_context, haxorg_ImmLatexAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_SubtreeLogHead haxorg_ImmAdapterTOfImmSubtreeLog_getHead_const(OrgContext* org_context, haxorg_ImmSubtreeLogAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmSubtreeLog_getDesc_const(OrgContext* org_context, haxorg_ImmSubtreeLogAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmSubtreeLog_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmSubtreeLogAdapter(OrgContext* org_context, haxorg_ImmSubtreeLogAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmColonExample_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmColonExampleAdapter(OrgContext* org_context, haxorg_ImmColonExampleAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmAdapterTOfImmCall_getName_const(OrgContext* org_context, haxorg_ImmCallAdapter __this);
HAXORG_C_API_LINKAGE haxorg_AttrGroup haxorg_ImmAdapterTOfImmCall_getAttrs_const(OrgContext* org_context, haxorg_ImmCallAdapter __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmAdapterTOfImmCall_getIsCommand_const(OrgContext* org_context, haxorg_ImmCallAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCall_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCallAdapter(OrgContext* org_context, haxorg_ImmCallAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmAdapterTOfImmFile_getRelPath_const(OrgContext* org_context, haxorg_ImmFileAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmAdapterTOfImmFile_getAbsPath_const(OrgContext* org_context, haxorg_ImmFileAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmFile_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmFileAdapter(OrgContext* org_context, haxorg_ImmFileAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmAdapterTOfImmDirectory_getRelPath_const(OrgContext* org_context, haxorg_ImmDirectoryAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmAdapterTOfImmDirectory_getAbsPath_const(OrgContext* org_context, haxorg_ImmDirectoryAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmDirectory_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmDirectoryAdapter(OrgContext* org_context, haxorg_ImmDirectoryAdapter* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmAdapterTOfImmSymlink_getIsDirectory_const(OrgContext* org_context, haxorg_ImmSymlinkAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmAdapterTOfImmSymlink_getAbsPath_const(OrgContext* org_context, haxorg_ImmSymlinkAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmSymlink_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmSymlinkAdapter(OrgContext* org_context, haxorg_ImmSymlinkAdapter* obj);
HAXORG_C_API_LINKAGE int haxorg_ImmAdapterTOfImmDocumentFragment_getBaseLine_const(OrgContext* org_context, haxorg_ImmDocumentFragmentAdapter __this);
HAXORG_C_API_LINKAGE int haxorg_ImmAdapterTOfImmDocumentFragment_getBaseCol_const(OrgContext* org_context, haxorg_ImmDocumentFragmentAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmDocumentFragment_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmDocumentFragmentAdapter(OrgContext* org_context, haxorg_ImmDocumentFragmentAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_ImmCriticMarkupKind haxorg_ImmAdapterTOfImmCriticMarkup_getKind_const(OrgContext* org_context, haxorg_ImmCriticMarkupAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCriticMarkup_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCriticMarkupAdapter(OrgContext* org_context, haxorg_ImmCriticMarkupAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_CheckboxState haxorg_ImmAdapterTOfImmListItem_getCheckbox_const(OrgContext* org_context, haxorg_ImmListItemAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmListItem_getHeader_const(OrgContext* org_context, haxorg_ImmListItemAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmListItem_getBullet_const(OrgContext* org_context, haxorg_ImmListItemAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmListItem_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmListItemAdapter(OrgContext* org_context, haxorg_ImmListItemAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_InitialSubtreeVisibility haxorg_ImmAdapterTOfImmDocumentOptions_getInitialVisibility_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter __this);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmAdapterTOfImmDocumentOptions_getProperties_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter __this);
HAXORG_C_API_LINKAGE haxorg_DocumentExportConfig haxorg_ImmAdapterTOfImmDocumentOptions_getExportConfig_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmDocumentOptions_getFixedWidthSections_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmDocumentOptions_getStartupIndented_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmDocumentOptions_getCategory_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmDocumentOptions_getSetupfile_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmDocumentOptions_getMaxSubtreeLevelExport_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmDocumentOptions_getColumns_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter __this);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmAdapterTOfImmDocumentOptions_getTodoKeywords_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter __this);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmAdapterTOfImmDocumentOptions_getDoneKeywords_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmDocumentOptions_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmDocumentOptionsAdapter(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmDocument_getTitle_const(OrgContext* org_context, haxorg_ImmDocumentAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmDocument_getAuthor_const(OrgContext* org_context, haxorg_ImmDocumentAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmDocument_getCreator_const(OrgContext* org_context, haxorg_ImmDocumentAdapter __this);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmAdapterTOfImmDocument_getFiletags_const(OrgContext* org_context, haxorg_ImmDocumentAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmDocument_getEmail_const(OrgContext* org_context, haxorg_ImmDocumentAdapter __this);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmAdapterTOfImmDocument_getLanguage_const(OrgContext* org_context, haxorg_ImmDocumentAdapter __this);
HAXORG_C_API_LINKAGE haxorg_ImmAdapter haxorg_ImmAdapterTOfImmDocument_getOptions_const(OrgContext* org_context, haxorg_ImmDocumentAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmDocument_getExportFileName_const(OrgContext* org_context, haxorg_ImmDocumentAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmDocument_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmDocumentAdapter(OrgContext* org_context, haxorg_ImmDocumentAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmAdapterTOfImmFileTarget_getPath_const(OrgContext* org_context, haxorg_ImmFileTargetAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmFileTarget_getLine_const(OrgContext* org_context, haxorg_ImmFileTargetAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmFileTarget_getSearchTarget_const(OrgContext* org_context, haxorg_ImmFileTargetAdapter __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmAdapterTOfImmFileTarget_getRestrictToHeadlines_const(OrgContext* org_context, haxorg_ImmFileTargetAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmFileTarget_getTargetId_const(OrgContext* org_context, haxorg_ImmFileTargetAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmFileTarget_getRegexp_const(OrgContext* org_context, haxorg_ImmFileTargetAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmFileTarget_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmFileTargetAdapter(OrgContext* org_context, haxorg_ImmFileTargetAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmTextSeparator_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmTextSeparatorAdapter(OrgContext* org_context, haxorg_ImmTextSeparatorAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdInclude_getPath_const(OrgContext* org_context, haxorg_ImmCmdIncludeAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmCmdInclude_getFirstLine_const(OrgContext* org_context, haxorg_ImmCmdIncludeAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmCmdInclude_getLastLine_const(OrgContext* org_context, haxorg_ImmCmdIncludeAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmdInclude_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdIncludeAdapter(OrgContext* org_context, haxorg_ImmCmdIncludeAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmDocumentGroup_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmDocumentGroupAdapter(OrgContext* org_context, haxorg_ImmDocumentGroupAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_BlockCenter(OrgContext* org_context, haxorg_BlockCenter* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_BlockQuote(OrgContext* org_context, haxorg_BlockQuote* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_BlockVerse(OrgContext* org_context, haxorg_BlockVerse* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_BlockDynamicFallback_get_name(OrgContext* org_context, haxorg_BlockDynamicFallback __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_BlockDynamicFallback(OrgContext* org_context, haxorg_BlockDynamicFallback* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_BlockExample(OrgContext* org_context, haxorg_BlockExample* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_BlockExport_get_exporter(OrgContext* org_context, haxorg_BlockExport __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_BlockExport_get_content(OrgContext* org_context, haxorg_BlockExport __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_BlockExport_getPlacement_const(OrgContext* org_context, haxorg_BlockExport __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_BlockExport(OrgContext* org_context, haxorg_BlockExport* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_BlockAdmonition(OrgContext* org_context, haxorg_BlockAdmonition* obj);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfOrgCodeEvalOutput haxorg_BlockCodeEvalResult_get_raw(OrgContext* org_context, haxorg_BlockCodeEvalResult __this);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_BlockCodeEvalResult_get_node(OrgContext* org_context, haxorg_BlockCodeEvalResult __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_BlockCodeEvalResult(OrgContext* org_context, haxorg_BlockCodeEvalResult* obj);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_BlockCode_get_lang(OrgContext* org_context, haxorg_BlockCode __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfSemIdOfBlockCodeEvalResult haxorg_BlockCode_get_result(OrgContext* org_context, haxorg_BlockCode __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfBlockCodeLine haxorg_BlockCode_get_lines(OrgContext* org_context, haxorg_BlockCode __this);
HAXORG_C_API_LINKAGE haxorg_AttrGroup haxorg_BlockCode_get_switches(OrgContext* org_context, haxorg_BlockCode __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_BlockCode_getVariable_const(OrgContext* org_context, haxorg_BlockCode __this, haxorg_HstdStr varname);
HAXORG_C_API_LINKAGE void haxorg_destroy_BlockCode(OrgContext* org_context, haxorg_BlockCode* obj);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfSemIdOfRow haxorg_Table_get_rows(OrgContext* org_context, haxorg_Table __this);
HAXORG_C_API_LINKAGE bool haxorg_Table_get_isBlock(OrgContext* org_context, haxorg_Table __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_Table(OrgContext* org_context, haxorg_Table* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Attached(OrgContext* org_context, haxorg_Attached* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmBlockCenter___eq___const(OrgContext* org_context, haxorg_ImmBlockCenter __this, haxorg_ImmBlockCenter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockCenter(OrgContext* org_context, haxorg_ImmBlockCenter* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmBlockQuote___eq___const(OrgContext* org_context, haxorg_ImmBlockQuote __this, haxorg_ImmBlockQuote other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockQuote(OrgContext* org_context, haxorg_ImmBlockQuote* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmBlockVerse___eq___const(OrgContext* org_context, haxorg_ImmBlockVerse __this, haxorg_ImmBlockVerse other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockVerse(OrgContext* org_context, haxorg_ImmBlockVerse* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmBlockDynamicFallback_get_name(OrgContext* org_context, haxorg_ImmBlockDynamicFallback __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmBlockDynamicFallback___eq___const(OrgContext* org_context, haxorg_ImmBlockDynamicFallback __this, haxorg_ImmBlockDynamicFallback other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockDynamicFallback(OrgContext* org_context, haxorg_ImmBlockDynamicFallback* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmBlockExample___eq___const(OrgContext* org_context, haxorg_ImmBlockExample __this, haxorg_ImmBlockExample other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockExample(OrgContext* org_context, haxorg_ImmBlockExample* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmBlockExport_get_exporter(OrgContext* org_context, haxorg_ImmBlockExport __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmBlockExport_get_content(OrgContext* org_context, haxorg_ImmBlockExport __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmBlockExport___eq___const(OrgContext* org_context, haxorg_ImmBlockExport __this, haxorg_ImmBlockExport other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockExport(OrgContext* org_context, haxorg_ImmBlockExport* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmBlockAdmonition___eq___const(OrgContext* org_context, haxorg_ImmBlockAdmonition __this, haxorg_ImmBlockAdmonition other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockAdmonition(OrgContext* org_context, haxorg_ImmBlockAdmonition* obj);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmBlockCodeEvalResult_get_raw(OrgContext* org_context, haxorg_ImmBlockCodeEvalResult __this);
HAXORG_C_API_LINKAGE haxorg_ImmId haxorg_ImmBlockCodeEvalResult_get_node(OrgContext* org_context, haxorg_ImmBlockCodeEvalResult __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmBlockCodeEvalResult___eq___const(OrgContext* org_context, haxorg_ImmBlockCodeEvalResult __this, haxorg_ImmBlockCodeEvalResult other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockCodeEvalResult(OrgContext* org_context, haxorg_ImmBlockCodeEvalResult* obj);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmBlockCode_get_lang(OrgContext* org_context, haxorg_ImmBlockCode __this);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmBlockCode_get_result(OrgContext* org_context, haxorg_ImmBlockCode __this);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmBlockCode_get_lines(OrgContext* org_context, haxorg_ImmBlockCode __this);
HAXORG_C_API_LINKAGE haxorg_AttrGroup haxorg_ImmBlockCode_get_switches(OrgContext* org_context, haxorg_ImmBlockCode __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmBlockCode___eq___const(OrgContext* org_context, haxorg_ImmBlockCode __this, haxorg_ImmBlockCode other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockCode(OrgContext* org_context, haxorg_ImmBlockCode* obj);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmTable_get_rows(OrgContext* org_context, haxorg_ImmTable __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmTable_get_isBlock(OrgContext* org_context, haxorg_ImmTable __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmTable___eq___const(OrgContext* org_context, haxorg_ImmTable __this, haxorg_ImmTable other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmTable(OrgContext* org_context, haxorg_ImmTable* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmAttached___eq___const(OrgContext* org_context, haxorg_ImmAttached __this, haxorg_ImmAttached other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAttached(OrgContext* org_context, haxorg_ImmAttached* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterLineCommandAPI(OrgContext* org_context, haxorg_ImmAdapterLineCommandAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdCustomArgsAPI(OrgContext* org_context, haxorg_ImmAdapterCmdCustomArgsAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdCreatorAPI(OrgContext* org_context, haxorg_ImmAdapterCmdCreatorAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdAuthorAPI(OrgContext* org_context, haxorg_ImmAdapterCmdAuthorAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdEmailAPI(OrgContext* org_context, haxorg_ImmAdapterCmdEmailAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdLanguageAPI(OrgContext* org_context, haxorg_ImmAdapterCmdLanguageAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdTblfmAPI(OrgContext* org_context, haxorg_ImmAdapterCmdTblfmAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterBlockAPI(OrgContext* org_context, haxorg_ImmAdapterBlockAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCellAPI(OrgContext* org_context, haxorg_ImmAdapterCellAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterRowAPI(OrgContext* org_context, haxorg_ImmAdapterRowAPI* obj);
HAXORG_C_API_LINKAGE haxorg_AttrGroup haxorg_ImmAdapterTOfImmCmd_getAttrs_const(OrgContext* org_context, haxorg_ImmCmdAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmd_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdAdapter(OrgContext* org_context, haxorg_ImmCmdAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdCustomRaw_getName_const(OrgContext* org_context, haxorg_ImmCmdCustomRawAdapter __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmAdapterTOfImmCmdCustomRaw_getIsAttached_const(OrgContext* org_context, haxorg_ImmCmdCustomRawAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdCustomRaw_getText_const(OrgContext* org_context, haxorg_ImmCmdCustomRawAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmdCustomRaw_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdCustomRawAdapter(OrgContext* org_context, haxorg_ImmCmdCustomRawAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdCustomText_getName_const(OrgContext* org_context, haxorg_ImmCmdCustomTextAdapter __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmAdapterTOfImmCmdCustomText_getIsAttached_const(OrgContext* org_context, haxorg_ImmCmdCustomTextAdapter __this);
HAXORG_C_API_LINKAGE haxorg_ImmAdapter haxorg_ImmAdapterTOfImmCmdCustomText_getText_const(OrgContext* org_context, haxorg_ImmCmdCustomTextAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmdCustomText_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdCustomTextAdapter(OrgContext* org_context, haxorg_ImmCmdCustomTextAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmLink_getDescription_const(OrgContext* org_context, haxorg_ImmLinkAdapter __this);
HAXORG_C_API_LINKAGE haxorg_LinkTarget haxorg_ImmAdapterTOfImmLink_getTarget_const(OrgContext* org_context, haxorg_ImmLinkAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmLink_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmLinkAdapter(OrgContext* org_context, haxorg_ImmLinkAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmBlockComment_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockCommentAdapter(OrgContext* org_context, haxorg_ImmBlockCommentAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmParagraph_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmParagraphAdapter(OrgContext* org_context, haxorg_ImmParagraphAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmList_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmListAdapter(OrgContext* org_context, haxorg_ImmListAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_HashTagText haxorg_ImmAdapterTOfImmHashTag_getText_const(OrgContext* org_context, haxorg_ImmHashTagAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmHashTag_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmHashTagAdapter(OrgContext* org_context, haxorg_ImmHashTagAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmAdapterTOfImmInlineFootnote_getTag_const(OrgContext* org_context, haxorg_ImmInlineFootnoteAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmInlineFootnote_getDefinition_const(OrgContext* org_context, haxorg_ImmInlineFootnoteAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmInlineFootnote_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmInlineFootnoteAdapter(OrgContext* org_context, haxorg_ImmInlineFootnoteAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmEscaped_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmEscapedAdapter(OrgContext* org_context, haxorg_ImmEscapedAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmNewline_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmNewlineAdapter(OrgContext* org_context, haxorg_ImmNewlineAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmSpace_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmSpaceAdapter(OrgContext* org_context, haxorg_ImmSpaceAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmWord_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmWordAdapter(OrgContext* org_context, haxorg_ImmWordAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmAtMention_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAtMentionAdapter(OrgContext* org_context, haxorg_ImmAtMentionAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmRawText_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmRawTextAdapter(OrgContext* org_context, haxorg_ImmRawTextAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmPunctuation_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmPunctuationAdapter(OrgContext* org_context, haxorg_ImmPunctuationAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmPlaceholder_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmPlaceholderAdapter(OrgContext* org_context, haxorg_ImmPlaceholderAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmBigIdent_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBigIdentAdapter(OrgContext* org_context, haxorg_ImmBigIdentAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmTextTarget_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmTextTargetAdapter(OrgContext* org_context, haxorg_ImmTextTargetAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmBold_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBoldAdapter(OrgContext* org_context, haxorg_ImmBoldAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmUnderline_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmUnderlineAdapter(OrgContext* org_context, haxorg_ImmUnderlineAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmMonospace_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmMonospaceAdapter(OrgContext* org_context, haxorg_ImmMonospaceAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmMarkQuote_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmMarkQuoteAdapter(OrgContext* org_context, haxorg_ImmMarkQuoteAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmAdapterTOfImmRadioTarget_getWords_const(OrgContext* org_context, haxorg_ImmRadioTargetAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmRadioTarget_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmRadioTargetAdapter(OrgContext* org_context, haxorg_ImmRadioTargetAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmVerbatim_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmVerbatimAdapter(OrgContext* org_context, haxorg_ImmVerbatimAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmItalic_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmItalicAdapter(OrgContext* org_context, haxorg_ImmItalicAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmStrike_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmStrikeAdapter(OrgContext* org_context, haxorg_ImmStrikeAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmPar_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmParAdapter(OrgContext* org_context, haxorg_ImmParAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_CmdCaption_get_text(OrgContext* org_context, haxorg_CmdCaption __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdCaption(OrgContext* org_context, haxorg_CmdCaption* obj);
HAXORG_C_API_LINKAGE haxorg_ColumnView haxorg_CmdColumns_get_view(OrgContext* org_context, haxorg_CmdColumns __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdColumns(OrgContext* org_context, haxorg_CmdColumns* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_CmdName_get_name(OrgContext* org_context, haxorg_CmdName __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdName(OrgContext* org_context, haxorg_CmdName* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_CmdCall_get_name(OrgContext* org_context, haxorg_CmdCall __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_CmdCall_get_fileName(OrgContext* org_context, haxorg_CmdCall __this);
HAXORG_C_API_LINKAGE haxorg_AttrGroup haxorg_CmdCall_get_insideHeaderAttrs(OrgContext* org_context, haxorg_CmdCall __this);
HAXORG_C_API_LINKAGE haxorg_AttrGroup haxorg_CmdCall_get_callAttrs(OrgContext* org_context, haxorg_CmdCall __this);
HAXORG_C_API_LINKAGE haxorg_AttrGroup haxorg_CmdCall_get_endHeaderAttrs(OrgContext* org_context, haxorg_CmdCall __this);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfSemIdOfBlockCodeEvalResult haxorg_CmdCall_get_result(OrgContext* org_context, haxorg_CmdCall __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdCall(OrgContext* org_context, haxorg_CmdCall* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_CmdAttr_get_target(OrgContext* org_context, haxorg_CmdAttr __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdAttr(OrgContext* org_context, haxorg_CmdAttr* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_CmdExport_get_exporter(OrgContext* org_context, haxorg_CmdExport __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_CmdExport_get_content(OrgContext* org_context, haxorg_CmdExport __this);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdExport(OrgContext* org_context, haxorg_CmdExport* obj);
HAXORG_C_API_LINKAGE haxorg_ImmId haxorg_ImmCmdCaption_get_text(OrgContext* org_context, haxorg_ImmCmdCaption __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCmdCaption___eq___const(OrgContext* org_context, haxorg_ImmCmdCaption __this, haxorg_ImmCmdCaption other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdCaption(OrgContext* org_context, haxorg_ImmCmdCaption* obj);
HAXORG_C_API_LINKAGE haxorg_ColumnView haxorg_ImmCmdColumns_get_view(OrgContext* org_context, haxorg_ImmCmdColumns __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCmdColumns___eq___const(OrgContext* org_context, haxorg_ImmCmdColumns __this, haxorg_ImmCmdColumns other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdColumns(OrgContext* org_context, haxorg_ImmCmdColumns* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmCmdName_get_name(OrgContext* org_context, haxorg_ImmCmdName __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCmdName___eq___const(OrgContext* org_context, haxorg_ImmCmdName __this, haxorg_ImmCmdName other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdName(OrgContext* org_context, haxorg_ImmCmdName* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmCmdCall_get_name(OrgContext* org_context, haxorg_ImmCmdCall __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmCmdCall_get_fileName(OrgContext* org_context, haxorg_ImmCmdCall __this);
HAXORG_C_API_LINKAGE haxorg_AttrGroup haxorg_ImmCmdCall_get_insideHeaderAttrs(OrgContext* org_context, haxorg_ImmCmdCall __this);
HAXORG_C_API_LINKAGE haxorg_AttrGroup haxorg_ImmCmdCall_get_callAttrs(OrgContext* org_context, haxorg_ImmCmdCall __this);
HAXORG_C_API_LINKAGE haxorg_AttrGroup haxorg_ImmCmdCall_get_endHeaderAttrs(OrgContext* org_context, haxorg_ImmCmdCall __this);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmCmdCall_get_result(OrgContext* org_context, haxorg_ImmCmdCall __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCmdCall___eq___const(OrgContext* org_context, haxorg_ImmCmdCall __this, haxorg_ImmCmdCall other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdCall(OrgContext* org_context, haxorg_ImmCmdCall* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmCmdAttr_get_target(OrgContext* org_context, haxorg_ImmCmdAttr __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCmdAttr___eq___const(OrgContext* org_context, haxorg_ImmCmdAttr __this, haxorg_ImmCmdAttr other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdAttr(OrgContext* org_context, haxorg_ImmCmdAttr* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmCmdExport_get_exporter(OrgContext* org_context, haxorg_ImmCmdExport __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmCmdExport_get_content(OrgContext* org_context, haxorg_ImmCmdExport __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmCmdExport___eq___const(OrgContext* org_context, haxorg_ImmCmdExport __this, haxorg_ImmCmdExport other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdExport(OrgContext* org_context, haxorg_ImmCmdExport* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterAttachedAPI(OrgContext* org_context, haxorg_ImmAdapterAttachedAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmLineCommand_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmLineCommandAdapter(OrgContext* org_context, haxorg_ImmLineCommandAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdCustomArgs_getName_const(OrgContext* org_context, haxorg_ImmCmdCustomArgsAdapter __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmAdapterTOfImmCmdCustomArgs_getIsAttached_const(OrgContext* org_context, haxorg_ImmCmdCustomArgsAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmdCustomArgs_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdCustomArgsAdapter(OrgContext* org_context, haxorg_ImmCmdCustomArgsAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_ImmAdapter haxorg_ImmAdapterTOfImmCmdCreator_getText_const(OrgContext* org_context, haxorg_ImmCmdCreatorAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmdCreator_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdCreatorAdapter(OrgContext* org_context, haxorg_ImmCmdCreatorAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_ImmAdapter haxorg_ImmAdapterTOfImmCmdAuthor_getText_const(OrgContext* org_context, haxorg_ImmCmdAuthorAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmdAuthor_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdAuthorAdapter(OrgContext* org_context, haxorg_ImmCmdAuthorAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdEmail_getText_const(OrgContext* org_context, haxorg_ImmCmdEmailAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmdEmail_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdEmailAdapter(OrgContext* org_context, haxorg_ImmCmdEmailAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdLanguage_getText_const(OrgContext* org_context, haxorg_ImmCmdLanguageAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmdLanguage_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdLanguageAdapter(OrgContext* org_context, haxorg_ImmCmdLanguageAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_Tblfm haxorg_ImmAdapterTOfImmCmdTblfm_getExpr_const(OrgContext* org_context, haxorg_ImmCmdTblfmAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmdTblfm_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdTblfmAdapter(OrgContext* org_context, haxorg_ImmCmdTblfmAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterBlockCenterAPI(OrgContext* org_context, haxorg_ImmAdapterBlockCenterAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterBlockQuoteAPI(OrgContext* org_context, haxorg_ImmAdapterBlockQuoteAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterBlockVerseAPI(OrgContext* org_context, haxorg_ImmAdapterBlockVerseAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterBlockExampleAPI(OrgContext* org_context, haxorg_ImmAdapterBlockExampleAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterInlineExportAPI(OrgContext* org_context, haxorg_ImmAdapterInlineExportAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdExportAPI(OrgContext* org_context, haxorg_ImmAdapterCmdExportAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterBlockExportAPI(OrgContext* org_context, haxorg_ImmAdapterBlockExportAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterBlockDynamicFallbackAPI(OrgContext* org_context, haxorg_ImmAdapterBlockDynamicFallbackAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterBlockAdmonitionAPI(OrgContext* org_context, haxorg_ImmAdapterBlockAdmonitionAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterBlockCodeEvalResultAPI(OrgContext* org_context, haxorg_ImmAdapterBlockCodeEvalResultAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterBlockCodeAPI(OrgContext* org_context, haxorg_ImmAdapterBlockCodeAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterTableAPI(OrgContext* org_context, haxorg_ImmAdapterTableAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmBlock_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockAdapter(OrgContext* org_context, haxorg_ImmBlockAdapter* obj);
HAXORG_C_API_LINKAGE bool haxorg_ImmAdapterTOfImmCell_getIsBlock_const(OrgContext* org_context, haxorg_ImmCellAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCell_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCellAdapter(OrgContext* org_context, haxorg_ImmCellAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmAdapterTOfImmRow_getCells_const(OrgContext* org_context, haxorg_ImmRowAdapter __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmAdapterTOfImmRow_getIsBlock_const(OrgContext* org_context, haxorg_ImmRowAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmRow_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmRowAdapter(OrgContext* org_context, haxorg_ImmRowAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdCaptionAPI(OrgContext* org_context, haxorg_ImmAdapterCmdCaptionAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdColumnsAPI(OrgContext* org_context, haxorg_ImmAdapterCmdColumnsAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdNameAPI(OrgContext* org_context, haxorg_ImmAdapterCmdNameAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdCallAPI(OrgContext* org_context, haxorg_ImmAdapterCmdCallAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdResultsAPI(OrgContext* org_context, haxorg_ImmAdapterCmdResultsAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdAttrAPI(OrgContext* org_context, haxorg_ImmAdapterCmdAttrAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmAttached_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAttachedAdapter(OrgContext* org_context, haxorg_ImmAttachedAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmBlockCenter_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockCenterAdapter(OrgContext* org_context, haxorg_ImmBlockCenterAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmBlockQuote_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockQuoteAdapter(OrgContext* org_context, haxorg_ImmBlockQuoteAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmBlockVerse_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockVerseAdapter(OrgContext* org_context, haxorg_ImmBlockVerseAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmBlockExample_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockExampleAdapter(OrgContext* org_context, haxorg_ImmBlockExampleAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmAdapterTOfImmInlineExport_getExporter_const(OrgContext* org_context, haxorg_ImmInlineExportAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmAdapterTOfImmInlineExport_getContent_const(OrgContext* org_context, haxorg_ImmInlineExportAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmInlineExport_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmInlineExportAdapter(OrgContext* org_context, haxorg_ImmInlineExportAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdExport_getExporter_const(OrgContext* org_context, haxorg_ImmCmdExportAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdExport_getContent_const(OrgContext* org_context, haxorg_ImmCmdExportAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmdExport_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdExportAdapter(OrgContext* org_context, haxorg_ImmCmdExportAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmAdapterTOfImmBlockExport_getExporter_const(OrgContext* org_context, haxorg_ImmBlockExportAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmAdapterTOfImmBlockExport_getContent_const(OrgContext* org_context, haxorg_ImmBlockExportAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmBlockExport_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockExportAdapter(OrgContext* org_context, haxorg_ImmBlockExportAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmAdapterTOfImmBlockDynamicFallback_getName_const(OrgContext* org_context, haxorg_ImmBlockDynamicFallbackAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmBlockDynamicFallback_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockDynamicFallbackAdapter(OrgContext* org_context, haxorg_ImmBlockDynamicFallbackAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmBlockAdmonition_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockAdmonitionAdapter(OrgContext* org_context, haxorg_ImmBlockAdmonitionAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmAdapterTOfImmBlockCodeEvalResult_getRaw_const(OrgContext* org_context, haxorg_ImmBlockCodeEvalResultAdapter __this);
HAXORG_C_API_LINKAGE haxorg_ImmAdapter haxorg_ImmAdapterTOfImmBlockCodeEvalResult_getNode_const(OrgContext* org_context, haxorg_ImmBlockCodeEvalResultAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmBlockCodeEvalResult_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockCodeEvalResultAdapter(OrgContext* org_context, haxorg_ImmBlockCodeEvalResultAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmBlockCode_getLang_const(OrgContext* org_context, haxorg_ImmBlockCodeAdapter __this);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmAdapterTOfImmBlockCode_getResult_const(OrgContext* org_context, haxorg_ImmBlockCodeAdapter __this);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmAdapterTOfImmBlockCode_getLines_const(OrgContext* org_context, haxorg_ImmBlockCodeAdapter __this);
HAXORG_C_API_LINKAGE haxorg_AttrGroup haxorg_ImmAdapterTOfImmBlockCode_getSwitches_const(OrgContext* org_context, haxorg_ImmBlockCodeAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmBlockCode_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockCodeAdapter(OrgContext* org_context, haxorg_ImmBlockCodeAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmAdapterTOfImmTable_getRows_const(OrgContext* org_context, haxorg_ImmTableAdapter __this);
HAXORG_C_API_LINKAGE bool haxorg_ImmAdapterTOfImmTable_getIsBlock_const(OrgContext* org_context, haxorg_ImmTableAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmTable_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmTableAdapter(OrgContext* org_context, haxorg_ImmTableAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_ImmAdapter haxorg_ImmAdapterTOfImmCmdCaption_getText_const(OrgContext* org_context, haxorg_ImmCmdCaptionAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmdCaption_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdCaptionAdapter(OrgContext* org_context, haxorg_ImmCmdCaptionAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_ColumnView haxorg_ImmAdapterTOfImmCmdColumns_getView_const(OrgContext* org_context, haxorg_ImmCmdColumnsAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmdColumns_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdColumnsAdapter(OrgContext* org_context, haxorg_ImmCmdColumnsAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdName_getName_const(OrgContext* org_context, haxorg_ImmCmdNameAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmdName_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdNameAdapter(OrgContext* org_context, haxorg_ImmCmdNameAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdCall_getName_const(OrgContext* org_context, haxorg_ImmCmdCallAdapter __this);
HAXORG_C_API_LINKAGE haxorg_HstdOpt haxorg_ImmAdapterTOfImmCmdCall_getFileName_const(OrgContext* org_context, haxorg_ImmCmdCallAdapter __this);
HAXORG_C_API_LINKAGE haxorg_AttrGroup haxorg_ImmAdapterTOfImmCmdCall_getInsideHeaderAttrs_const(OrgContext* org_context, haxorg_ImmCmdCallAdapter __this);
HAXORG_C_API_LINKAGE haxorg_AttrGroup haxorg_ImmAdapterTOfImmCmdCall_getCallAttrs_const(OrgContext* org_context, haxorg_ImmCmdCallAdapter __this);
HAXORG_C_API_LINKAGE haxorg_AttrGroup haxorg_ImmAdapterTOfImmCmdCall_getEndHeaderAttrs_const(OrgContext* org_context, haxorg_ImmCmdCallAdapter __this);
HAXORG_C_API_LINKAGE haxorg_ImmVec haxorg_ImmAdapterTOfImmCmdCall_getResult_const(OrgContext* org_context, haxorg_ImmCmdCallAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmdCall_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdCallAdapter(OrgContext* org_context, haxorg_ImmCmdCallAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdAttr_getTarget_const(OrgContext* org_context, haxorg_ImmCmdAttrAdapter __this);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmdAttr_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdAttrAdapter(OrgContext* org_context, haxorg_ImmCmdAttrAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_newSemTimeStatic(OrgContext* org_context, haxorg_UserTimeBreakdown breakdown, bool isActive);
HAXORG_C_API_LINKAGE haxorg_ImmAstContext haxorg_initImmutableAstContext(OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_asOneNode(OrgContext* org_context, haxorg_SemIdOfOrg arg);
HAXORG_C_API_LINKAGE haxorg_StdString haxorg_formatToString(OrgContext* org_context, haxorg_SemIdOfOrg arg);
HAXORG_C_API_LINKAGE haxorg_StdString haxorg_exportToYamlString(OrgContext* org_context, haxorg_SemIdOfOrg node, haxorg_OrgYamlExportOpts opts);
HAXORG_C_API_LINKAGE void haxorg_exportToYamlFile(OrgContext* org_context, haxorg_SemIdOfOrg node, haxorg_StdString path, haxorg_OrgYamlExportOpts opts);
HAXORG_C_API_LINKAGE haxorg_StdString haxorg_exportToJsonString(OrgContext* org_context, haxorg_SemIdOfOrg node);
HAXORG_C_API_LINKAGE void haxorg_exportToJsonFile(OrgContext* org_context, haxorg_SemIdOfOrg node, haxorg_StdString path);
HAXORG_C_API_LINKAGE haxorg_SemIdOfOrg haxorg_readProtobufFile(OrgContext* org_context, haxorg_StdString file);
HAXORG_C_API_LINKAGE void haxorg_exportToProtobufFile(OrgContext* org_context, haxorg_SemIdOfOrg doc, haxorg_StdString file);
HAXORG_C_API_LINKAGE haxorg_StdString haxorg_exportToTreeString(OrgContext* org_context, haxorg_SemIdOfOrg node, haxorg_OrgTreeExportOpts opts);
HAXORG_C_API_LINKAGE void haxorg_exportToTreeFile(OrgContext* org_context, haxorg_SemIdOfOrg node, haxorg_StdString path, haxorg_OrgTreeExportOpts opts);
HAXORG_C_API_LINKAGE haxorg_AstTrackingMap haxorg_getAstTrackingMap(OrgContext* org_context, haxorg_HstdVecOfSemIdOfOrg nodes);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfAstTrackingGroup haxorg_getSubnodeGroups(OrgContext* org_context, haxorg_SemIdOfOrg node, haxorg_AstTrackingMap map);
HAXORG_C_API_LINKAGE haxorg_HstdVecOfSequenceAnnotation haxorg_annotateSequence(OrgContext* org_context, haxorg_HstdVecOfSequenceSegmentGroup groups, int first, int last);
HAXORG_C_API_LINKAGE haxorg_GraphMapGraphState haxorg_initMapGraphState(OrgContext* org_context, haxorg_ImmAstContext ast);
HAXORG_C_API_LINKAGE haxorg_StdString haxorg_serializeAstContextToText(OrgContext* org_context, haxorg_ImmAstContext store);
HAXORG_C_API_LINKAGE void haxorg_serializeAstContextFromText(OrgContext* org_context, haxorg_StdString binary, haxorg_ImmAstContext store);
HAXORG_C_API_LINKAGE haxorg_StdString haxorg_serializeAstEpochToText(OrgContext* org_context, haxorg_ImmAstReplaceEpoch store);
HAXORG_C_API_LINKAGE void haxorg_serializeAstEpochFromText(OrgContext* org_context, haxorg_StdString binary, haxorg_ImmAstReplaceEpoch store);
HAXORG_C_API_LINKAGE haxorg_StdString haxorg_serializeMapGraphToText(OrgContext* org_context, haxorg_GraphMapGraph store);
HAXORG_C_API_LINKAGE void haxorg_serializeMapGraphFromText(OrgContext* org_context, haxorg_StdString binary, haxorg_GraphMapGraph store);
HAXORG_C_API_LINKAGE haxorg_StdString haxorg_serializeFromTextToTreeDump(OrgContext* org_context, haxorg_StdString binary);
/* clang-format on */
