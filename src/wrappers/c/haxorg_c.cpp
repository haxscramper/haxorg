/* clang-format off */
#include <wrappers/c/haxorg_c.h>
#include <wrappers/c/haxorg_c_utils.hpp>


































void haxorg_destroy_UserTimeBreakdown(haxorg_UserTimeBreakdown* obj) { org::bind::c::execute_destroy<hstd::UserTimeBreakdown>(obj); }

haxorg_UserTimeBreakdown haxorg_UserTime_getBreakdown(haxorg_UserTime __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_UserTimeBreakdown, hstd::UserTimeBreakdown(*)() const>(&getBreakdown, org_context); }

haxorg_StdString haxorg_UserTime_format(haxorg_UserTime __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_StdString, std::string(*)() const>(&format, org_context); }

int64_t haxorg_UserTime_getTimeDeltaSeconds(haxorg_UserTime __this, haxorg_UserTime other, OrgContext* org_context) { return org::bind::c::execute_cpp<int64_t, int64_t(*)(hstd::UserTime const&) const, haxorg_UserTime>(&getTimeDeltaSeconds, org_context, other); }

int64_t haxorg_UserTime_toUnixTimestamp(haxorg_UserTime __this, OrgContext* org_context) { return org::bind::c::execute_cpp<int64_t, int64_t(*)() const>(&toUnixTimestamp, org_context); }

void haxorg_destroy_UserTime(haxorg_UserTime* obj) { org::bind::c::execute_destroy<hstd::UserTime>(obj); }

void haxorg_destroy_ParseSourceFileId(haxorg_ParseSourceFileId* obj) { org::bind::c::execute_destroy<org::parse::SourceFileId>(obj); }

void haxorg_destroy_ParseSourceLoc(haxorg_ParseSourceLoc* obj) { org::bind::c::execute_destroy<org::parse::SourceLoc>(obj); }

haxorg_OrgJsonKind haxorg_OrgJson_getKind(haxorg_OrgJson __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_OrgJsonKind, OrgJsonKind(*)() const>(&getKind, org_context); }

haxorg_StdString haxorg_OrgJson_getJsonString(haxorg_OrgJson __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_StdString, std::string(*)() const>(&getJsonString, org_context); }

haxorg_OrgJson haxorg_OrgJson_atIndex(haxorg_OrgJson __this, int idx, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_OrgJson, org::sem::OrgJson(*)(int) const, int>(&at, org_context, idx); }

haxorg_OrgJson haxorg_OrgJson_atField(haxorg_OrgJson __this, haxorg_StdString name, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_OrgJson, org::sem::OrgJson(*)(std::string const&) const, haxorg_StdString>(&at, org_context, name); }

haxorg_StdString haxorg_OrgJson_getString(haxorg_OrgJson __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_StdString, std::string(*)() const>(&getString, org_context); }

haxorg_OrgJson haxorg_OrgJson_getField(haxorg_OrgJson __this, haxorg_StdString name, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_OrgJson, org::sem::OrgJson(*)(std::string const&) const, haxorg_StdString>(&getField, org_context, name); }

haxorg_OrgJson haxorg_OrgJson_getItem(haxorg_OrgJson __this, int index, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_OrgJson, org::sem::OrgJson(*)(int) const, int>(&getItem, org_context, index); }

int haxorg_OrgJson_getInt(haxorg_OrgJson __this, OrgContext* org_context) { return org::bind::c::execute_cpp<int, int(*)() const>(&getInt, org_context); }

bool haxorg_OrgJson_getBool(haxorg_OrgJson __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&getBool, org_context); }

haxorg_HstdVec haxorg_OrgJson_getArray(haxorg_OrgJson __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<org::sem::OrgJson>(*)() const>(&getArray, org_context); }

haxorg_StdString haxorg_OrgJson_dump(haxorg_OrgJson __this, int indent, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_StdString, std::string(*)(int) const, int>(&dump, org_context, indent); }

void haxorg_destroy_OrgJson(haxorg_OrgJson* obj) { org::bind::c::execute_destroy<org::sem::OrgJson>(obj); }

haxorg_OrgSemKind haxorg_Org_getKind(haxorg_Org __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_OrgSemKind, OrgSemKind(*)() const>(&getKind, org_context); }

void haxorg_Org_push_back(haxorg_Org __this, haxorg_SemId sub, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::sem::SemId<org::sem::Org>), haxorg_SemId>(&push_back, org_context, sub); }

int haxorg_Org_size(haxorg_Org __this, OrgContext* org_context) { return org::bind::c::execute_cpp<int, int(*)() const>(&size, org_context); }

void haxorg_Org_insert(haxorg_Org __this, int pos, haxorg_SemId node, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(int, org::sem::SemId<org::sem::Org>), int, haxorg_SemId>(&insert, org_context, pos, node); }

haxorg_SemId haxorg_Org_at(haxorg_Org __this, int idx, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SemId, org::sem::SemId<org::sem::Org>(*)(int) const, int>(&at, org_context, idx); }

bool haxorg_Org_is(haxorg_Org __this, haxorg_OrgSemKind kind, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(OrgSemKind) const, haxorg_OrgSemKind>(&is, org_context, kind); }

void haxorg_destroy_Org(haxorg_Org* obj) { org::bind::c::execute_destroy<org::sem::Org>(obj); }

void haxorg_OperationsTracer_setTraceFileStr(haxorg_OperationsTracer __this, haxorg_StdString outfile, bool overwrite, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(std::string const&, bool), haxorg_StdString, bool>(&setTraceFileStr, org_context, outfile, overwrite); }

void haxorg_OperationsTracer_sendMessage(haxorg_OperationsTracer __this, haxorg_StdString value, haxorg_StdString function, int line, haxorg_StdString file, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(std::string const&, std::string const&, int, std::string const&), haxorg_StdString, haxorg_StdString, int, haxorg_StdString>(&sendMessage, org_context, value, function, line, file); }

void haxorg_destroy_OperationsTracer(haxorg_OperationsTracer* obj) { org::bind::c::execute_destroy<hstd::OperationsTracer>(obj); }

void haxorg_destroy_Cache(haxorg_Cache* obj) { org::bind::c::execute_destroy<hstd::ext::Cache>(obj); }

void haxorg_destroy_ParseOrgParseFragment(haxorg_ParseOrgParseFragment* obj) { org::bind::c::execute_destroy<org::parse::OrgParseFragment>(obj); }

void haxorg_destroy_OrgParseParameters(haxorg_OrgParseParameters* obj) { org::bind::c::execute_destroy<org::parse::OrgParseParameters>(obj); }

void haxorg_destroy_OrgDirectoryParseParameters(haxorg_OrgDirectoryParseParameters* obj) { org::bind::c::execute_destroy<org::parse::OrgDirectoryParseParameters>(obj); }

haxorg_Cache haxorg_ParseContext_getDiagnosticStrings(haxorg_ParseContext __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_Cache, std::shared_ptr<hstd::ext::Cache>(*)()>(&getDiagnosticStrings, org_context); }

haxorg_ParseSourceFileId haxorg_ParseContext_addSource(haxorg_ParseContext __this, haxorg_StdString path, haxorg_StdString content, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ParseSourceFileId, org::parse::SourceFileId(*)(std::string const&, std::string const&) const, haxorg_StdString, haxorg_StdString>(&addSource, org_context, path, content); }

haxorg_SemId haxorg_ParseContext_parseFileOpts(haxorg_ParseContext __this, haxorg_StdString file, haxorg_OrgParseParameters opts, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SemId, org::sem::SemId<org::sem::Org>(*)(std::string const&, std::shared_ptr<org::parse::OrgParseParameters> const&), haxorg_StdString, haxorg_OrgParseParameters>(&parseFileOpts, org_context, file, opts); }

haxorg_SemId haxorg_ParseContext_parseFile(haxorg_ParseContext __this, haxorg_StdString file, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SemId, org::sem::SemId<org::sem::Org>(*)(std::string const&), haxorg_StdString>(&parseFile, org_context, file); }

haxorg_SemId haxorg_ParseContext_parseString(haxorg_ParseContext __this, haxorg_StdString text, haxorg_StdString file_name, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SemId, org::sem::SemId<org::sem::Org>(*)(std::string const&, std::string const&), haxorg_StdString, haxorg_StdString>(&parseString, org_context, text, file_name); }

haxorg_SemId haxorg_ParseContext_parseStringOpts(haxorg_ParseContext __this, haxorg_StdString text, haxorg_StdString file_name, haxorg_OrgParseParameters opts, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SemId, org::sem::SemId<org::sem::Org>(*)(std::string const, std::string const&, std::shared_ptr<org::parse::OrgParseParameters> const&), haxorg_StdString, haxorg_StdString, haxorg_OrgParseParameters>(&parseStringOpts, org_context, text, file_name, opts); }

haxorg_StdOptional haxorg_ParseContext_parseDirectory(haxorg_ParseContext __this, haxorg_StdString path, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_StdOptional, std::optional<org::sem::SemId<org::sem::Org>>(*)(std::string const&), haxorg_StdString>(&parseDirectory, org_context, path); }

haxorg_StdOptional haxorg_ParseContext_parseDirectoryOpts(haxorg_ParseContext __this, haxorg_StdString path, haxorg_OrgDirectoryParseParameters opts, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_StdOptional, std::optional<org::sem::SemId<org::sem::Org>>(*)(std::string const&, std::shared_ptr<org::parse::OrgDirectoryParseParameters> const&), haxorg_StdString, haxorg_OrgDirectoryParseParameters>(&parseDirectoryOpts, org_context, path, opts); }

haxorg_SemId haxorg_ParseContext_parseFileWithIncludes(haxorg_ParseContext __this, haxorg_StdString file, haxorg_OrgDirectoryParseParameters opts, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SemId, org::sem::SemId<org::sem::File>(*)(std::string const&, std::shared_ptr<org::parse::OrgDirectoryParseParameters> const&), haxorg_StdString, haxorg_OrgDirectoryParseParameters>(&parseFileWithIncludes, org_context, file, opts); }

haxorg_HstdVec haxorg_ParseContext_collectDiagnostics(haxorg_ParseContext __this, haxorg_SemId tree, haxorg_Cache cache, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<hstd::ext::Report>(*)(org::sem::SemId<org::sem::Org> const&, std::shared_ptr<hstd::ext::Cache> const&), haxorg_SemId, haxorg_Cache>(&collectDiagnostics, org_context, tree, cache); }

haxorg_HstdVec haxorg_ParseContext_collectErrorNodes(haxorg_ParseContext __this, haxorg_SemId tree, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<org::sem::SemId<org::sem::ErrorGroup>>(*)(org::sem::SemId<org::sem::Org> const&), haxorg_SemId>(&collectErrorNodes, org_context, tree); }

void haxorg_destroy_ParseContext(haxorg_ParseContext* obj) { org::bind::c::execute_destroy<org::parse::ParseContext>(obj); }

haxorg_HstdStr haxorg_ImmReflFieldId_getName(haxorg_ImmReflFieldId __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str(*)() const>(&getName, org_context); }

void haxorg_destroy_ImmReflFieldId(haxorg_ImmReflFieldId* obj) { org::bind::c::execute_destroy<org::imm::ImmReflFieldId>(obj); }

haxorg_OrgSemKind haxorg_ImmId_getKind(haxorg_ImmId __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_OrgSemKind, OrgSemKind(*)() const>(&getKind, org_context); }

bool haxorg_ImmId_is(haxorg_ImmId __this, haxorg_OrgSemKind kind, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(OrgSemKind) const, haxorg_OrgSemKind>(&is, org_context, kind); }

haxorg_ImmIdNodeIdxT haxorg_ImmId_getNodeIndex(haxorg_ImmId __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmIdNodeIdxT, org::imm::ImmId::NodeIdxT(*)() const>(&getNodeIndex, org_context); }

haxorg_StdString haxorg_ImmId_getReadableId(haxorg_ImmId __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_StdString, std::string(*)() const>(&getReadableId, org_context); }

void haxorg_destroy_ImmId(haxorg_ImmId* obj) { org::bind::c::execute_destroy<org::imm::ImmId>(obj); }

void haxorg_destroy_ImmOrg(haxorg_ImmOrg* obj) { org::bind::c::execute_destroy<org::imm::ImmOrg>(obj); }

void haxorg_destroy_ImmPathStep(haxorg_ImmPathStep* obj) { org::bind::c::execute_destroy<org::imm::ImmPathStep>(obj); }

bool haxorg_ImmPath_empty(haxorg_ImmPath __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&empty, org_context); }

void haxorg_destroy_ImmPath(haxorg_ImmPath* obj) { org::bind::c::execute_destroy<org::imm::ImmPath>(obj); }

void haxorg_destroy_ImmUniqId(haxorg_ImmUniqId* obj) { org::bind::c::execute_destroy<org::imm::ImmUniqId>(obj); }

void haxorg_destroy_ImmAstReplaceEpoch(haxorg_ImmAstReplaceEpoch* obj) { org::bind::c::execute_destroy<org::imm::ImmAstReplaceEpoch>(obj); }

haxorg_ImmAstVersion haxorg_ImmAstContext_addRoot(haxorg_ImmAstContext __this, haxorg_SemId data, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmAstVersion, org::imm::ImmAstVersion(*)(org::sem::SemId<org::sem::Org>), haxorg_SemId>(&addRoot, org_context, data); }

haxorg_ImmAstVersion haxorg_ImmAstContext_getEmptyVersion(haxorg_ImmAstContext __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmAstVersion, org::imm::ImmAstVersion(*)()>(&getEmptyVersion, org_context); }

haxorg_SemId haxorg_ImmAstContext_get(haxorg_ImmAstContext __this, haxorg_ImmId id, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SemId, org::sem::SemId<org::sem::Org>(*)(org::imm::ImmId), haxorg_ImmId>(&get, org_context, id); }

void haxorg_destroy_ImmAstContext(haxorg_ImmAstContext* obj) { org::bind::c::execute_destroy<org::imm::ImmAstContext>(obj); }

haxorg_ImmId haxorg_ImmAstVersion_getRoot(haxorg_ImmAstVersion __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmId, org::imm::ImmId(*)() const>(&getRoot, org_context); }

haxorg_ImmAdapter haxorg_ImmAstVersion_getRootAdapter(haxorg_ImmAstVersion __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmAdapter, org::imm::ImmAdapter(*)() const>(&getRootAdapter, org_context); }

haxorg_ImmAstContext haxorg_ImmAstVersion_getContext(haxorg_ImmAstVersion __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmAstContext, std::shared_ptr<org::imm::ImmAstContext>(*)() const>(&getContext, org_context); }

haxorg_ImmAstReplaceEpoch haxorg_ImmAstVersion_getEpoch(haxorg_ImmAstVersion __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmAstReplaceEpoch, std::shared_ptr<org::imm::ImmAstReplaceEpoch>(*)() const>(&getEpoch, org_context); }

void haxorg_destroy_ImmAstVersion(haxorg_ImmAstVersion* obj) { org::bind::c::execute_destroy<org::imm::ImmAstVersion>(obj); }

int haxorg_ImmAdapter_size(haxorg_ImmAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<int, int(*)() const>(&size, org_context); }

bool haxorg_ImmAdapter_isNil(haxorg_ImmAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isNil, org_context); }

bool haxorg_ImmAdapter_isRoot(haxorg_ImmAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isRoot, org_context); }

haxorg_OrgSemKind haxorg_ImmAdapter_getKind(haxorg_ImmAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_OrgSemKind, OrgSemKind(*)() const>(&getKind, org_context); }

haxorg_ImmUniqId haxorg_ImmAdapter_uniq(haxorg_ImmAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmUniqId, org::imm::ImmUniqId(*)() const>(&uniq, org_context); }

haxorg_StdString haxorg_ImmAdapter_treeReprString(haxorg_ImmAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_StdString, std::string(*)() const>(&treeReprString, org_context); }

haxorg_StdString haxorg_ImmAdapter_treeReprStringOpts(haxorg_ImmAdapter __this, haxorg_ImmAdapterTreeReprConf conf, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_StdString, std::string(*)(org::imm::ImmAdapter::TreeReprConf const&) const, haxorg_ImmAdapterTreeReprConf>(&treeReprStringOpts, org_context, conf); }

bool haxorg_ImmAdapter_isDirectParentOf(haxorg_ImmAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmAdapter const&) const, haxorg_ImmAdapter>(&isDirectParentOf, org_context, other); }

bool haxorg_ImmAdapter_isIndirectParentOf(haxorg_ImmAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmAdapter const&) const, haxorg_ImmAdapter>(&isIndirectParentOf, org_context, other); }

bool haxorg_ImmAdapter_isSubnodeOf(haxorg_ImmAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmAdapter const&) const, haxorg_ImmAdapter>(&isSubnodeOf, org_context, other); }

haxorg_StdOptional haxorg_ImmAdapter_getParent(haxorg_ImmAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_StdOptional, std::optional<org::imm::ImmAdapter>(*)() const>(&getParent, org_context); }

int haxorg_ImmAdapter_getSelfIndex(haxorg_ImmAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<int, int(*)() const>(&getSelfIndex, org_context); }

haxorg_ImmAdapter haxorg_ImmAdapter_atPathStep(haxorg_ImmAdapter __this, haxorg_ImmId id, haxorg_ImmPathStep idx, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmAdapter, org::imm::ImmAdapter(*)(org::imm::ImmId, org::imm::ImmPathStep) const, haxorg_ImmId, haxorg_ImmPathStep>(&at, org_context, id, idx); }

haxorg_ImmAdapter haxorg_ImmAdapter_atField(haxorg_ImmAdapter __this, haxorg_ImmReflFieldId field, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmAdapter, org::imm::ImmAdapter(*)(org::imm::ImmReflFieldId const&) const, haxorg_ImmReflFieldId>(&at, org_context, field); }

haxorg_ImmAdapter haxorg_ImmAdapter_atIndex(haxorg_ImmAdapter __this, int idx, bool withPath, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmAdapter, org::imm::ImmAdapter(*)(int, bool) const, int, bool>(&at, org_context, idx, withPath); }

haxorg_ImmAdapter haxorg_ImmAdapter_atPath(haxorg_ImmAdapter __this, haxorg_HstdVec path, bool withPath, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmAdapter, org::imm::ImmAdapter(*)(hstd::Vec<int> const&, bool) const, haxorg_HstdVec, bool>(&at, org_context, path, withPath); }

bool haxorg_ImmAdapter_is(haxorg_ImmAdapter __this, haxorg_OrgSemKind kind, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(OrgSemKind) const, haxorg_OrgSemKind>(&is, org_context, kind); }

haxorg_HstdVec haxorg_ImmAdapter_sub(haxorg_ImmAdapter __this, bool withPath, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<org::imm::ImmAdapter>(*)(bool) const, bool>(&sub, org_context, withPath); }

void haxorg_destroy_ImmAdapterTreeReprConf(haxorg_ImmAdapterTreeReprConf* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapter::TreeReprConf>(obj); }

void haxorg_destroy_ImmAdapter(haxorg_ImmAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapter>(obj); }

void haxorg_destroy_ImmAdapterVirtualBase(haxorg_ImmAdapterVirtualBase* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterVirtualBase>(obj); }

void haxorg_destroy_OrgYamlExportOpts(haxorg_OrgYamlExportOpts* obj) { org::bind::c::execute_destroy<org::OrgYamlExportOpts>(obj); }

void haxorg_destroy_OrgTreeExportOpts(haxorg_OrgTreeExportOpts* obj) { org::bind::c::execute_destroy<org::OrgTreeExportOpts>(obj); }

haxorg_SemId haxorg_AstTrackingPath_getParent(haxorg_AstTrackingPath __this, int offset, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SemId, org::sem::SemId<org::sem::Org>(*)(int) const, int>(&getParent, org_context, offset); }

haxorg_SemId haxorg_AstTrackingPath_getNode(haxorg_AstTrackingPath __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SemId, org::sem::SemId<org::sem::Org>(*)() const>(&getNode, org_context); }

void haxorg_destroy_AstTrackingPath(haxorg_AstTrackingPath* obj) { org::bind::c::execute_destroy<org::AstTrackingPath>(obj); }

haxorg_HstdVec haxorg_AstTrackingAlternatives_getAllNodes(haxorg_AstTrackingAlternatives __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<org::sem::SemId<org::sem::Org>>(*)() const>(&getAllNodes, org_context); }

haxorg_SemId haxorg_AstTrackingAlternatives_getNode(haxorg_AstTrackingAlternatives __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SemId, org::sem::SemId<org::sem::Org>(*)() const>(&getNode, org_context); }

void haxorg_destroy_AstTrackingAlternatives(haxorg_AstTrackingAlternatives* obj) { org::bind::c::execute_destroy<org::AstTrackingAlternatives>(obj); }

haxorg_AstTrackingGroupRadioTarget haxorg_AstTrackingGroup_getRadioTargetConst(haxorg_AstTrackingGroup __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_AstTrackingGroupRadioTarget, org::AstTrackingGroup::RadioTarget const&(*)() const>(&getRadioTarget, org_context); }

haxorg_AstTrackingGroupTrackedHashtag haxorg_AstTrackingGroup_getTrackedHashtagConst(haxorg_AstTrackingGroup __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_AstTrackingGroupTrackedHashtag, org::AstTrackingGroup::TrackedHashtag const&(*)() const>(&getTrackedHashtag, org_context); }

haxorg_AstTrackingGroupTrackedHashtag haxorg_AstTrackingGroup_getTrackedHashtagMut(haxorg_AstTrackingGroup __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_AstTrackingGroupTrackedHashtag, org::AstTrackingGroup::TrackedHashtag&(*)()>(&getTrackedHashtag, org_context); }

haxorg_AstTrackingGroupSingle haxorg_AstTrackingGroup_getSingleConst(haxorg_AstTrackingGroup __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_AstTrackingGroupSingle, org::AstTrackingGroup::Single const&(*)() const>(&getSingle, org_context); }

haxorg_AstTrackingGroupRadioTarget haxorg_AstTrackingGroup_getRadioTargetMut(haxorg_AstTrackingGroup __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_AstTrackingGroupRadioTarget, org::AstTrackingGroup::RadioTarget&(*)()>(&getRadioTarget, org_context); }

haxorg_AstTrackingGroupSingle haxorg_AstTrackingGroup_getSingleMut(haxorg_AstTrackingGroup __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_AstTrackingGroupSingle, org::AstTrackingGroup::Single&(*)()>(&getSingle, org_context); }

bool haxorg_AstTrackingGroup_isSingle(haxorg_AstTrackingGroup __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isSingle, org_context); }

bool haxorg_AstTrackingGroup_isTrackedHashtag(haxorg_AstTrackingGroup __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isTrackedHashtag, org_context); }

bool haxorg_AstTrackingGroup_isRadioTarget(haxorg_AstTrackingGroup __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isRadioTarget, org_context); }

void haxorg_destroy_AstTrackingGroupRadioTarget(haxorg_AstTrackingGroupRadioTarget* obj) { org::bind::c::execute_destroy<org::AstTrackingGroup::RadioTarget>(obj); }

void haxorg_destroy_AstTrackingGroupSingle(haxorg_AstTrackingGroupSingle* obj) { org::bind::c::execute_destroy<org::AstTrackingGroup::Single>(obj); }

void haxorg_destroy_AstTrackingGroupTrackedHashtag(haxorg_AstTrackingGroupTrackedHashtag* obj) { org::bind::c::execute_destroy<org::AstTrackingGroup::TrackedHashtag>(obj); }

void haxorg_destroy_AstTrackingGroup(haxorg_AstTrackingGroup* obj) { org::bind::c::execute_destroy<org::AstTrackingGroup>(obj); }

haxorg_StdOptional haxorg_AstTrackingMap_getIdPath(haxorg_AstTrackingMap __this, haxorg_HstdStr id, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_StdOptional, std::optional<org::AstTrackingAlternatives>(*)(hstd::Str const&) const, haxorg_HstdStr>(&getIdPath, org_context, id); }

haxorg_StdOptional haxorg_AstTrackingMap_getNamePath(haxorg_AstTrackingMap __this, haxorg_HstdStr id, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_StdOptional, std::optional<org::AstTrackingAlternatives>(*)(hstd::Str const&) const, haxorg_HstdStr>(&getNamePath, org_context, id); }

haxorg_StdOptional haxorg_AstTrackingMap_getAnchorTarget(haxorg_AstTrackingMap __this, haxorg_HstdStr id, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_StdOptional, std::optional<org::AstTrackingAlternatives>(*)(hstd::Str const&) const, haxorg_HstdStr>(&getAnchorTarget, org_context, id); }

haxorg_StdOptional haxorg_AstTrackingMap_getFootnotePath(haxorg_AstTrackingMap __this, haxorg_HstdStr id, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_StdOptional, std::optional<org::AstTrackingAlternatives>(*)(hstd::Str const&) const, haxorg_HstdStr>(&getFootnotePath, org_context, id); }

void haxorg_destroy_AstTrackingMap(haxorg_AstTrackingMap* obj) { org::bind::c::execute_destroy<org::AstTrackingMap>(obj); }

void haxorg_destroy_SequenceSegment(haxorg_SequenceSegment* obj) { org::bind::c::execute_destroy<hstd::SequenceSegment>(obj); }

void haxorg_destroy_SequenceSegmentGroup(haxorg_SequenceSegmentGroup* obj) { org::bind::c::execute_destroy<hstd::SequenceSegmentGroup>(obj); }

void haxorg_destroy_SequenceAnnotationTag(haxorg_SequenceAnnotationTag* obj) { org::bind::c::execute_destroy<hstd::SequenceAnnotationTag>(obj); }

bool haxorg_SequenceAnnotation_isAnnotatedWith(haxorg_SequenceAnnotation __this, int groupKind, int segmentKind, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(int, int) const, int, int>(&isAnnotatedWith, org_context, groupKind, segmentKind); }

void haxorg_destroy_SequenceAnnotation(haxorg_SequenceAnnotation* obj) { org::bind::c::execute_destroy<hstd::SequenceAnnotation>(obj); }

haxorg_GraphMapLinkRadio haxorg_GraphMapLink_getRadio(haxorg_GraphMapLink __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_GraphMapLinkRadio, org::graph::MapLink::Radio&(*)()>(&getRadio, org_context); }

haxorg_GraphMapLinkRadio haxorg_GraphMapLink_getRadio(haxorg_GraphMapLink __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_GraphMapLinkRadio, org::graph::MapLink::Radio const&(*)() const>(&getRadio, org_context); }

bool haxorg_GraphMapLink_isRadio(haxorg_GraphMapLink __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isRadio, org_context); }

haxorg_GraphMapLinkLink haxorg_GraphMapLink_getLink(haxorg_GraphMapLink __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_GraphMapLinkLink, org::graph::MapLink::Link&(*)()>(&getLink, org_context); }

haxorg_GraphMapLinkLink haxorg_GraphMapLink_getLink(haxorg_GraphMapLink __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_GraphMapLinkLink, org::graph::MapLink::Link const&(*)() const>(&getLink, org_context); }

bool haxorg_GraphMapLink_isLink(haxorg_GraphMapLink __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isLink, org_context); }

haxorg_GraphMapLinkKind haxorg_GraphMapLink_getKind(haxorg_GraphMapLink __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_GraphMapLinkKind, org::graph::MapLink::Kind(*)() const>(&getKind, org_context); }

void haxorg_destroy_GraphMapLinkLink(haxorg_GraphMapLinkLink* obj) { org::bind::c::execute_destroy<org::graph::MapLink::Link>(obj); }

void haxorg_destroy_GraphMapLinkRadio(haxorg_GraphMapLinkRadio* obj) { org::bind::c::execute_destroy<org::graph::MapLink::Radio>(obj); }

void haxorg_destroy_GraphMapLink(haxorg_GraphMapLink* obj) { org::bind::c::execute_destroy<org::graph::MapLink>(obj); }

haxorg_ImmAdapter haxorg_GraphMapNodeProp_getAdapter(haxorg_GraphMapNodeProp __this, haxorg_ImmAstContext context, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmAdapter, org::imm::ImmAdapter(*)(std::shared_ptr<org::imm::ImmAstContext> const&) const, haxorg_ImmAstContext>(&getAdapter, org_context, context); }

haxorg_StdOptional haxorg_GraphMapNodeProp_getSubtreeId(haxorg_GraphMapNodeProp __this, haxorg_ImmAstContext context, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_StdOptional, std::optional<hstd::Str>(*)(std::shared_ptr<org::imm::ImmAstContext> const&) const, haxorg_ImmAstContext>(&getSubtreeId, org_context, context); }

haxorg_StdOptional haxorg_GraphMapNodeProp_getFootnoteName(haxorg_GraphMapNodeProp __this, haxorg_ImmAstContext context, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_StdOptional, std::optional<hstd::Str>(*)(std::shared_ptr<org::imm::ImmAstContext> const&) const, haxorg_ImmAstContext>(&getFootnoteName, org_context, context); }

void haxorg_destroy_GraphMapNodeProp(haxorg_GraphMapNodeProp* obj) { org::bind::c::execute_destroy<org::graph::MapNodeProp>(obj); }

void haxorg_destroy_GraphMapEdgeProp(haxorg_GraphMapEdgeProp* obj) { org::bind::c::execute_destroy<org::graph::MapEdgeProp>(obj); }

bool haxorg_GraphMapNode___eq__(haxorg_GraphMapNode __this, haxorg_GraphMapNode other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::graph::MapNode const&) const, haxorg_GraphMapNode>(&operator==, org_context, other); }

bool haxorg_GraphMapNode___lt__(haxorg_GraphMapNode __this, haxorg_GraphMapNode other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::graph::MapNode const&) const, haxorg_GraphMapNode>(&operator<, org_context, other); }

void haxorg_destroy_GraphMapNode(haxorg_GraphMapNode* obj) { org::bind::c::execute_destroy<org::graph::MapNode>(obj); }

void haxorg_destroy_GraphMapEdge(haxorg_GraphMapEdge* obj) { org::bind::c::execute_destroy<org::graph::MapEdge>(obj); }

int haxorg_GraphMapGraph_nodeCount(haxorg_GraphMapGraph __this, OrgContext* org_context) { return org::bind::c::execute_cpp<int, int(*)() const>(&nodeCount, org_context); }

int haxorg_GraphMapGraph_edgeCount(haxorg_GraphMapGraph __this, OrgContext* org_context) { return org::bind::c::execute_cpp<int, int(*)() const>(&edgeCount, org_context); }

haxorg_GraphAdjNodesList haxorg_GraphMapGraph_outNodes(haxorg_GraphMapGraph __this, haxorg_GraphMapNode node, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_GraphAdjNodesList, org::graph::AdjNodesList const&(*)(org::graph::MapNode const&) const, haxorg_GraphMapNode>(&outNodes, org_context, node); }

haxorg_GraphAdjNodesList haxorg_GraphMapGraph_inNodes(haxorg_GraphMapGraph __this, haxorg_GraphMapNode node, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_GraphAdjNodesList, org::graph::AdjNodesList const&(*)(org::graph::MapNode const&) const, haxorg_GraphMapNode>(&inNodes, org_context, node); }

haxorg_HstdVec haxorg_GraphMapGraph_adjEdges(haxorg_GraphMapGraph __this, haxorg_GraphMapNode node, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<org::graph::MapEdge>(*)(org::graph::MapNode const&) const, haxorg_GraphMapNode>(&adjEdges, org_context, node); }

haxorg_HstdVec haxorg_GraphMapGraph_adjNodes(haxorg_GraphMapGraph __this, haxorg_GraphMapNode node, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<org::graph::MapNode>(*)(org::graph::MapNode const&) const, haxorg_GraphMapNode>(&adjNodes, org_context, node); }

haxorg_HstdVec haxorg_GraphMapGraph_outEdges(haxorg_GraphMapGraph __this, haxorg_GraphMapNode node, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<org::graph::MapEdge>(*)(org::graph::MapNode const&) const, haxorg_GraphMapNode>(&outEdges, org_context, node); }

