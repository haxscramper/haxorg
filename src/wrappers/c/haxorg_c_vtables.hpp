/* clang-format off */
#include <wrappers/c/haxorg_c.h>
#include <wrappers/c/haxorg_c_utils.hpp>
#include <wrappers/c/haxorg_c_vtables_manual.hpp>
template <>
struct org::bind::c::VTable<haxorg_UserTimeBreakdown, haxorg_UserTimeBreakdown_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_UserTime, haxorg_UserTime_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_UserTimeBreakdown getBreakdown_const(haxorg_UserTime self, OrgContext* org_context);
  static haxorg_StdString format_const(haxorg_UserTime self, OrgContext* org_context);
  static int64_t getTimeDeltaSeconds_const(haxorg_UserTime self, OrgContext* org_context, haxorg_UserTime other);
  static int64_t toUnixTimestamp_const(haxorg_UserTime self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ParseSourceFileId, haxorg_ParseSourceFileId_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ParseSourceManager, haxorg_ParseSourceManager_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_StdString getPath_const(haxorg_ParseSourceManager self, OrgContext* org_context, haxorg_ParseSourceFileId id);
  static haxorg_ParseSourceFileId getId_const(haxorg_ParseSourceManager self, OrgContext* org_context, haxorg_StdString path);
  static haxorg_StdString getSourceContent_const(haxorg_ParseSourceManager self, OrgContext* org_context, haxorg_ParseSourceFileId id);
  static haxorg_StdString getContentTextForPath_const(haxorg_ParseSourceManager self, OrgContext* org_context, haxorg_StdString path);
  static haxorg_ParseSourceFileId addSource(haxorg_ParseSourceManager self, OrgContext* org_context, haxorg_StdString path, haxorg_StdString content);
};

template <>
struct org::bind::c::VTable<haxorg_ParseSourceLoc, haxorg_ParseSourceLoc_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_OrgJsonKind getKind_const(haxorg_OrgJson self, OrgContext* org_context);
  static haxorg_StdString getJsonString_const(haxorg_OrgJson self, OrgContext* org_context);
  static haxorg_OrgJson atIndex_const(haxorg_OrgJson self, OrgContext* org_context, int idx);
  static haxorg_OrgJson atField_const(haxorg_OrgJson self, OrgContext* org_context, haxorg_StdString name);
  static haxorg_StdString getString_const(haxorg_OrgJson self, OrgContext* org_context);
  static haxorg_OrgJson getField_const(haxorg_OrgJson self, OrgContext* org_context, haxorg_StdString name);
  static haxorg_OrgJson getItem_const(haxorg_OrgJson self, OrgContext* org_context, int index);
  static int getInt_const(haxorg_OrgJson self, OrgContext* org_context);
  static bool getBool_const(haxorg_OrgJson self, OrgContext* org_context);
  static haxorg_HstdVec getArray_const(haxorg_OrgJson self, OrgContext* org_context);
  static haxorg_StdString dump_const(haxorg_OrgJson self, OrgContext* org_context, int indent);
};

template <>
struct org::bind::c::VTable<haxorg_Org, haxorg_Org_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_OrgSemKind getKind_const(haxorg_Org self, OrgContext* org_context);
  static void push_back(haxorg_Org self, OrgContext* org_context, haxorg_SemId sub);
  static int size_const(haxorg_Org self, OrgContext* org_context);
  static void insert(haxorg_Org self, OrgContext* org_context, int pos, haxorg_SemId node);
  static haxorg_SemId at_const(haxorg_Org self, OrgContext* org_context, int idx);
  static bool is_const(haxorg_Org self, OrgContext* org_context, haxorg_OrgSemKind kind);
};

template <>
struct org::bind::c::VTable<haxorg_OperationsTracer, haxorg_OperationsTracer_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static void setTraceFileStr(haxorg_OperationsTracer self, OrgContext* org_context, haxorg_StdString outfile, bool overwrite);
  static void sendMessage(haxorg_OperationsTracer self, OrgContext* org_context, haxorg_StdString value, haxorg_StdString function, int line, haxorg_StdString file);
};

template <>
struct org::bind::c::VTable<haxorg_Cache, haxorg_Cache_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ParseOrgParseFragment, haxorg_ParseOrgParseFragment_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_OrgParseParameters, haxorg_OrgParseParameters_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_OrgDirectoryParseParameters, haxorg_OrgDirectoryParseParameters_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Cache getDiagnosticStrings(haxorg_ParseContext self, OrgContext* org_context);
  static haxorg_ParseSourceFileId addSource_const(haxorg_ParseContext self, OrgContext* org_context, haxorg_StdString path, haxorg_StdString content);
  static haxorg_SemId parseFileOpts(haxorg_ParseContext self, OrgContext* org_context, haxorg_StdString file, haxorg_OrgParseParameters opts);
  static haxorg_SemId parseFile(haxorg_ParseContext self, OrgContext* org_context, haxorg_StdString file);
  static haxorg_SemId parseString(haxorg_ParseContext self, OrgContext* org_context, haxorg_StdString text, haxorg_StdString file_name);
  static haxorg_SemId parseStringOpts(haxorg_ParseContext self, OrgContext* org_context, haxorg_StdString text, haxorg_StdString file_name, haxorg_OrgParseParameters opts);
  static haxorg_StdOptional parseDirectory(haxorg_ParseContext self, OrgContext* org_context, haxorg_StdString path);
  static haxorg_StdOptional parseDirectoryOpts(haxorg_ParseContext self, OrgContext* org_context, haxorg_StdString path, haxorg_OrgDirectoryParseParameters opts);
  static haxorg_SemId parseFileWithIncludes(haxorg_ParseContext self, OrgContext* org_context, haxorg_StdString file, haxorg_OrgDirectoryParseParameters opts);
  static haxorg_HstdVec collectDiagnostics(haxorg_ParseContext self, OrgContext* org_context, haxorg_SemId tree, haxorg_Cache cache);
  static haxorg_HstdVec collectErrorNodes(haxorg_ParseContext self, OrgContext* org_context, haxorg_SemId tree);
};

template <>
struct org::bind::c::VTable<haxorg_ImmReflFieldId, haxorg_ImmReflFieldId_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getName_const(haxorg_ImmReflFieldId self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmId, haxorg_ImmId_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_OrgSemKind getKind_const(haxorg_ImmId self, OrgContext* org_context);
  static bool is_const(haxorg_ImmId self, OrgContext* org_context, haxorg_OrgSemKind kind);
  static haxorg_ImmIdNodeIdxT getNodeIndex_const(haxorg_ImmId self, OrgContext* org_context);
  static haxorg_StdString getReadableId_const(haxorg_ImmId self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmOrg, haxorg_ImmOrg_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmPathStep, haxorg_ImmPathStep_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmPath, haxorg_ImmPath_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool empty_const(haxorg_ImmPath self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmUniqId, haxorg_ImmUniqId_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAstReplaceEpoch, haxorg_ImmAstReplaceEpoch_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAstContext, haxorg_ImmAstContext_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAstVersion addRoot(haxorg_ImmAstContext self, OrgContext* org_context, haxorg_SemId data);
  static haxorg_ImmAstVersion getEmptyVersion(haxorg_ImmAstContext self, OrgContext* org_context);
  static haxorg_SemId get(haxorg_ImmAstContext self, OrgContext* org_context, haxorg_ImmId id);
};

template <>
struct org::bind::c::VTable<haxorg_ImmAstVersion, haxorg_ImmAstVersion_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmId getRoot_const(haxorg_ImmAstVersion self, OrgContext* org_context);
  static haxorg_ImmAdapter getRootAdapter_const(haxorg_ImmAstVersion self, OrgContext* org_context);
  static haxorg_ImmAstContext getContext_const(haxorg_ImmAstVersion self, OrgContext* org_context);
  static haxorg_ImmAstReplaceEpoch getEpoch_const(haxorg_ImmAstVersion self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(haxorg_ImmAdapter self, OrgContext* org_context);
  static bool isNil_const(haxorg_ImmAdapter self, OrgContext* org_context);
  static bool isRoot_const(haxorg_ImmAdapter self, OrgContext* org_context);
  static haxorg_OrgSemKind getKind_const(haxorg_ImmAdapter self, OrgContext* org_context);
  static haxorg_ImmUniqId uniq_const(haxorg_ImmAdapter self, OrgContext* org_context);
  static haxorg_StdString treeReprString_const(haxorg_ImmAdapter self, OrgContext* org_context);
  static haxorg_StdString treeReprStringOpts_const(haxorg_ImmAdapter self, OrgContext* org_context, haxorg_ImmAdapterTreeReprConf conf);
  static bool isDirectParentOf_const(haxorg_ImmAdapter self, OrgContext* org_context, haxorg_ImmAdapter other);
  static bool isIndirectParentOf_const(haxorg_ImmAdapter self, OrgContext* org_context, haxorg_ImmAdapter other);
  static bool isSubnodeOf_const(haxorg_ImmAdapter self, OrgContext* org_context, haxorg_ImmAdapter other);
  static haxorg_StdOptional getParent_const(haxorg_ImmAdapter self, OrgContext* org_context);
  static int getSelfIndex_const(haxorg_ImmAdapter self, OrgContext* org_context);
  static haxorg_ImmAdapter atPathStep_const(haxorg_ImmAdapter self, OrgContext* org_context, haxorg_ImmId id, haxorg_ImmPathStep idx);
  static haxorg_ImmAdapter atField_const(haxorg_ImmAdapter self, OrgContext* org_context, haxorg_ImmReflFieldId field);
  static haxorg_ImmAdapter atIndex_const(haxorg_ImmAdapter self, OrgContext* org_context, int idx, bool withPath);
  static haxorg_ImmAdapter atPath_const(haxorg_ImmAdapter self, OrgContext* org_context, haxorg_HstdVec path, bool withPath);
  static bool is_const(haxorg_ImmAdapter self, OrgContext* org_context, haxorg_OrgSemKind kind);
  static haxorg_HstdVec sub_const(haxorg_ImmAdapter self, OrgContext* org_context, bool withPath);
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterTreeReprConf, haxorg_ImmAdapterTreeReprConf_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterVirtualBase, haxorg_ImmAdapterVirtualBase_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_OrgYamlExportOpts, haxorg_OrgYamlExportOpts_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_OrgTreeExportOpts, haxorg_OrgTreeExportOpts_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_AstTrackingPath, haxorg_AstTrackingPath_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_SemId getParent_const(haxorg_AstTrackingPath self, OrgContext* org_context, int offset);
  static haxorg_SemId getNode_const(haxorg_AstTrackingPath self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_AstTrackingAlternatives, haxorg_AstTrackingAlternatives_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdVec getAllNodes_const(haxorg_AstTrackingAlternatives self, OrgContext* org_context);
  static haxorg_SemId getNode_const(haxorg_AstTrackingAlternatives self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_AstTrackingGroupRadioTarget getRadioTargetConst_const(haxorg_AstTrackingGroup self, OrgContext* org_context);
  static haxorg_AstTrackingGroupTrackedHashtag getTrackedHashtagConst_const(haxorg_AstTrackingGroup self, OrgContext* org_context);
  static haxorg_AstTrackingGroupTrackedHashtag getTrackedHashtagMut(haxorg_AstTrackingGroup self, OrgContext* org_context);
  static haxorg_AstTrackingGroupSingle getSingleConst_const(haxorg_AstTrackingGroup self, OrgContext* org_context);
  static haxorg_AstTrackingGroupRadioTarget getRadioTargetMut(haxorg_AstTrackingGroup self, OrgContext* org_context);
  static haxorg_AstTrackingGroupSingle getSingleMut(haxorg_AstTrackingGroup self, OrgContext* org_context);
  static bool isSingle_const(haxorg_AstTrackingGroup self, OrgContext* org_context);
  static bool isTrackedHashtag_const(haxorg_AstTrackingGroup self, OrgContext* org_context);
  static bool isRadioTarget_const(haxorg_AstTrackingGroup self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_AstTrackingGroupRadioTarget, haxorg_AstTrackingGroupRadioTarget_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_AstTrackingGroupSingle, haxorg_AstTrackingGroupSingle_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_AstTrackingGroupTrackedHashtag, haxorg_AstTrackingGroupTrackedHashtag_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_AstTrackingMap, haxorg_AstTrackingMap_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_StdOptional getIdPath_const(haxorg_AstTrackingMap self, OrgContext* org_context, haxorg_HstdStr id);
  static haxorg_StdOptional getNamePath_const(haxorg_AstTrackingMap self, OrgContext* org_context, haxorg_HstdStr id);
  static haxorg_StdOptional getAnchorTarget_const(haxorg_AstTrackingMap self, OrgContext* org_context, haxorg_HstdStr id);
  static haxorg_StdOptional getFootnotePath_const(haxorg_AstTrackingMap self, OrgContext* org_context, haxorg_HstdStr id);
};

template <>
struct org::bind::c::VTable<haxorg_SequenceSegment, haxorg_SequenceSegment_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_SequenceSegmentGroup, haxorg_SequenceSegmentGroup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_SequenceAnnotationTag, haxorg_SequenceAnnotationTag_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_SequenceAnnotation, haxorg_SequenceAnnotation_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool isAnnotatedWith_const(haxorg_SequenceAnnotation self, OrgContext* org_context, int groupKind, int segmentKind);
};

template <>
struct org::bind::c::VTable<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_GraphMapLinkRadio getRadio(haxorg_GraphMapLink self, OrgContext* org_context);
  static haxorg_GraphMapLinkRadio getRadio_const(haxorg_GraphMapLink self, OrgContext* org_context);
  static bool isRadio_const(haxorg_GraphMapLink self, OrgContext* org_context);
  static haxorg_GraphMapLinkLink getLink(haxorg_GraphMapLink self, OrgContext* org_context);
  static haxorg_GraphMapLinkLink getLink_const(haxorg_GraphMapLink self, OrgContext* org_context);
  static bool isLink_const(haxorg_GraphMapLink self, OrgContext* org_context);
  static haxorg_GraphMapLinkKind getKind_const(haxorg_GraphMapLink self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_GraphMapLinkLink, haxorg_GraphMapLinkLink_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_GraphMapLinkRadio, haxorg_GraphMapLinkRadio_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_GraphMapNodeProp, haxorg_GraphMapNodeProp_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapter getAdapter_const(haxorg_GraphMapNodeProp self, OrgContext* org_context, haxorg_ImmAstContext context);
  static haxorg_StdOptional getSubtreeId_const(haxorg_GraphMapNodeProp self, OrgContext* org_context, haxorg_ImmAstContext context);
  static haxorg_StdOptional getFootnoteName_const(haxorg_GraphMapNodeProp self, OrgContext* org_context, haxorg_ImmAstContext context);
};

template <>
struct org::bind::c::VTable<haxorg_GraphMapEdgeProp, haxorg_GraphMapEdgeProp_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_GraphMapNode, haxorg_GraphMapNode_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_GraphMapNode self, OrgContext* org_context, haxorg_GraphMapNode other);
  static bool __lt___const(haxorg_GraphMapNode self, OrgContext* org_context, haxorg_GraphMapNode other);
};

template <>
struct org::bind::c::VTable<haxorg_GraphMapEdge, haxorg_GraphMapEdge_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int nodeCount_const(haxorg_GraphMapGraph self, OrgContext* org_context);
  static int edgeCount_const(haxorg_GraphMapGraph self, OrgContext* org_context);
  static haxorg_GraphAdjNodesList outNodes_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node);
  static haxorg_GraphAdjNodesList inNodes_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node);
  static haxorg_HstdVec adjEdges_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node);
  static haxorg_HstdVec adjNodes_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node);
  static haxorg_HstdVec outEdges_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node);
  static haxorg_HstdVec inEdges_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node);
  static int outDegree_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node);
  static int inDegree_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node);
  static bool isRegisteredNode_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode id);
  static bool isRegisteredNodeById_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_ImmUniqId id);
  static haxorg_GraphMapNodeProp atMapNode_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node);
  static haxorg_GraphMapEdgeProp atMapEdge_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapEdge edge);
  static void addEdge(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapEdge edge);
  static void addEdgeWithProp(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapEdge edge, haxorg_GraphMapEdgeProp prop);
  static void addNode(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node);
  static void addNodeWithProp(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node, haxorg_GraphMapNodeProp prop);
  static bool hasEdge_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode source, haxorg_GraphMapNode target);
  static bool hasNode_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node);
  static bool has2AdapterEdge_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_ImmAdapter source, haxorg_ImmAdapter target);
};

