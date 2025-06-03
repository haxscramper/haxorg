/* clang-format off */
#include "node_utils.hpp"
#include "node_org_include.hpp"
#include "haxorg_wasm_manual.hpp"
using namespace org::bind::js;
void subdivide_0(org::bind::js::type_registration_guard& g) {
  org::bind::js::stdoptional_bind<int>(g, "StdOptionalOfInt");
  org::bind::js::stdoptional_bind<std::string>(g, "StdOptionalOfStdString");
  org::bind::js::hstdVec_bind<org::sem::OrgJson>(g, "VecOfOrgJson");
  org::bind::js::stdoptional_bind<org::parse::LineCol>(g, "StdOptionalOfParseLineCol");
  org::bind::js::hstdVec_bind<org::sem::SemId<org::sem::Org>>(g, "VecOfSemIdOfOrg");
  org::bind::js::immerbox_bind<hstd::Str>(g, "ImmBoxOfStr");
  org::bind::js::immerbox_bind<std::optional<hstd::Str>>(g, "ImmBoxOfStdOptionalOfStr");
  org::bind::js::stdoptional_bind<hstd::Str>(g, "StdOptionalOfStr");
  org::bind::js::immerbox_bind<std::optional<int>>(g, "ImmBoxOfStdOptionalOfInt");
  org::bind::js::immerflex_vector_bind<org::imm::ImmIdT<org::imm::ImmErrorItem>>(g, "ImmFlexVectorOfImmIdTOfImmErrorItem");
  org::bind::js::immerflex_vector_bind<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>>(g, "ImmFlexVectorOfImmIdTOfImmBlockCodeEvalResult");
  org::bind::js::immerbox_bind<std::optional<org::imm::ImmIdT<org::imm::ImmOrg>>>(g, "ImmBoxOfStdOptionalOfImmIdTOfImmOrg");
  org::bind::js::stdoptional_bind<org::imm::ImmIdT<org::imm::ImmOrg>>(g, "StdOptionalOfImmIdTOfImmOrg");
  org::bind::js::immerflex_vector_bind<org::imm::ImmSymbol::Param>(g, "ImmFlexVectorOfImmSymbolParam");
  org::bind::js::immerflex_vector_bind<org::imm::ImmIdT<org::imm::ImmOrg>>(g, "ImmFlexVectorOfImmIdTOfImmOrg");
  org::bind::js::immerflex_vector_bind<hstd::Str>(g, "ImmFlexVectorOfStr");
  org::bind::js::immerbox_bind<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>>(g, "ImmBoxOfStdOptionalOfImmIdTOfImmParagraph");
  org::bind::js::stdoptional_bind<org::imm::ImmIdT<org::imm::ImmParagraph>>(g, "StdOptionalOfImmIdTOfImmParagraph");
  org::bind::js::immerflex_vector_bind<org::sem::OrgCodeEvalOutput>(g, "ImmFlexVectorOfOrgCodeEvalOutput");
  org::bind::js::immerflex_vector_bind<org::sem::BlockCodeLine>(g, "ImmFlexVectorOfBlockCodeLine");
  org::bind::js::immerbox_bind<std::optional<org::imm::ImmIdT<org::imm::ImmStmtList>>>(g, "ImmBoxOfStdOptionalOfImmIdTOfImmStmtList");
  org::bind::js::stdoptional_bind<org::imm::ImmIdT<org::imm::ImmStmtList>>(g, "StdOptionalOfImmIdTOfImmStmtList");
  org::bind::js::immerbox_bind<std::optional<org::sem::SubtreeCompletion>>(g, "ImmBoxOfStdOptionalOfSubtreeCompletion");
  org::bind::js::stdoptional_bind<org::sem::SubtreeCompletion>(g, "StdOptionalOfSubtreeCompletion");
  org::bind::js::immerflex_vector_bind<org::imm::ImmIdT<org::imm::ImmHashTag>>(g, "ImmFlexVectorOfImmIdTOfImmHashTag");
  org::bind::js::immerflex_vector_bind<org::imm::ImmIdT<org::imm::ImmSubtreeLog>>(g, "ImmFlexVectorOfImmIdTOfImmSubtreeLog");
  org::bind::js::immerflex_vector_bind<org::sem::NamedProperty>(g, "ImmFlexVectorOfNamedProperty");
  org::bind::js::immerbox_bind<std::optional<hstd::UserTime>>(g, "ImmBoxOfStdOptionalOfUserTime");
  org::bind::js::stdoptional_bind<hstd::UserTime>(g, "StdOptionalOfUserTime");
  org::bind::js::immerflex_vector_bind<org::imm::ImmIdT<org::imm::ImmCell>>(g, "ImmFlexVectorOfImmIdTOfImmCell");
  org::bind::js::immerflex_vector_bind<org::imm::ImmIdT<org::imm::ImmRow>>(g, "ImmFlexVectorOfImmIdTOfImmRow");
  org::bind::js::immerbox_bind<std::optional<bool>>(g, "ImmBoxOfStdOptionalOfBool");
  org::bind::js::stdoptional_bind<bool>(g, "StdOptionalOfBool");
  org::bind::js::immerbox_bind<std::optional<org::sem::ColumnView>>(g, "ImmBoxOfStdOptionalOfColumnView");
  org::bind::js::stdoptional_bind<org::sem::ColumnView>(g, "StdOptionalOfColumnView");
  org::bind::js::immerflex_vector_bind<org::sem::TodoKeyword>(g, "ImmFlexVectorOfTodoKeyword");
  org::bind::js::immerbox_bind<std::optional<org::imm::ImmIdT<org::imm::ImmRawText>>>(g, "ImmBoxOfStdOptionalOfImmIdTOfImmRawText");
  org::bind::js::stdoptional_bind<org::imm::ImmIdT<org::imm::ImmRawText>>(g, "StdOptionalOfImmIdTOfImmRawText");
  org::bind::js::stdoptional_bind<org::imm::ImmAdapter>(g, "StdOptionalOfImmAdapter");
  org::bind::js::hstdVec_bind<int>(g, "VecOfInt");
  org::bind::js::hstdVec_bind<org::imm::ImmAdapter>(g, "VecOfImmAdapter");
  org::bind::js::hstdUnorderedMap_bind<org::sem::HashTagFlat, org::AstTrackingPath>(g, "UnorderedMapOfHashTagFlatAstTrackingPath");
  org::bind::js::hstdUnorderedMap_bind<hstd::Str, org::AstTrackingAlternatives>(g, "UnorderedMapOfStrAstTrackingAlternatives");
  org::bind::js::hstdUnorderedMap_bind<org::sem::HashTagFlat, org::AstTrackingAlternatives>(g, "UnorderedMapOfHashTagFlatAstTrackingAlternatives");
  org::bind::js::stdoptional_bind<org::AstTrackingAlternatives>(g, "StdOptionalOfAstTrackingAlternatives");
  org::bind::js::hstdVec_bind<hstd::SequenceSegment>(g, "VecOfSequenceSegment");
  org::bind::js::hstdVec_bind<hstd::SequenceAnnotationTag>(g, "VecOfSequenceAnnotationTag");
  org::bind::js::hstdVec_bind<org::imm::ImmUniqId>(g, "VecOfImmUniqId");
  org::bind::js::hstdVec_bind<org::graph::MapLink>(g, "VecOfGraphMapLink");
  org::bind::js::hstdUnorderedMap_bind<org::graph::MapNode, org::graph::MapNodeProp>(g, "UnorderedMapOfGraphMapNodeGraphMapNodeProp");
  org::bind::js::hstdUnorderedMap_bind<org::graph::MapEdge, org::graph::MapEdgeProp>(g, "UnorderedMapOfGraphMapEdgeGraphMapEdgeProp");
  org::bind::js::hstdUnorderedMap_bind<org::graph::MapNode, org::graph::AdjNodesList>(g, "UnorderedMapOfGraphMapNodeGraphAdjNodesList");
  org::bind::js::hstdVec_bind<org::graph::MapNode>(g, "VecOfGraphMapNode");
  org::bind::js::hstdVec_bind<org::graph::MapEdge>(g, "VecOfGraphMapEdge");
  org::bind::js::stdoptional_bind<org::graph::MapLink>(g, "StdOptionalOfGraphMapLink");
  org::bind::js::hstdVec_bind<org::sem::LispCode>(g, "VecOfLispCode");
  org::bind::js::hstdVec_bind<org::sem::Tblfm::Assign>(g, "VecOfTblfmAssign");
  org::bind::js::hstdOpt_bind<org::sem::Tblfm::Expr::AxisRef::Position>(g, "OptOfTblfmExprAxisRefPosition");
  org::bind::js::hstdOpt_bind<org::sem::Tblfm::Expr::AxisRef>(g, "OptOfTblfmExprAxisRef");
  org::bind::js::hstdVec_bind<org::sem::Tblfm::Expr>(g, "VecOfTblfmExpr");
  org::bind::js::hstdVec_bind<org::sem::Tblfm::Assign::Flag>(g, "VecOfTblfmAssignFlag");
  org::bind::js::hstdOpt_bind<hstd::Str>(g, "OptOfStr");
  org::bind::js::hstdVec_bind<org::sem::AttrValue::DimensionSpan>(g, "VecOfAttrValueDimensionSpan");
  org::bind::js::hstdOpt_bind<bool>(g, "OptOfBool");
  org::bind::js::hstdOpt_bind<int>(g, "OptOfInt");
  org::bind::js::hstdOpt_bind<double>(g, "OptOfDouble");
  org::bind::js::hstdVec_bind<hstd::Str>(g, "VecOfStr");
  org::bind::js::hstdVec_bind<org::sem::HashTagText>(g, "VecOfHashTagText");
  org::bind::js::hstdVec_bind<org::sem::HashTagFlat>(g, "VecOfHashTagFlat");
  org::bind::js::hstdOpt_bind<std::string>(g, "OptOfStdString");
  org::bind::js::hstdOpt_bind<hstd::UserTime>(g, "OptOfUserTime");
  org::bind::js::hstdVec_bind<org::sem::AttrValue>(g, "VecOfAttrValue");
  org::bind::js::hstdUnorderedMap_bind<hstd::Str, org::sem::AttrList>(g, "UnorderedMapOfStrAttrList");
  org::bind::js::hstdOpt_bind<org::sem::AttrValue>(g, "OptOfAttrValue");
  org::bind::js::hstdOpt_bind<org::sem::AttrList>(g, "OptOfAttrList");
  org::bind::js::hstdVec_bind<org::sem::OrgCodeEvalInput::Var>(g, "VecOfOrgCodeEvalInputVar");
  org::bind::js::hstdVec_bind<org::sem::ColumnView::Column>(g, "VecOfColumnViewColumn");
  org::bind::js::hstdOpt_bind<org::sem::ColumnView::Summary>(g, "OptOfColumnViewSummary");
  org::bind::js::hstdVec_bind<org::sem::BlockCodeLine::Part>(g, "VecOfBlockCodeLinePart");
  org::bind::js::hstdUnorderedMap_bind<hstd::Str, hstd::Str>(g, "UnorderedMapOfStrStr");
  org::bind::js::hstdVec_bind<org::sem::SemId<org::sem::ErrorItem>>(g, "VecOfSemIdOfErrorItem");
  org::bind::js::hstdVec_bind<org::sem::Time::Repeat>(g, "VecOfTimeRepeat");
  org::bind::js::hstdOpt_bind<org::sem::Time::Repeat>(g, "OptOfTimeRepeat");
  org::bind::js::hstdVec_bind<org::sem::Symbol::Param>(g, "VecOfSymbolParam");
  org::bind::js::hstdOpt_bind<org::sem::SemId<org::sem::StmtList>>(g, "OptOfSemIdOfStmtList");
  org::bind::js::hstdOpt_bind<org::sem::SubtreeCompletion>(g, "OptOfSubtreeCompletion");
  org::bind::js::hstdOpt_bind<org::sem::SemId<org::sem::Paragraph>>(g, "OptOfSemIdOfParagraph");
  org::bind::js::hstdVec_bind<org::sem::SemId<org::sem::HashTag>>(g, "VecOfSemIdOfHashTag");
  org::bind::js::hstdVec_bind<org::sem::SemId<org::sem::SubtreeLog>>(g, "VecOfSemIdOfSubtreeLog");
  org::bind::js::hstdVec_bind<org::sem::NamedProperty>(g, "VecOfNamedProperty");
  org::bind::js::hstdVec_bind<org::sem::SubtreePeriod>(g, "VecOfSubtreePeriod");
  org::bind::js::hstdIntSet_bind<org::sem::SubtreePeriod::Kind>(g, "IntSetOfSubtreePeriodKind");
  org::bind::js::hstdOpt_bind<org::sem::NamedProperty>(g, "OptOfNamedProperty");
  org::bind::js::hstdOpt_bind<org::sem::ColumnView>(g, "OptOfColumnView");
  org::bind::js::hstdVec_bind<org::sem::TodoKeyword>(g, "VecOfTodoKeyword");
  org::bind::js::hstdOpt_bind<org::sem::SemId<org::sem::RawText>>(g, "OptOfSemIdOfRawText");
  org::bind::js::hstdOpt_bind<org::sem::SubtreePath>(g, "OptOfSubtreePath");
  org::bind::js::hstdOpt_bind<org::imm::ImmTime::Repeat>(g, "OptOfImmTimeRepeat");
  org::bind::js::hstdOpt_bind<org::imm::ImmIdT<org::imm::ImmStmtList>>(g, "OptOfImmIdTOfImmStmtList");
  org::bind::js::hstdOpt_bind<org::imm::ImmIdT<org::imm::ImmParagraph>>(g, "OptOfImmIdTOfImmParagraph");
  org::bind::js::hstdOpt_bind<org::imm::ImmIdT<org::imm::ImmRawText>>(g, "OptOfImmIdTOfImmRawText");
}

void subdivide_1(org::bind::js::type_registration_guard& g) {
  org::bind::js::hstdVec_bind<org::sem::SemId<org::sem::BigIdent>>(g, "VecOfSemIdOfBigIdent");
  org::bind::js::hstdVec_bind<hstd::UserTime>(g, "VecOfUserTime");
  org::bind::js::hstdVec_bind<org::sem::SemId<org::sem::Time>>(g, "VecOfSemIdOfTime");
  org::bind::js::hstdOpt_bind<org::sem::SemId<org::sem::Org>>(g, "OptOfSemIdOfOrg");
  org::bind::js::hstdOpt_bind<org::imm::ImmIdT<org::imm::ImmOrg>>(g, "OptOfImmIdTOfImmOrg");
  org::bind::js::hstdVec_bind<org::sem::SemId<org::sem::Cell>>(g, "VecOfSemIdOfCell");
  org::bind::js::hstdVec_bind<org::sem::OrgCodeEvalOutput>(g, "VecOfOrgCodeEvalOutput");
  org::bind::js::hstdVec_bind<org::sem::SemId<org::sem::BlockCodeEvalResult>>(g, "VecOfSemIdOfBlockCodeEvalResult");
  org::bind::js::hstdVec_bind<org::sem::BlockCodeLine>(g, "VecOfBlockCodeLine");
  org::bind::js::hstdVec_bind<org::sem::SemId<org::sem::Row>>(g, "VecOfSemIdOfRow");
  org::bind::js::stdoptional_bind<org::sem::SemId<org::sem::Org>>(g, "StdOptionalOfSemIdOfOrg");
  org::bind::js::hstdVec_bind<org::AstTrackingGroup>(g, "VecOfAstTrackingGroup");
  org::bind::js::hstdVec_bind<hstd::SequenceAnnotation>(g, "VecOfSequenceAnnotation");
  org::bind::js::hstdVec_bind<hstd::SequenceSegmentGroup>(g, "VecOfSequenceSegmentGroup");
  emscripten::class_<hstd::UserTimeBreakdown>("UserTimeBreakdown")
    .property("year", &hstd::UserTimeBreakdown::year)
    .property("month", &hstd::UserTimeBreakdown::month)
    .property("day", &hstd::UserTimeBreakdown::day)
    .property("hour", &hstd::UserTimeBreakdown::hour)
    .property("minute", &hstd::UserTimeBreakdown::minute)
    .property("second", &hstd::UserTimeBreakdown::second)
    .property("zone", &hstd::UserTimeBreakdown::zone)
    .constructor<>()
    ;
  emscripten::class_<hstd::UserTime>("UserTime")
    .function("getBreakdown", static_cast<hstd::UserTimeBreakdown(hstd::UserTime::*)() const>(&hstd::UserTime::getBreakdown))
    .function("format", static_cast<std::string(hstd::UserTime::*)() const>(&hstd::UserTime::format))
    .constructor<>()
    ;
  emscripten::class_<org::parse::LineCol>("ParseLineCol")
    .property("line", &org::parse::LineCol::line)
    .property("column", &org::parse::LineCol::column)
    .property("pos", &org::parse::LineCol::pos)
    .constructor<>()
    ;
  emscripten::class_<hstd::OperationsTracer>("OperationsTracer")
    .property("TraceState", &hstd::OperationsTracer::TraceState)
    .property("traceToFile", &hstd::OperationsTracer::traceToFile)
    .property("traceToBuffer", &hstd::OperationsTracer::traceToBuffer)
    .property("traceStructured", &hstd::OperationsTracer::traceStructured)
    .property("traceColored", &hstd::OperationsTracer::traceColored)
    .property("activeLevel", &hstd::OperationsTracer::activeLevel)
    .property("traceBuffer", &hstd::OperationsTracer::traceBuffer)
    .function("setTraceFileStr", static_cast<void(hstd::OperationsTracer::*)(std::string const&, bool)>(&hstd::OperationsTracer::setTraceFileStr))
    .function("sendMessage", static_cast<void(hstd::OperationsTracer::*)(std::string const&, std::string const&, int, std::string const&)>(&hstd::OperationsTracer::sendMessage))
    .constructor<>()
    ;
  emscripten::class_<org::sem::OrgJson>("OrgJson")
    .function("getKind", static_cast<OrgJsonKind(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getKind))
    .function("getJsonString", static_cast<std::string(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getJsonString))
    .function("atIndex", static_cast<org::sem::OrgJson(org::sem::OrgJson::*)(int) const>(&org::sem::OrgJson::at))
    .function("atField", static_cast<org::sem::OrgJson(org::sem::OrgJson::*)(std::string const&) const>(&org::sem::OrgJson::at))
    .function("getString", static_cast<std::string(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getString))
    .function("getField", static_cast<org::sem::OrgJson(org::sem::OrgJson::*)(std::string const&) const>(&org::sem::OrgJson::getField))
    .function("getItem", static_cast<org::sem::OrgJson(org::sem::OrgJson::*)(int) const>(&org::sem::OrgJson::getItem))
    .function("getInt", static_cast<int(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getInt))
    .function("getBool", static_cast<bool(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getBool))
    .function("getArray", static_cast<hstd::Vec<org::sem::OrgJson>(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getArray))
    .constructor<>()
    ;
  emscripten::class_<org::sem::Org>("Org")
    .smart_ptr<org::sem::SemId<org::sem::Org>>("Org")
    .property("loc", &org::sem::Org::loc)
    .property("subnodes", &org::sem::Org::subnodes)
    .function("getKind", static_cast<OrgSemKind(org::sem::Org::*)() const>(&org::sem::Org::getKind))
    .function("isGenerated", static_cast<bool(org::sem::Org::*)() const>(&org::sem::Org::isGenerated))
    .function("push_back", static_cast<void(org::sem::Org::*)(org::sem::SemId<org::sem::Org>)>(&org::sem::Org::push_back))
    .function("size", static_cast<int(org::sem::Org::*)() const>(&org::sem::Org::size))
    .function("insert", static_cast<void(org::sem::Org::*)(int, org::sem::SemId<org::sem::Org>)>(&org::sem::Org::insert))
    .function("at", static_cast<org::sem::SemId<org::sem::Org>(org::sem::Org::*)(int) const>(&org::sem::Org::at))
    .function("is", static_cast<bool(org::sem::Org::*)(OrgSemKind) const>(&org::sem::Org::is))
    ;
  emscripten::class_<org::imm::ImmId>("ImmId")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmId::*)() const>(&org::imm::ImmId::getKind))
    .function("is", static_cast<bool(org::imm::ImmId::*)(OrgSemKind) const>(&org::imm::ImmId::is))
    .function("getNodeIndex", static_cast<org::imm::ImmId::NodeIdxT(org::imm::ImmId::*)() const>(&org::imm::ImmId::getNodeIndex))
    .function("getReadableId", static_cast<std::string(org::imm::ImmId::*)() const>(&org::imm::ImmId::getReadableId))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmOrg>("ImmOrg")
    ;
  emscripten::class_<org::imm::ImmPathStep>("ImmPathStep")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmPath>("ImmPath")
    .property("root", &org::imm::ImmPath::root)
    .property("path", &org::imm::ImmPath::path)
    .function("empty", static_cast<bool(org::imm::ImmPath::*)() const>(&org::imm::ImmPath::empty))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmUniqId>("ImmUniqId")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmNoneValueRead>("ImmNoneValueRead")
    ;
  emscripten::class_<org::imm::ImmErrorItemValueRead>("ImmErrorItemValueRead")
    .function("getMessage", static_cast<immer::box<hstd::Str> const&(org::imm::ImmErrorItemValueRead::*)() const>(&org::imm::ImmErrorItemValueRead::getMessage))
    .function("getFunction", static_cast<immer::box<std::optional<hstd::Str>> const&(org::imm::ImmErrorItemValueRead::*)() const>(&org::imm::ImmErrorItemValueRead::getFunction))
    .function("getLine", static_cast<immer::box<std::optional<int>> const&(org::imm::ImmErrorItemValueRead::*)() const>(&org::imm::ImmErrorItemValueRead::getLine))
    ;
  emscripten::class_<org::imm::ImmErrorGroupValueRead>("ImmErrorGroupValueRead")
    .function("getDiagnostics", static_cast<immer::flex_vector<org::imm::ImmIdT<org::imm::ImmErrorItem>> const&(org::imm::ImmErrorGroupValueRead::*)() const>(&org::imm::ImmErrorGroupValueRead::getDiagnostics))
    .function("getFunction", static_cast<immer::box<std::optional<hstd::Str>> const&(org::imm::ImmErrorGroupValueRead::*)() const>(&org::imm::ImmErrorGroupValueRead::getFunction))
    .function("getLine", static_cast<immer::box<std::optional<int>> const&(org::imm::ImmErrorGroupValueRead::*)() const>(&org::imm::ImmErrorGroupValueRead::getLine))
    ;
  emscripten::class_<org::imm::ImmStmtListValueRead>("ImmStmtListValueRead")
    ;
  emscripten::class_<org::imm::ImmEmptyValueRead>("ImmEmptyValueRead")
    ;
  emscripten::class_<org::imm::ImmCmdCaptionValueRead>("ImmCmdCaptionValueRead")
    .function("getText", static_cast<org::imm::ImmIdT<org::imm::ImmParagraph> const&(org::imm::ImmCmdCaptionValueRead::*)() const>(&org::imm::ImmCmdCaptionValueRead::getText))
    ;
  emscripten::class_<org::imm::ImmCmdColumnsValueRead>("ImmCmdColumnsValueRead")
    .function("getView", static_cast<org::sem::ColumnView const&(org::imm::ImmCmdColumnsValueRead::*)() const>(&org::imm::ImmCmdColumnsValueRead::getView))
    ;
  emscripten::class_<org::imm::ImmCmdNameValueRead>("ImmCmdNameValueRead")
    .function("getName", static_cast<immer::box<hstd::Str> const&(org::imm::ImmCmdNameValueRead::*)() const>(&org::imm::ImmCmdNameValueRead::getName))
    ;
  emscripten::class_<org::imm::ImmCmdCustomArgsValueRead>("ImmCmdCustomArgsValueRead")
    .function("getName", static_cast<immer::box<hstd::Str> const&(org::imm::ImmCmdCustomArgsValueRead::*)() const>(&org::imm::ImmCmdCustomArgsValueRead::getName))
    .function("getIsattached", static_cast<bool const&(org::imm::ImmCmdCustomArgsValueRead::*)() const>(&org::imm::ImmCmdCustomArgsValueRead::getIsattached))
    ;
  emscripten::class_<org::imm::ImmCmdCustomRawValueRead>("ImmCmdCustomRawValueRead")
    .function("getName", static_cast<immer::box<hstd::Str> const&(org::imm::ImmCmdCustomRawValueRead::*)() const>(&org::imm::ImmCmdCustomRawValueRead::getName))
    .function("getIsattached", static_cast<bool const&(org::imm::ImmCmdCustomRawValueRead::*)() const>(&org::imm::ImmCmdCustomRawValueRead::getIsattached))
    .function("getText", static_cast<immer::box<hstd::Str> const&(org::imm::ImmCmdCustomRawValueRead::*)() const>(&org::imm::ImmCmdCustomRawValueRead::getText))
    ;
  emscripten::class_<org::imm::ImmCmdCustomTextValueRead>("ImmCmdCustomTextValueRead")
    .function("getName", static_cast<immer::box<hstd::Str> const&(org::imm::ImmCmdCustomTextValueRead::*)() const>(&org::imm::ImmCmdCustomTextValueRead::getName))
    .function("getIsattached", static_cast<bool const&(org::imm::ImmCmdCustomTextValueRead::*)() const>(&org::imm::ImmCmdCustomTextValueRead::getIsattached))
    .function("getText", static_cast<org::imm::ImmIdT<org::imm::ImmParagraph> const&(org::imm::ImmCmdCustomTextValueRead::*)() const>(&org::imm::ImmCmdCustomTextValueRead::getText))
    ;
  emscripten::class_<org::imm::ImmCmdCallValueRead>("ImmCmdCallValueRead")
    .function("getName", static_cast<immer::box<hstd::Str> const&(org::imm::ImmCmdCallValueRead::*)() const>(&org::imm::ImmCmdCallValueRead::getName))
    .function("getFilename", static_cast<immer::box<std::optional<hstd::Str>> const&(org::imm::ImmCmdCallValueRead::*)() const>(&org::imm::ImmCmdCallValueRead::getFilename))
    .function("getInsideheaderattrs", static_cast<org::sem::AttrGroup const&(org::imm::ImmCmdCallValueRead::*)() const>(&org::imm::ImmCmdCallValueRead::getInsideheaderattrs))
    .function("getCallattrs", static_cast<org::sem::AttrGroup const&(org::imm::ImmCmdCallValueRead::*)() const>(&org::imm::ImmCmdCallValueRead::getCallattrs))
    .function("getEndheaderattrs", static_cast<org::sem::AttrGroup const&(org::imm::ImmCmdCallValueRead::*)() const>(&org::imm::ImmCmdCallValueRead::getEndheaderattrs))
    .function("getResult", static_cast<immer::flex_vector<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>> const&(org::imm::ImmCmdCallValueRead::*)() const>(&org::imm::ImmCmdCallValueRead::getResult))
    ;
  emscripten::class_<org::imm::ImmCmdTblfmValueRead>("ImmCmdTblfmValueRead")
    .function("getExpr", static_cast<org::sem::Tblfm const&(org::imm::ImmCmdTblfmValueRead::*)() const>(&org::imm::ImmCmdTblfmValueRead::getExpr))
    ;
  emscripten::class_<org::imm::ImmHashTagValueRead>("ImmHashTagValueRead")
    .function("getText", static_cast<org::sem::HashTagText const&(org::imm::ImmHashTagValueRead::*)() const>(&org::imm::ImmHashTagValueRead::getText))
    ;
  emscripten::class_<org::imm::ImmInlineFootnoteValueRead>("ImmInlineFootnoteValueRead")
    .function("getTag", static_cast<immer::box<hstd::Str> const&(org::imm::ImmInlineFootnoteValueRead::*)() const>(&org::imm::ImmInlineFootnoteValueRead::getTag))
    .function("getDefinition", static_cast<immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmOrg>>> const&(org::imm::ImmInlineFootnoteValueRead::*)() const>(&org::imm::ImmInlineFootnoteValueRead::getDefinition))
    ;
  emscripten::class_<org::imm::ImmInlineExportValueRead>("ImmInlineExportValueRead")
    .function("getExporter", static_cast<immer::box<hstd::Str> const&(org::imm::ImmInlineExportValueRead::*)() const>(&org::imm::ImmInlineExportValueRead::getExporter))
    .function("getContent", static_cast<immer::box<hstd::Str> const&(org::imm::ImmInlineExportValueRead::*)() const>(&org::imm::ImmInlineExportValueRead::getContent))
    ;
  emscripten::class_<org::imm::ImmTimeValueRead>("ImmTimeValueRead")
    .function("getIsactive", static_cast<bool const&(org::imm::ImmTimeValueRead::*)() const>(&org::imm::ImmTimeValueRead::getIsactive))
    .function("getTime", static_cast<org::imm::ImmTime::TimeVariant const&(org::imm::ImmTimeValueRead::*)() const>(&org::imm::ImmTimeValueRead::getTime))
    ;
  emscripten::class_<org::imm::ImmTimeRangeValueRead>("ImmTimeRangeValueRead")
    .function("getFrom", static_cast<org::imm::ImmIdT<org::imm::ImmTime> const&(org::imm::ImmTimeRangeValueRead::*)() const>(&org::imm::ImmTimeRangeValueRead::getFrom))
    .function("getTo", static_cast<org::imm::ImmIdT<org::imm::ImmTime> const&(org::imm::ImmTimeRangeValueRead::*)() const>(&org::imm::ImmTimeRangeValueRead::getTo))
    ;
  emscripten::class_<org::imm::ImmMacroValueRead>("ImmMacroValueRead")
    .function("getName", static_cast<immer::box<hstd::Str> const&(org::imm::ImmMacroValueRead::*)() const>(&org::imm::ImmMacroValueRead::getName))
    .function("getAttrs", static_cast<org::sem::AttrGroup const&(org::imm::ImmMacroValueRead::*)() const>(&org::imm::ImmMacroValueRead::getAttrs))
    ;
  emscripten::class_<org::imm::ImmSymbolValueRead>("ImmSymbolValueRead")
    .function("getName", static_cast<immer::box<hstd::Str> const&(org::imm::ImmSymbolValueRead::*)() const>(&org::imm::ImmSymbolValueRead::getName))
    .function("getParameters", static_cast<immer::flex_vector<org::imm::ImmSymbol::Param> const&(org::imm::ImmSymbolValueRead::*)() const>(&org::imm::ImmSymbolValueRead::getParameters))
    .function("getPositional", static_cast<immer::flex_vector<org::imm::ImmIdT<org::imm::ImmOrg>> const&(org::imm::ImmSymbolValueRead::*)() const>(&org::imm::ImmSymbolValueRead::getPositional))
    ;
  emscripten::class_<org::imm::ImmEscapedValueRead>("ImmEscapedValueRead")
    ;
  emscripten::class_<org::imm::ImmNewlineValueRead>("ImmNewlineValueRead")
    ;
  emscripten::class_<org::imm::ImmSpaceValueRead>("ImmSpaceValueRead")
    ;
  emscripten::class_<org::imm::ImmWordValueRead>("ImmWordValueRead")
    ;
  emscripten::class_<org::imm::ImmAtMentionValueRead>("ImmAtMentionValueRead")
    ;
  emscripten::class_<org::imm::ImmRawTextValueRead>("ImmRawTextValueRead")
    ;
  emscripten::class_<org::imm::ImmPunctuationValueRead>("ImmPunctuationValueRead")
    ;
  emscripten::class_<org::imm::ImmPlaceholderValueRead>("ImmPlaceholderValueRead")
    ;
  emscripten::class_<org::imm::ImmBigIdentValueRead>("ImmBigIdentValueRead")
    ;
  emscripten::class_<org::imm::ImmTextTargetValueRead>("ImmTextTargetValueRead")
    ;
  emscripten::class_<org::imm::ImmBoldValueRead>("ImmBoldValueRead")
    ;
  emscripten::class_<org::imm::ImmUnderlineValueRead>("ImmUnderlineValueRead")
    ;
  emscripten::class_<org::imm::ImmMonospaceValueRead>("ImmMonospaceValueRead")
    ;
  emscripten::class_<org::imm::ImmMarkQuoteValueRead>("ImmMarkQuoteValueRead")
    ;
  emscripten::class_<org::imm::ImmVerbatimValueRead>("ImmVerbatimValueRead")
    ;
  emscripten::class_<org::imm::ImmItalicValueRead>("ImmItalicValueRead")
    ;
  emscripten::class_<org::imm::ImmStrikeValueRead>("ImmStrikeValueRead")
    ;
  emscripten::class_<org::imm::ImmParValueRead>("ImmParValueRead")
    ;
  emscripten::class_<org::imm::ImmRadioTargetValueRead>("ImmRadioTargetValueRead")
    .function("getWords", static_cast<immer::flex_vector<hstd::Str> const&(org::imm::ImmRadioTargetValueRead::*)() const>(&org::imm::ImmRadioTargetValueRead::getWords))
    ;
  emscripten::class_<org::imm::ImmLatexValueRead>("ImmLatexValueRead")
    ;
  emscripten::class_<org::imm::ImmLinkValueRead>("ImmLinkValueRead")
    .function("getDescription", static_cast<immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&(org::imm::ImmLinkValueRead::*)() const>(&org::imm::ImmLinkValueRead::getDescription))
    .function("getTarget", static_cast<org::sem::LinkTarget const&(org::imm::ImmLinkValueRead::*)() const>(&org::imm::ImmLinkValueRead::getTarget))
    ;
  emscripten::class_<org::imm::ImmBlockCenterValueRead>("ImmBlockCenterValueRead")
    ;
  emscripten::class_<org::imm::ImmBlockQuoteValueRead>("ImmBlockQuoteValueRead")
    ;
  emscripten::class_<org::imm::ImmBlockCommentValueRead>("ImmBlockCommentValueRead")
    ;
  emscripten::class_<org::imm::ImmBlockVerseValueRead>("ImmBlockVerseValueRead")
    ;
  emscripten::class_<org::imm::ImmBlockDynamicFallbackValueRead>("ImmBlockDynamicFallbackValueRead")
    .function("getName", static_cast<immer::box<hstd::Str> const&(org::imm::ImmBlockDynamicFallbackValueRead::*)() const>(&org::imm::ImmBlockDynamicFallbackValueRead::getName))
    ;
  emscripten::class_<org::imm::ImmBlockExampleValueRead>("ImmBlockExampleValueRead")
    ;
  emscripten::class_<org::imm::ImmBlockExportValueRead>("ImmBlockExportValueRead")
    .function("getExporter", static_cast<immer::box<hstd::Str> const&(org::imm::ImmBlockExportValueRead::*)() const>(&org::imm::ImmBlockExportValueRead::getExporter))
    .function("getContent", static_cast<immer::box<hstd::Str> const&(org::imm::ImmBlockExportValueRead::*)() const>(&org::imm::ImmBlockExportValueRead::getContent))
    ;
  emscripten::class_<org::imm::ImmBlockAdmonitionValueRead>("ImmBlockAdmonitionValueRead")
    ;
  emscripten::class_<org::imm::ImmBlockCodeEvalResultValueRead>("ImmBlockCodeEvalResultValueRead")
    .function("getRaw", static_cast<immer::flex_vector<org::sem::OrgCodeEvalOutput> const&(org::imm::ImmBlockCodeEvalResultValueRead::*)() const>(&org::imm::ImmBlockCodeEvalResultValueRead::getRaw))
    .function("getNode", static_cast<org::imm::ImmIdT<org::imm::ImmOrg> const&(org::imm::ImmBlockCodeEvalResultValueRead::*)() const>(&org::imm::ImmBlockCodeEvalResultValueRead::getNode))
    ;
  emscripten::class_<org::imm::ImmBlockCodeValueRead>("ImmBlockCodeValueRead")
    .function("getLang", static_cast<immer::box<std::optional<hstd::Str>> const&(org::imm::ImmBlockCodeValueRead::*)() const>(&org::imm::ImmBlockCodeValueRead::getLang))
    .function("getExports", static_cast<BlockCodeExports const&(org::imm::ImmBlockCodeValueRead::*)() const>(&org::imm::ImmBlockCodeValueRead::getExports))
    .function("getResult", static_cast<immer::flex_vector<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>> const&(org::imm::ImmBlockCodeValueRead::*)() const>(&org::imm::ImmBlockCodeValueRead::getResult))
    .function("getLines", static_cast<immer::flex_vector<org::sem::BlockCodeLine> const&(org::imm::ImmBlockCodeValueRead::*)() const>(&org::imm::ImmBlockCodeValueRead::getLines))
    .function("getCache", static_cast<bool const&(org::imm::ImmBlockCodeValueRead::*)() const>(&org::imm::ImmBlockCodeValueRead::getCache))
    .function("getEval", static_cast<bool const&(org::imm::ImmBlockCodeValueRead::*)() const>(&org::imm::ImmBlockCodeValueRead::getEval))
    .function("getNoweb", static_cast<bool const&(org::imm::ImmBlockCodeValueRead::*)() const>(&org::imm::ImmBlockCodeValueRead::getNoweb))
    .function("getHlines", static_cast<bool const&(org::imm::ImmBlockCodeValueRead::*)() const>(&org::imm::ImmBlockCodeValueRead::getHlines))
    .function("getTangle", static_cast<bool const&(org::imm::ImmBlockCodeValueRead::*)() const>(&org::imm::ImmBlockCodeValueRead::getTangle))
    .function("getSwitches", static_cast<org::sem::AttrGroup const&(org::imm::ImmBlockCodeValueRead::*)() const>(&org::imm::ImmBlockCodeValueRead::getSwitches))
    ;
  emscripten::class_<org::imm::ImmSubtreeLogValueRead>("ImmSubtreeLogValueRead")
    .function("getHead", static_cast<org::sem::SubtreeLogHead const&(org::imm::ImmSubtreeLogValueRead::*)() const>(&org::imm::ImmSubtreeLogValueRead::getHead))
    .function("getDesc", static_cast<immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmStmtList>>> const&(org::imm::ImmSubtreeLogValueRead::*)() const>(&org::imm::ImmSubtreeLogValueRead::getDesc))
    ;
  emscripten::class_<org::imm::ImmSubtreeValueRead>("ImmSubtreeValueRead")
    .function("getLevel", static_cast<int const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getLevel))
    .function("getTreeid", static_cast<immer::box<std::optional<hstd::Str>> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getTreeid))
    .function("getTodo", static_cast<immer::box<std::optional<hstd::Str>> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getTodo))
    .function("getCompletion", static_cast<immer::box<std::optional<org::sem::SubtreeCompletion>> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getCompletion))
    .function("getDescription", static_cast<immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getDescription))
    .function("getTags", static_cast<immer::flex_vector<org::imm::ImmIdT<org::imm::ImmHashTag>> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getTags))
    .function("getTitle", static_cast<org::imm::ImmIdT<org::imm::ImmParagraph> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getTitle))
    .function("getLogbook", static_cast<immer::flex_vector<org::imm::ImmIdT<org::imm::ImmSubtreeLog>> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getLogbook))
    .function("getProperties", static_cast<immer::flex_vector<org::sem::NamedProperty> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getProperties))
    .function("getClosed", static_cast<immer::box<std::optional<hstd::UserTime>> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getClosed))
    .function("getDeadline", static_cast<immer::box<std::optional<hstd::UserTime>> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getDeadline))
    .function("getScheduled", static_cast<immer::box<std::optional<hstd::UserTime>> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getScheduled))
    .function("getIscomment", static_cast<bool const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getIscomment))
    .function("getIsarchived", static_cast<bool const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getIsarchived))
    .function("getPriority", static_cast<immer::box<std::optional<hstd::Str>> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getPriority))
    ;
  emscripten::class_<org::imm::ImmCellValueRead>("ImmCellValueRead")
    .function("getIsblock", static_cast<bool const&(org::imm::ImmCellValueRead::*)() const>(&org::imm::ImmCellValueRead::getIsblock))
    ;
  emscripten::class_<org::imm::ImmRowValueRead>("ImmRowValueRead")
    .function("getCells", static_cast<immer::flex_vector<org::imm::ImmIdT<org::imm::ImmCell>> const&(org::imm::ImmRowValueRead::*)() const>(&org::imm::ImmRowValueRead::getCells))
    .function("getIsblock", static_cast<bool const&(org::imm::ImmRowValueRead::*)() const>(&org::imm::ImmRowValueRead::getIsblock))
    ;
  emscripten::class_<org::imm::ImmTableValueRead>("ImmTableValueRead")
    .function("getRows", static_cast<immer::flex_vector<org::imm::ImmIdT<org::imm::ImmRow>> const&(org::imm::ImmTableValueRead::*)() const>(&org::imm::ImmTableValueRead::getRows))
    .function("getIsblock", static_cast<bool const&(org::imm::ImmTableValueRead::*)() const>(&org::imm::ImmTableValueRead::getIsblock))
    ;
  emscripten::class_<org::imm::ImmParagraphValueRead>("ImmParagraphValueRead")
    ;
  emscripten::class_<org::imm::ImmColonExampleValueRead>("ImmColonExampleValueRead")
    ;
  emscripten::class_<org::imm::ImmCmdAttrValueRead>("ImmCmdAttrValueRead")
    .function("getTarget", static_cast<immer::box<hstd::Str> const&(org::imm::ImmCmdAttrValueRead::*)() const>(&org::imm::ImmCmdAttrValueRead::getTarget))
    ;
  emscripten::class_<org::imm::ImmCmdExportValueRead>("ImmCmdExportValueRead")
    .function("getExporter", static_cast<immer::box<hstd::Str> const&(org::imm::ImmCmdExportValueRead::*)() const>(&org::imm::ImmCmdExportValueRead::getExporter))
    .function("getContent", static_cast<immer::box<hstd::Str> const&(org::imm::ImmCmdExportValueRead::*)() const>(&org::imm::ImmCmdExportValueRead::getContent))
    ;
  emscripten::class_<org::imm::ImmCallValueRead>("ImmCallValueRead")
    .function("getName", static_cast<immer::box<hstd::Str> const&(org::imm::ImmCallValueRead::*)() const>(&org::imm::ImmCallValueRead::getName))
    .function("getAttrs", static_cast<org::sem::AttrGroup const&(org::imm::ImmCallValueRead::*)() const>(&org::imm::ImmCallValueRead::getAttrs))
    .function("getIscommand", static_cast<bool const&(org::imm::ImmCallValueRead::*)() const>(&org::imm::ImmCallValueRead::getIscommand))
    ;
  emscripten::class_<org::imm::ImmListValueRead>("ImmListValueRead")
    ;
  emscripten::class_<org::imm::ImmListItemValueRead>("ImmListItemValueRead")
    .function("getCheckbox", static_cast<CheckboxState const&(org::imm::ImmListItemValueRead::*)() const>(&org::imm::ImmListItemValueRead::getCheckbox))
    .function("getHeader", static_cast<immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&(org::imm::ImmListItemValueRead::*)() const>(&org::imm::ImmListItemValueRead::getHeader))
    .function("getBullet", static_cast<immer::box<std::optional<hstd::Str>> const&(org::imm::ImmListItemValueRead::*)() const>(&org::imm::ImmListItemValueRead::getBullet))
    ;
  emscripten::class_<org::imm::ImmDocumentOptionsValueRead>("ImmDocumentOptionsValueRead")
    .function("getInitialvisibility", static_cast<InitialSubtreeVisibility const&(org::imm::ImmDocumentOptionsValueRead::*)() const>(&org::imm::ImmDocumentOptionsValueRead::getInitialvisibility))
    .function("getProperties", static_cast<immer::flex_vector<org::sem::NamedProperty> const&(org::imm::ImmDocumentOptionsValueRead::*)() const>(&org::imm::ImmDocumentOptionsValueRead::getProperties))
    .function("getExportconfig", static_cast<org::sem::DocumentExportConfig const&(org::imm::ImmDocumentOptionsValueRead::*)() const>(&org::imm::ImmDocumentOptionsValueRead::getExportconfig))
    .function("getFixedwidthsections", static_cast<immer::box<std::optional<bool>> const&(org::imm::ImmDocumentOptionsValueRead::*)() const>(&org::imm::ImmDocumentOptionsValueRead::getFixedwidthsections))
    .function("getStartupindented", static_cast<immer::box<std::optional<bool>> const&(org::imm::ImmDocumentOptionsValueRead::*)() const>(&org::imm::ImmDocumentOptionsValueRead::getStartupindented))
    .function("getCategory", static_cast<immer::box<std::optional<hstd::Str>> const&(org::imm::ImmDocumentOptionsValueRead::*)() const>(&org::imm::ImmDocumentOptionsValueRead::getCategory))
    .function("getSetupfile", static_cast<immer::box<std::optional<hstd::Str>> const&(org::imm::ImmDocumentOptionsValueRead::*)() const>(&org::imm::ImmDocumentOptionsValueRead::getSetupfile))
    .function("getMaxsubtreelevelexport", static_cast<immer::box<std::optional<int>> const&(org::imm::ImmDocumentOptionsValueRead::*)() const>(&org::imm::ImmDocumentOptionsValueRead::getMaxsubtreelevelexport))
    .function("getColumns", static_cast<immer::box<std::optional<org::sem::ColumnView>> const&(org::imm::ImmDocumentOptionsValueRead::*)() const>(&org::imm::ImmDocumentOptionsValueRead::getColumns))
    .function("getTodokeywords", static_cast<immer::flex_vector<org::sem::TodoKeyword> const&(org::imm::ImmDocumentOptionsValueRead::*)() const>(&org::imm::ImmDocumentOptionsValueRead::getTodokeywords))
    .function("getDonekeywords", static_cast<immer::flex_vector<org::sem::TodoKeyword> const&(org::imm::ImmDocumentOptionsValueRead::*)() const>(&org::imm::ImmDocumentOptionsValueRead::getDonekeywords))
    ;
  emscripten::class_<org::imm::ImmDocumentFragmentValueRead>("ImmDocumentFragmentValueRead")
    .function("getBaseline", static_cast<int const&(org::imm::ImmDocumentFragmentValueRead::*)() const>(&org::imm::ImmDocumentFragmentValueRead::getBaseline))
    .function("getBasecol", static_cast<int const&(org::imm::ImmDocumentFragmentValueRead::*)() const>(&org::imm::ImmDocumentFragmentValueRead::getBasecol))
    ;
  emscripten::class_<org::imm::ImmCriticMarkupValueRead>("ImmCriticMarkupValueRead")
    .function("getKind", static_cast<org::imm::ImmCriticMarkup::Kind const&(org::imm::ImmCriticMarkupValueRead::*)() const>(&org::imm::ImmCriticMarkupValueRead::getKind))
    ;
  emscripten::class_<org::imm::ImmDocumentValueRead>("ImmDocumentValueRead")
    .function("getTitle", static_cast<immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&(org::imm::ImmDocumentValueRead::*)() const>(&org::imm::ImmDocumentValueRead::getTitle))
    .function("getAuthor", static_cast<immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&(org::imm::ImmDocumentValueRead::*)() const>(&org::imm::ImmDocumentValueRead::getAuthor))
    .function("getCreator", static_cast<immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&(org::imm::ImmDocumentValueRead::*)() const>(&org::imm::ImmDocumentValueRead::getCreator))
    .function("getFiletags", static_cast<immer::flex_vector<org::imm::ImmIdT<org::imm::ImmHashTag>> const&(org::imm::ImmDocumentValueRead::*)() const>(&org::imm::ImmDocumentValueRead::getFiletags))
    .function("getEmail", static_cast<immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmRawText>>> const&(org::imm::ImmDocumentValueRead::*)() const>(&org::imm::ImmDocumentValueRead::getEmail))
    .function("getLanguage", static_cast<immer::flex_vector<hstd::Str> const&(org::imm::ImmDocumentValueRead::*)() const>(&org::imm::ImmDocumentValueRead::getLanguage))
    .function("getOptions", static_cast<org::imm::ImmIdT<org::imm::ImmDocumentOptions> const&(org::imm::ImmDocumentValueRead::*)() const>(&org::imm::ImmDocumentValueRead::getOptions))
    .function("getExportfilename", static_cast<immer::box<std::optional<hstd::Str>> const&(org::imm::ImmDocumentValueRead::*)() const>(&org::imm::ImmDocumentValueRead::getExportfilename))
    ;
  emscripten::class_<org::imm::ImmFileTargetValueRead>("ImmFileTargetValueRead")
    .function("getPath", static_cast<immer::box<hstd::Str> const&(org::imm::ImmFileTargetValueRead::*)() const>(&org::imm::ImmFileTargetValueRead::getPath))
    .function("getLine", static_cast<immer::box<std::optional<int>> const&(org::imm::ImmFileTargetValueRead::*)() const>(&org::imm::ImmFileTargetValueRead::getLine))
    .function("getSearchtarget", static_cast<immer::box<std::optional<hstd::Str>> const&(org::imm::ImmFileTargetValueRead::*)() const>(&org::imm::ImmFileTargetValueRead::getSearchtarget))
    .function("getRestricttoheadlines", static_cast<bool const&(org::imm::ImmFileTargetValueRead::*)() const>(&org::imm::ImmFileTargetValueRead::getRestricttoheadlines))
    .function("getTargetid", static_cast<immer::box<std::optional<hstd::Str>> const&(org::imm::ImmFileTargetValueRead::*)() const>(&org::imm::ImmFileTargetValueRead::getTargetid))
    .function("getRegexp", static_cast<immer::box<std::optional<hstd::Str>> const&(org::imm::ImmFileTargetValueRead::*)() const>(&org::imm::ImmFileTargetValueRead::getRegexp))
    ;
  emscripten::class_<org::imm::ImmTextSeparatorValueRead>("ImmTextSeparatorValueRead")
    ;
  emscripten::class_<org::imm::ImmDocumentGroupValueRead>("ImmDocumentGroupValueRead")
    ;
  emscripten::class_<org::imm::ImmFileValueRead>("ImmFileValueRead")
    .function("getRelpath", static_cast<immer::box<hstd::Str> const&(org::imm::ImmFileValueRead::*)() const>(&org::imm::ImmFileValueRead::getRelpath))
    .function("getAbspath", static_cast<immer::box<hstd::Str> const&(org::imm::ImmFileValueRead::*)() const>(&org::imm::ImmFileValueRead::getAbspath))
    .function("getData", static_cast<org::imm::ImmFile::Data const&(org::imm::ImmFileValueRead::*)() const>(&org::imm::ImmFileValueRead::getData))
    ;
  emscripten::class_<org::imm::ImmDirectoryValueRead>("ImmDirectoryValueRead")
    .function("getRelpath", static_cast<immer::box<hstd::Str> const&(org::imm::ImmDirectoryValueRead::*)() const>(&org::imm::ImmDirectoryValueRead::getRelpath))
    .function("getAbspath", static_cast<immer::box<hstd::Str> const&(org::imm::ImmDirectoryValueRead::*)() const>(&org::imm::ImmDirectoryValueRead::getAbspath))
    ;
  emscripten::class_<org::imm::ImmSymlinkValueRead>("ImmSymlinkValueRead")
    .function("getIsdirectory", static_cast<bool const&(org::imm::ImmSymlinkValueRead::*)() const>(&org::imm::ImmSymlinkValueRead::getIsdirectory))
    .function("getAbspath", static_cast<immer::box<hstd::Str> const&(org::imm::ImmSymlinkValueRead::*)() const>(&org::imm::ImmSymlinkValueRead::getAbspath))
    ;
  emscripten::class_<org::imm::ImmCmdIncludeValueRead>("ImmCmdIncludeValueRead")
    .function("getPath", static_cast<immer::box<hstd::Str> const&(org::imm::ImmCmdIncludeValueRead::*)() const>(&org::imm::ImmCmdIncludeValueRead::getPath))
    .function("getFirstline", static_cast<immer::box<std::optional<int>> const&(org::imm::ImmCmdIncludeValueRead::*)() const>(&org::imm::ImmCmdIncludeValueRead::getFirstline))
    .function("getLastline", static_cast<immer::box<std::optional<int>> const&(org::imm::ImmCmdIncludeValueRead::*)() const>(&org::imm::ImmCmdIncludeValueRead::getLastline))
    .function("getData", static_cast<org::imm::ImmCmdInclude::Data const&(org::imm::ImmCmdIncludeValueRead::*)() const>(&org::imm::ImmCmdIncludeValueRead::getData))
    ;
  emscripten::class_<org::imm::ImmAstContext>("ImmAstContext")
    .smart_ptr<std::shared_ptr<org::imm::ImmAstContext>>("ImmAstContext")
    .function("addRoot", static_cast<org::imm::ImmAstVersion(org::imm::ImmAstContext::*)(org::sem::SemId<org::sem::Org>)>(&org::imm::ImmAstContext::addRoot))
    .function("get", static_cast<org::sem::SemId<org::sem::Org>(org::imm::ImmAstContext::*)(org::imm::ImmId)>(&org::imm::ImmAstContext::get))
    ;
  emscripten::class_<org::imm::ImmAstVersion>("ImmAstVersion")
    .function("getRoot", static_cast<org::imm::ImmId(org::imm::ImmAstVersion::*)() const>(&org::imm::ImmAstVersion::getRoot))
    .function("getRootAdapter", static_cast<org::imm::ImmAdapter(org::imm::ImmAstVersion::*)() const>(&org::imm::ImmAstVersion::getRootAdapter))
    .function("getContext", static_cast<std::shared_ptr<org::imm::ImmAstContext>(org::imm::ImmAstVersion::*)() const>(&org::imm::ImmAstVersion::getContext))
    .constructor<>()
    ;
}

