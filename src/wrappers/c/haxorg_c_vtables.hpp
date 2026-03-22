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
  static haxorg_UserTimeBreakdown getBreakdown_const(OrgContext* org_context, haxorg_UserTime self);
  static haxorg_StdString format_const(OrgContext* org_context, haxorg_UserTime self);
  static int64_t getTimeDeltaSeconds_const(OrgContext* org_context, haxorg_UserTime self, haxorg_UserTime other);
  static int64_t toUnixTimestamp_const(OrgContext* org_context, haxorg_UserTime self);
};

template <>
struct org::bind::c::VTable<haxorg_ParseSourceFileId, haxorg_ParseSourceFileId_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ParseSourceManager, haxorg_ParseSourceManager_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_StdString getPath_const(OrgContext* org_context, haxorg_ParseSourceManager self, haxorg_ParseSourceFileId id);
  static haxorg_ParseSourceFileId getId_const(OrgContext* org_context, haxorg_ParseSourceManager self, haxorg_StdString path);
  static haxorg_StdString getSourceContent_const(OrgContext* org_context, haxorg_ParseSourceManager self, haxorg_ParseSourceFileId id);
  static haxorg_StdString getContentTextForPath_const(OrgContext* org_context, haxorg_ParseSourceManager self, haxorg_StdString path);
  static haxorg_ParseSourceFileId addSource(OrgContext* org_context, haxorg_ParseSourceManager self, haxorg_StdString path, haxorg_StdString content);
};

template <>
struct org::bind::c::VTable<haxorg_ParseSourceLoc, haxorg_ParseSourceLoc_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_OrgJsonKind getKind_const(OrgContext* org_context, haxorg_OrgJson self);
  static haxorg_StdString getJsonString_const(OrgContext* org_context, haxorg_OrgJson self);
  static haxorg_OrgJson atIndex_const(OrgContext* org_context, haxorg_OrgJson self, int idx);
  static haxorg_OrgJson atField_const(OrgContext* org_context, haxorg_OrgJson self, haxorg_StdString name);
  static haxorg_StdString getString_const(OrgContext* org_context, haxorg_OrgJson self);
  static haxorg_OrgJson getField_const(OrgContext* org_context, haxorg_OrgJson self, haxorg_StdString name);
  static haxorg_OrgJson getItem_const(OrgContext* org_context, haxorg_OrgJson self, int index);
  static int getInt_const(OrgContext* org_context, haxorg_OrgJson self);
  static bool getBool_const(OrgContext* org_context, haxorg_OrgJson self);
  static haxorg_HstdVec getArray_const(OrgContext* org_context, haxorg_OrgJson self);
  static haxorg_StdString dump_const(OrgContext* org_context, haxorg_OrgJson self, int indent);
};

template <>
struct org::bind::c::VTable<haxorg_Org, haxorg_Org_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_OrgSemKind getKind_const(OrgContext* org_context, haxorg_Org self);
  static void push_back(OrgContext* org_context, haxorg_Org self, haxorg_SemId sub);
  static int size_const(OrgContext* org_context, haxorg_Org self);
  static void insert(OrgContext* org_context, haxorg_Org self, int pos, haxorg_SemId node);
  static haxorg_SemId at_const(OrgContext* org_context, haxorg_Org self, int idx);
  static bool is_const(OrgContext* org_context, haxorg_Org self, haxorg_OrgSemKind kind);
};

template <>
struct org::bind::c::VTable<haxorg_OperationsTracer, haxorg_OperationsTracer_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static void setTraceFileStr(OrgContext* org_context, haxorg_OperationsTracer self, haxorg_StdString outfile, bool overwrite);
  static void sendMessage(OrgContext* org_context, haxorg_OperationsTracer self, haxorg_StdString value, haxorg_StdString function, int line, haxorg_StdString file);
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
  static haxorg_Cache getDiagnosticStrings(OrgContext* org_context, haxorg_ParseContext self);
  static haxorg_ParseSourceFileId addSource_const(OrgContext* org_context, haxorg_ParseContext self, haxorg_StdString path, haxorg_StdString content);
  static haxorg_SemId parseFileOpts(OrgContext* org_context, haxorg_ParseContext self, haxorg_StdString file, haxorg_OrgParseParameters opts);
  static haxorg_SemId parseFile(OrgContext* org_context, haxorg_ParseContext self, haxorg_StdString file);
  static haxorg_SemId parseString(OrgContext* org_context, haxorg_ParseContext self, haxorg_StdString text, haxorg_StdString file_name);
  static haxorg_SemId parseStringOpts(OrgContext* org_context, haxorg_ParseContext self, haxorg_StdString text, haxorg_StdString file_name, haxorg_OrgParseParameters opts);
  static haxorg_StdOptional parseDirectory(OrgContext* org_context, haxorg_ParseContext self, haxorg_StdString path);
  static haxorg_StdOptional parseDirectoryOpts(OrgContext* org_context, haxorg_ParseContext self, haxorg_StdString path, haxorg_OrgDirectoryParseParameters opts);
  static haxorg_SemId parseFileWithIncludes(OrgContext* org_context, haxorg_ParseContext self, haxorg_StdString file, haxorg_OrgDirectoryParseParameters opts);
  static haxorg_HstdVec collectDiagnostics(OrgContext* org_context, haxorg_ParseContext self, haxorg_SemId tree, haxorg_Cache cache);
  static haxorg_HstdVec collectErrorNodes(OrgContext* org_context, haxorg_ParseContext self, haxorg_SemId tree);
};

template <>
struct org::bind::c::VTable<haxorg_ImmReflFieldId, haxorg_ImmReflFieldId_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getName_const(OrgContext* org_context, haxorg_ImmReflFieldId self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmId, haxorg_ImmId_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_OrgSemKind getKind_const(OrgContext* org_context, haxorg_ImmId self);
  static bool is_const(OrgContext* org_context, haxorg_ImmId self, haxorg_OrgSemKind kind);
  static haxorg_ImmIdNodeIdxT getNodeIndex_const(OrgContext* org_context, haxorg_ImmId self);
  static haxorg_StdString getReadableId_const(OrgContext* org_context, haxorg_ImmId self);
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
  static bool empty_const(OrgContext* org_context, haxorg_ImmPath self);
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
  static haxorg_ImmAstVersion addRoot(OrgContext* org_context, haxorg_ImmAstContext self, haxorg_SemId data);
  static haxorg_ImmAstVersion getEmptyVersion(OrgContext* org_context, haxorg_ImmAstContext self);
  static haxorg_SemId get(OrgContext* org_context, haxorg_ImmAstContext self, haxorg_ImmId id);
};

template <>
struct org::bind::c::VTable<haxorg_ImmAstVersion, haxorg_ImmAstVersion_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmId getRoot_const(OrgContext* org_context, haxorg_ImmAstVersion self);
  static haxorg_ImmAdapter getRootAdapter_const(OrgContext* org_context, haxorg_ImmAstVersion self);
  static haxorg_ImmAstContext getContext_const(OrgContext* org_context, haxorg_ImmAstVersion self);
  static haxorg_ImmAstReplaceEpoch getEpoch_const(OrgContext* org_context, haxorg_ImmAstVersion self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_ImmAdapter self);
  static bool isNil_const(OrgContext* org_context, haxorg_ImmAdapter self);
  static bool isRoot_const(OrgContext* org_context, haxorg_ImmAdapter self);
  static haxorg_OrgSemKind getKind_const(OrgContext* org_context, haxorg_ImmAdapter self);
  static haxorg_ImmUniqId uniq_const(OrgContext* org_context, haxorg_ImmAdapter self);
  static haxorg_StdString treeReprString_const(OrgContext* org_context, haxorg_ImmAdapter self);
  static haxorg_StdString treeReprStringOpts_const(OrgContext* org_context, haxorg_ImmAdapter self, haxorg_ImmAdapterTreeReprConf conf);
  static bool isDirectParentOf_const(OrgContext* org_context, haxorg_ImmAdapter self, haxorg_ImmAdapter other);
  static bool isIndirectParentOf_const(OrgContext* org_context, haxorg_ImmAdapter self, haxorg_ImmAdapter other);
  static bool isSubnodeOf_const(OrgContext* org_context, haxorg_ImmAdapter self, haxorg_ImmAdapter other);
  static haxorg_StdOptional getParent_const(OrgContext* org_context, haxorg_ImmAdapter self);
  static int getSelfIndex_const(OrgContext* org_context, haxorg_ImmAdapter self);
  static haxorg_ImmAdapter atPathStep_const(OrgContext* org_context, haxorg_ImmAdapter self, haxorg_ImmId id, haxorg_ImmPathStep idx);
  static haxorg_ImmAdapter atField_const(OrgContext* org_context, haxorg_ImmAdapter self, haxorg_ImmReflFieldId field);
  static haxorg_ImmAdapter atIndex_const(OrgContext* org_context, haxorg_ImmAdapter self, int idx, bool withPath);
  static haxorg_ImmAdapter atPath_const(OrgContext* org_context, haxorg_ImmAdapter self, haxorg_HstdVec path, bool withPath);
  static bool is_const(OrgContext* org_context, haxorg_ImmAdapter self, haxorg_OrgSemKind kind);
  static haxorg_HstdVec sub_const(OrgContext* org_context, haxorg_ImmAdapter self, bool withPath);
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
  static haxorg_SemId getParent_const(OrgContext* org_context, haxorg_AstTrackingPath self, int offset);
  static haxorg_SemId getNode_const(OrgContext* org_context, haxorg_AstTrackingPath self);
};

template <>
struct org::bind::c::VTable<haxorg_AstTrackingAlternatives, haxorg_AstTrackingAlternatives_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdVec getAllNodes_const(OrgContext* org_context, haxorg_AstTrackingAlternatives self);
  static haxorg_SemId getNode_const(OrgContext* org_context, haxorg_AstTrackingAlternatives self);
};

template <>
struct org::bind::c::VTable<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_AstTrackingGroupRadioTarget getRadioTargetConst_const(OrgContext* org_context, haxorg_AstTrackingGroup self);
  static haxorg_AstTrackingGroupTrackedHashtag getTrackedHashtagConst_const(OrgContext* org_context, haxorg_AstTrackingGroup self);
  static haxorg_AstTrackingGroupTrackedHashtag getTrackedHashtagMut(OrgContext* org_context, haxorg_AstTrackingGroup self);
  static haxorg_AstTrackingGroupSingle getSingleConst_const(OrgContext* org_context, haxorg_AstTrackingGroup self);
  static haxorg_AstTrackingGroupRadioTarget getRadioTargetMut(OrgContext* org_context, haxorg_AstTrackingGroup self);
  static haxorg_AstTrackingGroupSingle getSingleMut(OrgContext* org_context, haxorg_AstTrackingGroup self);
  static bool isSingle_const(OrgContext* org_context, haxorg_AstTrackingGroup self);
  static bool isTrackedHashtag_const(OrgContext* org_context, haxorg_AstTrackingGroup self);
  static bool isRadioTarget_const(OrgContext* org_context, haxorg_AstTrackingGroup self);
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
  static haxorg_StdOptional getIdPath_const(OrgContext* org_context, haxorg_AstTrackingMap self, haxorg_HstdStr id);
  static haxorg_StdOptional getNamePath_const(OrgContext* org_context, haxorg_AstTrackingMap self, haxorg_HstdStr id);
  static haxorg_StdOptional getAnchorTarget_const(OrgContext* org_context, haxorg_AstTrackingMap self, haxorg_HstdStr id);
  static haxorg_StdOptional getFootnotePath_const(OrgContext* org_context, haxorg_AstTrackingMap self, haxorg_HstdStr id);
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
  static bool isAnnotatedWith_const(OrgContext* org_context, haxorg_SequenceAnnotation self, int groupKind, int segmentKind);
};

template <>
struct org::bind::c::VTable<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_GraphMapLinkRadio getRadio(OrgContext* org_context, haxorg_GraphMapLink self);
  static haxorg_GraphMapLinkRadio getRadio_const(OrgContext* org_context, haxorg_GraphMapLink self);
  static bool isRadio_const(OrgContext* org_context, haxorg_GraphMapLink self);
  static haxorg_GraphMapLinkLink getLink(OrgContext* org_context, haxorg_GraphMapLink self);
  static haxorg_GraphMapLinkLink getLink_const(OrgContext* org_context, haxorg_GraphMapLink self);
  static bool isLink_const(OrgContext* org_context, haxorg_GraphMapLink self);
  static haxorg_GraphMapLinkKind getKind_const(OrgContext* org_context, haxorg_GraphMapLink self);
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
  static haxorg_ImmAdapter getAdapter_const(OrgContext* org_context, haxorg_GraphMapNodeProp self, haxorg_ImmAstContext context);
  static haxorg_StdOptional getSubtreeId_const(OrgContext* org_context, haxorg_GraphMapNodeProp self, haxorg_ImmAstContext context);
  static haxorg_StdOptional getFootnoteName_const(OrgContext* org_context, haxorg_GraphMapNodeProp self, haxorg_ImmAstContext context);
};