haxorg_HstdVec haxorg_GraphMapGraph_inEdges(haxorg_GraphMapGraph __this, haxorg_GraphMapNode node, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<org::graph::MapEdge>(*)(org::graph::MapNode const&) const, haxorg_GraphMapNode>(&inEdges, org_context, node); }

int haxorg_GraphMapGraph_outDegree(haxorg_GraphMapGraph __this, haxorg_GraphMapNode node, OrgContext* org_context) { return org::bind::c::execute_cpp<int, int(*)(org::graph::MapNode const&) const, haxorg_GraphMapNode>(&outDegree, org_context, node); }

int haxorg_GraphMapGraph_inDegree(haxorg_GraphMapGraph __this, haxorg_GraphMapNode node, OrgContext* org_context) { return org::bind::c::execute_cpp<int, int(*)(org::graph::MapNode const&) const, haxorg_GraphMapNode>(&inDegree, org_context, node); }

bool haxorg_GraphMapGraph_isRegisteredNode(haxorg_GraphMapGraph __this, haxorg_GraphMapNode id, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::graph::MapNode const&) const, haxorg_GraphMapNode>(&isRegisteredNode, org_context, id); }

bool haxorg_GraphMapGraph_isRegisteredNodeById(haxorg_GraphMapGraph __this, haxorg_ImmUniqId id, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmUniqId const&) const, haxorg_ImmUniqId>(&isRegisteredNode, org_context, id); }

haxorg_GraphMapNodeProp haxorg_GraphMapGraph_atMapNode(haxorg_GraphMapGraph __this, haxorg_GraphMapNode node, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_GraphMapNodeProp, org::graph::MapNodeProp const&(*)(org::graph::MapNode const&) const, haxorg_GraphMapNode>(&at, org_context, node); }

haxorg_GraphMapEdgeProp haxorg_GraphMapGraph_atMapEdge(haxorg_GraphMapGraph __this, haxorg_GraphMapEdge edge, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_GraphMapEdgeProp, org::graph::MapEdgeProp const&(*)(org::graph::MapEdge const&) const, haxorg_GraphMapEdge>(&at, org_context, edge); }

void haxorg_GraphMapGraph_addEdge(haxorg_GraphMapGraph __this, haxorg_GraphMapEdge edge, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::graph::MapEdge const&), haxorg_GraphMapEdge>(&addEdge, org_context, edge); }

void haxorg_GraphMapGraph_addEdgeWithProp(haxorg_GraphMapGraph __this, haxorg_GraphMapEdge edge, haxorg_GraphMapEdgeProp prop, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::graph::MapEdge const&, org::graph::MapEdgeProp const&), haxorg_GraphMapEdge, haxorg_GraphMapEdgeProp>(&addEdge, org_context, edge, prop); }

void haxorg_GraphMapGraph_addNode(haxorg_GraphMapGraph __this, haxorg_GraphMapNode node, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::graph::MapNode const&), haxorg_GraphMapNode>(&addNode, org_context, node); }

void haxorg_GraphMapGraph_addNodeWithProp(haxorg_GraphMapGraph __this, haxorg_GraphMapNode node, haxorg_GraphMapNodeProp prop, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::graph::MapNode const&, org::graph::MapNodeProp const&), haxorg_GraphMapNode, haxorg_GraphMapNodeProp>(&addNode, org_context, node, prop); }

bool haxorg_GraphMapGraph_hasEdge(haxorg_GraphMapGraph __this, haxorg_GraphMapNode source, haxorg_GraphMapNode target, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::graph::MapNode const&, org::graph::MapNode const&) const, haxorg_GraphMapNode, haxorg_GraphMapNode>(&hasEdge, org_context, source, target); }

bool haxorg_GraphMapGraph_hasNode(haxorg_GraphMapGraph __this, haxorg_GraphMapNode node, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::graph::MapNode const&) const, haxorg_GraphMapNode>(&hasNode, org_context, node); }

bool haxorg_GraphMapGraph_has2AdapterEdge(haxorg_GraphMapGraph __this, haxorg_ImmAdapter source, haxorg_ImmAdapter target, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmAdapter const&, org::imm::ImmAdapter const&) const, haxorg_ImmAdapter, haxorg_ImmAdapter>(&hasEdge, org_context, source, target); }

void haxorg_destroy_GraphMapGraph(haxorg_GraphMapGraph* obj) { org::bind::c::execute_destroy<org::graph::MapGraph>(obj); }

void haxorg_destroy_GraphMapConfig(haxorg_GraphMapConfig* obj) { org::bind::c::execute_destroy<org::graph::MapConfig>(obj); }

haxorg_GraphMapGraph haxorg_GraphMapGraphState_getGraph(haxorg_GraphMapGraphState __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_GraphMapGraph, std::shared_ptr<org::graph::MapGraph>(*)() const>(&getGraph, org_context); }

haxorg_GraphMapGraphState haxorg_GraphMapGraphState_FromAstContext(haxorg_GraphMapGraphState __this, haxorg_ImmAstContext ast, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_GraphMapGraphState, std::shared_ptr<org::graph::MapGraphState>(*)(std::shared_ptr<org::imm::ImmAstContext>), haxorg_ImmAstContext>(&FromAstContext, org_context, ast); }

void haxorg_GraphMapGraphState_registerNode(haxorg_GraphMapGraphState __this, haxorg_GraphMapNodeProp node, haxorg_GraphMapConfig conf, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::graph::MapNodeProp const&, std::shared_ptr<org::graph::MapConfig> const&), haxorg_GraphMapNodeProp, haxorg_GraphMapConfig>(&registerNode, org_context, node, conf); }

void haxorg_GraphMapGraphState_addNode(haxorg_GraphMapGraphState __this, haxorg_ImmAdapter node, haxorg_GraphMapConfig conf, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&, std::shared_ptr<org::graph::MapConfig> const&), haxorg_ImmAdapter, haxorg_GraphMapConfig>(&addNode, org_context, node, conf); }

void haxorg_GraphMapGraphState_addNodeRec(haxorg_GraphMapGraphState __this, haxorg_ImmAstContext ast, haxorg_ImmAdapter node, haxorg_GraphMapConfig conf, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(std::shared_ptr<org::imm::ImmAstContext> const&, org::imm::ImmAdapter const&, std::shared_ptr<org::graph::MapConfig> const&), haxorg_ImmAstContext, haxorg_ImmAdapter, haxorg_GraphMapConfig>(&addNodeRec, org_context, ast, node, conf); }

haxorg_HstdVec haxorg_GraphMapGraphState_getUnresolvedSubtreeLinks(haxorg_GraphMapGraphState __this, haxorg_ImmSubtreeAdapter node, haxorg_GraphMapConfig conf, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<org::graph::MapLink>(*)(org::imm::ImmAdapterT<org::imm::ImmSubtree>, std::shared_ptr<org::graph::MapConfig> const&) const, haxorg_ImmSubtreeAdapter, haxorg_GraphMapConfig>(&getUnresolvedSubtreeLinks, org_context, node, conf); }

haxorg_StdOptional haxorg_GraphMapGraphState_getUnresolvedLink(haxorg_GraphMapGraphState __this, haxorg_ImmLinkAdapter node, haxorg_GraphMapConfig conf, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_StdOptional, std::optional<org::graph::MapLink>(*)(org::imm::ImmAdapterT<org::imm::ImmLink>, std::shared_ptr<org::graph::MapConfig> const&) const, haxorg_ImmLinkAdapter, haxorg_GraphMapConfig>(&getUnresolvedLink, org_context, node, conf); }

void haxorg_destroy_GraphMapGraphState(haxorg_GraphMapGraphState* obj) { org::bind::c::execute_destroy<org::graph::MapGraphState>(obj); }

bool haxorg_LispCode___eq__(haxorg_LispCode __this, haxorg_LispCode other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::LispCode const&) const, haxorg_LispCode>(&operator==, org_context, other); }

void haxorg_LispCode_LispCode(haxorg_LispCode __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&LispCode, org_context); }

bool haxorg_LispCode_isCall(haxorg_LispCode __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isCall, org_context); }

haxorg_LispCodeCall haxorg_LispCode_getCallConst(haxorg_LispCode __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LispCodeCall, org::sem::LispCode::Call const&(*)() const>(&getCall, org_context); }

haxorg_LispCodeCall haxorg_LispCode_getCallMut(haxorg_LispCode __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LispCodeCall, org::sem::LispCode::Call&(*)()>(&getCall, org_context); }

bool haxorg_LispCode_isList(haxorg_LispCode __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isList, org_context); }

haxorg_LispCodeList haxorg_LispCode_getListConst(haxorg_LispCode __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LispCodeList, org::sem::LispCode::List const&(*)() const>(&getList, org_context); }

haxorg_LispCodeList haxorg_LispCode_getListMut(haxorg_LispCode __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LispCodeList, org::sem::LispCode::List&(*)()>(&getList, org_context); }

bool haxorg_LispCode_isKeyValue(haxorg_LispCode __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isKeyValue, org_context); }

haxorg_LispCodeKeyValue haxorg_LispCode_getKeyValueConst(haxorg_LispCode __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LispCodeKeyValue, org::sem::LispCode::KeyValue const&(*)() const>(&getKeyValue, org_context); }

haxorg_LispCodeKeyValue haxorg_LispCode_getKeyValueMut(haxorg_LispCode __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LispCodeKeyValue, org::sem::LispCode::KeyValue&(*)()>(&getKeyValue, org_context); }

bool haxorg_LispCode_isNumber(haxorg_LispCode __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isNumber, org_context); }

haxorg_LispCodeNumber haxorg_LispCode_getNumberConst(haxorg_LispCode __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LispCodeNumber, org::sem::LispCode::Number const&(*)() const>(&getNumber, org_context); }

haxorg_LispCodeNumber haxorg_LispCode_getNumberMut(haxorg_LispCode __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LispCodeNumber, org::sem::LispCode::Number&(*)()>(&getNumber, org_context); }

bool haxorg_LispCode_isText(haxorg_LispCode __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isText, org_context); }

haxorg_LispCodeText haxorg_LispCode_getTextConst(haxorg_LispCode __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LispCodeText, org::sem::LispCode::Text const&(*)() const>(&getText, org_context); }

haxorg_LispCodeText haxorg_LispCode_getTextMut(haxorg_LispCode __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LispCodeText, org::sem::LispCode::Text&(*)()>(&getText, org_context); }

bool haxorg_LispCode_isIdent(haxorg_LispCode __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isIdent, org_context); }

haxorg_LispCodeIdent haxorg_LispCode_getIdentConst(haxorg_LispCode __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LispCodeIdent, org::sem::LispCode::Ident const&(*)() const>(&getIdent, org_context); }

haxorg_LispCodeIdent haxorg_LispCode_getIdentMut(haxorg_LispCode __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LispCodeIdent, org::sem::LispCode::Ident&(*)()>(&getIdent, org_context); }

bool haxorg_LispCode_isBoolean(haxorg_LispCode __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isBoolean, org_context); }

haxorg_LispCodeBoolean haxorg_LispCode_getBooleanConst(haxorg_LispCode __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LispCodeBoolean, org::sem::LispCode::Boolean const&(*)() const>(&getBoolean, org_context); }

haxorg_LispCodeBoolean haxorg_LispCode_getBooleanMut(haxorg_LispCode __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LispCodeBoolean, org::sem::LispCode::Boolean&(*)()>(&getBoolean, org_context); }

bool haxorg_LispCode_isReal(haxorg_LispCode __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isReal, org_context); }

haxorg_LispCodeReal haxorg_LispCode_getRealConst(haxorg_LispCode __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LispCodeReal, org::sem::LispCode::Real const&(*)() const>(&getReal, org_context); }

haxorg_LispCodeReal haxorg_LispCode_getRealMut(haxorg_LispCode __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LispCodeReal, org::sem::LispCode::Real&(*)()>(&getReal, org_context); }

haxorg_LispCodeKind haxorg_LispCode_getKind(haxorg_LispCode __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LispCodeKind, org::sem::LispCode::Kind(*)() const>(&getKind, org_context); }

bool haxorg_LispCodeCall___eq__(haxorg_LispCodeCall __this, haxorg_LispCodeCall other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::LispCode::Call const&) const, haxorg_LispCodeCall>(&operator==, org_context, other); }

void haxorg_LispCodeCall_Call(haxorg_LispCodeCall __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&Call, org_context); }

void haxorg_destroy_LispCodeCall(haxorg_LispCodeCall* obj) { org::bind::c::execute_destroy<org::sem::LispCode::Call>(obj); }

bool haxorg_LispCodeList___eq__(haxorg_LispCodeList __this, haxorg_LispCodeList other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::LispCode::List const&) const, haxorg_LispCodeList>(&operator==, org_context, other); }

void haxorg_LispCodeList_List(haxorg_LispCodeList __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&List, org_context); }

void haxorg_destroy_LispCodeList(haxorg_LispCodeList* obj) { org::bind::c::execute_destroy<org::sem::LispCode::List>(obj); }

bool haxorg_LispCodeKeyValue___eq__(haxorg_LispCodeKeyValue __this, haxorg_LispCodeKeyValue other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::LispCode::KeyValue const&) const, haxorg_LispCodeKeyValue>(&operator==, org_context, other); }

void haxorg_LispCodeKeyValue_KeyValue(haxorg_LispCodeKeyValue __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&KeyValue, org_context); }

void haxorg_destroy_LispCodeKeyValue(haxorg_LispCodeKeyValue* obj) { org::bind::c::execute_destroy<org::sem::LispCode::KeyValue>(obj); }

bool haxorg_LispCodeNumber___eq__(haxorg_LispCodeNumber __this, haxorg_LispCodeNumber other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::LispCode::Number const&) const, haxorg_LispCodeNumber>(&operator==, org_context, other); }

void haxorg_LispCodeNumber_Number(haxorg_LispCodeNumber __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&Number, org_context); }

void haxorg_destroy_LispCodeNumber(haxorg_LispCodeNumber* obj) { org::bind::c::execute_destroy<org::sem::LispCode::Number>(obj); }

bool haxorg_LispCodeText___eq__(haxorg_LispCodeText __this, haxorg_LispCodeText other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::LispCode::Text const&) const, haxorg_LispCodeText>(&operator==, org_context, other); }

void haxorg_LispCodeText_Text(haxorg_LispCodeText __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&Text, org_context); }

void haxorg_destroy_LispCodeText(haxorg_LispCodeText* obj) { org::bind::c::execute_destroy<org::sem::LispCode::Text>(obj); }

bool haxorg_LispCodeIdent___eq__(haxorg_LispCodeIdent __this, haxorg_LispCodeIdent other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::LispCode::Ident const&) const, haxorg_LispCodeIdent>(&operator==, org_context, other); }

void haxorg_LispCodeIdent_Ident(haxorg_LispCodeIdent __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&Ident, org_context); }

void haxorg_destroy_LispCodeIdent(haxorg_LispCodeIdent* obj) { org::bind::c::execute_destroy<org::sem::LispCode::Ident>(obj); }

bool haxorg_LispCodeBoolean___eq__(haxorg_LispCodeBoolean __this, haxorg_LispCodeBoolean other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::LispCode::Boolean const&) const, haxorg_LispCodeBoolean>(&operator==, org_context, other); }

void haxorg_LispCodeBoolean_Boolean(haxorg_LispCodeBoolean __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&Boolean, org_context); }

void haxorg_destroy_LispCodeBoolean(haxorg_LispCodeBoolean* obj) { org::bind::c::execute_destroy<org::sem::LispCode::Boolean>(obj); }

bool haxorg_LispCodeReal___eq__(haxorg_LispCodeReal __this, haxorg_LispCodeReal other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::LispCode::Real const&) const, haxorg_LispCodeReal>(&operator==, org_context, other); }

void haxorg_LispCodeReal_Real(haxorg_LispCodeReal __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&Real, org_context); }

void haxorg_destroy_LispCodeReal(haxorg_LispCodeReal* obj) { org::bind::c::execute_destroy<org::sem::LispCode::Real>(obj); }

void haxorg_destroy_LispCode(haxorg_LispCode* obj) { org::bind::c::execute_destroy<org::sem::LispCode>(obj); }

bool haxorg_Tblfm___eq__(haxorg_Tblfm __this, haxorg_Tblfm other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::Tblfm const&) const, haxorg_Tblfm>(&operator==, org_context, other); }

bool haxorg_TblfmExpr___eq__(haxorg_TblfmExpr __this, haxorg_TblfmExpr other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::Tblfm::Expr const&) const, haxorg_TblfmExpr>(&operator==, org_context, other); }

bool haxorg_TblfmExpr_isAxisRef(haxorg_TblfmExpr __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isAxisRef, org_context); }

haxorg_TblfmExprAxisRef haxorg_TblfmExpr_getAxisRefConst(haxorg_TblfmExpr __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRef, org::sem::Tblfm::Expr::AxisRef const&(*)() const>(&getAxisRef, org_context); }

haxorg_TblfmExprAxisRef haxorg_TblfmExpr_getAxisRefMut(haxorg_TblfmExpr __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRef, org::sem::Tblfm::Expr::AxisRef&(*)()>(&getAxisRef, org_context); }

bool haxorg_TblfmExpr_isAxisName(haxorg_TblfmExpr __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isAxisName, org_context); }

haxorg_TblfmExprAxisName haxorg_TblfmExpr_getAxisNameConst(haxorg_TblfmExpr __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_TblfmExprAxisName, org::sem::Tblfm::Expr::AxisName const&(*)() const>(&getAxisName, org_context); }

haxorg_TblfmExprAxisName haxorg_TblfmExpr_getAxisNameMut(haxorg_TblfmExpr __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_TblfmExprAxisName, org::sem::Tblfm::Expr::AxisName&(*)()>(&getAxisName, org_context); }

bool haxorg_TblfmExpr_isIntLiteral(haxorg_TblfmExpr __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isIntLiteral, org_context); }

haxorg_TblfmExprIntLiteral haxorg_TblfmExpr_getIntLiteralConst(haxorg_TblfmExpr __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_TblfmExprIntLiteral, org::sem::Tblfm::Expr::IntLiteral const&(*)() const>(&getIntLiteral, org_context); }

haxorg_TblfmExprIntLiteral haxorg_TblfmExpr_getIntLiteralMut(haxorg_TblfmExpr __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_TblfmExprIntLiteral, org::sem::Tblfm::Expr::IntLiteral&(*)()>(&getIntLiteral, org_context); }

bool haxorg_TblfmExpr_isFloatLiteral(haxorg_TblfmExpr __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isFloatLiteral, org_context); }

haxorg_TblfmExprFloatLiteral haxorg_TblfmExpr_getFloatLiteralConst(haxorg_TblfmExpr __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_TblfmExprFloatLiteral, org::sem::Tblfm::Expr::FloatLiteral const&(*)() const>(&getFloatLiteral, org_context); }

haxorg_TblfmExprFloatLiteral haxorg_TblfmExpr_getFloatLiteralMut(haxorg_TblfmExpr __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_TblfmExprFloatLiteral, org::sem::Tblfm::Expr::FloatLiteral&(*)()>(&getFloatLiteral, org_context); }

bool haxorg_TblfmExpr_isRangeRef(haxorg_TblfmExpr __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isRangeRef, org_context); }

haxorg_TblfmExprRangeRef haxorg_TblfmExpr_getRangeRefConst(haxorg_TblfmExpr __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_TblfmExprRangeRef, org::sem::Tblfm::Expr::RangeRef const&(*)() const>(&getRangeRef, org_context); }

haxorg_TblfmExprRangeRef haxorg_TblfmExpr_getRangeRefMut(haxorg_TblfmExpr __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_TblfmExprRangeRef, org::sem::Tblfm::Expr::RangeRef&(*)()>(&getRangeRef, org_context); }

bool haxorg_TblfmExpr_isCall(haxorg_TblfmExpr __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isCall, org_context); }

haxorg_TblfmExprCall haxorg_TblfmExpr_getCallConst(haxorg_TblfmExpr __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_TblfmExprCall, org::sem::Tblfm::Expr::Call const&(*)() const>(&getCall, org_context); }

haxorg_TblfmExprCall haxorg_TblfmExpr_getCallMut(haxorg_TblfmExpr __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_TblfmExprCall, org::sem::Tblfm::Expr::Call&(*)()>(&getCall, org_context); }

bool haxorg_TblfmExpr_isElisp(haxorg_TblfmExpr __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isElisp, org_context); }

haxorg_TblfmExprElisp haxorg_TblfmExpr_getElispConst(haxorg_TblfmExpr __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_TblfmExprElisp, org::sem::Tblfm::Expr::Elisp const&(*)() const>(&getElisp, org_context); }

haxorg_TblfmExprElisp haxorg_TblfmExpr_getElispMut(haxorg_TblfmExpr __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_TblfmExprElisp, org::sem::Tblfm::Expr::Elisp&(*)()>(&getElisp, org_context); }

haxorg_TblfmExprKind haxorg_TblfmExpr_getKind(haxorg_TblfmExpr __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_TblfmExprKind, org::sem::Tblfm::Expr::Kind(*)() const>(&getKind, org_context); }

bool haxorg_TblfmExprAxisRef___eq__(haxorg_TblfmExprAxisRef __this, haxorg_TblfmExprAxisRef other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::Tblfm::Expr::AxisRef const&) const, haxorg_TblfmExprAxisRef>(&operator==, org_context, other); }

bool haxorg_TblfmExprAxisRefPosition___eq__(haxorg_TblfmExprAxisRefPosition __this, haxorg_TblfmExprAxisRefPosition other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::Tblfm::Expr::AxisRef::Position const&) const, haxorg_TblfmExprAxisRefPosition>(&operator==, org_context, other); }

bool haxorg_TblfmExprAxisRefPosition_isIndex(haxorg_TblfmExprAxisRefPosition __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isIndex, org_context); }

haxorg_TblfmExprAxisRefPositionIndex haxorg_TblfmExprAxisRefPosition_getIndexConst(haxorg_TblfmExprAxisRefPosition __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPositionIndex, org::sem::Tblfm::Expr::AxisRef::Position::Index const&(*)() const>(&getIndex, org_context); }

haxorg_TblfmExprAxisRefPositionIndex haxorg_TblfmExprAxisRefPosition_getIndexMut(haxorg_TblfmExprAxisRefPosition __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPositionIndex, org::sem::Tblfm::Expr::AxisRef::Position::Index&(*)()>(&getIndex, org_context); }

bool haxorg_TblfmExprAxisRefPosition_isName(haxorg_TblfmExprAxisRefPosition __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isName, org_context); }

haxorg_TblfmExprAxisRefPositionName haxorg_TblfmExprAxisRefPosition_getNameConst(haxorg_TblfmExprAxisRefPosition __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPositionName, org::sem::Tblfm::Expr::AxisRef::Position::Name const&(*)() const>(&getName, org_context); }

haxorg_TblfmExprAxisRefPositionName haxorg_TblfmExprAxisRefPosition_getNameMut(haxorg_TblfmExprAxisRefPosition __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPositionName, org::sem::Tblfm::Expr::AxisRef::Position::Name&(*)()>(&getName, org_context); }

haxorg_TblfmExprAxisRefPositionKind haxorg_TblfmExprAxisRefPosition_getKind(haxorg_TblfmExprAxisRefPosition __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPositionKind, org::sem::Tblfm::Expr::AxisRef::Position::Kind(*)() const>(&getKind, org_context); }

bool haxorg_TblfmExprAxisRefPositionIndex___eq__(haxorg_TblfmExprAxisRefPositionIndex __this, haxorg_TblfmExprAxisRefPositionIndex other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::Tblfm::Expr::AxisRef::Position::Index const&) const, haxorg_TblfmExprAxisRefPositionIndex>(&operator==, org_context, other); }

void haxorg_destroy_TblfmExprAxisRefPositionIndex(haxorg_TblfmExprAxisRefPositionIndex* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::AxisRef::Position::Index>(obj); }

bool haxorg_TblfmExprAxisRefPositionName___eq__(haxorg_TblfmExprAxisRefPositionName __this, haxorg_TblfmExprAxisRefPositionName other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::Tblfm::Expr::AxisRef::Position::Name const&) const, haxorg_TblfmExprAxisRefPositionName>(&operator==, org_context, other); }

void haxorg_destroy_TblfmExprAxisRefPositionName(haxorg_TblfmExprAxisRefPositionName* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::AxisRef::Position::Name>(obj); }

void haxorg_destroy_TblfmExprAxisRefPosition(haxorg_TblfmExprAxisRefPosition* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::AxisRef::Position>(obj); }

void haxorg_destroy_TblfmExprAxisRef(haxorg_TblfmExprAxisRef* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::AxisRef>(obj); }

bool haxorg_TblfmExprAxisName___eq__(haxorg_TblfmExprAxisName __this, haxorg_TblfmExprAxisName other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::Tblfm::Expr::AxisName const&) const, haxorg_TblfmExprAxisName>(&operator==, org_context, other); }

void haxorg_destroy_TblfmExprAxisName(haxorg_TblfmExprAxisName* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::AxisName>(obj); }

bool haxorg_TblfmExprIntLiteral___eq__(haxorg_TblfmExprIntLiteral __this, haxorg_TblfmExprIntLiteral other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::Tblfm::Expr::IntLiteral const&) const, haxorg_TblfmExprIntLiteral>(&operator==, org_context, other); }

void haxorg_destroy_TblfmExprIntLiteral(haxorg_TblfmExprIntLiteral* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::IntLiteral>(obj); }

bool haxorg_TblfmExprFloatLiteral___eq__(haxorg_TblfmExprFloatLiteral __this, haxorg_TblfmExprFloatLiteral other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::Tblfm::Expr::FloatLiteral const&) const, haxorg_TblfmExprFloatLiteral>(&operator==, org_context, other); }

void haxorg_destroy_TblfmExprFloatLiteral(haxorg_TblfmExprFloatLiteral* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::FloatLiteral>(obj); }

bool haxorg_TblfmExprRangeRef___eq__(haxorg_TblfmExprRangeRef __this, haxorg_TblfmExprRangeRef other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::Tblfm::Expr::RangeRef const&) const, haxorg_TblfmExprRangeRef>(&operator==, org_context, other); }

void haxorg_destroy_TblfmExprRangeRef(haxorg_TblfmExprRangeRef* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::RangeRef>(obj); }

bool haxorg_TblfmExprCall___eq__(haxorg_TblfmExprCall __this, haxorg_TblfmExprCall other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::Tblfm::Expr::Call const&) const, haxorg_TblfmExprCall>(&operator==, org_context, other); }

void haxorg_destroy_TblfmExprCall(haxorg_TblfmExprCall* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::Call>(obj); }

bool haxorg_TblfmExprElisp___eq__(haxorg_TblfmExprElisp __this, haxorg_TblfmExprElisp other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::Tblfm::Expr::Elisp const&) const, haxorg_TblfmExprElisp>(&operator==, org_context, other); }

void haxorg_destroy_TblfmExprElisp(haxorg_TblfmExprElisp* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::Elisp>(obj); }

void haxorg_destroy_TblfmExpr(haxorg_TblfmExpr* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr>(obj); }

bool haxorg_TblfmAssign___eq__(haxorg_TblfmAssign __this, haxorg_TblfmAssign other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::Tblfm::Assign const&) const, haxorg_TblfmAssign>(&operator==, org_context, other); }

void haxorg_destroy_TblfmAssign(haxorg_TblfmAssign* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Assign>(obj); }

void haxorg_destroy_Tblfm(haxorg_Tblfm* obj) { org::bind::c::execute_destroy<org::sem::Tblfm>(obj); }

haxorg_HstdOpt haxorg_AttrValue_getBool(haxorg_AttrValue __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<bool>(*)() const>(&getBool, org_context); }

haxorg_HstdOpt haxorg_AttrValue_getInt(haxorg_AttrValue __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<int>(*)() const>(&getInt, org_context); }

haxorg_HstdStr haxorg_AttrValue_getString(haxorg_AttrValue __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str(*)() const>(&getString, org_context); }

haxorg_HstdOpt haxorg_AttrValue_getDouble(haxorg_AttrValue __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<double>(*)() const>(&getDouble, org_context); }

bool haxorg_AttrValue___eq__(haxorg_AttrValue __this, haxorg_AttrValue other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::AttrValue const&) const, haxorg_AttrValue>(&operator==, org_context, other); }

void haxorg_AttrValue_AttrValue(haxorg_AttrValue __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&AttrValue, org_context); }

bool haxorg_AttrValue_isTextValue(haxorg_AttrValue __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isTextValue, org_context); }

haxorg_AttrValueTextValue haxorg_AttrValue_getTextValueConst(haxorg_AttrValue __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_AttrValueTextValue, org::sem::AttrValue::TextValue const&(*)() const>(&getTextValue, org_context); }

haxorg_AttrValueTextValue haxorg_AttrValue_getTextValueMut(haxorg_AttrValue __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_AttrValueTextValue, org::sem::AttrValue::TextValue&(*)()>(&getTextValue, org_context); }

bool haxorg_AttrValue_isFileReference(haxorg_AttrValue __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isFileReference, org_context); }

haxorg_AttrValueFileReference haxorg_AttrValue_getFileReferenceConst(haxorg_AttrValue __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_AttrValueFileReference, org::sem::AttrValue::FileReference const&(*)() const>(&getFileReference, org_context); }

haxorg_AttrValueFileReference haxorg_AttrValue_getFileReferenceMut(haxorg_AttrValue __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_AttrValueFileReference, org::sem::AttrValue::FileReference&(*)()>(&getFileReference, org_context); }

bool haxorg_AttrValue_isLispValue(haxorg_AttrValue __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isLispValue, org_context); }

haxorg_AttrValueLispValue haxorg_AttrValue_getLispValueConst(haxorg_AttrValue __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_AttrValueLispValue, org::sem::AttrValue::LispValue const&(*)() const>(&getLispValue, org_context); }

haxorg_AttrValueLispValue haxorg_AttrValue_getLispValueMut(haxorg_AttrValue __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_AttrValueLispValue, org::sem::AttrValue::LispValue&(*)()>(&getLispValue, org_context); }

haxorg_AttrValueKind haxorg_AttrValue_getKind(haxorg_AttrValue __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_AttrValueKind, org::sem::AttrValue::Kind(*)() const>(&getKind, org_context); }

void haxorg_AttrValueDimensionSpan_DimensionSpan(haxorg_AttrValueDimensionSpan __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&DimensionSpan, org_context); }

bool haxorg_AttrValueDimensionSpan___eq__(haxorg_AttrValueDimensionSpan __this, haxorg_AttrValueDimensionSpan other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::AttrValue::DimensionSpan const&) const, haxorg_AttrValueDimensionSpan>(&operator==, org_context, other); }

void haxorg_destroy_AttrValueDimensionSpan(haxorg_AttrValueDimensionSpan* obj) { org::bind::c::execute_destroy<org::sem::AttrValue::DimensionSpan>(obj); }

bool haxorg_AttrValueTextValue___eq__(haxorg_AttrValueTextValue __this, haxorg_AttrValueTextValue other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::AttrValue::TextValue const&) const, haxorg_AttrValueTextValue>(&operator==, org_context, other); }

void haxorg_AttrValueTextValue_TextValue(haxorg_AttrValueTextValue __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&TextValue, org_context); }

void haxorg_destroy_AttrValueTextValue(haxorg_AttrValueTextValue* obj) { org::bind::c::execute_destroy<org::sem::AttrValue::TextValue>(obj); }

void haxorg_AttrValueFileReference_FileReference(haxorg_AttrValueFileReference __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&FileReference, org_context); }

bool haxorg_AttrValueFileReference___eq__(haxorg_AttrValueFileReference __this, haxorg_AttrValueFileReference other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::AttrValue::FileReference const&) const, haxorg_AttrValueFileReference>(&operator==, org_context, other); }

void haxorg_destroy_AttrValueFileReference(haxorg_AttrValueFileReference* obj) { org::bind::c::execute_destroy<org::sem::AttrValue::FileReference>(obj); }

bool haxorg_AttrValueLispValue___eq__(haxorg_AttrValueLispValue __this, haxorg_AttrValueLispValue other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::AttrValue::LispValue const&) const, haxorg_AttrValueLispValue>(&operator==, org_context, other); }

