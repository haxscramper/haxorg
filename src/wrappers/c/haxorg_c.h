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

typedef haxorg_immer_flex_vector haxorg_ImmPathStore;
/// \brief ['org', 'imm', 'ImmPath']
struct haxorg_ImmPath {
  haxorg_ImmPath_vtable const* vtable;
  haxorg_ptr_payload data;
};

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

typedef haxorg_HstdVec haxorg_GraphAdjNodesList;
typedef haxorg_HstdUnorderedMap haxorg_GraphNodeProps;
typedef haxorg_HstdUnorderedMap haxorg_GraphEdgeProps;
typedef haxorg_HstdUnorderedMap haxorg_GraphAdjList;
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

/// \brief ['org', 'graph', 'MapGraphState']
struct haxorg_GraphMapGraphState {
  haxorg_GraphMapGraphState_vtable const* vtable;
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
  haxorg_StdOptional const* (*get_year)(haxorg_UserTimeBreakdown const*, OrgContext*);
  haxorg_StdOptional const* (*get_month)(haxorg_UserTimeBreakdown const*, OrgContext*);
  haxorg_StdOptional const* (*get_day)(haxorg_UserTimeBreakdown const*, OrgContext*);
  haxorg_StdOptional const* (*get_hour)(haxorg_UserTimeBreakdown const*, OrgContext*);
  haxorg_StdOptional const* (*get_minute)(haxorg_UserTimeBreakdown const*, OrgContext*);
  haxorg_StdOptional const* (*get_second)(haxorg_UserTimeBreakdown const*, OrgContext*);
  haxorg_StdOptional const* (*get_zone)(haxorg_UserTimeBreakdown const*, OrgContext*);
};

struct haxorg_UserTime_vtable {
  haxorg_UserTimeBreakdown (*getBreakdown_const)(haxorg_UserTime, OrgContext*);
  haxorg_StdString (*format_const)(haxorg_UserTime, OrgContext*);
  int64_t (*getTimeDeltaSeconds_const)(haxorg_UserTime, OrgContext*, haxorg_UserTime);
  int64_t (*toUnixTimestamp_const)(haxorg_UserTime, OrgContext*);
};

struct haxorg_ParseSourceManager_vtable {
  haxorg_StdString (*getPath_const)(haxorg_ParseSourceManager, OrgContext*, haxorg_ParseSourceFileId);
  haxorg_ParseSourceFileId (*getId_const)(haxorg_ParseSourceManager, OrgContext*, haxorg_StdString);
  haxorg_StdString (*getSourceContent_const)(haxorg_ParseSourceManager, OrgContext*, haxorg_ParseSourceFileId);
  haxorg_StdString (*getContentTextForPath_const)(haxorg_ParseSourceManager, OrgContext*, haxorg_StdString);
  haxorg_ParseSourceFileId (*addSource)(haxorg_ParseSourceManager, OrgContext*, haxorg_StdString, haxorg_StdString);
};

struct haxorg_ParseSourceLoc_vtable {
  int const* (*get_line)(haxorg_ParseSourceLoc const*, OrgContext*);
  int const* (*get_column)(haxorg_ParseSourceLoc const*, OrgContext*);
  int const* (*get_pos)(haxorg_ParseSourceLoc const*, OrgContext*);
  haxorg_ParseSourceFileId const* (*get_file_id)(haxorg_ParseSourceLoc const*, OrgContext*);
};

struct haxorg_OrgJson_vtable {
  haxorg_OrgJsonKind (*getKind_const)(haxorg_OrgJson, OrgContext*);
  haxorg_StdString (*getJsonString_const)(haxorg_OrgJson, OrgContext*);
  haxorg_OrgJson (*atIndex_const)(haxorg_OrgJson, OrgContext*, int);
  haxorg_OrgJson (*atField_const)(haxorg_OrgJson, OrgContext*, haxorg_StdString);
  haxorg_StdString (*getString_const)(haxorg_OrgJson, OrgContext*);
  haxorg_OrgJson (*getField_const)(haxorg_OrgJson, OrgContext*, haxorg_StdString);
  haxorg_OrgJson (*getItem_const)(haxorg_OrgJson, OrgContext*, int);
  int (*getInt_const)(haxorg_OrgJson, OrgContext*);
  bool (*getBool_const)(haxorg_OrgJson, OrgContext*);
  haxorg_HstdVec (*getArray_const)(haxorg_OrgJson, OrgContext*);
  haxorg_StdString (*dump_const)(haxorg_OrgJson, OrgContext*, int);
};

struct haxorg_Org_vtable {
  haxorg_StdOptional const* (*get_loc)(haxorg_Org const*, OrgContext*);
  haxorg_HstdVec const* (*get_subnodes)(haxorg_Org const*, OrgContext*);
  haxorg_OrgSemKind (*getKind_const)(haxorg_Org, OrgContext*);
  void (*push_back)(haxorg_Org, OrgContext*, haxorg_SemId);
  int (*size_const)(haxorg_Org, OrgContext*);
  void (*insert)(haxorg_Org, OrgContext*, int, haxorg_SemId);
  haxorg_SemId (*at_const)(haxorg_Org, OrgContext*, int);
  bool (*is_const)(haxorg_Org, OrgContext*, haxorg_OrgSemKind);
};

struct haxorg_OperationsTracer_vtable {
  bool const* (*get_TraceState)(haxorg_OperationsTracer const*, OrgContext*);
  bool const* (*get_traceToFile)(haxorg_OperationsTracer const*, OrgContext*);
  bool const* (*get_traceToBuffer)(haxorg_OperationsTracer const*, OrgContext*);
  bool const* (*get_traceStructured)(haxorg_OperationsTracer const*, OrgContext*);
  bool const* (*get_traceColored)(haxorg_OperationsTracer const*, OrgContext*);
  int const* (*get_activeLevel)(haxorg_OperationsTracer const*, OrgContext*);
  haxorg_StdString const* (*get_traceBuffer)(haxorg_OperationsTracer const*, OrgContext*);
  void (*setTraceFileStr)(haxorg_OperationsTracer, OrgContext*, haxorg_StdString, bool);
  void (*sendMessage)(haxorg_OperationsTracer, OrgContext*, haxorg_StdString, haxorg_StdString, int, haxorg_StdString);
};

struct haxorg_ParseOrgParseFragment_vtable {
  int const* (*get_baseLine)(haxorg_ParseOrgParseFragment const*, OrgContext*);
  int const* (*get_baseCol)(haxorg_ParseOrgParseFragment const*, OrgContext*);
  haxorg_StdString const* (*get_text)(haxorg_ParseOrgParseFragment const*, OrgContext*);
};

struct haxorg_OrgParseParameters_vtable {
  haxorg_StdOptional const* (*get_baseTokenTracePath)(haxorg_OrgParseParameters const*, OrgContext*);
  haxorg_StdOptional const* (*get_tokenTracePath)(haxorg_OrgParseParameters const*, OrgContext*);
  haxorg_StdOptional const* (*get_parseTracePath)(haxorg_OrgParseParameters const*, OrgContext*);
  haxorg_StdOptional const* (*get_semTracePath)(haxorg_OrgParseParameters const*, OrgContext*);
};

struct haxorg_ParseContext_vtable {
  haxorg_Cache (*getDiagnosticStrings)(haxorg_ParseContext, OrgContext*);
  haxorg_ParseSourceFileId (*addSource_const)(haxorg_ParseContext, OrgContext*, haxorg_StdString, haxorg_StdString);
  haxorg_SemId (*parseFileOpts)(haxorg_ParseContext, OrgContext*, haxorg_StdString, haxorg_OrgParseParameters);
  haxorg_SemId (*parseFile)(haxorg_ParseContext, OrgContext*, haxorg_StdString);
  haxorg_SemId (*parseString)(haxorg_ParseContext, OrgContext*, haxorg_StdString, haxorg_StdString);
  haxorg_SemId (*parseStringOpts)(haxorg_ParseContext, OrgContext*, haxorg_StdString, haxorg_StdString, haxorg_OrgParseParameters);
  haxorg_StdOptional (*parseDirectory)(haxorg_ParseContext, OrgContext*, haxorg_StdString);
  haxorg_StdOptional (*parseDirectoryOpts)(haxorg_ParseContext, OrgContext*, haxorg_StdString, haxorg_OrgDirectoryParseParameters);
  haxorg_SemId (*parseFileWithIncludes)(haxorg_ParseContext, OrgContext*, haxorg_StdString, haxorg_OrgDirectoryParseParameters);
  haxorg_HstdVec (*collectDiagnostics)(haxorg_ParseContext, OrgContext*, haxorg_SemId, haxorg_Cache);
  haxorg_HstdVec (*collectErrorNodes)(haxorg_ParseContext, OrgContext*, haxorg_SemId);
};

struct haxorg_ImmReflFieldId_vtable {
  haxorg_HstdStr (*getName_const)(haxorg_ImmReflFieldId, OrgContext*);
};

struct haxorg_ImmId_vtable {
  haxorg_OrgSemKind (*getKind_const)(haxorg_ImmId, OrgContext*);
  bool (*is_const)(haxorg_ImmId, OrgContext*, haxorg_OrgSemKind);
  haxorg_ImmIdNodeIdxT (*getNodeIndex_const)(haxorg_ImmId, OrgContext*);
  haxorg_StdString (*getReadableId_const)(haxorg_ImmId, OrgContext*);
};

struct haxorg_ImmPath_vtable {
  haxorg_ImmId const* (*get_root)(haxorg_ImmPath const*, OrgContext*);
  haxorg_ImmPathStore const* (*get_path)(haxorg_ImmPath const*, OrgContext*);
  bool (*empty_const)(haxorg_ImmPath, OrgContext*);
};

struct haxorg_ImmAstContext_vtable {
  haxorg_ImmAstVersion (*addRoot)(haxorg_ImmAstContext, OrgContext*, haxorg_SemId);
  haxorg_ImmAstVersion (*getEmptyVersion)(haxorg_ImmAstContext, OrgContext*);
  haxorg_SemId (*get)(haxorg_ImmAstContext, OrgContext*, haxorg_ImmId);
};

struct haxorg_ImmAstVersion_vtable {
  haxorg_ImmId (*getRoot_const)(haxorg_ImmAstVersion, OrgContext*);
  haxorg_ImmAdapter (*getRootAdapter_const)(haxorg_ImmAstVersion, OrgContext*);
  haxorg_ImmAstContext (*getContext_const)(haxorg_ImmAstVersion, OrgContext*);
  haxorg_ImmAstReplaceEpoch (*getEpoch_const)(haxorg_ImmAstVersion, OrgContext*);
};

struct haxorg_ImmAdapterTreeReprConf_vtable {
  int const* (*get_maxDepth)(haxorg_ImmAdapterTreeReprConf const*, OrgContext*);
  bool const* (*get_withAuxFields)(haxorg_ImmAdapterTreeReprConf const*, OrgContext*);
  bool const* (*get_withReflFields)(haxorg_ImmAdapterTreeReprConf const*, OrgContext*);
  haxorg_HstdUnorderedSet const* (*get_withFieldSubset)(haxorg_ImmAdapterTreeReprConf const*, OrgContext*);
};

struct haxorg_ImmAdapter_vtable {
  int (*size_const)(haxorg_ImmAdapter, OrgContext*);
  bool (*isNil_const)(haxorg_ImmAdapter, OrgContext*);
  bool (*isRoot_const)(haxorg_ImmAdapter, OrgContext*);
  haxorg_OrgSemKind (*getKind_const)(haxorg_ImmAdapter, OrgContext*);
  haxorg_ImmUniqId (*uniq_const)(haxorg_ImmAdapter, OrgContext*);
  haxorg_StdString (*treeReprString_const)(haxorg_ImmAdapter, OrgContext*);
  haxorg_StdString (*treeReprStringOpts_const)(haxorg_ImmAdapter, OrgContext*, haxorg_ImmAdapterTreeReprConf);
  bool (*isDirectParentOf_const)(haxorg_ImmAdapter, OrgContext*, haxorg_ImmAdapter);
  bool (*isIndirectParentOf_const)(haxorg_ImmAdapter, OrgContext*, haxorg_ImmAdapter);
  bool (*isSubnodeOf_const)(haxorg_ImmAdapter, OrgContext*, haxorg_ImmAdapter);
  haxorg_StdOptional (*getParent_const)(haxorg_ImmAdapter, OrgContext*);
  int (*getSelfIndex_const)(haxorg_ImmAdapter, OrgContext*);
  haxorg_ImmAdapter (*atPathStep_const)(haxorg_ImmAdapter, OrgContext*, haxorg_ImmId, haxorg_ImmPathStep);
  haxorg_ImmAdapter (*atField_const)(haxorg_ImmAdapter, OrgContext*, haxorg_ImmReflFieldId);
  haxorg_ImmAdapter (*atIndex_const)(haxorg_ImmAdapter, OrgContext*, int, bool);
  haxorg_ImmAdapter (*atPath_const)(haxorg_ImmAdapter, OrgContext*, haxorg_HstdVec, bool);
  bool (*is_const)(haxorg_ImmAdapter, OrgContext*, haxorg_OrgSemKind);
  haxorg_HstdVec (*sub_const)(haxorg_ImmAdapter, OrgContext*, bool);
};

struct haxorg_OrgYamlExportOpts_vtable {
  bool const* (*get_skipNullFields)(haxorg_OrgYamlExportOpts const*, OrgContext*);
  bool const* (*get_skipFalseFields)(haxorg_OrgYamlExportOpts const*, OrgContext*);
  bool const* (*get_skipZeroFields)(haxorg_OrgYamlExportOpts const*, OrgContext*);
  bool const* (*get_skipLocation)(haxorg_OrgYamlExportOpts const*, OrgContext*);
  bool const* (*get_skipId)(haxorg_OrgYamlExportOpts const*, OrgContext*);
};

struct haxorg_OrgTreeExportOpts_vtable {
  bool const* (*get_withLineCol)(haxorg_OrgTreeExportOpts const*, OrgContext*);
  bool const* (*get_withOriginalId)(haxorg_OrgTreeExportOpts const*, OrgContext*);
  bool const* (*get_withSubnodeIdx)(haxorg_OrgTreeExportOpts const*, OrgContext*);
  bool const* (*get_skipEmptyFields)(haxorg_OrgTreeExportOpts const*, OrgContext*);
  int const* (*get_startLevel)(haxorg_OrgTreeExportOpts const*, OrgContext*);
  bool const* (*get_withColor)(haxorg_OrgTreeExportOpts const*, OrgContext*);
  int const* (*get_maxDepth)(haxorg_OrgTreeExportOpts const*, OrgContext*);
};

struct haxorg_AstTrackingPath_vtable {
  haxorg_HstdVec const* (*get_path)(haxorg_AstTrackingPath const*, OrgContext*);
  haxorg_SemId (*getParent_const)(haxorg_AstTrackingPath, OrgContext*, int);
  haxorg_SemId (*getNode_const)(haxorg_AstTrackingPath, OrgContext*);
};

struct haxorg_AstTrackingAlternatives_vtable {
  haxorg_HstdVec (*getAllNodes_const)(haxorg_AstTrackingAlternatives, OrgContext*);
  haxorg_SemId (*getNode_const)(haxorg_AstTrackingAlternatives, OrgContext*);
};

struct haxorg_AstTrackingGroupRadioTarget_vtable {
  haxorg_AstTrackingPath const* (*get_target)(haxorg_AstTrackingGroupRadioTarget const*, OrgContext*);
  haxorg_HstdVec const* (*get_nodes)(haxorg_AstTrackingGroupRadioTarget const*, OrgContext*);
};

struct haxorg_AstTrackingGroupSingle_vtable {
  haxorg_SemId const* (*get_node)(haxorg_AstTrackingGroupSingle const*, OrgContext*);
};

struct haxorg_AstTrackingGroupTrackedHashtag_vtable {
  haxorg_SemId const* (*get_tag)(haxorg_AstTrackingGroupTrackedHashtag const*, OrgContext*);
  haxorg_HstdUnorderedMap const* (*get_targets)(haxorg_AstTrackingGroupTrackedHashtag const*, OrgContext*);
};

struct haxorg_AstTrackingGroup_vtable {
  haxorg_AstTrackingGroupRadioTarget (*getRadioTargetConst_const)(haxorg_AstTrackingGroup, OrgContext*);
  haxorg_AstTrackingGroupTrackedHashtag (*getTrackedHashtagConst_const)(haxorg_AstTrackingGroup, OrgContext*);
  haxorg_AstTrackingGroupTrackedHashtag (*getTrackedHashtagMut)(haxorg_AstTrackingGroup, OrgContext*);
  haxorg_AstTrackingGroupSingle (*getSingleConst_const)(haxorg_AstTrackingGroup, OrgContext*);
  haxorg_AstTrackingGroupRadioTarget (*getRadioTargetMut)(haxorg_AstTrackingGroup, OrgContext*);
  haxorg_AstTrackingGroupSingle (*getSingleMut)(haxorg_AstTrackingGroup, OrgContext*);
  bool (*isSingle_const)(haxorg_AstTrackingGroup, OrgContext*);
  bool (*isTrackedHashtag_const)(haxorg_AstTrackingGroup, OrgContext*);
  bool (*isRadioTarget_const)(haxorg_AstTrackingGroup, OrgContext*);
};

struct haxorg_AstTrackingMap_vtable {
  haxorg_HstdUnorderedMap const* (*get_footnotes)(haxorg_AstTrackingMap const*, OrgContext*);
  haxorg_HstdUnorderedMap const* (*get_subtrees)(haxorg_AstTrackingMap const*, OrgContext*);
  haxorg_HstdUnorderedMap const* (*get_names)(haxorg_AstTrackingMap const*, OrgContext*);
  haxorg_HstdUnorderedMap const* (*get_anchorTargets)(haxorg_AstTrackingMap const*, OrgContext*);
  haxorg_HstdUnorderedMap const* (*get_radioTargets)(haxorg_AstTrackingMap const*, OrgContext*);
  haxorg_HstdUnorderedMap const* (*get_hashtagDefinitions)(haxorg_AstTrackingMap const*, OrgContext*);
  haxorg_StdOptional (*getIdPath_const)(haxorg_AstTrackingMap, OrgContext*, haxorg_HstdStr);
  haxorg_StdOptional (*getNamePath_const)(haxorg_AstTrackingMap, OrgContext*, haxorg_HstdStr);
  haxorg_StdOptional (*getAnchorTarget_const)(haxorg_AstTrackingMap, OrgContext*, haxorg_HstdStr);
  haxorg_StdOptional (*getFootnotePath_const)(haxorg_AstTrackingMap, OrgContext*, haxorg_HstdStr);
};

struct haxorg_SequenceSegment_vtable {
  int const* (*get_kind)(haxorg_SequenceSegment const*, OrgContext*);
  int const* (*get_first)(haxorg_SequenceSegment const*, OrgContext*);
  int const* (*get_last)(haxorg_SequenceSegment const*, OrgContext*);
};

struct haxorg_SequenceSegmentGroup_vtable {
  int const* (*get_kind)(haxorg_SequenceSegmentGroup const*, OrgContext*);
  haxorg_HstdVec const* (*get_segments)(haxorg_SequenceSegmentGroup const*, OrgContext*);
};

struct haxorg_SequenceAnnotationTag_vtable {
  int const* (*get_groupKind)(haxorg_SequenceAnnotationTag const*, OrgContext*);
  haxorg_HstdVec const* (*get_segmentKinds)(haxorg_SequenceAnnotationTag const*, OrgContext*);
};

struct haxorg_SequenceAnnotation_vtable {
  int const* (*get_first)(haxorg_SequenceAnnotation const*, OrgContext*);
  int const* (*get_last)(haxorg_SequenceAnnotation const*, OrgContext*);
  haxorg_HstdVec const* (*get_annotations)(haxorg_SequenceAnnotation const*, OrgContext*);
  bool (*isAnnotatedWith_const)(haxorg_SequenceAnnotation, OrgContext*, int, int);
};

struct haxorg_GraphMapLinkLink_vtable {
  haxorg_ImmUniqId const* (*get_link)(haxorg_GraphMapLinkLink const*, OrgContext*);
  haxorg_HstdVec const* (*get_description)(haxorg_GraphMapLinkLink const*, OrgContext*);
};

struct haxorg_GraphMapLinkRadio_vtable {
  haxorg_ImmUniqId const* (*get_target)(haxorg_GraphMapLinkRadio const*, OrgContext*);
};

struct haxorg_GraphMapLink_vtable {
  haxorg_GraphMapLinkRadio (*getRadio)(haxorg_GraphMapLink, OrgContext*);
  haxorg_GraphMapLinkRadio (*getRadio_const)(haxorg_GraphMapLink, OrgContext*);
  bool (*isRadio_const)(haxorg_GraphMapLink, OrgContext*);
  haxorg_GraphMapLinkLink (*getLink)(haxorg_GraphMapLink, OrgContext*);
  haxorg_GraphMapLinkLink (*getLink_const)(haxorg_GraphMapLink, OrgContext*);
  bool (*isLink_const)(haxorg_GraphMapLink, OrgContext*);
  haxorg_GraphMapLinkKind (*getKind_const)(haxorg_GraphMapLink, OrgContext*);
};

struct haxorg_GraphMapNodeProp_vtable {
  haxorg_ImmUniqId const* (*get_id)(haxorg_GraphMapNodeProp const*, OrgContext*);
  haxorg_HstdVec const* (*get_unresolved)(haxorg_GraphMapNodeProp const*, OrgContext*);
  haxorg_ImmAdapter (*getAdapter_const)(haxorg_GraphMapNodeProp, OrgContext*, haxorg_ImmAstContext);
  haxorg_StdOptional (*getSubtreeId_const)(haxorg_GraphMapNodeProp, OrgContext*, haxorg_ImmAstContext);
  haxorg_StdOptional (*getFootnoteName_const)(haxorg_GraphMapNodeProp, OrgContext*, haxorg_ImmAstContext);
};