template <>
struct org::bind::c::VTable<haxorg_GraphMapEdgeProp, haxorg_GraphMapEdgeProp_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_GraphMapNode, haxorg_GraphMapNode_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_GraphMapNode self, haxorg_GraphMapNode other);
  static bool __lt___const(OrgContext* org_context, haxorg_GraphMapNode self, haxorg_GraphMapNode other);
};

template <>
struct org::bind::c::VTable<haxorg_GraphMapEdge, haxorg_GraphMapEdge_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int nodeCount_const(OrgContext* org_context, haxorg_GraphMapGraph self);
  static int edgeCount_const(OrgContext* org_context, haxorg_GraphMapGraph self);
  static haxorg_GraphAdjNodesList outNodes_const(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapNode node);
  static haxorg_GraphAdjNodesList inNodes_const(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapNode node);
  static haxorg_HstdVec adjEdges_const(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapNode node);
  static haxorg_HstdVec adjNodes_const(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapNode node);
  static haxorg_HstdVec outEdges_const(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapNode node);
  static haxorg_HstdVec inEdges_const(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapNode node);
  static int outDegree_const(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapNode node);
  static int inDegree_const(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapNode node);
  static bool isRegisteredNode_const(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapNode id);
  static bool isRegisteredNodeById_const(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_ImmUniqId id);
  static haxorg_GraphMapNodeProp atMapNode_const(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapNode node);
  static haxorg_GraphMapEdgeProp atMapEdge_const(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapEdge edge);
  static void addEdge(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapEdge edge);
  static void addEdgeWithProp(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapEdge edge, haxorg_GraphMapEdgeProp prop);
  static void addNode(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapNode node);
  static void addNodeWithProp(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapNode node, haxorg_GraphMapNodeProp prop);
  static bool hasEdge_const(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapNode source, haxorg_GraphMapNode target);
  static bool hasNode_const(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapNode node);
  static bool has2AdapterEdge_const(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_ImmAdapter source, haxorg_ImmAdapter target);
};

template <>
struct org::bind::c::VTable<haxorg_GraphMapConfig, haxorg_GraphMapConfig_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_GraphMapGraph getGraph_const(OrgContext* org_context, haxorg_GraphMapGraphState self);
  static haxorg_GraphMapGraphState FromAstContext(OrgContext* org_context, haxorg_GraphMapGraphState self, haxorg_ImmAstContext ast);
  static void registerNode(OrgContext* org_context, haxorg_GraphMapGraphState self, haxorg_GraphMapNodeProp node, haxorg_GraphMapConfig conf);
  static void addNode(OrgContext* org_context, haxorg_GraphMapGraphState self, haxorg_ImmAdapter node, haxorg_GraphMapConfig conf);
  static void addNodeRec(OrgContext* org_context, haxorg_GraphMapGraphState self, haxorg_ImmAstContext ast, haxorg_ImmAdapter node, haxorg_GraphMapConfig conf);
  static haxorg_HstdVec getUnresolvedSubtreeLinks_const(OrgContext* org_context, haxorg_GraphMapGraphState self, haxorg_ImmSubtreeAdapter node, haxorg_GraphMapConfig conf);
  static haxorg_StdOptional getUnresolvedLink_const(OrgContext* org_context, haxorg_GraphMapGraphState self, haxorg_ImmLinkAdapter node, haxorg_GraphMapConfig conf);
};

template <>
struct org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LispCode self, haxorg_LispCode other);
  static bool isCall_const(OrgContext* org_context, haxorg_LispCode self);
  static haxorg_LispCodeCall getCallConst_const(OrgContext* org_context, haxorg_LispCode self);
  static haxorg_LispCodeCall getCallMut(OrgContext* org_context, haxorg_LispCode self);
  static bool isList_const(OrgContext* org_context, haxorg_LispCode self);
  static haxorg_LispCodeList getListConst_const(OrgContext* org_context, haxorg_LispCode self);
  static haxorg_LispCodeList getListMut(OrgContext* org_context, haxorg_LispCode self);
  static bool isKeyValue_const(OrgContext* org_context, haxorg_LispCode self);
  static haxorg_LispCodeKeyValue getKeyValueConst_const(OrgContext* org_context, haxorg_LispCode self);
  static haxorg_LispCodeKeyValue getKeyValueMut(OrgContext* org_context, haxorg_LispCode self);
  static bool isNumber_const(OrgContext* org_context, haxorg_LispCode self);
  static haxorg_LispCodeNumber getNumberConst_const(OrgContext* org_context, haxorg_LispCode self);
  static haxorg_LispCodeNumber getNumberMut(OrgContext* org_context, haxorg_LispCode self);
  static bool isText_const(OrgContext* org_context, haxorg_LispCode self);
  static haxorg_LispCodeText getTextConst_const(OrgContext* org_context, haxorg_LispCode self);
  static haxorg_LispCodeText getTextMut(OrgContext* org_context, haxorg_LispCode self);
  static bool isIdent_const(OrgContext* org_context, haxorg_LispCode self);
  static haxorg_LispCodeIdent getIdentConst_const(OrgContext* org_context, haxorg_LispCode self);
  static haxorg_LispCodeIdent getIdentMut(OrgContext* org_context, haxorg_LispCode self);
  static bool isBoolean_const(OrgContext* org_context, haxorg_LispCode self);
  static haxorg_LispCodeBoolean getBooleanConst_const(OrgContext* org_context, haxorg_LispCode self);
  static haxorg_LispCodeBoolean getBooleanMut(OrgContext* org_context, haxorg_LispCode self);
  static bool isReal_const(OrgContext* org_context, haxorg_LispCode self);
  static haxorg_LispCodeReal getRealConst_const(OrgContext* org_context, haxorg_LispCode self);
  static haxorg_LispCodeReal getRealMut(OrgContext* org_context, haxorg_LispCode self);
  static haxorg_LispCodeKind getKind_const(OrgContext* org_context, haxorg_LispCode self);
};

template <>
struct org::bind::c::VTable<haxorg_LispCodeCall, haxorg_LispCodeCall_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LispCodeCall self, haxorg_LispCodeCall other);
};

template <>
struct org::bind::c::VTable<haxorg_LispCodeList, haxorg_LispCodeList_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LispCodeList self, haxorg_LispCodeList other);
};

template <>
struct org::bind::c::VTable<haxorg_LispCodeKeyValue, haxorg_LispCodeKeyValue_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LispCodeKeyValue self, haxorg_LispCodeKeyValue other);
};

template <>
struct org::bind::c::VTable<haxorg_LispCodeNumber, haxorg_LispCodeNumber_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LispCodeNumber self, haxorg_LispCodeNumber other);
};

template <>
struct org::bind::c::VTable<haxorg_LispCodeText, haxorg_LispCodeText_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LispCodeText self, haxorg_LispCodeText other);
};

template <>
struct org::bind::c::VTable<haxorg_LispCodeIdent, haxorg_LispCodeIdent_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LispCodeIdent self, haxorg_LispCodeIdent other);
};

template <>
struct org::bind::c::VTable<haxorg_LispCodeBoolean, haxorg_LispCodeBoolean_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LispCodeBoolean self, haxorg_LispCodeBoolean other);
};

template <>
struct org::bind::c::VTable<haxorg_LispCodeReal, haxorg_LispCodeReal_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LispCodeReal self, haxorg_LispCodeReal other);
};

template <>
struct org::bind::c::VTable<haxorg_Tblfm, haxorg_Tblfm_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_Tblfm self, haxorg_Tblfm other);
};

template <>
struct org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_TblfmExpr self, haxorg_TblfmExpr other);
  static bool isAxisRef_const(OrgContext* org_context, haxorg_TblfmExpr self);
  static haxorg_TblfmExprAxisRef getAxisRefConst_const(OrgContext* org_context, haxorg_TblfmExpr self);
  static haxorg_TblfmExprAxisRef getAxisRefMut(OrgContext* org_context, haxorg_TblfmExpr self);
  static bool isAxisName_const(OrgContext* org_context, haxorg_TblfmExpr self);
  static haxorg_TblfmExprAxisName getAxisNameConst_const(OrgContext* org_context, haxorg_TblfmExpr self);
  static haxorg_TblfmExprAxisName getAxisNameMut(OrgContext* org_context, haxorg_TblfmExpr self);
  static bool isIntLiteral_const(OrgContext* org_context, haxorg_TblfmExpr self);
  static haxorg_TblfmExprIntLiteral getIntLiteralConst_const(OrgContext* org_context, haxorg_TblfmExpr self);
  static haxorg_TblfmExprIntLiteral getIntLiteralMut(OrgContext* org_context, haxorg_TblfmExpr self);
  static bool isFloatLiteral_const(OrgContext* org_context, haxorg_TblfmExpr self);
  static haxorg_TblfmExprFloatLiteral getFloatLiteralConst_const(OrgContext* org_context, haxorg_TblfmExpr self);
  static haxorg_TblfmExprFloatLiteral getFloatLiteralMut(OrgContext* org_context, haxorg_TblfmExpr self);
  static bool isRangeRef_const(OrgContext* org_context, haxorg_TblfmExpr self);
  static haxorg_TblfmExprRangeRef getRangeRefConst_const(OrgContext* org_context, haxorg_TblfmExpr self);
  static haxorg_TblfmExprRangeRef getRangeRefMut(OrgContext* org_context, haxorg_TblfmExpr self);
  static bool isCall_const(OrgContext* org_context, haxorg_TblfmExpr self);
  static haxorg_TblfmExprCall getCallConst_const(OrgContext* org_context, haxorg_TblfmExpr self);
  static haxorg_TblfmExprCall getCallMut(OrgContext* org_context, haxorg_TblfmExpr self);
  static bool isElisp_const(OrgContext* org_context, haxorg_TblfmExpr self);
  static haxorg_TblfmExprElisp getElispConst_const(OrgContext* org_context, haxorg_TblfmExpr self);
  static haxorg_TblfmExprElisp getElispMut(OrgContext* org_context, haxorg_TblfmExpr self);
  static haxorg_TblfmExprKind getKind_const(OrgContext* org_context, haxorg_TblfmExpr self);
};

template <>
struct org::bind::c::VTable<haxorg_TblfmExprAxisRef, haxorg_TblfmExprAxisRef_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_TblfmExprAxisRef self, haxorg_TblfmExprAxisRef other);
};

template <>
struct org::bind::c::VTable<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition self, haxorg_TblfmExprAxisRefPosition other);
  static bool isIndex_const(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition self);
  static haxorg_TblfmExprAxisRefPositionIndex getIndexConst_const(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition self);
  static haxorg_TblfmExprAxisRefPositionIndex getIndexMut(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition self);
  static bool isName_const(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition self);
  static haxorg_TblfmExprAxisRefPositionName getNameConst_const(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition self);
  static haxorg_TblfmExprAxisRefPositionName getNameMut(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition self);
  static haxorg_TblfmExprAxisRefPositionKind getKind_const(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition self);
};

template <>
struct org::bind::c::VTable<haxorg_TblfmExprAxisRefPositionIndex, haxorg_TblfmExprAxisRefPositionIndex_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_TblfmExprAxisRefPositionIndex self, haxorg_TblfmExprAxisRefPositionIndex other);
};

template <>
struct org::bind::c::VTable<haxorg_TblfmExprAxisRefPositionName, haxorg_TblfmExprAxisRefPositionName_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_TblfmExprAxisRefPositionName self, haxorg_TblfmExprAxisRefPositionName other);
};

template <>
struct org::bind::c::VTable<haxorg_TblfmExprAxisName, haxorg_TblfmExprAxisName_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_TblfmExprAxisName self, haxorg_TblfmExprAxisName other);
};

template <>
struct org::bind::c::VTable<haxorg_TblfmExprIntLiteral, haxorg_TblfmExprIntLiteral_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_TblfmExprIntLiteral self, haxorg_TblfmExprIntLiteral other);
};

template <>
struct org::bind::c::VTable<haxorg_TblfmExprFloatLiteral, haxorg_TblfmExprFloatLiteral_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_TblfmExprFloatLiteral self, haxorg_TblfmExprFloatLiteral other);
};

template <>
struct org::bind::c::VTable<haxorg_TblfmExprRangeRef, haxorg_TblfmExprRangeRef_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_TblfmExprRangeRef self, haxorg_TblfmExprRangeRef other);
};

template <>
struct org::bind::c::VTable<haxorg_TblfmExprCall, haxorg_TblfmExprCall_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_TblfmExprCall self, haxorg_TblfmExprCall other);
};

template <>
struct org::bind::c::VTable<haxorg_TblfmExprElisp, haxorg_TblfmExprElisp_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_TblfmExprElisp self, haxorg_TblfmExprElisp other);
};

template <>
struct org::bind::c::VTable<haxorg_TblfmAssign, haxorg_TblfmAssign_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_TblfmAssign self, haxorg_TblfmAssign other);
};

