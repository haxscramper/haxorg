/* clang-format off */
#include <wrappers/c/haxorg_c.h>
#include <wrappers/c/haxorg_c_utils.hpp>
haxorg_SemId newSemTimeStatic(haxorg_UserTimeBreakdown breakdown, bool isActive, OrgContext* org_context) { return convert_cpp_execution<haxorg_SemId, haxorg_UserTimeBreakdown, bool>(&org::newSemTimeStatic, org_context, breakdown, isActive); }

haxorg_StdShared_ptrOfImmAstContext initImmutableAstContext(OrgContext* org_context) { return convert_cpp_execution<haxorg_StdShared_ptrOfImmAstContext>(&org::initImmutableAstContext, org_context); }

haxorg_SemId asOneNode(haxorg_SemId arg, OrgContext* org_context) { return convert_cpp_execution<haxorg_SemId, haxorg_SemId>(&org::asOneNode, org_context, arg); }

haxorg_StdString formatToString(haxorg_SemId arg, OrgContext* org_context) { return convert_cpp_execution<haxorg_StdString, haxorg_SemId>(&org::formatToString, org_context, arg); }

haxorg_StdString exportToYamlString(haxorg_SemId node, haxorg_OrgYamlExportOpts opts, OrgContext* org_context) { return convert_cpp_execution<haxorg_StdString, haxorg_SemId, haxorg_OrgYamlExportOpts>(&org::exportToYamlString, org_context, node, opts); }

void exportToYamlFile(haxorg_SemId node, haxorg_StdString path, haxorg_OrgYamlExportOpts opts, OrgContext* org_context) { return convert_cpp_execution<void, haxorg_SemId, haxorg_StdString, haxorg_OrgYamlExportOpts>(&org::exportToYamlFile, org_context, node, path, opts); }

haxorg_StdString exportToJsonString(haxorg_SemId node, OrgContext* org_context) { return convert_cpp_execution<haxorg_StdString, haxorg_SemId>(&org::exportToJsonString, org_context, node); }

void exportToJsonFile(haxorg_SemId node, haxorg_StdString path, OrgContext* org_context) { return convert_cpp_execution<void, haxorg_SemId, haxorg_StdString>(&org::exportToJsonFile, org_context, node, path); }

haxorg_SemId readProtobufFile(haxorg_StdString file, OrgContext* org_context) { return convert_cpp_execution<haxorg_SemId, haxorg_StdString>(&org::readProtobufFile, org_context, file); }

void exportToProtobufFile(haxorg_SemId doc, haxorg_StdString file, OrgContext* org_context) { return convert_cpp_execution<void, haxorg_SemId, haxorg_StdString>(&org::exportToProtobufFile, org_context, doc, file); }

haxorg_StdString exportToTreeString(haxorg_SemId node, haxorg_OrgTreeExportOpts opts, OrgContext* org_context) { return convert_cpp_execution<haxorg_StdString, haxorg_SemId, haxorg_OrgTreeExportOpts>(&org::exportToTreeString, org_context, node, opts); }

void exportToTreeFile(haxorg_SemId node, haxorg_StdString path, haxorg_OrgTreeExportOpts opts, OrgContext* org_context) { return convert_cpp_execution<void, haxorg_SemId, haxorg_StdString, haxorg_OrgTreeExportOpts>(&org::exportToTreeFile, org_context, node, path, opts); }

haxorg_AstTrackingMap getAstTrackingMap(haxorg_CHstdVec nodes, OrgContext* org_context) { return convert_cpp_execution<haxorg_AstTrackingMap, haxorg_CHstdVec>(&org::getAstTrackingMap, org_context, nodes); }

haxorg_CHstdVec getSubnodeGroups(haxorg_SemId node, haxorg_AstTrackingMap map, OrgContext* org_context) { return convert_cpp_execution<haxorg_CHstdVec, haxorg_SemId, haxorg_AstTrackingMap>(&org::getSubnodeGroups, org_context, node, map); }

haxorg_CHstdVec annotateSequence(haxorg_CHstdVec groups, int first, int last, OrgContext* org_context) { return convert_cpp_execution<haxorg_CHstdVec, haxorg_CHstdVec, int, int>(&hstd::annotateSequence, org_context, groups, first, last); }

haxorg_StdShared_ptrOfGraphMapGraphState initMapGraphState(haxorg_StdShared_ptrOfImmAstContext ast, OrgContext* org_context) { return convert_cpp_execution<haxorg_StdShared_ptrOfGraphMapGraphState, haxorg_StdShared_ptrOfImmAstContext>(&org::graph::initMapGraphState, org_context, ast); }

haxorg_StdString serializeToText(haxorg_StdShared_ptrOfImmAstContext store, OrgContext* org_context) { return convert_cpp_execution<haxorg_StdString, haxorg_StdShared_ptrOfImmAstContext>(&org::imm::serializeToText, org_context, store); }

void serializeFromText(haxorg_StdString binary, haxorg_StdShared_ptrOfImmAstContext store, OrgContext* org_context) { return convert_cpp_execution<void, haxorg_StdString, haxorg_StdShared_ptrOfImmAstContext>(&org::imm::serializeFromText, org_context, binary, store); }