struct haxorg_GraphMapEdgeProp_vtable {
  haxorg_GraphMapLink const* (*get_link)(haxorg_GraphMapEdgeProp const*, OrgContext*);
};

struct haxorg_GraphMapNode_vtable {
  haxorg_ImmUniqId const* (*get_id)(haxorg_GraphMapNode const*, OrgContext*);
  bool (*__eq___const)(haxorg_GraphMapNode, OrgContext*, haxorg_GraphMapNode);
  bool (*__lt___const)(haxorg_GraphMapNode, OrgContext*, haxorg_GraphMapNode);
};

struct haxorg_GraphMapEdge_vtable {
  haxorg_GraphMapNode const* (*get_source)(haxorg_GraphMapEdge const*, OrgContext*);
  haxorg_GraphMapNode const* (*get_target)(haxorg_GraphMapEdge const*, OrgContext*);
};

struct haxorg_GraphMapGraph_vtable {
  haxorg_GraphNodeProps const* (*get_nodeProps)(haxorg_GraphMapGraph const*, OrgContext*);
  haxorg_GraphEdgeProps const* (*get_edgeProps)(haxorg_GraphMapGraph const*, OrgContext*);
  haxorg_GraphAdjList const* (*get_adjList)(haxorg_GraphMapGraph const*, OrgContext*);
  haxorg_GraphAdjList const* (*get_adjListIn)(haxorg_GraphMapGraph const*, OrgContext*);
  int (*nodeCount_const)(haxorg_GraphMapGraph, OrgContext*);
  int (*edgeCount_const)(haxorg_GraphMapGraph, OrgContext*);
  haxorg_GraphAdjNodesList (*outNodes_const)(haxorg_GraphMapGraph, OrgContext*, haxorg_GraphMapNode);
  haxorg_GraphAdjNodesList (*inNodes_const)(haxorg_GraphMapGraph, OrgContext*, haxorg_GraphMapNode);
  haxorg_HstdVec (*adjEdges_const)(haxorg_GraphMapGraph, OrgContext*, haxorg_GraphMapNode);
  haxorg_HstdVec (*adjNodes_const)(haxorg_GraphMapGraph, OrgContext*, haxorg_GraphMapNode);
  haxorg_HstdVec (*outEdges_const)(haxorg_GraphMapGraph, OrgContext*, haxorg_GraphMapNode);
  haxorg_HstdVec (*inEdges_const)(haxorg_GraphMapGraph, OrgContext*, haxorg_GraphMapNode);
  int (*outDegree_const)(haxorg_GraphMapGraph, OrgContext*, haxorg_GraphMapNode);
  int (*inDegree_const)(haxorg_GraphMapGraph, OrgContext*, haxorg_GraphMapNode);
  bool (*isRegisteredNode_const)(haxorg_GraphMapGraph, OrgContext*, haxorg_GraphMapNode);
  bool (*isRegisteredNodeById_const)(haxorg_GraphMapGraph, OrgContext*, haxorg_ImmUniqId);
  haxorg_GraphMapNodeProp (*atMapNode_const)(haxorg_GraphMapGraph, OrgContext*, haxorg_GraphMapNode);
  haxorg_GraphMapEdgeProp (*atMapEdge_const)(haxorg_GraphMapGraph, OrgContext*, haxorg_GraphMapEdge);
  void (*addEdge)(haxorg_GraphMapGraph, OrgContext*, haxorg_GraphMapEdge);
  void (*addEdgeWithProp)(haxorg_GraphMapGraph, OrgContext*, haxorg_GraphMapEdge, haxorg_GraphMapEdgeProp);
  void (*addNode)(haxorg_GraphMapGraph, OrgContext*, haxorg_GraphMapNode);
  void (*addNodeWithProp)(haxorg_GraphMapGraph, OrgContext*, haxorg_GraphMapNode, haxorg_GraphMapNodeProp);
  bool (*hasEdge_const)(haxorg_GraphMapGraph, OrgContext*, haxorg_GraphMapNode, haxorg_GraphMapNode);
  bool (*hasNode_const)(haxorg_GraphMapGraph, OrgContext*, haxorg_GraphMapNode);
  bool (*has2AdapterEdge_const)(haxorg_GraphMapGraph, OrgContext*, haxorg_ImmAdapter, haxorg_ImmAdapter);
};

struct haxorg_GraphMapConfig_vtable {
  haxorg_OperationsTracer const* (*get_dbg)(haxorg_GraphMapConfig const*, OrgContext*);
};

struct haxorg_ImmSubtreeAdapter_vtable {
  int (*getLevel_const)(haxorg_ImmSubtreeAdapter, OrgContext*);
  haxorg_HstdOpt (*getTreeId_const)(haxorg_ImmSubtreeAdapter, OrgContext*);
  haxorg_HstdOpt (*getTodo_const)(haxorg_ImmSubtreeAdapter, OrgContext*);
  haxorg_HstdOpt (*getCompletion_const)(haxorg_ImmSubtreeAdapter, OrgContext*);
  haxorg_HstdOpt (*getDescription_const)(haxorg_ImmSubtreeAdapter, OrgContext*);
  haxorg_ImmVec (*getTags_const)(haxorg_ImmSubtreeAdapter, OrgContext*);
  haxorg_ImmAdapter (*getTitle_const)(haxorg_ImmSubtreeAdapter, OrgContext*);
  haxorg_ImmVec (*getLogbook_const)(haxorg_ImmSubtreeAdapter, OrgContext*);
  haxorg_ImmVec (*getProperties_const)(haxorg_ImmSubtreeAdapter, OrgContext*);
  haxorg_HstdOpt (*getClosed_const)(haxorg_ImmSubtreeAdapter, OrgContext*);
  haxorg_HstdOpt (*getDeadline_const)(haxorg_ImmSubtreeAdapter, OrgContext*);
  haxorg_HstdOpt (*getScheduled_const)(haxorg_ImmSubtreeAdapter, OrgContext*);
  bool (*getIsComment_const)(haxorg_ImmSubtreeAdapter, OrgContext*);
  bool (*getIsArchived_const)(haxorg_ImmSubtreeAdapter, OrgContext*);
  haxorg_HstdOpt (*getPriority_const)(haxorg_ImmSubtreeAdapter, OrgContext*);
};

struct haxorg_GraphMapGraphState_vtable {
  haxorg_GraphMapGraph const* (*get_graph)(haxorg_GraphMapGraphState const*, OrgContext*);
  haxorg_ImmAstContext const* (*get_ast)(haxorg_GraphMapGraphState const*, OrgContext*);
  haxorg_GraphMapGraph (*getGraph_const)(haxorg_GraphMapGraphState, OrgContext*);
  haxorg_GraphMapGraphState (*FromAstContext)(haxorg_GraphMapGraphState, OrgContext*, haxorg_ImmAstContext);
  void (*registerNode)(haxorg_GraphMapGraphState, OrgContext*, haxorg_GraphMapNodeProp, haxorg_GraphMapConfig);
  void (*addNode)(haxorg_GraphMapGraphState, OrgContext*, haxorg_ImmAdapter, haxorg_GraphMapConfig);
  void (*addNodeRec)(haxorg_GraphMapGraphState, OrgContext*, haxorg_ImmAstContext, haxorg_ImmAdapter, haxorg_GraphMapConfig);
  haxorg_HstdVec (*getUnresolvedSubtreeLinks_const)(haxorg_GraphMapGraphState, OrgContext*, haxorg_ImmSubtreeAdapter, haxorg_GraphMapConfig);
  haxorg_StdOptional (*getUnresolvedLink_const)(haxorg_GraphMapGraphState, OrgContext*, haxorg_ImmLinkAdapter, haxorg_GraphMapConfig);
};

struct haxorg_LispCodeCall_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_LispCodeCall const*, OrgContext*);
  haxorg_HstdVec const* (*get_args)(haxorg_LispCodeCall const*, OrgContext*);
  bool (*__eq___const)(haxorg_LispCodeCall, OrgContext*, haxorg_LispCodeCall);
};

struct haxorg_LispCodeList_vtable {
  haxorg_HstdVec const* (*get_items)(haxorg_LispCodeList const*, OrgContext*);
  bool (*__eq___const)(haxorg_LispCodeList, OrgContext*, haxorg_LispCodeList);
};

struct haxorg_LispCodeKeyValue_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_LispCodeKeyValue const*, OrgContext*);
  haxorg_HstdVec const* (*get_value)(haxorg_LispCodeKeyValue const*, OrgContext*);
  bool (*__eq___const)(haxorg_LispCodeKeyValue, OrgContext*, haxorg_LispCodeKeyValue);
};

struct haxorg_LispCodeNumber_vtable {
  int const* (*get_value)(haxorg_LispCodeNumber const*, OrgContext*);
  bool (*__eq___const)(haxorg_LispCodeNumber, OrgContext*, haxorg_LispCodeNumber);
};

struct haxorg_LispCodeText_vtable {
  haxorg_HstdStr const* (*get_value)(haxorg_LispCodeText const*, OrgContext*);
  bool (*__eq___const)(haxorg_LispCodeText, OrgContext*, haxorg_LispCodeText);
};

struct haxorg_LispCodeIdent_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_LispCodeIdent const*, OrgContext*);
  bool (*__eq___const)(haxorg_LispCodeIdent, OrgContext*, haxorg_LispCodeIdent);
};

struct haxorg_LispCodeBoolean_vtable {
  bool const* (*get_value)(haxorg_LispCodeBoolean const*, OrgContext*);
  bool (*__eq___const)(haxorg_LispCodeBoolean, OrgContext*, haxorg_LispCodeBoolean);
};

struct haxorg_LispCodeReal_vtable {
  float const* (*get_value)(haxorg_LispCodeReal const*, OrgContext*);
  bool (*__eq___const)(haxorg_LispCodeReal, OrgContext*, haxorg_LispCodeReal);
};

struct haxorg_LispCode_vtable {
  bool (*__eq___const)(haxorg_LispCode, OrgContext*, haxorg_LispCode);
  bool (*isCall_const)(haxorg_LispCode, OrgContext*);
  haxorg_LispCodeCall (*getCallConst_const)(haxorg_LispCode, OrgContext*);
  haxorg_LispCodeCall (*getCallMut)(haxorg_LispCode, OrgContext*);
  bool (*isList_const)(haxorg_LispCode, OrgContext*);
  haxorg_LispCodeList (*getListConst_const)(haxorg_LispCode, OrgContext*);
  haxorg_LispCodeList (*getListMut)(haxorg_LispCode, OrgContext*);
  bool (*isKeyValue_const)(haxorg_LispCode, OrgContext*);
  haxorg_LispCodeKeyValue (*getKeyValueConst_const)(haxorg_LispCode, OrgContext*);
  haxorg_LispCodeKeyValue (*getKeyValueMut)(haxorg_LispCode, OrgContext*);
  bool (*isNumber_const)(haxorg_LispCode, OrgContext*);
  haxorg_LispCodeNumber (*getNumberConst_const)(haxorg_LispCode, OrgContext*);
  haxorg_LispCodeNumber (*getNumberMut)(haxorg_LispCode, OrgContext*);
  bool (*isText_const)(haxorg_LispCode, OrgContext*);
  haxorg_LispCodeText (*getTextConst_const)(haxorg_LispCode, OrgContext*);
  haxorg_LispCodeText (*getTextMut)(haxorg_LispCode, OrgContext*);
  bool (*isIdent_const)(haxorg_LispCode, OrgContext*);
  haxorg_LispCodeIdent (*getIdentConst_const)(haxorg_LispCode, OrgContext*);
  haxorg_LispCodeIdent (*getIdentMut)(haxorg_LispCode, OrgContext*);
  bool (*isBoolean_const)(haxorg_LispCode, OrgContext*);
  haxorg_LispCodeBoolean (*getBooleanConst_const)(haxorg_LispCode, OrgContext*);
  haxorg_LispCodeBoolean (*getBooleanMut)(haxorg_LispCode, OrgContext*);
  bool (*isReal_const)(haxorg_LispCode, OrgContext*);
  haxorg_LispCodeReal (*getRealConst_const)(haxorg_LispCode, OrgContext*);
  haxorg_LispCodeReal (*getRealMut)(haxorg_LispCode, OrgContext*);
  haxorg_LispCodeKind (*getKind_const)(haxorg_LispCode, OrgContext*);
};

struct haxorg_TblfmExprAxisRefPositionIndex_vtable {
  int const* (*get_index)(haxorg_TblfmExprAxisRefPositionIndex const*, OrgContext*);
  bool (*__eq___const)(haxorg_TblfmExprAxisRefPositionIndex, OrgContext*, haxorg_TblfmExprAxisRefPositionIndex);
};

struct haxorg_TblfmExprAxisRefPositionName_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_TblfmExprAxisRefPositionName const*, OrgContext*);
  bool (*__eq___const)(haxorg_TblfmExprAxisRefPositionName, OrgContext*, haxorg_TblfmExprAxisRefPositionName);
};

struct haxorg_TblfmExprAxisRefPosition_vtable {
  bool (*__eq___const)(haxorg_TblfmExprAxisRefPosition, OrgContext*, haxorg_TblfmExprAxisRefPosition);
  bool (*isIndex_const)(haxorg_TblfmExprAxisRefPosition, OrgContext*);
  haxorg_TblfmExprAxisRefPositionIndex (*getIndexConst_const)(haxorg_TblfmExprAxisRefPosition, OrgContext*);
  haxorg_TblfmExprAxisRefPositionIndex (*getIndexMut)(haxorg_TblfmExprAxisRefPosition, OrgContext*);
  bool (*isName_const)(haxorg_TblfmExprAxisRefPosition, OrgContext*);
  haxorg_TblfmExprAxisRefPositionName (*getNameConst_const)(haxorg_TblfmExprAxisRefPosition, OrgContext*);
  haxorg_TblfmExprAxisRefPositionName (*getNameMut)(haxorg_TblfmExprAxisRefPosition, OrgContext*);
  haxorg_TblfmExprAxisRefPositionKind (*getKind_const)(haxorg_TblfmExprAxisRefPosition, OrgContext*);
};

struct haxorg_TblfmExprAxisRef_vtable {
  haxorg_TblfmExprAxisRefPosition const* (*get_col)(haxorg_TblfmExprAxisRef const*, OrgContext*);
  haxorg_HstdOpt const* (*get_row)(haxorg_TblfmExprAxisRef const*, OrgContext*);
  bool (*__eq___const)(haxorg_TblfmExprAxisRef, OrgContext*, haxorg_TblfmExprAxisRef);
};

struct haxorg_TblfmExprAxisName_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_TblfmExprAxisName const*, OrgContext*);
  bool (*__eq___const)(haxorg_TblfmExprAxisName, OrgContext*, haxorg_TblfmExprAxisName);
};

struct haxorg_TblfmExprIntLiteral_vtable {
  int const* (*get_value)(haxorg_TblfmExprIntLiteral const*, OrgContext*);
  bool (*__eq___const)(haxorg_TblfmExprIntLiteral, OrgContext*, haxorg_TblfmExprIntLiteral);
};

struct haxorg_TblfmExprFloatLiteral_vtable {
  float const* (*get_value)(haxorg_TblfmExprFloatLiteral const*, OrgContext*);
  bool (*__eq___const)(haxorg_TblfmExprFloatLiteral, OrgContext*, haxorg_TblfmExprFloatLiteral);
};

struct haxorg_TblfmExprRangeRef_vtable {
  haxorg_HstdOpt const* (*get_first)(haxorg_TblfmExprRangeRef const*, OrgContext*);
  haxorg_HstdOpt const* (*get_last)(haxorg_TblfmExprRangeRef const*, OrgContext*);
  bool (*__eq___const)(haxorg_TblfmExprRangeRef, OrgContext*, haxorg_TblfmExprRangeRef);
};

struct haxorg_TblfmExprCall_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_TblfmExprCall const*, OrgContext*);
  haxorg_HstdVec const* (*get_args)(haxorg_TblfmExprCall const*, OrgContext*);
  bool (*__eq___const)(haxorg_TblfmExprCall, OrgContext*, haxorg_TblfmExprCall);
};

struct haxorg_TblfmExprElisp_vtable {
  haxorg_HstdStr const* (*get_value)(haxorg_TblfmExprElisp const*, OrgContext*);
  bool (*__eq___const)(haxorg_TblfmExprElisp, OrgContext*, haxorg_TblfmExprElisp);
};

struct haxorg_TblfmExpr_vtable {
  bool (*__eq___const)(haxorg_TblfmExpr, OrgContext*, haxorg_TblfmExpr);
  bool (*isAxisRef_const)(haxorg_TblfmExpr, OrgContext*);
  haxorg_TblfmExprAxisRef (*getAxisRefConst_const)(haxorg_TblfmExpr, OrgContext*);
  haxorg_TblfmExprAxisRef (*getAxisRefMut)(haxorg_TblfmExpr, OrgContext*);
  bool (*isAxisName_const)(haxorg_TblfmExpr, OrgContext*);
  haxorg_TblfmExprAxisName (*getAxisNameConst_const)(haxorg_TblfmExpr, OrgContext*);
  haxorg_TblfmExprAxisName (*getAxisNameMut)(haxorg_TblfmExpr, OrgContext*);
  bool (*isIntLiteral_const)(haxorg_TblfmExpr, OrgContext*);
  haxorg_TblfmExprIntLiteral (*getIntLiteralConst_const)(haxorg_TblfmExpr, OrgContext*);
  haxorg_TblfmExprIntLiteral (*getIntLiteralMut)(haxorg_TblfmExpr, OrgContext*);
  bool (*isFloatLiteral_const)(haxorg_TblfmExpr, OrgContext*);
  haxorg_TblfmExprFloatLiteral (*getFloatLiteralConst_const)(haxorg_TblfmExpr, OrgContext*);
  haxorg_TblfmExprFloatLiteral (*getFloatLiteralMut)(haxorg_TblfmExpr, OrgContext*);
  bool (*isRangeRef_const)(haxorg_TblfmExpr, OrgContext*);
  haxorg_TblfmExprRangeRef (*getRangeRefConst_const)(haxorg_TblfmExpr, OrgContext*);
  haxorg_TblfmExprRangeRef (*getRangeRefMut)(haxorg_TblfmExpr, OrgContext*);
  bool (*isCall_const)(haxorg_TblfmExpr, OrgContext*);
  haxorg_TblfmExprCall (*getCallConst_const)(haxorg_TblfmExpr, OrgContext*);
  haxorg_TblfmExprCall (*getCallMut)(haxorg_TblfmExpr, OrgContext*);
  bool (*isElisp_const)(haxorg_TblfmExpr, OrgContext*);
  haxorg_TblfmExprElisp (*getElispConst_const)(haxorg_TblfmExpr, OrgContext*);
  haxorg_TblfmExprElisp (*getElispMut)(haxorg_TblfmExpr, OrgContext*);
  haxorg_TblfmExprKind (*getKind_const)(haxorg_TblfmExpr, OrgContext*);
};

struct haxorg_TblfmAssign_vtable {
  haxorg_TblfmExprAxisRef const* (*get_target)(haxorg_TblfmAssign const*, OrgContext*);
  haxorg_HstdVec const* (*get_expr)(haxorg_TblfmAssign const*, OrgContext*);
  haxorg_HstdVec const* (*get_flags)(haxorg_TblfmAssign const*, OrgContext*);
  bool (*__eq___const)(haxorg_TblfmAssign, OrgContext*, haxorg_TblfmAssign);
};

struct haxorg_Tblfm_vtable {
  haxorg_HstdVec const* (*get_exprs)(haxorg_Tblfm const*, OrgContext*);
  bool (*__eq___const)(haxorg_Tblfm, OrgContext*, haxorg_Tblfm);
};

struct haxorg_AttrValueDimensionSpan_vtable {
  int const* (*get_first)(haxorg_AttrValueDimensionSpan const*, OrgContext*);
  haxorg_HstdOpt const* (*get_last)(haxorg_AttrValueDimensionSpan const*, OrgContext*);
  bool (*__eq___const)(haxorg_AttrValueDimensionSpan, OrgContext*, haxorg_AttrValueDimensionSpan);
};

struct haxorg_AttrValueTextValue_vtable {
  haxorg_HstdStr const* (*get_value)(haxorg_AttrValueTextValue const*, OrgContext*);
  bool (*__eq___const)(haxorg_AttrValueTextValue, OrgContext*, haxorg_AttrValueTextValue);
};

struct haxorg_AttrValueFileReference_vtable {
  haxorg_HstdStr const* (*get_file)(haxorg_AttrValueFileReference const*, OrgContext*);
  haxorg_HstdStr const* (*get_reference)(haxorg_AttrValueFileReference const*, OrgContext*);
  bool (*__eq___const)(haxorg_AttrValueFileReference, OrgContext*, haxorg_AttrValueFileReference);
};

struct haxorg_AttrValueLispValue_vtable {
  haxorg_LispCode const* (*get_code)(haxorg_AttrValueLispValue const*, OrgContext*);
  bool (*__eq___const)(haxorg_AttrValueLispValue, OrgContext*, haxorg_AttrValueLispValue);
};

