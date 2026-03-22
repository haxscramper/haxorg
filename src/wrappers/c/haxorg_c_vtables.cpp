/* clang-format off */
#include <wrappers/c/haxorg_c.h>
#include <wrappers/c/haxorg_c_utils.hpp>
#include <wrappers/c/haxorg_c_vtables.hpp>
#include <wrappers/c/haxorg_c_vtables_manual.hpp>
haxorg_UserTimeBreakdown org::bind::c::VTable<haxorg_UserTime, haxorg_UserTime_vtable>::getBreakdown_const(haxorg_UserTime self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_UserTime, haxorg_UserTime_vtable>(static_cast<hstd::UserTimeBreakdown(*)() const>(&getBreakdown), self, org_context)
}
haxorg_StdString org::bind::c::VTable<haxorg_UserTime, haxorg_UserTime_vtable>::format_const(haxorg_UserTime self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_UserTime, haxorg_UserTime_vtable>(static_cast<std::string(*)() const>(&format), self, org_context)
}
int64_t org::bind::c::VTable<haxorg_UserTime, haxorg_UserTime_vtable>::getTimeDeltaSeconds_const(haxorg_UserTime self, OrgContext* org_context, haxorg_UserTime other) {
  org::bind::c::execute_cpp<haxorg_UserTime, haxorg_UserTime_vtable>(static_cast<int64_t(*)(hstd::UserTime const&) const>(&getTimeDeltaSeconds), self, org_context, other)
}
int64_t org::bind::c::VTable<haxorg_UserTime, haxorg_UserTime_vtable>::toUnixTimestamp_const(haxorg_UserTime self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_UserTime, haxorg_UserTime_vtable>(static_cast<int64_t(*)() const>(&toUnixTimestamp), self, org_context)
}
haxorg_StdString org::bind::c::VTable<haxorg_ParseSourceManager, haxorg_ParseSourceManager_vtable>::getPath_const(haxorg_ParseSourceManager self, OrgContext* org_context, haxorg_ParseSourceFileId id) {
  org::bind::c::execute_cpp<haxorg_ParseSourceManager, haxorg_ParseSourceManager_vtable>(static_cast<std::string(*)(org::parse::SourceFileId const&) const>(&getPath), self, org_context, id)
}
haxorg_ParseSourceFileId org::bind::c::VTable<haxorg_ParseSourceManager, haxorg_ParseSourceManager_vtable>::getId_const(haxorg_ParseSourceManager self, OrgContext* org_context, haxorg_StdString path) {
  org::bind::c::execute_cpp<haxorg_ParseSourceManager, haxorg_ParseSourceManager_vtable>(static_cast<org::parse::SourceFileId(*)(std::string const&) const>(&getId), self, org_context, path)
}
haxorg_StdString org::bind::c::VTable<haxorg_ParseSourceManager, haxorg_ParseSourceManager_vtable>::getSourceContent_const(haxorg_ParseSourceManager self, OrgContext* org_context, haxorg_ParseSourceFileId id) {
  org::bind::c::execute_cpp<haxorg_ParseSourceManager, haxorg_ParseSourceManager_vtable>(static_cast<std::string const&(*)(org::parse::SourceFileId const&) const>(&getSourceContent), self, org_context, id)
}
haxorg_StdString org::bind::c::VTable<haxorg_ParseSourceManager, haxorg_ParseSourceManager_vtable>::getContentTextForPath_const(haxorg_ParseSourceManager self, OrgContext* org_context, haxorg_StdString path) {
  org::bind::c::execute_cpp<haxorg_ParseSourceManager, haxorg_ParseSourceManager_vtable>(static_cast<std::string const&(*)(std::string const&) const>(&getContentTextForPath), self, org_context, path)
}
haxorg_ParseSourceFileId org::bind::c::VTable<haxorg_ParseSourceManager, haxorg_ParseSourceManager_vtable>::addSource(haxorg_ParseSourceManager self, OrgContext* org_context, haxorg_StdString path, haxorg_StdString content) {
  org::bind::c::execute_cpp<haxorg_ParseSourceManager, haxorg_ParseSourceManager_vtable>(static_cast<org::parse::SourceFileId(*)(std::string const&, std::string const&)>(&addSource), self, org_context, path, content)
}
haxorg_OrgJsonKind org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::getKind_const(haxorg_OrgJson self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_OrgJson, haxorg_OrgJson_vtable>(static_cast<OrgJsonKind(*)() const>(&getKind), self, org_context)
}
haxorg_StdString org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::getJsonString_const(haxorg_OrgJson self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_OrgJson, haxorg_OrgJson_vtable>(static_cast<std::string(*)() const>(&getJsonString), self, org_context)
}
haxorg_OrgJson org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::atIndex_const(haxorg_OrgJson self, OrgContext* org_context, int idx) {
  org::bind::c::execute_cpp<haxorg_OrgJson, haxorg_OrgJson_vtable>(static_cast<org::sem::OrgJson(*)(int) const>(&at), self, org_context, idx)
}
haxorg_OrgJson org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::atField_const(haxorg_OrgJson self, OrgContext* org_context, haxorg_StdString name) {
  org::bind::c::execute_cpp<haxorg_OrgJson, haxorg_OrgJson_vtable>(static_cast<org::sem::OrgJson(*)(std::string const&) const>(&at), self, org_context, name)
}
haxorg_StdString org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::getString_const(haxorg_OrgJson self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_OrgJson, haxorg_OrgJson_vtable>(static_cast<std::string(*)() const>(&getString), self, org_context)
}
haxorg_OrgJson org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::getField_const(haxorg_OrgJson self, OrgContext* org_context, haxorg_StdString name) {
  org::bind::c::execute_cpp<haxorg_OrgJson, haxorg_OrgJson_vtable>(static_cast<org::sem::OrgJson(*)(std::string const&) const>(&getField), self, org_context, name)
}
haxorg_OrgJson org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::getItem_const(haxorg_OrgJson self, OrgContext* org_context, int index) {
  org::bind::c::execute_cpp<haxorg_OrgJson, haxorg_OrgJson_vtable>(static_cast<org::sem::OrgJson(*)(int) const>(&getItem), self, org_context, index)
}
int org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::getInt_const(haxorg_OrgJson self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_OrgJson, haxorg_OrgJson_vtable>(static_cast<int(*)() const>(&getInt), self, org_context)
}
bool org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::getBool_const(haxorg_OrgJson self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_OrgJson, haxorg_OrgJson_vtable>(static_cast<bool(*)() const>(&getBool), self, org_context)
}
haxorg_HstdVec org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::getArray_const(haxorg_OrgJson self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_OrgJson, haxorg_OrgJson_vtable>(static_cast<hstd::Vec<org::sem::OrgJson>(*)() const>(&getArray), self, org_context)
}
haxorg_StdString org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::dump_const(haxorg_OrgJson self, OrgContext* org_context, int indent) {
  org::bind::c::execute_cpp<haxorg_OrgJson, haxorg_OrgJson_vtable>(static_cast<std::string(*)(int) const>(&dump), self, org_context, indent)
}
haxorg_OrgSemKind org::bind::c::VTable<haxorg_Org, haxorg_Org_vtable>::getKind_const(haxorg_Org self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Org, haxorg_Org_vtable>(static_cast<OrgSemKind(*)() const>(&getKind), self, org_context)
}
void org::bind::c::VTable<haxorg_Org, haxorg_Org_vtable>::push_back(haxorg_Org self, OrgContext* org_context, haxorg_SemId sub) {
  org::bind::c::execute_cpp<haxorg_Org, haxorg_Org_vtable>(static_cast<void(*)(org::sem::SemId<org::sem::Org>)>(&push_back), self, org_context, sub)
}
int org::bind::c::VTable<haxorg_Org, haxorg_Org_vtable>::size_const(haxorg_Org self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Org, haxorg_Org_vtable>(static_cast<int(*)() const>(&size), self, org_context)
}
void org::bind::c::VTable<haxorg_Org, haxorg_Org_vtable>::insert(haxorg_Org self, OrgContext* org_context, int pos, haxorg_SemId node) {
  org::bind::c::execute_cpp<haxorg_Org, haxorg_Org_vtable>(static_cast<void(*)(int, org::sem::SemId<org::sem::Org>)>(&insert), self, org_context, pos, node)
}
haxorg_SemId org::bind::c::VTable<haxorg_Org, haxorg_Org_vtable>::at_const(haxorg_Org self, OrgContext* org_context, int idx) {
  org::bind::c::execute_cpp<haxorg_Org, haxorg_Org_vtable>(static_cast<org::sem::SemId<org::sem::Org>(*)(int) const>(&at), self, org_context, idx)
}
bool org::bind::c::VTable<haxorg_Org, haxorg_Org_vtable>::is_const(haxorg_Org self, OrgContext* org_context, haxorg_OrgSemKind kind) {
  org::bind::c::execute_cpp<haxorg_Org, haxorg_Org_vtable>(static_cast<bool(*)(OrgSemKind) const>(&is), self, org_context, kind)
}
void org::bind::c::VTable<haxorg_OperationsTracer, haxorg_OperationsTracer_vtable>::setTraceFileStr(haxorg_OperationsTracer self, OrgContext* org_context, haxorg_StdString outfile, bool overwrite) {
  org::bind::c::execute_cpp<haxorg_OperationsTracer, haxorg_OperationsTracer_vtable>(static_cast<void(*)(std::string const&, bool)>(&setTraceFileStr), self, org_context, outfile, overwrite)
}
void org::bind::c::VTable<haxorg_OperationsTracer, haxorg_OperationsTracer_vtable>::sendMessage(haxorg_OperationsTracer self, OrgContext* org_context, haxorg_StdString value, haxorg_StdString function, int line, haxorg_StdString file) {
  org::bind::c::execute_cpp<haxorg_OperationsTracer, haxorg_OperationsTracer_vtable>(static_cast<void(*)(std::string const&, std::string const&, int, std::string const&)>(&sendMessage), self, org_context, value, function, line, file)
}
haxorg_Cache org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::getDiagnosticStrings(haxorg_ParseContext self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ParseContext, haxorg_ParseContext_vtable>(static_cast<std::shared_ptr<hstd::ext::Cache>(*)()>(&getDiagnosticStrings), self, org_context)
}
haxorg_ParseSourceFileId org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::addSource_const(haxorg_ParseContext self, OrgContext* org_context, haxorg_StdString path, haxorg_StdString content) {
  org::bind::c::execute_cpp<haxorg_ParseContext, haxorg_ParseContext_vtable>(static_cast<org::parse::SourceFileId(*)(std::string const&, std::string const&) const>(&addSource), self, org_context, path, content)
}
haxorg_SemId org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::parseFileOpts(haxorg_ParseContext self, OrgContext* org_context, haxorg_StdString file, haxorg_OrgParseParameters opts) {
  org::bind::c::execute_cpp<haxorg_ParseContext, haxorg_ParseContext_vtable>(static_cast<org::sem::SemId<org::sem::Org>(*)(std::string const&, std::shared_ptr<org::parse::OrgParseParameters> const&)>(&parseFileOpts), self, org_context, file, opts)
}
haxorg_SemId org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::parseFile(haxorg_ParseContext self, OrgContext* org_context, haxorg_StdString file) {
  org::bind::c::execute_cpp<haxorg_ParseContext, haxorg_ParseContext_vtable>(static_cast<org::sem::SemId<org::sem::Org>(*)(std::string const&)>(&parseFile), self, org_context, file)
}
haxorg_SemId org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::parseString(haxorg_ParseContext self, OrgContext* org_context, haxorg_StdString text, haxorg_StdString file_name) {
  org::bind::c::execute_cpp<haxorg_ParseContext, haxorg_ParseContext_vtable>(static_cast<org::sem::SemId<org::sem::Org>(*)(std::string const&, std::string const&)>(&parseString), self, org_context, text, file_name)
}
haxorg_SemId org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::parseStringOpts(haxorg_ParseContext self, OrgContext* org_context, haxorg_StdString text, haxorg_StdString file_name, haxorg_OrgParseParameters opts) {
  org::bind::c::execute_cpp<haxorg_ParseContext, haxorg_ParseContext_vtable>(static_cast<org::sem::SemId<org::sem::Org>(*)(std::string const, std::string const&, std::shared_ptr<org::parse::OrgParseParameters> const&)>(&parseStringOpts), self, org_context, text, file_name, opts)
}
haxorg_StdOptional org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::parseDirectory(haxorg_ParseContext self, OrgContext* org_context, haxorg_StdString path) {
  org::bind::c::execute_cpp<haxorg_ParseContext, haxorg_ParseContext_vtable>(static_cast<std::optional<org::sem::SemId<org::sem::Org>>(*)(std::string const&)>(&parseDirectory), self, org_context, path)
}
haxorg_StdOptional org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::parseDirectoryOpts(haxorg_ParseContext self, OrgContext* org_context, haxorg_StdString path, haxorg_OrgDirectoryParseParameters opts) {
  org::bind::c::execute_cpp<haxorg_ParseContext, haxorg_ParseContext_vtable>(static_cast<std::optional<org::sem::SemId<org::sem::Org>>(*)(std::string const&, std::shared_ptr<org::parse::OrgDirectoryParseParameters> const&)>(&parseDirectoryOpts), self, org_context, path, opts)
}
haxorg_SemId org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::parseFileWithIncludes(haxorg_ParseContext self, OrgContext* org_context, haxorg_StdString file, haxorg_OrgDirectoryParseParameters opts) {
  org::bind::c::execute_cpp<haxorg_ParseContext, haxorg_ParseContext_vtable>(static_cast<org::sem::SemId<org::sem::File>(*)(std::string const&, std::shared_ptr<org::parse::OrgDirectoryParseParameters> const&)>(&parseFileWithIncludes), self, org_context, file, opts)
}
haxorg_HstdVec org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::collectDiagnostics(haxorg_ParseContext self, OrgContext* org_context, haxorg_SemId tree, haxorg_Cache cache) {
  org::bind::c::execute_cpp<haxorg_ParseContext, haxorg_ParseContext_vtable>(static_cast<hstd::Vec<hstd::ext::Report>(*)(org::sem::SemId<org::sem::Org> const&, std::shared_ptr<hstd::ext::Cache> const&)>(&collectDiagnostics), self, org_context, tree, cache)
}
haxorg_HstdVec org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::collectErrorNodes(haxorg_ParseContext self, OrgContext* org_context, haxorg_SemId tree) {
  org::bind::c::execute_cpp<haxorg_ParseContext, haxorg_ParseContext_vtable>(static_cast<hstd::Vec<org::sem::SemId<org::sem::ErrorGroup>>(*)(org::sem::SemId<org::sem::Org> const&)>(&collectErrorNodes), self, org_context, tree)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmReflFieldId, haxorg_ImmReflFieldId_vtable>::getName_const(haxorg_ImmReflFieldId self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmReflFieldId, haxorg_ImmReflFieldId_vtable>(static_cast<hstd::Str(*)() const>(&getName), self, org_context)
}
haxorg_OrgSemKind org::bind::c::VTable<haxorg_ImmId, haxorg_ImmId_vtable>::getKind_const(haxorg_ImmId self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmId, haxorg_ImmId_vtable>(static_cast<OrgSemKind(*)() const>(&getKind), self, org_context)
}
bool org::bind::c::VTable<haxorg_ImmId, haxorg_ImmId_vtable>::is_const(haxorg_ImmId self, OrgContext* org_context, haxorg_OrgSemKind kind) {
  org::bind::c::execute_cpp<haxorg_ImmId, haxorg_ImmId_vtable>(static_cast<bool(*)(OrgSemKind) const>(&is), self, org_context, kind)
}
haxorg_ImmIdNodeIdxT org::bind::c::VTable<haxorg_ImmId, haxorg_ImmId_vtable>::getNodeIndex_const(haxorg_ImmId self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmId, haxorg_ImmId_vtable>(static_cast<org::imm::ImmId::NodeIdxT(*)() const>(&getNodeIndex), self, org_context)
}
haxorg_StdString org::bind::c::VTable<haxorg_ImmId, haxorg_ImmId_vtable>::getReadableId_const(haxorg_ImmId self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmId, haxorg_ImmId_vtable>(static_cast<std::string(*)() const>(&getReadableId), self, org_context)
}
bool org::bind::c::VTable<haxorg_ImmPath, haxorg_ImmPath_vtable>::empty_const(haxorg_ImmPath self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmPath, haxorg_ImmPath_vtable>(static_cast<bool(*)() const>(&empty), self, org_context)
}
haxorg_ImmAstVersion org::bind::c::VTable<haxorg_ImmAstContext, haxorg_ImmAstContext_vtable>::addRoot(haxorg_ImmAstContext self, OrgContext* org_context, haxorg_SemId data) {
  org::bind::c::execute_cpp<haxorg_ImmAstContext, haxorg_ImmAstContext_vtable>(static_cast<org::imm::ImmAstVersion(*)(org::sem::SemId<org::sem::Org>)>(&addRoot), self, org_context, data)
}
haxorg_ImmAstVersion org::bind::c::VTable<haxorg_ImmAstContext, haxorg_ImmAstContext_vtable>::getEmptyVersion(haxorg_ImmAstContext self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmAstContext, haxorg_ImmAstContext_vtable>(static_cast<org::imm::ImmAstVersion(*)()>(&getEmptyVersion), self, org_context)
}
haxorg_SemId org::bind::c::VTable<haxorg_ImmAstContext, haxorg_ImmAstContext_vtable>::get(haxorg_ImmAstContext self, OrgContext* org_context, haxorg_ImmId id) {
  org::bind::c::execute_cpp<haxorg_ImmAstContext, haxorg_ImmAstContext_vtable>(static_cast<org::sem::SemId<org::sem::Org>(*)(org::imm::ImmId)>(&get), self, org_context, id)
}
haxorg_ImmId org::bind::c::VTable<haxorg_ImmAstVersion, haxorg_ImmAstVersion_vtable>::getRoot_const(haxorg_ImmAstVersion self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmAstVersion, haxorg_ImmAstVersion_vtable>(static_cast<org::imm::ImmId(*)() const>(&getRoot), self, org_context)
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmAstVersion, haxorg_ImmAstVersion_vtable>::getRootAdapter_const(haxorg_ImmAstVersion self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmAstVersion, haxorg_ImmAstVersion_vtable>(static_cast<org::imm::ImmAdapter(*)() const>(&getRootAdapter), self, org_context)
}
haxorg_ImmAstContext org::bind::c::VTable<haxorg_ImmAstVersion, haxorg_ImmAstVersion_vtable>::getContext_const(haxorg_ImmAstVersion self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmAstVersion, haxorg_ImmAstVersion_vtable>(static_cast<std::shared_ptr<org::imm::ImmAstContext>(*)() const>(&getContext), self, org_context)
}
haxorg_ImmAstReplaceEpoch org::bind::c::VTable<haxorg_ImmAstVersion, haxorg_ImmAstVersion_vtable>::getEpoch_const(haxorg_ImmAstVersion self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmAstVersion, haxorg_ImmAstVersion_vtable>(static_cast<std::shared_ptr<org::imm::ImmAstReplaceEpoch>(*)() const>(&getEpoch), self, org_context)
}
int org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::size_const(haxorg_ImmAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<int(*)() const>(&size), self, org_context)
}
bool org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::isNil_const(haxorg_ImmAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<bool(*)() const>(&isNil), self, org_context)
}
bool org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::isRoot_const(haxorg_ImmAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<bool(*)() const>(&isRoot), self, org_context)
}
haxorg_OrgSemKind org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::getKind_const(haxorg_ImmAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<OrgSemKind(*)() const>(&getKind), self, org_context)
}
haxorg_ImmUniqId org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::uniq_const(haxorg_ImmAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<org::imm::ImmUniqId(*)() const>(&uniq), self, org_context)
}
haxorg_StdString org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::treeReprString_const(haxorg_ImmAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<std::string(*)() const>(&treeReprString), self, org_context)
}
haxorg_StdString org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::treeReprStringOpts_const(haxorg_ImmAdapter self, OrgContext* org_context, haxorg_ImmAdapterTreeReprConf conf) {
  org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<std::string(*)(org::imm::ImmAdapter::TreeReprConf const&) const>(&treeReprStringOpts), self, org_context, conf)
}
bool org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::isDirectParentOf_const(haxorg_ImmAdapter self, OrgContext* org_context, haxorg_ImmAdapter other) {
  org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<bool(*)(org::imm::ImmAdapter const&) const>(&isDirectParentOf), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::isIndirectParentOf_const(haxorg_ImmAdapter self, OrgContext* org_context, haxorg_ImmAdapter other) {
  org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<bool(*)(org::imm::ImmAdapter const&) const>(&isIndirectParentOf), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::isSubnodeOf_const(haxorg_ImmAdapter self, OrgContext* org_context, haxorg_ImmAdapter other) {
  org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<bool(*)(org::imm::ImmAdapter const&) const>(&isSubnodeOf), self, org_context, other)
}
haxorg_StdOptional org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::getParent_const(haxorg_ImmAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<std::optional<org::imm::ImmAdapter>(*)() const>(&getParent), self, org_context)
}
int org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::getSelfIndex_const(haxorg_ImmAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<int(*)() const>(&getSelfIndex), self, org_context)
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::atPathStep_const(haxorg_ImmAdapter self, OrgContext* org_context, haxorg_ImmId id, haxorg_ImmPathStep idx) {
  org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<org::imm::ImmAdapter(*)(org::imm::ImmId, org::imm::ImmPathStep) const>(&at), self, org_context, id, idx)
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::atField_const(haxorg_ImmAdapter self, OrgContext* org_context, haxorg_ImmReflFieldId field) {
  org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<org::imm::ImmAdapter(*)(org::imm::ImmReflFieldId const&) const>(&at), self, org_context, field)
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::atIndex_const(haxorg_ImmAdapter self, OrgContext* org_context, int idx, bool withPath) {
  org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<org::imm::ImmAdapter(*)(int, bool) const>(&at), self, org_context, idx, withPath)
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::atPath_const(haxorg_ImmAdapter self, OrgContext* org_context, haxorg_HstdVec path, bool withPath) {
  org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<org::imm::ImmAdapter(*)(hstd::Vec<int> const&, bool) const>(&at), self, org_context, path, withPath)
}
bool org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::is_const(haxorg_ImmAdapter self, OrgContext* org_context, haxorg_OrgSemKind kind) {
  org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<bool(*)(OrgSemKind) const>(&is), self, org_context, kind)
}
haxorg_HstdVec org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::sub_const(haxorg_ImmAdapter self, OrgContext* org_context, bool withPath) {
  org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<hstd::Vec<org::imm::ImmAdapter>(*)(bool) const>(&sub), self, org_context, withPath)
}
haxorg_SemId org::bind::c::VTable<haxorg_AstTrackingPath, haxorg_AstTrackingPath_vtable>::getParent_const(haxorg_AstTrackingPath self, OrgContext* org_context, int offset) {
  org::bind::c::execute_cpp<haxorg_AstTrackingPath, haxorg_AstTrackingPath_vtable>(static_cast<org::sem::SemId<org::sem::Org>(*)(int) const>(&getParent), self, org_context, offset)
}
haxorg_SemId org::bind::c::VTable<haxorg_AstTrackingPath, haxorg_AstTrackingPath_vtable>::getNode_const(haxorg_AstTrackingPath self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AstTrackingPath, haxorg_AstTrackingPath_vtable>(static_cast<org::sem::SemId<org::sem::Org>(*)() const>(&getNode), self, org_context)
}
haxorg_HstdVec org::bind::c::VTable<haxorg_AstTrackingAlternatives, haxorg_AstTrackingAlternatives_vtable>::getAllNodes_const(haxorg_AstTrackingAlternatives self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AstTrackingAlternatives, haxorg_AstTrackingAlternatives_vtable>(static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(*)() const>(&getAllNodes), self, org_context)
}
haxorg_SemId org::bind::c::VTable<haxorg_AstTrackingAlternatives, haxorg_AstTrackingAlternatives_vtable>::getNode_const(haxorg_AstTrackingAlternatives self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AstTrackingAlternatives, haxorg_AstTrackingAlternatives_vtable>(static_cast<org::sem::SemId<org::sem::Org>(*)() const>(&getNode), self, org_context)
}
haxorg_AstTrackingGroupRadioTarget org::bind::c::VTable<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>::getRadioTargetConst_const(haxorg_AstTrackingGroup self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>(static_cast<org::AstTrackingGroup::RadioTarget const&(*)() const>(&getRadioTarget), self, org_context)
}
haxorg_AstTrackingGroupTrackedHashtag org::bind::c::VTable<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>::getTrackedHashtagConst_const(haxorg_AstTrackingGroup self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>(static_cast<org::AstTrackingGroup::TrackedHashtag const&(*)() const>(&getTrackedHashtag), self, org_context)
}
haxorg_AstTrackingGroupTrackedHashtag org::bind::c::VTable<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>::getTrackedHashtagMut(haxorg_AstTrackingGroup self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>(static_cast<org::AstTrackingGroup::TrackedHashtag&(*)()>(&getTrackedHashtag), self, org_context)
}
haxorg_AstTrackingGroupSingle org::bind::c::VTable<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>::getSingleConst_const(haxorg_AstTrackingGroup self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>(static_cast<org::AstTrackingGroup::Single const&(*)() const>(&getSingle), self, org_context)
}
haxorg_AstTrackingGroupRadioTarget org::bind::c::VTable<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>::getRadioTargetMut(haxorg_AstTrackingGroup self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>(static_cast<org::AstTrackingGroup::RadioTarget&(*)()>(&getRadioTarget), self, org_context)
}
haxorg_AstTrackingGroupSingle org::bind::c::VTable<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>::getSingleMut(haxorg_AstTrackingGroup self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>(static_cast<org::AstTrackingGroup::Single&(*)()>(&getSingle), self, org_context)
}
bool org::bind::c::VTable<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>::isSingle_const(haxorg_AstTrackingGroup self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>(static_cast<bool(*)() const>(&isSingle), self, org_context)
}
bool org::bind::c::VTable<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>::isTrackedHashtag_const(haxorg_AstTrackingGroup self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>(static_cast<bool(*)() const>(&isTrackedHashtag), self, org_context)
}
bool org::bind::c::VTable<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>::isRadioTarget_const(haxorg_AstTrackingGroup self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>(static_cast<bool(*)() const>(&isRadioTarget), self, org_context)
}
haxorg_StdOptional org::bind::c::VTable<haxorg_AstTrackingMap, haxorg_AstTrackingMap_vtable>::getIdPath_const(haxorg_AstTrackingMap self, OrgContext* org_context, haxorg_HstdStr id) {
  org::bind::c::execute_cpp<haxorg_AstTrackingMap, haxorg_AstTrackingMap_vtable>(static_cast<std::optional<org::AstTrackingAlternatives>(*)(hstd::Str const&) const>(&getIdPath), self, org_context, id)
}
haxorg_StdOptional org::bind::c::VTable<haxorg_AstTrackingMap, haxorg_AstTrackingMap_vtable>::getNamePath_const(haxorg_AstTrackingMap self, OrgContext* org_context, haxorg_HstdStr id) {
  org::bind::c::execute_cpp<haxorg_AstTrackingMap, haxorg_AstTrackingMap_vtable>(static_cast<std::optional<org::AstTrackingAlternatives>(*)(hstd::Str const&) const>(&getNamePath), self, org_context, id)
}
haxorg_StdOptional org::bind::c::VTable<haxorg_AstTrackingMap, haxorg_AstTrackingMap_vtable>::getAnchorTarget_const(haxorg_AstTrackingMap self, OrgContext* org_context, haxorg_HstdStr id) {
  org::bind::c::execute_cpp<haxorg_AstTrackingMap, haxorg_AstTrackingMap_vtable>(static_cast<std::optional<org::AstTrackingAlternatives>(*)(hstd::Str const&) const>(&getAnchorTarget), self, org_context, id)
}
haxorg_StdOptional org::bind::c::VTable<haxorg_AstTrackingMap, haxorg_AstTrackingMap_vtable>::getFootnotePath_const(haxorg_AstTrackingMap self, OrgContext* org_context, haxorg_HstdStr id) {
  org::bind::c::execute_cpp<haxorg_AstTrackingMap, haxorg_AstTrackingMap_vtable>(static_cast<std::optional<org::AstTrackingAlternatives>(*)(hstd::Str const&) const>(&getFootnotePath), self, org_context, id)
}
bool org::bind::c::VTable<haxorg_SequenceAnnotation, haxorg_SequenceAnnotation_vtable>::isAnnotatedWith_const(haxorg_SequenceAnnotation self, OrgContext* org_context, int groupKind, int segmentKind) {
  org::bind::c::execute_cpp<haxorg_SequenceAnnotation, haxorg_SequenceAnnotation_vtable>(static_cast<bool(*)(int, int) const>(&isAnnotatedWith), self, org_context, groupKind, segmentKind)
}
haxorg_GraphMapLinkRadio org::bind::c::VTable<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>::getRadio(haxorg_GraphMapLink self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>(static_cast<org::graph::MapLink::Radio&(*)()>(&getRadio), self, org_context)
}
haxorg_GraphMapLinkRadio org::bind::c::VTable<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>::getRadio_const(haxorg_GraphMapLink self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>(static_cast<org::graph::MapLink::Radio const&(*)() const>(&getRadio), self, org_context)
}
bool org::bind::c::VTable<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>::isRadio_const(haxorg_GraphMapLink self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>(static_cast<bool(*)() const>(&isRadio), self, org_context)
}
haxorg_GraphMapLinkLink org::bind::c::VTable<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>::getLink(haxorg_GraphMapLink self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>(static_cast<org::graph::MapLink::Link&(*)()>(&getLink), self, org_context)
}
haxorg_GraphMapLinkLink org::bind::c::VTable<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>::getLink_const(haxorg_GraphMapLink self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>(static_cast<org::graph::MapLink::Link const&(*)() const>(&getLink), self, org_context)
}
bool org::bind::c::VTable<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>::isLink_const(haxorg_GraphMapLink self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>(static_cast<bool(*)() const>(&isLink), self, org_context)
}
haxorg_GraphMapLinkKind org::bind::c::VTable<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>::getKind_const(haxorg_GraphMapLink self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>(static_cast<org::graph::MapLink::Kind(*)() const>(&getKind), self, org_context)
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_GraphMapNodeProp, haxorg_GraphMapNodeProp_vtable>::getAdapter_const(haxorg_GraphMapNodeProp self, OrgContext* org_context, haxorg_ImmAstContext context) {
  org::bind::c::execute_cpp<haxorg_GraphMapNodeProp, haxorg_GraphMapNodeProp_vtable>(static_cast<org::imm::ImmAdapter(*)(std::shared_ptr<org::imm::ImmAstContext> const&) const>(&getAdapter), self, org_context, context)
}
haxorg_StdOptional org::bind::c::VTable<haxorg_GraphMapNodeProp, haxorg_GraphMapNodeProp_vtable>::getSubtreeId_const(haxorg_GraphMapNodeProp self, OrgContext* org_context, haxorg_ImmAstContext context) {
  org::bind::c::execute_cpp<haxorg_GraphMapNodeProp, haxorg_GraphMapNodeProp_vtable>(static_cast<std::optional<hstd::Str>(*)(std::shared_ptr<org::imm::ImmAstContext> const&) const>(&getSubtreeId), self, org_context, context)
}
haxorg_StdOptional org::bind::c::VTable<haxorg_GraphMapNodeProp, haxorg_GraphMapNodeProp_vtable>::getFootnoteName_const(haxorg_GraphMapNodeProp self, OrgContext* org_context, haxorg_ImmAstContext context) {
  org::bind::c::execute_cpp<haxorg_GraphMapNodeProp, haxorg_GraphMapNodeProp_vtable>(static_cast<std::optional<hstd::Str>(*)(std::shared_ptr<org::imm::ImmAstContext> const&) const>(&getFootnoteName), self, org_context, context)
}
bool org::bind::c::VTable<haxorg_GraphMapNode, haxorg_GraphMapNode_vtable>::__eq___const(haxorg_GraphMapNode self, OrgContext* org_context, haxorg_GraphMapNode other) {
  org::bind::c::execute_cpp<haxorg_GraphMapNode, haxorg_GraphMapNode_vtable>(static_cast<bool(*)(org::graph::MapNode const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_GraphMapNode, haxorg_GraphMapNode_vtable>::__lt___const(haxorg_GraphMapNode self, OrgContext* org_context, haxorg_GraphMapNode other) {
  org::bind::c::execute_cpp<haxorg_GraphMapNode, haxorg_GraphMapNode_vtable>(static_cast<bool(*)(org::graph::MapNode const&) const>(&operator<), self, org_context, other)
}
int org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::nodeCount_const(haxorg_GraphMapGraph self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<int(*)() const>(&nodeCount), self, org_context)
}
int org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::edgeCount_const(haxorg_GraphMapGraph self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<int(*)() const>(&edgeCount), self, org_context)
}
haxorg_GraphAdjNodesList org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::outNodes_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node) {
  org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<org::graph::AdjNodesList const&(*)(org::graph::MapNode const&) const>(&outNodes), self, org_context, node)
}
haxorg_GraphAdjNodesList org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::inNodes_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node) {
  org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<org::graph::AdjNodesList const&(*)(org::graph::MapNode const&) const>(&inNodes), self, org_context, node)
}
haxorg_HstdVec org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::adjEdges_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node) {
  org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<hstd::Vec<org::graph::MapEdge>(*)(org::graph::MapNode const&) const>(&adjEdges), self, org_context, node)
}
haxorg_HstdVec org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::adjNodes_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node) {
  org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<hstd::Vec<org::graph::MapNode>(*)(org::graph::MapNode const&) const>(&adjNodes), self, org_context, node)
}
haxorg_HstdVec org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::outEdges_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node) {
  org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<hstd::Vec<org::graph::MapEdge>(*)(org::graph::MapNode const&) const>(&outEdges), self, org_context, node)
}
haxorg_HstdVec org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::inEdges_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node) {
  org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<hstd::Vec<org::graph::MapEdge>(*)(org::graph::MapNode const&) const>(&inEdges), self, org_context, node)
}
int org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::outDegree_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node) {
  org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<int(*)(org::graph::MapNode const&) const>(&outDegree), self, org_context, node)
}
int org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::inDegree_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node) {
  org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<int(*)(org::graph::MapNode const&) const>(&inDegree), self, org_context, node)
}
bool org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::isRegisteredNode_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode id) {
  org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<bool(*)(org::graph::MapNode const&) const>(&isRegisteredNode), self, org_context, id)
}
bool org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::isRegisteredNodeById_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_ImmUniqId id) {
  org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<bool(*)(org::imm::ImmUniqId const&) const>(&isRegisteredNode), self, org_context, id)
}
haxorg_GraphMapNodeProp org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::atMapNode_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node) {
  org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<org::graph::MapNodeProp const&(*)(org::graph::MapNode const&) const>(&at), self, org_context, node)
}
haxorg_GraphMapEdgeProp org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::atMapEdge_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapEdge edge) {
  org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<org::graph::MapEdgeProp const&(*)(org::graph::MapEdge const&) const>(&at), self, org_context, edge)
}
void org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::addEdge(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapEdge edge) {
  org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<void(*)(org::graph::MapEdge const&)>(&addEdge), self, org_context, edge)
}
void org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::addEdgeWithProp(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapEdge edge, haxorg_GraphMapEdgeProp prop) {
  org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<void(*)(org::graph::MapEdge const&, org::graph::MapEdgeProp const&)>(&addEdge), self, org_context, edge, prop)
}
void org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::addNode(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node) {
  org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<void(*)(org::graph::MapNode const&)>(&addNode), self, org_context, node)
}
void org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::addNodeWithProp(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node, haxorg_GraphMapNodeProp prop) {
  org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<void(*)(org::graph::MapNode const&, org::graph::MapNodeProp const&)>(&addNode), self, org_context, node, prop)
}
bool org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::hasEdge_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode source, haxorg_GraphMapNode target) {
  org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<bool(*)(org::graph::MapNode const&, org::graph::MapNode const&) const>(&hasEdge), self, org_context, source, target)
}
bool org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::hasNode_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node) {
  org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<bool(*)(org::graph::MapNode const&) const>(&hasNode), self, org_context, node)
}
bool org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::has2AdapterEdge_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_ImmAdapter source, haxorg_ImmAdapter target) {
  org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<bool(*)(org::imm::ImmAdapter const&, org::imm::ImmAdapter const&) const>(&hasEdge), self, org_context, source, target)
}
haxorg_GraphMapGraph org::bind::c::VTable<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>::getGraph_const(haxorg_GraphMapGraphState self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>(static_cast<std::shared_ptr<org::graph::MapGraph>(*)() const>(&getGraph), self, org_context)
}
haxorg_GraphMapGraphState org::bind::c::VTable<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>::FromAstContext(haxorg_GraphMapGraphState self, OrgContext* org_context, haxorg_ImmAstContext ast) {
  org::bind::c::execute_cpp<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>(static_cast<std::shared_ptr<org::graph::MapGraphState>(*)(std::shared_ptr<org::imm::ImmAstContext>)>(&FromAstContext), self, org_context, ast)
}
void org::bind::c::VTable<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>::registerNode(haxorg_GraphMapGraphState self, OrgContext* org_context, haxorg_GraphMapNodeProp node, haxorg_GraphMapConfig conf) {
  org::bind::c::execute_cpp<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>(static_cast<void(*)(org::graph::MapNodeProp const&, std::shared_ptr<org::graph::MapConfig> const&)>(&registerNode), self, org_context, node, conf)
}
void org::bind::c::VTable<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>::addNode(haxorg_GraphMapGraphState self, OrgContext* org_context, haxorg_ImmAdapter node, haxorg_GraphMapConfig conf) {
  org::bind::c::execute_cpp<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>(static_cast<void(*)(org::imm::ImmAdapter const&, std::shared_ptr<org::graph::MapConfig> const&)>(&addNode), self, org_context, node, conf)
}
void org::bind::c::VTable<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>::addNodeRec(haxorg_GraphMapGraphState self, OrgContext* org_context, haxorg_ImmAstContext ast, haxorg_ImmAdapter node, haxorg_GraphMapConfig conf) {
  org::bind::c::execute_cpp<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>(static_cast<void(*)(std::shared_ptr<org::imm::ImmAstContext> const&, org::imm::ImmAdapter const&, std::shared_ptr<org::graph::MapConfig> const&)>(&addNodeRec), self, org_context, ast, node, conf)
}
haxorg_HstdVec org::bind::c::VTable<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>::getUnresolvedSubtreeLinks_const(haxorg_GraphMapGraphState self, OrgContext* org_context, haxorg_ImmSubtreeAdapter node, haxorg_GraphMapConfig conf) {
  org::bind::c::execute_cpp<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>(static_cast<hstd::Vec<org::graph::MapLink>(*)(org::imm::ImmAdapterT<org::imm::ImmSubtree>, std::shared_ptr<org::graph::MapConfig> const&) const>(&getUnresolvedSubtreeLinks), self, org_context, node, conf)
}
haxorg_StdOptional org::bind::c::VTable<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>::getUnresolvedLink_const(haxorg_GraphMapGraphState self, OrgContext* org_context, haxorg_ImmLinkAdapter node, haxorg_GraphMapConfig conf) {
  org::bind::c::execute_cpp<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>(static_cast<std::optional<org::graph::MapLink>(*)(org::imm::ImmAdapterT<org::imm::ImmLink>, std::shared_ptr<org::graph::MapConfig> const&) const>(&getUnresolvedLink), self, org_context, node, conf)
}
bool org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::__eq___const(haxorg_LispCode self, OrgContext* org_context, haxorg_LispCode other) {
  org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<bool(*)(org::sem::LispCode const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::isCall_const(haxorg_LispCode self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<bool(*)() const>(&isCall), self, org_context)
}
haxorg_LispCodeCall org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getCallConst_const(haxorg_LispCode self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::Call const&(*)() const>(&getCall), self, org_context)
}
haxorg_LispCodeCall org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getCallMut(haxorg_LispCode self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::Call&(*)()>(&getCall), self, org_context)
}
bool org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::isList_const(haxorg_LispCode self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<bool(*)() const>(&isList), self, org_context)
}
haxorg_LispCodeList org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getListConst_const(haxorg_LispCode self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::List const&(*)() const>(&getList), self, org_context)
}
haxorg_LispCodeList org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getListMut(haxorg_LispCode self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::List&(*)()>(&getList), self, org_context)
}
bool org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::isKeyValue_const(haxorg_LispCode self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<bool(*)() const>(&isKeyValue), self, org_context)
}
haxorg_LispCodeKeyValue org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getKeyValueConst_const(haxorg_LispCode self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::KeyValue const&(*)() const>(&getKeyValue), self, org_context)
}
haxorg_LispCodeKeyValue org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getKeyValueMut(haxorg_LispCode self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::KeyValue&(*)()>(&getKeyValue), self, org_context)
}
bool org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::isNumber_const(haxorg_LispCode self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<bool(*)() const>(&isNumber), self, org_context)
}
haxorg_LispCodeNumber org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getNumberConst_const(haxorg_LispCode self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::Number const&(*)() const>(&getNumber), self, org_context)
}
haxorg_LispCodeNumber org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getNumberMut(haxorg_LispCode self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::Number&(*)()>(&getNumber), self, org_context)
}
bool org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::isText_const(haxorg_LispCode self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<bool(*)() const>(&isText), self, org_context)
}
haxorg_LispCodeText org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getTextConst_const(haxorg_LispCode self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::Text const&(*)() const>(&getText), self, org_context)
}
haxorg_LispCodeText org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getTextMut(haxorg_LispCode self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::Text&(*)()>(&getText), self, org_context)
}
bool org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::isIdent_const(haxorg_LispCode self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<bool(*)() const>(&isIdent), self, org_context)
}
haxorg_LispCodeIdent org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getIdentConst_const(haxorg_LispCode self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::Ident const&(*)() const>(&getIdent), self, org_context)
}
haxorg_LispCodeIdent org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getIdentMut(haxorg_LispCode self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::Ident&(*)()>(&getIdent), self, org_context)
}
bool org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::isBoolean_const(haxorg_LispCode self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<bool(*)() const>(&isBoolean), self, org_context)
}
haxorg_LispCodeBoolean org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getBooleanConst_const(haxorg_LispCode self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::Boolean const&(*)() const>(&getBoolean), self, org_context)
}
haxorg_LispCodeBoolean org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getBooleanMut(haxorg_LispCode self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::Boolean&(*)()>(&getBoolean), self, org_context)
}
bool org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::isReal_const(haxorg_LispCode self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<bool(*)() const>(&isReal), self, org_context)
}
haxorg_LispCodeReal org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getRealConst_const(haxorg_LispCode self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::Real const&(*)() const>(&getReal), self, org_context)
}
haxorg_LispCodeReal org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getRealMut(haxorg_LispCode self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::Real&(*)()>(&getReal), self, org_context)
}
haxorg_LispCodeKind org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getKind_const(haxorg_LispCode self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::Kind(*)() const>(&getKind), self, org_context)
}
bool org::bind::c::VTable<haxorg_LispCodeCall, haxorg_LispCodeCall_vtable>::__eq___const(haxorg_LispCodeCall self, OrgContext* org_context, haxorg_LispCodeCall other) {
  org::bind::c::execute_cpp<haxorg_LispCodeCall, haxorg_LispCodeCall_vtable>(static_cast<bool(*)(org::sem::LispCode::Call const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_LispCodeList, haxorg_LispCodeList_vtable>::__eq___const(haxorg_LispCodeList self, OrgContext* org_context, haxorg_LispCodeList other) {
  org::bind::c::execute_cpp<haxorg_LispCodeList, haxorg_LispCodeList_vtable>(static_cast<bool(*)(org::sem::LispCode::List const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_LispCodeKeyValue, haxorg_LispCodeKeyValue_vtable>::__eq___const(haxorg_LispCodeKeyValue self, OrgContext* org_context, haxorg_LispCodeKeyValue other) {
  org::bind::c::execute_cpp<haxorg_LispCodeKeyValue, haxorg_LispCodeKeyValue_vtable>(static_cast<bool(*)(org::sem::LispCode::KeyValue const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_LispCodeNumber, haxorg_LispCodeNumber_vtable>::__eq___const(haxorg_LispCodeNumber self, OrgContext* org_context, haxorg_LispCodeNumber other) {
  org::bind::c::execute_cpp<haxorg_LispCodeNumber, haxorg_LispCodeNumber_vtable>(static_cast<bool(*)(org::sem::LispCode::Number const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_LispCodeText, haxorg_LispCodeText_vtable>::__eq___const(haxorg_LispCodeText self, OrgContext* org_context, haxorg_LispCodeText other) {
  org::bind::c::execute_cpp<haxorg_LispCodeText, haxorg_LispCodeText_vtable>(static_cast<bool(*)(org::sem::LispCode::Text const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_LispCodeIdent, haxorg_LispCodeIdent_vtable>::__eq___const(haxorg_LispCodeIdent self, OrgContext* org_context, haxorg_LispCodeIdent other) {
  org::bind::c::execute_cpp<haxorg_LispCodeIdent, haxorg_LispCodeIdent_vtable>(static_cast<bool(*)(org::sem::LispCode::Ident const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_LispCodeBoolean, haxorg_LispCodeBoolean_vtable>::__eq___const(haxorg_LispCodeBoolean self, OrgContext* org_context, haxorg_LispCodeBoolean other) {
  org::bind::c::execute_cpp<haxorg_LispCodeBoolean, haxorg_LispCodeBoolean_vtable>(static_cast<bool(*)(org::sem::LispCode::Boolean const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_LispCodeReal, haxorg_LispCodeReal_vtable>::__eq___const(haxorg_LispCodeReal self, OrgContext* org_context, haxorg_LispCodeReal other) {
  org::bind::c::execute_cpp<haxorg_LispCodeReal, haxorg_LispCodeReal_vtable>(static_cast<bool(*)(org::sem::LispCode::Real const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_Tblfm, haxorg_Tblfm_vtable>::__eq___const(haxorg_Tblfm self, OrgContext* org_context, haxorg_Tblfm other) {
  org::bind::c::execute_cpp<haxorg_Tblfm, haxorg_Tblfm_vtable>(static_cast<bool(*)(org::sem::Tblfm const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::__eq___const(haxorg_TblfmExpr self, OrgContext* org_context, haxorg_TblfmExpr other) {
  org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<bool(*)(org::sem::Tblfm::Expr const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::isAxisRef_const(haxorg_TblfmExpr self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<bool(*)() const>(&isAxisRef), self, org_context)
}
haxorg_TblfmExprAxisRef org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getAxisRefConst_const(haxorg_TblfmExpr self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<org::sem::Tblfm::Expr::AxisRef const&(*)() const>(&getAxisRef), self, org_context)
}
haxorg_TblfmExprAxisRef org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getAxisRefMut(haxorg_TblfmExpr self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<org::sem::Tblfm::Expr::AxisRef&(*)()>(&getAxisRef), self, org_context)
}
bool org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::isAxisName_const(haxorg_TblfmExpr self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<bool(*)() const>(&isAxisName), self, org_context)
}
haxorg_TblfmExprAxisName org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getAxisNameConst_const(haxorg_TblfmExpr self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<org::sem::Tblfm::Expr::AxisName const&(*)() const>(&getAxisName), self, org_context)
}
haxorg_TblfmExprAxisName org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getAxisNameMut(haxorg_TblfmExpr self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<org::sem::Tblfm::Expr::AxisName&(*)()>(&getAxisName), self, org_context)
}
bool org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::isIntLiteral_const(haxorg_TblfmExpr self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<bool(*)() const>(&isIntLiteral), self, org_context)
}
haxorg_TblfmExprIntLiteral org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getIntLiteralConst_const(haxorg_TblfmExpr self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<org::sem::Tblfm::Expr::IntLiteral const&(*)() const>(&getIntLiteral), self, org_context)
}
haxorg_TblfmExprIntLiteral org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getIntLiteralMut(haxorg_TblfmExpr self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<org::sem::Tblfm::Expr::IntLiteral&(*)()>(&getIntLiteral), self, org_context)
}
bool org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::isFloatLiteral_const(haxorg_TblfmExpr self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<bool(*)() const>(&isFloatLiteral), self, org_context)
}
haxorg_TblfmExprFloatLiteral org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getFloatLiteralConst_const(haxorg_TblfmExpr self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<org::sem::Tblfm::Expr::FloatLiteral const&(*)() const>(&getFloatLiteral), self, org_context)
}
haxorg_TblfmExprFloatLiteral org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getFloatLiteralMut(haxorg_TblfmExpr self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<org::sem::Tblfm::Expr::FloatLiteral&(*)()>(&getFloatLiteral), self, org_context)
}
bool org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::isRangeRef_const(haxorg_TblfmExpr self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<bool(*)() const>(&isRangeRef), self, org_context)
}
haxorg_TblfmExprRangeRef org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getRangeRefConst_const(haxorg_TblfmExpr self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<org::sem::Tblfm::Expr::RangeRef const&(*)() const>(&getRangeRef), self, org_context)
}
haxorg_TblfmExprRangeRef org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getRangeRefMut(haxorg_TblfmExpr self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<org::sem::Tblfm::Expr::RangeRef&(*)()>(&getRangeRef), self, org_context)
}
bool org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::isCall_const(haxorg_TblfmExpr self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<bool(*)() const>(&isCall), self, org_context)
}
haxorg_TblfmExprCall org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getCallConst_const(haxorg_TblfmExpr self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<org::sem::Tblfm::Expr::Call const&(*)() const>(&getCall), self, org_context)
}
haxorg_TblfmExprCall org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getCallMut(haxorg_TblfmExpr self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<org::sem::Tblfm::Expr::Call&(*)()>(&getCall), self, org_context)
}
bool org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::isElisp_const(haxorg_TblfmExpr self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<bool(*)() const>(&isElisp), self, org_context)
}
haxorg_TblfmExprElisp org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getElispConst_const(haxorg_TblfmExpr self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<org::sem::Tblfm::Expr::Elisp const&(*)() const>(&getElisp), self, org_context)
}
haxorg_TblfmExprElisp org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getElispMut(haxorg_TblfmExpr self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<org::sem::Tblfm::Expr::Elisp&(*)()>(&getElisp), self, org_context)
}
haxorg_TblfmExprKind org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getKind_const(haxorg_TblfmExpr self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<org::sem::Tblfm::Expr::Kind(*)() const>(&getKind), self, org_context)
}
bool org::bind::c::VTable<haxorg_TblfmExprAxisRef, haxorg_TblfmExprAxisRef_vtable>::__eq___const(haxorg_TblfmExprAxisRef self, OrgContext* org_context, haxorg_TblfmExprAxisRef other) {
  org::bind::c::execute_cpp<haxorg_TblfmExprAxisRef, haxorg_TblfmExprAxisRef_vtable>(static_cast<bool(*)(org::sem::Tblfm::Expr::AxisRef const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>::__eq___const(haxorg_TblfmExprAxisRefPosition self, OrgContext* org_context, haxorg_TblfmExprAxisRefPosition other) {
  org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>(static_cast<bool(*)(org::sem::Tblfm::Expr::AxisRef::Position const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>::isIndex_const(haxorg_TblfmExprAxisRefPosition self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>(static_cast<bool(*)() const>(&isIndex), self, org_context)
}
haxorg_TblfmExprAxisRefPositionIndex org::bind::c::VTable<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>::getIndexConst_const(haxorg_TblfmExprAxisRefPosition self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>(static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Index const&(*)() const>(&getIndex), self, org_context)
}
haxorg_TblfmExprAxisRefPositionIndex org::bind::c::VTable<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>::getIndexMut(haxorg_TblfmExprAxisRefPosition self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>(static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Index&(*)()>(&getIndex), self, org_context)
}
bool org::bind::c::VTable<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>::isName_const(haxorg_TblfmExprAxisRefPosition self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>(static_cast<bool(*)() const>(&isName), self, org_context)
}
haxorg_TblfmExprAxisRefPositionName org::bind::c::VTable<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>::getNameConst_const(haxorg_TblfmExprAxisRefPosition self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>(static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Name const&(*)() const>(&getName), self, org_context)
}
haxorg_TblfmExprAxisRefPositionName org::bind::c::VTable<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>::getNameMut(haxorg_TblfmExprAxisRefPosition self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>(static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Name&(*)()>(&getName), self, org_context)
}
haxorg_TblfmExprAxisRefPositionKind org::bind::c::VTable<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>::getKind_const(haxorg_TblfmExprAxisRefPosition self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>(static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Kind(*)() const>(&getKind), self, org_context)
}
bool org::bind::c::VTable<haxorg_TblfmExprAxisRefPositionIndex, haxorg_TblfmExprAxisRefPositionIndex_vtable>::__eq___const(haxorg_TblfmExprAxisRefPositionIndex self, OrgContext* org_context, haxorg_TblfmExprAxisRefPositionIndex other) {
  org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPositionIndex, haxorg_TblfmExprAxisRefPositionIndex_vtable>(static_cast<bool(*)(org::sem::Tblfm::Expr::AxisRef::Position::Index const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_TblfmExprAxisRefPositionName, haxorg_TblfmExprAxisRefPositionName_vtable>::__eq___const(haxorg_TblfmExprAxisRefPositionName self, OrgContext* org_context, haxorg_TblfmExprAxisRefPositionName other) {
  org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPositionName, haxorg_TblfmExprAxisRefPositionName_vtable>(static_cast<bool(*)(org::sem::Tblfm::Expr::AxisRef::Position::Name const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_TblfmExprAxisName, haxorg_TblfmExprAxisName_vtable>::__eq___const(haxorg_TblfmExprAxisName self, OrgContext* org_context, haxorg_TblfmExprAxisName other) {
  org::bind::c::execute_cpp<haxorg_TblfmExprAxisName, haxorg_TblfmExprAxisName_vtable>(static_cast<bool(*)(org::sem::Tblfm::Expr::AxisName const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_TblfmExprIntLiteral, haxorg_TblfmExprIntLiteral_vtable>::__eq___const(haxorg_TblfmExprIntLiteral self, OrgContext* org_context, haxorg_TblfmExprIntLiteral other) {
  org::bind::c::execute_cpp<haxorg_TblfmExprIntLiteral, haxorg_TblfmExprIntLiteral_vtable>(static_cast<bool(*)(org::sem::Tblfm::Expr::IntLiteral const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_TblfmExprFloatLiteral, haxorg_TblfmExprFloatLiteral_vtable>::__eq___const(haxorg_TblfmExprFloatLiteral self, OrgContext* org_context, haxorg_TblfmExprFloatLiteral other) {
  org::bind::c::execute_cpp<haxorg_TblfmExprFloatLiteral, haxorg_TblfmExprFloatLiteral_vtable>(static_cast<bool(*)(org::sem::Tblfm::Expr::FloatLiteral const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_TblfmExprRangeRef, haxorg_TblfmExprRangeRef_vtable>::__eq___const(haxorg_TblfmExprRangeRef self, OrgContext* org_context, haxorg_TblfmExprRangeRef other) {
  org::bind::c::execute_cpp<haxorg_TblfmExprRangeRef, haxorg_TblfmExprRangeRef_vtable>(static_cast<bool(*)(org::sem::Tblfm::Expr::RangeRef const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_TblfmExprCall, haxorg_TblfmExprCall_vtable>::__eq___const(haxorg_TblfmExprCall self, OrgContext* org_context, haxorg_TblfmExprCall other) {
  org::bind::c::execute_cpp<haxorg_TblfmExprCall, haxorg_TblfmExprCall_vtable>(static_cast<bool(*)(org::sem::Tblfm::Expr::Call const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_TblfmExprElisp, haxorg_TblfmExprElisp_vtable>::__eq___const(haxorg_TblfmExprElisp self, OrgContext* org_context, haxorg_TblfmExprElisp other) {
  org::bind::c::execute_cpp<haxorg_TblfmExprElisp, haxorg_TblfmExprElisp_vtable>(static_cast<bool(*)(org::sem::Tblfm::Expr::Elisp const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_TblfmAssign, haxorg_TblfmAssign_vtable>::__eq___const(haxorg_TblfmAssign self, OrgContext* org_context, haxorg_TblfmAssign other) {
  org::bind::c::execute_cpp<haxorg_TblfmAssign, haxorg_TblfmAssign_vtable>(static_cast<bool(*)(org::sem::Tblfm::Assign const&) const>(&operator==), self, org_context, other)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getBool_const(haxorg_AttrValue self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<hstd::Opt<bool>(*)() const>(&getBool), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getInt_const(haxorg_AttrValue self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<hstd::Opt<int>(*)() const>(&getInt), self, org_context)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getString_const(haxorg_AttrValue self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<hstd::Str(*)() const>(&getString), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getDouble_const(haxorg_AttrValue self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<hstd::Opt<double>(*)() const>(&getDouble), self, org_context)
}
bool org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::__eq___const(haxorg_AttrValue self, OrgContext* org_context, haxorg_AttrValue other) {
  org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<bool(*)(org::sem::AttrValue const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::isTextValue_const(haxorg_AttrValue self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<bool(*)() const>(&isTextValue), self, org_context)
}
haxorg_AttrValueTextValue org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getTextValueConst_const(haxorg_AttrValue self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<org::sem::AttrValue::TextValue const&(*)() const>(&getTextValue), self, org_context)
}
haxorg_AttrValueTextValue org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getTextValueMut(haxorg_AttrValue self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<org::sem::AttrValue::TextValue&(*)()>(&getTextValue), self, org_context)
}
bool org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::isFileReference_const(haxorg_AttrValue self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<bool(*)() const>(&isFileReference), self, org_context)
}
haxorg_AttrValueFileReference org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getFileReferenceConst_const(haxorg_AttrValue self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<org::sem::AttrValue::FileReference const&(*)() const>(&getFileReference), self, org_context)
}
haxorg_AttrValueFileReference org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getFileReferenceMut(haxorg_AttrValue self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<org::sem::AttrValue::FileReference&(*)()>(&getFileReference), self, org_context)
}
bool org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::isLispValue_const(haxorg_AttrValue self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<bool(*)() const>(&isLispValue), self, org_context)
}
haxorg_AttrValueLispValue org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getLispValueConst_const(haxorg_AttrValue self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<org::sem::AttrValue::LispValue const&(*)() const>(&getLispValue), self, org_context)
}
haxorg_AttrValueLispValue org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getLispValueMut(haxorg_AttrValue self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<org::sem::AttrValue::LispValue&(*)()>(&getLispValue), self, org_context)
}
haxorg_AttrValueKind org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getKind_const(haxorg_AttrValue self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<org::sem::AttrValue::Kind(*)() const>(&getKind), self, org_context)
}
bool org::bind::c::VTable<haxorg_AttrValueDimensionSpan, haxorg_AttrValueDimensionSpan_vtable>::__eq___const(haxorg_AttrValueDimensionSpan self, OrgContext* org_context, haxorg_AttrValueDimensionSpan other) {
  org::bind::c::execute_cpp<haxorg_AttrValueDimensionSpan, haxorg_AttrValueDimensionSpan_vtable>(static_cast<bool(*)(org::sem::AttrValue::DimensionSpan const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_AttrValueTextValue, haxorg_AttrValueTextValue_vtable>::__eq___const(haxorg_AttrValueTextValue self, OrgContext* org_context, haxorg_AttrValueTextValue other) {
  org::bind::c::execute_cpp<haxorg_AttrValueTextValue, haxorg_AttrValueTextValue_vtable>(static_cast<bool(*)(org::sem::AttrValue::TextValue const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_AttrValueFileReference, haxorg_AttrValueFileReference_vtable>::__eq___const(haxorg_AttrValueFileReference self, OrgContext* org_context, haxorg_AttrValueFileReference other) {
  org::bind::c::execute_cpp<haxorg_AttrValueFileReference, haxorg_AttrValueFileReference_vtable>(static_cast<bool(*)(org::sem::AttrValue::FileReference const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_AttrValueLispValue, haxorg_AttrValueLispValue_vtable>::__eq___const(haxorg_AttrValueLispValue self, OrgContext* org_context, haxorg_AttrValueLispValue other) {
  org::bind::c::execute_cpp<haxorg_AttrValueLispValue, haxorg_AttrValueLispValue_vtable>(static_cast<bool(*)(org::sem::AttrValue::LispValue const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_HashTagFlat, haxorg_HashTagFlat_vtable>::__eq___const(haxorg_HashTagFlat self, OrgContext* org_context, haxorg_HashTagFlat other) {
  org::bind::c::execute_cpp<haxorg_HashTagFlat, haxorg_HashTagFlat_vtable>(static_cast<bool(*)(org::sem::HashTagFlat const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_HashTagFlat, haxorg_HashTagFlat_vtable>::__lt___const(haxorg_HashTagFlat self, OrgContext* org_context, haxorg_HashTagFlat other) {
  org::bind::c::execute_cpp<haxorg_HashTagFlat, haxorg_HashTagFlat_vtable>(static_cast<bool(*)(org::sem::HashTagFlat const&) const>(&operator<), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_TodoKeyword, haxorg_TodoKeyword_vtable>::__eq___const(haxorg_TodoKeyword self, OrgContext* org_context, haxorg_TodoKeyword other) {
  org::bind::c::execute_cpp<haxorg_TodoKeyword, haxorg_TodoKeyword_vtable>(static_cast<bool(*)(org::sem::TodoKeyword const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_HashTagText, haxorg_HashTagText_vtable>::__eq___const(haxorg_HashTagText self, OrgContext* org_context, haxorg_HashTagText other) {
  org::bind::c::execute_cpp<haxorg_HashTagText, haxorg_HashTagText_vtable>(static_cast<bool(*)(org::sem::HashTagText const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_HashTagText, haxorg_HashTagText_vtable>::prefixMatch_const(haxorg_HashTagText self, OrgContext* org_context, haxorg_HstdVec prefix) {
  org::bind::c::execute_cpp<haxorg_HashTagText, haxorg_HashTagText_vtable>(static_cast<bool(*)(hstd::Vec<hstd::Str> const&) const>(&prefixMatch), self, org_context, prefix)
}
haxorg_HstdVec org::bind::c::VTable<haxorg_HashTagText, haxorg_HashTagText_vtable>::getFlatHashes_const(haxorg_HashTagText self, OrgContext* org_context, bool withIntermediate) {
  org::bind::c::execute_cpp<haxorg_HashTagText, haxorg_HashTagText_vtable>(static_cast<hstd::Vec<org::sem::HashTagFlat>(*)(bool) const>(&getFlatHashes), self, org_context, withIntermediate)
}
bool org::bind::c::VTable<haxorg_SubtreePath, haxorg_SubtreePath_vtable>::__eq___const(haxorg_SubtreePath self, OrgContext* org_context, haxorg_SubtreePath other) {
  org::bind::c::execute_cpp<haxorg_SubtreePath, haxorg_SubtreePath_vtable>(static_cast<bool(*)(org::sem::SubtreePath const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::__eq___const(haxorg_LinkTarget self, OrgContext* org_context, haxorg_LinkTarget other) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<bool(*)(org::sem::LinkTarget const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::isRaw_const(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<bool(*)() const>(&isRaw), self, org_context)
}
haxorg_LinkTargetRaw org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getRawConst_const(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::Raw const&(*)() const>(&getRaw), self, org_context)
}
haxorg_LinkTargetRaw org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getRawMut(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::Raw&(*)()>(&getRaw), self, org_context)
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::isId_const(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<bool(*)() const>(&isId), self, org_context)
}
haxorg_LinkTargetId org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getIdConst_const(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::Id const&(*)() const>(&getId), self, org_context)
}
haxorg_LinkTargetId org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getIdMut(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::Id&(*)()>(&getId), self, org_context)
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::isCustomId_const(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<bool(*)() const>(&isCustomId), self, org_context)
}
haxorg_LinkTargetCustomId org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getCustomIdConst_const(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::CustomId const&(*)() const>(&getCustomId), self, org_context)
}
haxorg_LinkTargetCustomId org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getCustomIdMut(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::CustomId&(*)()>(&getCustomId), self, org_context)
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::isSubtreeTitle_const(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<bool(*)() const>(&isSubtreeTitle), self, org_context)
}
haxorg_LinkTargetSubtreeTitle org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getSubtreeTitleConst_const(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::SubtreeTitle const&(*)() const>(&getSubtreeTitle), self, org_context)
}
haxorg_LinkTargetSubtreeTitle org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getSubtreeTitleMut(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::SubtreeTitle&(*)()>(&getSubtreeTitle), self, org_context)
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::isPerson_const(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<bool(*)() const>(&isPerson), self, org_context)
}
haxorg_LinkTargetPerson org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getPersonConst_const(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::Person const&(*)() const>(&getPerson), self, org_context)
}
haxorg_LinkTargetPerson org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getPersonMut(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::Person&(*)()>(&getPerson), self, org_context)
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::isUserProtocol_const(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<bool(*)() const>(&isUserProtocol), self, org_context)
}
haxorg_LinkTargetUserProtocol org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getUserProtocolConst_const(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::UserProtocol const&(*)() const>(&getUserProtocol), self, org_context)
}
haxorg_LinkTargetUserProtocol org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getUserProtocolMut(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::UserProtocol&(*)()>(&getUserProtocol), self, org_context)
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::isInternal_const(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<bool(*)() const>(&isInternal), self, org_context)
}
haxorg_LinkTargetInternal org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getInternalConst_const(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::Internal const&(*)() const>(&getInternal), self, org_context)
}
haxorg_LinkTargetInternal org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getInternalMut(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::Internal&(*)()>(&getInternal), self, org_context)
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::isFootnote_const(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<bool(*)() const>(&isFootnote), self, org_context)
}
haxorg_LinkTargetFootnote org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getFootnoteConst_const(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::Footnote const&(*)() const>(&getFootnote), self, org_context)
}
haxorg_LinkTargetFootnote org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getFootnoteMut(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::Footnote&(*)()>(&getFootnote), self, org_context)
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::isFile_const(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<bool(*)() const>(&isFile), self, org_context)
}
haxorg_LinkTargetFile org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getFileConst_const(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::File const&(*)() const>(&getFile), self, org_context)
}
haxorg_LinkTargetFile org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getFileMut(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::File&(*)()>(&getFile), self, org_context)
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::isAttachment_const(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<bool(*)() const>(&isAttachment), self, org_context)
}
haxorg_LinkTargetAttachment org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getAttachmentConst_const(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::Attachment const&(*)() const>(&getAttachment), self, org_context)
}
haxorg_LinkTargetAttachment org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getAttachmentMut(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::Attachment&(*)()>(&getAttachment), self, org_context)
}
haxorg_LinkTargetKind org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getKind_const(haxorg_LinkTarget self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::Kind(*)() const>(&getKind), self, org_context)
}
bool org::bind::c::VTable<haxorg_LinkTargetRaw, haxorg_LinkTargetRaw_vtable>::__eq___const(haxorg_LinkTargetRaw self, OrgContext* org_context, haxorg_LinkTargetRaw other) {
  org::bind::c::execute_cpp<haxorg_LinkTargetRaw, haxorg_LinkTargetRaw_vtable>(static_cast<bool(*)(org::sem::LinkTarget::Raw const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_LinkTargetId, haxorg_LinkTargetId_vtable>::__eq___const(haxorg_LinkTargetId self, OrgContext* org_context, haxorg_LinkTargetId other) {
  org::bind::c::execute_cpp<haxorg_LinkTargetId, haxorg_LinkTargetId_vtable>(static_cast<bool(*)(org::sem::LinkTarget::Id const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_LinkTargetCustomId, haxorg_LinkTargetCustomId_vtable>::__eq___const(haxorg_LinkTargetCustomId self, OrgContext* org_context, haxorg_LinkTargetCustomId other) {
  org::bind::c::execute_cpp<haxorg_LinkTargetCustomId, haxorg_LinkTargetCustomId_vtable>(static_cast<bool(*)(org::sem::LinkTarget::CustomId const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_LinkTargetSubtreeTitle, haxorg_LinkTargetSubtreeTitle_vtable>::__eq___const(haxorg_LinkTargetSubtreeTitle self, OrgContext* org_context, haxorg_LinkTargetSubtreeTitle other) {
  org::bind::c::execute_cpp<haxorg_LinkTargetSubtreeTitle, haxorg_LinkTargetSubtreeTitle_vtable>(static_cast<bool(*)(org::sem::LinkTarget::SubtreeTitle const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_LinkTargetPerson, haxorg_LinkTargetPerson_vtable>::__eq___const(haxorg_LinkTargetPerson self, OrgContext* org_context, haxorg_LinkTargetPerson other) {
  org::bind::c::execute_cpp<haxorg_LinkTargetPerson, haxorg_LinkTargetPerson_vtable>(static_cast<bool(*)(org::sem::LinkTarget::Person const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_LinkTargetUserProtocol, haxorg_LinkTargetUserProtocol_vtable>::__eq___const(haxorg_LinkTargetUserProtocol self, OrgContext* org_context, haxorg_LinkTargetUserProtocol other) {
  org::bind::c::execute_cpp<haxorg_LinkTargetUserProtocol, haxorg_LinkTargetUserProtocol_vtable>(static_cast<bool(*)(org::sem::LinkTarget::UserProtocol const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_LinkTargetInternal, haxorg_LinkTargetInternal_vtable>::__eq___const(haxorg_LinkTargetInternal self, OrgContext* org_context, haxorg_LinkTargetInternal other) {
  org::bind::c::execute_cpp<haxorg_LinkTargetInternal, haxorg_LinkTargetInternal_vtable>(static_cast<bool(*)(org::sem::LinkTarget::Internal const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_LinkTargetFootnote, haxorg_LinkTargetFootnote_vtable>::__eq___const(haxorg_LinkTargetFootnote self, OrgContext* org_context, haxorg_LinkTargetFootnote other) {
  org::bind::c::execute_cpp<haxorg_LinkTargetFootnote, haxorg_LinkTargetFootnote_vtable>(static_cast<bool(*)(org::sem::LinkTarget::Footnote const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_LinkTargetFile, haxorg_LinkTargetFile_vtable>::__eq___const(haxorg_LinkTargetFile self, OrgContext* org_context, haxorg_LinkTargetFile other) {
  org::bind::c::execute_cpp<haxorg_LinkTargetFile, haxorg_LinkTargetFile_vtable>(static_cast<bool(*)(org::sem::LinkTarget::File const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_LinkTargetAttachment, haxorg_LinkTargetAttachment_vtable>::__eq___const(haxorg_LinkTargetAttachment self, OrgContext* org_context, haxorg_LinkTargetAttachment other) {
  org::bind::c::execute_cpp<haxorg_LinkTargetAttachment, haxorg_LinkTargetAttachment_vtable>(static_cast<bool(*)(org::sem::LinkTarget::Attachment const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::__eq___const(haxorg_SubtreeLogHead self, OrgContext* org_context, haxorg_SubtreeLogHead other) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<bool(*)(org::sem::SubtreeLogHead const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::isPriority_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<bool(*)() const>(&isPriority), self, org_context)
}
haxorg_SubtreeLogHeadPriority org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getPriorityConst_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Priority const&(*)() const>(&getPriority), self, org_context)
}
haxorg_SubtreeLogHeadPriority org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getPriorityMut(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Priority&(*)()>(&getPriority), self, org_context)
}
bool org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::isNote_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<bool(*)() const>(&isNote), self, org_context)
}
haxorg_SubtreeLogHeadNote org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getNoteConst_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Note const&(*)() const>(&getNote), self, org_context)
}
haxorg_SubtreeLogHeadNote org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getNoteMut(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Note&(*)()>(&getNote), self, org_context)
}
bool org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::isRefile_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<bool(*)() const>(&isRefile), self, org_context)
}
haxorg_SubtreeLogHeadRefile org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getRefileConst_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Refile const&(*)() const>(&getRefile), self, org_context)
}
haxorg_SubtreeLogHeadRefile org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getRefileMut(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Refile&(*)()>(&getRefile), self, org_context)
}
bool org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::isClock_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<bool(*)() const>(&isClock), self, org_context)
}
haxorg_SubtreeLogHeadClock org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getClockConst_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Clock const&(*)() const>(&getClock), self, org_context)
}
haxorg_SubtreeLogHeadClock org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getClockMut(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Clock&(*)()>(&getClock), self, org_context)
}
bool org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::isState_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<bool(*)() const>(&isState), self, org_context)
}
haxorg_SubtreeLogHeadState org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getStateConst_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::State const&(*)() const>(&getState), self, org_context)
}
haxorg_SubtreeLogHeadState org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getStateMut(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::State&(*)()>(&getState), self, org_context)
}
bool org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::isDeadline_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<bool(*)() const>(&isDeadline), self, org_context)
}
haxorg_SubtreeLogHeadDeadline org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getDeadlineConst_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Deadline const&(*)() const>(&getDeadline), self, org_context)
}
haxorg_SubtreeLogHeadDeadline org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getDeadlineMut(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Deadline&(*)()>(&getDeadline), self, org_context)
}
bool org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::isSchedule_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<bool(*)() const>(&isSchedule), self, org_context)
}
haxorg_SubtreeLogHeadSchedule org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getScheduleConst_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Schedule const&(*)() const>(&getSchedule), self, org_context)
}
haxorg_SubtreeLogHeadSchedule org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getScheduleMut(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Schedule&(*)()>(&getSchedule), self, org_context)
}
bool org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::isTag_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<bool(*)() const>(&isTag), self, org_context)
}
haxorg_SubtreeLogHeadTag org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getTagConst_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Tag const&(*)() const>(&getTag), self, org_context)
}
haxorg_SubtreeLogHeadTag org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getTagMut(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Tag&(*)()>(&getTag), self, org_context)
}
bool org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::isUnknown_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<bool(*)() const>(&isUnknown), self, org_context)
}
haxorg_SubtreeLogHeadUnknown org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getUnknownConst_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Unknown const&(*)() const>(&getUnknown), self, org_context)
}
haxorg_SubtreeLogHeadUnknown org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getUnknownMut(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Unknown&(*)()>(&getUnknown), self, org_context)
}
haxorg_SubtreeLogHeadKind org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getLogKind_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Kind(*)() const>(&getLogKind), self, org_context)
}
bool org::bind::c::VTable<haxorg_SubtreeLogHeadPriority, haxorg_SubtreeLogHeadPriority_vtable>::__eq___const(haxorg_SubtreeLogHeadPriority self, OrgContext* org_context, haxorg_SubtreeLogHeadPriority other) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHeadPriority, haxorg_SubtreeLogHeadPriority_vtable>(static_cast<bool(*)(org::sem::SubtreeLogHead::Priority const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_SubtreeLogHeadNote, haxorg_SubtreeLogHeadNote_vtable>::__eq___const(haxorg_SubtreeLogHeadNote self, OrgContext* org_context, haxorg_SubtreeLogHeadNote other) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHeadNote, haxorg_SubtreeLogHeadNote_vtable>(static_cast<bool(*)(org::sem::SubtreeLogHead::Note const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_SubtreeLogHeadRefile, haxorg_SubtreeLogHeadRefile_vtable>::__eq___const(haxorg_SubtreeLogHeadRefile self, OrgContext* org_context, haxorg_SubtreeLogHeadRefile other) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHeadRefile, haxorg_SubtreeLogHeadRefile_vtable>(static_cast<bool(*)(org::sem::SubtreeLogHead::Refile const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_SubtreeLogHeadClock, haxorg_SubtreeLogHeadClock_vtable>::__eq___const(haxorg_SubtreeLogHeadClock self, OrgContext* org_context, haxorg_SubtreeLogHeadClock other) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHeadClock, haxorg_SubtreeLogHeadClock_vtable>(static_cast<bool(*)(org::sem::SubtreeLogHead::Clock const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_SubtreeLogHeadState, haxorg_SubtreeLogHeadState_vtable>::__eq___const(haxorg_SubtreeLogHeadState self, OrgContext* org_context, haxorg_SubtreeLogHeadState other) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHeadState, haxorg_SubtreeLogHeadState_vtable>(static_cast<bool(*)(org::sem::SubtreeLogHead::State const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_SubtreeLogHeadDeadline, haxorg_SubtreeLogHeadDeadline_vtable>::__eq___const(haxorg_SubtreeLogHeadDeadline self, OrgContext* org_context, haxorg_SubtreeLogHeadDeadline other) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHeadDeadline, haxorg_SubtreeLogHeadDeadline_vtable>(static_cast<bool(*)(org::sem::SubtreeLogHead::Deadline const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_SubtreeLogHeadSchedule, haxorg_SubtreeLogHeadSchedule_vtable>::__eq___const(haxorg_SubtreeLogHeadSchedule self, OrgContext* org_context, haxorg_SubtreeLogHeadSchedule other) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHeadSchedule, haxorg_SubtreeLogHeadSchedule_vtable>(static_cast<bool(*)(org::sem::SubtreeLogHead::Schedule const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_SubtreeLogHeadTag, haxorg_SubtreeLogHeadTag_vtable>::__eq___const(haxorg_SubtreeLogHeadTag self, OrgContext* org_context, haxorg_SubtreeLogHeadTag other) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHeadTag, haxorg_SubtreeLogHeadTag_vtable>(static_cast<bool(*)(org::sem::SubtreeLogHead::Tag const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_SubtreeLogHeadUnknown, haxorg_SubtreeLogHeadUnknown_vtable>::__eq___const(haxorg_SubtreeLogHeadUnknown self, OrgContext* org_context, haxorg_SubtreeLogHeadUnknown other) {
  org::bind::c::execute_cpp<haxorg_SubtreeLogHeadUnknown, haxorg_SubtreeLogHeadUnknown_vtable>(static_cast<bool(*)(org::sem::SubtreeLogHead::Unknown const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_SubtreeCompletion, haxorg_SubtreeCompletion_vtable>::__eq___const(haxorg_SubtreeCompletion self, OrgContext* org_context, haxorg_SubtreeCompletion other) {
  org::bind::c::execute_cpp<haxorg_SubtreeCompletion, haxorg_SubtreeCompletion_vtable>(static_cast<bool(*)(org::sem::SubtreeCompletion const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_AttrList, haxorg_AttrList_vtable>::__eq___const(haxorg_AttrList self, OrgContext* org_context, haxorg_AttrList other) {
  org::bind::c::execute_cpp<haxorg_AttrList, haxorg_AttrList_vtable>(static_cast<bool(*)(org::sem::AttrList const&) const>(&operator==), self, org_context, other)
}
haxorg_HstdVec org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::getFlatArgs_const(haxorg_AttrGroup self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<hstd::Vec<org::sem::AttrValue>(*)() const>(&getFlatArgs), self, org_context)
}
haxorg_HstdVec org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::getAttrs_const(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdOpt key) {
  org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<hstd::Vec<org::sem::AttrValue>(*)(hstd::Opt<hstd::Str> const&) const>(&getAttrs), self, org_context, key)
}
void org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::setNamedAttr(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdStr key, haxorg_HstdVec attrs) {
  org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<void(*)(hstd::Str const&, hstd::Vec<org::sem::AttrValue> const&)>(&setNamedAttr), self, org_context, key, attrs)
}
void org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::setPositionalAttr(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdVec items) {
  org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<void(*)(hstd::Vec<org::sem::AttrValue> const&)>(&setPositionalAttr), self, org_context, items)
}
int org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::getPositionalSize_const(haxorg_AttrGroup self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<int(*)() const>(&getPositionalSize), self, org_context)
}
int org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::getNamedSize_const(haxorg_AttrGroup self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<int(*)() const>(&getNamedSize), self, org_context)
}
bool org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::isEmpty_const(haxorg_AttrGroup self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<bool(*)() const>(&isEmpty), self, org_context)
}
haxorg_AttrList org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::getAll_const(haxorg_AttrGroup self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<org::sem::AttrList(*)() const>(&getAll), self, org_context)
}
haxorg_AttrValue org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::atPositional_const(haxorg_AttrGroup self, OrgContext* org_context, int index) {
  org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<org::sem::AttrValue const&(*)(int) const>(&atPositional), self, org_context, index)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::getPositional_const(haxorg_AttrGroup self, OrgContext* org_context, int index) {
  org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<hstd::Opt<org::sem::AttrValue>(*)(int) const>(&getPositional), self, org_context, index)
}
haxorg_AttrList org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::atNamed_const(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdStr index) {
  org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<org::sem::AttrList const&(*)(hstd::Str const&) const>(&atNamed), self, org_context, index)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::getNamed_const(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdStr index) {
  org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<hstd::Opt<org::sem::AttrList>(*)(hstd::Str const&) const>(&getNamed), self, org_context, index)
}
haxorg_AttrValue org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::atFirstNamed_const(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdStr index) {
  org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<org::sem::AttrValue const&(*)(hstd::Str const&) const>(&atFirstNamed), self, org_context, index)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::getFirstNamed_const(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdStr index) {
  org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<hstd::Opt<org::sem::AttrValue>(*)(hstd::Str const&) const>(&getFirstNamed), self, org_context, index)
}
haxorg_AttrList org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::atVarNamed_const(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdStr index) {
  org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<org::sem::AttrList(*)(hstd::Str const&) const>(&atVarNamed), self, org_context, index)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::getVarNamed_const(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdStr index) {
  org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<hstd::Opt<org::sem::AttrList>(*)(hstd::Str const&) const>(&getVarNamed), self, org_context, index)
}
haxorg_AttrValue org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::atFirstVarNamed_const(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdStr index) {
  org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<org::sem::AttrValue(*)(hstd::Str const&) const>(&atFirstVarNamed), self, org_context, index)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::getFirstVarNamed_const(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdStr index) {
  org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<hstd::Opt<org::sem::AttrValue>(*)(hstd::Str const&) const>(&getFirstVarNamed), self, org_context, index)
}
bool org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::__eq___const(haxorg_AttrGroup self, OrgContext* org_context, haxorg_AttrGroup other) {
  org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<bool(*)(org::sem::AttrGroup const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_OrgCodeEvalInput, haxorg_OrgCodeEvalInput_vtable>::__eq___const(haxorg_OrgCodeEvalInput self, OrgContext* org_context, haxorg_OrgCodeEvalInput other) {
  org::bind::c::execute_cpp<haxorg_OrgCodeEvalInput, haxorg_OrgCodeEvalInput_vtable>(static_cast<bool(*)(org::sem::OrgCodeEvalInput const&) const>(&operator==), self, org_context, other)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_OrgCodeEvalInput, haxorg_OrgCodeEvalInput_vtable>::getVariable_const(haxorg_OrgCodeEvalInput self, OrgContext* org_context, haxorg_HstdStr name) {
  org::bind::c::execute_cpp<haxorg_OrgCodeEvalInput, haxorg_OrgCodeEvalInput_vtable>(static_cast<hstd::Opt<org::sem::OrgCodeEvalInput::Var>(*)(hstd::Str const&) const>(&getVariable), self, org_context, name)
}
bool org::bind::c::VTable<haxorg_OrgCodeEvalInputVar, haxorg_OrgCodeEvalInputVar_vtable>::__eq___const(haxorg_OrgCodeEvalInputVar self, OrgContext* org_context, haxorg_OrgCodeEvalInputVar other) {
  org::bind::c::execute_cpp<haxorg_OrgCodeEvalInputVar, haxorg_OrgCodeEvalInputVar_vtable>(static_cast<bool(*)(org::sem::OrgCodeEvalInput::Var const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_OrgCodeEvalOutput, haxorg_OrgCodeEvalOutput_vtable>::__eq___const(haxorg_OrgCodeEvalOutput self, OrgContext* org_context, haxorg_OrgCodeEvalOutput other) {
  org::bind::c::execute_cpp<haxorg_OrgCodeEvalOutput, haxorg_OrgCodeEvalOutput_vtable>(static_cast<bool(*)(org::sem::OrgCodeEvalOutput const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ColumnView, haxorg_ColumnView_vtable>::__eq___const(haxorg_ColumnView self, OrgContext* org_context, haxorg_ColumnView other) {
  org::bind::c::execute_cpp<haxorg_ColumnView, haxorg_ColumnView_vtable>(static_cast<bool(*)(org::sem::ColumnView const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>::__eq___const(haxorg_ColumnViewSummary self, OrgContext* org_context, haxorg_ColumnViewSummary other) {
  org::bind::c::execute_cpp<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>(static_cast<bool(*)(org::sem::ColumnView::Summary const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>::isCheckboxAggregate_const(haxorg_ColumnViewSummary self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>(static_cast<bool(*)() const>(&isCheckboxAggregate), self, org_context)
}
haxorg_ColumnViewSummaryCheckboxAggregate org::bind::c::VTable<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>::getCheckboxAggregateConst_const(haxorg_ColumnViewSummary self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>(static_cast<org::sem::ColumnView::Summary::CheckboxAggregate const&(*)() const>(&getCheckboxAggregate), self, org_context)
}
haxorg_ColumnViewSummaryCheckboxAggregate org::bind::c::VTable<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>::getCheckboxAggregateMut(haxorg_ColumnViewSummary self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>(static_cast<org::sem::ColumnView::Summary::CheckboxAggregate&(*)()>(&getCheckboxAggregate), self, org_context)
}
bool org::bind::c::VTable<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>::isMathAggregate_const(haxorg_ColumnViewSummary self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>(static_cast<bool(*)() const>(&isMathAggregate), self, org_context)
}
haxorg_ColumnViewSummaryMathAggregate org::bind::c::VTable<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>::getMathAggregateConst_const(haxorg_ColumnViewSummary self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>(static_cast<org::sem::ColumnView::Summary::MathAggregate const&(*)() const>(&getMathAggregate), self, org_context)
}
haxorg_ColumnViewSummaryMathAggregate org::bind::c::VTable<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>::getMathAggregateMut(haxorg_ColumnViewSummary self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>(static_cast<org::sem::ColumnView::Summary::MathAggregate&(*)()>(&getMathAggregate), self, org_context)
}
haxorg_ColumnViewSummaryKind org::bind::c::VTable<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>::getKind_const(haxorg_ColumnViewSummary self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>(static_cast<org::sem::ColumnView::Summary::Kind(*)() const>(&getKind), self, org_context)
}
bool org::bind::c::VTable<haxorg_ColumnViewSummaryCheckboxAggregate, haxorg_ColumnViewSummaryCheckboxAggregate_vtable>::__eq___const(haxorg_ColumnViewSummaryCheckboxAggregate self, OrgContext* org_context, haxorg_ColumnViewSummaryCheckboxAggregate other) {
  org::bind::c::execute_cpp<haxorg_ColumnViewSummaryCheckboxAggregate, haxorg_ColumnViewSummaryCheckboxAggregate_vtable>(static_cast<bool(*)(org::sem::ColumnView::Summary::CheckboxAggregate const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ColumnViewSummaryMathAggregate, haxorg_ColumnViewSummaryMathAggregate_vtable>::__eq___const(haxorg_ColumnViewSummaryMathAggregate self, OrgContext* org_context, haxorg_ColumnViewSummaryMathAggregate other) {
  org::bind::c::execute_cpp<haxorg_ColumnViewSummaryMathAggregate, haxorg_ColumnViewSummaryMathAggregate_vtable>(static_cast<bool(*)(org::sem::ColumnView::Summary::MathAggregate const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ColumnViewColumn, haxorg_ColumnViewColumn_vtable>::__eq___const(haxorg_ColumnViewColumn self, OrgContext* org_context, haxorg_ColumnViewColumn other) {
  org::bind::c::execute_cpp<haxorg_ColumnViewColumn, haxorg_ColumnViewColumn_vtable>(static_cast<bool(*)(org::sem::ColumnView::Column const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_BlockCodeLine, haxorg_BlockCodeLine_vtable>::__eq___const(haxorg_BlockCodeLine self, OrgContext* org_context, haxorg_BlockCodeLine other) {
  org::bind::c::execute_cpp<haxorg_BlockCodeLine, haxorg_BlockCodeLine_vtable>(static_cast<bool(*)(org::sem::BlockCodeLine const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::__eq___const(haxorg_BlockCodeLinePart self, OrgContext* org_context, haxorg_BlockCodeLinePart other) {
  org::bind::c::execute_cpp<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>(static_cast<bool(*)(org::sem::BlockCodeLine::Part const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::isRaw_const(haxorg_BlockCodeLinePart self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>(static_cast<bool(*)() const>(&isRaw), self, org_context)
}
haxorg_BlockCodeLinePartRaw org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::getRawConst_const(haxorg_BlockCodeLinePart self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>(static_cast<org::sem::BlockCodeLine::Part::Raw const&(*)() const>(&getRaw), self, org_context)
}
haxorg_BlockCodeLinePartRaw org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::getRawMut(haxorg_BlockCodeLinePart self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>(static_cast<org::sem::BlockCodeLine::Part::Raw&(*)()>(&getRaw), self, org_context)
}
bool org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::isCallout_const(haxorg_BlockCodeLinePart self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>(static_cast<bool(*)() const>(&isCallout), self, org_context)
}
haxorg_BlockCodeLinePartCallout org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::getCalloutConst_const(haxorg_BlockCodeLinePart self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>(static_cast<org::sem::BlockCodeLine::Part::Callout const&(*)() const>(&getCallout), self, org_context)
}
haxorg_BlockCodeLinePartCallout org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::getCalloutMut(haxorg_BlockCodeLinePart self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>(static_cast<org::sem::BlockCodeLine::Part::Callout&(*)()>(&getCallout), self, org_context)
}
bool org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::isTangle_const(haxorg_BlockCodeLinePart self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>(static_cast<bool(*)() const>(&isTangle), self, org_context)
}
haxorg_BlockCodeLinePartTangle org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::getTangleConst_const(haxorg_BlockCodeLinePart self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>(static_cast<org::sem::BlockCodeLine::Part::Tangle const&(*)() const>(&getTangle), self, org_context)
}
haxorg_BlockCodeLinePartTangle org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::getTangleMut(haxorg_BlockCodeLinePart self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>(static_cast<org::sem::BlockCodeLine::Part::Tangle&(*)()>(&getTangle), self, org_context)
}
haxorg_BlockCodeLinePartKind org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::getKind_const(haxorg_BlockCodeLinePart self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>(static_cast<org::sem::BlockCodeLine::Part::Kind(*)() const>(&getKind), self, org_context)
}
bool org::bind::c::VTable<haxorg_BlockCodeLinePartRaw, haxorg_BlockCodeLinePartRaw_vtable>::__eq___const(haxorg_BlockCodeLinePartRaw self, OrgContext* org_context, haxorg_BlockCodeLinePartRaw other) {
  org::bind::c::execute_cpp<haxorg_BlockCodeLinePartRaw, haxorg_BlockCodeLinePartRaw_vtable>(static_cast<bool(*)(org::sem::BlockCodeLine::Part::Raw const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_BlockCodeLinePartCallout, haxorg_BlockCodeLinePartCallout_vtable>::__eq___const(haxorg_BlockCodeLinePartCallout self, OrgContext* org_context, haxorg_BlockCodeLinePartCallout other) {
  org::bind::c::execute_cpp<haxorg_BlockCodeLinePartCallout, haxorg_BlockCodeLinePartCallout_vtable>(static_cast<bool(*)(org::sem::BlockCodeLine::Part::Callout const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_BlockCodeLinePartTangle, haxorg_BlockCodeLinePartTangle_vtable>::__eq___const(haxorg_BlockCodeLinePartTangle self, OrgContext* org_context, haxorg_BlockCodeLinePartTangle other) {
  org::bind::c::execute_cpp<haxorg_BlockCodeLinePartTangle, haxorg_BlockCodeLinePartTangle_vtable>(static_cast<bool(*)(org::sem::BlockCodeLine::Part::Tangle const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>::__eq___const(haxorg_DocumentExportConfig self, OrgContext* org_context, haxorg_DocumentExportConfig other) {
  org::bind::c::execute_cpp<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>(static_cast<bool(*)(org::sem::DocumentExportConfig const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>::isDoExport_const(haxorg_DocumentExportConfig self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>(static_cast<bool(*)() const>(&isDoExport), self, org_context)
}
haxorg_DocumentExportConfigDoExport org::bind::c::VTable<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>::getDoExportConst_const(haxorg_DocumentExportConfig self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>(static_cast<org::sem::DocumentExportConfig::DoExport const&(*)() const>(&getDoExport), self, org_context)
}
haxorg_DocumentExportConfigDoExport org::bind::c::VTable<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>::getDoExportMut(haxorg_DocumentExportConfig self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>(static_cast<org::sem::DocumentExportConfig::DoExport&(*)()>(&getDoExport), self, org_context)
}
bool org::bind::c::VTable<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>::isExportFixed_const(haxorg_DocumentExportConfig self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>(static_cast<bool(*)() const>(&isExportFixed), self, org_context)
}
haxorg_DocumentExportConfigExportFixed org::bind::c::VTable<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>::getExportFixedConst_const(haxorg_DocumentExportConfig self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>(static_cast<org::sem::DocumentExportConfig::ExportFixed const&(*)() const>(&getExportFixed), self, org_context)
}
haxorg_DocumentExportConfigExportFixed org::bind::c::VTable<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>::getExportFixedMut(haxorg_DocumentExportConfig self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>(static_cast<org::sem::DocumentExportConfig::ExportFixed&(*)()>(&getExportFixed), self, org_context)
}
haxorg_DocumentExportConfigTocExportKind org::bind::c::VTable<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>::getTocExportKind_const(haxorg_DocumentExportConfig self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>(static_cast<org::sem::DocumentExportConfig::TocExportKind(*)() const>(&getTocExportKind), self, org_context)
}
bool org::bind::c::VTable<haxorg_DocumentExportConfigTaskExport, haxorg_DocumentExportConfigTaskExport_vtable>::__eq___const(haxorg_DocumentExportConfigTaskExport self, OrgContext* org_context, haxorg_DocumentExportConfigTaskExport other) {
  org::bind::c::execute_cpp<haxorg_DocumentExportConfigTaskExport, haxorg_DocumentExportConfigTaskExport_vtable>(static_cast<bool(*)(org::sem::DocumentExportConfig::TaskExport const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_DocumentExportConfigDoExport, haxorg_DocumentExportConfigDoExport_vtable>::__eq___const(haxorg_DocumentExportConfigDoExport self, OrgContext* org_context, haxorg_DocumentExportConfigDoExport other) {
  org::bind::c::execute_cpp<haxorg_DocumentExportConfigDoExport, haxorg_DocumentExportConfigDoExport_vtable>(static_cast<bool(*)(org::sem::DocumentExportConfig::DoExport const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_DocumentExportConfigExportFixed, haxorg_DocumentExportConfigExportFixed_vtable>::__eq___const(haxorg_DocumentExportConfigExportFixed self, OrgContext* org_context, haxorg_DocumentExportConfigExportFixed other) {
  org::bind::c::execute_cpp<haxorg_DocumentExportConfigExportFixed, haxorg_DocumentExportConfigExportFixed_vtable>(static_cast<bool(*)(org::sem::DocumentExportConfig::ExportFixed const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_SubtreePeriod, haxorg_SubtreePeriod_vtable>::__eq___const(haxorg_SubtreePeriod self, OrgContext* org_context, haxorg_SubtreePeriod other) {
  org::bind::c::execute_cpp<haxorg_SubtreePeriod, haxorg_SubtreePeriod_vtable>(static_cast<bool(*)(org::sem::SubtreePeriod const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isMatching_const(haxorg_NamedProperty self, OrgContext* org_context, haxorg_HstdStr kind, haxorg_HstdOpt subKind) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&isMatching), self, org_context, kind, subKind)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getName_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<hstd::Str(*)() const>(&getName), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getSubKind_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<hstd::Opt<hstd::Str>(*)() const>(&getSubKind), self, org_context)
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::__eq___const(haxorg_NamedProperty self, OrgContext* org_context, haxorg_NamedProperty other) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(*)(org::sem::NamedProperty const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isNonblocking_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(*)() const>(&isNonblocking), self, org_context)
}
haxorg_NamedPropertyNonblocking org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getNonblockingConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Nonblocking const&(*)() const>(&getNonblocking), self, org_context)
}
haxorg_NamedPropertyNonblocking org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getNonblockingMut(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Nonblocking&(*)()>(&getNonblocking), self, org_context)
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isArchiveTime_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(*)() const>(&isArchiveTime), self, org_context)
}
haxorg_NamedPropertyArchiveTime org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveTimeConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ArchiveTime const&(*)() const>(&getArchiveTime), self, org_context)
}
haxorg_NamedPropertyArchiveTime org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveTimeMut(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ArchiveTime&(*)()>(&getArchiveTime), self, org_context)
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isArchiveFile_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(*)() const>(&isArchiveFile), self, org_context)
}
haxorg_NamedPropertyArchiveFile org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveFileConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ArchiveFile const&(*)() const>(&getArchiveFile), self, org_context)
}
haxorg_NamedPropertyArchiveFile org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveFileMut(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ArchiveFile&(*)()>(&getArchiveFile), self, org_context)
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isArchiveOlpath_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(*)() const>(&isArchiveOlpath), self, org_context)
}
haxorg_NamedPropertyArchiveOlpath org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveOlpathConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ArchiveOlpath const&(*)() const>(&getArchiveOlpath), self, org_context)
}
haxorg_NamedPropertyArchiveOlpath org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveOlpathMut(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ArchiveOlpath&(*)()>(&getArchiveOlpath), self, org_context)
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isArchiveTarget_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(*)() const>(&isArchiveTarget), self, org_context)
}
haxorg_NamedPropertyArchiveTarget org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveTargetConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ArchiveTarget const&(*)() const>(&getArchiveTarget), self, org_context)
}
haxorg_NamedPropertyArchiveTarget org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveTargetMut(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ArchiveTarget&(*)()>(&getArchiveTarget), self, org_context)
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isArchiveCategory_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(*)() const>(&isArchiveCategory), self, org_context)
}
haxorg_NamedPropertyArchiveCategory org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveCategoryConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ArchiveCategory const&(*)() const>(&getArchiveCategory), self, org_context)
}
haxorg_NamedPropertyArchiveCategory org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveCategoryMut(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ArchiveCategory&(*)()>(&getArchiveCategory), self, org_context)
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isArchiveTodo_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(*)() const>(&isArchiveTodo), self, org_context)
}
haxorg_NamedPropertyArchiveTodo org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveTodoConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ArchiveTodo const&(*)() const>(&getArchiveTodo), self, org_context)
}
haxorg_NamedPropertyArchiveTodo org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveTodoMut(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ArchiveTodo&(*)()>(&getArchiveTodo), self, org_context)
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isTrigger_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(*)() const>(&isTrigger), self, org_context)
}
haxorg_NamedPropertyTrigger org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getTriggerConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Trigger const&(*)() const>(&getTrigger), self, org_context)
}
haxorg_NamedPropertyTrigger org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getTriggerMut(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Trigger&(*)()>(&getTrigger), self, org_context)
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isExportLatexClass_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(*)() const>(&isExportLatexClass), self, org_context)
}
haxorg_NamedPropertyExportLatexClass org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getExportLatexClassConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ExportLatexClass const&(*)() const>(&getExportLatexClass), self, org_context)
}
haxorg_NamedPropertyExportLatexClass org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getExportLatexClassMut(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ExportLatexClass&(*)()>(&getExportLatexClass), self, org_context)
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isCookieData_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(*)() const>(&isCookieData), self, org_context)
}
haxorg_NamedPropertyCookieData org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCookieDataConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::CookieData const&(*)() const>(&getCookieData), self, org_context)
}
haxorg_NamedPropertyCookieData org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCookieDataMut(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::CookieData&(*)()>(&getCookieData), self, org_context)
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isExportLatexClassOptions_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(*)() const>(&isExportLatexClassOptions), self, org_context)
}
haxorg_NamedPropertyExportLatexClassOptions org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getExportLatexClassOptionsConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ExportLatexClassOptions const&(*)() const>(&getExportLatexClassOptions), self, org_context)
}
haxorg_NamedPropertyExportLatexClassOptions org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getExportLatexClassOptionsMut(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ExportLatexClassOptions&(*)()>(&getExportLatexClassOptions), self, org_context)
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isExportLatexHeader_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(*)() const>(&isExportLatexHeader), self, org_context)
}
haxorg_NamedPropertyExportLatexHeader org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getExportLatexHeaderConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ExportLatexHeader const&(*)() const>(&getExportLatexHeader), self, org_context)
}
haxorg_NamedPropertyExportLatexHeader org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getExportLatexHeaderMut(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ExportLatexHeader&(*)()>(&getExportLatexHeader), self, org_context)
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isExportLatexCompiler_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(*)() const>(&isExportLatexCompiler), self, org_context)
}
haxorg_NamedPropertyExportLatexCompiler org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getExportLatexCompilerConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ExportLatexCompiler const&(*)() const>(&getExportLatexCompiler), self, org_context)
}
haxorg_NamedPropertyExportLatexCompiler org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getExportLatexCompilerMut(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ExportLatexCompiler&(*)()>(&getExportLatexCompiler), self, org_context)
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isOrdered_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(*)() const>(&isOrdered), self, org_context)
}
haxorg_NamedPropertyOrdered org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getOrderedConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Ordered const&(*)() const>(&getOrdered), self, org_context)
}
haxorg_NamedPropertyOrdered org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getOrderedMut(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Ordered&(*)()>(&getOrdered), self, org_context)
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isEffort_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(*)() const>(&isEffort), self, org_context)
}
haxorg_NamedPropertyEffort org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getEffortConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Effort const&(*)() const>(&getEffort), self, org_context)
}
haxorg_NamedPropertyEffort org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getEffortMut(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Effort&(*)()>(&getEffort), self, org_context)
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isVisibility_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(*)() const>(&isVisibility), self, org_context)
}
haxorg_NamedPropertyVisibility org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getVisibilityConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Visibility const&(*)() const>(&getVisibility), self, org_context)
}
haxorg_NamedPropertyVisibility org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getVisibilityMut(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Visibility&(*)()>(&getVisibility), self, org_context)
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isExportOptions_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(*)() const>(&isExportOptions), self, org_context)
}
haxorg_NamedPropertyExportOptions org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getExportOptionsConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ExportOptions const&(*)() const>(&getExportOptions), self, org_context)
}
haxorg_NamedPropertyExportOptions org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getExportOptionsMut(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ExportOptions&(*)()>(&getExportOptions), self, org_context)
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isBlocker_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(*)() const>(&isBlocker), self, org_context)
}
haxorg_NamedPropertyBlocker org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getBlockerConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Blocker const&(*)() const>(&getBlocker), self, org_context)
}
haxorg_NamedPropertyBlocker org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getBlockerMut(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Blocker&(*)()>(&getBlocker), self, org_context)
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isUnnumbered_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(*)() const>(&isUnnumbered), self, org_context)
}
haxorg_NamedPropertyUnnumbered org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getUnnumberedConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Unnumbered const&(*)() const>(&getUnnumbered), self, org_context)
}
haxorg_NamedPropertyUnnumbered org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getUnnumberedMut(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Unnumbered&(*)()>(&getUnnumbered), self, org_context)
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isCreated_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(*)() const>(&isCreated), self, org_context)
}
haxorg_NamedPropertyCreated org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCreatedConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Created const&(*)() const>(&getCreated), self, org_context)
}
haxorg_NamedPropertyCreated org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCreatedMut(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Created&(*)()>(&getCreated), self, org_context)
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isRadioId_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(*)() const>(&isRadioId), self, org_context)
}
haxorg_NamedPropertyRadioId org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getRadioIdConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::RadioId const&(*)() const>(&getRadioId), self, org_context)
}
haxorg_NamedPropertyRadioId org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getRadioIdMut(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::RadioId&(*)()>(&getRadioId), self, org_context)
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isHashtagDef_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(*)() const>(&isHashtagDef), self, org_context)
}
haxorg_NamedPropertyHashtagDef org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getHashtagDefConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::HashtagDef const&(*)() const>(&getHashtagDef), self, org_context)
}
haxorg_NamedPropertyHashtagDef org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getHashtagDefMut(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::HashtagDef&(*)()>(&getHashtagDef), self, org_context)
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isCustomArgs_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(*)() const>(&isCustomArgs), self, org_context)
}
haxorg_NamedPropertyCustomArgs org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCustomArgsConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::CustomArgs const&(*)() const>(&getCustomArgs), self, org_context)
}
haxorg_NamedPropertyCustomArgs org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCustomArgsMut(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::CustomArgs&(*)()>(&getCustomArgs), self, org_context)
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isCustomRaw_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(*)() const>(&isCustomRaw), self, org_context)
}
haxorg_NamedPropertyCustomRaw org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCustomRawConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::CustomRaw const&(*)() const>(&getCustomRaw), self, org_context)
}
haxorg_NamedPropertyCustomRaw org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCustomRawMut(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::CustomRaw&(*)()>(&getCustomRaw), self, org_context)
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isCustomId_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(*)() const>(&isCustomId), self, org_context)
}
haxorg_NamedPropertyCustomId org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCustomIdConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::CustomId const&(*)() const>(&getCustomId), self, org_context)
}
haxorg_NamedPropertyCustomId org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCustomIdMut(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::CustomId&(*)()>(&getCustomId), self, org_context)
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isCustomSubtreeJson_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(*)() const>(&isCustomSubtreeJson), self, org_context)
}
haxorg_NamedPropertyCustomSubtreeJson org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCustomSubtreeJsonConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::CustomSubtreeJson const&(*)() const>(&getCustomSubtreeJson), self, org_context)
}
haxorg_NamedPropertyCustomSubtreeJson org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCustomSubtreeJsonMut(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::CustomSubtreeJson&(*)()>(&getCustomSubtreeJson), self, org_context)
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isCustomSubtreeFlags_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(*)() const>(&isCustomSubtreeFlags), self, org_context)
}
haxorg_NamedPropertyCustomSubtreeFlags org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCustomSubtreeFlagsConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::CustomSubtreeFlags const&(*)() const>(&getCustomSubtreeFlags), self, org_context)
}
haxorg_NamedPropertyCustomSubtreeFlags org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCustomSubtreeFlagsMut(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::CustomSubtreeFlags&(*)()>(&getCustomSubtreeFlags), self, org_context)
}
haxorg_NamedPropertyKind org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getKind_const(haxorg_NamedProperty self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Kind(*)() const>(&getKind), self, org_context)
}
bool org::bind::c::VTable<haxorg_NamedPropertyNonblocking, haxorg_NamedPropertyNonblocking_vtable>::__eq___const(haxorg_NamedPropertyNonblocking self, OrgContext* org_context, haxorg_NamedPropertyNonblocking other) {
  org::bind::c::execute_cpp<haxorg_NamedPropertyNonblocking, haxorg_NamedPropertyNonblocking_vtable>(static_cast<bool(*)(org::sem::NamedProperty::Nonblocking const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_NamedPropertyArchiveTime, haxorg_NamedPropertyArchiveTime_vtable>::__eq___const(haxorg_NamedPropertyArchiveTime self, OrgContext* org_context, haxorg_NamedPropertyArchiveTime other) {
  org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveTime, haxorg_NamedPropertyArchiveTime_vtable>(static_cast<bool(*)(org::sem::NamedProperty::ArchiveTime const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_NamedPropertyArchiveFile, haxorg_NamedPropertyArchiveFile_vtable>::__eq___const(haxorg_NamedPropertyArchiveFile self, OrgContext* org_context, haxorg_NamedPropertyArchiveFile other) {
  org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveFile, haxorg_NamedPropertyArchiveFile_vtable>(static_cast<bool(*)(org::sem::NamedProperty::ArchiveFile const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_NamedPropertyArchiveOlpath, haxorg_NamedPropertyArchiveOlpath_vtable>::__eq___const(haxorg_NamedPropertyArchiveOlpath self, OrgContext* org_context, haxorg_NamedPropertyArchiveOlpath other) {
  org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveOlpath, haxorg_NamedPropertyArchiveOlpath_vtable>(static_cast<bool(*)(org::sem::NamedProperty::ArchiveOlpath const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_NamedPropertyArchiveTarget, haxorg_NamedPropertyArchiveTarget_vtable>::__eq___const(haxorg_NamedPropertyArchiveTarget self, OrgContext* org_context, haxorg_NamedPropertyArchiveTarget other) {
  org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveTarget, haxorg_NamedPropertyArchiveTarget_vtable>(static_cast<bool(*)(org::sem::NamedProperty::ArchiveTarget const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_NamedPropertyArchiveCategory, haxorg_NamedPropertyArchiveCategory_vtable>::__eq___const(haxorg_NamedPropertyArchiveCategory self, OrgContext* org_context, haxorg_NamedPropertyArchiveCategory other) {
  org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveCategory, haxorg_NamedPropertyArchiveCategory_vtable>(static_cast<bool(*)(org::sem::NamedProperty::ArchiveCategory const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_NamedPropertyArchiveTodo, haxorg_NamedPropertyArchiveTodo_vtable>::__eq___const(haxorg_NamedPropertyArchiveTodo self, OrgContext* org_context, haxorg_NamedPropertyArchiveTodo other) {
  org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveTodo, haxorg_NamedPropertyArchiveTodo_vtable>(static_cast<bool(*)(org::sem::NamedProperty::ArchiveTodo const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_NamedPropertyTrigger, haxorg_NamedPropertyTrigger_vtable>::__eq___const(haxorg_NamedPropertyTrigger self, OrgContext* org_context, haxorg_NamedPropertyTrigger other) {
  org::bind::c::execute_cpp<haxorg_NamedPropertyTrigger, haxorg_NamedPropertyTrigger_vtable>(static_cast<bool(*)(org::sem::NamedProperty::Trigger const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_NamedPropertyExportLatexClass, haxorg_NamedPropertyExportLatexClass_vtable>::__eq___const(haxorg_NamedPropertyExportLatexClass self, OrgContext* org_context, haxorg_NamedPropertyExportLatexClass other) {
  org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexClass, haxorg_NamedPropertyExportLatexClass_vtable>(static_cast<bool(*)(org::sem::NamedProperty::ExportLatexClass const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_NamedPropertyCookieData, haxorg_NamedPropertyCookieData_vtable>::__eq___const(haxorg_NamedPropertyCookieData self, OrgContext* org_context, haxorg_NamedPropertyCookieData other) {
  org::bind::c::execute_cpp<haxorg_NamedPropertyCookieData, haxorg_NamedPropertyCookieData_vtable>(static_cast<bool(*)(org::sem::NamedProperty::CookieData const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_NamedPropertyExportLatexClassOptions, haxorg_NamedPropertyExportLatexClassOptions_vtable>::__eq___const(haxorg_NamedPropertyExportLatexClassOptions self, OrgContext* org_context, haxorg_NamedPropertyExportLatexClassOptions other) {
  org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexClassOptions, haxorg_NamedPropertyExportLatexClassOptions_vtable>(static_cast<bool(*)(org::sem::NamedProperty::ExportLatexClassOptions const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_NamedPropertyExportLatexHeader, haxorg_NamedPropertyExportLatexHeader_vtable>::__eq___const(haxorg_NamedPropertyExportLatexHeader self, OrgContext* org_context, haxorg_NamedPropertyExportLatexHeader other) {
  org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexHeader, haxorg_NamedPropertyExportLatexHeader_vtable>(static_cast<bool(*)(org::sem::NamedProperty::ExportLatexHeader const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_NamedPropertyExportLatexCompiler, haxorg_NamedPropertyExportLatexCompiler_vtable>::__eq___const(haxorg_NamedPropertyExportLatexCompiler self, OrgContext* org_context, haxorg_NamedPropertyExportLatexCompiler other) {
  org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexCompiler, haxorg_NamedPropertyExportLatexCompiler_vtable>(static_cast<bool(*)(org::sem::NamedProperty::ExportLatexCompiler const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_NamedPropertyOrdered, haxorg_NamedPropertyOrdered_vtable>::__eq___const(haxorg_NamedPropertyOrdered self, OrgContext* org_context, haxorg_NamedPropertyOrdered other) {
  org::bind::c::execute_cpp<haxorg_NamedPropertyOrdered, haxorg_NamedPropertyOrdered_vtable>(static_cast<bool(*)(org::sem::NamedProperty::Ordered const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_NamedPropertyEffort, haxorg_NamedPropertyEffort_vtable>::__eq___const(haxorg_NamedPropertyEffort self, OrgContext* org_context, haxorg_NamedPropertyEffort other) {
  org::bind::c::execute_cpp<haxorg_NamedPropertyEffort, haxorg_NamedPropertyEffort_vtable>(static_cast<bool(*)(org::sem::NamedProperty::Effort const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_NamedPropertyVisibility, haxorg_NamedPropertyVisibility_vtable>::__eq___const(haxorg_NamedPropertyVisibility self, OrgContext* org_context, haxorg_NamedPropertyVisibility other) {
  org::bind::c::execute_cpp<haxorg_NamedPropertyVisibility, haxorg_NamedPropertyVisibility_vtable>(static_cast<bool(*)(org::sem::NamedProperty::Visibility const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_NamedPropertyExportOptions, haxorg_NamedPropertyExportOptions_vtable>::__eq___const(haxorg_NamedPropertyExportOptions self, OrgContext* org_context, haxorg_NamedPropertyExportOptions other) {
  org::bind::c::execute_cpp<haxorg_NamedPropertyExportOptions, haxorg_NamedPropertyExportOptions_vtable>(static_cast<bool(*)(org::sem::NamedProperty::ExportOptions const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_NamedPropertyBlocker, haxorg_NamedPropertyBlocker_vtable>::__eq___const(haxorg_NamedPropertyBlocker self, OrgContext* org_context, haxorg_NamedPropertyBlocker other) {
  org::bind::c::execute_cpp<haxorg_NamedPropertyBlocker, haxorg_NamedPropertyBlocker_vtable>(static_cast<bool(*)(org::sem::NamedProperty::Blocker const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_NamedPropertyUnnumbered, haxorg_NamedPropertyUnnumbered_vtable>::__eq___const(haxorg_NamedPropertyUnnumbered self, OrgContext* org_context, haxorg_NamedPropertyUnnumbered other) {
  org::bind::c::execute_cpp<haxorg_NamedPropertyUnnumbered, haxorg_NamedPropertyUnnumbered_vtable>(static_cast<bool(*)(org::sem::NamedProperty::Unnumbered const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_NamedPropertyCreated, haxorg_NamedPropertyCreated_vtable>::__eq___const(haxorg_NamedPropertyCreated self, OrgContext* org_context, haxorg_NamedPropertyCreated other) {
  org::bind::c::execute_cpp<haxorg_NamedPropertyCreated, haxorg_NamedPropertyCreated_vtable>(static_cast<bool(*)(org::sem::NamedProperty::Created const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_NamedPropertyRadioId, haxorg_NamedPropertyRadioId_vtable>::__eq___const(haxorg_NamedPropertyRadioId self, OrgContext* org_context, haxorg_NamedPropertyRadioId other) {
  org::bind::c::execute_cpp<haxorg_NamedPropertyRadioId, haxorg_NamedPropertyRadioId_vtable>(static_cast<bool(*)(org::sem::NamedProperty::RadioId const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_NamedPropertyHashtagDef, haxorg_NamedPropertyHashtagDef_vtable>::__eq___const(haxorg_NamedPropertyHashtagDef self, OrgContext* org_context, haxorg_NamedPropertyHashtagDef other) {
  org::bind::c::execute_cpp<haxorg_NamedPropertyHashtagDef, haxorg_NamedPropertyHashtagDef_vtable>(static_cast<bool(*)(org::sem::NamedProperty::HashtagDef const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_NamedPropertyCustomArgs, haxorg_NamedPropertyCustomArgs_vtable>::__eq___const(haxorg_NamedPropertyCustomArgs self, OrgContext* org_context, haxorg_NamedPropertyCustomArgs other) {
  org::bind::c::execute_cpp<haxorg_NamedPropertyCustomArgs, haxorg_NamedPropertyCustomArgs_vtable>(static_cast<bool(*)(org::sem::NamedProperty::CustomArgs const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_NamedPropertyCustomRaw, haxorg_NamedPropertyCustomRaw_vtable>::__eq___const(haxorg_NamedPropertyCustomRaw self, OrgContext* org_context, haxorg_NamedPropertyCustomRaw other) {
  org::bind::c::execute_cpp<haxorg_NamedPropertyCustomRaw, haxorg_NamedPropertyCustomRaw_vtable>(static_cast<bool(*)(org::sem::NamedProperty::CustomRaw const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_NamedPropertyCustomId, haxorg_NamedPropertyCustomId_vtable>::__eq___const(haxorg_NamedPropertyCustomId self, OrgContext* org_context, haxorg_NamedPropertyCustomId other) {
  org::bind::c::execute_cpp<haxorg_NamedPropertyCustomId, haxorg_NamedPropertyCustomId_vtable>(static_cast<bool(*)(org::sem::NamedProperty::CustomId const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_NamedPropertyCustomSubtreeJson, haxorg_NamedPropertyCustomSubtreeJson_vtable>::__eq___const(haxorg_NamedPropertyCustomSubtreeJson self, OrgContext* org_context, haxorg_NamedPropertyCustomSubtreeJson other) {
  org::bind::c::execute_cpp<haxorg_NamedPropertyCustomSubtreeJson, haxorg_NamedPropertyCustomSubtreeJson_vtable>(static_cast<bool(*)(org::sem::NamedProperty::CustomSubtreeJson const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_NamedPropertyCustomSubtreeFlags, haxorg_NamedPropertyCustomSubtreeFlags_vtable>::__eq___const(haxorg_NamedPropertyCustomSubtreeFlags self, OrgContext* org_context, haxorg_NamedPropertyCustomSubtreeFlags other) {
  org::bind::c::execute_cpp<haxorg_NamedPropertyCustomSubtreeFlags, haxorg_NamedPropertyCustomSubtreeFlags_vtable>(static_cast<bool(*)(org::sem::NamedProperty::CustomSubtreeFlags const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::__eq___const(haxorg_OrgDiagnostics self, OrgContext* org_context, haxorg_OrgDiagnostics other) {
  org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<bool(*)(org::sem::OrgDiagnostics const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::isParseTokenError_const(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<bool(*)() const>(&isParseTokenError), self, org_context)
}
haxorg_OrgDiagnosticsParseTokenError org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getParseTokenErrorConst_const(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<org::sem::OrgDiagnostics::ParseTokenError const&(*)() const>(&getParseTokenError), self, org_context)
}
haxorg_OrgDiagnosticsParseTokenError org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getParseTokenErrorMut(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<org::sem::OrgDiagnostics::ParseTokenError&(*)()>(&getParseTokenError), self, org_context)
}
bool org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::isParseError_const(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<bool(*)() const>(&isParseError), self, org_context)
}
haxorg_OrgDiagnosticsParseError org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getParseErrorConst_const(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<org::sem::OrgDiagnostics::ParseError const&(*)() const>(&getParseError), self, org_context)
}
haxorg_OrgDiagnosticsParseError org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getParseErrorMut(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<org::sem::OrgDiagnostics::ParseError&(*)()>(&getParseError), self, org_context)
}
bool org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::isIncludeError_const(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<bool(*)() const>(&isIncludeError), self, org_context)
}
haxorg_OrgDiagnosticsIncludeError org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getIncludeErrorConst_const(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<org::sem::OrgDiagnostics::IncludeError const&(*)() const>(&getIncludeError), self, org_context)
}
haxorg_OrgDiagnosticsIncludeError org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getIncludeErrorMut(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<org::sem::OrgDiagnostics::IncludeError&(*)()>(&getIncludeError), self, org_context)
}
bool org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::isConvertError_const(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<bool(*)() const>(&isConvertError), self, org_context)
}
haxorg_OrgDiagnosticsConvertError org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getConvertErrorConst_const(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<org::sem::OrgDiagnostics::ConvertError const&(*)() const>(&getConvertError), self, org_context)
}
haxorg_OrgDiagnosticsConvertError org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getConvertErrorMut(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<org::sem::OrgDiagnostics::ConvertError&(*)()>(&getConvertError), self, org_context)
}
bool org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::isInternalError_const(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<bool(*)() const>(&isInternalError), self, org_context)
}
haxorg_OrgDiagnosticsInternalError org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getInternalErrorConst_const(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<org::sem::OrgDiagnostics::InternalError const&(*)() const>(&getInternalError), self, org_context)
}
haxorg_OrgDiagnosticsInternalError org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getInternalErrorMut(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<org::sem::OrgDiagnostics::InternalError&(*)()>(&getInternalError), self, org_context)
}
haxorg_OrgDiagnosticsKind org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getKind_const(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<org::sem::OrgDiagnostics::Kind(*)() const>(&getKind), self, org_context)
}
bool org::bind::c::VTable<haxorg_OrgDiagnosticsParseTokenError, haxorg_OrgDiagnosticsParseTokenError_vtable>::__eq___const(haxorg_OrgDiagnosticsParseTokenError self, OrgContext* org_context, haxorg_OrgDiagnosticsParseTokenError other) {
  org::bind::c::execute_cpp<haxorg_OrgDiagnosticsParseTokenError, haxorg_OrgDiagnosticsParseTokenError_vtable>(static_cast<bool(*)(org::sem::OrgDiagnostics::ParseTokenError const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_OrgDiagnosticsParseError, haxorg_OrgDiagnosticsParseError_vtable>::__eq___const(haxorg_OrgDiagnosticsParseError self, OrgContext* org_context, haxorg_OrgDiagnosticsParseError other) {
  org::bind::c::execute_cpp<haxorg_OrgDiagnosticsParseError, haxorg_OrgDiagnosticsParseError_vtable>(static_cast<bool(*)(org::sem::OrgDiagnostics::ParseError const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_OrgDiagnosticsIncludeError, haxorg_OrgDiagnosticsIncludeError_vtable>::__eq___const(haxorg_OrgDiagnosticsIncludeError self, OrgContext* org_context, haxorg_OrgDiagnosticsIncludeError other) {
  org::bind::c::execute_cpp<haxorg_OrgDiagnosticsIncludeError, haxorg_OrgDiagnosticsIncludeError_vtable>(static_cast<bool(*)(org::sem::OrgDiagnostics::IncludeError const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_OrgDiagnosticsConvertError, haxorg_OrgDiagnosticsConvertError_vtable>::__eq___const(haxorg_OrgDiagnosticsConvertError self, OrgContext* org_context, haxorg_OrgDiagnosticsConvertError other) {
  org::bind::c::execute_cpp<haxorg_OrgDiagnosticsConvertError, haxorg_OrgDiagnosticsConvertError_vtable>(static_cast<bool(*)(org::sem::OrgDiagnostics::ConvertError const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_OrgDiagnosticsInternalError, haxorg_OrgDiagnosticsInternalError_vtable>::__eq___const(haxorg_OrgDiagnosticsInternalError self, OrgContext* org_context, haxorg_OrgDiagnosticsInternalError other) {
  org::bind::c::execute_cpp<haxorg_OrgDiagnosticsInternalError, haxorg_OrgDiagnosticsInternalError_vtable>(static_cast<bool(*)(org::sem::OrgDiagnostics::InternalError const&) const>(&operator==), self, org_context, other)
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getAttached_const(haxorg_Stmt self, OrgContext* org_context, haxorg_HstdOpt kind) {
  org::bind::c::execute_cpp<haxorg_Stmt, haxorg_Stmt_vtable>(static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(*)(hstd::Opt<hstd::Str> const&) const>(&getAttached), self, org_context, kind)
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getCaption_const(haxorg_Stmt self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Stmt, haxorg_Stmt_vtable>(static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(*)() const>(&getCaption), self, org_context)
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getName_const(haxorg_Stmt self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Stmt, haxorg_Stmt_vtable>(static_cast<hstd::Vec<hstd::Str>(*)() const>(&getName), self, org_context)
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getAttrs_const(haxorg_Stmt self, OrgContext* org_context, haxorg_HstdOpt kind) {
  org::bind::c::execute_cpp<haxorg_Stmt, haxorg_Stmt_vtable>(static_cast<hstd::Vec<org::sem::AttrValue>(*)(hstd::Opt<hstd::Str> const&) const>(&getAttrs), self, org_context, kind)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getFirstAttr_const(haxorg_Stmt self, OrgContext* org_context, haxorg_HstdStr kind) {
  org::bind::c::execute_cpp<haxorg_Stmt, haxorg_Stmt_vtable>(static_cast<hstd::Opt<org::sem::AttrValue>(*)(hstd::Str const&) const>(&getFirstAttr), self, org_context, kind)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getFirstAttrString_const(haxorg_Stmt self, OrgContext* org_context, haxorg_HstdStr kind) {
  org::bind::c::execute_cpp<haxorg_Stmt, haxorg_Stmt_vtable>(static_cast<hstd::Opt<hstd::Str>(*)(hstd::Str const&) const>(&getFirstAttrString), self, org_context, kind)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getFirstAttrInt_const(haxorg_Stmt self, OrgContext* org_context, haxorg_HstdStr kind) {
  org::bind::c::execute_cpp<haxorg_Stmt, haxorg_Stmt_vtable>(static_cast<hstd::Opt<int>(*)(hstd::Str const&) const>(&getFirstAttrInt), self, org_context, kind)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getFirstAttrBool_const(haxorg_Stmt self, OrgContext* org_context, haxorg_HstdStr kind) {
  org::bind::c::execute_cpp<haxorg_Stmt, haxorg_Stmt_vtable>(static_cast<hstd::Opt<bool>(*)(hstd::Str const&) const>(&getFirstAttrBool), self, org_context, kind)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getFirstAttrDouble_const(haxorg_Stmt self, OrgContext* org_context, haxorg_HstdStr kind) {
  org::bind::c::execute_cpp<haxorg_Stmt, haxorg_Stmt_vtable>(static_cast<hstd::Opt<double>(*)(hstd::Str const&) const>(&getFirstAttrDouble), self, org_context, kind)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getFirstAttrLisp_const(haxorg_Stmt self, OrgContext* org_context, haxorg_HstdStr kind) {
  org::bind::c::execute_cpp<haxorg_Stmt, haxorg_Stmt_vtable>(static_cast<hstd::Opt<org::sem::AttrValue::LispValue>(*)(hstd::Str const&) const>(&getFirstAttrLisp), self, org_context, kind)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getFirstAttrKind_const(haxorg_Stmt self, OrgContext* org_context, haxorg_HstdStr kind) {
  org::bind::c::execute_cpp<haxorg_Stmt, haxorg_Stmt_vtable>(static_cast<hstd::Opt<org::sem::AttrValue::Kind>(*)(hstd::Str const&) const>(&getFirstAttrKind), self, org_context, kind)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_Leaf, haxorg_Leaf_vtable>::getText_const(haxorg_Leaf self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Leaf, haxorg_Leaf_vtable>(static_cast<hstd::Str(*)() const>(&getText), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getYear_const(haxorg_Time self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Time, haxorg_Time_vtable>(static_cast<hstd::Opt<int>(*)() const>(&getYear), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getMonth_const(haxorg_Time self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Time, haxorg_Time_vtable>(static_cast<hstd::Opt<int>(*)() const>(&getMonth), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getDay_const(haxorg_Time self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Time, haxorg_Time_vtable>(static_cast<hstd::Opt<int>(*)() const>(&getDay), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getHour_const(haxorg_Time self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Time, haxorg_Time_vtable>(static_cast<hstd::Opt<int>(*)() const>(&getHour), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getMinute_const(haxorg_Time self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Time, haxorg_Time_vtable>(static_cast<hstd::Opt<int>(*)() const>(&getMinute), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getSecond_const(haxorg_Time self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Time, haxorg_Time_vtable>(static_cast<hstd::Opt<int>(*)() const>(&getSecond), self, org_context)
}
haxorg_UserTime org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getStaticTime_const(haxorg_Time self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Time, haxorg_Time_vtable>(static_cast<hstd::UserTime(*)() const>(&getStaticTime), self, org_context)
}
bool org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::isStatic_const(haxorg_Time self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Time, haxorg_Time_vtable>(static_cast<bool(*)() const>(&isStatic), self, org_context)
}
haxorg_TimeStatic org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getStaticConst_const(haxorg_Time self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Time, haxorg_Time_vtable>(static_cast<org::sem::Time::Static const&(*)() const>(&getStatic), self, org_context)
}
haxorg_TimeStatic org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getStaticMut(haxorg_Time self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Time, haxorg_Time_vtable>(static_cast<org::sem::Time::Static&(*)()>(&getStatic), self, org_context)
}
bool org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::isDynamic_const(haxorg_Time self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Time, haxorg_Time_vtable>(static_cast<bool(*)() const>(&isDynamic), self, org_context)
}
haxorg_TimeDynamic org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getDynamicConst_const(haxorg_Time self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Time, haxorg_Time_vtable>(static_cast<org::sem::Time::Dynamic const&(*)() const>(&getDynamic), self, org_context)
}
haxorg_TimeDynamic org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getDynamicMut(haxorg_Time self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Time, haxorg_Time_vtable>(static_cast<org::sem::Time::Dynamic&(*)()>(&getDynamic), self, org_context)
}
haxorg_TimeTimeKind org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getTimeKind_const(haxorg_Time self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Time, haxorg_Time_vtable>(static_cast<org::sem::Time::TimeKind(*)() const>(&getTimeKind), self, org_context)
}
bool org::bind::c::VTable<haxorg_TimeRepeat, haxorg_TimeRepeat_vtable>::__eq___const(haxorg_TimeRepeat self, OrgContext* org_context, haxorg_TimeRepeat other) {
  org::bind::c::execute_cpp<haxorg_TimeRepeat, haxorg_TimeRepeat_vtable>(static_cast<bool(*)(org::sem::Time::Repeat const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_TimeStatic, haxorg_TimeStatic_vtable>::__eq___const(haxorg_TimeStatic self, OrgContext* org_context, haxorg_TimeStatic other) {
  org::bind::c::execute_cpp<haxorg_TimeStatic, haxorg_TimeStatic_vtable>(static_cast<bool(*)(org::sem::Time::Static const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_TimeDynamic, haxorg_TimeDynamic_vtable>::__eq___const(haxorg_TimeDynamic self, OrgContext* org_context, haxorg_TimeDynamic other) {
  org::bind::c::execute_cpp<haxorg_TimeDynamic, haxorg_TimeDynamic_vtable>(static_cast<bool(*)(org::sem::Time::Dynamic const&) const>(&operator==), self, org_context, other)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_TimeRange, haxorg_TimeRange_vtable>::getClockedTimeSeconds_const(haxorg_TimeRange self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_TimeRange, haxorg_TimeRange_vtable>(static_cast<hstd::Opt<int64_t>(*)() const>(&getClockedTimeSeconds), self, org_context)
}
void org::bind::c::VTable<haxorg_SubtreeLog, haxorg_SubtreeLog_vtable>::setDescription(haxorg_SubtreeLog self, OrgContext* org_context, haxorg_SemId desc) {
  org::bind::c::execute_cpp<haxorg_SubtreeLog, haxorg_SubtreeLog_vtable>(static_cast<void(*)(org::sem::SemId<org::sem::StmtList>)>(&setDescription), self, org_context, desc)
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Subtree, haxorg_Subtree_vtable>::getTimePeriods_const(haxorg_Subtree self, OrgContext* org_context, haxorg_HstdIntSet kinds) {
  org::bind::c::execute_cpp<haxorg_Subtree, haxorg_Subtree_vtable>(static_cast<hstd::Vec<org::sem::SubtreePeriod>(*)(hstd::IntSet<org::sem::SubtreePeriod::Kind>) const>(&getTimePeriods), self, org_context, kinds)
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Subtree, haxorg_Subtree_vtable>::getProperties_const(haxorg_Subtree self, OrgContext* org_context, haxorg_HstdStr kind, haxorg_HstdOpt subkind) {
  org::bind::c::execute_cpp<haxorg_Subtree, haxorg_Subtree_vtable>(static_cast<hstd::Vec<org::sem::NamedProperty>(*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&getProperties), self, org_context, kind, subkind)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Subtree, haxorg_Subtree_vtable>::getProperty_const(haxorg_Subtree self, OrgContext* org_context, haxorg_HstdStr kind, haxorg_HstdOpt subkind) {
  org::bind::c::execute_cpp<haxorg_Subtree, haxorg_Subtree_vtable>(static_cast<hstd::Opt<org::sem::NamedProperty>(*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&getProperty), self, org_context, kind, subkind)
}
void org::bind::c::VTable<haxorg_Subtree, haxorg_Subtree_vtable>::removeProperty(haxorg_Subtree self, OrgContext* org_context, haxorg_HstdStr kind, haxorg_HstdOpt subkind) {
  org::bind::c::execute_cpp<haxorg_Subtree, haxorg_Subtree_vtable>(static_cast<void(*)(hstd::Str const&, hstd::Opt<hstd::Str> const&)>(&removeProperty), self, org_context, kind, subkind)
}
void org::bind::c::VTable<haxorg_Subtree, haxorg_Subtree_vtable>::setProperty(haxorg_Subtree self, OrgContext* org_context, haxorg_NamedProperty value) {
  org::bind::c::execute_cpp<haxorg_Subtree, haxorg_Subtree_vtable>(static_cast<void(*)(org::sem::NamedProperty const&)>(&setProperty), self, org_context, value)
}
void org::bind::c::VTable<haxorg_Subtree, haxorg_Subtree_vtable>::setPropertyStrValue(haxorg_Subtree self, OrgContext* org_context, haxorg_HstdStr value, haxorg_HstdStr kind, haxorg_HstdOpt subkind) {
  org::bind::c::execute_cpp<haxorg_Subtree, haxorg_Subtree_vtable>(static_cast<void(*)(hstd::Str const&, hstd::Str const&, hstd::Opt<hstd::Str> const&)>(&setPropertyStrValue), self, org_context, value, kind, subkind)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_Subtree, haxorg_Subtree_vtable>::getCleanTitle_const(haxorg_Subtree self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Subtree, haxorg_Subtree_vtable>(static_cast<hstd::Str(*)() const>(&getCleanTitle), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Subtree, haxorg_Subtree_vtable>::getTodoKeyword_const(haxorg_Subtree self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Subtree, haxorg_Subtree_vtable>(static_cast<hstd::Opt<hstd::Str>(*)() const>(&getTodoKeyword), self, org_context)
}
bool org::bind::c::VTable<haxorg_ListItem, haxorg_ListItem_vtable>::isDescriptionItem_const(haxorg_ListItem self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ListItem, haxorg_ListItem_vtable>(static_cast<bool(*)() const>(&isDescriptionItem), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ListItem, haxorg_ListItem_vtable>::getCleanHeader_const(haxorg_ListItem self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ListItem, haxorg_ListItem_vtable>(static_cast<hstd::Opt<hstd::Str>(*)() const>(&getCleanHeader), self, org_context)
}
haxorg_HstdVec org::bind::c::VTable<haxorg_DocumentOptions, haxorg_DocumentOptions_vtable>::getProperties_const(haxorg_DocumentOptions self, OrgContext* org_context, haxorg_HstdStr kind, haxorg_HstdOpt subKind) {
  org::bind::c::execute_cpp<haxorg_DocumentOptions, haxorg_DocumentOptions_vtable>(static_cast<hstd::Vec<org::sem::NamedProperty>(*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&getProperties), self, org_context, kind, subKind)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_DocumentOptions, haxorg_DocumentOptions_vtable>::getProperty_const(haxorg_DocumentOptions self, OrgContext* org_context, haxorg_HstdStr kind, haxorg_HstdOpt subKind) {
  org::bind::c::execute_cpp<haxorg_DocumentOptions, haxorg_DocumentOptions_vtable>(static_cast<hstd::Opt<org::sem::NamedProperty>(*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&getProperty), self, org_context, kind, subKind)
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Document, haxorg_Document_vtable>::getProperties_const(haxorg_Document self, OrgContext* org_context, haxorg_HstdStr kind, haxorg_HstdOpt subKind) {
  org::bind::c::execute_cpp<haxorg_Document, haxorg_Document_vtable>(static_cast<hstd::Vec<org::sem::NamedProperty>(*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&getProperties), self, org_context, kind, subKind)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Document, haxorg_Document_vtable>::getProperty_const(haxorg_Document self, OrgContext* org_context, haxorg_HstdStr kind, haxorg_HstdOpt subKind) {
  org::bind::c::execute_cpp<haxorg_Document, haxorg_Document_vtable>(static_cast<hstd::Opt<org::sem::NamedProperty>(*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&getProperty), self, org_context, kind, subKind)
}
bool org::bind::c::VTable<haxorg_File, haxorg_File_vtable>::isDocument_const(haxorg_File self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_File, haxorg_File_vtable>(static_cast<bool(*)() const>(&isDocument), self, org_context)
}
haxorg_FileDocument org::bind::c::VTable<haxorg_File, haxorg_File_vtable>::getDocumentConst_const(haxorg_File self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_File, haxorg_File_vtable>(static_cast<org::sem::File::Document const&(*)() const>(&getDocument), self, org_context)
}
haxorg_FileDocument org::bind::c::VTable<haxorg_File, haxorg_File_vtable>::getDocumentMut(haxorg_File self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_File, haxorg_File_vtable>(static_cast<org::sem::File::Document&(*)()>(&getDocument), self, org_context)
}
bool org::bind::c::VTable<haxorg_File, haxorg_File_vtable>::isAttachment_const(haxorg_File self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_File, haxorg_File_vtable>(static_cast<bool(*)() const>(&isAttachment), self, org_context)
}
haxorg_FileAttachment org::bind::c::VTable<haxorg_File, haxorg_File_vtable>::getAttachmentConst_const(haxorg_File self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_File, haxorg_File_vtable>(static_cast<org::sem::File::Attachment const&(*)() const>(&getAttachment), self, org_context)
}
haxorg_FileAttachment org::bind::c::VTable<haxorg_File, haxorg_File_vtable>::getAttachmentMut(haxorg_File self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_File, haxorg_File_vtable>(static_cast<org::sem::File::Attachment&(*)()>(&getAttachment), self, org_context)
}
bool org::bind::c::VTable<haxorg_File, haxorg_File_vtable>::isSource_const(haxorg_File self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_File, haxorg_File_vtable>(static_cast<bool(*)() const>(&isSource), self, org_context)
}
haxorg_FileSource org::bind::c::VTable<haxorg_File, haxorg_File_vtable>::getSourceConst_const(haxorg_File self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_File, haxorg_File_vtable>(static_cast<org::sem::File::Source const&(*)() const>(&getSource), self, org_context)
}
haxorg_FileSource org::bind::c::VTable<haxorg_File, haxorg_File_vtable>::getSourceMut(haxorg_File self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_File, haxorg_File_vtable>(static_cast<org::sem::File::Source&(*)()>(&getSource), self, org_context)
}
haxorg_FileKind org::bind::c::VTable<haxorg_File, haxorg_File_vtable>::getFileKind_const(haxorg_File self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_File, haxorg_File_vtable>(static_cast<org::sem::File::Kind(*)() const>(&getFileKind), self, org_context)
}
bool org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::isExample_const(haxorg_CmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<bool(*)() const>(&isExample), self, org_context)
}
haxorg_CmdIncludeExample org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getExampleConst_const(haxorg_CmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<org::sem::CmdInclude::Example const&(*)() const>(&getExample), self, org_context)
}
haxorg_CmdIncludeExample org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getExampleMut(haxorg_CmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<org::sem::CmdInclude::Example&(*)()>(&getExample), self, org_context)
}
bool org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::isExport_const(haxorg_CmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<bool(*)() const>(&isExport), self, org_context)
}
haxorg_CmdIncludeExport org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getExportConst_const(haxorg_CmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<org::sem::CmdInclude::Export const&(*)() const>(&getExport), self, org_context)
}
haxorg_CmdIncludeExport org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getExportMut(haxorg_CmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<org::sem::CmdInclude::Export&(*)()>(&getExport), self, org_context)
}
bool org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::isCustom_const(haxorg_CmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<bool(*)() const>(&isCustom), self, org_context)
}
haxorg_CmdIncludeCustom org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getCustomConst_const(haxorg_CmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<org::sem::CmdInclude::Custom const&(*)() const>(&getCustom), self, org_context)
}
haxorg_CmdIncludeCustom org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getCustomMut(haxorg_CmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<org::sem::CmdInclude::Custom&(*)()>(&getCustom), self, org_context)
}
bool org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::isSrc_const(haxorg_CmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<bool(*)() const>(&isSrc), self, org_context)
}
haxorg_CmdIncludeSrc org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getSrcConst_const(haxorg_CmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<org::sem::CmdInclude::Src const&(*)() const>(&getSrc), self, org_context)
}
haxorg_CmdIncludeSrc org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getSrcMut(haxorg_CmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<org::sem::CmdInclude::Src&(*)()>(&getSrc), self, org_context)
}
bool org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::isOrgDocument_const(haxorg_CmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<bool(*)() const>(&isOrgDocument), self, org_context)
}
haxorg_CmdIncludeOrgDocument org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getOrgDocumentConst_const(haxorg_CmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<org::sem::CmdInclude::OrgDocument const&(*)() const>(&getOrgDocument), self, org_context)
}
haxorg_CmdIncludeOrgDocument org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getOrgDocumentMut(haxorg_CmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<org::sem::CmdInclude::OrgDocument&(*)()>(&getOrgDocument), self, org_context)
}
haxorg_CmdIncludeKind org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getIncludeKind_const(haxorg_CmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<org::sem::CmdInclude::Kind(*)() const>(&getIncludeKind), self, org_context)
}
bool org::bind::c::VTable<haxorg_CmdIncludeIncludeBase, haxorg_CmdIncludeIncludeBase_vtable>::__eq___const(haxorg_CmdIncludeIncludeBase self, OrgContext* org_context, haxorg_CmdIncludeIncludeBase other) {
  org::bind::c::execute_cpp<haxorg_CmdIncludeIncludeBase, haxorg_CmdIncludeIncludeBase_vtable>(static_cast<bool(*)(org::sem::CmdInclude::IncludeBase const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_CmdIncludeExample, haxorg_CmdIncludeExample_vtable>::__eq___const(haxorg_CmdIncludeExample self, OrgContext* org_context, haxorg_CmdIncludeExample other) {
  org::bind::c::execute_cpp<haxorg_CmdIncludeExample, haxorg_CmdIncludeExample_vtable>(static_cast<bool(*)(org::sem::CmdInclude::Example const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_CmdIncludeExport, haxorg_CmdIncludeExport_vtable>::__eq___const(haxorg_CmdIncludeExport self, OrgContext* org_context, haxorg_CmdIncludeExport other) {
  org::bind::c::execute_cpp<haxorg_CmdIncludeExport, haxorg_CmdIncludeExport_vtable>(static_cast<bool(*)(org::sem::CmdInclude::Export const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_CmdIncludeCustom, haxorg_CmdIncludeCustom_vtable>::__eq___const(haxorg_CmdIncludeCustom self, OrgContext* org_context, haxorg_CmdIncludeCustom other) {
  org::bind::c::execute_cpp<haxorg_CmdIncludeCustom, haxorg_CmdIncludeCustom_vtable>(static_cast<bool(*)(org::sem::CmdInclude::Custom const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_CmdIncludeSrc, haxorg_CmdIncludeSrc_vtable>::__eq___const(haxorg_CmdIncludeSrc self, OrgContext* org_context, haxorg_CmdIncludeSrc other) {
  org::bind::c::execute_cpp<haxorg_CmdIncludeSrc, haxorg_CmdIncludeSrc_vtable>(static_cast<bool(*)(org::sem::CmdInclude::Src const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_CmdIncludeOrgDocument, haxorg_CmdIncludeOrgDocument_vtable>::__eq___const(haxorg_CmdIncludeOrgDocument self, OrgContext* org_context, haxorg_CmdIncludeOrgDocument other) {
  org::bind::c::execute_cpp<haxorg_CmdIncludeOrgDocument, haxorg_CmdIncludeOrgDocument_vtable>(static_cast<bool(*)(org::sem::CmdInclude::OrgDocument const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmNoNode, haxorg_ImmNoNode_vtable>::__eq___const(haxorg_ImmNoNode self, OrgContext* org_context, haxorg_ImmNoNode other) {
  org::bind::c::execute_cpp<haxorg_ImmNoNode, haxorg_ImmNoNode_vtable>(static_cast<bool(*)(org::imm::ImmNoNode const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmErrorItem, haxorg_ImmErrorItem_vtable>::__eq___const(haxorg_ImmErrorItem self, OrgContext* org_context, haxorg_ImmErrorItem other) {
  org::bind::c::execute_cpp<haxorg_ImmErrorItem, haxorg_ImmErrorItem_vtable>(static_cast<bool(*)(org::imm::ImmErrorItem const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmErrorGroup, haxorg_ImmErrorGroup_vtable>::__eq___const(haxorg_ImmErrorGroup self, OrgContext* org_context, haxorg_ImmErrorGroup other) {
  org::bind::c::execute_cpp<haxorg_ImmErrorGroup, haxorg_ImmErrorGroup_vtable>(static_cast<bool(*)(org::imm::ImmErrorGroup const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmStmt, haxorg_ImmStmt_vtable>::__eq___const(haxorg_ImmStmt self, OrgContext* org_context, haxorg_ImmStmt other) {
  org::bind::c::execute_cpp<haxorg_ImmStmt, haxorg_ImmStmt_vtable>(static_cast<bool(*)(org::imm::ImmStmt const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmInline, haxorg_ImmInline_vtable>::__eq___const(haxorg_ImmInline self, OrgContext* org_context, haxorg_ImmInline other) {
  org::bind::c::execute_cpp<haxorg_ImmInline, haxorg_ImmInline_vtable>(static_cast<bool(*)(org::imm::ImmInline const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmStmtList, haxorg_ImmStmtList_vtable>::__eq___const(haxorg_ImmStmtList self, OrgContext* org_context, haxorg_ImmStmtList other) {
  org::bind::c::execute_cpp<haxorg_ImmStmtList, haxorg_ImmStmtList_vtable>(static_cast<bool(*)(org::imm::ImmStmtList const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmEmpty, haxorg_ImmEmpty_vtable>::__eq___const(haxorg_ImmEmpty self, OrgContext* org_context, haxorg_ImmEmpty other) {
  org::bind::c::execute_cpp<haxorg_ImmEmpty, haxorg_ImmEmpty_vtable>(static_cast<bool(*)(org::imm::ImmEmpty const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmLeaf, haxorg_ImmLeaf_vtable>::__eq___const(haxorg_ImmLeaf self, OrgContext* org_context, haxorg_ImmLeaf other) {
  org::bind::c::execute_cpp<haxorg_ImmLeaf, haxorg_ImmLeaf_vtable>(static_cast<bool(*)(org::imm::ImmLeaf const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmTime, haxorg_ImmTime_vtable>::__eq___const(haxorg_ImmTime self, OrgContext* org_context, haxorg_ImmTime other) {
  org::bind::c::execute_cpp<haxorg_ImmTime, haxorg_ImmTime_vtable>(static_cast<bool(*)(org::imm::ImmTime const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmTime, haxorg_ImmTime_vtable>::isStatic_const(haxorg_ImmTime self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmTime, haxorg_ImmTime_vtable>(static_cast<bool(*)() const>(&isStatic), self, org_context)
}
haxorg_ImmTimeStatic org::bind::c::VTable<haxorg_ImmTime, haxorg_ImmTime_vtable>::getStaticConst_const(haxorg_ImmTime self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmTime, haxorg_ImmTime_vtable>(static_cast<org::imm::ImmTime::Static const&(*)() const>(&getStatic), self, org_context)
}
haxorg_ImmTimeStatic org::bind::c::VTable<haxorg_ImmTime, haxorg_ImmTime_vtable>::getStaticMut(haxorg_ImmTime self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmTime, haxorg_ImmTime_vtable>(static_cast<org::imm::ImmTime::Static&(*)()>(&getStatic), self, org_context)
}
bool org::bind::c::VTable<haxorg_ImmTime, haxorg_ImmTime_vtable>::isDynamic_const(haxorg_ImmTime self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmTime, haxorg_ImmTime_vtable>(static_cast<bool(*)() const>(&isDynamic), self, org_context)
}
haxorg_ImmTimeDynamic org::bind::c::VTable<haxorg_ImmTime, haxorg_ImmTime_vtable>::getDynamicConst_const(haxorg_ImmTime self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmTime, haxorg_ImmTime_vtable>(static_cast<org::imm::ImmTime::Dynamic const&(*)() const>(&getDynamic), self, org_context)
}
haxorg_ImmTimeDynamic org::bind::c::VTable<haxorg_ImmTime, haxorg_ImmTime_vtable>::getDynamicMut(haxorg_ImmTime self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmTime, haxorg_ImmTime_vtable>(static_cast<org::imm::ImmTime::Dynamic&(*)()>(&getDynamic), self, org_context)
}
haxorg_ImmTimeTimeKind org::bind::c::VTable<haxorg_ImmTime, haxorg_ImmTime_vtable>::getTimeKind_const(haxorg_ImmTime self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmTime, haxorg_ImmTime_vtable>(static_cast<org::imm::ImmTime::TimeKind(*)() const>(&getTimeKind), self, org_context)
}
bool org::bind::c::VTable<haxorg_ImmTimeRepeat, haxorg_ImmTimeRepeat_vtable>::__eq___const(haxorg_ImmTimeRepeat self, OrgContext* org_context, haxorg_ImmTimeRepeat other) {
  org::bind::c::execute_cpp<haxorg_ImmTimeRepeat, haxorg_ImmTimeRepeat_vtable>(static_cast<bool(*)(org::imm::ImmTime::Repeat const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmTimeStatic, haxorg_ImmTimeStatic_vtable>::__eq___const(haxorg_ImmTimeStatic self, OrgContext* org_context, haxorg_ImmTimeStatic other) {
  org::bind::c::execute_cpp<haxorg_ImmTimeStatic, haxorg_ImmTimeStatic_vtable>(static_cast<bool(*)(org::imm::ImmTime::Static const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmTimeDynamic, haxorg_ImmTimeDynamic_vtable>::__eq___const(haxorg_ImmTimeDynamic self, OrgContext* org_context, haxorg_ImmTimeDynamic other) {
  org::bind::c::execute_cpp<haxorg_ImmTimeDynamic, haxorg_ImmTimeDynamic_vtable>(static_cast<bool(*)(org::imm::ImmTime::Dynamic const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmTimeRange, haxorg_ImmTimeRange_vtable>::__eq___const(haxorg_ImmTimeRange self, OrgContext* org_context, haxorg_ImmTimeRange other) {
  org::bind::c::execute_cpp<haxorg_ImmTimeRange, haxorg_ImmTimeRange_vtable>(static_cast<bool(*)(org::imm::ImmTimeRange const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmMacro, haxorg_ImmMacro_vtable>::__eq___const(haxorg_ImmMacro self, OrgContext* org_context, haxorg_ImmMacro other) {
  org::bind::c::execute_cpp<haxorg_ImmMacro, haxorg_ImmMacro_vtable>(static_cast<bool(*)(org::imm::ImmMacro const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmSymbol, haxorg_ImmSymbol_vtable>::__eq___const(haxorg_ImmSymbol self, OrgContext* org_context, haxorg_ImmSymbol other) {
  org::bind::c::execute_cpp<haxorg_ImmSymbol, haxorg_ImmSymbol_vtable>(static_cast<bool(*)(org::imm::ImmSymbol const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmSymbolParam, haxorg_ImmSymbolParam_vtable>::__eq___const(haxorg_ImmSymbolParam self, OrgContext* org_context, haxorg_ImmSymbolParam other) {
  org::bind::c::execute_cpp<haxorg_ImmSymbolParam, haxorg_ImmSymbolParam_vtable>(static_cast<bool(*)(org::imm::ImmSymbol::Param const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmErrorSkipGroup, haxorg_ImmErrorSkipGroup_vtable>::__eq___const(haxorg_ImmErrorSkipGroup self, OrgContext* org_context, haxorg_ImmErrorSkipGroup other) {
  org::bind::c::execute_cpp<haxorg_ImmErrorSkipGroup, haxorg_ImmErrorSkipGroup_vtable>(static_cast<bool(*)(org::imm::ImmErrorSkipGroup const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmMarkup, haxorg_ImmMarkup_vtable>::__eq___const(haxorg_ImmMarkup self, OrgContext* org_context, haxorg_ImmMarkup other) {
  org::bind::c::execute_cpp<haxorg_ImmMarkup, haxorg_ImmMarkup_vtable>(static_cast<bool(*)(org::imm::ImmMarkup const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmRadioTarget, haxorg_ImmRadioTarget_vtable>::__eq___const(haxorg_ImmRadioTarget self, OrgContext* org_context, haxorg_ImmRadioTarget other) {
  org::bind::c::execute_cpp<haxorg_ImmRadioTarget, haxorg_ImmRadioTarget_vtable>(static_cast<bool(*)(org::imm::ImmRadioTarget const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmLatex, haxorg_ImmLatex_vtable>::__eq___const(haxorg_ImmLatex self, OrgContext* org_context, haxorg_ImmLatex other) {
  org::bind::c::execute_cpp<haxorg_ImmLatex, haxorg_ImmLatex_vtable>(static_cast<bool(*)(org::imm::ImmLatex const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmSubtreeLog, haxorg_ImmSubtreeLog_vtable>::__eq___const(haxorg_ImmSubtreeLog self, OrgContext* org_context, haxorg_ImmSubtreeLog other) {
  org::bind::c::execute_cpp<haxorg_ImmSubtreeLog, haxorg_ImmSubtreeLog_vtable>(static_cast<bool(*)(org::imm::ImmSubtreeLog const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmSubtree, haxorg_ImmSubtree_vtable>::__eq___const(haxorg_ImmSubtree self, OrgContext* org_context, haxorg_ImmSubtree other) {
  org::bind::c::execute_cpp<haxorg_ImmSubtree, haxorg_ImmSubtree_vtable>(static_cast<bool(*)(org::imm::ImmSubtree const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmColonExample, haxorg_ImmColonExample_vtable>::__eq___const(haxorg_ImmColonExample self, OrgContext* org_context, haxorg_ImmColonExample other) {
  org::bind::c::execute_cpp<haxorg_ImmColonExample, haxorg_ImmColonExample_vtable>(static_cast<bool(*)(org::imm::ImmColonExample const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmCall, haxorg_ImmCall_vtable>::__eq___const(haxorg_ImmCall self, OrgContext* org_context, haxorg_ImmCall other) {
  org::bind::c::execute_cpp<haxorg_ImmCall, haxorg_ImmCall_vtable>(static_cast<bool(*)(org::imm::ImmCall const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmListItem, haxorg_ImmListItem_vtable>::__eq___const(haxorg_ImmListItem self, OrgContext* org_context, haxorg_ImmListItem other) {
  org::bind::c::execute_cpp<haxorg_ImmListItem, haxorg_ImmListItem_vtable>(static_cast<bool(*)(org::imm::ImmListItem const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmDocumentOptions, haxorg_ImmDocumentOptions_vtable>::__eq___const(haxorg_ImmDocumentOptions self, OrgContext* org_context, haxorg_ImmDocumentOptions other) {
  org::bind::c::execute_cpp<haxorg_ImmDocumentOptions, haxorg_ImmDocumentOptions_vtable>(static_cast<bool(*)(org::imm::ImmDocumentOptions const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmDocumentFragment, haxorg_ImmDocumentFragment_vtable>::__eq___const(haxorg_ImmDocumentFragment self, OrgContext* org_context, haxorg_ImmDocumentFragment other) {
  org::bind::c::execute_cpp<haxorg_ImmDocumentFragment, haxorg_ImmDocumentFragment_vtable>(static_cast<bool(*)(org::imm::ImmDocumentFragment const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmCriticMarkup, haxorg_ImmCriticMarkup_vtable>::__eq___const(haxorg_ImmCriticMarkup self, OrgContext* org_context, haxorg_ImmCriticMarkup other) {
  org::bind::c::execute_cpp<haxorg_ImmCriticMarkup, haxorg_ImmCriticMarkup_vtable>(static_cast<bool(*)(org::imm::ImmCriticMarkup const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmDocument, haxorg_ImmDocument_vtable>::__eq___const(haxorg_ImmDocument self, OrgContext* org_context, haxorg_ImmDocument other) {
  org::bind::c::execute_cpp<haxorg_ImmDocument, haxorg_ImmDocument_vtable>(static_cast<bool(*)(org::imm::ImmDocument const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmFileTarget, haxorg_ImmFileTarget_vtable>::__eq___const(haxorg_ImmFileTarget self, OrgContext* org_context, haxorg_ImmFileTarget other) {
  org::bind::c::execute_cpp<haxorg_ImmFileTarget, haxorg_ImmFileTarget_vtable>(static_cast<bool(*)(org::imm::ImmFileTarget const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmTextSeparator, haxorg_ImmTextSeparator_vtable>::__eq___const(haxorg_ImmTextSeparator self, OrgContext* org_context, haxorg_ImmTextSeparator other) {
  org::bind::c::execute_cpp<haxorg_ImmTextSeparator, haxorg_ImmTextSeparator_vtable>(static_cast<bool(*)(org::imm::ImmTextSeparator const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmDocumentGroup, haxorg_ImmDocumentGroup_vtable>::__eq___const(haxorg_ImmDocumentGroup self, OrgContext* org_context, haxorg_ImmDocumentGroup other) {
  org::bind::c::execute_cpp<haxorg_ImmDocumentGroup, haxorg_ImmDocumentGroup_vtable>(static_cast<bool(*)(org::imm::ImmDocumentGroup const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::__eq___const(haxorg_ImmFile self, OrgContext* org_context, haxorg_ImmFile other) {
  org::bind::c::execute_cpp<haxorg_ImmFile, haxorg_ImmFile_vtable>(static_cast<bool(*)(org::imm::ImmFile const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::isDocument_const(haxorg_ImmFile self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmFile, haxorg_ImmFile_vtable>(static_cast<bool(*)() const>(&isDocument), self, org_context)
}
haxorg_ImmFileDocument org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::getDocumentConst_const(haxorg_ImmFile self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmFile, haxorg_ImmFile_vtable>(static_cast<org::imm::ImmFile::Document const&(*)() const>(&getDocument), self, org_context)
}
haxorg_ImmFileDocument org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::getDocumentMut(haxorg_ImmFile self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmFile, haxorg_ImmFile_vtable>(static_cast<org::imm::ImmFile::Document&(*)()>(&getDocument), self, org_context)
}
bool org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::isAttachment_const(haxorg_ImmFile self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmFile, haxorg_ImmFile_vtable>(static_cast<bool(*)() const>(&isAttachment), self, org_context)
}
haxorg_ImmFileAttachment org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::getAttachmentConst_const(haxorg_ImmFile self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmFile, haxorg_ImmFile_vtable>(static_cast<org::imm::ImmFile::Attachment const&(*)() const>(&getAttachment), self, org_context)
}
haxorg_ImmFileAttachment org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::getAttachmentMut(haxorg_ImmFile self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmFile, haxorg_ImmFile_vtable>(static_cast<org::imm::ImmFile::Attachment&(*)()>(&getAttachment), self, org_context)
}
bool org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::isSource_const(haxorg_ImmFile self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmFile, haxorg_ImmFile_vtable>(static_cast<bool(*)() const>(&isSource), self, org_context)
}
haxorg_ImmFileSource org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::getSourceConst_const(haxorg_ImmFile self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmFile, haxorg_ImmFile_vtable>(static_cast<org::imm::ImmFile::Source const&(*)() const>(&getSource), self, org_context)
}
haxorg_ImmFileSource org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::getSourceMut(haxorg_ImmFile self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmFile, haxorg_ImmFile_vtable>(static_cast<org::imm::ImmFile::Source&(*)()>(&getSource), self, org_context)
}
haxorg_ImmFileKind org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::getFileKind_const(haxorg_ImmFile self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmFile, haxorg_ImmFile_vtable>(static_cast<org::imm::ImmFile::Kind(*)() const>(&getFileKind), self, org_context)
}
bool org::bind::c::VTable<haxorg_ImmFileDocument, haxorg_ImmFileDocument_vtable>::__eq___const(haxorg_ImmFileDocument self, OrgContext* org_context, haxorg_ImmFileDocument other) {
  org::bind::c::execute_cpp<haxorg_ImmFileDocument, haxorg_ImmFileDocument_vtable>(static_cast<bool(*)(org::imm::ImmFile::Document const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmFileAttachment, haxorg_ImmFileAttachment_vtable>::__eq___const(haxorg_ImmFileAttachment self, OrgContext* org_context, haxorg_ImmFileAttachment other) {
  org::bind::c::execute_cpp<haxorg_ImmFileAttachment, haxorg_ImmFileAttachment_vtable>(static_cast<bool(*)(org::imm::ImmFile::Attachment const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmFileSource, haxorg_ImmFileSource_vtable>::__eq___const(haxorg_ImmFileSource self, OrgContext* org_context, haxorg_ImmFileSource other) {
  org::bind::c::execute_cpp<haxorg_ImmFileSource, haxorg_ImmFileSource_vtable>(static_cast<bool(*)(org::imm::ImmFile::Source const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmDirectory, haxorg_ImmDirectory_vtable>::__eq___const(haxorg_ImmDirectory self, OrgContext* org_context, haxorg_ImmDirectory other) {
  org::bind::c::execute_cpp<haxorg_ImmDirectory, haxorg_ImmDirectory_vtable>(static_cast<bool(*)(org::imm::ImmDirectory const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmSymlink, haxorg_ImmSymlink_vtable>::__eq___const(haxorg_ImmSymlink self, OrgContext* org_context, haxorg_ImmSymlink other) {
  org::bind::c::execute_cpp<haxorg_ImmSymlink, haxorg_ImmSymlink_vtable>(static_cast<bool(*)(org::imm::ImmSymlink const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::__eq___const(haxorg_ImmCmdInclude self, OrgContext* org_context, haxorg_ImmCmdInclude other) {
  org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<bool(*)(org::imm::ImmCmdInclude const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::isExample_const(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<bool(*)() const>(&isExample), self, org_context)
}
haxorg_ImmCmdIncludeExample org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getExampleConst_const(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<org::imm::ImmCmdInclude::Example const&(*)() const>(&getExample), self, org_context)
}
haxorg_ImmCmdIncludeExample org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getExampleMut(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<org::imm::ImmCmdInclude::Example&(*)()>(&getExample), self, org_context)
}
bool org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::isExport_const(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<bool(*)() const>(&isExport), self, org_context)
}
haxorg_ImmCmdIncludeExport org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getExportConst_const(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<org::imm::ImmCmdInclude::Export const&(*)() const>(&getExport), self, org_context)
}
haxorg_ImmCmdIncludeExport org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getExportMut(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<org::imm::ImmCmdInclude::Export&(*)()>(&getExport), self, org_context)
}
bool org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::isCustom_const(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<bool(*)() const>(&isCustom), self, org_context)
}
haxorg_ImmCmdIncludeCustom org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getCustomConst_const(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<org::imm::ImmCmdInclude::Custom const&(*)() const>(&getCustom), self, org_context)
}
haxorg_ImmCmdIncludeCustom org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getCustomMut(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<org::imm::ImmCmdInclude::Custom&(*)()>(&getCustom), self, org_context)
}
bool org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::isSrc_const(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<bool(*)() const>(&isSrc), self, org_context)
}
haxorg_ImmCmdIncludeSrc org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getSrcConst_const(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<org::imm::ImmCmdInclude::Src const&(*)() const>(&getSrc), self, org_context)
}
haxorg_ImmCmdIncludeSrc org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getSrcMut(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<org::imm::ImmCmdInclude::Src&(*)()>(&getSrc), self, org_context)
}
bool org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::isOrgDocument_const(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<bool(*)() const>(&isOrgDocument), self, org_context)
}
haxorg_ImmCmdIncludeOrgDocument org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getOrgDocumentConst_const(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<org::imm::ImmCmdInclude::OrgDocument const&(*)() const>(&getOrgDocument), self, org_context)
}
haxorg_ImmCmdIncludeOrgDocument org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getOrgDocumentMut(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<org::imm::ImmCmdInclude::OrgDocument&(*)()>(&getOrgDocument), self, org_context)
}
haxorg_ImmCmdIncludeKind org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getIncludeKind_const(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<org::imm::ImmCmdInclude::Kind(*)() const>(&getIncludeKind), self, org_context)
}
bool org::bind::c::VTable<haxorg_ImmCmdIncludeIncludeBase, haxorg_ImmCmdIncludeIncludeBase_vtable>::__eq___const(haxorg_ImmCmdIncludeIncludeBase self, OrgContext* org_context, haxorg_ImmCmdIncludeIncludeBase other) {
  org::bind::c::execute_cpp<haxorg_ImmCmdIncludeIncludeBase, haxorg_ImmCmdIncludeIncludeBase_vtable>(static_cast<bool(*)(org::imm::ImmCmdInclude::IncludeBase const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmCmdIncludeExample, haxorg_ImmCmdIncludeExample_vtable>::__eq___const(haxorg_ImmCmdIncludeExample self, OrgContext* org_context, haxorg_ImmCmdIncludeExample other) {
  org::bind::c::execute_cpp<haxorg_ImmCmdIncludeExample, haxorg_ImmCmdIncludeExample_vtable>(static_cast<bool(*)(org::imm::ImmCmdInclude::Example const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmCmdIncludeExport, haxorg_ImmCmdIncludeExport_vtable>::__eq___const(haxorg_ImmCmdIncludeExport self, OrgContext* org_context, haxorg_ImmCmdIncludeExport other) {
  org::bind::c::execute_cpp<haxorg_ImmCmdIncludeExport, haxorg_ImmCmdIncludeExport_vtable>(static_cast<bool(*)(org::imm::ImmCmdInclude::Export const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmCmdIncludeCustom, haxorg_ImmCmdIncludeCustom_vtable>::__eq___const(haxorg_ImmCmdIncludeCustom self, OrgContext* org_context, haxorg_ImmCmdIncludeCustom other) {
  org::bind::c::execute_cpp<haxorg_ImmCmdIncludeCustom, haxorg_ImmCmdIncludeCustom_vtable>(static_cast<bool(*)(org::imm::ImmCmdInclude::Custom const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmCmdIncludeSrc, haxorg_ImmCmdIncludeSrc_vtable>::__eq___const(haxorg_ImmCmdIncludeSrc self, OrgContext* org_context, haxorg_ImmCmdIncludeSrc other) {
  org::bind::c::execute_cpp<haxorg_ImmCmdIncludeSrc, haxorg_ImmCmdIncludeSrc_vtable>(static_cast<bool(*)(org::imm::ImmCmdInclude::Src const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmCmdIncludeOrgDocument, haxorg_ImmCmdIncludeOrgDocument_vtable>::__eq___const(haxorg_ImmCmdIncludeOrgDocument self, OrgContext* org_context, haxorg_ImmCmdIncludeOrgDocument other) {
  org::bind::c::execute_cpp<haxorg_ImmCmdIncludeOrgDocument, haxorg_ImmCmdIncludeOrgDocument_vtable>(static_cast<bool(*)(org::imm::ImmCmdInclude::OrgDocument const&) const>(&operator==), self, org_context, other)
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Cmd, haxorg_Cmd_vtable>::getAttrs_const(haxorg_Cmd self, OrgContext* org_context, haxorg_HstdOpt key) {
  org::bind::c::execute_cpp<haxorg_Cmd, haxorg_Cmd_vtable>(static_cast<hstd::Vec<org::sem::AttrValue>(*)(hstd::Opt<hstd::Str> const&) const>(&getAttrs), self, org_context, key)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Cmd, haxorg_Cmd_vtable>::getFirstAttr_const(haxorg_Cmd self, OrgContext* org_context, haxorg_HstdStr kind) {
  org::bind::c::execute_cpp<haxorg_Cmd, haxorg_Cmd_vtable>(static_cast<hstd::Opt<org::sem::AttrValue>(*)(hstd::Str const&) const>(&getFirstAttr), self, org_context, kind)
}
bool org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::isFootnoteDefinition_const(haxorg_Paragraph self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Paragraph, haxorg_Paragraph_vtable>(static_cast<bool(*)() const>(&isFootnoteDefinition), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::getFootnoteName_const(haxorg_Paragraph self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Paragraph, haxorg_Paragraph_vtable>(static_cast<hstd::Opt<hstd::Str>(*)() const>(&getFootnoteName), self, org_context)
}
bool org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::hasAdmonition_const(haxorg_Paragraph self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Paragraph, haxorg_Paragraph_vtable>(static_cast<bool(*)() const>(&hasAdmonition), self, org_context)
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::getAdmonitions_const(haxorg_Paragraph self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Paragraph, haxorg_Paragraph_vtable>(static_cast<hstd::Vec<hstd::Str>(*)() const>(&getAdmonitions), self, org_context)
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::getAdmonitionNodes_const(haxorg_Paragraph self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Paragraph, haxorg_Paragraph_vtable>(static_cast<hstd::Vec<org::sem::SemId<org::sem::BigIdent>>(*)() const>(&getAdmonitionNodes), self, org_context)
}
bool org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::hasTimestamp_const(haxorg_Paragraph self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Paragraph, haxorg_Paragraph_vtable>(static_cast<bool(*)() const>(&hasTimestamp), self, org_context)
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::getTimestamps_const(haxorg_Paragraph self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Paragraph, haxorg_Paragraph_vtable>(static_cast<hstd::Vec<hstd::UserTime>(*)() const>(&getTimestamps), self, org_context)
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::getTimestampNodes_const(haxorg_Paragraph self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Paragraph, haxorg_Paragraph_vtable>(static_cast<hstd::Vec<org::sem::SemId<org::sem::Time>>(*)() const>(&getTimestampNodes), self, org_context)
}
bool org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::hasLeadHashtags_const(haxorg_Paragraph self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Paragraph, haxorg_Paragraph_vtable>(static_cast<bool(*)() const>(&hasLeadHashtags), self, org_context)
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::getLeadHashtags_const(haxorg_Paragraph self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Paragraph, haxorg_Paragraph_vtable>(static_cast<hstd::Vec<org::sem::SemId<org::sem::HashTag>>(*)() const>(&getLeadHashtags), self, org_context)
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::getBody_const(haxorg_Paragraph self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_Paragraph, haxorg_Paragraph_vtable>(static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(*)() const>(&getBody), self, org_context)
}
haxorg_HstdVec org::bind::c::VTable<haxorg_List, haxorg_List_vtable>::getListAttrs_const(haxorg_List self, OrgContext* org_context, haxorg_HstdStr key) {
  org::bind::c::execute_cpp<haxorg_List, haxorg_List_vtable>(static_cast<hstd::Vec<org::sem::AttrValue>(*)(hstd::Str const&) const>(&getListAttrs), self, org_context, key)
}
haxorg_ListFormattingMode org::bind::c::VTable<haxorg_List, haxorg_List_vtable>::getListFormattingMode_const(haxorg_List self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_List, haxorg_List_vtable>(static_cast<ListFormattingMode(*)() const>(&getListFormattingMode), self, org_context)
}
bool org::bind::c::VTable<haxorg_List, haxorg_List_vtable>::isDescriptionList_const(haxorg_List self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_List, haxorg_List_vtable>(static_cast<bool(*)() const>(&isDescriptionList), self, org_context)
}
bool org::bind::c::VTable<haxorg_List, haxorg_List_vtable>::isNumberedList_const(haxorg_List self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_List, haxorg_List_vtable>(static_cast<bool(*)() const>(&isNumberedList), self, org_context)
}
bool org::bind::c::VTable<haxorg_ImmCmd, haxorg_ImmCmd_vtable>::__eq___const(haxorg_ImmCmd self, OrgContext* org_context, haxorg_ImmCmd other) {
  org::bind::c::execute_cpp<haxorg_ImmCmd, haxorg_ImmCmd_vtable>(static_cast<bool(*)(org::imm::ImmCmd const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmCmdCustomRaw, haxorg_ImmCmdCustomRaw_vtable>::__eq___const(haxorg_ImmCmdCustomRaw self, OrgContext* org_context, haxorg_ImmCmdCustomRaw other) {
  org::bind::c::execute_cpp<haxorg_ImmCmdCustomRaw, haxorg_ImmCmdCustomRaw_vtable>(static_cast<bool(*)(org::imm::ImmCmdCustomRaw const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmCmdCustomText, haxorg_ImmCmdCustomText_vtable>::__eq___const(haxorg_ImmCmdCustomText self, OrgContext* org_context, haxorg_ImmCmdCustomText other) {
  org::bind::c::execute_cpp<haxorg_ImmCmdCustomText, haxorg_ImmCmdCustomText_vtable>(static_cast<bool(*)(org::imm::ImmCmdCustomText const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmLink, haxorg_ImmLink_vtable>::__eq___const(haxorg_ImmLink self, OrgContext* org_context, haxorg_ImmLink other) {
  org::bind::c::execute_cpp<haxorg_ImmLink, haxorg_ImmLink_vtable>(static_cast<bool(*)(org::imm::ImmLink const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmBlockComment, haxorg_ImmBlockComment_vtable>::__eq___const(haxorg_ImmBlockComment self, OrgContext* org_context, haxorg_ImmBlockComment other) {
  org::bind::c::execute_cpp<haxorg_ImmBlockComment, haxorg_ImmBlockComment_vtable>(static_cast<bool(*)(org::imm::ImmBlockComment const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmParagraph, haxorg_ImmParagraph_vtable>::__eq___const(haxorg_ImmParagraph self, OrgContext* org_context, haxorg_ImmParagraph other) {
  org::bind::c::execute_cpp<haxorg_ImmParagraph, haxorg_ImmParagraph_vtable>(static_cast<bool(*)(org::imm::ImmParagraph const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmList, haxorg_ImmList_vtable>::__eq___const(haxorg_ImmList self, OrgContext* org_context, haxorg_ImmList other) {
  org::bind::c::execute_cpp<haxorg_ImmList, haxorg_ImmList_vtable>(static_cast<bool(*)(org::imm::ImmList const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmHashTag, haxorg_ImmHashTag_vtable>::__eq___const(haxorg_ImmHashTag self, OrgContext* org_context, haxorg_ImmHashTag other) {
  org::bind::c::execute_cpp<haxorg_ImmHashTag, haxorg_ImmHashTag_vtable>(static_cast<bool(*)(org::imm::ImmHashTag const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmInlineFootnote, haxorg_ImmInlineFootnote_vtable>::__eq___const(haxorg_ImmInlineFootnote self, OrgContext* org_context, haxorg_ImmInlineFootnote other) {
  org::bind::c::execute_cpp<haxorg_ImmInlineFootnote, haxorg_ImmInlineFootnote_vtable>(static_cast<bool(*)(org::imm::ImmInlineFootnote const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmInlineExport, haxorg_ImmInlineExport_vtable>::__eq___const(haxorg_ImmInlineExport self, OrgContext* org_context, haxorg_ImmInlineExport other) {
  org::bind::c::execute_cpp<haxorg_ImmInlineExport, haxorg_ImmInlineExport_vtable>(static_cast<bool(*)(org::imm::ImmInlineExport const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmEscaped, haxorg_ImmEscaped_vtable>::__eq___const(haxorg_ImmEscaped self, OrgContext* org_context, haxorg_ImmEscaped other) {
  org::bind::c::execute_cpp<haxorg_ImmEscaped, haxorg_ImmEscaped_vtable>(static_cast<bool(*)(org::imm::ImmEscaped const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmNewline, haxorg_ImmNewline_vtable>::__eq___const(haxorg_ImmNewline self, OrgContext* org_context, haxorg_ImmNewline other) {
  org::bind::c::execute_cpp<haxorg_ImmNewline, haxorg_ImmNewline_vtable>(static_cast<bool(*)(org::imm::ImmNewline const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmSpace, haxorg_ImmSpace_vtable>::__eq___const(haxorg_ImmSpace self, OrgContext* org_context, haxorg_ImmSpace other) {
  org::bind::c::execute_cpp<haxorg_ImmSpace, haxorg_ImmSpace_vtable>(static_cast<bool(*)(org::imm::ImmSpace const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmWord, haxorg_ImmWord_vtable>::__eq___const(haxorg_ImmWord self, OrgContext* org_context, haxorg_ImmWord other) {
  org::bind::c::execute_cpp<haxorg_ImmWord, haxorg_ImmWord_vtable>(static_cast<bool(*)(org::imm::ImmWord const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmAtMention, haxorg_ImmAtMention_vtable>::__eq___const(haxorg_ImmAtMention self, OrgContext* org_context, haxorg_ImmAtMention other) {
  org::bind::c::execute_cpp<haxorg_ImmAtMention, haxorg_ImmAtMention_vtable>(static_cast<bool(*)(org::imm::ImmAtMention const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmRawText, haxorg_ImmRawText_vtable>::__eq___const(haxorg_ImmRawText self, OrgContext* org_context, haxorg_ImmRawText other) {
  org::bind::c::execute_cpp<haxorg_ImmRawText, haxorg_ImmRawText_vtable>(static_cast<bool(*)(org::imm::ImmRawText const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmPunctuation, haxorg_ImmPunctuation_vtable>::__eq___const(haxorg_ImmPunctuation self, OrgContext* org_context, haxorg_ImmPunctuation other) {
  org::bind::c::execute_cpp<haxorg_ImmPunctuation, haxorg_ImmPunctuation_vtable>(static_cast<bool(*)(org::imm::ImmPunctuation const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmPlaceholder, haxorg_ImmPlaceholder_vtable>::__eq___const(haxorg_ImmPlaceholder self, OrgContext* org_context, haxorg_ImmPlaceholder other) {
  org::bind::c::execute_cpp<haxorg_ImmPlaceholder, haxorg_ImmPlaceholder_vtable>(static_cast<bool(*)(org::imm::ImmPlaceholder const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmBigIdent, haxorg_ImmBigIdent_vtable>::__eq___const(haxorg_ImmBigIdent self, OrgContext* org_context, haxorg_ImmBigIdent other) {
  org::bind::c::execute_cpp<haxorg_ImmBigIdent, haxorg_ImmBigIdent_vtable>(static_cast<bool(*)(org::imm::ImmBigIdent const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmTextTarget, haxorg_ImmTextTarget_vtable>::__eq___const(haxorg_ImmTextTarget self, OrgContext* org_context, haxorg_ImmTextTarget other) {
  org::bind::c::execute_cpp<haxorg_ImmTextTarget, haxorg_ImmTextTarget_vtable>(static_cast<bool(*)(org::imm::ImmTextTarget const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmErrorSkipToken, haxorg_ImmErrorSkipToken_vtable>::__eq___const(haxorg_ImmErrorSkipToken self, OrgContext* org_context, haxorg_ImmErrorSkipToken other) {
  org::bind::c::execute_cpp<haxorg_ImmErrorSkipToken, haxorg_ImmErrorSkipToken_vtable>(static_cast<bool(*)(org::imm::ImmErrorSkipToken const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmBold, haxorg_ImmBold_vtable>::__eq___const(haxorg_ImmBold self, OrgContext* org_context, haxorg_ImmBold other) {
  org::bind::c::execute_cpp<haxorg_ImmBold, haxorg_ImmBold_vtable>(static_cast<bool(*)(org::imm::ImmBold const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmUnderline, haxorg_ImmUnderline_vtable>::__eq___const(haxorg_ImmUnderline self, OrgContext* org_context, haxorg_ImmUnderline other) {
  org::bind::c::execute_cpp<haxorg_ImmUnderline, haxorg_ImmUnderline_vtable>(static_cast<bool(*)(org::imm::ImmUnderline const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmMonospace, haxorg_ImmMonospace_vtable>::__eq___const(haxorg_ImmMonospace self, OrgContext* org_context, haxorg_ImmMonospace other) {
  org::bind::c::execute_cpp<haxorg_ImmMonospace, haxorg_ImmMonospace_vtable>(static_cast<bool(*)(org::imm::ImmMonospace const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmMarkQuote, haxorg_ImmMarkQuote_vtable>::__eq___const(haxorg_ImmMarkQuote self, OrgContext* org_context, haxorg_ImmMarkQuote other) {
  org::bind::c::execute_cpp<haxorg_ImmMarkQuote, haxorg_ImmMarkQuote_vtable>(static_cast<bool(*)(org::imm::ImmMarkQuote const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmVerbatim, haxorg_ImmVerbatim_vtable>::__eq___const(haxorg_ImmVerbatim self, OrgContext* org_context, haxorg_ImmVerbatim other) {
  org::bind::c::execute_cpp<haxorg_ImmVerbatim, haxorg_ImmVerbatim_vtable>(static_cast<bool(*)(org::imm::ImmVerbatim const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmItalic, haxorg_ImmItalic_vtable>::__eq___const(haxorg_ImmItalic self, OrgContext* org_context, haxorg_ImmItalic other) {
  org::bind::c::execute_cpp<haxorg_ImmItalic, haxorg_ImmItalic_vtable>(static_cast<bool(*)(org::imm::ImmItalic const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmStrike, haxorg_ImmStrike_vtable>::__eq___const(haxorg_ImmStrike self, OrgContext* org_context, haxorg_ImmStrike other) {
  org::bind::c::execute_cpp<haxorg_ImmStrike, haxorg_ImmStrike_vtable>(static_cast<bool(*)(org::imm::ImmStrike const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmPar, haxorg_ImmPar_vtable>::__eq___const(haxorg_ImmPar self, OrgContext* org_context, haxorg_ImmPar other) {
  org::bind::c::execute_cpp<haxorg_ImmPar, haxorg_ImmPar_vtable>(static_cast<bool(*)(org::imm::ImmPar const&) const>(&operator==), self, org_context, other)
}
haxorg_StdOptional org::bind::c::VTable<haxorg_ImmAdapterDirectoryAPI, haxorg_ImmAdapterDirectoryAPI_vtable>::getFsSubnode_const(haxorg_ImmAdapterDirectoryAPI self, OrgContext* org_context, haxorg_HstdStr name, bool withPath) {
  org::bind::c::execute_cpp<haxorg_ImmAdapterDirectoryAPI, haxorg_ImmAdapterDirectoryAPI_vtable>(static_cast<std::optional<org::imm::ImmAdapter>(*)(hstd::Str const&, bool) const>(&getFsSubnode), self, org_context, name, withPath)
}
bool org::bind::c::VTable<haxorg_ImmBlock, haxorg_ImmBlock_vtable>::__eq___const(haxorg_ImmBlock self, OrgContext* org_context, haxorg_ImmBlock other) {
  org::bind::c::execute_cpp<haxorg_ImmBlock, haxorg_ImmBlock_vtable>(static_cast<bool(*)(org::imm::ImmBlock const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmLineCommand, haxorg_ImmLineCommand_vtable>::__eq___const(haxorg_ImmLineCommand self, OrgContext* org_context, haxorg_ImmLineCommand other) {
  org::bind::c::execute_cpp<haxorg_ImmLineCommand, haxorg_ImmLineCommand_vtable>(static_cast<bool(*)(org::imm::ImmLineCommand const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmCmdCreator, haxorg_ImmCmdCreator_vtable>::__eq___const(haxorg_ImmCmdCreator self, OrgContext* org_context, haxorg_ImmCmdCreator other) {
  org::bind::c::execute_cpp<haxorg_ImmCmdCreator, haxorg_ImmCmdCreator_vtable>(static_cast<bool(*)(org::imm::ImmCmdCreator const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmCmdAuthor, haxorg_ImmCmdAuthor_vtable>::__eq___const(haxorg_ImmCmdAuthor self, OrgContext* org_context, haxorg_ImmCmdAuthor other) {
  org::bind::c::execute_cpp<haxorg_ImmCmdAuthor, haxorg_ImmCmdAuthor_vtable>(static_cast<bool(*)(org::imm::ImmCmdAuthor const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmCmdEmail, haxorg_ImmCmdEmail_vtable>::__eq___const(haxorg_ImmCmdEmail self, OrgContext* org_context, haxorg_ImmCmdEmail other) {
  org::bind::c::execute_cpp<haxorg_ImmCmdEmail, haxorg_ImmCmdEmail_vtable>(static_cast<bool(*)(org::imm::ImmCmdEmail const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmCmdLanguage, haxorg_ImmCmdLanguage_vtable>::__eq___const(haxorg_ImmCmdLanguage self, OrgContext* org_context, haxorg_ImmCmdLanguage other) {
  org::bind::c::execute_cpp<haxorg_ImmCmdLanguage, haxorg_ImmCmdLanguage_vtable>(static_cast<bool(*)(org::imm::ImmCmdLanguage const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmCmdCustomArgs, haxorg_ImmCmdCustomArgs_vtable>::__eq___const(haxorg_ImmCmdCustomArgs self, OrgContext* org_context, haxorg_ImmCmdCustomArgs other) {
  org::bind::c::execute_cpp<haxorg_ImmCmdCustomArgs, haxorg_ImmCmdCustomArgs_vtable>(static_cast<bool(*)(org::imm::ImmCmdCustomArgs const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmCmdTblfm, haxorg_ImmCmdTblfm_vtable>::__eq___const(haxorg_ImmCmdTblfm self, OrgContext* org_context, haxorg_ImmCmdTblfm other) {
  org::bind::c::execute_cpp<haxorg_ImmCmdTblfm, haxorg_ImmCmdTblfm_vtable>(static_cast<bool(*)(org::imm::ImmCmdTblfm const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmCell, haxorg_ImmCell_vtable>::__eq___const(haxorg_ImmCell self, OrgContext* org_context, haxorg_ImmCell other) {
  org::bind::c::execute_cpp<haxorg_ImmCell, haxorg_ImmCell_vtable>(static_cast<bool(*)(org::imm::ImmCell const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmRow, haxorg_ImmRow_vtable>::__eq___const(haxorg_ImmRow self, OrgContext* org_context, haxorg_ImmRow other) {
  org::bind::c::execute_cpp<haxorg_ImmRow, haxorg_ImmRow_vtable>(static_cast<bool(*)(org::imm::ImmRow const&) const>(&operator==), self, org_context, other)
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmStmtAdapter, haxorg_ImmStmtAdapter_vtable>::getAttached_const(haxorg_ImmStmtAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmStmtAdapter, haxorg_ImmStmtAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg>>(*)() const>(&getAttached), self, org_context)
}
int org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getLevel_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>(static_cast<int(*)() const>(&getLevel), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getTreeId_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>(static_cast<hstd::Opt<hstd::Str> const&(*)() const>(&getTreeId), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getTodo_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>(static_cast<hstd::Opt<hstd::Str> const&(*)() const>(&getTodo), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getCompletion_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>(static_cast<hstd::Opt<org::sem::SubtreeCompletion> const&(*)() const>(&getCompletion), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getDescription_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(*)() const>(&getDescription), self, org_context)
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getTags_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag>>(*)() const>(&getTags), self, org_context)
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getTitle_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>(static_cast<org::imm::ImmAdapter(*)() const>(&getTitle), self, org_context)
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getLogbook_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmSubtreeLog>>(*)() const>(&getLogbook), self, org_context)
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getProperties_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::sem::NamedProperty>(*)() const>(&getProperties), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getClosed_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime>>(*)() const>(&getClosed), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getDeadline_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime>>(*)() const>(&getDeadline), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getScheduled_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime>>(*)() const>(&getScheduled), self, org_context)
}
bool org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getIsComment_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>(static_cast<bool(*)() const>(&getIsComment), self, org_context)
}
bool org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getIsArchived_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>(static_cast<bool(*)() const>(&getIsArchived), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getPriority_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>(static_cast<hstd::Opt<hstd::Str> const&(*)() const>(&getPriority), self, org_context)
}
haxorg_OrgDiagnostics org::bind::c::VTable<haxorg_ImmErrorItemAdapter, haxorg_ImmErrorItemAdapter_vtable>::getDiag_const(haxorg_ImmErrorItemAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmErrorItemAdapter, haxorg_ImmErrorItemAdapter_vtable>(static_cast<org::sem::OrgDiagnostics(*)() const>(&getDiag), self, org_context)
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmErrorGroupAdapter, haxorg_ImmErrorGroupAdapter_vtable>::getDiagnostics_const(haxorg_ImmErrorGroupAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmErrorGroupAdapter, haxorg_ImmErrorGroupAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorItem>>(*)() const>(&getDiagnostics), self, org_context)
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmErrorSkipGroupAdapter, haxorg_ImmErrorSkipGroupAdapter_vtable>::getSkipped_const(haxorg_ImmErrorSkipGroupAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmErrorSkipGroupAdapter, haxorg_ImmErrorSkipGroupAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorSkipToken>>(*)() const>(&getSkipped), self, org_context)
}
bool org::bind::c::VTable<haxorg_ImmTimeAdapter, haxorg_ImmTimeAdapter_vtable>::getIsActive_const(haxorg_ImmTimeAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmTimeAdapter, haxorg_ImmTimeAdapter_vtable>(static_cast<bool(*)() const>(&getIsActive), self, org_context)
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmTimeRangeAdapter, haxorg_ImmTimeRangeAdapter_vtable>::getFrom_const(haxorg_ImmTimeRangeAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmTimeRangeAdapter, haxorg_ImmTimeRangeAdapter_vtable>(static_cast<org::imm::ImmAdapter(*)() const>(&getFrom), self, org_context)
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmTimeRangeAdapter, haxorg_ImmTimeRangeAdapter_vtable>::getTo_const(haxorg_ImmTimeRangeAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmTimeRangeAdapter, haxorg_ImmTimeRangeAdapter_vtable>(static_cast<org::imm::ImmAdapter(*)() const>(&getTo), self, org_context)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmMacroAdapter, haxorg_ImmMacroAdapter_vtable>::getName_const(haxorg_ImmMacroAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmMacroAdapter, haxorg_ImmMacroAdapter_vtable>(static_cast<hstd::Str const&(*)() const>(&getName), self, org_context)
}
haxorg_AttrGroup org::bind::c::VTable<haxorg_ImmMacroAdapter, haxorg_ImmMacroAdapter_vtable>::getAttrs_const(haxorg_ImmMacroAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmMacroAdapter, haxorg_ImmMacroAdapter_vtable>(static_cast<org::sem::AttrGroup(*)() const>(&getAttrs), self, org_context)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmSymbolAdapter, haxorg_ImmSymbolAdapter_vtable>::getName_const(haxorg_ImmSymbolAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmSymbolAdapter, haxorg_ImmSymbolAdapter_vtable>(static_cast<hstd::Str const&(*)() const>(&getName), self, org_context)
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmSymbolAdapter, haxorg_ImmSymbolAdapter_vtable>::getParameters_const(haxorg_ImmSymbolAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmSymbolAdapter, haxorg_ImmSymbolAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmSymbol::Param>(*)() const>(&getParameters), self, org_context)
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmSymbolAdapter, haxorg_ImmSymbolAdapter_vtable>::getPositional_const(haxorg_ImmSymbolAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmSymbolAdapter, haxorg_ImmSymbolAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg>>(*)() const>(&getPositional), self, org_context)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmLeafAdapter, haxorg_ImmLeafAdapter_vtable>::getText_const(haxorg_ImmLeafAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmLeafAdapter, haxorg_ImmLeafAdapter_vtable>(static_cast<hstd::Str const&(*)() const>(&getText), self, org_context)
}
haxorg_SubtreeLogHead org::bind::c::VTable<haxorg_ImmSubtreeLogAdapter, haxorg_ImmSubtreeLogAdapter_vtable>::getHead_const(haxorg_ImmSubtreeLogAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmSubtreeLogAdapter, haxorg_ImmSubtreeLogAdapter_vtable>(static_cast<org::sem::SubtreeLogHead(*)() const>(&getHead), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmSubtreeLogAdapter, haxorg_ImmSubtreeLogAdapter_vtable>::getDesc_const(haxorg_ImmSubtreeLogAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmSubtreeLogAdapter, haxorg_ImmSubtreeLogAdapter_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmStmtList>>(*)() const>(&getDesc), self, org_context)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCallAdapter, haxorg_ImmCallAdapter_vtable>::getName_const(haxorg_ImmCallAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCallAdapter, haxorg_ImmCallAdapter_vtable>(static_cast<hstd::Str const&(*)() const>(&getName), self, org_context)
}
haxorg_AttrGroup org::bind::c::VTable<haxorg_ImmCallAdapter, haxorg_ImmCallAdapter_vtable>::getAttrs_const(haxorg_ImmCallAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCallAdapter, haxorg_ImmCallAdapter_vtable>(static_cast<org::sem::AttrGroup(*)() const>(&getAttrs), self, org_context)
}
bool org::bind::c::VTable<haxorg_ImmCallAdapter, haxorg_ImmCallAdapter_vtable>::getIsCommand_const(haxorg_ImmCallAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCallAdapter, haxorg_ImmCallAdapter_vtable>(static_cast<bool(*)() const>(&getIsCommand), self, org_context)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmFileAdapter, haxorg_ImmFileAdapter_vtable>::getRelPath_const(haxorg_ImmFileAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmFileAdapter, haxorg_ImmFileAdapter_vtable>(static_cast<hstd::Str const&(*)() const>(&getRelPath), self, org_context)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmFileAdapter, haxorg_ImmFileAdapter_vtable>::getAbsPath_const(haxorg_ImmFileAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmFileAdapter, haxorg_ImmFileAdapter_vtable>(static_cast<hstd::Str const&(*)() const>(&getAbsPath), self, org_context)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmDirectoryAdapter, haxorg_ImmDirectoryAdapter_vtable>::getRelPath_const(haxorg_ImmDirectoryAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmDirectoryAdapter, haxorg_ImmDirectoryAdapter_vtable>(static_cast<hstd::Str const&(*)() const>(&getRelPath), self, org_context)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmDirectoryAdapter, haxorg_ImmDirectoryAdapter_vtable>::getAbsPath_const(haxorg_ImmDirectoryAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmDirectoryAdapter, haxorg_ImmDirectoryAdapter_vtable>(static_cast<hstd::Str const&(*)() const>(&getAbsPath), self, org_context)
}
bool org::bind::c::VTable<haxorg_ImmSymlinkAdapter, haxorg_ImmSymlinkAdapter_vtable>::getIsDirectory_const(haxorg_ImmSymlinkAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmSymlinkAdapter, haxorg_ImmSymlinkAdapter_vtable>(static_cast<bool(*)() const>(&getIsDirectory), self, org_context)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmSymlinkAdapter, haxorg_ImmSymlinkAdapter_vtable>::getAbsPath_const(haxorg_ImmSymlinkAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmSymlinkAdapter, haxorg_ImmSymlinkAdapter_vtable>(static_cast<hstd::Str const&(*)() const>(&getAbsPath), self, org_context)
}
int org::bind::c::VTable<haxorg_ImmDocumentFragmentAdapter, haxorg_ImmDocumentFragmentAdapter_vtable>::getBaseLine_const(haxorg_ImmDocumentFragmentAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmDocumentFragmentAdapter, haxorg_ImmDocumentFragmentAdapter_vtable>(static_cast<int(*)() const>(&getBaseLine), self, org_context)
}
int org::bind::c::VTable<haxorg_ImmDocumentFragmentAdapter, haxorg_ImmDocumentFragmentAdapter_vtable>::getBaseCol_const(haxorg_ImmDocumentFragmentAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmDocumentFragmentAdapter, haxorg_ImmDocumentFragmentAdapter_vtable>(static_cast<int(*)() const>(&getBaseCol), self, org_context)
}
haxorg_ImmCriticMarkupKind org::bind::c::VTable<haxorg_ImmCriticMarkupAdapter, haxorg_ImmCriticMarkupAdapter_vtable>::getKind_const(haxorg_ImmCriticMarkupAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCriticMarkupAdapter, haxorg_ImmCriticMarkupAdapter_vtable>(static_cast<org::imm::ImmCriticMarkup::Kind(*)() const>(&getKind), self, org_context)
}
haxorg_CheckboxState org::bind::c::VTable<haxorg_ImmListItemAdapter, haxorg_ImmListItemAdapter_vtable>::getCheckbox_const(haxorg_ImmListItemAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmListItemAdapter, haxorg_ImmListItemAdapter_vtable>(static_cast<CheckboxState(*)() const>(&getCheckbox), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmListItemAdapter, haxorg_ImmListItemAdapter_vtable>::getHeader_const(haxorg_ImmListItemAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmListItemAdapter, haxorg_ImmListItemAdapter_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(*)() const>(&getHeader), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmListItemAdapter, haxorg_ImmListItemAdapter_vtable>::getBullet_const(haxorg_ImmListItemAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmListItemAdapter, haxorg_ImmListItemAdapter_vtable>(static_cast<hstd::Opt<hstd::Str> const&(*)() const>(&getBullet), self, org_context)
}
haxorg_InitialSubtreeVisibility org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getInitialVisibility_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>(static_cast<InitialSubtreeVisibility(*)() const>(&getInitialVisibility), self, org_context)
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getProperties_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::sem::NamedProperty>(*)() const>(&getProperties), self, org_context)
}
haxorg_DocumentExportConfig org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getExportConfig_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>(static_cast<org::sem::DocumentExportConfig(*)() const>(&getExportConfig), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getFixedWidthSections_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>(static_cast<hstd::Opt<bool> const&(*)() const>(&getFixedWidthSections), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getStartupIndented_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>(static_cast<hstd::Opt<bool> const&(*)() const>(&getStartupIndented), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getCategory_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>(static_cast<hstd::Opt<hstd::Str> const&(*)() const>(&getCategory), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getSetupfile_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>(static_cast<hstd::Opt<hstd::Str> const&(*)() const>(&getSetupfile), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getMaxSubtreeLevelExport_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>(static_cast<hstd::Opt<int> const&(*)() const>(&getMaxSubtreeLevelExport), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getColumns_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>(static_cast<hstd::Opt<org::sem::ColumnView> const&(*)() const>(&getColumns), self, org_context)
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getTodoKeywords_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::sem::TodoKeyword>(*)() const>(&getTodoKeywords), self, org_context)
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getDoneKeywords_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::sem::TodoKeyword>(*)() const>(&getDoneKeywords), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>::getTitle_const(haxorg_ImmDocumentAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(*)() const>(&getTitle), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>::getAuthor_const(haxorg_ImmDocumentAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(*)() const>(&getAuthor), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>::getCreator_const(haxorg_ImmDocumentAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(*)() const>(&getCreator), self, org_context)
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>::getFiletags_const(haxorg_ImmDocumentAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag>>(*)() const>(&getFiletags), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>::getEmail_const(haxorg_ImmDocumentAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmRawText>>(*)() const>(&getEmail), self, org_context)
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>::getLanguage_const(haxorg_ImmDocumentAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>(static_cast<hstd::ext::ImmVec<hstd::Str>(*)() const>(&getLanguage), self, org_context)
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>::getOptions_const(haxorg_ImmDocumentAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>(static_cast<org::imm::ImmAdapter(*)() const>(&getOptions), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>::getExportFileName_const(haxorg_ImmDocumentAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>(static_cast<hstd::Opt<hstd::Str> const&(*)() const>(&getExportFileName), self, org_context)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable>::getPath_const(haxorg_ImmFileTargetAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable>(static_cast<hstd::Str const&(*)() const>(&getPath), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable>::getLine_const(haxorg_ImmFileTargetAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable>(static_cast<hstd::Opt<int> const&(*)() const>(&getLine), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable>::getSearchTarget_const(haxorg_ImmFileTargetAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable>(static_cast<hstd::Opt<hstd::Str> const&(*)() const>(&getSearchTarget), self, org_context)
}
bool org::bind::c::VTable<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable>::getRestrictToHeadlines_const(haxorg_ImmFileTargetAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable>(static_cast<bool(*)() const>(&getRestrictToHeadlines), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable>::getTargetId_const(haxorg_ImmFileTargetAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable>(static_cast<hstd::Opt<hstd::Str> const&(*)() const>(&getTargetId), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable>::getRegexp_const(haxorg_ImmFileTargetAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable>(static_cast<hstd::Opt<hstd::Str> const&(*)() const>(&getRegexp), self, org_context)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdIncludeAdapter, haxorg_ImmCmdIncludeAdapter_vtable>::getPath_const(haxorg_ImmCmdIncludeAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdIncludeAdapter, haxorg_ImmCmdIncludeAdapter_vtable>(static_cast<hstd::Str const&(*)() const>(&getPath), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmCmdIncludeAdapter, haxorg_ImmCmdIncludeAdapter_vtable>::getFirstLine_const(haxorg_ImmCmdIncludeAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdIncludeAdapter, haxorg_ImmCmdIncludeAdapter_vtable>(static_cast<hstd::Opt<int> const&(*)() const>(&getFirstLine), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmCmdIncludeAdapter, haxorg_ImmCmdIncludeAdapter_vtable>::getLastLine_const(haxorg_ImmCmdIncludeAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdIncludeAdapter, haxorg_ImmCmdIncludeAdapter_vtable>(static_cast<hstd::Opt<int> const&(*)() const>(&getLastLine), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_BlockExport, haxorg_BlockExport_vtable>::getPlacement_const(haxorg_BlockExport self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_BlockExport, haxorg_BlockExport_vtable>(static_cast<hstd::Opt<hstd::Str>(*)() const>(&getPlacement), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_BlockCode, haxorg_BlockCode_vtable>::getVariable_const(haxorg_BlockCode self, OrgContext* org_context, haxorg_HstdStr varname) {
  org::bind::c::execute_cpp<haxorg_BlockCode, haxorg_BlockCode_vtable>(static_cast<hstd::Opt<org::sem::AttrValue>(*)(hstd::Str const&) const>(&getVariable), self, org_context, varname)
}
bool org::bind::c::VTable<haxorg_ImmBlockCenter, haxorg_ImmBlockCenter_vtable>::__eq___const(haxorg_ImmBlockCenter self, OrgContext* org_context, haxorg_ImmBlockCenter other) {
  org::bind::c::execute_cpp<haxorg_ImmBlockCenter, haxorg_ImmBlockCenter_vtable>(static_cast<bool(*)(org::imm::ImmBlockCenter const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmBlockQuote, haxorg_ImmBlockQuote_vtable>::__eq___const(haxorg_ImmBlockQuote self, OrgContext* org_context, haxorg_ImmBlockQuote other) {
  org::bind::c::execute_cpp<haxorg_ImmBlockQuote, haxorg_ImmBlockQuote_vtable>(static_cast<bool(*)(org::imm::ImmBlockQuote const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmBlockVerse, haxorg_ImmBlockVerse_vtable>::__eq___const(haxorg_ImmBlockVerse self, OrgContext* org_context, haxorg_ImmBlockVerse other) {
  org::bind::c::execute_cpp<haxorg_ImmBlockVerse, haxorg_ImmBlockVerse_vtable>(static_cast<bool(*)(org::imm::ImmBlockVerse const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmBlockDynamicFallback, haxorg_ImmBlockDynamicFallback_vtable>::__eq___const(haxorg_ImmBlockDynamicFallback self, OrgContext* org_context, haxorg_ImmBlockDynamicFallback other) {
  org::bind::c::execute_cpp<haxorg_ImmBlockDynamicFallback, haxorg_ImmBlockDynamicFallback_vtable>(static_cast<bool(*)(org::imm::ImmBlockDynamicFallback const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmBlockExample, haxorg_ImmBlockExample_vtable>::__eq___const(haxorg_ImmBlockExample self, OrgContext* org_context, haxorg_ImmBlockExample other) {
  org::bind::c::execute_cpp<haxorg_ImmBlockExample, haxorg_ImmBlockExample_vtable>(static_cast<bool(*)(org::imm::ImmBlockExample const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmBlockExport, haxorg_ImmBlockExport_vtable>::__eq___const(haxorg_ImmBlockExport self, OrgContext* org_context, haxorg_ImmBlockExport other) {
  org::bind::c::execute_cpp<haxorg_ImmBlockExport, haxorg_ImmBlockExport_vtable>(static_cast<bool(*)(org::imm::ImmBlockExport const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmBlockAdmonition, haxorg_ImmBlockAdmonition_vtable>::__eq___const(haxorg_ImmBlockAdmonition self, OrgContext* org_context, haxorg_ImmBlockAdmonition other) {
  org::bind::c::execute_cpp<haxorg_ImmBlockAdmonition, haxorg_ImmBlockAdmonition_vtable>(static_cast<bool(*)(org::imm::ImmBlockAdmonition const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmBlockCodeEvalResult, haxorg_ImmBlockCodeEvalResult_vtable>::__eq___const(haxorg_ImmBlockCodeEvalResult self, OrgContext* org_context, haxorg_ImmBlockCodeEvalResult other) {
  org::bind::c::execute_cpp<haxorg_ImmBlockCodeEvalResult, haxorg_ImmBlockCodeEvalResult_vtable>(static_cast<bool(*)(org::imm::ImmBlockCodeEvalResult const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmBlockCode, haxorg_ImmBlockCode_vtable>::__eq___const(haxorg_ImmBlockCode self, OrgContext* org_context, haxorg_ImmBlockCode other) {
  org::bind::c::execute_cpp<haxorg_ImmBlockCode, haxorg_ImmBlockCode_vtable>(static_cast<bool(*)(org::imm::ImmBlockCode const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmTable, haxorg_ImmTable_vtable>::__eq___const(haxorg_ImmTable self, OrgContext* org_context, haxorg_ImmTable other) {
  org::bind::c::execute_cpp<haxorg_ImmTable, haxorg_ImmTable_vtable>(static_cast<bool(*)(org::imm::ImmTable const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmAttached, haxorg_ImmAttached_vtable>::__eq___const(haxorg_ImmAttached self, OrgContext* org_context, haxorg_ImmAttached other) {
  org::bind::c::execute_cpp<haxorg_ImmAttached, haxorg_ImmAttached_vtable>(static_cast<bool(*)(org::imm::ImmAttached const&) const>(&operator==), self, org_context, other)
}
haxorg_AttrGroup org::bind::c::VTable<haxorg_ImmCmdAdapter, haxorg_ImmCmdAdapter_vtable>::getAttrs_const(haxorg_ImmCmdAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdAdapter, haxorg_ImmCmdAdapter_vtable>(static_cast<org::sem::AttrGroup(*)() const>(&getAttrs), self, org_context)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdCustomRawAdapter, haxorg_ImmCmdCustomRawAdapter_vtable>::getName_const(haxorg_ImmCmdCustomRawAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdCustomRawAdapter, haxorg_ImmCmdCustomRawAdapter_vtable>(static_cast<hstd::Str const&(*)() const>(&getName), self, org_context)
}
bool org::bind::c::VTable<haxorg_ImmCmdCustomRawAdapter, haxorg_ImmCmdCustomRawAdapter_vtable>::getIsAttached_const(haxorg_ImmCmdCustomRawAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdCustomRawAdapter, haxorg_ImmCmdCustomRawAdapter_vtable>(static_cast<bool(*)() const>(&getIsAttached), self, org_context)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdCustomRawAdapter, haxorg_ImmCmdCustomRawAdapter_vtable>::getText_const(haxorg_ImmCmdCustomRawAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdCustomRawAdapter, haxorg_ImmCmdCustomRawAdapter_vtable>(static_cast<hstd::Str const&(*)() const>(&getText), self, org_context)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdCustomTextAdapter, haxorg_ImmCmdCustomTextAdapter_vtable>::getName_const(haxorg_ImmCmdCustomTextAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdCustomTextAdapter, haxorg_ImmCmdCustomTextAdapter_vtable>(static_cast<hstd::Str const&(*)() const>(&getName), self, org_context)
}
bool org::bind::c::VTable<haxorg_ImmCmdCustomTextAdapter, haxorg_ImmCmdCustomTextAdapter_vtable>::getIsAttached_const(haxorg_ImmCmdCustomTextAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdCustomTextAdapter, haxorg_ImmCmdCustomTextAdapter_vtable>(static_cast<bool(*)() const>(&getIsAttached), self, org_context)
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmCmdCustomTextAdapter, haxorg_ImmCmdCustomTextAdapter_vtable>::getText_const(haxorg_ImmCmdCustomTextAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdCustomTextAdapter, haxorg_ImmCmdCustomTextAdapter_vtable>(static_cast<org::imm::ImmAdapter(*)() const>(&getText), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmLinkAdapter, haxorg_ImmLinkAdapter_vtable>::getDescription_const(haxorg_ImmLinkAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmLinkAdapter, haxorg_ImmLinkAdapter_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(*)() const>(&getDescription), self, org_context)
}
haxorg_LinkTarget org::bind::c::VTable<haxorg_ImmLinkAdapter, haxorg_ImmLinkAdapter_vtable>::getTarget_const(haxorg_ImmLinkAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmLinkAdapter, haxorg_ImmLinkAdapter_vtable>(static_cast<org::sem::LinkTarget(*)() const>(&getTarget), self, org_context)
}
haxorg_HashTagText org::bind::c::VTable<haxorg_ImmHashTagAdapter, haxorg_ImmHashTagAdapter_vtable>::getText_const(haxorg_ImmHashTagAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmHashTagAdapter, haxorg_ImmHashTagAdapter_vtable>(static_cast<org::sem::HashTagText(*)() const>(&getText), self, org_context)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmInlineFootnoteAdapter, haxorg_ImmInlineFootnoteAdapter_vtable>::getTag_const(haxorg_ImmInlineFootnoteAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmInlineFootnoteAdapter, haxorg_ImmInlineFootnoteAdapter_vtable>(static_cast<hstd::Str const&(*)() const>(&getTag), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmInlineFootnoteAdapter, haxorg_ImmInlineFootnoteAdapter_vtable>::getDefinition_const(haxorg_ImmInlineFootnoteAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmInlineFootnoteAdapter, haxorg_ImmInlineFootnoteAdapter_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapter>(*)() const>(&getDefinition), self, org_context)
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmRadioTargetAdapter, haxorg_ImmRadioTargetAdapter_vtable>::getWords_const(haxorg_ImmRadioTargetAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmRadioTargetAdapter, haxorg_ImmRadioTargetAdapter_vtable>(static_cast<hstd::ext::ImmVec<hstd::Str>(*)() const>(&getWords), self, org_context)
}
bool org::bind::c::VTable<haxorg_ImmCmdCaption, haxorg_ImmCmdCaption_vtable>::__eq___const(haxorg_ImmCmdCaption self, OrgContext* org_context, haxorg_ImmCmdCaption other) {
  org::bind::c::execute_cpp<haxorg_ImmCmdCaption, haxorg_ImmCmdCaption_vtable>(static_cast<bool(*)(org::imm::ImmCmdCaption const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmCmdColumns, haxorg_ImmCmdColumns_vtable>::__eq___const(haxorg_ImmCmdColumns self, OrgContext* org_context, haxorg_ImmCmdColumns other) {
  org::bind::c::execute_cpp<haxorg_ImmCmdColumns, haxorg_ImmCmdColumns_vtable>(static_cast<bool(*)(org::imm::ImmCmdColumns const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmCmdName, haxorg_ImmCmdName_vtable>::__eq___const(haxorg_ImmCmdName self, OrgContext* org_context, haxorg_ImmCmdName other) {
  org::bind::c::execute_cpp<haxorg_ImmCmdName, haxorg_ImmCmdName_vtable>(static_cast<bool(*)(org::imm::ImmCmdName const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmCmdCall, haxorg_ImmCmdCall_vtable>::__eq___const(haxorg_ImmCmdCall self, OrgContext* org_context, haxorg_ImmCmdCall other) {
  org::bind::c::execute_cpp<haxorg_ImmCmdCall, haxorg_ImmCmdCall_vtable>(static_cast<bool(*)(org::imm::ImmCmdCall const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmCmdAttr, haxorg_ImmCmdAttr_vtable>::__eq___const(haxorg_ImmCmdAttr self, OrgContext* org_context, haxorg_ImmCmdAttr other) {
  org::bind::c::execute_cpp<haxorg_ImmCmdAttr, haxorg_ImmCmdAttr_vtable>(static_cast<bool(*)(org::imm::ImmCmdAttr const&) const>(&operator==), self, org_context, other)
}
bool org::bind::c::VTable<haxorg_ImmCmdExport, haxorg_ImmCmdExport_vtable>::__eq___const(haxorg_ImmCmdExport self, OrgContext* org_context, haxorg_ImmCmdExport other) {
  org::bind::c::execute_cpp<haxorg_ImmCmdExport, haxorg_ImmCmdExport_vtable>(static_cast<bool(*)(org::imm::ImmCmdExport const&) const>(&operator==), self, org_context, other)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdCustomArgsAdapter, haxorg_ImmCmdCustomArgsAdapter_vtable>::getName_const(haxorg_ImmCmdCustomArgsAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdCustomArgsAdapter, haxorg_ImmCmdCustomArgsAdapter_vtable>(static_cast<hstd::Str const&(*)() const>(&getName), self, org_context)
}
bool org::bind::c::VTable<haxorg_ImmCmdCustomArgsAdapter, haxorg_ImmCmdCustomArgsAdapter_vtable>::getIsAttached_const(haxorg_ImmCmdCustomArgsAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdCustomArgsAdapter, haxorg_ImmCmdCustomArgsAdapter_vtable>(static_cast<bool(*)() const>(&getIsAttached), self, org_context)
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmCmdCreatorAdapter, haxorg_ImmCmdCreatorAdapter_vtable>::getText_const(haxorg_ImmCmdCreatorAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdCreatorAdapter, haxorg_ImmCmdCreatorAdapter_vtable>(static_cast<org::imm::ImmAdapter(*)() const>(&getText), self, org_context)
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmCmdAuthorAdapter, haxorg_ImmCmdAuthorAdapter_vtable>::getText_const(haxorg_ImmCmdAuthorAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdAuthorAdapter, haxorg_ImmCmdAuthorAdapter_vtable>(static_cast<org::imm::ImmAdapter(*)() const>(&getText), self, org_context)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdEmailAdapter, haxorg_ImmCmdEmailAdapter_vtable>::getText_const(haxorg_ImmCmdEmailAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdEmailAdapter, haxorg_ImmCmdEmailAdapter_vtable>(static_cast<hstd::Str const&(*)() const>(&getText), self, org_context)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdLanguageAdapter, haxorg_ImmCmdLanguageAdapter_vtable>::getText_const(haxorg_ImmCmdLanguageAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdLanguageAdapter, haxorg_ImmCmdLanguageAdapter_vtable>(static_cast<hstd::Str const&(*)() const>(&getText), self, org_context)
}
haxorg_Tblfm org::bind::c::VTable<haxorg_ImmCmdTblfmAdapter, haxorg_ImmCmdTblfmAdapter_vtable>::getExpr_const(haxorg_ImmCmdTblfmAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdTblfmAdapter, haxorg_ImmCmdTblfmAdapter_vtable>(static_cast<org::sem::Tblfm(*)() const>(&getExpr), self, org_context)
}
bool org::bind::c::VTable<haxorg_ImmCellAdapter, haxorg_ImmCellAdapter_vtable>::getIsBlock_const(haxorg_ImmCellAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCellAdapter, haxorg_ImmCellAdapter_vtable>(static_cast<bool(*)() const>(&getIsBlock), self, org_context)
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmRowAdapter, haxorg_ImmRowAdapter_vtable>::getCells_const(haxorg_ImmRowAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmRowAdapter, haxorg_ImmRowAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmCell>>(*)() const>(&getCells), self, org_context)
}
bool org::bind::c::VTable<haxorg_ImmRowAdapter, haxorg_ImmRowAdapter_vtable>::getIsBlock_const(haxorg_ImmRowAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmRowAdapter, haxorg_ImmRowAdapter_vtable>(static_cast<bool(*)() const>(&getIsBlock), self, org_context)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmInlineExportAdapter, haxorg_ImmInlineExportAdapter_vtable>::getExporter_const(haxorg_ImmInlineExportAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmInlineExportAdapter, haxorg_ImmInlineExportAdapter_vtable>(static_cast<hstd::Str const&(*)() const>(&getExporter), self, org_context)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmInlineExportAdapter, haxorg_ImmInlineExportAdapter_vtable>::getContent_const(haxorg_ImmInlineExportAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmInlineExportAdapter, haxorg_ImmInlineExportAdapter_vtable>(static_cast<hstd::Str const&(*)() const>(&getContent), self, org_context)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdExportAdapter, haxorg_ImmCmdExportAdapter_vtable>::getExporter_const(haxorg_ImmCmdExportAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdExportAdapter, haxorg_ImmCmdExportAdapter_vtable>(static_cast<hstd::Str const&(*)() const>(&getExporter), self, org_context)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdExportAdapter, haxorg_ImmCmdExportAdapter_vtable>::getContent_const(haxorg_ImmCmdExportAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdExportAdapter, haxorg_ImmCmdExportAdapter_vtable>(static_cast<hstd::Str const&(*)() const>(&getContent), self, org_context)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmBlockExportAdapter, haxorg_ImmBlockExportAdapter_vtable>::getExporter_const(haxorg_ImmBlockExportAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmBlockExportAdapter, haxorg_ImmBlockExportAdapter_vtable>(static_cast<hstd::Str const&(*)() const>(&getExporter), self, org_context)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmBlockExportAdapter, haxorg_ImmBlockExportAdapter_vtable>::getContent_const(haxorg_ImmBlockExportAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmBlockExportAdapter, haxorg_ImmBlockExportAdapter_vtable>(static_cast<hstd::Str const&(*)() const>(&getContent), self, org_context)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmBlockDynamicFallbackAdapter, haxorg_ImmBlockDynamicFallbackAdapter_vtable>::getName_const(haxorg_ImmBlockDynamicFallbackAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmBlockDynamicFallbackAdapter, haxorg_ImmBlockDynamicFallbackAdapter_vtable>(static_cast<hstd::Str const&(*)() const>(&getName), self, org_context)
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmBlockCodeEvalResultAdapter, haxorg_ImmBlockCodeEvalResultAdapter_vtable>::getRaw_const(haxorg_ImmBlockCodeEvalResultAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmBlockCodeEvalResultAdapter, haxorg_ImmBlockCodeEvalResultAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::sem::OrgCodeEvalOutput>(*)() const>(&getRaw), self, org_context)
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmBlockCodeEvalResultAdapter, haxorg_ImmBlockCodeEvalResultAdapter_vtable>::getNode_const(haxorg_ImmBlockCodeEvalResultAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmBlockCodeEvalResultAdapter, haxorg_ImmBlockCodeEvalResultAdapter_vtable>(static_cast<org::imm::ImmAdapter(*)() const>(&getNode), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmBlockCodeAdapter, haxorg_ImmBlockCodeAdapter_vtable>::getLang_const(haxorg_ImmBlockCodeAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmBlockCodeAdapter, haxorg_ImmBlockCodeAdapter_vtable>(static_cast<hstd::Opt<hstd::Str> const&(*)() const>(&getLang), self, org_context)
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmBlockCodeAdapter, haxorg_ImmBlockCodeAdapter_vtable>::getResult_const(haxorg_ImmBlockCodeAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmBlockCodeAdapter, haxorg_ImmBlockCodeAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>>(*)() const>(&getResult), self, org_context)
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmBlockCodeAdapter, haxorg_ImmBlockCodeAdapter_vtable>::getLines_const(haxorg_ImmBlockCodeAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmBlockCodeAdapter, haxorg_ImmBlockCodeAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::sem::BlockCodeLine>(*)() const>(&getLines), self, org_context)
}
haxorg_AttrGroup org::bind::c::VTable<haxorg_ImmBlockCodeAdapter, haxorg_ImmBlockCodeAdapter_vtable>::getSwitches_const(haxorg_ImmBlockCodeAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmBlockCodeAdapter, haxorg_ImmBlockCodeAdapter_vtable>(static_cast<org::sem::AttrGroup(*)() const>(&getSwitches), self, org_context)
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmTableAdapter, haxorg_ImmTableAdapter_vtable>::getRows_const(haxorg_ImmTableAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmTableAdapter, haxorg_ImmTableAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmRow>>(*)() const>(&getRows), self, org_context)
}
bool org::bind::c::VTable<haxorg_ImmTableAdapter, haxorg_ImmTableAdapter_vtable>::getIsBlock_const(haxorg_ImmTableAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmTableAdapter, haxorg_ImmTableAdapter_vtable>(static_cast<bool(*)() const>(&getIsBlock), self, org_context)
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmCmdCaptionAdapter, haxorg_ImmCmdCaptionAdapter_vtable>::getText_const(haxorg_ImmCmdCaptionAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdCaptionAdapter, haxorg_ImmCmdCaptionAdapter_vtable>(static_cast<org::imm::ImmAdapter(*)() const>(&getText), self, org_context)
}
haxorg_ColumnView org::bind::c::VTable<haxorg_ImmCmdColumnsAdapter, haxorg_ImmCmdColumnsAdapter_vtable>::getView_const(haxorg_ImmCmdColumnsAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdColumnsAdapter, haxorg_ImmCmdColumnsAdapter_vtable>(static_cast<org::sem::ColumnView(*)() const>(&getView), self, org_context)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdNameAdapter, haxorg_ImmCmdNameAdapter_vtable>::getName_const(haxorg_ImmCmdNameAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdNameAdapter, haxorg_ImmCmdNameAdapter_vtable>(static_cast<hstd::Str const&(*)() const>(&getName), self, org_context)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable>::getName_const(haxorg_ImmCmdCallAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable>(static_cast<hstd::Str const&(*)() const>(&getName), self, org_context)
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable>::getFileName_const(haxorg_ImmCmdCallAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable>(static_cast<hstd::Opt<hstd::Str> const&(*)() const>(&getFileName), self, org_context)
}
haxorg_AttrGroup org::bind::c::VTable<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable>::getInsideHeaderAttrs_const(haxorg_ImmCmdCallAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable>(static_cast<org::sem::AttrGroup(*)() const>(&getInsideHeaderAttrs), self, org_context)
}
haxorg_AttrGroup org::bind::c::VTable<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable>::getCallAttrs_const(haxorg_ImmCmdCallAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable>(static_cast<org::sem::AttrGroup(*)() const>(&getCallAttrs), self, org_context)
}
haxorg_AttrGroup org::bind::c::VTable<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable>::getEndHeaderAttrs_const(haxorg_ImmCmdCallAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable>(static_cast<org::sem::AttrGroup(*)() const>(&getEndHeaderAttrs), self, org_context)
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable>::getResult_const(haxorg_ImmCmdCallAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>>(*)() const>(&getResult), self, org_context)
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdAttrAdapter, haxorg_ImmCmdAttrAdapter_vtable>::getTarget_const(haxorg_ImmCmdAttrAdapter self, OrgContext* org_context) {
  org::bind::c::execute_cpp<haxorg_ImmCmdAttrAdapter, haxorg_ImmCmdAttrAdapter_vtable>(static_cast<hstd::Str const&(*)() const>(&getTarget), self, org_context)
}
/* clang-format on */
