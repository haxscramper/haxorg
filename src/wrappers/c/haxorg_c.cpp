/* clang-format off */
#include <wrappers/c/haxorg_c.h>
#include <wrappers/c/haxorg_c_vtables.hpp>
#include <wrappers/c/haxorg_c_vtables_manual.hpp>
#include <wrappers/c/haxorg_c_utils.hpp>


































void haxorg_destroy_SemIdOfOrg(OrgContext* org_context, haxorg_SemIdOfOrg* obj) { org::bind::c::execute_destroy<org::sem::SemId<org::sem::Org>>(org_context, obj); }

void haxorg_destroy_BackwardsIndex(OrgContext* org_context, haxorg_BackwardsIndex* obj) { org::bind::c::execute_destroy<hstd::BackwardsIndex>(org_context, obj); }

void haxorg_destroy_UserTimeBreakdown(OrgContext* org_context, haxorg_UserTimeBreakdown* obj) { org::bind::c::execute_destroy<hstd::UserTimeBreakdown>(org_context, obj); }

void haxorg_destroy_UserTime(OrgContext* org_context, haxorg_UserTime* obj) { org::bind::c::execute_destroy<hstd::UserTime>(org_context, obj); }

void haxorg_destroy_ParseSourceFileId(OrgContext* org_context, haxorg_ParseSourceFileId* obj) { org::bind::c::execute_destroy<org::parse::SourceFileId>(org_context, obj); }

void haxorg_destroy_ParseSourceManager(OrgContext* org_context, haxorg_ParseSourceManager* obj) { org::bind::c::execute_destroy<org::parse::SourceManager>(org_context, obj); }

void haxorg_destroy_ParseSourceLoc(OrgContext* org_context, haxorg_ParseSourceLoc* obj) { org::bind::c::execute_destroy<org::parse::SourceLoc>(org_context, obj); }

void haxorg_destroy_OrgJson(OrgContext* org_context, haxorg_OrgJson* obj) { org::bind::c::execute_destroy<org::sem::OrgJson>(org_context, obj); }

void haxorg_destroy_Org(OrgContext* org_context, haxorg_Org* obj) { org::bind::c::execute_destroy<org::sem::Org>(org_context, obj); }

void haxorg_destroy_OperationsTracer(OrgContext* org_context, haxorg_OperationsTracer* obj) { org::bind::c::execute_destroy<hstd::OperationsTracer>(org_context, obj); }

void haxorg_destroy_Cache(OrgContext* org_context, haxorg_Cache* obj) { org::bind::c::execute_destroy<hstd::ext::Cache>(org_context, obj); }

void haxorg_destroy_ParseOrgParseFragment(OrgContext* org_context, haxorg_ParseOrgParseFragment* obj) { org::bind::c::execute_destroy<org::parse::OrgParseFragment>(org_context, obj); }

void haxorg_destroy_OrgParseParameters(OrgContext* org_context, haxorg_OrgParseParameters* obj) { org::bind::c::execute_destroy<org::parse::OrgParseParameters>(org_context, obj); }

void haxorg_destroy_OrgDirectoryParseParameters(OrgContext* org_context, haxorg_OrgDirectoryParseParameters* obj) { org::bind::c::execute_destroy<org::parse::OrgDirectoryParseParameters>(org_context, obj); }

haxorg_ParseContext haxorg_create_ParseContext_ParseContextDefault(OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ParseContext, haxorg_ParseContext_vtable>(+[]() -> org::parse::ParseContext { return org::parse::ParseContext(); }, org_context); }

haxorg_ParseContext haxorg_create_ParseContext_ParseContextWithManager(OrgContext* org_context, haxorg_ParseSourceManager source) { return org::bind::c::execute_cpp<haxorg_ParseContext, haxorg_ParseContext_vtable>(+[](std::shared_ptr<org::parse::SourceManager> const& source) -> org::parse::ParseContext { return org::parse::ParseContext(source); }, org_context, source); }

void haxorg_destroy_ParseContext(OrgContext* org_context, haxorg_ParseContext* obj) { org::bind::c::execute_destroy<org::parse::ParseContext>(org_context, obj); }

void haxorg_destroy_ImmReflFieldId(OrgContext* org_context, haxorg_ImmReflFieldId* obj) { org::bind::c::execute_destroy<org::imm::ImmReflFieldId>(org_context, obj); }

void haxorg_destroy_ImmId(OrgContext* org_context, haxorg_ImmId* obj) { org::bind::c::execute_destroy<org::imm::ImmId>(org_context, obj); }

void haxorg_destroy_ImmOrg(OrgContext* org_context, haxorg_ImmOrg* obj) { org::bind::c::execute_destroy<org::imm::ImmOrg>(org_context, obj); }

void haxorg_destroy_ImmPathStep(OrgContext* org_context, haxorg_ImmPathStep* obj) { org::bind::c::execute_destroy<org::imm::ImmPathStep>(org_context, obj); }

void haxorg_destroy_ImmPath(OrgContext* org_context, haxorg_ImmPath* obj) { org::bind::c::execute_destroy<org::imm::ImmPath>(org_context, obj); }

void haxorg_destroy_ImmUniqId(OrgContext* org_context, haxorg_ImmUniqId* obj) { org::bind::c::execute_destroy<org::imm::ImmUniqId>(org_context, obj); }

void haxorg_destroy_ImmAstReplaceEpoch(OrgContext* org_context, haxorg_ImmAstReplaceEpoch* obj) { org::bind::c::execute_destroy<org::imm::ImmAstReplaceEpoch>(org_context, obj); }

void haxorg_destroy_ImmAstContext(OrgContext* org_context, haxorg_ImmAstContext* obj) { org::bind::c::execute_destroy<org::imm::ImmAstContext>(org_context, obj); }

void haxorg_destroy_ImmAstVersion(OrgContext* org_context, haxorg_ImmAstVersion* obj) { org::bind::c::execute_destroy<org::imm::ImmAstVersion>(org_context, obj); }

void haxorg_destroy_ImmAdapterTreeReprConf(OrgContext* org_context, haxorg_ImmAdapterTreeReprConf* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapter::TreeReprConf>(org_context, obj); }

void haxorg_destroy_ImmAdapter(OrgContext* org_context, haxorg_ImmAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapter>(org_context, obj); }

void haxorg_destroy_ImmAdapterVirtualBase(OrgContext* org_context, haxorg_ImmAdapterVirtualBase* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterVirtualBase>(org_context, obj); }

void haxorg_destroy_OrgYamlExportOpts(OrgContext* org_context, haxorg_OrgYamlExportOpts* obj) { org::bind::c::execute_destroy<org::OrgYamlExportOpts>(org_context, obj); }

void haxorg_destroy_OrgTreeExportOpts(OrgContext* org_context, haxorg_OrgTreeExportOpts* obj) { org::bind::c::execute_destroy<org::OrgTreeExportOpts>(org_context, obj); }

void haxorg_destroy_AstTrackingPath(OrgContext* org_context, haxorg_AstTrackingPath* obj) { org::bind::c::execute_destroy<org::AstTrackingPath>(org_context, obj); }

void haxorg_destroy_AstTrackingAlternatives(OrgContext* org_context, haxorg_AstTrackingAlternatives* obj) { org::bind::c::execute_destroy<org::AstTrackingAlternatives>(org_context, obj); }

void haxorg_destroy_AstTrackingGroupRadioTarget(OrgContext* org_context, haxorg_AstTrackingGroupRadioTarget* obj) { org::bind::c::execute_destroy<org::AstTrackingGroup::RadioTarget>(org_context, obj); }

void haxorg_destroy_AstTrackingGroupSingle(OrgContext* org_context, haxorg_AstTrackingGroupSingle* obj) { org::bind::c::execute_destroy<org::AstTrackingGroup::Single>(org_context, obj); }

void haxorg_destroy_AstTrackingGroupTrackedHashtag(OrgContext* org_context, haxorg_AstTrackingGroupTrackedHashtag* obj) { org::bind::c::execute_destroy<org::AstTrackingGroup::TrackedHashtag>(org_context, obj); }

void haxorg_destroy_AstTrackingGroup(OrgContext* org_context, haxorg_AstTrackingGroup* obj) { org::bind::c::execute_destroy<org::AstTrackingGroup>(org_context, obj); }

void haxorg_destroy_AstTrackingMap(OrgContext* org_context, haxorg_AstTrackingMap* obj) { org::bind::c::execute_destroy<org::AstTrackingMap>(org_context, obj); }

void haxorg_destroy_SequenceSegment(OrgContext* org_context, haxorg_SequenceSegment* obj) { org::bind::c::execute_destroy<hstd::SequenceSegment>(org_context, obj); }

void haxorg_destroy_SequenceSegmentGroup(OrgContext* org_context, haxorg_SequenceSegmentGroup* obj) { org::bind::c::execute_destroy<hstd::SequenceSegmentGroup>(org_context, obj); }

void haxorg_destroy_SequenceAnnotationTag(OrgContext* org_context, haxorg_SequenceAnnotationTag* obj) { org::bind::c::execute_destroy<hstd::SequenceAnnotationTag>(org_context, obj); }

void haxorg_destroy_SequenceAnnotation(OrgContext* org_context, haxorg_SequenceAnnotation* obj) { org::bind::c::execute_destroy<hstd::SequenceAnnotation>(org_context, obj); }

void haxorg_destroy_GraphMapLinkLink(OrgContext* org_context, haxorg_GraphMapLinkLink* obj) { org::bind::c::execute_destroy<org::graph::MapLink::Link>(org_context, obj); }

void haxorg_destroy_GraphMapLinkRadio(OrgContext* org_context, haxorg_GraphMapLinkRadio* obj) { org::bind::c::execute_destroy<org::graph::MapLink::Radio>(org_context, obj); }

void haxorg_destroy_GraphMapLink(OrgContext* org_context, haxorg_GraphMapLink* obj) { org::bind::c::execute_destroy<org::graph::MapLink>(org_context, obj); }

void haxorg_destroy_GraphMapNodeProp(OrgContext* org_context, haxorg_GraphMapNodeProp* obj) { org::bind::c::execute_destroy<org::graph::MapNodeProp>(org_context, obj); }

void haxorg_destroy_GraphMapEdgeProp(OrgContext* org_context, haxorg_GraphMapEdgeProp* obj) { org::bind::c::execute_destroy<org::graph::MapEdgeProp>(org_context, obj); }

void haxorg_destroy_GraphMapNode(OrgContext* org_context, haxorg_GraphMapNode* obj) { org::bind::c::execute_destroy<org::graph::MapNode>(org_context, obj); }

void haxorg_destroy_GraphMapEdge(OrgContext* org_context, haxorg_GraphMapEdge* obj) { org::bind::c::execute_destroy<org::graph::MapEdge>(org_context, obj); }

void haxorg_destroy_GraphMapGraph(OrgContext* org_context, haxorg_GraphMapGraph* obj) { org::bind::c::execute_destroy<org::graph::MapGraph>(org_context, obj); }

void haxorg_destroy_GraphMapConfig(OrgContext* org_context, haxorg_GraphMapConfig* obj) { org::bind::c::execute_destroy<org::graph::MapConfig>(org_context, obj); }

void haxorg_destroy_GraphMapGraphState(OrgContext* org_context, haxorg_GraphMapGraphState* obj) { org::bind::c::execute_destroy<org::graph::MapGraphState>(org_context, obj); }

void haxorg_create_LispCode_LispCode(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::LispCode { return org::sem::LispCode(); }, org_context); }

void haxorg_create_LispCodeCall_Call(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::LispCode::Call { return org::sem::LispCode::Call(); }, org_context); }

void haxorg_destroy_LispCodeCall(OrgContext* org_context, haxorg_LispCodeCall* obj) { org::bind::c::execute_destroy<org::sem::LispCode::Call>(org_context, obj); }

void haxorg_create_LispCodeList_List(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::LispCode::List { return org::sem::LispCode::List(); }, org_context); }

void haxorg_destroy_LispCodeList(OrgContext* org_context, haxorg_LispCodeList* obj) { org::bind::c::execute_destroy<org::sem::LispCode::List>(org_context, obj); }

void haxorg_create_LispCodeKeyValue_KeyValue(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::LispCode::KeyValue { return org::sem::LispCode::KeyValue(); }, org_context); }

void haxorg_destroy_LispCodeKeyValue(OrgContext* org_context, haxorg_LispCodeKeyValue* obj) { org::bind::c::execute_destroy<org::sem::LispCode::KeyValue>(org_context, obj); }

void haxorg_create_LispCodeNumber_Number(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::LispCode::Number { return org::sem::LispCode::Number(); }, org_context); }

void haxorg_destroy_LispCodeNumber(OrgContext* org_context, haxorg_LispCodeNumber* obj) { org::bind::c::execute_destroy<org::sem::LispCode::Number>(org_context, obj); }

void haxorg_create_LispCodeText_Text(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::LispCode::Text { return org::sem::LispCode::Text(); }, org_context); }

void haxorg_destroy_LispCodeText(OrgContext* org_context, haxorg_LispCodeText* obj) { org::bind::c::execute_destroy<org::sem::LispCode::Text>(org_context, obj); }

void haxorg_create_LispCodeIdent_Ident(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::LispCode::Ident { return org::sem::LispCode::Ident(); }, org_context); }

void haxorg_destroy_LispCodeIdent(OrgContext* org_context, haxorg_LispCodeIdent* obj) { org::bind::c::execute_destroy<org::sem::LispCode::Ident>(org_context, obj); }

void haxorg_create_LispCodeBoolean_Boolean(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::LispCode::Boolean { return org::sem::LispCode::Boolean(); }, org_context); }

void haxorg_destroy_LispCodeBoolean(OrgContext* org_context, haxorg_LispCodeBoolean* obj) { org::bind::c::execute_destroy<org::sem::LispCode::Boolean>(org_context, obj); }