template <>
struct org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdOpt getBool_const(OrgContext* org_context, haxorg_AttrValue self);
  static haxorg_HstdOpt getInt_const(OrgContext* org_context, haxorg_AttrValue self);
  static haxorg_HstdStr getString_const(OrgContext* org_context, haxorg_AttrValue self);
  static haxorg_HstdOpt getDouble_const(OrgContext* org_context, haxorg_AttrValue self);
  static bool __eq___const(OrgContext* org_context, haxorg_AttrValue self, haxorg_AttrValue other);
  static bool isTextValue_const(OrgContext* org_context, haxorg_AttrValue self);
  static haxorg_AttrValueTextValue getTextValueConst_const(OrgContext* org_context, haxorg_AttrValue self);
  static haxorg_AttrValueTextValue getTextValueMut(OrgContext* org_context, haxorg_AttrValue self);
  static bool isFileReference_const(OrgContext* org_context, haxorg_AttrValue self);
  static haxorg_AttrValueFileReference getFileReferenceConst_const(OrgContext* org_context, haxorg_AttrValue self);
  static haxorg_AttrValueFileReference getFileReferenceMut(OrgContext* org_context, haxorg_AttrValue self);
  static bool isLispValue_const(OrgContext* org_context, haxorg_AttrValue self);
  static haxorg_AttrValueLispValue getLispValueConst_const(OrgContext* org_context, haxorg_AttrValue self);
  static haxorg_AttrValueLispValue getLispValueMut(OrgContext* org_context, haxorg_AttrValue self);
  static haxorg_AttrValueKind getKind_const(OrgContext* org_context, haxorg_AttrValue self);
};

template <>
struct org::bind::c::VTable<haxorg_AttrValueDimensionSpan, haxorg_AttrValueDimensionSpan_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_AttrValueDimensionSpan self, haxorg_AttrValueDimensionSpan other);
};

template <>
struct org::bind::c::VTable<haxorg_AttrValueTextValue, haxorg_AttrValueTextValue_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_AttrValueTextValue self, haxorg_AttrValueTextValue other);
};

template <>
struct org::bind::c::VTable<haxorg_AttrValueFileReference, haxorg_AttrValueFileReference_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_AttrValueFileReference self, haxorg_AttrValueFileReference other);
};

template <>
struct org::bind::c::VTable<haxorg_AttrValueLispValue, haxorg_AttrValueLispValue_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_AttrValueLispValue self, haxorg_AttrValueLispValue other);
};

template <>
struct org::bind::c::VTable<haxorg_HashTagFlat, haxorg_HashTagFlat_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_HashTagFlat self, haxorg_HashTagFlat other);
  static bool __lt___const(OrgContext* org_context, haxorg_HashTagFlat self, haxorg_HashTagFlat other);
};

template <>
struct org::bind::c::VTable<haxorg_TodoKeyword, haxorg_TodoKeyword_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_TodoKeyword self, haxorg_TodoKeyword other);
};

template <>
struct org::bind::c::VTable<haxorg_HashTagText, haxorg_HashTagText_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_HashTagText self, haxorg_HashTagText other);
  static bool prefixMatch_const(OrgContext* org_context, haxorg_HashTagText self, haxorg_HstdVec prefix);
  static haxorg_HstdVec getFlatHashes_const(OrgContext* org_context, haxorg_HashTagText self, bool withIntermediate);
};

template <>
struct org::bind::c::VTable<haxorg_SubtreePath, haxorg_SubtreePath_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_SubtreePath self, haxorg_SubtreePath other);
};

template <>
struct org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LinkTarget self, haxorg_LinkTarget other);
  static bool isRaw_const(OrgContext* org_context, haxorg_LinkTarget self);
  static haxorg_LinkTargetRaw getRawConst_const(OrgContext* org_context, haxorg_LinkTarget self);
  static haxorg_LinkTargetRaw getRawMut(OrgContext* org_context, haxorg_LinkTarget self);
  static bool isId_const(OrgContext* org_context, haxorg_LinkTarget self);
  static haxorg_LinkTargetId getIdConst_const(OrgContext* org_context, haxorg_LinkTarget self);
  static haxorg_LinkTargetId getIdMut(OrgContext* org_context, haxorg_LinkTarget self);
  static bool isCustomId_const(OrgContext* org_context, haxorg_LinkTarget self);
  static haxorg_LinkTargetCustomId getCustomIdConst_const(OrgContext* org_context, haxorg_LinkTarget self);
  static haxorg_LinkTargetCustomId getCustomIdMut(OrgContext* org_context, haxorg_LinkTarget self);
  static bool isSubtreeTitle_const(OrgContext* org_context, haxorg_LinkTarget self);
  static haxorg_LinkTargetSubtreeTitle getSubtreeTitleConst_const(OrgContext* org_context, haxorg_LinkTarget self);
  static haxorg_LinkTargetSubtreeTitle getSubtreeTitleMut(OrgContext* org_context, haxorg_LinkTarget self);
  static bool isPerson_const(OrgContext* org_context, haxorg_LinkTarget self);
  static haxorg_LinkTargetPerson getPersonConst_const(OrgContext* org_context, haxorg_LinkTarget self);
  static haxorg_LinkTargetPerson getPersonMut(OrgContext* org_context, haxorg_LinkTarget self);
  static bool isUserProtocol_const(OrgContext* org_context, haxorg_LinkTarget self);
  static haxorg_LinkTargetUserProtocol getUserProtocolConst_const(OrgContext* org_context, haxorg_LinkTarget self);
  static haxorg_LinkTargetUserProtocol getUserProtocolMut(OrgContext* org_context, haxorg_LinkTarget self);
  static bool isInternal_const(OrgContext* org_context, haxorg_LinkTarget self);
  static haxorg_LinkTargetInternal getInternalConst_const(OrgContext* org_context, haxorg_LinkTarget self);
  static haxorg_LinkTargetInternal getInternalMut(OrgContext* org_context, haxorg_LinkTarget self);
  static bool isFootnote_const(OrgContext* org_context, haxorg_LinkTarget self);
  static haxorg_LinkTargetFootnote getFootnoteConst_const(OrgContext* org_context, haxorg_LinkTarget self);
  static haxorg_LinkTargetFootnote getFootnoteMut(OrgContext* org_context, haxorg_LinkTarget self);
  static bool isFile_const(OrgContext* org_context, haxorg_LinkTarget self);
  static haxorg_LinkTargetFile getFileConst_const(OrgContext* org_context, haxorg_LinkTarget self);
  static haxorg_LinkTargetFile getFileMut(OrgContext* org_context, haxorg_LinkTarget self);
  static bool isAttachment_const(OrgContext* org_context, haxorg_LinkTarget self);
  static haxorg_LinkTargetAttachment getAttachmentConst_const(OrgContext* org_context, haxorg_LinkTarget self);
  static haxorg_LinkTargetAttachment getAttachmentMut(OrgContext* org_context, haxorg_LinkTarget self);
  static haxorg_LinkTargetKind getKind_const(OrgContext* org_context, haxorg_LinkTarget self);
};

template <>
struct org::bind::c::VTable<haxorg_LinkTargetRaw, haxorg_LinkTargetRaw_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LinkTargetRaw self, haxorg_LinkTargetRaw other);
};

template <>
struct org::bind::c::VTable<haxorg_LinkTargetId, haxorg_LinkTargetId_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LinkTargetId self, haxorg_LinkTargetId other);
};

template <>
struct org::bind::c::VTable<haxorg_LinkTargetCustomId, haxorg_LinkTargetCustomId_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LinkTargetCustomId self, haxorg_LinkTargetCustomId other);
};

template <>
struct org::bind::c::VTable<haxorg_LinkTargetSubtreeTitle, haxorg_LinkTargetSubtreeTitle_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LinkTargetSubtreeTitle self, haxorg_LinkTargetSubtreeTitle other);
};

template <>
struct org::bind::c::VTable<haxorg_LinkTargetPerson, haxorg_LinkTargetPerson_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LinkTargetPerson self, haxorg_LinkTargetPerson other);
};

template <>
struct org::bind::c::VTable<haxorg_LinkTargetUserProtocol, haxorg_LinkTargetUserProtocol_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LinkTargetUserProtocol self, haxorg_LinkTargetUserProtocol other);
};

template <>
struct org::bind::c::VTable<haxorg_LinkTargetInternal, haxorg_LinkTargetInternal_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LinkTargetInternal self, haxorg_LinkTargetInternal other);
};

template <>
struct org::bind::c::VTable<haxorg_LinkTargetFootnote, haxorg_LinkTargetFootnote_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LinkTargetFootnote self, haxorg_LinkTargetFootnote other);
};

template <>
struct org::bind::c::VTable<haxorg_LinkTargetFile, haxorg_LinkTargetFile_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LinkTargetFile self, haxorg_LinkTargetFile other);
};

template <>
struct org::bind::c::VTable<haxorg_LinkTargetAttachment, haxorg_LinkTargetAttachment_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LinkTargetAttachment self, haxorg_LinkTargetAttachment other);
};

template <>
struct org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_SubtreeLogHead self, haxorg_SubtreeLogHead other);
  static bool isPriority_const(OrgContext* org_context, haxorg_SubtreeLogHead self);
  static haxorg_SubtreeLogHeadPriority getPriorityConst_const(OrgContext* org_context, haxorg_SubtreeLogHead self);
  static haxorg_SubtreeLogHeadPriority getPriorityMut(OrgContext* org_context, haxorg_SubtreeLogHead self);
  static bool isNote_const(OrgContext* org_context, haxorg_SubtreeLogHead self);
  static haxorg_SubtreeLogHeadNote getNoteConst_const(OrgContext* org_context, haxorg_SubtreeLogHead self);
  static haxorg_SubtreeLogHeadNote getNoteMut(OrgContext* org_context, haxorg_SubtreeLogHead self);
  static bool isRefile_const(OrgContext* org_context, haxorg_SubtreeLogHead self);
  static haxorg_SubtreeLogHeadRefile getRefileConst_const(OrgContext* org_context, haxorg_SubtreeLogHead self);
  static haxorg_SubtreeLogHeadRefile getRefileMut(OrgContext* org_context, haxorg_SubtreeLogHead self);
  static bool isClock_const(OrgContext* org_context, haxorg_SubtreeLogHead self);
  static haxorg_SubtreeLogHeadClock getClockConst_const(OrgContext* org_context, haxorg_SubtreeLogHead self);
  static haxorg_SubtreeLogHeadClock getClockMut(OrgContext* org_context, haxorg_SubtreeLogHead self);
  static bool isState_const(OrgContext* org_context, haxorg_SubtreeLogHead self);
  static haxorg_SubtreeLogHeadState getStateConst_const(OrgContext* org_context, haxorg_SubtreeLogHead self);
  static haxorg_SubtreeLogHeadState getStateMut(OrgContext* org_context, haxorg_SubtreeLogHead self);
  static bool isDeadline_const(OrgContext* org_context, haxorg_SubtreeLogHead self);
  static haxorg_SubtreeLogHeadDeadline getDeadlineConst_const(OrgContext* org_context, haxorg_SubtreeLogHead self);
  static haxorg_SubtreeLogHeadDeadline getDeadlineMut(OrgContext* org_context, haxorg_SubtreeLogHead self);
  static bool isSchedule_const(OrgContext* org_context, haxorg_SubtreeLogHead self);
  static haxorg_SubtreeLogHeadSchedule getScheduleConst_const(OrgContext* org_context, haxorg_SubtreeLogHead self);
  static haxorg_SubtreeLogHeadSchedule getScheduleMut(OrgContext* org_context, haxorg_SubtreeLogHead self);
  static bool isTag_const(OrgContext* org_context, haxorg_SubtreeLogHead self);
  static haxorg_SubtreeLogHeadTag getTagConst_const(OrgContext* org_context, haxorg_SubtreeLogHead self);
  static haxorg_SubtreeLogHeadTag getTagMut(OrgContext* org_context, haxorg_SubtreeLogHead self);
  static bool isUnknown_const(OrgContext* org_context, haxorg_SubtreeLogHead self);
  static haxorg_SubtreeLogHeadUnknown getUnknownConst_const(OrgContext* org_context, haxorg_SubtreeLogHead self);
  static haxorg_SubtreeLogHeadUnknown getUnknownMut(OrgContext* org_context, haxorg_SubtreeLogHead self);
  static haxorg_SubtreeLogHeadKind getLogKind_const(OrgContext* org_context, haxorg_SubtreeLogHead self);
};

template <>
struct org::bind::c::VTable<haxorg_SubtreeLogHeadPriority, haxorg_SubtreeLogHeadPriority_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadPriority self, haxorg_SubtreeLogHeadPriority other);
};

template <>
struct org::bind::c::VTable<haxorg_SubtreeLogHeadNote, haxorg_SubtreeLogHeadNote_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadNote self, haxorg_SubtreeLogHeadNote other);
};

template <>
struct org::bind::c::VTable<haxorg_SubtreeLogHeadRefile, haxorg_SubtreeLogHeadRefile_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadRefile self, haxorg_SubtreeLogHeadRefile other);
};