void haxorg_AttrValueLispValue_LispValue(haxorg_AttrValueLispValue __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&LispValue, org_context); }

void haxorg_destroy_AttrValueLispValue(haxorg_AttrValueLispValue* obj) { org::bind::c::execute_destroy<org::sem::AttrValue::LispValue>(obj); }

void haxorg_destroy_AttrValue(haxorg_AttrValue* obj) { org::bind::c::execute_destroy<org::sem::AttrValue>(obj); }

bool haxorg_HashTagFlat___eq__(haxorg_HashTagFlat __this, haxorg_HashTagFlat other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::HashTagFlat const&) const, haxorg_HashTagFlat>(&operator==, org_context, other); }

bool haxorg_HashTagFlat___lt__(haxorg_HashTagFlat __this, haxorg_HashTagFlat other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::HashTagFlat const&) const, haxorg_HashTagFlat>(&operator<, org_context, other); }

void haxorg_destroy_HashTagFlat(haxorg_HashTagFlat* obj) { org::bind::c::execute_destroy<org::sem::HashTagFlat>(obj); }

bool haxorg_TodoKeyword___eq__(haxorg_TodoKeyword __this, haxorg_TodoKeyword other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::TodoKeyword const&) const, haxorg_TodoKeyword>(&operator==, org_context, other); }

void haxorg_destroy_TodoKeyword(haxorg_TodoKeyword* obj) { org::bind::c::execute_destroy<org::sem::TodoKeyword>(obj); }

bool haxorg_HashTagText___eq__(haxorg_HashTagText __this, haxorg_HashTagText other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::HashTagText const&) const, haxorg_HashTagText>(&operator==, org_context, other); }

bool haxorg_HashTagText_prefixMatch(haxorg_HashTagText __this, haxorg_HstdVec prefix, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(hstd::Vec<hstd::Str> const&) const, haxorg_HstdVec>(&prefixMatch, org_context, prefix); }

haxorg_HstdVec haxorg_HashTagText_getFlatHashes(haxorg_HashTagText __this, bool withIntermediate, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<org::sem::HashTagFlat>(*)(bool) const, bool>(&getFlatHashes, org_context, withIntermediate); }

void haxorg_destroy_HashTagText(haxorg_HashTagText* obj) { org::bind::c::execute_destroy<org::sem::HashTagText>(obj); }

bool haxorg_SubtreePath___eq__(haxorg_SubtreePath __this, haxorg_SubtreePath other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::SubtreePath const&) const, haxorg_SubtreePath>(&operator==, org_context, other); }

void haxorg_destroy_SubtreePath(haxorg_SubtreePath* obj) { org::bind::c::execute_destroy<org::sem::SubtreePath>(obj); }

bool haxorg_LinkTarget___eq__(haxorg_LinkTarget __this, haxorg_LinkTarget other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::LinkTarget const&) const, haxorg_LinkTarget>(&operator==, org_context, other); }

bool haxorg_LinkTarget_isRaw(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isRaw, org_context); }

haxorg_LinkTargetRaw haxorg_LinkTarget_getRawConst(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LinkTargetRaw, org::sem::LinkTarget::Raw const&(*)() const>(&getRaw, org_context); }

haxorg_LinkTargetRaw haxorg_LinkTarget_getRawMut(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LinkTargetRaw, org::sem::LinkTarget::Raw&(*)()>(&getRaw, org_context); }

bool haxorg_LinkTarget_isId(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isId, org_context); }

haxorg_LinkTargetId haxorg_LinkTarget_getIdConst(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LinkTargetId, org::sem::LinkTarget::Id const&(*)() const>(&getId, org_context); }

haxorg_LinkTargetId haxorg_LinkTarget_getIdMut(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LinkTargetId, org::sem::LinkTarget::Id&(*)()>(&getId, org_context); }

bool haxorg_LinkTarget_isCustomId(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isCustomId, org_context); }

haxorg_LinkTargetCustomId haxorg_LinkTarget_getCustomIdConst(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LinkTargetCustomId, org::sem::LinkTarget::CustomId const&(*)() const>(&getCustomId, org_context); }

haxorg_LinkTargetCustomId haxorg_LinkTarget_getCustomIdMut(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LinkTargetCustomId, org::sem::LinkTarget::CustomId&(*)()>(&getCustomId, org_context); }

bool haxorg_LinkTarget_isSubtreeTitle(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isSubtreeTitle, org_context); }

haxorg_LinkTargetSubtreeTitle haxorg_LinkTarget_getSubtreeTitleConst(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LinkTargetSubtreeTitle, org::sem::LinkTarget::SubtreeTitle const&(*)() const>(&getSubtreeTitle, org_context); }

haxorg_LinkTargetSubtreeTitle haxorg_LinkTarget_getSubtreeTitleMut(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LinkTargetSubtreeTitle, org::sem::LinkTarget::SubtreeTitle&(*)()>(&getSubtreeTitle, org_context); }

bool haxorg_LinkTarget_isPerson(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isPerson, org_context); }

haxorg_LinkTargetPerson haxorg_LinkTarget_getPersonConst(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LinkTargetPerson, org::sem::LinkTarget::Person const&(*)() const>(&getPerson, org_context); }

haxorg_LinkTargetPerson haxorg_LinkTarget_getPersonMut(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LinkTargetPerson, org::sem::LinkTarget::Person&(*)()>(&getPerson, org_context); }

bool haxorg_LinkTarget_isUserProtocol(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isUserProtocol, org_context); }

haxorg_LinkTargetUserProtocol haxorg_LinkTarget_getUserProtocolConst(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LinkTargetUserProtocol, org::sem::LinkTarget::UserProtocol const&(*)() const>(&getUserProtocol, org_context); }

haxorg_LinkTargetUserProtocol haxorg_LinkTarget_getUserProtocolMut(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LinkTargetUserProtocol, org::sem::LinkTarget::UserProtocol&(*)()>(&getUserProtocol, org_context); }

bool haxorg_LinkTarget_isInternal(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isInternal, org_context); }

haxorg_LinkTargetInternal haxorg_LinkTarget_getInternalConst(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LinkTargetInternal, org::sem::LinkTarget::Internal const&(*)() const>(&getInternal, org_context); }

haxorg_LinkTargetInternal haxorg_LinkTarget_getInternalMut(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LinkTargetInternal, org::sem::LinkTarget::Internal&(*)()>(&getInternal, org_context); }

bool haxorg_LinkTarget_isFootnote(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isFootnote, org_context); }

haxorg_LinkTargetFootnote haxorg_LinkTarget_getFootnoteConst(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LinkTargetFootnote, org::sem::LinkTarget::Footnote const&(*)() const>(&getFootnote, org_context); }

haxorg_LinkTargetFootnote haxorg_LinkTarget_getFootnoteMut(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LinkTargetFootnote, org::sem::LinkTarget::Footnote&(*)()>(&getFootnote, org_context); }

bool haxorg_LinkTarget_isFile(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isFile, org_context); }

haxorg_LinkTargetFile haxorg_LinkTarget_getFileConst(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LinkTargetFile, org::sem::LinkTarget::File const&(*)() const>(&getFile, org_context); }

haxorg_LinkTargetFile haxorg_LinkTarget_getFileMut(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LinkTargetFile, org::sem::LinkTarget::File&(*)()>(&getFile, org_context); }

bool haxorg_LinkTarget_isAttachment(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isAttachment, org_context); }

haxorg_LinkTargetAttachment haxorg_LinkTarget_getAttachmentConst(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LinkTargetAttachment, org::sem::LinkTarget::Attachment const&(*)() const>(&getAttachment, org_context); }

haxorg_LinkTargetAttachment haxorg_LinkTarget_getAttachmentMut(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LinkTargetAttachment, org::sem::LinkTarget::Attachment&(*)()>(&getAttachment, org_context); }

haxorg_LinkTargetKind haxorg_LinkTarget_getKind(haxorg_LinkTarget __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LinkTargetKind, org::sem::LinkTarget::Kind(*)() const>(&getKind, org_context); }

bool haxorg_LinkTargetRaw___eq__(haxorg_LinkTargetRaw __this, haxorg_LinkTargetRaw other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::LinkTarget::Raw const&) const, haxorg_LinkTargetRaw>(&operator==, org_context, other); }

void haxorg_destroy_LinkTargetRaw(haxorg_LinkTargetRaw* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::Raw>(obj); }

bool haxorg_LinkTargetId___eq__(haxorg_LinkTargetId __this, haxorg_LinkTargetId other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::LinkTarget::Id const&) const, haxorg_LinkTargetId>(&operator==, org_context, other); }

void haxorg_destroy_LinkTargetId(haxorg_LinkTargetId* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::Id>(obj); }

bool haxorg_LinkTargetCustomId___eq__(haxorg_LinkTargetCustomId __this, haxorg_LinkTargetCustomId other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::LinkTarget::CustomId const&) const, haxorg_LinkTargetCustomId>(&operator==, org_context, other); }

void haxorg_destroy_LinkTargetCustomId(haxorg_LinkTargetCustomId* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::CustomId>(obj); }

bool haxorg_LinkTargetSubtreeTitle___eq__(haxorg_LinkTargetSubtreeTitle __this, haxorg_LinkTargetSubtreeTitle other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::LinkTarget::SubtreeTitle const&) const, haxorg_LinkTargetSubtreeTitle>(&operator==, org_context, other); }

void haxorg_destroy_LinkTargetSubtreeTitle(haxorg_LinkTargetSubtreeTitle* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::SubtreeTitle>(obj); }

bool haxorg_LinkTargetPerson___eq__(haxorg_LinkTargetPerson __this, haxorg_LinkTargetPerson other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::LinkTarget::Person const&) const, haxorg_LinkTargetPerson>(&operator==, org_context, other); }

void haxorg_destroy_LinkTargetPerson(haxorg_LinkTargetPerson* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::Person>(obj); }

bool haxorg_LinkTargetUserProtocol___eq__(haxorg_LinkTargetUserProtocol __this, haxorg_LinkTargetUserProtocol other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::LinkTarget::UserProtocol const&) const, haxorg_LinkTargetUserProtocol>(&operator==, org_context, other); }

void haxorg_destroy_LinkTargetUserProtocol(haxorg_LinkTargetUserProtocol* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::UserProtocol>(obj); }

bool haxorg_LinkTargetInternal___eq__(haxorg_LinkTargetInternal __this, haxorg_LinkTargetInternal other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::LinkTarget::Internal const&) const, haxorg_LinkTargetInternal>(&operator==, org_context, other); }

void haxorg_destroy_LinkTargetInternal(haxorg_LinkTargetInternal* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::Internal>(obj); }

bool haxorg_LinkTargetFootnote___eq__(haxorg_LinkTargetFootnote __this, haxorg_LinkTargetFootnote other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::LinkTarget::Footnote const&) const, haxorg_LinkTargetFootnote>(&operator==, org_context, other); }

void haxorg_destroy_LinkTargetFootnote(haxorg_LinkTargetFootnote* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::Footnote>(obj); }

bool haxorg_LinkTargetFile___eq__(haxorg_LinkTargetFile __this, haxorg_LinkTargetFile other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::LinkTarget::File const&) const, haxorg_LinkTargetFile>(&operator==, org_context, other); }

void haxorg_destroy_LinkTargetFile(haxorg_LinkTargetFile* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::File>(obj); }

bool haxorg_LinkTargetAttachment___eq__(haxorg_LinkTargetAttachment __this, haxorg_LinkTargetAttachment other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::LinkTarget::Attachment const&) const, haxorg_LinkTargetAttachment>(&operator==, org_context, other); }

void haxorg_destroy_LinkTargetAttachment(haxorg_LinkTargetAttachment* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::Attachment>(obj); }

void haxorg_destroy_LinkTarget(haxorg_LinkTarget* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget>(obj); }

bool haxorg_SubtreeLogHead___eq__(haxorg_SubtreeLogHead __this, haxorg_SubtreeLogHead other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::SubtreeLogHead const&) const, haxorg_SubtreeLogHead>(&operator==, org_context, other); }

bool haxorg_SubtreeLogHead_isPriority(haxorg_SubtreeLogHead __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isPriority, org_context); }

haxorg_SubtreeLogHeadPriority haxorg_SubtreeLogHead_getPriorityConst(haxorg_SubtreeLogHead __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadPriority, org::sem::SubtreeLogHead::Priority const&(*)() const>(&getPriority, org_context); }

haxorg_SubtreeLogHeadPriority haxorg_SubtreeLogHead_getPriorityMut(haxorg_SubtreeLogHead __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadPriority, org::sem::SubtreeLogHead::Priority&(*)()>(&getPriority, org_context); }

bool haxorg_SubtreeLogHead_isNote(haxorg_SubtreeLogHead __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isNote, org_context); }

haxorg_SubtreeLogHeadNote haxorg_SubtreeLogHead_getNoteConst(haxorg_SubtreeLogHead __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadNote, org::sem::SubtreeLogHead::Note const&(*)() const>(&getNote, org_context); }

haxorg_SubtreeLogHeadNote haxorg_SubtreeLogHead_getNoteMut(haxorg_SubtreeLogHead __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadNote, org::sem::SubtreeLogHead::Note&(*)()>(&getNote, org_context); }

bool haxorg_SubtreeLogHead_isRefile(haxorg_SubtreeLogHead __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isRefile, org_context); }

haxorg_SubtreeLogHeadRefile haxorg_SubtreeLogHead_getRefileConst(haxorg_SubtreeLogHead __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadRefile, org::sem::SubtreeLogHead::Refile const&(*)() const>(&getRefile, org_context); }

haxorg_SubtreeLogHeadRefile haxorg_SubtreeLogHead_getRefileMut(haxorg_SubtreeLogHead __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadRefile, org::sem::SubtreeLogHead::Refile&(*)()>(&getRefile, org_context); }

bool haxorg_SubtreeLogHead_isClock(haxorg_SubtreeLogHead __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isClock, org_context); }

haxorg_SubtreeLogHeadClock haxorg_SubtreeLogHead_getClockConst(haxorg_SubtreeLogHead __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadClock, org::sem::SubtreeLogHead::Clock const&(*)() const>(&getClock, org_context); }

haxorg_SubtreeLogHeadClock haxorg_SubtreeLogHead_getClockMut(haxorg_SubtreeLogHead __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadClock, org::sem::SubtreeLogHead::Clock&(*)()>(&getClock, org_context); }

bool haxorg_SubtreeLogHead_isState(haxorg_SubtreeLogHead __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isState, org_context); }

haxorg_SubtreeLogHeadState haxorg_SubtreeLogHead_getStateConst(haxorg_SubtreeLogHead __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadState, org::sem::SubtreeLogHead::State const&(*)() const>(&getState, org_context); }

haxorg_SubtreeLogHeadState haxorg_SubtreeLogHead_getStateMut(haxorg_SubtreeLogHead __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadState, org::sem::SubtreeLogHead::State&(*)()>(&getState, org_context); }

bool haxorg_SubtreeLogHead_isDeadline(haxorg_SubtreeLogHead __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isDeadline, org_context); }

haxorg_SubtreeLogHeadDeadline haxorg_SubtreeLogHead_getDeadlineConst(haxorg_SubtreeLogHead __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadDeadline, org::sem::SubtreeLogHead::Deadline const&(*)() const>(&getDeadline, org_context); }

haxorg_SubtreeLogHeadDeadline haxorg_SubtreeLogHead_getDeadlineMut(haxorg_SubtreeLogHead __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadDeadline, org::sem::SubtreeLogHead::Deadline&(*)()>(&getDeadline, org_context); }

bool haxorg_SubtreeLogHead_isSchedule(haxorg_SubtreeLogHead __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isSchedule, org_context); }

haxorg_SubtreeLogHeadSchedule haxorg_SubtreeLogHead_getScheduleConst(haxorg_SubtreeLogHead __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadSchedule, org::sem::SubtreeLogHead::Schedule const&(*)() const>(&getSchedule, org_context); }

haxorg_SubtreeLogHeadSchedule haxorg_SubtreeLogHead_getScheduleMut(haxorg_SubtreeLogHead __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadSchedule, org::sem::SubtreeLogHead::Schedule&(*)()>(&getSchedule, org_context); }

bool haxorg_SubtreeLogHead_isTag(haxorg_SubtreeLogHead __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isTag, org_context); }

haxorg_SubtreeLogHeadTag haxorg_SubtreeLogHead_getTagConst(haxorg_SubtreeLogHead __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadTag, org::sem::SubtreeLogHead::Tag const&(*)() const>(&getTag, org_context); }

haxorg_SubtreeLogHeadTag haxorg_SubtreeLogHead_getTagMut(haxorg_SubtreeLogHead __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadTag, org::sem::SubtreeLogHead::Tag&(*)()>(&getTag, org_context); }

bool haxorg_SubtreeLogHead_isUnknown(haxorg_SubtreeLogHead __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isUnknown, org_context); }

haxorg_SubtreeLogHeadUnknown haxorg_SubtreeLogHead_getUnknownConst(haxorg_SubtreeLogHead __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadUnknown, org::sem::SubtreeLogHead::Unknown const&(*)() const>(&getUnknown, org_context); }

haxorg_SubtreeLogHeadUnknown haxorg_SubtreeLogHead_getUnknownMut(haxorg_SubtreeLogHead __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadUnknown, org::sem::SubtreeLogHead::Unknown&(*)()>(&getUnknown, org_context); }

haxorg_SubtreeLogHeadKind haxorg_SubtreeLogHead_getLogKind(haxorg_SubtreeLogHead __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadKind, org::sem::SubtreeLogHead::Kind(*)() const>(&getLogKind, org_context); }

bool haxorg_SubtreeLogHeadPriority___eq__(haxorg_SubtreeLogHeadPriority __this, haxorg_SubtreeLogHeadPriority other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::SubtreeLogHead::Priority const&) const, haxorg_SubtreeLogHeadPriority>(&operator==, org_context, other); }

void haxorg_destroy_SubtreeLogHeadPriority(haxorg_SubtreeLogHeadPriority* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Priority>(obj); }

bool haxorg_SubtreeLogHeadNote___eq__(haxorg_SubtreeLogHeadNote __this, haxorg_SubtreeLogHeadNote other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::SubtreeLogHead::Note const&) const, haxorg_SubtreeLogHeadNote>(&operator==, org_context, other); }

void haxorg_destroy_SubtreeLogHeadNote(haxorg_SubtreeLogHeadNote* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Note>(obj); }

bool haxorg_SubtreeLogHeadRefile___eq__(haxorg_SubtreeLogHeadRefile __this, haxorg_SubtreeLogHeadRefile other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::SubtreeLogHead::Refile const&) const, haxorg_SubtreeLogHeadRefile>(&operator==, org_context, other); }

void haxorg_destroy_SubtreeLogHeadRefile(haxorg_SubtreeLogHeadRefile* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Refile>(obj); }

bool haxorg_SubtreeLogHeadClock___eq__(haxorg_SubtreeLogHeadClock __this, haxorg_SubtreeLogHeadClock other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::SubtreeLogHead::Clock const&) const, haxorg_SubtreeLogHeadClock>(&operator==, org_context, other); }

void haxorg_destroy_SubtreeLogHeadClock(haxorg_SubtreeLogHeadClock* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Clock>(obj); }

bool haxorg_SubtreeLogHeadState___eq__(haxorg_SubtreeLogHeadState __this, haxorg_SubtreeLogHeadState other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::SubtreeLogHead::State const&) const, haxorg_SubtreeLogHeadState>(&operator==, org_context, other); }

void haxorg_destroy_SubtreeLogHeadState(haxorg_SubtreeLogHeadState* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::State>(obj); }

bool haxorg_SubtreeLogHeadDeadline___eq__(haxorg_SubtreeLogHeadDeadline __this, haxorg_SubtreeLogHeadDeadline other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::SubtreeLogHead::Deadline const&) const, haxorg_SubtreeLogHeadDeadline>(&operator==, org_context, other); }

void haxorg_destroy_SubtreeLogHeadDeadline(haxorg_SubtreeLogHeadDeadline* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Deadline>(obj); }

bool haxorg_SubtreeLogHeadSchedule___eq__(haxorg_SubtreeLogHeadSchedule __this, haxorg_SubtreeLogHeadSchedule other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::SubtreeLogHead::Schedule const&) const, haxorg_SubtreeLogHeadSchedule>(&operator==, org_context, other); }

void haxorg_destroy_SubtreeLogHeadSchedule(haxorg_SubtreeLogHeadSchedule* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Schedule>(obj); }

bool haxorg_SubtreeLogHeadTag___eq__(haxorg_SubtreeLogHeadTag __this, haxorg_SubtreeLogHeadTag other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::SubtreeLogHead::Tag const&) const, haxorg_SubtreeLogHeadTag>(&operator==, org_context, other); }

void haxorg_destroy_SubtreeLogHeadTag(haxorg_SubtreeLogHeadTag* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Tag>(obj); }

bool haxorg_SubtreeLogHeadUnknown___eq__(haxorg_SubtreeLogHeadUnknown __this, haxorg_SubtreeLogHeadUnknown other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::SubtreeLogHead::Unknown const&) const, haxorg_SubtreeLogHeadUnknown>(&operator==, org_context, other); }

void haxorg_destroy_SubtreeLogHeadUnknown(haxorg_SubtreeLogHeadUnknown* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Unknown>(obj); }

void haxorg_destroy_SubtreeLogHead(haxorg_SubtreeLogHead* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead>(obj); }

bool haxorg_SubtreeCompletion___eq__(haxorg_SubtreeCompletion __this, haxorg_SubtreeCompletion other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::SubtreeCompletion const&) const, haxorg_SubtreeCompletion>(&operator==, org_context, other); }

void haxorg_destroy_SubtreeCompletion(haxorg_SubtreeCompletion* obj) { org::bind::c::execute_destroy<org::sem::SubtreeCompletion>(obj); }

bool haxorg_AttrList___eq__(haxorg_AttrList __this, haxorg_AttrList other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::AttrList const&) const, haxorg_AttrList>(&operator==, org_context, other); }

void haxorg_destroy_AttrList(haxorg_AttrList* obj) { org::bind::c::execute_destroy<org::sem::AttrList>(obj); }

haxorg_HstdVec haxorg_AttrGroup_getFlatArgs(haxorg_AttrGroup __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<org::sem::AttrValue>(*)() const>(&getFlatArgs, org_context); }

haxorg_HstdVec haxorg_AttrGroup_getAttrs(haxorg_AttrGroup __this, haxorg_HstdOpt key, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<org::sem::AttrValue>(*)(hstd::Opt<hstd::Str> const&) const, haxorg_HstdOpt>(&getAttrs, org_context, key); }

void haxorg_AttrGroup_setNamedAttr(haxorg_AttrGroup __this, haxorg_HstdStr key, haxorg_HstdVec attrs, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(hstd::Str const&, hstd::Vec<org::sem::AttrValue> const&), haxorg_HstdStr, haxorg_HstdVec>(&setNamedAttr, org_context, key, attrs); }

void haxorg_AttrGroup_setPositionalAttr(haxorg_AttrGroup __this, haxorg_HstdVec items, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(hstd::Vec<org::sem::AttrValue> const&), haxorg_HstdVec>(&setPositionalAttr, org_context, items); }

int haxorg_AttrGroup_getPositionalSize(haxorg_AttrGroup __this, OrgContext* org_context) { return org::bind::c::execute_cpp<int, int(*)() const>(&getPositionalSize, org_context); }

int haxorg_AttrGroup_getNamedSize(haxorg_AttrGroup __this, OrgContext* org_context) { return org::bind::c::execute_cpp<int, int(*)() const>(&getNamedSize, org_context); }

bool haxorg_AttrGroup_isEmpty(haxorg_AttrGroup __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isEmpty, org_context); }

haxorg_AttrList haxorg_AttrGroup_getAll(haxorg_AttrGroup __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_AttrList, org::sem::AttrList(*)() const>(&getAll, org_context); }

haxorg_AttrValue haxorg_AttrGroup_atPositional(haxorg_AttrGroup __this, int index, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_AttrValue, org::sem::AttrValue const&(*)(int) const, int>(&atPositional, org_context, index); }

haxorg_HstdOpt haxorg_AttrGroup_getPositional(haxorg_AttrGroup __this, int index, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<org::sem::AttrValue>(*)(int) const, int>(&getPositional, org_context, index); }

haxorg_AttrList haxorg_AttrGroup_atNamed(haxorg_AttrGroup __this, haxorg_HstdStr index, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_AttrList, org::sem::AttrList const&(*)(hstd::Str const&) const, haxorg_HstdStr>(&atNamed, org_context, index); }

haxorg_HstdOpt haxorg_AttrGroup_getNamed(haxorg_AttrGroup __this, haxorg_HstdStr index, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<org::sem::AttrList>(*)(hstd::Str const&) const, haxorg_HstdStr>(&getNamed, org_context, index); }

haxorg_AttrValue haxorg_AttrGroup_atFirstNamed(haxorg_AttrGroup __this, haxorg_HstdStr index, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_AttrValue, org::sem::AttrValue const&(*)(hstd::Str const&) const, haxorg_HstdStr>(&atFirstNamed, org_context, index); }

haxorg_HstdOpt haxorg_AttrGroup_getFirstNamed(haxorg_AttrGroup __this, haxorg_HstdStr index, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<org::sem::AttrValue>(*)(hstd::Str const&) const, haxorg_HstdStr>(&getFirstNamed, org_context, index); }

haxorg_AttrList haxorg_AttrGroup_atVarNamed(haxorg_AttrGroup __this, haxorg_HstdStr index, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_AttrList, org::sem::AttrList(*)(hstd::Str const&) const, haxorg_HstdStr>(&atVarNamed, org_context, index); }

haxorg_HstdOpt haxorg_AttrGroup_getVarNamed(haxorg_AttrGroup __this, haxorg_HstdStr index, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<org::sem::AttrList>(*)(hstd::Str const&) const, haxorg_HstdStr>(&getVarNamed, org_context, index); }

haxorg_AttrValue haxorg_AttrGroup_atFirstVarNamed(haxorg_AttrGroup __this, haxorg_HstdStr index, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_AttrValue, org::sem::AttrValue(*)(hstd::Str const&) const, haxorg_HstdStr>(&atFirstVarNamed, org_context, index); }

haxorg_HstdOpt haxorg_AttrGroup_getFirstVarNamed(haxorg_AttrGroup __this, haxorg_HstdStr index, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<org::sem::AttrValue>(*)(hstd::Str const&) const, haxorg_HstdStr>(&getFirstVarNamed, org_context, index); }

bool haxorg_AttrGroup___eq__(haxorg_AttrGroup __this, haxorg_AttrGroup other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::AttrGroup const&) const, haxorg_AttrGroup>(&operator==, org_context, other); }

void haxorg_destroy_AttrGroup(haxorg_AttrGroup* obj) { org::bind::c::execute_destroy<org::sem::AttrGroup>(obj); }

bool haxorg_OrgCodeEvalInput___eq__(haxorg_OrgCodeEvalInput __this, haxorg_OrgCodeEvalInput other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::OrgCodeEvalInput const&) const, haxorg_OrgCodeEvalInput>(&operator==, org_context, other); }

haxorg_HstdOpt haxorg_OrgCodeEvalInput_getVariable(haxorg_OrgCodeEvalInput __this, haxorg_HstdStr name, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<org::sem::OrgCodeEvalInput::Var>(*)(hstd::Str const&) const, haxorg_HstdStr>(&getVariable, org_context, name); }

bool haxorg_OrgCodeEvalInputVar___eq__(haxorg_OrgCodeEvalInputVar __this, haxorg_OrgCodeEvalInputVar other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::OrgCodeEvalInput::Var const&) const, haxorg_OrgCodeEvalInputVar>(&operator==, org_context, other); }

void haxorg_OrgCodeEvalInputVar_Var(haxorg_OrgCodeEvalInputVar __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&Var, org_context); }

void haxorg_destroy_OrgCodeEvalInputVar(haxorg_OrgCodeEvalInputVar* obj) { org::bind::c::execute_destroy<org::sem::OrgCodeEvalInput::Var>(obj); }

void haxorg_destroy_OrgCodeEvalInput(haxorg_OrgCodeEvalInput* obj) { org::bind::c::execute_destroy<org::sem::OrgCodeEvalInput>(obj); }

bool haxorg_OrgCodeEvalOutput___eq__(haxorg_OrgCodeEvalOutput __this, haxorg_OrgCodeEvalOutput other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::OrgCodeEvalOutput const&) const, haxorg_OrgCodeEvalOutput>(&operator==, org_context, other); }

void haxorg_destroy_OrgCodeEvalOutput(haxorg_OrgCodeEvalOutput* obj) { org::bind::c::execute_destroy<org::sem::OrgCodeEvalOutput>(obj); }

bool haxorg_ColumnView___eq__(haxorg_ColumnView __this, haxorg_ColumnView other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::ColumnView const&) const, haxorg_ColumnView>(&operator==, org_context, other); }

bool haxorg_ColumnViewSummary___eq__(haxorg_ColumnViewSummary __this, haxorg_ColumnViewSummary other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::ColumnView::Summary const&) const, haxorg_ColumnViewSummary>(&operator==, org_context, other); }

bool haxorg_ColumnViewSummary_isCheckboxAggregate(haxorg_ColumnViewSummary __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isCheckboxAggregate, org_context); }

haxorg_ColumnViewSummaryCheckboxAggregate haxorg_ColumnViewSummary_getCheckboxAggregateConst(haxorg_ColumnViewSummary __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ColumnViewSummaryCheckboxAggregate, org::sem::ColumnView::Summary::CheckboxAggregate const&(*)() const>(&getCheckboxAggregate, org_context); }

haxorg_ColumnViewSummaryCheckboxAggregate haxorg_ColumnViewSummary_getCheckboxAggregateMut(haxorg_ColumnViewSummary __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ColumnViewSummaryCheckboxAggregate, org::sem::ColumnView::Summary::CheckboxAggregate&(*)()>(&getCheckboxAggregate, org_context); }

bool haxorg_ColumnViewSummary_isMathAggregate(haxorg_ColumnViewSummary __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isMathAggregate, org_context); }

haxorg_ColumnViewSummaryMathAggregate haxorg_ColumnViewSummary_getMathAggregateConst(haxorg_ColumnViewSummary __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ColumnViewSummaryMathAggregate, org::sem::ColumnView::Summary::MathAggregate const&(*)() const>(&getMathAggregate, org_context); }

haxorg_ColumnViewSummaryMathAggregate haxorg_ColumnViewSummary_getMathAggregateMut(haxorg_ColumnViewSummary __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ColumnViewSummaryMathAggregate, org::sem::ColumnView::Summary::MathAggregate&(*)()>(&getMathAggregate, org_context); }

haxorg_ColumnViewSummaryKind haxorg_ColumnViewSummary_getKind(haxorg_ColumnViewSummary __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ColumnViewSummaryKind, org::sem::ColumnView::Summary::Kind(*)() const>(&getKind, org_context); }

bool haxorg_ColumnViewSummaryCheckboxAggregate___eq__(haxorg_ColumnViewSummaryCheckboxAggregate __this, haxorg_ColumnViewSummaryCheckboxAggregate other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::ColumnView::Summary::CheckboxAggregate const&) const, haxorg_ColumnViewSummaryCheckboxAggregate>(&operator==, org_context, other); }

void haxorg_destroy_ColumnViewSummaryCheckboxAggregate(haxorg_ColumnViewSummaryCheckboxAggregate* obj) { org::bind::c::execute_destroy<org::sem::ColumnView::Summary::CheckboxAggregate>(obj); }

bool haxorg_ColumnViewSummaryMathAggregate___eq__(haxorg_ColumnViewSummaryMathAggregate __this, haxorg_ColumnViewSummaryMathAggregate other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::ColumnView::Summary::MathAggregate const&) const, haxorg_ColumnViewSummaryMathAggregate>(&operator==, org_context, other); }

void haxorg_destroy_ColumnViewSummaryMathAggregate(haxorg_ColumnViewSummaryMathAggregate* obj) { org::bind::c::execute_destroy<org::sem::ColumnView::Summary::MathAggregate>(obj); }