template <>
struct org::bind::c::VTable<haxorg_GraphMapConfig, haxorg_GraphMapConfig_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_GraphMapGraph getGraph_const(haxorg_GraphMapGraphState self, OrgContext* org_context);
  static haxorg_GraphMapGraphState FromAstContext(haxorg_GraphMapGraphState self, OrgContext* org_context, haxorg_ImmAstContext ast);
  static void registerNode(haxorg_GraphMapGraphState self, OrgContext* org_context, haxorg_GraphMapNodeProp node, haxorg_GraphMapConfig conf);
  static void addNode(haxorg_GraphMapGraphState self, OrgContext* org_context, haxorg_ImmAdapter node, haxorg_GraphMapConfig conf);
  static void addNodeRec(haxorg_GraphMapGraphState self, OrgContext* org_context, haxorg_ImmAstContext ast, haxorg_ImmAdapter node, haxorg_GraphMapConfig conf);
  static haxorg_HstdVec getUnresolvedSubtreeLinks_const(haxorg_GraphMapGraphState self, OrgContext* org_context, haxorg_ImmSubtreeAdapter node, haxorg_GraphMapConfig conf);
  static haxorg_StdOptional getUnresolvedLink_const(haxorg_GraphMapGraphState self, OrgContext* org_context, haxorg_ImmLinkAdapter node, haxorg_GraphMapConfig conf);
};

template <>
struct org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_LispCode self, OrgContext* org_context, haxorg_LispCode other);
  static bool isCall_const(haxorg_LispCode self, OrgContext* org_context);
  static haxorg_LispCodeCall getCallConst_const(haxorg_LispCode self, OrgContext* org_context);
  static haxorg_LispCodeCall getCallMut(haxorg_LispCode self, OrgContext* org_context);
  static bool isList_const(haxorg_LispCode self, OrgContext* org_context);
  static haxorg_LispCodeList getListConst_const(haxorg_LispCode self, OrgContext* org_context);
  static haxorg_LispCodeList getListMut(haxorg_LispCode self, OrgContext* org_context);
  static bool isKeyValue_const(haxorg_LispCode self, OrgContext* org_context);
  static haxorg_LispCodeKeyValue getKeyValueConst_const(haxorg_LispCode self, OrgContext* org_context);
  static haxorg_LispCodeKeyValue getKeyValueMut(haxorg_LispCode self, OrgContext* org_context);
  static bool isNumber_const(haxorg_LispCode self, OrgContext* org_context);
  static haxorg_LispCodeNumber getNumberConst_const(haxorg_LispCode self, OrgContext* org_context);
  static haxorg_LispCodeNumber getNumberMut(haxorg_LispCode self, OrgContext* org_context);
  static bool isText_const(haxorg_LispCode self, OrgContext* org_context);
  static haxorg_LispCodeText getTextConst_const(haxorg_LispCode self, OrgContext* org_context);
  static haxorg_LispCodeText getTextMut(haxorg_LispCode self, OrgContext* org_context);
  static bool isIdent_const(haxorg_LispCode self, OrgContext* org_context);
  static haxorg_LispCodeIdent getIdentConst_const(haxorg_LispCode self, OrgContext* org_context);
  static haxorg_LispCodeIdent getIdentMut(haxorg_LispCode self, OrgContext* org_context);
  static bool isBoolean_const(haxorg_LispCode self, OrgContext* org_context);
  static haxorg_LispCodeBoolean getBooleanConst_const(haxorg_LispCode self, OrgContext* org_context);
  static haxorg_LispCodeBoolean getBooleanMut(haxorg_LispCode self, OrgContext* org_context);
  static bool isReal_const(haxorg_LispCode self, OrgContext* org_context);
  static haxorg_LispCodeReal getRealConst_const(haxorg_LispCode self, OrgContext* org_context);
  static haxorg_LispCodeReal getRealMut(haxorg_LispCode self, OrgContext* org_context);
  static haxorg_LispCodeKind getKind_const(haxorg_LispCode self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_LispCodeCall, haxorg_LispCodeCall_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_LispCodeCall self, OrgContext* org_context, haxorg_LispCodeCall other);
};

template <>
struct org::bind::c::VTable<haxorg_LispCodeList, haxorg_LispCodeList_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_LispCodeList self, OrgContext* org_context, haxorg_LispCodeList other);
};

template <>
struct org::bind::c::VTable<haxorg_LispCodeKeyValue, haxorg_LispCodeKeyValue_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_LispCodeKeyValue self, OrgContext* org_context, haxorg_LispCodeKeyValue other);
};

template <>
struct org::bind::c::VTable<haxorg_LispCodeNumber, haxorg_LispCodeNumber_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_LispCodeNumber self, OrgContext* org_context, haxorg_LispCodeNumber other);
};

template <>
struct org::bind::c::VTable<haxorg_LispCodeText, haxorg_LispCodeText_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_LispCodeText self, OrgContext* org_context, haxorg_LispCodeText other);
};

template <>
struct org::bind::c::VTable<haxorg_LispCodeIdent, haxorg_LispCodeIdent_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_LispCodeIdent self, OrgContext* org_context, haxorg_LispCodeIdent other);
};

template <>
struct org::bind::c::VTable<haxorg_LispCodeBoolean, haxorg_LispCodeBoolean_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_LispCodeBoolean self, OrgContext* org_context, haxorg_LispCodeBoolean other);
};

template <>
struct org::bind::c::VTable<haxorg_LispCodeReal, haxorg_LispCodeReal_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_LispCodeReal self, OrgContext* org_context, haxorg_LispCodeReal other);
};

template <>
struct org::bind::c::VTable<haxorg_Tblfm, haxorg_Tblfm_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_Tblfm self, OrgContext* org_context, haxorg_Tblfm other);
};

template <>
struct org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_TblfmExpr self, OrgContext* org_context, haxorg_TblfmExpr other);
  static bool isAxisRef_const(haxorg_TblfmExpr self, OrgContext* org_context);
  static haxorg_TblfmExprAxisRef getAxisRefConst_const(haxorg_TblfmExpr self, OrgContext* org_context);
  static haxorg_TblfmExprAxisRef getAxisRefMut(haxorg_TblfmExpr self, OrgContext* org_context);
  static bool isAxisName_const(haxorg_TblfmExpr self, OrgContext* org_context);
  static haxorg_TblfmExprAxisName getAxisNameConst_const(haxorg_TblfmExpr self, OrgContext* org_context);
  static haxorg_TblfmExprAxisName getAxisNameMut(haxorg_TblfmExpr self, OrgContext* org_context);
  static bool isIntLiteral_const(haxorg_TblfmExpr self, OrgContext* org_context);
  static haxorg_TblfmExprIntLiteral getIntLiteralConst_const(haxorg_TblfmExpr self, OrgContext* org_context);
  static haxorg_TblfmExprIntLiteral getIntLiteralMut(haxorg_TblfmExpr self, OrgContext* org_context);
  static bool isFloatLiteral_const(haxorg_TblfmExpr self, OrgContext* org_context);
  static haxorg_TblfmExprFloatLiteral getFloatLiteralConst_const(haxorg_TblfmExpr self, OrgContext* org_context);
  static haxorg_TblfmExprFloatLiteral getFloatLiteralMut(haxorg_TblfmExpr self, OrgContext* org_context);
  static bool isRangeRef_const(haxorg_TblfmExpr self, OrgContext* org_context);
  static haxorg_TblfmExprRangeRef getRangeRefConst_const(haxorg_TblfmExpr self, OrgContext* org_context);
  static haxorg_TblfmExprRangeRef getRangeRefMut(haxorg_TblfmExpr self, OrgContext* org_context);
  static bool isCall_const(haxorg_TblfmExpr self, OrgContext* org_context);
  static haxorg_TblfmExprCall getCallConst_const(haxorg_TblfmExpr self, OrgContext* org_context);
  static haxorg_TblfmExprCall getCallMut(haxorg_TblfmExpr self, OrgContext* org_context);
  static bool isElisp_const(haxorg_TblfmExpr self, OrgContext* org_context);
  static haxorg_TblfmExprElisp getElispConst_const(haxorg_TblfmExpr self, OrgContext* org_context);
  static haxorg_TblfmExprElisp getElispMut(haxorg_TblfmExpr self, OrgContext* org_context);
  static haxorg_TblfmExprKind getKind_const(haxorg_TblfmExpr self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_TblfmExprAxisRef, haxorg_TblfmExprAxisRef_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_TblfmExprAxisRef self, OrgContext* org_context, haxorg_TblfmExprAxisRef other);
};

template <>
struct org::bind::c::VTable<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_TblfmExprAxisRefPosition self, OrgContext* org_context, haxorg_TblfmExprAxisRefPosition other);
  static bool isIndex_const(haxorg_TblfmExprAxisRefPosition self, OrgContext* org_context);
  static haxorg_TblfmExprAxisRefPositionIndex getIndexConst_const(haxorg_TblfmExprAxisRefPosition self, OrgContext* org_context);
  static haxorg_TblfmExprAxisRefPositionIndex getIndexMut(haxorg_TblfmExprAxisRefPosition self, OrgContext* org_context);
  static bool isName_const(haxorg_TblfmExprAxisRefPosition self, OrgContext* org_context);
  static haxorg_TblfmExprAxisRefPositionName getNameConst_const(haxorg_TblfmExprAxisRefPosition self, OrgContext* org_context);
  static haxorg_TblfmExprAxisRefPositionName getNameMut(haxorg_TblfmExprAxisRefPosition self, OrgContext* org_context);
  static haxorg_TblfmExprAxisRefPositionKind getKind_const(haxorg_TblfmExprAxisRefPosition self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_TblfmExprAxisRefPositionIndex, haxorg_TblfmExprAxisRefPositionIndex_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_TblfmExprAxisRefPositionIndex self, OrgContext* org_context, haxorg_TblfmExprAxisRefPositionIndex other);
};

template <>
struct org::bind::c::VTable<haxorg_TblfmExprAxisRefPositionName, haxorg_TblfmExprAxisRefPositionName_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_TblfmExprAxisRefPositionName self, OrgContext* org_context, haxorg_TblfmExprAxisRefPositionName other);
};

template <>
struct org::bind::c::VTable<haxorg_TblfmExprAxisName, haxorg_TblfmExprAxisName_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_TblfmExprAxisName self, OrgContext* org_context, haxorg_TblfmExprAxisName other);
};

template <>
struct org::bind::c::VTable<haxorg_TblfmExprIntLiteral, haxorg_TblfmExprIntLiteral_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_TblfmExprIntLiteral self, OrgContext* org_context, haxorg_TblfmExprIntLiteral other);
};

template <>
struct org::bind::c::VTable<haxorg_TblfmExprFloatLiteral, haxorg_TblfmExprFloatLiteral_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_TblfmExprFloatLiteral self, OrgContext* org_context, haxorg_TblfmExprFloatLiteral other);
};

template <>
struct org::bind::c::VTable<haxorg_TblfmExprRangeRef, haxorg_TblfmExprRangeRef_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_TblfmExprRangeRef self, OrgContext* org_context, haxorg_TblfmExprRangeRef other);
};

template <>
struct org::bind::c::VTable<haxorg_TblfmExprCall, haxorg_TblfmExprCall_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_TblfmExprCall self, OrgContext* org_context, haxorg_TblfmExprCall other);
};

template <>
struct org::bind::c::VTable<haxorg_TblfmExprElisp, haxorg_TblfmExprElisp_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_TblfmExprElisp self, OrgContext* org_context, haxorg_TblfmExprElisp other);
};

template <>
struct org::bind::c::VTable<haxorg_TblfmAssign, haxorg_TblfmAssign_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_TblfmAssign self, OrgContext* org_context, haxorg_TblfmAssign other);
};

template <>
struct org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdOpt getBool_const(haxorg_AttrValue self, OrgContext* org_context);
  static haxorg_HstdOpt getInt_const(haxorg_AttrValue self, OrgContext* org_context);
  static haxorg_HstdStr getString_const(haxorg_AttrValue self, OrgContext* org_context);
  static haxorg_HstdOpt getDouble_const(haxorg_AttrValue self, OrgContext* org_context);
  static bool __eq___const(haxorg_AttrValue self, OrgContext* org_context, haxorg_AttrValue other);
  static bool isTextValue_const(haxorg_AttrValue self, OrgContext* org_context);
  static haxorg_AttrValueTextValue getTextValueConst_const(haxorg_AttrValue self, OrgContext* org_context);
  static haxorg_AttrValueTextValue getTextValueMut(haxorg_AttrValue self, OrgContext* org_context);
  static bool isFileReference_const(haxorg_AttrValue self, OrgContext* org_context);
  static haxorg_AttrValueFileReference getFileReferenceConst_const(haxorg_AttrValue self, OrgContext* org_context);
  static haxorg_AttrValueFileReference getFileReferenceMut(haxorg_AttrValue self, OrgContext* org_context);
  static bool isLispValue_const(haxorg_AttrValue self, OrgContext* org_context);
  static haxorg_AttrValueLispValue getLispValueConst_const(haxorg_AttrValue self, OrgContext* org_context);
  static haxorg_AttrValueLispValue getLispValueMut(haxorg_AttrValue self, OrgContext* org_context);
  static haxorg_AttrValueKind getKind_const(haxorg_AttrValue self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_AttrValueDimensionSpan, haxorg_AttrValueDimensionSpan_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_AttrValueDimensionSpan self, OrgContext* org_context, haxorg_AttrValueDimensionSpan other);
};

template <>
struct org::bind::c::VTable<haxorg_AttrValueTextValue, haxorg_AttrValueTextValue_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_AttrValueTextValue self, OrgContext* org_context, haxorg_AttrValueTextValue other);
};

template <>
struct org::bind::c::VTable<haxorg_AttrValueFileReference, haxorg_AttrValueFileReference_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_AttrValueFileReference self, OrgContext* org_context, haxorg_AttrValueFileReference other);
};