template <>
struct org::bind::c::VTable<haxorg_SubtreeLogHeadClock, haxorg_SubtreeLogHeadClock_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadClock self, haxorg_SubtreeLogHeadClock other);
};

template <>
struct org::bind::c::VTable<haxorg_SubtreeLogHeadState, haxorg_SubtreeLogHeadState_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadState self, haxorg_SubtreeLogHeadState other);
};

template <>
struct org::bind::c::VTable<haxorg_SubtreeLogHeadDeadline, haxorg_SubtreeLogHeadDeadline_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadDeadline self, haxorg_SubtreeLogHeadDeadline other);
};

template <>
struct org::bind::c::VTable<haxorg_SubtreeLogHeadSchedule, haxorg_SubtreeLogHeadSchedule_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadSchedule self, haxorg_SubtreeLogHeadSchedule other);
};

template <>
struct org::bind::c::VTable<haxorg_SubtreeLogHeadTag, haxorg_SubtreeLogHeadTag_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadTag self, haxorg_SubtreeLogHeadTag other);
};

template <>
struct org::bind::c::VTable<haxorg_SubtreeLogHeadUnknown, haxorg_SubtreeLogHeadUnknown_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadUnknown self, haxorg_SubtreeLogHeadUnknown other);
};

template <>
struct org::bind::c::VTable<haxorg_SubtreeCompletion, haxorg_SubtreeCompletion_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_SubtreeCompletion self, haxorg_SubtreeCompletion other);
};

template <>
struct org::bind::c::VTable<haxorg_AttrList, haxorg_AttrList_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_AttrList self, haxorg_AttrList other);
};

template <>
struct org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdVec getFlatArgs_const(OrgContext* org_context, haxorg_AttrGroup self);
  static haxorg_HstdVec getAttrs_const(OrgContext* org_context, haxorg_AttrGroup self, haxorg_HstdOpt key);
  static void setNamedAttr(OrgContext* org_context, haxorg_AttrGroup self, haxorg_HstdStr key, haxorg_HstdVec attrs);
  static void setPositionalAttr(OrgContext* org_context, haxorg_AttrGroup self, haxorg_HstdVec items);
  static int getPositionalSize_const(OrgContext* org_context, haxorg_AttrGroup self);
  static int getNamedSize_const(OrgContext* org_context, haxorg_AttrGroup self);
  static bool isEmpty_const(OrgContext* org_context, haxorg_AttrGroup self);
  static haxorg_AttrList getAll_const(OrgContext* org_context, haxorg_AttrGroup self);
  static haxorg_AttrValue atPositional_const(OrgContext* org_context, haxorg_AttrGroup self, int index);
  static haxorg_HstdOpt getPositional_const(OrgContext* org_context, haxorg_AttrGroup self, int index);
  static haxorg_AttrList atNamed_const(OrgContext* org_context, haxorg_AttrGroup self, haxorg_HstdStr index);
  static haxorg_HstdOpt getNamed_const(OrgContext* org_context, haxorg_AttrGroup self, haxorg_HstdStr index);
  static haxorg_AttrValue atFirstNamed_const(OrgContext* org_context, haxorg_AttrGroup self, haxorg_HstdStr index);
  static haxorg_HstdOpt getFirstNamed_const(OrgContext* org_context, haxorg_AttrGroup self, haxorg_HstdStr index);
  static haxorg_AttrList atVarNamed_const(OrgContext* org_context, haxorg_AttrGroup self, haxorg_HstdStr index);
  static haxorg_HstdOpt getVarNamed_const(OrgContext* org_context, haxorg_AttrGroup self, haxorg_HstdStr index);
  static haxorg_AttrValue atFirstVarNamed_const(OrgContext* org_context, haxorg_AttrGroup self, haxorg_HstdStr index);
  static haxorg_HstdOpt getFirstVarNamed_const(OrgContext* org_context, haxorg_AttrGroup self, haxorg_HstdStr index);
  static bool __eq___const(OrgContext* org_context, haxorg_AttrGroup self, haxorg_AttrGroup other);
};

template <>
struct org::bind::c::VTable<haxorg_OrgCodeEvalInput, haxorg_OrgCodeEvalInput_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_OrgCodeEvalInput self, haxorg_OrgCodeEvalInput other);
  static haxorg_HstdOpt getVariable_const(OrgContext* org_context, haxorg_OrgCodeEvalInput self, haxorg_HstdStr name);
};

template <>
struct org::bind::c::VTable<haxorg_OrgCodeEvalInputVar, haxorg_OrgCodeEvalInputVar_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_OrgCodeEvalInputVar self, haxorg_OrgCodeEvalInputVar other);
};

template <>
struct org::bind::c::VTable<haxorg_OrgCodeEvalOutput, haxorg_OrgCodeEvalOutput_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_OrgCodeEvalOutput self, haxorg_OrgCodeEvalOutput other);
};

template <>
struct org::bind::c::VTable<haxorg_ColumnView, haxorg_ColumnView_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ColumnView self, haxorg_ColumnView other);
};

template <>
struct org::bind::c::VTable<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ColumnViewSummary self, haxorg_ColumnViewSummary other);
  static bool isCheckboxAggregate_const(OrgContext* org_context, haxorg_ColumnViewSummary self);
  static haxorg_ColumnViewSummaryCheckboxAggregate getCheckboxAggregateConst_const(OrgContext* org_context, haxorg_ColumnViewSummary self);
  static haxorg_ColumnViewSummaryCheckboxAggregate getCheckboxAggregateMut(OrgContext* org_context, haxorg_ColumnViewSummary self);
  static bool isMathAggregate_const(OrgContext* org_context, haxorg_ColumnViewSummary self);
  static haxorg_ColumnViewSummaryMathAggregate getMathAggregateConst_const(OrgContext* org_context, haxorg_ColumnViewSummary self);
  static haxorg_ColumnViewSummaryMathAggregate getMathAggregateMut(OrgContext* org_context, haxorg_ColumnViewSummary self);
  static haxorg_ColumnViewSummaryKind getKind_const(OrgContext* org_context, haxorg_ColumnViewSummary self);
};

template <>
struct org::bind::c::VTable<haxorg_ColumnViewSummaryCheckboxAggregate, haxorg_ColumnViewSummaryCheckboxAggregate_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ColumnViewSummaryCheckboxAggregate self, haxorg_ColumnViewSummaryCheckboxAggregate other);
};

template <>
struct org::bind::c::VTable<haxorg_ColumnViewSummaryMathAggregate, haxorg_ColumnViewSummaryMathAggregate_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ColumnViewSummaryMathAggregate self, haxorg_ColumnViewSummaryMathAggregate other);
};

template <>
struct org::bind::c::VTable<haxorg_ColumnViewColumn, haxorg_ColumnViewColumn_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ColumnViewColumn self, haxorg_ColumnViewColumn other);
};

template <>
struct org::bind::c::VTable<haxorg_BlockCodeLine, haxorg_BlockCodeLine_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_BlockCodeLine self, haxorg_BlockCodeLine other);
};

template <>
struct org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_BlockCodeLinePart self, haxorg_BlockCodeLinePart other);
  static bool isRaw_const(OrgContext* org_context, haxorg_BlockCodeLinePart self);
  static haxorg_BlockCodeLinePartRaw getRawConst_const(OrgContext* org_context, haxorg_BlockCodeLinePart self);
  static haxorg_BlockCodeLinePartRaw getRawMut(OrgContext* org_context, haxorg_BlockCodeLinePart self);
  static bool isCallout_const(OrgContext* org_context, haxorg_BlockCodeLinePart self);
  static haxorg_BlockCodeLinePartCallout getCalloutConst_const(OrgContext* org_context, haxorg_BlockCodeLinePart self);
  static haxorg_BlockCodeLinePartCallout getCalloutMut(OrgContext* org_context, haxorg_BlockCodeLinePart self);
  static bool isTangle_const(OrgContext* org_context, haxorg_BlockCodeLinePart self);
  static haxorg_BlockCodeLinePartTangle getTangleConst_const(OrgContext* org_context, haxorg_BlockCodeLinePart self);
  static haxorg_BlockCodeLinePartTangle getTangleMut(OrgContext* org_context, haxorg_BlockCodeLinePart self);
  static haxorg_BlockCodeLinePartKind getKind_const(OrgContext* org_context, haxorg_BlockCodeLinePart self);
};

template <>
struct org::bind::c::VTable<haxorg_BlockCodeLinePartRaw, haxorg_BlockCodeLinePartRaw_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_BlockCodeLinePartRaw self, haxorg_BlockCodeLinePartRaw other);
};

template <>
struct org::bind::c::VTable<haxorg_BlockCodeLinePartCallout, haxorg_BlockCodeLinePartCallout_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_BlockCodeLinePartCallout self, haxorg_BlockCodeLinePartCallout other);
};

template <>
struct org::bind::c::VTable<haxorg_BlockCodeLinePartTangle, haxorg_BlockCodeLinePartTangle_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_BlockCodeLinePartTangle self, haxorg_BlockCodeLinePartTangle other);
};

template <>
struct org::bind::c::VTable<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_DocumentExportConfig self, haxorg_DocumentExportConfig other);
  static bool isDoExport_const(OrgContext* org_context, haxorg_DocumentExportConfig self);
  static haxorg_DocumentExportConfigDoExport getDoExportConst_const(OrgContext* org_context, haxorg_DocumentExportConfig self);
  static haxorg_DocumentExportConfigDoExport getDoExportMut(OrgContext* org_context, haxorg_DocumentExportConfig self);
  static bool isExportFixed_const(OrgContext* org_context, haxorg_DocumentExportConfig self);
  static haxorg_DocumentExportConfigExportFixed getExportFixedConst_const(OrgContext* org_context, haxorg_DocumentExportConfig self);
  static haxorg_DocumentExportConfigExportFixed getExportFixedMut(OrgContext* org_context, haxorg_DocumentExportConfig self);
  static haxorg_DocumentExportConfigTocExportKind getTocExportKind_const(OrgContext* org_context, haxorg_DocumentExportConfig self);
};

template <>
struct org::bind::c::VTable<haxorg_DocumentExportConfigTaskExport, haxorg_DocumentExportConfigTaskExport_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_DocumentExportConfigTaskExport self, haxorg_DocumentExportConfigTaskExport other);
};

template <>
struct org::bind::c::VTable<haxorg_DocumentExportConfigDoExport, haxorg_DocumentExportConfigDoExport_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_DocumentExportConfigDoExport self, haxorg_DocumentExportConfigDoExport other);
};

template <>
struct org::bind::c::VTable<haxorg_DocumentExportConfigExportFixed, haxorg_DocumentExportConfigExportFixed_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_DocumentExportConfigExportFixed self, haxorg_DocumentExportConfigExportFixed other);
};

