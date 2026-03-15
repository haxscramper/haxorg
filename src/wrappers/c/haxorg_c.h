/* clang-format off */
#include <wrappers/c/haxorg_c_api.h>
struct haxorg_UserTimeBreakdown_vtable {
  haxorg_StdOptionalOfInt const*(*)() get_year;
  haxorg_StdOptionalOfInt const*(*)() get_month;
  haxorg_StdOptionalOfInt const*(*)() get_day;
  haxorg_StdOptionalOfInt const*(*)() get_hour;
  haxorg_StdOptionalOfInt const*(*)() get_minute;
  haxorg_StdOptionalOfInt const*(*)() get_second;
  haxorg_StdOptionalOfStdString const*(*)() get_zone;
};

/// \brief {{REC:(hstd)}::REC:(UserTimeBreakdown)}
struct haxorg_UserTimeBreakdown {
  haxorg_UserTimeBreakdown_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_UserTimeBreakdown(haxorg_UserTimeBreakdown* obj);
struct haxorg_UserTime_vtable {};

/// \brief {{REC:(hstd)}::REC:(UserTime)}
struct haxorg_UserTime {
  haxorg_UserTime_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_UserTime(haxorg_UserTime* obj);
struct haxorg_ParseSourceFileId_vtable {};

/// \brief {{REC:(org)}::{REC:(parse)}::REC:(SourceFileId)}
struct haxorg_ParseSourceFileId {
  haxorg_ParseSourceFileId_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ParseSourceFileId(haxorg_ParseSourceFileId* obj);
struct haxorg_ParseSourceLoc_vtable {
  int const*(*)() get_line;
  int const*(*)() get_column;
  int const*(*)() get_pos;
  haxorg_ParseSourceFileId const*(*)() get_file_id;
};

/// \brief {{REC:(org)}::{REC:(parse)}::REC:(SourceLoc)}
struct haxorg_ParseSourceLoc {
  haxorg_ParseSourceLoc_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ParseSourceLoc(haxorg_ParseSourceLoc* obj);
struct haxorg_OrgJson_vtable {};

/// \brief {{REC:(org)}::{REC:(sem)}::REC:(OrgJson)}
struct haxorg_OrgJson {
  haxorg_OrgJson_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_OrgJson(haxorg_OrgJson* obj);
struct haxorg_Org_vtable {
  haxorg_StdOptionalOfParseSourceLoc const*(*)() get_loc;
  haxorg_CHstdVec const*(*)() get_subnodes;
};

/// \brief {{REC:(org)}::{REC:(sem)}::REC:(Org)}
struct haxorg_Org {
  haxorg_Org_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Org(haxorg_Org* obj);
struct haxorg_OperationsTracer_vtable {
  bool const*(*)() get_TraceState;
  bool const*(*)() get_traceToFile;
  bool const*(*)() get_traceToBuffer;
  bool const*(*)() get_traceStructured;
  bool const*(*)() get_traceColored;
  int const*(*)() get_activeLevel;
  haxorg_StdString const*(*)() get_traceBuffer;
};

/// \brief {{REC:(hstd)}::REC:(OperationsTracer)}
struct haxorg_OperationsTracer {
  haxorg_OperationsTracer_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_OperationsTracer(haxorg_OperationsTracer* obj);
struct haxorg_Cache_vtable {};

/// \brief {{REC:(hstd)}::{REC:(ext)}::REC:(Cache)}
struct haxorg_Cache {
  haxorg_Cache_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Cache(haxorg_Cache* obj);
struct haxorg_ParseOrgParseFragment_vtable {
  int const*(*)() get_baseLine;
  int const*(*)() get_baseCol;
  haxorg_StdString const*(*)() get_text;
};

/// \brief {{REC:(org)}::{REC:(parse)}::REC:(OrgParseFragment)}
struct haxorg_ParseOrgParseFragment {
  haxorg_ParseOrgParseFragment_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ParseOrgParseFragment(haxorg_ParseOrgParseFragment* obj);
struct haxorg_OrgParseParameters_vtable {
  haxorg_StdOptionalOfStdString const*(*)() get_baseTokenTracePath;
  haxorg_StdOptionalOfStdString const*(*)() get_tokenTracePath;
  haxorg_StdOptionalOfStdString const*(*)() get_parseTracePath;
  haxorg_StdOptionalOfStdString const*(*)() get_semTracePath;
};

/// \brief {{REC:(org)}::{REC:(parse)}::REC:(OrgParseParameters)}
struct haxorg_OrgParseParameters {
  haxorg_OrgParseParameters_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_OrgParseParameters(haxorg_OrgParseParameters* obj);
struct haxorg_OrgDirectoryParseParameters_vtable {};

/// \brief {{REC:(org)}::{REC:(parse)}::REC:(OrgDirectoryParseParameters)}
struct haxorg_OrgDirectoryParseParameters {
  haxorg_OrgDirectoryParseParameters_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_OrgDirectoryParseParameters(haxorg_OrgDirectoryParseParameters* obj);
struct haxorg_ParseContext_vtable {};

/// \brief {{REC:(org)}::{REC:(parse)}::REC:(ParseContext)}
struct haxorg_ParseContext {
  haxorg_ParseContext_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ParseContext(haxorg_ParseContext* obj);
struct haxorg_ImmReflFieldId_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmReflFieldId)}
struct haxorg_ImmReflFieldId {
  haxorg_ImmReflFieldId_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmReflFieldId(haxorg_ImmReflFieldId* obj);
struct haxorg_ImmId_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmId)}
struct haxorg_ImmId {
  haxorg_ImmId_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmId(haxorg_ImmId* obj);
struct haxorg_ImmOrg_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmOrg)}
struct haxorg_ImmOrg {
  haxorg_ImmOrg_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmOrg(haxorg_ImmOrg* obj);
struct haxorg_ImmPathStep_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmPathStep)}
struct haxorg_ImmPathStep {
  haxorg_ImmPathStep_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmPathStep(haxorg_ImmPathStep* obj);
struct haxorg_ImmPath_vtable {
  haxorg_ImmId const*(*)() get_root;
  haxorg_ImmPathStore const*(*)() get_path;
};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmPath)}
struct haxorg_ImmPath {
  haxorg_ImmPath_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmPath(haxorg_ImmPath* obj);
struct haxorg_ImmUniqId_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmUniqId)}
struct haxorg_ImmUniqId {
  haxorg_ImmUniqId_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmUniqId(haxorg_ImmUniqId* obj);
struct haxorg_ImmAstReplaceEpoch_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAstReplaceEpoch)}
struct haxorg_ImmAstReplaceEpoch {
  haxorg_ImmAstReplaceEpoch_vtable const* vtable;
  haxorg_ptr_payload data;
};

void haxorg_destroy_ImmAstReplaceEpoch(haxorg_ImmAstReplaceEpoch* obj);
struct haxorg_ImmAstContext_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAstContext)}
struct haxorg_ImmAstContext {
  haxorg_ImmAstContext_vtable const* vtable;
  haxorg_ptr_payload data;
};

void haxorg_destroy_ImmAstContext(haxorg_ImmAstContext* obj);
struct haxorg_ImmAstVersion_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAstVersion)}
struct haxorg_ImmAstVersion {
  haxorg_ImmAstVersion_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAstVersion(haxorg_ImmAstVersion* obj);
struct haxorg_ImmAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapter)}
struct haxorg_ImmAdapter {
  haxorg_ImmAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapter(haxorg_ImmAdapter* obj);
struct haxorg_ImmAdapterVirtualBase_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterVirtualBase)}
struct haxorg_ImmAdapterVirtualBase {
  haxorg_ImmAdapterVirtualBase_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterVirtualBase(haxorg_ImmAdapterVirtualBase* obj);
struct haxorg_OrgYamlExportOpts_vtable {
  bool const*(*)() get_skipNullFields;
  bool const*(*)() get_skipFalseFields;
  bool const*(*)() get_skipZeroFields;
  bool const*(*)() get_skipLocation;
  bool const*(*)() get_skipId;
};

/// \brief {{REC:(org)}::REC:(OrgYamlExportOpts)}
struct haxorg_OrgYamlExportOpts {
  haxorg_OrgYamlExportOpts_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_OrgYamlExportOpts(haxorg_OrgYamlExportOpts* obj);
struct haxorg_OrgTreeExportOpts_vtable {
  bool const*(*)() get_withLineCol;
  bool const*(*)() get_withOriginalId;
  bool const*(*)() get_withSubnodeIdx;
  bool const*(*)() get_skipEmptyFields;
  int const*(*)() get_startLevel;
  bool const*(*)() get_withColor;
  int const*(*)() get_maxDepth;
};

/// \brief {{REC:(org)}::REC:(OrgTreeExportOpts)}
struct haxorg_OrgTreeExportOpts {
  haxorg_OrgTreeExportOpts_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_OrgTreeExportOpts(haxorg_OrgTreeExportOpts* obj);
struct haxorg_AstTrackingPath_vtable {
  haxorg_CHstdVec const*(*)() get_path;
};

/// \brief {{REC:(org)}::REC:(AstTrackingPath)}
struct haxorg_AstTrackingPath {
  haxorg_AstTrackingPath_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_AstTrackingPath(haxorg_AstTrackingPath* obj);
struct haxorg_AstTrackingAlternatives_vtable {};

/// \brief {{REC:(org)}::REC:(AstTrackingAlternatives)}
struct haxorg_AstTrackingAlternatives {
  haxorg_AstTrackingAlternatives_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_AstTrackingAlternatives(haxorg_AstTrackingAlternatives* obj);
struct haxorg_AstTrackingGroup_vtable {};

/// \brief {{REC:(org)}::REC:(AstTrackingGroup)}
struct haxorg_AstTrackingGroup {
  haxorg_AstTrackingGroup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_AstTrackingGroup(haxorg_AstTrackingGroup* obj);
struct haxorg_AstTrackingMap_vtable {
  haxorg_HstdMapOfStrAstTrackingAlternatives const*(*)() get_footnotes;
  haxorg_HstdMapOfStrAstTrackingAlternatives const*(*)() get_subtrees;
  haxorg_HstdMapOfStrAstTrackingAlternatives const*(*)() get_names;
  haxorg_HstdMapOfStrAstTrackingAlternatives const*(*)() get_anchorTargets;
  haxorg_HstdMapOfStrAstTrackingAlternatives const*(*)() get_radioTargets;
  haxorg_HstdMapOfHashTagFlatAstTrackingAlternatives const*(*)() get_hashtagDefinitions;
};

/// \brief {{REC:(org)}::REC:(AstTrackingMap)}
struct haxorg_AstTrackingMap {
  haxorg_AstTrackingMap_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_AstTrackingMap(haxorg_AstTrackingMap* obj);
struct haxorg_SequenceSegment_vtable {
  int const*(*)() get_kind;
  int const*(*)() get_first;
  int const*(*)() get_last;
};

/// \brief {{REC:(hstd)}::REC:(SequenceSegment)}
struct haxorg_SequenceSegment {
  haxorg_SequenceSegment_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_SequenceSegment(haxorg_SequenceSegment* obj);
struct haxorg_SequenceSegmentGroup_vtable {
  int const*(*)() get_kind;
  haxorg_CHstdVec const*(*)() get_segments;
};

/// \brief {{REC:(hstd)}::REC:(SequenceSegmentGroup)}
struct haxorg_SequenceSegmentGroup {
  haxorg_SequenceSegmentGroup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_SequenceSegmentGroup(haxorg_SequenceSegmentGroup* obj);
struct haxorg_SequenceAnnotationTag_vtable {
  int const*(*)() get_groupKind;
  haxorg_CHstdVec const*(*)() get_segmentKinds;
};

/// \brief {{REC:(hstd)}::REC:(SequenceAnnotationTag)}
struct haxorg_SequenceAnnotationTag {
  haxorg_SequenceAnnotationTag_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_SequenceAnnotationTag(haxorg_SequenceAnnotationTag* obj);
struct haxorg_SequenceAnnotation_vtable {
  int const*(*)() get_first;
  int const*(*)() get_last;
  haxorg_CHstdVec const*(*)() get_annotations;
};

/// \brief {{REC:(hstd)}::REC:(SequenceAnnotation)}
struct haxorg_SequenceAnnotation {
  haxorg_SequenceAnnotation_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_SequenceAnnotation(haxorg_SequenceAnnotation* obj);
struct haxorg_GraphMapLink_vtable {};

/// \brief {{REC:(org)}::{REC:(graph)}::REC:(MapLink)}
struct haxorg_GraphMapLink {
  haxorg_GraphMapLink_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_GraphMapLink(haxorg_GraphMapLink* obj);
struct haxorg_GraphMapNodeProp_vtable {
  haxorg_ImmUniqId const*(*)() get_id;
  haxorg_CHstdVec const*(*)() get_unresolved;
};

/// \brief {{REC:(org)}::{REC:(graph)}::REC:(MapNodeProp)}
struct haxorg_GraphMapNodeProp {
  haxorg_GraphMapNodeProp_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_GraphMapNodeProp(haxorg_GraphMapNodeProp* obj);
struct haxorg_GraphMapEdgeProp_vtable {
  haxorg_GraphMapLink const*(*)() get_link;
};

/// \brief {{REC:(org)}::{REC:(graph)}::REC:(MapEdgeProp)}
struct haxorg_GraphMapEdgeProp {
  haxorg_GraphMapEdgeProp_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_GraphMapEdgeProp(haxorg_GraphMapEdgeProp* obj);
struct haxorg_GraphMapNode_vtable {
  haxorg_ImmUniqId const*(*)() get_id;
};

/// \brief {{REC:(org)}::{REC:(graph)}::REC:(MapNode)}
struct haxorg_GraphMapNode {
  haxorg_GraphMapNode_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_GraphMapNode(haxorg_GraphMapNode* obj);
struct haxorg_GraphMapEdge_vtable {
  haxorg_GraphMapNode const*(*)() get_source;
  haxorg_GraphMapNode const*(*)() get_target;
};

/// \brief {{REC:(org)}::{REC:(graph)}::REC:(MapEdge)}
struct haxorg_GraphMapEdge {
  haxorg_GraphMapEdge_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_GraphMapEdge(haxorg_GraphMapEdge* obj);
struct haxorg_GraphMapGraph_vtable {
  haxorg_GraphNodeProps const*(*)() get_nodeProps;
  haxorg_GraphEdgeProps const*(*)() get_edgeProps;
  haxorg_GraphAdjList const*(*)() get_adjList;
  haxorg_GraphAdjList const*(*)() get_adjListIn;
};

/// \brief {{REC:(org)}::{REC:(graph)}::REC:(MapGraph)}
struct haxorg_GraphMapGraph {
  haxorg_GraphMapGraph_vtable const* vtable;
  haxorg_ptr_payload data;
};

void haxorg_destroy_GraphMapGraph(haxorg_GraphMapGraph* obj);
struct haxorg_GraphMapConfig_vtable {
  haxorg_OperationsTracer const*(*)() get_dbg;
};

/// \brief {{REC:(org)}::{REC:(graph)}::REC:(MapConfig)}
struct haxorg_GraphMapConfig {
  haxorg_GraphMapConfig_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_GraphMapConfig(haxorg_GraphMapConfig* obj);
struct haxorg_GraphMapGraphState_vtable {
  haxorg_GraphMapGraph const*(*)() get_graph;
  haxorg_ImmAstContext const*(*)() get_ast;
};

/// \brief {{REC:(org)}::{REC:(graph)}::REC:(MapGraphState)}
struct haxorg_GraphMapGraphState {
  haxorg_GraphMapGraphState_vtable const* vtable;
  haxorg_ptr_payload data;
};

void haxorg_destroy_GraphMapGraphState(haxorg_GraphMapGraphState* obj);
struct haxorg_LispCode_vtable {
  haxorg_LispCodeData const*(*)() get_data;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(LispCode)}
struct haxorg_LispCode {
  haxorg_LispCode_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_LispCode(haxorg_LispCode* obj);
struct haxorg_Tblfm_vtable {
  haxorg_CHstdVec const*(*)() get_exprs;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Tblfm)}
struct haxorg_Tblfm {
  haxorg_Tblfm_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Tblfm(haxorg_Tblfm* obj);
struct haxorg_AttrValue_vtable {
  haxorg_OptOfStr const*(*)() get_name;
  haxorg_OptOfStr const*(*)() get_varname;
  haxorg_CHstdVec const*(*)() get_span;
  bool const*(*)() get_isQuoted;
  haxorg_AttrValueDataVariant const*(*)() get_data;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(AttrValue)}
struct haxorg_AttrValue {
  haxorg_AttrValue_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_AttrValue(haxorg_AttrValue* obj);
struct haxorg_HashTagFlat_vtable {
  haxorg_CHstdVec const*(*)() get_tags;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(HashTagFlat)}
struct haxorg_HashTagFlat {
  haxorg_HashTagFlat_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_HashTagFlat(haxorg_HashTagFlat* obj);
struct haxorg_TodoKeyword_vtable {
  haxorg_Str const*(*)() get_name;
  haxorg_OptOfStr const*(*)() get_shortcut;
  haxorg_TodoKeywordTransition const*(*)() get_onEnter;
  haxorg_TodoKeywordTransition const*(*)() get_onLeave;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(TodoKeyword)}
struct haxorg_TodoKeyword {
  haxorg_TodoKeyword_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_TodoKeyword(haxorg_TodoKeyword* obj);
struct haxorg_HashTagText_vtable {
  haxorg_Str const*(*)() get_head;
  haxorg_CHstdVec const*(*)() get_subtags;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(HashTagText)}
struct haxorg_HashTagText {
  haxorg_HashTagText_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_HashTagText(haxorg_HashTagText* obj);
struct haxorg_SubtreePath_vtable {
  haxorg_CHstdVec const*(*)() get_path;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(SubtreePath)}
struct haxorg_SubtreePath {
  haxorg_SubtreePath_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_SubtreePath(haxorg_SubtreePath* obj);
struct haxorg_LinkTarget_vtable {
  haxorg_LinkTargetData const*(*)() get_data;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(LinkTarget)}
struct haxorg_LinkTarget {
  haxorg_LinkTarget_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_LinkTarget(haxorg_LinkTarget* obj);
struct haxorg_SubtreeLogHead_vtable {
  haxorg_SubtreeLogHeadLogEntry const*(*)() get_log;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(SubtreeLogHead)}
struct haxorg_SubtreeLogHead {
  haxorg_SubtreeLogHead_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_SubtreeLogHead(haxorg_SubtreeLogHead* obj);
struct haxorg_SubtreeCompletion_vtable {
  int const*(*)() get_done;
  int const*(*)() get_full;
  bool const*(*)() get_isPercent;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(SubtreeCompletion)}
struct haxorg_SubtreeCompletion {
  haxorg_SubtreeCompletion_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_SubtreeCompletion(haxorg_SubtreeCompletion* obj);
struct haxorg_AttrList_vtable {
  haxorg_CHstdVec const*(*)() get_items;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(AttrList)}
struct haxorg_AttrList {
  haxorg_AttrList_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_AttrList(haxorg_AttrList* obj);
struct haxorg_AttrGroup_vtable {
  haxorg_AttrList const*(*)() get_positional;
  haxorg_HstdMapOfStrAttrList const*(*)() get_named;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(AttrGroup)}
struct haxorg_AttrGroup {
  haxorg_AttrGroup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_AttrGroup(haxorg_AttrGroup* obj);
struct haxorg_OrgCodeEvalInput_vtable {
  haxorg_AttrGroup const*(*)() get_blockAttrs;
  haxorg_Str const*(*)() get_tangledCode;
  haxorg_OptOfStr const*(*)() get_exportType;
  haxorg_OrgCodeEvalInputResultType const*(*)() get_resultType;
  haxorg_OrgCodeEvalInputResultFormat const*(*)() get_resultFormat;
  haxorg_OrgCodeEvalInputResultHandling const*(*)() get_resultHandling;
  haxorg_Str const*(*)() get_language;
  haxorg_CHstdVec const*(*)() get_argList;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(OrgCodeEvalInput)}
struct haxorg_OrgCodeEvalInput {
  haxorg_OrgCodeEvalInput_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_OrgCodeEvalInput(haxorg_OrgCodeEvalInput* obj);
struct haxorg_OrgCodeEvalOutput_vtable {
  haxorg_Str const*(*)() get_stdoutText;
  haxorg_Str const*(*)() get_stderrText;
  int const*(*)() get_code;
  haxorg_OptOfStr const*(*)() get_cmd;
  haxorg_CHstdVec const*(*)() get_args;
  haxorg_Str const*(*)() get_cwd;
  haxorg_AttrGroup const*(*)() get_appliedHeaderArg;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(OrgCodeEvalOutput)}
struct haxorg_OrgCodeEvalOutput {
  haxorg_OrgCodeEvalOutput_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_OrgCodeEvalOutput(haxorg_OrgCodeEvalOutput* obj);
struct haxorg_ColumnView_vtable {
  haxorg_CHstdVec const*(*)() get_columns;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(ColumnView)}
struct haxorg_ColumnView {
  haxorg_ColumnView_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ColumnView(haxorg_ColumnView* obj);
struct haxorg_BlockCodeLine_vtable {
  haxorg_CHstdVec const*(*)() get_parts;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(BlockCodeLine)}
struct haxorg_BlockCodeLine {
  haxorg_BlockCodeLine_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_BlockCodeLine(haxorg_BlockCodeLine* obj);
struct haxorg_DocumentExportConfig_vtable {
  haxorg_OptOfBool const*(*)() get_inlinetasks;
  haxorg_OptOfBool const*(*)() get_footnotes;
  haxorg_OptOfBool const*(*)() get_clock;
  haxorg_OptOfBool const*(*)() get_author;
  haxorg_OptOfBool const*(*)() get_emphasis;
  haxorg_OptOfBool const*(*)() get_specialStrings;
  haxorg_OptOfBool const*(*)() get_propertyDrawers;
  haxorg_OptOfBool const*(*)() get_statisticsCookies;
  haxorg_OptOfBool const*(*)() get_todoText;
  haxorg_OptOfBool const*(*)() get_smartQuotes;
  haxorg_OptOfBool const*(*)() get_fixedWidth;
  haxorg_OptOfBool const*(*)() get_timestamps;
  haxorg_OptOfBool const*(*)() get_preserveBreaks;
  haxorg_OptOfBool const*(*)() get_subSuperscripts;
  haxorg_OptOfBool const*(*)() get_expandLinks;
  haxorg_OptOfBool const*(*)() get_creator;
  haxorg_OptOfBool const*(*)() get_drawers;
  haxorg_OptOfBool const*(*)() get_date;
  haxorg_OptOfBool const*(*)() get_entities;
  haxorg_OptOfBool const*(*)() get_email;
  haxorg_OptOfBool const*(*)() get_sectionNumbers;
  haxorg_OptOfBool const*(*)() get_planning;
  haxorg_OptOfBool const*(*)() get_priority;
  haxorg_OptOfBool const*(*)() get_latex;
  haxorg_OptOfBool const*(*)() get_timestamp;
  haxorg_OptOfBool const*(*)() get_title;
  haxorg_OptOfBool const*(*)() get_tables;
  haxorg_OptOfInt const*(*)() get_headlineLevels;
  haxorg_DocumentExportConfigBrokenLinks const*(*)() get_brokenLinks;
  haxorg_DocumentExportConfigTocExport const*(*)() get_tocExport;
  haxorg_DocumentExportConfigTagExport const*(*)() get_tagExport;
  haxorg_DocumentExportConfigTaskFiltering const*(*)() get_taskFiltering;
  haxorg_DocumentExportConfigArchivedTrees const*(*)() get_archivedTrees;
  haxorg_DocumentExportConfigTocExport const*(*)() get_data;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(DocumentExportConfig)}
struct haxorg_DocumentExportConfig {
  haxorg_DocumentExportConfig_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_DocumentExportConfig(haxorg_DocumentExportConfig* obj);
struct haxorg_SubtreePeriod_vtable {
  haxorg_SubtreePeriodKind const*(*)() get_kind;
  haxorg_UserTime const*(*)() get_from;
  haxorg_OptOfUserTime const*(*)() get_to;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(SubtreePeriod)}
struct haxorg_SubtreePeriod {
  haxorg_SubtreePeriod_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_SubtreePeriod(haxorg_SubtreePeriod* obj);
struct haxorg_NamedProperty_vtable {
  haxorg_NamedPropertyData const*(*)() get_data;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(NamedProperty)}
struct haxorg_NamedProperty {
  haxorg_NamedProperty_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_NamedProperty(haxorg_NamedProperty* obj);
struct haxorg_OrgDiagnostics_vtable {
  haxorg_OrgDiagnosticsData const*(*)() get_data;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(OrgDiagnostics)}
struct haxorg_OrgDiagnostics {
  haxorg_OrgDiagnostics_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_OrgDiagnostics(haxorg_OrgDiagnostics* obj);
struct haxorg_NoNode_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(NoNode)}
struct haxorg_NoNode {
  haxorg_NoNode_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_NoNode(haxorg_NoNode* obj);
struct haxorg_ErrorItem_vtable {
  haxorg_OrgDiagnostics const*(*)() get_diag;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(ErrorItem)}
struct haxorg_ErrorItem {
  haxorg_ErrorItem_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ErrorItem(haxorg_ErrorItem* obj);
struct haxorg_ErrorGroup_vtable {
  haxorg_CHstdVec const*(*)() get_diagnostics;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(ErrorGroup)}
struct haxorg_ErrorGroup {
  haxorg_ErrorGroup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ErrorGroup(haxorg_ErrorGroup* obj);
struct haxorg_Stmt_vtable {
  haxorg_CHstdVec const*(*)() get_attached;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Stmt)}
struct haxorg_Stmt {
  haxorg_Stmt_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Stmt(haxorg_Stmt* obj);
struct haxorg_Inline_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Inline)}
struct haxorg_Inline {
  haxorg_Inline_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Inline(haxorg_Inline* obj);
struct haxorg_StmtList_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(StmtList)}
struct haxorg_StmtList {
  haxorg_StmtList_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_StmtList(haxorg_StmtList* obj);
struct haxorg_Empty_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Empty)}
struct haxorg_Empty {
  haxorg_Empty_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Empty(haxorg_Empty* obj);
struct haxorg_Leaf_vtable {
  haxorg_Str const*(*)() get_text;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Leaf)}
struct haxorg_Leaf {
  haxorg_Leaf_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Leaf(haxorg_Leaf* obj);
struct haxorg_Time_vtable {
  bool const*(*)() get_isActive;
  haxorg_TimeTimeVariant const*(*)() get_time;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Time)}
struct haxorg_Time {
  haxorg_Time_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Time(haxorg_Time* obj);
struct haxorg_TimeRange_vtable {
  haxorg_SemId const*(*)() get_from;
  haxorg_SemId const*(*)() get_to;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(TimeRange)}
struct haxorg_TimeRange {
  haxorg_TimeRange_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_TimeRange(haxorg_TimeRange* obj);
struct haxorg_Macro_vtable {
  haxorg_Str const*(*)() get_name;
  haxorg_AttrGroup const*(*)() get_attrs;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Macro)}
struct haxorg_Macro {
  haxorg_Macro_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Macro(haxorg_Macro* obj);
struct haxorg_Symbol_vtable {
  haxorg_Str const*(*)() get_name;
  haxorg_CHstdVec const*(*)() get_parameters;
  haxorg_CHstdVec const*(*)() get_positional;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Symbol)}
struct haxorg_Symbol {
  haxorg_Symbol_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Symbol(haxorg_Symbol* obj);
struct haxorg_ErrorSkipGroup_vtable {
  haxorg_CHstdVec const*(*)() get_skipped;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(ErrorSkipGroup)}
struct haxorg_ErrorSkipGroup {
  haxorg_ErrorSkipGroup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ErrorSkipGroup(haxorg_ErrorSkipGroup* obj);
struct haxorg_Markup_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Markup)}
struct haxorg_Markup {
  haxorg_Markup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Markup(haxorg_Markup* obj);
struct haxorg_RadioTarget_vtable {
  haxorg_CHstdVec const*(*)() get_words;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(RadioTarget)}
struct haxorg_RadioTarget {
  haxorg_RadioTarget_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_RadioTarget(haxorg_RadioTarget* obj);
struct haxorg_Latex_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Latex)}
struct haxorg_Latex {
  haxorg_Latex_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Latex(haxorg_Latex* obj);
struct haxorg_SubtreeLog_vtable {
  haxorg_SubtreeLogHead const*(*)() get_head;
  haxorg_OptOfSemIdOfStmtList const*(*)() get_desc;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(SubtreeLog)}
struct haxorg_SubtreeLog {
  haxorg_SubtreeLog_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_SubtreeLog(haxorg_SubtreeLog* obj);
struct haxorg_Subtree_vtable {
  int const*(*)() get_level;
  haxorg_OptOfStr const*(*)() get_treeId;
  haxorg_OptOfStr const*(*)() get_todo;
  haxorg_OptOfSubtreeCompletion const*(*)() get_completion;
  haxorg_OptOfSemIdOfParagraph const*(*)() get_description;
  haxorg_CHstdVec const*(*)() get_tags;
  haxorg_SemId const*(*)() get_title;
  haxorg_CHstdVec const*(*)() get_logbook;
  haxorg_CHstdVec const*(*)() get_properties;
  haxorg_OptOfSemIdOfTime const*(*)() get_closed;
  haxorg_OptOfSemIdOfTime const*(*)() get_deadline;
  haxorg_OptOfSemIdOfTime const*(*)() get_scheduled;
  bool const*(*)() get_isComment;
  bool const*(*)() get_isArchived;
  haxorg_OptOfStr const*(*)() get_priority;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Subtree)}
struct haxorg_Subtree {
  haxorg_Subtree_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Subtree(haxorg_Subtree* obj);
struct haxorg_ColonExample_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(ColonExample)}
struct haxorg_ColonExample {
  haxorg_ColonExample_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ColonExample(haxorg_ColonExample* obj);
struct haxorg_Call_vtable {
  haxorg_Str const*(*)() get_name;
  haxorg_AttrGroup const*(*)() get_attrs;
  bool const*(*)() get_isCommand;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Call)}
struct haxorg_Call {
  haxorg_Call_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Call(haxorg_Call* obj);
struct haxorg_ListItem_vtable {
  haxorg_CheckboxState const*(*)() get_checkbox;
  haxorg_OptOfSemIdOfParagraph const*(*)() get_header;
  haxorg_OptOfStr const*(*)() get_bullet;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(ListItem)}
struct haxorg_ListItem {
  haxorg_ListItem_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ListItem(haxorg_ListItem* obj);
struct haxorg_DocumentOptions_vtable {
  haxorg_InitialSubtreeVisibility const*(*)() get_initialVisibility;
  haxorg_CHstdVec const*(*)() get_properties;
  haxorg_DocumentExportConfig const*(*)() get_exportConfig;
  haxorg_OptOfBool const*(*)() get_fixedWidthSections;
  haxorg_OptOfBool const*(*)() get_startupIndented;
  haxorg_OptOfStr const*(*)() get_category;
  haxorg_OptOfStr const*(*)() get_setupfile;
  haxorg_OptOfInt const*(*)() get_maxSubtreeLevelExport;
  haxorg_OptOfColumnView const*(*)() get_columns;
  haxorg_CHstdVec const*(*)() get_todoKeywords;
  haxorg_CHstdVec const*(*)() get_doneKeywords;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(DocumentOptions)}
struct haxorg_DocumentOptions {
  haxorg_DocumentOptions_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_DocumentOptions(haxorg_DocumentOptions* obj);
struct haxorg_DocumentFragment_vtable {
  int const*(*)() get_baseLine;
  int const*(*)() get_baseCol;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(DocumentFragment)}
struct haxorg_DocumentFragment {
  haxorg_DocumentFragment_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_DocumentFragment(haxorg_DocumentFragment* obj);
struct haxorg_CriticMarkup_vtable {
  haxorg_CriticMarkupKind const*(*)() get_kind;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(CriticMarkup)}
struct haxorg_CriticMarkup {
  haxorg_CriticMarkup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_CriticMarkup(haxorg_CriticMarkup* obj);
struct haxorg_Document_vtable {
  haxorg_OptOfSemIdOfParagraph const*(*)() get_title;
  haxorg_OptOfSemIdOfParagraph const*(*)() get_author;
  haxorg_OptOfSemIdOfParagraph const*(*)() get_creator;
  haxorg_CHstdVec const*(*)() get_filetags;
  haxorg_OptOfSemIdOfRawText const*(*)() get_email;
  haxorg_CHstdVec const*(*)() get_language;
  haxorg_SemId const*(*)() get_options;
  haxorg_OptOfStr const*(*)() get_exportFileName;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Document)}
struct haxorg_Document {
  haxorg_Document_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Document(haxorg_Document* obj);
struct haxorg_FileTarget_vtable {
  haxorg_Str const*(*)() get_path;
  haxorg_OptOfInt const*(*)() get_line;
  haxorg_OptOfStr const*(*)() get_searchTarget;
  bool const*(*)() get_restrictToHeadlines;
  haxorg_OptOfStr const*(*)() get_targetId;
  haxorg_OptOfStr const*(*)() get_regexp;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(FileTarget)}
struct haxorg_FileTarget {
  haxorg_FileTarget_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_FileTarget(haxorg_FileTarget* obj);
struct haxorg_TextSeparator_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(TextSeparator)}
struct haxorg_TextSeparator {
  haxorg_TextSeparator_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_TextSeparator(haxorg_TextSeparator* obj);
struct haxorg_DocumentGroup_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(DocumentGroup)}
struct haxorg_DocumentGroup {
  haxorg_DocumentGroup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_DocumentGroup(haxorg_DocumentGroup* obj);
struct haxorg_File_vtable {
  haxorg_Str const*(*)() get_relPath;
  haxorg_Str const*(*)() get_absPath;
  haxorg_FileData const*(*)() get_data;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(File)}
struct haxorg_File {
  haxorg_File_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_File(haxorg_File* obj);
struct haxorg_Directory_vtable {
  haxorg_Str const*(*)() get_relPath;
  haxorg_Str const*(*)() get_absPath;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Directory)}
struct haxorg_Directory {
  haxorg_Directory_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Directory(haxorg_Directory* obj);
struct haxorg_Symlink_vtable {
  bool const*(*)() get_isDirectory;
  haxorg_Str const*(*)() get_absPath;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Symlink)}
struct haxorg_Symlink {
  haxorg_Symlink_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Symlink(haxorg_Symlink* obj);
struct haxorg_CmdInclude_vtable {
  haxorg_Str const*(*)() get_path;
  haxorg_OptOfInt const*(*)() get_firstLine;
  haxorg_OptOfInt const*(*)() get_lastLine;
  haxorg_CmdIncludeData const*(*)() get_data;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(CmdInclude)}
struct haxorg_CmdInclude {
  haxorg_CmdInclude_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_CmdInclude(haxorg_CmdInclude* obj);
struct haxorg_ImmIdTOfImmNoNode_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmNoNode)}>)}
struct haxorg_ImmIdTOfImmNoNode {
  haxorg_ImmIdTOfImmNoNode_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmNoNode(haxorg_ImmIdTOfImmNoNode* obj);
struct haxorg_ImmIdTOfImmErrorItem_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmErrorItem)}>)}
struct haxorg_ImmIdTOfImmErrorItem {
  haxorg_ImmIdTOfImmErrorItem_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmErrorItem(haxorg_ImmIdTOfImmErrorItem* obj);
struct haxorg_ImmIdTOfImmErrorGroup_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmErrorGroup)}>)}
struct haxorg_ImmIdTOfImmErrorGroup {
  haxorg_ImmIdTOfImmErrorGroup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmErrorGroup(haxorg_ImmIdTOfImmErrorGroup* obj);
struct haxorg_ImmIdTOfImmStmt_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmStmt)}>)}
struct haxorg_ImmIdTOfImmStmt {
  haxorg_ImmIdTOfImmStmt_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmStmt(haxorg_ImmIdTOfImmStmt* obj);
struct haxorg_ImmIdTOfImmInline_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmInline)}>)}
struct haxorg_ImmIdTOfImmInline {
  haxorg_ImmIdTOfImmInline_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmInline(haxorg_ImmIdTOfImmInline* obj);
struct haxorg_ImmIdTOfImmStmtList_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmStmtList)}>)}
struct haxorg_ImmIdTOfImmStmtList {
  haxorg_ImmIdTOfImmStmtList_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmStmtList(haxorg_ImmIdTOfImmStmtList* obj);
struct haxorg_ImmIdTOfImmEmpty_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmEmpty)}>)}
struct haxorg_ImmIdTOfImmEmpty {
  haxorg_ImmIdTOfImmEmpty_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmEmpty(haxorg_ImmIdTOfImmEmpty* obj);
struct haxorg_ImmIdTOfImmCmd_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmCmd)}>)}
struct haxorg_ImmIdTOfImmCmd {
  haxorg_ImmIdTOfImmCmd_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmCmd(haxorg_ImmIdTOfImmCmd* obj);
struct haxorg_ImmIdTOfImmBlock_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmBlock)}>)}
struct haxorg_ImmIdTOfImmBlock {
  haxorg_ImmIdTOfImmBlock_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmBlock(haxorg_ImmIdTOfImmBlock* obj);
struct haxorg_ImmIdTOfImmLineCommand_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmLineCommand)}>)}
struct haxorg_ImmIdTOfImmLineCommand {
  haxorg_ImmIdTOfImmLineCommand_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmLineCommand(haxorg_ImmIdTOfImmLineCommand* obj);
struct haxorg_ImmIdTOfImmAttached_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmAttached)}>)}
struct haxorg_ImmIdTOfImmAttached {
  haxorg_ImmIdTOfImmAttached_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmAttached(haxorg_ImmIdTOfImmAttached* obj);
struct haxorg_ImmIdTOfImmLeaf_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmLeaf)}>)}
struct haxorg_ImmIdTOfImmLeaf {
  haxorg_ImmIdTOfImmLeaf_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmLeaf(haxorg_ImmIdTOfImmLeaf* obj);
struct haxorg_ImmIdTOfImmCmdCaption_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmCmdCaption)}>)}
struct haxorg_ImmIdTOfImmCmdCaption {
  haxorg_ImmIdTOfImmCmdCaption_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmCmdCaption(haxorg_ImmIdTOfImmCmdCaption* obj);
struct haxorg_ImmIdTOfImmCmdCreator_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmCmdCreator)}>)}
struct haxorg_ImmIdTOfImmCmdCreator {
  haxorg_ImmIdTOfImmCmdCreator_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmCmdCreator(haxorg_ImmIdTOfImmCmdCreator* obj);
struct haxorg_ImmIdTOfImmCmdAuthor_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmCmdAuthor)}>)}
struct haxorg_ImmIdTOfImmCmdAuthor {
  haxorg_ImmIdTOfImmCmdAuthor_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmCmdAuthor(haxorg_ImmIdTOfImmCmdAuthor* obj);
struct haxorg_ImmIdTOfImmCmdEmail_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmCmdEmail)}>)}
struct haxorg_ImmIdTOfImmCmdEmail {
  haxorg_ImmIdTOfImmCmdEmail_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmCmdEmail(haxorg_ImmIdTOfImmCmdEmail* obj);
struct haxorg_ImmIdTOfImmCmdLanguage_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmCmdLanguage)}>)}
struct haxorg_ImmIdTOfImmCmdLanguage {
  haxorg_ImmIdTOfImmCmdLanguage_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmCmdLanguage(haxorg_ImmIdTOfImmCmdLanguage* obj);
struct haxorg_ImmIdTOfImmCmdColumns_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmCmdColumns)}>)}
struct haxorg_ImmIdTOfImmCmdColumns {
  haxorg_ImmIdTOfImmCmdColumns_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmCmdColumns(haxorg_ImmIdTOfImmCmdColumns* obj);
struct haxorg_ImmIdTOfImmCmdName_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmCmdName)}>)}
struct haxorg_ImmIdTOfImmCmdName {
  haxorg_ImmIdTOfImmCmdName_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmCmdName(haxorg_ImmIdTOfImmCmdName* obj);
struct haxorg_ImmIdTOfImmCmdCustomArgs_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmCmdCustomArgs)}>)}
struct haxorg_ImmIdTOfImmCmdCustomArgs {
  haxorg_ImmIdTOfImmCmdCustomArgs_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmCmdCustomArgs(haxorg_ImmIdTOfImmCmdCustomArgs* obj);
struct haxorg_ImmIdTOfImmCmdCustomRaw_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmCmdCustomRaw)}>)}
struct haxorg_ImmIdTOfImmCmdCustomRaw {
  haxorg_ImmIdTOfImmCmdCustomRaw_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmCmdCustomRaw(haxorg_ImmIdTOfImmCmdCustomRaw* obj);
struct haxorg_ImmIdTOfImmCmdCustomText_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmCmdCustomText)}>)}
struct haxorg_ImmIdTOfImmCmdCustomText {
  haxorg_ImmIdTOfImmCmdCustomText_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmCmdCustomText(haxorg_ImmIdTOfImmCmdCustomText* obj);
struct haxorg_ImmIdTOfImmCmdCall_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmCmdCall)}>)}
struct haxorg_ImmIdTOfImmCmdCall {
  haxorg_ImmIdTOfImmCmdCall_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmCmdCall(haxorg_ImmIdTOfImmCmdCall* obj);
struct haxorg_ImmIdTOfImmCmdTblfm_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmCmdTblfm)}>)}
struct haxorg_ImmIdTOfImmCmdTblfm {
  haxorg_ImmIdTOfImmCmdTblfm_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmCmdTblfm(haxorg_ImmIdTOfImmCmdTblfm* obj);
struct haxorg_ImmIdTOfImmHashTag_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmHashTag)}>)}
struct haxorg_ImmIdTOfImmHashTag {
  haxorg_ImmIdTOfImmHashTag_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmHashTag(haxorg_ImmIdTOfImmHashTag* obj);
struct haxorg_ImmIdTOfImmInlineFootnote_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmInlineFootnote)}>)}
struct haxorg_ImmIdTOfImmInlineFootnote {
  haxorg_ImmIdTOfImmInlineFootnote_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmInlineFootnote(haxorg_ImmIdTOfImmInlineFootnote* obj);
struct haxorg_ImmIdTOfImmInlineExport_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmInlineExport)}>)}
struct haxorg_ImmIdTOfImmInlineExport {
  haxorg_ImmIdTOfImmInlineExport_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmInlineExport(haxorg_ImmIdTOfImmInlineExport* obj);
struct haxorg_ImmIdTOfImmTime_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmTime)}>)}
struct haxorg_ImmIdTOfImmTime {
  haxorg_ImmIdTOfImmTime_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmTime(haxorg_ImmIdTOfImmTime* obj);
struct haxorg_ImmIdTOfImmTimeRange_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmTimeRange)}>)}
struct haxorg_ImmIdTOfImmTimeRange {
  haxorg_ImmIdTOfImmTimeRange_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmTimeRange(haxorg_ImmIdTOfImmTimeRange* obj);
struct haxorg_ImmIdTOfImmMacro_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmMacro)}>)}
struct haxorg_ImmIdTOfImmMacro {
  haxorg_ImmIdTOfImmMacro_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmMacro(haxorg_ImmIdTOfImmMacro* obj);
struct haxorg_ImmIdTOfImmSymbol_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmSymbol)}>)}
struct haxorg_ImmIdTOfImmSymbol {
  haxorg_ImmIdTOfImmSymbol_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmSymbol(haxorg_ImmIdTOfImmSymbol* obj);
struct haxorg_ImmIdTOfImmEscaped_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmEscaped)}>)}
struct haxorg_ImmIdTOfImmEscaped {
  haxorg_ImmIdTOfImmEscaped_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmEscaped(haxorg_ImmIdTOfImmEscaped* obj);
struct haxorg_ImmIdTOfImmNewline_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmNewline)}>)}
struct haxorg_ImmIdTOfImmNewline {
  haxorg_ImmIdTOfImmNewline_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmNewline(haxorg_ImmIdTOfImmNewline* obj);
struct haxorg_ImmIdTOfImmSpace_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmSpace)}>)}
struct haxorg_ImmIdTOfImmSpace {
  haxorg_ImmIdTOfImmSpace_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmSpace(haxorg_ImmIdTOfImmSpace* obj);
struct haxorg_ImmIdTOfImmWord_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmWord)}>)}
struct haxorg_ImmIdTOfImmWord {
  haxorg_ImmIdTOfImmWord_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmWord(haxorg_ImmIdTOfImmWord* obj);
struct haxorg_ImmIdTOfImmAtMention_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmAtMention)}>)}
struct haxorg_ImmIdTOfImmAtMention {
  haxorg_ImmIdTOfImmAtMention_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmAtMention(haxorg_ImmIdTOfImmAtMention* obj);
struct haxorg_ImmIdTOfImmRawText_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmRawText)}>)}
struct haxorg_ImmIdTOfImmRawText {
  haxorg_ImmIdTOfImmRawText_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmRawText(haxorg_ImmIdTOfImmRawText* obj);
struct haxorg_ImmIdTOfImmPunctuation_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmPunctuation)}>)}
struct haxorg_ImmIdTOfImmPunctuation {
  haxorg_ImmIdTOfImmPunctuation_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmPunctuation(haxorg_ImmIdTOfImmPunctuation* obj);
struct haxorg_ImmIdTOfImmPlaceholder_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmPlaceholder)}>)}
struct haxorg_ImmIdTOfImmPlaceholder {
  haxorg_ImmIdTOfImmPlaceholder_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmPlaceholder(haxorg_ImmIdTOfImmPlaceholder* obj);
struct haxorg_ImmIdTOfImmBigIdent_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmBigIdent)}>)}
struct haxorg_ImmIdTOfImmBigIdent {
  haxorg_ImmIdTOfImmBigIdent_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmBigIdent(haxorg_ImmIdTOfImmBigIdent* obj);
struct haxorg_ImmIdTOfImmTextTarget_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmTextTarget)}>)}
struct haxorg_ImmIdTOfImmTextTarget {
  haxorg_ImmIdTOfImmTextTarget_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmTextTarget(haxorg_ImmIdTOfImmTextTarget* obj);
struct haxorg_ImmIdTOfImmErrorSkipToken_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmErrorSkipToken)}>)}
struct haxorg_ImmIdTOfImmErrorSkipToken {
  haxorg_ImmIdTOfImmErrorSkipToken_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmErrorSkipToken(haxorg_ImmIdTOfImmErrorSkipToken* obj);
struct haxorg_ImmIdTOfImmErrorSkipGroup_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmErrorSkipGroup)}>)}
struct haxorg_ImmIdTOfImmErrorSkipGroup {
  haxorg_ImmIdTOfImmErrorSkipGroup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmErrorSkipGroup(haxorg_ImmIdTOfImmErrorSkipGroup* obj);
struct haxorg_ImmIdTOfImmMarkup_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmMarkup)}>)}
struct haxorg_ImmIdTOfImmMarkup {
  haxorg_ImmIdTOfImmMarkup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmMarkup(haxorg_ImmIdTOfImmMarkup* obj);
struct haxorg_ImmIdTOfImmBold_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmBold)}>)}
struct haxorg_ImmIdTOfImmBold {
  haxorg_ImmIdTOfImmBold_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmBold(haxorg_ImmIdTOfImmBold* obj);
struct haxorg_ImmIdTOfImmUnderline_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmUnderline)}>)}
struct haxorg_ImmIdTOfImmUnderline {
  haxorg_ImmIdTOfImmUnderline_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmUnderline(haxorg_ImmIdTOfImmUnderline* obj);
struct haxorg_ImmIdTOfImmMonospace_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmMonospace)}>)}
struct haxorg_ImmIdTOfImmMonospace {
  haxorg_ImmIdTOfImmMonospace_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmMonospace(haxorg_ImmIdTOfImmMonospace* obj);
struct haxorg_ImmIdTOfImmMarkQuote_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmMarkQuote)}>)}
struct haxorg_ImmIdTOfImmMarkQuote {
  haxorg_ImmIdTOfImmMarkQuote_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmMarkQuote(haxorg_ImmIdTOfImmMarkQuote* obj);
struct haxorg_ImmIdTOfImmVerbatim_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmVerbatim)}>)}
struct haxorg_ImmIdTOfImmVerbatim {
  haxorg_ImmIdTOfImmVerbatim_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmVerbatim(haxorg_ImmIdTOfImmVerbatim* obj);
struct haxorg_ImmIdTOfImmItalic_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmItalic)}>)}
struct haxorg_ImmIdTOfImmItalic {
  haxorg_ImmIdTOfImmItalic_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmItalic(haxorg_ImmIdTOfImmItalic* obj);
struct haxorg_ImmIdTOfImmStrike_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmStrike)}>)}
struct haxorg_ImmIdTOfImmStrike {
  haxorg_ImmIdTOfImmStrike_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmStrike(haxorg_ImmIdTOfImmStrike* obj);
struct haxorg_ImmIdTOfImmPar_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmPar)}>)}
struct haxorg_ImmIdTOfImmPar {
  haxorg_ImmIdTOfImmPar_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmPar(haxorg_ImmIdTOfImmPar* obj);
struct haxorg_ImmIdTOfImmRadioTarget_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmRadioTarget)}>)}
struct haxorg_ImmIdTOfImmRadioTarget {
  haxorg_ImmIdTOfImmRadioTarget_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmRadioTarget(haxorg_ImmIdTOfImmRadioTarget* obj);
struct haxorg_ImmIdTOfImmLatex_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmLatex)}>)}
struct haxorg_ImmIdTOfImmLatex {
  haxorg_ImmIdTOfImmLatex_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmLatex(haxorg_ImmIdTOfImmLatex* obj);
struct haxorg_ImmIdTOfImmLink_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmLink)}>)}
struct haxorg_ImmIdTOfImmLink {
  haxorg_ImmIdTOfImmLink_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmLink(haxorg_ImmIdTOfImmLink* obj);
struct haxorg_ImmIdTOfImmBlockCenter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmBlockCenter)}>)}
struct haxorg_ImmIdTOfImmBlockCenter {
  haxorg_ImmIdTOfImmBlockCenter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmBlockCenter(haxorg_ImmIdTOfImmBlockCenter* obj);
struct haxorg_ImmIdTOfImmBlockQuote_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmBlockQuote)}>)}
struct haxorg_ImmIdTOfImmBlockQuote {
  haxorg_ImmIdTOfImmBlockQuote_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmBlockQuote(haxorg_ImmIdTOfImmBlockQuote* obj);
struct haxorg_ImmIdTOfImmBlockComment_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmBlockComment)}>)}
struct haxorg_ImmIdTOfImmBlockComment {
  haxorg_ImmIdTOfImmBlockComment_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmBlockComment(haxorg_ImmIdTOfImmBlockComment* obj);
struct haxorg_ImmIdTOfImmBlockVerse_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmBlockVerse)}>)}
struct haxorg_ImmIdTOfImmBlockVerse {
  haxorg_ImmIdTOfImmBlockVerse_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmBlockVerse(haxorg_ImmIdTOfImmBlockVerse* obj);
struct haxorg_ImmIdTOfImmBlockDynamicFallback_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmBlockDynamicFallback)}>)}
struct haxorg_ImmIdTOfImmBlockDynamicFallback {
  haxorg_ImmIdTOfImmBlockDynamicFallback_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmBlockDynamicFallback(haxorg_ImmIdTOfImmBlockDynamicFallback* obj);
struct haxorg_ImmIdTOfImmBlockExample_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmBlockExample)}>)}
struct haxorg_ImmIdTOfImmBlockExample {
  haxorg_ImmIdTOfImmBlockExample_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmBlockExample(haxorg_ImmIdTOfImmBlockExample* obj);
struct haxorg_ImmIdTOfImmBlockExport_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmBlockExport)}>)}
struct haxorg_ImmIdTOfImmBlockExport {
  haxorg_ImmIdTOfImmBlockExport_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmBlockExport(haxorg_ImmIdTOfImmBlockExport* obj);
struct haxorg_ImmIdTOfImmBlockAdmonition_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmBlockAdmonition)}>)}
struct haxorg_ImmIdTOfImmBlockAdmonition {
  haxorg_ImmIdTOfImmBlockAdmonition_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmBlockAdmonition(haxorg_ImmIdTOfImmBlockAdmonition* obj);
struct haxorg_ImmIdTOfImmBlockCodeEvalResult_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmBlockCodeEvalResult)}>)}
struct haxorg_ImmIdTOfImmBlockCodeEvalResult {
  haxorg_ImmIdTOfImmBlockCodeEvalResult_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmBlockCodeEvalResult(haxorg_ImmIdTOfImmBlockCodeEvalResult* obj);
struct haxorg_ImmIdTOfImmBlockCode_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmBlockCode)}>)}
struct haxorg_ImmIdTOfImmBlockCode {
  haxorg_ImmIdTOfImmBlockCode_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmBlockCode(haxorg_ImmIdTOfImmBlockCode* obj);
struct haxorg_ImmIdTOfImmSubtreeLog_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmSubtreeLog)}>)}
struct haxorg_ImmIdTOfImmSubtreeLog {
  haxorg_ImmIdTOfImmSubtreeLog_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmSubtreeLog(haxorg_ImmIdTOfImmSubtreeLog* obj);
struct haxorg_ImmIdTOfImmSubtree_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmSubtree)}>)}
struct haxorg_ImmIdTOfImmSubtree {
  haxorg_ImmIdTOfImmSubtree_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmSubtree(haxorg_ImmIdTOfImmSubtree* obj);
struct haxorg_ImmIdTOfImmCell_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmCell)}>)}
struct haxorg_ImmIdTOfImmCell {
  haxorg_ImmIdTOfImmCell_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmCell(haxorg_ImmIdTOfImmCell* obj);
struct haxorg_ImmIdTOfImmRow_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmRow)}>)}
struct haxorg_ImmIdTOfImmRow {
  haxorg_ImmIdTOfImmRow_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmRow(haxorg_ImmIdTOfImmRow* obj);
struct haxorg_ImmIdTOfImmTable_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmTable)}>)}
struct haxorg_ImmIdTOfImmTable {
  haxorg_ImmIdTOfImmTable_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmTable(haxorg_ImmIdTOfImmTable* obj);
struct haxorg_ImmIdTOfImmParagraph_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmParagraph)}>)}
struct haxorg_ImmIdTOfImmParagraph {
  haxorg_ImmIdTOfImmParagraph_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmParagraph(haxorg_ImmIdTOfImmParagraph* obj);
struct haxorg_ImmIdTOfImmColonExample_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmColonExample)}>)}
struct haxorg_ImmIdTOfImmColonExample {
  haxorg_ImmIdTOfImmColonExample_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmColonExample(haxorg_ImmIdTOfImmColonExample* obj);
struct haxorg_ImmIdTOfImmCmdAttr_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmCmdAttr)}>)}
struct haxorg_ImmIdTOfImmCmdAttr {
  haxorg_ImmIdTOfImmCmdAttr_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmCmdAttr(haxorg_ImmIdTOfImmCmdAttr* obj);
struct haxorg_ImmIdTOfImmCmdExport_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmCmdExport)}>)}
struct haxorg_ImmIdTOfImmCmdExport {
  haxorg_ImmIdTOfImmCmdExport_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmCmdExport(haxorg_ImmIdTOfImmCmdExport* obj);
struct haxorg_ImmIdTOfImmCall_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmCall)}>)}
struct haxorg_ImmIdTOfImmCall {
  haxorg_ImmIdTOfImmCall_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmCall(haxorg_ImmIdTOfImmCall* obj);
struct haxorg_ImmIdTOfImmList_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmList)}>)}
struct haxorg_ImmIdTOfImmList {
  haxorg_ImmIdTOfImmList_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmList(haxorg_ImmIdTOfImmList* obj);
struct haxorg_ImmIdTOfImmListItem_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmListItem)}>)}
struct haxorg_ImmIdTOfImmListItem {
  haxorg_ImmIdTOfImmListItem_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmListItem(haxorg_ImmIdTOfImmListItem* obj);
struct haxorg_ImmIdTOfImmDocumentOptions_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmDocumentOptions)}>)}
struct haxorg_ImmIdTOfImmDocumentOptions {
  haxorg_ImmIdTOfImmDocumentOptions_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmDocumentOptions(haxorg_ImmIdTOfImmDocumentOptions* obj);
struct haxorg_ImmIdTOfImmDocumentFragment_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmDocumentFragment)}>)}
struct haxorg_ImmIdTOfImmDocumentFragment {
  haxorg_ImmIdTOfImmDocumentFragment_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmDocumentFragment(haxorg_ImmIdTOfImmDocumentFragment* obj);
struct haxorg_ImmIdTOfImmCriticMarkup_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmCriticMarkup)}>)}
struct haxorg_ImmIdTOfImmCriticMarkup {
  haxorg_ImmIdTOfImmCriticMarkup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmCriticMarkup(haxorg_ImmIdTOfImmCriticMarkup* obj);
struct haxorg_ImmIdTOfImmDocument_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmDocument)}>)}
struct haxorg_ImmIdTOfImmDocument {
  haxorg_ImmIdTOfImmDocument_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmDocument(haxorg_ImmIdTOfImmDocument* obj);
struct haxorg_ImmIdTOfImmFileTarget_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmFileTarget)}>)}
struct haxorg_ImmIdTOfImmFileTarget {
  haxorg_ImmIdTOfImmFileTarget_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmFileTarget(haxorg_ImmIdTOfImmFileTarget* obj);
struct haxorg_ImmIdTOfImmTextSeparator_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmTextSeparator)}>)}
struct haxorg_ImmIdTOfImmTextSeparator {
  haxorg_ImmIdTOfImmTextSeparator_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmTextSeparator(haxorg_ImmIdTOfImmTextSeparator* obj);
struct haxorg_ImmIdTOfImmDocumentGroup_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmDocumentGroup)}>)}
struct haxorg_ImmIdTOfImmDocumentGroup {
  haxorg_ImmIdTOfImmDocumentGroup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmDocumentGroup(haxorg_ImmIdTOfImmDocumentGroup* obj);
struct haxorg_ImmIdTOfImmFile_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmFile)}>)}
struct haxorg_ImmIdTOfImmFile {
  haxorg_ImmIdTOfImmFile_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmFile(haxorg_ImmIdTOfImmFile* obj);
struct haxorg_ImmIdTOfImmDirectory_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmDirectory)}>)}
struct haxorg_ImmIdTOfImmDirectory {
  haxorg_ImmIdTOfImmDirectory_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmDirectory(haxorg_ImmIdTOfImmDirectory* obj);
struct haxorg_ImmIdTOfImmSymlink_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmSymlink)}>)}
struct haxorg_ImmIdTOfImmSymlink {
  haxorg_ImmIdTOfImmSymlink_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmSymlink(haxorg_ImmIdTOfImmSymlink* obj);
struct haxorg_ImmIdTOfImmCmdInclude_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmIdT<{{{REC:(org)}::REC:(imm)}::REC:(ImmCmdInclude)}>)}
struct haxorg_ImmIdTOfImmCmdInclude {
  haxorg_ImmIdTOfImmCmdInclude_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmIdTOfImmCmdInclude(haxorg_ImmIdTOfImmCmdInclude* obj);
struct haxorg_ImmNoNode_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmNoNode)}
struct haxorg_ImmNoNode {
  haxorg_ImmNoNode_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmNoNode(haxorg_ImmNoNode* obj);
struct haxorg_ImmErrorItem_vtable {
  haxorg_OrgDiagnostics const*(*)() get_diag;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmErrorItem)}
