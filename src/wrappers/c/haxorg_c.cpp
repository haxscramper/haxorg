/* clang-format off */
#include <wrappers/c/haxorg_c.h>
#include <wrappers/c/haxorg_c_vtables.hpp>
#include <wrappers/c/haxorg_c_vtables_manual.hpp>
#include <wrappers/c/haxorg_c_utils.hpp>


































void haxorg_destroy_UserTimeBreakdown(haxorg_UserTimeBreakdown* obj) { org::bind::c::execute_destroy<hstd::UserTimeBreakdown>(obj); }

void haxorg_destroy_UserTime(haxorg_UserTime* obj) { org::bind::c::execute_destroy<hstd::UserTime>(obj); }

void haxorg_destroy_ParseSourceFileId(haxorg_ParseSourceFileId* obj) { org::bind::c::execute_destroy<org::parse::SourceFileId>(obj); }

void haxorg_destroy_ParseSourceManager(haxorg_ParseSourceManager* obj) { org::bind::c::execute_destroy<org::parse::SourceManager>(obj); }

void haxorg_destroy_ParseSourceLoc(haxorg_ParseSourceLoc* obj) { org::bind::c::execute_destroy<org::parse::SourceLoc>(obj); }

void haxorg_destroy_OrgJson(haxorg_OrgJson* obj) { org::bind::c::execute_destroy<org::sem::OrgJson>(obj); }

void haxorg_destroy_Org(haxorg_Org* obj) { org::bind::c::execute_destroy<org::sem::Org>(obj); }

void haxorg_destroy_OperationsTracer(haxorg_OperationsTracer* obj) { org::bind::c::execute_destroy<hstd::OperationsTracer>(obj); }

void haxorg_destroy_Cache(haxorg_Cache* obj) { org::bind::c::execute_destroy<hstd::ext::Cache>(obj); }

void haxorg_destroy_ParseOrgParseFragment(haxorg_ParseOrgParseFragment* obj) { org::bind::c::execute_destroy<org::parse::OrgParseFragment>(obj); }

void haxorg_destroy_OrgParseParameters(haxorg_OrgParseParameters* obj) { org::bind::c::execute_destroy<org::parse::OrgParseParameters>(obj); }

void haxorg_destroy_OrgDirectoryParseParameters(haxorg_OrgDirectoryParseParameters* obj) { org::bind::c::execute_destroy<org::parse::OrgDirectoryParseParameters>(obj); }

haxorg_ParseContext haxorg_create_ParseContext_ParseContextDefault(OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ParseContext, haxorg_ParseContext_vtable>(+[]() -> org::parse::ParseContext { return org::parse::ParseContext(); }, org_context); }

haxorg_ParseContext haxorg_create_ParseContext_ParseContextWithManager(OrgContext* org_context, haxorg_ParseSourceManager source) { return org::bind::c::execute_cpp<haxorg_ParseContext, haxorg_ParseContext_vtable>(+[](std::shared_ptr<org::parse::SourceManager> const& source) -> org::parse::ParseContext { return org::parse::ParseContext(source); }, org_context, source); }

void haxorg_destroy_ParseContext(haxorg_ParseContext* obj) { org::bind::c::execute_destroy<org::parse::ParseContext>(obj); }

void haxorg_destroy_ImmReflFieldId(haxorg_ImmReflFieldId* obj) { org::bind::c::execute_destroy<org::imm::ImmReflFieldId>(obj); }

void haxorg_destroy_ImmId(haxorg_ImmId* obj) { org::bind::c::execute_destroy<org::imm::ImmId>(obj); }

void haxorg_destroy_ImmOrg(haxorg_ImmOrg* obj) { org::bind::c::execute_destroy<org::imm::ImmOrg>(obj); }

void haxorg_destroy_ImmPathStep(haxorg_ImmPathStep* obj) { org::bind::c::execute_destroy<org::imm::ImmPathStep>(obj); }

void haxorg_destroy_ImmPath(haxorg_ImmPath* obj) { org::bind::c::execute_destroy<org::imm::ImmPath>(obj); }

void haxorg_destroy_ImmUniqId(haxorg_ImmUniqId* obj) { org::bind::c::execute_destroy<org::imm::ImmUniqId>(obj); }

void haxorg_destroy_ImmAstReplaceEpoch(haxorg_ImmAstReplaceEpoch* obj) { org::bind::c::execute_destroy<org::imm::ImmAstReplaceEpoch>(obj); }

void haxorg_destroy_ImmAstContext(haxorg_ImmAstContext* obj) { org::bind::c::execute_destroy<org::imm::ImmAstContext>(obj); }

void haxorg_destroy_ImmAstVersion(haxorg_ImmAstVersion* obj) { org::bind::c::execute_destroy<org::imm::ImmAstVersion>(obj); }

void haxorg_destroy_ImmAdapterTreeReprConf(haxorg_ImmAdapterTreeReprConf* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapter::TreeReprConf>(obj); }

void haxorg_destroy_ImmAdapter(haxorg_ImmAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapter>(obj); }

void haxorg_destroy_ImmAdapterVirtualBase(haxorg_ImmAdapterVirtualBase* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterVirtualBase>(obj); }

void haxorg_destroy_OrgYamlExportOpts(haxorg_OrgYamlExportOpts* obj) { org::bind::c::execute_destroy<org::OrgYamlExportOpts>(obj); }

void haxorg_destroy_OrgTreeExportOpts(haxorg_OrgTreeExportOpts* obj) { org::bind::c::execute_destroy<org::OrgTreeExportOpts>(obj); }

void haxorg_destroy_AstTrackingPath(haxorg_AstTrackingPath* obj) { org::bind::c::execute_destroy<org::AstTrackingPath>(obj); }

void haxorg_destroy_AstTrackingAlternatives(haxorg_AstTrackingAlternatives* obj) { org::bind::c::execute_destroy<org::AstTrackingAlternatives>(obj); }

void haxorg_destroy_AstTrackingGroupRadioTarget(haxorg_AstTrackingGroupRadioTarget* obj) { org::bind::c::execute_destroy<org::AstTrackingGroup::RadioTarget>(obj); }

void haxorg_destroy_AstTrackingGroupSingle(haxorg_AstTrackingGroupSingle* obj) { org::bind::c::execute_destroy<org::AstTrackingGroup::Single>(obj); }

void haxorg_destroy_AstTrackingGroupTrackedHashtag(haxorg_AstTrackingGroupTrackedHashtag* obj) { org::bind::c::execute_destroy<org::AstTrackingGroup::TrackedHashtag>(obj); }

void haxorg_destroy_AstTrackingGroup(haxorg_AstTrackingGroup* obj) { org::bind::c::execute_destroy<org::AstTrackingGroup>(obj); }

void haxorg_destroy_AstTrackingMap(haxorg_AstTrackingMap* obj) { org::bind::c::execute_destroy<org::AstTrackingMap>(obj); }

void haxorg_destroy_SequenceSegment(haxorg_SequenceSegment* obj) { org::bind::c::execute_destroy<hstd::SequenceSegment>(obj); }

void haxorg_destroy_SequenceSegmentGroup(haxorg_SequenceSegmentGroup* obj) { org::bind::c::execute_destroy<hstd::SequenceSegmentGroup>(obj); }

void haxorg_destroy_SequenceAnnotationTag(haxorg_SequenceAnnotationTag* obj) { org::bind::c::execute_destroy<hstd::SequenceAnnotationTag>(obj); }

void haxorg_destroy_SequenceAnnotation(haxorg_SequenceAnnotation* obj) { org::bind::c::execute_destroy<hstd::SequenceAnnotation>(obj); }

void haxorg_destroy_GraphMapLinkLink(haxorg_GraphMapLinkLink* obj) { org::bind::c::execute_destroy<org::graph::MapLink::Link>(obj); }

void haxorg_destroy_GraphMapLinkRadio(haxorg_GraphMapLinkRadio* obj) { org::bind::c::execute_destroy<org::graph::MapLink::Radio>(obj); }

void haxorg_destroy_GraphMapLink(haxorg_GraphMapLink* obj) { org::bind::c::execute_destroy<org::graph::MapLink>(obj); }

void haxorg_destroy_GraphMapNodeProp(haxorg_GraphMapNodeProp* obj) { org::bind::c::execute_destroy<org::graph::MapNodeProp>(obj); }

void haxorg_destroy_GraphMapEdgeProp(haxorg_GraphMapEdgeProp* obj) { org::bind::c::execute_destroy<org::graph::MapEdgeProp>(obj); }

void haxorg_destroy_GraphMapNode(haxorg_GraphMapNode* obj) { org::bind::c::execute_destroy<org::graph::MapNode>(obj); }

void haxorg_destroy_GraphMapEdge(haxorg_GraphMapEdge* obj) { org::bind::c::execute_destroy<org::graph::MapEdge>(obj); }

void haxorg_destroy_GraphMapGraph(haxorg_GraphMapGraph* obj) { org::bind::c::execute_destroy<org::graph::MapGraph>(obj); }

void haxorg_destroy_GraphMapConfig(haxorg_GraphMapConfig* obj) { org::bind::c::execute_destroy<org::graph::MapConfig>(obj); }

void haxorg_destroy_GraphMapGraphState(haxorg_GraphMapGraphState* obj) { org::bind::c::execute_destroy<org::graph::MapGraphState>(obj); }

void haxorg_create_LispCode_LispCode(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::LispCode { return org::sem::LispCode(); }, org_context); }

void haxorg_create_LispCodeCall_Call(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::LispCode::Call { return org::sem::LispCode::Call(); }, org_context); }

void haxorg_destroy_LispCodeCall(haxorg_LispCodeCall* obj) { org::bind::c::execute_destroy<org::sem::LispCode::Call>(obj); }

void haxorg_create_LispCodeList_List(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::LispCode::List { return org::sem::LispCode::List(); }, org_context); }

void haxorg_destroy_LispCodeList(haxorg_LispCodeList* obj) { org::bind::c::execute_destroy<org::sem::LispCode::List>(obj); }

void haxorg_create_LispCodeKeyValue_KeyValue(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::LispCode::KeyValue { return org::sem::LispCode::KeyValue(); }, org_context); }

void haxorg_destroy_LispCodeKeyValue(haxorg_LispCodeKeyValue* obj) { org::bind::c::execute_destroy<org::sem::LispCode::KeyValue>(obj); }

void haxorg_create_LispCodeNumber_Number(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::LispCode::Number { return org::sem::LispCode::Number(); }, org_context); }

void haxorg_destroy_LispCodeNumber(haxorg_LispCodeNumber* obj) { org::bind::c::execute_destroy<org::sem::LispCode::Number>(obj); }

void haxorg_create_LispCodeText_Text(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::LispCode::Text { return org::sem::LispCode::Text(); }, org_context); }

void haxorg_destroy_LispCodeText(haxorg_LispCodeText* obj) { org::bind::c::execute_destroy<org::sem::LispCode::Text>(obj); }

void haxorg_create_LispCodeIdent_Ident(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::LispCode::Ident { return org::sem::LispCode::Ident(); }, org_context); }

void haxorg_destroy_LispCodeIdent(haxorg_LispCodeIdent* obj) { org::bind::c::execute_destroy<org::sem::LispCode::Ident>(obj); }

void haxorg_create_LispCodeBoolean_Boolean(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::LispCode::Boolean { return org::sem::LispCode::Boolean(); }, org_context); }

void haxorg_destroy_LispCodeBoolean(haxorg_LispCodeBoolean* obj) { org::bind::c::execute_destroy<org::sem::LispCode::Boolean>(obj); }

void haxorg_create_LispCodeReal_Real(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::LispCode::Real { return org::sem::LispCode::Real(); }, org_context); }

void haxorg_destroy_LispCodeReal(haxorg_LispCodeReal* obj) { org::bind::c::execute_destroy<org::sem::LispCode::Real>(obj); }

void haxorg_destroy_LispCode(haxorg_LispCode* obj) { org::bind::c::execute_destroy<org::sem::LispCode>(obj); }

void haxorg_create_TblfmExprAxisRefPosition_Position(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::Tblfm::Expr::AxisRef::Position { return org::sem::Tblfm::Expr::AxisRef::Position(); }, org_context); }

void haxorg_create_TblfmExprAxisRefPositionIndex_Index(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::Tblfm::Expr::AxisRef::Position::Index { return org::sem::Tblfm::Expr::AxisRef::Position::Index(); }, org_context); }

void haxorg_destroy_TblfmExprAxisRefPositionIndex(haxorg_TblfmExprAxisRefPositionIndex* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::AxisRef::Position::Index>(obj); }

void haxorg_create_TblfmExprAxisRefPositionName_Name(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::Tblfm::Expr::AxisRef::Position::Name { return org::sem::Tblfm::Expr::AxisRef::Position::Name(); }, org_context); }

void haxorg_destroy_TblfmExprAxisRefPositionName(haxorg_TblfmExprAxisRefPositionName* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::AxisRef::Position::Name>(obj); }

void haxorg_destroy_TblfmExprAxisRefPosition(haxorg_TblfmExprAxisRefPosition* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::AxisRef::Position>(obj); }

void haxorg_destroy_TblfmExprAxisRef(haxorg_TblfmExprAxisRef* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::AxisRef>(obj); }