void haxorg_destroy_ColumnViewSummary(haxorg_ColumnViewSummary* obj) { org::bind::c::execute_destroy<org::sem::ColumnView::Summary>(obj); }

bool haxorg_ColumnViewColumn___eq__(haxorg_ColumnViewColumn __this, haxorg_ColumnViewColumn other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::ColumnView::Column const&) const, haxorg_ColumnViewColumn>(&operator==, org_context, other); }

void haxorg_destroy_ColumnViewColumn(haxorg_ColumnViewColumn* obj) { org::bind::c::execute_destroy<org::sem::ColumnView::Column>(obj); }

void haxorg_destroy_ColumnView(haxorg_ColumnView* obj) { org::bind::c::execute_destroy<org::sem::ColumnView>(obj); }

bool haxorg_BlockCodeLine___eq__(haxorg_BlockCodeLine __this, haxorg_BlockCodeLine other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::BlockCodeLine const&) const, haxorg_BlockCodeLine>(&operator==, org_context, other); }

bool haxorg_BlockCodeLinePart___eq__(haxorg_BlockCodeLinePart __this, haxorg_BlockCodeLinePart other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::BlockCodeLine::Part const&) const, haxorg_BlockCodeLinePart>(&operator==, org_context, other); }

bool haxorg_BlockCodeLinePart_isRaw(haxorg_BlockCodeLinePart __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isRaw, org_context); }

haxorg_BlockCodeLinePartRaw haxorg_BlockCodeLinePart_getRawConst(haxorg_BlockCodeLinePart __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_BlockCodeLinePartRaw, org::sem::BlockCodeLine::Part::Raw const&(*)() const>(&getRaw, org_context); }

haxorg_BlockCodeLinePartRaw haxorg_BlockCodeLinePart_getRawMut(haxorg_BlockCodeLinePart __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_BlockCodeLinePartRaw, org::sem::BlockCodeLine::Part::Raw&(*)()>(&getRaw, org_context); }

bool haxorg_BlockCodeLinePart_isCallout(haxorg_BlockCodeLinePart __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isCallout, org_context); }

haxorg_BlockCodeLinePartCallout haxorg_BlockCodeLinePart_getCalloutConst(haxorg_BlockCodeLinePart __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_BlockCodeLinePartCallout, org::sem::BlockCodeLine::Part::Callout const&(*)() const>(&getCallout, org_context); }

haxorg_BlockCodeLinePartCallout haxorg_BlockCodeLinePart_getCalloutMut(haxorg_BlockCodeLinePart __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_BlockCodeLinePartCallout, org::sem::BlockCodeLine::Part::Callout&(*)()>(&getCallout, org_context); }

bool haxorg_BlockCodeLinePart_isTangle(haxorg_BlockCodeLinePart __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isTangle, org_context); }

haxorg_BlockCodeLinePartTangle haxorg_BlockCodeLinePart_getTangleConst(haxorg_BlockCodeLinePart __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_BlockCodeLinePartTangle, org::sem::BlockCodeLine::Part::Tangle const&(*)() const>(&getTangle, org_context); }

haxorg_BlockCodeLinePartTangle haxorg_BlockCodeLinePart_getTangleMut(haxorg_BlockCodeLinePart __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_BlockCodeLinePartTangle, org::sem::BlockCodeLine::Part::Tangle&(*)()>(&getTangle, org_context); }

haxorg_BlockCodeLinePartKind haxorg_BlockCodeLinePart_getKind(haxorg_BlockCodeLinePart __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_BlockCodeLinePartKind, org::sem::BlockCodeLine::Part::Kind(*)() const>(&getKind, org_context); }

bool haxorg_BlockCodeLinePartRaw___eq__(haxorg_BlockCodeLinePartRaw __this, haxorg_BlockCodeLinePartRaw other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::BlockCodeLine::Part::Raw const&) const, haxorg_BlockCodeLinePartRaw>(&operator==, org_context, other); }

void haxorg_destroy_BlockCodeLinePartRaw(haxorg_BlockCodeLinePartRaw* obj) { org::bind::c::execute_destroy<org::sem::BlockCodeLine::Part::Raw>(obj); }

bool haxorg_BlockCodeLinePartCallout___eq__(haxorg_BlockCodeLinePartCallout __this, haxorg_BlockCodeLinePartCallout other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::BlockCodeLine::Part::Callout const&) const, haxorg_BlockCodeLinePartCallout>(&operator==, org_context, other); }

void haxorg_destroy_BlockCodeLinePartCallout(haxorg_BlockCodeLinePartCallout* obj) { org::bind::c::execute_destroy<org::sem::BlockCodeLine::Part::Callout>(obj); }

bool haxorg_BlockCodeLinePartTangle___eq__(haxorg_BlockCodeLinePartTangle __this, haxorg_BlockCodeLinePartTangle other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::BlockCodeLine::Part::Tangle const&) const, haxorg_BlockCodeLinePartTangle>(&operator==, org_context, other); }

void haxorg_destroy_BlockCodeLinePartTangle(haxorg_BlockCodeLinePartTangle* obj) { org::bind::c::execute_destroy<org::sem::BlockCodeLine::Part::Tangle>(obj); }

void haxorg_destroy_BlockCodeLinePart(haxorg_BlockCodeLinePart* obj) { org::bind::c::execute_destroy<org::sem::BlockCodeLine::Part>(obj); }

void haxorg_destroy_BlockCodeLine(haxorg_BlockCodeLine* obj) { org::bind::c::execute_destroy<org::sem::BlockCodeLine>(obj); }

bool haxorg_DocumentExportConfig___eq__(haxorg_DocumentExportConfig __this, haxorg_DocumentExportConfig other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::DocumentExportConfig const&) const, haxorg_DocumentExportConfig>(&operator==, org_context, other); }

bool haxorg_DocumentExportConfig_isDoExport(haxorg_DocumentExportConfig __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isDoExport, org_context); }

haxorg_DocumentExportConfigDoExport haxorg_DocumentExportConfig_getDoExportConst(haxorg_DocumentExportConfig __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_DocumentExportConfigDoExport, org::sem::DocumentExportConfig::DoExport const&(*)() const>(&getDoExport, org_context); }

haxorg_DocumentExportConfigDoExport haxorg_DocumentExportConfig_getDoExportMut(haxorg_DocumentExportConfig __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_DocumentExportConfigDoExport, org::sem::DocumentExportConfig::DoExport&(*)()>(&getDoExport, org_context); }

bool haxorg_DocumentExportConfig_isExportFixed(haxorg_DocumentExportConfig __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isExportFixed, org_context); }

haxorg_DocumentExportConfigExportFixed haxorg_DocumentExportConfig_getExportFixedConst(haxorg_DocumentExportConfig __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_DocumentExportConfigExportFixed, org::sem::DocumentExportConfig::ExportFixed const&(*)() const>(&getExportFixed, org_context); }

haxorg_DocumentExportConfigExportFixed haxorg_DocumentExportConfig_getExportFixedMut(haxorg_DocumentExportConfig __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_DocumentExportConfigExportFixed, org::sem::DocumentExportConfig::ExportFixed&(*)()>(&getExportFixed, org_context); }

haxorg_DocumentExportConfigTocExportKind haxorg_DocumentExportConfig_getTocExportKind(haxorg_DocumentExportConfig __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_DocumentExportConfigTocExportKind, org::sem::DocumentExportConfig::TocExportKind(*)() const>(&getTocExportKind, org_context); }

bool haxorg_DocumentExportConfigTaskExport___eq__(haxorg_DocumentExportConfigTaskExport __this, haxorg_DocumentExportConfigTaskExport other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::DocumentExportConfig::TaskExport const&) const, haxorg_DocumentExportConfigTaskExport>(&operator==, org_context, other); }

void haxorg_destroy_DocumentExportConfigTaskExport(haxorg_DocumentExportConfigTaskExport* obj) { org::bind::c::execute_destroy<org::sem::DocumentExportConfig::TaskExport>(obj); }

bool haxorg_DocumentExportConfigDoExport___eq__(haxorg_DocumentExportConfigDoExport __this, haxorg_DocumentExportConfigDoExport other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::DocumentExportConfig::DoExport const&) const, haxorg_DocumentExportConfigDoExport>(&operator==, org_context, other); }

void haxorg_destroy_DocumentExportConfigDoExport(haxorg_DocumentExportConfigDoExport* obj) { org::bind::c::execute_destroy<org::sem::DocumentExportConfig::DoExport>(obj); }

bool haxorg_DocumentExportConfigExportFixed___eq__(haxorg_DocumentExportConfigExportFixed __this, haxorg_DocumentExportConfigExportFixed other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::DocumentExportConfig::ExportFixed const&) const, haxorg_DocumentExportConfigExportFixed>(&operator==, org_context, other); }

void haxorg_destroy_DocumentExportConfigExportFixed(haxorg_DocumentExportConfigExportFixed* obj) { org::bind::c::execute_destroy<org::sem::DocumentExportConfig::ExportFixed>(obj); }

void haxorg_destroy_DocumentExportConfig(haxorg_DocumentExportConfig* obj) { org::bind::c::execute_destroy<org::sem::DocumentExportConfig>(obj); }

bool haxorg_SubtreePeriod___eq__(haxorg_SubtreePeriod __this, haxorg_SubtreePeriod other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::SubtreePeriod const&) const, haxorg_SubtreePeriod>(&operator==, org_context, other); }

void haxorg_destroy_SubtreePeriod(haxorg_SubtreePeriod* obj) { org::bind::c::execute_destroy<org::sem::SubtreePeriod>(obj); }

bool haxorg_NamedProperty_isMatching(haxorg_NamedProperty __this, haxorg_HstdStr kind, haxorg_HstdOpt subKind, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const, haxorg_HstdStr, haxorg_HstdOpt>(&isMatching, org_context, kind, subKind); }

haxorg_HstdStr haxorg_NamedProperty_getName(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str(*)() const>(&getName, org_context); }

haxorg_HstdOpt haxorg_NamedProperty_getSubKind(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<hstd::Str>(*)() const>(&getSubKind, org_context); }

bool haxorg_NamedProperty___eq__(haxorg_NamedProperty __this, haxorg_NamedProperty other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::NamedProperty const&) const, haxorg_NamedProperty>(&operator==, org_context, other); }

bool haxorg_NamedProperty_isNonblocking(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isNonblocking, org_context); }

haxorg_NamedPropertyNonblocking haxorg_NamedProperty_getNonblockingConst(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyNonblocking, org::sem::NamedProperty::Nonblocking const&(*)() const>(&getNonblocking, org_context); }

haxorg_NamedPropertyNonblocking haxorg_NamedProperty_getNonblockingMut(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyNonblocking, org::sem::NamedProperty::Nonblocking&(*)()>(&getNonblocking, org_context); }

bool haxorg_NamedProperty_isArchiveTime(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isArchiveTime, org_context); }

haxorg_NamedPropertyArchiveTime haxorg_NamedProperty_getArchiveTimeConst(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveTime, org::sem::NamedProperty::ArchiveTime const&(*)() const>(&getArchiveTime, org_context); }

haxorg_NamedPropertyArchiveTime haxorg_NamedProperty_getArchiveTimeMut(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveTime, org::sem::NamedProperty::ArchiveTime&(*)()>(&getArchiveTime, org_context); }

bool haxorg_NamedProperty_isArchiveFile(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isArchiveFile, org_context); }

haxorg_NamedPropertyArchiveFile haxorg_NamedProperty_getArchiveFileConst(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveFile, org::sem::NamedProperty::ArchiveFile const&(*)() const>(&getArchiveFile, org_context); }

haxorg_NamedPropertyArchiveFile haxorg_NamedProperty_getArchiveFileMut(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveFile, org::sem::NamedProperty::ArchiveFile&(*)()>(&getArchiveFile, org_context); }

bool haxorg_NamedProperty_isArchiveOlpath(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isArchiveOlpath, org_context); }

haxorg_NamedPropertyArchiveOlpath haxorg_NamedProperty_getArchiveOlpathConst(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveOlpath, org::sem::NamedProperty::ArchiveOlpath const&(*)() const>(&getArchiveOlpath, org_context); }

haxorg_NamedPropertyArchiveOlpath haxorg_NamedProperty_getArchiveOlpathMut(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveOlpath, org::sem::NamedProperty::ArchiveOlpath&(*)()>(&getArchiveOlpath, org_context); }

bool haxorg_NamedProperty_isArchiveTarget(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isArchiveTarget, org_context); }

haxorg_NamedPropertyArchiveTarget haxorg_NamedProperty_getArchiveTargetConst(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveTarget, org::sem::NamedProperty::ArchiveTarget const&(*)() const>(&getArchiveTarget, org_context); }

haxorg_NamedPropertyArchiveTarget haxorg_NamedProperty_getArchiveTargetMut(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveTarget, org::sem::NamedProperty::ArchiveTarget&(*)()>(&getArchiveTarget, org_context); }

bool haxorg_NamedProperty_isArchiveCategory(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isArchiveCategory, org_context); }

haxorg_NamedPropertyArchiveCategory haxorg_NamedProperty_getArchiveCategoryConst(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveCategory, org::sem::NamedProperty::ArchiveCategory const&(*)() const>(&getArchiveCategory, org_context); }

haxorg_NamedPropertyArchiveCategory haxorg_NamedProperty_getArchiveCategoryMut(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveCategory, org::sem::NamedProperty::ArchiveCategory&(*)()>(&getArchiveCategory, org_context); }

bool haxorg_NamedProperty_isArchiveTodo(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isArchiveTodo, org_context); }

haxorg_NamedPropertyArchiveTodo haxorg_NamedProperty_getArchiveTodoConst(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveTodo, org::sem::NamedProperty::ArchiveTodo const&(*)() const>(&getArchiveTodo, org_context); }

haxorg_NamedPropertyArchiveTodo haxorg_NamedProperty_getArchiveTodoMut(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveTodo, org::sem::NamedProperty::ArchiveTodo&(*)()>(&getArchiveTodo, org_context); }

bool haxorg_NamedProperty_isTrigger(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isTrigger, org_context); }

haxorg_NamedPropertyTrigger haxorg_NamedProperty_getTriggerConst(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyTrigger, org::sem::NamedProperty::Trigger const&(*)() const>(&getTrigger, org_context); }

haxorg_NamedPropertyTrigger haxorg_NamedProperty_getTriggerMut(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyTrigger, org::sem::NamedProperty::Trigger&(*)()>(&getTrigger, org_context); }

bool haxorg_NamedProperty_isExportLatexClass(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isExportLatexClass, org_context); }

haxorg_NamedPropertyExportLatexClass haxorg_NamedProperty_getExportLatexClassConst(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexClass, org::sem::NamedProperty::ExportLatexClass const&(*)() const>(&getExportLatexClass, org_context); }

haxorg_NamedPropertyExportLatexClass haxorg_NamedProperty_getExportLatexClassMut(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexClass, org::sem::NamedProperty::ExportLatexClass&(*)()>(&getExportLatexClass, org_context); }

bool haxorg_NamedProperty_isCookieData(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isCookieData, org_context); }

haxorg_NamedPropertyCookieData haxorg_NamedProperty_getCookieDataConst(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyCookieData, org::sem::NamedProperty::CookieData const&(*)() const>(&getCookieData, org_context); }

haxorg_NamedPropertyCookieData haxorg_NamedProperty_getCookieDataMut(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyCookieData, org::sem::NamedProperty::CookieData&(*)()>(&getCookieData, org_context); }

bool haxorg_NamedProperty_isExportLatexClassOptions(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isExportLatexClassOptions, org_context); }

haxorg_NamedPropertyExportLatexClassOptions haxorg_NamedProperty_getExportLatexClassOptionsConst(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexClassOptions, org::sem::NamedProperty::ExportLatexClassOptions const&(*)() const>(&getExportLatexClassOptions, org_context); }

haxorg_NamedPropertyExportLatexClassOptions haxorg_NamedProperty_getExportLatexClassOptionsMut(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexClassOptions, org::sem::NamedProperty::ExportLatexClassOptions&(*)()>(&getExportLatexClassOptions, org_context); }

bool haxorg_NamedProperty_isExportLatexHeader(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isExportLatexHeader, org_context); }

haxorg_NamedPropertyExportLatexHeader haxorg_NamedProperty_getExportLatexHeaderConst(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexHeader, org::sem::NamedProperty::ExportLatexHeader const&(*)() const>(&getExportLatexHeader, org_context); }

haxorg_NamedPropertyExportLatexHeader haxorg_NamedProperty_getExportLatexHeaderMut(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexHeader, org::sem::NamedProperty::ExportLatexHeader&(*)()>(&getExportLatexHeader, org_context); }

bool haxorg_NamedProperty_isExportLatexCompiler(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isExportLatexCompiler, org_context); }

haxorg_NamedPropertyExportLatexCompiler haxorg_NamedProperty_getExportLatexCompilerConst(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexCompiler, org::sem::NamedProperty::ExportLatexCompiler const&(*)() const>(&getExportLatexCompiler, org_context); }

haxorg_NamedPropertyExportLatexCompiler haxorg_NamedProperty_getExportLatexCompilerMut(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexCompiler, org::sem::NamedProperty::ExportLatexCompiler&(*)()>(&getExportLatexCompiler, org_context); }

bool haxorg_NamedProperty_isOrdered(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isOrdered, org_context); }

haxorg_NamedPropertyOrdered haxorg_NamedProperty_getOrderedConst(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyOrdered, org::sem::NamedProperty::Ordered const&(*)() const>(&getOrdered, org_context); }

haxorg_NamedPropertyOrdered haxorg_NamedProperty_getOrderedMut(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyOrdered, org::sem::NamedProperty::Ordered&(*)()>(&getOrdered, org_context); }

bool haxorg_NamedProperty_isEffort(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isEffort, org_context); }

haxorg_NamedPropertyEffort haxorg_NamedProperty_getEffortConst(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyEffort, org::sem::NamedProperty::Effort const&(*)() const>(&getEffort, org_context); }

haxorg_NamedPropertyEffort haxorg_NamedProperty_getEffortMut(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyEffort, org::sem::NamedProperty::Effort&(*)()>(&getEffort, org_context); }

bool haxorg_NamedProperty_isVisibility(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isVisibility, org_context); }

haxorg_NamedPropertyVisibility haxorg_NamedProperty_getVisibilityConst(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyVisibility, org::sem::NamedProperty::Visibility const&(*)() const>(&getVisibility, org_context); }

haxorg_NamedPropertyVisibility haxorg_NamedProperty_getVisibilityMut(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyVisibility, org::sem::NamedProperty::Visibility&(*)()>(&getVisibility, org_context); }

bool haxorg_NamedProperty_isExportOptions(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isExportOptions, org_context); }

haxorg_NamedPropertyExportOptions haxorg_NamedProperty_getExportOptionsConst(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyExportOptions, org::sem::NamedProperty::ExportOptions const&(*)() const>(&getExportOptions, org_context); }

haxorg_NamedPropertyExportOptions haxorg_NamedProperty_getExportOptionsMut(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyExportOptions, org::sem::NamedProperty::ExportOptions&(*)()>(&getExportOptions, org_context); }

bool haxorg_NamedProperty_isBlocker(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isBlocker, org_context); }

haxorg_NamedPropertyBlocker haxorg_NamedProperty_getBlockerConst(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyBlocker, org::sem::NamedProperty::Blocker const&(*)() const>(&getBlocker, org_context); }

haxorg_NamedPropertyBlocker haxorg_NamedProperty_getBlockerMut(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyBlocker, org::sem::NamedProperty::Blocker&(*)()>(&getBlocker, org_context); }

bool haxorg_NamedProperty_isUnnumbered(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isUnnumbered, org_context); }

haxorg_NamedPropertyUnnumbered haxorg_NamedProperty_getUnnumberedConst(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyUnnumbered, org::sem::NamedProperty::Unnumbered const&(*)() const>(&getUnnumbered, org_context); }

haxorg_NamedPropertyUnnumbered haxorg_NamedProperty_getUnnumberedMut(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyUnnumbered, org::sem::NamedProperty::Unnumbered&(*)()>(&getUnnumbered, org_context); }

bool haxorg_NamedProperty_isCreated(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isCreated, org_context); }

haxorg_NamedPropertyCreated haxorg_NamedProperty_getCreatedConst(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyCreated, org::sem::NamedProperty::Created const&(*)() const>(&getCreated, org_context); }

haxorg_NamedPropertyCreated haxorg_NamedProperty_getCreatedMut(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyCreated, org::sem::NamedProperty::Created&(*)()>(&getCreated, org_context); }

bool haxorg_NamedProperty_isRadioId(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isRadioId, org_context); }

haxorg_NamedPropertyRadioId haxorg_NamedProperty_getRadioIdConst(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyRadioId, org::sem::NamedProperty::RadioId const&(*)() const>(&getRadioId, org_context); }

haxorg_NamedPropertyRadioId haxorg_NamedProperty_getRadioIdMut(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyRadioId, org::sem::NamedProperty::RadioId&(*)()>(&getRadioId, org_context); }

bool haxorg_NamedProperty_isHashtagDef(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isHashtagDef, org_context); }

haxorg_NamedPropertyHashtagDef haxorg_NamedProperty_getHashtagDefConst(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyHashtagDef, org::sem::NamedProperty::HashtagDef const&(*)() const>(&getHashtagDef, org_context); }

haxorg_NamedPropertyHashtagDef haxorg_NamedProperty_getHashtagDefMut(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyHashtagDef, org::sem::NamedProperty::HashtagDef&(*)()>(&getHashtagDef, org_context); }

bool haxorg_NamedProperty_isCustomArgs(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isCustomArgs, org_context); }

haxorg_NamedPropertyCustomArgs haxorg_NamedProperty_getCustomArgsConst(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomArgs, org::sem::NamedProperty::CustomArgs const&(*)() const>(&getCustomArgs, org_context); }

haxorg_NamedPropertyCustomArgs haxorg_NamedProperty_getCustomArgsMut(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomArgs, org::sem::NamedProperty::CustomArgs&(*)()>(&getCustomArgs, org_context); }

bool haxorg_NamedProperty_isCustomRaw(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isCustomRaw, org_context); }

haxorg_NamedPropertyCustomRaw haxorg_NamedProperty_getCustomRawConst(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomRaw, org::sem::NamedProperty::CustomRaw const&(*)() const>(&getCustomRaw, org_context); }

haxorg_NamedPropertyCustomRaw haxorg_NamedProperty_getCustomRawMut(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomRaw, org::sem::NamedProperty::CustomRaw&(*)()>(&getCustomRaw, org_context); }

bool haxorg_NamedProperty_isCustomId(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isCustomId, org_context); }

haxorg_NamedPropertyCustomId haxorg_NamedProperty_getCustomIdConst(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomId, org::sem::NamedProperty::CustomId const&(*)() const>(&getCustomId, org_context); }

haxorg_NamedPropertyCustomId haxorg_NamedProperty_getCustomIdMut(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomId, org::sem::NamedProperty::CustomId&(*)()>(&getCustomId, org_context); }

bool haxorg_NamedProperty_isCustomSubtreeJson(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isCustomSubtreeJson, org_context); }

haxorg_NamedPropertyCustomSubtreeJson haxorg_NamedProperty_getCustomSubtreeJsonConst(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomSubtreeJson, org::sem::NamedProperty::CustomSubtreeJson const&(*)() const>(&getCustomSubtreeJson, org_context); }

haxorg_NamedPropertyCustomSubtreeJson haxorg_NamedProperty_getCustomSubtreeJsonMut(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomSubtreeJson, org::sem::NamedProperty::CustomSubtreeJson&(*)()>(&getCustomSubtreeJson, org_context); }

bool haxorg_NamedProperty_isCustomSubtreeFlags(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isCustomSubtreeFlags, org_context); }

haxorg_NamedPropertyCustomSubtreeFlags haxorg_NamedProperty_getCustomSubtreeFlagsConst(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomSubtreeFlags, org::sem::NamedProperty::CustomSubtreeFlags const&(*)() const>(&getCustomSubtreeFlags, org_context); }

haxorg_NamedPropertyCustomSubtreeFlags haxorg_NamedProperty_getCustomSubtreeFlagsMut(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomSubtreeFlags, org::sem::NamedProperty::CustomSubtreeFlags&(*)()>(&getCustomSubtreeFlags, org_context); }

haxorg_NamedPropertyKind haxorg_NamedProperty_getKind(haxorg_NamedProperty __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_NamedPropertyKind, org::sem::NamedProperty::Kind(*)() const>(&getKind, org_context); }

bool haxorg_NamedPropertyNonblocking___eq__(haxorg_NamedPropertyNonblocking __this, haxorg_NamedPropertyNonblocking other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::NamedProperty::Nonblocking const&) const, haxorg_NamedPropertyNonblocking>(&operator==, org_context, other); }

void haxorg_destroy_NamedPropertyNonblocking(haxorg_NamedPropertyNonblocking* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Nonblocking>(obj); }

bool haxorg_NamedPropertyArchiveTime___eq__(haxorg_NamedPropertyArchiveTime __this, haxorg_NamedPropertyArchiveTime other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::NamedProperty::ArchiveTime const&) const, haxorg_NamedPropertyArchiveTime>(&operator==, org_context, other); }

void haxorg_destroy_NamedPropertyArchiveTime(haxorg_NamedPropertyArchiveTime* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ArchiveTime>(obj); }

bool haxorg_NamedPropertyArchiveFile___eq__(haxorg_NamedPropertyArchiveFile __this, haxorg_NamedPropertyArchiveFile other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::NamedProperty::ArchiveFile const&) const, haxorg_NamedPropertyArchiveFile>(&operator==, org_context, other); }

void haxorg_destroy_NamedPropertyArchiveFile(haxorg_NamedPropertyArchiveFile* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ArchiveFile>(obj); }

bool haxorg_NamedPropertyArchiveOlpath___eq__(haxorg_NamedPropertyArchiveOlpath __this, haxorg_NamedPropertyArchiveOlpath other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::NamedProperty::ArchiveOlpath const&) const, haxorg_NamedPropertyArchiveOlpath>(&operator==, org_context, other); }

void haxorg_destroy_NamedPropertyArchiveOlpath(haxorg_NamedPropertyArchiveOlpath* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ArchiveOlpath>(obj); }

bool haxorg_NamedPropertyArchiveTarget___eq__(haxorg_NamedPropertyArchiveTarget __this, haxorg_NamedPropertyArchiveTarget other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::NamedProperty::ArchiveTarget const&) const, haxorg_NamedPropertyArchiveTarget>(&operator==, org_context, other); }

void haxorg_destroy_NamedPropertyArchiveTarget(haxorg_NamedPropertyArchiveTarget* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ArchiveTarget>(obj); }

bool haxorg_NamedPropertyArchiveCategory___eq__(haxorg_NamedPropertyArchiveCategory __this, haxorg_NamedPropertyArchiveCategory other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::NamedProperty::ArchiveCategory const&) const, haxorg_NamedPropertyArchiveCategory>(&operator==, org_context, other); }

void haxorg_destroy_NamedPropertyArchiveCategory(haxorg_NamedPropertyArchiveCategory* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ArchiveCategory>(obj); }

bool haxorg_NamedPropertyArchiveTodo___eq__(haxorg_NamedPropertyArchiveTodo __this, haxorg_NamedPropertyArchiveTodo other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::NamedProperty::ArchiveTodo const&) const, haxorg_NamedPropertyArchiveTodo>(&operator==, org_context, other); }

void haxorg_destroy_NamedPropertyArchiveTodo(haxorg_NamedPropertyArchiveTodo* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ArchiveTodo>(obj); }

bool haxorg_NamedPropertyTrigger___eq__(haxorg_NamedPropertyTrigger __this, haxorg_NamedPropertyTrigger other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::NamedProperty::Trigger const&) const, haxorg_NamedPropertyTrigger>(&operator==, org_context, other); }

void haxorg_destroy_NamedPropertyTrigger(haxorg_NamedPropertyTrigger* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Trigger>(obj); }

bool haxorg_NamedPropertyExportLatexClass___eq__(haxorg_NamedPropertyExportLatexClass __this, haxorg_NamedPropertyExportLatexClass other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::NamedProperty::ExportLatexClass const&) const, haxorg_NamedPropertyExportLatexClass>(&operator==, org_context, other); }

void haxorg_destroy_NamedPropertyExportLatexClass(haxorg_NamedPropertyExportLatexClass* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ExportLatexClass>(obj); }

bool haxorg_NamedPropertyCookieData___eq__(haxorg_NamedPropertyCookieData __this, haxorg_NamedPropertyCookieData other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::NamedProperty::CookieData const&) const, haxorg_NamedPropertyCookieData>(&operator==, org_context, other); }

void haxorg_destroy_NamedPropertyCookieData(haxorg_NamedPropertyCookieData* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::CookieData>(obj); }

bool haxorg_NamedPropertyExportLatexClassOptions___eq__(haxorg_NamedPropertyExportLatexClassOptions __this, haxorg_NamedPropertyExportLatexClassOptions other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::NamedProperty::ExportLatexClassOptions const&) const, haxorg_NamedPropertyExportLatexClassOptions>(&operator==, org_context, other); }

void haxorg_destroy_NamedPropertyExportLatexClassOptions(haxorg_NamedPropertyExportLatexClassOptions* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ExportLatexClassOptions>(obj); }

bool haxorg_NamedPropertyExportLatexHeader___eq__(haxorg_NamedPropertyExportLatexHeader __this, haxorg_NamedPropertyExportLatexHeader other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::NamedProperty::ExportLatexHeader const&) const, haxorg_NamedPropertyExportLatexHeader>(&operator==, org_context, other); }

void haxorg_destroy_NamedPropertyExportLatexHeader(haxorg_NamedPropertyExportLatexHeader* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ExportLatexHeader>(obj); }

bool haxorg_NamedPropertyExportLatexCompiler___eq__(haxorg_NamedPropertyExportLatexCompiler __this, haxorg_NamedPropertyExportLatexCompiler other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::NamedProperty::ExportLatexCompiler const&) const, haxorg_NamedPropertyExportLatexCompiler>(&operator==, org_context, other); }

void haxorg_destroy_NamedPropertyExportLatexCompiler(haxorg_NamedPropertyExportLatexCompiler* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ExportLatexCompiler>(obj); }

bool haxorg_NamedPropertyOrdered___eq__(haxorg_NamedPropertyOrdered __this, haxorg_NamedPropertyOrdered other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::NamedProperty::Ordered const&) const, haxorg_NamedPropertyOrdered>(&operator==, org_context, other); }

void haxorg_destroy_NamedPropertyOrdered(haxorg_NamedPropertyOrdered* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Ordered>(obj); }

bool haxorg_NamedPropertyEffort___eq__(haxorg_NamedPropertyEffort __this, haxorg_NamedPropertyEffort other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::NamedProperty::Effort const&) const, haxorg_NamedPropertyEffort>(&operator==, org_context, other); }

void haxorg_destroy_NamedPropertyEffort(haxorg_NamedPropertyEffort* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Effort>(obj); }

bool haxorg_NamedPropertyVisibility___eq__(haxorg_NamedPropertyVisibility __this, haxorg_NamedPropertyVisibility other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::NamedProperty::Visibility const&) const, haxorg_NamedPropertyVisibility>(&operator==, org_context, other); }

void haxorg_destroy_NamedPropertyVisibility(haxorg_NamedPropertyVisibility* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Visibility>(obj); }

bool haxorg_NamedPropertyExportOptions___eq__(haxorg_NamedPropertyExportOptions __this, haxorg_NamedPropertyExportOptions other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::NamedProperty::ExportOptions const&) const, haxorg_NamedPropertyExportOptions>(&operator==, org_context, other); }

void haxorg_destroy_NamedPropertyExportOptions(haxorg_NamedPropertyExportOptions* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ExportOptions>(obj); }

bool haxorg_NamedPropertyBlocker___eq__(haxorg_NamedPropertyBlocker __this, haxorg_NamedPropertyBlocker other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::NamedProperty::Blocker const&) const, haxorg_NamedPropertyBlocker>(&operator==, org_context, other); }