struct haxorg_ImmErrorItem {
  haxorg_ImmErrorItem_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmErrorItem(haxorg_ImmErrorItem* obj);
struct haxorg_ImmErrorGroup_vtable {
  haxorg_ImmVecOfImmIdTOfImmErrorItem const*(*)() get_diagnostics;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmErrorGroup)}
struct haxorg_ImmErrorGroup {
  haxorg_ImmErrorGroup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmErrorGroup(haxorg_ImmErrorGroup* obj);
struct haxorg_ImmStmt_vtable {
  haxorg_ImmVecOfImmIdTOfImmOrg const*(*)() get_attached;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmStmt)}
struct haxorg_ImmStmt {
  haxorg_ImmStmt_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmStmt(haxorg_ImmStmt* obj);
struct haxorg_ImmInline_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmInline)}
struct haxorg_ImmInline {
  haxorg_ImmInline_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmInline(haxorg_ImmInline* obj);
struct haxorg_ImmStmtList_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmStmtList)}
struct haxorg_ImmStmtList {
  haxorg_ImmStmtList_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmStmtList(haxorg_ImmStmtList* obj);
struct haxorg_ImmEmpty_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmEmpty)}
struct haxorg_ImmEmpty {
  haxorg_ImmEmpty_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmEmpty(haxorg_ImmEmpty* obj);
struct haxorg_ImmLeaf_vtable {
  haxorg_ImmBoxOfStr const*(*)() get_text;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmLeaf)}