void haxorg_destroy_TblfmExprAxisName(haxorg_TblfmExprAxisName* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::AxisName>(obj); }

void haxorg_destroy_TblfmExprIntLiteral(haxorg_TblfmExprIntLiteral* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::IntLiteral>(obj); }

void haxorg_destroy_TblfmExprFloatLiteral(haxorg_TblfmExprFloatLiteral* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::FloatLiteral>(obj); }

void haxorg_destroy_TblfmExprRangeRef(haxorg_TblfmExprRangeRef* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::RangeRef>(obj); }

void haxorg_destroy_TblfmExprCall(haxorg_TblfmExprCall* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::Call>(obj); }

void haxorg_destroy_TblfmExprElisp(haxorg_TblfmExprElisp* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::Elisp>(obj); }

void haxorg_destroy_TblfmExpr(haxorg_TblfmExpr* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr>(obj); }

void haxorg_destroy_TblfmAssign(haxorg_TblfmAssign* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Assign>(obj); }

void haxorg_destroy_Tblfm(haxorg_Tblfm* obj) { org::bind::c::execute_destroy<org::sem::Tblfm>(obj); }

void haxorg_create_AttrValue_AttrValue(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::AttrValue { return org::sem::AttrValue(); }, org_context); }

void haxorg_create_AttrValueDimensionSpan_DimensionSpan(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::AttrValue::DimensionSpan { return org::sem::AttrValue::DimensionSpan(); }, org_context); }

void haxorg_destroy_AttrValueDimensionSpan(haxorg_AttrValueDimensionSpan* obj) { org::bind::c::execute_destroy<org::sem::AttrValue::DimensionSpan>(obj); }

void haxorg_create_AttrValueTextValue_TextValue(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::AttrValue::TextValue { return org::sem::AttrValue::TextValue(); }, org_context); }

void haxorg_destroy_AttrValueTextValue(haxorg_AttrValueTextValue* obj) { org::bind::c::execute_destroy<org::sem::AttrValue::TextValue>(obj); }

void haxorg_create_AttrValueFileReference_FileReference(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::AttrValue::FileReference { return org::sem::AttrValue::FileReference(); }, org_context); }

void haxorg_destroy_AttrValueFileReference(haxorg_AttrValueFileReference* obj) { org::bind::c::execute_destroy<org::sem::AttrValue::FileReference>(obj); }

void haxorg_create_AttrValueLispValue_LispValue(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::AttrValue::LispValue { return org::sem::AttrValue::LispValue(); }, org_context); }

void haxorg_destroy_AttrValueLispValue(haxorg_AttrValueLispValue* obj) { org::bind::c::execute_destroy<org::sem::AttrValue::LispValue>(obj); }

void haxorg_destroy_AttrValue(haxorg_AttrValue* obj) { org::bind::c::execute_destroy<org::sem::AttrValue>(obj); }

void haxorg_destroy_HashTagFlat(haxorg_HashTagFlat* obj) { org::bind::c::execute_destroy<org::sem::HashTagFlat>(obj); }

void haxorg_destroy_TodoKeyword(haxorg_TodoKeyword* obj) { org::bind::c::execute_destroy<org::sem::TodoKeyword>(obj); }

void haxorg_destroy_HashTagText(haxorg_HashTagText* obj) { org::bind::c::execute_destroy<org::sem::HashTagText>(obj); }

void haxorg_destroy_SubtreePath(haxorg_SubtreePath* obj) { org::bind::c::execute_destroy<org::sem::SubtreePath>(obj); }

void haxorg_destroy_LinkTargetRaw(haxorg_LinkTargetRaw* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::Raw>(obj); }

void haxorg_destroy_LinkTargetId(haxorg_LinkTargetId* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::Id>(obj); }

void haxorg_destroy_LinkTargetCustomId(haxorg_LinkTargetCustomId* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::CustomId>(obj); }

void haxorg_destroy_LinkTargetSubtreeTitle(haxorg_LinkTargetSubtreeTitle* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::SubtreeTitle>(obj); }

void haxorg_destroy_LinkTargetPerson(haxorg_LinkTargetPerson* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::Person>(obj); }

void haxorg_destroy_LinkTargetUserProtocol(haxorg_LinkTargetUserProtocol* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::UserProtocol>(obj); }

void haxorg_destroy_LinkTargetInternal(haxorg_LinkTargetInternal* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::Internal>(obj); }

void haxorg_destroy_LinkTargetFootnote(haxorg_LinkTargetFootnote* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::Footnote>(obj); }

void haxorg_destroy_LinkTargetFile(haxorg_LinkTargetFile* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::File>(obj); }

void haxorg_destroy_LinkTargetAttachment(haxorg_LinkTargetAttachment* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::Attachment>(obj); }

void haxorg_destroy_LinkTarget(haxorg_LinkTarget* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget>(obj); }

void haxorg_destroy_SubtreeLogHeadPriority(haxorg_SubtreeLogHeadPriority* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Priority>(obj); }

void haxorg_destroy_SubtreeLogHeadNote(haxorg_SubtreeLogHeadNote* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Note>(obj); }

void haxorg_destroy_SubtreeLogHeadRefile(haxorg_SubtreeLogHeadRefile* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Refile>(obj); }

void haxorg_destroy_SubtreeLogHeadClock(haxorg_SubtreeLogHeadClock* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Clock>(obj); }

void haxorg_destroy_SubtreeLogHeadState(haxorg_SubtreeLogHeadState* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::State>(obj); }

void haxorg_destroy_SubtreeLogHeadDeadline(haxorg_SubtreeLogHeadDeadline* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Deadline>(obj); }

void haxorg_destroy_SubtreeLogHeadSchedule(haxorg_SubtreeLogHeadSchedule* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Schedule>(obj); }

void haxorg_destroy_SubtreeLogHeadTag(haxorg_SubtreeLogHeadTag* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Tag>(obj); }

void haxorg_destroy_SubtreeLogHeadUnknown(haxorg_SubtreeLogHeadUnknown* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Unknown>(obj); }

void haxorg_destroy_SubtreeLogHead(haxorg_SubtreeLogHead* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead>(obj); }

void haxorg_destroy_SubtreeCompletion(haxorg_SubtreeCompletion* obj) { org::bind::c::execute_destroy<org::sem::SubtreeCompletion>(obj); }

void haxorg_destroy_AttrList(haxorg_AttrList* obj) { org::bind::c::execute_destroy<org::sem::AttrList>(obj); }

void haxorg_destroy_AttrGroup(haxorg_AttrGroup* obj) { org::bind::c::execute_destroy<org::sem::AttrGroup>(obj); }

void haxorg_create_OrgCodeEvalInputVar_Var(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::OrgCodeEvalInput::Var { return org::sem::OrgCodeEvalInput::Var(); }, org_context); }

void haxorg_destroy_OrgCodeEvalInputVar(haxorg_OrgCodeEvalInputVar* obj) { org::bind::c::execute_destroy<org::sem::OrgCodeEvalInput::Var>(obj); }

void haxorg_destroy_OrgCodeEvalInput(haxorg_OrgCodeEvalInput* obj) { org::bind::c::execute_destroy<org::sem::OrgCodeEvalInput>(obj); }

void haxorg_destroy_OrgCodeEvalOutput(haxorg_OrgCodeEvalOutput* obj) { org::bind::c::execute_destroy<org::sem::OrgCodeEvalOutput>(obj); }

void haxorg_destroy_ColumnViewSummaryCheckboxAggregate(haxorg_ColumnViewSummaryCheckboxAggregate* obj) { org::bind::c::execute_destroy<org::sem::ColumnView::Summary::CheckboxAggregate>(obj); }

void haxorg_destroy_ColumnViewSummaryMathAggregate(haxorg_ColumnViewSummaryMathAggregate* obj) { org::bind::c::execute_destroy<org::sem::ColumnView::Summary::MathAggregate>(obj); }

void haxorg_destroy_ColumnViewSummary(haxorg_ColumnViewSummary* obj) { org::bind::c::execute_destroy<org::sem::ColumnView::Summary>(obj); }

void haxorg_destroy_ColumnViewColumn(haxorg_ColumnViewColumn* obj) { org::bind::c::execute_destroy<org::sem::ColumnView::Column>(obj); }

void haxorg_destroy_ColumnView(haxorg_ColumnView* obj) { org::bind::c::execute_destroy<org::sem::ColumnView>(obj); }

void haxorg_destroy_BlockCodeLinePartRaw(haxorg_BlockCodeLinePartRaw* obj) { org::bind::c::execute_destroy<org::sem::BlockCodeLine::Part::Raw>(obj); }

void haxorg_destroy_BlockCodeLinePartCallout(haxorg_BlockCodeLinePartCallout* obj) { org::bind::c::execute_destroy<org::sem::BlockCodeLine::Part::Callout>(obj); }

void haxorg_destroy_BlockCodeLinePartTangle(haxorg_BlockCodeLinePartTangle* obj) { org::bind::c::execute_destroy<org::sem::BlockCodeLine::Part::Tangle>(obj); }

void haxorg_destroy_BlockCodeLinePart(haxorg_BlockCodeLinePart* obj) { org::bind::c::execute_destroy<org::sem::BlockCodeLine::Part>(obj); }

void haxorg_destroy_BlockCodeLine(haxorg_BlockCodeLine* obj) { org::bind::c::execute_destroy<org::sem::BlockCodeLine>(obj); }

void haxorg_destroy_DocumentExportConfigTaskExport(haxorg_DocumentExportConfigTaskExport* obj) { org::bind::c::execute_destroy<org::sem::DocumentExportConfig::TaskExport>(obj); }

void haxorg_destroy_DocumentExportConfigDoExport(haxorg_DocumentExportConfigDoExport* obj) { org::bind::c::execute_destroy<org::sem::DocumentExportConfig::DoExport>(obj); }

void haxorg_destroy_DocumentExportConfigExportFixed(haxorg_DocumentExportConfigExportFixed* obj) { org::bind::c::execute_destroy<org::sem::DocumentExportConfig::ExportFixed>(obj); }

void haxorg_destroy_DocumentExportConfig(haxorg_DocumentExportConfig* obj) { org::bind::c::execute_destroy<org::sem::DocumentExportConfig>(obj); }

void haxorg_destroy_SubtreePeriod(haxorg_SubtreePeriod* obj) { org::bind::c::execute_destroy<org::sem::SubtreePeriod>(obj); }

void haxorg_destroy_NamedPropertyNonblocking(haxorg_NamedPropertyNonblocking* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Nonblocking>(obj); }

void haxorg_destroy_NamedPropertyArchiveTime(haxorg_NamedPropertyArchiveTime* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ArchiveTime>(obj); }

void haxorg_destroy_NamedPropertyArchiveFile(haxorg_NamedPropertyArchiveFile* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ArchiveFile>(obj); }

void haxorg_destroy_NamedPropertyArchiveOlpath(haxorg_NamedPropertyArchiveOlpath* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ArchiveOlpath>(obj); }

void haxorg_destroy_NamedPropertyArchiveTarget(haxorg_NamedPropertyArchiveTarget* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ArchiveTarget>(obj); }

void haxorg_destroy_NamedPropertyArchiveCategory(haxorg_NamedPropertyArchiveCategory* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ArchiveCategory>(obj); }

void haxorg_destroy_NamedPropertyArchiveTodo(haxorg_NamedPropertyArchiveTodo* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ArchiveTodo>(obj); }

void haxorg_destroy_NamedPropertyTrigger(haxorg_NamedPropertyTrigger* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Trigger>(obj); }

void haxorg_destroy_NamedPropertyExportLatexClass(haxorg_NamedPropertyExportLatexClass* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ExportLatexClass>(obj); }

void haxorg_destroy_NamedPropertyCookieData(haxorg_NamedPropertyCookieData* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::CookieData>(obj); }

void haxorg_destroy_NamedPropertyExportLatexClassOptions(haxorg_NamedPropertyExportLatexClassOptions* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ExportLatexClassOptions>(obj); }

void haxorg_destroy_NamedPropertyExportLatexHeader(haxorg_NamedPropertyExportLatexHeader* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ExportLatexHeader>(obj); }

void haxorg_destroy_NamedPropertyExportLatexCompiler(haxorg_NamedPropertyExportLatexCompiler* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ExportLatexCompiler>(obj); }

void haxorg_destroy_NamedPropertyOrdered(haxorg_NamedPropertyOrdered* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Ordered>(obj); }

void haxorg_destroy_NamedPropertyEffort(haxorg_NamedPropertyEffort* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Effort>(obj); }

void haxorg_destroy_NamedPropertyVisibility(haxorg_NamedPropertyVisibility* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Visibility>(obj); }

void haxorg_destroy_NamedPropertyExportOptions(haxorg_NamedPropertyExportOptions* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ExportOptions>(obj); }

void haxorg_destroy_NamedPropertyBlocker(haxorg_NamedPropertyBlocker* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Blocker>(obj); }

void haxorg_destroy_NamedPropertyUnnumbered(haxorg_NamedPropertyUnnumbered* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Unnumbered>(obj); }

void haxorg_destroy_NamedPropertyCreated(haxorg_NamedPropertyCreated* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Created>(obj); }

void haxorg_destroy_NamedPropertyRadioId(haxorg_NamedPropertyRadioId* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::RadioId>(obj); }

