/* clang-format off */
#include <wrappers/c/haxorg_c.h>
#include <wrappers/c/haxorg_c_utils.hpp>
#include <wrappers/c/haxorg_c_vtables.hpp>
#include <wrappers/c/haxorg_c_vtables_manual.hpp>
haxorg_UserTimeBreakdown org::bind::c::VTable<haxorg_UserTime, haxorg_UserTime_vtable>::getBreakdown_const(haxorg_UserTime self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_UserTime, haxorg_UserTime_vtable>(static_cast<hstd::UserTimeBreakdown(hstd::UserTime::*)() const>(&hstd::UserTime::getBreakdown), self, org_context);
}
haxorg_StdString org::bind::c::VTable<haxorg_UserTime, haxorg_UserTime_vtable>::format_const(haxorg_UserTime self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_UserTime, haxorg_UserTime_vtable>(static_cast<std::string(hstd::UserTime::*)() const>(&hstd::UserTime::format), self, org_context);
}
int64_t org::bind::c::VTable<haxorg_UserTime, haxorg_UserTime_vtable>::getTimeDeltaSeconds_const(haxorg_UserTime self, OrgContext* org_context, haxorg_UserTime other) {
  return org::bind::c::execute_cpp<haxorg_UserTime, haxorg_UserTime_vtable>(static_cast<int64_t(hstd::UserTime::*)(hstd::UserTime const&) const>(&hstd::UserTime::getTimeDeltaSeconds), self, org_context, other);
}
int64_t org::bind::c::VTable<haxorg_UserTime, haxorg_UserTime_vtable>::toUnixTimestamp_const(haxorg_UserTime self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_UserTime, haxorg_UserTime_vtable>(static_cast<int64_t(hstd::UserTime::*)() const>(&hstd::UserTime::toUnixTimestamp), self, org_context);
}
haxorg_StdString org::bind::c::VTable<haxorg_ParseSourceManager, haxorg_ParseSourceManager_vtable>::getPath_const(haxorg_ParseSourceManager self, OrgContext* org_context, haxorg_ParseSourceFileId id) {
  return org::bind::c::execute_cpp<haxorg_ParseSourceManager, haxorg_ParseSourceManager_vtable>(static_cast<std::string(org::parse::SourceManager::*)(org::parse::SourceFileId const&) const>(&org::parse::SourceManager::getPath), self, org_context, id);
}
haxorg_ParseSourceFileId org::bind::c::VTable<haxorg_ParseSourceManager, haxorg_ParseSourceManager_vtable>::getId_const(haxorg_ParseSourceManager self, OrgContext* org_context, haxorg_StdString path) {
  return org::bind::c::execute_cpp<haxorg_ParseSourceManager, haxorg_ParseSourceManager_vtable>(static_cast<org::parse::SourceFileId(org::parse::SourceManager::*)(std::string const&) const>(&org::parse::SourceManager::getId), self, org_context, path);
}
haxorg_StdString org::bind::c::VTable<haxorg_ParseSourceManager, haxorg_ParseSourceManager_vtable>::getSourceContent_const(haxorg_ParseSourceManager self, OrgContext* org_context, haxorg_ParseSourceFileId id) {
  return org::bind::c::execute_cpp<haxorg_ParseSourceManager, haxorg_ParseSourceManager_vtable>(static_cast<std::string const&(org::parse::SourceManager::*)(org::parse::SourceFileId const&) const>(&org::parse::SourceManager::getSourceContent), self, org_context, id);
}
haxorg_StdString org::bind::c::VTable<haxorg_ParseSourceManager, haxorg_ParseSourceManager_vtable>::getContentTextForPath_const(haxorg_ParseSourceManager self, OrgContext* org_context, haxorg_StdString path) {
  return org::bind::c::execute_cpp<haxorg_ParseSourceManager, haxorg_ParseSourceManager_vtable>(static_cast<std::string const&(org::parse::SourceManager::*)(std::string const&) const>(&org::parse::SourceManager::getContentTextForPath), self, org_context, path);
}
haxorg_ParseSourceFileId org::bind::c::VTable<haxorg_ParseSourceManager, haxorg_ParseSourceManager_vtable>::addSource(haxorg_ParseSourceManager self, OrgContext* org_context, haxorg_StdString path, haxorg_StdString content) {
  return org::bind::c::execute_cpp<haxorg_ParseSourceManager, haxorg_ParseSourceManager_vtable>(static_cast<org::parse::SourceFileId(org::parse::SourceManager::*)(std::string const&, std::string const&)>(&org::parse::SourceManager::addSource), self, org_context, path, content);
}
haxorg_OrgJsonKind org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::getKind_const(haxorg_OrgJson self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_OrgJson, haxorg_OrgJson_vtable>(static_cast<OrgJsonKind(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getKind), self, org_context);
}
haxorg_StdString org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::getJsonString_const(haxorg_OrgJson self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_OrgJson, haxorg_OrgJson_vtable>(static_cast<std::string(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getJsonString), self, org_context);
}
haxorg_OrgJson org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::atIndex_const(haxorg_OrgJson self, OrgContext* org_context, int idx) {
  return org::bind::c::execute_cpp<haxorg_OrgJson, haxorg_OrgJson_vtable>(static_cast<org::sem::OrgJson(org::sem::OrgJson::*)(int) const>(&org::sem::OrgJson::at), self, org_context, idx);
}
haxorg_OrgJson org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::atField_const(haxorg_OrgJson self, OrgContext* org_context, haxorg_StdString name) {
  return org::bind::c::execute_cpp<haxorg_OrgJson, haxorg_OrgJson_vtable>(static_cast<org::sem::OrgJson(org::sem::OrgJson::*)(std::string const&) const>(&org::sem::OrgJson::at), self, org_context, name);
}
haxorg_StdString org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::getString_const(haxorg_OrgJson self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_OrgJson, haxorg_OrgJson_vtable>(static_cast<std::string(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getString), self, org_context);
}
haxorg_OrgJson org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::getField_const(haxorg_OrgJson self, OrgContext* org_context, haxorg_StdString name) {
  return org::bind::c::execute_cpp<haxorg_OrgJson, haxorg_OrgJson_vtable>(static_cast<org::sem::OrgJson(org::sem::OrgJson::*)(std::string const&) const>(&org::sem::OrgJson::getField), self, org_context, name);
}
haxorg_OrgJson org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::getItem_const(haxorg_OrgJson self, OrgContext* org_context, int index) {
  return org::bind::c::execute_cpp<haxorg_OrgJson, haxorg_OrgJson_vtable>(static_cast<org::sem::OrgJson(org::sem::OrgJson::*)(int) const>(&org::sem::OrgJson::getItem), self, org_context, index);
}
int org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::getInt_const(haxorg_OrgJson self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_OrgJson, haxorg_OrgJson_vtable>(static_cast<int(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getInt), self, org_context);
}
bool org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::getBool_const(haxorg_OrgJson self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_OrgJson, haxorg_OrgJson_vtable>(static_cast<bool(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getBool), self, org_context);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::getArray_const(haxorg_OrgJson self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_OrgJson, haxorg_OrgJson_vtable>(static_cast<hstd::Vec<org::sem::OrgJson>(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getArray), self, org_context);
}
haxorg_StdString org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::dump_const(haxorg_OrgJson self, OrgContext* org_context, int indent) {
  return org::bind::c::execute_cpp<haxorg_OrgJson, haxorg_OrgJson_vtable>(static_cast<std::string(org::sem::OrgJson::*)(int) const>(&org::sem::OrgJson::dump), self, org_context, indent);
}
haxorg_OrgSemKind org::bind::c::VTable<haxorg_Org, haxorg_Org_vtable>::getKind_const(haxorg_Org self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Org, haxorg_Org_vtable>(static_cast<OrgSemKind(org::sem::Org::*)() const>(&org::sem::Org::getKind), self, org_context);
}
void org::bind::c::VTable<haxorg_Org, haxorg_Org_vtable>::push_back(haxorg_Org self, OrgContext* org_context, haxorg_SemId sub) {
  return org::bind::c::execute_cpp<haxorg_Org, haxorg_Org_vtable>(static_cast<void(org::sem::Org::*)(org::sem::SemId<org::sem::Org>)>(&org::sem::Org::push_back), self, org_context, sub);
}
int org::bind::c::VTable<haxorg_Org, haxorg_Org_vtable>::size_const(haxorg_Org self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Org, haxorg_Org_vtable>(static_cast<int(org::sem::Org::*)() const>(&org::sem::Org::size), self, org_context);
}
void org::bind::c::VTable<haxorg_Org, haxorg_Org_vtable>::insert(haxorg_Org self, OrgContext* org_context, int pos, haxorg_SemId node) {
  return org::bind::c::execute_cpp<haxorg_Org, haxorg_Org_vtable>(static_cast<void(org::sem::Org::*)(int, org::sem::SemId<org::sem::Org>)>(&org::sem::Org::insert), self, org_context, pos, node);
}
haxorg_SemId org::bind::c::VTable<haxorg_Org, haxorg_Org_vtable>::at_const(haxorg_Org self, OrgContext* org_context, int idx) {
  return org::bind::c::execute_cpp<haxorg_Org, haxorg_Org_vtable>(static_cast<org::sem::SemId<org::sem::Org>(org::sem::Org::*)(int) const>(&org::sem::Org::at), self, org_context, idx);
}
bool org::bind::c::VTable<haxorg_Org, haxorg_Org_vtable>::is_const(haxorg_Org self, OrgContext* org_context, haxorg_OrgSemKind kind) {
  return org::bind::c::execute_cpp<haxorg_Org, haxorg_Org_vtable>(static_cast<bool(org::sem::Org::*)(OrgSemKind) const>(&org::sem::Org::is), self, org_context, kind);
}
void org::bind::c::VTable<haxorg_OperationsTracer, haxorg_OperationsTracer_vtable>::setTraceFileStr(haxorg_OperationsTracer self, OrgContext* org_context, haxorg_StdString outfile, bool overwrite) {
  return org::bind::c::execute_cpp<haxorg_OperationsTracer, haxorg_OperationsTracer_vtable>(static_cast<void(hstd::OperationsTracer::*)(std::string const&, bool)>(&hstd::OperationsTracer::setTraceFileStr), self, org_context, outfile, overwrite);
}
void org::bind::c::VTable<haxorg_OperationsTracer, haxorg_OperationsTracer_vtable>::sendMessage(haxorg_OperationsTracer self, OrgContext* org_context, haxorg_StdString value, haxorg_StdString function, int line, haxorg_StdString file) {
  return org::bind::c::execute_cpp<haxorg_OperationsTracer, haxorg_OperationsTracer_vtable>(static_cast<void(hstd::OperationsTracer::*)(std::string const&, std::string const&, int, std::string const&)>(&hstd::OperationsTracer::sendMessage), self, org_context, value, function, line, file);
}
haxorg_Cache org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::getDiagnosticStrings(haxorg_ParseContext self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ParseContext, haxorg_ParseContext_vtable>(static_cast<std::shared_ptr<hstd::ext::Cache>(org::parse::ParseContext::*)()>(&org::parse::ParseContext::getDiagnosticStrings), self, org_context);
}
haxorg_ParseSourceFileId org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::addSource_const(haxorg_ParseContext self, OrgContext* org_context, haxorg_StdString path, haxorg_StdString content) {
  return org::bind::c::execute_cpp<haxorg_ParseContext, haxorg_ParseContext_vtable>(static_cast<org::parse::SourceFileId(org::parse::ParseContext::*)(std::string const&, std::string const&) const>(&org::parse::ParseContext::addSource), self, org_context, path, content);
}
haxorg_SemId org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::parseFileOpts(haxorg_ParseContext self, OrgContext* org_context, haxorg_StdString file, haxorg_OrgParseParameters opts) {
  return org::bind::c::execute_cpp<haxorg_ParseContext, haxorg_ParseContext_vtable>(static_cast<org::sem::SemId<org::sem::Org>(org::parse::ParseContext::*)(std::string const&, std::shared_ptr<org::parse::OrgParseParameters> const&)>(&org::parse::ParseContext::parseFileOpts), self, org_context, file, opts);
}
haxorg_SemId org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::parseFile(haxorg_ParseContext self, OrgContext* org_context, haxorg_StdString file) {
  return org::bind::c::execute_cpp<haxorg_ParseContext, haxorg_ParseContext_vtable>(static_cast<org::sem::SemId<org::sem::Org>(org::parse::ParseContext::*)(std::string const&)>(&org::parse::ParseContext::parseFile), self, org_context, file);
}
haxorg_SemId org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::parseString(haxorg_ParseContext self, OrgContext* org_context, haxorg_StdString text, haxorg_StdString file_name) {
  return org::bind::c::execute_cpp<haxorg_ParseContext, haxorg_ParseContext_vtable>(static_cast<org::sem::SemId<org::sem::Org>(org::parse::ParseContext::*)(std::string const&, std::string const&)>(&org::parse::ParseContext::parseString), self, org_context, text, file_name);
}
haxorg_SemId org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::parseStringOpts(haxorg_ParseContext self, OrgContext* org_context, haxorg_StdString text, haxorg_StdString file_name, haxorg_OrgParseParameters opts) {
  return org::bind::c::execute_cpp<haxorg_ParseContext, haxorg_ParseContext_vtable>(static_cast<org::sem::SemId<org::sem::Org>(org::parse::ParseContext::*)(std::string const, std::string const&, std::shared_ptr<org::parse::OrgParseParameters> const&)>(&org::parse::ParseContext::parseStringOpts), self, org_context, text, file_name, opts);
}
haxorg_StdOptional org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::parseDirectory(haxorg_ParseContext self, OrgContext* org_context, haxorg_StdString path) {
  return org::bind::c::execute_cpp<haxorg_ParseContext, haxorg_ParseContext_vtable>(static_cast<std::optional<org::sem::SemId<org::sem::Org>>(org::parse::ParseContext::*)(std::string const&)>(&org::parse::ParseContext::parseDirectory), self, org_context, path);
}
haxorg_StdOptional org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::parseDirectoryOpts(haxorg_ParseContext self, OrgContext* org_context, haxorg_StdString path, haxorg_OrgDirectoryParseParameters opts) {
  return org::bind::c::execute_cpp<haxorg_ParseContext, haxorg_ParseContext_vtable>(static_cast<std::optional<org::sem::SemId<org::sem::Org>>(org::parse::ParseContext::*)(std::string const&, std::shared_ptr<org::parse::OrgDirectoryParseParameters> const&)>(&org::parse::ParseContext::parseDirectoryOpts), self, org_context, path, opts);
}
haxorg_SemId org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::parseFileWithIncludes(haxorg_ParseContext self, OrgContext* org_context, haxorg_StdString file, haxorg_OrgDirectoryParseParameters opts) {
  return org::bind::c::execute_cpp<haxorg_ParseContext, haxorg_ParseContext_vtable>(static_cast<org::sem::SemId<org::sem::File>(org::parse::ParseContext::*)(std::string const&, std::shared_ptr<org::parse::OrgDirectoryParseParameters> const&)>(&org::parse::ParseContext::parseFileWithIncludes), self, org_context, file, opts);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::collectDiagnostics(haxorg_ParseContext self, OrgContext* org_context, haxorg_SemId tree, haxorg_Cache cache) {
  return org::bind::c::execute_cpp<haxorg_ParseContext, haxorg_ParseContext_vtable>(static_cast<hstd::Vec<hstd::ext::Report>(org::parse::ParseContext::*)(org::sem::SemId<org::sem::Org> const&, std::shared_ptr<hstd::ext::Cache> const&)>(&org::parse::ParseContext::collectDiagnostics), self, org_context, tree, cache);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::collectErrorNodes(haxorg_ParseContext self, OrgContext* org_context, haxorg_SemId tree) {
  return org::bind::c::execute_cpp<haxorg_ParseContext, haxorg_ParseContext_vtable>(static_cast<hstd::Vec<org::sem::SemId<org::sem::ErrorGroup>>(org::parse::ParseContext::*)(org::sem::SemId<org::sem::Org> const&)>(&org::parse::ParseContext::collectErrorNodes), self, org_context, tree);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmReflFieldId, haxorg_ImmReflFieldId_vtable>::getName_const(haxorg_ImmReflFieldId self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmReflFieldId, haxorg_ImmReflFieldId_vtable>(static_cast<hstd::Str(org::imm::ImmReflFieldId::*)() const>(&org::imm::ImmReflFieldId::getName), self, org_context);
}
haxorg_OrgSemKind org::bind::c::VTable<haxorg_ImmId, haxorg_ImmId_vtable>::getKind_const(haxorg_ImmId self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmId, haxorg_ImmId_vtable>(static_cast<OrgSemKind(org::imm::ImmId::*)() const>(&org::imm::ImmId::getKind), self, org_context);
}
bool org::bind::c::VTable<haxorg_ImmId, haxorg_ImmId_vtable>::is_const(haxorg_ImmId self, OrgContext* org_context, haxorg_OrgSemKind kind) {
  return org::bind::c::execute_cpp<haxorg_ImmId, haxorg_ImmId_vtable>(static_cast<bool(org::imm::ImmId::*)(OrgSemKind) const>(&org::imm::ImmId::is), self, org_context, kind);
}
haxorg_ImmIdNodeIdxT org::bind::c::VTable<haxorg_ImmId, haxorg_ImmId_vtable>::getNodeIndex_const(haxorg_ImmId self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmId, haxorg_ImmId_vtable>(static_cast<org::imm::ImmId::NodeIdxT(org::imm::ImmId::*)() const>(&org::imm::ImmId::getNodeIndex), self, org_context);
}
haxorg_StdString org::bind::c::VTable<haxorg_ImmId, haxorg_ImmId_vtable>::getReadableId_const(haxorg_ImmId self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmId, haxorg_ImmId_vtable>(static_cast<std::string(org::imm::ImmId::*)() const>(&org::imm::ImmId::getReadableId), self, org_context);
}
bool org::bind::c::VTable<haxorg_ImmPath, haxorg_ImmPath_vtable>::empty_const(haxorg_ImmPath self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmPath, haxorg_ImmPath_vtable>(static_cast<bool(org::imm::ImmPath::*)() const>(&org::imm::ImmPath::empty), self, org_context);
}
haxorg_ImmAstVersion org::bind::c::VTable<haxorg_ImmAstContext, haxorg_ImmAstContext_vtable>::addRoot(haxorg_ImmAstContext self, OrgContext* org_context, haxorg_SemId data) {
  return org::bind::c::execute_cpp<haxorg_ImmAstContext, haxorg_ImmAstContext_vtable>(static_cast<org::imm::ImmAstVersion(org::imm::ImmAstContext::*)(org::sem::SemId<org::sem::Org>)>(&org::imm::ImmAstContext::addRoot), self, org_context, data);
}
haxorg_ImmAstVersion org::bind::c::VTable<haxorg_ImmAstContext, haxorg_ImmAstContext_vtable>::getEmptyVersion(haxorg_ImmAstContext self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmAstContext, haxorg_ImmAstContext_vtable>(static_cast<org::imm::ImmAstVersion(org::imm::ImmAstContext::*)()>(&org::imm::ImmAstContext::getEmptyVersion), self, org_context);
}
haxorg_SemId org::bind::c::VTable<haxorg_ImmAstContext, haxorg_ImmAstContext_vtable>::get(haxorg_ImmAstContext self, OrgContext* org_context, haxorg_ImmId id) {
  return org::bind::c::execute_cpp<haxorg_ImmAstContext, haxorg_ImmAstContext_vtable>(static_cast<org::sem::SemId<org::sem::Org>(org::imm::ImmAstContext::*)(org::imm::ImmId)>(&org::imm::ImmAstContext::get), self, org_context, id);
}
haxorg_ImmId org::bind::c::VTable<haxorg_ImmAstVersion, haxorg_ImmAstVersion_vtable>::getRoot_const(haxorg_ImmAstVersion self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmAstVersion, haxorg_ImmAstVersion_vtable>(static_cast<org::imm::ImmId(org::imm::ImmAstVersion::*)() const>(&org::imm::ImmAstVersion::getRoot), self, org_context);
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmAstVersion, haxorg_ImmAstVersion_vtable>::getRootAdapter_const(haxorg_ImmAstVersion self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmAstVersion, haxorg_ImmAstVersion_vtable>(static_cast<org::imm::ImmAdapter(org::imm::ImmAstVersion::*)() const>(&org::imm::ImmAstVersion::getRootAdapter), self, org_context);
}
haxorg_ImmAstContext org::bind::c::VTable<haxorg_ImmAstVersion, haxorg_ImmAstVersion_vtable>::getContext_const(haxorg_ImmAstVersion self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmAstVersion, haxorg_ImmAstVersion_vtable>(static_cast<std::shared_ptr<org::imm::ImmAstContext>(org::imm::ImmAstVersion::*)() const>(&org::imm::ImmAstVersion::getContext), self, org_context);
}
haxorg_ImmAstReplaceEpoch org::bind::c::VTable<haxorg_ImmAstVersion, haxorg_ImmAstVersion_vtable>::getEpoch_const(haxorg_ImmAstVersion self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmAstVersion, haxorg_ImmAstVersion_vtable>(static_cast<std::shared_ptr<org::imm::ImmAstReplaceEpoch>(org::imm::ImmAstVersion::*)() const>(&org::imm::ImmAstVersion::getEpoch), self, org_context);
}
int org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::size_const(haxorg_ImmAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<int(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::size), self, org_context);
}
bool org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::isNil_const(haxorg_ImmAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<bool(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::isNil), self, org_context);
}
bool org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::isRoot_const(haxorg_ImmAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<bool(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::isRoot), self, org_context);
}
haxorg_OrgSemKind org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::getKind_const(haxorg_ImmAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<OrgSemKind(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::getKind), self, org_context);
}
haxorg_ImmUniqId org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::uniq_const(haxorg_ImmAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<org::imm::ImmUniqId(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::uniq), self, org_context);
}
haxorg_StdString org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::treeReprString_const(haxorg_ImmAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<std::string(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::treeReprString), self, org_context);
}
haxorg_StdString org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::treeReprStringOpts_const(haxorg_ImmAdapter self, OrgContext* org_context, haxorg_ImmAdapterTreeReprConf conf) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<std::string(org::imm::ImmAdapter::*)(org::imm::ImmAdapter::TreeReprConf const&) const>(&org::imm::ImmAdapter::treeReprStringOpts), self, org_context, conf);
}
bool org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::isDirectParentOf_const(haxorg_ImmAdapter self, OrgContext* org_context, haxorg_ImmAdapter other) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<bool(org::imm::ImmAdapter::*)(org::imm::ImmAdapter const&) const>(&org::imm::ImmAdapter::isDirectParentOf), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::isIndirectParentOf_const(haxorg_ImmAdapter self, OrgContext* org_context, haxorg_ImmAdapter other) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<bool(org::imm::ImmAdapter::*)(org::imm::ImmAdapter const&) const>(&org::imm::ImmAdapter::isIndirectParentOf), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::isSubnodeOf_const(haxorg_ImmAdapter self, OrgContext* org_context, haxorg_ImmAdapter other) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<bool(org::imm::ImmAdapter::*)(org::imm::ImmAdapter const&) const>(&org::imm::ImmAdapter::isSubnodeOf), self, org_context, other);
}
haxorg_StdOptional org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::getParent_const(haxorg_ImmAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<std::optional<org::imm::ImmAdapter>(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::getParent), self, org_context);
}
int org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::getSelfIndex_const(haxorg_ImmAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<int(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::getSelfIndex), self, org_context);
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::atPathStep_const(haxorg_ImmAdapter self, OrgContext* org_context, haxorg_ImmId id, haxorg_ImmPathStep idx) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapter::*)(org::imm::ImmId, org::imm::ImmPathStep) const>(&org::imm::ImmAdapter::at), self, org_context, id, idx);
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::atField_const(haxorg_ImmAdapter self, OrgContext* org_context, haxorg_ImmReflFieldId field) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapter::*)(org::imm::ImmReflFieldId const&) const>(&org::imm::ImmAdapter::at), self, org_context, field);
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::atIndex_const(haxorg_ImmAdapter self, OrgContext* org_context, int idx, bool withPath) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapter::*)(int, bool) const>(&org::imm::ImmAdapter::at), self, org_context, idx, withPath);
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::atPath_const(haxorg_ImmAdapter self, OrgContext* org_context, haxorg_HstdVec path, bool withPath) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapter::*)(hstd::Vec<int> const&, bool) const>(&org::imm::ImmAdapter::at), self, org_context, path, withPath);
}
bool org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::is_const(haxorg_ImmAdapter self, OrgContext* org_context, haxorg_OrgSemKind kind) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<bool(org::imm::ImmAdapter::*)(OrgSemKind) const>(&org::imm::ImmAdapter::is), self, org_context, kind);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::sub_const(haxorg_ImmAdapter self, OrgContext* org_context, bool withPath) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<hstd::Vec<org::imm::ImmAdapter>(org::imm::ImmAdapter::*)(bool) const>(&org::imm::ImmAdapter::sub), self, org_context, withPath);
}
haxorg_SemId org::bind::c::VTable<haxorg_AstTrackingPath, haxorg_AstTrackingPath_vtable>::getParent_const(haxorg_AstTrackingPath self, OrgContext* org_context, int offset) {
  return org::bind::c::execute_cpp<haxorg_AstTrackingPath, haxorg_AstTrackingPath_vtable>(static_cast<org::sem::SemId<org::sem::Org>(org::AstTrackingPath::*)(int) const>(&org::AstTrackingPath::getParent), self, org_context, offset);
}
haxorg_SemId org::bind::c::VTable<haxorg_AstTrackingPath, haxorg_AstTrackingPath_vtable>::getNode_const(haxorg_AstTrackingPath self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AstTrackingPath, haxorg_AstTrackingPath_vtable>(static_cast<org::sem::SemId<org::sem::Org>(org::AstTrackingPath::*)() const>(&org::AstTrackingPath::getNode), self, org_context);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_AstTrackingAlternatives, haxorg_AstTrackingAlternatives_vtable>::getAllNodes_const(haxorg_AstTrackingAlternatives self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AstTrackingAlternatives, haxorg_AstTrackingAlternatives_vtable>(static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::AstTrackingAlternatives::*)() const>(&org::AstTrackingAlternatives::getAllNodes), self, org_context);
}
haxorg_SemId org::bind::c::VTable<haxorg_AstTrackingAlternatives, haxorg_AstTrackingAlternatives_vtable>::getNode_const(haxorg_AstTrackingAlternatives self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AstTrackingAlternatives, haxorg_AstTrackingAlternatives_vtable>(static_cast<org::sem::SemId<org::sem::Org>(org::AstTrackingAlternatives::*)() const>(&org::AstTrackingAlternatives::getNode), self, org_context);
}
haxorg_AstTrackingGroupRadioTarget org::bind::c::VTable<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>::getRadioTargetConst_const(haxorg_AstTrackingGroup self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>(static_cast<org::AstTrackingGroup::RadioTarget const&(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::getRadioTarget), self, org_context);
}
haxorg_AstTrackingGroupTrackedHashtag org::bind::c::VTable<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>::getTrackedHashtagConst_const(haxorg_AstTrackingGroup self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>(static_cast<org::AstTrackingGroup::TrackedHashtag const&(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::getTrackedHashtag), self, org_context);
}
haxorg_AstTrackingGroupTrackedHashtag org::bind::c::VTable<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>::getTrackedHashtagMut(haxorg_AstTrackingGroup self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>(static_cast<org::AstTrackingGroup::TrackedHashtag&(org::AstTrackingGroup::*)()>(&org::AstTrackingGroup::getTrackedHashtag), self, org_context);
}
haxorg_AstTrackingGroupSingle org::bind::c::VTable<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>::getSingleConst_const(haxorg_AstTrackingGroup self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>(static_cast<org::AstTrackingGroup::Single const&(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::getSingle), self, org_context);
}
haxorg_AstTrackingGroupRadioTarget org::bind::c::VTable<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>::getRadioTargetMut(haxorg_AstTrackingGroup self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>(static_cast<org::AstTrackingGroup::RadioTarget&(org::AstTrackingGroup::*)()>(&org::AstTrackingGroup::getRadioTarget), self, org_context);
}
haxorg_AstTrackingGroupSingle org::bind::c::VTable<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>::getSingleMut(haxorg_AstTrackingGroup self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>(static_cast<org::AstTrackingGroup::Single&(org::AstTrackingGroup::*)()>(&org::AstTrackingGroup::getSingle), self, org_context);
}
bool org::bind::c::VTable<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>::isSingle_const(haxorg_AstTrackingGroup self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>(static_cast<bool(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::isSingle), self, org_context);
}
bool org::bind::c::VTable<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>::isTrackedHashtag_const(haxorg_AstTrackingGroup self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>(static_cast<bool(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::isTrackedHashtag), self, org_context);
}
bool org::bind::c::VTable<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>::isRadioTarget_const(haxorg_AstTrackingGroup self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>(static_cast<bool(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::isRadioTarget), self, org_context);
}
haxorg_StdOptional org::bind::c::VTable<haxorg_AstTrackingMap, haxorg_AstTrackingMap_vtable>::getIdPath_const(haxorg_AstTrackingMap self, OrgContext* org_context, haxorg_HstdStr id) {
  return org::bind::c::execute_cpp<haxorg_AstTrackingMap, haxorg_AstTrackingMap_vtable>(static_cast<std::optional<org::AstTrackingAlternatives>(org::AstTrackingMap::*)(hstd::Str const&) const>(&org::AstTrackingMap::getIdPath), self, org_context, id);
}
haxorg_StdOptional org::bind::c::VTable<haxorg_AstTrackingMap, haxorg_AstTrackingMap_vtable>::getNamePath_const(haxorg_AstTrackingMap self, OrgContext* org_context, haxorg_HstdStr id) {
  return org::bind::c::execute_cpp<haxorg_AstTrackingMap, haxorg_AstTrackingMap_vtable>(static_cast<std::optional<org::AstTrackingAlternatives>(org::AstTrackingMap::*)(hstd::Str const&) const>(&org::AstTrackingMap::getNamePath), self, org_context, id);
}
haxorg_StdOptional org::bind::c::VTable<haxorg_AstTrackingMap, haxorg_AstTrackingMap_vtable>::getAnchorTarget_const(haxorg_AstTrackingMap self, OrgContext* org_context, haxorg_HstdStr id) {
  return org::bind::c::execute_cpp<haxorg_AstTrackingMap, haxorg_AstTrackingMap_vtable>(static_cast<std::optional<org::AstTrackingAlternatives>(org::AstTrackingMap::*)(hstd::Str const&) const>(&org::AstTrackingMap::getAnchorTarget), self, org_context, id);
}
haxorg_StdOptional org::bind::c::VTable<haxorg_AstTrackingMap, haxorg_AstTrackingMap_vtable>::getFootnotePath_const(haxorg_AstTrackingMap self, OrgContext* org_context, haxorg_HstdStr id) {
  return org::bind::c::execute_cpp<haxorg_AstTrackingMap, haxorg_AstTrackingMap_vtable>(static_cast<std::optional<org::AstTrackingAlternatives>(org::AstTrackingMap::*)(hstd::Str const&) const>(&org::AstTrackingMap::getFootnotePath), self, org_context, id);
}
bool org::bind::c::VTable<haxorg_SequenceAnnotation, haxorg_SequenceAnnotation_vtable>::isAnnotatedWith_const(haxorg_SequenceAnnotation self, OrgContext* org_context, int groupKind, int segmentKind) {
  return org::bind::c::execute_cpp<haxorg_SequenceAnnotation, haxorg_SequenceAnnotation_vtable>(static_cast<bool(hstd::SequenceAnnotation::*)(int, int) const>(&hstd::SequenceAnnotation::isAnnotatedWith), self, org_context, groupKind, segmentKind);
}
haxorg_GraphMapLinkRadio org::bind::c::VTable<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>::getRadio(haxorg_GraphMapLink self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>(static_cast<org::graph::MapLink::Radio&(org::graph::MapLink::*)()>(&org::graph::MapLink::getRadio), self, org_context);
}
haxorg_GraphMapLinkRadio org::bind::c::VTable<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>::getRadio_const(haxorg_GraphMapLink self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>(static_cast<org::graph::MapLink::Radio const&(org::graph::MapLink::*)() const>(&org::graph::MapLink::getRadio), self, org_context);
}
bool org::bind::c::VTable<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>::isRadio_const(haxorg_GraphMapLink self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>(static_cast<bool(org::graph::MapLink::*)() const>(&org::graph::MapLink::isRadio), self, org_context);
}
haxorg_GraphMapLinkLink org::bind::c::VTable<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>::getLink(haxorg_GraphMapLink self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>(static_cast<org::graph::MapLink::Link&(org::graph::MapLink::*)()>(&org::graph::MapLink::getLink), self, org_context);
}
haxorg_GraphMapLinkLink org::bind::c::VTable<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>::getLink_const(haxorg_GraphMapLink self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>(static_cast<org::graph::MapLink::Link const&(org::graph::MapLink::*)() const>(&org::graph::MapLink::getLink), self, org_context);
}
bool org::bind::c::VTable<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>::isLink_const(haxorg_GraphMapLink self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>(static_cast<bool(org::graph::MapLink::*)() const>(&org::graph::MapLink::isLink), self, org_context);
}
haxorg_GraphMapLinkKind org::bind::c::VTable<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>::getKind_const(haxorg_GraphMapLink self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>(static_cast<org::graph::MapLink::Kind(org::graph::MapLink::*)() const>(&org::graph::MapLink::getKind), self, org_context);
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_GraphMapNodeProp, haxorg_GraphMapNodeProp_vtable>::getAdapter_const(haxorg_GraphMapNodeProp self, OrgContext* org_context, haxorg_ImmAstContext context) {
  return org::bind::c::execute_cpp<haxorg_GraphMapNodeProp, haxorg_GraphMapNodeProp_vtable>(static_cast<org::imm::ImmAdapter(org::graph::MapNodeProp::*)(std::shared_ptr<org::imm::ImmAstContext> const&) const>(&org::graph::MapNodeProp::getAdapter), self, org_context, context);
}
haxorg_StdOptional org::bind::c::VTable<haxorg_GraphMapNodeProp, haxorg_GraphMapNodeProp_vtable>::getSubtreeId_const(haxorg_GraphMapNodeProp self, OrgContext* org_context, haxorg_ImmAstContext context) {
  return org::bind::c::execute_cpp<haxorg_GraphMapNodeProp, haxorg_GraphMapNodeProp_vtable>(static_cast<std::optional<hstd::Str>(org::graph::MapNodeProp::*)(std::shared_ptr<org::imm::ImmAstContext> const&) const>(&org::graph::MapNodeProp::getSubtreeId), self, org_context, context);
}
haxorg_StdOptional org::bind::c::VTable<haxorg_GraphMapNodeProp, haxorg_GraphMapNodeProp_vtable>::getFootnoteName_const(haxorg_GraphMapNodeProp self, OrgContext* org_context, haxorg_ImmAstContext context) {
  return org::bind::c::execute_cpp<haxorg_GraphMapNodeProp, haxorg_GraphMapNodeProp_vtable>(static_cast<std::optional<hstd::Str>(org::graph::MapNodeProp::*)(std::shared_ptr<org::imm::ImmAstContext> const&) const>(&org::graph::MapNodeProp::getFootnoteName), self, org_context, context);
}
bool org::bind::c::VTable<haxorg_GraphMapNode, haxorg_GraphMapNode_vtable>::__eq___const(haxorg_GraphMapNode self, OrgContext* org_context, haxorg_GraphMapNode other) {
  return org::bind::c::execute_cpp<haxorg_GraphMapNode, haxorg_GraphMapNode_vtable>(static_cast<bool(org::graph::MapNode::*)(org::graph::MapNode const&) const>(&org::graph::MapNode::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_GraphMapNode, haxorg_GraphMapNode_vtable>::__lt___const(haxorg_GraphMapNode self, OrgContext* org_context, haxorg_GraphMapNode other) {
  return org::bind::c::execute_cpp<haxorg_GraphMapNode, haxorg_GraphMapNode_vtable>(static_cast<bool(org::graph::MapNode::*)(org::graph::MapNode const&) const>(&org::graph::MapNode::operator<), self, org_context, other);
}
int org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::nodeCount_const(haxorg_GraphMapGraph self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<int(org::graph::MapGraph::*)() const>(&org::graph::MapGraph::nodeCount), self, org_context);
}
int org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::edgeCount_const(haxorg_GraphMapGraph self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<int(org::graph::MapGraph::*)() const>(&org::graph::MapGraph::edgeCount), self, org_context);
}
haxorg_GraphAdjNodesList org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::outNodes_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node) {
  return org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<org::graph::AdjNodesList const&(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::outNodes), self, org_context, node);
}
haxorg_GraphAdjNodesList org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::inNodes_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node) {
  return org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<org::graph::AdjNodesList const&(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::inNodes), self, org_context, node);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::adjEdges_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node) {
  return org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<hstd::Vec<org::graph::MapEdge>(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::adjEdges), self, org_context, node);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::adjNodes_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node) {
  return org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<hstd::Vec<org::graph::MapNode>(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::adjNodes), self, org_context, node);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::outEdges_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node) {
  return org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<hstd::Vec<org::graph::MapEdge>(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::outEdges), self, org_context, node);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::inEdges_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node) {
  return org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<hstd::Vec<org::graph::MapEdge>(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::inEdges), self, org_context, node);
}
int org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::outDegree_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node) {
  return org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<int(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::outDegree), self, org_context, node);
}
int org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::inDegree_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node) {
  return org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<int(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::inDegree), self, org_context, node);
}
bool org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::isRegisteredNode_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode id) {
  return org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<bool(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::isRegisteredNode), self, org_context, id);
}
bool org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::isRegisteredNodeById_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_ImmUniqId id) {
  return org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<bool(org::graph::MapGraph::*)(org::imm::ImmUniqId const&) const>(&org::graph::MapGraph::isRegisteredNode), self, org_context, id);
}
haxorg_GraphMapNodeProp org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::atMapNode_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node) {
  return org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<org::graph::MapNodeProp const&(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::at), self, org_context, node);
}
haxorg_GraphMapEdgeProp org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::atMapEdge_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapEdge edge) {
  return org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<org::graph::MapEdgeProp const&(org::graph::MapGraph::*)(org::graph::MapEdge const&) const>(&org::graph::MapGraph::at), self, org_context, edge);
}
void org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::addEdge(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapEdge edge) {
  return org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<void(org::graph::MapGraph::*)(org::graph::MapEdge const&)>(&org::graph::MapGraph::addEdge), self, org_context, edge);
}
void org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::addEdgeWithProp(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapEdge edge, haxorg_GraphMapEdgeProp prop) {
  return org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<void(org::graph::MapGraph::*)(org::graph::MapEdge const&, org::graph::MapEdgeProp const&)>(&org::graph::MapGraph::addEdge), self, org_context, edge, prop);
}
void org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::addNode(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node) {
  return org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<void(org::graph::MapGraph::*)(org::graph::MapNode const&)>(&org::graph::MapGraph::addNode), self, org_context, node);
}
void org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::addNodeWithProp(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node, haxorg_GraphMapNodeProp prop) {
  return org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<void(org::graph::MapGraph::*)(org::graph::MapNode const&, org::graph::MapNodeProp const&)>(&org::graph::MapGraph::addNode), self, org_context, node, prop);
}
bool org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::hasEdge_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode source, haxorg_GraphMapNode target) {
  return org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<bool(org::graph::MapGraph::*)(org::graph::MapNode const&, org::graph::MapNode const&) const>(&org::graph::MapGraph::hasEdge), self, org_context, source, target);
}
bool org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::hasNode_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_GraphMapNode node) {
  return org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<bool(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::hasNode), self, org_context, node);
}
bool org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::has2AdapterEdge_const(haxorg_GraphMapGraph self, OrgContext* org_context, haxorg_ImmAdapter source, haxorg_ImmAdapter target) {
  return org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<bool(org::graph::MapGraph::*)(org::imm::ImmAdapter const&, org::imm::ImmAdapter const&) const>(&org::graph::MapGraph::hasEdge), self, org_context, source, target);
}
haxorg_GraphMapGraph org::bind::c::VTable<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>::getGraph_const(haxorg_GraphMapGraphState self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>(static_cast<std::shared_ptr<org::graph::MapGraph>(org::graph::MapGraphState::*)() const>(&org::graph::MapGraphState::getGraph), self, org_context);
}
haxorg_GraphMapGraphState org::bind::c::VTable<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>::FromAstContext(haxorg_GraphMapGraphState self, OrgContext* org_context, haxorg_ImmAstContext ast) {
  return org::bind::c::execute_cpp<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>(static_cast<std::shared_ptr<org::graph::MapGraphState>(*)(std::shared_ptr<org::imm::ImmAstContext>)>(&org::graph::MapGraphState::FromAstContext), self, org_context, ast);
}
void org::bind::c::VTable<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>::registerNode(haxorg_GraphMapGraphState self, OrgContext* org_context, haxorg_GraphMapNodeProp node, haxorg_GraphMapConfig conf) {
  return org::bind::c::execute_cpp<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>(static_cast<void(org::graph::MapGraphState::*)(org::graph::MapNodeProp const&, std::shared_ptr<org::graph::MapConfig> const&)>(&org::graph::MapGraphState::registerNode), self, org_context, node, conf);
}
void org::bind::c::VTable<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>::addNode(haxorg_GraphMapGraphState self, OrgContext* org_context, haxorg_ImmAdapter node, haxorg_GraphMapConfig conf) {
  return org::bind::c::execute_cpp<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>(static_cast<void(org::graph::MapGraphState::*)(org::imm::ImmAdapter const&, std::shared_ptr<org::graph::MapConfig> const&)>(&org::graph::MapGraphState::addNode), self, org_context, node, conf);
}
void org::bind::c::VTable<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>::addNodeRec(haxorg_GraphMapGraphState self, OrgContext* org_context, haxorg_ImmAstContext ast, haxorg_ImmAdapter node, haxorg_GraphMapConfig conf) {
  return org::bind::c::execute_cpp<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>(static_cast<void(org::graph::MapGraphState::*)(std::shared_ptr<org::imm::ImmAstContext> const&, org::imm::ImmAdapter const&, std::shared_ptr<org::graph::MapConfig> const&)>(&org::graph::MapGraphState::addNodeRec), self, org_context, ast, node, conf);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>::getUnresolvedSubtreeLinks_const(haxorg_GraphMapGraphState self, OrgContext* org_context, haxorg_ImmSubtreeAdapter node, haxorg_GraphMapConfig conf) {
  return org::bind::c::execute_cpp<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>(static_cast<hstd::Vec<org::graph::MapLink>(org::graph::MapGraphState::*)(org::imm::ImmAdapterT<org::imm::ImmSubtree>, std::shared_ptr<org::graph::MapConfig> const&) const>(&org::graph::MapGraphState::getUnresolvedSubtreeLinks), self, org_context, node, conf);
}
haxorg_StdOptional org::bind::c::VTable<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>::getUnresolvedLink_const(haxorg_GraphMapGraphState self, OrgContext* org_context, haxorg_ImmLinkAdapter node, haxorg_GraphMapConfig conf) {
  return org::bind::c::execute_cpp<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>(static_cast<std::optional<org::graph::MapLink>(org::graph::MapGraphState::*)(org::imm::ImmAdapterT<org::imm::ImmLink>, std::shared_ptr<org::graph::MapConfig> const&) const>(&org::graph::MapGraphState::getUnresolvedLink), self, org_context, node, conf);
}
bool org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::__eq___const(haxorg_LispCode self, OrgContext* org_context, haxorg_LispCode other) {
  return org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<bool(org::sem::LispCode::*)(org::sem::LispCode const&) const>(&org::sem::LispCode::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::isCall_const(haxorg_LispCode self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isCall), self, org_context);
}
haxorg_LispCodeCall org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getCallConst_const(haxorg_LispCode self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::Call const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getCall), self, org_context);
}
haxorg_LispCodeCall org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getCallMut(haxorg_LispCode self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::Call&(org::sem::LispCode::*)()>(&org::sem::LispCode::getCall), self, org_context);
}
bool org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::isList_const(haxorg_LispCode self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isList), self, org_context);
}
haxorg_LispCodeList org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getListConst_const(haxorg_LispCode self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::List const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getList), self, org_context);
}
haxorg_LispCodeList org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getListMut(haxorg_LispCode self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::List&(org::sem::LispCode::*)()>(&org::sem::LispCode::getList), self, org_context);
}
bool org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::isKeyValue_const(haxorg_LispCode self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isKeyValue), self, org_context);
}
haxorg_LispCodeKeyValue org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getKeyValueConst_const(haxorg_LispCode self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::KeyValue const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getKeyValue), self, org_context);
}
haxorg_LispCodeKeyValue org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getKeyValueMut(haxorg_LispCode self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::KeyValue&(org::sem::LispCode::*)()>(&org::sem::LispCode::getKeyValue), self, org_context);
}
bool org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::isNumber_const(haxorg_LispCode self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isNumber), self, org_context);
}
haxorg_LispCodeNumber org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getNumberConst_const(haxorg_LispCode self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::Number const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getNumber), self, org_context);
}
haxorg_LispCodeNumber org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getNumberMut(haxorg_LispCode self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::Number&(org::sem::LispCode::*)()>(&org::sem::LispCode::getNumber), self, org_context);
}
bool org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::isText_const(haxorg_LispCode self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isText), self, org_context);
}
haxorg_LispCodeText org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getTextConst_const(haxorg_LispCode self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::Text const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getText), self, org_context);
}
haxorg_LispCodeText org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getTextMut(haxorg_LispCode self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::Text&(org::sem::LispCode::*)()>(&org::sem::LispCode::getText), self, org_context);
}
bool org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::isIdent_const(haxorg_LispCode self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isIdent), self, org_context);
}
haxorg_LispCodeIdent org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getIdentConst_const(haxorg_LispCode self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::Ident const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getIdent), self, org_context);
}
haxorg_LispCodeIdent org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getIdentMut(haxorg_LispCode self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::Ident&(org::sem::LispCode::*)()>(&org::sem::LispCode::getIdent), self, org_context);
}
bool org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::isBoolean_const(haxorg_LispCode self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isBoolean), self, org_context);
}
haxorg_LispCodeBoolean org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getBooleanConst_const(haxorg_LispCode self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::Boolean const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getBoolean), self, org_context);
}
haxorg_LispCodeBoolean org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getBooleanMut(haxorg_LispCode self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::Boolean&(org::sem::LispCode::*)()>(&org::sem::LispCode::getBoolean), self, org_context);
}
bool org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::isReal_const(haxorg_LispCode self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isReal), self, org_context);
}
haxorg_LispCodeReal org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getRealConst_const(haxorg_LispCode self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::Real const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getReal), self, org_context);
}
haxorg_LispCodeReal org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getRealMut(haxorg_LispCode self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::Real&(org::sem::LispCode::*)()>(&org::sem::LispCode::getReal), self, org_context);
}
haxorg_LispCodeKind org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getKind_const(haxorg_LispCode self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LispCode, haxorg_LispCode_vtable>(static_cast<org::sem::LispCode::Kind(org::sem::LispCode::*)() const>(&org::sem::LispCode::getKind), self, org_context);
}
bool org::bind::c::VTable<haxorg_LispCodeCall, haxorg_LispCodeCall_vtable>::__eq___const(haxorg_LispCodeCall self, OrgContext* org_context, haxorg_LispCodeCall other) {
  return org::bind::c::execute_cpp<haxorg_LispCodeCall, haxorg_LispCodeCall_vtable>(static_cast<bool(org::sem::LispCode::Call::*)(org::sem::LispCode::Call const&) const>(&org::sem::LispCode::Call::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_LispCodeList, haxorg_LispCodeList_vtable>::__eq___const(haxorg_LispCodeList self, OrgContext* org_context, haxorg_LispCodeList other) {
  return org::bind::c::execute_cpp<haxorg_LispCodeList, haxorg_LispCodeList_vtable>(static_cast<bool(org::sem::LispCode::List::*)(org::sem::LispCode::List const&) const>(&org::sem::LispCode::List::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_LispCodeKeyValue, haxorg_LispCodeKeyValue_vtable>::__eq___const(haxorg_LispCodeKeyValue self, OrgContext* org_context, haxorg_LispCodeKeyValue other) {
  return org::bind::c::execute_cpp<haxorg_LispCodeKeyValue, haxorg_LispCodeKeyValue_vtable>(static_cast<bool(org::sem::LispCode::KeyValue::*)(org::sem::LispCode::KeyValue const&) const>(&org::sem::LispCode::KeyValue::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_LispCodeNumber, haxorg_LispCodeNumber_vtable>::__eq___const(haxorg_LispCodeNumber self, OrgContext* org_context, haxorg_LispCodeNumber other) {
  return org::bind::c::execute_cpp<haxorg_LispCodeNumber, haxorg_LispCodeNumber_vtable>(static_cast<bool(org::sem::LispCode::Number::*)(org::sem::LispCode::Number const&) const>(&org::sem::LispCode::Number::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_LispCodeText, haxorg_LispCodeText_vtable>::__eq___const(haxorg_LispCodeText self, OrgContext* org_context, haxorg_LispCodeText other) {
  return org::bind::c::execute_cpp<haxorg_LispCodeText, haxorg_LispCodeText_vtable>(static_cast<bool(org::sem::LispCode::Text::*)(org::sem::LispCode::Text const&) const>(&org::sem::LispCode::Text::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_LispCodeIdent, haxorg_LispCodeIdent_vtable>::__eq___const(haxorg_LispCodeIdent self, OrgContext* org_context, haxorg_LispCodeIdent other) {
  return org::bind::c::execute_cpp<haxorg_LispCodeIdent, haxorg_LispCodeIdent_vtable>(static_cast<bool(org::sem::LispCode::Ident::*)(org::sem::LispCode::Ident const&) const>(&org::sem::LispCode::Ident::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_LispCodeBoolean, haxorg_LispCodeBoolean_vtable>::__eq___const(haxorg_LispCodeBoolean self, OrgContext* org_context, haxorg_LispCodeBoolean other) {
  return org::bind::c::execute_cpp<haxorg_LispCodeBoolean, haxorg_LispCodeBoolean_vtable>(static_cast<bool(org::sem::LispCode::Boolean::*)(org::sem::LispCode::Boolean const&) const>(&org::sem::LispCode::Boolean::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_LispCodeReal, haxorg_LispCodeReal_vtable>::__eq___const(haxorg_LispCodeReal self, OrgContext* org_context, haxorg_LispCodeReal other) {
  return org::bind::c::execute_cpp<haxorg_LispCodeReal, haxorg_LispCodeReal_vtable>(static_cast<bool(org::sem::LispCode::Real::*)(org::sem::LispCode::Real const&) const>(&org::sem::LispCode::Real::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_Tblfm, haxorg_Tblfm_vtable>::__eq___const(haxorg_Tblfm self, OrgContext* org_context, haxorg_Tblfm other) {
  return org::bind::c::execute_cpp<haxorg_Tblfm, haxorg_Tblfm_vtable>(static_cast<bool(org::sem::Tblfm::*)(org::sem::Tblfm const&) const>(&org::sem::Tblfm::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::__eq___const(haxorg_TblfmExpr self, OrgContext* org_context, haxorg_TblfmExpr other) {
  return org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<bool(org::sem::Tblfm::Expr::*)(org::sem::Tblfm::Expr const&) const>(&org::sem::Tblfm::Expr::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::isAxisRef_const(haxorg_TblfmExpr self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isAxisRef), self, org_context);
}
haxorg_TblfmExprAxisRef org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getAxisRefConst_const(haxorg_TblfmExpr self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<org::sem::Tblfm::Expr::AxisRef const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getAxisRef), self, org_context);
}
haxorg_TblfmExprAxisRef org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getAxisRefMut(haxorg_TblfmExpr self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<org::sem::Tblfm::Expr::AxisRef&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getAxisRef), self, org_context);
}
bool org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::isAxisName_const(haxorg_TblfmExpr self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isAxisName), self, org_context);
}
haxorg_TblfmExprAxisName org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getAxisNameConst_const(haxorg_TblfmExpr self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<org::sem::Tblfm::Expr::AxisName const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getAxisName), self, org_context);
}
haxorg_TblfmExprAxisName org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getAxisNameMut(haxorg_TblfmExpr self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<org::sem::Tblfm::Expr::AxisName&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getAxisName), self, org_context);
}
bool org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::isIntLiteral_const(haxorg_TblfmExpr self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isIntLiteral), self, org_context);
}
haxorg_TblfmExprIntLiteral org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getIntLiteralConst_const(haxorg_TblfmExpr self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<org::sem::Tblfm::Expr::IntLiteral const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getIntLiteral), self, org_context);
}
haxorg_TblfmExprIntLiteral org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getIntLiteralMut(haxorg_TblfmExpr self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<org::sem::Tblfm::Expr::IntLiteral&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getIntLiteral), self, org_context);
}
bool org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::isFloatLiteral_const(haxorg_TblfmExpr self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isFloatLiteral), self, org_context);
}
haxorg_TblfmExprFloatLiteral org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getFloatLiteralConst_const(haxorg_TblfmExpr self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<org::sem::Tblfm::Expr::FloatLiteral const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getFloatLiteral), self, org_context);
}
haxorg_TblfmExprFloatLiteral org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getFloatLiteralMut(haxorg_TblfmExpr self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<org::sem::Tblfm::Expr::FloatLiteral&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getFloatLiteral), self, org_context);
}
bool org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::isRangeRef_const(haxorg_TblfmExpr self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isRangeRef), self, org_context);
}
haxorg_TblfmExprRangeRef org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getRangeRefConst_const(haxorg_TblfmExpr self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<org::sem::Tblfm::Expr::RangeRef const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getRangeRef), self, org_context);
}
haxorg_TblfmExprRangeRef org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getRangeRefMut(haxorg_TblfmExpr self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<org::sem::Tblfm::Expr::RangeRef&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getRangeRef), self, org_context);
}
bool org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::isCall_const(haxorg_TblfmExpr self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isCall), self, org_context);
}
haxorg_TblfmExprCall org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getCallConst_const(haxorg_TblfmExpr self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<org::sem::Tblfm::Expr::Call const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getCall), self, org_context);
}
haxorg_TblfmExprCall org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getCallMut(haxorg_TblfmExpr self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<org::sem::Tblfm::Expr::Call&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getCall), self, org_context);
}
bool org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::isElisp_const(haxorg_TblfmExpr self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isElisp), self, org_context);
}
haxorg_TblfmExprElisp org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getElispConst_const(haxorg_TblfmExpr self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<org::sem::Tblfm::Expr::Elisp const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getElisp), self, org_context);
}
haxorg_TblfmExprElisp org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getElispMut(haxorg_TblfmExpr self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<org::sem::Tblfm::Expr::Elisp&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getElisp), self, org_context);
}
haxorg_TblfmExprKind org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getKind_const(haxorg_TblfmExpr self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>(static_cast<org::sem::Tblfm::Expr::Kind(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getKind), self, org_context);
}
bool org::bind::c::VTable<haxorg_TblfmExprAxisRef, haxorg_TblfmExprAxisRef_vtable>::__eq___const(haxorg_TblfmExprAxisRef self, OrgContext* org_context, haxorg_TblfmExprAxisRef other) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRef, haxorg_TblfmExprAxisRef_vtable>(static_cast<bool(org::sem::Tblfm::Expr::AxisRef::*)(org::sem::Tblfm::Expr::AxisRef const&) const>(&org::sem::Tblfm::Expr::AxisRef::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>::__eq___const(haxorg_TblfmExprAxisRefPosition self, OrgContext* org_context, haxorg_TblfmExprAxisRefPosition other) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>(static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::*)(org::sem::Tblfm::Expr::AxisRef::Position const&) const>(&org::sem::Tblfm::Expr::AxisRef::Position::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>::isIndex_const(haxorg_TblfmExprAxisRefPosition self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>(static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::isIndex), self, org_context);
}
haxorg_TblfmExprAxisRefPositionIndex org::bind::c::VTable<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>::getIndexConst_const(haxorg_TblfmExprAxisRefPosition self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>(static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Index const&(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::getIndex), self, org_context);
}
haxorg_TblfmExprAxisRefPositionIndex org::bind::c::VTable<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>::getIndexMut(haxorg_TblfmExprAxisRefPosition self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>(static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Index&(org::sem::Tblfm::Expr::AxisRef::Position::*)()>(&org::sem::Tblfm::Expr::AxisRef::Position::getIndex), self, org_context);
}
bool org::bind::c::VTable<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>::isName_const(haxorg_TblfmExprAxisRefPosition self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>(static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::isName), self, org_context);
}
haxorg_TblfmExprAxisRefPositionName org::bind::c::VTable<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>::getNameConst_const(haxorg_TblfmExprAxisRefPosition self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>(static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Name const&(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::getName), self, org_context);
}
haxorg_TblfmExprAxisRefPositionName org::bind::c::VTable<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>::getNameMut(haxorg_TblfmExprAxisRefPosition self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>(static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Name&(org::sem::Tblfm::Expr::AxisRef::Position::*)()>(&org::sem::Tblfm::Expr::AxisRef::Position::getName), self, org_context);
}
haxorg_TblfmExprAxisRefPositionKind org::bind::c::VTable<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>::getKind_const(haxorg_TblfmExprAxisRefPosition self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>(static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Kind(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::getKind), self, org_context);
}
bool org::bind::c::VTable<haxorg_TblfmExprAxisRefPositionIndex, haxorg_TblfmExprAxisRefPositionIndex_vtable>::__eq___const(haxorg_TblfmExprAxisRefPositionIndex self, OrgContext* org_context, haxorg_TblfmExprAxisRefPositionIndex other) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPositionIndex, haxorg_TblfmExprAxisRefPositionIndex_vtable>(static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::Index::*)(org::sem::Tblfm::Expr::AxisRef::Position::Index const&) const>(&org::sem::Tblfm::Expr::AxisRef::Position::Index::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_TblfmExprAxisRefPositionName, haxorg_TblfmExprAxisRefPositionName_vtable>::__eq___const(haxorg_TblfmExprAxisRefPositionName self, OrgContext* org_context, haxorg_TblfmExprAxisRefPositionName other) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPositionName, haxorg_TblfmExprAxisRefPositionName_vtable>(static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::Name::*)(org::sem::Tblfm::Expr::AxisRef::Position::Name const&) const>(&org::sem::Tblfm::Expr::AxisRef::Position::Name::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_TblfmExprAxisName, haxorg_TblfmExprAxisName_vtable>::__eq___const(haxorg_TblfmExprAxisName self, OrgContext* org_context, haxorg_TblfmExprAxisName other) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprAxisName, haxorg_TblfmExprAxisName_vtable>(static_cast<bool(org::sem::Tblfm::Expr::AxisName::*)(org::sem::Tblfm::Expr::AxisName const&) const>(&org::sem::Tblfm::Expr::AxisName::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_TblfmExprIntLiteral, haxorg_TblfmExprIntLiteral_vtable>::__eq___const(haxorg_TblfmExprIntLiteral self, OrgContext* org_context, haxorg_TblfmExprIntLiteral other) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprIntLiteral, haxorg_TblfmExprIntLiteral_vtable>(static_cast<bool(org::sem::Tblfm::Expr::IntLiteral::*)(org::sem::Tblfm::Expr::IntLiteral const&) const>(&org::sem::Tblfm::Expr::IntLiteral::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_TblfmExprFloatLiteral, haxorg_TblfmExprFloatLiteral_vtable>::__eq___const(haxorg_TblfmExprFloatLiteral self, OrgContext* org_context, haxorg_TblfmExprFloatLiteral other) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprFloatLiteral, haxorg_TblfmExprFloatLiteral_vtable>(static_cast<bool(org::sem::Tblfm::Expr::FloatLiteral::*)(org::sem::Tblfm::Expr::FloatLiteral const&) const>(&org::sem::Tblfm::Expr::FloatLiteral::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_TblfmExprRangeRef, haxorg_TblfmExprRangeRef_vtable>::__eq___const(haxorg_TblfmExprRangeRef self, OrgContext* org_context, haxorg_TblfmExprRangeRef other) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprRangeRef, haxorg_TblfmExprRangeRef_vtable>(static_cast<bool(org::sem::Tblfm::Expr::RangeRef::*)(org::sem::Tblfm::Expr::RangeRef const&) const>(&org::sem::Tblfm::Expr::RangeRef::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_TblfmExprCall, haxorg_TblfmExprCall_vtable>::__eq___const(haxorg_TblfmExprCall self, OrgContext* org_context, haxorg_TblfmExprCall other) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprCall, haxorg_TblfmExprCall_vtable>(static_cast<bool(org::sem::Tblfm::Expr::Call::*)(org::sem::Tblfm::Expr::Call const&) const>(&org::sem::Tblfm::Expr::Call::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_TblfmExprElisp, haxorg_TblfmExprElisp_vtable>::__eq___const(haxorg_TblfmExprElisp self, OrgContext* org_context, haxorg_TblfmExprElisp other) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprElisp, haxorg_TblfmExprElisp_vtable>(static_cast<bool(org::sem::Tblfm::Expr::Elisp::*)(org::sem::Tblfm::Expr::Elisp const&) const>(&org::sem::Tblfm::Expr::Elisp::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_TblfmAssign, haxorg_TblfmAssign_vtable>::__eq___const(haxorg_TblfmAssign self, OrgContext* org_context, haxorg_TblfmAssign other) {
  return org::bind::c::execute_cpp<haxorg_TblfmAssign, haxorg_TblfmAssign_vtable>(static_cast<bool(org::sem::Tblfm::Assign::*)(org::sem::Tblfm::Assign const&) const>(&org::sem::Tblfm::Assign::operator==), self, org_context, other);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getBool_const(haxorg_AttrValue self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<hstd::Opt<bool>(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getBool), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getInt_const(haxorg_AttrValue self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<hstd::Opt<int>(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getInt), self, org_context);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getString_const(haxorg_AttrValue self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<hstd::Str(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getString), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getDouble_const(haxorg_AttrValue self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<hstd::Opt<double>(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getDouble), self, org_context);
}
bool org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::__eq___const(haxorg_AttrValue self, OrgContext* org_context, haxorg_AttrValue other) {
  return org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<bool(org::sem::AttrValue::*)(org::sem::AttrValue const&) const>(&org::sem::AttrValue::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::isTextValue_const(haxorg_AttrValue self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<bool(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::isTextValue), self, org_context);
}
haxorg_AttrValueTextValue org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getTextValueConst_const(haxorg_AttrValue self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<org::sem::AttrValue::TextValue const&(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getTextValue), self, org_context);
}
haxorg_AttrValueTextValue org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getTextValueMut(haxorg_AttrValue self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<org::sem::AttrValue::TextValue&(org::sem::AttrValue::*)()>(&org::sem::AttrValue::getTextValue), self, org_context);
}
bool org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::isFileReference_const(haxorg_AttrValue self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<bool(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::isFileReference), self, org_context);
}
haxorg_AttrValueFileReference org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getFileReferenceConst_const(haxorg_AttrValue self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<org::sem::AttrValue::FileReference const&(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getFileReference), self, org_context);
}
haxorg_AttrValueFileReference org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getFileReferenceMut(haxorg_AttrValue self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<org::sem::AttrValue::FileReference&(org::sem::AttrValue::*)()>(&org::sem::AttrValue::getFileReference), self, org_context);
}
bool org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::isLispValue_const(haxorg_AttrValue self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<bool(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::isLispValue), self, org_context);
}
haxorg_AttrValueLispValue org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getLispValueConst_const(haxorg_AttrValue self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<org::sem::AttrValue::LispValue const&(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getLispValue), self, org_context);
}
haxorg_AttrValueLispValue org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getLispValueMut(haxorg_AttrValue self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<org::sem::AttrValue::LispValue&(org::sem::AttrValue::*)()>(&org::sem::AttrValue::getLispValue), self, org_context);
}
haxorg_AttrValueKind org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getKind_const(haxorg_AttrValue self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<org::sem::AttrValue::Kind(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getKind), self, org_context);
}
bool org::bind::c::VTable<haxorg_AttrValueDimensionSpan, haxorg_AttrValueDimensionSpan_vtable>::__eq___const(haxorg_AttrValueDimensionSpan self, OrgContext* org_context, haxorg_AttrValueDimensionSpan other) {
  return org::bind::c::execute_cpp<haxorg_AttrValueDimensionSpan, haxorg_AttrValueDimensionSpan_vtable>(static_cast<bool(org::sem::AttrValue::DimensionSpan::*)(org::sem::AttrValue::DimensionSpan const&) const>(&org::sem::AttrValue::DimensionSpan::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_AttrValueTextValue, haxorg_AttrValueTextValue_vtable>::__eq___const(haxorg_AttrValueTextValue self, OrgContext* org_context, haxorg_AttrValueTextValue other) {
  return org::bind::c::execute_cpp<haxorg_AttrValueTextValue, haxorg_AttrValueTextValue_vtable>(static_cast<bool(org::sem::AttrValue::TextValue::*)(org::sem::AttrValue::TextValue const&) const>(&org::sem::AttrValue::TextValue::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_AttrValueFileReference, haxorg_AttrValueFileReference_vtable>::__eq___const(haxorg_AttrValueFileReference self, OrgContext* org_context, haxorg_AttrValueFileReference other) {
  return org::bind::c::execute_cpp<haxorg_AttrValueFileReference, haxorg_AttrValueFileReference_vtable>(static_cast<bool(org::sem::AttrValue::FileReference::*)(org::sem::AttrValue::FileReference const&) const>(&org::sem::AttrValue::FileReference::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_AttrValueLispValue, haxorg_AttrValueLispValue_vtable>::__eq___const(haxorg_AttrValueLispValue self, OrgContext* org_context, haxorg_AttrValueLispValue other) {
  return org::bind::c::execute_cpp<haxorg_AttrValueLispValue, haxorg_AttrValueLispValue_vtable>(static_cast<bool(org::sem::AttrValue::LispValue::*)(org::sem::AttrValue::LispValue const&) const>(&org::sem::AttrValue::LispValue::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_HashTagFlat, haxorg_HashTagFlat_vtable>::__eq___const(haxorg_HashTagFlat self, OrgContext* org_context, haxorg_HashTagFlat other) {
  return org::bind::c::execute_cpp<haxorg_HashTagFlat, haxorg_HashTagFlat_vtable>(static_cast<bool(org::sem::HashTagFlat::*)(org::sem::HashTagFlat const&) const>(&org::sem::HashTagFlat::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_HashTagFlat, haxorg_HashTagFlat_vtable>::__lt___const(haxorg_HashTagFlat self, OrgContext* org_context, haxorg_HashTagFlat other) {
  return org::bind::c::execute_cpp<haxorg_HashTagFlat, haxorg_HashTagFlat_vtable>(static_cast<bool(org::sem::HashTagFlat::*)(org::sem::HashTagFlat const&) const>(&org::sem::HashTagFlat::operator<), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_TodoKeyword, haxorg_TodoKeyword_vtable>::__eq___const(haxorg_TodoKeyword self, OrgContext* org_context, haxorg_TodoKeyword other) {
  return org::bind::c::execute_cpp<haxorg_TodoKeyword, haxorg_TodoKeyword_vtable>(static_cast<bool(org::sem::TodoKeyword::*)(org::sem::TodoKeyword const&) const>(&org::sem::TodoKeyword::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_HashTagText, haxorg_HashTagText_vtable>::__eq___const(haxorg_HashTagText self, OrgContext* org_context, haxorg_HashTagText other) {
  return org::bind::c::execute_cpp<haxorg_HashTagText, haxorg_HashTagText_vtable>(static_cast<bool(org::sem::HashTagText::*)(org::sem::HashTagText const&) const>(&org::sem::HashTagText::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_HashTagText, haxorg_HashTagText_vtable>::prefixMatch_const(haxorg_HashTagText self, OrgContext* org_context, haxorg_HstdVec prefix) {
  return org::bind::c::execute_cpp<haxorg_HashTagText, haxorg_HashTagText_vtable>(static_cast<bool(org::sem::HashTagText::*)(hstd::Vec<hstd::Str> const&) const>(&org::sem::HashTagText::prefixMatch), self, org_context, prefix);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_HashTagText, haxorg_HashTagText_vtable>::getFlatHashes_const(haxorg_HashTagText self, OrgContext* org_context, bool withIntermediate) {
  return org::bind::c::execute_cpp<haxorg_HashTagText, haxorg_HashTagText_vtable>(static_cast<hstd::Vec<org::sem::HashTagFlat>(org::sem::HashTagText::*)(bool) const>(&org::sem::HashTagText::getFlatHashes), self, org_context, withIntermediate);
}
bool org::bind::c::VTable<haxorg_SubtreePath, haxorg_SubtreePath_vtable>::__eq___const(haxorg_SubtreePath self, OrgContext* org_context, haxorg_SubtreePath other) {
  return org::bind::c::execute_cpp<haxorg_SubtreePath, haxorg_SubtreePath_vtable>(static_cast<bool(org::sem::SubtreePath::*)(org::sem::SubtreePath const&) const>(&org::sem::SubtreePath::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::__eq___const(haxorg_LinkTarget self, OrgContext* org_context, haxorg_LinkTarget other) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<bool(org::sem::LinkTarget::*)(org::sem::LinkTarget const&) const>(&org::sem::LinkTarget::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::isRaw_const(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isRaw), self, org_context);
}
haxorg_LinkTargetRaw org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getRawConst_const(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::Raw const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getRaw), self, org_context);
}
haxorg_LinkTargetRaw org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getRawMut(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::Raw&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getRaw), self, org_context);
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::isId_const(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isId), self, org_context);
}
haxorg_LinkTargetId org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getIdConst_const(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::Id const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getId), self, org_context);
}
haxorg_LinkTargetId org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getIdMut(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::Id&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getId), self, org_context);
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::isCustomId_const(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isCustomId), self, org_context);
}
haxorg_LinkTargetCustomId org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getCustomIdConst_const(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::CustomId const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getCustomId), self, org_context);
}
haxorg_LinkTargetCustomId org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getCustomIdMut(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::CustomId&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getCustomId), self, org_context);
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::isSubtreeTitle_const(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isSubtreeTitle), self, org_context);
}
haxorg_LinkTargetSubtreeTitle org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getSubtreeTitleConst_const(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::SubtreeTitle const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getSubtreeTitle), self, org_context);
}
haxorg_LinkTargetSubtreeTitle org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getSubtreeTitleMut(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::SubtreeTitle&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getSubtreeTitle), self, org_context);
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::isPerson_const(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isPerson), self, org_context);
}
haxorg_LinkTargetPerson org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getPersonConst_const(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::Person const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getPerson), self, org_context);
}
haxorg_LinkTargetPerson org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getPersonMut(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::Person&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getPerson), self, org_context);
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::isUserProtocol_const(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isUserProtocol), self, org_context);
}
haxorg_LinkTargetUserProtocol org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getUserProtocolConst_const(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::UserProtocol const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getUserProtocol), self, org_context);
}
haxorg_LinkTargetUserProtocol org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getUserProtocolMut(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::UserProtocol&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getUserProtocol), self, org_context);
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::isInternal_const(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isInternal), self, org_context);
}
haxorg_LinkTargetInternal org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getInternalConst_const(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::Internal const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getInternal), self, org_context);
}
haxorg_LinkTargetInternal org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getInternalMut(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::Internal&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getInternal), self, org_context);
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::isFootnote_const(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isFootnote), self, org_context);
}
haxorg_LinkTargetFootnote org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getFootnoteConst_const(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::Footnote const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getFootnote), self, org_context);
}
haxorg_LinkTargetFootnote org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getFootnoteMut(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::Footnote&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getFootnote), self, org_context);
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::isFile_const(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isFile), self, org_context);
}
haxorg_LinkTargetFile org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getFileConst_const(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::File const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getFile), self, org_context);
}
haxorg_LinkTargetFile org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getFileMut(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::File&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getFile), self, org_context);
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::isAttachment_const(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isAttachment), self, org_context);
}
haxorg_LinkTargetAttachment org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getAttachmentConst_const(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::Attachment const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getAttachment), self, org_context);
}
haxorg_LinkTargetAttachment org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getAttachmentMut(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::Attachment&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getAttachment), self, org_context);
}
haxorg_LinkTargetKind org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getKind_const(haxorg_LinkTarget self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget::Kind(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getKind), self, org_context);
}
bool org::bind::c::VTable<haxorg_LinkTargetRaw, haxorg_LinkTargetRaw_vtable>::__eq___const(haxorg_LinkTargetRaw self, OrgContext* org_context, haxorg_LinkTargetRaw other) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetRaw, haxorg_LinkTargetRaw_vtable>(static_cast<bool(org::sem::LinkTarget::Raw::*)(org::sem::LinkTarget::Raw const&) const>(&org::sem::LinkTarget::Raw::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_LinkTargetId, haxorg_LinkTargetId_vtable>::__eq___const(haxorg_LinkTargetId self, OrgContext* org_context, haxorg_LinkTargetId other) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetId, haxorg_LinkTargetId_vtable>(static_cast<bool(org::sem::LinkTarget::Id::*)(org::sem::LinkTarget::Id const&) const>(&org::sem::LinkTarget::Id::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_LinkTargetCustomId, haxorg_LinkTargetCustomId_vtable>::__eq___const(haxorg_LinkTargetCustomId self, OrgContext* org_context, haxorg_LinkTargetCustomId other) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetCustomId, haxorg_LinkTargetCustomId_vtable>(static_cast<bool(org::sem::LinkTarget::CustomId::*)(org::sem::LinkTarget::CustomId const&) const>(&org::sem::LinkTarget::CustomId::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_LinkTargetSubtreeTitle, haxorg_LinkTargetSubtreeTitle_vtable>::__eq___const(haxorg_LinkTargetSubtreeTitle self, OrgContext* org_context, haxorg_LinkTargetSubtreeTitle other) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetSubtreeTitle, haxorg_LinkTargetSubtreeTitle_vtable>(static_cast<bool(org::sem::LinkTarget::SubtreeTitle::*)(org::sem::LinkTarget::SubtreeTitle const&) const>(&org::sem::LinkTarget::SubtreeTitle::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_LinkTargetPerson, haxorg_LinkTargetPerson_vtable>::__eq___const(haxorg_LinkTargetPerson self, OrgContext* org_context, haxorg_LinkTargetPerson other) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetPerson, haxorg_LinkTargetPerson_vtable>(static_cast<bool(org::sem::LinkTarget::Person::*)(org::sem::LinkTarget::Person const&) const>(&org::sem::LinkTarget::Person::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_LinkTargetUserProtocol, haxorg_LinkTargetUserProtocol_vtable>::__eq___const(haxorg_LinkTargetUserProtocol self, OrgContext* org_context, haxorg_LinkTargetUserProtocol other) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetUserProtocol, haxorg_LinkTargetUserProtocol_vtable>(static_cast<bool(org::sem::LinkTarget::UserProtocol::*)(org::sem::LinkTarget::UserProtocol const&) const>(&org::sem::LinkTarget::UserProtocol::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_LinkTargetInternal, haxorg_LinkTargetInternal_vtable>::__eq___const(haxorg_LinkTargetInternal self, OrgContext* org_context, haxorg_LinkTargetInternal other) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetInternal, haxorg_LinkTargetInternal_vtable>(static_cast<bool(org::sem::LinkTarget::Internal::*)(org::sem::LinkTarget::Internal const&) const>(&org::sem::LinkTarget::Internal::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_LinkTargetFootnote, haxorg_LinkTargetFootnote_vtable>::__eq___const(haxorg_LinkTargetFootnote self, OrgContext* org_context, haxorg_LinkTargetFootnote other) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetFootnote, haxorg_LinkTargetFootnote_vtable>(static_cast<bool(org::sem::LinkTarget::Footnote::*)(org::sem::LinkTarget::Footnote const&) const>(&org::sem::LinkTarget::Footnote::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_LinkTargetFile, haxorg_LinkTargetFile_vtable>::__eq___const(haxorg_LinkTargetFile self, OrgContext* org_context, haxorg_LinkTargetFile other) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetFile, haxorg_LinkTargetFile_vtable>(static_cast<bool(org::sem::LinkTarget::File::*)(org::sem::LinkTarget::File const&) const>(&org::sem::LinkTarget::File::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_LinkTargetAttachment, haxorg_LinkTargetAttachment_vtable>::__eq___const(haxorg_LinkTargetAttachment self, OrgContext* org_context, haxorg_LinkTargetAttachment other) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetAttachment, haxorg_LinkTargetAttachment_vtable>(static_cast<bool(org::sem::LinkTarget::Attachment::*)(org::sem::LinkTarget::Attachment const&) const>(&org::sem::LinkTarget::Attachment::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::__eq___const(haxorg_SubtreeLogHead self, OrgContext* org_context, haxorg_SubtreeLogHead other) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<bool(org::sem::SubtreeLogHead::*)(org::sem::SubtreeLogHead const&) const>(&org::sem::SubtreeLogHead::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::isPriority_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isPriority), self, org_context);
}
haxorg_SubtreeLogHeadPriority org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getPriorityConst_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Priority const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getPriority), self, org_context);
}
haxorg_SubtreeLogHeadPriority org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getPriorityMut(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Priority&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getPriority), self, org_context);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::isNote_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isNote), self, org_context);
}
haxorg_SubtreeLogHeadNote org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getNoteConst_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Note const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getNote), self, org_context);
}
haxorg_SubtreeLogHeadNote org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getNoteMut(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Note&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getNote), self, org_context);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::isRefile_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isRefile), self, org_context);
}
haxorg_SubtreeLogHeadRefile org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getRefileConst_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Refile const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getRefile), self, org_context);
}
haxorg_SubtreeLogHeadRefile org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getRefileMut(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Refile&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getRefile), self, org_context);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::isClock_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isClock), self, org_context);
}
haxorg_SubtreeLogHeadClock org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getClockConst_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Clock const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getClock), self, org_context);
}
haxorg_SubtreeLogHeadClock org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getClockMut(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Clock&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getClock), self, org_context);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::isState_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isState), self, org_context);
}
haxorg_SubtreeLogHeadState org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getStateConst_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::State const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getState), self, org_context);
}
haxorg_SubtreeLogHeadState org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getStateMut(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::State&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getState), self, org_context);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::isDeadline_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isDeadline), self, org_context);
}
haxorg_SubtreeLogHeadDeadline org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getDeadlineConst_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Deadline const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getDeadline), self, org_context);
}
haxorg_SubtreeLogHeadDeadline org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getDeadlineMut(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Deadline&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getDeadline), self, org_context);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::isSchedule_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isSchedule), self, org_context);
}
haxorg_SubtreeLogHeadSchedule org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getScheduleConst_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Schedule const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getSchedule), self, org_context);
}
haxorg_SubtreeLogHeadSchedule org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getScheduleMut(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Schedule&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getSchedule), self, org_context);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::isTag_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isTag), self, org_context);
}
haxorg_SubtreeLogHeadTag org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getTagConst_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Tag const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getTag), self, org_context);
}
haxorg_SubtreeLogHeadTag org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getTagMut(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Tag&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getTag), self, org_context);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::isUnknown_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isUnknown), self, org_context);
}
haxorg_SubtreeLogHeadUnknown org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getUnknownConst_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Unknown const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getUnknown), self, org_context);
}
haxorg_SubtreeLogHeadUnknown org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getUnknownMut(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Unknown&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getUnknown), self, org_context);
}
haxorg_SubtreeLogHeadKind org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getLogKind_const(haxorg_SubtreeLogHead self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead::Kind(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getLogKind), self, org_context);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHeadPriority, haxorg_SubtreeLogHeadPriority_vtable>::__eq___const(haxorg_SubtreeLogHeadPriority self, OrgContext* org_context, haxorg_SubtreeLogHeadPriority other) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadPriority, haxorg_SubtreeLogHeadPriority_vtable>(static_cast<bool(org::sem::SubtreeLogHead::Priority::*)(org::sem::SubtreeLogHead::Priority const&) const>(&org::sem::SubtreeLogHead::Priority::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHeadNote, haxorg_SubtreeLogHeadNote_vtable>::__eq___const(haxorg_SubtreeLogHeadNote self, OrgContext* org_context, haxorg_SubtreeLogHeadNote other) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadNote, haxorg_SubtreeLogHeadNote_vtable>(static_cast<bool(org::sem::SubtreeLogHead::Note::*)(org::sem::SubtreeLogHead::Note const&) const>(&org::sem::SubtreeLogHead::Note::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHeadRefile, haxorg_SubtreeLogHeadRefile_vtable>::__eq___const(haxorg_SubtreeLogHeadRefile self, OrgContext* org_context, haxorg_SubtreeLogHeadRefile other) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadRefile, haxorg_SubtreeLogHeadRefile_vtable>(static_cast<bool(org::sem::SubtreeLogHead::Refile::*)(org::sem::SubtreeLogHead::Refile const&) const>(&org::sem::SubtreeLogHead::Refile::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHeadClock, haxorg_SubtreeLogHeadClock_vtable>::__eq___const(haxorg_SubtreeLogHeadClock self, OrgContext* org_context, haxorg_SubtreeLogHeadClock other) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadClock, haxorg_SubtreeLogHeadClock_vtable>(static_cast<bool(org::sem::SubtreeLogHead::Clock::*)(org::sem::SubtreeLogHead::Clock const&) const>(&org::sem::SubtreeLogHead::Clock::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHeadState, haxorg_SubtreeLogHeadState_vtable>::__eq___const(haxorg_SubtreeLogHeadState self, OrgContext* org_context, haxorg_SubtreeLogHeadState other) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadState, haxorg_SubtreeLogHeadState_vtable>(static_cast<bool(org::sem::SubtreeLogHead::State::*)(org::sem::SubtreeLogHead::State const&) const>(&org::sem::SubtreeLogHead::State::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHeadDeadline, haxorg_SubtreeLogHeadDeadline_vtable>::__eq___const(haxorg_SubtreeLogHeadDeadline self, OrgContext* org_context, haxorg_SubtreeLogHeadDeadline other) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadDeadline, haxorg_SubtreeLogHeadDeadline_vtable>(static_cast<bool(org::sem::SubtreeLogHead::Deadline::*)(org::sem::SubtreeLogHead::Deadline const&) const>(&org::sem::SubtreeLogHead::Deadline::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHeadSchedule, haxorg_SubtreeLogHeadSchedule_vtable>::__eq___const(haxorg_SubtreeLogHeadSchedule self, OrgContext* org_context, haxorg_SubtreeLogHeadSchedule other) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadSchedule, haxorg_SubtreeLogHeadSchedule_vtable>(static_cast<bool(org::sem::SubtreeLogHead::Schedule::*)(org::sem::SubtreeLogHead::Schedule const&) const>(&org::sem::SubtreeLogHead::Schedule::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHeadTag, haxorg_SubtreeLogHeadTag_vtable>::__eq___const(haxorg_SubtreeLogHeadTag self, OrgContext* org_context, haxorg_SubtreeLogHeadTag other) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadTag, haxorg_SubtreeLogHeadTag_vtable>(static_cast<bool(org::sem::SubtreeLogHead::Tag::*)(org::sem::SubtreeLogHead::Tag const&) const>(&org::sem::SubtreeLogHead::Tag::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHeadUnknown, haxorg_SubtreeLogHeadUnknown_vtable>::__eq___const(haxorg_SubtreeLogHeadUnknown self, OrgContext* org_context, haxorg_SubtreeLogHeadUnknown other) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadUnknown, haxorg_SubtreeLogHeadUnknown_vtable>(static_cast<bool(org::sem::SubtreeLogHead::Unknown::*)(org::sem::SubtreeLogHead::Unknown const&) const>(&org::sem::SubtreeLogHead::Unknown::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_SubtreeCompletion, haxorg_SubtreeCompletion_vtable>::__eq___const(haxorg_SubtreeCompletion self, OrgContext* org_context, haxorg_SubtreeCompletion other) {
  return org::bind::c::execute_cpp<haxorg_SubtreeCompletion, haxorg_SubtreeCompletion_vtable>(static_cast<bool(org::sem::SubtreeCompletion::*)(org::sem::SubtreeCompletion const&) const>(&org::sem::SubtreeCompletion::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_AttrList, haxorg_AttrList_vtable>::__eq___const(haxorg_AttrList self, OrgContext* org_context, haxorg_AttrList other) {
  return org::bind::c::execute_cpp<haxorg_AttrList, haxorg_AttrList_vtable>(static_cast<bool(org::sem::AttrList::*)(org::sem::AttrList const&) const>(&org::sem::AttrList::operator==), self, org_context, other);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::getFlatArgs_const(haxorg_AttrGroup self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getFlatArgs), self, org_context);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::getAttrs_const(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdOpt key) {
  return org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::AttrGroup::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::AttrGroup::getAttrs), self, org_context, key);
}
void org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::setNamedAttr(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdStr key, haxorg_HstdVec attrs) {
  return org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<void(org::sem::AttrGroup::*)(hstd::Str const&, hstd::Vec<org::sem::AttrValue> const&)>(&org::sem::AttrGroup::setNamedAttr), self, org_context, key, attrs);
}
void org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::setPositionalAttr(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdVec items) {
  return org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<void(org::sem::AttrGroup::*)(hstd::Vec<org::sem::AttrValue> const&)>(&org::sem::AttrGroup::setPositionalAttr), self, org_context, items);
}
int org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::getPositionalSize_const(haxorg_AttrGroup self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<int(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getPositionalSize), self, org_context);
}
int org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::getNamedSize_const(haxorg_AttrGroup self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<int(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getNamedSize), self, org_context);
}
bool org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::isEmpty_const(haxorg_AttrGroup self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<bool(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::isEmpty), self, org_context);
}
haxorg_AttrList org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::getAll_const(haxorg_AttrGroup self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<org::sem::AttrList(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getAll), self, org_context);
}
haxorg_AttrValue org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::atPositional_const(haxorg_AttrGroup self, OrgContext* org_context, int index) {
  return org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<org::sem::AttrValue const&(org::sem::AttrGroup::*)(int) const>(&org::sem::AttrGroup::atPositional), self, org_context, index);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::getPositional_const(haxorg_AttrGroup self, OrgContext* org_context, int index) {
  return org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::AttrGroup::*)(int) const>(&org::sem::AttrGroup::getPositional), self, org_context, index);
}
haxorg_AttrList org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::atNamed_const(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdStr index) {
  return org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<org::sem::AttrList const&(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atNamed), self, org_context, index);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::getNamed_const(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdStr index) {
  return org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<hstd::Opt<org::sem::AttrList>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getNamed), self, org_context, index);
}
haxorg_AttrValue org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::atFirstNamed_const(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdStr index) {
  return org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<org::sem::AttrValue const&(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atFirstNamed), self, org_context, index);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::getFirstNamed_const(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdStr index) {
  return org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getFirstNamed), self, org_context, index);
}
haxorg_AttrList org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::atVarNamed_const(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdStr index) {
  return org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<org::sem::AttrList(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atVarNamed), self, org_context, index);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::getVarNamed_const(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdStr index) {
  return org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<hstd::Opt<org::sem::AttrList>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getVarNamed), self, org_context, index);
}
haxorg_AttrValue org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::atFirstVarNamed_const(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdStr index) {
  return org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<org::sem::AttrValue(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atFirstVarNamed), self, org_context, index);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::getFirstVarNamed_const(haxorg_AttrGroup self, OrgContext* org_context, haxorg_HstdStr index) {
  return org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getFirstVarNamed), self, org_context, index);
}
bool org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::__eq___const(haxorg_AttrGroup self, OrgContext* org_context, haxorg_AttrGroup other) {
  return org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<bool(org::sem::AttrGroup::*)(org::sem::AttrGroup const&) const>(&org::sem::AttrGroup::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_OrgCodeEvalInput, haxorg_OrgCodeEvalInput_vtable>::__eq___const(haxorg_OrgCodeEvalInput self, OrgContext* org_context, haxorg_OrgCodeEvalInput other) {
  return org::bind::c::execute_cpp<haxorg_OrgCodeEvalInput, haxorg_OrgCodeEvalInput_vtable>(static_cast<bool(org::sem::OrgCodeEvalInput::*)(org::sem::OrgCodeEvalInput const&) const>(&org::sem::OrgCodeEvalInput::operator==), self, org_context, other);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_OrgCodeEvalInput, haxorg_OrgCodeEvalInput_vtable>::getVariable_const(haxorg_OrgCodeEvalInput self, OrgContext* org_context, haxorg_HstdStr name) {
  return org::bind::c::execute_cpp<haxorg_OrgCodeEvalInput, haxorg_OrgCodeEvalInput_vtable>(static_cast<hstd::Opt<org::sem::OrgCodeEvalInput::Var>(org::sem::OrgCodeEvalInput::*)(hstd::Str const&) const>(&org::sem::OrgCodeEvalInput::getVariable), self, org_context, name);
}
bool org::bind::c::VTable<haxorg_OrgCodeEvalInputVar, haxorg_OrgCodeEvalInputVar_vtable>::__eq___const(haxorg_OrgCodeEvalInputVar self, OrgContext* org_context, haxorg_OrgCodeEvalInputVar other) {
  return org::bind::c::execute_cpp<haxorg_OrgCodeEvalInputVar, haxorg_OrgCodeEvalInputVar_vtable>(static_cast<bool(org::sem::OrgCodeEvalInput::Var::*)(org::sem::OrgCodeEvalInput::Var const&) const>(&org::sem::OrgCodeEvalInput::Var::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_OrgCodeEvalOutput, haxorg_OrgCodeEvalOutput_vtable>::__eq___const(haxorg_OrgCodeEvalOutput self, OrgContext* org_context, haxorg_OrgCodeEvalOutput other) {
  return org::bind::c::execute_cpp<haxorg_OrgCodeEvalOutput, haxorg_OrgCodeEvalOutput_vtable>(static_cast<bool(org::sem::OrgCodeEvalOutput::*)(org::sem::OrgCodeEvalOutput const&) const>(&org::sem::OrgCodeEvalOutput::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ColumnView, haxorg_ColumnView_vtable>::__eq___const(haxorg_ColumnView self, OrgContext* org_context, haxorg_ColumnView other) {
  return org::bind::c::execute_cpp<haxorg_ColumnView, haxorg_ColumnView_vtable>(static_cast<bool(org::sem::ColumnView::*)(org::sem::ColumnView const&) const>(&org::sem::ColumnView::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>::__eq___const(haxorg_ColumnViewSummary self, OrgContext* org_context, haxorg_ColumnViewSummary other) {
  return org::bind::c::execute_cpp<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>(static_cast<bool(org::sem::ColumnView::Summary::*)(org::sem::ColumnView::Summary const&) const>(&org::sem::ColumnView::Summary::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>::isCheckboxAggregate_const(haxorg_ColumnViewSummary self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>(static_cast<bool(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::isCheckboxAggregate), self, org_context);
}
haxorg_ColumnViewSummaryCheckboxAggregate org::bind::c::VTable<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>::getCheckboxAggregateConst_const(haxorg_ColumnViewSummary self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>(static_cast<org::sem::ColumnView::Summary::CheckboxAggregate const&(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::getCheckboxAggregate), self, org_context);
}
haxorg_ColumnViewSummaryCheckboxAggregate org::bind::c::VTable<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>::getCheckboxAggregateMut(haxorg_ColumnViewSummary self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>(static_cast<org::sem::ColumnView::Summary::CheckboxAggregate&(org::sem::ColumnView::Summary::*)()>(&org::sem::ColumnView::Summary::getCheckboxAggregate), self, org_context);
}
bool org::bind::c::VTable<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>::isMathAggregate_const(haxorg_ColumnViewSummary self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>(static_cast<bool(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::isMathAggregate), self, org_context);
}
haxorg_ColumnViewSummaryMathAggregate org::bind::c::VTable<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>::getMathAggregateConst_const(haxorg_ColumnViewSummary self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>(static_cast<org::sem::ColumnView::Summary::MathAggregate const&(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::getMathAggregate), self, org_context);
}
haxorg_ColumnViewSummaryMathAggregate org::bind::c::VTable<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>::getMathAggregateMut(haxorg_ColumnViewSummary self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>(static_cast<org::sem::ColumnView::Summary::MathAggregate&(org::sem::ColumnView::Summary::*)()>(&org::sem::ColumnView::Summary::getMathAggregate), self, org_context);
}
haxorg_ColumnViewSummaryKind org::bind::c::VTable<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>::getKind_const(haxorg_ColumnViewSummary self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>(static_cast<org::sem::ColumnView::Summary::Kind(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::getKind), self, org_context);
}
bool org::bind::c::VTable<haxorg_ColumnViewSummaryCheckboxAggregate, haxorg_ColumnViewSummaryCheckboxAggregate_vtable>::__eq___const(haxorg_ColumnViewSummaryCheckboxAggregate self, OrgContext* org_context, haxorg_ColumnViewSummaryCheckboxAggregate other) {
  return org::bind::c::execute_cpp<haxorg_ColumnViewSummaryCheckboxAggregate, haxorg_ColumnViewSummaryCheckboxAggregate_vtable>(static_cast<bool(org::sem::ColumnView::Summary::CheckboxAggregate::*)(org::sem::ColumnView::Summary::CheckboxAggregate const&) const>(&org::sem::ColumnView::Summary::CheckboxAggregate::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ColumnViewSummaryMathAggregate, haxorg_ColumnViewSummaryMathAggregate_vtable>::__eq___const(haxorg_ColumnViewSummaryMathAggregate self, OrgContext* org_context, haxorg_ColumnViewSummaryMathAggregate other) {
  return org::bind::c::execute_cpp<haxorg_ColumnViewSummaryMathAggregate, haxorg_ColumnViewSummaryMathAggregate_vtable>(static_cast<bool(org::sem::ColumnView::Summary::MathAggregate::*)(org::sem::ColumnView::Summary::MathAggregate const&) const>(&org::sem::ColumnView::Summary::MathAggregate::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ColumnViewColumn, haxorg_ColumnViewColumn_vtable>::__eq___const(haxorg_ColumnViewColumn self, OrgContext* org_context, haxorg_ColumnViewColumn other) {
  return org::bind::c::execute_cpp<haxorg_ColumnViewColumn, haxorg_ColumnViewColumn_vtable>(static_cast<bool(org::sem::ColumnView::Column::*)(org::sem::ColumnView::Column const&) const>(&org::sem::ColumnView::Column::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_BlockCodeLine, haxorg_BlockCodeLine_vtable>::__eq___const(haxorg_BlockCodeLine self, OrgContext* org_context, haxorg_BlockCodeLine other) {
  return org::bind::c::execute_cpp<haxorg_BlockCodeLine, haxorg_BlockCodeLine_vtable>(static_cast<bool(org::sem::BlockCodeLine::*)(org::sem::BlockCodeLine const&) const>(&org::sem::BlockCodeLine::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::__eq___const(haxorg_BlockCodeLinePart self, OrgContext* org_context, haxorg_BlockCodeLinePart other) {
  return org::bind::c::execute_cpp<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>(static_cast<bool(org::sem::BlockCodeLine::Part::*)(org::sem::BlockCodeLine::Part const&) const>(&org::sem::BlockCodeLine::Part::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::isRaw_const(haxorg_BlockCodeLinePart self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>(static_cast<bool(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::isRaw), self, org_context);
}
haxorg_BlockCodeLinePartRaw org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::getRawConst_const(haxorg_BlockCodeLinePart self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>(static_cast<org::sem::BlockCodeLine::Part::Raw const&(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::getRaw), self, org_context);
}
haxorg_BlockCodeLinePartRaw org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::getRawMut(haxorg_BlockCodeLinePart self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>(static_cast<org::sem::BlockCodeLine::Part::Raw&(org::sem::BlockCodeLine::Part::*)()>(&org::sem::BlockCodeLine::Part::getRaw), self, org_context);
}
bool org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::isCallout_const(haxorg_BlockCodeLinePart self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>(static_cast<bool(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::isCallout), self, org_context);
}
haxorg_BlockCodeLinePartCallout org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::getCalloutConst_const(haxorg_BlockCodeLinePart self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>(static_cast<org::sem::BlockCodeLine::Part::Callout const&(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::getCallout), self, org_context);
}
haxorg_BlockCodeLinePartCallout org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::getCalloutMut(haxorg_BlockCodeLinePart self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>(static_cast<org::sem::BlockCodeLine::Part::Callout&(org::sem::BlockCodeLine::Part::*)()>(&org::sem::BlockCodeLine::Part::getCallout), self, org_context);
}
bool org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::isTangle_const(haxorg_BlockCodeLinePart self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>(static_cast<bool(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::isTangle), self, org_context);
}
haxorg_BlockCodeLinePartTangle org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::getTangleConst_const(haxorg_BlockCodeLinePart self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>(static_cast<org::sem::BlockCodeLine::Part::Tangle const&(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::getTangle), self, org_context);
}
haxorg_BlockCodeLinePartTangle org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::getTangleMut(haxorg_BlockCodeLinePart self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>(static_cast<org::sem::BlockCodeLine::Part::Tangle&(org::sem::BlockCodeLine::Part::*)()>(&org::sem::BlockCodeLine::Part::getTangle), self, org_context);
}
haxorg_BlockCodeLinePartKind org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::getKind_const(haxorg_BlockCodeLinePart self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>(static_cast<org::sem::BlockCodeLine::Part::Kind(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::getKind), self, org_context);
}
bool org::bind::c::VTable<haxorg_BlockCodeLinePartRaw, haxorg_BlockCodeLinePartRaw_vtable>::__eq___const(haxorg_BlockCodeLinePartRaw self, OrgContext* org_context, haxorg_BlockCodeLinePartRaw other) {
  return org::bind::c::execute_cpp<haxorg_BlockCodeLinePartRaw, haxorg_BlockCodeLinePartRaw_vtable>(static_cast<bool(org::sem::BlockCodeLine::Part::Raw::*)(org::sem::BlockCodeLine::Part::Raw const&) const>(&org::sem::BlockCodeLine::Part::Raw::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_BlockCodeLinePartCallout, haxorg_BlockCodeLinePartCallout_vtable>::__eq___const(haxorg_BlockCodeLinePartCallout self, OrgContext* org_context, haxorg_BlockCodeLinePartCallout other) {
  return org::bind::c::execute_cpp<haxorg_BlockCodeLinePartCallout, haxorg_BlockCodeLinePartCallout_vtable>(static_cast<bool(org::sem::BlockCodeLine::Part::Callout::*)(org::sem::BlockCodeLine::Part::Callout const&) const>(&org::sem::BlockCodeLine::Part::Callout::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_BlockCodeLinePartTangle, haxorg_BlockCodeLinePartTangle_vtable>::__eq___const(haxorg_BlockCodeLinePartTangle self, OrgContext* org_context, haxorg_BlockCodeLinePartTangle other) {
  return org::bind::c::execute_cpp<haxorg_BlockCodeLinePartTangle, haxorg_BlockCodeLinePartTangle_vtable>(static_cast<bool(org::sem::BlockCodeLine::Part::Tangle::*)(org::sem::BlockCodeLine::Part::Tangle const&) const>(&org::sem::BlockCodeLine::Part::Tangle::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>::__eq___const(haxorg_DocumentExportConfig self, OrgContext* org_context, haxorg_DocumentExportConfig other) {
  return org::bind::c::execute_cpp<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>(static_cast<bool(org::sem::DocumentExportConfig::*)(org::sem::DocumentExportConfig const&) const>(&org::sem::DocumentExportConfig::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>::isDoExport_const(haxorg_DocumentExportConfig self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>(static_cast<bool(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::isDoExport), self, org_context);
}
haxorg_DocumentExportConfigDoExport org::bind::c::VTable<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>::getDoExportConst_const(haxorg_DocumentExportConfig self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>(static_cast<org::sem::DocumentExportConfig::DoExport const&(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::getDoExport), self, org_context);
}
haxorg_DocumentExportConfigDoExport org::bind::c::VTable<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>::getDoExportMut(haxorg_DocumentExportConfig self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>(static_cast<org::sem::DocumentExportConfig::DoExport&(org::sem::DocumentExportConfig::*)()>(&org::sem::DocumentExportConfig::getDoExport), self, org_context);
}
bool org::bind::c::VTable<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>::isExportFixed_const(haxorg_DocumentExportConfig self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>(static_cast<bool(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::isExportFixed), self, org_context);
}
haxorg_DocumentExportConfigExportFixed org::bind::c::VTable<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>::getExportFixedConst_const(haxorg_DocumentExportConfig self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>(static_cast<org::sem::DocumentExportConfig::ExportFixed const&(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::getExportFixed), self, org_context);
}
haxorg_DocumentExportConfigExportFixed org::bind::c::VTable<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>::getExportFixedMut(haxorg_DocumentExportConfig self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>(static_cast<org::sem::DocumentExportConfig::ExportFixed&(org::sem::DocumentExportConfig::*)()>(&org::sem::DocumentExportConfig::getExportFixed), self, org_context);
}
haxorg_DocumentExportConfigTocExportKind org::bind::c::VTable<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>::getTocExportKind_const(haxorg_DocumentExportConfig self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>(static_cast<org::sem::DocumentExportConfig::TocExportKind(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::getTocExportKind), self, org_context);
}
bool org::bind::c::VTable<haxorg_DocumentExportConfigTaskExport, haxorg_DocumentExportConfigTaskExport_vtable>::__eq___const(haxorg_DocumentExportConfigTaskExport self, OrgContext* org_context, haxorg_DocumentExportConfigTaskExport other) {
  return org::bind::c::execute_cpp<haxorg_DocumentExportConfigTaskExport, haxorg_DocumentExportConfigTaskExport_vtable>(static_cast<bool(org::sem::DocumentExportConfig::TaskExport::*)(org::sem::DocumentExportConfig::TaskExport const&) const>(&org::sem::DocumentExportConfig::TaskExport::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_DocumentExportConfigDoExport, haxorg_DocumentExportConfigDoExport_vtable>::__eq___const(haxorg_DocumentExportConfigDoExport self, OrgContext* org_context, haxorg_DocumentExportConfigDoExport other) {
  return org::bind::c::execute_cpp<haxorg_DocumentExportConfigDoExport, haxorg_DocumentExportConfigDoExport_vtable>(static_cast<bool(org::sem::DocumentExportConfig::DoExport::*)(org::sem::DocumentExportConfig::DoExport const&) const>(&org::sem::DocumentExportConfig::DoExport::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_DocumentExportConfigExportFixed, haxorg_DocumentExportConfigExportFixed_vtable>::__eq___const(haxorg_DocumentExportConfigExportFixed self, OrgContext* org_context, haxorg_DocumentExportConfigExportFixed other) {
  return org::bind::c::execute_cpp<haxorg_DocumentExportConfigExportFixed, haxorg_DocumentExportConfigExportFixed_vtable>(static_cast<bool(org::sem::DocumentExportConfig::ExportFixed::*)(org::sem::DocumentExportConfig::ExportFixed const&) const>(&org::sem::DocumentExportConfig::ExportFixed::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_SubtreePeriod, haxorg_SubtreePeriod_vtable>::__eq___const(haxorg_SubtreePeriod self, OrgContext* org_context, haxorg_SubtreePeriod other) {
  return org::bind::c::execute_cpp<haxorg_SubtreePeriod, haxorg_SubtreePeriod_vtable>(static_cast<bool(org::sem::SubtreePeriod::*)(org::sem::SubtreePeriod const&) const>(&org::sem::SubtreePeriod::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isMatching_const(haxorg_NamedProperty self, OrgContext* org_context, haxorg_HstdStr kind, haxorg_HstdOpt subKind) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(org::sem::NamedProperty::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::NamedProperty::isMatching), self, org_context, kind, subKind);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getName_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<hstd::Str(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getName), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getSubKind_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<hstd::Opt<hstd::Str>(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getSubKind), self, org_context);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::__eq___const(haxorg_NamedProperty self, OrgContext* org_context, haxorg_NamedProperty other) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(org::sem::NamedProperty::*)(org::sem::NamedProperty const&) const>(&org::sem::NamedProperty::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isNonblocking_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isNonblocking), self, org_context);
}
haxorg_NamedPropertyNonblocking org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getNonblockingConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Nonblocking const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getNonblocking), self, org_context);
}
haxorg_NamedPropertyNonblocking org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getNonblockingMut(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Nonblocking&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getNonblocking), self, org_context);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isArchiveTime_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveTime), self, org_context);
}
haxorg_NamedPropertyArchiveTime org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveTimeConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ArchiveTime const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveTime), self, org_context);
}
haxorg_NamedPropertyArchiveTime org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveTimeMut(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ArchiveTime&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveTime), self, org_context);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isArchiveFile_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveFile), self, org_context);
}
haxorg_NamedPropertyArchiveFile org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveFileConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ArchiveFile const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveFile), self, org_context);
}
haxorg_NamedPropertyArchiveFile org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveFileMut(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ArchiveFile&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveFile), self, org_context);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isArchiveOlpath_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveOlpath), self, org_context);
}
haxorg_NamedPropertyArchiveOlpath org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveOlpathConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ArchiveOlpath const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveOlpath), self, org_context);
}
haxorg_NamedPropertyArchiveOlpath org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveOlpathMut(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ArchiveOlpath&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveOlpath), self, org_context);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isArchiveTarget_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveTarget), self, org_context);
}
haxorg_NamedPropertyArchiveTarget org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveTargetConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ArchiveTarget const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveTarget), self, org_context);
}
haxorg_NamedPropertyArchiveTarget org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveTargetMut(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ArchiveTarget&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveTarget), self, org_context);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isArchiveCategory_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveCategory), self, org_context);
}
haxorg_NamedPropertyArchiveCategory org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveCategoryConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ArchiveCategory const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveCategory), self, org_context);
}
haxorg_NamedPropertyArchiveCategory org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveCategoryMut(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ArchiveCategory&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveCategory), self, org_context);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isArchiveTodo_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveTodo), self, org_context);
}
haxorg_NamedPropertyArchiveTodo org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveTodoConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ArchiveTodo const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveTodo), self, org_context);
}
haxorg_NamedPropertyArchiveTodo org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveTodoMut(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ArchiveTodo&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveTodo), self, org_context);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isTrigger_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isTrigger), self, org_context);
}
haxorg_NamedPropertyTrigger org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getTriggerConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Trigger const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getTrigger), self, org_context);
}
haxorg_NamedPropertyTrigger org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getTriggerMut(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Trigger&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getTrigger), self, org_context);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isExportLatexClass_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexClass), self, org_context);
}
haxorg_NamedPropertyExportLatexClass org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getExportLatexClassConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ExportLatexClass const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getExportLatexClass), self, org_context);
}
haxorg_NamedPropertyExportLatexClass org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getExportLatexClassMut(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ExportLatexClass&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexClass), self, org_context);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isCookieData_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCookieData), self, org_context);
}
haxorg_NamedPropertyCookieData org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCookieDataConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::CookieData const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCookieData), self, org_context);
}
haxorg_NamedPropertyCookieData org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCookieDataMut(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::CookieData&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCookieData), self, org_context);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isExportLatexClassOptions_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexClassOptions), self, org_context);
}
haxorg_NamedPropertyExportLatexClassOptions org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getExportLatexClassOptionsConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ExportLatexClassOptions const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getExportLatexClassOptions), self, org_context);
}
haxorg_NamedPropertyExportLatexClassOptions org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getExportLatexClassOptionsMut(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ExportLatexClassOptions&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexClassOptions), self, org_context);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isExportLatexHeader_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexHeader), self, org_context);
}
haxorg_NamedPropertyExportLatexHeader org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getExportLatexHeaderConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ExportLatexHeader const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getExportLatexHeader), self, org_context);
}
haxorg_NamedPropertyExportLatexHeader org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getExportLatexHeaderMut(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ExportLatexHeader&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexHeader), self, org_context);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isExportLatexCompiler_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexCompiler), self, org_context);
}
haxorg_NamedPropertyExportLatexCompiler org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getExportLatexCompilerConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ExportLatexCompiler const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getExportLatexCompiler), self, org_context);
}
haxorg_NamedPropertyExportLatexCompiler org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getExportLatexCompilerMut(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ExportLatexCompiler&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexCompiler), self, org_context);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isOrdered_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isOrdered), self, org_context);
}
haxorg_NamedPropertyOrdered org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getOrderedConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Ordered const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getOrdered), self, org_context);
}
haxorg_NamedPropertyOrdered org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getOrderedMut(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Ordered&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getOrdered), self, org_context);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isEffort_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isEffort), self, org_context);
}
haxorg_NamedPropertyEffort org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getEffortConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Effort const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getEffort), self, org_context);
}
haxorg_NamedPropertyEffort org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getEffortMut(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Effort&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getEffort), self, org_context);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isVisibility_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isVisibility), self, org_context);
}
haxorg_NamedPropertyVisibility org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getVisibilityConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Visibility const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getVisibility), self, org_context);
}
haxorg_NamedPropertyVisibility org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getVisibilityMut(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Visibility&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getVisibility), self, org_context);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isExportOptions_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportOptions), self, org_context);
}
haxorg_NamedPropertyExportOptions org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getExportOptionsConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ExportOptions const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getExportOptions), self, org_context);
}
haxorg_NamedPropertyExportOptions org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getExportOptionsMut(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::ExportOptions&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportOptions), self, org_context);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isBlocker_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isBlocker), self, org_context);
}
haxorg_NamedPropertyBlocker org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getBlockerConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Blocker const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getBlocker), self, org_context);
}
haxorg_NamedPropertyBlocker org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getBlockerMut(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Blocker&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getBlocker), self, org_context);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isUnnumbered_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isUnnumbered), self, org_context);
}
haxorg_NamedPropertyUnnumbered org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getUnnumberedConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Unnumbered const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getUnnumbered), self, org_context);
}
haxorg_NamedPropertyUnnumbered org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getUnnumberedMut(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Unnumbered&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getUnnumbered), self, org_context);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isCreated_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCreated), self, org_context);
}
haxorg_NamedPropertyCreated org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCreatedConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Created const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCreated), self, org_context);
}
haxorg_NamedPropertyCreated org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCreatedMut(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Created&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCreated), self, org_context);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isRadioId_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isRadioId), self, org_context);
}
haxorg_NamedPropertyRadioId org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getRadioIdConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::RadioId const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getRadioId), self, org_context);
}
haxorg_NamedPropertyRadioId org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getRadioIdMut(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::RadioId&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getRadioId), self, org_context);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isHashtagDef_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isHashtagDef), self, org_context);
}
haxorg_NamedPropertyHashtagDef org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getHashtagDefConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::HashtagDef const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getHashtagDef), self, org_context);
}
haxorg_NamedPropertyHashtagDef org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getHashtagDefMut(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::HashtagDef&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getHashtagDef), self, org_context);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isCustomArgs_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomArgs), self, org_context);
}
haxorg_NamedPropertyCustomArgs org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCustomArgsConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::CustomArgs const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCustomArgs), self, org_context);
}
haxorg_NamedPropertyCustomArgs org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCustomArgsMut(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::CustomArgs&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomArgs), self, org_context);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isCustomRaw_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomRaw), self, org_context);
}
haxorg_NamedPropertyCustomRaw org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCustomRawConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::CustomRaw const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCustomRaw), self, org_context);
}
haxorg_NamedPropertyCustomRaw org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCustomRawMut(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::CustomRaw&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomRaw), self, org_context);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isCustomId_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomId), self, org_context);
}
haxorg_NamedPropertyCustomId org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCustomIdConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::CustomId const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCustomId), self, org_context);
}
haxorg_NamedPropertyCustomId org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCustomIdMut(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::CustomId&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomId), self, org_context);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isCustomSubtreeJson_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomSubtreeJson), self, org_context);
}
haxorg_NamedPropertyCustomSubtreeJson org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCustomSubtreeJsonConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::CustomSubtreeJson const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCustomSubtreeJson), self, org_context);
}
haxorg_NamedPropertyCustomSubtreeJson org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCustomSubtreeJsonMut(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::CustomSubtreeJson&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomSubtreeJson), self, org_context);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isCustomSubtreeFlags_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomSubtreeFlags), self, org_context);
}
haxorg_NamedPropertyCustomSubtreeFlags org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCustomSubtreeFlagsConst_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::CustomSubtreeFlags const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCustomSubtreeFlags), self, org_context);
}
haxorg_NamedPropertyCustomSubtreeFlags org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCustomSubtreeFlagsMut(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::CustomSubtreeFlags&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomSubtreeFlags), self, org_context);
}
haxorg_NamedPropertyKind org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getKind_const(haxorg_NamedProperty self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty, haxorg_NamedProperty_vtable>(static_cast<org::sem::NamedProperty::Kind(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getKind), self, org_context);
}
bool org::bind::c::VTable<haxorg_NamedPropertyNonblocking, haxorg_NamedPropertyNonblocking_vtable>::__eq___const(haxorg_NamedPropertyNonblocking self, OrgContext* org_context, haxorg_NamedPropertyNonblocking other) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyNonblocking, haxorg_NamedPropertyNonblocking_vtable>(static_cast<bool(org::sem::NamedProperty::Nonblocking::*)(org::sem::NamedProperty::Nonblocking const&) const>(&org::sem::NamedProperty::Nonblocking::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyArchiveTime, haxorg_NamedPropertyArchiveTime_vtable>::__eq___const(haxorg_NamedPropertyArchiveTime self, OrgContext* org_context, haxorg_NamedPropertyArchiveTime other) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveTime, haxorg_NamedPropertyArchiveTime_vtable>(static_cast<bool(org::sem::NamedProperty::ArchiveTime::*)(org::sem::NamedProperty::ArchiveTime const&) const>(&org::sem::NamedProperty::ArchiveTime::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyArchiveFile, haxorg_NamedPropertyArchiveFile_vtable>::__eq___const(haxorg_NamedPropertyArchiveFile self, OrgContext* org_context, haxorg_NamedPropertyArchiveFile other) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveFile, haxorg_NamedPropertyArchiveFile_vtable>(static_cast<bool(org::sem::NamedProperty::ArchiveFile::*)(org::sem::NamedProperty::ArchiveFile const&) const>(&org::sem::NamedProperty::ArchiveFile::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyArchiveOlpath, haxorg_NamedPropertyArchiveOlpath_vtable>::__eq___const(haxorg_NamedPropertyArchiveOlpath self, OrgContext* org_context, haxorg_NamedPropertyArchiveOlpath other) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveOlpath, haxorg_NamedPropertyArchiveOlpath_vtable>(static_cast<bool(org::sem::NamedProperty::ArchiveOlpath::*)(org::sem::NamedProperty::ArchiveOlpath const&) const>(&org::sem::NamedProperty::ArchiveOlpath::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyArchiveTarget, haxorg_NamedPropertyArchiveTarget_vtable>::__eq___const(haxorg_NamedPropertyArchiveTarget self, OrgContext* org_context, haxorg_NamedPropertyArchiveTarget other) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveTarget, haxorg_NamedPropertyArchiveTarget_vtable>(static_cast<bool(org::sem::NamedProperty::ArchiveTarget::*)(org::sem::NamedProperty::ArchiveTarget const&) const>(&org::sem::NamedProperty::ArchiveTarget::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyArchiveCategory, haxorg_NamedPropertyArchiveCategory_vtable>::__eq___const(haxorg_NamedPropertyArchiveCategory self, OrgContext* org_context, haxorg_NamedPropertyArchiveCategory other) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveCategory, haxorg_NamedPropertyArchiveCategory_vtable>(static_cast<bool(org::sem::NamedProperty::ArchiveCategory::*)(org::sem::NamedProperty::ArchiveCategory const&) const>(&org::sem::NamedProperty::ArchiveCategory::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyArchiveTodo, haxorg_NamedPropertyArchiveTodo_vtable>::__eq___const(haxorg_NamedPropertyArchiveTodo self, OrgContext* org_context, haxorg_NamedPropertyArchiveTodo other) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveTodo, haxorg_NamedPropertyArchiveTodo_vtable>(static_cast<bool(org::sem::NamedProperty::ArchiveTodo::*)(org::sem::NamedProperty::ArchiveTodo const&) const>(&org::sem::NamedProperty::ArchiveTodo::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyTrigger, haxorg_NamedPropertyTrigger_vtable>::__eq___const(haxorg_NamedPropertyTrigger self, OrgContext* org_context, haxorg_NamedPropertyTrigger other) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyTrigger, haxorg_NamedPropertyTrigger_vtable>(static_cast<bool(org::sem::NamedProperty::Trigger::*)(org::sem::NamedProperty::Trigger const&) const>(&org::sem::NamedProperty::Trigger::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyExportLatexClass, haxorg_NamedPropertyExportLatexClass_vtable>::__eq___const(haxorg_NamedPropertyExportLatexClass self, OrgContext* org_context, haxorg_NamedPropertyExportLatexClass other) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexClass, haxorg_NamedPropertyExportLatexClass_vtable>(static_cast<bool(org::sem::NamedProperty::ExportLatexClass::*)(org::sem::NamedProperty::ExportLatexClass const&) const>(&org::sem::NamedProperty::ExportLatexClass::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyCookieData, haxorg_NamedPropertyCookieData_vtable>::__eq___const(haxorg_NamedPropertyCookieData self, OrgContext* org_context, haxorg_NamedPropertyCookieData other) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyCookieData, haxorg_NamedPropertyCookieData_vtable>(static_cast<bool(org::sem::NamedProperty::CookieData::*)(org::sem::NamedProperty::CookieData const&) const>(&org::sem::NamedProperty::CookieData::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyExportLatexClassOptions, haxorg_NamedPropertyExportLatexClassOptions_vtable>::__eq___const(haxorg_NamedPropertyExportLatexClassOptions self, OrgContext* org_context, haxorg_NamedPropertyExportLatexClassOptions other) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexClassOptions, haxorg_NamedPropertyExportLatexClassOptions_vtable>(static_cast<bool(org::sem::NamedProperty::ExportLatexClassOptions::*)(org::sem::NamedProperty::ExportLatexClassOptions const&) const>(&org::sem::NamedProperty::ExportLatexClassOptions::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyExportLatexHeader, haxorg_NamedPropertyExportLatexHeader_vtable>::__eq___const(haxorg_NamedPropertyExportLatexHeader self, OrgContext* org_context, haxorg_NamedPropertyExportLatexHeader other) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexHeader, haxorg_NamedPropertyExportLatexHeader_vtable>(static_cast<bool(org::sem::NamedProperty::ExportLatexHeader::*)(org::sem::NamedProperty::ExportLatexHeader const&) const>(&org::sem::NamedProperty::ExportLatexHeader::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyExportLatexCompiler, haxorg_NamedPropertyExportLatexCompiler_vtable>::__eq___const(haxorg_NamedPropertyExportLatexCompiler self, OrgContext* org_context, haxorg_NamedPropertyExportLatexCompiler other) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexCompiler, haxorg_NamedPropertyExportLatexCompiler_vtable>(static_cast<bool(org::sem::NamedProperty::ExportLatexCompiler::*)(org::sem::NamedProperty::ExportLatexCompiler const&) const>(&org::sem::NamedProperty::ExportLatexCompiler::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyOrdered, haxorg_NamedPropertyOrdered_vtable>::__eq___const(haxorg_NamedPropertyOrdered self, OrgContext* org_context, haxorg_NamedPropertyOrdered other) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyOrdered, haxorg_NamedPropertyOrdered_vtable>(static_cast<bool(org::sem::NamedProperty::Ordered::*)(org::sem::NamedProperty::Ordered const&) const>(&org::sem::NamedProperty::Ordered::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyEffort, haxorg_NamedPropertyEffort_vtable>::__eq___const(haxorg_NamedPropertyEffort self, OrgContext* org_context, haxorg_NamedPropertyEffort other) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyEffort, haxorg_NamedPropertyEffort_vtable>(static_cast<bool(org::sem::NamedProperty::Effort::*)(org::sem::NamedProperty::Effort const&) const>(&org::sem::NamedProperty::Effort::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyVisibility, haxorg_NamedPropertyVisibility_vtable>::__eq___const(haxorg_NamedPropertyVisibility self, OrgContext* org_context, haxorg_NamedPropertyVisibility other) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyVisibility, haxorg_NamedPropertyVisibility_vtable>(static_cast<bool(org::sem::NamedProperty::Visibility::*)(org::sem::NamedProperty::Visibility const&) const>(&org::sem::NamedProperty::Visibility::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyExportOptions, haxorg_NamedPropertyExportOptions_vtable>::__eq___const(haxorg_NamedPropertyExportOptions self, OrgContext* org_context, haxorg_NamedPropertyExportOptions other) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyExportOptions, haxorg_NamedPropertyExportOptions_vtable>(static_cast<bool(org::sem::NamedProperty::ExportOptions::*)(org::sem::NamedProperty::ExportOptions const&) const>(&org::sem::NamedProperty::ExportOptions::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyBlocker, haxorg_NamedPropertyBlocker_vtable>::__eq___const(haxorg_NamedPropertyBlocker self, OrgContext* org_context, haxorg_NamedPropertyBlocker other) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyBlocker, haxorg_NamedPropertyBlocker_vtable>(static_cast<bool(org::sem::NamedProperty::Blocker::*)(org::sem::NamedProperty::Blocker const&) const>(&org::sem::NamedProperty::Blocker::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyUnnumbered, haxorg_NamedPropertyUnnumbered_vtable>::__eq___const(haxorg_NamedPropertyUnnumbered self, OrgContext* org_context, haxorg_NamedPropertyUnnumbered other) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyUnnumbered, haxorg_NamedPropertyUnnumbered_vtable>(static_cast<bool(org::sem::NamedProperty::Unnumbered::*)(org::sem::NamedProperty::Unnumbered const&) const>(&org::sem::NamedProperty::Unnumbered::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyCreated, haxorg_NamedPropertyCreated_vtable>::__eq___const(haxorg_NamedPropertyCreated self, OrgContext* org_context, haxorg_NamedPropertyCreated other) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyCreated, haxorg_NamedPropertyCreated_vtable>(static_cast<bool(org::sem::NamedProperty::Created::*)(org::sem::NamedProperty::Created const&) const>(&org::sem::NamedProperty::Created::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyRadioId, haxorg_NamedPropertyRadioId_vtable>::__eq___const(haxorg_NamedPropertyRadioId self, OrgContext* org_context, haxorg_NamedPropertyRadioId other) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyRadioId, haxorg_NamedPropertyRadioId_vtable>(static_cast<bool(org::sem::NamedProperty::RadioId::*)(org::sem::NamedProperty::RadioId const&) const>(&org::sem::NamedProperty::RadioId::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyHashtagDef, haxorg_NamedPropertyHashtagDef_vtable>::__eq___const(haxorg_NamedPropertyHashtagDef self, OrgContext* org_context, haxorg_NamedPropertyHashtagDef other) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyHashtagDef, haxorg_NamedPropertyHashtagDef_vtable>(static_cast<bool(org::sem::NamedProperty::HashtagDef::*)(org::sem::NamedProperty::HashtagDef const&) const>(&org::sem::NamedProperty::HashtagDef::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyCustomArgs, haxorg_NamedPropertyCustomArgs_vtable>::__eq___const(haxorg_NamedPropertyCustomArgs self, OrgContext* org_context, haxorg_NamedPropertyCustomArgs other) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomArgs, haxorg_NamedPropertyCustomArgs_vtable>(static_cast<bool(org::sem::NamedProperty::CustomArgs::*)(org::sem::NamedProperty::CustomArgs const&) const>(&org::sem::NamedProperty::CustomArgs::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyCustomRaw, haxorg_NamedPropertyCustomRaw_vtable>::__eq___const(haxorg_NamedPropertyCustomRaw self, OrgContext* org_context, haxorg_NamedPropertyCustomRaw other) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomRaw, haxorg_NamedPropertyCustomRaw_vtable>(static_cast<bool(org::sem::NamedProperty::CustomRaw::*)(org::sem::NamedProperty::CustomRaw const&) const>(&org::sem::NamedProperty::CustomRaw::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyCustomId, haxorg_NamedPropertyCustomId_vtable>::__eq___const(haxorg_NamedPropertyCustomId self, OrgContext* org_context, haxorg_NamedPropertyCustomId other) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomId, haxorg_NamedPropertyCustomId_vtable>(static_cast<bool(org::sem::NamedProperty::CustomId::*)(org::sem::NamedProperty::CustomId const&) const>(&org::sem::NamedProperty::CustomId::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyCustomSubtreeJson, haxorg_NamedPropertyCustomSubtreeJson_vtable>::__eq___const(haxorg_NamedPropertyCustomSubtreeJson self, OrgContext* org_context, haxorg_NamedPropertyCustomSubtreeJson other) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomSubtreeJson, haxorg_NamedPropertyCustomSubtreeJson_vtable>(static_cast<bool(org::sem::NamedProperty::CustomSubtreeJson::*)(org::sem::NamedProperty::CustomSubtreeJson const&) const>(&org::sem::NamedProperty::CustomSubtreeJson::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyCustomSubtreeFlags, haxorg_NamedPropertyCustomSubtreeFlags_vtable>::__eq___const(haxorg_NamedPropertyCustomSubtreeFlags self, OrgContext* org_context, haxorg_NamedPropertyCustomSubtreeFlags other) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomSubtreeFlags, haxorg_NamedPropertyCustomSubtreeFlags_vtable>(static_cast<bool(org::sem::NamedProperty::CustomSubtreeFlags::*)(org::sem::NamedProperty::CustomSubtreeFlags const&) const>(&org::sem::NamedProperty::CustomSubtreeFlags::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::__eq___const(haxorg_OrgDiagnostics self, OrgContext* org_context, haxorg_OrgDiagnostics other) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<bool(org::sem::OrgDiagnostics::*)(org::sem::OrgDiagnostics const&) const>(&org::sem::OrgDiagnostics::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::isParseTokenError_const(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<bool(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::isParseTokenError), self, org_context);
}
haxorg_OrgDiagnosticsParseTokenError org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getParseTokenErrorConst_const(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<org::sem::OrgDiagnostics::ParseTokenError const&(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::getParseTokenError), self, org_context);
}
haxorg_OrgDiagnosticsParseTokenError org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getParseTokenErrorMut(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<org::sem::OrgDiagnostics::ParseTokenError&(org::sem::OrgDiagnostics::*)()>(&org::sem::OrgDiagnostics::getParseTokenError), self, org_context);
}
bool org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::isParseError_const(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<bool(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::isParseError), self, org_context);
}
haxorg_OrgDiagnosticsParseError org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getParseErrorConst_const(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<org::sem::OrgDiagnostics::ParseError const&(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::getParseError), self, org_context);
}
haxorg_OrgDiagnosticsParseError org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getParseErrorMut(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<org::sem::OrgDiagnostics::ParseError&(org::sem::OrgDiagnostics::*)()>(&org::sem::OrgDiagnostics::getParseError), self, org_context);
}
bool org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::isIncludeError_const(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<bool(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::isIncludeError), self, org_context);
}
haxorg_OrgDiagnosticsIncludeError org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getIncludeErrorConst_const(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<org::sem::OrgDiagnostics::IncludeError const&(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::getIncludeError), self, org_context);
}
haxorg_OrgDiagnosticsIncludeError org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getIncludeErrorMut(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<org::sem::OrgDiagnostics::IncludeError&(org::sem::OrgDiagnostics::*)()>(&org::sem::OrgDiagnostics::getIncludeError), self, org_context);
}
bool org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::isConvertError_const(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<bool(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::isConvertError), self, org_context);
}
haxorg_OrgDiagnosticsConvertError org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getConvertErrorConst_const(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<org::sem::OrgDiagnostics::ConvertError const&(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::getConvertError), self, org_context);
}
haxorg_OrgDiagnosticsConvertError org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getConvertErrorMut(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<org::sem::OrgDiagnostics::ConvertError&(org::sem::OrgDiagnostics::*)()>(&org::sem::OrgDiagnostics::getConvertError), self, org_context);
}
bool org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::isInternalError_const(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<bool(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::isInternalError), self, org_context);
}
haxorg_OrgDiagnosticsInternalError org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getInternalErrorConst_const(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<org::sem::OrgDiagnostics::InternalError const&(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::getInternalError), self, org_context);
}
haxorg_OrgDiagnosticsInternalError org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getInternalErrorMut(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<org::sem::OrgDiagnostics::InternalError&(org::sem::OrgDiagnostics::*)()>(&org::sem::OrgDiagnostics::getInternalError), self, org_context);
}
haxorg_OrgDiagnosticsKind org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getKind_const(haxorg_OrgDiagnostics self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<org::sem::OrgDiagnostics::Kind(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::getKind), self, org_context);
}
bool org::bind::c::VTable<haxorg_OrgDiagnosticsParseTokenError, haxorg_OrgDiagnosticsParseTokenError_vtable>::__eq___const(haxorg_OrgDiagnosticsParseTokenError self, OrgContext* org_context, haxorg_OrgDiagnosticsParseTokenError other) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsParseTokenError, haxorg_OrgDiagnosticsParseTokenError_vtable>(static_cast<bool(org::sem::OrgDiagnostics::ParseTokenError::*)(org::sem::OrgDiagnostics::ParseTokenError const&) const>(&org::sem::OrgDiagnostics::ParseTokenError::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_OrgDiagnosticsParseError, haxorg_OrgDiagnosticsParseError_vtable>::__eq___const(haxorg_OrgDiagnosticsParseError self, OrgContext* org_context, haxorg_OrgDiagnosticsParseError other) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsParseError, haxorg_OrgDiagnosticsParseError_vtable>(static_cast<bool(org::sem::OrgDiagnostics::ParseError::*)(org::sem::OrgDiagnostics::ParseError const&) const>(&org::sem::OrgDiagnostics::ParseError::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_OrgDiagnosticsIncludeError, haxorg_OrgDiagnosticsIncludeError_vtable>::__eq___const(haxorg_OrgDiagnosticsIncludeError self, OrgContext* org_context, haxorg_OrgDiagnosticsIncludeError other) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsIncludeError, haxorg_OrgDiagnosticsIncludeError_vtable>(static_cast<bool(org::sem::OrgDiagnostics::IncludeError::*)(org::sem::OrgDiagnostics::IncludeError const&) const>(&org::sem::OrgDiagnostics::IncludeError::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_OrgDiagnosticsConvertError, haxorg_OrgDiagnosticsConvertError_vtable>::__eq___const(haxorg_OrgDiagnosticsConvertError self, OrgContext* org_context, haxorg_OrgDiagnosticsConvertError other) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsConvertError, haxorg_OrgDiagnosticsConvertError_vtable>(static_cast<bool(org::sem::OrgDiagnostics::ConvertError::*)(org::sem::OrgDiagnostics::ConvertError const&) const>(&org::sem::OrgDiagnostics::ConvertError::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_OrgDiagnosticsInternalError, haxorg_OrgDiagnosticsInternalError_vtable>::__eq___const(haxorg_OrgDiagnosticsInternalError self, OrgContext* org_context, haxorg_OrgDiagnosticsInternalError other) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsInternalError, haxorg_OrgDiagnosticsInternalError_vtable>(static_cast<bool(org::sem::OrgDiagnostics::InternalError::*)(org::sem::OrgDiagnostics::InternalError const&) const>(&org::sem::OrgDiagnostics::InternalError::operator==), self, org_context, other);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getAttached_const(haxorg_Stmt self, OrgContext* org_context, haxorg_HstdOpt kind) {
  return org::bind::c::execute_cpp<haxorg_Stmt, haxorg_Stmt_vtable>(static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Stmt::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Stmt::getAttached), self, org_context, kind);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getCaption_const(haxorg_Stmt self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Stmt, haxorg_Stmt_vtable>(static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Stmt::*)() const>(&org::sem::Stmt::getCaption), self, org_context);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getName_const(haxorg_Stmt self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Stmt, haxorg_Stmt_vtable>(static_cast<hstd::Vec<hstd::Str>(org::sem::Stmt::*)() const>(&org::sem::Stmt::getName), self, org_context);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getAttrs_const(haxorg_Stmt self, OrgContext* org_context, haxorg_HstdOpt kind) {
  return org::bind::c::execute_cpp<haxorg_Stmt, haxorg_Stmt_vtable>(static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Stmt::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Stmt::getAttrs), self, org_context, kind);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getFirstAttr_const(haxorg_Stmt self, OrgContext* org_context, haxorg_HstdStr kind) {
  return org::bind::c::execute_cpp<haxorg_Stmt, haxorg_Stmt_vtable>(static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttr), self, org_context, kind);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getFirstAttrString_const(haxorg_Stmt self, OrgContext* org_context, haxorg_HstdStr kind) {
  return org::bind::c::execute_cpp<haxorg_Stmt, haxorg_Stmt_vtable>(static_cast<hstd::Opt<hstd::Str>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttrString), self, org_context, kind);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getFirstAttrInt_const(haxorg_Stmt self, OrgContext* org_context, haxorg_HstdStr kind) {
  return org::bind::c::execute_cpp<haxorg_Stmt, haxorg_Stmt_vtable>(static_cast<hstd::Opt<int>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttrInt), self, org_context, kind);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getFirstAttrBool_const(haxorg_Stmt self, OrgContext* org_context, haxorg_HstdStr kind) {
  return org::bind::c::execute_cpp<haxorg_Stmt, haxorg_Stmt_vtable>(static_cast<hstd::Opt<bool>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttrBool), self, org_context, kind);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getFirstAttrDouble_const(haxorg_Stmt self, OrgContext* org_context, haxorg_HstdStr kind) {
  return org::bind::c::execute_cpp<haxorg_Stmt, haxorg_Stmt_vtable>(static_cast<hstd::Opt<double>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttrDouble), self, org_context, kind);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getFirstAttrLisp_const(haxorg_Stmt self, OrgContext* org_context, haxorg_HstdStr kind) {
  return org::bind::c::execute_cpp<haxorg_Stmt, haxorg_Stmt_vtable>(static_cast<hstd::Opt<org::sem::AttrValue::LispValue>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttrLisp), self, org_context, kind);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getFirstAttrKind_const(haxorg_Stmt self, OrgContext* org_context, haxorg_HstdStr kind) {
  return org::bind::c::execute_cpp<haxorg_Stmt, haxorg_Stmt_vtable>(static_cast<hstd::Opt<org::sem::AttrValue::Kind>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttrKind), self, org_context, kind);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_Leaf, haxorg_Leaf_vtable>::getText_const(haxorg_Leaf self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Leaf, haxorg_Leaf_vtable>(static_cast<hstd::Str(org::sem::Leaf::*)() const>(&org::sem::Leaf::getText), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getYear_const(haxorg_Time self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Time, haxorg_Time_vtable>(static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getYear), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getMonth_const(haxorg_Time self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Time, haxorg_Time_vtable>(static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getMonth), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getDay_const(haxorg_Time self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Time, haxorg_Time_vtable>(static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getDay), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getHour_const(haxorg_Time self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Time, haxorg_Time_vtable>(static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getHour), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getMinute_const(haxorg_Time self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Time, haxorg_Time_vtable>(static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getMinute), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getSecond_const(haxorg_Time self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Time, haxorg_Time_vtable>(static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getSecond), self, org_context);
}
haxorg_UserTime org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getStaticTime_const(haxorg_Time self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Time, haxorg_Time_vtable>(static_cast<hstd::UserTime(org::sem::Time::*)() const>(&org::sem::Time::getStaticTime), self, org_context);
}
bool org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::isStatic_const(haxorg_Time self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Time, haxorg_Time_vtable>(static_cast<bool(org::sem::Time::*)() const>(&org::sem::Time::isStatic), self, org_context);
}
haxorg_TimeStatic org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getStaticConst_const(haxorg_Time self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Time, haxorg_Time_vtable>(static_cast<org::sem::Time::Static const&(org::sem::Time::*)() const>(&org::sem::Time::getStatic), self, org_context);
}
haxorg_TimeStatic org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getStaticMut(haxorg_Time self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Time, haxorg_Time_vtable>(static_cast<org::sem::Time::Static&(org::sem::Time::*)()>(&org::sem::Time::getStatic), self, org_context);
}
bool org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::isDynamic_const(haxorg_Time self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Time, haxorg_Time_vtable>(static_cast<bool(org::sem::Time::*)() const>(&org::sem::Time::isDynamic), self, org_context);
}
haxorg_TimeDynamic org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getDynamicConst_const(haxorg_Time self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Time, haxorg_Time_vtable>(static_cast<org::sem::Time::Dynamic const&(org::sem::Time::*)() const>(&org::sem::Time::getDynamic), self, org_context);
}
haxorg_TimeDynamic org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getDynamicMut(haxorg_Time self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Time, haxorg_Time_vtable>(static_cast<org::sem::Time::Dynamic&(org::sem::Time::*)()>(&org::sem::Time::getDynamic), self, org_context);
}
haxorg_TimeTimeKind org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getTimeKind_const(haxorg_Time self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Time, haxorg_Time_vtable>(static_cast<org::sem::Time::TimeKind(org::sem::Time::*)() const>(&org::sem::Time::getTimeKind), self, org_context);
}
bool org::bind::c::VTable<haxorg_TimeRepeat, haxorg_TimeRepeat_vtable>::__eq___const(haxorg_TimeRepeat self, OrgContext* org_context, haxorg_TimeRepeat other) {
  return org::bind::c::execute_cpp<haxorg_TimeRepeat, haxorg_TimeRepeat_vtable>(static_cast<bool(org::sem::Time::Repeat::*)(org::sem::Time::Repeat const&) const>(&org::sem::Time::Repeat::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_TimeStatic, haxorg_TimeStatic_vtable>::__eq___const(haxorg_TimeStatic self, OrgContext* org_context, haxorg_TimeStatic other) {
  return org::bind::c::execute_cpp<haxorg_TimeStatic, haxorg_TimeStatic_vtable>(static_cast<bool(org::sem::Time::Static::*)(org::sem::Time::Static const&) const>(&org::sem::Time::Static::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_TimeDynamic, haxorg_TimeDynamic_vtable>::__eq___const(haxorg_TimeDynamic self, OrgContext* org_context, haxorg_TimeDynamic other) {
  return org::bind::c::execute_cpp<haxorg_TimeDynamic, haxorg_TimeDynamic_vtable>(static_cast<bool(org::sem::Time::Dynamic::*)(org::sem::Time::Dynamic const&) const>(&org::sem::Time::Dynamic::operator==), self, org_context, other);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_TimeRange, haxorg_TimeRange_vtable>::getClockedTimeSeconds_const(haxorg_TimeRange self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_TimeRange, haxorg_TimeRange_vtable>(static_cast<hstd::Opt<int64_t>(org::sem::TimeRange::*)() const>(&org::sem::TimeRange::getClockedTimeSeconds), self, org_context);
}
void org::bind::c::VTable<haxorg_SubtreeLog, haxorg_SubtreeLog_vtable>::setDescription(haxorg_SubtreeLog self, OrgContext* org_context, haxorg_SemId desc) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLog, haxorg_SubtreeLog_vtable>(static_cast<void(org::sem::SubtreeLog::*)(org::sem::SemId<org::sem::StmtList>)>(&org::sem::SubtreeLog::setDescription), self, org_context, desc);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Subtree, haxorg_Subtree_vtable>::getTimePeriods_const(haxorg_Subtree self, OrgContext* org_context, haxorg_HstdIntSet kinds) {
  return org::bind::c::execute_cpp<haxorg_Subtree, haxorg_Subtree_vtable>(static_cast<hstd::Vec<org::sem::SubtreePeriod>(org::sem::Subtree::*)(hstd::IntSet<org::sem::SubtreePeriod::Kind>) const>(&org::sem::Subtree::getTimePeriods), self, org_context, kinds);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Subtree, haxorg_Subtree_vtable>::getProperties_const(haxorg_Subtree self, OrgContext* org_context, haxorg_HstdStr kind, haxorg_HstdOpt subkind) {
  return org::bind::c::execute_cpp<haxorg_Subtree, haxorg_Subtree_vtable>(static_cast<hstd::Vec<org::sem::NamedProperty>(org::sem::Subtree::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Subtree::getProperties), self, org_context, kind, subkind);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Subtree, haxorg_Subtree_vtable>::getProperty_const(haxorg_Subtree self, OrgContext* org_context, haxorg_HstdStr kind, haxorg_HstdOpt subkind) {
  return org::bind::c::execute_cpp<haxorg_Subtree, haxorg_Subtree_vtable>(static_cast<hstd::Opt<org::sem::NamedProperty>(org::sem::Subtree::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Subtree::getProperty), self, org_context, kind, subkind);
}
void org::bind::c::VTable<haxorg_Subtree, haxorg_Subtree_vtable>::removeProperty(haxorg_Subtree self, OrgContext* org_context, haxorg_HstdStr kind, haxorg_HstdOpt subkind) {
  return org::bind::c::execute_cpp<haxorg_Subtree, haxorg_Subtree_vtable>(static_cast<void(org::sem::Subtree::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&)>(&org::sem::Subtree::removeProperty), self, org_context, kind, subkind);
}
void org::bind::c::VTable<haxorg_Subtree, haxorg_Subtree_vtable>::setProperty(haxorg_Subtree self, OrgContext* org_context, haxorg_NamedProperty value) {
  return org::bind::c::execute_cpp<haxorg_Subtree, haxorg_Subtree_vtable>(static_cast<void(org::sem::Subtree::*)(org::sem::NamedProperty const&)>(&org::sem::Subtree::setProperty), self, org_context, value);
}
void org::bind::c::VTable<haxorg_Subtree, haxorg_Subtree_vtable>::setPropertyStrValue(haxorg_Subtree self, OrgContext* org_context, haxorg_HstdStr value, haxorg_HstdStr kind, haxorg_HstdOpt subkind) {
  return org::bind::c::execute_cpp<haxorg_Subtree, haxorg_Subtree_vtable>(static_cast<void(org::sem::Subtree::*)(hstd::Str const&, hstd::Str const&, hstd::Opt<hstd::Str> const&)>(&org::sem::Subtree::setPropertyStrValue), self, org_context, value, kind, subkind);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_Subtree, haxorg_Subtree_vtable>::getCleanTitle_const(haxorg_Subtree self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Subtree, haxorg_Subtree_vtable>(static_cast<hstd::Str(org::sem::Subtree::*)() const>(&org::sem::Subtree::getCleanTitle), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Subtree, haxorg_Subtree_vtable>::getTodoKeyword_const(haxorg_Subtree self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Subtree, haxorg_Subtree_vtable>(static_cast<hstd::Opt<hstd::Str>(org::sem::Subtree::*)() const>(&org::sem::Subtree::getTodoKeyword), self, org_context);
}
bool org::bind::c::VTable<haxorg_ListItem, haxorg_ListItem_vtable>::isDescriptionItem_const(haxorg_ListItem self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ListItem, haxorg_ListItem_vtable>(static_cast<bool(org::sem::ListItem::*)() const>(&org::sem::ListItem::isDescriptionItem), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ListItem, haxorg_ListItem_vtable>::getCleanHeader_const(haxorg_ListItem self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ListItem, haxorg_ListItem_vtable>(static_cast<hstd::Opt<hstd::Str>(org::sem::ListItem::*)() const>(&org::sem::ListItem::getCleanHeader), self, org_context);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_DocumentOptions, haxorg_DocumentOptions_vtable>::getProperties_const(haxorg_DocumentOptions self, OrgContext* org_context, haxorg_HstdStr kind, haxorg_HstdOpt subKind) {
  return org::bind::c::execute_cpp<haxorg_DocumentOptions, haxorg_DocumentOptions_vtable>(static_cast<hstd::Vec<org::sem::NamedProperty>(org::sem::DocumentOptions::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::DocumentOptions::getProperties), self, org_context, kind, subKind);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_DocumentOptions, haxorg_DocumentOptions_vtable>::getProperty_const(haxorg_DocumentOptions self, OrgContext* org_context, haxorg_HstdStr kind, haxorg_HstdOpt subKind) {
  return org::bind::c::execute_cpp<haxorg_DocumentOptions, haxorg_DocumentOptions_vtable>(static_cast<hstd::Opt<org::sem::NamedProperty>(org::sem::DocumentOptions::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::DocumentOptions::getProperty), self, org_context, kind, subKind);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Document, haxorg_Document_vtable>::getProperties_const(haxorg_Document self, OrgContext* org_context, haxorg_HstdStr kind, haxorg_HstdOpt subKind) {
  return org::bind::c::execute_cpp<haxorg_Document, haxorg_Document_vtable>(static_cast<hstd::Vec<org::sem::NamedProperty>(org::sem::Document::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Document::getProperties), self, org_context, kind, subKind);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Document, haxorg_Document_vtable>::getProperty_const(haxorg_Document self, OrgContext* org_context, haxorg_HstdStr kind, haxorg_HstdOpt subKind) {
  return org::bind::c::execute_cpp<haxorg_Document, haxorg_Document_vtable>(static_cast<hstd::Opt<org::sem::NamedProperty>(org::sem::Document::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Document::getProperty), self, org_context, kind, subKind);
}
bool org::bind::c::VTable<haxorg_File, haxorg_File_vtable>::isDocument_const(haxorg_File self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_File, haxorg_File_vtable>(static_cast<bool(org::sem::File::*)() const>(&org::sem::File::isDocument), self, org_context);
}
haxorg_FileDocument org::bind::c::VTable<haxorg_File, haxorg_File_vtable>::getDocumentConst_const(haxorg_File self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_File, haxorg_File_vtable>(static_cast<org::sem::File::Document const&(org::sem::File::*)() const>(&org::sem::File::getDocument), self, org_context);
}
haxorg_FileDocument org::bind::c::VTable<haxorg_File, haxorg_File_vtable>::getDocumentMut(haxorg_File self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_File, haxorg_File_vtable>(static_cast<org::sem::File::Document&(org::sem::File::*)()>(&org::sem::File::getDocument), self, org_context);
}
bool org::bind::c::VTable<haxorg_File, haxorg_File_vtable>::isAttachment_const(haxorg_File self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_File, haxorg_File_vtable>(static_cast<bool(org::sem::File::*)() const>(&org::sem::File::isAttachment), self, org_context);
}
haxorg_FileAttachment org::bind::c::VTable<haxorg_File, haxorg_File_vtable>::getAttachmentConst_const(haxorg_File self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_File, haxorg_File_vtable>(static_cast<org::sem::File::Attachment const&(org::sem::File::*)() const>(&org::sem::File::getAttachment), self, org_context);
}
haxorg_FileAttachment org::bind::c::VTable<haxorg_File, haxorg_File_vtable>::getAttachmentMut(haxorg_File self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_File, haxorg_File_vtable>(static_cast<org::sem::File::Attachment&(org::sem::File::*)()>(&org::sem::File::getAttachment), self, org_context);
}
bool org::bind::c::VTable<haxorg_File, haxorg_File_vtable>::isSource_const(haxorg_File self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_File, haxorg_File_vtable>(static_cast<bool(org::sem::File::*)() const>(&org::sem::File::isSource), self, org_context);
}
haxorg_FileSource org::bind::c::VTable<haxorg_File, haxorg_File_vtable>::getSourceConst_const(haxorg_File self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_File, haxorg_File_vtable>(static_cast<org::sem::File::Source const&(org::sem::File::*)() const>(&org::sem::File::getSource), self, org_context);
}
haxorg_FileSource org::bind::c::VTable<haxorg_File, haxorg_File_vtable>::getSourceMut(haxorg_File self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_File, haxorg_File_vtable>(static_cast<org::sem::File::Source&(org::sem::File::*)()>(&org::sem::File::getSource), self, org_context);
}
haxorg_FileKind org::bind::c::VTable<haxorg_File, haxorg_File_vtable>::getFileKind_const(haxorg_File self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_File, haxorg_File_vtable>(static_cast<org::sem::File::Kind(org::sem::File::*)() const>(&org::sem::File::getFileKind), self, org_context);
}
bool org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::isExample_const(haxorg_CmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<bool(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::isExample), self, org_context);
}
haxorg_CmdIncludeExample org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getExampleConst_const(haxorg_CmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<org::sem::CmdInclude::Example const&(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getExample), self, org_context);
}
haxorg_CmdIncludeExample org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getExampleMut(haxorg_CmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<org::sem::CmdInclude::Example&(org::sem::CmdInclude::*)()>(&org::sem::CmdInclude::getExample), self, org_context);
}
bool org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::isExport_const(haxorg_CmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<bool(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::isExport), self, org_context);
}
haxorg_CmdIncludeExport org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getExportConst_const(haxorg_CmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<org::sem::CmdInclude::Export const&(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getExport), self, org_context);
}
haxorg_CmdIncludeExport org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getExportMut(haxorg_CmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<org::sem::CmdInclude::Export&(org::sem::CmdInclude::*)()>(&org::sem::CmdInclude::getExport), self, org_context);
}
bool org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::isCustom_const(haxorg_CmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<bool(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::isCustom), self, org_context);
}
haxorg_CmdIncludeCustom org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getCustomConst_const(haxorg_CmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<org::sem::CmdInclude::Custom const&(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getCustom), self, org_context);
}
haxorg_CmdIncludeCustom org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getCustomMut(haxorg_CmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<org::sem::CmdInclude::Custom&(org::sem::CmdInclude::*)()>(&org::sem::CmdInclude::getCustom), self, org_context);
}
bool org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::isSrc_const(haxorg_CmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<bool(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::isSrc), self, org_context);
}
haxorg_CmdIncludeSrc org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getSrcConst_const(haxorg_CmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<org::sem::CmdInclude::Src const&(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getSrc), self, org_context);
}
haxorg_CmdIncludeSrc org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getSrcMut(haxorg_CmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<org::sem::CmdInclude::Src&(org::sem::CmdInclude::*)()>(&org::sem::CmdInclude::getSrc), self, org_context);
}
bool org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::isOrgDocument_const(haxorg_CmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<bool(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::isOrgDocument), self, org_context);
}
haxorg_CmdIncludeOrgDocument org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getOrgDocumentConst_const(haxorg_CmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<org::sem::CmdInclude::OrgDocument const&(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getOrgDocument), self, org_context);
}
haxorg_CmdIncludeOrgDocument org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getOrgDocumentMut(haxorg_CmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<org::sem::CmdInclude::OrgDocument&(org::sem::CmdInclude::*)()>(&org::sem::CmdInclude::getOrgDocument), self, org_context);
}
haxorg_CmdIncludeKind org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getIncludeKind_const(haxorg_CmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_CmdInclude, haxorg_CmdInclude_vtable>(static_cast<org::sem::CmdInclude::Kind(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getIncludeKind), self, org_context);
}
bool org::bind::c::VTable<haxorg_CmdIncludeIncludeBase, haxorg_CmdIncludeIncludeBase_vtable>::__eq___const(haxorg_CmdIncludeIncludeBase self, OrgContext* org_context, haxorg_CmdIncludeIncludeBase other) {
  return org::bind::c::execute_cpp<haxorg_CmdIncludeIncludeBase, haxorg_CmdIncludeIncludeBase_vtable>(static_cast<bool(org::sem::CmdInclude::IncludeBase::*)(org::sem::CmdInclude::IncludeBase const&) const>(&org::sem::CmdInclude::IncludeBase::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_CmdIncludeExample, haxorg_CmdIncludeExample_vtable>::__eq___const(haxorg_CmdIncludeExample self, OrgContext* org_context, haxorg_CmdIncludeExample other) {
  return org::bind::c::execute_cpp<haxorg_CmdIncludeExample, haxorg_CmdIncludeExample_vtable>(static_cast<bool(org::sem::CmdInclude::Example::*)(org::sem::CmdInclude::Example const&) const>(&org::sem::CmdInclude::Example::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_CmdIncludeExport, haxorg_CmdIncludeExport_vtable>::__eq___const(haxorg_CmdIncludeExport self, OrgContext* org_context, haxorg_CmdIncludeExport other) {
  return org::bind::c::execute_cpp<haxorg_CmdIncludeExport, haxorg_CmdIncludeExport_vtable>(static_cast<bool(org::sem::CmdInclude::Export::*)(org::sem::CmdInclude::Export const&) const>(&org::sem::CmdInclude::Export::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_CmdIncludeCustom, haxorg_CmdIncludeCustom_vtable>::__eq___const(haxorg_CmdIncludeCustom self, OrgContext* org_context, haxorg_CmdIncludeCustom other) {
  return org::bind::c::execute_cpp<haxorg_CmdIncludeCustom, haxorg_CmdIncludeCustom_vtable>(static_cast<bool(org::sem::CmdInclude::Custom::*)(org::sem::CmdInclude::Custom const&) const>(&org::sem::CmdInclude::Custom::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_CmdIncludeSrc, haxorg_CmdIncludeSrc_vtable>::__eq___const(haxorg_CmdIncludeSrc self, OrgContext* org_context, haxorg_CmdIncludeSrc other) {
  return org::bind::c::execute_cpp<haxorg_CmdIncludeSrc, haxorg_CmdIncludeSrc_vtable>(static_cast<bool(org::sem::CmdInclude::Src::*)(org::sem::CmdInclude::Src const&) const>(&org::sem::CmdInclude::Src::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_CmdIncludeOrgDocument, haxorg_CmdIncludeOrgDocument_vtable>::__eq___const(haxorg_CmdIncludeOrgDocument self, OrgContext* org_context, haxorg_CmdIncludeOrgDocument other) {
  return org::bind::c::execute_cpp<haxorg_CmdIncludeOrgDocument, haxorg_CmdIncludeOrgDocument_vtable>(static_cast<bool(org::sem::CmdInclude::OrgDocument::*)(org::sem::CmdInclude::OrgDocument const&) const>(&org::sem::CmdInclude::OrgDocument::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmNoNode, haxorg_ImmNoNode_vtable>::__eq___const(haxorg_ImmNoNode self, OrgContext* org_context, haxorg_ImmNoNode other) {
  return org::bind::c::execute_cpp<haxorg_ImmNoNode, haxorg_ImmNoNode_vtable>(static_cast<bool(org::imm::ImmNoNode::*)(org::imm::ImmNoNode const&) const>(&org::imm::ImmNoNode::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmErrorItem, haxorg_ImmErrorItem_vtable>::__eq___const(haxorg_ImmErrorItem self, OrgContext* org_context, haxorg_ImmErrorItem other) {
  return org::bind::c::execute_cpp<haxorg_ImmErrorItem, haxorg_ImmErrorItem_vtable>(static_cast<bool(org::imm::ImmErrorItem::*)(org::imm::ImmErrorItem const&) const>(&org::imm::ImmErrorItem::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmErrorGroup, haxorg_ImmErrorGroup_vtable>::__eq___const(haxorg_ImmErrorGroup self, OrgContext* org_context, haxorg_ImmErrorGroup other) {
  return org::bind::c::execute_cpp<haxorg_ImmErrorGroup, haxorg_ImmErrorGroup_vtable>(static_cast<bool(org::imm::ImmErrorGroup::*)(org::imm::ImmErrorGroup const&) const>(&org::imm::ImmErrorGroup::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmStmt, haxorg_ImmStmt_vtable>::__eq___const(haxorg_ImmStmt self, OrgContext* org_context, haxorg_ImmStmt other) {
  return org::bind::c::execute_cpp<haxorg_ImmStmt, haxorg_ImmStmt_vtable>(static_cast<bool(org::imm::ImmStmt::*)(org::imm::ImmStmt const&) const>(&org::imm::ImmStmt::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmInline, haxorg_ImmInline_vtable>::__eq___const(haxorg_ImmInline self, OrgContext* org_context, haxorg_ImmInline other) {
  return org::bind::c::execute_cpp<haxorg_ImmInline, haxorg_ImmInline_vtable>(static_cast<bool(org::imm::ImmInline::*)(org::imm::ImmInline const&) const>(&org::imm::ImmInline::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmStmtList, haxorg_ImmStmtList_vtable>::__eq___const(haxorg_ImmStmtList self, OrgContext* org_context, haxorg_ImmStmtList other) {
  return org::bind::c::execute_cpp<haxorg_ImmStmtList, haxorg_ImmStmtList_vtable>(static_cast<bool(org::imm::ImmStmtList::*)(org::imm::ImmStmtList const&) const>(&org::imm::ImmStmtList::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmEmpty, haxorg_ImmEmpty_vtable>::__eq___const(haxorg_ImmEmpty self, OrgContext* org_context, haxorg_ImmEmpty other) {
  return org::bind::c::execute_cpp<haxorg_ImmEmpty, haxorg_ImmEmpty_vtable>(static_cast<bool(org::imm::ImmEmpty::*)(org::imm::ImmEmpty const&) const>(&org::imm::ImmEmpty::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmLeaf, haxorg_ImmLeaf_vtable>::__eq___const(haxorg_ImmLeaf self, OrgContext* org_context, haxorg_ImmLeaf other) {
  return org::bind::c::execute_cpp<haxorg_ImmLeaf, haxorg_ImmLeaf_vtable>(static_cast<bool(org::imm::ImmLeaf::*)(org::imm::ImmLeaf const&) const>(&org::imm::ImmLeaf::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmTime, haxorg_ImmTime_vtable>::__eq___const(haxorg_ImmTime self, OrgContext* org_context, haxorg_ImmTime other) {
  return org::bind::c::execute_cpp<haxorg_ImmTime, haxorg_ImmTime_vtable>(static_cast<bool(org::imm::ImmTime::*)(org::imm::ImmTime const&) const>(&org::imm::ImmTime::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmTime, haxorg_ImmTime_vtable>::isStatic_const(haxorg_ImmTime self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmTime, haxorg_ImmTime_vtable>(static_cast<bool(org::imm::ImmTime::*)() const>(&org::imm::ImmTime::isStatic), self, org_context);
}
haxorg_ImmTimeStatic org::bind::c::VTable<haxorg_ImmTime, haxorg_ImmTime_vtable>::getStaticConst_const(haxorg_ImmTime self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmTime, haxorg_ImmTime_vtable>(static_cast<org::imm::ImmTime::Static const&(org::imm::ImmTime::*)() const>(&org::imm::ImmTime::getStatic), self, org_context);
}
haxorg_ImmTimeStatic org::bind::c::VTable<haxorg_ImmTime, haxorg_ImmTime_vtable>::getStaticMut(haxorg_ImmTime self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmTime, haxorg_ImmTime_vtable>(static_cast<org::imm::ImmTime::Static&(org::imm::ImmTime::*)()>(&org::imm::ImmTime::getStatic), self, org_context);
}
bool org::bind::c::VTable<haxorg_ImmTime, haxorg_ImmTime_vtable>::isDynamic_const(haxorg_ImmTime self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmTime, haxorg_ImmTime_vtable>(static_cast<bool(org::imm::ImmTime::*)() const>(&org::imm::ImmTime::isDynamic), self, org_context);
}
haxorg_ImmTimeDynamic org::bind::c::VTable<haxorg_ImmTime, haxorg_ImmTime_vtable>::getDynamicConst_const(haxorg_ImmTime self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmTime, haxorg_ImmTime_vtable>(static_cast<org::imm::ImmTime::Dynamic const&(org::imm::ImmTime::*)() const>(&org::imm::ImmTime::getDynamic), self, org_context);
}
haxorg_ImmTimeDynamic org::bind::c::VTable<haxorg_ImmTime, haxorg_ImmTime_vtable>::getDynamicMut(haxorg_ImmTime self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmTime, haxorg_ImmTime_vtable>(static_cast<org::imm::ImmTime::Dynamic&(org::imm::ImmTime::*)()>(&org::imm::ImmTime::getDynamic), self, org_context);
}
haxorg_ImmTimeTimeKind org::bind::c::VTable<haxorg_ImmTime, haxorg_ImmTime_vtable>::getTimeKind_const(haxorg_ImmTime self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmTime, haxorg_ImmTime_vtable>(static_cast<org::imm::ImmTime::TimeKind(org::imm::ImmTime::*)() const>(&org::imm::ImmTime::getTimeKind), self, org_context);
}
bool org::bind::c::VTable<haxorg_ImmTimeRepeat, haxorg_ImmTimeRepeat_vtable>::__eq___const(haxorg_ImmTimeRepeat self, OrgContext* org_context, haxorg_ImmTimeRepeat other) {
  return org::bind::c::execute_cpp<haxorg_ImmTimeRepeat, haxorg_ImmTimeRepeat_vtable>(static_cast<bool(org::imm::ImmTime::Repeat::*)(org::imm::ImmTime::Repeat const&) const>(&org::imm::ImmTime::Repeat::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmTimeStatic, haxorg_ImmTimeStatic_vtable>::__eq___const(haxorg_ImmTimeStatic self, OrgContext* org_context, haxorg_ImmTimeStatic other) {
  return org::bind::c::execute_cpp<haxorg_ImmTimeStatic, haxorg_ImmTimeStatic_vtable>(static_cast<bool(org::imm::ImmTime::Static::*)(org::imm::ImmTime::Static const&) const>(&org::imm::ImmTime::Static::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmTimeDynamic, haxorg_ImmTimeDynamic_vtable>::__eq___const(haxorg_ImmTimeDynamic self, OrgContext* org_context, haxorg_ImmTimeDynamic other) {
  return org::bind::c::execute_cpp<haxorg_ImmTimeDynamic, haxorg_ImmTimeDynamic_vtable>(static_cast<bool(org::imm::ImmTime::Dynamic::*)(org::imm::ImmTime::Dynamic const&) const>(&org::imm::ImmTime::Dynamic::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmTimeRange, haxorg_ImmTimeRange_vtable>::__eq___const(haxorg_ImmTimeRange self, OrgContext* org_context, haxorg_ImmTimeRange other) {
  return org::bind::c::execute_cpp<haxorg_ImmTimeRange, haxorg_ImmTimeRange_vtable>(static_cast<bool(org::imm::ImmTimeRange::*)(org::imm::ImmTimeRange const&) const>(&org::imm::ImmTimeRange::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmMacro, haxorg_ImmMacro_vtable>::__eq___const(haxorg_ImmMacro self, OrgContext* org_context, haxorg_ImmMacro other) {
  return org::bind::c::execute_cpp<haxorg_ImmMacro, haxorg_ImmMacro_vtable>(static_cast<bool(org::imm::ImmMacro::*)(org::imm::ImmMacro const&) const>(&org::imm::ImmMacro::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmSymbol, haxorg_ImmSymbol_vtable>::__eq___const(haxorg_ImmSymbol self, OrgContext* org_context, haxorg_ImmSymbol other) {
  return org::bind::c::execute_cpp<haxorg_ImmSymbol, haxorg_ImmSymbol_vtable>(static_cast<bool(org::imm::ImmSymbol::*)(org::imm::ImmSymbol const&) const>(&org::imm::ImmSymbol::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmSymbolParam, haxorg_ImmSymbolParam_vtable>::__eq___const(haxorg_ImmSymbolParam self, OrgContext* org_context, haxorg_ImmSymbolParam other) {
  return org::bind::c::execute_cpp<haxorg_ImmSymbolParam, haxorg_ImmSymbolParam_vtable>(static_cast<bool(org::imm::ImmSymbol::Param::*)(org::imm::ImmSymbol::Param const&) const>(&org::imm::ImmSymbol::Param::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmErrorSkipGroup, haxorg_ImmErrorSkipGroup_vtable>::__eq___const(haxorg_ImmErrorSkipGroup self, OrgContext* org_context, haxorg_ImmErrorSkipGroup other) {
  return org::bind::c::execute_cpp<haxorg_ImmErrorSkipGroup, haxorg_ImmErrorSkipGroup_vtable>(static_cast<bool(org::imm::ImmErrorSkipGroup::*)(org::imm::ImmErrorSkipGroup const&) const>(&org::imm::ImmErrorSkipGroup::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmMarkup, haxorg_ImmMarkup_vtable>::__eq___const(haxorg_ImmMarkup self, OrgContext* org_context, haxorg_ImmMarkup other) {
  return org::bind::c::execute_cpp<haxorg_ImmMarkup, haxorg_ImmMarkup_vtable>(static_cast<bool(org::imm::ImmMarkup::*)(org::imm::ImmMarkup const&) const>(&org::imm::ImmMarkup::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmRadioTarget, haxorg_ImmRadioTarget_vtable>::__eq___const(haxorg_ImmRadioTarget self, OrgContext* org_context, haxorg_ImmRadioTarget other) {
  return org::bind::c::execute_cpp<haxorg_ImmRadioTarget, haxorg_ImmRadioTarget_vtable>(static_cast<bool(org::imm::ImmRadioTarget::*)(org::imm::ImmRadioTarget const&) const>(&org::imm::ImmRadioTarget::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmLatex, haxorg_ImmLatex_vtable>::__eq___const(haxorg_ImmLatex self, OrgContext* org_context, haxorg_ImmLatex other) {
  return org::bind::c::execute_cpp<haxorg_ImmLatex, haxorg_ImmLatex_vtable>(static_cast<bool(org::imm::ImmLatex::*)(org::imm::ImmLatex const&) const>(&org::imm::ImmLatex::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmSubtreeLog, haxorg_ImmSubtreeLog_vtable>::__eq___const(haxorg_ImmSubtreeLog self, OrgContext* org_context, haxorg_ImmSubtreeLog other) {
  return org::bind::c::execute_cpp<haxorg_ImmSubtreeLog, haxorg_ImmSubtreeLog_vtable>(static_cast<bool(org::imm::ImmSubtreeLog::*)(org::imm::ImmSubtreeLog const&) const>(&org::imm::ImmSubtreeLog::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmSubtree, haxorg_ImmSubtree_vtable>::__eq___const(haxorg_ImmSubtree self, OrgContext* org_context, haxorg_ImmSubtree other) {
  return org::bind::c::execute_cpp<haxorg_ImmSubtree, haxorg_ImmSubtree_vtable>(static_cast<bool(org::imm::ImmSubtree::*)(org::imm::ImmSubtree const&) const>(&org::imm::ImmSubtree::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmColonExample, haxorg_ImmColonExample_vtable>::__eq___const(haxorg_ImmColonExample self, OrgContext* org_context, haxorg_ImmColonExample other) {
  return org::bind::c::execute_cpp<haxorg_ImmColonExample, haxorg_ImmColonExample_vtable>(static_cast<bool(org::imm::ImmColonExample::*)(org::imm::ImmColonExample const&) const>(&org::imm::ImmColonExample::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmCall, haxorg_ImmCall_vtable>::__eq___const(haxorg_ImmCall self, OrgContext* org_context, haxorg_ImmCall other) {
  return org::bind::c::execute_cpp<haxorg_ImmCall, haxorg_ImmCall_vtable>(static_cast<bool(org::imm::ImmCall::*)(org::imm::ImmCall const&) const>(&org::imm::ImmCall::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmListItem, haxorg_ImmListItem_vtable>::__eq___const(haxorg_ImmListItem self, OrgContext* org_context, haxorg_ImmListItem other) {
  return org::bind::c::execute_cpp<haxorg_ImmListItem, haxorg_ImmListItem_vtable>(static_cast<bool(org::imm::ImmListItem::*)(org::imm::ImmListItem const&) const>(&org::imm::ImmListItem::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmDocumentOptions, haxorg_ImmDocumentOptions_vtable>::__eq___const(haxorg_ImmDocumentOptions self, OrgContext* org_context, haxorg_ImmDocumentOptions other) {
  return org::bind::c::execute_cpp<haxorg_ImmDocumentOptions, haxorg_ImmDocumentOptions_vtable>(static_cast<bool(org::imm::ImmDocumentOptions::*)(org::imm::ImmDocumentOptions const&) const>(&org::imm::ImmDocumentOptions::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmDocumentFragment, haxorg_ImmDocumentFragment_vtable>::__eq___const(haxorg_ImmDocumentFragment self, OrgContext* org_context, haxorg_ImmDocumentFragment other) {
  return org::bind::c::execute_cpp<haxorg_ImmDocumentFragment, haxorg_ImmDocumentFragment_vtable>(static_cast<bool(org::imm::ImmDocumentFragment::*)(org::imm::ImmDocumentFragment const&) const>(&org::imm::ImmDocumentFragment::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmCriticMarkup, haxorg_ImmCriticMarkup_vtable>::__eq___const(haxorg_ImmCriticMarkup self, OrgContext* org_context, haxorg_ImmCriticMarkup other) {
  return org::bind::c::execute_cpp<haxorg_ImmCriticMarkup, haxorg_ImmCriticMarkup_vtable>(static_cast<bool(org::imm::ImmCriticMarkup::*)(org::imm::ImmCriticMarkup const&) const>(&org::imm::ImmCriticMarkup::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmDocument, haxorg_ImmDocument_vtable>::__eq___const(haxorg_ImmDocument self, OrgContext* org_context, haxorg_ImmDocument other) {
  return org::bind::c::execute_cpp<haxorg_ImmDocument, haxorg_ImmDocument_vtable>(static_cast<bool(org::imm::ImmDocument::*)(org::imm::ImmDocument const&) const>(&org::imm::ImmDocument::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmFileTarget, haxorg_ImmFileTarget_vtable>::__eq___const(haxorg_ImmFileTarget self, OrgContext* org_context, haxorg_ImmFileTarget other) {
  return org::bind::c::execute_cpp<haxorg_ImmFileTarget, haxorg_ImmFileTarget_vtable>(static_cast<bool(org::imm::ImmFileTarget::*)(org::imm::ImmFileTarget const&) const>(&org::imm::ImmFileTarget::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmTextSeparator, haxorg_ImmTextSeparator_vtable>::__eq___const(haxorg_ImmTextSeparator self, OrgContext* org_context, haxorg_ImmTextSeparator other) {
  return org::bind::c::execute_cpp<haxorg_ImmTextSeparator, haxorg_ImmTextSeparator_vtable>(static_cast<bool(org::imm::ImmTextSeparator::*)(org::imm::ImmTextSeparator const&) const>(&org::imm::ImmTextSeparator::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmDocumentGroup, haxorg_ImmDocumentGroup_vtable>::__eq___const(haxorg_ImmDocumentGroup self, OrgContext* org_context, haxorg_ImmDocumentGroup other) {
  return org::bind::c::execute_cpp<haxorg_ImmDocumentGroup, haxorg_ImmDocumentGroup_vtable>(static_cast<bool(org::imm::ImmDocumentGroup::*)(org::imm::ImmDocumentGroup const&) const>(&org::imm::ImmDocumentGroup::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::__eq___const(haxorg_ImmFile self, OrgContext* org_context, haxorg_ImmFile other) {
  return org::bind::c::execute_cpp<haxorg_ImmFile, haxorg_ImmFile_vtable>(static_cast<bool(org::imm::ImmFile::*)(org::imm::ImmFile const&) const>(&org::imm::ImmFile::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::isDocument_const(haxorg_ImmFile self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmFile, haxorg_ImmFile_vtable>(static_cast<bool(org::imm::ImmFile::*)() const>(&org::imm::ImmFile::isDocument), self, org_context);
}
haxorg_ImmFileDocument org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::getDocumentConst_const(haxorg_ImmFile self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmFile, haxorg_ImmFile_vtable>(static_cast<org::imm::ImmFile::Document const&(org::imm::ImmFile::*)() const>(&org::imm::ImmFile::getDocument), self, org_context);
}
haxorg_ImmFileDocument org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::getDocumentMut(haxorg_ImmFile self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmFile, haxorg_ImmFile_vtable>(static_cast<org::imm::ImmFile::Document&(org::imm::ImmFile::*)()>(&org::imm::ImmFile::getDocument), self, org_context);
}
bool org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::isAttachment_const(haxorg_ImmFile self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmFile, haxorg_ImmFile_vtable>(static_cast<bool(org::imm::ImmFile::*)() const>(&org::imm::ImmFile::isAttachment), self, org_context);
}
haxorg_ImmFileAttachment org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::getAttachmentConst_const(haxorg_ImmFile self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmFile, haxorg_ImmFile_vtable>(static_cast<org::imm::ImmFile::Attachment const&(org::imm::ImmFile::*)() const>(&org::imm::ImmFile::getAttachment), self, org_context);
}
haxorg_ImmFileAttachment org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::getAttachmentMut(haxorg_ImmFile self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmFile, haxorg_ImmFile_vtable>(static_cast<org::imm::ImmFile::Attachment&(org::imm::ImmFile::*)()>(&org::imm::ImmFile::getAttachment), self, org_context);
}
bool org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::isSource_const(haxorg_ImmFile self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmFile, haxorg_ImmFile_vtable>(static_cast<bool(org::imm::ImmFile::*)() const>(&org::imm::ImmFile::isSource), self, org_context);
}
haxorg_ImmFileSource org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::getSourceConst_const(haxorg_ImmFile self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmFile, haxorg_ImmFile_vtable>(static_cast<org::imm::ImmFile::Source const&(org::imm::ImmFile::*)() const>(&org::imm::ImmFile::getSource), self, org_context);
}
haxorg_ImmFileSource org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::getSourceMut(haxorg_ImmFile self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmFile, haxorg_ImmFile_vtable>(static_cast<org::imm::ImmFile::Source&(org::imm::ImmFile::*)()>(&org::imm::ImmFile::getSource), self, org_context);
}
haxorg_ImmFileKind org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::getFileKind_const(haxorg_ImmFile self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmFile, haxorg_ImmFile_vtable>(static_cast<org::imm::ImmFile::Kind(org::imm::ImmFile::*)() const>(&org::imm::ImmFile::getFileKind), self, org_context);
}
bool org::bind::c::VTable<haxorg_ImmFileDocument, haxorg_ImmFileDocument_vtable>::__eq___const(haxorg_ImmFileDocument self, OrgContext* org_context, haxorg_ImmFileDocument other) {
  return org::bind::c::execute_cpp<haxorg_ImmFileDocument, haxorg_ImmFileDocument_vtable>(static_cast<bool(org::imm::ImmFile::Document::*)(org::imm::ImmFile::Document const&) const>(&org::imm::ImmFile::Document::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmFileAttachment, haxorg_ImmFileAttachment_vtable>::__eq___const(haxorg_ImmFileAttachment self, OrgContext* org_context, haxorg_ImmFileAttachment other) {
  return org::bind::c::execute_cpp<haxorg_ImmFileAttachment, haxorg_ImmFileAttachment_vtable>(static_cast<bool(org::imm::ImmFile::Attachment::*)(org::imm::ImmFile::Attachment const&) const>(&org::imm::ImmFile::Attachment::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmFileSource, haxorg_ImmFileSource_vtable>::__eq___const(haxorg_ImmFileSource self, OrgContext* org_context, haxorg_ImmFileSource other) {
  return org::bind::c::execute_cpp<haxorg_ImmFileSource, haxorg_ImmFileSource_vtable>(static_cast<bool(org::imm::ImmFile::Source::*)(org::imm::ImmFile::Source const&) const>(&org::imm::ImmFile::Source::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmDirectory, haxorg_ImmDirectory_vtable>::__eq___const(haxorg_ImmDirectory self, OrgContext* org_context, haxorg_ImmDirectory other) {
  return org::bind::c::execute_cpp<haxorg_ImmDirectory, haxorg_ImmDirectory_vtable>(static_cast<bool(org::imm::ImmDirectory::*)(org::imm::ImmDirectory const&) const>(&org::imm::ImmDirectory::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmSymlink, haxorg_ImmSymlink_vtable>::__eq___const(haxorg_ImmSymlink self, OrgContext* org_context, haxorg_ImmSymlink other) {
  return org::bind::c::execute_cpp<haxorg_ImmSymlink, haxorg_ImmSymlink_vtable>(static_cast<bool(org::imm::ImmSymlink::*)(org::imm::ImmSymlink const&) const>(&org::imm::ImmSymlink::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::__eq___const(haxorg_ImmCmdInclude self, OrgContext* org_context, haxorg_ImmCmdInclude other) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<bool(org::imm::ImmCmdInclude::*)(org::imm::ImmCmdInclude const&) const>(&org::imm::ImmCmdInclude::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::isExample_const(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<bool(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::isExample), self, org_context);
}
haxorg_ImmCmdIncludeExample org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getExampleConst_const(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<org::imm::ImmCmdInclude::Example const&(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::getExample), self, org_context);
}
haxorg_ImmCmdIncludeExample org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getExampleMut(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<org::imm::ImmCmdInclude::Example&(org::imm::ImmCmdInclude::*)()>(&org::imm::ImmCmdInclude::getExample), self, org_context);
}
bool org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::isExport_const(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<bool(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::isExport), self, org_context);
}
haxorg_ImmCmdIncludeExport org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getExportConst_const(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<org::imm::ImmCmdInclude::Export const&(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::getExport), self, org_context);
}
haxorg_ImmCmdIncludeExport org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getExportMut(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<org::imm::ImmCmdInclude::Export&(org::imm::ImmCmdInclude::*)()>(&org::imm::ImmCmdInclude::getExport), self, org_context);
}
bool org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::isCustom_const(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<bool(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::isCustom), self, org_context);
}
haxorg_ImmCmdIncludeCustom org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getCustomConst_const(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<org::imm::ImmCmdInclude::Custom const&(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::getCustom), self, org_context);
}
haxorg_ImmCmdIncludeCustom org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getCustomMut(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<org::imm::ImmCmdInclude::Custom&(org::imm::ImmCmdInclude::*)()>(&org::imm::ImmCmdInclude::getCustom), self, org_context);
}
bool org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::isSrc_const(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<bool(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::isSrc), self, org_context);
}
haxorg_ImmCmdIncludeSrc org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getSrcConst_const(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<org::imm::ImmCmdInclude::Src const&(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::getSrc), self, org_context);
}
haxorg_ImmCmdIncludeSrc org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getSrcMut(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<org::imm::ImmCmdInclude::Src&(org::imm::ImmCmdInclude::*)()>(&org::imm::ImmCmdInclude::getSrc), self, org_context);
}
bool org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::isOrgDocument_const(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<bool(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::isOrgDocument), self, org_context);
}
haxorg_ImmCmdIncludeOrgDocument org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getOrgDocumentConst_const(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<org::imm::ImmCmdInclude::OrgDocument const&(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::getOrgDocument), self, org_context);
}
haxorg_ImmCmdIncludeOrgDocument org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getOrgDocumentMut(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<org::imm::ImmCmdInclude::OrgDocument&(org::imm::ImmCmdInclude::*)()>(&org::imm::ImmCmdInclude::getOrgDocument), self, org_context);
}
haxorg_ImmCmdIncludeKind org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getIncludeKind_const(haxorg_ImmCmdInclude self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>(static_cast<org::imm::ImmCmdInclude::Kind(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::getIncludeKind), self, org_context);
}
bool org::bind::c::VTable<haxorg_ImmCmdIncludeIncludeBase, haxorg_ImmCmdIncludeIncludeBase_vtable>::__eq___const(haxorg_ImmCmdIncludeIncludeBase self, OrgContext* org_context, haxorg_ImmCmdIncludeIncludeBase other) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeIncludeBase, haxorg_ImmCmdIncludeIncludeBase_vtable>(static_cast<bool(org::imm::ImmCmdInclude::IncludeBase::*)(org::imm::ImmCmdInclude::IncludeBase const&) const>(&org::imm::ImmCmdInclude::IncludeBase::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdIncludeExample, haxorg_ImmCmdIncludeExample_vtable>::__eq___const(haxorg_ImmCmdIncludeExample self, OrgContext* org_context, haxorg_ImmCmdIncludeExample other) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeExample, haxorg_ImmCmdIncludeExample_vtable>(static_cast<bool(org::imm::ImmCmdInclude::Example::*)(org::imm::ImmCmdInclude::Example const&) const>(&org::imm::ImmCmdInclude::Example::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdIncludeExport, haxorg_ImmCmdIncludeExport_vtable>::__eq___const(haxorg_ImmCmdIncludeExport self, OrgContext* org_context, haxorg_ImmCmdIncludeExport other) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeExport, haxorg_ImmCmdIncludeExport_vtable>(static_cast<bool(org::imm::ImmCmdInclude::Export::*)(org::imm::ImmCmdInclude::Export const&) const>(&org::imm::ImmCmdInclude::Export::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdIncludeCustom, haxorg_ImmCmdIncludeCustom_vtable>::__eq___const(haxorg_ImmCmdIncludeCustom self, OrgContext* org_context, haxorg_ImmCmdIncludeCustom other) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeCustom, haxorg_ImmCmdIncludeCustom_vtable>(static_cast<bool(org::imm::ImmCmdInclude::Custom::*)(org::imm::ImmCmdInclude::Custom const&) const>(&org::imm::ImmCmdInclude::Custom::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdIncludeSrc, haxorg_ImmCmdIncludeSrc_vtable>::__eq___const(haxorg_ImmCmdIncludeSrc self, OrgContext* org_context, haxorg_ImmCmdIncludeSrc other) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeSrc, haxorg_ImmCmdIncludeSrc_vtable>(static_cast<bool(org::imm::ImmCmdInclude::Src::*)(org::imm::ImmCmdInclude::Src const&) const>(&org::imm::ImmCmdInclude::Src::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdIncludeOrgDocument, haxorg_ImmCmdIncludeOrgDocument_vtable>::__eq___const(haxorg_ImmCmdIncludeOrgDocument self, OrgContext* org_context, haxorg_ImmCmdIncludeOrgDocument other) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeOrgDocument, haxorg_ImmCmdIncludeOrgDocument_vtable>(static_cast<bool(org::imm::ImmCmdInclude::OrgDocument::*)(org::imm::ImmCmdInclude::OrgDocument const&) const>(&org::imm::ImmCmdInclude::OrgDocument::operator==), self, org_context, other);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Cmd, haxorg_Cmd_vtable>::getAttrs_const(haxorg_Cmd self, OrgContext* org_context, haxorg_HstdOpt key) {
  return org::bind::c::execute_cpp<haxorg_Cmd, haxorg_Cmd_vtable>(static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Cmd::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Cmd::getAttrs), self, org_context, key);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Cmd, haxorg_Cmd_vtable>::getFirstAttr_const(haxorg_Cmd self, OrgContext* org_context, haxorg_HstdStr kind) {
  return org::bind::c::execute_cpp<haxorg_Cmd, haxorg_Cmd_vtable>(static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Cmd::*)(hstd::Str const&) const>(&org::sem::Cmd::getFirstAttr), self, org_context, kind);
}
bool org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::isFootnoteDefinition_const(haxorg_Paragraph self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Paragraph, haxorg_Paragraph_vtable>(static_cast<bool(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::isFootnoteDefinition), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::getFootnoteName_const(haxorg_Paragraph self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Paragraph, haxorg_Paragraph_vtable>(static_cast<hstd::Opt<hstd::Str>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getFootnoteName), self, org_context);
}
bool org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::hasAdmonition_const(haxorg_Paragraph self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Paragraph, haxorg_Paragraph_vtable>(static_cast<bool(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::hasAdmonition), self, org_context);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::getAdmonitions_const(haxorg_Paragraph self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Paragraph, haxorg_Paragraph_vtable>(static_cast<hstd::Vec<hstd::Str>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getAdmonitions), self, org_context);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::getAdmonitionNodes_const(haxorg_Paragraph self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Paragraph, haxorg_Paragraph_vtable>(static_cast<hstd::Vec<org::sem::SemId<org::sem::BigIdent>>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getAdmonitionNodes), self, org_context);
}
bool org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::hasTimestamp_const(haxorg_Paragraph self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Paragraph, haxorg_Paragraph_vtable>(static_cast<bool(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::hasTimestamp), self, org_context);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::getTimestamps_const(haxorg_Paragraph self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Paragraph, haxorg_Paragraph_vtable>(static_cast<hstd::Vec<hstd::UserTime>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getTimestamps), self, org_context);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::getTimestampNodes_const(haxorg_Paragraph self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Paragraph, haxorg_Paragraph_vtable>(static_cast<hstd::Vec<org::sem::SemId<org::sem::Time>>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getTimestampNodes), self, org_context);
}
bool org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::hasLeadHashtags_const(haxorg_Paragraph self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Paragraph, haxorg_Paragraph_vtable>(static_cast<bool(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::hasLeadHashtags), self, org_context);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::getLeadHashtags_const(haxorg_Paragraph self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Paragraph, haxorg_Paragraph_vtable>(static_cast<hstd::Vec<org::sem::SemId<org::sem::HashTag>>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getLeadHashtags), self, org_context);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::getBody_const(haxorg_Paragraph self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_Paragraph, haxorg_Paragraph_vtable>(static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getBody), self, org_context);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_List, haxorg_List_vtable>::getListAttrs_const(haxorg_List self, OrgContext* org_context, haxorg_HstdStr key) {
  return org::bind::c::execute_cpp<haxorg_List, haxorg_List_vtable>(static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::List::*)(hstd::Str const&) const>(&org::sem::List::getListAttrs), self, org_context, key);
}
haxorg_ListFormattingMode org::bind::c::VTable<haxorg_List, haxorg_List_vtable>::getListFormattingMode_const(haxorg_List self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_List, haxorg_List_vtable>(static_cast<ListFormattingMode(org::sem::List::*)() const>(&org::sem::List::getListFormattingMode), self, org_context);
}
bool org::bind::c::VTable<haxorg_List, haxorg_List_vtable>::isDescriptionList_const(haxorg_List self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_List, haxorg_List_vtable>(static_cast<bool(org::sem::List::*)() const>(&org::sem::List::isDescriptionList), self, org_context);
}
bool org::bind::c::VTable<haxorg_List, haxorg_List_vtable>::isNumberedList_const(haxorg_List self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_List, haxorg_List_vtable>(static_cast<bool(org::sem::List::*)() const>(&org::sem::List::isNumberedList), self, org_context);
}
bool org::bind::c::VTable<haxorg_ImmCmd, haxorg_ImmCmd_vtable>::__eq___const(haxorg_ImmCmd self, OrgContext* org_context, haxorg_ImmCmd other) {
  return org::bind::c::execute_cpp<haxorg_ImmCmd, haxorg_ImmCmd_vtable>(static_cast<bool(org::imm::ImmCmd::*)(org::imm::ImmCmd const&) const>(&org::imm::ImmCmd::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdCustomRaw, haxorg_ImmCmdCustomRaw_vtable>::__eq___const(haxorg_ImmCmdCustomRaw self, OrgContext* org_context, haxorg_ImmCmdCustomRaw other) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdCustomRaw, haxorg_ImmCmdCustomRaw_vtable>(static_cast<bool(org::imm::ImmCmdCustomRaw::*)(org::imm::ImmCmdCustomRaw const&) const>(&org::imm::ImmCmdCustomRaw::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdCustomText, haxorg_ImmCmdCustomText_vtable>::__eq___const(haxorg_ImmCmdCustomText self, OrgContext* org_context, haxorg_ImmCmdCustomText other) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdCustomText, haxorg_ImmCmdCustomText_vtable>(static_cast<bool(org::imm::ImmCmdCustomText::*)(org::imm::ImmCmdCustomText const&) const>(&org::imm::ImmCmdCustomText::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmLink, haxorg_ImmLink_vtable>::__eq___const(haxorg_ImmLink self, OrgContext* org_context, haxorg_ImmLink other) {
  return org::bind::c::execute_cpp<haxorg_ImmLink, haxorg_ImmLink_vtable>(static_cast<bool(org::imm::ImmLink::*)(org::imm::ImmLink const&) const>(&org::imm::ImmLink::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmBlockComment, haxorg_ImmBlockComment_vtable>::__eq___const(haxorg_ImmBlockComment self, OrgContext* org_context, haxorg_ImmBlockComment other) {
  return org::bind::c::execute_cpp<haxorg_ImmBlockComment, haxorg_ImmBlockComment_vtable>(static_cast<bool(org::imm::ImmBlockComment::*)(org::imm::ImmBlockComment const&) const>(&org::imm::ImmBlockComment::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmParagraph, haxorg_ImmParagraph_vtable>::__eq___const(haxorg_ImmParagraph self, OrgContext* org_context, haxorg_ImmParagraph other) {
  return org::bind::c::execute_cpp<haxorg_ImmParagraph, haxorg_ImmParagraph_vtable>(static_cast<bool(org::imm::ImmParagraph::*)(org::imm::ImmParagraph const&) const>(&org::imm::ImmParagraph::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmList, haxorg_ImmList_vtable>::__eq___const(haxorg_ImmList self, OrgContext* org_context, haxorg_ImmList other) {
  return org::bind::c::execute_cpp<haxorg_ImmList, haxorg_ImmList_vtable>(static_cast<bool(org::imm::ImmList::*)(org::imm::ImmList const&) const>(&org::imm::ImmList::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmHashTag, haxorg_ImmHashTag_vtable>::__eq___const(haxorg_ImmHashTag self, OrgContext* org_context, haxorg_ImmHashTag other) {
  return org::bind::c::execute_cpp<haxorg_ImmHashTag, haxorg_ImmHashTag_vtable>(static_cast<bool(org::imm::ImmHashTag::*)(org::imm::ImmHashTag const&) const>(&org::imm::ImmHashTag::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmInlineFootnote, haxorg_ImmInlineFootnote_vtable>::__eq___const(haxorg_ImmInlineFootnote self, OrgContext* org_context, haxorg_ImmInlineFootnote other) {
  return org::bind::c::execute_cpp<haxorg_ImmInlineFootnote, haxorg_ImmInlineFootnote_vtable>(static_cast<bool(org::imm::ImmInlineFootnote::*)(org::imm::ImmInlineFootnote const&) const>(&org::imm::ImmInlineFootnote::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmInlineExport, haxorg_ImmInlineExport_vtable>::__eq___const(haxorg_ImmInlineExport self, OrgContext* org_context, haxorg_ImmInlineExport other) {
  return org::bind::c::execute_cpp<haxorg_ImmInlineExport, haxorg_ImmInlineExport_vtable>(static_cast<bool(org::imm::ImmInlineExport::*)(org::imm::ImmInlineExport const&) const>(&org::imm::ImmInlineExport::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmEscaped, haxorg_ImmEscaped_vtable>::__eq___const(haxorg_ImmEscaped self, OrgContext* org_context, haxorg_ImmEscaped other) {
  return org::bind::c::execute_cpp<haxorg_ImmEscaped, haxorg_ImmEscaped_vtable>(static_cast<bool(org::imm::ImmEscaped::*)(org::imm::ImmEscaped const&) const>(&org::imm::ImmEscaped::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmNewline, haxorg_ImmNewline_vtable>::__eq___const(haxorg_ImmNewline self, OrgContext* org_context, haxorg_ImmNewline other) {
  return org::bind::c::execute_cpp<haxorg_ImmNewline, haxorg_ImmNewline_vtable>(static_cast<bool(org::imm::ImmNewline::*)(org::imm::ImmNewline const&) const>(&org::imm::ImmNewline::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmSpace, haxorg_ImmSpace_vtable>::__eq___const(haxorg_ImmSpace self, OrgContext* org_context, haxorg_ImmSpace other) {
  return org::bind::c::execute_cpp<haxorg_ImmSpace, haxorg_ImmSpace_vtable>(static_cast<bool(org::imm::ImmSpace::*)(org::imm::ImmSpace const&) const>(&org::imm::ImmSpace::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmWord, haxorg_ImmWord_vtable>::__eq___const(haxorg_ImmWord self, OrgContext* org_context, haxorg_ImmWord other) {
  return org::bind::c::execute_cpp<haxorg_ImmWord, haxorg_ImmWord_vtable>(static_cast<bool(org::imm::ImmWord::*)(org::imm::ImmWord const&) const>(&org::imm::ImmWord::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmAtMention, haxorg_ImmAtMention_vtable>::__eq___const(haxorg_ImmAtMention self, OrgContext* org_context, haxorg_ImmAtMention other) {
  return org::bind::c::execute_cpp<haxorg_ImmAtMention, haxorg_ImmAtMention_vtable>(static_cast<bool(org::imm::ImmAtMention::*)(org::imm::ImmAtMention const&) const>(&org::imm::ImmAtMention::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmRawText, haxorg_ImmRawText_vtable>::__eq___const(haxorg_ImmRawText self, OrgContext* org_context, haxorg_ImmRawText other) {
  return org::bind::c::execute_cpp<haxorg_ImmRawText, haxorg_ImmRawText_vtable>(static_cast<bool(org::imm::ImmRawText::*)(org::imm::ImmRawText const&) const>(&org::imm::ImmRawText::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmPunctuation, haxorg_ImmPunctuation_vtable>::__eq___const(haxorg_ImmPunctuation self, OrgContext* org_context, haxorg_ImmPunctuation other) {
  return org::bind::c::execute_cpp<haxorg_ImmPunctuation, haxorg_ImmPunctuation_vtable>(static_cast<bool(org::imm::ImmPunctuation::*)(org::imm::ImmPunctuation const&) const>(&org::imm::ImmPunctuation::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmPlaceholder, haxorg_ImmPlaceholder_vtable>::__eq___const(haxorg_ImmPlaceholder self, OrgContext* org_context, haxorg_ImmPlaceholder other) {
  return org::bind::c::execute_cpp<haxorg_ImmPlaceholder, haxorg_ImmPlaceholder_vtable>(static_cast<bool(org::imm::ImmPlaceholder::*)(org::imm::ImmPlaceholder const&) const>(&org::imm::ImmPlaceholder::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmBigIdent, haxorg_ImmBigIdent_vtable>::__eq___const(haxorg_ImmBigIdent self, OrgContext* org_context, haxorg_ImmBigIdent other) {
  return org::bind::c::execute_cpp<haxorg_ImmBigIdent, haxorg_ImmBigIdent_vtable>(static_cast<bool(org::imm::ImmBigIdent::*)(org::imm::ImmBigIdent const&) const>(&org::imm::ImmBigIdent::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmTextTarget, haxorg_ImmTextTarget_vtable>::__eq___const(haxorg_ImmTextTarget self, OrgContext* org_context, haxorg_ImmTextTarget other) {
  return org::bind::c::execute_cpp<haxorg_ImmTextTarget, haxorg_ImmTextTarget_vtable>(static_cast<bool(org::imm::ImmTextTarget::*)(org::imm::ImmTextTarget const&) const>(&org::imm::ImmTextTarget::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmErrorSkipToken, haxorg_ImmErrorSkipToken_vtable>::__eq___const(haxorg_ImmErrorSkipToken self, OrgContext* org_context, haxorg_ImmErrorSkipToken other) {
  return org::bind::c::execute_cpp<haxorg_ImmErrorSkipToken, haxorg_ImmErrorSkipToken_vtable>(static_cast<bool(org::imm::ImmErrorSkipToken::*)(org::imm::ImmErrorSkipToken const&) const>(&org::imm::ImmErrorSkipToken::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmBold, haxorg_ImmBold_vtable>::__eq___const(haxorg_ImmBold self, OrgContext* org_context, haxorg_ImmBold other) {
  return org::bind::c::execute_cpp<haxorg_ImmBold, haxorg_ImmBold_vtable>(static_cast<bool(org::imm::ImmBold::*)(org::imm::ImmBold const&) const>(&org::imm::ImmBold::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmUnderline, haxorg_ImmUnderline_vtable>::__eq___const(haxorg_ImmUnderline self, OrgContext* org_context, haxorg_ImmUnderline other) {
  return org::bind::c::execute_cpp<haxorg_ImmUnderline, haxorg_ImmUnderline_vtable>(static_cast<bool(org::imm::ImmUnderline::*)(org::imm::ImmUnderline const&) const>(&org::imm::ImmUnderline::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmMonospace, haxorg_ImmMonospace_vtable>::__eq___const(haxorg_ImmMonospace self, OrgContext* org_context, haxorg_ImmMonospace other) {
  return org::bind::c::execute_cpp<haxorg_ImmMonospace, haxorg_ImmMonospace_vtable>(static_cast<bool(org::imm::ImmMonospace::*)(org::imm::ImmMonospace const&) const>(&org::imm::ImmMonospace::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmMarkQuote, haxorg_ImmMarkQuote_vtable>::__eq___const(haxorg_ImmMarkQuote self, OrgContext* org_context, haxorg_ImmMarkQuote other) {
  return org::bind::c::execute_cpp<haxorg_ImmMarkQuote, haxorg_ImmMarkQuote_vtable>(static_cast<bool(org::imm::ImmMarkQuote::*)(org::imm::ImmMarkQuote const&) const>(&org::imm::ImmMarkQuote::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmVerbatim, haxorg_ImmVerbatim_vtable>::__eq___const(haxorg_ImmVerbatim self, OrgContext* org_context, haxorg_ImmVerbatim other) {
  return org::bind::c::execute_cpp<haxorg_ImmVerbatim, haxorg_ImmVerbatim_vtable>(static_cast<bool(org::imm::ImmVerbatim::*)(org::imm::ImmVerbatim const&) const>(&org::imm::ImmVerbatim::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmItalic, haxorg_ImmItalic_vtable>::__eq___const(haxorg_ImmItalic self, OrgContext* org_context, haxorg_ImmItalic other) {
  return org::bind::c::execute_cpp<haxorg_ImmItalic, haxorg_ImmItalic_vtable>(static_cast<bool(org::imm::ImmItalic::*)(org::imm::ImmItalic const&) const>(&org::imm::ImmItalic::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmStrike, haxorg_ImmStrike_vtable>::__eq___const(haxorg_ImmStrike self, OrgContext* org_context, haxorg_ImmStrike other) {
  return org::bind::c::execute_cpp<haxorg_ImmStrike, haxorg_ImmStrike_vtable>(static_cast<bool(org::imm::ImmStrike::*)(org::imm::ImmStrike const&) const>(&org::imm::ImmStrike::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmPar, haxorg_ImmPar_vtable>::__eq___const(haxorg_ImmPar self, OrgContext* org_context, haxorg_ImmPar other) {
  return org::bind::c::execute_cpp<haxorg_ImmPar, haxorg_ImmPar_vtable>(static_cast<bool(org::imm::ImmPar::*)(org::imm::ImmPar const&) const>(&org::imm::ImmPar::operator==), self, org_context, other);
}
haxorg_StdOptional org::bind::c::VTable<haxorg_ImmAdapterDirectoryAPI, haxorg_ImmAdapterDirectoryAPI_vtable>::getFsSubnode_const(haxorg_ImmAdapterDirectoryAPI self, OrgContext* org_context, haxorg_HstdStr name, bool withPath) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapterDirectoryAPI, haxorg_ImmAdapterDirectoryAPI_vtable>(static_cast<std::optional<org::imm::ImmAdapter>(org::imm::ImmAdapterDirectoryAPI::*)(hstd::Str const&, bool) const>(&org::imm::ImmAdapterDirectoryAPI::getFsSubnode), self, org_context, name, withPath);
}
bool org::bind::c::VTable<haxorg_ImmBlock, haxorg_ImmBlock_vtable>::__eq___const(haxorg_ImmBlock self, OrgContext* org_context, haxorg_ImmBlock other) {
  return org::bind::c::execute_cpp<haxorg_ImmBlock, haxorg_ImmBlock_vtable>(static_cast<bool(org::imm::ImmBlock::*)(org::imm::ImmBlock const&) const>(&org::imm::ImmBlock::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmLineCommand, haxorg_ImmLineCommand_vtable>::__eq___const(haxorg_ImmLineCommand self, OrgContext* org_context, haxorg_ImmLineCommand other) {
  return org::bind::c::execute_cpp<haxorg_ImmLineCommand, haxorg_ImmLineCommand_vtable>(static_cast<bool(org::imm::ImmLineCommand::*)(org::imm::ImmLineCommand const&) const>(&org::imm::ImmLineCommand::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdCreator, haxorg_ImmCmdCreator_vtable>::__eq___const(haxorg_ImmCmdCreator self, OrgContext* org_context, haxorg_ImmCmdCreator other) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdCreator, haxorg_ImmCmdCreator_vtable>(static_cast<bool(org::imm::ImmCmdCreator::*)(org::imm::ImmCmdCreator const&) const>(&org::imm::ImmCmdCreator::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdAuthor, haxorg_ImmCmdAuthor_vtable>::__eq___const(haxorg_ImmCmdAuthor self, OrgContext* org_context, haxorg_ImmCmdAuthor other) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdAuthor, haxorg_ImmCmdAuthor_vtable>(static_cast<bool(org::imm::ImmCmdAuthor::*)(org::imm::ImmCmdAuthor const&) const>(&org::imm::ImmCmdAuthor::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdEmail, haxorg_ImmCmdEmail_vtable>::__eq___const(haxorg_ImmCmdEmail self, OrgContext* org_context, haxorg_ImmCmdEmail other) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdEmail, haxorg_ImmCmdEmail_vtable>(static_cast<bool(org::imm::ImmCmdEmail::*)(org::imm::ImmCmdEmail const&) const>(&org::imm::ImmCmdEmail::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdLanguage, haxorg_ImmCmdLanguage_vtable>::__eq___const(haxorg_ImmCmdLanguage self, OrgContext* org_context, haxorg_ImmCmdLanguage other) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdLanguage, haxorg_ImmCmdLanguage_vtable>(static_cast<bool(org::imm::ImmCmdLanguage::*)(org::imm::ImmCmdLanguage const&) const>(&org::imm::ImmCmdLanguage::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdCustomArgs, haxorg_ImmCmdCustomArgs_vtable>::__eq___const(haxorg_ImmCmdCustomArgs self, OrgContext* org_context, haxorg_ImmCmdCustomArgs other) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdCustomArgs, haxorg_ImmCmdCustomArgs_vtable>(static_cast<bool(org::imm::ImmCmdCustomArgs::*)(org::imm::ImmCmdCustomArgs const&) const>(&org::imm::ImmCmdCustomArgs::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdTblfm, haxorg_ImmCmdTblfm_vtable>::__eq___const(haxorg_ImmCmdTblfm self, OrgContext* org_context, haxorg_ImmCmdTblfm other) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdTblfm, haxorg_ImmCmdTblfm_vtable>(static_cast<bool(org::imm::ImmCmdTblfm::*)(org::imm::ImmCmdTblfm const&) const>(&org::imm::ImmCmdTblfm::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmCell, haxorg_ImmCell_vtable>::__eq___const(haxorg_ImmCell self, OrgContext* org_context, haxorg_ImmCell other) {
  return org::bind::c::execute_cpp<haxorg_ImmCell, haxorg_ImmCell_vtable>(static_cast<bool(org::imm::ImmCell::*)(org::imm::ImmCell const&) const>(&org::imm::ImmCell::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmRow, haxorg_ImmRow_vtable>::__eq___const(haxorg_ImmRow self, OrgContext* org_context, haxorg_ImmRow other) {
  return org::bind::c::execute_cpp<haxorg_ImmRow, haxorg_ImmRow_vtable>(static_cast<bool(org::imm::ImmRow::*)(org::imm::ImmRow const&) const>(&org::imm::ImmRow::operator==), self, org_context, other);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmStmtAdapter, haxorg_ImmStmtAdapter_vtable>::getAttached_const(haxorg_ImmStmtAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmStmtAdapter, haxorg_ImmStmtAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg>>(org::imm::ImmAdapterT<org::imm::ImmStmt>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmStmt>::getAttached), self, org_context);
}
int org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getLevel_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>(static_cast<int(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getLevel), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getTreeId_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getTreeId), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getTodo_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getTodo), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getCompletion_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>(static_cast<hstd::Opt<org::sem::SubtreeCompletion> const&(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getCompletion), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getDescription_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getDescription), self, org_context);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getTags_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag>>(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getTags), self, org_context);
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getTitle_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getTitle), self, org_context);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getLogbook_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmSubtreeLog>>(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getLogbook), self, org_context);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getProperties_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::sem::NamedProperty>(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getProperties), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getClosed_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime>>(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getClosed), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getDeadline_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime>>(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getDeadline), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getScheduled_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime>>(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getScheduled), self, org_context);
}
bool org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getIsComment_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getIsComment), self, org_context);
}
bool org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getIsArchived_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getIsArchived), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getPriority_const(haxorg_ImmSubtreeAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getPriority), self, org_context);
}
haxorg_OrgDiagnostics org::bind::c::VTable<haxorg_ImmErrorItemAdapter, haxorg_ImmErrorItemAdapter_vtable>::getDiag_const(haxorg_ImmErrorItemAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmErrorItemAdapter, haxorg_ImmErrorItemAdapter_vtable>(static_cast<org::sem::OrgDiagnostics(org::imm::ImmAdapterT<org::imm::ImmErrorItem>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmErrorItem>::getDiag), self, org_context);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmErrorGroupAdapter, haxorg_ImmErrorGroupAdapter_vtable>::getDiagnostics_const(haxorg_ImmErrorGroupAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmErrorGroupAdapter, haxorg_ImmErrorGroupAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorItem>>(org::imm::ImmAdapterT<org::imm::ImmErrorGroup>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmErrorGroup>::getDiagnostics), self, org_context);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmErrorSkipGroupAdapter, haxorg_ImmErrorSkipGroupAdapter_vtable>::getSkipped_const(haxorg_ImmErrorSkipGroupAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmErrorSkipGroupAdapter, haxorg_ImmErrorSkipGroupAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorSkipToken>>(org::imm::ImmAdapterT<org::imm::ImmErrorSkipGroup>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmErrorSkipGroup>::getSkipped), self, org_context);
}
bool org::bind::c::VTable<haxorg_ImmTimeAdapter, haxorg_ImmTimeAdapter_vtable>::getIsActive_const(haxorg_ImmTimeAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmTimeAdapter, haxorg_ImmTimeAdapter_vtable>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmTime>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTime>::getIsActive), self, org_context);
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmTimeRangeAdapter, haxorg_ImmTimeRangeAdapter_vtable>::getFrom_const(haxorg_ImmTimeRangeAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmTimeRangeAdapter, haxorg_ImmTimeRangeAdapter_vtable>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmTimeRange>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTimeRange>::getFrom), self, org_context);
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmTimeRangeAdapter, haxorg_ImmTimeRangeAdapter_vtable>::getTo_const(haxorg_ImmTimeRangeAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmTimeRangeAdapter, haxorg_ImmTimeRangeAdapter_vtable>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmTimeRange>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTimeRange>::getTo), self, org_context);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmMacroAdapter, haxorg_ImmMacroAdapter_vtable>::getName_const(haxorg_ImmMacroAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmMacroAdapter, haxorg_ImmMacroAdapter_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmMacro>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmMacro>::getName), self, org_context);
}
haxorg_AttrGroup org::bind::c::VTable<haxorg_ImmMacroAdapter, haxorg_ImmMacroAdapter_vtable>::getAttrs_const(haxorg_ImmMacroAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmMacroAdapter, haxorg_ImmMacroAdapter_vtable>(static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmMacro>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmMacro>::getAttrs), self, org_context);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmSymbolAdapter, haxorg_ImmSymbolAdapter_vtable>::getName_const(haxorg_ImmSymbolAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmSymbolAdapter, haxorg_ImmSymbolAdapter_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmSymbol>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymbol>::getName), self, org_context);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmSymbolAdapter, haxorg_ImmSymbolAdapter_vtable>::getParameters_const(haxorg_ImmSymbolAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmSymbolAdapter, haxorg_ImmSymbolAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmSymbol::Param>(org::imm::ImmAdapterT<org::imm::ImmSymbol>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymbol>::getParameters), self, org_context);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmSymbolAdapter, haxorg_ImmSymbolAdapter_vtable>::getPositional_const(haxorg_ImmSymbolAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmSymbolAdapter, haxorg_ImmSymbolAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg>>(org::imm::ImmAdapterT<org::imm::ImmSymbol>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymbol>::getPositional), self, org_context);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmLeafAdapter, haxorg_ImmLeafAdapter_vtable>::getText_const(haxorg_ImmLeafAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmLeafAdapter, haxorg_ImmLeafAdapter_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmLeaf>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmLeaf>::getText), self, org_context);
}
haxorg_SubtreeLogHead org::bind::c::VTable<haxorg_ImmSubtreeLogAdapter, haxorg_ImmSubtreeLogAdapter_vtable>::getHead_const(haxorg_ImmSubtreeLogAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmSubtreeLogAdapter, haxorg_ImmSubtreeLogAdapter_vtable>(static_cast<org::sem::SubtreeLogHead(org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>::getHead), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmSubtreeLogAdapter, haxorg_ImmSubtreeLogAdapter_vtable>::getDesc_const(haxorg_ImmSubtreeLogAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmSubtreeLogAdapter, haxorg_ImmSubtreeLogAdapter_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmStmtList>>(org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>::getDesc), self, org_context);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCallAdapter, haxorg_ImmCallAdapter_vtable>::getName_const(haxorg_ImmCallAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCallAdapter, haxorg_ImmCallAdapter_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCall>::getName), self, org_context);
}
haxorg_AttrGroup org::bind::c::VTable<haxorg_ImmCallAdapter, haxorg_ImmCallAdapter_vtable>::getAttrs_const(haxorg_ImmCallAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCallAdapter, haxorg_ImmCallAdapter_vtable>(static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCall>::getAttrs), self, org_context);
}
bool org::bind::c::VTable<haxorg_ImmCallAdapter, haxorg_ImmCallAdapter_vtable>::getIsCommand_const(haxorg_ImmCallAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCallAdapter, haxorg_ImmCallAdapter_vtable>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCall>::getIsCommand), self, org_context);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmFileAdapter, haxorg_ImmFileAdapter_vtable>::getRelPath_const(haxorg_ImmFileAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmFileAdapter, haxorg_ImmFileAdapter_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmFile>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFile>::getRelPath), self, org_context);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmFileAdapter, haxorg_ImmFileAdapter_vtable>::getAbsPath_const(haxorg_ImmFileAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmFileAdapter, haxorg_ImmFileAdapter_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmFile>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFile>::getAbsPath), self, org_context);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmDirectoryAdapter, haxorg_ImmDirectoryAdapter_vtable>::getRelPath_const(haxorg_ImmDirectoryAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmDirectoryAdapter, haxorg_ImmDirectoryAdapter_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmDirectory>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDirectory>::getRelPath), self, org_context);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmDirectoryAdapter, haxorg_ImmDirectoryAdapter_vtable>::getAbsPath_const(haxorg_ImmDirectoryAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmDirectoryAdapter, haxorg_ImmDirectoryAdapter_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmDirectory>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDirectory>::getAbsPath), self, org_context);
}
bool org::bind::c::VTable<haxorg_ImmSymlinkAdapter, haxorg_ImmSymlinkAdapter_vtable>::getIsDirectory_const(haxorg_ImmSymlinkAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmSymlinkAdapter, haxorg_ImmSymlinkAdapter_vtable>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmSymlink>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymlink>::getIsDirectory), self, org_context);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmSymlinkAdapter, haxorg_ImmSymlinkAdapter_vtable>::getAbsPath_const(haxorg_ImmSymlinkAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmSymlinkAdapter, haxorg_ImmSymlinkAdapter_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmSymlink>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymlink>::getAbsPath), self, org_context);
}
int org::bind::c::VTable<haxorg_ImmDocumentFragmentAdapter, haxorg_ImmDocumentFragmentAdapter_vtable>::getBaseLine_const(haxorg_ImmDocumentFragmentAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmDocumentFragmentAdapter, haxorg_ImmDocumentFragmentAdapter_vtable>(static_cast<int(org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>::getBaseLine), self, org_context);
}
int org::bind::c::VTable<haxorg_ImmDocumentFragmentAdapter, haxorg_ImmDocumentFragmentAdapter_vtable>::getBaseCol_const(haxorg_ImmDocumentFragmentAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmDocumentFragmentAdapter, haxorg_ImmDocumentFragmentAdapter_vtable>(static_cast<int(org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>::getBaseCol), self, org_context);
}
haxorg_ImmCriticMarkupKind org::bind::c::VTable<haxorg_ImmCriticMarkupAdapter, haxorg_ImmCriticMarkupAdapter_vtable>::getKind_const(haxorg_ImmCriticMarkupAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCriticMarkupAdapter, haxorg_ImmCriticMarkupAdapter_vtable>(static_cast<org::imm::ImmCriticMarkup::Kind(org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>::getKind), self, org_context);
}
haxorg_CheckboxState org::bind::c::VTable<haxorg_ImmListItemAdapter, haxorg_ImmListItemAdapter_vtable>::getCheckbox_const(haxorg_ImmListItemAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmListItemAdapter, haxorg_ImmListItemAdapter_vtable>(static_cast<CheckboxState(org::imm::ImmAdapterT<org::imm::ImmListItem>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmListItem>::getCheckbox), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmListItemAdapter, haxorg_ImmListItemAdapter_vtable>::getHeader_const(haxorg_ImmListItemAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmListItemAdapter, haxorg_ImmListItemAdapter_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(org::imm::ImmAdapterT<org::imm::ImmListItem>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmListItem>::getHeader), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmListItemAdapter, haxorg_ImmListItemAdapter_vtable>::getBullet_const(haxorg_ImmListItemAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmListItemAdapter, haxorg_ImmListItemAdapter_vtable>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmListItem>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmListItem>::getBullet), self, org_context);
}
haxorg_InitialSubtreeVisibility org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getInitialVisibility_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>(static_cast<InitialSubtreeVisibility(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getInitialVisibility), self, org_context);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getProperties_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::sem::NamedProperty>(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getProperties), self, org_context);
}
haxorg_DocumentExportConfig org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getExportConfig_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>(static_cast<org::sem::DocumentExportConfig(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getExportConfig), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getFixedWidthSections_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>(static_cast<hstd::Opt<bool> const&(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getFixedWidthSections), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getStartupIndented_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>(static_cast<hstd::Opt<bool> const&(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getStartupIndented), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getCategory_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getCategory), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getSetupfile_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getSetupfile), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getMaxSubtreeLevelExport_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>(static_cast<hstd::Opt<int> const&(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getMaxSubtreeLevelExport), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getColumns_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>(static_cast<hstd::Opt<org::sem::ColumnView> const&(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getColumns), self, org_context);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getTodoKeywords_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::sem::TodoKeyword>(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getTodoKeywords), self, org_context);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getDoneKeywords_const(haxorg_ImmDocumentOptionsAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::sem::TodoKeyword>(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getDoneKeywords), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>::getTitle_const(haxorg_ImmDocumentAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getTitle), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>::getAuthor_const(haxorg_ImmDocumentAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getAuthor), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>::getCreator_const(haxorg_ImmDocumentAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getCreator), self, org_context);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>::getFiletags_const(haxorg_ImmDocumentAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag>>(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getFiletags), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>::getEmail_const(haxorg_ImmDocumentAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmRawText>>(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getEmail), self, org_context);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>::getLanguage_const(haxorg_ImmDocumentAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>(static_cast<hstd::ext::ImmVec<hstd::Str>(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getLanguage), self, org_context);
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>::getOptions_const(haxorg_ImmDocumentAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getOptions), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>::getExportFileName_const(haxorg_ImmDocumentAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getExportFileName), self, org_context);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable>::getPath_const(haxorg_ImmFileTargetAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getPath), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable>::getLine_const(haxorg_ImmFileTargetAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable>(static_cast<hstd::Opt<int> const&(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getLine), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable>::getSearchTarget_const(haxorg_ImmFileTargetAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getSearchTarget), self, org_context);
}
bool org::bind::c::VTable<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable>::getRestrictToHeadlines_const(haxorg_ImmFileTargetAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getRestrictToHeadlines), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable>::getTargetId_const(haxorg_ImmFileTargetAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getTargetId), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable>::getRegexp_const(haxorg_ImmFileTargetAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getRegexp), self, org_context);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdIncludeAdapter, haxorg_ImmCmdIncludeAdapter_vtable>::getPath_const(haxorg_ImmCmdIncludeAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeAdapter, haxorg_ImmCmdIncludeAdapter_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::getPath), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmCmdIncludeAdapter, haxorg_ImmCmdIncludeAdapter_vtable>::getFirstLine_const(haxorg_ImmCmdIncludeAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeAdapter, haxorg_ImmCmdIncludeAdapter_vtable>(static_cast<hstd::Opt<int> const&(org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::getFirstLine), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmCmdIncludeAdapter, haxorg_ImmCmdIncludeAdapter_vtable>::getLastLine_const(haxorg_ImmCmdIncludeAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeAdapter, haxorg_ImmCmdIncludeAdapter_vtable>(static_cast<hstd::Opt<int> const&(org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::getLastLine), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_BlockExport, haxorg_BlockExport_vtable>::getPlacement_const(haxorg_BlockExport self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_BlockExport, haxorg_BlockExport_vtable>(static_cast<hstd::Opt<hstd::Str>(org::sem::BlockExport::*)() const>(&org::sem::BlockExport::getPlacement), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_BlockCode, haxorg_BlockCode_vtable>::getVariable_const(haxorg_BlockCode self, OrgContext* org_context, haxorg_HstdStr varname) {
  return org::bind::c::execute_cpp<haxorg_BlockCode, haxorg_BlockCode_vtable>(static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::BlockCode::*)(hstd::Str const&) const>(&org::sem::BlockCode::getVariable), self, org_context, varname);
}
bool org::bind::c::VTable<haxorg_ImmBlockCenter, haxorg_ImmBlockCenter_vtable>::__eq___const(haxorg_ImmBlockCenter self, OrgContext* org_context, haxorg_ImmBlockCenter other) {
  return org::bind::c::execute_cpp<haxorg_ImmBlockCenter, haxorg_ImmBlockCenter_vtable>(static_cast<bool(org::imm::ImmBlockCenter::*)(org::imm::ImmBlockCenter const&) const>(&org::imm::ImmBlockCenter::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmBlockQuote, haxorg_ImmBlockQuote_vtable>::__eq___const(haxorg_ImmBlockQuote self, OrgContext* org_context, haxorg_ImmBlockQuote other) {
  return org::bind::c::execute_cpp<haxorg_ImmBlockQuote, haxorg_ImmBlockQuote_vtable>(static_cast<bool(org::imm::ImmBlockQuote::*)(org::imm::ImmBlockQuote const&) const>(&org::imm::ImmBlockQuote::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmBlockVerse, haxorg_ImmBlockVerse_vtable>::__eq___const(haxorg_ImmBlockVerse self, OrgContext* org_context, haxorg_ImmBlockVerse other) {
  return org::bind::c::execute_cpp<haxorg_ImmBlockVerse, haxorg_ImmBlockVerse_vtable>(static_cast<bool(org::imm::ImmBlockVerse::*)(org::imm::ImmBlockVerse const&) const>(&org::imm::ImmBlockVerse::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmBlockDynamicFallback, haxorg_ImmBlockDynamicFallback_vtable>::__eq___const(haxorg_ImmBlockDynamicFallback self, OrgContext* org_context, haxorg_ImmBlockDynamicFallback other) {
  return org::bind::c::execute_cpp<haxorg_ImmBlockDynamicFallback, haxorg_ImmBlockDynamicFallback_vtable>(static_cast<bool(org::imm::ImmBlockDynamicFallback::*)(org::imm::ImmBlockDynamicFallback const&) const>(&org::imm::ImmBlockDynamicFallback::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmBlockExample, haxorg_ImmBlockExample_vtable>::__eq___const(haxorg_ImmBlockExample self, OrgContext* org_context, haxorg_ImmBlockExample other) {
  return org::bind::c::execute_cpp<haxorg_ImmBlockExample, haxorg_ImmBlockExample_vtable>(static_cast<bool(org::imm::ImmBlockExample::*)(org::imm::ImmBlockExample const&) const>(&org::imm::ImmBlockExample::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmBlockExport, haxorg_ImmBlockExport_vtable>::__eq___const(haxorg_ImmBlockExport self, OrgContext* org_context, haxorg_ImmBlockExport other) {
  return org::bind::c::execute_cpp<haxorg_ImmBlockExport, haxorg_ImmBlockExport_vtable>(static_cast<bool(org::imm::ImmBlockExport::*)(org::imm::ImmBlockExport const&) const>(&org::imm::ImmBlockExport::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmBlockAdmonition, haxorg_ImmBlockAdmonition_vtable>::__eq___const(haxorg_ImmBlockAdmonition self, OrgContext* org_context, haxorg_ImmBlockAdmonition other) {
  return org::bind::c::execute_cpp<haxorg_ImmBlockAdmonition, haxorg_ImmBlockAdmonition_vtable>(static_cast<bool(org::imm::ImmBlockAdmonition::*)(org::imm::ImmBlockAdmonition const&) const>(&org::imm::ImmBlockAdmonition::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmBlockCodeEvalResult, haxorg_ImmBlockCodeEvalResult_vtable>::__eq___const(haxorg_ImmBlockCodeEvalResult self, OrgContext* org_context, haxorg_ImmBlockCodeEvalResult other) {
  return org::bind::c::execute_cpp<haxorg_ImmBlockCodeEvalResult, haxorg_ImmBlockCodeEvalResult_vtable>(static_cast<bool(org::imm::ImmBlockCodeEvalResult::*)(org::imm::ImmBlockCodeEvalResult const&) const>(&org::imm::ImmBlockCodeEvalResult::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmBlockCode, haxorg_ImmBlockCode_vtable>::__eq___const(haxorg_ImmBlockCode self, OrgContext* org_context, haxorg_ImmBlockCode other) {
  return org::bind::c::execute_cpp<haxorg_ImmBlockCode, haxorg_ImmBlockCode_vtable>(static_cast<bool(org::imm::ImmBlockCode::*)(org::imm::ImmBlockCode const&) const>(&org::imm::ImmBlockCode::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmTable, haxorg_ImmTable_vtable>::__eq___const(haxorg_ImmTable self, OrgContext* org_context, haxorg_ImmTable other) {
  return org::bind::c::execute_cpp<haxorg_ImmTable, haxorg_ImmTable_vtable>(static_cast<bool(org::imm::ImmTable::*)(org::imm::ImmTable const&) const>(&org::imm::ImmTable::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmAttached, haxorg_ImmAttached_vtable>::__eq___const(haxorg_ImmAttached self, OrgContext* org_context, haxorg_ImmAttached other) {
  return org::bind::c::execute_cpp<haxorg_ImmAttached, haxorg_ImmAttached_vtable>(static_cast<bool(org::imm::ImmAttached::*)(org::imm::ImmAttached const&) const>(&org::imm::ImmAttached::operator==), self, org_context, other);
}
haxorg_AttrGroup org::bind::c::VTable<haxorg_ImmCmdAdapter, haxorg_ImmCmdAdapter_vtable>::getAttrs_const(haxorg_ImmCmdAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdAdapter, haxorg_ImmCmdAdapter_vtable>(static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmCmd>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmd>::getAttrs), self, org_context);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdCustomRawAdapter, haxorg_ImmCmdCustomRawAdapter_vtable>::getName_const(haxorg_ImmCmdCustomRawAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdCustomRawAdapter, haxorg_ImmCmdCustomRawAdapter_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::getName), self, org_context);
}
bool org::bind::c::VTable<haxorg_ImmCmdCustomRawAdapter, haxorg_ImmCmdCustomRawAdapter_vtable>::getIsAttached_const(haxorg_ImmCmdCustomRawAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdCustomRawAdapter, haxorg_ImmCmdCustomRawAdapter_vtable>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::getIsAttached), self, org_context);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdCustomRawAdapter, haxorg_ImmCmdCustomRawAdapter_vtable>::getText_const(haxorg_ImmCmdCustomRawAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdCustomRawAdapter, haxorg_ImmCmdCustomRawAdapter_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::getText), self, org_context);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdCustomTextAdapter, haxorg_ImmCmdCustomTextAdapter_vtable>::getName_const(haxorg_ImmCmdCustomTextAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdCustomTextAdapter, haxorg_ImmCmdCustomTextAdapter_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::getName), self, org_context);
}
bool org::bind::c::VTable<haxorg_ImmCmdCustomTextAdapter, haxorg_ImmCmdCustomTextAdapter_vtable>::getIsAttached_const(haxorg_ImmCmdCustomTextAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdCustomTextAdapter, haxorg_ImmCmdCustomTextAdapter_vtable>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::getIsAttached), self, org_context);
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmCmdCustomTextAdapter, haxorg_ImmCmdCustomTextAdapter_vtable>::getText_const(haxorg_ImmCmdCustomTextAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdCustomTextAdapter, haxorg_ImmCmdCustomTextAdapter_vtable>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::getText), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmLinkAdapter, haxorg_ImmLinkAdapter_vtable>::getDescription_const(haxorg_ImmLinkAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmLinkAdapter, haxorg_ImmLinkAdapter_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(org::imm::ImmAdapterT<org::imm::ImmLink>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmLink>::getDescription), self, org_context);
}
haxorg_LinkTarget org::bind::c::VTable<haxorg_ImmLinkAdapter, haxorg_ImmLinkAdapter_vtable>::getTarget_const(haxorg_ImmLinkAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmLinkAdapter, haxorg_ImmLinkAdapter_vtable>(static_cast<org::sem::LinkTarget(org::imm::ImmAdapterT<org::imm::ImmLink>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmLink>::getTarget), self, org_context);
}
haxorg_HashTagText org::bind::c::VTable<haxorg_ImmHashTagAdapter, haxorg_ImmHashTagAdapter_vtable>::getText_const(haxorg_ImmHashTagAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmHashTagAdapter, haxorg_ImmHashTagAdapter_vtable>(static_cast<org::sem::HashTagText(org::imm::ImmAdapterT<org::imm::ImmHashTag>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmHashTag>::getText), self, org_context);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmInlineFootnoteAdapter, haxorg_ImmInlineFootnoteAdapter_vtable>::getTag_const(haxorg_ImmInlineFootnoteAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmInlineFootnoteAdapter, haxorg_ImmInlineFootnoteAdapter_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>::getTag), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmInlineFootnoteAdapter, haxorg_ImmInlineFootnoteAdapter_vtable>::getDefinition_const(haxorg_ImmInlineFootnoteAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmInlineFootnoteAdapter, haxorg_ImmInlineFootnoteAdapter_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapter>(org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>::getDefinition), self, org_context);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmRadioTargetAdapter, haxorg_ImmRadioTargetAdapter_vtable>::getWords_const(haxorg_ImmRadioTargetAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmRadioTargetAdapter, haxorg_ImmRadioTargetAdapter_vtable>(static_cast<hstd::ext::ImmVec<hstd::Str>(org::imm::ImmAdapterT<org::imm::ImmRadioTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmRadioTarget>::getWords), self, org_context);
}
bool org::bind::c::VTable<haxorg_ImmCmdCaption, haxorg_ImmCmdCaption_vtable>::__eq___const(haxorg_ImmCmdCaption self, OrgContext* org_context, haxorg_ImmCmdCaption other) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdCaption, haxorg_ImmCmdCaption_vtable>(static_cast<bool(org::imm::ImmCmdCaption::*)(org::imm::ImmCmdCaption const&) const>(&org::imm::ImmCmdCaption::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdColumns, haxorg_ImmCmdColumns_vtable>::__eq___const(haxorg_ImmCmdColumns self, OrgContext* org_context, haxorg_ImmCmdColumns other) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdColumns, haxorg_ImmCmdColumns_vtable>(static_cast<bool(org::imm::ImmCmdColumns::*)(org::imm::ImmCmdColumns const&) const>(&org::imm::ImmCmdColumns::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdName, haxorg_ImmCmdName_vtable>::__eq___const(haxorg_ImmCmdName self, OrgContext* org_context, haxorg_ImmCmdName other) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdName, haxorg_ImmCmdName_vtable>(static_cast<bool(org::imm::ImmCmdName::*)(org::imm::ImmCmdName const&) const>(&org::imm::ImmCmdName::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdCall, haxorg_ImmCmdCall_vtable>::__eq___const(haxorg_ImmCmdCall self, OrgContext* org_context, haxorg_ImmCmdCall other) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdCall, haxorg_ImmCmdCall_vtable>(static_cast<bool(org::imm::ImmCmdCall::*)(org::imm::ImmCmdCall const&) const>(&org::imm::ImmCmdCall::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdAttr, haxorg_ImmCmdAttr_vtable>::__eq___const(haxorg_ImmCmdAttr self, OrgContext* org_context, haxorg_ImmCmdAttr other) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdAttr, haxorg_ImmCmdAttr_vtable>(static_cast<bool(org::imm::ImmCmdAttr::*)(org::imm::ImmCmdAttr const&) const>(&org::imm::ImmCmdAttr::operator==), self, org_context, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdExport, haxorg_ImmCmdExport_vtable>::__eq___const(haxorg_ImmCmdExport self, OrgContext* org_context, haxorg_ImmCmdExport other) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdExport, haxorg_ImmCmdExport_vtable>(static_cast<bool(org::imm::ImmCmdExport::*)(org::imm::ImmCmdExport const&) const>(&org::imm::ImmCmdExport::operator==), self, org_context, other);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdCustomArgsAdapter, haxorg_ImmCmdCustomArgsAdapter_vtable>::getName_const(haxorg_ImmCmdCustomArgsAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdCustomArgsAdapter, haxorg_ImmCmdCustomArgsAdapter_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>::getName), self, org_context);
}
bool org::bind::c::VTable<haxorg_ImmCmdCustomArgsAdapter, haxorg_ImmCmdCustomArgsAdapter_vtable>::getIsAttached_const(haxorg_ImmCmdCustomArgsAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdCustomArgsAdapter, haxorg_ImmCmdCustomArgsAdapter_vtable>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>::getIsAttached), self, org_context);
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmCmdCreatorAdapter, haxorg_ImmCmdCreatorAdapter_vtable>::getText_const(haxorg_ImmCmdCreatorAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdCreatorAdapter, haxorg_ImmCmdCreatorAdapter_vtable>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmCmdCreator>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCreator>::getText), self, org_context);
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmCmdAuthorAdapter, haxorg_ImmCmdAuthorAdapter_vtable>::getText_const(haxorg_ImmCmdAuthorAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdAuthorAdapter, haxorg_ImmCmdAuthorAdapter_vtable>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmCmdAuthor>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdAuthor>::getText), self, org_context);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdEmailAdapter, haxorg_ImmCmdEmailAdapter_vtable>::getText_const(haxorg_ImmCmdEmailAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdEmailAdapter, haxorg_ImmCmdEmailAdapter_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdEmail>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdEmail>::getText), self, org_context);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdLanguageAdapter, haxorg_ImmCmdLanguageAdapter_vtable>::getText_const(haxorg_ImmCmdLanguageAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdLanguageAdapter, haxorg_ImmCmdLanguageAdapter_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdLanguage>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdLanguage>::getText), self, org_context);
}
haxorg_Tblfm org::bind::c::VTable<haxorg_ImmCmdTblfmAdapter, haxorg_ImmCmdTblfmAdapter_vtable>::getExpr_const(haxorg_ImmCmdTblfmAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdTblfmAdapter, haxorg_ImmCmdTblfmAdapter_vtable>(static_cast<org::sem::Tblfm(org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>::getExpr), self, org_context);
}
bool org::bind::c::VTable<haxorg_ImmCellAdapter, haxorg_ImmCellAdapter_vtable>::getIsBlock_const(haxorg_ImmCellAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCellAdapter, haxorg_ImmCellAdapter_vtable>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmCell>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCell>::getIsBlock), self, org_context);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmRowAdapter, haxorg_ImmRowAdapter_vtable>::getCells_const(haxorg_ImmRowAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmRowAdapter, haxorg_ImmRowAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmCell>>(org::imm::ImmAdapterT<org::imm::ImmRow>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmRow>::getCells), self, org_context);
}
bool org::bind::c::VTable<haxorg_ImmRowAdapter, haxorg_ImmRowAdapter_vtable>::getIsBlock_const(haxorg_ImmRowAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmRowAdapter, haxorg_ImmRowAdapter_vtable>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmRow>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmRow>::getIsBlock), self, org_context);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmInlineExportAdapter, haxorg_ImmInlineExportAdapter_vtable>::getExporter_const(haxorg_ImmInlineExportAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmInlineExportAdapter, haxorg_ImmInlineExportAdapter_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmInlineExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmInlineExport>::getExporter), self, org_context);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmInlineExportAdapter, haxorg_ImmInlineExportAdapter_vtable>::getContent_const(haxorg_ImmInlineExportAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmInlineExportAdapter, haxorg_ImmInlineExportAdapter_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmInlineExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmInlineExport>::getContent), self, org_context);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdExportAdapter, haxorg_ImmCmdExportAdapter_vtable>::getExporter_const(haxorg_ImmCmdExportAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdExportAdapter, haxorg_ImmCmdExportAdapter_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdExport>::getExporter), self, org_context);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdExportAdapter, haxorg_ImmCmdExportAdapter_vtable>::getContent_const(haxorg_ImmCmdExportAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdExportAdapter, haxorg_ImmCmdExportAdapter_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdExport>::getContent), self, org_context);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmBlockExportAdapter, haxorg_ImmBlockExportAdapter_vtable>::getExporter_const(haxorg_ImmBlockExportAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmBlockExportAdapter, haxorg_ImmBlockExportAdapter_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmBlockExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockExport>::getExporter), self, org_context);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmBlockExportAdapter, haxorg_ImmBlockExportAdapter_vtable>::getContent_const(haxorg_ImmBlockExportAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmBlockExportAdapter, haxorg_ImmBlockExportAdapter_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmBlockExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockExport>::getContent), self, org_context);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmBlockDynamicFallbackAdapter, haxorg_ImmBlockDynamicFallbackAdapter_vtable>::getName_const(haxorg_ImmBlockDynamicFallbackAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmBlockDynamicFallbackAdapter, haxorg_ImmBlockDynamicFallbackAdapter_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>::getName), self, org_context);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmBlockCodeEvalResultAdapter, haxorg_ImmBlockCodeEvalResultAdapter_vtable>::getRaw_const(haxorg_ImmBlockCodeEvalResultAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmBlockCodeEvalResultAdapter, haxorg_ImmBlockCodeEvalResultAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::sem::OrgCodeEvalOutput>(org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>::getRaw), self, org_context);
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmBlockCodeEvalResultAdapter, haxorg_ImmBlockCodeEvalResultAdapter_vtable>::getNode_const(haxorg_ImmBlockCodeEvalResultAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmBlockCodeEvalResultAdapter, haxorg_ImmBlockCodeEvalResultAdapter_vtable>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>::getNode), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmBlockCodeAdapter, haxorg_ImmBlockCodeAdapter_vtable>::getLang_const(haxorg_ImmBlockCodeAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmBlockCodeAdapter, haxorg_ImmBlockCodeAdapter_vtable>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmBlockCode>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCode>::getLang), self, org_context);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmBlockCodeAdapter, haxorg_ImmBlockCodeAdapter_vtable>::getResult_const(haxorg_ImmBlockCodeAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmBlockCodeAdapter, haxorg_ImmBlockCodeAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>>(org::imm::ImmAdapterT<org::imm::ImmBlockCode>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCode>::getResult), self, org_context);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmBlockCodeAdapter, haxorg_ImmBlockCodeAdapter_vtable>::getLines_const(haxorg_ImmBlockCodeAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmBlockCodeAdapter, haxorg_ImmBlockCodeAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::sem::BlockCodeLine>(org::imm::ImmAdapterT<org::imm::ImmBlockCode>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCode>::getLines), self, org_context);
}
haxorg_AttrGroup org::bind::c::VTable<haxorg_ImmBlockCodeAdapter, haxorg_ImmBlockCodeAdapter_vtable>::getSwitches_const(haxorg_ImmBlockCodeAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmBlockCodeAdapter, haxorg_ImmBlockCodeAdapter_vtable>(static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmBlockCode>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCode>::getSwitches), self, org_context);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmTableAdapter, haxorg_ImmTableAdapter_vtable>::getRows_const(haxorg_ImmTableAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmTableAdapter, haxorg_ImmTableAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmRow>>(org::imm::ImmAdapterT<org::imm::ImmTable>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTable>::getRows), self, org_context);
}
bool org::bind::c::VTable<haxorg_ImmTableAdapter, haxorg_ImmTableAdapter_vtable>::getIsBlock_const(haxorg_ImmTableAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmTableAdapter, haxorg_ImmTableAdapter_vtable>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmTable>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTable>::getIsBlock), self, org_context);
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmCmdCaptionAdapter, haxorg_ImmCmdCaptionAdapter_vtable>::getText_const(haxorg_ImmCmdCaptionAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdCaptionAdapter, haxorg_ImmCmdCaptionAdapter_vtable>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmCmdCaption>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCaption>::getText), self, org_context);
}
haxorg_ColumnView org::bind::c::VTable<haxorg_ImmCmdColumnsAdapter, haxorg_ImmCmdColumnsAdapter_vtable>::getView_const(haxorg_ImmCmdColumnsAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdColumnsAdapter, haxorg_ImmCmdColumnsAdapter_vtable>(static_cast<org::sem::ColumnView(org::imm::ImmAdapterT<org::imm::ImmCmdColumns>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdColumns>::getView), self, org_context);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdNameAdapter, haxorg_ImmCmdNameAdapter_vtable>::getName_const(haxorg_ImmCmdNameAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdNameAdapter, haxorg_ImmCmdNameAdapter_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdName>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdName>::getName), self, org_context);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable>::getName_const(haxorg_ImmCmdCallAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getName), self, org_context);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable>::getFileName_const(haxorg_ImmCmdCallAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getFileName), self, org_context);
}
haxorg_AttrGroup org::bind::c::VTable<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable>::getInsideHeaderAttrs_const(haxorg_ImmCmdCallAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable>(static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getInsideHeaderAttrs), self, org_context);
}
haxorg_AttrGroup org::bind::c::VTable<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable>::getCallAttrs_const(haxorg_ImmCmdCallAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable>(static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getCallAttrs), self, org_context);
}
haxorg_AttrGroup org::bind::c::VTable<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable>::getEndHeaderAttrs_const(haxorg_ImmCmdCallAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable>(static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getEndHeaderAttrs), self, org_context);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable>::getResult_const(haxorg_ImmCmdCallAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>>(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getResult), self, org_context);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdAttrAdapter, haxorg_ImmCmdAttrAdapter_vtable>::getTarget_const(haxorg_ImmCmdAttrAdapter self, OrgContext* org_context) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdAttrAdapter, haxorg_ImmCmdAttrAdapter_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdAttr>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdAttr>::getTarget), self, org_context);
}
/* clang-format on */