struct haxorg_ImmLeaf {
  haxorg_ImmLeaf_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmLeaf(haxorg_ImmLeaf* obj);
struct haxorg_ImmTime_vtable {
  bool const*(*)() get_isActive;
  haxorg_ImmTimeTimeVariant const*(*)() get_time;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmTime)}
struct haxorg_ImmTime {
  haxorg_ImmTime_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmTime(haxorg_ImmTime* obj);
struct haxorg_ImmTimeRange_vtable {
  haxorg_ImmIdTOfImmTime const*(*)() get_from;
  haxorg_ImmIdTOfImmTime const*(*)() get_to;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmTimeRange)}
struct haxorg_ImmTimeRange {
  haxorg_ImmTimeRange_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmTimeRange(haxorg_ImmTimeRange* obj);
struct haxorg_ImmMacro_vtable {
  haxorg_ImmBoxOfStr const*(*)() get_name;
  haxorg_AttrGroup const*(*)() get_attrs;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmMacro)}
struct haxorg_ImmMacro {
  haxorg_ImmMacro_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmMacro(haxorg_ImmMacro* obj);
struct haxorg_ImmSymbol_vtable {
  haxorg_ImmBoxOfStr const*(*)() get_name;
  haxorg_ImmVecOfImmSymbolParam const*(*)() get_parameters;
  haxorg_ImmVecOfImmIdTOfImmOrg const*(*)() get_positional;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmSymbol)}
