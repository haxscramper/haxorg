/* clang-format off */
#include <wrappers/c/haxorg_c.h>
#include <wrappers/c/haxorg_c_utils.hpp>
void haxorg_destroy_UserTimeBreakdown(haxorg_UserTimeBreakdown* obj) { execute_destroy<hstd::UserTimeBreakdown>(obj); }

void haxorg_destroy_UserTime(haxorg_UserTime* obj) { execute_destroy<hstd::UserTime>(obj); }

void haxorg_destroy_ParseSourceFileId(haxorg_ParseSourceFileId* obj) { execute_destroy<org::parse::SourceFileId>(obj); }

void haxorg_destroy_ParseSourceLoc(haxorg_ParseSourceLoc* obj) { execute_destroy<org::parse::SourceLoc>(obj); }

void haxorg_destroy_OrgJson(haxorg_OrgJson* obj) { execute_destroy<org::sem::OrgJson>(obj); }

void haxorg_destroy_Org(haxorg_Org* obj) { execute_destroy<org::sem::Org>(obj); }

void haxorg_destroy_OperationsTracer(haxorg_OperationsTracer* obj) { execute_destroy<hstd::OperationsTracer>(obj); }

void haxorg_destroy_Cache(haxorg_Cache* obj) { execute_destroy<hstd::ext::Cache>(obj); }

void haxorg_destroy_ParseOrgParseFragment(haxorg_ParseOrgParseFragment* obj) { execute_destroy<org::parse::OrgParseFragment>(obj); }

void haxorg_destroy_OrgParseParameters(haxorg_OrgParseParameters* obj) { execute_destroy<org::parse::OrgParseParameters>(obj); }

void haxorg_destroy_OrgDirectoryParseParameters(haxorg_OrgDirectoryParseParameters* obj) { execute_destroy<org::parse::OrgDirectoryParseParameters>(obj); }

void haxorg_destroy_ParseContext(haxorg_ParseContext* obj) { execute_destroy<org::parse::ParseContext>(obj); }

void haxorg_destroy_ImmReflFieldId(haxorg_ImmReflFieldId* obj) { execute_destroy<org::imm::ImmReflFieldId>(obj); }

void haxorg_destroy_ImmId(haxorg_ImmId* obj) { execute_destroy<org::imm::ImmId>(obj); }

void haxorg_destroy_ImmOrg(haxorg_ImmOrg* obj) { execute_destroy<org::imm::ImmOrg>(obj); }

void haxorg_destroy_ImmPathStep(haxorg_ImmPathStep* obj) { execute_destroy<org::imm::ImmPathStep>(obj); }

void haxorg_destroy_ImmPath(haxorg_ImmPath* obj) { execute_destroy<org::imm::ImmPath>(obj); }

void haxorg_destroy_ImmUniqId(haxorg_ImmUniqId* obj) { execute_destroy<org::imm::ImmUniqId>(obj); }

void haxorg_destroy_ImmAstReplaceEpoch(haxorg_ImmAstReplaceEpoch* obj) { execute_destroy<org::imm::ImmAstReplaceEpoch>(obj); }

void haxorg_destroy_ImmAstContext(haxorg_ImmAstContext* obj) { execute_destroy<org::imm::ImmAstContext>(obj); }

void haxorg_destroy_ImmAstVersion(haxorg_ImmAstVersion* obj) { execute_destroy<org::imm::ImmAstVersion>(obj); }

void haxorg_destroy_ImmAdapterTreeReprConf(haxorg_ImmAdapterTreeReprConf* obj) { execute_destroy<org::imm::ImmAdapter::TreeReprConf>(obj); }

void haxorg_destroy_ImmAdapter(haxorg_ImmAdapter* obj) { execute_destroy<org::imm::ImmAdapter>(obj); }

void haxorg_destroy_ImmAdapterVirtualBase(haxorg_ImmAdapterVirtualBase* obj) { execute_destroy<org::imm::ImmAdapterVirtualBase>(obj); }

void haxorg_destroy_OrgYamlExportOpts(haxorg_OrgYamlExportOpts* obj) { execute_destroy<org::OrgYamlExportOpts>(obj); }

void haxorg_destroy_OrgTreeExportOpts(haxorg_OrgTreeExportOpts* obj) { execute_destroy<org::OrgTreeExportOpts>(obj); }

void haxorg_destroy_AstTrackingPath(haxorg_AstTrackingPath* obj) { execute_destroy<org::AstTrackingPath>(obj); }

void haxorg_destroy_AstTrackingAlternatives(haxorg_AstTrackingAlternatives* obj) { execute_destroy<org::AstTrackingAlternatives>(obj); }

void haxorg_destroy_AstTrackingGroupRadioTarget(haxorg_AstTrackingGroupRadioTarget* obj) { execute_destroy<org::AstTrackingGroup::RadioTarget>(obj); }

void haxorg_destroy_AstTrackingGroupSingle(haxorg_AstTrackingGroupSingle* obj) { execute_destroy<org::AstTrackingGroup::Single>(obj); }

void haxorg_destroy_AstTrackingGroupTrackedHashtag(haxorg_AstTrackingGroupTrackedHashtag* obj) { execute_destroy<org::AstTrackingGroup::TrackedHashtag>(obj); }

void haxorg_destroy_AstTrackingGroup(haxorg_AstTrackingGroup* obj) { execute_destroy<org::AstTrackingGroup>(obj); }

void haxorg_destroy_AstTrackingMap(haxorg_AstTrackingMap* obj) { execute_destroy<org::AstTrackingMap>(obj); }

void haxorg_destroy_SequenceSegment(haxorg_SequenceSegment* obj) { execute_destroy<hstd::SequenceSegment>(obj); }

void haxorg_destroy_SequenceSegmentGroup(haxorg_SequenceSegmentGroup* obj) { execute_destroy<hstd::SequenceSegmentGroup>(obj); }

void haxorg_destroy_SequenceAnnotationTag(haxorg_SequenceAnnotationTag* obj) { execute_destroy<hstd::SequenceAnnotationTag>(obj); }

void haxorg_destroy_SequenceAnnotation(haxorg_SequenceAnnotation* obj) { execute_destroy<hstd::SequenceAnnotation>(obj); }

void haxorg_destroy_GraphMapLinkLink(haxorg_GraphMapLinkLink* obj) { execute_destroy<org::graph::MapLink::Link>(obj); }

void haxorg_destroy_GraphMapLinkRadio(haxorg_GraphMapLinkRadio* obj) { execute_destroy<org::graph::MapLink::Radio>(obj); }

void haxorg_destroy_GraphMapLink(haxorg_GraphMapLink* obj) { execute_destroy<org::graph::MapLink>(obj); }

void haxorg_destroy_GraphMapNodeProp(haxorg_GraphMapNodeProp* obj) { execute_destroy<org::graph::MapNodeProp>(obj); }

void haxorg_destroy_GraphMapEdgeProp(haxorg_GraphMapEdgeProp* obj) { execute_destroy<org::graph::MapEdgeProp>(obj); }

void haxorg_destroy_GraphMapNode(haxorg_GraphMapNode* obj) { execute_destroy<org::graph::MapNode>(obj); }

void haxorg_destroy_GraphMapEdge(haxorg_GraphMapEdge* obj) { execute_destroy<org::graph::MapEdge>(obj); }

void haxorg_destroy_GraphMapGraph(haxorg_GraphMapGraph* obj) { execute_destroy<org::graph::MapGraph>(obj); }

void haxorg_destroy_GraphMapConfig(haxorg_GraphMapConfig* obj) { execute_destroy<org::graph::MapConfig>(obj); }

void haxorg_destroy_GraphMapGraphState(haxorg_GraphMapGraphState* obj) { execute_destroy<org::graph::MapGraphState>(obj); }

void haxorg_destroy_LispCodeCall(haxorg_LispCodeCall* obj) { execute_destroy<org::sem::LispCode::Call>(obj); }

void haxorg_destroy_LispCodeList(haxorg_LispCodeList* obj) { execute_destroy<org::sem::LispCode::List>(obj); }

void haxorg_destroy_LispCodeKeyValue(haxorg_LispCodeKeyValue* obj) { execute_destroy<org::sem::LispCode::KeyValue>(obj); }

void haxorg_destroy_LispCodeNumber(haxorg_LispCodeNumber* obj) { execute_destroy<org::sem::LispCode::Number>(obj); }

void haxorg_destroy_LispCodeText(haxorg_LispCodeText* obj) { execute_destroy<org::sem::LispCode::Text>(obj); }

void haxorg_destroy_LispCodeIdent(haxorg_LispCodeIdent* obj) { execute_destroy<org::sem::LispCode::Ident>(obj); }

void haxorg_destroy_LispCodeBoolean(haxorg_LispCodeBoolean* obj) { execute_destroy<org::sem::LispCode::Boolean>(obj); }

void haxorg_destroy_LispCodeReal(haxorg_LispCodeReal* obj) { execute_destroy<org::sem::LispCode::Real>(obj); }


void haxorg_destroy_LispCode(haxorg_LispCode* obj) { execute_destroy<org::sem::LispCode>(obj); }

void haxorg_destroy_TblfmExprAxisRefPositionIndex(haxorg_TblfmExprAxisRefPositionIndex* obj) { execute_destroy<org::sem::Tblfm::Expr::AxisRef::Position::Index>(obj); }

void haxorg_destroy_TblfmExprAxisRefPositionName(haxorg_TblfmExprAxisRefPositionName* obj) { execute_destroy<org::sem::Tblfm::Expr::AxisRef::Position::Name>(obj); }


void haxorg_destroy_TblfmExprAxisRefPosition(haxorg_TblfmExprAxisRefPosition* obj) { execute_destroy<org::sem::Tblfm::Expr::AxisRef::Position>(obj); }

void haxorg_destroy_TblfmExprAxisRef(haxorg_TblfmExprAxisRef* obj) { execute_destroy<org::sem::Tblfm::Expr::AxisRef>(obj); }

void haxorg_destroy_TblfmExprAxisName(haxorg_TblfmExprAxisName* obj) { execute_destroy<org::sem::Tblfm::Expr::AxisName>(obj); }

void haxorg_destroy_TblfmExprIntLiteral(haxorg_TblfmExprIntLiteral* obj) { execute_destroy<org::sem::Tblfm::Expr::IntLiteral>(obj); }

void haxorg_destroy_TblfmExprFloatLiteral(haxorg_TblfmExprFloatLiteral* obj) { execute_destroy<org::sem::Tblfm::Expr::FloatLiteral>(obj); }

void haxorg_destroy_TblfmExprRangeRef(haxorg_TblfmExprRangeRef* obj) { execute_destroy<org::sem::Tblfm::Expr::RangeRef>(obj); }

void haxorg_destroy_TblfmExprCall(haxorg_TblfmExprCall* obj) { execute_destroy<org::sem::Tblfm::Expr::Call>(obj); }

void haxorg_destroy_TblfmExprElisp(haxorg_TblfmExprElisp* obj) { execute_destroy<org::sem::Tblfm::Expr::Elisp>(obj); }


void haxorg_destroy_TblfmExpr(haxorg_TblfmExpr* obj) { execute_destroy<org::sem::Tblfm::Expr>(obj); }


