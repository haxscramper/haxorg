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
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::sem::Tblfm::Expr::AxisRef::Position>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::sem::Tblfm::Expr::AxisRef::Position> const& __self) -> org::sem::Tblfm::Expr::AxisRef::Position const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::sem::Tblfm::Expr::AxisRef::Position>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::sem::Tblfm::Expr::AxisRef::Position>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::sem::Tblfm::Expr::AxisRef>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::sem::Tblfm::Expr::AxisRef> const& __self) -> org::sem::Tblfm::Expr::AxisRef const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::sem::Tblfm::Expr::AxisRef>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::sem::Tblfm::Expr::AxisRef>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<bool>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<bool> const& __self) -> bool const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<bool>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<bool>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<double>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<double> const& __self) -> double const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<double>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<double>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<hstd::UserTime>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<hstd::UserTime> const& __self) -> hstd::UserTime const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<hstd::UserTime>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<hstd::UserTime>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::sem::AttrValue>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::sem::AttrValue> const& __self) -> org::sem::AttrValue const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::sem::AttrValue>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::sem::AttrValue>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::sem::AttrList>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::sem::AttrList> const& __self) -> org::sem::AttrList const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::sem::AttrList>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::sem::AttrList>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::sem::OrgCodeEvalInput::Var>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::sem::OrgCodeEvalInput::Var> const& __self) -> org::sem::OrgCodeEvalInput::Var const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::sem::OrgCodeEvalInput::Var>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::sem::OrgCodeEvalInput::Var>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::sem::ColumnView::Summary>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::sem::ColumnView::Summary> const& __self) -> org::sem::ColumnView::Summary const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::sem::ColumnView::Summary>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::sem::ColumnView::Summary>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::sem::AttrValue::LispValue>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::sem::AttrValue::LispValue> const& __self) -> org::sem::AttrValue::LispValue const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::sem::AttrValue::LispValue>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::sem::AttrValue::LispValue>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::sem::AttrValue::Kind>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::sem::AttrValue::Kind> const& __self) -> org::sem::AttrValue::Kind const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::sem::AttrValue::Kind>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::sem::AttrValue::Kind>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::sem::Time::Repeat>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::sem::Time::Repeat> const& __self) -> org::sem::Time::Repeat const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::sem::Time::Repeat>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::sem::Time::Repeat>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<int64_t>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<int64_t> const& __self) -> int64_t const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<int64_t>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<int64_t>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::sem::SemId<org::sem::StmtList>>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::sem::SemId<org::sem::StmtList>> const& __self) -> org::sem::SemId<org::sem::StmtList> const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::sem::SemId<org::sem::StmtList>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::sem::SemId<org::sem::StmtList>>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::sem::NamedProperty>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::sem::NamedProperty> const& __self) -> org::sem::NamedProperty const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::sem::NamedProperty>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::sem::NamedProperty>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::sem::SubtreeCompletion>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::sem::SubtreeCompletion> const& __self) -> org::sem::SubtreeCompletion const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::sem::SubtreeCompletion>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::sem::SubtreeCompletion>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::sem::SemId<org::sem::Paragraph>>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::sem::SemId<org::sem::Paragraph>> const& __self) -> org::sem::SemId<org::sem::Paragraph> const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::sem::SemId<org::sem::Paragraph>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::sem::SemId<org::sem::Paragraph>>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::sem::SemId<org::sem::Time>>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::sem::SemId<org::sem::Time>> const& __self) -> org::sem::SemId<org::sem::Time> const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::sem::SemId<org::sem::Time>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::sem::SemId<org::sem::Time>>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::sem::ColumnView>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::sem::ColumnView> const& __self) -> org::sem::ColumnView const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::sem::ColumnView>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::sem::ColumnView>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::sem::SemId<org::sem::RawText>>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::sem::SemId<org::sem::RawText>> const& __self) -> org::sem::SemId<org::sem::RawText> const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::sem::SemId<org::sem::RawText>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::sem::SemId<org::sem::RawText>>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::sem::SubtreePath>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::sem::SubtreePath> const& __self) -> org::sem::SubtreePath const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::sem::SubtreePath>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::sem::SubtreePath>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::imm::ImmTime::Repeat>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::imm::ImmTime::Repeat> const& __self) -> org::imm::ImmTime::Repeat const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::imm::ImmTime::Repeat>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::imm::ImmTime::Repeat>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::imm::ImmIdT<org::imm::ImmStmtList>>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::imm::ImmIdT<org::imm::ImmStmtList>> const& __self) -> org::imm::ImmIdT<org::imm::ImmStmtList> const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::imm::ImmIdT<org::imm::ImmStmtList>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::imm::ImmIdT<org::imm::ImmStmtList>>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>> const& __self) -> org::imm::ImmIdT<org::imm::ImmParagraph> const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::imm::ImmIdT<org::imm::ImmTime>>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::imm::ImmIdT<org::imm::ImmTime>> const& __self) -> org::imm::ImmIdT<org::imm::ImmTime> const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::imm::ImmIdT<org::imm::ImmTime>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::imm::ImmIdT<org::imm::ImmTime>>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::imm::ImmIdT<org::imm::ImmRawText>>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::imm::ImmIdT<org::imm::ImmRawText>> const& __self) -> org::imm::ImmIdT<org::imm::ImmRawText> const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::imm::ImmIdT<org::imm::ImmRawText>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::imm::ImmIdT<org::imm::ImmRawText>>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::imm::ImmIdT<org::imm::ImmOrg>>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::imm::ImmIdT<org::imm::ImmOrg>> const& __self) -> org::imm::ImmIdT<org::imm::ImmOrg> const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::imm::ImmIdT<org::imm::ImmOrg>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::imm::ImmIdT<org::imm::ImmOrg>>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::imm::ImmAdapterT<org::imm::ImmParagraph>>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::imm::ImmAdapterT<org::imm::ImmParagraph>> const& __self) -> org::imm::ImmAdapterT<org::imm::ImmParagraph> const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::imm::ImmAdapterT<org::imm::ImmParagraph>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::imm::ImmAdapterT<org::imm::ImmParagraph>>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::imm::ImmAdapterT<org::imm::ImmTime>>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::imm::ImmAdapterT<org::imm::ImmTime>> const& __self) -> org::imm::ImmAdapterT<org::imm::ImmTime> const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::imm::ImmAdapterT<org::imm::ImmTime>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::imm::ImmAdapterT<org::imm::ImmTime>>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::imm::ImmAdapterT<org::imm::ImmStmtList>>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::imm::ImmAdapterT<org::imm::ImmStmtList>> const& __self) -> org::imm::ImmAdapterT<org::imm::ImmStmtList> const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::imm::ImmAdapterT<org::imm::ImmStmtList>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::imm::ImmAdapterT<org::imm::ImmStmtList>>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
haxorg_ptr_payload org::bind::c::VTable<std::optional<org::imm::ImmAdapterT<org::imm::ImmRawText>>>::value(OrgContext* org_context, haxorg_StdOptional __self) {
  return org::bind::c::execute_cpp<haxorg_ptr_payload>(+[](std::optional<org::imm::ImmAdapterT<org::imm::ImmRawText>> const& __self) -> org::imm::ImmAdapterT<org::imm::ImmRawText> const& { return __self.value(); }, org_context, __self);
}
haxorg_StdOptional_vtable const* org::bind::c::VTable<std::optional<org::imm::ImmAdapterT<org::imm::ImmRawText>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<std::optional<org::imm::ImmAdapterT<org::imm::ImmRawText>>>;
  static haxorg_StdOptional_vtable const vtable{.value = &VtableType::value,};
  return &vtable;
}
/* clang-format on */