struct haxorg_ImmSymbol {
  haxorg_ImmSymbol_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmSymbol(haxorg_ImmSymbol* obj);
struct haxorg_ImmErrorSkipGroup_vtable {
  haxorg_ImmVecOfImmIdTOfImmErrorSkipToken const*(*)() get_skipped;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmErrorSkipGroup)}
struct haxorg_ImmErrorSkipGroup {
  haxorg_ImmErrorSkipGroup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmErrorSkipGroup(haxorg_ImmErrorSkipGroup* obj);
struct haxorg_ImmMarkup_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmMarkup)}
struct haxorg_ImmMarkup {
  haxorg_ImmMarkup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmMarkup(haxorg_ImmMarkup* obj);
struct haxorg_ImmRadioTarget_vtable {
  haxorg_ImmVecOfStr const*(*)() get_words;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmRadioTarget)}
struct haxorg_ImmRadioTarget {
  haxorg_ImmRadioTarget_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmRadioTarget(haxorg_ImmRadioTarget* obj);
struct haxorg_ImmLatex_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmLatex)}
struct haxorg_ImmLatex {
  haxorg_ImmLatex_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmLatex(haxorg_ImmLatex* obj);
struct haxorg_ImmSubtreeLog_vtable {
  haxorg_SubtreeLogHead const*(*)() get_head;
  haxorg_ImmBoxOfOptOfImmIdTOfImmStmtList const*(*)() get_desc;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmSubtreeLog)}
struct haxorg_ImmSubtreeLog {
  haxorg_ImmSubtreeLog_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmSubtreeLog(haxorg_ImmSubtreeLog* obj);
struct haxorg_ImmSubtree_vtable {
  int const*(*)() get_level;
  haxorg_ImmBoxOfOptOfStr const*(*)() get_treeId;
  haxorg_ImmBoxOfOptOfStr const*(*)() get_todo;
  haxorg_ImmBoxOfOptOfSubtreeCompletion const*(*)() get_completion;
  haxorg_ImmBoxOfOptOfImmIdTOfImmParagraph const*(*)() get_description;
  haxorg_ImmVecOfImmIdTOfImmHashTag const*(*)() get_tags;
  haxorg_ImmIdTOfImmParagraph const*(*)() get_title;
  haxorg_ImmVecOfImmIdTOfImmSubtreeLog const*(*)() get_logbook;
  haxorg_ImmVecOfNamedProperty const*(*)() get_properties;
  haxorg_ImmBoxOfOptOfImmIdTOfImmTime const*(*)() get_closed;
  haxorg_ImmBoxOfOptOfImmIdTOfImmTime const*(*)() get_deadline;
  haxorg_ImmBoxOfOptOfImmIdTOfImmTime const*(*)() get_scheduled;
  bool const*(*)() get_isComment;
  bool const*(*)() get_isArchived;
  haxorg_ImmBoxOfOptOfStr const*(*)() get_priority;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmSubtree)}
struct haxorg_ImmSubtree {
  haxorg_ImmSubtree_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmSubtree(haxorg_ImmSubtree* obj);
struct haxorg_ImmColonExample_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmColonExample)}
struct haxorg_ImmColonExample {
  haxorg_ImmColonExample_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmColonExample(haxorg_ImmColonExample* obj);
struct haxorg_ImmCall_vtable {
  haxorg_ImmBoxOfStr const*(*)() get_name;
  haxorg_AttrGroup const*(*)() get_attrs;
  bool const*(*)() get_isCommand;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmCall)}
struct haxorg_ImmCall {
  haxorg_ImmCall_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCall(haxorg_ImmCall* obj);
struct haxorg_ImmListItem_vtable {
  haxorg_CheckboxState const*(*)() get_checkbox;
  haxorg_ImmBoxOfOptOfImmIdTOfImmParagraph const*(*)() get_header;
  haxorg_ImmBoxOfOptOfStr const*(*)() get_bullet;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmListItem)}
struct haxorg_ImmListItem {
  haxorg_ImmListItem_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmListItem(haxorg_ImmListItem* obj);
struct haxorg_ImmDocumentOptions_vtable {
  haxorg_InitialSubtreeVisibility const*(*)() get_initialVisibility;
  haxorg_ImmVecOfNamedProperty const*(*)() get_properties;
  haxorg_DocumentExportConfig const*(*)() get_exportConfig;
  haxorg_ImmBoxOfOptOfBool const*(*)() get_fixedWidthSections;
  haxorg_ImmBoxOfOptOfBool const*(*)() get_startupIndented;
  haxorg_ImmBoxOfOptOfStr const*(*)() get_category;
  haxorg_ImmBoxOfOptOfStr const*(*)() get_setupfile;
  haxorg_ImmBoxOfOptOfInt const*(*)() get_maxSubtreeLevelExport;
  haxorg_ImmBoxOfOptOfColumnView const*(*)() get_columns;
  haxorg_ImmVecOfTodoKeyword const*(*)() get_todoKeywords;
  haxorg_ImmVecOfTodoKeyword const*(*)() get_doneKeywords;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmDocumentOptions)}
struct haxorg_ImmDocumentOptions {
  haxorg_ImmDocumentOptions_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmDocumentOptions(haxorg_ImmDocumentOptions* obj);
struct haxorg_ImmDocumentFragment_vtable {
  int const*(*)() get_baseLine;
  int const*(*)() get_baseCol;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmDocumentFragment)}
struct haxorg_ImmDocumentFragment {
  haxorg_ImmDocumentFragment_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmDocumentFragment(haxorg_ImmDocumentFragment* obj);
struct haxorg_ImmCriticMarkup_vtable {
  haxorg_ImmCriticMarkupKind const*(*)() get_kind;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmCriticMarkup)}
struct haxorg_ImmCriticMarkup {
  haxorg_ImmCriticMarkup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCriticMarkup(haxorg_ImmCriticMarkup* obj);
struct haxorg_ImmDocument_vtable {
  haxorg_ImmBoxOfOptOfImmIdTOfImmParagraph const*(*)() get_title;
  haxorg_ImmBoxOfOptOfImmIdTOfImmParagraph const*(*)() get_author;
  haxorg_ImmBoxOfOptOfImmIdTOfImmParagraph const*(*)() get_creator;
  haxorg_ImmVecOfImmIdTOfImmHashTag const*(*)() get_filetags;
  haxorg_ImmBoxOfOptOfImmIdTOfImmRawText const*(*)() get_email;
  haxorg_ImmVecOfStr const*(*)() get_language;
  haxorg_ImmIdTOfImmDocumentOptions const*(*)() get_options;
  haxorg_ImmBoxOfOptOfStr const*(*)() get_exportFileName;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmDocument)}
struct haxorg_ImmDocument {
  haxorg_ImmDocument_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmDocument(haxorg_ImmDocument* obj);
struct haxorg_ImmFileTarget_vtable {
  haxorg_ImmBoxOfStr const*(*)() get_path;
  haxorg_ImmBoxOfOptOfInt const*(*)() get_line;
  haxorg_ImmBoxOfOptOfStr const*(*)() get_searchTarget;
  bool const*(*)() get_restrictToHeadlines;
  haxorg_ImmBoxOfOptOfStr const*(*)() get_targetId;
  haxorg_ImmBoxOfOptOfStr const*(*)() get_regexp;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmFileTarget)}
struct haxorg_ImmFileTarget {
  haxorg_ImmFileTarget_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmFileTarget(haxorg_ImmFileTarget* obj);
struct haxorg_ImmTextSeparator_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmTextSeparator)}
struct haxorg_ImmTextSeparator {
  haxorg_ImmTextSeparator_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmTextSeparator(haxorg_ImmTextSeparator* obj);
struct haxorg_ImmDocumentGroup_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmDocumentGroup)}
struct haxorg_ImmDocumentGroup {
  haxorg_ImmDocumentGroup_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmDocumentGroup(haxorg_ImmDocumentGroup* obj);
struct haxorg_ImmFile_vtable {
  haxorg_ImmBoxOfStr const*(*)() get_relPath;
  haxorg_ImmBoxOfStr const*(*)() get_absPath;
  haxorg_ImmFileData const*(*)() get_data;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmFile)}
struct haxorg_ImmFile {
  haxorg_ImmFile_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmFile(haxorg_ImmFile* obj);
struct haxorg_ImmDirectory_vtable {
  haxorg_ImmBoxOfStr const*(*)() get_relPath;
  haxorg_ImmBoxOfStr const*(*)() get_absPath;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmDirectory)}
struct haxorg_ImmDirectory {
  haxorg_ImmDirectory_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmDirectory(haxorg_ImmDirectory* obj);
struct haxorg_ImmSymlink_vtable {
  bool const*(*)() get_isDirectory;
  haxorg_ImmBoxOfStr const*(*)() get_absPath;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmSymlink)}
struct haxorg_ImmSymlink {
  haxorg_ImmSymlink_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmSymlink(haxorg_ImmSymlink* obj);
struct haxorg_ImmCmdInclude_vtable {
  haxorg_ImmBoxOfStr const*(*)() get_path;
  haxorg_ImmBoxOfOptOfInt const*(*)() get_firstLine;
  haxorg_ImmBoxOfOptOfInt const*(*)() get_lastLine;
  haxorg_ImmCmdIncludeData const*(*)() get_data;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmCmdInclude)}
struct haxorg_ImmCmdInclude {
  haxorg_ImmCmdInclude_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmdInclude(haxorg_ImmCmdInclude* obj);
struct haxorg_ImmAdapterOrgAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterOrgAPI)}
struct haxorg_ImmAdapterOrgAPI {
  haxorg_ImmAdapterOrgAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterOrgAPI(haxorg_ImmAdapterOrgAPI* obj);
struct haxorg_Cmd_vtable {
  haxorg_AttrGroup const*(*)() get_attrs;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Cmd)}
