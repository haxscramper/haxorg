/* clang-format off */
#include <wrappers/c/haxorg_c_api.h>
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
struct haxorg_UserTimeBreakdown_vtable;

struct haxorg_UserTimeBreakdown;

struct haxorg_UserTime_vtable;

struct haxorg_UserTime;

struct haxorg_ParseSourceFileId_vtable;

struct haxorg_ParseSourceFileId;

struct haxorg_ParseSourceLoc_vtable;

struct haxorg_ParseSourceLoc;

struct haxorg_OrgJson_vtable;

struct haxorg_OrgJson;

struct haxorg_Org_vtable;

struct haxorg_Org;

struct haxorg_OperationsTracer_vtable;

struct haxorg_OperationsTracer;

struct haxorg_Cache_vtable;

struct haxorg_Cache;

struct haxorg_ParseOrgParseFragment_vtable;

struct haxorg_ParseOrgParseFragment;

struct haxorg_OrgParseParameters_vtable;

struct haxorg_OrgParseParameters;

struct haxorg_OrgDirectoryParseParameters_vtable;

struct haxorg_OrgDirectoryParseParameters;

struct haxorg_ParseContext_vtable;

struct haxorg_ParseContext;

struct haxorg_ImmReflFieldId_vtable;

struct haxorg_ImmReflFieldId;

struct haxorg_ImmId_vtable;

struct haxorg_ImmId;

struct haxorg_ImmOrg_vtable;

struct haxorg_ImmOrg;

struct haxorg_ImmPathStep_vtable;

struct haxorg_ImmPathStep;

struct haxorg_ImmPath_vtable;

struct haxorg_ImmPath;

struct haxorg_ImmUniqId_vtable;

struct haxorg_ImmUniqId;

struct haxorg_ImmAstReplaceEpoch_vtable;

struct haxorg_ImmAstReplaceEpoch;

struct haxorg_ImmAstContext_vtable;

struct haxorg_ImmAstContext;

struct haxorg_ImmAstVersion_vtable;

struct haxorg_ImmAstVersion;

struct haxorg_ImmAdapter_vtable;

struct haxorg_ImmAdapter;

struct haxorg_ImmAdapterTreeReprConf_vtable;

struct haxorg_ImmAdapterTreeReprConf;

struct haxorg_ImmAdapterVirtualBase_vtable;

struct haxorg_ImmAdapterVirtualBase;

struct haxorg_OrgYamlExportOpts_vtable;

struct haxorg_OrgYamlExportOpts;

struct haxorg_OrgTreeExportOpts_vtable;

struct haxorg_OrgTreeExportOpts;

struct haxorg_AstTrackingPath_vtable;

struct haxorg_AstTrackingPath;

struct haxorg_AstTrackingAlternatives_vtable;

struct haxorg_AstTrackingAlternatives;

struct haxorg_AstTrackingGroup_vtable;

struct haxorg_AstTrackingGroup;

struct haxorg_AstTrackingGroupRadioTarget_vtable;

struct haxorg_AstTrackingGroupRadioTarget;

struct haxorg_AstTrackingGroupSingle_vtable;

struct haxorg_AstTrackingGroupSingle;

struct haxorg_AstTrackingGroupTrackedHashtag_vtable;

struct haxorg_AstTrackingGroupTrackedHashtag;

struct haxorg_AstTrackingMap_vtable;

struct haxorg_AstTrackingMap;

struct haxorg_SequenceSegment_vtable;

struct haxorg_SequenceSegment;

struct haxorg_SequenceSegmentGroup_vtable;

struct haxorg_SequenceSegmentGroup;

struct haxorg_SequenceAnnotationTag_vtable;

struct haxorg_SequenceAnnotationTag;

struct haxorg_SequenceAnnotation_vtable;

struct haxorg_SequenceAnnotation;

struct haxorg_GraphMapLink_vtable;

struct haxorg_GraphMapLink;

struct haxorg_GraphMapLinkLink_vtable;

struct haxorg_GraphMapLinkLink;

struct haxorg_GraphMapLinkRadio_vtable;

struct haxorg_GraphMapLinkRadio;

struct haxorg_GraphMapNodeProp_vtable;

struct haxorg_GraphMapNodeProp;

struct haxorg_GraphMapEdgeProp_vtable;

struct haxorg_GraphMapEdgeProp;

struct haxorg_GraphMapNode_vtable;

struct haxorg_GraphMapNode;

struct haxorg_GraphMapEdge_vtable;

struct haxorg_GraphMapEdge;

struct haxorg_GraphMapGraph_vtable;

struct haxorg_GraphMapGraph;

struct haxorg_GraphMapConfig_vtable;

struct haxorg_GraphMapConfig;

struct haxorg_GraphMapGraphState_vtable;

struct haxorg_GraphMapGraphState;

struct haxorg_LispCode_vtable;

struct haxorg_LispCode;

struct haxorg_LispCodeCall_vtable;

struct haxorg_LispCodeCall;

struct haxorg_LispCodeList_vtable;

struct haxorg_LispCodeList;

struct haxorg_LispCodeKeyValue_vtable;

struct haxorg_LispCodeKeyValue;

struct haxorg_LispCodeNumber_vtable;

struct haxorg_LispCodeNumber;

struct haxorg_LispCodeText_vtable;

struct haxorg_LispCodeText;

struct haxorg_LispCodeIdent_vtable;

struct haxorg_LispCodeIdent;

struct haxorg_LispCodeBoolean_vtable;

struct haxorg_LispCodeBoolean;

struct haxorg_LispCodeReal_vtable;

struct haxorg_LispCodeReal;

struct haxorg_Tblfm_vtable;

struct haxorg_Tblfm;

struct haxorg_TblfmExpr_vtable;

struct haxorg_TblfmExpr;

struct haxorg_TblfmExprAxisRef_vtable;

struct haxorg_TblfmExprAxisRef;

struct haxorg_TblfmExprAxisRefPosition_vtable;

struct haxorg_TblfmExprAxisRefPosition;

struct haxorg_TblfmExprAxisRefPositionIndex_vtable;

struct haxorg_TblfmExprAxisRefPositionIndex;

struct haxorg_TblfmExprAxisRefPositionName_vtable;

struct haxorg_TblfmExprAxisRefPositionName;

struct haxorg_TblfmExprAxisName_vtable;

struct haxorg_TblfmExprAxisName;

struct haxorg_TblfmExprIntLiteral_vtable;

struct haxorg_TblfmExprIntLiteral;

struct haxorg_TblfmExprFloatLiteral_vtable;

struct haxorg_TblfmExprFloatLiteral;

struct haxorg_TblfmExprRangeRef_vtable;

struct haxorg_TblfmExprRangeRef;

struct haxorg_TblfmExprCall_vtable;

struct haxorg_TblfmExprCall;

struct haxorg_TblfmExprElisp_vtable;

struct haxorg_TblfmExprElisp;

struct haxorg_TblfmAssign_vtable;

struct haxorg_TblfmAssign;

struct haxorg_AttrValue_vtable;

struct haxorg_AttrValue;

struct haxorg_AttrValueDimensionSpan_vtable;

struct haxorg_AttrValueDimensionSpan;

struct haxorg_AttrValueTextValue_vtable;

struct haxorg_AttrValueTextValue;

struct haxorg_AttrValueFileReference_vtable;

struct haxorg_AttrValueFileReference;

struct haxorg_AttrValueLispValue_vtable;

struct haxorg_AttrValueLispValue;

struct haxorg_HashTagFlat_vtable;

struct haxorg_HashTagFlat;

struct haxorg_TodoKeyword_vtable;

struct haxorg_TodoKeyword;

struct haxorg_HashTagText_vtable;

struct haxorg_HashTagText;

struct haxorg_SubtreePath_vtable;

struct haxorg_SubtreePath;

struct haxorg_LinkTarget_vtable;

struct haxorg_LinkTarget;

struct haxorg_LinkTargetRaw_vtable;

struct haxorg_LinkTargetRaw;

struct haxorg_LinkTargetId_vtable;

struct haxorg_LinkTargetId;

struct haxorg_LinkTargetCustomId_vtable;

struct haxorg_LinkTargetCustomId;

struct haxorg_LinkTargetSubtreeTitle_vtable;

struct haxorg_LinkTargetSubtreeTitle;

struct haxorg_LinkTargetPerson_vtable;

struct haxorg_LinkTargetPerson;

struct haxorg_LinkTargetUserProtocol_vtable;

struct haxorg_LinkTargetUserProtocol;

struct haxorg_LinkTargetInternal_vtable;

struct haxorg_LinkTargetInternal;

struct haxorg_LinkTargetFootnote_vtable;

struct haxorg_LinkTargetFootnote;

struct haxorg_LinkTargetFile_vtable;

struct haxorg_LinkTargetFile;

struct haxorg_LinkTargetAttachment_vtable;

struct haxorg_LinkTargetAttachment;

struct haxorg_SubtreeLogHead_vtable;

struct haxorg_SubtreeLogHead;

struct haxorg_SubtreeLogHeadPriority_vtable;

struct haxorg_SubtreeLogHeadPriority;

struct haxorg_SubtreeLogHeadNote_vtable;

struct haxorg_SubtreeLogHeadNote;

struct haxorg_SubtreeLogHeadRefile_vtable;

struct haxorg_SubtreeLogHeadRefile;

struct haxorg_SubtreeLogHeadClock_vtable;

struct haxorg_SubtreeLogHeadClock;

struct haxorg_SubtreeLogHeadState_vtable;

struct haxorg_SubtreeLogHeadState;

struct haxorg_SubtreeLogHeadDeadline_vtable;

struct haxorg_SubtreeLogHeadDeadline;

struct haxorg_SubtreeLogHeadSchedule_vtable;

struct haxorg_SubtreeLogHeadSchedule;

struct haxorg_SubtreeLogHeadTag_vtable;

struct haxorg_SubtreeLogHeadTag;

struct haxorg_SubtreeLogHeadUnknown_vtable;

struct haxorg_SubtreeLogHeadUnknown;

struct haxorg_SubtreeCompletion_vtable;

struct haxorg_SubtreeCompletion;

struct haxorg_AttrList_vtable;

struct haxorg_AttrList;

struct haxorg_AttrGroup_vtable;

struct haxorg_AttrGroup;

struct haxorg_OrgCodeEvalInput_vtable;

struct haxorg_OrgCodeEvalInput;

struct haxorg_OrgCodeEvalInputVar_vtable;

struct haxorg_OrgCodeEvalInputVar;

struct haxorg_OrgCodeEvalOutput_vtable;

struct haxorg_OrgCodeEvalOutput;

struct haxorg_ColumnView_vtable;

struct haxorg_ColumnView;

struct haxorg_ColumnViewSummary_vtable;

struct haxorg_ColumnViewSummary;

struct haxorg_ColumnViewSummaryCheckboxAggregate_vtable;

struct haxorg_ColumnViewSummaryCheckboxAggregate;

struct haxorg_ColumnViewSummaryMathAggregate_vtable;

struct haxorg_ColumnViewSummaryMathAggregate;

struct haxorg_ColumnViewColumn_vtable;

struct haxorg_ColumnViewColumn;

struct haxorg_BlockCodeLine_vtable;

struct haxorg_BlockCodeLine;

struct haxorg_BlockCodeLinePart_vtable;

struct haxorg_BlockCodeLinePart;

struct haxorg_BlockCodeLinePartRaw_vtable;

struct haxorg_BlockCodeLinePartRaw;

struct haxorg_BlockCodeLinePartCallout_vtable;

struct haxorg_BlockCodeLinePartCallout;

struct haxorg_BlockCodeLinePartTangle_vtable;

struct haxorg_BlockCodeLinePartTangle;

struct haxorg_DocumentExportConfig_vtable;

struct haxorg_DocumentExportConfig;

struct haxorg_DocumentExportConfigTaskExport_vtable;

struct haxorg_DocumentExportConfigTaskExport;

struct haxorg_DocumentExportConfigDoExport_vtable;

struct haxorg_DocumentExportConfigDoExport;

struct haxorg_DocumentExportConfigExportFixed_vtable;

struct haxorg_DocumentExportConfigExportFixed;

struct haxorg_SubtreePeriod_vtable;

struct haxorg_SubtreePeriod;

struct haxorg_NamedProperty_vtable;

struct haxorg_NamedProperty;

struct haxorg_NamedPropertyNonblocking_vtable;

struct haxorg_NamedPropertyNonblocking;

struct haxorg_NamedPropertyArchiveTime_vtable;

struct haxorg_NamedPropertyArchiveTime;

struct haxorg_NamedPropertyArchiveFile_vtable;

struct haxorg_NamedPropertyArchiveFile;

struct haxorg_NamedPropertyArchiveOlpath_vtable;

struct haxorg_NamedPropertyArchiveOlpath;

struct haxorg_NamedPropertyArchiveTarget_vtable;

struct haxorg_NamedPropertyArchiveTarget;

struct haxorg_NamedPropertyArchiveCategory_vtable;

struct haxorg_NamedPropertyArchiveCategory;

struct haxorg_NamedPropertyArchiveTodo_vtable;

struct haxorg_NamedPropertyArchiveTodo;

struct haxorg_NamedPropertyTrigger_vtable;

struct haxorg_NamedPropertyTrigger;

struct haxorg_NamedPropertyExportLatexClass_vtable;

struct haxorg_NamedPropertyExportLatexClass;

struct haxorg_NamedPropertyCookieData_vtable;

struct haxorg_NamedPropertyCookieData;

struct haxorg_NamedPropertyExportLatexClassOptions_vtable;

struct haxorg_NamedPropertyExportLatexClassOptions;

struct haxorg_NamedPropertyExportLatexHeader_vtable;

struct haxorg_NamedPropertyExportLatexHeader;

struct haxorg_NamedPropertyExportLatexCompiler_vtable;

struct haxorg_NamedPropertyExportLatexCompiler;

struct haxorg_NamedPropertyOrdered_vtable;

struct haxorg_NamedPropertyOrdered;

struct haxorg_NamedPropertyEffort_vtable;

struct haxorg_NamedPropertyEffort;

struct haxorg_NamedPropertyVisibility_vtable;

struct haxorg_NamedPropertyVisibility;

struct haxorg_NamedPropertyExportOptions_vtable;

struct haxorg_NamedPropertyExportOptions;

struct haxorg_NamedPropertyBlocker_vtable;

struct haxorg_NamedPropertyBlocker;

struct haxorg_NamedPropertyUnnumbered_vtable;

struct haxorg_NamedPropertyUnnumbered;

struct haxorg_NamedPropertyCreated_vtable;

struct haxorg_NamedPropertyCreated;

struct haxorg_NamedPropertyRadioId_vtable;

struct haxorg_NamedPropertyRadioId;

struct haxorg_NamedPropertyHashtagDef_vtable;

struct haxorg_NamedPropertyHashtagDef;

struct haxorg_NamedPropertyCustomArgs_vtable;

struct haxorg_NamedPropertyCustomArgs;

struct haxorg_NamedPropertyCustomRaw_vtable;

struct haxorg_NamedPropertyCustomRaw;

struct haxorg_NamedPropertyCustomId_vtable;

struct haxorg_NamedPropertyCustomId;

struct haxorg_NamedPropertyCustomSubtreeJson_vtable;

struct haxorg_NamedPropertyCustomSubtreeJson;

struct haxorg_NamedPropertyCustomSubtreeFlags_vtable;

struct haxorg_NamedPropertyCustomSubtreeFlags;

struct haxorg_OrgDiagnostics_vtable;

struct haxorg_OrgDiagnostics;

struct haxorg_OrgDiagnosticsParseTokenError_vtable;

struct haxorg_OrgDiagnosticsParseTokenError;

struct haxorg_OrgDiagnosticsParseError_vtable;

struct haxorg_OrgDiagnosticsParseError;

struct haxorg_OrgDiagnosticsIncludeError_vtable;

struct haxorg_OrgDiagnosticsIncludeError;

struct haxorg_OrgDiagnosticsConvertError_vtable;

struct haxorg_OrgDiagnosticsConvertError;

struct haxorg_OrgDiagnosticsInternalError_vtable;

struct haxorg_OrgDiagnosticsInternalError;

struct haxorg_NoNode_vtable;

struct haxorg_NoNode;

struct haxorg_ErrorItem_vtable;

struct haxorg_ErrorItem;

struct haxorg_ErrorGroup_vtable;

struct haxorg_ErrorGroup;

struct haxorg_Stmt_vtable;

struct haxorg_Stmt;

struct haxorg_Inline_vtable;

struct haxorg_Inline;

struct haxorg_StmtList_vtable;

struct haxorg_StmtList;

struct haxorg_Empty_vtable;

struct haxorg_Empty;

struct haxorg_Leaf_vtable;

struct haxorg_Leaf;

struct haxorg_Time_vtable;

struct haxorg_Time;

struct haxorg_TimeRepeat_vtable;

struct haxorg_TimeRepeat;

struct haxorg_TimeStatic_vtable;

struct haxorg_TimeStatic;

struct haxorg_TimeDynamic_vtable;

struct haxorg_TimeDynamic;

struct haxorg_TimeRange_vtable;

struct haxorg_TimeRange;

struct haxorg_Macro_vtable;

struct haxorg_Macro;

struct haxorg_Symbol_vtable;

struct haxorg_Symbol;

struct haxorg_SymbolParam_vtable;

struct haxorg_SymbolParam;

struct haxorg_ErrorSkipGroup_vtable;

struct haxorg_ErrorSkipGroup;

struct haxorg_Markup_vtable;

struct haxorg_Markup;

struct haxorg_RadioTarget_vtable;

struct haxorg_RadioTarget;

struct haxorg_Latex_vtable;

struct haxorg_Latex;

struct haxorg_SubtreeLog_vtable;

struct haxorg_SubtreeLog;

struct haxorg_Subtree_vtable;

struct haxorg_Subtree;

struct haxorg_ColonExample_vtable;

struct haxorg_ColonExample;

struct haxorg_Call_vtable;

struct haxorg_Call;

struct haxorg_ListItem_vtable;

struct haxorg_ListItem;

struct haxorg_DocumentOptions_vtable;

struct haxorg_DocumentOptions;

struct haxorg_DocumentFragment_vtable;

struct haxorg_DocumentFragment;

struct haxorg_CriticMarkup_vtable;

struct haxorg_CriticMarkup;

struct haxorg_Document_vtable;

struct haxorg_Document;

struct haxorg_FileTarget_vtable;

struct haxorg_FileTarget;

struct haxorg_TextSeparator_vtable;

struct haxorg_TextSeparator;

struct haxorg_DocumentGroup_vtable;

struct haxorg_DocumentGroup;

struct haxorg_File_vtable;

struct haxorg_File;

struct haxorg_FileDocument_vtable;

struct haxorg_FileDocument;

struct haxorg_FileAttachment_vtable;

struct haxorg_FileAttachment;

struct haxorg_FileSource_vtable;

struct haxorg_FileSource;

struct haxorg_Directory_vtable;

struct haxorg_Directory;

struct haxorg_Symlink_vtable;

struct haxorg_Symlink;

struct haxorg_CmdInclude_vtable;

struct haxorg_CmdInclude;

struct haxorg_CmdIncludeIncludeBase_vtable;

struct haxorg_CmdIncludeIncludeBase;

struct haxorg_CmdIncludeExample_vtable;

struct haxorg_CmdIncludeExample;

struct haxorg_CmdIncludeExport_vtable;

struct haxorg_CmdIncludeExport;

struct haxorg_CmdIncludeCustom_vtable;

struct haxorg_CmdIncludeCustom;

struct haxorg_CmdIncludeSrc_vtable;

struct haxorg_CmdIncludeSrc;

struct haxorg_CmdIncludeOrgDocument_vtable;

struct haxorg_CmdIncludeOrgDocument;

struct haxorg_ImmNoNode_vtable;

struct haxorg_ImmNoNode;

struct haxorg_ImmErrorItem_vtable;

struct haxorg_ImmErrorItem;

struct haxorg_ImmErrorGroup_vtable;

struct haxorg_ImmErrorGroup;

struct haxorg_ImmStmt_vtable;

struct haxorg_ImmStmt;

struct haxorg_ImmInline_vtable;

struct haxorg_ImmInline;

struct haxorg_ImmStmtList_vtable;

struct haxorg_ImmStmtList;

struct haxorg_ImmEmpty_vtable;

struct haxorg_ImmEmpty;

struct haxorg_ImmLeaf_vtable;

struct haxorg_ImmLeaf;

struct haxorg_ImmTime_vtable;

struct haxorg_ImmTime;

struct haxorg_ImmTimeRepeat_vtable;

struct haxorg_ImmTimeRepeat;

struct haxorg_ImmTimeStatic_vtable;

struct haxorg_ImmTimeStatic;

struct haxorg_ImmTimeDynamic_vtable;

struct haxorg_ImmTimeDynamic;

struct haxorg_ImmTimeRange_vtable;

struct haxorg_ImmTimeRange;

struct haxorg_ImmMacro_vtable;

struct haxorg_ImmMacro;

struct haxorg_ImmSymbol_vtable;

struct haxorg_ImmSymbol;

struct haxorg_ImmSymbolParam_vtable;

struct haxorg_ImmSymbolParam;

struct haxorg_ImmErrorSkipGroup_vtable;

struct haxorg_ImmErrorSkipGroup;

struct haxorg_ImmMarkup_vtable;

struct haxorg_ImmMarkup;

struct haxorg_ImmRadioTarget_vtable;

struct haxorg_ImmRadioTarget;

struct haxorg_ImmLatex_vtable;

struct haxorg_ImmLatex;

struct haxorg_ImmSubtreeLog_vtable;

struct haxorg_ImmSubtreeLog;

struct haxorg_ImmSubtree_vtable;

struct haxorg_ImmSubtree;

struct haxorg_ImmColonExample_vtable;

struct haxorg_ImmColonExample;

struct haxorg_ImmCall_vtable;

struct haxorg_ImmCall;

struct haxorg_ImmListItem_vtable;

struct haxorg_ImmListItem;

struct haxorg_ImmDocumentOptions_vtable;

struct haxorg_ImmDocumentOptions;

struct haxorg_ImmDocumentFragment_vtable;

struct haxorg_ImmDocumentFragment;

struct haxorg_ImmCriticMarkup_vtable;

struct haxorg_ImmCriticMarkup;

struct haxorg_ImmDocument_vtable;

struct haxorg_ImmDocument;

struct haxorg_ImmFileTarget_vtable;

struct haxorg_ImmFileTarget;

struct haxorg_ImmTextSeparator_vtable;

struct haxorg_ImmTextSeparator;

struct haxorg_ImmDocumentGroup_vtable;

struct haxorg_ImmDocumentGroup;

struct haxorg_ImmFile_vtable;

struct haxorg_ImmFile;

struct haxorg_ImmFileDocument_vtable;

struct haxorg_ImmFileDocument;

struct haxorg_ImmFileAttachment_vtable;

struct haxorg_ImmFileAttachment;

struct haxorg_ImmFileSource_vtable;

struct haxorg_ImmFileSource;

struct haxorg_ImmDirectory_vtable;

struct haxorg_ImmDirectory;

struct haxorg_ImmSymlink_vtable;

struct haxorg_ImmSymlink;

struct haxorg_ImmCmdInclude_vtable;

struct haxorg_ImmCmdInclude;

struct haxorg_ImmCmdIncludeIncludeBase_vtable;

struct haxorg_ImmCmdIncludeIncludeBase;

struct haxorg_ImmCmdIncludeExample_vtable;

struct haxorg_ImmCmdIncludeExample;

struct haxorg_ImmCmdIncludeExport_vtable;

struct haxorg_ImmCmdIncludeExport;

struct haxorg_ImmCmdIncludeCustom_vtable;

struct haxorg_ImmCmdIncludeCustom;

struct haxorg_ImmCmdIncludeSrc_vtable;

struct haxorg_ImmCmdIncludeSrc;

struct haxorg_ImmCmdIncludeOrgDocument_vtable;

struct haxorg_ImmCmdIncludeOrgDocument;

struct haxorg_ImmAdapterOrgAPI_vtable;

struct haxorg_ImmAdapterOrgAPI;

struct haxorg_Cmd_vtable;

struct haxorg_Cmd;

struct haxorg_CmdCustomRaw_vtable;

struct haxorg_CmdCustomRaw;

struct haxorg_CmdCustomText_vtable;

struct haxorg_CmdCustomText;

struct haxorg_Link_vtable;

struct haxorg_Link;

struct haxorg_BlockComment_vtable;

struct haxorg_BlockComment;

struct haxorg_Paragraph_vtable;

struct haxorg_Paragraph;

struct haxorg_List_vtable;

struct haxorg_List;

struct haxorg_HashTag_vtable;

struct haxorg_HashTag;

struct haxorg_InlineFootnote_vtable;

struct haxorg_InlineFootnote;

struct haxorg_InlineExport_vtable;

struct haxorg_InlineExport;

struct haxorg_Escaped_vtable;

struct haxorg_Escaped;

struct haxorg_Newline_vtable;

struct haxorg_Newline;

struct haxorg_Space_vtable;

struct haxorg_Space;

struct haxorg_Word_vtable;

struct haxorg_Word;

struct haxorg_AtMention_vtable;

struct haxorg_AtMention;

struct haxorg_RawText_vtable;

struct haxorg_RawText;

struct haxorg_Punctuation_vtable;

struct haxorg_Punctuation;

struct haxorg_Placeholder_vtable;

struct haxorg_Placeholder;

struct haxorg_BigIdent_vtable;

struct haxorg_BigIdent;

struct haxorg_TextTarget_vtable;

struct haxorg_TextTarget;

struct haxorg_ErrorSkipToken_vtable;

struct haxorg_ErrorSkipToken;

struct haxorg_Bold_vtable;

struct haxorg_Bold;

struct haxorg_Underline_vtable;

struct haxorg_Underline;

struct haxorg_Monospace_vtable;

struct haxorg_Monospace;

struct haxorg_MarkQuote_vtable;

struct haxorg_MarkQuote;

struct haxorg_Verbatim_vtable;

struct haxorg_Verbatim;

struct haxorg_Italic_vtable;

struct haxorg_Italic;

struct haxorg_Strike_vtable;

struct haxorg_Strike;

struct haxorg_Par_vtable;

struct haxorg_Par;

struct haxorg_ImmCmd_vtable;

struct haxorg_ImmCmd;

struct haxorg_ImmCmdCustomRaw_vtable;

struct haxorg_ImmCmdCustomRaw;

struct haxorg_ImmCmdCustomText_vtable;

struct haxorg_ImmCmdCustomText;

struct haxorg_ImmLink_vtable;

struct haxorg_ImmLink;

struct haxorg_ImmBlockComment_vtable;

struct haxorg_ImmBlockComment;

struct haxorg_ImmParagraph_vtable;

struct haxorg_ImmParagraph;

struct haxorg_ImmList_vtable;

struct haxorg_ImmList;

struct haxorg_ImmHashTag_vtable;

struct haxorg_ImmHashTag;

struct haxorg_ImmInlineFootnote_vtable;

struct haxorg_ImmInlineFootnote;

struct haxorg_ImmInlineExport_vtable;

struct haxorg_ImmInlineExport;

struct haxorg_ImmEscaped_vtable;

struct haxorg_ImmEscaped;

struct haxorg_ImmNewline_vtable;

struct haxorg_ImmNewline;

struct haxorg_ImmSpace_vtable;

struct haxorg_ImmSpace;

struct haxorg_ImmWord_vtable;

struct haxorg_ImmWord;

struct haxorg_ImmAtMention_vtable;

struct haxorg_ImmAtMention;

struct haxorg_ImmRawText_vtable;

struct haxorg_ImmRawText;

struct haxorg_ImmPunctuation_vtable;

struct haxorg_ImmPunctuation;

struct haxorg_ImmPlaceholder_vtable;

struct haxorg_ImmPlaceholder;

struct haxorg_ImmBigIdent_vtable;

struct haxorg_ImmBigIdent;

struct haxorg_ImmTextTarget_vtable;

struct haxorg_ImmTextTarget;

struct haxorg_ImmErrorSkipToken_vtable;

struct haxorg_ImmErrorSkipToken;

struct haxorg_ImmBold_vtable;

struct haxorg_ImmBold;

struct haxorg_ImmUnderline_vtable;

struct haxorg_ImmUnderline;

struct haxorg_ImmMonospace_vtable;

struct haxorg_ImmMonospace;

struct haxorg_ImmMarkQuote_vtable;

struct haxorg_ImmMarkQuote;

struct haxorg_ImmVerbatim_vtable;

struct haxorg_ImmVerbatim;

struct haxorg_ImmItalic_vtable;

struct haxorg_ImmItalic;

struct haxorg_ImmStrike_vtable;

struct haxorg_ImmStrike;

struct haxorg_ImmPar_vtable;

struct haxorg_ImmPar;

struct haxorg_ImmAdapterStmtAPI_vtable;

struct haxorg_ImmAdapterStmtAPI;

struct haxorg_ImmAdapterSubtreeAPI_vtable;

struct haxorg_ImmAdapterSubtreeAPI;

struct haxorg_ImmAdapterNoNodeAPI_vtable;

struct haxorg_ImmAdapterNoNodeAPI;

struct haxorg_ImmAdapterAttrAPI_vtable;

struct haxorg_ImmAdapterAttrAPI;

struct haxorg_ImmAdapterAttrListAPI_vtable;

struct haxorg_ImmAdapterAttrListAPI;

struct haxorg_ImmAdapterAttrsAPI_vtable;

struct haxorg_ImmAdapterAttrsAPI;

struct haxorg_ImmAdapterErrorItemAPI_vtable;

struct haxorg_ImmAdapterErrorItemAPI;

struct haxorg_ImmAdapterErrorGroupAPI_vtable;

struct haxorg_ImmAdapterErrorGroupAPI;

struct haxorg_ImmAdapterErrorSkipGroupAPI_vtable;

struct haxorg_ImmAdapterErrorSkipGroupAPI;

struct haxorg_ImmAdapterErrorSkipTokenAPI_vtable;

struct haxorg_ImmAdapterErrorSkipTokenAPI;

struct haxorg_ImmAdapterStmtListAPI_vtable;

struct haxorg_ImmAdapterStmtListAPI;

struct haxorg_ImmAdapterEmptyAPI_vtable;

struct haxorg_ImmAdapterEmptyAPI;

struct haxorg_ImmAdapterInlineAPI_vtable;

struct haxorg_ImmAdapterInlineAPI;

struct haxorg_ImmAdapterTimeAPI_vtable;

struct haxorg_ImmAdapterTimeAPI;

struct haxorg_ImmAdapterTimeRangeAPI_vtable;

struct haxorg_ImmAdapterTimeRangeAPI;

struct haxorg_ImmAdapterMacroAPI_vtable;

struct haxorg_ImmAdapterMacroAPI;

struct haxorg_ImmAdapterSymbolAPI_vtable;

struct haxorg_ImmAdapterSymbolAPI;

struct haxorg_ImmAdapterLeafAPI_vtable;

struct haxorg_ImmAdapterLeafAPI;