void haxorg_destroy_NamedPropertyBlocker(haxorg_NamedPropertyBlocker* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Blocker>(obj); }

bool haxorg_NamedPropertyUnnumbered___eq__(haxorg_NamedPropertyUnnumbered __this, haxorg_NamedPropertyUnnumbered other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::NamedProperty::Unnumbered const&) const, haxorg_NamedPropertyUnnumbered>(&operator==, org_context, other); }

void haxorg_destroy_NamedPropertyUnnumbered(haxorg_NamedPropertyUnnumbered* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Unnumbered>(obj); }

bool haxorg_NamedPropertyCreated___eq__(haxorg_NamedPropertyCreated __this, haxorg_NamedPropertyCreated other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::NamedProperty::Created const&) const, haxorg_NamedPropertyCreated>(&operator==, org_context, other); }

void haxorg_destroy_NamedPropertyCreated(haxorg_NamedPropertyCreated* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Created>(obj); }

bool haxorg_NamedPropertyRadioId___eq__(haxorg_NamedPropertyRadioId __this, haxorg_NamedPropertyRadioId other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::NamedProperty::RadioId const&) const, haxorg_NamedPropertyRadioId>(&operator==, org_context, other); }

void haxorg_destroy_NamedPropertyRadioId(haxorg_NamedPropertyRadioId* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::RadioId>(obj); }

bool haxorg_NamedPropertyHashtagDef___eq__(haxorg_NamedPropertyHashtagDef __this, haxorg_NamedPropertyHashtagDef other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::NamedProperty::HashtagDef const&) const, haxorg_NamedPropertyHashtagDef>(&operator==, org_context, other); }

void haxorg_destroy_NamedPropertyHashtagDef(haxorg_NamedPropertyHashtagDef* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::HashtagDef>(obj); }

bool haxorg_NamedPropertyCustomArgs___eq__(haxorg_NamedPropertyCustomArgs __this, haxorg_NamedPropertyCustomArgs other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::NamedProperty::CustomArgs const&) const, haxorg_NamedPropertyCustomArgs>(&operator==, org_context, other); }

void haxorg_destroy_NamedPropertyCustomArgs(haxorg_NamedPropertyCustomArgs* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::CustomArgs>(obj); }

bool haxorg_NamedPropertyCustomRaw___eq__(haxorg_NamedPropertyCustomRaw __this, haxorg_NamedPropertyCustomRaw other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::NamedProperty::CustomRaw const&) const, haxorg_NamedPropertyCustomRaw>(&operator==, org_context, other); }

void haxorg_destroy_NamedPropertyCustomRaw(haxorg_NamedPropertyCustomRaw* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::CustomRaw>(obj); }

bool haxorg_NamedPropertyCustomId___eq__(haxorg_NamedPropertyCustomId __this, haxorg_NamedPropertyCustomId other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::NamedProperty::CustomId const&) const, haxorg_NamedPropertyCustomId>(&operator==, org_context, other); }

void haxorg_destroy_NamedPropertyCustomId(haxorg_NamedPropertyCustomId* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::CustomId>(obj); }

bool haxorg_NamedPropertyCustomSubtreeJson___eq__(haxorg_NamedPropertyCustomSubtreeJson __this, haxorg_NamedPropertyCustomSubtreeJson other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::NamedProperty::CustomSubtreeJson const&) const, haxorg_NamedPropertyCustomSubtreeJson>(&operator==, org_context, other); }

void haxorg_destroy_NamedPropertyCustomSubtreeJson(haxorg_NamedPropertyCustomSubtreeJson* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::CustomSubtreeJson>(obj); }

bool haxorg_NamedPropertyCustomSubtreeFlags___eq__(haxorg_NamedPropertyCustomSubtreeFlags __this, haxorg_NamedPropertyCustomSubtreeFlags other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::NamedProperty::CustomSubtreeFlags const&) const, haxorg_NamedPropertyCustomSubtreeFlags>(&operator==, org_context, other); }

void haxorg_destroy_NamedPropertyCustomSubtreeFlags(haxorg_NamedPropertyCustomSubtreeFlags* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::CustomSubtreeFlags>(obj); }

void haxorg_destroy_NamedProperty(haxorg_NamedProperty* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty>(obj); }

bool haxorg_OrgDiagnostics___eq__(haxorg_OrgDiagnostics __this, haxorg_OrgDiagnostics other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::OrgDiagnostics const&) const, haxorg_OrgDiagnostics>(&operator==, org_context, other); }

bool haxorg_OrgDiagnostics_isParseTokenError(haxorg_OrgDiagnostics __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isParseTokenError, org_context); }

haxorg_OrgDiagnosticsParseTokenError haxorg_OrgDiagnostics_getParseTokenErrorConst(haxorg_OrgDiagnostics __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsParseTokenError, org::sem::OrgDiagnostics::ParseTokenError const&(*)() const>(&getParseTokenError, org_context); }

haxorg_OrgDiagnosticsParseTokenError haxorg_OrgDiagnostics_getParseTokenErrorMut(haxorg_OrgDiagnostics __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsParseTokenError, org::sem::OrgDiagnostics::ParseTokenError&(*)()>(&getParseTokenError, org_context); }

bool haxorg_OrgDiagnostics_isParseError(haxorg_OrgDiagnostics __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isParseError, org_context); }

haxorg_OrgDiagnosticsParseError haxorg_OrgDiagnostics_getParseErrorConst(haxorg_OrgDiagnostics __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsParseError, org::sem::OrgDiagnostics::ParseError const&(*)() const>(&getParseError, org_context); }

haxorg_OrgDiagnosticsParseError haxorg_OrgDiagnostics_getParseErrorMut(haxorg_OrgDiagnostics __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsParseError, org::sem::OrgDiagnostics::ParseError&(*)()>(&getParseError, org_context); }

bool haxorg_OrgDiagnostics_isIncludeError(haxorg_OrgDiagnostics __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isIncludeError, org_context); }

haxorg_OrgDiagnosticsIncludeError haxorg_OrgDiagnostics_getIncludeErrorConst(haxorg_OrgDiagnostics __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsIncludeError, org::sem::OrgDiagnostics::IncludeError const&(*)() const>(&getIncludeError, org_context); }

haxorg_OrgDiagnosticsIncludeError haxorg_OrgDiagnostics_getIncludeErrorMut(haxorg_OrgDiagnostics __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsIncludeError, org::sem::OrgDiagnostics::IncludeError&(*)()>(&getIncludeError, org_context); }

bool haxorg_OrgDiagnostics_isConvertError(haxorg_OrgDiagnostics __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isConvertError, org_context); }

haxorg_OrgDiagnosticsConvertError haxorg_OrgDiagnostics_getConvertErrorConst(haxorg_OrgDiagnostics __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsConvertError, org::sem::OrgDiagnostics::ConvertError const&(*)() const>(&getConvertError, org_context); }

haxorg_OrgDiagnosticsConvertError haxorg_OrgDiagnostics_getConvertErrorMut(haxorg_OrgDiagnostics __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsConvertError, org::sem::OrgDiagnostics::ConvertError&(*)()>(&getConvertError, org_context); }

bool haxorg_OrgDiagnostics_isInternalError(haxorg_OrgDiagnostics __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isInternalError, org_context); }

haxorg_OrgDiagnosticsInternalError haxorg_OrgDiagnostics_getInternalErrorConst(haxorg_OrgDiagnostics __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsInternalError, org::sem::OrgDiagnostics::InternalError const&(*)() const>(&getInternalError, org_context); }

haxorg_OrgDiagnosticsInternalError haxorg_OrgDiagnostics_getInternalErrorMut(haxorg_OrgDiagnostics __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsInternalError, org::sem::OrgDiagnostics::InternalError&(*)()>(&getInternalError, org_context); }

haxorg_OrgDiagnosticsKind haxorg_OrgDiagnostics_getKind(haxorg_OrgDiagnostics __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsKind, org::sem::OrgDiagnostics::Kind(*)() const>(&getKind, org_context); }

bool haxorg_OrgDiagnosticsParseTokenError___eq__(haxorg_OrgDiagnosticsParseTokenError __this, haxorg_OrgDiagnosticsParseTokenError other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::OrgDiagnostics::ParseTokenError const&) const, haxorg_OrgDiagnosticsParseTokenError>(&operator==, org_context, other); }

void haxorg_destroy_OrgDiagnosticsParseTokenError(haxorg_OrgDiagnosticsParseTokenError* obj) { org::bind::c::execute_destroy<org::sem::OrgDiagnostics::ParseTokenError>(obj); }

bool haxorg_OrgDiagnosticsParseError___eq__(haxorg_OrgDiagnosticsParseError __this, haxorg_OrgDiagnosticsParseError other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::OrgDiagnostics::ParseError const&) const, haxorg_OrgDiagnosticsParseError>(&operator==, org_context, other); }

void haxorg_destroy_OrgDiagnosticsParseError(haxorg_OrgDiagnosticsParseError* obj) { org::bind::c::execute_destroy<org::sem::OrgDiagnostics::ParseError>(obj); }

bool haxorg_OrgDiagnosticsIncludeError___eq__(haxorg_OrgDiagnosticsIncludeError __this, haxorg_OrgDiagnosticsIncludeError other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::OrgDiagnostics::IncludeError const&) const, haxorg_OrgDiagnosticsIncludeError>(&operator==, org_context, other); }

void haxorg_destroy_OrgDiagnosticsIncludeError(haxorg_OrgDiagnosticsIncludeError* obj) { org::bind::c::execute_destroy<org::sem::OrgDiagnostics::IncludeError>(obj); }

bool haxorg_OrgDiagnosticsConvertError___eq__(haxorg_OrgDiagnosticsConvertError __this, haxorg_OrgDiagnosticsConvertError other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::OrgDiagnostics::ConvertError const&) const, haxorg_OrgDiagnosticsConvertError>(&operator==, org_context, other); }

void haxorg_destroy_OrgDiagnosticsConvertError(haxorg_OrgDiagnosticsConvertError* obj) { org::bind::c::execute_destroy<org::sem::OrgDiagnostics::ConvertError>(obj); }

bool haxorg_OrgDiagnosticsInternalError___eq__(haxorg_OrgDiagnosticsInternalError __this, haxorg_OrgDiagnosticsInternalError other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::sem::OrgDiagnostics::InternalError const&) const, haxorg_OrgDiagnosticsInternalError>(&operator==, org_context, other); }

void haxorg_destroy_OrgDiagnosticsInternalError(haxorg_OrgDiagnosticsInternalError* obj) { org::bind::c::execute_destroy<org::sem::OrgDiagnostics::InternalError>(obj); }

void haxorg_destroy_OrgDiagnostics(haxorg_OrgDiagnostics* obj) { org::bind::c::execute_destroy<org::sem::OrgDiagnostics>(obj); }

void haxorg_destroy_NoNode(haxorg_NoNode* obj) { org::bind::c::execute_destroy<org::sem::NoNode>(obj); }

void haxorg_destroy_ErrorItem(haxorg_ErrorItem* obj) { org::bind::c::execute_destroy<org::sem::ErrorItem>(obj); }

void haxorg_destroy_ErrorGroup(haxorg_ErrorGroup* obj) { org::bind::c::execute_destroy<org::sem::ErrorGroup>(obj); }

haxorg_HstdVec haxorg_Stmt_getAttached(haxorg_Stmt __this, haxorg_HstdOpt kind, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<org::sem::SemId<org::sem::Org>>(*)(hstd::Opt<hstd::Str> const&) const, haxorg_HstdOpt>(&getAttached, org_context, kind); }

haxorg_HstdVec haxorg_Stmt_getCaption(haxorg_Stmt __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<org::sem::SemId<org::sem::Org>>(*)() const>(&getCaption, org_context); }

haxorg_HstdVec haxorg_Stmt_getName(haxorg_Stmt __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<hstd::Str>(*)() const>(&getName, org_context); }

haxorg_HstdVec haxorg_Stmt_getAttrs(haxorg_Stmt __this, haxorg_HstdOpt kind, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<org::sem::AttrValue>(*)(hstd::Opt<hstd::Str> const&) const, haxorg_HstdOpt>(&getAttrs, org_context, kind); }

haxorg_HstdOpt haxorg_Stmt_getFirstAttr(haxorg_Stmt __this, haxorg_HstdStr kind, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<org::sem::AttrValue>(*)(hstd::Str const&) const, haxorg_HstdStr>(&getFirstAttr, org_context, kind); }

haxorg_HstdOpt haxorg_Stmt_getFirstAttrString(haxorg_Stmt __this, haxorg_HstdStr kind, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<hstd::Str>(*)(hstd::Str const&) const, haxorg_HstdStr>(&getFirstAttrString, org_context, kind); }

haxorg_HstdOpt haxorg_Stmt_getFirstAttrInt(haxorg_Stmt __this, haxorg_HstdStr kind, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<int>(*)(hstd::Str const&) const, haxorg_HstdStr>(&getFirstAttrInt, org_context, kind); }

haxorg_HstdOpt haxorg_Stmt_getFirstAttrBool(haxorg_Stmt __this, haxorg_HstdStr kind, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<bool>(*)(hstd::Str const&) const, haxorg_HstdStr>(&getFirstAttrBool, org_context, kind); }

haxorg_HstdOpt haxorg_Stmt_getFirstAttrDouble(haxorg_Stmt __this, haxorg_HstdStr kind, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<double>(*)(hstd::Str const&) const, haxorg_HstdStr>(&getFirstAttrDouble, org_context, kind); }

haxorg_HstdOpt haxorg_Stmt_getFirstAttrLisp(haxorg_Stmt __this, haxorg_HstdStr kind, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<org::sem::AttrValue::LispValue>(*)(hstd::Str const&) const, haxorg_HstdStr>(&getFirstAttrLisp, org_context, kind); }

haxorg_HstdOpt haxorg_Stmt_getFirstAttrKind(haxorg_Stmt __this, haxorg_HstdStr kind, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<org::sem::AttrValue::Kind>(*)(hstd::Str const&) const, haxorg_HstdStr>(&getFirstAttrKind, org_context, kind); }

void haxorg_destroy_Stmt(haxorg_Stmt* obj) { org::bind::c::execute_destroy<org::sem::Stmt>(obj); }

void haxorg_destroy_Inline(haxorg_Inline* obj) { org::bind::c::execute_destroy<org::sem::Inline>(obj); }

void haxorg_destroy_StmtList(haxorg_StmtList* obj) { org::bind::c::execute_destroy<org::sem::StmtList>(obj); }

void haxorg_destroy_Empty(haxorg_Empty* obj) { org::bind::c::execute_destroy<org::sem::Empty>(obj); }

haxorg_HstdStr haxorg_Leaf_getText(haxorg_Leaf __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str(*)() const>(&getText, org_context); }

void haxorg_destroy_Leaf(haxorg_Leaf* obj) { org::bind::c::execute_destroy<org::sem::Leaf>(obj); }

haxorg_HstdOpt haxorg_Time_getYear(haxorg_Time __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<int>(*)() const>(&getYear, org_context); }

haxorg_HstdOpt haxorg_Time_getMonth(haxorg_Time __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<int>(*)() const>(&getMonth, org_context); }

haxorg_HstdOpt haxorg_Time_getDay(haxorg_Time __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<int>(*)() const>(&getDay, org_context); }

haxorg_HstdOpt haxorg_Time_getHour(haxorg_Time __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<int>(*)() const>(&getHour, org_context); }

haxorg_HstdOpt haxorg_Time_getMinute(haxorg_Time __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<int>(*)() const>(&getMinute, org_context); }

haxorg_HstdOpt haxorg_Time_getSecond(haxorg_Time __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<int>(*)() const>(&getSecond, org_context); }

haxorg_UserTime haxorg_Time_getStaticTime(haxorg_Time __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_UserTime, hstd::UserTime(*)() const>(&getStaticTime, org_context); }

bool haxorg_Time_isStatic(haxorg_Time __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isStatic, org_context); }

haxorg_TimeStatic haxorg_Time_getStaticConst(haxorg_Time __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_TimeStatic, org::sem::Time::Static const&(*)() const>(&getStatic, org_context); }

haxorg_TimeStatic haxorg_Time_getStaticMut(haxorg_Time __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_TimeStatic, org::sem::Time::Static&(*)()>(&getStatic, org_context); }

bool haxorg_Time_isDynamic(haxorg_Time __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isDynamic, org_context); }

haxorg_TimeDynamic haxorg_Time_getDynamicConst(haxorg_Time __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_TimeDynamic, org::sem::Time::Dynamic const&(*)() const>(&getDynamic, org_context); }

haxorg_TimeDynamic haxorg_Time_getDynamicMut(haxorg_Time __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_TimeDynamic, org::sem::Time::Dynamic&(*)()>(&getDynamic, org_context); }

haxorg_TimeTimeKind haxorg_Time_getTimeKind(haxorg_Time __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_TimeTimeKind, org::sem::Time::TimeKind(*)() const>(&getTimeKind, org_context); }

void haxorg_TimeRepeat_Repeat(haxorg_TimeRepeat __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&Repeat, org_context); }

void haxorg_destroy_TimeRepeat(haxorg_TimeRepeat* obj) { org::bind::c::execute_destroy<org::sem::Time::Repeat>(obj); }

void haxorg_TimeStatic_Static(haxorg_TimeStatic __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&Static, org_context); }

void haxorg_destroy_TimeStatic(haxorg_TimeStatic* obj) { org::bind::c::execute_destroy<org::sem::Time::Static>(obj); }

void haxorg_TimeDynamic_Dynamic(haxorg_TimeDynamic __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&Dynamic, org_context); }

void haxorg_destroy_TimeDynamic(haxorg_TimeDynamic* obj) { org::bind::c::execute_destroy<org::sem::Time::Dynamic>(obj); }

void haxorg_destroy_Time(haxorg_Time* obj) { org::bind::c::execute_destroy<org::sem::Time>(obj); }

haxorg_HstdOpt haxorg_TimeRange_getClockedTimeSeconds(haxorg_TimeRange __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<int64_t>(*)() const>(&getClockedTimeSeconds, org_context); }

void haxorg_destroy_TimeRange(haxorg_TimeRange* obj) { org::bind::c::execute_destroy<org::sem::TimeRange>(obj); }

void haxorg_destroy_Macro(haxorg_Macro* obj) { org::bind::c::execute_destroy<org::sem::Macro>(obj); }

void haxorg_destroy_SymbolParam(haxorg_SymbolParam* obj) { org::bind::c::execute_destroy<org::sem::Symbol::Param>(obj); }

void haxorg_destroy_Symbol(haxorg_Symbol* obj) { org::bind::c::execute_destroy<org::sem::Symbol>(obj); }

void haxorg_destroy_ErrorSkipGroup(haxorg_ErrorSkipGroup* obj) { org::bind::c::execute_destroy<org::sem::ErrorSkipGroup>(obj); }

void haxorg_destroy_Markup(haxorg_Markup* obj) { org::bind::c::execute_destroy<org::sem::Markup>(obj); }

void haxorg_destroy_RadioTarget(haxorg_RadioTarget* obj) { org::bind::c::execute_destroy<org::sem::RadioTarget>(obj); }

void haxorg_destroy_Latex(haxorg_Latex* obj) { org::bind::c::execute_destroy<org::sem::Latex>(obj); }

void haxorg_SubtreeLog_setDescription(haxorg_SubtreeLog __this, haxorg_SemId desc, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::sem::SemId<org::sem::StmtList>), haxorg_SemId>(&setDescription, org_context, desc); }

void haxorg_destroy_SubtreeLog(haxorg_SubtreeLog* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLog>(obj); }

haxorg_HstdVec haxorg_Subtree_getTimePeriods(haxorg_Subtree __this, haxorg_HstdIntSet kinds, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<org::sem::SubtreePeriod>(*)(hstd::IntSet<org::sem::SubtreePeriod::Kind>) const, haxorg_HstdIntSet>(&getTimePeriods, org_context, kinds); }

haxorg_HstdVec haxorg_Subtree_getProperties(haxorg_Subtree __this, haxorg_HstdStr kind, haxorg_HstdOpt subkind, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<org::sem::NamedProperty>(*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const, haxorg_HstdStr, haxorg_HstdOpt>(&getProperties, org_context, kind, subkind); }

haxorg_HstdOpt haxorg_Subtree_getProperty(haxorg_Subtree __this, haxorg_HstdStr kind, haxorg_HstdOpt subkind, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<org::sem::NamedProperty>(*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const, haxorg_HstdStr, haxorg_HstdOpt>(&getProperty, org_context, kind, subkind); }

void haxorg_Subtree_removeProperty(haxorg_Subtree __this, haxorg_HstdStr kind, haxorg_HstdOpt subkind, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(hstd::Str const&, hstd::Opt<hstd::Str> const&), haxorg_HstdStr, haxorg_HstdOpt>(&removeProperty, org_context, kind, subkind); }

void haxorg_Subtree_setProperty(haxorg_Subtree __this, haxorg_NamedProperty value, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::sem::NamedProperty const&), haxorg_NamedProperty>(&setProperty, org_context, value); }

void haxorg_Subtree_setPropertyStrValue(haxorg_Subtree __this, haxorg_HstdStr value, haxorg_HstdStr kind, haxorg_HstdOpt subkind, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(hstd::Str const&, hstd::Str const&, hstd::Opt<hstd::Str> const&), haxorg_HstdStr, haxorg_HstdStr, haxorg_HstdOpt>(&setPropertyStrValue, org_context, value, kind, subkind); }

haxorg_HstdStr haxorg_Subtree_getCleanTitle(haxorg_Subtree __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str(*)() const>(&getCleanTitle, org_context); }

haxorg_HstdOpt haxorg_Subtree_getTodoKeyword(haxorg_Subtree __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<hstd::Str>(*)() const>(&getTodoKeyword, org_context); }

void haxorg_destroy_Subtree(haxorg_Subtree* obj) { org::bind::c::execute_destroy<org::sem::Subtree>(obj); }

void haxorg_destroy_ColonExample(haxorg_ColonExample* obj) { org::bind::c::execute_destroy<org::sem::ColonExample>(obj); }

void haxorg_destroy_Call(haxorg_Call* obj) { org::bind::c::execute_destroy<org::sem::Call>(obj); }

bool haxorg_ListItem_isDescriptionItem(haxorg_ListItem __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isDescriptionItem, org_context); }

haxorg_HstdOpt haxorg_ListItem_getCleanHeader(haxorg_ListItem __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<hstd::Str>(*)() const>(&getCleanHeader, org_context); }

void haxorg_destroy_ListItem(haxorg_ListItem* obj) { org::bind::c::execute_destroy<org::sem::ListItem>(obj); }

haxorg_HstdVec haxorg_DocumentOptions_getProperties(haxorg_DocumentOptions __this, haxorg_HstdStr kind, haxorg_HstdOpt subKind, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<org::sem::NamedProperty>(*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const, haxorg_HstdStr, haxorg_HstdOpt>(&getProperties, org_context, kind, subKind); }

haxorg_HstdOpt haxorg_DocumentOptions_getProperty(haxorg_DocumentOptions __this, haxorg_HstdStr kind, haxorg_HstdOpt subKind, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<org::sem::NamedProperty>(*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const, haxorg_HstdStr, haxorg_HstdOpt>(&getProperty, org_context, kind, subKind); }

void haxorg_destroy_DocumentOptions(haxorg_DocumentOptions* obj) { org::bind::c::execute_destroy<org::sem::DocumentOptions>(obj); }

void haxorg_destroy_DocumentFragment(haxorg_DocumentFragment* obj) { org::bind::c::execute_destroy<org::sem::DocumentFragment>(obj); }

void haxorg_destroy_CriticMarkup(haxorg_CriticMarkup* obj) { org::bind::c::execute_destroy<org::sem::CriticMarkup>(obj); }

haxorg_HstdVec haxorg_Document_getProperties(haxorg_Document __this, haxorg_HstdStr kind, haxorg_HstdOpt subKind, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<org::sem::NamedProperty>(*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const, haxorg_HstdStr, haxorg_HstdOpt>(&getProperties, org_context, kind, subKind); }

haxorg_HstdOpt haxorg_Document_getProperty(haxorg_Document __this, haxorg_HstdStr kind, haxorg_HstdOpt subKind, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<org::sem::NamedProperty>(*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const, haxorg_HstdStr, haxorg_HstdOpt>(&getProperty, org_context, kind, subKind); }

void haxorg_destroy_Document(haxorg_Document* obj) { org::bind::c::execute_destroy<org::sem::Document>(obj); }

void haxorg_destroy_FileTarget(haxorg_FileTarget* obj) { org::bind::c::execute_destroy<org::sem::FileTarget>(obj); }

void haxorg_destroy_TextSeparator(haxorg_TextSeparator* obj) { org::bind::c::execute_destroy<org::sem::TextSeparator>(obj); }

void haxorg_destroy_DocumentGroup(haxorg_DocumentGroup* obj) { org::bind::c::execute_destroy<org::sem::DocumentGroup>(obj); }

bool haxorg_File_isDocument(haxorg_File __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isDocument, org_context); }

haxorg_FileDocument haxorg_File_getDocumentConst(haxorg_File __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_FileDocument, org::sem::File::Document const&(*)() const>(&getDocument, org_context); }

haxorg_FileDocument haxorg_File_getDocumentMut(haxorg_File __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_FileDocument, org::sem::File::Document&(*)()>(&getDocument, org_context); }

bool haxorg_File_isAttachment(haxorg_File __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isAttachment, org_context); }

haxorg_FileAttachment haxorg_File_getAttachmentConst(haxorg_File __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_FileAttachment, org::sem::File::Attachment const&(*)() const>(&getAttachment, org_context); }

haxorg_FileAttachment haxorg_File_getAttachmentMut(haxorg_File __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_FileAttachment, org::sem::File::Attachment&(*)()>(&getAttachment, org_context); }

bool haxorg_File_isSource(haxorg_File __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isSource, org_context); }

haxorg_FileSource haxorg_File_getSourceConst(haxorg_File __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_FileSource, org::sem::File::Source const&(*)() const>(&getSource, org_context); }

haxorg_FileSource haxorg_File_getSourceMut(haxorg_File __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_FileSource, org::sem::File::Source&(*)()>(&getSource, org_context); }

haxorg_FileKind haxorg_File_getFileKind(haxorg_File __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_FileKind, org::sem::File::Kind(*)() const>(&getFileKind, org_context); }

void haxorg_destroy_FileDocument(haxorg_FileDocument* obj) { org::bind::c::execute_destroy<org::sem::File::Document>(obj); }

void haxorg_destroy_FileAttachment(haxorg_FileAttachment* obj) { org::bind::c::execute_destroy<org::sem::File::Attachment>(obj); }

void haxorg_destroy_FileSource(haxorg_FileSource* obj) { org::bind::c::execute_destroy<org::sem::File::Source>(obj); }

void haxorg_destroy_File(haxorg_File* obj) { org::bind::c::execute_destroy<org::sem::File>(obj); }

void haxorg_destroy_Directory(haxorg_Directory* obj) { org::bind::c::execute_destroy<org::sem::Directory>(obj); }

void haxorg_destroy_Symlink(haxorg_Symlink* obj) { org::bind::c::execute_destroy<org::sem::Symlink>(obj); }

bool haxorg_CmdInclude_isExample(haxorg_CmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isExample, org_context); }

haxorg_CmdIncludeExample haxorg_CmdInclude_getExampleConst(haxorg_CmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_CmdIncludeExample, org::sem::CmdInclude::Example const&(*)() const>(&getExample, org_context); }

haxorg_CmdIncludeExample haxorg_CmdInclude_getExampleMut(haxorg_CmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_CmdIncludeExample, org::sem::CmdInclude::Example&(*)()>(&getExample, org_context); }

bool haxorg_CmdInclude_isExport(haxorg_CmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isExport, org_context); }

haxorg_CmdIncludeExport haxorg_CmdInclude_getExportConst(haxorg_CmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_CmdIncludeExport, org::sem::CmdInclude::Export const&(*)() const>(&getExport, org_context); }

haxorg_CmdIncludeExport haxorg_CmdInclude_getExportMut(haxorg_CmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_CmdIncludeExport, org::sem::CmdInclude::Export&(*)()>(&getExport, org_context); }

bool haxorg_CmdInclude_isCustom(haxorg_CmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isCustom, org_context); }

haxorg_CmdIncludeCustom haxorg_CmdInclude_getCustomConst(haxorg_CmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_CmdIncludeCustom, org::sem::CmdInclude::Custom const&(*)() const>(&getCustom, org_context); }

haxorg_CmdIncludeCustom haxorg_CmdInclude_getCustomMut(haxorg_CmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_CmdIncludeCustom, org::sem::CmdInclude::Custom&(*)()>(&getCustom, org_context); }

bool haxorg_CmdInclude_isSrc(haxorg_CmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isSrc, org_context); }

haxorg_CmdIncludeSrc haxorg_CmdInclude_getSrcConst(haxorg_CmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_CmdIncludeSrc, org::sem::CmdInclude::Src const&(*)() const>(&getSrc, org_context); }

haxorg_CmdIncludeSrc haxorg_CmdInclude_getSrcMut(haxorg_CmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_CmdIncludeSrc, org::sem::CmdInclude::Src&(*)()>(&getSrc, org_context); }

bool haxorg_CmdInclude_isOrgDocument(haxorg_CmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isOrgDocument, org_context); }

haxorg_CmdIncludeOrgDocument haxorg_CmdInclude_getOrgDocumentConst(haxorg_CmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_CmdIncludeOrgDocument, org::sem::CmdInclude::OrgDocument const&(*)() const>(&getOrgDocument, org_context); }

haxorg_CmdIncludeOrgDocument haxorg_CmdInclude_getOrgDocumentMut(haxorg_CmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_CmdIncludeOrgDocument, org::sem::CmdInclude::OrgDocument&(*)()>(&getOrgDocument, org_context); }

haxorg_CmdIncludeKind haxorg_CmdInclude_getIncludeKind(haxorg_CmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_CmdIncludeKind, org::sem::CmdInclude::Kind(*)() const>(&getIncludeKind, org_context); }

void haxorg_CmdIncludeIncludeBase_IncludeBase(haxorg_CmdIncludeIncludeBase __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&IncludeBase, org_context); }

void haxorg_destroy_CmdIncludeIncludeBase(haxorg_CmdIncludeIncludeBase* obj) { org::bind::c::execute_destroy<org::sem::CmdInclude::IncludeBase>(obj); }

void haxorg_CmdIncludeExample_Example(haxorg_CmdIncludeExample __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&Example, org_context); }

void haxorg_destroy_CmdIncludeExample(haxorg_CmdIncludeExample* obj) { org::bind::c::execute_destroy<org::sem::CmdInclude::Example>(obj); }

void haxorg_CmdIncludeExport_Export(haxorg_CmdIncludeExport __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&Export, org_context); }

void haxorg_destroy_CmdIncludeExport(haxorg_CmdIncludeExport* obj) { org::bind::c::execute_destroy<org::sem::CmdInclude::Export>(obj); }

void haxorg_CmdIncludeCustom_Custom(haxorg_CmdIncludeCustom __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&Custom, org_context); }

void haxorg_destroy_CmdIncludeCustom(haxorg_CmdIncludeCustom* obj) { org::bind::c::execute_destroy<org::sem::CmdInclude::Custom>(obj); }

void haxorg_CmdIncludeSrc_Src(haxorg_CmdIncludeSrc __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&Src, org_context); }

void haxorg_destroy_CmdIncludeSrc(haxorg_CmdIncludeSrc* obj) { org::bind::c::execute_destroy<org::sem::CmdInclude::Src>(obj); }

void haxorg_CmdIncludeOrgDocument_OrgDocument(haxorg_CmdIncludeOrgDocument __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&OrgDocument, org_context); }

void haxorg_destroy_CmdIncludeOrgDocument(haxorg_CmdIncludeOrgDocument* obj) { org::bind::c::execute_destroy<org::sem::CmdInclude::OrgDocument>(obj); }

