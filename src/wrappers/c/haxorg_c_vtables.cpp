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
/* clang-format on */
