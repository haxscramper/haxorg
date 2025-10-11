/* clang-format off */
import * as haxorg_wasm from "./haxorg_utility_types";
export interface haxorg_wasm_module_auto {
  UserTimeBreakdown: UserTimeBreakdownConstructor;
  UserTime: UserTimeConstructor;
  ParseLineCol: ParseLineColConstructor;
  OperationsTracer: OperationsTracerConstructor;
  OrgJson: OrgJsonConstructor;
  Org: OrgConstructor;
  ImmId: ImmIdConstructor;
  ImmOrg: ImmOrgConstructor;
  ImmPathStep: ImmPathStepConstructor;
  ImmPath: ImmPathConstructor;
  ImmUniqId: ImmUniqIdConstructor;
  ImmAstReplaceEpoch: ImmAstReplaceEpochConstructor;
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
  GraphMapConfig: GraphMapConfigConstructor;
  GraphMapGraphState: GraphMapGraphStateConstructor;
  SourceLocation: SourceLocationConstructor;
  LispCode: LispCodeConstructor;
  LispCodeCall: LispCodeCallConstructor;
  LispCodeList: LispCodeListConstructor;
  LispCodeKeyValue: LispCodeKeyValueConstructor;
  LispCodeNumber: LispCodeNumberConstructor;
  LispCodeText: LispCodeTextConstructor;
  LispCodeIdent: LispCodeIdentConstructor;
  LispCodeBoolean: LispCodeBooleanConstructor;
  LispCodeReal: LispCodeRealConstructor;
  LispCodeKind: {
    Call: LispCodeKind,
    List: LispCodeKind,
    KeyValue: LispCodeKind,
    Number: LispCodeKind,
    Text: LispCodeKind,
    Ident: LispCodeKind,
    Boolean: LispCodeKind,
    Real: LispCodeKind,
  }
  format_LispCodeKind(value: LispCodeKind): string;
  Tblfm: TblfmConstructor;
  TblfmExpr: TblfmExprConstructor;
  TblfmExprAxisRef: TblfmExprAxisRefConstructor;
  TblfmExprAxisRefPosition: TblfmExprAxisRefPositionConstructor;
  TblfmExprAxisRefPositionIndex: TblfmExprAxisRefPositionIndexConstructor;
  TblfmExprAxisRefPositionName: TblfmExprAxisRefPositionNameConstructor;
  TblfmExprAxisRefPositionKind: {
    Index: TblfmExprAxisRefPositionKind,
    Name: TblfmExprAxisRefPositionKind,
  }
  format_TblfmExprAxisRefPositionKind(value: TblfmExprAxisRefPositionKind): string;
  TblfmExprAxisName: TblfmExprAxisNameConstructor;
  TblfmExprIntLiteral: TblfmExprIntLiteralConstructor;
  TblfmExprFloatLiteral: TblfmExprFloatLiteralConstructor;
  TblfmExprRangeRef: TblfmExprRangeRefConstructor;
  TblfmExprCall: TblfmExprCallConstructor;
  TblfmExprElisp: TblfmExprElispConstructor;
  TblfmExprKind: {
    AxisRef: TblfmExprKind,
    AxisName: TblfmExprKind,
    IntLiteral: TblfmExprKind,
    FloatLiteral: TblfmExprKind,
    RangeRef: TblfmExprKind,
    Call: TblfmExprKind,
    Elisp: TblfmExprKind,
  }
  format_TblfmExprKind(value: TblfmExprKind): string;
  TblfmAssign: TblfmAssignConstructor;
  TblfmAssignFlag: {
    CellLeftAlign: TblfmAssignFlag,
    CellRightAlign: TblfmAssignFlag,
    CellCenterAlign: TblfmAssignFlag,
    CellNumber: TblfmAssignFlag,
    CellExponential: TblfmAssignFlag,
    CellFloating: TblfmAssignFlag,
    CellUnformat: TblfmAssignFlag,
    CellText: TblfmAssignFlag,
    CellBool: TblfmAssignFlag,
    CellDecimal: TblfmAssignFlag,
    CellPercentage: TblfmAssignFlag,
    CellHours: TblfmAssignFlag,
    CellZero: TblfmAssignFlag,
    CellMarkInvalid: TblfmAssignFlag,
    CellQuote: TblfmAssignFlag,
  }
  format_TblfmAssignFlag(value: TblfmAssignFlag): string;
  AttrValue: AttrValueConstructor;
  AttrValueDimensionSpan: AttrValueDimensionSpanConstructor;
  AttrValueTextValue: AttrValueTextValueConstructor;
  AttrValueFileReference: AttrValueFileReferenceConstructor;
  AttrValueLispValue: AttrValueLispValueConstructor;
  AttrValueKind: {
    TextValue: AttrValueKind,
    FileReference: AttrValueKind,
    LispValue: AttrValueKind,
  }
  format_AttrValueKind(value: AttrValueKind): string;
  HashTagFlat: HashTagFlatConstructor;
  TodoKeyword: TodoKeywordConstructor;
  TodoKeywordTransition: {
    None: TodoKeywordTransition,
    NoteWithTimestamp: TodoKeywordTransition,
    Timestamp: TodoKeywordTransition,
  }
  format_TodoKeywordTransition(value: TodoKeywordTransition): string;
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
  LinkTargetKind: {
    Raw: LinkTargetKind,
    Id: LinkTargetKind,
    CustomId: LinkTargetKind,
    SubtreeTitle: LinkTargetKind,
    Person: LinkTargetKind,
    UserProtocol: LinkTargetKind,
    Internal: LinkTargetKind,
    Footnote: LinkTargetKind,
    File: LinkTargetKind,
    Attachment: LinkTargetKind,
  }
  format_LinkTargetKind(value: LinkTargetKind): string;
  SubtreeLogHead: SubtreeLogHeadConstructor;
  SubtreeLogHeadPriority: SubtreeLogHeadPriorityConstructor;
  SubtreeLogHeadPriorityAction: {
    Added: SubtreeLogHeadPriorityAction,
    Removed: SubtreeLogHeadPriorityAction,
    Changed: SubtreeLogHeadPriorityAction,
  }
  format_SubtreeLogHeadPriorityAction(value: SubtreeLogHeadPriorityAction): string;
  SubtreeLogHeadNote: SubtreeLogHeadNoteConstructor;
  SubtreeLogHeadRefile: SubtreeLogHeadRefileConstructor;
  SubtreeLogHeadClock: SubtreeLogHeadClockConstructor;
  SubtreeLogHeadState: SubtreeLogHeadStateConstructor;
  SubtreeLogHeadDeadline: SubtreeLogHeadDeadlineConstructor;
  SubtreeLogHeadSchedule: SubtreeLogHeadScheduleConstructor;
  SubtreeLogHeadTag: SubtreeLogHeadTagConstructor;
  SubtreeLogHeadUnknown: SubtreeLogHeadUnknownConstructor;
  SubtreeLogHeadKind: {
    Priority: SubtreeLogHeadKind,
    Note: SubtreeLogHeadKind,
    Refile: SubtreeLogHeadKind,
    Clock: SubtreeLogHeadKind,
    State: SubtreeLogHeadKind,
    Deadline: SubtreeLogHeadKind,
    Schedule: SubtreeLogHeadKind,
    Tag: SubtreeLogHeadKind,
    Unknown: SubtreeLogHeadKind,
  }
  format_SubtreeLogHeadKind(value: SubtreeLogHeadKind): string;
  SubtreeCompletion: SubtreeCompletionConstructor;
  AttrList: AttrListConstructor;
  AttrGroup: AttrGroupConstructor;
  OrgCodeEvalInput: OrgCodeEvalInputConstructor;
  OrgCodeEvalInputVar: OrgCodeEvalInputVarConstructor;
  OrgCodeEvalInputResultType: {
    None: OrgCodeEvalInputResultType,
    Table: OrgCodeEvalInputResultType,
    List: OrgCodeEvalInputResultType,
    Scalar: OrgCodeEvalInputResultType,
    SaveFile: OrgCodeEvalInputResultType,
  }
  format_OrgCodeEvalInputResultType(value: OrgCodeEvalInputResultType): string;
  OrgCodeEvalInputResultFormat: {
    None: OrgCodeEvalInputResultFormat,
    Raw: OrgCodeEvalInputResultFormat,
    Code: OrgCodeEvalInputResultFormat,
    Drawer: OrgCodeEvalInputResultFormat,
    ExportType: OrgCodeEvalInputResultFormat,
    Link: OrgCodeEvalInputResultFormat,
  }
  format_OrgCodeEvalInputResultFormat(value: OrgCodeEvalInputResultFormat): string;
  OrgCodeEvalInputResultHandling: {
    None: OrgCodeEvalInputResultHandling,
    Replace: OrgCodeEvalInputResultHandling,
    Silent: OrgCodeEvalInputResultHandling,
    Discard: OrgCodeEvalInputResultHandling,
    Append: OrgCodeEvalInputResultHandling,
    Prepend: OrgCodeEvalInputResultHandling,
  }
  format_OrgCodeEvalInputResultHandling(value: OrgCodeEvalInputResultHandling): string;
  OrgCodeEvalOutput: OrgCodeEvalOutputConstructor;
  ColumnView: ColumnViewConstructor;
  ColumnViewSummary: ColumnViewSummaryConstructor;
  ColumnViewSummaryCheckboxAggregate: ColumnViewSummaryCheckboxAggregateConstructor;
  ColumnViewSummaryCheckboxAggregateKind: {
    IfAllNested: ColumnViewSummaryCheckboxAggregateKind,
    AggregateFractionRec: ColumnViewSummaryCheckboxAggregateKind,
    AggregatePercentRec: ColumnViewSummaryCheckboxAggregateKind,
  }
  format_ColumnViewSummaryCheckboxAggregateKind(value: ColumnViewSummaryCheckboxAggregateKind): string;
  ColumnViewSummaryMathAggregate: ColumnViewSummaryMathAggregateConstructor;
  ColumnViewSummaryMathAggregateKind: {
    Min: ColumnViewSummaryMathAggregateKind,
    Max: ColumnViewSummaryMathAggregateKind,
    Mean: ColumnViewSummaryMathAggregateKind,
    Sum: ColumnViewSummaryMathAggregateKind,
    LowHighEst: ColumnViewSummaryMathAggregateKind,
  }
  format_ColumnViewSummaryMathAggregateKind(value: ColumnViewSummaryMathAggregateKind): string;
  ColumnViewSummaryKind: {
    CheckboxAggregate: ColumnViewSummaryKind,
    MathAggregate: ColumnViewSummaryKind,
  }
  format_ColumnViewSummaryKind(value: ColumnViewSummaryKind): string;
  ColumnViewColumn: ColumnViewColumnConstructor;
  BlockCodeLine: BlockCodeLineConstructor;
  BlockCodeLinePart: BlockCodeLinePartConstructor;
  BlockCodeLinePartRaw: BlockCodeLinePartRawConstructor;
  BlockCodeLinePartCallout: BlockCodeLinePartCalloutConstructor;
  BlockCodeLinePartTangle: BlockCodeLinePartTangleConstructor;
  BlockCodeLinePartKind: {
    Raw: BlockCodeLinePartKind,
    Callout: BlockCodeLinePartKind,
    Tangle: BlockCodeLinePartKind,
  }
  format_BlockCodeLinePartKind(value: BlockCodeLinePartKind): string;
  DocumentExportConfig: DocumentExportConfigConstructor;
  DocumentExportConfigTaskExport: DocumentExportConfigTaskExportConstructor;
  DocumentExportConfigTagExport: {
    None: DocumentExportConfigTagExport,
    All: DocumentExportConfigTagExport,
    NotInToc: DocumentExportConfigTagExport,
  }
  format_DocumentExportConfigTagExport(value: DocumentExportConfigTagExport): string;
  DocumentExportConfigTaskFiltering: {
    Whitelist: DocumentExportConfigTaskFiltering,
    Done: DocumentExportConfigTaskFiltering,
    None: DocumentExportConfigTaskFiltering,
    All: DocumentExportConfigTaskFiltering,
  }
  format_DocumentExportConfigTaskFiltering(value: DocumentExportConfigTaskFiltering): string;
  DocumentExportConfigBrokenLinks: {
    None: DocumentExportConfigBrokenLinks,
    Mark: DocumentExportConfigBrokenLinks,
    Raise: DocumentExportConfigBrokenLinks,
    Ignore: DocumentExportConfigBrokenLinks,
  }
  format_DocumentExportConfigBrokenLinks(value: DocumentExportConfigBrokenLinks): string;
  DocumentExportConfigDoExport: DocumentExportConfigDoExportConstructor;
  DocumentExportConfigExportFixed: DocumentExportConfigExportFixedConstructor;
  DocumentExportConfigTocExportKind: {
    DoExport: DocumentExportConfigTocExportKind,
    ExportFixed: DocumentExportConfigTocExportKind,
  }
  format_DocumentExportConfigTocExportKind(value: DocumentExportConfigTocExportKind): string;
  SubtreePeriod: SubtreePeriodConstructor;
  SubtreePeriodKind: {
    Clocked: SubtreePeriodKind,
    Closed: SubtreePeriodKind,
    Scheduled: SubtreePeriodKind,
    Titled: SubtreePeriodKind,
    Deadline: SubtreePeriodKind,
    Created: SubtreePeriodKind,
    Repeated: SubtreePeriodKind,
  }
  format_SubtreePeriodKind(value: SubtreePeriodKind): string;
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
  NamedPropertyVisibilityLevel: {
    Folded: NamedPropertyVisibilityLevel,
    Children: NamedPropertyVisibilityLevel,
    Content: NamedPropertyVisibilityLevel,
    All: NamedPropertyVisibilityLevel,
  }
  format_NamedPropertyVisibilityLevel(value: NamedPropertyVisibilityLevel): string;
  NamedPropertyExportOptions: NamedPropertyExportOptionsConstructor;
  NamedPropertyBlocker: NamedPropertyBlockerConstructor;
  NamedPropertyUnnumbered: NamedPropertyUnnumberedConstructor;
  NamedPropertyCreated: NamedPropertyCreatedConstructor;
  NamedPropertyRadioId: NamedPropertyRadioIdConstructor;
  NamedPropertyHashtagDef: NamedPropertyHashtagDefConstructor;
  NamedPropertyCustomArgs: NamedPropertyCustomArgsConstructor;
  NamedPropertyCustomRaw: NamedPropertyCustomRawConstructor;
  NamedPropertyCustomId: NamedPropertyCustomIdConstructor;
  NamedPropertyCustomSubtreeJson: NamedPropertyCustomSubtreeJsonConstructor;
  NamedPropertyCustomSubtreeFlags: NamedPropertyCustomSubtreeFlagsConstructor;
  NamedPropertyKind: {
    Nonblocking: NamedPropertyKind,
    ArchiveTime: NamedPropertyKind,
    ArchiveFile: NamedPropertyKind,
    ArchiveOlpath: NamedPropertyKind,
    ArchiveTarget: NamedPropertyKind,
    ArchiveCategory: NamedPropertyKind,
    ArchiveTodo: NamedPropertyKind,
    Trigger: NamedPropertyKind,
    ExportLatexClass: NamedPropertyKind,
    CookieData: NamedPropertyKind,
    ExportLatexClassOptions: NamedPropertyKind,
    ExportLatexHeader: NamedPropertyKind,
    ExportLatexCompiler: NamedPropertyKind,
    Ordered: NamedPropertyKind,
    Effort: NamedPropertyKind,
    Visibility: NamedPropertyKind,
    ExportOptions: NamedPropertyKind,
    Blocker: NamedPropertyKind,
    Unnumbered: NamedPropertyKind,
    Created: NamedPropertyKind,
    RadioId: NamedPropertyKind,
    HashtagDef: NamedPropertyKind,
    CustomArgs: NamedPropertyKind,
    CustomRaw: NamedPropertyKind,
    CustomId: NamedPropertyKind,
    CustomSubtreeJson: NamedPropertyKind,
    CustomSubtreeFlags: NamedPropertyKind,
  }
  format_NamedPropertyKind(value: NamedPropertyKind): string;
  OrgDiagnostics: OrgDiagnosticsConstructor;
  OrgDiagnosticsParseTokenError: OrgDiagnosticsParseTokenErrorConstructor;
  OrgDiagnosticsParseError: OrgDiagnosticsParseErrorConstructor;
  OrgDiagnosticsIncludeError: OrgDiagnosticsIncludeErrorConstructor;
  OrgDiagnosticsConvertError: OrgDiagnosticsConvertErrorConstructor;
  OrgDiagnosticsInternalError: OrgDiagnosticsInternalErrorConstructor;
  OrgDiagnosticsKind: {
    ParseTokenError: OrgDiagnosticsKind,
    ParseError: OrgDiagnosticsKind,
    IncludeError: OrgDiagnosticsKind,
    ConvertError: OrgDiagnosticsKind,
    InternalError: OrgDiagnosticsKind,
  }
  format_OrgDiagnosticsKind(value: OrgDiagnosticsKind): string;
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
  TimeRepeatMode: {
    None: TimeRepeatMode,
    Exact: TimeRepeatMode,
    FirstMatch: TimeRepeatMode,
    SameDay: TimeRepeatMode,
  }
  format_TimeRepeatMode(value: TimeRepeatMode): string;
  TimeRepeatPeriod: {
    Year: TimeRepeatPeriod,
    Month: TimeRepeatPeriod,
    Week: TimeRepeatPeriod,
    Day: TimeRepeatPeriod,
    Hour: TimeRepeatPeriod,
    Minute: TimeRepeatPeriod,
  }
  format_TimeRepeatPeriod(value: TimeRepeatPeriod): string;
  TimeStatic: TimeStaticConstructor;
  TimeDynamic: TimeDynamicConstructor;
  TimeTimeKind: {
    Static: TimeTimeKind,
    Dynamic: TimeTimeKind,
  }
  format_TimeTimeKind(value: TimeTimeKind): string;
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
  CriticMarkupKind: {
    Deletion: CriticMarkupKind,
    Addition: CriticMarkupKind,
    Substitution: CriticMarkupKind,
    Highlighting: CriticMarkupKind,
    Comment: CriticMarkupKind,
  }
  format_CriticMarkupKind(value: CriticMarkupKind): string;
  Document: DocumentConstructor;
  FileTarget: FileTargetConstructor;
  TextSeparator: TextSeparatorConstructor;
  DocumentGroup: DocumentGroupConstructor;
  File: FileConstructor;
  FileDocument: FileDocumentConstructor;
  FileAttachment: FileAttachmentConstructor;
  FileSource: FileSourceConstructor;
  FileKind: {
    Document: FileKind,
    Attachment: FileKind,
    Source: FileKind,
  }
  format_FileKind(value: FileKind): string;
  Directory: DirectoryConstructor;
  Symlink: SymlinkConstructor;
  CmdInclude: CmdIncludeConstructor;
  CmdIncludeIncludeBase: CmdIncludeIncludeBaseConstructor;
  CmdIncludeExample: CmdIncludeExampleConstructor;
  CmdIncludeExport: CmdIncludeExportConstructor;
  CmdIncludeCustom: CmdIncludeCustomConstructor;
  CmdIncludeSrc: CmdIncludeSrcConstructor;
  CmdIncludeOrgDocument: CmdIncludeOrgDocumentConstructor;
  CmdIncludeKind: {
    Example: CmdIncludeKind,
    Export: CmdIncludeKind,
    Custom: CmdIncludeKind,
    Src: CmdIncludeKind,
    OrgDocument: CmdIncludeKind,
  }
  format_CmdIncludeKind(value: CmdIncludeKind): string;
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
  ImmTimeRepeatMode: {
    None: ImmTimeRepeatMode,
    Exact: ImmTimeRepeatMode,
    FirstMatch: ImmTimeRepeatMode,
    SameDay: ImmTimeRepeatMode,
  }
  format_ImmTimeRepeatMode(value: ImmTimeRepeatMode): string;
  ImmTimeRepeatPeriod: {
    Year: ImmTimeRepeatPeriod,
    Month: ImmTimeRepeatPeriod,
    Week: ImmTimeRepeatPeriod,
    Day: ImmTimeRepeatPeriod,
    Hour: ImmTimeRepeatPeriod,
    Minute: ImmTimeRepeatPeriod,
  }
  format_ImmTimeRepeatPeriod(value: ImmTimeRepeatPeriod): string;
  ImmTimeStatic: ImmTimeStaticConstructor;
  ImmTimeDynamic: ImmTimeDynamicConstructor;
  ImmTimeTimeKind: {
    Static: ImmTimeTimeKind,
    Dynamic: ImmTimeTimeKind,
  }
  format_ImmTimeTimeKind(value: ImmTimeTimeKind): string;
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
  ImmCriticMarkupKind: {
    Deletion: ImmCriticMarkupKind,
    Addition: ImmCriticMarkupKind,
    Substitution: ImmCriticMarkupKind,
    Highlighting: ImmCriticMarkupKind,
    Comment: ImmCriticMarkupKind,
  }
  format_ImmCriticMarkupKind(value: ImmCriticMarkupKind): string;
  ImmDocument: ImmDocumentConstructor;
  ImmFileTarget: ImmFileTargetConstructor;
  ImmTextSeparator: ImmTextSeparatorConstructor;
  ImmDocumentGroup: ImmDocumentGroupConstructor;
  ImmFile: ImmFileConstructor;
  ImmFileDocument: ImmFileDocumentConstructor;
  ImmFileAttachment: ImmFileAttachmentConstructor;
  ImmFileSource: ImmFileSourceConstructor;
  ImmFileKind: {
    Document: ImmFileKind,
    Attachment: ImmFileKind,
    Source: ImmFileKind,
  }
  format_ImmFileKind(value: ImmFileKind): string;
  ImmDirectory: ImmDirectoryConstructor;
  ImmSymlink: ImmSymlinkConstructor;
  ImmCmdInclude: ImmCmdIncludeConstructor;
  ImmCmdIncludeIncludeBase: ImmCmdIncludeIncludeBaseConstructor;
  ImmCmdIncludeExample: ImmCmdIncludeExampleConstructor;
  ImmCmdIncludeExport: ImmCmdIncludeExportConstructor;
  ImmCmdIncludeCustom: ImmCmdIncludeCustomConstructor;
  ImmCmdIncludeSrc: ImmCmdIncludeSrcConstructor;
  ImmCmdIncludeOrgDocument: ImmCmdIncludeOrgDocumentConstructor;
  ImmCmdIncludeKind: {
    Example: ImmCmdIncludeKind,
    Export: ImmCmdIncludeKind,
    Custom: ImmCmdIncludeKind,
    Src: ImmCmdIncludeKind,
    OrgDocument: ImmCmdIncludeKind,
  }
  format_ImmCmdIncludeKind(value: ImmCmdIncludeKind): string;
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
  Block: BlockConstructor;
  LineCommand: LineCommandConstructor;
  CmdCustomArgs: CmdCustomArgsConstructor;
  CmdTblfm: CmdTblfmConstructor;
  Cell: CellConstructor;
  Row: RowConstructor;
  ImmBlock: ImmBlockConstructor;
  ImmLineCommand: ImmLineCommandConstructor;
  ImmCmdCustomArgs: ImmCmdCustomArgsConstructor;
  ImmCmdTblfm: ImmCmdTblfmConstructor;
  ImmCell: ImmCellConstructor;
  ImmRow: ImmRowConstructor;
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
  CmdCaption: CmdCaptionConstructor;
  CmdColumns: CmdColumnsConstructor;
  CmdName: CmdNameConstructor;
  CmdCall: CmdCallConstructor;
  CmdAttr: CmdAttrConstructor;
  CmdExport: CmdExportConstructor;
  ImmCmdCaption: ImmCmdCaptionConstructor;
  ImmCmdColumns: ImmCmdColumnsConstructor;
  ImmCmdName: ImmCmdNameConstructor;
  ImmCmdCall: ImmCmdCallConstructor;
  ImmCmdAttr: ImmCmdAttrConstructor;
  ImmCmdExport: ImmCmdExportConstructor;
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
  CheckboxState: {
    None: CheckboxState,
    Done: CheckboxState,
    Empty: CheckboxState,
    Partial: CheckboxState,
  }
  format_CheckboxState(value: CheckboxState): string;
  SubtreeTodoSource: {
    Checkbox: SubtreeTodoSource,
    Todo: SubtreeTodoSource,
    Both: SubtreeTodoSource,
  }
  format_SubtreeTodoSource(value: SubtreeTodoSource): string;
  ListFormattingMode: {
    None: ListFormattingMode,
    Table1D1Col: ListFormattingMode,
    Table1D2Col: ListFormattingMode,
    Table2DColFirst: ListFormattingMode,
    Table2DRowFirst: ListFormattingMode,
  }
  format_ListFormattingMode(value: ListFormattingMode): string;
  InitialSubtreeVisibility: {
    Overview: InitialSubtreeVisibility,
    Content: InitialSubtreeVisibility,
    ShowAll: InitialSubtreeVisibility,
    Show2Levels: InitialSubtreeVisibility,
    Show3Levels: InitialSubtreeVisibility,
    Show4Levels: InitialSubtreeVisibility,
    Show5Levels: InitialSubtreeVisibility,
    ShowEverything: InitialSubtreeVisibility,
  }
  format_InitialSubtreeVisibility(value: InitialSubtreeVisibility): string;
  OrgSpecName: {
    Unnamed: OrgSpecName,
    Result: OrgSpecName,
    Year: OrgSpecName,
    Day: OrgSpecName,
    Clock: OrgSpecName,
    Repeater: OrgSpecName,
    Warn: OrgSpecName,
    Zone: OrgSpecName,
    Link: OrgSpecName,
    Tags: OrgSpecName,
    Tag: OrgSpecName,
    State: OrgSpecName,
    Protocol: OrgSpecName,
    Desc: OrgSpecName,
    Times: OrgSpecName,
    Drawer: OrgSpecName,
    Args: OrgSpecName,
    Name: OrgSpecName,
    Definition: OrgSpecName,
    Body: OrgSpecName,
    HeaderArgs: OrgSpecName,
    File: OrgSpecName,
    Kind: OrgSpecName,
    Lang: OrgSpecName,
    Prefix: OrgSpecName,
    Text: OrgSpecName,
    Todo: OrgSpecName,
    Importance: OrgSpecName,
    Title: OrgSpecName,
    Completion: OrgSpecName,
    Head: OrgSpecName,
    Subnodes: OrgSpecName,
    Properties: OrgSpecName,
    Logbook: OrgSpecName,
    Description: OrgSpecName,
    Logs: OrgSpecName,
    Newstate: OrgSpecName,
    Oldstate: OrgSpecName,
    Time: OrgSpecName,
    From: OrgSpecName,
    EndArgs: OrgSpecName,
    Flags: OrgSpecName,
    Value: OrgSpecName,
    Assoc: OrgSpecName,
    Main: OrgSpecName,
    Hash: OrgSpecName,
    Bullet: OrgSpecName,
    Counter: OrgSpecName,
    Checkbox: OrgSpecName,
    Header: OrgSpecName,
    To: OrgSpecName,
    Diff: OrgSpecName,
    Property: OrgSpecName,
    Subname: OrgSpecName,
    Values: OrgSpecName,
    Cells: OrgSpecName,
    Rows: OrgSpecName,
    Lines: OrgSpecName,
    Chunks: OrgSpecName,
  }
  format_OrgSpecName(value: OrgSpecName): string;
  OrgNodeKind: {
    None: OrgNodeKind,
    Document: OrgNodeKind,
    Empty: OrgNodeKind,
    InlineStmtList: OrgNodeKind,
    StmtList: OrgNodeKind,
    Checkbox: OrgNodeKind,
    List: OrgNodeKind,
    Bullet: OrgNodeKind,
    ListItem: OrgNodeKind,
    ListTag: OrgNodeKind,
    Counter: OrgNodeKind,
    File: OrgNodeKind,
    ColonExample: OrgNodeKind,
    TextSeparator: OrgNodeKind,
    Paragraph: OrgNodeKind,
    TableRow: OrgNodeKind,
    TableCell: OrgNodeKind,
    Table: OrgNodeKind,
    InlineFootnote: OrgNodeKind,
    Footnote: OrgNodeKind,
    Cmd: OrgNodeKind,
    Attrs: OrgNodeKind,
    AttrValue: OrgNodeKind,
    AttrLisp: OrgNodeKind,
    CmdTitle: OrgNodeKind,
    CmdAuthor: OrgNodeKind,
    CmdCreator: OrgNodeKind,
    CmdInclude: OrgNodeKind,
    CmdLanguage: OrgNodeKind,
    CmdAttr: OrgNodeKind,
    CmdStartup: OrgNodeKind,
    CmdName: OrgNodeKind,
    CmdCustomTextCommand: OrgNodeKind,
    CmdCustomArgsCommand: OrgNodeKind,
    CmdCustomRawCommand: OrgNodeKind,
    CmdResults: OrgNodeKind,
    CmdHeader: OrgNodeKind,
    CmdOptions: OrgNodeKind,
    CmdTblfm: OrgNodeKind,
    CmdCaption: OrgNodeKind,
    CmdResult: OrgNodeKind,
    CmdCallCode: OrgNodeKind,
    CmdFlag: OrgNodeKind,
    CmdLatexClass: OrgNodeKind,
    CmdLatexHeader: OrgNodeKind,
    CmdLatexCompiler: OrgNodeKind,
    CmdLatexClassOptions: OrgNodeKind,
    CmdHtmlHead: OrgNodeKind,
    CmdColumns: OrgNodeKind,
    CmdPropertyArgs: OrgNodeKind,
    CmdPropertyText: OrgNodeKind,
    CmdPropertyRaw: OrgNodeKind,
    CmdFiletags: OrgNodeKind,
    CmdKeywords: OrgNodeKind,
    BlockVerbatimMultiline: OrgNodeKind,
    CodeLine: OrgNodeKind,
    CodeText: OrgNodeKind,
    CodeTangle: OrgNodeKind,
    CodeCallout: OrgNodeKind,
    BlockCode: OrgNodeKind,
    BlockQuote: OrgNodeKind,
    BlockComment: OrgNodeKind,
    BlockCenter: OrgNodeKind,
    BlockVerse: OrgNodeKind,
    BlockExample: OrgNodeKind,
    BlockExport: OrgNodeKind,
    BlockDetails: OrgNodeKind,
    BlockSummary: OrgNodeKind,
    BlockDynamicFallback: OrgNodeKind,
    BigIdent: OrgNodeKind,
    Bold: OrgNodeKind,
    ErrorInfoToken: OrgNodeKind,
    ErrorSkipGroup: OrgNodeKind,
    ErrorSkipToken: OrgNodeKind,
    Italic: OrgNodeKind,
    Verbatim: OrgNodeKind,
    Backtick: OrgNodeKind,
    Underline: OrgNodeKind,
    Strike: OrgNodeKind,
    Quote: OrgNodeKind,
    Angle: OrgNodeKind,
    Monospace: OrgNodeKind,
    Par: OrgNodeKind,
    CriticMarkStructure: OrgNodeKind,
    InlineMath: OrgNodeKind,
    DisplayMath: OrgNodeKind,
    Space: OrgNodeKind,
    Punctuation: OrgNodeKind,
    Colon: OrgNodeKind,
    Word: OrgNodeKind,
    Escaped: OrgNodeKind,
    Newline: OrgNodeKind,
    RawLink: OrgNodeKind,
    Link: OrgNodeKind,
    Macro: OrgNodeKind,
    Symbol: OrgNodeKind,
    StaticActiveTime: OrgNodeKind,
    StaticInactiveTime: OrgNodeKind,
    DynamicActiveTime: OrgNodeKind,
    DynamicInactiveTime: OrgNodeKind,
    TimeRange: OrgNodeKind,
    SimpleTime: OrgNodeKind,
    HashTag: OrgNodeKind,
    MetaSymbol: OrgNodeKind,
    AtMention: OrgNodeKind,
    Placeholder: OrgNodeKind,
    RadioTarget: OrgNodeKind,
    Target: OrgNodeKind,
    SrcInlineCode: OrgNodeKind,
    InlineCallCode: OrgNodeKind,
    InlineExport: OrgNodeKind,
    InlineComment: OrgNodeKind,
    RawText: OrgNodeKind,
    SubtreeDescription: OrgNodeKind,
    SubtreeUrgency: OrgNodeKind,
    DrawerLogbook: OrgNodeKind,
    Drawer: OrgNodeKind,
    DrawerPropertyList: OrgNodeKind,
    DrawerProperty: OrgNodeKind,
    Subtree: OrgNodeKind,
    SubtreeTimes: OrgNodeKind,
    SubtreeStars: OrgNodeKind,
    SubtreeCompletion: OrgNodeKind,
    SubtreeImportance: OrgNodeKind,
  }
  format_OrgNodeKind(value: OrgNodeKind): string;
  OrgTokenKind: {
    Ampersand: OrgTokenKind,
    AngleBegin: OrgTokenKind,
    AngleEnd: OrgTokenKind,
    AnyPunct: OrgTokenKind,
    Asterisk: OrgTokenKind,
    At: OrgTokenKind,
    Backtick: OrgTokenKind,
    BigIdent: OrgTokenKind,
    BoldBegin: OrgTokenKind,
    BoldEnd: OrgTokenKind,
    BoldUnknown: OrgTokenKind,
    BraceBegin: OrgTokenKind,
    BraceEnd: OrgTokenKind,
    Checkbox: OrgTokenKind,
    Circumflex: OrgTokenKind,
    CmdAdmonitionEnd: OrgTokenKind,
    CmdAttr: OrgTokenKind,
    CmdAuthor: OrgTokenKind,
    CmdBindRaw: OrgTokenKind,
    CmdCall: OrgTokenKind,
    CmdCaption: OrgTokenKind,
    CmdCategoryRaw: OrgTokenKind,
    CmdCell: OrgTokenKind,
    CmdCellBegin: OrgTokenKind,
    CmdCellEnd: OrgTokenKind,
    CmdCenterBegin: OrgTokenKind,
    CmdCenterEnd: OrgTokenKind,
    CmdColonIdent: OrgTokenKind,
    CmdColumns: OrgTokenKind,
    CmdCommentBegin: OrgTokenKind,
    CmdCommentEnd: OrgTokenKind,
    CmdConstants: OrgTokenKind,
    CmdContentBegin: OrgTokenKind,
    CmdContentEnd: OrgTokenKind,
    CmdCreator: OrgTokenKind,
    CmdCustomRaw: OrgTokenKind,
    CmdDateRaw: OrgTokenKind,
    CmdDescription: OrgTokenKind,
    CmdDrawersRaw: OrgTokenKind,
    CmdDynamicBegin: OrgTokenKind,
    CmdDynamicBlockBegin: OrgTokenKind,
    CmdDynamicBlockEnd: OrgTokenKind,
    CmdDynamicEnd: OrgTokenKind,
    CmdEmailRaw: OrgTokenKind,
    CmdExampleBegin: OrgTokenKind,
    CmdExampleEnd: OrgTokenKind,
    CmdExampleLine: OrgTokenKind,
    CmdExcludeTagsRaw: OrgTokenKind,
    CmdExportBegin: OrgTokenKind,
    CmdExportEnd: OrgTokenKind,
    CmdExportLine: OrgTokenKind,
    CmdFiletags: OrgTokenKind,
    CmdFlag: OrgTokenKind,
    CmdHeader: OrgTokenKind,
    CmdHtmlHeadRaw: OrgTokenKind,
    CmdInclude: OrgTokenKind,
    CmdLanguage: OrgTokenKind,
    CmdLatexClass: OrgTokenKind,
    CmdLatexClassOptions: OrgTokenKind,
    CmdLatexCompiler: OrgTokenKind,
    CmdLatexHeader: OrgTokenKind,
    CmdLatexHeaderExtraRaw: OrgTokenKind,
    CmdLinkRaw: OrgTokenKind,
    CmdMacroRaw: OrgTokenKind,
    CmdName: OrgTokenKind,
    CmdOptions: OrgTokenKind,
    CmdPrefix: OrgTokenKind,
    CmdPrioritiesRaw: OrgTokenKind,
    CmdPropertyArgs: OrgTokenKind,
    CmdPropertyRaw: OrgTokenKind,
    CmdPropertyText: OrgTokenKind,
    CmdQuoteBegin: OrgTokenKind,
    CmdQuoteEnd: OrgTokenKind,
    CmdRawArg: OrgTokenKind,
    CmdResults: OrgTokenKind,
    CmdRow: OrgTokenKind,
    CmdRowBegin: OrgTokenKind,
    CmdRowEnd: OrgTokenKind,
    CmdSelectTagsRaw: OrgTokenKind,
    CmdSeqTodoRaw: OrgTokenKind,
    CmdKeywordsRaw: OrgTokenKind,
    CmdSetupfileRaw: OrgTokenKind,
    CmdSrcBegin: OrgTokenKind,
    CmdSrcEnd: OrgTokenKind,
    CmdStartup: OrgTokenKind,
    CmdTableBegin: OrgTokenKind,
    CmdTableEnd: OrgTokenKind,
    CmdTagsRaw: OrgTokenKind,
    CmdTblfm: OrgTokenKind,
    CmdTitle: OrgTokenKind,
    CmdVerseBegin: OrgTokenKind,
    CmdVerseEnd: OrgTokenKind,
    Colon: OrgTokenKind,
    ColonArgumentsProperty: OrgTokenKind,
    ColonEnd: OrgTokenKind,
    ColonExampleLine: OrgTokenKind,
    ColonLiteralProperty: OrgTokenKind,
    ColonLogbook: OrgTokenKind,
    ColonProperties: OrgTokenKind,
    ColonPropertyText: OrgTokenKind,
    Comma: OrgTokenKind,
    Comment: OrgTokenKind,
    CriticAddBegin: OrgTokenKind,
    CriticAddEnd: OrgTokenKind,
    CriticCommentBegin: OrgTokenKind,
    CriticCommentEnd: OrgTokenKind,
    CriticDeleteBegin: OrgTokenKind,
    CriticDeleteEnd: OrgTokenKind,
    CriticHighlightBegin: OrgTokenKind,
    CriticHighlightEnd: OrgTokenKind,
    CriticReplaceBegin: OrgTokenKind,
    CriticReplaceEnd: OrgTokenKind,
    CriticReplaceMiddle: OrgTokenKind,
    CurlyBegin: OrgTokenKind,
    CurlyEnd: OrgTokenKind,
    Date: OrgTokenKind,
    Dedent: OrgTokenKind,
    Dollar: OrgTokenKind,
    DoubleAngleBegin: OrgTokenKind,
    DoubleAngleEnd: OrgTokenKind,
    DoubleColon: OrgTokenKind,
    DoubleDash: OrgTokenKind,
    DoubleHash: OrgTokenKind,
    DoubleQuote: OrgTokenKind,
    DoubleSlash: OrgTokenKind,
    ActiveDynamicTimeContent: OrgTokenKind,
    InactiveDynamicTimeContent: OrgTokenKind,
    EndOfFile: OrgTokenKind,
    Equals: OrgTokenKind,
    Escaped: OrgTokenKind,
    Exclamation: OrgTokenKind,
    FootnoteInlineBegin: OrgTokenKind,
    FootnoteLinked: OrgTokenKind,
    ForwardSlash: OrgTokenKind,
    HashIdent: OrgTokenKind,
    HashTagBegin: OrgTokenKind,
    Indent: OrgTokenKind,
    InlineExportBackend: OrgTokenKind,
    InlineExportContent: OrgTokenKind,
    ItalicBegin: OrgTokenKind,
    ItalicEnd: OrgTokenKind,
    ItalicUnknown: OrgTokenKind,
    LatexInlineRaw: OrgTokenKind,
    LatexParBegin: OrgTokenKind,
    LatexParEnd: OrgTokenKind,
    LeadingMinus: OrgTokenKind,
    LeadingNumber: OrgTokenKind,
    LeadingPipe: OrgTokenKind,
    LeadingPlus: OrgTokenKind,
    LeadingSpace: OrgTokenKind,
    LineCommand: OrgTokenKind,
    LinkBegin: OrgTokenKind,
    LinkDescriptionBegin: OrgTokenKind,
    LinkDescriptionEnd: OrgTokenKind,
    LinkEnd: OrgTokenKind,
    LinkFull: OrgTokenKind,
    LinkProtocol: OrgTokenKind,
    LinkProtocolAttachment: OrgTokenKind,
    LinkProtocolCustomId: OrgTokenKind,
    LinkProtocolFile: OrgTokenKind,
    LinkProtocolHttp: OrgTokenKind,
    LinkProtocolId: OrgTokenKind,
    LinkProtocolInternal: OrgTokenKind,
    LinkProtocolTitle: OrgTokenKind,
    LinkSplit: OrgTokenKind,
    LinkTarget: OrgTokenKind,
    LinkTargetBegin: OrgTokenKind,
    LinkTargetEnd: OrgTokenKind,
    LinkTargetFile: OrgTokenKind,
    ListBegin: OrgTokenKind,
    ListEnd: OrgTokenKind,
    ListItemBegin: OrgTokenKind,
    ListItemEnd: OrgTokenKind,
    LongNewline: OrgTokenKind,
    MediumNewline: OrgTokenKind,
    Minus: OrgTokenKind,
    MiscUnicode: OrgTokenKind,
    MonospaceBegin: OrgTokenKind,
    MonospaceEnd: OrgTokenKind,
    MonospaceUnknown: OrgTokenKind,
    Newline: OrgTokenKind,
    Number: OrgTokenKind,
    ParBegin: OrgTokenKind,
    ParEnd: OrgTokenKind,
    Percent: OrgTokenKind,
    Pipe: OrgTokenKind,
    Placeholder: OrgTokenKind,
    Plus: OrgTokenKind,
    Punctuation: OrgTokenKind,
    RawText: OrgTokenKind,
    SameIndent: OrgTokenKind,
    Semicolon: OrgTokenKind,
    SingleQuote: OrgTokenKind,
    SrcContent: OrgTokenKind,
    StmtListBegin: OrgTokenKind,
    StmtListEnd: OrgTokenKind,
    StrikeBegin: OrgTokenKind,
    StrikeEnd: OrgTokenKind,
    StrikeUnknown: OrgTokenKind,
    SubtreeCompletion: OrgTokenKind,
    SubtreePriority: OrgTokenKind,
    SubtreeStars: OrgTokenKind,
    Symbol: OrgTokenKind,
    TableSeparator: OrgTokenKind,
    TextSeparator: OrgTokenKind,
    TextSrcBegin: OrgTokenKind,
    Tilda: OrgTokenKind,
    Time: OrgTokenKind,
    TimeArrow: OrgTokenKind,
    TimeRepeaterDuration: OrgTokenKind,
    TimeRepeaterSpec: OrgTokenKind,
    TimeWarnPeriod: OrgTokenKind,
    TrailingPipe: OrgTokenKind,
    TreeClock: OrgTokenKind,
    TreeTime: OrgTokenKind,
    TripleAngleBegin: OrgTokenKind,
    TripleAngleEnd: OrgTokenKind,
    Underline: OrgTokenKind,
    UnderlineBegin: OrgTokenKind,
    UnderlineEnd: OrgTokenKind,
    UnderlineUnknown: OrgTokenKind,
    Unknown: OrgTokenKind,
    VerbatimBegin: OrgTokenKind,
    VerbatimEnd: OrgTokenKind,
    VerbatimUnknown: OrgTokenKind,
    Whitespace: OrgTokenKind,
    Word: OrgTokenKind,
  }
  format_OrgTokenKind(value: OrgTokenKind): string;
  OrgJsonKind: {
    Null: OrgJsonKind,
    Object: OrgJsonKind,
    Array: OrgJsonKind,
    String: OrgJsonKind,
    Boolean: OrgJsonKind,
    Int: OrgJsonKind,
    Float: OrgJsonKind,
  }
  format_OrgJsonKind(value: OrgJsonKind): string;
  OrgSemKind: {
    None: OrgSemKind,
    ErrorItem: OrgSemKind,
    ErrorGroup: OrgSemKind,
    StmtList: OrgSemKind,
    Empty: OrgSemKind,
    CmdCaption: OrgSemKind,
    CmdColumns: OrgSemKind,
    CmdName: OrgSemKind,
    CmdCustomArgs: OrgSemKind,
    CmdCustomRaw: OrgSemKind,
    CmdCustomText: OrgSemKind,
    CmdCall: OrgSemKind,
    CmdTblfm: OrgSemKind,
    HashTag: OrgSemKind,
    InlineFootnote: OrgSemKind,
    InlineExport: OrgSemKind,
    Time: OrgSemKind,
    TimeRange: OrgSemKind,
    Macro: OrgSemKind,
    Symbol: OrgSemKind,
    Escaped: OrgSemKind,
    Newline: OrgSemKind,
    Space: OrgSemKind,
    Word: OrgSemKind,
    AtMention: OrgSemKind,
    RawText: OrgSemKind,
    Punctuation: OrgSemKind,
    Placeholder: OrgSemKind,
    BigIdent: OrgSemKind,
    TextTarget: OrgSemKind,
    Bold: OrgSemKind,
    Underline: OrgSemKind,
    Monospace: OrgSemKind,
    MarkQuote: OrgSemKind,
    Verbatim: OrgSemKind,
    Italic: OrgSemKind,
    Strike: OrgSemKind,
    Par: OrgSemKind,
    RadioTarget: OrgSemKind,
    Latex: OrgSemKind,
    Link: OrgSemKind,
    BlockCenter: OrgSemKind,
    BlockQuote: OrgSemKind,
    BlockComment: OrgSemKind,
    BlockVerse: OrgSemKind,
    BlockDynamicFallback: OrgSemKind,
    BlockExample: OrgSemKind,
    BlockExport: OrgSemKind,
    BlockAdmonition: OrgSemKind,
    BlockCodeEvalResult: OrgSemKind,
    BlockCode: OrgSemKind,
    SubtreeLog: OrgSemKind,
    Subtree: OrgSemKind,
    Cell: OrgSemKind,
    Row: OrgSemKind,
    Table: OrgSemKind,
    Paragraph: OrgSemKind,
    ColonExample: OrgSemKind,
    CmdAttr: OrgSemKind,
    CmdExport: OrgSemKind,
    Call: OrgSemKind,
    List: OrgSemKind,
    ListItem: OrgSemKind,
    DocumentOptions: OrgSemKind,
    DocumentFragment: OrgSemKind,
    CriticMarkup: OrgSemKind,
    Document: OrgSemKind,
    FileTarget: OrgSemKind,
    TextSeparator: OrgSemKind,
    DocumentGroup: OrgSemKind,
    File: OrgSemKind,
    Directory: OrgSemKind,
    Symlink: OrgSemKind,
    CmdInclude: OrgSemKind,
  }
  format_OrgSemKind(value: OrgSemKind): string;
  AstTrackingGroupKind: {
    RadioTarget: AstTrackingGroupKind,
    Single: AstTrackingGroupKind,
    TrackedHashtag: AstTrackingGroupKind,
  }
  format_AstTrackingGroupKind(value: AstTrackingGroupKind): string;
  GraphMapLinkKind: {
    Radio: GraphMapLinkKind,
    Link: GraphMapLinkKind,
  }
  format_GraphMapLinkKind(value: GraphMapLinkKind): string;
  newSemTimeStatic(breakdown: UserTimeBreakdown, isActive: boolean): Time;
  parseFile(file: string, opts: OrgParseParameters): Org;
  parseString(text: string): Org;
  parseStringOpts(text: string, opts: OrgParseParameters): Org;
  parseDirectoryOpts(path: string, opts: OrgDirectoryParseParameters): haxorg_wasm.Optional<Org>;
  parseFileWithIncludes(file: string, opts: OrgDirectoryParseParameters): File;
  initImmutableAstContext(): ImmAstContext;
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
  getAstTrackingMap(nodes: haxorg_wasm.Vec<Org>): AstTrackingMap;
  getSubnodeGroups(node: Org, map: AstTrackingMap): haxorg_wasm.Vec<AstTrackingGroup>;
  annotateSequence(groups: haxorg_wasm.Vec<SequenceSegmentGroup>, first: number, last: number): haxorg_wasm.Vec<SequenceAnnotation>;
  initMapGraphState(ast: ImmAstContext): GraphMapGraphState;
  serializeAstContextToText(store: ImmAstContext): string;
  serializeAstContextFromText(binary: string, store: ImmAstContext): void;
  serializeAstEpochToText(store: ImmAstReplaceEpoch): string;
  serializeAstEpochFromText(binary: string, store: ImmAstReplaceEpoch): void;
  serializeMapGraphToText(store: GraphMapGraph): string;
  serializeMapGraphFromText(binary: string, store: GraphMapGraph): void;
  serializeFromTextToTreeDump(binary: string): string;
}
type haxorg_wasm_module = haxorg_wasm_module_auto & haxorg_wasm.haxorg_wasm_manual;
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
  getTimeDeltaSeconds(other: UserTime): Int64_t;
  toUnixTimestamp(): Int64_t;
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
  sendMessage(value: string, function_: string, line: number, file: string): void;
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
  getArray(): haxorg_wasm.Vec<OrgJson>;
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
  subnodes: haxorg_wasm.Vec<Org>
}
export interface ImmIdConstructor { new(): ImmId; }
export interface ImmId {
  getKind(): OrgSemKind;
  is(kind: OrgSemKind): boolean;
  getNodeIndex(): ImmIdNodeIdxT;
  getReadableId(): string;
}
export interface ImmOrgConstructor { new(): ImmOrg; }
export interface ImmOrg {  }
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
export interface ImmAstReplaceEpochConstructor { new(): ImmAstReplaceEpoch; }
export interface ImmAstReplaceEpoch {  }
export interface ImmNoneValueReadConstructor { new(): ImmNoneValueRead; }
export interface ImmNoneValueRead {  }
export interface ImmErrorItemValueReadConstructor { new(): ImmErrorItemValueRead; }
export interface ImmErrorItemValueRead { getDiag(): OrgDiagnostics; }
export interface ImmErrorGroupValueReadConstructor { new(): ImmErrorGroupValueRead; }
export interface ImmErrorGroupValueRead { getDiagnostics(): haxorg_wasm.ImmerFlex_vector<haxorg_wasm.ImmIdT<ImmErrorItem>>; }
export interface ImmStmtListValueReadConstructor { new(): ImmStmtListValueRead; }
export interface ImmStmtListValueRead {  }
export interface ImmEmptyValueReadConstructor { new(): ImmEmptyValueRead; }
export interface ImmEmptyValueRead {  }
export interface ImmCmdCaptionValueReadConstructor { new(): ImmCmdCaptionValueRead; }
export interface ImmCmdCaptionValueRead { getText(): haxorg_wasm.ImmIdT<ImmParagraph>; }
export interface ImmCmdColumnsValueReadConstructor { new(): ImmCmdColumnsValueRead; }
export interface ImmCmdColumnsValueRead { getView(): ColumnView; }
export interface ImmCmdNameValueReadConstructor { new(): ImmCmdNameValueRead; }
export interface ImmCmdNameValueRead { getName(): haxorg_wasm.ImmerBox<string>; }
export interface ImmCmdCustomArgsValueReadConstructor { new(): ImmCmdCustomArgsValueRead; }
export interface ImmCmdCustomArgsValueRead {
  getName(): haxorg_wasm.ImmerBox<string>;
  getIsattached(): boolean;
}
export interface ImmCmdCustomRawValueReadConstructor { new(): ImmCmdCustomRawValueRead; }
export interface ImmCmdCustomRawValueRead {
  getName(): haxorg_wasm.ImmerBox<string>;
  getIsattached(): boolean;
  getText(): haxorg_wasm.ImmerBox<string>;
}
export interface ImmCmdCustomTextValueReadConstructor { new(): ImmCmdCustomTextValueRead; }
export interface ImmCmdCustomTextValueRead {
  getName(): haxorg_wasm.ImmerBox<string>;
  getIsattached(): boolean;
  getText(): haxorg_wasm.ImmIdT<ImmParagraph>;
}
export interface ImmCmdCallValueReadConstructor { new(): ImmCmdCallValueRead; }
export interface ImmCmdCallValueRead {
  getName(): haxorg_wasm.ImmerBox<string>;
  getFilename(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<string>>;
  getInsideheaderattrs(): AttrGroup;
  getCallattrs(): AttrGroup;
  getEndheaderattrs(): AttrGroup;
  getResult(): haxorg_wasm.ImmerFlex_vector<haxorg_wasm.ImmIdT<ImmBlockCodeEvalResult>>;
}
export interface ImmCmdTblfmValueReadConstructor { new(): ImmCmdTblfmValueRead; }
export interface ImmCmdTblfmValueRead { getExpr(): Tblfm; }
export interface ImmHashTagValueReadConstructor { new(): ImmHashTagValueRead; }
export interface ImmHashTagValueRead { getText(): HashTagText; }
export interface ImmInlineFootnoteValueReadConstructor { new(): ImmInlineFootnoteValueRead; }
export interface ImmInlineFootnoteValueRead {
  getTag(): haxorg_wasm.ImmerBox<string>;
  getDefinition(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmOrg>>>;
}
export interface ImmInlineExportValueReadConstructor { new(): ImmInlineExportValueRead; }
export interface ImmInlineExportValueRead {
  getExporter(): haxorg_wasm.ImmerBox<string>;
  getContent(): haxorg_wasm.ImmerBox<string>;
}
export interface ImmTimeValueReadConstructor { new(): ImmTimeValueRead; }
export interface ImmTimeValueRead {
  getIsactive(): boolean;
  getTime(): ImmTimeTimeVariant;
}
export interface ImmTimeRangeValueReadConstructor { new(): ImmTimeRangeValueRead; }
export interface ImmTimeRangeValueRead {
  getFrom(): haxorg_wasm.ImmIdT<ImmTime>;
  getTo(): haxorg_wasm.ImmIdT<ImmTime>;
}
export interface ImmMacroValueReadConstructor { new(): ImmMacroValueRead; }
export interface ImmMacroValueRead {
  getName(): haxorg_wasm.ImmerBox<string>;
  getAttrs(): AttrGroup;
}
export interface ImmSymbolValueReadConstructor { new(): ImmSymbolValueRead; }
export interface ImmSymbolValueRead {
  getName(): haxorg_wasm.ImmerBox<string>;
  getParameters(): haxorg_wasm.ImmerFlex_vector<ImmSymbolParam>;
  getPositional(): haxorg_wasm.ImmerFlex_vector<haxorg_wasm.ImmIdT<ImmOrg>>;
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
export interface ImmRadioTargetValueRead { getWords(): haxorg_wasm.ImmerFlex_vector<string>; }
export interface ImmLatexValueReadConstructor { new(): ImmLatexValueRead; }
export interface ImmLatexValueRead {  }
export interface ImmLinkValueReadConstructor { new(): ImmLinkValueRead; }
export interface ImmLinkValueRead {
  getDescription(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmParagraph>>>;
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
export interface ImmBlockDynamicFallbackValueRead { getName(): haxorg_wasm.ImmerBox<string>; }
export interface ImmBlockExampleValueReadConstructor { new(): ImmBlockExampleValueRead; }
export interface ImmBlockExampleValueRead {  }
export interface ImmBlockExportValueReadConstructor { new(): ImmBlockExportValueRead; }
export interface ImmBlockExportValueRead {
  getExporter(): haxorg_wasm.ImmerBox<string>;
  getContent(): haxorg_wasm.ImmerBox<string>;
}
export interface ImmBlockAdmonitionValueReadConstructor { new(): ImmBlockAdmonitionValueRead; }
export interface ImmBlockAdmonitionValueRead {  }
export interface ImmBlockCodeEvalResultValueReadConstructor { new(): ImmBlockCodeEvalResultValueRead; }
export interface ImmBlockCodeEvalResultValueRead {
  getRaw(): haxorg_wasm.ImmerFlex_vector<OrgCodeEvalOutput>;
  getNode(): haxorg_wasm.ImmIdT<ImmOrg>;
}
export interface ImmBlockCodeValueReadConstructor { new(): ImmBlockCodeValueRead; }
export interface ImmBlockCodeValueRead {
  getLang(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<string>>;
  getResult(): haxorg_wasm.ImmerFlex_vector<haxorg_wasm.ImmIdT<ImmBlockCodeEvalResult>>;
  getLines(): haxorg_wasm.ImmerFlex_vector<BlockCodeLine>;
  getSwitches(): AttrGroup;
}
export interface ImmSubtreeLogValueReadConstructor { new(): ImmSubtreeLogValueRead; }
export interface ImmSubtreeLogValueRead {
  getHead(): SubtreeLogHead;
  getDesc(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmStmtList>>>;
}
export interface ImmSubtreeValueReadConstructor { new(): ImmSubtreeValueRead; }
export interface ImmSubtreeValueRead {
  getLevel(): number;
  getTreeid(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<string>>;
  getTodo(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<string>>;
  getCompletion(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<SubtreeCompletion>>;
  getDescription(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmParagraph>>>;
  getTags(): haxorg_wasm.ImmerFlex_vector<haxorg_wasm.ImmIdT<ImmHashTag>>;
  getTitle(): haxorg_wasm.ImmIdT<ImmParagraph>;
  getLogbook(): haxorg_wasm.ImmerFlex_vector<haxorg_wasm.ImmIdT<ImmSubtreeLog>>;
  getProperties(): haxorg_wasm.ImmerFlex_vector<NamedProperty>;
  getClosed(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmTime>>>;
  getDeadline(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmTime>>>;
  getScheduled(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmTime>>>;
  getIscomment(): boolean;
  getIsarchived(): boolean;
  getPriority(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<string>>;
}
export interface ImmCellValueReadConstructor { new(): ImmCellValueRead; }
export interface ImmCellValueRead { getIsblock(): boolean; }
export interface ImmRowValueReadConstructor { new(): ImmRowValueRead; }
export interface ImmRowValueRead {
  getCells(): haxorg_wasm.ImmerFlex_vector<haxorg_wasm.ImmIdT<ImmCell>>;
  getIsblock(): boolean;
}
export interface ImmTableValueReadConstructor { new(): ImmTableValueRead; }
export interface ImmTableValueRead {
  getRows(): haxorg_wasm.ImmerFlex_vector<haxorg_wasm.ImmIdT<ImmRow>>;
  getIsblock(): boolean;
}
export interface ImmParagraphValueReadConstructor { new(): ImmParagraphValueRead; }
export interface ImmParagraphValueRead {  }
export interface ImmColonExampleValueReadConstructor { new(): ImmColonExampleValueRead; }
export interface ImmColonExampleValueRead {  }
export interface ImmCmdAttrValueReadConstructor { new(): ImmCmdAttrValueRead; }
export interface ImmCmdAttrValueRead { getTarget(): haxorg_wasm.ImmerBox<string>; }
export interface ImmCmdExportValueReadConstructor { new(): ImmCmdExportValueRead; }
export interface ImmCmdExportValueRead {
  getExporter(): haxorg_wasm.ImmerBox<string>;
  getContent(): haxorg_wasm.ImmerBox<string>;
}
export interface ImmCallValueReadConstructor { new(): ImmCallValueRead; }
export interface ImmCallValueRead {
  getName(): haxorg_wasm.ImmerBox<string>;
  getAttrs(): AttrGroup;
  getIscommand(): boolean;
}
export interface ImmListValueReadConstructor { new(): ImmListValueRead; }
export interface ImmListValueRead {  }
export interface ImmListItemValueReadConstructor { new(): ImmListItemValueRead; }
export interface ImmListItemValueRead {
  getCheckbox(): CheckboxState;
  getHeader(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmParagraph>>>;
  getBullet(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<string>>;
}
export interface ImmDocumentOptionsValueReadConstructor { new(): ImmDocumentOptionsValueRead; }
export interface ImmDocumentOptionsValueRead {
  getInitialvisibility(): InitialSubtreeVisibility;
  getProperties(): haxorg_wasm.ImmerFlex_vector<NamedProperty>;
  getExportconfig(): DocumentExportConfig;
  getFixedwidthsections(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<boolean>>;
  getStartupindented(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<boolean>>;
  getCategory(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<string>>;
  getSetupfile(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<string>>;
  getMaxsubtreelevelexport(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<number>>;
  getColumns(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<ColumnView>>;
  getTodokeywords(): haxorg_wasm.ImmerFlex_vector<TodoKeyword>;
  getDonekeywords(): haxorg_wasm.ImmerFlex_vector<TodoKeyword>;
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
  getTitle(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmParagraph>>>;
  getAuthor(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmParagraph>>>;
  getCreator(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmParagraph>>>;
  getFiletags(): haxorg_wasm.ImmerFlex_vector<haxorg_wasm.ImmIdT<ImmHashTag>>;
  getEmail(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmRawText>>>;
  getLanguage(): haxorg_wasm.ImmerFlex_vector<string>;
  getOptions(): haxorg_wasm.ImmIdT<ImmDocumentOptions>;
  getExportfilename(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<string>>;
}
export interface ImmFileTargetValueReadConstructor { new(): ImmFileTargetValueRead; }
export interface ImmFileTargetValueRead {
  getPath(): haxorg_wasm.ImmerBox<string>;
  getLine(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<number>>;
  getSearchtarget(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<string>>;
  getRestricttoheadlines(): boolean;
  getTargetid(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<string>>;
  getRegexp(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<string>>;
}
export interface ImmTextSeparatorValueReadConstructor { new(): ImmTextSeparatorValueRead; }
export interface ImmTextSeparatorValueRead {  }
export interface ImmDocumentGroupValueReadConstructor { new(): ImmDocumentGroupValueRead; }
export interface ImmDocumentGroupValueRead {  }
export interface ImmFileValueReadConstructor { new(): ImmFileValueRead; }
export interface ImmFileValueRead {
  getRelpath(): haxorg_wasm.ImmerBox<string>;
  getAbspath(): haxorg_wasm.ImmerBox<string>;
  getData(): ImmFileData;
}
export interface ImmDirectoryValueReadConstructor { new(): ImmDirectoryValueRead; }
export interface ImmDirectoryValueRead {
  getRelpath(): haxorg_wasm.ImmerBox<string>;
  getAbspath(): haxorg_wasm.ImmerBox<string>;
}
export interface ImmSymlinkValueReadConstructor { new(): ImmSymlinkValueRead; }
export interface ImmSymlinkValueRead {
  getIsdirectory(): boolean;
  getAbspath(): haxorg_wasm.ImmerBox<string>;
}
export interface ImmCmdIncludeValueReadConstructor { new(): ImmCmdIncludeValueRead; }
export interface ImmCmdIncludeValueRead {
  getPath(): haxorg_wasm.ImmerBox<string>;
  getFirstline(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<number>>;
  getLastline(): haxorg_wasm.ImmerBox<haxorg_wasm.Optional<number>>;
  getData(): ImmCmdIncludeData;
}
export interface ImmAstContextConstructor { new(): ImmAstContext; }
export interface ImmAstContext {
  addRoot(data: Org): ImmAstVersion;
  getEmptyVersion(): ImmAstVersion;
  get(id: ImmId): Org;
}
export interface ImmAstVersionConstructor { new(): ImmAstVersion; }
export interface ImmAstVersion {
  getRoot(): ImmId;
  getRootAdapter(): ImmAdapter;
  getContext(): ImmAstContext;
  getEpoch(): ImmAstReplaceEpoch;
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
  atField(field: ImmReflFieldId): ImmAdapter;
  atIndex(idx: number, withPath: boolean): ImmAdapter;
  atPath(path: haxorg_wasm.Vec<number>, withPath: boolean): ImmAdapter;
  is(kind: OrgSemKind): boolean;
  sub(withPath: boolean): haxorg_wasm.Vec<ImmAdapter>;
}
export interface ImmAdapterTreeReprConfConstructor { new(): ImmAdapterTreeReprConf; }
export interface ImmAdapterTreeReprConf {
  maxDepth: number
  withAuxFields: boolean
  withReflFields: boolean
  withFieldSubset: UnorderedSet<StdPair<OrgSemKind, ImmReflFieldId>>
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
  path: haxorg_wasm.Vec<Org>
}
export interface AstTrackingAlternativesConstructor { new(): AstTrackingAlternatives; }
export interface AstTrackingAlternatives {
  getAllNodes(): haxorg_wasm.Vec<Org>;
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
  nodes: haxorg_wasm.Vec<Org>
}
export interface AstTrackingGroupSingleConstructor { new(): AstTrackingGroupSingle; }
export interface AstTrackingGroupSingle { node: Org }
export interface AstTrackingGroupTrackedHashtagConstructor { new(): AstTrackingGroupTrackedHashtag; }
export interface AstTrackingGroupTrackedHashtag {
  tag: Org
  targets: haxorg_wasm.UnorderedMap<HashTagFlat, AstTrackingPath>
}
export interface AstTrackingMapConstructor { new(): AstTrackingMap; }
export interface AstTrackingMap {
  getIdPath(id: string): haxorg_wasm.Optional<AstTrackingAlternatives>;
  getNamePath(id: string): haxorg_wasm.Optional<AstTrackingAlternatives>;
  getAnchorTarget(id: string): haxorg_wasm.Optional<AstTrackingAlternatives>;
  getFootnotePath(id: string): haxorg_wasm.Optional<AstTrackingAlternatives>;
  footnotes: haxorg_wasm.UnorderedMap<string, AstTrackingAlternatives>
  subtrees: haxorg_wasm.UnorderedMap<string, AstTrackingAlternatives>
  names: haxorg_wasm.UnorderedMap<string, AstTrackingAlternatives>
  anchorTargets: haxorg_wasm.UnorderedMap<string, AstTrackingAlternatives>
  radioTargets: haxorg_wasm.UnorderedMap<string, AstTrackingAlternatives>
  hashtagDefinitions: haxorg_wasm.UnorderedMap<HashTagFlat, AstTrackingAlternatives>
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
  segments: haxorg_wasm.Vec<SequenceSegment>
}
export interface SequenceAnnotationTagConstructor { new(): SequenceAnnotationTag; }
export interface SequenceAnnotationTag {
  groupKind: number
  segmentKinds: haxorg_wasm.Vec<number>
}
export interface SequenceAnnotationConstructor { new(): SequenceAnnotation; }
export interface SequenceAnnotation {
  isAnnotatedWith(groupKind: number, segmentKind: number): boolean;
  first: number
  last: number
  annotations: haxorg_wasm.Vec<SequenceAnnotationTag>
}
export interface GraphMapLinkConstructor { new(): GraphMapLink; }
export interface GraphMapLink {
  getRadio(): GraphMapLinkRadio;
  getRadio(): GraphMapLinkRadio;
  isRadio(): boolean;
  getLink(): GraphMapLinkLink;
  getLink(): GraphMapLinkLink;
  isLink(): boolean;
  getKind(): GraphMapLinkKind;
}
export interface GraphMapLinkLinkConstructor { new(): GraphMapLinkLink; }
export interface GraphMapLinkLink {
  link: ImmUniqId
  description: haxorg_wasm.Vec<ImmUniqId>
}
export interface GraphMapLinkRadioConstructor { new(): GraphMapLinkRadio; }
export interface GraphMapLinkRadio { target: ImmUniqId }
export interface GraphMapNodePropConstructor { new(): GraphMapNodeProp; }
export interface GraphMapNodeProp {
  getAdapter(context: ImmAstContext): ImmAdapter;
  getSubtreeId(context: ImmAstContext): haxorg_wasm.Optional<string>;
  getFootnoteName(context: ImmAstContext): haxorg_wasm.Optional<string>;
  id: ImmUniqId
  unresolved: haxorg_wasm.Vec<GraphMapLink>
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
  adjEdges(node: GraphMapNode): haxorg_wasm.Vec<GraphMapEdge>;
  adjNodes(node: GraphMapNode): haxorg_wasm.Vec<GraphMapNode>;
  outEdges(node: GraphMapNode): haxorg_wasm.Vec<GraphMapEdge>;
  inEdges(node: GraphMapNode): haxorg_wasm.Vec<GraphMapEdge>;
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
export interface GraphMapConfigConstructor { new(): GraphMapConfig; }
export interface GraphMapConfig { dbg: OperationsTracer }
export interface GraphMapGraphStateConstructor { new(): GraphMapGraphState; }
export interface GraphMapGraphState {
  getGraph(): GraphMapGraph;
  FromAstContext(ast: ImmAstContext): GraphMapGraphState;
  registerNode(node: GraphMapNodeProp, conf: GraphMapConfig): void;
  addNode(node: ImmAdapter, conf: GraphMapConfig): void;
  addNodeRec(ast: ImmAstContext, node: ImmAdapter, conf: GraphMapConfig): void;
  getUnresolvedSubtreeLinks(node: ImmSubtreeAdapter, conf: GraphMapConfig): haxorg_wasm.Vec<GraphMapLink>;
  getUnresolvedLink(node: ImmLinkAdapter, conf: GraphMapConfig): haxorg_wasm.Optional<GraphMapLink>;
  graph: GraphMapGraph
  ast: ImmAstContext
}
export interface SourceLocationConstructor { new(): SourceLocation; }
export interface SourceLocation {
  __eq__(other: SourceLocation): boolean;
  SourceLocation(): void;
  line: number
  column: haxorg_wasm.Optional<number>
  file: haxorg_wasm.Optional<string>
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
  sub_variant_get_name(): string;
  sub_variant_get_data(): LispCodeData;
  sub_variant_get_kind(): LispCodeKind;
  data: LispCodeData
}
export interface LispCodeCallConstructor { new(): LispCodeCall; }
export interface LispCodeCall {
  __eq__(other: LispCodeCall): boolean;
  Call(): void;
  name: string
  args: haxorg_wasm.Vec<LispCode>
}
export interface LispCodeListConstructor { new(): LispCodeList; }
export interface LispCodeList {
  __eq__(other: LispCodeList): boolean;
  List(): void;
  items: haxorg_wasm.Vec<LispCode>
}
export interface LispCodeKeyValueConstructor { new(): LispCodeKeyValue; }
export interface LispCodeKeyValue {
  __eq__(other: LispCodeKeyValue): boolean;
  KeyValue(): void;
  name: string
  value: haxorg_wasm.Vec<LispCode>
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
  value: number
}
export type LispCodeData = haxorg_wasm.StdVariant<LispCodeCall, LispCodeList, LispCodeKeyValue, LispCodeNumber, LispCodeText, LispCodeIdent, LispCodeBoolean, LispCodeReal>;
export enum LispCodeKind {
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
  exprs: haxorg_wasm.Vec<TblfmAssign>
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
  sub_variant_get_name(): string;
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
  sub_variant_get_name(): string;
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
export type TblfmExprAxisRefPositionData = haxorg_wasm.StdVariant<TblfmExprAxisRefPositionIndex, TblfmExprAxisRefPositionName>;
export enum TblfmExprAxisRefPositionKind {
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
  value: number
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
  args: haxorg_wasm.Vec<TblfmExpr>
}
export interface TblfmExprElispConstructor { new(): TblfmExprElisp; }
export interface TblfmExprElisp {
  __eq__(other: TblfmExprElisp): boolean;
  value: string
}
export type TblfmExprData = haxorg_wasm.StdVariant<TblfmExprAxisRef, TblfmExprAxisName, TblfmExprIntLiteral, TblfmExprFloatLiteral, TblfmExprRangeRef, TblfmExprCall, TblfmExprElisp>;
export enum TblfmExprKind {
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
  expr: haxorg_wasm.Vec<TblfmExpr>
  flags: haxorg_wasm.Vec<TblfmAssignFlag>
}
export enum TblfmAssignFlag {
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
  getDouble(): haxorg_wasm.Optional<number>;
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
  getKindStatic(__input: AttrValueDataVariant): AttrValueKind;
  getKind(): AttrValueKind;
  sub_variant_get_name(): string;
  sub_variant_get_data(): AttrValueDataVariant;
  sub_variant_get_kind(): AttrValueKind;
  name: haxorg_wasm.Optional<string>
  varname: haxorg_wasm.Optional<string>
  span: haxorg_wasm.Vec<AttrValueDimensionSpan>
  isQuoted: boolean
  data: AttrValueDataVariant
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
export type AttrValueDataVariant = haxorg_wasm.StdVariant<AttrValueTextValue, AttrValueFileReference, AttrValueLispValue>;
export enum AttrValueKind {
  TextValue,
  FileReference,
  LispValue,
}
export interface HashTagFlatConstructor { new(): HashTagFlat; }
export interface HashTagFlat {
  __eq__(other: HashTagFlat): boolean;
  __lt__(other: HashTagFlat): boolean;
  tags: haxorg_wasm.Vec<string>
}
export interface TodoKeywordConstructor { new(): TodoKeyword; }
export interface TodoKeyword {
  __eq__(other: TodoKeyword): boolean;
  name: string
  shortcut: haxorg_wasm.Optional<string>
  onEnter: TodoKeywordTransition
  onLeave: TodoKeywordTransition
}
export enum TodoKeywordTransition {
  None,
  NoteWithTimestamp,
  Timestamp,
}
export interface HashTagTextConstructor { new(): HashTagText; }
export interface HashTagText {
  __eq__(other: HashTagText): boolean;
  prefixMatch(prefix: haxorg_wasm.Vec<string>): boolean;
  getFlatHashes(withIntermediate: boolean): haxorg_wasm.Vec<HashTagFlat>;
  head: string
  subtags: haxorg_wasm.Vec<HashTagText>
}
export interface SubtreePathConstructor { new(): SubtreePath; }
export interface SubtreePath {
  __eq__(other: SubtreePath): boolean;
  path: haxorg_wasm.Vec<string>
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
  sub_variant_get_name(): string;
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
export type LinkTargetData = haxorg_wasm.StdVariant<LinkTargetRaw, LinkTargetId, LinkTargetCustomId, LinkTargetSubtreeTitle, LinkTargetPerson, LinkTargetUserProtocol, LinkTargetInternal, LinkTargetFootnote, LinkTargetFile, LinkTargetAttachment>;
export enum LinkTargetKind {
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
  sub_variant_get_name(): string;
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
export enum SubtreeLogHeadPriorityAction {
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
export type SubtreeLogHeadLogEntry = haxorg_wasm.StdVariant<SubtreeLogHeadPriority, SubtreeLogHeadNote, SubtreeLogHeadRefile, SubtreeLogHeadClock, SubtreeLogHeadState, SubtreeLogHeadDeadline, SubtreeLogHeadSchedule, SubtreeLogHeadTag, SubtreeLogHeadUnknown>;
export enum SubtreeLogHeadKind {
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
  items: haxorg_wasm.Vec<AttrValue>
}
export interface AttrGroupConstructor { new(): AttrGroup; }
export interface AttrGroup {
  getFlatArgs(): haxorg_wasm.Vec<AttrValue>;
  getAttrs(key: haxorg_wasm.Optional<string>): haxorg_wasm.Vec<AttrValue>;
  setNamedAttr(key: string, attrs: haxorg_wasm.Vec<AttrValue>): void;
  setPositionalAttr(items: haxorg_wasm.Vec<AttrValue>): void;
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
  named: haxorg_wasm.UnorderedMap<string, AttrList>
}
export interface OrgCodeEvalInputConstructor { new(): OrgCodeEvalInput; }
export interface OrgCodeEvalInput {
  __eq__(other: OrgCodeEvalInput): boolean;
  getVariable(name: string): haxorg_wasm.Optional<OrgCodeEvalInputVar>;
  blockAttrs: AttrGroup
  tangledCode: string
  exportType: haxorg_wasm.Optional<string>
  resultType: OrgCodeEvalInputResultType
  resultFormat: OrgCodeEvalInputResultFormat
  resultHandling: OrgCodeEvalInputResultHandling
  language: string
  argList: haxorg_wasm.Vec<OrgCodeEvalInputVar>
}
export interface OrgCodeEvalInputVarConstructor { new(): OrgCodeEvalInputVar; }
export interface OrgCodeEvalInputVar {
  __eq__(other: OrgCodeEvalInputVar): boolean;
  Var(): void;
  name: string
  value: OrgJson
}
export enum OrgCodeEvalInputResultType {
  None,
  Table,
  List,
  Scalar,
  SaveFile,
}
export enum OrgCodeEvalInputResultFormat {
  None,
  Raw,
  Code,
  Drawer,
  ExportType,
  Link,
}
export enum OrgCodeEvalInputResultHandling {
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
  args: haxorg_wasm.Vec<string>
  cwd: string
  appliedHeaderArg: AttrGroup
}
export interface ColumnViewConstructor { new(): ColumnView; }
export interface ColumnView {
  __eq__(other: ColumnView): boolean;
  columns: haxorg_wasm.Vec<ColumnViewColumn>
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
  sub_variant_get_name(): string;
  sub_variant_get_data(): ColumnViewSummaryData;
  sub_variant_get_kind(): ColumnViewSummaryKind;
  data: ColumnViewSummaryData
}
export interface ColumnViewSummaryCheckboxAggregateConstructor { new(): ColumnViewSummaryCheckboxAggregate; }
export interface ColumnViewSummaryCheckboxAggregate {
  __eq__(other: ColumnViewSummaryCheckboxAggregate): boolean;
  kind: ColumnViewSummaryCheckboxAggregateKind
}
export enum ColumnViewSummaryCheckboxAggregateKind {
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
export enum ColumnViewSummaryMathAggregateKind {
  Min,
  Max,
  Mean,
  Sum,
  LowHighEst,
}
export type ColumnViewSummaryData = haxorg_wasm.StdVariant<ColumnViewSummaryCheckboxAggregate, ColumnViewSummaryMathAggregate>;
export enum ColumnViewSummaryKind {
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
  parts: haxorg_wasm.Vec<BlockCodeLinePart>
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
  sub_variant_get_name(): string;
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
export type BlockCodeLinePartData = haxorg_wasm.StdVariant<BlockCodeLinePartRaw, BlockCodeLinePartCallout, BlockCodeLinePartTangle>;
export enum BlockCodeLinePartKind {
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
  sub_variant_get_name(): string;
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
  taskWhitelist: haxorg_wasm.Vec<string>
}
export enum DocumentExportConfigTagExport {
  None,
  All,
  NotInToc,
}
export enum DocumentExportConfigTaskFiltering {
  Whitelist,
  Done,
  None,
  All,
}
export enum DocumentExportConfigBrokenLinks {
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
export type DocumentExportConfigTocExport = haxorg_wasm.StdVariant<DocumentExportConfigDoExport, DocumentExportConfigExportFixed>;
export enum DocumentExportConfigTocExportKind {
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
export enum SubtreePeriodKind {
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
  isCustomId(): boolean;
  getCustomIdConst(): NamedPropertyCustomId;
  getCustomIdMut(): NamedPropertyCustomId;
  isCustomSubtreeJson(): boolean;
  getCustomSubtreeJsonConst(): NamedPropertyCustomSubtreeJson;
  getCustomSubtreeJsonMut(): NamedPropertyCustomSubtreeJson;
  isCustomSubtreeFlags(): boolean;
  getCustomSubtreeFlagsConst(): NamedPropertyCustomSubtreeFlags;
  getCustomSubtreeFlagsMut(): NamedPropertyCustomSubtreeFlags;
  getKindStatic(__input: NamedPropertyData): NamedPropertyKind;
  getKind(): NamedPropertyKind;
  sub_variant_get_name(): string;
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
  options: haxorg_wasm.Vec<string>
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
export enum NamedPropertyVisibilityLevel {
  Folded,
  Children,
  Content,
  All,
}
export interface NamedPropertyExportOptionsConstructor { new(): NamedPropertyExportOptions; }
export interface NamedPropertyExportOptions {
  __eq__(other: NamedPropertyExportOptions): boolean;
  backend: string
  values: haxorg_wasm.UnorderedMap<string, string>
}
export interface NamedPropertyBlockerConstructor { new(): NamedPropertyBlocker; }
export interface NamedPropertyBlocker {
  __eq__(other: NamedPropertyBlocker): boolean;
  blockers: haxorg_wasm.Vec<string>
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
  words: haxorg_wasm.Vec<string>
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
export interface NamedPropertyCustomIdConstructor { new(): NamedPropertyCustomId; }
export interface NamedPropertyCustomId {
  __eq__(other: NamedPropertyCustomId): boolean;
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
export type NamedPropertyData = haxorg_wasm.StdVariant<NamedPropertyNonblocking, NamedPropertyArchiveTime, NamedPropertyArchiveFile, NamedPropertyArchiveOlpath, NamedPropertyArchiveTarget, NamedPropertyArchiveCategory, NamedPropertyArchiveTodo, NamedPropertyTrigger, NamedPropertyExportLatexClass, NamedPropertyCookieData, NamedPropertyExportLatexClassOptions, NamedPropertyExportLatexHeader, NamedPropertyExportLatexCompiler, NamedPropertyOrdered, NamedPropertyEffort, NamedPropertyVisibility, NamedPropertyExportOptions, NamedPropertyBlocker, NamedPropertyUnnumbered, NamedPropertyCreated, NamedPropertyRadioId, NamedPropertyHashtagDef, NamedPropertyCustomArgs, NamedPropertyCustomRaw, NamedPropertyCustomId, NamedPropertyCustomSubtreeJson, NamedPropertyCustomSubtreeFlags>;
export enum NamedPropertyKind {
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
  CustomId,
  CustomSubtreeJson,
  CustomSubtreeFlags,
}
export interface OrgDiagnosticsConstructor { new(): OrgDiagnostics; }
export interface OrgDiagnostics {
  __eq__(other: OrgDiagnostics): boolean;
  isParseTokenError(): boolean;
  getParseTokenErrorConst(): OrgDiagnosticsParseTokenError;
  getParseTokenErrorMut(): OrgDiagnosticsParseTokenError;
  isParseError(): boolean;
  getParseErrorConst(): OrgDiagnosticsParseError;
  getParseErrorMut(): OrgDiagnosticsParseError;
  isIncludeError(): boolean;
  getIncludeErrorConst(): OrgDiagnosticsIncludeError;
  getIncludeErrorMut(): OrgDiagnosticsIncludeError;
  isConvertError(): boolean;
  getConvertErrorConst(): OrgDiagnosticsConvertError;
  getConvertErrorMut(): OrgDiagnosticsConvertError;
  isInternalError(): boolean;
  getInternalErrorConst(): OrgDiagnosticsInternalError;
  getInternalErrorMut(): OrgDiagnosticsInternalError;
  getKindStatic(__input: OrgDiagnosticsData): OrgDiagnosticsKind;
  getKind(): OrgDiagnosticsKind;
  sub_variant_get_name(): string;
  sub_variant_get_data(): OrgDiagnosticsData;
  sub_variant_get_kind(): OrgDiagnosticsKind;
  data: OrgDiagnosticsData
}
export interface OrgDiagnosticsParseTokenErrorConstructor { new(): OrgDiagnosticsParseTokenError; }
export interface OrgDiagnosticsParseTokenError {
  __eq__(other: OrgDiagnosticsParseTokenError): boolean;
  brief: string
  detail: string
  parserFunction: string
  parserLine: number
  tokenKind: OrgTokenKind
  tokenText: string
  loc: SourceLocation
  errName: string
  errCode: string
}
export interface OrgDiagnosticsParseErrorConstructor { new(): OrgDiagnosticsParseError; }
export interface OrgDiagnosticsParseError {
  __eq__(other: OrgDiagnosticsParseError): boolean;
  brief: string
  detail: string
  parserFunction: string
  parserLine: number
  errName: string
  errCode: string
  loc: SourceLocation
}
export interface OrgDiagnosticsIncludeErrorConstructor { new(): OrgDiagnosticsIncludeError; }
export interface OrgDiagnosticsIncludeError {
  __eq__(other: OrgDiagnosticsIncludeError): boolean;
  brief: string
  targetPath: string
  workingFile: string
}
export interface OrgDiagnosticsConvertErrorConstructor { new(): OrgDiagnosticsConvertError; }
export interface OrgDiagnosticsConvertError {
  __eq__(other: OrgDiagnosticsConvertError): boolean;
  brief: string
  detail: string
  convertFunction: string
  convertLine: number
  convertFile: string
  errName: string
  errCode: string
  loc: haxorg_wasm.Optional<SourceLocation>
}
export interface OrgDiagnosticsInternalErrorConstructor { new(): OrgDiagnosticsInternalError; }
export interface OrgDiagnosticsInternalError {
  __eq__(other: OrgDiagnosticsInternalError): boolean;
  message: string
  function: string
  line: number
  file: string
  loc: haxorg_wasm.Optional<SourceLocation>
}
export type OrgDiagnosticsData = haxorg_wasm.StdVariant<OrgDiagnosticsParseTokenError, OrgDiagnosticsParseError, OrgDiagnosticsIncludeError, OrgDiagnosticsConvertError, OrgDiagnosticsInternalError>;
export enum OrgDiagnosticsKind {
  ParseTokenError,
  ParseError,
  IncludeError,
  ConvertError,
  InternalError,
}
export interface NoneConstructor { new(): None; }
export interface None { getKind(): OrgSemKind; }
export interface ErrorItemConstructor { new(): ErrorItem; }
export interface ErrorItem {
  getKind(): OrgSemKind;
  diag: OrgDiagnostics
}
export interface ErrorGroupConstructor { new(): ErrorGroup; }
export interface ErrorGroup {
  getKind(): OrgSemKind;
  diagnostics: haxorg_wasm.Vec<ErrorItem>
}
export interface StmtConstructor { new(): Stmt; }
export interface Stmt {
  getAttached(kind: haxorg_wasm.Optional<string>): haxorg_wasm.Vec<Org>;
  getCaption(): haxorg_wasm.Vec<Org>;
  getName(): haxorg_wasm.Vec<string>;
  getAttrs(kind: haxorg_wasm.Optional<string>): haxorg_wasm.Vec<AttrValue>;
  getFirstAttr(kind: string): haxorg_wasm.Optional<AttrValue>;
  getFirstAttrString(kind: string): haxorg_wasm.Optional<string>;
  getFirstAttrInt(kind: string): haxorg_wasm.Optional<number>;
  getFirstAttrBool(kind: string): haxorg_wasm.Optional<boolean>;
  getFirstAttrDouble(kind: string): haxorg_wasm.Optional<number>;
  getFirstAttrLisp(kind: string): haxorg_wasm.Optional<AttrValueLispValue>;
  getFirstAttrKind(kind: string): haxorg_wasm.Optional<AttrValueKind>;
  attached: haxorg_wasm.Vec<Org>
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
  sub_variant_get_name(): string;
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
export enum TimeRepeatMode {
  None,
  Exact,
  FirstMatch,
  SameDay,
}
export enum TimeRepeatPeriod {
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
  repeat: haxorg_wasm.Vec<TimeRepeat>
  warn: haxorg_wasm.Optional<TimeRepeat>
  time: UserTime
}
export interface TimeDynamicConstructor { new(): TimeDynamic; }
export interface TimeDynamic {
  Dynamic(): void;
  expr: LispCode
}
export type TimeTimeVariant = haxorg_wasm.StdVariant<TimeStatic, TimeDynamic>;
export enum TimeTimeKind {
  Static,
  Dynamic,
}
export interface TimeRangeConstructor { new(): TimeRange; }
export interface TimeRange {
  getKind(): OrgSemKind;
  getClockedTimeSeconds(): haxorg_wasm.Optional<Int64_t>;
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
  parameters: haxorg_wasm.Vec<SymbolParam>
  positional: haxorg_wasm.Vec<Org>
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
  words: haxorg_wasm.Vec<string>
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
  getTimePeriods(kinds: haxorg_wasm.IntSet<SubtreePeriodKind>): haxorg_wasm.Vec<SubtreePeriod>;
  getProperties(kind: string, subkind: haxorg_wasm.Optional<string>): haxorg_wasm.Vec<NamedProperty>;
  getProperty(kind: string, subkind: haxorg_wasm.Optional<string>): haxorg_wasm.Optional<NamedProperty>;
  removeProperty(kind: string, subkind: haxorg_wasm.Optional<string>): void;
  setProperty(value: NamedProperty): void;
  setPropertyStrValue(value: string, kind: string, subkind: haxorg_wasm.Optional<string>): void;
  getCleanTitle(): string;
  getTodoKeyword(): haxorg_wasm.Optional<string>;
  level: number
  treeId: haxorg_wasm.Optional<string>
  todo: haxorg_wasm.Optional<string>
  completion: haxorg_wasm.Optional<SubtreeCompletion>
  description: haxorg_wasm.Optional<Paragraph>
  tags: haxorg_wasm.Vec<HashTag>
  title: Paragraph
  logbook: haxorg_wasm.Vec<SubtreeLog>
  properties: haxorg_wasm.Vec<NamedProperty>
  closed: haxorg_wasm.Optional<Time>
  deadline: haxorg_wasm.Optional<Time>
  scheduled: haxorg_wasm.Optional<Time>
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
  getProperties(kind: string, subKind: haxorg_wasm.Optional<string>): haxorg_wasm.Vec<NamedProperty>;
  getProperty(kind: string, subKind: haxorg_wasm.Optional<string>): haxorg_wasm.Optional<NamedProperty>;
  initialVisibility: InitialSubtreeVisibility
  properties: haxorg_wasm.Vec<NamedProperty>
  exportConfig: DocumentExportConfig
  fixedWidthSections: haxorg_wasm.Optional<boolean>
  startupIndented: haxorg_wasm.Optional<boolean>
  category: haxorg_wasm.Optional<string>
  setupfile: haxorg_wasm.Optional<string>
  maxSubtreeLevelExport: haxorg_wasm.Optional<number>
  columns: haxorg_wasm.Optional<ColumnView>
  todoKeywords: haxorg_wasm.Vec<TodoKeyword>
  doneKeywords: haxorg_wasm.Vec<TodoKeyword>
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
export enum CriticMarkupKind {
  Deletion,
  Addition,
  Substitution,
  Highlighting,
  Comment,
}
export interface DocumentConstructor { new(): Document; }
export interface Document {
  getKind(): OrgSemKind;
  getProperties(kind: string, subKind: haxorg_wasm.Optional<string>): haxorg_wasm.Vec<NamedProperty>;
  getProperty(kind: string, subKind: haxorg_wasm.Optional<string>): haxorg_wasm.Optional<NamedProperty>;
  title: haxorg_wasm.Optional<Paragraph>
  author: haxorg_wasm.Optional<Paragraph>
  creator: haxorg_wasm.Optional<Paragraph>
  filetags: haxorg_wasm.Vec<HashTag>
  email: haxorg_wasm.Optional<RawText>
  language: haxorg_wasm.Vec<string>
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
  sub_variant_get_name(): string;
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
export type FileData = haxorg_wasm.StdVariant<FileDocument, FileAttachment, FileSource>;
export enum FileKind {
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
  sub_variant_get_name(): string;
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
export type CmdIncludeData = haxorg_wasm.StdVariant<CmdIncludeExample, CmdIncludeExport, CmdIncludeCustom, CmdIncludeSrc, CmdIncludeOrgDocument>;
export enum CmdIncludeKind {
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
export interface ImmNoneConstructor { new(): ImmNone; }
export interface ImmNone {
  getKind(): OrgSemKind;
  __eq__(other: ImmNone): boolean;
}
export interface ImmErrorItemConstructor { new(): ImmErrorItem; }
export interface ImmErrorItem {
  getKind(): OrgSemKind;
  __eq__(other: ImmErrorItem): boolean;
  diag: OrgDiagnostics
}
export interface ImmErrorGroupConstructor { new(): ImmErrorGroup; }
export interface ImmErrorGroup {
  getKind(): OrgSemKind;
  __eq__(other: ImmErrorGroup): boolean;
  diagnostics: haxorg_wasm.ImmVec<haxorg_wasm.ImmIdT<ImmErrorItem>>
}
export interface ImmStmtConstructor { new(): ImmStmt; }
export interface ImmStmt {
  __eq__(other: ImmStmt): boolean;
  attached: haxorg_wasm.ImmVec<haxorg_wasm.ImmIdT<ImmOrg>>
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
  text: haxorg_wasm.ImmBox<string>
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
  sub_variant_get_name(): string;
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
export enum ImmTimeRepeatMode {
  None,
  Exact,
  FirstMatch,
  SameDay,
}
export enum ImmTimeRepeatPeriod {
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
  repeat: haxorg_wasm.ImmVec<ImmTimeRepeat>
  warn: haxorg_wasm.ImmBox<haxorg_wasm.Optional<ImmTimeRepeat>>
  time: UserTime
}
export interface ImmTimeDynamicConstructor { new(): ImmTimeDynamic; }
export interface ImmTimeDynamic {
  Dynamic(): void;
  __eq__(other: ImmTimeDynamic): boolean;
  expr: LispCode
}
export type ImmTimeTimeVariant = haxorg_wasm.StdVariant<ImmTimeStatic, ImmTimeDynamic>;
export enum ImmTimeTimeKind {
  Static,
  Dynamic,
}
export interface ImmTimeRangeConstructor { new(): ImmTimeRange; }
export interface ImmTimeRange {
  getKind(): OrgSemKind;
  __eq__(other: ImmTimeRange): boolean;
  from: haxorg_wasm.ImmIdT<ImmTime>
  to: haxorg_wasm.ImmIdT<ImmTime>
}
export interface ImmMacroConstructor { new(): ImmMacro; }
export interface ImmMacro {
  getKind(): OrgSemKind;
  __eq__(other: ImmMacro): boolean;
  name: haxorg_wasm.ImmBox<string>
  attrs: AttrGroup
}
export interface ImmSymbolConstructor { new(): ImmSymbol; }
export interface ImmSymbol {
  getKind(): OrgSemKind;
  __eq__(other: ImmSymbol): boolean;
  name: haxorg_wasm.ImmBox<string>
  parameters: haxorg_wasm.ImmVec<ImmSymbolParam>
  positional: haxorg_wasm.ImmVec<haxorg_wasm.ImmIdT<ImmOrg>>
}
export interface ImmSymbolParamConstructor { new(): ImmSymbolParam; }
export interface ImmSymbolParam {
  __eq__(other: ImmSymbolParam): boolean;
  key: haxorg_wasm.ImmBox<haxorg_wasm.Optional<string>>
  value: haxorg_wasm.ImmBox<string>
}
export interface ImmMarkupConstructor { new(): ImmMarkup; }
export interface ImmMarkup { __eq__(other: ImmMarkup): boolean; }
export interface ImmRadioTargetConstructor { new(): ImmRadioTarget; }
export interface ImmRadioTarget {
  getKind(): OrgSemKind;
  __eq__(other: ImmRadioTarget): boolean;
  words: haxorg_wasm.ImmVec<string>
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
  desc: haxorg_wasm.ImmBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmStmtList>>>
}
export interface ImmSubtreeConstructor { new(): ImmSubtree; }
export interface ImmSubtree {
  getKind(): OrgSemKind;
  __eq__(other: ImmSubtree): boolean;
  level: number
  treeId: haxorg_wasm.ImmBox<haxorg_wasm.Optional<string>>
  todo: haxorg_wasm.ImmBox<haxorg_wasm.Optional<string>>
  completion: haxorg_wasm.ImmBox<haxorg_wasm.Optional<SubtreeCompletion>>
  description: haxorg_wasm.ImmBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmParagraph>>>
  tags: haxorg_wasm.ImmVec<haxorg_wasm.ImmIdT<ImmHashTag>>
  title: haxorg_wasm.ImmIdT<ImmParagraph>
  logbook: haxorg_wasm.ImmVec<haxorg_wasm.ImmIdT<ImmSubtreeLog>>
  properties: haxorg_wasm.ImmVec<NamedProperty>
  closed: haxorg_wasm.ImmBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmTime>>>
  deadline: haxorg_wasm.ImmBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmTime>>>
  scheduled: haxorg_wasm.ImmBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmTime>>>
  isComment: boolean
  isArchived: boolean
  priority: haxorg_wasm.ImmBox<haxorg_wasm.Optional<string>>
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
  name: haxorg_wasm.ImmBox<string>
  attrs: AttrGroup
  isCommand: boolean
}
export interface ImmListItemConstructor { new(): ImmListItem; }
export interface ImmListItem {
  getKind(): OrgSemKind;
  __eq__(other: ImmListItem): boolean;
  checkbox: CheckboxState
  header: haxorg_wasm.ImmBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmParagraph>>>
  bullet: haxorg_wasm.ImmBox<haxorg_wasm.Optional<string>>
}
export interface ImmDocumentOptionsConstructor { new(): ImmDocumentOptions; }
export interface ImmDocumentOptions {
  getKind(): OrgSemKind;
  __eq__(other: ImmDocumentOptions): boolean;
  initialVisibility: InitialSubtreeVisibility
  properties: haxorg_wasm.ImmVec<NamedProperty>
  exportConfig: DocumentExportConfig
  fixedWidthSections: haxorg_wasm.ImmBox<haxorg_wasm.Optional<boolean>>
  startupIndented: haxorg_wasm.ImmBox<haxorg_wasm.Optional<boolean>>
  category: haxorg_wasm.ImmBox<haxorg_wasm.Optional<string>>
  setupfile: haxorg_wasm.ImmBox<haxorg_wasm.Optional<string>>
  maxSubtreeLevelExport: haxorg_wasm.ImmBox<haxorg_wasm.Optional<number>>
  columns: haxorg_wasm.ImmBox<haxorg_wasm.Optional<ColumnView>>
  todoKeywords: haxorg_wasm.ImmVec<TodoKeyword>
  doneKeywords: haxorg_wasm.ImmVec<TodoKeyword>
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
export enum ImmCriticMarkupKind {
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
  title: haxorg_wasm.ImmBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmParagraph>>>
  author: haxorg_wasm.ImmBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmParagraph>>>
  creator: haxorg_wasm.ImmBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmParagraph>>>
  filetags: haxorg_wasm.ImmVec<haxorg_wasm.ImmIdT<ImmHashTag>>
  email: haxorg_wasm.ImmBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmRawText>>>
  language: haxorg_wasm.ImmVec<string>
  options: haxorg_wasm.ImmIdT<ImmDocumentOptions>
  exportFileName: haxorg_wasm.ImmBox<haxorg_wasm.Optional<string>>
}
export interface ImmFileTargetConstructor { new(): ImmFileTarget; }
export interface ImmFileTarget {
  getKind(): OrgSemKind;
  __eq__(other: ImmFileTarget): boolean;
  path: haxorg_wasm.ImmBox<string>
  line: haxorg_wasm.ImmBox<haxorg_wasm.Optional<number>>
  searchTarget: haxorg_wasm.ImmBox<haxorg_wasm.Optional<string>>
  restrictToHeadlines: boolean
  targetId: haxorg_wasm.ImmBox<haxorg_wasm.Optional<string>>
  regexp: haxorg_wasm.ImmBox<haxorg_wasm.Optional<string>>
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
  sub_variant_get_name(): string;
  sub_variant_get_data(): ImmFileData;
  sub_variant_get_kind(): ImmFileKind;
  relPath: haxorg_wasm.ImmBox<string>
  absPath: haxorg_wasm.ImmBox<string>
  data: ImmFileData
}
export interface ImmFileDocumentConstructor { new(): ImmFileDocument; }
export interface ImmFileDocument { __eq__(other: ImmFileDocument): boolean; }
export interface ImmFileAttachmentConstructor { new(): ImmFileAttachment; }
export interface ImmFileAttachment { __eq__(other: ImmFileAttachment): boolean; }
export interface ImmFileSourceConstructor { new(): ImmFileSource; }
export interface ImmFileSource { __eq__(other: ImmFileSource): boolean; }
export type ImmFileData = haxorg_wasm.StdVariant<ImmFileDocument, ImmFileAttachment, ImmFileSource>;
export enum ImmFileKind {
  Document,
  Attachment,
  Source,
}
export interface ImmDirectoryConstructor { new(): ImmDirectory; }
export interface ImmDirectory {
  getKind(): OrgSemKind;
  __eq__(other: ImmDirectory): boolean;
  relPath: haxorg_wasm.ImmBox<string>
  absPath: haxorg_wasm.ImmBox<string>
}
export interface ImmSymlinkConstructor { new(): ImmSymlink; }
export interface ImmSymlink {
  getKind(): OrgSemKind;
  __eq__(other: ImmSymlink): boolean;
  isDirectory: boolean
  absPath: haxorg_wasm.ImmBox<string>
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
  sub_variant_get_name(): string;
  sub_variant_get_data(): ImmCmdIncludeData;
  sub_variant_get_kind(): ImmCmdIncludeKind;
  path: haxorg_wasm.ImmBox<string>
  firstLine: haxorg_wasm.ImmBox<haxorg_wasm.Optional<number>>
  lastLine: haxorg_wasm.ImmBox<haxorg_wasm.Optional<number>>
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
  language: haxorg_wasm.ImmBox<string>
}
export interface ImmCmdIncludeCustomConstructor { new(): ImmCmdIncludeCustom; }
export interface ImmCmdIncludeCustom {
  Custom(): void;
  __eq__(other: ImmCmdIncludeCustom): boolean;
  blockName: haxorg_wasm.ImmBox<string>
}
export interface ImmCmdIncludeSrcConstructor { new(): ImmCmdIncludeSrc; }
export interface ImmCmdIncludeSrc {
  Src(): void;
  __eq__(other: ImmCmdIncludeSrc): boolean;
  language: haxorg_wasm.ImmBox<string>
}
export interface ImmCmdIncludeOrgDocumentConstructor { new(): ImmCmdIncludeOrgDocument; }
export interface ImmCmdIncludeOrgDocument {
  OrgDocument(): void;
  __eq__(other: ImmCmdIncludeOrgDocument): boolean;
  onlyContent: haxorg_wasm.ImmBox<haxorg_wasm.Optional<boolean>>
  subtreePath: haxorg_wasm.ImmBox<haxorg_wasm.Optional<SubtreePath>>
  minLevel: haxorg_wasm.ImmBox<haxorg_wasm.Optional<number>>
  customIdTarget: haxorg_wasm.ImmBox<haxorg_wasm.Optional<string>>
}
export type ImmCmdIncludeData = haxorg_wasm.StdVariant<ImmCmdIncludeExample, ImmCmdIncludeExport, ImmCmdIncludeCustom, ImmCmdIncludeSrc, ImmCmdIncludeOrgDocument>;
export enum ImmCmdIncludeKind {
  Example,
  Export,
  Custom,
  Src,
  OrgDocument,
}
export interface ImmNoneValueConstructor { new(): ImmNoneValue; }
export interface ImmNoneValue {  }
export interface ImmErrorItemValueConstructor { new(): ImmErrorItemValue; }
export interface ImmErrorItemValue { setDiag(value: OrgDiagnostics): void; }
export interface ImmErrorGroupValueConstructor { new(): ImmErrorGroupValue; }
export interface ImmErrorGroupValue { setDiagnostics(value: haxorg_wasm.ImmerFlex_vector<haxorg_wasm.ImmIdT<ImmErrorItem>>): void; }
export interface ImmStmtListValueConstructor { new(): ImmStmtListValue; }
export interface ImmStmtListValue {  }
export interface ImmEmptyValueConstructor { new(): ImmEmptyValue; }
export interface ImmEmptyValue {  }
export interface ImmCmdCaptionValueConstructor { new(): ImmCmdCaptionValue; }
export interface ImmCmdCaptionValue { setText(value: haxorg_wasm.ImmIdT<ImmParagraph>): void; }
export interface ImmCmdColumnsValueConstructor { new(): ImmCmdColumnsValue; }
export interface ImmCmdColumnsValue { setView(value: ColumnView): void; }
export interface ImmCmdNameValueConstructor { new(): ImmCmdNameValue; }
export interface ImmCmdNameValue { setName(value: haxorg_wasm.ImmerBox<string>): void; }
export interface ImmCmdCustomArgsValueConstructor { new(): ImmCmdCustomArgsValue; }
export interface ImmCmdCustomArgsValue {
  setName(value: haxorg_wasm.ImmerBox<string>): void;
  setIsattached(value: boolean): void;
}
export interface ImmCmdCustomRawValueConstructor { new(): ImmCmdCustomRawValue; }
export interface ImmCmdCustomRawValue {
  setName(value: haxorg_wasm.ImmerBox<string>): void;
  setIsattached(value: boolean): void;
  setText(value: haxorg_wasm.ImmerBox<string>): void;
}
export interface ImmCmdCustomTextValueConstructor { new(): ImmCmdCustomTextValue; }
export interface ImmCmdCustomTextValue {
  setName(value: haxorg_wasm.ImmerBox<string>): void;
  setIsattached(value: boolean): void;
  setText(value: haxorg_wasm.ImmIdT<ImmParagraph>): void;
}
export interface ImmCmdCallValueConstructor { new(): ImmCmdCallValue; }
export interface ImmCmdCallValue {
  setName(value: haxorg_wasm.ImmerBox<string>): void;
  setFilename(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<string>>): void;
  setInsideheaderattrs(value: AttrGroup): void;
  setCallattrs(value: AttrGroup): void;
  setEndheaderattrs(value: AttrGroup): void;
  setResult(value: haxorg_wasm.ImmerFlex_vector<haxorg_wasm.ImmIdT<ImmBlockCodeEvalResult>>): void;
}
export interface ImmCmdTblfmValueConstructor { new(): ImmCmdTblfmValue; }
export interface ImmCmdTblfmValue { setExpr(value: Tblfm): void; }
export interface ImmHashTagValueConstructor { new(): ImmHashTagValue; }
export interface ImmHashTagValue { setText(value: HashTagText): void; }
export interface ImmInlineFootnoteValueConstructor { new(): ImmInlineFootnoteValue; }
export interface ImmInlineFootnoteValue {
  setTag(value: haxorg_wasm.ImmerBox<string>): void;
  setDefinition(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmOrg>>>): void;
}
export interface ImmInlineExportValueConstructor { new(): ImmInlineExportValue; }
export interface ImmInlineExportValue {
  setExporter(value: haxorg_wasm.ImmerBox<string>): void;
  setContent(value: haxorg_wasm.ImmerBox<string>): void;
}
export interface ImmTimeValueConstructor { new(): ImmTimeValue; }
export interface ImmTimeValue {
  setIsactive(value: boolean): void;
  setTime(value: ImmTimeTimeVariant): void;
}
export interface ImmTimeRangeValueConstructor { new(): ImmTimeRangeValue; }
export interface ImmTimeRangeValue {
  setFrom(value: haxorg_wasm.ImmIdT<ImmTime>): void;
  setTo(value: haxorg_wasm.ImmIdT<ImmTime>): void;
}
export interface ImmMacroValueConstructor { new(): ImmMacroValue; }
export interface ImmMacroValue {
  setName(value: haxorg_wasm.ImmerBox<string>): void;
  setAttrs(value: AttrGroup): void;
}
export interface ImmSymbolValueConstructor { new(): ImmSymbolValue; }
export interface ImmSymbolValue {
  setName(value: haxorg_wasm.ImmerBox<string>): void;
  setParameters(value: haxorg_wasm.ImmerFlex_vector<ImmSymbolParam>): void;
  setPositional(value: haxorg_wasm.ImmerFlex_vector<haxorg_wasm.ImmIdT<ImmOrg>>): void;
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
export interface ImmRadioTargetValue { setWords(value: haxorg_wasm.ImmerFlex_vector<string>): void; }
export interface ImmLatexValueConstructor { new(): ImmLatexValue; }
export interface ImmLatexValue {  }
export interface ImmLinkValueConstructor { new(): ImmLinkValue; }
export interface ImmLinkValue {
  setDescription(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmParagraph>>>): void;
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
export interface ImmBlockDynamicFallbackValue { setName(value: haxorg_wasm.ImmerBox<string>): void; }
export interface ImmBlockExampleValueConstructor { new(): ImmBlockExampleValue; }
export interface ImmBlockExampleValue {  }
export interface ImmBlockExportValueConstructor { new(): ImmBlockExportValue; }
export interface ImmBlockExportValue {
  setExporter(value: haxorg_wasm.ImmerBox<string>): void;
  setContent(value: haxorg_wasm.ImmerBox<string>): void;
}
export interface ImmBlockAdmonitionValueConstructor { new(): ImmBlockAdmonitionValue; }
export interface ImmBlockAdmonitionValue {  }
export interface ImmBlockCodeEvalResultValueConstructor { new(): ImmBlockCodeEvalResultValue; }
export interface ImmBlockCodeEvalResultValue {
  setRaw(value: haxorg_wasm.ImmerFlex_vector<OrgCodeEvalOutput>): void;
  setNode(value: haxorg_wasm.ImmIdT<ImmOrg>): void;
}
export interface ImmBlockCodeValueConstructor { new(): ImmBlockCodeValue; }
export interface ImmBlockCodeValue {
  setLang(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<string>>): void;
  setResult(value: haxorg_wasm.ImmerFlex_vector<haxorg_wasm.ImmIdT<ImmBlockCodeEvalResult>>): void;
  setLines(value: haxorg_wasm.ImmerFlex_vector<BlockCodeLine>): void;
  setSwitches(value: AttrGroup): void;
}
export interface ImmSubtreeLogValueConstructor { new(): ImmSubtreeLogValue; }
export interface ImmSubtreeLogValue {
  setHead(value: SubtreeLogHead): void;
  setDesc(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmStmtList>>>): void;
}
export interface ImmSubtreeValueConstructor { new(): ImmSubtreeValue; }
export interface ImmSubtreeValue {
  setLevel(value: number): void;
  setTreeid(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<string>>): void;
  setTodo(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<string>>): void;
  setCompletion(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<SubtreeCompletion>>): void;
  setDescription(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmParagraph>>>): void;
  setTags(value: haxorg_wasm.ImmerFlex_vector<haxorg_wasm.ImmIdT<ImmHashTag>>): void;
  setTitle(value: haxorg_wasm.ImmIdT<ImmParagraph>): void;
  setLogbook(value: haxorg_wasm.ImmerFlex_vector<haxorg_wasm.ImmIdT<ImmSubtreeLog>>): void;
  setProperties(value: haxorg_wasm.ImmerFlex_vector<NamedProperty>): void;
  setClosed(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmTime>>>): void;
  setDeadline(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmTime>>>): void;
  setScheduled(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmTime>>>): void;
  setIscomment(value: boolean): void;
  setIsarchived(value: boolean): void;
  setPriority(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<string>>): void;
}
export interface ImmCellValueConstructor { new(): ImmCellValue; }
export interface ImmCellValue { setIsblock(value: boolean): void; }
export interface ImmRowValueConstructor { new(): ImmRowValue; }
export interface ImmRowValue {
  setCells(value: haxorg_wasm.ImmerFlex_vector<haxorg_wasm.ImmIdT<ImmCell>>): void;
  setIsblock(value: boolean): void;
}
export interface ImmTableValueConstructor { new(): ImmTableValue; }
export interface ImmTableValue {
  setRows(value: haxorg_wasm.ImmerFlex_vector<haxorg_wasm.ImmIdT<ImmRow>>): void;
  setIsblock(value: boolean): void;
}
export interface ImmParagraphValueConstructor { new(): ImmParagraphValue; }
export interface ImmParagraphValue {  }
export interface ImmColonExampleValueConstructor { new(): ImmColonExampleValue; }
export interface ImmColonExampleValue {  }
export interface ImmCmdAttrValueConstructor { new(): ImmCmdAttrValue; }
export interface ImmCmdAttrValue { setTarget(value: haxorg_wasm.ImmerBox<string>): void; }
export interface ImmCmdExportValueConstructor { new(): ImmCmdExportValue; }
export interface ImmCmdExportValue {
  setExporter(value: haxorg_wasm.ImmerBox<string>): void;
  setContent(value: haxorg_wasm.ImmerBox<string>): void;
}
export interface ImmCallValueConstructor { new(): ImmCallValue; }
export interface ImmCallValue {
  setName(value: haxorg_wasm.ImmerBox<string>): void;
  setAttrs(value: AttrGroup): void;
  setIscommand(value: boolean): void;
}
export interface ImmListValueConstructor { new(): ImmListValue; }
export interface ImmListValue {  }
export interface ImmListItemValueConstructor { new(): ImmListItemValue; }
export interface ImmListItemValue {
  setCheckbox(value: CheckboxState): void;
  setHeader(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmParagraph>>>): void;
  setBullet(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<string>>): void;
}
export interface ImmDocumentOptionsValueConstructor { new(): ImmDocumentOptionsValue; }
export interface ImmDocumentOptionsValue {
  setInitialvisibility(value: InitialSubtreeVisibility): void;
  setProperties(value: haxorg_wasm.ImmerFlex_vector<NamedProperty>): void;
  setExportconfig(value: DocumentExportConfig): void;
  setFixedwidthsections(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<boolean>>): void;
  setStartupindented(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<boolean>>): void;
  setCategory(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<string>>): void;
  setSetupfile(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<string>>): void;
  setMaxsubtreelevelexport(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<number>>): void;
  setColumns(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<ColumnView>>): void;
  setTodokeywords(value: haxorg_wasm.ImmerFlex_vector<TodoKeyword>): void;
  setDonekeywords(value: haxorg_wasm.ImmerFlex_vector<TodoKeyword>): void;
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
  setTitle(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmParagraph>>>): void;
  setAuthor(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmParagraph>>>): void;
  setCreator(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmParagraph>>>): void;
  setFiletags(value: haxorg_wasm.ImmerFlex_vector<haxorg_wasm.ImmIdT<ImmHashTag>>): void;
  setEmail(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmRawText>>>): void;
  setLanguage(value: haxorg_wasm.ImmerFlex_vector<string>): void;
  setOptions(value: haxorg_wasm.ImmIdT<ImmDocumentOptions>): void;
  setExportfilename(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<string>>): void;
}
export interface ImmFileTargetValueConstructor { new(): ImmFileTargetValue; }
export interface ImmFileTargetValue {
  setPath(value: haxorg_wasm.ImmerBox<string>): void;
  setLine(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<number>>): void;
  setSearchtarget(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<string>>): void;
  setRestricttoheadlines(value: boolean): void;
  setTargetid(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<string>>): void;
  setRegexp(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<string>>): void;
}
export interface ImmTextSeparatorValueConstructor { new(): ImmTextSeparatorValue; }
export interface ImmTextSeparatorValue {  }
export interface ImmDocumentGroupValueConstructor { new(): ImmDocumentGroupValue; }
export interface ImmDocumentGroupValue {  }
export interface ImmFileValueConstructor { new(): ImmFileValue; }
export interface ImmFileValue {
  setRelpath(value: haxorg_wasm.ImmerBox<string>): void;
  setAbspath(value: haxorg_wasm.ImmerBox<string>): void;
  setData(value: ImmFileData): void;
}
export interface ImmDirectoryValueConstructor { new(): ImmDirectoryValue; }
export interface ImmDirectoryValue {
  setRelpath(value: haxorg_wasm.ImmerBox<string>): void;
  setAbspath(value: haxorg_wasm.ImmerBox<string>): void;
}
export interface ImmSymlinkValueConstructor { new(): ImmSymlinkValue; }
export interface ImmSymlinkValue {
  setIsdirectory(value: boolean): void;
  setAbspath(value: haxorg_wasm.ImmerBox<string>): void;
}
export interface ImmCmdIncludeValueConstructor { new(): ImmCmdIncludeValue; }
export interface ImmCmdIncludeValue {
  setPath(value: haxorg_wasm.ImmerBox<string>): void;
  setFirstline(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<number>>): void;
  setLastline(value: haxorg_wasm.ImmerBox<haxorg_wasm.Optional<number>>): void;
  setData(value: ImmCmdIncludeData): void;
}
export interface ImmAdapterOrgAPIConstructor { new(): ImmAdapterOrgAPI; }
export interface ImmAdapterOrgAPI {  }
export interface CmdConstructor { new(): Cmd; }
export interface Cmd {
  getAttrs(key: haxorg_wasm.Optional<string>): haxorg_wasm.Vec<AttrValue>;
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
  getAdmonitions(): haxorg_wasm.Vec<string>;
  getAdmonitionNodes(): haxorg_wasm.Vec<BigIdent>;
  hasTimestamp(): boolean;
  getTimestamps(): haxorg_wasm.Vec<UserTime>;
  getTimestampNodes(): haxorg_wasm.Vec<Time>;
  hasLeadHashtags(): boolean;
  getLeadHashtags(): haxorg_wasm.Vec<HashTag>;
  getBody(): haxorg_wasm.Vec<Org>;
}
export interface ListConstructor { new(): List; }
export interface List {
  getKind(): OrgSemKind;
  getListAttrs(key: string): haxorg_wasm.Vec<AttrValue>;
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
export interface ImmCmdConstructor { new(): ImmCmd; }
export interface ImmCmd {
  __eq__(other: ImmCmd): boolean;
  attrs: AttrGroup
}
export interface ImmCmdCustomRawConstructor { new(): ImmCmdCustomRaw; }
export interface ImmCmdCustomRaw {
  getKind(): OrgSemKind;
  __eq__(other: ImmCmdCustomRaw): boolean;
  name: haxorg_wasm.ImmBox<string>
  isAttached: boolean
  text: haxorg_wasm.ImmBox<string>
}
export interface ImmCmdCustomTextConstructor { new(): ImmCmdCustomText; }
export interface ImmCmdCustomText {
  getKind(): OrgSemKind;
  __eq__(other: ImmCmdCustomText): boolean;
  name: haxorg_wasm.ImmBox<string>
  isAttached: boolean
  text: haxorg_wasm.ImmIdT<ImmParagraph>
}
export interface ImmLinkConstructor { new(): ImmLink; }
export interface ImmLink {
  getKind(): OrgSemKind;
  __eq__(other: ImmLink): boolean;
  description: haxorg_wasm.ImmBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmParagraph>>>
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
  tag: haxorg_wasm.ImmBox<string>
  definition: haxorg_wasm.ImmBox<haxorg_wasm.Optional<haxorg_wasm.ImmIdT<ImmOrg>>>
}
export interface ImmInlineExportConstructor { new(): ImmInlineExport; }
export interface ImmInlineExport {
  getKind(): OrgSemKind;
  __eq__(other: ImmInlineExport): boolean;
  exporter: haxorg_wasm.ImmBox<string>
  content: haxorg_wasm.ImmBox<string>
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
  cells: haxorg_wasm.Vec<Cell>
  isBlock: boolean
}
export interface ImmBlockConstructor { new(): ImmBlock; }
export interface ImmBlock { __eq__(other: ImmBlock): boolean; }
export interface ImmLineCommandConstructor { new(): ImmLineCommand; }
export interface ImmLineCommand { __eq__(other: ImmLineCommand): boolean; }
export interface ImmCmdCustomArgsConstructor { new(): ImmCmdCustomArgs; }
export interface ImmCmdCustomArgs {
  getKind(): OrgSemKind;
  __eq__(other: ImmCmdCustomArgs): boolean;
  name: haxorg_wasm.ImmBox<string>
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
  cells: haxorg_wasm.ImmVec<haxorg_wasm.ImmIdT<ImmCell>>
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
  ImmAdapterT(other: ImmAdapter): ImmSubtreeAdapter;
  getValue(): ImmSubtreeValueRead;
}
export interface ImmNoneAdapterConstructor { new(): ImmNoneAdapter; }
export interface ImmNoneAdapter {
  ImmAdapterT(other: ImmAdapter): ImmNoneAdapter;
  getValue(): ImmNoneValueRead;
}
export interface ImmErrorItemAdapterConstructor { new(): ImmErrorItemAdapter; }
export interface ImmErrorItemAdapter {
  ImmAdapterT(other: ImmAdapter): ImmErrorItemAdapter;
  getValue(): ImmErrorItemValueRead;
}
export interface ImmErrorGroupAdapterConstructor { new(): ImmErrorGroupAdapter; }
export interface ImmErrorGroupAdapter {
  ImmAdapterT(other: ImmAdapter): ImmErrorGroupAdapter;
  getValue(): ImmErrorGroupValueRead;
}
export interface ImmStmtListAdapterConstructor { new(): ImmStmtListAdapter; }
export interface ImmStmtListAdapter {
  ImmAdapterT(other: ImmAdapter): ImmStmtListAdapter;
  getValue(): ImmStmtListValueRead;
}
export interface ImmEmptyAdapterConstructor { new(): ImmEmptyAdapter; }
export interface ImmEmptyAdapter {
  ImmAdapterT(other: ImmAdapter): ImmEmptyAdapter;
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
  ImmAdapterT(other: ImmAdapter): ImmTimeAdapter;
  getValue(): ImmTimeValueRead;
}
export interface ImmTimeRangeAdapterConstructor { new(): ImmTimeRangeAdapter; }
export interface ImmTimeRangeAdapter {
  ImmAdapterT(other: ImmAdapter): ImmTimeRangeAdapter;
  getValue(): ImmTimeRangeValueRead;
}
export interface ImmMacroAdapterConstructor { new(): ImmMacroAdapter; }
export interface ImmMacroAdapter {
  ImmAdapterT(other: ImmAdapter): ImmMacroAdapter;
  getValue(): ImmMacroValueRead;
}
export interface ImmSymbolAdapterConstructor { new(): ImmSymbolAdapter; }
export interface ImmSymbolAdapter {
  ImmAdapterT(other: ImmAdapter): ImmSymbolAdapter;
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
  ImmAdapterT(other: ImmAdapter): ImmLatexAdapter;
  getValue(): ImmLatexValueRead;
}
export interface ImmSubtreeLogAdapterConstructor { new(): ImmSubtreeLogAdapter; }
export interface ImmSubtreeLogAdapter {
  ImmAdapterT(other: ImmAdapter): ImmSubtreeLogAdapter;
  getValue(): ImmSubtreeLogValueRead;
}
export interface ImmColonExampleAdapterConstructor { new(): ImmColonExampleAdapter; }
export interface ImmColonExampleAdapter {
  ImmAdapterT(other: ImmAdapter): ImmColonExampleAdapter;
  getValue(): ImmColonExampleValueRead;
}
export interface ImmCallAdapterConstructor { new(): ImmCallAdapter; }
export interface ImmCallAdapter {
  ImmAdapterT(other: ImmAdapter): ImmCallAdapter;
  getValue(): ImmCallValueRead;
}
export interface ImmFileAdapterConstructor { new(): ImmFileAdapter; }
export interface ImmFileAdapter {
  ImmAdapterT(other: ImmAdapter): ImmFileAdapter;
  getValue(): ImmFileValueRead;
}
export interface ImmDirectoryAdapterConstructor { new(): ImmDirectoryAdapter; }
export interface ImmDirectoryAdapter {
  ImmAdapterT(other: ImmAdapter): ImmDirectoryAdapter;
  getValue(): ImmDirectoryValueRead;
}
export interface ImmSymlinkAdapterConstructor { new(): ImmSymlinkAdapter; }
export interface ImmSymlinkAdapter {
  ImmAdapterT(other: ImmAdapter): ImmSymlinkAdapter;
  getValue(): ImmSymlinkValueRead;
}
export interface ImmDocumentFragmentAdapterConstructor { new(): ImmDocumentFragmentAdapter; }
export interface ImmDocumentFragmentAdapter {
  ImmAdapterT(other: ImmAdapter): ImmDocumentFragmentAdapter;
  getValue(): ImmDocumentFragmentValueRead;
}
export interface ImmCriticMarkupAdapterConstructor { new(): ImmCriticMarkupAdapter; }
export interface ImmCriticMarkupAdapter {
  ImmAdapterT(other: ImmAdapter): ImmCriticMarkupAdapter;
  getValue(): ImmCriticMarkupValueRead;
}
export interface ImmListItemAdapterConstructor { new(): ImmListItemAdapter; }
export interface ImmListItemAdapter {
  ImmAdapterT(other: ImmAdapter): ImmListItemAdapter;
  getValue(): ImmListItemValueRead;
}
export interface ImmDocumentOptionsAdapterConstructor { new(): ImmDocumentOptionsAdapter; }
export interface ImmDocumentOptionsAdapter {
  ImmAdapterT(other: ImmAdapter): ImmDocumentOptionsAdapter;
  getValue(): ImmDocumentOptionsValueRead;
}
export interface ImmDocumentAdapterConstructor { new(): ImmDocumentAdapter; }
export interface ImmDocumentAdapter {
  ImmAdapterT(other: ImmAdapter): ImmDocumentAdapter;
  getValue(): ImmDocumentValueRead;
}
export interface ImmFileTargetAdapterConstructor { new(): ImmFileTargetAdapter; }
export interface ImmFileTargetAdapter {
  ImmAdapterT(other: ImmAdapter): ImmFileTargetAdapter;
  getValue(): ImmFileTargetValueRead;
}
export interface ImmTextSeparatorAdapterConstructor { new(): ImmTextSeparatorAdapter; }
export interface ImmTextSeparatorAdapter {
  ImmAdapterT(other: ImmAdapter): ImmTextSeparatorAdapter;
  getValue(): ImmTextSeparatorValueRead;
}
export interface ImmCmdIncludeAdapterConstructor { new(): ImmCmdIncludeAdapter; }
export interface ImmCmdIncludeAdapter {
  ImmAdapterT(other: ImmAdapter): ImmCmdIncludeAdapter;
  getValue(): ImmCmdIncludeValueRead;
}
export interface ImmDocumentGroupAdapterConstructor { new(): ImmDocumentGroupAdapter; }
export interface ImmDocumentGroupAdapter {
  ImmAdapterT(other: ImmAdapter): ImmDocumentGroupAdapter;
  getValue(): ImmDocumentGroupValueRead;
}
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
  raw: haxorg_wasm.Vec<OrgCodeEvalOutput>
  node: Org
}
export interface BlockCodeConstructor { new(): BlockCode; }
export interface BlockCode {
  getKind(): OrgSemKind;
  getVariable(varname: string): haxorg_wasm.Optional<AttrValue>;
  lang: haxorg_wasm.Optional<string>
  result: haxorg_wasm.Vec<BlockCodeEvalResult>
  lines: haxorg_wasm.Vec<BlockCodeLine>
  switches: AttrGroup
}
export interface TableConstructor { new(): Table; }
export interface Table {
  getKind(): OrgSemKind;
  rows: haxorg_wasm.Vec<Row>
  isBlock: boolean
}
export interface AttachedConstructor { new(): Attached; }
export interface Attached {  }
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
  name: haxorg_wasm.ImmBox<string>
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
  exporter: haxorg_wasm.ImmBox<string>
  content: haxorg_wasm.ImmBox<string>
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
  raw: haxorg_wasm.ImmVec<OrgCodeEvalOutput>
  node: haxorg_wasm.ImmIdT<ImmOrg>
}
export interface ImmBlockCodeConstructor { new(): ImmBlockCode; }
export interface ImmBlockCode {
  getKind(): OrgSemKind;
  __eq__(other: ImmBlockCode): boolean;
  lang: haxorg_wasm.ImmBox<haxorg_wasm.Optional<string>>
  result: haxorg_wasm.ImmVec<haxorg_wasm.ImmIdT<ImmBlockCodeEvalResult>>
  lines: haxorg_wasm.ImmVec<BlockCodeLine>
  switches: AttrGroup
}
export interface ImmTableConstructor { new(): ImmTable; }
export interface ImmTable {
  getKind(): OrgSemKind;
  __eq__(other: ImmTable): boolean;
  rows: haxorg_wasm.ImmVec<haxorg_wasm.ImmIdT<ImmRow>>
  isBlock: boolean
}
export interface ImmAttachedConstructor { new(): ImmAttached; }
export interface ImmAttached { __eq__(other: ImmAttached): boolean; }
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
  ImmAdapterT(other: ImmAdapter): ImmCmdCustomRawAdapter;
  getValue(): ImmCmdCustomRawValueRead;
}
export interface ImmCmdCustomTextAdapterConstructor { new(): ImmCmdCustomTextAdapter; }
export interface ImmCmdCustomTextAdapter {
  ImmAdapterT(other: ImmAdapter): ImmCmdCustomTextAdapter;
  getValue(): ImmCmdCustomTextValueRead;
}
export interface ImmLinkAdapterConstructor { new(): ImmLinkAdapter; }
export interface ImmLinkAdapter {
  ImmAdapterT(other: ImmAdapter): ImmLinkAdapter;
  getValue(): ImmLinkValueRead;
}
export interface ImmBlockCommentAdapterConstructor { new(): ImmBlockCommentAdapter; }
export interface ImmBlockCommentAdapter {
  ImmAdapterT(other: ImmAdapter): ImmBlockCommentAdapter;
  getValue(): ImmBlockCommentValueRead;
}
export interface ImmParagraphAdapterConstructor { new(): ImmParagraphAdapter; }
export interface ImmParagraphAdapter {
  ImmAdapterT(other: ImmAdapter): ImmParagraphAdapter;
  getValue(): ImmParagraphValueRead;
}
export interface ImmListAdapterConstructor { new(): ImmListAdapter; }
export interface ImmListAdapter {
  ImmAdapterT(other: ImmAdapter): ImmListAdapter;
  getValue(): ImmListValueRead;
}
export interface ImmHashTagAdapterConstructor { new(): ImmHashTagAdapter; }
export interface ImmHashTagAdapter {
  ImmAdapterT(other: ImmAdapter): ImmHashTagAdapter;
  getValue(): ImmHashTagValueRead;
}
export interface ImmInlineFootnoteAdapterConstructor { new(): ImmInlineFootnoteAdapter; }
export interface ImmInlineFootnoteAdapter {
  ImmAdapterT(other: ImmAdapter): ImmInlineFootnoteAdapter;
  getValue(): ImmInlineFootnoteValueRead;
}
export interface ImmEscapedAdapterConstructor { new(): ImmEscapedAdapter; }
export interface ImmEscapedAdapter {
  ImmAdapterT(other: ImmAdapter): ImmEscapedAdapter;
  getValue(): ImmEscapedValueRead;
}
export interface ImmNewlineAdapterConstructor { new(): ImmNewlineAdapter; }
export interface ImmNewlineAdapter {
  ImmAdapterT(other: ImmAdapter): ImmNewlineAdapter;
  getValue(): ImmNewlineValueRead;
}
export interface ImmSpaceAdapterConstructor { new(): ImmSpaceAdapter; }
export interface ImmSpaceAdapter {
  ImmAdapterT(other: ImmAdapter): ImmSpaceAdapter;
  getValue(): ImmSpaceValueRead;
}
export interface ImmWordAdapterConstructor { new(): ImmWordAdapter; }
export interface ImmWordAdapter {
  ImmAdapterT(other: ImmAdapter): ImmWordAdapter;
  getValue(): ImmWordValueRead;
}
export interface ImmAtMentionAdapterConstructor { new(): ImmAtMentionAdapter; }
export interface ImmAtMentionAdapter {
  ImmAdapterT(other: ImmAdapter): ImmAtMentionAdapter;
  getValue(): ImmAtMentionValueRead;
}
export interface ImmRawTextAdapterConstructor { new(): ImmRawTextAdapter; }
export interface ImmRawTextAdapter {
  ImmAdapterT(other: ImmAdapter): ImmRawTextAdapter;
  getValue(): ImmRawTextValueRead;
}
export interface ImmPunctuationAdapterConstructor { new(): ImmPunctuationAdapter; }
export interface ImmPunctuationAdapter {
  ImmAdapterT(other: ImmAdapter): ImmPunctuationAdapter;
  getValue(): ImmPunctuationValueRead;
}
export interface ImmPlaceholderAdapterConstructor { new(): ImmPlaceholderAdapter; }
export interface ImmPlaceholderAdapter {
  ImmAdapterT(other: ImmAdapter): ImmPlaceholderAdapter;
  getValue(): ImmPlaceholderValueRead;
}
export interface ImmBigIdentAdapterConstructor { new(): ImmBigIdentAdapter; }
export interface ImmBigIdentAdapter {
  ImmAdapterT(other: ImmAdapter): ImmBigIdentAdapter;
  getValue(): ImmBigIdentValueRead;
}
export interface ImmTextTargetAdapterConstructor { new(): ImmTextTargetAdapter; }
export interface ImmTextTargetAdapter {
  ImmAdapterT(other: ImmAdapter): ImmTextTargetAdapter;
  getValue(): ImmTextTargetValueRead;
}
export interface ImmBoldAdapterConstructor { new(): ImmBoldAdapter; }
export interface ImmBoldAdapter {
  ImmAdapterT(other: ImmAdapter): ImmBoldAdapter;
  getValue(): ImmBoldValueRead;
}
export interface ImmUnderlineAdapterConstructor { new(): ImmUnderlineAdapter; }
export interface ImmUnderlineAdapter {
  ImmAdapterT(other: ImmAdapter): ImmUnderlineAdapter;
  getValue(): ImmUnderlineValueRead;
}
export interface ImmMonospaceAdapterConstructor { new(): ImmMonospaceAdapter; }
export interface ImmMonospaceAdapter {
  ImmAdapterT(other: ImmAdapter): ImmMonospaceAdapter;
  getValue(): ImmMonospaceValueRead;
}
export interface ImmMarkQuoteAdapterConstructor { new(): ImmMarkQuoteAdapter; }
export interface ImmMarkQuoteAdapter {
  ImmAdapterT(other: ImmAdapter): ImmMarkQuoteAdapter;
  getValue(): ImmMarkQuoteValueRead;
}
export interface ImmRadioTargetAdapterConstructor { new(): ImmRadioTargetAdapter; }
export interface ImmRadioTargetAdapter {
  ImmAdapterT(other: ImmAdapter): ImmRadioTargetAdapter;
  getValue(): ImmRadioTargetValueRead;
}
export interface ImmVerbatimAdapterConstructor { new(): ImmVerbatimAdapter; }
export interface ImmVerbatimAdapter {
  ImmAdapterT(other: ImmAdapter): ImmVerbatimAdapter;
  getValue(): ImmVerbatimValueRead;
}
export interface ImmItalicAdapterConstructor { new(): ImmItalicAdapter; }
export interface ImmItalicAdapter {
  ImmAdapterT(other: ImmAdapter): ImmItalicAdapter;
  getValue(): ImmItalicValueRead;
}
export interface ImmStrikeAdapterConstructor { new(): ImmStrikeAdapter; }
export interface ImmStrikeAdapter {
  ImmAdapterT(other: ImmAdapter): ImmStrikeAdapter;
  getValue(): ImmStrikeValueRead;
}
export interface ImmParAdapterConstructor { new(): ImmParAdapter; }
export interface ImmParAdapter {
  ImmAdapterT(other: ImmAdapter): ImmParAdapter;
  getValue(): ImmParValueRead;
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
  result: haxorg_wasm.Vec<BlockCodeEvalResult>
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
export interface ImmCmdCaptionConstructor { new(): ImmCmdCaption; }
export interface ImmCmdCaption {
  getKind(): OrgSemKind;
  __eq__(other: ImmCmdCaption): boolean;
  text: haxorg_wasm.ImmIdT<ImmParagraph>
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
  name: haxorg_wasm.ImmBox<string>
}
export interface ImmCmdCallConstructor { new(): ImmCmdCall; }
export interface ImmCmdCall {
  getKind(): OrgSemKind;
  __eq__(other: ImmCmdCall): boolean;
  name: haxorg_wasm.ImmBox<string>
  fileName: haxorg_wasm.ImmBox<haxorg_wasm.Optional<string>>
  insideHeaderAttrs: AttrGroup
  callAttrs: AttrGroup
  endHeaderAttrs: AttrGroup
  result: haxorg_wasm.ImmVec<haxorg_wasm.ImmIdT<ImmBlockCodeEvalResult>>
}
export interface ImmCmdAttrConstructor { new(): ImmCmdAttr; }
export interface ImmCmdAttr {
  getKind(): OrgSemKind;
  __eq__(other: ImmCmdAttr): boolean;
  target: haxorg_wasm.ImmBox<string>
}
export interface ImmCmdExportConstructor { new(): ImmCmdExport; }
export interface ImmCmdExport {
  getKind(): OrgSemKind;
  __eq__(other: ImmCmdExport): boolean;
  exporter: haxorg_wasm.ImmBox<string>
  content: haxorg_wasm.ImmBox<string>
}
export interface ImmAdapterAttachedAPIConstructor { new(): ImmAdapterAttachedAPI; }
export interface ImmAdapterAttachedAPI {  }
export interface ImmCmdCustomArgsAdapterConstructor { new(): ImmCmdCustomArgsAdapter; }
export interface ImmCmdCustomArgsAdapter {
  ImmAdapterT(other: ImmAdapter): ImmCmdCustomArgsAdapter;
  getValue(): ImmCmdCustomArgsValueRead;
}
export interface ImmCmdTblfmAdapterConstructor { new(): ImmCmdTblfmAdapter; }
export interface ImmCmdTblfmAdapter {
  ImmAdapterT(other: ImmAdapter): ImmCmdTblfmAdapter;
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
  ImmAdapterT(other: ImmAdapter): ImmCellAdapter;
  getValue(): ImmCellValueRead;
}
export interface ImmRowAdapterConstructor { new(): ImmRowAdapter; }
export interface ImmRowAdapter {
  ImmAdapterT(other: ImmAdapter): ImmRowAdapter;
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
  ImmAdapterT(other: ImmAdapter): ImmBlockCenterAdapter;
  getValue(): ImmBlockCenterValueRead;
}
export interface ImmBlockQuoteAdapterConstructor { new(): ImmBlockQuoteAdapter; }
export interface ImmBlockQuoteAdapter {
  ImmAdapterT(other: ImmAdapter): ImmBlockQuoteAdapter;
  getValue(): ImmBlockQuoteValueRead;
}
export interface ImmBlockVerseAdapterConstructor { new(): ImmBlockVerseAdapter; }
export interface ImmBlockVerseAdapter {
  ImmAdapterT(other: ImmAdapter): ImmBlockVerseAdapter;
  getValue(): ImmBlockVerseValueRead;
}
export interface ImmBlockExampleAdapterConstructor { new(): ImmBlockExampleAdapter; }
export interface ImmBlockExampleAdapter {
  ImmAdapterT(other: ImmAdapter): ImmBlockExampleAdapter;
  getValue(): ImmBlockExampleValueRead;
}
export interface ImmInlineExportAdapterConstructor { new(): ImmInlineExportAdapter; }
export interface ImmInlineExportAdapter {
  ImmAdapterT(other: ImmAdapter): ImmInlineExportAdapter;
  getValue(): ImmInlineExportValueRead;
}
export interface ImmCmdExportAdapterConstructor { new(): ImmCmdExportAdapter; }
export interface ImmCmdExportAdapter {
  ImmAdapterT(other: ImmAdapter): ImmCmdExportAdapter;
  getValue(): ImmCmdExportValueRead;
}
export interface ImmBlockExportAdapterConstructor { new(): ImmBlockExportAdapter; }
export interface ImmBlockExportAdapter {
  ImmAdapterT(other: ImmAdapter): ImmBlockExportAdapter;
  getValue(): ImmBlockExportValueRead;
}
export interface ImmBlockDynamicFallbackAdapterConstructor { new(): ImmBlockDynamicFallbackAdapter; }
export interface ImmBlockDynamicFallbackAdapter {
  ImmAdapterT(other: ImmAdapter): ImmBlockDynamicFallbackAdapter;
  getValue(): ImmBlockDynamicFallbackValueRead;
}
export interface ImmBlockAdmonitionAdapterConstructor { new(): ImmBlockAdmonitionAdapter; }
export interface ImmBlockAdmonitionAdapter {
  ImmAdapterT(other: ImmAdapter): ImmBlockAdmonitionAdapter;
  getValue(): ImmBlockAdmonitionValueRead;
}
export interface ImmBlockCodeEvalResultAdapterConstructor { new(): ImmBlockCodeEvalResultAdapter; }
export interface ImmBlockCodeEvalResultAdapter {
  ImmAdapterT(other: ImmAdapter): ImmBlockCodeEvalResultAdapter;
  getValue(): ImmBlockCodeEvalResultValueRead;
}
export interface ImmBlockCodeAdapterConstructor { new(): ImmBlockCodeAdapter; }
export interface ImmBlockCodeAdapter {
  ImmAdapterT(other: ImmAdapter): ImmBlockCodeAdapter;
  getValue(): ImmBlockCodeValueRead;
}
export interface ImmTableAdapterConstructor { new(): ImmTableAdapter; }
export interface ImmTableAdapter {
  ImmAdapterT(other: ImmAdapter): ImmTableAdapter;
  getValue(): ImmTableValueRead;
}
export interface ImmCmdCaptionAdapterConstructor { new(): ImmCmdCaptionAdapter; }
export interface ImmCmdCaptionAdapter {
  ImmAdapterT(other: ImmAdapter): ImmCmdCaptionAdapter;
  getValue(): ImmCmdCaptionValueRead;
}
export interface ImmCmdColumnsAdapterConstructor { new(): ImmCmdColumnsAdapter; }
export interface ImmCmdColumnsAdapter {
  ImmAdapterT(other: ImmAdapter): ImmCmdColumnsAdapter;
  getValue(): ImmCmdColumnsValueRead;
}
export interface ImmCmdNameAdapterConstructor { new(): ImmCmdNameAdapter; }
export interface ImmCmdNameAdapter {
  ImmAdapterT(other: ImmAdapter): ImmCmdNameAdapter;
  getValue(): ImmCmdNameValueRead;
}
export interface ImmCmdCallAdapterConstructor { new(): ImmCmdCallAdapter; }
export interface ImmCmdCallAdapter {
  ImmAdapterT(other: ImmAdapter): ImmCmdCallAdapter;
  getValue(): ImmCmdCallValueRead;
}
export interface ImmCmdAttrAdapterConstructor { new(): ImmCmdAttrAdapter; }
export interface ImmCmdAttrAdapter {
  ImmAdapterT(other: ImmAdapter): ImmCmdAttrAdapter;
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
  Table2DRowFirst,
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
  ErrorInfoToken,
  ErrorSkipGroup,
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
  ActiveDynamicTimeContent,
  InactiveDynamicTimeContent,
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
export enum AstTrackingGroupKind {
  RadioTarget,
  Single = 1,
  TrackedHashtag = 2,
}
export enum GraphMapLinkKind {
  Radio,
  Link = 1,
}
/* clang-format on */