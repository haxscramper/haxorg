/* clang-format off */
#pragma once
#include <wrappers/c/haxorg_c.h>
#include <wrappers/c/haxorg_c_utils.hpp>
#include <wrappers/c/haxorg_c_vtables_manual.hpp>
template <>
struct org::bind::c::VTable<hstd::Opt<org::sem::Tblfm::Expr::AxisRef::Position>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<org::sem::Tblfm::Expr::AxisRef>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<bool>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static bool const& value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<int>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int const& value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<double>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static double const& value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<hstd::Str>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<std::string>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_StdString value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<hstd::UserTime>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<org::sem::AttrValue>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<org::sem::AttrList>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<org::sem::OrgCodeEvalInput::Var>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<org::sem::ColumnView::Summary>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<org::parse::SourceLoc>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<org::sem::AttrValue::LispValue>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<org::sem::AttrValue::Kind>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<org::sem::Time::Repeat>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<int64_t>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static int64_t const& value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<org::sem::SemId<org::sem::StmtList>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_SemIdOfOrg value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<org::sem::NamedProperty>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<org::sem::SubtreeCompletion>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<org::sem::SemId<org::sem::Paragraph>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_SemIdOfOrg value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<org::sem::SemId<org::sem::Time>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_SemIdOfOrg value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<org::sem::ColumnView>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<org::sem::SemId<org::sem::RawText>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_SemIdOfOrg value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<org::sem::SubtreePath>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<org::imm::ImmTime::Repeat>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<org::imm::ImmIdT<org::imm::ImmStmtList>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmId value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmId value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<org::imm::ImmIdT<org::imm::ImmTime>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmId value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<org::imm::ImmIdT<org::imm::ImmRawText>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmId value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<org::sem::SemId<org::sem::Org>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_SemIdOfOrg value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<org::imm::ImmIdT<org::imm::ImmOrg>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmId value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmParagraphAdapter value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmTimeAdapter value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmStmtList>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmStmtListAdapter value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmRawText>>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ImmRawTextAdapter value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

template <>
struct org::bind::c::VTable<hstd::Opt<org::imm::ImmAdapter>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_ptr_payload value(OrgContext* org_context, haxorg_ptr_payload __self);
  static haxorg_Opt_vtable const* get_vtable();
};

/* clang-format on */
