/* clang-format off */
#include <wrappers/c/haxorg_c.h>
#include <wrappers/c/haxorg_c_utils.hpp>
#include <wrappers/c/haxorg_c_vtables.hpp>
#include <wrappers/c/haxorg_c_vtables_manual.hpp>
haxorg_TblfmExprAxisRefPosition org::bind::c::VTable<hstd::Opt<org::sem::Tblfm::Expr::AxisRef::Position>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPosition>(static_cast<org::sem::Tblfm::Expr::AxisRef::Position const&(hstd::Opt<org::sem::Tblfm::Expr::AxisRef::Position>::*)()>(&hstd::Opt<org::sem::Tblfm::Expr::AxisRef::Position>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<org::sem::Tblfm::Expr::AxisRef::Position>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<org::sem::Tblfm::Expr::AxisRef::Position>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_TblfmExprAxisRef org::bind::c::VTable<hstd::Opt<org::sem::Tblfm::Expr::AxisRef>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRef>(static_cast<org::sem::Tblfm::Expr::AxisRef const&(hstd::Opt<org::sem::Tblfm::Expr::AxisRef>::*)()>(&hstd::Opt<org::sem::Tblfm::Expr::AxisRef>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<org::sem::Tblfm::Expr::AxisRef>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<org::sem::Tblfm::Expr::AxisRef>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
bool const& org::bind::c::VTable<hstd::Opt<bool>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<bool const&>(static_cast<bool const&(hstd::Opt<bool>::*)()>(&hstd::Opt<bool>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<bool>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<bool>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
int const& org::bind::c::VTable<hstd::Opt<int>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<int const&>(static_cast<int const&(hstd::Opt<int>::*)()>(&hstd::Opt<int>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<int>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<int>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
double const& org::bind::c::VTable<hstd::Opt<double>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<double const&>(static_cast<double const&(hstd::Opt<double>::*)()>(&hstd::Opt<double>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<double>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<double>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_HstdStr org::bind::c::VTable<hstd::Opt<hstd::Str>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(hstd::Opt<hstd::Str>::*)()>(&hstd::Opt<hstd::Str>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<hstd::Str>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<hstd::Str>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_StdString org::bind::c::VTable<hstd::Opt<std::string>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_StdString>(static_cast<std::string const&(hstd::Opt<std::string>::*)()>(&hstd::Opt<std::string>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<std::string>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<std::string>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_UserTime org::bind::c::VTable<hstd::Opt<hstd::UserTime>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_UserTime>(static_cast<hstd::UserTime const&(hstd::Opt<hstd::UserTime>::*)()>(&hstd::Opt<hstd::UserTime>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<hstd::UserTime>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<hstd::UserTime>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_AttrValue org::bind::c::VTable<hstd::Opt<org::sem::AttrValue>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_AttrValue>(static_cast<org::sem::AttrValue const&(hstd::Opt<org::sem::AttrValue>::*)()>(&hstd::Opt<org::sem::AttrValue>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<org::sem::AttrValue>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<org::sem::AttrValue>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_AttrList org::bind::c::VTable<hstd::Opt<org::sem::AttrList>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_AttrList>(static_cast<org::sem::AttrList const&(hstd::Opt<org::sem::AttrList>::*)()>(&hstd::Opt<org::sem::AttrList>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<org::sem::AttrList>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<org::sem::AttrList>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_OrgCodeEvalInputVar org::bind::c::VTable<hstd::Opt<org::sem::OrgCodeEvalInput::Var>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_OrgCodeEvalInputVar>(static_cast<org::sem::OrgCodeEvalInput::Var const&(hstd::Opt<org::sem::OrgCodeEvalInput::Var>::*)()>(&hstd::Opt<org::sem::OrgCodeEvalInput::Var>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<org::sem::OrgCodeEvalInput::Var>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<org::sem::OrgCodeEvalInput::Var>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_ColumnViewSummary org::bind::c::VTable<hstd::Opt<org::sem::ColumnView::Summary>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_ColumnViewSummary>(static_cast<org::sem::ColumnView::Summary const&(hstd::Opt<org::sem::ColumnView::Summary>::*)()>(&hstd::Opt<org::sem::ColumnView::Summary>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<org::sem::ColumnView::Summary>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<org::sem::ColumnView::Summary>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_ParseSourceLoc org::bind::c::VTable<hstd::Opt<org::parse::SourceLoc>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_ParseSourceLoc>(static_cast<org::parse::SourceLoc const&(hstd::Opt<org::parse::SourceLoc>::*)()>(&hstd::Opt<org::parse::SourceLoc>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<org::parse::SourceLoc>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<org::parse::SourceLoc>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_AttrValueLispValue org::bind::c::VTable<hstd::Opt<org::sem::AttrValue::LispValue>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_AttrValueLispValue>(static_cast<org::sem::AttrValue::LispValue const&(hstd::Opt<org::sem::AttrValue::LispValue>::*)()>(&hstd::Opt<org::sem::AttrValue::LispValue>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<org::sem::AttrValue::LispValue>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<org::sem::AttrValue::LispValue>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_AttrValueKind org::bind::c::VTable<hstd::Opt<org::sem::AttrValue::Kind>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_AttrValueKind>(static_cast<org::sem::AttrValue::Kind const&(hstd::Opt<org::sem::AttrValue::Kind>::*)()>(&hstd::Opt<org::sem::AttrValue::Kind>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<org::sem::AttrValue::Kind>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<org::sem::AttrValue::Kind>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_TimeRepeat org::bind::c::VTable<hstd::Opt<org::sem::Time::Repeat>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_TimeRepeat>(static_cast<org::sem::Time::Repeat const&(hstd::Opt<org::sem::Time::Repeat>::*)()>(&hstd::Opt<org::sem::Time::Repeat>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<org::sem::Time::Repeat>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<org::sem::Time::Repeat>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
int64_t const& org::bind::c::VTable<hstd::Opt<int64_t>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<int64_t const&>(static_cast<int64_t const&(hstd::Opt<int64_t>::*)()>(&hstd::Opt<int64_t>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<int64_t>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<int64_t>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_SemIdOfOrg org::bind::c::VTable<hstd::Opt<org::sem::SemId<org::sem::StmtList>>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::StmtList> const&(hstd::Opt<org::sem::SemId<org::sem::StmtList>>::*)()>(&hstd::Opt<org::sem::SemId<org::sem::StmtList>>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<org::sem::SemId<org::sem::StmtList>>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<org::sem::SemId<org::sem::StmtList>>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_NamedProperty org::bind::c::VTable<hstd::Opt<org::sem::NamedProperty>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_NamedProperty>(static_cast<org::sem::NamedProperty const&(hstd::Opt<org::sem::NamedProperty>::*)()>(&hstd::Opt<org::sem::NamedProperty>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<org::sem::NamedProperty>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<org::sem::NamedProperty>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_SubtreeCompletion org::bind::c::VTable<hstd::Opt<org::sem::SubtreeCompletion>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_SubtreeCompletion>(static_cast<org::sem::SubtreeCompletion const&(hstd::Opt<org::sem::SubtreeCompletion>::*)()>(&hstd::Opt<org::sem::SubtreeCompletion>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<org::sem::SubtreeCompletion>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<org::sem::SubtreeCompletion>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_SemIdOfOrg org::bind::c::VTable<hstd::Opt<org::sem::SemId<org::sem::Paragraph>>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::Paragraph> const&(hstd::Opt<org::sem::SemId<org::sem::Paragraph>>::*)()>(&hstd::Opt<org::sem::SemId<org::sem::Paragraph>>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<org::sem::SemId<org::sem::Paragraph>>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<org::sem::SemId<org::sem::Paragraph>>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_SemIdOfOrg org::bind::c::VTable<hstd::Opt<org::sem::SemId<org::sem::Time>>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::Time> const&(hstd::Opt<org::sem::SemId<org::sem::Time>>::*)()>(&hstd::Opt<org::sem::SemId<org::sem::Time>>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<org::sem::SemId<org::sem::Time>>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<org::sem::SemId<org::sem::Time>>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_ColumnView org::bind::c::VTable<hstd::Opt<org::sem::ColumnView>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_ColumnView>(static_cast<org::sem::ColumnView const&(hstd::Opt<org::sem::ColumnView>::*)()>(&hstd::Opt<org::sem::ColumnView>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<org::sem::ColumnView>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<org::sem::ColumnView>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_SemIdOfOrg org::bind::c::VTable<hstd::Opt<org::sem::SemId<org::sem::RawText>>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::RawText> const&(hstd::Opt<org::sem::SemId<org::sem::RawText>>::*)()>(&hstd::Opt<org::sem::SemId<org::sem::RawText>>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<org::sem::SemId<org::sem::RawText>>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<org::sem::SemId<org::sem::RawText>>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_SubtreePath org::bind::c::VTable<hstd::Opt<org::sem::SubtreePath>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_SubtreePath>(static_cast<org::sem::SubtreePath const&(hstd::Opt<org::sem::SubtreePath>::*)()>(&hstd::Opt<org::sem::SubtreePath>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<org::sem::SubtreePath>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<org::sem::SubtreePath>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_ImmTimeRepeat org::bind::c::VTable<hstd::Opt<org::imm::ImmTime::Repeat>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_ImmTimeRepeat>(static_cast<org::imm::ImmTime::Repeat const&(hstd::Opt<org::imm::ImmTime::Repeat>::*)()>(&hstd::Opt<org::imm::ImmTime::Repeat>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<org::imm::ImmTime::Repeat>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<org::imm::ImmTime::Repeat>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_ImmId org::bind::c::VTable<hstd::Opt<org::imm::ImmIdT<org::imm::ImmStmtList>>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_ImmId>(static_cast<org::imm::ImmIdT<org::imm::ImmStmtList> const&(hstd::Opt<org::imm::ImmIdT<org::imm::ImmStmtList>>::*)()>(&hstd::Opt<org::imm::ImmIdT<org::imm::ImmStmtList>>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<org::imm::ImmIdT<org::imm::ImmStmtList>>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<org::imm::ImmIdT<org::imm::ImmStmtList>>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_ImmId org::bind::c::VTable<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_ImmId>(static_cast<org::imm::ImmIdT<org::imm::ImmParagraph> const&(hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>::*)()>(&hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_ImmId org::bind::c::VTable<hstd::Opt<org::imm::ImmIdT<org::imm::ImmTime>>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_ImmId>(static_cast<org::imm::ImmIdT<org::imm::ImmTime> const&(hstd::Opt<org::imm::ImmIdT<org::imm::ImmTime>>::*)()>(&hstd::Opt<org::imm::ImmIdT<org::imm::ImmTime>>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<org::imm::ImmIdT<org::imm::ImmTime>>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<org::imm::ImmIdT<org::imm::ImmTime>>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_ImmId org::bind::c::VTable<hstd::Opt<org::imm::ImmIdT<org::imm::ImmRawText>>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_ImmId>(static_cast<org::imm::ImmIdT<org::imm::ImmRawText> const&(hstd::Opt<org::imm::ImmIdT<org::imm::ImmRawText>>::*)()>(&hstd::Opt<org::imm::ImmIdT<org::imm::ImmRawText>>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<org::imm::ImmIdT<org::imm::ImmRawText>>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<org::imm::ImmIdT<org::imm::ImmRawText>>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_SemIdOfOrg org::bind::c::VTable<hstd::Opt<org::sem::SemId<org::sem::Org>>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::Org> const&(hstd::Opt<org::sem::SemId<org::sem::Org>>::*)()>(&hstd::Opt<org::sem::SemId<org::sem::Org>>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<org::sem::SemId<org::sem::Org>>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<org::sem::SemId<org::sem::Org>>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_ImmId org::bind::c::VTable<hstd::Opt<org::imm::ImmIdT<org::imm::ImmOrg>>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_ImmId>(static_cast<org::imm::ImmIdT<org::imm::ImmOrg> const&(hstd::Opt<org::imm::ImmIdT<org::imm::ImmOrg>>::*)()>(&hstd::Opt<org::imm::ImmIdT<org::imm::ImmOrg>>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<org::imm::ImmIdT<org::imm::ImmOrg>>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<org::imm::ImmIdT<org::imm::ImmOrg>>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_ImmParagraphAdapter org::bind::c::VTable<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_ImmParagraphAdapter>(static_cast<org::imm::ImmAdapterT<org::imm::ImmParagraph> const&(hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>::*)()>(&hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_ImmTimeAdapter org::bind::c::VTable<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime>>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_ImmTimeAdapter>(static_cast<org::imm::ImmAdapterT<org::imm::ImmTime> const&(hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime>>::*)()>(&hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime>>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime>>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime>>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_ImmStmtListAdapter org::bind::c::VTable<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmStmtList>>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_ImmStmtListAdapter>(static_cast<org::imm::ImmAdapterT<org::imm::ImmStmtList> const&(hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmStmtList>>::*)()>(&hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmStmtList>>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmStmtList>>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmStmtList>>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_ImmRawTextAdapter org::bind::c::VTable<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmRawText>>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_ImmRawTextAdapter>(static_cast<org::imm::ImmAdapterT<org::imm::ImmRawText> const&(hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmRawText>>::*)()>(&hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmRawText>>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmRawText>>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmRawText>>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
haxorg_ImmAdapter org::bind::c::VTable<hstd::Opt<org::imm::ImmAdapter>>::value(OrgContext* org_context, haxorg_ptr_payload self) {
  return org::bind::c::execute_cpp<haxorg_ImmAdapter>(static_cast<org::imm::ImmAdapter const&(hstd::Opt<org::imm::ImmAdapter>::*)()>(&hstd::Opt<org::imm::ImmAdapter>::value), org_context, self);
}
haxorg_Opt_vtable const* org::bind::c::VTable<hstd::Opt<org::imm::ImmAdapter>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::Opt<org::imm::ImmAdapter>>;
  static haxorg_Opt_vtable const vtable{.value = &Self::value,};
  return &vtable;
}
/* clang-format on */