template <>
struct org::bind::c::VTable<haxorg_AttrValueLispValue, haxorg_AttrValueLispValue_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_AttrValueLispValue self, OrgContext* org_context, haxorg_AttrValueLispValue other);
};

template <>
struct org::bind::c::VTable<haxorg_HashTagFlat, haxorg_HashTagFlat_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_HashTagFlat self, OrgContext* org_context, haxorg_HashTagFlat other);
  static bool __lt___const(haxorg_HashTagFlat self, OrgContext* org_context, haxorg_HashTagFlat other);
};

template <>
struct org::bind::c::VTable<haxorg_TodoKeyword, haxorg_TodoKeyword_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_TodoKeyword self, OrgContext* org_context, haxorg_TodoKeyword other);
};

template <>
struct org::bind::c::VTable<haxorg_HashTagText, haxorg_HashTagText_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_HashTagText self, OrgContext* org_context, haxorg_HashTagText other);
  static bool prefixMatch_const(haxorg_HashTagText self, OrgContext* org_context, haxorg_HstdVec prefix);
  static haxorg_HstdVec getFlatHashes_const(haxorg_HashTagText self, OrgContext* org_context, bool withIntermediate);
};

template <>
struct org::bind::c::VTable<haxorg_SubtreePath, haxorg_SubtreePath_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_SubtreePath self, OrgContext* org_context, haxorg_SubtreePath other);
};

template <>
struct org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_LinkTarget self, OrgContext* org_context, haxorg_LinkTarget other);
  static bool isRaw_const(haxorg_LinkTarget self, OrgContext* org_context);
  static haxorg_LinkTargetRaw getRawConst_const(haxorg_LinkTarget self, OrgContext* org_context);
  static haxorg_LinkTargetRaw getRawMut(haxorg_LinkTarget self, OrgContext* org_context);
  static bool isId_const(haxorg_LinkTarget self, OrgContext* org_context);
  static haxorg_LinkTargetId getIdConst_const(haxorg_LinkTarget self, OrgContext* org_context);
  static haxorg_LinkTargetId getIdMut(haxorg_LinkTarget self, OrgContext* org_context);
  static bool isCustomId_const(haxorg_LinkTarget self, OrgContext* org_context);
  static haxorg_LinkTargetCustomId getCustomIdConst_const(haxorg_LinkTarget self, OrgContext* org_context);
  static haxorg_LinkTargetCustomId getCustomIdMut(haxorg_LinkTarget self, OrgContext* org_context);
  static bool isSubtreeTitle_const(haxorg_LinkTarget self, OrgContext* org_context);
  static haxorg_LinkTargetSubtreeTitle getSubtreeTitleConst_const(haxorg_LinkTarget self, OrgContext* org_context);
  static haxorg_LinkTargetSubtreeTitle getSubtreeTitleMut(haxorg_LinkTarget self, OrgContext* org_context);
  static bool isPerson_const(haxorg_LinkTarget self, OrgContext* org_context);
  static haxorg_LinkTargetPerson getPersonConst_const(haxorg_LinkTarget self, OrgContext* org_context);
  static haxorg_LinkTargetPerson getPersonMut(haxorg_LinkTarget self, OrgContext* org_context);
  static bool isUserProtocol_const(haxorg_LinkTarget self, OrgContext* org_context);
  static haxorg_LinkTargetUserProtocol getUserProtocolConst_const(haxorg_LinkTarget self, OrgContext* org_context);
  static haxorg_LinkTargetUserProtocol getUserProtocolMut(haxorg_LinkTarget self, OrgContext* org_context);
  static bool isInternal_const(haxorg_LinkTarget self, OrgContext* org_context);
  static haxorg_LinkTargetInternal getInternalConst_const(haxorg_LinkTarget self, OrgContext* org_context);
  static haxorg_LinkTargetInternal getInternalMut(haxorg_LinkTarget self, OrgContext* org_context);
  static bool isFootnote_const(haxorg_LinkTarget self, OrgContext* org_context);
  static haxorg_LinkTargetFootnote getFootnoteConst_const(haxorg_LinkTarget self, OrgContext* org_context);
  static haxorg_LinkTargetFootnote getFootnoteMut(haxorg_LinkTarget self, OrgContext* org_context);
  static bool isFile_const(haxorg_LinkTarget self, OrgContext* org_context);
  static haxorg_LinkTargetFile getFileConst_const(haxorg_LinkTarget self, OrgContext* org_context);
  static haxorg_LinkTargetFile getFileMut(haxorg_LinkTarget self, OrgContext* org_context);
  static bool isAttachment_const(haxorg_LinkTarget self, OrgContext* org_context);
  static haxorg_LinkTargetAttachment getAttachmentConst_const(haxorg_LinkTarget self, OrgContext* org_context);
  static haxorg_LinkTargetAttachment getAttachmentMut(haxorg_LinkTarget self, OrgContext* org_context);
  static haxorg_LinkTargetKind getKind_const(haxorg_LinkTarget self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_LinkTargetRaw, haxorg_LinkTargetRaw_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_LinkTargetRaw self, OrgContext* org_context, haxorg_LinkTargetRaw other);
};

template <>
struct org::bind::c::VTable<haxorg_LinkTargetId, haxorg_LinkTargetId_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_LinkTargetId self, OrgContext* org_context, haxorg_LinkTargetId other);
};

template <>
struct org::bind::c::VTable<haxorg_LinkTargetCustomId, haxorg_LinkTargetCustomId_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_LinkTargetCustomId self, OrgContext* org_context, haxorg_LinkTargetCustomId other);
};

template <>
struct org::bind::c::VTable<haxorg_LinkTargetSubtreeTitle, haxorg_LinkTargetSubtreeTitle_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_LinkTargetSubtreeTitle self, OrgContext* org_context, haxorg_LinkTargetSubtreeTitle other);
};

template <>
struct org::bind::c::VTable<haxorg_LinkTargetPerson, haxorg_LinkTargetPerson_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_LinkTargetPerson self, OrgContext* org_context, haxorg_LinkTargetPerson other);
};

template <>
struct org::bind::c::VTable<haxorg_LinkTargetUserProtocol, haxorg_LinkTargetUserProtocol_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_LinkTargetUserProtocol self, OrgContext* org_context, haxorg_LinkTargetUserProtocol other);
};

template <>
struct org::bind::c::VTable<haxorg_LinkTargetInternal, haxorg_LinkTargetInternal_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_LinkTargetInternal self, OrgContext* org_context, haxorg_LinkTargetInternal other);
};

template <>
struct org::bind::c::VTable<haxorg_LinkTargetFootnote, haxorg_LinkTargetFootnote_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_LinkTargetFootnote self, OrgContext* org_context, haxorg_LinkTargetFootnote other);
};

template <>
struct org::bind::c::VTable<haxorg_LinkTargetFile, haxorg_LinkTargetFile_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_LinkTargetFile self, OrgContext* org_context, haxorg_LinkTargetFile other);
};

template <>
struct org::bind::c::VTable<haxorg_LinkTargetAttachment, haxorg_LinkTargetAttachment_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_LinkTargetAttachment self, OrgContext* org_context, haxorg_LinkTargetAttachment other);
};

template <>
struct org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_SubtreeLogHead self, OrgContext* org_context, haxorg_SubtreeLogHead other);
  static bool isPriority_const(haxorg_SubtreeLogHead self, OrgContext* org_context);
  static haxorg_SubtreeLogHeadPriority getPriorityConst_const(haxorg_SubtreeLogHead self, OrgContext* org_context);
  static haxorg_SubtreeLogHeadPriority getPriorityMut(haxorg_SubtreeLogHead self, OrgContext* org_context);
  static bool isNote_const(haxorg_SubtreeLogHead self, OrgContext* org_context);
  static haxorg_SubtreeLogHeadNote getNoteConst_const(haxorg_SubtreeLogHead self, OrgContext* org_context);
  static haxorg_SubtreeLogHeadNote getNoteMut(haxorg_SubtreeLogHead self, OrgContext* org_context);
  static bool isRefile_const(haxorg_SubtreeLogHead self, OrgContext* org_context);
  static haxorg_SubtreeLogHeadRefile getRefileConst_const(haxorg_SubtreeLogHead self, OrgContext* org_context);
  static haxorg_SubtreeLogHeadRefile getRefileMut(haxorg_SubtreeLogHead self, OrgContext* org_context);
  static bool isClock_const(haxorg_SubtreeLogHead self, OrgContext* org_context);
  static haxorg_SubtreeLogHeadClock getClockConst_const(haxorg_SubtreeLogHead self, OrgContext* org_context);
  static haxorg_SubtreeLogHeadClock getClockMut(haxorg_SubtreeLogHead self, OrgContext* org_context);
  static bool isState_const(haxorg_SubtreeLogHead self, OrgContext* org_context);
  static haxorg_SubtreeLogHeadState getStateConst_const(haxorg_SubtreeLogHead self, OrgContext* org_context);
  static haxorg_SubtreeLogHeadState getStateMut(haxorg_SubtreeLogHead self, OrgContext* org_context);
  static bool isDeadline_const(haxorg_SubtreeLogHead self, OrgContext* org_context);
  static haxorg_SubtreeLogHeadDeadline getDeadlineConst_const(haxorg_SubtreeLogHead self, OrgContext* org_context);
  static haxorg_SubtreeLogHeadDeadline getDeadlineMut(haxorg_SubtreeLogHead self, OrgContext* org_context);
  static bool isSchedule_const(haxorg_SubtreeLogHead self, OrgContext* org_context);
  static haxorg_SubtreeLogHeadSchedule getScheduleConst_const(haxorg_SubtreeLogHead self, OrgContext* org_context);
  static haxorg_SubtreeLogHeadSchedule getScheduleMut(haxorg_SubtreeLogHead self, OrgContext* org_context);
  static bool isTag_const(haxorg_SubtreeLogHead self, OrgContext* org_context);
  static haxorg_SubtreeLogHeadTag getTagConst_const(haxorg_SubtreeLogHead self, OrgContext* org_context);
  static haxorg_SubtreeLogHeadTag getTagMut(haxorg_SubtreeLogHead self, OrgContext* org_context);
  static bool isUnknown_const(haxorg_SubtreeLogHead self, OrgContext* org_context);
  static haxorg_SubtreeLogHeadUnknown getUnknownConst_const(haxorg_SubtreeLogHead self, OrgContext* org_context);
  static haxorg_SubtreeLogHeadUnknown getUnknownMut(haxorg_SubtreeLogHead self, OrgContext* org_context);
  static haxorg_SubtreeLogHeadKind getLogKind_const(haxorg_SubtreeLogHead self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_SubtreeLogHeadPriority, haxorg_SubtreeLogHeadPriority_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_SubtreeLogHeadPriority self, OrgContext* org_context, haxorg_SubtreeLogHeadPriority other);
};

template <>
struct org::bind::c::VTable<haxorg_SubtreeLogHeadNote, haxorg_SubtreeLogHeadNote_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_SubtreeLogHeadNote self, OrgContext* org_context, haxorg_SubtreeLogHeadNote other);
};

template <>
struct org::bind::c::VTable<haxorg_SubtreeLogHeadRefile, haxorg_SubtreeLogHeadRefile_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_SubtreeLogHeadRefile self, OrgContext* org_context, haxorg_SubtreeLogHeadRefile other);
};

template <>
struct org::bind::c::VTable<haxorg_SubtreeLogHeadClock, haxorg_SubtreeLogHeadClock_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_SubtreeLogHeadClock self, OrgContext* org_context, haxorg_SubtreeLogHeadClock other);
};

template <>
struct org::bind::c::VTable<haxorg_SubtreeLogHeadState, haxorg_SubtreeLogHeadState_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_SubtreeLogHeadState self, OrgContext* org_context, haxorg_SubtreeLogHeadState other);
};

template <>
struct org::bind::c::VTable<haxorg_SubtreeLogHeadDeadline, haxorg_SubtreeLogHeadDeadline_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_SubtreeLogHeadDeadline self, OrgContext* org_context, haxorg_SubtreeLogHeadDeadline other);
};

template <>
struct org::bind::c::VTable<haxorg_SubtreeLogHeadSchedule, haxorg_SubtreeLogHeadSchedule_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_SubtreeLogHeadSchedule self, OrgContext* org_context, haxorg_SubtreeLogHeadSchedule other);
};

template <>
struct org::bind::c::VTable<haxorg_SubtreeLogHeadTag, haxorg_SubtreeLogHeadTag_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_SubtreeLogHeadTag self, OrgContext* org_context, haxorg_SubtreeLogHeadTag other);
};

template <>
struct org::bind::c::VTable<haxorg_SubtreeLogHeadUnknown, haxorg_SubtreeLogHeadUnknown_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_SubtreeLogHeadUnknown self, OrgContext* org_context, haxorg_SubtreeLogHeadUnknown other);
};

template <>
struct org::bind::c::VTable<haxorg_SubtreeCompletion, haxorg_SubtreeCompletion_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_SubtreeCompletion self, OrgContext* org_context, haxorg_SubtreeCompletion other);
};

template <>
struct org::bind::c::VTable<haxorg_AttrList, haxorg_AttrList_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_AttrList self, OrgContext* org_context, haxorg_AttrList other);
};

template <>
struct org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdVec getFlatArgs_const(haxorg_AttrGroup self, OrgContext* org_context);
  static haxorg_HstdVec getAttrs_const(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdOpt key);
  static void setNamedAttr(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdStr key, haxorg_HstdVec attrs);
  static void setPositionalAttr(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdVec items);
  static int getPositionalSize_const(haxorg_AttrGroup self, OrgContext* org_context);
  static int getNamedSize_const(haxorg_AttrGroup self, OrgContext* org_context);
  static bool isEmpty_const(haxorg_AttrGroup self, OrgContext* org_context);
  static haxorg_AttrList getAll_const(haxorg_AttrGroup self, OrgContext* org_context);
  static haxorg_AttrValue atPositional_const(haxorg_AttrGroup self, OrgContext* org_context, int index);
  static haxorg_HstdOpt getPositional_const(haxorg_AttrGroup self, OrgContext* org_context, int index);
  static haxorg_AttrList atNamed_const(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdStr index);
  static haxorg_HstdOpt getNamed_const(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdStr index);
  static haxorg_AttrValue atFirstNamed_const(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdStr index);
  static haxorg_HstdOpt getFirstNamed_const(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdStr index);
  static haxorg_AttrList atVarNamed_const(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdStr index);
  static haxorg_HstdOpt getVarNamed_const(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdStr index);
  static haxorg_AttrValue atFirstVarNamed_const(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdStr index);
  static haxorg_HstdOpt getFirstVarNamed_const(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdStr index);
  static bool __eq___const(haxorg_AttrGroup self, OrgContext* org_context, haxorg_AttrGroup other);
};

template <>
struct org::bind::c::VTable<haxorg_OrgCodeEvalInput, haxorg_OrgCodeEvalInput_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_OrgCodeEvalInput self, OrgContext* org_context, haxorg_OrgCodeEvalInput other);
  static haxorg_HstdOpt getVariable_const(haxorg_OrgCodeEvalInput self, OrgContext* org_context, haxorg_HstdStr name);
};