void haxorg_create_LispCodeReal_Real(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::LispCode::Real { return org::sem::LispCode::Real(); }, org_context); }

void haxorg_destroy_LispCodeReal(OrgContext* org_context, haxorg_LispCodeReal* obj) { org::bind::c::execute_destroy<org::sem::LispCode::Real>(org_context, obj); }

void haxorg_destroy_LispCode(OrgContext* org_context, haxorg_LispCode* obj) { org::bind::c::execute_destroy<org::sem::LispCode>(org_context, obj); }

void haxorg_create_TblfmExprAxisRefPosition_Position(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::Tblfm::Expr::AxisRef::Position { return org::sem::Tblfm::Expr::AxisRef::Position(); }, org_context); }

void haxorg_create_TblfmExprAxisRefPositionIndex_Index(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::Tblfm::Expr::AxisRef::Position::Index { return org::sem::Tblfm::Expr::AxisRef::Position::Index(); }, org_context); }

void haxorg_destroy_TblfmExprAxisRefPositionIndex(OrgContext* org_context, haxorg_TblfmExprAxisRefPositionIndex* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::AxisRef::Position::Index>(org_context, obj); }

void haxorg_create_TblfmExprAxisRefPositionName_Name(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::Tblfm::Expr::AxisRef::Position::Name { return org::sem::Tblfm::Expr::AxisRef::Position::Name(); }, org_context); }

void haxorg_destroy_TblfmExprAxisRefPositionName(OrgContext* org_context, haxorg_TblfmExprAxisRefPositionName* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::AxisRef::Position::Name>(org_context, obj); }

void haxorg_destroy_TblfmExprAxisRefPosition(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::AxisRef::Position>(org_context, obj); }

void haxorg_destroy_TblfmExprAxisRef(OrgContext* org_context, haxorg_TblfmExprAxisRef* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::AxisRef>(org_context, obj); }

void haxorg_destroy_TblfmExprAxisName(OrgContext* org_context, haxorg_TblfmExprAxisName* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::AxisName>(org_context, obj); }

void haxorg_destroy_TblfmExprIntLiteral(OrgContext* org_context, haxorg_TblfmExprIntLiteral* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::IntLiteral>(org_context, obj); }

void haxorg_destroy_TblfmExprFloatLiteral(OrgContext* org_context, haxorg_TblfmExprFloatLiteral* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::FloatLiteral>(org_context, obj); }

void haxorg_destroy_TblfmExprRangeRef(OrgContext* org_context, haxorg_TblfmExprRangeRef* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::RangeRef>(org_context, obj); }

void haxorg_destroy_TblfmExprCall(OrgContext* org_context, haxorg_TblfmExprCall* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::Call>(org_context, obj); }

void haxorg_destroy_TblfmExprElisp(OrgContext* org_context, haxorg_TblfmExprElisp* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::Elisp>(org_context, obj); }

void haxorg_destroy_TblfmExpr(OrgContext* org_context, haxorg_TblfmExpr* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr>(org_context, obj); }

void haxorg_destroy_TblfmAssign(OrgContext* org_context, haxorg_TblfmAssign* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Assign>(org_context, obj); }

void haxorg_destroy_Tblfm(OrgContext* org_context, haxorg_Tblfm* obj) { org::bind::c::execute_destroy<org::sem::Tblfm>(org_context, obj); }

void haxorg_create_AttrValue_AttrValue(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::AttrValue { return org::sem::AttrValue(); }, org_context); }

void haxorg_create_AttrValueDimensionSpan_DimensionSpan(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::AttrValue::DimensionSpan { return org::sem::AttrValue::DimensionSpan(); }, org_context); }

void haxorg_destroy_AttrValueDimensionSpan(OrgContext* org_context, haxorg_AttrValueDimensionSpan* obj) { org::bind::c::execute_destroy<org::sem::AttrValue::DimensionSpan>(org_context, obj); }

void haxorg_create_AttrValueTextValue_TextValue(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::AttrValue::TextValue { return org::sem::AttrValue::TextValue(); }, org_context); }

void haxorg_destroy_AttrValueTextValue(OrgContext* org_context, haxorg_AttrValueTextValue* obj) { org::bind::c::execute_destroy<org::sem::AttrValue::TextValue>(org_context, obj); }

void haxorg_create_AttrValueFileReference_FileReference(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::AttrValue::FileReference { return org::sem::AttrValue::FileReference(); }, org_context); }

void haxorg_destroy_AttrValueFileReference(OrgContext* org_context, haxorg_AttrValueFileReference* obj) { org::bind::c::execute_destroy<org::sem::AttrValue::FileReference>(org_context, obj); }

void haxorg_create_AttrValueLispValue_LispValue(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::AttrValue::LispValue { return org::sem::AttrValue::LispValue(); }, org_context); }

void haxorg_destroy_AttrValueLispValue(OrgContext* org_context, haxorg_AttrValueLispValue* obj) { org::bind::c::execute_destroy<org::sem::AttrValue::LispValue>(org_context, obj); }

void haxorg_destroy_AttrValue(OrgContext* org_context, haxorg_AttrValue* obj) { org::bind::c::execute_destroy<org::sem::AttrValue>(org_context, obj); }

void haxorg_destroy_HashTagFlat(OrgContext* org_context, haxorg_HashTagFlat* obj) { org::bind::c::execute_destroy<org::sem::HashTagFlat>(org_context, obj); }

void haxorg_destroy_TodoKeyword(OrgContext* org_context, haxorg_TodoKeyword* obj) { org::bind::c::execute_destroy<org::sem::TodoKeyword>(org_context, obj); }

void haxorg_destroy_HashTagText(OrgContext* org_context, haxorg_HashTagText* obj) { org::bind::c::execute_destroy<org::sem::HashTagText>(org_context, obj); }

void haxorg_destroy_SubtreePath(OrgContext* org_context, haxorg_SubtreePath* obj) { org::bind::c::execute_destroy<org::sem::SubtreePath>(org_context, obj); }

void haxorg_destroy_LinkTargetRaw(OrgContext* org_context, haxorg_LinkTargetRaw* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::Raw>(org_context, obj); }

void haxorg_destroy_LinkTargetId(OrgContext* org_context, haxorg_LinkTargetId* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::Id>(org_context, obj); }

void haxorg_destroy_LinkTargetCustomId(OrgContext* org_context, haxorg_LinkTargetCustomId* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::CustomId>(org_context, obj); }

void haxorg_destroy_LinkTargetSubtreeTitle(OrgContext* org_context, haxorg_LinkTargetSubtreeTitle* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::SubtreeTitle>(org_context, obj); }

void haxorg_destroy_LinkTargetPerson(OrgContext* org_context, haxorg_LinkTargetPerson* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::Person>(org_context, obj); }

void haxorg_destroy_LinkTargetUserProtocol(OrgContext* org_context, haxorg_LinkTargetUserProtocol* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::UserProtocol>(org_context, obj); }

void haxorg_destroy_LinkTargetInternal(OrgContext* org_context, haxorg_LinkTargetInternal* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::Internal>(org_context, obj); }

void haxorg_destroy_LinkTargetFootnote(OrgContext* org_context, haxorg_LinkTargetFootnote* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::Footnote>(org_context, obj); }

void haxorg_destroy_LinkTargetFile(OrgContext* org_context, haxorg_LinkTargetFile* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::File>(org_context, obj); }

void haxorg_destroy_LinkTargetAttachment(OrgContext* org_context, haxorg_LinkTargetAttachment* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::Attachment>(org_context, obj); }

void haxorg_destroy_LinkTarget(OrgContext* org_context, haxorg_LinkTarget* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget>(org_context, obj); }

void haxorg_destroy_SubtreeLogHeadPriority(OrgContext* org_context, haxorg_SubtreeLogHeadPriority* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Priority>(org_context, obj); }

void haxorg_destroy_SubtreeLogHeadNote(OrgContext* org_context, haxorg_SubtreeLogHeadNote* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Note>(org_context, obj); }

void haxorg_destroy_SubtreeLogHeadRefile(OrgContext* org_context, haxorg_SubtreeLogHeadRefile* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Refile>(org_context, obj); }

void haxorg_destroy_SubtreeLogHeadClock(OrgContext* org_context, haxorg_SubtreeLogHeadClock* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Clock>(org_context, obj); }

void haxorg_destroy_SubtreeLogHeadState(OrgContext* org_context, haxorg_SubtreeLogHeadState* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::State>(org_context, obj); }

void haxorg_destroy_SubtreeLogHeadDeadline(OrgContext* org_context, haxorg_SubtreeLogHeadDeadline* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Deadline>(org_context, obj); }

void haxorg_destroy_SubtreeLogHeadSchedule(OrgContext* org_context, haxorg_SubtreeLogHeadSchedule* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Schedule>(org_context, obj); }

void haxorg_destroy_SubtreeLogHeadTag(OrgContext* org_context, haxorg_SubtreeLogHeadTag* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Tag>(org_context, obj); }

void haxorg_destroy_SubtreeLogHeadUnknown(OrgContext* org_context, haxorg_SubtreeLogHeadUnknown* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Unknown>(org_context, obj); }

void haxorg_destroy_SubtreeLogHead(OrgContext* org_context, haxorg_SubtreeLogHead* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead>(org_context, obj); }

void haxorg_destroy_SubtreeCompletion(OrgContext* org_context, haxorg_SubtreeCompletion* obj) { org::bind::c::execute_destroy<org::sem::SubtreeCompletion>(org_context, obj); }

void haxorg_destroy_AttrList(OrgContext* org_context, haxorg_AttrList* obj) { org::bind::c::execute_destroy<org::sem::AttrList>(org_context, obj); }

void haxorg_destroy_AttrGroup(OrgContext* org_context, haxorg_AttrGroup* obj) { org::bind::c::execute_destroy<org::sem::AttrGroup>(org_context, obj); }

void haxorg_create_OrgCodeEvalInputVar_Var(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::OrgCodeEvalInput::Var { return org::sem::OrgCodeEvalInput::Var(); }, org_context); }

void haxorg_destroy_OrgCodeEvalInputVar(OrgContext* org_context, haxorg_OrgCodeEvalInputVar* obj) { org::bind::c::execute_destroy<org::sem::OrgCodeEvalInput::Var>(org_context, obj); }

void haxorg_destroy_OrgCodeEvalInput(OrgContext* org_context, haxorg_OrgCodeEvalInput* obj) { org::bind::c::execute_destroy<org::sem::OrgCodeEvalInput>(org_context, obj); }

void haxorg_destroy_OrgCodeEvalOutput(OrgContext* org_context, haxorg_OrgCodeEvalOutput* obj) { org::bind::c::execute_destroy<org::sem::OrgCodeEvalOutput>(org_context, obj); }

void haxorg_destroy_ColumnViewSummaryCheckboxAggregate(OrgContext* org_context, haxorg_ColumnViewSummaryCheckboxAggregate* obj) { org::bind::c::execute_destroy<org::sem::ColumnView::Summary::CheckboxAggregate>(org_context, obj); }

void haxorg_destroy_ColumnViewSummaryMathAggregate(OrgContext* org_context, haxorg_ColumnViewSummaryMathAggregate* obj) { org::bind::c::execute_destroy<org::sem::ColumnView::Summary::MathAggregate>(org_context, obj); }

void haxorg_destroy_ColumnViewSummary(OrgContext* org_context, haxorg_ColumnViewSummary* obj) { org::bind::c::execute_destroy<org::sem::ColumnView::Summary>(org_context, obj); }

void haxorg_destroy_ColumnViewColumn(OrgContext* org_context, haxorg_ColumnViewColumn* obj) { org::bind::c::execute_destroy<org::sem::ColumnView::Column>(org_context, obj); }

void haxorg_destroy_ColumnView(OrgContext* org_context, haxorg_ColumnView* obj) { org::bind::c::execute_destroy<org::sem::ColumnView>(org_context, obj); }

void haxorg_destroy_BlockCodeLinePartRaw(OrgContext* org_context, haxorg_BlockCodeLinePartRaw* obj) { org::bind::c::execute_destroy<org::sem::BlockCodeLine::Part::Raw>(org_context, obj); }

void haxorg_destroy_BlockCodeLinePartCallout(OrgContext* org_context, haxorg_BlockCodeLinePartCallout* obj) { org::bind::c::execute_destroy<org::sem::BlockCodeLine::Part::Callout>(org_context, obj); }

void haxorg_destroy_BlockCodeLinePartTangle(OrgContext* org_context, haxorg_BlockCodeLinePartTangle* obj) { org::bind::c::execute_destroy<org::sem::BlockCodeLine::Part::Tangle>(org_context, obj); }

void haxorg_destroy_BlockCodeLinePart(OrgContext* org_context, haxorg_BlockCodeLinePart* obj) { org::bind::c::execute_destroy<org::sem::BlockCodeLine::Part>(org_context, obj); }

void haxorg_destroy_BlockCodeLine(OrgContext* org_context, haxorg_BlockCodeLine* obj) { org::bind::c::execute_destroy<org::sem::BlockCodeLine>(org_context, obj); }

void haxorg_destroy_DocumentExportConfigTaskExport(OrgContext* org_context, haxorg_DocumentExportConfigTaskExport* obj) { org::bind::c::execute_destroy<org::sem::DocumentExportConfig::TaskExport>(org_context, obj); }

void haxorg_destroy_DocumentExportConfigDoExport(OrgContext* org_context, haxorg_DocumentExportConfigDoExport* obj) { org::bind::c::execute_destroy<org::sem::DocumentExportConfig::DoExport>(org_context, obj); }

void haxorg_destroy_DocumentExportConfigExportFixed(OrgContext* org_context, haxorg_DocumentExportConfigExportFixed* obj) { org::bind::c::execute_destroy<org::sem::DocumentExportConfig::ExportFixed>(org_context, obj); }