void haxorg_destroy_CmdInclude(haxorg_CmdInclude* obj) { org::bind::c::execute_destroy<org::sem::CmdInclude>(obj); }

bool haxorg_ImmNoNode___eq__(haxorg_ImmNoNode __this, haxorg_ImmNoNode other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmNoNode const&) const, haxorg_ImmNoNode>(&operator==, org_context, other); }

void haxorg_destroy_ImmNoNode(haxorg_ImmNoNode* obj) { org::bind::c::execute_destroy<org::imm::ImmNoNode>(obj); }

bool haxorg_ImmErrorItem___eq__(haxorg_ImmErrorItem __this, haxorg_ImmErrorItem other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmErrorItem const&) const, haxorg_ImmErrorItem>(&operator==, org_context, other); }

void haxorg_destroy_ImmErrorItem(haxorg_ImmErrorItem* obj) { org::bind::c::execute_destroy<org::imm::ImmErrorItem>(obj); }

bool haxorg_ImmErrorGroup___eq__(haxorg_ImmErrorGroup __this, haxorg_ImmErrorGroup other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmErrorGroup const&) const, haxorg_ImmErrorGroup>(&operator==, org_context, other); }

void haxorg_destroy_ImmErrorGroup(haxorg_ImmErrorGroup* obj) { org::bind::c::execute_destroy<org::imm::ImmErrorGroup>(obj); }

bool haxorg_ImmStmt___eq__(haxorg_ImmStmt __this, haxorg_ImmStmt other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmStmt const&) const, haxorg_ImmStmt>(&operator==, org_context, other); }

void haxorg_destroy_ImmStmt(haxorg_ImmStmt* obj) { org::bind::c::execute_destroy<org::imm::ImmStmt>(obj); }

bool haxorg_ImmInline___eq__(haxorg_ImmInline __this, haxorg_ImmInline other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmInline const&) const, haxorg_ImmInline>(&operator==, org_context, other); }

void haxorg_destroy_ImmInline(haxorg_ImmInline* obj) { org::bind::c::execute_destroy<org::imm::ImmInline>(obj); }

bool haxorg_ImmStmtList___eq__(haxorg_ImmStmtList __this, haxorg_ImmStmtList other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmStmtList const&) const, haxorg_ImmStmtList>(&operator==, org_context, other); }

void haxorg_destroy_ImmStmtList(haxorg_ImmStmtList* obj) { org::bind::c::execute_destroy<org::imm::ImmStmtList>(obj); }

bool haxorg_ImmEmpty___eq__(haxorg_ImmEmpty __this, haxorg_ImmEmpty other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmEmpty const&) const, haxorg_ImmEmpty>(&operator==, org_context, other); }

void haxorg_destroy_ImmEmpty(haxorg_ImmEmpty* obj) { org::bind::c::execute_destroy<org::imm::ImmEmpty>(obj); }

bool haxorg_ImmLeaf___eq__(haxorg_ImmLeaf __this, haxorg_ImmLeaf other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmLeaf const&) const, haxorg_ImmLeaf>(&operator==, org_context, other); }

void haxorg_destroy_ImmLeaf(haxorg_ImmLeaf* obj) { org::bind::c::execute_destroy<org::imm::ImmLeaf>(obj); }

bool haxorg_ImmTime___eq__(haxorg_ImmTime __this, haxorg_ImmTime other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmTime const&) const, haxorg_ImmTime>(&operator==, org_context, other); }

bool haxorg_ImmTime_isStatic(haxorg_ImmTime __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isStatic, org_context); }

haxorg_ImmTimeStatic haxorg_ImmTime_getStaticConst(haxorg_ImmTime __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmTimeStatic, org::imm::ImmTime::Static const&(*)() const>(&getStatic, org_context); }

haxorg_ImmTimeStatic haxorg_ImmTime_getStaticMut(haxorg_ImmTime __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmTimeStatic, org::imm::ImmTime::Static&(*)()>(&getStatic, org_context); }

bool haxorg_ImmTime_isDynamic(haxorg_ImmTime __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isDynamic, org_context); }

haxorg_ImmTimeDynamic haxorg_ImmTime_getDynamicConst(haxorg_ImmTime __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmTimeDynamic, org::imm::ImmTime::Dynamic const&(*)() const>(&getDynamic, org_context); }

haxorg_ImmTimeDynamic haxorg_ImmTime_getDynamicMut(haxorg_ImmTime __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmTimeDynamic, org::imm::ImmTime::Dynamic&(*)()>(&getDynamic, org_context); }

haxorg_ImmTimeTimeKind haxorg_ImmTime_getTimeKind(haxorg_ImmTime __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmTimeTimeKind, org::imm::ImmTime::TimeKind(*)() const>(&getTimeKind, org_context); }

void haxorg_ImmTimeRepeat_Repeat(haxorg_ImmTimeRepeat __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&Repeat, org_context); }

bool haxorg_ImmTimeRepeat___eq__(haxorg_ImmTimeRepeat __this, haxorg_ImmTimeRepeat other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmTime::Repeat const&) const, haxorg_ImmTimeRepeat>(&operator==, org_context, other); }

void haxorg_destroy_ImmTimeRepeat(haxorg_ImmTimeRepeat* obj) { org::bind::c::execute_destroy<org::imm::ImmTime::Repeat>(obj); }

void haxorg_ImmTimeStatic_Static(haxorg_ImmTimeStatic __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&Static, org_context); }

bool haxorg_ImmTimeStatic___eq__(haxorg_ImmTimeStatic __this, haxorg_ImmTimeStatic other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmTime::Static const&) const, haxorg_ImmTimeStatic>(&operator==, org_context, other); }

void haxorg_destroy_ImmTimeStatic(haxorg_ImmTimeStatic* obj) { org::bind::c::execute_destroy<org::imm::ImmTime::Static>(obj); }

void haxorg_ImmTimeDynamic_Dynamic(haxorg_ImmTimeDynamic __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&Dynamic, org_context); }

bool haxorg_ImmTimeDynamic___eq__(haxorg_ImmTimeDynamic __this, haxorg_ImmTimeDynamic other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmTime::Dynamic const&) const, haxorg_ImmTimeDynamic>(&operator==, org_context, other); }

void haxorg_destroy_ImmTimeDynamic(haxorg_ImmTimeDynamic* obj) { org::bind::c::execute_destroy<org::imm::ImmTime::Dynamic>(obj); }

void haxorg_destroy_ImmTime(haxorg_ImmTime* obj) { org::bind::c::execute_destroy<org::imm::ImmTime>(obj); }

bool haxorg_ImmTimeRange___eq__(haxorg_ImmTimeRange __this, haxorg_ImmTimeRange other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmTimeRange const&) const, haxorg_ImmTimeRange>(&operator==, org_context, other); }

void haxorg_destroy_ImmTimeRange(haxorg_ImmTimeRange* obj) { org::bind::c::execute_destroy<org::imm::ImmTimeRange>(obj); }

bool haxorg_ImmMacro___eq__(haxorg_ImmMacro __this, haxorg_ImmMacro other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmMacro const&) const, haxorg_ImmMacro>(&operator==, org_context, other); }

void haxorg_destroy_ImmMacro(haxorg_ImmMacro* obj) { org::bind::c::execute_destroy<org::imm::ImmMacro>(obj); }

bool haxorg_ImmSymbol___eq__(haxorg_ImmSymbol __this, haxorg_ImmSymbol other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmSymbol const&) const, haxorg_ImmSymbol>(&operator==, org_context, other); }

bool haxorg_ImmSymbolParam___eq__(haxorg_ImmSymbolParam __this, haxorg_ImmSymbolParam other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmSymbol::Param const&) const, haxorg_ImmSymbolParam>(&operator==, org_context, other); }

void haxorg_destroy_ImmSymbolParam(haxorg_ImmSymbolParam* obj) { org::bind::c::execute_destroy<org::imm::ImmSymbol::Param>(obj); }

void haxorg_destroy_ImmSymbol(haxorg_ImmSymbol* obj) { org::bind::c::execute_destroy<org::imm::ImmSymbol>(obj); }

bool haxorg_ImmErrorSkipGroup___eq__(haxorg_ImmErrorSkipGroup __this, haxorg_ImmErrorSkipGroup other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmErrorSkipGroup const&) const, haxorg_ImmErrorSkipGroup>(&operator==, org_context, other); }

void haxorg_destroy_ImmErrorSkipGroup(haxorg_ImmErrorSkipGroup* obj) { org::bind::c::execute_destroy<org::imm::ImmErrorSkipGroup>(obj); }

bool haxorg_ImmMarkup___eq__(haxorg_ImmMarkup __this, haxorg_ImmMarkup other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmMarkup const&) const, haxorg_ImmMarkup>(&operator==, org_context, other); }

void haxorg_destroy_ImmMarkup(haxorg_ImmMarkup* obj) { org::bind::c::execute_destroy<org::imm::ImmMarkup>(obj); }

bool haxorg_ImmRadioTarget___eq__(haxorg_ImmRadioTarget __this, haxorg_ImmRadioTarget other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmRadioTarget const&) const, haxorg_ImmRadioTarget>(&operator==, org_context, other); }

void haxorg_destroy_ImmRadioTarget(haxorg_ImmRadioTarget* obj) { org::bind::c::execute_destroy<org::imm::ImmRadioTarget>(obj); }

bool haxorg_ImmLatex___eq__(haxorg_ImmLatex __this, haxorg_ImmLatex other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmLatex const&) const, haxorg_ImmLatex>(&operator==, org_context, other); }

void haxorg_destroy_ImmLatex(haxorg_ImmLatex* obj) { org::bind::c::execute_destroy<org::imm::ImmLatex>(obj); }

bool haxorg_ImmSubtreeLog___eq__(haxorg_ImmSubtreeLog __this, haxorg_ImmSubtreeLog other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmSubtreeLog const&) const, haxorg_ImmSubtreeLog>(&operator==, org_context, other); }

void haxorg_destroy_ImmSubtreeLog(haxorg_ImmSubtreeLog* obj) { org::bind::c::execute_destroy<org::imm::ImmSubtreeLog>(obj); }

bool haxorg_ImmSubtree___eq__(haxorg_ImmSubtree __this, haxorg_ImmSubtree other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmSubtree const&) const, haxorg_ImmSubtree>(&operator==, org_context, other); }

void haxorg_destroy_ImmSubtree(haxorg_ImmSubtree* obj) { org::bind::c::execute_destroy<org::imm::ImmSubtree>(obj); }

bool haxorg_ImmColonExample___eq__(haxorg_ImmColonExample __this, haxorg_ImmColonExample other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmColonExample const&) const, haxorg_ImmColonExample>(&operator==, org_context, other); }

void haxorg_destroy_ImmColonExample(haxorg_ImmColonExample* obj) { org::bind::c::execute_destroy<org::imm::ImmColonExample>(obj); }

bool haxorg_ImmCall___eq__(haxorg_ImmCall __this, haxorg_ImmCall other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmCall const&) const, haxorg_ImmCall>(&operator==, org_context, other); }

void haxorg_destroy_ImmCall(haxorg_ImmCall* obj) { org::bind::c::execute_destroy<org::imm::ImmCall>(obj); }

bool haxorg_ImmListItem___eq__(haxorg_ImmListItem __this, haxorg_ImmListItem other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmListItem const&) const, haxorg_ImmListItem>(&operator==, org_context, other); }

void haxorg_destroy_ImmListItem(haxorg_ImmListItem* obj) { org::bind::c::execute_destroy<org::imm::ImmListItem>(obj); }

bool haxorg_ImmDocumentOptions___eq__(haxorg_ImmDocumentOptions __this, haxorg_ImmDocumentOptions other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmDocumentOptions const&) const, haxorg_ImmDocumentOptions>(&operator==, org_context, other); }

void haxorg_destroy_ImmDocumentOptions(haxorg_ImmDocumentOptions* obj) { org::bind::c::execute_destroy<org::imm::ImmDocumentOptions>(obj); }

bool haxorg_ImmDocumentFragment___eq__(haxorg_ImmDocumentFragment __this, haxorg_ImmDocumentFragment other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmDocumentFragment const&) const, haxorg_ImmDocumentFragment>(&operator==, org_context, other); }

void haxorg_destroy_ImmDocumentFragment(haxorg_ImmDocumentFragment* obj) { org::bind::c::execute_destroy<org::imm::ImmDocumentFragment>(obj); }

bool haxorg_ImmCriticMarkup___eq__(haxorg_ImmCriticMarkup __this, haxorg_ImmCriticMarkup other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmCriticMarkup const&) const, haxorg_ImmCriticMarkup>(&operator==, org_context, other); }

void haxorg_destroy_ImmCriticMarkup(haxorg_ImmCriticMarkup* obj) { org::bind::c::execute_destroy<org::imm::ImmCriticMarkup>(obj); }

bool haxorg_ImmDocument___eq__(haxorg_ImmDocument __this, haxorg_ImmDocument other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmDocument const&) const, haxorg_ImmDocument>(&operator==, org_context, other); }

void haxorg_destroy_ImmDocument(haxorg_ImmDocument* obj) { org::bind::c::execute_destroy<org::imm::ImmDocument>(obj); }

bool haxorg_ImmFileTarget___eq__(haxorg_ImmFileTarget __this, haxorg_ImmFileTarget other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmFileTarget const&) const, haxorg_ImmFileTarget>(&operator==, org_context, other); }

void haxorg_destroy_ImmFileTarget(haxorg_ImmFileTarget* obj) { org::bind::c::execute_destroy<org::imm::ImmFileTarget>(obj); }

bool haxorg_ImmTextSeparator___eq__(haxorg_ImmTextSeparator __this, haxorg_ImmTextSeparator other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmTextSeparator const&) const, haxorg_ImmTextSeparator>(&operator==, org_context, other); }

void haxorg_destroy_ImmTextSeparator(haxorg_ImmTextSeparator* obj) { org::bind::c::execute_destroy<org::imm::ImmTextSeparator>(obj); }

bool haxorg_ImmDocumentGroup___eq__(haxorg_ImmDocumentGroup __this, haxorg_ImmDocumentGroup other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmDocumentGroup const&) const, haxorg_ImmDocumentGroup>(&operator==, org_context, other); }

void haxorg_destroy_ImmDocumentGroup(haxorg_ImmDocumentGroup* obj) { org::bind::c::execute_destroy<org::imm::ImmDocumentGroup>(obj); }

bool haxorg_ImmFile___eq__(haxorg_ImmFile __this, haxorg_ImmFile other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmFile const&) const, haxorg_ImmFile>(&operator==, org_context, other); }

bool haxorg_ImmFile_isDocument(haxorg_ImmFile __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isDocument, org_context); }

haxorg_ImmFileDocument haxorg_ImmFile_getDocumentConst(haxorg_ImmFile __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmFileDocument, org::imm::ImmFile::Document const&(*)() const>(&getDocument, org_context); }

haxorg_ImmFileDocument haxorg_ImmFile_getDocumentMut(haxorg_ImmFile __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmFileDocument, org::imm::ImmFile::Document&(*)()>(&getDocument, org_context); }

bool haxorg_ImmFile_isAttachment(haxorg_ImmFile __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isAttachment, org_context); }

haxorg_ImmFileAttachment haxorg_ImmFile_getAttachmentConst(haxorg_ImmFile __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmFileAttachment, org::imm::ImmFile::Attachment const&(*)() const>(&getAttachment, org_context); }

haxorg_ImmFileAttachment haxorg_ImmFile_getAttachmentMut(haxorg_ImmFile __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmFileAttachment, org::imm::ImmFile::Attachment&(*)()>(&getAttachment, org_context); }

bool haxorg_ImmFile_isSource(haxorg_ImmFile __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isSource, org_context); }

haxorg_ImmFileSource haxorg_ImmFile_getSourceConst(haxorg_ImmFile __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmFileSource, org::imm::ImmFile::Source const&(*)() const>(&getSource, org_context); }

haxorg_ImmFileSource haxorg_ImmFile_getSourceMut(haxorg_ImmFile __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmFileSource, org::imm::ImmFile::Source&(*)()>(&getSource, org_context); }

haxorg_ImmFileKind haxorg_ImmFile_getFileKind(haxorg_ImmFile __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmFileKind, org::imm::ImmFile::Kind(*)() const>(&getFileKind, org_context); }

bool haxorg_ImmFileDocument___eq__(haxorg_ImmFileDocument __this, haxorg_ImmFileDocument other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmFile::Document const&) const, haxorg_ImmFileDocument>(&operator==, org_context, other); }

void haxorg_destroy_ImmFileDocument(haxorg_ImmFileDocument* obj) { org::bind::c::execute_destroy<org::imm::ImmFile::Document>(obj); }

bool haxorg_ImmFileAttachment___eq__(haxorg_ImmFileAttachment __this, haxorg_ImmFileAttachment other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmFile::Attachment const&) const, haxorg_ImmFileAttachment>(&operator==, org_context, other); }

void haxorg_destroy_ImmFileAttachment(haxorg_ImmFileAttachment* obj) { org::bind::c::execute_destroy<org::imm::ImmFile::Attachment>(obj); }

bool haxorg_ImmFileSource___eq__(haxorg_ImmFileSource __this, haxorg_ImmFileSource other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmFile::Source const&) const, haxorg_ImmFileSource>(&operator==, org_context, other); }

void haxorg_destroy_ImmFileSource(haxorg_ImmFileSource* obj) { org::bind::c::execute_destroy<org::imm::ImmFile::Source>(obj); }

void haxorg_destroy_ImmFile(haxorg_ImmFile* obj) { org::bind::c::execute_destroy<org::imm::ImmFile>(obj); }

bool haxorg_ImmDirectory___eq__(haxorg_ImmDirectory __this, haxorg_ImmDirectory other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmDirectory const&) const, haxorg_ImmDirectory>(&operator==, org_context, other); }

void haxorg_destroy_ImmDirectory(haxorg_ImmDirectory* obj) { org::bind::c::execute_destroy<org::imm::ImmDirectory>(obj); }

bool haxorg_ImmSymlink___eq__(haxorg_ImmSymlink __this, haxorg_ImmSymlink other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmSymlink const&) const, haxorg_ImmSymlink>(&operator==, org_context, other); }

void haxorg_destroy_ImmSymlink(haxorg_ImmSymlink* obj) { org::bind::c::execute_destroy<org::imm::ImmSymlink>(obj); }

bool haxorg_ImmCmdInclude___eq__(haxorg_ImmCmdInclude __this, haxorg_ImmCmdInclude other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmCmdInclude const&) const, haxorg_ImmCmdInclude>(&operator==, org_context, other); }

bool haxorg_ImmCmdInclude_isExample(haxorg_ImmCmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isExample, org_context); }

haxorg_ImmCmdIncludeExample haxorg_ImmCmdInclude_getExampleConst(haxorg_ImmCmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeExample, org::imm::ImmCmdInclude::Example const&(*)() const>(&getExample, org_context); }

haxorg_ImmCmdIncludeExample haxorg_ImmCmdInclude_getExampleMut(haxorg_ImmCmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeExample, org::imm::ImmCmdInclude::Example&(*)()>(&getExample, org_context); }

bool haxorg_ImmCmdInclude_isExport(haxorg_ImmCmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isExport, org_context); }

haxorg_ImmCmdIncludeExport haxorg_ImmCmdInclude_getExportConst(haxorg_ImmCmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeExport, org::imm::ImmCmdInclude::Export const&(*)() const>(&getExport, org_context); }

haxorg_ImmCmdIncludeExport haxorg_ImmCmdInclude_getExportMut(haxorg_ImmCmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeExport, org::imm::ImmCmdInclude::Export&(*)()>(&getExport, org_context); }

bool haxorg_ImmCmdInclude_isCustom(haxorg_ImmCmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isCustom, org_context); }

haxorg_ImmCmdIncludeCustom haxorg_ImmCmdInclude_getCustomConst(haxorg_ImmCmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeCustom, org::imm::ImmCmdInclude::Custom const&(*)() const>(&getCustom, org_context); }

haxorg_ImmCmdIncludeCustom haxorg_ImmCmdInclude_getCustomMut(haxorg_ImmCmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeCustom, org::imm::ImmCmdInclude::Custom&(*)()>(&getCustom, org_context); }

bool haxorg_ImmCmdInclude_isSrc(haxorg_ImmCmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isSrc, org_context); }

haxorg_ImmCmdIncludeSrc haxorg_ImmCmdInclude_getSrcConst(haxorg_ImmCmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeSrc, org::imm::ImmCmdInclude::Src const&(*)() const>(&getSrc, org_context); }

haxorg_ImmCmdIncludeSrc haxorg_ImmCmdInclude_getSrcMut(haxorg_ImmCmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeSrc, org::imm::ImmCmdInclude::Src&(*)()>(&getSrc, org_context); }

bool haxorg_ImmCmdInclude_isOrgDocument(haxorg_ImmCmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isOrgDocument, org_context); }

haxorg_ImmCmdIncludeOrgDocument haxorg_ImmCmdInclude_getOrgDocumentConst(haxorg_ImmCmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeOrgDocument, org::imm::ImmCmdInclude::OrgDocument const&(*)() const>(&getOrgDocument, org_context); }

haxorg_ImmCmdIncludeOrgDocument haxorg_ImmCmdInclude_getOrgDocumentMut(haxorg_ImmCmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeOrgDocument, org::imm::ImmCmdInclude::OrgDocument&(*)()>(&getOrgDocument, org_context); }

haxorg_ImmCmdIncludeKind haxorg_ImmCmdInclude_getIncludeKind(haxorg_ImmCmdInclude __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeKind, org::imm::ImmCmdInclude::Kind(*)() const>(&getIncludeKind, org_context); }

void haxorg_ImmCmdIncludeIncludeBase_IncludeBase(haxorg_ImmCmdIncludeIncludeBase __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&IncludeBase, org_context); }

bool haxorg_ImmCmdIncludeIncludeBase___eq__(haxorg_ImmCmdIncludeIncludeBase __this, haxorg_ImmCmdIncludeIncludeBase other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmCmdInclude::IncludeBase const&) const, haxorg_ImmCmdIncludeIncludeBase>(&operator==, org_context, other); }

void haxorg_destroy_ImmCmdIncludeIncludeBase(haxorg_ImmCmdIncludeIncludeBase* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdInclude::IncludeBase>(obj); }

void haxorg_ImmCmdIncludeExample_Example(haxorg_ImmCmdIncludeExample __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&Example, org_context); }

bool haxorg_ImmCmdIncludeExample___eq__(haxorg_ImmCmdIncludeExample __this, haxorg_ImmCmdIncludeExample other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmCmdInclude::Example const&) const, haxorg_ImmCmdIncludeExample>(&operator==, org_context, other); }

void haxorg_destroy_ImmCmdIncludeExample(haxorg_ImmCmdIncludeExample* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdInclude::Example>(obj); }

void haxorg_ImmCmdIncludeExport_Export(haxorg_ImmCmdIncludeExport __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&Export, org_context); }

bool haxorg_ImmCmdIncludeExport___eq__(haxorg_ImmCmdIncludeExport __this, haxorg_ImmCmdIncludeExport other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmCmdInclude::Export const&) const, haxorg_ImmCmdIncludeExport>(&operator==, org_context, other); }

void haxorg_destroy_ImmCmdIncludeExport(haxorg_ImmCmdIncludeExport* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdInclude::Export>(obj); }

void haxorg_ImmCmdIncludeCustom_Custom(haxorg_ImmCmdIncludeCustom __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&Custom, org_context); }

bool haxorg_ImmCmdIncludeCustom___eq__(haxorg_ImmCmdIncludeCustom __this, haxorg_ImmCmdIncludeCustom other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmCmdInclude::Custom const&) const, haxorg_ImmCmdIncludeCustom>(&operator==, org_context, other); }

void haxorg_destroy_ImmCmdIncludeCustom(haxorg_ImmCmdIncludeCustom* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdInclude::Custom>(obj); }

void haxorg_ImmCmdIncludeSrc_Src(haxorg_ImmCmdIncludeSrc __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&Src, org_context); }

bool haxorg_ImmCmdIncludeSrc___eq__(haxorg_ImmCmdIncludeSrc __this, haxorg_ImmCmdIncludeSrc other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmCmdInclude::Src const&) const, haxorg_ImmCmdIncludeSrc>(&operator==, org_context, other); }

void haxorg_destroy_ImmCmdIncludeSrc(haxorg_ImmCmdIncludeSrc* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdInclude::Src>(obj); }

void haxorg_ImmCmdIncludeOrgDocument_OrgDocument(haxorg_ImmCmdIncludeOrgDocument __this, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)()>(&OrgDocument, org_context); }

bool haxorg_ImmCmdIncludeOrgDocument___eq__(haxorg_ImmCmdIncludeOrgDocument __this, haxorg_ImmCmdIncludeOrgDocument other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmCmdInclude::OrgDocument const&) const, haxorg_ImmCmdIncludeOrgDocument>(&operator==, org_context, other); }

void haxorg_destroy_ImmCmdIncludeOrgDocument(haxorg_ImmCmdIncludeOrgDocument* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdInclude::OrgDocument>(obj); }

void haxorg_destroy_ImmCmdInclude(haxorg_ImmCmdInclude* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdInclude>(obj); }

void haxorg_destroy_ImmAdapterOrgAPI(haxorg_ImmAdapterOrgAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterOrgAPI>(obj); }

haxorg_HstdVec haxorg_Cmd_getAttrs(haxorg_Cmd __this, haxorg_HstdOpt key, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<org::sem::AttrValue>(*)(hstd::Opt<hstd::Str> const&) const, haxorg_HstdOpt>(&getAttrs, org_context, key); }

haxorg_HstdOpt haxorg_Cmd_getFirstAttr(haxorg_Cmd __this, haxorg_HstdStr kind, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<org::sem::AttrValue>(*)(hstd::Str const&) const, haxorg_HstdStr>(&getFirstAttr, org_context, kind); }

void haxorg_destroy_Cmd(haxorg_Cmd* obj) { org::bind::c::execute_destroy<org::sem::Cmd>(obj); }

void haxorg_destroy_CmdCustomRaw(haxorg_CmdCustomRaw* obj) { org::bind::c::execute_destroy<org::sem::CmdCustomRaw>(obj); }

void haxorg_destroy_CmdCustomText(haxorg_CmdCustomText* obj) { org::bind::c::execute_destroy<org::sem::CmdCustomText>(obj); }

void haxorg_destroy_Link(haxorg_Link* obj) { org::bind::c::execute_destroy<org::sem::Link>(obj); }

void haxorg_destroy_BlockComment(haxorg_BlockComment* obj) { org::bind::c::execute_destroy<org::sem::BlockComment>(obj); }

bool haxorg_Paragraph_isFootnoteDefinition(haxorg_Paragraph __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isFootnoteDefinition, org_context); }

haxorg_HstdOpt haxorg_Paragraph_getFootnoteName(haxorg_Paragraph __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<hstd::Str>(*)() const>(&getFootnoteName, org_context); }

bool haxorg_Paragraph_hasAdmonition(haxorg_Paragraph __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&hasAdmonition, org_context); }

haxorg_HstdVec haxorg_Paragraph_getAdmonitions(haxorg_Paragraph __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<hstd::Str>(*)() const>(&getAdmonitions, org_context); }

haxorg_HstdVec haxorg_Paragraph_getAdmonitionNodes(haxorg_Paragraph __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<org::sem::SemId<org::sem::BigIdent>>(*)() const>(&getAdmonitionNodes, org_context); }

bool haxorg_Paragraph_hasTimestamp(haxorg_Paragraph __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&hasTimestamp, org_context); }

haxorg_HstdVec haxorg_Paragraph_getTimestamps(haxorg_Paragraph __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<hstd::UserTime>(*)() const>(&getTimestamps, org_context); }

haxorg_HstdVec haxorg_Paragraph_getTimestampNodes(haxorg_Paragraph __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<org::sem::SemId<org::sem::Time>>(*)() const>(&getTimestampNodes, org_context); }

bool haxorg_Paragraph_hasLeadHashtags(haxorg_Paragraph __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&hasLeadHashtags, org_context); }

haxorg_HstdVec haxorg_Paragraph_getLeadHashtags(haxorg_Paragraph __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<org::sem::SemId<org::sem::HashTag>>(*)() const>(&getLeadHashtags, org_context); }

haxorg_HstdVec haxorg_Paragraph_getBody(haxorg_Paragraph __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<org::sem::SemId<org::sem::Org>>(*)() const>(&getBody, org_context); }

void haxorg_destroy_Paragraph(haxorg_Paragraph* obj) { org::bind::c::execute_destroy<org::sem::Paragraph>(obj); }

haxorg_HstdVec haxorg_List_getListAttrs(haxorg_List __this, haxorg_HstdStr key, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<org::sem::AttrValue>(*)(hstd::Str const&) const, haxorg_HstdStr>(&getListAttrs, org_context, key); }

haxorg_ListFormattingMode haxorg_List_getListFormattingMode(haxorg_List __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ListFormattingMode, ListFormattingMode(*)() const>(&getListFormattingMode, org_context); }

bool haxorg_List_isDescriptionList(haxorg_List __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isDescriptionList, org_context); }

bool haxorg_List_isNumberedList(haxorg_List __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&isNumberedList, org_context); }

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

bool haxorg_ImmCmd___eq__(haxorg_ImmCmd __this, haxorg_ImmCmd other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmCmd const&) const, haxorg_ImmCmd>(&operator==, org_context, other); }

void haxorg_destroy_ImmCmd(haxorg_ImmCmd* obj) { org::bind::c::execute_destroy<org::imm::ImmCmd>(obj); }

bool haxorg_ImmCmdCustomRaw___eq__(haxorg_ImmCmdCustomRaw __this, haxorg_ImmCmdCustomRaw other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmCmdCustomRaw const&) const, haxorg_ImmCmdCustomRaw>(&operator==, org_context, other); }

void haxorg_destroy_ImmCmdCustomRaw(haxorg_ImmCmdCustomRaw* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdCustomRaw>(obj); }

bool haxorg_ImmCmdCustomText___eq__(haxorg_ImmCmdCustomText __this, haxorg_ImmCmdCustomText other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmCmdCustomText const&) const, haxorg_ImmCmdCustomText>(&operator==, org_context, other); }

void haxorg_destroy_ImmCmdCustomText(haxorg_ImmCmdCustomText* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdCustomText>(obj); }

bool haxorg_ImmLink___eq__(haxorg_ImmLink __this, haxorg_ImmLink other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmLink const&) const, haxorg_ImmLink>(&operator==, org_context, other); }

void haxorg_destroy_ImmLink(haxorg_ImmLink* obj) { org::bind::c::execute_destroy<org::imm::ImmLink>(obj); }

bool haxorg_ImmBlockComment___eq__(haxorg_ImmBlockComment __this, haxorg_ImmBlockComment other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmBlockComment const&) const, haxorg_ImmBlockComment>(&operator==, org_context, other); }

void haxorg_destroy_ImmBlockComment(haxorg_ImmBlockComment* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockComment>(obj); }

bool haxorg_ImmParagraph___eq__(haxorg_ImmParagraph __this, haxorg_ImmParagraph other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmParagraph const&) const, haxorg_ImmParagraph>(&operator==, org_context, other); }

void haxorg_destroy_ImmParagraph(haxorg_ImmParagraph* obj) { org::bind::c::execute_destroy<org::imm::ImmParagraph>(obj); }

bool haxorg_ImmList___eq__(haxorg_ImmList __this, haxorg_ImmList other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmList const&) const, haxorg_ImmList>(&operator==, org_context, other); }

void haxorg_destroy_ImmList(haxorg_ImmList* obj) { org::bind::c::execute_destroy<org::imm::ImmList>(obj); }

bool haxorg_ImmHashTag___eq__(haxorg_ImmHashTag __this, haxorg_ImmHashTag other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmHashTag const&) const, haxorg_ImmHashTag>(&operator==, org_context, other); }

void haxorg_destroy_ImmHashTag(haxorg_ImmHashTag* obj) { org::bind::c::execute_destroy<org::imm::ImmHashTag>(obj); }