template <>
struct org::bind::c::VTable<haxorg_SubtreePeriod, haxorg_SubtreePeriod_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_SubtreePeriod self, haxorg_SubtreePeriod other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool isMatching_const(OrgContext* org_context, haxorg_NamedProperty self, haxorg_HstdStr kind, haxorg_HstdOpt subKind);
  static haxorg_HstdStr getName_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_HstdOpt getSubKind_const(OrgContext* org_context, haxorg_NamedProperty self);
  static bool __eq___const(OrgContext* org_context, haxorg_NamedProperty self, haxorg_NamedProperty other);
  static bool isNonblocking_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyNonblocking getNonblockingConst_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyNonblocking getNonblockingMut(OrgContext* org_context, haxorg_NamedProperty self);
  static bool isArchiveTime_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyArchiveTime getArchiveTimeConst_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyArchiveTime getArchiveTimeMut(OrgContext* org_context, haxorg_NamedProperty self);
  static bool isArchiveFile_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyArchiveFile getArchiveFileConst_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyArchiveFile getArchiveFileMut(OrgContext* org_context, haxorg_NamedProperty self);
  static bool isArchiveOlpath_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyArchiveOlpath getArchiveOlpathConst_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyArchiveOlpath getArchiveOlpathMut(OrgContext* org_context, haxorg_NamedProperty self);
  static bool isArchiveTarget_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyArchiveTarget getArchiveTargetConst_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyArchiveTarget getArchiveTargetMut(OrgContext* org_context, haxorg_NamedProperty self);
  static bool isArchiveCategory_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyArchiveCategory getArchiveCategoryConst_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyArchiveCategory getArchiveCategoryMut(OrgContext* org_context, haxorg_NamedProperty self);
  static bool isArchiveTodo_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyArchiveTodo getArchiveTodoConst_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyArchiveTodo getArchiveTodoMut(OrgContext* org_context, haxorg_NamedProperty self);
  static bool isTrigger_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyTrigger getTriggerConst_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyTrigger getTriggerMut(OrgContext* org_context, haxorg_NamedProperty self);
  static bool isExportLatexClass_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyExportLatexClass getExportLatexClassConst_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyExportLatexClass getExportLatexClassMut(OrgContext* org_context, haxorg_NamedProperty self);
  static bool isCookieData_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyCookieData getCookieDataConst_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyCookieData getCookieDataMut(OrgContext* org_context, haxorg_NamedProperty self);
  static bool isExportLatexClassOptions_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyExportLatexClassOptions getExportLatexClassOptionsConst_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyExportLatexClassOptions getExportLatexClassOptionsMut(OrgContext* org_context, haxorg_NamedProperty self);
  static bool isExportLatexHeader_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyExportLatexHeader getExportLatexHeaderConst_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyExportLatexHeader getExportLatexHeaderMut(OrgContext* org_context, haxorg_NamedProperty self);
  static bool isExportLatexCompiler_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyExportLatexCompiler getExportLatexCompilerConst_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyExportLatexCompiler getExportLatexCompilerMut(OrgContext* org_context, haxorg_NamedProperty self);
  static bool isOrdered_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyOrdered getOrderedConst_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyOrdered getOrderedMut(OrgContext* org_context, haxorg_NamedProperty self);
  static bool isEffort_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyEffort getEffortConst_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyEffort getEffortMut(OrgContext* org_context, haxorg_NamedProperty self);
  static bool isVisibility_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyVisibility getVisibilityConst_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyVisibility getVisibilityMut(OrgContext* org_context, haxorg_NamedProperty self);
  static bool isExportOptions_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyExportOptions getExportOptionsConst_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyExportOptions getExportOptionsMut(OrgContext* org_context, haxorg_NamedProperty self);
  static bool isBlocker_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyBlocker getBlockerConst_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyBlocker getBlockerMut(OrgContext* org_context, haxorg_NamedProperty self);
  static bool isUnnumbered_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyUnnumbered getUnnumberedConst_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyUnnumbered getUnnumberedMut(OrgContext* org_context, haxorg_NamedProperty self);
  static bool isCreated_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyCreated getCreatedConst_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyCreated getCreatedMut(OrgContext* org_context, haxorg_NamedProperty self);
  static bool isRadioId_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyRadioId getRadioIdConst_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyRadioId getRadioIdMut(OrgContext* org_context, haxorg_NamedProperty self);
  static bool isHashtagDef_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyHashtagDef getHashtagDefConst_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyHashtagDef getHashtagDefMut(OrgContext* org_context, haxorg_NamedProperty self);
  static bool isCustomArgs_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyCustomArgs getCustomArgsConst_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyCustomArgs getCustomArgsMut(OrgContext* org_context, haxorg_NamedProperty self);
  static bool isCustomRaw_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyCustomRaw getCustomRawConst_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyCustomRaw getCustomRawMut(OrgContext* org_context, haxorg_NamedProperty self);
  static bool isCustomId_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyCustomId getCustomIdConst_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyCustomId getCustomIdMut(OrgContext* org_context, haxorg_NamedProperty self);
  static bool isCustomSubtreeJson_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyCustomSubtreeJson getCustomSubtreeJsonConst_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyCustomSubtreeJson getCustomSubtreeJsonMut(OrgContext* org_context, haxorg_NamedProperty self);
  static bool isCustomSubtreeFlags_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyCustomSubtreeFlags getCustomSubtreeFlagsConst_const(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyCustomSubtreeFlags getCustomSubtreeFlagsMut(OrgContext* org_context, haxorg_NamedProperty self);
  static haxorg_NamedPropertyKind getKind_const(OrgContext* org_context, haxorg_NamedProperty self);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyNonblocking, haxorg_NamedPropertyNonblocking_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyNonblocking self, haxorg_NamedPropertyNonblocking other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyArchiveTime, haxorg_NamedPropertyArchiveTime_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyArchiveTime self, haxorg_NamedPropertyArchiveTime other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyArchiveFile, haxorg_NamedPropertyArchiveFile_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyArchiveFile self, haxorg_NamedPropertyArchiveFile other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyArchiveOlpath, haxorg_NamedPropertyArchiveOlpath_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyArchiveOlpath self, haxorg_NamedPropertyArchiveOlpath other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyArchiveTarget, haxorg_NamedPropertyArchiveTarget_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyArchiveTarget self, haxorg_NamedPropertyArchiveTarget other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyArchiveCategory, haxorg_NamedPropertyArchiveCategory_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyArchiveCategory self, haxorg_NamedPropertyArchiveCategory other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyArchiveTodo, haxorg_NamedPropertyArchiveTodo_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyArchiveTodo self, haxorg_NamedPropertyArchiveTodo other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyTrigger, haxorg_NamedPropertyTrigger_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyTrigger self, haxorg_NamedPropertyTrigger other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyExportLatexClass, haxorg_NamedPropertyExportLatexClass_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyExportLatexClass self, haxorg_NamedPropertyExportLatexClass other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyCookieData, haxorg_NamedPropertyCookieData_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyCookieData self, haxorg_NamedPropertyCookieData other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyExportLatexClassOptions, haxorg_NamedPropertyExportLatexClassOptions_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyExportLatexClassOptions self, haxorg_NamedPropertyExportLatexClassOptions other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyExportLatexHeader, haxorg_NamedPropertyExportLatexHeader_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyExportLatexHeader self, haxorg_NamedPropertyExportLatexHeader other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyExportLatexCompiler, haxorg_NamedPropertyExportLatexCompiler_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyExportLatexCompiler self, haxorg_NamedPropertyExportLatexCompiler other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyOrdered, haxorg_NamedPropertyOrdered_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyOrdered self, haxorg_NamedPropertyOrdered other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyEffort, haxorg_NamedPropertyEffort_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyEffort self, haxorg_NamedPropertyEffort other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyVisibility, haxorg_NamedPropertyVisibility_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyVisibility self, haxorg_NamedPropertyVisibility other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyExportOptions, haxorg_NamedPropertyExportOptions_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyExportOptions self, haxorg_NamedPropertyExportOptions other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyBlocker, haxorg_NamedPropertyBlocker_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyBlocker self, haxorg_NamedPropertyBlocker other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyUnnumbered, haxorg_NamedPropertyUnnumbered_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyUnnumbered self, haxorg_NamedPropertyUnnumbered other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyCreated, haxorg_NamedPropertyCreated_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyCreated self, haxorg_NamedPropertyCreated other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyRadioId, haxorg_NamedPropertyRadioId_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyRadioId self, haxorg_NamedPropertyRadioId other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyHashtagDef, haxorg_NamedPropertyHashtagDef_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyHashtagDef self, haxorg_NamedPropertyHashtagDef other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyCustomArgs, haxorg_NamedPropertyCustomArgs_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyCustomArgs self, haxorg_NamedPropertyCustomArgs other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyCustomRaw, haxorg_NamedPropertyCustomRaw_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyCustomRaw self, haxorg_NamedPropertyCustomRaw other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyCustomId, haxorg_NamedPropertyCustomId_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyCustomId self, haxorg_NamedPropertyCustomId other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyCustomSubtreeJson, haxorg_NamedPropertyCustomSubtreeJson_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyCustomSubtreeJson self, haxorg_NamedPropertyCustomSubtreeJson other);
};

template <>
struct org::bind::c::VTable<haxorg_NamedPropertyCustomSubtreeFlags, haxorg_NamedPropertyCustomSubtreeFlags_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyCustomSubtreeFlags self, haxorg_NamedPropertyCustomSubtreeFlags other);
};

template <>
struct org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_OrgDiagnostics self, haxorg_OrgDiagnostics other);
  static bool isParseTokenError_const(OrgContext* org_context, haxorg_OrgDiagnostics self);
  static haxorg_OrgDiagnosticsParseTokenError getParseTokenErrorConst_const(OrgContext* org_context, haxorg_OrgDiagnostics self);
  static haxorg_OrgDiagnosticsParseTokenError getParseTokenErrorMut(OrgContext* org_context, haxorg_OrgDiagnostics self);
  static bool isParseError_const(OrgContext* org_context, haxorg_OrgDiagnostics self);
  static haxorg_OrgDiagnosticsParseError getParseErrorConst_const(OrgContext* org_context, haxorg_OrgDiagnostics self);
  static haxorg_OrgDiagnosticsParseError getParseErrorMut(OrgContext* org_context, haxorg_OrgDiagnostics self);
  static bool isIncludeError_const(OrgContext* org_context, haxorg_OrgDiagnostics self);
  static haxorg_OrgDiagnosticsIncludeError getIncludeErrorConst_const(OrgContext* org_context, haxorg_OrgDiagnostics self);
  static haxorg_OrgDiagnosticsIncludeError getIncludeErrorMut(OrgContext* org_context, haxorg_OrgDiagnostics self);
  static bool isConvertError_const(OrgContext* org_context, haxorg_OrgDiagnostics self);
  static haxorg_OrgDiagnosticsConvertError getConvertErrorConst_const(OrgContext* org_context, haxorg_OrgDiagnostics self);
  static haxorg_OrgDiagnosticsConvertError getConvertErrorMut(OrgContext* org_context, haxorg_OrgDiagnostics self);
  static bool isInternalError_const(OrgContext* org_context, haxorg_OrgDiagnostics self);
  static haxorg_OrgDiagnosticsInternalError getInternalErrorConst_const(OrgContext* org_context, haxorg_OrgDiagnostics self);
  static haxorg_OrgDiagnosticsInternalError getInternalErrorMut(OrgContext* org_context, haxorg_OrgDiagnostics self);
  static haxorg_OrgDiagnosticsKind getKind_const(OrgContext* org_context, haxorg_OrgDiagnostics self);
};

template <>
struct org::bind::c::VTable<haxorg_OrgDiagnosticsParseTokenError, haxorg_OrgDiagnosticsParseTokenError_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_OrgDiagnosticsParseTokenError self, haxorg_OrgDiagnosticsParseTokenError other);
};

template <>
struct org::bind::c::VTable<haxorg_OrgDiagnosticsParseError, haxorg_OrgDiagnosticsParseError_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_OrgDiagnosticsParseError self, haxorg_OrgDiagnosticsParseError other);
};

template <>
struct org::bind::c::VTable<haxorg_OrgDiagnosticsIncludeError, haxorg_OrgDiagnosticsIncludeError_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_OrgDiagnosticsIncludeError self, haxorg_OrgDiagnosticsIncludeError other);
};

template <>
struct org::bind::c::VTable<haxorg_OrgDiagnosticsConvertError, haxorg_OrgDiagnosticsConvertError_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_OrgDiagnosticsConvertError self, haxorg_OrgDiagnosticsConvertError other);
};

template <>
struct org::bind::c::VTable<haxorg_OrgDiagnosticsInternalError, haxorg_OrgDiagnosticsInternalError_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_OrgDiagnosticsInternalError self, haxorg_OrgDiagnosticsInternalError other);
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
  static haxorg_HstdVec getAttached_const(OrgContext* org_context, haxorg_Stmt self, haxorg_HstdOpt kind);
  static haxorg_HstdVec getCaption_const(OrgContext* org_context, haxorg_Stmt self);
  static haxorg_HstdVec getName_const(OrgContext* org_context, haxorg_Stmt self);
  static haxorg_HstdVec getAttrs_const(OrgContext* org_context, haxorg_Stmt self, haxorg_HstdOpt kind);
  static haxorg_HstdOpt getFirstAttr_const(OrgContext* org_context, haxorg_Stmt self, haxorg_HstdStr kind);
  static haxorg_HstdOpt getFirstAttrString_const(OrgContext* org_context, haxorg_Stmt self, haxorg_HstdStr kind);
  static haxorg_HstdOpt getFirstAttrInt_const(OrgContext* org_context, haxorg_Stmt self, haxorg_HstdStr kind);
  static haxorg_HstdOpt getFirstAttrBool_const(OrgContext* org_context, haxorg_Stmt self, haxorg_HstdStr kind);
  static haxorg_HstdOpt getFirstAttrDouble_const(OrgContext* org_context, haxorg_Stmt self, haxorg_HstdStr kind);
  static haxorg_HstdOpt getFirstAttrLisp_const(OrgContext* org_context, haxorg_Stmt self, haxorg_HstdStr kind);
  static haxorg_HstdOpt getFirstAttrKind_const(OrgContext* org_context, haxorg_Stmt self, haxorg_HstdStr kind);
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
  static haxorg_HstdStr getText_const(OrgContext* org_context, haxorg_Leaf self);
};

template <>
struct org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdOpt getYear_const(OrgContext* org_context, haxorg_Time self);
  static haxorg_HstdOpt getMonth_const(OrgContext* org_context, haxorg_Time self);
  static haxorg_HstdOpt getDay_const(OrgContext* org_context, haxorg_Time self);
  static haxorg_HstdOpt getHour_const(OrgContext* org_context, haxorg_Time self);
  static haxorg_HstdOpt getMinute_const(OrgContext* org_context, haxorg_Time self);
  static haxorg_HstdOpt getSecond_const(OrgContext* org_context, haxorg_Time self);
  static haxorg_UserTime getStaticTime_const(OrgContext* org_context, haxorg_Time self);
  static bool isStatic_const(OrgContext* org_context, haxorg_Time self);
  static haxorg_TimeStatic getStaticConst_const(OrgContext* org_context, haxorg_Time self);
  static haxorg_TimeStatic getStaticMut(OrgContext* org_context, haxorg_Time self);
  static bool isDynamic_const(OrgContext* org_context, haxorg_Time self);
  static haxorg_TimeDynamic getDynamicConst_const(OrgContext* org_context, haxorg_Time self);
  static haxorg_TimeDynamic getDynamicMut(OrgContext* org_context, haxorg_Time self);
  static haxorg_TimeTimeKind getTimeKind_const(OrgContext* org_context, haxorg_Time self);
};

