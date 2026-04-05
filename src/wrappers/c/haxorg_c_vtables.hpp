/* clang-format off */
#pragma once
#include <wrappers/c/haxorg_c.h>
#include <wrappers/c/haxorg_c_utils.hpp>
#include <wrappers/c/haxorg_c_vtables_manual.hpp>
template <>
struct org::bind::c::VTable<hstd::Vec<org::sem::OrgJson>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::Org>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_SemIdOfOrg atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<hstd::ext::Report>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::ErrorGroup>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_SemIdOfOrg atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<int>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static int const& atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::imm::ImmAdapter>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<hstd::SequenceSegment>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<hstd::SequenceAnnotationTag>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::imm::ImmUniqId>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::graph::MapLink>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::graph::MapNode>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::graph::MapEdge>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::sem::LispCode>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::sem::Tblfm::Assign>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::sem::Tblfm::Expr>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::sem::Tblfm::Assign::Flag>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::sem::AttrValue::DimensionSpan>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<hstd::Str>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::sem::HashTagFlat>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::sem::HashTagText>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::sem::AttrValue>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::sem::OrgCodeEvalInput::Var>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::sem::ColumnView::Column>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::sem::BlockCodeLine::Part>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::ErrorItem>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_SemIdOfOrg atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::sem::Time::Repeat>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::sem::Symbol::Param>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::ErrorSkipToken>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_SemIdOfOrg atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::sem::SubtreePeriod>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::sem::NamedProperty>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::HashTag>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_SemIdOfOrg atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::SubtreeLog>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_SemIdOfOrg atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::sem::TodoKeyword>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::BigIdent>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_SemIdOfOrg atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<hstd::UserTime>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::Time>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_SemIdOfOrg atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::Cell>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_SemIdOfOrg atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::sem::OrgCodeEvalOutput>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::BlockCodeEvalResult>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_SemIdOfOrg atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::sem::BlockCodeLine>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::Row>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_SemIdOfOrg atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<org::AstTrackingGroup>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<hstd::SequenceAnnotation>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Vec<hstd::SequenceSegmentGroup>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int size_const(OrgContext* org_context, haxorg_HstdVec __self);
  static haxorg_ptr_payload atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx);
  static haxorg_HstdVec_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::UnorderedMap<org::sem::HashTagFlat, org::AstTrackingPath, std::hash<org::sem::HashTagFlat>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdVec keys_const(OrgContext* org_context, haxorg_HstdMap __self);
  static haxorg_HstdMap_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::UnorderedMap<hstd::Str, org::AstTrackingAlternatives, std::hash<hstd::Str>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdVec keys_const(OrgContext* org_context, haxorg_HstdMap __self);
  static haxorg_HstdMap_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::UnorderedMap<org::sem::HashTagFlat, org::AstTrackingAlternatives, std::hash<org::sem::HashTagFlat>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdVec keys_const(OrgContext* org_context, haxorg_HstdMap __self);
  static haxorg_HstdMap_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::UnorderedMap<org::graph::MapNode, org::graph::MapNodeProp, std::hash<org::graph::MapNode>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdVec keys_const(OrgContext* org_context, haxorg_HstdMap __self);
  static haxorg_HstdMap_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::UnorderedMap<org::graph::MapEdge, org::graph::MapEdgeProp, std::hash<org::graph::MapEdge>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdVec keys_const(OrgContext* org_context, haxorg_HstdMap __self);
  static haxorg_HstdMap_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::UnorderedMap<org::graph::MapNode, org::graph::AdjNodesList, std::hash<org::graph::MapNode>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdVec keys_const(OrgContext* org_context, haxorg_HstdMap __self);
  static haxorg_HstdMap_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::UnorderedMap<hstd::Str, org::sem::AttrList, std::hash<hstd::Str>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdVec keys_const(OrgContext* org_context, haxorg_HstdMap __self);
  static haxorg_HstdMap_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::UnorderedMap<hstd::Str, hstd::Str, std::hash<hstd::Str>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdVec keys_const(OrgContext* org_context, haxorg_HstdMap __self);
  static haxorg_HstdMap_vtable const* get_vtable();
};

/* clang-format on */