struct haxorg_Cmd {
  haxorg_Cmd_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Cmd(haxorg_Cmd* obj);
struct haxorg_CmdCustomRaw_vtable {
  haxorg_Str const*(*)() get_name;
  bool const*(*)() get_isAttached;
  haxorg_Str const*(*)() get_text;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(CmdCustomRaw)}
struct haxorg_CmdCustomRaw {
  haxorg_CmdCustomRaw_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_CmdCustomRaw(haxorg_CmdCustomRaw* obj);
struct haxorg_CmdCustomText_vtable {
  haxorg_Str const*(*)() get_name;
  bool const*(*)() get_isAttached;
  haxorg_SemId const*(*)() get_text;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(CmdCustomText)}
struct haxorg_CmdCustomText {
  haxorg_CmdCustomText_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_CmdCustomText(haxorg_CmdCustomText* obj);
struct haxorg_Link_vtable {
  haxorg_OptOfSemIdOfParagraph const*(*)() get_description;
  haxorg_LinkTarget const*(*)() get_target;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Link)}
struct haxorg_Link {
  haxorg_Link_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Link(haxorg_Link* obj);
struct haxorg_BlockComment_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(BlockComment)}
struct haxorg_BlockComment {
  haxorg_BlockComment_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_BlockComment(haxorg_BlockComment* obj);
struct haxorg_Paragraph_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Paragraph)}
struct haxorg_Paragraph {
  haxorg_Paragraph_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Paragraph(haxorg_Paragraph* obj);
struct haxorg_List_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(List)}
struct haxorg_List {
  haxorg_List_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_List(haxorg_List* obj);
struct haxorg_HashTag_vtable {
  haxorg_HashTagText const*(*)() get_text;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(HashTag)}
struct haxorg_HashTag {
  haxorg_HashTag_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_HashTag(haxorg_HashTag* obj);
struct haxorg_InlineFootnote_vtable {
  haxorg_Str const*(*)() get_tag;
  haxorg_OptOfSemIdOfOrg const*(*)() get_definition;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(InlineFootnote)}
struct haxorg_InlineFootnote {
  haxorg_InlineFootnote_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_InlineFootnote(haxorg_InlineFootnote* obj);
struct haxorg_InlineExport_vtable {
  haxorg_Str const*(*)() get_exporter;
  haxorg_Str const*(*)() get_content;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(InlineExport)}
struct haxorg_InlineExport {
  haxorg_InlineExport_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_InlineExport(haxorg_InlineExport* obj);
struct haxorg_Escaped_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Escaped)}
struct haxorg_Escaped {
  haxorg_Escaped_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Escaped(haxorg_Escaped* obj);
struct haxorg_Newline_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Newline)}
struct haxorg_Newline {
  haxorg_Newline_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Newline(haxorg_Newline* obj);
struct haxorg_Space_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Space)}
struct haxorg_Space {
  haxorg_Space_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Space(haxorg_Space* obj);
struct haxorg_Word_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Word)}
struct haxorg_Word {
  haxorg_Word_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Word(haxorg_Word* obj);
struct haxorg_AtMention_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(AtMention)}
struct haxorg_AtMention {
  haxorg_AtMention_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_AtMention(haxorg_AtMention* obj);
struct haxorg_RawText_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(RawText)}
struct haxorg_RawText {
  haxorg_RawText_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_RawText(haxorg_RawText* obj);
struct haxorg_Punctuation_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Punctuation)}
struct haxorg_Punctuation {
  haxorg_Punctuation_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Punctuation(haxorg_Punctuation* obj);
struct haxorg_Placeholder_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Placeholder)}
struct haxorg_Placeholder {
  haxorg_Placeholder_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Placeholder(haxorg_Placeholder* obj);
struct haxorg_BigIdent_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(BigIdent)}
struct haxorg_BigIdent {
  haxorg_BigIdent_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_BigIdent(haxorg_BigIdent* obj);
struct haxorg_TextTarget_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(TextTarget)}
struct haxorg_TextTarget {
  haxorg_TextTarget_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_TextTarget(haxorg_TextTarget* obj);
struct haxorg_ErrorSkipToken_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(ErrorSkipToken)}
struct haxorg_ErrorSkipToken {
  haxorg_ErrorSkipToken_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ErrorSkipToken(haxorg_ErrorSkipToken* obj);
struct haxorg_Bold_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Bold)}
struct haxorg_Bold {
  haxorg_Bold_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Bold(haxorg_Bold* obj);
struct haxorg_Underline_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Underline)}
struct haxorg_Underline {
  haxorg_Underline_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Underline(haxorg_Underline* obj);
struct haxorg_Monospace_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Monospace)}
struct haxorg_Monospace {
  haxorg_Monospace_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Monospace(haxorg_Monospace* obj);
struct haxorg_MarkQuote_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(MarkQuote)}
struct haxorg_MarkQuote {
  haxorg_MarkQuote_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_MarkQuote(haxorg_MarkQuote* obj);
struct haxorg_Verbatim_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Verbatim)}
struct haxorg_Verbatim {
  haxorg_Verbatim_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Verbatim(haxorg_Verbatim* obj);
struct haxorg_Italic_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Italic)}
struct haxorg_Italic {
  haxorg_Italic_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Italic(haxorg_Italic* obj);
struct haxorg_Strike_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Strike)}
struct haxorg_Strike {
  haxorg_Strike_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Strike(haxorg_Strike* obj);
struct haxorg_Par_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Par)}
struct haxorg_Par {
  haxorg_Par_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Par(haxorg_Par* obj);
struct haxorg_ImmCmd_vtable {
  haxorg_AttrGroup const*(*)() get_attrs;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmCmd)}
struct haxorg_ImmCmd {
  haxorg_ImmCmd_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmd(haxorg_ImmCmd* obj);
struct haxorg_ImmCmdCustomRaw_vtable {
  haxorg_ImmBoxOfStr const*(*)() get_name;
  bool const*(*)() get_isAttached;
  haxorg_ImmBoxOfStr const*(*)() get_text;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmCmdCustomRaw)}
struct haxorg_ImmCmdCustomRaw {
  haxorg_ImmCmdCustomRaw_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmdCustomRaw(haxorg_ImmCmdCustomRaw* obj);
struct haxorg_ImmCmdCustomText_vtable {
  haxorg_ImmBoxOfStr const*(*)() get_name;
  bool const*(*)() get_isAttached;
  haxorg_ImmIdTOfImmParagraph const*(*)() get_text;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmCmdCustomText)}
struct haxorg_ImmCmdCustomText {
  haxorg_ImmCmdCustomText_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmdCustomText(haxorg_ImmCmdCustomText* obj);
struct haxorg_ImmLink_vtable {
  haxorg_ImmBoxOfOptOfImmIdTOfImmParagraph const*(*)() get_description;
  haxorg_LinkTarget const*(*)() get_target;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmLink)}
struct haxorg_ImmLink {
  haxorg_ImmLink_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmLink(haxorg_ImmLink* obj);
struct haxorg_ImmBlockComment_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmBlockComment)}
struct haxorg_ImmBlockComment {
  haxorg_ImmBlockComment_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmBlockComment(haxorg_ImmBlockComment* obj);
struct haxorg_ImmParagraph_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmParagraph)}
struct haxorg_ImmParagraph {
  haxorg_ImmParagraph_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmParagraph(haxorg_ImmParagraph* obj);
struct haxorg_ImmList_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmList)}
struct haxorg_ImmList {
  haxorg_ImmList_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmList(haxorg_ImmList* obj);
struct haxorg_ImmHashTag_vtable {
  haxorg_HashTagText const*(*)() get_text;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmHashTag)}
struct haxorg_ImmHashTag {
  haxorg_ImmHashTag_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmHashTag(haxorg_ImmHashTag* obj);
struct haxorg_ImmInlineFootnote_vtable {
  haxorg_ImmBoxOfStr const*(*)() get_tag;
  haxorg_ImmBoxOfOptOfImmIdTOfImmOrg const*(*)() get_definition;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmInlineFootnote)}
struct haxorg_ImmInlineFootnote {
  haxorg_ImmInlineFootnote_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmInlineFootnote(haxorg_ImmInlineFootnote* obj);
struct haxorg_ImmInlineExport_vtable {
  haxorg_ImmBoxOfStr const*(*)() get_exporter;
  haxorg_ImmBoxOfStr const*(*)() get_content;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmInlineExport)}