void haxorg_destroy_DocumentExportConfig(OrgContext* org_context, haxorg_DocumentExportConfig* obj) { org::bind::c::execute_destroy<org::sem::DocumentExportConfig>(org_context, obj); }

void haxorg_destroy_SubtreePeriod(OrgContext* org_context, haxorg_SubtreePeriod* obj) { org::bind::c::execute_destroy<org::sem::SubtreePeriod>(org_context, obj); }

void haxorg_destroy_NamedPropertyNonblocking(OrgContext* org_context, haxorg_NamedPropertyNonblocking* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Nonblocking>(org_context, obj); }

void haxorg_destroy_NamedPropertyArchiveTime(OrgContext* org_context, haxorg_NamedPropertyArchiveTime* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ArchiveTime>(org_context, obj); }

void haxorg_destroy_NamedPropertyArchiveFile(OrgContext* org_context, haxorg_NamedPropertyArchiveFile* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ArchiveFile>(org_context, obj); }

void haxorg_destroy_NamedPropertyArchiveOlpath(OrgContext* org_context, haxorg_NamedPropertyArchiveOlpath* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ArchiveOlpath>(org_context, obj); }

void haxorg_destroy_NamedPropertyArchiveTarget(OrgContext* org_context, haxorg_NamedPropertyArchiveTarget* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ArchiveTarget>(org_context, obj); }

void haxorg_destroy_NamedPropertyArchiveCategory(OrgContext* org_context, haxorg_NamedPropertyArchiveCategory* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ArchiveCategory>(org_context, obj); }

void haxorg_destroy_NamedPropertyArchiveTodo(OrgContext* org_context, haxorg_NamedPropertyArchiveTodo* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ArchiveTodo>(org_context, obj); }

void haxorg_destroy_NamedPropertyTrigger(OrgContext* org_context, haxorg_NamedPropertyTrigger* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Trigger>(org_context, obj); }

void haxorg_destroy_NamedPropertyExportLatexClass(OrgContext* org_context, haxorg_NamedPropertyExportLatexClass* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ExportLatexClass>(org_context, obj); }

void haxorg_destroy_NamedPropertyCookieData(OrgContext* org_context, haxorg_NamedPropertyCookieData* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::CookieData>(org_context, obj); }

void haxorg_destroy_NamedPropertyExportLatexClassOptions(OrgContext* org_context, haxorg_NamedPropertyExportLatexClassOptions* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ExportLatexClassOptions>(org_context, obj); }

void haxorg_destroy_NamedPropertyExportLatexHeader(OrgContext* org_context, haxorg_NamedPropertyExportLatexHeader* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ExportLatexHeader>(org_context, obj); }

void haxorg_destroy_NamedPropertyExportLatexCompiler(OrgContext* org_context, haxorg_NamedPropertyExportLatexCompiler* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ExportLatexCompiler>(org_context, obj); }

void haxorg_destroy_NamedPropertyOrdered(OrgContext* org_context, haxorg_NamedPropertyOrdered* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Ordered>(org_context, obj); }

void haxorg_destroy_NamedPropertyEffort(OrgContext* org_context, haxorg_NamedPropertyEffort* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Effort>(org_context, obj); }

void haxorg_destroy_NamedPropertyVisibility(OrgContext* org_context, haxorg_NamedPropertyVisibility* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Visibility>(org_context, obj); }

void haxorg_destroy_NamedPropertyExportOptions(OrgContext* org_context, haxorg_NamedPropertyExportOptions* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ExportOptions>(org_context, obj); }

void haxorg_destroy_NamedPropertyBlocker(OrgContext* org_context, haxorg_NamedPropertyBlocker* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Blocker>(org_context, obj); }

void haxorg_destroy_NamedPropertyUnnumbered(OrgContext* org_context, haxorg_NamedPropertyUnnumbered* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Unnumbered>(org_context, obj); }

void haxorg_destroy_NamedPropertyCreated(OrgContext* org_context, haxorg_NamedPropertyCreated* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Created>(org_context, obj); }

void haxorg_destroy_NamedPropertyRadioId(OrgContext* org_context, haxorg_NamedPropertyRadioId* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::RadioId>(org_context, obj); }

void haxorg_destroy_NamedPropertyHashtagDef(OrgContext* org_context, haxorg_NamedPropertyHashtagDef* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::HashtagDef>(org_context, obj); }

void haxorg_destroy_NamedPropertyCustomArgs(OrgContext* org_context, haxorg_NamedPropertyCustomArgs* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::CustomArgs>(org_context, obj); }

void haxorg_destroy_NamedPropertyCustomRaw(OrgContext* org_context, haxorg_NamedPropertyCustomRaw* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::CustomRaw>(org_context, obj); }

void haxorg_destroy_NamedPropertyCustomId(OrgContext* org_context, haxorg_NamedPropertyCustomId* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::CustomId>(org_context, obj); }

void haxorg_destroy_NamedPropertyCustomSubtreeJson(OrgContext* org_context, haxorg_NamedPropertyCustomSubtreeJson* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::CustomSubtreeJson>(org_context, obj); }

void haxorg_destroy_NamedPropertyCustomSubtreeFlags(OrgContext* org_context, haxorg_NamedPropertyCustomSubtreeFlags* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::CustomSubtreeFlags>(org_context, obj); }

void haxorg_destroy_NamedProperty(OrgContext* org_context, haxorg_NamedProperty* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty>(org_context, obj); }

void haxorg_destroy_OrgDiagnosticsParseTokenError(OrgContext* org_context, haxorg_OrgDiagnosticsParseTokenError* obj) { org::bind::c::execute_destroy<org::sem::OrgDiagnostics::ParseTokenError>(org_context, obj); }

void haxorg_destroy_OrgDiagnosticsParseError(OrgContext* org_context, haxorg_OrgDiagnosticsParseError* obj) { org::bind::c::execute_destroy<org::sem::OrgDiagnostics::ParseError>(org_context, obj); }

void haxorg_destroy_OrgDiagnosticsIncludeError(OrgContext* org_context, haxorg_OrgDiagnosticsIncludeError* obj) { org::bind::c::execute_destroy<org::sem::OrgDiagnostics::IncludeError>(org_context, obj); }

void haxorg_destroy_OrgDiagnosticsConvertError(OrgContext* org_context, haxorg_OrgDiagnosticsConvertError* obj) { org::bind::c::execute_destroy<org::sem::OrgDiagnostics::ConvertError>(org_context, obj); }

void haxorg_destroy_OrgDiagnosticsInternalError(OrgContext* org_context, haxorg_OrgDiagnosticsInternalError* obj) { org::bind::c::execute_destroy<org::sem::OrgDiagnostics::InternalError>(org_context, obj); }

void haxorg_destroy_OrgDiagnostics(OrgContext* org_context, haxorg_OrgDiagnostics* obj) { org::bind::c::execute_destroy<org::sem::OrgDiagnostics>(org_context, obj); }

void haxorg_destroy_NoNode(OrgContext* org_context, haxorg_NoNode* obj) { org::bind::c::execute_destroy<org::sem::NoNode>(org_context, obj); }

void haxorg_destroy_ErrorItem(OrgContext* org_context, haxorg_ErrorItem* obj) { org::bind::c::execute_destroy<org::sem::ErrorItem>(org_context, obj); }

void haxorg_destroy_ErrorGroup(OrgContext* org_context, haxorg_ErrorGroup* obj) { org::bind::c::execute_destroy<org::sem::ErrorGroup>(org_context, obj); }

void haxorg_destroy_Stmt(OrgContext* org_context, haxorg_Stmt* obj) { org::bind::c::execute_destroy<org::sem::Stmt>(org_context, obj); }

void haxorg_destroy_Inline(OrgContext* org_context, haxorg_Inline* obj) { org::bind::c::execute_destroy<org::sem::Inline>(org_context, obj); }

void haxorg_destroy_StmtList(OrgContext* org_context, haxorg_StmtList* obj) { org::bind::c::execute_destroy<org::sem::StmtList>(org_context, obj); }

void haxorg_destroy_Empty(OrgContext* org_context, haxorg_Empty* obj) { org::bind::c::execute_destroy<org::sem::Empty>(org_context, obj); }

void haxorg_destroy_Leaf(OrgContext* org_context, haxorg_Leaf* obj) { org::bind::c::execute_destroy<org::sem::Leaf>(org_context, obj); }

void haxorg_destroy_TimeRepeat(OrgContext* org_context, haxorg_TimeRepeat* obj) { org::bind::c::execute_destroy<org::sem::Time::Repeat>(org_context, obj); }

void haxorg_create_TimeStatic_Static(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::Time::Static { return org::sem::Time::Static(); }, org_context); }

void haxorg_destroy_TimeStatic(OrgContext* org_context, haxorg_TimeStatic* obj) { org::bind::c::execute_destroy<org::sem::Time::Static>(org_context, obj); }

void haxorg_create_TimeDynamic_Dynamic(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::sem::Time::Dynamic { return org::sem::Time::Dynamic(); }, org_context); }

void haxorg_destroy_TimeDynamic(OrgContext* org_context, haxorg_TimeDynamic* obj) { org::bind::c::execute_destroy<org::sem::Time::Dynamic>(org_context, obj); }

void haxorg_destroy_Time(OrgContext* org_context, haxorg_Time* obj) { org::bind::c::execute_destroy<org::sem::Time>(org_context, obj); }

void haxorg_destroy_TimeRange(OrgContext* org_context, haxorg_TimeRange* obj) { org::bind::c::execute_destroy<org::sem::TimeRange>(org_context, obj); }

void haxorg_destroy_Macro(OrgContext* org_context, haxorg_Macro* obj) { org::bind::c::execute_destroy<org::sem::Macro>(org_context, obj); }

void haxorg_destroy_SymbolParam(OrgContext* org_context, haxorg_SymbolParam* obj) { org::bind::c::execute_destroy<org::sem::Symbol::Param>(org_context, obj); }

void haxorg_destroy_Symbol(OrgContext* org_context, haxorg_Symbol* obj) { org::bind::c::execute_destroy<org::sem::Symbol>(org_context, obj); }

void haxorg_destroy_ErrorSkipGroup(OrgContext* org_context, haxorg_ErrorSkipGroup* obj) { org::bind::c::execute_destroy<org::sem::ErrorSkipGroup>(org_context, obj); }

void haxorg_destroy_Markup(OrgContext* org_context, haxorg_Markup* obj) { org::bind::c::execute_destroy<org::sem::Markup>(org_context, obj); }

void haxorg_destroy_RadioTarget(OrgContext* org_context, haxorg_RadioTarget* obj) { org::bind::c::execute_destroy<org::sem::RadioTarget>(org_context, obj); }

void haxorg_destroy_Latex(OrgContext* org_context, haxorg_Latex* obj) { org::bind::c::execute_destroy<org::sem::Latex>(org_context, obj); }

void haxorg_destroy_SubtreeLog(OrgContext* org_context, haxorg_SubtreeLog* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLog>(org_context, obj); }

void haxorg_destroy_Subtree(OrgContext* org_context, haxorg_Subtree* obj) { org::bind::c::execute_destroy<org::sem::Subtree>(org_context, obj); }

void haxorg_destroy_ColonExample(OrgContext* org_context, haxorg_ColonExample* obj) { org::bind::c::execute_destroy<org::sem::ColonExample>(org_context, obj); }

void haxorg_destroy_Call(OrgContext* org_context, haxorg_Call* obj) { org::bind::c::execute_destroy<org::sem::Call>(org_context, obj); }

void haxorg_destroy_ListItem(OrgContext* org_context, haxorg_ListItem* obj) { org::bind::c::execute_destroy<org::sem::ListItem>(org_context, obj); }

void haxorg_destroy_DocumentOptions(OrgContext* org_context, haxorg_DocumentOptions* obj) { org::bind::c::execute_destroy<org::sem::DocumentOptions>(org_context, obj); }

void haxorg_destroy_DocumentFragment(OrgContext* org_context, haxorg_DocumentFragment* obj) { org::bind::c::execute_destroy<org::sem::DocumentFragment>(org_context, obj); }

void haxorg_destroy_CriticMarkup(OrgContext* org_context, haxorg_CriticMarkup* obj) { org::bind::c::execute_destroy<org::sem::CriticMarkup>(org_context, obj); }

void haxorg_destroy_Document(OrgContext* org_context, haxorg_Document* obj) { org::bind::c::execute_destroy<org::sem::Document>(org_context, obj); }

void haxorg_destroy_FileTarget(OrgContext* org_context, haxorg_FileTarget* obj) { org::bind::c::execute_destroy<org::sem::FileTarget>(org_context, obj); }

void haxorg_destroy_TextSeparator(OrgContext* org_context, haxorg_TextSeparator* obj) { org::bind::c::execute_destroy<org::sem::TextSeparator>(org_context, obj); }

void haxorg_destroy_DocumentGroup(OrgContext* org_context, haxorg_DocumentGroup* obj) { org::bind::c::execute_destroy<org::sem::DocumentGroup>(org_context, obj); }

void haxorg_destroy_FileDocument(OrgContext* org_context, haxorg_FileDocument* obj) { org::bind::c::execute_destroy<org::sem::File::Document>(org_context, obj); }

void haxorg_destroy_FileAttachment(OrgContext* org_context, haxorg_FileAttachment* obj) { org::bind::c::execute_destroy<org::sem::File::Attachment>(org_context, obj); }

void haxorg_destroy_FileSource(OrgContext* org_context, haxorg_FileSource* obj) { org::bind::c::execute_destroy<org::sem::File::Source>(org_context, obj); }

void haxorg_destroy_File(OrgContext* org_context, haxorg_File* obj) { org::bind::c::execute_destroy<org::sem::File>(org_context, obj); }

void haxorg_destroy_Directory(OrgContext* org_context, haxorg_Directory* obj) { org::bind::c::execute_destroy<org::sem::Directory>(org_context, obj); }