template <>
struct org::bind::c::VTable<haxorg_OrgCodeEvalInputVar, haxorg_OrgCodeEvalInputVar_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_OrgCodeEvalInputVar self, OrgContext* org_context, haxorg_OrgCodeEvalInputVar other);
};

template <>
struct org::bind::c::VTable<haxorg_OrgCodeEvalOutput, haxorg_OrgCodeEvalOutput_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_OrgCodeEvalOutput self, OrgContext* org_context, haxorg_OrgCodeEvalOutput other);
};

template <>
struct org::bind::c::VTable<haxorg_ColumnView, haxorg_ColumnView_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ColumnView self, OrgContext* org_context, haxorg_ColumnView other);
};

template <>
struct org::bind::c::VTable<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ColumnViewSummary self, OrgContext* org_context, haxorg_ColumnViewSummary other);
  static bool isCheckboxAggregate_const(haxorg_ColumnViewSummary self, OrgContext* org_context);
  static haxorg_ColumnViewSummaryCheckboxAggregate getCheckboxAggregateConst_const(haxorg_ColumnViewSummary self, OrgContext* org_context);
  static haxorg_ColumnViewSummaryCheckboxAggregate getCheckboxAggregateMut(haxorg_ColumnViewSummary self, OrgContext* org_context);
  static bool isMathAggregate_const(haxorg_ColumnViewSummary self, OrgContext* org_context);
  static haxorg_ColumnViewSummaryMathAggregate getMathAggregateConst_const(haxorg_ColumnViewSummary self, OrgContext* org_context);
  static haxorg_ColumnViewSummaryMathAggregate getMathAggregateMut(haxorg_ColumnViewSummary self, OrgContext* org_context);
  static haxorg_ColumnViewSummaryKind getKind_const(haxorg_ColumnViewSummary self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ColumnViewSummaryCheckboxAggregate, haxorg_ColumnViewSummaryCheckboxAggregate_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ColumnViewSummaryCheckboxAggregate self, OrgContext* org_context, haxorg_ColumnViewSummaryCheckboxAggregate other);
};

template <>
struct org::bind::c::VTable<haxorg_ColumnViewSummaryMathAggregate, haxorg_ColumnViewSummaryMathAggregate_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ColumnViewSummaryMathAggregate self, OrgContext* org_context, haxorg_ColumnViewSummaryMathAggregate other);
};

template <>
struct org::bind::c::VTable<haxorg_ColumnViewColumn, haxorg_ColumnViewColumn_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ColumnViewColumn self, OrgContext* org_context, haxorg_ColumnViewColumn other);
};

template <>
struct org::bind::c::VTable<haxorg_BlockCodeLine, haxorg_BlockCodeLine_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_BlockCodeLine self, OrgContext* org_context, haxorg_BlockCodeLine other);
};

template <>
struct org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_BlockCodeLinePart self, OrgContext* org_context, haxorg_BlockCodeLinePart other);
  static bool isRaw_const(haxorg_BlockCodeLinePart self, OrgContext* org_context);
  static haxorg_BlockCodeLinePartRaw getRawConst_const(haxorg_BlockCodeLinePart self, OrgContext* org_context);
  static haxorg_BlockCodeLinePartRaw getRawMut(haxorg_BlockCodeLinePart self, OrgContext* org_context);
  static bool isCallout_const(haxorg_BlockCodeLinePart self, OrgContext* org_context);
  static haxorg_BlockCodeLinePartCallout getCalloutConst_const(haxorg_BlockCodeLinePart self, OrgContext* org_context);
  static haxorg_BlockCodeLinePartCallout getCalloutMut(haxorg_BlockCodeLinePart self, OrgContext* org_context);
  static bool isTangle_const(haxorg_BlockCodeLinePart self, OrgContext* org_context);
  static haxorg_BlockCodeLinePartTangle getTangleConst_const(haxorg_BlockCodeLinePart self, OrgContext* org_context);
  static haxorg_BlockCodeLinePartTangle getTangleMut(haxorg_BlockCodeLinePart self, OrgContext* org_context);
  static haxorg_BlockCodeLinePartKind getKind_const(haxorg_BlockCodeLinePart self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_BlockCodeLinePartRaw, haxorg_BlockCodeLinePartRaw_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_BlockCodeLinePartRaw self, OrgContext* org_context, haxorg_BlockCodeLinePartRaw other);
};

template <>
struct org::bind::c::VTable<haxorg_BlockCodeLinePartCallout, haxorg_BlockCodeLinePartCallout_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_BlockCodeLinePartCallout self, OrgContext* org_context, haxorg_BlockCodeLinePartCallout other);
};

template <>
struct org::bind::c::VTable<haxorg_BlockCodeLinePartTangle, haxorg_BlockCodeLinePartTangle_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_BlockCodeLinePartTangle self, OrgContext* org_context, haxorg_BlockCodeLinePartTangle other);
};

template <>
struct org::bind::c::VTable<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_DocumentExportConfig self, OrgContext* org_context, haxorg_DocumentExportConfig other);
  static bool isDoExport_const(haxorg_DocumentExportConfig self, OrgContext* org_context);
  static haxorg_DocumentExportConfigDoExport getDoExportConst_const(haxorg_DocumentExportConfig self, OrgContext* org_context);
  static haxorg_DocumentExportConfigDoExport getDoExportMut(haxorg_DocumentExportConfig self, OrgContext* org_context);
  static bool isExportFixed_const(haxorg_DocumentExportConfig self, OrgContext* org_context);
  static haxorg_DocumentExportConfigExportFixed getExportFixedConst_const(haxorg_DocumentExportConfig self, OrgContext* org_context);
  static haxorg_DocumentExportConfigExportFixed getExportFixedMut(haxorg_DocumentExportConfig self, OrgContext* org_context);
  static haxorg_DocumentExportConfigTocExportKind getTocExportKind_const(haxorg_DocumentExportConfig self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_DocumentExportConfigTaskExport, haxorg_DocumentExportConfigTaskExport_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_DocumentExportConfigTaskExport self, OrgContext* org_context, haxorg_DocumentExportConfigTaskExport other);
};

template <>
struct org::bind::c::VTable<haxorg_DocumentExportConfigDoExport, haxorg_DocumentExportConfigDoExport_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_DocumentExportConfigDoExport self, OrgContext* org_context, haxorg_DocumentExportConfigDoExport other);
};

template <>
struct org::bind::c::VTable<haxorg_DocumentExportConfigExportFixed, haxorg_DocumentExportConfigExportFixed_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_DocumentExportConfigExportFixed self, OrgContext* org_context, haxorg_DocumentExportConfigExportFixed other);
};

template <>
struct org::bind::c::VTable<haxorg_SubtreePeriod, haxorg_SubtreePeriod_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_SubtreePeriod self, OrgContext* org_context, haxorg_SubtreePeriod other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool isMatching_const(haxorg_NamedProperty self, OrgContext* org_context, haxorg_HstdStr kind, haxorg_HstdOpt subKind);
  static haxorg_HstdStr getName_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_HstdOpt getSubKind_const(haxorg_NamedProperty self, OrgContext* org_context);
  static bool __eq___const(haxorg_NamedProperty self, OrgContext* org_context, haxorg_NamedProperty other);
  static bool isNonblocking_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyNonblocking getNonblockingConst_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyNonblocking getNonblockingMut(haxorg_NamedProperty self, OrgContext* org_context);
  static bool isArchiveTime_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyArchiveTime getArchiveTimeConst_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyArchiveTime getArchiveTimeMut(haxorg_NamedProperty self, OrgContext* org_context);
  static bool isArchiveFile_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyArchiveFile getArchiveFileConst_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyArchiveFile getArchiveFileMut(haxorg_NamedProperty self, OrgContext* org_context);
  static bool isArchiveOlpath_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyArchiveOlpath getArchiveOlpathConst_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyArchiveOlpath getArchiveOlpathMut(haxorg_NamedProperty self, OrgContext* org_context);
  static bool isArchiveTarget_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyArchiveTarget getArchiveTargetConst_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyArchiveTarget getArchiveTargetMut(haxorg_NamedProperty self, OrgContext* org_context);
  static bool isArchiveCategory_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyArchiveCategory getArchiveCategoryConst_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyArchiveCategory getArchiveCategoryMut(haxorg_NamedProperty self, OrgContext* org_context);
  static bool isArchiveTodo_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyArchiveTodo getArchiveTodoConst_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyArchiveTodo getArchiveTodoMut(haxorg_NamedProperty self, OrgContext* org_context);
  static bool isTrigger_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyTrigger getTriggerConst_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyTrigger getTriggerMut(haxorg_NamedProperty self, OrgContext* org_context);
  static bool isExportLatexClass_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyExportLatexClass getExportLatexClassConst_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyExportLatexClass getExportLatexClassMut(haxorg_NamedProperty self, OrgContext* org_context);
  static bool isCookieData_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyCookieData getCookieDataConst_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyCookieData getCookieDataMut(haxorg_NamedProperty self, OrgContext* org_context);
  static bool isExportLatexClassOptions_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyExportLatexClassOptions getExportLatexClassOptionsConst_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyExportLatexClassOptions getExportLatexClassOptionsMut(haxorg_NamedProperty self, OrgContext* org_context);
  static bool isExportLatexHeader_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyExportLatexHeader getExportLatexHeaderConst_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyExportLatexHeader getExportLatexHeaderMut(haxorg_NamedProperty self, OrgContext* org_context);
  static bool isExportLatexCompiler_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyExportLatexCompiler getExportLatexCompilerConst_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyExportLatexCompiler getExportLatexCompilerMut(haxorg_NamedProperty self, OrgContext* org_context);
  static bool isOrdered_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyOrdered getOrderedConst_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyOrdered getOrderedMut(haxorg_NamedProperty self, OrgContext* org_context);
  static bool isEffort_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyEffort getEffortConst_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyEffort getEffortMut(haxorg_NamedProperty self, OrgContext* org_context);
  static bool isVisibility_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyVisibility getVisibilityConst_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyVisibility getVisibilityMut(haxorg_NamedProperty self, OrgContext* org_context);
  static bool isExportOptions_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyExportOptions getExportOptionsConst_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyExportOptions getExportOptionsMut(haxorg_NamedProperty self, OrgContext* org_context);
  static bool isBlocker_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyBlocker getBlockerConst_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyBlocker getBlockerMut(haxorg_NamedProperty self, OrgContext* org_context);
  static bool isUnnumbered_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyUnnumbered getUnnumberedConst_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyUnnumbered getUnnumberedMut(haxorg_NamedProperty self, OrgContext* org_context);
  static bool isCreated_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyCreated getCreatedConst_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyCreated getCreatedMut(haxorg_NamedProperty self, OrgContext* org_context);
  static bool isRadioId_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyRadioId getRadioIdConst_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyRadioId getRadioIdMut(haxorg_NamedProperty self, OrgContext* org_context);
  static bool isHashtagDef_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyHashtagDef getHashtagDefConst_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyHashtagDef getHashtagDefMut(haxorg_NamedProperty self, OrgContext* org_context);
  static bool isCustomArgs_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyCustomArgs getCustomArgsConst_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyCustomArgs getCustomArgsMut(haxorg_NamedProperty self, OrgContext* org_context);
  static bool isCustomRaw_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyCustomRaw getCustomRawConst_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyCustomRaw getCustomRawMut(haxorg_NamedProperty self, OrgContext* org_context);
  static bool isCustomId_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyCustomId getCustomIdConst_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyCustomId getCustomIdMut(haxorg_NamedProperty self, OrgContext* org_context);
  static bool isCustomSubtreeJson_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyCustomSubtreeJson getCustomSubtreeJsonConst_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyCustomSubtreeJson getCustomSubtreeJsonMut(haxorg_NamedProperty self, OrgContext* org_context);
  static bool isCustomSubtreeFlags_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyCustomSubtreeFlags getCustomSubtreeFlagsConst_const(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyCustomSubtreeFlags getCustomSubtreeFlagsMut(haxorg_NamedProperty self, OrgContext* org_context);
  static haxorg_NamedPropertyKind getKind_const(haxorg_NamedProperty self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyNonblocking, haxorg_NamedPropertyNonblocking_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_NamedPropertyNonblocking self, OrgContext* org_context, haxorg_NamedPropertyNonblocking other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyArchiveTime, haxorg_NamedPropertyArchiveTime_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_NamedPropertyArchiveTime self, OrgContext* org_context, haxorg_NamedPropertyArchiveTime other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyArchiveFile, haxorg_NamedPropertyArchiveFile_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_NamedPropertyArchiveFile self, OrgContext* org_context, haxorg_NamedPropertyArchiveFile other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyArchiveOlpath, haxorg_NamedPropertyArchiveOlpath_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_NamedPropertyArchiveOlpath self, OrgContext* org_context, haxorg_NamedPropertyArchiveOlpath other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyArchiveTarget, haxorg_NamedPropertyArchiveTarget_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_NamedPropertyArchiveTarget self, OrgContext* org_context, haxorg_NamedPropertyArchiveTarget other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyArchiveCategory, haxorg_NamedPropertyArchiveCategory_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_NamedPropertyArchiveCategory self, OrgContext* org_context, haxorg_NamedPropertyArchiveCategory other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyArchiveTodo, haxorg_NamedPropertyArchiveTodo_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_NamedPropertyArchiveTodo self, OrgContext* org_context, haxorg_NamedPropertyArchiveTodo other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyTrigger, haxorg_NamedPropertyTrigger_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_NamedPropertyTrigger self, OrgContext* org_context, haxorg_NamedPropertyTrigger other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyExportLatexClass, haxorg_NamedPropertyExportLatexClass_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_NamedPropertyExportLatexClass self, OrgContext* org_context, haxorg_NamedPropertyExportLatexClass other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyCookieData, haxorg_NamedPropertyCookieData_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_NamedPropertyCookieData self, OrgContext* org_context, haxorg_NamedPropertyCookieData other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyExportLatexClassOptions, haxorg_NamedPropertyExportLatexClassOptions_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_NamedPropertyExportLatexClassOptions self, OrgContext* org_context, haxorg_NamedPropertyExportLatexClassOptions other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyExportLatexHeader, haxorg_NamedPropertyExportLatexHeader_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_NamedPropertyExportLatexHeader self, OrgContext* org_context, haxorg_NamedPropertyExportLatexHeader other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyExportLatexCompiler, haxorg_NamedPropertyExportLatexCompiler_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_NamedPropertyExportLatexCompiler self, OrgContext* org_context, haxorg_NamedPropertyExportLatexCompiler other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyOrdered, haxorg_NamedPropertyOrdered_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_NamedPropertyOrdered self, OrgContext* org_context, haxorg_NamedPropertyOrdered other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyEffort, haxorg_NamedPropertyEffort_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_NamedPropertyEffort self, OrgContext* org_context, haxorg_NamedPropertyEffort other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyVisibility, haxorg_NamedPropertyVisibility_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_NamedPropertyVisibility self, OrgContext* org_context, haxorg_NamedPropertyVisibility other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyExportOptions, haxorg_NamedPropertyExportOptions_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_NamedPropertyExportOptions self, OrgContext* org_context, haxorg_NamedPropertyExportOptions other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyBlocker, haxorg_NamedPropertyBlocker_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_NamedPropertyBlocker self, OrgContext* org_context, haxorg_NamedPropertyBlocker other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyUnnumbered, haxorg_NamedPropertyUnnumbered_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_NamedPropertyUnnumbered self, OrgContext* org_context, haxorg_NamedPropertyUnnumbered other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyCreated, haxorg_NamedPropertyCreated_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_NamedPropertyCreated self, OrgContext* org_context, haxorg_NamedPropertyCreated other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyRadioId, haxorg_NamedPropertyRadioId_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_NamedPropertyRadioId self, OrgContext* org_context, haxorg_NamedPropertyRadioId other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyHashtagDef, haxorg_NamedPropertyHashtagDef_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_NamedPropertyHashtagDef self, OrgContext* org_context, haxorg_NamedPropertyHashtagDef other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyCustomArgs, haxorg_NamedPropertyCustomArgs_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_NamedPropertyCustomArgs self, OrgContext* org_context, haxorg_NamedPropertyCustomArgs other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyCustomRaw, haxorg_NamedPropertyCustomRaw_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_NamedPropertyCustomRaw self, OrgContext* org_context, haxorg_NamedPropertyCustomRaw other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyCustomId, haxorg_NamedPropertyCustomId_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_NamedPropertyCustomId self, OrgContext* org_context, haxorg_NamedPropertyCustomId other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyCustomSubtreeJson, haxorg_NamedPropertyCustomSubtreeJson_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_NamedPropertyCustomSubtreeJson self, OrgContext* org_context, haxorg_NamedPropertyCustomSubtreeJson other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyCustomSubtreeFlags, haxorg_NamedPropertyCustomSubtreeFlags_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_NamedPropertyCustomSubtreeFlags self, OrgContext* org_context, haxorg_NamedPropertyCustomSubtreeFlags other);
};