template <>
struct org::bind::c::VTable<haxorg_TimeRepeat, haxorg_TimeRepeat_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_TimeRepeat self, haxorg_TimeRepeat other);
};

template <>
struct org::bind::c::VTable<haxorg_TimeStatic, haxorg_TimeStatic_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_TimeStatic self, haxorg_TimeStatic other);
};

template <>
struct org::bind::c::VTable<haxorg_TimeDynamic, haxorg_TimeDynamic_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_TimeDynamic self, haxorg_TimeDynamic other);
};

template <>
struct org::bind::c::VTable<haxorg_TimeRange, haxorg_TimeRange_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdOpt getClockedTimeSeconds_const(OrgContext* org_context, haxorg_TimeRange self);
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
  static void setDescription(OrgContext* org_context, haxorg_SubtreeLog self, haxorg_SemId desc);
};

template <>
struct org::bind::c::VTable<haxorg_Subtree, haxorg_Subtree_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdVec getTimePeriods_const(OrgContext* org_context, haxorg_Subtree self, haxorg_HstdIntSet kinds);
  static haxorg_HstdVec getProperties_const(OrgContext* org_context, haxorg_Subtree self, haxorg_HstdStr kind, haxorg_HstdOpt subkind);
  static haxorg_HstdOpt getProperty_const(OrgContext* org_context, haxorg_Subtree self, haxorg_HstdStr kind, haxorg_HstdOpt subkind);
  static void removeProperty(OrgContext* org_context, haxorg_Subtree self, haxorg_HstdStr kind, haxorg_HstdOpt subkind);
  static void setProperty(OrgContext* org_context, haxorg_Subtree self, haxorg_NamedProperty value);
  static void setPropertyStrValue(OrgContext* org_context, haxorg_Subtree self, haxorg_HstdStr value, haxorg_HstdStr kind, haxorg_HstdOpt subkind);
  static haxorg_HstdStr getCleanTitle_const(OrgContext* org_context, haxorg_Subtree self);
  static haxorg_HstdOpt getTodoKeyword_const(OrgContext* org_context, haxorg_Subtree self);
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
  static bool isDescriptionItem_const(OrgContext* org_context, haxorg_ListItem self);
  static haxorg_HstdOpt getCleanHeader_const(OrgContext* org_context, haxorg_ListItem self);
};

template <>
struct org::bind::c::VTable<haxorg_DocumentOptions, haxorg_DocumentOptions_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdVec getProperties_const(OrgContext* org_context, haxorg_DocumentOptions self, haxorg_HstdStr kind, haxorg_HstdOpt subKind);
  static haxorg_HstdOpt getProperty_const(OrgContext* org_context, haxorg_DocumentOptions self, haxorg_HstdStr kind, haxorg_HstdOpt subKind);
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
  static haxorg_HstdVec getProperties_const(OrgContext* org_context, haxorg_Document self, haxorg_HstdStr kind, haxorg_HstdOpt subKind);
  static haxorg_HstdOpt getProperty_const(OrgContext* org_context, haxorg_Document self, haxorg_HstdStr kind, haxorg_HstdOpt subKind);
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
  static bool isDocument_const(OrgContext* org_context, haxorg_File self);
  static haxorg_FileDocument getDocumentConst_const(OrgContext* org_context, haxorg_File self);
  static haxorg_FileDocument getDocumentMut(OrgContext* org_context, haxorg_File self);
  static bool isAttachment_const(OrgContext* org_context, haxorg_File self);
  static haxorg_FileAttachment getAttachmentConst_const(OrgContext* org_context, haxorg_File self);
  static haxorg_FileAttachment getAttachmentMut(OrgContext* org_context, haxorg_File self);
  static bool isSource_const(OrgContext* org_context, haxorg_File self);
  static haxorg_FileSource getSourceConst_const(OrgContext* org_context, haxorg_File self);
  static haxorg_FileSource getSourceMut(OrgContext* org_context, haxorg_File self);
  static haxorg_FileKind getFileKind_const(OrgContext* org_context, haxorg_File self);
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
  static bool isExample_const(OrgContext* org_context, haxorg_CmdInclude self);
  static haxorg_CmdIncludeExample getExampleConst_const(OrgContext* org_context, haxorg_CmdInclude self);
  static haxorg_CmdIncludeExample getExampleMut(OrgContext* org_context, haxorg_CmdInclude self);
  static bool isExport_const(OrgContext* org_context, haxorg_CmdInclude self);
  static haxorg_CmdIncludeExport getExportConst_const(OrgContext* org_context, haxorg_CmdInclude self);
  static haxorg_CmdIncludeExport getExportMut(OrgContext* org_context, haxorg_CmdInclude self);
  static bool isCustom_const(OrgContext* org_context, haxorg_CmdInclude self);
  static haxorg_CmdIncludeCustom getCustomConst_const(OrgContext* org_context, haxorg_CmdInclude self);
  static haxorg_CmdIncludeCustom getCustomMut(OrgContext* org_context, haxorg_CmdInclude self);
  static bool isSrc_const(OrgContext* org_context, haxorg_CmdInclude self);
  static haxorg_CmdIncludeSrc getSrcConst_const(OrgContext* org_context, haxorg_CmdInclude self);
  static haxorg_CmdIncludeSrc getSrcMut(OrgContext* org_context, haxorg_CmdInclude self);
  static bool isOrgDocument_const(OrgContext* org_context, haxorg_CmdInclude self);
  static haxorg_CmdIncludeOrgDocument getOrgDocumentConst_const(OrgContext* org_context, haxorg_CmdInclude self);
  static haxorg_CmdIncludeOrgDocument getOrgDocumentMut(OrgContext* org_context, haxorg_CmdInclude self);
  static haxorg_CmdIncludeKind getIncludeKind_const(OrgContext* org_context, haxorg_CmdInclude self);
};

template <>
struct org::bind::c::VTable<haxorg_CmdIncludeIncludeBase, haxorg_CmdIncludeIncludeBase_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_CmdIncludeIncludeBase self, haxorg_CmdIncludeIncludeBase other);
};

template <>
struct org::bind::c::VTable<haxorg_CmdIncludeExample, haxorg_CmdIncludeExample_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_CmdIncludeExample self, haxorg_CmdIncludeExample other);
};

template <>
struct org::bind::c::VTable<haxorg_CmdIncludeExport, haxorg_CmdIncludeExport_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_CmdIncludeExport self, haxorg_CmdIncludeExport other);
};

template <>
struct org::bind::c::VTable<haxorg_CmdIncludeCustom, haxorg_CmdIncludeCustom_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_CmdIncludeCustom self, haxorg_CmdIncludeCustom other);
};

template <>
struct org::bind::c::VTable<haxorg_CmdIncludeSrc, haxorg_CmdIncludeSrc_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_CmdIncludeSrc self, haxorg_CmdIncludeSrc other);
};

template <>
struct org::bind::c::VTable<haxorg_CmdIncludeOrgDocument, haxorg_CmdIncludeOrgDocument_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_CmdIncludeOrgDocument self, haxorg_CmdIncludeOrgDocument other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmNoNode, haxorg_ImmNoNode_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmNoNode self, haxorg_ImmNoNode other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmErrorItem, haxorg_ImmErrorItem_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmErrorItem self, haxorg_ImmErrorItem other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmErrorGroup, haxorg_ImmErrorGroup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmErrorGroup self, haxorg_ImmErrorGroup other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmStmt, haxorg_ImmStmt_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmStmt self, haxorg_ImmStmt other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmInline, haxorg_ImmInline_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmInline self, haxorg_ImmInline other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmStmtList, haxorg_ImmStmtList_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmStmtList self, haxorg_ImmStmtList other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmEmpty, haxorg_ImmEmpty_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmEmpty self, haxorg_ImmEmpty other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmLeaf, haxorg_ImmLeaf_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmLeaf self, haxorg_ImmLeaf other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmTime, haxorg_ImmTime_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmTime self, haxorg_ImmTime other);
  static bool isStatic_const(OrgContext* org_context, haxorg_ImmTime self);
  static haxorg_ImmTimeStatic getStaticConst_const(OrgContext* org_context, haxorg_ImmTime self);
  static haxorg_ImmTimeStatic getStaticMut(OrgContext* org_context, haxorg_ImmTime self);
  static bool isDynamic_const(OrgContext* org_context, haxorg_ImmTime self);
  static haxorg_ImmTimeDynamic getDynamicConst_const(OrgContext* org_context, haxorg_ImmTime self);
  static haxorg_ImmTimeDynamic getDynamicMut(OrgContext* org_context, haxorg_ImmTime self);
  static haxorg_ImmTimeTimeKind getTimeKind_const(OrgContext* org_context, haxorg_ImmTime self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmTimeRepeat, haxorg_ImmTimeRepeat_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmTimeRepeat self, haxorg_ImmTimeRepeat other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmTimeStatic, haxorg_ImmTimeStatic_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmTimeStatic self, haxorg_ImmTimeStatic other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmTimeDynamic, haxorg_ImmTimeDynamic_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmTimeDynamic self, haxorg_ImmTimeDynamic other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmTimeRange, haxorg_ImmTimeRange_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmTimeRange self, haxorg_ImmTimeRange other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmMacro, haxorg_ImmMacro_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmMacro self, haxorg_ImmMacro other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmSymbol, haxorg_ImmSymbol_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmSymbol self, haxorg_ImmSymbol other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmSymbolParam, haxorg_ImmSymbolParam_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmSymbolParam self, haxorg_ImmSymbolParam other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmErrorSkipGroup, haxorg_ImmErrorSkipGroup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmErrorSkipGroup self, haxorg_ImmErrorSkipGroup other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmMarkup, haxorg_ImmMarkup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmMarkup self, haxorg_ImmMarkup other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmRadioTarget, haxorg_ImmRadioTarget_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmRadioTarget self, haxorg_ImmRadioTarget other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmLatex, haxorg_ImmLatex_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmLatex self, haxorg_ImmLatex other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmSubtreeLog, haxorg_ImmSubtreeLog_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmSubtreeLog self, haxorg_ImmSubtreeLog other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmSubtree, haxorg_ImmSubtree_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmSubtree self, haxorg_ImmSubtree other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmColonExample, haxorg_ImmColonExample_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmColonExample self, haxorg_ImmColonExample other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCall, haxorg_ImmCall_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCall self, haxorg_ImmCall other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmListItem, haxorg_ImmListItem_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmListItem self, haxorg_ImmListItem other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmDocumentOptions, haxorg_ImmDocumentOptions_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmDocumentOptions self, haxorg_ImmDocumentOptions other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmDocumentFragment, haxorg_ImmDocumentFragment_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmDocumentFragment self, haxorg_ImmDocumentFragment other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCriticMarkup, haxorg_ImmCriticMarkup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCriticMarkup self, haxorg_ImmCriticMarkup other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmDocument, haxorg_ImmDocument_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmDocument self, haxorg_ImmDocument other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmFileTarget, haxorg_ImmFileTarget_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmFileTarget self, haxorg_ImmFileTarget other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmTextSeparator, haxorg_ImmTextSeparator_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmTextSeparator self, haxorg_ImmTextSeparator other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmDocumentGroup, haxorg_ImmDocumentGroup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmDocumentGroup self, haxorg_ImmDocumentGroup other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmFile self, haxorg_ImmFile other);
  static bool isDocument_const(OrgContext* org_context, haxorg_ImmFile self);
  static haxorg_ImmFileDocument getDocumentConst_const(OrgContext* org_context, haxorg_ImmFile self);
  static haxorg_ImmFileDocument getDocumentMut(OrgContext* org_context, haxorg_ImmFile self);
  static bool isAttachment_const(OrgContext* org_context, haxorg_ImmFile self);
  static haxorg_ImmFileAttachment getAttachmentConst_const(OrgContext* org_context, haxorg_ImmFile self);
  static haxorg_ImmFileAttachment getAttachmentMut(OrgContext* org_context, haxorg_ImmFile self);
  static bool isSource_const(OrgContext* org_context, haxorg_ImmFile self);
  static haxorg_ImmFileSource getSourceConst_const(OrgContext* org_context, haxorg_ImmFile self);
  static haxorg_ImmFileSource getSourceMut(OrgContext* org_context, haxorg_ImmFile self);
  static haxorg_ImmFileKind getFileKind_const(OrgContext* org_context, haxorg_ImmFile self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmFileDocument, haxorg_ImmFileDocument_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmFileDocument self, haxorg_ImmFileDocument other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmFileAttachment, haxorg_ImmFileAttachment_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmFileAttachment self, haxorg_ImmFileAttachment other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmFileSource, haxorg_ImmFileSource_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmFileSource self, haxorg_ImmFileSource other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmDirectory, haxorg_ImmDirectory_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmDirectory self, haxorg_ImmDirectory other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmSymlink, haxorg_ImmSymlink_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmSymlink self, haxorg_ImmSymlink other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdInclude self, haxorg_ImmCmdInclude other);
  static bool isExample_const(OrgContext* org_context, haxorg_ImmCmdInclude self);
  static haxorg_ImmCmdIncludeExample getExampleConst_const(OrgContext* org_context, haxorg_ImmCmdInclude self);
  static haxorg_ImmCmdIncludeExample getExampleMut(OrgContext* org_context, haxorg_ImmCmdInclude self);
  static bool isExport_const(OrgContext* org_context, haxorg_ImmCmdInclude self);
  static haxorg_ImmCmdIncludeExport getExportConst_const(OrgContext* org_context, haxorg_ImmCmdInclude self);
  static haxorg_ImmCmdIncludeExport getExportMut(OrgContext* org_context, haxorg_ImmCmdInclude self);
  static bool isCustom_const(OrgContext* org_context, haxorg_ImmCmdInclude self);
  static haxorg_ImmCmdIncludeCustom getCustomConst_const(OrgContext* org_context, haxorg_ImmCmdInclude self);
  static haxorg_ImmCmdIncludeCustom getCustomMut(OrgContext* org_context, haxorg_ImmCmdInclude self);
  static bool isSrc_const(OrgContext* org_context, haxorg_ImmCmdInclude self);
  static haxorg_ImmCmdIncludeSrc getSrcConst_const(OrgContext* org_context, haxorg_ImmCmdInclude self);
  static haxorg_ImmCmdIncludeSrc getSrcMut(OrgContext* org_context, haxorg_ImmCmdInclude self);
  static bool isOrgDocument_const(OrgContext* org_context, haxorg_ImmCmdInclude self);
  static haxorg_ImmCmdIncludeOrgDocument getOrgDocumentConst_const(OrgContext* org_context, haxorg_ImmCmdInclude self);
  static haxorg_ImmCmdIncludeOrgDocument getOrgDocumentMut(OrgContext* org_context, haxorg_ImmCmdInclude self);
  static haxorg_ImmCmdIncludeKind getIncludeKind_const(OrgContext* org_context, haxorg_ImmCmdInclude self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdIncludeIncludeBase, haxorg_ImmCmdIncludeIncludeBase_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdIncludeIncludeBase self, haxorg_ImmCmdIncludeIncludeBase other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdIncludeExample, haxorg_ImmCmdIncludeExample_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdIncludeExample self, haxorg_ImmCmdIncludeExample other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdIncludeExport, haxorg_ImmCmdIncludeExport_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdIncludeExport self, haxorg_ImmCmdIncludeExport other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdIncludeCustom, haxorg_ImmCmdIncludeCustom_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdIncludeCustom self, haxorg_ImmCmdIncludeCustom other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdIncludeSrc, haxorg_ImmCmdIncludeSrc_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdIncludeSrc self, haxorg_ImmCmdIncludeSrc other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdIncludeOrgDocument, haxorg_ImmCmdIncludeOrgDocument_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdIncludeOrgDocument self, haxorg_ImmCmdIncludeOrgDocument other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmAdapterOrgAPI, haxorg_ImmAdapterOrgAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_Cmd, haxorg_Cmd_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdVec getAttrs_const(OrgContext* org_context, haxorg_Cmd self, haxorg_HstdOpt key);
  static haxorg_HstdOpt getFirstAttr_const(OrgContext* org_context, haxorg_Cmd self, haxorg_HstdStr kind);
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
  static bool isFootnoteDefinition_const(OrgContext* org_context, haxorg_Paragraph self);
  static haxorg_HstdOpt getFootnoteName_const(OrgContext* org_context, haxorg_Paragraph self);
  static bool hasAdmonition_const(OrgContext* org_context, haxorg_Paragraph self);
  static haxorg_HstdVec getAdmonitions_const(OrgContext* org_context, haxorg_Paragraph self);
  static haxorg_HstdVec getAdmonitionNodes_const(OrgContext* org_context, haxorg_Paragraph self);
  static bool hasTimestamp_const(OrgContext* org_context, haxorg_Paragraph self);
  static haxorg_HstdVec getTimestamps_const(OrgContext* org_context, haxorg_Paragraph self);
  static haxorg_HstdVec getTimestampNodes_const(OrgContext* org_context, haxorg_Paragraph self);
  static bool hasLeadHashtags_const(OrgContext* org_context, haxorg_Paragraph self);
  static haxorg_HstdVec getLeadHashtags_const(OrgContext* org_context, haxorg_Paragraph self);
  static haxorg_HstdVec getBody_const(OrgContext* org_context, haxorg_Paragraph self);
};