void haxorg_destroy_Symlink(OrgContext* org_context, haxorg_Symlink* obj) { org::bind::c::execute_destroy<org::sem::Symlink>(org_context, obj); }

void haxorg_destroy_CmdIncludeIncludeBase(OrgContext* org_context, haxorg_CmdIncludeIncludeBase* obj) { org::bind::c::execute_destroy<org::sem::CmdInclude::IncludeBase>(org_context, obj); }

void haxorg_destroy_CmdIncludeExample(OrgContext* org_context, haxorg_CmdIncludeExample* obj) { org::bind::c::execute_destroy<org::sem::CmdInclude::Example>(org_context, obj); }

void haxorg_destroy_CmdIncludeExport(OrgContext* org_context, haxorg_CmdIncludeExport* obj) { org::bind::c::execute_destroy<org::sem::CmdInclude::Export>(org_context, obj); }

void haxorg_destroy_CmdIncludeCustom(OrgContext* org_context, haxorg_CmdIncludeCustom* obj) { org::bind::c::execute_destroy<org::sem::CmdInclude::Custom>(org_context, obj); }

void haxorg_destroy_CmdIncludeSrc(OrgContext* org_context, haxorg_CmdIncludeSrc* obj) { org::bind::c::execute_destroy<org::sem::CmdInclude::Src>(org_context, obj); }

void haxorg_destroy_CmdIncludeOrgDocument(OrgContext* org_context, haxorg_CmdIncludeOrgDocument* obj) { org::bind::c::execute_destroy<org::sem::CmdInclude::OrgDocument>(org_context, obj); }

void haxorg_destroy_CmdInclude(OrgContext* org_context, haxorg_CmdInclude* obj) { org::bind::c::execute_destroy<org::sem::CmdInclude>(org_context, obj); }

void haxorg_destroy_ImmNoNode(OrgContext* org_context, haxorg_ImmNoNode* obj) { org::bind::c::execute_destroy<org::imm::ImmNoNode>(org_context, obj); }

void haxorg_destroy_ImmErrorItem(OrgContext* org_context, haxorg_ImmErrorItem* obj) { org::bind::c::execute_destroy<org::imm::ImmErrorItem>(org_context, obj); }

void haxorg_destroy_ImmErrorGroup(OrgContext* org_context, haxorg_ImmErrorGroup* obj) { org::bind::c::execute_destroy<org::imm::ImmErrorGroup>(org_context, obj); }

void haxorg_destroy_ImmStmt(OrgContext* org_context, haxorg_ImmStmt* obj) { org::bind::c::execute_destroy<org::imm::ImmStmt>(org_context, obj); }

void haxorg_destroy_ImmInline(OrgContext* org_context, haxorg_ImmInline* obj) { org::bind::c::execute_destroy<org::imm::ImmInline>(org_context, obj); }

void haxorg_destroy_ImmStmtList(OrgContext* org_context, haxorg_ImmStmtList* obj) { org::bind::c::execute_destroy<org::imm::ImmStmtList>(org_context, obj); }

void haxorg_destroy_ImmEmpty(OrgContext* org_context, haxorg_ImmEmpty* obj) { org::bind::c::execute_destroy<org::imm::ImmEmpty>(org_context, obj); }

void haxorg_destroy_ImmLeaf(OrgContext* org_context, haxorg_ImmLeaf* obj) { org::bind::c::execute_destroy<org::imm::ImmLeaf>(org_context, obj); }

void haxorg_destroy_ImmTimeRepeat(OrgContext* org_context, haxorg_ImmTimeRepeat* obj) { org::bind::c::execute_destroy<org::imm::ImmTime::Repeat>(org_context, obj); }

void haxorg_create_ImmTimeStatic_Static(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::imm::ImmTime::Static { return org::imm::ImmTime::Static(); }, org_context); }

void haxorg_destroy_ImmTimeStatic(OrgContext* org_context, haxorg_ImmTimeStatic* obj) { org::bind::c::execute_destroy<org::imm::ImmTime::Static>(org_context, obj); }

void haxorg_create_ImmTimeDynamic_Dynamic(OrgContext* org_context) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[]() -> org::imm::ImmTime::Dynamic { return org::imm::ImmTime::Dynamic(); }, org_context); }

void haxorg_destroy_ImmTimeDynamic(OrgContext* org_context, haxorg_ImmTimeDynamic* obj) { org::bind::c::execute_destroy<org::imm::ImmTime::Dynamic>(org_context, obj); }

void haxorg_destroy_ImmTime(OrgContext* org_context, haxorg_ImmTime* obj) { org::bind::c::execute_destroy<org::imm::ImmTime>(org_context, obj); }

void haxorg_destroy_ImmTimeRange(OrgContext* org_context, haxorg_ImmTimeRange* obj) { org::bind::c::execute_destroy<org::imm::ImmTimeRange>(org_context, obj); }

void haxorg_destroy_ImmMacro(OrgContext* org_context, haxorg_ImmMacro* obj) { org::bind::c::execute_destroy<org::imm::ImmMacro>(org_context, obj); }

void haxorg_destroy_ImmSymbolParam(OrgContext* org_context, haxorg_ImmSymbolParam* obj) { org::bind::c::execute_destroy<org::imm::ImmSymbol::Param>(org_context, obj); }

void haxorg_destroy_ImmSymbol(OrgContext* org_context, haxorg_ImmSymbol* obj) { org::bind::c::execute_destroy<org::imm::ImmSymbol>(org_context, obj); }

void haxorg_destroy_ImmErrorSkipGroup(OrgContext* org_context, haxorg_ImmErrorSkipGroup* obj) { org::bind::c::execute_destroy<org::imm::ImmErrorSkipGroup>(org_context, obj); }

void haxorg_destroy_ImmMarkup(OrgContext* org_context, haxorg_ImmMarkup* obj) { org::bind::c::execute_destroy<org::imm::ImmMarkup>(org_context, obj); }

void haxorg_destroy_ImmRadioTarget(OrgContext* org_context, haxorg_ImmRadioTarget* obj) { org::bind::c::execute_destroy<org::imm::ImmRadioTarget>(org_context, obj); }

void haxorg_destroy_ImmLatex(OrgContext* org_context, haxorg_ImmLatex* obj) { org::bind::c::execute_destroy<org::imm::ImmLatex>(org_context, obj); }

void haxorg_destroy_ImmSubtreeLog(OrgContext* org_context, haxorg_ImmSubtreeLog* obj) { org::bind::c::execute_destroy<org::imm::ImmSubtreeLog>(org_context, obj); }

void haxorg_destroy_ImmSubtree(OrgContext* org_context, haxorg_ImmSubtree* obj) { org::bind::c::execute_destroy<org::imm::ImmSubtree>(org_context, obj); }

void haxorg_destroy_ImmColonExample(OrgContext* org_context, haxorg_ImmColonExample* obj) { org::bind::c::execute_destroy<org::imm::ImmColonExample>(org_context, obj); }

void haxorg_destroy_ImmCall(OrgContext* org_context, haxorg_ImmCall* obj) { org::bind::c::execute_destroy<org::imm::ImmCall>(org_context, obj); }

void haxorg_destroy_ImmListItem(OrgContext* org_context, haxorg_ImmListItem* obj) { org::bind::c::execute_destroy<org::imm::ImmListItem>(org_context, obj); }

void haxorg_destroy_ImmDocumentOptions(OrgContext* org_context, haxorg_ImmDocumentOptions* obj) { org::bind::c::execute_destroy<org::imm::ImmDocumentOptions>(org_context, obj); }

void haxorg_destroy_ImmDocumentFragment(OrgContext* org_context, haxorg_ImmDocumentFragment* obj) { org::bind::c::execute_destroy<org::imm::ImmDocumentFragment>(org_context, obj); }

void haxorg_destroy_ImmCriticMarkup(OrgContext* org_context, haxorg_ImmCriticMarkup* obj) { org::bind::c::execute_destroy<org::imm::ImmCriticMarkup>(org_context, obj); }

void haxorg_destroy_ImmDocument(OrgContext* org_context, haxorg_ImmDocument* obj) { org::bind::c::execute_destroy<org::imm::ImmDocument>(org_context, obj); }

void haxorg_destroy_ImmFileTarget(OrgContext* org_context, haxorg_ImmFileTarget* obj) { org::bind::c::execute_destroy<org::imm::ImmFileTarget>(org_context, obj); }

void haxorg_destroy_ImmTextSeparator(OrgContext* org_context, haxorg_ImmTextSeparator* obj) { org::bind::c::execute_destroy<org::imm::ImmTextSeparator>(org_context, obj); }

void haxorg_destroy_ImmDocumentGroup(OrgContext* org_context, haxorg_ImmDocumentGroup* obj) { org::bind::c::execute_destroy<org::imm::ImmDocumentGroup>(org_context, obj); }

void haxorg_destroy_ImmFileDocument(OrgContext* org_context, haxorg_ImmFileDocument* obj) { org::bind::c::execute_destroy<org::imm::ImmFile::Document>(org_context, obj); }

void haxorg_destroy_ImmFileAttachment(OrgContext* org_context, haxorg_ImmFileAttachment* obj) { org::bind::c::execute_destroy<org::imm::ImmFile::Attachment>(org_context, obj); }

void haxorg_destroy_ImmFileSource(OrgContext* org_context, haxorg_ImmFileSource* obj) { org::bind::c::execute_destroy<org::imm::ImmFile::Source>(org_context, obj); }

void haxorg_destroy_ImmFile(OrgContext* org_context, haxorg_ImmFile* obj) { org::bind::c::execute_destroy<org::imm::ImmFile>(org_context, obj); }

void haxorg_destroy_ImmDirectory(OrgContext* org_context, haxorg_ImmDirectory* obj) { org::bind::c::execute_destroy<org::imm::ImmDirectory>(org_context, obj); }

void haxorg_destroy_ImmSymlink(OrgContext* org_context, haxorg_ImmSymlink* obj) { org::bind::c::execute_destroy<org::imm::ImmSymlink>(org_context, obj); }

void haxorg_destroy_ImmCmdIncludeIncludeBase(OrgContext* org_context, haxorg_ImmCmdIncludeIncludeBase* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdInclude::IncludeBase>(org_context, obj); }

void haxorg_destroy_ImmCmdIncludeExample(OrgContext* org_context, haxorg_ImmCmdIncludeExample* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdInclude::Example>(org_context, obj); }

void haxorg_destroy_ImmCmdIncludeExport(OrgContext* org_context, haxorg_ImmCmdIncludeExport* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdInclude::Export>(org_context, obj); }

void haxorg_destroy_ImmCmdIncludeCustom(OrgContext* org_context, haxorg_ImmCmdIncludeCustom* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdInclude::Custom>(org_context, obj); }

void haxorg_destroy_ImmCmdIncludeSrc(OrgContext* org_context, haxorg_ImmCmdIncludeSrc* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdInclude::Src>(org_context, obj); }

void haxorg_destroy_ImmCmdIncludeOrgDocument(OrgContext* org_context, haxorg_ImmCmdIncludeOrgDocument* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdInclude::OrgDocument>(org_context, obj); }

void haxorg_destroy_ImmCmdInclude(OrgContext* org_context, haxorg_ImmCmdInclude* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdInclude>(org_context, obj); }

void haxorg_destroy_ImmAdapterOrgAPI(OrgContext* org_context, haxorg_ImmAdapterOrgAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterOrgAPI>(org_context, obj); }

void haxorg_destroy_Cmd(OrgContext* org_context, haxorg_Cmd* obj) { org::bind::c::execute_destroy<org::sem::Cmd>(org_context, obj); }

void haxorg_destroy_CmdCustomRaw(OrgContext* org_context, haxorg_CmdCustomRaw* obj) { org::bind::c::execute_destroy<org::sem::CmdCustomRaw>(org_context, obj); }

void haxorg_destroy_CmdCustomText(OrgContext* org_context, haxorg_CmdCustomText* obj) { org::bind::c::execute_destroy<org::sem::CmdCustomText>(org_context, obj); }

void haxorg_destroy_Link(OrgContext* org_context, haxorg_Link* obj) { org::bind::c::execute_destroy<org::sem::Link>(org_context, obj); }

void haxorg_destroy_BlockComment(OrgContext* org_context, haxorg_BlockComment* obj) { org::bind::c::execute_destroy<org::sem::BlockComment>(org_context, obj); }

void haxorg_destroy_Paragraph(OrgContext* org_context, haxorg_Paragraph* obj) { org::bind::c::execute_destroy<org::sem::Paragraph>(org_context, obj); }

void haxorg_destroy_List(OrgContext* org_context, haxorg_List* obj) { org::bind::c::execute_destroy<org::sem::List>(org_context, obj); }

void haxorg_destroy_HashTag(OrgContext* org_context, haxorg_HashTag* obj) { org::bind::c::execute_destroy<org::sem::HashTag>(org_context, obj); }

void haxorg_destroy_InlineFootnote(OrgContext* org_context, haxorg_InlineFootnote* obj) { org::bind::c::execute_destroy<org::sem::InlineFootnote>(org_context, obj); }

void haxorg_destroy_InlineExport(OrgContext* org_context, haxorg_InlineExport* obj) { org::bind::c::execute_destroy<org::sem::InlineExport>(org_context, obj); }

void haxorg_destroy_Escaped(OrgContext* org_context, haxorg_Escaped* obj) { org::bind::c::execute_destroy<org::sem::Escaped>(org_context, obj); }

void haxorg_destroy_Newline(OrgContext* org_context, haxorg_Newline* obj) { org::bind::c::execute_destroy<org::sem::Newline>(org_context, obj); }

void haxorg_destroy_Space(OrgContext* org_context, haxorg_Space* obj) { org::bind::c::execute_destroy<org::sem::Space>(org_context, obj); }