template <>
struct org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_OrgDiagnostics self, OrgContext* org_context, haxorg_OrgDiagnostics other);
  static bool isParseTokenError_const(haxorg_OrgDiagnostics self, OrgContext* org_context);
  static haxorg_OrgDiagnosticsParseTokenError getParseTokenErrorConst_const(haxorg_OrgDiagnostics self, OrgContext* org_context);
  static haxorg_OrgDiagnosticsParseTokenError getParseTokenErrorMut(haxorg_OrgDiagnostics self, OrgContext* org_context);
  static bool isParseError_const(haxorg_OrgDiagnostics self, OrgContext* org_context);
  static haxorg_OrgDiagnosticsParseError getParseErrorConst_const(haxorg_OrgDiagnostics self, OrgContext* org_context);
  static haxorg_OrgDiagnosticsParseError getParseErrorMut(haxorg_OrgDiagnostics self, OrgContext* org_context);
  static bool isIncludeError_const(haxorg_OrgDiagnostics self, OrgContext* org_context);
  static haxorg_OrgDiagnosticsIncludeError getIncludeErrorConst_const(haxorg_OrgDiagnostics self, OrgContext* org_context);
  static haxorg_OrgDiagnosticsIncludeError getIncludeErrorMut(haxorg_OrgDiagnostics self, OrgContext* org_context);
  static bool isConvertError_const(haxorg_OrgDiagnostics self, OrgContext* org_context);
  static haxorg_OrgDiagnosticsConvertError getConvertErrorConst_const(haxorg_OrgDiagnostics self, OrgContext* org_context);
  static haxorg_OrgDiagnosticsConvertError getConvertErrorMut(haxorg_OrgDiagnostics self, OrgContext* org_context);
  static bool isInternalError_const(haxorg_OrgDiagnostics self, OrgContext* org_context);
  static haxorg_OrgDiagnosticsInternalError getInternalErrorConst_const(haxorg_OrgDiagnostics self, OrgContext* org_context);
  static haxorg_OrgDiagnosticsInternalError getInternalErrorMut(haxorg_OrgDiagnostics self, OrgContext* org_context);
  static haxorg_OrgDiagnosticsKind getKind_const(haxorg_OrgDiagnostics self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_OrgDiagnosticsParseTokenError, haxorg_OrgDiagnosticsParseTokenError_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_OrgDiagnosticsParseTokenError self, OrgContext* org_context, haxorg_OrgDiagnosticsParseTokenError other);
};

template <>
struct org::bind::c::VTable<haxorg_OrgDiagnosticsParseError, haxorg_OrgDiagnosticsParseError_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_OrgDiagnosticsParseError self, OrgContext* org_context, haxorg_OrgDiagnosticsParseError other);
};

template <>
struct org::bind::c::VTable<haxorg_OrgDiagnosticsIncludeError, haxorg_OrgDiagnosticsIncludeError_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_OrgDiagnosticsIncludeError self, OrgContext* org_context, haxorg_OrgDiagnosticsIncludeError other);
};

template <>
struct org::bind::c::VTable<haxorg_OrgDiagnosticsConvertError, haxorg_OrgDiagnosticsConvertError_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_OrgDiagnosticsConvertError self, OrgContext* org_context, haxorg_OrgDiagnosticsConvertError other);
};

template <>
struct org::bind::c::VTable<haxorg_OrgDiagnosticsInternalError, haxorg_OrgDiagnosticsInternalError_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_OrgDiagnosticsInternalError self, OrgContext* org_context, haxorg_OrgDiagnosticsInternalError other);
};

template <>
struct org::bind::c::VTable<haxorg_NoNode, haxorg_NoNode_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ErrorItem, haxorg_ErrorItem_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ErrorGroup, haxorg_ErrorGroup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdVec getAttached_const(haxorg_Stmt self, OrgContext* org_context, haxorg_HstdOpt kind);
  static haxorg_HstdVec getCaption_const(haxorg_Stmt self, OrgContext* org_context);
  static haxorg_HstdVec getName_const(haxorg_Stmt self, OrgContext* org_context);
  static haxorg_HstdVec getAttrs_const(haxorg_Stmt self, OrgContext* org_context, haxorg_HstdOpt kind);
  static haxorg_HstdOpt getFirstAttr_const(haxorg_Stmt self, OrgContext* org_context, haxorg_HstdStr kind);
  static haxorg_HstdOpt getFirstAttrString_const(haxorg_Stmt self, OrgContext* org_context, haxorg_HstdStr kind);
  static haxorg_HstdOpt getFirstAttrInt_const(haxorg_Stmt self, OrgContext* org_context, haxorg_HstdStr kind);
  static haxorg_HstdOpt getFirstAttrBool_const(haxorg_Stmt self, OrgContext* org_context, haxorg_HstdStr kind);
  static haxorg_HstdOpt getFirstAttrDouble_const(haxorg_Stmt self, OrgContext* org_context, haxorg_HstdStr kind);
  static haxorg_HstdOpt getFirstAttrLisp_const(haxorg_Stmt self, OrgContext* org_context, haxorg_HstdStr kind);
  static haxorg_HstdOpt getFirstAttrKind_const(haxorg_Stmt self, OrgContext* org_context, haxorg_HstdStr kind);
};

template <>
struct org::bind::c::VTable<haxorg_Inline, haxorg_Inline_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_StmtList, haxorg_StmtList_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Empty, haxorg_Empty_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Leaf, haxorg_Leaf_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getText_const(haxorg_Leaf self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdOpt getYear_const(haxorg_Time self, OrgContext* org_context);
  static haxorg_HstdOpt getMonth_const(haxorg_Time self, OrgContext* org_context);
  static haxorg_HstdOpt getDay_const(haxorg_Time self, OrgContext* org_context);
  static haxorg_HstdOpt getHour_const(haxorg_Time self, OrgContext* org_context);
  static haxorg_HstdOpt getMinute_const(haxorg_Time self, OrgContext* org_context);
  static haxorg_HstdOpt getSecond_const(haxorg_Time self, OrgContext* org_context);
  static haxorg_UserTime getStaticTime_const(haxorg_Time self, OrgContext* org_context);
  static bool isStatic_const(haxorg_Time self, OrgContext* org_context);
  static haxorg_TimeStatic getStaticConst_const(haxorg_Time self, OrgContext* org_context);
  static haxorg_TimeStatic getStaticMut(haxorg_Time self, OrgContext* org_context);
  static bool isDynamic_const(haxorg_Time self, OrgContext* org_context);
  static haxorg_TimeDynamic getDynamicConst_const(haxorg_Time self, OrgContext* org_context);
  static haxorg_TimeDynamic getDynamicMut(haxorg_Time self, OrgContext* org_context);
  static haxorg_TimeTimeKind getTimeKind_const(haxorg_Time self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_TimeRepeat, haxorg_TimeRepeat_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_TimeRepeat self, OrgContext* org_context, haxorg_TimeRepeat other);
};

template <>
struct org::bind::c::VTable<haxorg_TimeStatic, haxorg_TimeStatic_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_TimeStatic self, OrgContext* org_context, haxorg_TimeStatic other);
};

template <>
struct org::bind::c::VTable<haxorg_TimeDynamic, haxorg_TimeDynamic_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_TimeDynamic self, OrgContext* org_context, haxorg_TimeDynamic other);
};

template <>
struct org::bind::c::VTable<haxorg_TimeRange, haxorg_TimeRange_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdOpt getClockedTimeSeconds_const(haxorg_TimeRange self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_Macro, haxorg_Macro_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Symbol, haxorg_Symbol_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_SymbolParam, haxorg_SymbolParam_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ErrorSkipGroup, haxorg_ErrorSkipGroup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Markup, haxorg_Markup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_RadioTarget, haxorg_RadioTarget_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Latex, haxorg_Latex_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_SubtreeLog, haxorg_SubtreeLog_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static void setDescription(haxorg_SubtreeLog self, OrgContext* org_context, haxorg_SemId desc);
};

template <>
struct org::bind::c::VTable<haxorg_Subtree, haxorg_Subtree_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdVec getTimePeriods_const(haxorg_Subtree self, OrgContext* org_context, haxorg_HstdIntSet kinds);
  static haxorg_HstdVec getProperties_const(haxorg_Subtree self, OrgContext* org_context, haxorg_HstdStr kind, haxorg_HstdOpt subkind);
  static haxorg_HstdOpt getProperty_const(haxorg_Subtree self, OrgContext* org_context, haxorg_HstdStr kind, haxorg_HstdOpt subkind);
  static void removeProperty(haxorg_Subtree self, OrgContext* org_context, haxorg_HstdStr kind, haxorg_HstdOpt subkind);
  static void setProperty(haxorg_Subtree self, OrgContext* org_context, haxorg_NamedProperty value);
  static void setPropertyStrValue(haxorg_Subtree self, OrgContext* org_context, haxorg_HstdStr value, haxorg_HstdStr kind, haxorg_HstdOpt subkind);
  static haxorg_HstdStr getCleanTitle_const(haxorg_Subtree self, OrgContext* org_context);
  static haxorg_HstdOpt getTodoKeyword_const(haxorg_Subtree self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ColonExample, haxorg_ColonExample_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Call, haxorg_Call_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ListItem, haxorg_ListItem_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool isDescriptionItem_const(haxorg_ListItem self, OrgContext* org_context);
  static haxorg_HstdOpt getCleanHeader_const(haxorg_ListItem self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_DocumentOptions, haxorg_DocumentOptions_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdVec getProperties_const(haxorg_DocumentOptions self, OrgContext* org_context, haxorg_HstdStr kind, haxorg_HstdOpt subKind);
  static haxorg_HstdOpt getProperty_const(haxorg_DocumentOptions self, OrgContext* org_context, haxorg_HstdStr kind, haxorg_HstdOpt subKind);
};

template <>
struct org::bind::c::VTable<haxorg_DocumentFragment, haxorg_DocumentFragment_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_CriticMarkup, haxorg_CriticMarkup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Document, haxorg_Document_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdVec getProperties_const(haxorg_Document self, OrgContext* org_context, haxorg_HstdStr kind, haxorg_HstdOpt subKind);
  static haxorg_HstdOpt getProperty_const(haxorg_Document self, OrgContext* org_context, haxorg_HstdStr kind, haxorg_HstdOpt subKind);
};

template <>
struct org::bind::c::VTable<haxorg_FileTarget, haxorg_FileTarget_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_TextSeparator, haxorg_TextSeparator_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_DocumentGroup, haxorg_DocumentGroup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_File, haxorg_File_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool isDocument_const(haxorg_File self, OrgContext* org_context);
  static haxorg_FileDocument getDocumentConst_const(haxorg_File self, OrgContext* org_context);
  static haxorg_FileDocument getDocumentMut(haxorg_File self, OrgContext* org_context);
  static bool isAttachment_const(haxorg_File self, OrgContext* org_context);
  static haxorg_FileAttachment getAttachmentConst_const(haxorg_File self, OrgContext* org_context);
  static haxorg_FileAttachment getAttachmentMut(haxorg_File self, OrgContext* org_context);
  static bool isSource_const(haxorg_File self, OrgContext* org_context);
  static haxorg_FileSource getSourceConst_const(haxorg_File self, OrgContext* org_context);
  static haxorg_FileSource getSourceMut(haxorg_File self, OrgContext* org_context);
  static haxorg_FileKind getFileKind_const(haxorg_File self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_FileDocument, haxorg_FileDocument_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_FileAttachment, haxorg_FileAttachment_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_FileSource, haxorg_FileSource_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Directory, haxorg_Directory_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Symlink, haxorg_Symlink_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool isExample_const(haxorg_CmdInclude self, OrgContext* org_context);
  static haxorg_CmdIncludeExample getExampleConst_const(haxorg_CmdInclude self, OrgContext* org_context);
  static haxorg_CmdIncludeExample getExampleMut(haxorg_CmdInclude self, OrgContext* org_context);
  static bool isExport_const(haxorg_CmdInclude self, OrgContext* org_context);
  static haxorg_CmdIncludeExport getExportConst_const(haxorg_CmdInclude self, OrgContext* org_context);
  static haxorg_CmdIncludeExport getExportMut(haxorg_CmdInclude self, OrgContext* org_context);
  static bool isCustom_const(haxorg_CmdInclude self, OrgContext* org_context);
  static haxorg_CmdIncludeCustom getCustomConst_const(haxorg_CmdInclude self, OrgContext* org_context);
  static haxorg_CmdIncludeCustom getCustomMut(haxorg_CmdInclude self, OrgContext* org_context);
  static bool isSrc_const(haxorg_CmdInclude self, OrgContext* org_context);
  static haxorg_CmdIncludeSrc getSrcConst_const(haxorg_CmdInclude self, OrgContext* org_context);
  static haxorg_CmdIncludeSrc getSrcMut(haxorg_CmdInclude self, OrgContext* org_context);
  static bool isOrgDocument_const(haxorg_CmdInclude self, OrgContext* org_context);
  static haxorg_CmdIncludeOrgDocument getOrgDocumentConst_const(haxorg_CmdInclude self, OrgContext* org_context);
  static haxorg_CmdIncludeOrgDocument getOrgDocumentMut(haxorg_CmdInclude self, OrgContext* org_context);
  static haxorg_CmdIncludeKind getIncludeKind_const(haxorg_CmdInclude self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_CmdIncludeIncludeBase, haxorg_CmdIncludeIncludeBase_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_CmdIncludeIncludeBase self, OrgContext* org_context, haxorg_CmdIncludeIncludeBase other);
};