haxorg_StdString serializeToText(haxorg_StdShared_ptrOfImmAstReplaceEpoch store, OrgContext* org_context) { return convert_cpp_execution<haxorg_StdString, haxorg_StdShared_ptrOfImmAstReplaceEpoch>(&org::imm::serializeToText, org_context, store); }

void serializeFromText(haxorg_StdString binary, haxorg_StdShared_ptrOfImmAstReplaceEpoch store, OrgContext* org_context) { return convert_cpp_execution<void, haxorg_StdString, haxorg_StdShared_ptrOfImmAstReplaceEpoch>(&org::imm::serializeFromText, org_context, binary, store); }

haxorg_StdString serializeToText(haxorg_StdShared_ptrOfGraphMapGraph store, OrgContext* org_context) { return convert_cpp_execution<haxorg_StdString, haxorg_StdShared_ptrOfGraphMapGraph>(&org::imm::serializeToText, org_context, store); }

void serializeFromText(haxorg_StdString binary, haxorg_StdShared_ptrOfGraphMapGraph store, OrgContext* org_context) { return convert_cpp_execution<void, haxorg_StdString, haxorg_StdShared_ptrOfGraphMapGraph>(&org::imm::serializeFromText, org_context, binary, store); }

haxorg_StdString serializeFromTextToTreeDump(haxorg_StdString binary, OrgContext* org_context) { return convert_cpp_execution<haxorg_StdString, haxorg_StdString>(&org::imm::serializeFromTextToTreeDump, org_context, binary); }

void eachSubnodeRec(haxorg_SemId node, haxorg_NanobindCallable callback, OrgContext* org_context) { return convert_cpp_execution<void, haxorg_SemId, haxorg_NanobindCallable>(&org::bind::python::eachSubnodeRec, org_context, node, callback); }

void eachSubnodeRecSimplePath(haxorg_SemId node, haxorg_NanobindCallable callback, OrgContext* org_context) { return convert_cpp_execution<void, haxorg_SemId, haxorg_NanobindCallable>(&org::bind::python::eachSubnodeRecSimplePath, org_context, node, callback); }

void setShouldProcessPath(haxorg_OrgDirectoryParseParameters parameters, haxorg_NanobindCallable callback, OrgContext* org_context) { return convert_cpp_execution<void, haxorg_OrgDirectoryParseParameters, haxorg_NanobindCallable>(&org::bind::python::setShouldProcessPath, org_context, parameters, callback); }

haxorg_NanobindBytes serializeAstContextToText(haxorg_StdShared_ptrOfImmAstContext store, OrgContext* org_context) { return convert_cpp_execution<haxorg_NanobindBytes, haxorg_StdShared_ptrOfImmAstContext>(&org::bind::python::serializeAstContextToText, org_context, store); }

void serializeAstContextFromText(haxorg_NanobindBytes binary, haxorg_StdShared_ptrOfImmAstContext store, OrgContext* org_context) { return convert_cpp_execution<void, haxorg_NanobindBytes, haxorg_StdShared_ptrOfImmAstContext>(&org::bind::python::serializeAstContextFromText, org_context, binary, store); }

haxorg_NanobindBytes serializeAstReplaceEpochToText(haxorg_StdShared_ptrOfImmAstReplaceEpoch store, OrgContext* org_context) { return convert_cpp_execution<haxorg_NanobindBytes, haxorg_StdShared_ptrOfImmAstReplaceEpoch>(&org::bind::python::serializeAstReplaceEpochToText, org_context, store); }

void serializeAstReplaceEpochFromText(haxorg_NanobindBytes binary, haxorg_StdShared_ptrOfImmAstReplaceEpoch store, OrgContext* org_context) { return convert_cpp_execution<void, haxorg_NanobindBytes, haxorg_StdShared_ptrOfImmAstReplaceEpoch>(&org::bind::python::serializeAstReplaceEpochFromText, org_context, binary, store); }

void serializeMapGraphFromText(haxorg_NanobindBytes binary, haxorg_StdShared_ptrOfGraphMapGraph store, OrgContext* org_context) { return convert_cpp_execution<void, haxorg_NanobindBytes, haxorg_StdShared_ptrOfGraphMapGraph>(&org::bind::python::serializeMapGraphFromText, org_context, binary, store); }

haxorg_NanobindBytes serializeMapGraphToText(haxorg_StdShared_ptrOfGraphMapGraph store, OrgContext* org_context) { return convert_cpp_execution<haxorg_NanobindBytes, haxorg_StdShared_ptrOfGraphMapGraph>(&org::bind::python::serializeMapGraphToText, org_context, store); }

void setGetParsedNode(haxorg_OrgDirectoryParseParameters params, haxorg_NanobindCallable callback, OrgContext* org_context) { return convert_cpp_execution<void, haxorg_OrgDirectoryParseParameters, haxorg_NanobindCallable>(&org::bind::python::setGetParsedNode, org_context, params, callback); }

haxorg_SemId evaluateCodeBlocks(haxorg_SemId node, haxorg_PyCodeEvalParameters conf, haxorg_StdShared_ptrOfParseContext parse_context, OrgContext* org_context) { return convert_cpp_execution<haxorg_SemId, haxorg_SemId, haxorg_PyCodeEvalParameters, haxorg_StdShared_ptrOfParseContext>(&org::bind::python::evaluateCodeBlocks, org_context, node, conf, parse_context); }

/* clang-format on */
