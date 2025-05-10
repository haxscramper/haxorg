/* clang-format off */
import * as haxorg_wasm from "./haxorg_utility_types";
declare module "haxorg_wasm_types" {
  export interface haxorg_wasm_module {
    UserTimeBreakdown: UserTimeBreakdownConstructor;
    UserTime: UserTimeConstructor;
    ParseLineCol: ParseLineColConstructor;
    OperationsTracer: OperationsTracerConstructor;
    OrgJson: OrgJsonConstructor;
    Org: OrgConstructor;
    ImmId: ImmIdConstructor;
    ImmPathStep: ImmPathStepConstructor;
    ImmPath: ImmPathConstructor;
    ImmUniqId: ImmUniqIdConstructor;
    ImmNoneValueRead: ImmNoneValueReadConstructor;
    ImmErrorItemValueRead: ImmErrorItemValueReadConstructor;
    ImmErrorGroupValueRead: ImmErrorGroupValueReadConstructor;
    ImmStmtListValueRead: ImmStmtListValueReadConstructor;
    ImmEmptyValueRead: ImmEmptyValueReadConstructor;
    ImmCmdCaptionValueRead: ImmCmdCaptionValueReadConstructor;
    ImmCmdColumnsValueRead: ImmCmdColumnsValueReadConstructor;
    ImmCmdNameValueRead: ImmCmdNameValueReadConstructor;
    ImmCmdCustomArgsValueRead: ImmCmdCustomArgsValueReadConstructor;
    ImmCmdCustomRawValueRead: ImmCmdCustomRawValueReadConstructor;
    ImmCmdCustomTextValueRead: ImmCmdCustomTextValueReadConstructor;
    ImmCmdCallValueRead: ImmCmdCallValueReadConstructor;
    ImmCmdTblfmValueRead: ImmCmdTblfmValueReadConstructor;
    ImmHashTagValueRead: ImmHashTagValueReadConstructor;
    ImmInlineFootnoteValueRead: ImmInlineFootnoteValueReadConstructor;
    ImmInlineExportValueRead: ImmInlineExportValueReadConstructor;
    ImmTimeValueRead: ImmTimeValueReadConstructor;
    ImmTimeRangeValueRead: ImmTimeRangeValueReadConstructor;
    ImmMacroValueRead: ImmMacroValueReadConstructor;
    ImmSymbolValueRead: ImmSymbolValueReadConstructor;
    ImmEscapedValueRead: ImmEscapedValueReadConstructor;
    ImmNewlineValueRead: ImmNewlineValueReadConstructor;
    ImmSpaceValueRead: ImmSpaceValueReadConstructor;
    ImmWordValueRead: ImmWordValueReadConstructor;
    ImmAtMentionValueRead: ImmAtMentionValueReadConstructor;
    ImmRawTextValueRead: ImmRawTextValueReadConstructor;
    ImmPunctuationValueRead: ImmPunctuationValueReadConstructor;
    ImmPlaceholderValueRead: ImmPlaceholderValueReadConstructor;
    ImmBigIdentValueRead: ImmBigIdentValueReadConstructor;
    ImmTextTargetValueRead: ImmTextTargetValueReadConstructor;
    ImmBoldValueRead: ImmBoldValueReadConstructor;
    ImmUnderlineValueRead: ImmUnderlineValueReadConstructor;
    ImmMonospaceValueRead: ImmMonospaceValueReadConstructor;
    ImmMarkQuoteValueRead: ImmMarkQuoteValueReadConstructor;
    ImmVerbatimValueRead: ImmVerbatimValueReadConstructor;
    ImmItalicValueRead: ImmItalicValueReadConstructor;
    ImmStrikeValueRead: ImmStrikeValueReadConstructor;
    ImmParValueRead: ImmParValueReadConstructor;
    ImmRadioTargetValueRead: ImmRadioTargetValueReadConstructor;
    ImmLatexValueRead: ImmLatexValueReadConstructor;
    ImmLinkValueRead: ImmLinkValueReadConstructor;
    ImmBlockCenterValueRead: ImmBlockCenterValueReadConstructor;
    ImmBlockQuoteValueRead: ImmBlockQuoteValueReadConstructor;
    ImmBlockCommentValueRead: ImmBlockCommentValueReadConstructor;
    ImmBlockVerseValueRead: ImmBlockVerseValueReadConstructor;
    ImmBlockDynamicFallbackValueRead: ImmBlockDynamicFallbackValueReadConstructor;
    ImmBlockExampleValueRead: ImmBlockExampleValueReadConstructor;
    ImmBlockExportValueRead: ImmBlockExportValueReadConstructor;
    ImmBlockAdmonitionValueRead: ImmBlockAdmonitionValueReadConstructor;
    ImmBlockCodeEvalResultValueRead: ImmBlockCodeEvalResultValueReadConstructor;
    ImmBlockCodeValueRead: ImmBlockCodeValueReadConstructor;
    ImmSubtreeLogValueRead: ImmSubtreeLogValueReadConstructor;
    ImmSubtreeValueRead: ImmSubtreeValueReadConstructor;
    ImmCellValueRead: ImmCellValueReadConstructor;
    ImmRowValueRead: ImmRowValueReadConstructor;
    ImmTableValueRead: ImmTableValueReadConstructor;
    ImmParagraphValueRead: ImmParagraphValueReadConstructor;
    ImmColonExampleValueRead: ImmColonExampleValueReadConstructor;
    ImmCmdAttrValueRead: ImmCmdAttrValueReadConstructor;
    ImmCmdExportValueRead: ImmCmdExportValueReadConstructor;
    ImmCallValueRead: ImmCallValueReadConstructor;
    ImmListValueRead: ImmListValueReadConstructor;
    ImmListItemValueRead: ImmListItemValueReadConstructor;
    ImmDocumentOptionsValueRead: ImmDocumentOptionsValueReadConstructor;
    ImmDocumentFragmentValueRead: ImmDocumentFragmentValueReadConstructor;
    ImmCriticMarkupValueRead: ImmCriticMarkupValueReadConstructor;
    ImmDocumentValueRead: ImmDocumentValueReadConstructor;
    ImmFileTargetValueRead: ImmFileTargetValueReadConstructor;
    ImmTextSeparatorValueRead: ImmTextSeparatorValueReadConstructor;
    ImmDocumentGroupValueRead: ImmDocumentGroupValueReadConstructor;
    ImmFileValueRead: ImmFileValueReadConstructor;
    ImmDirectoryValueRead: ImmDirectoryValueReadConstructor;
    ImmSymlinkValueRead: ImmSymlinkValueReadConstructor;
    ImmCmdIncludeValueRead: ImmCmdIncludeValueReadConstructor;
    ImmAstContext: ImmAstContextConstructor;
    ImmAstVersion: ImmAstVersionConstructor;
    ImmAdapter: ImmAdapterConstructor;
    ImmAdapterTreeReprConf: ImmAdapterTreeReprConfConstructor;
    ImmAdapterVirtualBase: ImmAdapterVirtualBaseConstructor;
    OrgParseFragment: OrgParseFragmentConstructor;
    OrgParseParameters: OrgParseParametersConstructor;
    OrgDirectoryParseParameters: OrgDirectoryParseParametersConstructor;
    OrgYamlExportOpts: OrgYamlExportOptsConstructor;
    OrgTreeExportOpts: OrgTreeExportOptsConstructor;
    AstTrackingPath: AstTrackingPathConstructor;
    AstTrackingAlternatives: AstTrackingAlternativesConstructor;
    AstTrackingGroup: AstTrackingGroupConstructor;
    AstTrackingGroupRadioTarget: AstTrackingGroupRadioTargetConstructor;
    AstTrackingGroupSingle: AstTrackingGroupSingleConstructor;
    AstTrackingGroupTrackedHashtag: AstTrackingGroupTrackedHashtagConstructor;
    AstTrackingMap: AstTrackingMapConstructor;
    SequenceSegment: SequenceSegmentConstructor;
    SequenceSegmentGroup: SequenceSegmentGroupConstructor;
    SequenceAnnotationTag: SequenceAnnotationTagConstructor;
    SequenceAnnotation: SequenceAnnotationConstructor;
    GraphMapLink: GraphMapLinkConstructor;
    GraphMapLinkLink: GraphMapLinkLinkConstructor;
    GraphMapLinkRadio: GraphMapLinkRadioConstructor;
    GraphMapNodeProp: GraphMapNodePropConstructor;
    GraphMapEdgeProp: GraphMapEdgePropConstructor;
    GraphMapNode: GraphMapNodeConstructor;
    GraphMapEdge: GraphMapEdgeConstructor;
    GraphMapGraph: GraphMapGraphConstructor;
    GraphMapGraphState: GraphMapGraphStateConstructor;
    LispCode: LispCodeConstructor;
    LispCodeCall: LispCodeCallConstructor;
    LispCodeList: LispCodeListConstructor;
    LispCodeKeyValue: LispCodeKeyValueConstructor;
    LispCodeNumber: LispCodeNumberConstructor;
    LispCodeText: LispCodeTextConstructor;
    LispCodeIdent: LispCodeIdentConstructor;
    LispCodeBoolean: LispCodeBooleanConstructor;
    LispCodeReal: LispCodeRealConstructor;
    format_OrgSemLispCodeKind(value: OrgSemLispCodeKind): string;
    Tblfm: TblfmConstructor;
    TblfmExpr: TblfmExprConstructor;
    TblfmExprAxisRef: TblfmExprAxisRefConstructor;
    TblfmExprAxisRefPosition: TblfmExprAxisRefPositionConstructor;
    TblfmExprAxisRefPositionIndex: TblfmExprAxisRefPositionIndexConstructor;
    TblfmExprAxisRefPositionName: TblfmExprAxisRefPositionNameConstructor;
    format_OrgSemTblfmExprAxisRefPositionKind(value: OrgSemTblfmExprAxisRefPositionKind): string;
    TblfmExprAxisName: TblfmExprAxisNameConstructor;
    TblfmExprIntLiteral: TblfmExprIntLiteralConstructor;
    TblfmExprFloatLiteral: TblfmExprFloatLiteralConstructor;
    TblfmExprRangeRef: TblfmExprRangeRefConstructor;
    TblfmExprCall: TblfmExprCallConstructor;
    TblfmExprElisp: TblfmExprElispConstructor;
    format_OrgSemTblfmExprKind(value: OrgSemTblfmExprKind): string;
    TblfmAssign: TblfmAssignConstructor;
    format_OrgSemTblfmAssignFlag(value: OrgSemTblfmAssignFlag): string;
    AttrValue: AttrValueConstructor;
    format_OrgSemAttrValueKind(value: OrgSemAttrValueKind): string;
    AttrValueDimensionSpan: AttrValueDimensionSpanConstructor;
    AttrValueTextValue: AttrValueTextValueConstructor;
    AttrValueFileReference: AttrValueFileReferenceConstructor;
    AttrValueLispValue: AttrValueLispValueConstructor;
    format_OrgSemAttrValueDataKind(value: OrgSemAttrValueDataKind): string;
    HashTagFlat: HashTagFlatConstructor;
    TodoKeyword: TodoKeywordConstructor;
    format_OrgSemTodoKeywordTransition(value: OrgSemTodoKeywordTransition): string;
    HashTagText: HashTagTextConstructor;
    SubtreePath: SubtreePathConstructor;
    LinkTarget: LinkTargetConstructor;
    LinkTargetRaw: LinkTargetRawConstructor;
    LinkTargetId: LinkTargetIdConstructor;
    LinkTargetCustomId: LinkTargetCustomIdConstructor;
    LinkTargetSubtreeTitle: LinkTargetSubtreeTitleConstructor;
    LinkTargetPerson: LinkTargetPersonConstructor;
    LinkTargetUserProtocol: LinkTargetUserProtocolConstructor;
    LinkTargetInternal: LinkTargetInternalConstructor;
    LinkTargetFootnote: LinkTargetFootnoteConstructor;
    LinkTargetFile: LinkTargetFileConstructor;
    LinkTargetAttachment: LinkTargetAttachmentConstructor;
    format_OrgSemLinkTargetKind(value: OrgSemLinkTargetKind): string;
    SubtreeLogHead: SubtreeLogHeadConstructor;
    SubtreeLogHeadPriority: SubtreeLogHeadPriorityConstructor;
    format_OrgSemSubtreeLogHeadPriorityAction(value: OrgSemSubtreeLogHeadPriorityAction): string;
    SubtreeLogHeadNote: SubtreeLogHeadNoteConstructor;
    SubtreeLogHeadRefile: SubtreeLogHeadRefileConstructor;
    SubtreeLogHeadClock: SubtreeLogHeadClockConstructor;
    SubtreeLogHeadState: SubtreeLogHeadStateConstructor;
    SubtreeLogHeadDeadline: SubtreeLogHeadDeadlineConstructor;
    SubtreeLogHeadSchedule: SubtreeLogHeadScheduleConstructor;
    SubtreeLogHeadTag: SubtreeLogHeadTagConstructor;
    SubtreeLogHeadUnknown: SubtreeLogHeadUnknownConstructor;
    format_OrgSemSubtreeLogHeadKind(value: OrgSemSubtreeLogHeadKind): string;
    SubtreeCompletion: SubtreeCompletionConstructor;
    AttrList: AttrListConstructor;
    AttrGroup: AttrGroupConstructor;
    OrgCodeEvalInput: OrgCodeEvalInputConstructor;
    OrgCodeEvalInputVar: OrgCodeEvalInputVarConstructor;
    format_OrgSemOrgCodeEvalInputResultType(value: OrgSemOrgCodeEvalInputResultType): string;
    format_OrgSemOrgCodeEvalInputResultFormat(value: OrgSemOrgCodeEvalInputResultFormat): string;
    format_OrgSemOrgCodeEvalInputResultHandling(value: OrgSemOrgCodeEvalInputResultHandling): string;
    OrgCodeEvalOutput: OrgCodeEvalOutputConstructor;
    ColumnView: ColumnViewConstructor;
    ColumnViewSummary: ColumnViewSummaryConstructor;
    ColumnViewSummaryCheckboxAggregate: ColumnViewSummaryCheckboxAggregateConstructor;
    format_OrgSemColumnViewSummaryCheckboxAggregateKind(value: OrgSemColumnViewSummaryCheckboxAggregateKind): string;
    ColumnViewSummaryMathAggregate: ColumnViewSummaryMathAggregateConstructor;
    format_OrgSemColumnViewSummaryMathAggregateKind(value: OrgSemColumnViewSummaryMathAggregateKind): string;
    format_OrgSemColumnViewSummaryKind(value: OrgSemColumnViewSummaryKind): string;
    ColumnViewColumn: ColumnViewColumnConstructor;
    BlockCodeLine: BlockCodeLineConstructor;
    BlockCodeLinePart: BlockCodeLinePartConstructor;
    BlockCodeLinePartRaw: BlockCodeLinePartRawConstructor;
    BlockCodeLinePartCallout: BlockCodeLinePartCalloutConstructor;
    BlockCodeLinePartTangle: BlockCodeLinePartTangleConstructor;
    format_OrgSemBlockCodeLinePartKind(value: OrgSemBlockCodeLinePartKind): string;
    DocumentExportConfig: DocumentExportConfigConstructor;
    DocumentExportConfigTaskExport: DocumentExportConfigTaskExportConstructor;
    format_OrgSemDocumentExportConfigTagExport(value: OrgSemDocumentExportConfigTagExport): string;
    format_OrgSemDocumentExportConfigTaskFiltering(value: OrgSemDocumentExportConfigTaskFiltering): string;
    format_OrgSemDocumentExportConfigBrokenLinks(value: OrgSemDocumentExportConfigBrokenLinks): string;
    DocumentExportConfigDoExport: DocumentExportConfigDoExportConstructor;
    DocumentExportConfigExportFixed: DocumentExportConfigExportFixedConstructor;
    format_OrgSemDocumentExportConfigTocExportKind(value: OrgSemDocumentExportConfigTocExportKind): string;
    SubtreePeriod: SubtreePeriodConstructor;
    format_OrgSemSubtreePeriodKind(value: OrgSemSubtreePeriodKind): string;
    NamedProperty: NamedPropertyConstructor;
    NamedPropertyNonblocking: NamedPropertyNonblockingConstructor;
    NamedPropertyArchiveTime: NamedPropertyArchiveTimeConstructor;
    NamedPropertyArchiveFile: NamedPropertyArchiveFileConstructor;
    NamedPropertyArchiveOlpath: NamedPropertyArchiveOlpathConstructor;
    NamedPropertyArchiveTarget: NamedPropertyArchiveTargetConstructor;
    NamedPropertyArchiveCategory: NamedPropertyArchiveCategoryConstructor;
    NamedPropertyArchiveTodo: NamedPropertyArchiveTodoConstructor;
    NamedPropertyTrigger: NamedPropertyTriggerConstructor;
    NamedPropertyExportLatexClass: NamedPropertyExportLatexClassConstructor;
    NamedPropertyCookieData: NamedPropertyCookieDataConstructor;
    NamedPropertyExportLatexClassOptions: NamedPropertyExportLatexClassOptionsConstructor;
    NamedPropertyExportLatexHeader: NamedPropertyExportLatexHeaderConstructor;
    NamedPropertyExportLatexCompiler: NamedPropertyExportLatexCompilerConstructor;
    NamedPropertyOrdered: NamedPropertyOrderedConstructor;
    NamedPropertyEffort: NamedPropertyEffortConstructor;
    NamedPropertyVisibility: NamedPropertyVisibilityConstructor;
    format_OrgSemNamedPropertyVisibilityLevel(value: OrgSemNamedPropertyVisibilityLevel): string;
    NamedPropertyExportOptions: NamedPropertyExportOptionsConstructor;
    NamedPropertyBlocker: NamedPropertyBlockerConstructor;
    NamedPropertyUnnumbered: NamedPropertyUnnumberedConstructor;
    NamedPropertyCreated: NamedPropertyCreatedConstructor;
    NamedPropertyRadioId: NamedPropertyRadioIdConstructor;
    NamedPropertyHashtagDef: NamedPropertyHashtagDefConstructor;
    NamedPropertyCustomArgs: NamedPropertyCustomArgsConstructor;
    NamedPropertyCustomRaw: NamedPropertyCustomRawConstructor;
    NamedPropertyCustomSubtreeJson: NamedPropertyCustomSubtreeJsonConstructor;
    NamedPropertyCustomSubtreeFlags: NamedPropertyCustomSubtreeFlagsConstructor;
    format_OrgSemNamedPropertyKind(value: OrgSemNamedPropertyKind): string;
    ImmNone: ImmNoneConstructor;
    ImmErrorItem: ImmErrorItemConstructor;
    ImmErrorGroup: ImmErrorGroupConstructor;
    ImmStmt: ImmStmtConstructor;
    ImmInline: ImmInlineConstructor;
    ImmStmtList: ImmStmtListConstructor;
    ImmEmpty: ImmEmptyConstructor;
    ImmLeaf: ImmLeafConstructor;
    ImmTime: ImmTimeConstructor;
    ImmTimeRepeat: ImmTimeRepeatConstructor;
    format_OrgImmImmTimeRepeatMode(value: OrgImmImmTimeRepeatMode): string;
    format_OrgImmImmTimeRepeatPeriod(value: OrgImmImmTimeRepeatPeriod): string;
    ImmTimeStatic: ImmTimeStaticConstructor;
    ImmTimeDynamic: ImmTimeDynamicConstructor;
    format_OrgImmImmTimeTimeKind(value: OrgImmImmTimeTimeKind): string;
    ImmTimeRange: ImmTimeRangeConstructor;
    ImmMacro: ImmMacroConstructor;
    ImmSymbol: ImmSymbolConstructor;
    ImmSymbolParam: ImmSymbolParamConstructor;
    ImmMarkup: ImmMarkupConstructor;
    ImmRadioTarget: ImmRadioTargetConstructor;
    ImmLatex: ImmLatexConstructor;
    ImmSubtreeLog: ImmSubtreeLogConstructor;
    ImmSubtree: ImmSubtreeConstructor;
    ImmColonExample: ImmColonExampleConstructor;
    ImmCall: ImmCallConstructor;
    ImmListItem: ImmListItemConstructor;
    ImmDocumentOptions: ImmDocumentOptionsConstructor;
    ImmDocumentFragment: ImmDocumentFragmentConstructor;
    ImmCriticMarkup: ImmCriticMarkupConstructor;
    format_OrgImmImmCriticMarkupKind(value: OrgImmImmCriticMarkupKind): string;
    ImmDocument: ImmDocumentConstructor;
    ImmFileTarget: ImmFileTargetConstructor;
    ImmTextSeparator: ImmTextSeparatorConstructor;
    ImmDocumentGroup: ImmDocumentGroupConstructor;
    ImmFile: ImmFileConstructor;
    ImmFileDocument: ImmFileDocumentConstructor;
    ImmFileAttachment: ImmFileAttachmentConstructor;
    ImmFileSource: ImmFileSourceConstructor;
    format_OrgImmImmFileKind(value: OrgImmImmFileKind): string;
    ImmDirectory: ImmDirectoryConstructor;
    ImmSymlink: ImmSymlinkConstructor;
    ImmCmdInclude: ImmCmdIncludeConstructor;
    ImmCmdIncludeIncludeBase: ImmCmdIncludeIncludeBaseConstructor;
    ImmCmdIncludeExample: ImmCmdIncludeExampleConstructor;
    ImmCmdIncludeExport: ImmCmdIncludeExportConstructor;
    ImmCmdIncludeCustom: ImmCmdIncludeCustomConstructor;
    ImmCmdIncludeSrc: ImmCmdIncludeSrcConstructor;
    ImmCmdIncludeOrgDocument: ImmCmdIncludeOrgDocumentConstructor;
    format_OrgImmImmCmdIncludeKind(value: OrgImmImmCmdIncludeKind): string;
    GraphMapConfig: GraphMapConfigConstructor;
    None: NoneConstructor;
    ErrorItem: ErrorItemConstructor;
    ErrorGroup: ErrorGroupConstructor;
    Stmt: StmtConstructor;
    Inline: InlineConstructor;
    StmtList: StmtListConstructor;
    Empty: EmptyConstructor;
    Leaf: LeafConstructor;
    Time: TimeConstructor;
    TimeRepeat: TimeRepeatConstructor;
    format_OrgSemTimeRepeatMode(value: OrgSemTimeRepeatMode): string;
    format_OrgSemTimeRepeatPeriod(value: OrgSemTimeRepeatPeriod): string;
    TimeStatic: TimeStaticConstructor;
    TimeDynamic: TimeDynamicConstructor;
    format_OrgSemTimeTimeKind(value: OrgSemTimeTimeKind): string;
    TimeRange: TimeRangeConstructor;
    Macro: MacroConstructor;
    Symbol: SymbolConstructor;
    SymbolParam: SymbolParamConstructor;
    Markup: MarkupConstructor;
    RadioTarget: RadioTargetConstructor;
    Latex: LatexConstructor;
    SubtreeLog: SubtreeLogConstructor;
    Subtree: SubtreeConstructor;
    ColonExample: ColonExampleConstructor;
    Call: CallConstructor;
    ListItem: ListItemConstructor;
    DocumentOptions: DocumentOptionsConstructor;
    DocumentFragment: DocumentFragmentConstructor;
    CriticMarkup: CriticMarkupConstructor;
    format_OrgSemCriticMarkupKind(value: OrgSemCriticMarkupKind): string;
    Document: DocumentConstructor;
    FileTarget: FileTargetConstructor;
    TextSeparator: TextSeparatorConstructor;
    DocumentGroup: DocumentGroupConstructor;
    File: FileConstructor;
    FileDocument: FileDocumentConstructor;
    FileAttachment: FileAttachmentConstructor;
    FileSource: FileSourceConstructor;
    format_OrgSemFileKind(value: OrgSemFileKind): string;
    Directory: DirectoryConstructor;
    Symlink: SymlinkConstructor;
    CmdInclude: CmdIncludeConstructor;
    CmdIncludeIncludeBase: CmdIncludeIncludeBaseConstructor;
    CmdIncludeExample: CmdIncludeExampleConstructor;
    CmdIncludeExport: CmdIncludeExportConstructor;
    CmdIncludeCustom: CmdIncludeCustomConstructor;
    CmdIncludeSrc: CmdIncludeSrcConstructor;
    CmdIncludeOrgDocument: CmdIncludeOrgDocumentConstructor;
    format_OrgSemCmdIncludeKind(value: OrgSemCmdIncludeKind): string;
    ImmIdTNone: ImmIdTNoneConstructor;
    ImmIdTErrorItem: ImmIdTErrorItemConstructor;
    ImmIdTErrorGroup: ImmIdTErrorGroupConstructor;
    ImmIdTStmt: ImmIdTStmtConstructor;
    ImmIdTInline: ImmIdTInlineConstructor;
    ImmIdTStmtList: ImmIdTStmtListConstructor;
    ImmIdTEmpty: ImmIdTEmptyConstructor;
    ImmIdTCmd: ImmIdTCmdConstructor;
    ImmIdTBlock: ImmIdTBlockConstructor;
    ImmIdTLineCommand: ImmIdTLineCommandConstructor;
    ImmIdTAttached: ImmIdTAttachedConstructor;
    ImmIdTLeaf: ImmIdTLeafConstructor;
    ImmIdTCmdCaption: ImmIdTCmdCaptionConstructor;
    ImmIdTCmdColumns: ImmIdTCmdColumnsConstructor;
    ImmIdTCmdName: ImmIdTCmdNameConstructor;
    ImmIdTCmdCustomArgs: ImmIdTCmdCustomArgsConstructor;
    ImmIdTCmdCustomRaw: ImmIdTCmdCustomRawConstructor;
    ImmIdTCmdCustomText: ImmIdTCmdCustomTextConstructor;
    ImmIdTCmdCall: ImmIdTCmdCallConstructor;
    ImmIdTCmdTblfm: ImmIdTCmdTblfmConstructor;
    ImmIdTHashTag: ImmIdTHashTagConstructor;
    ImmIdTInlineFootnote: ImmIdTInlineFootnoteConstructor;
    ImmIdTInlineExport: ImmIdTInlineExportConstructor;
    ImmIdTTime: ImmIdTTimeConstructor;
    ImmIdTTimeRange: ImmIdTTimeRangeConstructor;
    ImmIdTMacro: ImmIdTMacroConstructor;
    ImmIdTSymbol: ImmIdTSymbolConstructor;
    ImmIdTEscaped: ImmIdTEscapedConstructor;
    ImmIdTNewline: ImmIdTNewlineConstructor;
    ImmIdTSpace: ImmIdTSpaceConstructor;
    ImmIdTWord: ImmIdTWordConstructor;
    ImmIdTAtMention: ImmIdTAtMentionConstructor;
    ImmIdTRawText: ImmIdTRawTextConstructor;
    ImmIdTPunctuation: ImmIdTPunctuationConstructor;
    ImmIdTPlaceholder: ImmIdTPlaceholderConstructor;
    ImmIdTBigIdent: ImmIdTBigIdentConstructor;
    ImmIdTTextTarget: ImmIdTTextTargetConstructor;
    ImmIdTMarkup: ImmIdTMarkupConstructor;
    ImmIdTBold: ImmIdTBoldConstructor;
    ImmIdTUnderline: ImmIdTUnderlineConstructor;
    ImmIdTMonospace: ImmIdTMonospaceConstructor;
    ImmIdTMarkQuote: ImmIdTMarkQuoteConstructor;
    ImmIdTVerbatim: ImmIdTVerbatimConstructor;
    ImmIdTItalic: ImmIdTItalicConstructor;
    ImmIdTStrike: ImmIdTStrikeConstructor;
    ImmIdTPar: ImmIdTParConstructor;
    ImmIdTRadioTarget: ImmIdTRadioTargetConstructor;
    ImmIdTLatex: ImmIdTLatexConstructor;
    ImmIdTLink: ImmIdTLinkConstructor;
    ImmIdTBlockCenter: ImmIdTBlockCenterConstructor;
    ImmIdTBlockQuote: ImmIdTBlockQuoteConstructor;
    ImmIdTBlockComment: ImmIdTBlockCommentConstructor;
    ImmIdTBlockVerse: ImmIdTBlockVerseConstructor;
    ImmIdTBlockDynamicFallback: ImmIdTBlockDynamicFallbackConstructor;
    ImmIdTBlockExample: ImmIdTBlockExampleConstructor;
    ImmIdTBlockExport: ImmIdTBlockExportConstructor;
    ImmIdTBlockAdmonition: ImmIdTBlockAdmonitionConstructor;
    ImmIdTBlockCodeEvalResult: ImmIdTBlockCodeEvalResultConstructor;
    ImmIdTBlockCode: ImmIdTBlockCodeConstructor;
    ImmIdTSubtreeLog: ImmIdTSubtreeLogConstructor;
    ImmIdTSubtree: ImmIdTSubtreeConstructor;
    ImmIdTCell: ImmIdTCellConstructor;
    ImmIdTRow: ImmIdTRowConstructor;
    ImmIdTTable: ImmIdTTableConstructor;
    ImmIdTParagraph: ImmIdTParagraphConstructor;
    ImmIdTColonExample: ImmIdTColonExampleConstructor;
    ImmIdTCmdAttr: ImmIdTCmdAttrConstructor;
    ImmIdTCmdExport: ImmIdTCmdExportConstructor;
    ImmIdTCall: ImmIdTCallConstructor;
    ImmIdTList: ImmIdTListConstructor;
    ImmIdTListItem: ImmIdTListItemConstructor;
    ImmIdTDocumentOptions: ImmIdTDocumentOptionsConstructor;
    ImmIdTDocumentFragment: ImmIdTDocumentFragmentConstructor;
    ImmIdTCriticMarkup: ImmIdTCriticMarkupConstructor;
    ImmIdTDocument: ImmIdTDocumentConstructor;
    ImmIdTFileTarget: ImmIdTFileTargetConstructor;
    ImmIdTTextSeparator: ImmIdTTextSeparatorConstructor;
    ImmIdTDocumentGroup: ImmIdTDocumentGroupConstructor;
    ImmIdTFile: ImmIdTFileConstructor;
    ImmIdTDirectory: ImmIdTDirectoryConstructor;
    ImmIdTSymlink: ImmIdTSymlinkConstructor;
    ImmIdTCmdInclude: ImmIdTCmdIncludeConstructor;
    ImmNoneValue: ImmNoneValueConstructor;
    ImmErrorItemValue: ImmErrorItemValueConstructor;
    ImmErrorGroupValue: ImmErrorGroupValueConstructor;
    ImmStmtListValue: ImmStmtListValueConstructor;
    ImmEmptyValue: ImmEmptyValueConstructor;
    ImmCmdCaptionValue: ImmCmdCaptionValueConstructor;
    ImmCmdColumnsValue: ImmCmdColumnsValueConstructor;
    ImmCmdNameValue: ImmCmdNameValueConstructor;
    ImmCmdCustomArgsValue: ImmCmdCustomArgsValueConstructor;
    ImmCmdCustomRawValue: ImmCmdCustomRawValueConstructor;
    ImmCmdCustomTextValue: ImmCmdCustomTextValueConstructor;
    ImmCmdCallValue: ImmCmdCallValueConstructor;
    ImmCmdTblfmValue: ImmCmdTblfmValueConstructor;
    ImmHashTagValue: ImmHashTagValueConstructor;
    ImmInlineFootnoteValue: ImmInlineFootnoteValueConstructor;
    ImmInlineExportValue: ImmInlineExportValueConstructor;
    ImmTimeValue: ImmTimeValueConstructor;
    ImmTimeRangeValue: ImmTimeRangeValueConstructor;
    ImmMacroValue: ImmMacroValueConstructor;
    ImmSymbolValue: ImmSymbolValueConstructor;
    ImmEscapedValue: ImmEscapedValueConstructor;
    ImmNewlineValue: ImmNewlineValueConstructor;
    ImmSpaceValue: ImmSpaceValueConstructor;
    ImmWordValue: ImmWordValueConstructor;
    ImmAtMentionValue: ImmAtMentionValueConstructor;
    ImmRawTextValue: ImmRawTextValueConstructor;
    ImmPunctuationValue: ImmPunctuationValueConstructor;
    ImmPlaceholderValue: ImmPlaceholderValueConstructor;
    ImmBigIdentValue: ImmBigIdentValueConstructor;
    ImmTextTargetValue: ImmTextTargetValueConstructor;
    ImmBoldValue: ImmBoldValueConstructor;
    ImmUnderlineValue: ImmUnderlineValueConstructor;
    ImmMonospaceValue: ImmMonospaceValueConstructor;
    ImmMarkQuoteValue: ImmMarkQuoteValueConstructor;
    ImmVerbatimValue: ImmVerbatimValueConstructor;
    ImmItalicValue: ImmItalicValueConstructor;
    ImmStrikeValue: ImmStrikeValueConstructor;
    ImmParValue: ImmParValueConstructor;
    ImmRadioTargetValue: ImmRadioTargetValueConstructor;
    ImmLatexValue: ImmLatexValueConstructor;
    ImmLinkValue: ImmLinkValueConstructor;
    ImmBlockCenterValue: ImmBlockCenterValueConstructor;
    ImmBlockQuoteValue: ImmBlockQuoteValueConstructor;
    ImmBlockCommentValue: ImmBlockCommentValueConstructor;
    ImmBlockVerseValue: ImmBlockVerseValueConstructor;
    ImmBlockDynamicFallbackValue: ImmBlockDynamicFallbackValueConstructor;
    ImmBlockExampleValue: ImmBlockExampleValueConstructor;
    ImmBlockExportValue: ImmBlockExportValueConstructor;
    ImmBlockAdmonitionValue: ImmBlockAdmonitionValueConstructor;
    ImmBlockCodeEvalResultValue: ImmBlockCodeEvalResultValueConstructor;
    ImmBlockCodeValue: ImmBlockCodeValueConstructor;
    ImmSubtreeLogValue: ImmSubtreeLogValueConstructor;
    ImmSubtreeValue: ImmSubtreeValueConstructor;
    ImmCellValue: ImmCellValueConstructor;
    ImmRowValue: ImmRowValueConstructor;
    ImmTableValue: ImmTableValueConstructor;
    ImmParagraphValue: ImmParagraphValueConstructor;
    ImmColonExampleValue: ImmColonExampleValueConstructor;
    ImmCmdAttrValue: ImmCmdAttrValueConstructor;
    ImmCmdExportValue: ImmCmdExportValueConstructor;
    ImmCallValue: ImmCallValueConstructor;
    ImmListValue: ImmListValueConstructor;
    ImmListItemValue: ImmListItemValueConstructor;
    ImmDocumentOptionsValue: ImmDocumentOptionsValueConstructor;
    ImmDocumentFragmentValue: ImmDocumentFragmentValueConstructor;
    ImmCriticMarkupValue: ImmCriticMarkupValueConstructor;
    ImmDocumentValue: ImmDocumentValueConstructor;
    ImmFileTargetValue: ImmFileTargetValueConstructor;
    ImmTextSeparatorValue: ImmTextSeparatorValueConstructor;
    ImmDocumentGroupValue: ImmDocumentGroupValueConstructor;
    ImmFileValue: ImmFileValueConstructor;
    ImmDirectoryValue: ImmDirectoryValueConstructor;
    ImmSymlinkValue: ImmSymlinkValueConstructor;
    ImmCmdIncludeValue: ImmCmdIncludeValueConstructor;
    ImmAdapterOrgAPI: ImmAdapterOrgAPIConstructor;
    ImmCmd: ImmCmdConstructor;
    ImmCmdCustomRaw: ImmCmdCustomRawConstructor;
    ImmCmdCustomText: ImmCmdCustomTextConstructor;
    ImmLink: ImmLinkConstructor;
    ImmBlockComment: ImmBlockCommentConstructor;
    ImmParagraph: ImmParagraphConstructor;
    ImmList: ImmListConstructor;
    ImmHashTag: ImmHashTagConstructor;
    ImmInlineFootnote: ImmInlineFootnoteConstructor;
    ImmInlineExport: ImmInlineExportConstructor;
    ImmEscaped: ImmEscapedConstructor;
    ImmNewline: ImmNewlineConstructor;
    ImmSpace: ImmSpaceConstructor;
    ImmWord: ImmWordConstructor;
    ImmAtMention: ImmAtMentionConstructor;
    ImmRawText: ImmRawTextConstructor;
    ImmPunctuation: ImmPunctuationConstructor;
    ImmPlaceholder: ImmPlaceholderConstructor;
    ImmBigIdent: ImmBigIdentConstructor;
    ImmTextTarget: ImmTextTargetConstructor;
    ImmBold: ImmBoldConstructor;
    ImmUnderline: ImmUnderlineConstructor;
    ImmMonospace: ImmMonospaceConstructor;
    ImmMarkQuote: ImmMarkQuoteConstructor;
    ImmVerbatim: ImmVerbatimConstructor;
    ImmItalic: ImmItalicConstructor;
    ImmStrike: ImmStrikeConstructor;
    ImmPar: ImmParConstructor;
    Cmd: CmdConstructor;
    CmdCustomRaw: CmdCustomRawConstructor;
    CmdCustomText: CmdCustomTextConstructor;
    Link: LinkConstructor;
    BlockComment: BlockCommentConstructor;
    Paragraph: ParagraphConstructor;
    List: ListConstructor;
    HashTag: HashTagConstructor;
    InlineFootnote: InlineFootnoteConstructor;
    InlineExport: InlineExportConstructor;
    Escaped: EscapedConstructor;
    Newline: NewlineConstructor;
    Space: SpaceConstructor;
    Word: WordConstructor;
    AtMention: AtMentionConstructor;
    RawText: RawTextConstructor;
    Punctuation: PunctuationConstructor;
    Placeholder: PlaceholderConstructor;
    BigIdent: BigIdentConstructor;
    TextTarget: TextTargetConstructor;
    Bold: BoldConstructor;
    Underline: UnderlineConstructor;
    Monospace: MonospaceConstructor;
    MarkQuote: MarkQuoteConstructor;
    Verbatim: VerbatimConstructor;
    Italic: ItalicConstructor;
    Strike: StrikeConstructor;
    Par: ParConstructor;
    ImmAdapterStmtAPI: ImmAdapterStmtAPIConstructor;
    ImmAdapterSubtreeAPI: ImmAdapterSubtreeAPIConstructor;
    ImmAdapterNoneAPI: ImmAdapterNoneAPIConstructor;
    ImmAdapterAttrAPI: ImmAdapterAttrAPIConstructor;
    ImmAdapterAttrListAPI: ImmAdapterAttrListAPIConstructor;
    ImmAdapterAttrsAPI: ImmAdapterAttrsAPIConstructor;
    ImmAdapterErrorItemAPI: ImmAdapterErrorItemAPIConstructor;
    ImmAdapterErrorGroupAPI: ImmAdapterErrorGroupAPIConstructor;
    ImmAdapterStmtListAPI: ImmAdapterStmtListAPIConstructor;
    ImmAdapterEmptyAPI: ImmAdapterEmptyAPIConstructor;
    ImmAdapterInlineAPI: ImmAdapterInlineAPIConstructor;
    ImmAdapterTimeAPI: ImmAdapterTimeAPIConstructor;
    ImmAdapterTimeRangeAPI: ImmAdapterTimeRangeAPIConstructor;
    ImmAdapterMacroAPI: ImmAdapterMacroAPIConstructor;
    ImmAdapterSymbolAPI: ImmAdapterSymbolAPIConstructor;
    ImmAdapterLeafAPI: ImmAdapterLeafAPIConstructor;
    ImmAdapterMarkupAPI: ImmAdapterMarkupAPIConstructor;
    ImmAdapterLatexAPI: ImmAdapterLatexAPIConstructor;
    ImmAdapterSubtreeLogAPI: ImmAdapterSubtreeLogAPIConstructor;
    ImmAdapterColonExampleAPI: ImmAdapterColonExampleAPIConstructor;
    ImmAdapterCallAPI: ImmAdapterCallAPIConstructor;
    ImmAdapterFileAPI: ImmAdapterFileAPIConstructor;
    ImmAdapterDirectoryAPI: ImmAdapterDirectoryAPIConstructor;
    ImmAdapterSymlinkAPI: ImmAdapterSymlinkAPIConstructor;
    ImmAdapterDocumentFragmentAPI: ImmAdapterDocumentFragmentAPIConstructor;
    ImmAdapterCriticMarkupAPI: ImmAdapterCriticMarkupAPIConstructor;
    ImmAdapterListItemAPI: ImmAdapterListItemAPIConstructor;
    ImmAdapterDocumentOptionsAPI: ImmAdapterDocumentOptionsAPIConstructor;
    ImmAdapterDocumentAPI: ImmAdapterDocumentAPIConstructor;
    ImmAdapterFileTargetAPI: ImmAdapterFileTargetAPIConstructor;
    ImmAdapterTextSeparatorAPI: ImmAdapterTextSeparatorAPIConstructor;
    ImmAdapterCmdIncludeAPI: ImmAdapterCmdIncludeAPIConstructor;
    ImmAdapterDocumentGroupAPI: ImmAdapterDocumentGroupAPIConstructor;
    ImmBlock: ImmBlockConstructor;
    ImmLineCommand: ImmLineCommandConstructor;
    ImmCmdCustomArgs: ImmCmdCustomArgsConstructor;
    ImmCmdTblfm: ImmCmdTblfmConstructor;
    ImmCell: ImmCellConstructor;
    ImmRow: ImmRowConstructor;
    Block: BlockConstructor;
    LineCommand: LineCommandConstructor;
    CmdCustomArgs: CmdCustomArgsConstructor;
    CmdTblfm: CmdTblfmConstructor;
    Cell: CellConstructor;
    Row: RowConstructor;
    ImmAdapterCmdAPI: ImmAdapterCmdAPIConstructor;
    ImmAdapterCmdCustomRawAPI: ImmAdapterCmdCustomRawAPIConstructor;
    ImmAdapterCmdCustomTextAPI: ImmAdapterCmdCustomTextAPIConstructor;
    ImmAdapterLinkAPI: ImmAdapterLinkAPIConstructor;
    ImmAdapterBlockCommentAPI: ImmAdapterBlockCommentAPIConstructor;
    ImmAdapterParagraphAPI: ImmAdapterParagraphAPIConstructor;
    ImmAdapterListAPI: ImmAdapterListAPIConstructor;
    ImmSubtreeAdapter: ImmSubtreeAdapterConstructor;
    ImmNoneAdapter: ImmNoneAdapterConstructor;
    ImmErrorItemAdapter: ImmErrorItemAdapterConstructor;
    ImmErrorGroupAdapter: ImmErrorGroupAdapterConstructor;
    ImmStmtListAdapter: ImmStmtListAdapterConstructor;
    ImmEmptyAdapter: ImmEmptyAdapterConstructor;
    ImmAdapterHashTagAPI: ImmAdapterHashTagAPIConstructor;
    ImmAdapterInlineFootnoteAPI: ImmAdapterInlineFootnoteAPIConstructor;
    ImmAdapterSubtreeCompletionAPI: ImmAdapterSubtreeCompletionAPIConstructor;
    ImmTimeAdapter: ImmTimeAdapterConstructor;
    ImmTimeRangeAdapter: ImmTimeRangeAdapterConstructor;
    ImmMacroAdapter: ImmMacroAdapterConstructor;
    ImmSymbolAdapter: ImmSymbolAdapterConstructor;
    ImmAdapterEscapedAPI: ImmAdapterEscapedAPIConstructor;
    ImmAdapterNewlineAPI: ImmAdapterNewlineAPIConstructor;
    ImmAdapterSpaceAPI: ImmAdapterSpaceAPIConstructor;
    ImmAdapterWordAPI: ImmAdapterWordAPIConstructor;
    ImmAdapterAtMentionAPI: ImmAdapterAtMentionAPIConstructor;
    ImmAdapterRawTextAPI: ImmAdapterRawTextAPIConstructor;
    ImmAdapterPunctuationAPI: ImmAdapterPunctuationAPIConstructor;
    ImmAdapterPlaceholderAPI: ImmAdapterPlaceholderAPIConstructor;
    ImmAdapterBigIdentAPI: ImmAdapterBigIdentAPIConstructor;
    ImmAdapterTextTargetAPI: ImmAdapterTextTargetAPIConstructor;
    ImmAdapterBoldAPI: ImmAdapterBoldAPIConstructor;
    ImmAdapterUnderlineAPI: ImmAdapterUnderlineAPIConstructor;
    ImmAdapterMonospaceAPI: ImmAdapterMonospaceAPIConstructor;
    ImmAdapterMarkQuoteAPI: ImmAdapterMarkQuoteAPIConstructor;
    ImmAdapterRadioTargetAPI: ImmAdapterRadioTargetAPIConstructor;
    ImmAdapterVerbatimAPI: ImmAdapterVerbatimAPIConstructor;
    ImmAdapterItalicAPI: ImmAdapterItalicAPIConstructor;
    ImmAdapterStrikeAPI: ImmAdapterStrikeAPIConstructor;
    ImmAdapterParAPI: ImmAdapterParAPIConstructor;
    ImmLatexAdapter: ImmLatexAdapterConstructor;
    ImmSubtreeLogAdapter: ImmSubtreeLogAdapterConstructor;
    ImmColonExampleAdapter: ImmColonExampleAdapterConstructor;
    ImmCallAdapter: ImmCallAdapterConstructor;
    ImmFileAdapter: ImmFileAdapterConstructor;
    ImmDirectoryAdapter: ImmDirectoryAdapterConstructor;
    ImmSymlinkAdapter: ImmSymlinkAdapterConstructor;
    ImmDocumentFragmentAdapter: ImmDocumentFragmentAdapterConstructor;
    ImmCriticMarkupAdapter: ImmCriticMarkupAdapterConstructor;
    ImmListItemAdapter: ImmListItemAdapterConstructor;
    ImmDocumentOptionsAdapter: ImmDocumentOptionsAdapterConstructor;
    ImmDocumentAdapter: ImmDocumentAdapterConstructor;
    ImmFileTargetAdapter: ImmFileTargetAdapterConstructor;
    ImmTextSeparatorAdapter: ImmTextSeparatorAdapterConstructor;
    ImmCmdIncludeAdapter: ImmCmdIncludeAdapterConstructor;
    ImmDocumentGroupAdapter: ImmDocumentGroupAdapterConstructor;
    ImmBlockCenter: ImmBlockCenterConstructor;
    ImmBlockQuote: ImmBlockQuoteConstructor;
    ImmBlockVerse: ImmBlockVerseConstructor;
    ImmBlockDynamicFallback: ImmBlockDynamicFallbackConstructor;
    ImmBlockExample: ImmBlockExampleConstructor;
    ImmBlockExport: ImmBlockExportConstructor;
    ImmBlockAdmonition: ImmBlockAdmonitionConstructor;
    ImmBlockCodeEvalResult: ImmBlockCodeEvalResultConstructor;
    ImmBlockCode: ImmBlockCodeConstructor;
    ImmTable: ImmTableConstructor;
    ImmAttached: ImmAttachedConstructor;
    BlockCenter: BlockCenterConstructor;
    BlockQuote: BlockQuoteConstructor;
    BlockVerse: BlockVerseConstructor;
    BlockDynamicFallback: BlockDynamicFallbackConstructor;
    BlockExample: BlockExampleConstructor;
    BlockExport: BlockExportConstructor;
    BlockAdmonition: BlockAdmonitionConstructor;
    BlockCodeEvalResult: BlockCodeEvalResultConstructor;
    BlockCode: BlockCodeConstructor;
    Table: TableConstructor;
    Attached: AttachedConstructor;
    ImmAdapterLineCommandAPI: ImmAdapterLineCommandAPIConstructor;
    ImmAdapterCmdCustomArgsAPI: ImmAdapterCmdCustomArgsAPIConstructor;
    ImmAdapterCmdTblfmAPI: ImmAdapterCmdTblfmAPIConstructor;
    ImmAdapterBlockAPI: ImmAdapterBlockAPIConstructor;
    ImmAdapterCellAPI: ImmAdapterCellAPIConstructor;
    ImmAdapterRowAPI: ImmAdapterRowAPIConstructor;
    ImmCmdCustomRawAdapter: ImmCmdCustomRawAdapterConstructor;
    ImmCmdCustomTextAdapter: ImmCmdCustomTextAdapterConstructor;
    ImmLinkAdapter: ImmLinkAdapterConstructor;
    ImmBlockCommentAdapter: ImmBlockCommentAdapterConstructor;
    ImmParagraphAdapter: ImmParagraphAdapterConstructor;
    ImmListAdapter: ImmListAdapterConstructor;
    ImmHashTagAdapter: ImmHashTagAdapterConstructor;
    ImmInlineFootnoteAdapter: ImmInlineFootnoteAdapterConstructor;
    ImmEscapedAdapter: ImmEscapedAdapterConstructor;
    ImmNewlineAdapter: ImmNewlineAdapterConstructor;
    ImmSpaceAdapter: ImmSpaceAdapterConstructor;
    ImmWordAdapter: ImmWordAdapterConstructor;
    ImmAtMentionAdapter: ImmAtMentionAdapterConstructor;
    ImmRawTextAdapter: ImmRawTextAdapterConstructor;
    ImmPunctuationAdapter: ImmPunctuationAdapterConstructor;
    ImmPlaceholderAdapter: ImmPlaceholderAdapterConstructor;
    ImmBigIdentAdapter: ImmBigIdentAdapterConstructor;
    ImmTextTargetAdapter: ImmTextTargetAdapterConstructor;
    ImmBoldAdapter: ImmBoldAdapterConstructor;
    ImmUnderlineAdapter: ImmUnderlineAdapterConstructor;
    ImmMonospaceAdapter: ImmMonospaceAdapterConstructor;
    ImmMarkQuoteAdapter: ImmMarkQuoteAdapterConstructor;
    ImmRadioTargetAdapter: ImmRadioTargetAdapterConstructor;
    ImmVerbatimAdapter: ImmVerbatimAdapterConstructor;
    ImmItalicAdapter: ImmItalicAdapterConstructor;
    ImmStrikeAdapter: ImmStrikeAdapterConstructor;
    ImmParAdapter: ImmParAdapterConstructor;
    ImmCmdCaption: ImmCmdCaptionConstructor;
    ImmCmdColumns: ImmCmdColumnsConstructor;
    ImmCmdName: ImmCmdNameConstructor;
    ImmCmdCall: ImmCmdCallConstructor;
    ImmCmdAttr: ImmCmdAttrConstructor;
    ImmCmdExport: ImmCmdExportConstructor;
    CmdCaption: CmdCaptionConstructor;
    CmdColumns: CmdColumnsConstructor;
    CmdName: CmdNameConstructor;
    CmdCall: CmdCallConstructor;
    CmdAttr: CmdAttrConstructor;
    CmdExport: CmdExportConstructor;
    ImmAdapterAttachedAPI: ImmAdapterAttachedAPIConstructor;
    ImmCmdCustomArgsAdapter: ImmCmdCustomArgsAdapterConstructor;
    ImmCmdTblfmAdapter: ImmCmdTblfmAdapterConstructor;
    ImmAdapterBlockCenterAPI: ImmAdapterBlockCenterAPIConstructor;
    ImmAdapterBlockQuoteAPI: ImmAdapterBlockQuoteAPIConstructor;
    ImmAdapterBlockVerseAPI: ImmAdapterBlockVerseAPIConstructor;
    ImmAdapterBlockExampleAPI: ImmAdapterBlockExampleAPIConstructor;
    ImmAdapterInlineExportAPI: ImmAdapterInlineExportAPIConstructor;
    ImmAdapterCmdExportAPI: ImmAdapterCmdExportAPIConstructor;
    ImmAdapterBlockExportAPI: ImmAdapterBlockExportAPIConstructor;
    ImmAdapterBlockDynamicFallbackAPI: ImmAdapterBlockDynamicFallbackAPIConstructor;
    ImmAdapterBlockAdmonitionAPI: ImmAdapterBlockAdmonitionAPIConstructor;
    ImmAdapterBlockCodeEvalResultAPI: ImmAdapterBlockCodeEvalResultAPIConstructor;
    ImmAdapterBlockCodeAPI: ImmAdapterBlockCodeAPIConstructor;
    ImmAdapterTableAPI: ImmAdapterTableAPIConstructor;
    ImmCellAdapter: ImmCellAdapterConstructor;
    ImmRowAdapter: ImmRowAdapterConstructor;
    ImmAdapterCmdCaptionAPI: ImmAdapterCmdCaptionAPIConstructor;
    ImmAdapterCmdColumnsAPI: ImmAdapterCmdColumnsAPIConstructor;
    ImmAdapterCmdNameAPI: ImmAdapterCmdNameAPIConstructor;
    ImmAdapterCmdCallAPI: ImmAdapterCmdCallAPIConstructor;
    ImmAdapterCmdResultsAPI: ImmAdapterCmdResultsAPIConstructor;
    ImmAdapterCmdAttrAPI: ImmAdapterCmdAttrAPIConstructor;
    ImmBlockCenterAdapter: ImmBlockCenterAdapterConstructor;
    ImmBlockQuoteAdapter: ImmBlockQuoteAdapterConstructor;
    ImmBlockVerseAdapter: ImmBlockVerseAdapterConstructor;
    ImmBlockExampleAdapter: ImmBlockExampleAdapterConstructor;
    ImmInlineExportAdapter: ImmInlineExportAdapterConstructor;
    ImmCmdExportAdapter: ImmCmdExportAdapterConstructor;
    ImmBlockExportAdapter: ImmBlockExportAdapterConstructor;
    ImmBlockDynamicFallbackAdapter: ImmBlockDynamicFallbackAdapterConstructor;
    ImmBlockAdmonitionAdapter: ImmBlockAdmonitionAdapterConstructor;
    ImmBlockCodeEvalResultAdapter: ImmBlockCodeEvalResultAdapterConstructor;
    ImmBlockCodeAdapter: ImmBlockCodeAdapterConstructor;
    ImmTableAdapter: ImmTableAdapterConstructor;
    ImmCmdCaptionAdapter: ImmCmdCaptionAdapterConstructor;
    ImmCmdColumnsAdapter: ImmCmdColumnsAdapterConstructor;
    ImmCmdNameAdapter: ImmCmdNameAdapterConstructor;
    ImmCmdCallAdapter: ImmCmdCallAdapterConstructor;
    ImmCmdAttrAdapter: ImmCmdAttrAdapterConstructor;
    format_CheckboxState(value: CheckboxState): string;
    format_SubtreeTodoSource(value: SubtreeTodoSource): string;
    format_ListFormattingMode(value: ListFormattingMode): string;
    format_InitialSubtreeVisibility(value: InitialSubtreeVisibility): string;
    format_BlockCodeResults(value: BlockCodeResults): string;
    format_BlockCodeExports(value: BlockCodeExports): string;
    format_OrgSpecName(value: OrgSpecName): string;
    format_OrgNodeKind(value: OrgNodeKind): string;
    format_OrgTokenKind(value: OrgTokenKind): string;
    format_OrgJsonKind(value: OrgJsonKind): string;
    format_OrgSemKind(value: OrgSemKind): string;
    format_OrgAstTrackingGroupKind(value: OrgAstTrackingGroupKind): string;
    newSemTimeStatic(breakdown: UserTimeBreakdown, isActive: boolean): Time;
    parseFile(file: string, opts: OrgParseParameters): Org;
    parseString(text: string): Org;
    parseStringOpts(text: string, opts: OrgParseParameters): Org;
    parseDirectoryOpts(path: string, opts: OrgDirectoryParseParameters): haxorg_wasm.Optional<Org>;
    parseFileWithIncludes(file: string, opts: OrgDirectoryParseParameters): File;
    initImmutableAstContext(): StdShared_ptr<ImmAstContext>;
    asOneNode(arg: Org): Org;
    formatToString(arg: Org): string;
    exportToYamlString(node: Org, opts: OrgYamlExportOpts): string;
    exportToYamlFile(node: Org, path: string, opts: OrgYamlExportOpts): void;
    exportToJsonString(node: Org): string;
    exportToJsonFile(node: Org, path: string): void;
    readProtobufFile(file: string): Document;
    exportToProtobufFile(doc: Document, file: string): void;
    exportToTreeString(node: Org, opts: OrgTreeExportOpts): string;
    exportToTreeFile(node: Org, path: string, opts: OrgTreeExportOpts): void;
    getAstTrackingMap(nodes: Vec<Org>): AstTrackingMap;
    getSubnodeGroups(node: Org, map: AstTrackingMap): Vec<AstTrackingGroup>;
    annotateSequence(groups: Vec<SequenceSegmentGroup>, first: number, last: number): Vec<SequenceAnnotation>;
  }
  export interface UserTimeBreakdownConstructor { new(): UserTimeBreakdown; }
  export interface UserTimeBreakdown {
    year: haxorg_wasm.Optional<number>
    month: haxorg_wasm.Optional<number>
    day: haxorg_wasm.Optional<number>
    hour: haxorg_wasm.Optional<number>
    minute: haxorg_wasm.Optional<number>
    second: haxorg_wasm.Optional<number>
    zone: haxorg_wasm.Optional<string>
  }
  export interface UserTimeConstructor { new(): UserTime; }
  export interface UserTime {
    getBreakdown(): UserTimeBreakdown;
    format(): string;
  }
  export interface ParseLineColConstructor { new(): ParseLineCol; }
  export interface ParseLineCol {
    line: number
    column: number
    pos: number
  }
  export interface OperationsTracerConstructor { new(): OperationsTracer; }
  export interface OperationsTracer {
    setTraceFileStr(outfile: string, overwrite: boolean): void;
    sendMessage(value: string, function: string, line: number, file: string): void;
    TraceState: boolean
    traceToFile: boolean
    traceToBuffer: boolean
    traceStructured: boolean
    traceColored: boolean
    activeLevel: number
    traceBuffer: string
  }
  export interface OrgJsonConstructor { new(): OrgJson; }
  export interface OrgJson {
    getKind(): OrgJsonKind;
    getJsonString(): string;
    atIndex(idx: number): OrgJson;
    atField(name: string): OrgJson;
    getString(): string;
    getField(name: string): OrgJson;
    getItem(index: number): OrgJson;
    getInt(): number;
    getBool(): boolean;
    getArray(): Vec<OrgJson>;
  }
  export interface OrgConstructor { new(): Org; }
  export interface Org {
    getKind(): OrgSemKind;
    isGenerated(): boolean;
    push_back(sub: Org): void;
    size(): number;
    insert(pos: number, node: Org): void;
    at(idx: number): Org;
    is(kind: OrgSemKind): boolean;
    loc: haxorg_wasm.Optional<ParseLineCol>
    subnodes: Vec<Org>
  }
  export interface ImmIdConstructor { new(): ImmId; }
  export interface ImmId {
    getKind(): OrgSemKind;
    is(kind: OrgSemKind): boolean;
    getNodeIndex(): ImmIdNodeIdxT;
    getReadableId(): string;
  }
  export interface ImmPathStepConstructor { new(): ImmPathStep; }
  export interface ImmPathStep {  }
  export interface ImmPathConstructor { new(): ImmPath; }
  export interface ImmPath {
    empty(): boolean;
    root: ImmId
    path: ImmPathStore
  }
  export interface ImmUniqIdConstructor { new(): ImmUniqId; }
  export interface ImmUniqId {  }
  export interface ImmNoneValueReadConstructor { new(): ImmNoneValueRead; }
  export interface ImmNoneValueRead {  }
  export interface ImmErrorItemValueReadConstructor { new(): ImmErrorItemValueRead; }
  export interface ImmErrorItemValueRead {
    getMessage(): ImmerBox<string>;
    getFunction(): ImmerBox<haxorg_wasm.Optional<string>>;
    getLine(): ImmerBox<haxorg_wasm.Optional<number>>;
  }
  export interface ImmErrorGroupValueReadConstructor { new(): ImmErrorGroupValueRead; }
  export interface ImmErrorGroupValueRead {
    getDiagnostics(): ImmerFlex_vector<ImmIdT<ImmErrorItem>>;
    getFunction(): ImmerBox<haxorg_wasm.Optional<string>>;
    getLine(): ImmerBox<haxorg_wasm.Optional<number>>;
  }
  export interface ImmStmtListValueReadConstructor { new(): ImmStmtListValueRead; }
  export interface ImmStmtListValueRead {  }
  export interface ImmEmptyValueReadConstructor { new(): ImmEmptyValueRead; }
  export interface ImmEmptyValueRead {  }
  export interface ImmCmdCaptionValueReadConstructor { new(): ImmCmdCaptionValueRead; }
  export interface ImmCmdCaptionValueRead { getText(): ImmIdT<ImmParagraph>; }
  export interface ImmCmdColumnsValueReadConstructor { new(): ImmCmdColumnsValueRead; }
  export interface ImmCmdColumnsValueRead { getView(): ColumnView; }
  export interface ImmCmdNameValueReadConstructor { new(): ImmCmdNameValueRead; }
  export interface ImmCmdNameValueRead { getName(): ImmerBox<string>; }
  export interface ImmCmdCustomArgsValueReadConstructor { new(): ImmCmdCustomArgsValueRead; }
  export interface ImmCmdCustomArgsValueRead {
    getName(): ImmerBox<string>;
    getIsattached(): boolean;
  }
  export interface ImmCmdCustomRawValueReadConstructor { new(): ImmCmdCustomRawValueRead; }
  export interface ImmCmdCustomRawValueRead {
    getName(): ImmerBox<string>;
    getIsattached(): boolean;
    getText(): ImmerBox<string>;
  }
  export interface ImmCmdCustomTextValueReadConstructor { new(): ImmCmdCustomTextValueRead; }
  export interface ImmCmdCustomTextValueRead {
    getName(): ImmerBox<string>;
    getIsattached(): boolean;
    getText(): ImmIdT<ImmParagraph>;
  }
  export interface ImmCmdCallValueReadConstructor { new(): ImmCmdCallValueRead; }
  export interface ImmCmdCallValueRead {
    getName(): ImmerBox<string>;
    getFilename(): ImmerBox<haxorg_wasm.Optional<string>>;
    getInsideheaderattrs(): AttrGroup;
    getCallattrs(): AttrGroup;
    getEndheaderattrs(): AttrGroup;
    getResult(): ImmerFlex_vector<ImmIdT<ImmBlockCodeEvalResult>>;
  }
  export interface ImmCmdTblfmValueReadConstructor { new(): ImmCmdTblfmValueRead; }
  export interface ImmCmdTblfmValueRead { getExpr(): Tblfm; }
  export interface ImmHashTagValueReadConstructor { new(): ImmHashTagValueRead; }
  export interface ImmHashTagValueRead { getText(): HashTagText; }
  export interface ImmInlineFootnoteValueReadConstructor { new(): ImmInlineFootnoteValueRead; }
  export interface ImmInlineFootnoteValueRead {
    getTag(): ImmerBox<string>;
    getDefinition(): ImmerBox<haxorg_wasm.Optional<ImmIdT<ImmOrg>>>;
  }
  export interface ImmInlineExportValueReadConstructor { new(): ImmInlineExportValueRead; }
  export interface ImmInlineExportValueRead {
    getExporter(): ImmerBox<string>;
    getContent(): ImmerBox<string>;
  }
  export interface ImmTimeValueReadConstructor { new(): ImmTimeValueRead; }
  export interface ImmTimeValueRead {
    getIsactive(): boolean;
    getTime(): ImmTimeTimeVariant;
  }
  export interface ImmTimeRangeValueReadConstructor { new(): ImmTimeRangeValueRead; }
  export interface ImmTimeRangeValueRead {
    getFrom(): ImmIdT<ImmTime>;
    getTo(): ImmIdT<ImmTime>;
  }
  export interface ImmMacroValueReadConstructor { new(): ImmMacroValueRead; }
  export interface ImmMacroValueRead {
    getName(): ImmerBox<string>;
    getAttrs(): AttrGroup;
  }
  export interface ImmSymbolValueReadConstructor { new(): ImmSymbolValueRead; }
  export interface ImmSymbolValueRead {
    getName(): ImmerBox<string>;
    getParameters(): ImmerFlex_vector<ImmSymbolParam>;
    getPositional(): ImmerFlex_vector<ImmIdT<ImmOrg>>;
  }
  export interface ImmEscapedValueReadConstructor { new(): ImmEscapedValueRead; }
  export interface ImmEscapedValueRead {  }
  export interface ImmNewlineValueReadConstructor { new(): ImmNewlineValueRead; }
  export interface ImmNewlineValueRead {  }
  export interface ImmSpaceValueReadConstructor { new(): ImmSpaceValueRead; }
  export interface ImmSpaceValueRead {  }
  export interface ImmWordValueReadConstructor { new(): ImmWordValueRead; }
  export interface ImmWordValueRead {  }
  export interface ImmAtMentionValueReadConstructor { new(): ImmAtMentionValueRead; }
  export interface ImmAtMentionValueRead {  }
  export interface ImmRawTextValueReadConstructor { new(): ImmRawTextValueRead; }
  export interface ImmRawTextValueRead {  }
  export interface ImmPunctuationValueReadConstructor { new(): ImmPunctuationValueRead; }
  export interface ImmPunctuationValueRead {  }
  export interface ImmPlaceholderValueReadConstructor { new(): ImmPlaceholderValueRead; }
  export interface ImmPlaceholderValueRead {  }
  export interface ImmBigIdentValueReadConstructor { new(): ImmBigIdentValueRead; }
  export interface ImmBigIdentValueRead {  }
  export interface ImmTextTargetValueReadConstructor { new(): ImmTextTargetValueRead; }
  export interface ImmTextTargetValueRead {  }
  export interface ImmBoldValueReadConstructor { new(): ImmBoldValueRead; }
  export interface ImmBoldValueRead {  }
  export interface ImmUnderlineValueReadConstructor { new(): ImmUnderlineValueRead; }
  export interface ImmUnderlineValueRead {  }
  export interface ImmMonospaceValueReadConstructor { new(): ImmMonospaceValueRead; }
  export interface ImmMonospaceValueRead {  }
  export interface ImmMarkQuoteValueReadConstructor { new(): ImmMarkQuoteValueRead; }
  export interface ImmMarkQuoteValueRead {  }
  export interface ImmVerbatimValueReadConstructor { new(): ImmVerbatimValueRead; }
  export interface ImmVerbatimValueRead {  }
  export interface ImmItalicValueReadConstructor { new(): ImmItalicValueRead; }
  export interface ImmItalicValueRead {  }
  export interface ImmStrikeValueReadConstructor { new(): ImmStrikeValueRead; }
  export interface ImmStrikeValueRead {  }
  export interface ImmParValueReadConstructor { new(): ImmParValueRead; }
  export interface ImmParValueRead {  }
  export interface ImmRadioTargetValueReadConstructor { new(): ImmRadioTargetValueRead; }
  export interface ImmRadioTargetValueRead { getWords(): ImmerFlex_vector<string>; }
  export interface ImmLatexValueReadConstructor { new(): ImmLatexValueRead; }
  export interface ImmLatexValueRead {  }
  export interface ImmLinkValueReadConstructor { new(): ImmLinkValueRead; }
  export interface ImmLinkValueRead {
    getDescription(): ImmerBox<haxorg_wasm.Optional<ImmIdT<ImmParagraph>>>;
    getTarget(): LinkTarget;
  }
  export interface ImmBlockCenterValueReadConstructor { new(): ImmBlockCenterValueRead; }
  export interface ImmBlockCenterValueRead {  }
  export interface ImmBlockQuoteValueReadConstructor { new(): ImmBlockQuoteValueRead; }
  export interface ImmBlockQuoteValueRead {  }
  export interface ImmBlockCommentValueReadConstructor { new(): ImmBlockCommentValueRead; }
  export interface ImmBlockCommentValueRead {  }
  export interface ImmBlockVerseValueReadConstructor { new(): ImmBlockVerseValueRead; }
  export interface ImmBlockVerseValueRead {  }
  export interface ImmBlockDynamicFallbackValueReadConstructor { new(): ImmBlockDynamicFallbackValueRead; }
  export interface ImmBlockDynamicFallbackValueRead { getName(): ImmerBox<string>; }
  export interface ImmBlockExampleValueReadConstructor { new(): ImmBlockExampleValueRead; }
  export interface ImmBlockExampleValueRead {  }
  export interface ImmBlockExportValueReadConstructor { new(): ImmBlockExportValueRead; }
  export interface ImmBlockExportValueRead {
    getExporter(): ImmerBox<string>;
    getContent(): ImmerBox<string>;
  }
  export interface ImmBlockAdmonitionValueReadConstructor { new(): ImmBlockAdmonitionValueRead; }
  export interface ImmBlockAdmonitionValueRead {  }
  export interface ImmBlockCodeEvalResultValueReadConstructor { new(): ImmBlockCodeEvalResultValueRead; }
  export interface ImmBlockCodeEvalResultValueRead {
    getRaw(): ImmerFlex_vector<OrgCodeEvalOutput>;
    getNode(): ImmIdT<ImmOrg>;
  }
  export interface ImmBlockCodeValueReadConstructor { new(): ImmBlockCodeValueRead; }
  export interface ImmBlockCodeValueRead {
    getLang(): ImmerBox<haxorg_wasm.Optional<string>>;
    getExports(): BlockCodeExports;
    getResult(): ImmerFlex_vector<ImmIdT<ImmBlockCodeEvalResult>>;
    getLines(): ImmerFlex_vector<BlockCodeLine>;
    getCache(): boolean;
    getEval(): boolean;
    getNoweb(): boolean;
    getHlines(): boolean;
    getTangle(): boolean;
    getSwitches(): AttrGroup;
  }
  export interface ImmSubtreeLogValueReadConstructor { new(): ImmSubtreeLogValueRead; }
  export interface ImmSubtreeLogValueRead {
    getHead(): SubtreeLogHead;
    getDesc(): ImmerBox<haxorg_wasm.Optional<ImmIdT<ImmStmtList>>>;
  }
  export interface ImmSubtreeValueReadConstructor { new(): ImmSubtreeValueRead; }
  export interface ImmSubtreeValueRead {
    getLevel(): number;
    getTreeid(): ImmerBox<haxorg_wasm.Optional<string>>;
    getTodo(): ImmerBox<haxorg_wasm.Optional<string>>;
    getCompletion(): ImmerBox<haxorg_wasm.Optional<SubtreeCompletion>>;
    getDescription(): ImmerBox<haxorg_wasm.Optional<ImmIdT<ImmParagraph>>>;
    getTags(): ImmerFlex_vector<ImmIdT<ImmHashTag>>;
    getTitle(): ImmIdT<ImmParagraph>;
    getLogbook(): ImmerFlex_vector<ImmIdT<ImmSubtreeLog>>;
    getProperties(): ImmerFlex_vector<NamedProperty>;
    getClosed(): ImmerBox<haxorg_wasm.Optional<UserTime>>;
    getDeadline(): ImmerBox<haxorg_wasm.Optional<UserTime>>;
    getScheduled(): ImmerBox<haxorg_wasm.Optional<UserTime>>;
    getIscomment(): boolean;
    getIsarchived(): boolean;
    getPriority(): ImmerBox<haxorg_wasm.Optional<string>>;
  }
  export interface ImmCellValueReadConstructor { new(): ImmCellValueRead; }
  export interface ImmCellValueRead { getIsblock(): boolean; }
  export interface ImmRowValueReadConstructor { new(): ImmRowValueRead; }
  export interface ImmRowValueRead {
    getCells(): ImmerFlex_vector<ImmIdT<ImmCell>>;
    getIsblock(): boolean;
  }
  export interface ImmTableValueReadConstructor { new(): ImmTableValueRead; }
  export interface ImmTableValueRead {
    getRows(): ImmerFlex_vector<ImmIdT<ImmRow>>;
    getIsblock(): boolean;
  }
  export interface ImmParagraphValueReadConstructor { new(): ImmParagraphValueRead; }
  export interface ImmParagraphValueRead {  }
  export interface ImmColonExampleValueReadConstructor { new(): ImmColonExampleValueRead; }
  export interface ImmColonExampleValueRead {  }
  export interface ImmCmdAttrValueReadConstructor { new(): ImmCmdAttrValueRead; }
  export interface ImmCmdAttrValueRead { getTarget(): ImmerBox<string>; }
  export interface ImmCmdExportValueReadConstructor { new(): ImmCmdExportValueRead; }
  export interface ImmCmdExportValueRead {
    getExporter(): ImmerBox<string>;
    getContent(): ImmerBox<string>;
  }
  export interface ImmCallValueReadConstructor { new(): ImmCallValueRead; }
  export interface ImmCallValueRead {
    getName(): ImmerBox<string>;
    getAttrs(): AttrGroup;
    getIscommand(): boolean;
  }
  export interface ImmListValueReadConstructor { new(): ImmListValueRead; }
  export interface ImmListValueRead {  }
  export interface ImmListItemValueReadConstructor { new(): ImmListItemValueRead; }
  export interface ImmListItemValueRead {
    getCheckbox(): CheckboxState;
    getHeader(): ImmerBox<haxorg_wasm.Optional<ImmIdT<ImmParagraph>>>;
    getBullet(): ImmerBox<haxorg_wasm.Optional<string>>;
  }
  export interface ImmDocumentOptionsValueReadConstructor { new(): ImmDocumentOptionsValueRead; }
  export interface ImmDocumentOptionsValueRead {
    getInitialvisibility(): InitialSubtreeVisibility;
    getProperties(): ImmerFlex_vector<NamedProperty>;
    getExportconfig(): DocumentExportConfig;
    getFixedwidthsections(): ImmerBox<haxorg_wasm.Optional<boolean>>;
    getStartupindented(): ImmerBox<haxorg_wasm.Optional<boolean>>;
    getCategory(): ImmerBox<haxorg_wasm.Optional<string>>;
    getSetupfile(): ImmerBox<haxorg_wasm.Optional<string>>;
    getMaxsubtreelevelexport(): ImmerBox<haxorg_wasm.Optional<number>>;
    getColumns(): ImmerBox<haxorg_wasm.Optional<ColumnView>>;
    getTodokeywords(): ImmerFlex_vector<TodoKeyword>;
    getDonekeywords(): ImmerFlex_vector<TodoKeyword>;
  }
  export interface ImmDocumentFragmentValueReadConstructor { new(): ImmDocumentFragmentValueRead; }
  export interface ImmDocumentFragmentValueRead {
    getBaseline(): number;
    getBasecol(): number;
  }
  export interface ImmCriticMarkupValueReadConstructor { new(): ImmCriticMarkupValueRead; }
  export interface ImmCriticMarkupValueRead { getKind(): ImmCriticMarkupKind; }
  export interface ImmDocumentValueReadConstructor { new(): ImmDocumentValueRead; }
  export interface ImmDocumentValueRead {
    getTitle(): ImmerBox<haxorg_wasm.Optional<ImmIdT<ImmParagraph>>>;
    getAuthor(): ImmerBox<haxorg_wasm.Optional<ImmIdT<ImmParagraph>>>;
    getCreator(): ImmerBox<haxorg_wasm.Optional<ImmIdT<ImmParagraph>>>;
    getFiletags(): ImmerFlex_vector<ImmIdT<ImmHashTag>>;
    getEmail(): ImmerBox<haxorg_wasm.Optional<ImmIdT<ImmRawText>>>;
    getLanguage(): ImmerFlex_vector<string>;
    getOptions(): ImmIdT<ImmDocumentOptions>;
    getExportfilename(): ImmerBox<haxorg_wasm.Optional<string>>;
  }
  export interface ImmFileTargetValueReadConstructor { new(): ImmFileTargetValueRead; }
  export interface ImmFileTargetValueRead {
    getPath(): ImmerBox<string>;
    getLine(): ImmerBox<haxorg_wasm.Optional<number>>;
    getSearchtarget(): ImmerBox<haxorg_wasm.Optional<string>>;
    getRestricttoheadlines(): boolean;
    getTargetid(): ImmerBox<haxorg_wasm.Optional<string>>;
    getRegexp(): ImmerBox<haxorg_wasm.Optional<string>>;
  }
  export interface ImmTextSeparatorValueReadConstructor { new(): ImmTextSeparatorValueRead; }
  export interface ImmTextSeparatorValueRead {  }
  export interface ImmDocumentGroupValueReadConstructor { new(): ImmDocumentGroupValueRead; }
  export interface ImmDocumentGroupValueRead {  }
  export interface ImmFileValueReadConstructor { new(): ImmFileValueRead; }
  export interface ImmFileValueRead {
    getRelpath(): ImmerBox<string>;
    getAbspath(): ImmerBox<string>;
    getData(): ImmFileData;
  }
  export interface ImmDirectoryValueReadConstructor { new(): ImmDirectoryValueRead; }
  export interface ImmDirectoryValueRead {
    getRelpath(): ImmerBox<string>;
    getAbspath(): ImmerBox<string>;
  }
  export interface ImmSymlinkValueReadConstructor { new(): ImmSymlinkValueRead; }
  export interface ImmSymlinkValueRead {
    getIsdirectory(): boolean;
    getAbspath(): ImmerBox<string>;
  }
  export interface ImmCmdIncludeValueReadConstructor { new(): ImmCmdIncludeValueRead; }
  export interface ImmCmdIncludeValueRead {
    getPath(): ImmerBox<string>;
    getFirstline(): ImmerBox<haxorg_wasm.Optional<number>>;
    getLastline(): ImmerBox<haxorg_wasm.Optional<number>>;
    getData(): ImmCmdIncludeData;
  }
  export interface ImmAstContextConstructor { new(): ImmAstContext; }
  export interface ImmAstContext {
    addRoot(data: Org): ImmAstVersion;
    get(id: ImmId): Org;
  }
  export interface ImmAstVersionConstructor { new(): ImmAstVersion; }
  export interface ImmAstVersion {
    getRoot(): ImmId;
    getRootAdapter(): ImmAdapter;
    getContext(): StdShared_ptr<ImmAstContext>;
  }
  export interface ImmAdapterConstructor { new(): ImmAdapter; }
  export interface ImmAdapter {
    size(): number;
    isNil(): boolean;
    isRoot(): boolean;
    getKind(): OrgSemKind;
    uniq(): ImmUniqId;
    treeReprString(): string;
    treeReprStringOpts(conf: ImmAdapterTreeReprConf): string;
    isDirectParentOf(other: ImmAdapter): boolean;
    isIndirectParentOf(other: ImmAdapter): boolean;
    isSubnodeOf(other: ImmAdapter): boolean;
    getParent(): haxorg_wasm.Optional<ImmAdapter>;
    getSelfIndex(): number;
    atIdReflPathStep(id: ImmId, idx: ImmPathStep): ImmAdapter;
    atField(field: ImmReflFieldId): ImmAdapter;
    atIndex(idx: number, withPath: boolean): ImmAdapter;
    atPath(path: Vec<number>, withPath: boolean): ImmAdapter;
    is(kind: OrgSemKind): boolean;
    sub(withPath: boolean): Vec<ImmAdapter>;
  }
  export interface ImmAdapterTreeReprConfConstructor { new(): ImmAdapterTreeReprConf; }
  export interface ImmAdapterTreeReprConf {
    maxDepth: number
    withAuxFields: boolean
    withReflFields: boolean
  }
  export interface ImmAdapterVirtualBaseConstructor { new(): ImmAdapterVirtualBase; }
  export interface ImmAdapterVirtualBase {  }
  export interface OrgParseFragmentConstructor { new(): OrgParseFragment; }
  export interface OrgParseFragment {
    baseLine: number
    baseCol: number
    text: string
  }
  export interface OrgParseParametersConstructor { new(): OrgParseParameters; }
  export interface OrgParseParameters {
    baseTokenTracePath: haxorg_wasm.Optional<string>
    tokenTracePath: haxorg_wasm.Optional<string>
    parseTracePath: haxorg_wasm.Optional<string>
    semTracePath: haxorg_wasm.Optional<string>
  }
  export interface OrgDirectoryParseParametersConstructor { new(): OrgDirectoryParseParameters; }
  export interface OrgDirectoryParseParameters {  }
  export interface OrgYamlExportOptsConstructor { new(): OrgYamlExportOpts; }
  export interface OrgYamlExportOpts {
    skipNullFields: boolean
    skipFalseFields: boolean
    skipZeroFields: boolean
    skipLocation: boolean
    skipId: boolean
  }
  export interface OrgTreeExportOptsConstructor { new(): OrgTreeExportOpts; }
  export interface OrgTreeExportOpts {
    withLineCol: boolean
    withOriginalId: boolean
    withSubnodeIdx: boolean
    skipEmptyFields: boolean
    startLevel: number
    withColor: boolean
    maxDepth: number
  }
  export interface AstTrackingPathConstructor { new(): AstTrackingPath; }
  export interface AstTrackingPath {
    getParent(offset: number): Org;
    getNode(): Org;
    path: Vec<Org>
  }
  export interface AstTrackingAlternativesConstructor { new(): AstTrackingAlternatives; }
  export interface AstTrackingAlternatives {
    getAllNodes(): Vec<Org>;
    getNode(): Org;
  }
  export interface AstTrackingGroupConstructor { new(): AstTrackingGroup; }
  export interface AstTrackingGroup {
    getRadioTargetConst(): AstTrackingGroupRadioTarget;
    getTrackedHashtagConst(): AstTrackingGroupTrackedHashtag;
    getTrackedHashtagMut(): AstTrackingGroupTrackedHashtag;
    getSingleConst(): AstTrackingGroupSingle;
    getRadioTargetMut(): AstTrackingGroupRadioTarget;
    getSingleMut(): AstTrackingGroupSingle;
    isSingle(): boolean;
    isTrackedHashtag(): boolean;
    isRadioTarget(): boolean;
  }
  export interface AstTrackingGroupRadioTargetConstructor { new(): AstTrackingGroupRadioTarget; }
  export interface AstTrackingGroupRadioTarget {
    target: AstTrackingPath
    nodes: Vec<Org>
  }
  export interface AstTrackingGroupSingleConstructor { new(): AstTrackingGroupSingle; }
  export interface AstTrackingGroupSingle { node: Org }
  export interface AstTrackingGroupTrackedHashtagConstructor { new(): AstTrackingGroupTrackedHashtag; }
  export interface AstTrackingGroupTrackedHashtag {
    tag: Org
    targets: UnorderedMap<HashTagFlat, AstTrackingPath>
  }
  export interface AstTrackingMapConstructor { new(): AstTrackingMap; }
  export interface AstTrackingMap {
    getIdPath(id: string): haxorg_wasm.Optional<AstTrackingAlternatives>;
    getNamePath(id: string): haxorg_wasm.Optional<AstTrackingAlternatives>;
    getAnchorTarget(id: string): haxorg_wasm.Optional<AstTrackingAlternatives>;
    getFootnotePath(id: string): haxorg_wasm.Optional<AstTrackingAlternatives>;
    footnotes: UnorderedMap<string, AstTrackingAlternatives>
    subtrees: UnorderedMap<string, AstTrackingAlternatives>
    names: UnorderedMap<string, AstTrackingAlternatives>
    anchorTargets: UnorderedMap<string, AstTrackingAlternatives>
    radioTargets: UnorderedMap<string, AstTrackingAlternatives>
    hashtagDefinitions: UnorderedMap<HashTagFlat, AstTrackingAlternatives>
  }
  export interface SequenceSegmentConstructor { new(): SequenceSegment; }
  export interface SequenceSegment {
    kind: number
    first: number
    last: number
  }
  export interface SequenceSegmentGroupConstructor { new(): SequenceSegmentGroup; }
  export interface SequenceSegmentGroup {
    kind: number
    segments: Vec<SequenceSegment>
  }
  export interface SequenceAnnotationTagConstructor { new(): SequenceAnnotationTag; }
  export interface SequenceAnnotationTag {
    groupKind: number
    segmentKinds: Vec<number>
  }
  export interface SequenceAnnotationConstructor { new(): SequenceAnnotation; }
  export interface SequenceAnnotation {
    isAnnotatedWith(groupKind: number, segmentKind: number): boolean;
    first: number
    last: number
    annotations: Vec<SequenceAnnotationTag>
  }
  export interface GraphMapLinkConstructor { new(): GraphMapLink; }
  export interface GraphMapLink {  }
  export interface GraphMapLinkLinkConstructor { new(): GraphMapLinkLink; }
  export interface GraphMapLinkLink {  }
  export interface GraphMapLinkRadioConstructor { new(): GraphMapLinkRadio; }
  export interface GraphMapLinkRadio {  }
  export interface GraphMapNodePropConstructor { new(): GraphMapNodeProp; }
  export interface GraphMapNodeProp {
    getSubtreeId(): haxorg_wasm.Optional<string>;
    getFootnoteName(): haxorg_wasm.Optional<string>;
    id: ImmAdapter
    unresolved: Vec<GraphMapLink>
  }
  export interface GraphMapEdgePropConstructor { new(): GraphMapEdgeProp; }
  export interface GraphMapEdgeProp { link: GraphMapLink }
  export interface GraphMapNodeConstructor { new(): GraphMapNode; }
  export interface GraphMapNode {
    __eq__(other: GraphMapNode): boolean;
    __lt__(other: GraphMapNode): boolean;
    id: ImmUniqId
  }
  export interface GraphMapEdgeConstructor { new(): GraphMapEdge; }
  export interface GraphMapEdge {
    source: GraphMapNode
    target: GraphMapNode
  }
  export interface GraphMapGraphConstructor { new(): GraphMapGraph; }
  export interface GraphMapGraph {
    nodeCount(): number;
    edgeCount(): number;
    outNodes(node: GraphMapNode): GraphAdjNodesList;
    inNodes(node: GraphMapNode): GraphAdjNodesList;
    adjEdges(node: GraphMapNode): Vec<GraphMapEdge>;
    adjNodes(node: GraphMapNode): Vec<GraphMapNode>;
    outEdges(node: GraphMapNode): Vec<GraphMapEdge>;
    inEdges(node: GraphMapNode): Vec<GraphMapEdge>;
    outDegree(node: GraphMapNode): number;
    inDegree(node: GraphMapNode): number;
    isRegisteredNode(id: GraphMapNode): boolean;
    isRegisteredNodeById(id: ImmUniqId): boolean;
    atMapNode(node: GraphMapNode): GraphMapNodeProp;
    atMapEdge(edge: GraphMapEdge): GraphMapEdgeProp;
    addEdge(edge: GraphMapEdge): void;
    addEdgeWithProp(edge: GraphMapEdge, prop: GraphMapEdgeProp): void;
    addNode(node: GraphMapNode): void;
    addNodeWithProp(node: GraphMapNode, prop: GraphMapNodeProp): void;
    hasEdge(source: GraphMapNode, target: GraphMapNode): boolean;
    hasNode(node: GraphMapNode): boolean;
    has2AdapterEdge(source: ImmAdapter, target: ImmAdapter): boolean;
    nodeProps: GraphNodeProps
    edgeProps: GraphEdgeProps
    adjList: GraphAdjList
    adjListIn: GraphAdjList
  }
  export interface GraphMapGraphStateConstructor { new(): GraphMapGraphState; }
  export interface GraphMapGraphState {
    FromAstContext(ast: StdShared_ptr<ImmAstContext>): GraphMapGraphState;
    registerNode(node: GraphMapNodeProp, conf: StdShared_ptr<GraphMapConfig>): void;
    addNode(node: ImmAdapter, conf: StdShared_ptr<GraphMapConfig>): void;
    addNodeRec(node: ImmAdapter, conf: StdShared_ptr<GraphMapConfig>): void;
    getUnresolvedSubtreeLinks(node: ImmAdapterT<ImmSubtree>, conf: StdShared_ptr<GraphMapConfig>): Vec<GraphMapLink>;
    getUnresolvedLink(node: ImmAdapterT<ImmLink>, conf: StdShared_ptr<GraphMapConfig>): haxorg_wasm.Optional<GraphMapLink>;
    graph: GraphMapGraph
    ast: StdShared_ptr<ImmAstContext>
  }
  export interface LispCodeConstructor { new(): LispCode; }
  export interface LispCode {
    __eq__(other: LispCode): boolean;
    LispCode(): void;
    isCall(): boolean;
    getCallConst(): LispCodeCall;
    getCallMut(): LispCodeCall;
    isList(): boolean;
    getListConst(): LispCodeList;
    getListMut(): LispCodeList;
    isKeyValue(): boolean;
    getKeyValueConst(): LispCodeKeyValue;
    getKeyValueMut(): LispCodeKeyValue;
    isNumber(): boolean;
    getNumberConst(): LispCodeNumber;
    getNumberMut(): LispCodeNumber;
    isText(): boolean;
    getTextConst(): LispCodeText;
    getTextMut(): LispCodeText;
    isIdent(): boolean;
    getIdentConst(): LispCodeIdent;
    getIdentMut(): LispCodeIdent;
    isBoolean(): boolean;
    getBooleanConst(): LispCodeBoolean;
    getBooleanMut(): LispCodeBoolean;
    isReal(): boolean;
    getRealConst(): LispCodeReal;
    getRealMut(): LispCodeReal;
    getKindStatic(__input: LispCodeData): LispCodeKind;
    getKind(): LispCodeKind;
    sub_variant_get_name(): Char;
    sub_variant_get_data(): LispCodeData;
    sub_variant_get_kind(): LispCodeKind;
    data: LispCodeData
  }
  export interface LispCodeCallConstructor { new(): LispCodeCall; }
  export interface LispCodeCall {
    __eq__(other: LispCodeCall): boolean;
    Call(): void;
    name: string
    args: Vec<LispCode>
  }
  export interface LispCodeListConstructor { new(): LispCodeList; }
  export interface LispCodeList {
    __eq__(other: LispCodeList): boolean;
    List(): void;
    items: Vec<LispCode>
  }
  export interface LispCodeKeyValueConstructor { new(): LispCodeKeyValue; }
  export interface LispCodeKeyValue {
    __eq__(other: LispCodeKeyValue): boolean;
    KeyValue(): void;
    name: string
    value: Vec<LispCode>
  }
  export interface LispCodeNumberConstructor { new(): LispCodeNumber; }
  export interface LispCodeNumber {
    __eq__(other: LispCodeNumber): boolean;
    Number(): void;
    value: number
  }
  export interface LispCodeTextConstructor { new(): LispCodeText; }
  export interface LispCodeText {
    __eq__(other: LispCodeText): boolean;
    Text(): void;
    value: string
  }
  export interface LispCodeIdentConstructor { new(): LispCodeIdent; }
  export interface LispCodeIdent {
    __eq__(other: LispCodeIdent): boolean;
    Ident(): void;
    name: string
  }
  export interface LispCodeBooleanConstructor { new(): LispCodeBoolean; }
  export interface LispCodeBoolean {
    __eq__(other: LispCodeBoolean): boolean;
    Boolean(): void;
    value: boolean
  }
  export interface LispCodeRealConstructor { new(): LispCodeReal; }
  export interface LispCodeReal {
    __eq__(other: LispCodeReal): boolean;
    Real(): void;
    value: Float
  }
  export enum OrgSemLispCodeKind {
    Call,
    List,
    KeyValue,
    Number,
    Text,
    Ident,
    Boolean,
    Real,
  }
  export interface TblfmConstructor { new(): Tblfm; }
  export interface Tblfm {
    __eq__(other: Tblfm): boolean;
    exprs: Vec<TblfmAssign>
  }
  export interface TblfmExprConstructor { new(): TblfmExpr; }
  export interface TblfmExpr {
    __eq__(other: TblfmExpr): boolean;
    isAxisRef(): boolean;
    getAxisRefConst(): TblfmExprAxisRef;
    getAxisRefMut(): TblfmExprAxisRef;
    isAxisName(): boolean;
    getAxisNameConst(): TblfmExprAxisName;
    getAxisNameMut(): TblfmExprAxisName;
    isIntLiteral(): boolean;
    getIntLiteralConst(): TblfmExprIntLiteral;
    getIntLiteralMut(): TblfmExprIntLiteral;
    isFloatLiteral(): boolean;
    getFloatLiteralConst(): TblfmExprFloatLiteral;
    getFloatLiteralMut(): TblfmExprFloatLiteral;
    isRangeRef(): boolean;
    getRangeRefConst(): TblfmExprRangeRef;
    getRangeRefMut(): TblfmExprRangeRef;
    isCall(): boolean;
    getCallConst(): TblfmExprCall;
    getCallMut(): TblfmExprCall;
    isElisp(): boolean;
    getElispConst(): TblfmExprElisp;
    getElispMut(): TblfmExprElisp;
    getKindStatic(__input: TblfmExprData): TblfmExprKind;
    getKind(): TblfmExprKind;
    sub_variant_get_name(): Char;
    sub_variant_get_data(): TblfmExprData;
    sub_variant_get_kind(): TblfmExprKind;
    data: TblfmExprData
  }
  export interface TblfmExprAxisRefConstructor { new(): TblfmExprAxisRef; }
  export interface TblfmExprAxisRef {
    __eq__(other: TblfmExprAxisRef): boolean;
    col: TblfmExprAxisRefPosition
    row: haxorg_wasm.Optional<TblfmExprAxisRefPosition>
  }
  export interface TblfmExprAxisRefPositionConstructor { new(): TblfmExprAxisRefPosition; }
  export interface TblfmExprAxisRefPosition {
    __eq__(other: TblfmExprAxisRefPosition): boolean;
    isIndex(): boolean;
    getIndexConst(): TblfmExprAxisRefPositionIndex;
    getIndexMut(): TblfmExprAxisRefPositionIndex;
    isName(): boolean;
    getNameConst(): TblfmExprAxisRefPositionName;
    getNameMut(): TblfmExprAxisRefPositionName;
    getKindStatic(__input: TblfmExprAxisRefPositionData): TblfmExprAxisRefPositionKind;
    getKind(): TblfmExprAxisRefPositionKind;
    sub_variant_get_name(): Char;
    sub_variant_get_data(): TblfmExprAxisRefPositionData;
    sub_variant_get_kind(): TblfmExprAxisRefPositionKind;
    data: TblfmExprAxisRefPositionData
  }
  export interface TblfmExprAxisRefPositionIndexConstructor { new(): TblfmExprAxisRefPositionIndex; }
  export interface TblfmExprAxisRefPositionIndex {
    __eq__(other: TblfmExprAxisRefPositionIndex): boolean;
    index: number
  }
  export interface TblfmExprAxisRefPositionNameConstructor { new(): TblfmExprAxisRefPositionName; }
  export interface TblfmExprAxisRefPositionName {
    __eq__(other: TblfmExprAxisRefPositionName): boolean;
    name: string
  }
  export enum OrgSemTblfmExprAxisRefPositionKind {
    Index,
    Name,
  }
  export interface TblfmExprAxisNameConstructor { new(): TblfmExprAxisName; }
  export interface TblfmExprAxisName {
    __eq__(other: TblfmExprAxisName): boolean;
    name: string
  }
  export interface TblfmExprIntLiteralConstructor { new(): TblfmExprIntLiteral; }
  export interface TblfmExprIntLiteral {
    __eq__(other: TblfmExprIntLiteral): boolean;
    value: number
  }
  export interface TblfmExprFloatLiteralConstructor { new(): TblfmExprFloatLiteral; }
  export interface TblfmExprFloatLiteral {
    __eq__(other: TblfmExprFloatLiteral): boolean;
    value: Float
  }
  export interface TblfmExprRangeRefConstructor { new(): TblfmExprRangeRef; }
  export interface TblfmExprRangeRef {
    __eq__(other: TblfmExprRangeRef): boolean;
    first: haxorg_wasm.Optional<TblfmExprAxisRef>
    last: haxorg_wasm.Optional<TblfmExprAxisRef>
  }
  export interface TblfmExprCallConstructor { new(): TblfmExprCall; }
  export interface TblfmExprCall {
    __eq__(other: TblfmExprCall): boolean;
    name: string
    args: Vec<TblfmExpr>
  }
  export interface TblfmExprElispConstructor { new(): TblfmExprElisp; }
  export interface TblfmExprElisp {
    __eq__(other: TblfmExprElisp): boolean;
    value: string
  }
  export enum OrgSemTblfmExprKind {
    AxisRef,
    AxisName,
    IntLiteral,
    FloatLiteral,
    RangeRef,
    Call,
    Elisp,
  }
  export interface TblfmAssignConstructor { new(): TblfmAssign; }
  export interface TblfmAssign {
    __eq__(other: TblfmAssign): boolean;
    target: TblfmExprAxisRef
    expr: Vec<TblfmExpr>
    flags: Vec<TblfmAssignFlag>
  }
  export enum OrgSemTblfmAssignFlag {
    CellLeftAlign,
    CellRightAlign,
    CellCenterAlign,
    CellNumber,
    CellExponential,
    CellFloating,
    CellUnformat,
    CellText,
    CellBool,
    CellDecimal,
    CellPercentage,
    CellHours,
    CellZero,
    CellMarkInvalid,
    CellQuote,
  }
  export interface AttrValueConstructor { new(): AttrValue; }
  export interface AttrValue {
    getBool(): haxorg_wasm.Optional<boolean>;
    getInt(): haxorg_wasm.Optional<number>;
    getString(): string;
    getFile(): string;
    getReference(): string;
    getDouble(): haxorg_wasm.Optional<Double>;
    __eq__(other: AttrValue): boolean;
    AttrValue(): void;
    isTextValue(): boolean;
    getTextValueConst(): AttrValueTextValue;
    getTextValueMut(): AttrValueTextValue;
    isFileReference(): boolean;
    getFileReferenceConst(): AttrValueFileReference;
    getFileReferenceMut(): AttrValueFileReference;
    isLispValue(): boolean;
    getLispValueConst(): AttrValueLispValue;
    getLispValueMut(): AttrValueLispValue;
    getDataKindStatic(__input: AttrValueDataVariant): AttrValueDataKind;
    getDataKind(): AttrValueDataKind;
    sub_variant_get_name(): Char;
    sub_variant_get_data(): AttrValueDataVariant;
    sub_variant_get_kind(): AttrValueDataKind;
    name: haxorg_wasm.Optional<string>
    varname: haxorg_wasm.Optional<string>
    span: Vec<AttrValueDimensionSpan>
    isQuoted: boolean
    data: AttrValueDataVariant
  }
  export enum OrgSemAttrValueKind {
    String,
    Boolean,
    Integer,
    Float,
    FileReference,
  }
  export interface AttrValueDimensionSpanConstructor { new(): AttrValueDimensionSpan; }
  export interface AttrValueDimensionSpan {
    DimensionSpan(): void;
    __eq__(other: AttrValueDimensionSpan): boolean;
    first: number
    last: haxorg_wasm.Optional<number>
  }
  export interface AttrValueTextValueConstructor { new(): AttrValueTextValue; }
  export interface AttrValueTextValue {
    __eq__(other: AttrValueTextValue): boolean;
    TextValue(): void;
    value: string
  }
  export interface AttrValueFileReferenceConstructor { new(): AttrValueFileReference; }
  export interface AttrValueFileReference {
    FileReference(): void;
    __eq__(other: AttrValueFileReference): boolean;
    file: string
    reference: string
  }
  export interface AttrValueLispValueConstructor { new(): AttrValueLispValue; }
  export interface AttrValueLispValue {
    __eq__(other: AttrValueLispValue): boolean;
    LispValue(): void;
    code: LispCode
  }
  export enum OrgSemAttrValueDataKind {
    TextValue,
    FileReference,
    LispValue,
  }
  export interface HashTagFlatConstructor { new(): HashTagFlat; }
  export interface HashTagFlat {
    __eq__(other: HashTagFlat): boolean;
    __lt__(other: HashTagFlat): boolean;
    tags: Vec<string>
  }
  export interface TodoKeywordConstructor { new(): TodoKeyword; }
  export interface TodoKeyword {
    __eq__(other: TodoKeyword): boolean;
    name: string
    shortcut: haxorg_wasm.Optional<string>
    onEnter: TodoKeywordTransition
    onLeave: TodoKeywordTransition
  }
  export enum OrgSemTodoKeywordTransition {
    None,
    NoteWithTimestamp,
    Timestamp,
  }
  export interface HashTagTextConstructor { new(): HashTagText; }
  export interface HashTagText {
    __eq__(other: HashTagText): boolean;
    prefixMatch(prefix: Vec<string>): boolean;
    getFlatHashes(withIntermediate: boolean): Vec<HashTagFlat>;
    head: string
    subtags: Vec<HashTagText>
  }
  export interface SubtreePathConstructor { new(): SubtreePath; }
  export interface SubtreePath {
    __eq__(other: SubtreePath): boolean;
    path: Vec<string>
  }
  export interface LinkTargetConstructor { new(): LinkTarget; }
  export interface LinkTarget {
    __eq__(other: LinkTarget): boolean;
    isRaw(): boolean;
    getRawConst(): LinkTargetRaw;
    getRawMut(): LinkTargetRaw;
    isId(): boolean;
    getIdConst(): LinkTargetId;
    getIdMut(): LinkTargetId;
    isCustomId(): boolean;
    getCustomIdConst(): LinkTargetCustomId;
    getCustomIdMut(): LinkTargetCustomId;
    isSubtreeTitle(): boolean;
    getSubtreeTitleConst(): LinkTargetSubtreeTitle;
    getSubtreeTitleMut(): LinkTargetSubtreeTitle;
    isPerson(): boolean;
    getPersonConst(): LinkTargetPerson;
    getPersonMut(): LinkTargetPerson;
    isUserProtocol(): boolean;
    getUserProtocolConst(): LinkTargetUserProtocol;
    getUserProtocolMut(): LinkTargetUserProtocol;
    isInternal(): boolean;
    getInternalConst(): LinkTargetInternal;
    getInternalMut(): LinkTargetInternal;
    isFootnote(): boolean;
    getFootnoteConst(): LinkTargetFootnote;
    getFootnoteMut(): LinkTargetFootnote;
    isFile(): boolean;
    getFileConst(): LinkTargetFile;
    getFileMut(): LinkTargetFile;
    isAttachment(): boolean;
    getAttachmentConst(): LinkTargetAttachment;
    getAttachmentMut(): LinkTargetAttachment;
    getKindStatic(__input: LinkTargetData): LinkTargetKind;
    getKind(): LinkTargetKind;
    sub_variant_get_name(): Char;
    sub_variant_get_data(): LinkTargetData;
    sub_variant_get_kind(): LinkTargetKind;
    data: LinkTargetData
  }
  export interface LinkTargetRawConstructor { new(): LinkTargetRaw; }
  export interface LinkTargetRaw {
    __eq__(other: LinkTargetRaw): boolean;
    text: string
  }
  export interface LinkTargetIdConstructor { new(): LinkTargetId; }
  export interface LinkTargetId {
    __eq__(other: LinkTargetId): boolean;
    text: string
  }
  export interface LinkTargetCustomIdConstructor { new(): LinkTargetCustomId; }
  export interface LinkTargetCustomId {
    __eq__(other: LinkTargetCustomId): boolean;
    text: string
  }
  export interface LinkTargetSubtreeTitleConstructor { new(): LinkTargetSubtreeTitle; }
  export interface LinkTargetSubtreeTitle {
    __eq__(other: LinkTargetSubtreeTitle): boolean;
    title: SubtreePath
    level: number
  }
  export interface LinkTargetPersonConstructor { new(): LinkTargetPerson; }
  export interface LinkTargetPerson {
    __eq__(other: LinkTargetPerson): boolean;
    name: string
  }
  export interface LinkTargetUserProtocolConstructor { new(): LinkTargetUserProtocol; }
  export interface LinkTargetUserProtocol {
    __eq__(other: LinkTargetUserProtocol): boolean;
    protocol: string
    target: string
  }
  export interface LinkTargetInternalConstructor { new(): LinkTargetInternal; }
  export interface LinkTargetInternal {
    __eq__(other: LinkTargetInternal): boolean;
    target: string
  }
  export interface LinkTargetFootnoteConstructor { new(): LinkTargetFootnote; }
  export interface LinkTargetFootnote {
    __eq__(other: LinkTargetFootnote): boolean;
    target: string
  }
  export interface LinkTargetFileConstructor { new(): LinkTargetFile; }
  export interface LinkTargetFile {
    __eq__(other: LinkTargetFile): boolean;
    file: string
  }
  export interface LinkTargetAttachmentConstructor { new(): LinkTargetAttachment; }
  export interface LinkTargetAttachment {
    __eq__(other: LinkTargetAttachment): boolean;
    file: string
  }
  export enum OrgSemLinkTargetKind {
    Raw,
    Id,
    CustomId,
    SubtreeTitle,
    Person,
    UserProtocol,
    Internal,
    Footnote,
    File,
    Attachment,
  }
  export interface SubtreeLogHeadConstructor { new(): SubtreeLogHead; }
  export interface SubtreeLogHead {
    __eq__(other: SubtreeLogHead): boolean;
    isPriority(): boolean;
    getPriorityConst(): SubtreeLogHeadPriority;
    getPriorityMut(): SubtreeLogHeadPriority;
    isNote(): boolean;
    getNoteConst(): SubtreeLogHeadNote;
    getNoteMut(): SubtreeLogHeadNote;
    isRefile(): boolean;
    getRefileConst(): SubtreeLogHeadRefile;
    getRefileMut(): SubtreeLogHeadRefile;
    isClock(): boolean;
    getClockConst(): SubtreeLogHeadClock;
    getClockMut(): SubtreeLogHeadClock;
    isState(): boolean;
    getStateConst(): SubtreeLogHeadState;
    getStateMut(): SubtreeLogHeadState;
    isDeadline(): boolean;
    getDeadlineConst(): SubtreeLogHeadDeadline;
    getDeadlineMut(): SubtreeLogHeadDeadline;
    isSchedule(): boolean;
    getScheduleConst(): SubtreeLogHeadSchedule;
    getScheduleMut(): SubtreeLogHeadSchedule;
    isTag(): boolean;
    getTagConst(): SubtreeLogHeadTag;
    getTagMut(): SubtreeLogHeadTag;
    isUnknown(): boolean;
    getUnknownConst(): SubtreeLogHeadUnknown;
    getUnknownMut(): SubtreeLogHeadUnknown;
    getLogKindStatic(__input: SubtreeLogHeadLogEntry): SubtreeLogHeadKind;
    getLogKind(): SubtreeLogHeadKind;
    sub_variant_get_name(): Char;
    sub_variant_get_data(): SubtreeLogHeadLogEntry;
    sub_variant_get_kind(): SubtreeLogHeadKind;
    log: SubtreeLogHeadLogEntry
  }
  export interface SubtreeLogHeadPriorityConstructor { new(): SubtreeLogHeadPriority; }
  export interface SubtreeLogHeadPriority {
    __eq__(other: SubtreeLogHeadPriority): boolean;
    oldPriority: haxorg_wasm.Optional<string>
    newPriority: haxorg_wasm.Optional<string>
    on: UserTime
    action: SubtreeLogHeadPriorityAction
  }
  export enum OrgSemSubtreeLogHeadPriorityAction {
    Added,
    Removed,
    Changed,
  }
  export interface SubtreeLogHeadNoteConstructor { new(): SubtreeLogHeadNote; }
  export interface SubtreeLogHeadNote {
    __eq__(other: SubtreeLogHeadNote): boolean;
    on: UserTime
  }
  export interface SubtreeLogHeadRefileConstructor { new(): SubtreeLogHeadRefile; }
  export interface SubtreeLogHeadRefile {
    __eq__(other: SubtreeLogHeadRefile): boolean;
    on: UserTime
    from: LinkTarget
  }
  export interface SubtreeLogHeadClockConstructor { new(): SubtreeLogHeadClock; }
  export interface SubtreeLogHeadClock {
    __eq__(other: SubtreeLogHeadClock): boolean;
    from: UserTime
    to: haxorg_wasm.Optional<UserTime>
  }
  export interface SubtreeLogHeadStateConstructor { new(): SubtreeLogHeadState; }
  export interface SubtreeLogHeadState {
    __eq__(other: SubtreeLogHeadState): boolean;
    from: string
    to: string
    on: UserTime
  }
  export interface SubtreeLogHeadDeadlineConstructor { new(): SubtreeLogHeadDeadline; }
  export interface SubtreeLogHeadDeadline {
    __eq__(other: SubtreeLogHeadDeadline): boolean;
    from: haxorg_wasm.Optional<UserTime>
    to: UserTime
    on: UserTime
  }
  export interface SubtreeLogHeadScheduleConstructor { new(): SubtreeLogHeadSchedule; }
  export interface SubtreeLogHeadSchedule {
    __eq__(other: SubtreeLogHeadSchedule): boolean;
    from: haxorg_wasm.Optional<UserTime>
    to: UserTime
    on: UserTime
  }
  export interface SubtreeLogHeadTagConstructor { new(): SubtreeLogHeadTag; }
  export interface SubtreeLogHeadTag {
    __eq__(other: SubtreeLogHeadTag): boolean;
    on: UserTime
    tag: HashTagText
    added: boolean
  }
  export interface SubtreeLogHeadUnknownConstructor { new(): SubtreeLogHeadUnknown; }
  export interface SubtreeLogHeadUnknown { __eq__(other: SubtreeLogHeadUnknown): boolean; }
  export enum OrgSemSubtreeLogHeadKind {
    Priority,
    Note,
    Refile,
    Clock,
    State,
    Deadline,
    Schedule,
    Tag,
    Unknown,
  }
  export interface SubtreeCompletionConstructor { new(): SubtreeCompletion; }
  export interface SubtreeCompletion {
    __eq__(other: SubtreeCompletion): boolean;
    done: number
    full: number
    isPercent: boolean
  }
  export interface AttrListConstructor { new(): AttrList; }
  export interface AttrList {
    __eq__(other: AttrList): boolean;
    items: Vec<AttrValue>
  }
  export interface AttrGroupConstructor { new(): AttrGroup; }
  export interface AttrGroup {
    getFlatArgs(): Vec<AttrValue>;
    getAttrs(key: haxorg_wasm.Optional<string>): Vec<AttrValue>;
    setNamedAttr(key: string, attrs: Vec<AttrValue>): void;
    setPositionalAttr(items: Vec<AttrValue>): void;
    getPositionalSize(): number;
    getNamedSize(): number;
    isEmpty(): boolean;
    getAll(): AttrList;
    atPositional(index: number): AttrValue;
    getPositional(index: number): haxorg_wasm.Optional<AttrValue>;
    atNamed(index: string): AttrList;
    getNamed(index: string): haxorg_wasm.Optional<AttrList>;
    atFirstNamed(index: string): AttrValue;
    getFirstNamed(index: string): haxorg_wasm.Optional<AttrValue>;
    atVarNamed(index: string): AttrList;
    getVarNamed(index: string): haxorg_wasm.Optional<AttrList>;
    atFirstVarNamed(index: string): AttrValue;
    getFirstVarNamed(index: string): haxorg_wasm.Optional<AttrValue>;
    __eq__(other: AttrGroup): boolean;
    positional: AttrList
    named: UnorderedMap<string, AttrList>
  }
  export interface OrgCodeEvalInputConstructor { new(): OrgCodeEvalInput; }
  export interface OrgCodeEvalInput {
    __eq__(other: OrgCodeEvalInput): boolean;
    blockAttrs: AttrGroup
    tangledCode: string
    exportType: haxorg_wasm.Optional<string>
    resultType: OrgCodeEvalInputResultType
    resultFormat: OrgCodeEvalInputResultFormat
    resultHandling: OrgCodeEvalInputResultHandling
    language: string
    argList: Vec<OrgCodeEvalInputVar>
  }
  export interface OrgCodeEvalInputVarConstructor { new(): OrgCodeEvalInputVar; }
  export interface OrgCodeEvalInputVar {
    __eq__(other: OrgCodeEvalInputVar): boolean;
    Var(): void;
    name: string
    value: OrgJson
  }
  export enum OrgSemOrgCodeEvalInputResultType {
    None,
    Table,
    List,
    Scalar,
    SaveFile,
  }
  export enum OrgSemOrgCodeEvalInputResultFormat {
    None,
    Raw,
    Code,
    Drawer,
    ExportType,
    Link,
  }
  export enum OrgSemOrgCodeEvalInputResultHandling {
    None,
    Replace,
    Silent,
    Discard,
    Append,
    Prepend,
  }
  export interface OrgCodeEvalOutputConstructor { new(): OrgCodeEvalOutput; }
  export interface OrgCodeEvalOutput {
    __eq__(other: OrgCodeEvalOutput): boolean;
    stdoutText: string
    stderrText: string
    code: number
    cmd: haxorg_wasm.Optional<string>
    args: Vec<string>
    cwd: string
    appliedHeaderArg: AttrGroup
  }
  export interface ColumnViewConstructor { new(): ColumnView; }
  export interface ColumnView {
    __eq__(other: ColumnView): boolean;
    columns: Vec<ColumnViewColumn>
  }
  export interface ColumnViewSummaryConstructor { new(): ColumnViewSummary; }
  export interface ColumnViewSummary {
    __eq__(other: ColumnViewSummary): boolean;
    isCheckboxAggregate(): boolean;
    getCheckboxAggregateConst(): ColumnViewSummaryCheckboxAggregate;
    getCheckboxAggregateMut(): ColumnViewSummaryCheckboxAggregate;
    isMathAggregate(): boolean;
    getMathAggregateConst(): ColumnViewSummaryMathAggregate;
    getMathAggregateMut(): ColumnViewSummaryMathAggregate;
    getKindStatic(__input: ColumnViewSummaryData): ColumnViewSummaryKind;
    getKind(): ColumnViewSummaryKind;
    sub_variant_get_name(): Char;
    sub_variant_get_data(): ColumnViewSummaryData;
    sub_variant_get_kind(): ColumnViewSummaryKind;
    data: ColumnViewSummaryData
  }
  export interface ColumnViewSummaryCheckboxAggregateConstructor { new(): ColumnViewSummaryCheckboxAggregate; }
  export interface ColumnViewSummaryCheckboxAggregate {
    __eq__(other: ColumnViewSummaryCheckboxAggregate): boolean;
    kind: ColumnViewSummaryCheckboxAggregateKind
  }
  export enum OrgSemColumnViewSummaryCheckboxAggregateKind {
    IfAllNested,
    AggregateFractionRec,
    AggregatePercentRec,
  }
  export interface ColumnViewSummaryMathAggregateConstructor { new(): ColumnViewSummaryMathAggregate; }
  export interface ColumnViewSummaryMathAggregate {
    __eq__(other: ColumnViewSummaryMathAggregate): boolean;
    kind: ColumnViewSummaryMathAggregateKind
    formatDigits: haxorg_wasm.Optional<number>
    formatPrecision: haxorg_wasm.Optional<number>
  }
  export enum OrgSemColumnViewSummaryMathAggregateKind {
    Min,
    Max,
    Mean,
    Sum,
    LowHighEst,
  }
  export enum OrgSemColumnViewSummaryKind {
    CheckboxAggregate,
    MathAggregate,
  }
  export interface ColumnViewColumnConstructor { new(): ColumnViewColumn; }
  export interface ColumnViewColumn {
    __eq__(other: ColumnViewColumn): boolean;
    summary: haxorg_wasm.Optional<ColumnViewSummary>
    width: haxorg_wasm.Optional<number>
    property: haxorg_wasm.Optional<string>
    propertyTitle: haxorg_wasm.Optional<string>
  }
  export interface BlockCodeLineConstructor { new(): BlockCodeLine; }
  export interface BlockCodeLine {
    __eq__(other: BlockCodeLine): boolean;
    parts: Vec<BlockCodeLinePart>
  }
  export interface BlockCodeLinePartConstructor { new(): BlockCodeLinePart; }
  export interface BlockCodeLinePart {
    __eq__(other: BlockCodeLinePart): boolean;
    isRaw(): boolean;
    getRawConst(): BlockCodeLinePartRaw;
    getRawMut(): BlockCodeLinePartRaw;
    isCallout(): boolean;
    getCalloutConst(): BlockCodeLinePartCallout;
    getCalloutMut(): BlockCodeLinePartCallout;
    isTangle(): boolean;
    getTangleConst(): BlockCodeLinePartTangle;
    getTangleMut(): BlockCodeLinePartTangle;
    getKindStatic(__input: BlockCodeLinePartData): BlockCodeLinePartKind;
    getKind(): BlockCodeLinePartKind;
    sub_variant_get_name(): Char;
    sub_variant_get_data(): BlockCodeLinePartData;
    sub_variant_get_kind(): BlockCodeLinePartKind;
    data: BlockCodeLinePartData
  }
  export interface BlockCodeLinePartRawConstructor { new(): BlockCodeLinePartRaw; }
  export interface BlockCodeLinePartRaw {
    __eq__(other: BlockCodeLinePartRaw): boolean;
    code: string
  }
  export interface BlockCodeLinePartCalloutConstructor { new(): BlockCodeLinePartCallout; }
  export interface BlockCodeLinePartCallout {
    __eq__(other: BlockCodeLinePartCallout): boolean;
    name: string
  }
  export interface BlockCodeLinePartTangleConstructor { new(): BlockCodeLinePartTangle; }
  export interface BlockCodeLinePartTangle {
    __eq__(other: BlockCodeLinePartTangle): boolean;
    target: string
  }
  export enum OrgSemBlockCodeLinePartKind {
    Raw,
    Callout,
    Tangle,
  }
  export interface DocumentExportConfigConstructor { new(): DocumentExportConfig; }
  export interface DocumentExportConfig {
    __eq__(other: DocumentExportConfig): boolean;
    isDoExport(): boolean;
    getDoExportConst(): DocumentExportConfigDoExport;
    getDoExportMut(): DocumentExportConfigDoExport;
    isExportFixed(): boolean;
    getExportFixedConst(): DocumentExportConfigExportFixed;
    getExportFixedMut(): DocumentExportConfigExportFixed;
    getTocExportKindStatic(__input: DocumentExportConfigTocExport): DocumentExportConfigTocExportKind;
    getTocExportKind(): DocumentExportConfigTocExportKind;
    sub_variant_get_name(): Char;
    sub_variant_get_data(): DocumentExportConfigTocExport;
    sub_variant_get_kind(): DocumentExportConfigTocExportKind;
    inlinetasks: haxorg_wasm.Optional<boolean>
    footnotes: haxorg_wasm.Optional<boolean>
    clock: haxorg_wasm.Optional<boolean>
    author: haxorg_wasm.Optional<boolean>
    emphasis: haxorg_wasm.Optional<boolean>
    specialStrings: haxorg_wasm.Optional<boolean>
    propertyDrawers: haxorg_wasm.Optional<boolean>
    statisticsCookies: haxorg_wasm.Optional<boolean>
    todoText: haxorg_wasm.Optional<boolean>
    brokenLinks: DocumentExportConfigBrokenLinks
    tocExport: DocumentExportConfigTocExport
    tagExport: DocumentExportConfigTagExport
    data: DocumentExportConfigTocExport
  }
  export interface DocumentExportConfigTaskExportConstructor { new(): DocumentExportConfigTaskExport; }
  export interface DocumentExportConfigTaskExport {
    __eq__(other: DocumentExportConfigTaskExport): boolean;
    taskWhitelist: Vec<string>
  }
  export enum OrgSemDocumentExportConfigTagExport {
    None,
    All,
    NotInToc,
  }
  export enum OrgSemDocumentExportConfigTaskFiltering {
    Whitelist,
    Done,
    None,
    All,
  }
  export enum OrgSemDocumentExportConfigBrokenLinks {
    None,
    Mark,
    Raise,
    Ignore,
  }
  export interface DocumentExportConfigDoExportConstructor { new(): DocumentExportConfigDoExport; }
  export interface DocumentExportConfigDoExport {
    __eq__(other: DocumentExportConfigDoExport): boolean;
    exportToc: boolean
  }
  export interface DocumentExportConfigExportFixedConstructor { new(): DocumentExportConfigExportFixed; }
  export interface DocumentExportConfigExportFixed {
    __eq__(other: DocumentExportConfigExportFixed): boolean;
    exportLevels: number
  }
  export enum OrgSemDocumentExportConfigTocExportKind {
    DoExport,
    ExportFixed,
  }
  export interface SubtreePeriodConstructor { new(): SubtreePeriod; }
  export interface SubtreePeriod {
    __eq__(other: SubtreePeriod): boolean;
    kind: SubtreePeriodKind
    from: UserTime
    to: haxorg_wasm.Optional<UserTime>
  }
  export enum OrgSemSubtreePeriodKind {
    Clocked,
    Closed,
    Scheduled,
    Titled,
    Deadline,
    Created,
    Repeated,
  }
  export interface NamedPropertyConstructor { new(): NamedProperty; }
  export interface NamedProperty {
    isMatching(kind: string, subKind: haxorg_wasm.Optional<string>): boolean;
    getName(): string;
    getSubKind(): haxorg_wasm.Optional<string>;
    __eq__(other: NamedProperty): boolean;
    isNonblocking(): boolean;
    getNonblockingConst(): NamedPropertyNonblocking;
    getNonblockingMut(): NamedPropertyNonblocking;
    isArchiveTime(): boolean;
    getArchiveTimeConst(): NamedPropertyArchiveTime;
    getArchiveTimeMut(): NamedPropertyArchiveTime;
    isArchiveFile(): boolean;
    getArchiveFileConst(): NamedPropertyArchiveFile;
    getArchiveFileMut(): NamedPropertyArchiveFile;
    isArchiveOlpath(): boolean;
    getArchiveOlpathConst(): NamedPropertyArchiveOlpath;
    getArchiveOlpathMut(): NamedPropertyArchiveOlpath;
    isArchiveTarget(): boolean;
    getArchiveTargetConst(): NamedPropertyArchiveTarget;
    getArchiveTargetMut(): NamedPropertyArchiveTarget;
    isArchiveCategory(): boolean;
    getArchiveCategoryConst(): NamedPropertyArchiveCategory;
    getArchiveCategoryMut(): NamedPropertyArchiveCategory;
    isArchiveTodo(): boolean;
    getArchiveTodoConst(): NamedPropertyArchiveTodo;
    getArchiveTodoMut(): NamedPropertyArchiveTodo;
    isTrigger(): boolean;
    getTriggerConst(): NamedPropertyTrigger;
    getTriggerMut(): NamedPropertyTrigger;
    isExportLatexClass(): boolean;
    getExportLatexClassConst(): NamedPropertyExportLatexClass;
    getExportLatexClassMut(): NamedPropertyExportLatexClass;
    isCookieData(): boolean;
    getCookieDataConst(): NamedPropertyCookieData;
    getCookieDataMut(): NamedPropertyCookieData;
    isExportLatexClassOptions(): boolean;
    getExportLatexClassOptionsConst(): NamedPropertyExportLatexClassOptions;
    getExportLatexClassOptionsMut(): NamedPropertyExportLatexClassOptions;
    isExportLatexHeader(): boolean;
    getExportLatexHeaderConst(): NamedPropertyExportLatexHeader;
    getExportLatexHeaderMut(): NamedPropertyExportLatexHeader;
    isExportLatexCompiler(): boolean;
    getExportLatexCompilerConst(): NamedPropertyExportLatexCompiler;
    getExportLatexCompilerMut(): NamedPropertyExportLatexCompiler;
    isOrdered(): boolean;
    getOrderedConst(): NamedPropertyOrdered;
    getOrderedMut(): NamedPropertyOrdered;
    isEffort(): boolean;
    getEffortConst(): NamedPropertyEffort;
    getEffortMut(): NamedPropertyEffort;
    isVisibility(): boolean;
    getVisibilityConst(): NamedPropertyVisibility;
    getVisibilityMut(): NamedPropertyVisibility;
    isExportOptions(): boolean;
    getExportOptionsConst(): NamedPropertyExportOptions;
    getExportOptionsMut(): NamedPropertyExportOptions;
    isBlocker(): boolean;
    getBlockerConst(): NamedPropertyBlocker;
    getBlockerMut(): NamedPropertyBlocker;
    isUnnumbered(): boolean;
    getUnnumberedConst(): NamedPropertyUnnumbered;
    getUnnumberedMut(): NamedPropertyUnnumbered;
    isCreated(): boolean;
    getCreatedConst(): NamedPropertyCreated;
    getCreatedMut(): NamedPropertyCreated;
    isRadioId(): boolean;
    getRadioIdConst(): NamedPropertyRadioId;
    getRadioIdMut(): NamedPropertyRadioId;
    isHashtagDef(): boolean;
    getHashtagDefConst(): NamedPropertyHashtagDef;
    getHashtagDefMut(): NamedPropertyHashtagDef;
    isCustomArgs(): boolean;
    getCustomArgsConst(): NamedPropertyCustomArgs;
    getCustomArgsMut(): NamedPropertyCustomArgs;
    isCustomRaw(): boolean;
    getCustomRawConst(): NamedPropertyCustomRaw;
    getCustomRawMut(): NamedPropertyCustomRaw;
    isCustomSubtreeJson(): boolean;
    getCustomSubtreeJsonConst(): NamedPropertyCustomSubtreeJson;
    getCustomSubtreeJsonMut(): NamedPropertyCustomSubtreeJson;
    isCustomSubtreeFlags(): boolean;
    getCustomSubtreeFlagsConst(): NamedPropertyCustomSubtreeFlags;
    getCustomSubtreeFlagsMut(): NamedPropertyCustomSubtreeFlags;
    getKindStatic(__input: NamedPropertyData): NamedPropertyKind;
    getKind(): NamedPropertyKind;
    sub_variant_get_name(): Char;
    sub_variant_get_data(): NamedPropertyData;
    sub_variant_get_kind(): NamedPropertyKind;
    data: NamedPropertyData
  }
  export interface NamedPropertyNonblockingConstructor { new(): NamedPropertyNonblocking; }
  export interface NamedPropertyNonblocking {
    __eq__(other: NamedPropertyNonblocking): boolean;
    isBlocking: boolean
  }
  export interface NamedPropertyArchiveTimeConstructor { new(): NamedPropertyArchiveTime; }
  export interface NamedPropertyArchiveTime {
    __eq__(other: NamedPropertyArchiveTime): boolean;
    time: UserTime
  }
  export interface NamedPropertyArchiveFileConstructor { new(): NamedPropertyArchiveFile; }
  export interface NamedPropertyArchiveFile {
    __eq__(other: NamedPropertyArchiveFile): boolean;
    file: string
  }
  export interface NamedPropertyArchiveOlpathConstructor { new(): NamedPropertyArchiveOlpath; }
  export interface NamedPropertyArchiveOlpath {
    __eq__(other: NamedPropertyArchiveOlpath): boolean;
    path: SubtreePath
  }
  export interface NamedPropertyArchiveTargetConstructor { new(): NamedPropertyArchiveTarget; }
  export interface NamedPropertyArchiveTarget {
    __eq__(other: NamedPropertyArchiveTarget): boolean;
    path: SubtreePath
    pattern: string
  }
  export interface NamedPropertyArchiveCategoryConstructor { new(): NamedPropertyArchiveCategory; }
  export interface NamedPropertyArchiveCategory {
    __eq__(other: NamedPropertyArchiveCategory): boolean;
    category: string
  }
  export interface NamedPropertyArchiveTodoConstructor { new(): NamedPropertyArchiveTodo; }
  export interface NamedPropertyArchiveTodo {
    __eq__(other: NamedPropertyArchiveTodo): boolean;
    todo: string
  }
  export interface NamedPropertyTriggerConstructor { new(): NamedPropertyTrigger; }
  export interface NamedPropertyTrigger { __eq__(other: NamedPropertyTrigger): boolean; }
  export interface NamedPropertyExportLatexClassConstructor { new(): NamedPropertyExportLatexClass; }
  export interface NamedPropertyExportLatexClass {
    __eq__(other: NamedPropertyExportLatexClass): boolean;
    latexClass: string
  }
  export interface NamedPropertyCookieDataConstructor { new(): NamedPropertyCookieData; }
  export interface NamedPropertyCookieData {
    __eq__(other: NamedPropertyCookieData): boolean;
    isRecursive: boolean
    source: SubtreeTodoSource
  }
  export interface NamedPropertyExportLatexClassOptionsConstructor { new(): NamedPropertyExportLatexClassOptions; }
  export interface NamedPropertyExportLatexClassOptions {
    __eq__(other: NamedPropertyExportLatexClassOptions): boolean;
    options: Vec<string>
  }
  export interface NamedPropertyExportLatexHeaderConstructor { new(): NamedPropertyExportLatexHeader; }
  export interface NamedPropertyExportLatexHeader {
    __eq__(other: NamedPropertyExportLatexHeader): boolean;
    header: string
  }
  export interface NamedPropertyExportLatexCompilerConstructor { new(): NamedPropertyExportLatexCompiler; }
  export interface NamedPropertyExportLatexCompiler {
    __eq__(other: NamedPropertyExportLatexCompiler): boolean;
    compiler: string
  }
  export interface NamedPropertyOrderedConstructor { new(): NamedPropertyOrdered; }
  export interface NamedPropertyOrdered {
    __eq__(other: NamedPropertyOrdered): boolean;
    isOrdered: boolean
  }
  export interface NamedPropertyEffortConstructor { new(): NamedPropertyEffort; }
  export interface NamedPropertyEffort {
    __eq__(other: NamedPropertyEffort): boolean;
    hours: number
    minutes: number
  }
  export interface NamedPropertyVisibilityConstructor { new(): NamedPropertyVisibility; }
  export interface NamedPropertyVisibility {
    __eq__(other: NamedPropertyVisibility): boolean;
    level: NamedPropertyVisibilityLevel
  }
  export enum OrgSemNamedPropertyVisibilityLevel {
    Folded,
    Children,
    Content,
    All,
  }
  export interface NamedPropertyExportOptionsConstructor { new(): NamedPropertyExportOptions; }
  export interface NamedPropertyExportOptions {
    __eq__(other: NamedPropertyExportOptions): boolean;
    backend: string
    values: UnorderedMap<string, string>
  }
  export interface NamedPropertyBlockerConstructor { new(): NamedPropertyBlocker; }
  export interface NamedPropertyBlocker {
    __eq__(other: NamedPropertyBlocker): boolean;
    blockers: Vec<string>
  }
  export interface NamedPropertyUnnumberedConstructor { new(): NamedPropertyUnnumbered; }
  export interface NamedPropertyUnnumbered { __eq__(other: NamedPropertyUnnumbered): boolean; }
  export interface NamedPropertyCreatedConstructor { new(): NamedPropertyCreated; }
  export interface NamedPropertyCreated {
    __eq__(other: NamedPropertyCreated): boolean;
    time: UserTime
  }
  export interface NamedPropertyRadioIdConstructor { new(): NamedPropertyRadioId; }
  export interface NamedPropertyRadioId {
    __eq__(other: NamedPropertyRadioId): boolean;
    words: Vec<string>
  }
  export interface NamedPropertyHashtagDefConstructor { new(): NamedPropertyHashtagDef; }
  export interface NamedPropertyHashtagDef {
    __eq__(other: NamedPropertyHashtagDef): boolean;
    hashtag: HashTagText
  }
  export interface NamedPropertyCustomArgsConstructor { new(): NamedPropertyCustomArgs; }
  export interface NamedPropertyCustomArgs {
    __eq__(other: NamedPropertyCustomArgs): boolean;
    name: string
    sub: haxorg_wasm.Optional<string>
    attrs: AttrGroup
  }
  export interface NamedPropertyCustomRawConstructor { new(): NamedPropertyCustomRaw; }
  export interface NamedPropertyCustomRaw {
    __eq__(other: NamedPropertyCustomRaw): boolean;
    name: string
    value: string
  }
  export interface NamedPropertyCustomSubtreeJsonConstructor { new(): NamedPropertyCustomSubtreeJson; }
  export interface NamedPropertyCustomSubtreeJson {
    __eq__(other: NamedPropertyCustomSubtreeJson): boolean;
    name: string
    value: OrgJson
  }
  export interface NamedPropertyCustomSubtreeFlagsConstructor { new(): NamedPropertyCustomSubtreeFlags; }
  export interface NamedPropertyCustomSubtreeFlags {
    __eq__(other: NamedPropertyCustomSubtreeFlags): boolean;
    name: string
    value: AttrGroup
  }
  export enum OrgSemNamedPropertyKind {
    Nonblocking,
    ArchiveTime,
    ArchiveFile,
    ArchiveOlpath,
    ArchiveTarget,
    ArchiveCategory,
    ArchiveTodo,
    Trigger,
    ExportLatexClass,
    CookieData,
    ExportLatexClassOptions,
    ExportLatexHeader,
    ExportLatexCompiler,
    Ordered,
    Effort,
    Visibility,
    ExportOptions,
    Blocker,
    Unnumbered,
    Created,
    RadioId,
    HashtagDef,
    CustomArgs,
    CustomRaw,
    CustomSubtreeJson,
    CustomSubtreeFlags,
  }
  export interface ImmNoneConstructor { new(): ImmNone; }
  export interface ImmNone {
    getKind(): OrgSemKind;
    __eq__(other: ImmNone): boolean;
  }
  export interface ImmErrorItemConstructor { new(): ImmErrorItem; }
  export interface ImmErrorItem {
    getKind(): OrgSemKind;
    __eq__(other: ImmErrorItem): boolean;
    message: ImmBox<string>
    function: ImmBox<haxorg_wasm.Optional<string>>
    line: ImmBox<haxorg_wasm.Optional<number>>
  }
  export interface ImmErrorGroupConstructor { new(): ImmErrorGroup; }
  export interface ImmErrorGroup {
    getKind(): OrgSemKind;
    __eq__(other: ImmErrorGroup): boolean;
    diagnostics: ImmVec<ImmIdT<ImmErrorItem>>
    function: ImmBox<haxorg_wasm.Optional<string>>
    line: ImmBox<haxorg_wasm.Optional<number>>
  }
  export interface ImmStmtConstructor { new(): ImmStmt; }
  export interface ImmStmt {
    __eq__(other: ImmStmt): boolean;
    attached: ImmVec<ImmIdT<ImmOrg>>
  }
  export interface ImmInlineConstructor { new(): ImmInline; }
  export interface ImmInline { __eq__(other: ImmInline): boolean; }
  export interface ImmStmtListConstructor { new(): ImmStmtList; }
  export interface ImmStmtList {
    getKind(): OrgSemKind;
    __eq__(other: ImmStmtList): boolean;
  }
  export interface ImmEmptyConstructor { new(): ImmEmpty; }
  export interface ImmEmpty {
    getKind(): OrgSemKind;
    __eq__(other: ImmEmpty): boolean;
  }
  export interface ImmLeafConstructor { new(): ImmLeaf; }
  export interface ImmLeaf {
    __eq__(other: ImmLeaf): boolean;
    text: ImmBox<string>
  }
  export interface ImmTimeConstructor { new(): ImmTime; }
  export interface ImmTime {
    getKind(): OrgSemKind;
    __eq__(other: ImmTime): boolean;
    isStatic(): boolean;
    getStaticConst(): ImmTimeStatic;
    getStaticMut(): ImmTimeStatic;
    isDynamic(): boolean;
    getDynamicConst(): ImmTimeDynamic;
    getDynamicMut(): ImmTimeDynamic;
    getTimeKindStatic(__input: ImmTimeTimeVariant): ImmTimeTimeKind;
    getTimeKind(): ImmTimeTimeKind;
    sub_variant_get_name(): Char;
    sub_variant_get_data(): ImmTimeTimeVariant;
    sub_variant_get_kind(): ImmTimeTimeKind;
    isActive: boolean
    time: ImmTimeTimeVariant
  }
  export interface ImmTimeRepeatConstructor { new(): ImmTimeRepeat; }
  export interface ImmTimeRepeat {
    Repeat(): void;
    __eq__(other: ImmTimeRepeat): boolean;
    mode: ImmTimeRepeatMode
    period: ImmTimeRepeatPeriod
    count: number
  }
  export enum OrgImmImmTimeRepeatMode {
    None,
    Exact,
    FirstMatch,
    SameDay,
  }
  export enum OrgImmImmTimeRepeatPeriod {
    Year,
    Month,
    Week,
    Day,
    Hour,
    Minute,
  }
  export interface ImmTimeStaticConstructor { new(): ImmTimeStatic; }
  export interface ImmTimeStatic {
    Static(): void;
    __eq__(other: ImmTimeStatic): boolean;
    repeat: ImmVec<ImmTimeRepeat>
    warn: ImmBox<haxorg_wasm.Optional<ImmTimeRepeat>>
    time: UserTime
  }
  export interface ImmTimeDynamicConstructor { new(): ImmTimeDynamic; }
  export interface ImmTimeDynamic {
    Dynamic(): void;
    __eq__(other: ImmTimeDynamic): boolean;
    expr: ImmBox<string>
  }
  export enum OrgImmImmTimeTimeKind {
    Static,
    Dynamic,
  }
  export interface ImmTimeRangeConstructor { new(): ImmTimeRange; }
  export interface ImmTimeRange {
    getKind(): OrgSemKind;
    __eq__(other: ImmTimeRange): boolean;
    from: ImmIdT<ImmTime>
    to: ImmIdT<ImmTime>
  }
  export interface ImmMacroConstructor { new(): ImmMacro; }
  export interface ImmMacro {
    getKind(): OrgSemKind;
    __eq__(other: ImmMacro): boolean;
    name: ImmBox<string>
    attrs: AttrGroup
  }
  export interface ImmSymbolConstructor { new(): ImmSymbol; }
  export interface ImmSymbol {
    getKind(): OrgSemKind;
    __eq__(other: ImmSymbol): boolean;
    name: ImmBox<string>
    parameters: ImmVec<ImmSymbolParam>
    positional: ImmVec<ImmIdT<ImmOrg>>
  }
  export interface ImmSymbolParamConstructor { new(): ImmSymbolParam; }
  export interface ImmSymbolParam {
    __eq__(other: ImmSymbolParam): boolean;
    key: ImmBox<haxorg_wasm.Optional<string>>
    value: ImmBox<string>
  }
  export interface ImmMarkupConstructor { new(): ImmMarkup; }
  export interface ImmMarkup { __eq__(other: ImmMarkup): boolean; }
  export interface ImmRadioTargetConstructor { new(): ImmRadioTarget; }
  export interface ImmRadioTarget {
    getKind(): OrgSemKind;
    __eq__(other: ImmRadioTarget): boolean;
    words: ImmVec<string>
  }
  export interface ImmLatexConstructor { new(): ImmLatex; }
  export interface ImmLatex {
    getKind(): OrgSemKind;
    __eq__(other: ImmLatex): boolean;
  }
  export interface ImmSubtreeLogConstructor { new(): ImmSubtreeLog; }
  export interface ImmSubtreeLog {
    getKind(): OrgSemKind;
    __eq__(other: ImmSubtreeLog): boolean;
    head: SubtreeLogHead
    desc: ImmBox<haxorg_wasm.Optional<ImmIdT<ImmStmtList>>>
  }
  export interface ImmSubtreeConstructor { new(): ImmSubtree; }
  export interface ImmSubtree {
    getKind(): OrgSemKind;
    __eq__(other: ImmSubtree): boolean;
    level: number
    treeId: ImmBox<haxorg_wasm.Optional<string>>
    todo: ImmBox<haxorg_wasm.Optional<string>>
    completion: ImmBox<haxorg_wasm.Optional<SubtreeCompletion>>
    description: ImmBox<haxorg_wasm.Optional<ImmIdT<ImmParagraph>>>
    tags: ImmVec<ImmIdT<ImmHashTag>>
    title: ImmIdT<ImmParagraph>
    logbook: ImmVec<ImmIdT<ImmSubtreeLog>>
    properties: ImmVec<NamedProperty>
    closed: ImmBox<haxorg_wasm.Optional<UserTime>>
    deadline: ImmBox<haxorg_wasm.Optional<UserTime>>
    scheduled: ImmBox<haxorg_wasm.Optional<UserTime>>
    isComment: boolean
    isArchived: boolean
    priority: ImmBox<haxorg_wasm.Optional<string>>
  }
  export interface ImmColonExampleConstructor { new(): ImmColonExample; }
  export interface ImmColonExample {
    getKind(): OrgSemKind;
    __eq__(other: ImmColonExample): boolean;
  }
  export interface ImmCallConstructor { new(): ImmCall; }
  export interface ImmCall {
    getKind(): OrgSemKind;
    __eq__(other: ImmCall): boolean;
    name: ImmBox<string>
    attrs: AttrGroup
    isCommand: boolean
  }
  export interface ImmListItemConstructor { new(): ImmListItem; }
  export interface ImmListItem {
    getKind(): OrgSemKind;
    __eq__(other: ImmListItem): boolean;
    checkbox: CheckboxState
    header: ImmBox<haxorg_wasm.Optional<ImmIdT<ImmParagraph>>>
    bullet: ImmBox<haxorg_wasm.Optional<string>>
  }
  export interface ImmDocumentOptionsConstructor { new(): ImmDocumentOptions; }
  export interface ImmDocumentOptions {
    getKind(): OrgSemKind;
    __eq__(other: ImmDocumentOptions): boolean;
    initialVisibility: InitialSubtreeVisibility
    properties: ImmVec<NamedProperty>
    exportConfig: DocumentExportConfig
    fixedWidthSections: ImmBox<haxorg_wasm.Optional<boolean>>
    startupIndented: ImmBox<haxorg_wasm.Optional<boolean>>
    category: ImmBox<haxorg_wasm.Optional<string>>
    setupfile: ImmBox<haxorg_wasm.Optional<string>>
    maxSubtreeLevelExport: ImmBox<haxorg_wasm.Optional<number>>
    columns: ImmBox<haxorg_wasm.Optional<ColumnView>>
    todoKeywords: ImmVec<TodoKeyword>
    doneKeywords: ImmVec<TodoKeyword>
  }
  export interface ImmDocumentFragmentConstructor { new(): ImmDocumentFragment; }
  export interface ImmDocumentFragment {
    getKind(): OrgSemKind;
    __eq__(other: ImmDocumentFragment): boolean;
    baseLine: number
    baseCol: number
  }
  export interface ImmCriticMarkupConstructor { new(): ImmCriticMarkup; }
  export interface ImmCriticMarkup {
    getKind(): OrgSemKind;
    __eq__(other: ImmCriticMarkup): boolean;
    kind: ImmCriticMarkupKind
  }
  export enum OrgImmImmCriticMarkupKind {
    Deletion,
    Addition,
    Substitution,
    Highlighting,
    Comment,
  }
  export interface ImmDocumentConstructor { new(): ImmDocument; }
  export interface ImmDocument {
    getKind(): OrgSemKind;
    __eq__(other: ImmDocument): boolean;
    title: ImmBox<haxorg_wasm.Optional<ImmIdT<ImmParagraph>>>
    author: ImmBox<haxorg_wasm.Optional<ImmIdT<ImmParagraph>>>
    creator: ImmBox<haxorg_wasm.Optional<ImmIdT<ImmParagraph>>>
    filetags: ImmVec<ImmIdT<ImmHashTag>>
    email: ImmBox<haxorg_wasm.Optional<ImmIdT<ImmRawText>>>
    language: ImmVec<string>
    options: ImmIdT<ImmDocumentOptions>
    exportFileName: ImmBox<haxorg_wasm.Optional<string>>
  }
  export interface ImmFileTargetConstructor { new(): ImmFileTarget; }
  export interface ImmFileTarget {
    getKind(): OrgSemKind;
    __eq__(other: ImmFileTarget): boolean;
    path: ImmBox<string>
    line: ImmBox<haxorg_wasm.Optional<number>>
    searchTarget: ImmBox<haxorg_wasm.Optional<string>>
    restrictToHeadlines: boolean
    targetId: ImmBox<haxorg_wasm.Optional<string>>
    regexp: ImmBox<haxorg_wasm.Optional<string>>
  }
  export interface ImmTextSeparatorConstructor { new(): ImmTextSeparator; }
  export interface ImmTextSeparator {
    getKind(): OrgSemKind;
    __eq__(other: ImmTextSeparator): boolean;
  }
  export interface ImmDocumentGroupConstructor { new(): ImmDocumentGroup; }
  export interface ImmDocumentGroup {
    getKind(): OrgSemKind;
    __eq__(other: ImmDocumentGroup): boolean;
  }
  export interface ImmFileConstructor { new(): ImmFile; }
  export interface ImmFile {
    getKind(): OrgSemKind;
    __eq__(other: ImmFile): boolean;
    isDocument(): boolean;
    getDocumentConst(): ImmFileDocument;
    getDocumentMut(): ImmFileDocument;
    isAttachment(): boolean;
    getAttachmentConst(): ImmFileAttachment;
    getAttachmentMut(): ImmFileAttachment;
    isSource(): boolean;
    getSourceConst(): ImmFileSource;
    getSourceMut(): ImmFileSource;
    getFileKindStatic(__input: ImmFileData): ImmFileKind;
    getFileKind(): ImmFileKind;
    sub_variant_get_name(): Char;
    sub_variant_get_data(): ImmFileData;
    sub_variant_get_kind(): ImmFileKind;
    relPath: ImmBox<string>
    absPath: ImmBox<string>
    data: ImmFileData
  }
  export interface ImmFileDocumentConstructor { new(): ImmFileDocument; }
  export interface ImmFileDocument { __eq__(other: ImmFileDocument): boolean; }
  export interface ImmFileAttachmentConstructor { new(): ImmFileAttachment; }
  export interface ImmFileAttachment { __eq__(other: ImmFileAttachment): boolean; }
  export interface ImmFileSourceConstructor { new(): ImmFileSource; }
  export interface ImmFileSource { __eq__(other: ImmFileSource): boolean; }
  export enum OrgImmImmFileKind {
    Document,
    Attachment,
    Source,
  }
  export interface ImmDirectoryConstructor { new(): ImmDirectory; }
  export interface ImmDirectory {
    getKind(): OrgSemKind;
    __eq__(other: ImmDirectory): boolean;
    relPath: ImmBox<string>
    absPath: ImmBox<string>
  }
  export interface ImmSymlinkConstructor { new(): ImmSymlink; }
  export interface ImmSymlink {
    getKind(): OrgSemKind;
    __eq__(other: ImmSymlink): boolean;
    isDirectory: boolean
    absPath: ImmBox<string>
  }
  export interface ImmCmdIncludeConstructor { new(): ImmCmdInclude; }
  export interface ImmCmdInclude {
    getKind(): OrgSemKind;
    __eq__(other: ImmCmdInclude): boolean;
    isExample(): boolean;
    getExampleConst(): ImmCmdIncludeExample;
    getExampleMut(): ImmCmdIncludeExample;
    isExport(): boolean;
    getExportConst(): ImmCmdIncludeExport;
    getExportMut(): ImmCmdIncludeExport;
    isCustom(): boolean;
    getCustomConst(): ImmCmdIncludeCustom;
    getCustomMut(): ImmCmdIncludeCustom;
    isSrc(): boolean;
    getSrcConst(): ImmCmdIncludeSrc;
    getSrcMut(): ImmCmdIncludeSrc;
    isOrgDocument(): boolean;
    getOrgDocumentConst(): ImmCmdIncludeOrgDocument;
    getOrgDocumentMut(): ImmCmdIncludeOrgDocument;
    getIncludeKindStatic(__input: ImmCmdIncludeData): ImmCmdIncludeKind;
    getIncludeKind(): ImmCmdIncludeKind;
    sub_variant_get_name(): Char;
    sub_variant_get_data(): ImmCmdIncludeData;
    sub_variant_get_kind(): ImmCmdIncludeKind;
    path: ImmBox<string>
    firstLine: ImmBox<haxorg_wasm.Optional<number>>
    lastLine: ImmBox<haxorg_wasm.Optional<number>>
    data: ImmCmdIncludeData
  }
  export interface ImmCmdIncludeIncludeBaseConstructor { new(): ImmCmdIncludeIncludeBase; }
  export interface ImmCmdIncludeIncludeBase {
    IncludeBase(): void;
    __eq__(other: ImmCmdIncludeIncludeBase): boolean;
  }
  export interface ImmCmdIncludeExampleConstructor { new(): ImmCmdIncludeExample; }
  export interface ImmCmdIncludeExample {
    Example(): void;
    __eq__(other: ImmCmdIncludeExample): boolean;
  }
  export interface ImmCmdIncludeExportConstructor { new(): ImmCmdIncludeExport; }
  export interface ImmCmdIncludeExport {
    Export(): void;
    __eq__(other: ImmCmdIncludeExport): boolean;
    language: ImmBox<string>
  }
  export interface ImmCmdIncludeCustomConstructor { new(): ImmCmdIncludeCustom; }
  export interface ImmCmdIncludeCustom {
    Custom(): void;
    __eq__(other: ImmCmdIncludeCustom): boolean;
    blockName: ImmBox<string>
  }
  export interface ImmCmdIncludeSrcConstructor { new(): ImmCmdIncludeSrc; }
  export interface ImmCmdIncludeSrc {
    Src(): void;
    __eq__(other: ImmCmdIncludeSrc): boolean;
    language: ImmBox<string>
  }
  export interface ImmCmdIncludeOrgDocumentConstructor { new(): ImmCmdIncludeOrgDocument; }
  export interface ImmCmdIncludeOrgDocument {
    OrgDocument(): void;
    __eq__(other: ImmCmdIncludeOrgDocument): boolean;
    onlyContent: ImmBox<haxorg_wasm.Optional<boolean>>
    subtreePath: ImmBox<haxorg_wasm.Optional<SubtreePath>>
    minLevel: ImmBox<haxorg_wasm.Optional<number>>
    customIdTarget: ImmBox<haxorg_wasm.Optional<string>>
  }
  export enum OrgImmImmCmdIncludeKind {
    Example,
    Export,
    Custom,
    Src,
    OrgDocument,
  }
  export interface GraphMapConfigConstructor { new(): GraphMapConfig; }
  export interface GraphMapConfig {  }
  export interface NoneConstructor { new(): None; }
  export interface None { getKind(): OrgSemKind; }
  export interface ErrorItemConstructor { new(): ErrorItem; }
  export interface ErrorItem {
    getKind(): OrgSemKind;
    message: string
    function: haxorg_wasm.Optional<string>
    line: haxorg_wasm.Optional<number>
  }
  export interface ErrorGroupConstructor { new(): ErrorGroup; }
  export interface ErrorGroup {
    getKind(): OrgSemKind;
    diagnostics: Vec<ErrorItem>
    function: haxorg_wasm.Optional<string>
    line: haxorg_wasm.Optional<number>
  }
  export interface StmtConstructor { new(): Stmt; }
  export interface Stmt {
    getAttached(kind: haxorg_wasm.Optional<string>): Vec<Org>;
    getCaption(): Vec<Org>;
    getName(): Vec<string>;
    getAttrs(kind: haxorg_wasm.Optional<string>): Vec<AttrValue>;
    getFirstAttr(kind: string): haxorg_wasm.Optional<AttrValue>;
    attached: Vec<Org>
  }
  export interface InlineConstructor { new(): Inline; }
  export interface Inline {  }
  export interface StmtListConstructor { new(): StmtList; }
  export interface StmtList { getKind(): OrgSemKind; }
  export interface EmptyConstructor { new(): Empty; }
  export interface Empty { getKind(): OrgSemKind; }
  export interface LeafConstructor { new(): Leaf; }
  export interface Leaf {
    getText(): string;
    text: string
  }
  export interface TimeConstructor { new(): Time; }
  export interface Time {
    getKind(): OrgSemKind;
    getYear(): haxorg_wasm.Optional<number>;
    getMonth(): haxorg_wasm.Optional<number>;
    getDay(): haxorg_wasm.Optional<number>;
    getHour(): haxorg_wasm.Optional<number>;
    getMinute(): haxorg_wasm.Optional<number>;
    getSecond(): haxorg_wasm.Optional<number>;
    getStaticTime(): UserTime;
    isStatic(): boolean;
    getStaticConst(): TimeStatic;
    getStaticMut(): TimeStatic;
    isDynamic(): boolean;
    getDynamicConst(): TimeDynamic;
    getDynamicMut(): TimeDynamic;
    getTimeKindStatic(__input: TimeTimeVariant): TimeTimeKind;
    getTimeKind(): TimeTimeKind;
    sub_variant_get_name(): Char;
    sub_variant_get_data(): TimeTimeVariant;
    sub_variant_get_kind(): TimeTimeKind;
    isActive: boolean
    time: TimeTimeVariant
  }
  export interface TimeRepeatConstructor { new(): TimeRepeat; }
  export interface TimeRepeat {
    Repeat(): void;
    mode: TimeRepeatMode
    period: TimeRepeatPeriod
    count: number
  }
  export enum OrgSemTimeRepeatMode {
    None,
    Exact,
    FirstMatch,
    SameDay,
  }
  export enum OrgSemTimeRepeatPeriod {
    Year,
    Month,
    Week,
    Day,
    Hour,
    Minute,
  }
  export interface TimeStaticConstructor { new(): TimeStatic; }
  export interface TimeStatic {
    Static(): void;
    repeat: Vec<TimeRepeat>
    warn: haxorg_wasm.Optional<TimeRepeat>
    time: UserTime
  }
  export interface TimeDynamicConstructor { new(): TimeDynamic; }
  export interface TimeDynamic {
    Dynamic(): void;
    expr: string
  }
  export enum OrgSemTimeTimeKind {
    Static,
    Dynamic,
  }
  export interface TimeRangeConstructor { new(): TimeRange; }
  export interface TimeRange {
    getKind(): OrgSemKind;
    from: Time
    to: Time
  }
  export interface MacroConstructor { new(): Macro; }
  export interface Macro {
    getKind(): OrgSemKind;
    name: string
    attrs: AttrGroup
  }
  export interface SymbolConstructor { new(): Symbol; }
  export interface Symbol {
    getKind(): OrgSemKind;
    name: string
    parameters: Vec<SymbolParam>
    positional: Vec<Org>
  }
  export interface SymbolParamConstructor { new(): SymbolParam; }
  export interface SymbolParam {
    key: haxorg_wasm.Optional<string>
    value: string
  }
  export interface MarkupConstructor { new(): Markup; }
  export interface Markup {  }
  export interface RadioTargetConstructor { new(): RadioTarget; }
  export interface RadioTarget {
    getKind(): OrgSemKind;
    words: Vec<string>
  }
  export interface LatexConstructor { new(): Latex; }
  export interface Latex { getKind(): OrgSemKind; }
  export interface SubtreeLogConstructor { new(): SubtreeLog; }
  export interface SubtreeLog {
    getKind(): OrgSemKind;
    setDescription(desc: StmtList): void;
    head: SubtreeLogHead
    desc: haxorg_wasm.Optional<StmtList>
  }
  export interface SubtreeConstructor { new(): Subtree; }
  export interface Subtree {
    getKind(): OrgSemKind;
    getTimePeriods(kinds: IntSet<SubtreePeriodKind>): Vec<SubtreePeriod>;
    getProperties(kind: string, subkind: haxorg_wasm.Optional<string>): Vec<NamedProperty>;
    getProperty(kind: string, subkind: haxorg_wasm.Optional<string>): haxorg_wasm.Optional<NamedProperty>;
    removeProperty(kind: string, subkind: haxorg_wasm.Optional<string>): void;
    setProperty(value: NamedProperty): void;
    setPropertyStrValue(value: string, kind: string, subkind: haxorg_wasm.Optional<string>): void;
    getCleanTitle(): string;
    level: number
    treeId: haxorg_wasm.Optional<string>
    todo: haxorg_wasm.Optional<string>
    completion: haxorg_wasm.Optional<SubtreeCompletion>
    description: haxorg_wasm.Optional<Paragraph>
    tags: Vec<HashTag>
    title: Paragraph
    logbook: Vec<SubtreeLog>
    properties: Vec<NamedProperty>
    closed: haxorg_wasm.Optional<UserTime>
    deadline: haxorg_wasm.Optional<UserTime>
    scheduled: haxorg_wasm.Optional<UserTime>
    isComment: boolean
    isArchived: boolean
    priority: haxorg_wasm.Optional<string>
  }
  export interface ColonExampleConstructor { new(): ColonExample; }
  export interface ColonExample { getKind(): OrgSemKind; }
  export interface CallConstructor { new(): Call; }
  export interface Call {
    getKind(): OrgSemKind;
    name: string
    attrs: AttrGroup
    isCommand: boolean
  }
  export interface ListItemConstructor { new(): ListItem; }
  export interface ListItem {
    getKind(): OrgSemKind;
    isDescriptionItem(): boolean;
    getCleanHeader(): haxorg_wasm.Optional<string>;
    checkbox: CheckboxState
    header: haxorg_wasm.Optional<Paragraph>
    bullet: haxorg_wasm.Optional<string>
  }
  export interface DocumentOptionsConstructor { new(): DocumentOptions; }
  export interface DocumentOptions {
    getKind(): OrgSemKind;
    getProperties(kind: string, subKind: haxorg_wasm.Optional<string>): Vec<NamedProperty>;
    getProperty(kind: string, subKind: haxorg_wasm.Optional<string>): haxorg_wasm.Optional<NamedProperty>;
    initialVisibility: InitialSubtreeVisibility
    properties: Vec<NamedProperty>
    exportConfig: DocumentExportConfig
    fixedWidthSections: haxorg_wasm.Optional<boolean>
    startupIndented: haxorg_wasm.Optional<boolean>
    category: haxorg_wasm.Optional<string>
    setupfile: haxorg_wasm.Optional<string>
    maxSubtreeLevelExport: haxorg_wasm.Optional<number>
    columns: haxorg_wasm.Optional<ColumnView>
    todoKeywords: Vec<TodoKeyword>
    doneKeywords: Vec<TodoKeyword>
  }
  export interface DocumentFragmentConstructor { new(): DocumentFragment; }
  export interface DocumentFragment {
    getKind(): OrgSemKind;
    baseLine: number
    baseCol: number
  }
  export interface CriticMarkupConstructor { new(): CriticMarkup; }
  export interface CriticMarkup {
    getKind(): OrgSemKind;
    kind: CriticMarkupKind
  }
  export enum OrgSemCriticMarkupKind {
    Deletion,
    Addition,
    Substitution,
    Highlighting,
    Comment,
  }
  export interface DocumentConstructor { new(): Document; }
  export interface Document {
    getKind(): OrgSemKind;
    getProperties(kind: string, subKind: haxorg_wasm.Optional<string>): Vec<NamedProperty>;
    getProperty(kind: string, subKind: haxorg_wasm.Optional<string>): haxorg_wasm.Optional<NamedProperty>;
    title: haxorg_wasm.Optional<Paragraph>
    author: haxorg_wasm.Optional<Paragraph>
    creator: haxorg_wasm.Optional<Paragraph>
    filetags: Vec<HashTag>
    email: haxorg_wasm.Optional<RawText>
    language: Vec<string>
    options: DocumentOptions
    exportFileName: haxorg_wasm.Optional<string>
  }
  export interface FileTargetConstructor { new(): FileTarget; }
  export interface FileTarget {
    getKind(): OrgSemKind;
    path: string
    line: haxorg_wasm.Optional<number>
    searchTarget: haxorg_wasm.Optional<string>
    restrictToHeadlines: boolean
    targetId: haxorg_wasm.Optional<string>
    regexp: haxorg_wasm.Optional<string>
  }
  export interface TextSeparatorConstructor { new(): TextSeparator; }
  export interface TextSeparator { getKind(): OrgSemKind; }
  export interface DocumentGroupConstructor { new(): DocumentGroup; }
  export interface DocumentGroup { getKind(): OrgSemKind; }
  export interface FileConstructor { new(): File; }
  export interface File {
    getKind(): OrgSemKind;
    isDocument(): boolean;
    getDocumentConst(): FileDocument;
    getDocumentMut(): FileDocument;
    isAttachment(): boolean;
    getAttachmentConst(): FileAttachment;
    getAttachmentMut(): FileAttachment;
    isSource(): boolean;
    getSourceConst(): FileSource;
    getSourceMut(): FileSource;
    getFileKindStatic(__input: FileData): FileKind;
    getFileKind(): FileKind;
    sub_variant_get_name(): Char;
    sub_variant_get_data(): FileData;
    sub_variant_get_kind(): FileKind;
    relPath: string
    absPath: string
    data: FileData
  }
  export interface FileDocumentConstructor { new(): FileDocument; }
  export interface FileDocument {  }
  export interface FileAttachmentConstructor { new(): FileAttachment; }
  export interface FileAttachment {  }
  export interface FileSourceConstructor { new(): FileSource; }
  export interface FileSource {  }
  export enum OrgSemFileKind {
    Document,
    Attachment,
    Source,
  }
  export interface DirectoryConstructor { new(): Directory; }
  export interface Directory {
    getKind(): OrgSemKind;
    relPath: string
    absPath: string
  }
  export interface SymlinkConstructor { new(): Symlink; }
  export interface Symlink {
    getKind(): OrgSemKind;
    isDirectory: boolean
    absPath: string
  }
  export interface CmdIncludeConstructor { new(): CmdInclude; }
  export interface CmdInclude {
    getKind(): OrgSemKind;
    isExample(): boolean;
    getExampleConst(): CmdIncludeExample;
    getExampleMut(): CmdIncludeExample;
    isExport(): boolean;
    getExportConst(): CmdIncludeExport;
    getExportMut(): CmdIncludeExport;
    isCustom(): boolean;
    getCustomConst(): CmdIncludeCustom;
    getCustomMut(): CmdIncludeCustom;
    isSrc(): boolean;
    getSrcConst(): CmdIncludeSrc;
    getSrcMut(): CmdIncludeSrc;
    isOrgDocument(): boolean;
    getOrgDocumentConst(): CmdIncludeOrgDocument;
    getOrgDocumentMut(): CmdIncludeOrgDocument;
    getIncludeKindStatic(__input: CmdIncludeData): CmdIncludeKind;
    getIncludeKind(): CmdIncludeKind;
    sub_variant_get_name(): Char;
    sub_variant_get_data(): CmdIncludeData;
    sub_variant_get_kind(): CmdIncludeKind;
    path: string
    firstLine: haxorg_wasm.Optional<number>
    lastLine: haxorg_wasm.Optional<number>
    data: CmdIncludeData
  }
  export interface CmdIncludeIncludeBaseConstructor { new(): CmdIncludeIncludeBase; }
  export interface CmdIncludeIncludeBase { IncludeBase(): void; }
  export interface CmdIncludeExampleConstructor { new(): CmdIncludeExample; }
  export interface CmdIncludeExample { Example(): void; }
  export interface CmdIncludeExportConstructor { new(): CmdIncludeExport; }
  export interface CmdIncludeExport {
    Export(): void;
    language: string
  }
  export interface CmdIncludeCustomConstructor { new(): CmdIncludeCustom; }
  export interface CmdIncludeCustom {
    Custom(): void;
    blockName: string
  }
  export interface CmdIncludeSrcConstructor { new(): CmdIncludeSrc; }
  export interface CmdIncludeSrc {
    Src(): void;
    language: string
  }
  export interface CmdIncludeOrgDocumentConstructor { new(): CmdIncludeOrgDocument; }
  export interface CmdIncludeOrgDocument {
    OrgDocument(): void;
    onlyContent: haxorg_wasm.Optional<boolean>
    subtreePath: haxorg_wasm.Optional<SubtreePath>
    minLevel: haxorg_wasm.Optional<number>
    customIdTarget: haxorg_wasm.Optional<string>
  }
  export enum OrgSemCmdIncludeKind {
    Example,
    Export,
    Custom,
    Src,
    OrgDocument,
  }
  export interface ImmIdTNoneConstructor { new(): ImmIdTNone; }
  export interface ImmIdTNone {  }
  export interface ImmIdTErrorItemConstructor { new(): ImmIdTErrorItem; }
  export interface ImmIdTErrorItem {  }
  export interface ImmIdTErrorGroupConstructor { new(): ImmIdTErrorGroup; }
  export interface ImmIdTErrorGroup {  }
  export interface ImmIdTStmtConstructor { new(): ImmIdTStmt; }
  export interface ImmIdTStmt {  }
  export interface ImmIdTInlineConstructor { new(): ImmIdTInline; }
  export interface ImmIdTInline {  }
  export interface ImmIdTStmtListConstructor { new(): ImmIdTStmtList; }
  export interface ImmIdTStmtList {  }
  export interface ImmIdTEmptyConstructor { new(): ImmIdTEmpty; }
  export interface ImmIdTEmpty {  }
  export interface ImmIdTCmdConstructor { new(): ImmIdTCmd; }
  export interface ImmIdTCmd {  }
  export interface ImmIdTBlockConstructor { new(): ImmIdTBlock; }
  export interface ImmIdTBlock {  }
  export interface ImmIdTLineCommandConstructor { new(): ImmIdTLineCommand; }
  export interface ImmIdTLineCommand {  }
  export interface ImmIdTAttachedConstructor { new(): ImmIdTAttached; }
  export interface ImmIdTAttached {  }
  export interface ImmIdTLeafConstructor { new(): ImmIdTLeaf; }
  export interface ImmIdTLeaf {  }
  export interface ImmIdTCmdCaptionConstructor { new(): ImmIdTCmdCaption; }
  export interface ImmIdTCmdCaption {  }
  export interface ImmIdTCmdColumnsConstructor { new(): ImmIdTCmdColumns; }
  export interface ImmIdTCmdColumns {  }
  export interface ImmIdTCmdNameConstructor { new(): ImmIdTCmdName; }
  export interface ImmIdTCmdName {  }
  export interface ImmIdTCmdCustomArgsConstructor { new(): ImmIdTCmdCustomArgs; }
  export interface ImmIdTCmdCustomArgs {  }
  export interface ImmIdTCmdCustomRawConstructor { new(): ImmIdTCmdCustomRaw; }
  export interface ImmIdTCmdCustomRaw {  }
  export interface ImmIdTCmdCustomTextConstructor { new(): ImmIdTCmdCustomText; }
  export interface ImmIdTCmdCustomText {  }
  export interface ImmIdTCmdCallConstructor { new(): ImmIdTCmdCall; }
  export interface ImmIdTCmdCall {  }
  export interface ImmIdTCmdTblfmConstructor { new(): ImmIdTCmdTblfm; }
  export interface ImmIdTCmdTblfm {  }
  export interface ImmIdTHashTagConstructor { new(): ImmIdTHashTag; }
  export interface ImmIdTHashTag {  }
  export interface ImmIdTInlineFootnoteConstructor { new(): ImmIdTInlineFootnote; }
  export interface ImmIdTInlineFootnote {  }
  export interface ImmIdTInlineExportConstructor { new(): ImmIdTInlineExport; }
  export interface ImmIdTInlineExport {  }
  export interface ImmIdTTimeConstructor { new(): ImmIdTTime; }
  export interface ImmIdTTime {  }
  export interface ImmIdTTimeRangeConstructor { new(): ImmIdTTimeRange; }
  export interface ImmIdTTimeRange {  }
  export interface ImmIdTMacroConstructor { new(): ImmIdTMacro; }
  export interface ImmIdTMacro {  }
  export interface ImmIdTSymbolConstructor { new(): ImmIdTSymbol; }
  export interface ImmIdTSymbol {  }
  export interface ImmIdTEscapedConstructor { new(): ImmIdTEscaped; }
  export interface ImmIdTEscaped {  }
  export interface ImmIdTNewlineConstructor { new(): ImmIdTNewline; }
  export interface ImmIdTNewline {  }
  export interface ImmIdTSpaceConstructor { new(): ImmIdTSpace; }
  export interface ImmIdTSpace {  }
  export interface ImmIdTWordConstructor { new(): ImmIdTWord; }
  export interface ImmIdTWord {  }
  export interface ImmIdTAtMentionConstructor { new(): ImmIdTAtMention; }
  export interface ImmIdTAtMention {  }
  export interface ImmIdTRawTextConstructor { new(): ImmIdTRawText; }
  export interface ImmIdTRawText {  }
  export interface ImmIdTPunctuationConstructor { new(): ImmIdTPunctuation; }
  export interface ImmIdTPunctuation {  }
  export interface ImmIdTPlaceholderConstructor { new(): ImmIdTPlaceholder; }
  export interface ImmIdTPlaceholder {  }
  export interface ImmIdTBigIdentConstructor { new(): ImmIdTBigIdent; }
  export interface ImmIdTBigIdent {  }
  export interface ImmIdTTextTargetConstructor { new(): ImmIdTTextTarget; }
  export interface ImmIdTTextTarget {  }
  export interface ImmIdTMarkupConstructor { new(): ImmIdTMarkup; }
  export interface ImmIdTMarkup {  }
  export interface ImmIdTBoldConstructor { new(): ImmIdTBold; }
  export interface ImmIdTBold {  }
  export interface ImmIdTUnderlineConstructor { new(): ImmIdTUnderline; }
  export interface ImmIdTUnderline {  }
  export interface ImmIdTMonospaceConstructor { new(): ImmIdTMonospace; }
  export interface ImmIdTMonospace {  }
  export interface ImmIdTMarkQuoteConstructor { new(): ImmIdTMarkQuote; }
  export interface ImmIdTMarkQuote {  }
  export interface ImmIdTVerbatimConstructor { new(): ImmIdTVerbatim; }
  export interface ImmIdTVerbatim {  }
  export interface ImmIdTItalicConstructor { new(): ImmIdTItalic; }
  export interface ImmIdTItalic {  }
  export interface ImmIdTStrikeConstructor { new(): ImmIdTStrike; }
  export interface ImmIdTStrike {  }
  export interface ImmIdTParConstructor { new(): ImmIdTPar; }
  export interface ImmIdTPar {  }
  export interface ImmIdTRadioTargetConstructor { new(): ImmIdTRadioTarget; }
  export interface ImmIdTRadioTarget {  }
  export interface ImmIdTLatexConstructor { new(): ImmIdTLatex; }
  export interface ImmIdTLatex {  }
  export interface ImmIdTLinkConstructor { new(): ImmIdTLink; }
  export interface ImmIdTLink {  }
  export interface ImmIdTBlockCenterConstructor { new(): ImmIdTBlockCenter; }
  export interface ImmIdTBlockCenter {  }
  export interface ImmIdTBlockQuoteConstructor { new(): ImmIdTBlockQuote; }
  export interface ImmIdTBlockQuote {  }
  export interface ImmIdTBlockCommentConstructor { new(): ImmIdTBlockComment; }
  export interface ImmIdTBlockComment {  }
  export interface ImmIdTBlockVerseConstructor { new(): ImmIdTBlockVerse; }
  export interface ImmIdTBlockVerse {  }
  export interface ImmIdTBlockDynamicFallbackConstructor { new(): ImmIdTBlockDynamicFallback; }
  export interface ImmIdTBlockDynamicFallback {  }
  export interface ImmIdTBlockExampleConstructor { new(): ImmIdTBlockExample; }
  export interface ImmIdTBlockExample {  }
  export interface ImmIdTBlockExportConstructor { new(): ImmIdTBlockExport; }
  export interface ImmIdTBlockExport {  }
  export interface ImmIdTBlockAdmonitionConstructor { new(): ImmIdTBlockAdmonition; }
  export interface ImmIdTBlockAdmonition {  }
  export interface ImmIdTBlockCodeEvalResultConstructor { new(): ImmIdTBlockCodeEvalResult; }
  export interface ImmIdTBlockCodeEvalResult {  }
  export interface ImmIdTBlockCodeConstructor { new(): ImmIdTBlockCode; }
  export interface ImmIdTBlockCode {  }
  export interface ImmIdTSubtreeLogConstructor { new(): ImmIdTSubtreeLog; }
  export interface ImmIdTSubtreeLog {  }
  export interface ImmIdTSubtreeConstructor { new(): ImmIdTSubtree; }
  export interface ImmIdTSubtree {  }
  export interface ImmIdTCellConstructor { new(): ImmIdTCell; }
  export interface ImmIdTCell {  }
  export interface ImmIdTRowConstructor { new(): ImmIdTRow; }
  export interface ImmIdTRow {  }
  export interface ImmIdTTableConstructor { new(): ImmIdTTable; }
  export interface ImmIdTTable {  }
  export interface ImmIdTParagraphConstructor { new(): ImmIdTParagraph; }
  export interface ImmIdTParagraph {  }
  export interface ImmIdTColonExampleConstructor { new(): ImmIdTColonExample; }
  export interface ImmIdTColonExample {  }
  export interface ImmIdTCmdAttrConstructor { new(): ImmIdTCmdAttr; }
  export interface ImmIdTCmdAttr {  }
  export interface ImmIdTCmdExportConstructor { new(): ImmIdTCmdExport; }
  export interface ImmIdTCmdExport {  }
  export interface ImmIdTCallConstructor { new(): ImmIdTCall; }
  export interface ImmIdTCall {  }
  export interface ImmIdTListConstructor { new(): ImmIdTList; }
  export interface ImmIdTList {  }
  export interface ImmIdTListItemConstructor { new(): ImmIdTListItem; }
  export interface ImmIdTListItem {  }
  export interface ImmIdTDocumentOptionsConstructor { new(): ImmIdTDocumentOptions; }
  export interface ImmIdTDocumentOptions {  }
  export interface ImmIdTDocumentFragmentConstructor { new(): ImmIdTDocumentFragment; }
  export interface ImmIdTDocumentFragment {  }
  export interface ImmIdTCriticMarkupConstructor { new(): ImmIdTCriticMarkup; }
  export interface ImmIdTCriticMarkup {  }
  export interface ImmIdTDocumentConstructor { new(): ImmIdTDocument; }
  export interface ImmIdTDocument {  }
  export interface ImmIdTFileTargetConstructor { new(): ImmIdTFileTarget; }
  export interface ImmIdTFileTarget {  }
  export interface ImmIdTTextSeparatorConstructor { new(): ImmIdTTextSeparator; }
  export interface ImmIdTTextSeparator {  }
  export interface ImmIdTDocumentGroupConstructor { new(): ImmIdTDocumentGroup; }
  export interface ImmIdTDocumentGroup {  }
  export interface ImmIdTFileConstructor { new(): ImmIdTFile; }
  export interface ImmIdTFile {  }
  export interface ImmIdTDirectoryConstructor { new(): ImmIdTDirectory; }
  export interface ImmIdTDirectory {  }
  export interface ImmIdTSymlinkConstructor { new(): ImmIdTSymlink; }
  export interface ImmIdTSymlink {  }
  export interface ImmIdTCmdIncludeConstructor { new(): ImmIdTCmdInclude; }
  export interface ImmIdTCmdInclude {  }
  export interface ImmNoneValueConstructor { new(): ImmNoneValue; }
  export interface ImmNoneValue {  }
  export interface ImmErrorItemValueConstructor { new(): ImmErrorItemValue; }
  export interface ImmErrorItemValue {
    setMessage(value: ImmerBox<string>): void;
    setFunction(value: ImmerBox<haxorg_wasm.Optional<string>>): void;
    setLine(value: ImmerBox<haxorg_wasm.Optional<number>>): void;
  }
  export interface ImmErrorGroupValueConstructor { new(): ImmErrorGroupValue; }
  export interface ImmErrorGroupValue {
    setDiagnostics(value: ImmerFlex_vector<ImmIdT<ImmErrorItem>>): void;
    setFunction(value: ImmerBox<haxorg_wasm.Optional<string>>): void;
    setLine(value: ImmerBox<haxorg_wasm.Optional<number>>): void;
  }
  export interface ImmStmtListValueConstructor { new(): ImmStmtListValue; }
  export interface ImmStmtListValue {  }
  export interface ImmEmptyValueConstructor { new(): ImmEmptyValue; }
  export interface ImmEmptyValue {  }
  export interface ImmCmdCaptionValueConstructor { new(): ImmCmdCaptionValue; }
  export interface ImmCmdCaptionValue { setText(value: ImmIdT<ImmParagraph>): void; }
  export interface ImmCmdColumnsValueConstructor { new(): ImmCmdColumnsValue; }
  export interface ImmCmdColumnsValue { setView(value: ColumnView): void; }
  export interface ImmCmdNameValueConstructor { new(): ImmCmdNameValue; }
  export interface ImmCmdNameValue { setName(value: ImmerBox<string>): void; }
  export interface ImmCmdCustomArgsValueConstructor { new(): ImmCmdCustomArgsValue; }
  export interface ImmCmdCustomArgsValue {
    setName(value: ImmerBox<string>): void;
    setIsattached(value: boolean): void;
  }
  export interface ImmCmdCustomRawValueConstructor { new(): ImmCmdCustomRawValue; }
  export interface ImmCmdCustomRawValue {
    setName(value: ImmerBox<string>): void;
    setIsattached(value: boolean): void;
    setText(value: ImmerBox<string>): void;
  }
  export interface ImmCmdCustomTextValueConstructor { new(): ImmCmdCustomTextValue; }
  export interface ImmCmdCustomTextValue {
    setName(value: ImmerBox<string>): void;
    setIsattached(value: boolean): void;
    setText(value: ImmIdT<ImmParagraph>): void;
  }
  export interface ImmCmdCallValueConstructor { new(): ImmCmdCallValue; }
  export interface ImmCmdCallValue {
    setName(value: ImmerBox<string>): void;
    setFilename(value: ImmerBox<haxorg_wasm.Optional<string>>): void;
    setInsideheaderattrs(value: AttrGroup): void;
    setCallattrs(value: AttrGroup): void;
    setEndheaderattrs(value: AttrGroup): void;
    setResult(value: ImmerFlex_vector<ImmIdT<ImmBlockCodeEvalResult>>): void;
  }
  export interface ImmCmdTblfmValueConstructor { new(): ImmCmdTblfmValue; }
  export interface ImmCmdTblfmValue { setExpr(value: Tblfm): void; }
  export interface ImmHashTagValueConstructor { new(): ImmHashTagValue; }
  export interface ImmHashTagValue { setText(value: HashTagText): void; }
  export interface ImmInlineFootnoteValueConstructor { new(): ImmInlineFootnoteValue; }
  export interface ImmInlineFootnoteValue {
    setTag(value: ImmerBox<string>): void;
    setDefinition(value: ImmerBox<haxorg_wasm.Optional<ImmIdT<ImmOrg>>>): void;
  }
  export interface ImmInlineExportValueConstructor { new(): ImmInlineExportValue; }
  export interface ImmInlineExportValue {
    setExporter(value: ImmerBox<string>): void;
    setContent(value: ImmerBox<string>): void;
  }
  export interface ImmTimeValueConstructor { new(): ImmTimeValue; }
  export interface ImmTimeValue {
    setIsactive(value: boolean): void;
    setTime(value: ImmTimeTimeVariant): void;
  }
  export interface ImmTimeRangeValueConstructor { new(): ImmTimeRangeValue; }
  export interface ImmTimeRangeValue {
    setFrom(value: ImmIdT<ImmTime>): void;
    setTo(value: ImmIdT<ImmTime>): void;
  }
  export interface ImmMacroValueConstructor { new(): ImmMacroValue; }
  export interface ImmMacroValue {
    setName(value: ImmerBox<string>): void;
    setAttrs(value: AttrGroup): void;
  }
  export interface ImmSymbolValueConstructor { new(): ImmSymbolValue; }
  export interface ImmSymbolValue {
    setName(value: ImmerBox<string>): void;
    setParameters(value: ImmerFlex_vector<ImmSymbolParam>): void;
    setPositional(value: ImmerFlex_vector<ImmIdT<ImmOrg>>): void;
  }
  export interface ImmEscapedValueConstructor { new(): ImmEscapedValue; }
  export interface ImmEscapedValue {  }
  export interface ImmNewlineValueConstructor { new(): ImmNewlineValue; }
  export interface ImmNewlineValue {  }
  export interface ImmSpaceValueConstructor { new(): ImmSpaceValue; }
  export interface ImmSpaceValue {  }
  export interface ImmWordValueConstructor { new(): ImmWordValue; }
  export interface ImmWordValue {  }
  export interface ImmAtMentionValueConstructor { new(): ImmAtMentionValue; }
  export interface ImmAtMentionValue {  }
  export interface ImmRawTextValueConstructor { new(): ImmRawTextValue; }
  export interface ImmRawTextValue {  }
  export interface ImmPunctuationValueConstructor { new(): ImmPunctuationValue; }
  export interface ImmPunctuationValue {  }
  export interface ImmPlaceholderValueConstructor { new(): ImmPlaceholderValue; }
  export interface ImmPlaceholderValue {  }
  export interface ImmBigIdentValueConstructor { new(): ImmBigIdentValue; }
  export interface ImmBigIdentValue {  }
  export interface ImmTextTargetValueConstructor { new(): ImmTextTargetValue; }
  export interface ImmTextTargetValue {  }
  export interface ImmBoldValueConstructor { new(): ImmBoldValue; }
  export interface ImmBoldValue {  }
  export interface ImmUnderlineValueConstructor { new(): ImmUnderlineValue; }
  export interface ImmUnderlineValue {  }
  export interface ImmMonospaceValueConstructor { new(): ImmMonospaceValue; }
  export interface ImmMonospaceValue {  }
  export interface ImmMarkQuoteValueConstructor { new(): ImmMarkQuoteValue; }
  export interface ImmMarkQuoteValue {  }
  export interface ImmVerbatimValueConstructor { new(): ImmVerbatimValue; }
  export interface ImmVerbatimValue {  }
  export interface ImmItalicValueConstructor { new(): ImmItalicValue; }
  export interface ImmItalicValue {  }
  export interface ImmStrikeValueConstructor { new(): ImmStrikeValue; }
  export interface ImmStrikeValue {  }
  export interface ImmParValueConstructor { new(): ImmParValue; }
  export interface ImmParValue {  }
  export interface ImmRadioTargetValueConstructor { new(): ImmRadioTargetValue; }
  export interface ImmRadioTargetValue { setWords(value: ImmerFlex_vector<string>): void; }
  export interface ImmLatexValueConstructor { new(): ImmLatexValue; }
  export interface ImmLatexValue {  }
  export interface ImmLinkValueConstructor { new(): ImmLinkValue; }
  export interface ImmLinkValue {
    setDescription(value: ImmerBox<haxorg_wasm.Optional<ImmIdT<ImmParagraph>>>): void;
    setTarget(value: LinkTarget): void;
  }
  export interface ImmBlockCenterValueConstructor { new(): ImmBlockCenterValue; }
  export interface ImmBlockCenterValue {  }
  export interface ImmBlockQuoteValueConstructor { new(): ImmBlockQuoteValue; }
  export interface ImmBlockQuoteValue {  }
  export interface ImmBlockCommentValueConstructor { new(): ImmBlockCommentValue; }
  export interface ImmBlockCommentValue {  }
  export interface ImmBlockVerseValueConstructor { new(): ImmBlockVerseValue; }
  export interface ImmBlockVerseValue {  }
  export interface ImmBlockDynamicFallbackValueConstructor { new(): ImmBlockDynamicFallbackValue; }
  export interface ImmBlockDynamicFallbackValue { setName(value: ImmerBox<string>): void; }
  export interface ImmBlockExampleValueConstructor { new(): ImmBlockExampleValue; }
  export interface ImmBlockExampleValue {  }
  export interface ImmBlockExportValueConstructor { new(): ImmBlockExportValue; }
  export interface ImmBlockExportValue {
    setExporter(value: ImmerBox<string>): void;
    setContent(value: ImmerBox<string>): void;
  }
  export interface ImmBlockAdmonitionValueConstructor { new(): ImmBlockAdmonitionValue; }
  export interface ImmBlockAdmonitionValue {  }
  export interface ImmBlockCodeEvalResultValueConstructor { new(): ImmBlockCodeEvalResultValue; }
  export interface ImmBlockCodeEvalResultValue {
    setRaw(value: ImmerFlex_vector<OrgCodeEvalOutput>): void;
    setNode(value: ImmIdT<ImmOrg>): void;
  }
  export interface ImmBlockCodeValueConstructor { new(): ImmBlockCodeValue; }
  export interface ImmBlockCodeValue {
    setLang(value: ImmerBox<haxorg_wasm.Optional<string>>): void;
    setExports(value: BlockCodeExports): void;
    setResult(value: ImmerFlex_vector<ImmIdT<ImmBlockCodeEvalResult>>): void;
    setLines(value: ImmerFlex_vector<BlockCodeLine>): void;
    setCache(value: boolean): void;
    setEval(value: boolean): void;
    setNoweb(value: boolean): void;
    setHlines(value: boolean): void;
    setTangle(value: boolean): void;
    setSwitches(value: AttrGroup): void;
  }
  export interface ImmSubtreeLogValueConstructor { new(): ImmSubtreeLogValue; }
  export interface ImmSubtreeLogValue {
    setHead(value: SubtreeLogHead): void;
    setDesc(value: ImmerBox<haxorg_wasm.Optional<ImmIdT<ImmStmtList>>>): void;
  }
  export interface ImmSubtreeValueConstructor { new(): ImmSubtreeValue; }
  export interface ImmSubtreeValue {
    setLevel(value: number): void;
    setTreeid(value: ImmerBox<haxorg_wasm.Optional<string>>): void;
    setTodo(value: ImmerBox<haxorg_wasm.Optional<string>>): void;
    setCompletion(value: ImmerBox<haxorg_wasm.Optional<SubtreeCompletion>>): void;
    setDescription(value: ImmerBox<haxorg_wasm.Optional<ImmIdT<ImmParagraph>>>): void;
    setTags(value: ImmerFlex_vector<ImmIdT<ImmHashTag>>): void;
    setTitle(value: ImmIdT<ImmParagraph>): void;
    setLogbook(value: ImmerFlex_vector<ImmIdT<ImmSubtreeLog>>): void;
    setProperties(value: ImmerFlex_vector<NamedProperty>): void;
    setClosed(value: ImmerBox<haxorg_wasm.Optional<UserTime>>): void;
    setDeadline(value: ImmerBox<haxorg_wasm.Optional<UserTime>>): void;
    setScheduled(value: ImmerBox<haxorg_wasm.Optional<UserTime>>): void;
    setIscomment(value: boolean): void;
    setIsarchived(value: boolean): void;
    setPriority(value: ImmerBox<haxorg_wasm.Optional<string>>): void;
  }
  export interface ImmCellValueConstructor { new(): ImmCellValue; }
  export interface ImmCellValue { setIsblock(value: boolean): void; }
  export interface ImmRowValueConstructor { new(): ImmRowValue; }
  export interface ImmRowValue {
    setCells(value: ImmerFlex_vector<ImmIdT<ImmCell>>): void;
    setIsblock(value: boolean): void;
  }
  export interface ImmTableValueConstructor { new(): ImmTableValue; }
  export interface ImmTableValue {
    setRows(value: ImmerFlex_vector<ImmIdT<ImmRow>>): void;
    setIsblock(value: boolean): void;
  }
  export interface ImmParagraphValueConstructor { new(): ImmParagraphValue; }
  export interface ImmParagraphValue {  }
  export interface ImmColonExampleValueConstructor { new(): ImmColonExampleValue; }
  export interface ImmColonExampleValue {  }
  export interface ImmCmdAttrValueConstructor { new(): ImmCmdAttrValue; }
  export interface ImmCmdAttrValue { setTarget(value: ImmerBox<string>): void; }
  export interface ImmCmdExportValueConstructor { new(): ImmCmdExportValue; }
  export interface ImmCmdExportValue {
    setExporter(value: ImmerBox<string>): void;
    setContent(value: ImmerBox<string>): void;
  }
  export interface ImmCallValueConstructor { new(): ImmCallValue; }
  export interface ImmCallValue {
    setName(value: ImmerBox<string>): void;
    setAttrs(value: AttrGroup): void;
    setIscommand(value: boolean): void;
  }
  export interface ImmListValueConstructor { new(): ImmListValue; }
  export interface ImmListValue {  }
  export interface ImmListItemValueConstructor { new(): ImmListItemValue; }
  export interface ImmListItemValue {
    setCheckbox(value: CheckboxState): void;
    setHeader(value: ImmerBox<haxorg_wasm.Optional<ImmIdT<ImmParagraph>>>): void;
    setBullet(value: ImmerBox<haxorg_wasm.Optional<string>>): void;
  }
  export interface ImmDocumentOptionsValueConstructor { new(): ImmDocumentOptionsValue; }
  export interface ImmDocumentOptionsValue {
    setInitialvisibility(value: InitialSubtreeVisibility): void;
    setProperties(value: ImmerFlex_vector<NamedProperty>): void;
    setExportconfig(value: DocumentExportConfig): void;
    setFixedwidthsections(value: ImmerBox<haxorg_wasm.Optional<boolean>>): void;
    setStartupindented(value: ImmerBox<haxorg_wasm.Optional<boolean>>): void;
    setCategory(value: ImmerBox<haxorg_wasm.Optional<string>>): void;
    setSetupfile(value: ImmerBox<haxorg_wasm.Optional<string>>): void;
    setMaxsubtreelevelexport(value: ImmerBox<haxorg_wasm.Optional<number>>): void;
    setColumns(value: ImmerBox<haxorg_wasm.Optional<ColumnView>>): void;
    setTodokeywords(value: ImmerFlex_vector<TodoKeyword>): void;
    setDonekeywords(value: ImmerFlex_vector<TodoKeyword>): void;
  }
  export interface ImmDocumentFragmentValueConstructor { new(): ImmDocumentFragmentValue; }
  export interface ImmDocumentFragmentValue {
    setBaseline(value: number): void;
    setBasecol(value: number): void;
  }
  export interface ImmCriticMarkupValueConstructor { new(): ImmCriticMarkupValue; }
  export interface ImmCriticMarkupValue { setKind(value: ImmCriticMarkupKind): void; }
  export interface ImmDocumentValueConstructor { new(): ImmDocumentValue; }
  export interface ImmDocumentValue {
    setTitle(value: ImmerBox<haxorg_wasm.Optional<ImmIdT<ImmParagraph>>>): void;
    setAuthor(value: ImmerBox<haxorg_wasm.Optional<ImmIdT<ImmParagraph>>>): void;
    setCreator(value: ImmerBox<haxorg_wasm.Optional<ImmIdT<ImmParagraph>>>): void;
    setFiletags(value: ImmerFlex_vector<ImmIdT<ImmHashTag>>): void;
    setEmail(value: ImmerBox<haxorg_wasm.Optional<ImmIdT<ImmRawText>>>): void;
    setLanguage(value: ImmerFlex_vector<string>): void;
    setOptions(value: ImmIdT<ImmDocumentOptions>): void;
    setExportfilename(value: ImmerBox<haxorg_wasm.Optional<string>>): void;
  }
  export interface ImmFileTargetValueConstructor { new(): ImmFileTargetValue; }
  export interface ImmFileTargetValue {
    setPath(value: ImmerBox<string>): void;
    setLine(value: ImmerBox<haxorg_wasm.Optional<number>>): void;
    setSearchtarget(value: ImmerBox<haxorg_wasm.Optional<string>>): void;
    setRestricttoheadlines(value: boolean): void;
    setTargetid(value: ImmerBox<haxorg_wasm.Optional<string>>): void;
    setRegexp(value: ImmerBox<haxorg_wasm.Optional<string>>): void;
  }
  export interface ImmTextSeparatorValueConstructor { new(): ImmTextSeparatorValue; }
  export interface ImmTextSeparatorValue {  }
  export interface ImmDocumentGroupValueConstructor { new(): ImmDocumentGroupValue; }
  export interface ImmDocumentGroupValue {  }
  export interface ImmFileValueConstructor { new(): ImmFileValue; }
  export interface ImmFileValue {
    setRelpath(value: ImmerBox<string>): void;
    setAbspath(value: ImmerBox<string>): void;
    setData(value: ImmFileData): void;
  }
  export interface ImmDirectoryValueConstructor { new(): ImmDirectoryValue; }
  export interface ImmDirectoryValue {
    setRelpath(value: ImmerBox<string>): void;
    setAbspath(value: ImmerBox<string>): void;
  }
  export interface ImmSymlinkValueConstructor { new(): ImmSymlinkValue; }
  export interface ImmSymlinkValue {
    setIsdirectory(value: boolean): void;
    setAbspath(value: ImmerBox<string>): void;
  }
  export interface ImmCmdIncludeValueConstructor { new(): ImmCmdIncludeValue; }
  export interface ImmCmdIncludeValue {
    setPath(value: ImmerBox<string>): void;
    setFirstline(value: ImmerBox<haxorg_wasm.Optional<number>>): void;
    setLastline(value: ImmerBox<haxorg_wasm.Optional<number>>): void;
    setData(value: ImmCmdIncludeData): void;
  }
  export interface ImmAdapterOrgAPIConstructor { new(): ImmAdapterOrgAPI; }
  export interface ImmAdapterOrgAPI {  }
  export interface ImmCmdConstructor { new(): ImmCmd; }
  export interface ImmCmd {
    __eq__(other: ImmCmd): boolean;
    attrs: AttrGroup
  }
  export interface ImmCmdCustomRawConstructor { new(): ImmCmdCustomRaw; }
  export interface ImmCmdCustomRaw {
    getKind(): OrgSemKind;
    __eq__(other: ImmCmdCustomRaw): boolean;
    name: ImmBox<string>
    isAttached: boolean
    text: ImmBox<string>
  }
  export interface ImmCmdCustomTextConstructor { new(): ImmCmdCustomText; }
  export interface ImmCmdCustomText {
    getKind(): OrgSemKind;
    __eq__(other: ImmCmdCustomText): boolean;
    name: ImmBox<string>
    isAttached: boolean
    text: ImmIdT<ImmParagraph>
  }
  export interface ImmLinkConstructor { new(): ImmLink; }
  export interface ImmLink {
    getKind(): OrgSemKind;
    __eq__(other: ImmLink): boolean;
    description: ImmBox<haxorg_wasm.Optional<ImmIdT<ImmParagraph>>>
    target: LinkTarget
  }
  export interface ImmBlockCommentConstructor { new(): ImmBlockComment; }
  export interface ImmBlockComment {
    getKind(): OrgSemKind;
    __eq__(other: ImmBlockComment): boolean;
  }
  export interface ImmParagraphConstructor { new(): ImmParagraph; }
  export interface ImmParagraph {
    getKind(): OrgSemKind;
    __eq__(other: ImmParagraph): boolean;
  }
  export interface ImmListConstructor { new(): ImmList; }
  export interface ImmList {
    getKind(): OrgSemKind;
    __eq__(other: ImmList): boolean;
  }
  export interface ImmHashTagConstructor { new(): ImmHashTag; }
  export interface ImmHashTag {
    getKind(): OrgSemKind;
    __eq__(other: ImmHashTag): boolean;
    text: HashTagText
  }
  export interface ImmInlineFootnoteConstructor { new(): ImmInlineFootnote; }
  export interface ImmInlineFootnote {
    getKind(): OrgSemKind;
    __eq__(other: ImmInlineFootnote): boolean;
    tag: ImmBox<string>
    definition: ImmBox<haxorg_wasm.Optional<ImmIdT<ImmOrg>>>
  }
  export interface ImmInlineExportConstructor { new(): ImmInlineExport; }
  export interface ImmInlineExport {
    getKind(): OrgSemKind;
    __eq__(other: ImmInlineExport): boolean;
    exporter: ImmBox<string>
    content: ImmBox<string>
  }
  export interface ImmEscapedConstructor { new(): ImmEscaped; }
  export interface ImmEscaped {
    getKind(): OrgSemKind;
    __eq__(other: ImmEscaped): boolean;
  }
  export interface ImmNewlineConstructor { new(): ImmNewline; }
  export interface ImmNewline {
    getKind(): OrgSemKind;
    __eq__(other: ImmNewline): boolean;
  }
  export interface ImmSpaceConstructor { new(): ImmSpace; }
  export interface ImmSpace {
    getKind(): OrgSemKind;
    __eq__(other: ImmSpace): boolean;
  }
  export interface ImmWordConstructor { new(): ImmWord; }
  export interface ImmWord {
    getKind(): OrgSemKind;
    __eq__(other: ImmWord): boolean;
  }
  export interface ImmAtMentionConstructor { new(): ImmAtMention; }
  export interface ImmAtMention {
    getKind(): OrgSemKind;
    __eq__(other: ImmAtMention): boolean;
  }
  export interface ImmRawTextConstructor { new(): ImmRawText; }
  export interface ImmRawText {
    getKind(): OrgSemKind;
    __eq__(other: ImmRawText): boolean;
  }
  export interface ImmPunctuationConstructor { new(): ImmPunctuation; }
  export interface ImmPunctuation {
    getKind(): OrgSemKind;
    __eq__(other: ImmPunctuation): boolean;
  }
  export interface ImmPlaceholderConstructor { new(): ImmPlaceholder; }
  export interface ImmPlaceholder {
    getKind(): OrgSemKind;
    __eq__(other: ImmPlaceholder): boolean;
  }
  export interface ImmBigIdentConstructor { new(): ImmBigIdent; }
  export interface ImmBigIdent {
    getKind(): OrgSemKind;
    __eq__(other: ImmBigIdent): boolean;
  }
  export interface ImmTextTargetConstructor { new(): ImmTextTarget; }
  export interface ImmTextTarget {
    getKind(): OrgSemKind;
    __eq__(other: ImmTextTarget): boolean;
  }
  export interface ImmBoldConstructor { new(): ImmBold; }
  export interface ImmBold {
    getKind(): OrgSemKind;
    __eq__(other: ImmBold): boolean;
  }
  export interface ImmUnderlineConstructor { new(): ImmUnderline; }
  export interface ImmUnderline {
    getKind(): OrgSemKind;
    __eq__(other: ImmUnderline): boolean;
  }
  export interface ImmMonospaceConstructor { new(): ImmMonospace; }
  export interface ImmMonospace {
    getKind(): OrgSemKind;
    __eq__(other: ImmMonospace): boolean;
  }
  export interface ImmMarkQuoteConstructor { new(): ImmMarkQuote; }
  export interface ImmMarkQuote {
    getKind(): OrgSemKind;
    __eq__(other: ImmMarkQuote): boolean;
  }
  export interface ImmVerbatimConstructor { new(): ImmVerbatim; }
  export interface ImmVerbatim {
    getKind(): OrgSemKind;
    __eq__(other: ImmVerbatim): boolean;
  }
  export interface ImmItalicConstructor { new(): ImmItalic; }
  export interface ImmItalic {
    getKind(): OrgSemKind;
    __eq__(other: ImmItalic): boolean;
  }
  export interface ImmStrikeConstructor { new(): ImmStrike; }
  export interface ImmStrike {
    getKind(): OrgSemKind;
    __eq__(other: ImmStrike): boolean;
  }
  export interface ImmParConstructor { new(): ImmPar; }
  export interface ImmPar {
    getKind(): OrgSemKind;
    __eq__(other: ImmPar): boolean;
  }
  export interface CmdConstructor { new(): Cmd; }
  export interface Cmd {
    getAttrs(key: haxorg_wasm.Optional<string>): Vec<AttrValue>;
    getFirstAttr(kind: string): haxorg_wasm.Optional<AttrValue>;
    attrs: AttrGroup
  }
  export interface CmdCustomRawConstructor { new(): CmdCustomRaw; }
  export interface CmdCustomRaw {
    getKind(): OrgSemKind;
    name: string
    isAttached: boolean
    text: string
  }
  export interface CmdCustomTextConstructor { new(): CmdCustomText; }
  export interface CmdCustomText {
    getKind(): OrgSemKind;
    name: string
    isAttached: boolean
    text: Paragraph
  }
  export interface LinkConstructor { new(): Link; }
  export interface Link {
    getKind(): OrgSemKind;
    description: haxorg_wasm.Optional<Paragraph>
    target: LinkTarget
  }
  export interface BlockCommentConstructor { new(): BlockComment; }
  export interface BlockComment { getKind(): OrgSemKind; }
  export interface ParagraphConstructor { new(): Paragraph; }
  export interface Paragraph {
    getKind(): OrgSemKind;
    isFootnoteDefinition(): boolean;
    getFootnoteName(): haxorg_wasm.Optional<string>;
    hasAdmonition(): boolean;
    getAdmonitions(): Vec<string>;
    getAdmonitionNodes(): Vec<BigIdent>;
    hasTimestamp(): boolean;
    getTimestamps(): Vec<UserTime>;
    getTimestampNodes(): Vec<Time>;
    hasLeadHashtags(): boolean;
    getLeadHashtags(): Vec<HashTag>;
    getBody(): Vec<Org>;
  }
  export interface ListConstructor { new(): List; }
  export interface List {
    getKind(): OrgSemKind;
    getListAttrs(key: string): Vec<AttrValue>;
    getListFormattingMode(): ListFormattingMode;
    isDescriptionList(): boolean;
    isNumberedList(): boolean;
  }
  export interface HashTagConstructor { new(): HashTag; }
  export interface HashTag {
    getKind(): OrgSemKind;
    text: HashTagText
  }
  export interface InlineFootnoteConstructor { new(): InlineFootnote; }
  export interface InlineFootnote {
    getKind(): OrgSemKind;
    tag: string
    definition: haxorg_wasm.Optional<Org>
  }
  export interface InlineExportConstructor { new(): InlineExport; }
  export interface InlineExport {
    getKind(): OrgSemKind;
    exporter: string
    content: string
  }
  export interface EscapedConstructor { new(): Escaped; }
  export interface Escaped { getKind(): OrgSemKind; }
  export interface NewlineConstructor { new(): Newline; }
  export interface Newline { getKind(): OrgSemKind; }
  export interface SpaceConstructor { new(): Space; }
  export interface Space { getKind(): OrgSemKind; }
  export interface WordConstructor { new(): Word; }
  export interface Word { getKind(): OrgSemKind; }
  export interface AtMentionConstructor { new(): AtMention; }
  export interface AtMention { getKind(): OrgSemKind; }
  export interface RawTextConstructor { new(): RawText; }
  export interface RawText { getKind(): OrgSemKind; }
  export interface PunctuationConstructor { new(): Punctuation; }
  export interface Punctuation { getKind(): OrgSemKind; }
  export interface PlaceholderConstructor { new(): Placeholder; }
  export interface Placeholder { getKind(): OrgSemKind; }
  export interface BigIdentConstructor { new(): BigIdent; }
  export interface BigIdent { getKind(): OrgSemKind; }
  export interface TextTargetConstructor { new(): TextTarget; }
  export interface TextTarget { getKind(): OrgSemKind; }
  export interface BoldConstructor { new(): Bold; }
  export interface Bold { getKind(): OrgSemKind; }
  export interface UnderlineConstructor { new(): Underline; }
  export interface Underline { getKind(): OrgSemKind; }
  export interface MonospaceConstructor { new(): Monospace; }
  export interface Monospace { getKind(): OrgSemKind; }
  export interface MarkQuoteConstructor { new(): MarkQuote; }
  export interface MarkQuote { getKind(): OrgSemKind; }
  export interface VerbatimConstructor { new(): Verbatim; }
  export interface Verbatim { getKind(): OrgSemKind; }
  export interface ItalicConstructor { new(): Italic; }
  export interface Italic { getKind(): OrgSemKind; }
  export interface StrikeConstructor { new(): Strike; }
  export interface Strike { getKind(): OrgSemKind; }
  export interface ParConstructor { new(): Par; }
  export interface Par { getKind(): OrgSemKind; }
  export interface ImmAdapterStmtAPIConstructor { new(): ImmAdapterStmtAPI; }
  export interface ImmAdapterStmtAPI {  }
  export interface ImmAdapterSubtreeAPIConstructor { new(): ImmAdapterSubtreeAPI; }
  export interface ImmAdapterSubtreeAPI {  }
  export interface ImmAdapterNoneAPIConstructor { new(): ImmAdapterNoneAPI; }
  export interface ImmAdapterNoneAPI {  }
  export interface ImmAdapterAttrAPIConstructor { new(): ImmAdapterAttrAPI; }
  export interface ImmAdapterAttrAPI {  }
  export interface ImmAdapterAttrListAPIConstructor { new(): ImmAdapterAttrListAPI; }
  export interface ImmAdapterAttrListAPI {  }
  export interface ImmAdapterAttrsAPIConstructor { new(): ImmAdapterAttrsAPI; }
  export interface ImmAdapterAttrsAPI {  }
  export interface ImmAdapterErrorItemAPIConstructor { new(): ImmAdapterErrorItemAPI; }
  export interface ImmAdapterErrorItemAPI {  }
  export interface ImmAdapterErrorGroupAPIConstructor { new(): ImmAdapterErrorGroupAPI; }
  export interface ImmAdapterErrorGroupAPI {  }
  export interface ImmAdapterStmtListAPIConstructor { new(): ImmAdapterStmtListAPI; }
  export interface ImmAdapterStmtListAPI {  }
  export interface ImmAdapterEmptyAPIConstructor { new(): ImmAdapterEmptyAPI; }
  export interface ImmAdapterEmptyAPI {  }
  export interface ImmAdapterInlineAPIConstructor { new(): ImmAdapterInlineAPI; }
  export interface ImmAdapterInlineAPI {  }
  export interface ImmAdapterTimeAPIConstructor { new(): ImmAdapterTimeAPI; }
  export interface ImmAdapterTimeAPI {  }
  export interface ImmAdapterTimeRangeAPIConstructor { new(): ImmAdapterTimeRangeAPI; }
  export interface ImmAdapterTimeRangeAPI {  }
  export interface ImmAdapterMacroAPIConstructor { new(): ImmAdapterMacroAPI; }
  export interface ImmAdapterMacroAPI {  }
  export interface ImmAdapterSymbolAPIConstructor { new(): ImmAdapterSymbolAPI; }
  export interface ImmAdapterSymbolAPI {  }
  export interface ImmAdapterLeafAPIConstructor { new(): ImmAdapterLeafAPI; }
  export interface ImmAdapterLeafAPI {  }
  export interface ImmAdapterMarkupAPIConstructor { new(): ImmAdapterMarkupAPI; }
  export interface ImmAdapterMarkupAPI {  }
  export interface ImmAdapterLatexAPIConstructor { new(): ImmAdapterLatexAPI; }
  export interface ImmAdapterLatexAPI {  }
  export interface ImmAdapterSubtreeLogAPIConstructor { new(): ImmAdapterSubtreeLogAPI; }
  export interface ImmAdapterSubtreeLogAPI {  }
  export interface ImmAdapterColonExampleAPIConstructor { new(): ImmAdapterColonExampleAPI; }
  export interface ImmAdapterColonExampleAPI {  }
  export interface ImmAdapterCallAPIConstructor { new(): ImmAdapterCallAPI; }
  export interface ImmAdapterCallAPI {  }
  export interface ImmAdapterFileAPIConstructor { new(): ImmAdapterFileAPI; }
  export interface ImmAdapterFileAPI {  }
  export interface ImmAdapterDirectoryAPIConstructor { new(): ImmAdapterDirectoryAPI; }
  export interface ImmAdapterDirectoryAPI { getFsSubnode(name: string, withPath: boolean): haxorg_wasm.Optional<ImmAdapter>; }
  export interface ImmAdapterSymlinkAPIConstructor { new(): ImmAdapterSymlinkAPI; }
  export interface ImmAdapterSymlinkAPI {  }
  export interface ImmAdapterDocumentFragmentAPIConstructor { new(): ImmAdapterDocumentFragmentAPI; }
  export interface ImmAdapterDocumentFragmentAPI {  }
  export interface ImmAdapterCriticMarkupAPIConstructor { new(): ImmAdapterCriticMarkupAPI; }
  export interface ImmAdapterCriticMarkupAPI {  }
  export interface ImmAdapterListItemAPIConstructor { new(): ImmAdapterListItemAPI; }
  export interface ImmAdapterListItemAPI {  }
  export interface ImmAdapterDocumentOptionsAPIConstructor { new(): ImmAdapterDocumentOptionsAPI; }
  export interface ImmAdapterDocumentOptionsAPI {  }
  export interface ImmAdapterDocumentAPIConstructor { new(): ImmAdapterDocumentAPI; }
  export interface ImmAdapterDocumentAPI {  }
  export interface ImmAdapterFileTargetAPIConstructor { new(): ImmAdapterFileTargetAPI; }
  export interface ImmAdapterFileTargetAPI {  }
  export interface ImmAdapterTextSeparatorAPIConstructor { new(): ImmAdapterTextSeparatorAPI; }
  export interface ImmAdapterTextSeparatorAPI {  }
  export interface ImmAdapterCmdIncludeAPIConstructor { new(): ImmAdapterCmdIncludeAPI; }
  export interface ImmAdapterCmdIncludeAPI {  }
  export interface ImmAdapterDocumentGroupAPIConstructor { new(): ImmAdapterDocumentGroupAPI; }
  export interface ImmAdapterDocumentGroupAPI {  }
  export interface ImmBlockConstructor { new(): ImmBlock; }
  export interface ImmBlock { __eq__(other: ImmBlock): boolean; }
  export interface ImmLineCommandConstructor { new(): ImmLineCommand; }
  export interface ImmLineCommand { __eq__(other: ImmLineCommand): boolean; }
  export interface ImmCmdCustomArgsConstructor { new(): ImmCmdCustomArgs; }
  export interface ImmCmdCustomArgs {
    getKind(): OrgSemKind;
    __eq__(other: ImmCmdCustomArgs): boolean;
    name: ImmBox<string>
    isAttached: boolean
  }
  export interface ImmCmdTblfmConstructor { new(): ImmCmdTblfm; }
  export interface ImmCmdTblfm {
    getKind(): OrgSemKind;
    __eq__(other: ImmCmdTblfm): boolean;
    expr: Tblfm
  }
  export interface ImmCellConstructor { new(): ImmCell; }
  export interface ImmCell {
    getKind(): OrgSemKind;
    __eq__(other: ImmCell): boolean;
    isBlock: boolean
  }
  export interface ImmRowConstructor { new(): ImmRow; }
  export interface ImmRow {
    getKind(): OrgSemKind;
    __eq__(other: ImmRow): boolean;
    cells: ImmVec<ImmIdT<ImmCell>>
    isBlock: boolean
  }
  export interface BlockConstructor { new(): Block; }
  export interface Block {  }
  export interface LineCommandConstructor { new(): LineCommand; }
  export interface LineCommand {  }
  export interface CmdCustomArgsConstructor { new(): CmdCustomArgs; }
  export interface CmdCustomArgs {
    getKind(): OrgSemKind;
    name: string
    isAttached: boolean
  }
  export interface CmdTblfmConstructor { new(): CmdTblfm; }
  export interface CmdTblfm {
    getKind(): OrgSemKind;
    expr: Tblfm
  }
  export interface CellConstructor { new(): Cell; }
  export interface Cell {
    getKind(): OrgSemKind;
    isBlock: boolean
  }
  export interface RowConstructor { new(): Row; }
  export interface Row {
    getKind(): OrgSemKind;
    cells: Vec<Cell>
    isBlock: boolean
  }
  export interface ImmAdapterCmdAPIConstructor { new(): ImmAdapterCmdAPI; }
  export interface ImmAdapterCmdAPI {  }
  export interface ImmAdapterCmdCustomRawAPIConstructor { new(): ImmAdapterCmdCustomRawAPI; }
  export interface ImmAdapterCmdCustomRawAPI {  }
  export interface ImmAdapterCmdCustomTextAPIConstructor { new(): ImmAdapterCmdCustomTextAPI; }
  export interface ImmAdapterCmdCustomTextAPI {  }
  export interface ImmAdapterLinkAPIConstructor { new(): ImmAdapterLinkAPI; }
  export interface ImmAdapterLinkAPI {  }
  export interface ImmAdapterBlockCommentAPIConstructor { new(): ImmAdapterBlockCommentAPI; }
  export interface ImmAdapterBlockCommentAPI {  }
  export interface ImmAdapterParagraphAPIConstructor { new(): ImmAdapterParagraphAPI; }
  export interface ImmAdapterParagraphAPI {  }
  export interface ImmAdapterListAPIConstructor { new(): ImmAdapterListAPI; }
  export interface ImmAdapterListAPI {  }
  export interface ImmSubtreeAdapterConstructor { new(): ImmSubtreeAdapter; }
  export interface ImmSubtreeAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmSubtree>;
    getValue(): ImmSubtreeValueRead;
  }
  export interface ImmNoneAdapterConstructor { new(): ImmNoneAdapter; }
  export interface ImmNoneAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmNone>;
    getValue(): ImmNoneValueRead;
  }
  export interface ImmErrorItemAdapterConstructor { new(): ImmErrorItemAdapter; }
  export interface ImmErrorItemAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmErrorItem>;
    getValue(): ImmErrorItemValueRead;
  }
  export interface ImmErrorGroupAdapterConstructor { new(): ImmErrorGroupAdapter; }
  export interface ImmErrorGroupAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmErrorGroup>;
    getValue(): ImmErrorGroupValueRead;
  }
  export interface ImmStmtListAdapterConstructor { new(): ImmStmtListAdapter; }
  export interface ImmStmtListAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmStmtList>;
    getValue(): ImmStmtListValueRead;
  }
  export interface ImmEmptyAdapterConstructor { new(): ImmEmptyAdapter; }
  export interface ImmEmptyAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmEmpty>;
    getValue(): ImmEmptyValueRead;
  }
  export interface ImmAdapterHashTagAPIConstructor { new(): ImmAdapterHashTagAPI; }
  export interface ImmAdapterHashTagAPI {  }
  export interface ImmAdapterInlineFootnoteAPIConstructor { new(): ImmAdapterInlineFootnoteAPI; }
  export interface ImmAdapterInlineFootnoteAPI {  }
  export interface ImmAdapterSubtreeCompletionAPIConstructor { new(): ImmAdapterSubtreeCompletionAPI; }
  export interface ImmAdapterSubtreeCompletionAPI {  }
  export interface ImmTimeAdapterConstructor { new(): ImmTimeAdapter; }
  export interface ImmTimeAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmTime>;
    getValue(): ImmTimeValueRead;
  }
  export interface ImmTimeRangeAdapterConstructor { new(): ImmTimeRangeAdapter; }
  export interface ImmTimeRangeAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmTimeRange>;
    getValue(): ImmTimeRangeValueRead;
  }
  export interface ImmMacroAdapterConstructor { new(): ImmMacroAdapter; }
  export interface ImmMacroAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmMacro>;
    getValue(): ImmMacroValueRead;
  }
  export interface ImmSymbolAdapterConstructor { new(): ImmSymbolAdapter; }
  export interface ImmSymbolAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmSymbol>;
    getValue(): ImmSymbolValueRead;
  }
  export interface ImmAdapterEscapedAPIConstructor { new(): ImmAdapterEscapedAPI; }
  export interface ImmAdapterEscapedAPI {  }
  export interface ImmAdapterNewlineAPIConstructor { new(): ImmAdapterNewlineAPI; }
  export interface ImmAdapterNewlineAPI {  }
  export interface ImmAdapterSpaceAPIConstructor { new(): ImmAdapterSpaceAPI; }
  export interface ImmAdapterSpaceAPI {  }
  export interface ImmAdapterWordAPIConstructor { new(): ImmAdapterWordAPI; }
  export interface ImmAdapterWordAPI {  }
  export interface ImmAdapterAtMentionAPIConstructor { new(): ImmAdapterAtMentionAPI; }
  export interface ImmAdapterAtMentionAPI {  }
  export interface ImmAdapterRawTextAPIConstructor { new(): ImmAdapterRawTextAPI; }
  export interface ImmAdapterRawTextAPI {  }
  export interface ImmAdapterPunctuationAPIConstructor { new(): ImmAdapterPunctuationAPI; }
  export interface ImmAdapterPunctuationAPI {  }
  export interface ImmAdapterPlaceholderAPIConstructor { new(): ImmAdapterPlaceholderAPI; }
  export interface ImmAdapterPlaceholderAPI {  }
  export interface ImmAdapterBigIdentAPIConstructor { new(): ImmAdapterBigIdentAPI; }
  export interface ImmAdapterBigIdentAPI {  }
  export interface ImmAdapterTextTargetAPIConstructor { new(): ImmAdapterTextTargetAPI; }
  export interface ImmAdapterTextTargetAPI {  }
  export interface ImmAdapterBoldAPIConstructor { new(): ImmAdapterBoldAPI; }
  export interface ImmAdapterBoldAPI {  }
  export interface ImmAdapterUnderlineAPIConstructor { new(): ImmAdapterUnderlineAPI; }
  export interface ImmAdapterUnderlineAPI {  }
  export interface ImmAdapterMonospaceAPIConstructor { new(): ImmAdapterMonospaceAPI; }
  export interface ImmAdapterMonospaceAPI {  }
  export interface ImmAdapterMarkQuoteAPIConstructor { new(): ImmAdapterMarkQuoteAPI; }
  export interface ImmAdapterMarkQuoteAPI {  }
  export interface ImmAdapterRadioTargetAPIConstructor { new(): ImmAdapterRadioTargetAPI; }
  export interface ImmAdapterRadioTargetAPI {  }
  export interface ImmAdapterVerbatimAPIConstructor { new(): ImmAdapterVerbatimAPI; }
  export interface ImmAdapterVerbatimAPI {  }
  export interface ImmAdapterItalicAPIConstructor { new(): ImmAdapterItalicAPI; }
  export interface ImmAdapterItalicAPI {  }
  export interface ImmAdapterStrikeAPIConstructor { new(): ImmAdapterStrikeAPI; }
  export interface ImmAdapterStrikeAPI {  }
  export interface ImmAdapterParAPIConstructor { new(): ImmAdapterParAPI; }
  export interface ImmAdapterParAPI {  }
  export interface ImmLatexAdapterConstructor { new(): ImmLatexAdapter; }
  export interface ImmLatexAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmLatex>;
    getValue(): ImmLatexValueRead;
  }
  export interface ImmSubtreeLogAdapterConstructor { new(): ImmSubtreeLogAdapter; }
  export interface ImmSubtreeLogAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmSubtreeLog>;
    getValue(): ImmSubtreeLogValueRead;
  }
  export interface ImmColonExampleAdapterConstructor { new(): ImmColonExampleAdapter; }
  export interface ImmColonExampleAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmColonExample>;
    getValue(): ImmColonExampleValueRead;
  }
  export interface ImmCallAdapterConstructor { new(): ImmCallAdapter; }
  export interface ImmCallAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmCall>;
    getValue(): ImmCallValueRead;
  }
  export interface ImmFileAdapterConstructor { new(): ImmFileAdapter; }
  export interface ImmFileAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmFile>;
    getValue(): ImmFileValueRead;
  }
  export interface ImmDirectoryAdapterConstructor { new(): ImmDirectoryAdapter; }
  export interface ImmDirectoryAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmDirectory>;
    getValue(): ImmDirectoryValueRead;
  }
  export interface ImmSymlinkAdapterConstructor { new(): ImmSymlinkAdapter; }
  export interface ImmSymlinkAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmSymlink>;
    getValue(): ImmSymlinkValueRead;
  }
  export interface ImmDocumentFragmentAdapterConstructor { new(): ImmDocumentFragmentAdapter; }
  export interface ImmDocumentFragmentAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmDocumentFragment>;
    getValue(): ImmDocumentFragmentValueRead;
  }
  export interface ImmCriticMarkupAdapterConstructor { new(): ImmCriticMarkupAdapter; }
  export interface ImmCriticMarkupAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmCriticMarkup>;
    getValue(): ImmCriticMarkupValueRead;
  }
  export interface ImmListItemAdapterConstructor { new(): ImmListItemAdapter; }
  export interface ImmListItemAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmListItem>;
    getValue(): ImmListItemValueRead;
  }
  export interface ImmDocumentOptionsAdapterConstructor { new(): ImmDocumentOptionsAdapter; }
  export interface ImmDocumentOptionsAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmDocumentOptions>;
    getValue(): ImmDocumentOptionsValueRead;
  }
  export interface ImmDocumentAdapterConstructor { new(): ImmDocumentAdapter; }
  export interface ImmDocumentAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmDocument>;
    getValue(): ImmDocumentValueRead;
  }
  export interface ImmFileTargetAdapterConstructor { new(): ImmFileTargetAdapter; }
  export interface ImmFileTargetAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmFileTarget>;
    getValue(): ImmFileTargetValueRead;
  }
  export interface ImmTextSeparatorAdapterConstructor { new(): ImmTextSeparatorAdapter; }
  export interface ImmTextSeparatorAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmTextSeparator>;
    getValue(): ImmTextSeparatorValueRead;
  }
  export interface ImmCmdIncludeAdapterConstructor { new(): ImmCmdIncludeAdapter; }
  export interface ImmCmdIncludeAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmCmdInclude>;
    getValue(): ImmCmdIncludeValueRead;
  }
  export interface ImmDocumentGroupAdapterConstructor { new(): ImmDocumentGroupAdapter; }
  export interface ImmDocumentGroupAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmDocumentGroup>;
    getValue(): ImmDocumentGroupValueRead;
  }
  export interface ImmBlockCenterConstructor { new(): ImmBlockCenter; }
  export interface ImmBlockCenter {
    getKind(): OrgSemKind;
    __eq__(other: ImmBlockCenter): boolean;
  }
  export interface ImmBlockQuoteConstructor { new(): ImmBlockQuote; }
  export interface ImmBlockQuote {
    getKind(): OrgSemKind;
    __eq__(other: ImmBlockQuote): boolean;
  }
  export interface ImmBlockVerseConstructor { new(): ImmBlockVerse; }
  export interface ImmBlockVerse {
    getKind(): OrgSemKind;
    __eq__(other: ImmBlockVerse): boolean;
  }
  export interface ImmBlockDynamicFallbackConstructor { new(): ImmBlockDynamicFallback; }
  export interface ImmBlockDynamicFallback {
    getKind(): OrgSemKind;
    __eq__(other: ImmBlockDynamicFallback): boolean;
    name: ImmBox<string>
  }
  export interface ImmBlockExampleConstructor { new(): ImmBlockExample; }
  export interface ImmBlockExample {
    getKind(): OrgSemKind;
    __eq__(other: ImmBlockExample): boolean;
  }
  export interface ImmBlockExportConstructor { new(): ImmBlockExport; }
  export interface ImmBlockExport {
    getKind(): OrgSemKind;
    __eq__(other: ImmBlockExport): boolean;
    exporter: ImmBox<string>
    content: ImmBox<string>
  }
  export interface ImmBlockAdmonitionConstructor { new(): ImmBlockAdmonition; }
  export interface ImmBlockAdmonition {
    getKind(): OrgSemKind;
    __eq__(other: ImmBlockAdmonition): boolean;
  }
  export interface ImmBlockCodeEvalResultConstructor { new(): ImmBlockCodeEvalResult; }
  export interface ImmBlockCodeEvalResult {
    getKind(): OrgSemKind;
    __eq__(other: ImmBlockCodeEvalResult): boolean;
    raw: ImmVec<OrgCodeEvalOutput>
    node: ImmIdT<ImmOrg>
  }
  export interface ImmBlockCodeConstructor { new(): ImmBlockCode; }
  export interface ImmBlockCode {
    getKind(): OrgSemKind;
    __eq__(other: ImmBlockCode): boolean;
    lang: ImmBox<haxorg_wasm.Optional<string>>
    exports: BlockCodeExports
    result: ImmVec<ImmIdT<ImmBlockCodeEvalResult>>
    lines: ImmVec<BlockCodeLine>
    cache: boolean
    eval: boolean
    noweb: boolean
    hlines: boolean
    tangle: boolean
    switches: AttrGroup
  }
  export interface ImmTableConstructor { new(): ImmTable; }
  export interface ImmTable {
    getKind(): OrgSemKind;
    __eq__(other: ImmTable): boolean;
    rows: ImmVec<ImmIdT<ImmRow>>
    isBlock: boolean
  }
  export interface ImmAttachedConstructor { new(): ImmAttached; }
  export interface ImmAttached { __eq__(other: ImmAttached): boolean; }
  export interface BlockCenterConstructor { new(): BlockCenter; }
  export interface BlockCenter { getKind(): OrgSemKind; }
  export interface BlockQuoteConstructor { new(): BlockQuote; }
  export interface BlockQuote { getKind(): OrgSemKind; }
  export interface BlockVerseConstructor { new(): BlockVerse; }
  export interface BlockVerse { getKind(): OrgSemKind; }
  export interface BlockDynamicFallbackConstructor { new(): BlockDynamicFallback; }
  export interface BlockDynamicFallback {
    getKind(): OrgSemKind;
    name: string
  }
  export interface BlockExampleConstructor { new(): BlockExample; }
  export interface BlockExample { getKind(): OrgSemKind; }
  export interface BlockExportConstructor { new(): BlockExport; }
  export interface BlockExport {
    getKind(): OrgSemKind;
    getPlacement(): haxorg_wasm.Optional<string>;
    exporter: string
    content: string
  }
  export interface BlockAdmonitionConstructor { new(): BlockAdmonition; }
  export interface BlockAdmonition { getKind(): OrgSemKind; }
  export interface BlockCodeEvalResultConstructor { new(): BlockCodeEvalResult; }
  export interface BlockCodeEvalResult {
    getKind(): OrgSemKind;
    raw: Vec<OrgCodeEvalOutput>
    node: Org
  }
  export interface BlockCodeConstructor { new(): BlockCode; }
  export interface BlockCode {
    getKind(): OrgSemKind;
    getVariable(varname: string): haxorg_wasm.Optional<AttrValue>;
    lang: haxorg_wasm.Optional<string>
    exports: BlockCodeExports
    result: Vec<BlockCodeEvalResult>
    lines: Vec<BlockCodeLine>
    cache: boolean
    eval: boolean
    noweb: boolean
    hlines: boolean
    tangle: boolean
    switches: AttrGroup
  }
  export interface TableConstructor { new(): Table; }
  export interface Table {
    getKind(): OrgSemKind;
    rows: Vec<Row>
    isBlock: boolean
  }
  export interface AttachedConstructor { new(): Attached; }
  export interface Attached {  }
  export interface ImmAdapterLineCommandAPIConstructor { new(): ImmAdapterLineCommandAPI; }
  export interface ImmAdapterLineCommandAPI {  }
  export interface ImmAdapterCmdCustomArgsAPIConstructor { new(): ImmAdapterCmdCustomArgsAPI; }
  export interface ImmAdapterCmdCustomArgsAPI {  }
  export interface ImmAdapterCmdTblfmAPIConstructor { new(): ImmAdapterCmdTblfmAPI; }
  export interface ImmAdapterCmdTblfmAPI {  }
  export interface ImmAdapterBlockAPIConstructor { new(): ImmAdapterBlockAPI; }
  export interface ImmAdapterBlockAPI {  }
  export interface ImmAdapterCellAPIConstructor { new(): ImmAdapterCellAPI; }
  export interface ImmAdapterCellAPI {  }
  export interface ImmAdapterRowAPIConstructor { new(): ImmAdapterRowAPI; }
  export interface ImmAdapterRowAPI {  }
  export interface ImmCmdCustomRawAdapterConstructor { new(): ImmCmdCustomRawAdapter; }
  export interface ImmCmdCustomRawAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmCmdCustomRaw>;
    getValue(): ImmCmdCustomRawValueRead;
  }
  export interface ImmCmdCustomTextAdapterConstructor { new(): ImmCmdCustomTextAdapter; }
  export interface ImmCmdCustomTextAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmCmdCustomText>;
    getValue(): ImmCmdCustomTextValueRead;
  }
  export interface ImmLinkAdapterConstructor { new(): ImmLinkAdapter; }
  export interface ImmLinkAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmLink>;
    getValue(): ImmLinkValueRead;
  }
  export interface ImmBlockCommentAdapterConstructor { new(): ImmBlockCommentAdapter; }
  export interface ImmBlockCommentAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmBlockComment>;
    getValue(): ImmBlockCommentValueRead;
  }
  export interface ImmParagraphAdapterConstructor { new(): ImmParagraphAdapter; }
  export interface ImmParagraphAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmParagraph>;
    getValue(): ImmParagraphValueRead;
  }
  export interface ImmListAdapterConstructor { new(): ImmListAdapter; }
  export interface ImmListAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmList>;
    getValue(): ImmListValueRead;
  }
  export interface ImmHashTagAdapterConstructor { new(): ImmHashTagAdapter; }
  export interface ImmHashTagAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmHashTag>;
    getValue(): ImmHashTagValueRead;
  }
  export interface ImmInlineFootnoteAdapterConstructor { new(): ImmInlineFootnoteAdapter; }
  export interface ImmInlineFootnoteAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmInlineFootnote>;
    getValue(): ImmInlineFootnoteValueRead;
  }
  export interface ImmEscapedAdapterConstructor { new(): ImmEscapedAdapter; }
  export interface ImmEscapedAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmEscaped>;
    getValue(): ImmEscapedValueRead;
  }
  export interface ImmNewlineAdapterConstructor { new(): ImmNewlineAdapter; }
  export interface ImmNewlineAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmNewline>;
    getValue(): ImmNewlineValueRead;
  }
  export interface ImmSpaceAdapterConstructor { new(): ImmSpaceAdapter; }
  export interface ImmSpaceAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmSpace>;
    getValue(): ImmSpaceValueRead;
  }
  export interface ImmWordAdapterConstructor { new(): ImmWordAdapter; }
  export interface ImmWordAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmWord>;
    getValue(): ImmWordValueRead;
  }
  export interface ImmAtMentionAdapterConstructor { new(): ImmAtMentionAdapter; }
  export interface ImmAtMentionAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmAtMention>;
    getValue(): ImmAtMentionValueRead;
  }
  export interface ImmRawTextAdapterConstructor { new(): ImmRawTextAdapter; }
  export interface ImmRawTextAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmRawText>;
    getValue(): ImmRawTextValueRead;
  }
  export interface ImmPunctuationAdapterConstructor { new(): ImmPunctuationAdapter; }
  export interface ImmPunctuationAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmPunctuation>;
    getValue(): ImmPunctuationValueRead;
  }
  export interface ImmPlaceholderAdapterConstructor { new(): ImmPlaceholderAdapter; }
  export interface ImmPlaceholderAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmPlaceholder>;
    getValue(): ImmPlaceholderValueRead;
  }
  export interface ImmBigIdentAdapterConstructor { new(): ImmBigIdentAdapter; }
  export interface ImmBigIdentAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmBigIdent>;
    getValue(): ImmBigIdentValueRead;
  }
  export interface ImmTextTargetAdapterConstructor { new(): ImmTextTargetAdapter; }
  export interface ImmTextTargetAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmTextTarget>;
    getValue(): ImmTextTargetValueRead;
  }
  export interface ImmBoldAdapterConstructor { new(): ImmBoldAdapter; }
  export interface ImmBoldAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmBold>;
    getValue(): ImmBoldValueRead;
  }
  export interface ImmUnderlineAdapterConstructor { new(): ImmUnderlineAdapter; }
  export interface ImmUnderlineAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmUnderline>;
    getValue(): ImmUnderlineValueRead;
  }
  export interface ImmMonospaceAdapterConstructor { new(): ImmMonospaceAdapter; }
  export interface ImmMonospaceAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmMonospace>;
    getValue(): ImmMonospaceValueRead;
  }
  export interface ImmMarkQuoteAdapterConstructor { new(): ImmMarkQuoteAdapter; }
  export interface ImmMarkQuoteAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmMarkQuote>;
    getValue(): ImmMarkQuoteValueRead;
  }
  export interface ImmRadioTargetAdapterConstructor { new(): ImmRadioTargetAdapter; }
  export interface ImmRadioTargetAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmRadioTarget>;
    getValue(): ImmRadioTargetValueRead;
  }
  export interface ImmVerbatimAdapterConstructor { new(): ImmVerbatimAdapter; }
  export interface ImmVerbatimAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmVerbatim>;
    getValue(): ImmVerbatimValueRead;
  }
  export interface ImmItalicAdapterConstructor { new(): ImmItalicAdapter; }
  export interface ImmItalicAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmItalic>;
    getValue(): ImmItalicValueRead;
  }
  export interface ImmStrikeAdapterConstructor { new(): ImmStrikeAdapter; }
  export interface ImmStrikeAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmStrike>;
    getValue(): ImmStrikeValueRead;
  }
  export interface ImmParAdapterConstructor { new(): ImmParAdapter; }
  export interface ImmParAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmPar>;
    getValue(): ImmParValueRead;
  }
  export interface ImmCmdCaptionConstructor { new(): ImmCmdCaption; }
  export interface ImmCmdCaption {
    getKind(): OrgSemKind;
    __eq__(other: ImmCmdCaption): boolean;
    text: ImmIdT<ImmParagraph>
  }
  export interface ImmCmdColumnsConstructor { new(): ImmCmdColumns; }
  export interface ImmCmdColumns {
    getKind(): OrgSemKind;
    __eq__(other: ImmCmdColumns): boolean;
    view: ColumnView
  }
  export interface ImmCmdNameConstructor { new(): ImmCmdName; }
  export interface ImmCmdName {
    getKind(): OrgSemKind;
    __eq__(other: ImmCmdName): boolean;
    name: ImmBox<string>
  }
  export interface ImmCmdCallConstructor { new(): ImmCmdCall; }
  export interface ImmCmdCall {
    getKind(): OrgSemKind;
    __eq__(other: ImmCmdCall): boolean;
    name: ImmBox<string>
    fileName: ImmBox<haxorg_wasm.Optional<string>>
    insideHeaderAttrs: AttrGroup
    callAttrs: AttrGroup
    endHeaderAttrs: AttrGroup
    result: ImmVec<ImmIdT<ImmBlockCodeEvalResult>>
  }
  export interface ImmCmdAttrConstructor { new(): ImmCmdAttr; }
  export interface ImmCmdAttr {
    getKind(): OrgSemKind;
    __eq__(other: ImmCmdAttr): boolean;
    target: ImmBox<string>
  }
  export interface ImmCmdExportConstructor { new(): ImmCmdExport; }
  export interface ImmCmdExport {
    getKind(): OrgSemKind;
    __eq__(other: ImmCmdExport): boolean;
    exporter: ImmBox<string>
    content: ImmBox<string>
  }
  export interface CmdCaptionConstructor { new(): CmdCaption; }
  export interface CmdCaption {
    getKind(): OrgSemKind;
    text: Paragraph
  }
  export interface CmdColumnsConstructor { new(): CmdColumns; }
  export interface CmdColumns {
    getKind(): OrgSemKind;
    view: ColumnView
  }
  export interface CmdNameConstructor { new(): CmdName; }
  export interface CmdName {
    getKind(): OrgSemKind;
    name: string
  }
  export interface CmdCallConstructor { new(): CmdCall; }
  export interface CmdCall {
    getKind(): OrgSemKind;
    name: string
    fileName: haxorg_wasm.Optional<string>
    insideHeaderAttrs: AttrGroup
    callAttrs: AttrGroup
    endHeaderAttrs: AttrGroup
    result: Vec<BlockCodeEvalResult>
  }
  export interface CmdAttrConstructor { new(): CmdAttr; }
  export interface CmdAttr {
    getKind(): OrgSemKind;
    target: string
  }
  export interface CmdExportConstructor { new(): CmdExport; }
  export interface CmdExport {
    getKind(): OrgSemKind;
    exporter: string
    content: string
  }
  export interface ImmAdapterAttachedAPIConstructor { new(): ImmAdapterAttachedAPI; }
  export interface ImmAdapterAttachedAPI {  }
  export interface ImmCmdCustomArgsAdapterConstructor { new(): ImmCmdCustomArgsAdapter; }
  export interface ImmCmdCustomArgsAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmCmdCustomArgs>;
    getValue(): ImmCmdCustomArgsValueRead;
  }
  export interface ImmCmdTblfmAdapterConstructor { new(): ImmCmdTblfmAdapter; }
  export interface ImmCmdTblfmAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmCmdTblfm>;
    getValue(): ImmCmdTblfmValueRead;
  }
  export interface ImmAdapterBlockCenterAPIConstructor { new(): ImmAdapterBlockCenterAPI; }
  export interface ImmAdapterBlockCenterAPI {  }
  export interface ImmAdapterBlockQuoteAPIConstructor { new(): ImmAdapterBlockQuoteAPI; }
  export interface ImmAdapterBlockQuoteAPI {  }
  export interface ImmAdapterBlockVerseAPIConstructor { new(): ImmAdapterBlockVerseAPI; }
  export interface ImmAdapterBlockVerseAPI {  }
  export interface ImmAdapterBlockExampleAPIConstructor { new(): ImmAdapterBlockExampleAPI; }
  export interface ImmAdapterBlockExampleAPI {  }
  export interface ImmAdapterInlineExportAPIConstructor { new(): ImmAdapterInlineExportAPI; }
  export interface ImmAdapterInlineExportAPI {  }
  export interface ImmAdapterCmdExportAPIConstructor { new(): ImmAdapterCmdExportAPI; }
  export interface ImmAdapterCmdExportAPI {  }
  export interface ImmAdapterBlockExportAPIConstructor { new(): ImmAdapterBlockExportAPI; }
  export interface ImmAdapterBlockExportAPI {  }
  export interface ImmAdapterBlockDynamicFallbackAPIConstructor { new(): ImmAdapterBlockDynamicFallbackAPI; }
  export interface ImmAdapterBlockDynamicFallbackAPI {  }
  export interface ImmAdapterBlockAdmonitionAPIConstructor { new(): ImmAdapterBlockAdmonitionAPI; }
  export interface ImmAdapterBlockAdmonitionAPI {  }
  export interface ImmAdapterBlockCodeEvalResultAPIConstructor { new(): ImmAdapterBlockCodeEvalResultAPI; }
  export interface ImmAdapterBlockCodeEvalResultAPI {  }
  export interface ImmAdapterBlockCodeAPIConstructor { new(): ImmAdapterBlockCodeAPI; }
  export interface ImmAdapterBlockCodeAPI {  }
  export interface ImmAdapterTableAPIConstructor { new(): ImmAdapterTableAPI; }
  export interface ImmAdapterTableAPI {  }
  export interface ImmCellAdapterConstructor { new(): ImmCellAdapter; }
  export interface ImmCellAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmCell>;
    getValue(): ImmCellValueRead;
  }
  export interface ImmRowAdapterConstructor { new(): ImmRowAdapter; }
  export interface ImmRowAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmRow>;
    getValue(): ImmRowValueRead;
  }
  export interface ImmAdapterCmdCaptionAPIConstructor { new(): ImmAdapterCmdCaptionAPI; }
  export interface ImmAdapterCmdCaptionAPI {  }
  export interface ImmAdapterCmdColumnsAPIConstructor { new(): ImmAdapterCmdColumnsAPI; }
  export interface ImmAdapterCmdColumnsAPI {  }
  export interface ImmAdapterCmdNameAPIConstructor { new(): ImmAdapterCmdNameAPI; }
  export interface ImmAdapterCmdNameAPI {  }
  export interface ImmAdapterCmdCallAPIConstructor { new(): ImmAdapterCmdCallAPI; }
  export interface ImmAdapterCmdCallAPI {  }
  export interface ImmAdapterCmdResultsAPIConstructor { new(): ImmAdapterCmdResultsAPI; }
  export interface ImmAdapterCmdResultsAPI {  }
  export interface ImmAdapterCmdAttrAPIConstructor { new(): ImmAdapterCmdAttrAPI; }
  export interface ImmAdapterCmdAttrAPI {  }
  export interface ImmBlockCenterAdapterConstructor { new(): ImmBlockCenterAdapter; }
  export interface ImmBlockCenterAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmBlockCenter>;
    getValue(): ImmBlockCenterValueRead;
  }
  export interface ImmBlockQuoteAdapterConstructor { new(): ImmBlockQuoteAdapter; }
  export interface ImmBlockQuoteAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmBlockQuote>;
    getValue(): ImmBlockQuoteValueRead;
  }
  export interface ImmBlockVerseAdapterConstructor { new(): ImmBlockVerseAdapter; }
  export interface ImmBlockVerseAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmBlockVerse>;
    getValue(): ImmBlockVerseValueRead;
  }
  export interface ImmBlockExampleAdapterConstructor { new(): ImmBlockExampleAdapter; }
  export interface ImmBlockExampleAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmBlockExample>;
    getValue(): ImmBlockExampleValueRead;
  }
  export interface ImmInlineExportAdapterConstructor { new(): ImmInlineExportAdapter; }
  export interface ImmInlineExportAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmInlineExport>;
    getValue(): ImmInlineExportValueRead;
  }
  export interface ImmCmdExportAdapterConstructor { new(): ImmCmdExportAdapter; }
  export interface ImmCmdExportAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmCmdExport>;
    getValue(): ImmCmdExportValueRead;
  }
  export interface ImmBlockExportAdapterConstructor { new(): ImmBlockExportAdapter; }
  export interface ImmBlockExportAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmBlockExport>;
    getValue(): ImmBlockExportValueRead;
  }
  export interface ImmBlockDynamicFallbackAdapterConstructor { new(): ImmBlockDynamicFallbackAdapter; }
  export interface ImmBlockDynamicFallbackAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmBlockDynamicFallback>;
    getValue(): ImmBlockDynamicFallbackValueRead;
  }
  export interface ImmBlockAdmonitionAdapterConstructor { new(): ImmBlockAdmonitionAdapter; }
  export interface ImmBlockAdmonitionAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmBlockAdmonition>;
    getValue(): ImmBlockAdmonitionValueRead;
  }
  export interface ImmBlockCodeEvalResultAdapterConstructor { new(): ImmBlockCodeEvalResultAdapter; }
  export interface ImmBlockCodeEvalResultAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmBlockCodeEvalResult>;
    getValue(): ImmBlockCodeEvalResultValueRead;
  }
  export interface ImmBlockCodeAdapterConstructor { new(): ImmBlockCodeAdapter; }
  export interface ImmBlockCodeAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmBlockCode>;
    getValue(): ImmBlockCodeValueRead;
  }
  export interface ImmTableAdapterConstructor { new(): ImmTableAdapter; }
  export interface ImmTableAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmTable>;
    getValue(): ImmTableValueRead;
  }
  export interface ImmCmdCaptionAdapterConstructor { new(): ImmCmdCaptionAdapter; }
  export interface ImmCmdCaptionAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmCmdCaption>;
    getValue(): ImmCmdCaptionValueRead;
  }
  export interface ImmCmdColumnsAdapterConstructor { new(): ImmCmdColumnsAdapter; }
  export interface ImmCmdColumnsAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmCmdColumns>;
    getValue(): ImmCmdColumnsValueRead;
  }
  export interface ImmCmdNameAdapterConstructor { new(): ImmCmdNameAdapter; }
  export interface ImmCmdNameAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmCmdName>;
    getValue(): ImmCmdNameValueRead;
  }
  export interface ImmCmdCallAdapterConstructor { new(): ImmCmdCallAdapter; }
  export interface ImmCmdCallAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmCmdCall>;
    getValue(): ImmCmdCallValueRead;
  }
  export interface ImmCmdAttrAdapterConstructor { new(): ImmCmdAttrAdapter; }
  export interface ImmCmdAttrAdapter {
    ImmAdapterT(other: ImmAdapter): ImmAdapterT<ImmCmdAttr>;
    getValue(): ImmCmdAttrValueRead;
  }
  export enum CheckboxState {
    None,
    Done,
    Empty,
    Partial,
  }
  export enum SubtreeTodoSource {
    Checkbox,
    Todo,
    Both,
  }
  export enum ListFormattingMode {
    None,
    Table1D1Col,
    Table1D2Col,
    Table2DColFirst,
  }
  export enum InitialSubtreeVisibility {
    Overview,
    Content,
    ShowAll,
    Show2Levels,
    Show3Levels,
    Show4Levels,
    Show5Levels,
    ShowEverything,
  }
  export enum BlockCodeResults { Replace, }
  export enum BlockCodeExports {
    None,
    Both,
    Code,
    Results,
  }
  export enum OrgSpecName {
    Unnamed,
    Result,
    Year,
    Day,
    Clock,
    Repeater,
    Warn,
    Zone,
    Link,
    Tags,
    Tag,
    State,
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
    Importance,
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
  }
  export enum OrgNodeKind {
    None,
    Document,
    Empty,
    InlineStmtList,
    StmtList,
    Checkbox,
    List,
    Bullet,
    ListItem,
    ListTag,
    Counter,
    File,
    ColonExample,
    TextSeparator,
    Paragraph,
    TableRow,
    TableCell,
    Table,
    InlineFootnote,
    Footnote,
    Cmd,
    Attrs,
    AttrValue,
    AttrLisp,
    CmdTitle,
    CmdAuthor,
    CmdCreator,
    CmdInclude,
    CmdLanguage,
    CmdAttr,
    CmdStartup,
    CmdName,
    CmdCustomTextCommand,
    CmdCustomArgsCommand,
    CmdCustomRawCommand,
    CmdResults,
    CmdHeader,
    CmdOptions,
    CmdTblfm,
    CmdCaption,
    CmdResult,
    CmdCallCode,
    CmdFlag,
    CmdLatexClass,
    CmdLatexHeader,
    CmdLatexCompiler,
    CmdLatexClassOptions,
    CmdHtmlHead,
    CmdColumns,
    CmdPropertyArgs,
    CmdPropertyText,
    CmdPropertyRaw,
    CmdFiletags,
    CmdKeywords,
    BlockVerbatimMultiline,
    CodeLine,
    CodeText,
    CodeTangle,
    CodeCallout,
    BlockCode,
    BlockQuote,
    BlockComment,
    BlockCenter,
    BlockVerse,
    BlockExample,
    BlockExport,
    BlockDetails,
    BlockSummary,
    BlockDynamicFallback,
    BigIdent,
    Bold,
    ErrorWrap,
    ErrorToken,
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
    InlineMath,
    DisplayMath,
    Space,
    Punctuation,
    Colon,
    Word,
    Escaped,
    Newline,
    RawLink,
    Link,
    Macro,
    Symbol,
    StaticActiveTime,
    StaticInactiveTime,
    DynamicActiveTime,
    DynamicInactiveTime,
    TimeRange,
    SimpleTime,
    HashTag,
    MetaSymbol,
    AtMention,
    Placeholder,
    RadioTarget,
    Target,
    SrcInlineCode,
    InlineCallCode,
    InlineExport,
    InlineComment,
    RawText,
    SubtreeDescription,
    SubtreeUrgency,
    DrawerLogbook,
    Drawer,
    DrawerPropertyList,
    DrawerProperty,
    Subtree,
    SubtreeTimes,
    SubtreeStars,
    SubtreeCompletion,
    SubtreeImportance,
  }
  export enum OrgTokenKind {
    Ampersand,
    AngleBegin,
    AngleEnd,
    AnyPunct,
    Asterisk,
    At,
    Backtick,
    BigIdent,
    BoldBegin,
    BoldEnd,
    BoldUnknown,
    BraceBegin,
    BraceEnd,
    Checkbox,
    Circumflex,
    CmdAdmonitionEnd,
    CmdAttr,
    CmdAuthor,
    CmdBindRaw,
    CmdCall,
    CmdCaption,
    CmdCategoryRaw,
    CmdCell,
    CmdCellBegin,
    CmdCellEnd,
    CmdCenterBegin,
    CmdCenterEnd,
    CmdColonIdent,
    CmdColumns,
    CmdCommentBegin,
    CmdCommentEnd,
    CmdConstants,
    CmdContentBegin,
    CmdContentEnd,
    CmdCreator,
    CmdCustomRaw,
    CmdDateRaw,
    CmdDescription,
    CmdDrawersRaw,
    CmdDynamicBegin,
    CmdDynamicBlockBegin,
    CmdDynamicBlockEnd,
    CmdDynamicEnd,
    CmdEmailRaw,
    CmdExampleBegin,
    CmdExampleEnd,
    CmdExampleLine,
    CmdExcludeTagsRaw,
    CmdExportBegin,
    CmdExportEnd,
    CmdExportLine,
    CmdFiletags,
    CmdFlag,
    CmdHeader,
    CmdHtmlHeadRaw,
    CmdInclude,
    CmdLanguage,
    CmdLatexClass,
    CmdLatexClassOptions,
    CmdLatexCompiler,
    CmdLatexHeader,
    CmdLatexHeaderExtraRaw,
    CmdLinkRaw,
    CmdMacroRaw,
    CmdName,
    CmdOptions,
    CmdPrefix,
    CmdPrioritiesRaw,
    CmdPropertyArgs,
    CmdPropertyRaw,
    CmdPropertyText,
    CmdQuoteBegin,
    CmdQuoteEnd,
    CmdRawArg,
    CmdResults,
    CmdRow,
    CmdRowBegin,
    CmdRowEnd,
    CmdSelectTagsRaw,
    CmdSeqTodoRaw,
    CmdKeywordsRaw,
    CmdSetupfileRaw,
    CmdSrcBegin,
    CmdSrcEnd,
    CmdStartup,
    CmdTableBegin,
    CmdTableEnd,
    CmdTagsRaw,
    CmdTblfm,
    CmdTitle,
    CmdVerseBegin,
    CmdVerseEnd,
    Colon,
    ColonArgumentsProperty,
    ColonEnd,
    ColonExampleLine,
    ColonLiteralProperty,
    ColonLogbook,
    ColonProperties,
    ColonPropertyText,
    Comma,
    Comment,
    CriticAddBegin,
    CriticAddEnd,
    CriticCommentBegin,
    CriticCommentEnd,
    CriticDeleteBegin,
    CriticDeleteEnd,
    CriticHighlightBegin,
    CriticHighlightEnd,
    CriticReplaceBegin,
    CriticReplaceEnd,
    CriticReplaceMiddle,
    CurlyBegin,
    CurlyEnd,
    Date,
    Dedent,
    Dollar,
    DoubleAngleBegin,
    DoubleAngleEnd,
    DoubleColon,
    DoubleDash,
    DoubleHash,
    DoubleQuote,
    DoubleSlash,
    DynamicTimeContent,
    EndOfFile,
    Equals,
    Escaped,
    Exclamation,
    FootnoteInlineBegin,
    FootnoteLinked,
    ForwardSlash,
    HashIdent,
    HashTagBegin,
    Indent,
    InlineExportBackend,
    InlineExportContent,
    ItalicBegin,
    ItalicEnd,
    ItalicUnknown,
    LatexInlineRaw,
    LatexParBegin,
    LatexParEnd,
    LeadingMinus,
    LeadingNumber,
    LeadingPipe,
    LeadingPlus,
    LeadingSpace,
    LineCommand,
    LinkBegin,
    LinkDescriptionBegin,
    LinkDescriptionEnd,
    LinkEnd,
    LinkFull,
    LinkProtocol,
    LinkProtocolAttachment,
    LinkProtocolCustomId,
    LinkProtocolFile,
    LinkProtocolHttp,
    LinkProtocolId,
    LinkProtocolInternal,
    LinkProtocolTitle,
    LinkSplit,
    LinkTarget,
    LinkTargetBegin,
    LinkTargetEnd,
    LinkTargetFile,
    ListBegin,
    ListEnd,
    ListItemBegin,
    ListItemEnd,
    LongNewline,
    MediumNewline,
    Minus,
    MiscUnicode,
    MonospaceBegin,
    MonospaceEnd,
    MonospaceUnknown,
    Newline,
    Number,
    ParBegin,
    ParEnd,
    Percent,
    Pipe,
    Placeholder,
    Plus,
    Punctuation,
    RawText,
    SameIndent,
    Semicolon,
    SingleQuote,
    SrcContent,
    StmtListBegin,
    StmtListEnd,
    StrikeBegin,
    StrikeEnd,
    StrikeUnknown,
    SubtreeCompletion,
    SubtreePriority,
    SubtreeStars,
    Symbol,
    TableSeparator,
    TextSeparator,
    TextSrcBegin,
    Tilda,
    Time,
    TimeArrow,
    TimeRepeaterDuration,
    TimeRepeaterSpec,
    TimeWarnPeriod,
    TrailingPipe,
    TreeClock,
    TreeTime,
    TripleAngleBegin,
    TripleAngleEnd,
    Underline,
    UnderlineBegin,
    UnderlineEnd,
    UnderlineUnknown,
    Unknown,
    VerbatimBegin,
    VerbatimEnd,
    VerbatimUnknown,
    Whitespace,
    Word,
  }
  export enum OrgJsonKind {
    Null,
    Object,
    Array,
    String,
    Boolean,
    Int,
    Float,
  }
  export enum OrgSemKind {
    None,
    ErrorItem,
    ErrorGroup,
    StmtList,
    Empty,
    CmdCaption,
    CmdColumns,
    CmdName,
    CmdCustomArgs,
    CmdCustomRaw,
    CmdCustomText,
    CmdCall,
    CmdTblfm,
    HashTag,
    InlineFootnote,
    InlineExport,
    Time,
    TimeRange,
    Macro,
    Symbol,
    Escaped,
    Newline,
    Space,
    Word,
    AtMention,
    RawText,
    Punctuation,
    Placeholder,
    BigIdent,
    TextTarget,
    Bold,
    Underline,
    Monospace,
    MarkQuote,
    Verbatim,
    Italic,
    Strike,
    Par,
    RadioTarget,
    Latex,
    Link,
    BlockCenter,
    BlockQuote,
    BlockComment,
    BlockVerse,
    BlockDynamicFallback,
    BlockExample,
    BlockExport,
    BlockAdmonition,
    BlockCodeEvalResult,
    BlockCode,
    SubtreeLog,
    Subtree,
    Cell,
    Row,
    Table,
    Paragraph,
    ColonExample,
    CmdAttr,
    CmdExport,
    Call,
    List,
    ListItem,
    DocumentOptions,
    DocumentFragment,
    CriticMarkup,
    Document,
    FileTarget,
    TextSeparator,
    DocumentGroup,
    File,
    Directory,
    Symlink,
    CmdInclude,
  }
  export enum OrgAstTrackingGroupKind {
    RadioTarget,
    Single = 1,
    TrackedHashtag = 2,
  }
  newSemTimeStatic(breakdown: UserTimeBreakdown, isActive: boolean): Time;
  parseFile(file: string, opts: OrgParseParameters): Org;
  parseString(text: string): Org;
  parseStringOpts(text: string, opts: OrgParseParameters): Org;
  parseDirectoryOpts(path: string, opts: OrgDirectoryParseParameters): haxorg_wasm.Optional<Org>;
  parseFileWithIncludes(file: string, opts: OrgDirectoryParseParameters): File;
  initImmutableAstContext(): StdShared_ptr<ImmAstContext>;
  asOneNode(arg: Org): Org;
  formatToString(arg: Org): string;
  exportToYamlString(node: Org, opts: OrgYamlExportOpts): string;
  exportToYamlFile(node: Org, path: string, opts: OrgYamlExportOpts): void;
  exportToJsonString(node: Org): string;
  exportToJsonFile(node: Org, path: string): void;
  readProtobufFile(file: string): Document;
  exportToProtobufFile(doc: Document, file: string): void;
  exportToTreeString(node: Org, opts: OrgTreeExportOpts): string;
  exportToTreeFile(node: Org, path: string, opts: OrgTreeExportOpts): void;
  getAstTrackingMap(nodes: Vec<Org>): AstTrackingMap;
  getSubnodeGroups(node: Org, map: AstTrackingMap): Vec<AstTrackingGroup>;
  annotateSequence(groups: Vec<SequenceSegmentGroup>, first: number, last: number): Vec<SequenceAnnotation>;
}
/* clang-format on */