struct haxorg_ImmInlineExport {
  haxorg_ImmInlineExport_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmInlineExport(haxorg_ImmInlineExport* obj);
struct haxorg_ImmEscaped_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmEscaped)}
struct haxorg_ImmEscaped {
  haxorg_ImmEscaped_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmEscaped(haxorg_ImmEscaped* obj);
struct haxorg_ImmNewline_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmNewline)}
struct haxorg_ImmNewline {
  haxorg_ImmNewline_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmNewline(haxorg_ImmNewline* obj);
struct haxorg_ImmSpace_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmSpace)}
struct haxorg_ImmSpace {
  haxorg_ImmSpace_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmSpace(haxorg_ImmSpace* obj);
struct haxorg_ImmWord_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmWord)}
struct haxorg_ImmWord {
  haxorg_ImmWord_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmWord(haxorg_ImmWord* obj);
struct haxorg_ImmAtMention_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmAtMention)}
struct haxorg_ImmAtMention {
  haxorg_ImmAtMention_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAtMention(haxorg_ImmAtMention* obj);
struct haxorg_ImmRawText_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmRawText)}
struct haxorg_ImmRawText {
  haxorg_ImmRawText_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmRawText(haxorg_ImmRawText* obj);
struct haxorg_ImmPunctuation_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmPunctuation)}
struct haxorg_ImmPunctuation {
  haxorg_ImmPunctuation_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmPunctuation(haxorg_ImmPunctuation* obj);
struct haxorg_ImmPlaceholder_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmPlaceholder)}
struct haxorg_ImmPlaceholder {
  haxorg_ImmPlaceholder_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmPlaceholder(haxorg_ImmPlaceholder* obj);
struct haxorg_ImmBigIdent_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmBigIdent)}
struct haxorg_ImmBigIdent {
  haxorg_ImmBigIdent_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmBigIdent(haxorg_ImmBigIdent* obj);
struct haxorg_ImmTextTarget_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmTextTarget)}
struct haxorg_ImmTextTarget {
  haxorg_ImmTextTarget_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmTextTarget(haxorg_ImmTextTarget* obj);
struct haxorg_ImmErrorSkipToken_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmErrorSkipToken)}
struct haxorg_ImmErrorSkipToken {
  haxorg_ImmErrorSkipToken_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmErrorSkipToken(haxorg_ImmErrorSkipToken* obj);
struct haxorg_ImmBold_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmBold)}
struct haxorg_ImmBold {
  haxorg_ImmBold_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmBold(haxorg_ImmBold* obj);
struct haxorg_ImmUnderline_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmUnderline)}
struct haxorg_ImmUnderline {
  haxorg_ImmUnderline_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmUnderline(haxorg_ImmUnderline* obj);
struct haxorg_ImmMonospace_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmMonospace)}
struct haxorg_ImmMonospace {
  haxorg_ImmMonospace_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmMonospace(haxorg_ImmMonospace* obj);
struct haxorg_ImmMarkQuote_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmMarkQuote)}
struct haxorg_ImmMarkQuote {
  haxorg_ImmMarkQuote_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmMarkQuote(haxorg_ImmMarkQuote* obj);
struct haxorg_ImmVerbatim_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmVerbatim)}
struct haxorg_ImmVerbatim {
  haxorg_ImmVerbatim_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmVerbatim(haxorg_ImmVerbatim* obj);
struct haxorg_ImmItalic_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmItalic)}
struct haxorg_ImmItalic {
  haxorg_ImmItalic_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmItalic(haxorg_ImmItalic* obj);
struct haxorg_ImmStrike_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmStrike)}
struct haxorg_ImmStrike {
  haxorg_ImmStrike_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmStrike(haxorg_ImmStrike* obj);
struct haxorg_ImmPar_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmPar)}
struct haxorg_ImmPar {
  haxorg_ImmPar_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmPar(haxorg_ImmPar* obj);
struct haxorg_ImmAdapterStmtAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterStmtAPI)}
struct haxorg_ImmAdapterStmtAPI {
  haxorg_ImmAdapterStmtAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterStmtAPI(haxorg_ImmAdapterStmtAPI* obj);
struct haxorg_ImmAdapterSubtreeAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterSubtreeAPI)}
struct haxorg_ImmAdapterSubtreeAPI {
  haxorg_ImmAdapterSubtreeAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterSubtreeAPI(haxorg_ImmAdapterSubtreeAPI* obj);
struct haxorg_ImmAdapterNoNodeAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterNoNodeAPI)}
struct haxorg_ImmAdapterNoNodeAPI {
  haxorg_ImmAdapterNoNodeAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterNoNodeAPI(haxorg_ImmAdapterNoNodeAPI* obj);
struct haxorg_ImmAdapterAttrAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterAttrAPI)}
struct haxorg_ImmAdapterAttrAPI {
  haxorg_ImmAdapterAttrAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterAttrAPI(haxorg_ImmAdapterAttrAPI* obj);
struct haxorg_ImmAdapterAttrListAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterAttrListAPI)}
struct haxorg_ImmAdapterAttrListAPI {
  haxorg_ImmAdapterAttrListAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterAttrListAPI(haxorg_ImmAdapterAttrListAPI* obj);
struct haxorg_ImmAdapterAttrsAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterAttrsAPI)}
struct haxorg_ImmAdapterAttrsAPI {
  haxorg_ImmAdapterAttrsAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterAttrsAPI(haxorg_ImmAdapterAttrsAPI* obj);
struct haxorg_ImmAdapterErrorItemAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterErrorItemAPI)}
struct haxorg_ImmAdapterErrorItemAPI {
  haxorg_ImmAdapterErrorItemAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterErrorItemAPI(haxorg_ImmAdapterErrorItemAPI* obj);
struct haxorg_ImmAdapterErrorGroupAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterErrorGroupAPI)}
struct haxorg_ImmAdapterErrorGroupAPI {
  haxorg_ImmAdapterErrorGroupAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterErrorGroupAPI(haxorg_ImmAdapterErrorGroupAPI* obj);
struct haxorg_ImmAdapterErrorSkipGroupAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterErrorSkipGroupAPI)}
struct haxorg_ImmAdapterErrorSkipGroupAPI {
  haxorg_ImmAdapterErrorSkipGroupAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterErrorSkipGroupAPI(haxorg_ImmAdapterErrorSkipGroupAPI* obj);
struct haxorg_ImmAdapterErrorSkipTokenAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterErrorSkipTokenAPI)}
struct haxorg_ImmAdapterErrorSkipTokenAPI {
  haxorg_ImmAdapterErrorSkipTokenAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterErrorSkipTokenAPI(haxorg_ImmAdapterErrorSkipTokenAPI* obj);
struct haxorg_ImmAdapterStmtListAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterStmtListAPI)}
struct haxorg_ImmAdapterStmtListAPI {
  haxorg_ImmAdapterStmtListAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterStmtListAPI(haxorg_ImmAdapterStmtListAPI* obj);
struct haxorg_ImmAdapterEmptyAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterEmptyAPI)}
struct haxorg_ImmAdapterEmptyAPI {
  haxorg_ImmAdapterEmptyAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterEmptyAPI(haxorg_ImmAdapterEmptyAPI* obj);
struct haxorg_ImmAdapterInlineAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterInlineAPI)}
struct haxorg_ImmAdapterInlineAPI {
  haxorg_ImmAdapterInlineAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterInlineAPI(haxorg_ImmAdapterInlineAPI* obj);
struct haxorg_ImmAdapterTimeAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterTimeAPI)}
struct haxorg_ImmAdapterTimeAPI {
  haxorg_ImmAdapterTimeAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterTimeAPI(haxorg_ImmAdapterTimeAPI* obj);
struct haxorg_ImmAdapterTimeRangeAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterTimeRangeAPI)}
struct haxorg_ImmAdapterTimeRangeAPI {
  haxorg_ImmAdapterTimeRangeAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterTimeRangeAPI(haxorg_ImmAdapterTimeRangeAPI* obj);
struct haxorg_ImmAdapterMacroAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterMacroAPI)}
struct haxorg_ImmAdapterMacroAPI {
  haxorg_ImmAdapterMacroAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterMacroAPI(haxorg_ImmAdapterMacroAPI* obj);
struct haxorg_ImmAdapterSymbolAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterSymbolAPI)}
struct haxorg_ImmAdapterSymbolAPI {
  haxorg_ImmAdapterSymbolAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterSymbolAPI(haxorg_ImmAdapterSymbolAPI* obj);
struct haxorg_ImmAdapterLeafAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterLeafAPI)}
struct haxorg_ImmAdapterLeafAPI {
  haxorg_ImmAdapterLeafAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterLeafAPI(haxorg_ImmAdapterLeafAPI* obj);
struct haxorg_ImmAdapterMarkupAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterMarkupAPI)}
struct haxorg_ImmAdapterMarkupAPI {
  haxorg_ImmAdapterMarkupAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterMarkupAPI(haxorg_ImmAdapterMarkupAPI* obj);
struct haxorg_ImmAdapterLatexAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterLatexAPI)}
struct haxorg_ImmAdapterLatexAPI {
  haxorg_ImmAdapterLatexAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterLatexAPI(haxorg_ImmAdapterLatexAPI* obj);
struct haxorg_ImmAdapterSubtreeLogAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterSubtreeLogAPI)}
struct haxorg_ImmAdapterSubtreeLogAPI {
  haxorg_ImmAdapterSubtreeLogAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterSubtreeLogAPI(haxorg_ImmAdapterSubtreeLogAPI* obj);
struct haxorg_ImmAdapterColonExampleAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterColonExampleAPI)}
struct haxorg_ImmAdapterColonExampleAPI {
  haxorg_ImmAdapterColonExampleAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterColonExampleAPI(haxorg_ImmAdapterColonExampleAPI* obj);
struct haxorg_ImmAdapterCallAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterCallAPI)}
struct haxorg_ImmAdapterCallAPI {
  haxorg_ImmAdapterCallAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterCallAPI(haxorg_ImmAdapterCallAPI* obj);
struct haxorg_ImmAdapterFileAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterFileAPI)}
struct haxorg_ImmAdapterFileAPI {
  haxorg_ImmAdapterFileAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterFileAPI(haxorg_ImmAdapterFileAPI* obj);
struct haxorg_ImmAdapterDirectoryAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterDirectoryAPI)}
struct haxorg_ImmAdapterDirectoryAPI {
  haxorg_ImmAdapterDirectoryAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterDirectoryAPI(haxorg_ImmAdapterDirectoryAPI* obj);
struct haxorg_ImmAdapterSymlinkAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterSymlinkAPI)}
struct haxorg_ImmAdapterSymlinkAPI {
  haxorg_ImmAdapterSymlinkAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterSymlinkAPI(haxorg_ImmAdapterSymlinkAPI* obj);
struct haxorg_ImmAdapterDocumentFragmentAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterDocumentFragmentAPI)}
struct haxorg_ImmAdapterDocumentFragmentAPI {
  haxorg_ImmAdapterDocumentFragmentAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterDocumentFragmentAPI(haxorg_ImmAdapterDocumentFragmentAPI* obj);
struct haxorg_ImmAdapterCriticMarkupAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterCriticMarkupAPI)}
struct haxorg_ImmAdapterCriticMarkupAPI {
  haxorg_ImmAdapterCriticMarkupAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterCriticMarkupAPI(haxorg_ImmAdapterCriticMarkupAPI* obj);
struct haxorg_ImmAdapterListItemAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterListItemAPI)}
struct haxorg_ImmAdapterListItemAPI {
  haxorg_ImmAdapterListItemAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterListItemAPI(haxorg_ImmAdapterListItemAPI* obj);
struct haxorg_ImmAdapterDocumentOptionsAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterDocumentOptionsAPI)}
struct haxorg_ImmAdapterDocumentOptionsAPI {
  haxorg_ImmAdapterDocumentOptionsAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterDocumentOptionsAPI(haxorg_ImmAdapterDocumentOptionsAPI* obj);
struct haxorg_ImmAdapterDocumentAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterDocumentAPI)}
struct haxorg_ImmAdapterDocumentAPI {
  haxorg_ImmAdapterDocumentAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterDocumentAPI(haxorg_ImmAdapterDocumentAPI* obj);
struct haxorg_ImmAdapterFileTargetAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterFileTargetAPI)}
struct haxorg_ImmAdapterFileTargetAPI {
  haxorg_ImmAdapterFileTargetAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterFileTargetAPI(haxorg_ImmAdapterFileTargetAPI* obj);
struct haxorg_ImmAdapterTextSeparatorAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterTextSeparatorAPI)}
struct haxorg_ImmAdapterTextSeparatorAPI {
  haxorg_ImmAdapterTextSeparatorAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterTextSeparatorAPI(haxorg_ImmAdapterTextSeparatorAPI* obj);
struct haxorg_ImmAdapterCmdIncludeAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterCmdIncludeAPI)}
struct haxorg_ImmAdapterCmdIncludeAPI {
  haxorg_ImmAdapterCmdIncludeAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterCmdIncludeAPI(haxorg_ImmAdapterCmdIncludeAPI* obj);
struct haxorg_ImmAdapterDocumentGroupAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterDocumentGroupAPI)}
struct haxorg_ImmAdapterDocumentGroupAPI {
  haxorg_ImmAdapterDocumentGroupAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterDocumentGroupAPI(haxorg_ImmAdapterDocumentGroupAPI* obj);
struct haxorg_Block_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Block)}
struct haxorg_Block {
  haxorg_Block_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Block(haxorg_Block* obj);
struct haxorg_LineCommand_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(LineCommand)}
struct haxorg_LineCommand {
  haxorg_LineCommand_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_LineCommand(haxorg_LineCommand* obj);
struct haxorg_CmdCreator_vtable {
  haxorg_SemId const*(*)() get_text;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(CmdCreator)}
struct haxorg_CmdCreator {
  haxorg_CmdCreator_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_CmdCreator(haxorg_CmdCreator* obj);
struct haxorg_CmdAuthor_vtable {
  haxorg_SemId const*(*)() get_text;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(CmdAuthor)}
struct haxorg_CmdAuthor {
  haxorg_CmdAuthor_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_CmdAuthor(haxorg_CmdAuthor* obj);
struct haxorg_CmdEmail_vtable {
  haxorg_Str const*(*)() get_text;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(CmdEmail)}
struct haxorg_CmdEmail {
  haxorg_CmdEmail_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_CmdEmail(haxorg_CmdEmail* obj);
struct haxorg_CmdLanguage_vtable {
  haxorg_Str const*(*)() get_text;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(CmdLanguage)}
struct haxorg_CmdLanguage {
  haxorg_CmdLanguage_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_CmdLanguage(haxorg_CmdLanguage* obj);
struct haxorg_CmdCustomArgs_vtable {
  haxorg_Str const*(*)() get_name;
  bool const*(*)() get_isAttached;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(CmdCustomArgs)}
struct haxorg_CmdCustomArgs {
  haxorg_CmdCustomArgs_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_CmdCustomArgs(haxorg_CmdCustomArgs* obj);
struct haxorg_CmdTblfm_vtable {
  haxorg_Tblfm const*(*)() get_expr;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(CmdTblfm)}
struct haxorg_CmdTblfm {
  haxorg_CmdTblfm_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_CmdTblfm(haxorg_CmdTblfm* obj);
struct haxorg_Cell_vtable {
  bool const*(*)() get_isBlock;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Cell)}
struct haxorg_Cell {
  haxorg_Cell_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Cell(haxorg_Cell* obj);
struct haxorg_Row_vtable {
  haxorg_CHstdVec const*(*)() get_cells;
  bool const*(*)() get_isBlock;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Row)}
struct haxorg_Row {
  haxorg_Row_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Row(haxorg_Row* obj);
struct haxorg_ImmBlock_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmBlock)}
struct haxorg_ImmBlock {
  haxorg_ImmBlock_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmBlock(haxorg_ImmBlock* obj);
struct haxorg_ImmLineCommand_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmLineCommand)}
struct haxorg_ImmLineCommand {
  haxorg_ImmLineCommand_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmLineCommand(haxorg_ImmLineCommand* obj);
struct haxorg_ImmCmdCreator_vtable {
  haxorg_ImmIdTOfImmParagraph const*(*)() get_text;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmCmdCreator)}
struct haxorg_ImmCmdCreator {
  haxorg_ImmCmdCreator_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmdCreator(haxorg_ImmCmdCreator* obj);
struct haxorg_ImmCmdAuthor_vtable {
  haxorg_ImmIdTOfImmParagraph const*(*)() get_text;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmCmdAuthor)}
struct haxorg_ImmCmdAuthor {
  haxorg_ImmCmdAuthor_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmdAuthor(haxorg_ImmCmdAuthor* obj);
struct haxorg_ImmCmdEmail_vtable {
  haxorg_ImmBoxOfStr const*(*)() get_text;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmCmdEmail)}
struct haxorg_ImmCmdEmail {
  haxorg_ImmCmdEmail_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmdEmail(haxorg_ImmCmdEmail* obj);
struct haxorg_ImmCmdLanguage_vtable {
  haxorg_ImmBoxOfStr const*(*)() get_text;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmCmdLanguage)}
struct haxorg_ImmCmdLanguage {
  haxorg_ImmCmdLanguage_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmdLanguage(haxorg_ImmCmdLanguage* obj);
struct haxorg_ImmCmdCustomArgs_vtable {
  haxorg_ImmBoxOfStr const*(*)() get_name;
  bool const*(*)() get_isAttached;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmCmdCustomArgs)}
struct haxorg_ImmCmdCustomArgs {
  haxorg_ImmCmdCustomArgs_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmdCustomArgs(haxorg_ImmCmdCustomArgs* obj);
struct haxorg_ImmCmdTblfm_vtable {
  haxorg_Tblfm const*(*)() get_expr;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmCmdTblfm)}
struct haxorg_ImmCmdTblfm {
  haxorg_ImmCmdTblfm_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmdTblfm(haxorg_ImmCmdTblfm* obj);
struct haxorg_ImmCell_vtable {
  bool const*(*)() get_isBlock;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmCell)}
struct haxorg_ImmCell {
  haxorg_ImmCell_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCell(haxorg_ImmCell* obj);
struct haxorg_ImmRow_vtable {
  haxorg_ImmVecOfImmIdTOfImmCell const*(*)() get_cells;
  bool const*(*)() get_isBlock;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmRow)}
struct haxorg_ImmRow {
  haxorg_ImmRow_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmRow(haxorg_ImmRow* obj);
struct haxorg_ImmAdapterCmdAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterCmdAPI)}
struct haxorg_ImmAdapterCmdAPI {
  haxorg_ImmAdapterCmdAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterCmdAPI(haxorg_ImmAdapterCmdAPI* obj);
struct haxorg_ImmAdapterCmdCustomRawAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterCmdCustomRawAPI)}
struct haxorg_ImmAdapterCmdCustomRawAPI {
  haxorg_ImmAdapterCmdCustomRawAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterCmdCustomRawAPI(haxorg_ImmAdapterCmdCustomRawAPI* obj);
struct haxorg_ImmAdapterCmdCustomTextAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterCmdCustomTextAPI)}
struct haxorg_ImmAdapterCmdCustomTextAPI {
  haxorg_ImmAdapterCmdCustomTextAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterCmdCustomTextAPI(haxorg_ImmAdapterCmdCustomTextAPI* obj);
struct haxorg_ImmAdapterLinkAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterLinkAPI)}
struct haxorg_ImmAdapterLinkAPI {
  haxorg_ImmAdapterLinkAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterLinkAPI(haxorg_ImmAdapterLinkAPI* obj);
struct haxorg_ImmAdapterBlockCommentAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterBlockCommentAPI)}
struct haxorg_ImmAdapterBlockCommentAPI {
  haxorg_ImmAdapterBlockCommentAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterBlockCommentAPI(haxorg_ImmAdapterBlockCommentAPI* obj);
struct haxorg_ImmAdapterParagraphAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterParagraphAPI)}
struct haxorg_ImmAdapterParagraphAPI {
  haxorg_ImmAdapterParagraphAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterParagraphAPI(haxorg_ImmAdapterParagraphAPI* obj);
struct haxorg_ImmAdapterListAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterListAPI)}
struct haxorg_ImmAdapterListAPI {
  haxorg_ImmAdapterListAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterListAPI(haxorg_ImmAdapterListAPI* obj);
struct haxorg_ImmStmtAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmStmt)}>)}
struct haxorg_ImmStmtAdapter {
  haxorg_ImmStmtAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmStmtAdapter(haxorg_ImmStmtAdapter* obj);
struct haxorg_ImmSubtreeAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmSubtree)}>)}
struct haxorg_ImmSubtreeAdapter {
  haxorg_ImmSubtreeAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmSubtreeAdapter(haxorg_ImmSubtreeAdapter* obj);
struct haxorg_ImmNoNodeAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmNoNode)}>)}
struct haxorg_ImmNoNodeAdapter {
  haxorg_ImmNoNodeAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmNoNodeAdapter(haxorg_ImmNoNodeAdapter* obj);
struct haxorg_ImmErrorItemAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmErrorItem)}>)}
struct haxorg_ImmErrorItemAdapter {
  haxorg_ImmErrorItemAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmErrorItemAdapter(haxorg_ImmErrorItemAdapter* obj);
struct haxorg_ImmErrorGroupAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmErrorGroup)}>)}
struct haxorg_ImmErrorGroupAdapter {
  haxorg_ImmErrorGroupAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmErrorGroupAdapter(haxorg_ImmErrorGroupAdapter* obj);
struct haxorg_ImmErrorSkipGroupAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmErrorSkipGroup)}>)}
struct haxorg_ImmErrorSkipGroupAdapter {
  haxorg_ImmErrorSkipGroupAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmErrorSkipGroupAdapter(haxorg_ImmErrorSkipGroupAdapter* obj);
struct haxorg_ImmErrorSkipTokenAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmErrorSkipToken)}>)}
struct haxorg_ImmErrorSkipTokenAdapter {
  haxorg_ImmErrorSkipTokenAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmErrorSkipTokenAdapter(haxorg_ImmErrorSkipTokenAdapter* obj);
struct haxorg_ImmStmtListAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmStmtList)}>)}
struct haxorg_ImmStmtListAdapter {
  haxorg_ImmStmtListAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmStmtListAdapter(haxorg_ImmStmtListAdapter* obj);
struct haxorg_ImmEmptyAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmEmpty)}>)}
struct haxorg_ImmEmptyAdapter {
  haxorg_ImmEmptyAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmEmptyAdapter(haxorg_ImmEmptyAdapter* obj);
struct haxorg_ImmAdapterHashTagAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterHashTagAPI)}
struct haxorg_ImmAdapterHashTagAPI {
  haxorg_ImmAdapterHashTagAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterHashTagAPI(haxorg_ImmAdapterHashTagAPI* obj);
struct haxorg_ImmAdapterInlineFootnoteAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterInlineFootnoteAPI)}
struct haxorg_ImmAdapterInlineFootnoteAPI {
  haxorg_ImmAdapterInlineFootnoteAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterInlineFootnoteAPI(haxorg_ImmAdapterInlineFootnoteAPI* obj);
struct haxorg_ImmAdapterSubtreeCompletionAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterSubtreeCompletionAPI)}
struct haxorg_ImmAdapterSubtreeCompletionAPI {
  haxorg_ImmAdapterSubtreeCompletionAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterSubtreeCompletionAPI(haxorg_ImmAdapterSubtreeCompletionAPI* obj);
struct haxorg_ImmInlineAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmInline)}>)}
struct haxorg_ImmInlineAdapter {
  haxorg_ImmInlineAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmInlineAdapter(haxorg_ImmInlineAdapter* obj);
struct haxorg_ImmTimeAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmTime)}>)}
struct haxorg_ImmTimeAdapter {
  haxorg_ImmTimeAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmTimeAdapter(haxorg_ImmTimeAdapter* obj);
struct haxorg_ImmTimeRangeAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmTimeRange)}>)}
struct haxorg_ImmTimeRangeAdapter {
  haxorg_ImmTimeRangeAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmTimeRangeAdapter(haxorg_ImmTimeRangeAdapter* obj);
struct haxorg_ImmMacroAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmMacro)}>)}
struct haxorg_ImmMacroAdapter {
  haxorg_ImmMacroAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmMacroAdapter(haxorg_ImmMacroAdapter* obj);
struct haxorg_ImmSymbolAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmSymbol)}>)}
struct haxorg_ImmSymbolAdapter {
  haxorg_ImmSymbolAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmSymbolAdapter(haxorg_ImmSymbolAdapter* obj);
struct haxorg_ImmAdapterEscapedAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterEscapedAPI)}
struct haxorg_ImmAdapterEscapedAPI {
  haxorg_ImmAdapterEscapedAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterEscapedAPI(haxorg_ImmAdapterEscapedAPI* obj);
struct haxorg_ImmAdapterNewlineAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterNewlineAPI)}
struct haxorg_ImmAdapterNewlineAPI {
  haxorg_ImmAdapterNewlineAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterNewlineAPI(haxorg_ImmAdapterNewlineAPI* obj);
struct haxorg_ImmAdapterSpaceAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterSpaceAPI)}
struct haxorg_ImmAdapterSpaceAPI {
  haxorg_ImmAdapterSpaceAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterSpaceAPI(haxorg_ImmAdapterSpaceAPI* obj);
struct haxorg_ImmAdapterWordAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterWordAPI)}
struct haxorg_ImmAdapterWordAPI {
  haxorg_ImmAdapterWordAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterWordAPI(haxorg_ImmAdapterWordAPI* obj);
struct haxorg_ImmAdapterAtMentionAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterAtMentionAPI)}
struct haxorg_ImmAdapterAtMentionAPI {
  haxorg_ImmAdapterAtMentionAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterAtMentionAPI(haxorg_ImmAdapterAtMentionAPI* obj);
struct haxorg_ImmAdapterRawTextAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterRawTextAPI)}
struct haxorg_ImmAdapterRawTextAPI {
  haxorg_ImmAdapterRawTextAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterRawTextAPI(haxorg_ImmAdapterRawTextAPI* obj);
struct haxorg_ImmAdapterPunctuationAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterPunctuationAPI)}
struct haxorg_ImmAdapterPunctuationAPI {
  haxorg_ImmAdapterPunctuationAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterPunctuationAPI(haxorg_ImmAdapterPunctuationAPI* obj);
struct haxorg_ImmAdapterPlaceholderAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterPlaceholderAPI)}
struct haxorg_ImmAdapterPlaceholderAPI {
  haxorg_ImmAdapterPlaceholderAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterPlaceholderAPI(haxorg_ImmAdapterPlaceholderAPI* obj);
struct haxorg_ImmAdapterBigIdentAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterBigIdentAPI)}
struct haxorg_ImmAdapterBigIdentAPI {
  haxorg_ImmAdapterBigIdentAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterBigIdentAPI(haxorg_ImmAdapterBigIdentAPI* obj);
struct haxorg_ImmAdapterTextTargetAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterTextTargetAPI)}
struct haxorg_ImmAdapterTextTargetAPI {
  haxorg_ImmAdapterTextTargetAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterTextTargetAPI(haxorg_ImmAdapterTextTargetAPI* obj);
struct haxorg_ImmLeafAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmLeaf)}>)}
struct haxorg_ImmLeafAdapter {
  haxorg_ImmLeafAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmLeafAdapter(haxorg_ImmLeafAdapter* obj);
struct haxorg_ImmAdapterBoldAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterBoldAPI)}
struct haxorg_ImmAdapterBoldAPI {
  haxorg_ImmAdapterBoldAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterBoldAPI(haxorg_ImmAdapterBoldAPI* obj);
struct haxorg_ImmAdapterUnderlineAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterUnderlineAPI)}
struct haxorg_ImmAdapterUnderlineAPI {
  haxorg_ImmAdapterUnderlineAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterUnderlineAPI(haxorg_ImmAdapterUnderlineAPI* obj);
struct haxorg_ImmAdapterMonospaceAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterMonospaceAPI)}
struct haxorg_ImmAdapterMonospaceAPI {
  haxorg_ImmAdapterMonospaceAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterMonospaceAPI(haxorg_ImmAdapterMonospaceAPI* obj);
struct haxorg_ImmAdapterMarkQuoteAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterMarkQuoteAPI)}
struct haxorg_ImmAdapterMarkQuoteAPI {
  haxorg_ImmAdapterMarkQuoteAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterMarkQuoteAPI(haxorg_ImmAdapterMarkQuoteAPI* obj);
struct haxorg_ImmAdapterRadioTargetAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterRadioTargetAPI)}
struct haxorg_ImmAdapterRadioTargetAPI {
  haxorg_ImmAdapterRadioTargetAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterRadioTargetAPI(haxorg_ImmAdapterRadioTargetAPI* obj);
struct haxorg_ImmAdapterVerbatimAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterVerbatimAPI)}
struct haxorg_ImmAdapterVerbatimAPI {
  haxorg_ImmAdapterVerbatimAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterVerbatimAPI(haxorg_ImmAdapterVerbatimAPI* obj);
struct haxorg_ImmAdapterItalicAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterItalicAPI)}
struct haxorg_ImmAdapterItalicAPI {
  haxorg_ImmAdapterItalicAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterItalicAPI(haxorg_ImmAdapterItalicAPI* obj);
struct haxorg_ImmAdapterStrikeAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterStrikeAPI)}
struct haxorg_ImmAdapterStrikeAPI {
  haxorg_ImmAdapterStrikeAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterStrikeAPI(haxorg_ImmAdapterStrikeAPI* obj);
struct haxorg_ImmAdapterParAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterParAPI)}
struct haxorg_ImmAdapterParAPI {
  haxorg_ImmAdapterParAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterParAPI(haxorg_ImmAdapterParAPI* obj);
struct haxorg_ImmMarkupAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmMarkup)}>)}
struct haxorg_ImmMarkupAdapter {
  haxorg_ImmMarkupAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmMarkupAdapter(haxorg_ImmMarkupAdapter* obj);
struct haxorg_ImmLatexAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmLatex)}>)}
struct haxorg_ImmLatexAdapter {
  haxorg_ImmLatexAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmLatexAdapter(haxorg_ImmLatexAdapter* obj);
struct haxorg_ImmSubtreeLogAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmSubtreeLog)}>)}
struct haxorg_ImmSubtreeLogAdapter {
  haxorg_ImmSubtreeLogAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmSubtreeLogAdapter(haxorg_ImmSubtreeLogAdapter* obj);
struct haxorg_ImmColonExampleAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmColonExample)}>)}
struct haxorg_ImmColonExampleAdapter {
  haxorg_ImmColonExampleAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmColonExampleAdapter(haxorg_ImmColonExampleAdapter* obj);
struct haxorg_ImmCallAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmCall)}>)}
struct haxorg_ImmCallAdapter {
  haxorg_ImmCallAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCallAdapter(haxorg_ImmCallAdapter* obj);
struct haxorg_ImmFileAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmFile)}>)}
struct haxorg_ImmFileAdapter {
  haxorg_ImmFileAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmFileAdapter(haxorg_ImmFileAdapter* obj);
struct haxorg_ImmDirectoryAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmDirectory)}>)}
struct haxorg_ImmDirectoryAdapter {
  haxorg_ImmDirectoryAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmDirectoryAdapter(haxorg_ImmDirectoryAdapter* obj);
struct haxorg_ImmSymlinkAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmSymlink)}>)}
struct haxorg_ImmSymlinkAdapter {
  haxorg_ImmSymlinkAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmSymlinkAdapter(haxorg_ImmSymlinkAdapter* obj);
struct haxorg_ImmDocumentFragmentAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmDocumentFragment)}>)}
struct haxorg_ImmDocumentFragmentAdapter {
  haxorg_ImmDocumentFragmentAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmDocumentFragmentAdapter(haxorg_ImmDocumentFragmentAdapter* obj);
struct haxorg_ImmCriticMarkupAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmCriticMarkup)}>)}
struct haxorg_ImmCriticMarkupAdapter {
  haxorg_ImmCriticMarkupAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCriticMarkupAdapter(haxorg_ImmCriticMarkupAdapter* obj);
struct haxorg_ImmListItemAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmListItem)}>)}
struct haxorg_ImmListItemAdapter {
  haxorg_ImmListItemAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmListItemAdapter(haxorg_ImmListItemAdapter* obj);
struct haxorg_ImmDocumentOptionsAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmDocumentOptions)}>)}
struct haxorg_ImmDocumentOptionsAdapter {
  haxorg_ImmDocumentOptionsAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmDocumentOptionsAdapter(haxorg_ImmDocumentOptionsAdapter* obj);
struct haxorg_ImmDocumentAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmDocument)}>)}
struct haxorg_ImmDocumentAdapter {
  haxorg_ImmDocumentAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmDocumentAdapter(haxorg_ImmDocumentAdapter* obj);
struct haxorg_ImmFileTargetAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmFileTarget)}>)}
struct haxorg_ImmFileTargetAdapter {
  haxorg_ImmFileTargetAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmFileTargetAdapter(haxorg_ImmFileTargetAdapter* obj);
struct haxorg_ImmTextSeparatorAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmTextSeparator)}>)}
struct haxorg_ImmTextSeparatorAdapter {
  haxorg_ImmTextSeparatorAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmTextSeparatorAdapter(haxorg_ImmTextSeparatorAdapter* obj);
struct haxorg_ImmCmdIncludeAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmCmdInclude)}>)}
struct haxorg_ImmCmdIncludeAdapter {
  haxorg_ImmCmdIncludeAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmdIncludeAdapter(haxorg_ImmCmdIncludeAdapter* obj);
struct haxorg_ImmDocumentGroupAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmDocumentGroup)}>)}
struct haxorg_ImmDocumentGroupAdapter {
  haxorg_ImmDocumentGroupAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmDocumentGroupAdapter(haxorg_ImmDocumentGroupAdapter* obj);
struct haxorg_BlockCenter_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(BlockCenter)}
struct haxorg_BlockCenter {
  haxorg_BlockCenter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_BlockCenter(haxorg_BlockCenter* obj);
struct haxorg_BlockQuote_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(BlockQuote)}
struct haxorg_BlockQuote {
  haxorg_BlockQuote_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_BlockQuote(haxorg_BlockQuote* obj);
struct haxorg_BlockVerse_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(BlockVerse)}
struct haxorg_BlockVerse {
  haxorg_BlockVerse_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_BlockVerse(haxorg_BlockVerse* obj);
struct haxorg_BlockDynamicFallback_vtable {
  haxorg_Str const*(*)() get_name;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(BlockDynamicFallback)}
struct haxorg_BlockDynamicFallback {
  haxorg_BlockDynamicFallback_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_BlockDynamicFallback(haxorg_BlockDynamicFallback* obj);
struct haxorg_BlockExample_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(BlockExample)}
struct haxorg_BlockExample {
  haxorg_BlockExample_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_BlockExample(haxorg_BlockExample* obj);
struct haxorg_BlockExport_vtable {
  haxorg_Str const*(*)() get_exporter;
  haxorg_Str const*(*)() get_content;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(BlockExport)}
struct haxorg_BlockExport {
  haxorg_BlockExport_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_BlockExport(haxorg_BlockExport* obj);
struct haxorg_BlockAdmonition_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(BlockAdmonition)}
struct haxorg_BlockAdmonition {
  haxorg_BlockAdmonition_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_BlockAdmonition(haxorg_BlockAdmonition* obj);
struct haxorg_BlockCodeEvalResult_vtable {
  haxorg_CHstdVec const*(*)() get_raw;
  haxorg_SemId const*(*)() get_node;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(BlockCodeEvalResult)}
struct haxorg_BlockCodeEvalResult {
  haxorg_BlockCodeEvalResult_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_BlockCodeEvalResult(haxorg_BlockCodeEvalResult* obj);
struct haxorg_BlockCode_vtable {
  haxorg_OptOfStr const*(*)() get_lang;
  haxorg_CHstdVec const*(*)() get_result;
  haxorg_CHstdVec const*(*)() get_lines;
  haxorg_AttrGroup const*(*)() get_switches;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(BlockCode)}
struct haxorg_BlockCode {
  haxorg_BlockCode_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_BlockCode(haxorg_BlockCode* obj);
struct haxorg_Table_vtable {
  haxorg_CHstdVec const*(*)() get_rows;
  bool const*(*)() get_isBlock;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Table)}
struct haxorg_Table {
  haxorg_Table_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Table(haxorg_Table* obj);
struct haxorg_Attached_vtable {};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(Attached)}
struct haxorg_Attached {
  haxorg_Attached_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_Attached(haxorg_Attached* obj);
struct haxorg_ImmBlockCenter_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmBlockCenter)}
struct haxorg_ImmBlockCenter {
  haxorg_ImmBlockCenter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmBlockCenter(haxorg_ImmBlockCenter* obj);
struct haxorg_ImmBlockQuote_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmBlockQuote)}
struct haxorg_ImmBlockQuote {
  haxorg_ImmBlockQuote_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmBlockQuote(haxorg_ImmBlockQuote* obj);
struct haxorg_ImmBlockVerse_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmBlockVerse)}
struct haxorg_ImmBlockVerse {
  haxorg_ImmBlockVerse_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmBlockVerse(haxorg_ImmBlockVerse* obj);
struct haxorg_ImmBlockDynamicFallback_vtable {
  haxorg_ImmBoxOfStr const*(*)() get_name;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmBlockDynamicFallback)}
struct haxorg_ImmBlockDynamicFallback {
  haxorg_ImmBlockDynamicFallback_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmBlockDynamicFallback(haxorg_ImmBlockDynamicFallback* obj);
struct haxorg_ImmBlockExample_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmBlockExample)}
struct haxorg_ImmBlockExample {
  haxorg_ImmBlockExample_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmBlockExample(haxorg_ImmBlockExample* obj);
struct haxorg_ImmBlockExport_vtable {
  haxorg_ImmBoxOfStr const*(*)() get_exporter;
  haxorg_ImmBoxOfStr const*(*)() get_content;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmBlockExport)}
