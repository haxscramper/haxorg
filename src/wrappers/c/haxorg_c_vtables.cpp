/* clang-format off */
#include <wrappers/c/haxorg_c.h>
#include <wrappers/c/haxorg_c_utils.hpp>
#include <wrappers/c/haxorg_c_vtables.hpp>
#include <wrappers/c/haxorg_c_vtables_manual.hpp>
int org::bind::c::VTable<hstd::Vec<org::sem::OrgJson>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::OrgJson>::*)() const>(&hstd::Vec<org::sem::OrgJson>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<org::sem::OrgJson>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_OrgJson>(static_cast<org::sem::OrgJson const&(hstd::Vec<org::sem::OrgJson>::*)(int) const>(&hstd::Vec<org::sem::OrgJson>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::sem::OrgJson>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::sem::OrgJson>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::Org>>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::SemId<org::sem::Org>>::*)() const>(&hstd::Vec<org::sem::SemId<org::sem::Org>>::size), org_context, __self);
}
haxorg_SemIdOfOrg org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::Org>>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::Org> const&(hstd::Vec<org::sem::SemId<org::sem::Org>>::*)(int) const>(&hstd::Vec<org::sem::SemId<org::sem::Org>>::at), org_context, __self, idx);
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::Org>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::Org>>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<hstd::ext::Report>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<hstd::ext::Report>::*)() const>(&hstd::Vec<hstd::ext::Report>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<hstd::ext::Report>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_Report>(static_cast<hstd::ext::Report const&(hstd::Vec<hstd::ext::Report>::*)(int) const>(&hstd::Vec<hstd::ext::Report>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<hstd::ext::Report>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<hstd::ext::Report>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::ErrorGroup>>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::SemId<org::sem::ErrorGroup>>::*)() const>(&hstd::Vec<org::sem::SemId<org::sem::ErrorGroup>>::size), org_context, __self);
}
haxorg_SemIdOfOrg org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::ErrorGroup>>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::ErrorGroup> const&(hstd::Vec<org::sem::SemId<org::sem::ErrorGroup>>::*)(int) const>(&hstd::Vec<org::sem::SemId<org::sem::ErrorGroup>>::at), org_context, __self, idx);
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::ErrorGroup>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::ErrorGroup>>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<int>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<int>::*)() const>(&hstd::Vec<int>::size), org_context, __self);
}
int const& org::bind::c::VTable<hstd::Vec<int>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<int const&>(static_cast<int const&(hstd::Vec<int>::*)(int) const>(&hstd::Vec<int>::at), org_context, __self, idx);
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<int>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<int>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::imm::ImmAdapter>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::imm::ImmAdapter>::*)() const>(&hstd::Vec<org::imm::ImmAdapter>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<org::imm::ImmAdapter>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter>(static_cast<org::imm::ImmAdapter const&(hstd::Vec<org::imm::ImmAdapter>::*)(int) const>(&hstd::Vec<org::imm::ImmAdapter>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::imm::ImmAdapter>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::imm::ImmAdapter>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<hstd::SequenceSegment>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<hstd::SequenceSegment>::*)() const>(&hstd::Vec<hstd::SequenceSegment>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<hstd::SequenceSegment>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_SequenceSegment>(static_cast<hstd::SequenceSegment const&(hstd::Vec<hstd::SequenceSegment>::*)(int) const>(&hstd::Vec<hstd::SequenceSegment>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<hstd::SequenceSegment>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<hstd::SequenceSegment>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<hstd::SequenceAnnotationTag>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<hstd::SequenceAnnotationTag>::*)() const>(&hstd::Vec<hstd::SequenceAnnotationTag>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<hstd::SequenceAnnotationTag>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_SequenceAnnotationTag>(static_cast<hstd::SequenceAnnotationTag const&(hstd::Vec<hstd::SequenceAnnotationTag>::*)(int) const>(&hstd::Vec<hstd::SequenceAnnotationTag>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<hstd::SequenceAnnotationTag>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<hstd::SequenceAnnotationTag>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::imm::ImmUniqId>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::imm::ImmUniqId>::*)() const>(&hstd::Vec<org::imm::ImmUniqId>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<org::imm::ImmUniqId>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_ImmUniqId>(static_cast<org::imm::ImmUniqId const&(hstd::Vec<org::imm::ImmUniqId>::*)(int) const>(&hstd::Vec<org::imm::ImmUniqId>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::imm::ImmUniqId>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::imm::ImmUniqId>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::graph::MapLink>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::graph::MapLink>::*)() const>(&hstd::Vec<org::graph::MapLink>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<org::graph::MapLink>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_GraphMapLink>(static_cast<org::graph::MapLink const&(hstd::Vec<org::graph::MapLink>::*)(int) const>(&hstd::Vec<org::graph::MapLink>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::graph::MapLink>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::graph::MapLink>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::graph::MapNode>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::graph::MapNode>::*)() const>(&hstd::Vec<org::graph::MapNode>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<org::graph::MapNode>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_GraphMapNode>(static_cast<org::graph::MapNode const&(hstd::Vec<org::graph::MapNode>::*)(int) const>(&hstd::Vec<org::graph::MapNode>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::graph::MapNode>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::graph::MapNode>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::graph::MapEdge>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::graph::MapEdge>::*)() const>(&hstd::Vec<org::graph::MapEdge>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<org::graph::MapEdge>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_GraphMapEdge>(static_cast<org::graph::MapEdge const&(hstd::Vec<org::graph::MapEdge>::*)(int) const>(&hstd::Vec<org::graph::MapEdge>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::graph::MapEdge>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::graph::MapEdge>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::sem::LispCode>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::LispCode>::*)() const>(&hstd::Vec<org::sem::LispCode>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<org::sem::LispCode>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_LispCode>(static_cast<org::sem::LispCode const&(hstd::Vec<org::sem::LispCode>::*)(int) const>(&hstd::Vec<org::sem::LispCode>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::sem::LispCode>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::sem::LispCode>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::sem::Tblfm::Assign>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::Tblfm::Assign>::*)() const>(&hstd::Vec<org::sem::Tblfm::Assign>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<org::sem::Tblfm::Assign>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_TblfmAssign>(static_cast<org::sem::Tblfm::Assign const&(hstd::Vec<org::sem::Tblfm::Assign>::*)(int) const>(&hstd::Vec<org::sem::Tblfm::Assign>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::sem::Tblfm::Assign>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::sem::Tblfm::Assign>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::sem::Tblfm::Expr>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::Tblfm::Expr>::*)() const>(&hstd::Vec<org::sem::Tblfm::Expr>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<org::sem::Tblfm::Expr>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_TblfmExpr>(static_cast<org::sem::Tblfm::Expr const&(hstd::Vec<org::sem::Tblfm::Expr>::*)(int) const>(&hstd::Vec<org::sem::Tblfm::Expr>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::sem::Tblfm::Expr>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::sem::Tblfm::Expr>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::sem::Tblfm::Assign::Flag>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::Tblfm::Assign::Flag>::*)() const>(&hstd::Vec<org::sem::Tblfm::Assign::Flag>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<org::sem::Tblfm::Assign::Flag>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_TblfmAssignFlag>(static_cast<org::sem::Tblfm::Assign::Flag const&(hstd::Vec<org::sem::Tblfm::Assign::Flag>::*)(int) const>(&hstd::Vec<org::sem::Tblfm::Assign::Flag>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::sem::Tblfm::Assign::Flag>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::sem::Tblfm::Assign::Flag>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::sem::AttrValue::DimensionSpan>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::AttrValue::DimensionSpan>::*)() const>(&hstd::Vec<org::sem::AttrValue::DimensionSpan>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<org::sem::AttrValue::DimensionSpan>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_AttrValueDimensionSpan>(static_cast<org::sem::AttrValue::DimensionSpan const&(hstd::Vec<org::sem::AttrValue::DimensionSpan>::*)(int) const>(&hstd::Vec<org::sem::AttrValue::DimensionSpan>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::sem::AttrValue::DimensionSpan>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::sem::AttrValue::DimensionSpan>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<hstd::Str>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<hstd::Str>::*)() const>(&hstd::Vec<hstd::Str>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<hstd::Str>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(hstd::Vec<hstd::Str>::*)(int) const>(&hstd::Vec<hstd::Str>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<hstd::Str>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<hstd::Str>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::sem::HashTagFlat>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::HashTagFlat>::*)() const>(&hstd::Vec<org::sem::HashTagFlat>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<org::sem::HashTagFlat>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_HashTagFlat>(static_cast<org::sem::HashTagFlat const&(hstd::Vec<org::sem::HashTagFlat>::*)(int) const>(&hstd::Vec<org::sem::HashTagFlat>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::sem::HashTagFlat>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::sem::HashTagFlat>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::sem::HashTagText>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::HashTagText>::*)() const>(&hstd::Vec<org::sem::HashTagText>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<org::sem::HashTagText>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_HashTagText>(static_cast<org::sem::HashTagText const&(hstd::Vec<org::sem::HashTagText>::*)(int) const>(&hstd::Vec<org::sem::HashTagText>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::sem::HashTagText>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::sem::HashTagText>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::sem::AttrValue>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::AttrValue>::*)() const>(&hstd::Vec<org::sem::AttrValue>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<org::sem::AttrValue>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_AttrValue>(static_cast<org::sem::AttrValue const&(hstd::Vec<org::sem::AttrValue>::*)(int) const>(&hstd::Vec<org::sem::AttrValue>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::sem::AttrValue>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::sem::AttrValue>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::sem::OrgCodeEvalInput::Var>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::OrgCodeEvalInput::Var>::*)() const>(&hstd::Vec<org::sem::OrgCodeEvalInput::Var>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<org::sem::OrgCodeEvalInput::Var>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_OrgCodeEvalInputVar>(static_cast<org::sem::OrgCodeEvalInput::Var const&(hstd::Vec<org::sem::OrgCodeEvalInput::Var>::*)(int) const>(&hstd::Vec<org::sem::OrgCodeEvalInput::Var>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::sem::OrgCodeEvalInput::Var>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::sem::OrgCodeEvalInput::Var>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::sem::ColumnView::Column>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::ColumnView::Column>::*)() const>(&hstd::Vec<org::sem::ColumnView::Column>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<org::sem::ColumnView::Column>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_ColumnViewColumn>(static_cast<org::sem::ColumnView::Column const&(hstd::Vec<org::sem::ColumnView::Column>::*)(int) const>(&hstd::Vec<org::sem::ColumnView::Column>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::sem::ColumnView::Column>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::sem::ColumnView::Column>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::sem::BlockCodeLine::Part>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::BlockCodeLine::Part>::*)() const>(&hstd::Vec<org::sem::BlockCodeLine::Part>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<org::sem::BlockCodeLine::Part>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_BlockCodeLinePart>(static_cast<org::sem::BlockCodeLine::Part const&(hstd::Vec<org::sem::BlockCodeLine::Part>::*)(int) const>(&hstd::Vec<org::sem::BlockCodeLine::Part>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::sem::BlockCodeLine::Part>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::sem::BlockCodeLine::Part>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::ErrorItem>>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::SemId<org::sem::ErrorItem>>::*)() const>(&hstd::Vec<org::sem::SemId<org::sem::ErrorItem>>::size), org_context, __self);
}
haxorg_SemIdOfOrg org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::ErrorItem>>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::ErrorItem> const&(hstd::Vec<org::sem::SemId<org::sem::ErrorItem>>::*)(int) const>(&hstd::Vec<org::sem::SemId<org::sem::ErrorItem>>::at), org_context, __self, idx);
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::ErrorItem>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::ErrorItem>>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::sem::Time::Repeat>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::Time::Repeat>::*)() const>(&hstd::Vec<org::sem::Time::Repeat>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<org::sem::Time::Repeat>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_TimeRepeat>(static_cast<org::sem::Time::Repeat const&(hstd::Vec<org::sem::Time::Repeat>::*)(int) const>(&hstd::Vec<org::sem::Time::Repeat>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::sem::Time::Repeat>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::sem::Time::Repeat>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::sem::Symbol::Param>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::Symbol::Param>::*)() const>(&hstd::Vec<org::sem::Symbol::Param>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<org::sem::Symbol::Param>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_SymbolParam>(static_cast<org::sem::Symbol::Param const&(hstd::Vec<org::sem::Symbol::Param>::*)(int) const>(&hstd::Vec<org::sem::Symbol::Param>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::sem::Symbol::Param>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::sem::Symbol::Param>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::ErrorSkipToken>>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::SemId<org::sem::ErrorSkipToken>>::*)() const>(&hstd::Vec<org::sem::SemId<org::sem::ErrorSkipToken>>::size), org_context, __self);
}
haxorg_SemIdOfOrg org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::ErrorSkipToken>>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::ErrorSkipToken> const&(hstd::Vec<org::sem::SemId<org::sem::ErrorSkipToken>>::*)(int) const>(&hstd::Vec<org::sem::SemId<org::sem::ErrorSkipToken>>::at), org_context, __self, idx);
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::ErrorSkipToken>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::ErrorSkipToken>>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::sem::SubtreePeriod>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::SubtreePeriod>::*)() const>(&hstd::Vec<org::sem::SubtreePeriod>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<org::sem::SubtreePeriod>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_SubtreePeriod>(static_cast<org::sem::SubtreePeriod const&(hstd::Vec<org::sem::SubtreePeriod>::*)(int) const>(&hstd::Vec<org::sem::SubtreePeriod>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::sem::SubtreePeriod>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::sem::SubtreePeriod>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::sem::NamedProperty>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::NamedProperty>::*)() const>(&hstd::Vec<org::sem::NamedProperty>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<org::sem::NamedProperty>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty>(static_cast<org::sem::NamedProperty const&(hstd::Vec<org::sem::NamedProperty>::*)(int) const>(&hstd::Vec<org::sem::NamedProperty>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::sem::NamedProperty>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::sem::NamedProperty>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::HashTag>>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::SemId<org::sem::HashTag>>::*)() const>(&hstd::Vec<org::sem::SemId<org::sem::HashTag>>::size), org_context, __self);
}
haxorg_SemIdOfOrg org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::HashTag>>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::HashTag> const&(hstd::Vec<org::sem::SemId<org::sem::HashTag>>::*)(int) const>(&hstd::Vec<org::sem::SemId<org::sem::HashTag>>::at), org_context, __self, idx);
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::HashTag>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::HashTag>>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::SubtreeLog>>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::SemId<org::sem::SubtreeLog>>::*)() const>(&hstd::Vec<org::sem::SemId<org::sem::SubtreeLog>>::size), org_context, __self);
}
haxorg_SemIdOfOrg org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::SubtreeLog>>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::SubtreeLog> const&(hstd::Vec<org::sem::SemId<org::sem::SubtreeLog>>::*)(int) const>(&hstd::Vec<org::sem::SemId<org::sem::SubtreeLog>>::at), org_context, __self, idx);
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::SubtreeLog>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::SubtreeLog>>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::sem::TodoKeyword>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::TodoKeyword>::*)() const>(&hstd::Vec<org::sem::TodoKeyword>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<org::sem::TodoKeyword>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_TodoKeyword>(static_cast<org::sem::TodoKeyword const&(hstd::Vec<org::sem::TodoKeyword>::*)(int) const>(&hstd::Vec<org::sem::TodoKeyword>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::sem::TodoKeyword>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::sem::TodoKeyword>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::BigIdent>>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::SemId<org::sem::BigIdent>>::*)() const>(&hstd::Vec<org::sem::SemId<org::sem::BigIdent>>::size), org_context, __self);
}
haxorg_SemIdOfOrg org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::BigIdent>>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::BigIdent> const&(hstd::Vec<org::sem::SemId<org::sem::BigIdent>>::*)(int) const>(&hstd::Vec<org::sem::SemId<org::sem::BigIdent>>::at), org_context, __self, idx);
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::BigIdent>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::BigIdent>>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<hstd::UserTime>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<hstd::UserTime>::*)() const>(&hstd::Vec<hstd::UserTime>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<hstd::UserTime>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_UserTime>(static_cast<hstd::UserTime const&(hstd::Vec<hstd::UserTime>::*)(int) const>(&hstd::Vec<hstd::UserTime>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<hstd::UserTime>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<hstd::UserTime>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::Time>>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::SemId<org::sem::Time>>::*)() const>(&hstd::Vec<org::sem::SemId<org::sem::Time>>::size), org_context, __self);
}
haxorg_SemIdOfOrg org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::Time>>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::Time> const&(hstd::Vec<org::sem::SemId<org::sem::Time>>::*)(int) const>(&hstd::Vec<org::sem::SemId<org::sem::Time>>::at), org_context, __self, idx);
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::Time>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::Time>>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::Cell>>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::SemId<org::sem::Cell>>::*)() const>(&hstd::Vec<org::sem::SemId<org::sem::Cell>>::size), org_context, __self);
}
haxorg_SemIdOfOrg org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::Cell>>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::Cell> const&(hstd::Vec<org::sem::SemId<org::sem::Cell>>::*)(int) const>(&hstd::Vec<org::sem::SemId<org::sem::Cell>>::at), org_context, __self, idx);
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::Cell>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::Cell>>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::sem::OrgCodeEvalOutput>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::OrgCodeEvalOutput>::*)() const>(&hstd::Vec<org::sem::OrgCodeEvalOutput>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<org::sem::OrgCodeEvalOutput>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_OrgCodeEvalOutput>(static_cast<org::sem::OrgCodeEvalOutput const&(hstd::Vec<org::sem::OrgCodeEvalOutput>::*)(int) const>(&hstd::Vec<org::sem::OrgCodeEvalOutput>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::sem::OrgCodeEvalOutput>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::sem::OrgCodeEvalOutput>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::BlockCodeEvalResult>>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::SemId<org::sem::BlockCodeEvalResult>>::*)() const>(&hstd::Vec<org::sem::SemId<org::sem::BlockCodeEvalResult>>::size), org_context, __self);
}
haxorg_SemIdOfOrg org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::BlockCodeEvalResult>>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::BlockCodeEvalResult> const&(hstd::Vec<org::sem::SemId<org::sem::BlockCodeEvalResult>>::*)(int) const>(&hstd::Vec<org::sem::SemId<org::sem::BlockCodeEvalResult>>::at), org_context, __self, idx);
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::BlockCodeEvalResult>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::BlockCodeEvalResult>>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::sem::BlockCodeLine>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::BlockCodeLine>::*)() const>(&hstd::Vec<org::sem::BlockCodeLine>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<org::sem::BlockCodeLine>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_BlockCodeLine>(static_cast<org::sem::BlockCodeLine const&(hstd::Vec<org::sem::BlockCodeLine>::*)(int) const>(&hstd::Vec<org::sem::BlockCodeLine>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::sem::BlockCodeLine>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::sem::BlockCodeLine>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::Row>>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::SemId<org::sem::Row>>::*)() const>(&hstd::Vec<org::sem::SemId<org::sem::Row>>::size), org_context, __self);
}
haxorg_SemIdOfOrg org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::Row>>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::Row> const&(hstd::Vec<org::sem::SemId<org::sem::Row>>::*)(int) const>(&hstd::Vec<org::sem::SemId<org::sem::Row>>::at), org_context, __self, idx);
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::Row>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::sem::SemId<org::sem::Row>>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<org::AstTrackingGroup>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::AstTrackingGroup>::*)() const>(&hstd::Vec<org::AstTrackingGroup>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<org::AstTrackingGroup>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_AstTrackingGroup>(static_cast<org::AstTrackingGroup const&(hstd::Vec<org::AstTrackingGroup>::*)(int) const>(&hstd::Vec<org::AstTrackingGroup>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<org::AstTrackingGroup>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<org::AstTrackingGroup>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<hstd::SequenceAnnotation>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<hstd::SequenceAnnotation>::*)() const>(&hstd::Vec<hstd::SequenceAnnotation>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<hstd::SequenceAnnotation>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_SequenceAnnotation>(static_cast<hstd::SequenceAnnotation const&(hstd::Vec<hstd::SequenceAnnotation>::*)(int) const>(&hstd::Vec<hstd::SequenceAnnotation>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<hstd::SequenceAnnotation>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<hstd::SequenceAnnotation>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
int org::bind::c::VTable<hstd::Vec<hstd::SequenceSegmentGroup>>::size_const(OrgContext* org_context, haxorg_HstdVec __self) {
  return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<hstd::SequenceSegmentGroup>::*)() const>(&hstd::Vec<hstd::SequenceSegmentGroup>::size), org_context, __self);
}
haxorg_ptr_payload org::bind::c::VTable<hstd::Vec<hstd::SequenceSegmentGroup>>::atIndex_const(OrgContext* org_context, haxorg_HstdVec __self, int idx) {
  return org::bind::c::execute_cpp<haxorg_SequenceSegmentGroup>(static_cast<hstd::SequenceSegmentGroup const&(hstd::Vec<hstd::SequenceSegmentGroup>::*)(int) const>(&hstd::Vec<hstd::SequenceSegmentGroup>::at), org_context, __self, idx).data;
}
haxorg_HstdVec_vtable const* org::bind::c::VTable<hstd::Vec<hstd::SequenceSegmentGroup>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::Vec<hstd::SequenceSegmentGroup>>;
  static haxorg_HstdVec_vtable const vtable{.size_const = &VtableType::size_const,
                                            .atIndex_const = &VtableType::atIndex_const,};
  return &vtable;
}
haxorg_HstdVec org::bind::c::VTable<hstd::UnorderedMap<org::sem::HashTagFlat, org::AstTrackingPath, std::hash<org::sem::HashTagFlat>>>::keys_const(OrgContext* org_context, haxorg_HstdMap __self) {
  return org::bind::c::execute_cpp<haxorg_HstdVec>(static_cast<hstd::Vec<org::sem::HashTagFlat>(hstd::UnorderedMap<org::sem::HashTagFlat, org::AstTrackingPath, std::hash<org::sem::HashTagFlat>>::*)() const>(&hstd::UnorderedMap<org::sem::HashTagFlat, org::AstTrackingPath, std::hash<org::sem::HashTagFlat>>::keys), org_context, __self);
}
haxorg_HstdMap_vtable const* org::bind::c::VTable<hstd::UnorderedMap<org::sem::HashTagFlat, org::AstTrackingPath, std::hash<org::sem::HashTagFlat>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::UnorderedMap<org::sem::HashTagFlat, org::AstTrackingPath, std::hash<org::sem::HashTagFlat>>>;
  static haxorg_HstdMap_vtable const vtable{.keys_const = &VtableType::keys_const,};
  return &vtable;
}
haxorg_HstdVec org::bind::c::VTable<hstd::UnorderedMap<hstd::Str, org::AstTrackingAlternatives, std::hash<hstd::Str>>>::keys_const(OrgContext* org_context, haxorg_HstdMap __self) {
  return org::bind::c::execute_cpp<haxorg_HstdVec>(static_cast<hstd::Vec<hstd::Str>(hstd::UnorderedMap<hstd::Str, org::AstTrackingAlternatives, std::hash<hstd::Str>>::*)() const>(&hstd::UnorderedMap<hstd::Str, org::AstTrackingAlternatives, std::hash<hstd::Str>>::keys), org_context, __self);
}
haxorg_HstdMap_vtable const* org::bind::c::VTable<hstd::UnorderedMap<hstd::Str, org::AstTrackingAlternatives, std::hash<hstd::Str>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::UnorderedMap<hstd::Str, org::AstTrackingAlternatives, std::hash<hstd::Str>>>;
  static haxorg_HstdMap_vtable const vtable{.keys_const = &VtableType::keys_const,};
  return &vtable;
}
haxorg_HstdVec org::bind::c::VTable<hstd::UnorderedMap<org::sem::HashTagFlat, org::AstTrackingAlternatives, std::hash<org::sem::HashTagFlat>>>::keys_const(OrgContext* org_context, haxorg_HstdMap __self) {
  return org::bind::c::execute_cpp<haxorg_HstdVec>(static_cast<hstd::Vec<org::sem::HashTagFlat>(hstd::UnorderedMap<org::sem::HashTagFlat, org::AstTrackingAlternatives, std::hash<org::sem::HashTagFlat>>::*)() const>(&hstd::UnorderedMap<org::sem::HashTagFlat, org::AstTrackingAlternatives, std::hash<org::sem::HashTagFlat>>::keys), org_context, __self);
}
haxorg_HstdMap_vtable const* org::bind::c::VTable<hstd::UnorderedMap<org::sem::HashTagFlat, org::AstTrackingAlternatives, std::hash<org::sem::HashTagFlat>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::UnorderedMap<org::sem::HashTagFlat, org::AstTrackingAlternatives, std::hash<org::sem::HashTagFlat>>>;
  static haxorg_HstdMap_vtable const vtable{.keys_const = &VtableType::keys_const,};
  return &vtable;
}
haxorg_HstdVec org::bind::c::VTable<hstd::UnorderedMap<org::graph::MapNode, org::graph::MapNodeProp, std::hash<org::graph::MapNode>>>::keys_const(OrgContext* org_context, haxorg_HstdMap __self) {
  return org::bind::c::execute_cpp<haxorg_HstdVec>(static_cast<hstd::Vec<org::graph::MapNode>(hstd::UnorderedMap<org::graph::MapNode, org::graph::MapNodeProp, std::hash<org::graph::MapNode>>::*)() const>(&hstd::UnorderedMap<org::graph::MapNode, org::graph::MapNodeProp, std::hash<org::graph::MapNode>>::keys), org_context, __self);
}
haxorg_HstdMap_vtable const* org::bind::c::VTable<hstd::UnorderedMap<org::graph::MapNode, org::graph::MapNodeProp, std::hash<org::graph::MapNode>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::UnorderedMap<org::graph::MapNode, org::graph::MapNodeProp, std::hash<org::graph::MapNode>>>;
  static haxorg_HstdMap_vtable const vtable{.keys_const = &VtableType::keys_const,};
  return &vtable;
}
haxorg_HstdVec org::bind::c::VTable<hstd::UnorderedMap<org::graph::MapEdge, org::graph::MapEdgeProp, std::hash<org::graph::MapEdge>>>::keys_const(OrgContext* org_context, haxorg_HstdMap __self) {
  return org::bind::c::execute_cpp<haxorg_HstdVec>(static_cast<hstd::Vec<org::graph::MapEdge>(hstd::UnorderedMap<org::graph::MapEdge, org::graph::MapEdgeProp, std::hash<org::graph::MapEdge>>::*)() const>(&hstd::UnorderedMap<org::graph::MapEdge, org::graph::MapEdgeProp, std::hash<org::graph::MapEdge>>::keys), org_context, __self);
}
haxorg_HstdMap_vtable const* org::bind::c::VTable<hstd::UnorderedMap<org::graph::MapEdge, org::graph::MapEdgeProp, std::hash<org::graph::MapEdge>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::UnorderedMap<org::graph::MapEdge, org::graph::MapEdgeProp, std::hash<org::graph::MapEdge>>>;
  static haxorg_HstdMap_vtable const vtable{.keys_const = &VtableType::keys_const,};
  return &vtable;
}
haxorg_HstdVec org::bind::c::VTable<hstd::UnorderedMap<org::graph::MapNode, org::graph::AdjNodesList, std::hash<org::graph::MapNode>>>::keys_const(OrgContext* org_context, haxorg_HstdMap __self) {
  return org::bind::c::execute_cpp<haxorg_HstdVec>(static_cast<hstd::Vec<org::graph::MapNode>(hstd::UnorderedMap<org::graph::MapNode, org::graph::AdjNodesList, std::hash<org::graph::MapNode>>::*)() const>(&hstd::UnorderedMap<org::graph::MapNode, org::graph::AdjNodesList, std::hash<org::graph::MapNode>>::keys), org_context, __self);
}
haxorg_HstdMap_vtable const* org::bind::c::VTable<hstd::UnorderedMap<org::graph::MapNode, org::graph::AdjNodesList, std::hash<org::graph::MapNode>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::UnorderedMap<org::graph::MapNode, org::graph::AdjNodesList, std::hash<org::graph::MapNode>>>;
  static haxorg_HstdMap_vtable const vtable{.keys_const = &VtableType::keys_const,};
  return &vtable;
}
haxorg_HstdVec org::bind::c::VTable<hstd::UnorderedMap<hstd::Str, org::sem::AttrList, std::hash<hstd::Str>>>::keys_const(OrgContext* org_context, haxorg_HstdMap __self) {
  return org::bind::c::execute_cpp<haxorg_HstdVec>(static_cast<hstd::Vec<hstd::Str>(hstd::UnorderedMap<hstd::Str, org::sem::AttrList, std::hash<hstd::Str>>::*)() const>(&hstd::UnorderedMap<hstd::Str, org::sem::AttrList, std::hash<hstd::Str>>::keys), org_context, __self);
}
haxorg_HstdMap_vtable const* org::bind::c::VTable<hstd::UnorderedMap<hstd::Str, org::sem::AttrList, std::hash<hstd::Str>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::UnorderedMap<hstd::Str, org::sem::AttrList, std::hash<hstd::Str>>>;
  static haxorg_HstdMap_vtable const vtable{.keys_const = &VtableType::keys_const,};
  return &vtable;
}
haxorg_HstdVec org::bind::c::VTable<hstd::UnorderedMap<hstd::Str, hstd::Str, std::hash<hstd::Str>>>::keys_const(OrgContext* org_context, haxorg_HstdMap __self) {
  return org::bind::c::execute_cpp<haxorg_HstdVec>(static_cast<hstd::Vec<hstd::Str>(hstd::UnorderedMap<hstd::Str, hstd::Str, std::hash<hstd::Str>>::*)() const>(&hstd::UnorderedMap<hstd::Str, hstd::Str, std::hash<hstd::Str>>::keys), org_context, __self);
}
haxorg_HstdMap_vtable const* org::bind::c::VTable<hstd::UnorderedMap<hstd::Str, hstd::Str, std::hash<hstd::Str>>>::get_vtable() {
  using VtableType = org::bind::c::VTable<hstd::UnorderedMap<hstd::Str, hstd::Str, std::hash<hstd::Str>>>;
  static haxorg_HstdMap_vtable const vtable{.keys_const = &VtableType::keys_const,};
  return &vtable;
}
/* clang-format on */