struct haxorg_ImmAdapterMarkupAPI_vtable;

struct haxorg_ImmAdapterMarkupAPI;

struct haxorg_ImmAdapterLatexAPI_vtable;

struct haxorg_ImmAdapterLatexAPI;

struct haxorg_ImmAdapterSubtreeLogAPI_vtable;

struct haxorg_ImmAdapterSubtreeLogAPI;

struct haxorg_ImmAdapterColonExampleAPI_vtable;

struct haxorg_ImmAdapterColonExampleAPI;

struct haxorg_ImmAdapterCallAPI_vtable;

struct haxorg_ImmAdapterCallAPI;

struct haxorg_ImmAdapterFileAPI_vtable;

struct haxorg_ImmAdapterFileAPI;

struct haxorg_ImmAdapterDirectoryAPI_vtable;

struct haxorg_ImmAdapterDirectoryAPI;

struct haxorg_ImmAdapterSymlinkAPI_vtable;

struct haxorg_ImmAdapterSymlinkAPI;

struct haxorg_ImmAdapterDocumentFragmentAPI_vtable;

struct haxorg_ImmAdapterDocumentFragmentAPI;

struct haxorg_ImmAdapterCriticMarkupAPI_vtable;

struct haxorg_ImmAdapterCriticMarkupAPI;

struct haxorg_ImmAdapterListItemAPI_vtable;

struct haxorg_ImmAdapterListItemAPI;

struct haxorg_ImmAdapterDocumentOptionsAPI_vtable;

struct haxorg_ImmAdapterDocumentOptionsAPI;

struct haxorg_ImmAdapterDocumentAPI_vtable;

struct haxorg_ImmAdapterDocumentAPI;

struct haxorg_ImmAdapterFileTargetAPI_vtable;

struct haxorg_ImmAdapterFileTargetAPI;

struct haxorg_ImmAdapterTextSeparatorAPI_vtable;

struct haxorg_ImmAdapterTextSeparatorAPI;

struct haxorg_ImmAdapterCmdIncludeAPI_vtable;

struct haxorg_ImmAdapterCmdIncludeAPI;

struct haxorg_ImmAdapterDocumentGroupAPI_vtable;

struct haxorg_ImmAdapterDocumentGroupAPI;

struct haxorg_Block_vtable;

struct haxorg_Block;

struct haxorg_LineCommand_vtable;

struct haxorg_LineCommand;

struct haxorg_CmdCreator_vtable;

struct haxorg_CmdCreator;

struct haxorg_CmdAuthor_vtable;

struct haxorg_CmdAuthor;

struct haxorg_CmdEmail_vtable;

struct haxorg_CmdEmail;

struct haxorg_CmdLanguage_vtable;

struct haxorg_CmdLanguage;

struct haxorg_CmdCustomArgs_vtable;

struct haxorg_CmdCustomArgs;

struct haxorg_CmdTblfm_vtable;

struct haxorg_CmdTblfm;

struct haxorg_Cell_vtable;

struct haxorg_Cell;

struct haxorg_Row_vtable;

struct haxorg_Row;

struct haxorg_ImmBlock_vtable;

struct haxorg_ImmBlock;

struct haxorg_ImmLineCommand_vtable;

struct haxorg_ImmLineCommand;

struct haxorg_ImmCmdCreator_vtable;

struct haxorg_ImmCmdCreator;

struct haxorg_ImmCmdAuthor_vtable;

struct haxorg_ImmCmdAuthor;

struct haxorg_ImmCmdEmail_vtable;

struct haxorg_ImmCmdEmail;

struct haxorg_ImmCmdLanguage_vtable;

struct haxorg_ImmCmdLanguage;

struct haxorg_ImmCmdCustomArgs_vtable;

struct haxorg_ImmCmdCustomArgs;

struct haxorg_ImmCmdTblfm_vtable;

struct haxorg_ImmCmdTblfm;

struct haxorg_ImmCell_vtable;

struct haxorg_ImmCell;

struct haxorg_ImmRow_vtable;

struct haxorg_ImmRow;

struct haxorg_ImmAdapterCmdAPI_vtable;

struct haxorg_ImmAdapterCmdAPI;

struct haxorg_ImmAdapterCmdCustomRawAPI_vtable;

struct haxorg_ImmAdapterCmdCustomRawAPI;

struct haxorg_ImmAdapterCmdCustomTextAPI_vtable;

struct haxorg_ImmAdapterCmdCustomTextAPI;

struct haxorg_ImmAdapterLinkAPI_vtable;

struct haxorg_ImmAdapterLinkAPI;

struct haxorg_ImmAdapterBlockCommentAPI_vtable;

struct haxorg_ImmAdapterBlockCommentAPI;

struct haxorg_ImmAdapterParagraphAPI_vtable;

struct haxorg_ImmAdapterParagraphAPI;

struct haxorg_ImmAdapterListAPI_vtable;

struct haxorg_ImmAdapterListAPI;

struct haxorg_ImmStmtAdapter_vtable;

struct haxorg_ImmStmtAdapter;

struct haxorg_ImmSubtreeAdapter_vtable;

struct haxorg_ImmSubtreeAdapter;

struct haxorg_ImmNoNodeAdapter_vtable;

struct haxorg_ImmNoNodeAdapter;

struct haxorg_ImmErrorItemAdapter_vtable;

struct haxorg_ImmErrorItemAdapter;

struct haxorg_ImmErrorGroupAdapter_vtable;

struct haxorg_ImmErrorGroupAdapter;

struct haxorg_ImmErrorSkipGroupAdapter_vtable;

struct haxorg_ImmErrorSkipGroupAdapter;

struct haxorg_ImmErrorSkipTokenAdapter_vtable;

struct haxorg_ImmErrorSkipTokenAdapter;

struct haxorg_ImmStmtListAdapter_vtable;

struct haxorg_ImmStmtListAdapter;

struct haxorg_ImmEmptyAdapter_vtable;

struct haxorg_ImmEmptyAdapter;

struct haxorg_ImmAdapterHashTagAPI_vtable;

struct haxorg_ImmAdapterHashTagAPI;

struct haxorg_ImmAdapterInlineFootnoteAPI_vtable;

struct haxorg_ImmAdapterInlineFootnoteAPI;

struct haxorg_ImmAdapterSubtreeCompletionAPI_vtable;

struct haxorg_ImmAdapterSubtreeCompletionAPI;

struct haxorg_ImmInlineAdapter_vtable;

struct haxorg_ImmInlineAdapter;

struct haxorg_ImmTimeAdapter_vtable;

struct haxorg_ImmTimeAdapter;

struct haxorg_ImmTimeRangeAdapter_vtable;

struct haxorg_ImmTimeRangeAdapter;

struct haxorg_ImmMacroAdapter_vtable;

struct haxorg_ImmMacroAdapter;

struct haxorg_ImmSymbolAdapter_vtable;

struct haxorg_ImmSymbolAdapter;

struct haxorg_ImmAdapterEscapedAPI_vtable;

struct haxorg_ImmAdapterEscapedAPI;

struct haxorg_ImmAdapterNewlineAPI_vtable;

struct haxorg_ImmAdapterNewlineAPI;

struct haxorg_ImmAdapterSpaceAPI_vtable;

struct haxorg_ImmAdapterSpaceAPI;

struct haxorg_ImmAdapterWordAPI_vtable;

struct haxorg_ImmAdapterWordAPI;

struct haxorg_ImmAdapterAtMentionAPI_vtable;

struct haxorg_ImmAdapterAtMentionAPI;

struct haxorg_ImmAdapterRawTextAPI_vtable;

struct haxorg_ImmAdapterRawTextAPI;

struct haxorg_ImmAdapterPunctuationAPI_vtable;

struct haxorg_ImmAdapterPunctuationAPI;

struct haxorg_ImmAdapterPlaceholderAPI_vtable;

struct haxorg_ImmAdapterPlaceholderAPI;

struct haxorg_ImmAdapterBigIdentAPI_vtable;

struct haxorg_ImmAdapterBigIdentAPI;

struct haxorg_ImmAdapterTextTargetAPI_vtable;

struct haxorg_ImmAdapterTextTargetAPI;

struct haxorg_ImmLeafAdapter_vtable;

struct haxorg_ImmLeafAdapter;

struct haxorg_ImmAdapterBoldAPI_vtable;

struct haxorg_ImmAdapterBoldAPI;

struct haxorg_ImmAdapterUnderlineAPI_vtable;

struct haxorg_ImmAdapterUnderlineAPI;

struct haxorg_ImmAdapterMonospaceAPI_vtable;

struct haxorg_ImmAdapterMonospaceAPI;

struct haxorg_ImmAdapterMarkQuoteAPI_vtable;

struct haxorg_ImmAdapterMarkQuoteAPI;

struct haxorg_ImmAdapterRadioTargetAPI_vtable;

struct haxorg_ImmAdapterRadioTargetAPI;

struct haxorg_ImmAdapterVerbatimAPI_vtable;

struct haxorg_ImmAdapterVerbatimAPI;

struct haxorg_ImmAdapterItalicAPI_vtable;

struct haxorg_ImmAdapterItalicAPI;

struct haxorg_ImmAdapterStrikeAPI_vtable;

struct haxorg_ImmAdapterStrikeAPI;

struct haxorg_ImmAdapterParAPI_vtable;

struct haxorg_ImmAdapterParAPI;

struct haxorg_ImmMarkupAdapter_vtable;

struct haxorg_ImmMarkupAdapter;

struct haxorg_ImmLatexAdapter_vtable;

struct haxorg_ImmLatexAdapter;

struct haxorg_ImmSubtreeLogAdapter_vtable;

struct haxorg_ImmSubtreeLogAdapter;

struct haxorg_ImmColonExampleAdapter_vtable;

struct haxorg_ImmColonExampleAdapter;

struct haxorg_ImmCallAdapter_vtable;

struct haxorg_ImmCallAdapter;

struct haxorg_ImmFileAdapter_vtable;

struct haxorg_ImmFileAdapter;

struct haxorg_ImmDirectoryAdapter_vtable;

struct haxorg_ImmDirectoryAdapter;

struct haxorg_ImmSymlinkAdapter_vtable;

struct haxorg_ImmSymlinkAdapter;

struct haxorg_ImmDocumentFragmentAdapter_vtable;

struct haxorg_ImmDocumentFragmentAdapter;

struct haxorg_ImmCriticMarkupAdapter_vtable;

struct haxorg_ImmCriticMarkupAdapter;

struct haxorg_ImmListItemAdapter_vtable;

struct haxorg_ImmListItemAdapter;

struct haxorg_ImmDocumentOptionsAdapter_vtable;

struct haxorg_ImmDocumentOptionsAdapter;

struct haxorg_ImmDocumentAdapter_vtable;

struct haxorg_ImmDocumentAdapter;

struct haxorg_ImmFileTargetAdapter_vtable;

struct haxorg_ImmFileTargetAdapter;

struct haxorg_ImmTextSeparatorAdapter_vtable;

struct haxorg_ImmTextSeparatorAdapter;

struct haxorg_ImmCmdIncludeAdapter_vtable;

struct haxorg_ImmCmdIncludeAdapter;

struct haxorg_ImmDocumentGroupAdapter_vtable;

struct haxorg_ImmDocumentGroupAdapter;

struct haxorg_BlockCenter_vtable;

struct haxorg_BlockCenter;

struct haxorg_BlockQuote_vtable;

struct haxorg_BlockQuote;

struct haxorg_BlockVerse_vtable;

struct haxorg_BlockVerse;

struct haxorg_BlockDynamicFallback_vtable;

struct haxorg_BlockDynamicFallback;

struct haxorg_BlockExample_vtable;

struct haxorg_BlockExample;

struct haxorg_BlockExport_vtable;

struct haxorg_BlockExport;

struct haxorg_BlockAdmonition_vtable;

struct haxorg_BlockAdmonition;

struct haxorg_BlockCodeEvalResult_vtable;

struct haxorg_BlockCodeEvalResult;

struct haxorg_BlockCode_vtable;

struct haxorg_BlockCode;

struct haxorg_Table_vtable;

struct haxorg_Table;

struct haxorg_Attached_vtable;

struct haxorg_Attached;

struct haxorg_ImmBlockCenter_vtable;

struct haxorg_ImmBlockCenter;

struct haxorg_ImmBlockQuote_vtable;

struct haxorg_ImmBlockQuote;

struct haxorg_ImmBlockVerse_vtable;

struct haxorg_ImmBlockVerse;

struct haxorg_ImmBlockDynamicFallback_vtable;

struct haxorg_ImmBlockDynamicFallback;

struct haxorg_ImmBlockExample_vtable;

struct haxorg_ImmBlockExample;

struct haxorg_ImmBlockExport_vtable;

struct haxorg_ImmBlockExport;

struct haxorg_ImmBlockAdmonition_vtable;

struct haxorg_ImmBlockAdmonition;

struct haxorg_ImmBlockCodeEvalResult_vtable;

struct haxorg_ImmBlockCodeEvalResult;

struct haxorg_ImmBlockCode_vtable;

struct haxorg_ImmBlockCode;

struct haxorg_ImmTable_vtable;

struct haxorg_ImmTable;

struct haxorg_ImmAttached_vtable;

struct haxorg_ImmAttached;

struct haxorg_ImmAdapterLineCommandAPI_vtable;

struct haxorg_ImmAdapterLineCommandAPI;

struct haxorg_ImmAdapterCmdCustomArgsAPI_vtable;

struct haxorg_ImmAdapterCmdCustomArgsAPI;

struct haxorg_ImmAdapterCmdCreatorAPI_vtable;

struct haxorg_ImmAdapterCmdCreatorAPI;

struct haxorg_ImmAdapterCmdAuthorAPI_vtable;

struct haxorg_ImmAdapterCmdAuthorAPI;

struct haxorg_ImmAdapterCmdEmailAPI_vtable;

struct haxorg_ImmAdapterCmdEmailAPI;

struct haxorg_ImmAdapterCmdLanguageAPI_vtable;

struct haxorg_ImmAdapterCmdLanguageAPI;

struct haxorg_ImmAdapterCmdTblfmAPI_vtable;

struct haxorg_ImmAdapterCmdTblfmAPI;

struct haxorg_ImmAdapterBlockAPI_vtable;

struct haxorg_ImmAdapterBlockAPI;

struct haxorg_ImmAdapterCellAPI_vtable;

struct haxorg_ImmAdapterCellAPI;

struct haxorg_ImmAdapterRowAPI_vtable;

struct haxorg_ImmAdapterRowAPI;

struct haxorg_ImmCmdAdapter_vtable;

struct haxorg_ImmCmdAdapter;

struct haxorg_ImmCmdCustomRawAdapter_vtable;

struct haxorg_ImmCmdCustomRawAdapter;

struct haxorg_ImmCmdCustomTextAdapter_vtable;

struct haxorg_ImmCmdCustomTextAdapter;

struct haxorg_ImmLinkAdapter_vtable;

struct haxorg_ImmLinkAdapter;

struct haxorg_ImmBlockCommentAdapter_vtable;

struct haxorg_ImmBlockCommentAdapter;

struct haxorg_ImmParagraphAdapter_vtable;

struct haxorg_ImmParagraphAdapter;

struct haxorg_ImmListAdapter_vtable;

struct haxorg_ImmListAdapter;

struct haxorg_ImmHashTagAdapter_vtable;

struct haxorg_ImmHashTagAdapter;

struct haxorg_ImmInlineFootnoteAdapter_vtable;

struct haxorg_ImmInlineFootnoteAdapter;

struct haxorg_ImmEscapedAdapter_vtable;

struct haxorg_ImmEscapedAdapter;

struct haxorg_ImmNewlineAdapter_vtable;

struct haxorg_ImmNewlineAdapter;

struct haxorg_ImmSpaceAdapter_vtable;

struct haxorg_ImmSpaceAdapter;

struct haxorg_ImmWordAdapter_vtable;

struct haxorg_ImmWordAdapter;

struct haxorg_ImmAtMentionAdapter_vtable;

struct haxorg_ImmAtMentionAdapter;

struct haxorg_ImmRawTextAdapter_vtable;

struct haxorg_ImmRawTextAdapter;

struct haxorg_ImmPunctuationAdapter_vtable;

struct haxorg_ImmPunctuationAdapter;

struct haxorg_ImmPlaceholderAdapter_vtable;

struct haxorg_ImmPlaceholderAdapter;

struct haxorg_ImmBigIdentAdapter_vtable;

struct haxorg_ImmBigIdentAdapter;

struct haxorg_ImmTextTargetAdapter_vtable;

struct haxorg_ImmTextTargetAdapter;

struct haxorg_ImmBoldAdapter_vtable;

struct haxorg_ImmBoldAdapter;

struct haxorg_ImmUnderlineAdapter_vtable;

struct haxorg_ImmUnderlineAdapter;

struct haxorg_ImmMonospaceAdapter_vtable;

struct haxorg_ImmMonospaceAdapter;

struct haxorg_ImmMarkQuoteAdapter_vtable;

struct haxorg_ImmMarkQuoteAdapter;

struct haxorg_ImmRadioTargetAdapter_vtable;

struct haxorg_ImmRadioTargetAdapter;

struct haxorg_ImmVerbatimAdapter_vtable;

struct haxorg_ImmVerbatimAdapter;

struct haxorg_ImmItalicAdapter_vtable;

struct haxorg_ImmItalicAdapter;

struct haxorg_ImmStrikeAdapter_vtable;

struct haxorg_ImmStrikeAdapter;

struct haxorg_ImmParAdapter_vtable;

struct haxorg_ImmParAdapter;

struct haxorg_CmdCaption_vtable;

struct haxorg_CmdCaption;

struct haxorg_CmdColumns_vtable;

struct haxorg_CmdColumns;

struct haxorg_CmdName_vtable;

struct haxorg_CmdName;

struct haxorg_CmdCall_vtable;

struct haxorg_CmdCall;

struct haxorg_CmdAttr_vtable;

struct haxorg_CmdAttr;

struct haxorg_CmdExport_vtable;

struct haxorg_CmdExport;

struct haxorg_ImmCmdCaption_vtable;

struct haxorg_ImmCmdCaption;

struct haxorg_ImmCmdColumns_vtable;

struct haxorg_ImmCmdColumns;

struct haxorg_ImmCmdName_vtable;

struct haxorg_ImmCmdName;

struct haxorg_ImmCmdCall_vtable;

struct haxorg_ImmCmdCall;

struct haxorg_ImmCmdAttr_vtable;

struct haxorg_ImmCmdAttr;

struct haxorg_ImmCmdExport_vtable;

struct haxorg_ImmCmdExport;

struct haxorg_ImmAdapterAttachedAPI_vtable;

struct haxorg_ImmAdapterAttachedAPI;

struct haxorg_ImmLineCommandAdapter_vtable;

struct haxorg_ImmLineCommandAdapter;

struct haxorg_ImmCmdCustomArgsAdapter_vtable;

struct haxorg_ImmCmdCustomArgsAdapter;

struct haxorg_ImmCmdCreatorAdapter_vtable;

struct haxorg_ImmCmdCreatorAdapter;

struct haxorg_ImmCmdAuthorAdapter_vtable;

struct haxorg_ImmCmdAuthorAdapter;

struct haxorg_ImmCmdEmailAdapter_vtable;

struct haxorg_ImmCmdEmailAdapter;

struct haxorg_ImmCmdLanguageAdapter_vtable;

struct haxorg_ImmCmdLanguageAdapter;

struct haxorg_ImmCmdTblfmAdapter_vtable;

struct haxorg_ImmCmdTblfmAdapter;

struct haxorg_ImmAdapterBlockCenterAPI_vtable;

struct haxorg_ImmAdapterBlockCenterAPI;

struct haxorg_ImmAdapterBlockQuoteAPI_vtable;

struct haxorg_ImmAdapterBlockQuoteAPI;

struct haxorg_ImmAdapterBlockVerseAPI_vtable;

struct haxorg_ImmAdapterBlockVerseAPI;

struct haxorg_ImmAdapterBlockExampleAPI_vtable;

struct haxorg_ImmAdapterBlockExampleAPI;

struct haxorg_ImmAdapterInlineExportAPI_vtable;

struct haxorg_ImmAdapterInlineExportAPI;

struct haxorg_ImmAdapterCmdExportAPI_vtable;

struct haxorg_ImmAdapterCmdExportAPI;

struct haxorg_ImmAdapterBlockExportAPI_vtable;

struct haxorg_ImmAdapterBlockExportAPI;

struct haxorg_ImmAdapterBlockDynamicFallbackAPI_vtable;

struct haxorg_ImmAdapterBlockDynamicFallbackAPI;

struct haxorg_ImmAdapterBlockAdmonitionAPI_vtable;

struct haxorg_ImmAdapterBlockAdmonitionAPI;

struct haxorg_ImmAdapterBlockCodeEvalResultAPI_vtable;

struct haxorg_ImmAdapterBlockCodeEvalResultAPI;

struct haxorg_ImmAdapterBlockCodeAPI_vtable;

struct haxorg_ImmAdapterBlockCodeAPI;

struct haxorg_ImmAdapterTableAPI_vtable;

struct haxorg_ImmAdapterTableAPI;

struct haxorg_ImmBlockAdapter_vtable;

struct haxorg_ImmBlockAdapter;

struct haxorg_ImmCellAdapter_vtable;

struct haxorg_ImmCellAdapter;

struct haxorg_ImmRowAdapter_vtable;

struct haxorg_ImmRowAdapter;

struct haxorg_ImmAdapterCmdCaptionAPI_vtable;

struct haxorg_ImmAdapterCmdCaptionAPI;

struct haxorg_ImmAdapterCmdColumnsAPI_vtable;

struct haxorg_ImmAdapterCmdColumnsAPI;

struct haxorg_ImmAdapterCmdNameAPI_vtable;

struct haxorg_ImmAdapterCmdNameAPI;

struct haxorg_ImmAdapterCmdCallAPI_vtable;

struct haxorg_ImmAdapterCmdCallAPI;

struct haxorg_ImmAdapterCmdResultsAPI_vtable;

struct haxorg_ImmAdapterCmdResultsAPI;

struct haxorg_ImmAdapterCmdAttrAPI_vtable;

struct haxorg_ImmAdapterCmdAttrAPI;

struct haxorg_ImmAttachedAdapter_vtable;

struct haxorg_ImmAttachedAdapter;

struct haxorg_ImmBlockCenterAdapter_vtable;

struct haxorg_ImmBlockCenterAdapter;

struct haxorg_ImmBlockQuoteAdapter_vtable;

struct haxorg_ImmBlockQuoteAdapter;

struct haxorg_ImmBlockVerseAdapter_vtable;

struct haxorg_ImmBlockVerseAdapter;

struct haxorg_ImmBlockExampleAdapter_vtable;

struct haxorg_ImmBlockExampleAdapter;

struct haxorg_ImmInlineExportAdapter_vtable;

struct haxorg_ImmInlineExportAdapter;

struct haxorg_ImmCmdExportAdapter_vtable;

struct haxorg_ImmCmdExportAdapter;

struct haxorg_ImmBlockExportAdapter_vtable;

struct haxorg_ImmBlockExportAdapter;

struct haxorg_ImmBlockDynamicFallbackAdapter_vtable;

struct haxorg_ImmBlockDynamicFallbackAdapter;

struct haxorg_ImmBlockAdmonitionAdapter_vtable;

struct haxorg_ImmBlockAdmonitionAdapter;

struct haxorg_ImmBlockCodeEvalResultAdapter_vtable;

struct haxorg_ImmBlockCodeEvalResultAdapter;

struct haxorg_ImmBlockCodeAdapter_vtable;

struct haxorg_ImmBlockCodeAdapter;

struct haxorg_ImmTableAdapter_vtable;

struct haxorg_ImmTableAdapter;

struct haxorg_ImmCmdCaptionAdapter_vtable;

struct haxorg_ImmCmdCaptionAdapter;

struct haxorg_ImmCmdColumnsAdapter_vtable;

struct haxorg_ImmCmdColumnsAdapter;

struct haxorg_ImmCmdNameAdapter_vtable;

struct haxorg_ImmCmdNameAdapter;

struct haxorg_ImmCmdCallAdapter_vtable;

struct haxorg_ImmCmdCallAdapter;