bool haxorg_ImmInlineFootnote___eq__(haxorg_ImmInlineFootnote __this, haxorg_ImmInlineFootnote other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmInlineFootnote const&) const, haxorg_ImmInlineFootnote>(&operator==, org_context, other); }

void haxorg_destroy_ImmInlineFootnote(haxorg_ImmInlineFootnote* obj) { org::bind::c::execute_destroy<org::imm::ImmInlineFootnote>(obj); }

bool haxorg_ImmInlineExport___eq__(haxorg_ImmInlineExport __this, haxorg_ImmInlineExport other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmInlineExport const&) const, haxorg_ImmInlineExport>(&operator==, org_context, other); }

void haxorg_destroy_ImmInlineExport(haxorg_ImmInlineExport* obj) { org::bind::c::execute_destroy<org::imm::ImmInlineExport>(obj); }

bool haxorg_ImmEscaped___eq__(haxorg_ImmEscaped __this, haxorg_ImmEscaped other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmEscaped const&) const, haxorg_ImmEscaped>(&operator==, org_context, other); }

void haxorg_destroy_ImmEscaped(haxorg_ImmEscaped* obj) { org::bind::c::execute_destroy<org::imm::ImmEscaped>(obj); }

bool haxorg_ImmNewline___eq__(haxorg_ImmNewline __this, haxorg_ImmNewline other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmNewline const&) const, haxorg_ImmNewline>(&operator==, org_context, other); }

void haxorg_destroy_ImmNewline(haxorg_ImmNewline* obj) { org::bind::c::execute_destroy<org::imm::ImmNewline>(obj); }

bool haxorg_ImmSpace___eq__(haxorg_ImmSpace __this, haxorg_ImmSpace other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmSpace const&) const, haxorg_ImmSpace>(&operator==, org_context, other); }

void haxorg_destroy_ImmSpace(haxorg_ImmSpace* obj) { org::bind::c::execute_destroy<org::imm::ImmSpace>(obj); }

bool haxorg_ImmWord___eq__(haxorg_ImmWord __this, haxorg_ImmWord other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmWord const&) const, haxorg_ImmWord>(&operator==, org_context, other); }

void haxorg_destroy_ImmWord(haxorg_ImmWord* obj) { org::bind::c::execute_destroy<org::imm::ImmWord>(obj); }

bool haxorg_ImmAtMention___eq__(haxorg_ImmAtMention __this, haxorg_ImmAtMention other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmAtMention const&) const, haxorg_ImmAtMention>(&operator==, org_context, other); }

void haxorg_destroy_ImmAtMention(haxorg_ImmAtMention* obj) { org::bind::c::execute_destroy<org::imm::ImmAtMention>(obj); }

bool haxorg_ImmRawText___eq__(haxorg_ImmRawText __this, haxorg_ImmRawText other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmRawText const&) const, haxorg_ImmRawText>(&operator==, org_context, other); }

void haxorg_destroy_ImmRawText(haxorg_ImmRawText* obj) { org::bind::c::execute_destroy<org::imm::ImmRawText>(obj); }

bool haxorg_ImmPunctuation___eq__(haxorg_ImmPunctuation __this, haxorg_ImmPunctuation other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmPunctuation const&) const, haxorg_ImmPunctuation>(&operator==, org_context, other); }

void haxorg_destroy_ImmPunctuation(haxorg_ImmPunctuation* obj) { org::bind::c::execute_destroy<org::imm::ImmPunctuation>(obj); }

bool haxorg_ImmPlaceholder___eq__(haxorg_ImmPlaceholder __this, haxorg_ImmPlaceholder other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmPlaceholder const&) const, haxorg_ImmPlaceholder>(&operator==, org_context, other); }

void haxorg_destroy_ImmPlaceholder(haxorg_ImmPlaceholder* obj) { org::bind::c::execute_destroy<org::imm::ImmPlaceholder>(obj); }

bool haxorg_ImmBigIdent___eq__(haxorg_ImmBigIdent __this, haxorg_ImmBigIdent other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmBigIdent const&) const, haxorg_ImmBigIdent>(&operator==, org_context, other); }

void haxorg_destroy_ImmBigIdent(haxorg_ImmBigIdent* obj) { org::bind::c::execute_destroy<org::imm::ImmBigIdent>(obj); }

bool haxorg_ImmTextTarget___eq__(haxorg_ImmTextTarget __this, haxorg_ImmTextTarget other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmTextTarget const&) const, haxorg_ImmTextTarget>(&operator==, org_context, other); }

void haxorg_destroy_ImmTextTarget(haxorg_ImmTextTarget* obj) { org::bind::c::execute_destroy<org::imm::ImmTextTarget>(obj); }

bool haxorg_ImmErrorSkipToken___eq__(haxorg_ImmErrorSkipToken __this, haxorg_ImmErrorSkipToken other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmErrorSkipToken const&) const, haxorg_ImmErrorSkipToken>(&operator==, org_context, other); }

void haxorg_destroy_ImmErrorSkipToken(haxorg_ImmErrorSkipToken* obj) { org::bind::c::execute_destroy<org::imm::ImmErrorSkipToken>(obj); }

bool haxorg_ImmBold___eq__(haxorg_ImmBold __this, haxorg_ImmBold other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmBold const&) const, haxorg_ImmBold>(&operator==, org_context, other); }

void haxorg_destroy_ImmBold(haxorg_ImmBold* obj) { org::bind::c::execute_destroy<org::imm::ImmBold>(obj); }

bool haxorg_ImmUnderline___eq__(haxorg_ImmUnderline __this, haxorg_ImmUnderline other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmUnderline const&) const, haxorg_ImmUnderline>(&operator==, org_context, other); }

void haxorg_destroy_ImmUnderline(haxorg_ImmUnderline* obj) { org::bind::c::execute_destroy<org::imm::ImmUnderline>(obj); }

bool haxorg_ImmMonospace___eq__(haxorg_ImmMonospace __this, haxorg_ImmMonospace other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmMonospace const&) const, haxorg_ImmMonospace>(&operator==, org_context, other); }

void haxorg_destroy_ImmMonospace(haxorg_ImmMonospace* obj) { org::bind::c::execute_destroy<org::imm::ImmMonospace>(obj); }

bool haxorg_ImmMarkQuote___eq__(haxorg_ImmMarkQuote __this, haxorg_ImmMarkQuote other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmMarkQuote const&) const, haxorg_ImmMarkQuote>(&operator==, org_context, other); }

void haxorg_destroy_ImmMarkQuote(haxorg_ImmMarkQuote* obj) { org::bind::c::execute_destroy<org::imm::ImmMarkQuote>(obj); }

bool haxorg_ImmVerbatim___eq__(haxorg_ImmVerbatim __this, haxorg_ImmVerbatim other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmVerbatim const&) const, haxorg_ImmVerbatim>(&operator==, org_context, other); }

void haxorg_destroy_ImmVerbatim(haxorg_ImmVerbatim* obj) { org::bind::c::execute_destroy<org::imm::ImmVerbatim>(obj); }

bool haxorg_ImmItalic___eq__(haxorg_ImmItalic __this, haxorg_ImmItalic other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmItalic const&) const, haxorg_ImmItalic>(&operator==, org_context, other); }

void haxorg_destroy_ImmItalic(haxorg_ImmItalic* obj) { org::bind::c::execute_destroy<org::imm::ImmItalic>(obj); }

bool haxorg_ImmStrike___eq__(haxorg_ImmStrike __this, haxorg_ImmStrike other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmStrike const&) const, haxorg_ImmStrike>(&operator==, org_context, other); }

void haxorg_destroy_ImmStrike(haxorg_ImmStrike* obj) { org::bind::c::execute_destroy<org::imm::ImmStrike>(obj); }

bool haxorg_ImmPar___eq__(haxorg_ImmPar __this, haxorg_ImmPar other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmPar const&) const, haxorg_ImmPar>(&operator==, org_context, other); }

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

haxorg_StdOptional haxorg_ImmAdapterDirectoryAPI_getFsSubnode(haxorg_ImmAdapterDirectoryAPI __this, haxorg_HstdStr name, bool withPath, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_StdOptional, std::optional<org::imm::ImmAdapter>(*)(hstd::Str const&, bool) const, haxorg_HstdStr, bool>(&getFsSubnode, org_context, name, withPath); }

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

bool haxorg_ImmBlock___eq__(haxorg_ImmBlock __this, haxorg_ImmBlock other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmBlock const&) const, haxorg_ImmBlock>(&operator==, org_context, other); }

void haxorg_destroy_ImmBlock(haxorg_ImmBlock* obj) { org::bind::c::execute_destroy<org::imm::ImmBlock>(obj); }

bool haxorg_ImmLineCommand___eq__(haxorg_ImmLineCommand __this, haxorg_ImmLineCommand other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmLineCommand const&) const, haxorg_ImmLineCommand>(&operator==, org_context, other); }

void haxorg_destroy_ImmLineCommand(haxorg_ImmLineCommand* obj) { org::bind::c::execute_destroy<org::imm::ImmLineCommand>(obj); }

bool haxorg_ImmCmdCreator___eq__(haxorg_ImmCmdCreator __this, haxorg_ImmCmdCreator other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmCmdCreator const&) const, haxorg_ImmCmdCreator>(&operator==, org_context, other); }

void haxorg_destroy_ImmCmdCreator(haxorg_ImmCmdCreator* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdCreator>(obj); }

bool haxorg_ImmCmdAuthor___eq__(haxorg_ImmCmdAuthor __this, haxorg_ImmCmdAuthor other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmCmdAuthor const&) const, haxorg_ImmCmdAuthor>(&operator==, org_context, other); }

void haxorg_destroy_ImmCmdAuthor(haxorg_ImmCmdAuthor* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdAuthor>(obj); }

bool haxorg_ImmCmdEmail___eq__(haxorg_ImmCmdEmail __this, haxorg_ImmCmdEmail other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmCmdEmail const&) const, haxorg_ImmCmdEmail>(&operator==, org_context, other); }

void haxorg_destroy_ImmCmdEmail(haxorg_ImmCmdEmail* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdEmail>(obj); }

bool haxorg_ImmCmdLanguage___eq__(haxorg_ImmCmdLanguage __this, haxorg_ImmCmdLanguage other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmCmdLanguage const&) const, haxorg_ImmCmdLanguage>(&operator==, org_context, other); }

void haxorg_destroy_ImmCmdLanguage(haxorg_ImmCmdLanguage* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdLanguage>(obj); }

bool haxorg_ImmCmdCustomArgs___eq__(haxorg_ImmCmdCustomArgs __this, haxorg_ImmCmdCustomArgs other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmCmdCustomArgs const&) const, haxorg_ImmCmdCustomArgs>(&operator==, org_context, other); }

void haxorg_destroy_ImmCmdCustomArgs(haxorg_ImmCmdCustomArgs* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdCustomArgs>(obj); }

bool haxorg_ImmCmdTblfm___eq__(haxorg_ImmCmdTblfm __this, haxorg_ImmCmdTblfm other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmCmdTblfm const&) const, haxorg_ImmCmdTblfm>(&operator==, org_context, other); }

void haxorg_destroy_ImmCmdTblfm(haxorg_ImmCmdTblfm* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdTblfm>(obj); }

bool haxorg_ImmCell___eq__(haxorg_ImmCell __this, haxorg_ImmCell other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmCell const&) const, haxorg_ImmCell>(&operator==, org_context, other); }

void haxorg_destroy_ImmCell(haxorg_ImmCell* obj) { org::bind::c::execute_destroy<org::imm::ImmCell>(obj); }

bool haxorg_ImmRow___eq__(haxorg_ImmRow __this, haxorg_ImmRow other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmRow const&) const, haxorg_ImmRow>(&operator==, org_context, other); }

void haxorg_destroy_ImmRow(haxorg_ImmRow* obj) { org::bind::c::execute_destroy<org::imm::ImmRow>(obj); }