void haxorg_destroy_NamedPropertyHashtagDef(haxorg_NamedPropertyHashtagDef* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::HashtagDef>(obj); }

void haxorg_destroy_NamedPropertyCustomArgs(haxorg_NamedPropertyCustomArgs* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::CustomArgs>(obj); }

void haxorg_destroy_NamedPropertyCustomRaw(haxorg_NamedPropertyCustomRaw* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::CustomRaw>(obj); }

void haxorg_destroy_NamedPropertyCustomId(haxorg_NamedPropertyCustomId* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::CustomId>(obj); }

void haxorg_destroy_NamedPropertyCustomSubtreeJson(haxorg_NamedPropertyCustomSubtreeJson* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::CustomSubtreeJson>(obj); }

void haxorg_destroy_NamedPropertyCustomSubtreeFlags(haxorg_NamedPropertyCustomSubtreeFlags* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::CustomSubtreeFlags>(obj); }

void haxorg_destroy_NamedProperty(haxorg_NamedProperty* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty>(obj); }

void haxorg_destroy_OrgDiagnosticsParseTokenError(haxorg_OrgDiagnosticsParseTokenError* obj) { org::bind::c::execute_destroy<org::sem::OrgDiagnostics::ParseTokenError>(obj); }

void haxorg_destroy_OrgDiagnosticsParseError(haxorg_OrgDiagnosticsParseError* obj) { org::bind::c::execute_destroy<org::sem::OrgDiagnostics::ParseError>(obj); }

void haxorg_destroy_OrgDiagnosticsIncludeError(haxorg_OrgDiagnosticsIncludeError* obj) { org::bind::c::execute_destroy<org::sem::OrgDiagnostics::IncludeError>(obj); }

void haxorg_destroy_OrgDiagnosticsConvertError(haxorg_OrgDiagnosticsConvertError* obj) { org::bind::c::execute_destroy<org::sem::OrgDiagnostics::ConvertError>(obj); }

void haxorg_destroy_OrgDiagnosticsInternalError(haxorg_OrgDiagnosticsInternalError* obj) { org::bind::c::execute_destroy<org::sem::OrgDiagnostics::InternalError>(obj); }

void haxorg_destroy_OrgDiagnostics(haxorg_OrgDiagnostics* obj) { org::bind::c::execute_destroy<org::sem::OrgDiagnostics>(obj); }

void haxorg_destroy_NoNode(haxorg_NoNode* obj) { org::bind::c::execute_destroy<org::sem::NoNode>(obj); }

void haxorg_destroy_ErrorItem(haxorg_ErrorItem* obj) { org::bind::c::execute_destroy<org::sem::ErrorItem>(obj); }

void haxorg_destroy_ErrorGroup(haxorg_ErrorGroup* obj) { org::bind::c::execute_destroy<org::sem::ErrorGroup>(obj); }

void haxorg_destroy_Stmt(haxorg_Stmt* obj) { org::bind::c::execute_destroy<org::sem::Stmt>(obj); }

void haxorg_destroy_Inline(haxorg_Inline* obj) { org::bind::c::execute_destroy<org::sem::Inline>(obj); }

void haxorg_destroy_StmtList(haxorg_StmtList* obj) { org::bind::c::execute_destroy<org::sem::StmtList>(obj); }

void haxorg_destroy_Empty(haxorg_Empty* obj) { org::bind::c::execute_destroy<org::sem::Empty>(obj); }

void haxorg_destroy_Leaf(haxorg_Leaf* obj) { org::bind::c::execute_destroy<org::sem::Leaf>(obj); }

void haxorg_destroy_TimeRepeat(haxorg_TimeRepeat* obj) { org::bind::c::execute_destroy<org::sem::Time::Repeat>(obj); }

void haxorg_create_TimeStatic_Static(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::Time::Static { return org::sem::Time::Static(); }, org_context); }

void haxorg_destroy_TimeStatic(haxorg_TimeStatic* obj) { org::bind::c::execute_destroy<org::sem::Time::Static>(obj); }

void haxorg_create_TimeDynamic_Dynamic(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::Time::Dynamic { return org::sem::Time::Dynamic(); }, org_context); }

void haxorg_destroy_TimeDynamic(haxorg_TimeDynamic* obj) { org::bind::c::execute_destroy<org::sem::Time::Dynamic>(obj); }

void haxorg_destroy_Time(haxorg_Time* obj) { org::bind::c::execute_destroy<org::sem::Time>(obj); }

void haxorg_destroy_TimeRange(haxorg_TimeRange* obj) { org::bind::c::execute_destroy<org::sem::TimeRange>(obj); }

void haxorg_destroy_Macro(haxorg_Macro* obj) { org::bind::c::execute_destroy<org::sem::Macro>(obj); }

void haxorg_destroy_SymbolParam(haxorg_SymbolParam* obj) { org::bind::c::execute_destroy<org::sem::Symbol::Param>(obj); }

void haxorg_destroy_Symbol(haxorg_Symbol* obj) { org::bind::c::execute_destroy<org::sem::Symbol>(obj); }

void haxorg_destroy_ErrorSkipGroup(haxorg_ErrorSkipGroup* obj) { org::bind::c::execute_destroy<org::sem::ErrorSkipGroup>(obj); }

void haxorg_destroy_Markup(haxorg_Markup* obj) { org::bind::c::execute_destroy<org::sem::Markup>(obj); }

void haxorg_destroy_RadioTarget(haxorg_RadioTarget* obj) { org::bind::c::execute_destroy<org::sem::RadioTarget>(obj); }

void haxorg_destroy_Latex(haxorg_Latex* obj) { org::bind::c::execute_destroy<org::sem::Latex>(obj); }

void haxorg_destroy_SubtreeLog(haxorg_SubtreeLog* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLog>(obj); }

void haxorg_destroy_Subtree(haxorg_Subtree* obj) { org::bind::c::execute_destroy<org::sem::Subtree>(obj); }

void haxorg_destroy_ColonExample(haxorg_ColonExample* obj) { org::bind::c::execute_destroy<org::sem::ColonExample>(obj); }

void haxorg_destroy_Call(haxorg_Call* obj) { org::bind::c::execute_destroy<org::sem::Call>(obj); }

void haxorg_destroy_ListItem(haxorg_ListItem* obj) { org::bind::c::execute_destroy<org::sem::ListItem>(obj); }

void haxorg_destroy_DocumentOptions(haxorg_DocumentOptions* obj) { org::bind::c::execute_destroy<org::sem::DocumentOptions>(obj); }

void haxorg_destroy_DocumentFragment(haxorg_DocumentFragment* obj) { org::bind::c::execute_destroy<org::sem::DocumentFragment>(obj); }

void haxorg_destroy_CriticMarkup(haxorg_CriticMarkup* obj) { org::bind::c::execute_destroy<org::sem::CriticMarkup>(obj); }

void haxorg_destroy_Document(haxorg_Document* obj) { org::bind::c::execute_destroy<org::sem::Document>(obj); }

void haxorg_destroy_FileTarget(haxorg_FileTarget* obj) { org::bind::c::execute_destroy<org::sem::FileTarget>(obj); }

void haxorg_destroy_TextSeparator(haxorg_TextSeparator* obj) { org::bind::c::execute_destroy<org::sem::TextSeparator>(obj); }

void haxorg_destroy_DocumentGroup(haxorg_DocumentGroup* obj) { org::bind::c::execute_destroy<org::sem::DocumentGroup>(obj); }

void haxorg_destroy_FileDocument(haxorg_FileDocument* obj) { org::bind::c::execute_destroy<org::sem::File::Document>(obj); }

void haxorg_destroy_FileAttachment(haxorg_FileAttachment* obj) { org::bind::c::execute_destroy<org::sem::File::Attachment>(obj); }

void haxorg_destroy_FileSource(haxorg_FileSource* obj) { org::bind::c::execute_destroy<org::sem::File::Source>(obj); }

void haxorg_destroy_File(haxorg_File* obj) { org::bind::c::execute_destroy<org::sem::File>(obj); }

void haxorg_destroy_Directory(haxorg_Directory* obj) { org::bind::c::execute_destroy<org::sem::Directory>(obj); }

void haxorg_destroy_Symlink(haxorg_Symlink* obj) { org::bind::c::execute_destroy<org::sem::Symlink>(obj); }

void haxorg_destroy_CmdIncludeIncludeBase(haxorg_CmdIncludeIncludeBase* obj) { org::bind::c::execute_destroy<org::sem::CmdInclude::IncludeBase>(obj); }

void haxorg_destroy_CmdIncludeExample(haxorg_CmdIncludeExample* obj) { org::bind::c::execute_destroy<org::sem::CmdInclude::Example>(obj); }

void haxorg_destroy_CmdIncludeExport(haxorg_CmdIncludeExport* obj) { org::bind::c::execute_destroy<org::sem::CmdInclude::Export>(obj); }

void haxorg_destroy_CmdIncludeCustom(haxorg_CmdIncludeCustom* obj) { org::bind::c::execute_destroy<org::sem::CmdInclude::Custom>(obj); }

void haxorg_destroy_CmdIncludeSrc(haxorg_CmdIncludeSrc* obj) { org::bind::c::execute_destroy<org::sem::CmdInclude::Src>(obj); }

void haxorg_destroy_CmdIncludeOrgDocument(haxorg_CmdIncludeOrgDocument* obj) { org::bind::c::execute_destroy<org::sem::CmdInclude::OrgDocument>(obj); }

void haxorg_destroy_CmdInclude(haxorg_CmdInclude* obj) { org::bind::c::execute_destroy<org::sem::CmdInclude>(obj); }

void haxorg_destroy_ImmNoNode(haxorg_ImmNoNode* obj) { org::bind::c::execute_destroy<org::imm::ImmNoNode>(obj); }

void haxorg_destroy_ImmErrorItem(haxorg_ImmErrorItem* obj) { org::bind::c::execute_destroy<org::imm::ImmErrorItem>(obj); }

void haxorg_destroy_ImmErrorGroup(haxorg_ImmErrorGroup* obj) { org::bind::c::execute_destroy<org::imm::ImmErrorGroup>(obj); }

void haxorg_destroy_ImmStmt(haxorg_ImmStmt* obj) { org::bind::c::execute_destroy<org::imm::ImmStmt>(obj); }

void haxorg_destroy_ImmInline(haxorg_ImmInline* obj) { org::bind::c::execute_destroy<org::imm::ImmInline>(obj); }

void haxorg_destroy_ImmStmtList(haxorg_ImmStmtList* obj) { org::bind::c::execute_destroy<org::imm::ImmStmtList>(obj); }

void haxorg_destroy_ImmEmpty(haxorg_ImmEmpty* obj) { org::bind::c::execute_destroy<org::imm::ImmEmpty>(obj); }

void haxorg_destroy_ImmLeaf(haxorg_ImmLeaf* obj) { org::bind::c::execute_destroy<org::imm::ImmLeaf>(obj); }

void haxorg_destroy_ImmTimeRepeat(haxorg_ImmTimeRepeat* obj) { org::bind::c::execute_destroy<org::imm::ImmTime::Repeat>(obj); }

void haxorg_create_ImmTimeStatic_Static(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::imm::ImmTime::Static { return org::imm::ImmTime::Static(); }, org_context); }

void haxorg_destroy_ImmTimeStatic(haxorg_ImmTimeStatic* obj) { org::bind::c::execute_destroy<org::imm::ImmTime::Static>(obj); }

void haxorg_create_ImmTimeDynamic_Dynamic(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::imm::ImmTime::Dynamic { return org::imm::ImmTime::Dynamic(); }, org_context); }

void haxorg_destroy_ImmTimeDynamic(haxorg_ImmTimeDynamic* obj) { org::bind::c::execute_destroy<org::imm::ImmTime::Dynamic>(obj); }

void haxorg_destroy_ImmTime(haxorg_ImmTime* obj) { org::bind::c::execute_destroy<org::imm::ImmTime>(obj); }

void haxorg_destroy_ImmTimeRange(haxorg_ImmTimeRange* obj) { org::bind::c::execute_destroy<org::imm::ImmTimeRange>(obj); }

void haxorg_destroy_ImmMacro(haxorg_ImmMacro* obj) { org::bind::c::execute_destroy<org::imm::ImmMacro>(obj); }

void haxorg_destroy_ImmSymbolParam(haxorg_ImmSymbolParam* obj) { org::bind::c::execute_destroy<org::imm::ImmSymbol::Param>(obj); }

void haxorg_destroy_ImmSymbol(haxorg_ImmSymbol* obj) { org::bind::c::execute_destroy<org::imm::ImmSymbol>(obj); }

void haxorg_destroy_ImmErrorSkipGroup(haxorg_ImmErrorSkipGroup* obj) { org::bind::c::execute_destroy<org::imm::ImmErrorSkipGroup>(obj); }

void haxorg_destroy_ImmMarkup(haxorg_ImmMarkup* obj) { org::bind::c::execute_destroy<org::imm::ImmMarkup>(obj); }

void haxorg_destroy_ImmRadioTarget(haxorg_ImmRadioTarget* obj) { org::bind::c::execute_destroy<org::imm::ImmRadioTarget>(obj); }

void haxorg_destroy_ImmLatex(haxorg_ImmLatex* obj) { org::bind::c::execute_destroy<org::imm::ImmLatex>(obj); }

