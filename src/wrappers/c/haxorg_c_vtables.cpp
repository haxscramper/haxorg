/* clang-format off */
#include <wrappers/c/haxorg_c.h>
#include <wrappers/c/haxorg_c_utils.hpp>
#include <wrappers/c/haxorg_c_vtables.hpp>
#include <wrappers/c/haxorg_c_vtables_manual.hpp>
haxorg_ptr_payload org::bind::c::VTable<hstd::UnorderedMap<org::sem::HashTagFlat, org::AstTrackingPath, std::hash<org::sem::HashTagFlat>>>::keys_const(OrgContext* org_context, haxorg_HstdMap __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(static_cast<hstd::Vec<org::sem::HashTagFlat>(hstd::UnorderedMap<org::sem::HashTagFlat, org::AstTrackingPath, std::hash<org::sem::HashTagFlat>>::*)() const>(&hstd::UnorderedMap<org::sem::HashTagFlat, org::AstTrackingPath, std::hash<org::sem::HashTagFlat>>::keys), org_context, __self);
}
haxorg_HstdMap_vtable const* org::bind::c::VTable<hstd::UnorderedMap<org::sem::HashTagFlat, org::AstTrackingPath, std::hash<org::sem::HashTagFlat>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::UnorderedMap<org::sem::HashTagFlat, org::AstTrackingPath, std::hash<org::sem::HashTagFlat>>>;
  static haxorg_HstdMap_vtable const vtable{.keys_const = &VtableType::keys_const,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<hstd::UnorderedMap<hstd::Str, org::AstTrackingAlternatives, std::hash<hstd::Str>>>::keys_const(OrgContext* org_context, haxorg_HstdMap __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(static_cast<hstd::Vec<hstd::Str>(hstd::UnorderedMap<hstd::Str, org::AstTrackingAlternatives, std::hash<hstd::Str>>::*)() const>(&hstd::UnorderedMap<hstd::Str, org::AstTrackingAlternatives, std::hash<hstd::Str>>::keys), org_context, __self);
}
haxorg_HstdMap_vtable const* org::bind::c::VTable<hstd::UnorderedMap<hstd::Str, org::AstTrackingAlternatives, std::hash<hstd::Str>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::UnorderedMap<hstd::Str, org::AstTrackingAlternatives, std::hash<hstd::Str>>>;
  static haxorg_HstdMap_vtable const vtable{.keys_const = &VtableType::keys_const,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<hstd::UnorderedMap<org::sem::HashTagFlat, org::AstTrackingAlternatives, std::hash<org::sem::HashTagFlat>>>::keys_const(OrgContext* org_context, haxorg_HstdMap __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(static_cast<hstd::Vec<org::sem::HashTagFlat>(hstd::UnorderedMap<org::sem::HashTagFlat, org::AstTrackingAlternatives, std::hash<org::sem::HashTagFlat>>::*)() const>(&hstd::UnorderedMap<org::sem::HashTagFlat, org::AstTrackingAlternatives, std::hash<org::sem::HashTagFlat>>::keys), org_context, __self);
}
haxorg_HstdMap_vtable const* org::bind::c::VTable<hstd::UnorderedMap<org::sem::HashTagFlat, org::AstTrackingAlternatives, std::hash<org::sem::HashTagFlat>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::UnorderedMap<org::sem::HashTagFlat, org::AstTrackingAlternatives, std::hash<org::sem::HashTagFlat>>>;
  static haxorg_HstdMap_vtable const vtable{.keys_const = &VtableType::keys_const,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<hstd::UnorderedMap<org::graph::MapNode, org::graph::MapNodeProp, std::hash<org::graph::MapNode>>>::keys_const(OrgContext* org_context, haxorg_HstdMap __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(static_cast<hstd::Vec<org::graph::MapNode>(hstd::UnorderedMap<org::graph::MapNode, org::graph::MapNodeProp, std::hash<org::graph::MapNode>>::*)() const>(&hstd::UnorderedMap<org::graph::MapNode, org::graph::MapNodeProp, std::hash<org::graph::MapNode>>::keys), org_context, __self);
}
haxorg_HstdMap_vtable const* org::bind::c::VTable<hstd::UnorderedMap<org::graph::MapNode, org::graph::MapNodeProp, std::hash<org::graph::MapNode>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::UnorderedMap<org::graph::MapNode, org::graph::MapNodeProp, std::hash<org::graph::MapNode>>>;
  static haxorg_HstdMap_vtable const vtable{.keys_const = &VtableType::keys_const,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<hstd::UnorderedMap<org::graph::MapEdge, org::graph::MapEdgeProp, std::hash<org::graph::MapEdge>>>::keys_const(OrgContext* org_context, haxorg_HstdMap __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(static_cast<hstd::Vec<org::graph::MapEdge>(hstd::UnorderedMap<org::graph::MapEdge, org::graph::MapEdgeProp, std::hash<org::graph::MapEdge>>::*)() const>(&hstd::UnorderedMap<org::graph::MapEdge, org::graph::MapEdgeProp, std::hash<org::graph::MapEdge>>::keys), org_context, __self);
}
haxorg_HstdMap_vtable const* org::bind::c::VTable<hstd::UnorderedMap<org::graph::MapEdge, org::graph::MapEdgeProp, std::hash<org::graph::MapEdge>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::UnorderedMap<org::graph::MapEdge, org::graph::MapEdgeProp, std::hash<org::graph::MapEdge>>>;
  static haxorg_HstdMap_vtable const vtable{.keys_const = &VtableType::keys_const,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<hstd::UnorderedMap<org::graph::MapNode, org::graph::AdjNodesList, std::hash<org::graph::MapNode>>>::keys_const(OrgContext* org_context, haxorg_HstdMap __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(static_cast<hstd::Vec<org::graph::MapNode>(hstd::UnorderedMap<org::graph::MapNode, org::graph::AdjNodesList, std::hash<org::graph::MapNode>>::*)() const>(&hstd::UnorderedMap<org::graph::MapNode, org::graph::AdjNodesList, std::hash<org::graph::MapNode>>::keys), org_context, __self);
}
haxorg_HstdMap_vtable const* org::bind::c::VTable<hstd::UnorderedMap<org::graph::MapNode, org::graph::AdjNodesList, std::hash<org::graph::MapNode>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::UnorderedMap<org::graph::MapNode, org::graph::AdjNodesList, std::hash<org::graph::MapNode>>>;
  static haxorg_HstdMap_vtable const vtable{.keys_const = &VtableType::keys_const,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<hstd::UnorderedMap<hstd::Str, org::sem::AttrList, std::hash<hstd::Str>>>::keys_const(OrgContext* org_context, haxorg_HstdMap __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(static_cast<hstd::Vec<hstd::Str>(hstd::UnorderedMap<hstd::Str, org::sem::AttrList, std::hash<hstd::Str>>::*)() const>(&hstd::UnorderedMap<hstd::Str, org::sem::AttrList, std::hash<hstd::Str>>::keys), org_context, __self);
}
haxorg_HstdMap_vtable const* org::bind::c::VTable<hstd::UnorderedMap<hstd::Str, org::sem::AttrList, std::hash<hstd::Str>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::UnorderedMap<hstd::Str, org::sem::AttrList, std::hash<hstd::Str>>>;
  static haxorg_HstdMap_vtable const vtable{.keys_const = &VtableType::keys_const,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<hstd::UnorderedMap<hstd::Str, hstd::Str, std::hash<hstd::Str>>>::keys_const(OrgContext* org_context, haxorg_HstdMap __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(static_cast<hstd::Vec<hstd::Str>(hstd::UnorderedMap<hstd::Str, hstd::Str, std::hash<hstd::Str>>::*)() const>(&hstd::UnorderedMap<hstd::Str, hstd::Str, std::hash<hstd::Str>>::keys), org_context, __self);
}
haxorg_HstdMap_vtable const* org::bind::c::VTable<hstd::UnorderedMap<hstd::Str, hstd::Str, std::hash<hstd::Str>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::UnorderedMap<hstd::Str, hstd::Str, std::hash<hstd::Str>>>;
  static haxorg_HstdMap_vtable const vtable{.keys_const = &VtableType::keys_const,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<int>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<int> const& __self) -> int const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<int>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<int>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<std::string>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<std::string> const& __self) -> std::string const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<std::string>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<std::string>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::sem::SemId<org::sem::Org>>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::sem::SemId<org::sem::Org>> const& __self) -> org::sem::SemId<org::sem::Org> const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::sem::SemId<org::sem::Org>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::sem::SemId<org::sem::Org>>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::parse::SourceLoc>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::parse::SourceLoc> const& __self) -> org::parse::SourceLoc const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::parse::SourceLoc>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::parse::SourceLoc>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::imm::ImmAdapter>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::imm::ImmAdapter> const& __self) -> org::imm::ImmAdapter const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::imm::ImmAdapter>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::imm::ImmAdapter>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::AstTrackingAlternatives>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::AstTrackingAlternatives> const& __self) -> org::AstTrackingAlternatives const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::AstTrackingAlternatives>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::AstTrackingAlternatives>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<hstd::Str>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<hstd::Str> const& __self) -> hstd::Str const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<hstd::Str>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<hstd::Str>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::graph::MapLink>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::graph::MapLink> const& __self) -> org::graph::MapLink const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::graph::MapLink>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::graph::MapLink>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
/* clang-format on */