struct haxorg_AttrValue_vtable {
  haxorg_HstdOpt const* (*get_name)(haxorg_AttrValue const*, OrgContext*);
  haxorg_HstdOpt const* (*get_varname)(haxorg_AttrValue const*, OrgContext*);
  haxorg_HstdVec const* (*get_span)(haxorg_AttrValue const*, OrgContext*);
  bool const* (*get_isQuoted)(haxorg_AttrValue const*, OrgContext*);
  haxorg_HstdOpt (*getBool_const)(haxorg_AttrValue, OrgContext*);
  haxorg_HstdOpt (*getInt_const)(haxorg_AttrValue, OrgContext*);
  haxorg_HstdStr (*getString_const)(haxorg_AttrValue, OrgContext*);
  haxorg_HstdOpt (*getDouble_const)(haxorg_AttrValue, OrgContext*);
  bool (*__eq___const)(haxorg_AttrValue, OrgContext*, haxorg_AttrValue);
  bool (*isTextValue_const)(haxorg_AttrValue, OrgContext*);
  haxorg_AttrValueTextValue (*getTextValueConst_const)(haxorg_AttrValue, OrgContext*);
  haxorg_AttrValueTextValue (*getTextValueMut)(haxorg_AttrValue, OrgContext*);
  bool (*isFileReference_const)(haxorg_AttrValue, OrgContext*);
  haxorg_AttrValueFileReference (*getFileReferenceConst_const)(haxorg_AttrValue, OrgContext*);
  haxorg_AttrValueFileReference (*getFileReferenceMut)(haxorg_AttrValue, OrgContext*);
  bool (*isLispValue_const)(haxorg_AttrValue, OrgContext*);
  haxorg_AttrValueLispValue (*getLispValueConst_const)(haxorg_AttrValue, OrgContext*);
  haxorg_AttrValueLispValue (*getLispValueMut)(haxorg_AttrValue, OrgContext*);
  haxorg_AttrValueKind (*getKind_const)(haxorg_AttrValue, OrgContext*);
};

struct haxorg_HashTagFlat_vtable {
  haxorg_HstdVec const* (*get_tags)(haxorg_HashTagFlat const*, OrgContext*);
  bool (*__eq___const)(haxorg_HashTagFlat, OrgContext*, haxorg_HashTagFlat);
  bool (*__lt___const)(haxorg_HashTagFlat, OrgContext*, haxorg_HashTagFlat);
};

struct haxorg_TodoKeyword_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_TodoKeyword const*, OrgContext*);
  haxorg_HstdOpt const* (*get_shortcut)(haxorg_TodoKeyword const*, OrgContext*);
  haxorg_TodoKeywordTransition const* (*get_onEnter)(haxorg_TodoKeyword const*, OrgContext*);
  haxorg_TodoKeywordTransition const* (*get_onLeave)(haxorg_TodoKeyword const*, OrgContext*);
  bool (*__eq___const)(haxorg_TodoKeyword, OrgContext*, haxorg_TodoKeyword);
};

struct haxorg_HashTagText_vtable {
  haxorg_HstdStr const* (*get_head)(haxorg_HashTagText const*, OrgContext*);
  haxorg_HstdVec const* (*get_subtags)(haxorg_HashTagText const*, OrgContext*);
  bool (*__eq___const)(haxorg_HashTagText, OrgContext*, haxorg_HashTagText);
  bool (*prefixMatch_const)(haxorg_HashTagText, OrgContext*, haxorg_HstdVec);
  haxorg_HstdVec (*getFlatHashes_const)(haxorg_HashTagText, OrgContext*, bool);
};

struct haxorg_SubtreePath_vtable {
  haxorg_HstdVec const* (*get_path)(haxorg_SubtreePath const*, OrgContext*);
  bool (*__eq___const)(haxorg_SubtreePath, OrgContext*, haxorg_SubtreePath);
};

struct haxorg_LinkTargetRaw_vtable {
  haxorg_HstdStr const* (*get_text)(haxorg_LinkTargetRaw const*, OrgContext*);
  bool (*__eq___const)(haxorg_LinkTargetRaw, OrgContext*, haxorg_LinkTargetRaw);
};

struct haxorg_LinkTargetId_vtable {
  haxorg_HstdStr const* (*get_text)(haxorg_LinkTargetId const*, OrgContext*);
  bool (*__eq___const)(haxorg_LinkTargetId, OrgContext*, haxorg_LinkTargetId);
};

struct haxorg_LinkTargetCustomId_vtable {
  haxorg_HstdStr const* (*get_text)(haxorg_LinkTargetCustomId const*, OrgContext*);
  bool (*__eq___const)(haxorg_LinkTargetCustomId, OrgContext*, haxorg_LinkTargetCustomId);
};

struct haxorg_LinkTargetSubtreeTitle_vtable {
  haxorg_SubtreePath const* (*get_title)(haxorg_LinkTargetSubtreeTitle const*, OrgContext*);
  int const* (*get_level)(haxorg_LinkTargetSubtreeTitle const*, OrgContext*);
  bool (*__eq___const)(haxorg_LinkTargetSubtreeTitle, OrgContext*, haxorg_LinkTargetSubtreeTitle);
};

struct haxorg_LinkTargetPerson_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_LinkTargetPerson const*, OrgContext*);
  bool (*__eq___const)(haxorg_LinkTargetPerson, OrgContext*, haxorg_LinkTargetPerson);
};

struct haxorg_LinkTargetUserProtocol_vtable {
  haxorg_HstdStr const* (*get_protocol)(haxorg_LinkTargetUserProtocol const*, OrgContext*);
  haxorg_HstdStr const* (*get_target)(haxorg_LinkTargetUserProtocol const*, OrgContext*);
  bool (*__eq___const)(haxorg_LinkTargetUserProtocol, OrgContext*, haxorg_LinkTargetUserProtocol);
};

struct haxorg_LinkTargetInternal_vtable {
  haxorg_HstdStr const* (*get_target)(haxorg_LinkTargetInternal const*, OrgContext*);
  bool (*__eq___const)(haxorg_LinkTargetInternal, OrgContext*, haxorg_LinkTargetInternal);
};

struct haxorg_LinkTargetFootnote_vtable {
  haxorg_HstdStr const* (*get_target)(haxorg_LinkTargetFootnote const*, OrgContext*);
  bool (*__eq___const)(haxorg_LinkTargetFootnote, OrgContext*, haxorg_LinkTargetFootnote);
};

struct haxorg_LinkTargetFile_vtable {
  haxorg_HstdStr const* (*get_file)(haxorg_LinkTargetFile const*, OrgContext*);
  bool (*__eq___const)(haxorg_LinkTargetFile, OrgContext*, haxorg_LinkTargetFile);
};

struct haxorg_LinkTargetAttachment_vtable {
  haxorg_HstdStr const* (*get_file)(haxorg_LinkTargetAttachment const*, OrgContext*);
  bool (*__eq___const)(haxorg_LinkTargetAttachment, OrgContext*, haxorg_LinkTargetAttachment);
};

struct haxorg_LinkTarget_vtable {
  bool (*__eq___const)(haxorg_LinkTarget, OrgContext*, haxorg_LinkTarget);
  bool (*isRaw_const)(haxorg_LinkTarget, OrgContext*);
  haxorg_LinkTargetRaw (*getRawConst_const)(haxorg_LinkTarget, OrgContext*);
  haxorg_LinkTargetRaw (*getRawMut)(haxorg_LinkTarget, OrgContext*);
  bool (*isId_const)(haxorg_LinkTarget, OrgContext*);
  haxorg_LinkTargetId (*getIdConst_const)(haxorg_LinkTarget, OrgContext*);
  haxorg_LinkTargetId (*getIdMut)(haxorg_LinkTarget, OrgContext*);
  bool (*isCustomId_const)(haxorg_LinkTarget, OrgContext*);
  haxorg_LinkTargetCustomId (*getCustomIdConst_const)(haxorg_LinkTarget, OrgContext*);
  haxorg_LinkTargetCustomId (*getCustomIdMut)(haxorg_LinkTarget, OrgContext*);
  bool (*isSubtreeTitle_const)(haxorg_LinkTarget, OrgContext*);
  haxorg_LinkTargetSubtreeTitle (*getSubtreeTitleConst_const)(haxorg_LinkTarget, OrgContext*);
  haxorg_LinkTargetSubtreeTitle (*getSubtreeTitleMut)(haxorg_LinkTarget, OrgContext*);
  bool (*isPerson_const)(haxorg_LinkTarget, OrgContext*);
  haxorg_LinkTargetPerson (*getPersonConst_const)(haxorg_LinkTarget, OrgContext*);
  haxorg_LinkTargetPerson (*getPersonMut)(haxorg_LinkTarget, OrgContext*);
  bool (*isUserProtocol_const)(haxorg_LinkTarget, OrgContext*);
  haxorg_LinkTargetUserProtocol (*getUserProtocolConst_const)(haxorg_LinkTarget, OrgContext*);
  haxorg_LinkTargetUserProtocol (*getUserProtocolMut)(haxorg_LinkTarget, OrgContext*);
  bool (*isInternal_const)(haxorg_LinkTarget, OrgContext*);
  haxorg_LinkTargetInternal (*getInternalConst_const)(haxorg_LinkTarget, OrgContext*);
  haxorg_LinkTargetInternal (*getInternalMut)(haxorg_LinkTarget, OrgContext*);
  bool (*isFootnote_const)(haxorg_LinkTarget, OrgContext*);
  haxorg_LinkTargetFootnote (*getFootnoteConst_const)(haxorg_LinkTarget, OrgContext*);
  haxorg_LinkTargetFootnote (*getFootnoteMut)(haxorg_LinkTarget, OrgContext*);
  bool (*isFile_const)(haxorg_LinkTarget, OrgContext*);
  haxorg_LinkTargetFile (*getFileConst_const)(haxorg_LinkTarget, OrgContext*);
  haxorg_LinkTargetFile (*getFileMut)(haxorg_LinkTarget, OrgContext*);
  bool (*isAttachment_const)(haxorg_LinkTarget, OrgContext*);
  haxorg_LinkTargetAttachment (*getAttachmentConst_const)(haxorg_LinkTarget, OrgContext*);
  haxorg_LinkTargetAttachment (*getAttachmentMut)(haxorg_LinkTarget, OrgContext*);
  haxorg_LinkTargetKind (*getKind_const)(haxorg_LinkTarget, OrgContext*);
};

struct haxorg_ImmLinkAdapter_vtable {
  haxorg_HstdOpt (*getDescription_const)(haxorg_ImmLinkAdapter, OrgContext*);
  haxorg_LinkTarget (*getTarget_const)(haxorg_ImmLinkAdapter, OrgContext*);
};

struct haxorg_SubtreeLogHeadPriority_vtable {
  haxorg_HstdOpt const* (*get_oldPriority)(haxorg_SubtreeLogHeadPriority const*, OrgContext*);
  haxorg_HstdOpt const* (*get_newPriority)(haxorg_SubtreeLogHeadPriority const*, OrgContext*);
  haxorg_UserTime const* (*get_on)(haxorg_SubtreeLogHeadPriority const*, OrgContext*);
  haxorg_SubtreeLogHeadPriorityAction const* (*get_action)(haxorg_SubtreeLogHeadPriority const*, OrgContext*);
  bool (*__eq___const)(haxorg_SubtreeLogHeadPriority, OrgContext*, haxorg_SubtreeLogHeadPriority);
};

struct haxorg_SubtreeLogHeadNote_vtable {
  haxorg_UserTime const* (*get_on)(haxorg_SubtreeLogHeadNote const*, OrgContext*);
  bool (*__eq___const)(haxorg_SubtreeLogHeadNote, OrgContext*, haxorg_SubtreeLogHeadNote);
};

struct haxorg_SubtreeLogHeadRefile_vtable {
  haxorg_UserTime const* (*get_on)(haxorg_SubtreeLogHeadRefile const*, OrgContext*);
  haxorg_LinkTarget const* (*get_from)(haxorg_SubtreeLogHeadRefile const*, OrgContext*);
  bool (*__eq___const)(haxorg_SubtreeLogHeadRefile, OrgContext*, haxorg_SubtreeLogHeadRefile);
};

struct haxorg_SubtreeLogHeadClock_vtable {
  haxorg_UserTime const* (*get_from)(haxorg_SubtreeLogHeadClock const*, OrgContext*);
  haxorg_HstdOpt const* (*get_to)(haxorg_SubtreeLogHeadClock const*, OrgContext*);
  bool (*__eq___const)(haxorg_SubtreeLogHeadClock, OrgContext*, haxorg_SubtreeLogHeadClock);
};

struct haxorg_SubtreeLogHeadState_vtable {
  haxorg_HstdStr const* (*get_from)(haxorg_SubtreeLogHeadState const*, OrgContext*);
  haxorg_HstdStr const* (*get_to)(haxorg_SubtreeLogHeadState const*, OrgContext*);
  haxorg_UserTime const* (*get_on)(haxorg_SubtreeLogHeadState const*, OrgContext*);
  bool (*__eq___const)(haxorg_SubtreeLogHeadState, OrgContext*, haxorg_SubtreeLogHeadState);
};

struct haxorg_SubtreeLogHeadDeadline_vtable {
  haxorg_HstdOpt const* (*get_from)(haxorg_SubtreeLogHeadDeadline const*, OrgContext*);
  haxorg_UserTime const* (*get_to)(haxorg_SubtreeLogHeadDeadline const*, OrgContext*);
  haxorg_UserTime const* (*get_on)(haxorg_SubtreeLogHeadDeadline const*, OrgContext*);
  bool (*__eq___const)(haxorg_SubtreeLogHeadDeadline, OrgContext*, haxorg_SubtreeLogHeadDeadline);
};

struct haxorg_SubtreeLogHeadSchedule_vtable {
  haxorg_HstdOpt const* (*get_from)(haxorg_SubtreeLogHeadSchedule const*, OrgContext*);
  haxorg_UserTime const* (*get_to)(haxorg_SubtreeLogHeadSchedule const*, OrgContext*);
  haxorg_UserTime const* (*get_on)(haxorg_SubtreeLogHeadSchedule const*, OrgContext*);
  bool (*__eq___const)(haxorg_SubtreeLogHeadSchedule, OrgContext*, haxorg_SubtreeLogHeadSchedule);
};

struct haxorg_SubtreeLogHeadTag_vtable {
  haxorg_UserTime const* (*get_on)(haxorg_SubtreeLogHeadTag const*, OrgContext*);
  haxorg_HashTagText const* (*get_tag)(haxorg_SubtreeLogHeadTag const*, OrgContext*);
  bool const* (*get_added)(haxorg_SubtreeLogHeadTag const*, OrgContext*);
  bool (*__eq___const)(haxorg_SubtreeLogHeadTag, OrgContext*, haxorg_SubtreeLogHeadTag);
};

struct haxorg_SubtreeLogHeadUnknown_vtable {
  bool (*__eq___const)(haxorg_SubtreeLogHeadUnknown, OrgContext*, haxorg_SubtreeLogHeadUnknown);
};

struct haxorg_SubtreeLogHead_vtable {
  bool (*__eq___const)(haxorg_SubtreeLogHead, OrgContext*, haxorg_SubtreeLogHead);
  bool (*isPriority_const)(haxorg_SubtreeLogHead, OrgContext*);
  haxorg_SubtreeLogHeadPriority (*getPriorityConst_const)(haxorg_SubtreeLogHead, OrgContext*);
  haxorg_SubtreeLogHeadPriority (*getPriorityMut)(haxorg_SubtreeLogHead, OrgContext*);
  bool (*isNote_const)(haxorg_SubtreeLogHead, OrgContext*);
  haxorg_SubtreeLogHeadNote (*getNoteConst_const)(haxorg_SubtreeLogHead, OrgContext*);
  haxorg_SubtreeLogHeadNote (*getNoteMut)(haxorg_SubtreeLogHead, OrgContext*);
  bool (*isRefile_const)(haxorg_SubtreeLogHead, OrgContext*);
  haxorg_SubtreeLogHeadRefile (*getRefileConst_const)(haxorg_SubtreeLogHead, OrgContext*);
  haxorg_SubtreeLogHeadRefile (*getRefileMut)(haxorg_SubtreeLogHead, OrgContext*);
  bool (*isClock_const)(haxorg_SubtreeLogHead, OrgContext*);
  haxorg_SubtreeLogHeadClock (*getClockConst_const)(haxorg_SubtreeLogHead, OrgContext*);
  haxorg_SubtreeLogHeadClock (*getClockMut)(haxorg_SubtreeLogHead, OrgContext*);
  bool (*isState_const)(haxorg_SubtreeLogHead, OrgContext*);
  haxorg_SubtreeLogHeadState (*getStateConst_const)(haxorg_SubtreeLogHead, OrgContext*);
  haxorg_SubtreeLogHeadState (*getStateMut)(haxorg_SubtreeLogHead, OrgContext*);
  bool (*isDeadline_const)(haxorg_SubtreeLogHead, OrgContext*);
  haxorg_SubtreeLogHeadDeadline (*getDeadlineConst_const)(haxorg_SubtreeLogHead, OrgContext*);
  haxorg_SubtreeLogHeadDeadline (*getDeadlineMut)(haxorg_SubtreeLogHead, OrgContext*);
  bool (*isSchedule_const)(haxorg_SubtreeLogHead, OrgContext*);
  haxorg_SubtreeLogHeadSchedule (*getScheduleConst_const)(haxorg_SubtreeLogHead, OrgContext*);
  haxorg_SubtreeLogHeadSchedule (*getScheduleMut)(haxorg_SubtreeLogHead, OrgContext*);
  bool (*isTag_const)(haxorg_SubtreeLogHead, OrgContext*);
  haxorg_SubtreeLogHeadTag (*getTagConst_const)(haxorg_SubtreeLogHead, OrgContext*);
  haxorg_SubtreeLogHeadTag (*getTagMut)(haxorg_SubtreeLogHead, OrgContext*);
  bool (*isUnknown_const)(haxorg_SubtreeLogHead, OrgContext*);
  haxorg_SubtreeLogHeadUnknown (*getUnknownConst_const)(haxorg_SubtreeLogHead, OrgContext*);
  haxorg_SubtreeLogHeadUnknown (*getUnknownMut)(haxorg_SubtreeLogHead, OrgContext*);
  haxorg_SubtreeLogHeadKind (*getLogKind_const)(haxorg_SubtreeLogHead, OrgContext*);
};

struct haxorg_SubtreeCompletion_vtable {
  int const* (*get_done)(haxorg_SubtreeCompletion const*, OrgContext*);
  int const* (*get_full)(haxorg_SubtreeCompletion const*, OrgContext*);
  bool const* (*get_isPercent)(haxorg_SubtreeCompletion const*, OrgContext*);
  bool (*__eq___const)(haxorg_SubtreeCompletion, OrgContext*, haxorg_SubtreeCompletion);
};

struct haxorg_AttrList_vtable {
  haxorg_HstdVec const* (*get_items)(haxorg_AttrList const*, OrgContext*);
  bool (*__eq___const)(haxorg_AttrList, OrgContext*, haxorg_AttrList);
};

struct haxorg_AttrGroup_vtable {
  haxorg_AttrList const* (*get_positional)(haxorg_AttrGroup const*, OrgContext*);
  haxorg_HstdUnorderedMap const* (*get_named)(haxorg_AttrGroup const*, OrgContext*);
  haxorg_HstdVec (*getFlatArgs_const)(haxorg_AttrGroup, OrgContext*);
  haxorg_HstdVec (*getAttrs_const)(haxorg_AttrGroup, OrgContext*, haxorg_HstdOpt);
  void (*setNamedAttr)(haxorg_AttrGroup, OrgContext*, haxorg_HstdStr, haxorg_HstdVec);
  void (*setPositionalAttr)(haxorg_AttrGroup, OrgContext*, haxorg_HstdVec);
  int (*getPositionalSize_const)(haxorg_AttrGroup, OrgContext*);
  int (*getNamedSize_const)(haxorg_AttrGroup, OrgContext*);
  bool (*isEmpty_const)(haxorg_AttrGroup, OrgContext*);
  haxorg_AttrList (*getAll_const)(haxorg_AttrGroup, OrgContext*);
  haxorg_AttrValue (*atPositional_const)(haxorg_AttrGroup, OrgContext*, int);
  haxorg_HstdOpt (*getPositional_const)(haxorg_AttrGroup, OrgContext*, int);
  haxorg_AttrList (*atNamed_const)(haxorg_AttrGroup, OrgContext*, haxorg_HstdStr);
  haxorg_HstdOpt (*getNamed_const)(haxorg_AttrGroup, OrgContext*, haxorg_HstdStr);
  haxorg_AttrValue (*atFirstNamed_const)(haxorg_AttrGroup, OrgContext*, haxorg_HstdStr);
  haxorg_HstdOpt (*getFirstNamed_const)(haxorg_AttrGroup, OrgContext*, haxorg_HstdStr);
  haxorg_AttrList (*atVarNamed_const)(haxorg_AttrGroup, OrgContext*, haxorg_HstdStr);
  haxorg_HstdOpt (*getVarNamed_const)(haxorg_AttrGroup, OrgContext*, haxorg_HstdStr);
  haxorg_AttrValue (*atFirstVarNamed_const)(haxorg_AttrGroup, OrgContext*, haxorg_HstdStr);
  haxorg_HstdOpt (*getFirstVarNamed_const)(haxorg_AttrGroup, OrgContext*, haxorg_HstdStr);
  bool (*__eq___const)(haxorg_AttrGroup, OrgContext*, haxorg_AttrGroup);
};

struct haxorg_OrgCodeEvalInputVar_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_OrgCodeEvalInputVar const*, OrgContext*);
  haxorg_OrgJson const* (*get_value)(haxorg_OrgCodeEvalInputVar const*, OrgContext*);
  bool (*__eq___const)(haxorg_OrgCodeEvalInputVar, OrgContext*, haxorg_OrgCodeEvalInputVar);
};