template <>
struct org::bind::c::VTable<haxorg_CmdIncludeExample, haxorg_CmdIncludeExample_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_CmdIncludeExample self, OrgContext* org_context, haxorg_CmdIncludeExample other);
};

template <>
struct org::bind::c::VTable<haxorg_CmdIncludeExport, haxorg_CmdIncludeExport_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_CmdIncludeExport self, OrgContext* org_context, haxorg_CmdIncludeExport other);
};

template <>
struct org::bind::c::VTable<haxorg_CmdIncludeCustom, haxorg_CmdIncludeCustom_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_CmdIncludeCustom self, OrgContext* org_context, haxorg_CmdIncludeCustom other);
};

template <>
struct org::bind::c::VTable<haxorg_CmdIncludeSrc, haxorg_CmdIncludeSrc_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_CmdIncludeSrc self, OrgContext* org_context, haxorg_CmdIncludeSrc other);
};

template <>
struct org::bind::c::VTable<haxorg_CmdIncludeOrgDocument, haxorg_CmdIncludeOrgDocument_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_CmdIncludeOrgDocument self, OrgContext* org_context, haxorg_CmdIncludeOrgDocument other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmNoNode, haxorg_ImmNoNode_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmNoNode self, OrgContext* org_context, haxorg_ImmNoNode other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmErrorItem, haxorg_ImmErrorItem_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmErrorItem self, OrgContext* org_context, haxorg_ImmErrorItem other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmErrorGroup, haxorg_ImmErrorGroup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmErrorGroup self, OrgContext* org_context, haxorg_ImmErrorGroup other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmStmt, haxorg_ImmStmt_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmStmt self, OrgContext* org_context, haxorg_ImmStmt other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmInline, haxorg_ImmInline_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmInline self, OrgContext* org_context, haxorg_ImmInline other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmStmtList, haxorg_ImmStmtList_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmStmtList self, OrgContext* org_context, haxorg_ImmStmtList other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmEmpty, haxorg_ImmEmpty_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmEmpty self, OrgContext* org_context, haxorg_ImmEmpty other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmLeaf, haxorg_ImmLeaf_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmLeaf self, OrgContext* org_context, haxorg_ImmLeaf other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmTime, haxorg_ImmTime_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmTime self, OrgContext* org_context, haxorg_ImmTime other);
  static bool isStatic_const(haxorg_ImmTime self, OrgContext* org_context);
  static haxorg_ImmTimeStatic getStaticConst_const(haxorg_ImmTime self, OrgContext* org_context);
  static haxorg_ImmTimeStatic getStaticMut(haxorg_ImmTime self, OrgContext* org_context);
  static bool isDynamic_const(haxorg_ImmTime self, OrgContext* org_context);
  static haxorg_ImmTimeDynamic getDynamicConst_const(haxorg_ImmTime self, OrgContext* org_context);
  static haxorg_ImmTimeDynamic getDynamicMut(haxorg_ImmTime self, OrgContext* org_context);
  static haxorg_ImmTimeTimeKind getTimeKind_const(haxorg_ImmTime self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmTimeRepeat, haxorg_ImmTimeRepeat_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmTimeRepeat self, OrgContext* org_context, haxorg_ImmTimeRepeat other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmTimeStatic, haxorg_ImmTimeStatic_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmTimeStatic self, OrgContext* org_context, haxorg_ImmTimeStatic other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmTimeDynamic, haxorg_ImmTimeDynamic_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmTimeDynamic self, OrgContext* org_context, haxorg_ImmTimeDynamic other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmTimeRange, haxorg_ImmTimeRange_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmTimeRange self, OrgContext* org_context, haxorg_ImmTimeRange other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmMacro, haxorg_ImmMacro_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmMacro self, OrgContext* org_context, haxorg_ImmMacro other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmSymbol, haxorg_ImmSymbol_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmSymbol self, OrgContext* org_context, haxorg_ImmSymbol other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmSymbolParam, haxorg_ImmSymbolParam_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmSymbolParam self, OrgContext* org_context, haxorg_ImmSymbolParam other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmErrorSkipGroup, haxorg_ImmErrorSkipGroup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmErrorSkipGroup self, OrgContext* org_context, haxorg_ImmErrorSkipGroup other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmMarkup, haxorg_ImmMarkup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmMarkup self, OrgContext* org_context, haxorg_ImmMarkup other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmRadioTarget, haxorg_ImmRadioTarget_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmRadioTarget self, OrgContext* org_context, haxorg_ImmRadioTarget other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmLatex, haxorg_ImmLatex_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmLatex self, OrgContext* org_context, haxorg_ImmLatex other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmSubtreeLog, haxorg_ImmSubtreeLog_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmSubtreeLog self, OrgContext* org_context, haxorg_ImmSubtreeLog other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmSubtree, haxorg_ImmSubtree_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmSubtree self, OrgContext* org_context, haxorg_ImmSubtree other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmColonExample, haxorg_ImmColonExample_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmColonExample self, OrgContext* org_context, haxorg_ImmColonExample other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCall, haxorg_ImmCall_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmCall self, OrgContext* org_context, haxorg_ImmCall other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmListItem, haxorg_ImmListItem_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmListItem self, OrgContext* org_context, haxorg_ImmListItem other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmDocumentOptions, haxorg_ImmDocumentOptions_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmDocumentOptions self, OrgContext* org_context, haxorg_ImmDocumentOptions other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmDocumentFragment, haxorg_ImmDocumentFragment_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmDocumentFragment self, OrgContext* org_context, haxorg_ImmDocumentFragment other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCriticMarkup, haxorg_ImmCriticMarkup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmCriticMarkup self, OrgContext* org_context, haxorg_ImmCriticMarkup other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmDocument, haxorg_ImmDocument_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmDocument self, OrgContext* org_context, haxorg_ImmDocument other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmFileTarget, haxorg_ImmFileTarget_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmFileTarget self, OrgContext* org_context, haxorg_ImmFileTarget other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmTextSeparator, haxorg_ImmTextSeparator_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmTextSeparator self, OrgContext* org_context, haxorg_ImmTextSeparator other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmDocumentGroup, haxorg_ImmDocumentGroup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmDocumentGroup self, OrgContext* org_context, haxorg_ImmDocumentGroup other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmFile self, OrgContext* org_context, haxorg_ImmFile other);
  static bool isDocument_const(haxorg_ImmFile self, OrgContext* org_context);
  static haxorg_ImmFileDocument getDocumentConst_const(haxorg_ImmFile self, OrgContext* org_context);
  static haxorg_ImmFileDocument getDocumentMut(haxorg_ImmFile self, OrgContext* org_context);
  static bool isAttachment_const(haxorg_ImmFile self, OrgContext* org_context);
  static haxorg_ImmFileAttachment getAttachmentConst_const(haxorg_ImmFile self, OrgContext* org_context);
  static haxorg_ImmFileAttachment getAttachmentMut(haxorg_ImmFile self, OrgContext* org_context);
  static bool isSource_const(haxorg_ImmFile self, OrgContext* org_context);
  static haxorg_ImmFileSource getSourceConst_const(haxorg_ImmFile self, OrgContext* org_context);
  static haxorg_ImmFileSource getSourceMut(haxorg_ImmFile self, OrgContext* org_context);
  static haxorg_ImmFileKind getFileKind_const(haxorg_ImmFile self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmFileDocument, haxorg_ImmFileDocument_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmFileDocument self, OrgContext* org_context, haxorg_ImmFileDocument other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmFileAttachment, haxorg_ImmFileAttachment_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmFileAttachment self, OrgContext* org_context, haxorg_ImmFileAttachment other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmFileSource, haxorg_ImmFileSource_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmFileSource self, OrgContext* org_context, haxorg_ImmFileSource other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmDirectory, haxorg_ImmDirectory_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmDirectory self, OrgContext* org_context, haxorg_ImmDirectory other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmSymlink, haxorg_ImmSymlink_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmSymlink self, OrgContext* org_context, haxorg_ImmSymlink other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmCmdInclude self, OrgContext* org_context, haxorg_ImmCmdInclude other);
  static bool isExample_const(haxorg_ImmCmdInclude self, OrgContext* org_context);
  static haxorg_ImmCmdIncludeExample getExampleConst_const(haxorg_ImmCmdInclude self, OrgContext* org_context);
  static haxorg_ImmCmdIncludeExample getExampleMut(haxorg_ImmCmdInclude self, OrgContext* org_context);
  static bool isExport_const(haxorg_ImmCmdInclude self, OrgContext* org_context);
  static haxorg_ImmCmdIncludeExport getExportConst_const(haxorg_ImmCmdInclude self, OrgContext* org_context);
  static haxorg_ImmCmdIncludeExport getExportMut(haxorg_ImmCmdInclude self, OrgContext* org_context);
  static bool isCustom_const(haxorg_ImmCmdInclude self, OrgContext* org_context);
  static haxorg_ImmCmdIncludeCustom getCustomConst_const(haxorg_ImmCmdInclude self, OrgContext* org_context);
  static haxorg_ImmCmdIncludeCustom getCustomMut(haxorg_ImmCmdInclude self, OrgContext* org_context);
  static bool isSrc_const(haxorg_ImmCmdInclude self, OrgContext* org_context);
  static haxorg_ImmCmdIncludeSrc getSrcConst_const(haxorg_ImmCmdInclude self, OrgContext* org_context);
  static haxorg_ImmCmdIncludeSrc getSrcMut(haxorg_ImmCmdInclude self, OrgContext* org_context);
  static bool isOrgDocument_const(haxorg_ImmCmdInclude self, OrgContext* org_context);
  static haxorg_ImmCmdIncludeOrgDocument getOrgDocumentConst_const(haxorg_ImmCmdInclude self, OrgContext* org_context);
  static haxorg_ImmCmdIncludeOrgDocument getOrgDocumentMut(haxorg_ImmCmdInclude self, OrgContext* org_context);
  static haxorg_ImmCmdIncludeKind getIncludeKind_const(haxorg_ImmCmdInclude self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdIncludeIncludeBase, haxorg_ImmCmdIncludeIncludeBase_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmCmdIncludeIncludeBase self, OrgContext* org_context, haxorg_ImmCmdIncludeIncludeBase other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdIncludeExample, haxorg_ImmCmdIncludeExample_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmCmdIncludeExample self, OrgContext* org_context, haxorg_ImmCmdIncludeExample other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdIncludeExport, haxorg_ImmCmdIncludeExport_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmCmdIncludeExport self, OrgContext* org_context, haxorg_ImmCmdIncludeExport other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdIncludeCustom, haxorg_ImmCmdIncludeCustom_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmCmdIncludeCustom self, OrgContext* org_context, haxorg_ImmCmdIncludeCustom other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdIncludeSrc, haxorg_ImmCmdIncludeSrc_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmCmdIncludeSrc self, OrgContext* org_context, haxorg_ImmCmdIncludeSrc other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdIncludeOrgDocument, haxorg_ImmCmdIncludeOrgDocument_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmCmdIncludeOrgDocument self, OrgContext* org_context, haxorg_ImmCmdIncludeOrgDocument other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterOrgAPI, haxorg_ImmAdapterOrgAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Cmd, haxorg_Cmd_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdVec getAttrs_const(haxorg_Cmd self, OrgContext* org_context, haxorg_HstdOpt key);
  static haxorg_HstdOpt getFirstAttr_const(haxorg_Cmd self, OrgContext* org_context, haxorg_HstdStr kind);
};