void haxorg_destroy_TblfmAssign(haxorg_TblfmAssign* obj) { execute_destroy<org::sem::Tblfm::Assign>(obj); }

void haxorg_destroy_Tblfm(haxorg_Tblfm* obj) { execute_destroy<org::sem::Tblfm>(obj); }

void haxorg_destroy_AttrValueDimensionSpan(haxorg_AttrValueDimensionSpan* obj) { execute_destroy<org::sem::AttrValue::DimensionSpan>(obj); }

void haxorg_destroy_AttrValueTextValue(haxorg_AttrValueTextValue* obj) { execute_destroy<org::sem::AttrValue::TextValue>(obj); }

void haxorg_destroy_AttrValueFileReference(haxorg_AttrValueFileReference* obj) { execute_destroy<org::sem::AttrValue::FileReference>(obj); }

void haxorg_destroy_AttrValueLispValue(haxorg_AttrValueLispValue* obj) { execute_destroy<org::sem::AttrValue::LispValue>(obj); }


void haxorg_destroy_AttrValue(haxorg_AttrValue* obj) { execute_destroy<org::sem::AttrValue>(obj); }

void haxorg_destroy_HashTagFlat(haxorg_HashTagFlat* obj) { execute_destroy<org::sem::HashTagFlat>(obj); }


void haxorg_destroy_TodoKeyword(haxorg_TodoKeyword* obj) { execute_destroy<org::sem::TodoKeyword>(obj); }

void haxorg_destroy_HashTagText(haxorg_HashTagText* obj) { execute_destroy<org::sem::HashTagText>(obj); }

void haxorg_destroy_SubtreePath(haxorg_SubtreePath* obj) { execute_destroy<org::sem::SubtreePath>(obj); }

void haxorg_destroy_LinkTargetRaw(haxorg_LinkTargetRaw* obj) { execute_destroy<org::sem::LinkTarget::Raw>(obj); }

void haxorg_destroy_LinkTargetId(haxorg_LinkTargetId* obj) { execute_destroy<org::sem::LinkTarget::Id>(obj); }

void haxorg_destroy_LinkTargetCustomId(haxorg_LinkTargetCustomId* obj) { execute_destroy<org::sem::LinkTarget::CustomId>(obj); }

void haxorg_destroy_LinkTargetSubtreeTitle(haxorg_LinkTargetSubtreeTitle* obj) { execute_destroy<org::sem::LinkTarget::SubtreeTitle>(obj); }

void haxorg_destroy_LinkTargetPerson(haxorg_LinkTargetPerson* obj) { execute_destroy<org::sem::LinkTarget::Person>(obj); }

void haxorg_destroy_LinkTargetUserProtocol(haxorg_LinkTargetUserProtocol* obj) { execute_destroy<org::sem::LinkTarget::UserProtocol>(obj); }

void haxorg_destroy_LinkTargetInternal(haxorg_LinkTargetInternal* obj) { execute_destroy<org::sem::LinkTarget::Internal>(obj); }

void haxorg_destroy_LinkTargetFootnote(haxorg_LinkTargetFootnote* obj) { execute_destroy<org::sem::LinkTarget::Footnote>(obj); }

void haxorg_destroy_LinkTargetFile(haxorg_LinkTargetFile* obj) { execute_destroy<org::sem::LinkTarget::File>(obj); }

void haxorg_destroy_LinkTargetAttachment(haxorg_LinkTargetAttachment* obj) { execute_destroy<org::sem::LinkTarget::Attachment>(obj); }


void haxorg_destroy_LinkTarget(haxorg_LinkTarget* obj) { execute_destroy<org::sem::LinkTarget>(obj); }


void haxorg_destroy_SubtreeLogHeadPriority(haxorg_SubtreeLogHeadPriority* obj) { execute_destroy<org::sem::SubtreeLogHead::Priority>(obj); }

void haxorg_destroy_SubtreeLogHeadNote(haxorg_SubtreeLogHeadNote* obj) { execute_destroy<org::sem::SubtreeLogHead::Note>(obj); }

void haxorg_destroy_SubtreeLogHeadRefile(haxorg_SubtreeLogHeadRefile* obj) { execute_destroy<org::sem::SubtreeLogHead::Refile>(obj); }

void haxorg_destroy_SubtreeLogHeadClock(haxorg_SubtreeLogHeadClock* obj) { execute_destroy<org::sem::SubtreeLogHead::Clock>(obj); }

void haxorg_destroy_SubtreeLogHeadState(haxorg_SubtreeLogHeadState* obj) { execute_destroy<org::sem::SubtreeLogHead::State>(obj); }

void haxorg_destroy_SubtreeLogHeadDeadline(haxorg_SubtreeLogHeadDeadline* obj) { execute_destroy<org::sem::SubtreeLogHead::Deadline>(obj); }

void haxorg_destroy_SubtreeLogHeadSchedule(haxorg_SubtreeLogHeadSchedule* obj) { execute_destroy<org::sem::SubtreeLogHead::Schedule>(obj); }

void haxorg_destroy_SubtreeLogHeadTag(haxorg_SubtreeLogHeadTag* obj) { execute_destroy<org::sem::SubtreeLogHead::Tag>(obj); }

void haxorg_destroy_SubtreeLogHeadUnknown(haxorg_SubtreeLogHeadUnknown* obj) { execute_destroy<org::sem::SubtreeLogHead::Unknown>(obj); }


void haxorg_destroy_SubtreeLogHead(haxorg_SubtreeLogHead* obj) { execute_destroy<org::sem::SubtreeLogHead>(obj); }

void haxorg_destroy_SubtreeCompletion(haxorg_SubtreeCompletion* obj) { execute_destroy<org::sem::SubtreeCompletion>(obj); }

void haxorg_destroy_AttrList(haxorg_AttrList* obj) { execute_destroy<org::sem::AttrList>(obj); }

void haxorg_destroy_AttrGroup(haxorg_AttrGroup* obj) { execute_destroy<org::sem::AttrGroup>(obj); }

void haxorg_destroy_OrgCodeEvalInputVar(haxorg_OrgCodeEvalInputVar* obj) { execute_destroy<org::sem::OrgCodeEvalInput::Var>(obj); }




void haxorg_destroy_OrgCodeEvalInput(haxorg_OrgCodeEvalInput* obj) { execute_destroy<org::sem::OrgCodeEvalInput>(obj); }

void haxorg_destroy_OrgCodeEvalOutput(haxorg_OrgCodeEvalOutput* obj) { execute_destroy<org::sem::OrgCodeEvalOutput>(obj); }


void haxorg_destroy_ColumnViewSummaryCheckboxAggregate(haxorg_ColumnViewSummaryCheckboxAggregate* obj) { execute_destroy<org::sem::ColumnView::Summary::CheckboxAggregate>(obj); }


void haxorg_destroy_ColumnViewSummaryMathAggregate(haxorg_ColumnViewSummaryMathAggregate* obj) { execute_destroy<org::sem::ColumnView::Summary::MathAggregate>(obj); }


void haxorg_destroy_ColumnViewSummary(haxorg_ColumnViewSummary* obj) { execute_destroy<org::sem::ColumnView::Summary>(obj); }

void haxorg_destroy_ColumnViewColumn(haxorg_ColumnViewColumn* obj) { execute_destroy<org::sem::ColumnView::Column>(obj); }

void haxorg_destroy_ColumnView(haxorg_ColumnView* obj) { execute_destroy<org::sem::ColumnView>(obj); }

void haxorg_destroy_BlockCodeLinePartRaw(haxorg_BlockCodeLinePartRaw* obj) { execute_destroy<org::sem::BlockCodeLine::Part::Raw>(obj); }

void haxorg_destroy_BlockCodeLinePartCallout(haxorg_BlockCodeLinePartCallout* obj) { execute_destroy<org::sem::BlockCodeLine::Part::Callout>(obj); }

void haxorg_destroy_BlockCodeLinePartTangle(haxorg_BlockCodeLinePartTangle* obj) { execute_destroy<org::sem::BlockCodeLine::Part::Tangle>(obj); }


void haxorg_destroy_BlockCodeLinePart(haxorg_BlockCodeLinePart* obj) { execute_destroy<org::sem::BlockCodeLine::Part>(obj); }

void haxorg_destroy_BlockCodeLine(haxorg_BlockCodeLine* obj) { execute_destroy<org::sem::BlockCodeLine>(obj); }

void haxorg_destroy_DocumentExportConfigTaskExport(haxorg_DocumentExportConfigTaskExport* obj) { execute_destroy<org::sem::DocumentExportConfig::TaskExport>(obj); }





void haxorg_destroy_DocumentExportConfigDoExport(haxorg_DocumentExportConfigDoExport* obj) { execute_destroy<org::sem::DocumentExportConfig::DoExport>(obj); }

void haxorg_destroy_DocumentExportConfigExportFixed(haxorg_DocumentExportConfigExportFixed* obj) { execute_destroy<org::sem::DocumentExportConfig::ExportFixed>(obj); }


void haxorg_destroy_DocumentExportConfig(haxorg_DocumentExportConfig* obj) { execute_destroy<org::sem::DocumentExportConfig>(obj); }


void haxorg_destroy_SubtreePeriod(haxorg_SubtreePeriod* obj) { execute_destroy<org::sem::SubtreePeriod>(obj); }

void haxorg_destroy_NamedPropertyNonblocking(haxorg_NamedPropertyNonblocking* obj) { execute_destroy<org::sem::NamedProperty::Nonblocking>(obj); }

void haxorg_destroy_NamedPropertyArchiveTime(haxorg_NamedPropertyArchiveTime* obj) { execute_destroy<org::sem::NamedProperty::ArchiveTime>(obj); }

void haxorg_destroy_NamedPropertyArchiveFile(haxorg_NamedPropertyArchiveFile* obj) { execute_destroy<org::sem::NamedProperty::ArchiveFile>(obj); }

void haxorg_destroy_NamedPropertyArchiveOlpath(haxorg_NamedPropertyArchiveOlpath* obj) { execute_destroy<org::sem::NamedProperty::ArchiveOlpath>(obj); }

void haxorg_destroy_NamedPropertyArchiveTarget(haxorg_NamedPropertyArchiveTarget* obj) { execute_destroy<org::sem::NamedProperty::ArchiveTarget>(obj); }

void haxorg_destroy_NamedPropertyArchiveCategory(haxorg_NamedPropertyArchiveCategory* obj) { execute_destroy<org::sem::NamedProperty::ArchiveCategory>(obj); }

void haxorg_destroy_NamedPropertyArchiveTodo(haxorg_NamedPropertyArchiveTodo* obj) { execute_destroy<org::sem::NamedProperty::ArchiveTodo>(obj); }

void haxorg_destroy_NamedPropertyTrigger(haxorg_NamedPropertyTrigger* obj) { execute_destroy<org::sem::NamedProperty::Trigger>(obj); }

void haxorg_destroy_NamedPropertyExportLatexClass(haxorg_NamedPropertyExportLatexClass* obj) { execute_destroy<org::sem::NamedProperty::ExportLatexClass>(obj); }

void haxorg_destroy_NamedPropertyCookieData(haxorg_NamedPropertyCookieData* obj) { execute_destroy<org::sem::NamedProperty::CookieData>(obj); }