struct haxorg_ImmBlockExport {
  haxorg_ImmBlockExport_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmBlockExport(haxorg_ImmBlockExport* obj);
struct haxorg_ImmBlockAdmonition_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmBlockAdmonition)}
struct haxorg_ImmBlockAdmonition {
  haxorg_ImmBlockAdmonition_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmBlockAdmonition(haxorg_ImmBlockAdmonition* obj);
struct haxorg_ImmBlockCodeEvalResult_vtable {
  haxorg_ImmVecOfOrgCodeEvalOutput const*(*)() get_raw;
  haxorg_ImmIdTOfImmOrg const*(*)() get_node;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmBlockCodeEvalResult)}
struct haxorg_ImmBlockCodeEvalResult {
  haxorg_ImmBlockCodeEvalResult_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmBlockCodeEvalResult(haxorg_ImmBlockCodeEvalResult* obj);
struct haxorg_ImmBlockCode_vtable {
  haxorg_ImmBoxOfOptOfStr const*(*)() get_lang;
  haxorg_ImmVecOfImmIdTOfImmBlockCodeEvalResult const*(*)() get_result;
  haxorg_ImmVecOfBlockCodeLine const*(*)() get_lines;
  haxorg_AttrGroup const*(*)() get_switches;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmBlockCode)}
struct haxorg_ImmBlockCode {
  haxorg_ImmBlockCode_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmBlockCode(haxorg_ImmBlockCode* obj);
struct haxorg_ImmTable_vtable {
  haxorg_ImmVecOfImmIdTOfImmRow const*(*)() get_rows;
  bool const*(*)() get_isBlock;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmTable)}