void subdivide_2(org::bind::js::type_registration_guard& g) {
  emscripten::class_<org::imm::ImmAdapter>("ImmAdapter")
    .function("size", static_cast<int(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::size))
    .function("isNil", static_cast<bool(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::isNil))
    .function("isRoot", static_cast<bool(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::isRoot))
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::getKind))
    .function("uniq", static_cast<org::imm::ImmUniqId(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::uniq))
    .function("treeReprString", static_cast<std::string(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::treeReprString))
    .function("treeReprStringOpts", static_cast<std::string(org::imm::ImmAdapter::*)(org::imm::ImmAdapter::TreeReprConf const&) const>(&org::imm::ImmAdapter::treeReprStringOpts))
    .function("isDirectParentOf", static_cast<bool(org::imm::ImmAdapter::*)(org::imm::ImmAdapter const&) const>(&org::imm::ImmAdapter::isDirectParentOf))
    .function("isIndirectParentOf", static_cast<bool(org::imm::ImmAdapter::*)(org::imm::ImmAdapter const&) const>(&org::imm::ImmAdapter::isIndirectParentOf))
    .function("isSubnodeOf", static_cast<bool(org::imm::ImmAdapter::*)(org::imm::ImmAdapter const&) const>(&org::imm::ImmAdapter::isSubnodeOf))
    .function("getParent", static_cast<std::optional<org::imm::ImmAdapter>(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::getParent))
    .function("getSelfIndex", static_cast<int(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::getSelfIndex))
    .function("atField", static_cast<org::imm::ImmAdapter(org::imm::ImmAdapter::*)(org::imm::ImmReflFieldId const&) const>(&org::imm::ImmAdapter::at))
    .function("atIndex", static_cast<org::imm::ImmAdapter(org::imm::ImmAdapter::*)(int, bool) const>(&org::imm::ImmAdapter::at))
    .function("atPath", static_cast<org::imm::ImmAdapter(org::imm::ImmAdapter::*)(hstd::Vec<int> const&, bool) const>(&org::imm::ImmAdapter::at))
    .function("is", static_cast<bool(org::imm::ImmAdapter::*)(OrgSemKind) const>(&org::imm::ImmAdapter::is))
    .function("sub", static_cast<hstd::Vec<org::imm::ImmAdapter>(org::imm::ImmAdapter::*)(bool) const>(&org::imm::ImmAdapter::sub))
    ;
  emscripten::class_<org::imm::ImmAdapter::TreeReprConf>("ImmAdapterTreeReprConf")
    .property("maxDepth", &org::imm::ImmAdapter::TreeReprConf::maxDepth)
    .property("withAuxFields", &org::imm::ImmAdapter::TreeReprConf::withAuxFields)
    .property("withReflFields", &org::imm::ImmAdapter::TreeReprConf::withReflFields)
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmAdapterVirtualBase>("ImmAdapterVirtualBase")
    ;
  emscripten::class_<org::OrgParseFragment>("OrgParseFragment")
    .property("baseLine", &org::OrgParseFragment::baseLine)
    .property("baseCol", &org::OrgParseFragment::baseCol)
    .property("text", &org::OrgParseFragment::text)
    .constructor<>()
    ;
  emscripten::class_<org::OrgParseParameters>("OrgParseParameters")
    .smart_ptr<std::shared_ptr<org::OrgParseParameters>>("OrgParseParameters")
    .property("baseTokenTracePath", &org::OrgParseParameters::baseTokenTracePath)
    .property("tokenTracePath", &org::OrgParseParameters::tokenTracePath)
    .property("parseTracePath", &org::OrgParseParameters::parseTracePath)
    .property("semTracePath", &org::OrgParseParameters::semTracePath)
    .constructor(&org::bind::js::holder_type_constructor<std::shared_ptr<org::OrgParseParameters>>)
    ;
  emscripten::class_<org::OrgDirectoryParseParameters>("OrgDirectoryParseParameters")
    .smart_ptr<std::shared_ptr<org::OrgDirectoryParseParameters>>("OrgDirectoryParseParameters")
    .constructor(&org::bind::js::holder_type_constructor<std::shared_ptr<org::OrgDirectoryParseParameters>>)
    ;
  emscripten::class_<org::OrgYamlExportOpts>("OrgYamlExportOpts")
    .property("skipNullFields", &org::OrgYamlExportOpts::skipNullFields)
    .property("skipFalseFields", &org::OrgYamlExportOpts::skipFalseFields)
    .property("skipZeroFields", &org::OrgYamlExportOpts::skipZeroFields)
    .property("skipLocation", &org::OrgYamlExportOpts::skipLocation)
    .property("skipId", &org::OrgYamlExportOpts::skipId)
    .constructor<>()
    ;
  emscripten::class_<org::OrgTreeExportOpts>("OrgTreeExportOpts")
    .property("withLineCol", &org::OrgTreeExportOpts::withLineCol)
    .property("withOriginalId", &org::OrgTreeExportOpts::withOriginalId)
    .property("withSubnodeIdx", &org::OrgTreeExportOpts::withSubnodeIdx)
    .property("skipEmptyFields", &org::OrgTreeExportOpts::skipEmptyFields)
    .property("startLevel", &org::OrgTreeExportOpts::startLevel)
    .property("withColor", &org::OrgTreeExportOpts::withColor)
    .property("maxDepth", &org::OrgTreeExportOpts::maxDepth)
    .constructor<>()
    ;
  emscripten::class_<org::AstTrackingPath>("AstTrackingPath")
    .property("path", &org::AstTrackingPath::path)
    .function("getParent", static_cast<org::sem::SemId<org::sem::Org>(org::AstTrackingPath::*)(int) const>(&org::AstTrackingPath::getParent))
    .function("getNode", static_cast<org::sem::SemId<org::sem::Org>(org::AstTrackingPath::*)() const>(&org::AstTrackingPath::getNode))
    .constructor<>()
    ;
  emscripten::class_<org::AstTrackingAlternatives>("AstTrackingAlternatives")
    .function("getAllNodes", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::AstTrackingAlternatives::*)() const>(&org::AstTrackingAlternatives::getAllNodes))
    .function("getNode", static_cast<org::sem::SemId<org::sem::Org>(org::AstTrackingAlternatives::*)() const>(&org::AstTrackingAlternatives::getNode))
    .constructor<>()
    ;
  emscripten::class_<org::AstTrackingGroup>("AstTrackingGroup")
    .function("getRadioTargetConst", static_cast<org::AstTrackingGroup::RadioTarget const&(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::getRadioTarget))
    .function("getTrackedHashtagConst", static_cast<org::AstTrackingGroup::TrackedHashtag const&(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::getTrackedHashtag))
    .function("getTrackedHashtagMut", static_cast<org::AstTrackingGroup::TrackedHashtag&(org::AstTrackingGroup::*)()>(&org::AstTrackingGroup::getTrackedHashtag))
    .function("getSingleConst", static_cast<org::AstTrackingGroup::Single const&(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::getSingle))
    .function("getRadioTargetMut", static_cast<org::AstTrackingGroup::RadioTarget&(org::AstTrackingGroup::*)()>(&org::AstTrackingGroup::getRadioTarget))
    .function("getSingleMut", static_cast<org::AstTrackingGroup::Single&(org::AstTrackingGroup::*)()>(&org::AstTrackingGroup::getSingle))
    .function("isSingle", static_cast<bool(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::isSingle))
    .function("isTrackedHashtag", static_cast<bool(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::isTrackedHashtag))
    .function("isRadioTarget", static_cast<bool(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::isRadioTarget))
    .constructor<>()
    ;
  emscripten::class_<org::AstTrackingGroup::RadioTarget>("AstTrackingGroupRadioTarget")
    .property("target", &org::AstTrackingGroup::RadioTarget::target)
    .property("nodes", &org::AstTrackingGroup::RadioTarget::nodes)
    .constructor<>()
    ;
  emscripten::class_<org::AstTrackingGroup::Single>("AstTrackingGroupSingle")
    .property("node", &org::AstTrackingGroup::Single::node)
    .constructor<>()
    ;
  emscripten::class_<org::AstTrackingGroup::TrackedHashtag>("AstTrackingGroupTrackedHashtag")
    .property("tag", &org::AstTrackingGroup::TrackedHashtag::tag)
    .property("targets", &org::AstTrackingGroup::TrackedHashtag::targets)
    .constructor<>()
    ;
  emscripten::class_<org::AstTrackingMap>("AstTrackingMap")
    .property("footnotes", &org::AstTrackingMap::footnotes)
    .property("subtrees", &org::AstTrackingMap::subtrees)
    .property("names", &org::AstTrackingMap::names)
    .property("anchorTargets", &org::AstTrackingMap::anchorTargets)
    .property("radioTargets", &org::AstTrackingMap::radioTargets)
    .property("hashtagDefinitions", &org::AstTrackingMap::hashtagDefinitions)
    .function("getIdPath", static_cast<std::optional<org::AstTrackingAlternatives>(org::AstTrackingMap::*)(hstd::Str const&) const>(&org::AstTrackingMap::getIdPath))
    .function("getNamePath", static_cast<std::optional<org::AstTrackingAlternatives>(org::AstTrackingMap::*)(hstd::Str const&) const>(&org::AstTrackingMap::getNamePath))
    .function("getAnchorTarget", static_cast<std::optional<org::AstTrackingAlternatives>(org::AstTrackingMap::*)(hstd::Str const&) const>(&org::AstTrackingMap::getAnchorTarget))
    .function("getFootnotePath", static_cast<std::optional<org::AstTrackingAlternatives>(org::AstTrackingMap::*)(hstd::Str const&) const>(&org::AstTrackingMap::getFootnotePath))
    .constructor<>()
    ;
  emscripten::class_<hstd::SequenceSegment>("SequenceSegment")
    .property("kind", &hstd::SequenceSegment::kind)
    .property("first", &hstd::SequenceSegment::first)
    .property("last", &hstd::SequenceSegment::last)
    .constructor<>()
    ;
  emscripten::class_<hstd::SequenceSegmentGroup>("SequenceSegmentGroup")
    .property("kind", &hstd::SequenceSegmentGroup::kind)
    .property("segments", &hstd::SequenceSegmentGroup::segments)
    .constructor<>()
    ;
  emscripten::class_<hstd::SequenceAnnotationTag>("SequenceAnnotationTag")
    .property("groupKind", &hstd::SequenceAnnotationTag::groupKind)
    .property("segmentKinds", &hstd::SequenceAnnotationTag::segmentKinds)
    .constructor<>()
    ;
  emscripten::class_<hstd::SequenceAnnotation>("SequenceAnnotation")
    .property("first", &hstd::SequenceAnnotation::first)
    .property("last", &hstd::SequenceAnnotation::last)
    .property("annotations", &hstd::SequenceAnnotation::annotations)
    .function("isAnnotatedWith", static_cast<bool(hstd::SequenceAnnotation::*)(int, int) const>(&hstd::SequenceAnnotation::isAnnotatedWith))
    .constructor<>()
    ;
  emscripten::class_<org::graph::MapLink>("GraphMapLink")
    .function("getRadio", static_cast<org::graph::MapLink::Radio&(org::graph::MapLink::*)()>(&org::graph::MapLink::getRadio))
    .function("getRadio", static_cast<org::graph::MapLink::Radio const&(org::graph::MapLink::*)() const>(&org::graph::MapLink::getRadio))
    .function("isRadio", static_cast<bool(org::graph::MapLink::*)() const>(&org::graph::MapLink::isRadio))
    .function("getLink", static_cast<org::graph::MapLink::Link&(org::graph::MapLink::*)()>(&org::graph::MapLink::getLink))
    .function("getLink", static_cast<org::graph::MapLink::Link const&(org::graph::MapLink::*)() const>(&org::graph::MapLink::getLink))
    .function("isLink", static_cast<bool(org::graph::MapLink::*)() const>(&org::graph::MapLink::isLink))
    .function("getKind", static_cast<org::graph::MapLink::Kind(org::graph::MapLink::*)() const>(&org::graph::MapLink::getKind))
    .constructor<>()
    ;
  emscripten::class_<org::graph::MapLink::Link>("GraphMapLinkLink")
    .property("link", &org::graph::MapLink::Link::link)
    .property("description", &org::graph::MapLink::Link::description)
    .constructor<>()
    ;
  emscripten::class_<org::graph::MapLink::Radio>("GraphMapLinkRadio")
    .property("target", &org::graph::MapLink::Radio::target)
    .constructor<>()
    ;
  emscripten::class_<org::graph::MapNodeProp>("GraphMapNodeProp")
    .property("id", &org::graph::MapNodeProp::id)
    .property("unresolved", &org::graph::MapNodeProp::unresolved)
    .function("getAdapter", static_cast<org::imm::ImmAdapter(org::graph::MapNodeProp::*)(std::shared_ptr<org::imm::ImmAstContext> const&) const>(&org::graph::MapNodeProp::getAdapter))
    .function("getSubtreeId", static_cast<std::optional<hstd::Str>(org::graph::MapNodeProp::*)(std::shared_ptr<org::imm::ImmAstContext> const&) const>(&org::graph::MapNodeProp::getSubtreeId))
    .function("getFootnoteName", static_cast<std::optional<hstd::Str>(org::graph::MapNodeProp::*)(std::shared_ptr<org::imm::ImmAstContext> const&) const>(&org::graph::MapNodeProp::getFootnoteName))
    .constructor<>()
    ;
  emscripten::class_<org::graph::MapEdgeProp>("GraphMapEdgeProp")
    .property("link", &org::graph::MapEdgeProp::link)
    .constructor<>()
    ;
  emscripten::class_<org::graph::MapNode>("GraphMapNode")
    .property("id", &org::graph::MapNode::id)
    .function("__eq__", static_cast<bool(org::graph::MapNode::*)(org::graph::MapNode const&) const>(&org::graph::MapNode::operator==))
    .function("__lt__", static_cast<bool(org::graph::MapNode::*)(org::graph::MapNode const&) const>(&org::graph::MapNode::operator<))
    .constructor<>()
    ;
  emscripten::class_<org::graph::MapEdge>("GraphMapEdge")
    .property("source", &org::graph::MapEdge::source)
    .property("target", &org::graph::MapEdge::target)
    .constructor<>()
    ;
  emscripten::class_<org::graph::MapGraph>("GraphMapGraph")
    .smart_ptr<std::shared_ptr<org::graph::MapGraph>>("GraphMapGraph")
    .property("nodeProps", &org::graph::MapGraph::nodeProps)
    .property("edgeProps", &org::graph::MapGraph::edgeProps)
    .property("adjList", &org::graph::MapGraph::adjList)
    .property("adjListIn", &org::graph::MapGraph::adjListIn)
    .function("nodeCount", static_cast<int(org::graph::MapGraph::*)() const>(&org::graph::MapGraph::nodeCount))
    .function("edgeCount", static_cast<int(org::graph::MapGraph::*)() const>(&org::graph::MapGraph::edgeCount))
    .function("outNodes", static_cast<org::graph::AdjNodesList const&(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::outNodes))
    .function("inNodes", static_cast<org::graph::AdjNodesList const&(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::inNodes))
    .function("adjEdges", static_cast<hstd::Vec<org::graph::MapEdge>(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::adjEdges))
    .function("adjNodes", static_cast<hstd::Vec<org::graph::MapNode>(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::adjNodes))
    .function("outEdges", static_cast<hstd::Vec<org::graph::MapEdge>(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::outEdges))
    .function("inEdges", static_cast<hstd::Vec<org::graph::MapEdge>(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::inEdges))
    .function("outDegree", static_cast<int(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::outDegree))
    .function("inDegree", static_cast<int(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::inDegree))
    .function("isRegisteredNode", static_cast<bool(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::isRegisteredNode))
    .function("isRegisteredNodeById", static_cast<bool(org::graph::MapGraph::*)(org::imm::ImmUniqId const&) const>(&org::graph::MapGraph::isRegisteredNode))
    .function("atMapNode", static_cast<org::graph::MapNodeProp const&(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::at))
    .function("atMapEdge", static_cast<org::graph::MapEdgeProp const&(org::graph::MapGraph::*)(org::graph::MapEdge const&) const>(&org::graph::MapGraph::at))
    .function("addEdge", static_cast<void(org::graph::MapGraph::*)(org::graph::MapEdge const&)>(&org::graph::MapGraph::addEdge))
    .function("addEdgeWithProp", static_cast<void(org::graph::MapGraph::*)(org::graph::MapEdge const&, org::graph::MapEdgeProp const&)>(&org::graph::MapGraph::addEdge))
    .function("addNode", static_cast<void(org::graph::MapGraph::*)(org::graph::MapNode const&)>(&org::graph::MapGraph::addNode))
    .function("addNodeWithProp", static_cast<void(org::graph::MapGraph::*)(org::graph::MapNode const&, org::graph::MapNodeProp const&)>(&org::graph::MapGraph::addNode))
    .function("hasEdge", static_cast<bool(org::graph::MapGraph::*)(org::graph::MapNode const&, org::graph::MapNode const&) const>(&org::graph::MapGraph::hasEdge))
    .function("hasNode", static_cast<bool(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::hasNode))
    .function("has2AdapterEdge", static_cast<bool(org::graph::MapGraph::*)(org::imm::ImmAdapter const&, org::imm::ImmAdapter const&) const>(&org::graph::MapGraph::hasEdge))
    .constructor(&org::bind::js::holder_type_constructor<std::shared_ptr<org::graph::MapGraph>>)
    ;
  emscripten::class_<org::graph::MapConfig>("GraphMapConfig")
    .smart_ptr<std::shared_ptr<org::graph::MapConfig>>("GraphMapConfig")
    .property("dbg", &org::graph::MapConfig::dbg)
    .constructor(&org::bind::js::holder_type_constructor<std::shared_ptr<org::graph::MapConfig>>)
    ;
  emscripten::class_<org::graph::MapGraphState>("GraphMapGraphState")
    .smart_ptr<std::shared_ptr<org::graph::MapGraphState>>("GraphMapGraphState")
    .property("graph", &org::graph::MapGraphState::graph)
    .property("ast", &org::graph::MapGraphState::ast)
    .class_function("FromAstContext", static_cast<std::shared_ptr<org::graph::MapGraphState>(*)(std::shared_ptr<org::imm::ImmAstContext>)>(&org::graph::MapGraphState::FromAstContext))
    .function("registerNode", static_cast<void(org::graph::MapGraphState::*)(org::graph::MapNodeProp const&, std::shared_ptr<org::graph::MapConfig> const&)>(&org::graph::MapGraphState::registerNode))
    .function("addNode", static_cast<void(org::graph::MapGraphState::*)(org::imm::ImmAdapter const&, std::shared_ptr<org::graph::MapConfig> const&)>(&org::graph::MapGraphState::addNode))
    .function("addNodeRec", static_cast<void(org::graph::MapGraphState::*)(std::shared_ptr<org::imm::ImmAstContext> const&, org::imm::ImmAdapter const&, std::shared_ptr<org::graph::MapConfig> const&)>(&org::graph::MapGraphState::addNodeRec))
    .function("getUnresolvedSubtreeLinks", static_cast<hstd::Vec<org::graph::MapLink>(org::graph::MapGraphState::*)(org::imm::ImmAdapterT<org::imm::ImmSubtree>, std::shared_ptr<org::graph::MapConfig> const&) const>(&org::graph::MapGraphState::getUnresolvedSubtreeLinks))
    .function("getUnresolvedLink", static_cast<std::optional<org::graph::MapLink>(org::graph::MapGraphState::*)(org::imm::ImmAdapterT<org::imm::ImmLink>, std::shared_ptr<org::graph::MapConfig> const&) const>(&org::graph::MapGraphState::getUnresolvedLink))
    ;
  emscripten::class_<org::sem::LispCode>("LispCode")
    .property("data", &org::sem::LispCode::data)
    .function("__eq__", static_cast<bool(org::sem::LispCode::*)(org::sem::LispCode const&) const>(&org::sem::LispCode::operator==))
    .function("isCall", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isCall))
    .function("getCallConst", static_cast<org::sem::LispCode::Call const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getCall))
    .function("getCallMut", static_cast<org::sem::LispCode::Call&(org::sem::LispCode::*)()>(&org::sem::LispCode::getCall))
    .function("isList", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isList))
    .function("getListConst", static_cast<org::sem::LispCode::List const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getList))
    .function("getListMut", static_cast<org::sem::LispCode::List&(org::sem::LispCode::*)()>(&org::sem::LispCode::getList))
    .function("isKeyValue", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isKeyValue))
    .function("getKeyValueConst", static_cast<org::sem::LispCode::KeyValue const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getKeyValue))
    .function("getKeyValueMut", static_cast<org::sem::LispCode::KeyValue&(org::sem::LispCode::*)()>(&org::sem::LispCode::getKeyValue))
    .function("isNumber", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isNumber))
    .function("getNumberConst", static_cast<org::sem::LispCode::Number const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getNumber))
    .function("getNumberMut", static_cast<org::sem::LispCode::Number&(org::sem::LispCode::*)()>(&org::sem::LispCode::getNumber))
    .function("isText", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isText))
    .function("getTextConst", static_cast<org::sem::LispCode::Text const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getText))
    .function("getTextMut", static_cast<org::sem::LispCode::Text&(org::sem::LispCode::*)()>(&org::sem::LispCode::getText))
    .function("isIdent", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isIdent))
    .function("getIdentConst", static_cast<org::sem::LispCode::Ident const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getIdent))
    .function("getIdentMut", static_cast<org::sem::LispCode::Ident&(org::sem::LispCode::*)()>(&org::sem::LispCode::getIdent))
    .function("isBoolean", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isBoolean))
    .function("getBooleanConst", static_cast<org::sem::LispCode::Boolean const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getBoolean))
    .function("getBooleanMut", static_cast<org::sem::LispCode::Boolean&(org::sem::LispCode::*)()>(&org::sem::LispCode::getBoolean))
    .function("isReal", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isReal))
    .function("getRealConst", static_cast<org::sem::LispCode::Real const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getReal))
    .function("getRealMut", static_cast<org::sem::LispCode::Real&(org::sem::LispCode::*)()>(&org::sem::LispCode::getReal))
    .class_function("getKindStatic", static_cast<org::sem::LispCode::Kind(*)(org::sem::LispCode::Data const&)>(&org::sem::LispCode::getKind))
    .function("getKind", static_cast<org::sem::LispCode::Kind(org::sem::LispCode::*)() const>(&org::sem::LispCode::getKind))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LispCode::Call>("LispCodeCall")
    .property("name", &org::sem::LispCode::Call::name)
    .property("args", &org::sem::LispCode::Call::args)
    .function("__eq__", static_cast<bool(org::sem::LispCode::Call::*)(org::sem::LispCode::Call const&) const>(&org::sem::LispCode::Call::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LispCode::List>("LispCodeList")
    .property("items", &org::sem::LispCode::List::items)
    .function("__eq__", static_cast<bool(org::sem::LispCode::List::*)(org::sem::LispCode::List const&) const>(&org::sem::LispCode::List::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LispCode::KeyValue>("LispCodeKeyValue")
    .property("name", &org::sem::LispCode::KeyValue::name)
    .property("value", &org::sem::LispCode::KeyValue::value)
    .function("__eq__", static_cast<bool(org::sem::LispCode::KeyValue::*)(org::sem::LispCode::KeyValue const&) const>(&org::sem::LispCode::KeyValue::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LispCode::Number>("LispCodeNumber")
    .property("value", &org::sem::LispCode::Number::value)
    .function("__eq__", static_cast<bool(org::sem::LispCode::Number::*)(org::sem::LispCode::Number const&) const>(&org::sem::LispCode::Number::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LispCode::Text>("LispCodeText")
    .property("value", &org::sem::LispCode::Text::value)
    .function("__eq__", static_cast<bool(org::sem::LispCode::Text::*)(org::sem::LispCode::Text const&) const>(&org::sem::LispCode::Text::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LispCode::Ident>("LispCodeIdent")
    .property("name", &org::sem::LispCode::Ident::name)
    .function("__eq__", static_cast<bool(org::sem::LispCode::Ident::*)(org::sem::LispCode::Ident const&) const>(&org::sem::LispCode::Ident::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LispCode::Boolean>("LispCodeBoolean")
    .property("value", &org::sem::LispCode::Boolean::value)
    .function("__eq__", static_cast<bool(org::sem::LispCode::Boolean::*)(org::sem::LispCode::Boolean const&) const>(&org::sem::LispCode::Boolean::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LispCode::Real>("LispCodeReal")
    .property("value", &org::sem::LispCode::Real::value)
    .function("__eq__", static_cast<bool(org::sem::LispCode::Real::*)(org::sem::LispCode::Real const&) const>(&org::sem::LispCode::Real::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::LispCode::Kind>("OrgSemLispCodeKind");
  emscripten::class_<org::sem::Tblfm>("Tblfm")
    .property("exprs", &org::sem::Tblfm::exprs)
    .function("__eq__", static_cast<bool(org::sem::Tblfm::*)(org::sem::Tblfm const&) const>(&org::sem::Tblfm::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::Tblfm::Expr>("TblfmExpr")
    .property("data", &org::sem::Tblfm::Expr::data)
    .function("__eq__", static_cast<bool(org::sem::Tblfm::Expr::*)(org::sem::Tblfm::Expr const&) const>(&org::sem::Tblfm::Expr::operator==))
    .function("isAxisRef", static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isAxisRef))
    .function("getAxisRefConst", static_cast<org::sem::Tblfm::Expr::AxisRef const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getAxisRef))
    .function("getAxisRefMut", static_cast<org::sem::Tblfm::Expr::AxisRef&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getAxisRef))
    .function("isAxisName", static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isAxisName))
    .function("getAxisNameConst", static_cast<org::sem::Tblfm::Expr::AxisName const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getAxisName))
    .function("getAxisNameMut", static_cast<org::sem::Tblfm::Expr::AxisName&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getAxisName))
    .function("isIntLiteral", static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isIntLiteral))
    .function("getIntLiteralConst", static_cast<org::sem::Tblfm::Expr::IntLiteral const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getIntLiteral))
    .function("getIntLiteralMut", static_cast<org::sem::Tblfm::Expr::IntLiteral&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getIntLiteral))
    .function("isFloatLiteral", static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isFloatLiteral))
    .function("getFloatLiteralConst", static_cast<org::sem::Tblfm::Expr::FloatLiteral const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getFloatLiteral))
    .function("getFloatLiteralMut", static_cast<org::sem::Tblfm::Expr::FloatLiteral&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getFloatLiteral))
    .function("isRangeRef", static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isRangeRef))
    .function("getRangeRefConst", static_cast<org::sem::Tblfm::Expr::RangeRef const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getRangeRef))
    .function("getRangeRefMut", static_cast<org::sem::Tblfm::Expr::RangeRef&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getRangeRef))
    .function("isCall", static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isCall))
    .function("getCallConst", static_cast<org::sem::Tblfm::Expr::Call const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getCall))
    .function("getCallMut", static_cast<org::sem::Tblfm::Expr::Call&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getCall))
    .function("isElisp", static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isElisp))
    .function("getElispConst", static_cast<org::sem::Tblfm::Expr::Elisp const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getElisp))
    .function("getElispMut", static_cast<org::sem::Tblfm::Expr::Elisp&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getElisp))
    .class_function("getKindStatic", static_cast<org::sem::Tblfm::Expr::Kind(*)(org::sem::Tblfm::Expr::Data const&)>(&org::sem::Tblfm::Expr::getKind))
    .function("getKind", static_cast<org::sem::Tblfm::Expr::Kind(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getKind))
    .constructor<>()
    ;
  emscripten::class_<org::sem::Tblfm::Expr::AxisRef>("TblfmExprAxisRef")
    .property("col", &org::sem::Tblfm::Expr::AxisRef::col)
    .property("row", &org::sem::Tblfm::Expr::AxisRef::row)
    .function("__eq__", static_cast<bool(org::sem::Tblfm::Expr::AxisRef::*)(org::sem::Tblfm::Expr::AxisRef const&) const>(&org::sem::Tblfm::Expr::AxisRef::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::Tblfm::Expr::AxisRef::Position>("TblfmExprAxisRefPosition")
    .property("data", &org::sem::Tblfm::Expr::AxisRef::Position::data)
    .function("__eq__", static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::*)(org::sem::Tblfm::Expr::AxisRef::Position const&) const>(&org::sem::Tblfm::Expr::AxisRef::Position::operator==))
    .function("isIndex", static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::isIndex))
    .function("getIndexConst", static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Index const&(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::getIndex))
    .function("getIndexMut", static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Index&(org::sem::Tblfm::Expr::AxisRef::Position::*)()>(&org::sem::Tblfm::Expr::AxisRef::Position::getIndex))
    .function("isName", static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::isName))
    .function("getNameConst", static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Name const&(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::getName))
    .function("getNameMut", static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Name&(org::sem::Tblfm::Expr::AxisRef::Position::*)()>(&org::sem::Tblfm::Expr::AxisRef::Position::getName))
    .class_function("getKindStatic", static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Kind(*)(org::sem::Tblfm::Expr::AxisRef::Position::Data const&)>(&org::sem::Tblfm::Expr::AxisRef::Position::getKind))
    .function("getKind", static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Kind(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::getKind))
    .constructor<>()
    ;
  emscripten::class_<org::sem::Tblfm::Expr::AxisRef::Position::Index>("TblfmExprAxisRefPositionIndex")
    .property("index", &org::sem::Tblfm::Expr::AxisRef::Position::Index::index)
    .function("__eq__", static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::Index::*)(org::sem::Tblfm::Expr::AxisRef::Position::Index const&) const>(&org::sem::Tblfm::Expr::AxisRef::Position::Index::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::Tblfm::Expr::AxisRef::Position::Name>("TblfmExprAxisRefPositionName")
    .property("name", &org::sem::Tblfm::Expr::AxisRef::Position::Name::name)
    .function("__eq__", static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::Name::*)(org::sem::Tblfm::Expr::AxisRef::Position::Name const&) const>(&org::sem::Tblfm::Expr::AxisRef::Position::Name::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::Tblfm::Expr::AxisRef::Position::Kind>("OrgSemTblfmExprAxisRefPositionKind");
  emscripten::class_<org::sem::Tblfm::Expr::AxisName>("TblfmExprAxisName")
    .property("name", &org::sem::Tblfm::Expr::AxisName::name)
    .function("__eq__", static_cast<bool(org::sem::Tblfm::Expr::AxisName::*)(org::sem::Tblfm::Expr::AxisName const&) const>(&org::sem::Tblfm::Expr::AxisName::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::Tblfm::Expr::IntLiteral>("TblfmExprIntLiteral")
    .property("value", &org::sem::Tblfm::Expr::IntLiteral::value)
    .function("__eq__", static_cast<bool(org::sem::Tblfm::Expr::IntLiteral::*)(org::sem::Tblfm::Expr::IntLiteral const&) const>(&org::sem::Tblfm::Expr::IntLiteral::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::Tblfm::Expr::FloatLiteral>("TblfmExprFloatLiteral")
    .property("value", &org::sem::Tblfm::Expr::FloatLiteral::value)
    .function("__eq__", static_cast<bool(org::sem::Tblfm::Expr::FloatLiteral::*)(org::sem::Tblfm::Expr::FloatLiteral const&) const>(&org::sem::Tblfm::Expr::FloatLiteral::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::Tblfm::Expr::RangeRef>("TblfmExprRangeRef")
    .property("first", &org::sem::Tblfm::Expr::RangeRef::first)
    .property("last", &org::sem::Tblfm::Expr::RangeRef::last)
    .function("__eq__", static_cast<bool(org::sem::Tblfm::Expr::RangeRef::*)(org::sem::Tblfm::Expr::RangeRef const&) const>(&org::sem::Tblfm::Expr::RangeRef::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::Tblfm::Expr::Call>("TblfmExprCall")
    .property("name", &org::sem::Tblfm::Expr::Call::name)
    .property("args", &org::sem::Tblfm::Expr::Call::args)
    .function("__eq__", static_cast<bool(org::sem::Tblfm::Expr::Call::*)(org::sem::Tblfm::Expr::Call const&) const>(&org::sem::Tblfm::Expr::Call::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::Tblfm::Expr::Elisp>("TblfmExprElisp")
    .property("value", &org::sem::Tblfm::Expr::Elisp::value)
    .function("__eq__", static_cast<bool(org::sem::Tblfm::Expr::Elisp::*)(org::sem::Tblfm::Expr::Elisp const&) const>(&org::sem::Tblfm::Expr::Elisp::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::Tblfm::Expr::Kind>("OrgSemTblfmExprKind");
  emscripten::class_<org::sem::Tblfm::Assign>("TblfmAssign")
    .property("target", &org::sem::Tblfm::Assign::target)
    .property("expr", &org::sem::Tblfm::Assign::expr)
    .property("flags", &org::sem::Tblfm::Assign::flags)
    .function("__eq__", static_cast<bool(org::sem::Tblfm::Assign::*)(org::sem::Tblfm::Assign const&) const>(&org::sem::Tblfm::Assign::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::Tblfm::Assign::Flag>("OrgSemTblfmAssignFlag");
  emscripten::class_<org::sem::AttrValue>("AttrValue")
    .property("name", &org::sem::AttrValue::name)
    .property("varname", &org::sem::AttrValue::varname)
    .property("span", &org::sem::AttrValue::span)
    .property("isQuoted", &org::sem::AttrValue::isQuoted)
    .property("data", &org::sem::AttrValue::data)
    .function("getBool", static_cast<hstd::Opt<bool>(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getBool))
    .function("getInt", static_cast<hstd::Opt<int>(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getInt))
    .function("getString", static_cast<hstd::Str(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getString))
    .function("getFile", static_cast<hstd::Str(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getFile))
    .function("getReference", static_cast<hstd::Str(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getReference))
    .function("getDouble", static_cast<hstd::Opt<double>(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getDouble))
    .function("__eq__", static_cast<bool(org::sem::AttrValue::*)(org::sem::AttrValue const&) const>(&org::sem::AttrValue::operator==))
    .function("isTextValue", static_cast<bool(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::isTextValue))
    .function("getTextValueConst", static_cast<org::sem::AttrValue::TextValue const&(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getTextValue))
    .function("getTextValueMut", static_cast<org::sem::AttrValue::TextValue&(org::sem::AttrValue::*)()>(&org::sem::AttrValue::getTextValue))
    .function("isFileReference", static_cast<bool(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::isFileReference))
    .function("getFileReferenceConst", static_cast<org::sem::AttrValue::FileReference const&(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getFileReference))
    .function("getFileReferenceMut", static_cast<org::sem::AttrValue::FileReference&(org::sem::AttrValue::*)()>(&org::sem::AttrValue::getFileReference))
    .function("isLispValue", static_cast<bool(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::isLispValue))
    .function("getLispValueConst", static_cast<org::sem::AttrValue::LispValue const&(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getLispValue))
    .function("getLispValueMut", static_cast<org::sem::AttrValue::LispValue&(org::sem::AttrValue::*)()>(&org::sem::AttrValue::getLispValue))
    .class_function("getDataKindStatic", static_cast<org::sem::AttrValue::DataKind(*)(org::sem::AttrValue::DataVariant const&)>(&org::sem::AttrValue::getDataKind))
    .function("getDataKind", static_cast<org::sem::AttrValue::DataKind(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getDataKind))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::AttrValue::Kind>("OrgSemAttrValueKind");
  emscripten::class_<org::sem::AttrValue::DimensionSpan>("AttrValueDimensionSpan")
    .property("first", &org::sem::AttrValue::DimensionSpan::first)
    .property("last", &org::sem::AttrValue::DimensionSpan::last)
    .function("__eq__", static_cast<bool(org::sem::AttrValue::DimensionSpan::*)(org::sem::AttrValue::DimensionSpan const&) const>(&org::sem::AttrValue::DimensionSpan::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::AttrValue::TextValue>("AttrValueTextValue")
    .property("value", &org::sem::AttrValue::TextValue::value)
    .function("__eq__", static_cast<bool(org::sem::AttrValue::TextValue::*)(org::sem::AttrValue::TextValue const&) const>(&org::sem::AttrValue::TextValue::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::AttrValue::FileReference>("AttrValueFileReference")
    .property("file", &org::sem::AttrValue::FileReference::file)
    .property("reference", &org::sem::AttrValue::FileReference::reference)
    .function("__eq__", static_cast<bool(org::sem::AttrValue::FileReference::*)(org::sem::AttrValue::FileReference const&) const>(&org::sem::AttrValue::FileReference::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::AttrValue::LispValue>("AttrValueLispValue")
    .property("code", &org::sem::AttrValue::LispValue::code)
    .function("__eq__", static_cast<bool(org::sem::AttrValue::LispValue::*)(org::sem::AttrValue::LispValue const&) const>(&org::sem::AttrValue::LispValue::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::AttrValue::DataKind>("OrgSemAttrValueDataKind");
  emscripten::class_<org::sem::HashTagFlat>("HashTagFlat")
    .property("tags", &org::sem::HashTagFlat::tags)
    .function("__eq__", static_cast<bool(org::sem::HashTagFlat::*)(org::sem::HashTagFlat const&) const>(&org::sem::HashTagFlat::operator==))
    .function("__lt__", static_cast<bool(org::sem::HashTagFlat::*)(org::sem::HashTagFlat const&) const>(&org::sem::HashTagFlat::operator<))
    .constructor<>()
    ;
  emscripten::class_<org::sem::TodoKeyword>("TodoKeyword")
    .property("name", &org::sem::TodoKeyword::name)
    .property("shortcut", &org::sem::TodoKeyword::shortcut)
    .property("onEnter", &org::sem::TodoKeyword::onEnter)
    .property("onLeave", &org::sem::TodoKeyword::onLeave)
    .function("__eq__", static_cast<bool(org::sem::TodoKeyword::*)(org::sem::TodoKeyword const&) const>(&org::sem::TodoKeyword::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::TodoKeyword::Transition>("OrgSemTodoKeywordTransition");
  emscripten::class_<org::sem::HashTagText>("HashTagText")
    .property("head", &org::sem::HashTagText::head)
    .property("subtags", &org::sem::HashTagText::subtags)
    .function("__eq__", static_cast<bool(org::sem::HashTagText::*)(org::sem::HashTagText const&) const>(&org::sem::HashTagText::operator==))
    .function("prefixMatch", static_cast<bool(org::sem::HashTagText::*)(hstd::Vec<hstd::Str> const&) const>(&org::sem::HashTagText::prefixMatch))
    .function("getFlatHashes", static_cast<hstd::Vec<org::sem::HashTagFlat>(org::sem::HashTagText::*)(bool) const>(&org::sem::HashTagText::getFlatHashes))
    .constructor<>()
    ;
  emscripten::class_<org::sem::SubtreePath>("SubtreePath")
    .property("path", &org::sem::SubtreePath::path)
    .function("__eq__", static_cast<bool(org::sem::SubtreePath::*)(org::sem::SubtreePath const&) const>(&org::sem::SubtreePath::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LinkTarget>("LinkTarget")
    .property("data", &org::sem::LinkTarget::data)
    .function("__eq__", static_cast<bool(org::sem::LinkTarget::*)(org::sem::LinkTarget const&) const>(&org::sem::LinkTarget::operator==))
    .function("isRaw", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isRaw))
    .function("getRawConst", static_cast<org::sem::LinkTarget::Raw const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getRaw))
    .function("getRawMut", static_cast<org::sem::LinkTarget::Raw&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getRaw))
    .function("isId", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isId))
    .function("getIdConst", static_cast<org::sem::LinkTarget::Id const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getId))
    .function("getIdMut", static_cast<org::sem::LinkTarget::Id&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getId))
    .function("isCustomId", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isCustomId))
    .function("getCustomIdConst", static_cast<org::sem::LinkTarget::CustomId const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getCustomId))
    .function("getCustomIdMut", static_cast<org::sem::LinkTarget::CustomId&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getCustomId))
    .function("isSubtreeTitle", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isSubtreeTitle))
    .function("getSubtreeTitleConst", static_cast<org::sem::LinkTarget::SubtreeTitle const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getSubtreeTitle))
    .function("getSubtreeTitleMut", static_cast<org::sem::LinkTarget::SubtreeTitle&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getSubtreeTitle))
    .function("isPerson", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isPerson))
    .function("getPersonConst", static_cast<org::sem::LinkTarget::Person const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getPerson))
    .function("getPersonMut", static_cast<org::sem::LinkTarget::Person&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getPerson))
    .function("isUserProtocol", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isUserProtocol))
    .function("getUserProtocolConst", static_cast<org::sem::LinkTarget::UserProtocol const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getUserProtocol))
    .function("getUserProtocolMut", static_cast<org::sem::LinkTarget::UserProtocol&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getUserProtocol))
    .function("isInternal", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isInternal))
    .function("getInternalConst", static_cast<org::sem::LinkTarget::Internal const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getInternal))
    .function("getInternalMut", static_cast<org::sem::LinkTarget::Internal&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getInternal))
    .function("isFootnote", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isFootnote))
    .function("getFootnoteConst", static_cast<org::sem::LinkTarget::Footnote const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getFootnote))
    .function("getFootnoteMut", static_cast<org::sem::LinkTarget::Footnote&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getFootnote))
    .function("isFile", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isFile))
    .function("getFileConst", static_cast<org::sem::LinkTarget::File const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getFile))
    .function("getFileMut", static_cast<org::sem::LinkTarget::File&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getFile))
    .function("isAttachment", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isAttachment))
    .function("getAttachmentConst", static_cast<org::sem::LinkTarget::Attachment const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getAttachment))
    .function("getAttachmentMut", static_cast<org::sem::LinkTarget::Attachment&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getAttachment))
    .class_function("getKindStatic", static_cast<org::sem::LinkTarget::Kind(*)(org::sem::LinkTarget::Data const&)>(&org::sem::LinkTarget::getKind))
    .function("getKind", static_cast<org::sem::LinkTarget::Kind(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getKind))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LinkTarget::Raw>("LinkTargetRaw")
    .property("text", &org::sem::LinkTarget::Raw::text)
    .function("__eq__", static_cast<bool(org::sem::LinkTarget::Raw::*)(org::sem::LinkTarget::Raw const&) const>(&org::sem::LinkTarget::Raw::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LinkTarget::Id>("LinkTargetId")
    .property("text", &org::sem::LinkTarget::Id::text)
    .function("__eq__", static_cast<bool(org::sem::LinkTarget::Id::*)(org::sem::LinkTarget::Id const&) const>(&org::sem::LinkTarget::Id::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LinkTarget::CustomId>("LinkTargetCustomId")
    .property("text", &org::sem::LinkTarget::CustomId::text)
    .function("__eq__", static_cast<bool(org::sem::LinkTarget::CustomId::*)(org::sem::LinkTarget::CustomId const&) const>(&org::sem::LinkTarget::CustomId::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LinkTarget::SubtreeTitle>("LinkTargetSubtreeTitle")
    .property("title", &org::sem::LinkTarget::SubtreeTitle::title)
    .property("level", &org::sem::LinkTarget::SubtreeTitle::level)
    .function("__eq__", static_cast<bool(org::sem::LinkTarget::SubtreeTitle::*)(org::sem::LinkTarget::SubtreeTitle const&) const>(&org::sem::LinkTarget::SubtreeTitle::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LinkTarget::Person>("LinkTargetPerson")
    .property("name", &org::sem::LinkTarget::Person::name)
    .function("__eq__", static_cast<bool(org::sem::LinkTarget::Person::*)(org::sem::LinkTarget::Person const&) const>(&org::sem::LinkTarget::Person::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LinkTarget::UserProtocol>("LinkTargetUserProtocol")
    .property("protocol", &org::sem::LinkTarget::UserProtocol::protocol)
    .property("target", &org::sem::LinkTarget::UserProtocol::target)
    .function("__eq__", static_cast<bool(org::sem::LinkTarget::UserProtocol::*)(org::sem::LinkTarget::UserProtocol const&) const>(&org::sem::LinkTarget::UserProtocol::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LinkTarget::Internal>("LinkTargetInternal")
    .property("target", &org::sem::LinkTarget::Internal::target)
    .function("__eq__", static_cast<bool(org::sem::LinkTarget::Internal::*)(org::sem::LinkTarget::Internal const&) const>(&org::sem::LinkTarget::Internal::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LinkTarget::Footnote>("LinkTargetFootnote")
    .property("target", &org::sem::LinkTarget::Footnote::target)
    .function("__eq__", static_cast<bool(org::sem::LinkTarget::Footnote::*)(org::sem::LinkTarget::Footnote const&) const>(&org::sem::LinkTarget::Footnote::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LinkTarget::File>("LinkTargetFile")
    .property("file", &org::sem::LinkTarget::File::file)
    .function("__eq__", static_cast<bool(org::sem::LinkTarget::File::*)(org::sem::LinkTarget::File const&) const>(&org::sem::LinkTarget::File::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LinkTarget::Attachment>("LinkTargetAttachment")
    .property("file", &org::sem::LinkTarget::Attachment::file)
    .function("__eq__", static_cast<bool(org::sem::LinkTarget::Attachment::*)(org::sem::LinkTarget::Attachment const&) const>(&org::sem::LinkTarget::Attachment::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::LinkTarget::Kind>("OrgSemLinkTargetKind");
  emscripten::class_<org::sem::SubtreeLogHead>("SubtreeLogHead")
    .property("log", &org::sem::SubtreeLogHead::log)
    .function("__eq__", static_cast<bool(org::sem::SubtreeLogHead::*)(org::sem::SubtreeLogHead const&) const>(&org::sem::SubtreeLogHead::operator==))
    .function("isPriority", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isPriority))
    .function("getPriorityConst", static_cast<org::sem::SubtreeLogHead::Priority const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getPriority))
    .function("getPriorityMut", static_cast<org::sem::SubtreeLogHead::Priority&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getPriority))
    .function("isNote", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isNote))
    .function("getNoteConst", static_cast<org::sem::SubtreeLogHead::Note const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getNote))
    .function("getNoteMut", static_cast<org::sem::SubtreeLogHead::Note&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getNote))
    .function("isRefile", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isRefile))
    .function("getRefileConst", static_cast<org::sem::SubtreeLogHead::Refile const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getRefile))
    .function("getRefileMut", static_cast<org::sem::SubtreeLogHead::Refile&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getRefile))
    .function("isClock", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isClock))
    .function("getClockConst", static_cast<org::sem::SubtreeLogHead::Clock const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getClock))
    .function("getClockMut", static_cast<org::sem::SubtreeLogHead::Clock&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getClock))
    .function("isState", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isState))
    .function("getStateConst", static_cast<org::sem::SubtreeLogHead::State const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getState))
    .function("getStateMut", static_cast<org::sem::SubtreeLogHead::State&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getState))
    .function("isDeadline", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isDeadline))
    .function("getDeadlineConst", static_cast<org::sem::SubtreeLogHead::Deadline const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getDeadline))
    .function("getDeadlineMut", static_cast<org::sem::SubtreeLogHead::Deadline&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getDeadline))
    .function("isSchedule", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isSchedule))
    .function("getScheduleConst", static_cast<org::sem::SubtreeLogHead::Schedule const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getSchedule))
    .function("getScheduleMut", static_cast<org::sem::SubtreeLogHead::Schedule&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getSchedule))
    .function("isTag", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isTag))
    .function("getTagConst", static_cast<org::sem::SubtreeLogHead::Tag const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getTag))
    .function("getTagMut", static_cast<org::sem::SubtreeLogHead::Tag&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getTag))
    .function("isUnknown", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isUnknown))
    .function("getUnknownConst", static_cast<org::sem::SubtreeLogHead::Unknown const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getUnknown))
    .function("getUnknownMut", static_cast<org::sem::SubtreeLogHead::Unknown&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getUnknown))
    .class_function("getLogKindStatic", static_cast<org::sem::SubtreeLogHead::Kind(*)(org::sem::SubtreeLogHead::LogEntry const&)>(&org::sem::SubtreeLogHead::getLogKind))
    .function("getLogKind", static_cast<org::sem::SubtreeLogHead::Kind(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getLogKind))
    .constructor<>()
    ;
  emscripten::class_<org::sem::SubtreeLogHead::Priority>("SubtreeLogHeadPriority")
    .property("oldPriority", &org::sem::SubtreeLogHead::Priority::oldPriority)
    .property("newPriority", &org::sem::SubtreeLogHead::Priority::newPriority)
    .property("on", &org::sem::SubtreeLogHead::Priority::on)
    .property("action", &org::sem::SubtreeLogHead::Priority::action)
    .function("__eq__", static_cast<bool(org::sem::SubtreeLogHead::Priority::*)(org::sem::SubtreeLogHead::Priority const&) const>(&org::sem::SubtreeLogHead::Priority::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::SubtreeLogHead::Priority::Action>("OrgSemSubtreeLogHeadPriorityAction");
  emscripten::class_<org::sem::SubtreeLogHead::Note>("SubtreeLogHeadNote")
    .property("on", &org::sem::SubtreeLogHead::Note::on)
    .function("__eq__", static_cast<bool(org::sem::SubtreeLogHead::Note::*)(org::sem::SubtreeLogHead::Note const&) const>(&org::sem::SubtreeLogHead::Note::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::SubtreeLogHead::Refile>("SubtreeLogHeadRefile")
    .property("on", &org::sem::SubtreeLogHead::Refile::on)
    .property("from", &org::sem::SubtreeLogHead::Refile::from)
    .function("__eq__", static_cast<bool(org::sem::SubtreeLogHead::Refile::*)(org::sem::SubtreeLogHead::Refile const&) const>(&org::sem::SubtreeLogHead::Refile::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::SubtreeLogHead::Clock>("SubtreeLogHeadClock")
    .property("from", &org::sem::SubtreeLogHead::Clock::from)
    .property("to", &org::sem::SubtreeLogHead::Clock::to)
    .function("__eq__", static_cast<bool(org::sem::SubtreeLogHead::Clock::*)(org::sem::SubtreeLogHead::Clock const&) const>(&org::sem::SubtreeLogHead::Clock::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::SubtreeLogHead::State>("SubtreeLogHeadState")
    .property("from", &org::sem::SubtreeLogHead::State::from)
    .property("to", &org::sem::SubtreeLogHead::State::to)
    .property("on", &org::sem::SubtreeLogHead::State::on)
    .function("__eq__", static_cast<bool(org::sem::SubtreeLogHead::State::*)(org::sem::SubtreeLogHead::State const&) const>(&org::sem::SubtreeLogHead::State::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::SubtreeLogHead::Deadline>("SubtreeLogHeadDeadline")
    .property("from", &org::sem::SubtreeLogHead::Deadline::from)
    .property("to", &org::sem::SubtreeLogHead::Deadline::to)
    .property("on", &org::sem::SubtreeLogHead::Deadline::on)
    .function("__eq__", static_cast<bool(org::sem::SubtreeLogHead::Deadline::*)(org::sem::SubtreeLogHead::Deadline const&) const>(&org::sem::SubtreeLogHead::Deadline::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::SubtreeLogHead::Schedule>("SubtreeLogHeadSchedule")
    .property("from", &org::sem::SubtreeLogHead::Schedule::from)
    .property("to", &org::sem::SubtreeLogHead::Schedule::to)
    .property("on", &org::sem::SubtreeLogHead::Schedule::on)
    .function("__eq__", static_cast<bool(org::sem::SubtreeLogHead::Schedule::*)(org::sem::SubtreeLogHead::Schedule const&) const>(&org::sem::SubtreeLogHead::Schedule::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::SubtreeLogHead::Tag>("SubtreeLogHeadTag")
    .property("on", &org::sem::SubtreeLogHead::Tag::on)
    .property("tag", &org::sem::SubtreeLogHead::Tag::tag)
    .property("added", &org::sem::SubtreeLogHead::Tag::added)
    .function("__eq__", static_cast<bool(org::sem::SubtreeLogHead::Tag::*)(org::sem::SubtreeLogHead::Tag const&) const>(&org::sem::SubtreeLogHead::Tag::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::SubtreeLogHead::Unknown>("SubtreeLogHeadUnknown")
    .function("__eq__", static_cast<bool(org::sem::SubtreeLogHead::Unknown::*)(org::sem::SubtreeLogHead::Unknown const&) const>(&org::sem::SubtreeLogHead::Unknown::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::SubtreeLogHead::Kind>("OrgSemSubtreeLogHeadKind");
  emscripten::class_<org::sem::SubtreeCompletion>("SubtreeCompletion")
    .property("done", &org::sem::SubtreeCompletion::done)
    .property("full", &org::sem::SubtreeCompletion::full)
    .property("isPercent", &org::sem::SubtreeCompletion::isPercent)
    .function("__eq__", static_cast<bool(org::sem::SubtreeCompletion::*)(org::sem::SubtreeCompletion const&) const>(&org::sem::SubtreeCompletion::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::AttrList>("AttrList")
    .property("items", &org::sem::AttrList::items)
    .function("__eq__", static_cast<bool(org::sem::AttrList::*)(org::sem::AttrList const&) const>(&org::sem::AttrList::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::AttrGroup>("AttrGroup")
    .property("positional", &org::sem::AttrGroup::positional)
    .property("named", &org::sem::AttrGroup::named)
    .function("getFlatArgs", static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getFlatArgs))
    .function("getAttrs", static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::AttrGroup::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::AttrGroup::getAttrs))
    .function("setNamedAttr", static_cast<void(org::sem::AttrGroup::*)(hstd::Str const&, hstd::Vec<org::sem::AttrValue> const&)>(&org::sem::AttrGroup::setNamedAttr))
    .function("setPositionalAttr", static_cast<void(org::sem::AttrGroup::*)(hstd::Vec<org::sem::AttrValue> const&)>(&org::sem::AttrGroup::setPositionalAttr))
    .function("getPositionalSize", static_cast<int(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getPositionalSize))
    .function("getNamedSize", static_cast<int(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getNamedSize))
    .function("isEmpty", static_cast<bool(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::isEmpty))
    .function("getAll", static_cast<org::sem::AttrList(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getAll))
    .function("atPositional", static_cast<org::sem::AttrValue const&(org::sem::AttrGroup::*)(int) const>(&org::sem::AttrGroup::atPositional))
    .function("getPositional", static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::AttrGroup::*)(int) const>(&org::sem::AttrGroup::getPositional))
    .function("atNamed", static_cast<org::sem::AttrList const&(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atNamed))
    .function("getNamed", static_cast<hstd::Opt<org::sem::AttrList>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getNamed))
    .function("atFirstNamed", static_cast<org::sem::AttrValue const&(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atFirstNamed))
    .function("getFirstNamed", static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getFirstNamed))
    .function("atVarNamed", static_cast<org::sem::AttrList(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atVarNamed))
    .function("getVarNamed", static_cast<hstd::Opt<org::sem::AttrList>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getVarNamed))
    .function("atFirstVarNamed", static_cast<org::sem::AttrValue(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atFirstVarNamed))
    .function("getFirstVarNamed", static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getFirstVarNamed))
    .function("__eq__", static_cast<bool(org::sem::AttrGroup::*)(org::sem::AttrGroup const&) const>(&org::sem::AttrGroup::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::OrgCodeEvalInput>("OrgCodeEvalInput")
    .property("blockAttrs", &org::sem::OrgCodeEvalInput::blockAttrs)
    .property("tangledCode", &org::sem::OrgCodeEvalInput::tangledCode)
    .property("exportType", &org::sem::OrgCodeEvalInput::exportType)
    .property("resultType", &org::sem::OrgCodeEvalInput::resultType)
    .property("resultFormat", &org::sem::OrgCodeEvalInput::resultFormat)
    .property("resultHandling", &org::sem::OrgCodeEvalInput::resultHandling)
    .property("language", &org::sem::OrgCodeEvalInput::language)
    .property("argList", &org::sem::OrgCodeEvalInput::argList)
    .function("__eq__", static_cast<bool(org::sem::OrgCodeEvalInput::*)(org::sem::OrgCodeEvalInput const&) const>(&org::sem::OrgCodeEvalInput::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::OrgCodeEvalInput::Var>("OrgCodeEvalInputVar")
    .property("name", &org::sem::OrgCodeEvalInput::Var::name)
    .property("value", &org::sem::OrgCodeEvalInput::Var::value)
    .function("__eq__", static_cast<bool(org::sem::OrgCodeEvalInput::Var::*)(org::sem::OrgCodeEvalInput::Var const&) const>(&org::sem::OrgCodeEvalInput::Var::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::OrgCodeEvalInput::ResultType>("OrgSemOrgCodeEvalInputResultType");
  org::bind::js::bind_enum<org::sem::OrgCodeEvalInput::ResultFormat>("OrgSemOrgCodeEvalInputResultFormat");
  org::bind::js::bind_enum<org::sem::OrgCodeEvalInput::ResultHandling>("OrgSemOrgCodeEvalInputResultHandling");
  emscripten::class_<org::sem::OrgCodeEvalOutput>("OrgCodeEvalOutput")
    .property("stdoutText", &org::sem::OrgCodeEvalOutput::stdoutText)
    .property("stderrText", &org::sem::OrgCodeEvalOutput::stderrText)
    .property("code", &org::sem::OrgCodeEvalOutput::code)
    .property("cmd", &org::sem::OrgCodeEvalOutput::cmd)
    .property("args", &org::sem::OrgCodeEvalOutput::args)
    .property("cwd", &org::sem::OrgCodeEvalOutput::cwd)
    .property("appliedHeaderArg", &org::sem::OrgCodeEvalOutput::appliedHeaderArg)
    .function("__eq__", static_cast<bool(org::sem::OrgCodeEvalOutput::*)(org::sem::OrgCodeEvalOutput const&) const>(&org::sem::OrgCodeEvalOutput::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::ColumnView>("ColumnView")
    .property("columns", &org::sem::ColumnView::columns)
    .function("__eq__", static_cast<bool(org::sem::ColumnView::*)(org::sem::ColumnView const&) const>(&org::sem::ColumnView::operator==))
    .constructor<>()
    ;
}

void subdivide_3(org::bind::js::type_registration_guard& g) {
  emscripten::class_<org::sem::ColumnView::Summary>("ColumnViewSummary")
    .property("data", &org::sem::ColumnView::Summary::data)
    .function("__eq__", static_cast<bool(org::sem::ColumnView::Summary::*)(org::sem::ColumnView::Summary const&) const>(&org::sem::ColumnView::Summary::operator==))
    .function("isCheckboxAggregate", static_cast<bool(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::isCheckboxAggregate))
    .function("getCheckboxAggregateConst", static_cast<org::sem::ColumnView::Summary::CheckboxAggregate const&(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::getCheckboxAggregate))
    .function("getCheckboxAggregateMut", static_cast<org::sem::ColumnView::Summary::CheckboxAggregate&(org::sem::ColumnView::Summary::*)()>(&org::sem::ColumnView::Summary::getCheckboxAggregate))
    .function("isMathAggregate", static_cast<bool(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::isMathAggregate))
    .function("getMathAggregateConst", static_cast<org::sem::ColumnView::Summary::MathAggregate const&(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::getMathAggregate))
    .function("getMathAggregateMut", static_cast<org::sem::ColumnView::Summary::MathAggregate&(org::sem::ColumnView::Summary::*)()>(&org::sem::ColumnView::Summary::getMathAggregate))
    .class_function("getKindStatic", static_cast<org::sem::ColumnView::Summary::Kind(*)(org::sem::ColumnView::Summary::Data const&)>(&org::sem::ColumnView::Summary::getKind))
    .function("getKind", static_cast<org::sem::ColumnView::Summary::Kind(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::getKind))
    .constructor<>()
    ;
  emscripten::class_<org::sem::ColumnView::Summary::CheckboxAggregate>("ColumnViewSummaryCheckboxAggregate")
    .property("kind", &org::sem::ColumnView::Summary::CheckboxAggregate::kind)
    .function("__eq__", static_cast<bool(org::sem::ColumnView::Summary::CheckboxAggregate::*)(org::sem::ColumnView::Summary::CheckboxAggregate const&) const>(&org::sem::ColumnView::Summary::CheckboxAggregate::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::ColumnView::Summary::CheckboxAggregate::Kind>("OrgSemColumnViewSummaryCheckboxAggregateKind");
  emscripten::class_<org::sem::ColumnView::Summary::MathAggregate>("ColumnViewSummaryMathAggregate")
    .property("kind", &org::sem::ColumnView::Summary::MathAggregate::kind)
    .property("formatDigits", &org::sem::ColumnView::Summary::MathAggregate::formatDigits)
    .property("formatPrecision", &org::sem::ColumnView::Summary::MathAggregate::formatPrecision)
    .function("__eq__", static_cast<bool(org::sem::ColumnView::Summary::MathAggregate::*)(org::sem::ColumnView::Summary::MathAggregate const&) const>(&org::sem::ColumnView::Summary::MathAggregate::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::ColumnView::Summary::MathAggregate::Kind>("OrgSemColumnViewSummaryMathAggregateKind");
  org::bind::js::bind_enum<org::sem::ColumnView::Summary::Kind>("OrgSemColumnViewSummaryKind");
  emscripten::class_<org::sem::ColumnView::Column>("ColumnViewColumn")
    .property("summary", &org::sem::ColumnView::Column::summary)
    .property("width", &org::sem::ColumnView::Column::width)
    .property("property", &org::sem::ColumnView::Column::property)
    .property("propertyTitle", &org::sem::ColumnView::Column::propertyTitle)
    .function("__eq__", static_cast<bool(org::sem::ColumnView::Column::*)(org::sem::ColumnView::Column const&) const>(&org::sem::ColumnView::Column::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::BlockCodeLine>("BlockCodeLine")
    .property("parts", &org::sem::BlockCodeLine::parts)
    .function("__eq__", static_cast<bool(org::sem::BlockCodeLine::*)(org::sem::BlockCodeLine const&) const>(&org::sem::BlockCodeLine::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::BlockCodeLine::Part>("BlockCodeLinePart")
    .property("data", &org::sem::BlockCodeLine::Part::data)
    .function("__eq__", static_cast<bool(org::sem::BlockCodeLine::Part::*)(org::sem::BlockCodeLine::Part const&) const>(&org::sem::BlockCodeLine::Part::operator==))
    .function("isRaw", static_cast<bool(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::isRaw))
    .function("getRawConst", static_cast<org::sem::BlockCodeLine::Part::Raw const&(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::getRaw))
    .function("getRawMut", static_cast<org::sem::BlockCodeLine::Part::Raw&(org::sem::BlockCodeLine::Part::*)()>(&org::sem::BlockCodeLine::Part::getRaw))
    .function("isCallout", static_cast<bool(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::isCallout))
    .function("getCalloutConst", static_cast<org::sem::BlockCodeLine::Part::Callout const&(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::getCallout))
    .function("getCalloutMut", static_cast<org::sem::BlockCodeLine::Part::Callout&(org::sem::BlockCodeLine::Part::*)()>(&org::sem::BlockCodeLine::Part::getCallout))
    .function("isTangle", static_cast<bool(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::isTangle))
    .function("getTangleConst", static_cast<org::sem::BlockCodeLine::Part::Tangle const&(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::getTangle))
    .function("getTangleMut", static_cast<org::sem::BlockCodeLine::Part::Tangle&(org::sem::BlockCodeLine::Part::*)()>(&org::sem::BlockCodeLine::Part::getTangle))
    .class_function("getKindStatic", static_cast<org::sem::BlockCodeLine::Part::Kind(*)(org::sem::BlockCodeLine::Part::Data const&)>(&org::sem::BlockCodeLine::Part::getKind))
    .function("getKind", static_cast<org::sem::BlockCodeLine::Part::Kind(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::getKind))
    .constructor<>()
    ;
  emscripten::class_<org::sem::BlockCodeLine::Part::Raw>("BlockCodeLinePartRaw")
    .property("code", &org::sem::BlockCodeLine::Part::Raw::code)
    .function("__eq__", static_cast<bool(org::sem::BlockCodeLine::Part::Raw::*)(org::sem::BlockCodeLine::Part::Raw const&) const>(&org::sem::BlockCodeLine::Part::Raw::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::BlockCodeLine::Part::Callout>("BlockCodeLinePartCallout")
    .property("name", &org::sem::BlockCodeLine::Part::Callout::name)
    .function("__eq__", static_cast<bool(org::sem::BlockCodeLine::Part::Callout::*)(org::sem::BlockCodeLine::Part::Callout const&) const>(&org::sem::BlockCodeLine::Part::Callout::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::BlockCodeLine::Part::Tangle>("BlockCodeLinePartTangle")
    .property("target", &org::sem::BlockCodeLine::Part::Tangle::target)
    .function("__eq__", static_cast<bool(org::sem::BlockCodeLine::Part::Tangle::*)(org::sem::BlockCodeLine::Part::Tangle const&) const>(&org::sem::BlockCodeLine::Part::Tangle::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::BlockCodeLine::Part::Kind>("OrgSemBlockCodeLinePartKind");
  emscripten::class_<org::sem::DocumentExportConfig>("DocumentExportConfig")
    .property("inlinetasks", &org::sem::DocumentExportConfig::inlinetasks)
    .property("footnotes", &org::sem::DocumentExportConfig::footnotes)
    .property("clock", &org::sem::DocumentExportConfig::clock)
    .property("author", &org::sem::DocumentExportConfig::author)
    .property("emphasis", &org::sem::DocumentExportConfig::emphasis)
    .property("specialStrings", &org::sem::DocumentExportConfig::specialStrings)
    .property("propertyDrawers", &org::sem::DocumentExportConfig::propertyDrawers)
    .property("statisticsCookies", &org::sem::DocumentExportConfig::statisticsCookies)
    .property("todoText", &org::sem::DocumentExportConfig::todoText)
    .property("brokenLinks", &org::sem::DocumentExportConfig::brokenLinks)
    .property("tocExport", &org::sem::DocumentExportConfig::tocExport)
    .property("tagExport", &org::sem::DocumentExportConfig::tagExport)
    .property("data", &org::sem::DocumentExportConfig::data)
    .function("__eq__", static_cast<bool(org::sem::DocumentExportConfig::*)(org::sem::DocumentExportConfig const&) const>(&org::sem::DocumentExportConfig::operator==))
    .function("isDoExport", static_cast<bool(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::isDoExport))
    .function("getDoExportConst", static_cast<org::sem::DocumentExportConfig::DoExport const&(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::getDoExport))
    .function("getDoExportMut", static_cast<org::sem::DocumentExportConfig::DoExport&(org::sem::DocumentExportConfig::*)()>(&org::sem::DocumentExportConfig::getDoExport))
    .function("isExportFixed", static_cast<bool(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::isExportFixed))
    .function("getExportFixedConst", static_cast<org::sem::DocumentExportConfig::ExportFixed const&(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::getExportFixed))
    .function("getExportFixedMut", static_cast<org::sem::DocumentExportConfig::ExportFixed&(org::sem::DocumentExportConfig::*)()>(&org::sem::DocumentExportConfig::getExportFixed))
    .class_function("getTocExportKindStatic", static_cast<org::sem::DocumentExportConfig::TocExportKind(*)(org::sem::DocumentExportConfig::TocExport const&)>(&org::sem::DocumentExportConfig::getTocExportKind))
    .function("getTocExportKind", static_cast<org::sem::DocumentExportConfig::TocExportKind(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::getTocExportKind))
    .constructor<>()
    ;
  emscripten::class_<org::sem::DocumentExportConfig::TaskExport>("DocumentExportConfigTaskExport")
    .property("taskWhitelist", &org::sem::DocumentExportConfig::TaskExport::taskWhitelist)
    .function("__eq__", static_cast<bool(org::sem::DocumentExportConfig::TaskExport::*)(org::sem::DocumentExportConfig::TaskExport const&) const>(&org::sem::DocumentExportConfig::TaskExport::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::DocumentExportConfig::TagExport>("OrgSemDocumentExportConfigTagExport");
  org::bind::js::bind_enum<org::sem::DocumentExportConfig::TaskFiltering>("OrgSemDocumentExportConfigTaskFiltering");
  org::bind::js::bind_enum<org::sem::DocumentExportConfig::BrokenLinks>("OrgSemDocumentExportConfigBrokenLinks");
  emscripten::class_<org::sem::DocumentExportConfig::DoExport>("DocumentExportConfigDoExport")
    .property("exportToc", &org::sem::DocumentExportConfig::DoExport::exportToc)
    .function("__eq__", static_cast<bool(org::sem::DocumentExportConfig::DoExport::*)(org::sem::DocumentExportConfig::DoExport const&) const>(&org::sem::DocumentExportConfig::DoExport::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::DocumentExportConfig::ExportFixed>("DocumentExportConfigExportFixed")
    .property("exportLevels", &org::sem::DocumentExportConfig::ExportFixed::exportLevels)
    .function("__eq__", static_cast<bool(org::sem::DocumentExportConfig::ExportFixed::*)(org::sem::DocumentExportConfig::ExportFixed const&) const>(&org::sem::DocumentExportConfig::ExportFixed::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::DocumentExportConfig::TocExportKind>("OrgSemDocumentExportConfigTocExportKind");
  emscripten::class_<org::sem::SubtreePeriod>("SubtreePeriod")
    .property("kind", &org::sem::SubtreePeriod::kind)
    .property("from", &org::sem::SubtreePeriod::from)
    .property("to", &org::sem::SubtreePeriod::to)
    .function("__eq__", static_cast<bool(org::sem::SubtreePeriod::*)(org::sem::SubtreePeriod const&) const>(&org::sem::SubtreePeriod::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::SubtreePeriod::Kind>("OrgSemSubtreePeriodKind");
  emscripten::class_<org::sem::NamedProperty>("NamedProperty")
    .property("data", &org::sem::NamedProperty::data)
    .function("isMatching", static_cast<bool(org::sem::NamedProperty::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::NamedProperty::isMatching))
    .function("getName", static_cast<hstd::Str(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getName))
    .function("getSubKind", static_cast<hstd::Opt<hstd::Str>(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getSubKind))
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::*)(org::sem::NamedProperty const&) const>(&org::sem::NamedProperty::operator==))
    .function("isNonblocking", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isNonblocking))
    .function("getNonblockingConst", static_cast<org::sem::NamedProperty::Nonblocking const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getNonblocking))
    .function("getNonblockingMut", static_cast<org::sem::NamedProperty::Nonblocking&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getNonblocking))
    .function("isArchiveTime", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveTime))
    .function("getArchiveTimeConst", static_cast<org::sem::NamedProperty::ArchiveTime const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveTime))
    .function("getArchiveTimeMut", static_cast<org::sem::NamedProperty::ArchiveTime&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveTime))
    .function("isArchiveFile", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveFile))
    .function("getArchiveFileConst", static_cast<org::sem::NamedProperty::ArchiveFile const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveFile))
    .function("getArchiveFileMut", static_cast<org::sem::NamedProperty::ArchiveFile&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveFile))
    .function("isArchiveOlpath", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveOlpath))
    .function("getArchiveOlpathConst", static_cast<org::sem::NamedProperty::ArchiveOlpath const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveOlpath))
    .function("getArchiveOlpathMut", static_cast<org::sem::NamedProperty::ArchiveOlpath&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveOlpath))
    .function("isArchiveTarget", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveTarget))
    .function("getArchiveTargetConst", static_cast<org::sem::NamedProperty::ArchiveTarget const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveTarget))
    .function("getArchiveTargetMut", static_cast<org::sem::NamedProperty::ArchiveTarget&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveTarget))
    .function("isArchiveCategory", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveCategory))
    .function("getArchiveCategoryConst", static_cast<org::sem::NamedProperty::ArchiveCategory const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveCategory))
    .function("getArchiveCategoryMut", static_cast<org::sem::NamedProperty::ArchiveCategory&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveCategory))
    .function("isArchiveTodo", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveTodo))
    .function("getArchiveTodoConst", static_cast<org::sem::NamedProperty::ArchiveTodo const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveTodo))
    .function("getArchiveTodoMut", static_cast<org::sem::NamedProperty::ArchiveTodo&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveTodo))
    .function("isTrigger", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isTrigger))
    .function("getTriggerConst", static_cast<org::sem::NamedProperty::Trigger const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getTrigger))
    .function("getTriggerMut", static_cast<org::sem::NamedProperty::Trigger&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getTrigger))
    .function("isExportLatexClass", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexClass))
    .function("getExportLatexClassConst", static_cast<org::sem::NamedProperty::ExportLatexClass const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getExportLatexClass))
    .function("getExportLatexClassMut", static_cast<org::sem::NamedProperty::ExportLatexClass&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexClass))
    .function("isCookieData", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCookieData))
    .function("getCookieDataConst", static_cast<org::sem::NamedProperty::CookieData const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCookieData))
    .function("getCookieDataMut", static_cast<org::sem::NamedProperty::CookieData&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCookieData))
    .function("isExportLatexClassOptions", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexClassOptions))
    .function("getExportLatexClassOptionsConst", static_cast<org::sem::NamedProperty::ExportLatexClassOptions const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getExportLatexClassOptions))
    .function("getExportLatexClassOptionsMut", static_cast<org::sem::NamedProperty::ExportLatexClassOptions&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexClassOptions))
    .function("isExportLatexHeader", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexHeader))
    .function("getExportLatexHeaderConst", static_cast<org::sem::NamedProperty::ExportLatexHeader const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getExportLatexHeader))
    .function("getExportLatexHeaderMut", static_cast<org::sem::NamedProperty::ExportLatexHeader&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexHeader))
    .function("isExportLatexCompiler", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexCompiler))
    .function("getExportLatexCompilerConst", static_cast<org::sem::NamedProperty::ExportLatexCompiler const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getExportLatexCompiler))
    .function("getExportLatexCompilerMut", static_cast<org::sem::NamedProperty::ExportLatexCompiler&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexCompiler))
    .function("isOrdered", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isOrdered))
    .function("getOrderedConst", static_cast<org::sem::NamedProperty::Ordered const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getOrdered))
    .function("getOrderedMut", static_cast<org::sem::NamedProperty::Ordered&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getOrdered))
    .function("isEffort", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isEffort))
    .function("getEffortConst", static_cast<org::sem::NamedProperty::Effort const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getEffort))
    .function("getEffortMut", static_cast<org::sem::NamedProperty::Effort&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getEffort))
    .function("isVisibility", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isVisibility))
    .function("getVisibilityConst", static_cast<org::sem::NamedProperty::Visibility const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getVisibility))
    .function("getVisibilityMut", static_cast<org::sem::NamedProperty::Visibility&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getVisibility))
    .function("isExportOptions", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportOptions))
    .function("getExportOptionsConst", static_cast<org::sem::NamedProperty::ExportOptions const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getExportOptions))
    .function("getExportOptionsMut", static_cast<org::sem::NamedProperty::ExportOptions&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportOptions))
    .function("isBlocker", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isBlocker))
    .function("getBlockerConst", static_cast<org::sem::NamedProperty::Blocker const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getBlocker))
    .function("getBlockerMut", static_cast<org::sem::NamedProperty::Blocker&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getBlocker))
    .function("isUnnumbered", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isUnnumbered))
    .function("getUnnumberedConst", static_cast<org::sem::NamedProperty::Unnumbered const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getUnnumbered))
    .function("getUnnumberedMut", static_cast<org::sem::NamedProperty::Unnumbered&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getUnnumbered))
    .function("isCreated", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCreated))
    .function("getCreatedConst", static_cast<org::sem::NamedProperty::Created const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCreated))
    .function("getCreatedMut", static_cast<org::sem::NamedProperty::Created&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCreated))
    .function("isRadioId", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isRadioId))
    .function("getRadioIdConst", static_cast<org::sem::NamedProperty::RadioId const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getRadioId))
    .function("getRadioIdMut", static_cast<org::sem::NamedProperty::RadioId&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getRadioId))
    .function("isHashtagDef", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isHashtagDef))
    .function("getHashtagDefConst", static_cast<org::sem::NamedProperty::HashtagDef const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getHashtagDef))
    .function("getHashtagDefMut", static_cast<org::sem::NamedProperty::HashtagDef&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getHashtagDef))
    .function("isCustomArgs", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomArgs))
    .function("getCustomArgsConst", static_cast<org::sem::NamedProperty::CustomArgs const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCustomArgs))
    .function("getCustomArgsMut", static_cast<org::sem::NamedProperty::CustomArgs&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomArgs))
    .function("isCustomRaw", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomRaw))
    .function("getCustomRawConst", static_cast<org::sem::NamedProperty::CustomRaw const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCustomRaw))
    .function("getCustomRawMut", static_cast<org::sem::NamedProperty::CustomRaw&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomRaw))
    .function("isCustomSubtreeJson", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomSubtreeJson))
    .function("getCustomSubtreeJsonConst", static_cast<org::sem::NamedProperty::CustomSubtreeJson const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCustomSubtreeJson))
    .function("getCustomSubtreeJsonMut", static_cast<org::sem::NamedProperty::CustomSubtreeJson&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomSubtreeJson))
    .function("isCustomSubtreeFlags", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomSubtreeFlags))
    .function("getCustomSubtreeFlagsConst", static_cast<org::sem::NamedProperty::CustomSubtreeFlags const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCustomSubtreeFlags))
    .function("getCustomSubtreeFlagsMut", static_cast<org::sem::NamedProperty::CustomSubtreeFlags&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomSubtreeFlags))
    .class_function("getKindStatic", static_cast<org::sem::NamedProperty::Kind(*)(org::sem::NamedProperty::Data const&)>(&org::sem::NamedProperty::getKind))
    .function("getKind", static_cast<org::sem::NamedProperty::Kind(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getKind))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::Nonblocking>("NamedPropertyNonblocking")
    .property("isBlocking", &org::sem::NamedProperty::Nonblocking::isBlocking)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::Nonblocking::*)(org::sem::NamedProperty::Nonblocking const&) const>(&org::sem::NamedProperty::Nonblocking::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::ArchiveTime>("NamedPropertyArchiveTime")
    .property("time", &org::sem::NamedProperty::ArchiveTime::time)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::ArchiveTime::*)(org::sem::NamedProperty::ArchiveTime const&) const>(&org::sem::NamedProperty::ArchiveTime::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::ArchiveFile>("NamedPropertyArchiveFile")
    .property("file", &org::sem::NamedProperty::ArchiveFile::file)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::ArchiveFile::*)(org::sem::NamedProperty::ArchiveFile const&) const>(&org::sem::NamedProperty::ArchiveFile::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::ArchiveOlpath>("NamedPropertyArchiveOlpath")
    .property("path", &org::sem::NamedProperty::ArchiveOlpath::path)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::ArchiveOlpath::*)(org::sem::NamedProperty::ArchiveOlpath const&) const>(&org::sem::NamedProperty::ArchiveOlpath::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::ArchiveTarget>("NamedPropertyArchiveTarget")
    .property("path", &org::sem::NamedProperty::ArchiveTarget::path)
    .property("pattern", &org::sem::NamedProperty::ArchiveTarget::pattern)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::ArchiveTarget::*)(org::sem::NamedProperty::ArchiveTarget const&) const>(&org::sem::NamedProperty::ArchiveTarget::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::ArchiveCategory>("NamedPropertyArchiveCategory")
    .property("category", &org::sem::NamedProperty::ArchiveCategory::category)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::ArchiveCategory::*)(org::sem::NamedProperty::ArchiveCategory const&) const>(&org::sem::NamedProperty::ArchiveCategory::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::ArchiveTodo>("NamedPropertyArchiveTodo")
    .property("todo", &org::sem::NamedProperty::ArchiveTodo::todo)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::ArchiveTodo::*)(org::sem::NamedProperty::ArchiveTodo const&) const>(&org::sem::NamedProperty::ArchiveTodo::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::Trigger>("NamedPropertyTrigger")
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::Trigger::*)(org::sem::NamedProperty::Trigger const&) const>(&org::sem::NamedProperty::Trigger::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::ExportLatexClass>("NamedPropertyExportLatexClass")
    .property("latexClass", &org::sem::NamedProperty::ExportLatexClass::latexClass)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::ExportLatexClass::*)(org::sem::NamedProperty::ExportLatexClass const&) const>(&org::sem::NamedProperty::ExportLatexClass::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::CookieData>("NamedPropertyCookieData")
    .property("isRecursive", &org::sem::NamedProperty::CookieData::isRecursive)
    .property("source", &org::sem::NamedProperty::CookieData::source)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::CookieData::*)(org::sem::NamedProperty::CookieData const&) const>(&org::sem::NamedProperty::CookieData::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::ExportLatexClassOptions>("NamedPropertyExportLatexClassOptions")
    .property("options", &org::sem::NamedProperty::ExportLatexClassOptions::options)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::ExportLatexClassOptions::*)(org::sem::NamedProperty::ExportLatexClassOptions const&) const>(&org::sem::NamedProperty::ExportLatexClassOptions::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::ExportLatexHeader>("NamedPropertyExportLatexHeader")
    .property("header", &org::sem::NamedProperty::ExportLatexHeader::header)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::ExportLatexHeader::*)(org::sem::NamedProperty::ExportLatexHeader const&) const>(&org::sem::NamedProperty::ExportLatexHeader::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::ExportLatexCompiler>("NamedPropertyExportLatexCompiler")
    .property("compiler", &org::sem::NamedProperty::ExportLatexCompiler::compiler)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::ExportLatexCompiler::*)(org::sem::NamedProperty::ExportLatexCompiler const&) const>(&org::sem::NamedProperty::ExportLatexCompiler::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::Ordered>("NamedPropertyOrdered")
    .property("isOrdered", &org::sem::NamedProperty::Ordered::isOrdered)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::Ordered::*)(org::sem::NamedProperty::Ordered const&) const>(&org::sem::NamedProperty::Ordered::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::Effort>("NamedPropertyEffort")
    .property("hours", &org::sem::NamedProperty::Effort::hours)
    .property("minutes", &org::sem::NamedProperty::Effort::minutes)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::Effort::*)(org::sem::NamedProperty::Effort const&) const>(&org::sem::NamedProperty::Effort::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::Visibility>("NamedPropertyVisibility")
    .property("level", &org::sem::NamedProperty::Visibility::level)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::Visibility::*)(org::sem::NamedProperty::Visibility const&) const>(&org::sem::NamedProperty::Visibility::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::NamedProperty::Visibility::Level>("OrgSemNamedPropertyVisibilityLevel");
  emscripten::class_<org::sem::NamedProperty::ExportOptions>("NamedPropertyExportOptions")
    .property("backend", &org::sem::NamedProperty::ExportOptions::backend)
    .property("values", &org::sem::NamedProperty::ExportOptions::values)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::ExportOptions::*)(org::sem::NamedProperty::ExportOptions const&) const>(&org::sem::NamedProperty::ExportOptions::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::Blocker>("NamedPropertyBlocker")
    .property("blockers", &org::sem::NamedProperty::Blocker::blockers)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::Blocker::*)(org::sem::NamedProperty::Blocker const&) const>(&org::sem::NamedProperty::Blocker::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::Unnumbered>("NamedPropertyUnnumbered")
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::Unnumbered::*)(org::sem::NamedProperty::Unnumbered const&) const>(&org::sem::NamedProperty::Unnumbered::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::Created>("NamedPropertyCreated")
    .property("time", &org::sem::NamedProperty::Created::time)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::Created::*)(org::sem::NamedProperty::Created const&) const>(&org::sem::NamedProperty::Created::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::RadioId>("NamedPropertyRadioId")
    .property("words", &org::sem::NamedProperty::RadioId::words)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::RadioId::*)(org::sem::NamedProperty::RadioId const&) const>(&org::sem::NamedProperty::RadioId::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::HashtagDef>("NamedPropertyHashtagDef")
    .property("hashtag", &org::sem::NamedProperty::HashtagDef::hashtag)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::HashtagDef::*)(org::sem::NamedProperty::HashtagDef const&) const>(&org::sem::NamedProperty::HashtagDef::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::CustomArgs>("NamedPropertyCustomArgs")
    .property("name", &org::sem::NamedProperty::CustomArgs::name)
    .property("sub", &org::sem::NamedProperty::CustomArgs::sub)
    .property("attrs", &org::sem::NamedProperty::CustomArgs::attrs)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::CustomArgs::*)(org::sem::NamedProperty::CustomArgs const&) const>(&org::sem::NamedProperty::CustomArgs::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::CustomRaw>("NamedPropertyCustomRaw")
    .property("name", &org::sem::NamedProperty::CustomRaw::name)
    .property("value", &org::sem::NamedProperty::CustomRaw::value)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::CustomRaw::*)(org::sem::NamedProperty::CustomRaw const&) const>(&org::sem::NamedProperty::CustomRaw::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::CustomSubtreeJson>("NamedPropertyCustomSubtreeJson")
    .property("name", &org::sem::NamedProperty::CustomSubtreeJson::name)
    .property("value", &org::sem::NamedProperty::CustomSubtreeJson::value)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::CustomSubtreeJson::*)(org::sem::NamedProperty::CustomSubtreeJson const&) const>(&org::sem::NamedProperty::CustomSubtreeJson::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::CustomSubtreeFlags>("NamedPropertyCustomSubtreeFlags")
    .property("name", &org::sem::NamedProperty::CustomSubtreeFlags::name)
    .property("value", &org::sem::NamedProperty::CustomSubtreeFlags::value)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::CustomSubtreeFlags::*)(org::sem::NamedProperty::CustomSubtreeFlags const&) const>(&org::sem::NamedProperty::CustomSubtreeFlags::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::NamedProperty::Kind>("OrgSemNamedPropertyKind");
  emscripten::class_<org::sem::None, emscripten::base<org::sem::Org>>("None")
    .smart_ptr<org::sem::SemId<org::sem::None>>("None")
    .function("getKind", static_cast<OrgSemKind(org::sem::None::*)() const>(&org::sem::None::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::None>>)
    ;
  emscripten::class_<org::sem::ErrorItem, emscripten::base<org::sem::Org>>("ErrorItem")
    .smart_ptr<org::sem::SemId<org::sem::ErrorItem>>("ErrorItem")
    .property("message", &org::sem::ErrorItem::message)
    .property("function", &org::sem::ErrorItem::function)
    .property("line", &org::sem::ErrorItem::line)
    .function("getKind", static_cast<OrgSemKind(org::sem::ErrorItem::*)() const>(&org::sem::ErrorItem::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::ErrorItem>>)
    ;
  emscripten::class_<org::sem::ErrorGroup, emscripten::base<org::sem::Org>>("ErrorGroup")
    .smart_ptr<org::sem::SemId<org::sem::ErrorGroup>>("ErrorGroup")
    .property("diagnostics", &org::sem::ErrorGroup::diagnostics)
    .property("function", &org::sem::ErrorGroup::function)
    .property("line", &org::sem::ErrorGroup::line)
    .function("getKind", static_cast<OrgSemKind(org::sem::ErrorGroup::*)() const>(&org::sem::ErrorGroup::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::ErrorGroup>>)
    ;
  emscripten::class_<org::sem::Stmt, emscripten::base<org::sem::Org>>("Stmt")
    .smart_ptr<org::sem::SemId<org::sem::Stmt>>("Stmt")
    .property("attached", &org::sem::Stmt::attached)
    .function("getAttached", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Stmt::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Stmt::getAttached))
    .function("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Stmt::*)() const>(&org::sem::Stmt::getCaption))
    .function("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::Stmt::*)() const>(&org::sem::Stmt::getName))
    .function("getAttrs", static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Stmt::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Stmt::getAttrs))
    .function("getFirstAttr", static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttr))
    ;
  emscripten::class_<org::sem::Inline, emscripten::base<org::sem::Org>>("Inline")
    .smart_ptr<org::sem::SemId<org::sem::Inline>>("Inline")
    ;
  emscripten::class_<org::sem::StmtList, emscripten::base<org::sem::Org>>("StmtList")
    .smart_ptr<org::sem::SemId<org::sem::StmtList>>("StmtList")
    .function("getKind", static_cast<OrgSemKind(org::sem::StmtList::*)() const>(&org::sem::StmtList::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::StmtList>>)
    ;
  emscripten::class_<org::sem::Empty, emscripten::base<org::sem::Org>>("Empty")
    .smart_ptr<org::sem::SemId<org::sem::Empty>>("Empty")
    .function("getKind", static_cast<OrgSemKind(org::sem::Empty::*)() const>(&org::sem::Empty::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Empty>>)
    ;
  emscripten::class_<org::sem::Leaf, emscripten::base<org::sem::Org>>("Leaf")
    .smart_ptr<org::sem::SemId<org::sem::Leaf>>("Leaf")
    .property("text", &org::sem::Leaf::text)
    .function("getText", static_cast<hstd::Str(org::sem::Leaf::*)() const>(&org::sem::Leaf::getText))
    ;
  emscripten::class_<org::sem::Time, emscripten::base<org::sem::Org>>("Time")
    .smart_ptr<org::sem::SemId<org::sem::Time>>("Time")
    .property("isActive", &org::sem::Time::isActive)
    .property("time", &org::sem::Time::time)
    .function("getKind", static_cast<OrgSemKind(org::sem::Time::*)() const>(&org::sem::Time::getKind))
    .function("getYear", static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getYear))
    .function("getMonth", static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getMonth))
    .function("getDay", static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getDay))
    .function("getHour", static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getHour))
    .function("getMinute", static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getMinute))
    .function("getSecond", static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getSecond))
    .function("getStaticTime", static_cast<hstd::UserTime(org::sem::Time::*)() const>(&org::sem::Time::getStaticTime))
    .function("isStatic", static_cast<bool(org::sem::Time::*)() const>(&org::sem::Time::isStatic))
    .function("getStaticConst", static_cast<org::sem::Time::Static const&(org::sem::Time::*)() const>(&org::sem::Time::getStatic))
    .function("getStaticMut", static_cast<org::sem::Time::Static&(org::sem::Time::*)()>(&org::sem::Time::getStatic))
    .function("isDynamic", static_cast<bool(org::sem::Time::*)() const>(&org::sem::Time::isDynamic))
    .function("getDynamicConst", static_cast<org::sem::Time::Dynamic const&(org::sem::Time::*)() const>(&org::sem::Time::getDynamic))
    .function("getDynamicMut", static_cast<org::sem::Time::Dynamic&(org::sem::Time::*)()>(&org::sem::Time::getDynamic))
    .class_function("getTimeKindStatic", static_cast<org::sem::Time::TimeKind(*)(org::sem::Time::TimeVariant const&)>(&org::sem::Time::getTimeKind))
    .function("getTimeKind", static_cast<org::sem::Time::TimeKind(org::sem::Time::*)() const>(&org::sem::Time::getTimeKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Time>>)
    ;
  emscripten::class_<org::sem::Time::Repeat>("TimeRepeat")
    .property("mode", &org::sem::Time::Repeat::mode)
    .property("period", &org::sem::Time::Repeat::period)
    .property("count", &org::sem::Time::Repeat::count)
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::Time::Repeat::Mode>("OrgSemTimeRepeatMode");
  org::bind::js::bind_enum<org::sem::Time::Repeat::Period>("OrgSemTimeRepeatPeriod");
  emscripten::class_<org::sem::Time::Static>("TimeStatic")
    .property("repeat", &org::sem::Time::Static::repeat)
    .property("warn", &org::sem::Time::Static::warn)
    .property("time", &org::sem::Time::Static::time)
    .constructor<>()
    ;
  emscripten::class_<org::sem::Time::Dynamic>("TimeDynamic")
    .property("expr", &org::sem::Time::Dynamic::expr)
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::Time::TimeKind>("OrgSemTimeTimeKind");
  emscripten::class_<org::sem::TimeRange, emscripten::base<org::sem::Org>>("TimeRange")
    .smart_ptr<org::sem::SemId<org::sem::TimeRange>>("TimeRange")
    .property("from", &org::sem::TimeRange::from)
    .property("to", &org::sem::TimeRange::to)
    .function("getKind", static_cast<OrgSemKind(org::sem::TimeRange::*)() const>(&org::sem::TimeRange::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::TimeRange>>)
    ;
  emscripten::class_<org::sem::Macro, emscripten::base<org::sem::Org>>("Macro")
    .smart_ptr<org::sem::SemId<org::sem::Macro>>("Macro")
    .property("name", &org::sem::Macro::name)
    .property("attrs", &org::sem::Macro::attrs)
    .function("getKind", static_cast<OrgSemKind(org::sem::Macro::*)() const>(&org::sem::Macro::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Macro>>)
    ;
  emscripten::class_<org::sem::Symbol, emscripten::base<org::sem::Org>>("Symbol")
    .smart_ptr<org::sem::SemId<org::sem::Symbol>>("Symbol")
    .property("name", &org::sem::Symbol::name)
    .property("parameters", &org::sem::Symbol::parameters)
    .property("positional", &org::sem::Symbol::positional)
    .function("getKind", static_cast<OrgSemKind(org::sem::Symbol::*)() const>(&org::sem::Symbol::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Symbol>>)
    ;
  emscripten::class_<org::sem::Symbol::Param>("SymbolParam")
    .property("key", &org::sem::Symbol::Param::key)
    .property("value", &org::sem::Symbol::Param::value)
    .constructor<>()
    ;
  emscripten::class_<org::sem::Markup, emscripten::base<org::sem::Org>>("Markup")
    .smart_ptr<org::sem::SemId<org::sem::Markup>>("Markup")
    ;
  emscripten::class_<org::sem::RadioTarget, emscripten::base<org::sem::Org>>("RadioTarget")
    .smart_ptr<org::sem::SemId<org::sem::RadioTarget>>("RadioTarget")
    .property("words", &org::sem::RadioTarget::words)
    .function("getKind", static_cast<OrgSemKind(org::sem::RadioTarget::*)() const>(&org::sem::RadioTarget::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::RadioTarget>>)
    ;
  emscripten::class_<org::sem::Latex, emscripten::base<org::sem::Org>>("Latex")
    .smart_ptr<org::sem::SemId<org::sem::Latex>>("Latex")
    .function("getKind", static_cast<OrgSemKind(org::sem::Latex::*)() const>(&org::sem::Latex::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Latex>>)
    ;
  emscripten::class_<org::sem::SubtreeLog, emscripten::base<org::sem::Org>>("SubtreeLog")
    .smart_ptr<org::sem::SemId<org::sem::SubtreeLog>>("SubtreeLog")
    .property("head", &org::sem::SubtreeLog::head)
    .property("desc", &org::sem::SubtreeLog::desc)
    .function("getKind", static_cast<OrgSemKind(org::sem::SubtreeLog::*)() const>(&org::sem::SubtreeLog::getKind))
    .function("setDescription", static_cast<void(org::sem::SubtreeLog::*)(org::sem::SemId<org::sem::StmtList>)>(&org::sem::SubtreeLog::setDescription))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::SubtreeLog>>)
    ;
  emscripten::class_<org::sem::Subtree, emscripten::base<org::sem::Org>>("Subtree")
    .smart_ptr<org::sem::SemId<org::sem::Subtree>>("Subtree")
    .property("level", &org::sem::Subtree::level)
    .property("treeId", &org::sem::Subtree::treeId)
    .property("todo", &org::sem::Subtree::todo)
    .property("completion", &org::sem::Subtree::completion)
    .property("description", &org::sem::Subtree::description)
    .property("tags", &org::sem::Subtree::tags)
    .property("title", &org::sem::Subtree::title)
    .property("logbook", &org::sem::Subtree::logbook)
    .property("properties", &org::sem::Subtree::properties)
    .property("closed", &org::sem::Subtree::closed)
    .property("deadline", &org::sem::Subtree::deadline)
    .property("scheduled", &org::sem::Subtree::scheduled)
    .property("isComment", &org::sem::Subtree::isComment)
    .property("isArchived", &org::sem::Subtree::isArchived)
    .property("priority", &org::sem::Subtree::priority)
    .function("getKind", static_cast<OrgSemKind(org::sem::Subtree::*)() const>(&org::sem::Subtree::getKind))
    .function("getTimePeriods", static_cast<hstd::Vec<org::sem::SubtreePeriod>(org::sem::Subtree::*)(hstd::IntSet<org::sem::SubtreePeriod::Kind>) const>(&org::sem::Subtree::getTimePeriods))
    .function("getProperties", static_cast<hstd::Vec<org::sem::NamedProperty>(org::sem::Subtree::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Subtree::getProperties))
    .function("getProperty", static_cast<hstd::Opt<org::sem::NamedProperty>(org::sem::Subtree::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Subtree::getProperty))
    .function("removeProperty", static_cast<void(org::sem::Subtree::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&)>(&org::sem::Subtree::removeProperty))
    .function("setProperty", static_cast<void(org::sem::Subtree::*)(org::sem::NamedProperty const&)>(&org::sem::Subtree::setProperty))
    .function("setPropertyStrValue", static_cast<void(org::sem::Subtree::*)(hstd::Str const&, hstd::Str const&, hstd::Opt<hstd::Str> const&)>(&org::sem::Subtree::setPropertyStrValue))
    .function("getCleanTitle", static_cast<hstd::Str(org::sem::Subtree::*)() const>(&org::sem::Subtree::getCleanTitle))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Subtree>>)
    ;
  emscripten::class_<org::sem::ColonExample, emscripten::base<org::sem::Org>>("ColonExample")
    .smart_ptr<org::sem::SemId<org::sem::ColonExample>>("ColonExample")
    .function("getKind", static_cast<OrgSemKind(org::sem::ColonExample::*)() const>(&org::sem::ColonExample::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::ColonExample>>)
    ;
  emscripten::class_<org::sem::Call, emscripten::base<org::sem::Org>>("Call")
    .smart_ptr<org::sem::SemId<org::sem::Call>>("Call")
    .property("name", &org::sem::Call::name)
    .property("attrs", &org::sem::Call::attrs)
    .property("isCommand", &org::sem::Call::isCommand)
    .function("getKind", static_cast<OrgSemKind(org::sem::Call::*)() const>(&org::sem::Call::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Call>>)
    ;
  emscripten::class_<org::sem::ListItem, emscripten::base<org::sem::Org>>("ListItem")
    .smart_ptr<org::sem::SemId<org::sem::ListItem>>("ListItem")
    .property("checkbox", &org::sem::ListItem::checkbox)
    .property("header", &org::sem::ListItem::header)
    .property("bullet", &org::sem::ListItem::bullet)
    .function("getKind", static_cast<OrgSemKind(org::sem::ListItem::*)() const>(&org::sem::ListItem::getKind))
    .function("isDescriptionItem", static_cast<bool(org::sem::ListItem::*)() const>(&org::sem::ListItem::isDescriptionItem))
    .function("getCleanHeader", static_cast<hstd::Opt<hstd::Str>(org::sem::ListItem::*)() const>(&org::sem::ListItem::getCleanHeader))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::ListItem>>)
    ;
  emscripten::class_<org::sem::DocumentOptions, emscripten::base<org::sem::Org>>("DocumentOptions")
    .smart_ptr<org::sem::SemId<org::sem::DocumentOptions>>("DocumentOptions")
    .property("initialVisibility", &org::sem::DocumentOptions::initialVisibility)
    .property("properties", &org::sem::DocumentOptions::properties)
    .property("exportConfig", &org::sem::DocumentOptions::exportConfig)
    .property("fixedWidthSections", &org::sem::DocumentOptions::fixedWidthSections)
    .property("startupIndented", &org::sem::DocumentOptions::startupIndented)
    .property("category", &org::sem::DocumentOptions::category)
    .property("setupfile", &org::sem::DocumentOptions::setupfile)
    .property("maxSubtreeLevelExport", &org::sem::DocumentOptions::maxSubtreeLevelExport)
    .property("columns", &org::sem::DocumentOptions::columns)
    .property("todoKeywords", &org::sem::DocumentOptions::todoKeywords)
    .property("doneKeywords", &org::sem::DocumentOptions::doneKeywords)
    .function("getKind", static_cast<OrgSemKind(org::sem::DocumentOptions::*)() const>(&org::sem::DocumentOptions::getKind))
    .function("getProperties", static_cast<hstd::Vec<org::sem::NamedProperty>(org::sem::DocumentOptions::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::DocumentOptions::getProperties))
    .function("getProperty", static_cast<hstd::Opt<org::sem::NamedProperty>(org::sem::DocumentOptions::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::DocumentOptions::getProperty))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::DocumentOptions>>)
    ;
  emscripten::class_<org::sem::DocumentFragment, emscripten::base<org::sem::Org>>("DocumentFragment")
    .smart_ptr<org::sem::SemId<org::sem::DocumentFragment>>("DocumentFragment")
    .property("baseLine", &org::sem::DocumentFragment::baseLine)
    .property("baseCol", &org::sem::DocumentFragment::baseCol)
    .function("getKind", static_cast<OrgSemKind(org::sem::DocumentFragment::*)() const>(&org::sem::DocumentFragment::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::DocumentFragment>>)
    ;
  emscripten::class_<org::sem::CriticMarkup, emscripten::base<org::sem::Org>>("CriticMarkup")
    .smart_ptr<org::sem::SemId<org::sem::CriticMarkup>>("CriticMarkup")
    .property("kind", &org::sem::CriticMarkup::kind)
    .function("getKind", static_cast<OrgSemKind(org::sem::CriticMarkup::*)() const>(&org::sem::CriticMarkup::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::CriticMarkup>>)
    ;
  org::bind::js::bind_enum<org::sem::CriticMarkup::Kind>("OrgSemCriticMarkupKind");
  emscripten::class_<org::sem::Document, emscripten::base<org::sem::Org>>("Document")
    .smart_ptr<org::sem::SemId<org::sem::Document>>("Document")
    .property("title", &org::sem::Document::title)
    .property("author", &org::sem::Document::author)
    .property("creator", &org::sem::Document::creator)
    .property("filetags", &org::sem::Document::filetags)
    .property("email", &org::sem::Document::email)
    .property("language", &org::sem::Document::language)
    .property("options", &org::sem::Document::options)
    .property("exportFileName", &org::sem::Document::exportFileName)
    .function("getKind", static_cast<OrgSemKind(org::sem::Document::*)() const>(&org::sem::Document::getKind))
    .function("getProperties", static_cast<hstd::Vec<org::sem::NamedProperty>(org::sem::Document::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Document::getProperties))
    .function("getProperty", static_cast<hstd::Opt<org::sem::NamedProperty>(org::sem::Document::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Document::getProperty))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Document>>)
    ;
  emscripten::class_<org::sem::FileTarget, emscripten::base<org::sem::Org>>("FileTarget")
    .smart_ptr<org::sem::SemId<org::sem::FileTarget>>("FileTarget")
    .property("path", &org::sem::FileTarget::path)
    .property("line", &org::sem::FileTarget::line)
    .property("searchTarget", &org::sem::FileTarget::searchTarget)
    .property("restrictToHeadlines", &org::sem::FileTarget::restrictToHeadlines)
    .property("targetId", &org::sem::FileTarget::targetId)
    .property("regexp", &org::sem::FileTarget::regexp)
    .function("getKind", static_cast<OrgSemKind(org::sem::FileTarget::*)() const>(&org::sem::FileTarget::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::FileTarget>>)
    ;
  emscripten::class_<org::sem::TextSeparator, emscripten::base<org::sem::Org>>("TextSeparator")
    .smart_ptr<org::sem::SemId<org::sem::TextSeparator>>("TextSeparator")
    .function("getKind", static_cast<OrgSemKind(org::sem::TextSeparator::*)() const>(&org::sem::TextSeparator::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::TextSeparator>>)
    ;
  emscripten::class_<org::sem::DocumentGroup, emscripten::base<org::sem::Org>>("DocumentGroup")
    .smart_ptr<org::sem::SemId<org::sem::DocumentGroup>>("DocumentGroup")
    .function("getKind", static_cast<OrgSemKind(org::sem::DocumentGroup::*)() const>(&org::sem::DocumentGroup::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::DocumentGroup>>)
    ;
  emscripten::class_<org::sem::File, emscripten::base<org::sem::Org>>("File")
    .smart_ptr<org::sem::SemId<org::sem::File>>("File")
    .property("relPath", &org::sem::File::relPath)
    .property("absPath", &org::sem::File::absPath)
    .property("data", &org::sem::File::data)
    .function("getKind", static_cast<OrgSemKind(org::sem::File::*)() const>(&org::sem::File::getKind))
    .function("isDocument", static_cast<bool(org::sem::File::*)() const>(&org::sem::File::isDocument))
    .function("getDocumentConst", static_cast<org::sem::File::Document const&(org::sem::File::*)() const>(&org::sem::File::getDocument))
    .function("getDocumentMut", static_cast<org::sem::File::Document&(org::sem::File::*)()>(&org::sem::File::getDocument))
    .function("isAttachment", static_cast<bool(org::sem::File::*)() const>(&org::sem::File::isAttachment))
    .function("getAttachmentConst", static_cast<org::sem::File::Attachment const&(org::sem::File::*)() const>(&org::sem::File::getAttachment))
    .function("getAttachmentMut", static_cast<org::sem::File::Attachment&(org::sem::File::*)()>(&org::sem::File::getAttachment))
    .function("isSource", static_cast<bool(org::sem::File::*)() const>(&org::sem::File::isSource))
    .function("getSourceConst", static_cast<org::sem::File::Source const&(org::sem::File::*)() const>(&org::sem::File::getSource))
    .function("getSourceMut", static_cast<org::sem::File::Source&(org::sem::File::*)()>(&org::sem::File::getSource))
    .class_function("getFileKindStatic", static_cast<org::sem::File::Kind(*)(org::sem::File::Data const&)>(&org::sem::File::getFileKind))
    .function("getFileKind", static_cast<org::sem::File::Kind(org::sem::File::*)() const>(&org::sem::File::getFileKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::File>>)
    ;
  emscripten::class_<org::sem::File::Document>("FileDocument")
    .constructor<>()
    ;
  emscripten::class_<org::sem::File::Attachment>("FileAttachment")
    .constructor<>()
    ;
  emscripten::class_<org::sem::File::Source>("FileSource")
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::File::Kind>("OrgSemFileKind");
  emscripten::class_<org::sem::Directory, emscripten::base<org::sem::Org>>("Directory")
    .smart_ptr<org::sem::SemId<org::sem::Directory>>("Directory")
    .property("relPath", &org::sem::Directory::relPath)
    .property("absPath", &org::sem::Directory::absPath)
    .function("getKind", static_cast<OrgSemKind(org::sem::Directory::*)() const>(&org::sem::Directory::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Directory>>)
    ;
  emscripten::class_<org::sem::Symlink, emscripten::base<org::sem::Org>>("Symlink")
    .smart_ptr<org::sem::SemId<org::sem::Symlink>>("Symlink")
    .property("isDirectory", &org::sem::Symlink::isDirectory)
    .property("absPath", &org::sem::Symlink::absPath)
    .function("getKind", static_cast<OrgSemKind(org::sem::Symlink::*)() const>(&org::sem::Symlink::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Symlink>>)
    ;
  emscripten::class_<org::sem::CmdInclude, emscripten::base<org::sem::Org>>("CmdInclude")
    .smart_ptr<org::sem::SemId<org::sem::CmdInclude>>("CmdInclude")
    .property("path", &org::sem::CmdInclude::path)
    .property("firstLine", &org::sem::CmdInclude::firstLine)
    .property("lastLine", &org::sem::CmdInclude::lastLine)
    .property("data", &org::sem::CmdInclude::data)
    .function("getKind", static_cast<OrgSemKind(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getKind))
    .function("isExample", static_cast<bool(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::isExample))
    .function("getExampleConst", static_cast<org::sem::CmdInclude::Example const&(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getExample))
    .function("getExampleMut", static_cast<org::sem::CmdInclude::Example&(org::sem::CmdInclude::*)()>(&org::sem::CmdInclude::getExample))
    .function("isExport", static_cast<bool(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::isExport))
    .function("getExportConst", static_cast<org::sem::CmdInclude::Export const&(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getExport))
    .function("getExportMut", static_cast<org::sem::CmdInclude::Export&(org::sem::CmdInclude::*)()>(&org::sem::CmdInclude::getExport))
    .function("isCustom", static_cast<bool(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::isCustom))
    .function("getCustomConst", static_cast<org::sem::CmdInclude::Custom const&(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getCustom))
    .function("getCustomMut", static_cast<org::sem::CmdInclude::Custom&(org::sem::CmdInclude::*)()>(&org::sem::CmdInclude::getCustom))
    .function("isSrc", static_cast<bool(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::isSrc))
    .function("getSrcConst", static_cast<org::sem::CmdInclude::Src const&(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getSrc))
    .function("getSrcMut", static_cast<org::sem::CmdInclude::Src&(org::sem::CmdInclude::*)()>(&org::sem::CmdInclude::getSrc))
    .function("isOrgDocument", static_cast<bool(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::isOrgDocument))
    .function("getOrgDocumentConst", static_cast<org::sem::CmdInclude::OrgDocument const&(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getOrgDocument))
    .function("getOrgDocumentMut", static_cast<org::sem::CmdInclude::OrgDocument&(org::sem::CmdInclude::*)()>(&org::sem::CmdInclude::getOrgDocument))
    .class_function("getIncludeKindStatic", static_cast<org::sem::CmdInclude::Kind(*)(org::sem::CmdInclude::Data const&)>(&org::sem::CmdInclude::getIncludeKind))
    .function("getIncludeKind", static_cast<org::sem::CmdInclude::Kind(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getIncludeKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::CmdInclude>>)
    ;
  emscripten::class_<org::sem::CmdInclude::IncludeBase>("CmdIncludeIncludeBase")
    .constructor<>()
    ;
  emscripten::class_<org::sem::CmdInclude::Example, emscripten::base<org::sem::CmdInclude::IncludeBase>>("CmdIncludeExample")
    .constructor<>()
    ;
  emscripten::class_<org::sem::CmdInclude::Export, emscripten::base<org::sem::CmdInclude::IncludeBase>>("CmdIncludeExport")
    .property("language", &org::sem::CmdInclude::Export::language)
    .constructor<>()
    ;
  emscripten::class_<org::sem::CmdInclude::Custom, emscripten::base<org::sem::CmdInclude::IncludeBase>>("CmdIncludeCustom")
    .property("blockName", &org::sem::CmdInclude::Custom::blockName)
    .constructor<>()
    ;
  emscripten::class_<org::sem::CmdInclude::Src, emscripten::base<org::sem::CmdInclude::IncludeBase>>("CmdIncludeSrc")
    .property("language", &org::sem::CmdInclude::Src::language)
    .constructor<>()
    ;
  emscripten::class_<org::sem::CmdInclude::OrgDocument, emscripten::base<org::sem::CmdInclude::IncludeBase>>("CmdIncludeOrgDocument")
    .property("onlyContent", &org::sem::CmdInclude::OrgDocument::onlyContent)
    .property("subtreePath", &org::sem::CmdInclude::OrgDocument::subtreePath)
    .property("minLevel", &org::sem::CmdInclude::OrgDocument::minLevel)
    .property("customIdTarget", &org::sem::CmdInclude::OrgDocument::customIdTarget)
    .constructor<>()
    ;
}

void subdivide_4(org::bind::js::type_registration_guard& g) {
  org::bind::js::bind_enum<org::sem::CmdInclude::Kind>("OrgSemCmdIncludeKind");
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmNone>, emscripten::base<org::imm::ImmId>>("ImmIdTNone")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmErrorItem>, emscripten::base<org::imm::ImmId>>("ImmIdTErrorItem")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmErrorGroup>, emscripten::base<org::imm::ImmId>>("ImmIdTErrorGroup")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmStmt>, emscripten::base<org::imm::ImmId>>("ImmIdTStmt")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmInline>, emscripten::base<org::imm::ImmId>>("ImmIdTInline")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmStmtList>, emscripten::base<org::imm::ImmId>>("ImmIdTStmtList")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmEmpty>, emscripten::base<org::imm::ImmId>>("ImmIdTEmpty")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCmd>, emscripten::base<org::imm::ImmId>>("ImmIdTCmd")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmBlock>, emscripten::base<org::imm::ImmId>>("ImmIdTBlock")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmLineCommand>, emscripten::base<org::imm::ImmId>>("ImmIdTLineCommand")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmAttached>, emscripten::base<org::imm::ImmId>>("ImmIdTAttached")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmLeaf>, emscripten::base<org::imm::ImmId>>("ImmIdTLeaf")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCmdCaption>, emscripten::base<org::imm::ImmId>>("ImmIdTCmdCaption")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCmdColumns>, emscripten::base<org::imm::ImmId>>("ImmIdTCmdColumns")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCmdName>, emscripten::base<org::imm::ImmId>>("ImmIdTCmdName")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCmdCustomArgs>, emscripten::base<org::imm::ImmId>>("ImmIdTCmdCustomArgs")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCmdCustomRaw>, emscripten::base<org::imm::ImmId>>("ImmIdTCmdCustomRaw")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCmdCustomText>, emscripten::base<org::imm::ImmId>>("ImmIdTCmdCustomText")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCmdCall>, emscripten::base<org::imm::ImmId>>("ImmIdTCmdCall")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCmdTblfm>, emscripten::base<org::imm::ImmId>>("ImmIdTCmdTblfm")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmHashTag>, emscripten::base<org::imm::ImmId>>("ImmIdTHashTag")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmInlineFootnote>, emscripten::base<org::imm::ImmId>>("ImmIdTInlineFootnote")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmInlineExport>, emscripten::base<org::imm::ImmId>>("ImmIdTInlineExport")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmTime>, emscripten::base<org::imm::ImmId>>("ImmIdTTime")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmTimeRange>, emscripten::base<org::imm::ImmId>>("ImmIdTTimeRange")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmMacro>, emscripten::base<org::imm::ImmId>>("ImmIdTMacro")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmSymbol>, emscripten::base<org::imm::ImmId>>("ImmIdTSymbol")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmEscaped>, emscripten::base<org::imm::ImmId>>("ImmIdTEscaped")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmNewline>, emscripten::base<org::imm::ImmId>>("ImmIdTNewline")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmSpace>, emscripten::base<org::imm::ImmId>>("ImmIdTSpace")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmWord>, emscripten::base<org::imm::ImmId>>("ImmIdTWord")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmAtMention>, emscripten::base<org::imm::ImmId>>("ImmIdTAtMention")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmRawText>, emscripten::base<org::imm::ImmId>>("ImmIdTRawText")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmPunctuation>, emscripten::base<org::imm::ImmId>>("ImmIdTPunctuation")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmPlaceholder>, emscripten::base<org::imm::ImmId>>("ImmIdTPlaceholder")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmBigIdent>, emscripten::base<org::imm::ImmId>>("ImmIdTBigIdent")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmTextTarget>, emscripten::base<org::imm::ImmId>>("ImmIdTTextTarget")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmMarkup>, emscripten::base<org::imm::ImmId>>("ImmIdTMarkup")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmBold>, emscripten::base<org::imm::ImmId>>("ImmIdTBold")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmUnderline>, emscripten::base<org::imm::ImmId>>("ImmIdTUnderline")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmMonospace>, emscripten::base<org::imm::ImmId>>("ImmIdTMonospace")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmMarkQuote>, emscripten::base<org::imm::ImmId>>("ImmIdTMarkQuote")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmVerbatim>, emscripten::base<org::imm::ImmId>>("ImmIdTVerbatim")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmItalic>, emscripten::base<org::imm::ImmId>>("ImmIdTItalic")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmStrike>, emscripten::base<org::imm::ImmId>>("ImmIdTStrike")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmPar>, emscripten::base<org::imm::ImmId>>("ImmIdTPar")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmRadioTarget>, emscripten::base<org::imm::ImmId>>("ImmIdTRadioTarget")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmLatex>, emscripten::base<org::imm::ImmId>>("ImmIdTLatex")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmLink>, emscripten::base<org::imm::ImmId>>("ImmIdTLink")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmBlockCenter>, emscripten::base<org::imm::ImmId>>("ImmIdTBlockCenter")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmBlockQuote>, emscripten::base<org::imm::ImmId>>("ImmIdTBlockQuote")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmBlockComment>, emscripten::base<org::imm::ImmId>>("ImmIdTBlockComment")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmBlockVerse>, emscripten::base<org::imm::ImmId>>("ImmIdTBlockVerse")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmBlockDynamicFallback>, emscripten::base<org::imm::ImmId>>("ImmIdTBlockDynamicFallback")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmBlockExample>, emscripten::base<org::imm::ImmId>>("ImmIdTBlockExample")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmBlockExport>, emscripten::base<org::imm::ImmId>>("ImmIdTBlockExport")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmBlockAdmonition>, emscripten::base<org::imm::ImmId>>("ImmIdTBlockAdmonition")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>, emscripten::base<org::imm::ImmId>>("ImmIdTBlockCodeEvalResult")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmBlockCode>, emscripten::base<org::imm::ImmId>>("ImmIdTBlockCode")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmSubtreeLog>, emscripten::base<org::imm::ImmId>>("ImmIdTSubtreeLog")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmSubtree>, emscripten::base<org::imm::ImmId>>("ImmIdTSubtree")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCell>, emscripten::base<org::imm::ImmId>>("ImmIdTCell")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmRow>, emscripten::base<org::imm::ImmId>>("ImmIdTRow")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmTable>, emscripten::base<org::imm::ImmId>>("ImmIdTTable")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmParagraph>, emscripten::base<org::imm::ImmId>>("ImmIdTParagraph")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmColonExample>, emscripten::base<org::imm::ImmId>>("ImmIdTColonExample")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCmdAttr>, emscripten::base<org::imm::ImmId>>("ImmIdTCmdAttr")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCmdExport>, emscripten::base<org::imm::ImmId>>("ImmIdTCmdExport")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCall>, emscripten::base<org::imm::ImmId>>("ImmIdTCall")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmList>, emscripten::base<org::imm::ImmId>>("ImmIdTList")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmListItem>, emscripten::base<org::imm::ImmId>>("ImmIdTListItem")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmDocumentOptions>, emscripten::base<org::imm::ImmId>>("ImmIdTDocumentOptions")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmDocumentFragment>, emscripten::base<org::imm::ImmId>>("ImmIdTDocumentFragment")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCriticMarkup>, emscripten::base<org::imm::ImmId>>("ImmIdTCriticMarkup")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmDocument>, emscripten::base<org::imm::ImmId>>("ImmIdTDocument")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmFileTarget>, emscripten::base<org::imm::ImmId>>("ImmIdTFileTarget")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmTextSeparator>, emscripten::base<org::imm::ImmId>>("ImmIdTTextSeparator")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmDocumentGroup>, emscripten::base<org::imm::ImmId>>("ImmIdTDocumentGroup")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmFile>, emscripten::base<org::imm::ImmId>>("ImmIdTFile")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmDirectory>, emscripten::base<org::imm::ImmId>>("ImmIdTDirectory")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmSymlink>, emscripten::base<org::imm::ImmId>>("ImmIdTSymlink")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCmdInclude>, emscripten::base<org::imm::ImmId>>("ImmIdTCmdInclude")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmNone, emscripten::base<org::imm::ImmOrg>>("ImmNone")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmNone::*)() const>(&org::imm::ImmNone::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmNone::*)(org::imm::ImmNone const&) const>(&org::imm::ImmNone::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmErrorItem, emscripten::base<org::imm::ImmOrg>>("ImmErrorItem")
    .property("message", &org::imm::ImmErrorItem::message)
    .property("function", &org::imm::ImmErrorItem::function)
    .property("line", &org::imm::ImmErrorItem::line)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmErrorItem::*)() const>(&org::imm::ImmErrorItem::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmErrorItem::*)(org::imm::ImmErrorItem const&) const>(&org::imm::ImmErrorItem::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmErrorGroup, emscripten::base<org::imm::ImmOrg>>("ImmErrorGroup")
    .property("diagnostics", &org::imm::ImmErrorGroup::diagnostics)
    .property("function", &org::imm::ImmErrorGroup::function)
    .property("line", &org::imm::ImmErrorGroup::line)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmErrorGroup::*)() const>(&org::imm::ImmErrorGroup::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmErrorGroup::*)(org::imm::ImmErrorGroup const&) const>(&org::imm::ImmErrorGroup::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmStmt, emscripten::base<org::imm::ImmOrg>>("ImmStmt")
    .property("attached", &org::imm::ImmStmt::attached)
    .function("__eq__", static_cast<bool(org::imm::ImmStmt::*)(org::imm::ImmStmt const&) const>(&org::imm::ImmStmt::operator==))
    ;
  emscripten::class_<org::imm::ImmInline, emscripten::base<org::imm::ImmOrg>>("ImmInline")
    .function("__eq__", static_cast<bool(org::imm::ImmInline::*)(org::imm::ImmInline const&) const>(&org::imm::ImmInline::operator==))
    ;
  emscripten::class_<org::imm::ImmStmtList, emscripten::base<org::imm::ImmOrg>>("ImmStmtList")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmStmtList::*)() const>(&org::imm::ImmStmtList::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmStmtList::*)(org::imm::ImmStmtList const&) const>(&org::imm::ImmStmtList::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmEmpty, emscripten::base<org::imm::ImmOrg>>("ImmEmpty")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmEmpty::*)() const>(&org::imm::ImmEmpty::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmEmpty::*)(org::imm::ImmEmpty const&) const>(&org::imm::ImmEmpty::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmLeaf, emscripten::base<org::imm::ImmOrg>>("ImmLeaf")
    .property("text", &org::imm::ImmLeaf::text)
    .function("__eq__", static_cast<bool(org::imm::ImmLeaf::*)(org::imm::ImmLeaf const&) const>(&org::imm::ImmLeaf::operator==))
    ;
  emscripten::class_<org::imm::ImmTime, emscripten::base<org::imm::ImmOrg>>("ImmTime")
    .property("isActive", &org::imm::ImmTime::isActive)
    .property("time", &org::imm::ImmTime::time)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmTime::*)() const>(&org::imm::ImmTime::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmTime::*)(org::imm::ImmTime const&) const>(&org::imm::ImmTime::operator==))
    .function("isStatic", static_cast<bool(org::imm::ImmTime::*)() const>(&org::imm::ImmTime::isStatic))
    .function("getStaticConst", static_cast<org::imm::ImmTime::Static const&(org::imm::ImmTime::*)() const>(&org::imm::ImmTime::getStatic))
    .function("getStaticMut", static_cast<org::imm::ImmTime::Static&(org::imm::ImmTime::*)()>(&org::imm::ImmTime::getStatic))
    .function("isDynamic", static_cast<bool(org::imm::ImmTime::*)() const>(&org::imm::ImmTime::isDynamic))
    .function("getDynamicConst", static_cast<org::imm::ImmTime::Dynamic const&(org::imm::ImmTime::*)() const>(&org::imm::ImmTime::getDynamic))
    .function("getDynamicMut", static_cast<org::imm::ImmTime::Dynamic&(org::imm::ImmTime::*)()>(&org::imm::ImmTime::getDynamic))
    .class_function("getTimeKindStatic", static_cast<org::imm::ImmTime::TimeKind(*)(org::imm::ImmTime::TimeVariant const&)>(&org::imm::ImmTime::getTimeKind))
    .function("getTimeKind", static_cast<org::imm::ImmTime::TimeKind(org::imm::ImmTime::*)() const>(&org::imm::ImmTime::getTimeKind))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmTime::Repeat>("ImmTimeRepeat")
    .property("mode", &org::imm::ImmTime::Repeat::mode)
    .property("period", &org::imm::ImmTime::Repeat::period)
    .property("count", &org::imm::ImmTime::Repeat::count)
    .function("__eq__", static_cast<bool(org::imm::ImmTime::Repeat::*)(org::imm::ImmTime::Repeat const&) const>(&org::imm::ImmTime::Repeat::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::imm::ImmTime::Repeat::Mode>("OrgImmImmTimeRepeatMode");
  org::bind::js::bind_enum<org::imm::ImmTime::Repeat::Period>("OrgImmImmTimeRepeatPeriod");
  emscripten::class_<org::imm::ImmTime::Static>("ImmTimeStatic")
    .property("repeat", &org::imm::ImmTime::Static::repeat)
    .property("warn", &org::imm::ImmTime::Static::warn)
    .property("time", &org::imm::ImmTime::Static::time)
    .function("__eq__", static_cast<bool(org::imm::ImmTime::Static::*)(org::imm::ImmTime::Static const&) const>(&org::imm::ImmTime::Static::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmTime::Dynamic>("ImmTimeDynamic")
    .property("expr", &org::imm::ImmTime::Dynamic::expr)
    .function("__eq__", static_cast<bool(org::imm::ImmTime::Dynamic::*)(org::imm::ImmTime::Dynamic const&) const>(&org::imm::ImmTime::Dynamic::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::imm::ImmTime::TimeKind>("OrgImmImmTimeTimeKind");
  emscripten::class_<org::imm::ImmTimeRange, emscripten::base<org::imm::ImmOrg>>("ImmTimeRange")
    .property("from", &org::imm::ImmTimeRange::from)
    .property("to", &org::imm::ImmTimeRange::to)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmTimeRange::*)() const>(&org::imm::ImmTimeRange::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmTimeRange::*)(org::imm::ImmTimeRange const&) const>(&org::imm::ImmTimeRange::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmMacro, emscripten::base<org::imm::ImmOrg>>("ImmMacro")
    .property("name", &org::imm::ImmMacro::name)
    .property("attrs", &org::imm::ImmMacro::attrs)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmMacro::*)() const>(&org::imm::ImmMacro::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmMacro::*)(org::imm::ImmMacro const&) const>(&org::imm::ImmMacro::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmSymbol, emscripten::base<org::imm::ImmOrg>>("ImmSymbol")
    .property("name", &org::imm::ImmSymbol::name)
    .property("parameters", &org::imm::ImmSymbol::parameters)
    .property("positional", &org::imm::ImmSymbol::positional)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmSymbol::*)() const>(&org::imm::ImmSymbol::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmSymbol::*)(org::imm::ImmSymbol const&) const>(&org::imm::ImmSymbol::operator==))
    .constructor<>()
    ;
}

void subdivide_5(org::bind::js::type_registration_guard& g) {
  emscripten::class_<org::imm::ImmSymbol::Param>("ImmSymbolParam")
    .property("key", &org::imm::ImmSymbol::Param::key)
    .property("value", &org::imm::ImmSymbol::Param::value)
    .function("__eq__", static_cast<bool(org::imm::ImmSymbol::Param::*)(org::imm::ImmSymbol::Param const&) const>(&org::imm::ImmSymbol::Param::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmMarkup, emscripten::base<org::imm::ImmOrg>>("ImmMarkup")
    .function("__eq__", static_cast<bool(org::imm::ImmMarkup::*)(org::imm::ImmMarkup const&) const>(&org::imm::ImmMarkup::operator==))
    ;
  emscripten::class_<org::imm::ImmRadioTarget, emscripten::base<org::imm::ImmOrg>>("ImmRadioTarget")
    .property("words", &org::imm::ImmRadioTarget::words)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmRadioTarget::*)() const>(&org::imm::ImmRadioTarget::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmRadioTarget::*)(org::imm::ImmRadioTarget const&) const>(&org::imm::ImmRadioTarget::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmLatex, emscripten::base<org::imm::ImmOrg>>("ImmLatex")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmLatex::*)() const>(&org::imm::ImmLatex::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmLatex::*)(org::imm::ImmLatex const&) const>(&org::imm::ImmLatex::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmSubtreeLog, emscripten::base<org::imm::ImmOrg>>("ImmSubtreeLog")
    .property("head", &org::imm::ImmSubtreeLog::head)
    .property("desc", &org::imm::ImmSubtreeLog::desc)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmSubtreeLog::*)() const>(&org::imm::ImmSubtreeLog::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmSubtreeLog::*)(org::imm::ImmSubtreeLog const&) const>(&org::imm::ImmSubtreeLog::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmSubtree, emscripten::base<org::imm::ImmOrg>>("ImmSubtree")
    .property("level", &org::imm::ImmSubtree::level)
    .property("treeId", &org::imm::ImmSubtree::treeId)
    .property("todo", &org::imm::ImmSubtree::todo)
    .property("completion", &org::imm::ImmSubtree::completion)
    .property("description", &org::imm::ImmSubtree::description)
    .property("tags", &org::imm::ImmSubtree::tags)
    .property("title", &org::imm::ImmSubtree::title)
    .property("logbook", &org::imm::ImmSubtree::logbook)
    .property("properties", &org::imm::ImmSubtree::properties)
    .property("closed", &org::imm::ImmSubtree::closed)
    .property("deadline", &org::imm::ImmSubtree::deadline)
    .property("scheduled", &org::imm::ImmSubtree::scheduled)
    .property("isComment", &org::imm::ImmSubtree::isComment)
    .property("isArchived", &org::imm::ImmSubtree::isArchived)
    .property("priority", &org::imm::ImmSubtree::priority)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmSubtree::*)() const>(&org::imm::ImmSubtree::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmSubtree::*)(org::imm::ImmSubtree const&) const>(&org::imm::ImmSubtree::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmColonExample, emscripten::base<org::imm::ImmOrg>>("ImmColonExample")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmColonExample::*)() const>(&org::imm::ImmColonExample::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmColonExample::*)(org::imm::ImmColonExample const&) const>(&org::imm::ImmColonExample::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCall, emscripten::base<org::imm::ImmOrg>>("ImmCall")
    .property("name", &org::imm::ImmCall::name)
    .property("attrs", &org::imm::ImmCall::attrs)
    .property("isCommand", &org::imm::ImmCall::isCommand)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmCall::*)() const>(&org::imm::ImmCall::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCall::*)(org::imm::ImmCall const&) const>(&org::imm::ImmCall::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmListItem, emscripten::base<org::imm::ImmOrg>>("ImmListItem")
    .property("checkbox", &org::imm::ImmListItem::checkbox)
    .property("header", &org::imm::ImmListItem::header)
    .property("bullet", &org::imm::ImmListItem::bullet)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmListItem::*)() const>(&org::imm::ImmListItem::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmListItem::*)(org::imm::ImmListItem const&) const>(&org::imm::ImmListItem::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmDocumentOptions, emscripten::base<org::imm::ImmOrg>>("ImmDocumentOptions")
    .property("initialVisibility", &org::imm::ImmDocumentOptions::initialVisibility)
    .property("properties", &org::imm::ImmDocumentOptions::properties)
    .property("exportConfig", &org::imm::ImmDocumentOptions::exportConfig)
    .property("fixedWidthSections", &org::imm::ImmDocumentOptions::fixedWidthSections)
    .property("startupIndented", &org::imm::ImmDocumentOptions::startupIndented)
    .property("category", &org::imm::ImmDocumentOptions::category)
    .property("setupfile", &org::imm::ImmDocumentOptions::setupfile)
    .property("maxSubtreeLevelExport", &org::imm::ImmDocumentOptions::maxSubtreeLevelExport)
    .property("columns", &org::imm::ImmDocumentOptions::columns)
    .property("todoKeywords", &org::imm::ImmDocumentOptions::todoKeywords)
    .property("doneKeywords", &org::imm::ImmDocumentOptions::doneKeywords)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmDocumentOptions::*)() const>(&org::imm::ImmDocumentOptions::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmDocumentOptions::*)(org::imm::ImmDocumentOptions const&) const>(&org::imm::ImmDocumentOptions::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmDocumentFragment, emscripten::base<org::imm::ImmOrg>>("ImmDocumentFragment")
    .property("baseLine", &org::imm::ImmDocumentFragment::baseLine)
    .property("baseCol", &org::imm::ImmDocumentFragment::baseCol)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmDocumentFragment::*)() const>(&org::imm::ImmDocumentFragment::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmDocumentFragment::*)(org::imm::ImmDocumentFragment const&) const>(&org::imm::ImmDocumentFragment::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCriticMarkup, emscripten::base<org::imm::ImmOrg>>("ImmCriticMarkup")
    .property("kind", &org::imm::ImmCriticMarkup::kind)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmCriticMarkup::*)() const>(&org::imm::ImmCriticMarkup::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCriticMarkup::*)(org::imm::ImmCriticMarkup const&) const>(&org::imm::ImmCriticMarkup::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::imm::ImmCriticMarkup::Kind>("OrgImmImmCriticMarkupKind");
  emscripten::class_<org::imm::ImmDocument, emscripten::base<org::imm::ImmOrg>>("ImmDocument")
    .property("title", &org::imm::ImmDocument::title)
    .property("author", &org::imm::ImmDocument::author)
    .property("creator", &org::imm::ImmDocument::creator)
    .property("filetags", &org::imm::ImmDocument::filetags)
    .property("email", &org::imm::ImmDocument::email)
    .property("language", &org::imm::ImmDocument::language)
    .property("options", &org::imm::ImmDocument::options)
    .property("exportFileName", &org::imm::ImmDocument::exportFileName)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmDocument::*)() const>(&org::imm::ImmDocument::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmDocument::*)(org::imm::ImmDocument const&) const>(&org::imm::ImmDocument::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmFileTarget, emscripten::base<org::imm::ImmOrg>>("ImmFileTarget")
    .property("path", &org::imm::ImmFileTarget::path)
    .property("line", &org::imm::ImmFileTarget::line)
    .property("searchTarget", &org::imm::ImmFileTarget::searchTarget)
    .property("restrictToHeadlines", &org::imm::ImmFileTarget::restrictToHeadlines)
    .property("targetId", &org::imm::ImmFileTarget::targetId)
    .property("regexp", &org::imm::ImmFileTarget::regexp)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmFileTarget::*)() const>(&org::imm::ImmFileTarget::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmFileTarget::*)(org::imm::ImmFileTarget const&) const>(&org::imm::ImmFileTarget::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmTextSeparator, emscripten::base<org::imm::ImmOrg>>("ImmTextSeparator")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmTextSeparator::*)() const>(&org::imm::ImmTextSeparator::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmTextSeparator::*)(org::imm::ImmTextSeparator const&) const>(&org::imm::ImmTextSeparator::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmDocumentGroup, emscripten::base<org::imm::ImmOrg>>("ImmDocumentGroup")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmDocumentGroup::*)() const>(&org::imm::ImmDocumentGroup::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmDocumentGroup::*)(org::imm::ImmDocumentGroup const&) const>(&org::imm::ImmDocumentGroup::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmFile, emscripten::base<org::imm::ImmOrg>>("ImmFile")
    .property("relPath", &org::imm::ImmFile::relPath)
    .property("absPath", &org::imm::ImmFile::absPath)
    .property("data", &org::imm::ImmFile::data)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmFile::*)() const>(&org::imm::ImmFile::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmFile::*)(org::imm::ImmFile const&) const>(&org::imm::ImmFile::operator==))
    .function("isDocument", static_cast<bool(org::imm::ImmFile::*)() const>(&org::imm::ImmFile::isDocument))
    .function("getDocumentConst", static_cast<org::imm::ImmFile::Document const&(org::imm::ImmFile::*)() const>(&org::imm::ImmFile::getDocument))
    .function("getDocumentMut", static_cast<org::imm::ImmFile::Document&(org::imm::ImmFile::*)()>(&org::imm::ImmFile::getDocument))
    .function("isAttachment", static_cast<bool(org::imm::ImmFile::*)() const>(&org::imm::ImmFile::isAttachment))
    .function("getAttachmentConst", static_cast<org::imm::ImmFile::Attachment const&(org::imm::ImmFile::*)() const>(&org::imm::ImmFile::getAttachment))
    .function("getAttachmentMut", static_cast<org::imm::ImmFile::Attachment&(org::imm::ImmFile::*)()>(&org::imm::ImmFile::getAttachment))
    .function("isSource", static_cast<bool(org::imm::ImmFile::*)() const>(&org::imm::ImmFile::isSource))
    .function("getSourceConst", static_cast<org::imm::ImmFile::Source const&(org::imm::ImmFile::*)() const>(&org::imm::ImmFile::getSource))
    .function("getSourceMut", static_cast<org::imm::ImmFile::Source&(org::imm::ImmFile::*)()>(&org::imm::ImmFile::getSource))
    .class_function("getFileKindStatic", static_cast<org::imm::ImmFile::Kind(*)(org::imm::ImmFile::Data const&)>(&org::imm::ImmFile::getFileKind))
    .function("getFileKind", static_cast<org::imm::ImmFile::Kind(org::imm::ImmFile::*)() const>(&org::imm::ImmFile::getFileKind))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmFile::Document>("ImmFileDocument")
    .function("__eq__", static_cast<bool(org::imm::ImmFile::Document::*)(org::imm::ImmFile::Document const&) const>(&org::imm::ImmFile::Document::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmFile::Attachment>("ImmFileAttachment")
    .function("__eq__", static_cast<bool(org::imm::ImmFile::Attachment::*)(org::imm::ImmFile::Attachment const&) const>(&org::imm::ImmFile::Attachment::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmFile::Source>("ImmFileSource")
    .function("__eq__", static_cast<bool(org::imm::ImmFile::Source::*)(org::imm::ImmFile::Source const&) const>(&org::imm::ImmFile::Source::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::imm::ImmFile::Kind>("OrgImmImmFileKind");
  emscripten::class_<org::imm::ImmDirectory, emscripten::base<org::imm::ImmOrg>>("ImmDirectory")
    .property("relPath", &org::imm::ImmDirectory::relPath)
    .property("absPath", &org::imm::ImmDirectory::absPath)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmDirectory::*)() const>(&org::imm::ImmDirectory::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmDirectory::*)(org::imm::ImmDirectory const&) const>(&org::imm::ImmDirectory::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmSymlink, emscripten::base<org::imm::ImmOrg>>("ImmSymlink")
    .property("isDirectory", &org::imm::ImmSymlink::isDirectory)
    .property("absPath", &org::imm::ImmSymlink::absPath)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmSymlink::*)() const>(&org::imm::ImmSymlink::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmSymlink::*)(org::imm::ImmSymlink const&) const>(&org::imm::ImmSymlink::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdInclude, emscripten::base<org::imm::ImmOrg>>("ImmCmdInclude")
    .property("path", &org::imm::ImmCmdInclude::path)
    .property("firstLine", &org::imm::ImmCmdInclude::firstLine)
    .property("lastLine", &org::imm::ImmCmdInclude::lastLine)
    .property("data", &org::imm::ImmCmdInclude::data)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCmdInclude::*)(org::imm::ImmCmdInclude const&) const>(&org::imm::ImmCmdInclude::operator==))
    .function("isExample", static_cast<bool(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::isExample))
    .function("getExampleConst", static_cast<org::imm::ImmCmdInclude::Example const&(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::getExample))
    .function("getExampleMut", static_cast<org::imm::ImmCmdInclude::Example&(org::imm::ImmCmdInclude::*)()>(&org::imm::ImmCmdInclude::getExample))
    .function("isExport", static_cast<bool(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::isExport))
    .function("getExportConst", static_cast<org::imm::ImmCmdInclude::Export const&(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::getExport))
    .function("getExportMut", static_cast<org::imm::ImmCmdInclude::Export&(org::imm::ImmCmdInclude::*)()>(&org::imm::ImmCmdInclude::getExport))
    .function("isCustom", static_cast<bool(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::isCustom))
    .function("getCustomConst", static_cast<org::imm::ImmCmdInclude::Custom const&(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::getCustom))
    .function("getCustomMut", static_cast<org::imm::ImmCmdInclude::Custom&(org::imm::ImmCmdInclude::*)()>(&org::imm::ImmCmdInclude::getCustom))
    .function("isSrc", static_cast<bool(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::isSrc))
    .function("getSrcConst", static_cast<org::imm::ImmCmdInclude::Src const&(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::getSrc))
    .function("getSrcMut", static_cast<org::imm::ImmCmdInclude::Src&(org::imm::ImmCmdInclude::*)()>(&org::imm::ImmCmdInclude::getSrc))
    .function("isOrgDocument", static_cast<bool(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::isOrgDocument))
    .function("getOrgDocumentConst", static_cast<org::imm::ImmCmdInclude::OrgDocument const&(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::getOrgDocument))
    .function("getOrgDocumentMut", static_cast<org::imm::ImmCmdInclude::OrgDocument&(org::imm::ImmCmdInclude::*)()>(&org::imm::ImmCmdInclude::getOrgDocument))
    .class_function("getIncludeKindStatic", static_cast<org::imm::ImmCmdInclude::Kind(*)(org::imm::ImmCmdInclude::Data const&)>(&org::imm::ImmCmdInclude::getIncludeKind))
    .function("getIncludeKind", static_cast<org::imm::ImmCmdInclude::Kind(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::getIncludeKind))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdInclude::IncludeBase>("ImmCmdIncludeIncludeBase")
    .function("__eq__", static_cast<bool(org::imm::ImmCmdInclude::IncludeBase::*)(org::imm::ImmCmdInclude::IncludeBase const&) const>(&org::imm::ImmCmdInclude::IncludeBase::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdInclude::Example, emscripten::base<org::imm::ImmCmdInclude::IncludeBase>>("ImmCmdIncludeExample")
    .function("__eq__", static_cast<bool(org::imm::ImmCmdInclude::Example::*)(org::imm::ImmCmdInclude::Example const&) const>(&org::imm::ImmCmdInclude::Example::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdInclude::Export, emscripten::base<org::imm::ImmCmdInclude::IncludeBase>>("ImmCmdIncludeExport")
    .property("language", &org::imm::ImmCmdInclude::Export::language)
    .function("__eq__", static_cast<bool(org::imm::ImmCmdInclude::Export::*)(org::imm::ImmCmdInclude::Export const&) const>(&org::imm::ImmCmdInclude::Export::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdInclude::Custom, emscripten::base<org::imm::ImmCmdInclude::IncludeBase>>("ImmCmdIncludeCustom")
    .property("blockName", &org::imm::ImmCmdInclude::Custom::blockName)
    .function("__eq__", static_cast<bool(org::imm::ImmCmdInclude::Custom::*)(org::imm::ImmCmdInclude::Custom const&) const>(&org::imm::ImmCmdInclude::Custom::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdInclude::Src, emscripten::base<org::imm::ImmCmdInclude::IncludeBase>>("ImmCmdIncludeSrc")
    .property("language", &org::imm::ImmCmdInclude::Src::language)
    .function("__eq__", static_cast<bool(org::imm::ImmCmdInclude::Src::*)(org::imm::ImmCmdInclude::Src const&) const>(&org::imm::ImmCmdInclude::Src::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdInclude::OrgDocument, emscripten::base<org::imm::ImmCmdInclude::IncludeBase>>("ImmCmdIncludeOrgDocument")
    .property("onlyContent", &org::imm::ImmCmdInclude::OrgDocument::onlyContent)
    .property("subtreePath", &org::imm::ImmCmdInclude::OrgDocument::subtreePath)
    .property("minLevel", &org::imm::ImmCmdInclude::OrgDocument::minLevel)
    .property("customIdTarget", &org::imm::ImmCmdInclude::OrgDocument::customIdTarget)
    .function("__eq__", static_cast<bool(org::imm::ImmCmdInclude::OrgDocument::*)(org::imm::ImmCmdInclude::OrgDocument const&) const>(&org::imm::ImmCmdInclude::OrgDocument::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::imm::ImmCmdInclude::Kind>("OrgImmImmCmdIncludeKind");
  emscripten::class_<org::imm::ImmNoneValue, emscripten::base<org::imm::ImmNoneValueRead>>("ImmNoneValue")
    ;
  emscripten::class_<org::imm::ImmErrorItemValue, emscripten::base<org::imm::ImmErrorItemValueRead>>("ImmErrorItemValue")
    .function("setMessage", static_cast<void(org::imm::ImmErrorItemValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmErrorItemValue::setMessage))
    .function("setFunction", static_cast<void(org::imm::ImmErrorItemValue::*)(immer::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmErrorItemValue::setFunction))
    .function("setLine", static_cast<void(org::imm::ImmErrorItemValue::*)(immer::box<std::optional<int>> const&)>(&org::imm::ImmErrorItemValue::setLine))
    ;
  emscripten::class_<org::imm::ImmErrorGroupValue, emscripten::base<org::imm::ImmErrorGroupValueRead>>("ImmErrorGroupValue")
    .function("setDiagnostics", static_cast<void(org::imm::ImmErrorGroupValue::*)(immer::flex_vector<org::imm::ImmIdT<org::imm::ImmErrorItem>> const&)>(&org::imm::ImmErrorGroupValue::setDiagnostics))
    .function("setFunction", static_cast<void(org::imm::ImmErrorGroupValue::*)(immer::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmErrorGroupValue::setFunction))
    .function("setLine", static_cast<void(org::imm::ImmErrorGroupValue::*)(immer::box<std::optional<int>> const&)>(&org::imm::ImmErrorGroupValue::setLine))
    ;
  emscripten::class_<org::imm::ImmStmtListValue, emscripten::base<org::imm::ImmStmtListValueRead>>("ImmStmtListValue")
    ;
  emscripten::class_<org::imm::ImmEmptyValue, emscripten::base<org::imm::ImmEmptyValueRead>>("ImmEmptyValue")
    ;
  emscripten::class_<org::imm::ImmCmdCaptionValue, emscripten::base<org::imm::ImmCmdCaptionValueRead>>("ImmCmdCaptionValue")
    .function("setText", static_cast<void(org::imm::ImmCmdCaptionValue::*)(org::imm::ImmIdT<org::imm::ImmParagraph> const&)>(&org::imm::ImmCmdCaptionValue::setText))
    ;
  emscripten::class_<org::imm::ImmCmdColumnsValue, emscripten::base<org::imm::ImmCmdColumnsValueRead>>("ImmCmdColumnsValue")
    .function("setView", static_cast<void(org::imm::ImmCmdColumnsValue::*)(org::sem::ColumnView const&)>(&org::imm::ImmCmdColumnsValue::setView))
    ;
  emscripten::class_<org::imm::ImmCmdNameValue, emscripten::base<org::imm::ImmCmdNameValueRead>>("ImmCmdNameValue")
    .function("setName", static_cast<void(org::imm::ImmCmdNameValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmCmdNameValue::setName))
    ;
  emscripten::class_<org::imm::ImmCmdCustomArgsValue, emscripten::base<org::imm::ImmCmdCustomArgsValueRead>>("ImmCmdCustomArgsValue")
    .function("setName", static_cast<void(org::imm::ImmCmdCustomArgsValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmCmdCustomArgsValue::setName))
    .function("setIsattached", static_cast<void(org::imm::ImmCmdCustomArgsValue::*)(bool const&)>(&org::imm::ImmCmdCustomArgsValue::setIsattached))
    ;
  emscripten::class_<org::imm::ImmCmdCustomRawValue, emscripten::base<org::imm::ImmCmdCustomRawValueRead>>("ImmCmdCustomRawValue")
    .function("setName", static_cast<void(org::imm::ImmCmdCustomRawValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmCmdCustomRawValue::setName))
    .function("setIsattached", static_cast<void(org::imm::ImmCmdCustomRawValue::*)(bool const&)>(&org::imm::ImmCmdCustomRawValue::setIsattached))
    .function("setText", static_cast<void(org::imm::ImmCmdCustomRawValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmCmdCustomRawValue::setText))
    ;
  emscripten::class_<org::imm::ImmCmdCustomTextValue, emscripten::base<org::imm::ImmCmdCustomTextValueRead>>("ImmCmdCustomTextValue")
    .function("setName", static_cast<void(org::imm::ImmCmdCustomTextValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmCmdCustomTextValue::setName))
    .function("setIsattached", static_cast<void(org::imm::ImmCmdCustomTextValue::*)(bool const&)>(&org::imm::ImmCmdCustomTextValue::setIsattached))
    .function("setText", static_cast<void(org::imm::ImmCmdCustomTextValue::*)(org::imm::ImmIdT<org::imm::ImmParagraph> const&)>(&org::imm::ImmCmdCustomTextValue::setText))
    ;
  emscripten::class_<org::imm::ImmCmdCallValue, emscripten::base<org::imm::ImmCmdCallValueRead>>("ImmCmdCallValue")
    .function("setName", static_cast<void(org::imm::ImmCmdCallValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmCmdCallValue::setName))
    .function("setFilename", static_cast<void(org::imm::ImmCmdCallValue::*)(immer::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmCmdCallValue::setFilename))
    .function("setInsideheaderattrs", static_cast<void(org::imm::ImmCmdCallValue::*)(org::sem::AttrGroup const&)>(&org::imm::ImmCmdCallValue::setInsideheaderattrs))
    .function("setCallattrs", static_cast<void(org::imm::ImmCmdCallValue::*)(org::sem::AttrGroup const&)>(&org::imm::ImmCmdCallValue::setCallattrs))
    .function("setEndheaderattrs", static_cast<void(org::imm::ImmCmdCallValue::*)(org::sem::AttrGroup const&)>(&org::imm::ImmCmdCallValue::setEndheaderattrs))
    .function("setResult", static_cast<void(org::imm::ImmCmdCallValue::*)(immer::flex_vector<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>> const&)>(&org::imm::ImmCmdCallValue::setResult))
    ;
  emscripten::class_<org::imm::ImmCmdTblfmValue, emscripten::base<org::imm::ImmCmdTblfmValueRead>>("ImmCmdTblfmValue")
    .function("setExpr", static_cast<void(org::imm::ImmCmdTblfmValue::*)(org::sem::Tblfm const&)>(&org::imm::ImmCmdTblfmValue::setExpr))
    ;
  emscripten::class_<org::imm::ImmHashTagValue, emscripten::base<org::imm::ImmHashTagValueRead>>("ImmHashTagValue")
    .function("setText", static_cast<void(org::imm::ImmHashTagValue::*)(org::sem::HashTagText const&)>(&org::imm::ImmHashTagValue::setText))
    ;
  emscripten::class_<org::imm::ImmInlineFootnoteValue, emscripten::base<org::imm::ImmInlineFootnoteValueRead>>("ImmInlineFootnoteValue")
    .function("setTag", static_cast<void(org::imm::ImmInlineFootnoteValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmInlineFootnoteValue::setTag))
    .function("setDefinition", static_cast<void(org::imm::ImmInlineFootnoteValue::*)(immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmOrg>>> const&)>(&org::imm::ImmInlineFootnoteValue::setDefinition))
    ;
  emscripten::class_<org::imm::ImmInlineExportValue, emscripten::base<org::imm::ImmInlineExportValueRead>>("ImmInlineExportValue")
    .function("setExporter", static_cast<void(org::imm::ImmInlineExportValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmInlineExportValue::setExporter))
    .function("setContent", static_cast<void(org::imm::ImmInlineExportValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmInlineExportValue::setContent))
    ;
  emscripten::class_<org::imm::ImmTimeValue, emscripten::base<org::imm::ImmTimeValueRead>>("ImmTimeValue")
    .function("setIsactive", static_cast<void(org::imm::ImmTimeValue::*)(bool const&)>(&org::imm::ImmTimeValue::setIsactive))
    .function("setTime", static_cast<void(org::imm::ImmTimeValue::*)(org::imm::ImmTime::TimeVariant const&)>(&org::imm::ImmTimeValue::setTime))
    ;
  emscripten::class_<org::imm::ImmTimeRangeValue, emscripten::base<org::imm::ImmTimeRangeValueRead>>("ImmTimeRangeValue")
    .function("setFrom", static_cast<void(org::imm::ImmTimeRangeValue::*)(org::imm::ImmIdT<org::imm::ImmTime> const&)>(&org::imm::ImmTimeRangeValue::setFrom))
    .function("setTo", static_cast<void(org::imm::ImmTimeRangeValue::*)(org::imm::ImmIdT<org::imm::ImmTime> const&)>(&org::imm::ImmTimeRangeValue::setTo))
    ;
  emscripten::class_<org::imm::ImmMacroValue, emscripten::base<org::imm::ImmMacroValueRead>>("ImmMacroValue")
    .function("setName", static_cast<void(org::imm::ImmMacroValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmMacroValue::setName))
    .function("setAttrs", static_cast<void(org::imm::ImmMacroValue::*)(org::sem::AttrGroup const&)>(&org::imm::ImmMacroValue::setAttrs))
    ;
  emscripten::class_<org::imm::ImmSymbolValue, emscripten::base<org::imm::ImmSymbolValueRead>>("ImmSymbolValue")
    .function("setName", static_cast<void(org::imm::ImmSymbolValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmSymbolValue::setName))
    .function("setParameters", static_cast<void(org::imm::ImmSymbolValue::*)(immer::flex_vector<org::imm::ImmSymbol::Param> const&)>(&org::imm::ImmSymbolValue::setParameters))
    .function("setPositional", static_cast<void(org::imm::ImmSymbolValue::*)(immer::flex_vector<org::imm::ImmIdT<org::imm::ImmOrg>> const&)>(&org::imm::ImmSymbolValue::setPositional))
    ;
  emscripten::class_<org::imm::ImmEscapedValue, emscripten::base<org::imm::ImmEscapedValueRead>>("ImmEscapedValue")
    ;
  emscripten::class_<org::imm::ImmNewlineValue, emscripten::base<org::imm::ImmNewlineValueRead>>("ImmNewlineValue")
    ;
  emscripten::class_<org::imm::ImmSpaceValue, emscripten::base<org::imm::ImmSpaceValueRead>>("ImmSpaceValue")
    ;
  emscripten::class_<org::imm::ImmWordValue, emscripten::base<org::imm::ImmWordValueRead>>("ImmWordValue")
    ;
  emscripten::class_<org::imm::ImmAtMentionValue, emscripten::base<org::imm::ImmAtMentionValueRead>>("ImmAtMentionValue")
    ;
  emscripten::class_<org::imm::ImmRawTextValue, emscripten::base<org::imm::ImmRawTextValueRead>>("ImmRawTextValue")
    ;
  emscripten::class_<org::imm::ImmPunctuationValue, emscripten::base<org::imm::ImmPunctuationValueRead>>("ImmPunctuationValue")
    ;
  emscripten::class_<org::imm::ImmPlaceholderValue, emscripten::base<org::imm::ImmPlaceholderValueRead>>("ImmPlaceholderValue")
    ;
  emscripten::class_<org::imm::ImmBigIdentValue, emscripten::base<org::imm::ImmBigIdentValueRead>>("ImmBigIdentValue")
    ;
  emscripten::class_<org::imm::ImmTextTargetValue, emscripten::base<org::imm::ImmTextTargetValueRead>>("ImmTextTargetValue")
    ;
  emscripten::class_<org::imm::ImmBoldValue, emscripten::base<org::imm::ImmBoldValueRead>>("ImmBoldValue")
    ;
  emscripten::class_<org::imm::ImmUnderlineValue, emscripten::base<org::imm::ImmUnderlineValueRead>>("ImmUnderlineValue")
    ;
  emscripten::class_<org::imm::ImmMonospaceValue, emscripten::base<org::imm::ImmMonospaceValueRead>>("ImmMonospaceValue")
    ;
  emscripten::class_<org::imm::ImmMarkQuoteValue, emscripten::base<org::imm::ImmMarkQuoteValueRead>>("ImmMarkQuoteValue")
    ;
  emscripten::class_<org::imm::ImmVerbatimValue, emscripten::base<org::imm::ImmVerbatimValueRead>>("ImmVerbatimValue")
    ;
  emscripten::class_<org::imm::ImmItalicValue, emscripten::base<org::imm::ImmItalicValueRead>>("ImmItalicValue")
    ;
  emscripten::class_<org::imm::ImmStrikeValue, emscripten::base<org::imm::ImmStrikeValueRead>>("ImmStrikeValue")
    ;
  emscripten::class_<org::imm::ImmParValue, emscripten::base<org::imm::ImmParValueRead>>("ImmParValue")
    ;
  emscripten::class_<org::imm::ImmRadioTargetValue, emscripten::base<org::imm::ImmRadioTargetValueRead>>("ImmRadioTargetValue")
    .function("setWords", static_cast<void(org::imm::ImmRadioTargetValue::*)(immer::flex_vector<hstd::Str> const&)>(&org::imm::ImmRadioTargetValue::setWords))
    ;
  emscripten::class_<org::imm::ImmLatexValue, emscripten::base<org::imm::ImmLatexValueRead>>("ImmLatexValue")
    ;
  emscripten::class_<org::imm::ImmLinkValue, emscripten::base<org::imm::ImmLinkValueRead>>("ImmLinkValue")
    .function("setDescription", static_cast<void(org::imm::ImmLinkValue::*)(immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&)>(&org::imm::ImmLinkValue::setDescription))
    .function("setTarget", static_cast<void(org::imm::ImmLinkValue::*)(org::sem::LinkTarget const&)>(&org::imm::ImmLinkValue::setTarget))
    ;
  emscripten::class_<org::imm::ImmBlockCenterValue, emscripten::base<org::imm::ImmBlockCenterValueRead>>("ImmBlockCenterValue")
    ;
  emscripten::class_<org::imm::ImmBlockQuoteValue, emscripten::base<org::imm::ImmBlockQuoteValueRead>>("ImmBlockQuoteValue")
    ;
  emscripten::class_<org::imm::ImmBlockCommentValue, emscripten::base<org::imm::ImmBlockCommentValueRead>>("ImmBlockCommentValue")
    ;
  emscripten::class_<org::imm::ImmBlockVerseValue, emscripten::base<org::imm::ImmBlockVerseValueRead>>("ImmBlockVerseValue")
    ;
  emscripten::class_<org::imm::ImmBlockDynamicFallbackValue, emscripten::base<org::imm::ImmBlockDynamicFallbackValueRead>>("ImmBlockDynamicFallbackValue")
    .function("setName", static_cast<void(org::imm::ImmBlockDynamicFallbackValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmBlockDynamicFallbackValue::setName))
    ;
  emscripten::class_<org::imm::ImmBlockExampleValue, emscripten::base<org::imm::ImmBlockExampleValueRead>>("ImmBlockExampleValue")
    ;
  emscripten::class_<org::imm::ImmBlockExportValue, emscripten::base<org::imm::ImmBlockExportValueRead>>("ImmBlockExportValue")
    .function("setExporter", static_cast<void(org::imm::ImmBlockExportValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmBlockExportValue::setExporter))
    .function("setContent", static_cast<void(org::imm::ImmBlockExportValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmBlockExportValue::setContent))
    ;
  emscripten::class_<org::imm::ImmBlockAdmonitionValue, emscripten::base<org::imm::ImmBlockAdmonitionValueRead>>("ImmBlockAdmonitionValue")
    ;
  emscripten::class_<org::imm::ImmBlockCodeEvalResultValue, emscripten::base<org::imm::ImmBlockCodeEvalResultValueRead>>("ImmBlockCodeEvalResultValue")
    .function("setRaw", static_cast<void(org::imm::ImmBlockCodeEvalResultValue::*)(immer::flex_vector<org::sem::OrgCodeEvalOutput> const&)>(&org::imm::ImmBlockCodeEvalResultValue::setRaw))
    .function("setNode", static_cast<void(org::imm::ImmBlockCodeEvalResultValue::*)(org::imm::ImmIdT<org::imm::ImmOrg> const&)>(&org::imm::ImmBlockCodeEvalResultValue::setNode))
    ;
  emscripten::class_<org::imm::ImmBlockCodeValue, emscripten::base<org::imm::ImmBlockCodeValueRead>>("ImmBlockCodeValue")
    .function("setLang", static_cast<void(org::imm::ImmBlockCodeValue::*)(immer::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmBlockCodeValue::setLang))
    .function("setExports", static_cast<void(org::imm::ImmBlockCodeValue::*)(BlockCodeExports const&)>(&org::imm::ImmBlockCodeValue::setExports))
    .function("setResult", static_cast<void(org::imm::ImmBlockCodeValue::*)(immer::flex_vector<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>> const&)>(&org::imm::ImmBlockCodeValue::setResult))
    .function("setLines", static_cast<void(org::imm::ImmBlockCodeValue::*)(immer::flex_vector<org::sem::BlockCodeLine> const&)>(&org::imm::ImmBlockCodeValue::setLines))
    .function("setCache", static_cast<void(org::imm::ImmBlockCodeValue::*)(bool const&)>(&org::imm::ImmBlockCodeValue::setCache))
    .function("setEval", static_cast<void(org::imm::ImmBlockCodeValue::*)(bool const&)>(&org::imm::ImmBlockCodeValue::setEval))
    .function("setNoweb", static_cast<void(org::imm::ImmBlockCodeValue::*)(bool const&)>(&org::imm::ImmBlockCodeValue::setNoweb))
    .function("setHlines", static_cast<void(org::imm::ImmBlockCodeValue::*)(bool const&)>(&org::imm::ImmBlockCodeValue::setHlines))
    .function("setTangle", static_cast<void(org::imm::ImmBlockCodeValue::*)(bool const&)>(&org::imm::ImmBlockCodeValue::setTangle))
    .function("setSwitches", static_cast<void(org::imm::ImmBlockCodeValue::*)(org::sem::AttrGroup const&)>(&org::imm::ImmBlockCodeValue::setSwitches))
    ;
  emscripten::class_<org::imm::ImmSubtreeLogValue, emscripten::base<org::imm::ImmSubtreeLogValueRead>>("ImmSubtreeLogValue")
    .function("setHead", static_cast<void(org::imm::ImmSubtreeLogValue::*)(org::sem::SubtreeLogHead const&)>(&org::imm::ImmSubtreeLogValue::setHead))
    .function("setDesc", static_cast<void(org::imm::ImmSubtreeLogValue::*)(immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmStmtList>>> const&)>(&org::imm::ImmSubtreeLogValue::setDesc))
    ;
  emscripten::class_<org::imm::ImmSubtreeValue, emscripten::base<org::imm::ImmSubtreeValueRead>>("ImmSubtreeValue")
    .function("setLevel", static_cast<void(org::imm::ImmSubtreeValue::*)(int const&)>(&org::imm::ImmSubtreeValue::setLevel))
    .function("setTreeid", static_cast<void(org::imm::ImmSubtreeValue::*)(immer::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmSubtreeValue::setTreeid))
    .function("setTodo", static_cast<void(org::imm::ImmSubtreeValue::*)(immer::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmSubtreeValue::setTodo))
    .function("setCompletion", static_cast<void(org::imm::ImmSubtreeValue::*)(immer::box<std::optional<org::sem::SubtreeCompletion>> const&)>(&org::imm::ImmSubtreeValue::setCompletion))
    .function("setDescription", static_cast<void(org::imm::ImmSubtreeValue::*)(immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&)>(&org::imm::ImmSubtreeValue::setDescription))
    .function("setTags", static_cast<void(org::imm::ImmSubtreeValue::*)(immer::flex_vector<org::imm::ImmIdT<org::imm::ImmHashTag>> const&)>(&org::imm::ImmSubtreeValue::setTags))
    .function("setTitle", static_cast<void(org::imm::ImmSubtreeValue::*)(org::imm::ImmIdT<org::imm::ImmParagraph> const&)>(&org::imm::ImmSubtreeValue::setTitle))
    .function("setLogbook", static_cast<void(org::imm::ImmSubtreeValue::*)(immer::flex_vector<org::imm::ImmIdT<org::imm::ImmSubtreeLog>> const&)>(&org::imm::ImmSubtreeValue::setLogbook))
    .function("setProperties", static_cast<void(org::imm::ImmSubtreeValue::*)(immer::flex_vector<org::sem::NamedProperty> const&)>(&org::imm::ImmSubtreeValue::setProperties))
    .function("setClosed", static_cast<void(org::imm::ImmSubtreeValue::*)(immer::box<std::optional<hstd::UserTime>> const&)>(&org::imm::ImmSubtreeValue::setClosed))
    .function("setDeadline", static_cast<void(org::imm::ImmSubtreeValue::*)(immer::box<std::optional<hstd::UserTime>> const&)>(&org::imm::ImmSubtreeValue::setDeadline))
    .function("setScheduled", static_cast<void(org::imm::ImmSubtreeValue::*)(immer::box<std::optional<hstd::UserTime>> const&)>(&org::imm::ImmSubtreeValue::setScheduled))
    .function("setIscomment", static_cast<void(org::imm::ImmSubtreeValue::*)(bool const&)>(&org::imm::ImmSubtreeValue::setIscomment))
    .function("setIsarchived", static_cast<void(org::imm::ImmSubtreeValue::*)(bool const&)>(&org::imm::ImmSubtreeValue::setIsarchived))
    .function("setPriority", static_cast<void(org::imm::ImmSubtreeValue::*)(immer::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmSubtreeValue::setPriority))
    ;
  emscripten::class_<org::imm::ImmCellValue, emscripten::base<org::imm::ImmCellValueRead>>("ImmCellValue")
    .function("setIsblock", static_cast<void(org::imm::ImmCellValue::*)(bool const&)>(&org::imm::ImmCellValue::setIsblock))
    ;
  emscripten::class_<org::imm::ImmRowValue, emscripten::base<org::imm::ImmRowValueRead>>("ImmRowValue")
    .function("setCells", static_cast<void(org::imm::ImmRowValue::*)(immer::flex_vector<org::imm::ImmIdT<org::imm::ImmCell>> const&)>(&org::imm::ImmRowValue::setCells))
    .function("setIsblock", static_cast<void(org::imm::ImmRowValue::*)(bool const&)>(&org::imm::ImmRowValue::setIsblock))
    ;
  emscripten::class_<org::imm::ImmTableValue, emscripten::base<org::imm::ImmTableValueRead>>("ImmTableValue")
    .function("setRows", static_cast<void(org::imm::ImmTableValue::*)(immer::flex_vector<org::imm::ImmIdT<org::imm::ImmRow>> const&)>(&org::imm::ImmTableValue::setRows))
    .function("setIsblock", static_cast<void(org::imm::ImmTableValue::*)(bool const&)>(&org::imm::ImmTableValue::setIsblock))
    ;
  emscripten::class_<org::imm::ImmParagraphValue, emscripten::base<org::imm::ImmParagraphValueRead>>("ImmParagraphValue")
    ;
  emscripten::class_<org::imm::ImmColonExampleValue, emscripten::base<org::imm::ImmColonExampleValueRead>>("ImmColonExampleValue")
    ;
  emscripten::class_<org::imm::ImmCmdAttrValue, emscripten::base<org::imm::ImmCmdAttrValueRead>>("ImmCmdAttrValue")
    .function("setTarget", static_cast<void(org::imm::ImmCmdAttrValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmCmdAttrValue::setTarget))
    ;
  emscripten::class_<org::imm::ImmCmdExportValue, emscripten::base<org::imm::ImmCmdExportValueRead>>("ImmCmdExportValue")
    .function("setExporter", static_cast<void(org::imm::ImmCmdExportValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmCmdExportValue::setExporter))
    .function("setContent", static_cast<void(org::imm::ImmCmdExportValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmCmdExportValue::setContent))
    ;
  emscripten::class_<org::imm::ImmCallValue, emscripten::base<org::imm::ImmCallValueRead>>("ImmCallValue")
    .function("setName", static_cast<void(org::imm::ImmCallValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmCallValue::setName))
    .function("setAttrs", static_cast<void(org::imm::ImmCallValue::*)(org::sem::AttrGroup const&)>(&org::imm::ImmCallValue::setAttrs))
    .function("setIscommand", static_cast<void(org::imm::ImmCallValue::*)(bool const&)>(&org::imm::ImmCallValue::setIscommand))
    ;
  emscripten::class_<org::imm::ImmListValue, emscripten::base<org::imm::ImmListValueRead>>("ImmListValue")
    ;
  emscripten::class_<org::imm::ImmListItemValue, emscripten::base<org::imm::ImmListItemValueRead>>("ImmListItemValue")
    .function("setCheckbox", static_cast<void(org::imm::ImmListItemValue::*)(CheckboxState const&)>(&org::imm::ImmListItemValue::setCheckbox))
    .function("setHeader", static_cast<void(org::imm::ImmListItemValue::*)(immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&)>(&org::imm::ImmListItemValue::setHeader))
    .function("setBullet", static_cast<void(org::imm::ImmListItemValue::*)(immer::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmListItemValue::setBullet))
    ;
  emscripten::class_<org::imm::ImmDocumentOptionsValue, emscripten::base<org::imm::ImmDocumentOptionsValueRead>>("ImmDocumentOptionsValue")
    .function("setInitialvisibility", static_cast<void(org::imm::ImmDocumentOptionsValue::*)(InitialSubtreeVisibility const&)>(&org::imm::ImmDocumentOptionsValue::setInitialvisibility))
    .function("setProperties", static_cast<void(org::imm::ImmDocumentOptionsValue::*)(immer::flex_vector<org::sem::NamedProperty> const&)>(&org::imm::ImmDocumentOptionsValue::setProperties))
    .function("setExportconfig", static_cast<void(org::imm::ImmDocumentOptionsValue::*)(org::sem::DocumentExportConfig const&)>(&org::imm::ImmDocumentOptionsValue::setExportconfig))
    .function("setFixedwidthsections", static_cast<void(org::imm::ImmDocumentOptionsValue::*)(immer::box<std::optional<bool>> const&)>(&org::imm::ImmDocumentOptionsValue::setFixedwidthsections))
    .function("setStartupindented", static_cast<void(org::imm::ImmDocumentOptionsValue::*)(immer::box<std::optional<bool>> const&)>(&org::imm::ImmDocumentOptionsValue::setStartupindented))
    .function("setCategory", static_cast<void(org::imm::ImmDocumentOptionsValue::*)(immer::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmDocumentOptionsValue::setCategory))
    .function("setSetupfile", static_cast<void(org::imm::ImmDocumentOptionsValue::*)(immer::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmDocumentOptionsValue::setSetupfile))
    .function("setMaxsubtreelevelexport", static_cast<void(org::imm::ImmDocumentOptionsValue::*)(immer::box<std::optional<int>> const&)>(&org::imm::ImmDocumentOptionsValue::setMaxsubtreelevelexport))
    .function("setColumns", static_cast<void(org::imm::ImmDocumentOptionsValue::*)(immer::box<std::optional<org::sem::ColumnView>> const&)>(&org::imm::ImmDocumentOptionsValue::setColumns))
    .function("setTodokeywords", static_cast<void(org::imm::ImmDocumentOptionsValue::*)(immer::flex_vector<org::sem::TodoKeyword> const&)>(&org::imm::ImmDocumentOptionsValue::setTodokeywords))
    .function("setDonekeywords", static_cast<void(org::imm::ImmDocumentOptionsValue::*)(immer::flex_vector<org::sem::TodoKeyword> const&)>(&org::imm::ImmDocumentOptionsValue::setDonekeywords))
    ;
  emscripten::class_<org::imm::ImmDocumentFragmentValue, emscripten::base<org::imm::ImmDocumentFragmentValueRead>>("ImmDocumentFragmentValue")
    .function("setBaseline", static_cast<void(org::imm::ImmDocumentFragmentValue::*)(int const&)>(&org::imm::ImmDocumentFragmentValue::setBaseline))
    .function("setBasecol", static_cast<void(org::imm::ImmDocumentFragmentValue::*)(int const&)>(&org::imm::ImmDocumentFragmentValue::setBasecol))
    ;
  emscripten::class_<org::imm::ImmCriticMarkupValue, emscripten::base<org::imm::ImmCriticMarkupValueRead>>("ImmCriticMarkupValue")
    .function("setKind", static_cast<void(org::imm::ImmCriticMarkupValue::*)(org::imm::ImmCriticMarkup::Kind const&)>(&org::imm::ImmCriticMarkupValue::setKind))
    ;
  emscripten::class_<org::imm::ImmDocumentValue, emscripten::base<org::imm::ImmDocumentValueRead>>("ImmDocumentValue")
    .function("setTitle", static_cast<void(org::imm::ImmDocumentValue::*)(immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&)>(&org::imm::ImmDocumentValue::setTitle))
    .function("setAuthor", static_cast<void(org::imm::ImmDocumentValue::*)(immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&)>(&org::imm::ImmDocumentValue::setAuthor))
    .function("setCreator", static_cast<void(org::imm::ImmDocumentValue::*)(immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&)>(&org::imm::ImmDocumentValue::setCreator))
    .function("setFiletags", static_cast<void(org::imm::ImmDocumentValue::*)(immer::flex_vector<org::imm::ImmIdT<org::imm::ImmHashTag>> const&)>(&org::imm::ImmDocumentValue::setFiletags))
    .function("setEmail", static_cast<void(org::imm::ImmDocumentValue::*)(immer::box<std::optional<org::imm::ImmIdT<org::imm::ImmRawText>>> const&)>(&org::imm::ImmDocumentValue::setEmail))
    .function("setLanguage", static_cast<void(org::imm::ImmDocumentValue::*)(immer::flex_vector<hstd::Str> const&)>(&org::imm::ImmDocumentValue::setLanguage))
    .function("setOptions", static_cast<void(org::imm::ImmDocumentValue::*)(org::imm::ImmIdT<org::imm::ImmDocumentOptions> const&)>(&org::imm::ImmDocumentValue::setOptions))
    .function("setExportfilename", static_cast<void(org::imm::ImmDocumentValue::*)(immer::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmDocumentValue::setExportfilename))
    ;
  emscripten::class_<org::imm::ImmFileTargetValue, emscripten::base<org::imm::ImmFileTargetValueRead>>("ImmFileTargetValue")
    .function("setPath", static_cast<void(org::imm::ImmFileTargetValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmFileTargetValue::setPath))
    .function("setLine", static_cast<void(org::imm::ImmFileTargetValue::*)(immer::box<std::optional<int>> const&)>(&org::imm::ImmFileTargetValue::setLine))
    .function("setSearchtarget", static_cast<void(org::imm::ImmFileTargetValue::*)(immer::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmFileTargetValue::setSearchtarget))
    .function("setRestricttoheadlines", static_cast<void(org::imm::ImmFileTargetValue::*)(bool const&)>(&org::imm::ImmFileTargetValue::setRestricttoheadlines))
    .function("setTargetid", static_cast<void(org::imm::ImmFileTargetValue::*)(immer::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmFileTargetValue::setTargetid))
    .function("setRegexp", static_cast<void(org::imm::ImmFileTargetValue::*)(immer::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmFileTargetValue::setRegexp))
    ;
  emscripten::class_<org::imm::ImmTextSeparatorValue, emscripten::base<org::imm::ImmTextSeparatorValueRead>>("ImmTextSeparatorValue")
    ;
}

void subdivide_6(org::bind::js::type_registration_guard& g) {
  emscripten::class_<org::imm::ImmDocumentGroupValue, emscripten::base<org::imm::ImmDocumentGroupValueRead>>("ImmDocumentGroupValue")
    ;
  emscripten::class_<org::imm::ImmFileValue, emscripten::base<org::imm::ImmFileValueRead>>("ImmFileValue")
    .function("setRelpath", static_cast<void(org::imm::ImmFileValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmFileValue::setRelpath))
    .function("setAbspath", static_cast<void(org::imm::ImmFileValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmFileValue::setAbspath))
    .function("setData", static_cast<void(org::imm::ImmFileValue::*)(org::imm::ImmFile::Data const&)>(&org::imm::ImmFileValue::setData))
    ;
  emscripten::class_<org::imm::ImmDirectoryValue, emscripten::base<org::imm::ImmDirectoryValueRead>>("ImmDirectoryValue")
    .function("setRelpath", static_cast<void(org::imm::ImmDirectoryValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmDirectoryValue::setRelpath))
    .function("setAbspath", static_cast<void(org::imm::ImmDirectoryValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmDirectoryValue::setAbspath))
    ;
  emscripten::class_<org::imm::ImmSymlinkValue, emscripten::base<org::imm::ImmSymlinkValueRead>>("ImmSymlinkValue")
    .function("setIsdirectory", static_cast<void(org::imm::ImmSymlinkValue::*)(bool const&)>(&org::imm::ImmSymlinkValue::setIsdirectory))
    .function("setAbspath", static_cast<void(org::imm::ImmSymlinkValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmSymlinkValue::setAbspath))
    ;
  emscripten::class_<org::imm::ImmCmdIncludeValue, emscripten::base<org::imm::ImmCmdIncludeValueRead>>("ImmCmdIncludeValue")
    .function("setPath", static_cast<void(org::imm::ImmCmdIncludeValue::*)(immer::box<hstd::Str> const&)>(&org::imm::ImmCmdIncludeValue::setPath))
    .function("setFirstline", static_cast<void(org::imm::ImmCmdIncludeValue::*)(immer::box<std::optional<int>> const&)>(&org::imm::ImmCmdIncludeValue::setFirstline))
    .function("setLastline", static_cast<void(org::imm::ImmCmdIncludeValue::*)(immer::box<std::optional<int>> const&)>(&org::imm::ImmCmdIncludeValue::setLastline))
    .function("setData", static_cast<void(org::imm::ImmCmdIncludeValue::*)(org::imm::ImmCmdInclude::Data const&)>(&org::imm::ImmCmdIncludeValue::setData))
    ;
  emscripten::class_<org::imm::ImmAdapterOrgAPI, emscripten::base<org::imm::ImmAdapterVirtualBase>>("ImmAdapterOrgAPI")
    ;
  emscripten::class_<org::sem::Cmd, emscripten::base<org::sem::Stmt>>("Cmd")
    .smart_ptr<org::sem::SemId<org::sem::Cmd>>("Cmd")
    .property("attrs", &org::sem::Cmd::attrs)
    .function("getAttrs", static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Cmd::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Cmd::getAttrs))
    .function("getFirstAttr", static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Cmd::*)(hstd::Str const&) const>(&org::sem::Cmd::getFirstAttr))
    ;
  emscripten::class_<org::sem::CmdCustomRaw, emscripten::base<org::sem::Stmt>>("CmdCustomRaw")
    .smart_ptr<org::sem::SemId<org::sem::CmdCustomRaw>>("CmdCustomRaw")
    .property("name", &org::sem::CmdCustomRaw::name)
    .property("isAttached", &org::sem::CmdCustomRaw::isAttached)
    .property("text", &org::sem::CmdCustomRaw::text)
    .function("getKind", static_cast<OrgSemKind(org::sem::CmdCustomRaw::*)() const>(&org::sem::CmdCustomRaw::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::CmdCustomRaw>>)
    ;
  emscripten::class_<org::sem::CmdCustomText, emscripten::base<org::sem::Stmt>>("CmdCustomText")
    .smart_ptr<org::sem::SemId<org::sem::CmdCustomText>>("CmdCustomText")
    .property("name", &org::sem::CmdCustomText::name)
    .property("isAttached", &org::sem::CmdCustomText::isAttached)
    .property("text", &org::sem::CmdCustomText::text)
    .function("getKind", static_cast<OrgSemKind(org::sem::CmdCustomText::*)() const>(&org::sem::CmdCustomText::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::CmdCustomText>>)
    ;
  emscripten::class_<org::sem::Link, emscripten::base<org::sem::Stmt>>("Link")
    .smart_ptr<org::sem::SemId<org::sem::Link>>("Link")
    .property("description", &org::sem::Link::description)
    .property("target", &org::sem::Link::target)
    .function("getKind", static_cast<OrgSemKind(org::sem::Link::*)() const>(&org::sem::Link::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Link>>)
    ;
  emscripten::class_<org::sem::BlockComment, emscripten::base<org::sem::Stmt>>("BlockComment")
    .smart_ptr<org::sem::SemId<org::sem::BlockComment>>("BlockComment")
    .function("getKind", static_cast<OrgSemKind(org::sem::BlockComment::*)() const>(&org::sem::BlockComment::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::BlockComment>>)
    ;
  emscripten::class_<org::sem::Paragraph, emscripten::base<org::sem::Stmt>>("Paragraph")
    .smart_ptr<org::sem::SemId<org::sem::Paragraph>>("Paragraph")
    .function("getKind", static_cast<OrgSemKind(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getKind))
    .function("isFootnoteDefinition", static_cast<bool(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::isFootnoteDefinition))
    .function("getFootnoteName", static_cast<hstd::Opt<hstd::Str>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getFootnoteName))
    .function("hasAdmonition", static_cast<bool(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::hasAdmonition))
    .function("getAdmonitions", static_cast<hstd::Vec<hstd::Str>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getAdmonitions))
    .function("getAdmonitionNodes", static_cast<hstd::Vec<org::sem::SemId<org::sem::BigIdent>>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getAdmonitionNodes))
    .function("hasTimestamp", static_cast<bool(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::hasTimestamp))
    .function("getTimestamps", static_cast<hstd::Vec<hstd::UserTime>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getTimestamps))
    .function("getTimestampNodes", static_cast<hstd::Vec<org::sem::SemId<org::sem::Time>>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getTimestampNodes))
    .function("hasLeadHashtags", static_cast<bool(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::hasLeadHashtags))
    .function("getLeadHashtags", static_cast<hstd::Vec<org::sem::SemId<org::sem::HashTag>>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getLeadHashtags))
    .function("getBody", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getBody))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Paragraph>>)
    ;
  emscripten::class_<org::sem::List, emscripten::base<org::sem::Stmt>>("List")
    .smart_ptr<org::sem::SemId<org::sem::List>>("List")
    .function("getKind", static_cast<OrgSemKind(org::sem::List::*)() const>(&org::sem::List::getKind))
    .function("getListAttrs", static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::List::*)(hstd::Str const&) const>(&org::sem::List::getListAttrs))
    .function("getListFormattingMode", static_cast<ListFormattingMode(org::sem::List::*)() const>(&org::sem::List::getListFormattingMode))
    .function("isDescriptionList", static_cast<bool(org::sem::List::*)() const>(&org::sem::List::isDescriptionList))
    .function("isNumberedList", static_cast<bool(org::sem::List::*)() const>(&org::sem::List::isNumberedList))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::List>>)
    ;
  emscripten::class_<org::sem::HashTag, emscripten::base<org::sem::Inline>>("HashTag")
    .smart_ptr<org::sem::SemId<org::sem::HashTag>>("HashTag")
    .property("text", &org::sem::HashTag::text)
    .function("getKind", static_cast<OrgSemKind(org::sem::HashTag::*)() const>(&org::sem::HashTag::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::HashTag>>)
    ;
  emscripten::class_<org::sem::InlineFootnote, emscripten::base<org::sem::Inline>>("InlineFootnote")
    .smart_ptr<org::sem::SemId<org::sem::InlineFootnote>>("InlineFootnote")
    .property("tag", &org::sem::InlineFootnote::tag)
    .property("definition", &org::sem::InlineFootnote::definition)
    .function("getKind", static_cast<OrgSemKind(org::sem::InlineFootnote::*)() const>(&org::sem::InlineFootnote::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::InlineFootnote>>)
    ;
  emscripten::class_<org::sem::InlineExport, emscripten::base<org::sem::Inline>>("InlineExport")
    .smart_ptr<org::sem::SemId<org::sem::InlineExport>>("InlineExport")
    .property("exporter", &org::sem::InlineExport::exporter)
    .property("content", &org::sem::InlineExport::content)
    .function("getKind", static_cast<OrgSemKind(org::sem::InlineExport::*)() const>(&org::sem::InlineExport::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::InlineExport>>)
    ;
  emscripten::class_<org::sem::Escaped, emscripten::base<org::sem::Leaf>>("Escaped")
    .smart_ptr<org::sem::SemId<org::sem::Escaped>>("Escaped")
    .function("getKind", static_cast<OrgSemKind(org::sem::Escaped::*)() const>(&org::sem::Escaped::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Escaped>>)
    ;
  emscripten::class_<org::sem::Newline, emscripten::base<org::sem::Leaf>>("Newline")
    .smart_ptr<org::sem::SemId<org::sem::Newline>>("Newline")
    .function("getKind", static_cast<OrgSemKind(org::sem::Newline::*)() const>(&org::sem::Newline::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Newline>>)
    ;
  emscripten::class_<org::sem::Space, emscripten::base<org::sem::Leaf>>("Space")
    .smart_ptr<org::sem::SemId<org::sem::Space>>("Space")
    .function("getKind", static_cast<OrgSemKind(org::sem::Space::*)() const>(&org::sem::Space::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Space>>)
    ;
  emscripten::class_<org::sem::Word, emscripten::base<org::sem::Leaf>>("Word")
    .smart_ptr<org::sem::SemId<org::sem::Word>>("Word")
    .function("getKind", static_cast<OrgSemKind(org::sem::Word::*)() const>(&org::sem::Word::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Word>>)
    ;
  emscripten::class_<org::sem::AtMention, emscripten::base<org::sem::Leaf>>("AtMention")
    .smart_ptr<org::sem::SemId<org::sem::AtMention>>("AtMention")
    .function("getKind", static_cast<OrgSemKind(org::sem::AtMention::*)() const>(&org::sem::AtMention::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::AtMention>>)
    ;
  emscripten::class_<org::sem::RawText, emscripten::base<org::sem::Leaf>>("RawText")
    .smart_ptr<org::sem::SemId<org::sem::RawText>>("RawText")
    .function("getKind", static_cast<OrgSemKind(org::sem::RawText::*)() const>(&org::sem::RawText::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::RawText>>)
    ;
  emscripten::class_<org::sem::Punctuation, emscripten::base<org::sem::Leaf>>("Punctuation")
    .smart_ptr<org::sem::SemId<org::sem::Punctuation>>("Punctuation")
    .function("getKind", static_cast<OrgSemKind(org::sem::Punctuation::*)() const>(&org::sem::Punctuation::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Punctuation>>)
    ;
  emscripten::class_<org::sem::Placeholder, emscripten::base<org::sem::Leaf>>("Placeholder")
    .smart_ptr<org::sem::SemId<org::sem::Placeholder>>("Placeholder")
    .function("getKind", static_cast<OrgSemKind(org::sem::Placeholder::*)() const>(&org::sem::Placeholder::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Placeholder>>)
    ;
  emscripten::class_<org::sem::BigIdent, emscripten::base<org::sem::Leaf>>("BigIdent")
    .smart_ptr<org::sem::SemId<org::sem::BigIdent>>("BigIdent")
    .function("getKind", static_cast<OrgSemKind(org::sem::BigIdent::*)() const>(&org::sem::BigIdent::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::BigIdent>>)
    ;
  emscripten::class_<org::sem::TextTarget, emscripten::base<org::sem::Leaf>>("TextTarget")
    .smart_ptr<org::sem::SemId<org::sem::TextTarget>>("TextTarget")
    .function("getKind", static_cast<OrgSemKind(org::sem::TextTarget::*)() const>(&org::sem::TextTarget::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::TextTarget>>)
    ;
  emscripten::class_<org::sem::Bold, emscripten::base<org::sem::Markup>>("Bold")
    .smart_ptr<org::sem::SemId<org::sem::Bold>>("Bold")
    .function("getKind", static_cast<OrgSemKind(org::sem::Bold::*)() const>(&org::sem::Bold::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Bold>>)
    ;
  emscripten::class_<org::sem::Underline, emscripten::base<org::sem::Markup>>("Underline")
    .smart_ptr<org::sem::SemId<org::sem::Underline>>("Underline")
    .function("getKind", static_cast<OrgSemKind(org::sem::Underline::*)() const>(&org::sem::Underline::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Underline>>)
    ;
  emscripten::class_<org::sem::Monospace, emscripten::base<org::sem::Markup>>("Monospace")
    .smart_ptr<org::sem::SemId<org::sem::Monospace>>("Monospace")
    .function("getKind", static_cast<OrgSemKind(org::sem::Monospace::*)() const>(&org::sem::Monospace::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Monospace>>)
    ;
  emscripten::class_<org::sem::MarkQuote, emscripten::base<org::sem::Markup>>("MarkQuote")
    .smart_ptr<org::sem::SemId<org::sem::MarkQuote>>("MarkQuote")
    .function("getKind", static_cast<OrgSemKind(org::sem::MarkQuote::*)() const>(&org::sem::MarkQuote::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::MarkQuote>>)
    ;
  emscripten::class_<org::sem::Verbatim, emscripten::base<org::sem::Markup>>("Verbatim")
    .smart_ptr<org::sem::SemId<org::sem::Verbatim>>("Verbatim")
    .function("getKind", static_cast<OrgSemKind(org::sem::Verbatim::*)() const>(&org::sem::Verbatim::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Verbatim>>)
    ;
  emscripten::class_<org::sem::Italic, emscripten::base<org::sem::Markup>>("Italic")
    .smart_ptr<org::sem::SemId<org::sem::Italic>>("Italic")
    .function("getKind", static_cast<OrgSemKind(org::sem::Italic::*)() const>(&org::sem::Italic::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Italic>>)
    ;
  emscripten::class_<org::sem::Strike, emscripten::base<org::sem::Markup>>("Strike")
    .smart_ptr<org::sem::SemId<org::sem::Strike>>("Strike")
    .function("getKind", static_cast<OrgSemKind(org::sem::Strike::*)() const>(&org::sem::Strike::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Strike>>)
    ;
  emscripten::class_<org::sem::Par, emscripten::base<org::sem::Markup>>("Par")
    .smart_ptr<org::sem::SemId<org::sem::Par>>("Par")
    .function("getKind", static_cast<OrgSemKind(org::sem::Par::*)() const>(&org::sem::Par::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Par>>)
    ;
  emscripten::class_<org::imm::ImmCmd, emscripten::base<org::imm::ImmStmt>>("ImmCmd")
    .property("attrs", &org::imm::ImmCmd::attrs)
    .function("__eq__", static_cast<bool(org::imm::ImmCmd::*)(org::imm::ImmCmd const&) const>(&org::imm::ImmCmd::operator==))
    ;
  emscripten::class_<org::imm::ImmCmdCustomRaw, emscripten::base<org::imm::ImmStmt>>("ImmCmdCustomRaw")
    .property("name", &org::imm::ImmCmdCustomRaw::name)
    .property("isAttached", &org::imm::ImmCmdCustomRaw::isAttached)
    .property("text", &org::imm::ImmCmdCustomRaw::text)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmCmdCustomRaw::*)() const>(&org::imm::ImmCmdCustomRaw::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCmdCustomRaw::*)(org::imm::ImmCmdCustomRaw const&) const>(&org::imm::ImmCmdCustomRaw::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdCustomText, emscripten::base<org::imm::ImmStmt>>("ImmCmdCustomText")
    .property("name", &org::imm::ImmCmdCustomText::name)
    .property("isAttached", &org::imm::ImmCmdCustomText::isAttached)
    .property("text", &org::imm::ImmCmdCustomText::text)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmCmdCustomText::*)() const>(&org::imm::ImmCmdCustomText::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCmdCustomText::*)(org::imm::ImmCmdCustomText const&) const>(&org::imm::ImmCmdCustomText::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmLink, emscripten::base<org::imm::ImmStmt>>("ImmLink")
    .property("description", &org::imm::ImmLink::description)
    .property("target", &org::imm::ImmLink::target)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmLink::*)() const>(&org::imm::ImmLink::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmLink::*)(org::imm::ImmLink const&) const>(&org::imm::ImmLink::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmBlockComment, emscripten::base<org::imm::ImmStmt>>("ImmBlockComment")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmBlockComment::*)() const>(&org::imm::ImmBlockComment::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmBlockComment::*)(org::imm::ImmBlockComment const&) const>(&org::imm::ImmBlockComment::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmParagraph, emscripten::base<org::imm::ImmStmt>>("ImmParagraph")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmParagraph::*)() const>(&org::imm::ImmParagraph::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmParagraph::*)(org::imm::ImmParagraph const&) const>(&org::imm::ImmParagraph::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmList, emscripten::base<org::imm::ImmStmt>>("ImmList")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmList::*)() const>(&org::imm::ImmList::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmList::*)(org::imm::ImmList const&) const>(&org::imm::ImmList::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmHashTag, emscripten::base<org::imm::ImmInline>>("ImmHashTag")
    .property("text", &org::imm::ImmHashTag::text)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmHashTag::*)() const>(&org::imm::ImmHashTag::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmHashTag::*)(org::imm::ImmHashTag const&) const>(&org::imm::ImmHashTag::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmInlineFootnote, emscripten::base<org::imm::ImmInline>>("ImmInlineFootnote")
    .property("tag", &org::imm::ImmInlineFootnote::tag)
    .property("definition", &org::imm::ImmInlineFootnote::definition)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmInlineFootnote::*)() const>(&org::imm::ImmInlineFootnote::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmInlineFootnote::*)(org::imm::ImmInlineFootnote const&) const>(&org::imm::ImmInlineFootnote::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmInlineExport, emscripten::base<org::imm::ImmInline>>("ImmInlineExport")
    .property("exporter", &org::imm::ImmInlineExport::exporter)
    .property("content", &org::imm::ImmInlineExport::content)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmInlineExport::*)() const>(&org::imm::ImmInlineExport::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmInlineExport::*)(org::imm::ImmInlineExport const&) const>(&org::imm::ImmInlineExport::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmEscaped, emscripten::base<org::imm::ImmLeaf>>("ImmEscaped")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmEscaped::*)() const>(&org::imm::ImmEscaped::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmEscaped::*)(org::imm::ImmEscaped const&) const>(&org::imm::ImmEscaped::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmNewline, emscripten::base<org::imm::ImmLeaf>>("ImmNewline")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmNewline::*)() const>(&org::imm::ImmNewline::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmNewline::*)(org::imm::ImmNewline const&) const>(&org::imm::ImmNewline::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmSpace, emscripten::base<org::imm::ImmLeaf>>("ImmSpace")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmSpace::*)() const>(&org::imm::ImmSpace::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmSpace::*)(org::imm::ImmSpace const&) const>(&org::imm::ImmSpace::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmWord, emscripten::base<org::imm::ImmLeaf>>("ImmWord")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmWord::*)() const>(&org::imm::ImmWord::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmWord::*)(org::imm::ImmWord const&) const>(&org::imm::ImmWord::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmAtMention, emscripten::base<org::imm::ImmLeaf>>("ImmAtMention")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmAtMention::*)() const>(&org::imm::ImmAtMention::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmAtMention::*)(org::imm::ImmAtMention const&) const>(&org::imm::ImmAtMention::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmRawText, emscripten::base<org::imm::ImmLeaf>>("ImmRawText")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmRawText::*)() const>(&org::imm::ImmRawText::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmRawText::*)(org::imm::ImmRawText const&) const>(&org::imm::ImmRawText::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmPunctuation, emscripten::base<org::imm::ImmLeaf>>("ImmPunctuation")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmPunctuation::*)() const>(&org::imm::ImmPunctuation::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmPunctuation::*)(org::imm::ImmPunctuation const&) const>(&org::imm::ImmPunctuation::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmPlaceholder, emscripten::base<org::imm::ImmLeaf>>("ImmPlaceholder")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmPlaceholder::*)() const>(&org::imm::ImmPlaceholder::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmPlaceholder::*)(org::imm::ImmPlaceholder const&) const>(&org::imm::ImmPlaceholder::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmBigIdent, emscripten::base<org::imm::ImmLeaf>>("ImmBigIdent")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmBigIdent::*)() const>(&org::imm::ImmBigIdent::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmBigIdent::*)(org::imm::ImmBigIdent const&) const>(&org::imm::ImmBigIdent::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmTextTarget, emscripten::base<org::imm::ImmLeaf>>("ImmTextTarget")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmTextTarget::*)() const>(&org::imm::ImmTextTarget::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmTextTarget::*)(org::imm::ImmTextTarget const&) const>(&org::imm::ImmTextTarget::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmBold, emscripten::base<org::imm::ImmMarkup>>("ImmBold")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmBold::*)() const>(&org::imm::ImmBold::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmBold::*)(org::imm::ImmBold const&) const>(&org::imm::ImmBold::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmUnderline, emscripten::base<org::imm::ImmMarkup>>("ImmUnderline")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmUnderline::*)() const>(&org::imm::ImmUnderline::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmUnderline::*)(org::imm::ImmUnderline const&) const>(&org::imm::ImmUnderline::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmMonospace, emscripten::base<org::imm::ImmMarkup>>("ImmMonospace")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmMonospace::*)() const>(&org::imm::ImmMonospace::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmMonospace::*)(org::imm::ImmMonospace const&) const>(&org::imm::ImmMonospace::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmMarkQuote, emscripten::base<org::imm::ImmMarkup>>("ImmMarkQuote")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmMarkQuote::*)() const>(&org::imm::ImmMarkQuote::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmMarkQuote::*)(org::imm::ImmMarkQuote const&) const>(&org::imm::ImmMarkQuote::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmVerbatim, emscripten::base<org::imm::ImmMarkup>>("ImmVerbatim")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmVerbatim::*)() const>(&org::imm::ImmVerbatim::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmVerbatim::*)(org::imm::ImmVerbatim const&) const>(&org::imm::ImmVerbatim::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmItalic, emscripten::base<org::imm::ImmMarkup>>("ImmItalic")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmItalic::*)() const>(&org::imm::ImmItalic::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmItalic::*)(org::imm::ImmItalic const&) const>(&org::imm::ImmItalic::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmStrike, emscripten::base<org::imm::ImmMarkup>>("ImmStrike")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmStrike::*)() const>(&org::imm::ImmStrike::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmStrike::*)(org::imm::ImmStrike const&) const>(&org::imm::ImmStrike::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmPar, emscripten::base<org::imm::ImmMarkup>>("ImmPar")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmPar::*)() const>(&org::imm::ImmPar::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmPar::*)(org::imm::ImmPar const&) const>(&org::imm::ImmPar::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmAdapterStmtAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterStmtAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterSubtreeAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterSubtreeAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterNoneAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterNoneAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterAttrAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterAttrAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterAttrListAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterAttrListAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterAttrsAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterAttrsAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterErrorItemAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterErrorItemAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterErrorGroupAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterErrorGroupAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterStmtListAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterStmtListAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterEmptyAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterEmptyAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterInlineAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterInlineAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterTimeAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterTimeAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterTimeRangeAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterTimeRangeAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterMacroAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterMacroAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterSymbolAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterSymbolAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterLeafAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterLeafAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterMarkupAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterMarkupAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterLatexAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterLatexAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterSubtreeLogAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterSubtreeLogAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterColonExampleAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterColonExampleAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterCallAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterCallAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterFileAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterFileAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterDirectoryAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterDirectoryAPI")
    .function("getFsSubnode", static_cast<std::optional<org::imm::ImmAdapter>(org::imm::ImmAdapterDirectoryAPI::*)(hstd::Str const&, bool) const>(&org::imm::ImmAdapterDirectoryAPI::getFsSubnode))
    ;
  emscripten::class_<org::imm::ImmAdapterSymlinkAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterSymlinkAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterDocumentFragmentAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterDocumentFragmentAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterCriticMarkupAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterCriticMarkupAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterListItemAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterListItemAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterDocumentOptionsAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterDocumentOptionsAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterDocumentAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterDocumentAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterFileTargetAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterFileTargetAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterTextSeparatorAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterTextSeparatorAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterCmdIncludeAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterCmdIncludeAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterDocumentGroupAPI, emscripten::base<org::imm::ImmAdapterOrgAPI>>("ImmAdapterDocumentGroupAPI")
    ;
  emscripten::class_<org::sem::Block, emscripten::base<org::sem::Cmd>>("Block")
    .smart_ptr<org::sem::SemId<org::sem::Block>>("Block")
    ;
  emscripten::class_<org::sem::LineCommand, emscripten::base<org::sem::Cmd>>("LineCommand")
    .smart_ptr<org::sem::SemId<org::sem::LineCommand>>("LineCommand")
    ;
  emscripten::class_<org::sem::CmdCustomArgs, emscripten::base<org::sem::Cmd>>("CmdCustomArgs")
    .smart_ptr<org::sem::SemId<org::sem::CmdCustomArgs>>("CmdCustomArgs")
    .property("name", &org::sem::CmdCustomArgs::name)
    .property("isAttached", &org::sem::CmdCustomArgs::isAttached)
    .function("getKind", static_cast<OrgSemKind(org::sem::CmdCustomArgs::*)() const>(&org::sem::CmdCustomArgs::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::CmdCustomArgs>>)
    ;
  emscripten::class_<org::sem::CmdTblfm, emscripten::base<org::sem::Cmd>>("CmdTblfm")
    .smart_ptr<org::sem::SemId<org::sem::CmdTblfm>>("CmdTblfm")
    .property("expr", &org::sem::CmdTblfm::expr)
    .function("getKind", static_cast<OrgSemKind(org::sem::CmdTblfm::*)() const>(&org::sem::CmdTblfm::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::CmdTblfm>>)
    ;
  emscripten::class_<org::sem::Cell, emscripten::base<org::sem::Cmd>>("Cell")
    .smart_ptr<org::sem::SemId<org::sem::Cell>>("Cell")
    .property("isBlock", &org::sem::Cell::isBlock)
    .function("getKind", static_cast<OrgSemKind(org::sem::Cell::*)() const>(&org::sem::Cell::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Cell>>)
    ;
  emscripten::class_<org::sem::Row, emscripten::base<org::sem::Cmd>>("Row")
    .smart_ptr<org::sem::SemId<org::sem::Row>>("Row")
    .property("cells", &org::sem::Row::cells)
    .property("isBlock", &org::sem::Row::isBlock)
    .function("getKind", static_cast<OrgSemKind(org::sem::Row::*)() const>(&org::sem::Row::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Row>>)
    ;
}

void subdivide_7(org::bind::js::type_registration_guard& g) {
  emscripten::class_<org::imm::ImmBlock, emscripten::base<org::imm::ImmCmd>>("ImmBlock")
    .function("__eq__", static_cast<bool(org::imm::ImmBlock::*)(org::imm::ImmBlock const&) const>(&org::imm::ImmBlock::operator==))
    ;
  emscripten::class_<org::imm::ImmLineCommand, emscripten::base<org::imm::ImmCmd>>("ImmLineCommand")
    .function("__eq__", static_cast<bool(org::imm::ImmLineCommand::*)(org::imm::ImmLineCommand const&) const>(&org::imm::ImmLineCommand::operator==))
    ;
  emscripten::class_<org::imm::ImmCmdCustomArgs, emscripten::base<org::imm::ImmCmd>>("ImmCmdCustomArgs")
    .property("name", &org::imm::ImmCmdCustomArgs::name)
    .property("isAttached", &org::imm::ImmCmdCustomArgs::isAttached)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmCmdCustomArgs::*)() const>(&org::imm::ImmCmdCustomArgs::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCmdCustomArgs::*)(org::imm::ImmCmdCustomArgs const&) const>(&org::imm::ImmCmdCustomArgs::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdTblfm, emscripten::base<org::imm::ImmCmd>>("ImmCmdTblfm")
    .property("expr", &org::imm::ImmCmdTblfm::expr)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmCmdTblfm::*)() const>(&org::imm::ImmCmdTblfm::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCmdTblfm::*)(org::imm::ImmCmdTblfm const&) const>(&org::imm::ImmCmdTblfm::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCell, emscripten::base<org::imm::ImmCmd>>("ImmCell")
    .property("isBlock", &org::imm::ImmCell::isBlock)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmCell::*)() const>(&org::imm::ImmCell::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCell::*)(org::imm::ImmCell const&) const>(&org::imm::ImmCell::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmRow, emscripten::base<org::imm::ImmCmd>>("ImmRow")
    .property("cells", &org::imm::ImmRow::cells)
    .property("isBlock", &org::imm::ImmRow::isBlock)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmRow::*)() const>(&org::imm::ImmRow::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmRow::*)(org::imm::ImmRow const&) const>(&org::imm::ImmRow::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmAdapterCmdAPI, emscripten::base<org::imm::ImmAdapterStmtAPI>>("ImmAdapterCmdAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterCmdCustomRawAPI, emscripten::base<org::imm::ImmAdapterStmtAPI>>("ImmAdapterCmdCustomRawAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterCmdCustomTextAPI, emscripten::base<org::imm::ImmAdapterStmtAPI>>("ImmAdapterCmdCustomTextAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterLinkAPI, emscripten::base<org::imm::ImmAdapterStmtAPI>>("ImmAdapterLinkAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterBlockCommentAPI, emscripten::base<org::imm::ImmAdapterStmtAPI>>("ImmAdapterBlockCommentAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterParagraphAPI, emscripten::base<org::imm::ImmAdapterStmtAPI>>("ImmAdapterParagraphAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterListAPI, emscripten::base<org::imm::ImmAdapterStmtAPI>>("ImmAdapterListAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmSubtree>, emscripten::base<org::imm::ImmAdapterSubtreeAPI>>("ImmSubtreeAdapter")
    .function("getValue", static_cast<org::imm::ImmSubtreeValueRead(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmNone>, emscripten::base<org::imm::ImmAdapterNoneAPI>>("ImmNoneAdapter")
    .function("getValue", static_cast<org::imm::ImmNoneValueRead(org::imm::ImmAdapterT<org::imm::ImmNone>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmNone>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmErrorItem>, emscripten::base<org::imm::ImmAdapterErrorItemAPI>>("ImmErrorItemAdapter")
    .function("getValue", static_cast<org::imm::ImmErrorItemValueRead(org::imm::ImmAdapterT<org::imm::ImmErrorItem>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmErrorItem>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmErrorGroup>, emscripten::base<org::imm::ImmAdapterErrorGroupAPI>>("ImmErrorGroupAdapter")
    .function("getValue", static_cast<org::imm::ImmErrorGroupValueRead(org::imm::ImmAdapterT<org::imm::ImmErrorGroup>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmErrorGroup>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmStmtList>, emscripten::base<org::imm::ImmAdapterStmtListAPI>>("ImmStmtListAdapter")
    .function("getValue", static_cast<org::imm::ImmStmtListValueRead(org::imm::ImmAdapterT<org::imm::ImmStmtList>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmStmtList>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmEmpty>, emscripten::base<org::imm::ImmAdapterEmptyAPI>>("ImmEmptyAdapter")
    .function("getValue", static_cast<org::imm::ImmEmptyValueRead(org::imm::ImmAdapterT<org::imm::ImmEmpty>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmEmpty>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterHashTagAPI, emscripten::base<org::imm::ImmAdapterInlineAPI>>("ImmAdapterHashTagAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterInlineFootnoteAPI, emscripten::base<org::imm::ImmAdapterInlineAPI>>("ImmAdapterInlineFootnoteAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterSubtreeCompletionAPI, emscripten::base<org::imm::ImmAdapterInlineAPI>>("ImmAdapterSubtreeCompletionAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmTime>, emscripten::base<org::imm::ImmAdapterTimeAPI>>("ImmTimeAdapter")
    .function("getValue", static_cast<org::imm::ImmTimeValueRead(org::imm::ImmAdapterT<org::imm::ImmTime>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTime>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmTimeRange>, emscripten::base<org::imm::ImmAdapterTimeRangeAPI>>("ImmTimeRangeAdapter")
    .function("getValue", static_cast<org::imm::ImmTimeRangeValueRead(org::imm::ImmAdapterT<org::imm::ImmTimeRange>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTimeRange>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmMacro>, emscripten::base<org::imm::ImmAdapterMacroAPI>>("ImmMacroAdapter")
    .function("getValue", static_cast<org::imm::ImmMacroValueRead(org::imm::ImmAdapterT<org::imm::ImmMacro>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmMacro>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmSymbol>, emscripten::base<org::imm::ImmAdapterSymbolAPI>>("ImmSymbolAdapter")
    .function("getValue", static_cast<org::imm::ImmSymbolValueRead(org::imm::ImmAdapterT<org::imm::ImmSymbol>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymbol>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterEscapedAPI, emscripten::base<org::imm::ImmAdapterLeafAPI>>("ImmAdapterEscapedAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterNewlineAPI, emscripten::base<org::imm::ImmAdapterLeafAPI>>("ImmAdapterNewlineAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterSpaceAPI, emscripten::base<org::imm::ImmAdapterLeafAPI>>("ImmAdapterSpaceAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterWordAPI, emscripten::base<org::imm::ImmAdapterLeafAPI>>("ImmAdapterWordAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterAtMentionAPI, emscripten::base<org::imm::ImmAdapterLeafAPI>>("ImmAdapterAtMentionAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterRawTextAPI, emscripten::base<org::imm::ImmAdapterLeafAPI>>("ImmAdapterRawTextAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterPunctuationAPI, emscripten::base<org::imm::ImmAdapterLeafAPI>>("ImmAdapterPunctuationAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterPlaceholderAPI, emscripten::base<org::imm::ImmAdapterLeafAPI>>("ImmAdapterPlaceholderAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterBigIdentAPI, emscripten::base<org::imm::ImmAdapterLeafAPI>>("ImmAdapterBigIdentAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterTextTargetAPI, emscripten::base<org::imm::ImmAdapterLeafAPI>>("ImmAdapterTextTargetAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterBoldAPI, emscripten::base<org::imm::ImmAdapterMarkupAPI>>("ImmAdapterBoldAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterUnderlineAPI, emscripten::base<org::imm::ImmAdapterMarkupAPI>>("ImmAdapterUnderlineAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterMonospaceAPI, emscripten::base<org::imm::ImmAdapterMarkupAPI>>("ImmAdapterMonospaceAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterMarkQuoteAPI, emscripten::base<org::imm::ImmAdapterMarkupAPI>>("ImmAdapterMarkQuoteAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterRadioTargetAPI, emscripten::base<org::imm::ImmAdapterMarkupAPI>>("ImmAdapterRadioTargetAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterVerbatimAPI, emscripten::base<org::imm::ImmAdapterMarkupAPI>>("ImmAdapterVerbatimAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterItalicAPI, emscripten::base<org::imm::ImmAdapterMarkupAPI>>("ImmAdapterItalicAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterStrikeAPI, emscripten::base<org::imm::ImmAdapterMarkupAPI>>("ImmAdapterStrikeAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterParAPI, emscripten::base<org::imm::ImmAdapterMarkupAPI>>("ImmAdapterParAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmLatex>, emscripten::base<org::imm::ImmAdapterLatexAPI>>("ImmLatexAdapter")
    .function("getValue", static_cast<org::imm::ImmLatexValueRead(org::imm::ImmAdapterT<org::imm::ImmLatex>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmLatex>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>, emscripten::base<org::imm::ImmAdapterSubtreeLogAPI>>("ImmSubtreeLogAdapter")
    .function("getValue", static_cast<org::imm::ImmSubtreeLogValueRead(org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmColonExample>, emscripten::base<org::imm::ImmAdapterColonExampleAPI>>("ImmColonExampleAdapter")
    .function("getValue", static_cast<org::imm::ImmColonExampleValueRead(org::imm::ImmAdapterT<org::imm::ImmColonExample>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmColonExample>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCall>, emscripten::base<org::imm::ImmAdapterCallAPI>>("ImmCallAdapter")
    .function("getValue", static_cast<org::imm::ImmCallValueRead(org::imm::ImmAdapterT<org::imm::ImmCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCall>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmFile>, emscripten::base<org::imm::ImmAdapterFileAPI>>("ImmFileAdapter")
    .function("getValue", static_cast<org::imm::ImmFileValueRead(org::imm::ImmAdapterT<org::imm::ImmFile>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFile>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmDirectory>, emscripten::base<org::imm::ImmAdapterDirectoryAPI>>("ImmDirectoryAdapter")
    .function("getValue", static_cast<org::imm::ImmDirectoryValueRead(org::imm::ImmAdapterT<org::imm::ImmDirectory>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDirectory>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmSymlink>, emscripten::base<org::imm::ImmAdapterSymlinkAPI>>("ImmSymlinkAdapter")
    .function("getValue", static_cast<org::imm::ImmSymlinkValueRead(org::imm::ImmAdapterT<org::imm::ImmSymlink>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymlink>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>, emscripten::base<org::imm::ImmAdapterDocumentFragmentAPI>>("ImmDocumentFragmentAdapter")
    .function("getValue", static_cast<org::imm::ImmDocumentFragmentValueRead(org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>, emscripten::base<org::imm::ImmAdapterCriticMarkupAPI>>("ImmCriticMarkupAdapter")
    .function("getValue", static_cast<org::imm::ImmCriticMarkupValueRead(org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmListItem>, emscripten::base<org::imm::ImmAdapterListItemAPI>>("ImmListItemAdapter")
    .function("getValue", static_cast<org::imm::ImmListItemValueRead(org::imm::ImmAdapterT<org::imm::ImmListItem>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmListItem>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>, emscripten::base<org::imm::ImmAdapterDocumentOptionsAPI>>("ImmDocumentOptionsAdapter")
    .function("getValue", static_cast<org::imm::ImmDocumentOptionsValueRead(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmDocument>, emscripten::base<org::imm::ImmAdapterDocumentAPI>>("ImmDocumentAdapter")
    .function("getValue", static_cast<org::imm::ImmDocumentValueRead(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmFileTarget>, emscripten::base<org::imm::ImmAdapterFileTargetAPI>>("ImmFileTargetAdapter")
    .function("getValue", static_cast<org::imm::ImmFileTargetValueRead(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmTextSeparator>, emscripten::base<org::imm::ImmAdapterTextSeparatorAPI>>("ImmTextSeparatorAdapter")
    .function("getValue", static_cast<org::imm::ImmTextSeparatorValueRead(org::imm::ImmAdapterT<org::imm::ImmTextSeparator>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTextSeparator>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCmdInclude>, emscripten::base<org::imm::ImmAdapterCmdIncludeAPI>>("ImmCmdIncludeAdapter")
    .function("getValue", static_cast<org::imm::ImmCmdIncludeValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmDocumentGroup>, emscripten::base<org::imm::ImmAdapterDocumentGroupAPI>>("ImmDocumentGroupAdapter")
    .function("getValue", static_cast<org::imm::ImmDocumentGroupValueRead(org::imm::ImmAdapterT<org::imm::ImmDocumentGroup>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentGroup>::getValue))
    ;
  emscripten::class_<org::sem::BlockCenter, emscripten::base<org::sem::Block>>("BlockCenter")
    .smart_ptr<org::sem::SemId<org::sem::BlockCenter>>("BlockCenter")
    .function("getKind", static_cast<OrgSemKind(org::sem::BlockCenter::*)() const>(&org::sem::BlockCenter::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::BlockCenter>>)
    ;
  emscripten::class_<org::sem::BlockQuote, emscripten::base<org::sem::Block>>("BlockQuote")
    .smart_ptr<org::sem::SemId<org::sem::BlockQuote>>("BlockQuote")
    .function("getKind", static_cast<OrgSemKind(org::sem::BlockQuote::*)() const>(&org::sem::BlockQuote::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::BlockQuote>>)
    ;
  emscripten::class_<org::sem::BlockVerse, emscripten::base<org::sem::Block>>("BlockVerse")
    .smart_ptr<org::sem::SemId<org::sem::BlockVerse>>("BlockVerse")
    .function("getKind", static_cast<OrgSemKind(org::sem::BlockVerse::*)() const>(&org::sem::BlockVerse::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::BlockVerse>>)
    ;
  emscripten::class_<org::sem::BlockDynamicFallback, emscripten::base<org::sem::Block>>("BlockDynamicFallback")
    .smart_ptr<org::sem::SemId<org::sem::BlockDynamicFallback>>("BlockDynamicFallback")
    .property("name", &org::sem::BlockDynamicFallback::name)
    .function("getKind", static_cast<OrgSemKind(org::sem::BlockDynamicFallback::*)() const>(&org::sem::BlockDynamicFallback::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::BlockDynamicFallback>>)
    ;
  emscripten::class_<org::sem::BlockExample, emscripten::base<org::sem::Block>>("BlockExample")
    .smart_ptr<org::sem::SemId<org::sem::BlockExample>>("BlockExample")
    .function("getKind", static_cast<OrgSemKind(org::sem::BlockExample::*)() const>(&org::sem::BlockExample::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::BlockExample>>)
    ;
  emscripten::class_<org::sem::BlockExport, emscripten::base<org::sem::Block>>("BlockExport")
    .smart_ptr<org::sem::SemId<org::sem::BlockExport>>("BlockExport")
    .property("exporter", &org::sem::BlockExport::exporter)
    .property("content", &org::sem::BlockExport::content)
    .function("getKind", static_cast<OrgSemKind(org::sem::BlockExport::*)() const>(&org::sem::BlockExport::getKind))
    .function("getPlacement", static_cast<hstd::Opt<hstd::Str>(org::sem::BlockExport::*)() const>(&org::sem::BlockExport::getPlacement))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::BlockExport>>)
    ;
  emscripten::class_<org::sem::BlockAdmonition, emscripten::base<org::sem::Block>>("BlockAdmonition")
    .smart_ptr<org::sem::SemId<org::sem::BlockAdmonition>>("BlockAdmonition")
    .function("getKind", static_cast<OrgSemKind(org::sem::BlockAdmonition::*)() const>(&org::sem::BlockAdmonition::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::BlockAdmonition>>)
    ;
  emscripten::class_<org::sem::BlockCodeEvalResult, emscripten::base<org::sem::Block>>("BlockCodeEvalResult")
    .smart_ptr<org::sem::SemId<org::sem::BlockCodeEvalResult>>("BlockCodeEvalResult")
    .property("raw", &org::sem::BlockCodeEvalResult::raw)
    .property("node", &org::sem::BlockCodeEvalResult::node)
    .function("getKind", static_cast<OrgSemKind(org::sem::BlockCodeEvalResult::*)() const>(&org::sem::BlockCodeEvalResult::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::BlockCodeEvalResult>>)
    ;
  emscripten::class_<org::sem::BlockCode, emscripten::base<org::sem::Block>>("BlockCode")
    .smart_ptr<org::sem::SemId<org::sem::BlockCode>>("BlockCode")
    .property("lang", &org::sem::BlockCode::lang)
    .property("exports", &org::sem::BlockCode::exports)
    .property("result", &org::sem::BlockCode::result)
    .property("lines", &org::sem::BlockCode::lines)
    .property("cache", &org::sem::BlockCode::cache)
    .property("eval", &org::sem::BlockCode::eval)
    .property("noweb", &org::sem::BlockCode::noweb)
    .property("hlines", &org::sem::BlockCode::hlines)
    .property("tangle", &org::sem::BlockCode::tangle)
    .property("switches", &org::sem::BlockCode::switches)
    .function("getKind", static_cast<OrgSemKind(org::sem::BlockCode::*)() const>(&org::sem::BlockCode::getKind))
    .function("getVariable", static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::BlockCode::*)(hstd::Str const&) const>(&org::sem::BlockCode::getVariable))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::BlockCode>>)
    ;
  emscripten::class_<org::sem::Table, emscripten::base<org::sem::Block>>("Table")
    .smart_ptr<org::sem::SemId<org::sem::Table>>("Table")
    .property("rows", &org::sem::Table::rows)
    .property("isBlock", &org::sem::Table::isBlock)
    .function("getKind", static_cast<OrgSemKind(org::sem::Table::*)() const>(&org::sem::Table::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Table>>)
    ;
  emscripten::class_<org::sem::Attached, emscripten::base<org::sem::LineCommand>>("Attached")
    .smart_ptr<org::sem::SemId<org::sem::Attached>>("Attached")
    ;
  emscripten::class_<org::imm::ImmBlockCenter, emscripten::base<org::imm::ImmBlock>>("ImmBlockCenter")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmBlockCenter::*)() const>(&org::imm::ImmBlockCenter::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmBlockCenter::*)(org::imm::ImmBlockCenter const&) const>(&org::imm::ImmBlockCenter::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmBlockQuote, emscripten::base<org::imm::ImmBlock>>("ImmBlockQuote")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmBlockQuote::*)() const>(&org::imm::ImmBlockQuote::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmBlockQuote::*)(org::imm::ImmBlockQuote const&) const>(&org::imm::ImmBlockQuote::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmBlockVerse, emscripten::base<org::imm::ImmBlock>>("ImmBlockVerse")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmBlockVerse::*)() const>(&org::imm::ImmBlockVerse::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmBlockVerse::*)(org::imm::ImmBlockVerse const&) const>(&org::imm::ImmBlockVerse::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmBlockDynamicFallback, emscripten::base<org::imm::ImmBlock>>("ImmBlockDynamicFallback")
    .property("name", &org::imm::ImmBlockDynamicFallback::name)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmBlockDynamicFallback::*)() const>(&org::imm::ImmBlockDynamicFallback::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmBlockDynamicFallback::*)(org::imm::ImmBlockDynamicFallback const&) const>(&org::imm::ImmBlockDynamicFallback::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmBlockExample, emscripten::base<org::imm::ImmBlock>>("ImmBlockExample")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmBlockExample::*)() const>(&org::imm::ImmBlockExample::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmBlockExample::*)(org::imm::ImmBlockExample const&) const>(&org::imm::ImmBlockExample::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmBlockExport, emscripten::base<org::imm::ImmBlock>>("ImmBlockExport")
    .property("exporter", &org::imm::ImmBlockExport::exporter)
    .property("content", &org::imm::ImmBlockExport::content)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmBlockExport::*)() const>(&org::imm::ImmBlockExport::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmBlockExport::*)(org::imm::ImmBlockExport const&) const>(&org::imm::ImmBlockExport::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmBlockAdmonition, emscripten::base<org::imm::ImmBlock>>("ImmBlockAdmonition")
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmBlockAdmonition::*)() const>(&org::imm::ImmBlockAdmonition::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmBlockAdmonition::*)(org::imm::ImmBlockAdmonition const&) const>(&org::imm::ImmBlockAdmonition::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmBlockCodeEvalResult, emscripten::base<org::imm::ImmBlock>>("ImmBlockCodeEvalResult")
    .property("raw", &org::imm::ImmBlockCodeEvalResult::raw)
    .property("node", &org::imm::ImmBlockCodeEvalResult::node)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmBlockCodeEvalResult::*)() const>(&org::imm::ImmBlockCodeEvalResult::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmBlockCodeEvalResult::*)(org::imm::ImmBlockCodeEvalResult const&) const>(&org::imm::ImmBlockCodeEvalResult::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmBlockCode, emscripten::base<org::imm::ImmBlock>>("ImmBlockCode")
    .property("lang", &org::imm::ImmBlockCode::lang)
    .property("exports", &org::imm::ImmBlockCode::exports)
    .property("result", &org::imm::ImmBlockCode::result)
    .property("lines", &org::imm::ImmBlockCode::lines)
    .property("cache", &org::imm::ImmBlockCode::cache)
    .property("eval", &org::imm::ImmBlockCode::eval)
    .property("noweb", &org::imm::ImmBlockCode::noweb)
    .property("hlines", &org::imm::ImmBlockCode::hlines)
    .property("tangle", &org::imm::ImmBlockCode::tangle)
    .property("switches", &org::imm::ImmBlockCode::switches)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmBlockCode::*)() const>(&org::imm::ImmBlockCode::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmBlockCode::*)(org::imm::ImmBlockCode const&) const>(&org::imm::ImmBlockCode::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmTable, emscripten::base<org::imm::ImmBlock>>("ImmTable")
    .property("rows", &org::imm::ImmTable::rows)
    .property("isBlock", &org::imm::ImmTable::isBlock)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmTable::*)() const>(&org::imm::ImmTable::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmTable::*)(org::imm::ImmTable const&) const>(&org::imm::ImmTable::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmAttached, emscripten::base<org::imm::ImmLineCommand>>("ImmAttached")
    .function("__eq__", static_cast<bool(org::imm::ImmAttached::*)(org::imm::ImmAttached const&) const>(&org::imm::ImmAttached::operator==))
    ;
  emscripten::class_<org::imm::ImmAdapterLineCommandAPI, emscripten::base<org::imm::ImmAdapterCmdAPI>>("ImmAdapterLineCommandAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterCmdCustomArgsAPI, emscripten::base<org::imm::ImmAdapterCmdAPI>>("ImmAdapterCmdCustomArgsAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterCmdTblfmAPI, emscripten::base<org::imm::ImmAdapterCmdAPI>>("ImmAdapterCmdTblfmAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterBlockAPI, emscripten::base<org::imm::ImmAdapterCmdAPI>>("ImmAdapterBlockAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterCellAPI, emscripten::base<org::imm::ImmAdapterCmdAPI>>("ImmAdapterCellAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterRowAPI, emscripten::base<org::imm::ImmAdapterCmdAPI>>("ImmAdapterRowAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>, emscripten::base<org::imm::ImmAdapterCmdCustomRawAPI>>("ImmCmdCustomRawAdapter")
    .function("getValue", static_cast<org::imm::ImmCmdCustomRawValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>, emscripten::base<org::imm::ImmAdapterCmdCustomTextAPI>>("ImmCmdCustomTextAdapter")
    .function("getValue", static_cast<org::imm::ImmCmdCustomTextValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmLink>, emscripten::base<org::imm::ImmAdapterLinkAPI>>("ImmLinkAdapter")
    .function("getValue", static_cast<org::imm::ImmLinkValueRead(org::imm::ImmAdapterT<org::imm::ImmLink>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmLink>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmBlockComment>, emscripten::base<org::imm::ImmAdapterBlockCommentAPI>>("ImmBlockCommentAdapter")
    .function("getValue", static_cast<org::imm::ImmBlockCommentValueRead(org::imm::ImmAdapterT<org::imm::ImmBlockComment>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockComment>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmParagraph>, emscripten::base<org::imm::ImmAdapterParagraphAPI>>("ImmParagraphAdapter")
    .function("getValue", static_cast<org::imm::ImmParagraphValueRead(org::imm::ImmAdapterT<org::imm::ImmParagraph>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmParagraph>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmList>, emscripten::base<org::imm::ImmAdapterListAPI>>("ImmListAdapter")
    .function("getValue", static_cast<org::imm::ImmListValueRead(org::imm::ImmAdapterT<org::imm::ImmList>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmList>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmHashTag>, emscripten::base<org::imm::ImmAdapterHashTagAPI>>("ImmHashTagAdapter")
    .function("getValue", static_cast<org::imm::ImmHashTagValueRead(org::imm::ImmAdapterT<org::imm::ImmHashTag>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmHashTag>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>, emscripten::base<org::imm::ImmAdapterInlineFootnoteAPI>>("ImmInlineFootnoteAdapter")
    .function("getValue", static_cast<org::imm::ImmInlineFootnoteValueRead(org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmEscaped>, emscripten::base<org::imm::ImmAdapterEscapedAPI>>("ImmEscapedAdapter")
    .function("getValue", static_cast<org::imm::ImmEscapedValueRead(org::imm::ImmAdapterT<org::imm::ImmEscaped>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmEscaped>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmNewline>, emscripten::base<org::imm::ImmAdapterNewlineAPI>>("ImmNewlineAdapter")
    .function("getValue", static_cast<org::imm::ImmNewlineValueRead(org::imm::ImmAdapterT<org::imm::ImmNewline>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmNewline>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmSpace>, emscripten::base<org::imm::ImmAdapterSpaceAPI>>("ImmSpaceAdapter")
    .function("getValue", static_cast<org::imm::ImmSpaceValueRead(org::imm::ImmAdapterT<org::imm::ImmSpace>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSpace>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmWord>, emscripten::base<org::imm::ImmAdapterWordAPI>>("ImmWordAdapter")
    .function("getValue", static_cast<org::imm::ImmWordValueRead(org::imm::ImmAdapterT<org::imm::ImmWord>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmWord>::getValue))
    ;
}

void subdivide_8(org::bind::js::type_registration_guard& g) {
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmAtMention>, emscripten::base<org::imm::ImmAdapterAtMentionAPI>>("ImmAtMentionAdapter")
    .function("getValue", static_cast<org::imm::ImmAtMentionValueRead(org::imm::ImmAdapterT<org::imm::ImmAtMention>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmAtMention>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmRawText>, emscripten::base<org::imm::ImmAdapterRawTextAPI>>("ImmRawTextAdapter")
    .function("getValue", static_cast<org::imm::ImmRawTextValueRead(org::imm::ImmAdapterT<org::imm::ImmRawText>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmRawText>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmPunctuation>, emscripten::base<org::imm::ImmAdapterPunctuationAPI>>("ImmPunctuationAdapter")
    .function("getValue", static_cast<org::imm::ImmPunctuationValueRead(org::imm::ImmAdapterT<org::imm::ImmPunctuation>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmPunctuation>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmPlaceholder>, emscripten::base<org::imm::ImmAdapterPlaceholderAPI>>("ImmPlaceholderAdapter")
    .function("getValue", static_cast<org::imm::ImmPlaceholderValueRead(org::imm::ImmAdapterT<org::imm::ImmPlaceholder>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmPlaceholder>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmBigIdent>, emscripten::base<org::imm::ImmAdapterBigIdentAPI>>("ImmBigIdentAdapter")
    .function("getValue", static_cast<org::imm::ImmBigIdentValueRead(org::imm::ImmAdapterT<org::imm::ImmBigIdent>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBigIdent>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmTextTarget>, emscripten::base<org::imm::ImmAdapterTextTargetAPI>>("ImmTextTargetAdapter")
    .function("getValue", static_cast<org::imm::ImmTextTargetValueRead(org::imm::ImmAdapterT<org::imm::ImmTextTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTextTarget>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmBold>, emscripten::base<org::imm::ImmAdapterBoldAPI>>("ImmBoldAdapter")
    .function("getValue", static_cast<org::imm::ImmBoldValueRead(org::imm::ImmAdapterT<org::imm::ImmBold>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBold>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmUnderline>, emscripten::base<org::imm::ImmAdapterUnderlineAPI>>("ImmUnderlineAdapter")
    .function("getValue", static_cast<org::imm::ImmUnderlineValueRead(org::imm::ImmAdapterT<org::imm::ImmUnderline>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmUnderline>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmMonospace>, emscripten::base<org::imm::ImmAdapterMonospaceAPI>>("ImmMonospaceAdapter")
    .function("getValue", static_cast<org::imm::ImmMonospaceValueRead(org::imm::ImmAdapterT<org::imm::ImmMonospace>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmMonospace>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmMarkQuote>, emscripten::base<org::imm::ImmAdapterMarkQuoteAPI>>("ImmMarkQuoteAdapter")
    .function("getValue", static_cast<org::imm::ImmMarkQuoteValueRead(org::imm::ImmAdapterT<org::imm::ImmMarkQuote>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmMarkQuote>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmRadioTarget>, emscripten::base<org::imm::ImmAdapterRadioTargetAPI>>("ImmRadioTargetAdapter")
    .function("getValue", static_cast<org::imm::ImmRadioTargetValueRead(org::imm::ImmAdapterT<org::imm::ImmRadioTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmRadioTarget>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmVerbatim>, emscripten::base<org::imm::ImmAdapterVerbatimAPI>>("ImmVerbatimAdapter")
    .function("getValue", static_cast<org::imm::ImmVerbatimValueRead(org::imm::ImmAdapterT<org::imm::ImmVerbatim>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmVerbatim>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmItalic>, emscripten::base<org::imm::ImmAdapterItalicAPI>>("ImmItalicAdapter")
    .function("getValue", static_cast<org::imm::ImmItalicValueRead(org::imm::ImmAdapterT<org::imm::ImmItalic>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmItalic>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmStrike>, emscripten::base<org::imm::ImmAdapterStrikeAPI>>("ImmStrikeAdapter")
    .function("getValue", static_cast<org::imm::ImmStrikeValueRead(org::imm::ImmAdapterT<org::imm::ImmStrike>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmStrike>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmPar>, emscripten::base<org::imm::ImmAdapterParAPI>>("ImmParAdapter")
    .function("getValue", static_cast<org::imm::ImmParValueRead(org::imm::ImmAdapterT<org::imm::ImmPar>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmPar>::getValue))
    ;
  emscripten::class_<org::sem::CmdCaption, emscripten::base<org::sem::Attached>>("CmdCaption")
    .smart_ptr<org::sem::SemId<org::sem::CmdCaption>>("CmdCaption")
    .property("text", &org::sem::CmdCaption::text)
    .function("getKind", static_cast<OrgSemKind(org::sem::CmdCaption::*)() const>(&org::sem::CmdCaption::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::CmdCaption>>)
    ;
  emscripten::class_<org::sem::CmdColumns, emscripten::base<org::sem::Attached>>("CmdColumns")
    .smart_ptr<org::sem::SemId<org::sem::CmdColumns>>("CmdColumns")
    .property("view", &org::sem::CmdColumns::view)
    .function("getKind", static_cast<OrgSemKind(org::sem::CmdColumns::*)() const>(&org::sem::CmdColumns::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::CmdColumns>>)
    ;
  emscripten::class_<org::sem::CmdName, emscripten::base<org::sem::Attached>>("CmdName")
    .smart_ptr<org::sem::SemId<org::sem::CmdName>>("CmdName")
    .property("name", &org::sem::CmdName::name)
    .function("getKind", static_cast<OrgSemKind(org::sem::CmdName::*)() const>(&org::sem::CmdName::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::CmdName>>)
    ;
  emscripten::class_<org::sem::CmdCall, emscripten::base<org::sem::Attached>>("CmdCall")
    .smart_ptr<org::sem::SemId<org::sem::CmdCall>>("CmdCall")
    .property("name", &org::sem::CmdCall::name)
    .property("fileName", &org::sem::CmdCall::fileName)
    .property("insideHeaderAttrs", &org::sem::CmdCall::insideHeaderAttrs)
    .property("callAttrs", &org::sem::CmdCall::callAttrs)
    .property("endHeaderAttrs", &org::sem::CmdCall::endHeaderAttrs)
    .property("result", &org::sem::CmdCall::result)
    .function("getKind", static_cast<OrgSemKind(org::sem::CmdCall::*)() const>(&org::sem::CmdCall::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::CmdCall>>)
    ;
  emscripten::class_<org::sem::CmdAttr, emscripten::base<org::sem::Attached>>("CmdAttr")
    .smart_ptr<org::sem::SemId<org::sem::CmdAttr>>("CmdAttr")
    .property("target", &org::sem::CmdAttr::target)
    .function("getKind", static_cast<OrgSemKind(org::sem::CmdAttr::*)() const>(&org::sem::CmdAttr::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::CmdAttr>>)
    ;
  emscripten::class_<org::sem::CmdExport, emscripten::base<org::sem::Attached>>("CmdExport")
    .smart_ptr<org::sem::SemId<org::sem::CmdExport>>("CmdExport")
    .property("exporter", &org::sem::CmdExport::exporter)
    .property("content", &org::sem::CmdExport::content)
    .function("getKind", static_cast<OrgSemKind(org::sem::CmdExport::*)() const>(&org::sem::CmdExport::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::CmdExport>>)
    ;
  emscripten::class_<org::imm::ImmCmdCaption, emscripten::base<org::imm::ImmAttached>>("ImmCmdCaption")
    .property("text", &org::imm::ImmCmdCaption::text)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmCmdCaption::*)() const>(&org::imm::ImmCmdCaption::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCmdCaption::*)(org::imm::ImmCmdCaption const&) const>(&org::imm::ImmCmdCaption::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdColumns, emscripten::base<org::imm::ImmAttached>>("ImmCmdColumns")
    .property("view", &org::imm::ImmCmdColumns::view)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmCmdColumns::*)() const>(&org::imm::ImmCmdColumns::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCmdColumns::*)(org::imm::ImmCmdColumns const&) const>(&org::imm::ImmCmdColumns::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdName, emscripten::base<org::imm::ImmAttached>>("ImmCmdName")
    .property("name", &org::imm::ImmCmdName::name)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmCmdName::*)() const>(&org::imm::ImmCmdName::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCmdName::*)(org::imm::ImmCmdName const&) const>(&org::imm::ImmCmdName::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdCall, emscripten::base<org::imm::ImmAttached>>("ImmCmdCall")
    .property("name", &org::imm::ImmCmdCall::name)
    .property("fileName", &org::imm::ImmCmdCall::fileName)
    .property("insideHeaderAttrs", &org::imm::ImmCmdCall::insideHeaderAttrs)
    .property("callAttrs", &org::imm::ImmCmdCall::callAttrs)
    .property("endHeaderAttrs", &org::imm::ImmCmdCall::endHeaderAttrs)
    .property("result", &org::imm::ImmCmdCall::result)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmCmdCall::*)() const>(&org::imm::ImmCmdCall::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCmdCall::*)(org::imm::ImmCmdCall const&) const>(&org::imm::ImmCmdCall::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdAttr, emscripten::base<org::imm::ImmAttached>>("ImmCmdAttr")
    .property("target", &org::imm::ImmCmdAttr::target)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmCmdAttr::*)() const>(&org::imm::ImmCmdAttr::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCmdAttr::*)(org::imm::ImmCmdAttr const&) const>(&org::imm::ImmCmdAttr::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdExport, emscripten::base<org::imm::ImmAttached>>("ImmCmdExport")
    .property("exporter", &org::imm::ImmCmdExport::exporter)
    .property("content", &org::imm::ImmCmdExport::content)
    .function("getKind", static_cast<OrgSemKind(org::imm::ImmCmdExport::*)() const>(&org::imm::ImmCmdExport::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCmdExport::*)(org::imm::ImmCmdExport const&) const>(&org::imm::ImmCmdExport::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmAdapterAttachedAPI, emscripten::base<org::imm::ImmAdapterLineCommandAPI>>("ImmAdapterAttachedAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>, emscripten::base<org::imm::ImmAdapterCmdCustomArgsAPI>>("ImmCmdCustomArgsAdapter")
    .function("getValue", static_cast<org::imm::ImmCmdCustomArgsValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>, emscripten::base<org::imm::ImmAdapterCmdTblfmAPI>>("ImmCmdTblfmAdapter")
    .function("getValue", static_cast<org::imm::ImmCmdTblfmValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterBlockCenterAPI, emscripten::base<org::imm::ImmAdapterBlockAPI>>("ImmAdapterBlockCenterAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterBlockQuoteAPI, emscripten::base<org::imm::ImmAdapterBlockAPI>>("ImmAdapterBlockQuoteAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterBlockVerseAPI, emscripten::base<org::imm::ImmAdapterBlockAPI>>("ImmAdapterBlockVerseAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterBlockExampleAPI, emscripten::base<org::imm::ImmAdapterBlockAPI>>("ImmAdapterBlockExampleAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterInlineExportAPI, emscripten::base<org::imm::ImmAdapterBlockAPI>>("ImmAdapterInlineExportAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterCmdExportAPI, emscripten::base<org::imm::ImmAdapterBlockAPI>>("ImmAdapterCmdExportAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterBlockExportAPI, emscripten::base<org::imm::ImmAdapterBlockAPI>>("ImmAdapterBlockExportAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterBlockDynamicFallbackAPI, emscripten::base<org::imm::ImmAdapterBlockAPI>>("ImmAdapterBlockDynamicFallbackAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterBlockAdmonitionAPI, emscripten::base<org::imm::ImmAdapterBlockAPI>>("ImmAdapterBlockAdmonitionAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterBlockCodeEvalResultAPI, emscripten::base<org::imm::ImmAdapterBlockAPI>>("ImmAdapterBlockCodeEvalResultAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterBlockCodeAPI, emscripten::base<org::imm::ImmAdapterBlockAPI>>("ImmAdapterBlockCodeAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterTableAPI, emscripten::base<org::imm::ImmAdapterBlockAPI>>("ImmAdapterTableAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCell>, emscripten::base<org::imm::ImmAdapterCellAPI>>("ImmCellAdapter")
    .function("getValue", static_cast<org::imm::ImmCellValueRead(org::imm::ImmAdapterT<org::imm::ImmCell>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCell>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmRow>, emscripten::base<org::imm::ImmAdapterRowAPI>>("ImmRowAdapter")
    .function("getValue", static_cast<org::imm::ImmRowValueRead(org::imm::ImmAdapterT<org::imm::ImmRow>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmRow>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterCmdCaptionAPI, emscripten::base<org::imm::ImmAdapterAttachedAPI>>("ImmAdapterCmdCaptionAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterCmdColumnsAPI, emscripten::base<org::imm::ImmAdapterAttachedAPI>>("ImmAdapterCmdColumnsAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterCmdNameAPI, emscripten::base<org::imm::ImmAdapterAttachedAPI>>("ImmAdapterCmdNameAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterCmdCallAPI, emscripten::base<org::imm::ImmAdapterAttachedAPI>>("ImmAdapterCmdCallAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterCmdResultsAPI, emscripten::base<org::imm::ImmAdapterAttachedAPI>>("ImmAdapterCmdResultsAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterCmdAttrAPI, emscripten::base<org::imm::ImmAdapterAttachedAPI>>("ImmAdapterCmdAttrAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmBlockCenter>, emscripten::base<org::imm::ImmAdapterBlockCenterAPI>>("ImmBlockCenterAdapter")
    .function("getValue", static_cast<org::imm::ImmBlockCenterValueRead(org::imm::ImmAdapterT<org::imm::ImmBlockCenter>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCenter>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmBlockQuote>, emscripten::base<org::imm::ImmAdapterBlockQuoteAPI>>("ImmBlockQuoteAdapter")
    .function("getValue", static_cast<org::imm::ImmBlockQuoteValueRead(org::imm::ImmAdapterT<org::imm::ImmBlockQuote>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockQuote>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmBlockVerse>, emscripten::base<org::imm::ImmAdapterBlockVerseAPI>>("ImmBlockVerseAdapter")
    .function("getValue", static_cast<org::imm::ImmBlockVerseValueRead(org::imm::ImmAdapterT<org::imm::ImmBlockVerse>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockVerse>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmBlockExample>, emscripten::base<org::imm::ImmAdapterBlockExampleAPI>>("ImmBlockExampleAdapter")
    .function("getValue", static_cast<org::imm::ImmBlockExampleValueRead(org::imm::ImmAdapterT<org::imm::ImmBlockExample>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockExample>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmInlineExport>, emscripten::base<org::imm::ImmAdapterInlineExportAPI>>("ImmInlineExportAdapter")
    .function("getValue", static_cast<org::imm::ImmInlineExportValueRead(org::imm::ImmAdapterT<org::imm::ImmInlineExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmInlineExport>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCmdExport>, emscripten::base<org::imm::ImmAdapterCmdExportAPI>>("ImmCmdExportAdapter")
    .function("getValue", static_cast<org::imm::ImmCmdExportValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdExport>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmBlockExport>, emscripten::base<org::imm::ImmAdapterBlockExportAPI>>("ImmBlockExportAdapter")
    .function("getValue", static_cast<org::imm::ImmBlockExportValueRead(org::imm::ImmAdapterT<org::imm::ImmBlockExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockExport>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>, emscripten::base<org::imm::ImmAdapterBlockDynamicFallbackAPI>>("ImmBlockDynamicFallbackAdapter")
    .function("getValue", static_cast<org::imm::ImmBlockDynamicFallbackValueRead(org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition>, emscripten::base<org::imm::ImmAdapterBlockAdmonitionAPI>>("ImmBlockAdmonitionAdapter")
    .function("getValue", static_cast<org::imm::ImmBlockAdmonitionValueRead(org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>, emscripten::base<org::imm::ImmAdapterBlockCodeEvalResultAPI>>("ImmBlockCodeEvalResultAdapter")
    .function("getValue", static_cast<org::imm::ImmBlockCodeEvalResultValueRead(org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmBlockCode>, emscripten::base<org::imm::ImmAdapterBlockCodeAPI>>("ImmBlockCodeAdapter")
    .function("getValue", static_cast<org::imm::ImmBlockCodeValueRead(org::imm::ImmAdapterT<org::imm::ImmBlockCode>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCode>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmTable>, emscripten::base<org::imm::ImmAdapterTableAPI>>("ImmTableAdapter")
    .function("getValue", static_cast<org::imm::ImmTableValueRead(org::imm::ImmAdapterT<org::imm::ImmTable>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTable>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCmdCaption>, emscripten::base<org::imm::ImmAdapterCmdCaptionAPI>>("ImmCmdCaptionAdapter")
    .function("getValue", static_cast<org::imm::ImmCmdCaptionValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdCaption>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCaption>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCmdColumns>, emscripten::base<org::imm::ImmAdapterCmdColumnsAPI>>("ImmCmdColumnsAdapter")
    .function("getValue", static_cast<org::imm::ImmCmdColumnsValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdColumns>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdColumns>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCmdName>, emscripten::base<org::imm::ImmAdapterCmdNameAPI>>("ImmCmdNameAdapter")
    .function("getValue", static_cast<org::imm::ImmCmdNameValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdName>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdName>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCmdCall>, emscripten::base<org::imm::ImmAdapterCmdCallAPI>>("ImmCmdCallAdapter")
    .function("getValue", static_cast<org::imm::ImmCmdCallValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getValue))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCmdAttr>, emscripten::base<org::imm::ImmAdapterCmdAttrAPI>>("ImmCmdAttrAdapter")
    .function("getValue", static_cast<org::imm::ImmCmdAttrValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdAttr>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdAttr>::getValue))
    ;
  org::bind::js::bind_enum<CheckboxState>("CheckboxState");
  org::bind::js::bind_enum<SubtreeTodoSource>("SubtreeTodoSource");
  org::bind::js::bind_enum<ListFormattingMode>("ListFormattingMode");
  org::bind::js::bind_enum<InitialSubtreeVisibility>("InitialSubtreeVisibility");
  org::bind::js::bind_enum<BlockCodeResults>("BlockCodeResults");
  org::bind::js::bind_enum<BlockCodeExports>("BlockCodeExports");
  org::bind::js::bind_enum<OrgSpecName>("OrgSpecName");
  org::bind::js::bind_enum<OrgNodeKind>("OrgNodeKind");
  org::bind::js::bind_enum<OrgTokenKind>("OrgTokenKind");
  org::bind::js::bind_enum<OrgJsonKind>("OrgJsonKind");
  org::bind::js::bind_enum<OrgSemKind>("OrgSemKind");
  org::bind::js::bind_enum<org::AstTrackingGroup::Kind>("OrgAstTrackingGroupKind");
  org::bind::js::bind_enum<org::graph::MapLink::Kind>("OrgGraphMapLinkKind");
  emscripten::function("newSemTimeStatic", static_cast<org::sem::SemId<org::sem::Time>(*)(hstd::UserTimeBreakdown const&, bool)>(&org::newSemTimeStatic));
  emscripten::function("parseFile", static_cast<org::sem::SemId<org::sem::Org>(*)(std::string, std::shared_ptr<org::OrgParseParameters> const&)>(&org::parseFile));
  emscripten::function("parseString", static_cast<org::sem::SemId<org::sem::Org>(*)(std::string const)>(&org::parseString));
  emscripten::function("parseStringOpts", static_cast<org::sem::SemId<org::sem::Org>(*)(std::string const, std::shared_ptr<org::OrgParseParameters> const&)>(&org::parseStringOpts));
  emscripten::function("parseDirectoryOpts", static_cast<std::optional<org::sem::SemId<org::sem::Org>>(*)(std::string const&, std::shared_ptr<org::OrgDirectoryParseParameters> const&)>(&org::parseDirectoryOpts));
  emscripten::function("parseFileWithIncludes", static_cast<org::sem::SemId<org::sem::File>(*)(std::string const&, std::shared_ptr<org::OrgDirectoryParseParameters> const&)>(&org::parseFileWithIncludes));
  emscripten::function("initImmutableAstContext", static_cast<std::shared_ptr<org::imm::ImmAstContext>(*)()>(&org::initImmutableAstContext));
  emscripten::function("asOneNode", static_cast<org::sem::SemId<org::sem::Org>(*)(org::sem::SemId<org::sem::Org> const&)>(&org::asOneNode));
  emscripten::function("formatToString", static_cast<std::string(*)(org::sem::SemId<org::sem::Org>)>(&org::formatToString));
  emscripten::function("exportToYamlString", static_cast<std::string(*)(org::sem::SemId<org::sem::Org> const&, org::OrgYamlExportOpts const&)>(&org::exportToYamlString));
  emscripten::function("exportToYamlFile", static_cast<void(*)(org::sem::SemId<org::sem::Org> const&, std::string, org::OrgYamlExportOpts const&)>(&org::exportToYamlFile));
  emscripten::function("exportToJsonString", static_cast<std::string(*)(org::sem::SemId<org::sem::Org> const&)>(&org::exportToJsonString));
  emscripten::function("exportToJsonFile", static_cast<void(*)(org::sem::SemId<org::sem::Org> const&, std::string)>(&org::exportToJsonFile));
  emscripten::function("readProtobufFile", static_cast<org::sem::SemId<org::sem::Document>(*)(std::string const&)>(&org::readProtobufFile));
  emscripten::function("exportToProtobufFile", static_cast<void(*)(org::sem::SemId<org::sem::Document>, std::string const&)>(&org::exportToProtobufFile));
  emscripten::function("exportToTreeString", static_cast<std::string(*)(org::sem::SemId<org::sem::Org> const&, org::OrgTreeExportOpts const&)>(&org::exportToTreeString));
  emscripten::function("exportToTreeFile", static_cast<void(*)(org::sem::SemId<org::sem::Org> const&, std::string, org::OrgTreeExportOpts const&)>(&org::exportToTreeFile));
  emscripten::function("getAstTrackingMap", static_cast<org::AstTrackingMap(*)(hstd::Vec<org::sem::SemId<org::sem::Org>> const&)>(&org::getAstTrackingMap));
  emscripten::function("getSubnodeGroups", static_cast<hstd::Vec<org::AstTrackingGroup>(*)(org::sem::SemId<org::sem::Org>, org::AstTrackingMap const&)>(&org::getSubnodeGroups));
  emscripten::function("annotateSequence", static_cast<hstd::Vec<hstd::SequenceAnnotation>(*)(hstd::Vec<hstd::SequenceSegmentGroup> const&, int, int)>(&hstd::annotateSequence));
  emscripten::function("initMapGraphState", static_cast<std::shared_ptr<org::graph::MapGraphState>(*)(std::shared_ptr<org::imm::ImmAstContext>)>(&org::graph::initMapGraphState));
}

void subdivide_9(org::bind::js::type_registration_guard& g) {
  emscripten::function("serializeAstContextToText", static_cast<std::string(*)(std::shared_ptr<org::imm::ImmAstContext> const&)>(&org::imm::serializeToText));
  emscripten::function("serializeAstContextFromText", static_cast<void(*)(std::string const&, std::shared_ptr<org::imm::ImmAstContext> const&)>(&org::imm::serializeFromText));
  emscripten::function("serializeMapGraphToText", static_cast<std::string(*)(std::shared_ptr<org::graph::MapGraph> const&)>(&org::imm::serializeToText));
  emscripten::function("serializeMapGraphFromText", static_cast<void(*)(std::string const&, std::shared_ptr<org::graph::MapGraph> const&)>(&org::imm::serializeFromText));
  emscripten::function("serializeFromTextToTreeDump", static_cast<std::string(*)(std::string const&)>(&org::imm::serializeFromTextToTreeDump));
  haxorg_wasm_manual_register();
}

EMSCRIPTEN_BINDINGS(haxorg_wasm) {
  org::bind::js::type_registration_guard g;
  subdivide_0(g);
  subdivide_1(g);
  subdivide_2(g);
  subdivide_3(g);
  subdivide_4(g);
  subdivide_5(g);
  subdivide_6(g);
  subdivide_7(g);
  subdivide_8(g);
  subdivide_9(g);
}
/* clang-format on */