void haxorg_destroy_Word(OrgContext* org_context, haxorg_Word* obj) { org::bind::c::execute_destroy<org::sem::Word>(org_context, obj); }

void haxorg_destroy_AtMention(OrgContext* org_context, haxorg_AtMention* obj) { org::bind::c::execute_destroy<org::sem::AtMention>(org_context, obj); }

void haxorg_destroy_RawText(OrgContext* org_context, haxorg_RawText* obj) { org::bind::c::execute_destroy<org::sem::RawText>(org_context, obj); }

void haxorg_destroy_Punctuation(OrgContext* org_context, haxorg_Punctuation* obj) { org::bind::c::execute_destroy<org::sem::Punctuation>(org_context, obj); }

void haxorg_destroy_Placeholder(OrgContext* org_context, haxorg_Placeholder* obj) { org::bind::c::execute_destroy<org::sem::Placeholder>(org_context, obj); }

void haxorg_destroy_BigIdent(OrgContext* org_context, haxorg_BigIdent* obj) { org::bind::c::execute_destroy<org::sem::BigIdent>(org_context, obj); }

void haxorg_destroy_TextTarget(OrgContext* org_context, haxorg_TextTarget* obj) { org::bind::c::execute_destroy<org::sem::TextTarget>(org_context, obj); }

void haxorg_destroy_ErrorSkipToken(OrgContext* org_context, haxorg_ErrorSkipToken* obj) { org::bind::c::execute_destroy<org::sem::ErrorSkipToken>(org_context, obj); }

void haxorg_destroy_Bold(OrgContext* org_context, haxorg_Bold* obj) { org::bind::c::execute_destroy<org::sem::Bold>(org_context, obj); }

void haxorg_destroy_Underline(OrgContext* org_context, haxorg_Underline* obj) { org::bind::c::execute_destroy<org::sem::Underline>(org_context, obj); }

void haxorg_destroy_Monospace(OrgContext* org_context, haxorg_Monospace* obj) { org::bind::c::execute_destroy<org::sem::Monospace>(org_context, obj); }

void haxorg_destroy_MarkQuote(OrgContext* org_context, haxorg_MarkQuote* obj) { org::bind::c::execute_destroy<org::sem::MarkQuote>(org_context, obj); }

void haxorg_destroy_Verbatim(OrgContext* org_context, haxorg_Verbatim* obj) { org::bind::c::execute_destroy<org::sem::Verbatim>(org_context, obj); }

void haxorg_destroy_Italic(OrgContext* org_context, haxorg_Italic* obj) { org::bind::c::execute_destroy<org::sem::Italic>(org_context, obj); }

void haxorg_destroy_Strike(OrgContext* org_context, haxorg_Strike* obj) { org::bind::c::execute_destroy<org::sem::Strike>(org_context, obj); }

void haxorg_destroy_Par(OrgContext* org_context, haxorg_Par* obj) { org::bind::c::execute_destroy<org::sem::Par>(org_context, obj); }

void haxorg_destroy_ImmCmd(OrgContext* org_context, haxorg_ImmCmd* obj) { org::bind::c::execute_destroy<org::imm::ImmCmd>(org_context, obj); }

void haxorg_destroy_ImmCmdCustomRaw(OrgContext* org_context, haxorg_ImmCmdCustomRaw* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdCustomRaw>(org_context, obj); }

void haxorg_destroy_ImmCmdCustomText(OrgContext* org_context, haxorg_ImmCmdCustomText* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdCustomText>(org_context, obj); }

void haxorg_destroy_ImmLink(OrgContext* org_context, haxorg_ImmLink* obj) { org::bind::c::execute_destroy<org::imm::ImmLink>(org_context, obj); }

void haxorg_destroy_ImmBlockComment(OrgContext* org_context, haxorg_ImmBlockComment* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockComment>(org_context, obj); }

void haxorg_destroy_ImmParagraph(OrgContext* org_context, haxorg_ImmParagraph* obj) { org::bind::c::execute_destroy<org::imm::ImmParagraph>(org_context, obj); }

void haxorg_destroy_ImmList(OrgContext* org_context, haxorg_ImmList* obj) { org::bind::c::execute_destroy<org::imm::ImmList>(org_context, obj); }

void haxorg_destroy_ImmHashTag(OrgContext* org_context, haxorg_ImmHashTag* obj) { org::bind::c::execute_destroy<org::imm::ImmHashTag>(org_context, obj); }

void haxorg_destroy_ImmInlineFootnote(OrgContext* org_context, haxorg_ImmInlineFootnote* obj) { org::bind::c::execute_destroy<org::imm::ImmInlineFootnote>(org_context, obj); }

void haxorg_destroy_ImmInlineExport(OrgContext* org_context, haxorg_ImmInlineExport* obj) { org::bind::c::execute_destroy<org::imm::ImmInlineExport>(org_context, obj); }

void haxorg_destroy_ImmEscaped(OrgContext* org_context, haxorg_ImmEscaped* obj) { org::bind::c::execute_destroy<org::imm::ImmEscaped>(org_context, obj); }

void haxorg_destroy_ImmNewline(OrgContext* org_context, haxorg_ImmNewline* obj) { org::bind::c::execute_destroy<org::imm::ImmNewline>(org_context, obj); }

void haxorg_destroy_ImmSpace(OrgContext* org_context, haxorg_ImmSpace* obj) { org::bind::c::execute_destroy<org::imm::ImmSpace>(org_context, obj); }

void haxorg_destroy_ImmWord(OrgContext* org_context, haxorg_ImmWord* obj) { org::bind::c::execute_destroy<org::imm::ImmWord>(org_context, obj); }

void haxorg_destroy_ImmAtMention(OrgContext* org_context, haxorg_ImmAtMention* obj) { org::bind::c::execute_destroy<org::imm::ImmAtMention>(org_context, obj); }

void haxorg_destroy_ImmRawText(OrgContext* org_context, haxorg_ImmRawText* obj) { org::bind::c::execute_destroy<org::imm::ImmRawText>(org_context, obj); }

void haxorg_destroy_ImmPunctuation(OrgContext* org_context, haxorg_ImmPunctuation* obj) { org::bind::c::execute_destroy<org::imm::ImmPunctuation>(org_context, obj); }

void haxorg_destroy_ImmPlaceholder(OrgContext* org_context, haxorg_ImmPlaceholder* obj) { org::bind::c::execute_destroy<org::imm::ImmPlaceholder>(org_context, obj); }

void haxorg_destroy_ImmBigIdent(OrgContext* org_context, haxorg_ImmBigIdent* obj) { org::bind::c::execute_destroy<org::imm::ImmBigIdent>(org_context, obj); }

void haxorg_destroy_ImmTextTarget(OrgContext* org_context, haxorg_ImmTextTarget* obj) { org::bind::c::execute_destroy<org::imm::ImmTextTarget>(org_context, obj); }

void haxorg_destroy_ImmErrorSkipToken(OrgContext* org_context, haxorg_ImmErrorSkipToken* obj) { org::bind::c::execute_destroy<org::imm::ImmErrorSkipToken>(org_context, obj); }

void haxorg_destroy_ImmBold(OrgContext* org_context, haxorg_ImmBold* obj) { org::bind::c::execute_destroy<org::imm::ImmBold>(org_context, obj); }

void haxorg_destroy_ImmUnderline(OrgContext* org_context, haxorg_ImmUnderline* obj) { org::bind::c::execute_destroy<org::imm::ImmUnderline>(org_context, obj); }

void haxorg_destroy_ImmMonospace(OrgContext* org_context, haxorg_ImmMonospace* obj) { org::bind::c::execute_destroy<org::imm::ImmMonospace>(org_context, obj); }

void haxorg_destroy_ImmMarkQuote(OrgContext* org_context, haxorg_ImmMarkQuote* obj) { org::bind::c::execute_destroy<org::imm::ImmMarkQuote>(org_context, obj); }

void haxorg_destroy_ImmVerbatim(OrgContext* org_context, haxorg_ImmVerbatim* obj) { org::bind::c::execute_destroy<org::imm::ImmVerbatim>(org_context, obj); }

void haxorg_destroy_ImmItalic(OrgContext* org_context, haxorg_ImmItalic* obj) { org::bind::c::execute_destroy<org::imm::ImmItalic>(org_context, obj); }

void haxorg_destroy_ImmStrike(OrgContext* org_context, haxorg_ImmStrike* obj) { org::bind::c::execute_destroy<org::imm::ImmStrike>(org_context, obj); }

void haxorg_destroy_ImmPar(OrgContext* org_context, haxorg_ImmPar* obj) { org::bind::c::execute_destroy<org::imm::ImmPar>(org_context, obj); }