void haxorg_destroy_ImmSubtreeLog(haxorg_ImmSubtreeLog* obj) { org::bind::c::execute_destroy<org::imm::ImmSubtreeLog>(obj); }

void haxorg_destroy_ImmSubtree(haxorg_ImmSubtree* obj) { org::bind::c::execute_destroy<org::imm::ImmSubtree>(obj); }

void haxorg_destroy_ImmColonExample(haxorg_ImmColonExample* obj) { org::bind::c::execute_destroy<org::imm::ImmColonExample>(obj); }

void haxorg_destroy_ImmCall(haxorg_ImmCall* obj) { org::bind::c::execute_destroy<org::imm::ImmCall>(obj); }

void haxorg_destroy_ImmListItem(haxorg_ImmListItem* obj) { org::bind::c::execute_destroy<org::imm::ImmListItem>(obj); }

void haxorg_destroy_ImmDocumentOptions(haxorg_ImmDocumentOptions* obj) { org::bind::c::execute_destroy<org::imm::ImmDocumentOptions>(obj); }

void haxorg_destroy_ImmDocumentFragment(haxorg_ImmDocumentFragment* obj) { org::bind::c::execute_destroy<org::imm::ImmDocumentFragment>(obj); }

void haxorg_destroy_ImmCriticMarkup(haxorg_ImmCriticMarkup* obj) { org::bind::c::execute_destroy<org::imm::ImmCriticMarkup>(obj); }

void haxorg_destroy_ImmDocument(haxorg_ImmDocument* obj) { org::bind::c::execute_destroy<org::imm::ImmDocument>(obj); }

void haxorg_destroy_ImmFileTarget(haxorg_ImmFileTarget* obj) { org::bind::c::execute_destroy<org::imm::ImmFileTarget>(obj); }

void haxorg_destroy_ImmTextSeparator(haxorg_ImmTextSeparator* obj) { org::bind::c::execute_destroy<org::imm::ImmTextSeparator>(obj); }

void haxorg_destroy_ImmDocumentGroup(haxorg_ImmDocumentGroup* obj) { org::bind::c::execute_destroy<org::imm::ImmDocumentGroup>(obj); }

void haxorg_destroy_ImmFileDocument(haxorg_ImmFileDocument* obj) { org::bind::c::execute_destroy<org::imm::ImmFile::Document>(obj); }

void haxorg_destroy_ImmFileAttachment(haxorg_ImmFileAttachment* obj) { org::bind::c::execute_destroy<org::imm::ImmFile::Attachment>(obj); }

void haxorg_destroy_ImmFileSource(haxorg_ImmFileSource* obj) { org::bind::c::execute_destroy<org::imm::ImmFile::Source>(obj); }

void haxorg_destroy_ImmFile(haxorg_ImmFile* obj) { org::bind::c::execute_destroy<org::imm::ImmFile>(obj); }

void haxorg_destroy_ImmDirectory(haxorg_ImmDirectory* obj) { org::bind::c::execute_destroy<org::imm::ImmDirectory>(obj); }

void haxorg_destroy_ImmSymlink(haxorg_ImmSymlink* obj) { org::bind::c::execute_destroy<org::imm::ImmSymlink>(obj); }

void haxorg_destroy_ImmCmdIncludeIncludeBase(haxorg_ImmCmdIncludeIncludeBase* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdInclude::IncludeBase>(obj); }

void haxorg_destroy_ImmCmdIncludeExample(haxorg_ImmCmdIncludeExample* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdInclude::Example>(obj); }

void haxorg_destroy_ImmCmdIncludeExport(haxorg_ImmCmdIncludeExport* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdInclude::Export>(obj); }

void haxorg_destroy_ImmCmdIncludeCustom(haxorg_ImmCmdIncludeCustom* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdInclude::Custom>(obj); }

void haxorg_destroy_ImmCmdIncludeSrc(haxorg_ImmCmdIncludeSrc* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdInclude::Src>(obj); }

void haxorg_destroy_ImmCmdIncludeOrgDocument(haxorg_ImmCmdIncludeOrgDocument* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdInclude::OrgDocument>(obj); }

void haxorg_destroy_ImmCmdInclude(haxorg_ImmCmdInclude* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdInclude>(obj); }

void haxorg_destroy_ImmAdapterOrgAPI(haxorg_ImmAdapterOrgAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterOrgAPI>(obj); }

void haxorg_destroy_Cmd(haxorg_Cmd* obj) { org::bind::c::execute_destroy<org::sem::Cmd>(obj); }

void haxorg_destroy_CmdCustomRaw(haxorg_CmdCustomRaw* obj) { org::bind::c::execute_destroy<org::sem::CmdCustomRaw>(obj); }

void haxorg_destroy_CmdCustomText(haxorg_CmdCustomText* obj) { org::bind::c::execute_destroy<org::sem::CmdCustomText>(obj); }

void haxorg_destroy_Link(haxorg_Link* obj) { org::bind::c::execute_destroy<org::sem::Link>(obj); }

void haxorg_destroy_BlockComment(haxorg_BlockComment* obj) { org::bind::c::execute_destroy<org::sem::BlockComment>(obj); }

void haxorg_destroy_Paragraph(haxorg_Paragraph* obj) { org::bind::c::execute_destroy<org::sem::Paragraph>(obj); }

void haxorg_destroy_List(haxorg_List* obj) { org::bind::c::execute_destroy<org::sem::List>(obj); }

void haxorg_destroy_HashTag(haxorg_HashTag* obj) { org::bind::c::execute_destroy<org::sem::HashTag>(obj); }

void haxorg_destroy_InlineFootnote(haxorg_InlineFootnote* obj) { org::bind::c::execute_destroy<org::sem::InlineFootnote>(obj); }

void haxorg_destroy_InlineExport(haxorg_InlineExport* obj) { org::bind::c::execute_destroy<org::sem::InlineExport>(obj); }

void haxorg_destroy_Escaped(haxorg_Escaped* obj) { org::bind::c::execute_destroy<org::sem::Escaped>(obj); }

void haxorg_destroy_Newline(haxorg_Newline* obj) { org::bind::c::execute_destroy<org::sem::Newline>(obj); }

void haxorg_destroy_Space(haxorg_Space* obj) { org::bind::c::execute_destroy<org::sem::Space>(obj); }

void haxorg_destroy_Word(haxorg_Word* obj) { org::bind::c::execute_destroy<org::sem::Word>(obj); }

void haxorg_destroy_AtMention(haxorg_AtMention* obj) { org::bind::c::execute_destroy<org::sem::AtMention>(obj); }

void haxorg_destroy_RawText(haxorg_RawText* obj) { org::bind::c::execute_destroy<org::sem::RawText>(obj); }

void haxorg_destroy_Punctuation(haxorg_Punctuation* obj) { org::bind::c::execute_destroy<org::sem::Punctuation>(obj); }

void haxorg_destroy_Placeholder(haxorg_Placeholder* obj) { org::bind::c::execute_destroy<org::sem::Placeholder>(obj); }

void haxorg_destroy_BigIdent(haxorg_BigIdent* obj) { org::bind::c::execute_destroy<org::sem::BigIdent>(obj); }

void haxorg_destroy_TextTarget(haxorg_TextTarget* obj) { org::bind::c::execute_destroy<org::sem::TextTarget>(obj); }

void haxorg_destroy_ErrorSkipToken(haxorg_ErrorSkipToken* obj) { org::bind::c::execute_destroy<org::sem::ErrorSkipToken>(obj); }

void haxorg_destroy_Bold(haxorg_Bold* obj) { org::bind::c::execute_destroy<org::sem::Bold>(obj); }

void haxorg_destroy_Underline(haxorg_Underline* obj) { org::bind::c::execute_destroy<org::sem::Underline>(obj); }

void haxorg_destroy_Monospace(haxorg_Monospace* obj) { org::bind::c::execute_destroy<org::sem::Monospace>(obj); }

void haxorg_destroy_MarkQuote(haxorg_MarkQuote* obj) { org::bind::c::execute_destroy<org::sem::MarkQuote>(obj); }

void haxorg_destroy_Verbatim(haxorg_Verbatim* obj) { org::bind::c::execute_destroy<org::sem::Verbatim>(obj); }

void haxorg_destroy_Italic(haxorg_Italic* obj) { org::bind::c::execute_destroy<org::sem::Italic>(obj); }

void haxorg_destroy_Strike(haxorg_Strike* obj) { org::bind::c::execute_destroy<org::sem::Strike>(obj); }

void haxorg_destroy_Par(haxorg_Par* obj) { org::bind::c::execute_destroy<org::sem::Par>(obj); }

void haxorg_destroy_ImmCmd(haxorg_ImmCmd* obj) { org::bind::c::execute_destroy<org::imm::ImmCmd>(obj); }

void haxorg_destroy_ImmCmdCustomRaw(haxorg_ImmCmdCustomRaw* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdCustomRaw>(obj); }

void haxorg_destroy_ImmCmdCustomText(haxorg_ImmCmdCustomText* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdCustomText>(obj); }

void haxorg_destroy_ImmLink(haxorg_ImmLink* obj) { org::bind::c::execute_destroy<org::imm::ImmLink>(obj); }

void haxorg_destroy_ImmBlockComment(haxorg_ImmBlockComment* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockComment>(obj); }

void haxorg_destroy_ImmParagraph(haxorg_ImmParagraph* obj) { org::bind::c::execute_destroy<org::imm::ImmParagraph>(obj); }

void haxorg_destroy_ImmList(haxorg_ImmList* obj) { org::bind::c::execute_destroy<org::imm::ImmList>(obj); }

void haxorg_destroy_ImmHashTag(haxorg_ImmHashTag* obj) { org::bind::c::execute_destroy<org::imm::ImmHashTag>(obj); }

void haxorg_destroy_ImmInlineFootnote(haxorg_ImmInlineFootnote* obj) { org::bind::c::execute_destroy<org::imm::ImmInlineFootnote>(obj); }

void haxorg_destroy_ImmInlineExport(haxorg_ImmInlineExport* obj) { org::bind::c::execute_destroy<org::imm::ImmInlineExport>(obj); }

void haxorg_destroy_ImmEscaped(haxorg_ImmEscaped* obj) { org::bind::c::execute_destroy<org::imm::ImmEscaped>(obj); }

void haxorg_destroy_ImmNewline(haxorg_ImmNewline* obj) { org::bind::c::execute_destroy<org::imm::ImmNewline>(obj); }

void haxorg_destroy_ImmSpace(haxorg_ImmSpace* obj) { org::bind::c::execute_destroy<org::imm::ImmSpace>(obj); }

void haxorg_destroy_ImmWord(haxorg_ImmWord* obj) { org::bind::c::execute_destroy<org::imm::ImmWord>(obj); }

void haxorg_destroy_ImmAtMention(haxorg_ImmAtMention* obj) { org::bind::c::execute_destroy<org::imm::ImmAtMention>(obj); }

void haxorg_destroy_ImmRawText(haxorg_ImmRawText* obj) { org::bind::c::execute_destroy<org::imm::ImmRawText>(obj); }

void haxorg_destroy_ImmPunctuation(haxorg_ImmPunctuation* obj) { org::bind::c::execute_destroy<org::imm::ImmPunctuation>(obj); }

void haxorg_destroy_ImmPlaceholder(haxorg_ImmPlaceholder* obj) { org::bind::c::execute_destroy<org::imm::ImmPlaceholder>(obj); }

void haxorg_destroy_ImmBigIdent(haxorg_ImmBigIdent* obj) { org::bind::c::execute_destroy<org::imm::ImmBigIdent>(obj); }

void haxorg_destroy_ImmTextTarget(haxorg_ImmTextTarget* obj) { org::bind::c::execute_destroy<org::imm::ImmTextTarget>(obj); }

void haxorg_destroy_ImmErrorSkipToken(haxorg_ImmErrorSkipToken* obj) { org::bind::c::execute_destroy<org::imm::ImmErrorSkipToken>(obj); }

void haxorg_destroy_ImmBold(haxorg_ImmBold* obj) { org::bind::c::execute_destroy<org::imm::ImmBold>(obj); }

void haxorg_destroy_ImmUnderline(haxorg_ImmUnderline* obj) { org::bind::c::execute_destroy<org::imm::ImmUnderline>(obj); }

void haxorg_destroy_ImmMonospace(haxorg_ImmMonospace* obj) { org::bind::c::execute_destroy<org::imm::ImmMonospace>(obj); }

void haxorg_destroy_ImmMarkQuote(haxorg_ImmMarkQuote* obj) { org::bind::c::execute_destroy<org::imm::ImmMarkQuote>(obj); }

void haxorg_destroy_ImmVerbatim(haxorg_ImmVerbatim* obj) { org::bind::c::execute_destroy<org::imm::ImmVerbatim>(obj); }

void haxorg_destroy_ImmItalic(haxorg_ImmItalic* obj) { org::bind::c::execute_destroy<org::imm::ImmItalic>(obj); }

void haxorg_destroy_ImmStrike(haxorg_ImmStrike* obj) { org::bind::c::execute_destroy<org::imm::ImmStrike>(obj); }

void haxorg_destroy_ImmPar(haxorg_ImmPar* obj) { org::bind::c::execute_destroy<org::imm::ImmPar>(obj); }