struct haxorg_OrgCodeEvalInput_vtable {
  haxorg_AttrGroup const* (*get_blockAttrs)(haxorg_OrgCodeEvalInput const*, OrgContext*);
  haxorg_HstdStr const* (*get_tangledCode)(haxorg_OrgCodeEvalInput const*, OrgContext*);
  haxorg_HstdOpt const* (*get_exportType)(haxorg_OrgCodeEvalInput const*, OrgContext*);
  haxorg_OrgCodeEvalInputResultType const* (*get_resultType)(haxorg_OrgCodeEvalInput const*, OrgContext*);
  haxorg_OrgCodeEvalInputResultFormat const* (*get_resultFormat)(haxorg_OrgCodeEvalInput const*, OrgContext*);
  haxorg_OrgCodeEvalInputResultHandling const* (*get_resultHandling)(haxorg_OrgCodeEvalInput const*, OrgContext*);
  haxorg_HstdStr const* (*get_language)(haxorg_OrgCodeEvalInput const*, OrgContext*);
  haxorg_HstdVec const* (*get_argList)(haxorg_OrgCodeEvalInput const*, OrgContext*);
  bool (*__eq___const)(haxorg_OrgCodeEvalInput, OrgContext*, haxorg_OrgCodeEvalInput);
  haxorg_HstdOpt (*getVariable_const)(haxorg_OrgCodeEvalInput, OrgContext*, haxorg_HstdStr);
};

struct haxorg_OrgCodeEvalOutput_vtable {
  haxorg_HstdStr const* (*get_stdoutText)(haxorg_OrgCodeEvalOutput const*, OrgContext*);
  haxorg_HstdStr const* (*get_stderrText)(haxorg_OrgCodeEvalOutput const*, OrgContext*);
  int const* (*get_code)(haxorg_OrgCodeEvalOutput const*, OrgContext*);
  haxorg_HstdOpt const* (*get_cmd)(haxorg_OrgCodeEvalOutput const*, OrgContext*);
  haxorg_HstdVec const* (*get_args)(haxorg_OrgCodeEvalOutput const*, OrgContext*);
  haxorg_HstdStr const* (*get_cwd)(haxorg_OrgCodeEvalOutput const*, OrgContext*);
  haxorg_AttrGroup const* (*get_appliedHeaderArg)(haxorg_OrgCodeEvalOutput const*, OrgContext*);
  bool (*__eq___const)(haxorg_OrgCodeEvalOutput, OrgContext*, haxorg_OrgCodeEvalOutput);
};

struct haxorg_ColumnViewSummaryCheckboxAggregate_vtable {
  haxorg_ColumnViewSummaryCheckboxAggregateKind const* (*get_kind)(haxorg_ColumnViewSummaryCheckboxAggregate const*, OrgContext*);
  bool (*__eq___const)(haxorg_ColumnViewSummaryCheckboxAggregate, OrgContext*, haxorg_ColumnViewSummaryCheckboxAggregate);
};

struct haxorg_ColumnViewSummaryMathAggregate_vtable {
  haxorg_ColumnViewSummaryMathAggregateKind const* (*get_kind)(haxorg_ColumnViewSummaryMathAggregate const*, OrgContext*);
  haxorg_HstdOpt const* (*get_formatDigits)(haxorg_ColumnViewSummaryMathAggregate const*, OrgContext*);
  haxorg_HstdOpt const* (*get_formatPrecision)(haxorg_ColumnViewSummaryMathAggregate const*, OrgContext*);
  bool (*__eq___const)(haxorg_ColumnViewSummaryMathAggregate, OrgContext*, haxorg_ColumnViewSummaryMathAggregate);
};

struct haxorg_ColumnViewSummary_vtable {
  bool (*__eq___const)(haxorg_ColumnViewSummary, OrgContext*, haxorg_ColumnViewSummary);
  bool (*isCheckboxAggregate_const)(haxorg_ColumnViewSummary, OrgContext*);
  haxorg_ColumnViewSummaryCheckboxAggregate (*getCheckboxAggregateConst_const)(haxorg_ColumnViewSummary, OrgContext*);
  haxorg_ColumnViewSummaryCheckboxAggregate (*getCheckboxAggregateMut)(haxorg_ColumnViewSummary, OrgContext*);
  bool (*isMathAggregate_const)(haxorg_ColumnViewSummary, OrgContext*);
  haxorg_ColumnViewSummaryMathAggregate (*getMathAggregateConst_const)(haxorg_ColumnViewSummary, OrgContext*);
  haxorg_ColumnViewSummaryMathAggregate (*getMathAggregateMut)(haxorg_ColumnViewSummary, OrgContext*);
  haxorg_ColumnViewSummaryKind (*getKind_const)(haxorg_ColumnViewSummary, OrgContext*);
};

struct haxorg_ColumnViewColumn_vtable {
  haxorg_HstdOpt const* (*get_summary)(haxorg_ColumnViewColumn const*, OrgContext*);
  haxorg_HstdOpt const* (*get_width)(haxorg_ColumnViewColumn const*, OrgContext*);
  haxorg_HstdOpt const* (*get_property)(haxorg_ColumnViewColumn const*, OrgContext*);
  haxorg_HstdOpt const* (*get_propertyTitle)(haxorg_ColumnViewColumn const*, OrgContext*);
  bool (*__eq___const)(haxorg_ColumnViewColumn, OrgContext*, haxorg_ColumnViewColumn);
};

struct haxorg_ColumnView_vtable {
  haxorg_HstdVec const* (*get_columns)(haxorg_ColumnView const*, OrgContext*);
  bool (*__eq___const)(haxorg_ColumnView, OrgContext*, haxorg_ColumnView);
};

struct haxorg_BlockCodeLinePartRaw_vtable {
  haxorg_HstdStr const* (*get_code)(haxorg_BlockCodeLinePartRaw const*, OrgContext*);
  bool (*__eq___const)(haxorg_BlockCodeLinePartRaw, OrgContext*, haxorg_BlockCodeLinePartRaw);
};

struct haxorg_BlockCodeLinePartCallout_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_BlockCodeLinePartCallout const*, OrgContext*);
  bool (*__eq___const)(haxorg_BlockCodeLinePartCallout, OrgContext*, haxorg_BlockCodeLinePartCallout);
};

struct haxorg_BlockCodeLinePartTangle_vtable {
  haxorg_HstdStr const* (*get_target)(haxorg_BlockCodeLinePartTangle const*, OrgContext*);
  bool (*__eq___const)(haxorg_BlockCodeLinePartTangle, OrgContext*, haxorg_BlockCodeLinePartTangle);
};

struct haxorg_BlockCodeLinePart_vtable {
  bool (*__eq___const)(haxorg_BlockCodeLinePart, OrgContext*, haxorg_BlockCodeLinePart);
  bool (*isRaw_const)(haxorg_BlockCodeLinePart, OrgContext*);
  haxorg_BlockCodeLinePartRaw (*getRawConst_const)(haxorg_BlockCodeLinePart, OrgContext*);
  haxorg_BlockCodeLinePartRaw (*getRawMut)(haxorg_BlockCodeLinePart, OrgContext*);
  bool (*isCallout_const)(haxorg_BlockCodeLinePart, OrgContext*);
  haxorg_BlockCodeLinePartCallout (*getCalloutConst_const)(haxorg_BlockCodeLinePart, OrgContext*);
  haxorg_BlockCodeLinePartCallout (*getCalloutMut)(haxorg_BlockCodeLinePart, OrgContext*);
  bool (*isTangle_const)(haxorg_BlockCodeLinePart, OrgContext*);
  haxorg_BlockCodeLinePartTangle (*getTangleConst_const)(haxorg_BlockCodeLinePart, OrgContext*);
  haxorg_BlockCodeLinePartTangle (*getTangleMut)(haxorg_BlockCodeLinePart, OrgContext*);
  haxorg_BlockCodeLinePartKind (*getKind_const)(haxorg_BlockCodeLinePart, OrgContext*);
};

struct haxorg_BlockCodeLine_vtable {
  haxorg_HstdVec const* (*get_parts)(haxorg_BlockCodeLine const*, OrgContext*);
  bool (*__eq___const)(haxorg_BlockCodeLine, OrgContext*, haxorg_BlockCodeLine);
};

struct haxorg_DocumentExportConfigTaskExport_vtable {
  haxorg_HstdVec const* (*get_taskWhitelist)(haxorg_DocumentExportConfigTaskExport const*, OrgContext*);
  bool (*__eq___const)(haxorg_DocumentExportConfigTaskExport, OrgContext*, haxorg_DocumentExportConfigTaskExport);
};

struct haxorg_DocumentExportConfigDoExport_vtable {
  bool const* (*get_exportToc)(haxorg_DocumentExportConfigDoExport const*, OrgContext*);
  bool (*__eq___const)(haxorg_DocumentExportConfigDoExport, OrgContext*, haxorg_DocumentExportConfigDoExport);
};

struct haxorg_DocumentExportConfigExportFixed_vtable {
  int const* (*get_exportLevels)(haxorg_DocumentExportConfigExportFixed const*, OrgContext*);
  bool (*__eq___const)(haxorg_DocumentExportConfigExportFixed, OrgContext*, haxorg_DocumentExportConfigExportFixed);
};

struct haxorg_DocumentExportConfig_vtable {
  haxorg_HstdOpt const* (*get_inlinetasks)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_HstdOpt const* (*get_footnotes)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_HstdOpt const* (*get_clock)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_HstdOpt const* (*get_author)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_HstdOpt const* (*get_emphasis)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_HstdOpt const* (*get_specialStrings)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_HstdOpt const* (*get_propertyDrawers)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_HstdOpt const* (*get_statisticsCookies)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_HstdOpt const* (*get_todoText)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_HstdOpt const* (*get_smartQuotes)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_HstdOpt const* (*get_fixedWidth)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_HstdOpt const* (*get_timestamps)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_HstdOpt const* (*get_preserveBreaks)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_HstdOpt const* (*get_subSuperscripts)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_HstdOpt const* (*get_expandLinks)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_HstdOpt const* (*get_creator)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_HstdOpt const* (*get_drawers)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_HstdOpt const* (*get_date)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_HstdOpt const* (*get_entities)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_HstdOpt const* (*get_email)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_HstdOpt const* (*get_sectionNumbers)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_HstdOpt const* (*get_planning)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_HstdOpt const* (*get_priority)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_HstdOpt const* (*get_latex)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_HstdOpt const* (*get_timestamp)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_HstdOpt const* (*get_title)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_HstdOpt const* (*get_tables)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_HstdOpt const* (*get_headlineLevels)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_DocumentExportConfigBrokenLinks const* (*get_brokenLinks)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_DocumentExportConfigTagExport const* (*get_tagExport)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_DocumentExportConfigTaskFiltering const* (*get_taskFiltering)(haxorg_DocumentExportConfig const*, OrgContext*);
  haxorg_DocumentExportConfigArchivedTrees const* (*get_archivedTrees)(haxorg_DocumentExportConfig const*, OrgContext*);
  bool (*__eq___const)(haxorg_DocumentExportConfig, OrgContext*, haxorg_DocumentExportConfig);
  bool (*isDoExport_const)(haxorg_DocumentExportConfig, OrgContext*);
  haxorg_DocumentExportConfigDoExport (*getDoExportConst_const)(haxorg_DocumentExportConfig, OrgContext*);
  haxorg_DocumentExportConfigDoExport (*getDoExportMut)(haxorg_DocumentExportConfig, OrgContext*);
  bool (*isExportFixed_const)(haxorg_DocumentExportConfig, OrgContext*);
  haxorg_DocumentExportConfigExportFixed (*getExportFixedConst_const)(haxorg_DocumentExportConfig, OrgContext*);
  haxorg_DocumentExportConfigExportFixed (*getExportFixedMut)(haxorg_DocumentExportConfig, OrgContext*);
  haxorg_DocumentExportConfigTocExportKind (*getTocExportKind_const)(haxorg_DocumentExportConfig, OrgContext*);
};

struct haxorg_SubtreePeriod_vtable {
  haxorg_SubtreePeriodKind const* (*get_kind)(haxorg_SubtreePeriod const*, OrgContext*);
  haxorg_UserTime const* (*get_from)(haxorg_SubtreePeriod const*, OrgContext*);
  haxorg_HstdOpt const* (*get_to)(haxorg_SubtreePeriod const*, OrgContext*);
  bool (*__eq___const)(haxorg_SubtreePeriod, OrgContext*, haxorg_SubtreePeriod);
};

struct haxorg_NamedPropertyNonblocking_vtable {
  bool const* (*get_isBlocking)(haxorg_NamedPropertyNonblocking const*, OrgContext*);
  bool (*__eq___const)(haxorg_NamedPropertyNonblocking, OrgContext*, haxorg_NamedPropertyNonblocking);
};

struct haxorg_NamedPropertyArchiveTime_vtable {
  haxorg_UserTime const* (*get_time)(haxorg_NamedPropertyArchiveTime const*, OrgContext*);
  bool (*__eq___const)(haxorg_NamedPropertyArchiveTime, OrgContext*, haxorg_NamedPropertyArchiveTime);
};

struct haxorg_NamedPropertyArchiveFile_vtable {
  haxorg_HstdStr const* (*get_file)(haxorg_NamedPropertyArchiveFile const*, OrgContext*);
  bool (*__eq___const)(haxorg_NamedPropertyArchiveFile, OrgContext*, haxorg_NamedPropertyArchiveFile);
};

struct haxorg_NamedPropertyArchiveOlpath_vtable {
  haxorg_SubtreePath const* (*get_path)(haxorg_NamedPropertyArchiveOlpath const*, OrgContext*);
  bool (*__eq___const)(haxorg_NamedPropertyArchiveOlpath, OrgContext*, haxorg_NamedPropertyArchiveOlpath);
};

struct haxorg_NamedPropertyArchiveTarget_vtable {
  haxorg_SubtreePath const* (*get_path)(haxorg_NamedPropertyArchiveTarget const*, OrgContext*);
  haxorg_HstdStr const* (*get_pattern)(haxorg_NamedPropertyArchiveTarget const*, OrgContext*);
  bool (*__eq___const)(haxorg_NamedPropertyArchiveTarget, OrgContext*, haxorg_NamedPropertyArchiveTarget);
};

struct haxorg_NamedPropertyArchiveCategory_vtable {
  haxorg_HstdStr const* (*get_category)(haxorg_NamedPropertyArchiveCategory const*, OrgContext*);
  bool (*__eq___const)(haxorg_NamedPropertyArchiveCategory, OrgContext*, haxorg_NamedPropertyArchiveCategory);
};

struct haxorg_NamedPropertyArchiveTodo_vtable {
  haxorg_HstdStr const* (*get_todo)(haxorg_NamedPropertyArchiveTodo const*, OrgContext*);
  bool (*__eq___const)(haxorg_NamedPropertyArchiveTodo, OrgContext*, haxorg_NamedPropertyArchiveTodo);
};

struct haxorg_NamedPropertyTrigger_vtable {
  bool (*__eq___const)(haxorg_NamedPropertyTrigger, OrgContext*, haxorg_NamedPropertyTrigger);
};

struct haxorg_NamedPropertyExportLatexClass_vtable {
  haxorg_HstdStr const* (*get_latexClass)(haxorg_NamedPropertyExportLatexClass const*, OrgContext*);
  bool (*__eq___const)(haxorg_NamedPropertyExportLatexClass, OrgContext*, haxorg_NamedPropertyExportLatexClass);
};

struct haxorg_NamedPropertyCookieData_vtable {
  bool const* (*get_isRecursive)(haxorg_NamedPropertyCookieData const*, OrgContext*);
  haxorg_SubtreeTodoSource const* (*get_source)(haxorg_NamedPropertyCookieData const*, OrgContext*);
  bool (*__eq___const)(haxorg_NamedPropertyCookieData, OrgContext*, haxorg_NamedPropertyCookieData);
};

struct haxorg_NamedPropertyExportLatexClassOptions_vtable {
  haxorg_HstdVec const* (*get_options)(haxorg_NamedPropertyExportLatexClassOptions const*, OrgContext*);
  bool (*__eq___const)(haxorg_NamedPropertyExportLatexClassOptions, OrgContext*, haxorg_NamedPropertyExportLatexClassOptions);
};

struct haxorg_NamedPropertyExportLatexHeader_vtable {
  haxorg_HstdStr const* (*get_header)(haxorg_NamedPropertyExportLatexHeader const*, OrgContext*);
  bool (*__eq___const)(haxorg_NamedPropertyExportLatexHeader, OrgContext*, haxorg_NamedPropertyExportLatexHeader);
};

struct haxorg_NamedPropertyExportLatexCompiler_vtable {
  haxorg_HstdStr const* (*get_compiler)(haxorg_NamedPropertyExportLatexCompiler const*, OrgContext*);
  bool (*__eq___const)(haxorg_NamedPropertyExportLatexCompiler, OrgContext*, haxorg_NamedPropertyExportLatexCompiler);
};

struct haxorg_NamedPropertyOrdered_vtable {
  bool const* (*get_isOrdered)(haxorg_NamedPropertyOrdered const*, OrgContext*);
  bool (*__eq___const)(haxorg_NamedPropertyOrdered, OrgContext*, haxorg_NamedPropertyOrdered);
};

struct haxorg_NamedPropertyEffort_vtable {
  int const* (*get_hours)(haxorg_NamedPropertyEffort const*, OrgContext*);
  int const* (*get_minutes)(haxorg_NamedPropertyEffort const*, OrgContext*);
  bool (*__eq___const)(haxorg_NamedPropertyEffort, OrgContext*, haxorg_NamedPropertyEffort);
};

struct haxorg_NamedPropertyVisibility_vtable {
  haxorg_NamedPropertyVisibilityLevel const* (*get_level)(haxorg_NamedPropertyVisibility const*, OrgContext*);
  bool (*__eq___const)(haxorg_NamedPropertyVisibility, OrgContext*, haxorg_NamedPropertyVisibility);
};

struct haxorg_NamedPropertyExportOptions_vtable {
  haxorg_HstdStr const* (*get_backend)(haxorg_NamedPropertyExportOptions const*, OrgContext*);
  haxorg_HstdUnorderedMap const* (*get_values)(haxorg_NamedPropertyExportOptions const*, OrgContext*);
  bool (*__eq___const)(haxorg_NamedPropertyExportOptions, OrgContext*, haxorg_NamedPropertyExportOptions);
};

struct haxorg_NamedPropertyBlocker_vtable {
  haxorg_HstdVec const* (*get_blockers)(haxorg_NamedPropertyBlocker const*, OrgContext*);
  bool (*__eq___const)(haxorg_NamedPropertyBlocker, OrgContext*, haxorg_NamedPropertyBlocker);
};

struct haxorg_NamedPropertyUnnumbered_vtable {
  bool (*__eq___const)(haxorg_NamedPropertyUnnumbered, OrgContext*, haxorg_NamedPropertyUnnumbered);
};

struct haxorg_NamedPropertyCreated_vtable {
  haxorg_UserTime const* (*get_time)(haxorg_NamedPropertyCreated const*, OrgContext*);
  bool (*__eq___const)(haxorg_NamedPropertyCreated, OrgContext*, haxorg_NamedPropertyCreated);
};

struct haxorg_NamedPropertyRadioId_vtable {
  haxorg_HstdVec const* (*get_words)(haxorg_NamedPropertyRadioId const*, OrgContext*);
  bool (*__eq___const)(haxorg_NamedPropertyRadioId, OrgContext*, haxorg_NamedPropertyRadioId);
};

struct haxorg_NamedPropertyHashtagDef_vtable {
  haxorg_HashTagText const* (*get_hashtag)(haxorg_NamedPropertyHashtagDef const*, OrgContext*);
  bool (*__eq___const)(haxorg_NamedPropertyHashtagDef, OrgContext*, haxorg_NamedPropertyHashtagDef);
};

struct haxorg_NamedPropertyCustomArgs_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_NamedPropertyCustomArgs const*, OrgContext*);
  haxorg_HstdOpt const* (*get_sub)(haxorg_NamedPropertyCustomArgs const*, OrgContext*);
  haxorg_AttrGroup const* (*get_attrs)(haxorg_NamedPropertyCustomArgs const*, OrgContext*);
  bool (*__eq___const)(haxorg_NamedPropertyCustomArgs, OrgContext*, haxorg_NamedPropertyCustomArgs);
};

struct haxorg_NamedPropertyCustomRaw_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_NamedPropertyCustomRaw const*, OrgContext*);
  haxorg_HstdStr const* (*get_value)(haxorg_NamedPropertyCustomRaw const*, OrgContext*);
  bool (*__eq___const)(haxorg_NamedPropertyCustomRaw, OrgContext*, haxorg_NamedPropertyCustomRaw);
};

struct haxorg_NamedPropertyCustomId_vtable {
  haxorg_HstdStr const* (*get_value)(haxorg_NamedPropertyCustomId const*, OrgContext*);
  bool (*__eq___const)(haxorg_NamedPropertyCustomId, OrgContext*, haxorg_NamedPropertyCustomId);
};

struct haxorg_NamedPropertyCustomSubtreeJson_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_NamedPropertyCustomSubtreeJson const*, OrgContext*);
  haxorg_OrgJson const* (*get_value)(haxorg_NamedPropertyCustomSubtreeJson const*, OrgContext*);
  bool (*__eq___const)(haxorg_NamedPropertyCustomSubtreeJson, OrgContext*, haxorg_NamedPropertyCustomSubtreeJson);
};

struct haxorg_NamedPropertyCustomSubtreeFlags_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_NamedPropertyCustomSubtreeFlags const*, OrgContext*);
  haxorg_AttrGroup const* (*get_value)(haxorg_NamedPropertyCustomSubtreeFlags const*, OrgContext*);
  bool (*__eq___const)(haxorg_NamedPropertyCustomSubtreeFlags, OrgContext*, haxorg_NamedPropertyCustomSubtreeFlags);
};