struct haxorg_ImmCmdAttrAdapter_vtable;

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
/// \brief ['hstd', 'UserTimeBreakdown']
struct haxorg_UserTimeBreakdown {
  haxorg_UserTimeBreakdown_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_UserTime_vtable {};

/// \brief ['hstd', 'UserTime']
struct haxorg_UserTime {
  haxorg_UserTime_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ParseSourceFileId_vtable {};

/// \brief ['org', 'parse', 'SourceFileId']
struct haxorg_ParseSourceFileId {
  haxorg_ParseSourceFileId_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'parse', 'SourceLoc']
struct haxorg_ParseSourceLoc {
  haxorg_ParseSourceLoc_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_OrgJson_vtable {};

/// \brief ['org', 'sem', 'OrgJson']
struct haxorg_OrgJson {
  haxorg_OrgJson_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Org']
struct haxorg_Org {
  haxorg_Org_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['hstd', 'OperationsTracer']
struct haxorg_OperationsTracer {
  haxorg_OperationsTracer_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_Cache_vtable {};

/// \brief ['hstd', 'ext', 'Cache']
struct haxorg_Cache {
  haxorg_Cache_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'parse', 'OrgParseFragment']
struct haxorg_ParseOrgParseFragment {
  haxorg_ParseOrgParseFragment_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'parse', 'OrgParseParameters']
struct haxorg_OrgParseParameters {
  haxorg_OrgParseParameters_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_OrgDirectoryParseParameters_vtable {};

/// \brief ['org', 'parse', 'OrgDirectoryParseParameters']
struct haxorg_OrgDirectoryParseParameters {
  haxorg_OrgDirectoryParseParameters_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ParseContext_vtable {};

/// \brief ['org', 'parse', 'ParseContext']
struct haxorg_ParseContext {
  haxorg_ParseContext_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmReflFieldId_vtable {};

/// \brief ['org', 'imm', 'ImmReflFieldId']
struct haxorg_ImmReflFieldId {
  haxorg_ImmReflFieldId_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmId_vtable {};

/// \brief ['org', 'imm', 'ImmId']
struct haxorg_ImmId {
  haxorg_ImmId_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmOrg_vtable {};

/// \brief ['org', 'imm', 'ImmOrg']
struct haxorg_ImmOrg {
  haxorg_ImmOrg_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmPathStep_vtable {};

/// \brief ['org', 'imm', 'ImmPathStep']
struct haxorg_ImmPathStep {
  haxorg_ImmPathStep_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

typedef haxorg_ImmVecOfImmPathStep haxorg_ImmPathStore;
/// \brief ['org', 'imm', 'ImmPath']
struct haxorg_ImmPath {
  haxorg_ImmPath_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmUniqId_vtable {};

/// \brief ['org', 'imm', 'ImmUniqId']
struct haxorg_ImmUniqId {
  haxorg_ImmUniqId_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAstReplaceEpoch_vtable {};

/// \brief ['org', 'imm', 'ImmAstReplaceEpoch']
struct haxorg_ImmAstReplaceEpoch {
  haxorg_ImmAstReplaceEpoch_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAstContext_vtable {};

/// \brief ['org', 'imm', 'ImmAstContext']
struct haxorg_ImmAstContext {
  haxorg_ImmAstContext_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAstVersion_vtable {};

/// \brief ['org', 'imm', 'ImmAstVersion']
struct haxorg_ImmAstVersion {
  haxorg_ImmAstVersion_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapter', 'TreeReprConf']
struct haxorg_ImmAdapterTreeReprConf {
  haxorg_ImmAdapterTreeReprConf_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapter']
struct haxorg_ImmAdapter {
  haxorg_ImmAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterVirtualBase_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterVirtualBase']
struct haxorg_ImmAdapterVirtualBase {
  haxorg_ImmAdapterVirtualBase_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'OrgYamlExportOpts']
struct haxorg_OrgYamlExportOpts {
  haxorg_OrgYamlExportOpts_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'OrgTreeExportOpts']
struct haxorg_OrgTreeExportOpts {
  haxorg_OrgTreeExportOpts_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'AstTrackingPath']
struct haxorg_AstTrackingPath {
  haxorg_AstTrackingPath_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_AstTrackingAlternatives_vtable {};

/// \brief ['org', 'AstTrackingAlternatives']
struct haxorg_AstTrackingAlternatives {
  haxorg_AstTrackingAlternatives_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'AstTrackingGroup', 'RadioTarget']
struct haxorg_AstTrackingGroupRadioTarget {
  haxorg_AstTrackingGroupRadioTarget_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'AstTrackingGroup', 'Single']
struct haxorg_AstTrackingGroupSingle {
  haxorg_AstTrackingGroupSingle_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'AstTrackingGroup', 'TrackedHashtag']
struct haxorg_AstTrackingGroupTrackedHashtag {
  haxorg_AstTrackingGroupTrackedHashtag_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_AstTrackingGroup_vtable {};

/// \brief ['org', 'AstTrackingGroup']
struct haxorg_AstTrackingGroup {
  haxorg_AstTrackingGroup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'AstTrackingMap']
struct haxorg_AstTrackingMap {
  haxorg_AstTrackingMap_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['hstd', 'SequenceSegment']
struct haxorg_SequenceSegment {
  haxorg_SequenceSegment_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['hstd', 'SequenceSegmentGroup']
struct haxorg_SequenceSegmentGroup {
  haxorg_SequenceSegmentGroup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['hstd', 'SequenceAnnotationTag']
struct haxorg_SequenceAnnotationTag {
  haxorg_SequenceAnnotationTag_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['hstd', 'SequenceAnnotation']
struct haxorg_SequenceAnnotation {
  haxorg_SequenceAnnotation_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'graph', 'MapLink', 'Link']
struct haxorg_GraphMapLinkLink {
  haxorg_GraphMapLinkLink_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'graph', 'MapLink', 'Radio']
struct haxorg_GraphMapLinkRadio {
  haxorg_GraphMapLinkRadio_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_GraphMapLink_vtable {};

/// \brief ['org', 'graph', 'MapLink']
struct haxorg_GraphMapLink {
  haxorg_GraphMapLink_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'graph', 'MapNodeProp']
struct haxorg_GraphMapNodeProp {
  haxorg_GraphMapNodeProp_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'graph', 'MapEdgeProp']
struct haxorg_GraphMapEdgeProp {
  haxorg_GraphMapEdgeProp_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'graph', 'MapNode']
struct haxorg_GraphMapNode {
  haxorg_GraphMapNode_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'graph', 'MapEdge']
struct haxorg_GraphMapEdge {
  haxorg_GraphMapEdge_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'graph', 'MapGraph']
struct haxorg_GraphMapGraph {
  haxorg_GraphMapGraph_vtable const* vtable;
  haxorg_ptr_payload data;
};

typedef haxorg_HstdUnorderedMap haxorg_GraphEdgeProps;
typedef haxorg_HstdUnorderedMap haxorg_GraphAdjList;
typedef haxorg_HstdUnorderedMap haxorg_GraphNodeProps;
/// \brief ['org', 'graph', 'MapConfig']
struct haxorg_GraphMapConfig {
  haxorg_GraphMapConfig_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'graph', 'MapGraphState']
struct haxorg_GraphMapGraphState {
  haxorg_GraphMapGraphState_vtable const* vtable;
  haxorg_ptr_payload data;
};

typedef haxorg_HstdVec haxorg_GraphAdjNodesList;
/// \brief ['org', 'sem', 'LispCode', 'Call']
struct haxorg_LispCodeCall {
  haxorg_LispCodeCall_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'LispCode', 'List']
struct haxorg_LispCodeList {
  haxorg_LispCodeList_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'LispCode', 'KeyValue']
struct haxorg_LispCodeKeyValue {
  haxorg_LispCodeKeyValue_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'LispCode', 'Number']
struct haxorg_LispCodeNumber {
  haxorg_LispCodeNumber_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'LispCode', 'Text']
struct haxorg_LispCodeText {
  haxorg_LispCodeText_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'LispCode', 'Ident']
struct haxorg_LispCodeIdent {
  haxorg_LispCodeIdent_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'LispCode', 'Boolean']
struct haxorg_LispCodeBoolean {
  haxorg_LispCodeBoolean_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'LispCode', 'Real']
struct haxorg_LispCodeReal {
  haxorg_LispCodeReal_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_LispCode_vtable {};

/// \brief ['org', 'sem', 'LispCode']
struct haxorg_LispCode {
  haxorg_LispCode_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr', 'AxisRef', 'Position', 'Index']
struct haxorg_TblfmExprAxisRefPositionIndex {
  haxorg_TblfmExprAxisRefPositionIndex_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr', 'AxisRef', 'Position', 'Name']
struct haxorg_TblfmExprAxisRefPositionName {
  haxorg_TblfmExprAxisRefPositionName_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_TblfmExprAxisRefPosition_vtable {};

/// \brief ['org', 'sem', 'Tblfm', 'Expr', 'AxisRef', 'Position']
struct haxorg_TblfmExprAxisRefPosition {
  haxorg_TblfmExprAxisRefPosition_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr', 'AxisRef']
struct haxorg_TblfmExprAxisRef {
  haxorg_TblfmExprAxisRef_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr', 'AxisName']
struct haxorg_TblfmExprAxisName {
  haxorg_TblfmExprAxisName_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr', 'IntLiteral']
struct haxorg_TblfmExprIntLiteral {
  haxorg_TblfmExprIntLiteral_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr', 'FloatLiteral']
struct haxorg_TblfmExprFloatLiteral {
  haxorg_TblfmExprFloatLiteral_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr', 'RangeRef']
struct haxorg_TblfmExprRangeRef {
  haxorg_TblfmExprRangeRef_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr', 'Call']
struct haxorg_TblfmExprCall {
  haxorg_TblfmExprCall_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr', 'Elisp']
struct haxorg_TblfmExprElisp {
  haxorg_TblfmExprElisp_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_TblfmExpr_vtable {};

/// \brief ['org', 'sem', 'Tblfm', 'Expr']
struct haxorg_TblfmExpr {
  haxorg_TblfmExpr_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Assign']
struct haxorg_TblfmAssign {
  haxorg_TblfmAssign_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm']
struct haxorg_Tblfm {
  haxorg_Tblfm_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'AttrValue', 'DimensionSpan']
struct haxorg_AttrValueDimensionSpan {
  haxorg_AttrValueDimensionSpan_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'AttrValue', 'TextValue']
struct haxorg_AttrValueTextValue {
  haxorg_AttrValueTextValue_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'AttrValue', 'FileReference']
struct haxorg_AttrValueFileReference {
  haxorg_AttrValueFileReference_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'AttrValue', 'LispValue']
struct haxorg_AttrValueLispValue {
  haxorg_AttrValueLispValue_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'AttrValue']
struct haxorg_AttrValue {
  haxorg_AttrValue_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'HashTagFlat']
struct haxorg_HashTagFlat {
  haxorg_HashTagFlat_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'TodoKeyword']
struct haxorg_TodoKeyword {
  haxorg_TodoKeyword_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'HashTagText']
struct haxorg_HashTagText {
  haxorg_HashTagText_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreePath']
struct haxorg_SubtreePath {
  haxorg_SubtreePath_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget', 'Raw']
struct haxorg_LinkTargetRaw {
  haxorg_LinkTargetRaw_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget', 'Id']
struct haxorg_LinkTargetId {
  haxorg_LinkTargetId_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget', 'CustomId']
struct haxorg_LinkTargetCustomId {
  haxorg_LinkTargetCustomId_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget', 'SubtreeTitle']
struct haxorg_LinkTargetSubtreeTitle {
  haxorg_LinkTargetSubtreeTitle_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget', 'Person']
struct haxorg_LinkTargetPerson {
  haxorg_LinkTargetPerson_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget', 'UserProtocol']
struct haxorg_LinkTargetUserProtocol {
  haxorg_LinkTargetUserProtocol_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget', 'Internal']
struct haxorg_LinkTargetInternal {
  haxorg_LinkTargetInternal_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget', 'Footnote']
struct haxorg_LinkTargetFootnote {
  haxorg_LinkTargetFootnote_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget', 'File']
struct haxorg_LinkTargetFile {
  haxorg_LinkTargetFile_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget', 'Attachment']
struct haxorg_LinkTargetAttachment {
  haxorg_LinkTargetAttachment_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_LinkTarget_vtable {};

/// \brief ['org', 'sem', 'LinkTarget']
struct haxorg_LinkTarget {
  haxorg_LinkTarget_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLogHead', 'Priority']
struct haxorg_SubtreeLogHeadPriority {
  haxorg_SubtreeLogHeadPriority_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLogHead', 'Note']
struct haxorg_SubtreeLogHeadNote {
  haxorg_SubtreeLogHeadNote_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLogHead', 'Refile']
struct haxorg_SubtreeLogHeadRefile {
  haxorg_SubtreeLogHeadRefile_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLogHead', 'Clock']
struct haxorg_SubtreeLogHeadClock {
  haxorg_SubtreeLogHeadClock_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLogHead', 'State']
struct haxorg_SubtreeLogHeadState {
  haxorg_SubtreeLogHeadState_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLogHead', 'Deadline']
struct haxorg_SubtreeLogHeadDeadline {
  haxorg_SubtreeLogHeadDeadline_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLogHead', 'Schedule']
struct haxorg_SubtreeLogHeadSchedule {
  haxorg_SubtreeLogHeadSchedule_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLogHead', 'Tag']
struct haxorg_SubtreeLogHeadTag {
  haxorg_SubtreeLogHeadTag_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_SubtreeLogHeadUnknown_vtable {};

/// \brief ['org', 'sem', 'SubtreeLogHead', 'Unknown']
struct haxorg_SubtreeLogHeadUnknown {
  haxorg_SubtreeLogHeadUnknown_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_SubtreeLogHead_vtable {};

/// \brief ['org', 'sem', 'SubtreeLogHead']
struct haxorg_SubtreeLogHead {
  haxorg_SubtreeLogHead_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeCompletion']
struct haxorg_SubtreeCompletion {
  haxorg_SubtreeCompletion_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'AttrList']
struct haxorg_AttrList {
  haxorg_AttrList_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'AttrGroup']
struct haxorg_AttrGroup {
  haxorg_AttrGroup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'OrgCodeEvalInput', 'Var']
struct haxorg_OrgCodeEvalInputVar {
  haxorg_OrgCodeEvalInputVar_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'OrgCodeEvalInput']
struct haxorg_OrgCodeEvalInput {
  haxorg_OrgCodeEvalInput_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'OrgCodeEvalOutput']
struct haxorg_OrgCodeEvalOutput {
  haxorg_OrgCodeEvalOutput_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'ColumnView', 'Summary', 'CheckboxAggregate']
struct haxorg_ColumnViewSummaryCheckboxAggregate {
  haxorg_ColumnViewSummaryCheckboxAggregate_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'ColumnView', 'Summary', 'MathAggregate']
struct haxorg_ColumnViewSummaryMathAggregate {
  haxorg_ColumnViewSummaryMathAggregate_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ColumnViewSummary_vtable {};

/// \brief ['org', 'sem', 'ColumnView', 'Summary']
struct haxorg_ColumnViewSummary {
  haxorg_ColumnViewSummary_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'ColumnView', 'Column']
struct haxorg_ColumnViewColumn {
  haxorg_ColumnViewColumn_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'ColumnView']
struct haxorg_ColumnView {
  haxorg_ColumnView_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockCodeLine', 'Part', 'Raw']
struct haxorg_BlockCodeLinePartRaw {
  haxorg_BlockCodeLinePartRaw_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockCodeLine', 'Part', 'Callout']
struct haxorg_BlockCodeLinePartCallout {
  haxorg_BlockCodeLinePartCallout_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockCodeLine', 'Part', 'Tangle']
struct haxorg_BlockCodeLinePartTangle {
  haxorg_BlockCodeLinePartTangle_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_BlockCodeLinePart_vtable {};

/// \brief ['org', 'sem', 'BlockCodeLine', 'Part']
struct haxorg_BlockCodeLinePart {
  haxorg_BlockCodeLinePart_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockCodeLine']
struct haxorg_BlockCodeLine {
  haxorg_BlockCodeLine_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'DocumentExportConfig', 'TaskExport']
struct haxorg_DocumentExportConfigTaskExport {
  haxorg_DocumentExportConfigTaskExport_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'DocumentExportConfig', 'DoExport']
struct haxorg_DocumentExportConfigDoExport {
  haxorg_DocumentExportConfigDoExport_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'DocumentExportConfig', 'ExportFixed']
struct haxorg_DocumentExportConfigExportFixed {
  haxorg_DocumentExportConfigExportFixed_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'DocumentExportConfig']
struct haxorg_DocumentExportConfig {
  haxorg_DocumentExportConfig_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreePeriod']
struct haxorg_SubtreePeriod {
  haxorg_SubtreePeriod_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'Nonblocking']
struct haxorg_NamedPropertyNonblocking {
  haxorg_NamedPropertyNonblocking_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ArchiveTime']
struct haxorg_NamedPropertyArchiveTime {
  haxorg_NamedPropertyArchiveTime_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ArchiveFile']
struct haxorg_NamedPropertyArchiveFile {
  haxorg_NamedPropertyArchiveFile_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ArchiveOlpath']
struct haxorg_NamedPropertyArchiveOlpath {
  haxorg_NamedPropertyArchiveOlpath_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ArchiveTarget']
struct haxorg_NamedPropertyArchiveTarget {
  haxorg_NamedPropertyArchiveTarget_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ArchiveCategory']
struct haxorg_NamedPropertyArchiveCategory {
  haxorg_NamedPropertyArchiveCategory_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ArchiveTodo']
struct haxorg_NamedPropertyArchiveTodo {
  haxorg_NamedPropertyArchiveTodo_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_NamedPropertyTrigger_vtable {};

/// \brief ['org', 'sem', 'NamedProperty', 'Trigger']
struct haxorg_NamedPropertyTrigger {
  haxorg_NamedPropertyTrigger_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ExportLatexClass']
struct haxorg_NamedPropertyExportLatexClass {
  haxorg_NamedPropertyExportLatexClass_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'CookieData']
struct haxorg_NamedPropertyCookieData {
  haxorg_NamedPropertyCookieData_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ExportLatexClassOptions']
struct haxorg_NamedPropertyExportLatexClassOptions {
  haxorg_NamedPropertyExportLatexClassOptions_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ExportLatexHeader']
struct haxorg_NamedPropertyExportLatexHeader {
  haxorg_NamedPropertyExportLatexHeader_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ExportLatexCompiler']
struct haxorg_NamedPropertyExportLatexCompiler {
  haxorg_NamedPropertyExportLatexCompiler_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'Ordered']
struct haxorg_NamedPropertyOrdered {
  haxorg_NamedPropertyOrdered_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'Effort']
struct haxorg_NamedPropertyEffort {
  haxorg_NamedPropertyEffort_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'Visibility']
struct haxorg_NamedPropertyVisibility {
  haxorg_NamedPropertyVisibility_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ExportOptions']
struct haxorg_NamedPropertyExportOptions {
  haxorg_NamedPropertyExportOptions_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'Blocker']
struct haxorg_NamedPropertyBlocker {
  haxorg_NamedPropertyBlocker_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_NamedPropertyUnnumbered_vtable {};

/// \brief ['org', 'sem', 'NamedProperty', 'Unnumbered']
struct haxorg_NamedPropertyUnnumbered {
  haxorg_NamedPropertyUnnumbered_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'Created']
struct haxorg_NamedPropertyCreated {
  haxorg_NamedPropertyCreated_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'RadioId']
struct haxorg_NamedPropertyRadioId {
  haxorg_NamedPropertyRadioId_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'HashtagDef']
struct haxorg_NamedPropertyHashtagDef {
  haxorg_NamedPropertyHashtagDef_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'CustomArgs']
struct haxorg_NamedPropertyCustomArgs {
  haxorg_NamedPropertyCustomArgs_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'CustomRaw']
struct haxorg_NamedPropertyCustomRaw {
  haxorg_NamedPropertyCustomRaw_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'CustomId']
struct haxorg_NamedPropertyCustomId {
  haxorg_NamedPropertyCustomId_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'CustomSubtreeJson']
struct haxorg_NamedPropertyCustomSubtreeJson {
  haxorg_NamedPropertyCustomSubtreeJson_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'CustomSubtreeFlags']
struct haxorg_NamedPropertyCustomSubtreeFlags {
  haxorg_NamedPropertyCustomSubtreeFlags_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_NamedProperty_vtable {};

/// \brief ['org', 'sem', 'NamedProperty']
struct haxorg_NamedProperty {
  haxorg_NamedProperty_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'OrgDiagnostics', 'ParseTokenError']
struct haxorg_OrgDiagnosticsParseTokenError {
  haxorg_OrgDiagnosticsParseTokenError_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'OrgDiagnostics', 'ParseError']
struct haxorg_OrgDiagnosticsParseError {
  haxorg_OrgDiagnosticsParseError_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'OrgDiagnostics', 'IncludeError']
struct haxorg_OrgDiagnosticsIncludeError {
  haxorg_OrgDiagnosticsIncludeError_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'OrgDiagnostics', 'ConvertError']
struct haxorg_OrgDiagnosticsConvertError {
  haxorg_OrgDiagnosticsConvertError_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'OrgDiagnostics', 'InternalError']
struct haxorg_OrgDiagnosticsInternalError {
  haxorg_OrgDiagnosticsInternalError_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_OrgDiagnostics_vtable {};

/// \brief ['org', 'sem', 'OrgDiagnostics']
struct haxorg_OrgDiagnostics {
  haxorg_OrgDiagnostics_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_NoNode_vtable {};

/// \brief ['org', 'sem', 'NoNode']
struct haxorg_NoNode {
  haxorg_NoNode_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'ErrorItem']
struct haxorg_ErrorItem {
  haxorg_ErrorItem_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'ErrorGroup']
struct haxorg_ErrorGroup {
  haxorg_ErrorGroup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Stmt']
struct haxorg_Stmt {
  haxorg_Stmt_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_Inline_vtable {};

/// \brief ['org', 'sem', 'Inline']
struct haxorg_Inline {
  haxorg_Inline_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_StmtList_vtable {};

/// \brief ['org', 'sem', 'StmtList']
struct haxorg_StmtList {
  haxorg_StmtList_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_Empty_vtable {};

/// \brief ['org', 'sem', 'Empty']
struct haxorg_Empty {
  haxorg_Empty_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Leaf']
struct haxorg_Leaf {
  haxorg_Leaf_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Time', 'Repeat']
struct haxorg_TimeRepeat {
  haxorg_TimeRepeat_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Time', 'Static']
struct haxorg_TimeStatic {
  haxorg_TimeStatic_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Time', 'Dynamic']
struct haxorg_TimeDynamic {
  haxorg_TimeDynamic_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Time']
struct haxorg_Time {
  haxorg_Time_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'TimeRange']
struct haxorg_TimeRange {
  haxorg_TimeRange_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Macro']
struct haxorg_Macro {
  haxorg_Macro_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Symbol', 'Param']
struct haxorg_SymbolParam {
  haxorg_SymbolParam_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Symbol']
struct haxorg_Symbol {
  haxorg_Symbol_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'ErrorSkipGroup']
struct haxorg_ErrorSkipGroup {
  haxorg_ErrorSkipGroup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_Markup_vtable {};

/// \brief ['org', 'sem', 'Markup']
struct haxorg_Markup {
  haxorg_Markup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'RadioTarget']
struct haxorg_RadioTarget {
  haxorg_RadioTarget_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_Latex_vtable {};

/// \brief ['org', 'sem', 'Latex']
struct haxorg_Latex {
  haxorg_Latex_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLog']
struct haxorg_SubtreeLog {
  haxorg_SubtreeLog_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Subtree']
struct haxorg_Subtree {
  haxorg_Subtree_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ColonExample_vtable {};

/// \brief ['org', 'sem', 'ColonExample']
struct haxorg_ColonExample {
  haxorg_ColonExample_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Call']
struct haxorg_Call {
  haxorg_Call_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'ListItem']
struct haxorg_ListItem {
  haxorg_ListItem_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'DocumentOptions']
struct haxorg_DocumentOptions {
  haxorg_DocumentOptions_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'DocumentFragment']
struct haxorg_DocumentFragment {
  haxorg_DocumentFragment_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'CriticMarkup']
struct haxorg_CriticMarkup {
  haxorg_CriticMarkup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Document']
struct haxorg_Document {
  haxorg_Document_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'FileTarget']
struct haxorg_FileTarget {
  haxorg_FileTarget_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_TextSeparator_vtable {};

/// \brief ['org', 'sem', 'TextSeparator']
struct haxorg_TextSeparator {
  haxorg_TextSeparator_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_DocumentGroup_vtable {};

/// \brief ['org', 'sem', 'DocumentGroup']
struct haxorg_DocumentGroup {
  haxorg_DocumentGroup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_FileDocument_vtable {};

/// \brief ['org', 'sem', 'File', 'Document']
struct haxorg_FileDocument {
  haxorg_FileDocument_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_FileAttachment_vtable {};

/// \brief ['org', 'sem', 'File', 'Attachment']
struct haxorg_FileAttachment {
  haxorg_FileAttachment_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_FileSource_vtable {};

/// \brief ['org', 'sem', 'File', 'Source']
struct haxorg_FileSource {
  haxorg_FileSource_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'File']
struct haxorg_File {
  haxorg_File_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Directory']
struct haxorg_Directory {
  haxorg_Directory_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Symlink']
struct haxorg_Symlink {
  haxorg_Symlink_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_CmdIncludeIncludeBase_vtable {};

/// \brief ['org', 'sem', 'CmdInclude', 'IncludeBase']
struct haxorg_CmdIncludeIncludeBase {
  haxorg_CmdIncludeIncludeBase_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_CmdIncludeExample_vtable {};

/// \brief ['org', 'sem', 'CmdInclude', 'Example']
struct haxorg_CmdIncludeExample {
  haxorg_CmdIncludeExample_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdInclude', 'Export']
struct haxorg_CmdIncludeExport {
  haxorg_CmdIncludeExport_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdInclude', 'Custom']
struct haxorg_CmdIncludeCustom {
  haxorg_CmdIncludeCustom_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdInclude', 'Src']
struct haxorg_CmdIncludeSrc {
  haxorg_CmdIncludeSrc_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdInclude', 'OrgDocument']
struct haxorg_CmdIncludeOrgDocument {
  haxorg_CmdIncludeOrgDocument_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdInclude']
struct haxorg_CmdInclude {
  haxorg_CmdInclude_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmNoNode_vtable {};

/// \brief ['org', 'imm', 'ImmNoNode']
struct haxorg_ImmNoNode {
  haxorg_ImmNoNode_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmErrorItem']
struct haxorg_ImmErrorItem {
  haxorg_ImmErrorItem_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmErrorGroup']
struct haxorg_ImmErrorGroup {
  haxorg_ImmErrorGroup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmStmt']
struct haxorg_ImmStmt {
  haxorg_ImmStmt_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmInline_vtable {};

/// \brief ['org', 'imm', 'ImmInline']
struct haxorg_ImmInline {
  haxorg_ImmInline_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmStmtList_vtable {};

/// \brief ['org', 'imm', 'ImmStmtList']
struct haxorg_ImmStmtList {
  haxorg_ImmStmtList_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmEmpty_vtable {};

/// \brief ['org', 'imm', 'ImmEmpty']
struct haxorg_ImmEmpty {
  haxorg_ImmEmpty_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmLeaf']
struct haxorg_ImmLeaf {
  haxorg_ImmLeaf_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

typedef haxorg_TimeRepeatMode haxorg_ImmTimeRepeatMode;
typedef haxorg_TimeRepeatPeriod haxorg_ImmTimeRepeatPeriod;
/// \brief ['org', 'imm', 'ImmTime', 'Repeat']
struct haxorg_ImmTimeRepeat {
  haxorg_ImmTimeRepeat_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmTime', 'Static']
struct haxorg_ImmTimeStatic {
  haxorg_ImmTimeStatic_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmTime', 'Dynamic']
struct haxorg_ImmTimeDynamic {
  haxorg_ImmTimeDynamic_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmTime']
struct haxorg_ImmTime {
  haxorg_ImmTime_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmTimeRange']
struct haxorg_ImmTimeRange {
  haxorg_ImmTimeRange_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmMacro']
struct haxorg_ImmMacro {
  haxorg_ImmMacro_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmSymbol', 'Param']
struct haxorg_ImmSymbolParam {
  haxorg_ImmSymbolParam_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmSymbol']
struct haxorg_ImmSymbol {
  haxorg_ImmSymbol_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmErrorSkipGroup']
struct haxorg_ImmErrorSkipGroup {
  haxorg_ImmErrorSkipGroup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmMarkup_vtable {};

/// \brief ['org', 'imm', 'ImmMarkup']
struct haxorg_ImmMarkup {
  haxorg_ImmMarkup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmRadioTarget']
struct haxorg_ImmRadioTarget {
  haxorg_ImmRadioTarget_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmLatex_vtable {};

/// \brief ['org', 'imm', 'ImmLatex']
struct haxorg_ImmLatex {
  haxorg_ImmLatex_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmSubtreeLog']
struct haxorg_ImmSubtreeLog {
  haxorg_ImmSubtreeLog_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmSubtree']
struct haxorg_ImmSubtree {
  haxorg_ImmSubtree_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmColonExample_vtable {};

/// \brief ['org', 'imm', 'ImmColonExample']
struct haxorg_ImmColonExample {
  haxorg_ImmColonExample_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCall']
struct haxorg_ImmCall {
  haxorg_ImmCall_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmListItem']
struct haxorg_ImmListItem {
  haxorg_ImmListItem_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmDocumentOptions']
struct haxorg_ImmDocumentOptions {
  haxorg_ImmDocumentOptions_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmDocumentFragment']
struct haxorg_ImmDocumentFragment {
  haxorg_ImmDocumentFragment_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

typedef haxorg_CriticMarkupKind haxorg_ImmCriticMarkupKind;
/// \brief ['org', 'imm', 'ImmCriticMarkup']
struct haxorg_ImmCriticMarkup {
  haxorg_ImmCriticMarkup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmDocument']
struct haxorg_ImmDocument {
  haxorg_ImmDocument_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmFileTarget']
struct haxorg_ImmFileTarget {
  haxorg_ImmFileTarget_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmTextSeparator_vtable {};

/// \brief ['org', 'imm', 'ImmTextSeparator']
struct haxorg_ImmTextSeparator {
  haxorg_ImmTextSeparator_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmDocumentGroup_vtable {};

/// \brief ['org', 'imm', 'ImmDocumentGroup']
struct haxorg_ImmDocumentGroup {
  haxorg_ImmDocumentGroup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmFileDocument_vtable {};

/// \brief ['org', 'imm', 'ImmFile', 'Document']
struct haxorg_ImmFileDocument {
  haxorg_ImmFileDocument_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmFileAttachment_vtable {};

/// \brief ['org', 'imm', 'ImmFile', 'Attachment']
struct haxorg_ImmFileAttachment {
  haxorg_ImmFileAttachment_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmFileSource_vtable {};

/// \brief ['org', 'imm', 'ImmFile', 'Source']
struct haxorg_ImmFileSource {
  haxorg_ImmFileSource_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmFile']
struct haxorg_ImmFile {
  haxorg_ImmFile_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmDirectory']
struct haxorg_ImmDirectory {
  haxorg_ImmDirectory_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmSymlink']
struct haxorg_ImmSymlink {
  haxorg_ImmSymlink_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmCmdIncludeIncludeBase_vtable {};

/// \brief ['org', 'imm', 'ImmCmdInclude', 'IncludeBase']
struct haxorg_ImmCmdIncludeIncludeBase {
  haxorg_ImmCmdIncludeIncludeBase_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmCmdIncludeExample_vtable {};

/// \brief ['org', 'imm', 'ImmCmdInclude', 'Example']
struct haxorg_ImmCmdIncludeExample {
  haxorg_ImmCmdIncludeExample_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdInclude', 'Export']
struct haxorg_ImmCmdIncludeExport {
  haxorg_ImmCmdIncludeExport_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdInclude', 'Custom']
struct haxorg_ImmCmdIncludeCustom {
  haxorg_ImmCmdIncludeCustom_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdInclude', 'Src']
struct haxorg_ImmCmdIncludeSrc {
  haxorg_ImmCmdIncludeSrc_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdInclude', 'OrgDocument']
struct haxorg_ImmCmdIncludeOrgDocument {
  haxorg_ImmCmdIncludeOrgDocument_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdInclude']
struct haxorg_ImmCmdInclude {
  haxorg_ImmCmdInclude_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterOrgAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterOrgAPI']
struct haxorg_ImmAdapterOrgAPI {
  haxorg_ImmAdapterOrgAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Cmd']
struct haxorg_Cmd {
  haxorg_Cmd_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdCustomRaw']
struct haxorg_CmdCustomRaw {
  haxorg_CmdCustomRaw_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdCustomText']
struct haxorg_CmdCustomText {
  haxorg_CmdCustomText_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Link']
struct haxorg_Link {
  haxorg_Link_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_BlockComment_vtable {};

/// \brief ['org', 'sem', 'BlockComment']
struct haxorg_BlockComment {
  haxorg_BlockComment_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_Paragraph_vtable {};

/// \brief ['org', 'sem', 'Paragraph']
struct haxorg_Paragraph {
  haxorg_Paragraph_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_List_vtable {};

/// \brief ['org', 'sem', 'List']
struct haxorg_List {
  haxorg_List_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'HashTag']
struct haxorg_HashTag {
  haxorg_HashTag_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'InlineFootnote']
struct haxorg_InlineFootnote {
  haxorg_InlineFootnote_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'InlineExport']
struct haxorg_InlineExport {
  haxorg_InlineExport_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_Escaped_vtable {};

/// \brief ['org', 'sem', 'Escaped']
struct haxorg_Escaped {
  haxorg_Escaped_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_Newline_vtable {};

/// \brief ['org', 'sem', 'Newline']
struct haxorg_Newline {
  haxorg_Newline_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_Space_vtable {};

/// \brief ['org', 'sem', 'Space']
struct haxorg_Space {
  haxorg_Space_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_Word_vtable {};

/// \brief ['org', 'sem', 'Word']
struct haxorg_Word {
  haxorg_Word_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_AtMention_vtable {};

/// \brief ['org', 'sem', 'AtMention']
struct haxorg_AtMention {
  haxorg_AtMention_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_RawText_vtable {};

/// \brief ['org', 'sem', 'RawText']
struct haxorg_RawText {
  haxorg_RawText_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_Punctuation_vtable {};

/// \brief ['org', 'sem', 'Punctuation']
struct haxorg_Punctuation {
  haxorg_Punctuation_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_Placeholder_vtable {};

/// \brief ['org', 'sem', 'Placeholder']
struct haxorg_Placeholder {
  haxorg_Placeholder_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_BigIdent_vtable {};

/// \brief ['org', 'sem', 'BigIdent']
struct haxorg_BigIdent {
  haxorg_BigIdent_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_TextTarget_vtable {};

/// \brief ['org', 'sem', 'TextTarget']
struct haxorg_TextTarget {
  haxorg_TextTarget_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ErrorSkipToken_vtable {};

/// \brief ['org', 'sem', 'ErrorSkipToken']
struct haxorg_ErrorSkipToken {
  haxorg_ErrorSkipToken_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_Bold_vtable {};

/// \brief ['org', 'sem', 'Bold']
struct haxorg_Bold {
  haxorg_Bold_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_Underline_vtable {};

/// \brief ['org', 'sem', 'Underline']
struct haxorg_Underline {
  haxorg_Underline_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_Monospace_vtable {};

/// \brief ['org', 'sem', 'Monospace']
struct haxorg_Monospace {
  haxorg_Monospace_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_MarkQuote_vtable {};

/// \brief ['org', 'sem', 'MarkQuote']
struct haxorg_MarkQuote {
  haxorg_MarkQuote_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_Verbatim_vtable {};

/// \brief ['org', 'sem', 'Verbatim']
struct haxorg_Verbatim {
  haxorg_Verbatim_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_Italic_vtable {};

/// \brief ['org', 'sem', 'Italic']
struct haxorg_Italic {
  haxorg_Italic_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_Strike_vtable {};

/// \brief ['org', 'sem', 'Strike']
struct haxorg_Strike {
  haxorg_Strike_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_Par_vtable {};

/// \brief ['org', 'sem', 'Par']
struct haxorg_Par {
  haxorg_Par_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmd']
struct haxorg_ImmCmd {
  haxorg_ImmCmd_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdCustomRaw']
struct haxorg_ImmCmdCustomRaw {
  haxorg_ImmCmdCustomRaw_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdCustomText']
struct haxorg_ImmCmdCustomText {
  haxorg_ImmCmdCustomText_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmLink']
struct haxorg_ImmLink {
  haxorg_ImmLink_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmBlockComment_vtable {};

/// \brief ['org', 'imm', 'ImmBlockComment']
struct haxorg_ImmBlockComment {
  haxorg_ImmBlockComment_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmParagraph_vtable {};

/// \brief ['org', 'imm', 'ImmParagraph']
struct haxorg_ImmParagraph {
  haxorg_ImmParagraph_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmList_vtable {};

/// \brief ['org', 'imm', 'ImmList']
struct haxorg_ImmList {
  haxorg_ImmList_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmHashTag']
struct haxorg_ImmHashTag {
  haxorg_ImmHashTag_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmInlineFootnote']
struct haxorg_ImmInlineFootnote {
  haxorg_ImmInlineFootnote_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmInlineExport']
struct haxorg_ImmInlineExport {
  haxorg_ImmInlineExport_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmEscaped_vtable {};

/// \brief ['org', 'imm', 'ImmEscaped']
struct haxorg_ImmEscaped {
  haxorg_ImmEscaped_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmNewline_vtable {};

/// \brief ['org', 'imm', 'ImmNewline']
struct haxorg_ImmNewline {
  haxorg_ImmNewline_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmSpace_vtable {};

/// \brief ['org', 'imm', 'ImmSpace']
struct haxorg_ImmSpace {
  haxorg_ImmSpace_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmWord_vtable {};

/// \brief ['org', 'imm', 'ImmWord']
struct haxorg_ImmWord {
  haxorg_ImmWord_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAtMention_vtable {};

/// \brief ['org', 'imm', 'ImmAtMention']
struct haxorg_ImmAtMention {
  haxorg_ImmAtMention_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmRawText_vtable {};

/// \brief ['org', 'imm', 'ImmRawText']
struct haxorg_ImmRawText {
  haxorg_ImmRawText_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmPunctuation_vtable {};

/// \brief ['org', 'imm', 'ImmPunctuation']
struct haxorg_ImmPunctuation {
  haxorg_ImmPunctuation_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmPlaceholder_vtable {};

/// \brief ['org', 'imm', 'ImmPlaceholder']
struct haxorg_ImmPlaceholder {
  haxorg_ImmPlaceholder_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmBigIdent_vtable {};

/// \brief ['org', 'imm', 'ImmBigIdent']
struct haxorg_ImmBigIdent {
  haxorg_ImmBigIdent_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmTextTarget_vtable {};

/// \brief ['org', 'imm', 'ImmTextTarget']
struct haxorg_ImmTextTarget {
  haxorg_ImmTextTarget_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmErrorSkipToken_vtable {};

/// \brief ['org', 'imm', 'ImmErrorSkipToken']
struct haxorg_ImmErrorSkipToken {
  haxorg_ImmErrorSkipToken_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmBold_vtable {};

/// \brief ['org', 'imm', 'ImmBold']
struct haxorg_ImmBold {
  haxorg_ImmBold_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmUnderline_vtable {};

/// \brief ['org', 'imm', 'ImmUnderline']
struct haxorg_ImmUnderline {
  haxorg_ImmUnderline_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmMonospace_vtable {};

/// \brief ['org', 'imm', 'ImmMonospace']
struct haxorg_ImmMonospace {
  haxorg_ImmMonospace_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmMarkQuote_vtable {};

/// \brief ['org', 'imm', 'ImmMarkQuote']
struct haxorg_ImmMarkQuote {
  haxorg_ImmMarkQuote_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmVerbatim_vtable {};

/// \brief ['org', 'imm', 'ImmVerbatim']
struct haxorg_ImmVerbatim {
  haxorg_ImmVerbatim_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmItalic_vtable {};

/// \brief ['org', 'imm', 'ImmItalic']
struct haxorg_ImmItalic {
  haxorg_ImmItalic_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmStrike_vtable {};

/// \brief ['org', 'imm', 'ImmStrike']
struct haxorg_ImmStrike {
  haxorg_ImmStrike_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmPar_vtable {};

/// \brief ['org', 'imm', 'ImmPar']
struct haxorg_ImmPar {
  haxorg_ImmPar_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterStmtAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterStmtAPI']
struct haxorg_ImmAdapterStmtAPI {
  haxorg_ImmAdapterStmtAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterSubtreeAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterSubtreeAPI']
struct haxorg_ImmAdapterSubtreeAPI {
  haxorg_ImmAdapterSubtreeAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterNoNodeAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterNoNodeAPI']
struct haxorg_ImmAdapterNoNodeAPI {
  haxorg_ImmAdapterNoNodeAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterAttrAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterAttrAPI']
struct haxorg_ImmAdapterAttrAPI {
  haxorg_ImmAdapterAttrAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterAttrListAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterAttrListAPI']
struct haxorg_ImmAdapterAttrListAPI {
  haxorg_ImmAdapterAttrListAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterAttrsAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterAttrsAPI']
struct haxorg_ImmAdapterAttrsAPI {
  haxorg_ImmAdapterAttrsAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterErrorItemAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterErrorItemAPI']
struct haxorg_ImmAdapterErrorItemAPI {
  haxorg_ImmAdapterErrorItemAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterErrorGroupAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterErrorGroupAPI']
struct haxorg_ImmAdapterErrorGroupAPI {
  haxorg_ImmAdapterErrorGroupAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterErrorSkipGroupAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterErrorSkipGroupAPI']
struct haxorg_ImmAdapterErrorSkipGroupAPI {
  haxorg_ImmAdapterErrorSkipGroupAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterErrorSkipTokenAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterErrorSkipTokenAPI']
struct haxorg_ImmAdapterErrorSkipTokenAPI {
  haxorg_ImmAdapterErrorSkipTokenAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterStmtListAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterStmtListAPI']
struct haxorg_ImmAdapterStmtListAPI {
  haxorg_ImmAdapterStmtListAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterEmptyAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterEmptyAPI']
struct haxorg_ImmAdapterEmptyAPI {
  haxorg_ImmAdapterEmptyAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterInlineAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterInlineAPI']
struct haxorg_ImmAdapterInlineAPI {
  haxorg_ImmAdapterInlineAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterTimeAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterTimeAPI']
struct haxorg_ImmAdapterTimeAPI {
  haxorg_ImmAdapterTimeAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterTimeRangeAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterTimeRangeAPI']
struct haxorg_ImmAdapterTimeRangeAPI {
  haxorg_ImmAdapterTimeRangeAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterMacroAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterMacroAPI']
struct haxorg_ImmAdapterMacroAPI {
  haxorg_ImmAdapterMacroAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterSymbolAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterSymbolAPI']
struct haxorg_ImmAdapterSymbolAPI {
  haxorg_ImmAdapterSymbolAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterLeafAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterLeafAPI']
struct haxorg_ImmAdapterLeafAPI {
  haxorg_ImmAdapterLeafAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterMarkupAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterMarkupAPI']
struct haxorg_ImmAdapterMarkupAPI {
  haxorg_ImmAdapterMarkupAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterLatexAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterLatexAPI']
struct haxorg_ImmAdapterLatexAPI {
  haxorg_ImmAdapterLatexAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterSubtreeLogAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterSubtreeLogAPI']
struct haxorg_ImmAdapterSubtreeLogAPI {
  haxorg_ImmAdapterSubtreeLogAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterColonExampleAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterColonExampleAPI']
struct haxorg_ImmAdapterColonExampleAPI {
  haxorg_ImmAdapterColonExampleAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterCallAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCallAPI']
struct haxorg_ImmAdapterCallAPI {
  haxorg_ImmAdapterCallAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterFileAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterFileAPI']
struct haxorg_ImmAdapterFileAPI {
  haxorg_ImmAdapterFileAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterDirectoryAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterDirectoryAPI']
struct haxorg_ImmAdapterDirectoryAPI {
  haxorg_ImmAdapterDirectoryAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterSymlinkAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterSymlinkAPI']
struct haxorg_ImmAdapterSymlinkAPI {
  haxorg_ImmAdapterSymlinkAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterDocumentFragmentAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterDocumentFragmentAPI']
struct haxorg_ImmAdapterDocumentFragmentAPI {
  haxorg_ImmAdapterDocumentFragmentAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterCriticMarkupAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCriticMarkupAPI']
struct haxorg_ImmAdapterCriticMarkupAPI {
  haxorg_ImmAdapterCriticMarkupAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterListItemAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterListItemAPI']
struct haxorg_ImmAdapterListItemAPI {
  haxorg_ImmAdapterListItemAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterDocumentOptionsAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterDocumentOptionsAPI']
struct haxorg_ImmAdapterDocumentOptionsAPI {
  haxorg_ImmAdapterDocumentOptionsAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterDocumentAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterDocumentAPI']
struct haxorg_ImmAdapterDocumentAPI {
  haxorg_ImmAdapterDocumentAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterFileTargetAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterFileTargetAPI']
struct haxorg_ImmAdapterFileTargetAPI {
  haxorg_ImmAdapterFileTargetAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterTextSeparatorAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterTextSeparatorAPI']
struct haxorg_ImmAdapterTextSeparatorAPI {
  haxorg_ImmAdapterTextSeparatorAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterCmdIncludeAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdIncludeAPI']
struct haxorg_ImmAdapterCmdIncludeAPI {
  haxorg_ImmAdapterCmdIncludeAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterDocumentGroupAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterDocumentGroupAPI']
struct haxorg_ImmAdapterDocumentGroupAPI {
  haxorg_ImmAdapterDocumentGroupAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_Block_vtable {};

/// \brief ['org', 'sem', 'Block']
struct haxorg_Block {
  haxorg_Block_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_LineCommand_vtable {};

/// \brief ['org', 'sem', 'LineCommand']
struct haxorg_LineCommand {
  haxorg_LineCommand_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdCreator']
struct haxorg_CmdCreator {
  haxorg_CmdCreator_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdAuthor']
struct haxorg_CmdAuthor {
  haxorg_CmdAuthor_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdEmail']
struct haxorg_CmdEmail {
  haxorg_CmdEmail_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdLanguage']
struct haxorg_CmdLanguage {
  haxorg_CmdLanguage_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdCustomArgs']
struct haxorg_CmdCustomArgs {
  haxorg_CmdCustomArgs_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdTblfm']
struct haxorg_CmdTblfm {
  haxorg_CmdTblfm_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Cell']
struct haxorg_Cell {
  haxorg_Cell_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Row']
struct haxorg_Row {
  haxorg_Row_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmBlock_vtable {};

/// \brief ['org', 'imm', 'ImmBlock']
struct haxorg_ImmBlock {
  haxorg_ImmBlock_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmLineCommand_vtable {};

/// \brief ['org', 'imm', 'ImmLineCommand']
struct haxorg_ImmLineCommand {
  haxorg_ImmLineCommand_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdCreator']
struct haxorg_ImmCmdCreator {
  haxorg_ImmCmdCreator_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdAuthor']
struct haxorg_ImmCmdAuthor {
  haxorg_ImmCmdAuthor_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdEmail']
struct haxorg_ImmCmdEmail {
  haxorg_ImmCmdEmail_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdLanguage']
struct haxorg_ImmCmdLanguage {
  haxorg_ImmCmdLanguage_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdCustomArgs']
struct haxorg_ImmCmdCustomArgs {
  haxorg_ImmCmdCustomArgs_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdTblfm']
struct haxorg_ImmCmdTblfm {
  haxorg_ImmCmdTblfm_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCell']
struct haxorg_ImmCell {
  haxorg_ImmCell_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmRow']
struct haxorg_ImmRow {
  haxorg_ImmRow_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterCmdAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdAPI']
struct haxorg_ImmAdapterCmdAPI {
  haxorg_ImmAdapterCmdAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterCmdCustomRawAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdCustomRawAPI']
struct haxorg_ImmAdapterCmdCustomRawAPI {
  haxorg_ImmAdapterCmdCustomRawAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterCmdCustomTextAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdCustomTextAPI']
struct haxorg_ImmAdapterCmdCustomTextAPI {
  haxorg_ImmAdapterCmdCustomTextAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterLinkAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterLinkAPI']
struct haxorg_ImmAdapterLinkAPI {
  haxorg_ImmAdapterLinkAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterBlockCommentAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterBlockCommentAPI']
struct haxorg_ImmAdapterBlockCommentAPI {
  haxorg_ImmAdapterBlockCommentAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterParagraphAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterParagraphAPI']
struct haxorg_ImmAdapterParagraphAPI {
  haxorg_ImmAdapterParagraphAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterListAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterListAPI']
struct haxorg_ImmAdapterListAPI {
  haxorg_ImmAdapterListAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmStmtAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmStmt']]]
struct haxorg_ImmStmtAdapter {
  haxorg_ImmStmtAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmSubtreeAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmSubtree']]]
struct haxorg_ImmSubtreeAdapter {
  haxorg_ImmSubtreeAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmNoNodeAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmNoNode']]]
struct haxorg_ImmNoNodeAdapter {
  haxorg_ImmNoNodeAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmErrorItemAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmErrorItem']]]
struct haxorg_ImmErrorItemAdapter {
  haxorg_ImmErrorItemAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmErrorGroupAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmErrorGroup']]]
struct haxorg_ImmErrorGroupAdapter {
  haxorg_ImmErrorGroupAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmErrorSkipGroupAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmErrorSkipGroup']]]
struct haxorg_ImmErrorSkipGroupAdapter {
  haxorg_ImmErrorSkipGroupAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmErrorSkipTokenAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmErrorSkipToken']]]
struct haxorg_ImmErrorSkipTokenAdapter {
  haxorg_ImmErrorSkipTokenAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmStmtListAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmStmtList']]]
struct haxorg_ImmStmtListAdapter {
  haxorg_ImmStmtListAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmEmptyAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmEmpty']]]
struct haxorg_ImmEmptyAdapter {
  haxorg_ImmEmptyAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterHashTagAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterHashTagAPI']
struct haxorg_ImmAdapterHashTagAPI {
  haxorg_ImmAdapterHashTagAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterInlineFootnoteAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterInlineFootnoteAPI']
struct haxorg_ImmAdapterInlineFootnoteAPI {
  haxorg_ImmAdapterInlineFootnoteAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterSubtreeCompletionAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterSubtreeCompletionAPI']
struct haxorg_ImmAdapterSubtreeCompletionAPI {
  haxorg_ImmAdapterSubtreeCompletionAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmInlineAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmInline']]]
struct haxorg_ImmInlineAdapter {
  haxorg_ImmInlineAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmTimeAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmTime']]]
struct haxorg_ImmTimeAdapter {
  haxorg_ImmTimeAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmTimeRangeAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmTimeRange']]]
struct haxorg_ImmTimeRangeAdapter {
  haxorg_ImmTimeRangeAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmMacroAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmMacro']]]
struct haxorg_ImmMacroAdapter {
  haxorg_ImmMacroAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmSymbolAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmSymbol']]]
struct haxorg_ImmSymbolAdapter {
  haxorg_ImmSymbolAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterEscapedAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterEscapedAPI']
struct haxorg_ImmAdapterEscapedAPI {
  haxorg_ImmAdapterEscapedAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterNewlineAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterNewlineAPI']
struct haxorg_ImmAdapterNewlineAPI {
  haxorg_ImmAdapterNewlineAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterSpaceAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterSpaceAPI']
struct haxorg_ImmAdapterSpaceAPI {
  haxorg_ImmAdapterSpaceAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterWordAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterWordAPI']
struct haxorg_ImmAdapterWordAPI {
  haxorg_ImmAdapterWordAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterAtMentionAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterAtMentionAPI']
struct haxorg_ImmAdapterAtMentionAPI {
  haxorg_ImmAdapterAtMentionAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterRawTextAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterRawTextAPI']
struct haxorg_ImmAdapterRawTextAPI {
  haxorg_ImmAdapterRawTextAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterPunctuationAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterPunctuationAPI']
struct haxorg_ImmAdapterPunctuationAPI {
  haxorg_ImmAdapterPunctuationAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterPlaceholderAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterPlaceholderAPI']
struct haxorg_ImmAdapterPlaceholderAPI {
  haxorg_ImmAdapterPlaceholderAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterBigIdentAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterBigIdentAPI']
struct haxorg_ImmAdapterBigIdentAPI {
  haxorg_ImmAdapterBigIdentAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterTextTargetAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterTextTargetAPI']
struct haxorg_ImmAdapterTextTargetAPI {
  haxorg_ImmAdapterTextTargetAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmLeafAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmLeaf']]]
struct haxorg_ImmLeafAdapter {
  haxorg_ImmLeafAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterBoldAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterBoldAPI']
struct haxorg_ImmAdapterBoldAPI {
  haxorg_ImmAdapterBoldAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterUnderlineAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterUnderlineAPI']
struct haxorg_ImmAdapterUnderlineAPI {
  haxorg_ImmAdapterUnderlineAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterMonospaceAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterMonospaceAPI']
struct haxorg_ImmAdapterMonospaceAPI {
  haxorg_ImmAdapterMonospaceAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterMarkQuoteAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterMarkQuoteAPI']
struct haxorg_ImmAdapterMarkQuoteAPI {
  haxorg_ImmAdapterMarkQuoteAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterRadioTargetAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterRadioTargetAPI']
struct haxorg_ImmAdapterRadioTargetAPI {
  haxorg_ImmAdapterRadioTargetAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterVerbatimAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterVerbatimAPI']
struct haxorg_ImmAdapterVerbatimAPI {
  haxorg_ImmAdapterVerbatimAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterItalicAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterItalicAPI']
struct haxorg_ImmAdapterItalicAPI {
  haxorg_ImmAdapterItalicAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterStrikeAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterStrikeAPI']
struct haxorg_ImmAdapterStrikeAPI {
  haxorg_ImmAdapterStrikeAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterParAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterParAPI']
struct haxorg_ImmAdapterParAPI {
  haxorg_ImmAdapterParAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmMarkupAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmMarkup']]]
struct haxorg_ImmMarkupAdapter {
  haxorg_ImmMarkupAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmLatexAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmLatex']]]
struct haxorg_ImmLatexAdapter {
  haxorg_ImmLatexAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmSubtreeLogAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmSubtreeLog']]]
struct haxorg_ImmSubtreeLogAdapter {
  haxorg_ImmSubtreeLogAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmColonExampleAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmColonExample']]]
struct haxorg_ImmColonExampleAdapter {
  haxorg_ImmColonExampleAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmCallAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCall']]]
struct haxorg_ImmCallAdapter {
  haxorg_ImmCallAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmFileAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmFile']]]
struct haxorg_ImmFileAdapter {
  haxorg_ImmFileAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmDirectoryAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmDirectory']]]
struct haxorg_ImmDirectoryAdapter {
  haxorg_ImmDirectoryAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmSymlinkAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmSymlink']]]
struct haxorg_ImmSymlinkAdapter {
  haxorg_ImmSymlinkAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmDocumentFragmentAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmDocumentFragment']]]
struct haxorg_ImmDocumentFragmentAdapter {
  haxorg_ImmDocumentFragmentAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmCriticMarkupAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCriticMarkup']]]
struct haxorg_ImmCriticMarkupAdapter {
  haxorg_ImmCriticMarkupAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmListItemAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmListItem']]]
struct haxorg_ImmListItemAdapter {
  haxorg_ImmListItemAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmDocumentOptionsAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmDocumentOptions']]]
struct haxorg_ImmDocumentOptionsAdapter {
  haxorg_ImmDocumentOptionsAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmDocumentAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmDocument']]]
struct haxorg_ImmDocumentAdapter {
  haxorg_ImmDocumentAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmFileTargetAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmFileTarget']]]
struct haxorg_ImmFileTargetAdapter {
  haxorg_ImmFileTargetAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmTextSeparatorAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmTextSeparator']]]
struct haxorg_ImmTextSeparatorAdapter {
  haxorg_ImmTextSeparatorAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmCmdIncludeAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdInclude']]]
struct haxorg_ImmCmdIncludeAdapter {
  haxorg_ImmCmdIncludeAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmDocumentGroupAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmDocumentGroup']]]
struct haxorg_ImmDocumentGroupAdapter {
  haxorg_ImmDocumentGroupAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_BlockCenter_vtable {};

/// \brief ['org', 'sem', 'BlockCenter']
struct haxorg_BlockCenter {
  haxorg_BlockCenter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_BlockQuote_vtable {};

/// \brief ['org', 'sem', 'BlockQuote']
struct haxorg_BlockQuote {
  haxorg_BlockQuote_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_BlockVerse_vtable {};

/// \brief ['org', 'sem', 'BlockVerse']
struct haxorg_BlockVerse {
  haxorg_BlockVerse_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockDynamicFallback']
struct haxorg_BlockDynamicFallback {
  haxorg_BlockDynamicFallback_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_BlockExample_vtable {};

/// \brief ['org', 'sem', 'BlockExample']
struct haxorg_BlockExample {
  haxorg_BlockExample_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockExport']
struct haxorg_BlockExport {
  haxorg_BlockExport_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_BlockAdmonition_vtable {};

/// \brief ['org', 'sem', 'BlockAdmonition']
struct haxorg_BlockAdmonition {
  haxorg_BlockAdmonition_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockCodeEvalResult']
struct haxorg_BlockCodeEvalResult {
  haxorg_BlockCodeEvalResult_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockCode']
struct haxorg_BlockCode {
  haxorg_BlockCode_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'Table']
struct haxorg_Table {
  haxorg_Table_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_Attached_vtable {};

/// \brief ['org', 'sem', 'Attached']
struct haxorg_Attached {
  haxorg_Attached_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmBlockCenter_vtable {};

/// \brief ['org', 'imm', 'ImmBlockCenter']
struct haxorg_ImmBlockCenter {
  haxorg_ImmBlockCenter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmBlockQuote_vtable {};

/// \brief ['org', 'imm', 'ImmBlockQuote']
struct haxorg_ImmBlockQuote {
  haxorg_ImmBlockQuote_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmBlockVerse_vtable {};

/// \brief ['org', 'imm', 'ImmBlockVerse']
struct haxorg_ImmBlockVerse {
  haxorg_ImmBlockVerse_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmBlockDynamicFallback']
struct haxorg_ImmBlockDynamicFallback {
  haxorg_ImmBlockDynamicFallback_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmBlockExample_vtable {};

/// \brief ['org', 'imm', 'ImmBlockExample']
struct haxorg_ImmBlockExample {
  haxorg_ImmBlockExample_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmBlockExport']
struct haxorg_ImmBlockExport {
  haxorg_ImmBlockExport_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmBlockAdmonition_vtable {};

/// \brief ['org', 'imm', 'ImmBlockAdmonition']
struct haxorg_ImmBlockAdmonition {
  haxorg_ImmBlockAdmonition_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmBlockCodeEvalResult']
struct haxorg_ImmBlockCodeEvalResult {
  haxorg_ImmBlockCodeEvalResult_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmBlockCode']
struct haxorg_ImmBlockCode {
  haxorg_ImmBlockCode_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmTable']
struct haxorg_ImmTable {
  haxorg_ImmTable_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAttached_vtable {};

/// \brief ['org', 'imm', 'ImmAttached']
struct haxorg_ImmAttached {
  haxorg_ImmAttached_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterLineCommandAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterLineCommandAPI']
struct haxorg_ImmAdapterLineCommandAPI {
  haxorg_ImmAdapterLineCommandAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterCmdCustomArgsAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdCustomArgsAPI']
struct haxorg_ImmAdapterCmdCustomArgsAPI {
  haxorg_ImmAdapterCmdCustomArgsAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterCmdCreatorAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdCreatorAPI']
struct haxorg_ImmAdapterCmdCreatorAPI {
  haxorg_ImmAdapterCmdCreatorAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterCmdAuthorAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdAuthorAPI']
struct haxorg_ImmAdapterCmdAuthorAPI {
  haxorg_ImmAdapterCmdAuthorAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterCmdEmailAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdEmailAPI']
struct haxorg_ImmAdapterCmdEmailAPI {
  haxorg_ImmAdapterCmdEmailAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterCmdLanguageAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdLanguageAPI']
struct haxorg_ImmAdapterCmdLanguageAPI {
  haxorg_ImmAdapterCmdLanguageAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterCmdTblfmAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdTblfmAPI']
struct haxorg_ImmAdapterCmdTblfmAPI {
  haxorg_ImmAdapterCmdTblfmAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterBlockAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterBlockAPI']
struct haxorg_ImmAdapterBlockAPI {
  haxorg_ImmAdapterBlockAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterCellAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCellAPI']
struct haxorg_ImmAdapterCellAPI {
  haxorg_ImmAdapterCellAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterRowAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterRowAPI']
struct haxorg_ImmAdapterRowAPI {
  haxorg_ImmAdapterRowAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmCmdAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmd']]]
struct haxorg_ImmCmdAdapter {
  haxorg_ImmCmdAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmCmdCustomRawAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdCustomRaw']]]
struct haxorg_ImmCmdCustomRawAdapter {
  haxorg_ImmCmdCustomRawAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmCmdCustomTextAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdCustomText']]]
struct haxorg_ImmCmdCustomTextAdapter {
  haxorg_ImmCmdCustomTextAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmLinkAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmLink']]]
struct haxorg_ImmLinkAdapter {
  haxorg_ImmLinkAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmBlockCommentAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlockComment']]]
struct haxorg_ImmBlockCommentAdapter {
  haxorg_ImmBlockCommentAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmParagraphAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmParagraph']]]
struct haxorg_ImmParagraphAdapter {
  haxorg_ImmParagraphAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmListAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmList']]]
struct haxorg_ImmListAdapter {
  haxorg_ImmListAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmHashTagAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmHashTag']]]
struct haxorg_ImmHashTagAdapter {
  haxorg_ImmHashTagAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmInlineFootnoteAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmInlineFootnote']]]
struct haxorg_ImmInlineFootnoteAdapter {
  haxorg_ImmInlineFootnoteAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmEscapedAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmEscaped']]]
struct haxorg_ImmEscapedAdapter {
  haxorg_ImmEscapedAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmNewlineAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmNewline']]]
struct haxorg_ImmNewlineAdapter {
  haxorg_ImmNewlineAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmSpaceAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmSpace']]]
struct haxorg_ImmSpaceAdapter {
  haxorg_ImmSpaceAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmWordAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmWord']]]
struct haxorg_ImmWordAdapter {
  haxorg_ImmWordAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAtMentionAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmAtMention']]]
struct haxorg_ImmAtMentionAdapter {
  haxorg_ImmAtMentionAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmRawTextAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmRawText']]]
struct haxorg_ImmRawTextAdapter {
  haxorg_ImmRawTextAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmPunctuationAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmPunctuation']]]
struct haxorg_ImmPunctuationAdapter {
  haxorg_ImmPunctuationAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmPlaceholderAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmPlaceholder']]]
struct haxorg_ImmPlaceholderAdapter {
  haxorg_ImmPlaceholderAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmBigIdentAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBigIdent']]]
struct haxorg_ImmBigIdentAdapter {
  haxorg_ImmBigIdentAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmTextTargetAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmTextTarget']]]
struct haxorg_ImmTextTargetAdapter {
  haxorg_ImmTextTargetAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmBoldAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBold']]]
struct haxorg_ImmBoldAdapter {
  haxorg_ImmBoldAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmUnderlineAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmUnderline']]]
struct haxorg_ImmUnderlineAdapter {
  haxorg_ImmUnderlineAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmMonospaceAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmMonospace']]]
struct haxorg_ImmMonospaceAdapter {
  haxorg_ImmMonospaceAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmMarkQuoteAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmMarkQuote']]]
struct haxorg_ImmMarkQuoteAdapter {
  haxorg_ImmMarkQuoteAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmRadioTargetAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmRadioTarget']]]
struct haxorg_ImmRadioTargetAdapter {
  haxorg_ImmRadioTargetAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmVerbatimAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmVerbatim']]]
struct haxorg_ImmVerbatimAdapter {
  haxorg_ImmVerbatimAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmItalicAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmItalic']]]
struct haxorg_ImmItalicAdapter {
  haxorg_ImmItalicAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmStrikeAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmStrike']]]
struct haxorg_ImmStrikeAdapter {
  haxorg_ImmStrikeAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmParAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmPar']]]
struct haxorg_ImmParAdapter {
  haxorg_ImmParAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdCaption']
struct haxorg_CmdCaption {
  haxorg_CmdCaption_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdColumns']
struct haxorg_CmdColumns {
  haxorg_CmdColumns_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdName']
struct haxorg_CmdName {
  haxorg_CmdName_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdCall']
struct haxorg_CmdCall {
  haxorg_CmdCall_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdAttr']
struct haxorg_CmdAttr {
  haxorg_CmdAttr_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdExport']
struct haxorg_CmdExport {
  haxorg_CmdExport_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdCaption']
struct haxorg_ImmCmdCaption {
  haxorg_ImmCmdCaption_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdColumns']
struct haxorg_ImmCmdColumns {
  haxorg_ImmCmdColumns_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdName']
struct haxorg_ImmCmdName {
  haxorg_ImmCmdName_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdCall']
struct haxorg_ImmCmdCall {
  haxorg_ImmCmdCall_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdAttr']
struct haxorg_ImmCmdAttr {
  haxorg_ImmCmdAttr_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdExport']
struct haxorg_ImmCmdExport {
  haxorg_ImmCmdExport_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterAttachedAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterAttachedAPI']
struct haxorg_ImmAdapterAttachedAPI {
  haxorg_ImmAdapterAttachedAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmLineCommandAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmLineCommand']]]
struct haxorg_ImmLineCommandAdapter {
  haxorg_ImmLineCommandAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmCmdCustomArgsAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdCustomArgs']]]
struct haxorg_ImmCmdCustomArgsAdapter {
  haxorg_ImmCmdCustomArgsAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmCmdCreatorAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdCreator']]]
struct haxorg_ImmCmdCreatorAdapter {
  haxorg_ImmCmdCreatorAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmCmdAuthorAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdAuthor']]]
struct haxorg_ImmCmdAuthorAdapter {
  haxorg_ImmCmdAuthorAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmCmdEmailAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdEmail']]]
struct haxorg_ImmCmdEmailAdapter {
  haxorg_ImmCmdEmailAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmCmdLanguageAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdLanguage']]]
struct haxorg_ImmCmdLanguageAdapter {
  haxorg_ImmCmdLanguageAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmCmdTblfmAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdTblfm']]]
struct haxorg_ImmCmdTblfmAdapter {
  haxorg_ImmCmdTblfmAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterBlockCenterAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterBlockCenterAPI']
struct haxorg_ImmAdapterBlockCenterAPI {
  haxorg_ImmAdapterBlockCenterAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterBlockQuoteAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterBlockQuoteAPI']
struct haxorg_ImmAdapterBlockQuoteAPI {
  haxorg_ImmAdapterBlockQuoteAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterBlockVerseAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterBlockVerseAPI']
struct haxorg_ImmAdapterBlockVerseAPI {
  haxorg_ImmAdapterBlockVerseAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterBlockExampleAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterBlockExampleAPI']
struct haxorg_ImmAdapterBlockExampleAPI {
  haxorg_ImmAdapterBlockExampleAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterInlineExportAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterInlineExportAPI']
struct haxorg_ImmAdapterInlineExportAPI {
  haxorg_ImmAdapterInlineExportAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterCmdExportAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdExportAPI']
struct haxorg_ImmAdapterCmdExportAPI {
  haxorg_ImmAdapterCmdExportAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterBlockExportAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterBlockExportAPI']
struct haxorg_ImmAdapterBlockExportAPI {
  haxorg_ImmAdapterBlockExportAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterBlockDynamicFallbackAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterBlockDynamicFallbackAPI']
struct haxorg_ImmAdapterBlockDynamicFallbackAPI {
  haxorg_ImmAdapterBlockDynamicFallbackAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterBlockAdmonitionAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterBlockAdmonitionAPI']
struct haxorg_ImmAdapterBlockAdmonitionAPI {
  haxorg_ImmAdapterBlockAdmonitionAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterBlockCodeEvalResultAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterBlockCodeEvalResultAPI']
struct haxorg_ImmAdapterBlockCodeEvalResultAPI {
  haxorg_ImmAdapterBlockCodeEvalResultAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterBlockCodeAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterBlockCodeAPI']
struct haxorg_ImmAdapterBlockCodeAPI {
  haxorg_ImmAdapterBlockCodeAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterTableAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterTableAPI']
struct haxorg_ImmAdapterTableAPI {
  haxorg_ImmAdapterTableAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmBlockAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlock']]]
struct haxorg_ImmBlockAdapter {
  haxorg_ImmBlockAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmCellAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCell']]]
struct haxorg_ImmCellAdapter {
  haxorg_ImmCellAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmRowAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmRow']]]
struct haxorg_ImmRowAdapter {
  haxorg_ImmRowAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterCmdCaptionAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdCaptionAPI']
struct haxorg_ImmAdapterCmdCaptionAPI {
  haxorg_ImmAdapterCmdCaptionAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterCmdColumnsAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdColumnsAPI']
struct haxorg_ImmAdapterCmdColumnsAPI {
  haxorg_ImmAdapterCmdColumnsAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterCmdNameAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdNameAPI']
struct haxorg_ImmAdapterCmdNameAPI {
  haxorg_ImmAdapterCmdNameAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterCmdCallAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdCallAPI']
struct haxorg_ImmAdapterCmdCallAPI {
  haxorg_ImmAdapterCmdCallAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterCmdResultsAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdResultsAPI']
struct haxorg_ImmAdapterCmdResultsAPI {
  haxorg_ImmAdapterCmdResultsAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAdapterCmdAttrAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdAttrAPI']
struct haxorg_ImmAdapterCmdAttrAPI {
  haxorg_ImmAdapterCmdAttrAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmAttachedAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmAttached']]]
struct haxorg_ImmAttachedAdapter {
  haxorg_ImmAttachedAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmBlockCenterAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlockCenter']]]
struct haxorg_ImmBlockCenterAdapter {
  haxorg_ImmBlockCenterAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmBlockQuoteAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlockQuote']]]
struct haxorg_ImmBlockQuoteAdapter {
  haxorg_ImmBlockQuoteAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmBlockVerseAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlockVerse']]]
struct haxorg_ImmBlockVerseAdapter {
  haxorg_ImmBlockVerseAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmBlockExampleAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlockExample']]]
struct haxorg_ImmBlockExampleAdapter {
  haxorg_ImmBlockExampleAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmInlineExportAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmInlineExport']]]
struct haxorg_ImmInlineExportAdapter {
  haxorg_ImmInlineExportAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmCmdExportAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdExport']]]
struct haxorg_ImmCmdExportAdapter {
  haxorg_ImmCmdExportAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmBlockExportAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlockExport']]]
struct haxorg_ImmBlockExportAdapter {
  haxorg_ImmBlockExportAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmBlockDynamicFallbackAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlockDynamicFallback']]]
struct haxorg_ImmBlockDynamicFallbackAdapter {
  haxorg_ImmBlockDynamicFallbackAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmBlockAdmonitionAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlockAdmonition']]]
struct haxorg_ImmBlockAdmonitionAdapter {
  haxorg_ImmBlockAdmonitionAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmBlockCodeEvalResultAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlockCodeEvalResult']]]
struct haxorg_ImmBlockCodeEvalResultAdapter {
  haxorg_ImmBlockCodeEvalResultAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmBlockCodeAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlockCode']]]
struct haxorg_ImmBlockCodeAdapter {
  haxorg_ImmBlockCodeAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmTableAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmTable']]]
struct haxorg_ImmTableAdapter {
  haxorg_ImmTableAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmCmdCaptionAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdCaption']]]
struct haxorg_ImmCmdCaptionAdapter {
  haxorg_ImmCmdCaptionAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmCmdColumnsAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdColumns']]]
struct haxorg_ImmCmdColumnsAdapter {
  haxorg_ImmCmdColumnsAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmCmdNameAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdName']]]
struct haxorg_ImmCmdNameAdapter {
  haxorg_ImmCmdNameAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmCmdCallAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdCall']]]
struct haxorg_ImmCmdCallAdapter {
  haxorg_ImmCmdCallAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_ImmCmdAttrAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdAttr']]]
struct haxorg_ImmCmdAttrAdapter {
  haxorg_ImmCmdAttrAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

struct haxorg_UserTimeBreakdown_vtable {
  haxorg_StdOptional const* (*get_year)(haxorg_UserTimeBreakdown const*);
  haxorg_StdOptional const* (*get_month)(haxorg_UserTimeBreakdown const*);
  haxorg_StdOptional const* (*get_day)(haxorg_UserTimeBreakdown const*);
  haxorg_StdOptional const* (*get_hour)(haxorg_UserTimeBreakdown const*);
  haxorg_StdOptional const* (*get_minute)(haxorg_UserTimeBreakdown const*);
  haxorg_StdOptional const* (*get_second)(haxorg_UserTimeBreakdown const*);
  haxorg_StdOptional const* (*get_zone)(haxorg_UserTimeBreakdown const*);
};

struct haxorg_ParseSourceLoc_vtable {
  int const* (*get_line)(haxorg_ParseSourceLoc const*);
  int const* (*get_column)(haxorg_ParseSourceLoc const*);
  int const* (*get_pos)(haxorg_ParseSourceLoc const*);
  haxorg_ParseSourceFileId const* (*get_file_id)(haxorg_ParseSourceLoc const*);
};

struct haxorg_Org_vtable {
  haxorg_StdOptional const* (*get_loc)(haxorg_Org const*);
  haxorg_HstdVec const* (*get_subnodes)(haxorg_Org const*);
};

struct haxorg_OperationsTracer_vtable {
  bool const* (*get_TraceState)(haxorg_OperationsTracer const*);
  bool const* (*get_traceToFile)(haxorg_OperationsTracer const*);
  bool const* (*get_traceToBuffer)(haxorg_OperationsTracer const*);
  bool const* (*get_traceStructured)(haxorg_OperationsTracer const*);
  bool const* (*get_traceColored)(haxorg_OperationsTracer const*);
  int const* (*get_activeLevel)(haxorg_OperationsTracer const*);
  haxorg_StdString const* (*get_traceBuffer)(haxorg_OperationsTracer const*);
};

struct haxorg_ParseOrgParseFragment_vtable {
  int const* (*get_baseLine)(haxorg_ParseOrgParseFragment const*);
  int const* (*get_baseCol)(haxorg_ParseOrgParseFragment const*);
  haxorg_StdString const* (*get_text)(haxorg_ParseOrgParseFragment const*);
};

struct haxorg_OrgParseParameters_vtable {
  haxorg_StdOptional const* (*get_baseTokenTracePath)(haxorg_OrgParseParameters const*);
  haxorg_StdOptional const* (*get_tokenTracePath)(haxorg_OrgParseParameters const*);
  haxorg_StdOptional const* (*get_parseTracePath)(haxorg_OrgParseParameters const*);
  haxorg_StdOptional const* (*get_semTracePath)(haxorg_OrgParseParameters const*);
};

struct haxorg_ImmPath_vtable {
  haxorg_ImmId const* (*get_root)(haxorg_ImmPath const*);
  haxorg_ImmPathStore const* (*get_path)(haxorg_ImmPath const*);
};

struct haxorg_ImmAdapterTreeReprConf_vtable {
  int const* (*get_maxDepth)(haxorg_ImmAdapterTreeReprConf const*);
  bool const* (*get_withAuxFields)(haxorg_ImmAdapterTreeReprConf const*);
  bool const* (*get_withReflFields)(haxorg_ImmAdapterTreeReprConf const*);
  haxorg_HstdUnorderedSet const* (*get_withFieldSubset)(haxorg_ImmAdapterTreeReprConf const*);
};

struct haxorg_OrgYamlExportOpts_vtable {
  bool const* (*get_skipNullFields)(haxorg_OrgYamlExportOpts const*);
  bool const* (*get_skipFalseFields)(haxorg_OrgYamlExportOpts const*);
  bool const* (*get_skipZeroFields)(haxorg_OrgYamlExportOpts const*);
  bool const* (*get_skipLocation)(haxorg_OrgYamlExportOpts const*);
  bool const* (*get_skipId)(haxorg_OrgYamlExportOpts const*);
};

struct haxorg_OrgTreeExportOpts_vtable {
  bool const* (*get_withLineCol)(haxorg_OrgTreeExportOpts const*);
  bool const* (*get_withOriginalId)(haxorg_OrgTreeExportOpts const*);
  bool const* (*get_withSubnodeIdx)(haxorg_OrgTreeExportOpts const*);
  bool const* (*get_skipEmptyFields)(haxorg_OrgTreeExportOpts const*);
  int const* (*get_startLevel)(haxorg_OrgTreeExportOpts const*);
  bool const* (*get_withColor)(haxorg_OrgTreeExportOpts const*);
  int const* (*get_maxDepth)(haxorg_OrgTreeExportOpts const*);
};

struct haxorg_AstTrackingPath_vtable {
  haxorg_HstdVec const* (*get_path)(haxorg_AstTrackingPath const*);
};

struct haxorg_AstTrackingGroupRadioTarget_vtable {
  haxorg_AstTrackingPath const* (*get_target)(haxorg_AstTrackingGroupRadioTarget const*);
  haxorg_HstdVec const* (*get_nodes)(haxorg_AstTrackingGroupRadioTarget const*);
};

struct haxorg_AstTrackingGroupSingle_vtable {
  haxorg_SemId const* (*get_node)(haxorg_AstTrackingGroupSingle const*);
};

struct haxorg_AstTrackingGroupTrackedHashtag_vtable {
  haxorg_SemId const* (*get_tag)(haxorg_AstTrackingGroupTrackedHashtag const*);
  haxorg_HstdUnorderedMap const* (*get_targets)(haxorg_AstTrackingGroupTrackedHashtag const*);
};

struct haxorg_AstTrackingMap_vtable {
  haxorg_HstdUnorderedMap const* (*get_footnotes)(haxorg_AstTrackingMap const*);
  haxorg_HstdUnorderedMap const* (*get_subtrees)(haxorg_AstTrackingMap const*);
  haxorg_HstdUnorderedMap const* (*get_names)(haxorg_AstTrackingMap const*);
  haxorg_HstdUnorderedMap const* (*get_anchorTargets)(haxorg_AstTrackingMap const*);
  haxorg_HstdUnorderedMap const* (*get_radioTargets)(haxorg_AstTrackingMap const*);
  haxorg_HstdUnorderedMap const* (*get_hashtagDefinitions)(haxorg_AstTrackingMap const*);
};

struct haxorg_SequenceSegment_vtable {
  int const* (*get_kind)(haxorg_SequenceSegment const*);
  int const* (*get_first)(haxorg_SequenceSegment const*);
  int const* (*get_last)(haxorg_SequenceSegment const*);
};

struct haxorg_SequenceSegmentGroup_vtable {
  int const* (*get_kind)(haxorg_SequenceSegmentGroup const*);
  haxorg_HstdVec const* (*get_segments)(haxorg_SequenceSegmentGroup const*);
};

struct haxorg_SequenceAnnotationTag_vtable {
  int const* (*get_groupKind)(haxorg_SequenceAnnotationTag const*);
  haxorg_HstdVec const* (*get_segmentKinds)(haxorg_SequenceAnnotationTag const*);
};

struct haxorg_SequenceAnnotation_vtable {
  int const* (*get_first)(haxorg_SequenceAnnotation const*);
  int const* (*get_last)(haxorg_SequenceAnnotation const*);
  haxorg_HstdVec const* (*get_annotations)(haxorg_SequenceAnnotation const*);
};

struct haxorg_GraphMapLinkLink_vtable {
  haxorg_ImmUniqId const* (*get_link)(haxorg_GraphMapLinkLink const*);
  haxorg_HstdVec const* (*get_description)(haxorg_GraphMapLinkLink const*);
};

struct haxorg_GraphMapLinkRadio_vtable {
  haxorg_ImmUniqId const* (*get_target)(haxorg_GraphMapLinkRadio const*);
};

struct haxorg_GraphMapNodeProp_vtable {
  haxorg_ImmUniqId const* (*get_id)(haxorg_GraphMapNodeProp const*);
  haxorg_HstdVec const* (*get_unresolved)(haxorg_GraphMapNodeProp const*);
};

struct haxorg_GraphMapEdgeProp_vtable {
  haxorg_GraphMapLink const* (*get_link)(haxorg_GraphMapEdgeProp const*);
};

struct haxorg_GraphMapNode_vtable {
  haxorg_ImmUniqId const* (*get_id)(haxorg_GraphMapNode const*);
};

struct haxorg_GraphMapEdge_vtable {
  haxorg_GraphMapNode const* (*get_source)(haxorg_GraphMapEdge const*);
  haxorg_GraphMapNode const* (*get_target)(haxorg_GraphMapEdge const*);
};

struct haxorg_GraphMapGraph_vtable {
  haxorg_GraphNodeProps const* (*get_nodeProps)(haxorg_GraphMapGraph const*);
  haxorg_GraphEdgeProps const* (*get_edgeProps)(haxorg_GraphMapGraph const*);
  haxorg_GraphAdjList const* (*get_adjList)(haxorg_GraphMapGraph const*);
  haxorg_GraphAdjList const* (*get_adjListIn)(haxorg_GraphMapGraph const*);
};

struct haxorg_GraphMapConfig_vtable {
  haxorg_OperationsTracer const* (*get_dbg)(haxorg_GraphMapConfig const*);
};

struct haxorg_GraphMapGraphState_vtable {
  haxorg_GraphMapGraph const* (*get_graph)(haxorg_GraphMapGraphState const*);
  haxorg_ImmAstContext const* (*get_ast)(haxorg_GraphMapGraphState const*);
};

struct haxorg_LispCodeCall_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_LispCodeCall const*);
  haxorg_HstdVec const* (*get_args)(haxorg_LispCodeCall const*);
};

struct haxorg_LispCodeList_vtable {
  haxorg_HstdVec const* (*get_items)(haxorg_LispCodeList const*);
};

struct haxorg_LispCodeKeyValue_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_LispCodeKeyValue const*);
  haxorg_HstdVec const* (*get_value)(haxorg_LispCodeKeyValue const*);
};

struct haxorg_LispCodeNumber_vtable {
  int const* (*get_value)(haxorg_LispCodeNumber const*);
};

struct haxorg_LispCodeText_vtable {
  haxorg_HstdStr const* (*get_value)(haxorg_LispCodeText const*);
};

struct haxorg_LispCodeIdent_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_LispCodeIdent const*);
};

struct haxorg_LispCodeBoolean_vtable {
  bool const* (*get_value)(haxorg_LispCodeBoolean const*);
};

struct haxorg_LispCodeReal_vtable {
  float const* (*get_value)(haxorg_LispCodeReal const*);
};

struct haxorg_TblfmExprAxisRefPositionIndex_vtable {
  int const* (*get_index)(haxorg_TblfmExprAxisRefPositionIndex const*);
};

struct haxorg_TblfmExprAxisRefPositionName_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_TblfmExprAxisRefPositionName const*);
};

struct haxorg_TblfmExprAxisRef_vtable {
  haxorg_TblfmExprAxisRefPosition const* (*get_col)(haxorg_TblfmExprAxisRef const*);
  haxorg_HstdOpt const* (*get_row)(haxorg_TblfmExprAxisRef const*);
};

struct haxorg_TblfmExprAxisName_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_TblfmExprAxisName const*);
};

struct haxorg_TblfmExprIntLiteral_vtable {
  int const* (*get_value)(haxorg_TblfmExprIntLiteral const*);
};

struct haxorg_TblfmExprFloatLiteral_vtable {
  float const* (*get_value)(haxorg_TblfmExprFloatLiteral const*);
};

struct haxorg_TblfmExprRangeRef_vtable {
  haxorg_HstdOpt const* (*get_first)(haxorg_TblfmExprRangeRef const*);
  haxorg_HstdOpt const* (*get_last)(haxorg_TblfmExprRangeRef const*);
};

struct haxorg_TblfmExprCall_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_TblfmExprCall const*);
  haxorg_HstdVec const* (*get_args)(haxorg_TblfmExprCall const*);
};

struct haxorg_TblfmExprElisp_vtable {
  haxorg_HstdStr const* (*get_value)(haxorg_TblfmExprElisp const*);
};

struct haxorg_TblfmAssign_vtable {
  haxorg_TblfmExprAxisRef const* (*get_target)(haxorg_TblfmAssign const*);
  haxorg_HstdVec const* (*get_expr)(haxorg_TblfmAssign const*);
  haxorg_HstdVec const* (*get_flags)(haxorg_TblfmAssign const*);
};

struct haxorg_Tblfm_vtable {
  haxorg_HstdVec const* (*get_exprs)(haxorg_Tblfm const*);
};

struct haxorg_AttrValueDimensionSpan_vtable {
  int const* (*get_first)(haxorg_AttrValueDimensionSpan const*);
  haxorg_HstdOpt const* (*get_last)(haxorg_AttrValueDimensionSpan const*);
};

struct haxorg_AttrValueTextValue_vtable {
  haxorg_HstdStr const* (*get_value)(haxorg_AttrValueTextValue const*);
};

struct haxorg_AttrValueFileReference_vtable {
  haxorg_HstdStr const* (*get_file)(haxorg_AttrValueFileReference const*);
  haxorg_HstdStr const* (*get_reference)(haxorg_AttrValueFileReference const*);
};

struct haxorg_AttrValueLispValue_vtable {
  haxorg_LispCode const* (*get_code)(haxorg_AttrValueLispValue const*);
};

struct haxorg_AttrValue_vtable {
  haxorg_HstdOpt const* (*get_name)(haxorg_AttrValue const*);
  haxorg_HstdOpt const* (*get_varname)(haxorg_AttrValue const*);
  haxorg_HstdVec const* (*get_span)(haxorg_AttrValue const*);
  bool const* (*get_isQuoted)(haxorg_AttrValue const*);
};

struct haxorg_HashTagFlat_vtable {
  haxorg_HstdVec const* (*get_tags)(haxorg_HashTagFlat const*);
};

struct haxorg_TodoKeyword_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_TodoKeyword const*);
  haxorg_HstdOpt const* (*get_shortcut)(haxorg_TodoKeyword const*);
  haxorg_TodoKeywordTransition const* (*get_onEnter)(haxorg_TodoKeyword const*);
  haxorg_TodoKeywordTransition const* (*get_onLeave)(haxorg_TodoKeyword const*);
};

struct haxorg_HashTagText_vtable {
  haxorg_HstdStr const* (*get_head)(haxorg_HashTagText const*);
  haxorg_HstdVec const* (*get_subtags)(haxorg_HashTagText const*);
};

struct haxorg_SubtreePath_vtable {
  haxorg_HstdVec const* (*get_path)(haxorg_SubtreePath const*);
};

struct haxorg_LinkTargetRaw_vtable {
  haxorg_HstdStr const* (*get_text)(haxorg_LinkTargetRaw const*);
};

struct haxorg_LinkTargetId_vtable {
  haxorg_HstdStr const* (*get_text)(haxorg_LinkTargetId const*);
};

struct haxorg_LinkTargetCustomId_vtable {
  haxorg_HstdStr const* (*get_text)(haxorg_LinkTargetCustomId const*);
};

struct haxorg_LinkTargetSubtreeTitle_vtable {
  haxorg_SubtreePath const* (*get_title)(haxorg_LinkTargetSubtreeTitle const*);
  int const* (*get_level)(haxorg_LinkTargetSubtreeTitle const*);
};

struct haxorg_LinkTargetPerson_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_LinkTargetPerson const*);
};

struct haxorg_LinkTargetUserProtocol_vtable {
  haxorg_HstdStr const* (*get_protocol)(haxorg_LinkTargetUserProtocol const*);
  haxorg_HstdStr const* (*get_target)(haxorg_LinkTargetUserProtocol const*);
};

struct haxorg_LinkTargetInternal_vtable {
  haxorg_HstdStr const* (*get_target)(haxorg_LinkTargetInternal const*);
};

struct haxorg_LinkTargetFootnote_vtable {
  haxorg_HstdStr const* (*get_target)(haxorg_LinkTargetFootnote const*);
};

struct haxorg_LinkTargetFile_vtable {
  haxorg_HstdStr const* (*get_file)(haxorg_LinkTargetFile const*);
};

struct haxorg_LinkTargetAttachment_vtable {
  haxorg_HstdStr const* (*get_file)(haxorg_LinkTargetAttachment const*);
};

struct haxorg_SubtreeLogHeadPriority_vtable {
  haxorg_HstdOpt const* (*get_oldPriority)(haxorg_SubtreeLogHeadPriority const*);
  haxorg_HstdOpt const* (*get_newPriority)(haxorg_SubtreeLogHeadPriority const*);
  haxorg_UserTime const* (*get_on)(haxorg_SubtreeLogHeadPriority const*);
  haxorg_SubtreeLogHeadPriorityAction const* (*get_action)(haxorg_SubtreeLogHeadPriority const*);
};

struct haxorg_SubtreeLogHeadNote_vtable {
  haxorg_UserTime const* (*get_on)(haxorg_SubtreeLogHeadNote const*);
};

struct haxorg_SubtreeLogHeadRefile_vtable {
  haxorg_UserTime const* (*get_on)(haxorg_SubtreeLogHeadRefile const*);
  haxorg_LinkTarget const* (*get_from)(haxorg_SubtreeLogHeadRefile const*);
};

struct haxorg_SubtreeLogHeadClock_vtable {
  haxorg_UserTime const* (*get_from)(haxorg_SubtreeLogHeadClock const*);
  haxorg_HstdOpt const* (*get_to)(haxorg_SubtreeLogHeadClock const*);
};

struct haxorg_SubtreeLogHeadState_vtable {
  haxorg_HstdStr const* (*get_from)(haxorg_SubtreeLogHeadState const*);
  haxorg_HstdStr const* (*get_to)(haxorg_SubtreeLogHeadState const*);
  haxorg_UserTime const* (*get_on)(haxorg_SubtreeLogHeadState const*);
};

struct haxorg_SubtreeLogHeadDeadline_vtable {
  haxorg_HstdOpt const* (*get_from)(haxorg_SubtreeLogHeadDeadline const*);
  haxorg_UserTime const* (*get_to)(haxorg_SubtreeLogHeadDeadline const*);
  haxorg_UserTime const* (*get_on)(haxorg_SubtreeLogHeadDeadline const*);
};

struct haxorg_SubtreeLogHeadSchedule_vtable {
  haxorg_HstdOpt const* (*get_from)(haxorg_SubtreeLogHeadSchedule const*);
  haxorg_UserTime const* (*get_to)(haxorg_SubtreeLogHeadSchedule const*);
  haxorg_UserTime const* (*get_on)(haxorg_SubtreeLogHeadSchedule const*);
};

struct haxorg_SubtreeLogHeadTag_vtable {
  haxorg_UserTime const* (*get_on)(haxorg_SubtreeLogHeadTag const*);
  haxorg_HashTagText const* (*get_tag)(haxorg_SubtreeLogHeadTag const*);
  bool const* (*get_added)(haxorg_SubtreeLogHeadTag const*);
};

struct haxorg_SubtreeCompletion_vtable {
  int const* (*get_done)(haxorg_SubtreeCompletion const*);
  int const* (*get_full)(haxorg_SubtreeCompletion const*);
  bool const* (*get_isPercent)(haxorg_SubtreeCompletion const*);
};

struct haxorg_AttrList_vtable {
  haxorg_HstdVec const* (*get_items)(haxorg_AttrList const*);
};

struct haxorg_AttrGroup_vtable {
  haxorg_AttrList const* (*get_positional)(haxorg_AttrGroup const*);
  haxorg_HstdUnorderedMap const* (*get_named)(haxorg_AttrGroup const*);
};

struct haxorg_OrgCodeEvalInputVar_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_OrgCodeEvalInputVar const*);
  haxorg_OrgJson const* (*get_value)(haxorg_OrgCodeEvalInputVar const*);
};

struct haxorg_OrgCodeEvalInput_vtable {
  haxorg_AttrGroup const* (*get_blockAttrs)(haxorg_OrgCodeEvalInput const*);
  haxorg_HstdStr const* (*get_tangledCode)(haxorg_OrgCodeEvalInput const*);
  haxorg_HstdOpt const* (*get_exportType)(haxorg_OrgCodeEvalInput const*);
  haxorg_OrgCodeEvalInputResultType const* (*get_resultType)(haxorg_OrgCodeEvalInput const*);
  haxorg_OrgCodeEvalInputResultFormat const* (*get_resultFormat)(haxorg_OrgCodeEvalInput const*);
  haxorg_OrgCodeEvalInputResultHandling const* (*get_resultHandling)(haxorg_OrgCodeEvalInput const*);
  haxorg_HstdStr const* (*get_language)(haxorg_OrgCodeEvalInput const*);
  haxorg_HstdVec const* (*get_argList)(haxorg_OrgCodeEvalInput const*);
};

struct haxorg_OrgCodeEvalOutput_vtable {
  haxorg_HstdStr const* (*get_stdoutText)(haxorg_OrgCodeEvalOutput const*);
  haxorg_HstdStr const* (*get_stderrText)(haxorg_OrgCodeEvalOutput const*);
  int const* (*get_code)(haxorg_OrgCodeEvalOutput const*);
  haxorg_HstdOpt const* (*get_cmd)(haxorg_OrgCodeEvalOutput const*);
  haxorg_HstdVec const* (*get_args)(haxorg_OrgCodeEvalOutput const*);
  haxorg_HstdStr const* (*get_cwd)(haxorg_OrgCodeEvalOutput const*);
  haxorg_AttrGroup const* (*get_appliedHeaderArg)(haxorg_OrgCodeEvalOutput const*);
};

struct haxorg_ColumnViewSummaryCheckboxAggregate_vtable {
  haxorg_ColumnViewSummaryCheckboxAggregateKind const* (*get_kind)(haxorg_ColumnViewSummaryCheckboxAggregate const*);
};

struct haxorg_ColumnViewSummaryMathAggregate_vtable {
  haxorg_ColumnViewSummaryMathAggregateKind const* (*get_kind)(haxorg_ColumnViewSummaryMathAggregate const*);
  haxorg_HstdOpt const* (*get_formatDigits)(haxorg_ColumnViewSummaryMathAggregate const*);
  haxorg_HstdOpt const* (*get_formatPrecision)(haxorg_ColumnViewSummaryMathAggregate const*);
};

struct haxorg_ColumnViewColumn_vtable {
  haxorg_HstdOpt const* (*get_summary)(haxorg_ColumnViewColumn const*);
  haxorg_HstdOpt const* (*get_width)(haxorg_ColumnViewColumn const*);
  haxorg_HstdOpt const* (*get_property)(haxorg_ColumnViewColumn const*);
  haxorg_HstdOpt const* (*get_propertyTitle)(haxorg_ColumnViewColumn const*);
};

struct haxorg_ColumnView_vtable {
  haxorg_HstdVec const* (*get_columns)(haxorg_ColumnView const*);
};

struct haxorg_BlockCodeLinePartRaw_vtable {
  haxorg_HstdStr const* (*get_code)(haxorg_BlockCodeLinePartRaw const*);
};

struct haxorg_BlockCodeLinePartCallout_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_BlockCodeLinePartCallout const*);
};

struct haxorg_BlockCodeLinePartTangle_vtable {
  haxorg_HstdStr const* (*get_target)(haxorg_BlockCodeLinePartTangle const*);
};

struct haxorg_BlockCodeLine_vtable {
  haxorg_HstdVec const* (*get_parts)(haxorg_BlockCodeLine const*);
};

struct haxorg_DocumentExportConfigTaskExport_vtable {
  haxorg_HstdVec const* (*get_taskWhitelist)(haxorg_DocumentExportConfigTaskExport const*);
};

struct haxorg_DocumentExportConfigDoExport_vtable {
  bool const* (*get_exportToc)(haxorg_DocumentExportConfigDoExport const*);
};

struct haxorg_DocumentExportConfigExportFixed_vtable {
  int const* (*get_exportLevels)(haxorg_DocumentExportConfigExportFixed const*);
};

struct haxorg_DocumentExportConfig_vtable {
  haxorg_HstdOpt const* (*get_inlinetasks)(haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_footnotes)(haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_clock)(haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_author)(haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_emphasis)(haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_specialStrings)(haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_propertyDrawers)(haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_statisticsCookies)(haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_todoText)(haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_smartQuotes)(haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_fixedWidth)(haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_timestamps)(haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_preserveBreaks)(haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_subSuperscripts)(haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_expandLinks)(haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_creator)(haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_drawers)(haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_date)(haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_entities)(haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_email)(haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_sectionNumbers)(haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_planning)(haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_priority)(haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_latex)(haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_timestamp)(haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_title)(haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_tables)(haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_headlineLevels)(haxorg_DocumentExportConfig const*);
  haxorg_DocumentExportConfigBrokenLinks const* (*get_brokenLinks)(haxorg_DocumentExportConfig const*);
  haxorg_DocumentExportConfigTocExport const* (*get_tocExport)(haxorg_DocumentExportConfig const*);
  haxorg_DocumentExportConfigTagExport const* (*get_tagExport)(haxorg_DocumentExportConfig const*);
  haxorg_DocumentExportConfigTaskFiltering const* (*get_taskFiltering)(haxorg_DocumentExportConfig const*);
  haxorg_DocumentExportConfigArchivedTrees const* (*get_archivedTrees)(haxorg_DocumentExportConfig const*);
};

struct haxorg_SubtreePeriod_vtable {
  haxorg_SubtreePeriodKind const* (*get_kind)(haxorg_SubtreePeriod const*);
  haxorg_UserTime const* (*get_from)(haxorg_SubtreePeriod const*);
  haxorg_HstdOpt const* (*get_to)(haxorg_SubtreePeriod const*);
};

struct haxorg_NamedPropertyNonblocking_vtable {
  bool const* (*get_isBlocking)(haxorg_NamedPropertyNonblocking const*);
};

struct haxorg_NamedPropertyArchiveTime_vtable {
  haxorg_UserTime const* (*get_time)(haxorg_NamedPropertyArchiveTime const*);
};

struct haxorg_NamedPropertyArchiveFile_vtable {
  haxorg_HstdStr const* (*get_file)(haxorg_NamedPropertyArchiveFile const*);
};

struct haxorg_NamedPropertyArchiveOlpath_vtable {
  haxorg_SubtreePath const* (*get_path)(haxorg_NamedPropertyArchiveOlpath const*);
};

struct haxorg_NamedPropertyArchiveTarget_vtable {
  haxorg_SubtreePath const* (*get_path)(haxorg_NamedPropertyArchiveTarget const*);
  haxorg_HstdStr const* (*get_pattern)(haxorg_NamedPropertyArchiveTarget const*);
};

struct haxorg_NamedPropertyArchiveCategory_vtable {
  haxorg_HstdStr const* (*get_category)(haxorg_NamedPropertyArchiveCategory const*);
};

struct haxorg_NamedPropertyArchiveTodo_vtable {
  haxorg_HstdStr const* (*get_todo)(haxorg_NamedPropertyArchiveTodo const*);
};

struct haxorg_NamedPropertyExportLatexClass_vtable {
  haxorg_HstdStr const* (*get_latexClass)(haxorg_NamedPropertyExportLatexClass const*);
};

struct haxorg_NamedPropertyCookieData_vtable {
  bool const* (*get_isRecursive)(haxorg_NamedPropertyCookieData const*);
  haxorg_SubtreeTodoSource const* (*get_source)(haxorg_NamedPropertyCookieData const*);
};

struct haxorg_NamedPropertyExportLatexClassOptions_vtable {
  haxorg_HstdVec const* (*get_options)(haxorg_NamedPropertyExportLatexClassOptions const*);
};

struct haxorg_NamedPropertyExportLatexHeader_vtable {
  haxorg_HstdStr const* (*get_header)(haxorg_NamedPropertyExportLatexHeader const*);
};

struct haxorg_NamedPropertyExportLatexCompiler_vtable {
  haxorg_HstdStr const* (*get_compiler)(haxorg_NamedPropertyExportLatexCompiler const*);
};

struct haxorg_NamedPropertyOrdered_vtable {
  bool const* (*get_isOrdered)(haxorg_NamedPropertyOrdered const*);
};

struct haxorg_NamedPropertyEffort_vtable {
  int const* (*get_hours)(haxorg_NamedPropertyEffort const*);
  int const* (*get_minutes)(haxorg_NamedPropertyEffort const*);
};

struct haxorg_NamedPropertyVisibility_vtable {
  haxorg_NamedPropertyVisibilityLevel const* (*get_level)(haxorg_NamedPropertyVisibility const*);
};

struct haxorg_NamedPropertyExportOptions_vtable {
  haxorg_HstdStr const* (*get_backend)(haxorg_NamedPropertyExportOptions const*);
  haxorg_HstdUnorderedMap const* (*get_values)(haxorg_NamedPropertyExportOptions const*);
};

struct haxorg_NamedPropertyBlocker_vtable {
  haxorg_HstdVec const* (*get_blockers)(haxorg_NamedPropertyBlocker const*);
};

struct haxorg_NamedPropertyCreated_vtable {
  haxorg_UserTime const* (*get_time)(haxorg_NamedPropertyCreated const*);
};

struct haxorg_NamedPropertyRadioId_vtable {
  haxorg_HstdVec const* (*get_words)(haxorg_NamedPropertyRadioId const*);
};

struct haxorg_NamedPropertyHashtagDef_vtable {
  haxorg_HashTagText const* (*get_hashtag)(haxorg_NamedPropertyHashtagDef const*);
};

struct haxorg_NamedPropertyCustomArgs_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_NamedPropertyCustomArgs const*);
  haxorg_HstdOpt const* (*get_sub)(haxorg_NamedPropertyCustomArgs const*);
  haxorg_AttrGroup const* (*get_attrs)(haxorg_NamedPropertyCustomArgs const*);
};

struct haxorg_NamedPropertyCustomRaw_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_NamedPropertyCustomRaw const*);
  haxorg_HstdStr const* (*get_value)(haxorg_NamedPropertyCustomRaw const*);
};

struct haxorg_NamedPropertyCustomId_vtable {
  haxorg_HstdStr const* (*get_value)(haxorg_NamedPropertyCustomId const*);
};

struct haxorg_NamedPropertyCustomSubtreeJson_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_NamedPropertyCustomSubtreeJson const*);
  haxorg_OrgJson const* (*get_value)(haxorg_NamedPropertyCustomSubtreeJson const*);
};

struct haxorg_NamedPropertyCustomSubtreeFlags_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_NamedPropertyCustomSubtreeFlags const*);
  haxorg_AttrGroup const* (*get_value)(haxorg_NamedPropertyCustomSubtreeFlags const*);
};

struct haxorg_OrgDiagnosticsParseTokenError_vtable {
  haxorg_HstdStr const* (*get_brief)(haxorg_OrgDiagnosticsParseTokenError const*);
  haxorg_HstdStr const* (*get_detail)(haxorg_OrgDiagnosticsParseTokenError const*);
  haxorg_HstdStr const* (*get_parserFunction)(haxorg_OrgDiagnosticsParseTokenError const*);
  int const* (*get_parserLine)(haxorg_OrgDiagnosticsParseTokenError const*);
  haxorg_OrgTokenKind const* (*get_tokenKind)(haxorg_OrgDiagnosticsParseTokenError const*);
  haxorg_HstdStr const* (*get_tokenText)(haxorg_OrgDiagnosticsParseTokenError const*);
  haxorg_ParseSourceLoc const* (*get_loc)(haxorg_OrgDiagnosticsParseTokenError const*);
  haxorg_HstdStr const* (*get_errName)(haxorg_OrgDiagnosticsParseTokenError const*);
  haxorg_HstdStr const* (*get_errCode)(haxorg_OrgDiagnosticsParseTokenError const*);
};

struct haxorg_OrgDiagnosticsParseError_vtable {
  haxorg_HstdStr const* (*get_brief)(haxorg_OrgDiagnosticsParseError const*);
  haxorg_HstdStr const* (*get_detail)(haxorg_OrgDiagnosticsParseError const*);
  haxorg_HstdStr const* (*get_parserFunction)(haxorg_OrgDiagnosticsParseError const*);
  int const* (*get_parserLine)(haxorg_OrgDiagnosticsParseError const*);
  haxorg_HstdStr const* (*get_errName)(haxorg_OrgDiagnosticsParseError const*);
  haxorg_HstdStr const* (*get_errCode)(haxorg_OrgDiagnosticsParseError const*);
  haxorg_HstdOpt const* (*get_loc)(haxorg_OrgDiagnosticsParseError const*);
};

struct haxorg_OrgDiagnosticsIncludeError_vtable {
  haxorg_HstdStr const* (*get_brief)(haxorg_OrgDiagnosticsIncludeError const*);
  haxorg_HstdStr const* (*get_targetPath)(haxorg_OrgDiagnosticsIncludeError const*);
  haxorg_HstdStr const* (*get_workingFile)(haxorg_OrgDiagnosticsIncludeError const*);
};

struct haxorg_OrgDiagnosticsConvertError_vtable {
  haxorg_HstdStr const* (*get_brief)(haxorg_OrgDiagnosticsConvertError const*);
  haxorg_HstdStr const* (*get_detail)(haxorg_OrgDiagnosticsConvertError const*);
  haxorg_HstdStr const* (*get_convertFunction)(haxorg_OrgDiagnosticsConvertError const*);
  int const* (*get_convertLine)(haxorg_OrgDiagnosticsConvertError const*);
  haxorg_HstdStr const* (*get_convertFile)(haxorg_OrgDiagnosticsConvertError const*);
  haxorg_HstdStr const* (*get_errName)(haxorg_OrgDiagnosticsConvertError const*);
  haxorg_HstdStr const* (*get_errCode)(haxorg_OrgDiagnosticsConvertError const*);
  haxorg_HstdOpt const* (*get_loc)(haxorg_OrgDiagnosticsConvertError const*);
};

struct haxorg_OrgDiagnosticsInternalError_vtable {
  haxorg_HstdStr const* (*get_message)(haxorg_OrgDiagnosticsInternalError const*);
  haxorg_HstdStr const* (*get_function)(haxorg_OrgDiagnosticsInternalError const*);
  int const* (*get_line)(haxorg_OrgDiagnosticsInternalError const*);
  haxorg_HstdStr const* (*get_file)(haxorg_OrgDiagnosticsInternalError const*);
  haxorg_HstdOpt const* (*get_loc)(haxorg_OrgDiagnosticsInternalError const*);
};

struct haxorg_ErrorItem_vtable {
  haxorg_OrgDiagnostics const* (*get_diag)(haxorg_ErrorItem const*);
};

struct haxorg_ErrorGroup_vtable {
  haxorg_HstdVec const* (*get_diagnostics)(haxorg_ErrorGroup const*);
};

struct haxorg_Stmt_vtable {
  haxorg_HstdVec const* (*get_attached)(haxorg_Stmt const*);
};

struct haxorg_Leaf_vtable {
  haxorg_HstdStr const* (*get_text)(haxorg_Leaf const*);
};

struct haxorg_TimeRepeat_vtable {
  haxorg_TimeRepeatMode const* (*get_mode)(haxorg_TimeRepeat const*);
  haxorg_TimeRepeatPeriod const* (*get_period)(haxorg_TimeRepeat const*);
  int const* (*get_count)(haxorg_TimeRepeat const*);
};

struct haxorg_TimeStatic_vtable {
  haxorg_HstdVec const* (*get_repeat)(haxorg_TimeStatic const*);
  haxorg_HstdOpt const* (*get_warn)(haxorg_TimeStatic const*);
  haxorg_UserTime const* (*get_time)(haxorg_TimeStatic const*);
};

struct haxorg_TimeDynamic_vtable {
  haxorg_LispCode const* (*get_expr)(haxorg_TimeDynamic const*);
};

struct haxorg_Time_vtable {
  bool const* (*get_isActive)(haxorg_Time const*);
};

struct haxorg_TimeRange_vtable {
  haxorg_SemId const* (*get_from)(haxorg_TimeRange const*);
  haxorg_SemId const* (*get_to)(haxorg_TimeRange const*);
};

struct haxorg_Macro_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_Macro const*);
  haxorg_AttrGroup const* (*get_attrs)(haxorg_Macro const*);
};

struct haxorg_SymbolParam_vtable {
  haxorg_HstdOpt const* (*get_key)(haxorg_SymbolParam const*);
  haxorg_HstdStr const* (*get_value)(haxorg_SymbolParam const*);
};

struct haxorg_Symbol_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_Symbol const*);
  haxorg_HstdVec const* (*get_parameters)(haxorg_Symbol const*);
  haxorg_HstdVec const* (*get_positional)(haxorg_Symbol const*);
};

struct haxorg_ErrorSkipGroup_vtable {
  haxorg_HstdVec const* (*get_skipped)(haxorg_ErrorSkipGroup const*);
};

struct haxorg_RadioTarget_vtable {
  haxorg_HstdVec const* (*get_words)(haxorg_RadioTarget const*);
};

struct haxorg_SubtreeLog_vtable {
  haxorg_SubtreeLogHead const* (*get_head)(haxorg_SubtreeLog const*);
  haxorg_HstdOpt const* (*get_desc)(haxorg_SubtreeLog const*);
};

struct haxorg_Subtree_vtable {
  int const* (*get_level)(haxorg_Subtree const*);
  haxorg_HstdOpt const* (*get_treeId)(haxorg_Subtree const*);
  haxorg_HstdOpt const* (*get_todo)(haxorg_Subtree const*);
  haxorg_HstdOpt const* (*get_completion)(haxorg_Subtree const*);
  haxorg_HstdOpt const* (*get_description)(haxorg_Subtree const*);
  haxorg_HstdVec const* (*get_tags)(haxorg_Subtree const*);
  haxorg_SemId const* (*get_title)(haxorg_Subtree const*);
  haxorg_HstdVec const* (*get_logbook)(haxorg_Subtree const*);
  haxorg_HstdVec const* (*get_properties)(haxorg_Subtree const*);
  haxorg_HstdOpt const* (*get_closed)(haxorg_Subtree const*);
  haxorg_HstdOpt const* (*get_deadline)(haxorg_Subtree const*);
  haxorg_HstdOpt const* (*get_scheduled)(haxorg_Subtree const*);
  bool const* (*get_isComment)(haxorg_Subtree const*);
  bool const* (*get_isArchived)(haxorg_Subtree const*);
  haxorg_HstdOpt const* (*get_priority)(haxorg_Subtree const*);
};

struct haxorg_Call_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_Call const*);
  haxorg_AttrGroup const* (*get_attrs)(haxorg_Call const*);
  bool const* (*get_isCommand)(haxorg_Call const*);
};

struct haxorg_ListItem_vtable {
  haxorg_CheckboxState const* (*get_checkbox)(haxorg_ListItem const*);
  haxorg_HstdOpt const* (*get_header)(haxorg_ListItem const*);
  haxorg_HstdOpt const* (*get_bullet)(haxorg_ListItem const*);
};

struct haxorg_DocumentOptions_vtable {
  haxorg_InitialSubtreeVisibility const* (*get_initialVisibility)(haxorg_DocumentOptions const*);
  haxorg_HstdVec const* (*get_properties)(haxorg_DocumentOptions const*);
  haxorg_DocumentExportConfig const* (*get_exportConfig)(haxorg_DocumentOptions const*);
  haxorg_HstdOpt const* (*get_fixedWidthSections)(haxorg_DocumentOptions const*);
  haxorg_HstdOpt const* (*get_startupIndented)(haxorg_DocumentOptions const*);
  haxorg_HstdOpt const* (*get_category)(haxorg_DocumentOptions const*);
  haxorg_HstdOpt const* (*get_setupfile)(haxorg_DocumentOptions const*);
  haxorg_HstdOpt const* (*get_maxSubtreeLevelExport)(haxorg_DocumentOptions const*);
  haxorg_HstdOpt const* (*get_columns)(haxorg_DocumentOptions const*);
  haxorg_HstdVec const* (*get_todoKeywords)(haxorg_DocumentOptions const*);
  haxorg_HstdVec const* (*get_doneKeywords)(haxorg_DocumentOptions const*);
};

struct haxorg_DocumentFragment_vtable {
  int const* (*get_baseLine)(haxorg_DocumentFragment const*);
  int const* (*get_baseCol)(haxorg_DocumentFragment const*);
};

struct haxorg_CriticMarkup_vtable {
  haxorg_CriticMarkupKind const* (*get_kind)(haxorg_CriticMarkup const*);
};

struct haxorg_Document_vtable {
  haxorg_HstdOpt const* (*get_title)(haxorg_Document const*);
  haxorg_HstdOpt const* (*get_author)(haxorg_Document const*);
  haxorg_HstdOpt const* (*get_creator)(haxorg_Document const*);
  haxorg_HstdVec const* (*get_filetags)(haxorg_Document const*);
  haxorg_HstdOpt const* (*get_email)(haxorg_Document const*);
  haxorg_HstdVec const* (*get_language)(haxorg_Document const*);
  haxorg_SemId const* (*get_options)(haxorg_Document const*);
  haxorg_HstdOpt const* (*get_exportFileName)(haxorg_Document const*);
};

struct haxorg_FileTarget_vtable {
  haxorg_HstdStr const* (*get_path)(haxorg_FileTarget const*);
  haxorg_HstdOpt const* (*get_line)(haxorg_FileTarget const*);
  haxorg_HstdOpt const* (*get_searchTarget)(haxorg_FileTarget const*);
  bool const* (*get_restrictToHeadlines)(haxorg_FileTarget const*);
  haxorg_HstdOpt const* (*get_targetId)(haxorg_FileTarget const*);
  haxorg_HstdOpt const* (*get_regexp)(haxorg_FileTarget const*);
};

struct haxorg_File_vtable {
  haxorg_HstdStr const* (*get_relPath)(haxorg_File const*);
  haxorg_HstdStr const* (*get_absPath)(haxorg_File const*);
};

struct haxorg_Directory_vtable {
  haxorg_HstdStr const* (*get_relPath)(haxorg_Directory const*);
  haxorg_HstdStr const* (*get_absPath)(haxorg_Directory const*);
};

struct haxorg_Symlink_vtable {
  bool const* (*get_isDirectory)(haxorg_Symlink const*);
  haxorg_HstdStr const* (*get_absPath)(haxorg_Symlink const*);
};

struct haxorg_CmdIncludeExport_vtable {
  haxorg_HstdStr const* (*get_language)(haxorg_CmdIncludeExport const*);
};

struct haxorg_CmdIncludeCustom_vtable {
  haxorg_HstdStr const* (*get_blockName)(haxorg_CmdIncludeCustom const*);
};

struct haxorg_CmdIncludeSrc_vtable {
  haxorg_HstdStr const* (*get_language)(haxorg_CmdIncludeSrc const*);
};

struct haxorg_CmdIncludeOrgDocument_vtable {
  haxorg_HstdOpt const* (*get_onlyContent)(haxorg_CmdIncludeOrgDocument const*);
  haxorg_HstdOpt const* (*get_subtreePath)(haxorg_CmdIncludeOrgDocument const*);
  haxorg_HstdOpt const* (*get_minLevel)(haxorg_CmdIncludeOrgDocument const*);
  haxorg_HstdOpt const* (*get_customIdTarget)(haxorg_CmdIncludeOrgDocument const*);
};

struct haxorg_CmdInclude_vtable {
  haxorg_HstdStr const* (*get_path)(haxorg_CmdInclude const*);
  haxorg_HstdOpt const* (*get_firstLine)(haxorg_CmdInclude const*);
  haxorg_HstdOpt const* (*get_lastLine)(haxorg_CmdInclude const*);
};

struct haxorg_ImmErrorItem_vtable {
  haxorg_OrgDiagnostics const* (*get_diag)(haxorg_ImmErrorItem const*);
};

struct haxorg_ImmErrorGroup_vtable {
  haxorg_ImmVec const* (*get_diagnostics)(haxorg_ImmErrorGroup const*);
};

struct haxorg_ImmStmt_vtable {
  haxorg_ImmVec const* (*get_attached)(haxorg_ImmStmt const*);
};

struct haxorg_ImmLeaf_vtable {
  haxorg_HstdStr const* (*get_text)(haxorg_ImmLeaf const*);
};

struct haxorg_ImmTimeRepeat_vtable {
  haxorg_ImmTimeRepeatMode const* (*get_mode)(haxorg_ImmTimeRepeat const*);
  haxorg_ImmTimeRepeatPeriod const* (*get_period)(haxorg_ImmTimeRepeat const*);
  int const* (*get_count)(haxorg_ImmTimeRepeat const*);
};

struct haxorg_ImmTimeStatic_vtable {
  haxorg_ImmVec const* (*get_repeat)(haxorg_ImmTimeStatic const*);
  haxorg_HstdOpt const* (*get_warn)(haxorg_ImmTimeStatic const*);
  haxorg_UserTime const* (*get_time)(haxorg_ImmTimeStatic const*);
};

struct haxorg_ImmTimeDynamic_vtable {
  haxorg_LispCode const* (*get_expr)(haxorg_ImmTimeDynamic const*);
};

struct haxorg_ImmTime_vtable {
  bool const* (*get_isActive)(haxorg_ImmTime const*);
};

struct haxorg_ImmTimeRange_vtable {
  haxorg_ImmId const* (*get_from)(haxorg_ImmTimeRange const*);
  haxorg_ImmId const* (*get_to)(haxorg_ImmTimeRange const*);
};

struct haxorg_ImmMacro_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_ImmMacro const*);
  haxorg_AttrGroup const* (*get_attrs)(haxorg_ImmMacro const*);
};

struct haxorg_ImmSymbolParam_vtable {
  haxorg_HstdOpt const* (*get_key)(haxorg_ImmSymbolParam const*);
  haxorg_HstdStr const* (*get_value)(haxorg_ImmSymbolParam const*);
};

struct haxorg_ImmSymbol_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_ImmSymbol const*);
  haxorg_ImmVec const* (*get_parameters)(haxorg_ImmSymbol const*);
  haxorg_ImmVec const* (*get_positional)(haxorg_ImmSymbol const*);
};

struct haxorg_ImmErrorSkipGroup_vtable {
  haxorg_ImmVec const* (*get_skipped)(haxorg_ImmErrorSkipGroup const*);
};

struct haxorg_ImmRadioTarget_vtable {
  haxorg_ImmVec const* (*get_words)(haxorg_ImmRadioTarget const*);
};

struct haxorg_ImmSubtreeLog_vtable {
  haxorg_SubtreeLogHead const* (*get_head)(haxorg_ImmSubtreeLog const*);
  haxorg_HstdOpt const* (*get_desc)(haxorg_ImmSubtreeLog const*);
};

struct haxorg_ImmSubtree_vtable {
  int const* (*get_level)(haxorg_ImmSubtree const*);
  haxorg_HstdOpt const* (*get_treeId)(haxorg_ImmSubtree const*);
  haxorg_HstdOpt const* (*get_todo)(haxorg_ImmSubtree const*);
  haxorg_HstdOpt const* (*get_completion)(haxorg_ImmSubtree const*);
  haxorg_HstdOpt const* (*get_description)(haxorg_ImmSubtree const*);
  haxorg_ImmVec const* (*get_tags)(haxorg_ImmSubtree const*);
  haxorg_ImmId const* (*get_title)(haxorg_ImmSubtree const*);
  haxorg_ImmVec const* (*get_logbook)(haxorg_ImmSubtree const*);
  haxorg_ImmVec const* (*get_properties)(haxorg_ImmSubtree const*);
  haxorg_HstdOpt const* (*get_closed)(haxorg_ImmSubtree const*);
  haxorg_HstdOpt const* (*get_deadline)(haxorg_ImmSubtree const*);
  haxorg_HstdOpt const* (*get_scheduled)(haxorg_ImmSubtree const*);
  bool const* (*get_isComment)(haxorg_ImmSubtree const*);
  bool const* (*get_isArchived)(haxorg_ImmSubtree const*);
  haxorg_HstdOpt const* (*get_priority)(haxorg_ImmSubtree const*);
};

struct haxorg_ImmCall_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_ImmCall const*);
  haxorg_AttrGroup const* (*get_attrs)(haxorg_ImmCall const*);
  bool const* (*get_isCommand)(haxorg_ImmCall const*);
};

struct haxorg_ImmListItem_vtable {
  haxorg_CheckboxState const* (*get_checkbox)(haxorg_ImmListItem const*);
  haxorg_HstdOpt const* (*get_header)(haxorg_ImmListItem const*);
  haxorg_HstdOpt const* (*get_bullet)(haxorg_ImmListItem const*);
};

struct haxorg_ImmDocumentOptions_vtable {
  haxorg_InitialSubtreeVisibility const* (*get_initialVisibility)(haxorg_ImmDocumentOptions const*);
  haxorg_ImmVec const* (*get_properties)(haxorg_ImmDocumentOptions const*);
  haxorg_DocumentExportConfig const* (*get_exportConfig)(haxorg_ImmDocumentOptions const*);
  haxorg_HstdOpt const* (*get_fixedWidthSections)(haxorg_ImmDocumentOptions const*);
  haxorg_HstdOpt const* (*get_startupIndented)(haxorg_ImmDocumentOptions const*);
  haxorg_HstdOpt const* (*get_category)(haxorg_ImmDocumentOptions const*);
  haxorg_HstdOpt const* (*get_setupfile)(haxorg_ImmDocumentOptions const*);
  haxorg_HstdOpt const* (*get_maxSubtreeLevelExport)(haxorg_ImmDocumentOptions const*);
  haxorg_HstdOpt const* (*get_columns)(haxorg_ImmDocumentOptions const*);
  haxorg_ImmVec const* (*get_todoKeywords)(haxorg_ImmDocumentOptions const*);
  haxorg_ImmVec const* (*get_doneKeywords)(haxorg_ImmDocumentOptions const*);
};

struct haxorg_ImmDocumentFragment_vtable {
  int const* (*get_baseLine)(haxorg_ImmDocumentFragment const*);
  int const* (*get_baseCol)(haxorg_ImmDocumentFragment const*);
};

struct haxorg_ImmCriticMarkup_vtable {
  haxorg_ImmCriticMarkupKind const* (*get_kind)(haxorg_ImmCriticMarkup const*);
};

struct haxorg_ImmDocument_vtable {
  haxorg_HstdOpt const* (*get_title)(haxorg_ImmDocument const*);
  haxorg_HstdOpt const* (*get_author)(haxorg_ImmDocument const*);
  haxorg_HstdOpt const* (*get_creator)(haxorg_ImmDocument const*);
  haxorg_ImmVec const* (*get_filetags)(haxorg_ImmDocument const*);
  haxorg_HstdOpt const* (*get_email)(haxorg_ImmDocument const*);
  haxorg_ImmVec const* (*get_language)(haxorg_ImmDocument const*);
  haxorg_ImmId const* (*get_options)(haxorg_ImmDocument const*);
  haxorg_HstdOpt const* (*get_exportFileName)(haxorg_ImmDocument const*);
};

struct haxorg_ImmFileTarget_vtable {
  haxorg_HstdStr const* (*get_path)(haxorg_ImmFileTarget const*);
  haxorg_HstdOpt const* (*get_line)(haxorg_ImmFileTarget const*);
  haxorg_HstdOpt const* (*get_searchTarget)(haxorg_ImmFileTarget const*);
  bool const* (*get_restrictToHeadlines)(haxorg_ImmFileTarget const*);
  haxorg_HstdOpt const* (*get_targetId)(haxorg_ImmFileTarget const*);
  haxorg_HstdOpt const* (*get_regexp)(haxorg_ImmFileTarget const*);
};

struct haxorg_ImmFile_vtable {
  haxorg_HstdStr const* (*get_relPath)(haxorg_ImmFile const*);
  haxorg_HstdStr const* (*get_absPath)(haxorg_ImmFile const*);
};

struct haxorg_ImmDirectory_vtable {
  haxorg_HstdStr const* (*get_relPath)(haxorg_ImmDirectory const*);
  haxorg_HstdStr const* (*get_absPath)(haxorg_ImmDirectory const*);
};

struct haxorg_ImmSymlink_vtable {
  bool const* (*get_isDirectory)(haxorg_ImmSymlink const*);
  haxorg_HstdStr const* (*get_absPath)(haxorg_ImmSymlink const*);
};

struct haxorg_ImmCmdIncludeExport_vtable {
  haxorg_HstdStr const* (*get_language)(haxorg_ImmCmdIncludeExport const*);
};

struct haxorg_ImmCmdIncludeCustom_vtable {
  haxorg_HstdStr const* (*get_blockName)(haxorg_ImmCmdIncludeCustom const*);
};

struct haxorg_ImmCmdIncludeSrc_vtable {
  haxorg_HstdStr const* (*get_language)(haxorg_ImmCmdIncludeSrc const*);
};

struct haxorg_ImmCmdIncludeOrgDocument_vtable {
  haxorg_HstdOpt const* (*get_onlyContent)(haxorg_ImmCmdIncludeOrgDocument const*);
  haxorg_HstdOpt const* (*get_subtreePath)(haxorg_ImmCmdIncludeOrgDocument const*);
  haxorg_HstdOpt const* (*get_minLevel)(haxorg_ImmCmdIncludeOrgDocument const*);
  haxorg_HstdOpt const* (*get_customIdTarget)(haxorg_ImmCmdIncludeOrgDocument const*);
};

struct haxorg_ImmCmdInclude_vtable {
  haxorg_HstdStr const* (*get_path)(haxorg_ImmCmdInclude const*);
  haxorg_HstdOpt const* (*get_firstLine)(haxorg_ImmCmdInclude const*);
  haxorg_HstdOpt const* (*get_lastLine)(haxorg_ImmCmdInclude const*);
};

struct haxorg_Cmd_vtable {
  haxorg_AttrGroup const* (*get_attrs)(haxorg_Cmd const*);
};

struct haxorg_CmdCustomRaw_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_CmdCustomRaw const*);
  bool const* (*get_isAttached)(haxorg_CmdCustomRaw const*);
  haxorg_HstdStr const* (*get_text)(haxorg_CmdCustomRaw const*);
};

struct haxorg_CmdCustomText_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_CmdCustomText const*);
  bool const* (*get_isAttached)(haxorg_CmdCustomText const*);
  haxorg_SemId const* (*get_text)(haxorg_CmdCustomText const*);
};

struct haxorg_Link_vtable {
  haxorg_HstdOpt const* (*get_description)(haxorg_Link const*);
  haxorg_LinkTarget const* (*get_target)(haxorg_Link const*);
};

struct haxorg_HashTag_vtable {
  haxorg_HashTagText const* (*get_text)(haxorg_HashTag const*);
};

struct haxorg_InlineFootnote_vtable {
  haxorg_HstdStr const* (*get_tag)(haxorg_InlineFootnote const*);
  haxorg_HstdOpt const* (*get_definition)(haxorg_InlineFootnote const*);
};

struct haxorg_InlineExport_vtable {
  haxorg_HstdStr const* (*get_exporter)(haxorg_InlineExport const*);
  haxorg_HstdStr const* (*get_content)(haxorg_InlineExport const*);
};

struct haxorg_ImmCmd_vtable {
  haxorg_AttrGroup const* (*get_attrs)(haxorg_ImmCmd const*);
};

struct haxorg_ImmCmdCustomRaw_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_ImmCmdCustomRaw const*);
  bool const* (*get_isAttached)(haxorg_ImmCmdCustomRaw const*);
  haxorg_HstdStr const* (*get_text)(haxorg_ImmCmdCustomRaw const*);
};

struct haxorg_ImmCmdCustomText_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_ImmCmdCustomText const*);
  bool const* (*get_isAttached)(haxorg_ImmCmdCustomText const*);
  haxorg_ImmId const* (*get_text)(haxorg_ImmCmdCustomText const*);
};

struct haxorg_ImmLink_vtable {
  haxorg_HstdOpt const* (*get_description)(haxorg_ImmLink const*);
  haxorg_LinkTarget const* (*get_target)(haxorg_ImmLink const*);
};

struct haxorg_ImmHashTag_vtable {
  haxorg_HashTagText const* (*get_text)(haxorg_ImmHashTag const*);
};

struct haxorg_ImmInlineFootnote_vtable {
  haxorg_HstdStr const* (*get_tag)(haxorg_ImmInlineFootnote const*);
  haxorg_HstdOpt const* (*get_definition)(haxorg_ImmInlineFootnote const*);
};

struct haxorg_ImmInlineExport_vtable {
  haxorg_HstdStr const* (*get_exporter)(haxorg_ImmInlineExport const*);
  haxorg_HstdStr const* (*get_content)(haxorg_ImmInlineExport const*);
};

struct haxorg_CmdCreator_vtable {
  haxorg_SemId const* (*get_text)(haxorg_CmdCreator const*);
};

struct haxorg_CmdAuthor_vtable {
  haxorg_SemId const* (*get_text)(haxorg_CmdAuthor const*);
};

struct haxorg_CmdEmail_vtable {
  haxorg_HstdStr const* (*get_text)(haxorg_CmdEmail const*);
};

struct haxorg_CmdLanguage_vtable {
  haxorg_HstdStr const* (*get_text)(haxorg_CmdLanguage const*);
};

struct haxorg_CmdCustomArgs_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_CmdCustomArgs const*);
  bool const* (*get_isAttached)(haxorg_CmdCustomArgs const*);
};

struct haxorg_CmdTblfm_vtable {
  haxorg_Tblfm const* (*get_expr)(haxorg_CmdTblfm const*);
};

struct haxorg_Cell_vtable {
  bool const* (*get_isBlock)(haxorg_Cell const*);
};

struct haxorg_Row_vtable {
  haxorg_HstdVec const* (*get_cells)(haxorg_Row const*);
  bool const* (*get_isBlock)(haxorg_Row const*);
};

struct haxorg_ImmCmdCreator_vtable {
  haxorg_ImmId const* (*get_text)(haxorg_ImmCmdCreator const*);
};

struct haxorg_ImmCmdAuthor_vtable {
  haxorg_ImmId const* (*get_text)(haxorg_ImmCmdAuthor const*);
};

struct haxorg_ImmCmdEmail_vtable {
  haxorg_HstdStr const* (*get_text)(haxorg_ImmCmdEmail const*);
};

struct haxorg_ImmCmdLanguage_vtable {
  haxorg_HstdStr const* (*get_text)(haxorg_ImmCmdLanguage const*);
};

struct haxorg_ImmCmdCustomArgs_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_ImmCmdCustomArgs const*);
  bool const* (*get_isAttached)(haxorg_ImmCmdCustomArgs const*);
};

struct haxorg_ImmCmdTblfm_vtable {
  haxorg_Tblfm const* (*get_expr)(haxorg_ImmCmdTblfm const*);
};

struct haxorg_ImmCell_vtable {
  bool const* (*get_isBlock)(haxorg_ImmCell const*);
};

struct haxorg_ImmRow_vtable {
  haxorg_ImmVec const* (*get_cells)(haxorg_ImmRow const*);
  bool const* (*get_isBlock)(haxorg_ImmRow const*);
};

struct haxorg_BlockDynamicFallback_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_BlockDynamicFallback const*);
};

struct haxorg_BlockExport_vtable {
  haxorg_HstdStr const* (*get_exporter)(haxorg_BlockExport const*);
  haxorg_HstdStr const* (*get_content)(haxorg_BlockExport const*);
};

struct haxorg_BlockCodeEvalResult_vtable {
  haxorg_HstdVec const* (*get_raw)(haxorg_BlockCodeEvalResult const*);
  haxorg_SemId const* (*get_node)(haxorg_BlockCodeEvalResult const*);
};

struct haxorg_BlockCode_vtable {
  haxorg_HstdOpt const* (*get_lang)(haxorg_BlockCode const*);
  haxorg_HstdVec const* (*get_result)(haxorg_BlockCode const*);
  haxorg_HstdVec const* (*get_lines)(haxorg_BlockCode const*);
  haxorg_AttrGroup const* (*get_switches)(haxorg_BlockCode const*);
};

struct haxorg_Table_vtable {
  haxorg_HstdVec const* (*get_rows)(haxorg_Table const*);
  bool const* (*get_isBlock)(haxorg_Table const*);
};

struct haxorg_ImmBlockDynamicFallback_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_ImmBlockDynamicFallback const*);
};

struct haxorg_ImmBlockExport_vtable {
  haxorg_HstdStr const* (*get_exporter)(haxorg_ImmBlockExport const*);
  haxorg_HstdStr const* (*get_content)(haxorg_ImmBlockExport const*);
};

struct haxorg_ImmBlockCodeEvalResult_vtable {
  haxorg_ImmVec const* (*get_raw)(haxorg_ImmBlockCodeEvalResult const*);
  haxorg_ImmId const* (*get_node)(haxorg_ImmBlockCodeEvalResult const*);
};

struct haxorg_ImmBlockCode_vtable {
  haxorg_HstdOpt const* (*get_lang)(haxorg_ImmBlockCode const*);
  haxorg_ImmVec const* (*get_result)(haxorg_ImmBlockCode const*);
  haxorg_ImmVec const* (*get_lines)(haxorg_ImmBlockCode const*);
  haxorg_AttrGroup const* (*get_switches)(haxorg_ImmBlockCode const*);
};

struct haxorg_ImmTable_vtable {
  haxorg_ImmVec const* (*get_rows)(haxorg_ImmTable const*);
  bool const* (*get_isBlock)(haxorg_ImmTable const*);
};

struct haxorg_CmdCaption_vtable {
  haxorg_SemId const* (*get_text)(haxorg_CmdCaption const*);
};

struct haxorg_CmdColumns_vtable {
  haxorg_ColumnView const* (*get_view)(haxorg_CmdColumns const*);
};

struct haxorg_CmdName_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_CmdName const*);
};

struct haxorg_CmdCall_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_CmdCall const*);
  haxorg_HstdOpt const* (*get_fileName)(haxorg_CmdCall const*);
  haxorg_AttrGroup const* (*get_insideHeaderAttrs)(haxorg_CmdCall const*);
  haxorg_AttrGroup const* (*get_callAttrs)(haxorg_CmdCall const*);
  haxorg_AttrGroup const* (*get_endHeaderAttrs)(haxorg_CmdCall const*);
  haxorg_HstdVec const* (*get_result)(haxorg_CmdCall const*);
};

struct haxorg_CmdAttr_vtable {
  haxorg_HstdStr const* (*get_target)(haxorg_CmdAttr const*);
};

struct haxorg_CmdExport_vtable {
  haxorg_HstdStr const* (*get_exporter)(haxorg_CmdExport const*);
  haxorg_HstdStr const* (*get_content)(haxorg_CmdExport const*);
};

struct haxorg_ImmCmdCaption_vtable {
  haxorg_ImmId const* (*get_text)(haxorg_ImmCmdCaption const*);
};

struct haxorg_ImmCmdColumns_vtable {
  haxorg_ColumnView const* (*get_view)(haxorg_ImmCmdColumns const*);
};

struct haxorg_ImmCmdName_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_ImmCmdName const*);
};

struct haxorg_ImmCmdCall_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_ImmCmdCall const*);
  haxorg_HstdOpt const* (*get_fileName)(haxorg_ImmCmdCall const*);
  haxorg_AttrGroup const* (*get_insideHeaderAttrs)(haxorg_ImmCmdCall const*);
  haxorg_AttrGroup const* (*get_callAttrs)(haxorg_ImmCmdCall const*);
  haxorg_AttrGroup const* (*get_endHeaderAttrs)(haxorg_ImmCmdCall const*);
  haxorg_ImmVec const* (*get_result)(haxorg_ImmCmdCall const*);
};

struct haxorg_ImmCmdAttr_vtable {
  haxorg_HstdStr const* (*get_target)(haxorg_ImmCmdAttr const*);
};

struct haxorg_ImmCmdExport_vtable {
  haxorg_HstdStr const* (*get_exporter)(haxorg_ImmCmdExport const*);
  haxorg_HstdStr const* (*get_content)(haxorg_ImmCmdExport const*);
};

void haxorg_destroy_UserTimeBreakdown(haxorg_UserTimeBreakdown* obj);
void haxorg_destroy_UserTime(haxorg_UserTime* obj);
void haxorg_destroy_ParseSourceFileId(haxorg_ParseSourceFileId* obj);
void haxorg_destroy_ParseSourceLoc(haxorg_ParseSourceLoc* obj);
void haxorg_destroy_OrgJson(haxorg_OrgJson* obj);
void haxorg_destroy_Org(haxorg_Org* obj);
void haxorg_destroy_OperationsTracer(haxorg_OperationsTracer* obj);
void haxorg_destroy_Cache(haxorg_Cache* obj);
void haxorg_destroy_ParseOrgParseFragment(haxorg_ParseOrgParseFragment* obj);
void haxorg_destroy_OrgParseParameters(haxorg_OrgParseParameters* obj);
void haxorg_destroy_OrgDirectoryParseParameters(haxorg_OrgDirectoryParseParameters* obj);
void haxorg_destroy_ParseContext(haxorg_ParseContext* obj);
void haxorg_destroy_ImmReflFieldId(haxorg_ImmReflFieldId* obj);
void haxorg_destroy_ImmId(haxorg_ImmId* obj);
void haxorg_destroy_ImmOrg(haxorg_ImmOrg* obj);
void haxorg_destroy_ImmPathStep(haxorg_ImmPathStep* obj);
void haxorg_destroy_ImmPath(haxorg_ImmPath* obj);
void haxorg_destroy_ImmUniqId(haxorg_ImmUniqId* obj);
void haxorg_destroy_ImmAstReplaceEpoch(haxorg_ImmAstReplaceEpoch* obj);
void haxorg_destroy_ImmAstContext(haxorg_ImmAstContext* obj);
void haxorg_destroy_ImmAstVersion(haxorg_ImmAstVersion* obj);
void haxorg_destroy_ImmAdapterTreeReprConf(haxorg_ImmAdapterTreeReprConf* obj);
void haxorg_destroy_ImmAdapter(haxorg_ImmAdapter* obj);
void haxorg_destroy_ImmAdapterVirtualBase(haxorg_ImmAdapterVirtualBase* obj);
void haxorg_destroy_OrgYamlExportOpts(haxorg_OrgYamlExportOpts* obj);
void haxorg_destroy_OrgTreeExportOpts(haxorg_OrgTreeExportOpts* obj);
void haxorg_destroy_AstTrackingPath(haxorg_AstTrackingPath* obj);
void haxorg_destroy_AstTrackingAlternatives(haxorg_AstTrackingAlternatives* obj);
void haxorg_destroy_AstTrackingGroupRadioTarget(haxorg_AstTrackingGroupRadioTarget* obj);
void haxorg_destroy_AstTrackingGroupSingle(haxorg_AstTrackingGroupSingle* obj);
void haxorg_destroy_AstTrackingGroupTrackedHashtag(haxorg_AstTrackingGroupTrackedHashtag* obj);
void haxorg_destroy_AstTrackingGroup(haxorg_AstTrackingGroup* obj);
void haxorg_destroy_AstTrackingMap(haxorg_AstTrackingMap* obj);
void haxorg_destroy_SequenceSegment(haxorg_SequenceSegment* obj);
void haxorg_destroy_SequenceSegmentGroup(haxorg_SequenceSegmentGroup* obj);
void haxorg_destroy_SequenceAnnotationTag(haxorg_SequenceAnnotationTag* obj);
void haxorg_destroy_SequenceAnnotation(haxorg_SequenceAnnotation* obj);
void haxorg_destroy_GraphMapLinkLink(haxorg_GraphMapLinkLink* obj);
void haxorg_destroy_GraphMapLinkRadio(haxorg_GraphMapLinkRadio* obj);
void haxorg_destroy_GraphMapLink(haxorg_GraphMapLink* obj);
void haxorg_destroy_GraphMapNodeProp(haxorg_GraphMapNodeProp* obj);
void haxorg_destroy_GraphMapEdgeProp(haxorg_GraphMapEdgeProp* obj);
void haxorg_destroy_GraphMapNode(haxorg_GraphMapNode* obj);
void haxorg_destroy_GraphMapEdge(haxorg_GraphMapEdge* obj);
void haxorg_destroy_GraphMapGraph(haxorg_GraphMapGraph* obj);
void haxorg_destroy_GraphMapConfig(haxorg_GraphMapConfig* obj);
void haxorg_destroy_GraphMapGraphState(haxorg_GraphMapGraphState* obj);
void haxorg_destroy_LispCodeCall(haxorg_LispCodeCall* obj);
void haxorg_destroy_LispCodeList(haxorg_LispCodeList* obj);
void haxorg_destroy_LispCodeKeyValue(haxorg_LispCodeKeyValue* obj);
void haxorg_destroy_LispCodeNumber(haxorg_LispCodeNumber* obj);
void haxorg_destroy_LispCodeText(haxorg_LispCodeText* obj);
void haxorg_destroy_LispCodeIdent(haxorg_LispCodeIdent* obj);
void haxorg_destroy_LispCodeBoolean(haxorg_LispCodeBoolean* obj);
void haxorg_destroy_LispCodeReal(haxorg_LispCodeReal* obj);
void haxorg_destroy_LispCode(haxorg_LispCode* obj);
void haxorg_destroy_TblfmExprAxisRefPositionIndex(haxorg_TblfmExprAxisRefPositionIndex* obj);
void haxorg_destroy_TblfmExprAxisRefPositionName(haxorg_TblfmExprAxisRefPositionName* obj);
void haxorg_destroy_TblfmExprAxisRefPosition(haxorg_TblfmExprAxisRefPosition* obj);
void haxorg_destroy_TblfmExprAxisRef(haxorg_TblfmExprAxisRef* obj);
void haxorg_destroy_TblfmExprAxisName(haxorg_TblfmExprAxisName* obj);
void haxorg_destroy_TblfmExprIntLiteral(haxorg_TblfmExprIntLiteral* obj);
void haxorg_destroy_TblfmExprFloatLiteral(haxorg_TblfmExprFloatLiteral* obj);
void haxorg_destroy_TblfmExprRangeRef(haxorg_TblfmExprRangeRef* obj);
void haxorg_destroy_TblfmExprCall(haxorg_TblfmExprCall* obj);
void haxorg_destroy_TblfmExprElisp(haxorg_TblfmExprElisp* obj);
void haxorg_destroy_TblfmExpr(haxorg_TblfmExpr* obj);
void haxorg_destroy_TblfmAssign(haxorg_TblfmAssign* obj);
void haxorg_destroy_Tblfm(haxorg_Tblfm* obj);
void haxorg_destroy_AttrValueDimensionSpan(haxorg_AttrValueDimensionSpan* obj);
void haxorg_destroy_AttrValueTextValue(haxorg_AttrValueTextValue* obj);
void haxorg_destroy_AttrValueFileReference(haxorg_AttrValueFileReference* obj);
void haxorg_destroy_AttrValueLispValue(haxorg_AttrValueLispValue* obj);
void haxorg_destroy_AttrValue(haxorg_AttrValue* obj);
void haxorg_destroy_HashTagFlat(haxorg_HashTagFlat* obj);
void haxorg_destroy_TodoKeyword(haxorg_TodoKeyword* obj);
void haxorg_destroy_HashTagText(haxorg_HashTagText* obj);
void haxorg_destroy_SubtreePath(haxorg_SubtreePath* obj);
void haxorg_destroy_LinkTargetRaw(haxorg_LinkTargetRaw* obj);
void haxorg_destroy_LinkTargetId(haxorg_LinkTargetId* obj);
void haxorg_destroy_LinkTargetCustomId(haxorg_LinkTargetCustomId* obj);
void haxorg_destroy_LinkTargetSubtreeTitle(haxorg_LinkTargetSubtreeTitle* obj);
void haxorg_destroy_LinkTargetPerson(haxorg_LinkTargetPerson* obj);
void haxorg_destroy_LinkTargetUserProtocol(haxorg_LinkTargetUserProtocol* obj);
void haxorg_destroy_LinkTargetInternal(haxorg_LinkTargetInternal* obj);
void haxorg_destroy_LinkTargetFootnote(haxorg_LinkTargetFootnote* obj);
void haxorg_destroy_LinkTargetFile(haxorg_LinkTargetFile* obj);
void haxorg_destroy_LinkTargetAttachment(haxorg_LinkTargetAttachment* obj);
void haxorg_destroy_LinkTarget(haxorg_LinkTarget* obj);
void haxorg_destroy_SubtreeLogHeadPriority(haxorg_SubtreeLogHeadPriority* obj);
void haxorg_destroy_SubtreeLogHeadNote(haxorg_SubtreeLogHeadNote* obj);
void haxorg_destroy_SubtreeLogHeadRefile(haxorg_SubtreeLogHeadRefile* obj);
void haxorg_destroy_SubtreeLogHeadClock(haxorg_SubtreeLogHeadClock* obj);
void haxorg_destroy_SubtreeLogHeadState(haxorg_SubtreeLogHeadState* obj);
void haxorg_destroy_SubtreeLogHeadDeadline(haxorg_SubtreeLogHeadDeadline* obj);
void haxorg_destroy_SubtreeLogHeadSchedule(haxorg_SubtreeLogHeadSchedule* obj);
void haxorg_destroy_SubtreeLogHeadTag(haxorg_SubtreeLogHeadTag* obj);
void haxorg_destroy_SubtreeLogHeadUnknown(haxorg_SubtreeLogHeadUnknown* obj);
void haxorg_destroy_SubtreeLogHead(haxorg_SubtreeLogHead* obj);
void haxorg_destroy_SubtreeCompletion(haxorg_SubtreeCompletion* obj);
void haxorg_destroy_AttrList(haxorg_AttrList* obj);
void haxorg_destroy_AttrGroup(haxorg_AttrGroup* obj);
void haxorg_destroy_OrgCodeEvalInputVar(haxorg_OrgCodeEvalInputVar* obj);
void haxorg_destroy_OrgCodeEvalInput(haxorg_OrgCodeEvalInput* obj);
void haxorg_destroy_OrgCodeEvalOutput(haxorg_OrgCodeEvalOutput* obj);
void haxorg_destroy_ColumnViewSummaryCheckboxAggregate(haxorg_ColumnViewSummaryCheckboxAggregate* obj);
void haxorg_destroy_ColumnViewSummaryMathAggregate(haxorg_ColumnViewSummaryMathAggregate* obj);
void haxorg_destroy_ColumnViewSummary(haxorg_ColumnViewSummary* obj);
void haxorg_destroy_ColumnViewColumn(haxorg_ColumnViewColumn* obj);
void haxorg_destroy_ColumnView(haxorg_ColumnView* obj);
void haxorg_destroy_BlockCodeLinePartRaw(haxorg_BlockCodeLinePartRaw* obj);
void haxorg_destroy_BlockCodeLinePartCallout(haxorg_BlockCodeLinePartCallout* obj);
void haxorg_destroy_BlockCodeLinePartTangle(haxorg_BlockCodeLinePartTangle* obj);
void haxorg_destroy_BlockCodeLinePart(haxorg_BlockCodeLinePart* obj);
void haxorg_destroy_BlockCodeLine(haxorg_BlockCodeLine* obj);
void haxorg_destroy_DocumentExportConfigTaskExport(haxorg_DocumentExportConfigTaskExport* obj);
void haxorg_destroy_DocumentExportConfigDoExport(haxorg_DocumentExportConfigDoExport* obj);
void haxorg_destroy_DocumentExportConfigExportFixed(haxorg_DocumentExportConfigExportFixed* obj);
void haxorg_destroy_DocumentExportConfig(haxorg_DocumentExportConfig* obj);
void haxorg_destroy_SubtreePeriod(haxorg_SubtreePeriod* obj);
void haxorg_destroy_NamedPropertyNonblocking(haxorg_NamedPropertyNonblocking* obj);
void haxorg_destroy_NamedPropertyArchiveTime(haxorg_NamedPropertyArchiveTime* obj);
void haxorg_destroy_NamedPropertyArchiveFile(haxorg_NamedPropertyArchiveFile* obj);
void haxorg_destroy_NamedPropertyArchiveOlpath(haxorg_NamedPropertyArchiveOlpath* obj);
void haxorg_destroy_NamedPropertyArchiveTarget(haxorg_NamedPropertyArchiveTarget* obj);
void haxorg_destroy_NamedPropertyArchiveCategory(haxorg_NamedPropertyArchiveCategory* obj);
void haxorg_destroy_NamedPropertyArchiveTodo(haxorg_NamedPropertyArchiveTodo* obj);
void haxorg_destroy_NamedPropertyTrigger(haxorg_NamedPropertyTrigger* obj);
void haxorg_destroy_NamedPropertyExportLatexClass(haxorg_NamedPropertyExportLatexClass* obj);
void haxorg_destroy_NamedPropertyCookieData(haxorg_NamedPropertyCookieData* obj);
void haxorg_destroy_NamedPropertyExportLatexClassOptions(haxorg_NamedPropertyExportLatexClassOptions* obj);
void haxorg_destroy_NamedPropertyExportLatexHeader(haxorg_NamedPropertyExportLatexHeader* obj);
void haxorg_destroy_NamedPropertyExportLatexCompiler(haxorg_NamedPropertyExportLatexCompiler* obj);
void haxorg_destroy_NamedPropertyOrdered(haxorg_NamedPropertyOrdered* obj);
void haxorg_destroy_NamedPropertyEffort(haxorg_NamedPropertyEffort* obj);
void haxorg_destroy_NamedPropertyVisibility(haxorg_NamedPropertyVisibility* obj);
void haxorg_destroy_NamedPropertyExportOptions(haxorg_NamedPropertyExportOptions* obj);
void haxorg_destroy_NamedPropertyBlocker(haxorg_NamedPropertyBlocker* obj);
void haxorg_destroy_NamedPropertyUnnumbered(haxorg_NamedPropertyUnnumbered* obj);
void haxorg_destroy_NamedPropertyCreated(haxorg_NamedPropertyCreated* obj);
void haxorg_destroy_NamedPropertyRadioId(haxorg_NamedPropertyRadioId* obj);
void haxorg_destroy_NamedPropertyHashtagDef(haxorg_NamedPropertyHashtagDef* obj);
void haxorg_destroy_NamedPropertyCustomArgs(haxorg_NamedPropertyCustomArgs* obj);
void haxorg_destroy_NamedPropertyCustomRaw(haxorg_NamedPropertyCustomRaw* obj);
void haxorg_destroy_NamedPropertyCustomId(haxorg_NamedPropertyCustomId* obj);
void haxorg_destroy_NamedPropertyCustomSubtreeJson(haxorg_NamedPropertyCustomSubtreeJson* obj);
void haxorg_destroy_NamedPropertyCustomSubtreeFlags(haxorg_NamedPropertyCustomSubtreeFlags* obj);
void haxorg_destroy_NamedProperty(haxorg_NamedProperty* obj);
void haxorg_destroy_OrgDiagnosticsParseTokenError(haxorg_OrgDiagnosticsParseTokenError* obj);
void haxorg_destroy_OrgDiagnosticsParseError(haxorg_OrgDiagnosticsParseError* obj);
void haxorg_destroy_OrgDiagnosticsIncludeError(haxorg_OrgDiagnosticsIncludeError* obj);
void haxorg_destroy_OrgDiagnosticsConvertError(haxorg_OrgDiagnosticsConvertError* obj);
void haxorg_destroy_OrgDiagnosticsInternalError(haxorg_OrgDiagnosticsInternalError* obj);
void haxorg_destroy_OrgDiagnostics(haxorg_OrgDiagnostics* obj);
void haxorg_destroy_NoNode(haxorg_NoNode* obj);
void haxorg_destroy_ErrorItem(haxorg_ErrorItem* obj);
void haxorg_destroy_ErrorGroup(haxorg_ErrorGroup* obj);
void haxorg_destroy_Stmt(haxorg_Stmt* obj);
void haxorg_destroy_Inline(haxorg_Inline* obj);
void haxorg_destroy_StmtList(haxorg_StmtList* obj);
void haxorg_destroy_Empty(haxorg_Empty* obj);
void haxorg_destroy_Leaf(haxorg_Leaf* obj);
void haxorg_destroy_TimeRepeat(haxorg_TimeRepeat* obj);
void haxorg_destroy_TimeStatic(haxorg_TimeStatic* obj);
void haxorg_destroy_TimeDynamic(haxorg_TimeDynamic* obj);
void haxorg_destroy_Time(haxorg_Time* obj);
void haxorg_destroy_TimeRange(haxorg_TimeRange* obj);
void haxorg_destroy_Macro(haxorg_Macro* obj);
void haxorg_destroy_SymbolParam(haxorg_SymbolParam* obj);
void haxorg_destroy_Symbol(haxorg_Symbol* obj);
void haxorg_destroy_ErrorSkipGroup(haxorg_ErrorSkipGroup* obj);
void haxorg_destroy_Markup(haxorg_Markup* obj);
void haxorg_destroy_RadioTarget(haxorg_RadioTarget* obj);
void haxorg_destroy_Latex(haxorg_Latex* obj);
void haxorg_destroy_SubtreeLog(haxorg_SubtreeLog* obj);
void haxorg_destroy_Subtree(haxorg_Subtree* obj);
void haxorg_destroy_ColonExample(haxorg_ColonExample* obj);
void haxorg_destroy_Call(haxorg_Call* obj);
void haxorg_destroy_ListItem(haxorg_ListItem* obj);
void haxorg_destroy_DocumentOptions(haxorg_DocumentOptions* obj);
void haxorg_destroy_DocumentFragment(haxorg_DocumentFragment* obj);
void haxorg_destroy_CriticMarkup(haxorg_CriticMarkup* obj);
void haxorg_destroy_Document(haxorg_Document* obj);
void haxorg_destroy_FileTarget(haxorg_FileTarget* obj);
void haxorg_destroy_TextSeparator(haxorg_TextSeparator* obj);
void haxorg_destroy_DocumentGroup(haxorg_DocumentGroup* obj);
void haxorg_destroy_FileDocument(haxorg_FileDocument* obj);
void haxorg_destroy_FileAttachment(haxorg_FileAttachment* obj);
void haxorg_destroy_FileSource(haxorg_FileSource* obj);
void haxorg_destroy_File(haxorg_File* obj);
void haxorg_destroy_Directory(haxorg_Directory* obj);
void haxorg_destroy_Symlink(haxorg_Symlink* obj);
void haxorg_destroy_CmdIncludeIncludeBase(haxorg_CmdIncludeIncludeBase* obj);
void haxorg_destroy_CmdIncludeExample(haxorg_CmdIncludeExample* obj);
void haxorg_destroy_CmdIncludeExport(haxorg_CmdIncludeExport* obj);
void haxorg_destroy_CmdIncludeCustom(haxorg_CmdIncludeCustom* obj);
void haxorg_destroy_CmdIncludeSrc(haxorg_CmdIncludeSrc* obj);
void haxorg_destroy_CmdIncludeOrgDocument(haxorg_CmdIncludeOrgDocument* obj);
void haxorg_destroy_CmdInclude(haxorg_CmdInclude* obj);
void haxorg_destroy_ImmNoNode(haxorg_ImmNoNode* obj);
void haxorg_destroy_ImmErrorItem(haxorg_ImmErrorItem* obj);
void haxorg_destroy_ImmErrorGroup(haxorg_ImmErrorGroup* obj);
void haxorg_destroy_ImmStmt(haxorg_ImmStmt* obj);
void haxorg_destroy_ImmInline(haxorg_ImmInline* obj);
void haxorg_destroy_ImmStmtList(haxorg_ImmStmtList* obj);
void haxorg_destroy_ImmEmpty(haxorg_ImmEmpty* obj);
void haxorg_destroy_ImmLeaf(haxorg_ImmLeaf* obj);
void haxorg_destroy_ImmTimeRepeat(haxorg_ImmTimeRepeat* obj);
void haxorg_destroy_ImmTimeStatic(haxorg_ImmTimeStatic* obj);
void haxorg_destroy_ImmTimeDynamic(haxorg_ImmTimeDynamic* obj);
void haxorg_destroy_ImmTime(haxorg_ImmTime* obj);
void haxorg_destroy_ImmTimeRange(haxorg_ImmTimeRange* obj);
void haxorg_destroy_ImmMacro(haxorg_ImmMacro* obj);
void haxorg_destroy_ImmSymbolParam(haxorg_ImmSymbolParam* obj);
void haxorg_destroy_ImmSymbol(haxorg_ImmSymbol* obj);
void haxorg_destroy_ImmErrorSkipGroup(haxorg_ImmErrorSkipGroup* obj);
void haxorg_destroy_ImmMarkup(haxorg_ImmMarkup* obj);
void haxorg_destroy_ImmRadioTarget(haxorg_ImmRadioTarget* obj);
void haxorg_destroy_ImmLatex(haxorg_ImmLatex* obj);
void haxorg_destroy_ImmSubtreeLog(haxorg_ImmSubtreeLog* obj);
void haxorg_destroy_ImmSubtree(haxorg_ImmSubtree* obj);
void haxorg_destroy_ImmColonExample(haxorg_ImmColonExample* obj);
void haxorg_destroy_ImmCall(haxorg_ImmCall* obj);
void haxorg_destroy_ImmListItem(haxorg_ImmListItem* obj);
void haxorg_destroy_ImmDocumentOptions(haxorg_ImmDocumentOptions* obj);
void haxorg_destroy_ImmDocumentFragment(haxorg_ImmDocumentFragment* obj);
void haxorg_destroy_ImmCriticMarkup(haxorg_ImmCriticMarkup* obj);
void haxorg_destroy_ImmDocument(haxorg_ImmDocument* obj);
void haxorg_destroy_ImmFileTarget(haxorg_ImmFileTarget* obj);
void haxorg_destroy_ImmTextSeparator(haxorg_ImmTextSeparator* obj);
void haxorg_destroy_ImmDocumentGroup(haxorg_ImmDocumentGroup* obj);
void haxorg_destroy_ImmFileDocument(haxorg_ImmFileDocument* obj);
void haxorg_destroy_ImmFileAttachment(haxorg_ImmFileAttachment* obj);
void haxorg_destroy_ImmFileSource(haxorg_ImmFileSource* obj);
void haxorg_destroy_ImmFile(haxorg_ImmFile* obj);
void haxorg_destroy_ImmDirectory(haxorg_ImmDirectory* obj);
void haxorg_destroy_ImmSymlink(haxorg_ImmSymlink* obj);
void haxorg_destroy_ImmCmdIncludeIncludeBase(haxorg_ImmCmdIncludeIncludeBase* obj);
void haxorg_destroy_ImmCmdIncludeExample(haxorg_ImmCmdIncludeExample* obj);
void haxorg_destroy_ImmCmdIncludeExport(haxorg_ImmCmdIncludeExport* obj);
void haxorg_destroy_ImmCmdIncludeCustom(haxorg_ImmCmdIncludeCustom* obj);
void haxorg_destroy_ImmCmdIncludeSrc(haxorg_ImmCmdIncludeSrc* obj);
void haxorg_destroy_ImmCmdIncludeOrgDocument(haxorg_ImmCmdIncludeOrgDocument* obj);
void haxorg_destroy_ImmCmdInclude(haxorg_ImmCmdInclude* obj);
void haxorg_destroy_ImmAdapterOrgAPI(haxorg_ImmAdapterOrgAPI* obj);
void haxorg_destroy_Cmd(haxorg_Cmd* obj);
void haxorg_destroy_CmdCustomRaw(haxorg_CmdCustomRaw* obj);
void haxorg_destroy_CmdCustomText(haxorg_CmdCustomText* obj);
void haxorg_destroy_Link(haxorg_Link* obj);
void haxorg_destroy_BlockComment(haxorg_BlockComment* obj);
void haxorg_destroy_Paragraph(haxorg_Paragraph* obj);
void haxorg_destroy_List(haxorg_List* obj);
void haxorg_destroy_HashTag(haxorg_HashTag* obj);
void haxorg_destroy_InlineFootnote(haxorg_InlineFootnote* obj);
void haxorg_destroy_InlineExport(haxorg_InlineExport* obj);
void haxorg_destroy_Escaped(haxorg_Escaped* obj);
void haxorg_destroy_Newline(haxorg_Newline* obj);
void haxorg_destroy_Space(haxorg_Space* obj);
void haxorg_destroy_Word(haxorg_Word* obj);
void haxorg_destroy_AtMention(haxorg_AtMention* obj);
void haxorg_destroy_RawText(haxorg_RawText* obj);
void haxorg_destroy_Punctuation(haxorg_Punctuation* obj);
void haxorg_destroy_Placeholder(haxorg_Placeholder* obj);
void haxorg_destroy_BigIdent(haxorg_BigIdent* obj);
void haxorg_destroy_TextTarget(haxorg_TextTarget* obj);
void haxorg_destroy_ErrorSkipToken(haxorg_ErrorSkipToken* obj);
void haxorg_destroy_Bold(haxorg_Bold* obj);
void haxorg_destroy_Underline(haxorg_Underline* obj);
void haxorg_destroy_Monospace(haxorg_Monospace* obj);
void haxorg_destroy_MarkQuote(haxorg_MarkQuote* obj);
void haxorg_destroy_Verbatim(haxorg_Verbatim* obj);
void haxorg_destroy_Italic(haxorg_Italic* obj);
void haxorg_destroy_Strike(haxorg_Strike* obj);
void haxorg_destroy_Par(haxorg_Par* obj);
void haxorg_destroy_ImmCmd(haxorg_ImmCmd* obj);
void haxorg_destroy_ImmCmdCustomRaw(haxorg_ImmCmdCustomRaw* obj);
void haxorg_destroy_ImmCmdCustomText(haxorg_ImmCmdCustomText* obj);
void haxorg_destroy_ImmLink(haxorg_ImmLink* obj);
void haxorg_destroy_ImmBlockComment(haxorg_ImmBlockComment* obj);
void haxorg_destroy_ImmParagraph(haxorg_ImmParagraph* obj);
void haxorg_destroy_ImmList(haxorg_ImmList* obj);
void haxorg_destroy_ImmHashTag(haxorg_ImmHashTag* obj);
void haxorg_destroy_ImmInlineFootnote(haxorg_ImmInlineFootnote* obj);
void haxorg_destroy_ImmInlineExport(haxorg_ImmInlineExport* obj);
void haxorg_destroy_ImmEscaped(haxorg_ImmEscaped* obj);
void haxorg_destroy_ImmNewline(haxorg_ImmNewline* obj);
void haxorg_destroy_ImmSpace(haxorg_ImmSpace* obj);
void haxorg_destroy_ImmWord(haxorg_ImmWord* obj);
void haxorg_destroy_ImmAtMention(haxorg_ImmAtMention* obj);
void haxorg_destroy_ImmRawText(haxorg_ImmRawText* obj);
void haxorg_destroy_ImmPunctuation(haxorg_ImmPunctuation* obj);
void haxorg_destroy_ImmPlaceholder(haxorg_ImmPlaceholder* obj);
void haxorg_destroy_ImmBigIdent(haxorg_ImmBigIdent* obj);
void haxorg_destroy_ImmTextTarget(haxorg_ImmTextTarget* obj);
void haxorg_destroy_ImmErrorSkipToken(haxorg_ImmErrorSkipToken* obj);
void haxorg_destroy_ImmBold(haxorg_ImmBold* obj);
void haxorg_destroy_ImmUnderline(haxorg_ImmUnderline* obj);
void haxorg_destroy_ImmMonospace(haxorg_ImmMonospace* obj);
void haxorg_destroy_ImmMarkQuote(haxorg_ImmMarkQuote* obj);
void haxorg_destroy_ImmVerbatim(haxorg_ImmVerbatim* obj);
void haxorg_destroy_ImmItalic(haxorg_ImmItalic* obj);
void haxorg_destroy_ImmStrike(haxorg_ImmStrike* obj);
void haxorg_destroy_ImmPar(haxorg_ImmPar* obj);
void haxorg_destroy_ImmAdapterStmtAPI(haxorg_ImmAdapterStmtAPI* obj);
void haxorg_destroy_ImmAdapterSubtreeAPI(haxorg_ImmAdapterSubtreeAPI* obj);
void haxorg_destroy_ImmAdapterNoNodeAPI(haxorg_ImmAdapterNoNodeAPI* obj);
void haxorg_destroy_ImmAdapterAttrAPI(haxorg_ImmAdapterAttrAPI* obj);
void haxorg_destroy_ImmAdapterAttrListAPI(haxorg_ImmAdapterAttrListAPI* obj);
void haxorg_destroy_ImmAdapterAttrsAPI(haxorg_ImmAdapterAttrsAPI* obj);
void haxorg_destroy_ImmAdapterErrorItemAPI(haxorg_ImmAdapterErrorItemAPI* obj);
void haxorg_destroy_ImmAdapterErrorGroupAPI(haxorg_ImmAdapterErrorGroupAPI* obj);
void haxorg_destroy_ImmAdapterErrorSkipGroupAPI(haxorg_ImmAdapterErrorSkipGroupAPI* obj);
void haxorg_destroy_ImmAdapterErrorSkipTokenAPI(haxorg_ImmAdapterErrorSkipTokenAPI* obj);
void haxorg_destroy_ImmAdapterStmtListAPI(haxorg_ImmAdapterStmtListAPI* obj);
void haxorg_destroy_ImmAdapterEmptyAPI(haxorg_ImmAdapterEmptyAPI* obj);
void haxorg_destroy_ImmAdapterInlineAPI(haxorg_ImmAdapterInlineAPI* obj);
void haxorg_destroy_ImmAdapterTimeAPI(haxorg_ImmAdapterTimeAPI* obj);
void haxorg_destroy_ImmAdapterTimeRangeAPI(haxorg_ImmAdapterTimeRangeAPI* obj);
void haxorg_destroy_ImmAdapterMacroAPI(haxorg_ImmAdapterMacroAPI* obj);
void haxorg_destroy_ImmAdapterSymbolAPI(haxorg_ImmAdapterSymbolAPI* obj);
void haxorg_destroy_ImmAdapterLeafAPI(haxorg_ImmAdapterLeafAPI* obj);
void haxorg_destroy_ImmAdapterMarkupAPI(haxorg_ImmAdapterMarkupAPI* obj);
void haxorg_destroy_ImmAdapterLatexAPI(haxorg_ImmAdapterLatexAPI* obj);
void haxorg_destroy_ImmAdapterSubtreeLogAPI(haxorg_ImmAdapterSubtreeLogAPI* obj);
void haxorg_destroy_ImmAdapterColonExampleAPI(haxorg_ImmAdapterColonExampleAPI* obj);
void haxorg_destroy_ImmAdapterCallAPI(haxorg_ImmAdapterCallAPI* obj);
void haxorg_destroy_ImmAdapterFileAPI(haxorg_ImmAdapterFileAPI* obj);
void haxorg_destroy_ImmAdapterDirectoryAPI(haxorg_ImmAdapterDirectoryAPI* obj);
void haxorg_destroy_ImmAdapterSymlinkAPI(haxorg_ImmAdapterSymlinkAPI* obj);
void haxorg_destroy_ImmAdapterDocumentFragmentAPI(haxorg_ImmAdapterDocumentFragmentAPI* obj);
void haxorg_destroy_ImmAdapterCriticMarkupAPI(haxorg_ImmAdapterCriticMarkupAPI* obj);
void haxorg_destroy_ImmAdapterListItemAPI(haxorg_ImmAdapterListItemAPI* obj);
void haxorg_destroy_ImmAdapterDocumentOptionsAPI(haxorg_ImmAdapterDocumentOptionsAPI* obj);
void haxorg_destroy_ImmAdapterDocumentAPI(haxorg_ImmAdapterDocumentAPI* obj);
void haxorg_destroy_ImmAdapterFileTargetAPI(haxorg_ImmAdapterFileTargetAPI* obj);
void haxorg_destroy_ImmAdapterTextSeparatorAPI(haxorg_ImmAdapterTextSeparatorAPI* obj);
void haxorg_destroy_ImmAdapterCmdIncludeAPI(haxorg_ImmAdapterCmdIncludeAPI* obj);
void haxorg_destroy_ImmAdapterDocumentGroupAPI(haxorg_ImmAdapterDocumentGroupAPI* obj);
void haxorg_destroy_Block(haxorg_Block* obj);
void haxorg_destroy_LineCommand(haxorg_LineCommand* obj);
void haxorg_destroy_CmdCreator(haxorg_CmdCreator* obj);
void haxorg_destroy_CmdAuthor(haxorg_CmdAuthor* obj);
void haxorg_destroy_CmdEmail(haxorg_CmdEmail* obj);
void haxorg_destroy_CmdLanguage(haxorg_CmdLanguage* obj);
void haxorg_destroy_CmdCustomArgs(haxorg_CmdCustomArgs* obj);
void haxorg_destroy_CmdTblfm(haxorg_CmdTblfm* obj);
void haxorg_destroy_Cell(haxorg_Cell* obj);
void haxorg_destroy_Row(haxorg_Row* obj);
void haxorg_destroy_ImmBlock(haxorg_ImmBlock* obj);
void haxorg_destroy_ImmLineCommand(haxorg_ImmLineCommand* obj);
void haxorg_destroy_ImmCmdCreator(haxorg_ImmCmdCreator* obj);
void haxorg_destroy_ImmCmdAuthor(haxorg_ImmCmdAuthor* obj);
void haxorg_destroy_ImmCmdEmail(haxorg_ImmCmdEmail* obj);
void haxorg_destroy_ImmCmdLanguage(haxorg_ImmCmdLanguage* obj);
void haxorg_destroy_ImmCmdCustomArgs(haxorg_ImmCmdCustomArgs* obj);
void haxorg_destroy_ImmCmdTblfm(haxorg_ImmCmdTblfm* obj);
void haxorg_destroy_ImmCell(haxorg_ImmCell* obj);
void haxorg_destroy_ImmRow(haxorg_ImmRow* obj);
void haxorg_destroy_ImmAdapterCmdAPI(haxorg_ImmAdapterCmdAPI* obj);
void haxorg_destroy_ImmAdapterCmdCustomRawAPI(haxorg_ImmAdapterCmdCustomRawAPI* obj);
void haxorg_destroy_ImmAdapterCmdCustomTextAPI(haxorg_ImmAdapterCmdCustomTextAPI* obj);
void haxorg_destroy_ImmAdapterLinkAPI(haxorg_ImmAdapterLinkAPI* obj);
void haxorg_destroy_ImmAdapterBlockCommentAPI(haxorg_ImmAdapterBlockCommentAPI* obj);
void haxorg_destroy_ImmAdapterParagraphAPI(haxorg_ImmAdapterParagraphAPI* obj);
void haxorg_destroy_ImmAdapterListAPI(haxorg_ImmAdapterListAPI* obj);
void haxorg_destroy_ImmStmtAdapter(haxorg_ImmStmtAdapter* obj);
void haxorg_destroy_ImmSubtreeAdapter(haxorg_ImmSubtreeAdapter* obj);
void haxorg_destroy_ImmNoNodeAdapter(haxorg_ImmNoNodeAdapter* obj);
void haxorg_destroy_ImmErrorItemAdapter(haxorg_ImmErrorItemAdapter* obj);
void haxorg_destroy_ImmErrorGroupAdapter(haxorg_ImmErrorGroupAdapter* obj);
void haxorg_destroy_ImmErrorSkipGroupAdapter(haxorg_ImmErrorSkipGroupAdapter* obj);
void haxorg_destroy_ImmErrorSkipTokenAdapter(haxorg_ImmErrorSkipTokenAdapter* obj);
void haxorg_destroy_ImmStmtListAdapter(haxorg_ImmStmtListAdapter* obj);
void haxorg_destroy_ImmEmptyAdapter(haxorg_ImmEmptyAdapter* obj);
void haxorg_destroy_ImmAdapterHashTagAPI(haxorg_ImmAdapterHashTagAPI* obj);
void haxorg_destroy_ImmAdapterInlineFootnoteAPI(haxorg_ImmAdapterInlineFootnoteAPI* obj);
void haxorg_destroy_ImmAdapterSubtreeCompletionAPI(haxorg_ImmAdapterSubtreeCompletionAPI* obj);
void haxorg_destroy_ImmInlineAdapter(haxorg_ImmInlineAdapter* obj);
void haxorg_destroy_ImmTimeAdapter(haxorg_ImmTimeAdapter* obj);
void haxorg_destroy_ImmTimeRangeAdapter(haxorg_ImmTimeRangeAdapter* obj);
void haxorg_destroy_ImmMacroAdapter(haxorg_ImmMacroAdapter* obj);
void haxorg_destroy_ImmSymbolAdapter(haxorg_ImmSymbolAdapter* obj);
void haxorg_destroy_ImmAdapterEscapedAPI(haxorg_ImmAdapterEscapedAPI* obj);
void haxorg_destroy_ImmAdapterNewlineAPI(haxorg_ImmAdapterNewlineAPI* obj);
void haxorg_destroy_ImmAdapterSpaceAPI(haxorg_ImmAdapterSpaceAPI* obj);
void haxorg_destroy_ImmAdapterWordAPI(haxorg_ImmAdapterWordAPI* obj);
void haxorg_destroy_ImmAdapterAtMentionAPI(haxorg_ImmAdapterAtMentionAPI* obj);
void haxorg_destroy_ImmAdapterRawTextAPI(haxorg_ImmAdapterRawTextAPI* obj);
void haxorg_destroy_ImmAdapterPunctuationAPI(haxorg_ImmAdapterPunctuationAPI* obj);
void haxorg_destroy_ImmAdapterPlaceholderAPI(haxorg_ImmAdapterPlaceholderAPI* obj);
void haxorg_destroy_ImmAdapterBigIdentAPI(haxorg_ImmAdapterBigIdentAPI* obj);
void haxorg_destroy_ImmAdapterTextTargetAPI(haxorg_ImmAdapterTextTargetAPI* obj);
void haxorg_destroy_ImmLeafAdapter(haxorg_ImmLeafAdapter* obj);
void haxorg_destroy_ImmAdapterBoldAPI(haxorg_ImmAdapterBoldAPI* obj);
void haxorg_destroy_ImmAdapterUnderlineAPI(haxorg_ImmAdapterUnderlineAPI* obj);
void haxorg_destroy_ImmAdapterMonospaceAPI(haxorg_ImmAdapterMonospaceAPI* obj);
void haxorg_destroy_ImmAdapterMarkQuoteAPI(haxorg_ImmAdapterMarkQuoteAPI* obj);
void haxorg_destroy_ImmAdapterRadioTargetAPI(haxorg_ImmAdapterRadioTargetAPI* obj);
void haxorg_destroy_ImmAdapterVerbatimAPI(haxorg_ImmAdapterVerbatimAPI* obj);
void haxorg_destroy_ImmAdapterItalicAPI(haxorg_ImmAdapterItalicAPI* obj);
void haxorg_destroy_ImmAdapterStrikeAPI(haxorg_ImmAdapterStrikeAPI* obj);
void haxorg_destroy_ImmAdapterParAPI(haxorg_ImmAdapterParAPI* obj);
void haxorg_destroy_ImmMarkupAdapter(haxorg_ImmMarkupAdapter* obj);
void haxorg_destroy_ImmLatexAdapter(haxorg_ImmLatexAdapter* obj);
void haxorg_destroy_ImmSubtreeLogAdapter(haxorg_ImmSubtreeLogAdapter* obj);
void haxorg_destroy_ImmColonExampleAdapter(haxorg_ImmColonExampleAdapter* obj);
void haxorg_destroy_ImmCallAdapter(haxorg_ImmCallAdapter* obj);
void haxorg_destroy_ImmFileAdapter(haxorg_ImmFileAdapter* obj);
void haxorg_destroy_ImmDirectoryAdapter(haxorg_ImmDirectoryAdapter* obj);
void haxorg_destroy_ImmSymlinkAdapter(haxorg_ImmSymlinkAdapter* obj);
void haxorg_destroy_ImmDocumentFragmentAdapter(haxorg_ImmDocumentFragmentAdapter* obj);
void haxorg_destroy_ImmCriticMarkupAdapter(haxorg_ImmCriticMarkupAdapter* obj);
void haxorg_destroy_ImmListItemAdapter(haxorg_ImmListItemAdapter* obj);
void haxorg_destroy_ImmDocumentOptionsAdapter(haxorg_ImmDocumentOptionsAdapter* obj);
void haxorg_destroy_ImmDocumentAdapter(haxorg_ImmDocumentAdapter* obj);
void haxorg_destroy_ImmFileTargetAdapter(haxorg_ImmFileTargetAdapter* obj);
void haxorg_destroy_ImmTextSeparatorAdapter(haxorg_ImmTextSeparatorAdapter* obj);
void haxorg_destroy_ImmCmdIncludeAdapter(haxorg_ImmCmdIncludeAdapter* obj);
void haxorg_destroy_ImmDocumentGroupAdapter(haxorg_ImmDocumentGroupAdapter* obj);
void haxorg_destroy_BlockCenter(haxorg_BlockCenter* obj);
void haxorg_destroy_BlockQuote(haxorg_BlockQuote* obj);
void haxorg_destroy_BlockVerse(haxorg_BlockVerse* obj);
void haxorg_destroy_BlockDynamicFallback(haxorg_BlockDynamicFallback* obj);
void haxorg_destroy_BlockExample(haxorg_BlockExample* obj);
void haxorg_destroy_BlockExport(haxorg_BlockExport* obj);
void haxorg_destroy_BlockAdmonition(haxorg_BlockAdmonition* obj);
void haxorg_destroy_BlockCodeEvalResult(haxorg_BlockCodeEvalResult* obj);
void haxorg_destroy_BlockCode(haxorg_BlockCode* obj);
void haxorg_destroy_Table(haxorg_Table* obj);
void haxorg_destroy_Attached(haxorg_Attached* obj);
void haxorg_destroy_ImmBlockCenter(haxorg_ImmBlockCenter* obj);
void haxorg_destroy_ImmBlockQuote(haxorg_ImmBlockQuote* obj);
void haxorg_destroy_ImmBlockVerse(haxorg_ImmBlockVerse* obj);
void haxorg_destroy_ImmBlockDynamicFallback(haxorg_ImmBlockDynamicFallback* obj);
void haxorg_destroy_ImmBlockExample(haxorg_ImmBlockExample* obj);
void haxorg_destroy_ImmBlockExport(haxorg_ImmBlockExport* obj);
void haxorg_destroy_ImmBlockAdmonition(haxorg_ImmBlockAdmonition* obj);
void haxorg_destroy_ImmBlockCodeEvalResult(haxorg_ImmBlockCodeEvalResult* obj);
void haxorg_destroy_ImmBlockCode(haxorg_ImmBlockCode* obj);
void haxorg_destroy_ImmTable(haxorg_ImmTable* obj);
void haxorg_destroy_ImmAttached(haxorg_ImmAttached* obj);
void haxorg_destroy_ImmAdapterLineCommandAPI(haxorg_ImmAdapterLineCommandAPI* obj);
void haxorg_destroy_ImmAdapterCmdCustomArgsAPI(haxorg_ImmAdapterCmdCustomArgsAPI* obj);
void haxorg_destroy_ImmAdapterCmdCreatorAPI(haxorg_ImmAdapterCmdCreatorAPI* obj);
void haxorg_destroy_ImmAdapterCmdAuthorAPI(haxorg_ImmAdapterCmdAuthorAPI* obj);
void haxorg_destroy_ImmAdapterCmdEmailAPI(haxorg_ImmAdapterCmdEmailAPI* obj);
void haxorg_destroy_ImmAdapterCmdLanguageAPI(haxorg_ImmAdapterCmdLanguageAPI* obj);
void haxorg_destroy_ImmAdapterCmdTblfmAPI(haxorg_ImmAdapterCmdTblfmAPI* obj);
void haxorg_destroy_ImmAdapterBlockAPI(haxorg_ImmAdapterBlockAPI* obj);
void haxorg_destroy_ImmAdapterCellAPI(haxorg_ImmAdapterCellAPI* obj);
void haxorg_destroy_ImmAdapterRowAPI(haxorg_ImmAdapterRowAPI* obj);
void haxorg_destroy_ImmCmdAdapter(haxorg_ImmCmdAdapter* obj);
void haxorg_destroy_ImmCmdCustomRawAdapter(haxorg_ImmCmdCustomRawAdapter* obj);
void haxorg_destroy_ImmCmdCustomTextAdapter(haxorg_ImmCmdCustomTextAdapter* obj);
void haxorg_destroy_ImmLinkAdapter(haxorg_ImmLinkAdapter* obj);
void haxorg_destroy_ImmBlockCommentAdapter(haxorg_ImmBlockCommentAdapter* obj);
void haxorg_destroy_ImmParagraphAdapter(haxorg_ImmParagraphAdapter* obj);
void haxorg_destroy_ImmListAdapter(haxorg_ImmListAdapter* obj);
void haxorg_destroy_ImmHashTagAdapter(haxorg_ImmHashTagAdapter* obj);
void haxorg_destroy_ImmInlineFootnoteAdapter(haxorg_ImmInlineFootnoteAdapter* obj);
void haxorg_destroy_ImmEscapedAdapter(haxorg_ImmEscapedAdapter* obj);
void haxorg_destroy_ImmNewlineAdapter(haxorg_ImmNewlineAdapter* obj);
void haxorg_destroy_ImmSpaceAdapter(haxorg_ImmSpaceAdapter* obj);
void haxorg_destroy_ImmWordAdapter(haxorg_ImmWordAdapter* obj);
void haxorg_destroy_ImmAtMentionAdapter(haxorg_ImmAtMentionAdapter* obj);
void haxorg_destroy_ImmRawTextAdapter(haxorg_ImmRawTextAdapter* obj);
void haxorg_destroy_ImmPunctuationAdapter(haxorg_ImmPunctuationAdapter* obj);
void haxorg_destroy_ImmPlaceholderAdapter(haxorg_ImmPlaceholderAdapter* obj);
void haxorg_destroy_ImmBigIdentAdapter(haxorg_ImmBigIdentAdapter* obj);
void haxorg_destroy_ImmTextTargetAdapter(haxorg_ImmTextTargetAdapter* obj);
void haxorg_destroy_ImmBoldAdapter(haxorg_ImmBoldAdapter* obj);
void haxorg_destroy_ImmUnderlineAdapter(haxorg_ImmUnderlineAdapter* obj);
void haxorg_destroy_ImmMonospaceAdapter(haxorg_ImmMonospaceAdapter* obj);
void haxorg_destroy_ImmMarkQuoteAdapter(haxorg_ImmMarkQuoteAdapter* obj);
void haxorg_destroy_ImmRadioTargetAdapter(haxorg_ImmRadioTargetAdapter* obj);
void haxorg_destroy_ImmVerbatimAdapter(haxorg_ImmVerbatimAdapter* obj);
void haxorg_destroy_ImmItalicAdapter(haxorg_ImmItalicAdapter* obj);
void haxorg_destroy_ImmStrikeAdapter(haxorg_ImmStrikeAdapter* obj);
void haxorg_destroy_ImmParAdapter(haxorg_ImmParAdapter* obj);
void haxorg_destroy_CmdCaption(haxorg_CmdCaption* obj);
void haxorg_destroy_CmdColumns(haxorg_CmdColumns* obj);
void haxorg_destroy_CmdName(haxorg_CmdName* obj);
void haxorg_destroy_CmdCall(haxorg_CmdCall* obj);
void haxorg_destroy_CmdAttr(haxorg_CmdAttr* obj);
void haxorg_destroy_CmdExport(haxorg_CmdExport* obj);
void haxorg_destroy_ImmCmdCaption(haxorg_ImmCmdCaption* obj);
void haxorg_destroy_ImmCmdColumns(haxorg_ImmCmdColumns* obj);
void haxorg_destroy_ImmCmdName(haxorg_ImmCmdName* obj);
void haxorg_destroy_ImmCmdCall(haxorg_ImmCmdCall* obj);
void haxorg_destroy_ImmCmdAttr(haxorg_ImmCmdAttr* obj);
void haxorg_destroy_ImmCmdExport(haxorg_ImmCmdExport* obj);
void haxorg_destroy_ImmAdapterAttachedAPI(haxorg_ImmAdapterAttachedAPI* obj);
void haxorg_destroy_ImmLineCommandAdapter(haxorg_ImmLineCommandAdapter* obj);
void haxorg_destroy_ImmCmdCustomArgsAdapter(haxorg_ImmCmdCustomArgsAdapter* obj);
void haxorg_destroy_ImmCmdCreatorAdapter(haxorg_ImmCmdCreatorAdapter* obj);
void haxorg_destroy_ImmCmdAuthorAdapter(haxorg_ImmCmdAuthorAdapter* obj);
void haxorg_destroy_ImmCmdEmailAdapter(haxorg_ImmCmdEmailAdapter* obj);
void haxorg_destroy_ImmCmdLanguageAdapter(haxorg_ImmCmdLanguageAdapter* obj);
void haxorg_destroy_ImmCmdTblfmAdapter(haxorg_ImmCmdTblfmAdapter* obj);
void haxorg_destroy_ImmAdapterBlockCenterAPI(haxorg_ImmAdapterBlockCenterAPI* obj);
void haxorg_destroy_ImmAdapterBlockQuoteAPI(haxorg_ImmAdapterBlockQuoteAPI* obj);
void haxorg_destroy_ImmAdapterBlockVerseAPI(haxorg_ImmAdapterBlockVerseAPI* obj);
void haxorg_destroy_ImmAdapterBlockExampleAPI(haxorg_ImmAdapterBlockExampleAPI* obj);
void haxorg_destroy_ImmAdapterInlineExportAPI(haxorg_ImmAdapterInlineExportAPI* obj);
void haxorg_destroy_ImmAdapterCmdExportAPI(haxorg_ImmAdapterCmdExportAPI* obj);
void haxorg_destroy_ImmAdapterBlockExportAPI(haxorg_ImmAdapterBlockExportAPI* obj);
void haxorg_destroy_ImmAdapterBlockDynamicFallbackAPI(haxorg_ImmAdapterBlockDynamicFallbackAPI* obj);
void haxorg_destroy_ImmAdapterBlockAdmonitionAPI(haxorg_ImmAdapterBlockAdmonitionAPI* obj);
void haxorg_destroy_ImmAdapterBlockCodeEvalResultAPI(haxorg_ImmAdapterBlockCodeEvalResultAPI* obj);
void haxorg_destroy_ImmAdapterBlockCodeAPI(haxorg_ImmAdapterBlockCodeAPI* obj);
void haxorg_destroy_ImmAdapterTableAPI(haxorg_ImmAdapterTableAPI* obj);
void haxorg_destroy_ImmBlockAdapter(haxorg_ImmBlockAdapter* obj);
void haxorg_destroy_ImmCellAdapter(haxorg_ImmCellAdapter* obj);
void haxorg_destroy_ImmRowAdapter(haxorg_ImmRowAdapter* obj);
void haxorg_destroy_ImmAdapterCmdCaptionAPI(haxorg_ImmAdapterCmdCaptionAPI* obj);
void haxorg_destroy_ImmAdapterCmdColumnsAPI(haxorg_ImmAdapterCmdColumnsAPI* obj);
void haxorg_destroy_ImmAdapterCmdNameAPI(haxorg_ImmAdapterCmdNameAPI* obj);
void haxorg_destroy_ImmAdapterCmdCallAPI(haxorg_ImmAdapterCmdCallAPI* obj);
void haxorg_destroy_ImmAdapterCmdResultsAPI(haxorg_ImmAdapterCmdResultsAPI* obj);
void haxorg_destroy_ImmAdapterCmdAttrAPI(haxorg_ImmAdapterCmdAttrAPI* obj);
void haxorg_destroy_ImmAttachedAdapter(haxorg_ImmAttachedAdapter* obj);
void haxorg_destroy_ImmBlockCenterAdapter(haxorg_ImmBlockCenterAdapter* obj);
void haxorg_destroy_ImmBlockQuoteAdapter(haxorg_ImmBlockQuoteAdapter* obj);
void haxorg_destroy_ImmBlockVerseAdapter(haxorg_ImmBlockVerseAdapter* obj);
void haxorg_destroy_ImmBlockExampleAdapter(haxorg_ImmBlockExampleAdapter* obj);
void haxorg_destroy_ImmInlineExportAdapter(haxorg_ImmInlineExportAdapter* obj);
void haxorg_destroy_ImmCmdExportAdapter(haxorg_ImmCmdExportAdapter* obj);
void haxorg_destroy_ImmBlockExportAdapter(haxorg_ImmBlockExportAdapter* obj);
void haxorg_destroy_ImmBlockDynamicFallbackAdapter(haxorg_ImmBlockDynamicFallbackAdapter* obj);
void haxorg_destroy_ImmBlockAdmonitionAdapter(haxorg_ImmBlockAdmonitionAdapter* obj);
void haxorg_destroy_ImmBlockCodeEvalResultAdapter(haxorg_ImmBlockCodeEvalResultAdapter* obj);
void haxorg_destroy_ImmBlockCodeAdapter(haxorg_ImmBlockCodeAdapter* obj);
void haxorg_destroy_ImmTableAdapter(haxorg_ImmTableAdapter* obj);
void haxorg_destroy_ImmCmdCaptionAdapter(haxorg_ImmCmdCaptionAdapter* obj);
void haxorg_destroy_ImmCmdColumnsAdapter(haxorg_ImmCmdColumnsAdapter* obj);
void haxorg_destroy_ImmCmdNameAdapter(haxorg_ImmCmdNameAdapter* obj);
void haxorg_destroy_ImmCmdCallAdapter(haxorg_ImmCmdCallAdapter* obj);
void haxorg_destroy_ImmCmdAttrAdapter(haxorg_ImmCmdAttrAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_SemId newSemTimeStatic(haxorg_UserTimeBreakdown breakdown, bool isActive, OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_ImmAstContext initImmutableAstContext(OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_SemId asOneNode(haxorg_SemId arg, OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_StdString formatToString(haxorg_SemId arg, OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_StdString exportToYamlString(haxorg_SemId node, haxorg_OrgYamlExportOpts opts, OrgContext* org_context);
HAXORG_C_API_LINKAGE void exportToYamlFile(haxorg_SemId node, haxorg_StdString path, haxorg_OrgYamlExportOpts opts, OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_StdString exportToJsonString(haxorg_SemId node, OrgContext* org_context);
HAXORG_C_API_LINKAGE void exportToJsonFile(haxorg_SemId node, haxorg_StdString path, OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_SemId readProtobufFile(haxorg_StdString file, OrgContext* org_context);
HAXORG_C_API_LINKAGE void exportToProtobufFile(haxorg_SemId doc, haxorg_StdString file, OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_StdString exportToTreeString(haxorg_SemId node, haxorg_OrgTreeExportOpts opts, OrgContext* org_context);
HAXORG_C_API_LINKAGE void exportToTreeFile(haxorg_SemId node, haxorg_StdString path, haxorg_OrgTreeExportOpts opts, OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_AstTrackingMap getAstTrackingMap(haxorg_HstdVec nodes, OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_HstdVec getSubnodeGroups(haxorg_SemId node, haxorg_AstTrackingMap map, OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_HstdVec annotateSequence(haxorg_HstdVec groups, int first, int last, OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_GraphMapGraphState initMapGraphState(haxorg_ImmAstContext ast, OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_StdString serializeToText(haxorg_ImmAstContext store, OrgContext* org_context);
HAXORG_C_API_LINKAGE void serializeFromText(haxorg_StdString binary, haxorg_ImmAstContext store, OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_StdString serializeToText(haxorg_ImmAstReplaceEpoch store, OrgContext* org_context);
HAXORG_C_API_LINKAGE void serializeFromText(haxorg_StdString binary, haxorg_ImmAstReplaceEpoch store, OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_StdString serializeToText(haxorg_GraphMapGraph store, OrgContext* org_context);
HAXORG_C_API_LINKAGE void serializeFromText(haxorg_StdString binary, haxorg_GraphMapGraph store, OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_StdString serializeFromTextToTreeDump(haxorg_StdString binary, OrgContext* org_context);
/* clang-format on */