void haxorg_destroy_ImmAdapterCmdAPI(haxorg_ImmAdapterCmdAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdCustomRawAPI(haxorg_ImmAdapterCmdCustomRawAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdCustomRawAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdCustomTextAPI(haxorg_ImmAdapterCmdCustomTextAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdCustomTextAPI>(obj); }

void haxorg_destroy_ImmAdapterLinkAPI(haxorg_ImmAdapterLinkAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterLinkAPI>(obj); }

void haxorg_destroy_ImmAdapterBlockCommentAPI(haxorg_ImmAdapterBlockCommentAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockCommentAPI>(obj); }

void haxorg_destroy_ImmAdapterParagraphAPI(haxorg_ImmAdapterParagraphAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterParagraphAPI>(obj); }

void haxorg_destroy_ImmAdapterListAPI(haxorg_ImmAdapterListAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterListAPI>(obj); }

void haxorg_ImmAdapterTOfImmStmt_ImmAdapterT(haxorg_ImmStmtAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmStmt_getAttached(haxorg_ImmStmtAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmVec, hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg>>(*)() const>(&getAttached, org_context); }

void haxorg_destroy_ImmStmtAdapter(haxorg_ImmStmtAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmSubtree_ImmAdapterT(haxorg_ImmSubtreeAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

int haxorg_ImmAdapterTOfImmSubtree_getLevel(haxorg_ImmSubtreeAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<int, int(*)() const>(&getLevel, org_context); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmSubtree_getTreeId(haxorg_ImmSubtreeAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<hstd::Str> const&(*)() const>(&getTreeId, org_context); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmSubtree_getTodo(haxorg_ImmSubtreeAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<hstd::Str> const&(*)() const>(&getTodo, org_context); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmSubtree_getCompletion(haxorg_ImmSubtreeAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<org::sem::SubtreeCompletion> const&(*)() const>(&getCompletion, org_context); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmSubtree_getDescription(haxorg_ImmSubtreeAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(*)() const>(&getDescription, org_context); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmSubtree_getTags(haxorg_ImmSubtreeAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmVec, hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag>>(*)() const>(&getTags, org_context); }

haxorg_ImmAdapter haxorg_ImmAdapterTOfImmSubtree_getTitle(haxorg_ImmSubtreeAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmAdapter, org::imm::ImmAdapter(*)() const>(&getTitle, org_context); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmSubtree_getLogbook(haxorg_ImmSubtreeAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmVec, hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmSubtreeLog>>(*)() const>(&getLogbook, org_context); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmSubtree_getProperties(haxorg_ImmSubtreeAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmVec, hstd::ext::ImmVec<org::sem::NamedProperty>(*)() const>(&getProperties, org_context); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmSubtree_getClosed(haxorg_ImmSubtreeAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime>>(*)() const>(&getClosed, org_context); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmSubtree_getDeadline(haxorg_ImmSubtreeAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime>>(*)() const>(&getDeadline, org_context); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmSubtree_getScheduled(haxorg_ImmSubtreeAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime>>(*)() const>(&getScheduled, org_context); }

bool haxorg_ImmAdapterTOfImmSubtree_getIsComment(haxorg_ImmSubtreeAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&getIsComment, org_context); }

bool haxorg_ImmAdapterTOfImmSubtree_getIsArchived(haxorg_ImmSubtreeAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&getIsArchived, org_context); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmSubtree_getPriority(haxorg_ImmSubtreeAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<hstd::Str> const&(*)() const>(&getPriority, org_context); }

void haxorg_destroy_ImmSubtreeAdapter(haxorg_ImmSubtreeAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmNoNode_ImmAdapterT(haxorg_ImmNoNodeAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmNoNodeAdapter(haxorg_ImmNoNodeAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmErrorItem_ImmAdapterT(haxorg_ImmErrorItemAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_OrgDiagnostics haxorg_ImmAdapterTOfImmErrorItem_getDiag(haxorg_ImmErrorItemAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_OrgDiagnostics, org::sem::OrgDiagnostics(*)() const>(&getDiag, org_context); }

void haxorg_destroy_ImmErrorItemAdapter(haxorg_ImmErrorItemAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmErrorGroup_ImmAdapterT(haxorg_ImmErrorGroupAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmErrorGroup_getDiagnostics(haxorg_ImmErrorGroupAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmVec, hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorItem>>(*)() const>(&getDiagnostics, org_context); }

void haxorg_destroy_ImmErrorGroupAdapter(haxorg_ImmErrorGroupAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmErrorSkipGroup_ImmAdapterT(haxorg_ImmErrorSkipGroupAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmErrorSkipGroup_getSkipped(haxorg_ImmErrorSkipGroupAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmVec, hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorSkipToken>>(*)() const>(&getSkipped, org_context); }

void haxorg_destroy_ImmErrorSkipGroupAdapter(haxorg_ImmErrorSkipGroupAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmErrorSkipToken_ImmAdapterT(haxorg_ImmErrorSkipTokenAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmErrorSkipTokenAdapter(haxorg_ImmErrorSkipTokenAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmStmtList_ImmAdapterT(haxorg_ImmStmtListAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmStmtListAdapter(haxorg_ImmStmtListAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmEmpty_ImmAdapterT(haxorg_ImmEmptyAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmEmptyAdapter(haxorg_ImmEmptyAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmAdapterHashTagAPI(haxorg_ImmAdapterHashTagAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterHashTagAPI>(obj); }

void haxorg_destroy_ImmAdapterInlineFootnoteAPI(haxorg_ImmAdapterInlineFootnoteAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterInlineFootnoteAPI>(obj); }

void haxorg_destroy_ImmAdapterSubtreeCompletionAPI(haxorg_ImmAdapterSubtreeCompletionAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterSubtreeCompletionAPI>(obj); }

void haxorg_ImmAdapterTOfImmInline_ImmAdapterT(haxorg_ImmInlineAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmInlineAdapter(haxorg_ImmInlineAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmTime_ImmAdapterT(haxorg_ImmTimeAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

bool haxorg_ImmAdapterTOfImmTime_getIsActive(haxorg_ImmTimeAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&getIsActive, org_context); }

void haxorg_destroy_ImmTimeAdapter(haxorg_ImmTimeAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmTimeRange_ImmAdapterT(haxorg_ImmTimeRangeAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_ImmAdapter haxorg_ImmAdapterTOfImmTimeRange_getFrom(haxorg_ImmTimeRangeAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmAdapter, org::imm::ImmAdapter(*)() const>(&getFrom, org_context); }

haxorg_ImmAdapter haxorg_ImmAdapterTOfImmTimeRange_getTo(haxorg_ImmTimeRangeAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmAdapter, org::imm::ImmAdapter(*)() const>(&getTo, org_context); }

void haxorg_destroy_ImmTimeRangeAdapter(haxorg_ImmTimeRangeAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmMacro_ImmAdapterT(haxorg_ImmMacroAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmMacro_getName(haxorg_ImmMacroAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str const&(*)() const>(&getName, org_context); }

haxorg_AttrGroup haxorg_ImmAdapterTOfImmMacro_getAttrs(haxorg_ImmMacroAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_AttrGroup, org::sem::AttrGroup(*)() const>(&getAttrs, org_context); }

void haxorg_destroy_ImmMacroAdapter(haxorg_ImmMacroAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmSymbol_ImmAdapterT(haxorg_ImmSymbolAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmSymbol_getName(haxorg_ImmSymbolAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str const&(*)() const>(&getName, org_context); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmSymbol_getParameters(haxorg_ImmSymbolAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmVec, hstd::ext::ImmVec<org::imm::ImmSymbol::Param>(*)() const>(&getParameters, org_context); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmSymbol_getPositional(haxorg_ImmSymbolAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmVec, hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg>>(*)() const>(&getPositional, org_context); }

void haxorg_destroy_ImmSymbolAdapter(haxorg_ImmSymbolAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

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

void haxorg_ImmAdapterTOfImmLeaf_ImmAdapterT(haxorg_ImmLeafAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmLeaf_getText(haxorg_ImmLeafAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str const&(*)() const>(&getText, org_context); }

void haxorg_destroy_ImmLeafAdapter(haxorg_ImmLeafAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmAdapterBoldAPI(haxorg_ImmAdapterBoldAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBoldAPI>(obj); }

void haxorg_destroy_ImmAdapterUnderlineAPI(haxorg_ImmAdapterUnderlineAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterUnderlineAPI>(obj); }

void haxorg_destroy_ImmAdapterMonospaceAPI(haxorg_ImmAdapterMonospaceAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterMonospaceAPI>(obj); }

void haxorg_destroy_ImmAdapterMarkQuoteAPI(haxorg_ImmAdapterMarkQuoteAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterMarkQuoteAPI>(obj); }

void haxorg_destroy_ImmAdapterRadioTargetAPI(haxorg_ImmAdapterRadioTargetAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterRadioTargetAPI>(obj); }

void haxorg_destroy_ImmAdapterVerbatimAPI(haxorg_ImmAdapterVerbatimAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterVerbatimAPI>(obj); }

void haxorg_destroy_ImmAdapterItalicAPI(haxorg_ImmAdapterItalicAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterItalicAPI>(obj); }

void haxorg_destroy_ImmAdapterStrikeAPI(haxorg_ImmAdapterStrikeAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterStrikeAPI>(obj); }

void haxorg_destroy_ImmAdapterParAPI(haxorg_ImmAdapterParAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterParAPI>(obj); }

void haxorg_ImmAdapterTOfImmMarkup_ImmAdapterT(haxorg_ImmMarkupAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmMarkupAdapter(haxorg_ImmMarkupAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmLatex_ImmAdapterT(haxorg_ImmLatexAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmLatexAdapter(haxorg_ImmLatexAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmSubtreeLog_ImmAdapterT(haxorg_ImmSubtreeLogAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_SubtreeLogHead haxorg_ImmAdapterTOfImmSubtreeLog_getHead(haxorg_ImmSubtreeLogAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, org::sem::SubtreeLogHead(*)() const>(&getHead, org_context); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmSubtreeLog_getDesc(haxorg_ImmSubtreeLogAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmStmtList>>(*)() const>(&getDesc, org_context); }

void haxorg_destroy_ImmSubtreeLogAdapter(haxorg_ImmSubtreeLogAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmColonExample_ImmAdapterT(haxorg_ImmColonExampleAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmColonExampleAdapter(haxorg_ImmColonExampleAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmCall_ImmAdapterT(haxorg_ImmCallAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmCall_getName(haxorg_ImmCallAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str const&(*)() const>(&getName, org_context); }

haxorg_AttrGroup haxorg_ImmAdapterTOfImmCall_getAttrs(haxorg_ImmCallAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_AttrGroup, org::sem::AttrGroup(*)() const>(&getAttrs, org_context); }

bool haxorg_ImmAdapterTOfImmCall_getIsCommand(haxorg_ImmCallAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&getIsCommand, org_context); }

void haxorg_destroy_ImmCallAdapter(haxorg_ImmCallAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmFile_ImmAdapterT(haxorg_ImmFileAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmFile_getRelPath(haxorg_ImmFileAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str const&(*)() const>(&getRelPath, org_context); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmFile_getAbsPath(haxorg_ImmFileAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str const&(*)() const>(&getAbsPath, org_context); }

void haxorg_destroy_ImmFileAdapter(haxorg_ImmFileAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmDirectory_ImmAdapterT(haxorg_ImmDirectoryAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmDirectory_getRelPath(haxorg_ImmDirectoryAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str const&(*)() const>(&getRelPath, org_context); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmDirectory_getAbsPath(haxorg_ImmDirectoryAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str const&(*)() const>(&getAbsPath, org_context); }

void haxorg_destroy_ImmDirectoryAdapter(haxorg_ImmDirectoryAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmSymlink_ImmAdapterT(haxorg_ImmSymlinkAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

bool haxorg_ImmAdapterTOfImmSymlink_getIsDirectory(haxorg_ImmSymlinkAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&getIsDirectory, org_context); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmSymlink_getAbsPath(haxorg_ImmSymlinkAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str const&(*)() const>(&getAbsPath, org_context); }

void haxorg_destroy_ImmSymlinkAdapter(haxorg_ImmSymlinkAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmDocumentFragment_ImmAdapterT(haxorg_ImmDocumentFragmentAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

int haxorg_ImmAdapterTOfImmDocumentFragment_getBaseLine(haxorg_ImmDocumentFragmentAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<int, int(*)() const>(&getBaseLine, org_context); }

int haxorg_ImmAdapterTOfImmDocumentFragment_getBaseCol(haxorg_ImmDocumentFragmentAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<int, int(*)() const>(&getBaseCol, org_context); }

void haxorg_destroy_ImmDocumentFragmentAdapter(haxorg_ImmDocumentFragmentAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmCriticMarkup_ImmAdapterT(haxorg_ImmCriticMarkupAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_ImmCriticMarkupKind haxorg_ImmAdapterTOfImmCriticMarkup_getKind(haxorg_ImmCriticMarkupAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmCriticMarkupKind, org::imm::ImmCriticMarkup::Kind(*)() const>(&getKind, org_context); }

void haxorg_destroy_ImmCriticMarkupAdapter(haxorg_ImmCriticMarkupAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmListItem_ImmAdapterT(haxorg_ImmListItemAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_CheckboxState haxorg_ImmAdapterTOfImmListItem_getCheckbox(haxorg_ImmListItemAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_CheckboxState, CheckboxState(*)() const>(&getCheckbox, org_context); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmListItem_getHeader(haxorg_ImmListItemAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(*)() const>(&getHeader, org_context); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmListItem_getBullet(haxorg_ImmListItemAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<hstd::Str> const&(*)() const>(&getBullet, org_context); }

void haxorg_destroy_ImmListItemAdapter(haxorg_ImmListItemAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmDocumentOptions_ImmAdapterT(haxorg_ImmDocumentOptionsAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_InitialSubtreeVisibility haxorg_ImmAdapterTOfImmDocumentOptions_getInitialVisibility(haxorg_ImmDocumentOptionsAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_InitialSubtreeVisibility, InitialSubtreeVisibility(*)() const>(&getInitialVisibility, org_context); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmDocumentOptions_getProperties(haxorg_ImmDocumentOptionsAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmVec, hstd::ext::ImmVec<org::sem::NamedProperty>(*)() const>(&getProperties, org_context); }

haxorg_DocumentExportConfig haxorg_ImmAdapterTOfImmDocumentOptions_getExportConfig(haxorg_ImmDocumentOptionsAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_DocumentExportConfig, org::sem::DocumentExportConfig(*)() const>(&getExportConfig, org_context); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmDocumentOptions_getFixedWidthSections(haxorg_ImmDocumentOptionsAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<bool> const&(*)() const>(&getFixedWidthSections, org_context); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmDocumentOptions_getStartupIndented(haxorg_ImmDocumentOptionsAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<bool> const&(*)() const>(&getStartupIndented, org_context); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmDocumentOptions_getCategory(haxorg_ImmDocumentOptionsAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<hstd::Str> const&(*)() const>(&getCategory, org_context); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmDocumentOptions_getSetupfile(haxorg_ImmDocumentOptionsAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<hstd::Str> const&(*)() const>(&getSetupfile, org_context); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmDocumentOptions_getMaxSubtreeLevelExport(haxorg_ImmDocumentOptionsAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<int> const&(*)() const>(&getMaxSubtreeLevelExport, org_context); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmDocumentOptions_getColumns(haxorg_ImmDocumentOptionsAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<org::sem::ColumnView> const&(*)() const>(&getColumns, org_context); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmDocumentOptions_getTodoKeywords(haxorg_ImmDocumentOptionsAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmVec, hstd::ext::ImmVec<org::sem::TodoKeyword>(*)() const>(&getTodoKeywords, org_context); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmDocumentOptions_getDoneKeywords(haxorg_ImmDocumentOptionsAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmVec, hstd::ext::ImmVec<org::sem::TodoKeyword>(*)() const>(&getDoneKeywords, org_context); }

void haxorg_destroy_ImmDocumentOptionsAdapter(haxorg_ImmDocumentOptionsAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmDocument_ImmAdapterT(haxorg_ImmDocumentAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmDocument_getTitle(haxorg_ImmDocumentAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(*)() const>(&getTitle, org_context); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmDocument_getAuthor(haxorg_ImmDocumentAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(*)() const>(&getAuthor, org_context); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmDocument_getCreator(haxorg_ImmDocumentAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(*)() const>(&getCreator, org_context); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmDocument_getFiletags(haxorg_ImmDocumentAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmVec, hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag>>(*)() const>(&getFiletags, org_context); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmDocument_getEmail(haxorg_ImmDocumentAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmRawText>>(*)() const>(&getEmail, org_context); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmDocument_getLanguage(haxorg_ImmDocumentAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmVec, hstd::ext::ImmVec<hstd::Str>(*)() const>(&getLanguage, org_context); }

haxorg_ImmAdapter haxorg_ImmAdapterTOfImmDocument_getOptions(haxorg_ImmDocumentAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmAdapter, org::imm::ImmAdapter(*)() const>(&getOptions, org_context); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmDocument_getExportFileName(haxorg_ImmDocumentAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<hstd::Str> const&(*)() const>(&getExportFileName, org_context); }

void haxorg_destroy_ImmDocumentAdapter(haxorg_ImmDocumentAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmFileTarget_ImmAdapterT(haxorg_ImmFileTargetAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmFileTarget_getPath(haxorg_ImmFileTargetAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str const&(*)() const>(&getPath, org_context); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmFileTarget_getLine(haxorg_ImmFileTargetAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<int> const&(*)() const>(&getLine, org_context); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmFileTarget_getSearchTarget(haxorg_ImmFileTargetAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<hstd::Str> const&(*)() const>(&getSearchTarget, org_context); }

bool haxorg_ImmAdapterTOfImmFileTarget_getRestrictToHeadlines(haxorg_ImmFileTargetAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&getRestrictToHeadlines, org_context); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmFileTarget_getTargetId(haxorg_ImmFileTargetAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<hstd::Str> const&(*)() const>(&getTargetId, org_context); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmFileTarget_getRegexp(haxorg_ImmFileTargetAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<hstd::Str> const&(*)() const>(&getRegexp, org_context); }

void haxorg_destroy_ImmFileTargetAdapter(haxorg_ImmFileTargetAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmTextSeparator_ImmAdapterT(haxorg_ImmTextSeparatorAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmTextSeparatorAdapter(haxorg_ImmTextSeparatorAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmCmdInclude_ImmAdapterT(haxorg_ImmCmdIncludeAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdInclude_getPath(haxorg_ImmCmdIncludeAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str const&(*)() const>(&getPath, org_context); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmCmdInclude_getFirstLine(haxorg_ImmCmdIncludeAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<int> const&(*)() const>(&getFirstLine, org_context); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmCmdInclude_getLastLine(haxorg_ImmCmdIncludeAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<int> const&(*)() const>(&getLastLine, org_context); }

void haxorg_destroy_ImmCmdIncludeAdapter(haxorg_ImmCmdIncludeAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmDocumentGroup_ImmAdapterT(haxorg_ImmDocumentGroupAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmDocumentGroupAdapter(haxorg_ImmDocumentGroupAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_BlockCenter(haxorg_BlockCenter* obj) { org::bind::c::execute_destroy<org::sem::BlockCenter>(obj); }

void haxorg_destroy_BlockQuote(haxorg_BlockQuote* obj) { org::bind::c::execute_destroy<org::sem::BlockQuote>(obj); }

void haxorg_destroy_BlockVerse(haxorg_BlockVerse* obj) { org::bind::c::execute_destroy<org::sem::BlockVerse>(obj); }

void haxorg_destroy_BlockDynamicFallback(haxorg_BlockDynamicFallback* obj) { org::bind::c::execute_destroy<org::sem::BlockDynamicFallback>(obj); }

void haxorg_destroy_BlockExample(haxorg_BlockExample* obj) { org::bind::c::execute_destroy<org::sem::BlockExample>(obj); }

haxorg_HstdOpt haxorg_BlockExport_getPlacement(haxorg_BlockExport __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<hstd::Str>(*)() const>(&getPlacement, org_context); }

void haxorg_destroy_BlockExport(haxorg_BlockExport* obj) { org::bind::c::execute_destroy<org::sem::BlockExport>(obj); }

void haxorg_destroy_BlockAdmonition(haxorg_BlockAdmonition* obj) { org::bind::c::execute_destroy<org::sem::BlockAdmonition>(obj); }

void haxorg_destroy_BlockCodeEvalResult(haxorg_BlockCodeEvalResult* obj) { org::bind::c::execute_destroy<org::sem::BlockCodeEvalResult>(obj); }

haxorg_HstdOpt haxorg_BlockCode_getVariable(haxorg_BlockCode __this, haxorg_HstdStr varname, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<org::sem::AttrValue>(*)(hstd::Str const&) const, haxorg_HstdStr>(&getVariable, org_context, varname); }

void haxorg_destroy_BlockCode(haxorg_BlockCode* obj) { org::bind::c::execute_destroy<org::sem::BlockCode>(obj); }

void haxorg_destroy_Table(haxorg_Table* obj) { org::bind::c::execute_destroy<org::sem::Table>(obj); }

void haxorg_destroy_Attached(haxorg_Attached* obj) { org::bind::c::execute_destroy<org::sem::Attached>(obj); }

bool haxorg_ImmBlockCenter___eq__(haxorg_ImmBlockCenter __this, haxorg_ImmBlockCenter other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmBlockCenter const&) const, haxorg_ImmBlockCenter>(&operator==, org_context, other); }

void haxorg_destroy_ImmBlockCenter(haxorg_ImmBlockCenter* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockCenter>(obj); }

bool haxorg_ImmBlockQuote___eq__(haxorg_ImmBlockQuote __this, haxorg_ImmBlockQuote other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmBlockQuote const&) const, haxorg_ImmBlockQuote>(&operator==, org_context, other); }

void haxorg_destroy_ImmBlockQuote(haxorg_ImmBlockQuote* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockQuote>(obj); }

bool haxorg_ImmBlockVerse___eq__(haxorg_ImmBlockVerse __this, haxorg_ImmBlockVerse other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmBlockVerse const&) const, haxorg_ImmBlockVerse>(&operator==, org_context, other); }

void haxorg_destroy_ImmBlockVerse(haxorg_ImmBlockVerse* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockVerse>(obj); }

bool haxorg_ImmBlockDynamicFallback___eq__(haxorg_ImmBlockDynamicFallback __this, haxorg_ImmBlockDynamicFallback other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmBlockDynamicFallback const&) const, haxorg_ImmBlockDynamicFallback>(&operator==, org_context, other); }

void haxorg_destroy_ImmBlockDynamicFallback(haxorg_ImmBlockDynamicFallback* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockDynamicFallback>(obj); }

bool haxorg_ImmBlockExample___eq__(haxorg_ImmBlockExample __this, haxorg_ImmBlockExample other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmBlockExample const&) const, haxorg_ImmBlockExample>(&operator==, org_context, other); }

void haxorg_destroy_ImmBlockExample(haxorg_ImmBlockExample* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockExample>(obj); }

bool haxorg_ImmBlockExport___eq__(haxorg_ImmBlockExport __this, haxorg_ImmBlockExport other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmBlockExport const&) const, haxorg_ImmBlockExport>(&operator==, org_context, other); }

void haxorg_destroy_ImmBlockExport(haxorg_ImmBlockExport* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockExport>(obj); }

bool haxorg_ImmBlockAdmonition___eq__(haxorg_ImmBlockAdmonition __this, haxorg_ImmBlockAdmonition other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmBlockAdmonition const&) const, haxorg_ImmBlockAdmonition>(&operator==, org_context, other); }

void haxorg_destroy_ImmBlockAdmonition(haxorg_ImmBlockAdmonition* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockAdmonition>(obj); }

bool haxorg_ImmBlockCodeEvalResult___eq__(haxorg_ImmBlockCodeEvalResult __this, haxorg_ImmBlockCodeEvalResult other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmBlockCodeEvalResult const&) const, haxorg_ImmBlockCodeEvalResult>(&operator==, org_context, other); }

void haxorg_destroy_ImmBlockCodeEvalResult(haxorg_ImmBlockCodeEvalResult* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockCodeEvalResult>(obj); }

bool haxorg_ImmBlockCode___eq__(haxorg_ImmBlockCode __this, haxorg_ImmBlockCode other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmBlockCode const&) const, haxorg_ImmBlockCode>(&operator==, org_context, other); }

void haxorg_destroy_ImmBlockCode(haxorg_ImmBlockCode* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockCode>(obj); }

bool haxorg_ImmTable___eq__(haxorg_ImmTable __this, haxorg_ImmTable other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmTable const&) const, haxorg_ImmTable>(&operator==, org_context, other); }

void haxorg_destroy_ImmTable(haxorg_ImmTable* obj) { org::bind::c::execute_destroy<org::imm::ImmTable>(obj); }

bool haxorg_ImmAttached___eq__(haxorg_ImmAttached __this, haxorg_ImmAttached other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmAttached const&) const, haxorg_ImmAttached>(&operator==, org_context, other); }

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

void haxorg_ImmAdapterTOfImmCmd_ImmAdapterT(haxorg_ImmCmdAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_AttrGroup haxorg_ImmAdapterTOfImmCmd_getAttrs(haxorg_ImmCmdAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_AttrGroup, org::sem::AttrGroup(*)() const>(&getAttrs, org_context); }

void haxorg_destroy_ImmCmdAdapter(haxorg_ImmCmdAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmCmdCustomRaw_ImmAdapterT(haxorg_ImmCmdCustomRawAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdCustomRaw_getName(haxorg_ImmCmdCustomRawAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str const&(*)() const>(&getName, org_context); }

bool haxorg_ImmAdapterTOfImmCmdCustomRaw_getIsAttached(haxorg_ImmCmdCustomRawAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&getIsAttached, org_context); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdCustomRaw_getText(haxorg_ImmCmdCustomRawAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str const&(*)() const>(&getText, org_context); }

void haxorg_destroy_ImmCmdCustomRawAdapter(haxorg_ImmCmdCustomRawAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmCmdCustomText_ImmAdapterT(haxorg_ImmCmdCustomTextAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdCustomText_getName(haxorg_ImmCmdCustomTextAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str const&(*)() const>(&getName, org_context); }

bool haxorg_ImmAdapterTOfImmCmdCustomText_getIsAttached(haxorg_ImmCmdCustomTextAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&getIsAttached, org_context); }

haxorg_ImmAdapter haxorg_ImmAdapterTOfImmCmdCustomText_getText(haxorg_ImmCmdCustomTextAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmAdapter, org::imm::ImmAdapter(*)() const>(&getText, org_context); }

void haxorg_destroy_ImmCmdCustomTextAdapter(haxorg_ImmCmdCustomTextAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmLink_ImmAdapterT(haxorg_ImmLinkAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmLink_getDescription(haxorg_ImmLinkAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(*)() const>(&getDescription, org_context); }

haxorg_LinkTarget haxorg_ImmAdapterTOfImmLink_getTarget(haxorg_ImmLinkAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_LinkTarget, org::sem::LinkTarget(*)() const>(&getTarget, org_context); }

void haxorg_destroy_ImmLinkAdapter(haxorg_ImmLinkAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmBlockComment_ImmAdapterT(haxorg_ImmBlockCommentAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmBlockCommentAdapter(haxorg_ImmBlockCommentAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmParagraph_ImmAdapterT(haxorg_ImmParagraphAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmParagraphAdapter(haxorg_ImmParagraphAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmList_ImmAdapterT(haxorg_ImmListAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmListAdapter(haxorg_ImmListAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmHashTag_ImmAdapterT(haxorg_ImmHashTagAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_HashTagText haxorg_ImmAdapterTOfImmHashTag_getText(haxorg_ImmHashTagAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HashTagText, org::sem::HashTagText(*)() const>(&getText, org_context); }

void haxorg_destroy_ImmHashTagAdapter(haxorg_ImmHashTagAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmInlineFootnote_ImmAdapterT(haxorg_ImmInlineFootnoteAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmInlineFootnote_getTag(haxorg_ImmInlineFootnoteAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str const&(*)() const>(&getTag, org_context); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmInlineFootnote_getDefinition(haxorg_ImmInlineFootnoteAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<org::imm::ImmAdapter>(*)() const>(&getDefinition, org_context); }

void haxorg_destroy_ImmInlineFootnoteAdapter(haxorg_ImmInlineFootnoteAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmEscaped_ImmAdapterT(haxorg_ImmEscapedAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmEscapedAdapter(haxorg_ImmEscapedAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmNewline_ImmAdapterT(haxorg_ImmNewlineAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmNewlineAdapter(haxorg_ImmNewlineAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmSpace_ImmAdapterT(haxorg_ImmSpaceAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmSpaceAdapter(haxorg_ImmSpaceAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmWord_ImmAdapterT(haxorg_ImmWordAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmWordAdapter(haxorg_ImmWordAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmAtMention_ImmAdapterT(haxorg_ImmAtMentionAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmAtMentionAdapter(haxorg_ImmAtMentionAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmRawText_ImmAdapterT(haxorg_ImmRawTextAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmRawTextAdapter(haxorg_ImmRawTextAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmPunctuation_ImmAdapterT(haxorg_ImmPunctuationAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmPunctuationAdapter(haxorg_ImmPunctuationAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmPlaceholder_ImmAdapterT(haxorg_ImmPlaceholderAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmPlaceholderAdapter(haxorg_ImmPlaceholderAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmBigIdent_ImmAdapterT(haxorg_ImmBigIdentAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmBigIdentAdapter(haxorg_ImmBigIdentAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmTextTarget_ImmAdapterT(haxorg_ImmTextTargetAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmTextTargetAdapter(haxorg_ImmTextTargetAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmBold_ImmAdapterT(haxorg_ImmBoldAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmBoldAdapter(haxorg_ImmBoldAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmUnderline_ImmAdapterT(haxorg_ImmUnderlineAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmUnderlineAdapter(haxorg_ImmUnderlineAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmMonospace_ImmAdapterT(haxorg_ImmMonospaceAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmMonospaceAdapter(haxorg_ImmMonospaceAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmMarkQuote_ImmAdapterT(haxorg_ImmMarkQuoteAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmMarkQuoteAdapter(haxorg_ImmMarkQuoteAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmRadioTarget_ImmAdapterT(haxorg_ImmRadioTargetAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmRadioTarget_getWords(haxorg_ImmRadioTargetAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmVec, hstd::ext::ImmVec<hstd::Str>(*)() const>(&getWords, org_context); }

void haxorg_destroy_ImmRadioTargetAdapter(haxorg_ImmRadioTargetAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmVerbatim_ImmAdapterT(haxorg_ImmVerbatimAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmVerbatimAdapter(haxorg_ImmVerbatimAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmItalic_ImmAdapterT(haxorg_ImmItalicAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmItalicAdapter(haxorg_ImmItalicAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmStrike_ImmAdapterT(haxorg_ImmStrikeAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmStrikeAdapter(haxorg_ImmStrikeAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmPar_ImmAdapterT(haxorg_ImmParAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmParAdapter(haxorg_ImmParAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_CmdCaption(haxorg_CmdCaption* obj) { org::bind::c::execute_destroy<org::sem::CmdCaption>(obj); }

void haxorg_destroy_CmdColumns(haxorg_CmdColumns* obj) { org::bind::c::execute_destroy<org::sem::CmdColumns>(obj); }

void haxorg_destroy_CmdName(haxorg_CmdName* obj) { org::bind::c::execute_destroy<org::sem::CmdName>(obj); }

void haxorg_destroy_CmdCall(haxorg_CmdCall* obj) { org::bind::c::execute_destroy<org::sem::CmdCall>(obj); }

void haxorg_destroy_CmdAttr(haxorg_CmdAttr* obj) { org::bind::c::execute_destroy<org::sem::CmdAttr>(obj); }

void haxorg_destroy_CmdExport(haxorg_CmdExport* obj) { org::bind::c::execute_destroy<org::sem::CmdExport>(obj); }

bool haxorg_ImmCmdCaption___eq__(haxorg_ImmCmdCaption __this, haxorg_ImmCmdCaption other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmCmdCaption const&) const, haxorg_ImmCmdCaption>(&operator==, org_context, other); }

void haxorg_destroy_ImmCmdCaption(haxorg_ImmCmdCaption* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdCaption>(obj); }

bool haxorg_ImmCmdColumns___eq__(haxorg_ImmCmdColumns __this, haxorg_ImmCmdColumns other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmCmdColumns const&) const, haxorg_ImmCmdColumns>(&operator==, org_context, other); }

void haxorg_destroy_ImmCmdColumns(haxorg_ImmCmdColumns* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdColumns>(obj); }

bool haxorg_ImmCmdName___eq__(haxorg_ImmCmdName __this, haxorg_ImmCmdName other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmCmdName const&) const, haxorg_ImmCmdName>(&operator==, org_context, other); }

void haxorg_destroy_ImmCmdName(haxorg_ImmCmdName* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdName>(obj); }

bool haxorg_ImmCmdCall___eq__(haxorg_ImmCmdCall __this, haxorg_ImmCmdCall other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmCmdCall const&) const, haxorg_ImmCmdCall>(&operator==, org_context, other); }

void haxorg_destroy_ImmCmdCall(haxorg_ImmCmdCall* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdCall>(obj); }

bool haxorg_ImmCmdAttr___eq__(haxorg_ImmCmdAttr __this, haxorg_ImmCmdAttr other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmCmdAttr const&) const, haxorg_ImmCmdAttr>(&operator==, org_context, other); }

void haxorg_destroy_ImmCmdAttr(haxorg_ImmCmdAttr* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdAttr>(obj); }

bool haxorg_ImmCmdExport___eq__(haxorg_ImmCmdExport __this, haxorg_ImmCmdExport other, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)(org::imm::ImmCmdExport const&) const, haxorg_ImmCmdExport>(&operator==, org_context, other); }

void haxorg_destroy_ImmCmdExport(haxorg_ImmCmdExport* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdExport>(obj); }

void haxorg_destroy_ImmAdapterAttachedAPI(haxorg_ImmAdapterAttachedAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterAttachedAPI>(obj); }

void haxorg_ImmAdapterTOfImmLineCommand_ImmAdapterT(haxorg_ImmLineCommandAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmLineCommandAdapter(haxorg_ImmLineCommandAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmCmdCustomArgs_ImmAdapterT(haxorg_ImmCmdCustomArgsAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdCustomArgs_getName(haxorg_ImmCmdCustomArgsAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str const&(*)() const>(&getName, org_context); }

bool haxorg_ImmAdapterTOfImmCmdCustomArgs_getIsAttached(haxorg_ImmCmdCustomArgsAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&getIsAttached, org_context); }

void haxorg_destroy_ImmCmdCustomArgsAdapter(haxorg_ImmCmdCustomArgsAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmCmdCreator_ImmAdapterT(haxorg_ImmCmdCreatorAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_ImmAdapter haxorg_ImmAdapterTOfImmCmdCreator_getText(haxorg_ImmCmdCreatorAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmAdapter, org::imm::ImmAdapter(*)() const>(&getText, org_context); }

void haxorg_destroy_ImmCmdCreatorAdapter(haxorg_ImmCmdCreatorAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmCmdAuthor_ImmAdapterT(haxorg_ImmCmdAuthorAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_ImmAdapter haxorg_ImmAdapterTOfImmCmdAuthor_getText(haxorg_ImmCmdAuthorAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmAdapter, org::imm::ImmAdapter(*)() const>(&getText, org_context); }

void haxorg_destroy_ImmCmdAuthorAdapter(haxorg_ImmCmdAuthorAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmCmdEmail_ImmAdapterT(haxorg_ImmCmdEmailAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdEmail_getText(haxorg_ImmCmdEmailAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str const&(*)() const>(&getText, org_context); }

void haxorg_destroy_ImmCmdEmailAdapter(haxorg_ImmCmdEmailAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmCmdLanguage_ImmAdapterT(haxorg_ImmCmdLanguageAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdLanguage_getText(haxorg_ImmCmdLanguageAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str const&(*)() const>(&getText, org_context); }

void haxorg_destroy_ImmCmdLanguageAdapter(haxorg_ImmCmdLanguageAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmCmdTblfm_ImmAdapterT(haxorg_ImmCmdTblfmAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_Tblfm haxorg_ImmAdapterTOfImmCmdTblfm_getExpr(haxorg_ImmCmdTblfmAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_Tblfm, org::sem::Tblfm(*)() const>(&getExpr, org_context); }

void haxorg_destroy_ImmCmdTblfmAdapter(haxorg_ImmCmdTblfmAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

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

void haxorg_ImmAdapterTOfImmBlock_ImmAdapterT(haxorg_ImmBlockAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmBlockAdapter(haxorg_ImmBlockAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmCell_ImmAdapterT(haxorg_ImmCellAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

bool haxorg_ImmAdapterTOfImmCell_getIsBlock(haxorg_ImmCellAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&getIsBlock, org_context); }

void haxorg_destroy_ImmCellAdapter(haxorg_ImmCellAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmRow_ImmAdapterT(haxorg_ImmRowAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmRow_getCells(haxorg_ImmRowAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmVec, hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmCell>>(*)() const>(&getCells, org_context); }

bool haxorg_ImmAdapterTOfImmRow_getIsBlock(haxorg_ImmRowAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&getIsBlock, org_context); }

void haxorg_destroy_ImmRowAdapter(haxorg_ImmRowAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_destroy_ImmAdapterCmdCaptionAPI(haxorg_ImmAdapterCmdCaptionAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdCaptionAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdColumnsAPI(haxorg_ImmAdapterCmdColumnsAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdColumnsAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdNameAPI(haxorg_ImmAdapterCmdNameAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdNameAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdCallAPI(haxorg_ImmAdapterCmdCallAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdCallAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdResultsAPI(haxorg_ImmAdapterCmdResultsAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdResultsAPI>(obj); }

void haxorg_destroy_ImmAdapterCmdAttrAPI(haxorg_ImmAdapterCmdAttrAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdAttrAPI>(obj); }

void haxorg_ImmAdapterTOfImmAttached_ImmAdapterT(haxorg_ImmAttachedAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmAttachedAdapter(haxorg_ImmAttachedAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmBlockCenter_ImmAdapterT(haxorg_ImmBlockCenterAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmBlockCenterAdapter(haxorg_ImmBlockCenterAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmBlockQuote_ImmAdapterT(haxorg_ImmBlockQuoteAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmBlockQuoteAdapter(haxorg_ImmBlockQuoteAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmBlockVerse_ImmAdapterT(haxorg_ImmBlockVerseAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmBlockVerseAdapter(haxorg_ImmBlockVerseAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmBlockExample_ImmAdapterT(haxorg_ImmBlockExampleAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmBlockExampleAdapter(haxorg_ImmBlockExampleAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmInlineExport_ImmAdapterT(haxorg_ImmInlineExportAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmInlineExport_getExporter(haxorg_ImmInlineExportAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str const&(*)() const>(&getExporter, org_context); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmInlineExport_getContent(haxorg_ImmInlineExportAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str const&(*)() const>(&getContent, org_context); }

void haxorg_destroy_ImmInlineExportAdapter(haxorg_ImmInlineExportAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmCmdExport_ImmAdapterT(haxorg_ImmCmdExportAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdExport_getExporter(haxorg_ImmCmdExportAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str const&(*)() const>(&getExporter, org_context); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdExport_getContent(haxorg_ImmCmdExportAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str const&(*)() const>(&getContent, org_context); }

void haxorg_destroy_ImmCmdExportAdapter(haxorg_ImmCmdExportAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmBlockExport_ImmAdapterT(haxorg_ImmBlockExportAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmBlockExport_getExporter(haxorg_ImmBlockExportAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str const&(*)() const>(&getExporter, org_context); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmBlockExport_getContent(haxorg_ImmBlockExportAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str const&(*)() const>(&getContent, org_context); }

void haxorg_destroy_ImmBlockExportAdapter(haxorg_ImmBlockExportAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmBlockDynamicFallback_ImmAdapterT(haxorg_ImmBlockDynamicFallbackAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmBlockDynamicFallback_getName(haxorg_ImmBlockDynamicFallbackAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str const&(*)() const>(&getName, org_context); }

void haxorg_destroy_ImmBlockDynamicFallbackAdapter(haxorg_ImmBlockDynamicFallbackAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmBlockAdmonition_ImmAdapterT(haxorg_ImmBlockAdmonitionAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

void haxorg_destroy_ImmBlockAdmonitionAdapter(haxorg_ImmBlockAdmonitionAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmBlockCodeEvalResult_ImmAdapterT(haxorg_ImmBlockCodeEvalResultAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmBlockCodeEvalResult_getRaw(haxorg_ImmBlockCodeEvalResultAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmVec, hstd::ext::ImmVec<org::sem::OrgCodeEvalOutput>(*)() const>(&getRaw, org_context); }

haxorg_ImmAdapter haxorg_ImmAdapterTOfImmBlockCodeEvalResult_getNode(haxorg_ImmBlockCodeEvalResultAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmAdapter, org::imm::ImmAdapter(*)() const>(&getNode, org_context); }

void haxorg_destroy_ImmBlockCodeEvalResultAdapter(haxorg_ImmBlockCodeEvalResultAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmBlockCode_ImmAdapterT(haxorg_ImmBlockCodeAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmBlockCode_getLang(haxorg_ImmBlockCodeAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<hstd::Str> const&(*)() const>(&getLang, org_context); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmBlockCode_getResult(haxorg_ImmBlockCodeAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmVec, hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>>(*)() const>(&getResult, org_context); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmBlockCode_getLines(haxorg_ImmBlockCodeAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmVec, hstd::ext::ImmVec<org::sem::BlockCodeLine>(*)() const>(&getLines, org_context); }

haxorg_AttrGroup haxorg_ImmAdapterTOfImmBlockCode_getSwitches(haxorg_ImmBlockCodeAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_AttrGroup, org::sem::AttrGroup(*)() const>(&getSwitches, org_context); }

void haxorg_destroy_ImmBlockCodeAdapter(haxorg_ImmBlockCodeAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmTable_ImmAdapterT(haxorg_ImmTableAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmTable_getRows(haxorg_ImmTableAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmVec, hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmRow>>(*)() const>(&getRows, org_context); }

bool haxorg_ImmAdapterTOfImmTable_getIsBlock(haxorg_ImmTableAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<bool, bool(*)() const>(&getIsBlock, org_context); }

void haxorg_destroy_ImmTableAdapter(haxorg_ImmTableAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmCmdCaption_ImmAdapterT(haxorg_ImmCmdCaptionAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_ImmAdapter haxorg_ImmAdapterTOfImmCmdCaption_getText(haxorg_ImmCmdCaptionAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmAdapter, org::imm::ImmAdapter(*)() const>(&getText, org_context); }

void haxorg_destroy_ImmCmdCaptionAdapter(haxorg_ImmCmdCaptionAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmCmdColumns_ImmAdapterT(haxorg_ImmCmdColumnsAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_ColumnView haxorg_ImmAdapterTOfImmCmdColumns_getView(haxorg_ImmCmdColumnsAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ColumnView, org::sem::ColumnView(*)() const>(&getView, org_context); }

void haxorg_destroy_ImmCmdColumnsAdapter(haxorg_ImmCmdColumnsAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmCmdName_ImmAdapterT(haxorg_ImmCmdNameAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdName_getName(haxorg_ImmCmdNameAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str const&(*)() const>(&getName, org_context); }

void haxorg_destroy_ImmCmdNameAdapter(haxorg_ImmCmdNameAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmCmdCall_ImmAdapterT(haxorg_ImmCmdCallAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdCall_getName(haxorg_ImmCmdCallAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str const&(*)() const>(&getName, org_context); }

haxorg_HstdOpt haxorg_ImmAdapterTOfImmCmdCall_getFileName(haxorg_ImmCmdCallAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdOpt, hstd::Opt<hstd::Str> const&(*)() const>(&getFileName, org_context); }

haxorg_AttrGroup haxorg_ImmAdapterTOfImmCmdCall_getInsideHeaderAttrs(haxorg_ImmCmdCallAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_AttrGroup, org::sem::AttrGroup(*)() const>(&getInsideHeaderAttrs, org_context); }

haxorg_AttrGroup haxorg_ImmAdapterTOfImmCmdCall_getCallAttrs(haxorg_ImmCmdCallAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_AttrGroup, org::sem::AttrGroup(*)() const>(&getCallAttrs, org_context); }

haxorg_AttrGroup haxorg_ImmAdapterTOfImmCmdCall_getEndHeaderAttrs(haxorg_ImmCmdCallAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_AttrGroup, org::sem::AttrGroup(*)() const>(&getEndHeaderAttrs, org_context); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmCmdCall_getResult(haxorg_ImmCmdCallAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmVec, hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>>(*)() const>(&getResult, org_context); }

void haxorg_destroy_ImmCmdCallAdapter(haxorg_ImmCmdCallAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

void haxorg_ImmAdapterTOfImmCmdAttr_ImmAdapterT(haxorg_ImmCmdAttrAdapter __this, haxorg_ImmAdapter other, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::imm::ImmAdapter const&), haxorg_ImmAdapter>(&ImmAdapterT, org_context, other); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdAttr_getTarget(haxorg_ImmCmdAttrAdapter __this, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdStr, hstd::Str const&(*)() const>(&getTarget, org_context); }

void haxorg_destroy_ImmCmdAttrAdapter(haxorg_ImmCmdAttrAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT>(obj); }

haxorg_SemId haxorg_newSemTimeStatic(haxorg_UserTimeBreakdown breakdown, bool isActive, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SemId, org::sem::SemId<org::sem::Time>(*)(hstd::UserTimeBreakdown const&, bool), haxorg_UserTimeBreakdown, bool>(&org::newSemTimeStatic, org_context, breakdown, isActive); }

haxorg_ImmAstContext haxorg_initImmutableAstContext(OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmAstContext, std::shared_ptr<org::imm::ImmAstContext>(*)()>(&org::initImmutableAstContext, org_context); }

haxorg_SemId haxorg_asOneNode(haxorg_SemId arg, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SemId, org::sem::SemId<org::sem::Org>(*)(org::sem::SemId<org::sem::Org> const&), haxorg_SemId>(&org::asOneNode, org_context, arg); }

haxorg_StdString haxorg_formatToString(haxorg_SemId arg, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_StdString, std::string(*)(org::sem::SemId<org::sem::Org>), haxorg_SemId>(&org::formatToString, org_context, arg); }

haxorg_StdString haxorg_exportToYamlString(haxorg_SemId node, haxorg_OrgYamlExportOpts opts, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_StdString, std::string(*)(org::sem::SemId<org::sem::Org> const&, org::OrgYamlExportOpts const&), haxorg_SemId, haxorg_OrgYamlExportOpts>(&org::exportToYamlString, org_context, node, opts); }

void haxorg_exportToYamlFile(haxorg_SemId node, haxorg_StdString path, haxorg_OrgYamlExportOpts opts, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::sem::SemId<org::sem::Org> const&, std::string, org::OrgYamlExportOpts const&), haxorg_SemId, haxorg_StdString, haxorg_OrgYamlExportOpts>(&org::exportToYamlFile, org_context, node, path, opts); }

haxorg_StdString haxorg_exportToJsonString(haxorg_SemId node, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_StdString, std::string(*)(org::sem::SemId<org::sem::Org> const&), haxorg_SemId>(&org::exportToJsonString, org_context, node); }

void haxorg_exportToJsonFile(haxorg_SemId node, haxorg_StdString path, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::sem::SemId<org::sem::Org> const&, std::string), haxorg_SemId, haxorg_StdString>(&org::exportToJsonFile, org_context, node, path); }

haxorg_SemId haxorg_readProtobufFile(haxorg_StdString file, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SemId, org::sem::SemId<org::sem::Document>(*)(std::string const&), haxorg_StdString>(&org::readProtobufFile, org_context, file); }

void haxorg_exportToProtobufFile(haxorg_SemId doc, haxorg_StdString file, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::sem::SemId<org::sem::Document>, std::string const&), haxorg_SemId, haxorg_StdString>(&org::exportToProtobufFile, org_context, doc, file); }

haxorg_StdString haxorg_exportToTreeString(haxorg_SemId node, haxorg_OrgTreeExportOpts opts, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_StdString, std::string(*)(org::sem::SemId<org::sem::Org> const&, org::OrgTreeExportOpts const&), haxorg_SemId, haxorg_OrgTreeExportOpts>(&org::exportToTreeString, org_context, node, opts); }

void haxorg_exportToTreeFile(haxorg_SemId node, haxorg_StdString path, haxorg_OrgTreeExportOpts opts, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(org::sem::SemId<org::sem::Org> const&, std::string, org::OrgTreeExportOpts const&), haxorg_SemId, haxorg_StdString, haxorg_OrgTreeExportOpts>(&org::exportToTreeFile, org_context, node, path, opts); }

haxorg_AstTrackingMap haxorg_getAstTrackingMap(haxorg_HstdVec nodes, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_AstTrackingMap, org::AstTrackingMap(*)(hstd::Vec<org::sem::SemId<org::sem::Org>> const&), haxorg_HstdVec>(&org::getAstTrackingMap, org_context, nodes); }

haxorg_HstdVec haxorg_getSubnodeGroups(haxorg_SemId node, haxorg_AstTrackingMap map, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<org::AstTrackingGroup>(*)(org::sem::SemId<org::sem::Org>, org::AstTrackingMap const&), haxorg_SemId, haxorg_AstTrackingMap>(&org::getSubnodeGroups, org_context, node, map); }

haxorg_HstdVec haxorg_annotateSequence(haxorg_HstdVec groups, int first, int last, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_HstdVec, hstd::Vec<hstd::SequenceAnnotation>(*)(hstd::Vec<hstd::SequenceSegmentGroup> const&, int, int), haxorg_HstdVec, int, int>(&hstd::annotateSequence, org_context, groups, first, last); }

haxorg_GraphMapGraphState haxorg_initMapGraphState(haxorg_ImmAstContext ast, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_GraphMapGraphState, std::shared_ptr<org::graph::MapGraphState>(*)(std::shared_ptr<org::imm::ImmAstContext>), haxorg_ImmAstContext>(&org::graph::initMapGraphState, org_context, ast); }

haxorg_StdString haxorg_serializeAstContextToText(haxorg_ImmAstContext store, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_StdString, std::string(*)(std::shared_ptr<org::imm::ImmAstContext> const&), haxorg_ImmAstContext>(&org::imm::serializeToText, org_context, store); }

void haxorg_serializeAstContextFromText(haxorg_StdString binary, haxorg_ImmAstContext store, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(std::string const&, std::shared_ptr<org::imm::ImmAstContext> const&), haxorg_StdString, haxorg_ImmAstContext>(&org::imm::serializeFromText, org_context, binary, store); }

haxorg_StdString haxorg_serializeAstEpochToText(haxorg_ImmAstReplaceEpoch store, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_StdString, std::string(*)(std::shared_ptr<org::imm::ImmAstReplaceEpoch> const&), haxorg_ImmAstReplaceEpoch>(&org::imm::serializeToText, org_context, store); }

void haxorg_serializeAstEpochFromText(haxorg_StdString binary, haxorg_ImmAstReplaceEpoch store, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(std::string const&, std::shared_ptr<org::imm::ImmAstReplaceEpoch> const&), haxorg_StdString, haxorg_ImmAstReplaceEpoch>(&org::imm::serializeFromText, org_context, binary, store); }

haxorg_StdString haxorg_serializeMapGraphToText(haxorg_GraphMapGraph store, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_StdString, std::string(*)(std::shared_ptr<org::graph::MapGraph> const&), haxorg_GraphMapGraph>(&org::imm::serializeToText, org_context, store); }

void haxorg_serializeMapGraphFromText(haxorg_StdString binary, haxorg_GraphMapGraph store, OrgContext* org_context) { return org::bind::c::execute_cpp<void, void(*)(std::string const&, std::shared_ptr<org::graph::MapGraph> const&), haxorg_StdString, haxorg_GraphMapGraph>(&org::imm::serializeFromText, org_context, binary, store); }

haxorg_StdString haxorg_serializeFromTextToTreeDump(haxorg_StdString binary, OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_StdString, std::string(*)(std::string const&), haxorg_StdString>(&org::imm::serializeFromTextToTreeDump, org_context, binary); }

/* clang-format on */
