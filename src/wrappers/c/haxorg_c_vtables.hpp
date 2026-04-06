/* clang-format off */
#pragma once
#include <wrappers/c/haxorg_c.h>
#include <wrappers/c/haxorg_c_utils.hpp>
#include <wrappers/c/haxorg_c_vtables_manual.hpp>
template <>
struct org::bind::c::VTable<hstd::UnorderedMap<org::sem::HashTagFlat, org::AstTrackingPath, std::hash<org::sem::HashTagFlat>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload keys_const(OrgContext* org_context, haxorg_HstdMap __self);
  static haxorg_HstdMap_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::UnorderedMap<hstd::Str, org::AstTrackingAlternatives, std::hash<hstd::Str>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload keys_const(OrgContext* org_context, haxorg_HstdMap __self);
  static haxorg_HstdMap_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::UnorderedMap<org::sem::HashTagFlat, org::AstTrackingAlternatives, std::hash<org::sem::HashTagFlat>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload keys_const(OrgContext* org_context, haxorg_HstdMap __self);
  static haxorg_HstdMap_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::UnorderedMap<org::graph::MapNode, org::graph::MapNodeProp, std::hash<org::graph::MapNode>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload keys_const(OrgContext* org_context, haxorg_HstdMap __self);
  static haxorg_HstdMap_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::UnorderedMap<org::graph::MapEdge, org::graph::MapEdgeProp, std::hash<org::graph::MapEdge>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload keys_const(OrgContext* org_context, haxorg_HstdMap __self);
  static haxorg_HstdMap_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::UnorderedMap<org::graph::MapNode, org::graph::AdjNodesList, std::hash<org::graph::MapNode>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload keys_const(OrgContext* org_context, haxorg_HstdMap __self);
  static haxorg_HstdMap_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::UnorderedMap<hstd::Str, org::sem::AttrList, std::hash<hstd::Str>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload keys_const(OrgContext* org_context, haxorg_HstdMap __self);
  static haxorg_HstdMap_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::UnorderedMap<hstd::Str, hstd::Str, std::hash<hstd::Str>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload keys_const(OrgContext* org_context, haxorg_HstdMap __self);
  static haxorg_HstdMap_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<int>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<std::string>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::sem::SemId<org::sem::Org>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::parse::SourceLoc>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::imm::ImmAdapter>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::AstTrackingAlternatives>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<hstd::Str>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::graph::MapLink>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::sem::Tblfm::Expr::AxisRef::Position>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::sem::Tblfm::Expr::AxisRef>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<bool>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<double>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<hstd::UserTime>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::sem::AttrValue>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::sem::AttrList>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::sem::OrgCodeEvalInput::Var>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::sem::ColumnView::Summary>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::sem::AttrValue::LispValue>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::sem::AttrValue::Kind>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::sem::Time::Repeat>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<int64_t>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::sem::SemId<org::sem::StmtList>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::sem::NamedProperty>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::sem::SubtreeCompletion>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::sem::SemId<org::sem::Paragraph>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::sem::SemId<org::sem::Time>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::sem::ColumnView>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::sem::SemId<org::sem::RawText>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::sem::SubtreePath>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::imm::ImmTime::Repeat>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::imm::ImmIdT<org::imm::ImmStmtList>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::imm::ImmIdT<org::imm::ImmTime>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::imm::ImmIdT<org::imm::ImmRawText>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::imm::ImmIdT<org::imm::ImmOrg>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::imm::ImmAdapterT<org::imm::ImmParagraph>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::imm::ImmAdapterT<org::imm::ImmTime>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::imm::ImmAdapterT<org::imm::ImmStmtList>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<std::optional<org::imm::ImmAdapterT<org::imm::ImmRawText>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_StdOptional __self);
  static haxorg_StdOptional_vtable const* get_vtable();
};

/* clang-format on */