void haxorg_destroy_ImmAdapterStmtAPI(haxorg_ImmAdapterStmtAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterStmtAPI>(obj); }

void haxorg_destroy_ImmAdapterSubtreeAPI(haxorg_ImmAdapterSubtreeAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterSubtreeAPI>(obj); }

void haxorg_destroy_ImmAdapterNoNodeAPI(haxorg_ImmAdapterNoNodeAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterNoNodeAPI>(obj); }

void haxorg_destroy_ImmAdapterAttrAPI(haxorg_ImmAdapterAttrAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterAttrAPI>(obj); }

void haxorg_destroy_ImmAdapterAttrListAPI(haxorg_ImmAdapterAttrListAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterAttrListAPI>(obj); }

void haxorg_destroy_ImmAdapterAttrsAPI(haxorg_ImmAdapterAttrsAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterAttrsAPI>(obj); }

void haxorg_destroy_ImmAdapterErrorItemAPI(haxorg_ImmAdapterErrorItemAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterErrorItemAPI>(obj); }

void haxorg_destroy_ImmAdapterErrorGroupAPI(haxorg_ImmAdapterErrorGroupAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterErrorGroupAPI>(obj); }

void haxorg_destroy_ImmAdapterErrorSkipGroupAPI(haxorg_ImmAdapterErrorSkipGroupAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterErrorSkipGroupAPI>(obj); }

void haxorg_destroy_ImmAdapterErrorSkipTokenAPI(haxorg_ImmAdapterErrorSkipTokenAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterErrorSkipTokenAPI>(obj); }

void haxorg_destroy_ImmAdapterStmtListAPI(haxorg_ImmAdapterStmtListAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterStmtListAPI>(obj); }

void haxorg_destroy_ImmAdapterEmptyAPI(haxorg_ImmAdapterEmptyAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterEmptyAPI>(obj); }

void haxorg_destroy_ImmAdapterInlineAPI(haxorg_ImmAdapterInlineAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterInlineAPI>(obj); }

void haxorg_destroy_ImmAdapterTimeAPI(haxorg_ImmAdapterTimeAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterTimeAPI>(obj); }

void haxorg_destroy_ImmAdapterTimeRangeAPI(haxorg_ImmAdapterTimeRangeAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterTimeRangeAPI>(obj); }

void haxorg_destroy_ImmAdapterMacroAPI(haxorg_ImmAdapterMacroAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterMacroAPI>(obj); }

void haxorg_destroy_ImmAdapterSymbolAPI(haxorg_ImmAdapterSymbolAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterSymbolAPI>(obj); }

void haxorg_destroy_ImmAdapterLeafAPI(haxorg_ImmAdapterLeafAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterLeafAPI>(obj); }

void haxorg_destroy_ImmAdapterMarkupAPI(haxorg_ImmAdapterMarkupAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterMarkupAPI>(obj); }

void haxorg_destroy_ImmAdapterLatexAPI(haxorg_ImmAdapterLatexAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterLatexAPI>(obj); }

void haxorg_destroy_ImmAdapterSubtreeLogAPI(haxorg_ImmAdapterSubtreeLogAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterSubtreeLogAPI>(obj); }

void haxorg_destroy_ImmAdapterColonExampleAPI(haxorg_ImmAdapterColonExampleAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterColonExampleAPI>(obj); }

void haxorg_destroy_ImmAdapterCallAPI(haxorg_ImmAdapterCallAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCallAPI>(obj); }

void haxorg_destroy_ImmAdapterFileAPI(haxorg_ImmAdapterFileAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterFileAPI>(obj); }

void haxorg_destroy_ImmAdapterDirectoryAPI(haxorg_ImmAdapterDirectoryAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterDirectoryAPI>(obj); }

void haxorg_destroy_ImmAdapterSymlinkAPI(haxorg_ImmAdapterSymlinkAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterSymlinkAPI>(obj); }

void haxorg_destroy_ImmAdapterDocumentFragmentAPI(haxorg_ImmAdapterDocumentFragmentAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterDocumentFragmentAPI>(obj); }

void haxorg_destroy_ImmAdapterCriticMarkupAPI(haxorg_ImmAdapterCriticMarkupAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCriticMarkupAPI>(obj); }

void haxorg_destroy_ImmAdapterListItemAPI(haxorg_ImmAdapterListItemAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterListItemAPI>(obj); }

void haxorg_destroy_ImmAdapterDocumentOptionsAPI(haxorg_ImmAdapterDocumentOptionsAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterDocumentOptionsAPI>(obj); }

void haxorg_destroy_ImmAdapterDocumentAPI(haxorg_ImmAdapterDocumentAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterDocumentAPI>(obj); }

void haxorg_destroy_ImmAdapterFileTargetAPI(haxorg_ImmAdapterFileTargetAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterFileTargetAPI>(obj); }

void haxorg_destroy_ImmAdapterTextSeparatorAPI(haxorg_ImmAdapterTextSeparatorAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterTextSeparatorAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdIncludeAPI(haxorg_ImmAdapterCmdIncludeAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdIncludeAPI>(obj); }

void haxorg_destroy_ImmAdapterDocumentGroupAPI(haxorg_ImmAdapterDocumentGroupAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterDocumentGroupAPI>(obj); }

void haxorg_destroy_Block(haxorg_Block* obj) { org::bind::c::execute_destroy<org::sem::Block>(obj); }

void haxorg_destroy_LineCommand(haxorg_LineCommand* obj) { org::bind::c::execute_destroy<org::sem::LineCommand>(obj); }

void haxorg_destroy_CmdCreator(haxorg_CmdCreator* obj) { org::bind::c::execute_destroy<org::sem::CmdCreator>(obj); }

void haxorg_destroy_CmdAuthor(haxorg_CmdAuthor* obj) { org::bind::c::execute_destroy<org::sem::CmdAuthor>(obj); }

void haxorg_destroy_CmdEmail(haxorg_CmdEmail* obj) { org::bind::c::execute_destroy<org::sem::CmdEmail>(obj); }

void haxorg_destroy_CmdLanguage(haxorg_CmdLanguage* obj) { org::bind::c::execute_destroy<org::sem::CmdLanguage>(obj); }

void haxorg_destroy_CmdCustomArgs(haxorg_CmdCustomArgs* obj) { org::bind::c::execute_destroy<org::sem::CmdCustomArgs>(obj); }

void haxorg_destroy_CmdTblfm(haxorg_CmdTblfm* obj) { org::bind::c::execute_destroy<org::sem::CmdTblfm>(obj); }

void haxorg_destroy_Cell(haxorg_Cell* obj) { org::bind::c::execute_destroy<org::sem::Cell>(obj); }

void haxorg_destroy_Row(haxorg_Row* obj) { org::bind::c::execute_destroy<org::sem::Row>(obj); }

void haxorg_destroy_ImmBlock(haxorg_ImmBlock* obj) { org::bind::c::execute_destroy<org::imm::ImmBlock>(obj); }

void haxorg_destroy_ImmLineCommand(haxorg_ImmLineCommand* obj) { org::bind::c::execute_destroy<org::imm::ImmLineCommand>(obj); }

void haxorg_destroy_ImmCmdCreator(haxorg_ImmCmdCreator* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdCreator>(obj); }

void haxorg_destroy_ImmCmdAuthor(haxorg_ImmCmdAuthor* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdAuthor>(obj); }

void haxorg_destroy_ImmCmdEmail(haxorg_ImmCmdEmail* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdEmail>(obj); }

void haxorg_destroy_ImmCmdLanguage(haxorg_ImmCmdLanguage* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdLanguage>(obj); }

void haxorg_destroy_ImmCmdCustomArgs(haxorg_ImmCmdCustomArgs* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdCustomArgs>(obj); }

void haxorg_destroy_ImmCmdTblfm(haxorg_ImmCmdTblfm* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdTblfm>(obj); }

void haxorg_destroy_ImmCell(haxorg_ImmCell* obj) { org::bind::c::execute_destroy<org::imm::ImmCell>(obj); }

void haxorg_destroy_ImmRow(haxorg_ImmRow* obj) { org::bind::c::execute_destroy<org::imm::ImmRow>(obj); }

void haxorg_destroy_ImmAdapterCmdAPI(haxorg_ImmAdapterCmdAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdCustomRawAPI(haxorg_ImmAdapterCmdCustomRawAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdCustomRawAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdCustomTextAPI(haxorg_ImmAdapterCmdCustomTextAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdCustomTextAPI>(obj); }

void haxorg_destroy_ImmAdapterLinkAPI(haxorg_ImmAdapterLinkAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterLinkAPI>(obj); }

void haxorg_destroy_ImmAdapterBlockCommentAPI(haxorg_ImmAdapterBlockCommentAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockCommentAPI>(obj); }

void haxorg_destroy_ImmAdapterParagraphAPI(haxorg_ImmAdapterParagraphAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterParagraphAPI>(obj); }

void haxorg_destroy_ImmAdapterListAPI(haxorg_ImmAdapterListAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterListAPI>(obj); }

void haxorg_create_ImmAdapterTOfImmStmt_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmStmt> { return org::imm::ImmAdapterT<org::imm::ImmStmt>(other); }, org_context, other); }

void haxorg_destroy_ImmStmtAdapter(haxorg_ImmStmtAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmStmt>>(obj); }

void haxorg_create_ImmAdapterTOfImmSubtree_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmSubtree> { return org::imm::ImmAdapterT<org::imm::ImmSubtree>(other); }, org_context, other); }

void haxorg_destroy_ImmSubtreeAdapter(haxorg_ImmSubtreeAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmSubtree>>(obj); }

void haxorg_create_ImmAdapterTOfImmNoNode_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmNoNode> { return org::imm::ImmAdapterT<org::imm::ImmNoNode>(other); }, org_context, other); }

void haxorg_destroy_ImmNoNodeAdapter(haxorg_ImmNoNodeAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmNoNode>>(obj); }

void haxorg_create_ImmAdapterTOfImmErrorItem_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmErrorItem> { return org::imm::ImmAdapterT<org::imm::ImmErrorItem>(other); }, org_context, other); }

void haxorg_destroy_ImmErrorItemAdapter(haxorg_ImmErrorItemAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmErrorItem>>(obj); }

void haxorg_create_ImmAdapterTOfImmErrorGroup_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmErrorGroup> { return org::imm::ImmAdapterT<org::imm::ImmErrorGroup>(other); }, org_context, other); }

void haxorg_destroy_ImmErrorGroupAdapter(haxorg_ImmErrorGroupAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmErrorGroup>>(obj); }

void haxorg_create_ImmAdapterTOfImmErrorSkipGroup_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmErrorSkipGroup> { return org::imm::ImmAdapterT<org::imm::ImmErrorSkipGroup>(other); }, org_context, other); }

void haxorg_destroy_ImmErrorSkipGroupAdapter(haxorg_ImmErrorSkipGroupAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmErrorSkipGroup>>(obj); }

void haxorg_create_ImmAdapterTOfImmErrorSkipToken_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmErrorSkipToken> { return org::imm::ImmAdapterT<org::imm::ImmErrorSkipToken>(other); }, org_context, other); }

void haxorg_destroy_ImmErrorSkipTokenAdapter(haxorg_ImmErrorSkipTokenAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmErrorSkipToken>>(obj); }

void haxorg_create_ImmAdapterTOfImmStmtList_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmStmtList> { return org::imm::ImmAdapterT<org::imm::ImmStmtList>(other); }, org_context, other); }

void haxorg_destroy_ImmStmtListAdapter(haxorg_ImmStmtListAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmStmtList>>(obj); }

void haxorg_create_ImmAdapterTOfImmEmpty_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmEmpty> { return org::imm::ImmAdapterT<org::imm::ImmEmpty>(other); }, org_context, other); }

void haxorg_destroy_ImmEmptyAdapter(haxorg_ImmEmptyAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmEmpty>>(obj); }

void haxorg_destroy_ImmAdapterHashTagAPI(haxorg_ImmAdapterHashTagAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterHashTagAPI>(obj); }

void haxorg_destroy_ImmAdapterInlineFootnoteAPI(haxorg_ImmAdapterInlineFootnoteAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterInlineFootnoteAPI>(obj); }

void haxorg_destroy_ImmAdapterSubtreeCompletionAPI(haxorg_ImmAdapterSubtreeCompletionAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterSubtreeCompletionAPI>(obj); }

void haxorg_create_ImmAdapterTOfImmInline_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmInline> { return org::imm::ImmAdapterT<org::imm::ImmInline>(other); }, org_context, other); }

void haxorg_destroy_ImmInlineAdapter(haxorg_ImmInlineAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmInline>>(obj); }

void haxorg_create_ImmAdapterTOfImmTime_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmTime> { return org::imm::ImmAdapterT<org::imm::ImmTime>(other); }, org_context, other); }

void haxorg_destroy_ImmTimeAdapter(haxorg_ImmTimeAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmTime>>(obj); }

void haxorg_create_ImmAdapterTOfImmTimeRange_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmTimeRange> { return org::imm::ImmAdapterT<org::imm::ImmTimeRange>(other); }, org_context, other); }

void haxorg_destroy_ImmTimeRangeAdapter(haxorg_ImmTimeRangeAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmTimeRange>>(obj); }

