/* clang-format off */
#pragma once
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

struct haxorg_ParseSourceManager_vtable;

struct haxorg_ParseSourceManager;

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
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'UserTime']
struct haxorg_UserTime {
  haxorg_UserTime_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ParseSourceFileId_vtable {};

/// \brief ['org', 'parse', 'SourceFileId']
struct haxorg_ParseSourceFileId {
  haxorg_ParseSourceFileId_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'parse', 'SourceManager']
struct haxorg_ParseSourceManager {
  haxorg_ParseSourceManager_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'parse', 'SourceLoc']
struct haxorg_ParseSourceLoc {
  haxorg_ParseSourceLoc_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'OrgJson']
struct haxorg_OrgJson {
  haxorg_OrgJson_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Org']
struct haxorg_Org {
  haxorg_Org_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'OperationsTracer']
struct haxorg_OperationsTracer {
  haxorg_OperationsTracer_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_Cache_vtable {};

/// \brief ['hstd', 'ext', 'Cache']
struct haxorg_Cache {
  haxorg_Cache_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'parse', 'OrgParseFragment']
struct haxorg_ParseOrgParseFragment {
  haxorg_ParseOrgParseFragment_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'parse', 'OrgParseParameters']
struct haxorg_OrgParseParameters {
  haxorg_OrgParseParameters_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_OrgDirectoryParseParameters_vtable {};

/// \brief ['org', 'parse', 'OrgDirectoryParseParameters']
struct haxorg_OrgDirectoryParseParameters {
  haxorg_OrgDirectoryParseParameters_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'parse', 'ParseContext']
struct haxorg_ParseContext {
  haxorg_ParseContext_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmReflFieldId']
struct haxorg_ImmReflFieldId {
  haxorg_ImmReflFieldId_vtable const* vtable;
  haxorg_ptr_payload data;
};

typedef uint32_t haxorg_ImmIdNodeIdxT;
/// \brief ['org', 'imm', 'ImmId']
struct haxorg_ImmId {
  haxorg_ImmId_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmOrg_vtable {};

/// \brief ['org', 'imm', 'ImmOrg']
struct haxorg_ImmOrg {
  haxorg_ImmOrg_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmPathStep_vtable {};

/// \brief ['org', 'imm', 'ImmPathStep']
struct haxorg_ImmPathStep {
  haxorg_ImmPathStep_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmPath']
struct haxorg_ImmPath {
  haxorg_ImmPath_vtable const* vtable;
  haxorg_ptr_payload data;
};

typedef haxorg_immer_flex_vector haxorg_ImmPathStore;
struct haxorg_ImmUniqId_vtable {};

/// \brief ['org', 'imm', 'ImmUniqId']
struct haxorg_ImmUniqId {
  haxorg_ImmUniqId_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAstReplaceEpoch_vtable {};

/// \brief ['org', 'imm', 'ImmAstReplaceEpoch']
struct haxorg_ImmAstReplaceEpoch {
  haxorg_ImmAstReplaceEpoch_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAstVersion']
struct haxorg_ImmAstVersion {
  haxorg_ImmAstVersion_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAstContext']
struct haxorg_ImmAstContext {
  haxorg_ImmAstContext_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapter']
struct haxorg_ImmAdapter {
  haxorg_ImmAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapter', 'TreeReprConf']
struct haxorg_ImmAdapterTreeReprConf {
  haxorg_ImmAdapterTreeReprConf_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterVirtualBase_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterVirtualBase']
struct haxorg_ImmAdapterVirtualBase {
  haxorg_ImmAdapterVirtualBase_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'OrgYamlExportOpts']
struct haxorg_OrgYamlExportOpts {
  haxorg_OrgYamlExportOpts_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'OrgTreeExportOpts']
struct haxorg_OrgTreeExportOpts {
  haxorg_OrgTreeExportOpts_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'AstTrackingPath']
struct haxorg_AstTrackingPath {
  haxorg_AstTrackingPath_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'AstTrackingAlternatives']
struct haxorg_AstTrackingAlternatives {
  haxorg_AstTrackingAlternatives_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'AstTrackingGroup', 'RadioTarget']
struct haxorg_AstTrackingGroupRadioTarget {
  haxorg_AstTrackingGroupRadioTarget_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'AstTrackingGroup', 'Single']
struct haxorg_AstTrackingGroupSingle {
  haxorg_AstTrackingGroupSingle_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'AstTrackingGroup', 'TrackedHashtag']
struct haxorg_AstTrackingGroupTrackedHashtag {
  haxorg_AstTrackingGroupTrackedHashtag_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'AstTrackingGroup']
struct haxorg_AstTrackingGroup {
  haxorg_AstTrackingGroup_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'AstTrackingMap']
struct haxorg_AstTrackingMap {
  haxorg_AstTrackingMap_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'SequenceSegment']
struct haxorg_SequenceSegment {
  haxorg_SequenceSegment_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'SequenceSegmentGroup']
struct haxorg_SequenceSegmentGroup {
  haxorg_SequenceSegmentGroup_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'SequenceAnnotationTag']
struct haxorg_SequenceAnnotationTag {
  haxorg_SequenceAnnotationTag_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['hstd', 'SequenceAnnotation']
struct haxorg_SequenceAnnotation {
  haxorg_SequenceAnnotation_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'graph', 'MapLink', 'Link']
struct haxorg_GraphMapLinkLink {
  haxorg_GraphMapLinkLink_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'graph', 'MapLink', 'Radio']
struct haxorg_GraphMapLinkRadio {
  haxorg_GraphMapLinkRadio_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'graph', 'MapLink']
struct haxorg_GraphMapLink {
  haxorg_GraphMapLink_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'graph', 'MapNodeProp']
struct haxorg_GraphMapNodeProp {
  haxorg_GraphMapNodeProp_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'graph', 'MapEdgeProp']
struct haxorg_GraphMapEdgeProp {
  haxorg_GraphMapEdgeProp_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'graph', 'MapNode']
struct haxorg_GraphMapNode {
  haxorg_GraphMapNode_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'graph', 'MapEdge']
struct haxorg_GraphMapEdge {
  haxorg_GraphMapEdge_vtable const* vtable;
  haxorg_ptr_payload data;
};

typedef haxorg_HstdUnorderedMap haxorg_GraphEdgeProps;
typedef haxorg_HstdUnorderedMap haxorg_GraphNodeProps;
typedef haxorg_HstdUnorderedMap haxorg_GraphAdjList;
typedef haxorg_HstdVec haxorg_GraphAdjNodesList;
/// \brief ['org', 'graph', 'MapGraph']
struct haxorg_GraphMapGraph {
  haxorg_GraphMapGraph_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'graph', 'MapConfig']
struct haxorg_GraphMapConfig {
  haxorg_GraphMapConfig_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'graph', 'MapGraphState']
struct haxorg_GraphMapGraphState {
  haxorg_GraphMapGraphState_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmLink']]]
struct haxorg_ImmLinkAdapter {
  haxorg_ImmLinkAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmSubtree']]]
struct haxorg_ImmSubtreeAdapter {
  haxorg_ImmSubtreeAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

typedef uint64_t haxorg_ImmIdIdType;
/// \brief ['org', 'sem', 'LispCode', 'Call']
struct haxorg_LispCodeCall {
  haxorg_LispCodeCall_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LispCode', 'List']
struct haxorg_LispCodeList {
  haxorg_LispCodeList_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LispCode', 'KeyValue']
struct haxorg_LispCodeKeyValue {
  haxorg_LispCodeKeyValue_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LispCode', 'Number']
struct haxorg_LispCodeNumber {
  haxorg_LispCodeNumber_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LispCode', 'Text']
struct haxorg_LispCodeText {
  haxorg_LispCodeText_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LispCode', 'Ident']
struct haxorg_LispCodeIdent {
  haxorg_LispCodeIdent_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LispCode', 'Boolean']
struct haxorg_LispCodeBoolean {
  haxorg_LispCodeBoolean_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LispCode', 'Real']
struct haxorg_LispCodeReal {
  haxorg_LispCodeReal_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LispCode']
struct haxorg_LispCode {
  haxorg_LispCode_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr', 'AxisRef', 'Position', 'Index']
struct haxorg_TblfmExprAxisRefPositionIndex {
  haxorg_TblfmExprAxisRefPositionIndex_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr', 'AxisRef', 'Position', 'Name']
struct haxorg_TblfmExprAxisRefPositionName {
  haxorg_TblfmExprAxisRefPositionName_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr', 'AxisRef', 'Position']
struct haxorg_TblfmExprAxisRefPosition {
  haxorg_TblfmExprAxisRefPosition_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr', 'AxisRef']
struct haxorg_TblfmExprAxisRef {
  haxorg_TblfmExprAxisRef_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr', 'AxisName']
struct haxorg_TblfmExprAxisName {
  haxorg_TblfmExprAxisName_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr', 'IntLiteral']
struct haxorg_TblfmExprIntLiteral {
  haxorg_TblfmExprIntLiteral_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr', 'FloatLiteral']
struct haxorg_TblfmExprFloatLiteral {
  haxorg_TblfmExprFloatLiteral_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr', 'RangeRef']
struct haxorg_TblfmExprRangeRef {
  haxorg_TblfmExprRangeRef_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr', 'Call']
struct haxorg_TblfmExprCall {
  haxorg_TblfmExprCall_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr', 'Elisp']
struct haxorg_TblfmExprElisp {
  haxorg_TblfmExprElisp_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Expr']
struct haxorg_TblfmExpr {
  haxorg_TblfmExpr_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm', 'Assign']
struct haxorg_TblfmAssign {
  haxorg_TblfmAssign_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Tblfm']
struct haxorg_Tblfm {
  haxorg_Tblfm_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'AttrValue', 'DimensionSpan']
struct haxorg_AttrValueDimensionSpan {
  haxorg_AttrValueDimensionSpan_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'AttrValue', 'TextValue']
struct haxorg_AttrValueTextValue {
  haxorg_AttrValueTextValue_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'AttrValue', 'FileReference']
struct haxorg_AttrValueFileReference {
  haxorg_AttrValueFileReference_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'AttrValue', 'LispValue']
struct haxorg_AttrValueLispValue {
  haxorg_AttrValueLispValue_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'AttrValue']
struct haxorg_AttrValue {
  haxorg_AttrValue_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'HashTagFlat']
struct haxorg_HashTagFlat {
  haxorg_HashTagFlat_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'TodoKeyword']
struct haxorg_TodoKeyword {
  haxorg_TodoKeyword_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'HashTagText']
struct haxorg_HashTagText {
  haxorg_HashTagText_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreePath']
struct haxorg_SubtreePath {
  haxorg_SubtreePath_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget', 'Raw']
struct haxorg_LinkTargetRaw {
  haxorg_LinkTargetRaw_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget', 'Id']
struct haxorg_LinkTargetId {
  haxorg_LinkTargetId_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget', 'CustomId']
struct haxorg_LinkTargetCustomId {
  haxorg_LinkTargetCustomId_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget', 'SubtreeTitle']
struct haxorg_LinkTargetSubtreeTitle {
  haxorg_LinkTargetSubtreeTitle_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget', 'Person']
struct haxorg_LinkTargetPerson {
  haxorg_LinkTargetPerson_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget', 'UserProtocol']
struct haxorg_LinkTargetUserProtocol {
  haxorg_LinkTargetUserProtocol_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget', 'Internal']
struct haxorg_LinkTargetInternal {
  haxorg_LinkTargetInternal_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget', 'Footnote']
struct haxorg_LinkTargetFootnote {
  haxorg_LinkTargetFootnote_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget', 'File']
struct haxorg_LinkTargetFile {
  haxorg_LinkTargetFile_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget', 'Attachment']
struct haxorg_LinkTargetAttachment {
  haxorg_LinkTargetAttachment_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'LinkTarget']
struct haxorg_LinkTarget {
  haxorg_LinkTarget_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLogHead', 'Priority']
struct haxorg_SubtreeLogHeadPriority {
  haxorg_SubtreeLogHeadPriority_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLogHead', 'Note']
struct haxorg_SubtreeLogHeadNote {
  haxorg_SubtreeLogHeadNote_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLogHead', 'Refile']
struct haxorg_SubtreeLogHeadRefile {
  haxorg_SubtreeLogHeadRefile_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLogHead', 'Clock']
struct haxorg_SubtreeLogHeadClock {
  haxorg_SubtreeLogHeadClock_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLogHead', 'State']
struct haxorg_SubtreeLogHeadState {
  haxorg_SubtreeLogHeadState_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLogHead', 'Deadline']
struct haxorg_SubtreeLogHeadDeadline {
  haxorg_SubtreeLogHeadDeadline_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLogHead', 'Schedule']
struct haxorg_SubtreeLogHeadSchedule {
  haxorg_SubtreeLogHeadSchedule_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLogHead', 'Tag']
struct haxorg_SubtreeLogHeadTag {
  haxorg_SubtreeLogHeadTag_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLogHead', 'Unknown']
struct haxorg_SubtreeLogHeadUnknown {
  haxorg_SubtreeLogHeadUnknown_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLogHead']
struct haxorg_SubtreeLogHead {
  haxorg_SubtreeLogHead_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeCompletion']
struct haxorg_SubtreeCompletion {
  haxorg_SubtreeCompletion_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'AttrList']
struct haxorg_AttrList {
  haxorg_AttrList_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'AttrGroup']
struct haxorg_AttrGroup {
  haxorg_AttrGroup_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'OrgCodeEvalInput', 'Var']
struct haxorg_OrgCodeEvalInputVar {
  haxorg_OrgCodeEvalInputVar_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'OrgCodeEvalInput']
struct haxorg_OrgCodeEvalInput {
  haxorg_OrgCodeEvalInput_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'OrgCodeEvalOutput']
struct haxorg_OrgCodeEvalOutput {
  haxorg_OrgCodeEvalOutput_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'ColumnView', 'Summary', 'CheckboxAggregate']
struct haxorg_ColumnViewSummaryCheckboxAggregate {
  haxorg_ColumnViewSummaryCheckboxAggregate_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'ColumnView', 'Summary', 'MathAggregate']
struct haxorg_ColumnViewSummaryMathAggregate {
  haxorg_ColumnViewSummaryMathAggregate_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'ColumnView', 'Summary']
struct haxorg_ColumnViewSummary {
  haxorg_ColumnViewSummary_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'ColumnView', 'Column']
struct haxorg_ColumnViewColumn {
  haxorg_ColumnViewColumn_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'ColumnView']
struct haxorg_ColumnView {
  haxorg_ColumnView_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockCodeLine', 'Part', 'Raw']
struct haxorg_BlockCodeLinePartRaw {
  haxorg_BlockCodeLinePartRaw_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockCodeLine', 'Part', 'Callout']
struct haxorg_BlockCodeLinePartCallout {
  haxorg_BlockCodeLinePartCallout_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockCodeLine', 'Part', 'Tangle']
struct haxorg_BlockCodeLinePartTangle {
  haxorg_BlockCodeLinePartTangle_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockCodeLine', 'Part']
struct haxorg_BlockCodeLinePart {
  haxorg_BlockCodeLinePart_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockCodeLine']
struct haxorg_BlockCodeLine {
  haxorg_BlockCodeLine_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'DocumentExportConfig', 'TaskExport']
struct haxorg_DocumentExportConfigTaskExport {
  haxorg_DocumentExportConfigTaskExport_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'DocumentExportConfig', 'DoExport']
struct haxorg_DocumentExportConfigDoExport {
  haxorg_DocumentExportConfigDoExport_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'DocumentExportConfig', 'ExportFixed']
struct haxorg_DocumentExportConfigExportFixed {
  haxorg_DocumentExportConfigExportFixed_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'DocumentExportConfig']
struct haxorg_DocumentExportConfig {
  haxorg_DocumentExportConfig_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreePeriod']
struct haxorg_SubtreePeriod {
  haxorg_SubtreePeriod_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'Nonblocking']
struct haxorg_NamedPropertyNonblocking {
  haxorg_NamedPropertyNonblocking_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ArchiveTime']
struct haxorg_NamedPropertyArchiveTime {
  haxorg_NamedPropertyArchiveTime_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ArchiveFile']
struct haxorg_NamedPropertyArchiveFile {
  haxorg_NamedPropertyArchiveFile_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ArchiveOlpath']
struct haxorg_NamedPropertyArchiveOlpath {
  haxorg_NamedPropertyArchiveOlpath_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ArchiveTarget']
struct haxorg_NamedPropertyArchiveTarget {
  haxorg_NamedPropertyArchiveTarget_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ArchiveCategory']
struct haxorg_NamedPropertyArchiveCategory {
  haxorg_NamedPropertyArchiveCategory_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ArchiveTodo']
struct haxorg_NamedPropertyArchiveTodo {
  haxorg_NamedPropertyArchiveTodo_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'Trigger']
struct haxorg_NamedPropertyTrigger {
  haxorg_NamedPropertyTrigger_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ExportLatexClass']
struct haxorg_NamedPropertyExportLatexClass {
  haxorg_NamedPropertyExportLatexClass_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'CookieData']
struct haxorg_NamedPropertyCookieData {
  haxorg_NamedPropertyCookieData_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ExportLatexClassOptions']
struct haxorg_NamedPropertyExportLatexClassOptions {
  haxorg_NamedPropertyExportLatexClassOptions_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ExportLatexHeader']
struct haxorg_NamedPropertyExportLatexHeader {
  haxorg_NamedPropertyExportLatexHeader_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ExportLatexCompiler']
struct haxorg_NamedPropertyExportLatexCompiler {
  haxorg_NamedPropertyExportLatexCompiler_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'Ordered']
struct haxorg_NamedPropertyOrdered {
  haxorg_NamedPropertyOrdered_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'Effort']
struct haxorg_NamedPropertyEffort {
  haxorg_NamedPropertyEffort_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'Visibility']
struct haxorg_NamedPropertyVisibility {
  haxorg_NamedPropertyVisibility_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'ExportOptions']
struct haxorg_NamedPropertyExportOptions {
  haxorg_NamedPropertyExportOptions_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'Blocker']
struct haxorg_NamedPropertyBlocker {
  haxorg_NamedPropertyBlocker_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'Unnumbered']
struct haxorg_NamedPropertyUnnumbered {
  haxorg_NamedPropertyUnnumbered_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'Created']
struct haxorg_NamedPropertyCreated {
  haxorg_NamedPropertyCreated_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'RadioId']
struct haxorg_NamedPropertyRadioId {
  haxorg_NamedPropertyRadioId_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'HashtagDef']
struct haxorg_NamedPropertyHashtagDef {
  haxorg_NamedPropertyHashtagDef_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'CustomArgs']
struct haxorg_NamedPropertyCustomArgs {
  haxorg_NamedPropertyCustomArgs_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'CustomRaw']
struct haxorg_NamedPropertyCustomRaw {
  haxorg_NamedPropertyCustomRaw_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'CustomId']
struct haxorg_NamedPropertyCustomId {
  haxorg_NamedPropertyCustomId_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'CustomSubtreeJson']
struct haxorg_NamedPropertyCustomSubtreeJson {
  haxorg_NamedPropertyCustomSubtreeJson_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty', 'CustomSubtreeFlags']
struct haxorg_NamedPropertyCustomSubtreeFlags {
  haxorg_NamedPropertyCustomSubtreeFlags_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'NamedProperty']
struct haxorg_NamedProperty {
  haxorg_NamedProperty_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'OrgDiagnostics', 'ParseTokenError']
struct haxorg_OrgDiagnosticsParseTokenError {
  haxorg_OrgDiagnosticsParseTokenError_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'OrgDiagnostics', 'ParseError']
struct haxorg_OrgDiagnosticsParseError {
  haxorg_OrgDiagnosticsParseError_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'OrgDiagnostics', 'IncludeError']
struct haxorg_OrgDiagnosticsIncludeError {
  haxorg_OrgDiagnosticsIncludeError_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'OrgDiagnostics', 'ConvertError']
struct haxorg_OrgDiagnosticsConvertError {
  haxorg_OrgDiagnosticsConvertError_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'OrgDiagnostics', 'InternalError']
struct haxorg_OrgDiagnosticsInternalError {
  haxorg_OrgDiagnosticsInternalError_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'OrgDiagnostics']
struct haxorg_OrgDiagnostics {
  haxorg_OrgDiagnostics_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_NoNode_vtable {};

/// \brief ['org', 'sem', 'NoNode']
struct haxorg_NoNode {
  haxorg_NoNode_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'ErrorItem']
struct haxorg_ErrorItem {
  haxorg_ErrorItem_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'ErrorGroup']
struct haxorg_ErrorGroup {
  haxorg_ErrorGroup_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Stmt']
struct haxorg_Stmt {
  haxorg_Stmt_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_Inline_vtable {};

/// \brief ['org', 'sem', 'Inline']
struct haxorg_Inline {
  haxorg_Inline_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_StmtList_vtable {};

/// \brief ['org', 'sem', 'StmtList']
struct haxorg_StmtList {
  haxorg_StmtList_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_Empty_vtable {};

/// \brief ['org', 'sem', 'Empty']
struct haxorg_Empty {
  haxorg_Empty_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Leaf']
struct haxorg_Leaf {
  haxorg_Leaf_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Time', 'Repeat']
struct haxorg_TimeRepeat {
  haxorg_TimeRepeat_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Time', 'Static']
struct haxorg_TimeStatic {
  haxorg_TimeStatic_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Time', 'Dynamic']
struct haxorg_TimeDynamic {
  haxorg_TimeDynamic_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Time']
struct haxorg_Time {
  haxorg_Time_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'TimeRange']
struct haxorg_TimeRange {
  haxorg_TimeRange_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Macro']
struct haxorg_Macro {
  haxorg_Macro_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Symbol', 'Param']
struct haxorg_SymbolParam {
  haxorg_SymbolParam_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Symbol']
struct haxorg_Symbol {
  haxorg_Symbol_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'ErrorSkipGroup']
struct haxorg_ErrorSkipGroup {
  haxorg_ErrorSkipGroup_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_Markup_vtable {};

/// \brief ['org', 'sem', 'Markup']
struct haxorg_Markup {
  haxorg_Markup_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'RadioTarget']
struct haxorg_RadioTarget {
  haxorg_RadioTarget_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_Latex_vtable {};

/// \brief ['org', 'sem', 'Latex']
struct haxorg_Latex {
  haxorg_Latex_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'SubtreeLog']
struct haxorg_SubtreeLog {
  haxorg_SubtreeLog_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Subtree']
struct haxorg_Subtree {
  haxorg_Subtree_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ColonExample_vtable {};

/// \brief ['org', 'sem', 'ColonExample']
struct haxorg_ColonExample {
  haxorg_ColonExample_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Call']
struct haxorg_Call {
  haxorg_Call_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'ListItem']
struct haxorg_ListItem {
  haxorg_ListItem_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'DocumentOptions']
struct haxorg_DocumentOptions {
  haxorg_DocumentOptions_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'DocumentFragment']
struct haxorg_DocumentFragment {
  haxorg_DocumentFragment_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CriticMarkup']
struct haxorg_CriticMarkup {
  haxorg_CriticMarkup_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Document']
struct haxorg_Document {
  haxorg_Document_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'FileTarget']
struct haxorg_FileTarget {
  haxorg_FileTarget_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_TextSeparator_vtable {};

/// \brief ['org', 'sem', 'TextSeparator']
struct haxorg_TextSeparator {
  haxorg_TextSeparator_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_DocumentGroup_vtable {};

/// \brief ['org', 'sem', 'DocumentGroup']
struct haxorg_DocumentGroup {
  haxorg_DocumentGroup_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_FileDocument_vtable {};

/// \brief ['org', 'sem', 'File', 'Document']
struct haxorg_FileDocument {
  haxorg_FileDocument_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_FileAttachment_vtable {};

/// \brief ['org', 'sem', 'File', 'Attachment']
struct haxorg_FileAttachment {
  haxorg_FileAttachment_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_FileSource_vtable {};

/// \brief ['org', 'sem', 'File', 'Source']
struct haxorg_FileSource {
  haxorg_FileSource_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'File']
struct haxorg_File {
  haxorg_File_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Directory']
struct haxorg_Directory {
  haxorg_Directory_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Symlink']
struct haxorg_Symlink {
  haxorg_Symlink_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdInclude', 'IncludeBase']
struct haxorg_CmdIncludeIncludeBase {
  haxorg_CmdIncludeIncludeBase_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdInclude', 'Example']
struct haxorg_CmdIncludeExample {
  haxorg_CmdIncludeExample_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdInclude', 'Export']
struct haxorg_CmdIncludeExport {
  haxorg_CmdIncludeExport_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdInclude', 'Custom']
struct haxorg_CmdIncludeCustom {
  haxorg_CmdIncludeCustom_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdInclude', 'Src']
struct haxorg_CmdIncludeSrc {
  haxorg_CmdIncludeSrc_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdInclude', 'OrgDocument']
struct haxorg_CmdIncludeOrgDocument {
  haxorg_CmdIncludeOrgDocument_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdInclude']
struct haxorg_CmdInclude {
  haxorg_CmdInclude_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmNoNode']
struct haxorg_ImmNoNode {
  haxorg_ImmNoNode_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmErrorItem']
struct haxorg_ImmErrorItem {
  haxorg_ImmErrorItem_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmErrorGroup']
struct haxorg_ImmErrorGroup {
  haxorg_ImmErrorGroup_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmStmt']
struct haxorg_ImmStmt {
  haxorg_ImmStmt_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmInline']
struct haxorg_ImmInline {
  haxorg_ImmInline_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmStmtList']
struct haxorg_ImmStmtList {
  haxorg_ImmStmtList_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmEmpty']
struct haxorg_ImmEmpty {
  haxorg_ImmEmpty_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmLeaf']
struct haxorg_ImmLeaf {
  haxorg_ImmLeaf_vtable const* vtable;
  haxorg_ptr_payload data;
};

typedef haxorg_TimeRepeatMode haxorg_ImmTimeRepeatMode;
typedef haxorg_TimeRepeatPeriod haxorg_ImmTimeRepeatPeriod;
/// \brief ['org', 'imm', 'ImmTime', 'Repeat']
struct haxorg_ImmTimeRepeat {
  haxorg_ImmTimeRepeat_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmTime', 'Static']
struct haxorg_ImmTimeStatic {
  haxorg_ImmTimeStatic_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmTime', 'Dynamic']
struct haxorg_ImmTimeDynamic {
  haxorg_ImmTimeDynamic_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmTime']
struct haxorg_ImmTime {
  haxorg_ImmTime_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmTimeRange']
struct haxorg_ImmTimeRange {
  haxorg_ImmTimeRange_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmMacro']
struct haxorg_ImmMacro {
  haxorg_ImmMacro_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmSymbol', 'Param']
struct haxorg_ImmSymbolParam {
  haxorg_ImmSymbolParam_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmSymbol']
struct haxorg_ImmSymbol {
  haxorg_ImmSymbol_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmErrorSkipGroup']
struct haxorg_ImmErrorSkipGroup {
  haxorg_ImmErrorSkipGroup_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmMarkup']
struct haxorg_ImmMarkup {
  haxorg_ImmMarkup_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmRadioTarget']
struct haxorg_ImmRadioTarget {
  haxorg_ImmRadioTarget_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmLatex']
struct haxorg_ImmLatex {
  haxorg_ImmLatex_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmSubtreeLog']
struct haxorg_ImmSubtreeLog {
  haxorg_ImmSubtreeLog_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmSubtree']
struct haxorg_ImmSubtree {
  haxorg_ImmSubtree_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmColonExample']
struct haxorg_ImmColonExample {
  haxorg_ImmColonExample_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCall']
struct haxorg_ImmCall {
  haxorg_ImmCall_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmListItem']
struct haxorg_ImmListItem {
  haxorg_ImmListItem_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmDocumentOptions']
struct haxorg_ImmDocumentOptions {
  haxorg_ImmDocumentOptions_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmDocumentFragment']
struct haxorg_ImmDocumentFragment {
  haxorg_ImmDocumentFragment_vtable const* vtable;
  haxorg_ptr_payload data;
};

typedef haxorg_CriticMarkupKind haxorg_ImmCriticMarkupKind;
/// \brief ['org', 'imm', 'ImmCriticMarkup']
struct haxorg_ImmCriticMarkup {
  haxorg_ImmCriticMarkup_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmDocument']
struct haxorg_ImmDocument {
  haxorg_ImmDocument_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmFileTarget']
struct haxorg_ImmFileTarget {
  haxorg_ImmFileTarget_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmTextSeparator']
struct haxorg_ImmTextSeparator {
  haxorg_ImmTextSeparator_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmDocumentGroup']
struct haxorg_ImmDocumentGroup {
  haxorg_ImmDocumentGroup_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmFile', 'Document']
struct haxorg_ImmFileDocument {
  haxorg_ImmFileDocument_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmFile', 'Attachment']
struct haxorg_ImmFileAttachment {
  haxorg_ImmFileAttachment_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmFile', 'Source']
struct haxorg_ImmFileSource {
  haxorg_ImmFileSource_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmFile']
struct haxorg_ImmFile {
  haxorg_ImmFile_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmDirectory']
struct haxorg_ImmDirectory {
  haxorg_ImmDirectory_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmSymlink']
struct haxorg_ImmSymlink {
  haxorg_ImmSymlink_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdInclude', 'IncludeBase']
struct haxorg_ImmCmdIncludeIncludeBase {
  haxorg_ImmCmdIncludeIncludeBase_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdInclude', 'Example']
struct haxorg_ImmCmdIncludeExample {
  haxorg_ImmCmdIncludeExample_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdInclude', 'Export']
struct haxorg_ImmCmdIncludeExport {
  haxorg_ImmCmdIncludeExport_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdInclude', 'Custom']
struct haxorg_ImmCmdIncludeCustom {
  haxorg_ImmCmdIncludeCustom_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdInclude', 'Src']
struct haxorg_ImmCmdIncludeSrc {
  haxorg_ImmCmdIncludeSrc_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdInclude', 'OrgDocument']
struct haxorg_ImmCmdIncludeOrgDocument {
  haxorg_ImmCmdIncludeOrgDocument_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdInclude']
struct haxorg_ImmCmdInclude {
  haxorg_ImmCmdInclude_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterOrgAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterOrgAPI']
struct haxorg_ImmAdapterOrgAPI {
  haxorg_ImmAdapterOrgAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Cmd']
struct haxorg_Cmd {
  haxorg_Cmd_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdCustomRaw']
struct haxorg_CmdCustomRaw {
  haxorg_CmdCustomRaw_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdCustomText']
struct haxorg_CmdCustomText {
  haxorg_CmdCustomText_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Link']
struct haxorg_Link {
  haxorg_Link_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_BlockComment_vtable {};

/// \brief ['org', 'sem', 'BlockComment']
struct haxorg_BlockComment {
  haxorg_BlockComment_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Paragraph']
struct haxorg_Paragraph {
  haxorg_Paragraph_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'List']
struct haxorg_List {
  haxorg_List_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'HashTag']
struct haxorg_HashTag {
  haxorg_HashTag_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'InlineFootnote']
struct haxorg_InlineFootnote {
  haxorg_InlineFootnote_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'InlineExport']
struct haxorg_InlineExport {
  haxorg_InlineExport_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_Escaped_vtable {};

/// \brief ['org', 'sem', 'Escaped']
struct haxorg_Escaped {
  haxorg_Escaped_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_Newline_vtable {};

/// \brief ['org', 'sem', 'Newline']
struct haxorg_Newline {
  haxorg_Newline_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_Space_vtable {};

/// \brief ['org', 'sem', 'Space']
struct haxorg_Space {
  haxorg_Space_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_Word_vtable {};

/// \brief ['org', 'sem', 'Word']
struct haxorg_Word {
  haxorg_Word_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_AtMention_vtable {};

/// \brief ['org', 'sem', 'AtMention']
struct haxorg_AtMention {
  haxorg_AtMention_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_RawText_vtable {};

/// \brief ['org', 'sem', 'RawText']
struct haxorg_RawText {
  haxorg_RawText_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_Punctuation_vtable {};

/// \brief ['org', 'sem', 'Punctuation']
struct haxorg_Punctuation {
  haxorg_Punctuation_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_Placeholder_vtable {};

/// \brief ['org', 'sem', 'Placeholder']
struct haxorg_Placeholder {
  haxorg_Placeholder_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_BigIdent_vtable {};

/// \brief ['org', 'sem', 'BigIdent']
struct haxorg_BigIdent {
  haxorg_BigIdent_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_TextTarget_vtable {};

/// \brief ['org', 'sem', 'TextTarget']
struct haxorg_TextTarget {
  haxorg_TextTarget_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ErrorSkipToken_vtable {};

/// \brief ['org', 'sem', 'ErrorSkipToken']
struct haxorg_ErrorSkipToken {
  haxorg_ErrorSkipToken_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_Bold_vtable {};

/// \brief ['org', 'sem', 'Bold']
struct haxorg_Bold {
  haxorg_Bold_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_Underline_vtable {};

/// \brief ['org', 'sem', 'Underline']
struct haxorg_Underline {
  haxorg_Underline_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_Monospace_vtable {};

/// \brief ['org', 'sem', 'Monospace']
struct haxorg_Monospace {
  haxorg_Monospace_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_MarkQuote_vtable {};

/// \brief ['org', 'sem', 'MarkQuote']
struct haxorg_MarkQuote {
  haxorg_MarkQuote_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_Verbatim_vtable {};

/// \brief ['org', 'sem', 'Verbatim']
struct haxorg_Verbatim {
  haxorg_Verbatim_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_Italic_vtable {};

/// \brief ['org', 'sem', 'Italic']
struct haxorg_Italic {
  haxorg_Italic_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_Strike_vtable {};

/// \brief ['org', 'sem', 'Strike']
struct haxorg_Strike {
  haxorg_Strike_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_Par_vtable {};

/// \brief ['org', 'sem', 'Par']
struct haxorg_Par {
  haxorg_Par_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmd']
struct haxorg_ImmCmd {
  haxorg_ImmCmd_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdCustomRaw']
struct haxorg_ImmCmdCustomRaw {
  haxorg_ImmCmdCustomRaw_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdCustomText']
struct haxorg_ImmCmdCustomText {
  haxorg_ImmCmdCustomText_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmLink']
struct haxorg_ImmLink {
  haxorg_ImmLink_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmBlockComment']
struct haxorg_ImmBlockComment {
  haxorg_ImmBlockComment_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmParagraph']
struct haxorg_ImmParagraph {
  haxorg_ImmParagraph_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmList']
struct haxorg_ImmList {
  haxorg_ImmList_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmHashTag']
struct haxorg_ImmHashTag {
  haxorg_ImmHashTag_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmInlineFootnote']
struct haxorg_ImmInlineFootnote {
  haxorg_ImmInlineFootnote_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmInlineExport']
struct haxorg_ImmInlineExport {
  haxorg_ImmInlineExport_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmEscaped']
struct haxorg_ImmEscaped {
  haxorg_ImmEscaped_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmNewline']
struct haxorg_ImmNewline {
  haxorg_ImmNewline_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmSpace']
struct haxorg_ImmSpace {
  haxorg_ImmSpace_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmWord']
struct haxorg_ImmWord {
  haxorg_ImmWord_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAtMention']
struct haxorg_ImmAtMention {
  haxorg_ImmAtMention_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmRawText']
struct haxorg_ImmRawText {
  haxorg_ImmRawText_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmPunctuation']
struct haxorg_ImmPunctuation {
  haxorg_ImmPunctuation_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmPlaceholder']
struct haxorg_ImmPlaceholder {
  haxorg_ImmPlaceholder_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmBigIdent']
struct haxorg_ImmBigIdent {
  haxorg_ImmBigIdent_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmTextTarget']
struct haxorg_ImmTextTarget {
  haxorg_ImmTextTarget_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmErrorSkipToken']
struct haxorg_ImmErrorSkipToken {
  haxorg_ImmErrorSkipToken_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmBold']
struct haxorg_ImmBold {
  haxorg_ImmBold_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmUnderline']
struct haxorg_ImmUnderline {
  haxorg_ImmUnderline_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmMonospace']
struct haxorg_ImmMonospace {
  haxorg_ImmMonospace_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmMarkQuote']
struct haxorg_ImmMarkQuote {
  haxorg_ImmMarkQuote_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmVerbatim']
struct haxorg_ImmVerbatim {
  haxorg_ImmVerbatim_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmItalic']
struct haxorg_ImmItalic {
  haxorg_ImmItalic_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmStrike']
struct haxorg_ImmStrike {
  haxorg_ImmStrike_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmPar']
struct haxorg_ImmPar {
  haxorg_ImmPar_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterStmtAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterStmtAPI']
struct haxorg_ImmAdapterStmtAPI {
  haxorg_ImmAdapterStmtAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterSubtreeAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterSubtreeAPI']
struct haxorg_ImmAdapterSubtreeAPI {
  haxorg_ImmAdapterSubtreeAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterNoNodeAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterNoNodeAPI']
struct haxorg_ImmAdapterNoNodeAPI {
  haxorg_ImmAdapterNoNodeAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterAttrAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterAttrAPI']
struct haxorg_ImmAdapterAttrAPI {
  haxorg_ImmAdapterAttrAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterAttrListAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterAttrListAPI']
struct haxorg_ImmAdapterAttrListAPI {
  haxorg_ImmAdapterAttrListAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterAttrsAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterAttrsAPI']
struct haxorg_ImmAdapterAttrsAPI {
  haxorg_ImmAdapterAttrsAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterErrorItemAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterErrorItemAPI']
struct haxorg_ImmAdapterErrorItemAPI {
  haxorg_ImmAdapterErrorItemAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterErrorGroupAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterErrorGroupAPI']
struct haxorg_ImmAdapterErrorGroupAPI {
  haxorg_ImmAdapterErrorGroupAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterErrorSkipGroupAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterErrorSkipGroupAPI']
struct haxorg_ImmAdapterErrorSkipGroupAPI {
  haxorg_ImmAdapterErrorSkipGroupAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterErrorSkipTokenAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterErrorSkipTokenAPI']
struct haxorg_ImmAdapterErrorSkipTokenAPI {
  haxorg_ImmAdapterErrorSkipTokenAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterStmtListAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterStmtListAPI']
struct haxorg_ImmAdapterStmtListAPI {
  haxorg_ImmAdapterStmtListAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterEmptyAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterEmptyAPI']
struct haxorg_ImmAdapterEmptyAPI {
  haxorg_ImmAdapterEmptyAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterInlineAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterInlineAPI']
struct haxorg_ImmAdapterInlineAPI {
  haxorg_ImmAdapterInlineAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterTimeAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterTimeAPI']
struct haxorg_ImmAdapterTimeAPI {
  haxorg_ImmAdapterTimeAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterTimeRangeAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterTimeRangeAPI']
struct haxorg_ImmAdapterTimeRangeAPI {
  haxorg_ImmAdapterTimeRangeAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterMacroAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterMacroAPI']
struct haxorg_ImmAdapterMacroAPI {
  haxorg_ImmAdapterMacroAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterSymbolAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterSymbolAPI']
struct haxorg_ImmAdapterSymbolAPI {
  haxorg_ImmAdapterSymbolAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterLeafAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterLeafAPI']
struct haxorg_ImmAdapterLeafAPI {
  haxorg_ImmAdapterLeafAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterMarkupAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterMarkupAPI']
struct haxorg_ImmAdapterMarkupAPI {
  haxorg_ImmAdapterMarkupAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterLatexAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterLatexAPI']
struct haxorg_ImmAdapterLatexAPI {
  haxorg_ImmAdapterLatexAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterSubtreeLogAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterSubtreeLogAPI']
struct haxorg_ImmAdapterSubtreeLogAPI {
  haxorg_ImmAdapterSubtreeLogAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterColonExampleAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterColonExampleAPI']
struct haxorg_ImmAdapterColonExampleAPI {
  haxorg_ImmAdapterColonExampleAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterCallAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCallAPI']
struct haxorg_ImmAdapterCallAPI {
  haxorg_ImmAdapterCallAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterFileAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterFileAPI']
struct haxorg_ImmAdapterFileAPI {
  haxorg_ImmAdapterFileAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterDirectoryAPI']
struct haxorg_ImmAdapterDirectoryAPI {
  haxorg_ImmAdapterDirectoryAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterSymlinkAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterSymlinkAPI']
struct haxorg_ImmAdapterSymlinkAPI {
  haxorg_ImmAdapterSymlinkAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterDocumentFragmentAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterDocumentFragmentAPI']
struct haxorg_ImmAdapterDocumentFragmentAPI {
  haxorg_ImmAdapterDocumentFragmentAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterCriticMarkupAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCriticMarkupAPI']
struct haxorg_ImmAdapterCriticMarkupAPI {
  haxorg_ImmAdapterCriticMarkupAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterListItemAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterListItemAPI']
struct haxorg_ImmAdapterListItemAPI {
  haxorg_ImmAdapterListItemAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterDocumentOptionsAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterDocumentOptionsAPI']
struct haxorg_ImmAdapterDocumentOptionsAPI {
  haxorg_ImmAdapterDocumentOptionsAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterDocumentAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterDocumentAPI']
struct haxorg_ImmAdapterDocumentAPI {
  haxorg_ImmAdapterDocumentAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterFileTargetAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterFileTargetAPI']
struct haxorg_ImmAdapterFileTargetAPI {
  haxorg_ImmAdapterFileTargetAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterTextSeparatorAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterTextSeparatorAPI']
struct haxorg_ImmAdapterTextSeparatorAPI {
  haxorg_ImmAdapterTextSeparatorAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterCmdIncludeAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdIncludeAPI']
struct haxorg_ImmAdapterCmdIncludeAPI {
  haxorg_ImmAdapterCmdIncludeAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterDocumentGroupAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterDocumentGroupAPI']
struct haxorg_ImmAdapterDocumentGroupAPI {
  haxorg_ImmAdapterDocumentGroupAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_Block_vtable {};

/// \brief ['org', 'sem', 'Block']
struct haxorg_Block {
  haxorg_Block_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_LineCommand_vtable {};

/// \brief ['org', 'sem', 'LineCommand']
struct haxorg_LineCommand {
  haxorg_LineCommand_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdCreator']
struct haxorg_CmdCreator {
  haxorg_CmdCreator_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdAuthor']
struct haxorg_CmdAuthor {
  haxorg_CmdAuthor_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdEmail']
struct haxorg_CmdEmail {
  haxorg_CmdEmail_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdLanguage']
struct haxorg_CmdLanguage {
  haxorg_CmdLanguage_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdCustomArgs']
struct haxorg_CmdCustomArgs {
  haxorg_CmdCustomArgs_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdTblfm']
struct haxorg_CmdTblfm {
  haxorg_CmdTblfm_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Cell']
struct haxorg_Cell {
  haxorg_Cell_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Row']
struct haxorg_Row {
  haxorg_Row_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmBlock']
struct haxorg_ImmBlock {
  haxorg_ImmBlock_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmLineCommand']
struct haxorg_ImmLineCommand {
  haxorg_ImmLineCommand_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdCreator']
struct haxorg_ImmCmdCreator {
  haxorg_ImmCmdCreator_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdAuthor']
struct haxorg_ImmCmdAuthor {
  haxorg_ImmCmdAuthor_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdEmail']
struct haxorg_ImmCmdEmail {
  haxorg_ImmCmdEmail_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdLanguage']
struct haxorg_ImmCmdLanguage {
  haxorg_ImmCmdLanguage_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdCustomArgs']
struct haxorg_ImmCmdCustomArgs {
  haxorg_ImmCmdCustomArgs_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdTblfm']
struct haxorg_ImmCmdTblfm {
  haxorg_ImmCmdTblfm_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCell']
struct haxorg_ImmCell {
  haxorg_ImmCell_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmRow']
struct haxorg_ImmRow {
  haxorg_ImmRow_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterCmdAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdAPI']
struct haxorg_ImmAdapterCmdAPI {
  haxorg_ImmAdapterCmdAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterCmdCustomRawAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdCustomRawAPI']
struct haxorg_ImmAdapterCmdCustomRawAPI {
  haxorg_ImmAdapterCmdCustomRawAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterCmdCustomTextAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdCustomTextAPI']
struct haxorg_ImmAdapterCmdCustomTextAPI {
  haxorg_ImmAdapterCmdCustomTextAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterLinkAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterLinkAPI']
struct haxorg_ImmAdapterLinkAPI {
  haxorg_ImmAdapterLinkAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterBlockCommentAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterBlockCommentAPI']
struct haxorg_ImmAdapterBlockCommentAPI {
  haxorg_ImmAdapterBlockCommentAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterParagraphAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterParagraphAPI']
struct haxorg_ImmAdapterParagraphAPI {
  haxorg_ImmAdapterParagraphAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterListAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterListAPI']
struct haxorg_ImmAdapterListAPI {
  haxorg_ImmAdapterListAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmStmt']]]
struct haxorg_ImmStmtAdapter {
  haxorg_ImmStmtAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmNoNodeAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmNoNode']]]
struct haxorg_ImmNoNodeAdapter {
  haxorg_ImmNoNodeAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmErrorItem']]]
struct haxorg_ImmErrorItemAdapter {
  haxorg_ImmErrorItemAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmErrorGroup']]]
struct haxorg_ImmErrorGroupAdapter {
  haxorg_ImmErrorGroupAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmErrorSkipGroup']]]
struct haxorg_ImmErrorSkipGroupAdapter {
  haxorg_ImmErrorSkipGroupAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmErrorSkipTokenAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmErrorSkipToken']]]
struct haxorg_ImmErrorSkipTokenAdapter {
  haxorg_ImmErrorSkipTokenAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmStmtListAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmStmtList']]]
struct haxorg_ImmStmtListAdapter {
  haxorg_ImmStmtListAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmEmptyAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmEmpty']]]
struct haxorg_ImmEmptyAdapter {
  haxorg_ImmEmptyAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterHashTagAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterHashTagAPI']
struct haxorg_ImmAdapterHashTagAPI {
  haxorg_ImmAdapterHashTagAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterInlineFootnoteAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterInlineFootnoteAPI']
struct haxorg_ImmAdapterInlineFootnoteAPI {
  haxorg_ImmAdapterInlineFootnoteAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterSubtreeCompletionAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterSubtreeCompletionAPI']
struct haxorg_ImmAdapterSubtreeCompletionAPI {
  haxorg_ImmAdapterSubtreeCompletionAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmInlineAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmInline']]]
struct haxorg_ImmInlineAdapter {
  haxorg_ImmInlineAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmTime']]]
struct haxorg_ImmTimeAdapter {
  haxorg_ImmTimeAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmTimeRange']]]
struct haxorg_ImmTimeRangeAdapter {
  haxorg_ImmTimeRangeAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmMacro']]]
struct haxorg_ImmMacroAdapter {
  haxorg_ImmMacroAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmSymbol']]]
struct haxorg_ImmSymbolAdapter {
  haxorg_ImmSymbolAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterEscapedAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterEscapedAPI']
struct haxorg_ImmAdapterEscapedAPI {
  haxorg_ImmAdapterEscapedAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterNewlineAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterNewlineAPI']
struct haxorg_ImmAdapterNewlineAPI {
  haxorg_ImmAdapterNewlineAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterSpaceAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterSpaceAPI']
struct haxorg_ImmAdapterSpaceAPI {
  haxorg_ImmAdapterSpaceAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterWordAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterWordAPI']
struct haxorg_ImmAdapterWordAPI {
  haxorg_ImmAdapterWordAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterAtMentionAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterAtMentionAPI']
struct haxorg_ImmAdapterAtMentionAPI {
  haxorg_ImmAdapterAtMentionAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterRawTextAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterRawTextAPI']
struct haxorg_ImmAdapterRawTextAPI {
  haxorg_ImmAdapterRawTextAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterPunctuationAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterPunctuationAPI']
struct haxorg_ImmAdapterPunctuationAPI {
  haxorg_ImmAdapterPunctuationAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterPlaceholderAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterPlaceholderAPI']
struct haxorg_ImmAdapterPlaceholderAPI {
  haxorg_ImmAdapterPlaceholderAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterBigIdentAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterBigIdentAPI']
struct haxorg_ImmAdapterBigIdentAPI {
  haxorg_ImmAdapterBigIdentAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterTextTargetAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterTextTargetAPI']
struct haxorg_ImmAdapterTextTargetAPI {
  haxorg_ImmAdapterTextTargetAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmLeaf']]]
struct haxorg_ImmLeafAdapter {
  haxorg_ImmLeafAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterBoldAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterBoldAPI']
struct haxorg_ImmAdapterBoldAPI {
  haxorg_ImmAdapterBoldAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterUnderlineAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterUnderlineAPI']
struct haxorg_ImmAdapterUnderlineAPI {
  haxorg_ImmAdapterUnderlineAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterMonospaceAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterMonospaceAPI']
struct haxorg_ImmAdapterMonospaceAPI {
  haxorg_ImmAdapterMonospaceAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterMarkQuoteAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterMarkQuoteAPI']
struct haxorg_ImmAdapterMarkQuoteAPI {
  haxorg_ImmAdapterMarkQuoteAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterRadioTargetAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterRadioTargetAPI']
struct haxorg_ImmAdapterRadioTargetAPI {
  haxorg_ImmAdapterRadioTargetAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterVerbatimAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterVerbatimAPI']
struct haxorg_ImmAdapterVerbatimAPI {
  haxorg_ImmAdapterVerbatimAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterItalicAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterItalicAPI']
struct haxorg_ImmAdapterItalicAPI {
  haxorg_ImmAdapterItalicAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterStrikeAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterStrikeAPI']
struct haxorg_ImmAdapterStrikeAPI {
  haxorg_ImmAdapterStrikeAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterParAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterParAPI']
struct haxorg_ImmAdapterParAPI {
  haxorg_ImmAdapterParAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmMarkupAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmMarkup']]]
struct haxorg_ImmMarkupAdapter {
  haxorg_ImmMarkupAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmLatexAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmLatex']]]
struct haxorg_ImmLatexAdapter {
  haxorg_ImmLatexAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmSubtreeLog']]]
struct haxorg_ImmSubtreeLogAdapter {
  haxorg_ImmSubtreeLogAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmColonExampleAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmColonExample']]]
struct haxorg_ImmColonExampleAdapter {
  haxorg_ImmColonExampleAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCall']]]
struct haxorg_ImmCallAdapter {
  haxorg_ImmCallAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmFile']]]
struct haxorg_ImmFileAdapter {
  haxorg_ImmFileAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmDirectory']]]
struct haxorg_ImmDirectoryAdapter {
  haxorg_ImmDirectoryAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmSymlink']]]
struct haxorg_ImmSymlinkAdapter {
  haxorg_ImmSymlinkAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmDocumentFragment']]]
struct haxorg_ImmDocumentFragmentAdapter {
  haxorg_ImmDocumentFragmentAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCriticMarkup']]]
struct haxorg_ImmCriticMarkupAdapter {
  haxorg_ImmCriticMarkupAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmListItem']]]
struct haxorg_ImmListItemAdapter {
  haxorg_ImmListItemAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmDocumentOptions']]]
struct haxorg_ImmDocumentOptionsAdapter {
  haxorg_ImmDocumentOptionsAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmDocument']]]
struct haxorg_ImmDocumentAdapter {
  haxorg_ImmDocumentAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmFileTarget']]]
struct haxorg_ImmFileTargetAdapter {
  haxorg_ImmFileTargetAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmTextSeparatorAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmTextSeparator']]]
struct haxorg_ImmTextSeparatorAdapter {
  haxorg_ImmTextSeparatorAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdInclude']]]
struct haxorg_ImmCmdIncludeAdapter {
  haxorg_ImmCmdIncludeAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmDocumentGroupAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmDocumentGroup']]]
struct haxorg_ImmDocumentGroupAdapter {
  haxorg_ImmDocumentGroupAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_BlockCenter_vtable {};

/// \brief ['org', 'sem', 'BlockCenter']
struct haxorg_BlockCenter {
  haxorg_BlockCenter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_BlockQuote_vtable {};

/// \brief ['org', 'sem', 'BlockQuote']
struct haxorg_BlockQuote {
  haxorg_BlockQuote_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_BlockVerse_vtable {};

/// \brief ['org', 'sem', 'BlockVerse']
struct haxorg_BlockVerse {
  haxorg_BlockVerse_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockDynamicFallback']
struct haxorg_BlockDynamicFallback {
  haxorg_BlockDynamicFallback_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_BlockExample_vtable {};

/// \brief ['org', 'sem', 'BlockExample']
struct haxorg_BlockExample {
  haxorg_BlockExample_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockExport']
struct haxorg_BlockExport {
  haxorg_BlockExport_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_BlockAdmonition_vtable {};

/// \brief ['org', 'sem', 'BlockAdmonition']
struct haxorg_BlockAdmonition {
  haxorg_BlockAdmonition_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockCodeEvalResult']
struct haxorg_BlockCodeEvalResult {
  haxorg_BlockCodeEvalResult_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'BlockCode']
struct haxorg_BlockCode {
  haxorg_BlockCode_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'Table']
struct haxorg_Table {
  haxorg_Table_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_Attached_vtable {};

/// \brief ['org', 'sem', 'Attached']
struct haxorg_Attached {
  haxorg_Attached_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmBlockCenter']
struct haxorg_ImmBlockCenter {
  haxorg_ImmBlockCenter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmBlockQuote']
struct haxorg_ImmBlockQuote {
  haxorg_ImmBlockQuote_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmBlockVerse']
struct haxorg_ImmBlockVerse {
  haxorg_ImmBlockVerse_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmBlockDynamicFallback']
struct haxorg_ImmBlockDynamicFallback {
  haxorg_ImmBlockDynamicFallback_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmBlockExample']
struct haxorg_ImmBlockExample {
  haxorg_ImmBlockExample_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmBlockExport']
struct haxorg_ImmBlockExport {
  haxorg_ImmBlockExport_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmBlockAdmonition']
struct haxorg_ImmBlockAdmonition {
  haxorg_ImmBlockAdmonition_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmBlockCodeEvalResult']
struct haxorg_ImmBlockCodeEvalResult {
  haxorg_ImmBlockCodeEvalResult_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmBlockCode']
struct haxorg_ImmBlockCode {
  haxorg_ImmBlockCode_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmTable']
struct haxorg_ImmTable {
  haxorg_ImmTable_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAttached']
struct haxorg_ImmAttached {
  haxorg_ImmAttached_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterLineCommandAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterLineCommandAPI']
struct haxorg_ImmAdapterLineCommandAPI {
  haxorg_ImmAdapterLineCommandAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterCmdCustomArgsAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdCustomArgsAPI']
struct haxorg_ImmAdapterCmdCustomArgsAPI {
  haxorg_ImmAdapterCmdCustomArgsAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterCmdCreatorAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdCreatorAPI']
struct haxorg_ImmAdapterCmdCreatorAPI {
  haxorg_ImmAdapterCmdCreatorAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterCmdAuthorAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdAuthorAPI']
struct haxorg_ImmAdapterCmdAuthorAPI {
  haxorg_ImmAdapterCmdAuthorAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterCmdEmailAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdEmailAPI']
struct haxorg_ImmAdapterCmdEmailAPI {
  haxorg_ImmAdapterCmdEmailAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterCmdLanguageAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdLanguageAPI']
struct haxorg_ImmAdapterCmdLanguageAPI {
  haxorg_ImmAdapterCmdLanguageAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterCmdTblfmAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdTblfmAPI']
struct haxorg_ImmAdapterCmdTblfmAPI {
  haxorg_ImmAdapterCmdTblfmAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterBlockAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterBlockAPI']
struct haxorg_ImmAdapterBlockAPI {
  haxorg_ImmAdapterBlockAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterCellAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCellAPI']
struct haxorg_ImmAdapterCellAPI {
  haxorg_ImmAdapterCellAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterRowAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterRowAPI']
struct haxorg_ImmAdapterRowAPI {
  haxorg_ImmAdapterRowAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmd']]]
struct haxorg_ImmCmdAdapter {
  haxorg_ImmCmdAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdCustomRaw']]]
struct haxorg_ImmCmdCustomRawAdapter {
  haxorg_ImmCmdCustomRawAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdCustomText']]]
struct haxorg_ImmCmdCustomTextAdapter {
  haxorg_ImmCmdCustomTextAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmBlockCommentAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlockComment']]]
struct haxorg_ImmBlockCommentAdapter {
  haxorg_ImmBlockCommentAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmParagraphAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmParagraph']]]
struct haxorg_ImmParagraphAdapter {
  haxorg_ImmParagraphAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmListAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmList']]]
struct haxorg_ImmListAdapter {
  haxorg_ImmListAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmHashTag']]]
struct haxorg_ImmHashTagAdapter {
  haxorg_ImmHashTagAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmInlineFootnote']]]
struct haxorg_ImmInlineFootnoteAdapter {
  haxorg_ImmInlineFootnoteAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmEscapedAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmEscaped']]]
struct haxorg_ImmEscapedAdapter {
  haxorg_ImmEscapedAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmNewlineAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmNewline']]]
struct haxorg_ImmNewlineAdapter {
  haxorg_ImmNewlineAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmSpaceAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmSpace']]]
struct haxorg_ImmSpaceAdapter {
  haxorg_ImmSpaceAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmWordAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmWord']]]
struct haxorg_ImmWordAdapter {
  haxorg_ImmWordAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAtMentionAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmAtMention']]]
struct haxorg_ImmAtMentionAdapter {
  haxorg_ImmAtMentionAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmRawTextAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmRawText']]]
struct haxorg_ImmRawTextAdapter {
  haxorg_ImmRawTextAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmPunctuationAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmPunctuation']]]
struct haxorg_ImmPunctuationAdapter {
  haxorg_ImmPunctuationAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmPlaceholderAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmPlaceholder']]]
struct haxorg_ImmPlaceholderAdapter {
  haxorg_ImmPlaceholderAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmBigIdentAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBigIdent']]]
struct haxorg_ImmBigIdentAdapter {
  haxorg_ImmBigIdentAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmTextTargetAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmTextTarget']]]
struct haxorg_ImmTextTargetAdapter {
  haxorg_ImmTextTargetAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmBoldAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBold']]]
struct haxorg_ImmBoldAdapter {
  haxorg_ImmBoldAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmUnderlineAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmUnderline']]]
struct haxorg_ImmUnderlineAdapter {
  haxorg_ImmUnderlineAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmMonospaceAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmMonospace']]]
struct haxorg_ImmMonospaceAdapter {
  haxorg_ImmMonospaceAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmMarkQuoteAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmMarkQuote']]]
struct haxorg_ImmMarkQuoteAdapter {
  haxorg_ImmMarkQuoteAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmRadioTarget']]]
struct haxorg_ImmRadioTargetAdapter {
  haxorg_ImmRadioTargetAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmVerbatimAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmVerbatim']]]
struct haxorg_ImmVerbatimAdapter {
  haxorg_ImmVerbatimAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmItalicAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmItalic']]]
struct haxorg_ImmItalicAdapter {
  haxorg_ImmItalicAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmStrikeAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmStrike']]]
struct haxorg_ImmStrikeAdapter {
  haxorg_ImmStrikeAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmParAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmPar']]]
struct haxorg_ImmParAdapter {
  haxorg_ImmParAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdCaption']
struct haxorg_CmdCaption {
  haxorg_CmdCaption_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdColumns']
struct haxorg_CmdColumns {
  haxorg_CmdColumns_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdName']
struct haxorg_CmdName {
  haxorg_CmdName_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdCall']
struct haxorg_CmdCall {
  haxorg_CmdCall_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdAttr']
struct haxorg_CmdAttr {
  haxorg_CmdAttr_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'sem', 'CmdExport']
struct haxorg_CmdExport {
  haxorg_CmdExport_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdCaption']
struct haxorg_ImmCmdCaption {
  haxorg_ImmCmdCaption_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdColumns']
struct haxorg_ImmCmdColumns {
  haxorg_ImmCmdColumns_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdName']
struct haxorg_ImmCmdName {
  haxorg_ImmCmdName_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdCall']
struct haxorg_ImmCmdCall {
  haxorg_ImmCmdCall_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdAttr']
struct haxorg_ImmCmdAttr {
  haxorg_ImmCmdAttr_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmCmdExport']
struct haxorg_ImmCmdExport {
  haxorg_ImmCmdExport_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterAttachedAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterAttachedAPI']
struct haxorg_ImmAdapterAttachedAPI {
  haxorg_ImmAdapterAttachedAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmLineCommandAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmLineCommand']]]
struct haxorg_ImmLineCommandAdapter {
  haxorg_ImmLineCommandAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdCustomArgs']]]
struct haxorg_ImmCmdCustomArgsAdapter {
  haxorg_ImmCmdCustomArgsAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdCreator']]]
struct haxorg_ImmCmdCreatorAdapter {
  haxorg_ImmCmdCreatorAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdAuthor']]]
struct haxorg_ImmCmdAuthorAdapter {
  haxorg_ImmCmdAuthorAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdEmail']]]
struct haxorg_ImmCmdEmailAdapter {
  haxorg_ImmCmdEmailAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdLanguage']]]
struct haxorg_ImmCmdLanguageAdapter {
  haxorg_ImmCmdLanguageAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdTblfm']]]
struct haxorg_ImmCmdTblfmAdapter {
  haxorg_ImmCmdTblfmAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterBlockCenterAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterBlockCenterAPI']
struct haxorg_ImmAdapterBlockCenterAPI {
  haxorg_ImmAdapterBlockCenterAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterBlockQuoteAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterBlockQuoteAPI']
struct haxorg_ImmAdapterBlockQuoteAPI {
  haxorg_ImmAdapterBlockQuoteAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterBlockVerseAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterBlockVerseAPI']
struct haxorg_ImmAdapterBlockVerseAPI {
  haxorg_ImmAdapterBlockVerseAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterBlockExampleAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterBlockExampleAPI']
struct haxorg_ImmAdapterBlockExampleAPI {
  haxorg_ImmAdapterBlockExampleAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterInlineExportAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterInlineExportAPI']
struct haxorg_ImmAdapterInlineExportAPI {
  haxorg_ImmAdapterInlineExportAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterCmdExportAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdExportAPI']
struct haxorg_ImmAdapterCmdExportAPI {
  haxorg_ImmAdapterCmdExportAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterBlockExportAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterBlockExportAPI']
struct haxorg_ImmAdapterBlockExportAPI {
  haxorg_ImmAdapterBlockExportAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterBlockDynamicFallbackAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterBlockDynamicFallbackAPI']
struct haxorg_ImmAdapterBlockDynamicFallbackAPI {
  haxorg_ImmAdapterBlockDynamicFallbackAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterBlockAdmonitionAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterBlockAdmonitionAPI']
struct haxorg_ImmAdapterBlockAdmonitionAPI {
  haxorg_ImmAdapterBlockAdmonitionAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterBlockCodeEvalResultAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterBlockCodeEvalResultAPI']
struct haxorg_ImmAdapterBlockCodeEvalResultAPI {
  haxorg_ImmAdapterBlockCodeEvalResultAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterBlockCodeAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterBlockCodeAPI']
struct haxorg_ImmAdapterBlockCodeAPI {
  haxorg_ImmAdapterBlockCodeAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterTableAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterTableAPI']
struct haxorg_ImmAdapterTableAPI {
  haxorg_ImmAdapterTableAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmBlockAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlock']]]
struct haxorg_ImmBlockAdapter {
  haxorg_ImmBlockAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCell']]]
struct haxorg_ImmCellAdapter {
  haxorg_ImmCellAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmRow']]]
struct haxorg_ImmRowAdapter {
  haxorg_ImmRowAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterCmdCaptionAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdCaptionAPI']
struct haxorg_ImmAdapterCmdCaptionAPI {
  haxorg_ImmAdapterCmdCaptionAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterCmdColumnsAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdColumnsAPI']
struct haxorg_ImmAdapterCmdColumnsAPI {
  haxorg_ImmAdapterCmdColumnsAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterCmdNameAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdNameAPI']
struct haxorg_ImmAdapterCmdNameAPI {
  haxorg_ImmAdapterCmdNameAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterCmdCallAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdCallAPI']
struct haxorg_ImmAdapterCmdCallAPI {
  haxorg_ImmAdapterCmdCallAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterCmdResultsAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdResultsAPI']
struct haxorg_ImmAdapterCmdResultsAPI {
  haxorg_ImmAdapterCmdResultsAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAdapterCmdAttrAPI_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterCmdAttrAPI']
struct haxorg_ImmAdapterCmdAttrAPI {
  haxorg_ImmAdapterCmdAttrAPI_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmAttachedAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmAttached']]]
struct haxorg_ImmAttachedAdapter {
  haxorg_ImmAttachedAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmBlockCenterAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlockCenter']]]
struct haxorg_ImmBlockCenterAdapter {
  haxorg_ImmBlockCenterAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmBlockQuoteAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlockQuote']]]
struct haxorg_ImmBlockQuoteAdapter {
  haxorg_ImmBlockQuoteAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmBlockVerseAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlockVerse']]]
struct haxorg_ImmBlockVerseAdapter {
  haxorg_ImmBlockVerseAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmBlockExampleAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlockExample']]]
struct haxorg_ImmBlockExampleAdapter {
  haxorg_ImmBlockExampleAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmInlineExport']]]
struct haxorg_ImmInlineExportAdapter {
  haxorg_ImmInlineExportAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdExport']]]
struct haxorg_ImmCmdExportAdapter {
  haxorg_ImmCmdExportAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlockExport']]]
struct haxorg_ImmBlockExportAdapter {
  haxorg_ImmBlockExportAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlockDynamicFallback']]]
struct haxorg_ImmBlockDynamicFallbackAdapter {
  haxorg_ImmBlockDynamicFallbackAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_ImmBlockAdmonitionAdapter_vtable {};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlockAdmonition']]]
struct haxorg_ImmBlockAdmonitionAdapter {
  haxorg_ImmBlockAdmonitionAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlockCodeEvalResult']]]
struct haxorg_ImmBlockCodeEvalResultAdapter {
  haxorg_ImmBlockCodeEvalResultAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmBlockCode']]]
struct haxorg_ImmBlockCodeAdapter {
  haxorg_ImmBlockCodeAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmTable']]]
struct haxorg_ImmTableAdapter {
  haxorg_ImmTableAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdCaption']]]
struct haxorg_ImmCmdCaptionAdapter {
  haxorg_ImmCmdCaptionAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdColumns']]]
struct haxorg_ImmCmdColumnsAdapter {
  haxorg_ImmCmdColumnsAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdName']]]
struct haxorg_ImmCmdNameAdapter {
  haxorg_ImmCmdNameAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdCall']]]
struct haxorg_ImmCmdCallAdapter {
  haxorg_ImmCmdCallAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

/// \brief ['org', 'imm', 'ImmAdapterT', [['org', 'imm', 'ImmCmdAttr']]]
struct haxorg_ImmCmdAttrAdapter {
  haxorg_ImmCmdAttrAdapter_vtable const* vtable;
  haxorg_ptr_payload data;
};

struct haxorg_UserTimeBreakdown_vtable {
  haxorg_StdOptional const* (*get_year)(OrgContext*, haxorg_UserTimeBreakdown const*);
  haxorg_StdOptional const* (*get_month)(OrgContext*, haxorg_UserTimeBreakdown const*);
  haxorg_StdOptional const* (*get_day)(OrgContext*, haxorg_UserTimeBreakdown const*);
  haxorg_StdOptional const* (*get_hour)(OrgContext*, haxorg_UserTimeBreakdown const*);
  haxorg_StdOptional const* (*get_minute)(OrgContext*, haxorg_UserTimeBreakdown const*);
  haxorg_StdOptional const* (*get_second)(OrgContext*, haxorg_UserTimeBreakdown const*);
  haxorg_StdOptional const* (*get_zone)(OrgContext*, haxorg_UserTimeBreakdown const*);
};

struct haxorg_UserTime_vtable {
  haxorg_UserTimeBreakdown (*getBreakdown_const)(OrgContext*, haxorg_UserTime);
  haxorg_StdString (*format_const)(OrgContext*, haxorg_UserTime);
  int64_t (*getTimeDeltaSeconds_const)(OrgContext*, haxorg_UserTime, haxorg_UserTime);
  int64_t (*toUnixTimestamp_const)(OrgContext*, haxorg_UserTime);
};

struct haxorg_ParseSourceManager_vtable {
  haxorg_StdString (*getPath_const)(OrgContext*, haxorg_ParseSourceManager, haxorg_ParseSourceFileId);
  haxorg_ParseSourceFileId (*getId_const)(OrgContext*, haxorg_ParseSourceManager, haxorg_StdString);
  haxorg_StdString (*getSourceContent_const)(OrgContext*, haxorg_ParseSourceManager, haxorg_ParseSourceFileId);
  haxorg_StdString (*getContentTextForPath_const)(OrgContext*, haxorg_ParseSourceManager, haxorg_StdString);
  haxorg_ParseSourceFileId (*addSource)(OrgContext*, haxorg_ParseSourceManager, haxorg_StdString, haxorg_StdString);
};

struct haxorg_ParseSourceLoc_vtable {
  int const* (*get_line)(OrgContext*, haxorg_ParseSourceLoc const*);
  int const* (*get_column)(OrgContext*, haxorg_ParseSourceLoc const*);
  int const* (*get_pos)(OrgContext*, haxorg_ParseSourceLoc const*);
  haxorg_ParseSourceFileId const* (*get_file_id)(OrgContext*, haxorg_ParseSourceLoc const*);
};

struct haxorg_OrgJson_vtable {
  haxorg_OrgJsonKind (*getKind_const)(OrgContext*, haxorg_OrgJson);
  haxorg_StdString (*getJsonString_const)(OrgContext*, haxorg_OrgJson);
  haxorg_OrgJson (*atIndex_const)(OrgContext*, haxorg_OrgJson, int);
  haxorg_OrgJson (*atField_const)(OrgContext*, haxorg_OrgJson, haxorg_StdString);
  haxorg_StdString (*getString_const)(OrgContext*, haxorg_OrgJson);
  haxorg_OrgJson (*getField_const)(OrgContext*, haxorg_OrgJson, haxorg_StdString);
  haxorg_OrgJson (*getItem_const)(OrgContext*, haxorg_OrgJson, int);
  int (*getInt_const)(OrgContext*, haxorg_OrgJson);
  bool (*getBool_const)(OrgContext*, haxorg_OrgJson);
  haxorg_HstdVec (*getArray_const)(OrgContext*, haxorg_OrgJson);
  haxorg_StdString (*dump_const)(OrgContext*, haxorg_OrgJson, int);
};

struct haxorg_Org_vtable {
  haxorg_StdOptional const* (*get_loc)(OrgContext*, haxorg_Org const*);
  haxorg_HstdVec const* (*get_subnodes)(OrgContext*, haxorg_Org const*);
  haxorg_OrgSemKind (*getKind_const)(OrgContext*, haxorg_Org);
  void (*push_back)(OrgContext*, haxorg_Org, haxorg_SemId);
  int (*size_const)(OrgContext*, haxorg_Org);
  void (*insert)(OrgContext*, haxorg_Org, int, haxorg_SemId);
  haxorg_SemId (*at_const)(OrgContext*, haxorg_Org, int);
  bool (*is_const)(OrgContext*, haxorg_Org, haxorg_OrgSemKind);
};

struct haxorg_OperationsTracer_vtable {
  bool const* (*get_TraceState)(OrgContext*, haxorg_OperationsTracer const*);
  bool const* (*get_traceToFile)(OrgContext*, haxorg_OperationsTracer const*);
  bool const* (*get_traceToBuffer)(OrgContext*, haxorg_OperationsTracer const*);
  bool const* (*get_traceStructured)(OrgContext*, haxorg_OperationsTracer const*);
  bool const* (*get_traceColored)(OrgContext*, haxorg_OperationsTracer const*);
  int const* (*get_activeLevel)(OrgContext*, haxorg_OperationsTracer const*);
  haxorg_StdString const* (*get_traceBuffer)(OrgContext*, haxorg_OperationsTracer const*);
  void (*setTraceFileStr)(OrgContext*, haxorg_OperationsTracer, haxorg_StdString, bool);
  void (*sendMessage)(OrgContext*, haxorg_OperationsTracer, haxorg_StdString, haxorg_StdString, int, haxorg_StdString);
};

struct haxorg_ParseOrgParseFragment_vtable {
  int const* (*get_baseLine)(OrgContext*, haxorg_ParseOrgParseFragment const*);
  int const* (*get_baseCol)(OrgContext*, haxorg_ParseOrgParseFragment const*);
  haxorg_StdString const* (*get_text)(OrgContext*, haxorg_ParseOrgParseFragment const*);
};

struct haxorg_OrgParseParameters_vtable {
  haxorg_StdOptional const* (*get_baseTokenTracePath)(OrgContext*, haxorg_OrgParseParameters const*);
  haxorg_StdOptional const* (*get_tokenTracePath)(OrgContext*, haxorg_OrgParseParameters const*);
  haxorg_StdOptional const* (*get_parseTracePath)(OrgContext*, haxorg_OrgParseParameters const*);
  haxorg_StdOptional const* (*get_semTracePath)(OrgContext*, haxorg_OrgParseParameters const*);
};

struct haxorg_ParseContext_vtable {
  haxorg_Cache (*getDiagnosticStrings)(OrgContext*, haxorg_ParseContext);
  haxorg_ParseSourceFileId (*addSource_const)(OrgContext*, haxorg_ParseContext, haxorg_StdString, haxorg_StdString);
  haxorg_SemId (*parseFileOpts)(OrgContext*, haxorg_ParseContext, haxorg_StdString, haxorg_OrgParseParameters);
  haxorg_SemId (*parseFile)(OrgContext*, haxorg_ParseContext, haxorg_StdString);
  haxorg_SemId (*parseString)(OrgContext*, haxorg_ParseContext, haxorg_StdString, haxorg_StdString);
  haxorg_SemId (*parseStringOpts)(OrgContext*, haxorg_ParseContext, haxorg_StdString, haxorg_StdString, haxorg_OrgParseParameters);
  haxorg_StdOptional (*parseDirectory)(OrgContext*, haxorg_ParseContext, haxorg_StdString);
  haxorg_StdOptional (*parseDirectoryOpts)(OrgContext*, haxorg_ParseContext, haxorg_StdString, haxorg_OrgDirectoryParseParameters);
  haxorg_SemId (*parseFileWithIncludes)(OrgContext*, haxorg_ParseContext, haxorg_StdString, haxorg_OrgDirectoryParseParameters);
  haxorg_HstdVec (*collectDiagnostics)(OrgContext*, haxorg_ParseContext, haxorg_SemId, haxorg_Cache);
  haxorg_HstdVec (*collectErrorNodes)(OrgContext*, haxorg_ParseContext, haxorg_SemId);
};

struct haxorg_ImmReflFieldId_vtable {
  haxorg_HstdStr (*getName_const)(OrgContext*, haxorg_ImmReflFieldId);
};

struct haxorg_ImmId_vtable {
  haxorg_OrgSemKind (*getKind_const)(OrgContext*, haxorg_ImmId);
  bool (*is_const)(OrgContext*, haxorg_ImmId, haxorg_OrgSemKind);
  haxorg_ImmIdNodeIdxT (*getNodeIndex_const)(OrgContext*, haxorg_ImmId);
  haxorg_StdString (*getReadableId_const)(OrgContext*, haxorg_ImmId);
};

struct haxorg_ImmPath_vtable {
  haxorg_ImmId const* (*get_root)(OrgContext*, haxorg_ImmPath const*);
  haxorg_ImmPathStore const* (*get_path)(OrgContext*, haxorg_ImmPath const*);
  bool (*empty_const)(OrgContext*, haxorg_ImmPath);
};

struct haxorg_ImmAstContext_vtable {
  haxorg_ImmAstVersion (*addRoot)(OrgContext*, haxorg_ImmAstContext, haxorg_SemId);
  haxorg_ImmAstVersion (*getEmptyVersion)(OrgContext*, haxorg_ImmAstContext);
  haxorg_SemId (*get)(OrgContext*, haxorg_ImmAstContext, haxorg_ImmId);
};

struct haxorg_ImmAstVersion_vtable {
  haxorg_ImmId (*getRoot_const)(OrgContext*, haxorg_ImmAstVersion);
  haxorg_ImmAdapter (*getRootAdapter_const)(OrgContext*, haxorg_ImmAstVersion);
  haxorg_ImmAstContext (*getContext_const)(OrgContext*, haxorg_ImmAstVersion);
  haxorg_ImmAstReplaceEpoch (*getEpoch_const)(OrgContext*, haxorg_ImmAstVersion);
};

struct haxorg_ImmAdapterTreeReprConf_vtable {
  int const* (*get_maxDepth)(OrgContext*, haxorg_ImmAdapterTreeReprConf const*);
  bool const* (*get_withAuxFields)(OrgContext*, haxorg_ImmAdapterTreeReprConf const*);
  bool const* (*get_withReflFields)(OrgContext*, haxorg_ImmAdapterTreeReprConf const*);
  haxorg_HstdUnorderedSet const* (*get_withFieldSubset)(OrgContext*, haxorg_ImmAdapterTreeReprConf const*);
};

struct haxorg_ImmAdapter_vtable {
  int (*size_const)(OrgContext*, haxorg_ImmAdapter);
  bool (*isNil_const)(OrgContext*, haxorg_ImmAdapter);
  bool (*isRoot_const)(OrgContext*, haxorg_ImmAdapter);
  haxorg_OrgSemKind (*getKind_const)(OrgContext*, haxorg_ImmAdapter);
  haxorg_ImmUniqId (*uniq_const)(OrgContext*, haxorg_ImmAdapter);
  haxorg_StdString (*treeReprString_const)(OrgContext*, haxorg_ImmAdapter);
  haxorg_StdString (*treeReprStringOpts_const)(OrgContext*, haxorg_ImmAdapter, haxorg_ImmAdapterTreeReprConf);
  bool (*isDirectParentOf_const)(OrgContext*, haxorg_ImmAdapter, haxorg_ImmAdapter);
  bool (*isIndirectParentOf_const)(OrgContext*, haxorg_ImmAdapter, haxorg_ImmAdapter);
  bool (*isSubnodeOf_const)(OrgContext*, haxorg_ImmAdapter, haxorg_ImmAdapter);
  haxorg_StdOptional (*getParent_const)(OrgContext*, haxorg_ImmAdapter);
  int (*getSelfIndex_const)(OrgContext*, haxorg_ImmAdapter);
  haxorg_ImmAdapter (*atPathStep_const)(OrgContext*, haxorg_ImmAdapter, haxorg_ImmId, haxorg_ImmPathStep);
  haxorg_ImmAdapter (*atField_const)(OrgContext*, haxorg_ImmAdapter, haxorg_ImmReflFieldId);
  haxorg_ImmAdapter (*atIndex_const)(OrgContext*, haxorg_ImmAdapter, int, bool);
  haxorg_ImmAdapter (*atPath_const)(OrgContext*, haxorg_ImmAdapter, haxorg_HstdVec, bool);
  bool (*is_const)(OrgContext*, haxorg_ImmAdapter, haxorg_OrgSemKind);
  haxorg_HstdVec (*sub_const)(OrgContext*, haxorg_ImmAdapter, bool);
};

struct haxorg_OrgYamlExportOpts_vtable {
  bool const* (*get_skipNullFields)(OrgContext*, haxorg_OrgYamlExportOpts const*);
  bool const* (*get_skipFalseFields)(OrgContext*, haxorg_OrgYamlExportOpts const*);
  bool const* (*get_skipZeroFields)(OrgContext*, haxorg_OrgYamlExportOpts const*);
  bool const* (*get_skipLocation)(OrgContext*, haxorg_OrgYamlExportOpts const*);
  bool const* (*get_skipId)(OrgContext*, haxorg_OrgYamlExportOpts const*);
};

struct haxorg_OrgTreeExportOpts_vtable {
  bool const* (*get_withLineCol)(OrgContext*, haxorg_OrgTreeExportOpts const*);
  bool const* (*get_withOriginalId)(OrgContext*, haxorg_OrgTreeExportOpts const*);
  bool const* (*get_withSubnodeIdx)(OrgContext*, haxorg_OrgTreeExportOpts const*);
  bool const* (*get_skipEmptyFields)(OrgContext*, haxorg_OrgTreeExportOpts const*);
  int const* (*get_startLevel)(OrgContext*, haxorg_OrgTreeExportOpts const*);
  bool const* (*get_withColor)(OrgContext*, haxorg_OrgTreeExportOpts const*);
  int const* (*get_maxDepth)(OrgContext*, haxorg_OrgTreeExportOpts const*);
};

struct haxorg_AstTrackingPath_vtable {
  haxorg_HstdVec const* (*get_path)(OrgContext*, haxorg_AstTrackingPath const*);
  haxorg_SemId (*getParent_const)(OrgContext*, haxorg_AstTrackingPath, int);
  haxorg_SemId (*getNode_const)(OrgContext*, haxorg_AstTrackingPath);
};

struct haxorg_AstTrackingAlternatives_vtable {
  haxorg_HstdVec (*getAllNodes_const)(OrgContext*, haxorg_AstTrackingAlternatives);
  haxorg_SemId (*getNode_const)(OrgContext*, haxorg_AstTrackingAlternatives);
};

struct haxorg_AstTrackingGroupRadioTarget_vtable {
  haxorg_AstTrackingPath const* (*get_target)(OrgContext*, haxorg_AstTrackingGroupRadioTarget const*);
  haxorg_HstdVec const* (*get_nodes)(OrgContext*, haxorg_AstTrackingGroupRadioTarget const*);
};

struct haxorg_AstTrackingGroupSingle_vtable {
  haxorg_SemId const* (*get_node)(OrgContext*, haxorg_AstTrackingGroupSingle const*);
};

struct haxorg_AstTrackingGroupTrackedHashtag_vtable {
  haxorg_SemId const* (*get_tag)(OrgContext*, haxorg_AstTrackingGroupTrackedHashtag const*);
  haxorg_HstdUnorderedMap const* (*get_targets)(OrgContext*, haxorg_AstTrackingGroupTrackedHashtag const*);
};

struct haxorg_AstTrackingGroup_vtable {
  haxorg_AstTrackingGroupRadioTarget (*getRadioTargetConst_const)(OrgContext*, haxorg_AstTrackingGroup);
  haxorg_AstTrackingGroupTrackedHashtag (*getTrackedHashtagConst_const)(OrgContext*, haxorg_AstTrackingGroup);
  haxorg_AstTrackingGroupTrackedHashtag (*getTrackedHashtagMut)(OrgContext*, haxorg_AstTrackingGroup);
  haxorg_AstTrackingGroupSingle (*getSingleConst_const)(OrgContext*, haxorg_AstTrackingGroup);
  haxorg_AstTrackingGroupRadioTarget (*getRadioTargetMut)(OrgContext*, haxorg_AstTrackingGroup);
  haxorg_AstTrackingGroupSingle (*getSingleMut)(OrgContext*, haxorg_AstTrackingGroup);
  bool (*isSingle_const)(OrgContext*, haxorg_AstTrackingGroup);
  bool (*isTrackedHashtag_const)(OrgContext*, haxorg_AstTrackingGroup);
  bool (*isRadioTarget_const)(OrgContext*, haxorg_AstTrackingGroup);
};

struct haxorg_AstTrackingMap_vtable {
  haxorg_HstdUnorderedMap const* (*get_footnotes)(OrgContext*, haxorg_AstTrackingMap const*);
  haxorg_HstdUnorderedMap const* (*get_subtrees)(OrgContext*, haxorg_AstTrackingMap const*);
  haxorg_HstdUnorderedMap const* (*get_names)(OrgContext*, haxorg_AstTrackingMap const*);
  haxorg_HstdUnorderedMap const* (*get_anchorTargets)(OrgContext*, haxorg_AstTrackingMap const*);
  haxorg_HstdUnorderedMap const* (*get_radioTargets)(OrgContext*, haxorg_AstTrackingMap const*);
  haxorg_HstdUnorderedMap const* (*get_hashtagDefinitions)(OrgContext*, haxorg_AstTrackingMap const*);
  haxorg_StdOptional (*getIdPath_const)(OrgContext*, haxorg_AstTrackingMap, haxorg_HstdStr);
  haxorg_StdOptional (*getNamePath_const)(OrgContext*, haxorg_AstTrackingMap, haxorg_HstdStr);
  haxorg_StdOptional (*getAnchorTarget_const)(OrgContext*, haxorg_AstTrackingMap, haxorg_HstdStr);
  haxorg_StdOptional (*getFootnotePath_const)(OrgContext*, haxorg_AstTrackingMap, haxorg_HstdStr);
};

struct haxorg_SequenceSegment_vtable {
  int const* (*get_kind)(OrgContext*, haxorg_SequenceSegment const*);
  int const* (*get_first)(OrgContext*, haxorg_SequenceSegment const*);
  int const* (*get_last)(OrgContext*, haxorg_SequenceSegment const*);
};

struct haxorg_SequenceSegmentGroup_vtable {
  int const* (*get_kind)(OrgContext*, haxorg_SequenceSegmentGroup const*);
  haxorg_HstdVec const* (*get_segments)(OrgContext*, haxorg_SequenceSegmentGroup const*);
};

struct haxorg_SequenceAnnotationTag_vtable {
  int const* (*get_groupKind)(OrgContext*, haxorg_SequenceAnnotationTag const*);
  haxorg_HstdVec const* (*get_segmentKinds)(OrgContext*, haxorg_SequenceAnnotationTag const*);
};

struct haxorg_SequenceAnnotation_vtable {
  int const* (*get_first)(OrgContext*, haxorg_SequenceAnnotation const*);
  int const* (*get_last)(OrgContext*, haxorg_SequenceAnnotation const*);
  haxorg_HstdVec const* (*get_annotations)(OrgContext*, haxorg_SequenceAnnotation const*);
  bool (*isAnnotatedWith_const)(OrgContext*, haxorg_SequenceAnnotation, int, int);
};

struct haxorg_GraphMapLinkLink_vtable {
  haxorg_ImmUniqId const* (*get_link)(OrgContext*, haxorg_GraphMapLinkLink const*);
  haxorg_HstdVec const* (*get_description)(OrgContext*, haxorg_GraphMapLinkLink const*);
};

struct haxorg_GraphMapLinkRadio_vtable {
  haxorg_ImmUniqId const* (*get_target)(OrgContext*, haxorg_GraphMapLinkRadio const*);
};

struct haxorg_GraphMapLink_vtable {
  haxorg_GraphMapLinkRadio (*getRadio)(OrgContext*, haxorg_GraphMapLink);
  haxorg_GraphMapLinkRadio (*getRadio_const)(OrgContext*, haxorg_GraphMapLink);
  bool (*isRadio_const)(OrgContext*, haxorg_GraphMapLink);
  haxorg_GraphMapLinkLink (*getLink)(OrgContext*, haxorg_GraphMapLink);
  haxorg_GraphMapLinkLink (*getLink_const)(OrgContext*, haxorg_GraphMapLink);
  bool (*isLink_const)(OrgContext*, haxorg_GraphMapLink);
  haxorg_GraphMapLinkKind (*getKind_const)(OrgContext*, haxorg_GraphMapLink);
};

struct haxorg_GraphMapNodeProp_vtable {
  haxorg_ImmUniqId const* (*get_id)(OrgContext*, haxorg_GraphMapNodeProp const*);
  haxorg_HstdVec const* (*get_unresolved)(OrgContext*, haxorg_GraphMapNodeProp const*);
  haxorg_ImmAdapter (*getAdapter_const)(OrgContext*, haxorg_GraphMapNodeProp, haxorg_ImmAstContext);
  haxorg_StdOptional (*getSubtreeId_const)(OrgContext*, haxorg_GraphMapNodeProp, haxorg_ImmAstContext);
  haxorg_StdOptional (*getFootnoteName_const)(OrgContext*, haxorg_GraphMapNodeProp, haxorg_ImmAstContext);
};

struct haxorg_GraphMapEdgeProp_vtable {
  haxorg_GraphMapLink const* (*get_link)(OrgContext*, haxorg_GraphMapEdgeProp const*);
};

struct haxorg_GraphMapNode_vtable {
  haxorg_ImmUniqId const* (*get_id)(OrgContext*, haxorg_GraphMapNode const*);
  bool (*__eq___const)(OrgContext*, haxorg_GraphMapNode, haxorg_GraphMapNode);
  bool (*__lt___const)(OrgContext*, haxorg_GraphMapNode, haxorg_GraphMapNode);
};

struct haxorg_GraphMapEdge_vtable {
  haxorg_GraphMapNode const* (*get_source)(OrgContext*, haxorg_GraphMapEdge const*);
  haxorg_GraphMapNode const* (*get_target)(OrgContext*, haxorg_GraphMapEdge const*);
};

struct haxorg_GraphMapGraph_vtable {
  haxorg_GraphNodeProps const* (*get_nodeProps)(OrgContext*, haxorg_GraphMapGraph const*);
  haxorg_GraphEdgeProps const* (*get_edgeProps)(OrgContext*, haxorg_GraphMapGraph const*);
  haxorg_GraphAdjList const* (*get_adjList)(OrgContext*, haxorg_GraphMapGraph const*);
  haxorg_GraphAdjList const* (*get_adjListIn)(OrgContext*, haxorg_GraphMapGraph const*);
  int (*nodeCount_const)(OrgContext*, haxorg_GraphMapGraph);
  int (*edgeCount_const)(OrgContext*, haxorg_GraphMapGraph);
  haxorg_GraphAdjNodesList (*outNodes_const)(OrgContext*, haxorg_GraphMapGraph, haxorg_GraphMapNode);
  haxorg_GraphAdjNodesList (*inNodes_const)(OrgContext*, haxorg_GraphMapGraph, haxorg_GraphMapNode);
  haxorg_HstdVec (*adjEdges_const)(OrgContext*, haxorg_GraphMapGraph, haxorg_GraphMapNode);
  haxorg_HstdVec (*adjNodes_const)(OrgContext*, haxorg_GraphMapGraph, haxorg_GraphMapNode);
  haxorg_HstdVec (*outEdges_const)(OrgContext*, haxorg_GraphMapGraph, haxorg_GraphMapNode);
  haxorg_HstdVec (*inEdges_const)(OrgContext*, haxorg_GraphMapGraph, haxorg_GraphMapNode);
  int (*outDegree_const)(OrgContext*, haxorg_GraphMapGraph, haxorg_GraphMapNode);
  int (*inDegree_const)(OrgContext*, haxorg_GraphMapGraph, haxorg_GraphMapNode);
  bool (*isRegisteredNode_const)(OrgContext*, haxorg_GraphMapGraph, haxorg_GraphMapNode);
  bool (*isRegisteredNodeById_const)(OrgContext*, haxorg_GraphMapGraph, haxorg_ImmUniqId);
  haxorg_GraphMapNodeProp (*atMapNode_const)(OrgContext*, haxorg_GraphMapGraph, haxorg_GraphMapNode);
  haxorg_GraphMapEdgeProp (*atMapEdge_const)(OrgContext*, haxorg_GraphMapGraph, haxorg_GraphMapEdge);
  void (*addEdge)(OrgContext*, haxorg_GraphMapGraph, haxorg_GraphMapEdge);
  void (*addEdgeWithProp)(OrgContext*, haxorg_GraphMapGraph, haxorg_GraphMapEdge, haxorg_GraphMapEdgeProp);
  void (*addNode)(OrgContext*, haxorg_GraphMapGraph, haxorg_GraphMapNode);
  void (*addNodeWithProp)(OrgContext*, haxorg_GraphMapGraph, haxorg_GraphMapNode, haxorg_GraphMapNodeProp);
  bool (*hasEdge_const)(OrgContext*, haxorg_GraphMapGraph, haxorg_GraphMapNode, haxorg_GraphMapNode);
  bool (*hasNode_const)(OrgContext*, haxorg_GraphMapGraph, haxorg_GraphMapNode);
  bool (*has2AdapterEdge_const)(OrgContext*, haxorg_GraphMapGraph, haxorg_ImmAdapter, haxorg_ImmAdapter);
};

struct haxorg_GraphMapConfig_vtable {
  haxorg_OperationsTracer const* (*get_dbg)(OrgContext*, haxorg_GraphMapConfig const*);
};

struct haxorg_GraphMapGraphState_vtable {
  haxorg_GraphMapGraph const* (*get_graph)(OrgContext*, haxorg_GraphMapGraphState const*);
  haxorg_ImmAstContext const* (*get_ast)(OrgContext*, haxorg_GraphMapGraphState const*);
  haxorg_GraphMapGraph (*getGraph_const)(OrgContext*, haxorg_GraphMapGraphState);
  haxorg_GraphMapGraphState (*FromAstContext)(OrgContext*, haxorg_GraphMapGraphState, haxorg_ImmAstContext);
  void (*registerNode)(OrgContext*, haxorg_GraphMapGraphState, haxorg_GraphMapNodeProp, haxorg_GraphMapConfig);
  void (*addNode)(OrgContext*, haxorg_GraphMapGraphState, haxorg_ImmAdapter, haxorg_GraphMapConfig);
  void (*addNodeRec)(OrgContext*, haxorg_GraphMapGraphState, haxorg_ImmAstContext, haxorg_ImmAdapter, haxorg_GraphMapConfig);
  haxorg_HstdVec (*getUnresolvedSubtreeLinks_const)(OrgContext*, haxorg_GraphMapGraphState, haxorg_ImmSubtreeAdapter, haxorg_GraphMapConfig);
  haxorg_StdOptional (*getUnresolvedLink_const)(OrgContext*, haxorg_GraphMapGraphState, haxorg_ImmLinkAdapter, haxorg_GraphMapConfig);
};

struct haxorg_ImmSubtreeAdapter_vtable {
  int (*getLevel_const)(OrgContext*, haxorg_ImmSubtreeAdapter);
  haxorg_HstdOpt (*getTreeId_const)(OrgContext*, haxorg_ImmSubtreeAdapter);
  haxorg_HstdOpt (*getTodo_const)(OrgContext*, haxorg_ImmSubtreeAdapter);
  haxorg_HstdOpt (*getCompletion_const)(OrgContext*, haxorg_ImmSubtreeAdapter);
  haxorg_HstdOpt (*getDescription_const)(OrgContext*, haxorg_ImmSubtreeAdapter);
  haxorg_ImmVec (*getTags_const)(OrgContext*, haxorg_ImmSubtreeAdapter);
  haxorg_ImmAdapter (*getTitle_const)(OrgContext*, haxorg_ImmSubtreeAdapter);
  haxorg_ImmVec (*getLogbook_const)(OrgContext*, haxorg_ImmSubtreeAdapter);
  haxorg_ImmVec (*getProperties_const)(OrgContext*, haxorg_ImmSubtreeAdapter);
  haxorg_HstdOpt (*getClosed_const)(OrgContext*, haxorg_ImmSubtreeAdapter);
  haxorg_HstdOpt (*getDeadline_const)(OrgContext*, haxorg_ImmSubtreeAdapter);
  haxorg_HstdOpt (*getScheduled_const)(OrgContext*, haxorg_ImmSubtreeAdapter);
  bool (*getIsComment_const)(OrgContext*, haxorg_ImmSubtreeAdapter);
  bool (*getIsArchived_const)(OrgContext*, haxorg_ImmSubtreeAdapter);
  haxorg_HstdOpt (*getPriority_const)(OrgContext*, haxorg_ImmSubtreeAdapter);
};

struct haxorg_LispCodeCall_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_LispCodeCall const*);
  haxorg_HstdVec const* (*get_args)(OrgContext*, haxorg_LispCodeCall const*);
  bool (*__eq___const)(OrgContext*, haxorg_LispCodeCall, haxorg_LispCodeCall);
};

struct haxorg_LispCodeList_vtable {
  haxorg_HstdVec const* (*get_items)(OrgContext*, haxorg_LispCodeList const*);
  bool (*__eq___const)(OrgContext*, haxorg_LispCodeList, haxorg_LispCodeList);
};

struct haxorg_LispCodeKeyValue_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_LispCodeKeyValue const*);
  haxorg_HstdVec const* (*get_value)(OrgContext*, haxorg_LispCodeKeyValue const*);
  bool (*__eq___const)(OrgContext*, haxorg_LispCodeKeyValue, haxorg_LispCodeKeyValue);
};

struct haxorg_LispCodeNumber_vtable {
  int const* (*get_value)(OrgContext*, haxorg_LispCodeNumber const*);
  bool (*__eq___const)(OrgContext*, haxorg_LispCodeNumber, haxorg_LispCodeNumber);
};

struct haxorg_LispCodeText_vtable {
  haxorg_HstdStr const* (*get_value)(OrgContext*, haxorg_LispCodeText const*);
  bool (*__eq___const)(OrgContext*, haxorg_LispCodeText, haxorg_LispCodeText);
};

struct haxorg_LispCodeIdent_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_LispCodeIdent const*);
  bool (*__eq___const)(OrgContext*, haxorg_LispCodeIdent, haxorg_LispCodeIdent);
};

struct haxorg_LispCodeBoolean_vtable {
  bool const* (*get_value)(OrgContext*, haxorg_LispCodeBoolean const*);
  bool (*__eq___const)(OrgContext*, haxorg_LispCodeBoolean, haxorg_LispCodeBoolean);
};

struct haxorg_LispCodeReal_vtable {
  float const* (*get_value)(OrgContext*, haxorg_LispCodeReal const*);
  bool (*__eq___const)(OrgContext*, haxorg_LispCodeReal, haxorg_LispCodeReal);
};

struct haxorg_LispCode_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_LispCode, haxorg_LispCode);
  bool (*isCall_const)(OrgContext*, haxorg_LispCode);
  haxorg_LispCodeCall (*getCallConst_const)(OrgContext*, haxorg_LispCode);
  haxorg_LispCodeCall (*getCallMut)(OrgContext*, haxorg_LispCode);
  bool (*isList_const)(OrgContext*, haxorg_LispCode);
  haxorg_LispCodeList (*getListConst_const)(OrgContext*, haxorg_LispCode);
  haxorg_LispCodeList (*getListMut)(OrgContext*, haxorg_LispCode);
  bool (*isKeyValue_const)(OrgContext*, haxorg_LispCode);
  haxorg_LispCodeKeyValue (*getKeyValueConst_const)(OrgContext*, haxorg_LispCode);
  haxorg_LispCodeKeyValue (*getKeyValueMut)(OrgContext*, haxorg_LispCode);
  bool (*isNumber_const)(OrgContext*, haxorg_LispCode);
  haxorg_LispCodeNumber (*getNumberConst_const)(OrgContext*, haxorg_LispCode);
  haxorg_LispCodeNumber (*getNumberMut)(OrgContext*, haxorg_LispCode);
  bool (*isText_const)(OrgContext*, haxorg_LispCode);
  haxorg_LispCodeText (*getTextConst_const)(OrgContext*, haxorg_LispCode);
  haxorg_LispCodeText (*getTextMut)(OrgContext*, haxorg_LispCode);
  bool (*isIdent_const)(OrgContext*, haxorg_LispCode);
  haxorg_LispCodeIdent (*getIdentConst_const)(OrgContext*, haxorg_LispCode);
  haxorg_LispCodeIdent (*getIdentMut)(OrgContext*, haxorg_LispCode);
  bool (*isBoolean_const)(OrgContext*, haxorg_LispCode);
  haxorg_LispCodeBoolean (*getBooleanConst_const)(OrgContext*, haxorg_LispCode);
  haxorg_LispCodeBoolean (*getBooleanMut)(OrgContext*, haxorg_LispCode);
  bool (*isReal_const)(OrgContext*, haxorg_LispCode);
  haxorg_LispCodeReal (*getRealConst_const)(OrgContext*, haxorg_LispCode);
  haxorg_LispCodeReal (*getRealMut)(OrgContext*, haxorg_LispCode);
  haxorg_LispCodeKind (*getKind_const)(OrgContext*, haxorg_LispCode);
};

struct haxorg_TblfmExprAxisRefPositionIndex_vtable {
  int const* (*get_index)(OrgContext*, haxorg_TblfmExprAxisRefPositionIndex const*);
  bool (*__eq___const)(OrgContext*, haxorg_TblfmExprAxisRefPositionIndex, haxorg_TblfmExprAxisRefPositionIndex);
};

struct haxorg_TblfmExprAxisRefPositionName_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_TblfmExprAxisRefPositionName const*);
  bool (*__eq___const)(OrgContext*, haxorg_TblfmExprAxisRefPositionName, haxorg_TblfmExprAxisRefPositionName);
};

struct haxorg_TblfmExprAxisRefPosition_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition);
  bool (*isIndex_const)(OrgContext*, haxorg_TblfmExprAxisRefPosition);
  haxorg_TblfmExprAxisRefPositionIndex (*getIndexConst_const)(OrgContext*, haxorg_TblfmExprAxisRefPosition);
  haxorg_TblfmExprAxisRefPositionIndex (*getIndexMut)(OrgContext*, haxorg_TblfmExprAxisRefPosition);
  bool (*isName_const)(OrgContext*, haxorg_TblfmExprAxisRefPosition);
  haxorg_TblfmExprAxisRefPositionName (*getNameConst_const)(OrgContext*, haxorg_TblfmExprAxisRefPosition);
  haxorg_TblfmExprAxisRefPositionName (*getNameMut)(OrgContext*, haxorg_TblfmExprAxisRefPosition);
  haxorg_TblfmExprAxisRefPositionKind (*getKind_const)(OrgContext*, haxorg_TblfmExprAxisRefPosition);
};

struct haxorg_TblfmExprAxisRef_vtable {
  haxorg_TblfmExprAxisRefPosition const* (*get_col)(OrgContext*, haxorg_TblfmExprAxisRef const*);
  haxorg_HstdOpt const* (*get_row)(OrgContext*, haxorg_TblfmExprAxisRef const*);
  bool (*__eq___const)(OrgContext*, haxorg_TblfmExprAxisRef, haxorg_TblfmExprAxisRef);
};

struct haxorg_TblfmExprAxisName_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_TblfmExprAxisName const*);
  bool (*__eq___const)(OrgContext*, haxorg_TblfmExprAxisName, haxorg_TblfmExprAxisName);
};

struct haxorg_TblfmExprIntLiteral_vtable {
  int const* (*get_value)(OrgContext*, haxorg_TblfmExprIntLiteral const*);
  bool (*__eq___const)(OrgContext*, haxorg_TblfmExprIntLiteral, haxorg_TblfmExprIntLiteral);
};

struct haxorg_TblfmExprFloatLiteral_vtable {
  float const* (*get_value)(OrgContext*, haxorg_TblfmExprFloatLiteral const*);
  bool (*__eq___const)(OrgContext*, haxorg_TblfmExprFloatLiteral, haxorg_TblfmExprFloatLiteral);
};

struct haxorg_TblfmExprRangeRef_vtable {
  haxorg_HstdOpt const* (*get_first)(OrgContext*, haxorg_TblfmExprRangeRef const*);
  haxorg_HstdOpt const* (*get_last)(OrgContext*, haxorg_TblfmExprRangeRef const*);
  bool (*__eq___const)(OrgContext*, haxorg_TblfmExprRangeRef, haxorg_TblfmExprRangeRef);
};

struct haxorg_TblfmExprCall_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_TblfmExprCall const*);
  haxorg_HstdVec const* (*get_args)(OrgContext*, haxorg_TblfmExprCall const*);
  bool (*__eq___const)(OrgContext*, haxorg_TblfmExprCall, haxorg_TblfmExprCall);
};

struct haxorg_TblfmExprElisp_vtable {
  haxorg_HstdStr const* (*get_value)(OrgContext*, haxorg_TblfmExprElisp const*);
  bool (*__eq___const)(OrgContext*, haxorg_TblfmExprElisp, haxorg_TblfmExprElisp);
};

struct haxorg_TblfmExpr_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_TblfmExpr, haxorg_TblfmExpr);
  bool (*isAxisRef_const)(OrgContext*, haxorg_TblfmExpr);
  haxorg_TblfmExprAxisRef (*getAxisRefConst_const)(OrgContext*, haxorg_TblfmExpr);
  haxorg_TblfmExprAxisRef (*getAxisRefMut)(OrgContext*, haxorg_TblfmExpr);
  bool (*isAxisName_const)(OrgContext*, haxorg_TblfmExpr);
  haxorg_TblfmExprAxisName (*getAxisNameConst_const)(OrgContext*, haxorg_TblfmExpr);
  haxorg_TblfmExprAxisName (*getAxisNameMut)(OrgContext*, haxorg_TblfmExpr);
  bool (*isIntLiteral_const)(OrgContext*, haxorg_TblfmExpr);
  haxorg_TblfmExprIntLiteral (*getIntLiteralConst_const)(OrgContext*, haxorg_TblfmExpr);
  haxorg_TblfmExprIntLiteral (*getIntLiteralMut)(OrgContext*, haxorg_TblfmExpr);
  bool (*isFloatLiteral_const)(OrgContext*, haxorg_TblfmExpr);
  haxorg_TblfmExprFloatLiteral (*getFloatLiteralConst_const)(OrgContext*, haxorg_TblfmExpr);
  haxorg_TblfmExprFloatLiteral (*getFloatLiteralMut)(OrgContext*, haxorg_TblfmExpr);
  bool (*isRangeRef_const)(OrgContext*, haxorg_TblfmExpr);
  haxorg_TblfmExprRangeRef (*getRangeRefConst_const)(OrgContext*, haxorg_TblfmExpr);
  haxorg_TblfmExprRangeRef (*getRangeRefMut)(OrgContext*, haxorg_TblfmExpr);
  bool (*isCall_const)(OrgContext*, haxorg_TblfmExpr);
  haxorg_TblfmExprCall (*getCallConst_const)(OrgContext*, haxorg_TblfmExpr);
  haxorg_TblfmExprCall (*getCallMut)(OrgContext*, haxorg_TblfmExpr);
  bool (*isElisp_const)(OrgContext*, haxorg_TblfmExpr);
  haxorg_TblfmExprElisp (*getElispConst_const)(OrgContext*, haxorg_TblfmExpr);
  haxorg_TblfmExprElisp (*getElispMut)(OrgContext*, haxorg_TblfmExpr);
  haxorg_TblfmExprKind (*getKind_const)(OrgContext*, haxorg_TblfmExpr);
};

struct haxorg_TblfmAssign_vtable {
  haxorg_TblfmExprAxisRef const* (*get_target)(OrgContext*, haxorg_TblfmAssign const*);
  haxorg_HstdVec const* (*get_expr)(OrgContext*, haxorg_TblfmAssign const*);
  haxorg_HstdVec const* (*get_flags)(OrgContext*, haxorg_TblfmAssign const*);
  bool (*__eq___const)(OrgContext*, haxorg_TblfmAssign, haxorg_TblfmAssign);
};

struct haxorg_Tblfm_vtable {
  haxorg_HstdVec const* (*get_exprs)(OrgContext*, haxorg_Tblfm const*);
  bool (*__eq___const)(OrgContext*, haxorg_Tblfm, haxorg_Tblfm);
};

struct haxorg_AttrValueDimensionSpan_vtable {
  int const* (*get_first)(OrgContext*, haxorg_AttrValueDimensionSpan const*);
  haxorg_HstdOpt const* (*get_last)(OrgContext*, haxorg_AttrValueDimensionSpan const*);
  bool (*__eq___const)(OrgContext*, haxorg_AttrValueDimensionSpan, haxorg_AttrValueDimensionSpan);
};

struct haxorg_AttrValueTextValue_vtable {
  haxorg_HstdStr const* (*get_value)(OrgContext*, haxorg_AttrValueTextValue const*);
  bool (*__eq___const)(OrgContext*, haxorg_AttrValueTextValue, haxorg_AttrValueTextValue);
};

struct haxorg_AttrValueFileReference_vtable {
  haxorg_HstdStr const* (*get_file)(OrgContext*, haxorg_AttrValueFileReference const*);
  haxorg_HstdStr const* (*get_reference)(OrgContext*, haxorg_AttrValueFileReference const*);
  bool (*__eq___const)(OrgContext*, haxorg_AttrValueFileReference, haxorg_AttrValueFileReference);
};

struct haxorg_AttrValueLispValue_vtable {
  haxorg_LispCode const* (*get_code)(OrgContext*, haxorg_AttrValueLispValue const*);
  bool (*__eq___const)(OrgContext*, haxorg_AttrValueLispValue, haxorg_AttrValueLispValue);
};

struct haxorg_AttrValue_vtable {
  haxorg_HstdOpt const* (*get_name)(OrgContext*, haxorg_AttrValue const*);
  haxorg_HstdOpt const* (*get_varname)(OrgContext*, haxorg_AttrValue const*);
  haxorg_HstdVec const* (*get_span)(OrgContext*, haxorg_AttrValue const*);
  bool const* (*get_isQuoted)(OrgContext*, haxorg_AttrValue const*);
  haxorg_HstdOpt (*getBool_const)(OrgContext*, haxorg_AttrValue);
  haxorg_HstdOpt (*getInt_const)(OrgContext*, haxorg_AttrValue);
  haxorg_HstdStr (*getString_const)(OrgContext*, haxorg_AttrValue);
  haxorg_HstdOpt (*getDouble_const)(OrgContext*, haxorg_AttrValue);
  bool (*__eq___const)(OrgContext*, haxorg_AttrValue, haxorg_AttrValue);
  bool (*isTextValue_const)(OrgContext*, haxorg_AttrValue);
  haxorg_AttrValueTextValue (*getTextValueConst_const)(OrgContext*, haxorg_AttrValue);
  haxorg_AttrValueTextValue (*getTextValueMut)(OrgContext*, haxorg_AttrValue);
  bool (*isFileReference_const)(OrgContext*, haxorg_AttrValue);
  haxorg_AttrValueFileReference (*getFileReferenceConst_const)(OrgContext*, haxorg_AttrValue);
  haxorg_AttrValueFileReference (*getFileReferenceMut)(OrgContext*, haxorg_AttrValue);
  bool (*isLispValue_const)(OrgContext*, haxorg_AttrValue);
  haxorg_AttrValueLispValue (*getLispValueConst_const)(OrgContext*, haxorg_AttrValue);
  haxorg_AttrValueLispValue (*getLispValueMut)(OrgContext*, haxorg_AttrValue);
  haxorg_AttrValueKind (*getKind_const)(OrgContext*, haxorg_AttrValue);
};

struct haxorg_HashTagFlat_vtable {
  haxorg_HstdVec const* (*get_tags)(OrgContext*, haxorg_HashTagFlat const*);
  bool (*__eq___const)(OrgContext*, haxorg_HashTagFlat, haxorg_HashTagFlat);
  bool (*__lt___const)(OrgContext*, haxorg_HashTagFlat, haxorg_HashTagFlat);
};

struct haxorg_TodoKeyword_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_TodoKeyword const*);
  haxorg_HstdOpt const* (*get_shortcut)(OrgContext*, haxorg_TodoKeyword const*);
  haxorg_TodoKeywordTransition const* (*get_onEnter)(OrgContext*, haxorg_TodoKeyword const*);
  haxorg_TodoKeywordTransition const* (*get_onLeave)(OrgContext*, haxorg_TodoKeyword const*);
  bool (*__eq___const)(OrgContext*, haxorg_TodoKeyword, haxorg_TodoKeyword);
};

struct haxorg_HashTagText_vtable {
  haxorg_HstdStr const* (*get_head)(OrgContext*, haxorg_HashTagText const*);
  haxorg_HstdVec const* (*get_subtags)(OrgContext*, haxorg_HashTagText const*);
  bool (*__eq___const)(OrgContext*, haxorg_HashTagText, haxorg_HashTagText);
  bool (*prefixMatch_const)(OrgContext*, haxorg_HashTagText, haxorg_HstdVec);
  haxorg_HstdVec (*getFlatHashes_const)(OrgContext*, haxorg_HashTagText, bool);
};

struct haxorg_SubtreePath_vtable {
  haxorg_HstdVec const* (*get_path)(OrgContext*, haxorg_SubtreePath const*);
  bool (*__eq___const)(OrgContext*, haxorg_SubtreePath, haxorg_SubtreePath);
};

struct haxorg_LinkTargetRaw_vtable {
  haxorg_HstdStr const* (*get_text)(OrgContext*, haxorg_LinkTargetRaw const*);
  bool (*__eq___const)(OrgContext*, haxorg_LinkTargetRaw, haxorg_LinkTargetRaw);
};

struct haxorg_LinkTargetId_vtable {
  haxorg_HstdStr const* (*get_text)(OrgContext*, haxorg_LinkTargetId const*);
  bool (*__eq___const)(OrgContext*, haxorg_LinkTargetId, haxorg_LinkTargetId);
};

struct haxorg_LinkTargetCustomId_vtable {
  haxorg_HstdStr const* (*get_text)(OrgContext*, haxorg_LinkTargetCustomId const*);
  bool (*__eq___const)(OrgContext*, haxorg_LinkTargetCustomId, haxorg_LinkTargetCustomId);
};

struct haxorg_LinkTargetSubtreeTitle_vtable {
  haxorg_SubtreePath const* (*get_title)(OrgContext*, haxorg_LinkTargetSubtreeTitle const*);
  int const* (*get_level)(OrgContext*, haxorg_LinkTargetSubtreeTitle const*);
  bool (*__eq___const)(OrgContext*, haxorg_LinkTargetSubtreeTitle, haxorg_LinkTargetSubtreeTitle);
};

struct haxorg_LinkTargetPerson_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_LinkTargetPerson const*);
  bool (*__eq___const)(OrgContext*, haxorg_LinkTargetPerson, haxorg_LinkTargetPerson);
};

struct haxorg_LinkTargetUserProtocol_vtable {
  haxorg_HstdStr const* (*get_protocol)(OrgContext*, haxorg_LinkTargetUserProtocol const*);
  haxorg_HstdStr const* (*get_target)(OrgContext*, haxorg_LinkTargetUserProtocol const*);
  bool (*__eq___const)(OrgContext*, haxorg_LinkTargetUserProtocol, haxorg_LinkTargetUserProtocol);
};

struct haxorg_LinkTargetInternal_vtable {
  haxorg_HstdStr const* (*get_target)(OrgContext*, haxorg_LinkTargetInternal const*);
  bool (*__eq___const)(OrgContext*, haxorg_LinkTargetInternal, haxorg_LinkTargetInternal);
};

struct haxorg_LinkTargetFootnote_vtable {
  haxorg_HstdStr const* (*get_target)(OrgContext*, haxorg_LinkTargetFootnote const*);
  bool (*__eq___const)(OrgContext*, haxorg_LinkTargetFootnote, haxorg_LinkTargetFootnote);
};

struct haxorg_LinkTargetFile_vtable {
  haxorg_HstdStr const* (*get_file)(OrgContext*, haxorg_LinkTargetFile const*);
  bool (*__eq___const)(OrgContext*, haxorg_LinkTargetFile, haxorg_LinkTargetFile);
};

struct haxorg_LinkTargetAttachment_vtable {
  haxorg_HstdStr const* (*get_file)(OrgContext*, haxorg_LinkTargetAttachment const*);
  bool (*__eq___const)(OrgContext*, haxorg_LinkTargetAttachment, haxorg_LinkTargetAttachment);
};

struct haxorg_LinkTarget_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_LinkTarget, haxorg_LinkTarget);
  bool (*isRaw_const)(OrgContext*, haxorg_LinkTarget);
  haxorg_LinkTargetRaw (*getRawConst_const)(OrgContext*, haxorg_LinkTarget);
  haxorg_LinkTargetRaw (*getRawMut)(OrgContext*, haxorg_LinkTarget);
  bool (*isId_const)(OrgContext*, haxorg_LinkTarget);
  haxorg_LinkTargetId (*getIdConst_const)(OrgContext*, haxorg_LinkTarget);
  haxorg_LinkTargetId (*getIdMut)(OrgContext*, haxorg_LinkTarget);
  bool (*isCustomId_const)(OrgContext*, haxorg_LinkTarget);
  haxorg_LinkTargetCustomId (*getCustomIdConst_const)(OrgContext*, haxorg_LinkTarget);
  haxorg_LinkTargetCustomId (*getCustomIdMut)(OrgContext*, haxorg_LinkTarget);
  bool (*isSubtreeTitle_const)(OrgContext*, haxorg_LinkTarget);
  haxorg_LinkTargetSubtreeTitle (*getSubtreeTitleConst_const)(OrgContext*, haxorg_LinkTarget);
  haxorg_LinkTargetSubtreeTitle (*getSubtreeTitleMut)(OrgContext*, haxorg_LinkTarget);
  bool (*isPerson_const)(OrgContext*, haxorg_LinkTarget);
  haxorg_LinkTargetPerson (*getPersonConst_const)(OrgContext*, haxorg_LinkTarget);
  haxorg_LinkTargetPerson (*getPersonMut)(OrgContext*, haxorg_LinkTarget);
  bool (*isUserProtocol_const)(OrgContext*, haxorg_LinkTarget);
  haxorg_LinkTargetUserProtocol (*getUserProtocolConst_const)(OrgContext*, haxorg_LinkTarget);
  haxorg_LinkTargetUserProtocol (*getUserProtocolMut)(OrgContext*, haxorg_LinkTarget);
  bool (*isInternal_const)(OrgContext*, haxorg_LinkTarget);
  haxorg_LinkTargetInternal (*getInternalConst_const)(OrgContext*, haxorg_LinkTarget);
  haxorg_LinkTargetInternal (*getInternalMut)(OrgContext*, haxorg_LinkTarget);
  bool (*isFootnote_const)(OrgContext*, haxorg_LinkTarget);
  haxorg_LinkTargetFootnote (*getFootnoteConst_const)(OrgContext*, haxorg_LinkTarget);
  haxorg_LinkTargetFootnote (*getFootnoteMut)(OrgContext*, haxorg_LinkTarget);
  bool (*isFile_const)(OrgContext*, haxorg_LinkTarget);
  haxorg_LinkTargetFile (*getFileConst_const)(OrgContext*, haxorg_LinkTarget);
  haxorg_LinkTargetFile (*getFileMut)(OrgContext*, haxorg_LinkTarget);
  bool (*isAttachment_const)(OrgContext*, haxorg_LinkTarget);
  haxorg_LinkTargetAttachment (*getAttachmentConst_const)(OrgContext*, haxorg_LinkTarget);
  haxorg_LinkTargetAttachment (*getAttachmentMut)(OrgContext*, haxorg_LinkTarget);
  haxorg_LinkTargetKind (*getKind_const)(OrgContext*, haxorg_LinkTarget);
};

struct haxorg_ImmLinkAdapter_vtable {
  haxorg_HstdOpt (*getDescription_const)(OrgContext*, haxorg_ImmLinkAdapter);
  haxorg_LinkTarget (*getTarget_const)(OrgContext*, haxorg_ImmLinkAdapter);
};

struct haxorg_SubtreeLogHeadPriority_vtable {
  haxorg_HstdOpt const* (*get_oldPriority)(OrgContext*, haxorg_SubtreeLogHeadPriority const*);
  haxorg_HstdOpt const* (*get_newPriority)(OrgContext*, haxorg_SubtreeLogHeadPriority const*);
  haxorg_UserTime const* (*get_on)(OrgContext*, haxorg_SubtreeLogHeadPriority const*);
  haxorg_SubtreeLogHeadPriorityAction const* (*get_action)(OrgContext*, haxorg_SubtreeLogHeadPriority const*);
  bool (*__eq___const)(OrgContext*, haxorg_SubtreeLogHeadPriority, haxorg_SubtreeLogHeadPriority);
};

struct haxorg_SubtreeLogHeadNote_vtable {
  haxorg_UserTime const* (*get_on)(OrgContext*, haxorg_SubtreeLogHeadNote const*);
  bool (*__eq___const)(OrgContext*, haxorg_SubtreeLogHeadNote, haxorg_SubtreeLogHeadNote);
};

struct haxorg_SubtreeLogHeadRefile_vtable {
  haxorg_UserTime const* (*get_on)(OrgContext*, haxorg_SubtreeLogHeadRefile const*);
  haxorg_LinkTarget const* (*get_from)(OrgContext*, haxorg_SubtreeLogHeadRefile const*);
  bool (*__eq___const)(OrgContext*, haxorg_SubtreeLogHeadRefile, haxorg_SubtreeLogHeadRefile);
};

struct haxorg_SubtreeLogHeadClock_vtable {
  haxorg_UserTime const* (*get_from)(OrgContext*, haxorg_SubtreeLogHeadClock const*);
  haxorg_HstdOpt const* (*get_to)(OrgContext*, haxorg_SubtreeLogHeadClock const*);
  bool (*__eq___const)(OrgContext*, haxorg_SubtreeLogHeadClock, haxorg_SubtreeLogHeadClock);
};

struct haxorg_SubtreeLogHeadState_vtable {
  haxorg_HstdStr const* (*get_from)(OrgContext*, haxorg_SubtreeLogHeadState const*);
  haxorg_HstdStr const* (*get_to)(OrgContext*, haxorg_SubtreeLogHeadState const*);
  haxorg_UserTime const* (*get_on)(OrgContext*, haxorg_SubtreeLogHeadState const*);
  bool (*__eq___const)(OrgContext*, haxorg_SubtreeLogHeadState, haxorg_SubtreeLogHeadState);
};

struct haxorg_SubtreeLogHeadDeadline_vtable {
  haxorg_HstdOpt const* (*get_from)(OrgContext*, haxorg_SubtreeLogHeadDeadline const*);
  haxorg_UserTime const* (*get_to)(OrgContext*, haxorg_SubtreeLogHeadDeadline const*);
  haxorg_UserTime const* (*get_on)(OrgContext*, haxorg_SubtreeLogHeadDeadline const*);
  bool (*__eq___const)(OrgContext*, haxorg_SubtreeLogHeadDeadline, haxorg_SubtreeLogHeadDeadline);
};

struct haxorg_SubtreeLogHeadSchedule_vtable {
  haxorg_HstdOpt const* (*get_from)(OrgContext*, haxorg_SubtreeLogHeadSchedule const*);
  haxorg_UserTime const* (*get_to)(OrgContext*, haxorg_SubtreeLogHeadSchedule const*);
  haxorg_UserTime const* (*get_on)(OrgContext*, haxorg_SubtreeLogHeadSchedule const*);
  bool (*__eq___const)(OrgContext*, haxorg_SubtreeLogHeadSchedule, haxorg_SubtreeLogHeadSchedule);
};

struct haxorg_SubtreeLogHeadTag_vtable {
  haxorg_UserTime const* (*get_on)(OrgContext*, haxorg_SubtreeLogHeadTag const*);
  haxorg_HashTagText const* (*get_tag)(OrgContext*, haxorg_SubtreeLogHeadTag const*);
  bool const* (*get_added)(OrgContext*, haxorg_SubtreeLogHeadTag const*);
  bool (*__eq___const)(OrgContext*, haxorg_SubtreeLogHeadTag, haxorg_SubtreeLogHeadTag);
};

struct haxorg_SubtreeLogHeadUnknown_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_SubtreeLogHeadUnknown, haxorg_SubtreeLogHeadUnknown);
};

struct haxorg_SubtreeLogHead_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_SubtreeLogHead, haxorg_SubtreeLogHead);
  bool (*isPriority_const)(OrgContext*, haxorg_SubtreeLogHead);
  haxorg_SubtreeLogHeadPriority (*getPriorityConst_const)(OrgContext*, haxorg_SubtreeLogHead);
  haxorg_SubtreeLogHeadPriority (*getPriorityMut)(OrgContext*, haxorg_SubtreeLogHead);
  bool (*isNote_const)(OrgContext*, haxorg_SubtreeLogHead);
  haxorg_SubtreeLogHeadNote (*getNoteConst_const)(OrgContext*, haxorg_SubtreeLogHead);
  haxorg_SubtreeLogHeadNote (*getNoteMut)(OrgContext*, haxorg_SubtreeLogHead);
  bool (*isRefile_const)(OrgContext*, haxorg_SubtreeLogHead);
  haxorg_SubtreeLogHeadRefile (*getRefileConst_const)(OrgContext*, haxorg_SubtreeLogHead);
  haxorg_SubtreeLogHeadRefile (*getRefileMut)(OrgContext*, haxorg_SubtreeLogHead);
  bool (*isClock_const)(OrgContext*, haxorg_SubtreeLogHead);
  haxorg_SubtreeLogHeadClock (*getClockConst_const)(OrgContext*, haxorg_SubtreeLogHead);
  haxorg_SubtreeLogHeadClock (*getClockMut)(OrgContext*, haxorg_SubtreeLogHead);
  bool (*isState_const)(OrgContext*, haxorg_SubtreeLogHead);
  haxorg_SubtreeLogHeadState (*getStateConst_const)(OrgContext*, haxorg_SubtreeLogHead);
  haxorg_SubtreeLogHeadState (*getStateMut)(OrgContext*, haxorg_SubtreeLogHead);
  bool (*isDeadline_const)(OrgContext*, haxorg_SubtreeLogHead);
  haxorg_SubtreeLogHeadDeadline (*getDeadlineConst_const)(OrgContext*, haxorg_SubtreeLogHead);
  haxorg_SubtreeLogHeadDeadline (*getDeadlineMut)(OrgContext*, haxorg_SubtreeLogHead);
  bool (*isSchedule_const)(OrgContext*, haxorg_SubtreeLogHead);
  haxorg_SubtreeLogHeadSchedule (*getScheduleConst_const)(OrgContext*, haxorg_SubtreeLogHead);
  haxorg_SubtreeLogHeadSchedule (*getScheduleMut)(OrgContext*, haxorg_SubtreeLogHead);
  bool (*isTag_const)(OrgContext*, haxorg_SubtreeLogHead);
  haxorg_SubtreeLogHeadTag (*getTagConst_const)(OrgContext*, haxorg_SubtreeLogHead);
  haxorg_SubtreeLogHeadTag (*getTagMut)(OrgContext*, haxorg_SubtreeLogHead);
  bool (*isUnknown_const)(OrgContext*, haxorg_SubtreeLogHead);
  haxorg_SubtreeLogHeadUnknown (*getUnknownConst_const)(OrgContext*, haxorg_SubtreeLogHead);
  haxorg_SubtreeLogHeadUnknown (*getUnknownMut)(OrgContext*, haxorg_SubtreeLogHead);
  haxorg_SubtreeLogHeadKind (*getLogKind_const)(OrgContext*, haxorg_SubtreeLogHead);
};

struct haxorg_SubtreeCompletion_vtable {
  int const* (*get_done)(OrgContext*, haxorg_SubtreeCompletion const*);
  int const* (*get_full)(OrgContext*, haxorg_SubtreeCompletion const*);
  bool const* (*get_isPercent)(OrgContext*, haxorg_SubtreeCompletion const*);
  bool (*__eq___const)(OrgContext*, haxorg_SubtreeCompletion, haxorg_SubtreeCompletion);
};

struct haxorg_AttrList_vtable {
  haxorg_HstdVec const* (*get_items)(OrgContext*, haxorg_AttrList const*);
  bool (*__eq___const)(OrgContext*, haxorg_AttrList, haxorg_AttrList);
};

struct haxorg_AttrGroup_vtable {
  haxorg_AttrList const* (*get_positional)(OrgContext*, haxorg_AttrGroup const*);
  haxorg_HstdUnorderedMap const* (*get_named)(OrgContext*, haxorg_AttrGroup const*);
  haxorg_HstdVec (*getFlatArgs_const)(OrgContext*, haxorg_AttrGroup);
  haxorg_HstdVec (*getAttrs_const)(OrgContext*, haxorg_AttrGroup, haxorg_HstdOpt);
  void (*setNamedAttr)(OrgContext*, haxorg_AttrGroup, haxorg_HstdStr, haxorg_HstdVec);
  void (*setPositionalAttr)(OrgContext*, haxorg_AttrGroup, haxorg_HstdVec);
  int (*getPositionalSize_const)(OrgContext*, haxorg_AttrGroup);
  int (*getNamedSize_const)(OrgContext*, haxorg_AttrGroup);
  bool (*isEmpty_const)(OrgContext*, haxorg_AttrGroup);
  haxorg_AttrList (*getAll_const)(OrgContext*, haxorg_AttrGroup);
  haxorg_AttrValue (*atPositional_const)(OrgContext*, haxorg_AttrGroup, int);
  haxorg_HstdOpt (*getPositional_const)(OrgContext*, haxorg_AttrGroup, int);
  haxorg_AttrList (*atNamed_const)(OrgContext*, haxorg_AttrGroup, haxorg_HstdStr);
  haxorg_HstdOpt (*getNamed_const)(OrgContext*, haxorg_AttrGroup, haxorg_HstdStr);
  haxorg_AttrValue (*atFirstNamed_const)(OrgContext*, haxorg_AttrGroup, haxorg_HstdStr);
  haxorg_HstdOpt (*getFirstNamed_const)(OrgContext*, haxorg_AttrGroup, haxorg_HstdStr);
  haxorg_AttrList (*atVarNamed_const)(OrgContext*, haxorg_AttrGroup, haxorg_HstdStr);
  haxorg_HstdOpt (*getVarNamed_const)(OrgContext*, haxorg_AttrGroup, haxorg_HstdStr);
  haxorg_AttrValue (*atFirstVarNamed_const)(OrgContext*, haxorg_AttrGroup, haxorg_HstdStr);
  haxorg_HstdOpt (*getFirstVarNamed_const)(OrgContext*, haxorg_AttrGroup, haxorg_HstdStr);
  bool (*__eq___const)(OrgContext*, haxorg_AttrGroup, haxorg_AttrGroup);
};

struct haxorg_OrgCodeEvalInputVar_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_OrgCodeEvalInputVar const*);
  haxorg_OrgJson const* (*get_value)(OrgContext*, haxorg_OrgCodeEvalInputVar const*);
  bool (*__eq___const)(OrgContext*, haxorg_OrgCodeEvalInputVar, haxorg_OrgCodeEvalInputVar);
};

struct haxorg_OrgCodeEvalInput_vtable {
  haxorg_AttrGroup const* (*get_blockAttrs)(OrgContext*, haxorg_OrgCodeEvalInput const*);
  haxorg_HstdStr const* (*get_tangledCode)(OrgContext*, haxorg_OrgCodeEvalInput const*);
  haxorg_HstdOpt const* (*get_exportType)(OrgContext*, haxorg_OrgCodeEvalInput const*);
  haxorg_OrgCodeEvalInputResultType const* (*get_resultType)(OrgContext*, haxorg_OrgCodeEvalInput const*);
  haxorg_OrgCodeEvalInputResultFormat const* (*get_resultFormat)(OrgContext*, haxorg_OrgCodeEvalInput const*);
  haxorg_OrgCodeEvalInputResultHandling const* (*get_resultHandling)(OrgContext*, haxorg_OrgCodeEvalInput const*);
  haxorg_HstdStr const* (*get_language)(OrgContext*, haxorg_OrgCodeEvalInput const*);
  haxorg_HstdVec const* (*get_argList)(OrgContext*, haxorg_OrgCodeEvalInput const*);
  bool (*__eq___const)(OrgContext*, haxorg_OrgCodeEvalInput, haxorg_OrgCodeEvalInput);
  haxorg_HstdOpt (*getVariable_const)(OrgContext*, haxorg_OrgCodeEvalInput, haxorg_HstdStr);
};

struct haxorg_OrgCodeEvalOutput_vtable {
  haxorg_HstdStr const* (*get_stdoutText)(OrgContext*, haxorg_OrgCodeEvalOutput const*);
  haxorg_HstdStr const* (*get_stderrText)(OrgContext*, haxorg_OrgCodeEvalOutput const*);
  int const* (*get_code)(OrgContext*, haxorg_OrgCodeEvalOutput const*);
  haxorg_HstdOpt const* (*get_cmd)(OrgContext*, haxorg_OrgCodeEvalOutput const*);
  haxorg_HstdVec const* (*get_args)(OrgContext*, haxorg_OrgCodeEvalOutput const*);
  haxorg_HstdStr const* (*get_cwd)(OrgContext*, haxorg_OrgCodeEvalOutput const*);
  haxorg_AttrGroup const* (*get_appliedHeaderArg)(OrgContext*, haxorg_OrgCodeEvalOutput const*);
  bool (*__eq___const)(OrgContext*, haxorg_OrgCodeEvalOutput, haxorg_OrgCodeEvalOutput);
};

struct haxorg_ColumnViewSummaryCheckboxAggregate_vtable {
  haxorg_ColumnViewSummaryCheckboxAggregateKind const* (*get_kind)(OrgContext*, haxorg_ColumnViewSummaryCheckboxAggregate const*);
  bool (*__eq___const)(OrgContext*, haxorg_ColumnViewSummaryCheckboxAggregate, haxorg_ColumnViewSummaryCheckboxAggregate);
};

struct haxorg_ColumnViewSummaryMathAggregate_vtable {
  haxorg_ColumnViewSummaryMathAggregateKind const* (*get_kind)(OrgContext*, haxorg_ColumnViewSummaryMathAggregate const*);
  haxorg_HstdOpt const* (*get_formatDigits)(OrgContext*, haxorg_ColumnViewSummaryMathAggregate const*);
  haxorg_HstdOpt const* (*get_formatPrecision)(OrgContext*, haxorg_ColumnViewSummaryMathAggregate const*);
  bool (*__eq___const)(OrgContext*, haxorg_ColumnViewSummaryMathAggregate, haxorg_ColumnViewSummaryMathAggregate);
};

struct haxorg_ColumnViewSummary_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ColumnViewSummary, haxorg_ColumnViewSummary);
  bool (*isCheckboxAggregate_const)(OrgContext*, haxorg_ColumnViewSummary);
  haxorg_ColumnViewSummaryCheckboxAggregate (*getCheckboxAggregateConst_const)(OrgContext*, haxorg_ColumnViewSummary);
  haxorg_ColumnViewSummaryCheckboxAggregate (*getCheckboxAggregateMut)(OrgContext*, haxorg_ColumnViewSummary);
  bool (*isMathAggregate_const)(OrgContext*, haxorg_ColumnViewSummary);
  haxorg_ColumnViewSummaryMathAggregate (*getMathAggregateConst_const)(OrgContext*, haxorg_ColumnViewSummary);
  haxorg_ColumnViewSummaryMathAggregate (*getMathAggregateMut)(OrgContext*, haxorg_ColumnViewSummary);
  haxorg_ColumnViewSummaryKind (*getKind_const)(OrgContext*, haxorg_ColumnViewSummary);
};

struct haxorg_ColumnViewColumn_vtable {
  haxorg_HstdOpt const* (*get_summary)(OrgContext*, haxorg_ColumnViewColumn const*);
  haxorg_HstdOpt const* (*get_width)(OrgContext*, haxorg_ColumnViewColumn const*);
  haxorg_HstdOpt const* (*get_property)(OrgContext*, haxorg_ColumnViewColumn const*);
  haxorg_HstdOpt const* (*get_propertyTitle)(OrgContext*, haxorg_ColumnViewColumn const*);
  bool (*__eq___const)(OrgContext*, haxorg_ColumnViewColumn, haxorg_ColumnViewColumn);
};

struct haxorg_ColumnView_vtable {
  haxorg_HstdVec const* (*get_columns)(OrgContext*, haxorg_ColumnView const*);
  bool (*__eq___const)(OrgContext*, haxorg_ColumnView, haxorg_ColumnView);
};

struct haxorg_BlockCodeLinePartRaw_vtable {
  haxorg_HstdStr const* (*get_code)(OrgContext*, haxorg_BlockCodeLinePartRaw const*);
  bool (*__eq___const)(OrgContext*, haxorg_BlockCodeLinePartRaw, haxorg_BlockCodeLinePartRaw);
};

struct haxorg_BlockCodeLinePartCallout_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_BlockCodeLinePartCallout const*);
  bool (*__eq___const)(OrgContext*, haxorg_BlockCodeLinePartCallout, haxorg_BlockCodeLinePartCallout);
};

struct haxorg_BlockCodeLinePartTangle_vtable {
  haxorg_HstdStr const* (*get_target)(OrgContext*, haxorg_BlockCodeLinePartTangle const*);
  bool (*__eq___const)(OrgContext*, haxorg_BlockCodeLinePartTangle, haxorg_BlockCodeLinePartTangle);
};

struct haxorg_BlockCodeLinePart_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart);
  bool (*isRaw_const)(OrgContext*, haxorg_BlockCodeLinePart);
  haxorg_BlockCodeLinePartRaw (*getRawConst_const)(OrgContext*, haxorg_BlockCodeLinePart);
  haxorg_BlockCodeLinePartRaw (*getRawMut)(OrgContext*, haxorg_BlockCodeLinePart);
  bool (*isCallout_const)(OrgContext*, haxorg_BlockCodeLinePart);
  haxorg_BlockCodeLinePartCallout (*getCalloutConst_const)(OrgContext*, haxorg_BlockCodeLinePart);
  haxorg_BlockCodeLinePartCallout (*getCalloutMut)(OrgContext*, haxorg_BlockCodeLinePart);
  bool (*isTangle_const)(OrgContext*, haxorg_BlockCodeLinePart);
  haxorg_BlockCodeLinePartTangle (*getTangleConst_const)(OrgContext*, haxorg_BlockCodeLinePart);
  haxorg_BlockCodeLinePartTangle (*getTangleMut)(OrgContext*, haxorg_BlockCodeLinePart);
  haxorg_BlockCodeLinePartKind (*getKind_const)(OrgContext*, haxorg_BlockCodeLinePart);
};

struct haxorg_BlockCodeLine_vtable {
  haxorg_HstdVec const* (*get_parts)(OrgContext*, haxorg_BlockCodeLine const*);
  bool (*__eq___const)(OrgContext*, haxorg_BlockCodeLine, haxorg_BlockCodeLine);
};

struct haxorg_DocumentExportConfigTaskExport_vtable {
  haxorg_HstdVec const* (*get_taskWhitelist)(OrgContext*, haxorg_DocumentExportConfigTaskExport const*);
  bool (*__eq___const)(OrgContext*, haxorg_DocumentExportConfigTaskExport, haxorg_DocumentExportConfigTaskExport);
};

struct haxorg_DocumentExportConfigDoExport_vtable {
  bool const* (*get_exportToc)(OrgContext*, haxorg_DocumentExportConfigDoExport const*);
  bool (*__eq___const)(OrgContext*, haxorg_DocumentExportConfigDoExport, haxorg_DocumentExportConfigDoExport);
};

struct haxorg_DocumentExportConfigExportFixed_vtable {
  int const* (*get_exportLevels)(OrgContext*, haxorg_DocumentExportConfigExportFixed const*);
  bool (*__eq___const)(OrgContext*, haxorg_DocumentExportConfigExportFixed, haxorg_DocumentExportConfigExportFixed);
};

struct haxorg_DocumentExportConfig_vtable {
  haxorg_HstdOpt const* (*get_inlinetasks)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_footnotes)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_clock)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_author)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_emphasis)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_specialStrings)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_propertyDrawers)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_statisticsCookies)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_todoText)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_smartQuotes)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_fixedWidth)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_timestamps)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_preserveBreaks)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_subSuperscripts)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_expandLinks)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_creator)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_drawers)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_date)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_entities)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_email)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_sectionNumbers)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_planning)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_priority)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_latex)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_timestamp)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_title)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_tables)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_HstdOpt const* (*get_headlineLevels)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_DocumentExportConfigBrokenLinks const* (*get_brokenLinks)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_DocumentExportConfigTagExport const* (*get_tagExport)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_DocumentExportConfigTaskFiltering const* (*get_taskFiltering)(OrgContext*, haxorg_DocumentExportConfig const*);
  haxorg_DocumentExportConfigArchivedTrees const* (*get_archivedTrees)(OrgContext*, haxorg_DocumentExportConfig const*);
  bool (*__eq___const)(OrgContext*, haxorg_DocumentExportConfig, haxorg_DocumentExportConfig);
  bool (*isDoExport_const)(OrgContext*, haxorg_DocumentExportConfig);
  haxorg_DocumentExportConfigDoExport (*getDoExportConst_const)(OrgContext*, haxorg_DocumentExportConfig);
  haxorg_DocumentExportConfigDoExport (*getDoExportMut)(OrgContext*, haxorg_DocumentExportConfig);
  bool (*isExportFixed_const)(OrgContext*, haxorg_DocumentExportConfig);
  haxorg_DocumentExportConfigExportFixed (*getExportFixedConst_const)(OrgContext*, haxorg_DocumentExportConfig);
  haxorg_DocumentExportConfigExportFixed (*getExportFixedMut)(OrgContext*, haxorg_DocumentExportConfig);
  haxorg_DocumentExportConfigTocExportKind (*getTocExportKind_const)(OrgContext*, haxorg_DocumentExportConfig);
};

struct haxorg_SubtreePeriod_vtable {
  haxorg_SubtreePeriodKind const* (*get_kind)(OrgContext*, haxorg_SubtreePeriod const*);
  haxorg_UserTime const* (*get_from)(OrgContext*, haxorg_SubtreePeriod const*);
  haxorg_HstdOpt const* (*get_to)(OrgContext*, haxorg_SubtreePeriod const*);
  bool (*__eq___const)(OrgContext*, haxorg_SubtreePeriod, haxorg_SubtreePeriod);
};

struct haxorg_NamedPropertyNonblocking_vtable {
  bool const* (*get_isBlocking)(OrgContext*, haxorg_NamedPropertyNonblocking const*);
  bool (*__eq___const)(OrgContext*, haxorg_NamedPropertyNonblocking, haxorg_NamedPropertyNonblocking);
};

struct haxorg_NamedPropertyArchiveTime_vtable {
  haxorg_UserTime const* (*get_time)(OrgContext*, haxorg_NamedPropertyArchiveTime const*);
  bool (*__eq___const)(OrgContext*, haxorg_NamedPropertyArchiveTime, haxorg_NamedPropertyArchiveTime);
};

struct haxorg_NamedPropertyArchiveFile_vtable {
  haxorg_HstdStr const* (*get_file)(OrgContext*, haxorg_NamedPropertyArchiveFile const*);
  bool (*__eq___const)(OrgContext*, haxorg_NamedPropertyArchiveFile, haxorg_NamedPropertyArchiveFile);
};

struct haxorg_NamedPropertyArchiveOlpath_vtable {
  haxorg_SubtreePath const* (*get_path)(OrgContext*, haxorg_NamedPropertyArchiveOlpath const*);
  bool (*__eq___const)(OrgContext*, haxorg_NamedPropertyArchiveOlpath, haxorg_NamedPropertyArchiveOlpath);
};

struct haxorg_NamedPropertyArchiveTarget_vtable {
  haxorg_SubtreePath const* (*get_path)(OrgContext*, haxorg_NamedPropertyArchiveTarget const*);
  haxorg_HstdStr const* (*get_pattern)(OrgContext*, haxorg_NamedPropertyArchiveTarget const*);
  bool (*__eq___const)(OrgContext*, haxorg_NamedPropertyArchiveTarget, haxorg_NamedPropertyArchiveTarget);
};

struct haxorg_NamedPropertyArchiveCategory_vtable {
  haxorg_HstdStr const* (*get_category)(OrgContext*, haxorg_NamedPropertyArchiveCategory const*);
  bool (*__eq___const)(OrgContext*, haxorg_NamedPropertyArchiveCategory, haxorg_NamedPropertyArchiveCategory);
};

struct haxorg_NamedPropertyArchiveTodo_vtable {
  haxorg_HstdStr const* (*get_todo)(OrgContext*, haxorg_NamedPropertyArchiveTodo const*);
  bool (*__eq___const)(OrgContext*, haxorg_NamedPropertyArchiveTodo, haxorg_NamedPropertyArchiveTodo);
};

struct haxorg_NamedPropertyTrigger_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_NamedPropertyTrigger, haxorg_NamedPropertyTrigger);
};

struct haxorg_NamedPropertyExportLatexClass_vtable {
  haxorg_HstdStr const* (*get_latexClass)(OrgContext*, haxorg_NamedPropertyExportLatexClass const*);
  bool (*__eq___const)(OrgContext*, haxorg_NamedPropertyExportLatexClass, haxorg_NamedPropertyExportLatexClass);
};

struct haxorg_NamedPropertyCookieData_vtable {
  bool const* (*get_isRecursive)(OrgContext*, haxorg_NamedPropertyCookieData const*);
  haxorg_SubtreeTodoSource const* (*get_source)(OrgContext*, haxorg_NamedPropertyCookieData const*);
  bool (*__eq___const)(OrgContext*, haxorg_NamedPropertyCookieData, haxorg_NamedPropertyCookieData);
};

struct haxorg_NamedPropertyExportLatexClassOptions_vtable {
  haxorg_HstdVec const* (*get_options)(OrgContext*, haxorg_NamedPropertyExportLatexClassOptions const*);
  bool (*__eq___const)(OrgContext*, haxorg_NamedPropertyExportLatexClassOptions, haxorg_NamedPropertyExportLatexClassOptions);
};

struct haxorg_NamedPropertyExportLatexHeader_vtable {
  haxorg_HstdStr const* (*get_header)(OrgContext*, haxorg_NamedPropertyExportLatexHeader const*);
  bool (*__eq___const)(OrgContext*, haxorg_NamedPropertyExportLatexHeader, haxorg_NamedPropertyExportLatexHeader);
};

struct haxorg_NamedPropertyExportLatexCompiler_vtable {
  haxorg_HstdStr const* (*get_compiler)(OrgContext*, haxorg_NamedPropertyExportLatexCompiler const*);
  bool (*__eq___const)(OrgContext*, haxorg_NamedPropertyExportLatexCompiler, haxorg_NamedPropertyExportLatexCompiler);
};

struct haxorg_NamedPropertyOrdered_vtable {
  bool const* (*get_isOrdered)(OrgContext*, haxorg_NamedPropertyOrdered const*);
  bool (*__eq___const)(OrgContext*, haxorg_NamedPropertyOrdered, haxorg_NamedPropertyOrdered);
};

struct haxorg_NamedPropertyEffort_vtable {
  int const* (*get_hours)(OrgContext*, haxorg_NamedPropertyEffort const*);
  int const* (*get_minutes)(OrgContext*, haxorg_NamedPropertyEffort const*);
  bool (*__eq___const)(OrgContext*, haxorg_NamedPropertyEffort, haxorg_NamedPropertyEffort);
};

struct haxorg_NamedPropertyVisibility_vtable {
  haxorg_NamedPropertyVisibilityLevel const* (*get_level)(OrgContext*, haxorg_NamedPropertyVisibility const*);
  bool (*__eq___const)(OrgContext*, haxorg_NamedPropertyVisibility, haxorg_NamedPropertyVisibility);
};

struct haxorg_NamedPropertyExportOptions_vtable {
  haxorg_HstdStr const* (*get_backend)(OrgContext*, haxorg_NamedPropertyExportOptions const*);
  haxorg_HstdUnorderedMap const* (*get_values)(OrgContext*, haxorg_NamedPropertyExportOptions const*);
  bool (*__eq___const)(OrgContext*, haxorg_NamedPropertyExportOptions, haxorg_NamedPropertyExportOptions);
};

struct haxorg_NamedPropertyBlocker_vtable {
  haxorg_HstdVec const* (*get_blockers)(OrgContext*, haxorg_NamedPropertyBlocker const*);
  bool (*__eq___const)(OrgContext*, haxorg_NamedPropertyBlocker, haxorg_NamedPropertyBlocker);
};

struct haxorg_NamedPropertyUnnumbered_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_NamedPropertyUnnumbered, haxorg_NamedPropertyUnnumbered);
};

struct haxorg_NamedPropertyCreated_vtable {
  haxorg_UserTime const* (*get_time)(OrgContext*, haxorg_NamedPropertyCreated const*);
  bool (*__eq___const)(OrgContext*, haxorg_NamedPropertyCreated, haxorg_NamedPropertyCreated);
};

struct haxorg_NamedPropertyRadioId_vtable {
  haxorg_HstdVec const* (*get_words)(OrgContext*, haxorg_NamedPropertyRadioId const*);
  bool (*__eq___const)(OrgContext*, haxorg_NamedPropertyRadioId, haxorg_NamedPropertyRadioId);
};

struct haxorg_NamedPropertyHashtagDef_vtable {
  haxorg_HashTagText const* (*get_hashtag)(OrgContext*, haxorg_NamedPropertyHashtagDef const*);
  bool (*__eq___const)(OrgContext*, haxorg_NamedPropertyHashtagDef, haxorg_NamedPropertyHashtagDef);
};

struct haxorg_NamedPropertyCustomArgs_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_NamedPropertyCustomArgs const*);
  haxorg_HstdOpt const* (*get_sub)(OrgContext*, haxorg_NamedPropertyCustomArgs const*);
  haxorg_AttrGroup const* (*get_attrs)(OrgContext*, haxorg_NamedPropertyCustomArgs const*);
  bool (*__eq___const)(OrgContext*, haxorg_NamedPropertyCustomArgs, haxorg_NamedPropertyCustomArgs);
};

struct haxorg_NamedPropertyCustomRaw_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_NamedPropertyCustomRaw const*);
  haxorg_HstdStr const* (*get_value)(OrgContext*, haxorg_NamedPropertyCustomRaw const*);
  bool (*__eq___const)(OrgContext*, haxorg_NamedPropertyCustomRaw, haxorg_NamedPropertyCustomRaw);
};

struct haxorg_NamedPropertyCustomId_vtable {
  haxorg_HstdStr const* (*get_value)(OrgContext*, haxorg_NamedPropertyCustomId const*);
  bool (*__eq___const)(OrgContext*, haxorg_NamedPropertyCustomId, haxorg_NamedPropertyCustomId);
};

struct haxorg_NamedPropertyCustomSubtreeJson_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_NamedPropertyCustomSubtreeJson const*);
  haxorg_OrgJson const* (*get_value)(OrgContext*, haxorg_NamedPropertyCustomSubtreeJson const*);
  bool (*__eq___const)(OrgContext*, haxorg_NamedPropertyCustomSubtreeJson, haxorg_NamedPropertyCustomSubtreeJson);
};

struct haxorg_NamedPropertyCustomSubtreeFlags_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_NamedPropertyCustomSubtreeFlags const*);
  haxorg_AttrGroup const* (*get_value)(OrgContext*, haxorg_NamedPropertyCustomSubtreeFlags const*);
  bool (*__eq___const)(OrgContext*, haxorg_NamedPropertyCustomSubtreeFlags, haxorg_NamedPropertyCustomSubtreeFlags);
};

struct haxorg_NamedProperty_vtable {
  bool (*isMatching_const)(OrgContext*, haxorg_NamedProperty, haxorg_HstdStr, haxorg_HstdOpt);
  haxorg_HstdStr (*getName_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_HstdOpt (*getSubKind_const)(OrgContext*, haxorg_NamedProperty);
  bool (*__eq___const)(OrgContext*, haxorg_NamedProperty, haxorg_NamedProperty);
  bool (*isNonblocking_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyNonblocking (*getNonblockingConst_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyNonblocking (*getNonblockingMut)(OrgContext*, haxorg_NamedProperty);
  bool (*isArchiveTime_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyArchiveTime (*getArchiveTimeConst_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyArchiveTime (*getArchiveTimeMut)(OrgContext*, haxorg_NamedProperty);
  bool (*isArchiveFile_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyArchiveFile (*getArchiveFileConst_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyArchiveFile (*getArchiveFileMut)(OrgContext*, haxorg_NamedProperty);
  bool (*isArchiveOlpath_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyArchiveOlpath (*getArchiveOlpathConst_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyArchiveOlpath (*getArchiveOlpathMut)(OrgContext*, haxorg_NamedProperty);
  bool (*isArchiveTarget_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyArchiveTarget (*getArchiveTargetConst_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyArchiveTarget (*getArchiveTargetMut)(OrgContext*, haxorg_NamedProperty);
  bool (*isArchiveCategory_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyArchiveCategory (*getArchiveCategoryConst_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyArchiveCategory (*getArchiveCategoryMut)(OrgContext*, haxorg_NamedProperty);
  bool (*isArchiveTodo_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyArchiveTodo (*getArchiveTodoConst_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyArchiveTodo (*getArchiveTodoMut)(OrgContext*, haxorg_NamedProperty);
  bool (*isTrigger_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyTrigger (*getTriggerConst_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyTrigger (*getTriggerMut)(OrgContext*, haxorg_NamedProperty);
  bool (*isExportLatexClass_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyExportLatexClass (*getExportLatexClassConst_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyExportLatexClass (*getExportLatexClassMut)(OrgContext*, haxorg_NamedProperty);
  bool (*isCookieData_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyCookieData (*getCookieDataConst_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyCookieData (*getCookieDataMut)(OrgContext*, haxorg_NamedProperty);
  bool (*isExportLatexClassOptions_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyExportLatexClassOptions (*getExportLatexClassOptionsConst_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyExportLatexClassOptions (*getExportLatexClassOptionsMut)(OrgContext*, haxorg_NamedProperty);
  bool (*isExportLatexHeader_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyExportLatexHeader (*getExportLatexHeaderConst_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyExportLatexHeader (*getExportLatexHeaderMut)(OrgContext*, haxorg_NamedProperty);
  bool (*isExportLatexCompiler_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyExportLatexCompiler (*getExportLatexCompilerConst_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyExportLatexCompiler (*getExportLatexCompilerMut)(OrgContext*, haxorg_NamedProperty);
  bool (*isOrdered_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyOrdered (*getOrderedConst_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyOrdered (*getOrderedMut)(OrgContext*, haxorg_NamedProperty);
  bool (*isEffort_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyEffort (*getEffortConst_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyEffort (*getEffortMut)(OrgContext*, haxorg_NamedProperty);
  bool (*isVisibility_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyVisibility (*getVisibilityConst_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyVisibility (*getVisibilityMut)(OrgContext*, haxorg_NamedProperty);
  bool (*isExportOptions_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyExportOptions (*getExportOptionsConst_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyExportOptions (*getExportOptionsMut)(OrgContext*, haxorg_NamedProperty);
  bool (*isBlocker_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyBlocker (*getBlockerConst_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyBlocker (*getBlockerMut)(OrgContext*, haxorg_NamedProperty);
  bool (*isUnnumbered_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyUnnumbered (*getUnnumberedConst_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyUnnumbered (*getUnnumberedMut)(OrgContext*, haxorg_NamedProperty);
  bool (*isCreated_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyCreated (*getCreatedConst_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyCreated (*getCreatedMut)(OrgContext*, haxorg_NamedProperty);
  bool (*isRadioId_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyRadioId (*getRadioIdConst_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyRadioId (*getRadioIdMut)(OrgContext*, haxorg_NamedProperty);
  bool (*isHashtagDef_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyHashtagDef (*getHashtagDefConst_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyHashtagDef (*getHashtagDefMut)(OrgContext*, haxorg_NamedProperty);
  bool (*isCustomArgs_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyCustomArgs (*getCustomArgsConst_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyCustomArgs (*getCustomArgsMut)(OrgContext*, haxorg_NamedProperty);
  bool (*isCustomRaw_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyCustomRaw (*getCustomRawConst_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyCustomRaw (*getCustomRawMut)(OrgContext*, haxorg_NamedProperty);
  bool (*isCustomId_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyCustomId (*getCustomIdConst_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyCustomId (*getCustomIdMut)(OrgContext*, haxorg_NamedProperty);
  bool (*isCustomSubtreeJson_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyCustomSubtreeJson (*getCustomSubtreeJsonConst_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyCustomSubtreeJson (*getCustomSubtreeJsonMut)(OrgContext*, haxorg_NamedProperty);
  bool (*isCustomSubtreeFlags_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyCustomSubtreeFlags (*getCustomSubtreeFlagsConst_const)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyCustomSubtreeFlags (*getCustomSubtreeFlagsMut)(OrgContext*, haxorg_NamedProperty);
  haxorg_NamedPropertyKind (*getKind_const)(OrgContext*, haxorg_NamedProperty);
};

struct haxorg_OrgDiagnosticsParseTokenError_vtable {
  haxorg_HstdStr const* (*get_brief)(OrgContext*, haxorg_OrgDiagnosticsParseTokenError const*);
  haxorg_HstdStr const* (*get_detail)(OrgContext*, haxorg_OrgDiagnosticsParseTokenError const*);
  haxorg_HstdStr const* (*get_parserFunction)(OrgContext*, haxorg_OrgDiagnosticsParseTokenError const*);
  int const* (*get_parserLine)(OrgContext*, haxorg_OrgDiagnosticsParseTokenError const*);
  haxorg_OrgTokenKind const* (*get_tokenKind)(OrgContext*, haxorg_OrgDiagnosticsParseTokenError const*);
  haxorg_HstdStr const* (*get_tokenText)(OrgContext*, haxorg_OrgDiagnosticsParseTokenError const*);
  haxorg_ParseSourceLoc const* (*get_loc)(OrgContext*, haxorg_OrgDiagnosticsParseTokenError const*);
  haxorg_HstdStr const* (*get_errName)(OrgContext*, haxorg_OrgDiagnosticsParseTokenError const*);
  haxorg_HstdStr const* (*get_errCode)(OrgContext*, haxorg_OrgDiagnosticsParseTokenError const*);
  bool (*__eq___const)(OrgContext*, haxorg_OrgDiagnosticsParseTokenError, haxorg_OrgDiagnosticsParseTokenError);
};

struct haxorg_OrgDiagnosticsParseError_vtable {
  haxorg_HstdStr const* (*get_brief)(OrgContext*, haxorg_OrgDiagnosticsParseError const*);
  haxorg_HstdStr const* (*get_detail)(OrgContext*, haxorg_OrgDiagnosticsParseError const*);
  haxorg_HstdStr const* (*get_parserFunction)(OrgContext*, haxorg_OrgDiagnosticsParseError const*);
  int const* (*get_parserLine)(OrgContext*, haxorg_OrgDiagnosticsParseError const*);
  haxorg_HstdStr const* (*get_errName)(OrgContext*, haxorg_OrgDiagnosticsParseError const*);
  haxorg_HstdStr const* (*get_errCode)(OrgContext*, haxorg_OrgDiagnosticsParseError const*);
  haxorg_HstdOpt const* (*get_loc)(OrgContext*, haxorg_OrgDiagnosticsParseError const*);
  bool (*__eq___const)(OrgContext*, haxorg_OrgDiagnosticsParseError, haxorg_OrgDiagnosticsParseError);
};

struct haxorg_OrgDiagnosticsIncludeError_vtable {
  haxorg_HstdStr const* (*get_brief)(OrgContext*, haxorg_OrgDiagnosticsIncludeError const*);
  haxorg_HstdStr const* (*get_targetPath)(OrgContext*, haxorg_OrgDiagnosticsIncludeError const*);
  haxorg_HstdStr const* (*get_workingFile)(OrgContext*, haxorg_OrgDiagnosticsIncludeError const*);
  bool (*__eq___const)(OrgContext*, haxorg_OrgDiagnosticsIncludeError, haxorg_OrgDiagnosticsIncludeError);
};

struct haxorg_OrgDiagnosticsConvertError_vtable {
  haxorg_HstdStr const* (*get_brief)(OrgContext*, haxorg_OrgDiagnosticsConvertError const*);
  haxorg_HstdStr const* (*get_detail)(OrgContext*, haxorg_OrgDiagnosticsConvertError const*);
  haxorg_HstdStr const* (*get_convertFunction)(OrgContext*, haxorg_OrgDiagnosticsConvertError const*);
  int const* (*get_convertLine)(OrgContext*, haxorg_OrgDiagnosticsConvertError const*);
  haxorg_HstdStr const* (*get_convertFile)(OrgContext*, haxorg_OrgDiagnosticsConvertError const*);
  haxorg_HstdStr const* (*get_errName)(OrgContext*, haxorg_OrgDiagnosticsConvertError const*);
  haxorg_HstdStr const* (*get_errCode)(OrgContext*, haxorg_OrgDiagnosticsConvertError const*);
  haxorg_HstdOpt const* (*get_loc)(OrgContext*, haxorg_OrgDiagnosticsConvertError const*);
  bool (*__eq___const)(OrgContext*, haxorg_OrgDiagnosticsConvertError, haxorg_OrgDiagnosticsConvertError);
};

struct haxorg_OrgDiagnosticsInternalError_vtable {
  haxorg_HstdStr const* (*get_message)(OrgContext*, haxorg_OrgDiagnosticsInternalError const*);
  haxorg_HstdStr const* (*get_function)(OrgContext*, haxorg_OrgDiagnosticsInternalError const*);
  int const* (*get_line)(OrgContext*, haxorg_OrgDiagnosticsInternalError const*);
  haxorg_HstdStr const* (*get_file)(OrgContext*, haxorg_OrgDiagnosticsInternalError const*);
  haxorg_HstdOpt const* (*get_loc)(OrgContext*, haxorg_OrgDiagnosticsInternalError const*);
  bool (*__eq___const)(OrgContext*, haxorg_OrgDiagnosticsInternalError, haxorg_OrgDiagnosticsInternalError);
};

struct haxorg_OrgDiagnostics_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_OrgDiagnostics, haxorg_OrgDiagnostics);
  bool (*isParseTokenError_const)(OrgContext*, haxorg_OrgDiagnostics);
  haxorg_OrgDiagnosticsParseTokenError (*getParseTokenErrorConst_const)(OrgContext*, haxorg_OrgDiagnostics);
  haxorg_OrgDiagnosticsParseTokenError (*getParseTokenErrorMut)(OrgContext*, haxorg_OrgDiagnostics);
  bool (*isParseError_const)(OrgContext*, haxorg_OrgDiagnostics);
  haxorg_OrgDiagnosticsParseError (*getParseErrorConst_const)(OrgContext*, haxorg_OrgDiagnostics);
  haxorg_OrgDiagnosticsParseError (*getParseErrorMut)(OrgContext*, haxorg_OrgDiagnostics);
  bool (*isIncludeError_const)(OrgContext*, haxorg_OrgDiagnostics);
  haxorg_OrgDiagnosticsIncludeError (*getIncludeErrorConst_const)(OrgContext*, haxorg_OrgDiagnostics);
  haxorg_OrgDiagnosticsIncludeError (*getIncludeErrorMut)(OrgContext*, haxorg_OrgDiagnostics);
  bool (*isConvertError_const)(OrgContext*, haxorg_OrgDiagnostics);
  haxorg_OrgDiagnosticsConvertError (*getConvertErrorConst_const)(OrgContext*, haxorg_OrgDiagnostics);
  haxorg_OrgDiagnosticsConvertError (*getConvertErrorMut)(OrgContext*, haxorg_OrgDiagnostics);
  bool (*isInternalError_const)(OrgContext*, haxorg_OrgDiagnostics);
  haxorg_OrgDiagnosticsInternalError (*getInternalErrorConst_const)(OrgContext*, haxorg_OrgDiagnostics);
  haxorg_OrgDiagnosticsInternalError (*getInternalErrorMut)(OrgContext*, haxorg_OrgDiagnostics);
  haxorg_OrgDiagnosticsKind (*getKind_const)(OrgContext*, haxorg_OrgDiagnostics);
};

struct haxorg_ErrorItem_vtable {
  haxorg_OrgDiagnostics const* (*get_diag)(OrgContext*, haxorg_ErrorItem const*);
};

struct haxorg_ErrorGroup_vtable {
  haxorg_HstdVec const* (*get_diagnostics)(OrgContext*, haxorg_ErrorGroup const*);
};

struct haxorg_Stmt_vtable {
  haxorg_HstdVec const* (*get_attached)(OrgContext*, haxorg_Stmt const*);
  haxorg_HstdVec (*getAttached_const)(OrgContext*, haxorg_Stmt, haxorg_HstdOpt);
  haxorg_HstdVec (*getCaption_const)(OrgContext*, haxorg_Stmt);
  haxorg_HstdVec (*getName_const)(OrgContext*, haxorg_Stmt);
  haxorg_HstdVec (*getAttrs_const)(OrgContext*, haxorg_Stmt, haxorg_HstdOpt);
  haxorg_HstdOpt (*getFirstAttr_const)(OrgContext*, haxorg_Stmt, haxorg_HstdStr);
  haxorg_HstdOpt (*getFirstAttrString_const)(OrgContext*, haxorg_Stmt, haxorg_HstdStr);
  haxorg_HstdOpt (*getFirstAttrInt_const)(OrgContext*, haxorg_Stmt, haxorg_HstdStr);
  haxorg_HstdOpt (*getFirstAttrBool_const)(OrgContext*, haxorg_Stmt, haxorg_HstdStr);
  haxorg_HstdOpt (*getFirstAttrDouble_const)(OrgContext*, haxorg_Stmt, haxorg_HstdStr);
  haxorg_HstdOpt (*getFirstAttrLisp_const)(OrgContext*, haxorg_Stmt, haxorg_HstdStr);
  haxorg_HstdOpt (*getFirstAttrKind_const)(OrgContext*, haxorg_Stmt, haxorg_HstdStr);
};

struct haxorg_Leaf_vtable {
  haxorg_HstdStr const* (*get_text)(OrgContext*, haxorg_Leaf const*);
  haxorg_HstdStr (*getText_const)(OrgContext*, haxorg_Leaf);
};

struct haxorg_TimeRepeat_vtable {
  haxorg_TimeRepeatMode const* (*get_mode)(OrgContext*, haxorg_TimeRepeat const*);
  haxorg_TimeRepeatPeriod const* (*get_period)(OrgContext*, haxorg_TimeRepeat const*);
  int const* (*get_count)(OrgContext*, haxorg_TimeRepeat const*);
  bool (*__eq___const)(OrgContext*, haxorg_TimeRepeat, haxorg_TimeRepeat);
};

struct haxorg_TimeStatic_vtable {
  haxorg_HstdVec const* (*get_repeat)(OrgContext*, haxorg_TimeStatic const*);
  haxorg_HstdOpt const* (*get_warn)(OrgContext*, haxorg_TimeStatic const*);
  haxorg_UserTime const* (*get_time)(OrgContext*, haxorg_TimeStatic const*);
  bool (*__eq___const)(OrgContext*, haxorg_TimeStatic, haxorg_TimeStatic);
};

struct haxorg_TimeDynamic_vtable {
  haxorg_LispCode const* (*get_expr)(OrgContext*, haxorg_TimeDynamic const*);
  bool (*__eq___const)(OrgContext*, haxorg_TimeDynamic, haxorg_TimeDynamic);
};

struct haxorg_Time_vtable {
  bool const* (*get_isActive)(OrgContext*, haxorg_Time const*);
  haxorg_HstdOpt (*getYear_const)(OrgContext*, haxorg_Time);
  haxorg_HstdOpt (*getMonth_const)(OrgContext*, haxorg_Time);
  haxorg_HstdOpt (*getDay_const)(OrgContext*, haxorg_Time);
  haxorg_HstdOpt (*getHour_const)(OrgContext*, haxorg_Time);
  haxorg_HstdOpt (*getMinute_const)(OrgContext*, haxorg_Time);
  haxorg_HstdOpt (*getSecond_const)(OrgContext*, haxorg_Time);
  haxorg_UserTime (*getStaticTime_const)(OrgContext*, haxorg_Time);
  bool (*isStatic_const)(OrgContext*, haxorg_Time);
  haxorg_TimeStatic (*getStaticConst_const)(OrgContext*, haxorg_Time);
  haxorg_TimeStatic (*getStaticMut)(OrgContext*, haxorg_Time);
  bool (*isDynamic_const)(OrgContext*, haxorg_Time);
  haxorg_TimeDynamic (*getDynamicConst_const)(OrgContext*, haxorg_Time);
  haxorg_TimeDynamic (*getDynamicMut)(OrgContext*, haxorg_Time);
  haxorg_TimeTimeKind (*getTimeKind_const)(OrgContext*, haxorg_Time);
};

struct haxorg_TimeRange_vtable {
  haxorg_SemId const* (*get_from)(OrgContext*, haxorg_TimeRange const*);
  haxorg_SemId const* (*get_to)(OrgContext*, haxorg_TimeRange const*);
  haxorg_HstdOpt (*getClockedTimeSeconds_const)(OrgContext*, haxorg_TimeRange);
};

struct haxorg_Macro_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_Macro const*);
  haxorg_AttrGroup const* (*get_attrs)(OrgContext*, haxorg_Macro const*);
};

struct haxorg_SymbolParam_vtable {
  haxorg_HstdOpt const* (*get_key)(OrgContext*, haxorg_SymbolParam const*);
  haxorg_HstdStr const* (*get_value)(OrgContext*, haxorg_SymbolParam const*);
};

struct haxorg_Symbol_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_Symbol const*);
  haxorg_HstdVec const* (*get_parameters)(OrgContext*, haxorg_Symbol const*);
  haxorg_HstdVec const* (*get_positional)(OrgContext*, haxorg_Symbol const*);
};

struct haxorg_ErrorSkipGroup_vtable {
  haxorg_HstdVec const* (*get_skipped)(OrgContext*, haxorg_ErrorSkipGroup const*);
};

struct haxorg_RadioTarget_vtable {
  haxorg_HstdVec const* (*get_words)(OrgContext*, haxorg_RadioTarget const*);
};

struct haxorg_SubtreeLog_vtable {
  haxorg_SubtreeLogHead const* (*get_head)(OrgContext*, haxorg_SubtreeLog const*);
  haxorg_HstdOpt const* (*get_desc)(OrgContext*, haxorg_SubtreeLog const*);
  void (*setDescription)(OrgContext*, haxorg_SubtreeLog, haxorg_SemId);
};

struct haxorg_Subtree_vtable {
  int const* (*get_level)(OrgContext*, haxorg_Subtree const*);
  haxorg_HstdOpt const* (*get_treeId)(OrgContext*, haxorg_Subtree const*);
  haxorg_HstdOpt const* (*get_todo)(OrgContext*, haxorg_Subtree const*);
  haxorg_HstdOpt const* (*get_completion)(OrgContext*, haxorg_Subtree const*);
  haxorg_HstdOpt const* (*get_description)(OrgContext*, haxorg_Subtree const*);
  haxorg_HstdVec const* (*get_tags)(OrgContext*, haxorg_Subtree const*);
  haxorg_SemId const* (*get_title)(OrgContext*, haxorg_Subtree const*);
  haxorg_HstdVec const* (*get_logbook)(OrgContext*, haxorg_Subtree const*);
  haxorg_HstdVec const* (*get_properties)(OrgContext*, haxorg_Subtree const*);
  haxorg_HstdOpt const* (*get_closed)(OrgContext*, haxorg_Subtree const*);
  haxorg_HstdOpt const* (*get_deadline)(OrgContext*, haxorg_Subtree const*);
  haxorg_HstdOpt const* (*get_scheduled)(OrgContext*, haxorg_Subtree const*);
  bool const* (*get_isComment)(OrgContext*, haxorg_Subtree const*);
  bool const* (*get_isArchived)(OrgContext*, haxorg_Subtree const*);
  haxorg_HstdOpt const* (*get_priority)(OrgContext*, haxorg_Subtree const*);
  haxorg_HstdVec (*getTimePeriods_const)(OrgContext*, haxorg_Subtree, haxorg_HstdIntSet);
  haxorg_HstdVec (*getProperties_const)(OrgContext*, haxorg_Subtree, haxorg_HstdStr, haxorg_HstdOpt);
  haxorg_HstdOpt (*getProperty_const)(OrgContext*, haxorg_Subtree, haxorg_HstdStr, haxorg_HstdOpt);
  void (*removeProperty)(OrgContext*, haxorg_Subtree, haxorg_HstdStr, haxorg_HstdOpt);
  void (*setProperty)(OrgContext*, haxorg_Subtree, haxorg_NamedProperty);
  void (*setPropertyStrValue)(OrgContext*, haxorg_Subtree, haxorg_HstdStr, haxorg_HstdStr, haxorg_HstdOpt);
  haxorg_HstdStr (*getCleanTitle_const)(OrgContext*, haxorg_Subtree);
  haxorg_HstdOpt (*getTodoKeyword_const)(OrgContext*, haxorg_Subtree);
};

struct haxorg_Call_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_Call const*);
  haxorg_AttrGroup const* (*get_attrs)(OrgContext*, haxorg_Call const*);
  bool const* (*get_isCommand)(OrgContext*, haxorg_Call const*);
};

struct haxorg_ListItem_vtable {
  haxorg_CheckboxState const* (*get_checkbox)(OrgContext*, haxorg_ListItem const*);
  haxorg_HstdOpt const* (*get_header)(OrgContext*, haxorg_ListItem const*);
  haxorg_HstdOpt const* (*get_bullet)(OrgContext*, haxorg_ListItem const*);
  bool (*isDescriptionItem_const)(OrgContext*, haxorg_ListItem);
  haxorg_HstdOpt (*getCleanHeader_const)(OrgContext*, haxorg_ListItem);
};

struct haxorg_DocumentOptions_vtable {
  haxorg_InitialSubtreeVisibility const* (*get_initialVisibility)(OrgContext*, haxorg_DocumentOptions const*);
  haxorg_HstdVec const* (*get_properties)(OrgContext*, haxorg_DocumentOptions const*);
  haxorg_DocumentExportConfig const* (*get_exportConfig)(OrgContext*, haxorg_DocumentOptions const*);
  haxorg_HstdOpt const* (*get_fixedWidthSections)(OrgContext*, haxorg_DocumentOptions const*);
  haxorg_HstdOpt const* (*get_startupIndented)(OrgContext*, haxorg_DocumentOptions const*);
  haxorg_HstdOpt const* (*get_category)(OrgContext*, haxorg_DocumentOptions const*);
  haxorg_HstdOpt const* (*get_setupfile)(OrgContext*, haxorg_DocumentOptions const*);
  haxorg_HstdOpt const* (*get_maxSubtreeLevelExport)(OrgContext*, haxorg_DocumentOptions const*);
  haxorg_HstdOpt const* (*get_columns)(OrgContext*, haxorg_DocumentOptions const*);
  haxorg_HstdVec const* (*get_todoKeywords)(OrgContext*, haxorg_DocumentOptions const*);
  haxorg_HstdVec const* (*get_doneKeywords)(OrgContext*, haxorg_DocumentOptions const*);
  haxorg_HstdVec (*getProperties_const)(OrgContext*, haxorg_DocumentOptions, haxorg_HstdStr, haxorg_HstdOpt);
  haxorg_HstdOpt (*getProperty_const)(OrgContext*, haxorg_DocumentOptions, haxorg_HstdStr, haxorg_HstdOpt);
};

struct haxorg_DocumentFragment_vtable {
  int const* (*get_baseLine)(OrgContext*, haxorg_DocumentFragment const*);
  int const* (*get_baseCol)(OrgContext*, haxorg_DocumentFragment const*);
};

struct haxorg_CriticMarkup_vtable {
  haxorg_CriticMarkupKind const* (*get_kind)(OrgContext*, haxorg_CriticMarkup const*);
};

struct haxorg_Document_vtable {
  haxorg_HstdOpt const* (*get_title)(OrgContext*, haxorg_Document const*);
  haxorg_HstdOpt const* (*get_author)(OrgContext*, haxorg_Document const*);
  haxorg_HstdOpt const* (*get_creator)(OrgContext*, haxorg_Document const*);
  haxorg_HstdVec const* (*get_filetags)(OrgContext*, haxorg_Document const*);
  haxorg_HstdOpt const* (*get_email)(OrgContext*, haxorg_Document const*);
  haxorg_HstdVec const* (*get_language)(OrgContext*, haxorg_Document const*);
  haxorg_SemId const* (*get_options)(OrgContext*, haxorg_Document const*);
  haxorg_HstdOpt const* (*get_exportFileName)(OrgContext*, haxorg_Document const*);
  haxorg_HstdVec (*getProperties_const)(OrgContext*, haxorg_Document, haxorg_HstdStr, haxorg_HstdOpt);
  haxorg_HstdOpt (*getProperty_const)(OrgContext*, haxorg_Document, haxorg_HstdStr, haxorg_HstdOpt);
};

struct haxorg_FileTarget_vtable {
  haxorg_HstdStr const* (*get_path)(OrgContext*, haxorg_FileTarget const*);
  haxorg_HstdOpt const* (*get_line)(OrgContext*, haxorg_FileTarget const*);
  haxorg_HstdOpt const* (*get_searchTarget)(OrgContext*, haxorg_FileTarget const*);
  bool const* (*get_restrictToHeadlines)(OrgContext*, haxorg_FileTarget const*);
  haxorg_HstdOpt const* (*get_targetId)(OrgContext*, haxorg_FileTarget const*);
  haxorg_HstdOpt const* (*get_regexp)(OrgContext*, haxorg_FileTarget const*);
};

struct haxorg_File_vtable {
  haxorg_HstdStr const* (*get_relPath)(OrgContext*, haxorg_File const*);
  haxorg_HstdStr const* (*get_absPath)(OrgContext*, haxorg_File const*);
  bool (*isDocument_const)(OrgContext*, haxorg_File);
  haxorg_FileDocument (*getDocumentConst_const)(OrgContext*, haxorg_File);
  haxorg_FileDocument (*getDocumentMut)(OrgContext*, haxorg_File);
  bool (*isAttachment_const)(OrgContext*, haxorg_File);
  haxorg_FileAttachment (*getAttachmentConst_const)(OrgContext*, haxorg_File);
  haxorg_FileAttachment (*getAttachmentMut)(OrgContext*, haxorg_File);
  bool (*isSource_const)(OrgContext*, haxorg_File);
  haxorg_FileSource (*getSourceConst_const)(OrgContext*, haxorg_File);
  haxorg_FileSource (*getSourceMut)(OrgContext*, haxorg_File);
  haxorg_FileKind (*getFileKind_const)(OrgContext*, haxorg_File);
};

struct haxorg_Directory_vtable {
  haxorg_HstdStr const* (*get_relPath)(OrgContext*, haxorg_Directory const*);
  haxorg_HstdStr const* (*get_absPath)(OrgContext*, haxorg_Directory const*);
};

struct haxorg_Symlink_vtable {
  bool const* (*get_isDirectory)(OrgContext*, haxorg_Symlink const*);
  haxorg_HstdStr const* (*get_absPath)(OrgContext*, haxorg_Symlink const*);
};

struct haxorg_CmdIncludeIncludeBase_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_CmdIncludeIncludeBase, haxorg_CmdIncludeIncludeBase);
};

struct haxorg_CmdIncludeExample_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_CmdIncludeExample, haxorg_CmdIncludeExample);
};

struct haxorg_CmdIncludeExport_vtable {
  haxorg_HstdStr const* (*get_language)(OrgContext*, haxorg_CmdIncludeExport const*);
  bool (*__eq___const)(OrgContext*, haxorg_CmdIncludeExport, haxorg_CmdIncludeExport);
};

struct haxorg_CmdIncludeCustom_vtable {
  haxorg_HstdStr const* (*get_blockName)(OrgContext*, haxorg_CmdIncludeCustom const*);
  bool (*__eq___const)(OrgContext*, haxorg_CmdIncludeCustom, haxorg_CmdIncludeCustom);
};

struct haxorg_CmdIncludeSrc_vtable {
  haxorg_HstdStr const* (*get_language)(OrgContext*, haxorg_CmdIncludeSrc const*);
  bool (*__eq___const)(OrgContext*, haxorg_CmdIncludeSrc, haxorg_CmdIncludeSrc);
};

struct haxorg_CmdIncludeOrgDocument_vtable {
  haxorg_HstdOpt const* (*get_onlyContent)(OrgContext*, haxorg_CmdIncludeOrgDocument const*);
  haxorg_HstdOpt const* (*get_subtreePath)(OrgContext*, haxorg_CmdIncludeOrgDocument const*);
  haxorg_HstdOpt const* (*get_minLevel)(OrgContext*, haxorg_CmdIncludeOrgDocument const*);
  haxorg_HstdOpt const* (*get_customIdTarget)(OrgContext*, haxorg_CmdIncludeOrgDocument const*);
  bool (*__eq___const)(OrgContext*, haxorg_CmdIncludeOrgDocument, haxorg_CmdIncludeOrgDocument);
};

struct haxorg_CmdInclude_vtable {
  haxorg_HstdStr const* (*get_path)(OrgContext*, haxorg_CmdInclude const*);
  haxorg_HstdOpt const* (*get_firstLine)(OrgContext*, haxorg_CmdInclude const*);
  haxorg_HstdOpt const* (*get_lastLine)(OrgContext*, haxorg_CmdInclude const*);
  bool (*isExample_const)(OrgContext*, haxorg_CmdInclude);
  haxorg_CmdIncludeExample (*getExampleConst_const)(OrgContext*, haxorg_CmdInclude);
  haxorg_CmdIncludeExample (*getExampleMut)(OrgContext*, haxorg_CmdInclude);
  bool (*isExport_const)(OrgContext*, haxorg_CmdInclude);
  haxorg_CmdIncludeExport (*getExportConst_const)(OrgContext*, haxorg_CmdInclude);
  haxorg_CmdIncludeExport (*getExportMut)(OrgContext*, haxorg_CmdInclude);
  bool (*isCustom_const)(OrgContext*, haxorg_CmdInclude);
  haxorg_CmdIncludeCustom (*getCustomConst_const)(OrgContext*, haxorg_CmdInclude);
  haxorg_CmdIncludeCustom (*getCustomMut)(OrgContext*, haxorg_CmdInclude);
  bool (*isSrc_const)(OrgContext*, haxorg_CmdInclude);
  haxorg_CmdIncludeSrc (*getSrcConst_const)(OrgContext*, haxorg_CmdInclude);
  haxorg_CmdIncludeSrc (*getSrcMut)(OrgContext*, haxorg_CmdInclude);
  bool (*isOrgDocument_const)(OrgContext*, haxorg_CmdInclude);
  haxorg_CmdIncludeOrgDocument (*getOrgDocumentConst_const)(OrgContext*, haxorg_CmdInclude);
  haxorg_CmdIncludeOrgDocument (*getOrgDocumentMut)(OrgContext*, haxorg_CmdInclude);
  haxorg_CmdIncludeKind (*getIncludeKind_const)(OrgContext*, haxorg_CmdInclude);
};

struct haxorg_ImmNoNode_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmNoNode, haxorg_ImmNoNode);
};

struct haxorg_ImmErrorItem_vtable {
  haxorg_OrgDiagnostics const* (*get_diag)(OrgContext*, haxorg_ImmErrorItem const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmErrorItem, haxorg_ImmErrorItem);
};

struct haxorg_ImmErrorGroup_vtable {
  haxorg_ImmVec const* (*get_diagnostics)(OrgContext*, haxorg_ImmErrorGroup const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmErrorGroup, haxorg_ImmErrorGroup);
};

struct haxorg_ImmStmt_vtable {
  haxorg_ImmVec const* (*get_attached)(OrgContext*, haxorg_ImmStmt const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmStmt, haxorg_ImmStmt);
};

struct haxorg_ImmInline_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmInline, haxorg_ImmInline);
};

struct haxorg_ImmStmtList_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmStmtList, haxorg_ImmStmtList);
};

struct haxorg_ImmEmpty_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmEmpty, haxorg_ImmEmpty);
};

struct haxorg_ImmLeaf_vtable {
  haxorg_HstdStr const* (*get_text)(OrgContext*, haxorg_ImmLeaf const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmLeaf, haxorg_ImmLeaf);
};

struct haxorg_ImmTimeRepeat_vtable {
  haxorg_ImmTimeRepeatMode const* (*get_mode)(OrgContext*, haxorg_ImmTimeRepeat const*);
  haxorg_ImmTimeRepeatPeriod const* (*get_period)(OrgContext*, haxorg_ImmTimeRepeat const*);
  int const* (*get_count)(OrgContext*, haxorg_ImmTimeRepeat const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmTimeRepeat, haxorg_ImmTimeRepeat);
};

struct haxorg_ImmTimeStatic_vtable {
  haxorg_ImmVec const* (*get_repeat)(OrgContext*, haxorg_ImmTimeStatic const*);
  haxorg_HstdOpt const* (*get_warn)(OrgContext*, haxorg_ImmTimeStatic const*);
  haxorg_UserTime const* (*get_time)(OrgContext*, haxorg_ImmTimeStatic const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmTimeStatic, haxorg_ImmTimeStatic);
};

struct haxorg_ImmTimeDynamic_vtable {
  haxorg_LispCode const* (*get_expr)(OrgContext*, haxorg_ImmTimeDynamic const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmTimeDynamic, haxorg_ImmTimeDynamic);
};

struct haxorg_ImmTime_vtable {
  bool const* (*get_isActive)(OrgContext*, haxorg_ImmTime const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmTime, haxorg_ImmTime);
  bool (*isStatic_const)(OrgContext*, haxorg_ImmTime);
  haxorg_ImmTimeStatic (*getStaticConst_const)(OrgContext*, haxorg_ImmTime);
  haxorg_ImmTimeStatic (*getStaticMut)(OrgContext*, haxorg_ImmTime);
  bool (*isDynamic_const)(OrgContext*, haxorg_ImmTime);
  haxorg_ImmTimeDynamic (*getDynamicConst_const)(OrgContext*, haxorg_ImmTime);
  haxorg_ImmTimeDynamic (*getDynamicMut)(OrgContext*, haxorg_ImmTime);
  haxorg_ImmTimeTimeKind (*getTimeKind_const)(OrgContext*, haxorg_ImmTime);
};

struct haxorg_ImmTimeRange_vtable {
  haxorg_ImmId const* (*get_from)(OrgContext*, haxorg_ImmTimeRange const*);
  haxorg_ImmId const* (*get_to)(OrgContext*, haxorg_ImmTimeRange const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmTimeRange, haxorg_ImmTimeRange);
};

struct haxorg_ImmMacro_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_ImmMacro const*);
  haxorg_AttrGroup const* (*get_attrs)(OrgContext*, haxorg_ImmMacro const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmMacro, haxorg_ImmMacro);
};

struct haxorg_ImmSymbolParam_vtable {
  haxorg_HstdOpt const* (*get_key)(OrgContext*, haxorg_ImmSymbolParam const*);
  haxorg_HstdStr const* (*get_value)(OrgContext*, haxorg_ImmSymbolParam const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmSymbolParam, haxorg_ImmSymbolParam);
};

struct haxorg_ImmSymbol_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_ImmSymbol const*);
  haxorg_ImmVec const* (*get_parameters)(OrgContext*, haxorg_ImmSymbol const*);
  haxorg_ImmVec const* (*get_positional)(OrgContext*, haxorg_ImmSymbol const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmSymbol, haxorg_ImmSymbol);
};

struct haxorg_ImmErrorSkipGroup_vtable {
  haxorg_ImmVec const* (*get_skipped)(OrgContext*, haxorg_ImmErrorSkipGroup const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmErrorSkipGroup, haxorg_ImmErrorSkipGroup);
};

struct haxorg_ImmMarkup_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmMarkup, haxorg_ImmMarkup);
};

struct haxorg_ImmRadioTarget_vtable {
  haxorg_ImmVec const* (*get_words)(OrgContext*, haxorg_ImmRadioTarget const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmRadioTarget, haxorg_ImmRadioTarget);
};

struct haxorg_ImmLatex_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmLatex, haxorg_ImmLatex);
};

struct haxorg_ImmSubtreeLog_vtable {
  haxorg_SubtreeLogHead const* (*get_head)(OrgContext*, haxorg_ImmSubtreeLog const*);
  haxorg_HstdOpt const* (*get_desc)(OrgContext*, haxorg_ImmSubtreeLog const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmSubtreeLog, haxorg_ImmSubtreeLog);
};

struct haxorg_ImmSubtree_vtable {
  int const* (*get_level)(OrgContext*, haxorg_ImmSubtree const*);
  haxorg_HstdOpt const* (*get_treeId)(OrgContext*, haxorg_ImmSubtree const*);
  haxorg_HstdOpt const* (*get_todo)(OrgContext*, haxorg_ImmSubtree const*);
  haxorg_HstdOpt const* (*get_completion)(OrgContext*, haxorg_ImmSubtree const*);
  haxorg_HstdOpt const* (*get_description)(OrgContext*, haxorg_ImmSubtree const*);
  haxorg_ImmVec const* (*get_tags)(OrgContext*, haxorg_ImmSubtree const*);
  haxorg_ImmId const* (*get_title)(OrgContext*, haxorg_ImmSubtree const*);
  haxorg_ImmVec const* (*get_logbook)(OrgContext*, haxorg_ImmSubtree const*);
  haxorg_ImmVec const* (*get_properties)(OrgContext*, haxorg_ImmSubtree const*);
  haxorg_HstdOpt const* (*get_closed)(OrgContext*, haxorg_ImmSubtree const*);
  haxorg_HstdOpt const* (*get_deadline)(OrgContext*, haxorg_ImmSubtree const*);
  haxorg_HstdOpt const* (*get_scheduled)(OrgContext*, haxorg_ImmSubtree const*);
  bool const* (*get_isComment)(OrgContext*, haxorg_ImmSubtree const*);
  bool const* (*get_isArchived)(OrgContext*, haxorg_ImmSubtree const*);
  haxorg_HstdOpt const* (*get_priority)(OrgContext*, haxorg_ImmSubtree const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmSubtree, haxorg_ImmSubtree);
};

struct haxorg_ImmColonExample_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmColonExample, haxorg_ImmColonExample);
};

struct haxorg_ImmCall_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_ImmCall const*);
  haxorg_AttrGroup const* (*get_attrs)(OrgContext*, haxorg_ImmCall const*);
  bool const* (*get_isCommand)(OrgContext*, haxorg_ImmCall const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmCall, haxorg_ImmCall);
};

struct haxorg_ImmListItem_vtable {
  haxorg_CheckboxState const* (*get_checkbox)(OrgContext*, haxorg_ImmListItem const*);
  haxorg_HstdOpt const* (*get_header)(OrgContext*, haxorg_ImmListItem const*);
  haxorg_HstdOpt const* (*get_bullet)(OrgContext*, haxorg_ImmListItem const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmListItem, haxorg_ImmListItem);
};

struct haxorg_ImmDocumentOptions_vtable {
  haxorg_InitialSubtreeVisibility const* (*get_initialVisibility)(OrgContext*, haxorg_ImmDocumentOptions const*);
  haxorg_ImmVec const* (*get_properties)(OrgContext*, haxorg_ImmDocumentOptions const*);
  haxorg_DocumentExportConfig const* (*get_exportConfig)(OrgContext*, haxorg_ImmDocumentOptions const*);
  haxorg_HstdOpt const* (*get_fixedWidthSections)(OrgContext*, haxorg_ImmDocumentOptions const*);
  haxorg_HstdOpt const* (*get_startupIndented)(OrgContext*, haxorg_ImmDocumentOptions const*);
  haxorg_HstdOpt const* (*get_category)(OrgContext*, haxorg_ImmDocumentOptions const*);
  haxorg_HstdOpt const* (*get_setupfile)(OrgContext*, haxorg_ImmDocumentOptions const*);
  haxorg_HstdOpt const* (*get_maxSubtreeLevelExport)(OrgContext*, haxorg_ImmDocumentOptions const*);
  haxorg_HstdOpt const* (*get_columns)(OrgContext*, haxorg_ImmDocumentOptions const*);
  haxorg_ImmVec const* (*get_todoKeywords)(OrgContext*, haxorg_ImmDocumentOptions const*);
  haxorg_ImmVec const* (*get_doneKeywords)(OrgContext*, haxorg_ImmDocumentOptions const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmDocumentOptions, haxorg_ImmDocumentOptions);
};

struct haxorg_ImmDocumentFragment_vtable {
  int const* (*get_baseLine)(OrgContext*, haxorg_ImmDocumentFragment const*);
  int const* (*get_baseCol)(OrgContext*, haxorg_ImmDocumentFragment const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmDocumentFragment, haxorg_ImmDocumentFragment);
};

struct haxorg_ImmCriticMarkup_vtable {
  haxorg_ImmCriticMarkupKind const* (*get_kind)(OrgContext*, haxorg_ImmCriticMarkup const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmCriticMarkup, haxorg_ImmCriticMarkup);
};

struct haxorg_ImmDocument_vtable {
  haxorg_HstdOpt const* (*get_title)(OrgContext*, haxorg_ImmDocument const*);
  haxorg_HstdOpt const* (*get_author)(OrgContext*, haxorg_ImmDocument const*);
  haxorg_HstdOpt const* (*get_creator)(OrgContext*, haxorg_ImmDocument const*);
  haxorg_ImmVec const* (*get_filetags)(OrgContext*, haxorg_ImmDocument const*);
  haxorg_HstdOpt const* (*get_email)(OrgContext*, haxorg_ImmDocument const*);
  haxorg_ImmVec const* (*get_language)(OrgContext*, haxorg_ImmDocument const*);
  haxorg_ImmId const* (*get_options)(OrgContext*, haxorg_ImmDocument const*);
  haxorg_HstdOpt const* (*get_exportFileName)(OrgContext*, haxorg_ImmDocument const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmDocument, haxorg_ImmDocument);
};

struct haxorg_ImmFileTarget_vtable {
  haxorg_HstdStr const* (*get_path)(OrgContext*, haxorg_ImmFileTarget const*);
  haxorg_HstdOpt const* (*get_line)(OrgContext*, haxorg_ImmFileTarget const*);
  haxorg_HstdOpt const* (*get_searchTarget)(OrgContext*, haxorg_ImmFileTarget const*);
  bool const* (*get_restrictToHeadlines)(OrgContext*, haxorg_ImmFileTarget const*);
  haxorg_HstdOpt const* (*get_targetId)(OrgContext*, haxorg_ImmFileTarget const*);
  haxorg_HstdOpt const* (*get_regexp)(OrgContext*, haxorg_ImmFileTarget const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmFileTarget, haxorg_ImmFileTarget);
};

struct haxorg_ImmTextSeparator_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmTextSeparator, haxorg_ImmTextSeparator);
};

struct haxorg_ImmDocumentGroup_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmDocumentGroup, haxorg_ImmDocumentGroup);
};

struct haxorg_ImmFileDocument_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmFileDocument, haxorg_ImmFileDocument);
};

struct haxorg_ImmFileAttachment_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmFileAttachment, haxorg_ImmFileAttachment);
};

struct haxorg_ImmFileSource_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmFileSource, haxorg_ImmFileSource);
};

struct haxorg_ImmFile_vtable {
  haxorg_HstdStr const* (*get_relPath)(OrgContext*, haxorg_ImmFile const*);
  haxorg_HstdStr const* (*get_absPath)(OrgContext*, haxorg_ImmFile const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmFile, haxorg_ImmFile);
  bool (*isDocument_const)(OrgContext*, haxorg_ImmFile);
  haxorg_ImmFileDocument (*getDocumentConst_const)(OrgContext*, haxorg_ImmFile);
  haxorg_ImmFileDocument (*getDocumentMut)(OrgContext*, haxorg_ImmFile);
  bool (*isAttachment_const)(OrgContext*, haxorg_ImmFile);
  haxorg_ImmFileAttachment (*getAttachmentConst_const)(OrgContext*, haxorg_ImmFile);
  haxorg_ImmFileAttachment (*getAttachmentMut)(OrgContext*, haxorg_ImmFile);
  bool (*isSource_const)(OrgContext*, haxorg_ImmFile);
  haxorg_ImmFileSource (*getSourceConst_const)(OrgContext*, haxorg_ImmFile);
  haxorg_ImmFileSource (*getSourceMut)(OrgContext*, haxorg_ImmFile);
  haxorg_ImmFileKind (*getFileKind_const)(OrgContext*, haxorg_ImmFile);
};

struct haxorg_ImmDirectory_vtable {
  haxorg_HstdStr const* (*get_relPath)(OrgContext*, haxorg_ImmDirectory const*);
  haxorg_HstdStr const* (*get_absPath)(OrgContext*, haxorg_ImmDirectory const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmDirectory, haxorg_ImmDirectory);
};

struct haxorg_ImmSymlink_vtable {
  bool const* (*get_isDirectory)(OrgContext*, haxorg_ImmSymlink const*);
  haxorg_HstdStr const* (*get_absPath)(OrgContext*, haxorg_ImmSymlink const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmSymlink, haxorg_ImmSymlink);
};

struct haxorg_ImmCmdIncludeIncludeBase_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmCmdIncludeIncludeBase, haxorg_ImmCmdIncludeIncludeBase);
};

struct haxorg_ImmCmdIncludeExample_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmCmdIncludeExample, haxorg_ImmCmdIncludeExample);
};

struct haxorg_ImmCmdIncludeExport_vtable {
  haxorg_HstdStr const* (*get_language)(OrgContext*, haxorg_ImmCmdIncludeExport const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmCmdIncludeExport, haxorg_ImmCmdIncludeExport);
};

struct haxorg_ImmCmdIncludeCustom_vtable {
  haxorg_HstdStr const* (*get_blockName)(OrgContext*, haxorg_ImmCmdIncludeCustom const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmCmdIncludeCustom, haxorg_ImmCmdIncludeCustom);
};

struct haxorg_ImmCmdIncludeSrc_vtable {
  haxorg_HstdStr const* (*get_language)(OrgContext*, haxorg_ImmCmdIncludeSrc const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmCmdIncludeSrc, haxorg_ImmCmdIncludeSrc);
};

struct haxorg_ImmCmdIncludeOrgDocument_vtable {
  haxorg_HstdOpt const* (*get_onlyContent)(OrgContext*, haxorg_ImmCmdIncludeOrgDocument const*);
  haxorg_HstdOpt const* (*get_subtreePath)(OrgContext*, haxorg_ImmCmdIncludeOrgDocument const*);
  haxorg_HstdOpt const* (*get_minLevel)(OrgContext*, haxorg_ImmCmdIncludeOrgDocument const*);
  haxorg_HstdOpt const* (*get_customIdTarget)(OrgContext*, haxorg_ImmCmdIncludeOrgDocument const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmCmdIncludeOrgDocument, haxorg_ImmCmdIncludeOrgDocument);
};

struct haxorg_ImmCmdInclude_vtable {
  haxorg_HstdStr const* (*get_path)(OrgContext*, haxorg_ImmCmdInclude const*);
  haxorg_HstdOpt const* (*get_firstLine)(OrgContext*, haxorg_ImmCmdInclude const*);
  haxorg_HstdOpt const* (*get_lastLine)(OrgContext*, haxorg_ImmCmdInclude const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmCmdInclude, haxorg_ImmCmdInclude);
  bool (*isExample_const)(OrgContext*, haxorg_ImmCmdInclude);
  haxorg_ImmCmdIncludeExample (*getExampleConst_const)(OrgContext*, haxorg_ImmCmdInclude);
  haxorg_ImmCmdIncludeExample (*getExampleMut)(OrgContext*, haxorg_ImmCmdInclude);
  bool (*isExport_const)(OrgContext*, haxorg_ImmCmdInclude);
  haxorg_ImmCmdIncludeExport (*getExportConst_const)(OrgContext*, haxorg_ImmCmdInclude);
  haxorg_ImmCmdIncludeExport (*getExportMut)(OrgContext*, haxorg_ImmCmdInclude);
  bool (*isCustom_const)(OrgContext*, haxorg_ImmCmdInclude);
  haxorg_ImmCmdIncludeCustom (*getCustomConst_const)(OrgContext*, haxorg_ImmCmdInclude);
  haxorg_ImmCmdIncludeCustom (*getCustomMut)(OrgContext*, haxorg_ImmCmdInclude);
  bool (*isSrc_const)(OrgContext*, haxorg_ImmCmdInclude);
  haxorg_ImmCmdIncludeSrc (*getSrcConst_const)(OrgContext*, haxorg_ImmCmdInclude);
  haxorg_ImmCmdIncludeSrc (*getSrcMut)(OrgContext*, haxorg_ImmCmdInclude);
  bool (*isOrgDocument_const)(OrgContext*, haxorg_ImmCmdInclude);
  haxorg_ImmCmdIncludeOrgDocument (*getOrgDocumentConst_const)(OrgContext*, haxorg_ImmCmdInclude);
  haxorg_ImmCmdIncludeOrgDocument (*getOrgDocumentMut)(OrgContext*, haxorg_ImmCmdInclude);
  haxorg_ImmCmdIncludeKind (*getIncludeKind_const)(OrgContext*, haxorg_ImmCmdInclude);
};

struct haxorg_Cmd_vtable {
  haxorg_AttrGroup const* (*get_attrs)(OrgContext*, haxorg_Cmd const*);
  haxorg_HstdVec (*getAttrs_const)(OrgContext*, haxorg_Cmd, haxorg_HstdOpt);
  haxorg_HstdOpt (*getFirstAttr_const)(OrgContext*, haxorg_Cmd, haxorg_HstdStr);
};

struct haxorg_CmdCustomRaw_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_CmdCustomRaw const*);
  bool const* (*get_isAttached)(OrgContext*, haxorg_CmdCustomRaw const*);
  haxorg_HstdStr const* (*get_text)(OrgContext*, haxorg_CmdCustomRaw const*);
};

struct haxorg_CmdCustomText_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_CmdCustomText const*);
  bool const* (*get_isAttached)(OrgContext*, haxorg_CmdCustomText const*);
  haxorg_SemId const* (*get_text)(OrgContext*, haxorg_CmdCustomText const*);
};

struct haxorg_Link_vtable {
  haxorg_HstdOpt const* (*get_description)(OrgContext*, haxorg_Link const*);
  haxorg_LinkTarget const* (*get_target)(OrgContext*, haxorg_Link const*);
};

struct haxorg_Paragraph_vtable {
  bool (*isFootnoteDefinition_const)(OrgContext*, haxorg_Paragraph);
  haxorg_HstdOpt (*getFootnoteName_const)(OrgContext*, haxorg_Paragraph);
  bool (*hasAdmonition_const)(OrgContext*, haxorg_Paragraph);
  haxorg_HstdVec (*getAdmonitions_const)(OrgContext*, haxorg_Paragraph);
  haxorg_HstdVec (*getAdmonitionNodes_const)(OrgContext*, haxorg_Paragraph);
  bool (*hasTimestamp_const)(OrgContext*, haxorg_Paragraph);
  haxorg_HstdVec (*getTimestamps_const)(OrgContext*, haxorg_Paragraph);
  haxorg_HstdVec (*getTimestampNodes_const)(OrgContext*, haxorg_Paragraph);
  bool (*hasLeadHashtags_const)(OrgContext*, haxorg_Paragraph);
  haxorg_HstdVec (*getLeadHashtags_const)(OrgContext*, haxorg_Paragraph);
  haxorg_HstdVec (*getBody_const)(OrgContext*, haxorg_Paragraph);
};

struct haxorg_List_vtable {
  haxorg_HstdVec (*getListAttrs_const)(OrgContext*, haxorg_List, haxorg_HstdStr);
  haxorg_ListFormattingMode (*getListFormattingMode_const)(OrgContext*, haxorg_List);
  bool (*isDescriptionList_const)(OrgContext*, haxorg_List);
  bool (*isNumberedList_const)(OrgContext*, haxorg_List);
};

struct haxorg_HashTag_vtable {
  haxorg_HashTagText const* (*get_text)(OrgContext*, haxorg_HashTag const*);
};

struct haxorg_InlineFootnote_vtable {
  haxorg_HstdStr const* (*get_tag)(OrgContext*, haxorg_InlineFootnote const*);
  haxorg_HstdOpt const* (*get_definition)(OrgContext*, haxorg_InlineFootnote const*);
};

struct haxorg_InlineExport_vtable {
  haxorg_HstdStr const* (*get_exporter)(OrgContext*, haxorg_InlineExport const*);
  haxorg_HstdStr const* (*get_content)(OrgContext*, haxorg_InlineExport const*);
};

struct haxorg_ImmCmd_vtable {
  haxorg_AttrGroup const* (*get_attrs)(OrgContext*, haxorg_ImmCmd const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmCmd, haxorg_ImmCmd);
};

struct haxorg_ImmCmdCustomRaw_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_ImmCmdCustomRaw const*);
  bool const* (*get_isAttached)(OrgContext*, haxorg_ImmCmdCustomRaw const*);
  haxorg_HstdStr const* (*get_text)(OrgContext*, haxorg_ImmCmdCustomRaw const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmCmdCustomRaw, haxorg_ImmCmdCustomRaw);
};

struct haxorg_ImmCmdCustomText_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_ImmCmdCustomText const*);
  bool const* (*get_isAttached)(OrgContext*, haxorg_ImmCmdCustomText const*);
  haxorg_ImmId const* (*get_text)(OrgContext*, haxorg_ImmCmdCustomText const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmCmdCustomText, haxorg_ImmCmdCustomText);
};

struct haxorg_ImmLink_vtable {
  haxorg_HstdOpt const* (*get_description)(OrgContext*, haxorg_ImmLink const*);
  haxorg_LinkTarget const* (*get_target)(OrgContext*, haxorg_ImmLink const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmLink, haxorg_ImmLink);
};

struct haxorg_ImmBlockComment_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmBlockComment, haxorg_ImmBlockComment);
};

struct haxorg_ImmParagraph_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmParagraph, haxorg_ImmParagraph);
};

struct haxorg_ImmList_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmList, haxorg_ImmList);
};

struct haxorg_ImmHashTag_vtable {
  haxorg_HashTagText const* (*get_text)(OrgContext*, haxorg_ImmHashTag const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmHashTag, haxorg_ImmHashTag);
};

struct haxorg_ImmInlineFootnote_vtable {
  haxorg_HstdStr const* (*get_tag)(OrgContext*, haxorg_ImmInlineFootnote const*);
  haxorg_HstdOpt const* (*get_definition)(OrgContext*, haxorg_ImmInlineFootnote const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmInlineFootnote, haxorg_ImmInlineFootnote);
};

struct haxorg_ImmInlineExport_vtable {
  haxorg_HstdStr const* (*get_exporter)(OrgContext*, haxorg_ImmInlineExport const*);
  haxorg_HstdStr const* (*get_content)(OrgContext*, haxorg_ImmInlineExport const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmInlineExport, haxorg_ImmInlineExport);
};

struct haxorg_ImmEscaped_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmEscaped, haxorg_ImmEscaped);
};

struct haxorg_ImmNewline_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmNewline, haxorg_ImmNewline);
};

struct haxorg_ImmSpace_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmSpace, haxorg_ImmSpace);
};

struct haxorg_ImmWord_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmWord, haxorg_ImmWord);
};

struct haxorg_ImmAtMention_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmAtMention, haxorg_ImmAtMention);
};

struct haxorg_ImmRawText_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmRawText, haxorg_ImmRawText);
};

struct haxorg_ImmPunctuation_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmPunctuation, haxorg_ImmPunctuation);
};

struct haxorg_ImmPlaceholder_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmPlaceholder, haxorg_ImmPlaceholder);
};

struct haxorg_ImmBigIdent_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmBigIdent, haxorg_ImmBigIdent);
};

struct haxorg_ImmTextTarget_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmTextTarget, haxorg_ImmTextTarget);
};

struct haxorg_ImmErrorSkipToken_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmErrorSkipToken, haxorg_ImmErrorSkipToken);
};

struct haxorg_ImmBold_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmBold, haxorg_ImmBold);
};

struct haxorg_ImmUnderline_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmUnderline, haxorg_ImmUnderline);
};

struct haxorg_ImmMonospace_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmMonospace, haxorg_ImmMonospace);
};

struct haxorg_ImmMarkQuote_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmMarkQuote, haxorg_ImmMarkQuote);
};

struct haxorg_ImmVerbatim_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmVerbatim, haxorg_ImmVerbatim);
};

struct haxorg_ImmItalic_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmItalic, haxorg_ImmItalic);
};

struct haxorg_ImmStrike_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmStrike, haxorg_ImmStrike);
};

struct haxorg_ImmPar_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmPar, haxorg_ImmPar);
};

struct haxorg_ImmAdapterDirectoryAPI_vtable {
  haxorg_StdOptional (*getFsSubnode_const)(OrgContext*, haxorg_ImmAdapterDirectoryAPI, haxorg_HstdStr, bool);
};

struct haxorg_CmdCreator_vtable {
  haxorg_SemId const* (*get_text)(OrgContext*, haxorg_CmdCreator const*);
};

struct haxorg_CmdAuthor_vtable {
  haxorg_SemId const* (*get_text)(OrgContext*, haxorg_CmdAuthor const*);
};

struct haxorg_CmdEmail_vtable {
  haxorg_HstdStr const* (*get_text)(OrgContext*, haxorg_CmdEmail const*);
};

struct haxorg_CmdLanguage_vtable {
  haxorg_HstdStr const* (*get_text)(OrgContext*, haxorg_CmdLanguage const*);
};

struct haxorg_CmdCustomArgs_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_CmdCustomArgs const*);
  bool const* (*get_isAttached)(OrgContext*, haxorg_CmdCustomArgs const*);
};

struct haxorg_CmdTblfm_vtable {
  haxorg_Tblfm const* (*get_expr)(OrgContext*, haxorg_CmdTblfm const*);
};

struct haxorg_Cell_vtable {
  bool const* (*get_isBlock)(OrgContext*, haxorg_Cell const*);
};

struct haxorg_Row_vtable {
  haxorg_HstdVec const* (*get_cells)(OrgContext*, haxorg_Row const*);
  bool const* (*get_isBlock)(OrgContext*, haxorg_Row const*);
};

struct haxorg_ImmBlock_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmBlock, haxorg_ImmBlock);
};

struct haxorg_ImmLineCommand_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmLineCommand, haxorg_ImmLineCommand);
};

struct haxorg_ImmCmdCreator_vtable {
  haxorg_ImmId const* (*get_text)(OrgContext*, haxorg_ImmCmdCreator const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmCmdCreator, haxorg_ImmCmdCreator);
};

struct haxorg_ImmCmdAuthor_vtable {
  haxorg_ImmId const* (*get_text)(OrgContext*, haxorg_ImmCmdAuthor const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmCmdAuthor, haxorg_ImmCmdAuthor);
};

struct haxorg_ImmCmdEmail_vtable {
  haxorg_HstdStr const* (*get_text)(OrgContext*, haxorg_ImmCmdEmail const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmCmdEmail, haxorg_ImmCmdEmail);
};

struct haxorg_ImmCmdLanguage_vtable {
  haxorg_HstdStr const* (*get_text)(OrgContext*, haxorg_ImmCmdLanguage const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmCmdLanguage, haxorg_ImmCmdLanguage);
};

struct haxorg_ImmCmdCustomArgs_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_ImmCmdCustomArgs const*);
  bool const* (*get_isAttached)(OrgContext*, haxorg_ImmCmdCustomArgs const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmCmdCustomArgs, haxorg_ImmCmdCustomArgs);
};

struct haxorg_ImmCmdTblfm_vtable {
  haxorg_Tblfm const* (*get_expr)(OrgContext*, haxorg_ImmCmdTblfm const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmCmdTblfm, haxorg_ImmCmdTblfm);
};

struct haxorg_ImmCell_vtable {
  bool const* (*get_isBlock)(OrgContext*, haxorg_ImmCell const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmCell, haxorg_ImmCell);
};

struct haxorg_ImmRow_vtable {
  haxorg_ImmVec const* (*get_cells)(OrgContext*, haxorg_ImmRow const*);
  bool const* (*get_isBlock)(OrgContext*, haxorg_ImmRow const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmRow, haxorg_ImmRow);
};

struct haxorg_ImmStmtAdapter_vtable {
  haxorg_ImmVec (*getAttached_const)(OrgContext*, haxorg_ImmStmtAdapter);
};

struct haxorg_ImmErrorItemAdapter_vtable {
  haxorg_OrgDiagnostics (*getDiag_const)(OrgContext*, haxorg_ImmErrorItemAdapter);
};

struct haxorg_ImmErrorGroupAdapter_vtable {
  haxorg_ImmVec (*getDiagnostics_const)(OrgContext*, haxorg_ImmErrorGroupAdapter);
};

struct haxorg_ImmErrorSkipGroupAdapter_vtable {
  haxorg_ImmVec (*getSkipped_const)(OrgContext*, haxorg_ImmErrorSkipGroupAdapter);
};

struct haxorg_ImmTimeAdapter_vtable {
  bool (*getIsActive_const)(OrgContext*, haxorg_ImmTimeAdapter);
};

struct haxorg_ImmTimeRangeAdapter_vtable {
  haxorg_ImmAdapter (*getFrom_const)(OrgContext*, haxorg_ImmTimeRangeAdapter);
  haxorg_ImmAdapter (*getTo_const)(OrgContext*, haxorg_ImmTimeRangeAdapter);
};

struct haxorg_ImmMacroAdapter_vtable {
  haxorg_HstdStr (*getName_const)(OrgContext*, haxorg_ImmMacroAdapter);
  haxorg_AttrGroup (*getAttrs_const)(OrgContext*, haxorg_ImmMacroAdapter);
};

struct haxorg_ImmSymbolAdapter_vtable {
  haxorg_HstdStr (*getName_const)(OrgContext*, haxorg_ImmSymbolAdapter);
  haxorg_ImmVec (*getParameters_const)(OrgContext*, haxorg_ImmSymbolAdapter);
  haxorg_ImmVec (*getPositional_const)(OrgContext*, haxorg_ImmSymbolAdapter);
};

struct haxorg_ImmLeafAdapter_vtable {
  haxorg_HstdStr (*getText_const)(OrgContext*, haxorg_ImmLeafAdapter);
};

struct haxorg_ImmSubtreeLogAdapter_vtable {
  haxorg_SubtreeLogHead (*getHead_const)(OrgContext*, haxorg_ImmSubtreeLogAdapter);
  haxorg_HstdOpt (*getDesc_const)(OrgContext*, haxorg_ImmSubtreeLogAdapter);
};

struct haxorg_ImmCallAdapter_vtable {
  haxorg_HstdStr (*getName_const)(OrgContext*, haxorg_ImmCallAdapter);
  haxorg_AttrGroup (*getAttrs_const)(OrgContext*, haxorg_ImmCallAdapter);
  bool (*getIsCommand_const)(OrgContext*, haxorg_ImmCallAdapter);
};

struct haxorg_ImmFileAdapter_vtable {
  haxorg_HstdStr (*getRelPath_const)(OrgContext*, haxorg_ImmFileAdapter);
  haxorg_HstdStr (*getAbsPath_const)(OrgContext*, haxorg_ImmFileAdapter);
};

struct haxorg_ImmDirectoryAdapter_vtable {
  haxorg_HstdStr (*getRelPath_const)(OrgContext*, haxorg_ImmDirectoryAdapter);
  haxorg_HstdStr (*getAbsPath_const)(OrgContext*, haxorg_ImmDirectoryAdapter);
};

struct haxorg_ImmSymlinkAdapter_vtable {
  bool (*getIsDirectory_const)(OrgContext*, haxorg_ImmSymlinkAdapter);
  haxorg_HstdStr (*getAbsPath_const)(OrgContext*, haxorg_ImmSymlinkAdapter);
};

struct haxorg_ImmDocumentFragmentAdapter_vtable {
  int (*getBaseLine_const)(OrgContext*, haxorg_ImmDocumentFragmentAdapter);
  int (*getBaseCol_const)(OrgContext*, haxorg_ImmDocumentFragmentAdapter);
};

struct haxorg_ImmCriticMarkupAdapter_vtable {
  haxorg_ImmCriticMarkupKind (*getKind_const)(OrgContext*, haxorg_ImmCriticMarkupAdapter);
};

struct haxorg_ImmListItemAdapter_vtable {
  haxorg_CheckboxState (*getCheckbox_const)(OrgContext*, haxorg_ImmListItemAdapter);
  haxorg_HstdOpt (*getHeader_const)(OrgContext*, haxorg_ImmListItemAdapter);
  haxorg_HstdOpt (*getBullet_const)(OrgContext*, haxorg_ImmListItemAdapter);
};

struct haxorg_ImmDocumentOptionsAdapter_vtable {
  haxorg_InitialSubtreeVisibility (*getInitialVisibility_const)(OrgContext*, haxorg_ImmDocumentOptionsAdapter);
  haxorg_ImmVec (*getProperties_const)(OrgContext*, haxorg_ImmDocumentOptionsAdapter);
  haxorg_DocumentExportConfig (*getExportConfig_const)(OrgContext*, haxorg_ImmDocumentOptionsAdapter);
  haxorg_HstdOpt (*getFixedWidthSections_const)(OrgContext*, haxorg_ImmDocumentOptionsAdapter);
  haxorg_HstdOpt (*getStartupIndented_const)(OrgContext*, haxorg_ImmDocumentOptionsAdapter);
  haxorg_HstdOpt (*getCategory_const)(OrgContext*, haxorg_ImmDocumentOptionsAdapter);
  haxorg_HstdOpt (*getSetupfile_const)(OrgContext*, haxorg_ImmDocumentOptionsAdapter);
  haxorg_HstdOpt (*getMaxSubtreeLevelExport_const)(OrgContext*, haxorg_ImmDocumentOptionsAdapter);
  haxorg_HstdOpt (*getColumns_const)(OrgContext*, haxorg_ImmDocumentOptionsAdapter);
  haxorg_ImmVec (*getTodoKeywords_const)(OrgContext*, haxorg_ImmDocumentOptionsAdapter);
  haxorg_ImmVec (*getDoneKeywords_const)(OrgContext*, haxorg_ImmDocumentOptionsAdapter);
};

struct haxorg_ImmDocumentAdapter_vtable {
  haxorg_HstdOpt (*getTitle_const)(OrgContext*, haxorg_ImmDocumentAdapter);
  haxorg_HstdOpt (*getAuthor_const)(OrgContext*, haxorg_ImmDocumentAdapter);
  haxorg_HstdOpt (*getCreator_const)(OrgContext*, haxorg_ImmDocumentAdapter);
  haxorg_ImmVec (*getFiletags_const)(OrgContext*, haxorg_ImmDocumentAdapter);
  haxorg_HstdOpt (*getEmail_const)(OrgContext*, haxorg_ImmDocumentAdapter);
  haxorg_ImmVec (*getLanguage_const)(OrgContext*, haxorg_ImmDocumentAdapter);
  haxorg_ImmAdapter (*getOptions_const)(OrgContext*, haxorg_ImmDocumentAdapter);
  haxorg_HstdOpt (*getExportFileName_const)(OrgContext*, haxorg_ImmDocumentAdapter);
};

struct haxorg_ImmFileTargetAdapter_vtable {
  haxorg_HstdStr (*getPath_const)(OrgContext*, haxorg_ImmFileTargetAdapter);
  haxorg_HstdOpt (*getLine_const)(OrgContext*, haxorg_ImmFileTargetAdapter);
  haxorg_HstdOpt (*getSearchTarget_const)(OrgContext*, haxorg_ImmFileTargetAdapter);
  bool (*getRestrictToHeadlines_const)(OrgContext*, haxorg_ImmFileTargetAdapter);
  haxorg_HstdOpt (*getTargetId_const)(OrgContext*, haxorg_ImmFileTargetAdapter);
  haxorg_HstdOpt (*getRegexp_const)(OrgContext*, haxorg_ImmFileTargetAdapter);
};

struct haxorg_ImmCmdIncludeAdapter_vtable {
  haxorg_HstdStr (*getPath_const)(OrgContext*, haxorg_ImmCmdIncludeAdapter);
  haxorg_HstdOpt (*getFirstLine_const)(OrgContext*, haxorg_ImmCmdIncludeAdapter);
  haxorg_HstdOpt (*getLastLine_const)(OrgContext*, haxorg_ImmCmdIncludeAdapter);
};

struct haxorg_BlockDynamicFallback_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_BlockDynamicFallback const*);
};

struct haxorg_BlockExport_vtable {
  haxorg_HstdStr const* (*get_exporter)(OrgContext*, haxorg_BlockExport const*);
  haxorg_HstdStr const* (*get_content)(OrgContext*, haxorg_BlockExport const*);
  haxorg_HstdOpt (*getPlacement_const)(OrgContext*, haxorg_BlockExport);
};

struct haxorg_BlockCodeEvalResult_vtable {
  haxorg_HstdVec const* (*get_raw)(OrgContext*, haxorg_BlockCodeEvalResult const*);
  haxorg_SemId const* (*get_node)(OrgContext*, haxorg_BlockCodeEvalResult const*);
};

struct haxorg_BlockCode_vtable {
  haxorg_HstdOpt const* (*get_lang)(OrgContext*, haxorg_BlockCode const*);
  haxorg_HstdVec const* (*get_result)(OrgContext*, haxorg_BlockCode const*);
  haxorg_HstdVec const* (*get_lines)(OrgContext*, haxorg_BlockCode const*);
  haxorg_AttrGroup const* (*get_switches)(OrgContext*, haxorg_BlockCode const*);
  haxorg_HstdOpt (*getVariable_const)(OrgContext*, haxorg_BlockCode, haxorg_HstdStr);
};

struct haxorg_Table_vtable {
  haxorg_HstdVec const* (*get_rows)(OrgContext*, haxorg_Table const*);
  bool const* (*get_isBlock)(OrgContext*, haxorg_Table const*);
};

struct haxorg_ImmBlockCenter_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmBlockCenter, haxorg_ImmBlockCenter);
};

struct haxorg_ImmBlockQuote_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmBlockQuote, haxorg_ImmBlockQuote);
};

struct haxorg_ImmBlockVerse_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmBlockVerse, haxorg_ImmBlockVerse);
};

struct haxorg_ImmBlockDynamicFallback_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_ImmBlockDynamicFallback const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmBlockDynamicFallback, haxorg_ImmBlockDynamicFallback);
};

struct haxorg_ImmBlockExample_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmBlockExample, haxorg_ImmBlockExample);
};

struct haxorg_ImmBlockExport_vtable {
  haxorg_HstdStr const* (*get_exporter)(OrgContext*, haxorg_ImmBlockExport const*);
  haxorg_HstdStr const* (*get_content)(OrgContext*, haxorg_ImmBlockExport const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmBlockExport, haxorg_ImmBlockExport);
};

struct haxorg_ImmBlockAdmonition_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmBlockAdmonition, haxorg_ImmBlockAdmonition);
};

struct haxorg_ImmBlockCodeEvalResult_vtable {
  haxorg_ImmVec const* (*get_raw)(OrgContext*, haxorg_ImmBlockCodeEvalResult const*);
  haxorg_ImmId const* (*get_node)(OrgContext*, haxorg_ImmBlockCodeEvalResult const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmBlockCodeEvalResult, haxorg_ImmBlockCodeEvalResult);
};

struct haxorg_ImmBlockCode_vtable {
  haxorg_HstdOpt const* (*get_lang)(OrgContext*, haxorg_ImmBlockCode const*);
  haxorg_ImmVec const* (*get_result)(OrgContext*, haxorg_ImmBlockCode const*);
  haxorg_ImmVec const* (*get_lines)(OrgContext*, haxorg_ImmBlockCode const*);
  haxorg_AttrGroup const* (*get_switches)(OrgContext*, haxorg_ImmBlockCode const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmBlockCode, haxorg_ImmBlockCode);
};

struct haxorg_ImmTable_vtable {
  haxorg_ImmVec const* (*get_rows)(OrgContext*, haxorg_ImmTable const*);
  bool const* (*get_isBlock)(OrgContext*, haxorg_ImmTable const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmTable, haxorg_ImmTable);
};

struct haxorg_ImmAttached_vtable {
  bool (*__eq___const)(OrgContext*, haxorg_ImmAttached, haxorg_ImmAttached);
};

struct haxorg_ImmCmdAdapter_vtable {
  haxorg_AttrGroup (*getAttrs_const)(OrgContext*, haxorg_ImmCmdAdapter);
};

struct haxorg_ImmCmdCustomRawAdapter_vtable {
  haxorg_HstdStr (*getName_const)(OrgContext*, haxorg_ImmCmdCustomRawAdapter);
  bool (*getIsAttached_const)(OrgContext*, haxorg_ImmCmdCustomRawAdapter);
  haxorg_HstdStr (*getText_const)(OrgContext*, haxorg_ImmCmdCustomRawAdapter);
};

struct haxorg_ImmCmdCustomTextAdapter_vtable {
  haxorg_HstdStr (*getName_const)(OrgContext*, haxorg_ImmCmdCustomTextAdapter);
  bool (*getIsAttached_const)(OrgContext*, haxorg_ImmCmdCustomTextAdapter);
  haxorg_ImmAdapter (*getText_const)(OrgContext*, haxorg_ImmCmdCustomTextAdapter);
};

struct haxorg_ImmHashTagAdapter_vtable {
  haxorg_HashTagText (*getText_const)(OrgContext*, haxorg_ImmHashTagAdapter);
};

struct haxorg_ImmInlineFootnoteAdapter_vtable {
  haxorg_HstdStr (*getTag_const)(OrgContext*, haxorg_ImmInlineFootnoteAdapter);
  haxorg_HstdOpt (*getDefinition_const)(OrgContext*, haxorg_ImmInlineFootnoteAdapter);
};

struct haxorg_ImmRadioTargetAdapter_vtable {
  haxorg_ImmVec (*getWords_const)(OrgContext*, haxorg_ImmRadioTargetAdapter);
};

struct haxorg_CmdCaption_vtable {
  haxorg_SemId const* (*get_text)(OrgContext*, haxorg_CmdCaption const*);
};

struct haxorg_CmdColumns_vtable {
  haxorg_ColumnView const* (*get_view)(OrgContext*, haxorg_CmdColumns const*);
};

struct haxorg_CmdName_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_CmdName const*);
};

struct haxorg_CmdCall_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_CmdCall const*);
  haxorg_HstdOpt const* (*get_fileName)(OrgContext*, haxorg_CmdCall const*);
  haxorg_AttrGroup const* (*get_insideHeaderAttrs)(OrgContext*, haxorg_CmdCall const*);
  haxorg_AttrGroup const* (*get_callAttrs)(OrgContext*, haxorg_CmdCall const*);
  haxorg_AttrGroup const* (*get_endHeaderAttrs)(OrgContext*, haxorg_CmdCall const*);
  haxorg_HstdVec const* (*get_result)(OrgContext*, haxorg_CmdCall const*);
};

struct haxorg_CmdAttr_vtable {
  haxorg_HstdStr const* (*get_target)(OrgContext*, haxorg_CmdAttr const*);
};

struct haxorg_CmdExport_vtable {
  haxorg_HstdStr const* (*get_exporter)(OrgContext*, haxorg_CmdExport const*);
  haxorg_HstdStr const* (*get_content)(OrgContext*, haxorg_CmdExport const*);
};

struct haxorg_ImmCmdCaption_vtable {
  haxorg_ImmId const* (*get_text)(OrgContext*, haxorg_ImmCmdCaption const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmCmdCaption, haxorg_ImmCmdCaption);
};

struct haxorg_ImmCmdColumns_vtable {
  haxorg_ColumnView const* (*get_view)(OrgContext*, haxorg_ImmCmdColumns const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmCmdColumns, haxorg_ImmCmdColumns);
};

struct haxorg_ImmCmdName_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_ImmCmdName const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmCmdName, haxorg_ImmCmdName);
};

struct haxorg_ImmCmdCall_vtable {
  haxorg_HstdStr const* (*get_name)(OrgContext*, haxorg_ImmCmdCall const*);
  haxorg_HstdOpt const* (*get_fileName)(OrgContext*, haxorg_ImmCmdCall const*);
  haxorg_AttrGroup const* (*get_insideHeaderAttrs)(OrgContext*, haxorg_ImmCmdCall const*);
  haxorg_AttrGroup const* (*get_callAttrs)(OrgContext*, haxorg_ImmCmdCall const*);
  haxorg_AttrGroup const* (*get_endHeaderAttrs)(OrgContext*, haxorg_ImmCmdCall const*);
  haxorg_ImmVec const* (*get_result)(OrgContext*, haxorg_ImmCmdCall const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmCmdCall, haxorg_ImmCmdCall);
};

struct haxorg_ImmCmdAttr_vtable {
  haxorg_HstdStr const* (*get_target)(OrgContext*, haxorg_ImmCmdAttr const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmCmdAttr, haxorg_ImmCmdAttr);
};

struct haxorg_ImmCmdExport_vtable {
  haxorg_HstdStr const* (*get_exporter)(OrgContext*, haxorg_ImmCmdExport const*);
  haxorg_HstdStr const* (*get_content)(OrgContext*, haxorg_ImmCmdExport const*);
  bool (*__eq___const)(OrgContext*, haxorg_ImmCmdExport, haxorg_ImmCmdExport);
};

struct haxorg_ImmCmdCustomArgsAdapter_vtable {
  haxorg_HstdStr (*getName_const)(OrgContext*, haxorg_ImmCmdCustomArgsAdapter);
  bool (*getIsAttached_const)(OrgContext*, haxorg_ImmCmdCustomArgsAdapter);
};

struct haxorg_ImmCmdCreatorAdapter_vtable {
  haxorg_ImmAdapter (*getText_const)(OrgContext*, haxorg_ImmCmdCreatorAdapter);
};

struct haxorg_ImmCmdAuthorAdapter_vtable {
  haxorg_ImmAdapter (*getText_const)(OrgContext*, haxorg_ImmCmdAuthorAdapter);
};

struct haxorg_ImmCmdEmailAdapter_vtable {
  haxorg_HstdStr (*getText_const)(OrgContext*, haxorg_ImmCmdEmailAdapter);
};

struct haxorg_ImmCmdLanguageAdapter_vtable {
  haxorg_HstdStr (*getText_const)(OrgContext*, haxorg_ImmCmdLanguageAdapter);
};

struct haxorg_ImmCmdTblfmAdapter_vtable {
  haxorg_Tblfm (*getExpr_const)(OrgContext*, haxorg_ImmCmdTblfmAdapter);
};

struct haxorg_ImmCellAdapter_vtable {
  bool (*getIsBlock_const)(OrgContext*, haxorg_ImmCellAdapter);
};

struct haxorg_ImmRowAdapter_vtable {
  haxorg_ImmVec (*getCells_const)(OrgContext*, haxorg_ImmRowAdapter);
  bool (*getIsBlock_const)(OrgContext*, haxorg_ImmRowAdapter);
};

struct haxorg_ImmInlineExportAdapter_vtable {
  haxorg_HstdStr (*getExporter_const)(OrgContext*, haxorg_ImmInlineExportAdapter);
  haxorg_HstdStr (*getContent_const)(OrgContext*, haxorg_ImmInlineExportAdapter);
};

struct haxorg_ImmCmdExportAdapter_vtable {
  haxorg_HstdStr (*getExporter_const)(OrgContext*, haxorg_ImmCmdExportAdapter);
  haxorg_HstdStr (*getContent_const)(OrgContext*, haxorg_ImmCmdExportAdapter);
};

struct haxorg_ImmBlockExportAdapter_vtable {
  haxorg_HstdStr (*getExporter_const)(OrgContext*, haxorg_ImmBlockExportAdapter);
  haxorg_HstdStr (*getContent_const)(OrgContext*, haxorg_ImmBlockExportAdapter);
};

struct haxorg_ImmBlockDynamicFallbackAdapter_vtable {
  haxorg_HstdStr (*getName_const)(OrgContext*, haxorg_ImmBlockDynamicFallbackAdapter);
};

struct haxorg_ImmBlockCodeEvalResultAdapter_vtable {
  haxorg_ImmVec (*getRaw_const)(OrgContext*, haxorg_ImmBlockCodeEvalResultAdapter);
  haxorg_ImmAdapter (*getNode_const)(OrgContext*, haxorg_ImmBlockCodeEvalResultAdapter);
};

struct haxorg_ImmBlockCodeAdapter_vtable {
  haxorg_HstdOpt (*getLang_const)(OrgContext*, haxorg_ImmBlockCodeAdapter);
  haxorg_ImmVec (*getResult_const)(OrgContext*, haxorg_ImmBlockCodeAdapter);
  haxorg_ImmVec (*getLines_const)(OrgContext*, haxorg_ImmBlockCodeAdapter);
  haxorg_AttrGroup (*getSwitches_const)(OrgContext*, haxorg_ImmBlockCodeAdapter);
};

struct haxorg_ImmTableAdapter_vtable {
  haxorg_ImmVec (*getRows_const)(OrgContext*, haxorg_ImmTableAdapter);
  bool (*getIsBlock_const)(OrgContext*, haxorg_ImmTableAdapter);
};

struct haxorg_ImmCmdCaptionAdapter_vtable {
  haxorg_ImmAdapter (*getText_const)(OrgContext*, haxorg_ImmCmdCaptionAdapter);
};

struct haxorg_ImmCmdColumnsAdapter_vtable {
  haxorg_ColumnView (*getView_const)(OrgContext*, haxorg_ImmCmdColumnsAdapter);
};

struct haxorg_ImmCmdNameAdapter_vtable {
  haxorg_HstdStr (*getName_const)(OrgContext*, haxorg_ImmCmdNameAdapter);
};

struct haxorg_ImmCmdCallAdapter_vtable {
  haxorg_HstdStr (*getName_const)(OrgContext*, haxorg_ImmCmdCallAdapter);
  haxorg_HstdOpt (*getFileName_const)(OrgContext*, haxorg_ImmCmdCallAdapter);
  haxorg_AttrGroup (*getInsideHeaderAttrs_const)(OrgContext*, haxorg_ImmCmdCallAdapter);
  haxorg_AttrGroup (*getCallAttrs_const)(OrgContext*, haxorg_ImmCmdCallAdapter);
  haxorg_AttrGroup (*getEndHeaderAttrs_const)(OrgContext*, haxorg_ImmCmdCallAdapter);
  haxorg_ImmVec (*getResult_const)(OrgContext*, haxorg_ImmCmdCallAdapter);
};

struct haxorg_ImmCmdAttrAdapter_vtable {
  haxorg_HstdStr (*getTarget_const)(OrgContext*, haxorg_ImmCmdAttrAdapter);
};

HAXORG_C_API_LINKAGE void haxorg_destroy_UserTimeBreakdown(haxorg_UserTimeBreakdown* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_UserTime(haxorg_UserTime* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ParseSourceFileId(haxorg_ParseSourceFileId* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ParseSourceManager(haxorg_ParseSourceManager* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ParseSourceLoc(haxorg_ParseSourceLoc* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_OrgJson(haxorg_OrgJson* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Org(haxorg_Org* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_OperationsTracer(haxorg_OperationsTracer* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Cache(haxorg_Cache* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ParseOrgParseFragment(haxorg_ParseOrgParseFragment* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_OrgParseParameters(haxorg_OrgParseParameters* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_OrgDirectoryParseParameters(haxorg_OrgDirectoryParseParameters* obj);
HAXORG_C_API_LINKAGE haxorg_ParseContext haxorg_create_ParseContext_ParseContextDefault(OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_ParseContext haxorg_create_ParseContext_ParseContextWithManager(OrgContext* org_context, haxorg_ParseSourceManager source);
HAXORG_C_API_LINKAGE void haxorg_destroy_ParseContext(haxorg_ParseContext* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmReflFieldId(haxorg_ImmReflFieldId* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmId(haxorg_ImmId* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmOrg(haxorg_ImmOrg* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmPathStep(haxorg_ImmPathStep* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmPath(haxorg_ImmPath* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmUniqId(haxorg_ImmUniqId* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAstReplaceEpoch(haxorg_ImmAstReplaceEpoch* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAstContext(haxorg_ImmAstContext* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAstVersion(haxorg_ImmAstVersion* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterTreeReprConf(haxorg_ImmAdapterTreeReprConf* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapter(haxorg_ImmAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterVirtualBase(haxorg_ImmAdapterVirtualBase* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_OrgYamlExportOpts(haxorg_OrgYamlExportOpts* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_OrgTreeExportOpts(haxorg_OrgTreeExportOpts* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_AstTrackingPath(haxorg_AstTrackingPath* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_AstTrackingAlternatives(haxorg_AstTrackingAlternatives* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_AstTrackingGroupRadioTarget(haxorg_AstTrackingGroupRadioTarget* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_AstTrackingGroupSingle(haxorg_AstTrackingGroupSingle* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_AstTrackingGroupTrackedHashtag(haxorg_AstTrackingGroupTrackedHashtag* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_AstTrackingGroup(haxorg_AstTrackingGroup* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_AstTrackingMap(haxorg_AstTrackingMap* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_SequenceSegment(haxorg_SequenceSegment* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_SequenceSegmentGroup(haxorg_SequenceSegmentGroup* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_SequenceAnnotationTag(haxorg_SequenceAnnotationTag* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_SequenceAnnotation(haxorg_SequenceAnnotation* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_GraphMapLinkLink(haxorg_GraphMapLinkLink* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_GraphMapLinkRadio(haxorg_GraphMapLinkRadio* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_GraphMapLink(haxorg_GraphMapLink* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_GraphMapNodeProp(haxorg_GraphMapNodeProp* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_GraphMapEdgeProp(haxorg_GraphMapEdgeProp* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_GraphMapNode(haxorg_GraphMapNode* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_GraphMapEdge(haxorg_GraphMapEdge* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_GraphMapGraph(haxorg_GraphMapGraph* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_GraphMapConfig(haxorg_GraphMapConfig* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_GraphMapGraphState(haxorg_GraphMapGraphState* obj);
HAXORG_C_API_LINKAGE void haxorg_create_LispCode_LispCode(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_create_LispCodeCall_Call(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_LispCodeCall(haxorg_LispCodeCall* obj);
HAXORG_C_API_LINKAGE void haxorg_create_LispCodeList_List(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_LispCodeList(haxorg_LispCodeList* obj);
HAXORG_C_API_LINKAGE void haxorg_create_LispCodeKeyValue_KeyValue(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_LispCodeKeyValue(haxorg_LispCodeKeyValue* obj);
HAXORG_C_API_LINKAGE void haxorg_create_LispCodeNumber_Number(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_LispCodeNumber(haxorg_LispCodeNumber* obj);
HAXORG_C_API_LINKAGE void haxorg_create_LispCodeText_Text(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_LispCodeText(haxorg_LispCodeText* obj);
HAXORG_C_API_LINKAGE void haxorg_create_LispCodeIdent_Ident(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_LispCodeIdent(haxorg_LispCodeIdent* obj);
HAXORG_C_API_LINKAGE void haxorg_create_LispCodeBoolean_Boolean(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_LispCodeBoolean(haxorg_LispCodeBoolean* obj);
HAXORG_C_API_LINKAGE void haxorg_create_LispCodeReal_Real(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_LispCodeReal(haxorg_LispCodeReal* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_LispCode(haxorg_LispCode* obj);
HAXORG_C_API_LINKAGE void haxorg_create_TblfmExprAxisRefPosition_Position(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_create_TblfmExprAxisRefPositionIndex_Index(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_TblfmExprAxisRefPositionIndex(haxorg_TblfmExprAxisRefPositionIndex* obj);
HAXORG_C_API_LINKAGE void haxorg_create_TblfmExprAxisRefPositionName_Name(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_TblfmExprAxisRefPositionName(haxorg_TblfmExprAxisRefPositionName* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_TblfmExprAxisRefPosition(haxorg_TblfmExprAxisRefPosition* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_TblfmExprAxisRef(haxorg_TblfmExprAxisRef* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_TblfmExprAxisName(haxorg_TblfmExprAxisName* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_TblfmExprIntLiteral(haxorg_TblfmExprIntLiteral* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_TblfmExprFloatLiteral(haxorg_TblfmExprFloatLiteral* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_TblfmExprRangeRef(haxorg_TblfmExprRangeRef* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_TblfmExprCall(haxorg_TblfmExprCall* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_TblfmExprElisp(haxorg_TblfmExprElisp* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_TblfmExpr(haxorg_TblfmExpr* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_TblfmAssign(haxorg_TblfmAssign* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Tblfm(haxorg_Tblfm* obj);
HAXORG_C_API_LINKAGE void haxorg_create_AttrValue_AttrValue(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_create_AttrValueDimensionSpan_DimensionSpan(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_AttrValueDimensionSpan(haxorg_AttrValueDimensionSpan* obj);
HAXORG_C_API_LINKAGE void haxorg_create_AttrValueTextValue_TextValue(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_AttrValueTextValue(haxorg_AttrValueTextValue* obj);
HAXORG_C_API_LINKAGE void haxorg_create_AttrValueFileReference_FileReference(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_AttrValueFileReference(haxorg_AttrValueFileReference* obj);
HAXORG_C_API_LINKAGE void haxorg_create_AttrValueLispValue_LispValue(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_AttrValueLispValue(haxorg_AttrValueLispValue* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_AttrValue(haxorg_AttrValue* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_HashTagFlat(haxorg_HashTagFlat* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_TodoKeyword(haxorg_TodoKeyword* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_HashTagText(haxorg_HashTagText* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_SubtreePath(haxorg_SubtreePath* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_LinkTargetRaw(haxorg_LinkTargetRaw* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_LinkTargetId(haxorg_LinkTargetId* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_LinkTargetCustomId(haxorg_LinkTargetCustomId* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_LinkTargetSubtreeTitle(haxorg_LinkTargetSubtreeTitle* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_LinkTargetPerson(haxorg_LinkTargetPerson* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_LinkTargetUserProtocol(haxorg_LinkTargetUserProtocol* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_LinkTargetInternal(haxorg_LinkTargetInternal* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_LinkTargetFootnote(haxorg_LinkTargetFootnote* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_LinkTargetFile(haxorg_LinkTargetFile* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_LinkTargetAttachment(haxorg_LinkTargetAttachment* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_LinkTarget(haxorg_LinkTarget* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_SubtreeLogHeadPriority(haxorg_SubtreeLogHeadPriority* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_SubtreeLogHeadNote(haxorg_SubtreeLogHeadNote* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_SubtreeLogHeadRefile(haxorg_SubtreeLogHeadRefile* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_SubtreeLogHeadClock(haxorg_SubtreeLogHeadClock* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_SubtreeLogHeadState(haxorg_SubtreeLogHeadState* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_SubtreeLogHeadDeadline(haxorg_SubtreeLogHeadDeadline* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_SubtreeLogHeadSchedule(haxorg_SubtreeLogHeadSchedule* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_SubtreeLogHeadTag(haxorg_SubtreeLogHeadTag* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_SubtreeLogHeadUnknown(haxorg_SubtreeLogHeadUnknown* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_SubtreeLogHead(haxorg_SubtreeLogHead* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_SubtreeCompletion(haxorg_SubtreeCompletion* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_AttrList(haxorg_AttrList* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_AttrGroup(haxorg_AttrGroup* obj);
HAXORG_C_API_LINKAGE void haxorg_create_OrgCodeEvalInputVar_Var(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_OrgCodeEvalInputVar(haxorg_OrgCodeEvalInputVar* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_OrgCodeEvalInput(haxorg_OrgCodeEvalInput* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_OrgCodeEvalOutput(haxorg_OrgCodeEvalOutput* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ColumnViewSummaryCheckboxAggregate(haxorg_ColumnViewSummaryCheckboxAggregate* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ColumnViewSummaryMathAggregate(haxorg_ColumnViewSummaryMathAggregate* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ColumnViewSummary(haxorg_ColumnViewSummary* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ColumnViewColumn(haxorg_ColumnViewColumn* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ColumnView(haxorg_ColumnView* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_BlockCodeLinePartRaw(haxorg_BlockCodeLinePartRaw* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_BlockCodeLinePartCallout(haxorg_BlockCodeLinePartCallout* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_BlockCodeLinePartTangle(haxorg_BlockCodeLinePartTangle* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_BlockCodeLinePart(haxorg_BlockCodeLinePart* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_BlockCodeLine(haxorg_BlockCodeLine* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_DocumentExportConfigTaskExport(haxorg_DocumentExportConfigTaskExport* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_DocumentExportConfigDoExport(haxorg_DocumentExportConfigDoExport* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_DocumentExportConfigExportFixed(haxorg_DocumentExportConfigExportFixed* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_DocumentExportConfig(haxorg_DocumentExportConfig* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_SubtreePeriod(haxorg_SubtreePeriod* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyNonblocking(haxorg_NamedPropertyNonblocking* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyArchiveTime(haxorg_NamedPropertyArchiveTime* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyArchiveFile(haxorg_NamedPropertyArchiveFile* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyArchiveOlpath(haxorg_NamedPropertyArchiveOlpath* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyArchiveTarget(haxorg_NamedPropertyArchiveTarget* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyArchiveCategory(haxorg_NamedPropertyArchiveCategory* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyArchiveTodo(haxorg_NamedPropertyArchiveTodo* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyTrigger(haxorg_NamedPropertyTrigger* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyExportLatexClass(haxorg_NamedPropertyExportLatexClass* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyCookieData(haxorg_NamedPropertyCookieData* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyExportLatexClassOptions(haxorg_NamedPropertyExportLatexClassOptions* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyExportLatexHeader(haxorg_NamedPropertyExportLatexHeader* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyExportLatexCompiler(haxorg_NamedPropertyExportLatexCompiler* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyOrdered(haxorg_NamedPropertyOrdered* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyEffort(haxorg_NamedPropertyEffort* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyVisibility(haxorg_NamedPropertyVisibility* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyExportOptions(haxorg_NamedPropertyExportOptions* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyBlocker(haxorg_NamedPropertyBlocker* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyUnnumbered(haxorg_NamedPropertyUnnumbered* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyCreated(haxorg_NamedPropertyCreated* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyRadioId(haxorg_NamedPropertyRadioId* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyHashtagDef(haxorg_NamedPropertyHashtagDef* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyCustomArgs(haxorg_NamedPropertyCustomArgs* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyCustomRaw(haxorg_NamedPropertyCustomRaw* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyCustomId(haxorg_NamedPropertyCustomId* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyCustomSubtreeJson(haxorg_NamedPropertyCustomSubtreeJson* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedPropertyCustomSubtreeFlags(haxorg_NamedPropertyCustomSubtreeFlags* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NamedProperty(haxorg_NamedProperty* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_OrgDiagnosticsParseTokenError(haxorg_OrgDiagnosticsParseTokenError* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_OrgDiagnosticsParseError(haxorg_OrgDiagnosticsParseError* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_OrgDiagnosticsIncludeError(haxorg_OrgDiagnosticsIncludeError* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_OrgDiagnosticsConvertError(haxorg_OrgDiagnosticsConvertError* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_OrgDiagnosticsInternalError(haxorg_OrgDiagnosticsInternalError* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_OrgDiagnostics(haxorg_OrgDiagnostics* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_NoNode(haxorg_NoNode* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ErrorItem(haxorg_ErrorItem* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ErrorGroup(haxorg_ErrorGroup* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Stmt(haxorg_Stmt* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Inline(haxorg_Inline* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_StmtList(haxorg_StmtList* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Empty(haxorg_Empty* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Leaf(haxorg_Leaf* obj);
HAXORG_C_API_LINKAGE void haxorg_create_TimeRepeat_Repeat(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_TimeRepeat(haxorg_TimeRepeat* obj);
HAXORG_C_API_LINKAGE void haxorg_create_TimeStatic_Static(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_TimeStatic(haxorg_TimeStatic* obj);
HAXORG_C_API_LINKAGE void haxorg_create_TimeDynamic_Dynamic(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_TimeDynamic(haxorg_TimeDynamic* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Time(haxorg_Time* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_TimeRange(haxorg_TimeRange* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Macro(haxorg_Macro* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_SymbolParam(haxorg_SymbolParam* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Symbol(haxorg_Symbol* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ErrorSkipGroup(haxorg_ErrorSkipGroup* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Markup(haxorg_Markup* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_RadioTarget(haxorg_RadioTarget* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Latex(haxorg_Latex* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_SubtreeLog(haxorg_SubtreeLog* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Subtree(haxorg_Subtree* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ColonExample(haxorg_ColonExample* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Call(haxorg_Call* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ListItem(haxorg_ListItem* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_DocumentOptions(haxorg_DocumentOptions* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_DocumentFragment(haxorg_DocumentFragment* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_CriticMarkup(haxorg_CriticMarkup* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Document(haxorg_Document* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_FileTarget(haxorg_FileTarget* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_TextSeparator(haxorg_TextSeparator* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_DocumentGroup(haxorg_DocumentGroup* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_FileDocument(haxorg_FileDocument* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_FileAttachment(haxorg_FileAttachment* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_FileSource(haxorg_FileSource* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_File(haxorg_File* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Directory(haxorg_Directory* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Symlink(haxorg_Symlink* obj);
HAXORG_C_API_LINKAGE void haxorg_create_CmdIncludeIncludeBase_IncludeBase(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdIncludeIncludeBase(haxorg_CmdIncludeIncludeBase* obj);
HAXORG_C_API_LINKAGE void haxorg_create_CmdIncludeExample_Example(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdIncludeExample(haxorg_CmdIncludeExample* obj);
HAXORG_C_API_LINKAGE void haxorg_create_CmdIncludeExport_Export(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdIncludeExport(haxorg_CmdIncludeExport* obj);
HAXORG_C_API_LINKAGE void haxorg_create_CmdIncludeCustom_Custom(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdIncludeCustom(haxorg_CmdIncludeCustom* obj);
HAXORG_C_API_LINKAGE void haxorg_create_CmdIncludeSrc_Src(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdIncludeSrc(haxorg_CmdIncludeSrc* obj);
HAXORG_C_API_LINKAGE void haxorg_create_CmdIncludeOrgDocument_OrgDocument(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdIncludeOrgDocument(haxorg_CmdIncludeOrgDocument* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdInclude(haxorg_CmdInclude* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmNoNode(haxorg_ImmNoNode* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmErrorItem(haxorg_ImmErrorItem* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmErrorGroup(haxorg_ImmErrorGroup* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmStmt(haxorg_ImmStmt* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmInline(haxorg_ImmInline* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmStmtList(haxorg_ImmStmtList* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmEmpty(haxorg_ImmEmpty* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmLeaf(haxorg_ImmLeaf* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmTimeRepeat_Repeat(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmTimeRepeat(haxorg_ImmTimeRepeat* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmTimeStatic_Static(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmTimeStatic(haxorg_ImmTimeStatic* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmTimeDynamic_Dynamic(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmTimeDynamic(haxorg_ImmTimeDynamic* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmTime(haxorg_ImmTime* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmTimeRange(haxorg_ImmTimeRange* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmMacro(haxorg_ImmMacro* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmSymbolParam(haxorg_ImmSymbolParam* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmSymbol(haxorg_ImmSymbol* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmErrorSkipGroup(haxorg_ImmErrorSkipGroup* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmMarkup(haxorg_ImmMarkup* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmRadioTarget(haxorg_ImmRadioTarget* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmLatex(haxorg_ImmLatex* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmSubtreeLog(haxorg_ImmSubtreeLog* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmSubtree(haxorg_ImmSubtree* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmColonExample(haxorg_ImmColonExample* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCall(haxorg_ImmCall* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmListItem(haxorg_ImmListItem* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmDocumentOptions(haxorg_ImmDocumentOptions* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmDocumentFragment(haxorg_ImmDocumentFragment* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCriticMarkup(haxorg_ImmCriticMarkup* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmDocument(haxorg_ImmDocument* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmFileTarget(haxorg_ImmFileTarget* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmTextSeparator(haxorg_ImmTextSeparator* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmDocumentGroup(haxorg_ImmDocumentGroup* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmFileDocument(haxorg_ImmFileDocument* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmFileAttachment(haxorg_ImmFileAttachment* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmFileSource(haxorg_ImmFileSource* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmFile(haxorg_ImmFile* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmDirectory(haxorg_ImmDirectory* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmSymlink(haxorg_ImmSymlink* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmCmdIncludeIncludeBase_IncludeBase(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdIncludeIncludeBase(haxorg_ImmCmdIncludeIncludeBase* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmCmdIncludeExample_Example(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdIncludeExample(haxorg_ImmCmdIncludeExample* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmCmdIncludeExport_Export(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdIncludeExport(haxorg_ImmCmdIncludeExport* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmCmdIncludeCustom_Custom(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdIncludeCustom(haxorg_ImmCmdIncludeCustom* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmCmdIncludeSrc_Src(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdIncludeSrc(haxorg_ImmCmdIncludeSrc* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmCmdIncludeOrgDocument_OrgDocument(OrgContext* org_context);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdIncludeOrgDocument(haxorg_ImmCmdIncludeOrgDocument* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdInclude(haxorg_ImmCmdInclude* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterOrgAPI(haxorg_ImmAdapterOrgAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Cmd(haxorg_Cmd* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdCustomRaw(haxorg_CmdCustomRaw* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdCustomText(haxorg_CmdCustomText* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Link(haxorg_Link* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_BlockComment(haxorg_BlockComment* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Paragraph(haxorg_Paragraph* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_List(haxorg_List* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_HashTag(haxorg_HashTag* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_InlineFootnote(haxorg_InlineFootnote* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_InlineExport(haxorg_InlineExport* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Escaped(haxorg_Escaped* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Newline(haxorg_Newline* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Space(haxorg_Space* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Word(haxorg_Word* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_AtMention(haxorg_AtMention* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_RawText(haxorg_RawText* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Punctuation(haxorg_Punctuation* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Placeholder(haxorg_Placeholder* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_BigIdent(haxorg_BigIdent* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_TextTarget(haxorg_TextTarget* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ErrorSkipToken(haxorg_ErrorSkipToken* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Bold(haxorg_Bold* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Underline(haxorg_Underline* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Monospace(haxorg_Monospace* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_MarkQuote(haxorg_MarkQuote* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Verbatim(haxorg_Verbatim* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Italic(haxorg_Italic* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Strike(haxorg_Strike* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Par(haxorg_Par* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmd(haxorg_ImmCmd* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdCustomRaw(haxorg_ImmCmdCustomRaw* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdCustomText(haxorg_ImmCmdCustomText* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmLink(haxorg_ImmLink* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockComment(haxorg_ImmBlockComment* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmParagraph(haxorg_ImmParagraph* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmList(haxorg_ImmList* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmHashTag(haxorg_ImmHashTag* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmInlineFootnote(haxorg_ImmInlineFootnote* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmInlineExport(haxorg_ImmInlineExport* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmEscaped(haxorg_ImmEscaped* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmNewline(haxorg_ImmNewline* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmSpace(haxorg_ImmSpace* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmWord(haxorg_ImmWord* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAtMention(haxorg_ImmAtMention* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmRawText(haxorg_ImmRawText* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmPunctuation(haxorg_ImmPunctuation* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmPlaceholder(haxorg_ImmPlaceholder* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBigIdent(haxorg_ImmBigIdent* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmTextTarget(haxorg_ImmTextTarget* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmErrorSkipToken(haxorg_ImmErrorSkipToken* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBold(haxorg_ImmBold* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmUnderline(haxorg_ImmUnderline* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmMonospace(haxorg_ImmMonospace* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmMarkQuote(haxorg_ImmMarkQuote* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmVerbatim(haxorg_ImmVerbatim* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmItalic(haxorg_ImmItalic* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmStrike(haxorg_ImmStrike* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmPar(haxorg_ImmPar* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterStmtAPI(haxorg_ImmAdapterStmtAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterSubtreeAPI(haxorg_ImmAdapterSubtreeAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterNoNodeAPI(haxorg_ImmAdapterNoNodeAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterAttrAPI(haxorg_ImmAdapterAttrAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterAttrListAPI(haxorg_ImmAdapterAttrListAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterAttrsAPI(haxorg_ImmAdapterAttrsAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterErrorItemAPI(haxorg_ImmAdapterErrorItemAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterErrorGroupAPI(haxorg_ImmAdapterErrorGroupAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterErrorSkipGroupAPI(haxorg_ImmAdapterErrorSkipGroupAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterErrorSkipTokenAPI(haxorg_ImmAdapterErrorSkipTokenAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterStmtListAPI(haxorg_ImmAdapterStmtListAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterEmptyAPI(haxorg_ImmAdapterEmptyAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterInlineAPI(haxorg_ImmAdapterInlineAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterTimeAPI(haxorg_ImmAdapterTimeAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterTimeRangeAPI(haxorg_ImmAdapterTimeRangeAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterMacroAPI(haxorg_ImmAdapterMacroAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterSymbolAPI(haxorg_ImmAdapterSymbolAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterLeafAPI(haxorg_ImmAdapterLeafAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterMarkupAPI(haxorg_ImmAdapterMarkupAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterLatexAPI(haxorg_ImmAdapterLatexAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterSubtreeLogAPI(haxorg_ImmAdapterSubtreeLogAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterColonExampleAPI(haxorg_ImmAdapterColonExampleAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCallAPI(haxorg_ImmAdapterCallAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterFileAPI(haxorg_ImmAdapterFileAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterDirectoryAPI(haxorg_ImmAdapterDirectoryAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterSymlinkAPI(haxorg_ImmAdapterSymlinkAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterDocumentFragmentAPI(haxorg_ImmAdapterDocumentFragmentAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCriticMarkupAPI(haxorg_ImmAdapterCriticMarkupAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterListItemAPI(haxorg_ImmAdapterListItemAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterDocumentOptionsAPI(haxorg_ImmAdapterDocumentOptionsAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterDocumentAPI(haxorg_ImmAdapterDocumentAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterFileTargetAPI(haxorg_ImmAdapterFileTargetAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterTextSeparatorAPI(haxorg_ImmAdapterTextSeparatorAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdIncludeAPI(haxorg_ImmAdapterCmdIncludeAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterDocumentGroupAPI(haxorg_ImmAdapterDocumentGroupAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Block(haxorg_Block* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_LineCommand(haxorg_LineCommand* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdCreator(haxorg_CmdCreator* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdAuthor(haxorg_CmdAuthor* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdEmail(haxorg_CmdEmail* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdLanguage(haxorg_CmdLanguage* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdCustomArgs(haxorg_CmdCustomArgs* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdTblfm(haxorg_CmdTblfm* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Cell(haxorg_Cell* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Row(haxorg_Row* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlock(haxorg_ImmBlock* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmLineCommand(haxorg_ImmLineCommand* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdCreator(haxorg_ImmCmdCreator* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdAuthor(haxorg_ImmCmdAuthor* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdEmail(haxorg_ImmCmdEmail* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdLanguage(haxorg_ImmCmdLanguage* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdCustomArgs(haxorg_ImmCmdCustomArgs* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdTblfm(haxorg_ImmCmdTblfm* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCell(haxorg_ImmCell* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmRow(haxorg_ImmRow* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdAPI(haxorg_ImmAdapterCmdAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdCustomRawAPI(haxorg_ImmAdapterCmdCustomRawAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdCustomTextAPI(haxorg_ImmAdapterCmdCustomTextAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterLinkAPI(haxorg_ImmAdapterLinkAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterBlockCommentAPI(haxorg_ImmAdapterBlockCommentAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterParagraphAPI(haxorg_ImmAdapterParagraphAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterListAPI(haxorg_ImmAdapterListAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmStmt_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmStmtAdapter(haxorg_ImmStmtAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmSubtree_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmSubtreeAdapter(haxorg_ImmSubtreeAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmNoNode_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmNoNodeAdapter(haxorg_ImmNoNodeAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmErrorItem_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmErrorItemAdapter(haxorg_ImmErrorItemAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmErrorGroup_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmErrorGroupAdapter(haxorg_ImmErrorGroupAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmErrorSkipGroup_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmErrorSkipGroupAdapter(haxorg_ImmErrorSkipGroupAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmErrorSkipToken_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmErrorSkipTokenAdapter(haxorg_ImmErrorSkipTokenAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmStmtList_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmStmtListAdapter(haxorg_ImmStmtListAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmEmpty_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmEmptyAdapter(haxorg_ImmEmptyAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterHashTagAPI(haxorg_ImmAdapterHashTagAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterInlineFootnoteAPI(haxorg_ImmAdapterInlineFootnoteAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterSubtreeCompletionAPI(haxorg_ImmAdapterSubtreeCompletionAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmInline_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmInlineAdapter(haxorg_ImmInlineAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmTime_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmTimeAdapter(haxorg_ImmTimeAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmTimeRange_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmTimeRangeAdapter(haxorg_ImmTimeRangeAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmMacro_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmMacroAdapter(haxorg_ImmMacroAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmSymbol_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmSymbolAdapter(haxorg_ImmSymbolAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterEscapedAPI(haxorg_ImmAdapterEscapedAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterNewlineAPI(haxorg_ImmAdapterNewlineAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterSpaceAPI(haxorg_ImmAdapterSpaceAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterWordAPI(haxorg_ImmAdapterWordAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterAtMentionAPI(haxorg_ImmAdapterAtMentionAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterRawTextAPI(haxorg_ImmAdapterRawTextAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterPunctuationAPI(haxorg_ImmAdapterPunctuationAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterPlaceholderAPI(haxorg_ImmAdapterPlaceholderAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterBigIdentAPI(haxorg_ImmAdapterBigIdentAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterTextTargetAPI(haxorg_ImmAdapterTextTargetAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmLeaf_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmLeafAdapter(haxorg_ImmLeafAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterBoldAPI(haxorg_ImmAdapterBoldAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterUnderlineAPI(haxorg_ImmAdapterUnderlineAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterMonospaceAPI(haxorg_ImmAdapterMonospaceAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterMarkQuoteAPI(haxorg_ImmAdapterMarkQuoteAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterRadioTargetAPI(haxorg_ImmAdapterRadioTargetAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterVerbatimAPI(haxorg_ImmAdapterVerbatimAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterItalicAPI(haxorg_ImmAdapterItalicAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterStrikeAPI(haxorg_ImmAdapterStrikeAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterParAPI(haxorg_ImmAdapterParAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmMarkup_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmMarkupAdapter(haxorg_ImmMarkupAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmLatex_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmLatexAdapter(haxorg_ImmLatexAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmSubtreeLog_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmSubtreeLogAdapter(haxorg_ImmSubtreeLogAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmColonExample_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmColonExampleAdapter(haxorg_ImmColonExampleAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCall_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCallAdapter(haxorg_ImmCallAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmFile_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmFileAdapter(haxorg_ImmFileAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmDirectory_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmDirectoryAdapter(haxorg_ImmDirectoryAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmSymlink_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmSymlinkAdapter(haxorg_ImmSymlinkAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmDocumentFragment_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmDocumentFragmentAdapter(haxorg_ImmDocumentFragmentAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCriticMarkup_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCriticMarkupAdapter(haxorg_ImmCriticMarkupAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmListItem_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmListItemAdapter(haxorg_ImmListItemAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmDocumentOptions_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmDocumentOptionsAdapter(haxorg_ImmDocumentOptionsAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmDocument_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmDocumentAdapter(haxorg_ImmDocumentAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmFileTarget_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmFileTargetAdapter(haxorg_ImmFileTargetAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmTextSeparator_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmTextSeparatorAdapter(haxorg_ImmTextSeparatorAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmdInclude_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdIncludeAdapter(haxorg_ImmCmdIncludeAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmDocumentGroup_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmDocumentGroupAdapter(haxorg_ImmDocumentGroupAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_BlockCenter(haxorg_BlockCenter* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_BlockQuote(haxorg_BlockQuote* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_BlockVerse(haxorg_BlockVerse* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_BlockDynamicFallback(haxorg_BlockDynamicFallback* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_BlockExample(haxorg_BlockExample* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_BlockExport(haxorg_BlockExport* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_BlockAdmonition(haxorg_BlockAdmonition* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_BlockCodeEvalResult(haxorg_BlockCodeEvalResult* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_BlockCode(haxorg_BlockCode* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Table(haxorg_Table* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_Attached(haxorg_Attached* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockCenter(haxorg_ImmBlockCenter* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockQuote(haxorg_ImmBlockQuote* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockVerse(haxorg_ImmBlockVerse* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockDynamicFallback(haxorg_ImmBlockDynamicFallback* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockExample(haxorg_ImmBlockExample* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockExport(haxorg_ImmBlockExport* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockAdmonition(haxorg_ImmBlockAdmonition* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockCodeEvalResult(haxorg_ImmBlockCodeEvalResult* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockCode(haxorg_ImmBlockCode* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmTable(haxorg_ImmTable* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAttached(haxorg_ImmAttached* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterLineCommandAPI(haxorg_ImmAdapterLineCommandAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdCustomArgsAPI(haxorg_ImmAdapterCmdCustomArgsAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdCreatorAPI(haxorg_ImmAdapterCmdCreatorAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdAuthorAPI(haxorg_ImmAdapterCmdAuthorAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdEmailAPI(haxorg_ImmAdapterCmdEmailAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdLanguageAPI(haxorg_ImmAdapterCmdLanguageAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdTblfmAPI(haxorg_ImmAdapterCmdTblfmAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterBlockAPI(haxorg_ImmAdapterBlockAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCellAPI(haxorg_ImmAdapterCellAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterRowAPI(haxorg_ImmAdapterRowAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmd_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdAdapter(haxorg_ImmCmdAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmdCustomRaw_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdCustomRawAdapter(haxorg_ImmCmdCustomRawAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmdCustomText_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdCustomTextAdapter(haxorg_ImmCmdCustomTextAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmLink_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmLinkAdapter(haxorg_ImmLinkAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmBlockComment_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockCommentAdapter(haxorg_ImmBlockCommentAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmParagraph_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmParagraphAdapter(haxorg_ImmParagraphAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmList_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmListAdapter(haxorg_ImmListAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmHashTag_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmHashTagAdapter(haxorg_ImmHashTagAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmInlineFootnote_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmInlineFootnoteAdapter(haxorg_ImmInlineFootnoteAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmEscaped_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmEscapedAdapter(haxorg_ImmEscapedAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmNewline_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmNewlineAdapter(haxorg_ImmNewlineAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmSpace_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmSpaceAdapter(haxorg_ImmSpaceAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmWord_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmWordAdapter(haxorg_ImmWordAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmAtMention_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAtMentionAdapter(haxorg_ImmAtMentionAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmRawText_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmRawTextAdapter(haxorg_ImmRawTextAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmPunctuation_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmPunctuationAdapter(haxorg_ImmPunctuationAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmPlaceholder_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmPlaceholderAdapter(haxorg_ImmPlaceholderAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmBigIdent_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBigIdentAdapter(haxorg_ImmBigIdentAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmTextTarget_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmTextTargetAdapter(haxorg_ImmTextTargetAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmBold_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBoldAdapter(haxorg_ImmBoldAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmUnderline_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmUnderlineAdapter(haxorg_ImmUnderlineAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmMonospace_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmMonospaceAdapter(haxorg_ImmMonospaceAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmMarkQuote_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmMarkQuoteAdapter(haxorg_ImmMarkQuoteAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmRadioTarget_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmRadioTargetAdapter(haxorg_ImmRadioTargetAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmVerbatim_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmVerbatimAdapter(haxorg_ImmVerbatimAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmItalic_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmItalicAdapter(haxorg_ImmItalicAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmStrike_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmStrikeAdapter(haxorg_ImmStrikeAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmPar_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmParAdapter(haxorg_ImmParAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdCaption(haxorg_CmdCaption* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdColumns(haxorg_CmdColumns* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdName(haxorg_CmdName* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdCall(haxorg_CmdCall* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdAttr(haxorg_CmdAttr* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_CmdExport(haxorg_CmdExport* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdCaption(haxorg_ImmCmdCaption* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdColumns(haxorg_ImmCmdColumns* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdName(haxorg_ImmCmdName* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdCall(haxorg_ImmCmdCall* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdAttr(haxorg_ImmCmdAttr* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdExport(haxorg_ImmCmdExport* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterAttachedAPI(haxorg_ImmAdapterAttachedAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmLineCommand_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmLineCommandAdapter(haxorg_ImmLineCommandAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmdCustomArgs_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdCustomArgsAdapter(haxorg_ImmCmdCustomArgsAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmdCreator_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdCreatorAdapter(haxorg_ImmCmdCreatorAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmdAuthor_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdAuthorAdapter(haxorg_ImmCmdAuthorAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmdEmail_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdEmailAdapter(haxorg_ImmCmdEmailAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmdLanguage_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdLanguageAdapter(haxorg_ImmCmdLanguageAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmdTblfm_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdTblfmAdapter(haxorg_ImmCmdTblfmAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterBlockCenterAPI(haxorg_ImmAdapterBlockCenterAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterBlockQuoteAPI(haxorg_ImmAdapterBlockQuoteAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterBlockVerseAPI(haxorg_ImmAdapterBlockVerseAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterBlockExampleAPI(haxorg_ImmAdapterBlockExampleAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterInlineExportAPI(haxorg_ImmAdapterInlineExportAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdExportAPI(haxorg_ImmAdapterCmdExportAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterBlockExportAPI(haxorg_ImmAdapterBlockExportAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterBlockDynamicFallbackAPI(haxorg_ImmAdapterBlockDynamicFallbackAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterBlockAdmonitionAPI(haxorg_ImmAdapterBlockAdmonitionAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterBlockCodeEvalResultAPI(haxorg_ImmAdapterBlockCodeEvalResultAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterBlockCodeAPI(haxorg_ImmAdapterBlockCodeAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterTableAPI(haxorg_ImmAdapterTableAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmBlock_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockAdapter(haxorg_ImmBlockAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCell_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCellAdapter(haxorg_ImmCellAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmRow_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmRowAdapter(haxorg_ImmRowAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdCaptionAPI(haxorg_ImmAdapterCmdCaptionAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdColumnsAPI(haxorg_ImmAdapterCmdColumnsAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdNameAPI(haxorg_ImmAdapterCmdNameAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdCallAPI(haxorg_ImmAdapterCmdCallAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdResultsAPI(haxorg_ImmAdapterCmdResultsAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAdapterCmdAttrAPI(haxorg_ImmAdapterCmdAttrAPI* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmAttached_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmAttachedAdapter(haxorg_ImmAttachedAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmBlockCenter_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockCenterAdapter(haxorg_ImmBlockCenterAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmBlockQuote_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockQuoteAdapter(haxorg_ImmBlockQuoteAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmBlockVerse_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockVerseAdapter(haxorg_ImmBlockVerseAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmBlockExample_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockExampleAdapter(haxorg_ImmBlockExampleAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmInlineExport_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmInlineExportAdapter(haxorg_ImmInlineExportAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmdExport_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdExportAdapter(haxorg_ImmCmdExportAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmBlockExport_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockExportAdapter(haxorg_ImmBlockExportAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmBlockDynamicFallback_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockDynamicFallbackAdapter(haxorg_ImmBlockDynamicFallbackAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmBlockAdmonition_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockAdmonitionAdapter(haxorg_ImmBlockAdmonitionAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmBlockCodeEvalResult_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockCodeEvalResultAdapter(haxorg_ImmBlockCodeEvalResultAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmBlockCode_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmBlockCodeAdapter(haxorg_ImmBlockCodeAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmTable_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmTableAdapter(haxorg_ImmTableAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmdCaption_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdCaptionAdapter(haxorg_ImmCmdCaptionAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmdColumns_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdColumnsAdapter(haxorg_ImmCmdColumnsAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmdName_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdNameAdapter(haxorg_ImmCmdNameAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmdCall_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdCallAdapter(haxorg_ImmCmdCallAdapter* obj);
HAXORG_C_API_LINKAGE void haxorg_create_ImmAdapterTOfImmCmdAttr_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other);
HAXORG_C_API_LINKAGE void haxorg_destroy_ImmCmdAttrAdapter(haxorg_ImmCmdAttrAdapter* obj);
HAXORG_C_API_LINKAGE haxorg_SemId haxorg_newSemTimeStatic(OrgContext* org_context, haxorg_UserTimeBreakdown breakdown, bool isActive);
HAXORG_C_API_LINKAGE haxorg_ImmAstContext haxorg_initImmutableAstContext(OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_SemId haxorg_asOneNode(OrgContext* org_context, haxorg_SemId arg);
HAXORG_C_API_LINKAGE haxorg_StdString haxorg_formatToString(OrgContext* org_context, haxorg_SemId arg);
HAXORG_C_API_LINKAGE haxorg_StdString haxorg_exportToYamlString(OrgContext* org_context, haxorg_SemId node, haxorg_OrgYamlExportOpts opts);
HAXORG_C_API_LINKAGE void haxorg_exportToYamlFile(OrgContext* org_context, haxorg_SemId node, haxorg_StdString path, haxorg_OrgYamlExportOpts opts);
HAXORG_C_API_LINKAGE haxorg_StdString haxorg_exportToJsonString(OrgContext* org_context, haxorg_SemId node);
HAXORG_C_API_LINKAGE void haxorg_exportToJsonFile(OrgContext* org_context, haxorg_SemId node, haxorg_StdString path);
HAXORG_C_API_LINKAGE haxorg_SemId haxorg_readProtobufFile(OrgContext* org_context, haxorg_StdString file);
HAXORG_C_API_LINKAGE void haxorg_exportToProtobufFile(OrgContext* org_context, haxorg_SemId doc, haxorg_StdString file);
HAXORG_C_API_LINKAGE haxorg_StdString haxorg_exportToTreeString(OrgContext* org_context, haxorg_SemId node, haxorg_OrgTreeExportOpts opts);
HAXORG_C_API_LINKAGE void haxorg_exportToTreeFile(OrgContext* org_context, haxorg_SemId node, haxorg_StdString path, haxorg_OrgTreeExportOpts opts);
HAXORG_C_API_LINKAGE haxorg_AstTrackingMap haxorg_getAstTrackingMap(OrgContext* org_context, haxorg_HstdVec nodes);
HAXORG_C_API_LINKAGE haxorg_HstdVec haxorg_getSubnodeGroups(OrgContext* org_context, haxorg_SemId node, haxorg_AstTrackingMap map);
HAXORG_C_API_LINKAGE haxorg_HstdVec haxorg_annotateSequence(OrgContext* org_context, haxorg_HstdVec groups, int first, int last);
HAXORG_C_API_LINKAGE haxorg_GraphMapGraphState haxorg_initMapGraphState(OrgContext* org_context, haxorg_ImmAstContext ast);
HAXORG_C_API_LINKAGE haxorg_StdString haxorg_serializeAstContextToText(OrgContext* org_context, haxorg_ImmAstContext store);
HAXORG_C_API_LINKAGE void haxorg_serializeAstContextFromText(OrgContext* org_context, haxorg_StdString binary, haxorg_ImmAstContext store);
HAXORG_C_API_LINKAGE haxorg_StdString haxorg_serializeAstEpochToText(OrgContext* org_context, haxorg_ImmAstReplaceEpoch store);
HAXORG_C_API_LINKAGE void haxorg_serializeAstEpochFromText(OrgContext* org_context, haxorg_StdString binary, haxorg_ImmAstReplaceEpoch store);
HAXORG_C_API_LINKAGE haxorg_StdString haxorg_serializeMapGraphToText(OrgContext* org_context, haxorg_GraphMapGraph store);
HAXORG_C_API_LINKAGE void haxorg_serializeMapGraphFromText(OrgContext* org_context, haxorg_StdString binary, haxorg_GraphMapGraph store);
HAXORG_C_API_LINKAGE haxorg_StdString haxorg_serializeFromTextToTreeDump(OrgContext* org_context, haxorg_StdString binary);
/* clang-format on */