void haxorg_destroy_NamedPropertyExportLatexClassOptions(haxorg_NamedPropertyExportLatexClassOptions* obj) { execute_destroy<org::sem::NamedProperty::ExportLatexClassOptions>(obj); }

void haxorg_destroy_NamedPropertyExportLatexHeader(haxorg_NamedPropertyExportLatexHeader* obj) { execute_destroy<org::sem::NamedProperty::ExportLatexHeader>(obj); }

void haxorg_destroy_NamedPropertyExportLatexCompiler(haxorg_NamedPropertyExportLatexCompiler* obj) { execute_destroy<org::sem::NamedProperty::ExportLatexCompiler>(obj); }

void haxorg_destroy_NamedPropertyOrdered(haxorg_NamedPropertyOrdered* obj) { execute_destroy<org::sem::NamedProperty::Ordered>(obj); }

void haxorg_destroy_NamedPropertyEffort(haxorg_NamedPropertyEffort* obj) { execute_destroy<org::sem::NamedProperty::Effort>(obj); }


void haxorg_destroy_NamedPropertyVisibility(haxorg_NamedPropertyVisibility* obj) { execute_destroy<org::sem::NamedProperty::Visibility>(obj); }

void haxorg_destroy_NamedPropertyExportOptions(haxorg_NamedPropertyExportOptions* obj) { execute_destroy<org::sem::NamedProperty::ExportOptions>(obj); }

void haxorg_destroy_NamedPropertyBlocker(haxorg_NamedPropertyBlocker* obj) { execute_destroy<org::sem::NamedProperty::Blocker>(obj); }

void haxorg_destroy_NamedPropertyUnnumbered(haxorg_NamedPropertyUnnumbered* obj) { execute_destroy<org::sem::NamedProperty::Unnumbered>(obj); }

void haxorg_destroy_NamedPropertyCreated(haxorg_NamedPropertyCreated* obj) { execute_destroy<org::sem::NamedProperty::Created>(obj); }

void haxorg_destroy_NamedPropertyRadioId(haxorg_NamedPropertyRadioId* obj) { execute_destroy<org::sem::NamedProperty::RadioId>(obj); }

void haxorg_destroy_NamedPropertyHashtagDef(haxorg_NamedPropertyHashtagDef* obj) { execute_destroy<org::sem::NamedProperty::HashtagDef>(obj); }

void haxorg_destroy_NamedPropertyCustomArgs(haxorg_NamedPropertyCustomArgs* obj) { execute_destroy<org::sem::NamedProperty::CustomArgs>(obj); }

void haxorg_destroy_NamedPropertyCustomRaw(haxorg_NamedPropertyCustomRaw* obj) { execute_destroy<org::sem::NamedProperty::CustomRaw>(obj); }

void haxorg_destroy_NamedPropertyCustomId(haxorg_NamedPropertyCustomId* obj) { execute_destroy<org::sem::NamedProperty::CustomId>(obj); }

void haxorg_destroy_NamedPropertyCustomSubtreeJson(haxorg_NamedPropertyCustomSubtreeJson* obj) { execute_destroy<org::sem::NamedProperty::CustomSubtreeJson>(obj); }

void haxorg_destroy_NamedPropertyCustomSubtreeFlags(haxorg_NamedPropertyCustomSubtreeFlags* obj) { execute_destroy<org::sem::NamedProperty::CustomSubtreeFlags>(obj); }


void haxorg_destroy_NamedProperty(haxorg_NamedProperty* obj) { execute_destroy<org::sem::NamedProperty>(obj); }

void haxorg_destroy_OrgDiagnosticsParseTokenError(haxorg_OrgDiagnosticsParseTokenError* obj) { execute_destroy<org::sem::OrgDiagnostics::ParseTokenError>(obj); }

void haxorg_destroy_OrgDiagnosticsParseError(haxorg_OrgDiagnosticsParseError* obj) { execute_destroy<org::sem::OrgDiagnostics::ParseError>(obj); }

void haxorg_destroy_OrgDiagnosticsIncludeError(haxorg_OrgDiagnosticsIncludeError* obj) { execute_destroy<org::sem::OrgDiagnostics::IncludeError>(obj); }

void haxorg_destroy_OrgDiagnosticsConvertError(haxorg_OrgDiagnosticsConvertError* obj) { execute_destroy<org::sem::OrgDiagnostics::ConvertError>(obj); }

void haxorg_destroy_OrgDiagnosticsInternalError(haxorg_OrgDiagnosticsInternalError* obj) { execute_destroy<org::sem::OrgDiagnostics::InternalError>(obj); }


void haxorg_destroy_OrgDiagnostics(haxorg_OrgDiagnostics* obj) { execute_destroy<org::sem::OrgDiagnostics>(obj); }

void haxorg_destroy_NoNode(haxorg_NoNode* obj) { execute_destroy<org::sem::NoNode>(obj); }

void haxorg_destroy_ErrorItem(haxorg_ErrorItem* obj) { execute_destroy<org::sem::ErrorItem>(obj); }

void haxorg_destroy_ErrorGroup(haxorg_ErrorGroup* obj) { execute_destroy<org::sem::ErrorGroup>(obj); }

void haxorg_destroy_Stmt(haxorg_Stmt* obj) { execute_destroy<org::sem::Stmt>(obj); }

void haxorg_destroy_Inline(haxorg_Inline* obj) { execute_destroy<org::sem::Inline>(obj); }

void haxorg_destroy_StmtList(haxorg_StmtList* obj) { execute_destroy<org::sem::StmtList>(obj); }

void haxorg_destroy_Empty(haxorg_Empty* obj) { execute_destroy<org::sem::Empty>(obj); }

void haxorg_destroy_Leaf(haxorg_Leaf* obj) { execute_destroy<org::sem::Leaf>(obj); }



void haxorg_destroy_TimeRepeat(haxorg_TimeRepeat* obj) { execute_destroy<org::sem::Time::Repeat>(obj); }

void haxorg_destroy_TimeStatic(haxorg_TimeStatic* obj) { execute_destroy<org::sem::Time::Static>(obj); }

void haxorg_destroy_TimeDynamic(haxorg_TimeDynamic* obj) { execute_destroy<org::sem::Time::Dynamic>(obj); }


void haxorg_destroy_Time(haxorg_Time* obj) { execute_destroy<org::sem::Time>(obj); }

void haxorg_destroy_TimeRange(haxorg_TimeRange* obj) { execute_destroy<org::sem::TimeRange>(obj); }

void haxorg_destroy_Macro(haxorg_Macro* obj) { execute_destroy<org::sem::Macro>(obj); }

void haxorg_destroy_SymbolParam(haxorg_SymbolParam* obj) { execute_destroy<org::sem::Symbol::Param>(obj); }

void haxorg_destroy_Symbol(haxorg_Symbol* obj) { execute_destroy<org::sem::Symbol>(obj); }

void haxorg_destroy_ErrorSkipGroup(haxorg_ErrorSkipGroup* obj) { execute_destroy<org::sem::ErrorSkipGroup>(obj); }

void haxorg_destroy_Markup(haxorg_Markup* obj) { execute_destroy<org::sem::Markup>(obj); }

void haxorg_destroy_RadioTarget(haxorg_RadioTarget* obj) { execute_destroy<org::sem::RadioTarget>(obj); }

void haxorg_destroy_Latex(haxorg_Latex* obj) { execute_destroy<org::sem::Latex>(obj); }

void haxorg_destroy_SubtreeLog(haxorg_SubtreeLog* obj) { execute_destroy<org::sem::SubtreeLog>(obj); }

void haxorg_destroy_Subtree(haxorg_Subtree* obj) { execute_destroy<org::sem::Subtree>(obj); }

void haxorg_destroy_ColonExample(haxorg_ColonExample* obj) { execute_destroy<org::sem::ColonExample>(obj); }

void haxorg_destroy_Call(haxorg_Call* obj) { execute_destroy<org::sem::Call>(obj); }

void haxorg_destroy_ListItem(haxorg_ListItem* obj) { execute_destroy<org::sem::ListItem>(obj); }

void haxorg_destroy_DocumentOptions(haxorg_DocumentOptions* obj) { execute_destroy<org::sem::DocumentOptions>(obj); }

void haxorg_destroy_DocumentFragment(haxorg_DocumentFragment* obj) { execute_destroy<org::sem::DocumentFragment>(obj); }


void haxorg_destroy_CriticMarkup(haxorg_CriticMarkup* obj) { execute_destroy<org::sem::CriticMarkup>(obj); }

void haxorg_destroy_Document(haxorg_Document* obj) { execute_destroy<org::sem::Document>(obj); }

void haxorg_destroy_FileTarget(haxorg_FileTarget* obj) { execute_destroy<org::sem::FileTarget>(obj); }

void haxorg_destroy_TextSeparator(haxorg_TextSeparator* obj) { execute_destroy<org::sem::TextSeparator>(obj); }

void haxorg_destroy_DocumentGroup(haxorg_DocumentGroup* obj) { execute_destroy<org::sem::DocumentGroup>(obj); }

void haxorg_destroy_FileDocument(haxorg_FileDocument* obj) { execute_destroy<org::sem::File::Document>(obj); }

void haxorg_destroy_FileAttachment(haxorg_FileAttachment* obj) { execute_destroy<org::sem::File::Attachment>(obj); }

void haxorg_destroy_FileSource(haxorg_FileSource* obj) { execute_destroy<org::sem::File::Source>(obj); }


void haxorg_destroy_File(haxorg_File* obj) { execute_destroy<org::sem::File>(obj); }

void haxorg_destroy_Directory(haxorg_Directory* obj) { execute_destroy<org::sem::Directory>(obj); }

void haxorg_destroy_Symlink(haxorg_Symlink* obj) { execute_destroy<org::sem::Symlink>(obj); }

void haxorg_destroy_CmdIncludeIncludeBase(haxorg_CmdIncludeIncludeBase* obj) { execute_destroy<org::sem::CmdInclude::IncludeBase>(obj); }

void haxorg_destroy_CmdIncludeExample(haxorg_CmdIncludeExample* obj) { execute_destroy<org::sem::CmdInclude::Example>(obj); }

void haxorg_destroy_CmdIncludeExport(haxorg_CmdIncludeExport* obj) { execute_destroy<org::sem::CmdInclude::Export>(obj); }

void haxorg_destroy_CmdIncludeCustom(haxorg_CmdIncludeCustom* obj) { execute_destroy<org::sem::CmdInclude::Custom>(obj); }

void haxorg_destroy_CmdIncludeSrc(haxorg_CmdIncludeSrc* obj) { execute_destroy<org::sem::CmdInclude::Src>(obj); }

void haxorg_destroy_CmdIncludeOrgDocument(haxorg_CmdIncludeOrgDocument* obj) { execute_destroy<org::sem::CmdInclude::OrgDocument>(obj); }


void haxorg_destroy_CmdInclude(haxorg_CmdInclude* obj) { execute_destroy<org::sem::CmdInclude>(obj); }

void haxorg_destroy_ImmNoNode(haxorg_ImmNoNode* obj) { execute_destroy<org::imm::ImmNoNode>(obj); }

void haxorg_destroy_ImmErrorItem(haxorg_ImmErrorItem* obj) { execute_destroy<org::imm::ImmErrorItem>(obj); }