template <>
struct org::bind::c::VTable<haxorg_List, haxorg_List_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdVec getListAttrs_const(OrgContext* org_context, haxorg_List self, haxorg_HstdStr key);
  static haxorg_ListFormattingMode getListFormattingMode_const(OrgContext* org_context, haxorg_List self);
  static bool isDescriptionList_const(OrgContext* org_context, haxorg_List self);
  static bool isNumberedList_const(OrgContext* org_context, haxorg_List self);
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
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmd self, haxorg_ImmCmd other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdCustomRaw, haxorg_ImmCmdCustomRaw_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdCustomRaw self, haxorg_ImmCmdCustomRaw other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdCustomText, haxorg_ImmCmdCustomText_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdCustomText self, haxorg_ImmCmdCustomText other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmLink, haxorg_ImmLink_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmLink self, haxorg_ImmLink other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockComment, haxorg_ImmBlockComment_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmBlockComment self, haxorg_ImmBlockComment other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmParagraph, haxorg_ImmParagraph_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmParagraph self, haxorg_ImmParagraph other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmList, haxorg_ImmList_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmList self, haxorg_ImmList other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmHashTag, haxorg_ImmHashTag_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmHashTag self, haxorg_ImmHashTag other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmInlineFootnote, haxorg_ImmInlineFootnote_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmInlineFootnote self, haxorg_ImmInlineFootnote other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmInlineExport, haxorg_ImmInlineExport_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmInlineExport self, haxorg_ImmInlineExport other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmEscaped, haxorg_ImmEscaped_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmEscaped self, haxorg_ImmEscaped other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmNewline, haxorg_ImmNewline_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmNewline self, haxorg_ImmNewline other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmSpace, haxorg_ImmSpace_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmSpace self, haxorg_ImmSpace other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmWord, haxorg_ImmWord_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmWord self, haxorg_ImmWord other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmAtMention, haxorg_ImmAtMention_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmAtMention self, haxorg_ImmAtMention other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmRawText, haxorg_ImmRawText_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmRawText self, haxorg_ImmRawText other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmPunctuation, haxorg_ImmPunctuation_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmPunctuation self, haxorg_ImmPunctuation other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmPlaceholder, haxorg_ImmPlaceholder_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmPlaceholder self, haxorg_ImmPlaceholder other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBigIdent, haxorg_ImmBigIdent_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmBigIdent self, haxorg_ImmBigIdent other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmTextTarget, haxorg_ImmTextTarget_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmTextTarget self, haxorg_ImmTextTarget other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmErrorSkipToken, haxorg_ImmErrorSkipToken_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmErrorSkipToken self, haxorg_ImmErrorSkipToken other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBold, haxorg_ImmBold_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmBold self, haxorg_ImmBold other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmUnderline, haxorg_ImmUnderline_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmUnderline self, haxorg_ImmUnderline other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmMonospace, haxorg_ImmMonospace_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmMonospace self, haxorg_ImmMonospace other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmMarkQuote, haxorg_ImmMarkQuote_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmMarkQuote self, haxorg_ImmMarkQuote other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmVerbatim, haxorg_ImmVerbatim_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmVerbatim self, haxorg_ImmVerbatim other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmItalic, haxorg_ImmItalic_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmItalic self, haxorg_ImmItalic other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmStrike, haxorg_ImmStrike_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmStrike self, haxorg_ImmStrike other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmPar, haxorg_ImmPar_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmPar self, haxorg_ImmPar other);
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
  static haxorg_StdOptional getFsSubnode_const(OrgContext* org_context, haxorg_ImmAdapterDirectoryAPI self, haxorg_HstdStr name, bool withPath);
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
  static bool __eq___const(OrgContext* org_context, haxorg_ImmBlock self, haxorg_ImmBlock other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmLineCommand, haxorg_ImmLineCommand_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmLineCommand self, haxorg_ImmLineCommand other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdCreator, haxorg_ImmCmdCreator_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdCreator self, haxorg_ImmCmdCreator other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdAuthor, haxorg_ImmCmdAuthor_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdAuthor self, haxorg_ImmCmdAuthor other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdEmail, haxorg_ImmCmdEmail_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdEmail self, haxorg_ImmCmdEmail other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdLanguage, haxorg_ImmCmdLanguage_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdLanguage self, haxorg_ImmCmdLanguage other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdCustomArgs, haxorg_ImmCmdCustomArgs_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdCustomArgs self, haxorg_ImmCmdCustomArgs other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdTblfm, haxorg_ImmCmdTblfm_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdTblfm self, haxorg_ImmCmdTblfm other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCell, haxorg_ImmCell_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCell self, haxorg_ImmCell other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmRow, haxorg_ImmRow_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmRow self, haxorg_ImmRow other);
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
  static haxorg_ImmVec getAttached_const(OrgContext* org_context, haxorg_ImmStmtAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int getLevel_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter self);
  static haxorg_HstdOpt getTreeId_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter self);
  static haxorg_HstdOpt getTodo_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter self);
  static haxorg_HstdOpt getCompletion_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter self);
  static haxorg_HstdOpt getDescription_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter self);
  static haxorg_ImmVec getTags_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter self);
  static haxorg_ImmAdapter getTitle_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter self);
  static haxorg_ImmVec getLogbook_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter self);
  static haxorg_ImmVec getProperties_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter self);
  static haxorg_HstdOpt getClosed_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter self);
  static haxorg_HstdOpt getDeadline_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter self);
  static haxorg_HstdOpt getScheduled_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter self);
  static bool getIsComment_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter self);
  static bool getIsArchived_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter self);
  static haxorg_HstdOpt getPriority_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmNoNodeAdapter, haxorg_ImmNoNodeAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmErrorItemAdapter, haxorg_ImmErrorItemAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_OrgDiagnostics getDiag_const(OrgContext* org_context, haxorg_ImmErrorItemAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmErrorGroupAdapter, haxorg_ImmErrorGroupAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmVec getDiagnostics_const(OrgContext* org_context, haxorg_ImmErrorGroupAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmErrorSkipGroupAdapter, haxorg_ImmErrorSkipGroupAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmVec getSkipped_const(OrgContext* org_context, haxorg_ImmErrorSkipGroupAdapter self);
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
  static bool getIsActive_const(OrgContext* org_context, haxorg_ImmTimeAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmTimeRangeAdapter, haxorg_ImmTimeRangeAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapter getFrom_const(OrgContext* org_context, haxorg_ImmTimeRangeAdapter self);
  static haxorg_ImmAdapter getTo_const(OrgContext* org_context, haxorg_ImmTimeRangeAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmMacroAdapter, haxorg_ImmMacroAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getName_const(OrgContext* org_context, haxorg_ImmMacroAdapter self);
  static haxorg_AttrGroup getAttrs_const(OrgContext* org_context, haxorg_ImmMacroAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmSymbolAdapter, haxorg_ImmSymbolAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getName_const(OrgContext* org_context, haxorg_ImmSymbolAdapter self);
  static haxorg_ImmVec getParameters_const(OrgContext* org_context, haxorg_ImmSymbolAdapter self);
  static haxorg_ImmVec getPositional_const(OrgContext* org_context, haxorg_ImmSymbolAdapter self);
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
  static haxorg_HstdStr getText_const(OrgContext* org_context, haxorg_ImmLeafAdapter self);
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
  static haxorg_SubtreeLogHead getHead_const(OrgContext* org_context, haxorg_ImmSubtreeLogAdapter self);
  static haxorg_HstdOpt getDesc_const(OrgContext* org_context, haxorg_ImmSubtreeLogAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmColonExampleAdapter, haxorg_ImmColonExampleAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmCallAdapter, haxorg_ImmCallAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getName_const(OrgContext* org_context, haxorg_ImmCallAdapter self);
  static haxorg_AttrGroup getAttrs_const(OrgContext* org_context, haxorg_ImmCallAdapter self);
  static bool getIsCommand_const(OrgContext* org_context, haxorg_ImmCallAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmFileAdapter, haxorg_ImmFileAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getRelPath_const(OrgContext* org_context, haxorg_ImmFileAdapter self);
  static haxorg_HstdStr getAbsPath_const(OrgContext* org_context, haxorg_ImmFileAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmDirectoryAdapter, haxorg_ImmDirectoryAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getRelPath_const(OrgContext* org_context, haxorg_ImmDirectoryAdapter self);
  static haxorg_HstdStr getAbsPath_const(OrgContext* org_context, haxorg_ImmDirectoryAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmSymlinkAdapter, haxorg_ImmSymlinkAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool getIsDirectory_const(OrgContext* org_context, haxorg_ImmSymlinkAdapter self);
  static haxorg_HstdStr getAbsPath_const(OrgContext* org_context, haxorg_ImmSymlinkAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmDocumentFragmentAdapter, haxorg_ImmDocumentFragmentAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int getBaseLine_const(OrgContext* org_context, haxorg_ImmDocumentFragmentAdapter self);
  static int getBaseCol_const(OrgContext* org_context, haxorg_ImmDocumentFragmentAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCriticMarkupAdapter, haxorg_ImmCriticMarkupAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmCriticMarkupKind getKind_const(OrgContext* org_context, haxorg_ImmCriticMarkupAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmListItemAdapter, haxorg_ImmListItemAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_CheckboxState getCheckbox_const(OrgContext* org_context, haxorg_ImmListItemAdapter self);
  static haxorg_HstdOpt getHeader_const(OrgContext* org_context, haxorg_ImmListItemAdapter self);
  static haxorg_HstdOpt getBullet_const(OrgContext* org_context, haxorg_ImmListItemAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_InitialSubtreeVisibility getInitialVisibility_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter self);
  static haxorg_ImmVec getProperties_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter self);
  static haxorg_DocumentExportConfig getExportConfig_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter self);
  static haxorg_HstdOpt getFixedWidthSections_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter self);
  static haxorg_HstdOpt getStartupIndented_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter self);
  static haxorg_HstdOpt getCategory_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter self);
  static haxorg_HstdOpt getSetupfile_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter self);
  static haxorg_HstdOpt getMaxSubtreeLevelExport_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter self);
  static haxorg_HstdOpt getColumns_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter self);
  static haxorg_ImmVec getTodoKeywords_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter self);
  static haxorg_ImmVec getDoneKeywords_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdOpt getTitle_const(OrgContext* org_context, haxorg_ImmDocumentAdapter self);
  static haxorg_HstdOpt getAuthor_const(OrgContext* org_context, haxorg_ImmDocumentAdapter self);
  static haxorg_HstdOpt getCreator_const(OrgContext* org_context, haxorg_ImmDocumentAdapter self);
  static haxorg_ImmVec getFiletags_const(OrgContext* org_context, haxorg_ImmDocumentAdapter self);
  static haxorg_HstdOpt getEmail_const(OrgContext* org_context, haxorg_ImmDocumentAdapter self);
  static haxorg_ImmVec getLanguage_const(OrgContext* org_context, haxorg_ImmDocumentAdapter self);
  static haxorg_ImmAdapter getOptions_const(OrgContext* org_context, haxorg_ImmDocumentAdapter self);
  static haxorg_HstdOpt getExportFileName_const(OrgContext* org_context, haxorg_ImmDocumentAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getPath_const(OrgContext* org_context, haxorg_ImmFileTargetAdapter self);
  static haxorg_HstdOpt getLine_const(OrgContext* org_context, haxorg_ImmFileTargetAdapter self);
  static haxorg_HstdOpt getSearchTarget_const(OrgContext* org_context, haxorg_ImmFileTargetAdapter self);
  static bool getRestrictToHeadlines_const(OrgContext* org_context, haxorg_ImmFileTargetAdapter self);
  static haxorg_HstdOpt getTargetId_const(OrgContext* org_context, haxorg_ImmFileTargetAdapter self);
  static haxorg_HstdOpt getRegexp_const(OrgContext* org_context, haxorg_ImmFileTargetAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmTextSeparatorAdapter, haxorg_ImmTextSeparatorAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdIncludeAdapter, haxorg_ImmCmdIncludeAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getPath_const(OrgContext* org_context, haxorg_ImmCmdIncludeAdapter self);
  static haxorg_HstdOpt getFirstLine_const(OrgContext* org_context, haxorg_ImmCmdIncludeAdapter self);
  static haxorg_HstdOpt getLastLine_const(OrgContext* org_context, haxorg_ImmCmdIncludeAdapter self);
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
  static haxorg_HstdOpt getPlacement_const(OrgContext* org_context, haxorg_BlockExport self);
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
  static haxorg_HstdOpt getVariable_const(OrgContext* org_context, haxorg_BlockCode self, haxorg_HstdStr varname);
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
  static bool __eq___const(OrgContext* org_context, haxorg_ImmBlockCenter self, haxorg_ImmBlockCenter other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockQuote, haxorg_ImmBlockQuote_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmBlockQuote self, haxorg_ImmBlockQuote other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockVerse, haxorg_ImmBlockVerse_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmBlockVerse self, haxorg_ImmBlockVerse other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockDynamicFallback, haxorg_ImmBlockDynamicFallback_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmBlockDynamicFallback self, haxorg_ImmBlockDynamicFallback other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockExample, haxorg_ImmBlockExample_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmBlockExample self, haxorg_ImmBlockExample other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockExport, haxorg_ImmBlockExport_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmBlockExport self, haxorg_ImmBlockExport other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockAdmonition, haxorg_ImmBlockAdmonition_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmBlockAdmonition self, haxorg_ImmBlockAdmonition other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockCodeEvalResult, haxorg_ImmBlockCodeEvalResult_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmBlockCodeEvalResult self, haxorg_ImmBlockCodeEvalResult other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockCode, haxorg_ImmBlockCode_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmBlockCode self, haxorg_ImmBlockCode other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmTable, haxorg_ImmTable_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmTable self, haxorg_ImmTable other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmAttached, haxorg_ImmAttached_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmAttached self, haxorg_ImmAttached other);
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
  static haxorg_AttrGroup getAttrs_const(OrgContext* org_context, haxorg_ImmCmdAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdCustomRawAdapter, haxorg_ImmCmdCustomRawAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getName_const(OrgContext* org_context, haxorg_ImmCmdCustomRawAdapter self);
  static bool getIsAttached_const(OrgContext* org_context, haxorg_ImmCmdCustomRawAdapter self);
  static haxorg_HstdStr getText_const(OrgContext* org_context, haxorg_ImmCmdCustomRawAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdCustomTextAdapter, haxorg_ImmCmdCustomTextAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getName_const(OrgContext* org_context, haxorg_ImmCmdCustomTextAdapter self);
  static bool getIsAttached_const(OrgContext* org_context, haxorg_ImmCmdCustomTextAdapter self);
  static haxorg_ImmAdapter getText_const(OrgContext* org_context, haxorg_ImmCmdCustomTextAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmLinkAdapter, haxorg_ImmLinkAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdOpt getDescription_const(OrgContext* org_context, haxorg_ImmLinkAdapter self);
  static haxorg_LinkTarget getTarget_const(OrgContext* org_context, haxorg_ImmLinkAdapter self);
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
  static haxorg_HashTagText getText_const(OrgContext* org_context, haxorg_ImmHashTagAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmInlineFootnoteAdapter, haxorg_ImmInlineFootnoteAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getTag_const(OrgContext* org_context, haxorg_ImmInlineFootnoteAdapter self);
  static haxorg_HstdOpt getDefinition_const(OrgContext* org_context, haxorg_ImmInlineFootnoteAdapter self);
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
  static haxorg_ImmVec getWords_const(OrgContext* org_context, haxorg_ImmRadioTargetAdapter self);
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
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdCaption self, haxorg_ImmCmdCaption other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdColumns, haxorg_ImmCmdColumns_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdColumns self, haxorg_ImmCmdColumns other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdName, haxorg_ImmCmdName_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdName self, haxorg_ImmCmdName other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdCall, haxorg_ImmCmdCall_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdCall self, haxorg_ImmCmdCall other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdAttr, haxorg_ImmCmdAttr_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdAttr self, haxorg_ImmCmdAttr other);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdExport, haxorg_ImmCmdExport_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdExport self, haxorg_ImmCmdExport other);
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
  static haxorg_HstdStr getName_const(OrgContext* org_context, haxorg_ImmCmdCustomArgsAdapter self);
  static bool getIsAttached_const(OrgContext* org_context, haxorg_ImmCmdCustomArgsAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdCreatorAdapter, haxorg_ImmCmdCreatorAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapter getText_const(OrgContext* org_context, haxorg_ImmCmdCreatorAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdAuthorAdapter, haxorg_ImmCmdAuthorAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapter getText_const(OrgContext* org_context, haxorg_ImmCmdAuthorAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdEmailAdapter, haxorg_ImmCmdEmailAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getText_const(OrgContext* org_context, haxorg_ImmCmdEmailAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdLanguageAdapter, haxorg_ImmCmdLanguageAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getText_const(OrgContext* org_context, haxorg_ImmCmdLanguageAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdTblfmAdapter, haxorg_ImmCmdTblfmAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Tblfm getExpr_const(OrgContext* org_context, haxorg_ImmCmdTblfmAdapter self);
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
  static bool getIsBlock_const(OrgContext* org_context, haxorg_ImmCellAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmRowAdapter, haxorg_ImmRowAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmVec getCells_const(OrgContext* org_context, haxorg_ImmRowAdapter self);
  static bool getIsBlock_const(OrgContext* org_context, haxorg_ImmRowAdapter self);
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
  static haxorg_HstdStr getExporter_const(OrgContext* org_context, haxorg_ImmInlineExportAdapter self);
  static haxorg_HstdStr getContent_const(OrgContext* org_context, haxorg_ImmInlineExportAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdExportAdapter, haxorg_ImmCmdExportAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getExporter_const(OrgContext* org_context, haxorg_ImmCmdExportAdapter self);
  static haxorg_HstdStr getContent_const(OrgContext* org_context, haxorg_ImmCmdExportAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockExportAdapter, haxorg_ImmBlockExportAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getExporter_const(OrgContext* org_context, haxorg_ImmBlockExportAdapter self);
  static haxorg_HstdStr getContent_const(OrgContext* org_context, haxorg_ImmBlockExportAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockDynamicFallbackAdapter, haxorg_ImmBlockDynamicFallbackAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getName_const(OrgContext* org_context, haxorg_ImmBlockDynamicFallbackAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockAdmonitionAdapter, haxorg_ImmBlockAdmonitionAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockCodeEvalResultAdapter, haxorg_ImmBlockCodeEvalResultAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmVec getRaw_const(OrgContext* org_context, haxorg_ImmBlockCodeEvalResultAdapter self);
  static haxorg_ImmAdapter getNode_const(OrgContext* org_context, haxorg_ImmBlockCodeEvalResultAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmBlockCodeAdapter, haxorg_ImmBlockCodeAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdOpt getLang_const(OrgContext* org_context, haxorg_ImmBlockCodeAdapter self);
  static haxorg_ImmVec getResult_const(OrgContext* org_context, haxorg_ImmBlockCodeAdapter self);
  static haxorg_ImmVec getLines_const(OrgContext* org_context, haxorg_ImmBlockCodeAdapter self);
  static haxorg_AttrGroup getSwitches_const(OrgContext* org_context, haxorg_ImmBlockCodeAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmTableAdapter, haxorg_ImmTableAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmVec getRows_const(OrgContext* org_context, haxorg_ImmTableAdapter self);
  static bool getIsBlock_const(OrgContext* org_context, haxorg_ImmTableAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdCaptionAdapter, haxorg_ImmCmdCaptionAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapter getText_const(OrgContext* org_context, haxorg_ImmCmdCaptionAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdColumnsAdapter, haxorg_ImmCmdColumnsAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ColumnView getView_const(OrgContext* org_context, haxorg_ImmCmdColumnsAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdNameAdapter, haxorg_ImmCmdNameAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getName_const(OrgContext* org_context, haxorg_ImmCmdNameAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getName_const(OrgContext* org_context, haxorg_ImmCmdCallAdapter self);
  static haxorg_HstdOpt getFileName_const(OrgContext* org_context, haxorg_ImmCmdCallAdapter self);
  static haxorg_AttrGroup getInsideHeaderAttrs_const(OrgContext* org_context, haxorg_ImmCmdCallAdapter self);
  static haxorg_AttrGroup getCallAttrs_const(OrgContext* org_context, haxorg_ImmCmdCallAdapter self);
  static haxorg_AttrGroup getEndHeaderAttrs_const(OrgContext* org_context, haxorg_ImmCmdCallAdapter self);
  static haxorg_ImmVec getResult_const(OrgContext* org_context, haxorg_ImmCmdCallAdapter self);
};

template <>
struct org::bind::c::VTable<haxorg_ImmCmdAttrAdapter, haxorg_ImmCmdAttrAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getTarget_const(OrgContext* org_context, haxorg_ImmCmdAttrAdapter self);
};

/* clang-format on */
