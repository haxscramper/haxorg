/* clang-format off */
#include <wrappers/c/haxorg_c_api.h>
HAXORG_C_API_LINKAGE haxorg_SemId newSemTimeStatic(haxorg_UserTimeBreakdown breakdown, bool isActive, OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_StdShared_ptrOfImmAstContext initImmutableAstContext(OrgContext* org_context);
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
HAXORG_C_API_LINKAGE haxorg_StdShared_ptrOfGraphMapGraphState initMapGraphState(haxorg_StdShared_ptrOfImmAstContext ast, OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_StdString serializeToText(haxorg_StdShared_ptrOfImmAstContext store, OrgContext* org_context);
HAXORG_C_API_LINKAGE void serializeFromText(haxorg_StdString binary, haxorg_StdShared_ptrOfImmAstContext store, OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_StdString serializeToText(haxorg_StdShared_ptrOfImmAstReplaceEpoch store, OrgContext* org_context);
HAXORG_C_API_LINKAGE void serializeFromText(haxorg_StdString binary, haxorg_StdShared_ptrOfImmAstReplaceEpoch store, OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_StdString serializeToText(haxorg_StdShared_ptrOfGraphMapGraph store, OrgContext* org_context);
HAXORG_C_API_LINKAGE void serializeFromText(haxorg_StdString binary, haxorg_StdShared_ptrOfGraphMapGraph store, OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_StdString serializeFromTextToTreeDump(haxorg_StdString binary, OrgContext* org_context);
HAXORG_C_API_LINKAGE void eachSubnodeRec(haxorg_SemId node, haxorg_NanobindCallable callback, OrgContext* org_context);
HAXORG_C_API_LINKAGE void eachSubnodeRecSimplePath(haxorg_SemId node, haxorg_NanobindCallable callback, OrgContext* org_context);
HAXORG_C_API_LINKAGE void setShouldProcessPath(haxorg_OrgDirectoryParseParameters parameters, haxorg_NanobindCallable callback, OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_NanobindBytes serializeAstContextToText(haxorg_StdShared_ptrOfImmAstContext store, OrgContext* org_context);
HAXORG_C_API_LINKAGE void serializeAstContextFromText(haxorg_NanobindBytes binary, haxorg_StdShared_ptrOfImmAstContext store, OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_NanobindBytes serializeAstReplaceEpochToText(haxorg_StdShared_ptrOfImmAstReplaceEpoch store, OrgContext* org_context);
HAXORG_C_API_LINKAGE void serializeAstReplaceEpochFromText(haxorg_NanobindBytes binary, haxorg_StdShared_ptrOfImmAstReplaceEpoch store, OrgContext* org_context);
HAXORG_C_API_LINKAGE void serializeMapGraphFromText(haxorg_NanobindBytes binary, haxorg_StdShared_ptrOfGraphMapGraph store, OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_NanobindBytes serializeMapGraphToText(haxorg_StdShared_ptrOfGraphMapGraph store, OrgContext* org_context);
HAXORG_C_API_LINKAGE void setGetParsedNode(haxorg_OrgDirectoryParseParameters params, haxorg_NanobindCallable callback, OrgContext* org_context);
HAXORG_C_API_LINKAGE haxorg_SemId evaluateCodeBlocks(haxorg_SemId node, haxorg_PyCodeEvalParameters conf, haxorg_StdShared_ptrOfParseContext parse_context, OrgContext* org_context);
/* clang-format on */