void haxorg_destroy_ImmErrorGroup(haxorg_ImmErrorGroup* obj) { execute_destroy<org::imm::ImmErrorGroup>(obj); }

void haxorg_destroy_ImmStmt(haxorg_ImmStmt* obj) { execute_destroy<org::imm::ImmStmt>(obj); }

void haxorg_destroy_ImmInline(haxorg_ImmInline* obj) { execute_destroy<org::imm::ImmInline>(obj); }

void haxorg_destroy_ImmStmtList(haxorg_ImmStmtList* obj) { execute_destroy<org::imm::ImmStmtList>(obj); }

void haxorg_destroy_ImmEmpty(haxorg_ImmEmpty* obj) { execute_destroy<org::imm::ImmEmpty>(obj); }

void haxorg_destroy_ImmLeaf(haxorg_ImmLeaf* obj) { execute_destroy<org::imm::ImmLeaf>(obj); }

void haxorg_destroy_ImmTimeRepeat(haxorg_ImmTimeRepeat* obj) { execute_destroy<org::imm::ImmTime::Repeat>(obj); }

void haxorg_destroy_ImmTimeStatic(haxorg_ImmTimeStatic* obj) { execute_destroy<org::imm::ImmTime::Static>(obj); }

void haxorg_destroy_ImmTimeDynamic(haxorg_ImmTimeDynamic* obj) { execute_destroy<org::imm::ImmTime::Dynamic>(obj); }


void haxorg_destroy_ImmTime(haxorg_ImmTime* obj) { execute_destroy<org::imm::ImmTime>(obj); }

void haxorg_destroy_ImmTimeRange(haxorg_ImmTimeRange* obj) { execute_destroy<org::imm::ImmTimeRange>(obj); }

void haxorg_destroy_ImmMacro(haxorg_ImmMacro* obj) { execute_destroy<org::imm::ImmMacro>(obj); }

void haxorg_destroy_ImmSymbolParam(haxorg_ImmSymbolParam* obj) { execute_destroy<org::imm::ImmSymbol::Param>(obj); }

void haxorg_destroy_ImmSymbol(haxorg_ImmSymbol* obj) { execute_destroy<org::imm::ImmSymbol>(obj); }

void haxorg_destroy_ImmErrorSkipGroup(haxorg_ImmErrorSkipGroup* obj) { execute_destroy<org::imm::ImmErrorSkipGroup>(obj); }

void haxorg_destroy_ImmMarkup(haxorg_ImmMarkup* obj) { execute_destroy<org::imm::ImmMarkup>(obj); }

void haxorg_destroy_ImmRadioTarget(haxorg_ImmRadioTarget* obj) { execute_destroy<org::imm::ImmRadioTarget>(obj); }

void haxorg_destroy_ImmLatex(haxorg_ImmLatex* obj) { execute_destroy<org::imm::ImmLatex>(obj); }

void haxorg_destroy_ImmSubtreeLog(haxorg_ImmSubtreeLog* obj) { execute_destroy<org::imm::ImmSubtreeLog>(obj); }

void haxorg_destroy_ImmSubtree(haxorg_ImmSubtree* obj) { execute_destroy<org::imm::ImmSubtree>(obj); }

void haxorg_destroy_ImmColonExample(haxorg_ImmColonExample* obj) { execute_destroy<org::imm::ImmColonExample>(obj); }

void haxorg_destroy_ImmCall(haxorg_ImmCall* obj) { execute_destroy<org::imm::ImmCall>(obj); }

void haxorg_destroy_ImmListItem(haxorg_ImmListItem* obj) { execute_destroy<org::imm::ImmListItem>(obj); }

void haxorg_destroy_ImmDocumentOptions(haxorg_ImmDocumentOptions* obj) { execute_destroy<org::imm::ImmDocumentOptions>(obj); }

void haxorg_destroy_ImmDocumentFragment(haxorg_ImmDocumentFragment* obj) { execute_destroy<org::imm::ImmDocumentFragment>(obj); }

void haxorg_destroy_ImmCriticMarkup(haxorg_ImmCriticMarkup* obj) { execute_destroy<org::imm::ImmCriticMarkup>(obj); }

void haxorg_destroy_ImmDocument(haxorg_ImmDocument* obj) { execute_destroy<org::imm::ImmDocument>(obj); }

void haxorg_destroy_ImmFileTarget(haxorg_ImmFileTarget* obj) { execute_destroy<org::imm::ImmFileTarget>(obj); }

void haxorg_destroy_ImmTextSeparator(haxorg_ImmTextSeparator* obj) { execute_destroy<org::imm::ImmTextSeparator>(obj); }

void haxorg_destroy_ImmDocumentGroup(haxorg_ImmDocumentGroup* obj) { execute_destroy<org::imm::ImmDocumentGroup>(obj); }

void haxorg_destroy_ImmFileDocument(haxorg_ImmFileDocument* obj) { execute_destroy<org::imm::ImmFile::Document>(obj); }

void haxorg_destroy_ImmFileAttachment(haxorg_ImmFileAttachment* obj) { execute_destroy<org::imm::ImmFile::Attachment>(obj); }

void haxorg_destroy_ImmFileSource(haxorg_ImmFileSource* obj) { execute_destroy<org::imm::ImmFile::Source>(obj); }


void haxorg_destroy_ImmFile(haxorg_ImmFile* obj) { execute_destroy<org::imm::ImmFile>(obj); }

void haxorg_destroy_ImmDirectory(haxorg_ImmDirectory* obj) { execute_destroy<org::imm::ImmDirectory>(obj); }

void haxorg_destroy_ImmSymlink(haxorg_ImmSymlink* obj) { execute_destroy<org::imm::ImmSymlink>(obj); }

void haxorg_destroy_ImmCmdIncludeIncludeBase(haxorg_ImmCmdIncludeIncludeBase* obj) { execute_destroy<org::imm::ImmCmdInclude::IncludeBase>(obj); }

void haxorg_destroy_ImmCmdIncludeExample(haxorg_ImmCmdIncludeExample* obj) { execute_destroy<org::imm::ImmCmdInclude::Example>(obj); }

void haxorg_destroy_ImmCmdIncludeExport(haxorg_ImmCmdIncludeExport* obj) { execute_destroy<org::imm::ImmCmdInclude::Export>(obj); }

void haxorg_destroy_ImmCmdIncludeCustom(haxorg_ImmCmdIncludeCustom* obj) { execute_destroy<org::imm::ImmCmdInclude::Custom>(obj); }

void haxorg_destroy_ImmCmdIncludeSrc(haxorg_ImmCmdIncludeSrc* obj) { execute_destroy<org::imm::ImmCmdInclude::Src>(obj); }

void haxorg_destroy_ImmCmdIncludeOrgDocument(haxorg_ImmCmdIncludeOrgDocument* obj) { execute_destroy<org::imm::ImmCmdInclude::OrgDocument>(obj); }


void haxorg_destroy_ImmCmdInclude(haxorg_ImmCmdInclude* obj) { execute_destroy<org::imm::ImmCmdInclude>(obj); }

void haxorg_destroy_ImmAdapterOrgAPI(haxorg_ImmAdapterOrgAPI* obj) { execute_destroy<org::imm::ImmAdapterOrgAPI>(obj); }

void haxorg_destroy_Cmd(haxorg_Cmd* obj) { execute_destroy<org::sem::Cmd>(obj); }

void haxorg_destroy_CmdCustomRaw(haxorg_CmdCustomRaw* obj) { execute_destroy<org::sem::CmdCustomRaw>(obj); }

void haxorg_destroy_CmdCustomText(haxorg_CmdCustomText* obj) { execute_destroy<org::sem::CmdCustomText>(obj); }

void haxorg_destroy_Link(haxorg_Link* obj) { execute_destroy<org::sem::Link>(obj); }

void haxorg_destroy_BlockComment(haxorg_BlockComment* obj) { execute_destroy<org::sem::BlockComment>(obj); }

void haxorg_destroy_Paragraph(haxorg_Paragraph* obj) { execute_destroy<org::sem::Paragraph>(obj); }

void haxorg_destroy_List(haxorg_List* obj) { execute_destroy<org::sem::List>(obj); }

void haxorg_destroy_HashTag(haxorg_HashTag* obj) { execute_destroy<org::sem::HashTag>(obj); }

void haxorg_destroy_InlineFootnote(haxorg_InlineFootnote* obj) { execute_destroy<org::sem::InlineFootnote>(obj); }

void haxorg_destroy_InlineExport(haxorg_InlineExport* obj) { execute_destroy<org::sem::InlineExport>(obj); }

void haxorg_destroy_Escaped(haxorg_Escaped* obj) { execute_destroy<org::sem::Escaped>(obj); }

void haxorg_destroy_Newline(haxorg_Newline* obj) { execute_destroy<org::sem::Newline>(obj); }

void haxorg_destroy_Space(haxorg_Space* obj) { execute_destroy<org::sem::Space>(obj); }

void haxorg_destroy_Word(haxorg_Word* obj) { execute_destroy<org::sem::Word>(obj); }

void haxorg_destroy_AtMention(haxorg_AtMention* obj) { execute_destroy<org::sem::AtMention>(obj); }

void haxorg_destroy_RawText(haxorg_RawText* obj) { execute_destroy<org::sem::RawText>(obj); }

void haxorg_destroy_Punctuation(haxorg_Punctuation* obj) { execute_destroy<org::sem::Punctuation>(obj); }

void haxorg_destroy_Placeholder(haxorg_Placeholder* obj) { execute_destroy<org::sem::Placeholder>(obj); }

void haxorg_destroy_BigIdent(haxorg_BigIdent* obj) { execute_destroy<org::sem::BigIdent>(obj); }

void haxorg_destroy_TextTarget(haxorg_TextTarget* obj) { execute_destroy<org::sem::TextTarget>(obj); }

void haxorg_destroy_ErrorSkipToken(haxorg_ErrorSkipToken* obj) { execute_destroy<org::sem::ErrorSkipToken>(obj); }

void haxorg_destroy_Bold(haxorg_Bold* obj) { execute_destroy<org::sem::Bold>(obj); }

void haxorg_destroy_Underline(haxorg_Underline* obj) { execute_destroy<org::sem::Underline>(obj); }

void haxorg_destroy_Monospace(haxorg_Monospace* obj) { execute_destroy<org::sem::Monospace>(obj); }

void haxorg_destroy_MarkQuote(haxorg_MarkQuote* obj) { execute_destroy<org::sem::MarkQuote>(obj); }

void haxorg_destroy_Verbatim(haxorg_Verbatim* obj) { execute_destroy<org::sem::Verbatim>(obj); }

void haxorg_destroy_Italic(haxorg_Italic* obj) { execute_destroy<org::sem::Italic>(obj); }

void haxorg_destroy_Strike(haxorg_Strike* obj) { execute_destroy<org::sem::Strike>(obj); }

void haxorg_destroy_Par(haxorg_Par* obj) { execute_destroy<org::sem::Par>(obj); }

void haxorg_destroy_ImmCmd(haxorg_ImmCmd* obj) { execute_destroy<org::imm::ImmCmd>(obj); }

void haxorg_destroy_ImmCmdCustomRaw(haxorg_ImmCmdCustomRaw* obj) { execute_destroy<org::imm::ImmCmdCustomRaw>(obj); }

