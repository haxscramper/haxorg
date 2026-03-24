/* clang-format off */
#include <wrappers/c/haxorg_c.h>
#include <wrappers/c/haxorg_c_utils.hpp>
#include <wrappers/c/haxorg_c_vtables.hpp>
#include <wrappers/c/haxorg_c_vtables_manual.hpp>
haxorg_UserTimeBreakdown org::bind::c::VTable<haxorg_UserTime, haxorg_UserTime_vtable>::getBreakdown_const(OrgContext* org_context, haxorg_UserTime self) {
  return org::bind::c::execute_cpp<haxorg_UserTimeBreakdown, haxorg_UserTimeBreakdown_vtable>(static_cast<hstd::UserTimeBreakdown(hstd::UserTime::*)() const>(&hstd::UserTime::getBreakdown), org_context, self);
}
haxorg_StdString org::bind::c::VTable<haxorg_UserTime, haxorg_UserTime_vtable>::format_const(OrgContext* org_context, haxorg_UserTime self) {
  return org::bind::c::execute_cpp<haxorg_StdString, haxorg_StdString_vtable>(static_cast<std::string(hstd::UserTime::*)() const>(&hstd::UserTime::format), org_context, self);
}
int64_t org::bind::c::VTable<haxorg_UserTime, haxorg_UserTime_vtable>::getTimeDeltaSeconds_const(OrgContext* org_context, haxorg_UserTime self, haxorg_UserTime other) {
  return org::bind::c::execute_cpp<int64_t, haxorg_builtin_vtable>(static_cast<int64_t(hstd::UserTime::*)(hstd::UserTime const&) const>(&hstd::UserTime::getTimeDeltaSeconds), org_context, self, other);
}
int64_t org::bind::c::VTable<haxorg_UserTime, haxorg_UserTime_vtable>::toUnixTimestamp_const(OrgContext* org_context, haxorg_UserTime self) {
  return org::bind::c::execute_cpp<int64_t, haxorg_builtin_vtable>(static_cast<int64_t(hstd::UserTime::*)() const>(&hstd::UserTime::toUnixTimestamp), org_context, self);
}
haxorg_StdString org::bind::c::VTable<haxorg_ParseSourceManager, haxorg_ParseSourceManager_vtable>::getPath_const(OrgContext* org_context, haxorg_ParseSourceManager self, haxorg_ParseSourceFileId id) {
  return org::bind::c::execute_cpp<haxorg_StdString, haxorg_StdString_vtable>(static_cast<std::string(org::parse::SourceManager::*)(org::parse::SourceFileId const&) const>(&org::parse::SourceManager::getPath), org_context, self, id);
}
haxorg_ParseSourceFileId org::bind::c::VTable<haxorg_ParseSourceManager, haxorg_ParseSourceManager_vtable>::getId_const(OrgContext* org_context, haxorg_ParseSourceManager self, haxorg_StdString path) {
  return org::bind::c::execute_cpp<haxorg_ParseSourceFileId, haxorg_ParseSourceFileId_vtable>(static_cast<org::parse::SourceFileId(org::parse::SourceManager::*)(std::string const&) const>(&org::parse::SourceManager::getId), org_context, self, path);
}
haxorg_StdString org::bind::c::VTable<haxorg_ParseSourceManager, haxorg_ParseSourceManager_vtable>::getSourceContent_const(OrgContext* org_context, haxorg_ParseSourceManager self, haxorg_ParseSourceFileId id) {
  return org::bind::c::execute_cpp<haxorg_StdString, haxorg_StdString_vtable>(static_cast<std::string const&(org::parse::SourceManager::*)(org::parse::SourceFileId const&) const>(&org::parse::SourceManager::getSourceContent), org_context, self, id);
}
haxorg_StdString org::bind::c::VTable<haxorg_ParseSourceManager, haxorg_ParseSourceManager_vtable>::getContentTextForPath_const(OrgContext* org_context, haxorg_ParseSourceManager self, haxorg_StdString path) {
  return org::bind::c::execute_cpp<haxorg_StdString, haxorg_StdString_vtable>(static_cast<std::string const&(org::parse::SourceManager::*)(std::string const&) const>(&org::parse::SourceManager::getContentTextForPath), org_context, self, path);
}
haxorg_ParseSourceFileId org::bind::c::VTable<haxorg_ParseSourceManager, haxorg_ParseSourceManager_vtable>::addSource(OrgContext* org_context, haxorg_ParseSourceManager self, haxorg_StdString path, haxorg_StdString content) {
  return org::bind::c::execute_cpp<haxorg_ParseSourceFileId, haxorg_ParseSourceFileId_vtable>(static_cast<org::parse::SourceFileId(org::parse::SourceManager::*)(std::string const&, std::string const&)>(&org::parse::SourceManager::addSource), org_context, self, path, content);
}
haxorg_OrgJsonKind org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::getKind_const(OrgContext* org_context, haxorg_OrgJson self) {
  return org::bind::c::execute_cpp<haxorg_OrgJsonKind, haxorg_builtin_vtable>(static_cast<OrgJsonKind(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getKind), org_context, self);
}
haxorg_StdString org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::getJsonString_const(OrgContext* org_context, haxorg_OrgJson self) {
  return org::bind::c::execute_cpp<haxorg_StdString, haxorg_StdString_vtable>(static_cast<std::string(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getJsonString), org_context, self);
}
haxorg_OrgJson org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::atIndex_const(OrgContext* org_context, haxorg_OrgJson self, int idx) {
  return org::bind::c::execute_cpp<haxorg_OrgJson, haxorg_OrgJson_vtable>(static_cast<org::sem::OrgJson(org::sem::OrgJson::*)(int) const>(&org::sem::OrgJson::at), org_context, self, idx);
}
haxorg_OrgJson org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::atField_const(OrgContext* org_context, haxorg_OrgJson self, haxorg_StdString name) {
  return org::bind::c::execute_cpp<haxorg_OrgJson, haxorg_OrgJson_vtable>(static_cast<org::sem::OrgJson(org::sem::OrgJson::*)(std::string const&) const>(&org::sem::OrgJson::at), org_context, self, name);
}
haxorg_StdString org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::getString_const(OrgContext* org_context, haxorg_OrgJson self) {
  return org::bind::c::execute_cpp<haxorg_StdString, haxorg_StdString_vtable>(static_cast<std::string(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getString), org_context, self);
}
haxorg_OrgJson org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::getField_const(OrgContext* org_context, haxorg_OrgJson self, haxorg_StdString name) {
  return org::bind::c::execute_cpp<haxorg_OrgJson, haxorg_OrgJson_vtable>(static_cast<org::sem::OrgJson(org::sem::OrgJson::*)(std::string const&) const>(&org::sem::OrgJson::getField), org_context, self, name);
}
haxorg_OrgJson org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::getItem_const(OrgContext* org_context, haxorg_OrgJson self, int index) {
  return org::bind::c::execute_cpp<haxorg_OrgJson, haxorg_OrgJson_vtable>(static_cast<org::sem::OrgJson(org::sem::OrgJson::*)(int) const>(&org::sem::OrgJson::getItem), org_context, self, index);
}
int org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::getInt_const(OrgContext* org_context, haxorg_OrgJson self) {
  return org::bind::c::execute_cpp<int, haxorg_builtin_vtable>(static_cast<int(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getInt), org_context, self);
}
bool org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::getBool_const(OrgContext* org_context, haxorg_OrgJson self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getBool), org_context, self);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::getArray_const(OrgContext* org_context, haxorg_OrgJson self) {
  return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<org::sem::OrgJson>(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getArray), org_context, self);
}
haxorg_StdString org::bind::c::VTable<haxorg_OrgJson, haxorg_OrgJson_vtable>::dump_const(OrgContext* org_context, haxorg_OrgJson self, int indent) {
  return org::bind::c::execute_cpp<haxorg_StdString, haxorg_StdString_vtable>(static_cast<std::string(org::sem::OrgJson::*)(int) const>(&org::sem::OrgJson::dump), org_context, self, indent);
}
haxorg_OrgSemKind org::bind::c::VTable<haxorg_Org, haxorg_Org_vtable>::getKind_const(OrgContext* org_context, haxorg_Org self) {
  return org::bind::c::execute_cpp<haxorg_OrgSemKind, haxorg_builtin_vtable>(static_cast<OrgSemKind(org::sem::Org::*)() const>(&org::sem::Org::getKind), org_context, self);
}
void org::bind::c::VTable<haxorg_Org, haxorg_Org_vtable>::push_back(OrgContext* org_context, haxorg_Org self, haxorg_SemId sub) {
  return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(static_cast<void(org::sem::Org::*)(org::sem::SemId<org::sem::Org>)>(&org::sem::Org::push_back), org_context, self, sub);
}
int org::bind::c::VTable<haxorg_Org, haxorg_Org_vtable>::size_const(OrgContext* org_context, haxorg_Org self) {
  return org::bind::c::execute_cpp<int, haxorg_builtin_vtable>(static_cast<int(org::sem::Org::*)() const>(&org::sem::Org::size), org_context, self);
}
void org::bind::c::VTable<haxorg_Org, haxorg_Org_vtable>::insert(OrgContext* org_context, haxorg_Org self, int pos, haxorg_SemId node) {
  return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(static_cast<void(org::sem::Org::*)(int, org::sem::SemId<org::sem::Org>)>(&org::sem::Org::insert), org_context, self, pos, node);
}
haxorg_SemId org::bind::c::VTable<haxorg_Org, haxorg_Org_vtable>::at_const(OrgContext* org_context, haxorg_Org self, int idx) {
  return org::bind::c::execute_cpp<haxorg_SemId, haxorg_SemId_vtable>(static_cast<org::sem::SemId<org::sem::Org>(org::sem::Org::*)(int) const>(&org::sem::Org::at), org_context, self, idx);
}
bool org::bind::c::VTable<haxorg_Org, haxorg_Org_vtable>::is_const(OrgContext* org_context, haxorg_Org self, haxorg_OrgSemKind kind) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Org::*)(OrgSemKind) const>(&org::sem::Org::is), org_context, self, kind);
}
void org::bind::c::VTable<haxorg_OperationsTracer, haxorg_OperationsTracer_vtable>::setTraceFileStr(OrgContext* org_context, haxorg_OperationsTracer self, haxorg_StdString outfile, bool overwrite) {
  return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(static_cast<void(hstd::OperationsTracer::*)(std::string const&, bool)>(&hstd::OperationsTracer::setTraceFileStr), org_context, self, outfile, overwrite);
}
void org::bind::c::VTable<haxorg_OperationsTracer, haxorg_OperationsTracer_vtable>::sendMessage(OrgContext* org_context, haxorg_OperationsTracer self, haxorg_StdString value, haxorg_StdString function, int line, haxorg_StdString file) {
  return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(static_cast<void(hstd::OperationsTracer::*)(std::string const&, std::string const&, int, std::string const&)>(&hstd::OperationsTracer::sendMessage), org_context, self, value, function, line, file);
}
haxorg_Cache org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::getDiagnosticStrings(OrgContext* org_context, haxorg_ParseContext self) {
  return org::bind::c::execute_cpp<haxorg_Cache, haxorg_Cache_vtable>(static_cast<std::shared_ptr<hstd::ext::Cache>(org::parse::ParseContext::*)()>(&org::parse::ParseContext::getDiagnosticStrings), org_context, self);
}
haxorg_ParseSourceFileId org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::addSource_const(OrgContext* org_context, haxorg_ParseContext self, haxorg_StdString path, haxorg_StdString content) {
  return org::bind::c::execute_cpp<haxorg_ParseSourceFileId, haxorg_ParseSourceFileId_vtable>(static_cast<org::parse::SourceFileId(org::parse::ParseContext::*)(std::string const&, std::string const&) const>(&org::parse::ParseContext::addSource), org_context, self, path, content);
}
haxorg_SemId org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::parseFileOpts(OrgContext* org_context, haxorg_ParseContext self, haxorg_StdString file, haxorg_OrgParseParameters opts) {
  return org::bind::c::execute_cpp<haxorg_SemId, haxorg_SemId_vtable>(static_cast<org::sem::SemId<org::sem::Org>(org::parse::ParseContext::*)(std::string const&, std::shared_ptr<org::parse::OrgParseParameters> const&)>(&org::parse::ParseContext::parseFileOpts), org_context, self, file, opts);
}
haxorg_SemId org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::parseFile(OrgContext* org_context, haxorg_ParseContext self, haxorg_StdString file) {
  return org::bind::c::execute_cpp<haxorg_SemId, haxorg_SemId_vtable>(static_cast<org::sem::SemId<org::sem::Org>(org::parse::ParseContext::*)(std::string const&)>(&org::parse::ParseContext::parseFile), org_context, self, file);
}
haxorg_SemId org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::parseString(OrgContext* org_context, haxorg_ParseContext self, haxorg_StdString text, haxorg_StdString file_name) {
  return org::bind::c::execute_cpp<haxorg_SemId, haxorg_SemId_vtable>(static_cast<org::sem::SemId<org::sem::Org>(org::parse::ParseContext::*)(std::string const&, std::string const&)>(&org::parse::ParseContext::parseString), org_context, self, text, file_name);
}
haxorg_SemId org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::parseStringOpts(OrgContext* org_context, haxorg_ParseContext self, haxorg_StdString text, haxorg_StdString file_name, haxorg_OrgParseParameters opts) {
  return org::bind::c::execute_cpp<haxorg_SemId, haxorg_SemId_vtable>(static_cast<org::sem::SemId<org::sem::Org>(org::parse::ParseContext::*)(std::string const, std::string const&, std::shared_ptr<org::parse::OrgParseParameters> const&)>(&org::parse::ParseContext::parseStringOpts), org_context, self, text, file_name, opts);
}
haxorg_StdOptional org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::parseDirectory(OrgContext* org_context, haxorg_ParseContext self, haxorg_StdString path) {
  return org::bind::c::execute_cpp<haxorg_StdOptional, haxorg_StdOptional_vtable>(static_cast<std::optional<org::sem::SemId<org::sem::Org>>(org::parse::ParseContext::*)(std::string const&)>(&org::parse::ParseContext::parseDirectory), org_context, self, path);
}
haxorg_StdOptional org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::parseDirectoryOpts(OrgContext* org_context, haxorg_ParseContext self, haxorg_StdString path, haxorg_OrgDirectoryParseParameters opts) {
  return org::bind::c::execute_cpp<haxorg_StdOptional, haxorg_StdOptional_vtable>(static_cast<std::optional<org::sem::SemId<org::sem::Org>>(org::parse::ParseContext::*)(std::string const&, std::shared_ptr<org::parse::OrgDirectoryParseParameters> const&)>(&org::parse::ParseContext::parseDirectoryOpts), org_context, self, path, opts);
}
haxorg_SemId org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::parseFileWithIncludes(OrgContext* org_context, haxorg_ParseContext self, haxorg_StdString file, haxorg_OrgDirectoryParseParameters opts) {
  return org::bind::c::execute_cpp<haxorg_SemId, haxorg_SemId_vtable>(static_cast<org::sem::SemId<org::sem::File>(org::parse::ParseContext::*)(std::string const&, std::shared_ptr<org::parse::OrgDirectoryParseParameters> const&)>(&org::parse::ParseContext::parseFileWithIncludes), org_context, self, file, opts);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::collectDiagnostics(OrgContext* org_context, haxorg_ParseContext self, haxorg_SemId tree, haxorg_Cache cache) {
  return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<hstd::ext::Report>(org::parse::ParseContext::*)(org::sem::SemId<org::sem::Org> const&, std::shared_ptr<hstd::ext::Cache> const&)>(&org::parse::ParseContext::collectDiagnostics), org_context, self, tree, cache);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_ParseContext, haxorg_ParseContext_vtable>::collectErrorNodes(OrgContext* org_context, haxorg_ParseContext self, haxorg_SemId tree) {
  return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<org::sem::SemId<org::sem::ErrorGroup>>(org::parse::ParseContext::*)(org::sem::SemId<org::sem::Org> const&)>(&org::parse::ParseContext::collectErrorNodes), org_context, self, tree);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmReflFieldId, haxorg_ImmReflFieldId_vtable>::getName_const(OrgContext* org_context, haxorg_ImmReflFieldId self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str(org::imm::ImmReflFieldId::*)() const>(&org::imm::ImmReflFieldId::getName), org_context, self);
}
haxorg_OrgSemKind org::bind::c::VTable<haxorg_ImmId, haxorg_ImmId_vtable>::getKind_const(OrgContext* org_context, haxorg_ImmId self) {
  return org::bind::c::execute_cpp<haxorg_OrgSemKind, haxorg_builtin_vtable>(static_cast<OrgSemKind(org::imm::ImmId::*)() const>(&org::imm::ImmId::getKind), org_context, self);
}
bool org::bind::c::VTable<haxorg_ImmId, haxorg_ImmId_vtable>::is_const(OrgContext* org_context, haxorg_ImmId self, haxorg_OrgSemKind kind) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmId::*)(OrgSemKind) const>(&org::imm::ImmId::is), org_context, self, kind);
}
haxorg_ImmIdNodeIdxT org::bind::c::VTable<haxorg_ImmId, haxorg_ImmId_vtable>::getNodeIndex_const(OrgContext* org_context, haxorg_ImmId self) {
  return org::bind::c::execute_cpp<haxorg_ImmIdNodeIdxT, haxorg_builtin_vtable>(static_cast<org::imm::ImmId::NodeIdxT(org::imm::ImmId::*)() const>(&org::imm::ImmId::getNodeIndex), org_context, self);
}
haxorg_StdString org::bind::c::VTable<haxorg_ImmId, haxorg_ImmId_vtable>::getReadableId_const(OrgContext* org_context, haxorg_ImmId self) {
  return org::bind::c::execute_cpp<haxorg_StdString, haxorg_StdString_vtable>(static_cast<std::string(org::imm::ImmId::*)() const>(&org::imm::ImmId::getReadableId), org_context, self);
}
bool org::bind::c::VTable<haxorg_ImmPath, haxorg_ImmPath_vtable>::empty_const(OrgContext* org_context, haxorg_ImmPath self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmPath::*)() const>(&org::imm::ImmPath::empty), org_context, self);
}
haxorg_ImmAstVersion org::bind::c::VTable<haxorg_ImmAstContext, haxorg_ImmAstContext_vtable>::addRoot(OrgContext* org_context, haxorg_ImmAstContext self, haxorg_SemId data) {
  return org::bind::c::execute_cpp<haxorg_ImmAstVersion, haxorg_ImmAstVersion_vtable>(static_cast<org::imm::ImmAstVersion(org::imm::ImmAstContext::*)(org::sem::SemId<org::sem::Org>)>(&org::imm::ImmAstContext::addRoot), org_context, self, data);
}
haxorg_ImmAstVersion org::bind::c::VTable<haxorg_ImmAstContext, haxorg_ImmAstContext_vtable>::getEmptyVersion(OrgContext* org_context, haxorg_ImmAstContext self) {
  return org::bind::c::execute_cpp<haxorg_ImmAstVersion, haxorg_ImmAstVersion_vtable>(static_cast<org::imm::ImmAstVersion(org::imm::ImmAstContext::*)()>(&org::imm::ImmAstContext::getEmptyVersion), org_context, self);
}
haxorg_SemId org::bind::c::VTable<haxorg_ImmAstContext, haxorg_ImmAstContext_vtable>::get(OrgContext* org_context, haxorg_ImmAstContext self, haxorg_ImmId id) {
  return org::bind::c::execute_cpp<haxorg_SemId, haxorg_SemId_vtable>(static_cast<org::sem::SemId<org::sem::Org>(org::imm::ImmAstContext::*)(org::imm::ImmId)>(&org::imm::ImmAstContext::get), org_context, self, id);
}
haxorg_ImmId org::bind::c::VTable<haxorg_ImmAstVersion, haxorg_ImmAstVersion_vtable>::getRoot_const(OrgContext* org_context, haxorg_ImmAstVersion self) {
  return org::bind::c::execute_cpp<haxorg_ImmId, haxorg_ImmId_vtable>(static_cast<org::imm::ImmId(org::imm::ImmAstVersion::*)() const>(&org::imm::ImmAstVersion::getRoot), org_context, self);
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmAstVersion, haxorg_ImmAstVersion_vtable>::getRootAdapter_const(OrgContext* org_context, haxorg_ImmAstVersion self) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<org::imm::ImmAdapter(org::imm::ImmAstVersion::*)() const>(&org::imm::ImmAstVersion::getRootAdapter), org_context, self);
}
haxorg_ImmAstContext org::bind::c::VTable<haxorg_ImmAstVersion, haxorg_ImmAstVersion_vtable>::getContext_const(OrgContext* org_context, haxorg_ImmAstVersion self) {
  return org::bind::c::execute_cpp<haxorg_ImmAstContext, haxorg_ImmAstContext_vtable>(static_cast<std::shared_ptr<org::imm::ImmAstContext>(org::imm::ImmAstVersion::*)() const>(&org::imm::ImmAstVersion::getContext), org_context, self);
}
haxorg_ImmAstReplaceEpoch org::bind::c::VTable<haxorg_ImmAstVersion, haxorg_ImmAstVersion_vtable>::getEpoch_const(OrgContext* org_context, haxorg_ImmAstVersion self) {
  return org::bind::c::execute_cpp<haxorg_ImmAstReplaceEpoch, haxorg_ImmAstReplaceEpoch_vtable>(static_cast<std::shared_ptr<org::imm::ImmAstReplaceEpoch>(org::imm::ImmAstVersion::*)() const>(&org::imm::ImmAstVersion::getEpoch), org_context, self);
}
int org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::size_const(OrgContext* org_context, haxorg_ImmAdapter self) {
  return org::bind::c::execute_cpp<int, haxorg_builtin_vtable>(static_cast<int(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::size), org_context, self);
}
bool org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::isNil_const(OrgContext* org_context, haxorg_ImmAdapter self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::isNil), org_context, self);
}
bool org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::isRoot_const(OrgContext* org_context, haxorg_ImmAdapter self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::isRoot), org_context, self);
}
haxorg_OrgSemKind org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::getKind_const(OrgContext* org_context, haxorg_ImmAdapter self) {
  return org::bind::c::execute_cpp<haxorg_OrgSemKind, haxorg_builtin_vtable>(static_cast<OrgSemKind(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::getKind), org_context, self);
}
haxorg_ImmUniqId org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::uniq_const(OrgContext* org_context, haxorg_ImmAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmUniqId, haxorg_ImmUniqId_vtable>(static_cast<org::imm::ImmUniqId(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::uniq), org_context, self);
}
haxorg_StdString org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::treeReprString_const(OrgContext* org_context, haxorg_ImmAdapter self) {
  return org::bind::c::execute_cpp<haxorg_StdString, haxorg_StdString_vtable>(static_cast<std::string(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::treeReprString), org_context, self);
}
haxorg_StdString org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::treeReprStringOpts_const(OrgContext* org_context, haxorg_ImmAdapter self, haxorg_ImmAdapterTreeReprConf conf) {
  return org::bind::c::execute_cpp<haxorg_StdString, haxorg_StdString_vtable>(static_cast<std::string(org::imm::ImmAdapter::*)(org::imm::ImmAdapter::TreeReprConf const&) const>(&org::imm::ImmAdapter::treeReprStringOpts), org_context, self, conf);
}
bool org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::isDirectParentOf_const(OrgContext* org_context, haxorg_ImmAdapter self, haxorg_ImmAdapter other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmAdapter::*)(org::imm::ImmAdapter const&) const>(&org::imm::ImmAdapter::isDirectParentOf), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::isIndirectParentOf_const(OrgContext* org_context, haxorg_ImmAdapter self, haxorg_ImmAdapter other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmAdapter::*)(org::imm::ImmAdapter const&) const>(&org::imm::ImmAdapter::isIndirectParentOf), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::isSubnodeOf_const(OrgContext* org_context, haxorg_ImmAdapter self, haxorg_ImmAdapter other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmAdapter::*)(org::imm::ImmAdapter const&) const>(&org::imm::ImmAdapter::isSubnodeOf), org_context, self, other);
}
haxorg_StdOptional org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::getParent_const(OrgContext* org_context, haxorg_ImmAdapter self) {
  return org::bind::c::execute_cpp<haxorg_StdOptional, haxorg_StdOptional_vtable>(static_cast<std::optional<org::imm::ImmAdapter>(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::getParent), org_context, self);
}
int org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::getSelfIndex_const(OrgContext* org_context, haxorg_ImmAdapter self) {
  return org::bind::c::execute_cpp<int, haxorg_builtin_vtable>(static_cast<int(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::getSelfIndex), org_context, self);
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::atPathStep_const(OrgContext* org_context, haxorg_ImmAdapter self, haxorg_ImmId id, haxorg_ImmPathStep idx) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapter::*)(org::imm::ImmId, org::imm::ImmPathStep) const>(&org::imm::ImmAdapter::at), org_context, self, id, idx);
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::atField_const(OrgContext* org_context, haxorg_ImmAdapter self, haxorg_ImmReflFieldId field) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapter::*)(org::imm::ImmReflFieldId const&) const>(&org::imm::ImmAdapter::at), org_context, self, field);
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::atIndex_const(OrgContext* org_context, haxorg_ImmAdapter self, int idx, bool withPath) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapter::*)(int, bool) const>(&org::imm::ImmAdapter::at), org_context, self, idx, withPath);
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::atPath_const(OrgContext* org_context, haxorg_ImmAdapter self, haxorg_HstdVec path, bool withPath) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapter::*)(hstd::Vec<int> const&, bool) const>(&org::imm::ImmAdapter::at), org_context, self, path, withPath);
}
bool org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::is_const(OrgContext* org_context, haxorg_ImmAdapter self, haxorg_OrgSemKind kind) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmAdapter::*)(OrgSemKind) const>(&org::imm::ImmAdapter::is), org_context, self, kind);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>::sub_const(OrgContext* org_context, haxorg_ImmAdapter self, bool withPath) {
  return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<org::imm::ImmAdapter>(org::imm::ImmAdapter::*)(bool) const>(&org::imm::ImmAdapter::sub), org_context, self, withPath);
}
haxorg_SemId org::bind::c::VTable<haxorg_AstTrackingPath, haxorg_AstTrackingPath_vtable>::getParent_const(OrgContext* org_context, haxorg_AstTrackingPath self, int offset) {
  return org::bind::c::execute_cpp<haxorg_SemId, haxorg_SemId_vtable>(static_cast<org::sem::SemId<org::sem::Org>(org::AstTrackingPath::*)(int) const>(&org::AstTrackingPath::getParent), org_context, self, offset);
}
haxorg_SemId org::bind::c::VTable<haxorg_AstTrackingPath, haxorg_AstTrackingPath_vtable>::getNode_const(OrgContext* org_context, haxorg_AstTrackingPath self) {
  return org::bind::c::execute_cpp<haxorg_SemId, haxorg_SemId_vtable>(static_cast<org::sem::SemId<org::sem::Org>(org::AstTrackingPath::*)() const>(&org::AstTrackingPath::getNode), org_context, self);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_AstTrackingAlternatives, haxorg_AstTrackingAlternatives_vtable>::getAllNodes_const(OrgContext* org_context, haxorg_AstTrackingAlternatives self) {
  return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::AstTrackingAlternatives::*)() const>(&org::AstTrackingAlternatives::getAllNodes), org_context, self);
}
haxorg_SemId org::bind::c::VTable<haxorg_AstTrackingAlternatives, haxorg_AstTrackingAlternatives_vtable>::getNode_const(OrgContext* org_context, haxorg_AstTrackingAlternatives self) {
  return org::bind::c::execute_cpp<haxorg_SemId, haxorg_SemId_vtable>(static_cast<org::sem::SemId<org::sem::Org>(org::AstTrackingAlternatives::*)() const>(&org::AstTrackingAlternatives::getNode), org_context, self);
}
haxorg_AstTrackingGroupRadioTarget org::bind::c::VTable<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>::getRadioTargetConst_const(OrgContext* org_context, haxorg_AstTrackingGroup self) {
  return org::bind::c::execute_cpp<haxorg_AstTrackingGroupRadioTarget, haxorg_AstTrackingGroupRadioTarget_vtable>(static_cast<org::AstTrackingGroup::RadioTarget const&(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::getRadioTarget), org_context, self);
}
haxorg_AstTrackingGroupTrackedHashtag org::bind::c::VTable<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>::getTrackedHashtagConst_const(OrgContext* org_context, haxorg_AstTrackingGroup self) {
  return org::bind::c::execute_cpp<haxorg_AstTrackingGroupTrackedHashtag, haxorg_AstTrackingGroupTrackedHashtag_vtable>(static_cast<org::AstTrackingGroup::TrackedHashtag const&(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::getTrackedHashtag), org_context, self);
}
haxorg_AstTrackingGroupTrackedHashtag org::bind::c::VTable<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>::getTrackedHashtagMut(OrgContext* org_context, haxorg_AstTrackingGroup self) {
  return org::bind::c::execute_cpp<haxorg_AstTrackingGroupTrackedHashtag, haxorg_AstTrackingGroupTrackedHashtag_vtable>(static_cast<org::AstTrackingGroup::TrackedHashtag&(org::AstTrackingGroup::*)()>(&org::AstTrackingGroup::getTrackedHashtag), org_context, self);
}
haxorg_AstTrackingGroupSingle org::bind::c::VTable<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>::getSingleConst_const(OrgContext* org_context, haxorg_AstTrackingGroup self) {
  return org::bind::c::execute_cpp<haxorg_AstTrackingGroupSingle, haxorg_AstTrackingGroupSingle_vtable>(static_cast<org::AstTrackingGroup::Single const&(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::getSingle), org_context, self);
}
haxorg_AstTrackingGroupRadioTarget org::bind::c::VTable<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>::getRadioTargetMut(OrgContext* org_context, haxorg_AstTrackingGroup self) {
  return org::bind::c::execute_cpp<haxorg_AstTrackingGroupRadioTarget, haxorg_AstTrackingGroupRadioTarget_vtable>(static_cast<org::AstTrackingGroup::RadioTarget&(org::AstTrackingGroup::*)()>(&org::AstTrackingGroup::getRadioTarget), org_context, self);
}
haxorg_AstTrackingGroupSingle org::bind::c::VTable<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>::getSingleMut(OrgContext* org_context, haxorg_AstTrackingGroup self) {
  return org::bind::c::execute_cpp<haxorg_AstTrackingGroupSingle, haxorg_AstTrackingGroupSingle_vtable>(static_cast<org::AstTrackingGroup::Single&(org::AstTrackingGroup::*)()>(&org::AstTrackingGroup::getSingle), org_context, self);
}
bool org::bind::c::VTable<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>::isSingle_const(OrgContext* org_context, haxorg_AstTrackingGroup self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::isSingle), org_context, self);
}
bool org::bind::c::VTable<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>::isTrackedHashtag_const(OrgContext* org_context, haxorg_AstTrackingGroup self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::isTrackedHashtag), org_context, self);
}
bool org::bind::c::VTable<haxorg_AstTrackingGroup, haxorg_AstTrackingGroup_vtable>::isRadioTarget_const(OrgContext* org_context, haxorg_AstTrackingGroup self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::isRadioTarget), org_context, self);
}
haxorg_StdOptional org::bind::c::VTable<haxorg_AstTrackingMap, haxorg_AstTrackingMap_vtable>::getIdPath_const(OrgContext* org_context, haxorg_AstTrackingMap self, haxorg_HstdStr id) {
  return org::bind::c::execute_cpp<haxorg_StdOptional, haxorg_StdOptional_vtable>(static_cast<std::optional<org::AstTrackingAlternatives>(org::AstTrackingMap::*)(hstd::Str const&) const>(&org::AstTrackingMap::getIdPath), org_context, self, id);
}
haxorg_StdOptional org::bind::c::VTable<haxorg_AstTrackingMap, haxorg_AstTrackingMap_vtable>::getNamePath_const(OrgContext* org_context, haxorg_AstTrackingMap self, haxorg_HstdStr id) {
  return org::bind::c::execute_cpp<haxorg_StdOptional, haxorg_StdOptional_vtable>(static_cast<std::optional<org::AstTrackingAlternatives>(org::AstTrackingMap::*)(hstd::Str const&) const>(&org::AstTrackingMap::getNamePath), org_context, self, id);
}
haxorg_StdOptional org::bind::c::VTable<haxorg_AstTrackingMap, haxorg_AstTrackingMap_vtable>::getAnchorTarget_const(OrgContext* org_context, haxorg_AstTrackingMap self, haxorg_HstdStr id) {
  return org::bind::c::execute_cpp<haxorg_StdOptional, haxorg_StdOptional_vtable>(static_cast<std::optional<org::AstTrackingAlternatives>(org::AstTrackingMap::*)(hstd::Str const&) const>(&org::AstTrackingMap::getAnchorTarget), org_context, self, id);
}
haxorg_StdOptional org::bind::c::VTable<haxorg_AstTrackingMap, haxorg_AstTrackingMap_vtable>::getFootnotePath_const(OrgContext* org_context, haxorg_AstTrackingMap self, haxorg_HstdStr id) {
  return org::bind::c::execute_cpp<haxorg_StdOptional, haxorg_StdOptional_vtable>(static_cast<std::optional<org::AstTrackingAlternatives>(org::AstTrackingMap::*)(hstd::Str const&) const>(&org::AstTrackingMap::getFootnotePath), org_context, self, id);
}
bool org::bind::c::VTable<haxorg_SequenceAnnotation, haxorg_SequenceAnnotation_vtable>::isAnnotatedWith_const(OrgContext* org_context, haxorg_SequenceAnnotation self, int groupKind, int segmentKind) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(hstd::SequenceAnnotation::*)(int, int) const>(&hstd::SequenceAnnotation::isAnnotatedWith), org_context, self, groupKind, segmentKind);
}
haxorg_GraphMapLinkRadio org::bind::c::VTable<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>::getRadio(OrgContext* org_context, haxorg_GraphMapLink self) {
  return org::bind::c::execute_cpp<haxorg_GraphMapLinkRadio, haxorg_GraphMapLinkRadio_vtable>(static_cast<org::graph::MapLink::Radio&(org::graph::MapLink::*)()>(&org::graph::MapLink::getRadio), org_context, self);
}
haxorg_GraphMapLinkRadio org::bind::c::VTable<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>::getRadio_const(OrgContext* org_context, haxorg_GraphMapLink self) {
  return org::bind::c::execute_cpp<haxorg_GraphMapLinkRadio, haxorg_GraphMapLinkRadio_vtable>(static_cast<org::graph::MapLink::Radio const&(org::graph::MapLink::*)() const>(&org::graph::MapLink::getRadio), org_context, self);
}
bool org::bind::c::VTable<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>::isRadio_const(OrgContext* org_context, haxorg_GraphMapLink self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::graph::MapLink::*)() const>(&org::graph::MapLink::isRadio), org_context, self);
}
haxorg_GraphMapLinkLink org::bind::c::VTable<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>::getLink(OrgContext* org_context, haxorg_GraphMapLink self) {
  return org::bind::c::execute_cpp<haxorg_GraphMapLinkLink, haxorg_GraphMapLinkLink_vtable>(static_cast<org::graph::MapLink::Link&(org::graph::MapLink::*)()>(&org::graph::MapLink::getLink), org_context, self);
}
haxorg_GraphMapLinkLink org::bind::c::VTable<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>::getLink_const(OrgContext* org_context, haxorg_GraphMapLink self) {
  return org::bind::c::execute_cpp<haxorg_GraphMapLinkLink, haxorg_GraphMapLinkLink_vtable>(static_cast<org::graph::MapLink::Link const&(org::graph::MapLink::*)() const>(&org::graph::MapLink::getLink), org_context, self);
}
bool org::bind::c::VTable<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>::isLink_const(OrgContext* org_context, haxorg_GraphMapLink self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::graph::MapLink::*)() const>(&org::graph::MapLink::isLink), org_context, self);
}
haxorg_GraphMapLinkKind org::bind::c::VTable<haxorg_GraphMapLink, haxorg_GraphMapLink_vtable>::getKind_const(OrgContext* org_context, haxorg_GraphMapLink self) {
  return org::bind::c::execute_cpp<haxorg_GraphMapLinkKind, haxorg_builtin_vtable>(static_cast<org::graph::MapLink::Kind(org::graph::MapLink::*)() const>(&org::graph::MapLink::getKind), org_context, self);
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_GraphMapNodeProp, haxorg_GraphMapNodeProp_vtable>::getAdapter_const(OrgContext* org_context, haxorg_GraphMapNodeProp self, haxorg_ImmAstContext context) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<org::imm::ImmAdapter(org::graph::MapNodeProp::*)(std::shared_ptr<org::imm::ImmAstContext> const&) const>(&org::graph::MapNodeProp::getAdapter), org_context, self, context);
}
haxorg_StdOptional org::bind::c::VTable<haxorg_GraphMapNodeProp, haxorg_GraphMapNodeProp_vtable>::getSubtreeId_const(OrgContext* org_context, haxorg_GraphMapNodeProp self, haxorg_ImmAstContext context) {
  return org::bind::c::execute_cpp<haxorg_StdOptional, haxorg_StdOptional_vtable>(static_cast<std::optional<hstd::Str>(org::graph::MapNodeProp::*)(std::shared_ptr<org::imm::ImmAstContext> const&) const>(&org::graph::MapNodeProp::getSubtreeId), org_context, self, context);
}
haxorg_StdOptional org::bind::c::VTable<haxorg_GraphMapNodeProp, haxorg_GraphMapNodeProp_vtable>::getFootnoteName_const(OrgContext* org_context, haxorg_GraphMapNodeProp self, haxorg_ImmAstContext context) {
  return org::bind::c::execute_cpp<haxorg_StdOptional, haxorg_StdOptional_vtable>(static_cast<std::optional<hstd::Str>(org::graph::MapNodeProp::*)(std::shared_ptr<org::imm::ImmAstContext> const&) const>(&org::graph::MapNodeProp::getFootnoteName), org_context, self, context);
}
bool org::bind::c::VTable<haxorg_GraphMapNode, haxorg_GraphMapNode_vtable>::__eq___const(OrgContext* org_context, haxorg_GraphMapNode self, haxorg_GraphMapNode other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::graph::MapNode::*)(org::graph::MapNode const&) const>(&org::graph::MapNode::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_GraphMapNode, haxorg_GraphMapNode_vtable>::__lt___const(OrgContext* org_context, haxorg_GraphMapNode self, haxorg_GraphMapNode other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::graph::MapNode::*)(org::graph::MapNode const&) const>(&org::graph::MapNode::operator<), org_context, self, other);
}
int org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::nodeCount_const(OrgContext* org_context, haxorg_GraphMapGraph self) {
  return org::bind::c::execute_cpp<int, haxorg_builtin_vtable>(static_cast<int(org::graph::MapGraph::*)() const>(&org::graph::MapGraph::nodeCount), org_context, self);
}
int org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::edgeCount_const(OrgContext* org_context, haxorg_GraphMapGraph self) {
  return org::bind::c::execute_cpp<int, haxorg_builtin_vtable>(static_cast<int(org::graph::MapGraph::*)() const>(&org::graph::MapGraph::edgeCount), org_context, self);
}
haxorg_GraphAdjNodesList org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::outNodes_const(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapNode node) {
  return org::bind::c::execute_cpp<haxorg_GraphAdjNodesList, haxorg_HstdVec_vtable>(static_cast<org::graph::AdjNodesList const&(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::outNodes), org_context, self, node);
}
haxorg_GraphAdjNodesList org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::inNodes_const(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapNode node) {
  return org::bind::c::execute_cpp<haxorg_GraphAdjNodesList, haxorg_HstdVec_vtable>(static_cast<org::graph::AdjNodesList const&(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::inNodes), org_context, self, node);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::adjEdges_const(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapNode node) {
  return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<org::graph::MapEdge>(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::adjEdges), org_context, self, node);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::adjNodes_const(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapNode node) {
  return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<org::graph::MapNode>(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::adjNodes), org_context, self, node);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::outEdges_const(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapNode node) {
  return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<org::graph::MapEdge>(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::outEdges), org_context, self, node);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::inEdges_const(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapNode node) {
  return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<org::graph::MapEdge>(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::inEdges), org_context, self, node);
}
int org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::outDegree_const(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapNode node) {
  return org::bind::c::execute_cpp<int, haxorg_builtin_vtable>(static_cast<int(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::outDegree), org_context, self, node);
}
int org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::inDegree_const(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapNode node) {
  return org::bind::c::execute_cpp<int, haxorg_builtin_vtable>(static_cast<int(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::inDegree), org_context, self, node);
}
bool org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::isRegisteredNode_const(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapNode id) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::isRegisteredNode), org_context, self, id);
}
bool org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::isRegisteredNodeById_const(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_ImmUniqId id) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::graph::MapGraph::*)(org::imm::ImmUniqId const&) const>(&org::graph::MapGraph::isRegisteredNode), org_context, self, id);
}
haxorg_GraphMapNodeProp org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::atMapNode_const(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapNode node) {
  return org::bind::c::execute_cpp<haxorg_GraphMapNodeProp, haxorg_GraphMapNodeProp_vtable>(static_cast<org::graph::MapNodeProp const&(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::at), org_context, self, node);
}
haxorg_GraphMapEdgeProp org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::atMapEdge_const(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapEdge edge) {
  return org::bind::c::execute_cpp<haxorg_GraphMapEdgeProp, haxorg_GraphMapEdgeProp_vtable>(static_cast<org::graph::MapEdgeProp const&(org::graph::MapGraph::*)(org::graph::MapEdge const&) const>(&org::graph::MapGraph::at), org_context, self, edge);
}
void org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::addEdge(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapEdge edge) {
  return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(static_cast<void(org::graph::MapGraph::*)(org::graph::MapEdge const&)>(&org::graph::MapGraph::addEdge), org_context, self, edge);
}
void org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::addEdgeWithProp(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapEdge edge, haxorg_GraphMapEdgeProp prop) {
  return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(static_cast<void(org::graph::MapGraph::*)(org::graph::MapEdge const&, org::graph::MapEdgeProp const&)>(&org::graph::MapGraph::addEdge), org_context, self, edge, prop);
}
void org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::addNode(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapNode node) {
  return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(static_cast<void(org::graph::MapGraph::*)(org::graph::MapNode const&)>(&org::graph::MapGraph::addNode), org_context, self, node);
}
void org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::addNodeWithProp(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapNode node, haxorg_GraphMapNodeProp prop) {
  return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(static_cast<void(org::graph::MapGraph::*)(org::graph::MapNode const&, org::graph::MapNodeProp const&)>(&org::graph::MapGraph::addNode), org_context, self, node, prop);
}
bool org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::hasEdge_const(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapNode source, haxorg_GraphMapNode target) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::graph::MapGraph::*)(org::graph::MapNode const&, org::graph::MapNode const&) const>(&org::graph::MapGraph::hasEdge), org_context, self, source, target);
}
bool org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::hasNode_const(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_GraphMapNode node) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::hasNode), org_context, self, node);
}
bool org::bind::c::VTable<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>::has2AdapterEdge_const(OrgContext* org_context, haxorg_GraphMapGraph self, haxorg_ImmAdapter source, haxorg_ImmAdapter target) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::graph::MapGraph::*)(org::imm::ImmAdapter const&, org::imm::ImmAdapter const&) const>(&org::graph::MapGraph::hasEdge), org_context, self, source, target);
}
haxorg_GraphMapGraph org::bind::c::VTable<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>::getGraph_const(OrgContext* org_context, haxorg_GraphMapGraphState self) {
  return org::bind::c::execute_cpp<haxorg_GraphMapGraph, haxorg_GraphMapGraph_vtable>(static_cast<std::shared_ptr<org::graph::MapGraph>(org::graph::MapGraphState::*)() const>(&org::graph::MapGraphState::getGraph), org_context, self);
}
haxorg_GraphMapGraphState org::bind::c::VTable<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>::FromAstContext(OrgContext* org_context, haxorg_GraphMapGraphState self, haxorg_ImmAstContext ast) {
  return org::bind::c::execute_cpp<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>(static_cast<std::shared_ptr<org::graph::MapGraphState>(*)(std::shared_ptr<org::imm::ImmAstContext>)>(&org::graph::MapGraphState::FromAstContext), org_context, ast);
}
void org::bind::c::VTable<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>::registerNode(OrgContext* org_context, haxorg_GraphMapGraphState self, haxorg_GraphMapNodeProp node, haxorg_GraphMapConfig conf) {
  return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(static_cast<void(org::graph::MapGraphState::*)(org::graph::MapNodeProp const&, std::shared_ptr<org::graph::MapConfig> const&)>(&org::graph::MapGraphState::registerNode), org_context, self, node, conf);
}
void org::bind::c::VTable<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>::addNode(OrgContext* org_context, haxorg_GraphMapGraphState self, haxorg_ImmAdapter node, haxorg_GraphMapConfig conf) {
  return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(static_cast<void(org::graph::MapGraphState::*)(org::imm::ImmAdapter const&, std::shared_ptr<org::graph::MapConfig> const&)>(&org::graph::MapGraphState::addNode), org_context, self, node, conf);
}
void org::bind::c::VTable<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>::addNodeRec(OrgContext* org_context, haxorg_GraphMapGraphState self, haxorg_ImmAstContext ast, haxorg_ImmAdapter node, haxorg_GraphMapConfig conf) {
  return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(static_cast<void(org::graph::MapGraphState::*)(std::shared_ptr<org::imm::ImmAstContext> const&, org::imm::ImmAdapter const&, std::shared_ptr<org::graph::MapConfig> const&)>(&org::graph::MapGraphState::addNodeRec), org_context, self, ast, node, conf);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>::getUnresolvedSubtreeLinks_const(OrgContext* org_context, haxorg_GraphMapGraphState self, haxorg_ImmSubtreeAdapter node, haxorg_GraphMapConfig conf) {
  return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<org::graph::MapLink>(org::graph::MapGraphState::*)(org::imm::ImmAdapterT<org::imm::ImmSubtree>, std::shared_ptr<org::graph::MapConfig> const&) const>(&org::graph::MapGraphState::getUnresolvedSubtreeLinks), org_context, self, node, conf);
}
haxorg_StdOptional org::bind::c::VTable<haxorg_GraphMapGraphState, haxorg_GraphMapGraphState_vtable>::getUnresolvedLink_const(OrgContext* org_context, haxorg_GraphMapGraphState self, haxorg_ImmLinkAdapter node, haxorg_GraphMapConfig conf) {
  return org::bind::c::execute_cpp<haxorg_StdOptional, haxorg_StdOptional_vtable>(static_cast<std::optional<org::graph::MapLink>(org::graph::MapGraphState::*)(org::imm::ImmAdapterT<org::imm::ImmLink>, std::shared_ptr<org::graph::MapConfig> const&) const>(&org::graph::MapGraphState::getUnresolvedLink), org_context, self, node, conf);
}
bool org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::__eq___const(OrgContext* org_context, haxorg_LispCode self, haxorg_LispCode other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LispCode::*)(org::sem::LispCode const&) const>(&org::sem::LispCode::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::isCall_const(OrgContext* org_context, haxorg_LispCode self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isCall), org_context, self);
}
haxorg_LispCodeCall org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getCallConst_const(OrgContext* org_context, haxorg_LispCode self) {
  return org::bind::c::execute_cpp<haxorg_LispCodeCall, haxorg_LispCodeCall_vtable>(static_cast<org::sem::LispCode::Call const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getCall), org_context, self);
}
haxorg_LispCodeCall org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getCallMut(OrgContext* org_context, haxorg_LispCode self) {
  return org::bind::c::execute_cpp<haxorg_LispCodeCall, haxorg_LispCodeCall_vtable>(static_cast<org::sem::LispCode::Call&(org::sem::LispCode::*)()>(&org::sem::LispCode::getCall), org_context, self);
}
bool org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::isList_const(OrgContext* org_context, haxorg_LispCode self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isList), org_context, self);
}
haxorg_LispCodeList org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getListConst_const(OrgContext* org_context, haxorg_LispCode self) {
  return org::bind::c::execute_cpp<haxorg_LispCodeList, haxorg_LispCodeList_vtable>(static_cast<org::sem::LispCode::List const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getList), org_context, self);
}
haxorg_LispCodeList org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getListMut(OrgContext* org_context, haxorg_LispCode self) {
  return org::bind::c::execute_cpp<haxorg_LispCodeList, haxorg_LispCodeList_vtable>(static_cast<org::sem::LispCode::List&(org::sem::LispCode::*)()>(&org::sem::LispCode::getList), org_context, self);
}
bool org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::isKeyValue_const(OrgContext* org_context, haxorg_LispCode self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isKeyValue), org_context, self);
}
haxorg_LispCodeKeyValue org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getKeyValueConst_const(OrgContext* org_context, haxorg_LispCode self) {
  return org::bind::c::execute_cpp<haxorg_LispCodeKeyValue, haxorg_LispCodeKeyValue_vtable>(static_cast<org::sem::LispCode::KeyValue const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getKeyValue), org_context, self);
}
haxorg_LispCodeKeyValue org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getKeyValueMut(OrgContext* org_context, haxorg_LispCode self) {
  return org::bind::c::execute_cpp<haxorg_LispCodeKeyValue, haxorg_LispCodeKeyValue_vtable>(static_cast<org::sem::LispCode::KeyValue&(org::sem::LispCode::*)()>(&org::sem::LispCode::getKeyValue), org_context, self);
}
bool org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::isNumber_const(OrgContext* org_context, haxorg_LispCode self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isNumber), org_context, self);
}
haxorg_LispCodeNumber org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getNumberConst_const(OrgContext* org_context, haxorg_LispCode self) {
  return org::bind::c::execute_cpp<haxorg_LispCodeNumber, haxorg_LispCodeNumber_vtable>(static_cast<org::sem::LispCode::Number const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getNumber), org_context, self);
}
haxorg_LispCodeNumber org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getNumberMut(OrgContext* org_context, haxorg_LispCode self) {
  return org::bind::c::execute_cpp<haxorg_LispCodeNumber, haxorg_LispCodeNumber_vtable>(static_cast<org::sem::LispCode::Number&(org::sem::LispCode::*)()>(&org::sem::LispCode::getNumber), org_context, self);
}
bool org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::isText_const(OrgContext* org_context, haxorg_LispCode self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isText), org_context, self);
}
haxorg_LispCodeText org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getTextConst_const(OrgContext* org_context, haxorg_LispCode self) {
  return org::bind::c::execute_cpp<haxorg_LispCodeText, haxorg_LispCodeText_vtable>(static_cast<org::sem::LispCode::Text const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getText), org_context, self);
}
haxorg_LispCodeText org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getTextMut(OrgContext* org_context, haxorg_LispCode self) {
  return org::bind::c::execute_cpp<haxorg_LispCodeText, haxorg_LispCodeText_vtable>(static_cast<org::sem::LispCode::Text&(org::sem::LispCode::*)()>(&org::sem::LispCode::getText), org_context, self);
}
bool org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::isIdent_const(OrgContext* org_context, haxorg_LispCode self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isIdent), org_context, self);
}
haxorg_LispCodeIdent org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getIdentConst_const(OrgContext* org_context, haxorg_LispCode self) {
  return org::bind::c::execute_cpp<haxorg_LispCodeIdent, haxorg_LispCodeIdent_vtable>(static_cast<org::sem::LispCode::Ident const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getIdent), org_context, self);
}
haxorg_LispCodeIdent org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getIdentMut(OrgContext* org_context, haxorg_LispCode self) {
  return org::bind::c::execute_cpp<haxorg_LispCodeIdent, haxorg_LispCodeIdent_vtable>(static_cast<org::sem::LispCode::Ident&(org::sem::LispCode::*)()>(&org::sem::LispCode::getIdent), org_context, self);
}
bool org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::isBoolean_const(OrgContext* org_context, haxorg_LispCode self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isBoolean), org_context, self);
}
haxorg_LispCodeBoolean org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getBooleanConst_const(OrgContext* org_context, haxorg_LispCode self) {
  return org::bind::c::execute_cpp<haxorg_LispCodeBoolean, haxorg_LispCodeBoolean_vtable>(static_cast<org::sem::LispCode::Boolean const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getBoolean), org_context, self);
}
haxorg_LispCodeBoolean org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getBooleanMut(OrgContext* org_context, haxorg_LispCode self) {
  return org::bind::c::execute_cpp<haxorg_LispCodeBoolean, haxorg_LispCodeBoolean_vtable>(static_cast<org::sem::LispCode::Boolean&(org::sem::LispCode::*)()>(&org::sem::LispCode::getBoolean), org_context, self);
}
bool org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::isReal_const(OrgContext* org_context, haxorg_LispCode self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isReal), org_context, self);
}
haxorg_LispCodeReal org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getRealConst_const(OrgContext* org_context, haxorg_LispCode self) {
  return org::bind::c::execute_cpp<haxorg_LispCodeReal, haxorg_LispCodeReal_vtable>(static_cast<org::sem::LispCode::Real const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getReal), org_context, self);
}
haxorg_LispCodeReal org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getRealMut(OrgContext* org_context, haxorg_LispCode self) {
  return org::bind::c::execute_cpp<haxorg_LispCodeReal, haxorg_LispCodeReal_vtable>(static_cast<org::sem::LispCode::Real&(org::sem::LispCode::*)()>(&org::sem::LispCode::getReal), org_context, self);
}
haxorg_LispCodeKind org::bind::c::VTable<haxorg_LispCode, haxorg_LispCode_vtable>::getKind_const(OrgContext* org_context, haxorg_LispCode self) {
  return org::bind::c::execute_cpp<haxorg_LispCodeKind, haxorg_builtin_vtable>(static_cast<org::sem::LispCode::Kind(org::sem::LispCode::*)() const>(&org::sem::LispCode::getKind), org_context, self);
}
bool org::bind::c::VTable<haxorg_LispCodeCall, haxorg_LispCodeCall_vtable>::__eq___const(OrgContext* org_context, haxorg_LispCodeCall self, haxorg_LispCodeCall other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LispCode::Call::*)(org::sem::LispCode::Call const&) const>(&org::sem::LispCode::Call::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_LispCodeList, haxorg_LispCodeList_vtable>::__eq___const(OrgContext* org_context, haxorg_LispCodeList self, haxorg_LispCodeList other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LispCode::List::*)(org::sem::LispCode::List const&) const>(&org::sem::LispCode::List::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_LispCodeKeyValue, haxorg_LispCodeKeyValue_vtable>::__eq___const(OrgContext* org_context, haxorg_LispCodeKeyValue self, haxorg_LispCodeKeyValue other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LispCode::KeyValue::*)(org::sem::LispCode::KeyValue const&) const>(&org::sem::LispCode::KeyValue::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_LispCodeNumber, haxorg_LispCodeNumber_vtable>::__eq___const(OrgContext* org_context, haxorg_LispCodeNumber self, haxorg_LispCodeNumber other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LispCode::Number::*)(org::sem::LispCode::Number const&) const>(&org::sem::LispCode::Number::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_LispCodeText, haxorg_LispCodeText_vtable>::__eq___const(OrgContext* org_context, haxorg_LispCodeText self, haxorg_LispCodeText other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LispCode::Text::*)(org::sem::LispCode::Text const&) const>(&org::sem::LispCode::Text::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_LispCodeIdent, haxorg_LispCodeIdent_vtable>::__eq___const(OrgContext* org_context, haxorg_LispCodeIdent self, haxorg_LispCodeIdent other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LispCode::Ident::*)(org::sem::LispCode::Ident const&) const>(&org::sem::LispCode::Ident::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_LispCodeBoolean, haxorg_LispCodeBoolean_vtable>::__eq___const(OrgContext* org_context, haxorg_LispCodeBoolean self, haxorg_LispCodeBoolean other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LispCode::Boolean::*)(org::sem::LispCode::Boolean const&) const>(&org::sem::LispCode::Boolean::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_LispCodeReal, haxorg_LispCodeReal_vtable>::__eq___const(OrgContext* org_context, haxorg_LispCodeReal self, haxorg_LispCodeReal other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LispCode::Real::*)(org::sem::LispCode::Real const&) const>(&org::sem::LispCode::Real::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_Tblfm, haxorg_Tblfm_vtable>::__eq___const(OrgContext* org_context, haxorg_Tblfm self, haxorg_Tblfm other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Tblfm::*)(org::sem::Tblfm const&) const>(&org::sem::Tblfm::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::__eq___const(OrgContext* org_context, haxorg_TblfmExpr self, haxorg_TblfmExpr other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Tblfm::Expr::*)(org::sem::Tblfm::Expr const&) const>(&org::sem::Tblfm::Expr::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::isAxisRef_const(OrgContext* org_context, haxorg_TblfmExpr self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isAxisRef), org_context, self);
}
haxorg_TblfmExprAxisRef org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getAxisRefConst_const(OrgContext* org_context, haxorg_TblfmExpr self) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRef, haxorg_TblfmExprAxisRef_vtable>(static_cast<org::sem::Tblfm::Expr::AxisRef const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getAxisRef), org_context, self);
}
haxorg_TblfmExprAxisRef org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getAxisRefMut(OrgContext* org_context, haxorg_TblfmExpr self) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRef, haxorg_TblfmExprAxisRef_vtable>(static_cast<org::sem::Tblfm::Expr::AxisRef&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getAxisRef), org_context, self);
}
bool org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::isAxisName_const(OrgContext* org_context, haxorg_TblfmExpr self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isAxisName), org_context, self);
}
haxorg_TblfmExprAxisName org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getAxisNameConst_const(OrgContext* org_context, haxorg_TblfmExpr self) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprAxisName, haxorg_TblfmExprAxisName_vtable>(static_cast<org::sem::Tblfm::Expr::AxisName const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getAxisName), org_context, self);
}
haxorg_TblfmExprAxisName org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getAxisNameMut(OrgContext* org_context, haxorg_TblfmExpr self) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprAxisName, haxorg_TblfmExprAxisName_vtable>(static_cast<org::sem::Tblfm::Expr::AxisName&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getAxisName), org_context, self);
}
bool org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::isIntLiteral_const(OrgContext* org_context, haxorg_TblfmExpr self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isIntLiteral), org_context, self);
}
haxorg_TblfmExprIntLiteral org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getIntLiteralConst_const(OrgContext* org_context, haxorg_TblfmExpr self) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprIntLiteral, haxorg_TblfmExprIntLiteral_vtable>(static_cast<org::sem::Tblfm::Expr::IntLiteral const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getIntLiteral), org_context, self);
}
haxorg_TblfmExprIntLiteral org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getIntLiteralMut(OrgContext* org_context, haxorg_TblfmExpr self) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprIntLiteral, haxorg_TblfmExprIntLiteral_vtable>(static_cast<org::sem::Tblfm::Expr::IntLiteral&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getIntLiteral), org_context, self);
}
bool org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::isFloatLiteral_const(OrgContext* org_context, haxorg_TblfmExpr self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isFloatLiteral), org_context, self);
}
haxorg_TblfmExprFloatLiteral org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getFloatLiteralConst_const(OrgContext* org_context, haxorg_TblfmExpr self) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprFloatLiteral, haxorg_TblfmExprFloatLiteral_vtable>(static_cast<org::sem::Tblfm::Expr::FloatLiteral const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getFloatLiteral), org_context, self);
}
haxorg_TblfmExprFloatLiteral org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getFloatLiteralMut(OrgContext* org_context, haxorg_TblfmExpr self) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprFloatLiteral, haxorg_TblfmExprFloatLiteral_vtable>(static_cast<org::sem::Tblfm::Expr::FloatLiteral&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getFloatLiteral), org_context, self);
}
bool org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::isRangeRef_const(OrgContext* org_context, haxorg_TblfmExpr self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isRangeRef), org_context, self);
}
haxorg_TblfmExprRangeRef org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getRangeRefConst_const(OrgContext* org_context, haxorg_TblfmExpr self) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprRangeRef, haxorg_TblfmExprRangeRef_vtable>(static_cast<org::sem::Tblfm::Expr::RangeRef const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getRangeRef), org_context, self);
}
haxorg_TblfmExprRangeRef org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getRangeRefMut(OrgContext* org_context, haxorg_TblfmExpr self) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprRangeRef, haxorg_TblfmExprRangeRef_vtable>(static_cast<org::sem::Tblfm::Expr::RangeRef&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getRangeRef), org_context, self);
}
bool org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::isCall_const(OrgContext* org_context, haxorg_TblfmExpr self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isCall), org_context, self);
}
haxorg_TblfmExprCall org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getCallConst_const(OrgContext* org_context, haxorg_TblfmExpr self) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprCall, haxorg_TblfmExprCall_vtable>(static_cast<org::sem::Tblfm::Expr::Call const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getCall), org_context, self);
}
haxorg_TblfmExprCall org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getCallMut(OrgContext* org_context, haxorg_TblfmExpr self) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprCall, haxorg_TblfmExprCall_vtable>(static_cast<org::sem::Tblfm::Expr::Call&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getCall), org_context, self);
}
bool org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::isElisp_const(OrgContext* org_context, haxorg_TblfmExpr self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isElisp), org_context, self);
}
haxorg_TblfmExprElisp org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getElispConst_const(OrgContext* org_context, haxorg_TblfmExpr self) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprElisp, haxorg_TblfmExprElisp_vtable>(static_cast<org::sem::Tblfm::Expr::Elisp const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getElisp), org_context, self);
}
haxorg_TblfmExprElisp org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getElispMut(OrgContext* org_context, haxorg_TblfmExpr self) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprElisp, haxorg_TblfmExprElisp_vtable>(static_cast<org::sem::Tblfm::Expr::Elisp&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getElisp), org_context, self);
}
haxorg_TblfmExprKind org::bind::c::VTable<haxorg_TblfmExpr, haxorg_TblfmExpr_vtable>::getKind_const(OrgContext* org_context, haxorg_TblfmExpr self) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprKind, haxorg_builtin_vtable>(static_cast<org::sem::Tblfm::Expr::Kind(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getKind), org_context, self);
}
bool org::bind::c::VTable<haxorg_TblfmExprAxisRef, haxorg_TblfmExprAxisRef_vtable>::__eq___const(OrgContext* org_context, haxorg_TblfmExprAxisRef self, haxorg_TblfmExprAxisRef other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Tblfm::Expr::AxisRef::*)(org::sem::Tblfm::Expr::AxisRef const&) const>(&org::sem::Tblfm::Expr::AxisRef::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>::__eq___const(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition self, haxorg_TblfmExprAxisRefPosition other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::*)(org::sem::Tblfm::Expr::AxisRef::Position const&) const>(&org::sem::Tblfm::Expr::AxisRef::Position::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>::isIndex_const(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::isIndex), org_context, self);
}
haxorg_TblfmExprAxisRefPositionIndex org::bind::c::VTable<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>::getIndexConst_const(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition self) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPositionIndex, haxorg_TblfmExprAxisRefPositionIndex_vtable>(static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Index const&(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::getIndex), org_context, self);
}
haxorg_TblfmExprAxisRefPositionIndex org::bind::c::VTable<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>::getIndexMut(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition self) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPositionIndex, haxorg_TblfmExprAxisRefPositionIndex_vtable>(static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Index&(org::sem::Tblfm::Expr::AxisRef::Position::*)()>(&org::sem::Tblfm::Expr::AxisRef::Position::getIndex), org_context, self);
}
bool org::bind::c::VTable<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>::isName_const(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::isName), org_context, self);
}
haxorg_TblfmExprAxisRefPositionName org::bind::c::VTable<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>::getNameConst_const(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition self) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPositionName, haxorg_TblfmExprAxisRefPositionName_vtable>(static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Name const&(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::getName), org_context, self);
}
haxorg_TblfmExprAxisRefPositionName org::bind::c::VTable<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>::getNameMut(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition self) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPositionName, haxorg_TblfmExprAxisRefPositionName_vtable>(static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Name&(org::sem::Tblfm::Expr::AxisRef::Position::*)()>(&org::sem::Tblfm::Expr::AxisRef::Position::getName), org_context, self);
}
haxorg_TblfmExprAxisRefPositionKind org::bind::c::VTable<haxorg_TblfmExprAxisRefPosition, haxorg_TblfmExprAxisRefPosition_vtable>::getKind_const(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition self) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPositionKind, haxorg_builtin_vtable>(static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Kind(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::getKind), org_context, self);
}
bool org::bind::c::VTable<haxorg_TblfmExprAxisRefPositionIndex, haxorg_TblfmExprAxisRefPositionIndex_vtable>::__eq___const(OrgContext* org_context, haxorg_TblfmExprAxisRefPositionIndex self, haxorg_TblfmExprAxisRefPositionIndex other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::Index::*)(org::sem::Tblfm::Expr::AxisRef::Position::Index const&) const>(&org::sem::Tblfm::Expr::AxisRef::Position::Index::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_TblfmExprAxisRefPositionName, haxorg_TblfmExprAxisRefPositionName_vtable>::__eq___const(OrgContext* org_context, haxorg_TblfmExprAxisRefPositionName self, haxorg_TblfmExprAxisRefPositionName other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::Name::*)(org::sem::Tblfm::Expr::AxisRef::Position::Name const&) const>(&org::sem::Tblfm::Expr::AxisRef::Position::Name::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_TblfmExprAxisName, haxorg_TblfmExprAxisName_vtable>::__eq___const(OrgContext* org_context, haxorg_TblfmExprAxisName self, haxorg_TblfmExprAxisName other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Tblfm::Expr::AxisName::*)(org::sem::Tblfm::Expr::AxisName const&) const>(&org::sem::Tblfm::Expr::AxisName::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_TblfmExprIntLiteral, haxorg_TblfmExprIntLiteral_vtable>::__eq___const(OrgContext* org_context, haxorg_TblfmExprIntLiteral self, haxorg_TblfmExprIntLiteral other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Tblfm::Expr::IntLiteral::*)(org::sem::Tblfm::Expr::IntLiteral const&) const>(&org::sem::Tblfm::Expr::IntLiteral::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_TblfmExprFloatLiteral, haxorg_TblfmExprFloatLiteral_vtable>::__eq___const(OrgContext* org_context, haxorg_TblfmExprFloatLiteral self, haxorg_TblfmExprFloatLiteral other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Tblfm::Expr::FloatLiteral::*)(org::sem::Tblfm::Expr::FloatLiteral const&) const>(&org::sem::Tblfm::Expr::FloatLiteral::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_TblfmExprRangeRef, haxorg_TblfmExprRangeRef_vtable>::__eq___const(OrgContext* org_context, haxorg_TblfmExprRangeRef self, haxorg_TblfmExprRangeRef other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Tblfm::Expr::RangeRef::*)(org::sem::Tblfm::Expr::RangeRef const&) const>(&org::sem::Tblfm::Expr::RangeRef::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_TblfmExprCall, haxorg_TblfmExprCall_vtable>::__eq___const(OrgContext* org_context, haxorg_TblfmExprCall self, haxorg_TblfmExprCall other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Tblfm::Expr::Call::*)(org::sem::Tblfm::Expr::Call const&) const>(&org::sem::Tblfm::Expr::Call::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_TblfmExprElisp, haxorg_TblfmExprElisp_vtable>::__eq___const(OrgContext* org_context, haxorg_TblfmExprElisp self, haxorg_TblfmExprElisp other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Tblfm::Expr::Elisp::*)(org::sem::Tblfm::Expr::Elisp const&) const>(&org::sem::Tblfm::Expr::Elisp::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_TblfmAssign, haxorg_TblfmAssign_vtable>::__eq___const(OrgContext* org_context, haxorg_TblfmAssign self, haxorg_TblfmAssign other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Tblfm::Assign::*)(org::sem::Tblfm::Assign const&) const>(&org::sem::Tblfm::Assign::operator==), org_context, self, other);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getBool_const(OrgContext* org_context, haxorg_AttrValue self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<bool>(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getBool), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getInt_const(OrgContext* org_context, haxorg_AttrValue self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<int>(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getInt), org_context, self);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getString_const(OrgContext* org_context, haxorg_AttrValue self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getString), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getDouble_const(OrgContext* org_context, haxorg_AttrValue self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<double>(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getDouble), org_context, self);
}
bool org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::__eq___const(OrgContext* org_context, haxorg_AttrValue self, haxorg_AttrValue other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::AttrValue::*)(org::sem::AttrValue const&) const>(&org::sem::AttrValue::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::isTextValue_const(OrgContext* org_context, haxorg_AttrValue self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::isTextValue), org_context, self);
}
haxorg_AttrValueTextValue org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getTextValueConst_const(OrgContext* org_context, haxorg_AttrValue self) {
  return org::bind::c::execute_cpp<haxorg_AttrValueTextValue, haxorg_AttrValueTextValue_vtable>(static_cast<org::sem::AttrValue::TextValue const&(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getTextValue), org_context, self);
}
haxorg_AttrValueTextValue org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getTextValueMut(OrgContext* org_context, haxorg_AttrValue self) {
  return org::bind::c::execute_cpp<haxorg_AttrValueTextValue, haxorg_AttrValueTextValue_vtable>(static_cast<org::sem::AttrValue::TextValue&(org::sem::AttrValue::*)()>(&org::sem::AttrValue::getTextValue), org_context, self);
}
bool org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::isFileReference_const(OrgContext* org_context, haxorg_AttrValue self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::isFileReference), org_context, self);
}
haxorg_AttrValueFileReference org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getFileReferenceConst_const(OrgContext* org_context, haxorg_AttrValue self) {
  return org::bind::c::execute_cpp<haxorg_AttrValueFileReference, haxorg_AttrValueFileReference_vtable>(static_cast<org::sem::AttrValue::FileReference const&(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getFileReference), org_context, self);
}
haxorg_AttrValueFileReference org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getFileReferenceMut(OrgContext* org_context, haxorg_AttrValue self) {
  return org::bind::c::execute_cpp<haxorg_AttrValueFileReference, haxorg_AttrValueFileReference_vtable>(static_cast<org::sem::AttrValue::FileReference&(org::sem::AttrValue::*)()>(&org::sem::AttrValue::getFileReference), org_context, self);
}
bool org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::isLispValue_const(OrgContext* org_context, haxorg_AttrValue self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::isLispValue), org_context, self);
}
haxorg_AttrValueLispValue org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getLispValueConst_const(OrgContext* org_context, haxorg_AttrValue self) {
  return org::bind::c::execute_cpp<haxorg_AttrValueLispValue, haxorg_AttrValueLispValue_vtable>(static_cast<org::sem::AttrValue::LispValue const&(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getLispValue), org_context, self);
}
haxorg_AttrValueLispValue org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getLispValueMut(OrgContext* org_context, haxorg_AttrValue self) {
  return org::bind::c::execute_cpp<haxorg_AttrValueLispValue, haxorg_AttrValueLispValue_vtable>(static_cast<org::sem::AttrValue::LispValue&(org::sem::AttrValue::*)()>(&org::sem::AttrValue::getLispValue), org_context, self);
}
haxorg_AttrValueKind org::bind::c::VTable<haxorg_AttrValue, haxorg_AttrValue_vtable>::getKind_const(OrgContext* org_context, haxorg_AttrValue self) {
  return org::bind::c::execute_cpp<haxorg_AttrValueKind, haxorg_builtin_vtable>(static_cast<org::sem::AttrValue::Kind(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getKind), org_context, self);
}
bool org::bind::c::VTable<haxorg_AttrValueDimensionSpan, haxorg_AttrValueDimensionSpan_vtable>::__eq___const(OrgContext* org_context, haxorg_AttrValueDimensionSpan self, haxorg_AttrValueDimensionSpan other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::AttrValue::DimensionSpan::*)(org::sem::AttrValue::DimensionSpan const&) const>(&org::sem::AttrValue::DimensionSpan::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_AttrValueTextValue, haxorg_AttrValueTextValue_vtable>::__eq___const(OrgContext* org_context, haxorg_AttrValueTextValue self, haxorg_AttrValueTextValue other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::AttrValue::TextValue::*)(org::sem::AttrValue::TextValue const&) const>(&org::sem::AttrValue::TextValue::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_AttrValueFileReference, haxorg_AttrValueFileReference_vtable>::__eq___const(OrgContext* org_context, haxorg_AttrValueFileReference self, haxorg_AttrValueFileReference other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::AttrValue::FileReference::*)(org::sem::AttrValue::FileReference const&) const>(&org::sem::AttrValue::FileReference::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_AttrValueLispValue, haxorg_AttrValueLispValue_vtable>::__eq___const(OrgContext* org_context, haxorg_AttrValueLispValue self, haxorg_AttrValueLispValue other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::AttrValue::LispValue::*)(org::sem::AttrValue::LispValue const&) const>(&org::sem::AttrValue::LispValue::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_HashTagFlat, haxorg_HashTagFlat_vtable>::__eq___const(OrgContext* org_context, haxorg_HashTagFlat self, haxorg_HashTagFlat other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::HashTagFlat::*)(org::sem::HashTagFlat const&) const>(&org::sem::HashTagFlat::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_HashTagFlat, haxorg_HashTagFlat_vtable>::__lt___const(OrgContext* org_context, haxorg_HashTagFlat self, haxorg_HashTagFlat other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::HashTagFlat::*)(org::sem::HashTagFlat const&) const>(&org::sem::HashTagFlat::operator<), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_TodoKeyword, haxorg_TodoKeyword_vtable>::__eq___const(OrgContext* org_context, haxorg_TodoKeyword self, haxorg_TodoKeyword other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::TodoKeyword::*)(org::sem::TodoKeyword const&) const>(&org::sem::TodoKeyword::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_HashTagText, haxorg_HashTagText_vtable>::__eq___const(OrgContext* org_context, haxorg_HashTagText self, haxorg_HashTagText other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::HashTagText::*)(org::sem::HashTagText const&) const>(&org::sem::HashTagText::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_HashTagText, haxorg_HashTagText_vtable>::prefixMatch_const(OrgContext* org_context, haxorg_HashTagText self, haxorg_HstdVec prefix) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::HashTagText::*)(hstd::Vec<hstd::Str> const&) const>(&org::sem::HashTagText::prefixMatch), org_context, self, prefix);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_HashTagText, haxorg_HashTagText_vtable>::getFlatHashes_const(OrgContext* org_context, haxorg_HashTagText self, bool withIntermediate) {
  return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<org::sem::HashTagFlat>(org::sem::HashTagText::*)(bool) const>(&org::sem::HashTagText::getFlatHashes), org_context, self, withIntermediate);
}
bool org::bind::c::VTable<haxorg_SubtreePath, haxorg_SubtreePath_vtable>::__eq___const(OrgContext* org_context, haxorg_SubtreePath self, haxorg_SubtreePath other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::SubtreePath::*)(org::sem::SubtreePath const&) const>(&org::sem::SubtreePath::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::__eq___const(OrgContext* org_context, haxorg_LinkTarget self, haxorg_LinkTarget other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LinkTarget::*)(org::sem::LinkTarget const&) const>(&org::sem::LinkTarget::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::isRaw_const(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isRaw), org_context, self);
}
haxorg_LinkTargetRaw org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getRawConst_const(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetRaw, haxorg_LinkTargetRaw_vtable>(static_cast<org::sem::LinkTarget::Raw const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getRaw), org_context, self);
}
haxorg_LinkTargetRaw org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getRawMut(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetRaw, haxorg_LinkTargetRaw_vtable>(static_cast<org::sem::LinkTarget::Raw&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getRaw), org_context, self);
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::isId_const(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isId), org_context, self);
}
haxorg_LinkTargetId org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getIdConst_const(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetId, haxorg_LinkTargetId_vtable>(static_cast<org::sem::LinkTarget::Id const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getId), org_context, self);
}
haxorg_LinkTargetId org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getIdMut(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetId, haxorg_LinkTargetId_vtable>(static_cast<org::sem::LinkTarget::Id&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getId), org_context, self);
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::isCustomId_const(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isCustomId), org_context, self);
}
haxorg_LinkTargetCustomId org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getCustomIdConst_const(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetCustomId, haxorg_LinkTargetCustomId_vtable>(static_cast<org::sem::LinkTarget::CustomId const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getCustomId), org_context, self);
}
haxorg_LinkTargetCustomId org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getCustomIdMut(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetCustomId, haxorg_LinkTargetCustomId_vtable>(static_cast<org::sem::LinkTarget::CustomId&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getCustomId), org_context, self);
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::isSubtreeTitle_const(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isSubtreeTitle), org_context, self);
}
haxorg_LinkTargetSubtreeTitle org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getSubtreeTitleConst_const(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetSubtreeTitle, haxorg_LinkTargetSubtreeTitle_vtable>(static_cast<org::sem::LinkTarget::SubtreeTitle const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getSubtreeTitle), org_context, self);
}
haxorg_LinkTargetSubtreeTitle org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getSubtreeTitleMut(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetSubtreeTitle, haxorg_LinkTargetSubtreeTitle_vtable>(static_cast<org::sem::LinkTarget::SubtreeTitle&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getSubtreeTitle), org_context, self);
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::isPerson_const(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isPerson), org_context, self);
}
haxorg_LinkTargetPerson org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getPersonConst_const(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetPerson, haxorg_LinkTargetPerson_vtable>(static_cast<org::sem::LinkTarget::Person const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getPerson), org_context, self);
}
haxorg_LinkTargetPerson org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getPersonMut(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetPerson, haxorg_LinkTargetPerson_vtable>(static_cast<org::sem::LinkTarget::Person&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getPerson), org_context, self);
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::isUserProtocol_const(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isUserProtocol), org_context, self);
}
haxorg_LinkTargetUserProtocol org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getUserProtocolConst_const(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetUserProtocol, haxorg_LinkTargetUserProtocol_vtable>(static_cast<org::sem::LinkTarget::UserProtocol const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getUserProtocol), org_context, self);
}
haxorg_LinkTargetUserProtocol org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getUserProtocolMut(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetUserProtocol, haxorg_LinkTargetUserProtocol_vtable>(static_cast<org::sem::LinkTarget::UserProtocol&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getUserProtocol), org_context, self);
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::isInternal_const(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isInternal), org_context, self);
}
haxorg_LinkTargetInternal org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getInternalConst_const(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetInternal, haxorg_LinkTargetInternal_vtable>(static_cast<org::sem::LinkTarget::Internal const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getInternal), org_context, self);
}
haxorg_LinkTargetInternal org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getInternalMut(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetInternal, haxorg_LinkTargetInternal_vtable>(static_cast<org::sem::LinkTarget::Internal&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getInternal), org_context, self);
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::isFootnote_const(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isFootnote), org_context, self);
}
haxorg_LinkTargetFootnote org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getFootnoteConst_const(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetFootnote, haxorg_LinkTargetFootnote_vtable>(static_cast<org::sem::LinkTarget::Footnote const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getFootnote), org_context, self);
}
haxorg_LinkTargetFootnote org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getFootnoteMut(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetFootnote, haxorg_LinkTargetFootnote_vtable>(static_cast<org::sem::LinkTarget::Footnote&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getFootnote), org_context, self);
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::isFile_const(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isFile), org_context, self);
}
haxorg_LinkTargetFile org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getFileConst_const(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetFile, haxorg_LinkTargetFile_vtable>(static_cast<org::sem::LinkTarget::File const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getFile), org_context, self);
}
haxorg_LinkTargetFile org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getFileMut(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetFile, haxorg_LinkTargetFile_vtable>(static_cast<org::sem::LinkTarget::File&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getFile), org_context, self);
}
bool org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::isAttachment_const(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isAttachment), org_context, self);
}
haxorg_LinkTargetAttachment org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getAttachmentConst_const(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetAttachment, haxorg_LinkTargetAttachment_vtable>(static_cast<org::sem::LinkTarget::Attachment const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getAttachment), org_context, self);
}
haxorg_LinkTargetAttachment org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getAttachmentMut(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetAttachment, haxorg_LinkTargetAttachment_vtable>(static_cast<org::sem::LinkTarget::Attachment&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getAttachment), org_context, self);
}
haxorg_LinkTargetKind org::bind::c::VTable<haxorg_LinkTarget, haxorg_LinkTarget_vtable>::getKind_const(OrgContext* org_context, haxorg_LinkTarget self) {
  return org::bind::c::execute_cpp<haxorg_LinkTargetKind, haxorg_builtin_vtable>(static_cast<org::sem::LinkTarget::Kind(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getKind), org_context, self);
}
bool org::bind::c::VTable<haxorg_LinkTargetRaw, haxorg_LinkTargetRaw_vtable>::__eq___const(OrgContext* org_context, haxorg_LinkTargetRaw self, haxorg_LinkTargetRaw other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LinkTarget::Raw::*)(org::sem::LinkTarget::Raw const&) const>(&org::sem::LinkTarget::Raw::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_LinkTargetId, haxorg_LinkTargetId_vtable>::__eq___const(OrgContext* org_context, haxorg_LinkTargetId self, haxorg_LinkTargetId other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LinkTarget::Id::*)(org::sem::LinkTarget::Id const&) const>(&org::sem::LinkTarget::Id::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_LinkTargetCustomId, haxorg_LinkTargetCustomId_vtable>::__eq___const(OrgContext* org_context, haxorg_LinkTargetCustomId self, haxorg_LinkTargetCustomId other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LinkTarget::CustomId::*)(org::sem::LinkTarget::CustomId const&) const>(&org::sem::LinkTarget::CustomId::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_LinkTargetSubtreeTitle, haxorg_LinkTargetSubtreeTitle_vtable>::__eq___const(OrgContext* org_context, haxorg_LinkTargetSubtreeTitle self, haxorg_LinkTargetSubtreeTitle other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LinkTarget::SubtreeTitle::*)(org::sem::LinkTarget::SubtreeTitle const&) const>(&org::sem::LinkTarget::SubtreeTitle::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_LinkTargetPerson, haxorg_LinkTargetPerson_vtable>::__eq___const(OrgContext* org_context, haxorg_LinkTargetPerson self, haxorg_LinkTargetPerson other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LinkTarget::Person::*)(org::sem::LinkTarget::Person const&) const>(&org::sem::LinkTarget::Person::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_LinkTargetUserProtocol, haxorg_LinkTargetUserProtocol_vtable>::__eq___const(OrgContext* org_context, haxorg_LinkTargetUserProtocol self, haxorg_LinkTargetUserProtocol other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LinkTarget::UserProtocol::*)(org::sem::LinkTarget::UserProtocol const&) const>(&org::sem::LinkTarget::UserProtocol::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_LinkTargetInternal, haxorg_LinkTargetInternal_vtable>::__eq___const(OrgContext* org_context, haxorg_LinkTargetInternal self, haxorg_LinkTargetInternal other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LinkTarget::Internal::*)(org::sem::LinkTarget::Internal const&) const>(&org::sem::LinkTarget::Internal::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_LinkTargetFootnote, haxorg_LinkTargetFootnote_vtable>::__eq___const(OrgContext* org_context, haxorg_LinkTargetFootnote self, haxorg_LinkTargetFootnote other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LinkTarget::Footnote::*)(org::sem::LinkTarget::Footnote const&) const>(&org::sem::LinkTarget::Footnote::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_LinkTargetFile, haxorg_LinkTargetFile_vtable>::__eq___const(OrgContext* org_context, haxorg_LinkTargetFile self, haxorg_LinkTargetFile other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LinkTarget::File::*)(org::sem::LinkTarget::File const&) const>(&org::sem::LinkTarget::File::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_LinkTargetAttachment, haxorg_LinkTargetAttachment_vtable>::__eq___const(OrgContext* org_context, haxorg_LinkTargetAttachment self, haxorg_LinkTargetAttachment other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::LinkTarget::Attachment::*)(org::sem::LinkTarget::Attachment const&) const>(&org::sem::LinkTarget::Attachment::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::__eq___const(OrgContext* org_context, haxorg_SubtreeLogHead self, haxorg_SubtreeLogHead other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::SubtreeLogHead::*)(org::sem::SubtreeLogHead const&) const>(&org::sem::SubtreeLogHead::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::isPriority_const(OrgContext* org_context, haxorg_SubtreeLogHead self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isPriority), org_context, self);
}
haxorg_SubtreeLogHeadPriority org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getPriorityConst_const(OrgContext* org_context, haxorg_SubtreeLogHead self) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadPriority, haxorg_SubtreeLogHeadPriority_vtable>(static_cast<org::sem::SubtreeLogHead::Priority const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getPriority), org_context, self);
}
haxorg_SubtreeLogHeadPriority org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getPriorityMut(OrgContext* org_context, haxorg_SubtreeLogHead self) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadPriority, haxorg_SubtreeLogHeadPriority_vtable>(static_cast<org::sem::SubtreeLogHead::Priority&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getPriority), org_context, self);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::isNote_const(OrgContext* org_context, haxorg_SubtreeLogHead self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isNote), org_context, self);
}
haxorg_SubtreeLogHeadNote org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getNoteConst_const(OrgContext* org_context, haxorg_SubtreeLogHead self) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadNote, haxorg_SubtreeLogHeadNote_vtable>(static_cast<org::sem::SubtreeLogHead::Note const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getNote), org_context, self);
}
haxorg_SubtreeLogHeadNote org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getNoteMut(OrgContext* org_context, haxorg_SubtreeLogHead self) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadNote, haxorg_SubtreeLogHeadNote_vtable>(static_cast<org::sem::SubtreeLogHead::Note&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getNote), org_context, self);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::isRefile_const(OrgContext* org_context, haxorg_SubtreeLogHead self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isRefile), org_context, self);
}
haxorg_SubtreeLogHeadRefile org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getRefileConst_const(OrgContext* org_context, haxorg_SubtreeLogHead self) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadRefile, haxorg_SubtreeLogHeadRefile_vtable>(static_cast<org::sem::SubtreeLogHead::Refile const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getRefile), org_context, self);
}
haxorg_SubtreeLogHeadRefile org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getRefileMut(OrgContext* org_context, haxorg_SubtreeLogHead self) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadRefile, haxorg_SubtreeLogHeadRefile_vtable>(static_cast<org::sem::SubtreeLogHead::Refile&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getRefile), org_context, self);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::isClock_const(OrgContext* org_context, haxorg_SubtreeLogHead self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isClock), org_context, self);
}
haxorg_SubtreeLogHeadClock org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getClockConst_const(OrgContext* org_context, haxorg_SubtreeLogHead self) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadClock, haxorg_SubtreeLogHeadClock_vtable>(static_cast<org::sem::SubtreeLogHead::Clock const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getClock), org_context, self);
}
haxorg_SubtreeLogHeadClock org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getClockMut(OrgContext* org_context, haxorg_SubtreeLogHead self) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadClock, haxorg_SubtreeLogHeadClock_vtable>(static_cast<org::sem::SubtreeLogHead::Clock&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getClock), org_context, self);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::isState_const(OrgContext* org_context, haxorg_SubtreeLogHead self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isState), org_context, self);
}
haxorg_SubtreeLogHeadState org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getStateConst_const(OrgContext* org_context, haxorg_SubtreeLogHead self) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadState, haxorg_SubtreeLogHeadState_vtable>(static_cast<org::sem::SubtreeLogHead::State const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getState), org_context, self);
}
haxorg_SubtreeLogHeadState org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getStateMut(OrgContext* org_context, haxorg_SubtreeLogHead self) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadState, haxorg_SubtreeLogHeadState_vtable>(static_cast<org::sem::SubtreeLogHead::State&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getState), org_context, self);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::isDeadline_const(OrgContext* org_context, haxorg_SubtreeLogHead self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isDeadline), org_context, self);
}
haxorg_SubtreeLogHeadDeadline org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getDeadlineConst_const(OrgContext* org_context, haxorg_SubtreeLogHead self) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadDeadline, haxorg_SubtreeLogHeadDeadline_vtable>(static_cast<org::sem::SubtreeLogHead::Deadline const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getDeadline), org_context, self);
}
haxorg_SubtreeLogHeadDeadline org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getDeadlineMut(OrgContext* org_context, haxorg_SubtreeLogHead self) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadDeadline, haxorg_SubtreeLogHeadDeadline_vtable>(static_cast<org::sem::SubtreeLogHead::Deadline&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getDeadline), org_context, self);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::isSchedule_const(OrgContext* org_context, haxorg_SubtreeLogHead self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isSchedule), org_context, self);
}
haxorg_SubtreeLogHeadSchedule org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getScheduleConst_const(OrgContext* org_context, haxorg_SubtreeLogHead self) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadSchedule, haxorg_SubtreeLogHeadSchedule_vtable>(static_cast<org::sem::SubtreeLogHead::Schedule const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getSchedule), org_context, self);
}
haxorg_SubtreeLogHeadSchedule org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getScheduleMut(OrgContext* org_context, haxorg_SubtreeLogHead self) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadSchedule, haxorg_SubtreeLogHeadSchedule_vtable>(static_cast<org::sem::SubtreeLogHead::Schedule&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getSchedule), org_context, self);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::isTag_const(OrgContext* org_context, haxorg_SubtreeLogHead self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isTag), org_context, self);
}
haxorg_SubtreeLogHeadTag org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getTagConst_const(OrgContext* org_context, haxorg_SubtreeLogHead self) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadTag, haxorg_SubtreeLogHeadTag_vtable>(static_cast<org::sem::SubtreeLogHead::Tag const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getTag), org_context, self);
}
haxorg_SubtreeLogHeadTag org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getTagMut(OrgContext* org_context, haxorg_SubtreeLogHead self) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadTag, haxorg_SubtreeLogHeadTag_vtable>(static_cast<org::sem::SubtreeLogHead::Tag&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getTag), org_context, self);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::isUnknown_const(OrgContext* org_context, haxorg_SubtreeLogHead self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isUnknown), org_context, self);
}
haxorg_SubtreeLogHeadUnknown org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getUnknownConst_const(OrgContext* org_context, haxorg_SubtreeLogHead self) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadUnknown, haxorg_SubtreeLogHeadUnknown_vtable>(static_cast<org::sem::SubtreeLogHead::Unknown const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getUnknown), org_context, self);
}
haxorg_SubtreeLogHeadUnknown org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getUnknownMut(OrgContext* org_context, haxorg_SubtreeLogHead self) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadUnknown, haxorg_SubtreeLogHeadUnknown_vtable>(static_cast<org::sem::SubtreeLogHead::Unknown&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getUnknown), org_context, self);
}
haxorg_SubtreeLogHeadKind org::bind::c::VTable<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>::getLogKind_const(OrgContext* org_context, haxorg_SubtreeLogHead self) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadKind, haxorg_builtin_vtable>(static_cast<org::sem::SubtreeLogHead::Kind(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getLogKind), org_context, self);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHeadPriority, haxorg_SubtreeLogHeadPriority_vtable>::__eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadPriority self, haxorg_SubtreeLogHeadPriority other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::SubtreeLogHead::Priority::*)(org::sem::SubtreeLogHead::Priority const&) const>(&org::sem::SubtreeLogHead::Priority::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHeadNote, haxorg_SubtreeLogHeadNote_vtable>::__eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadNote self, haxorg_SubtreeLogHeadNote other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::SubtreeLogHead::Note::*)(org::sem::SubtreeLogHead::Note const&) const>(&org::sem::SubtreeLogHead::Note::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHeadRefile, haxorg_SubtreeLogHeadRefile_vtable>::__eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadRefile self, haxorg_SubtreeLogHeadRefile other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::SubtreeLogHead::Refile::*)(org::sem::SubtreeLogHead::Refile const&) const>(&org::sem::SubtreeLogHead::Refile::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHeadClock, haxorg_SubtreeLogHeadClock_vtable>::__eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadClock self, haxorg_SubtreeLogHeadClock other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::SubtreeLogHead::Clock::*)(org::sem::SubtreeLogHead::Clock const&) const>(&org::sem::SubtreeLogHead::Clock::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHeadState, haxorg_SubtreeLogHeadState_vtable>::__eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadState self, haxorg_SubtreeLogHeadState other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::SubtreeLogHead::State::*)(org::sem::SubtreeLogHead::State const&) const>(&org::sem::SubtreeLogHead::State::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHeadDeadline, haxorg_SubtreeLogHeadDeadline_vtable>::__eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadDeadline self, haxorg_SubtreeLogHeadDeadline other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::SubtreeLogHead::Deadline::*)(org::sem::SubtreeLogHead::Deadline const&) const>(&org::sem::SubtreeLogHead::Deadline::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHeadSchedule, haxorg_SubtreeLogHeadSchedule_vtable>::__eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadSchedule self, haxorg_SubtreeLogHeadSchedule other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::SubtreeLogHead::Schedule::*)(org::sem::SubtreeLogHead::Schedule const&) const>(&org::sem::SubtreeLogHead::Schedule::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHeadTag, haxorg_SubtreeLogHeadTag_vtable>::__eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadTag self, haxorg_SubtreeLogHeadTag other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::SubtreeLogHead::Tag::*)(org::sem::SubtreeLogHead::Tag const&) const>(&org::sem::SubtreeLogHead::Tag::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_SubtreeLogHeadUnknown, haxorg_SubtreeLogHeadUnknown_vtable>::__eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadUnknown self, haxorg_SubtreeLogHeadUnknown other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::SubtreeLogHead::Unknown::*)(org::sem::SubtreeLogHead::Unknown const&) const>(&org::sem::SubtreeLogHead::Unknown::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_SubtreeCompletion, haxorg_SubtreeCompletion_vtable>::__eq___const(OrgContext* org_context, haxorg_SubtreeCompletion self, haxorg_SubtreeCompletion other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::SubtreeCompletion::*)(org::sem::SubtreeCompletion const&) const>(&org::sem::SubtreeCompletion::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_AttrList, haxorg_AttrList_vtable>::__eq___const(OrgContext* org_context, haxorg_AttrList self, haxorg_AttrList other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::AttrList::*)(org::sem::AttrList const&) const>(&org::sem::AttrList::operator==), org_context, self, other);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::getFlatArgs_const(OrgContext* org_context, haxorg_AttrGroup self) {
  return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getFlatArgs), org_context, self);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::getAttrs_const(OrgContext* org_context, haxorg_AttrGroup self, haxorg_HstdOpt key) {
  return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::AttrGroup::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::AttrGroup::getAttrs), org_context, self, key);
}
void org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::setNamedAttr(OrgContext* org_context, haxorg_AttrGroup self, haxorg_HstdStr key, haxorg_HstdVec attrs) {
  return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(static_cast<void(org::sem::AttrGroup::*)(hstd::Str const&, hstd::Vec<org::sem::AttrValue> const&)>(&org::sem::AttrGroup::setNamedAttr), org_context, self, key, attrs);
}
void org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::setPositionalAttr(OrgContext* org_context, haxorg_AttrGroup self, haxorg_HstdVec items) {
  return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(static_cast<void(org::sem::AttrGroup::*)(hstd::Vec<org::sem::AttrValue> const&)>(&org::sem::AttrGroup::setPositionalAttr), org_context, self, items);
}
int org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::getPositionalSize_const(OrgContext* org_context, haxorg_AttrGroup self) {
  return org::bind::c::execute_cpp<int, haxorg_builtin_vtable>(static_cast<int(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getPositionalSize), org_context, self);
}
int org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::getNamedSize_const(OrgContext* org_context, haxorg_AttrGroup self) {
  return org::bind::c::execute_cpp<int, haxorg_builtin_vtable>(static_cast<int(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getNamedSize), org_context, self);
}
bool org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::isEmpty_const(OrgContext* org_context, haxorg_AttrGroup self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::isEmpty), org_context, self);
}
haxorg_AttrList org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::getAll_const(OrgContext* org_context, haxorg_AttrGroup self) {
  return org::bind::c::execute_cpp<haxorg_AttrList, haxorg_AttrList_vtable>(static_cast<org::sem::AttrList(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getAll), org_context, self);
}
haxorg_AttrValue org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::atPositional_const(OrgContext* org_context, haxorg_AttrGroup self, int index) {
  return org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<org::sem::AttrValue const&(org::sem::AttrGroup::*)(int) const>(&org::sem::AttrGroup::atPositional), org_context, self, index);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::getPositional_const(OrgContext* org_context, haxorg_AttrGroup self, int index) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::AttrGroup::*)(int) const>(&org::sem::AttrGroup::getPositional), org_context, self, index);
}
haxorg_AttrList org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::atNamed_const(OrgContext* org_context, haxorg_AttrGroup self, haxorg_HstdStr index) {
  return org::bind::c::execute_cpp<haxorg_AttrList, haxorg_AttrList_vtable>(static_cast<org::sem::AttrList const&(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atNamed), org_context, self, index);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::getNamed_const(OrgContext* org_context, haxorg_AttrGroup self, haxorg_HstdStr index) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<org::sem::AttrList>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getNamed), org_context, self, index);
}
haxorg_AttrValue org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::atFirstNamed_const(OrgContext* org_context, haxorg_AttrGroup self, haxorg_HstdStr index) {
  return org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<org::sem::AttrValue const&(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atFirstNamed), org_context, self, index);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::getFirstNamed_const(OrgContext* org_context, haxorg_AttrGroup self, haxorg_HstdStr index) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getFirstNamed), org_context, self, index);
}
haxorg_AttrList org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::atVarNamed_const(OrgContext* org_context, haxorg_AttrGroup self, haxorg_HstdStr index) {
  return org::bind::c::execute_cpp<haxorg_AttrList, haxorg_AttrList_vtable>(static_cast<org::sem::AttrList(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atVarNamed), org_context, self, index);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::getVarNamed_const(OrgContext* org_context, haxorg_AttrGroup self, haxorg_HstdStr index) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<org::sem::AttrList>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getVarNamed), org_context, self, index);
}
haxorg_AttrValue org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::atFirstVarNamed_const(OrgContext* org_context, haxorg_AttrGroup self, haxorg_HstdStr index) {
  return org::bind::c::execute_cpp<haxorg_AttrValue, haxorg_AttrValue_vtable>(static_cast<org::sem::AttrValue(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atFirstVarNamed), org_context, self, index);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::getFirstVarNamed_const(OrgContext* org_context, haxorg_AttrGroup self, haxorg_HstdStr index) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getFirstVarNamed), org_context, self, index);
}
bool org::bind::c::VTable<haxorg_AttrGroup, haxorg_AttrGroup_vtable>::__eq___const(OrgContext* org_context, haxorg_AttrGroup self, haxorg_AttrGroup other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::AttrGroup::*)(org::sem::AttrGroup const&) const>(&org::sem::AttrGroup::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_OrgCodeEvalInput, haxorg_OrgCodeEvalInput_vtable>::__eq___const(OrgContext* org_context, haxorg_OrgCodeEvalInput self, haxorg_OrgCodeEvalInput other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::OrgCodeEvalInput::*)(org::sem::OrgCodeEvalInput const&) const>(&org::sem::OrgCodeEvalInput::operator==), org_context, self, other);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_OrgCodeEvalInput, haxorg_OrgCodeEvalInput_vtable>::getVariable_const(OrgContext* org_context, haxorg_OrgCodeEvalInput self, haxorg_HstdStr name) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<org::sem::OrgCodeEvalInput::Var>(org::sem::OrgCodeEvalInput::*)(hstd::Str const&) const>(&org::sem::OrgCodeEvalInput::getVariable), org_context, self, name);
}
bool org::bind::c::VTable<haxorg_OrgCodeEvalInputVar, haxorg_OrgCodeEvalInputVar_vtable>::__eq___const(OrgContext* org_context, haxorg_OrgCodeEvalInputVar self, haxorg_OrgCodeEvalInputVar other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::OrgCodeEvalInput::Var::*)(org::sem::OrgCodeEvalInput::Var const&) const>(&org::sem::OrgCodeEvalInput::Var::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_OrgCodeEvalOutput, haxorg_OrgCodeEvalOutput_vtable>::__eq___const(OrgContext* org_context, haxorg_OrgCodeEvalOutput self, haxorg_OrgCodeEvalOutput other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::OrgCodeEvalOutput::*)(org::sem::OrgCodeEvalOutput const&) const>(&org::sem::OrgCodeEvalOutput::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ColumnView, haxorg_ColumnView_vtable>::__eq___const(OrgContext* org_context, haxorg_ColumnView self, haxorg_ColumnView other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::ColumnView::*)(org::sem::ColumnView const&) const>(&org::sem::ColumnView::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>::__eq___const(OrgContext* org_context, haxorg_ColumnViewSummary self, haxorg_ColumnViewSummary other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::ColumnView::Summary::*)(org::sem::ColumnView::Summary const&) const>(&org::sem::ColumnView::Summary::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>::isCheckboxAggregate_const(OrgContext* org_context, haxorg_ColumnViewSummary self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::isCheckboxAggregate), org_context, self);
}
haxorg_ColumnViewSummaryCheckboxAggregate org::bind::c::VTable<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>::getCheckboxAggregateConst_const(OrgContext* org_context, haxorg_ColumnViewSummary self) {
  return org::bind::c::execute_cpp<haxorg_ColumnViewSummaryCheckboxAggregate, haxorg_ColumnViewSummaryCheckboxAggregate_vtable>(static_cast<org::sem::ColumnView::Summary::CheckboxAggregate const&(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::getCheckboxAggregate), org_context, self);
}
haxorg_ColumnViewSummaryCheckboxAggregate org::bind::c::VTable<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>::getCheckboxAggregateMut(OrgContext* org_context, haxorg_ColumnViewSummary self) {
  return org::bind::c::execute_cpp<haxorg_ColumnViewSummaryCheckboxAggregate, haxorg_ColumnViewSummaryCheckboxAggregate_vtable>(static_cast<org::sem::ColumnView::Summary::CheckboxAggregate&(org::sem::ColumnView::Summary::*)()>(&org::sem::ColumnView::Summary::getCheckboxAggregate), org_context, self);
}
bool org::bind::c::VTable<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>::isMathAggregate_const(OrgContext* org_context, haxorg_ColumnViewSummary self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::isMathAggregate), org_context, self);
}
haxorg_ColumnViewSummaryMathAggregate org::bind::c::VTable<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>::getMathAggregateConst_const(OrgContext* org_context, haxorg_ColumnViewSummary self) {
  return org::bind::c::execute_cpp<haxorg_ColumnViewSummaryMathAggregate, haxorg_ColumnViewSummaryMathAggregate_vtable>(static_cast<org::sem::ColumnView::Summary::MathAggregate const&(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::getMathAggregate), org_context, self);
}
haxorg_ColumnViewSummaryMathAggregate org::bind::c::VTable<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>::getMathAggregateMut(OrgContext* org_context, haxorg_ColumnViewSummary self) {
  return org::bind::c::execute_cpp<haxorg_ColumnViewSummaryMathAggregate, haxorg_ColumnViewSummaryMathAggregate_vtable>(static_cast<org::sem::ColumnView::Summary::MathAggregate&(org::sem::ColumnView::Summary::*)()>(&org::sem::ColumnView::Summary::getMathAggregate), org_context, self);
}
haxorg_ColumnViewSummaryKind org::bind::c::VTable<haxorg_ColumnViewSummary, haxorg_ColumnViewSummary_vtable>::getKind_const(OrgContext* org_context, haxorg_ColumnViewSummary self) {
  return org::bind::c::execute_cpp<haxorg_ColumnViewSummaryKind, haxorg_builtin_vtable>(static_cast<org::sem::ColumnView::Summary::Kind(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::getKind), org_context, self);
}
bool org::bind::c::VTable<haxorg_ColumnViewSummaryCheckboxAggregate, haxorg_ColumnViewSummaryCheckboxAggregate_vtable>::__eq___const(OrgContext* org_context, haxorg_ColumnViewSummaryCheckboxAggregate self, haxorg_ColumnViewSummaryCheckboxAggregate other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::ColumnView::Summary::CheckboxAggregate::*)(org::sem::ColumnView::Summary::CheckboxAggregate const&) const>(&org::sem::ColumnView::Summary::CheckboxAggregate::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ColumnViewSummaryMathAggregate, haxorg_ColumnViewSummaryMathAggregate_vtable>::__eq___const(OrgContext* org_context, haxorg_ColumnViewSummaryMathAggregate self, haxorg_ColumnViewSummaryMathAggregate other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::ColumnView::Summary::MathAggregate::*)(org::sem::ColumnView::Summary::MathAggregate const&) const>(&org::sem::ColumnView::Summary::MathAggregate::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ColumnViewColumn, haxorg_ColumnViewColumn_vtable>::__eq___const(OrgContext* org_context, haxorg_ColumnViewColumn self, haxorg_ColumnViewColumn other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::ColumnView::Column::*)(org::sem::ColumnView::Column const&) const>(&org::sem::ColumnView::Column::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_BlockCodeLine, haxorg_BlockCodeLine_vtable>::__eq___const(OrgContext* org_context, haxorg_BlockCodeLine self, haxorg_BlockCodeLine other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::BlockCodeLine::*)(org::sem::BlockCodeLine const&) const>(&org::sem::BlockCodeLine::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::__eq___const(OrgContext* org_context, haxorg_BlockCodeLinePart self, haxorg_BlockCodeLinePart other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::BlockCodeLine::Part::*)(org::sem::BlockCodeLine::Part const&) const>(&org::sem::BlockCodeLine::Part::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::isRaw_const(OrgContext* org_context, haxorg_BlockCodeLinePart self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::isRaw), org_context, self);
}
haxorg_BlockCodeLinePartRaw org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::getRawConst_const(OrgContext* org_context, haxorg_BlockCodeLinePart self) {
  return org::bind::c::execute_cpp<haxorg_BlockCodeLinePartRaw, haxorg_BlockCodeLinePartRaw_vtable>(static_cast<org::sem::BlockCodeLine::Part::Raw const&(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::getRaw), org_context, self);
}
haxorg_BlockCodeLinePartRaw org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::getRawMut(OrgContext* org_context, haxorg_BlockCodeLinePart self) {
  return org::bind::c::execute_cpp<haxorg_BlockCodeLinePartRaw, haxorg_BlockCodeLinePartRaw_vtable>(static_cast<org::sem::BlockCodeLine::Part::Raw&(org::sem::BlockCodeLine::Part::*)()>(&org::sem::BlockCodeLine::Part::getRaw), org_context, self);
}
bool org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::isCallout_const(OrgContext* org_context, haxorg_BlockCodeLinePart self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::isCallout), org_context, self);
}
haxorg_BlockCodeLinePartCallout org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::getCalloutConst_const(OrgContext* org_context, haxorg_BlockCodeLinePart self) {
  return org::bind::c::execute_cpp<haxorg_BlockCodeLinePartCallout, haxorg_BlockCodeLinePartCallout_vtable>(static_cast<org::sem::BlockCodeLine::Part::Callout const&(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::getCallout), org_context, self);
}
haxorg_BlockCodeLinePartCallout org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::getCalloutMut(OrgContext* org_context, haxorg_BlockCodeLinePart self) {
  return org::bind::c::execute_cpp<haxorg_BlockCodeLinePartCallout, haxorg_BlockCodeLinePartCallout_vtable>(static_cast<org::sem::BlockCodeLine::Part::Callout&(org::sem::BlockCodeLine::Part::*)()>(&org::sem::BlockCodeLine::Part::getCallout), org_context, self);
}
bool org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::isTangle_const(OrgContext* org_context, haxorg_BlockCodeLinePart self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::isTangle), org_context, self);
}
haxorg_BlockCodeLinePartTangle org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::getTangleConst_const(OrgContext* org_context, haxorg_BlockCodeLinePart self) {
  return org::bind::c::execute_cpp<haxorg_BlockCodeLinePartTangle, haxorg_BlockCodeLinePartTangle_vtable>(static_cast<org::sem::BlockCodeLine::Part::Tangle const&(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::getTangle), org_context, self);
}
haxorg_BlockCodeLinePartTangle org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::getTangleMut(OrgContext* org_context, haxorg_BlockCodeLinePart self) {
  return org::bind::c::execute_cpp<haxorg_BlockCodeLinePartTangle, haxorg_BlockCodeLinePartTangle_vtable>(static_cast<org::sem::BlockCodeLine::Part::Tangle&(org::sem::BlockCodeLine::Part::*)()>(&org::sem::BlockCodeLine::Part::getTangle), org_context, self);
}
haxorg_BlockCodeLinePartKind org::bind::c::VTable<haxorg_BlockCodeLinePart, haxorg_BlockCodeLinePart_vtable>::getKind_const(OrgContext* org_context, haxorg_BlockCodeLinePart self) {
  return org::bind::c::execute_cpp<haxorg_BlockCodeLinePartKind, haxorg_builtin_vtable>(static_cast<org::sem::BlockCodeLine::Part::Kind(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::getKind), org_context, self);
}
bool org::bind::c::VTable<haxorg_BlockCodeLinePartRaw, haxorg_BlockCodeLinePartRaw_vtable>::__eq___const(OrgContext* org_context, haxorg_BlockCodeLinePartRaw self, haxorg_BlockCodeLinePartRaw other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::BlockCodeLine::Part::Raw::*)(org::sem::BlockCodeLine::Part::Raw const&) const>(&org::sem::BlockCodeLine::Part::Raw::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_BlockCodeLinePartCallout, haxorg_BlockCodeLinePartCallout_vtable>::__eq___const(OrgContext* org_context, haxorg_BlockCodeLinePartCallout self, haxorg_BlockCodeLinePartCallout other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::BlockCodeLine::Part::Callout::*)(org::sem::BlockCodeLine::Part::Callout const&) const>(&org::sem::BlockCodeLine::Part::Callout::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_BlockCodeLinePartTangle, haxorg_BlockCodeLinePartTangle_vtable>::__eq___const(OrgContext* org_context, haxorg_BlockCodeLinePartTangle self, haxorg_BlockCodeLinePartTangle other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::BlockCodeLine::Part::Tangle::*)(org::sem::BlockCodeLine::Part::Tangle const&) const>(&org::sem::BlockCodeLine::Part::Tangle::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>::__eq___const(OrgContext* org_context, haxorg_DocumentExportConfig self, haxorg_DocumentExportConfig other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::DocumentExportConfig::*)(org::sem::DocumentExportConfig const&) const>(&org::sem::DocumentExportConfig::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>::isDoExport_const(OrgContext* org_context, haxorg_DocumentExportConfig self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::isDoExport), org_context, self);
}
haxorg_DocumentExportConfigDoExport org::bind::c::VTable<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>::getDoExportConst_const(OrgContext* org_context, haxorg_DocumentExportConfig self) {
  return org::bind::c::execute_cpp<haxorg_DocumentExportConfigDoExport, haxorg_DocumentExportConfigDoExport_vtable>(static_cast<org::sem::DocumentExportConfig::DoExport const&(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::getDoExport), org_context, self);
}
haxorg_DocumentExportConfigDoExport org::bind::c::VTable<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>::getDoExportMut(OrgContext* org_context, haxorg_DocumentExportConfig self) {
  return org::bind::c::execute_cpp<haxorg_DocumentExportConfigDoExport, haxorg_DocumentExportConfigDoExport_vtable>(static_cast<org::sem::DocumentExportConfig::DoExport&(org::sem::DocumentExportConfig::*)()>(&org::sem::DocumentExportConfig::getDoExport), org_context, self);
}
bool org::bind::c::VTable<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>::isExportFixed_const(OrgContext* org_context, haxorg_DocumentExportConfig self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::isExportFixed), org_context, self);
}
haxorg_DocumentExportConfigExportFixed org::bind::c::VTable<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>::getExportFixedConst_const(OrgContext* org_context, haxorg_DocumentExportConfig self) {
  return org::bind::c::execute_cpp<haxorg_DocumentExportConfigExportFixed, haxorg_DocumentExportConfigExportFixed_vtable>(static_cast<org::sem::DocumentExportConfig::ExportFixed const&(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::getExportFixed), org_context, self);
}
haxorg_DocumentExportConfigExportFixed org::bind::c::VTable<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>::getExportFixedMut(OrgContext* org_context, haxorg_DocumentExportConfig self) {
  return org::bind::c::execute_cpp<haxorg_DocumentExportConfigExportFixed, haxorg_DocumentExportConfigExportFixed_vtable>(static_cast<org::sem::DocumentExportConfig::ExportFixed&(org::sem::DocumentExportConfig::*)()>(&org::sem::DocumentExportConfig::getExportFixed), org_context, self);
}
haxorg_DocumentExportConfigTocExportKind org::bind::c::VTable<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>::getTocExportKind_const(OrgContext* org_context, haxorg_DocumentExportConfig self) {
  return org::bind::c::execute_cpp<haxorg_DocumentExportConfigTocExportKind, haxorg_builtin_vtable>(static_cast<org::sem::DocumentExportConfig::TocExportKind(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::getTocExportKind), org_context, self);
}
bool org::bind::c::VTable<haxorg_DocumentExportConfigTaskExport, haxorg_DocumentExportConfigTaskExport_vtable>::__eq___const(OrgContext* org_context, haxorg_DocumentExportConfigTaskExport self, haxorg_DocumentExportConfigTaskExport other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::DocumentExportConfig::TaskExport::*)(org::sem::DocumentExportConfig::TaskExport const&) const>(&org::sem::DocumentExportConfig::TaskExport::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_DocumentExportConfigDoExport, haxorg_DocumentExportConfigDoExport_vtable>::__eq___const(OrgContext* org_context, haxorg_DocumentExportConfigDoExport self, haxorg_DocumentExportConfigDoExport other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::DocumentExportConfig::DoExport::*)(org::sem::DocumentExportConfig::DoExport const&) const>(&org::sem::DocumentExportConfig::DoExport::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_DocumentExportConfigExportFixed, haxorg_DocumentExportConfigExportFixed_vtable>::__eq___const(OrgContext* org_context, haxorg_DocumentExportConfigExportFixed self, haxorg_DocumentExportConfigExportFixed other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::DocumentExportConfig::ExportFixed::*)(org::sem::DocumentExportConfig::ExportFixed const&) const>(&org::sem::DocumentExportConfig::ExportFixed::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_SubtreePeriod, haxorg_SubtreePeriod_vtable>::__eq___const(OrgContext* org_context, haxorg_SubtreePeriod self, haxorg_SubtreePeriod other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::SubtreePeriod::*)(org::sem::SubtreePeriod const&) const>(&org::sem::SubtreePeriod::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isMatching_const(OrgContext* org_context, haxorg_NamedProperty self, haxorg_HstdStr kind, haxorg_HstdOpt subKind) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::NamedProperty::isMatching), org_context, self, kind, subKind);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getName_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getName), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getSubKind_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<hstd::Str>(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getSubKind), org_context, self);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::__eq___const(OrgContext* org_context, haxorg_NamedProperty self, haxorg_NamedProperty other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::*)(org::sem::NamedProperty const&) const>(&org::sem::NamedProperty::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isNonblocking_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isNonblocking), org_context, self);
}
haxorg_NamedPropertyNonblocking org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getNonblockingConst_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyNonblocking, haxorg_NamedPropertyNonblocking_vtable>(static_cast<org::sem::NamedProperty::Nonblocking const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getNonblocking), org_context, self);
}
haxorg_NamedPropertyNonblocking org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getNonblockingMut(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyNonblocking, haxorg_NamedPropertyNonblocking_vtable>(static_cast<org::sem::NamedProperty::Nonblocking&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getNonblocking), org_context, self);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isArchiveTime_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveTime), org_context, self);
}
haxorg_NamedPropertyArchiveTime org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveTimeConst_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveTime, haxorg_NamedPropertyArchiveTime_vtable>(static_cast<org::sem::NamedProperty::ArchiveTime const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveTime), org_context, self);
}
haxorg_NamedPropertyArchiveTime org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveTimeMut(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveTime, haxorg_NamedPropertyArchiveTime_vtable>(static_cast<org::sem::NamedProperty::ArchiveTime&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveTime), org_context, self);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isArchiveFile_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveFile), org_context, self);
}
haxorg_NamedPropertyArchiveFile org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveFileConst_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveFile, haxorg_NamedPropertyArchiveFile_vtable>(static_cast<org::sem::NamedProperty::ArchiveFile const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveFile), org_context, self);
}
haxorg_NamedPropertyArchiveFile org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveFileMut(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveFile, haxorg_NamedPropertyArchiveFile_vtable>(static_cast<org::sem::NamedProperty::ArchiveFile&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveFile), org_context, self);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isArchiveOlpath_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveOlpath), org_context, self);
}
haxorg_NamedPropertyArchiveOlpath org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveOlpathConst_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveOlpath, haxorg_NamedPropertyArchiveOlpath_vtable>(static_cast<org::sem::NamedProperty::ArchiveOlpath const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveOlpath), org_context, self);
}
haxorg_NamedPropertyArchiveOlpath org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveOlpathMut(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveOlpath, haxorg_NamedPropertyArchiveOlpath_vtable>(static_cast<org::sem::NamedProperty::ArchiveOlpath&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveOlpath), org_context, self);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isArchiveTarget_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveTarget), org_context, self);
}
haxorg_NamedPropertyArchiveTarget org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveTargetConst_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveTarget, haxorg_NamedPropertyArchiveTarget_vtable>(static_cast<org::sem::NamedProperty::ArchiveTarget const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveTarget), org_context, self);
}
haxorg_NamedPropertyArchiveTarget org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveTargetMut(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveTarget, haxorg_NamedPropertyArchiveTarget_vtable>(static_cast<org::sem::NamedProperty::ArchiveTarget&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveTarget), org_context, self);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isArchiveCategory_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveCategory), org_context, self);
}
haxorg_NamedPropertyArchiveCategory org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveCategoryConst_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveCategory, haxorg_NamedPropertyArchiveCategory_vtable>(static_cast<org::sem::NamedProperty::ArchiveCategory const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveCategory), org_context, self);
}
haxorg_NamedPropertyArchiveCategory org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveCategoryMut(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveCategory, haxorg_NamedPropertyArchiveCategory_vtable>(static_cast<org::sem::NamedProperty::ArchiveCategory&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveCategory), org_context, self);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isArchiveTodo_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveTodo), org_context, self);
}
haxorg_NamedPropertyArchiveTodo org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveTodoConst_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveTodo, haxorg_NamedPropertyArchiveTodo_vtable>(static_cast<org::sem::NamedProperty::ArchiveTodo const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveTodo), org_context, self);
}
haxorg_NamedPropertyArchiveTodo org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getArchiveTodoMut(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveTodo, haxorg_NamedPropertyArchiveTodo_vtable>(static_cast<org::sem::NamedProperty::ArchiveTodo&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveTodo), org_context, self);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isTrigger_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isTrigger), org_context, self);
}
haxorg_NamedPropertyTrigger org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getTriggerConst_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyTrigger, haxorg_NamedPropertyTrigger_vtable>(static_cast<org::sem::NamedProperty::Trigger const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getTrigger), org_context, self);
}
haxorg_NamedPropertyTrigger org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getTriggerMut(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyTrigger, haxorg_NamedPropertyTrigger_vtable>(static_cast<org::sem::NamedProperty::Trigger&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getTrigger), org_context, self);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isExportLatexClass_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexClass), org_context, self);
}
haxorg_NamedPropertyExportLatexClass org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getExportLatexClassConst_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexClass, haxorg_NamedPropertyExportLatexClass_vtable>(static_cast<org::sem::NamedProperty::ExportLatexClass const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getExportLatexClass), org_context, self);
}
haxorg_NamedPropertyExportLatexClass org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getExportLatexClassMut(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexClass, haxorg_NamedPropertyExportLatexClass_vtable>(static_cast<org::sem::NamedProperty::ExportLatexClass&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexClass), org_context, self);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isCookieData_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCookieData), org_context, self);
}
haxorg_NamedPropertyCookieData org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCookieDataConst_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyCookieData, haxorg_NamedPropertyCookieData_vtable>(static_cast<org::sem::NamedProperty::CookieData const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCookieData), org_context, self);
}
haxorg_NamedPropertyCookieData org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCookieDataMut(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyCookieData, haxorg_NamedPropertyCookieData_vtable>(static_cast<org::sem::NamedProperty::CookieData&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCookieData), org_context, self);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isExportLatexClassOptions_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexClassOptions), org_context, self);
}
haxorg_NamedPropertyExportLatexClassOptions org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getExportLatexClassOptionsConst_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexClassOptions, haxorg_NamedPropertyExportLatexClassOptions_vtable>(static_cast<org::sem::NamedProperty::ExportLatexClassOptions const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getExportLatexClassOptions), org_context, self);
}
haxorg_NamedPropertyExportLatexClassOptions org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getExportLatexClassOptionsMut(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexClassOptions, haxorg_NamedPropertyExportLatexClassOptions_vtable>(static_cast<org::sem::NamedProperty::ExportLatexClassOptions&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexClassOptions), org_context, self);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isExportLatexHeader_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexHeader), org_context, self);
}
haxorg_NamedPropertyExportLatexHeader org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getExportLatexHeaderConst_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexHeader, haxorg_NamedPropertyExportLatexHeader_vtable>(static_cast<org::sem::NamedProperty::ExportLatexHeader const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getExportLatexHeader), org_context, self);
}
haxorg_NamedPropertyExportLatexHeader org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getExportLatexHeaderMut(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexHeader, haxorg_NamedPropertyExportLatexHeader_vtable>(static_cast<org::sem::NamedProperty::ExportLatexHeader&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexHeader), org_context, self);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isExportLatexCompiler_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexCompiler), org_context, self);
}
haxorg_NamedPropertyExportLatexCompiler org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getExportLatexCompilerConst_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexCompiler, haxorg_NamedPropertyExportLatexCompiler_vtable>(static_cast<org::sem::NamedProperty::ExportLatexCompiler const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getExportLatexCompiler), org_context, self);
}
haxorg_NamedPropertyExportLatexCompiler org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getExportLatexCompilerMut(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexCompiler, haxorg_NamedPropertyExportLatexCompiler_vtable>(static_cast<org::sem::NamedProperty::ExportLatexCompiler&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexCompiler), org_context, self);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isOrdered_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isOrdered), org_context, self);
}
haxorg_NamedPropertyOrdered org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getOrderedConst_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyOrdered, haxorg_NamedPropertyOrdered_vtable>(static_cast<org::sem::NamedProperty::Ordered const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getOrdered), org_context, self);
}
haxorg_NamedPropertyOrdered org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getOrderedMut(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyOrdered, haxorg_NamedPropertyOrdered_vtable>(static_cast<org::sem::NamedProperty::Ordered&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getOrdered), org_context, self);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isEffort_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isEffort), org_context, self);
}
haxorg_NamedPropertyEffort org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getEffortConst_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyEffort, haxorg_NamedPropertyEffort_vtable>(static_cast<org::sem::NamedProperty::Effort const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getEffort), org_context, self);
}
haxorg_NamedPropertyEffort org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getEffortMut(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyEffort, haxorg_NamedPropertyEffort_vtable>(static_cast<org::sem::NamedProperty::Effort&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getEffort), org_context, self);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isVisibility_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isVisibility), org_context, self);
}
haxorg_NamedPropertyVisibility org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getVisibilityConst_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyVisibility, haxorg_NamedPropertyVisibility_vtable>(static_cast<org::sem::NamedProperty::Visibility const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getVisibility), org_context, self);
}
haxorg_NamedPropertyVisibility org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getVisibilityMut(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyVisibility, haxorg_NamedPropertyVisibility_vtable>(static_cast<org::sem::NamedProperty::Visibility&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getVisibility), org_context, self);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isExportOptions_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportOptions), org_context, self);
}
haxorg_NamedPropertyExportOptions org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getExportOptionsConst_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyExportOptions, haxorg_NamedPropertyExportOptions_vtable>(static_cast<org::sem::NamedProperty::ExportOptions const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getExportOptions), org_context, self);
}
haxorg_NamedPropertyExportOptions org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getExportOptionsMut(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyExportOptions, haxorg_NamedPropertyExportOptions_vtable>(static_cast<org::sem::NamedProperty::ExportOptions&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportOptions), org_context, self);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isBlocker_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isBlocker), org_context, self);
}
haxorg_NamedPropertyBlocker org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getBlockerConst_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyBlocker, haxorg_NamedPropertyBlocker_vtable>(static_cast<org::sem::NamedProperty::Blocker const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getBlocker), org_context, self);
}
haxorg_NamedPropertyBlocker org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getBlockerMut(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyBlocker, haxorg_NamedPropertyBlocker_vtable>(static_cast<org::sem::NamedProperty::Blocker&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getBlocker), org_context, self);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isUnnumbered_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isUnnumbered), org_context, self);
}
haxorg_NamedPropertyUnnumbered org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getUnnumberedConst_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyUnnumbered, haxorg_NamedPropertyUnnumbered_vtable>(static_cast<org::sem::NamedProperty::Unnumbered const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getUnnumbered), org_context, self);
}
haxorg_NamedPropertyUnnumbered org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getUnnumberedMut(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyUnnumbered, haxorg_NamedPropertyUnnumbered_vtable>(static_cast<org::sem::NamedProperty::Unnumbered&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getUnnumbered), org_context, self);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isCreated_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCreated), org_context, self);
}
haxorg_NamedPropertyCreated org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCreatedConst_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyCreated, haxorg_NamedPropertyCreated_vtable>(static_cast<org::sem::NamedProperty::Created const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCreated), org_context, self);
}
haxorg_NamedPropertyCreated org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCreatedMut(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyCreated, haxorg_NamedPropertyCreated_vtable>(static_cast<org::sem::NamedProperty::Created&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCreated), org_context, self);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isRadioId_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isRadioId), org_context, self);
}
haxorg_NamedPropertyRadioId org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getRadioIdConst_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyRadioId, haxorg_NamedPropertyRadioId_vtable>(static_cast<org::sem::NamedProperty::RadioId const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getRadioId), org_context, self);
}
haxorg_NamedPropertyRadioId org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getRadioIdMut(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyRadioId, haxorg_NamedPropertyRadioId_vtable>(static_cast<org::sem::NamedProperty::RadioId&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getRadioId), org_context, self);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isHashtagDef_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isHashtagDef), org_context, self);
}
haxorg_NamedPropertyHashtagDef org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getHashtagDefConst_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyHashtagDef, haxorg_NamedPropertyHashtagDef_vtable>(static_cast<org::sem::NamedProperty::HashtagDef const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getHashtagDef), org_context, self);
}
haxorg_NamedPropertyHashtagDef org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getHashtagDefMut(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyHashtagDef, haxorg_NamedPropertyHashtagDef_vtable>(static_cast<org::sem::NamedProperty::HashtagDef&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getHashtagDef), org_context, self);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isCustomArgs_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomArgs), org_context, self);
}
haxorg_NamedPropertyCustomArgs org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCustomArgsConst_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomArgs, haxorg_NamedPropertyCustomArgs_vtable>(static_cast<org::sem::NamedProperty::CustomArgs const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCustomArgs), org_context, self);
}
haxorg_NamedPropertyCustomArgs org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCustomArgsMut(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomArgs, haxorg_NamedPropertyCustomArgs_vtable>(static_cast<org::sem::NamedProperty::CustomArgs&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomArgs), org_context, self);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isCustomRaw_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomRaw), org_context, self);
}
haxorg_NamedPropertyCustomRaw org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCustomRawConst_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomRaw, haxorg_NamedPropertyCustomRaw_vtable>(static_cast<org::sem::NamedProperty::CustomRaw const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCustomRaw), org_context, self);
}
haxorg_NamedPropertyCustomRaw org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCustomRawMut(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomRaw, haxorg_NamedPropertyCustomRaw_vtable>(static_cast<org::sem::NamedProperty::CustomRaw&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomRaw), org_context, self);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isCustomId_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomId), org_context, self);
}
haxorg_NamedPropertyCustomId org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCustomIdConst_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomId, haxorg_NamedPropertyCustomId_vtable>(static_cast<org::sem::NamedProperty::CustomId const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCustomId), org_context, self);
}
haxorg_NamedPropertyCustomId org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCustomIdMut(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomId, haxorg_NamedPropertyCustomId_vtable>(static_cast<org::sem::NamedProperty::CustomId&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomId), org_context, self);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isCustomSubtreeJson_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomSubtreeJson), org_context, self);
}
haxorg_NamedPropertyCustomSubtreeJson org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCustomSubtreeJsonConst_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomSubtreeJson, haxorg_NamedPropertyCustomSubtreeJson_vtable>(static_cast<org::sem::NamedProperty::CustomSubtreeJson const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCustomSubtreeJson), org_context, self);
}
haxorg_NamedPropertyCustomSubtreeJson org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCustomSubtreeJsonMut(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomSubtreeJson, haxorg_NamedPropertyCustomSubtreeJson_vtable>(static_cast<org::sem::NamedProperty::CustomSubtreeJson&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomSubtreeJson), org_context, self);
}
bool org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::isCustomSubtreeFlags_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomSubtreeFlags), org_context, self);
}
haxorg_NamedPropertyCustomSubtreeFlags org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCustomSubtreeFlagsConst_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomSubtreeFlags, haxorg_NamedPropertyCustomSubtreeFlags_vtable>(static_cast<org::sem::NamedProperty::CustomSubtreeFlags const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCustomSubtreeFlags), org_context, self);
}
haxorg_NamedPropertyCustomSubtreeFlags org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getCustomSubtreeFlagsMut(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomSubtreeFlags, haxorg_NamedPropertyCustomSubtreeFlags_vtable>(static_cast<org::sem::NamedProperty::CustomSubtreeFlags&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomSubtreeFlags), org_context, self);
}
haxorg_NamedPropertyKind org::bind::c::VTable<haxorg_NamedProperty, haxorg_NamedProperty_vtable>::getKind_const(OrgContext* org_context, haxorg_NamedProperty self) {
  return org::bind::c::execute_cpp<haxorg_NamedPropertyKind, haxorg_builtin_vtable>(static_cast<org::sem::NamedProperty::Kind(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getKind), org_context, self);
}
bool org::bind::c::VTable<haxorg_NamedPropertyNonblocking, haxorg_NamedPropertyNonblocking_vtable>::__eq___const(OrgContext* org_context, haxorg_NamedPropertyNonblocking self, haxorg_NamedPropertyNonblocking other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::Nonblocking::*)(org::sem::NamedProperty::Nonblocking const&) const>(&org::sem::NamedProperty::Nonblocking::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyArchiveTime, haxorg_NamedPropertyArchiveTime_vtable>::__eq___const(OrgContext* org_context, haxorg_NamedPropertyArchiveTime self, haxorg_NamedPropertyArchiveTime other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::ArchiveTime::*)(org::sem::NamedProperty::ArchiveTime const&) const>(&org::sem::NamedProperty::ArchiveTime::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyArchiveFile, haxorg_NamedPropertyArchiveFile_vtable>::__eq___const(OrgContext* org_context, haxorg_NamedPropertyArchiveFile self, haxorg_NamedPropertyArchiveFile other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::ArchiveFile::*)(org::sem::NamedProperty::ArchiveFile const&) const>(&org::sem::NamedProperty::ArchiveFile::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyArchiveOlpath, haxorg_NamedPropertyArchiveOlpath_vtable>::__eq___const(OrgContext* org_context, haxorg_NamedPropertyArchiveOlpath self, haxorg_NamedPropertyArchiveOlpath other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::ArchiveOlpath::*)(org::sem::NamedProperty::ArchiveOlpath const&) const>(&org::sem::NamedProperty::ArchiveOlpath::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyArchiveTarget, haxorg_NamedPropertyArchiveTarget_vtable>::__eq___const(OrgContext* org_context, haxorg_NamedPropertyArchiveTarget self, haxorg_NamedPropertyArchiveTarget other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::ArchiveTarget::*)(org::sem::NamedProperty::ArchiveTarget const&) const>(&org::sem::NamedProperty::ArchiveTarget::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyArchiveCategory, haxorg_NamedPropertyArchiveCategory_vtable>::__eq___const(OrgContext* org_context, haxorg_NamedPropertyArchiveCategory self, haxorg_NamedPropertyArchiveCategory other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::ArchiveCategory::*)(org::sem::NamedProperty::ArchiveCategory const&) const>(&org::sem::NamedProperty::ArchiveCategory::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyArchiveTodo, haxorg_NamedPropertyArchiveTodo_vtable>::__eq___const(OrgContext* org_context, haxorg_NamedPropertyArchiveTodo self, haxorg_NamedPropertyArchiveTodo other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::ArchiveTodo::*)(org::sem::NamedProperty::ArchiveTodo const&) const>(&org::sem::NamedProperty::ArchiveTodo::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyTrigger, haxorg_NamedPropertyTrigger_vtable>::__eq___const(OrgContext* org_context, haxorg_NamedPropertyTrigger self, haxorg_NamedPropertyTrigger other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::Trigger::*)(org::sem::NamedProperty::Trigger const&) const>(&org::sem::NamedProperty::Trigger::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyExportLatexClass, haxorg_NamedPropertyExportLatexClass_vtable>::__eq___const(OrgContext* org_context, haxorg_NamedPropertyExportLatexClass self, haxorg_NamedPropertyExportLatexClass other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::ExportLatexClass::*)(org::sem::NamedProperty::ExportLatexClass const&) const>(&org::sem::NamedProperty::ExportLatexClass::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyCookieData, haxorg_NamedPropertyCookieData_vtable>::__eq___const(OrgContext* org_context, haxorg_NamedPropertyCookieData self, haxorg_NamedPropertyCookieData other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::CookieData::*)(org::sem::NamedProperty::CookieData const&) const>(&org::sem::NamedProperty::CookieData::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyExportLatexClassOptions, haxorg_NamedPropertyExportLatexClassOptions_vtable>::__eq___const(OrgContext* org_context, haxorg_NamedPropertyExportLatexClassOptions self, haxorg_NamedPropertyExportLatexClassOptions other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::ExportLatexClassOptions::*)(org::sem::NamedProperty::ExportLatexClassOptions const&) const>(&org::sem::NamedProperty::ExportLatexClassOptions::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyExportLatexHeader, haxorg_NamedPropertyExportLatexHeader_vtable>::__eq___const(OrgContext* org_context, haxorg_NamedPropertyExportLatexHeader self, haxorg_NamedPropertyExportLatexHeader other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::ExportLatexHeader::*)(org::sem::NamedProperty::ExportLatexHeader const&) const>(&org::sem::NamedProperty::ExportLatexHeader::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyExportLatexCompiler, haxorg_NamedPropertyExportLatexCompiler_vtable>::__eq___const(OrgContext* org_context, haxorg_NamedPropertyExportLatexCompiler self, haxorg_NamedPropertyExportLatexCompiler other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::ExportLatexCompiler::*)(org::sem::NamedProperty::ExportLatexCompiler const&) const>(&org::sem::NamedProperty::ExportLatexCompiler::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyOrdered, haxorg_NamedPropertyOrdered_vtable>::__eq___const(OrgContext* org_context, haxorg_NamedPropertyOrdered self, haxorg_NamedPropertyOrdered other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::Ordered::*)(org::sem::NamedProperty::Ordered const&) const>(&org::sem::NamedProperty::Ordered::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyEffort, haxorg_NamedPropertyEffort_vtable>::__eq___const(OrgContext* org_context, haxorg_NamedPropertyEffort self, haxorg_NamedPropertyEffort other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::Effort::*)(org::sem::NamedProperty::Effort const&) const>(&org::sem::NamedProperty::Effort::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyVisibility, haxorg_NamedPropertyVisibility_vtable>::__eq___const(OrgContext* org_context, haxorg_NamedPropertyVisibility self, haxorg_NamedPropertyVisibility other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::Visibility::*)(org::sem::NamedProperty::Visibility const&) const>(&org::sem::NamedProperty::Visibility::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyExportOptions, haxorg_NamedPropertyExportOptions_vtable>::__eq___const(OrgContext* org_context, haxorg_NamedPropertyExportOptions self, haxorg_NamedPropertyExportOptions other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::ExportOptions::*)(org::sem::NamedProperty::ExportOptions const&) const>(&org::sem::NamedProperty::ExportOptions::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyBlocker, haxorg_NamedPropertyBlocker_vtable>::__eq___const(OrgContext* org_context, haxorg_NamedPropertyBlocker self, haxorg_NamedPropertyBlocker other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::Blocker::*)(org::sem::NamedProperty::Blocker const&) const>(&org::sem::NamedProperty::Blocker::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyUnnumbered, haxorg_NamedPropertyUnnumbered_vtable>::__eq___const(OrgContext* org_context, haxorg_NamedPropertyUnnumbered self, haxorg_NamedPropertyUnnumbered other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::Unnumbered::*)(org::sem::NamedProperty::Unnumbered const&) const>(&org::sem::NamedProperty::Unnumbered::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyCreated, haxorg_NamedPropertyCreated_vtable>::__eq___const(OrgContext* org_context, haxorg_NamedPropertyCreated self, haxorg_NamedPropertyCreated other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::Created::*)(org::sem::NamedProperty::Created const&) const>(&org::sem::NamedProperty::Created::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyRadioId, haxorg_NamedPropertyRadioId_vtable>::__eq___const(OrgContext* org_context, haxorg_NamedPropertyRadioId self, haxorg_NamedPropertyRadioId other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::RadioId::*)(org::sem::NamedProperty::RadioId const&) const>(&org::sem::NamedProperty::RadioId::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyHashtagDef, haxorg_NamedPropertyHashtagDef_vtable>::__eq___const(OrgContext* org_context, haxorg_NamedPropertyHashtagDef self, haxorg_NamedPropertyHashtagDef other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::HashtagDef::*)(org::sem::NamedProperty::HashtagDef const&) const>(&org::sem::NamedProperty::HashtagDef::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyCustomArgs, haxorg_NamedPropertyCustomArgs_vtable>::__eq___const(OrgContext* org_context, haxorg_NamedPropertyCustomArgs self, haxorg_NamedPropertyCustomArgs other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::CustomArgs::*)(org::sem::NamedProperty::CustomArgs const&) const>(&org::sem::NamedProperty::CustomArgs::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyCustomRaw, haxorg_NamedPropertyCustomRaw_vtable>::__eq___const(OrgContext* org_context, haxorg_NamedPropertyCustomRaw self, haxorg_NamedPropertyCustomRaw other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::CustomRaw::*)(org::sem::NamedProperty::CustomRaw const&) const>(&org::sem::NamedProperty::CustomRaw::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyCustomId, haxorg_NamedPropertyCustomId_vtable>::__eq___const(OrgContext* org_context, haxorg_NamedPropertyCustomId self, haxorg_NamedPropertyCustomId other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::CustomId::*)(org::sem::NamedProperty::CustomId const&) const>(&org::sem::NamedProperty::CustomId::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyCustomSubtreeJson, haxorg_NamedPropertyCustomSubtreeJson_vtable>::__eq___const(OrgContext* org_context, haxorg_NamedPropertyCustomSubtreeJson self, haxorg_NamedPropertyCustomSubtreeJson other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::CustomSubtreeJson::*)(org::sem::NamedProperty::CustomSubtreeJson const&) const>(&org::sem::NamedProperty::CustomSubtreeJson::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_NamedPropertyCustomSubtreeFlags, haxorg_NamedPropertyCustomSubtreeFlags_vtable>::__eq___const(OrgContext* org_context, haxorg_NamedPropertyCustomSubtreeFlags self, haxorg_NamedPropertyCustomSubtreeFlags other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::NamedProperty::CustomSubtreeFlags::*)(org::sem::NamedProperty::CustomSubtreeFlags const&) const>(&org::sem::NamedProperty::CustomSubtreeFlags::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::__eq___const(OrgContext* org_context, haxorg_OrgDiagnostics self, haxorg_OrgDiagnostics other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::OrgDiagnostics::*)(org::sem::OrgDiagnostics const&) const>(&org::sem::OrgDiagnostics::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::isParseTokenError_const(OrgContext* org_context, haxorg_OrgDiagnostics self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::isParseTokenError), org_context, self);
}
haxorg_OrgDiagnosticsParseTokenError org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getParseTokenErrorConst_const(OrgContext* org_context, haxorg_OrgDiagnostics self) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsParseTokenError, haxorg_OrgDiagnosticsParseTokenError_vtable>(static_cast<org::sem::OrgDiagnostics::ParseTokenError const&(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::getParseTokenError), org_context, self);
}
haxorg_OrgDiagnosticsParseTokenError org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getParseTokenErrorMut(OrgContext* org_context, haxorg_OrgDiagnostics self) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsParseTokenError, haxorg_OrgDiagnosticsParseTokenError_vtable>(static_cast<org::sem::OrgDiagnostics::ParseTokenError&(org::sem::OrgDiagnostics::*)()>(&org::sem::OrgDiagnostics::getParseTokenError), org_context, self);
}
bool org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::isParseError_const(OrgContext* org_context, haxorg_OrgDiagnostics self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::isParseError), org_context, self);
}
haxorg_OrgDiagnosticsParseError org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getParseErrorConst_const(OrgContext* org_context, haxorg_OrgDiagnostics self) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsParseError, haxorg_OrgDiagnosticsParseError_vtable>(static_cast<org::sem::OrgDiagnostics::ParseError const&(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::getParseError), org_context, self);
}
haxorg_OrgDiagnosticsParseError org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getParseErrorMut(OrgContext* org_context, haxorg_OrgDiagnostics self) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsParseError, haxorg_OrgDiagnosticsParseError_vtable>(static_cast<org::sem::OrgDiagnostics::ParseError&(org::sem::OrgDiagnostics::*)()>(&org::sem::OrgDiagnostics::getParseError), org_context, self);
}
bool org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::isIncludeError_const(OrgContext* org_context, haxorg_OrgDiagnostics self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::isIncludeError), org_context, self);
}
haxorg_OrgDiagnosticsIncludeError org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getIncludeErrorConst_const(OrgContext* org_context, haxorg_OrgDiagnostics self) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsIncludeError, haxorg_OrgDiagnosticsIncludeError_vtable>(static_cast<org::sem::OrgDiagnostics::IncludeError const&(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::getIncludeError), org_context, self);
}
haxorg_OrgDiagnosticsIncludeError org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getIncludeErrorMut(OrgContext* org_context, haxorg_OrgDiagnostics self) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsIncludeError, haxorg_OrgDiagnosticsIncludeError_vtable>(static_cast<org::sem::OrgDiagnostics::IncludeError&(org::sem::OrgDiagnostics::*)()>(&org::sem::OrgDiagnostics::getIncludeError), org_context, self);
}
bool org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::isConvertError_const(OrgContext* org_context, haxorg_OrgDiagnostics self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::isConvertError), org_context, self);
}
haxorg_OrgDiagnosticsConvertError org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getConvertErrorConst_const(OrgContext* org_context, haxorg_OrgDiagnostics self) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsConvertError, haxorg_OrgDiagnosticsConvertError_vtable>(static_cast<org::sem::OrgDiagnostics::ConvertError const&(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::getConvertError), org_context, self);
}
haxorg_OrgDiagnosticsConvertError org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getConvertErrorMut(OrgContext* org_context, haxorg_OrgDiagnostics self) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsConvertError, haxorg_OrgDiagnosticsConvertError_vtable>(static_cast<org::sem::OrgDiagnostics::ConvertError&(org::sem::OrgDiagnostics::*)()>(&org::sem::OrgDiagnostics::getConvertError), org_context, self);
}
bool org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::isInternalError_const(OrgContext* org_context, haxorg_OrgDiagnostics self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::isInternalError), org_context, self);
}
haxorg_OrgDiagnosticsInternalError org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getInternalErrorConst_const(OrgContext* org_context, haxorg_OrgDiagnostics self) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsInternalError, haxorg_OrgDiagnosticsInternalError_vtable>(static_cast<org::sem::OrgDiagnostics::InternalError const&(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::getInternalError), org_context, self);
}
haxorg_OrgDiagnosticsInternalError org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getInternalErrorMut(OrgContext* org_context, haxorg_OrgDiagnostics self) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsInternalError, haxorg_OrgDiagnosticsInternalError_vtable>(static_cast<org::sem::OrgDiagnostics::InternalError&(org::sem::OrgDiagnostics::*)()>(&org::sem::OrgDiagnostics::getInternalError), org_context, self);
}
haxorg_OrgDiagnosticsKind org::bind::c::VTable<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>::getKind_const(OrgContext* org_context, haxorg_OrgDiagnostics self) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsKind, haxorg_builtin_vtable>(static_cast<org::sem::OrgDiagnostics::Kind(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::getKind), org_context, self);
}
bool org::bind::c::VTable<haxorg_OrgDiagnosticsParseTokenError, haxorg_OrgDiagnosticsParseTokenError_vtable>::__eq___const(OrgContext* org_context, haxorg_OrgDiagnosticsParseTokenError self, haxorg_OrgDiagnosticsParseTokenError other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::OrgDiagnostics::ParseTokenError::*)(org::sem::OrgDiagnostics::ParseTokenError const&) const>(&org::sem::OrgDiagnostics::ParseTokenError::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_OrgDiagnosticsParseError, haxorg_OrgDiagnosticsParseError_vtable>::__eq___const(OrgContext* org_context, haxorg_OrgDiagnosticsParseError self, haxorg_OrgDiagnosticsParseError other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::OrgDiagnostics::ParseError::*)(org::sem::OrgDiagnostics::ParseError const&) const>(&org::sem::OrgDiagnostics::ParseError::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_OrgDiagnosticsIncludeError, haxorg_OrgDiagnosticsIncludeError_vtable>::__eq___const(OrgContext* org_context, haxorg_OrgDiagnosticsIncludeError self, haxorg_OrgDiagnosticsIncludeError other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::OrgDiagnostics::IncludeError::*)(org::sem::OrgDiagnostics::IncludeError const&) const>(&org::sem::OrgDiagnostics::IncludeError::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_OrgDiagnosticsConvertError, haxorg_OrgDiagnosticsConvertError_vtable>::__eq___const(OrgContext* org_context, haxorg_OrgDiagnosticsConvertError self, haxorg_OrgDiagnosticsConvertError other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::OrgDiagnostics::ConvertError::*)(org::sem::OrgDiagnostics::ConvertError const&) const>(&org::sem::OrgDiagnostics::ConvertError::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_OrgDiagnosticsInternalError, haxorg_OrgDiagnosticsInternalError_vtable>::__eq___const(OrgContext* org_context, haxorg_OrgDiagnosticsInternalError self, haxorg_OrgDiagnosticsInternalError other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::OrgDiagnostics::InternalError::*)(org::sem::OrgDiagnostics::InternalError const&) const>(&org::sem::OrgDiagnostics::InternalError::operator==), org_context, self, other);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getAttached_const(OrgContext* org_context, haxorg_Stmt self, haxorg_HstdOpt kind) {
  return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Stmt::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Stmt::getAttached), org_context, self, kind);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getCaption_const(OrgContext* org_context, haxorg_Stmt self) {
  return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Stmt::*)() const>(&org::sem::Stmt::getCaption), org_context, self);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getName_const(OrgContext* org_context, haxorg_Stmt self) {
  return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<hstd::Str>(org::sem::Stmt::*)() const>(&org::sem::Stmt::getName), org_context, self);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getAttrs_const(OrgContext* org_context, haxorg_Stmt self, haxorg_HstdOpt kind) {
  return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Stmt::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Stmt::getAttrs), org_context, self, kind);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getFirstAttr_const(OrgContext* org_context, haxorg_Stmt self, haxorg_HstdStr kind) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttr), org_context, self, kind);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getFirstAttrString_const(OrgContext* org_context, haxorg_Stmt self, haxorg_HstdStr kind) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<hstd::Str>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttrString), org_context, self, kind);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getFirstAttrInt_const(OrgContext* org_context, haxorg_Stmt self, haxorg_HstdStr kind) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<int>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttrInt), org_context, self, kind);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getFirstAttrBool_const(OrgContext* org_context, haxorg_Stmt self, haxorg_HstdStr kind) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<bool>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttrBool), org_context, self, kind);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getFirstAttrDouble_const(OrgContext* org_context, haxorg_Stmt self, haxorg_HstdStr kind) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<double>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttrDouble), org_context, self, kind);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getFirstAttrLisp_const(OrgContext* org_context, haxorg_Stmt self, haxorg_HstdStr kind) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<org::sem::AttrValue::LispValue>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttrLisp), org_context, self, kind);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Stmt, haxorg_Stmt_vtable>::getFirstAttrKind_const(OrgContext* org_context, haxorg_Stmt self, haxorg_HstdStr kind) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<org::sem::AttrValue::Kind>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttrKind), org_context, self, kind);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_Leaf, haxorg_Leaf_vtable>::getText_const(OrgContext* org_context, haxorg_Leaf self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str(org::sem::Leaf::*)() const>(&org::sem::Leaf::getText), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getYear_const(OrgContext* org_context, haxorg_Time self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getYear), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getMonth_const(OrgContext* org_context, haxorg_Time self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getMonth), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getDay_const(OrgContext* org_context, haxorg_Time self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getDay), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getHour_const(OrgContext* org_context, haxorg_Time self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getHour), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getMinute_const(OrgContext* org_context, haxorg_Time self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getMinute), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getSecond_const(OrgContext* org_context, haxorg_Time self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getSecond), org_context, self);
}
haxorg_UserTime org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getStaticTime_const(OrgContext* org_context, haxorg_Time self) {
  return org::bind::c::execute_cpp<haxorg_UserTime, haxorg_UserTime_vtable>(static_cast<hstd::UserTime(org::sem::Time::*)() const>(&org::sem::Time::getStaticTime), org_context, self);
}
bool org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::isStatic_const(OrgContext* org_context, haxorg_Time self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Time::*)() const>(&org::sem::Time::isStatic), org_context, self);
}
haxorg_TimeStatic org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getStaticConst_const(OrgContext* org_context, haxorg_Time self) {
  return org::bind::c::execute_cpp<haxorg_TimeStatic, haxorg_TimeStatic_vtable>(static_cast<org::sem::Time::Static const&(org::sem::Time::*)() const>(&org::sem::Time::getStatic), org_context, self);
}
haxorg_TimeStatic org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getStaticMut(OrgContext* org_context, haxorg_Time self) {
  return org::bind::c::execute_cpp<haxorg_TimeStatic, haxorg_TimeStatic_vtable>(static_cast<org::sem::Time::Static&(org::sem::Time::*)()>(&org::sem::Time::getStatic), org_context, self);
}
bool org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::isDynamic_const(OrgContext* org_context, haxorg_Time self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Time::*)() const>(&org::sem::Time::isDynamic), org_context, self);
}
haxorg_TimeDynamic org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getDynamicConst_const(OrgContext* org_context, haxorg_Time self) {
  return org::bind::c::execute_cpp<haxorg_TimeDynamic, haxorg_TimeDynamic_vtable>(static_cast<org::sem::Time::Dynamic const&(org::sem::Time::*)() const>(&org::sem::Time::getDynamic), org_context, self);
}
haxorg_TimeDynamic org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getDynamicMut(OrgContext* org_context, haxorg_Time self) {
  return org::bind::c::execute_cpp<haxorg_TimeDynamic, haxorg_TimeDynamic_vtable>(static_cast<org::sem::Time::Dynamic&(org::sem::Time::*)()>(&org::sem::Time::getDynamic), org_context, self);
}
haxorg_TimeTimeKind org::bind::c::VTable<haxorg_Time, haxorg_Time_vtable>::getTimeKind_const(OrgContext* org_context, haxorg_Time self) {
  return org::bind::c::execute_cpp<haxorg_TimeTimeKind, haxorg_builtin_vtable>(static_cast<org::sem::Time::TimeKind(org::sem::Time::*)() const>(&org::sem::Time::getTimeKind), org_context, self);
}
bool org::bind::c::VTable<haxorg_TimeRepeat, haxorg_TimeRepeat_vtable>::__eq___const(OrgContext* org_context, haxorg_TimeRepeat self, haxorg_TimeRepeat other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Time::Repeat::*)(org::sem::Time::Repeat const&) const>(&org::sem::Time::Repeat::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_TimeStatic, haxorg_TimeStatic_vtable>::__eq___const(OrgContext* org_context, haxorg_TimeStatic self, haxorg_TimeStatic other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Time::Static::*)(org::sem::Time::Static const&) const>(&org::sem::Time::Static::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_TimeDynamic, haxorg_TimeDynamic_vtable>::__eq___const(OrgContext* org_context, haxorg_TimeDynamic self, haxorg_TimeDynamic other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Time::Dynamic::*)(org::sem::Time::Dynamic const&) const>(&org::sem::Time::Dynamic::operator==), org_context, self, other);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_TimeRange, haxorg_TimeRange_vtable>::getClockedTimeSeconds_const(OrgContext* org_context, haxorg_TimeRange self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<int64_t>(org::sem::TimeRange::*)() const>(&org::sem::TimeRange::getClockedTimeSeconds), org_context, self);
}
void org::bind::c::VTable<haxorg_SubtreeLog, haxorg_SubtreeLog_vtable>::setDescription(OrgContext* org_context, haxorg_SubtreeLog self, haxorg_SemId desc) {
  return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(static_cast<void(org::sem::SubtreeLog::*)(org::sem::SemId<org::sem::StmtList>)>(&org::sem::SubtreeLog::setDescription), org_context, self, desc);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Subtree, haxorg_Subtree_vtable>::getTimePeriods_const(OrgContext* org_context, haxorg_Subtree self, haxorg_HstdIntSet kinds) {
  return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<org::sem::SubtreePeriod>(org::sem::Subtree::*)(hstd::IntSet<org::sem::SubtreePeriod::Kind>) const>(&org::sem::Subtree::getTimePeriods), org_context, self, kinds);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Subtree, haxorg_Subtree_vtable>::getProperties_const(OrgContext* org_context, haxorg_Subtree self, haxorg_HstdStr kind, haxorg_HstdOpt subkind) {
  return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<org::sem::NamedProperty>(org::sem::Subtree::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Subtree::getProperties), org_context, self, kind, subkind);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Subtree, haxorg_Subtree_vtable>::getProperty_const(OrgContext* org_context, haxorg_Subtree self, haxorg_HstdStr kind, haxorg_HstdOpt subkind) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<org::sem::NamedProperty>(org::sem::Subtree::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Subtree::getProperty), org_context, self, kind, subkind);
}
void org::bind::c::VTable<haxorg_Subtree, haxorg_Subtree_vtable>::removeProperty(OrgContext* org_context, haxorg_Subtree self, haxorg_HstdStr kind, haxorg_HstdOpt subkind) {
  return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(static_cast<void(org::sem::Subtree::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&)>(&org::sem::Subtree::removeProperty), org_context, self, kind, subkind);
}
void org::bind::c::VTable<haxorg_Subtree, haxorg_Subtree_vtable>::setProperty(OrgContext* org_context, haxorg_Subtree self, haxorg_NamedProperty value) {
  return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(static_cast<void(org::sem::Subtree::*)(org::sem::NamedProperty const&)>(&org::sem::Subtree::setProperty), org_context, self, value);
}
void org::bind::c::VTable<haxorg_Subtree, haxorg_Subtree_vtable>::setPropertyStrValue(OrgContext* org_context, haxorg_Subtree self, haxorg_HstdStr value, haxorg_HstdStr kind, haxorg_HstdOpt subkind) {
  return org::bind::c::execute_cpp<void, haxorg_builtin_vtable>(static_cast<void(org::sem::Subtree::*)(hstd::Str const&, hstd::Str const&, hstd::Opt<hstd::Str> const&)>(&org::sem::Subtree::setPropertyStrValue), org_context, self, value, kind, subkind);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_Subtree, haxorg_Subtree_vtable>::getCleanTitle_const(OrgContext* org_context, haxorg_Subtree self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str(org::sem::Subtree::*)() const>(&org::sem::Subtree::getCleanTitle), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Subtree, haxorg_Subtree_vtable>::getTodoKeyword_const(OrgContext* org_context, haxorg_Subtree self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<hstd::Str>(org::sem::Subtree::*)() const>(&org::sem::Subtree::getTodoKeyword), org_context, self);
}
bool org::bind::c::VTable<haxorg_ListItem, haxorg_ListItem_vtable>::isDescriptionItem_const(OrgContext* org_context, haxorg_ListItem self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::ListItem::*)() const>(&org::sem::ListItem::isDescriptionItem), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ListItem, haxorg_ListItem_vtable>::getCleanHeader_const(OrgContext* org_context, haxorg_ListItem self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<hstd::Str>(org::sem::ListItem::*)() const>(&org::sem::ListItem::getCleanHeader), org_context, self);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_DocumentOptions, haxorg_DocumentOptions_vtable>::getProperties_const(OrgContext* org_context, haxorg_DocumentOptions self, haxorg_HstdStr kind, haxorg_HstdOpt subKind) {
  return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<org::sem::NamedProperty>(org::sem::DocumentOptions::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::DocumentOptions::getProperties), org_context, self, kind, subKind);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_DocumentOptions, haxorg_DocumentOptions_vtable>::getProperty_const(OrgContext* org_context, haxorg_DocumentOptions self, haxorg_HstdStr kind, haxorg_HstdOpt subKind) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<org::sem::NamedProperty>(org::sem::DocumentOptions::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::DocumentOptions::getProperty), org_context, self, kind, subKind);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Document, haxorg_Document_vtable>::getProperties_const(OrgContext* org_context, haxorg_Document self, haxorg_HstdStr kind, haxorg_HstdOpt subKind) {
  return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<org::sem::NamedProperty>(org::sem::Document::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Document::getProperties), org_context, self, kind, subKind);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Document, haxorg_Document_vtable>::getProperty_const(OrgContext* org_context, haxorg_Document self, haxorg_HstdStr kind, haxorg_HstdOpt subKind) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<org::sem::NamedProperty>(org::sem::Document::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Document::getProperty), org_context, self, kind, subKind);
}
bool org::bind::c::VTable<haxorg_File, haxorg_File_vtable>::isDocument_const(OrgContext* org_context, haxorg_File self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::File::*)() const>(&org::sem::File::isDocument), org_context, self);
}
haxorg_FileDocument org::bind::c::VTable<haxorg_File, haxorg_File_vtable>::getDocumentConst_const(OrgContext* org_context, haxorg_File self) {
  return org::bind::c::execute_cpp<haxorg_FileDocument, haxorg_FileDocument_vtable>(static_cast<org::sem::File::Document const&(org::sem::File::*)() const>(&org::sem::File::getDocument), org_context, self);
}
haxorg_FileDocument org::bind::c::VTable<haxorg_File, haxorg_File_vtable>::getDocumentMut(OrgContext* org_context, haxorg_File self) {
  return org::bind::c::execute_cpp<haxorg_FileDocument, haxorg_FileDocument_vtable>(static_cast<org::sem::File::Document&(org::sem::File::*)()>(&org::sem::File::getDocument), org_context, self);
}
bool org::bind::c::VTable<haxorg_File, haxorg_File_vtable>::isAttachment_const(OrgContext* org_context, haxorg_File self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::File::*)() const>(&org::sem::File::isAttachment), org_context, self);
}
haxorg_FileAttachment org::bind::c::VTable<haxorg_File, haxorg_File_vtable>::getAttachmentConst_const(OrgContext* org_context, haxorg_File self) {
  return org::bind::c::execute_cpp<haxorg_FileAttachment, haxorg_FileAttachment_vtable>(static_cast<org::sem::File::Attachment const&(org::sem::File::*)() const>(&org::sem::File::getAttachment), org_context, self);
}
haxorg_FileAttachment org::bind::c::VTable<haxorg_File, haxorg_File_vtable>::getAttachmentMut(OrgContext* org_context, haxorg_File self) {
  return org::bind::c::execute_cpp<haxorg_FileAttachment, haxorg_FileAttachment_vtable>(static_cast<org::sem::File::Attachment&(org::sem::File::*)()>(&org::sem::File::getAttachment), org_context, self);
}
bool org::bind::c::VTable<haxorg_File, haxorg_File_vtable>::isSource_const(OrgContext* org_context, haxorg_File self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::File::*)() const>(&org::sem::File::isSource), org_context, self);
}
haxorg_FileSource org::bind::c::VTable<haxorg_File, haxorg_File_vtable>::getSourceConst_const(OrgContext* org_context, haxorg_File self) {
  return org::bind::c::execute_cpp<haxorg_FileSource, haxorg_FileSource_vtable>(static_cast<org::sem::File::Source const&(org::sem::File::*)() const>(&org::sem::File::getSource), org_context, self);
}
haxorg_FileSource org::bind::c::VTable<haxorg_File, haxorg_File_vtable>::getSourceMut(OrgContext* org_context, haxorg_File self) {
  return org::bind::c::execute_cpp<haxorg_FileSource, haxorg_FileSource_vtable>(static_cast<org::sem::File::Source&(org::sem::File::*)()>(&org::sem::File::getSource), org_context, self);
}
haxorg_FileKind org::bind::c::VTable<haxorg_File, haxorg_File_vtable>::getFileKind_const(OrgContext* org_context, haxorg_File self) {
  return org::bind::c::execute_cpp<haxorg_FileKind, haxorg_builtin_vtable>(static_cast<org::sem::File::Kind(org::sem::File::*)() const>(&org::sem::File::getFileKind), org_context, self);
}
bool org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::isExample_const(OrgContext* org_context, haxorg_CmdInclude self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::isExample), org_context, self);
}
haxorg_CmdIncludeExample org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getExampleConst_const(OrgContext* org_context, haxorg_CmdInclude self) {
  return org::bind::c::execute_cpp<haxorg_CmdIncludeExample, haxorg_CmdIncludeExample_vtable>(static_cast<org::sem::CmdInclude::Example const&(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getExample), org_context, self);
}
haxorg_CmdIncludeExample org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getExampleMut(OrgContext* org_context, haxorg_CmdInclude self) {
  return org::bind::c::execute_cpp<haxorg_CmdIncludeExample, haxorg_CmdIncludeExample_vtable>(static_cast<org::sem::CmdInclude::Example&(org::sem::CmdInclude::*)()>(&org::sem::CmdInclude::getExample), org_context, self);
}
bool org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::isExport_const(OrgContext* org_context, haxorg_CmdInclude self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::isExport), org_context, self);
}
haxorg_CmdIncludeExport org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getExportConst_const(OrgContext* org_context, haxorg_CmdInclude self) {
  return org::bind::c::execute_cpp<haxorg_CmdIncludeExport, haxorg_CmdIncludeExport_vtable>(static_cast<org::sem::CmdInclude::Export const&(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getExport), org_context, self);
}
haxorg_CmdIncludeExport org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getExportMut(OrgContext* org_context, haxorg_CmdInclude self) {
  return org::bind::c::execute_cpp<haxorg_CmdIncludeExport, haxorg_CmdIncludeExport_vtable>(static_cast<org::sem::CmdInclude::Export&(org::sem::CmdInclude::*)()>(&org::sem::CmdInclude::getExport), org_context, self);
}
bool org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::isCustom_const(OrgContext* org_context, haxorg_CmdInclude self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::isCustom), org_context, self);
}
haxorg_CmdIncludeCustom org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getCustomConst_const(OrgContext* org_context, haxorg_CmdInclude self) {
  return org::bind::c::execute_cpp<haxorg_CmdIncludeCustom, haxorg_CmdIncludeCustom_vtable>(static_cast<org::sem::CmdInclude::Custom const&(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getCustom), org_context, self);
}
haxorg_CmdIncludeCustom org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getCustomMut(OrgContext* org_context, haxorg_CmdInclude self) {
  return org::bind::c::execute_cpp<haxorg_CmdIncludeCustom, haxorg_CmdIncludeCustom_vtable>(static_cast<org::sem::CmdInclude::Custom&(org::sem::CmdInclude::*)()>(&org::sem::CmdInclude::getCustom), org_context, self);
}
bool org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::isSrc_const(OrgContext* org_context, haxorg_CmdInclude self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::isSrc), org_context, self);
}
haxorg_CmdIncludeSrc org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getSrcConst_const(OrgContext* org_context, haxorg_CmdInclude self) {
  return org::bind::c::execute_cpp<haxorg_CmdIncludeSrc, haxorg_CmdIncludeSrc_vtable>(static_cast<org::sem::CmdInclude::Src const&(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getSrc), org_context, self);
}
haxorg_CmdIncludeSrc org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getSrcMut(OrgContext* org_context, haxorg_CmdInclude self) {
  return org::bind::c::execute_cpp<haxorg_CmdIncludeSrc, haxorg_CmdIncludeSrc_vtable>(static_cast<org::sem::CmdInclude::Src&(org::sem::CmdInclude::*)()>(&org::sem::CmdInclude::getSrc), org_context, self);
}
bool org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::isOrgDocument_const(OrgContext* org_context, haxorg_CmdInclude self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::isOrgDocument), org_context, self);
}
haxorg_CmdIncludeOrgDocument org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getOrgDocumentConst_const(OrgContext* org_context, haxorg_CmdInclude self) {
  return org::bind::c::execute_cpp<haxorg_CmdIncludeOrgDocument, haxorg_CmdIncludeOrgDocument_vtable>(static_cast<org::sem::CmdInclude::OrgDocument const&(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getOrgDocument), org_context, self);
}
haxorg_CmdIncludeOrgDocument org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getOrgDocumentMut(OrgContext* org_context, haxorg_CmdInclude self) {
  return org::bind::c::execute_cpp<haxorg_CmdIncludeOrgDocument, haxorg_CmdIncludeOrgDocument_vtable>(static_cast<org::sem::CmdInclude::OrgDocument&(org::sem::CmdInclude::*)()>(&org::sem::CmdInclude::getOrgDocument), org_context, self);
}
haxorg_CmdIncludeKind org::bind::c::VTable<haxorg_CmdInclude, haxorg_CmdInclude_vtable>::getIncludeKind_const(OrgContext* org_context, haxorg_CmdInclude self) {
  return org::bind::c::execute_cpp<haxorg_CmdIncludeKind, haxorg_builtin_vtable>(static_cast<org::sem::CmdInclude::Kind(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getIncludeKind), org_context, self);
}
bool org::bind::c::VTable<haxorg_CmdIncludeIncludeBase, haxorg_CmdIncludeIncludeBase_vtable>::__eq___const(OrgContext* org_context, haxorg_CmdIncludeIncludeBase self, haxorg_CmdIncludeIncludeBase other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::CmdInclude::IncludeBase::*)(org::sem::CmdInclude::IncludeBase const&) const>(&org::sem::CmdInclude::IncludeBase::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_CmdIncludeExample, haxorg_CmdIncludeExample_vtable>::__eq___const(OrgContext* org_context, haxorg_CmdIncludeExample self, haxorg_CmdIncludeExample other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::CmdInclude::Example::*)(org::sem::CmdInclude::Example const&) const>(&org::sem::CmdInclude::Example::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_CmdIncludeExport, haxorg_CmdIncludeExport_vtable>::__eq___const(OrgContext* org_context, haxorg_CmdIncludeExport self, haxorg_CmdIncludeExport other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::CmdInclude::Export::*)(org::sem::CmdInclude::Export const&) const>(&org::sem::CmdInclude::Export::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_CmdIncludeCustom, haxorg_CmdIncludeCustom_vtable>::__eq___const(OrgContext* org_context, haxorg_CmdIncludeCustom self, haxorg_CmdIncludeCustom other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::CmdInclude::Custom::*)(org::sem::CmdInclude::Custom const&) const>(&org::sem::CmdInclude::Custom::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_CmdIncludeSrc, haxorg_CmdIncludeSrc_vtable>::__eq___const(OrgContext* org_context, haxorg_CmdIncludeSrc self, haxorg_CmdIncludeSrc other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::CmdInclude::Src::*)(org::sem::CmdInclude::Src const&) const>(&org::sem::CmdInclude::Src::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_CmdIncludeOrgDocument, haxorg_CmdIncludeOrgDocument_vtable>::__eq___const(OrgContext* org_context, haxorg_CmdIncludeOrgDocument self, haxorg_CmdIncludeOrgDocument other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::CmdInclude::OrgDocument::*)(org::sem::CmdInclude::OrgDocument const&) const>(&org::sem::CmdInclude::OrgDocument::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmNoNode, haxorg_ImmNoNode_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmNoNode self, haxorg_ImmNoNode other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmNoNode::*)(org::imm::ImmNoNode const&) const>(&org::imm::ImmNoNode::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmErrorItem, haxorg_ImmErrorItem_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmErrorItem self, haxorg_ImmErrorItem other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmErrorItem::*)(org::imm::ImmErrorItem const&) const>(&org::imm::ImmErrorItem::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmErrorGroup, haxorg_ImmErrorGroup_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmErrorGroup self, haxorg_ImmErrorGroup other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmErrorGroup::*)(org::imm::ImmErrorGroup const&) const>(&org::imm::ImmErrorGroup::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmStmt, haxorg_ImmStmt_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmStmt self, haxorg_ImmStmt other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmStmt::*)(org::imm::ImmStmt const&) const>(&org::imm::ImmStmt::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmInline, haxorg_ImmInline_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmInline self, haxorg_ImmInline other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmInline::*)(org::imm::ImmInline const&) const>(&org::imm::ImmInline::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmStmtList, haxorg_ImmStmtList_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmStmtList self, haxorg_ImmStmtList other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmStmtList::*)(org::imm::ImmStmtList const&) const>(&org::imm::ImmStmtList::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmEmpty, haxorg_ImmEmpty_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmEmpty self, haxorg_ImmEmpty other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmEmpty::*)(org::imm::ImmEmpty const&) const>(&org::imm::ImmEmpty::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmLeaf, haxorg_ImmLeaf_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmLeaf self, haxorg_ImmLeaf other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmLeaf::*)(org::imm::ImmLeaf const&) const>(&org::imm::ImmLeaf::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmTime, haxorg_ImmTime_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmTime self, haxorg_ImmTime other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmTime::*)(org::imm::ImmTime const&) const>(&org::imm::ImmTime::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmTime, haxorg_ImmTime_vtable>::isStatic_const(OrgContext* org_context, haxorg_ImmTime self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmTime::*)() const>(&org::imm::ImmTime::isStatic), org_context, self);
}
haxorg_ImmTimeStatic org::bind::c::VTable<haxorg_ImmTime, haxorg_ImmTime_vtable>::getStaticConst_const(OrgContext* org_context, haxorg_ImmTime self) {
  return org::bind::c::execute_cpp<haxorg_ImmTimeStatic, haxorg_ImmTimeStatic_vtable>(static_cast<org::imm::ImmTime::Static const&(org::imm::ImmTime::*)() const>(&org::imm::ImmTime::getStatic), org_context, self);
}
haxorg_ImmTimeStatic org::bind::c::VTable<haxorg_ImmTime, haxorg_ImmTime_vtable>::getStaticMut(OrgContext* org_context, haxorg_ImmTime self) {
  return org::bind::c::execute_cpp<haxorg_ImmTimeStatic, haxorg_ImmTimeStatic_vtable>(static_cast<org::imm::ImmTime::Static&(org::imm::ImmTime::*)()>(&org::imm::ImmTime::getStatic), org_context, self);
}
bool org::bind::c::VTable<haxorg_ImmTime, haxorg_ImmTime_vtable>::isDynamic_const(OrgContext* org_context, haxorg_ImmTime self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmTime::*)() const>(&org::imm::ImmTime::isDynamic), org_context, self);
}
haxorg_ImmTimeDynamic org::bind::c::VTable<haxorg_ImmTime, haxorg_ImmTime_vtable>::getDynamicConst_const(OrgContext* org_context, haxorg_ImmTime self) {
  return org::bind::c::execute_cpp<haxorg_ImmTimeDynamic, haxorg_ImmTimeDynamic_vtable>(static_cast<org::imm::ImmTime::Dynamic const&(org::imm::ImmTime::*)() const>(&org::imm::ImmTime::getDynamic), org_context, self);
}
haxorg_ImmTimeDynamic org::bind::c::VTable<haxorg_ImmTime, haxorg_ImmTime_vtable>::getDynamicMut(OrgContext* org_context, haxorg_ImmTime self) {
  return org::bind::c::execute_cpp<haxorg_ImmTimeDynamic, haxorg_ImmTimeDynamic_vtable>(static_cast<org::imm::ImmTime::Dynamic&(org::imm::ImmTime::*)()>(&org::imm::ImmTime::getDynamic), org_context, self);
}
haxorg_ImmTimeTimeKind org::bind::c::VTable<haxorg_ImmTime, haxorg_ImmTime_vtable>::getTimeKind_const(OrgContext* org_context, haxorg_ImmTime self) {
  return org::bind::c::execute_cpp<haxorg_ImmTimeTimeKind, haxorg_builtin_vtable>(static_cast<org::imm::ImmTime::TimeKind(org::imm::ImmTime::*)() const>(&org::imm::ImmTime::getTimeKind), org_context, self);
}
bool org::bind::c::VTable<haxorg_ImmTimeRepeat, haxorg_ImmTimeRepeat_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmTimeRepeat self, haxorg_ImmTimeRepeat other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmTime::Repeat::*)(org::imm::ImmTime::Repeat const&) const>(&org::imm::ImmTime::Repeat::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmTimeStatic, haxorg_ImmTimeStatic_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmTimeStatic self, haxorg_ImmTimeStatic other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmTime::Static::*)(org::imm::ImmTime::Static const&) const>(&org::imm::ImmTime::Static::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmTimeDynamic, haxorg_ImmTimeDynamic_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmTimeDynamic self, haxorg_ImmTimeDynamic other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmTime::Dynamic::*)(org::imm::ImmTime::Dynamic const&) const>(&org::imm::ImmTime::Dynamic::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmTimeRange, haxorg_ImmTimeRange_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmTimeRange self, haxorg_ImmTimeRange other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmTimeRange::*)(org::imm::ImmTimeRange const&) const>(&org::imm::ImmTimeRange::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmMacro, haxorg_ImmMacro_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmMacro self, haxorg_ImmMacro other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmMacro::*)(org::imm::ImmMacro const&) const>(&org::imm::ImmMacro::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmSymbol, haxorg_ImmSymbol_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmSymbol self, haxorg_ImmSymbol other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmSymbol::*)(org::imm::ImmSymbol const&) const>(&org::imm::ImmSymbol::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmSymbolParam, haxorg_ImmSymbolParam_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmSymbolParam self, haxorg_ImmSymbolParam other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmSymbol::Param::*)(org::imm::ImmSymbol::Param const&) const>(&org::imm::ImmSymbol::Param::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmErrorSkipGroup, haxorg_ImmErrorSkipGroup_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmErrorSkipGroup self, haxorg_ImmErrorSkipGroup other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmErrorSkipGroup::*)(org::imm::ImmErrorSkipGroup const&) const>(&org::imm::ImmErrorSkipGroup::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmMarkup, haxorg_ImmMarkup_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmMarkup self, haxorg_ImmMarkup other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmMarkup::*)(org::imm::ImmMarkup const&) const>(&org::imm::ImmMarkup::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmRadioTarget, haxorg_ImmRadioTarget_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmRadioTarget self, haxorg_ImmRadioTarget other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmRadioTarget::*)(org::imm::ImmRadioTarget const&) const>(&org::imm::ImmRadioTarget::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmLatex, haxorg_ImmLatex_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmLatex self, haxorg_ImmLatex other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmLatex::*)(org::imm::ImmLatex const&) const>(&org::imm::ImmLatex::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmSubtreeLog, haxorg_ImmSubtreeLog_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmSubtreeLog self, haxorg_ImmSubtreeLog other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmSubtreeLog::*)(org::imm::ImmSubtreeLog const&) const>(&org::imm::ImmSubtreeLog::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmSubtree, haxorg_ImmSubtree_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmSubtree self, haxorg_ImmSubtree other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmSubtree::*)(org::imm::ImmSubtree const&) const>(&org::imm::ImmSubtree::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmColonExample, haxorg_ImmColonExample_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmColonExample self, haxorg_ImmColonExample other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmColonExample::*)(org::imm::ImmColonExample const&) const>(&org::imm::ImmColonExample::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmCall, haxorg_ImmCall_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmCall self, haxorg_ImmCall other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmCall::*)(org::imm::ImmCall const&) const>(&org::imm::ImmCall::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmListItem, haxorg_ImmListItem_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmListItem self, haxorg_ImmListItem other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmListItem::*)(org::imm::ImmListItem const&) const>(&org::imm::ImmListItem::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmDocumentOptions, haxorg_ImmDocumentOptions_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmDocumentOptions self, haxorg_ImmDocumentOptions other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmDocumentOptions::*)(org::imm::ImmDocumentOptions const&) const>(&org::imm::ImmDocumentOptions::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmDocumentFragment, haxorg_ImmDocumentFragment_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmDocumentFragment self, haxorg_ImmDocumentFragment other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmDocumentFragment::*)(org::imm::ImmDocumentFragment const&) const>(&org::imm::ImmDocumentFragment::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmCriticMarkup, haxorg_ImmCriticMarkup_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmCriticMarkup self, haxorg_ImmCriticMarkup other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmCriticMarkup::*)(org::imm::ImmCriticMarkup const&) const>(&org::imm::ImmCriticMarkup::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmDocument, haxorg_ImmDocument_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmDocument self, haxorg_ImmDocument other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmDocument::*)(org::imm::ImmDocument const&) const>(&org::imm::ImmDocument::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmFileTarget, haxorg_ImmFileTarget_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmFileTarget self, haxorg_ImmFileTarget other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmFileTarget::*)(org::imm::ImmFileTarget const&) const>(&org::imm::ImmFileTarget::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmTextSeparator, haxorg_ImmTextSeparator_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmTextSeparator self, haxorg_ImmTextSeparator other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmTextSeparator::*)(org::imm::ImmTextSeparator const&) const>(&org::imm::ImmTextSeparator::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmDocumentGroup, haxorg_ImmDocumentGroup_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmDocumentGroup self, haxorg_ImmDocumentGroup other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmDocumentGroup::*)(org::imm::ImmDocumentGroup const&) const>(&org::imm::ImmDocumentGroup::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmFile self, haxorg_ImmFile other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmFile::*)(org::imm::ImmFile const&) const>(&org::imm::ImmFile::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::isDocument_const(OrgContext* org_context, haxorg_ImmFile self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmFile::*)() const>(&org::imm::ImmFile::isDocument), org_context, self);
}
haxorg_ImmFileDocument org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::getDocumentConst_const(OrgContext* org_context, haxorg_ImmFile self) {
  return org::bind::c::execute_cpp<haxorg_ImmFileDocument, haxorg_ImmFileDocument_vtable>(static_cast<org::imm::ImmFile::Document const&(org::imm::ImmFile::*)() const>(&org::imm::ImmFile::getDocument), org_context, self);
}
haxorg_ImmFileDocument org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::getDocumentMut(OrgContext* org_context, haxorg_ImmFile self) {
  return org::bind::c::execute_cpp<haxorg_ImmFileDocument, haxorg_ImmFileDocument_vtable>(static_cast<org::imm::ImmFile::Document&(org::imm::ImmFile::*)()>(&org::imm::ImmFile::getDocument), org_context, self);
}
bool org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::isAttachment_const(OrgContext* org_context, haxorg_ImmFile self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmFile::*)() const>(&org::imm::ImmFile::isAttachment), org_context, self);
}
haxorg_ImmFileAttachment org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::getAttachmentConst_const(OrgContext* org_context, haxorg_ImmFile self) {
  return org::bind::c::execute_cpp<haxorg_ImmFileAttachment, haxorg_ImmFileAttachment_vtable>(static_cast<org::imm::ImmFile::Attachment const&(org::imm::ImmFile::*)() const>(&org::imm::ImmFile::getAttachment), org_context, self);
}
haxorg_ImmFileAttachment org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::getAttachmentMut(OrgContext* org_context, haxorg_ImmFile self) {
  return org::bind::c::execute_cpp<haxorg_ImmFileAttachment, haxorg_ImmFileAttachment_vtable>(static_cast<org::imm::ImmFile::Attachment&(org::imm::ImmFile::*)()>(&org::imm::ImmFile::getAttachment), org_context, self);
}
bool org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::isSource_const(OrgContext* org_context, haxorg_ImmFile self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmFile::*)() const>(&org::imm::ImmFile::isSource), org_context, self);
}
haxorg_ImmFileSource org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::getSourceConst_const(OrgContext* org_context, haxorg_ImmFile self) {
  return org::bind::c::execute_cpp<haxorg_ImmFileSource, haxorg_ImmFileSource_vtable>(static_cast<org::imm::ImmFile::Source const&(org::imm::ImmFile::*)() const>(&org::imm::ImmFile::getSource), org_context, self);
}
haxorg_ImmFileSource org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::getSourceMut(OrgContext* org_context, haxorg_ImmFile self) {
  return org::bind::c::execute_cpp<haxorg_ImmFileSource, haxorg_ImmFileSource_vtable>(static_cast<org::imm::ImmFile::Source&(org::imm::ImmFile::*)()>(&org::imm::ImmFile::getSource), org_context, self);
}
haxorg_ImmFileKind org::bind::c::VTable<haxorg_ImmFile, haxorg_ImmFile_vtable>::getFileKind_const(OrgContext* org_context, haxorg_ImmFile self) {
  return org::bind::c::execute_cpp<haxorg_ImmFileKind, haxorg_builtin_vtable>(static_cast<org::imm::ImmFile::Kind(org::imm::ImmFile::*)() const>(&org::imm::ImmFile::getFileKind), org_context, self);
}
bool org::bind::c::VTable<haxorg_ImmFileDocument, haxorg_ImmFileDocument_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmFileDocument self, haxorg_ImmFileDocument other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmFile::Document::*)(org::imm::ImmFile::Document const&) const>(&org::imm::ImmFile::Document::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmFileAttachment, haxorg_ImmFileAttachment_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmFileAttachment self, haxorg_ImmFileAttachment other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmFile::Attachment::*)(org::imm::ImmFile::Attachment const&) const>(&org::imm::ImmFile::Attachment::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmFileSource, haxorg_ImmFileSource_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmFileSource self, haxorg_ImmFileSource other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmFile::Source::*)(org::imm::ImmFile::Source const&) const>(&org::imm::ImmFile::Source::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmDirectory, haxorg_ImmDirectory_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmDirectory self, haxorg_ImmDirectory other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmDirectory::*)(org::imm::ImmDirectory const&) const>(&org::imm::ImmDirectory::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmSymlink, haxorg_ImmSymlink_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmSymlink self, haxorg_ImmSymlink other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmSymlink::*)(org::imm::ImmSymlink const&) const>(&org::imm::ImmSymlink::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmCmdInclude self, haxorg_ImmCmdInclude other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmCmdInclude::*)(org::imm::ImmCmdInclude const&) const>(&org::imm::ImmCmdInclude::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::isExample_const(OrgContext* org_context, haxorg_ImmCmdInclude self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::isExample), org_context, self);
}
haxorg_ImmCmdIncludeExample org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getExampleConst_const(OrgContext* org_context, haxorg_ImmCmdInclude self) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeExample, haxorg_ImmCmdIncludeExample_vtable>(static_cast<org::imm::ImmCmdInclude::Example const&(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::getExample), org_context, self);
}
haxorg_ImmCmdIncludeExample org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getExampleMut(OrgContext* org_context, haxorg_ImmCmdInclude self) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeExample, haxorg_ImmCmdIncludeExample_vtable>(static_cast<org::imm::ImmCmdInclude::Example&(org::imm::ImmCmdInclude::*)()>(&org::imm::ImmCmdInclude::getExample), org_context, self);
}
bool org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::isExport_const(OrgContext* org_context, haxorg_ImmCmdInclude self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::isExport), org_context, self);
}
haxorg_ImmCmdIncludeExport org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getExportConst_const(OrgContext* org_context, haxorg_ImmCmdInclude self) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeExport, haxorg_ImmCmdIncludeExport_vtable>(static_cast<org::imm::ImmCmdInclude::Export const&(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::getExport), org_context, self);
}
haxorg_ImmCmdIncludeExport org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getExportMut(OrgContext* org_context, haxorg_ImmCmdInclude self) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeExport, haxorg_ImmCmdIncludeExport_vtable>(static_cast<org::imm::ImmCmdInclude::Export&(org::imm::ImmCmdInclude::*)()>(&org::imm::ImmCmdInclude::getExport), org_context, self);
}
bool org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::isCustom_const(OrgContext* org_context, haxorg_ImmCmdInclude self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::isCustom), org_context, self);
}
haxorg_ImmCmdIncludeCustom org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getCustomConst_const(OrgContext* org_context, haxorg_ImmCmdInclude self) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeCustom, haxorg_ImmCmdIncludeCustom_vtable>(static_cast<org::imm::ImmCmdInclude::Custom const&(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::getCustom), org_context, self);
}
haxorg_ImmCmdIncludeCustom org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getCustomMut(OrgContext* org_context, haxorg_ImmCmdInclude self) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeCustom, haxorg_ImmCmdIncludeCustom_vtable>(static_cast<org::imm::ImmCmdInclude::Custom&(org::imm::ImmCmdInclude::*)()>(&org::imm::ImmCmdInclude::getCustom), org_context, self);
}
bool org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::isSrc_const(OrgContext* org_context, haxorg_ImmCmdInclude self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::isSrc), org_context, self);
}
haxorg_ImmCmdIncludeSrc org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getSrcConst_const(OrgContext* org_context, haxorg_ImmCmdInclude self) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeSrc, haxorg_ImmCmdIncludeSrc_vtable>(static_cast<org::imm::ImmCmdInclude::Src const&(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::getSrc), org_context, self);
}
haxorg_ImmCmdIncludeSrc org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getSrcMut(OrgContext* org_context, haxorg_ImmCmdInclude self) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeSrc, haxorg_ImmCmdIncludeSrc_vtable>(static_cast<org::imm::ImmCmdInclude::Src&(org::imm::ImmCmdInclude::*)()>(&org::imm::ImmCmdInclude::getSrc), org_context, self);
}
bool org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::isOrgDocument_const(OrgContext* org_context, haxorg_ImmCmdInclude self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::isOrgDocument), org_context, self);
}
haxorg_ImmCmdIncludeOrgDocument org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getOrgDocumentConst_const(OrgContext* org_context, haxorg_ImmCmdInclude self) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeOrgDocument, haxorg_ImmCmdIncludeOrgDocument_vtable>(static_cast<org::imm::ImmCmdInclude::OrgDocument const&(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::getOrgDocument), org_context, self);
}
haxorg_ImmCmdIncludeOrgDocument org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getOrgDocumentMut(OrgContext* org_context, haxorg_ImmCmdInclude self) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeOrgDocument, haxorg_ImmCmdIncludeOrgDocument_vtable>(static_cast<org::imm::ImmCmdInclude::OrgDocument&(org::imm::ImmCmdInclude::*)()>(&org::imm::ImmCmdInclude::getOrgDocument), org_context, self);
}
haxorg_ImmCmdIncludeKind org::bind::c::VTable<haxorg_ImmCmdInclude, haxorg_ImmCmdInclude_vtable>::getIncludeKind_const(OrgContext* org_context, haxorg_ImmCmdInclude self) {
  return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeKind, haxorg_builtin_vtable>(static_cast<org::imm::ImmCmdInclude::Kind(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::getIncludeKind), org_context, self);
}
bool org::bind::c::VTable<haxorg_ImmCmdIncludeIncludeBase, haxorg_ImmCmdIncludeIncludeBase_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmCmdIncludeIncludeBase self, haxorg_ImmCmdIncludeIncludeBase other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmCmdInclude::IncludeBase::*)(org::imm::ImmCmdInclude::IncludeBase const&) const>(&org::imm::ImmCmdInclude::IncludeBase::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdIncludeExample, haxorg_ImmCmdIncludeExample_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmCmdIncludeExample self, haxorg_ImmCmdIncludeExample other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmCmdInclude::Example::*)(org::imm::ImmCmdInclude::Example const&) const>(&org::imm::ImmCmdInclude::Example::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdIncludeExport, haxorg_ImmCmdIncludeExport_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmCmdIncludeExport self, haxorg_ImmCmdIncludeExport other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmCmdInclude::Export::*)(org::imm::ImmCmdInclude::Export const&) const>(&org::imm::ImmCmdInclude::Export::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdIncludeCustom, haxorg_ImmCmdIncludeCustom_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmCmdIncludeCustom self, haxorg_ImmCmdIncludeCustom other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmCmdInclude::Custom::*)(org::imm::ImmCmdInclude::Custom const&) const>(&org::imm::ImmCmdInclude::Custom::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdIncludeSrc, haxorg_ImmCmdIncludeSrc_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmCmdIncludeSrc self, haxorg_ImmCmdIncludeSrc other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmCmdInclude::Src::*)(org::imm::ImmCmdInclude::Src const&) const>(&org::imm::ImmCmdInclude::Src::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdIncludeOrgDocument, haxorg_ImmCmdIncludeOrgDocument_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmCmdIncludeOrgDocument self, haxorg_ImmCmdIncludeOrgDocument other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmCmdInclude::OrgDocument::*)(org::imm::ImmCmdInclude::OrgDocument const&) const>(&org::imm::ImmCmdInclude::OrgDocument::operator==), org_context, self, other);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Cmd, haxorg_Cmd_vtable>::getAttrs_const(OrgContext* org_context, haxorg_Cmd self, haxorg_HstdOpt key) {
  return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Cmd::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Cmd::getAttrs), org_context, self, key);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Cmd, haxorg_Cmd_vtable>::getFirstAttr_const(OrgContext* org_context, haxorg_Cmd self, haxorg_HstdStr kind) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Cmd::*)(hstd::Str const&) const>(&org::sem::Cmd::getFirstAttr), org_context, self, kind);
}
bool org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::isFootnoteDefinition_const(OrgContext* org_context, haxorg_Paragraph self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::isFootnoteDefinition), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::getFootnoteName_const(OrgContext* org_context, haxorg_Paragraph self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<hstd::Str>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getFootnoteName), org_context, self);
}
bool org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::hasAdmonition_const(OrgContext* org_context, haxorg_Paragraph self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::hasAdmonition), org_context, self);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::getAdmonitions_const(OrgContext* org_context, haxorg_Paragraph self) {
  return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<hstd::Str>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getAdmonitions), org_context, self);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::getAdmonitionNodes_const(OrgContext* org_context, haxorg_Paragraph self) {
  return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<org::sem::SemId<org::sem::BigIdent>>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getAdmonitionNodes), org_context, self);
}
bool org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::hasTimestamp_const(OrgContext* org_context, haxorg_Paragraph self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::hasTimestamp), org_context, self);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::getTimestamps_const(OrgContext* org_context, haxorg_Paragraph self) {
  return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<hstd::UserTime>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getTimestamps), org_context, self);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::getTimestampNodes_const(OrgContext* org_context, haxorg_Paragraph self) {
  return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<org::sem::SemId<org::sem::Time>>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getTimestampNodes), org_context, self);
}
bool org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::hasLeadHashtags_const(OrgContext* org_context, haxorg_Paragraph self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::hasLeadHashtags), org_context, self);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::getLeadHashtags_const(OrgContext* org_context, haxorg_Paragraph self) {
  return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<org::sem::SemId<org::sem::HashTag>>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getLeadHashtags), org_context, self);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_Paragraph, haxorg_Paragraph_vtable>::getBody_const(OrgContext* org_context, haxorg_Paragraph self) {
  return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getBody), org_context, self);
}
haxorg_HstdVec org::bind::c::VTable<haxorg_List, haxorg_List_vtable>::getListAttrs_const(OrgContext* org_context, haxorg_List self, haxorg_HstdStr key) {
  return org::bind::c::execute_cpp<haxorg_HstdVec, haxorg_HstdVec_vtable>(static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::List::*)(hstd::Str const&) const>(&org::sem::List::getListAttrs), org_context, self, key);
}
haxorg_ListFormattingMode org::bind::c::VTable<haxorg_List, haxorg_List_vtable>::getListFormattingMode_const(OrgContext* org_context, haxorg_List self) {
  return org::bind::c::execute_cpp<haxorg_ListFormattingMode, haxorg_builtin_vtable>(static_cast<ListFormattingMode(org::sem::List::*)() const>(&org::sem::List::getListFormattingMode), org_context, self);
}
bool org::bind::c::VTable<haxorg_List, haxorg_List_vtable>::isDescriptionList_const(OrgContext* org_context, haxorg_List self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::List::*)() const>(&org::sem::List::isDescriptionList), org_context, self);
}
bool org::bind::c::VTable<haxorg_List, haxorg_List_vtable>::isNumberedList_const(OrgContext* org_context, haxorg_List self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::sem::List::*)() const>(&org::sem::List::isNumberedList), org_context, self);
}
bool org::bind::c::VTable<haxorg_ImmCmd, haxorg_ImmCmd_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmCmd self, haxorg_ImmCmd other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmCmd::*)(org::imm::ImmCmd const&) const>(&org::imm::ImmCmd::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdCustomRaw, haxorg_ImmCmdCustomRaw_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmCmdCustomRaw self, haxorg_ImmCmdCustomRaw other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmCmdCustomRaw::*)(org::imm::ImmCmdCustomRaw const&) const>(&org::imm::ImmCmdCustomRaw::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdCustomText, haxorg_ImmCmdCustomText_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmCmdCustomText self, haxorg_ImmCmdCustomText other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmCmdCustomText::*)(org::imm::ImmCmdCustomText const&) const>(&org::imm::ImmCmdCustomText::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmLink, haxorg_ImmLink_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmLink self, haxorg_ImmLink other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmLink::*)(org::imm::ImmLink const&) const>(&org::imm::ImmLink::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmBlockComment, haxorg_ImmBlockComment_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmBlockComment self, haxorg_ImmBlockComment other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmBlockComment::*)(org::imm::ImmBlockComment const&) const>(&org::imm::ImmBlockComment::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmParagraph, haxorg_ImmParagraph_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmParagraph self, haxorg_ImmParagraph other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmParagraph::*)(org::imm::ImmParagraph const&) const>(&org::imm::ImmParagraph::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmList, haxorg_ImmList_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmList self, haxorg_ImmList other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmList::*)(org::imm::ImmList const&) const>(&org::imm::ImmList::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmHashTag, haxorg_ImmHashTag_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmHashTag self, haxorg_ImmHashTag other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmHashTag::*)(org::imm::ImmHashTag const&) const>(&org::imm::ImmHashTag::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmInlineFootnote, haxorg_ImmInlineFootnote_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmInlineFootnote self, haxorg_ImmInlineFootnote other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmInlineFootnote::*)(org::imm::ImmInlineFootnote const&) const>(&org::imm::ImmInlineFootnote::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmInlineExport, haxorg_ImmInlineExport_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmInlineExport self, haxorg_ImmInlineExport other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmInlineExport::*)(org::imm::ImmInlineExport const&) const>(&org::imm::ImmInlineExport::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmEscaped, haxorg_ImmEscaped_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmEscaped self, haxorg_ImmEscaped other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmEscaped::*)(org::imm::ImmEscaped const&) const>(&org::imm::ImmEscaped::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmNewline, haxorg_ImmNewline_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmNewline self, haxorg_ImmNewline other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmNewline::*)(org::imm::ImmNewline const&) const>(&org::imm::ImmNewline::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmSpace, haxorg_ImmSpace_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmSpace self, haxorg_ImmSpace other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmSpace::*)(org::imm::ImmSpace const&) const>(&org::imm::ImmSpace::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmWord, haxorg_ImmWord_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmWord self, haxorg_ImmWord other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmWord::*)(org::imm::ImmWord const&) const>(&org::imm::ImmWord::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmAtMention, haxorg_ImmAtMention_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmAtMention self, haxorg_ImmAtMention other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmAtMention::*)(org::imm::ImmAtMention const&) const>(&org::imm::ImmAtMention::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmRawText, haxorg_ImmRawText_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmRawText self, haxorg_ImmRawText other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmRawText::*)(org::imm::ImmRawText const&) const>(&org::imm::ImmRawText::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmPunctuation, haxorg_ImmPunctuation_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmPunctuation self, haxorg_ImmPunctuation other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmPunctuation::*)(org::imm::ImmPunctuation const&) const>(&org::imm::ImmPunctuation::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmPlaceholder, haxorg_ImmPlaceholder_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmPlaceholder self, haxorg_ImmPlaceholder other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmPlaceholder::*)(org::imm::ImmPlaceholder const&) const>(&org::imm::ImmPlaceholder::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmBigIdent, haxorg_ImmBigIdent_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmBigIdent self, haxorg_ImmBigIdent other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmBigIdent::*)(org::imm::ImmBigIdent const&) const>(&org::imm::ImmBigIdent::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmTextTarget, haxorg_ImmTextTarget_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmTextTarget self, haxorg_ImmTextTarget other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmTextTarget::*)(org::imm::ImmTextTarget const&) const>(&org::imm::ImmTextTarget::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmErrorSkipToken, haxorg_ImmErrorSkipToken_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmErrorSkipToken self, haxorg_ImmErrorSkipToken other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmErrorSkipToken::*)(org::imm::ImmErrorSkipToken const&) const>(&org::imm::ImmErrorSkipToken::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmBold, haxorg_ImmBold_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmBold self, haxorg_ImmBold other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmBold::*)(org::imm::ImmBold const&) const>(&org::imm::ImmBold::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmUnderline, haxorg_ImmUnderline_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmUnderline self, haxorg_ImmUnderline other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmUnderline::*)(org::imm::ImmUnderline const&) const>(&org::imm::ImmUnderline::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmMonospace, haxorg_ImmMonospace_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmMonospace self, haxorg_ImmMonospace other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmMonospace::*)(org::imm::ImmMonospace const&) const>(&org::imm::ImmMonospace::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmMarkQuote, haxorg_ImmMarkQuote_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmMarkQuote self, haxorg_ImmMarkQuote other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmMarkQuote::*)(org::imm::ImmMarkQuote const&) const>(&org::imm::ImmMarkQuote::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmVerbatim, haxorg_ImmVerbatim_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmVerbatim self, haxorg_ImmVerbatim other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmVerbatim::*)(org::imm::ImmVerbatim const&) const>(&org::imm::ImmVerbatim::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmItalic, haxorg_ImmItalic_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmItalic self, haxorg_ImmItalic other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmItalic::*)(org::imm::ImmItalic const&) const>(&org::imm::ImmItalic::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmStrike, haxorg_ImmStrike_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmStrike self, haxorg_ImmStrike other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmStrike::*)(org::imm::ImmStrike const&) const>(&org::imm::ImmStrike::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmPar, haxorg_ImmPar_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmPar self, haxorg_ImmPar other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmPar::*)(org::imm::ImmPar const&) const>(&org::imm::ImmPar::operator==), org_context, self, other);
}
haxorg_StdOptional org::bind::c::VTable<haxorg_ImmAdapterDirectoryAPI, haxorg_ImmAdapterDirectoryAPI_vtable>::getFsSubnode_const(OrgContext* org_context, haxorg_ImmAdapterDirectoryAPI self, haxorg_HstdStr name, bool withPath) {
  return org::bind::c::execute_cpp<haxorg_StdOptional, haxorg_StdOptional_vtable>(static_cast<std::optional<org::imm::ImmAdapter>(org::imm::ImmAdapterDirectoryAPI::*)(hstd::Str const&, bool) const>(&org::imm::ImmAdapterDirectoryAPI::getFsSubnode), org_context, self, name, withPath);
}
bool org::bind::c::VTable<haxorg_ImmBlock, haxorg_ImmBlock_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmBlock self, haxorg_ImmBlock other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmBlock::*)(org::imm::ImmBlock const&) const>(&org::imm::ImmBlock::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmLineCommand, haxorg_ImmLineCommand_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmLineCommand self, haxorg_ImmLineCommand other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmLineCommand::*)(org::imm::ImmLineCommand const&) const>(&org::imm::ImmLineCommand::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdCreator, haxorg_ImmCmdCreator_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmCmdCreator self, haxorg_ImmCmdCreator other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmCmdCreator::*)(org::imm::ImmCmdCreator const&) const>(&org::imm::ImmCmdCreator::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdAuthor, haxorg_ImmCmdAuthor_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmCmdAuthor self, haxorg_ImmCmdAuthor other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmCmdAuthor::*)(org::imm::ImmCmdAuthor const&) const>(&org::imm::ImmCmdAuthor::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdEmail, haxorg_ImmCmdEmail_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmCmdEmail self, haxorg_ImmCmdEmail other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmCmdEmail::*)(org::imm::ImmCmdEmail const&) const>(&org::imm::ImmCmdEmail::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdLanguage, haxorg_ImmCmdLanguage_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmCmdLanguage self, haxorg_ImmCmdLanguage other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmCmdLanguage::*)(org::imm::ImmCmdLanguage const&) const>(&org::imm::ImmCmdLanguage::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdCustomArgs, haxorg_ImmCmdCustomArgs_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmCmdCustomArgs self, haxorg_ImmCmdCustomArgs other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmCmdCustomArgs::*)(org::imm::ImmCmdCustomArgs const&) const>(&org::imm::ImmCmdCustomArgs::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdTblfm, haxorg_ImmCmdTblfm_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmCmdTblfm self, haxorg_ImmCmdTblfm other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmCmdTblfm::*)(org::imm::ImmCmdTblfm const&) const>(&org::imm::ImmCmdTblfm::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmCell, haxorg_ImmCell_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmCell self, haxorg_ImmCell other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmCell::*)(org::imm::ImmCell const&) const>(&org::imm::ImmCell::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmRow, haxorg_ImmRow_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmRow self, haxorg_ImmRow other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmRow::*)(org::imm::ImmRow const&) const>(&org::imm::ImmRow::operator==), org_context, self, other);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmStmtAdapter, haxorg_ImmStmtAdapter_vtable>::getAttached_const(OrgContext* org_context, haxorg_ImmStmtAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmVec, haxorg_ImmVec_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg>>(org::imm::ImmAdapterT<org::imm::ImmStmt>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmStmt>::getAttached), org_context, self);
}
int org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getLevel_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter self) {
  return org::bind::c::execute_cpp<int, haxorg_builtin_vtable>(static_cast<int(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getLevel), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getTreeId_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getTreeId), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getTodo_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getTodo), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getCompletion_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<org::sem::SubtreeCompletion> const&(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getCompletion), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getDescription_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getDescription), org_context, self);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getTags_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmVec, haxorg_ImmVec_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag>>(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getTags), org_context, self);
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getTitle_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getTitle), org_context, self);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getLogbook_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmVec, haxorg_ImmVec_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmSubtreeLog>>(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getLogbook), org_context, self);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getProperties_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmVec, haxorg_ImmVec_vtable>(static_cast<hstd::ext::ImmVec<org::sem::NamedProperty>(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getProperties), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getClosed_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime>>(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getClosed), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getDeadline_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime>>(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getDeadline), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getScheduled_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime>>(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getScheduled), org_context, self);
}
bool org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getIsComment_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getIsComment), org_context, self);
}
bool org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getIsArchived_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getIsArchived), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmSubtreeAdapter, haxorg_ImmSubtreeAdapter_vtable>::getPriority_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getPriority), org_context, self);
}
haxorg_OrgDiagnostics org::bind::c::VTable<haxorg_ImmErrorItemAdapter, haxorg_ImmErrorItemAdapter_vtable>::getDiag_const(OrgContext* org_context, haxorg_ImmErrorItemAdapter self) {
  return org::bind::c::execute_cpp<haxorg_OrgDiagnostics, haxorg_OrgDiagnostics_vtable>(static_cast<org::sem::OrgDiagnostics(org::imm::ImmAdapterT<org::imm::ImmErrorItem>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmErrorItem>::getDiag), org_context, self);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmErrorGroupAdapter, haxorg_ImmErrorGroupAdapter_vtable>::getDiagnostics_const(OrgContext* org_context, haxorg_ImmErrorGroupAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmVec, haxorg_ImmVec_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorItem>>(org::imm::ImmAdapterT<org::imm::ImmErrorGroup>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmErrorGroup>::getDiagnostics), org_context, self);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmErrorSkipGroupAdapter, haxorg_ImmErrorSkipGroupAdapter_vtable>::getSkipped_const(OrgContext* org_context, haxorg_ImmErrorSkipGroupAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmVec, haxorg_ImmVec_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorSkipToken>>(org::imm::ImmAdapterT<org::imm::ImmErrorSkipGroup>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmErrorSkipGroup>::getSkipped), org_context, self);
}
bool org::bind::c::VTable<haxorg_ImmTimeAdapter, haxorg_ImmTimeAdapter_vtable>::getIsActive_const(OrgContext* org_context, haxorg_ImmTimeAdapter self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmTime>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTime>::getIsActive), org_context, self);
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmTimeRangeAdapter, haxorg_ImmTimeRangeAdapter_vtable>::getFrom_const(OrgContext* org_context, haxorg_ImmTimeRangeAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmTimeRange>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTimeRange>::getFrom), org_context, self);
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmTimeRangeAdapter, haxorg_ImmTimeRangeAdapter_vtable>::getTo_const(OrgContext* org_context, haxorg_ImmTimeRangeAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmTimeRange>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTimeRange>::getTo), org_context, self);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmMacroAdapter, haxorg_ImmMacroAdapter_vtable>::getName_const(OrgContext* org_context, haxorg_ImmMacroAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmMacro>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmMacro>::getName), org_context, self);
}
haxorg_AttrGroup org::bind::c::VTable<haxorg_ImmMacroAdapter, haxorg_ImmMacroAdapter_vtable>::getAttrs_const(OrgContext* org_context, haxorg_ImmMacroAdapter self) {
  return org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmMacro>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmMacro>::getAttrs), org_context, self);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmSymbolAdapter, haxorg_ImmSymbolAdapter_vtable>::getName_const(OrgContext* org_context, haxorg_ImmSymbolAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmSymbol>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymbol>::getName), org_context, self);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmSymbolAdapter, haxorg_ImmSymbolAdapter_vtable>::getParameters_const(OrgContext* org_context, haxorg_ImmSymbolAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmVec, haxorg_ImmVec_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmSymbol::Param>(org::imm::ImmAdapterT<org::imm::ImmSymbol>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymbol>::getParameters), org_context, self);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmSymbolAdapter, haxorg_ImmSymbolAdapter_vtable>::getPositional_const(OrgContext* org_context, haxorg_ImmSymbolAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmVec, haxorg_ImmVec_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg>>(org::imm::ImmAdapterT<org::imm::ImmSymbol>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymbol>::getPositional), org_context, self);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmLeafAdapter, haxorg_ImmLeafAdapter_vtable>::getText_const(OrgContext* org_context, haxorg_ImmLeafAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmLeaf>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmLeaf>::getText), org_context, self);
}
haxorg_SubtreeLogHead org::bind::c::VTable<haxorg_ImmSubtreeLogAdapter, haxorg_ImmSubtreeLogAdapter_vtable>::getHead_const(OrgContext* org_context, haxorg_ImmSubtreeLogAdapter self) {
  return org::bind::c::execute_cpp<haxorg_SubtreeLogHead, haxorg_SubtreeLogHead_vtable>(static_cast<org::sem::SubtreeLogHead(org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>::getHead), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmSubtreeLogAdapter, haxorg_ImmSubtreeLogAdapter_vtable>::getDesc_const(OrgContext* org_context, haxorg_ImmSubtreeLogAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmStmtList>>(org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>::getDesc), org_context, self);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCallAdapter, haxorg_ImmCallAdapter_vtable>::getName_const(OrgContext* org_context, haxorg_ImmCallAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCall>::getName), org_context, self);
}
haxorg_AttrGroup org::bind::c::VTable<haxorg_ImmCallAdapter, haxorg_ImmCallAdapter_vtable>::getAttrs_const(OrgContext* org_context, haxorg_ImmCallAdapter self) {
  return org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCall>::getAttrs), org_context, self);
}
bool org::bind::c::VTable<haxorg_ImmCallAdapter, haxorg_ImmCallAdapter_vtable>::getIsCommand_const(OrgContext* org_context, haxorg_ImmCallAdapter self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCall>::getIsCommand), org_context, self);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmFileAdapter, haxorg_ImmFileAdapter_vtable>::getRelPath_const(OrgContext* org_context, haxorg_ImmFileAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmFile>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFile>::getRelPath), org_context, self);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmFileAdapter, haxorg_ImmFileAdapter_vtable>::getAbsPath_const(OrgContext* org_context, haxorg_ImmFileAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmFile>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFile>::getAbsPath), org_context, self);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmDirectoryAdapter, haxorg_ImmDirectoryAdapter_vtable>::getRelPath_const(OrgContext* org_context, haxorg_ImmDirectoryAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmDirectory>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDirectory>::getRelPath), org_context, self);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmDirectoryAdapter, haxorg_ImmDirectoryAdapter_vtable>::getAbsPath_const(OrgContext* org_context, haxorg_ImmDirectoryAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmDirectory>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDirectory>::getAbsPath), org_context, self);
}
bool org::bind::c::VTable<haxorg_ImmSymlinkAdapter, haxorg_ImmSymlinkAdapter_vtable>::getIsDirectory_const(OrgContext* org_context, haxorg_ImmSymlinkAdapter self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmSymlink>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymlink>::getIsDirectory), org_context, self);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmSymlinkAdapter, haxorg_ImmSymlinkAdapter_vtable>::getAbsPath_const(OrgContext* org_context, haxorg_ImmSymlinkAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmSymlink>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymlink>::getAbsPath), org_context, self);
}
int org::bind::c::VTable<haxorg_ImmDocumentFragmentAdapter, haxorg_ImmDocumentFragmentAdapter_vtable>::getBaseLine_const(OrgContext* org_context, haxorg_ImmDocumentFragmentAdapter self) {
  return org::bind::c::execute_cpp<int, haxorg_builtin_vtable>(static_cast<int(org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>::getBaseLine), org_context, self);
}
int org::bind::c::VTable<haxorg_ImmDocumentFragmentAdapter, haxorg_ImmDocumentFragmentAdapter_vtable>::getBaseCol_const(OrgContext* org_context, haxorg_ImmDocumentFragmentAdapter self) {
  return org::bind::c::execute_cpp<int, haxorg_builtin_vtable>(static_cast<int(org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>::getBaseCol), org_context, self);
}
haxorg_ImmCriticMarkupKind org::bind::c::VTable<haxorg_ImmCriticMarkupAdapter, haxorg_ImmCriticMarkupAdapter_vtable>::getKind_const(OrgContext* org_context, haxorg_ImmCriticMarkupAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmCriticMarkupKind, haxorg_builtin_vtable>(static_cast<org::imm::ImmCriticMarkup::Kind(org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>::getKind), org_context, self);
}
haxorg_CheckboxState org::bind::c::VTable<haxorg_ImmListItemAdapter, haxorg_ImmListItemAdapter_vtable>::getCheckbox_const(OrgContext* org_context, haxorg_ImmListItemAdapter self) {
  return org::bind::c::execute_cpp<haxorg_CheckboxState, haxorg_builtin_vtable>(static_cast<CheckboxState(org::imm::ImmAdapterT<org::imm::ImmListItem>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmListItem>::getCheckbox), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmListItemAdapter, haxorg_ImmListItemAdapter_vtable>::getHeader_const(OrgContext* org_context, haxorg_ImmListItemAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(org::imm::ImmAdapterT<org::imm::ImmListItem>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmListItem>::getHeader), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmListItemAdapter, haxorg_ImmListItemAdapter_vtable>::getBullet_const(OrgContext* org_context, haxorg_ImmListItemAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmListItem>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmListItem>::getBullet), org_context, self);
}
haxorg_InitialSubtreeVisibility org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getInitialVisibility_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter self) {
  return org::bind::c::execute_cpp<haxorg_InitialSubtreeVisibility, haxorg_builtin_vtable>(static_cast<InitialSubtreeVisibility(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getInitialVisibility), org_context, self);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getProperties_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmVec, haxorg_ImmVec_vtable>(static_cast<hstd::ext::ImmVec<org::sem::NamedProperty>(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getProperties), org_context, self);
}
haxorg_DocumentExportConfig org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getExportConfig_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter self) {
  return org::bind::c::execute_cpp<haxorg_DocumentExportConfig, haxorg_DocumentExportConfig_vtable>(static_cast<org::sem::DocumentExportConfig(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getExportConfig), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getFixedWidthSections_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<bool> const&(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getFixedWidthSections), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getStartupIndented_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<bool> const&(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getStartupIndented), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getCategory_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getCategory), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getSetupfile_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getSetupfile), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getMaxSubtreeLevelExport_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<int> const&(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getMaxSubtreeLevelExport), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getColumns_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<org::sem::ColumnView> const&(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getColumns), org_context, self);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getTodoKeywords_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmVec, haxorg_ImmVec_vtable>(static_cast<hstd::ext::ImmVec<org::sem::TodoKeyword>(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getTodoKeywords), org_context, self);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmDocumentOptionsAdapter, haxorg_ImmDocumentOptionsAdapter_vtable>::getDoneKeywords_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmVec, haxorg_ImmVec_vtable>(static_cast<hstd::ext::ImmVec<org::sem::TodoKeyword>(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getDoneKeywords), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>::getTitle_const(OrgContext* org_context, haxorg_ImmDocumentAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getTitle), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>::getAuthor_const(OrgContext* org_context, haxorg_ImmDocumentAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getAuthor), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>::getCreator_const(OrgContext* org_context, haxorg_ImmDocumentAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getCreator), org_context, self);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>::getFiletags_const(OrgContext* org_context, haxorg_ImmDocumentAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmVec, haxorg_ImmVec_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag>>(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getFiletags), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>::getEmail_const(OrgContext* org_context, haxorg_ImmDocumentAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmRawText>>(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getEmail), org_context, self);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>::getLanguage_const(OrgContext* org_context, haxorg_ImmDocumentAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmVec, haxorg_ImmVec_vtable>(static_cast<hstd::ext::ImmVec<hstd::Str>(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getLanguage), org_context, self);
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>::getOptions_const(OrgContext* org_context, haxorg_ImmDocumentAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getOptions), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmDocumentAdapter, haxorg_ImmDocumentAdapter_vtable>::getExportFileName_const(OrgContext* org_context, haxorg_ImmDocumentAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getExportFileName), org_context, self);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable>::getPath_const(OrgContext* org_context, haxorg_ImmFileTargetAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getPath), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable>::getLine_const(OrgContext* org_context, haxorg_ImmFileTargetAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<int> const&(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getLine), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable>::getSearchTarget_const(OrgContext* org_context, haxorg_ImmFileTargetAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getSearchTarget), org_context, self);
}
bool org::bind::c::VTable<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable>::getRestrictToHeadlines_const(OrgContext* org_context, haxorg_ImmFileTargetAdapter self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getRestrictToHeadlines), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable>::getTargetId_const(OrgContext* org_context, haxorg_ImmFileTargetAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getTargetId), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmFileTargetAdapter, haxorg_ImmFileTargetAdapter_vtable>::getRegexp_const(OrgContext* org_context, haxorg_ImmFileTargetAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getRegexp), org_context, self);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdIncludeAdapter, haxorg_ImmCmdIncludeAdapter_vtable>::getPath_const(OrgContext* org_context, haxorg_ImmCmdIncludeAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::getPath), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmCmdIncludeAdapter, haxorg_ImmCmdIncludeAdapter_vtable>::getFirstLine_const(OrgContext* org_context, haxorg_ImmCmdIncludeAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<int> const&(org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::getFirstLine), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmCmdIncludeAdapter, haxorg_ImmCmdIncludeAdapter_vtable>::getLastLine_const(OrgContext* org_context, haxorg_ImmCmdIncludeAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<int> const&(org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::getLastLine), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_BlockExport, haxorg_BlockExport_vtable>::getPlacement_const(OrgContext* org_context, haxorg_BlockExport self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<hstd::Str>(org::sem::BlockExport::*)() const>(&org::sem::BlockExport::getPlacement), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_BlockCode, haxorg_BlockCode_vtable>::getVariable_const(OrgContext* org_context, haxorg_BlockCode self, haxorg_HstdStr varname) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::BlockCode::*)(hstd::Str const&) const>(&org::sem::BlockCode::getVariable), org_context, self, varname);
}
bool org::bind::c::VTable<haxorg_ImmBlockCenter, haxorg_ImmBlockCenter_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmBlockCenter self, haxorg_ImmBlockCenter other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmBlockCenter::*)(org::imm::ImmBlockCenter const&) const>(&org::imm::ImmBlockCenter::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmBlockQuote, haxorg_ImmBlockQuote_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmBlockQuote self, haxorg_ImmBlockQuote other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmBlockQuote::*)(org::imm::ImmBlockQuote const&) const>(&org::imm::ImmBlockQuote::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmBlockVerse, haxorg_ImmBlockVerse_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmBlockVerse self, haxorg_ImmBlockVerse other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmBlockVerse::*)(org::imm::ImmBlockVerse const&) const>(&org::imm::ImmBlockVerse::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmBlockDynamicFallback, haxorg_ImmBlockDynamicFallback_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmBlockDynamicFallback self, haxorg_ImmBlockDynamicFallback other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmBlockDynamicFallback::*)(org::imm::ImmBlockDynamicFallback const&) const>(&org::imm::ImmBlockDynamicFallback::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmBlockExample, haxorg_ImmBlockExample_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmBlockExample self, haxorg_ImmBlockExample other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmBlockExample::*)(org::imm::ImmBlockExample const&) const>(&org::imm::ImmBlockExample::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmBlockExport, haxorg_ImmBlockExport_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmBlockExport self, haxorg_ImmBlockExport other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmBlockExport::*)(org::imm::ImmBlockExport const&) const>(&org::imm::ImmBlockExport::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmBlockAdmonition, haxorg_ImmBlockAdmonition_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmBlockAdmonition self, haxorg_ImmBlockAdmonition other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmBlockAdmonition::*)(org::imm::ImmBlockAdmonition const&) const>(&org::imm::ImmBlockAdmonition::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmBlockCodeEvalResult, haxorg_ImmBlockCodeEvalResult_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmBlockCodeEvalResult self, haxorg_ImmBlockCodeEvalResult other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmBlockCodeEvalResult::*)(org::imm::ImmBlockCodeEvalResult const&) const>(&org::imm::ImmBlockCodeEvalResult::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmBlockCode, haxorg_ImmBlockCode_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmBlockCode self, haxorg_ImmBlockCode other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmBlockCode::*)(org::imm::ImmBlockCode const&) const>(&org::imm::ImmBlockCode::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmTable, haxorg_ImmTable_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmTable self, haxorg_ImmTable other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmTable::*)(org::imm::ImmTable const&) const>(&org::imm::ImmTable::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmAttached, haxorg_ImmAttached_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmAttached self, haxorg_ImmAttached other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmAttached::*)(org::imm::ImmAttached const&) const>(&org::imm::ImmAttached::operator==), org_context, self, other);
}
haxorg_AttrGroup org::bind::c::VTable<haxorg_ImmCmdAdapter, haxorg_ImmCmdAdapter_vtable>::getAttrs_const(OrgContext* org_context, haxorg_ImmCmdAdapter self) {
  return org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmCmd>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmd>::getAttrs), org_context, self);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdCustomRawAdapter, haxorg_ImmCmdCustomRawAdapter_vtable>::getName_const(OrgContext* org_context, haxorg_ImmCmdCustomRawAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::getName), org_context, self);
}
bool org::bind::c::VTable<haxorg_ImmCmdCustomRawAdapter, haxorg_ImmCmdCustomRawAdapter_vtable>::getIsAttached_const(OrgContext* org_context, haxorg_ImmCmdCustomRawAdapter self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::getIsAttached), org_context, self);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdCustomRawAdapter, haxorg_ImmCmdCustomRawAdapter_vtable>::getText_const(OrgContext* org_context, haxorg_ImmCmdCustomRawAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::getText), org_context, self);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdCustomTextAdapter, haxorg_ImmCmdCustomTextAdapter_vtable>::getName_const(OrgContext* org_context, haxorg_ImmCmdCustomTextAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::getName), org_context, self);
}
bool org::bind::c::VTable<haxorg_ImmCmdCustomTextAdapter, haxorg_ImmCmdCustomTextAdapter_vtable>::getIsAttached_const(OrgContext* org_context, haxorg_ImmCmdCustomTextAdapter self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::getIsAttached), org_context, self);
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmCmdCustomTextAdapter, haxorg_ImmCmdCustomTextAdapter_vtable>::getText_const(OrgContext* org_context, haxorg_ImmCmdCustomTextAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::getText), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmLinkAdapter, haxorg_ImmLinkAdapter_vtable>::getDescription_const(OrgContext* org_context, haxorg_ImmLinkAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(org::imm::ImmAdapterT<org::imm::ImmLink>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmLink>::getDescription), org_context, self);
}
haxorg_LinkTarget org::bind::c::VTable<haxorg_ImmLinkAdapter, haxorg_ImmLinkAdapter_vtable>::getTarget_const(OrgContext* org_context, haxorg_ImmLinkAdapter self) {
  return org::bind::c::execute_cpp<haxorg_LinkTarget, haxorg_LinkTarget_vtable>(static_cast<org::sem::LinkTarget(org::imm::ImmAdapterT<org::imm::ImmLink>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmLink>::getTarget), org_context, self);
}
haxorg_HashTagText org::bind::c::VTable<haxorg_ImmHashTagAdapter, haxorg_ImmHashTagAdapter_vtable>::getText_const(OrgContext* org_context, haxorg_ImmHashTagAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HashTagText, haxorg_HashTagText_vtable>(static_cast<org::sem::HashTagText(org::imm::ImmAdapterT<org::imm::ImmHashTag>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmHashTag>::getText), org_context, self);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmInlineFootnoteAdapter, haxorg_ImmInlineFootnoteAdapter_vtable>::getTag_const(OrgContext* org_context, haxorg_ImmInlineFootnoteAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>::getTag), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmInlineFootnoteAdapter, haxorg_ImmInlineFootnoteAdapter_vtable>::getDefinition_const(OrgContext* org_context, haxorg_ImmInlineFootnoteAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<org::imm::ImmAdapter>(org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>::getDefinition), org_context, self);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmRadioTargetAdapter, haxorg_ImmRadioTargetAdapter_vtable>::getWords_const(OrgContext* org_context, haxorg_ImmRadioTargetAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmVec, haxorg_ImmVec_vtable>(static_cast<hstd::ext::ImmVec<hstd::Str>(org::imm::ImmAdapterT<org::imm::ImmRadioTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmRadioTarget>::getWords), org_context, self);
}
bool org::bind::c::VTable<haxorg_ImmCmdCaption, haxorg_ImmCmdCaption_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmCmdCaption self, haxorg_ImmCmdCaption other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmCmdCaption::*)(org::imm::ImmCmdCaption const&) const>(&org::imm::ImmCmdCaption::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdColumns, haxorg_ImmCmdColumns_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmCmdColumns self, haxorg_ImmCmdColumns other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmCmdColumns::*)(org::imm::ImmCmdColumns const&) const>(&org::imm::ImmCmdColumns::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdName, haxorg_ImmCmdName_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmCmdName self, haxorg_ImmCmdName other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmCmdName::*)(org::imm::ImmCmdName const&) const>(&org::imm::ImmCmdName::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdCall, haxorg_ImmCmdCall_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmCmdCall self, haxorg_ImmCmdCall other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmCmdCall::*)(org::imm::ImmCmdCall const&) const>(&org::imm::ImmCmdCall::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdAttr, haxorg_ImmCmdAttr_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmCmdAttr self, haxorg_ImmCmdAttr other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmCmdAttr::*)(org::imm::ImmCmdAttr const&) const>(&org::imm::ImmCmdAttr::operator==), org_context, self, other);
}
bool org::bind::c::VTable<haxorg_ImmCmdExport, haxorg_ImmCmdExport_vtable>::__eq___const(OrgContext* org_context, haxorg_ImmCmdExport self, haxorg_ImmCmdExport other) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmCmdExport::*)(org::imm::ImmCmdExport const&) const>(&org::imm::ImmCmdExport::operator==), org_context, self, other);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdCustomArgsAdapter, haxorg_ImmCmdCustomArgsAdapter_vtable>::getName_const(OrgContext* org_context, haxorg_ImmCmdCustomArgsAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>::getName), org_context, self);
}
bool org::bind::c::VTable<haxorg_ImmCmdCustomArgsAdapter, haxorg_ImmCmdCustomArgsAdapter_vtable>::getIsAttached_const(OrgContext* org_context, haxorg_ImmCmdCustomArgsAdapter self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>::getIsAttached), org_context, self);
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmCmdCreatorAdapter, haxorg_ImmCmdCreatorAdapter_vtable>::getText_const(OrgContext* org_context, haxorg_ImmCmdCreatorAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmCmdCreator>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCreator>::getText), org_context, self);
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmCmdAuthorAdapter, haxorg_ImmCmdAuthorAdapter_vtable>::getText_const(OrgContext* org_context, haxorg_ImmCmdAuthorAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmCmdAuthor>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdAuthor>::getText), org_context, self);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdEmailAdapter, haxorg_ImmCmdEmailAdapter_vtable>::getText_const(OrgContext* org_context, haxorg_ImmCmdEmailAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdEmail>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdEmail>::getText), org_context, self);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdLanguageAdapter, haxorg_ImmCmdLanguageAdapter_vtable>::getText_const(OrgContext* org_context, haxorg_ImmCmdLanguageAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdLanguage>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdLanguage>::getText), org_context, self);
}
haxorg_Tblfm org::bind::c::VTable<haxorg_ImmCmdTblfmAdapter, haxorg_ImmCmdTblfmAdapter_vtable>::getExpr_const(OrgContext* org_context, haxorg_ImmCmdTblfmAdapter self) {
  return org::bind::c::execute_cpp<haxorg_Tblfm, haxorg_Tblfm_vtable>(static_cast<org::sem::Tblfm(org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>::getExpr), org_context, self);
}
bool org::bind::c::VTable<haxorg_ImmCellAdapter, haxorg_ImmCellAdapter_vtable>::getIsBlock_const(OrgContext* org_context, haxorg_ImmCellAdapter self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmCell>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCell>::getIsBlock), org_context, self);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmRowAdapter, haxorg_ImmRowAdapter_vtable>::getCells_const(OrgContext* org_context, haxorg_ImmRowAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmVec, haxorg_ImmVec_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmCell>>(org::imm::ImmAdapterT<org::imm::ImmRow>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmRow>::getCells), org_context, self);
}
bool org::bind::c::VTable<haxorg_ImmRowAdapter, haxorg_ImmRowAdapter_vtable>::getIsBlock_const(OrgContext* org_context, haxorg_ImmRowAdapter self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmRow>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmRow>::getIsBlock), org_context, self);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmInlineExportAdapter, haxorg_ImmInlineExportAdapter_vtable>::getExporter_const(OrgContext* org_context, haxorg_ImmInlineExportAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmInlineExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmInlineExport>::getExporter), org_context, self);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmInlineExportAdapter, haxorg_ImmInlineExportAdapter_vtable>::getContent_const(OrgContext* org_context, haxorg_ImmInlineExportAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmInlineExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmInlineExport>::getContent), org_context, self);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdExportAdapter, haxorg_ImmCmdExportAdapter_vtable>::getExporter_const(OrgContext* org_context, haxorg_ImmCmdExportAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdExport>::getExporter), org_context, self);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdExportAdapter, haxorg_ImmCmdExportAdapter_vtable>::getContent_const(OrgContext* org_context, haxorg_ImmCmdExportAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdExport>::getContent), org_context, self);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmBlockExportAdapter, haxorg_ImmBlockExportAdapter_vtable>::getExporter_const(OrgContext* org_context, haxorg_ImmBlockExportAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmBlockExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockExport>::getExporter), org_context, self);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmBlockExportAdapter, haxorg_ImmBlockExportAdapter_vtable>::getContent_const(OrgContext* org_context, haxorg_ImmBlockExportAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmBlockExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockExport>::getContent), org_context, self);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmBlockDynamicFallbackAdapter, haxorg_ImmBlockDynamicFallbackAdapter_vtable>::getName_const(OrgContext* org_context, haxorg_ImmBlockDynamicFallbackAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>::getName), org_context, self);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmBlockCodeEvalResultAdapter, haxorg_ImmBlockCodeEvalResultAdapter_vtable>::getRaw_const(OrgContext* org_context, haxorg_ImmBlockCodeEvalResultAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmVec, haxorg_ImmVec_vtable>(static_cast<hstd::ext::ImmVec<org::sem::OrgCodeEvalOutput>(org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>::getRaw), org_context, self);
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmBlockCodeEvalResultAdapter, haxorg_ImmBlockCodeEvalResultAdapter_vtable>::getNode_const(OrgContext* org_context, haxorg_ImmBlockCodeEvalResultAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>::getNode), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmBlockCodeAdapter, haxorg_ImmBlockCodeAdapter_vtable>::getLang_const(OrgContext* org_context, haxorg_ImmBlockCodeAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmBlockCode>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCode>::getLang), org_context, self);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmBlockCodeAdapter, haxorg_ImmBlockCodeAdapter_vtable>::getResult_const(OrgContext* org_context, haxorg_ImmBlockCodeAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmVec, haxorg_ImmVec_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>>(org::imm::ImmAdapterT<org::imm::ImmBlockCode>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCode>::getResult), org_context, self);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmBlockCodeAdapter, haxorg_ImmBlockCodeAdapter_vtable>::getLines_const(OrgContext* org_context, haxorg_ImmBlockCodeAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmVec, haxorg_ImmVec_vtable>(static_cast<hstd::ext::ImmVec<org::sem::BlockCodeLine>(org::imm::ImmAdapterT<org::imm::ImmBlockCode>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCode>::getLines), org_context, self);
}
haxorg_AttrGroup org::bind::c::VTable<haxorg_ImmBlockCodeAdapter, haxorg_ImmBlockCodeAdapter_vtable>::getSwitches_const(OrgContext* org_context, haxorg_ImmBlockCodeAdapter self) {
  return org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmBlockCode>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCode>::getSwitches), org_context, self);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmTableAdapter, haxorg_ImmTableAdapter_vtable>::getRows_const(OrgContext* org_context, haxorg_ImmTableAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmVec, haxorg_ImmVec_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmRow>>(org::imm::ImmAdapterT<org::imm::ImmTable>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTable>::getRows), org_context, self);
}
bool org::bind::c::VTable<haxorg_ImmTableAdapter, haxorg_ImmTableAdapter_vtable>::getIsBlock_const(OrgContext* org_context, haxorg_ImmTableAdapter self) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmTable>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTable>::getIsBlock), org_context, self);
}
haxorg_ImmAdapter org::bind::c::VTable<haxorg_ImmCmdCaptionAdapter, haxorg_ImmCmdCaptionAdapter_vtable>::getText_const(OrgContext* org_context, haxorg_ImmCmdCaptionAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter, haxorg_ImmAdapter_vtable>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmCmdCaption>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCaption>::getText), org_context, self);
}
haxorg_ColumnView org::bind::c::VTable<haxorg_ImmCmdColumnsAdapter, haxorg_ImmCmdColumnsAdapter_vtable>::getView_const(OrgContext* org_context, haxorg_ImmCmdColumnsAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ColumnView, haxorg_ColumnView_vtable>(static_cast<org::sem::ColumnView(org::imm::ImmAdapterT<org::imm::ImmCmdColumns>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdColumns>::getView), org_context, self);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdNameAdapter, haxorg_ImmCmdNameAdapter_vtable>::getName_const(OrgContext* org_context, haxorg_ImmCmdNameAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdName>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdName>::getName), org_context, self);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable>::getName_const(OrgContext* org_context, haxorg_ImmCmdCallAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getName), org_context, self);
}
haxorg_HstdOpt org::bind::c::VTable<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable>::getFileName_const(OrgContext* org_context, haxorg_ImmCmdCallAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getFileName), org_context, self);
}
haxorg_AttrGroup org::bind::c::VTable<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable>::getInsideHeaderAttrs_const(OrgContext* org_context, haxorg_ImmCmdCallAdapter self) {
  return org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getInsideHeaderAttrs), org_context, self);
}
haxorg_AttrGroup org::bind::c::VTable<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable>::getCallAttrs_const(OrgContext* org_context, haxorg_ImmCmdCallAdapter self) {
  return org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getCallAttrs), org_context, self);
}
haxorg_AttrGroup org::bind::c::VTable<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable>::getEndHeaderAttrs_const(OrgContext* org_context, haxorg_ImmCmdCallAdapter self) {
  return org::bind::c::execute_cpp<haxorg_AttrGroup, haxorg_AttrGroup_vtable>(static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getEndHeaderAttrs), org_context, self);
}
haxorg_ImmVec org::bind::c::VTable<haxorg_ImmCmdCallAdapter, haxorg_ImmCmdCallAdapter_vtable>::getResult_const(OrgContext* org_context, haxorg_ImmCmdCallAdapter self) {
  return org::bind::c::execute_cpp<haxorg_ImmVec, haxorg_ImmVec_vtable>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>>(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getResult), org_context, self);
}
haxorg_HstdStr org::bind::c::VTable<haxorg_ImmCmdAttrAdapter, haxorg_ImmCmdAttrAdapter_vtable>::getTarget_const(OrgContext* org_context, haxorg_ImmCmdAttrAdapter self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr, haxorg_HstdStr_vtable>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdAttr>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdAttr>::getTarget), org_context, self);
}
/* clang-format on */