struct haxorg_ImmTable {
  haxorg_ImmTable_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmTable(haxorg_ImmTable* obj);
struct haxorg_ImmAttached_vtable {};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmAttached)}
struct haxorg_ImmAttached {
  haxorg_ImmAttached_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAttached(haxorg_ImmAttached* obj);
struct haxorg_ImmAdapterLineCommandAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterLineCommandAPI)}
struct haxorg_ImmAdapterLineCommandAPI {
  haxorg_ImmAdapterLineCommandAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterLineCommandAPI(haxorg_ImmAdapterLineCommandAPI* obj);
struct haxorg_ImmAdapterCmdCustomArgsAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterCmdCustomArgsAPI)}
struct haxorg_ImmAdapterCmdCustomArgsAPI {
  haxorg_ImmAdapterCmdCustomArgsAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterCmdCustomArgsAPI(haxorg_ImmAdapterCmdCustomArgsAPI* obj);
struct haxorg_ImmAdapterCmdCreatorAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterCmdCreatorAPI)}
struct haxorg_ImmAdapterCmdCreatorAPI {
  haxorg_ImmAdapterCmdCreatorAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterCmdCreatorAPI(haxorg_ImmAdapterCmdCreatorAPI* obj);
struct haxorg_ImmAdapterCmdAuthorAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterCmdAuthorAPI)}
struct haxorg_ImmAdapterCmdAuthorAPI {
  haxorg_ImmAdapterCmdAuthorAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterCmdAuthorAPI(haxorg_ImmAdapterCmdAuthorAPI* obj);
struct haxorg_ImmAdapterCmdEmailAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterCmdEmailAPI)}
struct haxorg_ImmAdapterCmdEmailAPI {
  haxorg_ImmAdapterCmdEmailAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterCmdEmailAPI(haxorg_ImmAdapterCmdEmailAPI* obj);
struct haxorg_ImmAdapterCmdLanguageAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterCmdLanguageAPI)}
struct haxorg_ImmAdapterCmdLanguageAPI {
  haxorg_ImmAdapterCmdLanguageAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterCmdLanguageAPI(haxorg_ImmAdapterCmdLanguageAPI* obj);
struct haxorg_ImmAdapterCmdTblfmAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterCmdTblfmAPI)}
struct haxorg_ImmAdapterCmdTblfmAPI {
  haxorg_ImmAdapterCmdTblfmAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterCmdTblfmAPI(haxorg_ImmAdapterCmdTblfmAPI* obj);
struct haxorg_ImmAdapterBlockAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterBlockAPI)}
struct haxorg_ImmAdapterBlockAPI {
  haxorg_ImmAdapterBlockAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterBlockAPI(haxorg_ImmAdapterBlockAPI* obj);
struct haxorg_ImmAdapterCellAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterCellAPI)}
struct haxorg_ImmAdapterCellAPI {
  haxorg_ImmAdapterCellAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterCellAPI(haxorg_ImmAdapterCellAPI* obj);
struct haxorg_ImmAdapterRowAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterRowAPI)}
struct haxorg_ImmAdapterRowAPI {
  haxorg_ImmAdapterRowAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterRowAPI(haxorg_ImmAdapterRowAPI* obj);
struct haxorg_ImmCmdAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmCmd)}>)}
struct haxorg_ImmCmdAdapter {
  haxorg_ImmCmdAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmdAdapter(haxorg_ImmCmdAdapter* obj);
struct haxorg_ImmCmdCustomRawAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmCmdCustomRaw)}>)}
struct haxorg_ImmCmdCustomRawAdapter {
  haxorg_ImmCmdCustomRawAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmdCustomRawAdapter(haxorg_ImmCmdCustomRawAdapter* obj);
struct haxorg_ImmCmdCustomTextAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmCmdCustomText)}>)}
struct haxorg_ImmCmdCustomTextAdapter {
  haxorg_ImmCmdCustomTextAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmdCustomTextAdapter(haxorg_ImmCmdCustomTextAdapter* obj);
struct haxorg_ImmLinkAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmLink)}>)}
struct haxorg_ImmLinkAdapter {
  haxorg_ImmLinkAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmLinkAdapter(haxorg_ImmLinkAdapter* obj);
struct haxorg_ImmBlockCommentAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmBlockComment)}>)}
struct haxorg_ImmBlockCommentAdapter {
  haxorg_ImmBlockCommentAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmBlockCommentAdapter(haxorg_ImmBlockCommentAdapter* obj);
struct haxorg_ImmParagraphAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmParagraph)}>)}
struct haxorg_ImmParagraphAdapter {
  haxorg_ImmParagraphAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmParagraphAdapter(haxorg_ImmParagraphAdapter* obj);
struct haxorg_ImmListAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmList)}>)}
struct haxorg_ImmListAdapter {
  haxorg_ImmListAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmListAdapter(haxorg_ImmListAdapter* obj);
struct haxorg_ImmHashTagAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmHashTag)}>)}
struct haxorg_ImmHashTagAdapter {
  haxorg_ImmHashTagAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmHashTagAdapter(haxorg_ImmHashTagAdapter* obj);
struct haxorg_ImmInlineFootnoteAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmInlineFootnote)}>)}
struct haxorg_ImmInlineFootnoteAdapter {
  haxorg_ImmInlineFootnoteAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmInlineFootnoteAdapter(haxorg_ImmInlineFootnoteAdapter* obj);
struct haxorg_ImmEscapedAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmEscaped)}>)}
struct haxorg_ImmEscapedAdapter {
  haxorg_ImmEscapedAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmEscapedAdapter(haxorg_ImmEscapedAdapter* obj);
struct haxorg_ImmNewlineAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmNewline)}>)}
struct haxorg_ImmNewlineAdapter {
  haxorg_ImmNewlineAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmNewlineAdapter(haxorg_ImmNewlineAdapter* obj);
struct haxorg_ImmSpaceAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmSpace)}>)}
struct haxorg_ImmSpaceAdapter {
  haxorg_ImmSpaceAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmSpaceAdapter(haxorg_ImmSpaceAdapter* obj);
struct haxorg_ImmWordAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmWord)}>)}
struct haxorg_ImmWordAdapter {
  haxorg_ImmWordAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmWordAdapter(haxorg_ImmWordAdapter* obj);
struct haxorg_ImmAtMentionAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmAtMention)}>)}
struct haxorg_ImmAtMentionAdapter {
  haxorg_ImmAtMentionAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAtMentionAdapter(haxorg_ImmAtMentionAdapter* obj);
struct haxorg_ImmRawTextAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmRawText)}>)}
struct haxorg_ImmRawTextAdapter {
  haxorg_ImmRawTextAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmRawTextAdapter(haxorg_ImmRawTextAdapter* obj);
struct haxorg_ImmPunctuationAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmPunctuation)}>)}
struct haxorg_ImmPunctuationAdapter {
  haxorg_ImmPunctuationAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmPunctuationAdapter(haxorg_ImmPunctuationAdapter* obj);
struct haxorg_ImmPlaceholderAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmPlaceholder)}>)}
struct haxorg_ImmPlaceholderAdapter {
  haxorg_ImmPlaceholderAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmPlaceholderAdapter(haxorg_ImmPlaceholderAdapter* obj);
struct haxorg_ImmBigIdentAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmBigIdent)}>)}
struct haxorg_ImmBigIdentAdapter {
  haxorg_ImmBigIdentAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmBigIdentAdapter(haxorg_ImmBigIdentAdapter* obj);
struct haxorg_ImmTextTargetAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmTextTarget)}>)}
struct haxorg_ImmTextTargetAdapter {
  haxorg_ImmTextTargetAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmTextTargetAdapter(haxorg_ImmTextTargetAdapter* obj);
struct haxorg_ImmBoldAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmBold)}>)}
struct haxorg_ImmBoldAdapter {
  haxorg_ImmBoldAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmBoldAdapter(haxorg_ImmBoldAdapter* obj);
struct haxorg_ImmUnderlineAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmUnderline)}>)}
struct haxorg_ImmUnderlineAdapter {
  haxorg_ImmUnderlineAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmUnderlineAdapter(haxorg_ImmUnderlineAdapter* obj);
struct haxorg_ImmMonospaceAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmMonospace)}>)}
struct haxorg_ImmMonospaceAdapter {
  haxorg_ImmMonospaceAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmMonospaceAdapter(haxorg_ImmMonospaceAdapter* obj);
struct haxorg_ImmMarkQuoteAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmMarkQuote)}>)}
struct haxorg_ImmMarkQuoteAdapter {
  haxorg_ImmMarkQuoteAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmMarkQuoteAdapter(haxorg_ImmMarkQuoteAdapter* obj);
struct haxorg_ImmRadioTargetAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmRadioTarget)}>)}
struct haxorg_ImmRadioTargetAdapter {
  haxorg_ImmRadioTargetAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmRadioTargetAdapter(haxorg_ImmRadioTargetAdapter* obj);
struct haxorg_ImmVerbatimAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmVerbatim)}>)}
struct haxorg_ImmVerbatimAdapter {
  haxorg_ImmVerbatimAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmVerbatimAdapter(haxorg_ImmVerbatimAdapter* obj);
struct haxorg_ImmItalicAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmItalic)}>)}
struct haxorg_ImmItalicAdapter {
  haxorg_ImmItalicAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmItalicAdapter(haxorg_ImmItalicAdapter* obj);
struct haxorg_ImmStrikeAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmStrike)}>)}
struct haxorg_ImmStrikeAdapter {
  haxorg_ImmStrikeAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmStrikeAdapter(haxorg_ImmStrikeAdapter* obj);
struct haxorg_ImmParAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmPar)}>)}
struct haxorg_ImmParAdapter {
  haxorg_ImmParAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmParAdapter(haxorg_ImmParAdapter* obj);
struct haxorg_CmdCaption_vtable {
  haxorg_SemId const*(*)() get_text;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(CmdCaption)}
struct haxorg_CmdCaption {
  haxorg_CmdCaption_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_CmdCaption(haxorg_CmdCaption* obj);
struct haxorg_CmdColumns_vtable {
  haxorg_ColumnView const*(*)() get_view;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(CmdColumns)}
struct haxorg_CmdColumns {
  haxorg_CmdColumns_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_CmdColumns(haxorg_CmdColumns* obj);
struct haxorg_CmdName_vtable {
  haxorg_Str const*(*)() get_name;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(CmdName)}
struct haxorg_CmdName {
  haxorg_CmdName_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_CmdName(haxorg_CmdName* obj);
struct haxorg_CmdCall_vtable {
  haxorg_Str const*(*)() get_name;
  haxorg_OptOfStr const*(*)() get_fileName;
  haxorg_AttrGroup const*(*)() get_insideHeaderAttrs;
  haxorg_AttrGroup const*(*)() get_callAttrs;
  haxorg_AttrGroup const*(*)() get_endHeaderAttrs;
  haxorg_CHstdVec const*(*)() get_result;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(CmdCall)}
struct haxorg_CmdCall {
  haxorg_CmdCall_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_CmdCall(haxorg_CmdCall* obj);
struct haxorg_CmdAttr_vtable {
  haxorg_Str const*(*)() get_target;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(CmdAttr)}
struct haxorg_CmdAttr {
  haxorg_CmdAttr_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_CmdAttr(haxorg_CmdAttr* obj);
struct haxorg_CmdExport_vtable {
  haxorg_Str const*(*)() get_exporter;
  haxorg_Str const*(*)() get_content;
};

/// \brief {{{REC:(org)}::REC:(sem)}::REC:(CmdExport)}
struct haxorg_CmdExport {
  haxorg_CmdExport_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_CmdExport(haxorg_CmdExport* obj);
struct haxorg_ImmCmdCaption_vtable {
  haxorg_ImmIdTOfImmParagraph const*(*)() get_text;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmCmdCaption)}
struct haxorg_ImmCmdCaption {
  haxorg_ImmCmdCaption_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmdCaption(haxorg_ImmCmdCaption* obj);
struct haxorg_ImmCmdColumns_vtable {
  haxorg_ColumnView const*(*)() get_view;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmCmdColumns)}
struct haxorg_ImmCmdColumns {
  haxorg_ImmCmdColumns_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmdColumns(haxorg_ImmCmdColumns* obj);
struct haxorg_ImmCmdName_vtable {
  haxorg_ImmBoxOfStr const*(*)() get_name;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmCmdName)}
struct haxorg_ImmCmdName {
  haxorg_ImmCmdName_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmdName(haxorg_ImmCmdName* obj);
struct haxorg_ImmCmdCall_vtable {
  haxorg_ImmBoxOfStr const*(*)() get_name;
  haxorg_ImmBoxOfOptOfStr const*(*)() get_fileName;
  haxorg_AttrGroup const*(*)() get_insideHeaderAttrs;
  haxorg_AttrGroup const*(*)() get_callAttrs;
  haxorg_AttrGroup const*(*)() get_endHeaderAttrs;
  haxorg_ImmVecOfImmIdTOfImmBlockCodeEvalResult const*(*)() get_result;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmCmdCall)}
struct haxorg_ImmCmdCall {
  haxorg_ImmCmdCall_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmdCall(haxorg_ImmCmdCall* obj);
struct haxorg_ImmCmdAttr_vtable {
  haxorg_ImmBoxOfStr const*(*)() get_target;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmCmdAttr)}
struct haxorg_ImmCmdAttr {
  haxorg_ImmCmdAttr_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmdAttr(haxorg_ImmCmdAttr* obj);
struct haxorg_ImmCmdExport_vtable {
  haxorg_ImmBoxOfStr const*(*)() get_exporter;
  haxorg_ImmBoxOfStr const*(*)() get_content;
};

/// \brief {{{REC:(org)}::REC:(imm)}::REC:(ImmCmdExport)}
struct haxorg_ImmCmdExport {
  haxorg_ImmCmdExport_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmdExport(haxorg_ImmCmdExport* obj);
struct haxorg_ImmAdapterAttachedAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterAttachedAPI)}
struct haxorg_ImmAdapterAttachedAPI {
  haxorg_ImmAdapterAttachedAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterAttachedAPI(haxorg_ImmAdapterAttachedAPI* obj);
struct haxorg_ImmLineCommandAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmLineCommand)}>)}
struct haxorg_ImmLineCommandAdapter {
  haxorg_ImmLineCommandAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmLineCommandAdapter(haxorg_ImmLineCommandAdapter* obj);
struct haxorg_ImmCmdCustomArgsAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmCmdCustomArgs)}>)}
struct haxorg_ImmCmdCustomArgsAdapter {
  haxorg_ImmCmdCustomArgsAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmdCustomArgsAdapter(haxorg_ImmCmdCustomArgsAdapter* obj);
struct haxorg_ImmCmdCreatorAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmCmdCreator)}>)}
struct haxorg_ImmCmdCreatorAdapter {
  haxorg_ImmCmdCreatorAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmdCreatorAdapter(haxorg_ImmCmdCreatorAdapter* obj);
struct haxorg_ImmCmdAuthorAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmCmdAuthor)}>)}
struct haxorg_ImmCmdAuthorAdapter {
  haxorg_ImmCmdAuthorAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmdAuthorAdapter(haxorg_ImmCmdAuthorAdapter* obj);
struct haxorg_ImmCmdEmailAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmCmdEmail)}>)}
struct haxorg_ImmCmdEmailAdapter {
  haxorg_ImmCmdEmailAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmdEmailAdapter(haxorg_ImmCmdEmailAdapter* obj);
struct haxorg_ImmCmdLanguageAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmCmdLanguage)}>)}
struct haxorg_ImmCmdLanguageAdapter {
  haxorg_ImmCmdLanguageAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmdLanguageAdapter(haxorg_ImmCmdLanguageAdapter* obj);
struct haxorg_ImmCmdTblfmAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmCmdTblfm)}>)}
struct haxorg_ImmCmdTblfmAdapter {
  haxorg_ImmCmdTblfmAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmdTblfmAdapter(haxorg_ImmCmdTblfmAdapter* obj);
struct haxorg_ImmAdapterBlockCenterAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterBlockCenterAPI)}
struct haxorg_ImmAdapterBlockCenterAPI {
  haxorg_ImmAdapterBlockCenterAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterBlockCenterAPI(haxorg_ImmAdapterBlockCenterAPI* obj);
struct haxorg_ImmAdapterBlockQuoteAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterBlockQuoteAPI)}
struct haxorg_ImmAdapterBlockQuoteAPI {
  haxorg_ImmAdapterBlockQuoteAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterBlockQuoteAPI(haxorg_ImmAdapterBlockQuoteAPI* obj);
struct haxorg_ImmAdapterBlockVerseAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterBlockVerseAPI)}
struct haxorg_ImmAdapterBlockVerseAPI {
  haxorg_ImmAdapterBlockVerseAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterBlockVerseAPI(haxorg_ImmAdapterBlockVerseAPI* obj);
struct haxorg_ImmAdapterBlockExampleAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterBlockExampleAPI)}
struct haxorg_ImmAdapterBlockExampleAPI {
  haxorg_ImmAdapterBlockExampleAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterBlockExampleAPI(haxorg_ImmAdapterBlockExampleAPI* obj);
struct haxorg_ImmAdapterInlineExportAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterInlineExportAPI)}
struct haxorg_ImmAdapterInlineExportAPI {
  haxorg_ImmAdapterInlineExportAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterInlineExportAPI(haxorg_ImmAdapterInlineExportAPI* obj);
struct haxorg_ImmAdapterCmdExportAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterCmdExportAPI)}
struct haxorg_ImmAdapterCmdExportAPI {
  haxorg_ImmAdapterCmdExportAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterCmdExportAPI(haxorg_ImmAdapterCmdExportAPI* obj);
struct haxorg_ImmAdapterBlockExportAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterBlockExportAPI)}
struct haxorg_ImmAdapterBlockExportAPI {
  haxorg_ImmAdapterBlockExportAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterBlockExportAPI(haxorg_ImmAdapterBlockExportAPI* obj);
struct haxorg_ImmAdapterBlockDynamicFallbackAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterBlockDynamicFallbackAPI)}
struct haxorg_ImmAdapterBlockDynamicFallbackAPI {
  haxorg_ImmAdapterBlockDynamicFallbackAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterBlockDynamicFallbackAPI(haxorg_ImmAdapterBlockDynamicFallbackAPI* obj);
struct haxorg_ImmAdapterBlockAdmonitionAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterBlockAdmonitionAPI)}
struct haxorg_ImmAdapterBlockAdmonitionAPI {
  haxorg_ImmAdapterBlockAdmonitionAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterBlockAdmonitionAPI(haxorg_ImmAdapterBlockAdmonitionAPI* obj);
struct haxorg_ImmAdapterBlockCodeEvalResultAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterBlockCodeEvalResultAPI)}
struct haxorg_ImmAdapterBlockCodeEvalResultAPI {
  haxorg_ImmAdapterBlockCodeEvalResultAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterBlockCodeEvalResultAPI(haxorg_ImmAdapterBlockCodeEvalResultAPI* obj);
struct haxorg_ImmAdapterBlockCodeAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterBlockCodeAPI)}
struct haxorg_ImmAdapterBlockCodeAPI {
  haxorg_ImmAdapterBlockCodeAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterBlockCodeAPI(haxorg_ImmAdapterBlockCodeAPI* obj);
struct haxorg_ImmAdapterTableAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterTableAPI)}
struct haxorg_ImmAdapterTableAPI {
  haxorg_ImmAdapterTableAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterTableAPI(haxorg_ImmAdapterTableAPI* obj);
struct haxorg_ImmBlockAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmBlock)}>)}
struct haxorg_ImmBlockAdapter {
  haxorg_ImmBlockAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmBlockAdapter(haxorg_ImmBlockAdapter* obj);
struct haxorg_ImmCellAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmCell)}>)}
struct haxorg_ImmCellAdapter {
  haxorg_ImmCellAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCellAdapter(haxorg_ImmCellAdapter* obj);
struct haxorg_ImmRowAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmRow)}>)}
struct haxorg_ImmRowAdapter {
  haxorg_ImmRowAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmRowAdapter(haxorg_ImmRowAdapter* obj);
struct haxorg_ImmAdapterCmdCaptionAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterCmdCaptionAPI)}
struct haxorg_ImmAdapterCmdCaptionAPI {
  haxorg_ImmAdapterCmdCaptionAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterCmdCaptionAPI(haxorg_ImmAdapterCmdCaptionAPI* obj);
struct haxorg_ImmAdapterCmdColumnsAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterCmdColumnsAPI)}
struct haxorg_ImmAdapterCmdColumnsAPI {
  haxorg_ImmAdapterCmdColumnsAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterCmdColumnsAPI(haxorg_ImmAdapterCmdColumnsAPI* obj);
struct haxorg_ImmAdapterCmdNameAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterCmdNameAPI)}
struct haxorg_ImmAdapterCmdNameAPI {
  haxorg_ImmAdapterCmdNameAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterCmdNameAPI(haxorg_ImmAdapterCmdNameAPI* obj);
struct haxorg_ImmAdapterCmdCallAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterCmdCallAPI)}
struct haxorg_ImmAdapterCmdCallAPI {
  haxorg_ImmAdapterCmdCallAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterCmdCallAPI(haxorg_ImmAdapterCmdCallAPI* obj);
struct haxorg_ImmAdapterCmdResultsAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterCmdResultsAPI)}
struct haxorg_ImmAdapterCmdResultsAPI {
  haxorg_ImmAdapterCmdResultsAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterCmdResultsAPI(haxorg_ImmAdapterCmdResultsAPI* obj);
struct haxorg_ImmAdapterCmdAttrAPI_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterCmdAttrAPI)}
struct haxorg_ImmAdapterCmdAttrAPI {
  haxorg_ImmAdapterCmdAttrAPI_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAdapterCmdAttrAPI(haxorg_ImmAdapterCmdAttrAPI* obj);
struct haxorg_ImmAttachedAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmAttached)}>)}
struct haxorg_ImmAttachedAdapter {
  haxorg_ImmAttachedAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmAttachedAdapter(haxorg_ImmAttachedAdapter* obj);
struct haxorg_ImmBlockCenterAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmBlockCenter)}>)}
struct haxorg_ImmBlockCenterAdapter {
  haxorg_ImmBlockCenterAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmBlockCenterAdapter(haxorg_ImmBlockCenterAdapter* obj);
struct haxorg_ImmBlockQuoteAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmBlockQuote)}>)}
struct haxorg_ImmBlockQuoteAdapter {
  haxorg_ImmBlockQuoteAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmBlockQuoteAdapter(haxorg_ImmBlockQuoteAdapter* obj);
struct haxorg_ImmBlockVerseAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmBlockVerse)}>)}
struct haxorg_ImmBlockVerseAdapter {
  haxorg_ImmBlockVerseAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmBlockVerseAdapter(haxorg_ImmBlockVerseAdapter* obj);
struct haxorg_ImmBlockExampleAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmBlockExample)}>)}
struct haxorg_ImmBlockExampleAdapter {
  haxorg_ImmBlockExampleAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmBlockExampleAdapter(haxorg_ImmBlockExampleAdapter* obj);
struct haxorg_ImmInlineExportAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmInlineExport)}>)}
struct haxorg_ImmInlineExportAdapter {
  haxorg_ImmInlineExportAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmInlineExportAdapter(haxorg_ImmInlineExportAdapter* obj);
struct haxorg_ImmCmdExportAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmCmdExport)}>)}
struct haxorg_ImmCmdExportAdapter {
  haxorg_ImmCmdExportAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmdExportAdapter(haxorg_ImmCmdExportAdapter* obj);
struct haxorg_ImmBlockExportAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmBlockExport)}>)}
struct haxorg_ImmBlockExportAdapter {
  haxorg_ImmBlockExportAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmBlockExportAdapter(haxorg_ImmBlockExportAdapter* obj);
struct haxorg_ImmBlockDynamicFallbackAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmBlockDynamicFallback)}>)}
struct haxorg_ImmBlockDynamicFallbackAdapter {
  haxorg_ImmBlockDynamicFallbackAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmBlockDynamicFallbackAdapter(haxorg_ImmBlockDynamicFallbackAdapter* obj);
struct haxorg_ImmBlockAdmonitionAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmBlockAdmonition)}>)}
struct haxorg_ImmBlockAdmonitionAdapter {
  haxorg_ImmBlockAdmonitionAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmBlockAdmonitionAdapter(haxorg_ImmBlockAdmonitionAdapter* obj);
struct haxorg_ImmBlockCodeEvalResultAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmBlockCodeEvalResult)}>)}
struct haxorg_ImmBlockCodeEvalResultAdapter {
  haxorg_ImmBlockCodeEvalResultAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmBlockCodeEvalResultAdapter(haxorg_ImmBlockCodeEvalResultAdapter* obj);
struct haxorg_ImmBlockCodeAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmBlockCode)}>)}
struct haxorg_ImmBlockCodeAdapter {
  haxorg_ImmBlockCodeAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmBlockCodeAdapter(haxorg_ImmBlockCodeAdapter* obj);
struct haxorg_ImmTableAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmTable)}>)}
struct haxorg_ImmTableAdapter {
  haxorg_ImmTableAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmTableAdapter(haxorg_ImmTableAdapter* obj);
struct haxorg_ImmCmdCaptionAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmCmdCaption)}>)}
struct haxorg_ImmCmdCaptionAdapter {
  haxorg_ImmCmdCaptionAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmdCaptionAdapter(haxorg_ImmCmdCaptionAdapter* obj);
struct haxorg_ImmCmdColumnsAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmCmdColumns)}>)}
struct haxorg_ImmCmdColumnsAdapter {
  haxorg_ImmCmdColumnsAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmdColumnsAdapter(haxorg_ImmCmdColumnsAdapter* obj);
struct haxorg_ImmCmdNameAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmCmdName)}>)}
struct haxorg_ImmCmdNameAdapter {
  haxorg_ImmCmdNameAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmdNameAdapter(haxorg_ImmCmdNameAdapter* obj);
struct haxorg_ImmCmdCallAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmCmdCall)}>)}
struct haxorg_ImmCmdCallAdapter {
  haxorg_ImmCmdCallAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

void haxorg_destroy_ImmCmdCallAdapter(haxorg_ImmCmdCallAdapter* obj);
struct haxorg_ImmCmdAttrAdapter_vtable {};

/// \brief {{REC:(org)}::{REC:(imm)}::REC:(ImmAdapterT<{{REC:(org)}::{REC:(imm)}::REC:(ImmCmdAttr)}>)}
struct haxorg_ImmCmdAttrAdapter {
  haxorg_ImmCmdAttrAdapter_vtable const* vtable;
  haxorg_shared_ptr_payload data;
};

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
HAXORG_C_API_LINKAGE haxorg_AstTrackingMap getAstTrackingMap(haxorg_CHstdVec nodes, OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_CHstdVec getSubnodeGroups(haxorg_SemId node, haxorg_AstTrackingMap map, OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_CHstdVec annotateSequence(haxorg_CHstdVec groups, int first, int last, OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_GraphMapGraphState initMapGraphState(haxorg_ImmAstContext ast, OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_StdString serializeToText(haxorg_ImmAstContext store, OrgContext* org_context);
HAXORG_C_API_LINKAGE void serializeFromText(haxorg_StdString binary, haxorg_ImmAstContext store, OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_StdString serializeToText(haxorg_ImmAstReplaceEpoch store, OrgContext* org_context);
HAXORG_C_API_LINKAGE void serializeFromText(haxorg_StdString binary, haxorg_ImmAstReplaceEpoch store, OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_StdString serializeToText(haxorg_GraphMapGraph store, OrgContext* org_context);
HAXORG_C_API_LINKAGE void serializeFromText(haxorg_StdString binary, haxorg_GraphMapGraph store, OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_StdString serializeFromTextToTreeDump(haxorg_StdString binary, OrgContext* org_context);
/* clang-format on */