void haxorg_destroy_ImmCmdCustomText(haxorg_ImmCmdCustomText* obj) { execute_destroy<org::imm::ImmCmdCustomText>(obj); }

void haxorg_destroy_ImmLink(haxorg_ImmLink* obj) { execute_destroy<org::imm::ImmLink>(obj); }

void haxorg_destroy_ImmBlockComment(haxorg_ImmBlockComment* obj) { execute_destroy<org::imm::ImmBlockComment>(obj); }

void haxorg_destroy_ImmParagraph(haxorg_ImmParagraph* obj) { execute_destroy<org::imm::ImmParagraph>(obj); }

void haxorg_destroy_ImmList(haxorg_ImmList* obj) { execute_destroy<org::imm::ImmList>(obj); }

void haxorg_destroy_ImmHashTag(haxorg_ImmHashTag* obj) { execute_destroy<org::imm::ImmHashTag>(obj); }

void haxorg_destroy_ImmInlineFootnote(haxorg_ImmInlineFootnote* obj) { execute_destroy<org::imm::ImmInlineFootnote>(obj); }

void haxorg_destroy_ImmInlineExport(haxorg_ImmInlineExport* obj) { execute_destroy<org::imm::ImmInlineExport>(obj); }

void haxorg_destroy_ImmEscaped(haxorg_ImmEscaped* obj) { execute_destroy<org::imm::ImmEscaped>(obj); }

void haxorg_destroy_ImmNewline(haxorg_ImmNewline* obj) { execute_destroy<org::imm::ImmNewline>(obj); }

void haxorg_destroy_ImmSpace(haxorg_ImmSpace* obj) { execute_destroy<org::imm::ImmSpace>(obj); }

void haxorg_destroy_ImmWord(haxorg_ImmWord* obj) { execute_destroy<org::imm::ImmWord>(obj); }

void haxorg_destroy_ImmAtMention(haxorg_ImmAtMention* obj) { execute_destroy<org::imm::ImmAtMention>(obj); }

void haxorg_destroy_ImmRawText(haxorg_ImmRawText* obj) { execute_destroy<org::imm::ImmRawText>(obj); }

void haxorg_destroy_ImmPunctuation(haxorg_ImmPunctuation* obj) { execute_destroy<org::imm::ImmPunctuation>(obj); }

void haxorg_destroy_ImmPlaceholder(haxorg_ImmPlaceholder* obj) { execute_destroy<org::imm::ImmPlaceholder>(obj); }

void haxorg_destroy_ImmBigIdent(haxorg_ImmBigIdent* obj) { execute_destroy<org::imm::ImmBigIdent>(obj); }

void haxorg_destroy_ImmTextTarget(haxorg_ImmTextTarget* obj) { execute_destroy<org::imm::ImmTextTarget>(obj); }

void haxorg_destroy_ImmErrorSkipToken(haxorg_ImmErrorSkipToken* obj) { execute_destroy<org::imm::ImmErrorSkipToken>(obj); }

void haxorg_destroy_ImmBold(haxorg_ImmBold* obj) { execute_destroy<org::imm::ImmBold>(obj); }

void haxorg_destroy_ImmUnderline(haxorg_ImmUnderline* obj) { execute_destroy<org::imm::ImmUnderline>(obj); }

void haxorg_destroy_ImmMonospace(haxorg_ImmMonospace* obj) { execute_destroy<org::imm::ImmMonospace>(obj); }

void haxorg_destroy_ImmMarkQuote(haxorg_ImmMarkQuote* obj) { execute_destroy<org::imm::ImmMarkQuote>(obj); }

void haxorg_destroy_ImmVerbatim(haxorg_ImmVerbatim* obj) { execute_destroy<org::imm::ImmVerbatim>(obj); }

void haxorg_destroy_ImmItalic(haxorg_ImmItalic* obj) { execute_destroy<org::imm::ImmItalic>(obj); }

void haxorg_destroy_ImmStrike(haxorg_ImmStrike* obj) { execute_destroy<org::imm::ImmStrike>(obj); }

void haxorg_destroy_ImmPar(haxorg_ImmPar* obj) { execute_destroy<org::imm::ImmPar>(obj); }

void haxorg_destroy_ImmAdapterStmtAPI(haxorg_ImmAdapterStmtAPI* obj) { execute_destroy<org::imm::ImmAdapterStmtAPI>(obj); }

void haxorg_destroy_ImmAdapterSubtreeAPI(haxorg_ImmAdapterSubtreeAPI* obj) { execute_destroy<org::imm::ImmAdapterSubtreeAPI>(obj); }

void haxorg_destroy_ImmAdapterNoNodeAPI(haxorg_ImmAdapterNoNodeAPI* obj) { execute_destroy<org::imm::ImmAdapterNoNodeAPI>(obj); }

void haxorg_destroy_ImmAdapterAttrAPI(haxorg_ImmAdapterAttrAPI* obj) { execute_destroy<org::imm::ImmAdapterAttrAPI>(obj); }

void haxorg_destroy_ImmAdapterAttrListAPI(haxorg_ImmAdapterAttrListAPI* obj) { execute_destroy<org::imm::ImmAdapterAttrListAPI>(obj); }

void haxorg_destroy_ImmAdapterAttrsAPI(haxorg_ImmAdapterAttrsAPI* obj) { execute_destroy<org::imm::ImmAdapterAttrsAPI>(obj); }

void haxorg_destroy_ImmAdapterErrorItemAPI(haxorg_ImmAdapterErrorItemAPI* obj) { execute_destroy<org::imm::ImmAdapterErrorItemAPI>(obj); }

void haxorg_destroy_ImmAdapterErrorGroupAPI(haxorg_ImmAdapterErrorGroupAPI* obj) { execute_destroy<org::imm::ImmAdapterErrorGroupAPI>(obj); }

void haxorg_destroy_ImmAdapterErrorSkipGroupAPI(haxorg_ImmAdapterErrorSkipGroupAPI* obj) { execute_destroy<org::imm::ImmAdapterErrorSkipGroupAPI>(obj); }

void haxorg_destroy_ImmAdapterErrorSkipTokenAPI(haxorg_ImmAdapterErrorSkipTokenAPI* obj) { execute_destroy<org::imm::ImmAdapterErrorSkipTokenAPI>(obj); }

void haxorg_destroy_ImmAdapterStmtListAPI(haxorg_ImmAdapterStmtListAPI* obj) { execute_destroy<org::imm::ImmAdapterStmtListAPI>(obj); }

void haxorg_destroy_ImmAdapterEmptyAPI(haxorg_ImmAdapterEmptyAPI* obj) { execute_destroy<org::imm::ImmAdapterEmptyAPI>(obj); }

void haxorg_destroy_ImmAdapterInlineAPI(haxorg_ImmAdapterInlineAPI* obj) { execute_destroy<org::imm::ImmAdapterInlineAPI>(obj); }

void haxorg_destroy_ImmAdapterTimeAPI(haxorg_ImmAdapterTimeAPI* obj) { execute_destroy<org::imm::ImmAdapterTimeAPI>(obj); }

void haxorg_destroy_ImmAdapterTimeRangeAPI(haxorg_ImmAdapterTimeRangeAPI* obj) { execute_destroy<org::imm::ImmAdapterTimeRangeAPI>(obj); }

void haxorg_destroy_ImmAdapterMacroAPI(haxorg_ImmAdapterMacroAPI* obj) { execute_destroy<org::imm::ImmAdapterMacroAPI>(obj); }

void haxorg_destroy_ImmAdapterSymbolAPI(haxorg_ImmAdapterSymbolAPI* obj) { execute_destroy<org::imm::ImmAdapterSymbolAPI>(obj); }

void haxorg_destroy_ImmAdapterLeafAPI(haxorg_ImmAdapterLeafAPI* obj) { execute_destroy<org::imm::ImmAdapterLeafAPI>(obj); }

void haxorg_destroy_ImmAdapterMarkupAPI(haxorg_ImmAdapterMarkupAPI* obj) { execute_destroy<org::imm::ImmAdapterMarkupAPI>(obj); }

void haxorg_destroy_ImmAdapterLatexAPI(haxorg_ImmAdapterLatexAPI* obj) { execute_destroy<org::imm::ImmAdapterLatexAPI>(obj); }

void haxorg_destroy_ImmAdapterSubtreeLogAPI(haxorg_ImmAdapterSubtreeLogAPI* obj) { execute_destroy<org::imm::ImmAdapterSubtreeLogAPI>(obj); }

void haxorg_destroy_ImmAdapterColonExampleAPI(haxorg_ImmAdapterColonExampleAPI* obj) { execute_destroy<org::imm::ImmAdapterColonExampleAPI>(obj); }

void haxorg_destroy_ImmAdapterCallAPI(haxorg_ImmAdapterCallAPI* obj) { execute_destroy<org::imm::ImmAdapterCallAPI>(obj); }

void haxorg_destroy_ImmAdapterFileAPI(haxorg_ImmAdapterFileAPI* obj) { execute_destroy<org::imm::ImmAdapterFileAPI>(obj); }

void haxorg_destroy_ImmAdapterDirectoryAPI(haxorg_ImmAdapterDirectoryAPI* obj) { execute_destroy<org::imm::ImmAdapterDirectoryAPI>(obj); }

void haxorg_destroy_ImmAdapterSymlinkAPI(haxorg_ImmAdapterSymlinkAPI* obj) { execute_destroy<org::imm::ImmAdapterSymlinkAPI>(obj); }

void haxorg_destroy_ImmAdapterDocumentFragmentAPI(haxorg_ImmAdapterDocumentFragmentAPI* obj) { execute_destroy<org::imm::ImmAdapterDocumentFragmentAPI>(obj); }

void haxorg_destroy_ImmAdapterCriticMarkupAPI(haxorg_ImmAdapterCriticMarkupAPI* obj) { execute_destroy<org::imm::ImmAdapterCriticMarkupAPI>(obj); }

void haxorg_destroy_ImmAdapterListItemAPI(haxorg_ImmAdapterListItemAPI* obj) { execute_destroy<org::imm::ImmAdapterListItemAPI>(obj); }

void haxorg_destroy_ImmAdapterDocumentOptionsAPI(haxorg_ImmAdapterDocumentOptionsAPI* obj) { execute_destroy<org::imm::ImmAdapterDocumentOptionsAPI>(obj); }

void haxorg_destroy_ImmAdapterDocumentAPI(haxorg_ImmAdapterDocumentAPI* obj) { execute_destroy<org::imm::ImmAdapterDocumentAPI>(obj); }

void haxorg_destroy_ImmAdapterFileTargetAPI(haxorg_ImmAdapterFileTargetAPI* obj) { execute_destroy<org::imm::ImmAdapterFileTargetAPI>(obj); }