void haxorg_create_ImmAdapterTOfImmMacro_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmMacro> { return org::imm::ImmAdapterT<org::imm::ImmMacro>(other); }, org_context, other); }

void haxorg_destroy_ImmMacroAdapter(haxorg_ImmMacroAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmMacro>>(obj); }

void haxorg_create_ImmAdapterTOfImmSymbol_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmSymbol> { return org::imm::ImmAdapterT<org::imm::ImmSymbol>(other); }, org_context, other); }

void haxorg_destroy_ImmSymbolAdapter(haxorg_ImmSymbolAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmSymbol>>(obj); }

void haxorg_destroy_ImmAdapterEscapedAPI(haxorg_ImmAdapterEscapedAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterEscapedAPI>(obj); }

void haxorg_destroy_ImmAdapterNewlineAPI(haxorg_ImmAdapterNewlineAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterNewlineAPI>(obj); }

void haxorg_destroy_ImmAdapterSpaceAPI(haxorg_ImmAdapterSpaceAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterSpaceAPI>(obj); }

void haxorg_destroy_ImmAdapterWordAPI(haxorg_ImmAdapterWordAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterWordAPI>(obj); }

void haxorg_destroy_ImmAdapterAtMentionAPI(haxorg_ImmAdapterAtMentionAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterAtMentionAPI>(obj); }

void haxorg_destroy_ImmAdapterRawTextAPI(haxorg_ImmAdapterRawTextAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterRawTextAPI>(obj); }

void haxorg_destroy_ImmAdapterPunctuationAPI(haxorg_ImmAdapterPunctuationAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterPunctuationAPI>(obj); }

void haxorg_destroy_ImmAdapterPlaceholderAPI(haxorg_ImmAdapterPlaceholderAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterPlaceholderAPI>(obj); }

void haxorg_destroy_ImmAdapterBigIdentAPI(haxorg_ImmAdapterBigIdentAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBigIdentAPI>(obj); }

void haxorg_destroy_ImmAdapterTextTargetAPI(haxorg_ImmAdapterTextTargetAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterTextTargetAPI>(obj); }

void haxorg_create_ImmAdapterTOfImmLeaf_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmLeaf> { return org::imm::ImmAdapterT<org::imm::ImmLeaf>(other); }, org_context, other); }

void haxorg_destroy_ImmLeafAdapter(haxorg_ImmLeafAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmLeaf>>(obj); }

void haxorg_destroy_ImmAdapterBoldAPI(haxorg_ImmAdapterBoldAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBoldAPI>(obj); }

void haxorg_destroy_ImmAdapterUnderlineAPI(haxorg_ImmAdapterUnderlineAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterUnderlineAPI>(obj); }

void haxorg_destroy_ImmAdapterMonospaceAPI(haxorg_ImmAdapterMonospaceAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterMonospaceAPI>(obj); }

void haxorg_destroy_ImmAdapterMarkQuoteAPI(haxorg_ImmAdapterMarkQuoteAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterMarkQuoteAPI>(obj); }

void haxorg_destroy_ImmAdapterRadioTargetAPI(haxorg_ImmAdapterRadioTargetAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterRadioTargetAPI>(obj); }

void haxorg_destroy_ImmAdapterVerbatimAPI(haxorg_ImmAdapterVerbatimAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterVerbatimAPI>(obj); }

void haxorg_destroy_ImmAdapterItalicAPI(haxorg_ImmAdapterItalicAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterItalicAPI>(obj); }

void haxorg_destroy_ImmAdapterStrikeAPI(haxorg_ImmAdapterStrikeAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterStrikeAPI>(obj); }

void haxorg_destroy_ImmAdapterParAPI(haxorg_ImmAdapterParAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterParAPI>(obj); }

void haxorg_create_ImmAdapterTOfImmMarkup_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmMarkup> { return org::imm::ImmAdapterT<org::imm::ImmMarkup>(other); }, org_context, other); }

void haxorg_destroy_ImmMarkupAdapter(haxorg_ImmMarkupAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmMarkup>>(obj); }

void haxorg_create_ImmAdapterTOfImmLatex_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmLatex> { return org::imm::ImmAdapterT<org::imm::ImmLatex>(other); }, org_context, other); }

void haxorg_destroy_ImmLatexAdapter(haxorg_ImmLatexAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmLatex>>(obj); }

void haxorg_create_ImmAdapterTOfImmSubtreeLog_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmSubtreeLog> { return org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>(other); }, org_context, other); }

void haxorg_destroy_ImmSubtreeLogAdapter(haxorg_ImmSubtreeLogAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>>(obj); }

void haxorg_create_ImmAdapterTOfImmColonExample_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmColonExample> { return org::imm::ImmAdapterT<org::imm::ImmColonExample>(other); }, org_context, other); }

void haxorg_destroy_ImmColonExampleAdapter(haxorg_ImmColonExampleAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmColonExample>>(obj); }

void haxorg_create_ImmAdapterTOfImmCall_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCall> { return org::imm::ImmAdapterT<org::imm::ImmCall>(other); }, org_context, other); }

void haxorg_destroy_ImmCallAdapter(haxorg_ImmCallAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCall>>(obj); }

void haxorg_create_ImmAdapterTOfImmFile_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmFile> { return org::imm::ImmAdapterT<org::imm::ImmFile>(other); }, org_context, other); }

void haxorg_destroy_ImmFileAdapter(haxorg_ImmFileAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmFile>>(obj); }

void haxorg_create_ImmAdapterTOfImmDirectory_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmDirectory> { return org::imm::ImmAdapterT<org::imm::ImmDirectory>(other); }, org_context, other); }

void haxorg_destroy_ImmDirectoryAdapter(haxorg_ImmDirectoryAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmDirectory>>(obj); }

void haxorg_create_ImmAdapterTOfImmSymlink_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmSymlink> { return org::imm::ImmAdapterT<org::imm::ImmSymlink>(other); }, org_context, other); }

void haxorg_destroy_ImmSymlinkAdapter(haxorg_ImmSymlinkAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmSymlink>>(obj); }

void haxorg_create_ImmAdapterTOfImmDocumentFragment_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmDocumentFragment> { return org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>(other); }, org_context, other); }

void haxorg_destroy_ImmDocumentFragmentAdapter(haxorg_ImmDocumentFragmentAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>>(obj); }

void haxorg_create_ImmAdapterTOfImmCriticMarkup_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCriticMarkup> { return org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>(other); }, org_context, other); }

void haxorg_destroy_ImmCriticMarkupAdapter(haxorg_ImmCriticMarkupAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>>(obj); }

void haxorg_create_ImmAdapterTOfImmListItem_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmListItem> { return org::imm::ImmAdapterT<org::imm::ImmListItem>(other); }, org_context, other); }

void haxorg_destroy_ImmListItemAdapter(haxorg_ImmListItemAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmListItem>>(obj); }

void haxorg_create_ImmAdapterTOfImmDocumentOptions_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmDocumentOptions> { return org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>(other); }, org_context, other); }

void haxorg_destroy_ImmDocumentOptionsAdapter(haxorg_ImmDocumentOptionsAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>>(obj); }

void haxorg_create_ImmAdapterTOfImmDocument_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmDocument> { return org::imm::ImmAdapterT<org::imm::ImmDocument>(other); }, org_context, other); }

void haxorg_destroy_ImmDocumentAdapter(haxorg_ImmDocumentAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmDocument>>(obj); }

void haxorg_create_ImmAdapterTOfImmFileTarget_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmFileTarget> { return org::imm::ImmAdapterT<org::imm::ImmFileTarget>(other); }, org_context, other); }

void haxorg_destroy_ImmFileTargetAdapter(haxorg_ImmFileTargetAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmFileTarget>>(obj); }

void haxorg_create_ImmAdapterTOfImmTextSeparator_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmTextSeparator> { return org::imm::ImmAdapterT<org::imm::ImmTextSeparator>(other); }, org_context, other); }

void haxorg_destroy_ImmTextSeparatorAdapter(haxorg_ImmTextSeparatorAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmTextSeparator>>(obj); }

void haxorg_create_ImmAdapterTOfImmCmdInclude_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdInclude> { return org::imm::ImmAdapterT<org::imm::ImmCmdInclude>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdIncludeAdapter(haxorg_ImmCmdIncludeAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdInclude>>(obj); }

void haxorg_create_ImmAdapterTOfImmDocumentGroup_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmDocumentGroup> { return org::imm::ImmAdapterT<org::imm::ImmDocumentGroup>(other); }, org_context, other); }

void haxorg_destroy_ImmDocumentGroupAdapter(haxorg_ImmDocumentGroupAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmDocumentGroup>>(obj); }

void haxorg_destroy_BlockCenter(haxorg_BlockCenter* obj) { org::bind::c::execute_destroy<org::sem::BlockCenter>(obj); }

void haxorg_destroy_BlockQuote(haxorg_BlockQuote* obj) { org::bind::c::execute_destroy<org::sem::BlockQuote>(obj); }

void haxorg_destroy_BlockVerse(haxorg_BlockVerse* obj) { org::bind::c::execute_destroy<org::sem::BlockVerse>(obj); }

void haxorg_destroy_BlockDynamicFallback(haxorg_BlockDynamicFallback* obj) { org::bind::c::execute_destroy<org::sem::BlockDynamicFallback>(obj); }

void haxorg_destroy_BlockExample(haxorg_BlockExample* obj) { org::bind::c::execute_destroy<org::sem::BlockExample>(obj); }

void haxorg_destroy_BlockExport(haxorg_BlockExport* obj) { org::bind::c::execute_destroy<org::sem::BlockExport>(obj); }

void haxorg_destroy_BlockAdmonition(haxorg_BlockAdmonition* obj) { org::bind::c::execute_destroy<org::sem::BlockAdmonition>(obj); }

void haxorg_destroy_BlockCodeEvalResult(haxorg_BlockCodeEvalResult* obj) { org::bind::c::execute_destroy<org::sem::BlockCodeEvalResult>(obj); }

void haxorg_destroy_BlockCode(haxorg_BlockCode* obj) { org::bind::c::execute_destroy<org::sem::BlockCode>(obj); }

void haxorg_destroy_Table(haxorg_Table* obj) { org::bind::c::execute_destroy<org::sem::Table>(obj); }

void haxorg_destroy_Attached(haxorg_Attached* obj) { org::bind::c::execute_destroy<org::sem::Attached>(obj); }

void haxorg_destroy_ImmBlockCenter(haxorg_ImmBlockCenter* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockCenter>(obj); }

void haxorg_destroy_ImmBlockQuote(haxorg_ImmBlockQuote* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockQuote>(obj); }

void haxorg_destroy_ImmBlockVerse(haxorg_ImmBlockVerse* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockVerse>(obj); }

void haxorg_destroy_ImmBlockDynamicFallback(haxorg_ImmBlockDynamicFallback* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockDynamicFallback>(obj); }

void haxorg_destroy_ImmBlockExample(haxorg_ImmBlockExample* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockExample>(obj); }

void haxorg_destroy_ImmBlockExport(haxorg_ImmBlockExport* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockExport>(obj); }

void haxorg_destroy_ImmBlockAdmonition(haxorg_ImmBlockAdmonition* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockAdmonition>(obj); }

void haxorg_destroy_ImmBlockCodeEvalResult(haxorg_ImmBlockCodeEvalResult* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockCodeEvalResult>(obj); }

void haxorg_destroy_ImmBlockCode(haxorg_ImmBlockCode* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockCode>(obj); }

void haxorg_destroy_ImmTable(haxorg_ImmTable* obj) { org::bind::c::execute_destroy<org::imm::ImmTable>(obj); }

void haxorg_destroy_ImmAttached(haxorg_ImmAttached* obj) { org::bind::c::execute_destroy<org::imm::ImmAttached>(obj); }