void haxorg_destroy_ImmAdapterStmtAPI(OrgContext* org_context, haxorg_ImmAdapterStmtAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterStmtAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterSubtreeAPI(OrgContext* org_context, haxorg_ImmAdapterSubtreeAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterSubtreeAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterNoNodeAPI(OrgContext* org_context, haxorg_ImmAdapterNoNodeAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterNoNodeAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterAttrAPI(OrgContext* org_context, haxorg_ImmAdapterAttrAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterAttrAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterAttrListAPI(OrgContext* org_context, haxorg_ImmAdapterAttrListAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterAttrListAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterAttrsAPI(OrgContext* org_context, haxorg_ImmAdapterAttrsAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterAttrsAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterErrorItemAPI(OrgContext* org_context, haxorg_ImmAdapterErrorItemAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterErrorItemAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterErrorGroupAPI(OrgContext* org_context, haxorg_ImmAdapterErrorGroupAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterErrorGroupAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterErrorSkipGroupAPI(OrgContext* org_context, haxorg_ImmAdapterErrorSkipGroupAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterErrorSkipGroupAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterErrorSkipTokenAPI(OrgContext* org_context, haxorg_ImmAdapterErrorSkipTokenAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterErrorSkipTokenAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterStmtListAPI(OrgContext* org_context, haxorg_ImmAdapterStmtListAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterStmtListAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterEmptyAPI(OrgContext* org_context, haxorg_ImmAdapterEmptyAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterEmptyAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterInlineAPI(OrgContext* org_context, haxorg_ImmAdapterInlineAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterInlineAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterTimeAPI(OrgContext* org_context, haxorg_ImmAdapterTimeAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterTimeAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterTimeRangeAPI(OrgContext* org_context, haxorg_ImmAdapterTimeRangeAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterTimeRangeAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterMacroAPI(OrgContext* org_context, haxorg_ImmAdapterMacroAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterMacroAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterSymbolAPI(OrgContext* org_context, haxorg_ImmAdapterSymbolAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterSymbolAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterLeafAPI(OrgContext* org_context, haxorg_ImmAdapterLeafAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterLeafAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterMarkupAPI(OrgContext* org_context, haxorg_ImmAdapterMarkupAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterMarkupAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterLatexAPI(OrgContext* org_context, haxorg_ImmAdapterLatexAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterLatexAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterSubtreeLogAPI(OrgContext* org_context, haxorg_ImmAdapterSubtreeLogAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterSubtreeLogAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterColonExampleAPI(OrgContext* org_context, haxorg_ImmAdapterColonExampleAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterColonExampleAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCallAPI(OrgContext* org_context, haxorg_ImmAdapterCallAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCallAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterFileAPI(OrgContext* org_context, haxorg_ImmAdapterFileAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterFileAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterDirectoryAPI(OrgContext* org_context, haxorg_ImmAdapterDirectoryAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterDirectoryAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterSymlinkAPI(OrgContext* org_context, haxorg_ImmAdapterSymlinkAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterSymlinkAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterDocumentFragmentAPI(OrgContext* org_context, haxorg_ImmAdapterDocumentFragmentAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterDocumentFragmentAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCriticMarkupAPI(OrgContext* org_context, haxorg_ImmAdapterCriticMarkupAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCriticMarkupAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterListItemAPI(OrgContext* org_context, haxorg_ImmAdapterListItemAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterListItemAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterDocumentOptionsAPI(OrgContext* org_context, haxorg_ImmAdapterDocumentOptionsAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterDocumentOptionsAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterDocumentAPI(OrgContext* org_context, haxorg_ImmAdapterDocumentAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterDocumentAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterFileTargetAPI(OrgContext* org_context, haxorg_ImmAdapterFileTargetAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterFileTargetAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterTextSeparatorAPI(OrgContext* org_context, haxorg_ImmAdapterTextSeparatorAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterTextSeparatorAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdIncludeAPI(OrgContext* org_context, haxorg_ImmAdapterCmdIncludeAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdIncludeAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterDocumentGroupAPI(OrgContext* org_context, haxorg_ImmAdapterDocumentGroupAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterDocumentGroupAPI>(org_context, obj); }

void haxorg_destroy_Block(OrgContext* org_context, haxorg_Block* obj) { org::bind::c::execute_destroy<org::sem::Block>(org_context, obj); }

void haxorg_destroy_LineCommand(OrgContext* org_context, haxorg_LineCommand* obj) { org::bind::c::execute_destroy<org::sem::LineCommand>(org_context, obj); }

void haxorg_destroy_CmdCreator(OrgContext* org_context, haxorg_CmdCreator* obj) { org::bind::c::execute_destroy<org::sem::CmdCreator>(org_context, obj); }

void haxorg_destroy_CmdAuthor(OrgContext* org_context, haxorg_CmdAuthor* obj) { org::bind::c::execute_destroy<org::sem::CmdAuthor>(org_context, obj); }

void haxorg_destroy_CmdEmail(OrgContext* org_context, haxorg_CmdEmail* obj) { org::bind::c::execute_destroy<org::sem::CmdEmail>(org_context, obj); }

void haxorg_destroy_CmdLanguage(OrgContext* org_context, haxorg_CmdLanguage* obj) { org::bind::c::execute_destroy<org::sem::CmdLanguage>(org_context, obj); }

void haxorg_destroy_CmdCustomArgs(OrgContext* org_context, haxorg_CmdCustomArgs* obj) { org::bind::c::execute_destroy<org::sem::CmdCustomArgs>(org_context, obj); }

void haxorg_destroy_CmdTblfm(OrgContext* org_context, haxorg_CmdTblfm* obj) { org::bind::c::execute_destroy<org::sem::CmdTblfm>(org_context, obj); }

void haxorg_destroy_Cell(OrgContext* org_context, haxorg_Cell* obj) { org::bind::c::execute_destroy<org::sem::Cell>(org_context, obj); }

void haxorg_destroy_Row(OrgContext* org_context, haxorg_Row* obj) { org::bind::c::execute_destroy<org::sem::Row>(org_context, obj); }

void haxorg_destroy_ImmBlock(OrgContext* org_context, haxorg_ImmBlock* obj) { org::bind::c::execute_destroy<org::imm::ImmBlock>(org_context, obj); }

void haxorg_destroy_ImmLineCommand(OrgContext* org_context, haxorg_ImmLineCommand* obj) { org::bind::c::execute_destroy<org::imm::ImmLineCommand>(org_context, obj); }

void haxorg_destroy_ImmCmdCreator(OrgContext* org_context, haxorg_ImmCmdCreator* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdCreator>(org_context, obj); }

void haxorg_destroy_ImmCmdAuthor(OrgContext* org_context, haxorg_ImmCmdAuthor* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdAuthor>(org_context, obj); }

void haxorg_destroy_ImmCmdEmail(OrgContext* org_context, haxorg_ImmCmdEmail* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdEmail>(org_context, obj); }

void haxorg_destroy_ImmCmdLanguage(OrgContext* org_context, haxorg_ImmCmdLanguage* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdLanguage>(org_context, obj); }

void haxorg_destroy_ImmCmdCustomArgs(OrgContext* org_context, haxorg_ImmCmdCustomArgs* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdCustomArgs>(org_context, obj); }

void haxorg_destroy_ImmCmdTblfm(OrgContext* org_context, haxorg_ImmCmdTblfm* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdTblfm>(org_context, obj); }

void haxorg_destroy_ImmCell(OrgContext* org_context, haxorg_ImmCell* obj) { org::bind::c::execute_destroy<org::imm::ImmCell>(org_context, obj); }

void haxorg_destroy_ImmRow(OrgContext* org_context, haxorg_ImmRow* obj) { org::bind::c::execute_destroy<org::imm::ImmRow>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdAPI(OrgContext* org_context, haxorg_ImmAdapterCmdAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdCustomRawAPI(OrgContext* org_context, haxorg_ImmAdapterCmdCustomRawAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdCustomRawAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdCustomTextAPI(OrgContext* org_context, haxorg_ImmAdapterCmdCustomTextAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdCustomTextAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterLinkAPI(OrgContext* org_context, haxorg_ImmAdapterLinkAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterLinkAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterBlockCommentAPI(OrgContext* org_context, haxorg_ImmAdapterBlockCommentAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockCommentAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterParagraphAPI(OrgContext* org_context, haxorg_ImmAdapterParagraphAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterParagraphAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterListAPI(OrgContext* org_context, haxorg_ImmAdapterListAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterListAPI>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmStmt_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmStmt> { return org::imm::ImmAdapterT<org::imm::ImmStmt>(other); }, org_context, other); }

void haxorg_destroy_ImmStmtAdapter(OrgContext* org_context, haxorg_ImmStmtAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmStmt>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmSubtree_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmSubtree> { return org::imm::ImmAdapterT<org::imm::ImmSubtree>(other); }, org_context, other); }

void haxorg_destroy_ImmSubtreeAdapter(OrgContext* org_context, haxorg_ImmSubtreeAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmSubtree>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmNoNode_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmNoNode> { return org::imm::ImmAdapterT<org::imm::ImmNoNode>(other); }, org_context, other); }

void haxorg_destroy_ImmNoNodeAdapter(OrgContext* org_context, haxorg_ImmNoNodeAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmNoNode>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmErrorItem_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmErrorItem> { return org::imm::ImmAdapterT<org::imm::ImmErrorItem>(other); }, org_context, other); }

void haxorg_destroy_ImmErrorItemAdapter(OrgContext* org_context, haxorg_ImmErrorItemAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmErrorItem>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmErrorGroup_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmErrorGroup> { return org::imm::ImmAdapterT<org::imm::ImmErrorGroup>(other); }, org_context, other); }

void haxorg_destroy_ImmErrorGroupAdapter(OrgContext* org_context, haxorg_ImmErrorGroupAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmErrorGroup>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmErrorSkipGroup_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmErrorSkipGroup> { return org::imm::ImmAdapterT<org::imm::ImmErrorSkipGroup>(other); }, org_context, other); }

void haxorg_destroy_ImmErrorSkipGroupAdapter(OrgContext* org_context, haxorg_ImmErrorSkipGroupAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmErrorSkipGroup>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmErrorSkipToken_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmErrorSkipToken> { return org::imm::ImmAdapterT<org::imm::ImmErrorSkipToken>(other); }, org_context, other); }

void haxorg_destroy_ImmErrorSkipTokenAdapter(OrgContext* org_context, haxorg_ImmErrorSkipTokenAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmErrorSkipToken>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmStmtList_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmStmtList> { return org::imm::ImmAdapterT<org::imm::ImmStmtList>(other); }, org_context, other); }

void haxorg_destroy_ImmStmtListAdapter(OrgContext* org_context, haxorg_ImmStmtListAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmStmtList>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmEmpty_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmEmpty> { return org::imm::ImmAdapterT<org::imm::ImmEmpty>(other); }, org_context, other); }

void haxorg_destroy_ImmEmptyAdapter(OrgContext* org_context, haxorg_ImmEmptyAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmEmpty>>(org_context, obj); }

void haxorg_destroy_ImmAdapterHashTagAPI(OrgContext* org_context, haxorg_ImmAdapterHashTagAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterHashTagAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterInlineFootnoteAPI(OrgContext* org_context, haxorg_ImmAdapterInlineFootnoteAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterInlineFootnoteAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterSubtreeCompletionAPI(OrgContext* org_context, haxorg_ImmAdapterSubtreeCompletionAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterSubtreeCompletionAPI>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmInline_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmInline> { return org::imm::ImmAdapterT<org::imm::ImmInline>(other); }, org_context, other); }

void haxorg_destroy_ImmInlineAdapter(OrgContext* org_context, haxorg_ImmInlineAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmInline>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmTime_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmTime> { return org::imm::ImmAdapterT<org::imm::ImmTime>(other); }, org_context, other); }

void haxorg_destroy_ImmTimeAdapter(OrgContext* org_context, haxorg_ImmTimeAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmTime>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmTimeRange_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmTimeRange> { return org::imm::ImmAdapterT<org::imm::ImmTimeRange>(other); }, org_context, other); }

void haxorg_destroy_ImmTimeRangeAdapter(OrgContext* org_context, haxorg_ImmTimeRangeAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmTimeRange>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmMacro_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmMacro> { return org::imm::ImmAdapterT<org::imm::ImmMacro>(other); }, org_context, other); }

void haxorg_destroy_ImmMacroAdapter(OrgContext* org_context, haxorg_ImmMacroAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmMacro>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmSymbol_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmSymbol> { return org::imm::ImmAdapterT<org::imm::ImmSymbol>(other); }, org_context, other); }

void haxorg_destroy_ImmSymbolAdapter(OrgContext* org_context, haxorg_ImmSymbolAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmSymbol>>(org_context, obj); }

void haxorg_destroy_ImmAdapterEscapedAPI(OrgContext* org_context, haxorg_ImmAdapterEscapedAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterEscapedAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterNewlineAPI(OrgContext* org_context, haxorg_ImmAdapterNewlineAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterNewlineAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterSpaceAPI(OrgContext* org_context, haxorg_ImmAdapterSpaceAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterSpaceAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterWordAPI(OrgContext* org_context, haxorg_ImmAdapterWordAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterWordAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterAtMentionAPI(OrgContext* org_context, haxorg_ImmAdapterAtMentionAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterAtMentionAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterRawTextAPI(OrgContext* org_context, haxorg_ImmAdapterRawTextAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterRawTextAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterPunctuationAPI(OrgContext* org_context, haxorg_ImmAdapterPunctuationAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterPunctuationAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterPlaceholderAPI(OrgContext* org_context, haxorg_ImmAdapterPlaceholderAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterPlaceholderAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterBigIdentAPI(OrgContext* org_context, haxorg_ImmAdapterBigIdentAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBigIdentAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterTextTargetAPI(OrgContext* org_context, haxorg_ImmAdapterTextTargetAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterTextTargetAPI>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmLeaf_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmLeaf> { return org::imm::ImmAdapterT<org::imm::ImmLeaf>(other); }, org_context, other); }

void haxorg_destroy_ImmLeafAdapter(OrgContext* org_context, haxorg_ImmLeafAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmLeaf>>(org_context, obj); }

void haxorg_destroy_ImmAdapterBoldAPI(OrgContext* org_context, haxorg_ImmAdapterBoldAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBoldAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterUnderlineAPI(OrgContext* org_context, haxorg_ImmAdapterUnderlineAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterUnderlineAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterMonospaceAPI(OrgContext* org_context, haxorg_ImmAdapterMonospaceAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterMonospaceAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterMarkQuoteAPI(OrgContext* org_context, haxorg_ImmAdapterMarkQuoteAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterMarkQuoteAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterRadioTargetAPI(OrgContext* org_context, haxorg_ImmAdapterRadioTargetAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterRadioTargetAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterVerbatimAPI(OrgContext* org_context, haxorg_ImmAdapterVerbatimAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterVerbatimAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterItalicAPI(OrgContext* org_context, haxorg_ImmAdapterItalicAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterItalicAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterStrikeAPI(OrgContext* org_context, haxorg_ImmAdapterStrikeAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterStrikeAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterParAPI(OrgContext* org_context, haxorg_ImmAdapterParAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterParAPI>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmMarkup_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmMarkup> { return org::imm::ImmAdapterT<org::imm::ImmMarkup>(other); }, org_context, other); }

void haxorg_destroy_ImmMarkupAdapter(OrgContext* org_context, haxorg_ImmMarkupAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmMarkup>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmLatex_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmLatex> { return org::imm::ImmAdapterT<org::imm::ImmLatex>(other); }, org_context, other); }

void haxorg_destroy_ImmLatexAdapter(OrgContext* org_context, haxorg_ImmLatexAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmLatex>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmSubtreeLog_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmSubtreeLog> { return org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>(other); }, org_context, other); }

void haxorg_destroy_ImmSubtreeLogAdapter(OrgContext* org_context, haxorg_ImmSubtreeLogAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmColonExample_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmColonExample> { return org::imm::ImmAdapterT<org::imm::ImmColonExample>(other); }, org_context, other); }

void haxorg_destroy_ImmColonExampleAdapter(OrgContext* org_context, haxorg_ImmColonExampleAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmColonExample>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmCall_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCall> { return org::imm::ImmAdapterT<org::imm::ImmCall>(other); }, org_context, other); }

void haxorg_destroy_ImmCallAdapter(OrgContext* org_context, haxorg_ImmCallAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCall>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmFile_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmFile> { return org::imm::ImmAdapterT<org::imm::ImmFile>(other); }, org_context, other); }

void haxorg_destroy_ImmFileAdapter(OrgContext* org_context, haxorg_ImmFileAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmFile>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmDirectory_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmDirectory> { return org::imm::ImmAdapterT<org::imm::ImmDirectory>(other); }, org_context, other); }

void haxorg_destroy_ImmDirectoryAdapter(OrgContext* org_context, haxorg_ImmDirectoryAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmDirectory>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmSymlink_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmSymlink> { return org::imm::ImmAdapterT<org::imm::ImmSymlink>(other); }, org_context, other); }

void haxorg_destroy_ImmSymlinkAdapter(OrgContext* org_context, haxorg_ImmSymlinkAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmSymlink>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmDocumentFragment_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmDocumentFragment> { return org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>(other); }, org_context, other); }

void haxorg_destroy_ImmDocumentFragmentAdapter(OrgContext* org_context, haxorg_ImmDocumentFragmentAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmCriticMarkup_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCriticMarkup> { return org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>(other); }, org_context, other); }

void haxorg_destroy_ImmCriticMarkupAdapter(OrgContext* org_context, haxorg_ImmCriticMarkupAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmListItem_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmListItem> { return org::imm::ImmAdapterT<org::imm::ImmListItem>(other); }, org_context, other); }

void haxorg_destroy_ImmListItemAdapter(OrgContext* org_context, haxorg_ImmListItemAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmListItem>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmDocumentOptions_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmDocumentOptions> { return org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>(other); }, org_context, other); }

void haxorg_destroy_ImmDocumentOptionsAdapter(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmDocument_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmDocument> { return org::imm::ImmAdapterT<org::imm::ImmDocument>(other); }, org_context, other); }

void haxorg_destroy_ImmDocumentAdapter(OrgContext* org_context, haxorg_ImmDocumentAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmDocument>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmFileTarget_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmFileTarget> { return org::imm::ImmAdapterT<org::imm::ImmFileTarget>(other); }, org_context, other); }

void haxorg_destroy_ImmFileTargetAdapter(OrgContext* org_context, haxorg_ImmFileTargetAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmFileTarget>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmTextSeparator_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmTextSeparator> { return org::imm::ImmAdapterT<org::imm::ImmTextSeparator>(other); }, org_context, other); }

void haxorg_destroy_ImmTextSeparatorAdapter(OrgContext* org_context, haxorg_ImmTextSeparatorAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmTextSeparator>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmCmdInclude_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdInclude> { return org::imm::ImmAdapterT<org::imm::ImmCmdInclude>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdIncludeAdapter(OrgContext* org_context, haxorg_ImmCmdIncludeAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdInclude>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmDocumentGroup_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmDocumentGroup> { return org::imm::ImmAdapterT<org::imm::ImmDocumentGroup>(other); }, org_context, other); }

void haxorg_destroy_ImmDocumentGroupAdapter(OrgContext* org_context, haxorg_ImmDocumentGroupAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmDocumentGroup>>(org_context, obj); }

void haxorg_destroy_BlockCenter(OrgContext* org_context, haxorg_BlockCenter* obj) { org::bind::c::execute_destroy<org::sem::BlockCenter>(org_context, obj); }

void haxorg_destroy_BlockQuote(OrgContext* org_context, haxorg_BlockQuote* obj) { org::bind::c::execute_destroy<org::sem::BlockQuote>(org_context, obj); }

void haxorg_destroy_BlockVerse(OrgContext* org_context, haxorg_BlockVerse* obj) { org::bind::c::execute_destroy<org::sem::BlockVerse>(org_context, obj); }

void haxorg_destroy_BlockDynamicFallback(OrgContext* org_context, haxorg_BlockDynamicFallback* obj) { org::bind::c::execute_destroy<org::sem::BlockDynamicFallback>(org_context, obj); }

void haxorg_destroy_BlockExample(OrgContext* org_context, haxorg_BlockExample* obj) { org::bind::c::execute_destroy<org::sem::BlockExample>(org_context, obj); }

void haxorg_destroy_BlockExport(OrgContext* org_context, haxorg_BlockExport* obj) { org::bind::c::execute_destroy<org::sem::BlockExport>(org_context, obj); }

void haxorg_destroy_BlockAdmonition(OrgContext* org_context, haxorg_BlockAdmonition* obj) { org::bind::c::execute_destroy<org::sem::BlockAdmonition>(org_context, obj); }

void haxorg_destroy_BlockCodeEvalResult(OrgContext* org_context, haxorg_BlockCodeEvalResult* obj) { org::bind::c::execute_destroy<org::sem::BlockCodeEvalResult>(org_context, obj); }

void haxorg_destroy_BlockCode(OrgContext* org_context, haxorg_BlockCode* obj) { org::bind::c::execute_destroy<org::sem::BlockCode>(org_context, obj); }

void haxorg_destroy_Table(OrgContext* org_context, haxorg_Table* obj) { org::bind::c::execute_destroy<org::sem::Table>(org_context, obj); }

void haxorg_destroy_Attached(OrgContext* org_context, haxorg_Attached* obj) { org::bind::c::execute_destroy<org::sem::Attached>(org_context, obj); }

void haxorg_destroy_ImmBlockCenter(OrgContext* org_context, haxorg_ImmBlockCenter* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockCenter>(org_context, obj); }

void haxorg_destroy_ImmBlockQuote(OrgContext* org_context, haxorg_ImmBlockQuote* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockQuote>(org_context, obj); }

void haxorg_destroy_ImmBlockVerse(OrgContext* org_context, haxorg_ImmBlockVerse* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockVerse>(org_context, obj); }

void haxorg_destroy_ImmBlockDynamicFallback(OrgContext* org_context, haxorg_ImmBlockDynamicFallback* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockDynamicFallback>(org_context, obj); }

void haxorg_destroy_ImmBlockExample(OrgContext* org_context, haxorg_ImmBlockExample* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockExample>(org_context, obj); }

void haxorg_destroy_ImmBlockExport(OrgContext* org_context, haxorg_ImmBlockExport* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockExport>(org_context, obj); }

void haxorg_destroy_ImmBlockAdmonition(OrgContext* org_context, haxorg_ImmBlockAdmonition* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockAdmonition>(org_context, obj); }

void haxorg_destroy_ImmBlockCodeEvalResult(OrgContext* org_context, haxorg_ImmBlockCodeEvalResult* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockCodeEvalResult>(org_context, obj); }

void haxorg_destroy_ImmBlockCode(OrgContext* org_context, haxorg_ImmBlockCode* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockCode>(org_context, obj); }

void haxorg_destroy_ImmTable(OrgContext* org_context, haxorg_ImmTable* obj) { org::bind::c::execute_destroy<org::imm::ImmTable>(org_context, obj); }

void haxorg_destroy_ImmAttached(OrgContext* org_context, haxorg_ImmAttached* obj) { org::bind::c::execute_destroy<org::imm::ImmAttached>(org_context, obj); }

void haxorg_destroy_ImmAdapterLineCommandAPI(OrgContext* org_context, haxorg_ImmAdapterLineCommandAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterLineCommandAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdCustomArgsAPI(OrgContext* org_context, haxorg_ImmAdapterCmdCustomArgsAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdCustomArgsAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdCreatorAPI(OrgContext* org_context, haxorg_ImmAdapterCmdCreatorAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdCreatorAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdAuthorAPI(OrgContext* org_context, haxorg_ImmAdapterCmdAuthorAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdAuthorAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdEmailAPI(OrgContext* org_context, haxorg_ImmAdapterCmdEmailAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdEmailAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdLanguageAPI(OrgContext* org_context, haxorg_ImmAdapterCmdLanguageAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdLanguageAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdTblfmAPI(OrgContext* org_context, haxorg_ImmAdapterCmdTblfmAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdTblfmAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterBlockAPI(OrgContext* org_context, haxorg_ImmAdapterBlockAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCellAPI(OrgContext* org_context, haxorg_ImmAdapterCellAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCellAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterRowAPI(OrgContext* org_context, haxorg_ImmAdapterRowAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterRowAPI>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmCmd_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmd> { return org::imm::ImmAdapterT<org::imm::ImmCmd>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdAdapter(OrgContext* org_context, haxorg_ImmCmdAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmd>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmCmdCustomRaw_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw> { return org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdCustomRawAdapter(OrgContext* org_context, haxorg_ImmCmdCustomRawAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmCmdCustomText_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdCustomText> { return org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdCustomTextAdapter(OrgContext* org_context, haxorg_ImmCmdCustomTextAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmLink_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmLink> { return org::imm::ImmAdapterT<org::imm::ImmLink>(other); }, org_context, other); }

void haxorg_destroy_ImmLinkAdapter(OrgContext* org_context, haxorg_ImmLinkAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmLink>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmBlockComment_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlockComment> { return org::imm::ImmAdapterT<org::imm::ImmBlockComment>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockCommentAdapter(OrgContext* org_context, haxorg_ImmBlockCommentAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlockComment>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmParagraph_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmParagraph> { return org::imm::ImmAdapterT<org::imm::ImmParagraph>(other); }, org_context, other); }

void haxorg_destroy_ImmParagraphAdapter(OrgContext* org_context, haxorg_ImmParagraphAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmList_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmList> { return org::imm::ImmAdapterT<org::imm::ImmList>(other); }, org_context, other); }

void haxorg_destroy_ImmListAdapter(OrgContext* org_context, haxorg_ImmListAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmList>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmHashTag_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmHashTag> { return org::imm::ImmAdapterT<org::imm::ImmHashTag>(other); }, org_context, other); }

void haxorg_destroy_ImmHashTagAdapter(OrgContext* org_context, haxorg_ImmHashTagAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmHashTag>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmInlineFootnote_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmInlineFootnote> { return org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>(other); }, org_context, other); }

void haxorg_destroy_ImmInlineFootnoteAdapter(OrgContext* org_context, haxorg_ImmInlineFootnoteAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmEscaped_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmEscaped> { return org::imm::ImmAdapterT<org::imm::ImmEscaped>(other); }, org_context, other); }

void haxorg_destroy_ImmEscapedAdapter(OrgContext* org_context, haxorg_ImmEscapedAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmEscaped>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmNewline_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmNewline> { return org::imm::ImmAdapterT<org::imm::ImmNewline>(other); }, org_context, other); }

void haxorg_destroy_ImmNewlineAdapter(OrgContext* org_context, haxorg_ImmNewlineAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmNewline>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmSpace_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmSpace> { return org::imm::ImmAdapterT<org::imm::ImmSpace>(other); }, org_context, other); }

void haxorg_destroy_ImmSpaceAdapter(OrgContext* org_context, haxorg_ImmSpaceAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmSpace>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmWord_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmWord> { return org::imm::ImmAdapterT<org::imm::ImmWord>(other); }, org_context, other); }

void haxorg_destroy_ImmWordAdapter(OrgContext* org_context, haxorg_ImmWordAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmWord>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmAtMention_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmAtMention> { return org::imm::ImmAdapterT<org::imm::ImmAtMention>(other); }, org_context, other); }

void haxorg_destroy_ImmAtMentionAdapter(OrgContext* org_context, haxorg_ImmAtMentionAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmAtMention>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmRawText_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmRawText> { return org::imm::ImmAdapterT<org::imm::ImmRawText>(other); }, org_context, other); }

void haxorg_destroy_ImmRawTextAdapter(OrgContext* org_context, haxorg_ImmRawTextAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmRawText>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmPunctuation_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmPunctuation> { return org::imm::ImmAdapterT<org::imm::ImmPunctuation>(other); }, org_context, other); }

void haxorg_destroy_ImmPunctuationAdapter(OrgContext* org_context, haxorg_ImmPunctuationAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmPunctuation>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmPlaceholder_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmPlaceholder> { return org::imm::ImmAdapterT<org::imm::ImmPlaceholder>(other); }, org_context, other); }

void haxorg_destroy_ImmPlaceholderAdapter(OrgContext* org_context, haxorg_ImmPlaceholderAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmPlaceholder>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmBigIdent_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBigIdent> { return org::imm::ImmAdapterT<org::imm::ImmBigIdent>(other); }, org_context, other); }

void haxorg_destroy_ImmBigIdentAdapter(OrgContext* org_context, haxorg_ImmBigIdentAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBigIdent>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmTextTarget_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmTextTarget> { return org::imm::ImmAdapterT<org::imm::ImmTextTarget>(other); }, org_context, other); }

void haxorg_destroy_ImmTextTargetAdapter(OrgContext* org_context, haxorg_ImmTextTargetAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmTextTarget>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmBold_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBold> { return org::imm::ImmAdapterT<org::imm::ImmBold>(other); }, org_context, other); }

void haxorg_destroy_ImmBoldAdapter(OrgContext* org_context, haxorg_ImmBoldAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBold>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmUnderline_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmUnderline> { return org::imm::ImmAdapterT<org::imm::ImmUnderline>(other); }, org_context, other); }

void haxorg_destroy_ImmUnderlineAdapter(OrgContext* org_context, haxorg_ImmUnderlineAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmUnderline>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmMonospace_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmMonospace> { return org::imm::ImmAdapterT<org::imm::ImmMonospace>(other); }, org_context, other); }

void haxorg_destroy_ImmMonospaceAdapter(OrgContext* org_context, haxorg_ImmMonospaceAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmMonospace>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmMarkQuote_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmMarkQuote> { return org::imm::ImmAdapterT<org::imm::ImmMarkQuote>(other); }, org_context, other); }

void haxorg_destroy_ImmMarkQuoteAdapter(OrgContext* org_context, haxorg_ImmMarkQuoteAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmMarkQuote>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmRadioTarget_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmRadioTarget> { return org::imm::ImmAdapterT<org::imm::ImmRadioTarget>(other); }, org_context, other); }

void haxorg_destroy_ImmRadioTargetAdapter(OrgContext* org_context, haxorg_ImmRadioTargetAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmRadioTarget>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmVerbatim_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmVerbatim> { return org::imm::ImmAdapterT<org::imm::ImmVerbatim>(other); }, org_context, other); }

void haxorg_destroy_ImmVerbatimAdapter(OrgContext* org_context, haxorg_ImmVerbatimAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmVerbatim>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmItalic_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmItalic> { return org::imm::ImmAdapterT<org::imm::ImmItalic>(other); }, org_context, other); }

void haxorg_destroy_ImmItalicAdapter(OrgContext* org_context, haxorg_ImmItalicAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmItalic>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmStrike_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmStrike> { return org::imm::ImmAdapterT<org::imm::ImmStrike>(other); }, org_context, other); }

void haxorg_destroy_ImmStrikeAdapter(OrgContext* org_context, haxorg_ImmStrikeAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmStrike>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmPar_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmPar> { return org::imm::ImmAdapterT<org::imm::ImmPar>(other); }, org_context, other); }

void haxorg_destroy_ImmParAdapter(OrgContext* org_context, haxorg_ImmParAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmPar>>(org_context, obj); }

void haxorg_destroy_CmdCaption(OrgContext* org_context, haxorg_CmdCaption* obj) { org::bind::c::execute_destroy<org::sem::CmdCaption>(org_context, obj); }

void haxorg_destroy_CmdColumns(OrgContext* org_context, haxorg_CmdColumns* obj) { org::bind::c::execute_destroy<org::sem::CmdColumns>(org_context, obj); }

void haxorg_destroy_CmdName(OrgContext* org_context, haxorg_CmdName* obj) { org::bind::c::execute_destroy<org::sem::CmdName>(org_context, obj); }

void haxorg_destroy_CmdCall(OrgContext* org_context, haxorg_CmdCall* obj) { org::bind::c::execute_destroy<org::sem::CmdCall>(org_context, obj); }

void haxorg_destroy_CmdAttr(OrgContext* org_context, haxorg_CmdAttr* obj) { org::bind::c::execute_destroy<org::sem::CmdAttr>(org_context, obj); }

void haxorg_destroy_CmdExport(OrgContext* org_context, haxorg_CmdExport* obj) { org::bind::c::execute_destroy<org::sem::CmdExport>(org_context, obj); }

void haxorg_destroy_ImmCmdCaption(OrgContext* org_context, haxorg_ImmCmdCaption* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdCaption>(org_context, obj); }

void haxorg_destroy_ImmCmdColumns(OrgContext* org_context, haxorg_ImmCmdColumns* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdColumns>(org_context, obj); }

void haxorg_destroy_ImmCmdName(OrgContext* org_context, haxorg_ImmCmdName* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdName>(org_context, obj); }

void haxorg_destroy_ImmCmdCall(OrgContext* org_context, haxorg_ImmCmdCall* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdCall>(org_context, obj); }

void haxorg_destroy_ImmCmdAttr(OrgContext* org_context, haxorg_ImmCmdAttr* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdAttr>(org_context, obj); }

void haxorg_destroy_ImmCmdExport(OrgContext* org_context, haxorg_ImmCmdExport* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdExport>(org_context, obj); }

void haxorg_destroy_ImmAdapterAttachedAPI(OrgContext* org_context, haxorg_ImmAdapterAttachedAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterAttachedAPI>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmLineCommand_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmLineCommand> { return org::imm::ImmAdapterT<org::imm::ImmLineCommand>(other); }, org_context, other); }

void haxorg_destroy_ImmLineCommandAdapter(OrgContext* org_context, haxorg_ImmLineCommandAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmLineCommand>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmCmdCustomArgs_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs> { return org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdCustomArgsAdapter(OrgContext* org_context, haxorg_ImmCmdCustomArgsAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmCmdCreator_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdCreator> { return org::imm::ImmAdapterT<org::imm::ImmCmdCreator>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdCreatorAdapter(OrgContext* org_context, haxorg_ImmCmdCreatorAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdCreator>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmCmdAuthor_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdAuthor> { return org::imm::ImmAdapterT<org::imm::ImmCmdAuthor>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdAuthorAdapter(OrgContext* org_context, haxorg_ImmCmdAuthorAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdAuthor>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmCmdEmail_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdEmail> { return org::imm::ImmAdapterT<org::imm::ImmCmdEmail>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdEmailAdapter(OrgContext* org_context, haxorg_ImmCmdEmailAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdEmail>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmCmdLanguage_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdLanguage> { return org::imm::ImmAdapterT<org::imm::ImmCmdLanguage>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdLanguageAdapter(OrgContext* org_context, haxorg_ImmCmdLanguageAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdLanguage>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmCmdTblfm_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdTblfm> { return org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdTblfmAdapter(OrgContext* org_context, haxorg_ImmCmdTblfmAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>>(org_context, obj); }

void haxorg_destroy_ImmAdapterBlockCenterAPI(OrgContext* org_context, haxorg_ImmAdapterBlockCenterAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockCenterAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterBlockQuoteAPI(OrgContext* org_context, haxorg_ImmAdapterBlockQuoteAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockQuoteAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterBlockVerseAPI(OrgContext* org_context, haxorg_ImmAdapterBlockVerseAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockVerseAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterBlockExampleAPI(OrgContext* org_context, haxorg_ImmAdapterBlockExampleAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockExampleAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterInlineExportAPI(OrgContext* org_context, haxorg_ImmAdapterInlineExportAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterInlineExportAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdExportAPI(OrgContext* org_context, haxorg_ImmAdapterCmdExportAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdExportAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterBlockExportAPI(OrgContext* org_context, haxorg_ImmAdapterBlockExportAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockExportAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterBlockDynamicFallbackAPI(OrgContext* org_context, haxorg_ImmAdapterBlockDynamicFallbackAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockDynamicFallbackAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterBlockAdmonitionAPI(OrgContext* org_context, haxorg_ImmAdapterBlockAdmonitionAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockAdmonitionAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterBlockCodeEvalResultAPI(OrgContext* org_context, haxorg_ImmAdapterBlockCodeEvalResultAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockCodeEvalResultAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterBlockCodeAPI(OrgContext* org_context, haxorg_ImmAdapterBlockCodeAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockCodeAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterTableAPI(OrgContext* org_context, haxorg_ImmAdapterTableAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterTableAPI>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmBlock_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlock> { return org::imm::ImmAdapterT<org::imm::ImmBlock>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockAdapter(OrgContext* org_context, haxorg_ImmBlockAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlock>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmCell_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCell> { return org::imm::ImmAdapterT<org::imm::ImmCell>(other); }, org_context, other); }

void haxorg_destroy_ImmCellAdapter(OrgContext* org_context, haxorg_ImmCellAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCell>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmRow_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmRow> { return org::imm::ImmAdapterT<org::imm::ImmRow>(other); }, org_context, other); }

void haxorg_destroy_ImmRowAdapter(OrgContext* org_context, haxorg_ImmRowAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmRow>>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdCaptionAPI(OrgContext* org_context, haxorg_ImmAdapterCmdCaptionAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdCaptionAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdColumnsAPI(OrgContext* org_context, haxorg_ImmAdapterCmdColumnsAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdColumnsAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdNameAPI(OrgContext* org_context, haxorg_ImmAdapterCmdNameAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdNameAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdCallAPI(OrgContext* org_context, haxorg_ImmAdapterCmdCallAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdCallAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdResultsAPI(OrgContext* org_context, haxorg_ImmAdapterCmdResultsAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdResultsAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdAttrAPI(OrgContext* org_context, haxorg_ImmAdapterCmdAttrAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdAttrAPI>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmAttached_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmAttached> { return org::imm::ImmAdapterT<org::imm::ImmAttached>(other); }, org_context, other); }

void haxorg_destroy_ImmAttachedAdapter(OrgContext* org_context, haxorg_ImmAttachedAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmAttached>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmBlockCenter_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlockCenter> { return org::imm::ImmAdapterT<org::imm::ImmBlockCenter>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockCenterAdapter(OrgContext* org_context, haxorg_ImmBlockCenterAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlockCenter>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmBlockQuote_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlockQuote> { return org::imm::ImmAdapterT<org::imm::ImmBlockQuote>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockQuoteAdapter(OrgContext* org_context, haxorg_ImmBlockQuoteAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlockQuote>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmBlockVerse_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlockVerse> { return org::imm::ImmAdapterT<org::imm::ImmBlockVerse>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockVerseAdapter(OrgContext* org_context, haxorg_ImmBlockVerseAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlockVerse>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmBlockExample_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlockExample> { return org::imm::ImmAdapterT<org::imm::ImmBlockExample>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockExampleAdapter(OrgContext* org_context, haxorg_ImmBlockExampleAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlockExample>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmInlineExport_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmInlineExport> { return org::imm::ImmAdapterT<org::imm::ImmInlineExport>(other); }, org_context, other); }

void haxorg_destroy_ImmInlineExportAdapter(OrgContext* org_context, haxorg_ImmInlineExportAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmInlineExport>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmCmdExport_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdExport> { return org::imm::ImmAdapterT<org::imm::ImmCmdExport>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdExportAdapter(OrgContext* org_context, haxorg_ImmCmdExportAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdExport>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmBlockExport_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlockExport> { return org::imm::ImmAdapterT<org::imm::ImmBlockExport>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockExportAdapter(OrgContext* org_context, haxorg_ImmBlockExportAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlockExport>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmBlockDynamicFallback_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback> { return org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockDynamicFallbackAdapter(OrgContext* org_context, haxorg_ImmBlockDynamicFallbackAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmBlockAdmonition_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition> { return org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockAdmonitionAdapter(OrgContext* org_context, haxorg_ImmBlockAdmonitionAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmBlockCodeEvalResult_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult> { return org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockCodeEvalResultAdapter(OrgContext* org_context, haxorg_ImmBlockCodeEvalResultAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmBlockCode_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlockCode> { return org::imm::ImmAdapterT<org::imm::ImmBlockCode>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockCodeAdapter(OrgContext* org_context, haxorg_ImmBlockCodeAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlockCode>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmTable_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmTable> { return org::imm::ImmAdapterT<org::imm::ImmTable>(other); }, org_context, other); }

void haxorg_destroy_ImmTableAdapter(OrgContext* org_context, haxorg_ImmTableAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmTable>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmCmdCaption_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdCaption> { return org::imm::ImmAdapterT<org::imm::ImmCmdCaption>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdCaptionAdapter(OrgContext* org_context, haxorg_ImmCmdCaptionAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdCaption>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmCmdColumns_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdColumns> { return org::imm::ImmAdapterT<org::imm::ImmCmdColumns>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdColumnsAdapter(OrgContext* org_context, haxorg_ImmCmdColumnsAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdColumns>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmCmdName_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdName> { return org::imm::ImmAdapterT<org::imm::ImmCmdName>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdNameAdapter(OrgContext* org_context, haxorg_ImmCmdNameAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdName>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmCmdCall_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdCall> { return org::imm::ImmAdapterT<org::imm::ImmCmdCall>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdCallAdapter(OrgContext* org_context, haxorg_ImmCmdCallAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdCall>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmCmdAttr_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdAttr> { return org::imm::ImmAdapterT<org::imm::ImmCmdAttr>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdAttrAdapter(OrgContext* org_context, haxorg_ImmCmdAttrAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdAttr>>(org_context, obj); }

haxorg_SemIdOfOrg haxorg_newSemTimeStatic(OrgContext* org_context, haxorg_UserTimeBreakdown breakdown, bool isActive) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg, haxorg_SemIdOfOrg_vtable>(static_cast<org::sem::SemId<org::sem::Time>(*)(hstd::UserTimeBreakdown const&, bool)>(&org::newSemTimeStatic), org_context, breakdown, isActive); }

haxorg_ImmAstContext haxorg_initImmutableAstContext(OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmAstContext, haxorg_ImmAstContext_vtable>(static_cast<std::shared_ptr<org::imm::ImmAstContext>(*)()>(&org::initImmutableAstContext), org_context); }

haxorg_SemIdOfOrg haxorg_asOneNode(OrgContext* org_context, haxorg_SemIdOfOrg arg) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg, haxorg_SemIdOfOrg_vtable>(static_cast<org::sem::SemId<org::sem::Org>(*)(org::sem::SemId<org::sem::Org> const&)>(&org::asOneNode), org_context, arg); }

haxorg_StdString haxorg_formatToString(OrgContext* org_context, haxorg_SemIdOfOrg arg) { return org::bind::c::execute_cpp<haxorg_StdString, haxorg_StdString_vtable>(static_cast<std::string(*)(org::sem::SemId<org::sem::Org>)>(&org::formatToString), org_context, arg); }

haxorg_StdString haxorg_exportToYamlString(OrgContext* org_context, haxorg_SemIdOfOrg node, haxorg_OrgYamlExportOpts opts) { return org::bind::c::execute_cpp<haxorg_StdString, haxorg_StdString_vtable>(static_cast<std::string(*)(org::sem::SemId<org::sem::Org> const&, org::OrgYamlExportOpts const&)>(&org::exportToYamlString), org_context, node, opts); }

void haxorg_exportToYamlFile(OrgContext* org_context, haxorg_SemIdOfOrg node, haxorg_StdString path, haxorg_OrgYamlExportOpts opts) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(static_cast<void(*)(org::sem::SemId<org::sem::Org> const&, std::string, org::OrgYamlExportOpts const&)>(&org::exportToYamlFile), org_context, node, path, opts); }

haxorg_StdString haxorg_exportToJsonString(OrgContext* org_context, haxorg_SemIdOfOrg node) { return org::bind::c::execute_cpp<haxorg_StdString, haxorg_StdString_vtable>(static_cast<std::string(*)(org::sem::SemId<org::sem::Org> const&)>(&org::exportToJsonString), org_context, node); }

void haxorg_exportToJsonFile(OrgContext* org_context, haxorg_SemIdOfOrg node, haxorg_StdString path) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(static_cast<void(*)(org::sem::SemId<org::sem::Org> const&, std::string)>(&org::exportToJsonFile), org_context, node, path); }

haxorg_SemIdOfOrg haxorg_readProtobufFile(OrgContext* org_context, haxorg_StdString file) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg, haxorg_SemIdOfOrg_vtable>(static_cast<org::sem::SemId<org::sem::Document>(*)(std::string const&)>(&org::readProtobufFile), org_context, file); }

void haxorg_exportToProtobufFile(OrgContext* org_context, haxorg_SemIdOfOrg doc, haxorg_StdString file) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(static_cast<void(*)(org::sem::SemId<org::sem::Document>, std::string const&)>(&org::exportToProtobufFile), org_context, doc, file); }

haxorg_StdString haxorg_exportToTreeString(OrgContext* org_context, haxorg_SemIdOfOrg node, haxorg_OrgTreeExportOpts opts) { return org::bind::c::execute_cpp<haxorg_StdString, haxorg_StdString_vtable>(static_cast<std::string(*)(org::sem::SemId<org::sem::Org> const&, org::OrgTreeExportOpts const&)>(&org::exportToTreeString), org_context, node, opts); }

void haxorg_exportToTreeFile(OrgContext* org_context, haxorg_SemIdOfOrg node, haxorg_StdString path, haxorg_OrgTreeExportOpts opts) { return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(static_cast<void(*)(org::sem::SemId<org::sem::Org> const&, std::string, org::OrgTreeExportOpts const&)>(&org::exportToTreeFile), org_context, node, path, opts); }

haxorg_AstTrackingMap haxorg_getAstTrackingMap(OrgContext* org_context, haxorg_HstdVec nodes) { return org::bind::c::execute_cpp<haxorg_AstTrackingMap, haxorg_AstTrackingMap_vtable>(static_cast<org::AstTrackingMap(*)(hstd::Vec<org::sem::SemId<org::sem::Org>> const&)>(&org::getAstTrackingMap), org_context, nodes); }

haxorg_HstdVec haxorg_getSubnodeGroups(OrgContext* org_context, haxorg_SemIdOfOrg node, haxorg_AstTrackingMap map) { return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<org::AstTrackingGroup>(*)(org::sem::SemId<org::sem::Org>, org::AstTrackingMap const&)>(&org::getSubnodeGroups), org_context, node, map); }

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