void haxorg_destroy_ImmAdapterTextSeparatorAPI(haxorg_ImmAdapterTextSeparatorAPI* obj) { execute_destroy<org::imm::ImmAdapterTextSeparatorAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdIncludeAPI(haxorg_ImmAdapterCmdIncludeAPI* obj) { execute_destroy<org::imm::ImmAdapterCmdIncludeAPI>(obj); }

void haxorg_destroy_ImmAdapterDocumentGroupAPI(haxorg_ImmAdapterDocumentGroupAPI* obj) { execute_destroy<org::imm::ImmAdapterDocumentGroupAPI>(obj); }

void haxorg_destroy_Block(haxorg_Block* obj) { execute_destroy<org::sem::Block>(obj); }

void haxorg_destroy_LineCommand(haxorg_LineCommand* obj) { execute_destroy<org::sem::LineCommand>(obj); }

void haxorg_destroy_CmdCreator(haxorg_CmdCreator* obj) { execute_destroy<org::sem::CmdCreator>(obj); }

void haxorg_destroy_CmdAuthor(haxorg_CmdAuthor* obj) { execute_destroy<org::sem::CmdAuthor>(obj); }

void haxorg_destroy_CmdEmail(haxorg_CmdEmail* obj) { execute_destroy<org::sem::CmdEmail>(obj); }

void haxorg_destroy_CmdLanguage(haxorg_CmdLanguage* obj) { execute_destroy<org::sem::CmdLanguage>(obj); }

void haxorg_destroy_CmdCustomArgs(haxorg_CmdCustomArgs* obj) { execute_destroy<org::sem::CmdCustomArgs>(obj); }

void haxorg_destroy_CmdTblfm(haxorg_CmdTblfm* obj) { execute_destroy<org::sem::CmdTblfm>(obj); }

void haxorg_destroy_Cell(haxorg_Cell* obj) { execute_destroy<org::sem::Cell>(obj); }

void haxorg_destroy_Row(haxorg_Row* obj) { execute_destroy<org::sem::Row>(obj); }

void haxorg_destroy_ImmBlock(haxorg_ImmBlock* obj) { execute_destroy<org::imm::ImmBlock>(obj); }

void haxorg_destroy_ImmLineCommand(haxorg_ImmLineCommand* obj) { execute_destroy<org::imm::ImmLineCommand>(obj); }

void haxorg_destroy_ImmCmdCreator(haxorg_ImmCmdCreator* obj) { execute_destroy<org::imm::ImmCmdCreator>(obj); }

void haxorg_destroy_ImmCmdAuthor(haxorg_ImmCmdAuthor* obj) { execute_destroy<org::imm::ImmCmdAuthor>(obj); }

void haxorg_destroy_ImmCmdEmail(haxorg_ImmCmdEmail* obj) { execute_destroy<org::imm::ImmCmdEmail>(obj); }

void haxorg_destroy_ImmCmdLanguage(haxorg_ImmCmdLanguage* obj) { execute_destroy<org::imm::ImmCmdLanguage>(obj); }

void haxorg_destroy_ImmCmdCustomArgs(haxorg_ImmCmdCustomArgs* obj) { execute_destroy<org::imm::ImmCmdCustomArgs>(obj); }

void haxorg_destroy_ImmCmdTblfm(haxorg_ImmCmdTblfm* obj) { execute_destroy<org::imm::ImmCmdTblfm>(obj); }

void haxorg_destroy_ImmCell(haxorg_ImmCell* obj) { execute_destroy<org::imm::ImmCell>(obj); }

void haxorg_destroy_ImmRow(haxorg_ImmRow* obj) { execute_destroy<org::imm::ImmRow>(obj); }

void haxorg_destroy_ImmAdapterCmdAPI(haxorg_ImmAdapterCmdAPI* obj) { execute_destroy<org::imm::ImmAdapterCmdAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdCustomRawAPI(haxorg_ImmAdapterCmdCustomRawAPI* obj) { execute_destroy<org::imm::ImmAdapterCmdCustomRawAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdCustomTextAPI(haxorg_ImmAdapterCmdCustomTextAPI* obj) { execute_destroy<org::imm::ImmAdapterCmdCustomTextAPI>(obj); }

void haxorg_destroy_ImmAdapterLinkAPI(haxorg_ImmAdapterLinkAPI* obj) { execute_destroy<org::imm::ImmAdapterLinkAPI>(obj); }

void haxorg_destroy_ImmAdapterBlockCommentAPI(haxorg_ImmAdapterBlockCommentAPI* obj) { execute_destroy<org::imm::ImmAdapterBlockCommentAPI>(obj); }

void haxorg_destroy_ImmAdapterParagraphAPI(haxorg_ImmAdapterParagraphAPI* obj) { execute_destroy<org::imm::ImmAdapterParagraphAPI>(obj); }

void haxorg_destroy_ImmAdapterListAPI(haxorg_ImmAdapterListAPI* obj) { execute_destroy<org::imm::ImmAdapterListAPI>(obj); }

void haxorg_destroy_ImmStmtAdapter(haxorg_ImmStmtAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmSubtreeAdapter(haxorg_ImmSubtreeAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmNoNodeAdapter(haxorg_ImmNoNodeAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmErrorItemAdapter(haxorg_ImmErrorItemAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmErrorGroupAdapter(haxorg_ImmErrorGroupAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmErrorSkipGroupAdapter(haxorg_ImmErrorSkipGroupAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmErrorSkipTokenAdapter(haxorg_ImmErrorSkipTokenAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmStmtListAdapter(haxorg_ImmStmtListAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmEmptyAdapter(haxorg_ImmEmptyAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmAdapterHashTagAPI(haxorg_ImmAdapterHashTagAPI* obj) { execute_destroy<org::imm::ImmAdapterHashTagAPI>(obj); }

void haxorg_destroy_ImmAdapterInlineFootnoteAPI(haxorg_ImmAdapterInlineFootnoteAPI* obj) { execute_destroy<org::imm::ImmAdapterInlineFootnoteAPI>(obj); }

void haxorg_destroy_ImmAdapterSubtreeCompletionAPI(haxorg_ImmAdapterSubtreeCompletionAPI* obj) { execute_destroy<org::imm::ImmAdapterSubtreeCompletionAPI>(obj); }

void haxorg_destroy_ImmInlineAdapter(haxorg_ImmInlineAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmTimeAdapter(haxorg_ImmTimeAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmTimeRangeAdapter(haxorg_ImmTimeRangeAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmMacroAdapter(haxorg_ImmMacroAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmSymbolAdapter(haxorg_ImmSymbolAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmAdapterEscapedAPI(haxorg_ImmAdapterEscapedAPI* obj) { execute_destroy<org::imm::ImmAdapterEscapedAPI>(obj); }

void haxorg_destroy_ImmAdapterNewlineAPI(haxorg_ImmAdapterNewlineAPI* obj) { execute_destroy<org::imm::ImmAdapterNewlineAPI>(obj); }

void haxorg_destroy_ImmAdapterSpaceAPI(haxorg_ImmAdapterSpaceAPI* obj) { execute_destroy<org::imm::ImmAdapterSpaceAPI>(obj); }

void haxorg_destroy_ImmAdapterWordAPI(haxorg_ImmAdapterWordAPI* obj) { execute_destroy<org::imm::ImmAdapterWordAPI>(obj); }

void haxorg_destroy_ImmAdapterAtMentionAPI(haxorg_ImmAdapterAtMentionAPI* obj) { execute_destroy<org::imm::ImmAdapterAtMentionAPI>(obj); }

void haxorg_destroy_ImmAdapterRawTextAPI(haxorg_ImmAdapterRawTextAPI* obj) { execute_destroy<org::imm::ImmAdapterRawTextAPI>(obj); }

void haxorg_destroy_ImmAdapterPunctuationAPI(haxorg_ImmAdapterPunctuationAPI* obj) { execute_destroy<org::imm::ImmAdapterPunctuationAPI>(obj); }

void haxorg_destroy_ImmAdapterPlaceholderAPI(haxorg_ImmAdapterPlaceholderAPI* obj) { execute_destroy<org::imm::ImmAdapterPlaceholderAPI>(obj); }

void haxorg_destroy_ImmAdapterBigIdentAPI(haxorg_ImmAdapterBigIdentAPI* obj) { execute_destroy<org::imm::ImmAdapterBigIdentAPI>(obj); }

void haxorg_destroy_ImmAdapterTextTargetAPI(haxorg_ImmAdapterTextTargetAPI* obj) { execute_destroy<org::imm::ImmAdapterTextTargetAPI>(obj); }

void haxorg_destroy_ImmLeafAdapter(haxorg_ImmLeafAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmAdapterBoldAPI(haxorg_ImmAdapterBoldAPI* obj) { execute_destroy<org::imm::ImmAdapterBoldAPI>(obj); }

void haxorg_destroy_ImmAdapterUnderlineAPI(haxorg_ImmAdapterUnderlineAPI* obj) { execute_destroy<org::imm::ImmAdapterUnderlineAPI>(obj); }

void haxorg_destroy_ImmAdapterMonospaceAPI(haxorg_ImmAdapterMonospaceAPI* obj) { execute_destroy<org::imm::ImmAdapterMonospaceAPI>(obj); }

void haxorg_destroy_ImmAdapterMarkQuoteAPI(haxorg_ImmAdapterMarkQuoteAPI* obj) { execute_destroy<org::imm::ImmAdapterMarkQuoteAPI>(obj); }

void haxorg_destroy_ImmAdapterRadioTargetAPI(haxorg_ImmAdapterRadioTargetAPI* obj) { execute_destroy<org::imm::ImmAdapterRadioTargetAPI>(obj); }

void haxorg_destroy_ImmAdapterVerbatimAPI(haxorg_ImmAdapterVerbatimAPI* obj) { execute_destroy<org::imm::ImmAdapterVerbatimAPI>(obj); }

void haxorg_destroy_ImmAdapterItalicAPI(haxorg_ImmAdapterItalicAPI* obj) { execute_destroy<org::imm::ImmAdapterItalicAPI>(obj); }

void haxorg_destroy_ImmAdapterStrikeAPI(haxorg_ImmAdapterStrikeAPI* obj) { execute_destroy<org::imm::ImmAdapterStrikeAPI>(obj); }

void haxorg_destroy_ImmAdapterParAPI(haxorg_ImmAdapterParAPI* obj) { execute_destroy<org::imm::ImmAdapterParAPI>(obj); }

void haxorg_destroy_ImmMarkupAdapter(haxorg_ImmMarkupAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmLatexAdapter(haxorg_ImmLatexAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmSubtreeLogAdapter(haxorg_ImmSubtreeLogAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmColonExampleAdapter(haxorg_ImmColonExampleAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmCallAdapter(haxorg_ImmCallAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmFileAdapter(haxorg_ImmFileAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmDirectoryAdapter(haxorg_ImmDirectoryAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmSymlinkAdapter(haxorg_ImmSymlinkAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmDocumentFragmentAdapter(haxorg_ImmDocumentFragmentAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmCriticMarkupAdapter(haxorg_ImmCriticMarkupAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmListItemAdapter(haxorg_ImmListItemAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmDocumentOptionsAdapter(haxorg_ImmDocumentOptionsAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmDocumentAdapter(haxorg_ImmDocumentAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmFileTargetAdapter(haxorg_ImmFileTargetAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmTextSeparatorAdapter(haxorg_ImmTextSeparatorAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmCmdIncludeAdapter(haxorg_ImmCmdIncludeAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmDocumentGroupAdapter(haxorg_ImmDocumentGroupAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_BlockCenter(haxorg_BlockCenter* obj) { execute_destroy<org::sem::BlockCenter>(obj); }

void haxorg_destroy_BlockQuote(haxorg_BlockQuote* obj) { execute_destroy<org::sem::BlockQuote>(obj); }

void haxorg_destroy_BlockVerse(haxorg_BlockVerse* obj) { execute_destroy<org::sem::BlockVerse>(obj); }

void haxorg_destroy_BlockDynamicFallback(haxorg_BlockDynamicFallback* obj) { execute_destroy<org::sem::BlockDynamicFallback>(obj); }

void haxorg_destroy_BlockExample(haxorg_BlockExample* obj) { execute_destroy<org::sem::BlockExample>(obj); }

void haxorg_destroy_BlockExport(haxorg_BlockExport* obj) { execute_destroy<org::sem::BlockExport>(obj); }

void haxorg_destroy_BlockAdmonition(haxorg_BlockAdmonition* obj) { execute_destroy<org::sem::BlockAdmonition>(obj); }

void haxorg_destroy_BlockCodeEvalResult(haxorg_BlockCodeEvalResult* obj) { execute_destroy<org::sem::BlockCodeEvalResult>(obj); }

void haxorg_destroy_BlockCode(haxorg_BlockCode* obj) { execute_destroy<org::sem::BlockCode>(obj); }

void haxorg_destroy_Table(haxorg_Table* obj) { execute_destroy<org::sem::Table>(obj); }

void haxorg_destroy_Attached(haxorg_Attached* obj) { execute_destroy<org::sem::Attached>(obj); }

void haxorg_destroy_ImmBlockCenter(haxorg_ImmBlockCenter* obj) { execute_destroy<org::imm::ImmBlockCenter>(obj); }

void haxorg_destroy_ImmBlockQuote(haxorg_ImmBlockQuote* obj) { execute_destroy<org::imm::ImmBlockQuote>(obj); }

void haxorg_destroy_ImmBlockVerse(haxorg_ImmBlockVerse* obj) { execute_destroy<org::imm::ImmBlockVerse>(obj); }

void haxorg_destroy_ImmBlockDynamicFallback(haxorg_ImmBlockDynamicFallback* obj) { execute_destroy<org::imm::ImmBlockDynamicFallback>(obj); }

void haxorg_destroy_ImmBlockExample(haxorg_ImmBlockExample* obj) { execute_destroy<org::imm::ImmBlockExample>(obj); }

void haxorg_destroy_ImmBlockExport(haxorg_ImmBlockExport* obj) { execute_destroy<org::imm::ImmBlockExport>(obj); }

void haxorg_destroy_ImmBlockAdmonition(haxorg_ImmBlockAdmonition* obj) { execute_destroy<org::imm::ImmBlockAdmonition>(obj); }

void haxorg_destroy_ImmBlockCodeEvalResult(haxorg_ImmBlockCodeEvalResult* obj) { execute_destroy<org::imm::ImmBlockCodeEvalResult>(obj); }

void haxorg_destroy_ImmBlockCode(haxorg_ImmBlockCode* obj) { execute_destroy<org::imm::ImmBlockCode>(obj); }

void haxorg_destroy_ImmTable(haxorg_ImmTable* obj) { execute_destroy<org::imm::ImmTable>(obj); }

void haxorg_destroy_ImmAttached(haxorg_ImmAttached* obj) { execute_destroy<org::imm::ImmAttached>(obj); }

void haxorg_destroy_ImmAdapterLineCommandAPI(haxorg_ImmAdapterLineCommandAPI* obj) { execute_destroy<org::imm::ImmAdapterLineCommandAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdCustomArgsAPI(haxorg_ImmAdapterCmdCustomArgsAPI* obj) { execute_destroy<org::imm::ImmAdapterCmdCustomArgsAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdCreatorAPI(haxorg_ImmAdapterCmdCreatorAPI* obj) { execute_destroy<org::imm::ImmAdapterCmdCreatorAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdAuthorAPI(haxorg_ImmAdapterCmdAuthorAPI* obj) { execute_destroy<org::imm::ImmAdapterCmdAuthorAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdEmailAPI(haxorg_ImmAdapterCmdEmailAPI* obj) { execute_destroy<org::imm::ImmAdapterCmdEmailAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdLanguageAPI(haxorg_ImmAdapterCmdLanguageAPI* obj) { execute_destroy<org::imm::ImmAdapterCmdLanguageAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdTblfmAPI(haxorg_ImmAdapterCmdTblfmAPI* obj) { execute_destroy<org::imm::ImmAdapterCmdTblfmAPI>(obj); }

void haxorg_destroy_ImmAdapterBlockAPI(haxorg_ImmAdapterBlockAPI* obj) { execute_destroy<org::imm::ImmAdapterBlockAPI>(obj); }

void haxorg_destroy_ImmAdapterCellAPI(haxorg_ImmAdapterCellAPI* obj) { execute_destroy<org::imm::ImmAdapterCellAPI>(obj); }

void haxorg_destroy_ImmAdapterRowAPI(haxorg_ImmAdapterRowAPI* obj) { execute_destroy<org::imm::ImmAdapterRowAPI>(obj); }

void haxorg_destroy_ImmCmdAdapter(haxorg_ImmCmdAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmCmdCustomRawAdapter(haxorg_ImmCmdCustomRawAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmCmdCustomTextAdapter(haxorg_ImmCmdCustomTextAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmLinkAdapter(haxorg_ImmLinkAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmBlockCommentAdapter(haxorg_ImmBlockCommentAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmParagraphAdapter(haxorg_ImmParagraphAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmListAdapter(haxorg_ImmListAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmHashTagAdapter(haxorg_ImmHashTagAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmInlineFootnoteAdapter(haxorg_ImmInlineFootnoteAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmEscapedAdapter(haxorg_ImmEscapedAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmNewlineAdapter(haxorg_ImmNewlineAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmSpaceAdapter(haxorg_ImmSpaceAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmWordAdapter(haxorg_ImmWordAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmAtMentionAdapter(haxorg_ImmAtMentionAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmRawTextAdapter(haxorg_ImmRawTextAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmPunctuationAdapter(haxorg_ImmPunctuationAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmPlaceholderAdapter(haxorg_ImmPlaceholderAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmBigIdentAdapter(haxorg_ImmBigIdentAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmTextTargetAdapter(haxorg_ImmTextTargetAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmBoldAdapter(haxorg_ImmBoldAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmUnderlineAdapter(haxorg_ImmUnderlineAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmMonospaceAdapter(haxorg_ImmMonospaceAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmMarkQuoteAdapter(haxorg_ImmMarkQuoteAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmRadioTargetAdapter(haxorg_ImmRadioTargetAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmVerbatimAdapter(haxorg_ImmVerbatimAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmItalicAdapter(haxorg_ImmItalicAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmStrikeAdapter(haxorg_ImmStrikeAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmParAdapter(haxorg_ImmParAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_CmdCaption(haxorg_CmdCaption* obj) { execute_destroy<org::sem::CmdCaption>(obj); }

void haxorg_destroy_CmdColumns(haxorg_CmdColumns* obj) { execute_destroy<org::sem::CmdColumns>(obj); }

void haxorg_destroy_CmdName(haxorg_CmdName* obj) { execute_destroy<org::sem::CmdName>(obj); }

void haxorg_destroy_CmdCall(haxorg_CmdCall* obj) { execute_destroy<org::sem::CmdCall>(obj); }

void haxorg_destroy_CmdAttr(haxorg_CmdAttr* obj) { execute_destroy<org::sem::CmdAttr>(obj); }

void haxorg_destroy_CmdExport(haxorg_CmdExport* obj) { execute_destroy<org::sem::CmdExport>(obj); }

void haxorg_destroy_ImmCmdCaption(haxorg_ImmCmdCaption* obj) { execute_destroy<org::imm::ImmCmdCaption>(obj); }

void haxorg_destroy_ImmCmdColumns(haxorg_ImmCmdColumns* obj) { execute_destroy<org::imm::ImmCmdColumns>(obj); }

void haxorg_destroy_ImmCmdName(haxorg_ImmCmdName* obj) { execute_destroy<org::imm::ImmCmdName>(obj); }

void haxorg_destroy_ImmCmdCall(haxorg_ImmCmdCall* obj) { execute_destroy<org::imm::ImmCmdCall>(obj); }

void haxorg_destroy_ImmCmdAttr(haxorg_ImmCmdAttr* obj) { execute_destroy<org::imm::ImmCmdAttr>(obj); }

void haxorg_destroy_ImmCmdExport(haxorg_ImmCmdExport* obj) { execute_destroy<org::imm::ImmCmdExport>(obj); }

void haxorg_destroy_ImmAdapterAttachedAPI(haxorg_ImmAdapterAttachedAPI* obj) { execute_destroy<org::imm::ImmAdapterAttachedAPI>(obj); }

void haxorg_destroy_ImmLineCommandAdapter(haxorg_ImmLineCommandAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmCmdCustomArgsAdapter(haxorg_ImmCmdCustomArgsAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmCmdCreatorAdapter(haxorg_ImmCmdCreatorAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmCmdAuthorAdapter(haxorg_ImmCmdAuthorAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmCmdEmailAdapter(haxorg_ImmCmdEmailAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmCmdLanguageAdapter(haxorg_ImmCmdLanguageAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmCmdTblfmAdapter(haxorg_ImmCmdTblfmAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmAdapterBlockCenterAPI(haxorg_ImmAdapterBlockCenterAPI* obj) { execute_destroy<org::imm::ImmAdapterBlockCenterAPI>(obj); }

void haxorg_destroy_ImmAdapterBlockQuoteAPI(haxorg_ImmAdapterBlockQuoteAPI* obj) { execute_destroy<org::imm::ImmAdapterBlockQuoteAPI>(obj); }

void haxorg_destroy_ImmAdapterBlockVerseAPI(haxorg_ImmAdapterBlockVerseAPI* obj) { execute_destroy<org::imm::ImmAdapterBlockVerseAPI>(obj); }

void haxorg_destroy_ImmAdapterBlockExampleAPI(haxorg_ImmAdapterBlockExampleAPI* obj) { execute_destroy<org::imm::ImmAdapterBlockExampleAPI>(obj); }

void haxorg_destroy_ImmAdapterInlineExportAPI(haxorg_ImmAdapterInlineExportAPI* obj) { execute_destroy<org::imm::ImmAdapterInlineExportAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdExportAPI(haxorg_ImmAdapterCmdExportAPI* obj) { execute_destroy<org::imm::ImmAdapterCmdExportAPI>(obj); }

void haxorg_destroy_ImmAdapterBlockExportAPI(haxorg_ImmAdapterBlockExportAPI* obj) { execute_destroy<org::imm::ImmAdapterBlockExportAPI>(obj); }

void haxorg_destroy_ImmAdapterBlockDynamicFallbackAPI(haxorg_ImmAdapterBlockDynamicFallbackAPI* obj) { execute_destroy<org::imm::ImmAdapterBlockDynamicFallbackAPI>(obj); }

void haxorg_destroy_ImmAdapterBlockAdmonitionAPI(haxorg_ImmAdapterBlockAdmonitionAPI* obj) { execute_destroy<org::imm::ImmAdapterBlockAdmonitionAPI>(obj); }

void haxorg_destroy_ImmAdapterBlockCodeEvalResultAPI(haxorg_ImmAdapterBlockCodeEvalResultAPI* obj) { execute_destroy<org::imm::ImmAdapterBlockCodeEvalResultAPI>(obj); }

void haxorg_destroy_ImmAdapterBlockCodeAPI(haxorg_ImmAdapterBlockCodeAPI* obj) { execute_destroy<org::imm::ImmAdapterBlockCodeAPI>(obj); }

void haxorg_destroy_ImmAdapterTableAPI(haxorg_ImmAdapterTableAPI* obj) { execute_destroy<org::imm::ImmAdapterTableAPI>(obj); }

void haxorg_destroy_ImmBlockAdapter(haxorg_ImmBlockAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmCellAdapter(haxorg_ImmCellAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmRowAdapter(haxorg_ImmRowAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmAdapterCmdCaptionAPI(haxorg_ImmAdapterCmdCaptionAPI* obj) { execute_destroy<org::imm::ImmAdapterCmdCaptionAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdColumnsAPI(haxorg_ImmAdapterCmdColumnsAPI* obj) { execute_destroy<org::imm::ImmAdapterCmdColumnsAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdNameAPI(haxorg_ImmAdapterCmdNameAPI* obj) { execute_destroy<org::imm::ImmAdapterCmdNameAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdCallAPI(haxorg_ImmAdapterCmdCallAPI* obj) { execute_destroy<org::imm::ImmAdapterCmdCallAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdResultsAPI(haxorg_ImmAdapterCmdResultsAPI* obj) { execute_destroy<org::imm::ImmAdapterCmdResultsAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdAttrAPI(haxorg_ImmAdapterCmdAttrAPI* obj) { execute_destroy<org::imm::ImmAdapterCmdAttrAPI>(obj); }

void haxorg_destroy_ImmAttachedAdapter(haxorg_ImmAttachedAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmBlockCenterAdapter(haxorg_ImmBlockCenterAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmBlockQuoteAdapter(haxorg_ImmBlockQuoteAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmBlockVerseAdapter(haxorg_ImmBlockVerseAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmBlockExampleAdapter(haxorg_ImmBlockExampleAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmInlineExportAdapter(haxorg_ImmInlineExportAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmCmdExportAdapter(haxorg_ImmCmdExportAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmBlockExportAdapter(haxorg_ImmBlockExportAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmBlockDynamicFallbackAdapter(haxorg_ImmBlockDynamicFallbackAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmBlockAdmonitionAdapter(haxorg_ImmBlockAdmonitionAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmBlockCodeEvalResultAdapter(haxorg_ImmBlockCodeEvalResultAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmBlockCodeAdapter(haxorg_ImmBlockCodeAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmTableAdapter(haxorg_ImmTableAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmCmdCaptionAdapter(haxorg_ImmCmdCaptionAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmCmdColumnsAdapter(haxorg_ImmCmdColumnsAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmCmdNameAdapter(haxorg_ImmCmdNameAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmCmdCallAdapter(haxorg_ImmCmdCallAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmCmdAttrAdapter(haxorg_ImmCmdAttrAdapter* obj) { execute_destroy<org::imm::ImmAdapterT>(obj); }

haxorg_SemId newSemTimeStatic(haxorg_UserTimeBreakdown breakdown, bool isActive, OrgContext* org_context) { return convert_cpp_execution<haxorg_SemId, org::sem::SemId<org::sem::Time>(*)(hstd::UserTimeBreakdown const&, bool), haxorg_UserTimeBreakdown, bool>(&org::newSemTimeStatic, org_context, breakdown, isActive); }

haxorg_ImmAstContext initImmutableAstContext(OrgContext* org_context) { return convert_cpp_execution<haxorg_ImmAstContext, std::shared_ptr<org::imm::ImmAstContext>(*)()>(&org::initImmutableAstContext, org_context); }

haxorg_SemId asOneNode(haxorg_SemId arg, OrgContext* org_context) { return convert_cpp_execution<haxorg_SemId, org::sem::SemId<org::sem::Org>(*)(org::sem::SemId<org::sem::Org> const&), haxorg_SemId>(&org::asOneNode, org_context, arg); }

haxorg_StdString formatToString(haxorg_SemId arg, OrgContext* org_context) { return convert_cpp_execution<haxorg_StdString, std::string(*)(org::sem::SemId<org::sem::Org>), haxorg_SemId>(&org::formatToString, org_context, arg); }

haxorg_StdString exportToYamlString(haxorg_SemId node, haxorg_OrgYamlExportOpts opts, OrgContext* org_context) { return convert_cpp_execution<haxorg_StdString, std::string(*)(org::sem::SemId<org::sem::Org> const&, org::OrgYamlExportOpts const&), haxorg_SemId, haxorg_OrgYamlExportOpts>(&org::exportToYamlString, org_context, node, opts); }

void exportToYamlFile(haxorg_SemId node, haxorg_StdString path, haxorg_OrgYamlExportOpts opts, OrgContext* org_context) { return convert_cpp_execution<void, void(*)(org::sem::SemId<org::sem::Org> const&, std::string, org::OrgYamlExportOpts const&), haxorg_SemId, haxorg_StdString, haxorg_OrgYamlExportOpts>(&org::exportToYamlFile, org_context, node, path, opts); }

haxorg_StdString exportToJsonString(haxorg_SemId node, OrgContext* org_context) { return convert_cpp_execution<haxorg_StdString, std::string(*)(org::sem::SemId<org::sem::Org> const&), haxorg_SemId>(&org::exportToJsonString, org_context, node); }

void exportToJsonFile(haxorg_SemId node, haxorg_StdString path, OrgContext* org_context) { return convert_cpp_execution<void, void(*)(org::sem::SemId<org::sem::Org> const&, std::string), haxorg_SemId, haxorg_StdString>(&org::exportToJsonFile, org_context, node, path); }

haxorg_SemId readProtobufFile(haxorg_StdString file, OrgContext* org_context) { return convert_cpp_execution<haxorg_SemId, org::sem::SemId<org::sem::Document>(*)(std::string const&), haxorg_StdString>(&org::readProtobufFile, org_context, file); }

void exportToProtobufFile(haxorg_SemId doc, haxorg_StdString file, OrgContext* org_context) { return convert_cpp_execution<void, void(*)(org::sem::SemId<org::sem::Document>, std::string const&), haxorg_SemId, haxorg_StdString>(&org::exportToProtobufFile, org_context, doc, file); }

haxorg_StdString exportToTreeString(haxorg_SemId node, haxorg_OrgTreeExportOpts opts, OrgContext* org_context) { return convert_cpp_execution<haxorg_StdString, std::string(*)(org::sem::SemId<org::sem::Org> const&, org::OrgTreeExportOpts const&), haxorg_SemId, haxorg_OrgTreeExportOpts>(&org::exportToTreeString, org_context, node, opts); }

void exportToTreeFile(haxorg_SemId node, haxorg_StdString path, haxorg_OrgTreeExportOpts opts, OrgContext* org_context) { return convert_cpp_execution<void, void(*)(org::sem::SemId<org::sem::Org> const&, std::string, org::OrgTreeExportOpts const&), haxorg_SemId, haxorg_StdString, haxorg_OrgTreeExportOpts>(&org::exportToTreeFile, org_context, node, path, opts); }

haxorg_AstTrackingMap getAstTrackingMap(haxorg_HstdVec nodes, OrgContext* org_context) { return convert_cpp_execution<haxorg_AstTrackingMap, org::AstTrackingMap(*)(hstd::Vec<org::sem::SemId<org::sem::Org>> const&), haxorg_HstdVec>(&org::getAstTrackingMap, org_context, nodes); }

haxorg_HstdVec getSubnodeGroups(haxorg_SemId node, haxorg_AstTrackingMap map, OrgContext* org_context) { return convert_cpp_execution<haxorg_HstdVec, hstd::Vec<org::AstTrackingGroup>(*)(org::sem::SemId<org::sem::Org>, org::AstTrackingMap const&), haxorg_SemId, haxorg_AstTrackingMap>(&org::getSubnodeGroups, org_context, node, map); }

haxorg_HstdVec annotateSequence(haxorg_HstdVec groups, int first, int last, OrgContext* org_context) { return convert_cpp_execution<haxorg_HstdVec, hstd::Vec<hstd::SequenceAnnotation>(*)(hstd::Vec<hstd::SequenceSegmentGroup> const&, int, int), haxorg_HstdVec, int, int>(&hstd::annotateSequence, org_context, groups, first, last); }

haxorg_GraphMapGraphState initMapGraphState(haxorg_ImmAstContext ast, OrgContext* org_context) { return convert_cpp_execution<haxorg_GraphMapGraphState, std::shared_ptr<org::graph::MapGraphState>(*)(std::shared_ptr<org::imm::ImmAstContext>), haxorg_ImmAstContext>(&org::graph::initMapGraphState, org_context, ast); }

haxorg_StdString serializeToText(haxorg_ImmAstContext store, OrgContext* org_context) { return convert_cpp_execution<haxorg_StdString, std::string(*)(std::shared_ptr<org::imm::ImmAstContext> const&), haxorg_ImmAstContext>(&org::imm::serializeToText, org_context, store); }

void serializeFromText(haxorg_StdString binary, haxorg_ImmAstContext store, OrgContext* org_context) { return convert_cpp_execution<void, void(*)(std::string const&, std::shared_ptr<org::imm::ImmAstContext> const&), haxorg_StdString, haxorg_ImmAstContext>(&org::imm::serializeFromText, org_context, binary, store); }

haxorg_StdString serializeToText(haxorg_ImmAstReplaceEpoch store, OrgContext* org_context) { return convert_cpp_execution<haxorg_StdString, std::string(*)(std::shared_ptr<org::imm::ImmAstReplaceEpoch> const&), haxorg_ImmAstReplaceEpoch>(&org::imm::serializeToText, org_context, store); }

void serializeFromText(haxorg_StdString binary, haxorg_ImmAstReplaceEpoch store, OrgContext* org_context) { return convert_cpp_execution<void, void(*)(std::string const&, std::shared_ptr<org::imm::ImmAstReplaceEpoch> const&), haxorg_StdString, haxorg_ImmAstReplaceEpoch>(&org::imm::serializeFromText, org_context, binary, store); }

haxorg_StdString serializeToText(haxorg_GraphMapGraph store, OrgContext* org_context) { return convert_cpp_execution<haxorg_StdString, std::string(*)(std::shared_ptr<org::graph::MapGraph> const&), haxorg_GraphMapGraph>(&org::imm::serializeToText, org_context, store); }

void serializeFromText(haxorg_StdString binary, haxorg_GraphMapGraph store, OrgContext* org_context) { return convert_cpp_execution<void, void(*)(std::string const&, std::shared_ptr<org::graph::MapGraph> const&), haxorg_StdString, haxorg_GraphMapGraph>(&org::imm::serializeFromText, org_context, binary, store); }

haxorg_StdString serializeFromTextToTreeDump(haxorg_StdString binary, OrgContext* org_context) { return convert_cpp_execution<haxorg_StdString, std::string(*)(std::string const&), haxorg_StdString>(&org::imm::serializeFromTextToTreeDump, org_context, binary); }

/* clang-format on */