void haxorg_destroy_ImmAdapterLineCommandAPI(haxorg_ImmAdapterLineCommandAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterLineCommandAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdCustomArgsAPI(haxorg_ImmAdapterCmdCustomArgsAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdCustomArgsAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdCreatorAPI(haxorg_ImmAdapterCmdCreatorAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdCreatorAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdAuthorAPI(haxorg_ImmAdapterCmdAuthorAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdAuthorAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdEmailAPI(haxorg_ImmAdapterCmdEmailAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdEmailAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdLanguageAPI(haxorg_ImmAdapterCmdLanguageAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdLanguageAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdTblfmAPI(haxorg_ImmAdapterCmdTblfmAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdTblfmAPI>(obj); }

void haxorg_destroy_ImmAdapterBlockAPI(haxorg_ImmAdapterBlockAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockAPI>(obj); }

void haxorg_destroy_ImmAdapterCellAPI(haxorg_ImmAdapterCellAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCellAPI>(obj); }

void haxorg_destroy_ImmAdapterRowAPI(haxorg_ImmAdapterRowAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterRowAPI>(obj); }

void haxorg_create_ImmAdapterTOfImmCmd_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmd> { return org::imm::ImmAdapterT<org::imm::ImmCmd>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdAdapter(haxorg_ImmCmdAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmd>>(obj); }

void haxorg_create_ImmAdapterTOfImmCmdCustomRaw_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw> { return org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdCustomRawAdapter(haxorg_ImmCmdCustomRawAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>>(obj); }

void haxorg_create_ImmAdapterTOfImmCmdCustomText_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdCustomText> { return org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdCustomTextAdapter(haxorg_ImmCmdCustomTextAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>>(obj); }

void haxorg_create_ImmAdapterTOfImmLink_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmLink> { return org::imm::ImmAdapterT<org::imm::ImmLink>(other); }, org_context, other); }

void haxorg_destroy_ImmLinkAdapter(haxorg_ImmLinkAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmLink>>(obj); }

void haxorg_create_ImmAdapterTOfImmBlockComment_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlockComment> { return org::imm::ImmAdapterT<org::imm::ImmBlockComment>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockCommentAdapter(haxorg_ImmBlockCommentAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlockComment>>(obj); }

void haxorg_create_ImmAdapterTOfImmParagraph_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmParagraph> { return org::imm::ImmAdapterT<org::imm::ImmParagraph>(other); }, org_context, other); }

void haxorg_destroy_ImmParagraphAdapter(haxorg_ImmParagraphAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(obj); }

void haxorg_create_ImmAdapterTOfImmList_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmList> { return org::imm::ImmAdapterT<org::imm::ImmList>(other); }, org_context, other); }

void haxorg_destroy_ImmListAdapter(haxorg_ImmListAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmList>>(obj); }

void haxorg_create_ImmAdapterTOfImmHashTag_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmHashTag> { return org::imm::ImmAdapterT<org::imm::ImmHashTag>(other); }, org_context, other); }

void haxorg_destroy_ImmHashTagAdapter(haxorg_ImmHashTagAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmHashTag>>(obj); }

void haxorg_create_ImmAdapterTOfImmInlineFootnote_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmInlineFootnote> { return org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>(other); }, org_context, other); }

void haxorg_destroy_ImmInlineFootnoteAdapter(haxorg_ImmInlineFootnoteAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>>(obj); }

void haxorg_create_ImmAdapterTOfImmEscaped_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmEscaped> { return org::imm::ImmAdapterT<org::imm::ImmEscaped>(other); }, org_context, other); }

void haxorg_destroy_ImmEscapedAdapter(haxorg_ImmEscapedAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmEscaped>>(obj); }

void haxorg_create_ImmAdapterTOfImmNewline_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmNewline> { return org::imm::ImmAdapterT<org::imm::ImmNewline>(other); }, org_context, other); }

void haxorg_destroy_ImmNewlineAdapter(haxorg_ImmNewlineAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmNewline>>(obj); }

void haxorg_create_ImmAdapterTOfImmSpace_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmSpace> { return org::imm::ImmAdapterT<org::imm::ImmSpace>(other); }, org_context, other); }

void haxorg_destroy_ImmSpaceAdapter(haxorg_ImmSpaceAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmSpace>>(obj); }

void haxorg_create_ImmAdapterTOfImmWord_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmWord> { return org::imm::ImmAdapterT<org::imm::ImmWord>(other); }, org_context, other); }

void haxorg_destroy_ImmWordAdapter(haxorg_ImmWordAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmWord>>(obj); }

void haxorg_create_ImmAdapterTOfImmAtMention_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmAtMention> { return org::imm::ImmAdapterT<org::imm::ImmAtMention>(other); }, org_context, other); }

void haxorg_destroy_ImmAtMentionAdapter(haxorg_ImmAtMentionAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmAtMention>>(obj); }

void haxorg_create_ImmAdapterTOfImmRawText_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmRawText> { return org::imm::ImmAdapterT<org::imm::ImmRawText>(other); }, org_context, other); }

void haxorg_destroy_ImmRawTextAdapter(haxorg_ImmRawTextAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmRawText>>(obj); }

void haxorg_create_ImmAdapterTOfImmPunctuation_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmPunctuation> { return org::imm::ImmAdapterT<org::imm::ImmPunctuation>(other); }, org_context, other); }

void haxorg_destroy_ImmPunctuationAdapter(haxorg_ImmPunctuationAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmPunctuation>>(obj); }

void haxorg_create_ImmAdapterTOfImmPlaceholder_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmPlaceholder> { return org::imm::ImmAdapterT<org::imm::ImmPlaceholder>(other); }, org_context, other); }

void haxorg_destroy_ImmPlaceholderAdapter(haxorg_ImmPlaceholderAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmPlaceholder>>(obj); }

void haxorg_create_ImmAdapterTOfImmBigIdent_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBigIdent> { return org::imm::ImmAdapterT<org::imm::ImmBigIdent>(other); }, org_context, other); }

void haxorg_destroy_ImmBigIdentAdapter(haxorg_ImmBigIdentAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBigIdent>>(obj); }

void haxorg_create_ImmAdapterTOfImmTextTarget_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmTextTarget> { return org::imm::ImmAdapterT<org::imm::ImmTextTarget>(other); }, org_context, other); }

void haxorg_destroy_ImmTextTargetAdapter(haxorg_ImmTextTargetAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmTextTarget>>(obj); }

void haxorg_create_ImmAdapterTOfImmBold_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBold> { return org::imm::ImmAdapterT<org::imm::ImmBold>(other); }, org_context, other); }

void haxorg_destroy_ImmBoldAdapter(haxorg_ImmBoldAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBold>>(obj); }

void haxorg_create_ImmAdapterTOfImmUnderline_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmUnderline> { return org::imm::ImmAdapterT<org::imm::ImmUnderline>(other); }, org_context, other); }

void haxorg_destroy_ImmUnderlineAdapter(haxorg_ImmUnderlineAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmUnderline>>(obj); }

void haxorg_create_ImmAdapterTOfImmMonospace_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmMonospace> { return org::imm::ImmAdapterT<org::imm::ImmMonospace>(other); }, org_context, other); }

void haxorg_destroy_ImmMonospaceAdapter(haxorg_ImmMonospaceAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmMonospace>>(obj); }

void haxorg_create_ImmAdapterTOfImmMarkQuote_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmMarkQuote> { return org::imm::ImmAdapterT<org::imm::ImmMarkQuote>(other); }, org_context, other); }

void haxorg_destroy_ImmMarkQuoteAdapter(haxorg_ImmMarkQuoteAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmMarkQuote>>(obj); }

void haxorg_create_ImmAdapterTOfImmRadioTarget_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmRadioTarget> { return org::imm::ImmAdapterT<org::imm::ImmRadioTarget>(other); }, org_context, other); }

void haxorg_destroy_ImmRadioTargetAdapter(haxorg_ImmRadioTargetAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmRadioTarget>>(obj); }

void haxorg_create_ImmAdapterTOfImmVerbatim_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmVerbatim> { return org::imm::ImmAdapterT<org::imm::ImmVerbatim>(other); }, org_context, other); }

void haxorg_destroy_ImmVerbatimAdapter(haxorg_ImmVerbatimAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmVerbatim>>(obj); }

void haxorg_create_ImmAdapterTOfImmItalic_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmItalic> { return org::imm::ImmAdapterT<org::imm::ImmItalic>(other); }, org_context, other); }

void haxorg_destroy_ImmItalicAdapter(haxorg_ImmItalicAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmItalic>>(obj); }

void haxorg_create_ImmAdapterTOfImmStrike_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmStrike> { return org::imm::ImmAdapterT<org::imm::ImmStrike>(other); }, org_context, other); }

void haxorg_destroy_ImmStrikeAdapter(haxorg_ImmStrikeAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmStrike>>(obj); }

void haxorg_create_ImmAdapterTOfImmPar_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmPar> { return org::imm::ImmAdapterT<org::imm::ImmPar>(other); }, org_context, other); }

void haxorg_destroy_ImmParAdapter(haxorg_ImmParAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmPar>>(obj); }

void haxorg_destroy_CmdCaption(haxorg_CmdCaption* obj) { org::bind::c::execute_destroy<org::sem::CmdCaption>(obj); }

void haxorg_destroy_CmdColumns(haxorg_CmdColumns* obj) { org::bind::c::execute_destroy<org::sem::CmdColumns>(obj); }

void haxorg_destroy_CmdName(haxorg_CmdName* obj) { org::bind::c::execute_destroy<org::sem::CmdName>(obj); }

void haxorg_destroy_CmdCall(haxorg_CmdCall* obj) { org::bind::c::execute_destroy<org::sem::CmdCall>(obj); }

void haxorg_destroy_CmdAttr(haxorg_CmdAttr* obj) { org::bind::c::execute_destroy<org::sem::CmdAttr>(obj); }

void haxorg_destroy_CmdExport(haxorg_CmdExport* obj) { org::bind::c::execute_destroy<org::sem::CmdExport>(obj); }

void haxorg_destroy_ImmCmdCaption(haxorg_ImmCmdCaption* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdCaption>(obj); }

void haxorg_destroy_ImmCmdColumns(haxorg_ImmCmdColumns* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdColumns>(obj); }

void haxorg_destroy_ImmCmdName(haxorg_ImmCmdName* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdName>(obj); }

void haxorg_destroy_ImmCmdCall(haxorg_ImmCmdCall* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdCall>(obj); }

void haxorg_destroy_ImmCmdAttr(haxorg_ImmCmdAttr* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdAttr>(obj); }

void haxorg_destroy_ImmCmdExport(haxorg_ImmCmdExport* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdExport>(obj); }

void haxorg_destroy_ImmAdapterAttachedAPI(haxorg_ImmAdapterAttachedAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterAttachedAPI>(obj); }

void haxorg_create_ImmAdapterTOfImmLineCommand_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmLineCommand> { return org::imm::ImmAdapterT<org::imm::ImmLineCommand>(other); }, org_context, other); }

void haxorg_destroy_ImmLineCommandAdapter(haxorg_ImmLineCommandAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmLineCommand>>(obj); }