struct haxorg_NamedProperty_vtable {
  bool (*isMatching_const)(haxorg_NamedProperty, OrgContext*, haxorg_HstdStr, haxorg_HstdOpt);
  haxorg_HstdStr (*getName_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_HstdOpt (*getSubKind_const)(haxorg_NamedProperty, OrgContext*);
  bool (*__eq___const)(haxorg_NamedProperty, OrgContext*, haxorg_NamedProperty);
  bool (*isNonblocking_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyNonblocking (*getNonblockingConst_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyNonblocking (*getNonblockingMut)(haxorg_NamedProperty, OrgContext*);
  bool (*isArchiveTime_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyArchiveTime (*getArchiveTimeConst_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyArchiveTime (*getArchiveTimeMut)(haxorg_NamedProperty, OrgContext*);
  bool (*isArchiveFile_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyArchiveFile (*getArchiveFileConst_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyArchiveFile (*getArchiveFileMut)(haxorg_NamedProperty, OrgContext*);
  bool (*isArchiveOlpath_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyArchiveOlpath (*getArchiveOlpathConst_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyArchiveOlpath (*getArchiveOlpathMut)(haxorg_NamedProperty, OrgContext*);
  bool (*isArchiveTarget_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyArchiveTarget (*getArchiveTargetConst_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyArchiveTarget (*getArchiveTargetMut)(haxorg_NamedProperty, OrgContext*);
  bool (*isArchiveCategory_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyArchiveCategory (*getArchiveCategoryConst_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyArchiveCategory (*getArchiveCategoryMut)(haxorg_NamedProperty, OrgContext*);
  bool (*isArchiveTodo_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyArchiveTodo (*getArchiveTodoConst_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyArchiveTodo (*getArchiveTodoMut)(haxorg_NamedProperty, OrgContext*);
  bool (*isTrigger_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyTrigger (*getTriggerConst_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyTrigger (*getTriggerMut)(haxorg_NamedProperty, OrgContext*);
  bool (*isExportLatexClass_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyExportLatexClass (*getExportLatexClassConst_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyExportLatexClass (*getExportLatexClassMut)(haxorg_NamedProperty, OrgContext*);
  bool (*isCookieData_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyCookieData (*getCookieDataConst_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyCookieData (*getCookieDataMut)(haxorg_NamedProperty, OrgContext*);
  bool (*isExportLatexClassOptions_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyExportLatexClassOptions (*getExportLatexClassOptionsConst_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyExportLatexClassOptions (*getExportLatexClassOptionsMut)(haxorg_NamedProperty, OrgContext*);
  bool (*isExportLatexHeader_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyExportLatexHeader (*getExportLatexHeaderConst_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyExportLatexHeader (*getExportLatexHeaderMut)(haxorg_NamedProperty, OrgContext*);
  bool (*isExportLatexCompiler_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyExportLatexCompiler (*getExportLatexCompilerConst_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyExportLatexCompiler (*getExportLatexCompilerMut)(haxorg_NamedProperty, OrgContext*);
  bool (*isOrdered_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyOrdered (*getOrderedConst_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyOrdered (*getOrderedMut)(haxorg_NamedProperty, OrgContext*);
  bool (*isEffort_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyEffort (*getEffortConst_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyEffort (*getEffortMut)(haxorg_NamedProperty, OrgContext*);
  bool (*isVisibility_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyVisibility (*getVisibilityConst_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyVisibility (*getVisibilityMut)(haxorg_NamedProperty, OrgContext*);
  bool (*isExportOptions_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyExportOptions (*getExportOptionsConst_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyExportOptions (*getExportOptionsMut)(haxorg_NamedProperty, OrgContext*);
  bool (*isBlocker_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyBlocker (*getBlockerConst_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyBlocker (*getBlockerMut)(haxorg_NamedProperty, OrgContext*);
  bool (*isUnnumbered_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyUnnumbered (*getUnnumberedConst_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyUnnumbered (*getUnnumberedMut)(haxorg_NamedProperty, OrgContext*);
  bool (*isCreated_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyCreated (*getCreatedConst_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyCreated (*getCreatedMut)(haxorg_NamedProperty, OrgContext*);
  bool (*isRadioId_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyRadioId (*getRadioIdConst_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyRadioId (*getRadioIdMut)(haxorg_NamedProperty, OrgContext*);
  bool (*isHashtagDef_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyHashtagDef (*getHashtagDefConst_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyHashtagDef (*getHashtagDefMut)(haxorg_NamedProperty, OrgContext*);
  bool (*isCustomArgs_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyCustomArgs (*getCustomArgsConst_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyCustomArgs (*getCustomArgsMut)(haxorg_NamedProperty, OrgContext*);
  bool (*isCustomRaw_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyCustomRaw (*getCustomRawConst_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyCustomRaw (*getCustomRawMut)(haxorg_NamedProperty, OrgContext*);
  bool (*isCustomId_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyCustomId (*getCustomIdConst_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyCustomId (*getCustomIdMut)(haxorg_NamedProperty, OrgContext*);
  bool (*isCustomSubtreeJson_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyCustomSubtreeJson (*getCustomSubtreeJsonConst_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyCustomSubtreeJson (*getCustomSubtreeJsonMut)(haxorg_NamedProperty, OrgContext*);
  bool (*isCustomSubtreeFlags_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyCustomSubtreeFlags (*getCustomSubtreeFlagsConst_const)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyCustomSubtreeFlags (*getCustomSubtreeFlagsMut)(haxorg_NamedProperty, OrgContext*);
  haxorg_NamedPropertyKind (*getKind_const)(haxorg_NamedProperty, OrgContext*);
};

struct haxorg_OrgDiagnosticsParseTokenError_vtable {
  haxorg_HstdStr const* (*get_brief)(haxorg_OrgDiagnosticsParseTokenError const*, OrgContext*);
  haxorg_HstdStr const* (*get_detail)(haxorg_OrgDiagnosticsParseTokenError const*, OrgContext*);
  haxorg_HstdStr const* (*get_parserFunction)(haxorg_OrgDiagnosticsParseTokenError const*, OrgContext*);
  int const* (*get_parserLine)(haxorg_OrgDiagnosticsParseTokenError const*, OrgContext*);
  haxorg_OrgTokenKind const* (*get_tokenKind)(haxorg_OrgDiagnosticsParseTokenError const*, OrgContext*);
  haxorg_HstdStr const* (*get_tokenText)(haxorg_OrgDiagnosticsParseTokenError const*, OrgContext*);
  haxorg_ParseSourceLoc const* (*get_loc)(haxorg_OrgDiagnosticsParseTokenError const*, OrgContext*);
  haxorg_HstdStr const* (*get_errName)(haxorg_OrgDiagnosticsParseTokenError const*, OrgContext*);
  haxorg_HstdStr const* (*get_errCode)(haxorg_OrgDiagnosticsParseTokenError const*, OrgContext*);
  bool (*__eq___const)(haxorg_OrgDiagnosticsParseTokenError, OrgContext*, haxorg_OrgDiagnosticsParseTokenError);
};

struct haxorg_OrgDiagnosticsParseError_vtable {
  haxorg_HstdStr const* (*get_brief)(haxorg_OrgDiagnosticsParseError const*, OrgContext*);
  haxorg_HstdStr const* (*get_detail)(haxorg_OrgDiagnosticsParseError const*, OrgContext*);
  haxorg_HstdStr const* (*get_parserFunction)(haxorg_OrgDiagnosticsParseError const*, OrgContext*);
  int const* (*get_parserLine)(haxorg_OrgDiagnosticsParseError const*, OrgContext*);
  haxorg_HstdStr const* (*get_errName)(haxorg_OrgDiagnosticsParseError const*, OrgContext*);
  haxorg_HstdStr const* (*get_errCode)(haxorg_OrgDiagnosticsParseError const*, OrgContext*);
  haxorg_HstdOpt const* (*get_loc)(haxorg_OrgDiagnosticsParseError const*, OrgContext*);
  bool (*__eq___const)(haxorg_OrgDiagnosticsParseError, OrgContext*, haxorg_OrgDiagnosticsParseError);
};

struct haxorg_OrgDiagnosticsIncludeError_vtable {
  haxorg_HstdStr const* (*get_brief)(haxorg_OrgDiagnosticsIncludeError const*, OrgContext*);
  haxorg_HstdStr const* (*get_targetPath)(haxorg_OrgDiagnosticsIncludeError const*, OrgContext*);
  haxorg_HstdStr const* (*get_workingFile)(haxorg_OrgDiagnosticsIncludeError const*, OrgContext*);
  bool (*__eq___const)(haxorg_OrgDiagnosticsIncludeError, OrgContext*, haxorg_OrgDiagnosticsIncludeError);
};

struct haxorg_OrgDiagnosticsConvertError_vtable {
  haxorg_HstdStr const* (*get_brief)(haxorg_OrgDiagnosticsConvertError const*, OrgContext*);
  haxorg_HstdStr const* (*get_detail)(haxorg_OrgDiagnosticsConvertError const*, OrgContext*);
  haxorg_HstdStr const* (*get_convertFunction)(haxorg_OrgDiagnosticsConvertError const*, OrgContext*);
  int const* (*get_convertLine)(haxorg_OrgDiagnosticsConvertError const*, OrgContext*);
  haxorg_HstdStr const* (*get_convertFile)(haxorg_OrgDiagnosticsConvertError const*, OrgContext*);
  haxorg_HstdStr const* (*get_errName)(haxorg_OrgDiagnosticsConvertError const*, OrgContext*);
  haxorg_HstdStr const* (*get_errCode)(haxorg_OrgDiagnosticsConvertError const*, OrgContext*);
  haxorg_HstdOpt const* (*get_loc)(haxorg_OrgDiagnosticsConvertError const*, OrgContext*);
  bool (*__eq___const)(haxorg_OrgDiagnosticsConvertError, OrgContext*, haxorg_OrgDiagnosticsConvertError);
};

struct haxorg_OrgDiagnosticsInternalError_vtable {
  haxorg_HstdStr const* (*get_message)(haxorg_OrgDiagnosticsInternalError const*, OrgContext*);
  haxorg_HstdStr const* (*get_function)(haxorg_OrgDiagnosticsInternalError const*, OrgContext*);
  int const* (*get_line)(haxorg_OrgDiagnosticsInternalError const*, OrgContext*);
  haxorg_HstdStr const* (*get_file)(haxorg_OrgDiagnosticsInternalError const*, OrgContext*);
  haxorg_HstdOpt const* (*get_loc)(haxorg_OrgDiagnosticsInternalError const*, OrgContext*);
  bool (*__eq___const)(haxorg_OrgDiagnosticsInternalError, OrgContext*, haxorg_OrgDiagnosticsInternalError);
};

struct haxorg_OrgDiagnostics_vtable {
  bool (*__eq___const)(haxorg_OrgDiagnostics, OrgContext*, haxorg_OrgDiagnostics);
  bool (*isParseTokenError_const)(haxorg_OrgDiagnostics, OrgContext*);
  haxorg_OrgDiagnosticsParseTokenError (*getParseTokenErrorConst_const)(haxorg_OrgDiagnostics, OrgContext*);
  haxorg_OrgDiagnosticsParseTokenError (*getParseTokenErrorMut)(haxorg_OrgDiagnostics, OrgContext*);
  bool (*isParseError_const)(haxorg_OrgDiagnostics, OrgContext*);
  haxorg_OrgDiagnosticsParseError (*getParseErrorConst_const)(haxorg_OrgDiagnostics, OrgContext*);
  haxorg_OrgDiagnosticsParseError (*getParseErrorMut)(haxorg_OrgDiagnostics, OrgContext*);
  bool (*isIncludeError_const)(haxorg_OrgDiagnostics, OrgContext*);
  haxorg_OrgDiagnosticsIncludeError (*getIncludeErrorConst_const)(haxorg_OrgDiagnostics, OrgContext*);
  haxorg_OrgDiagnosticsIncludeError (*getIncludeErrorMut)(haxorg_OrgDiagnostics, OrgContext*);
  bool (*isConvertError_const)(haxorg_OrgDiagnostics, OrgContext*);
  haxorg_OrgDiagnosticsConvertError (*getConvertErrorConst_const)(haxorg_OrgDiagnostics, OrgContext*);
  haxorg_OrgDiagnosticsConvertError (*getConvertErrorMut)(haxorg_OrgDiagnostics, OrgContext*);
  bool (*isInternalError_const)(haxorg_OrgDiagnostics, OrgContext*);
  haxorg_OrgDiagnosticsInternalError (*getInternalErrorConst_const)(haxorg_OrgDiagnostics, OrgContext*);
  haxorg_OrgDiagnosticsInternalError (*getInternalErrorMut)(haxorg_OrgDiagnostics, OrgContext*);
  haxorg_OrgDiagnosticsKind (*getKind_const)(haxorg_OrgDiagnostics, OrgContext*);
};

struct haxorg_ErrorItem_vtable {
  haxorg_OrgDiagnostics const* (*get_diag)(haxorg_ErrorItem const*, OrgContext*);
};

struct haxorg_ErrorGroup_vtable {
  haxorg_HstdVec const* (*get_diagnostics)(haxorg_ErrorGroup const*, OrgContext*);
};

struct haxorg_Stmt_vtable {
  haxorg_HstdVec const* (*get_attached)(haxorg_Stmt const*, OrgContext*);
  haxorg_HstdVec (*getAttached_const)(haxorg_Stmt, OrgContext*, haxorg_HstdOpt);
  haxorg_HstdVec (*getCaption_const)(haxorg_Stmt, OrgContext*);
  haxorg_HstdVec (*getName_const)(haxorg_Stmt, OrgContext*);
  haxorg_HstdVec (*getAttrs_const)(haxorg_Stmt, OrgContext*, haxorg_HstdOpt);
  haxorg_HstdOpt (*getFirstAttr_const)(haxorg_Stmt, OrgContext*, haxorg_HstdStr);
  haxorg_HstdOpt (*getFirstAttrString_const)(haxorg_Stmt, OrgContext*, haxorg_HstdStr);
  haxorg_HstdOpt (*getFirstAttrInt_const)(haxorg_Stmt, OrgContext*, haxorg_HstdStr);
  haxorg_HstdOpt (*getFirstAttrBool_const)(haxorg_Stmt, OrgContext*, haxorg_HstdStr);
  haxorg_HstdOpt (*getFirstAttrDouble_const)(haxorg_Stmt, OrgContext*, haxorg_HstdStr);
  haxorg_HstdOpt (*getFirstAttrLisp_const)(haxorg_Stmt, OrgContext*, haxorg_HstdStr);
  haxorg_HstdOpt (*getFirstAttrKind_const)(haxorg_Stmt, OrgContext*, haxorg_HstdStr);
};

struct haxorg_Leaf_vtable {
  haxorg_HstdStr const* (*get_text)(haxorg_Leaf const*, OrgContext*);
  haxorg_HstdStr (*getText_const)(haxorg_Leaf, OrgContext*);
};

struct haxorg_TimeRepeat_vtable {
  haxorg_TimeRepeatMode const* (*get_mode)(haxorg_TimeRepeat const*, OrgContext*);
  haxorg_TimeRepeatPeriod const* (*get_period)(haxorg_TimeRepeat const*, OrgContext*);
  int const* (*get_count)(haxorg_TimeRepeat const*, OrgContext*);
  bool (*__eq___const)(haxorg_TimeRepeat, OrgContext*, haxorg_TimeRepeat);
};

struct haxorg_TimeStatic_vtable {
  haxorg_HstdVec const* (*get_repeat)(haxorg_TimeStatic const*, OrgContext*);
  haxorg_HstdOpt const* (*get_warn)(haxorg_TimeStatic const*, OrgContext*);
  haxorg_UserTime const* (*get_time)(haxorg_TimeStatic const*, OrgContext*);
  bool (*__eq___const)(haxorg_TimeStatic, OrgContext*, haxorg_TimeStatic);
};

struct haxorg_TimeDynamic_vtable {
  haxorg_LispCode const* (*get_expr)(haxorg_TimeDynamic const*, OrgContext*);
  bool (*__eq___const)(haxorg_TimeDynamic, OrgContext*, haxorg_TimeDynamic);
};

struct haxorg_Time_vtable {
  bool const* (*get_isActive)(haxorg_Time const*, OrgContext*);
  haxorg_HstdOpt (*getYear_const)(haxorg_Time, OrgContext*);
  haxorg_HstdOpt (*getMonth_const)(haxorg_Time, OrgContext*);
  haxorg_HstdOpt (*getDay_const)(haxorg_Time, OrgContext*);
  haxorg_HstdOpt (*getHour_const)(haxorg_Time, OrgContext*);
  haxorg_HstdOpt (*getMinute_const)(haxorg_Time, OrgContext*);
  haxorg_HstdOpt (*getSecond_const)(haxorg_Time, OrgContext*);
  haxorg_UserTime (*getStaticTime_const)(haxorg_Time, OrgContext*);
  bool (*isStatic_const)(haxorg_Time, OrgContext*);
  haxorg_TimeStatic (*getStaticConst_const)(haxorg_Time, OrgContext*);
  haxorg_TimeStatic (*getStaticMut)(haxorg_Time, OrgContext*);
  bool (*isDynamic_const)(haxorg_Time, OrgContext*);
  haxorg_TimeDynamic (*getDynamicConst_const)(haxorg_Time, OrgContext*);
  haxorg_TimeDynamic (*getDynamicMut)(haxorg_Time, OrgContext*);
  haxorg_TimeTimeKind (*getTimeKind_const)(haxorg_Time, OrgContext*);
};

struct haxorg_TimeRange_vtable {
  haxorg_SemId const* (*get_from)(haxorg_TimeRange const*, OrgContext*);
  haxorg_SemId const* (*get_to)(haxorg_TimeRange const*, OrgContext*);
  haxorg_HstdOpt (*getClockedTimeSeconds_const)(haxorg_TimeRange, OrgContext*);
};

struct haxorg_Macro_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_Macro const*, OrgContext*);
  haxorg_AttrGroup const* (*get_attrs)(haxorg_Macro const*, OrgContext*);
};

struct haxorg_SymbolParam_vtable {
  haxorg_HstdOpt const* (*get_key)(haxorg_SymbolParam const*, OrgContext*);
  haxorg_HstdStr const* (*get_value)(haxorg_SymbolParam const*, OrgContext*);
};

struct haxorg_Symbol_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_Symbol const*, OrgContext*);
  haxorg_HstdVec const* (*get_parameters)(haxorg_Symbol const*, OrgContext*);
  haxorg_HstdVec const* (*get_positional)(haxorg_Symbol const*, OrgContext*);
};

struct haxorg_ErrorSkipGroup_vtable {
  haxorg_HstdVec const* (*get_skipped)(haxorg_ErrorSkipGroup const*, OrgContext*);
};

struct haxorg_RadioTarget_vtable {
  haxorg_HstdVec const* (*get_words)(haxorg_RadioTarget const*, OrgContext*);
};

struct haxorg_SubtreeLog_vtable {
  haxorg_SubtreeLogHead const* (*get_head)(haxorg_SubtreeLog const*, OrgContext*);
  haxorg_HstdOpt const* (*get_desc)(haxorg_SubtreeLog const*, OrgContext*);
  void (*setDescription)(haxorg_SubtreeLog, OrgContext*, haxorg_SemId);
};

struct haxorg_Subtree_vtable {
  int const* (*get_level)(haxorg_Subtree const*, OrgContext*);
  haxorg_HstdOpt const* (*get_treeId)(haxorg_Subtree const*, OrgContext*);
  haxorg_HstdOpt const* (*get_todo)(haxorg_Subtree const*, OrgContext*);
  haxorg_HstdOpt const* (*get_completion)(haxorg_Subtree const*, OrgContext*);
  haxorg_HstdOpt const* (*get_description)(haxorg_Subtree const*, OrgContext*);
  haxorg_HstdVec const* (*get_tags)(haxorg_Subtree const*, OrgContext*);
  haxorg_SemId const* (*get_title)(haxorg_Subtree const*, OrgContext*);
  haxorg_HstdVec const* (*get_logbook)(haxorg_Subtree const*, OrgContext*);
  haxorg_HstdVec const* (*get_properties)(haxorg_Subtree const*, OrgContext*);
  haxorg_HstdOpt const* (*get_closed)(haxorg_Subtree const*, OrgContext*);
  haxorg_HstdOpt const* (*get_deadline)(haxorg_Subtree const*, OrgContext*);
  haxorg_HstdOpt const* (*get_scheduled)(haxorg_Subtree const*, OrgContext*);
  bool const* (*get_isComment)(haxorg_Subtree const*, OrgContext*);
  bool const* (*get_isArchived)(haxorg_Subtree const*, OrgContext*);
  haxorg_HstdOpt const* (*get_priority)(haxorg_Subtree const*, OrgContext*);
  haxorg_HstdVec (*getTimePeriods_const)(haxorg_Subtree, OrgContext*, haxorg_HstdIntSet);
  haxorg_HstdVec (*getProperties_const)(haxorg_Subtree, OrgContext*, haxorg_HstdStr, haxorg_HstdOpt);
  haxorg_HstdOpt (*getProperty_const)(haxorg_Subtree, OrgContext*, haxorg_HstdStr, haxorg_HstdOpt);
  void (*removeProperty)(haxorg_Subtree, OrgContext*, haxorg_HstdStr, haxorg_HstdOpt);
  void (*setProperty)(haxorg_Subtree, OrgContext*, haxorg_NamedProperty);
  void (*setPropertyStrValue)(haxorg_Subtree, OrgContext*, haxorg_HstdStr, haxorg_HstdStr, haxorg_HstdOpt);
  haxorg_HstdStr (*getCleanTitle_const)(haxorg_Subtree, OrgContext*);
  haxorg_HstdOpt (*getTodoKeyword_const)(haxorg_Subtree, OrgContext*);
};

struct haxorg_Call_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_Call const*, OrgContext*);
  haxorg_AttrGroup const* (*get_attrs)(haxorg_Call const*, OrgContext*);
  bool const* (*get_isCommand)(haxorg_Call const*, OrgContext*);
};

struct haxorg_ListItem_vtable {
  haxorg_CheckboxState const* (*get_checkbox)(haxorg_ListItem const*, OrgContext*);
  haxorg_HstdOpt const* (*get_header)(haxorg_ListItem const*, OrgContext*);
  haxorg_HstdOpt const* (*get_bullet)(haxorg_ListItem const*, OrgContext*);
  bool (*isDescriptionItem_const)(haxorg_ListItem, OrgContext*);
  haxorg_HstdOpt (*getCleanHeader_const)(haxorg_ListItem, OrgContext*);
};

struct haxorg_DocumentOptions_vtable {
  haxorg_InitialSubtreeVisibility const* (*get_initialVisibility)(haxorg_DocumentOptions const*, OrgContext*);
  haxorg_HstdVec const* (*get_properties)(haxorg_DocumentOptions const*, OrgContext*);
  haxorg_DocumentExportConfig const* (*get_exportConfig)(haxorg_DocumentOptions const*, OrgContext*);
  haxorg_HstdOpt const* (*get_fixedWidthSections)(haxorg_DocumentOptions const*, OrgContext*);
  haxorg_HstdOpt const* (*get_startupIndented)(haxorg_DocumentOptions const*, OrgContext*);
  haxorg_HstdOpt const* (*get_category)(haxorg_DocumentOptions const*, OrgContext*);
  haxorg_HstdOpt const* (*get_setupfile)(haxorg_DocumentOptions const*, OrgContext*);
  haxorg_HstdOpt const* (*get_maxSubtreeLevelExport)(haxorg_DocumentOptions const*, OrgContext*);
  haxorg_HstdOpt const* (*get_columns)(haxorg_DocumentOptions const*, OrgContext*);
  haxorg_HstdVec const* (*get_todoKeywords)(haxorg_DocumentOptions const*, OrgContext*);
  haxorg_HstdVec const* (*get_doneKeywords)(haxorg_DocumentOptions const*, OrgContext*);
  haxorg_HstdVec (*getProperties_const)(haxorg_DocumentOptions, OrgContext*, haxorg_HstdStr, haxorg_HstdOpt);
  haxorg_HstdOpt (*getProperty_const)(haxorg_DocumentOptions, OrgContext*, haxorg_HstdStr, haxorg_HstdOpt);
};

struct haxorg_DocumentFragment_vtable {
  int const* (*get_baseLine)(haxorg_DocumentFragment const*, OrgContext*);
  int const* (*get_baseCol)(haxorg_DocumentFragment const*, OrgContext*);
};

struct haxorg_CriticMarkup_vtable {
  haxorg_CriticMarkupKind const* (*get_kind)(haxorg_CriticMarkup const*, OrgContext*);
};

struct haxorg_Document_vtable {
  haxorg_HstdOpt const* (*get_title)(haxorg_Document const*, OrgContext*);
  haxorg_HstdOpt const* (*get_author)(haxorg_Document const*, OrgContext*);
  haxorg_HstdOpt const* (*get_creator)(haxorg_Document const*, OrgContext*);
  haxorg_HstdVec const* (*get_filetags)(haxorg_Document const*, OrgContext*);
  haxorg_HstdOpt const* (*get_email)(haxorg_Document const*, OrgContext*);
  haxorg_HstdVec const* (*get_language)(haxorg_Document const*, OrgContext*);
  haxorg_SemId const* (*get_options)(haxorg_Document const*, OrgContext*);
  haxorg_HstdOpt const* (*get_exportFileName)(haxorg_Document const*, OrgContext*);
  haxorg_HstdVec (*getProperties_const)(haxorg_Document, OrgContext*, haxorg_HstdStr, haxorg_HstdOpt);
  haxorg_HstdOpt (*getProperty_const)(haxorg_Document, OrgContext*, haxorg_HstdStr, haxorg_HstdOpt);
};

struct haxorg_FileTarget_vtable {
  haxorg_HstdStr const* (*get_path)(haxorg_FileTarget const*, OrgContext*);
  haxorg_HstdOpt const* (*get_line)(haxorg_FileTarget const*, OrgContext*);
  haxorg_HstdOpt const* (*get_searchTarget)(haxorg_FileTarget const*, OrgContext*);
  bool const* (*get_restrictToHeadlines)(haxorg_FileTarget const*, OrgContext*);
  haxorg_HstdOpt const* (*get_targetId)(haxorg_FileTarget const*, OrgContext*);
  haxorg_HstdOpt const* (*get_regexp)(haxorg_FileTarget const*, OrgContext*);
};

struct haxorg_File_vtable {
  haxorg_HstdStr const* (*get_relPath)(haxorg_File const*, OrgContext*);
  haxorg_HstdStr const* (*get_absPath)(haxorg_File const*, OrgContext*);
  bool (*isDocument_const)(haxorg_File, OrgContext*);
  haxorg_FileDocument (*getDocumentConst_const)(haxorg_File, OrgContext*);
  haxorg_FileDocument (*getDocumentMut)(haxorg_File, OrgContext*);
  bool (*isAttachment_const)(haxorg_File, OrgContext*);
  haxorg_FileAttachment (*getAttachmentConst_const)(haxorg_File, OrgContext*);
  haxorg_FileAttachment (*getAttachmentMut)(haxorg_File, OrgContext*);
  bool (*isSource_const)(haxorg_File, OrgContext*);
  haxorg_FileSource (*getSourceConst_const)(haxorg_File, OrgContext*);
  haxorg_FileSource (*getSourceMut)(haxorg_File, OrgContext*);
  haxorg_FileKind (*getFileKind_const)(haxorg_File, OrgContext*);
};

struct haxorg_Directory_vtable {
  haxorg_HstdStr const* (*get_relPath)(haxorg_Directory const*, OrgContext*);
  haxorg_HstdStr const* (*get_absPath)(haxorg_Directory const*, OrgContext*);
};

struct haxorg_Symlink_vtable {
  bool const* (*get_isDirectory)(haxorg_Symlink const*, OrgContext*);
  haxorg_HstdStr const* (*get_absPath)(haxorg_Symlink const*, OrgContext*);
};

struct haxorg_CmdIncludeIncludeBase_vtable {
  bool (*__eq___const)(haxorg_CmdIncludeIncludeBase, OrgContext*, haxorg_CmdIncludeIncludeBase);
};

struct haxorg_CmdIncludeExample_vtable {
  bool (*__eq___const)(haxorg_CmdIncludeExample, OrgContext*, haxorg_CmdIncludeExample);
};

struct haxorg_CmdIncludeExport_vtable {
  haxorg_HstdStr const* (*get_language)(haxorg_CmdIncludeExport const*, OrgContext*);
  bool (*__eq___const)(haxorg_CmdIncludeExport, OrgContext*, haxorg_CmdIncludeExport);
};

struct haxorg_CmdIncludeCustom_vtable {
  haxorg_HstdStr const* (*get_blockName)(haxorg_CmdIncludeCustom const*, OrgContext*);
  bool (*__eq___const)(haxorg_CmdIncludeCustom, OrgContext*, haxorg_CmdIncludeCustom);
};

struct haxorg_CmdIncludeSrc_vtable {
  haxorg_HstdStr const* (*get_language)(haxorg_CmdIncludeSrc const*, OrgContext*);
  bool (*__eq___const)(haxorg_CmdIncludeSrc, OrgContext*, haxorg_CmdIncludeSrc);
};

struct haxorg_CmdIncludeOrgDocument_vtable {
  haxorg_HstdOpt const* (*get_onlyContent)(haxorg_CmdIncludeOrgDocument const*, OrgContext*);
  haxorg_HstdOpt const* (*get_subtreePath)(haxorg_CmdIncludeOrgDocument const*, OrgContext*);
  haxorg_HstdOpt const* (*get_minLevel)(haxorg_CmdIncludeOrgDocument const*, OrgContext*);
  haxorg_HstdOpt const* (*get_customIdTarget)(haxorg_CmdIncludeOrgDocument const*, OrgContext*);
  bool (*__eq___const)(haxorg_CmdIncludeOrgDocument, OrgContext*, haxorg_CmdIncludeOrgDocument);
};

struct haxorg_CmdInclude_vtable {
  haxorg_HstdStr const* (*get_path)(haxorg_CmdInclude const*, OrgContext*);
  haxorg_HstdOpt const* (*get_firstLine)(haxorg_CmdInclude const*, OrgContext*);
  haxorg_HstdOpt const* (*get_lastLine)(haxorg_CmdInclude const*, OrgContext*);
  bool (*isExample_const)(haxorg_CmdInclude, OrgContext*);
  haxorg_CmdIncludeExample (*getExampleConst_const)(haxorg_CmdInclude, OrgContext*);
  haxorg_CmdIncludeExample (*getExampleMut)(haxorg_CmdInclude, OrgContext*);
  bool (*isExport_const)(haxorg_CmdInclude, OrgContext*);
  haxorg_CmdIncludeExport (*getExportConst_const)(haxorg_CmdInclude, OrgContext*);
  haxorg_CmdIncludeExport (*getExportMut)(haxorg_CmdInclude, OrgContext*);
  bool (*isCustom_const)(haxorg_CmdInclude, OrgContext*);
  haxorg_CmdIncludeCustom (*getCustomConst_const)(haxorg_CmdInclude, OrgContext*);
  haxorg_CmdIncludeCustom (*getCustomMut)(haxorg_CmdInclude, OrgContext*);
  bool (*isSrc_const)(haxorg_CmdInclude, OrgContext*);
  haxorg_CmdIncludeSrc (*getSrcConst_const)(haxorg_CmdInclude, OrgContext*);
  haxorg_CmdIncludeSrc (*getSrcMut)(haxorg_CmdInclude, OrgContext*);
  bool (*isOrgDocument_const)(haxorg_CmdInclude, OrgContext*);
  haxorg_CmdIncludeOrgDocument (*getOrgDocumentConst_const)(haxorg_CmdInclude, OrgContext*);
  haxorg_CmdIncludeOrgDocument (*getOrgDocumentMut)(haxorg_CmdInclude, OrgContext*);
  haxorg_CmdIncludeKind (*getIncludeKind_const)(haxorg_CmdInclude, OrgContext*);
};

struct haxorg_ImmNoNode_vtable {
  bool (*__eq___const)(haxorg_ImmNoNode, OrgContext*, haxorg_ImmNoNode);
};

struct haxorg_ImmErrorItem_vtable {
  haxorg_OrgDiagnostics const* (*get_diag)(haxorg_ImmErrorItem const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmErrorItem, OrgContext*, haxorg_ImmErrorItem);
};

struct haxorg_ImmErrorGroup_vtable {
  haxorg_ImmVec const* (*get_diagnostics)(haxorg_ImmErrorGroup const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmErrorGroup, OrgContext*, haxorg_ImmErrorGroup);
};

struct haxorg_ImmStmt_vtable {
  haxorg_ImmVec const* (*get_attached)(haxorg_ImmStmt const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmStmt, OrgContext*, haxorg_ImmStmt);
};

struct haxorg_ImmInline_vtable {
  bool (*__eq___const)(haxorg_ImmInline, OrgContext*, haxorg_ImmInline);
};

struct haxorg_ImmStmtList_vtable {
  bool (*__eq___const)(haxorg_ImmStmtList, OrgContext*, haxorg_ImmStmtList);
};

struct haxorg_ImmEmpty_vtable {
  bool (*__eq___const)(haxorg_ImmEmpty, OrgContext*, haxorg_ImmEmpty);
};

struct haxorg_ImmLeaf_vtable {
  haxorg_HstdStr const* (*get_text)(haxorg_ImmLeaf const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmLeaf, OrgContext*, haxorg_ImmLeaf);
};

struct haxorg_ImmTimeRepeat_vtable {
  haxorg_ImmTimeRepeatMode const* (*get_mode)(haxorg_ImmTimeRepeat const*, OrgContext*);
  haxorg_ImmTimeRepeatPeriod const* (*get_period)(haxorg_ImmTimeRepeat const*, OrgContext*);
  int const* (*get_count)(haxorg_ImmTimeRepeat const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmTimeRepeat, OrgContext*, haxorg_ImmTimeRepeat);
};

struct haxorg_ImmTimeStatic_vtable {
  haxorg_ImmVec const* (*get_repeat)(haxorg_ImmTimeStatic const*, OrgContext*);
  haxorg_HstdOpt const* (*get_warn)(haxorg_ImmTimeStatic const*, OrgContext*);
  haxorg_UserTime const* (*get_time)(haxorg_ImmTimeStatic const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmTimeStatic, OrgContext*, haxorg_ImmTimeStatic);
};

struct haxorg_ImmTimeDynamic_vtable {
  haxorg_LispCode const* (*get_expr)(haxorg_ImmTimeDynamic const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmTimeDynamic, OrgContext*, haxorg_ImmTimeDynamic);
};

struct haxorg_ImmTime_vtable {
  bool const* (*get_isActive)(haxorg_ImmTime const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmTime, OrgContext*, haxorg_ImmTime);
  bool (*isStatic_const)(haxorg_ImmTime, OrgContext*);
  haxorg_ImmTimeStatic (*getStaticConst_const)(haxorg_ImmTime, OrgContext*);
  haxorg_ImmTimeStatic (*getStaticMut)(haxorg_ImmTime, OrgContext*);
  bool (*isDynamic_const)(haxorg_ImmTime, OrgContext*);
  haxorg_ImmTimeDynamic (*getDynamicConst_const)(haxorg_ImmTime, OrgContext*);
  haxorg_ImmTimeDynamic (*getDynamicMut)(haxorg_ImmTime, OrgContext*);
  haxorg_ImmTimeTimeKind (*getTimeKind_const)(haxorg_ImmTime, OrgContext*);
};

struct haxorg_ImmTimeRange_vtable {
  haxorg_ImmId const* (*get_from)(haxorg_ImmTimeRange const*, OrgContext*);
  haxorg_ImmId const* (*get_to)(haxorg_ImmTimeRange const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmTimeRange, OrgContext*, haxorg_ImmTimeRange);
};

struct haxorg_ImmMacro_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_ImmMacro const*, OrgContext*);
  haxorg_AttrGroup const* (*get_attrs)(haxorg_ImmMacro const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmMacro, OrgContext*, haxorg_ImmMacro);
};

struct haxorg_ImmSymbolParam_vtable {
  haxorg_HstdOpt const* (*get_key)(haxorg_ImmSymbolParam const*, OrgContext*);
  haxorg_HstdStr const* (*get_value)(haxorg_ImmSymbolParam const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmSymbolParam, OrgContext*, haxorg_ImmSymbolParam);
};

struct haxorg_ImmSymbol_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_ImmSymbol const*, OrgContext*);
  haxorg_ImmVec const* (*get_parameters)(haxorg_ImmSymbol const*, OrgContext*);
  haxorg_ImmVec const* (*get_positional)(haxorg_ImmSymbol const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmSymbol, OrgContext*, haxorg_ImmSymbol);
};

struct haxorg_ImmErrorSkipGroup_vtable {
  haxorg_ImmVec const* (*get_skipped)(haxorg_ImmErrorSkipGroup const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmErrorSkipGroup, OrgContext*, haxorg_ImmErrorSkipGroup);
};

struct haxorg_ImmMarkup_vtable {
  bool (*__eq___const)(haxorg_ImmMarkup, OrgContext*, haxorg_ImmMarkup);
};

struct haxorg_ImmRadioTarget_vtable {
  haxorg_ImmVec const* (*get_words)(haxorg_ImmRadioTarget const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmRadioTarget, OrgContext*, haxorg_ImmRadioTarget);
};

struct haxorg_ImmLatex_vtable {
  bool (*__eq___const)(haxorg_ImmLatex, OrgContext*, haxorg_ImmLatex);
};

struct haxorg_ImmSubtreeLog_vtable {
  haxorg_SubtreeLogHead const* (*get_head)(haxorg_ImmSubtreeLog const*, OrgContext*);
  haxorg_HstdOpt const* (*get_desc)(haxorg_ImmSubtreeLog const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmSubtreeLog, OrgContext*, haxorg_ImmSubtreeLog);
};

struct haxorg_ImmSubtree_vtable {
  int const* (*get_level)(haxorg_ImmSubtree const*, OrgContext*);
  haxorg_HstdOpt const* (*get_treeId)(haxorg_ImmSubtree const*, OrgContext*);
  haxorg_HstdOpt const* (*get_todo)(haxorg_ImmSubtree const*, OrgContext*);
  haxorg_HstdOpt const* (*get_completion)(haxorg_ImmSubtree const*, OrgContext*);
  haxorg_HstdOpt const* (*get_description)(haxorg_ImmSubtree const*, OrgContext*);
  haxorg_ImmVec const* (*get_tags)(haxorg_ImmSubtree const*, OrgContext*);
  haxorg_ImmId const* (*get_title)(haxorg_ImmSubtree const*, OrgContext*);
  haxorg_ImmVec const* (*get_logbook)(haxorg_ImmSubtree const*, OrgContext*);
  haxorg_ImmVec const* (*get_properties)(haxorg_ImmSubtree const*, OrgContext*);
  haxorg_HstdOpt const* (*get_closed)(haxorg_ImmSubtree const*, OrgContext*);
  haxorg_HstdOpt const* (*get_deadline)(haxorg_ImmSubtree const*, OrgContext*);
  haxorg_HstdOpt const* (*get_scheduled)(haxorg_ImmSubtree const*, OrgContext*);
  bool const* (*get_isComment)(haxorg_ImmSubtree const*, OrgContext*);
  bool const* (*get_isArchived)(haxorg_ImmSubtree const*, OrgContext*);
  haxorg_HstdOpt const* (*get_priority)(haxorg_ImmSubtree const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmSubtree, OrgContext*, haxorg_ImmSubtree);
};

struct haxorg_ImmColonExample_vtable {
  bool (*__eq___const)(haxorg_ImmColonExample, OrgContext*, haxorg_ImmColonExample);
};

struct haxorg_ImmCall_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_ImmCall const*, OrgContext*);
  haxorg_AttrGroup const* (*get_attrs)(haxorg_ImmCall const*, OrgContext*);
  bool const* (*get_isCommand)(haxorg_ImmCall const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmCall, OrgContext*, haxorg_ImmCall);
};

struct haxorg_ImmListItem_vtable {
  haxorg_CheckboxState const* (*get_checkbox)(haxorg_ImmListItem const*, OrgContext*);
  haxorg_HstdOpt const* (*get_header)(haxorg_ImmListItem const*, OrgContext*);
  haxorg_HstdOpt const* (*get_bullet)(haxorg_ImmListItem const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmListItem, OrgContext*, haxorg_ImmListItem);
};

struct haxorg_ImmDocumentOptions_vtable {
  haxorg_InitialSubtreeVisibility const* (*get_initialVisibility)(haxorg_ImmDocumentOptions const*, OrgContext*);
  haxorg_ImmVec const* (*get_properties)(haxorg_ImmDocumentOptions const*, OrgContext*);
  haxorg_DocumentExportConfig const* (*get_exportConfig)(haxorg_ImmDocumentOptions const*, OrgContext*);
  haxorg_HstdOpt const* (*get_fixedWidthSections)(haxorg_ImmDocumentOptions const*, OrgContext*);
  haxorg_HstdOpt const* (*get_startupIndented)(haxorg_ImmDocumentOptions const*, OrgContext*);
  haxorg_HstdOpt const* (*get_category)(haxorg_ImmDocumentOptions const*, OrgContext*);
  haxorg_HstdOpt const* (*get_setupfile)(haxorg_ImmDocumentOptions const*, OrgContext*);
  haxorg_HstdOpt const* (*get_maxSubtreeLevelExport)(haxorg_ImmDocumentOptions const*, OrgContext*);
  haxorg_HstdOpt const* (*get_columns)(haxorg_ImmDocumentOptions const*, OrgContext*);
  haxorg_ImmVec const* (*get_todoKeywords)(haxorg_ImmDocumentOptions const*, OrgContext*);
  haxorg_ImmVec const* (*get_doneKeywords)(haxorg_ImmDocumentOptions const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmDocumentOptions, OrgContext*, haxorg_ImmDocumentOptions);
};

struct haxorg_ImmDocumentFragment_vtable {
  int const* (*get_baseLine)(haxorg_ImmDocumentFragment const*, OrgContext*);
  int const* (*get_baseCol)(haxorg_ImmDocumentFragment const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmDocumentFragment, OrgContext*, haxorg_ImmDocumentFragment);
};

struct haxorg_ImmCriticMarkup_vtable {
  haxorg_ImmCriticMarkupKind const* (*get_kind)(haxorg_ImmCriticMarkup const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmCriticMarkup, OrgContext*, haxorg_ImmCriticMarkup);
};

struct haxorg_ImmDocument_vtable {
  haxorg_HstdOpt const* (*get_title)(haxorg_ImmDocument const*, OrgContext*);
  haxorg_HstdOpt const* (*get_author)(haxorg_ImmDocument const*, OrgContext*);
  haxorg_HstdOpt const* (*get_creator)(haxorg_ImmDocument const*, OrgContext*);
  haxorg_ImmVec const* (*get_filetags)(haxorg_ImmDocument const*, OrgContext*);
  haxorg_HstdOpt const* (*get_email)(haxorg_ImmDocument const*, OrgContext*);
  haxorg_ImmVec const* (*get_language)(haxorg_ImmDocument const*, OrgContext*);
  haxorg_ImmId const* (*get_options)(haxorg_ImmDocument const*, OrgContext*);
  haxorg_HstdOpt const* (*get_exportFileName)(haxorg_ImmDocument const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmDocument, OrgContext*, haxorg_ImmDocument);
};

struct haxorg_ImmFileTarget_vtable {
  haxorg_HstdStr const* (*get_path)(haxorg_ImmFileTarget const*, OrgContext*);
  haxorg_HstdOpt const* (*get_line)(haxorg_ImmFileTarget const*, OrgContext*);
  haxorg_HstdOpt const* (*get_searchTarget)(haxorg_ImmFileTarget const*, OrgContext*);
  bool const* (*get_restrictToHeadlines)(haxorg_ImmFileTarget const*, OrgContext*);
  haxorg_HstdOpt const* (*get_targetId)(haxorg_ImmFileTarget const*, OrgContext*);
  haxorg_HstdOpt const* (*get_regexp)(haxorg_ImmFileTarget const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmFileTarget, OrgContext*, haxorg_ImmFileTarget);
};

struct haxorg_ImmTextSeparator_vtable {
  bool (*__eq___const)(haxorg_ImmTextSeparator, OrgContext*, haxorg_ImmTextSeparator);
};

struct haxorg_ImmDocumentGroup_vtable {
  bool (*__eq___const)(haxorg_ImmDocumentGroup, OrgContext*, haxorg_ImmDocumentGroup);
};

struct haxorg_ImmFileDocument_vtable {
  bool (*__eq___const)(haxorg_ImmFileDocument, OrgContext*, haxorg_ImmFileDocument);
};

struct haxorg_ImmFileAttachment_vtable {
  bool (*__eq___const)(haxorg_ImmFileAttachment, OrgContext*, haxorg_ImmFileAttachment);
};

struct haxorg_ImmFileSource_vtable {
  bool (*__eq___const)(haxorg_ImmFileSource, OrgContext*, haxorg_ImmFileSource);
};

struct haxorg_ImmFile_vtable {
  haxorg_HstdStr const* (*get_relPath)(haxorg_ImmFile const*, OrgContext*);
  haxorg_HstdStr const* (*get_absPath)(haxorg_ImmFile const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmFile, OrgContext*, haxorg_ImmFile);
  bool (*isDocument_const)(haxorg_ImmFile, OrgContext*);
  haxorg_ImmFileDocument (*getDocumentConst_const)(haxorg_ImmFile, OrgContext*);
  haxorg_ImmFileDocument (*getDocumentMut)(haxorg_ImmFile, OrgContext*);
  bool (*isAttachment_const)(haxorg_ImmFile, OrgContext*);
  haxorg_ImmFileAttachment (*getAttachmentConst_const)(haxorg_ImmFile, OrgContext*);
  haxorg_ImmFileAttachment (*getAttachmentMut)(haxorg_ImmFile, OrgContext*);
  bool (*isSource_const)(haxorg_ImmFile, OrgContext*);
  haxorg_ImmFileSource (*getSourceConst_const)(haxorg_ImmFile, OrgContext*);
  haxorg_ImmFileSource (*getSourceMut)(haxorg_ImmFile, OrgContext*);
  haxorg_ImmFileKind (*getFileKind_const)(haxorg_ImmFile, OrgContext*);
};

struct haxorg_ImmDirectory_vtable {
  haxorg_HstdStr const* (*get_relPath)(haxorg_ImmDirectory const*, OrgContext*);
  haxorg_HstdStr const* (*get_absPath)(haxorg_ImmDirectory const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmDirectory, OrgContext*, haxorg_ImmDirectory);
};

struct haxorg_ImmSymlink_vtable {
  bool const* (*get_isDirectory)(haxorg_ImmSymlink const*, OrgContext*);
  haxorg_HstdStr const* (*get_absPath)(haxorg_ImmSymlink const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmSymlink, OrgContext*, haxorg_ImmSymlink);
};

struct haxorg_ImmCmdIncludeIncludeBase_vtable {
  bool (*__eq___const)(haxorg_ImmCmdIncludeIncludeBase, OrgContext*, haxorg_ImmCmdIncludeIncludeBase);
};

struct haxorg_ImmCmdIncludeExample_vtable {
  bool (*__eq___const)(haxorg_ImmCmdIncludeExample, OrgContext*, haxorg_ImmCmdIncludeExample);
};

struct haxorg_ImmCmdIncludeExport_vtable {
  haxorg_HstdStr const* (*get_language)(haxorg_ImmCmdIncludeExport const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmCmdIncludeExport, OrgContext*, haxorg_ImmCmdIncludeExport);
};

struct haxorg_ImmCmdIncludeCustom_vtable {
  haxorg_HstdStr const* (*get_blockName)(haxorg_ImmCmdIncludeCustom const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmCmdIncludeCustom, OrgContext*, haxorg_ImmCmdIncludeCustom);
};

struct haxorg_ImmCmdIncludeSrc_vtable {
  haxorg_HstdStr const* (*get_language)(haxorg_ImmCmdIncludeSrc const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmCmdIncludeSrc, OrgContext*, haxorg_ImmCmdIncludeSrc);
};

struct haxorg_ImmCmdIncludeOrgDocument_vtable {
  haxorg_HstdOpt const* (*get_onlyContent)(haxorg_ImmCmdIncludeOrgDocument const*, OrgContext*);
  haxorg_HstdOpt const* (*get_subtreePath)(haxorg_ImmCmdIncludeOrgDocument const*, OrgContext*);
  haxorg_HstdOpt const* (*get_minLevel)(haxorg_ImmCmdIncludeOrgDocument const*, OrgContext*);
  haxorg_HstdOpt const* (*get_customIdTarget)(haxorg_ImmCmdIncludeOrgDocument const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmCmdIncludeOrgDocument, OrgContext*, haxorg_ImmCmdIncludeOrgDocument);
};

struct haxorg_ImmCmdInclude_vtable {
  haxorg_HstdStr const* (*get_path)(haxorg_ImmCmdInclude const*, OrgContext*);
  haxorg_HstdOpt const* (*get_firstLine)(haxorg_ImmCmdInclude const*, OrgContext*);
  haxorg_HstdOpt const* (*get_lastLine)(haxorg_ImmCmdInclude const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmCmdInclude, OrgContext*, haxorg_ImmCmdInclude);
  bool (*isExample_const)(haxorg_ImmCmdInclude, OrgContext*);
  haxorg_ImmCmdIncludeExample (*getExampleConst_const)(haxorg_ImmCmdInclude, OrgContext*);
  haxorg_ImmCmdIncludeExample (*getExampleMut)(haxorg_ImmCmdInclude, OrgContext*);
  bool (*isExport_const)(haxorg_ImmCmdInclude, OrgContext*);
  haxorg_ImmCmdIncludeExport (*getExportConst_const)(haxorg_ImmCmdInclude, OrgContext*);
  haxorg_ImmCmdIncludeExport (*getExportMut)(haxorg_ImmCmdInclude, OrgContext*);
  bool (*isCustom_const)(haxorg_ImmCmdInclude, OrgContext*);
  haxorg_ImmCmdIncludeCustom (*getCustomConst_const)(haxorg_ImmCmdInclude, OrgContext*);
  haxorg_ImmCmdIncludeCustom (*getCustomMut)(haxorg_ImmCmdInclude, OrgContext*);
  bool (*isSrc_const)(haxorg_ImmCmdInclude, OrgContext*);
  haxorg_ImmCmdIncludeSrc (*getSrcConst_const)(haxorg_ImmCmdInclude, OrgContext*);
  haxorg_ImmCmdIncludeSrc (*getSrcMut)(haxorg_ImmCmdInclude, OrgContext*);
  bool (*isOrgDocument_const)(haxorg_ImmCmdInclude, OrgContext*);
  haxorg_ImmCmdIncludeOrgDocument (*getOrgDocumentConst_const)(haxorg_ImmCmdInclude, OrgContext*);
  haxorg_ImmCmdIncludeOrgDocument (*getOrgDocumentMut)(haxorg_ImmCmdInclude, OrgContext*);
  haxorg_ImmCmdIncludeKind (*getIncludeKind_const)(haxorg_ImmCmdInclude, OrgContext*);
};

struct haxorg_Cmd_vtable {
  haxorg_AttrGroup const* (*get_attrs)(haxorg_Cmd const*, OrgContext*);
  haxorg_HstdVec (*getAttrs_const)(haxorg_Cmd, OrgContext*, haxorg_HstdOpt);
  haxorg_HstdOpt (*getFirstAttr_const)(haxorg_Cmd, OrgContext*, haxorg_HstdStr);
};

struct haxorg_CmdCustomRaw_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_CmdCustomRaw const*, OrgContext*);
  bool const* (*get_isAttached)(haxorg_CmdCustomRaw const*, OrgContext*);
  haxorg_HstdStr const* (*get_text)(haxorg_CmdCustomRaw const*, OrgContext*);
};

struct haxorg_CmdCustomText_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_CmdCustomText const*, OrgContext*);
  bool const* (*get_isAttached)(haxorg_CmdCustomText const*, OrgContext*);
  haxorg_SemId const* (*get_text)(haxorg_CmdCustomText const*, OrgContext*);
};

struct haxorg_Link_vtable {
  haxorg_HstdOpt const* (*get_description)(haxorg_Link const*, OrgContext*);
  haxorg_LinkTarget const* (*get_target)(haxorg_Link const*, OrgContext*);
};

struct haxorg_Paragraph_vtable {
  bool (*isFootnoteDefinition_const)(haxorg_Paragraph, OrgContext*);
  haxorg_HstdOpt (*getFootnoteName_const)(haxorg_Paragraph, OrgContext*);
  bool (*hasAdmonition_const)(haxorg_Paragraph, OrgContext*);
  haxorg_HstdVec (*getAdmonitions_const)(haxorg_Paragraph, OrgContext*);
  haxorg_HstdVec (*getAdmonitionNodes_const)(haxorg_Paragraph, OrgContext*);
  bool (*hasTimestamp_const)(haxorg_Paragraph, OrgContext*);
  haxorg_HstdVec (*getTimestamps_const)(haxorg_Paragraph, OrgContext*);
  haxorg_HstdVec (*getTimestampNodes_const)(haxorg_Paragraph, OrgContext*);
  bool (*hasLeadHashtags_const)(haxorg_Paragraph, OrgContext*);
  haxorg_HstdVec (*getLeadHashtags_const)(haxorg_Paragraph, OrgContext*);
  haxorg_HstdVec (*getBody_const)(haxorg_Paragraph, OrgContext*);
};

struct haxorg_List_vtable {
  haxorg_HstdVec (*getListAttrs_const)(haxorg_List, OrgContext*, haxorg_HstdStr);
  haxorg_ListFormattingMode (*getListFormattingMode_const)(haxorg_List, OrgContext*);
  bool (*isDescriptionList_const)(haxorg_List, OrgContext*);
  bool (*isNumberedList_const)(haxorg_List, OrgContext*);
};

struct haxorg_HashTag_vtable {
  haxorg_HashTagText const* (*get_text)(haxorg_HashTag const*, OrgContext*);
};

struct haxorg_InlineFootnote_vtable {
  haxorg_HstdStr const* (*get_tag)(haxorg_InlineFootnote const*, OrgContext*);
  haxorg_HstdOpt const* (*get_definition)(haxorg_InlineFootnote const*, OrgContext*);
};

struct haxorg_InlineExport_vtable {
  haxorg_HstdStr const* (*get_exporter)(haxorg_InlineExport const*, OrgContext*);
  haxorg_HstdStr const* (*get_content)(haxorg_InlineExport const*, OrgContext*);
};

struct haxorg_ImmCmd_vtable {
  haxorg_AttrGroup const* (*get_attrs)(haxorg_ImmCmd const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmCmd, OrgContext*, haxorg_ImmCmd);
};

struct haxorg_ImmCmdCustomRaw_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_ImmCmdCustomRaw const*, OrgContext*);
  bool const* (*get_isAttached)(haxorg_ImmCmdCustomRaw const*, OrgContext*);
  haxorg_HstdStr const* (*get_text)(haxorg_ImmCmdCustomRaw const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmCmdCustomRaw, OrgContext*, haxorg_ImmCmdCustomRaw);
};

struct haxorg_ImmCmdCustomText_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_ImmCmdCustomText const*, OrgContext*);
  bool const* (*get_isAttached)(haxorg_ImmCmdCustomText const*, OrgContext*);
  haxorg_ImmId const* (*get_text)(haxorg_ImmCmdCustomText const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmCmdCustomText, OrgContext*, haxorg_ImmCmdCustomText);
};

struct haxorg_ImmLink_vtable {
  haxorg_HstdOpt const* (*get_description)(haxorg_ImmLink const*, OrgContext*);
  haxorg_LinkTarget const* (*get_target)(haxorg_ImmLink const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmLink, OrgContext*, haxorg_ImmLink);
};

struct haxorg_ImmBlockComment_vtable {
  bool (*__eq___const)(haxorg_ImmBlockComment, OrgContext*, haxorg_ImmBlockComment);
};

struct haxorg_ImmParagraph_vtable {
  bool (*__eq___const)(haxorg_ImmParagraph, OrgContext*, haxorg_ImmParagraph);
};

struct haxorg_ImmList_vtable {
  bool (*__eq___const)(haxorg_ImmList, OrgContext*, haxorg_ImmList);
};

struct haxorg_ImmHashTag_vtable {
  haxorg_HashTagText const* (*get_text)(haxorg_ImmHashTag const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmHashTag, OrgContext*, haxorg_ImmHashTag);
};

struct haxorg_ImmInlineFootnote_vtable {
  haxorg_HstdStr const* (*get_tag)(haxorg_ImmInlineFootnote const*, OrgContext*);
  haxorg_HstdOpt const* (*get_definition)(haxorg_ImmInlineFootnote const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmInlineFootnote, OrgContext*, haxorg_ImmInlineFootnote);
};

struct haxorg_ImmInlineExport_vtable {
  haxorg_HstdStr const* (*get_exporter)(haxorg_ImmInlineExport const*, OrgContext*);
  haxorg_HstdStr const* (*get_content)(haxorg_ImmInlineExport const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmInlineExport, OrgContext*, haxorg_ImmInlineExport);
};

struct haxorg_ImmEscaped_vtable {
  bool (*__eq___const)(haxorg_ImmEscaped, OrgContext*, haxorg_ImmEscaped);
};

struct haxorg_ImmNewline_vtable {
  bool (*__eq___const)(haxorg_ImmNewline, OrgContext*, haxorg_ImmNewline);
};

struct haxorg_ImmSpace_vtable {
  bool (*__eq___const)(haxorg_ImmSpace, OrgContext*, haxorg_ImmSpace);
};

struct haxorg_ImmWord_vtable {
  bool (*__eq___const)(haxorg_ImmWord, OrgContext*, haxorg_ImmWord);
};

struct haxorg_ImmAtMention_vtable {
  bool (*__eq___const)(haxorg_ImmAtMention, OrgContext*, haxorg_ImmAtMention);
};

struct haxorg_ImmRawText_vtable {
  bool (*__eq___const)(haxorg_ImmRawText, OrgContext*, haxorg_ImmRawText);
};

struct haxorg_ImmPunctuation_vtable {
  bool (*__eq___const)(haxorg_ImmPunctuation, OrgContext*, haxorg_ImmPunctuation);
};

struct haxorg_ImmPlaceholder_vtable {
  bool (*__eq___const)(haxorg_ImmPlaceholder, OrgContext*, haxorg_ImmPlaceholder);
};

struct haxorg_ImmBigIdent_vtable {
  bool (*__eq___const)(haxorg_ImmBigIdent, OrgContext*, haxorg_ImmBigIdent);
};

struct haxorg_ImmTextTarget_vtable {
  bool (*__eq___const)(haxorg_ImmTextTarget, OrgContext*, haxorg_ImmTextTarget);
};

struct haxorg_ImmErrorSkipToken_vtable {
  bool (*__eq___const)(haxorg_ImmErrorSkipToken, OrgContext*, haxorg_ImmErrorSkipToken);
};

struct haxorg_ImmBold_vtable {
  bool (*__eq___const)(haxorg_ImmBold, OrgContext*, haxorg_ImmBold);
};

struct haxorg_ImmUnderline_vtable {
  bool (*__eq___const)(haxorg_ImmUnderline, OrgContext*, haxorg_ImmUnderline);
};

struct haxorg_ImmMonospace_vtable {
  bool (*__eq___const)(haxorg_ImmMonospace, OrgContext*, haxorg_ImmMonospace);
};

struct haxorg_ImmMarkQuote_vtable {
  bool (*__eq___const)(haxorg_ImmMarkQuote, OrgContext*, haxorg_ImmMarkQuote);
};

struct haxorg_ImmVerbatim_vtable {
  bool (*__eq___const)(haxorg_ImmVerbatim, OrgContext*, haxorg_ImmVerbatim);
};

struct haxorg_ImmItalic_vtable {
  bool (*__eq___const)(haxorg_ImmItalic, OrgContext*, haxorg_ImmItalic);
};

struct haxorg_ImmStrike_vtable {
  bool (*__eq___const)(haxorg_ImmStrike, OrgContext*, haxorg_ImmStrike);
};

struct haxorg_ImmPar_vtable {
  bool (*__eq___const)(haxorg_ImmPar, OrgContext*, haxorg_ImmPar);
};

struct haxorg_ImmAdapterDirectoryAPI_vtable {
  haxorg_StdOptional (*getFsSubnode_const)(haxorg_ImmAdapterDirectoryAPI, OrgContext*, haxorg_HstdStr, bool);
};

struct haxorg_CmdCreator_vtable {
  haxorg_SemId const* (*get_text)(haxorg_CmdCreator const*, OrgContext*);
};

struct haxorg_CmdAuthor_vtable {
  haxorg_SemId const* (*get_text)(haxorg_CmdAuthor const*, OrgContext*);
};

struct haxorg_CmdEmail_vtable {
  haxorg_HstdStr const* (*get_text)(haxorg_CmdEmail const*, OrgContext*);
};

struct haxorg_CmdLanguage_vtable {
  haxorg_HstdStr const* (*get_text)(haxorg_CmdLanguage const*, OrgContext*);
};

struct haxorg_CmdCustomArgs_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_CmdCustomArgs const*, OrgContext*);
  bool const* (*get_isAttached)(haxorg_CmdCustomArgs const*, OrgContext*);
};

struct haxorg_CmdTblfm_vtable {
  haxorg_Tblfm const* (*get_expr)(haxorg_CmdTblfm const*, OrgContext*);
};

struct haxorg_Cell_vtable {
  bool const* (*get_isBlock)(haxorg_Cell const*, OrgContext*);
};

struct haxorg_Row_vtable {
  haxorg_HstdVec const* (*get_cells)(haxorg_Row const*, OrgContext*);
  bool const* (*get_isBlock)(haxorg_Row const*, OrgContext*);
};

struct haxorg_ImmBlock_vtable {
  bool (*__eq___const)(haxorg_ImmBlock, OrgContext*, haxorg_ImmBlock);
};

struct haxorg_ImmLineCommand_vtable {
  bool (*__eq___const)(haxorg_ImmLineCommand, OrgContext*, haxorg_ImmLineCommand);
};

struct haxorg_ImmCmdCreator_vtable {
  haxorg_ImmId const* (*get_text)(haxorg_ImmCmdCreator const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmCmdCreator, OrgContext*, haxorg_ImmCmdCreator);
};

struct haxorg_ImmCmdAuthor_vtable {
  haxorg_ImmId const* (*get_text)(haxorg_ImmCmdAuthor const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmCmdAuthor, OrgContext*, haxorg_ImmCmdAuthor);
};

struct haxorg_ImmCmdEmail_vtable {
  haxorg_HstdStr const* (*get_text)(haxorg_ImmCmdEmail const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmCmdEmail, OrgContext*, haxorg_ImmCmdEmail);
};

struct haxorg_ImmCmdLanguage_vtable {
  haxorg_HstdStr const* (*get_text)(haxorg_ImmCmdLanguage const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmCmdLanguage, OrgContext*, haxorg_ImmCmdLanguage);
};

struct haxorg_ImmCmdCustomArgs_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_ImmCmdCustomArgs const*, OrgContext*);
  bool const* (*get_isAttached)(haxorg_ImmCmdCustomArgs const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmCmdCustomArgs, OrgContext*, haxorg_ImmCmdCustomArgs);
};

struct haxorg_ImmCmdTblfm_vtable {
  haxorg_Tblfm const* (*get_expr)(haxorg_ImmCmdTblfm const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmCmdTblfm, OrgContext*, haxorg_ImmCmdTblfm);
};

struct haxorg_ImmCell_vtable {
  bool const* (*get_isBlock)(haxorg_ImmCell const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmCell, OrgContext*, haxorg_ImmCell);
};

struct haxorg_ImmRow_vtable {
  haxorg_ImmVec const* (*get_cells)(haxorg_ImmRow const*, OrgContext*);
  bool const* (*get_isBlock)(haxorg_ImmRow const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmRow, OrgContext*, haxorg_ImmRow);
};

struct haxorg_ImmStmtAdapter_vtable {
  haxorg_ImmVec (*getAttached_const)(haxorg_ImmStmtAdapter, OrgContext*);
};

struct haxorg_ImmErrorItemAdapter_vtable {
  haxorg_OrgDiagnostics (*getDiag_const)(haxorg_ImmErrorItemAdapter, OrgContext*);
};

struct haxorg_ImmErrorGroupAdapter_vtable {
  haxorg_ImmVec (*getDiagnostics_const)(haxorg_ImmErrorGroupAdapter, OrgContext*);
};

struct haxorg_ImmErrorSkipGroupAdapter_vtable {
  haxorg_ImmVec (*getSkipped_const)(haxorg_ImmErrorSkipGroupAdapter, OrgContext*);
};

struct haxorg_ImmTimeAdapter_vtable {
  bool (*getIsActive_const)(haxorg_ImmTimeAdapter, OrgContext*);
};

struct haxorg_ImmTimeRangeAdapter_vtable {
  haxorg_ImmAdapter (*getFrom_const)(haxorg_ImmTimeRangeAdapter, OrgContext*);
  haxorg_ImmAdapter (*getTo_const)(haxorg_ImmTimeRangeAdapter, OrgContext*);
};

struct haxorg_ImmMacroAdapter_vtable {
  haxorg_HstdStr (*getName_const)(haxorg_ImmMacroAdapter, OrgContext*);
  haxorg_AttrGroup (*getAttrs_const)(haxorg_ImmMacroAdapter, OrgContext*);
};

struct haxorg_ImmSymbolAdapter_vtable {
  haxorg_HstdStr (*getName_const)(haxorg_ImmSymbolAdapter, OrgContext*);
  haxorg_ImmVec (*getParameters_const)(haxorg_ImmSymbolAdapter, OrgContext*);
  haxorg_ImmVec (*getPositional_const)(haxorg_ImmSymbolAdapter, OrgContext*);
};

struct haxorg_ImmLeafAdapter_vtable {
  haxorg_HstdStr (*getText_const)(haxorg_ImmLeafAdapter, OrgContext*);
};

struct haxorg_ImmSubtreeLogAdapter_vtable {
  haxorg_SubtreeLogHead (*getHead_const)(haxorg_ImmSubtreeLogAdapter, OrgContext*);
  haxorg_HstdOpt (*getDesc_const)(haxorg_ImmSubtreeLogAdapter, OrgContext*);
};

struct haxorg_ImmCallAdapter_vtable {
  haxorg_HstdStr (*getName_const)(haxorg_ImmCallAdapter, OrgContext*);
  haxorg_AttrGroup (*getAttrs_const)(haxorg_ImmCallAdapter, OrgContext*);
  bool (*getIsCommand_const)(haxorg_ImmCallAdapter, OrgContext*);
};

struct haxorg_ImmFileAdapter_vtable {
  haxorg_HstdStr (*getRelPath_const)(haxorg_ImmFileAdapter, OrgContext*);
  haxorg_HstdStr (*getAbsPath_const)(haxorg_ImmFileAdapter, OrgContext*);
};

struct haxorg_ImmDirectoryAdapter_vtable {
  haxorg_HstdStr (*getRelPath_const)(haxorg_ImmDirectoryAdapter, OrgContext*);
  haxorg_HstdStr (*getAbsPath_const)(haxorg_ImmDirectoryAdapter, OrgContext*);
};

struct haxorg_ImmSymlinkAdapter_vtable {
  bool (*getIsDirectory_const)(haxorg_ImmSymlinkAdapter, OrgContext*);
  haxorg_HstdStr (*getAbsPath_const)(haxorg_ImmSymlinkAdapter, OrgContext*);
};

struct haxorg_ImmDocumentFragmentAdapter_vtable {
  int (*getBaseLine_const)(haxorg_ImmDocumentFragmentAdapter, OrgContext*);
  int (*getBaseCol_const)(haxorg_ImmDocumentFragmentAdapter, OrgContext*);
};

struct haxorg_ImmCriticMarkupAdapter_vtable {
  haxorg_ImmCriticMarkupKind (*getKind_const)(haxorg_ImmCriticMarkupAdapter, OrgContext*);
};

struct haxorg_ImmListItemAdapter_vtable {
  haxorg_CheckboxState (*getCheckbox_const)(haxorg_ImmListItemAdapter, OrgContext*);
  haxorg_HstdOpt (*getHeader_const)(haxorg_ImmListItemAdapter, OrgContext*);
  haxorg_HstdOpt (*getBullet_const)(haxorg_ImmListItemAdapter, OrgContext*);
};

struct haxorg_ImmDocumentOptionsAdapter_vtable {
  haxorg_InitialSubtreeVisibility (*getInitialVisibility_const)(haxorg_ImmDocumentOptionsAdapter, OrgContext*);
  haxorg_ImmVec (*getProperties_const)(haxorg_ImmDocumentOptionsAdapter, OrgContext*);
  haxorg_DocumentExportConfig (*getExportConfig_const)(haxorg_ImmDocumentOptionsAdapter, OrgContext*);
  haxorg_HstdOpt (*getFixedWidthSections_const)(haxorg_ImmDocumentOptionsAdapter, OrgContext*);
  haxorg_HstdOpt (*getStartupIndented_const)(haxorg_ImmDocumentOptionsAdapter, OrgContext*);
  haxorg_HstdOpt (*getCategory_const)(haxorg_ImmDocumentOptionsAdapter, OrgContext*);
  haxorg_HstdOpt (*getSetupfile_const)(haxorg_ImmDocumentOptionsAdapter, OrgContext*);
  haxorg_HstdOpt (*getMaxSubtreeLevelExport_const)(haxorg_ImmDocumentOptionsAdapter, OrgContext*);
  haxorg_HstdOpt (*getColumns_const)(haxorg_ImmDocumentOptionsAdapter, OrgContext*);
  haxorg_ImmVec (*getTodoKeywords_const)(haxorg_ImmDocumentOptionsAdapter, OrgContext*);
  haxorg_ImmVec (*getDoneKeywords_const)(haxorg_ImmDocumentOptionsAdapter, OrgContext*);
};

struct haxorg_ImmDocumentAdapter_vtable {
  haxorg_HstdOpt (*getTitle_const)(haxorg_ImmDocumentAdapter, OrgContext*);
  haxorg_HstdOpt (*getAuthor_const)(haxorg_ImmDocumentAdapter, OrgContext*);
  haxorg_HstdOpt (*getCreator_const)(haxorg_ImmDocumentAdapter, OrgContext*);
  haxorg_ImmVec (*getFiletags_const)(haxorg_ImmDocumentAdapter, OrgContext*);
  haxorg_HstdOpt (*getEmail_const)(haxorg_ImmDocumentAdapter, OrgContext*);
  haxorg_ImmVec (*getLanguage_const)(haxorg_ImmDocumentAdapter, OrgContext*);
  haxorg_ImmAdapter (*getOptions_const)(haxorg_ImmDocumentAdapter, OrgContext*);
  haxorg_HstdOpt (*getExportFileName_const)(haxorg_ImmDocumentAdapter, OrgContext*);
};

struct haxorg_ImmFileTargetAdapter_vtable {
  haxorg_HstdStr (*getPath_const)(haxorg_ImmFileTargetAdapter, OrgContext*);
  haxorg_HstdOpt (*getLine_const)(haxorg_ImmFileTargetAdapter, OrgContext*);
  haxorg_HstdOpt (*getSearchTarget_const)(haxorg_ImmFileTargetAdapter, OrgContext*);
  bool (*getRestrictToHeadlines_const)(haxorg_ImmFileTargetAdapter, OrgContext*);
  haxorg_HstdOpt (*getTargetId_const)(haxorg_ImmFileTargetAdapter, OrgContext*);
  haxorg_HstdOpt (*getRegexp_const)(haxorg_ImmFileTargetAdapter, OrgContext*);
};

struct haxorg_ImmCmdIncludeAdapter_vtable {
  haxorg_HstdStr (*getPath_const)(haxorg_ImmCmdIncludeAdapter, OrgContext*);
  haxorg_HstdOpt (*getFirstLine_const)(haxorg_ImmCmdIncludeAdapter, OrgContext*);
  haxorg_HstdOpt (*getLastLine_const)(haxorg_ImmCmdIncludeAdapter, OrgContext*);
};

struct haxorg_BlockDynamicFallback_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_BlockDynamicFallback const*, OrgContext*);
};

struct haxorg_BlockExport_vtable {
  haxorg_HstdStr const* (*get_exporter)(haxorg_BlockExport const*, OrgContext*);
  haxorg_HstdStr const* (*get_content)(haxorg_BlockExport const*, OrgContext*);
  haxorg_HstdOpt (*getPlacement_const)(haxorg_BlockExport, OrgContext*);
};

struct haxorg_BlockCodeEvalResult_vtable {
  haxorg_HstdVec const* (*get_raw)(haxorg_BlockCodeEvalResult const*, OrgContext*);
  haxorg_SemId const* (*get_node)(haxorg_BlockCodeEvalResult const*, OrgContext*);
};

struct haxorg_BlockCode_vtable {
  haxorg_HstdOpt const* (*get_lang)(haxorg_BlockCode const*, OrgContext*);
  haxorg_HstdVec const* (*get_result)(haxorg_BlockCode const*, OrgContext*);
  haxorg_HstdVec const* (*get_lines)(haxorg_BlockCode const*, OrgContext*);
  haxorg_AttrGroup const* (*get_switches)(haxorg_BlockCode const*, OrgContext*);
  haxorg_HstdOpt (*getVariable_const)(haxorg_BlockCode, OrgContext*, haxorg_HstdStr);
};

struct haxorg_Table_vtable {
  haxorg_HstdVec const* (*get_rows)(haxorg_Table const*, OrgContext*);
  bool const* (*get_isBlock)(haxorg_Table const*, OrgContext*);
};

struct haxorg_ImmBlockCenter_vtable {
  bool (*__eq___const)(haxorg_ImmBlockCenter, OrgContext*, haxorg_ImmBlockCenter);
};

struct haxorg_ImmBlockQuote_vtable {
  bool (*__eq___const)(haxorg_ImmBlockQuote, OrgContext*, haxorg_ImmBlockQuote);
};

struct haxorg_ImmBlockVerse_vtable {
  bool (*__eq___const)(haxorg_ImmBlockVerse, OrgContext*, haxorg_ImmBlockVerse);
};

struct haxorg_ImmBlockDynamicFallback_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_ImmBlockDynamicFallback const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmBlockDynamicFallback, OrgContext*, haxorg_ImmBlockDynamicFallback);
};

struct haxorg_ImmBlockExample_vtable {
  bool (*__eq___const)(haxorg_ImmBlockExample, OrgContext*, haxorg_ImmBlockExample);
};

struct haxorg_ImmBlockExport_vtable {
  haxorg_HstdStr const* (*get_exporter)(haxorg_ImmBlockExport const*, OrgContext*);
  haxorg_HstdStr const* (*get_content)(haxorg_ImmBlockExport const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmBlockExport, OrgContext*, haxorg_ImmBlockExport);
};

struct haxorg_ImmBlockAdmonition_vtable {
  bool (*__eq___const)(haxorg_ImmBlockAdmonition, OrgContext*, haxorg_ImmBlockAdmonition);
};

struct haxorg_ImmBlockCodeEvalResult_vtable {
  haxorg_ImmVec const* (*get_raw)(haxorg_ImmBlockCodeEvalResult const*, OrgContext*);
  haxorg_ImmId const* (*get_node)(haxorg_ImmBlockCodeEvalResult const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmBlockCodeEvalResult, OrgContext*, haxorg_ImmBlockCodeEvalResult);
};

struct haxorg_ImmBlockCode_vtable {
  haxorg_HstdOpt const* (*get_lang)(haxorg_ImmBlockCode const*, OrgContext*);
  haxorg_ImmVec const* (*get_result)(haxorg_ImmBlockCode const*, OrgContext*);
  haxorg_ImmVec const* (*get_lines)(haxorg_ImmBlockCode const*, OrgContext*);
  haxorg_AttrGroup const* (*get_switches)(haxorg_ImmBlockCode const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmBlockCode, OrgContext*, haxorg_ImmBlockCode);
};

struct haxorg_ImmTable_vtable {
  haxorg_ImmVec const* (*get_rows)(haxorg_ImmTable const*, OrgContext*);
  bool const* (*get_isBlock)(haxorg_ImmTable const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmTable, OrgContext*, haxorg_ImmTable);
};

struct haxorg_ImmAttached_vtable {
  bool (*__eq___const)(haxorg_ImmAttached, OrgContext*, haxorg_ImmAttached);
};

struct haxorg_ImmCmdAdapter_vtable {
  haxorg_AttrGroup (*getAttrs_const)(haxorg_ImmCmdAdapter, OrgContext*);
};

struct haxorg_ImmCmdCustomRawAdapter_vtable {
  haxorg_HstdStr (*getName_const)(haxorg_ImmCmdCustomRawAdapter, OrgContext*);
  bool (*getIsAttached_const)(haxorg_ImmCmdCustomRawAdapter, OrgContext*);
  haxorg_HstdStr (*getText_const)(haxorg_ImmCmdCustomRawAdapter, OrgContext*);
};

struct haxorg_ImmCmdCustomTextAdapter_vtable {
  haxorg_HstdStr (*getName_const)(haxorg_ImmCmdCustomTextAdapter, OrgContext*);
  bool (*getIsAttached_const)(haxorg_ImmCmdCustomTextAdapter, OrgContext*);
  haxorg_ImmAdapter (*getText_const)(haxorg_ImmCmdCustomTextAdapter, OrgContext*);
};

struct haxorg_ImmHashTagAdapter_vtable {
  haxorg_HashTagText (*getText_const)(haxorg_ImmHashTagAdapter, OrgContext*);
};

struct haxorg_ImmInlineFootnoteAdapter_vtable {
  haxorg_HstdStr (*getTag_const)(haxorg_ImmInlineFootnoteAdapter, OrgContext*);
  haxorg_HstdOpt (*getDefinition_const)(haxorg_ImmInlineFootnoteAdapter, OrgContext*);
};

struct haxorg_ImmRadioTargetAdapter_vtable {
  haxorg_ImmVec (*getWords_const)(haxorg_ImmRadioTargetAdapter, OrgContext*);
};

struct haxorg_CmdCaption_vtable {
  haxorg_SemId const* (*get_text)(haxorg_CmdCaption const*, OrgContext*);
};

struct haxorg_CmdColumns_vtable {
  haxorg_ColumnView const* (*get_view)(haxorg_CmdColumns const*, OrgContext*);
};

struct haxorg_CmdName_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_CmdName const*, OrgContext*);
};

struct haxorg_CmdCall_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_CmdCall const*, OrgContext*);
  haxorg_HstdOpt const* (*get_fileName)(haxorg_CmdCall const*, OrgContext*);
  haxorg_AttrGroup const* (*get_insideHeaderAttrs)(haxorg_CmdCall const*, OrgContext*);
  haxorg_AttrGroup const* (*get_callAttrs)(haxorg_CmdCall const*, OrgContext*);
  haxorg_AttrGroup const* (*get_endHeaderAttrs)(haxorg_CmdCall const*, OrgContext*);
  haxorg_HstdVec const* (*get_result)(haxorg_CmdCall const*, OrgContext*);
};

struct haxorg_CmdAttr_vtable {
  haxorg_HstdStr const* (*get_target)(haxorg_CmdAttr const*, OrgContext*);
};

struct haxorg_CmdExport_vtable {
  haxorg_HstdStr const* (*get_exporter)(haxorg_CmdExport const*, OrgContext*);
  haxorg_HstdStr const* (*get_content)(haxorg_CmdExport const*, OrgContext*);
};

struct haxorg_ImmCmdCaption_vtable {
  haxorg_ImmId const* (*get_text)(haxorg_ImmCmdCaption const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmCmdCaption, OrgContext*, haxorg_ImmCmdCaption);
};

struct haxorg_ImmCmdColumns_vtable {
  haxorg_ColumnView const* (*get_view)(haxorg_ImmCmdColumns const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmCmdColumns, OrgContext*, haxorg_ImmCmdColumns);
};

struct haxorg_ImmCmdName_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_ImmCmdName const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmCmdName, OrgContext*, haxorg_ImmCmdName);
};

struct haxorg_ImmCmdCall_vtable {
  haxorg_HstdStr const* (*get_name)(haxorg_ImmCmdCall const*, OrgContext*);
  haxorg_HstdOpt const* (*get_fileName)(haxorg_ImmCmdCall const*, OrgContext*);
  haxorg_AttrGroup const* (*get_insideHeaderAttrs)(haxorg_ImmCmdCall const*, OrgContext*);
  haxorg_AttrGroup const* (*get_callAttrs)(haxorg_ImmCmdCall const*, OrgContext*);
  haxorg_AttrGroup const* (*get_endHeaderAttrs)(haxorg_ImmCmdCall const*, OrgContext*);
  haxorg_ImmVec const* (*get_result)(haxorg_ImmCmdCall const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmCmdCall, OrgContext*, haxorg_ImmCmdCall);
};

struct haxorg_ImmCmdAttr_vtable {
  haxorg_HstdStr const* (*get_target)(haxorg_ImmCmdAttr const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmCmdAttr, OrgContext*, haxorg_ImmCmdAttr);
};

struct haxorg_ImmCmdExport_vtable {
  haxorg_HstdStr const* (*get_exporter)(haxorg_ImmCmdExport const*, OrgContext*);
  haxorg_HstdStr const* (*get_content)(haxorg_ImmCmdExport const*, OrgContext*);
  bool (*__eq___const)(haxorg_ImmCmdExport, OrgContext*, haxorg_ImmCmdExport);
};

struct haxorg_ImmCmdCustomArgsAdapter_vtable {
  haxorg_HstdStr (*getName_const)(haxorg_ImmCmdCustomArgsAdapter, OrgContext*);
  bool (*getIsAttached_const)(haxorg_ImmCmdCustomArgsAdapter, OrgContext*);
};

struct haxorg_ImmCmdCreatorAdapter_vtable {
  haxorg_ImmAdapter (*getText_const)(haxorg_ImmCmdCreatorAdapter, OrgContext*);
};

struct haxorg_ImmCmdAuthorAdapter_vtable {
  haxorg_ImmAdapter (*getText_const)(haxorg_ImmCmdAuthorAdapter, OrgContext*);
};

struct haxorg_ImmCmdEmailAdapter_vtable {
  haxorg_HstdStr (*getText_const)(haxorg_ImmCmdEmailAdapter, OrgContext*);
};

struct haxorg_ImmCmdLanguageAdapter_vtable {
  haxorg_HstdStr (*getText_const)(haxorg_ImmCmdLanguageAdapter, OrgContext*);
};

struct haxorg_ImmCmdTblfmAdapter_vtable {
  haxorg_Tblfm (*getExpr_const)(haxorg_ImmCmdTblfmAdapter, OrgContext*);
};

struct haxorg_ImmCellAdapter_vtable {
  bool (*getIsBlock_const)(haxorg_ImmCellAdapter, OrgContext*);
};

struct haxorg_ImmRowAdapter_vtable {
  haxorg_ImmVec (*getCells_const)(haxorg_ImmRowAdapter, OrgContext*);
  bool (*getIsBlock_const)(haxorg_ImmRowAdapter, OrgContext*);
};

struct haxorg_ImmInlineExportAdapter_vtable {
  haxorg_HstdStr (*getExporter_const)(haxorg_ImmInlineExportAdapter, OrgContext*);
  haxorg_HstdStr (*getContent_const)(haxorg_ImmInlineExportAdapter, OrgContext*);
};

struct haxorg_ImmCmdExportAdapter_vtable {
  haxorg_HstdStr (*getExporter_const)(haxorg_ImmCmdExportAdapter, OrgContext*);
  haxorg_HstdStr (*getContent_const)(haxorg_ImmCmdExportAdapter, OrgContext*);
};

struct haxorg_ImmBlockExportAdapter_vtable {
  haxorg_HstdStr (*getExporter_const)(haxorg_ImmBlockExportAdapter, OrgContext*);
  haxorg_HstdStr (*getContent_const)(haxorg_ImmBlockExportAdapter, OrgContext*);
};

struct haxorg_ImmBlockDynamicFallbackAdapter_vtable {
  haxorg_HstdStr (*getName_const)(haxorg_ImmBlockDynamicFallbackAdapter, OrgContext*);
};

struct haxorg_ImmBlockCodeEvalResultAdapter_vtable {
  haxorg_ImmVec (*getRaw_const)(haxorg_ImmBlockCodeEvalResultAdapter, OrgContext*);
  haxorg_ImmAdapter (*getNode_const)(haxorg_ImmBlockCodeEvalResultAdapter, OrgContext*);
};

struct haxorg_ImmBlockCodeAdapter_vtable {
  haxorg_HstdOpt (*getLang_const)(haxorg_ImmBlockCodeAdapter, OrgContext*);
  haxorg_ImmVec (*getResult_const)(haxorg_ImmBlockCodeAdapter, OrgContext*);
  haxorg_ImmVec (*getLines_const)(haxorg_ImmBlockCodeAdapter, OrgContext*);
  haxorg_AttrGroup (*getSwitches_const)(haxorg_ImmBlockCodeAdapter, OrgContext*);
};

struct haxorg_ImmTableAdapter_vtable {
  haxorg_ImmVec (*getRows_const)(haxorg_ImmTableAdapter, OrgContext*);
  bool (*getIsBlock_const)(haxorg_ImmTableAdapter, OrgContext*);
};

struct haxorg_ImmCmdCaptionAdapter_vtable {
  haxorg_ImmAdapter (*getText_const)(haxorg_ImmCmdCaptionAdapter, OrgContext*);
};

struct haxorg_ImmCmdColumnsAdapter_vtable {
  haxorg_ColumnView (*getView_const)(haxorg_ImmCmdColumnsAdapter, OrgContext*);
};

struct haxorg_ImmCmdNameAdapter_vtable {
  haxorg_HstdStr (*getName_const)(haxorg_ImmCmdNameAdapter, OrgContext*);
};

struct haxorg_ImmCmdCallAdapter_vtable {
  haxorg_HstdStr (*getName_const)(haxorg_ImmCmdCallAdapter, OrgContext*);
  haxorg_HstdOpt (*getFileName_const)(haxorg_ImmCmdCallAdapter, OrgContext*);
  haxorg_AttrGroup (*getInsideHeaderAttrs_const)(haxorg_ImmCmdCallAdapter, OrgContext*);
  haxorg_AttrGroup (*getCallAttrs_const)(haxorg_ImmCmdCallAdapter, OrgContext*);
  haxorg_AttrGroup (*getEndHeaderAttrs_const)(haxorg_ImmCmdCallAdapter, OrgContext*);
  haxorg_ImmVec (*getResult_const)(haxorg_ImmCmdCallAdapter, OrgContext*);
};

struct haxorg_ImmCmdAttrAdapter_vtable {
  haxorg_HstdStr (*getTarget_const)(haxorg_ImmCmdAttrAdapter, OrgContext*);
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