template <>
struct org::bind::c::VTable<haxorg_CmdCustomRaw, haxorg_CmdCustomRaw_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_CmdCustomText, haxorg_CmdCustomText_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Link, haxorg_Link_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_BlockComment, haxorg_BlockComment_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool isFootnoteDefinition_const(haxorg_Paragraph self, OrgContext* org_context);
  static haxorg_HstdOpt getFootnoteName_const(haxorg_Paragraph self, OrgContext* org_context);
  static bool hasAdmonition_const(haxorg_Paragraph self, OrgContext* org_context);
  static haxorg_HstdVec getAdmonitions_const(haxorg_Paragraph self, OrgContext* org_context);
  static haxorg_HstdVec getAdmonitionNodes_const(haxorg_Paragraph self, OrgContext* org_context);
  static bool hasTimestamp_const(haxorg_Paragraph self, OrgContext* org_context);
  static haxorg_HstdVec getTimestamps_const(haxorg_Paragraph self, OrgContext* org_context);
  static haxorg_HstdVec getTimestampNodes_const(haxorg_Paragraph self, OrgContext* org_context);
  static bool hasLeadHashtags_const(haxorg_Paragraph self, OrgContext* org_context);
  static haxorg_HstdVec getLeadHashtags_const(haxorg_Paragraph self, OrgContext* org_context);
  static haxorg_HstdVec getBody_const(haxorg_Paragraph self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_List, haxorg_List_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdVec getListAttrs_const(haxorg_List self, OrgContext* org_context, haxorg_HstdStr key);
  static haxorg_ListFormattingMode getListFormattingMode_const(haxorg_List self, OrgContext* org_context);
  static bool isDescriptionList_const(haxorg_List self, OrgContext* org_context);
  static bool isNumberedList_const(haxorg_List self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_HashTag, haxorg_HashTag_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_InlineFootnote, haxorg_InlineFootnote_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_InlineExport, haxorg_InlineExport_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Escaped, haxorg_Escaped_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Newline, haxorg_Newline_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Space, haxorg_Space_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Word, haxorg_Word_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_AtMention, haxorg_AtMention_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_RawText, haxorg_RawText_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Punctuation, haxorg_Punctuation_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Placeholder, haxorg_Placeholder_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_BigIdent, haxorg_BigIdent_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_TextTarget, haxorg_TextTarget_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ErrorSkipToken, haxorg_ErrorSkipToken_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Bold, haxorg_Bold_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Underline, haxorg_Underline_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Monospace, haxorg_Monospace_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_MarkQuote, haxorg_MarkQuote_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Verbatim, haxorg_Verbatim_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Italic, haxorg_Italic_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Strike, haxorg_Strike_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Par, haxorg_Par_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmd, haxorg_ImmCmd_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmCmd self, OrgContext* org_context, haxorg_ImmCmd other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdCustomRaw, haxorg_ImmCmdCustomRaw_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmCmdCustomRaw self, OrgContext* org_context, haxorg_ImmCmdCustomRaw other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdCustomText, haxorg_ImmCmdCustomText_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmCmdCustomText self, OrgContext* org_context, haxorg_ImmCmdCustomText other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmLink, haxorg_ImmLink_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmLink self, OrgContext* org_context, haxorg_ImmLink other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockComment, haxorg_ImmBlockComment_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmBlockComment self, OrgContext* org_context, haxorg_ImmBlockComment other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmParagraph, haxorg_ImmParagraph_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmParagraph self, OrgContext* org_context, haxorg_ImmParagraph other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmList, haxorg_ImmList_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmList self, OrgContext* org_context, haxorg_ImmList other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmHashTag, haxorg_ImmHashTag_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmHashTag self, OrgContext* org_context, haxorg_ImmHashTag other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmInlineFootnote, haxorg_ImmInlineFootnote_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmInlineFootnote self, OrgContext* org_context, haxorg_ImmInlineFootnote other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmInlineExport, haxorg_ImmInlineExport_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmInlineExport self, OrgContext* org_context, haxorg_ImmInlineExport other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmEscaped, haxorg_ImmEscaped_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmEscaped self, OrgContext* org_context, haxorg_ImmEscaped other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmNewline, haxorg_ImmNewline_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmNewline self, OrgContext* org_context, haxorg_ImmNewline other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmSpace, haxorg_ImmSpace_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmSpace self, OrgContext* org_context, haxorg_ImmSpace other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmWord, haxorg_ImmWord_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmWord self, OrgContext* org_context, haxorg_ImmWord other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmAtMention, haxorg_ImmAtMention_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmAtMention self, OrgContext* org_context, haxorg_ImmAtMention other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmRawText, haxorg_ImmRawText_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmRawText self, OrgContext* org_context, haxorg_ImmRawText other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmPunctuation, haxorg_ImmPunctuation_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmPunctuation self, OrgContext* org_context, haxorg_ImmPunctuation other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmPlaceholder, haxorg_ImmPlaceholder_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmPlaceholder self, OrgContext* org_context, haxorg_ImmPlaceholder other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBigIdent, haxorg_ImmBigIdent_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmBigIdent self, OrgContext* org_context, haxorg_ImmBigIdent other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmTextTarget, haxorg_ImmTextTarget_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmTextTarget self, OrgContext* org_context, haxorg_ImmTextTarget other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmErrorSkipToken, haxorg_ImmErrorSkipToken_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmErrorSkipToken self, OrgContext* org_context, haxorg_ImmErrorSkipToken other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBold, haxorg_ImmBold_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmBold self, OrgContext* org_context, haxorg_ImmBold other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmUnderline, haxorg_ImmUnderline_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmUnderline self, OrgContext* org_context, haxorg_ImmUnderline other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmMonospace, haxorg_ImmMonospace_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmMonospace self, OrgContext* org_context, haxorg_ImmMonospace other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmMarkQuote, haxorg_ImmMarkQuote_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmMarkQuote self, OrgContext* org_context, haxorg_ImmMarkQuote other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmVerbatim, haxorg_ImmVerbatim_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmVerbatim self, OrgContext* org_context, haxorg_ImmVerbatim other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmItalic, haxorg_ImmItalic_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmItalic self, OrgContext* org_context, haxorg_ImmItalic other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmStrike, haxorg_ImmStrike_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmStrike self, OrgContext* org_context, haxorg_ImmStrike other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmPar, haxorg_ImmPar_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmPar self, OrgContext* org_context, haxorg_ImmPar other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterStmtAPI, haxorg_ImmAdapterStmtAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterSubtreeAPI, haxorg_ImmAdapterSubtreeAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterNoNodeAPI, haxorg_ImmAdapterNoNodeAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterAttrAPI, haxorg_ImmAdapterAttrAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterAttrListAPI, haxorg_ImmAdapterAttrListAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterAttrsAPI, haxorg_ImmAdapterAttrsAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterErrorItemAPI, haxorg_ImmAdapterErrorItemAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterErrorGroupAPI, haxorg_ImmAdapterErrorGroupAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterErrorSkipGroupAPI, haxorg_ImmAdapterErrorSkipGroupAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterErrorSkipTokenAPI, haxorg_ImmAdapterErrorSkipTokenAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterStmtListAPI, haxorg_ImmAdapterStmtListAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterEmptyAPI, haxorg_ImmAdapterEmptyAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterInlineAPI, haxorg_ImmAdapterInlineAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterTimeAPI, haxorg_ImmAdapterTimeAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterTimeRangeAPI, haxorg_ImmAdapterTimeRangeAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterMacroAPI, haxorg_ImmAdapterMacroAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterSymbolAPI, haxorg_ImmAdapterSymbolAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterLeafAPI, haxorg_ImmAdapterLeafAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterMarkupAPI, haxorg_ImmAdapterMarkupAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterLatexAPI, haxorg_ImmAdapterLatexAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterSubtreeLogAPI, haxorg_ImmAdapterSubtreeLogAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterColonExampleAPI, haxorg_ImmAdapterColonExampleAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterCallAPI, haxorg_ImmAdapterCallAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterFileAPI, haxorg_ImmAdapterFileAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterDirectoryAPI, haxorg_ImmAdapterDirectoryAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_StdOptional getFsSubnode_const(haxorg_ImmAdapterDirectoryAPI self, OrgContext* org_context, haxorg_HstdStr name, bool withPath);
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterSymlinkAPI, haxorg_ImmAdapterSymlinkAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterDocumentFragmentAPI, haxorg_ImmAdapterDocumentFragmentAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterCriticMarkupAPI, haxorg_ImmAdapterCriticMarkupAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterListItemAPI, haxorg_ImmAdapterListItemAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterDocumentOptionsAPI, haxorg_ImmAdapterDocumentOptionsAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterDocumentAPI, haxorg_ImmAdapterDocumentAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterFileTargetAPI, haxorg_ImmAdapterFileTargetAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterTextSeparatorAPI, haxorg_ImmAdapterTextSeparatorAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterCmdIncludeAPI, haxorg_ImmAdapterCmdIncludeAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterDocumentGroupAPI, haxorg_ImmAdapterDocumentGroupAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Block, haxorg_Block_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_LineCommand, haxorg_LineCommand_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_CmdCreator, haxorg_CmdCreator_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_CmdAuthor, haxorg_CmdAuthor_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_CmdEmail, haxorg_CmdEmail_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_CmdLanguage, haxorg_CmdLanguage_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_CmdCustomArgs, haxorg_CmdCustomArgs_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_CmdTblfm, haxorg_CmdTblfm_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Cell, haxorg_Cell_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Row, haxorg_Row_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlock, haxorg_ImmBlock_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmBlock self, OrgContext* org_context, haxorg_ImmBlock other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmLineCommand, haxorg_ImmLineCommand_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmLineCommand self, OrgContext* org_context, haxorg_ImmLineCommand other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdCreator, haxorg_ImmCmdCreator_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmCmdCreator self, OrgContext* org_context, haxorg_ImmCmdCreator other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdAuthor, haxorg_ImmCmdAuthor_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmCmdAuthor self, OrgContext* org_context, haxorg_ImmCmdAuthor other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdEmail, haxorg_ImmCmdEmail_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmCmdEmail self, OrgContext* org_context, haxorg_ImmCmdEmail other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdLanguage, haxorg_ImmCmdLanguage_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmCmdLanguage self, OrgContext* org_context, haxorg_ImmCmdLanguage other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdCustomArgs, haxorg_ImmCmdCustomArgs_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmCmdCustomArgs self, OrgContext* org_context, haxorg_ImmCmdCustomArgs other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdTblfm, haxorg_ImmCmdTblfm_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmCmdTblfm self, OrgContext* org_context, haxorg_ImmCmdTblfm other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCell, haxorg_ImmCell_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmCell self, OrgContext* org_context, haxorg_ImmCell other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmRow, haxorg_ImmRow_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmRow self, OrgContext* org_context, haxorg_ImmRow other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterCmdAPI, haxorg_ImmAdapterCmdAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterCmdCustomRawAPI, haxorg_ImmAdapterCmdCustomRawAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterCmdCustomTextAPI, haxorg_ImmAdapterCmdCustomTextAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterLinkAPI, haxorg_ImmAdapterLinkAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterBlockCommentAPI, haxorg_ImmAdapterBlockCommentAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterParagraphAPI, haxorg_ImmAdapterParagraphAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterListAPI, haxorg_ImmAdapterListAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmStmtAdapter, haxorg_ImmStmtAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmVec getAttached_const(haxorg_ImmStmtAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int getLevel_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context);
  static haxorg_HstdOpt getTreeId_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context);
  static haxorg_HstdOpt getTodo_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context);
  static haxorg_HstdOpt getCompletion_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context);
  static haxorg_HstdOpt getDescription_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context);
  static haxorg_ImmVec getTags_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context);
  static haxorg_ImmAdapter getTitle_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context);
  static haxorg_ImmVec getLogbook_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context);
  static haxorg_ImmVec getProperties_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context);
  static haxorg_HstdOpt getClosed_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context);
  static haxorg_HstdOpt getDeadline_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context);
  static haxorg_HstdOpt getScheduled_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context);
  static bool getIsComment_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context);
  static bool getIsArchived_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context);
  static haxorg_HstdOpt getPriority_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmNoNodeAdapter, haxorg_ImmNoNodeAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmErrorItemAdapter, haxorg_ImmErrorItemAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_OrgDiagnostics getDiag_const(haxorg_ImmErrorItemAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmErrorGroupAdapter, haxorg_ImmErrorGroupAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmVec getDiagnostics_const(haxorg_ImmErrorGroupAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmErrorSkipGroupAdapter, haxorg_ImmErrorSkipGroupAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmVec getSkipped_const(haxorg_ImmErrorSkipGroupAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmErrorSkipTokenAdapter, haxorg_ImmErrorSkipTokenAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmStmtListAdapter, haxorg_ImmStmtListAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmEmptyAdapter, haxorg_ImmEmptyAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterHashTagAPI, haxorg_ImmAdapterHashTagAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterInlineFootnoteAPI, haxorg_ImmAdapterInlineFootnoteAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterSubtreeCompletionAPI, haxorg_ImmAdapterSubtreeCompletionAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmInlineAdapter, haxorg_ImmInlineAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmTimeAdapter, haxorg_ImmTimeAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool getIsActive_const(haxorg_ImmTimeAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmTimeRangeAdapter, haxorg_ImmTimeRangeAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapter getFrom_const(haxorg_ImmTimeRangeAdapter self, OrgContext* org_context);
  static haxorg_ImmAdapter getTo_const(haxorg_ImmTimeRangeAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmMacroAdapter, haxorg_ImmMacroAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getName_const(haxorg_ImmMacroAdapter self, OrgContext* org_context);
  static haxorg_AttrGroup getAttrs_const(haxorg_ImmMacroAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmSymbolAdapter, haxorg_ImmSymbolAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getName_const(haxorg_ImmSymbolAdapter self, OrgContext* org_context);
  static haxorg_ImmVec getParameters_const(haxorg_ImmSymbolAdapter self, OrgContext* org_context);
  static haxorg_ImmVec getPositional_const(haxorg_ImmSymbolAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterEscapedAPI, haxorg_ImmAdapterEscapedAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterNewlineAPI, haxorg_ImmAdapterNewlineAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterSpaceAPI, haxorg_ImmAdapterSpaceAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterWordAPI, haxorg_ImmAdapterWordAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterAtMentionAPI, haxorg_ImmAdapterAtMentionAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterRawTextAPI, haxorg_ImmAdapterRawTextAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterPunctuationAPI, haxorg_ImmAdapterPunctuationAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterPlaceholderAPI, haxorg_ImmAdapterPlaceholderAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterBigIdentAPI, haxorg_ImmAdapterBigIdentAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterTextTargetAPI, haxorg_ImmAdapterTextTargetAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmLeafAdapter, haxorg_ImmLeafAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getText_const(haxorg_ImmLeafAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterBoldAPI, haxorg_ImmAdapterBoldAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterUnderlineAPI, haxorg_ImmAdapterUnderlineAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterMonospaceAPI, haxorg_ImmAdapterMonospaceAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterMarkQuoteAPI, haxorg_ImmAdapterMarkQuoteAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterRadioTargetAPI, haxorg_ImmAdapterRadioTargetAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterVerbatimAPI, haxorg_ImmAdapterVerbatimAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterItalicAPI, haxorg_ImmAdapterItalicAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterStrikeAPI, haxorg_ImmAdapterStrikeAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterParAPI, haxorg_ImmAdapterParAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmMarkupAdapter, haxorg_ImmMarkupAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmLatexAdapter, haxorg_ImmLatexAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmSubtreeLogAdapter, haxorg_ImmSubtreeLogAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_SubtreeLogHead getHead_const(haxorg_ImmSubtreeLogAdapter self, OrgContext* org_context);
  static haxorg_HstdOpt getDesc_const(haxorg_ImmSubtreeLogAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmColonExampleAdapter, haxorg_ImmColonExampleAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmCallAdapter, haxorg_ImmCallAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getName_const(haxorg_ImmCallAdapter self, OrgContext* org_context);
  static haxorg_AttrGroup getAttrs_const(haxorg_ImmCallAdapter self, OrgContext* org_context);
  static bool getIsCommand_const(haxorg_ImmCallAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmFileAdapter, haxorg_ImmFileAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getRelPath_const(haxorg_ImmFileAdapter self, OrgContext* org_context);
  static haxorg_HstdStr getAbsPath_const(haxorg_ImmFileAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmDirectoryAdapter, haxorg_ImmDirectoryAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getRelPath_const(haxorg_ImmDirectoryAdapter self, OrgContext* org_context);
  static haxorg_HstdStr getAbsPath_const(haxorg_ImmDirectoryAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmSymlinkAdapter, haxorg_ImmSymlinkAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool getIsDirectory_const(haxorg_ImmSymlinkAdapter self, OrgContext* org_context);
  static haxorg_HstdStr getAbsPath_const(haxorg_ImmSymlinkAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmDocumentFragmentAdapter, haxorg_ImmDocumentFragmentAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int getBaseLine_const(haxorg_ImmDocumentFragmentAdapter self, OrgContext* org_context);
  static int getBaseCol_const(haxorg_ImmDocumentFragmentAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCriticMarkupAdapter, haxorg_ImmCriticMarkupAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmCriticMarkupKind getKind_const(haxorg_ImmCriticMarkupAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmListItemAdapter, haxorg_ImmListItemAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_CheckboxState getCheckbox_const(haxorg_ImmListItemAdapter self, OrgContext* org_context);
  static haxorg_HstdOpt getHeader_const(haxorg_ImmListItemAdapter self, OrgContext* org_context);
  static haxorg_HstdOpt getBullet_const(haxorg_ImmListItemAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_InitialSubtreeVisibility getInitialVisibility_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context);
  static haxorg_ImmVec getProperties_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context);
  static haxorg_DocumentExportConfig getExportConfig_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context);
  static haxorg_HstdOpt getFixedWidthSections_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context);
  static haxorg_HstdOpt getStartupIndented_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context);
  static haxorg_HstdOpt getCategory_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context);
  static haxorg_HstdOpt getSetupfile_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context);
  static haxorg_HstdOpt getMaxSubtreeLevelExport_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context);
  static haxorg_HstdOpt getColumns_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context);
  static haxorg_ImmVec getTodoKeywords_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context);
  static haxorg_ImmVec getDoneKeywords_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdOpt getTitle_const(haxorg_ImmDocumentAdapter self, OrgContext* org_context);
  static haxorg_HstdOpt getAuthor_const(haxorg_ImmDocumentAdapter self, OrgContext* org_context);
  static haxorg_HstdOpt getCreator_const(haxorg_ImmDocumentAdapter self, OrgContext* org_context);
  static haxorg_ImmVec getFiletags_const(haxorg_ImmDocumentAdapter self, OrgContext* org_context);
  static haxorg_HstdOpt getEmail_const(haxorg_ImmDocumentAdapter self, OrgContext* org_context);
  static haxorg_ImmVec getLanguage_const(haxorg_ImmDocumentAdapter self, OrgContext* org_context);
  static haxorg_ImmAdapter getOptions_const(haxorg_ImmDocumentAdapter self, OrgContext* org_context);
  static haxorg_HstdOpt getExportFileName_const(haxorg_ImmDocumentAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getPath_const(haxorg_ImmFileTargetAdapter self, OrgContext* org_context);
  static haxorg_HstdOpt getLine_const(haxorg_ImmFileTargetAdapter self, OrgContext* org_context);
  static haxorg_HstdOpt getSearchTarget_const(haxorg_ImmFileTargetAdapter self, OrgContext* org_context);
  static bool getRestrictToHeadlines_const(haxorg_ImmFileTargetAdapter self, OrgContext* org_context);
  static haxorg_HstdOpt getTargetId_const(haxorg_ImmFileTargetAdapter self, OrgContext* org_context);
  static haxorg_HstdOpt getRegexp_const(haxorg_ImmFileTargetAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmTextSeparatorAdapter, haxorg_ImmTextSeparatorAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdIncludeAdapter, haxorg_ImmCmdIncludeAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getPath_const(haxorg_ImmCmdIncludeAdapter self, OrgContext* org_context);
  static haxorg_HstdOpt getFirstLine_const(haxorg_ImmCmdIncludeAdapter self, OrgContext* org_context);
  static haxorg_HstdOpt getLastLine_const(haxorg_ImmCmdIncludeAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmDocumentGroupAdapter, haxorg_ImmDocumentGroupAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_BlockCenter, haxorg_BlockCenter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_BlockQuote, haxorg_BlockQuote_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_BlockVerse, haxorg_BlockVerse_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_BlockDynamicFallback, haxorg_BlockDynamicFallback_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_BlockExample, haxorg_BlockExample_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_BlockExport, haxorg_BlockExport_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdOpt getPlacement_const(haxorg_BlockExport self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_BlockAdmonition, haxorg_BlockAdmonition_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_BlockCodeEvalResult, haxorg_BlockCodeEvalResult_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_BlockCode, haxorg_BlockCode_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdOpt getVariable_const(haxorg_BlockCode self, OrgContext* org_context, haxorg_HstdStr varname);
};

template <>
struct org::bind::c::VTable<haxorg_Table, haxorg_Table_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Attached, haxorg_Attached_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockCenter, haxorg_ImmBlockCenter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmBlockCenter self, OrgContext* org_context, haxorg_ImmBlockCenter other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockQuote, haxorg_ImmBlockQuote_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmBlockQuote self, OrgContext* org_context, haxorg_ImmBlockQuote other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockVerse, haxorg_ImmBlockVerse_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmBlockVerse self, OrgContext* org_context, haxorg_ImmBlockVerse other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockDynamicFallback, haxorg_ImmBlockDynamicFallback_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmBlockDynamicFallback self, OrgContext* org_context, haxorg_ImmBlockDynamicFallback other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockExample, haxorg_ImmBlockExample_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmBlockExample self, OrgContext* org_context, haxorg_ImmBlockExample other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockExport, haxorg_ImmBlockExport_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmBlockExport self, OrgContext* org_context, haxorg_ImmBlockExport other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockAdmonition, haxorg_ImmBlockAdmonition_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmBlockAdmonition self, OrgContext* org_context, haxorg_ImmBlockAdmonition other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockCodeEvalResult, haxorg_ImmBlockCodeEvalResult_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmBlockCodeEvalResult self, OrgContext* org_context, haxorg_ImmBlockCodeEvalResult other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockCode, haxorg_ImmBlockCode_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmBlockCode self, OrgContext* org_context, haxorg_ImmBlockCode other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmTable, haxorg_ImmTable_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmTable self, OrgContext* org_context, haxorg_ImmTable other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmAttached, haxorg_ImmAttached_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmAttached self, OrgContext* org_context, haxorg_ImmAttached other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterLineCommandAPI, haxorg_ImmAdapterLineCommandAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterCmdCustomArgsAPI, haxorg_ImmAdapterCmdCustomArgsAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterCmdCreatorAPI, haxorg_ImmAdapterCmdCreatorAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterCmdAuthorAPI, haxorg_ImmAdapterCmdAuthorAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterCmdEmailAPI, haxorg_ImmAdapterCmdEmailAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterCmdLanguageAPI, haxorg_ImmAdapterCmdLanguageAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterCmdTblfmAPI, haxorg_ImmAdapterCmdTblfmAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterBlockAPI, haxorg_ImmAdapterBlockAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterCellAPI, haxorg_ImmAdapterCellAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterRowAPI, haxorg_ImmAdapterRowAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdAdapter, haxorg_ImmCmdAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_AttrGroup getAttrs_const(haxorg_ImmCmdAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdCustomRawAdapter, haxorg_ImmCmdCustomRawAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getName_const(haxorg_ImmCmdCustomRawAdapter self, OrgContext* org_context);
  static bool getIsAttached_const(haxorg_ImmCmdCustomRawAdapter self, OrgContext* org_context);
  static haxorg_HstdStr getText_const(haxorg_ImmCmdCustomRawAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdCustomTextAdapter, haxorg_ImmCmdCustomTextAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getName_const(haxorg_ImmCmdCustomTextAdapter self, OrgContext* org_context);
  static bool getIsAttached_const(haxorg_ImmCmdCustomTextAdapter self, OrgContext* org_context);
  static haxorg_ImmAdapter getText_const(haxorg_ImmCmdCustomTextAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmLinkAdapter, haxorg_ImmLinkAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdOpt getDescription_const(haxorg_ImmLinkAdapter self, OrgContext* org_context);
  static haxorg_LinkTarget getTarget_const(haxorg_ImmLinkAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockCommentAdapter, haxorg_ImmBlockCommentAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmParagraphAdapter, haxorg_ImmParagraphAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmListAdapter, haxorg_ImmListAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmHashTagAdapter, haxorg_ImmHashTagAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HashTagText getText_const(haxorg_ImmHashTagAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmInlineFootnoteAdapter, haxorg_ImmInlineFootnoteAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getTag_const(haxorg_ImmInlineFootnoteAdapter self, OrgContext* org_context);
  static haxorg_HstdOpt getDefinition_const(haxorg_ImmInlineFootnoteAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmEscapedAdapter, haxorg_ImmEscapedAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmNewlineAdapter, haxorg_ImmNewlineAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmSpaceAdapter, haxorg_ImmSpaceAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmWordAdapter, haxorg_ImmWordAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAtMentionAdapter, haxorg_ImmAtMentionAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmRawTextAdapter, haxorg_ImmRawTextAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmPunctuationAdapter, haxorg_ImmPunctuationAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmPlaceholderAdapter, haxorg_ImmPlaceholderAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmBigIdentAdapter, haxorg_ImmBigIdentAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmTextTargetAdapter, haxorg_ImmTextTargetAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmBoldAdapter, haxorg_ImmBoldAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmUnderlineAdapter, haxorg_ImmUnderlineAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmMonospaceAdapter, haxorg_ImmMonospaceAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmMarkQuoteAdapter, haxorg_ImmMarkQuoteAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmRadioTargetAdapter, haxorg_ImmRadioTargetAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmVec getWords_const(haxorg_ImmRadioTargetAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmVerbatimAdapter, haxorg_ImmVerbatimAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmItalicAdapter, haxorg_ImmItalicAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmStrikeAdapter, haxorg_ImmStrikeAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmParAdapter, haxorg_ImmParAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_CmdCaption, haxorg_CmdCaption_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_CmdColumns, haxorg_CmdColumns_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_CmdName, haxorg_CmdName_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_CmdCall, haxorg_CmdCall_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_CmdAttr, haxorg_CmdAttr_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_CmdExport, haxorg_CmdExport_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdCaption, haxorg_ImmCmdCaption_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmCmdCaption self, OrgContext* org_context, haxorg_ImmCmdCaption other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdColumns, haxorg_ImmCmdColumns_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmCmdColumns self, OrgContext* org_context, haxorg_ImmCmdColumns other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdName, haxorg_ImmCmdName_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmCmdName self, OrgContext* org_context, haxorg_ImmCmdName other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdCall, haxorg_ImmCmdCall_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmCmdCall self, OrgContext* org_context, haxorg_ImmCmdCall other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdAttr, haxorg_ImmCmdAttr_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmCmdAttr self, OrgContext* org_context, haxorg_ImmCmdAttr other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdExport, haxorg_ImmCmdExport_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(haxorg_ImmCmdExport self, OrgContext* org_context, haxorg_ImmCmdExport other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterAttachedAPI, haxorg_ImmAdapterAttachedAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmLineCommandAdapter, haxorg_ImmLineCommandAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdCustomArgsAdapter, haxorg_ImmCmdCustomArgsAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getName_const(haxorg_ImmCmdCustomArgsAdapter self, OrgContext* org_context);
  static bool getIsAttached_const(haxorg_ImmCmdCustomArgsAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdCreatorAdapter, haxorg_ImmCmdCreatorAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapter getText_const(haxorg_ImmCmdCreatorAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdAuthorAdapter, haxorg_ImmCmdAuthorAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapter getText_const(haxorg_ImmCmdAuthorAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdEmailAdapter, haxorg_ImmCmdEmailAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getText_const(haxorg_ImmCmdEmailAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdLanguageAdapter, haxorg_ImmCmdLanguageAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getText_const(haxorg_ImmCmdLanguageAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdTblfmAdapter, haxorg_ImmCmdTblfmAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Tblfm getExpr_const(haxorg_ImmCmdTblfmAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterBlockCenterAPI, haxorg_ImmAdapterBlockCenterAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterBlockQuoteAPI, haxorg_ImmAdapterBlockQuoteAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterBlockVerseAPI, haxorg_ImmAdapterBlockVerseAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterBlockExampleAPI, haxorg_ImmAdapterBlockExampleAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterInlineExportAPI, haxorg_ImmAdapterInlineExportAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterCmdExportAPI, haxorg_ImmAdapterCmdExportAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterBlockExportAPI, haxorg_ImmAdapterBlockExportAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterBlockDynamicFallbackAPI, haxorg_ImmAdapterBlockDynamicFallbackAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterBlockAdmonitionAPI, haxorg_ImmAdapterBlockAdmonitionAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterBlockCodeEvalResultAPI, haxorg_ImmAdapterBlockCodeEvalResultAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterBlockCodeAPI, haxorg_ImmAdapterBlockCodeAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterTableAPI, haxorg_ImmAdapterTableAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockAdapter, haxorg_ImmBlockAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmCellAdapter, haxorg_ImmCellAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool getIsBlock_const(haxorg_ImmCellAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmRowAdapter, haxorg_ImmRowAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmVec getCells_const(haxorg_ImmRowAdapter self, OrgContext* org_context);
  static bool getIsBlock_const(haxorg_ImmRowAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterCmdCaptionAPI, haxorg_ImmAdapterCmdCaptionAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterCmdColumnsAPI, haxorg_ImmAdapterCmdColumnsAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterCmdNameAPI, haxorg_ImmAdapterCmdNameAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterCmdCallAPI, haxorg_ImmAdapterCmdCallAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterCmdResultsAPI, haxorg_ImmAdapterCmdResultsAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterCmdAttrAPI, haxorg_ImmAdapterCmdAttrAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmAttachedAdapter, haxorg_ImmAttachedAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockCenterAdapter, haxorg_ImmBlockCenterAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockQuoteAdapter, haxorg_ImmBlockQuoteAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockVerseAdapter, haxorg_ImmBlockVerseAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockExampleAdapter, haxorg_ImmBlockExampleAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmInlineExportAdapter, haxorg_ImmInlineExportAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getExporter_const(haxorg_ImmInlineExportAdapter self, OrgContext* org_context);
  static haxorg_HstdStr getContent_const(haxorg_ImmInlineExportAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdExportAdapter, haxorg_ImmCmdExportAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getExporter_const(haxorg_ImmCmdExportAdapter self, OrgContext* org_context);
  static haxorg_HstdStr getContent_const(haxorg_ImmCmdExportAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockExportAdapter, haxorg_ImmBlockExportAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getExporter_const(haxorg_ImmBlockExportAdapter self, OrgContext* org_context);
  static haxorg_HstdStr getContent_const(haxorg_ImmBlockExportAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockDynamicFallbackAdapter, haxorg_ImmBlockDynamicFallbackAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getName_const(haxorg_ImmBlockDynamicFallbackAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockAdmonitionAdapter, haxorg_ImmBlockAdmonitionAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockCodeEvalResultAdapter, haxorg_ImmBlockCodeEvalResultAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmVec getRaw_const(haxorg_ImmBlockCodeEvalResultAdapter self, OrgContext* org_context);
  static haxorg_ImmAdapter getNode_const(haxorg_ImmBlockCodeEvalResultAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockCodeAdapter, haxorg_ImmBlockCodeAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdOpt getLang_const(haxorg_ImmBlockCodeAdapter self, OrgContext* org_context);
  static haxorg_ImmVec getResult_const(haxorg_ImmBlockCodeAdapter self, OrgContext* org_context);
  static haxorg_ImmVec getLines_const(haxorg_ImmBlockCodeAdapter self, OrgContext* org_context);
  static haxorg_AttrGroup getSwitches_const(haxorg_ImmBlockCodeAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmTableAdapter, haxorg_ImmTableAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmVec getRows_const(haxorg_ImmTableAdapter self, OrgContext* org_context);
  static bool getIsBlock_const(haxorg_ImmTableAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdCaptionAdapter, haxorg_ImmCmdCaptionAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapter getText_const(haxorg_ImmCmdCaptionAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdColumnsAdapter, haxorg_ImmCmdColumnsAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ColumnView getView_const(haxorg_ImmCmdColumnsAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdNameAdapter, haxorg_ImmCmdNameAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getName_const(haxorg_ImmCmdNameAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getName_const(haxorg_ImmCmdCallAdapter self, OrgContext* org_context);
  static haxorg_HstdOpt getFileName_const(haxorg_ImmCmdCallAdapter self, OrgContext* org_context);
  static haxorg_AttrGroup getInsideHeaderAttrs_const(haxorg_ImmCmdCallAdapter self, OrgContext* org_context);
  static haxorg_AttrGroup getCallAttrs_const(haxorg_ImmCmdCallAdapter self, OrgContext* org_context);
  static haxorg_AttrGroup getEndHeaderAttrs_const(haxorg_ImmCmdCallAdapter self, OrgContext* org_context);
  static haxorg_ImmVec getResult_const(haxorg_ImmCmdCallAdapter self, OrgContext* org_context);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdAttrAdapter, haxorg_ImmCmdAttrAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getTarget_const(haxorg_ImmCmdAttrAdapter self, OrgContext* org_context);
};

/* clang-format on */
