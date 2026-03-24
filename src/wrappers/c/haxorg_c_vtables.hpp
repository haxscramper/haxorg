/* clang-format off */
#pragma once
#include <wrappers/c/haxorg_c.h>
#include <wrappers/c/haxorg_c_utils.hpp>
#include <wrappers/c/haxorg_c_vtables_manual.hpp>
template <>
struct org::bind::c::VTable<hstd::BackwardsIndex, haxorg_BackwardsIndex_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_BackwardsIndex_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::UserTimeBreakdown, haxorg_UserTimeBreakdown_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_UserTimeBreakdown_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::UserTime, haxorg_UserTime_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_UserTimeBreakdown getBreakdown_const(OrgContext* org_context, haxorg_UserTime self);
  static haxorg_StdString format_const(OrgContext* org_context, haxorg_UserTime self);
  static int64_t getTimeDeltaSeconds_const(OrgContext* org_context, haxorg_UserTime self, haxorg_UserTime other);
  static int64_t toUnixTimestamp_const(OrgContext* org_context, haxorg_UserTime self);
  static haxorg_UserTime_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::parse::SourceFileId, haxorg_ParseSourceFileId_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ParseSourceFileId_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::parse::SourceManager, haxorg_ParseSourceManager_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_StdString getPath_const(OrgContext* org_context, haxorg_ParseSourceManager self, haxorg_ParseSourceFileId id);
  static haxorg_ParseSourceFileId getId_const(OrgContext* org_context, haxorg_ParseSourceManager self, haxorg_StdString path);
  static haxorg_StdString getSourceContent_const(OrgContext* org_context, haxorg_ParseSourceManager self, haxorg_ParseSourceFileId id);
  static haxorg_StdString getContentTextForPath_const(OrgContext* org_context, haxorg_ParseSourceManager self, haxorg_StdString path);
  static haxorg_ParseSourceFileId addSource(OrgContext* org_context, haxorg_ParseSourceManager self, haxorg_StdString path, haxorg_StdString content);
  static haxorg_ParseSourceManager_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::parse::SourceLoc, haxorg_ParseSourceLoc_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ParseSourceLoc_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::OrgJson, haxorg_OrgJson_vtable> {
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
  static haxorg_OrgJson_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::SemId, haxorg_SemId_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool isNil_const(OrgContext* org_context, haxorg_SemId self);
  static bool __eq___const(OrgContext* org_context, haxorg_SemId self, haxorg_SemId other);
  static haxorg_SemId Nil(OrgContext* org_context, haxorg_SemId self);
  static haxorg_O get(OrgContext* org_context, haxorg_SemId self);
  static haxorg_O get_const(OrgContext* org_context, haxorg_SemId self);
  static haxorg_SemId asOrg_const(OrgContext* org_context, haxorg_SemId self);
  static haxorg_SemId at(OrgContext* org_context, haxorg_SemId self, int idx);
  static haxorg_SemId at(OrgContext* org_context, haxorg_SemId self, haxorg_BackwardsIndex idx);
  static haxorg_SemId get(OrgContext* org_context, haxorg_SemId self, int idx);
  static haxorg_SemId get(OrgContext* org_context, haxorg_SemId self, haxorg_BackwardsIndex idx);
  static int size_const(OrgContext* org_context, haxorg_SemId self);
  static haxorg_SemId_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Org, haxorg_Org_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_OrgSemKind getKind_const(OrgContext* org_context, haxorg_Org self);
  static void push_back(OrgContext* org_context, haxorg_Org self, haxorg_SemId sub);
  static int size_const(OrgContext* org_context, haxorg_Org self);
  static void insert(OrgContext* org_context, haxorg_Org self, int pos, haxorg_SemId node);
  static haxorg_SemId at_const(OrgContext* org_context, haxorg_Org self, int idx);
  static bool is_const(OrgContext* org_context, haxorg_Org self, haxorg_OrgSemKind kind);
  static haxorg_Org_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::OperationsTracer, haxorg_OperationsTracer_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static void setTraceFileStr(OrgContext* org_context, haxorg_OperationsTracer self, haxorg_StdString outfile, bool overwrite);
  static void sendMessage(OrgContext* org_context, haxorg_OperationsTracer self, haxorg_StdString value, haxorg_StdString function, int line, haxorg_StdString file);
  static haxorg_OperationsTracer_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::ext::Cache, haxorg_Cache_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Cache_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::parse::OrgParseFragment, haxorg_ParseOrgParseFragment_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ParseOrgParseFragment_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::parse::OrgParseParameters, haxorg_OrgParseParameters_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_OrgParseParameters_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::parse::OrgDirectoryParseParameters, haxorg_OrgDirectoryParseParameters_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_OrgDirectoryParseParameters_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::parse::ParseContext, haxorg_ParseContext_vtable> {
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
  static haxorg_ParseContext_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmReflFieldId, haxorg_ImmReflFieldId_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getName_const(OrgContext* org_context, haxorg_ImmReflFieldId self);
  static haxorg_ImmReflFieldId_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmId, haxorg_ImmId_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_OrgSemKind getKind_const(OrgContext* org_context, haxorg_ImmId self);
  static bool is_const(OrgContext* org_context, haxorg_ImmId self, haxorg_OrgSemKind kind);
  static haxorg_ImmIdNodeIdxT getNodeIndex_const(OrgContext* org_context, haxorg_ImmId self);
  static haxorg_StdString getReadableId_const(OrgContext* org_context, haxorg_ImmId self);
  static haxorg_ImmId_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmOrg, haxorg_ImmOrg_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmOrg_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmPathStep, haxorg_ImmPathStep_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmPathStep_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmPath, haxorg_ImmPath_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool empty_const(OrgContext* org_context, haxorg_ImmPath self);
  static haxorg_ImmPath_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmUniqId, haxorg_ImmUniqId_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmUniqId_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAstReplaceEpoch, haxorg_ImmAstReplaceEpoch_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAstReplaceEpoch_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAstContext, haxorg_ImmAstContext_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAstVersion addRoot(OrgContext* org_context, haxorg_ImmAstContext self, haxorg_SemId data);
  static haxorg_ImmAstVersion getEmptyVersion(OrgContext* org_context, haxorg_ImmAstContext self);
  static haxorg_SemId get(OrgContext* org_context, haxorg_ImmAstContext self, haxorg_ImmId id);
  static haxorg_ImmAstContext_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAstVersion, haxorg_ImmAstVersion_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmId getRoot_const(OrgContext* org_context, haxorg_ImmAstVersion self);
  static haxorg_ImmAdapter getRootAdapter_const(OrgContext* org_context, haxorg_ImmAstVersion self);
  static haxorg_ImmAstContext getContext_const(OrgContext* org_context, haxorg_ImmAstVersion self);
  static haxorg_ImmAstReplaceEpoch getEpoch_const(OrgContext* org_context, haxorg_ImmAstVersion self);
  static haxorg_ImmAstVersion_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapter, haxorg_ImmAdapter_vtable> {
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
  static haxorg_ImmAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapter::TreeReprConf, haxorg_ImmAdapterTreeReprConf_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterTreeReprConf_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterVirtualBase, haxorg_ImmAdapterVirtualBase_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterVirtualBase_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::OrgYamlExportOpts, haxorg_OrgYamlExportOpts_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_OrgYamlExportOpts_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::OrgTreeExportOpts, haxorg_OrgTreeExportOpts_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_OrgTreeExportOpts_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::AstTrackingPath, haxorg_AstTrackingPath_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_SemId getParent_const(OrgContext* org_context, haxorg_AstTrackingPath self, int offset);
  static haxorg_SemId getNode_const(OrgContext* org_context, haxorg_AstTrackingPath self);
  static haxorg_AstTrackingPath_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::AstTrackingAlternatives, haxorg_AstTrackingAlternatives_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdVec getAllNodes_const(OrgContext* org_context, haxorg_AstTrackingAlternatives self);
  static haxorg_SemId getNode_const(OrgContext* org_context, haxorg_AstTrackingAlternatives self);
  static haxorg_AstTrackingAlternatives_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::AstTrackingGroup, haxorg_AstTrackingGroup_vtable> {
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
  static haxorg_AstTrackingGroup_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::AstTrackingGroup::RadioTarget, haxorg_AstTrackingGroupRadioTarget_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_AstTrackingGroupRadioTarget_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::AstTrackingGroup::Single, haxorg_AstTrackingGroupSingle_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_AstTrackingGroupSingle_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::AstTrackingGroup::TrackedHashtag, haxorg_AstTrackingGroupTrackedHashtag_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_AstTrackingGroupTrackedHashtag_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::AstTrackingMap, haxorg_AstTrackingMap_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_StdOptional getIdPath_const(OrgContext* org_context, haxorg_AstTrackingMap self, haxorg_HstdStr id);
  static haxorg_StdOptional getNamePath_const(OrgContext* org_context, haxorg_AstTrackingMap self, haxorg_HstdStr id);
  static haxorg_StdOptional getAnchorTarget_const(OrgContext* org_context, haxorg_AstTrackingMap self, haxorg_HstdStr id);
  static haxorg_StdOptional getFootnotePath_const(OrgContext* org_context, haxorg_AstTrackingMap self, haxorg_HstdStr id);
  static haxorg_AstTrackingMap_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::SequenceSegment, haxorg_SequenceSegment_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_SequenceSegment_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::SequenceSegmentGroup, haxorg_SequenceSegmentGroup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_SequenceSegmentGroup_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::SequenceAnnotationTag, haxorg_SequenceAnnotationTag_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_SequenceAnnotationTag_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::SequenceAnnotation, haxorg_SequenceAnnotation_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool isAnnotatedWith_const(OrgContext* org_context, haxorg_SequenceAnnotation self, int groupKind, int segmentKind);
  static haxorg_SequenceAnnotation_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::graph::MapLink, haxorg_GraphMapLink_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_GraphMapLinkRadio getRadio(OrgContext* org_context, haxorg_GraphMapLink self);
  static haxorg_GraphMapLinkRadio getRadio_const(OrgContext* org_context, haxorg_GraphMapLink self);
  static bool isRadio_const(OrgContext* org_context, haxorg_GraphMapLink self);
  static haxorg_GraphMapLinkLink getLink(OrgContext* org_context, haxorg_GraphMapLink self);
  static haxorg_GraphMapLinkLink getLink_const(OrgContext* org_context, haxorg_GraphMapLink self);
  static bool isLink_const(OrgContext* org_context, haxorg_GraphMapLink self);
  static haxorg_GraphMapLinkKind getKind_const(OrgContext* org_context, haxorg_GraphMapLink self);
  static haxorg_GraphMapLink_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::graph::MapLink::Link, haxorg_GraphMapLinkLink_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_GraphMapLinkLink_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::graph::MapLink::Radio, haxorg_GraphMapLinkRadio_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_GraphMapLinkRadio_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::graph::MapNodeProp, haxorg_GraphMapNodeProp_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapter getAdapter_const(OrgContext* org_context, haxorg_GraphMapNodeProp self, haxorg_ImmAstContext context);
  static haxorg_StdOptional getSubtreeId_const(OrgContext* org_context, haxorg_GraphMapNodeProp self, haxorg_ImmAstContext context);
  static haxorg_StdOptional getFootnoteName_const(OrgContext* org_context, haxorg_GraphMapNodeProp self, haxorg_ImmAstContext context);
  static haxorg_GraphMapNodeProp_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::graph::MapEdgeProp, haxorg_GraphMapEdgeProp_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_GraphMapEdgeProp_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::graph::MapNode, haxorg_GraphMapNode_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_GraphMapNode self, haxorg_GraphMapNode other);
  static bool __lt___const(OrgContext* org_context, haxorg_GraphMapNode self, haxorg_GraphMapNode other);
  static haxorg_GraphMapNode_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::graph::MapEdge, haxorg_GraphMapEdge_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_GraphMapEdge_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::graph::MapGraph, haxorg_GraphMapGraph_vtable> {
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
  static haxorg_GraphMapGraph_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::graph::MapConfig, haxorg_GraphMapConfig_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_GraphMapConfig_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::graph::MapGraphState, haxorg_GraphMapGraphState_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_GraphMapGraph getGraph_const(OrgContext* org_context, haxorg_GraphMapGraphState self);
  static haxorg_GraphMapGraphState FromAstContext(OrgContext* org_context, haxorg_GraphMapGraphState self, haxorg_ImmAstContext ast);
  static void registerNode(OrgContext* org_context, haxorg_GraphMapGraphState self, haxorg_GraphMapNodeProp node, haxorg_GraphMapConfig conf);
  static void addNode(OrgContext* org_context, haxorg_GraphMapGraphState self, haxorg_ImmAdapter node, haxorg_GraphMapConfig conf);
  static void addNodeRec(OrgContext* org_context, haxorg_GraphMapGraphState self, haxorg_ImmAstContext ast, haxorg_ImmAdapter node, haxorg_GraphMapConfig conf);
  static haxorg_HstdVec getUnresolvedSubtreeLinks_const(OrgContext* org_context, haxorg_GraphMapGraphState self, haxorg_ImmSubtreeAdapter node, haxorg_GraphMapConfig conf);
  static haxorg_StdOptional getUnresolvedLink_const(OrgContext* org_context, haxorg_GraphMapGraphState self, haxorg_ImmLinkAdapter node, haxorg_GraphMapConfig conf);
  static haxorg_GraphMapGraphState_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::LispCode, haxorg_LispCode_vtable> {
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
  static haxorg_LispCode_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::LispCode::Call, haxorg_LispCodeCall_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LispCodeCall self, haxorg_LispCodeCall other);
  static haxorg_LispCodeCall_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::LispCode::List, haxorg_LispCodeList_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LispCodeList self, haxorg_LispCodeList other);
  static haxorg_LispCodeList_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::LispCode::KeyValue, haxorg_LispCodeKeyValue_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LispCodeKeyValue self, haxorg_LispCodeKeyValue other);
  static haxorg_LispCodeKeyValue_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::LispCode::Number, haxorg_LispCodeNumber_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LispCodeNumber self, haxorg_LispCodeNumber other);
  static haxorg_LispCodeNumber_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::LispCode::Text, haxorg_LispCodeText_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LispCodeText self, haxorg_LispCodeText other);
  static haxorg_LispCodeText_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::LispCode::Ident, haxorg_LispCodeIdent_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LispCodeIdent self, haxorg_LispCodeIdent other);
  static haxorg_LispCodeIdent_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::LispCode::Boolean, haxorg_LispCodeBoolean_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LispCodeBoolean self, haxorg_LispCodeBoolean other);
  static haxorg_LispCodeBoolean_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::LispCode::Real, haxorg_LispCodeReal_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LispCodeReal self, haxorg_LispCodeReal other);
  static haxorg_LispCodeReal_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Tblfm, haxorg_Tblfm_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_Tblfm self, haxorg_Tblfm other);
  static haxorg_Tblfm_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Tblfm::Expr, haxorg_TblfmExpr_vtable> {
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
  static haxorg_TblfmExpr_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Tblfm::Expr::AxisRef, haxorg_TblfmExprAxisRef_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_TblfmExprAxisRef self, haxorg_TblfmExprAxisRef other);
  static haxorg_TblfmExprAxisRef_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Tblfm::Expr::AxisRef::Position, haxorg_TblfmExprAxisRefPosition_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition self, haxorg_TblfmExprAxisRefPosition other);
  static bool isIndex_const(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition self);
  static haxorg_TblfmExprAxisRefPositionIndex getIndexConst_const(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition self);
  static haxorg_TblfmExprAxisRefPositionIndex getIndexMut(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition self);
  static bool isName_const(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition self);
  static haxorg_TblfmExprAxisRefPositionName getNameConst_const(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition self);
  static haxorg_TblfmExprAxisRefPositionName getNameMut(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition self);
  static haxorg_TblfmExprAxisRefPositionKind getKind_const(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition self);
  static haxorg_TblfmExprAxisRefPosition_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Tblfm::Expr::AxisRef::Position::Index, haxorg_TblfmExprAxisRefPositionIndex_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_TblfmExprAxisRefPositionIndex self, haxorg_TblfmExprAxisRefPositionIndex other);
  static haxorg_TblfmExprAxisRefPositionIndex_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Tblfm::Expr::AxisRef::Position::Name, haxorg_TblfmExprAxisRefPositionName_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_TblfmExprAxisRefPositionName self, haxorg_TblfmExprAxisRefPositionName other);
  static haxorg_TblfmExprAxisRefPositionName_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Tblfm::Expr::AxisName, haxorg_TblfmExprAxisName_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_TblfmExprAxisName self, haxorg_TblfmExprAxisName other);
  static haxorg_TblfmExprAxisName_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Tblfm::Expr::IntLiteral, haxorg_TblfmExprIntLiteral_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_TblfmExprIntLiteral self, haxorg_TblfmExprIntLiteral other);
  static haxorg_TblfmExprIntLiteral_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Tblfm::Expr::FloatLiteral, haxorg_TblfmExprFloatLiteral_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_TblfmExprFloatLiteral self, haxorg_TblfmExprFloatLiteral other);
  static haxorg_TblfmExprFloatLiteral_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Tblfm::Expr::RangeRef, haxorg_TblfmExprRangeRef_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_TblfmExprRangeRef self, haxorg_TblfmExprRangeRef other);
  static haxorg_TblfmExprRangeRef_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Tblfm::Expr::Call, haxorg_TblfmExprCall_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_TblfmExprCall self, haxorg_TblfmExprCall other);
  static haxorg_TblfmExprCall_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Tblfm::Expr::Elisp, haxorg_TblfmExprElisp_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_TblfmExprElisp self, haxorg_TblfmExprElisp other);
  static haxorg_TblfmExprElisp_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Tblfm::Assign, haxorg_TblfmAssign_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_TblfmAssign self, haxorg_TblfmAssign other);
  static haxorg_TblfmAssign_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::AttrValue, haxorg_AttrValue_vtable> {
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
  static haxorg_AttrValue_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::AttrValue::DimensionSpan, haxorg_AttrValueDimensionSpan_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_AttrValueDimensionSpan self, haxorg_AttrValueDimensionSpan other);
  static haxorg_AttrValueDimensionSpan_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::AttrValue::TextValue, haxorg_AttrValueTextValue_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_AttrValueTextValue self, haxorg_AttrValueTextValue other);
  static haxorg_AttrValueTextValue_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::AttrValue::FileReference, haxorg_AttrValueFileReference_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_AttrValueFileReference self, haxorg_AttrValueFileReference other);
  static haxorg_AttrValueFileReference_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::AttrValue::LispValue, haxorg_AttrValueLispValue_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_AttrValueLispValue self, haxorg_AttrValueLispValue other);
  static haxorg_AttrValueLispValue_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::HashTagFlat, haxorg_HashTagFlat_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_HashTagFlat self, haxorg_HashTagFlat other);
  static bool __lt___const(OrgContext* org_context, haxorg_HashTagFlat self, haxorg_HashTagFlat other);
  static haxorg_HashTagFlat_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::TodoKeyword, haxorg_TodoKeyword_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_TodoKeyword self, haxorg_TodoKeyword other);
  static haxorg_TodoKeyword_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::HashTagText, haxorg_HashTagText_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_HashTagText self, haxorg_HashTagText other);
  static bool prefixMatch_const(OrgContext* org_context, haxorg_HashTagText self, haxorg_HstdVec prefix);
  static haxorg_HstdVec getFlatHashes_const(OrgContext* org_context, haxorg_HashTagText self, bool withIntermediate);
  static haxorg_HashTagText_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::SubtreePath, haxorg_SubtreePath_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_SubtreePath self, haxorg_SubtreePath other);
  static haxorg_SubtreePath_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::LinkTarget, haxorg_LinkTarget_vtable> {
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
  static haxorg_LinkTarget_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::LinkTarget::Raw, haxorg_LinkTargetRaw_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LinkTargetRaw self, haxorg_LinkTargetRaw other);
  static haxorg_LinkTargetRaw_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::LinkTarget::Id, haxorg_LinkTargetId_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LinkTargetId self, haxorg_LinkTargetId other);
  static haxorg_LinkTargetId_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::LinkTarget::CustomId, haxorg_LinkTargetCustomId_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LinkTargetCustomId self, haxorg_LinkTargetCustomId other);
  static haxorg_LinkTargetCustomId_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::LinkTarget::SubtreeTitle, haxorg_LinkTargetSubtreeTitle_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LinkTargetSubtreeTitle self, haxorg_LinkTargetSubtreeTitle other);
  static haxorg_LinkTargetSubtreeTitle_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::LinkTarget::Person, haxorg_LinkTargetPerson_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LinkTargetPerson self, haxorg_LinkTargetPerson other);
  static haxorg_LinkTargetPerson_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::LinkTarget::UserProtocol, haxorg_LinkTargetUserProtocol_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LinkTargetUserProtocol self, haxorg_LinkTargetUserProtocol other);
  static haxorg_LinkTargetUserProtocol_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::LinkTarget::Internal, haxorg_LinkTargetInternal_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LinkTargetInternal self, haxorg_LinkTargetInternal other);
  static haxorg_LinkTargetInternal_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::LinkTarget::Footnote, haxorg_LinkTargetFootnote_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LinkTargetFootnote self, haxorg_LinkTargetFootnote other);
  static haxorg_LinkTargetFootnote_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::LinkTarget::File, haxorg_LinkTargetFile_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LinkTargetFile self, haxorg_LinkTargetFile other);
  static haxorg_LinkTargetFile_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::LinkTarget::Attachment, haxorg_LinkTargetAttachment_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_LinkTargetAttachment self, haxorg_LinkTargetAttachment other);
  static haxorg_LinkTargetAttachment_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::SubtreeLogHead, haxorg_SubtreeLogHead_vtable> {
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
  static haxorg_SubtreeLogHead_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::SubtreeLogHead::Priority, haxorg_SubtreeLogHeadPriority_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadPriority self, haxorg_SubtreeLogHeadPriority other);
  static haxorg_SubtreeLogHeadPriority_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::SubtreeLogHead::Note, haxorg_SubtreeLogHeadNote_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadNote self, haxorg_SubtreeLogHeadNote other);
  static haxorg_SubtreeLogHeadNote_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::SubtreeLogHead::Refile, haxorg_SubtreeLogHeadRefile_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadRefile self, haxorg_SubtreeLogHeadRefile other);
  static haxorg_SubtreeLogHeadRefile_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::SubtreeLogHead::Clock, haxorg_SubtreeLogHeadClock_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadClock self, haxorg_SubtreeLogHeadClock other);
  static haxorg_SubtreeLogHeadClock_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::SubtreeLogHead::State, haxorg_SubtreeLogHeadState_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadState self, haxorg_SubtreeLogHeadState other);
  static haxorg_SubtreeLogHeadState_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::SubtreeLogHead::Deadline, haxorg_SubtreeLogHeadDeadline_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadDeadline self, haxorg_SubtreeLogHeadDeadline other);
  static haxorg_SubtreeLogHeadDeadline_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::SubtreeLogHead::Schedule, haxorg_SubtreeLogHeadSchedule_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadSchedule self, haxorg_SubtreeLogHeadSchedule other);
  static haxorg_SubtreeLogHeadSchedule_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::SubtreeLogHead::Tag, haxorg_SubtreeLogHeadTag_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadTag self, haxorg_SubtreeLogHeadTag other);
  static haxorg_SubtreeLogHeadTag_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::SubtreeLogHead::Unknown, haxorg_SubtreeLogHeadUnknown_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadUnknown self, haxorg_SubtreeLogHeadUnknown other);
  static haxorg_SubtreeLogHeadUnknown_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::SubtreeCompletion, haxorg_SubtreeCompletion_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_SubtreeCompletion self, haxorg_SubtreeCompletion other);
  static haxorg_SubtreeCompletion_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::AttrList, haxorg_AttrList_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_AttrList self, haxorg_AttrList other);
  static haxorg_AttrList_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::AttrGroup, haxorg_AttrGroup_vtable> {
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
  static haxorg_AttrGroup_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::OrgCodeEvalInput, haxorg_OrgCodeEvalInput_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_OrgCodeEvalInput self, haxorg_OrgCodeEvalInput other);
  static haxorg_HstdOpt getVariable_const(OrgContext* org_context, haxorg_OrgCodeEvalInput self, haxorg_HstdStr name);
  static haxorg_OrgCodeEvalInput_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::OrgCodeEvalInput::Var, haxorg_OrgCodeEvalInputVar_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_OrgCodeEvalInputVar self, haxorg_OrgCodeEvalInputVar other);
  static haxorg_OrgCodeEvalInputVar_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::OrgCodeEvalOutput, haxorg_OrgCodeEvalOutput_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_OrgCodeEvalOutput self, haxorg_OrgCodeEvalOutput other);
  static haxorg_OrgCodeEvalOutput_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::ColumnView, haxorg_ColumnView_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ColumnView self, haxorg_ColumnView other);
  static haxorg_ColumnView_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::ColumnView::Summary, haxorg_ColumnViewSummary_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ColumnViewSummary self, haxorg_ColumnViewSummary other);
  static bool isCheckboxAggregate_const(OrgContext* org_context, haxorg_ColumnViewSummary self);
  static haxorg_ColumnViewSummaryCheckboxAggregate getCheckboxAggregateConst_const(OrgContext* org_context, haxorg_ColumnViewSummary self);
  static haxorg_ColumnViewSummaryCheckboxAggregate getCheckboxAggregateMut(OrgContext* org_context, haxorg_ColumnViewSummary self);
  static bool isMathAggregate_const(OrgContext* org_context, haxorg_ColumnViewSummary self);
  static haxorg_ColumnViewSummaryMathAggregate getMathAggregateConst_const(OrgContext* org_context, haxorg_ColumnViewSummary self);
  static haxorg_ColumnViewSummaryMathAggregate getMathAggregateMut(OrgContext* org_context, haxorg_ColumnViewSummary self);
  static haxorg_ColumnViewSummaryKind getKind_const(OrgContext* org_context, haxorg_ColumnViewSummary self);
  static haxorg_ColumnViewSummary_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::ColumnView::Summary::CheckboxAggregate, haxorg_ColumnViewSummaryCheckboxAggregate_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ColumnViewSummaryCheckboxAggregate self, haxorg_ColumnViewSummaryCheckboxAggregate other);
  static haxorg_ColumnViewSummaryCheckboxAggregate_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::ColumnView::Summary::MathAggregate, haxorg_ColumnViewSummaryMathAggregate_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ColumnViewSummaryMathAggregate self, haxorg_ColumnViewSummaryMathAggregate other);
  static haxorg_ColumnViewSummaryMathAggregate_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::ColumnView::Column, haxorg_ColumnViewColumn_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ColumnViewColumn self, haxorg_ColumnViewColumn other);
  static haxorg_ColumnViewColumn_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::BlockCodeLine, haxorg_BlockCodeLine_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_BlockCodeLine self, haxorg_BlockCodeLine other);
  static haxorg_BlockCodeLine_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::BlockCodeLine::Part, haxorg_BlockCodeLinePart_vtable> {
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
  static haxorg_BlockCodeLinePart_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::BlockCodeLine::Part::Raw, haxorg_BlockCodeLinePartRaw_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_BlockCodeLinePartRaw self, haxorg_BlockCodeLinePartRaw other);
  static haxorg_BlockCodeLinePartRaw_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::BlockCodeLine::Part::Callout, haxorg_BlockCodeLinePartCallout_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_BlockCodeLinePartCallout self, haxorg_BlockCodeLinePartCallout other);
  static haxorg_BlockCodeLinePartCallout_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::BlockCodeLine::Part::Tangle, haxorg_BlockCodeLinePartTangle_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_BlockCodeLinePartTangle self, haxorg_BlockCodeLinePartTangle other);
  static haxorg_BlockCodeLinePartTangle_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::DocumentExportConfig, haxorg_DocumentExportConfig_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_DocumentExportConfig self, haxorg_DocumentExportConfig other);
  static bool isDoExport_const(OrgContext* org_context, haxorg_DocumentExportConfig self);
  static haxorg_DocumentExportConfigDoExport getDoExportConst_const(OrgContext* org_context, haxorg_DocumentExportConfig self);
  static haxorg_DocumentExportConfigDoExport getDoExportMut(OrgContext* org_context, haxorg_DocumentExportConfig self);
  static bool isExportFixed_const(OrgContext* org_context, haxorg_DocumentExportConfig self);
  static haxorg_DocumentExportConfigExportFixed getExportFixedConst_const(OrgContext* org_context, haxorg_DocumentExportConfig self);
  static haxorg_DocumentExportConfigExportFixed getExportFixedMut(OrgContext* org_context, haxorg_DocumentExportConfig self);
  static haxorg_DocumentExportConfigTocExportKind getTocExportKind_const(OrgContext* org_context, haxorg_DocumentExportConfig self);
  static haxorg_DocumentExportConfig_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::DocumentExportConfig::TaskExport, haxorg_DocumentExportConfigTaskExport_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_DocumentExportConfigTaskExport self, haxorg_DocumentExportConfigTaskExport other);
  static haxorg_DocumentExportConfigTaskExport_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::DocumentExportConfig::DoExport, haxorg_DocumentExportConfigDoExport_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_DocumentExportConfigDoExport self, haxorg_DocumentExportConfigDoExport other);
  static haxorg_DocumentExportConfigDoExport_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::DocumentExportConfig::ExportFixed, haxorg_DocumentExportConfigExportFixed_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_DocumentExportConfigExportFixed self, haxorg_DocumentExportConfigExportFixed other);
  static haxorg_DocumentExportConfigExportFixed_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::SubtreePeriod, haxorg_SubtreePeriod_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_SubtreePeriod self, haxorg_SubtreePeriod other);
  static haxorg_SubtreePeriod_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::NamedProperty, haxorg_NamedProperty_vtable> {
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
  static haxorg_NamedProperty_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::NamedProperty::Nonblocking, haxorg_NamedPropertyNonblocking_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyNonblocking self, haxorg_NamedPropertyNonblocking other);
  static haxorg_NamedPropertyNonblocking_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::NamedProperty::ArchiveTime, haxorg_NamedPropertyArchiveTime_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyArchiveTime self, haxorg_NamedPropertyArchiveTime other);
  static haxorg_NamedPropertyArchiveTime_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::NamedProperty::ArchiveFile, haxorg_NamedPropertyArchiveFile_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyArchiveFile self, haxorg_NamedPropertyArchiveFile other);
  static haxorg_NamedPropertyArchiveFile_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::NamedProperty::ArchiveOlpath, haxorg_NamedPropertyArchiveOlpath_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyArchiveOlpath self, haxorg_NamedPropertyArchiveOlpath other);
  static haxorg_NamedPropertyArchiveOlpath_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::NamedProperty::ArchiveTarget, haxorg_NamedPropertyArchiveTarget_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyArchiveTarget self, haxorg_NamedPropertyArchiveTarget other);
  static haxorg_NamedPropertyArchiveTarget_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::NamedProperty::ArchiveCategory, haxorg_NamedPropertyArchiveCategory_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyArchiveCategory self, haxorg_NamedPropertyArchiveCategory other);
  static haxorg_NamedPropertyArchiveCategory_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::NamedProperty::ArchiveTodo, haxorg_NamedPropertyArchiveTodo_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyArchiveTodo self, haxorg_NamedPropertyArchiveTodo other);
  static haxorg_NamedPropertyArchiveTodo_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::NamedProperty::Trigger, haxorg_NamedPropertyTrigger_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyTrigger self, haxorg_NamedPropertyTrigger other);
  static haxorg_NamedPropertyTrigger_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::NamedProperty::ExportLatexClass, haxorg_NamedPropertyExportLatexClass_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyExportLatexClass self, haxorg_NamedPropertyExportLatexClass other);
  static haxorg_NamedPropertyExportLatexClass_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::NamedProperty::CookieData, haxorg_NamedPropertyCookieData_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyCookieData self, haxorg_NamedPropertyCookieData other);
  static haxorg_NamedPropertyCookieData_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::NamedProperty::ExportLatexClassOptions, haxorg_NamedPropertyExportLatexClassOptions_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyExportLatexClassOptions self, haxorg_NamedPropertyExportLatexClassOptions other);
  static haxorg_NamedPropertyExportLatexClassOptions_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::NamedProperty::ExportLatexHeader, haxorg_NamedPropertyExportLatexHeader_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyExportLatexHeader self, haxorg_NamedPropertyExportLatexHeader other);
  static haxorg_NamedPropertyExportLatexHeader_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::NamedProperty::ExportLatexCompiler, haxorg_NamedPropertyExportLatexCompiler_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyExportLatexCompiler self, haxorg_NamedPropertyExportLatexCompiler other);
  static haxorg_NamedPropertyExportLatexCompiler_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::NamedProperty::Ordered, haxorg_NamedPropertyOrdered_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyOrdered self, haxorg_NamedPropertyOrdered other);
  static haxorg_NamedPropertyOrdered_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::NamedProperty::Effort, haxorg_NamedPropertyEffort_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyEffort self, haxorg_NamedPropertyEffort other);
  static haxorg_NamedPropertyEffort_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::NamedProperty::Visibility, haxorg_NamedPropertyVisibility_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyVisibility self, haxorg_NamedPropertyVisibility other);
  static haxorg_NamedPropertyVisibility_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::NamedProperty::ExportOptions, haxorg_NamedPropertyExportOptions_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyExportOptions self, haxorg_NamedPropertyExportOptions other);
  static haxorg_NamedPropertyExportOptions_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::NamedProperty::Blocker, haxorg_NamedPropertyBlocker_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyBlocker self, haxorg_NamedPropertyBlocker other);
  static haxorg_NamedPropertyBlocker_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::NamedProperty::Unnumbered, haxorg_NamedPropertyUnnumbered_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyUnnumbered self, haxorg_NamedPropertyUnnumbered other);
  static haxorg_NamedPropertyUnnumbered_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::NamedProperty::Created, haxorg_NamedPropertyCreated_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyCreated self, haxorg_NamedPropertyCreated other);
  static haxorg_NamedPropertyCreated_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::NamedProperty::RadioId, haxorg_NamedPropertyRadioId_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyRadioId self, haxorg_NamedPropertyRadioId other);
  static haxorg_NamedPropertyRadioId_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::NamedProperty::HashtagDef, haxorg_NamedPropertyHashtagDef_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyHashtagDef self, haxorg_NamedPropertyHashtagDef other);
  static haxorg_NamedPropertyHashtagDef_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::NamedProperty::CustomArgs, haxorg_NamedPropertyCustomArgs_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyCustomArgs self, haxorg_NamedPropertyCustomArgs other);
  static haxorg_NamedPropertyCustomArgs_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::NamedProperty::CustomRaw, haxorg_NamedPropertyCustomRaw_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyCustomRaw self, haxorg_NamedPropertyCustomRaw other);
  static haxorg_NamedPropertyCustomRaw_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::NamedProperty::CustomId, haxorg_NamedPropertyCustomId_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyCustomId self, haxorg_NamedPropertyCustomId other);
  static haxorg_NamedPropertyCustomId_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::NamedProperty::CustomSubtreeJson, haxorg_NamedPropertyCustomSubtreeJson_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyCustomSubtreeJson self, haxorg_NamedPropertyCustomSubtreeJson other);
  static haxorg_NamedPropertyCustomSubtreeJson_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::NamedProperty::CustomSubtreeFlags, haxorg_NamedPropertyCustomSubtreeFlags_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_NamedPropertyCustomSubtreeFlags self, haxorg_NamedPropertyCustomSubtreeFlags other);
  static haxorg_NamedPropertyCustomSubtreeFlags_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::OrgDiagnostics, haxorg_OrgDiagnostics_vtable> {
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
  static haxorg_OrgDiagnostics_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::OrgDiagnostics::ParseTokenError, haxorg_OrgDiagnosticsParseTokenError_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_OrgDiagnosticsParseTokenError self, haxorg_OrgDiagnosticsParseTokenError other);
  static haxorg_OrgDiagnosticsParseTokenError_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::OrgDiagnostics::ParseError, haxorg_OrgDiagnosticsParseError_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_OrgDiagnosticsParseError self, haxorg_OrgDiagnosticsParseError other);
  static haxorg_OrgDiagnosticsParseError_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::OrgDiagnostics::IncludeError, haxorg_OrgDiagnosticsIncludeError_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_OrgDiagnosticsIncludeError self, haxorg_OrgDiagnosticsIncludeError other);
  static haxorg_OrgDiagnosticsIncludeError_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::OrgDiagnostics::ConvertError, haxorg_OrgDiagnosticsConvertError_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_OrgDiagnosticsConvertError self, haxorg_OrgDiagnosticsConvertError other);
  static haxorg_OrgDiagnosticsConvertError_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::OrgDiagnostics::InternalError, haxorg_OrgDiagnosticsInternalError_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_OrgDiagnosticsInternalError self, haxorg_OrgDiagnosticsInternalError other);
  static haxorg_OrgDiagnosticsInternalError_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::NoNode, haxorg_NoNode_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_NoNode_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::ErrorItem, haxorg_ErrorItem_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ErrorItem_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::ErrorGroup, haxorg_ErrorGroup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ErrorGroup_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Stmt, haxorg_Stmt_vtable> {
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
  static haxorg_Stmt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Inline, haxorg_Inline_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Inline_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::StmtList, haxorg_StmtList_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_StmtList_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Empty, haxorg_Empty_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Empty_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Leaf, haxorg_Leaf_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getText_const(OrgContext* org_context, haxorg_Leaf self);
  static haxorg_Leaf_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Time, haxorg_Time_vtable> {
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
  static haxorg_Time_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Time::Repeat, haxorg_TimeRepeat_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_TimeRepeat_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Time::Static, haxorg_TimeStatic_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_TimeStatic_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Time::Dynamic, haxorg_TimeDynamic_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_TimeDynamic_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::TimeRange, haxorg_TimeRange_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdOpt getClockedTimeSeconds_const(OrgContext* org_context, haxorg_TimeRange self);
  static haxorg_TimeRange_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Macro, haxorg_Macro_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Macro_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Symbol, haxorg_Symbol_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Symbol_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Symbol::Param, haxorg_SymbolParam_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_SymbolParam_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::ErrorSkipGroup, haxorg_ErrorSkipGroup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ErrorSkipGroup_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Markup, haxorg_Markup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Markup_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::RadioTarget, haxorg_RadioTarget_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_RadioTarget_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Latex, haxorg_Latex_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Latex_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::SubtreeLog, haxorg_SubtreeLog_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static void setDescription(OrgContext* org_context, haxorg_SubtreeLog self, haxorg_SemId desc);
  static haxorg_SubtreeLog_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Subtree, haxorg_Subtree_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdVec getTimePeriods_const(OrgContext* org_context, haxorg_Subtree self, haxorg_HstdIntSet kinds);
  static haxorg_HstdVec getProperties_const(OrgContext* org_context, haxorg_Subtree self, haxorg_HstdStr kind, haxorg_HstdOpt subkind);
  static haxorg_HstdOpt getProperty_const(OrgContext* org_context, haxorg_Subtree self, haxorg_HstdStr kind, haxorg_HstdOpt subkind);
  static void removeProperty(OrgContext* org_context, haxorg_Subtree self, haxorg_HstdStr kind, haxorg_HstdOpt subkind);
  static void setProperty(OrgContext* org_context, haxorg_Subtree self, haxorg_NamedProperty value);
  static void setPropertyStrValue(OrgContext* org_context, haxorg_Subtree self, haxorg_HstdStr value, haxorg_HstdStr kind, haxorg_HstdOpt subkind);
  static haxorg_HstdStr getCleanTitle_const(OrgContext* org_context, haxorg_Subtree self);
  static haxorg_HstdOpt getTodoKeyword_const(OrgContext* org_context, haxorg_Subtree self);
  static haxorg_Subtree_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::ColonExample, haxorg_ColonExample_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ColonExample_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Call, haxorg_Call_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Call_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::ListItem, haxorg_ListItem_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool isDescriptionItem_const(OrgContext* org_context, haxorg_ListItem self);
  static haxorg_HstdOpt getCleanHeader_const(OrgContext* org_context, haxorg_ListItem self);
  static haxorg_ListItem_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::DocumentOptions, haxorg_DocumentOptions_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdVec getProperties_const(OrgContext* org_context, haxorg_DocumentOptions self, haxorg_HstdStr kind, haxorg_HstdOpt subKind);
  static haxorg_HstdOpt getProperty_const(OrgContext* org_context, haxorg_DocumentOptions self, haxorg_HstdStr kind, haxorg_HstdOpt subKind);
  static haxorg_DocumentOptions_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::DocumentFragment, haxorg_DocumentFragment_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_DocumentFragment_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::CriticMarkup, haxorg_CriticMarkup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_CriticMarkup_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Document, haxorg_Document_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdVec getProperties_const(OrgContext* org_context, haxorg_Document self, haxorg_HstdStr kind, haxorg_HstdOpt subKind);
  static haxorg_HstdOpt getProperty_const(OrgContext* org_context, haxorg_Document self, haxorg_HstdStr kind, haxorg_HstdOpt subKind);
  static haxorg_Document_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::FileTarget, haxorg_FileTarget_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_FileTarget_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::TextSeparator, haxorg_TextSeparator_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_TextSeparator_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::DocumentGroup, haxorg_DocumentGroup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_DocumentGroup_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::File, haxorg_File_vtable> {
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
  static haxorg_File_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::File::Document, haxorg_FileDocument_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_FileDocument_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::File::Attachment, haxorg_FileAttachment_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_FileAttachment_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::File::Source, haxorg_FileSource_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_FileSource_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Directory, haxorg_Directory_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Directory_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Symlink, haxorg_Symlink_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Symlink_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::CmdInclude, haxorg_CmdInclude_vtable> {
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
  static haxorg_CmdInclude_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::CmdInclude::IncludeBase, haxorg_CmdIncludeIncludeBase_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_CmdIncludeIncludeBase_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::CmdInclude::Example, haxorg_CmdIncludeExample_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_CmdIncludeExample_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::CmdInclude::Export, haxorg_CmdIncludeExport_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_CmdIncludeExport_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::CmdInclude::Custom, haxorg_CmdIncludeCustom_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_CmdIncludeCustom_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::CmdInclude::Src, haxorg_CmdIncludeSrc_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_CmdIncludeSrc_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::CmdInclude::OrgDocument, haxorg_CmdIncludeOrgDocument_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_CmdIncludeOrgDocument_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmNoNode, haxorg_ImmNoNode_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmNoNode self, haxorg_ImmNoNode other);
  static haxorg_ImmNoNode_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmErrorItem, haxorg_ImmErrorItem_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmErrorItem self, haxorg_ImmErrorItem other);
  static haxorg_ImmErrorItem_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmErrorGroup, haxorg_ImmErrorGroup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmErrorGroup self, haxorg_ImmErrorGroup other);
  static haxorg_ImmErrorGroup_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmStmt, haxorg_ImmStmt_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmStmt self, haxorg_ImmStmt other);
  static haxorg_ImmStmt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmInline, haxorg_ImmInline_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmInline self, haxorg_ImmInline other);
  static haxorg_ImmInline_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmStmtList, haxorg_ImmStmtList_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmStmtList self, haxorg_ImmStmtList other);
  static haxorg_ImmStmtList_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmEmpty, haxorg_ImmEmpty_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmEmpty self, haxorg_ImmEmpty other);
  static haxorg_ImmEmpty_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmLeaf, haxorg_ImmLeaf_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmLeaf self, haxorg_ImmLeaf other);
  static haxorg_ImmLeaf_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmTime, haxorg_ImmTime_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmTime self, haxorg_ImmTime other);
  static bool isStatic_const(OrgContext* org_context, haxorg_ImmTime self);
  static haxorg_ImmTimeStatic getStaticConst_const(OrgContext* org_context, haxorg_ImmTime self);
  static haxorg_ImmTimeStatic getStaticMut(OrgContext* org_context, haxorg_ImmTime self);
  static bool isDynamic_const(OrgContext* org_context, haxorg_ImmTime self);
  static haxorg_ImmTimeDynamic getDynamicConst_const(OrgContext* org_context, haxorg_ImmTime self);
  static haxorg_ImmTimeDynamic getDynamicMut(OrgContext* org_context, haxorg_ImmTime self);
  static haxorg_ImmTimeTimeKind getTimeKind_const(OrgContext* org_context, haxorg_ImmTime self);
  static haxorg_ImmTime_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmTime::Repeat, haxorg_ImmTimeRepeat_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmTimeRepeat self, haxorg_ImmTimeRepeat other);
  static haxorg_ImmTimeRepeat_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmTime::Static, haxorg_ImmTimeStatic_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmTimeStatic self, haxorg_ImmTimeStatic other);
  static haxorg_ImmTimeStatic_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmTime::Dynamic, haxorg_ImmTimeDynamic_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmTimeDynamic self, haxorg_ImmTimeDynamic other);
  static haxorg_ImmTimeDynamic_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmTimeRange, haxorg_ImmTimeRange_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmTimeRange self, haxorg_ImmTimeRange other);
  static haxorg_ImmTimeRange_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmMacro, haxorg_ImmMacro_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmMacro self, haxorg_ImmMacro other);
  static haxorg_ImmMacro_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmSymbol, haxorg_ImmSymbol_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmSymbol self, haxorg_ImmSymbol other);
  static haxorg_ImmSymbol_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmSymbol::Param, haxorg_ImmSymbolParam_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmSymbolParam self, haxorg_ImmSymbolParam other);
  static haxorg_ImmSymbolParam_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmErrorSkipGroup, haxorg_ImmErrorSkipGroup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmErrorSkipGroup self, haxorg_ImmErrorSkipGroup other);
  static haxorg_ImmErrorSkipGroup_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmMarkup, haxorg_ImmMarkup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmMarkup self, haxorg_ImmMarkup other);
  static haxorg_ImmMarkup_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmRadioTarget, haxorg_ImmRadioTarget_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmRadioTarget self, haxorg_ImmRadioTarget other);
  static haxorg_ImmRadioTarget_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmLatex, haxorg_ImmLatex_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmLatex self, haxorg_ImmLatex other);
  static haxorg_ImmLatex_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmSubtreeLog, haxorg_ImmSubtreeLog_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmSubtreeLog self, haxorg_ImmSubtreeLog other);
  static haxorg_ImmSubtreeLog_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmSubtree, haxorg_ImmSubtree_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmSubtree self, haxorg_ImmSubtree other);
  static haxorg_ImmSubtree_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmColonExample, haxorg_ImmColonExample_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmColonExample self, haxorg_ImmColonExample other);
  static haxorg_ImmColonExample_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmCall, haxorg_ImmCall_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCall self, haxorg_ImmCall other);
  static haxorg_ImmCall_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmListItem, haxorg_ImmListItem_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmListItem self, haxorg_ImmListItem other);
  static haxorg_ImmListItem_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmDocumentOptions, haxorg_ImmDocumentOptions_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmDocumentOptions self, haxorg_ImmDocumentOptions other);
  static haxorg_ImmDocumentOptions_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmDocumentFragment, haxorg_ImmDocumentFragment_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmDocumentFragment self, haxorg_ImmDocumentFragment other);
  static haxorg_ImmDocumentFragment_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmCriticMarkup, haxorg_ImmCriticMarkup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCriticMarkup self, haxorg_ImmCriticMarkup other);
  static haxorg_ImmCriticMarkup_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmDocument, haxorg_ImmDocument_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmDocument self, haxorg_ImmDocument other);
  static haxorg_ImmDocument_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmFileTarget, haxorg_ImmFileTarget_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmFileTarget self, haxorg_ImmFileTarget other);
  static haxorg_ImmFileTarget_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmTextSeparator, haxorg_ImmTextSeparator_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmTextSeparator self, haxorg_ImmTextSeparator other);
  static haxorg_ImmTextSeparator_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmDocumentGroup, haxorg_ImmDocumentGroup_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmDocumentGroup self, haxorg_ImmDocumentGroup other);
  static haxorg_ImmDocumentGroup_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmFile, haxorg_ImmFile_vtable> {
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
  static haxorg_ImmFile_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmFile::Document, haxorg_ImmFileDocument_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmFileDocument self, haxorg_ImmFileDocument other);
  static haxorg_ImmFileDocument_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmFile::Attachment, haxorg_ImmFileAttachment_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmFileAttachment self, haxorg_ImmFileAttachment other);
  static haxorg_ImmFileAttachment_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmFile::Source, haxorg_ImmFileSource_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmFileSource self, haxorg_ImmFileSource other);
  static haxorg_ImmFileSource_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmDirectory, haxorg_ImmDirectory_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmDirectory self, haxorg_ImmDirectory other);
  static haxorg_ImmDirectory_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmSymlink, haxorg_ImmSymlink_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmSymlink self, haxorg_ImmSymlink other);
  static haxorg_ImmSymlink_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmCmdInclude, haxorg_ImmCmdInclude_vtable> {
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
  static haxorg_ImmCmdInclude_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmCmdInclude::IncludeBase, haxorg_ImmCmdIncludeIncludeBase_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdIncludeIncludeBase self, haxorg_ImmCmdIncludeIncludeBase other);
  static haxorg_ImmCmdIncludeIncludeBase_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmCmdInclude::Example, haxorg_ImmCmdIncludeExample_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdIncludeExample self, haxorg_ImmCmdIncludeExample other);
  static haxorg_ImmCmdIncludeExample_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmCmdInclude::Export, haxorg_ImmCmdIncludeExport_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdIncludeExport self, haxorg_ImmCmdIncludeExport other);
  static haxorg_ImmCmdIncludeExport_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmCmdInclude::Custom, haxorg_ImmCmdIncludeCustom_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdIncludeCustom self, haxorg_ImmCmdIncludeCustom other);
  static haxorg_ImmCmdIncludeCustom_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmCmdInclude::Src, haxorg_ImmCmdIncludeSrc_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdIncludeSrc self, haxorg_ImmCmdIncludeSrc other);
  static haxorg_ImmCmdIncludeSrc_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmCmdInclude::OrgDocument, haxorg_ImmCmdIncludeOrgDocument_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdIncludeOrgDocument self, haxorg_ImmCmdIncludeOrgDocument other);
  static haxorg_ImmCmdIncludeOrgDocument_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterOrgAPI, haxorg_ImmAdapterOrgAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterOrgAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Cmd, haxorg_Cmd_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdVec getAttrs_const(OrgContext* org_context, haxorg_Cmd self, haxorg_HstdOpt key);
  static haxorg_HstdOpt getFirstAttr_const(OrgContext* org_context, haxorg_Cmd self, haxorg_HstdStr kind);
  static haxorg_Cmd_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::CmdCustomRaw, haxorg_CmdCustomRaw_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_CmdCustomRaw_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::CmdCustomText, haxorg_CmdCustomText_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_CmdCustomText_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Link, haxorg_Link_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Link_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::BlockComment, haxorg_BlockComment_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_BlockComment_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Paragraph, haxorg_Paragraph_vtable> {
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
  static haxorg_Paragraph_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::List, haxorg_List_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdVec getListAttrs_const(OrgContext* org_context, haxorg_List self, haxorg_HstdStr key);
  static haxorg_ListFormattingMode getListFormattingMode_const(OrgContext* org_context, haxorg_List self);
  static bool isDescriptionList_const(OrgContext* org_context, haxorg_List self);
  static bool isNumberedList_const(OrgContext* org_context, haxorg_List self);
  static haxorg_List_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::HashTag, haxorg_HashTag_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HashTag_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::InlineFootnote, haxorg_InlineFootnote_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_InlineFootnote_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::InlineExport, haxorg_InlineExport_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_InlineExport_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Escaped, haxorg_Escaped_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Escaped_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Newline, haxorg_Newline_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Newline_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Space, haxorg_Space_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Space_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Word, haxorg_Word_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Word_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::AtMention, haxorg_AtMention_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_AtMention_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::RawText, haxorg_RawText_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_RawText_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Punctuation, haxorg_Punctuation_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Punctuation_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Placeholder, haxorg_Placeholder_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Placeholder_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::BigIdent, haxorg_BigIdent_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_BigIdent_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::TextTarget, haxorg_TextTarget_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_TextTarget_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::ErrorSkipToken, haxorg_ErrorSkipToken_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ErrorSkipToken_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Bold, haxorg_Bold_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Bold_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Underline, haxorg_Underline_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Underline_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Monospace, haxorg_Monospace_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Monospace_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::MarkQuote, haxorg_MarkQuote_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_MarkQuote_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Verbatim, haxorg_Verbatim_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Verbatim_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Italic, haxorg_Italic_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Italic_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Strike, haxorg_Strike_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Strike_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Par, haxorg_Par_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Par_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmCmd, haxorg_ImmCmd_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmd self, haxorg_ImmCmd other);
  static haxorg_ImmCmd_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmCmdCustomRaw, haxorg_ImmCmdCustomRaw_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdCustomRaw self, haxorg_ImmCmdCustomRaw other);
  static haxorg_ImmCmdCustomRaw_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmCmdCustomText, haxorg_ImmCmdCustomText_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdCustomText self, haxorg_ImmCmdCustomText other);
  static haxorg_ImmCmdCustomText_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmLink, haxorg_ImmLink_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmLink self, haxorg_ImmLink other);
  static haxorg_ImmLink_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmBlockComment, haxorg_ImmBlockComment_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmBlockComment self, haxorg_ImmBlockComment other);
  static haxorg_ImmBlockComment_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmParagraph, haxorg_ImmParagraph_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmParagraph self, haxorg_ImmParagraph other);
  static haxorg_ImmParagraph_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmList, haxorg_ImmList_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmList self, haxorg_ImmList other);
  static haxorg_ImmList_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmHashTag, haxorg_ImmHashTag_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmHashTag self, haxorg_ImmHashTag other);
  static haxorg_ImmHashTag_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmInlineFootnote, haxorg_ImmInlineFootnote_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmInlineFootnote self, haxorg_ImmInlineFootnote other);
  static haxorg_ImmInlineFootnote_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmInlineExport, haxorg_ImmInlineExport_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmInlineExport self, haxorg_ImmInlineExport other);
  static haxorg_ImmInlineExport_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmEscaped, haxorg_ImmEscaped_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmEscaped self, haxorg_ImmEscaped other);
  static haxorg_ImmEscaped_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmNewline, haxorg_ImmNewline_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmNewline self, haxorg_ImmNewline other);
  static haxorg_ImmNewline_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmSpace, haxorg_ImmSpace_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmSpace self, haxorg_ImmSpace other);
  static haxorg_ImmSpace_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmWord, haxorg_ImmWord_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmWord self, haxorg_ImmWord other);
  static haxorg_ImmWord_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAtMention, haxorg_ImmAtMention_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmAtMention self, haxorg_ImmAtMention other);
  static haxorg_ImmAtMention_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmRawText, haxorg_ImmRawText_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmRawText self, haxorg_ImmRawText other);
  static haxorg_ImmRawText_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmPunctuation, haxorg_ImmPunctuation_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmPunctuation self, haxorg_ImmPunctuation other);
  static haxorg_ImmPunctuation_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmPlaceholder, haxorg_ImmPlaceholder_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmPlaceholder self, haxorg_ImmPlaceholder other);
  static haxorg_ImmPlaceholder_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmBigIdent, haxorg_ImmBigIdent_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmBigIdent self, haxorg_ImmBigIdent other);
  static haxorg_ImmBigIdent_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmTextTarget, haxorg_ImmTextTarget_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmTextTarget self, haxorg_ImmTextTarget other);
  static haxorg_ImmTextTarget_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmErrorSkipToken, haxorg_ImmErrorSkipToken_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmErrorSkipToken self, haxorg_ImmErrorSkipToken other);
  static haxorg_ImmErrorSkipToken_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmBold, haxorg_ImmBold_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmBold self, haxorg_ImmBold other);
  static haxorg_ImmBold_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmUnderline, haxorg_ImmUnderline_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmUnderline self, haxorg_ImmUnderline other);
  static haxorg_ImmUnderline_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmMonospace, haxorg_ImmMonospace_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmMonospace self, haxorg_ImmMonospace other);
  static haxorg_ImmMonospace_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmMarkQuote, haxorg_ImmMarkQuote_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmMarkQuote self, haxorg_ImmMarkQuote other);
  static haxorg_ImmMarkQuote_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmVerbatim, haxorg_ImmVerbatim_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmVerbatim self, haxorg_ImmVerbatim other);
  static haxorg_ImmVerbatim_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmItalic, haxorg_ImmItalic_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmItalic self, haxorg_ImmItalic other);
  static haxorg_ImmItalic_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmStrike, haxorg_ImmStrike_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmStrike self, haxorg_ImmStrike other);
  static haxorg_ImmStrike_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmPar, haxorg_ImmPar_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmPar self, haxorg_ImmPar other);
  static haxorg_ImmPar_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterStmtAPI, haxorg_ImmAdapterStmtAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterStmtAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterSubtreeAPI, haxorg_ImmAdapterSubtreeAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterSubtreeAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterNoNodeAPI, haxorg_ImmAdapterNoNodeAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterNoNodeAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterAttrAPI, haxorg_ImmAdapterAttrAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterAttrAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterAttrListAPI, haxorg_ImmAdapterAttrListAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterAttrListAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterAttrsAPI, haxorg_ImmAdapterAttrsAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterAttrsAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterErrorItemAPI, haxorg_ImmAdapterErrorItemAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterErrorItemAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterErrorGroupAPI, haxorg_ImmAdapterErrorGroupAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterErrorGroupAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterErrorSkipGroupAPI, haxorg_ImmAdapterErrorSkipGroupAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterErrorSkipGroupAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterErrorSkipTokenAPI, haxorg_ImmAdapterErrorSkipTokenAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterErrorSkipTokenAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterStmtListAPI, haxorg_ImmAdapterStmtListAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterStmtListAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterEmptyAPI, haxorg_ImmAdapterEmptyAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterEmptyAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterInlineAPI, haxorg_ImmAdapterInlineAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterInlineAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterTimeAPI, haxorg_ImmAdapterTimeAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterTimeAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterTimeRangeAPI, haxorg_ImmAdapterTimeRangeAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterTimeRangeAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterMacroAPI, haxorg_ImmAdapterMacroAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterMacroAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterSymbolAPI, haxorg_ImmAdapterSymbolAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterSymbolAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterLeafAPI, haxorg_ImmAdapterLeafAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterLeafAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterMarkupAPI, haxorg_ImmAdapterMarkupAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterMarkupAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterLatexAPI, haxorg_ImmAdapterLatexAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterLatexAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterSubtreeLogAPI, haxorg_ImmAdapterSubtreeLogAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterSubtreeLogAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterColonExampleAPI, haxorg_ImmAdapterColonExampleAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterColonExampleAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterCallAPI, haxorg_ImmAdapterCallAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterCallAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterFileAPI, haxorg_ImmAdapterFileAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterFileAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterDirectoryAPI, haxorg_ImmAdapterDirectoryAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_StdOptional getFsSubnode_const(OrgContext* org_context, haxorg_ImmAdapterDirectoryAPI self, haxorg_HstdStr name, bool withPath);
  static haxorg_ImmAdapterDirectoryAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterSymlinkAPI, haxorg_ImmAdapterSymlinkAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterSymlinkAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterDocumentFragmentAPI, haxorg_ImmAdapterDocumentFragmentAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterDocumentFragmentAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterCriticMarkupAPI, haxorg_ImmAdapterCriticMarkupAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterCriticMarkupAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterListItemAPI, haxorg_ImmAdapterListItemAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterListItemAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterDocumentOptionsAPI, haxorg_ImmAdapterDocumentOptionsAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterDocumentOptionsAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterDocumentAPI, haxorg_ImmAdapterDocumentAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterDocumentAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterFileTargetAPI, haxorg_ImmAdapterFileTargetAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterFileTargetAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterTextSeparatorAPI, haxorg_ImmAdapterTextSeparatorAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterTextSeparatorAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterCmdIncludeAPI, haxorg_ImmAdapterCmdIncludeAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterCmdIncludeAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterDocumentGroupAPI, haxorg_ImmAdapterDocumentGroupAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterDocumentGroupAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Block, haxorg_Block_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Block_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::LineCommand, haxorg_LineCommand_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_LineCommand_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::CmdCreator, haxorg_CmdCreator_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_CmdCreator_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::CmdAuthor, haxorg_CmdAuthor_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_CmdAuthor_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::CmdEmail, haxorg_CmdEmail_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_CmdEmail_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::CmdLanguage, haxorg_CmdLanguage_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_CmdLanguage_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::CmdCustomArgs, haxorg_CmdCustomArgs_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_CmdCustomArgs_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::CmdTblfm, haxorg_CmdTblfm_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_CmdTblfm_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Cell, haxorg_Cell_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Cell_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Row, haxorg_Row_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Row_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmBlock, haxorg_ImmBlock_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmBlock self, haxorg_ImmBlock other);
  static haxorg_ImmBlock_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmLineCommand, haxorg_ImmLineCommand_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmLineCommand self, haxorg_ImmLineCommand other);
  static haxorg_ImmLineCommand_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmCmdCreator, haxorg_ImmCmdCreator_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdCreator self, haxorg_ImmCmdCreator other);
  static haxorg_ImmCmdCreator_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmCmdAuthor, haxorg_ImmCmdAuthor_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdAuthor self, haxorg_ImmCmdAuthor other);
  static haxorg_ImmCmdAuthor_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmCmdEmail, haxorg_ImmCmdEmail_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdEmail self, haxorg_ImmCmdEmail other);
  static haxorg_ImmCmdEmail_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmCmdLanguage, haxorg_ImmCmdLanguage_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdLanguage self, haxorg_ImmCmdLanguage other);
  static haxorg_ImmCmdLanguage_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmCmdCustomArgs, haxorg_ImmCmdCustomArgs_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdCustomArgs self, haxorg_ImmCmdCustomArgs other);
  static haxorg_ImmCmdCustomArgs_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmCmdTblfm, haxorg_ImmCmdTblfm_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdTblfm self, haxorg_ImmCmdTblfm other);
  static haxorg_ImmCmdTblfm_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmCell, haxorg_ImmCell_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCell self, haxorg_ImmCell other);
  static haxorg_ImmCell_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmRow, haxorg_ImmRow_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmRow self, haxorg_ImmRow other);
  static haxorg_ImmRow_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterCmdAPI, haxorg_ImmAdapterCmdAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterCmdAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterCmdCustomRawAPI, haxorg_ImmAdapterCmdCustomRawAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterCmdCustomRawAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterCmdCustomTextAPI, haxorg_ImmAdapterCmdCustomTextAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterCmdCustomTextAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterLinkAPI, haxorg_ImmAdapterLinkAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterLinkAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterBlockCommentAPI, haxorg_ImmAdapterBlockCommentAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterBlockCommentAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterParagraphAPI, haxorg_ImmAdapterParagraphAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterParagraphAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterListAPI, haxorg_ImmAdapterListAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterListAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmStmt>, haxorg_ImmStmtAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmVec getAttached_const(OrgContext* org_context, haxorg_ImmStmtAdapter self);
  static haxorg_ImmStmtAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmSubtree>, haxorg_ImmSubtreeAdapter_vtable> {
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
  static haxorg_ImmSubtreeAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmNoNode>, haxorg_ImmNoNodeAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmNoNodeAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmErrorItem>, haxorg_ImmErrorItemAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_OrgDiagnostics getDiag_const(OrgContext* org_context, haxorg_ImmErrorItemAdapter self);
  static haxorg_ImmErrorItemAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmErrorGroup>, haxorg_ImmErrorGroupAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmVec getDiagnostics_const(OrgContext* org_context, haxorg_ImmErrorGroupAdapter self);
  static haxorg_ImmErrorGroupAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmErrorSkipGroup>, haxorg_ImmErrorSkipGroupAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmVec getSkipped_const(OrgContext* org_context, haxorg_ImmErrorSkipGroupAdapter self);
  static haxorg_ImmErrorSkipGroupAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmErrorSkipToken>, haxorg_ImmErrorSkipTokenAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmErrorSkipTokenAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmStmtList>, haxorg_ImmStmtListAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmStmtListAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmEmpty>, haxorg_ImmEmptyAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmEmptyAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterHashTagAPI, haxorg_ImmAdapterHashTagAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterHashTagAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterInlineFootnoteAPI, haxorg_ImmAdapterInlineFootnoteAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterInlineFootnoteAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterSubtreeCompletionAPI, haxorg_ImmAdapterSubtreeCompletionAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterSubtreeCompletionAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmInline>, haxorg_ImmInlineAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmInlineAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmTime>, haxorg_ImmTimeAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool getIsActive_const(OrgContext* org_context, haxorg_ImmTimeAdapter self);
  static haxorg_ImmTimeAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmTimeRange>, haxorg_ImmTimeRangeAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapter getFrom_const(OrgContext* org_context, haxorg_ImmTimeRangeAdapter self);
  static haxorg_ImmAdapter getTo_const(OrgContext* org_context, haxorg_ImmTimeRangeAdapter self);
  static haxorg_ImmTimeRangeAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmMacro>, haxorg_ImmMacroAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getName_const(OrgContext* org_context, haxorg_ImmMacroAdapter self);
  static haxorg_AttrGroup getAttrs_const(OrgContext* org_context, haxorg_ImmMacroAdapter self);
  static haxorg_ImmMacroAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmSymbol>, haxorg_ImmSymbolAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getName_const(OrgContext* org_context, haxorg_ImmSymbolAdapter self);
  static haxorg_ImmVec getParameters_const(OrgContext* org_context, haxorg_ImmSymbolAdapter self);
  static haxorg_ImmVec getPositional_const(OrgContext* org_context, haxorg_ImmSymbolAdapter self);
  static haxorg_ImmSymbolAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterEscapedAPI, haxorg_ImmAdapterEscapedAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterEscapedAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterNewlineAPI, haxorg_ImmAdapterNewlineAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterNewlineAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterSpaceAPI, haxorg_ImmAdapterSpaceAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterSpaceAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterWordAPI, haxorg_ImmAdapterWordAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterWordAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterAtMentionAPI, haxorg_ImmAdapterAtMentionAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterAtMentionAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterRawTextAPI, haxorg_ImmAdapterRawTextAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterRawTextAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterPunctuationAPI, haxorg_ImmAdapterPunctuationAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterPunctuationAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterPlaceholderAPI, haxorg_ImmAdapterPlaceholderAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterPlaceholderAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterBigIdentAPI, haxorg_ImmAdapterBigIdentAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterBigIdentAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterTextTargetAPI, haxorg_ImmAdapterTextTargetAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterTextTargetAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmLeaf>, haxorg_ImmLeafAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getText_const(OrgContext* org_context, haxorg_ImmLeafAdapter self);
  static haxorg_ImmLeafAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterBoldAPI, haxorg_ImmAdapterBoldAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterBoldAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterUnderlineAPI, haxorg_ImmAdapterUnderlineAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterUnderlineAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterMonospaceAPI, haxorg_ImmAdapterMonospaceAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterMonospaceAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterMarkQuoteAPI, haxorg_ImmAdapterMarkQuoteAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterMarkQuoteAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterRadioTargetAPI, haxorg_ImmAdapterRadioTargetAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterRadioTargetAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterVerbatimAPI, haxorg_ImmAdapterVerbatimAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterVerbatimAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterItalicAPI, haxorg_ImmAdapterItalicAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterItalicAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterStrikeAPI, haxorg_ImmAdapterStrikeAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterStrikeAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterParAPI, haxorg_ImmAdapterParAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterParAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmMarkup>, haxorg_ImmMarkupAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmMarkupAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmLatex>, haxorg_ImmLatexAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmLatexAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>, haxorg_ImmSubtreeLogAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_SubtreeLogHead getHead_const(OrgContext* org_context, haxorg_ImmSubtreeLogAdapter self);
  static haxorg_HstdOpt getDesc_const(OrgContext* org_context, haxorg_ImmSubtreeLogAdapter self);
  static haxorg_ImmSubtreeLogAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmColonExample>, haxorg_ImmColonExampleAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmColonExampleAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmCall>, haxorg_ImmCallAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getName_const(OrgContext* org_context, haxorg_ImmCallAdapter self);
  static haxorg_AttrGroup getAttrs_const(OrgContext* org_context, haxorg_ImmCallAdapter self);
  static bool getIsCommand_const(OrgContext* org_context, haxorg_ImmCallAdapter self);
  static haxorg_ImmCallAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmFile>, haxorg_ImmFileAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getRelPath_const(OrgContext* org_context, haxorg_ImmFileAdapter self);
  static haxorg_HstdStr getAbsPath_const(OrgContext* org_context, haxorg_ImmFileAdapter self);
  static haxorg_ImmFileAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmDirectory>, haxorg_ImmDirectoryAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getRelPath_const(OrgContext* org_context, haxorg_ImmDirectoryAdapter self);
  static haxorg_HstdStr getAbsPath_const(OrgContext* org_context, haxorg_ImmDirectoryAdapter self);
  static haxorg_ImmDirectoryAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmSymlink>, haxorg_ImmSymlinkAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool getIsDirectory_const(OrgContext* org_context, haxorg_ImmSymlinkAdapter self);
  static haxorg_HstdStr getAbsPath_const(OrgContext* org_context, haxorg_ImmSymlinkAdapter self);
  static haxorg_ImmSymlinkAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>, haxorg_ImmDocumentFragmentAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int getBaseLine_const(OrgContext* org_context, haxorg_ImmDocumentFragmentAdapter self);
  static int getBaseCol_const(OrgContext* org_context, haxorg_ImmDocumentFragmentAdapter self);
  static haxorg_ImmDocumentFragmentAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>, haxorg_ImmCriticMarkupAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmCriticMarkupKind getKind_const(OrgContext* org_context, haxorg_ImmCriticMarkupAdapter self);
  static haxorg_ImmCriticMarkupAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmListItem>, haxorg_ImmListItemAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_CheckboxState getCheckbox_const(OrgContext* org_context, haxorg_ImmListItemAdapter self);
  static haxorg_HstdOpt getHeader_const(OrgContext* org_context, haxorg_ImmListItemAdapter self);
  static haxorg_HstdOpt getBullet_const(OrgContext* org_context, haxorg_ImmListItemAdapter self);
  static haxorg_ImmListItemAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>, haxorg_ImmDocumentOptionsAdapter_vtable> {
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
  static haxorg_ImmDocumentOptionsAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmDocument>, haxorg_ImmDocumentAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdOpt getTitle_const(OrgContext* org_context, haxorg_ImmDocumentAdapter self);
  static haxorg_HstdOpt getAuthor_const(OrgContext* org_context, haxorg_ImmDocumentAdapter self);
  static haxorg_HstdOpt getCreator_const(OrgContext* org_context, haxorg_ImmDocumentAdapter self);
  static haxorg_ImmVec getFiletags_const(OrgContext* org_context, haxorg_ImmDocumentAdapter self);
  static haxorg_HstdOpt getEmail_const(OrgContext* org_context, haxorg_ImmDocumentAdapter self);
  static haxorg_ImmVec getLanguage_const(OrgContext* org_context, haxorg_ImmDocumentAdapter self);
  static haxorg_ImmAdapter getOptions_const(OrgContext* org_context, haxorg_ImmDocumentAdapter self);
  static haxorg_HstdOpt getExportFileName_const(OrgContext* org_context, haxorg_ImmDocumentAdapter self);
  static haxorg_ImmDocumentAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmFileTarget>, haxorg_ImmFileTargetAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getPath_const(OrgContext* org_context, haxorg_ImmFileTargetAdapter self);
  static haxorg_HstdOpt getLine_const(OrgContext* org_context, haxorg_ImmFileTargetAdapter self);
  static haxorg_HstdOpt getSearchTarget_const(OrgContext* org_context, haxorg_ImmFileTargetAdapter self);
  static bool getRestrictToHeadlines_const(OrgContext* org_context, haxorg_ImmFileTargetAdapter self);
  static haxorg_HstdOpt getTargetId_const(OrgContext* org_context, haxorg_ImmFileTargetAdapter self);
  static haxorg_HstdOpt getRegexp_const(OrgContext* org_context, haxorg_ImmFileTargetAdapter self);
  static haxorg_ImmFileTargetAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmTextSeparator>, haxorg_ImmTextSeparatorAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmTextSeparatorAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmCmdInclude>, haxorg_ImmCmdIncludeAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getPath_const(OrgContext* org_context, haxorg_ImmCmdIncludeAdapter self);
  static haxorg_HstdOpt getFirstLine_const(OrgContext* org_context, haxorg_ImmCmdIncludeAdapter self);
  static haxorg_HstdOpt getLastLine_const(OrgContext* org_context, haxorg_ImmCmdIncludeAdapter self);
  static haxorg_ImmCmdIncludeAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmDocumentGroup>, haxorg_ImmDocumentGroupAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmDocumentGroupAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::BlockCenter, haxorg_BlockCenter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_BlockCenter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::BlockQuote, haxorg_BlockQuote_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_BlockQuote_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::BlockVerse, haxorg_BlockVerse_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_BlockVerse_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::BlockDynamicFallback, haxorg_BlockDynamicFallback_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_BlockDynamicFallback_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::BlockExample, haxorg_BlockExample_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_BlockExample_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::BlockExport, haxorg_BlockExport_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdOpt getPlacement_const(OrgContext* org_context, haxorg_BlockExport self);
  static haxorg_BlockExport_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::BlockAdmonition, haxorg_BlockAdmonition_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_BlockAdmonition_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::BlockCodeEvalResult, haxorg_BlockCodeEvalResult_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_BlockCodeEvalResult_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::BlockCode, haxorg_BlockCode_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdOpt getVariable_const(OrgContext* org_context, haxorg_BlockCode self, haxorg_HstdStr varname);
  static haxorg_BlockCode_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Table, haxorg_Table_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Table_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::Attached, haxorg_Attached_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Attached_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmBlockCenter, haxorg_ImmBlockCenter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmBlockCenter self, haxorg_ImmBlockCenter other);
  static haxorg_ImmBlockCenter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmBlockQuote, haxorg_ImmBlockQuote_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmBlockQuote self, haxorg_ImmBlockQuote other);
  static haxorg_ImmBlockQuote_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmBlockVerse, haxorg_ImmBlockVerse_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmBlockVerse self, haxorg_ImmBlockVerse other);
  static haxorg_ImmBlockVerse_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmBlockDynamicFallback, haxorg_ImmBlockDynamicFallback_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmBlockDynamicFallback self, haxorg_ImmBlockDynamicFallback other);
  static haxorg_ImmBlockDynamicFallback_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmBlockExample, haxorg_ImmBlockExample_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmBlockExample self, haxorg_ImmBlockExample other);
  static haxorg_ImmBlockExample_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmBlockExport, haxorg_ImmBlockExport_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmBlockExport self, haxorg_ImmBlockExport other);
  static haxorg_ImmBlockExport_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmBlockAdmonition, haxorg_ImmBlockAdmonition_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmBlockAdmonition self, haxorg_ImmBlockAdmonition other);
  static haxorg_ImmBlockAdmonition_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmBlockCodeEvalResult, haxorg_ImmBlockCodeEvalResult_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmBlockCodeEvalResult self, haxorg_ImmBlockCodeEvalResult other);
  static haxorg_ImmBlockCodeEvalResult_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmBlockCode, haxorg_ImmBlockCode_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmBlockCode self, haxorg_ImmBlockCode other);
  static haxorg_ImmBlockCode_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmTable, haxorg_ImmTable_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmTable self, haxorg_ImmTable other);
  static haxorg_ImmTable_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAttached, haxorg_ImmAttached_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmAttached self, haxorg_ImmAttached other);
  static haxorg_ImmAttached_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterLineCommandAPI, haxorg_ImmAdapterLineCommandAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterLineCommandAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterCmdCustomArgsAPI, haxorg_ImmAdapterCmdCustomArgsAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterCmdCustomArgsAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterCmdCreatorAPI, haxorg_ImmAdapterCmdCreatorAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterCmdCreatorAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterCmdAuthorAPI, haxorg_ImmAdapterCmdAuthorAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterCmdAuthorAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterCmdEmailAPI, haxorg_ImmAdapterCmdEmailAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterCmdEmailAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterCmdLanguageAPI, haxorg_ImmAdapterCmdLanguageAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterCmdLanguageAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterCmdTblfmAPI, haxorg_ImmAdapterCmdTblfmAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterCmdTblfmAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterBlockAPI, haxorg_ImmAdapterBlockAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterBlockAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterCellAPI, haxorg_ImmAdapterCellAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterCellAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterRowAPI, haxorg_ImmAdapterRowAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterRowAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmCmd>, haxorg_ImmCmdAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_AttrGroup getAttrs_const(OrgContext* org_context, haxorg_ImmCmdAdapter self);
  static haxorg_ImmCmdAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>, haxorg_ImmCmdCustomRawAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getName_const(OrgContext* org_context, haxorg_ImmCmdCustomRawAdapter self);
  static bool getIsAttached_const(OrgContext* org_context, haxorg_ImmCmdCustomRawAdapter self);
  static haxorg_HstdStr getText_const(OrgContext* org_context, haxorg_ImmCmdCustomRawAdapter self);
  static haxorg_ImmCmdCustomRawAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>, haxorg_ImmCmdCustomTextAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getName_const(OrgContext* org_context, haxorg_ImmCmdCustomTextAdapter self);
  static bool getIsAttached_const(OrgContext* org_context, haxorg_ImmCmdCustomTextAdapter self);
  static haxorg_ImmAdapter getText_const(OrgContext* org_context, haxorg_ImmCmdCustomTextAdapter self);
  static haxorg_ImmCmdCustomTextAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmLink>, haxorg_ImmLinkAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdOpt getDescription_const(OrgContext* org_context, haxorg_ImmLinkAdapter self);
  static haxorg_LinkTarget getTarget_const(OrgContext* org_context, haxorg_ImmLinkAdapter self);
  static haxorg_ImmLinkAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmBlockComment>, haxorg_ImmBlockCommentAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmBlockCommentAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmParagraph>, haxorg_ImmParagraphAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmParagraphAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmList>, haxorg_ImmListAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmListAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmHashTag>, haxorg_ImmHashTagAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HashTagText getText_const(OrgContext* org_context, haxorg_ImmHashTagAdapter self);
  static haxorg_ImmHashTagAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>, haxorg_ImmInlineFootnoteAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getTag_const(OrgContext* org_context, haxorg_ImmInlineFootnoteAdapter self);
  static haxorg_HstdOpt getDefinition_const(OrgContext* org_context, haxorg_ImmInlineFootnoteAdapter self);
  static haxorg_ImmInlineFootnoteAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmEscaped>, haxorg_ImmEscapedAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmEscapedAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmNewline>, haxorg_ImmNewlineAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmNewlineAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmSpace>, haxorg_ImmSpaceAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmSpaceAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmWord>, haxorg_ImmWordAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmWordAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmAtMention>, haxorg_ImmAtMentionAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAtMentionAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmRawText>, haxorg_ImmRawTextAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmRawTextAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmPunctuation>, haxorg_ImmPunctuationAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmPunctuationAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmPlaceholder>, haxorg_ImmPlaceholderAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmPlaceholderAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmBigIdent>, haxorg_ImmBigIdentAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmBigIdentAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmTextTarget>, haxorg_ImmTextTargetAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmTextTargetAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmBold>, haxorg_ImmBoldAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmBoldAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmUnderline>, haxorg_ImmUnderlineAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmUnderlineAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmMonospace>, haxorg_ImmMonospaceAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmMonospaceAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmMarkQuote>, haxorg_ImmMarkQuoteAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmMarkQuoteAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmRadioTarget>, haxorg_ImmRadioTargetAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmVec getWords_const(OrgContext* org_context, haxorg_ImmRadioTargetAdapter self);
  static haxorg_ImmRadioTargetAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmVerbatim>, haxorg_ImmVerbatimAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmVerbatimAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmItalic>, haxorg_ImmItalicAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmItalicAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmStrike>, haxorg_ImmStrikeAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmStrikeAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmPar>, haxorg_ImmParAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmParAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::CmdCaption, haxorg_CmdCaption_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_CmdCaption_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::CmdColumns, haxorg_CmdColumns_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_CmdColumns_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::CmdName, haxorg_CmdName_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_CmdName_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::CmdCall, haxorg_CmdCall_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_CmdCall_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::CmdAttr, haxorg_CmdAttr_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_CmdAttr_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::sem::CmdExport, haxorg_CmdExport_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_CmdExport_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmCmdCaption, haxorg_ImmCmdCaption_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdCaption self, haxorg_ImmCmdCaption other);
  static haxorg_ImmCmdCaption_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmCmdColumns, haxorg_ImmCmdColumns_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdColumns self, haxorg_ImmCmdColumns other);
  static haxorg_ImmCmdColumns_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmCmdName, haxorg_ImmCmdName_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdName self, haxorg_ImmCmdName other);
  static haxorg_ImmCmdName_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmCmdCall, haxorg_ImmCmdCall_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdCall self, haxorg_ImmCmdCall other);
  static haxorg_ImmCmdCall_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmCmdAttr, haxorg_ImmCmdAttr_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdAttr self, haxorg_ImmCmdAttr other);
  static haxorg_ImmCmdAttr_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmCmdExport, haxorg_ImmCmdExport_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool __eq___const(OrgContext* org_context, haxorg_ImmCmdExport self, haxorg_ImmCmdExport other);
  static haxorg_ImmCmdExport_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterAttachedAPI, haxorg_ImmAdapterAttachedAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterAttachedAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmLineCommand>, haxorg_ImmLineCommandAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmLineCommandAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>, haxorg_ImmCmdCustomArgsAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getName_const(OrgContext* org_context, haxorg_ImmCmdCustomArgsAdapter self);
  static bool getIsAttached_const(OrgContext* org_context, haxorg_ImmCmdCustomArgsAdapter self);
  static haxorg_ImmCmdCustomArgsAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmCmdCreator>, haxorg_ImmCmdCreatorAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapter getText_const(OrgContext* org_context, haxorg_ImmCmdCreatorAdapter self);
  static haxorg_ImmCmdCreatorAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmCmdAuthor>, haxorg_ImmCmdAuthorAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapter getText_const(OrgContext* org_context, haxorg_ImmCmdAuthorAdapter self);
  static haxorg_ImmCmdAuthorAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmCmdEmail>, haxorg_ImmCmdEmailAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getText_const(OrgContext* org_context, haxorg_ImmCmdEmailAdapter self);
  static haxorg_ImmCmdEmailAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmCmdLanguage>, haxorg_ImmCmdLanguageAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getText_const(OrgContext* org_context, haxorg_ImmCmdLanguageAdapter self);
  static haxorg_ImmCmdLanguageAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>, haxorg_ImmCmdTblfmAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Tblfm getExpr_const(OrgContext* org_context, haxorg_ImmCmdTblfmAdapter self);
  static haxorg_ImmCmdTblfmAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterBlockCenterAPI, haxorg_ImmAdapterBlockCenterAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterBlockCenterAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterBlockQuoteAPI, haxorg_ImmAdapterBlockQuoteAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterBlockQuoteAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterBlockVerseAPI, haxorg_ImmAdapterBlockVerseAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterBlockVerseAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterBlockExampleAPI, haxorg_ImmAdapterBlockExampleAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterBlockExampleAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterInlineExportAPI, haxorg_ImmAdapterInlineExportAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterInlineExportAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterCmdExportAPI, haxorg_ImmAdapterCmdExportAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterCmdExportAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterBlockExportAPI, haxorg_ImmAdapterBlockExportAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterBlockExportAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterBlockDynamicFallbackAPI, haxorg_ImmAdapterBlockDynamicFallbackAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterBlockDynamicFallbackAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterBlockAdmonitionAPI, haxorg_ImmAdapterBlockAdmonitionAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterBlockAdmonitionAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterBlockCodeEvalResultAPI, haxorg_ImmAdapterBlockCodeEvalResultAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterBlockCodeEvalResultAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterBlockCodeAPI, haxorg_ImmAdapterBlockCodeAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterBlockCodeAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterTableAPI, haxorg_ImmAdapterTableAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterTableAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmBlock>, haxorg_ImmBlockAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmBlockAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmCell>, haxorg_ImmCellAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool getIsBlock_const(OrgContext* org_context, haxorg_ImmCellAdapter self);
  static haxorg_ImmCellAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmRow>, haxorg_ImmRowAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmVec getCells_const(OrgContext* org_context, haxorg_ImmRowAdapter self);
  static bool getIsBlock_const(OrgContext* org_context, haxorg_ImmRowAdapter self);
  static haxorg_ImmRowAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterCmdCaptionAPI, haxorg_ImmAdapterCmdCaptionAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterCmdCaptionAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterCmdColumnsAPI, haxorg_ImmAdapterCmdColumnsAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterCmdColumnsAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterCmdNameAPI, haxorg_ImmAdapterCmdNameAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterCmdNameAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterCmdCallAPI, haxorg_ImmAdapterCmdCallAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterCmdCallAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterCmdResultsAPI, haxorg_ImmAdapterCmdResultsAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterCmdResultsAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterCmdAttrAPI, haxorg_ImmAdapterCmdAttrAPI_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapterCmdAttrAPI_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmAttached>, haxorg_ImmAttachedAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAttachedAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmBlockCenter>, haxorg_ImmBlockCenterAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmBlockCenterAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmBlockQuote>, haxorg_ImmBlockQuoteAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmBlockQuoteAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmBlockVerse>, haxorg_ImmBlockVerseAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmBlockVerseAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmBlockExample>, haxorg_ImmBlockExampleAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmBlockExampleAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmInlineExport>, haxorg_ImmInlineExportAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getExporter_const(OrgContext* org_context, haxorg_ImmInlineExportAdapter self);
  static haxorg_HstdStr getContent_const(OrgContext* org_context, haxorg_ImmInlineExportAdapter self);
  static haxorg_ImmInlineExportAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmCmdExport>, haxorg_ImmCmdExportAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getExporter_const(OrgContext* org_context, haxorg_ImmCmdExportAdapter self);
  static haxorg_HstdStr getContent_const(OrgContext* org_context, haxorg_ImmCmdExportAdapter self);
  static haxorg_ImmCmdExportAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmBlockExport>, haxorg_ImmBlockExportAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getExporter_const(OrgContext* org_context, haxorg_ImmBlockExportAdapter self);
  static haxorg_HstdStr getContent_const(OrgContext* org_context, haxorg_ImmBlockExportAdapter self);
  static haxorg_ImmBlockExportAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>, haxorg_ImmBlockDynamicFallbackAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getName_const(OrgContext* org_context, haxorg_ImmBlockDynamicFallbackAdapter self);
  static haxorg_ImmBlockDynamicFallbackAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition>, haxorg_ImmBlockAdmonitionAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmBlockAdmonitionAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>, haxorg_ImmBlockCodeEvalResultAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmVec getRaw_const(OrgContext* org_context, haxorg_ImmBlockCodeEvalResultAdapter self);
  static haxorg_ImmAdapter getNode_const(OrgContext* org_context, haxorg_ImmBlockCodeEvalResultAdapter self);
  static haxorg_ImmBlockCodeEvalResultAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmBlockCode>, haxorg_ImmBlockCodeAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdOpt getLang_const(OrgContext* org_context, haxorg_ImmBlockCodeAdapter self);
  static haxorg_ImmVec getResult_const(OrgContext* org_context, haxorg_ImmBlockCodeAdapter self);
  static haxorg_ImmVec getLines_const(OrgContext* org_context, haxorg_ImmBlockCodeAdapter self);
  static haxorg_AttrGroup getSwitches_const(OrgContext* org_context, haxorg_ImmBlockCodeAdapter self);
  static haxorg_ImmBlockCodeAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmTable>, haxorg_ImmTableAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmVec getRows_const(OrgContext* org_context, haxorg_ImmTableAdapter self);
  static bool getIsBlock_const(OrgContext* org_context, haxorg_ImmTableAdapter self);
  static haxorg_ImmTableAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmCmdCaption>, haxorg_ImmCmdCaptionAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmAdapter getText_const(OrgContext* org_context, haxorg_ImmCmdCaptionAdapter self);
  static haxorg_ImmCmdCaptionAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmCmdColumns>, haxorg_ImmCmdColumnsAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ColumnView getView_const(OrgContext* org_context, haxorg_ImmCmdColumnsAdapter self);
  static haxorg_ImmCmdColumnsAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmCmdName>, haxorg_ImmCmdNameAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getName_const(OrgContext* org_context, haxorg_ImmCmdNameAdapter self);
  static haxorg_ImmCmdNameAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmCmdCall>, haxorg_ImmCmdCallAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getName_const(OrgContext* org_context, haxorg_ImmCmdCallAdapter self);
  static haxorg_HstdOpt getFileName_const(OrgContext* org_context, haxorg_ImmCmdCallAdapter self);
  static haxorg_AttrGroup getInsideHeaderAttrs_const(OrgContext* org_context, haxorg_ImmCmdCallAdapter self);
  static haxorg_AttrGroup getCallAttrs_const(OrgContext* org_context, haxorg_ImmCmdCallAdapter self);
  static haxorg_AttrGroup getEndHeaderAttrs_const(OrgContext* org_context, haxorg_ImmCmdCallAdapter self);
  static haxorg_ImmVec getResult_const(OrgContext* org_context, haxorg_ImmCmdCallAdapter self);
  static haxorg_ImmCmdCallAdapter_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<org::imm::ImmAdapterT<org::imm::ImmCmdAttr>, haxorg_ImmCmdAttrAdapter_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdStr getTarget_const(OrgContext* org_context, haxorg_ImmCmdAttrAdapter self);
  static haxorg_ImmCmdAttrAdapter_vtable const* get_vtable();
};

/* clang-format on */