void haxorg_create_ImmAdapterTOfImmCmdCustomArgs_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs> { return org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdCustomArgsAdapter(haxorg_ImmCmdCustomArgsAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>>(obj); }

void haxorg_create_ImmAdapterTOfImmCmdCreator_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdCreator> { return org::imm::ImmAdapterT<org::imm::ImmCmdCreator>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdCreatorAdapter(haxorg_ImmCmdCreatorAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdCreator>>(obj); }

void haxorg_create_ImmAdapterTOfImmCmdAuthor_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdAuthor> { return org::imm::ImmAdapterT<org::imm::ImmCmdAuthor>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdAuthorAdapter(haxorg_ImmCmdAuthorAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdAuthor>>(obj); }

void haxorg_create_ImmAdapterTOfImmCmdEmail_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdEmail> { return org::imm::ImmAdapterT<org::imm::ImmCmdEmail>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdEmailAdapter(haxorg_ImmCmdEmailAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdEmail>>(obj); }

void haxorg_create_ImmAdapterTOfImmCmdLanguage_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdLanguage> { return org::imm::ImmAdapterT<org::imm::ImmCmdLanguage>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdLanguageAdapter(haxorg_ImmCmdLanguageAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdLanguage>>(obj); }

void haxorg_create_ImmAdapterTOfImmCmdTblfm_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdTblfm> { return org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdTblfmAdapter(haxorg_ImmCmdTblfmAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>>(obj); }

void haxorg_destroy_ImmAdapterBlockCenterAPI(haxorg_ImmAdapterBlockCenterAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockCenterAPI>(obj); }

void haxorg_destroy_ImmAdapterBlockQuoteAPI(haxorg_ImmAdapterBlockQuoteAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockQuoteAPI>(obj); }

void haxorg_destroy_ImmAdapterBlockVerseAPI(haxorg_ImmAdapterBlockVerseAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockVerseAPI>(obj); }

void haxorg_destroy_ImmAdapterBlockExampleAPI(haxorg_ImmAdapterBlockExampleAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockExampleAPI>(obj); }

void haxorg_destroy_ImmAdapterInlineExportAPI(haxorg_ImmAdapterInlineExportAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterInlineExportAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdExportAPI(haxorg_ImmAdapterCmdExportAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdExportAPI>(obj); }

void haxorg_destroy_ImmAdapterBlockExportAPI(haxorg_ImmAdapterBlockExportAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockExportAPI>(obj); }

void haxorg_destroy_ImmAdapterBlockDynamicFallbackAPI(haxorg_ImmAdapterBlockDynamicFallbackAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockDynamicFallbackAPI>(obj); }

void haxorg_destroy_ImmAdapterBlockAdmonitionAPI(haxorg_ImmAdapterBlockAdmonitionAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockAdmonitionAPI>(obj); }

void haxorg_destroy_ImmAdapterBlockCodeEvalResultAPI(haxorg_ImmAdapterBlockCodeEvalResultAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockCodeEvalResultAPI>(obj); }

void haxorg_destroy_ImmAdapterBlockCodeAPI(haxorg_ImmAdapterBlockCodeAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockCodeAPI>(obj); }

void haxorg_destroy_ImmAdapterTableAPI(haxorg_ImmAdapterTableAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterTableAPI>(obj); }

void haxorg_create_ImmAdapterTOfImmBlock_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlock> { return org::imm::ImmAdapterT<org::imm::ImmBlock>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockAdapter(haxorg_ImmBlockAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlock>>(obj); }

void haxorg_create_ImmAdapterTOfImmCell_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCell> { return org::imm::ImmAdapterT<org::imm::ImmCell>(other); }, org_context, other); }

void haxorg_destroy_ImmCellAdapter(haxorg_ImmCellAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCell>>(obj); }

void haxorg_create_ImmAdapterTOfImmRow_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmRow> { return org::imm::ImmAdapterT<org::imm::ImmRow>(other); }, org_context, other); }

void haxorg_destroy_ImmRowAdapter(haxorg_ImmRowAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmRow>>(obj); }

void haxorg_destroy_ImmAdapterCmdCaptionAPI(haxorg_ImmAdapterCmdCaptionAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdCaptionAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdColumnsAPI(haxorg_ImmAdapterCmdColumnsAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdColumnsAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdNameAPI(haxorg_ImmAdapterCmdNameAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdNameAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdCallAPI(haxorg_ImmAdapterCmdCallAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdCallAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdResultsAPI(haxorg_ImmAdapterCmdResultsAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdResultsAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdAttrAPI(haxorg_ImmAdapterCmdAttrAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdAttrAPI>(obj); }

void haxorg_create_ImmAdapterTOfImmAttached_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmAttached> { return org::imm::ImmAdapterT<org::imm::ImmAttached>(other); }, org_context, other); }

void haxorg_destroy_ImmAttachedAdapter(haxorg_ImmAttachedAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmAttached>>(obj); }

void haxorg_create_ImmAdapterTOfImmBlockCenter_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlockCenter> { return org::imm::ImmAdapterT<org::imm::ImmBlockCenter>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockCenterAdapter(haxorg_ImmBlockCenterAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlockCenter>>(obj); }

void haxorg_create_ImmAdapterTOfImmBlockQuote_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlockQuote> { return org::imm::ImmAdapterT<org::imm::ImmBlockQuote>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockQuoteAdapter(haxorg_ImmBlockQuoteAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlockQuote>>(obj); }

void haxorg_create_ImmAdapterTOfImmBlockVerse_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlockVerse> { return org::imm::ImmAdapterT<org::imm::ImmBlockVerse>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockVerseAdapter(haxorg_ImmBlockVerseAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlockVerse>>(obj); }

void haxorg_create_ImmAdapterTOfImmBlockExample_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlockExample> { return org::imm::ImmAdapterT<org::imm::ImmBlockExample>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockExampleAdapter(haxorg_ImmBlockExampleAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlockExample>>(obj); }

void haxorg_create_ImmAdapterTOfImmInlineExport_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmInlineExport> { return org::imm::ImmAdapterT<org::imm::ImmInlineExport>(other); }, org_context, other); }

void haxorg_destroy_ImmInlineExportAdapter(haxorg_ImmInlineExportAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmInlineExport>>(obj); }

void haxorg_create_ImmAdapterTOfImmCmdExport_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdExport> { return org::imm::ImmAdapterT<org::imm::ImmCmdExport>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdExportAdapter(haxorg_ImmCmdExportAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdExport>>(obj); }

void haxorg_create_ImmAdapterTOfImmBlockExport_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlockExport> { return org::imm::ImmAdapterT<org::imm::ImmBlockExport>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockExportAdapter(haxorg_ImmBlockExportAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlockExport>>(obj); }

void haxorg_create_ImmAdapterTOfImmBlockDynamicFallback_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback> { return org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockDynamicFallbackAdapter(haxorg_ImmBlockDynamicFallbackAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>>(obj); }

void haxorg_create_ImmAdapterTOfImmBlockAdmonition_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition> { return org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockAdmonitionAdapter(haxorg_ImmBlockAdmonitionAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition>>(obj); }

void haxorg_create_ImmAdapterTOfImmBlockCodeEvalResult_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult> { return org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockCodeEvalResultAdapter(haxorg_ImmBlockCodeEvalResultAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>>(obj); }

void haxorg_create_ImmAdapterTOfImmBlockCode_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlockCode> { return org::imm::ImmAdapterT<org::imm::ImmBlockCode>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockCodeAdapter(haxorg_ImmBlockCodeAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlockCode>>(obj); }

void haxorg_create_ImmAdapterTOfImmTable_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmTable> { return org::imm::ImmAdapterT<org::imm::ImmTable>(other); }, org_context, other); }

void haxorg_destroy_ImmTableAdapter(haxorg_ImmTableAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmTable>>(obj); }

void haxorg_create_ImmAdapterTOfImmCmdCaption_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdCaption> { return org::imm::ImmAdapterT<org::imm::ImmCmdCaption>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdCaptionAdapter(haxorg_ImmCmdCaptionAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdCaption>>(obj); }

void haxorg_create_ImmAdapterTOfImmCmdColumns_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdColumns> { return org::imm::ImmAdapterT<org::imm::ImmCmdColumns>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdColumnsAdapter(haxorg_ImmCmdColumnsAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdColumns>>(obj); }

void haxorg_create_ImmAdapterTOfImmCmdName_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdName> { return org::imm::ImmAdapterT<org::imm::ImmCmdName>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdNameAdapter(haxorg_ImmCmdNameAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdName>>(obj); }

void haxorg_create_ImmAdapterTOfImmCmdCall_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdCall> { return org::imm::ImmAdapterT<org::imm::ImmCmdCall>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdCallAdapter(haxorg_ImmCmdCallAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdCall>>(obj); }

void haxorg_create_ImmAdapterTOfImmCmdAttr_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdAttr> { return org::imm::ImmAdapterT<org::imm::ImmCmdAttr>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdAttrAdapter(haxorg_ImmCmdAttrAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdAttr>>(obj); }

haxorg_SemId haxorg_newSemTimeStatic(OrgContext* org_context, haxorg_UserTimeBreakdown breakdown, bool isActive) { return org::bind::c::execute_cpp<haxorg_SemId, haxorg_SemId_vtable>(static_cast<org::sem::SemId<org::sem::Time>(*)(hstd::UserTimeBreakdown const&, bool)>(&org::newSemTimeStatic), org_context, breakdown, isActive); }

haxorg_ImmAstContext haxorg_initImmutableAstContext(OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmAstContext, haxorg_ImmAstContext_vtable>(static_cast<std::shared_ptr<org::imm::ImmAstContext>(*)()>(&org::initImmutableAstContext), org_context); }

haxorg_SemId haxorg_asOneNode(OrgContext* org_context, haxorg_SemId arg) { return org::bind::c::execute_cpp<haxorg_SemId, haxorg_SemId_vtable>(static_cast<org::sem::SemId<org::sem::Org>(*)(org::sem::SemId<org::sem::Org> const&)>(&org::asOneNode), org_context, arg); }

haxorg_StdString haxorg_formatToString(OrgContext* org_context, haxorg_SemId arg) { return org::bind::c::execute_cpp<haxorg_StdString, haxorg_StdString_vtable>(static_cast<std::string(*)(org::sem::SemId<org::sem::Org>)>(&org::formatToString), org_context, arg); }

haxorg_StdString haxorg_exportToYamlString(OrgContext* org_context, haxorg_SemId node, haxorg_OrgYamlExportOpts opts) { return org::bind::c::execute_cpp<haxorg_StdString, haxorg_StdString_vtable>(static_cast<std::string(*)(org::sem::SemId<org::sem::Org> const&, org::OrgYamlExportOpts const&)>(&org::exportToYamlString), org_context, node, opts); }

void haxorg_exportToYamlFile(OrgContext* org_context, haxorg_SemId node, haxorg_StdString path, haxorg_OrgYamlExportOpts opts) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(static_cast<void(*)(org::sem::SemId<org::sem::Org> const&, std::string, org::OrgYamlExportOpts const&)>(&org::exportToYamlFile), org_context, node, path, opts); }

haxorg_StdString haxorg_exportToJsonString(OrgContext* org_context, haxorg_SemId node) { return org::bind::c::execute_cpp<haxorg_StdString, haxorg_StdString_vtable>(static_cast<std::string(*)(org::sem::SemId<org::sem::Org> const&)>(&org::exportToJsonString), org_context, node); }

void haxorg_exportToJsonFile(OrgContext* org_context, haxorg_SemId node, haxorg_StdString path) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(static_cast<void(*)(org::sem::SemId<org::sem::Org> const&, std::string)>(&org::exportToJsonFile), org_context, node, path); }

haxorg_SemId haxorg_readProtobufFile(OrgContext* org_context, haxorg_StdString file) { return org::bind::c::execute_cpp<haxorg_SemId, haxorg_SemId_vtable>(static_cast<org::sem::SemId<org::sem::Document>(*)(std::string const&)>(&org::readProtobufFile), org_context, file); }

void haxorg_exportToProtobufFile(OrgContext* org_context, haxorg_SemId doc, haxorg_StdString file) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(static_cast<void(*)(org::sem::SemId<org::sem::Document>, std::string const&)>(&org::exportToProtobufFile), org_context, doc, file); }

haxorg_StdString haxorg_exportToTreeString(OrgContext* org_context, haxorg_SemId node, haxorg_OrgTreeExportOpts opts) { return org::bind::c::execute_cpp<haxorg_StdString, haxorg_StdString_vtable>(static_cast<std::string(*)(org::sem::SemId<org::sem::Org> const&, org::OrgTreeExportOpts const&)>(&org::exportToTreeString), org_context, node, opts); }

void haxorg_exportToTreeFile(OrgContext* org_context, haxorg_SemId node, haxorg_StdString path, haxorg_OrgTreeExportOpts opts) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(static_cast<void(*)(org::sem::SemId<org::sem::Org> const&, std::string, org::OrgTreeExportOpts const&)>(&org::exportToTreeFile), org_context, node, path, opts); }

haxorg_AstTrackingMap haxorg_getAstTrackingMap(OrgContext* org_context, haxorg_HstdVec nodes) { return org::bind::c::execute_cpp<haxorg_AstTrackingMap, haxorg_AstTrackingMap_vtable>(static_cast<org::AstTrackingMap(*)(hstd::Vec<org::sem::SemId<org::sem::Org>> const&)>(&org::getAstTrackingMap), org_context, nodes); }

haxorg_HstdVec haxorg_getSubnodeGroups(OrgContext* org_context, haxorg_SemId node, haxorg_AstTrackingMap map) { return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<org::AstTrackingGroup>(*)(org::sem::SemId<org::sem::Org>, org::AstTrackingMap const&)>(&org::getSubnodeGroups), org_context, node, map); }

haxorg_HstdVec haxorg_annotateSequence(OrgContext* org_context, haxorg_HstdVec groups, int first, int last) { return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<hstd::SequenceAnnotation>(*)(hstd::Vec<hstd::SequenceSegmentGroup> const&, int, int)>(&hstd::annotateSequence), org_context, groups, first, last); }

haxorg_GraphMapGraphState haxorg_initMapGraphState(OrgContext* org_context, haxorg_ImmAstContext ast) { return org::bind::c::execute_cpp<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>(static_cast<std::shared_ptr<org::graph::MapGraphState>(*)(std::shared_ptr<org::imm::ImmAstContext>)>(&org::graph::initMapGraphState), org_context, ast); }

haxorg_StdString haxorg_serializeAstContextToText(OrgContext* org_context, haxorg_ImmAstContext store) { return org::bind::c::execute_cpp<haxorg_StdString, haxorg_StdString_vtable>(static_cast<std::string(*)(std::shared_ptr<org::imm::ImmAstContext> const&)>(&org::imm::serializeToText), org_context, store); }

void haxorg_serializeAstContextFromText(OrgContext* org_context, haxorg_StdString binary, haxorg_ImmAstContext store) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(static_cast<void(*)(std::string const&, std::shared_ptr<org::imm::ImmAstContext> const&)>(&org::imm::serializeFromText), org_context, binary, store); }

haxorg_StdString haxorg_serializeAstEpochToText(OrgContext* org_context, haxorg_ImmAstReplaceEpoch store) { return org::bind::c::execute_cpp<haxorg_StdString, haxorg_StdString_vtable>(static_cast<std::string(*)(std::shared_ptr<org::imm::ImmAstReplaceEpoch> const&)>(&org::imm::serializeToText), org_context, store); }

void haxorg_serializeAstEpochFromText(OrgContext* org_context, haxorg_StdString binary, haxorg_ImmAstReplaceEpoch store) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(static_cast<void(*)(std::string const&, std::shared_ptr<org::imm::ImmAstReplaceEpoch> const&)>(&org::imm::serializeFromText), org_context, binary, store); }

haxorg_StdString haxorg_serializeMapGraphToText(OrgContext* org_context, haxorg_GraphMapGraph store) { return org::bind::c::execute_cpp<haxorg_StdString, haxorg_StdString_vtable>(static_cast<std::string(*)(std::shared_ptr<org::graph::MapGraph> const&)>(&org::imm::serializeToText), org_context, store); }

void haxorg_serializeMapGraphFromText(OrgContext* org_context, haxorg_StdString binary, haxorg_GraphMapGraph store) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(static_cast<void(*)(std::string const&, std::shared_ptr<org::graph::MapGraph> const&)>(&org::imm::serializeFromText), org_context, binary, store); }

haxorg_StdString haxorg_serializeFromTextToTreeDump(OrgContext* org_context, haxorg_StdString binary) { return org::bind::c::execute_cpp<haxorg_StdString, haxorg_StdString_vtable>(static_cast<std::string(*)(std::string const&)>(&org::imm::serializeFromTextToTreeDump), org_context, binary); }

/* clang-format on */
