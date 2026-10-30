/* clang-format off */
#include "tUnidataDSLModel.hpp"
namespace ud = hstd::ext::unidata;


hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::TrivialText::__check_text_text_check(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::TrivialText const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::TrivialText>>::RootValue(this_obj_ptr, ctx->getPath());
  // lt typed_as='bool'
  //     const_int typed_as='int64' int_val=0
  //     str_size typed_as='int64'
  //         this typed_as='string'
  //
  auto const& expr0 = (this_obj.Field(&this_obj.get()->text, "text"));
  int64_t const& expr1 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
  int64_t const& expr2 = ud::eval_str_size<int64_t>(expr0);
  bool const& expr3 = ud::eval_lt<bool>(expr1, expr2);
  if (expr3) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr4 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("text must not be empty"), "text must not be empty");
    return ud::VerifyResult::Error(*expr4.get());
  }
}
hstd::ext::unidata::VerifyCheckCollection const* hstd::unidata_dsl::test::TrivialText::get_unidata_checks() {
  static hstd::ext::unidata::VerifyCheckCollection checks
   = {{
      {hstd::ext::unidata::VerifyKey{"TrivialText", "text"}, hstd::ext::unidata::VerifyCbList{hstd::ext::unidata::VerifyCb{&__check_text_text_check}}}
      }};
  return &checks;
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::Base::__check_record_base_positive_id(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::Base const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::Base>>::RootValue(this_obj_ptr, ctx->getPath());
  // lt typed_as='bool'
  //     const_int typed_as='int64' int_val=0
  //     get_field typed_as='int64' str_val='id'
  //         this typed_as='Base'
  //
  auto const& expr0 = (this_obj);
  int64_t const& expr1 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
  int64_t const& expr2 = expr0.Field(&expr0.get()->id, "id");
  bool const& expr3 = ud::eval_lt<bool>(expr1, expr2);
  if (expr3) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr4 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("base id must be positive"), "base id must be positive");
    return ud::VerifyResult::Error(*expr4.get());
  }
}
hstd::ext::unidata::VerifyCheckCollection const* hstd::unidata_dsl::test::Base::get_unidata_checks() {
  static hstd::ext::unidata::VerifyCheckCollection checks
   = {{
      {hstd::ext::unidata::VerifyKey{"Base", std::nullopt}, hstd::ext::unidata::VerifyCbList{hstd::ext::unidata::VerifyCb{&__check_record_base_positive_id}}}
      }};
  return &checks;
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::Derived::__check_record_derived_positive_weight(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::Derived const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::Derived>>::RootValue(this_obj_ptr, ctx->getPath());
  // lt typed_as='bool'
  //     const_int typed_as='int64' int_val=0
  //     get_field typed_as='int64' str_val='weight'
  //         this typed_as='Derived'
  //
  auto const& expr0 = (this_obj);
  int64_t const& expr1 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
  int64_t const& expr2 = expr0.Field(&expr0.get()->weight, "weight");
  bool const& expr3 = ud::eval_lt<bool>(expr1, expr2);
  if (expr3) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr4 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("derived weight must be positive"), "derived weight must be positive");
    return ud::VerifyResult::Error(*expr4.get());
  }
}
hstd::ext::unidata::VerifyCheckCollection const* hstd::unidata_dsl::test::Derived::get_unidata_checks() {
  static hstd::ext::unidata::VerifyCheckCollection checks
   = {{
      {hstd::ext::unidata::VerifyKey{"Derived", std::nullopt}, hstd::ext::unidata::VerifyCbList{hstd::ext::unidata::VerifyCb{&__check_record_derived_positive_weight}}}
      }};
  return &checks;
}
bool hstd::unidata_dsl::test::Choice::isFirst() const {
  return getKind() == Kind::First;
}
hstd::unidata_dsl::test::Choice::First const& hstd::unidata_dsl::test::Choice::getFirst() const {
  return hstd::variant_get<0>(data);
}
hstd::unidata_dsl::test::Choice::First& hstd::unidata_dsl::test::Choice::getFirst() {
  return hstd::variant_get<0>(data);
}
bool hstd::unidata_dsl::test::Choice::isSecond() const {
  return getKind() == Kind::Second;
}
hstd::unidata_dsl::test::Choice::Second const& hstd::unidata_dsl::test::Choice::getSecond() const {
  return hstd::variant_get<1>(data);
}
hstd::unidata_dsl::test::Choice::Second& hstd::unidata_dsl::test::Choice::getSecond() {
  return hstd::variant_get<1>(data);
}
hstd::unidata_dsl::test::Choice::Kind hstd::unidata_dsl::test::Choice::getKind(hstd::unidata_dsl::test::Choice::Data const& __input) {
  return static_cast<hstd::unidata_dsl::test::Choice::Kind>(__input.index());
}
hstd::unidata_dsl::test::Choice::Kind hstd::unidata_dsl::test::Choice::getKind() const {
  return getKind(data);
}
char const* hstd::unidata_dsl::test::Choice::sub_variant_get_name() const {
  return "data";
}
hstd::unidata_dsl::test::Choice::Data const& hstd::unidata_dsl::test::Choice::sub_variant_get_data() const {
  return data;
}
hstd::unidata_dsl::test::Choice::Kind hstd::unidata_dsl::test::Choice::sub_variant_get_kind() const {
  return getKind();
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Eq(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='Eq'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         get_field typed_as='int64' str_val='number'
  //             this typed_as='OperationChecks'
  //         const_int typed_as='int64' int_val=6
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::Eq);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    int64_t const& expr5 = expr0.Field(&expr0.get()->number, "number");
    int64_t const& expr6 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(6), "6");
    bool const& expr7 = ud::eval_eq<bool>(expr5, expr6);
    condition1 = expr7;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr8 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.Eq"), "poc.Eq");
    return ud::VerifyResult::Error(*expr8.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Ne(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='Ne'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     ne typed_as='bool'
  //         get_field typed_as='int64' str_val='number'
  //             this typed_as='OperationChecks'
  //         const_int typed_as='int64' int_val=8
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::Ne);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    int64_t const& expr5 = expr0.Field(&expr0.get()->number, "number");
    int64_t const& expr6 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(8), "8");
    bool const& expr7 = ud::eval_ne<bool>(expr5, expr6);
    condition1 = expr7;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr8 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.Ne"), "poc.Ne");
    return ud::VerifyResult::Error(*expr8.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Lt(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='Lt'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     lt typed_as='bool'
  //         get_field typed_as='int64' str_val='number'
  //             this typed_as='OperationChecks'
  //         const_int typed_as='int64' int_val=7
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::Lt);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    int64_t const& expr5 = expr0.Field(&expr0.get()->number, "number");
    int64_t const& expr6 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(7), "7");
    bool const& expr7 = ud::eval_lt<bool>(expr5, expr6);
    condition1 = expr7;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr8 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.Lt"), "poc.Lt");
    return ud::VerifyResult::Error(*expr8.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Le(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='Le'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     le typed_as='bool'
  //         get_field typed_as='int64' str_val='number'
  //             this typed_as='OperationChecks'
  //         const_int typed_as='int64' int_val=6
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::Le);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    int64_t const& expr5 = expr0.Field(&expr0.get()->number, "number");
    int64_t const& expr6 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(6), "6");
    bool const& expr7 = ud::eval_le<bool>(expr5, expr6);
    condition1 = expr7;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr8 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.Le"), "poc.Le");
    return ud::VerifyResult::Error(*expr8.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Add(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='Add'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         add typed_as='int64'
  //             get_field typed_as='int64' str_val='number'
  //                 this typed_as='OperationChecks'
  //             const_int typed_as='int64' int_val=3
  //         const_int typed_as='int64' int_val=9
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::Add);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    int64_t const& expr5 = expr0.Field(&expr0.get()->number, "number");
    int64_t const& expr6 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(3), "3");
    int64_t const& expr7 = ud::eval_add<int64_t>(expr5, expr6);
    int64_t const& expr8 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(9), "9");
    bool const& expr9 = ud::eval_eq<bool>(expr7, expr8);
    condition1 = expr9;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr10 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.Add"), "poc.Add");
    return ud::VerifyResult::Error(*expr10.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Sub(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='Sub'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         sub typed_as='int64'
  //             get_field typed_as='int64' str_val='number'
  //                 this typed_as='OperationChecks'
  //             const_int typed_as='int64' int_val=3
  //         const_int typed_as='int64' int_val=3
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::Sub);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    int64_t const& expr5 = expr0.Field(&expr0.get()->number, "number");
    int64_t const& expr6 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(3), "3");
    int64_t const& expr7 = ud::eval_sub<int64_t>(expr5, expr6);
    int64_t const& expr8 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(3), "3");
    bool const& expr9 = ud::eval_eq<bool>(expr7, expr8);
    condition1 = expr9;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr10 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.Sub"), "poc.Sub");
    return ud::VerifyResult::Error(*expr10.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Mul(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='Mul'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         mul typed_as='int64'
  //             get_field typed_as='int64' str_val='number'
  //                 this typed_as='OperationChecks'
  //             const_int typed_as='int64' int_val=3
  //         const_int typed_as='int64' int_val=18
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::Mul);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    int64_t const& expr5 = expr0.Field(&expr0.get()->number, "number");
    int64_t const& expr6 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(3), "3");
    int64_t const& expr7 = ud::eval_mul<int64_t>(expr5, expr6);
    int64_t const& expr8 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(18), "18");
    bool const& expr9 = ud::eval_eq<bool>(expr7, expr8);
    condition1 = expr9;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr10 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.Mul"), "poc.Mul");
    return ud::VerifyResult::Error(*expr10.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Div(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='Div'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         div typed_as='int64'
  //             get_field typed_as='int64' str_val='number'
  //                 this typed_as='OperationChecks'
  //             const_int typed_as='int64' int_val=3
  //         const_int typed_as='int64' int_val=2
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::Div);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    int64_t const& expr5 = expr0.Field(&expr0.get()->number, "number");
    int64_t const& expr6 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(3), "3");
    int64_t const& expr7 = ud::eval_div<int64_t>(expr5, expr6);
    int64_t const& expr8 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(2), "2");
    bool const& expr9 = ud::eval_eq<bool>(expr7, expr8);
    condition1 = expr9;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr10 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.Div"), "poc.Div");
    return ud::VerifyResult::Error(*expr10.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ConstFloat(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='ConstFloat'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     and typed_as='bool'
  //         eq typed_as='bool'
  //             get_field typed_as='float64' str_val='real'
  //                 this typed_as='OperationChecks'
  //             const_float typed_as='float64' float_val=2.5
  //         eq typed_as='bool'
  //             div typed_as='float64'
  //                 get_field typed_as='float64' str_val='real'
  //                     this typed_as='OperationChecks'
  //                 const_float typed_as='float64' float_val=2.0
  //             const_float typed_as='float64' float_val=1.25
  //         eq typed_as='bool'
  //             mul typed_as='float64'
  //                 get_field typed_as='float64' str_val='real'
  //                     this typed_as='OperationChecks'
  //                 const_float typed_as='float64' float_val=2.0
  //             const_float typed_as='float64' float_val=5.0
  //         eq typed_as='bool'
  //             sub typed_as='float64'
  //                 get_field typed_as='float64' str_val='real'
  //                     this typed_as='OperationChecks'
  //                 const_float typed_as='float64' float_val=0.5
  //             const_float typed_as='float64' float_val=2.0
  //         eq typed_as='bool'
  //             add typed_as='float64'
  //                 get_field typed_as='float64' str_val='real'
  //                     this typed_as='OperationChecks'
  //                 const_float typed_as='float64' float_val=0.5
  //             const_float typed_as='float64' float_val=3.0
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::ConstFloat);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    auto condition5 = ud::UniValue<ud::StaticT<bool>>::FromConst(true, "true");
    if (*condition5.get()) {
      double const& expr6 = expr0.Field(&expr0.get()->real, "real");
      double const& expr7 = ud::UniValue<ud::StaticT<double>>::FromConst(static_cast<double>(2.5), "2.5");
      bool const& expr8 = ud::eval_eq<bool>(expr6, expr7);
      condition5 = expr8;
    }
    if (*condition5.get()) {
      double const& expr9 = expr0.Field(&expr0.get()->real, "real");
      double const& expr10 = ud::UniValue<ud::StaticT<double>>::FromConst(static_cast<double>(2.0), "2.0");
      double const& expr11 = ud::eval_div<double>(expr9, expr10);
      double const& expr12 = ud::UniValue<ud::StaticT<double>>::FromConst(static_cast<double>(1.25), "1.25");
      bool const& expr13 = ud::eval_eq<bool>(expr11, expr12);
      condition5 = expr13;
    }
    if (*condition5.get()) {
      double const& expr14 = expr0.Field(&expr0.get()->real, "real");
      double const& expr15 = ud::UniValue<ud::StaticT<double>>::FromConst(static_cast<double>(2.0), "2.0");
      double const& expr16 = ud::eval_mul<double>(expr14, expr15);
      double const& expr17 = ud::UniValue<ud::StaticT<double>>::FromConst(static_cast<double>(5.0), "5.0");
      bool const& expr18 = ud::eval_eq<bool>(expr16, expr17);
      condition5 = expr18;
    }
    if (*condition5.get()) {
      double const& expr19 = expr0.Field(&expr0.get()->real, "real");
      double const& expr20 = ud::UniValue<ud::StaticT<double>>::FromConst(static_cast<double>(0.5), "0.5");
      double const& expr21 = ud::eval_sub<double>(expr19, expr20);
      double const& expr22 = ud::UniValue<ud::StaticT<double>>::FromConst(static_cast<double>(2.0), "2.0");
      bool const& expr23 = ud::eval_eq<bool>(expr21, expr22);
      condition5 = expr23;
    }
    if (*condition5.get()) {
      double const& expr24 = expr0.Field(&expr0.get()->real, "real");
      double const& expr25 = ud::UniValue<ud::StaticT<double>>::FromConst(static_cast<double>(0.5), "0.5");
      double const& expr26 = ud::eval_add<double>(expr24, expr25);
      double const& expr27 = ud::UniValue<ud::StaticT<double>>::FromConst(static_cast<double>(3.0), "3.0");
      bool const& expr28 = ud::eval_eq<bool>(expr26, expr27);
      condition5 = expr28;
    }
    condition1 = *condition5.get();
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr29 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.ConstFloat"), "poc.ConstFloat");
    return ud::VerifyResult::Error(*expr29.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ConstBool(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='ConstBool'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         get_field typed_as='bool' str_val='flag'
  //             this typed_as='OperationChecks'
  //         const_bool typed_as='bool' bool_val=True
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::ConstBool);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    bool const& expr5 = expr0.Field(&expr0.get()->flag, "flag");
    bool const& expr6 = ud::UniValue<ud::StaticT<bool>>::FromConst(static_cast<bool>(true), "true");
    bool const& expr7 = ud::eval_eq<bool>(expr5, expr6);
    condition1 = expr7;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr8 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.ConstBool"), "poc.ConstBool");
    return ud::VerifyResult::Error(*expr8.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_And(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='And'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     and typed_as='bool'
  //         get_field typed_as='bool' str_val='flag'
  //             this typed_as='OperationChecks'
  //         eq typed_as='bool'
  //             get_field typed_as='int64' str_val='number'
  //                 this typed_as='OperationChecks'
  //             const_int typed_as='int64' int_val=6
  //         eq typed_as='bool'
  //             map_get typed_as='int64'
  //                 get_field typed_as='map<string, int64>' str_val='mapping'
  //                     this typed_as='OperationChecks'
  //                 const_str typed_as='string' str_val='a'
  //             const_int typed_as='int64' int_val=1
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::And);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    auto condition5 = ud::UniValue<ud::StaticT<bool>>::FromConst(true, "true");
    if (*condition5.get()) {
      bool const& expr6 = expr0.Field(&expr0.get()->flag, "flag");
      condition5 = expr6;
    }
    if (*condition5.get()) {
      int64_t const& expr7 = expr0.Field(&expr0.get()->number, "number");
      int64_t const& expr8 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(6), "6");
      bool const& expr9 = ud::eval_eq<bool>(expr7, expr8);
      condition5 = expr9;
    }
    if (*condition5.get()) {
      hstd::UnorderedMap<hstd::Str, int64_t> const& expr10 = expr0.Field(&expr0.get()->mapping, "mapping");
      hstd::Str const& expr11 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("a"), "a");
      int64_t const& expr12 = ud::eval_map_get<int64_t>(expr10, expr11);
      int64_t const& expr13 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(1), "1");
      bool const& expr14 = ud::eval_eq<bool>(expr12, expr13);
      condition5 = expr14;
    }
    condition1 = *condition5.get();
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr15 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.And"), "poc.And");
    return ud::VerifyResult::Error(*expr15.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Or(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='Or'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     or typed_as='bool'
  //         const_bool typed_as='bool' bool_val=False
  //         eq typed_as='bool'
  //             get_field typed_as='int64' str_val='number'
  //                 this typed_as='OperationChecks'
  //             const_int typed_as='int64' int_val=6
  //         eq typed_as='bool'
  //             map_get typed_as='int64'
  //                 get_field typed_as='map<string, int64>' str_val='mapping'
  //                     this typed_as='OperationChecks'
  //                 const_str typed_as='string' str_val='a'
  //             const_int typed_as='int64' int_val=99
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::Or);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    auto condition5 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
    if (!(*condition5.get())) {
      bool const& expr6 = ud::UniValue<ud::StaticT<bool>>::FromConst(static_cast<bool>(false), "false");
      condition5 = expr6;
    }
    if (!(*condition5.get())) {
      int64_t const& expr7 = expr0.Field(&expr0.get()->number, "number");
      int64_t const& expr8 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(6), "6");
      bool const& expr9 = ud::eval_eq<bool>(expr7, expr8);
      condition5 = expr9;
    }
    if (!(*condition5.get())) {
      hstd::UnorderedMap<hstd::Str, int64_t> const& expr10 = expr0.Field(&expr0.get()->mapping, "mapping");
      hstd::Str const& expr11 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("a"), "a");
      int64_t const& expr12 = ud::eval_map_get<int64_t>(expr10, expr11);
      int64_t const& expr13 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(99), "99");
      bool const& expr14 = ud::eval_eq<bool>(expr12, expr13);
      condition5 = expr14;
    }
    condition1 = *condition5.get();
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr15 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.Or"), "poc.Or");
    return ud::VerifyResult::Error(*expr15.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Not(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='Not'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     not typed_as='bool'
  //         ne typed_as='bool'
  //             get_field typed_as='int64' str_val='number'
  //                 this typed_as='OperationChecks'
  //             const_int typed_as='int64' int_val=6
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::Not);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    int64_t const& expr5 = expr0.Field(&expr0.get()->number, "number");
    int64_t const& expr6 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(6), "6");
    bool const& expr7 = ud::eval_ne<bool>(expr5, expr6);
    bool const& expr8 = ud::eval_not<bool>((expr7));
    condition1 = expr8;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr9 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.Not"), "poc.Not");
    return ud::VerifyResult::Error(*expr9.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Cond(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='Cond'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         cond typed_as='string'
  //             eq typed_as='bool'
  //                 get_field typed_as='int64' str_val='number'
  //                     this typed_as='OperationChecks'
  //                 const_int typed_as='int64' int_val=6
  //             get_field typed_as='string' str_val='text'
  //                 this typed_as='OperationChecks'
  //             str_format typed_as='string' str_val='other-%d'
  //                 get_field typed_as='int64' str_val='number'
  //                     this typed_as='OperationChecks'
  //         const_str typed_as='string' str_val='six'
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::Cond);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    int64_t const& expr5 = expr0.Field(&expr0.get()->number, "number");
    int64_t const& expr6 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(6), "6");
    bool const& expr7 = ud::eval_eq<bool>(expr5, expr6);
    std::optional<hstd::Str> result11 = std::nullopt;
    if (expr7) {
      hstd::Str const& expr8 = expr0.Field(&expr0.get()->text, "text");
      result11.emplace(expr8);
    } else {
      int64_t const& expr9 = expr0.Field(&expr0.get()->number, "number");
      hstd::Str const& expr10 = ud::eval_str_format(ud::eval_str_pattern("other-%d"), expr9);
      result11.emplace(expr10);
    }
    hstd::Str const& expr12 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("six"), "six");
    bool const& expr13 = ud::eval_eq<bool>(result11.value(), expr12);
    condition1 = expr13;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr14 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.Cond"), "poc.Cond");
    return ud::VerifyResult::Error(*expr14.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_CondLazy(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='CondLazy'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         cond typed_as='int64'
  //             get_field typed_as='bool' str_val='flag'
  //                 this typed_as='OperationChecks'
  //             map_get typed_as='int64'
  //                 get_field typed_as='map<string, int64>' str_val='mapping'
  //                     this typed_as='OperationChecks'
  //                 const_str typed_as='string' str_val='a'
  //             map_get typed_as='int64'
  //                 get_field typed_as='map<string, int64>' str_val='mapping'
  //                     this typed_as='OperationChecks'
  //                 const_str typed_as='string' str_val='absent'
  //         const_int typed_as='int64' int_val=1
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::CondLazy);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    bool const& expr5 = expr0.Field(&expr0.get()->flag, "flag");
    std::optional<int64_t> result12 = std::nullopt;
    if (expr5) {
      hstd::UnorderedMap<hstd::Str, int64_t> const& expr6 = expr0.Field(&expr0.get()->mapping, "mapping");
      hstd::Str const& expr7 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("a"), "a");
      int64_t const& expr8 = ud::eval_map_get<int64_t>(expr6, expr7);
      result12.emplace(expr8);
    } else {
      hstd::UnorderedMap<hstd::Str, int64_t> const& expr9 = expr0.Field(&expr0.get()->mapping, "mapping");
      hstd::Str const& expr10 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("absent"), "absent");
      int64_t const& expr11 = ud::eval_map_get<int64_t>(expr9, expr10);
      result12.emplace(expr11);
    }
    int64_t const& expr13 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(1), "1");
    bool const& expr14 = ud::eval_eq<bool>(result12.value(), expr13);
    condition1 = expr14;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr15 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.CondLazy"), "poc.CondLazy");
    return ud::VerifyResult::Error(*expr15.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_All(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='All'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     all typed_as='bool' binders=('number',)
  //         get_field typed_as='list<int64>' str_val='numbers'
  //             this typed_as='OperationChecks'
  //         lt typed_as='bool'
  //             var typed_as='int64' str_val='number'
  //             const_int typed_as='int64' int_val=4
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::All);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::Vec<int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    auto callback9 = [&](auto const& item6) {
                     int64_t const& expr7 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(4), "4");
                     bool const& expr8 = ud::eval_lt<bool>(item6, expr7);
                     return expr8;
                     };
    bool const& expr10 = ud::eval_all(expr5, callback9);
    condition1 = expr10;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr11 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.All"), "poc.All");
    return ud::VerifyResult::Error(*expr11.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Exists(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='Exists'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     exists typed_as='bool' binders=('number',)
  //         get_field typed_as='list<int64>' str_val='numbers'
  //             this typed_as='OperationChecks'
  //         eq typed_as='bool'
  //             var typed_as='int64' str_val='number'
  //             const_int typed_as='int64' int_val=3
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::Exists);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::Vec<int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    auto callback9 = [&](auto const& item6) {
                     int64_t const& expr7 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(3), "3");
                     bool const& expr8 = ud::eval_eq<bool>(item6, expr7);
                     return expr8;
                     };
    bool const& expr10 = ud::eval_exists(expr5, callback9);
    condition1 = expr10;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr11 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.Exists"), "poc.Exists");
    return ud::VerifyResult::Error(*expr11.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ExistsOne(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='ExistsOne'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     exists_one typed_as='bool' binders=('number',)
  //         get_field typed_as='list<int64>' str_val='numbers'
  //             this typed_as='OperationChecks'
  //         eq typed_as='bool'
  //             var typed_as='int64' str_val='number'
  //             const_int typed_as='int64' int_val=3
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::ExistsOne);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::Vec<int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    auto callback9 = [&](auto const& item6) {
                     int64_t const& expr7 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(3), "3");
                     bool const& expr8 = ud::eval_eq<bool>(item6, expr7);
                     return expr8;
                     };
    bool const& expr10 = ud::eval_exists_one(expr5, callback9);
    condition1 = expr10;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr11 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.ExistsOne"), "poc.ExistsOne");
    return ud::VerifyResult::Error(*expr11.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Map(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='Map'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         list_at typed_as='int64'
  //             map typed_as='list<int64>' binders=('number',)
  //                 get_field typed_as='list<int64>' str_val='numbers'
  //                     this typed_as='OperationChecks'
  //                 mul typed_as='int64'
  //                     var typed_as='int64' str_val='number'
  //                     const_int typed_as='int64' int_val=2
  //             const_int typed_as='int64' int_val=2
  //         const_int typed_as='int64' int_val=6
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::Map);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::Vec<int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    auto callback9 = [&](auto const& item6) {
                     int64_t const& expr7 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(2), "2");
                     int64_t const& expr8 = ud::eval_mul<int64_t>(item6, expr7);
                     return expr8;
                     };
    hstd::Vec<int64_t> const& expr10 = ud::eval_map<int64_t>(expr5, callback9);
    int64_t const& expr11 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(2), "2");
    int64_t const& expr12 = ud::eval_list_at<int64_t>(expr10, expr11);
    int64_t const& expr13 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(6), "6");
    bool const& expr14 = ud::eval_eq<bool>(expr12, expr13);
    condition1 = expr14;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr15 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.Map"), "poc.Map");
    return ud::VerifyResult::Error(*expr15.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Filter(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='Filter'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         list_size typed_as='int64'
  //             filter typed_as='list<int64>' binders=('number',)
  //                 get_field typed_as='list<int64>' str_val='numbers'
  //                     this typed_as='OperationChecks'
  //                 lt typed_as='bool'
  //                     const_int typed_as='int64' int_val=1
  //                     var typed_as='int64' str_val='number'
  //         const_int typed_as='int64' int_val=2
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::Filter);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::Vec<int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    auto callback9 = [&](auto const& item6) {
                     int64_t const& expr7 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(1), "1");
                     bool const& expr8 = ud::eval_lt<bool>(expr7, item6);
                     return expr8;
                     };
    hstd::Vec<int64_t> const& expr10 = ud::eval_filter<int64_t>(expr5, callback9);
    int64_t const& expr11 = ud::eval_list_size<int64_t>(expr10);
    int64_t const& expr12 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(2), "2");
    bool const& expr13 = ud::eval_eq<bool>(expr11, expr12);
    condition1 = expr13;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr14 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.Filter"), "poc.Filter");
    return ud::VerifyResult::Error(*expr14.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_FilterMap(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='FilterMap'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     let typed_as='bool' binders=('present',)
  //         filter_map typed_as='list<int64>' binders=('optional',)
  //             get_field typed_as='list<optional<int64>>' str_val='optionals'
  //                 this typed_as='OperationChecks'
  //             var typed_as='optional<int64>' str_val='optional'
  //         and typed_as='bool'
  //             eq typed_as='bool'
  //                 list_size typed_as='int64'
  //                     var typed_as='list<int64>' str_val='present'
  //                 const_int typed_as='int64' int_val=2
  //             eq typed_as='bool'
  //                 list_at typed_as='int64'
  //                     var typed_as='list<int64>' str_val='present'
  //                     const_int typed_as='int64' int_val=0
  //                 const_int typed_as='int64' int_val=1
  //             eq typed_as='bool'
  //                 list_at typed_as='int64'
  //                     var typed_as='list<int64>' str_val='present'
  //                     const_int typed_as='int64' int_val=1
  //                 const_int typed_as='int64' int_val=3
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::FilterMap);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::Vec<hstd::Opt<int64_t>> const& expr5 = expr0.Field(&expr0.get()->optionals, "optionals");
    auto callback7 = [&](auto const& item6) {
                     return item6;
                     };
    hstd::Vec<int64_t> const& expr8 = ud::eval_filter_map<hstd::Vec<int64_t>>(expr5, callback7);
    auto condition9 = ud::UniValue<ud::StaticT<bool>>::FromConst(true, "true");
    if (*condition9.get()) {
      int64_t const& expr10 = ud::eval_list_size<int64_t>(expr8);
      int64_t const& expr11 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(2), "2");
      bool const& expr12 = ud::eval_eq<bool>(expr10, expr11);
      condition9 = expr12;
    }
    if (*condition9.get()) {
      int64_t const& expr13 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
      int64_t const& expr14 = ud::eval_list_at<int64_t>(expr8, expr13);
      int64_t const& expr15 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(1), "1");
      bool const& expr16 = ud::eval_eq<bool>(expr14, expr15);
      condition9 = expr16;
    }
    if (*condition9.get()) {
      int64_t const& expr17 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(1), "1");
      int64_t const& expr18 = ud::eval_list_at<int64_t>(expr8, expr17);
      int64_t const& expr19 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(3), "3");
      bool const& expr20 = ud::eval_eq<bool>(expr18, expr19);
      condition9 = expr20;
    }
    condition1 = *condition9.get();
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr21 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.FilterMap"), "poc.FilterMap");
    return ud::VerifyResult::Error(*expr21.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_TakeWhile(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='TakeWhile'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         list_size typed_as='int64'
  //             take_while typed_as='list<int64>' binders=('number',)
  //                 get_field typed_as='list<int64>' str_val='numbers'
  //                     this typed_as='OperationChecks'
  //                 lt typed_as='bool'
  //                     var typed_as='int64' str_val='number'
  //                     const_int typed_as='int64' int_val=3
  //         const_int typed_as='int64' int_val=2
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::TakeWhile);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::Vec<int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    auto callback9 = [&](auto const& item6) {
                     int64_t const& expr7 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(3), "3");
                     bool const& expr8 = ud::eval_lt<bool>(item6, expr7);
                     return expr8;
                     };
    hstd::Vec<int64_t> const& expr10 = ud::eval_take_while<hstd::Vec<int64_t>>(expr5, callback9);
    int64_t const& expr11 = ud::eval_list_size<int64_t>(expr10);
    int64_t const& expr12 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(2), "2");
    bool const& expr13 = ud::eval_eq<bool>(expr11, expr12);
    condition1 = expr13;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr14 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.TakeWhile"), "poc.TakeWhile");
    return ud::VerifyResult::Error(*expr14.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_GroupBy(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='GroupBy'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     let typed_as='bool' binders=('groups',)
  //         group_by typed_as='map<bool, list<int64>>' binders=('number',)
  //             get_field typed_as='list<int64>' str_val='numbers'
  //                 this typed_as='OperationChecks'
  //             lt typed_as='bool'
  //                 var typed_as='int64' str_val='number'
  //                 const_int typed_as='int64' int_val=3
  //         and typed_as='bool'
  //             eq typed_as='bool'
  //                 map_size typed_as='int64'
  //                     var typed_as='map<bool, list<int64>>' str_val='groups'
  //                 const_int typed_as='int64' int_val=2
  //             eq typed_as='bool'
  //                 list_at typed_as='int64'
  //                     list_at typed_as='list<int64>'
  //                         map_values typed_as='list<list<int64>>'
  //                             var typed_as='map<bool, list<int64>>' str_val='groups'
  //                         const_int typed_as='int64' int_val=0
  //                     const_int typed_as='int64' int_val=0
  //                 list_at typed_as='int64'
  //                     get_field typed_as='list<int64>' str_val='numbers'
  //                         this typed_as='OperationChecks'
  //                     const_int typed_as='int64' int_val=0
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::GroupBy);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::Vec<int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    auto callback9 = [&](auto const& item6) {
                     int64_t const& expr7 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(3), "3");
                     bool const& expr8 = ud::eval_lt<bool>(item6, expr7);
                     return expr8;
                     };
    hstd::UnorderedMap<bool, hstd::Vec<int64_t>> const& expr10 = ud::eval_group_by<hstd::UnorderedMap<bool, hstd::Vec<int64_t>>>(expr5, callback9);
    auto condition11 = ud::UniValue<ud::StaticT<bool>>::FromConst(true, "true");
    if (*condition11.get()) {
      int64_t const& expr12 = ud::eval_map_size<int64_t>(expr10);
      int64_t const& expr13 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(2), "2");
      bool const& expr14 = ud::eval_eq<bool>(expr12, expr13);
      condition11 = expr14;
    }
    if (*condition11.get()) {
      hstd::Vec<hstd::Vec<int64_t>> const& expr15 = ud::eval_map_values<hstd::Vec<hstd::Vec<int64_t>>>(expr10);
      int64_t const& expr16 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
      hstd::Vec<int64_t> const& expr17 = ud::eval_list_at<hstd::Vec<int64_t>>(expr15, expr16);
      int64_t const& expr18 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
      int64_t const& expr19 = ud::eval_list_at<int64_t>(expr17, expr18);
      hstd::Vec<int64_t> const& expr20 = expr0.Field(&expr0.get()->numbers, "numbers");
      int64_t const& expr21 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
      int64_t const& expr22 = ud::eval_list_at<int64_t>(expr20, expr21);
      bool const& expr23 = ud::eval_eq<bool>(expr19, expr22);
      condition11 = expr23;
    }
    condition1 = *condition11.get();
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr24 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.GroupBy"), "poc.GroupBy");
    return ud::VerifyResult::Error(*expr24.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Fold(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='Fold'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         fold typed_as='int64' binders=('acc', 'number')
  //             get_field typed_as='list<int64>' str_val='numbers'
  //                 this typed_as='OperationChecks'
  //             const_int typed_as='int64' int_val=0
  //             add typed_as='int64'
  //                 var typed_as='int64' str_val='acc'
  //                 var typed_as='int64' str_val='number'
  //         const_int typed_as='int64' int_val=6
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::Fold);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::Vec<int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    int64_t const& expr6 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
    auto callback7 = [&](auto const& item8, auto const& item9) {
                     int64_t const& expr10 = ud::eval_add<int64_t>(item8, item9);
                     return expr10;
                     };
    int64_t const& expr11 = ud::eval_fold<int64_t>(expr5, expr6, callback7);
    int64_t const& expr12 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(6), "6");
    bool const& expr13 = ud::eval_eq<bool>(expr11, expr12);
    condition1 = expr13;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr14 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.Fold"), "poc.Fold");
    return ud::VerifyResult::Error(*expr14.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Walk(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='Walk'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     let typed_as='bool' binders=('ids',)
  //         filter_map typed_as='list<int64>' binders=('walk_value',)
  //             walk typed_as='list<dyn<Derived>>'
  //                 get_field typed_as='Derived' str_val='derived'
  //                     this typed_as='OperationChecks'
  //             type_cond typed_as='optional<int64>' bool_val=True
  //                 var typed_as='dyn<Derived>' str_val='walk_value'
  //                 type_case typed_as='int64' type_val='Derived' binders=('derived',)
  //                     get_field typed_as='int64' str_val='id'
  //                         var typed_as='Derived' str_val='derived'
  //         and typed_as='bool'
  //             eq typed_as='bool'
  //                 list_size typed_as='int64'
  //                     var typed_as='list<int64>' str_val='ids'
  //                 const_int typed_as='int64' int_val=1
  //             eq typed_as='bool'
  //                 list_at typed_as='int64'
  //                     var typed_as='list<int64>' str_val='ids'
  //                     const_int typed_as='int64' int_val=0
  //                 const_int typed_as='int64' int_val=6
  //
  hstd::ext::unidata::EvalRuntime expression_runtime = hstd::ext::unidata::EvalRuntime{ctx};
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::Walk);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::Derived const& expr5 = expr0.Field(&expr0.get()->derived, "derived");
    hstd::Vec<DynamicT> const& expr6 = ud::eval_walk(expression_runtime, expr5);
    auto callback11 = [&](auto const& item7) {
                      std::optional<int64_t> result8 = std::nullopt;
                      if (!(result8.has_value())) {
                        auto const* candidate9 = expression_runtime.try_as<hstd::unidata_dsl::test::Derived>(item7);
                        if (candidate9 != nullptr) {
                          int64_t const& expr10 = (*candidate9).Field(&(*candidate9).get()->id, "id");
                          result8.emplace(expr10);
                        }
                      }
                      return result8;
                      };
    hstd::Vec<int64_t> const& expr12 = ud::eval_filter_map<hstd::Vec<int64_t>>(expr6, callback11);
    auto condition13 = ud::UniValue<ud::StaticT<bool>>::FromConst(true, "true");
    if (*condition13.get()) {
      int64_t const& expr14 = ud::eval_list_size<int64_t>(expr12);
      int64_t const& expr15 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(1), "1");
      bool const& expr16 = ud::eval_eq<bool>(expr14, expr15);
      condition13 = expr16;
    }
    if (*condition13.get()) {
      int64_t const& expr17 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
      int64_t const& expr18 = ud::eval_list_at<int64_t>(expr12, expr17);
      int64_t const& expr19 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(6), "6");
      bool const& expr20 = ud::eval_eq<bool>(expr18, expr19);
      condition13 = expr20;
    }
    condition1 = *condition13.get();
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr21 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.Walk"), "poc.Walk");
    return ud::VerifyResult::Error(*expr21.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Sum(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='Sum'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         sum typed_as='int64'
  //             get_field typed_as='list<int64>' str_val='numbers'
  //                 this typed_as='OperationChecks'
  //         const_int typed_as='int64' int_val=6
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::Sum);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::Vec<int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    int64_t const& expr6 = ud::eval_sum<int64_t>(expr5);
    int64_t const& expr7 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(6), "6");
    bool const& expr8 = ud::eval_eq<bool>(expr6, expr7);
    condition1 = expr8;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr9 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.Sum"), "poc.Sum");
    return ud::VerifyResult::Error(*expr9.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Min(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='Min'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         min typed_as='int64'
  //             get_field typed_as='list<int64>' str_val='numbers'
  //                 this typed_as='OperationChecks'
  //         const_int typed_as='int64' int_val=1
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::Min);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::Vec<int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    int64_t const& expr6 = ud::eval_min<int64_t>(expr5);
    int64_t const& expr7 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(1), "1");
    bool const& expr8 = ud::eval_eq<bool>(expr6, expr7);
    condition1 = expr8;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr9 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.Min"), "poc.Min");
    return ud::VerifyResult::Error(*expr9.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Max(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='Max'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         max typed_as='int64'
  //             get_field typed_as='list<int64>' str_val='numbers'
  //                 this typed_as='OperationChecks'
  //         const_int typed_as='int64' int_val=3
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::Max);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::Vec<int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    int64_t const& expr6 = ud::eval_max<int64_t>(expr5);
    int64_t const& expr7 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(3), "3");
    bool const& expr8 = ud::eval_eq<bool>(expr6, expr7);
    condition1 = expr8;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr9 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.Max"), "poc.Max");
    return ud::VerifyResult::Error(*expr9.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_StrSize(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='StrSize'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         str_size typed_as='int64'
  //             get_field typed_as='string' str_val='text'
  //                 this typed_as='OperationChecks'
  //         const_int typed_as='int64' int_val=3
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::StrSize);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::Str const& expr5 = expr0.Field(&expr0.get()->text, "text");
    int64_t const& expr6 = ud::eval_str_size<int64_t>(expr5);
    int64_t const& expr7 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(3), "3");
    bool const& expr8 = ud::eval_eq<bool>(expr6, expr7);
    condition1 = expr8;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr9 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.StrSize"), "poc.StrSize");
    return ud::VerifyResult::Error(*expr9.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_StrMatches(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='StrMatches'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     str_matches typed_as='bool' str_val='^s[a-z]{2}$'
  //         get_field typed_as='string' str_val='text'
  //             this typed_as='OperationChecks'
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::StrMatches);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::Str const& expr5 = expr0.Field(&expr0.get()->text, "text");
    bool const& expr6 = ud::eval_str_matches(expr5, "^s[a-z]{2}$");
    condition1 = expr6;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr7 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.StrMatches"), "poc.StrMatches");
    return ud::VerifyResult::Error(*expr7.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_StrFormat(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='StrFormat'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         str_format typed_as='string' str_val='%s:%d'
  //             get_field typed_as='string' str_val='text'
  //                 this typed_as='OperationChecks'
  //             get_field typed_as='int64' str_val='number'
  //                 this typed_as='OperationChecks'
  //         const_str typed_as='string' str_val='six:6'
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::StrFormat);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::Str const& expr5 = expr0.Field(&expr0.get()->text, "text");
    int64_t const& expr6 = expr0.Field(&expr0.get()->number, "number");
    hstd::Str const& expr7 = ud::eval_str_format(ud::eval_str_pattern("%s:%d"), expr5, expr6);
    hstd::Str const& expr8 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("six:6"), "six:6");
    bool const& expr9 = ud::eval_eq<bool>(expr7, expr8);
    condition1 = expr9;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr10 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.StrFormat"), "poc.StrFormat");
    return ud::VerifyResult::Error(*expr10.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ListSize(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='ListSize'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         list_size typed_as='int64'
  //             get_field typed_as='list<int64>' str_val='numbers'
  //                 this typed_as='OperationChecks'
  //         const_int typed_as='int64' int_val=3
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::ListSize);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::Vec<int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    int64_t const& expr6 = ud::eval_list_size<int64_t>(expr5);
    int64_t const& expr7 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(3), "3");
    bool const& expr8 = ud::eval_eq<bool>(expr6, expr7);
    condition1 = expr8;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr9 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.ListSize"), "poc.ListSize");
    return ud::VerifyResult::Error(*expr9.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ListContains(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='ListContains'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     list_contains typed_as='bool'
  //         get_field typed_as='list<int64>' str_val='numbers'
  //             this typed_as='OperationChecks'
  //         const_int typed_as='int64' int_val=3
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::ListContains);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::Vec<int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    int64_t const& expr6 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(3), "3");
    bool const& expr7 = ud::eval_list_contains<bool>(expr5, expr6);
    condition1 = expr7;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr8 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.ListContains"), "poc.ListContains");
    return ud::VerifyResult::Error(*expr8.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ListAt(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='ListAt'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         list_at typed_as='int64'
  //             get_field typed_as='list<int64>' str_val='numbers'
  //                 this typed_as='OperationChecks'
  //             const_int typed_as='int64' int_val=2
  //         const_int typed_as='int64' int_val=3
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::ListAt);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::Vec<int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    int64_t const& expr6 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(2), "2");
    int64_t const& expr7 = ud::eval_list_at<int64_t>(expr5, expr6);
    int64_t const& expr8 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(3), "3");
    bool const& expr9 = ud::eval_eq<bool>(expr7, expr8);
    condition1 = expr9;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr10 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.ListAt"), "poc.ListAt");
    return ud::VerifyResult::Error(*expr10.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ListSlice(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='ListSlice'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     let typed_as='bool' binders=('slice',)
  //         list_slice typed_as='list<int64>'
  //             get_field typed_as='list<int64>' str_val='numbers'
  //                 this typed_as='OperationChecks'
  //             const_int typed_as='int64' int_val=1
  //             const_int typed_as='int64' int_val=3
  //         and typed_as='bool'
  //             eq typed_as='bool'
  //                 list_size typed_as='int64'
  //                     var typed_as='list<int64>' str_val='slice'
  //                 const_int typed_as='int64' int_val=2
  //             eq typed_as='bool'
  //                 list_at typed_as='int64'
  //                     var typed_as='list<int64>' str_val='slice'
  //                     const_int typed_as='int64' int_val=0
  //                 const_int typed_as='int64' int_val=2
  //             eq typed_as='bool'
  //                 list_at typed_as='int64'
  //                     var typed_as='list<int64>' str_val='slice'
  //                     const_int typed_as='int64' int_val=1
  //                 const_int typed_as='int64' int_val=3
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::ListSlice);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::Vec<int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    int64_t const& expr6 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(1), "1");
    int64_t const& expr7 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(3), "3");
    hstd::Vec<int64_t> const& expr8 = ud::eval_list_slice<hstd::Vec<int64_t>>(expr5, expr6, expr7);
    auto condition9 = ud::UniValue<ud::StaticT<bool>>::FromConst(true, "true");
    if (*condition9.get()) {
      int64_t const& expr10 = ud::eval_list_size<int64_t>(expr8);
      int64_t const& expr11 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(2), "2");
      bool const& expr12 = ud::eval_eq<bool>(expr10, expr11);
      condition9 = expr12;
    }
    if (*condition9.get()) {
      int64_t const& expr13 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
      int64_t const& expr14 = ud::eval_list_at<int64_t>(expr8, expr13);
      int64_t const& expr15 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(2), "2");
      bool const& expr16 = ud::eval_eq<bool>(expr14, expr15);
      condition9 = expr16;
    }
    if (*condition9.get()) {
      int64_t const& expr17 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(1), "1");
      int64_t const& expr18 = ud::eval_list_at<int64_t>(expr8, expr17);
      int64_t const& expr19 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(3), "3");
      bool const& expr20 = ud::eval_eq<bool>(expr18, expr19);
      condition9 = expr20;
    }
    condition1 = *condition9.get();
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr21 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.ListSlice"), "poc.ListSlice");
    return ud::VerifyResult::Error(*expr21.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ListSliceBounds(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='ListSliceBounds'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     let typed_as='bool' binders=('slice',)
  //         list_slice typed_as='list<int64>'
  //             get_field typed_as='list<int64>' str_val='numbers'
  //                 this typed_as='OperationChecks'
  //             const_int typed_as='int64' int_val=-2
  //             const_int typed_as='int64' int_val=100
  //         and typed_as='bool'
  //             eq typed_as='bool'
  //                 list_size typed_as='int64'
  //                     var typed_as='list<int64>' str_val='slice'
  //                 const_int typed_as='int64' int_val=2
  //             eq typed_as='bool'
  //                 list_at typed_as='int64'
  //                     var typed_as='list<int64>' str_val='slice'
  //                     const_int typed_as='int64' int_val=0
  //                 const_int typed_as='int64' int_val=2
  //             eq typed_as='bool'
  //                 list_at typed_as='int64'
  //                     var typed_as='list<int64>' str_val='slice'
  //                     const_int typed_as='int64' int_val=1
  //                 const_int typed_as='int64' int_val=3
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::ListSliceBounds);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::Vec<int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    int64_t const& expr6 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(-2), "-2");
    int64_t const& expr7 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(100), "100");
    hstd::Vec<int64_t> const& expr8 = ud::eval_list_slice<hstd::Vec<int64_t>>(expr5, expr6, expr7);
    auto condition9 = ud::UniValue<ud::StaticT<bool>>::FromConst(true, "true");
    if (*condition9.get()) {
      int64_t const& expr10 = ud::eval_list_size<int64_t>(expr8);
      int64_t const& expr11 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(2), "2");
      bool const& expr12 = ud::eval_eq<bool>(expr10, expr11);
      condition9 = expr12;
    }
    if (*condition9.get()) {
      int64_t const& expr13 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
      int64_t const& expr14 = ud::eval_list_at<int64_t>(expr8, expr13);
      int64_t const& expr15 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(2), "2");
      bool const& expr16 = ud::eval_eq<bool>(expr14, expr15);
      condition9 = expr16;
    }
    if (*condition9.get()) {
      int64_t const& expr17 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(1), "1");
      int64_t const& expr18 = ud::eval_list_at<int64_t>(expr8, expr17);
      int64_t const& expr19 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(3), "3");
      bool const& expr20 = ud::eval_eq<bool>(expr18, expr19);
      condition9 = expr20;
    }
    condition1 = *condition9.get();
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr21 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.ListSliceBounds"), "poc.ListSliceBounds");
    return ud::VerifyResult::Error(*expr21.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ListConcat(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='ListConcat'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     let typed_as='bool' binders=('joined',)
  //         list_concat typed_as='list<int64>'
  //             get_field typed_as='list<int64>' str_val='numbers'
  //                 this typed_as='OperationChecks'
  //             get_field typed_as='list<int64>' str_val='numbers'
  //                 this typed_as='OperationChecks'
  //         and typed_as='bool'
  //             eq typed_as='bool'
  //                 list_size typed_as='int64'
  //                     var typed_as='list<int64>' str_val='joined'
  //                 const_int typed_as='int64' int_val=6
  //             eq typed_as='bool'
  //                 list_at typed_as='int64'
  //                     var typed_as='list<int64>' str_val='joined'
  //                     const_int typed_as='int64' int_val=3
  //                 list_at typed_as='int64'
  //                     get_field typed_as='list<int64>' str_val='numbers'
  //                         this typed_as='OperationChecks'
  //                     const_int typed_as='int64' int_val=0
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::ListConcat);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::Vec<int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    hstd::Vec<int64_t> const& expr6 = expr0.Field(&expr0.get()->numbers, "numbers");
    hstd::Vec<int64_t> const& expr7 = ud::eval_list_concat<hstd::Vec<int64_t>>(expr5, expr6);
    auto condition8 = ud::UniValue<ud::StaticT<bool>>::FromConst(true, "true");
    if (*condition8.get()) {
      int64_t const& expr9 = ud::eval_list_size<int64_t>(expr7);
      int64_t const& expr10 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(6), "6");
      bool const& expr11 = ud::eval_eq<bool>(expr9, expr10);
      condition8 = expr11;
    }
    if (*condition8.get()) {
      int64_t const& expr12 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(3), "3");
      int64_t const& expr13 = ud::eval_list_at<int64_t>(expr7, expr12);
      hstd::Vec<int64_t> const& expr14 = expr0.Field(&expr0.get()->numbers, "numbers");
      int64_t const& expr15 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
      int64_t const& expr16 = ud::eval_list_at<int64_t>(expr14, expr15);
      bool const& expr17 = ud::eval_eq<bool>(expr13, expr16);
      condition8 = expr17;
    }
    condition1 = *condition8.get();
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr18 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.ListConcat"), "poc.ListConcat");
    return ud::VerifyResult::Error(*expr18.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ListEmpty(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='ListEmpty'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         list_size typed_as='int64'
  //             list_empty typed_as='list<int64>' type_val='list<int64>'
  //         const_int typed_as='int64' int_val=0
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::ListEmpty);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::Vec<int64_t> const& expr5 = ud::eval_list_empty<hstd::Vec<int64_t>>();
    int64_t const& expr6 = ud::eval_list_size<int64_t>(expr5);
    int64_t const& expr7 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
    bool const& expr8 = ud::eval_eq<bool>(expr6, expr7);
    condition1 = expr8;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr9 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.ListEmpty"), "poc.ListEmpty");
    return ud::VerifyResult::Error(*expr9.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapSize(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='MapSize'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         map_size typed_as='int64'
  //             get_field typed_as='map<string, int64>' str_val='mapping'
  //                 this typed_as='OperationChecks'
  //         const_int typed_as='int64' int_val=2
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::MapSize);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::UnorderedMap<hstd::Str, int64_t> const& expr5 = expr0.Field(&expr0.get()->mapping, "mapping");
    int64_t const& expr6 = ud::eval_map_size<int64_t>(expr5);
    int64_t const& expr7 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(2), "2");
    bool const& expr8 = ud::eval_eq<bool>(expr6, expr7);
    condition1 = expr8;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr9 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.MapSize"), "poc.MapSize");
    return ud::VerifyResult::Error(*expr9.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapContains(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='MapContains'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     map_contains typed_as='bool'
  //         get_field typed_as='map<string, int64>' str_val='mapping'
  //             this typed_as='OperationChecks'
  //         const_str typed_as='string' str_val='a'
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::MapContains);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::UnorderedMap<hstd::Str, int64_t> const& expr5 = expr0.Field(&expr0.get()->mapping, "mapping");
    hstd::Str const& expr6 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("a"), "a");
    bool const& expr7 = ud::eval_map_contains<bool>(expr5, expr6);
    condition1 = expr7;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr8 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.MapContains"), "poc.MapContains");
    return ud::VerifyResult::Error(*expr8.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapGet(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='MapGet'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         map_get typed_as='int64'
  //             get_field typed_as='map<string, int64>' str_val='mapping'
  //                 this typed_as='OperationChecks'
  //             const_str typed_as='string' str_val='a'
  //         const_int typed_as='int64' int_val=1
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::MapGet);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::UnorderedMap<hstd::Str, int64_t> const& expr5 = expr0.Field(&expr0.get()->mapping, "mapping");
    hstd::Str const& expr6 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("a"), "a");
    int64_t const& expr7 = ud::eval_map_get<int64_t>(expr5, expr6);
    int64_t const& expr8 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(1), "1");
    bool const& expr9 = ud::eval_eq<bool>(expr7, expr8);
    condition1 = expr9;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr10 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.MapGet"), "poc.MapGet");
    return ud::VerifyResult::Error(*expr10.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapInsert(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='MapInsert'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     let typed_as='bool' binders=('updated',)
  //         map_insert typed_as='map<string, int64>'
  //             get_field typed_as='map<string, int64>' str_val='mapping'
  //                 this typed_as='OperationChecks'
  //             const_str typed_as='string' str_val='c'
  //             const_int typed_as='int64' int_val=3
  //         and typed_as='bool'
  //             eq typed_as='bool'
  //                 map_size typed_as='int64'
  //                     var typed_as='map<string, int64>' str_val='updated'
  //                 const_int typed_as='int64' int_val=3
  //             eq typed_as='bool'
  //                 map_get typed_as='int64'
  //                     var typed_as='map<string, int64>' str_val='updated'
  //                     const_str typed_as='string' str_val='c'
  //                 const_int typed_as='int64' int_val=3
  //             not typed_as='bool'
  //                 map_contains typed_as='bool'
  //                     get_field typed_as='map<string, int64>' str_val='mapping'
  //                         this typed_as='OperationChecks'
  //                     const_str typed_as='string' str_val='c'
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::MapInsert);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::UnorderedMap<hstd::Str, int64_t> const& expr5 = expr0.Field(&expr0.get()->mapping, "mapping");
    hstd::Str const& expr6 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("c"), "c");
    int64_t const& expr7 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(3), "3");
    hstd::UnorderedMap<hstd::Str, int64_t> const& expr8 = ud::eval_map_insert<hstd::UnorderedMap<hstd::Str, int64_t>>(expr5, expr6, expr7);
    auto condition9 = ud::UniValue<ud::StaticT<bool>>::FromConst(true, "true");
    if (*condition9.get()) {
      int64_t const& expr10 = ud::eval_map_size<int64_t>(expr8);
      int64_t const& expr11 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(3), "3");
      bool const& expr12 = ud::eval_eq<bool>(expr10, expr11);
      condition9 = expr12;
    }
    if (*condition9.get()) {
      hstd::Str const& expr13 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("c"), "c");
      int64_t const& expr14 = ud::eval_map_get<int64_t>(expr8, expr13);
      int64_t const& expr15 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(3), "3");
      bool const& expr16 = ud::eval_eq<bool>(expr14, expr15);
      condition9 = expr16;
    }
    if (*condition9.get()) {
      hstd::UnorderedMap<hstd::Str, int64_t> const& expr17 = expr0.Field(&expr0.get()->mapping, "mapping");
      hstd::Str const& expr18 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("c"), "c");
      bool const& expr19 = ud::eval_map_contains<bool>(expr17, expr18);
      bool const& expr20 = ud::eval_not<bool>((expr19));
      condition9 = expr20;
    }
    condition1 = *condition9.get();
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr21 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.MapInsert"), "poc.MapInsert");
    return ud::VerifyResult::Error(*expr21.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapReplace(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='MapReplace'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     let typed_as='bool' binders=('updated',)
  //         map_insert typed_as='map<string, int64>'
  //             get_field typed_as='map<string, int64>' str_val='mapping'
  //                 this typed_as='OperationChecks'
  //             const_str typed_as='string' str_val='a'
  //             const_int typed_as='int64' int_val=9
  //         and typed_as='bool'
  //             eq typed_as='bool'
  //                 map_size typed_as='int64'
  //                     var typed_as='map<string, int64>' str_val='updated'
  //                 map_size typed_as='int64'
  //                     get_field typed_as='map<string, int64>' str_val='mapping'
  //                         this typed_as='OperationChecks'
  //             eq typed_as='bool'
  //                 map_get typed_as='int64'
  //                     var typed_as='map<string, int64>' str_val='updated'
  //                     const_str typed_as='string' str_val='a'
  //                 const_int typed_as='int64' int_val=9
  //             eq typed_as='bool'
  //                 map_get typed_as='int64'
  //                     get_field typed_as='map<string, int64>' str_val='mapping'
  //                         this typed_as='OperationChecks'
  //                     const_str typed_as='string' str_val='a'
  //                 const_int typed_as='int64' int_val=1
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::MapReplace);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::UnorderedMap<hstd::Str, int64_t> const& expr5 = expr0.Field(&expr0.get()->mapping, "mapping");
    hstd::Str const& expr6 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("a"), "a");
    int64_t const& expr7 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(9), "9");
    hstd::UnorderedMap<hstd::Str, int64_t> const& expr8 = ud::eval_map_insert<hstd::UnorderedMap<hstd::Str, int64_t>>(expr5, expr6, expr7);
    auto condition9 = ud::UniValue<ud::StaticT<bool>>::FromConst(true, "true");
    if (*condition9.get()) {
      int64_t const& expr10 = ud::eval_map_size<int64_t>(expr8);
      hstd::UnorderedMap<hstd::Str, int64_t> const& expr11 = expr0.Field(&expr0.get()->mapping, "mapping");
      int64_t const& expr12 = ud::eval_map_size<int64_t>(expr11);
      bool const& expr13 = ud::eval_eq<bool>(expr10, expr12);
      condition9 = expr13;
    }
    if (*condition9.get()) {
      hstd::Str const& expr14 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("a"), "a");
      int64_t const& expr15 = ud::eval_map_get<int64_t>(expr8, expr14);
      int64_t const& expr16 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(9), "9");
      bool const& expr17 = ud::eval_eq<bool>(expr15, expr16);
      condition9 = expr17;
    }
    if (*condition9.get()) {
      hstd::UnorderedMap<hstd::Str, int64_t> const& expr18 = expr0.Field(&expr0.get()->mapping, "mapping");
      hstd::Str const& expr19 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("a"), "a");
      int64_t const& expr20 = ud::eval_map_get<int64_t>(expr18, expr19);
      int64_t const& expr21 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(1), "1");
      bool const& expr22 = ud::eval_eq<bool>(expr20, expr21);
      condition9 = expr22;
    }
    condition1 = *condition9.get();
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr23 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.MapReplace"), "poc.MapReplace");
    return ud::VerifyResult::Error(*expr23.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapKeys(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='MapKeys'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     let typed_as='bool' binders=('keys',)
  //         map_keys typed_as='list<string>'
  //             get_field typed_as='map<string, int64>' str_val='mapping'
  //                 this typed_as='OperationChecks'
  //         and typed_as='bool'
  //             eq typed_as='bool'
  //                 list_size typed_as='int64'
  //                     var typed_as='list<string>' str_val='keys'
  //                 const_int typed_as='int64' int_val=2
  //             list_contains typed_as='bool'
  //                 var typed_as='list<string>' str_val='keys'
  //                 const_str typed_as='string' str_val='a'
  //             list_contains typed_as='bool'
  //                 var typed_as='list<string>' str_val='keys'
  //                 const_str typed_as='string' str_val='b'
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::MapKeys);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::UnorderedMap<hstd::Str, int64_t> const& expr5 = expr0.Field(&expr0.get()->mapping, "mapping");
    hstd::Vec<hstd::Str> const& expr6 = ud::eval_map_keys<hstd::Vec<hstd::Str>>(expr5);
    auto condition7 = ud::UniValue<ud::StaticT<bool>>::FromConst(true, "true");
    if (*condition7.get()) {
      int64_t const& expr8 = ud::eval_list_size<int64_t>(expr6);
      int64_t const& expr9 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(2), "2");
      bool const& expr10 = ud::eval_eq<bool>(expr8, expr9);
      condition7 = expr10;
    }
    if (*condition7.get()) {
      hstd::Str const& expr11 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("a"), "a");
      bool const& expr12 = ud::eval_list_contains<bool>(expr6, expr11);
      condition7 = expr12;
    }
    if (*condition7.get()) {
      hstd::Str const& expr13 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("b"), "b");
      bool const& expr14 = ud::eval_list_contains<bool>(expr6, expr13);
      condition7 = expr14;
    }
    condition1 = *condition7.get();
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr15 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.MapKeys"), "poc.MapKeys");
    return ud::VerifyResult::Error(*expr15.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapValues(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='MapValues'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     let typed_as='bool' binders=('values',)
  //         map_values typed_as='list<int64>'
  //             get_field typed_as='map<string, int64>' str_val='mapping'
  //                 this typed_as='OperationChecks'
  //         and typed_as='bool'
  //             eq typed_as='bool'
  //                 list_size typed_as='int64'
  //                     var typed_as='list<int64>' str_val='values'
  //                 const_int typed_as='int64' int_val=2
  //             list_contains typed_as='bool'
  //                 var typed_as='list<int64>' str_val='values'
  //                 const_int typed_as='int64' int_val=1
  //             list_contains typed_as='bool'
  //                 var typed_as='list<int64>' str_val='values'
  //                 const_int typed_as='int64' int_val=2
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::MapValues);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::UnorderedMap<hstd::Str, int64_t> const& expr5 = expr0.Field(&expr0.get()->mapping, "mapping");
    hstd::Vec<int64_t> const& expr6 = ud::eval_map_values<hstd::Vec<int64_t>>(expr5);
    auto condition7 = ud::UniValue<ud::StaticT<bool>>::FromConst(true, "true");
    if (*condition7.get()) {
      int64_t const& expr8 = ud::eval_list_size<int64_t>(expr6);
      int64_t const& expr9 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(2), "2");
      bool const& expr10 = ud::eval_eq<bool>(expr8, expr9);
      condition7 = expr10;
    }
    if (*condition7.get()) {
      int64_t const& expr11 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(1), "1");
      bool const& expr12 = ud::eval_list_contains<bool>(expr6, expr11);
      condition7 = expr12;
    }
    if (*condition7.get()) {
      int64_t const& expr13 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(2), "2");
      bool const& expr14 = ud::eval_list_contains<bool>(expr6, expr13);
      condition7 = expr14;
    }
    condition1 = *condition7.get();
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr15 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.MapValues"), "poc.MapValues");
    return ud::VerifyResult::Error(*expr15.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapEmpty(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='MapEmpty'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         map_size typed_as='int64'
  //             map_empty typed_as='map<string, int64>' type_val='map<string, int64>'
  //         const_int typed_as='int64' int_val=0
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::MapEmpty);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::UnorderedMap<hstd::Str, int64_t> const& expr5 = ud::eval_map_empty<hstd::UnorderedMap<hstd::Str, int64_t>>();
    int64_t const& expr6 = ud::eval_map_size<int64_t>(expr5);
    int64_t const& expr7 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
    bool const& expr8 = ud::eval_eq<bool>(expr6, expr7);
    condition1 = expr8;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr9 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.MapEmpty"), "poc.MapEmpty");
    return ud::VerifyResult::Error(*expr9.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_OptHasValue(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='OptHasValue'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     opt_has_value typed_as='bool'
  //         get_field typed_as='optional<int64>' str_val='optional'
  //             this typed_as='OperationChecks'
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::OptHasValue);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::Opt<int64_t> const& expr5 = expr0.Field(&expr0.get()->optional, "optional");
    bool const& expr6 = ud::eval_opt_has_value<bool>(expr5);
    condition1 = expr6;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr7 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.OptHasValue"), "poc.OptHasValue");
    return ud::VerifyResult::Error(*expr7.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_OptValue(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='OptValue'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     and typed_as='bool'
  //         opt_has_value typed_as='bool'
  //             get_field typed_as='optional<int64>' str_val='optional'
  //                 this typed_as='OperationChecks'
  //         eq typed_as='bool'
  //             opt_value typed_as='int64'
  //                 get_field typed_as='optional<int64>' str_val='optional'
  //                     this typed_as='OperationChecks'
  //             const_int typed_as='int64' int_val=3
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::OptValue);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    auto condition5 = ud::UniValue<ud::StaticT<bool>>::FromConst(true, "true");
    if (*condition5.get()) {
      hstd::Opt<int64_t> const& expr6 = expr0.Field(&expr0.get()->optional, "optional");
      bool const& expr7 = ud::eval_opt_has_value<bool>(expr6);
      condition5 = expr7;
    }
    if (*condition5.get()) {
      hstd::Opt<int64_t> const& expr8 = expr0.Field(&expr0.get()->optional, "optional");
      int64_t const& expr9 = ud::eval_opt_value<int64_t>(expr8);
      int64_t const& expr10 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(3), "3");
      bool const& expr11 = ud::eval_eq<bool>(expr9, expr10);
      condition5 = expr11;
    }
    condition1 = *condition5.get();
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr12 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.OptValue"), "poc.OptValue");
    return ud::VerifyResult::Error(*expr12.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_CaseIs(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='CaseIs'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     case_is typed_as='bool' str_val='First'
  //         get_field typed_as='variant<Choice.data>' str_val='data'
  //             get_field typed_as='Choice' str_val='choice'
  //                 this typed_as='OperationChecks'
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::CaseIs);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::Choice const& expr5 = expr0.Field(&expr0.get()->choice, "choice");
    hstd::unidata_dsl::test::Choice::Data const& expr6 = expr5.Field(&expr5.get()->data, "data");
    bool const& expr7 = std::holds_alternative<hstd::unidata_dsl::test::Choice::First>(expr6);
    condition1 = expr7;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr8 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.CaseIs"), "poc.CaseIs");
    return ud::VerifyResult::Error(*expr8.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_CaseWhich(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='CaseWhich'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     enum_is typed_as='bool' str_val='First'
  //         case_which typed_as='Choice::Kind'
  //             get_field typed_as='variant<Choice.data>' str_val='data'
  //                 get_field typed_as='Choice' str_val='choice'
  //                     this typed_as='OperationChecks'
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::CaseWhich);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::Choice const& expr5 = expr0.Field(&expr0.get()->choice, "choice");
    hstd::unidata_dsl::test::Choice::Data const& expr6 = expr5.Field(&expr5.get()->data, "data");
    hstd::unidata_dsl::test::Choice::Kind const& expr7 = static_cast<hstd::unidata_dsl::test::Choice::Kind>(expr6.index());
    bool const& expr8 = ud::eval_eq<bool>(expr7, hstd::unidata_dsl::test::Choice::Kind::First);
    condition1 = expr8;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr9 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.CaseWhich"), "poc.CaseWhich");
    return ud::VerifyResult::Error(*expr9.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_CaseField(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='CaseField'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         cond typed_as='int64'
  //             case_is typed_as='bool' str_val='First'
  //                 get_field typed_as='variant<Choice.data>' str_val='data'
  //                     get_field typed_as='Choice' str_val='choice'
  //                         this typed_as='OperationChecks'
  //             get_field typed_as='int64' str_val='value'
  //                 get_field typed_as='variant<Choice.data>' str_val='data'
  //                     get_field typed_as='Choice' str_val='choice'
  //                         this typed_as='OperationChecks'
  //             const_int typed_as='int64' int_val=-1
  //         const_int typed_as='int64' int_val=6
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::CaseField);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::Choice const& expr5 = expr0.Field(&expr0.get()->choice, "choice");
    hstd::unidata_dsl::test::Choice::Data const& expr6 = expr5.Field(&expr5.get()->data, "data");
    bool const& expr7 = std::holds_alternative<hstd::unidata_dsl::test::Choice::First>(expr6);
    std::optional<int64_t> result12 = std::nullopt;
    if (expr7) {
      hstd::unidata_dsl::test::Choice const& expr8 = expr0.Field(&expr0.get()->choice, "choice");
      hstd::unidata_dsl::test::Choice::Data const& expr9 = expr8.Field(&expr8.get()->data, "data");
      int64_t const& expr10 = ud::eval_get_field<int64_t>(expr9, "value");
      result12.emplace(expr10);
    } else {
      int64_t const& expr11 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(-1), "-1");
      result12.emplace(expr11);
    }
    int64_t const& expr13 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(6), "6");
    bool const& expr14 = ud::eval_eq<bool>(result12.value(), expr13);
    condition1 = expr14;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr15 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.CaseField"), "poc.CaseField");
    return ud::VerifyResult::Error(*expr15.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_EnumIs(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='EnumIs'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     enum_is typed_as='bool' str_val='Ready'
  //         get_field typed_as='Status' str_val='status'
  //             this typed_as='OperationChecks'
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::EnumIs);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::Status const& expr5 = expr0.Field(&expr0.get()->status, "status");
    bool const& expr6 = ud::eval_eq<bool>(expr5, hstd::unidata_dsl::test::Status::Ready);
    condition1 = expr6;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr7 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.EnumIs"), "poc.EnumIs");
    return ud::VerifyResult::Error(*expr7.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_NthGet(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='NthGet'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     and typed_as='bool'
  //         eq typed_as='bool'
  //             nth_get typed_as='int64' int_val=0
  //                 get_field typed_as='tuple<int64, string>' str_val='coords'
  //                     this typed_as='OperationChecks'
  //             const_int typed_as='int64' int_val=6
  //         eq typed_as='bool'
  //             nth_get typed_as='string' int_val=1
  //                 get_field typed_as='tuple<int64, string>' str_val='coords'
  //                     this typed_as='OperationChecks'
  //             const_str typed_as='string' str_val='six'
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::NthGet);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    auto condition5 = ud::UniValue<ud::StaticT<bool>>::FromConst(true, "true");
    if (*condition5.get()) {
      hstd::Tuple<int64_t, hstd::Str> const& expr6 = expr0.Field(&expr0.get()->coords, "coords");
      int64_t const& expr7 = ud::eval_nth_get<0>(expr6);
      int64_t const& expr8 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(6), "6");
      bool const& expr9 = ud::eval_eq<bool>(expr7, expr8);
      condition5 = expr9;
    }
    if (*condition5.get()) {
      hstd::Tuple<int64_t, hstd::Str> const& expr10 = expr0.Field(&expr0.get()->coords, "coords");
      hstd::Str const& expr11 = ud::eval_nth_get<1>(expr10);
      hstd::Str const& expr12 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("six"), "six");
      bool const& expr13 = ud::eval_eq<bool>(expr11, expr12);
      condition5 = expr13;
    }
    condition1 = *condition5.get();
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr14 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.NthGet"), "poc.NthGet");
    return ud::VerifyResult::Error(*expr14.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_IsDerived(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='IsDerived'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     and typed_as='bool'
  //         is_derived typed_as='bool' type_val='Base'
  //             get_field typed_as='Derived' str_val='derived'
  //                 this typed_as='OperationChecks'
  //         not typed_as='bool'
  //             is_derived typed_as='bool' type_val='Derived'
  //                 get_field typed_as='Base' str_val='base'
  //                     this typed_as='OperationChecks'
  //
  hstd::ext::unidata::EvalRuntime expression_runtime = hstd::ext::unidata::EvalRuntime{ctx};
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::IsDerived);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    auto condition5 = ud::UniValue<ud::StaticT<bool>>::FromConst(true, "true");
    if (*condition5.get()) {
      hstd::unidata_dsl::test::Derived const& expr6 = expr0.Field(&expr0.get()->derived, "derived");
      bool const& expr7 = ud::eval_is_derived<hstd::unidata_dsl::test::Base>(expr6);
      condition5 = expr7;
    }
    if (*condition5.get()) {
      hstd::unidata_dsl::test::Base const& expr8 = expr0.Field(&expr0.get()->base, "base");
      bool const& expr9 = ud::eval_is_derived<hstd::unidata_dsl::test::Derived>(expr8);
      bool const& expr10 = ud::eval_not<bool>((expr9));
      condition5 = expr10;
    }
    condition1 = *condition5.get();
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr11 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.IsDerived"), "poc.IsDerived");
    return ud::VerifyResult::Error(*expr11.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_TypeCond(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='TypeCond'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         type_cond typed_as='int64' bool_val=False
  //             list_at typed_as='dyn<Derived>'
  //                 walk typed_as='list<dyn<Derived>>'
  //                     get_field typed_as='Derived' str_val='derived'
  //                         this typed_as='OperationChecks'
  //                 const_int typed_as='int64' int_val=0
  //             type_case typed_as='int64' type_val='Base' binders=('record',)
  //                 get_field typed_as='int64' str_val='id'
  //                     var typed_as='Base' str_val='record'
  //             type_case typed_as='int64' type_val='Derived' binders=('record',)
  //                 const_int typed_as='int64' int_val=-1
  //         const_int typed_as='int64' int_val=6
  //
  hstd::ext::unidata::EvalRuntime expression_runtime = hstd::ext::unidata::EvalRuntime{ctx};
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::TypeCond);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::Derived const& expr5 = expr0.Field(&expr0.get()->derived, "derived");
    hstd::Vec<DynamicT> const& expr6 = ud::eval_walk(expression_runtime, expr5);
    int64_t const& expr7 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
    DynamicT const& expr8 = ud::eval_list_at<DynamicT>(expr6, expr7);
    std::optional<int64_t> result9 = std::nullopt;
    if (!(result9.has_value())) {
      auto const* candidate10 = expression_runtime.try_as<hstd::unidata_dsl::test::Base>(expr8);
      if (candidate10 != nullptr) {
        int64_t const& expr11 = (*candidate10).Field(&(*candidate10).get()->id, "id");
        result9.emplace(expr11);
      }
    }
    if (!(result9.has_value())) {
      auto const* candidate12 = expression_runtime.try_as<hstd::unidata_dsl::test::Derived>(expr8);
      if (candidate12 != nullptr) {
        int64_t const& expr13 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(-1), "-1");
        result9.emplace(expr13);
      }
    }
    if (!(result9.has_value())) {
      throw std::runtime_error{"No type case matched at hstd_test_model.py:504; expected one of: Base, Derived"};
    }
    int64_t const& expr14 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(6), "6");
    bool const& expr15 = ud::eval_eq<bool>(result9.value(), expr14);
    condition1 = expr15;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr16 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.TypeCond"), "poc.TypeCond");
    return ud::VerifyResult::Error(*expr16.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_TypeCondOptional(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='TypeCondOptional'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     and typed_as='bool'
  //         not typed_as='bool'
  //             opt_has_value typed_as='bool'
  //                 type_cond typed_as='optional<int64>' bool_val=True
  //                     list_at typed_as='dyn<Base>'
  //                         walk typed_as='list<dyn<Base>>'
  //                             get_field typed_as='Base' str_val='base'
  //                                 this typed_as='OperationChecks'
  //                         const_int typed_as='int64' int_val=0
  //                     type_case typed_as='int64' type_val='Derived' binders=('record',)
  //                         get_field typed_as='int64' str_val='id'
  //                             var typed_as='Derived' str_val='record'
  //         eq typed_as='bool'
  //             opt_value typed_as='int64'
  //                 type_cond typed_as='optional<int64>' bool_val=True
  //                     list_at typed_as='dyn<Derived>'
  //                         walk typed_as='list<dyn<Derived>>'
  //                             get_field typed_as='Derived' str_val='derived'
  //                                 this typed_as='OperationChecks'
  //                         const_int typed_as='int64' int_val=0
  //                     type_case typed_as='int64' type_val='Derived' binders=('record',)
  //                         get_field typed_as='int64' str_val='id'
  //                             var typed_as='Derived' str_val='record'
  //             const_int typed_as='int64' int_val=6
  //
  hstd::ext::unidata::EvalRuntime expression_runtime = hstd::ext::unidata::EvalRuntime{ctx};
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::TypeCondOptional);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    auto condition5 = ud::UniValue<ud::StaticT<bool>>::FromConst(true, "true");
    if (*condition5.get()) {
      hstd::unidata_dsl::test::Base const& expr6 = expr0.Field(&expr0.get()->base, "base");
      hstd::Vec<DynamicT> const& expr7 = ud::eval_walk(expression_runtime, expr6);
      int64_t const& expr8 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
      DynamicT const& expr9 = ud::eval_list_at<DynamicT>(expr7, expr8);
      std::optional<int64_t> result10 = std::nullopt;
      if (!(result10.has_value())) {
        auto const* candidate11 = expression_runtime.try_as<hstd::unidata_dsl::test::Derived>(expr9);
        if (candidate11 != nullptr) {
          int64_t const& expr12 = (*candidate11).Field(&(*candidate11).get()->id, "id");
          result10.emplace(expr12);
        }
      }
      bool const& expr13 = ud::eval_opt_has_value<bool>(result10);
      bool const& expr14 = ud::eval_not<bool>((expr13));
      condition5 = expr14;
    }
    if (*condition5.get()) {
      hstd::unidata_dsl::test::Derived const& expr15 = expr0.Field(&expr0.get()->derived, "derived");
      hstd::Vec<DynamicT> const& expr16 = ud::eval_walk(expression_runtime, expr15);
      int64_t const& expr17 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
      DynamicT const& expr18 = ud::eval_list_at<DynamicT>(expr16, expr17);
      std::optional<int64_t> result19 = std::nullopt;
      if (!(result19.has_value())) {
        auto const* candidate20 = expression_runtime.try_as<hstd::unidata_dsl::test::Derived>(expr18);
        if (candidate20 != nullptr) {
          int64_t const& expr21 = (*candidate20).Field(&(*candidate20).get()->id, "id");
          result19.emplace(expr21);
        }
      }
      int64_t const& expr22 = ud::eval_opt_value<int64_t>(result19);
      int64_t const& expr23 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(6), "6");
      bool const& expr24 = ud::eval_eq<bool>(expr22, expr23);
      condition5 = expr24;
    }
    condition1 = *condition5.get();
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr25 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.TypeCondOptional"), "poc.TypeCondOptional");
    return ud::VerifyResult::Error(*expr25.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_TypeOf(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='TypeOf'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         type_cond typed_as='string' bool_val=False
  //             list_at typed_as='dyn<Derived>'
  //                 walk typed_as='list<dyn<Derived>>'
  //                     get_field typed_as='Derived' str_val='derived'
  //                         this typed_as='OperationChecks'
  //                 const_int typed_as='int64' int_val=0
  //             type_case typed_as='string' type_val='Base' binders=('record',)
  //                 type_of typed_as='string'
  //                     var typed_as='Base' str_val='record'
  //         const_str typed_as='string' str_val='Derived'
  //
  hstd::ext::unidata::EvalRuntime expression_runtime = hstd::ext::unidata::EvalRuntime{ctx};
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::TypeOf);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::Derived const& expr5 = expr0.Field(&expr0.get()->derived, "derived");
    hstd::Vec<DynamicT> const& expr6 = ud::eval_walk(expression_runtime, expr5);
    int64_t const& expr7 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
    DynamicT const& expr8 = ud::eval_list_at<DynamicT>(expr6, expr7);
    std::optional<hstd::Str> result9 = std::nullopt;
    if (!(result9.has_value())) {
      auto const* candidate10 = expression_runtime.try_as<hstd::unidata_dsl::test::Base>(expr8);
      if (candidate10 != nullptr) {
        hstd::Str const& expr11 = ud::eval_type_of<hstd::Str>((*candidate10));
        result9.emplace(expr11);
      }
    }
    if (!(result9.has_value())) {
      throw std::runtime_error{"No type case matched at hstd_test_model.py:545; expected one of: Base"};
    }
    hstd::Str const& expr12 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("Derived"), "Derived");
    bool const& expr13 = ud::eval_eq<bool>(result9.value(), expr12);
    condition1 = expr13;
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr14 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.TypeOf"), "poc.TypeOf");
    return ud::VerifyResult::Error(*expr14.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_PathOf(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='PathOf'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     and typed_as='bool'
  //         eq typed_as='bool'
  //             str_format typed_as='string' str_val='%s'
  //                 path_of typed_as='path'
  //                     get_field typed_as='int64' str_val='number'
  //                         this typed_as='OperationChecks'
  //             const_str typed_as='string' str_val='/number'
  //         eq typed_as='bool'
  //             list_at typed_as='string'
  //                 map typed_as='list<string>' binders=('number',)
  //                     get_field typed_as='list<int64>' str_val='numbers'
  //                         this typed_as='OperationChecks'
  //                     str_format typed_as='string' str_val='%s'
  //                         path_of typed_as='path'
  //                             var typed_as='int64' str_val='number'
  //                 const_int typed_as='int64' int_val=0
  //             const_str typed_as='string' str_val='/numbers/0'
  //         eq typed_as='bool'
  //             type_cond typed_as='string' bool_val=False
  //                 list_at typed_as='dyn<Derived>'
  //                     walk typed_as='list<dyn<Derived>>'
  //                         get_field typed_as='Derived' str_val='derived'
  //                             this typed_as='OperationChecks'
  //                     const_int typed_as='int64' int_val=0
  //                 type_case typed_as='string' type_val='Base' binders=('record',)
  //                     str_format typed_as='string' str_val='%s'
  //                         path_of typed_as='path'
  //                             var typed_as='Base' str_val='record'
  //             const_str typed_as='string' str_val='/derived'
  //
  hstd::ext::unidata::EvalRuntime expression_runtime = hstd::ext::unidata::EvalRuntime{ctx};
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::PathOf);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    auto condition5 = ud::UniValue<ud::StaticT<bool>>::FromConst(true, "true");
    if (*condition5.get()) {
      int64_t const& expr6 = expr0.Field(&expr0.get()->number, "number");
      hstd::ext::unidata::UniPath const& expr7 = ud::eval_path_of<hstd::ext::unidata::UniPath>(expr6);
      hstd::Str const& expr8 = ud::eval_str_format(ud::eval_str_pattern("%s"), expr7);
      hstd::Str const& expr9 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("/number"), "/number");
      bool const& expr10 = ud::eval_eq<bool>(expr8, expr9);
      condition5 = expr10;
    }
    if (*condition5.get()) {
      hstd::Vec<int64_t> const& expr11 = expr0.Field(&expr0.get()->numbers, "numbers");
      auto callback15 = [&](auto const& item12) {
                        hstd::ext::unidata::UniPath const& expr13 = ud::eval_path_of<hstd::ext::unidata::UniPath>(item12);
                        hstd::Str const& expr14 = ud::eval_str_format(ud::eval_str_pattern("%s"), expr13);
                        return expr14;
                        };
      hstd::Vec<hstd::Str> const& expr16 = ud::eval_map<hstd::Str>(expr11, callback15);
      int64_t const& expr17 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
      hstd::Str const& expr18 = ud::eval_list_at<hstd::Str>(expr16, expr17);
      hstd::Str const& expr19 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("/numbers/0"), "/numbers/0");
      bool const& expr20 = ud::eval_eq<bool>(expr18, expr19);
      condition5 = expr20;
    }
    if (*condition5.get()) {
      hstd::unidata_dsl::test::Derived const& expr21 = expr0.Field(&expr0.get()->derived, "derived");
      hstd::Vec<DynamicT> const& expr22 = ud::eval_walk(expression_runtime, expr21);
      int64_t const& expr23 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
      DynamicT const& expr24 = ud::eval_list_at<DynamicT>(expr22, expr23);
      std::optional<hstd::Str> result25 = std::nullopt;
      if (!(result25.has_value())) {
        auto const* candidate26 = expression_runtime.try_as<hstd::unidata_dsl::test::Base>(expr24);
        if (candidate26 != nullptr) {
          hstd::ext::unidata::UniPath const& expr27 = ud::eval_path_of<hstd::ext::unidata::UniPath>((*candidate26));
          hstd::Str const& expr28 = ud::eval_str_format(ud::eval_str_pattern("%s"), expr27);
          result25.emplace(expr28);
        }
      }
      if (!(result25.has_value())) {
        throw std::runtime_error{"No type case matched at hstd_test_model.py:565; expected one of: Base"};
      }
      hstd::Str const& expr29 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("/derived"), "/derived");
      bool const& expr30 = ud::eval_eq<bool>(result25.value(), expr29);
      condition5 = expr30;
    }
    condition1 = *condition5.get();
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr31 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.PathOf"), "poc.PathOf");
    return ud::VerifyResult::Error(*expr31.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_EmptyCollections(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='EmptyCollections'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     and typed_as='bool'
  //         all typed_as='bool' binders=('number',)
  //             list_empty typed_as='list<int64>' type_val='list<int64>'
  //             lt typed_as='bool'
  //                 const_int typed_as='int64' int_val=0
  //                 var typed_as='int64' str_val='number'
  //         not typed_as='bool'
  //             exists typed_as='bool' binders=('number',)
  //                 list_empty typed_as='list<int64>' type_val='list<int64>'
  //                 lt typed_as='bool'
  //                     const_int typed_as='int64' int_val=0
  //                     var typed_as='int64' str_val='number'
  //         not typed_as='bool'
  //             exists_one typed_as='bool' binders=('number',)
  //                 list_empty typed_as='list<int64>' type_val='list<int64>'
  //                 lt typed_as='bool'
  //                     const_int typed_as='int64' int_val=0
  //                     var typed_as='int64' str_val='number'
  //         eq typed_as='bool'
  //             sum typed_as='int64'
  //                 list_empty typed_as='list<int64>' type_val='list<int64>'
  //             const_int typed_as='int64' int_val=0
  //         eq typed_as='bool'
  //             list_size typed_as='int64'
  //                 map typed_as='list<int64>' binders=('unused',)
  //                     list_empty typed_as='list<int64>' type_val='list<int64>'
  //                     map_get typed_as='int64'
  //                         get_field typed_as='map<string, int64>' str_val='mapping'
  //                             this typed_as='OperationChecks'
  //                         const_str typed_as='string' str_val='absent'
  //             const_int typed_as='int64' int_val=0
  //         eq typed_as='bool'
  //             list_size typed_as='int64'
  //                 filter typed_as='list<int64>' binders=('unused',)
  //                     list_empty typed_as='list<int64>' type_val='list<int64>'
  //                     eq typed_as='bool'
  //                         opt_value typed_as='int64'
  //                             get_field typed_as='optional<int64>' str_val='optional'
  //                                 this typed_as='OperationChecks'
  //                         const_int typed_as='int64' int_val=0
  //             const_int typed_as='int64' int_val=0
  //         eq typed_as='bool'
  //             list_size typed_as='int64'
  //                 filter_map typed_as='list<int64>' binders=('unused',)
  //                     list_empty typed_as='list<int64>' type_val='list<int64>'
  //                     get_field typed_as='optional<int64>' str_val='optional'
  //                         this typed_as='OperationChecks'
  //             const_int typed_as='int64' int_val=0
  //         eq typed_as='bool'
  //             list_size typed_as='int64'
  //                 take_while typed_as='list<int64>' binders=('unused',)
  //                     list_empty typed_as='list<int64>' type_val='list<int64>'
  //                     eq typed_as='bool'
  //                         opt_value typed_as='int64'
  //                             get_field typed_as='optional<int64>' str_val='optional'
  //                                 this typed_as='OperationChecks'
  //                         const_int typed_as='int64' int_val=0
  //             const_int typed_as='int64' int_val=0
  //         eq typed_as='bool'
  //             map_size typed_as='int64'
  //                 group_by typed_as='map<int64, list<int64>>' binders=('unused',)
  //                     list_empty typed_as='list<int64>' type_val='list<int64>'
  //                     map_get typed_as='int64'
  //                         get_field typed_as='map<string, int64>' str_val='mapping'
  //                             this typed_as='OperationChecks'
  //                         const_str typed_as='string' str_val='absent'
  //             const_int typed_as='int64' int_val=0
  //         eq typed_as='bool'
  //             fold typed_as='int64' binders=('acc', 'unused')
  //                 list_empty typed_as='list<int64>' type_val='list<int64>'
  //                 const_int typed_as='int64' int_val=9
  //                 map_get typed_as='int64'
  //                     get_field typed_as='map<string, int64>' str_val='mapping'
  //                         this typed_as='OperationChecks'
  //                     const_str typed_as='string' str_val='absent'
  //             const_int typed_as='int64' int_val=9
  //         eq typed_as='bool'
  //             list_size typed_as='int64'
  //                 list_concat typed_as='list<int64>'
  //                     list_empty typed_as='list<int64>' type_val='list<int64>'
  //                     list_empty typed_as='list<int64>' type_val='list<int64>'
  //             const_int typed_as='int64' int_val=0
  //         eq typed_as='bool'
  //             cond typed_as='int64'
  //                 const_bool typed_as='bool' bool_val=True
  //                 const_int typed_as='int64' int_val=42
  //                 min typed_as='int64'
  //                     list_empty typed_as='list<int64>' type_val='list<int64>'
  //             const_int typed_as='int64' int_val=42
  //         eq typed_as='bool'
  //             cond typed_as='int64'
  //                 const_bool typed_as='bool' bool_val=True
  //                 const_int typed_as='int64' int_val=42
  //                 max typed_as='int64'
  //                     list_empty typed_as='list<int64>' type_val='list<int64>'
  //             const_int typed_as='int64' int_val=42
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::UniValue<ud::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    hstd::unidata_dsl::test::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    bool const& expr3 = ud::eval_eq<bool>(expr2, hstd::unidata_dsl::test::CheckKind::EmptyCollections);
    bool const& expr4 = ud::eval_not<bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    auto condition5 = ud::UniValue<ud::StaticT<bool>>::FromConst(true, "true");
    if (*condition5.get()) {
      hstd::Vec<int64_t> const& expr6 = ud::eval_list_empty<hstd::Vec<int64_t>>();
      auto callback10 = [&](auto const& item7) {
                        int64_t const& expr8 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
                        bool const& expr9 = ud::eval_lt<bool>(expr8, item7);
                        return expr9;
                        };
      bool const& expr11 = ud::eval_all(expr6, callback10);
      condition5 = expr11;
    }
    if (*condition5.get()) {
      hstd::Vec<int64_t> const& expr12 = ud::eval_list_empty<hstd::Vec<int64_t>>();
      auto callback16 = [&](auto const& item13) {
                        int64_t const& expr14 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
                        bool const& expr15 = ud::eval_lt<bool>(expr14, item13);
                        return expr15;
                        };
      bool const& expr17 = ud::eval_exists(expr12, callback16);
      bool const& expr18 = ud::eval_not<bool>((expr17));
      condition5 = expr18;
    }
    if (*condition5.get()) {
      hstd::Vec<int64_t> const& expr19 = ud::eval_list_empty<hstd::Vec<int64_t>>();
      auto callback23 = [&](auto const& item20) {
                        int64_t const& expr21 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
                        bool const& expr22 = ud::eval_lt<bool>(expr21, item20);
                        return expr22;
                        };
      bool const& expr24 = ud::eval_exists_one(expr19, callback23);
      bool const& expr25 = ud::eval_not<bool>((expr24));
      condition5 = expr25;
    }
    if (*condition5.get()) {
      hstd::Vec<int64_t> const& expr26 = ud::eval_list_empty<hstd::Vec<int64_t>>();
      int64_t const& expr27 = ud::eval_sum<int64_t>(expr26);
      int64_t const& expr28 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
      bool const& expr29 = ud::eval_eq<bool>(expr27, expr28);
      condition5 = expr29;
    }
    if (*condition5.get()) {
      hstd::Vec<int64_t> const& expr30 = ud::eval_list_empty<hstd::Vec<int64_t>>();
      auto callback35 = [&](auto const& item31) {
                        hstd::UnorderedMap<hstd::Str, int64_t> const& expr32 = expr0.Field(&expr0.get()->mapping, "mapping");
                        hstd::Str const& expr33 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("absent"), "absent");
                        int64_t const& expr34 = ud::eval_map_get<int64_t>(expr32, expr33);
                        return expr34;
                        };
      hstd::Vec<int64_t> const& expr36 = ud::eval_map<int64_t>(expr30, callback35);
      int64_t const& expr37 = ud::eval_list_size<int64_t>(expr36);
      int64_t const& expr38 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
      bool const& expr39 = ud::eval_eq<bool>(expr37, expr38);
      condition5 = expr39;
    }
    if (*condition5.get()) {
      hstd::Vec<int64_t> const& expr40 = ud::eval_list_empty<hstd::Vec<int64_t>>();
      auto callback46 = [&](auto const& item41) {
                        hstd::Opt<int64_t> const& expr42 = expr0.Field(&expr0.get()->optional, "optional");
                        int64_t const& expr43 = ud::eval_opt_value<int64_t>(expr42);
                        int64_t const& expr44 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
                        bool const& expr45 = ud::eval_eq<bool>(expr43, expr44);
                        return expr45;
                        };
      hstd::Vec<int64_t> const& expr47 = ud::eval_filter<int64_t>(expr40, callback46);
      int64_t const& expr48 = ud::eval_list_size<int64_t>(expr47);
      int64_t const& expr49 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
      bool const& expr50 = ud::eval_eq<bool>(expr48, expr49);
      condition5 = expr50;
    }
    if (*condition5.get()) {
      hstd::Vec<int64_t> const& expr51 = ud::eval_list_empty<hstd::Vec<int64_t>>();
      auto callback54 = [&](auto const& item52) {
                        hstd::Opt<int64_t> const& expr53 = expr0.Field(&expr0.get()->optional, "optional");
                        return expr53;
                        };
      hstd::Vec<int64_t> const& expr55 = ud::eval_filter_map<hstd::Vec<int64_t>>(expr51, callback54);
      int64_t const& expr56 = ud::eval_list_size<int64_t>(expr55);
      int64_t const& expr57 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
      bool const& expr58 = ud::eval_eq<bool>(expr56, expr57);
      condition5 = expr58;
    }
    if (*condition5.get()) {
      hstd::Vec<int64_t> const& expr59 = ud::eval_list_empty<hstd::Vec<int64_t>>();
      auto callback65 = [&](auto const& item60) {
                        hstd::Opt<int64_t> const& expr61 = expr0.Field(&expr0.get()->optional, "optional");
                        int64_t const& expr62 = ud::eval_opt_value<int64_t>(expr61);
                        int64_t const& expr63 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
                        bool const& expr64 = ud::eval_eq<bool>(expr62, expr63);
                        return expr64;
                        };
      hstd::Vec<int64_t> const& expr66 = ud::eval_take_while<hstd::Vec<int64_t>>(expr59, callback65);
      int64_t const& expr67 = ud::eval_list_size<int64_t>(expr66);
      int64_t const& expr68 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
      bool const& expr69 = ud::eval_eq<bool>(expr67, expr68);
      condition5 = expr69;
    }
    if (*condition5.get()) {
      hstd::Vec<int64_t> const& expr70 = ud::eval_list_empty<hstd::Vec<int64_t>>();
      auto callback75 = [&](auto const& item71) {
                        hstd::UnorderedMap<hstd::Str, int64_t> const& expr72 = expr0.Field(&expr0.get()->mapping, "mapping");
                        hstd::Str const& expr73 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("absent"), "absent");
                        int64_t const& expr74 = ud::eval_map_get<int64_t>(expr72, expr73);
                        return expr74;
                        };
      hstd::UnorderedMap<int64_t, hstd::Vec<int64_t>> const& expr76 = ud::eval_group_by<hstd::UnorderedMap<int64_t, hstd::Vec<int64_t>>>(expr70, callback75);
      int64_t const& expr77 = ud::eval_map_size<int64_t>(expr76);
      int64_t const& expr78 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
      bool const& expr79 = ud::eval_eq<bool>(expr77, expr78);
      condition5 = expr79;
    }
    if (*condition5.get()) {
      hstd::Vec<int64_t> const& expr80 = ud::eval_list_empty<hstd::Vec<int64_t>>();
      int64_t const& expr81 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(9), "9");
      auto callback82 = [&](auto const& item83, auto const& item84) {
                        hstd::UnorderedMap<hstd::Str, int64_t> const& expr85 = expr0.Field(&expr0.get()->mapping, "mapping");
                        hstd::Str const& expr86 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("absent"), "absent");
                        int64_t const& expr87 = ud::eval_map_get<int64_t>(expr85, expr86);
                        return expr87;
                        };
      int64_t const& expr88 = ud::eval_fold<int64_t>(expr80, expr81, callback82);
      int64_t const& expr89 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(9), "9");
      bool const& expr90 = ud::eval_eq<bool>(expr88, expr89);
      condition5 = expr90;
    }
    if (*condition5.get()) {
      hstd::Vec<int64_t> const& expr91 = ud::eval_list_empty<hstd::Vec<int64_t>>();
      hstd::Vec<int64_t> const& expr92 = ud::eval_list_empty<hstd::Vec<int64_t>>();
      hstd::Vec<int64_t> const& expr93 = ud::eval_list_concat<hstd::Vec<int64_t>>(expr91, expr92);
      int64_t const& expr94 = ud::eval_list_size<int64_t>(expr93);
      int64_t const& expr95 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
      bool const& expr96 = ud::eval_eq<bool>(expr94, expr95);
      condition5 = expr96;
    }
    if (*condition5.get()) {
      bool const& expr97 = ud::UniValue<ud::StaticT<bool>>::FromConst(static_cast<bool>(true), "true");
      std::optional<int64_t> result101 = std::nullopt;
      if (expr97) {
        int64_t const& expr98 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(42), "42");
        result101.emplace(expr98);
      } else {
        hstd::Vec<int64_t> const& expr99 = ud::eval_list_empty<hstd::Vec<int64_t>>();
        int64_t const& expr100 = ud::eval_min<int64_t>(expr99);
        result101.emplace(expr100);
      }
      int64_t const& expr102 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(42), "42");
      bool const& expr103 = ud::eval_eq<bool>(result101.value(), expr102);
      condition5 = expr103;
    }
    if (*condition5.get()) {
      bool const& expr104 = ud::UniValue<ud::StaticT<bool>>::FromConst(static_cast<bool>(true), "true");
      std::optional<int64_t> result108 = std::nullopt;
      if (expr104) {
        int64_t const& expr105 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(42), "42");
        result108.emplace(expr105);
      } else {
        hstd::Vec<int64_t> const& expr106 = ud::eval_list_empty<hstd::Vec<int64_t>>();
        int64_t const& expr107 = ud::eval_max<int64_t>(expr106);
        result108.emplace(expr107);
      }
      int64_t const& expr109 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(42), "42");
      bool const& expr110 = ud::eval_eq<bool>(result108.value(), expr109);
      condition5 = expr110;
    }
    condition1 = *condition5.get();
  }
  if (*condition1.get()) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr111 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("poc.EmptyCollections"), "poc.EmptyCollections");
    return ud::VerifyResult::Error(*expr111.get());
  }
}
hstd::ext::unidata::VerifyCheckCollection const* hstd::unidata_dsl::test::OperationChecks::get_unidata_checks() {
  static hstd::ext::unidata::VerifyCheckCollection checks
   = {{
      {hstd::ext::unidata::VerifyKey{"OperationChecks", std::nullopt}, hstd::ext::unidata::VerifyCbList{hstd::ext::unidata::VerifyCb{&__check_record_poc_Eq}, hstd::ext::unidata::VerifyCb{&__check_record_poc_Ne}, hstd::ext::unidata::VerifyCb{&__check_record_poc_Lt}, hstd::ext::unidata::VerifyCb{&__check_record_poc_Le}, hstd::ext::unidata::VerifyCb{&__check_record_poc_Add}, hstd::ext::unidata::VerifyCb{&__check_record_poc_Sub}, hstd::ext::unidata::VerifyCb{&__check_record_poc_Mul}, hstd::ext::unidata::VerifyCb{&__check_record_poc_Div}, hstd::ext::unidata::VerifyCb{&__check_record_poc_ConstFloat}, hstd::ext::unidata::VerifyCb{&__check_record_poc_ConstBool}, hstd::ext::unidata::VerifyCb{&__check_record_poc_And}, hstd::ext::unidata::VerifyCb{&__check_record_poc_Or}, hstd::ext::unidata::VerifyCb{&__check_record_poc_Not}, hstd::ext::unidata::VerifyCb{&__check_record_poc_Cond}, hstd::ext::unidata::VerifyCb{&__check_record_poc_CondLazy}, hstd::ext::unidata::VerifyCb{&__check_record_poc_All}, hstd::ext::unidata::VerifyCb{&__check_record_poc_Exists}, hstd::ext::unidata::VerifyCb{&__check_record_poc_ExistsOne}, hstd::ext::unidata::VerifyCb{&__check_record_poc_Map}, hstd::ext::unidata::VerifyCb{&__check_record_poc_Filter}, hstd::ext::unidata::VerifyCb{&__check_record_poc_FilterMap}, hstd::ext::unidata::VerifyCb{&__check_record_poc_TakeWhile}, hstd::ext::unidata::VerifyCb{&__check_record_poc_GroupBy}, hstd::ext::unidata::VerifyCb{&__check_record_poc_Fold}, hstd::ext::unidata::VerifyCb{&__check_record_poc_Walk}, hstd::ext::unidata::VerifyCb{&__check_record_poc_Sum}, hstd::ext::unidata::VerifyCb{&__check_record_poc_Min}, hstd::ext::unidata::VerifyCb{&__check_record_poc_Max}, hstd::ext::unidata::VerifyCb{&__check_record_poc_StrSize}, hstd::ext::unidata::VerifyCb{&__check_record_poc_StrMatches}, hstd::ext::unidata::VerifyCb{&__check_record_poc_StrFormat}, hstd::ext::unidata::VerifyCb{&__check_record_poc_ListSize}, hstd::ext::unidata::VerifyCb{&__check_record_poc_ListContains}, hstd::ext::unidata::VerifyCb{&__check_record_poc_ListAt}, hstd::ext::unidata::VerifyCb{&__check_record_poc_ListSlice}, hstd::ext::unidata::VerifyCb{&__check_record_poc_ListSliceBounds}, hstd::ext::unidata::VerifyCb{&__check_record_poc_ListConcat}, hstd::ext::unidata::VerifyCb{&__check_record_poc_ListEmpty}, hstd::ext::unidata::VerifyCb{&__check_record_poc_MapSize}, hstd::ext::unidata::VerifyCb{&__check_record_poc_MapContains}, hstd::ext::unidata::VerifyCb{&__check_record_poc_MapGet}, hstd::ext::unidata::VerifyCb{&__check_record_poc_MapInsert}, hstd::ext::unidata::VerifyCb{&__check_record_poc_MapReplace}, hstd::ext::unidata::VerifyCb{&__check_record_poc_MapKeys}, hstd::ext::unidata::VerifyCb{&__check_record_poc_MapValues}, hstd::ext::unidata::VerifyCb{&__check_record_poc_MapEmpty}, hstd::ext::unidata::VerifyCb{&__check_record_poc_OptHasValue}, hstd::ext::unidata::VerifyCb{&__check_record_poc_OptValue}, hstd::ext::unidata::VerifyCb{&__check_record_poc_CaseIs}, hstd::ext::unidata::VerifyCb{&__check_record_poc_CaseWhich}, hstd::ext::unidata::VerifyCb{&__check_record_poc_CaseField}, hstd::ext::unidata::VerifyCb{&__check_record_poc_EnumIs}, hstd::ext::unidata::VerifyCb{&__check_record_poc_NthGet}, hstd::ext::unidata::VerifyCb{&__check_record_poc_IsDerived}, hstd::ext::unidata::VerifyCb{&__check_record_poc_TypeCond}, hstd::ext::unidata::VerifyCb{&__check_record_poc_TypeCondOptional}, hstd::ext::unidata::VerifyCb{&__check_record_poc_TypeOf}, hstd::ext::unidata::VerifyCb{&__check_record_poc_PathOf}, hstd::ext::unidata::VerifyCb{&__check_record_poc_EmptyCollections}}}
      }};
  return &checks;
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::FieldChecks::__check_text_text_check(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::FieldChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::FieldChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // lt typed_as='bool'
  //     const_int typed_as='int64' int_val=0
  //     str_size typed_as='int64'
  //         this typed_as='string'
  //
  auto const& expr0 = (this_obj.Field(&this_obj.get()->text, "text"));
  int64_t const& expr1 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
  int64_t const& expr2 = ud::eval_str_size<int64_t>(expr0);
  bool const& expr3 = ud::eval_lt<bool>(expr1, expr2);
  if (expr3) {
    return ud::VerifyResult::Ok();
  } else {
    int64_t const& expr4 = ud::eval_str_size<int64_t>(expr0);
    hstd::Str const& expr5 = ud::eval_str_format(ud::eval_str_pattern("text length is %d"), expr4);
    return ud::VerifyResult::Error(*expr5.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::FieldChecks::__check_numbers_numbers_check(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::FieldChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::FieldChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // all typed_as='bool' binders=('number',)
  //     this typed_as='list<int64>'
  //     lt typed_as='bool'
  //         const_int typed_as='int64' int_val=0
  //         var typed_as='int64' str_val='number'
  //
  auto const& expr0 = (this_obj.Field(&this_obj.get()->numbers, "numbers"));
  auto callback4 = [&](auto const& item1) {
                   int64_t const& expr2 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(0), "0");
                   bool const& expr3 = ud::eval_lt<bool>(expr2, item1);
                   return expr3;
                   };
  bool const& expr5 = ud::eval_all(expr0, callback4);
  if (expr5) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Str const& expr6 = ud::eval_str_format(ud::eval_str_pattern("values=%s"), expr0);
    return ud::VerifyResult::Error(*expr6.get());
  }
}
hstd::ext::unidata::VerifyCheckCollection const* hstd::unidata_dsl::test::FieldChecks::get_unidata_checks() {
  static hstd::ext::unidata::VerifyCheckCollection checks
   = {{
      {hstd::ext::unidata::VerifyKey{"FieldChecks", "text"}, hstd::ext::unidata::VerifyCbList{hstd::ext::unidata::VerifyCb{&__check_text_text_check}}},
      {hstd::ext::unidata::VerifyKey{"FieldChecks", "numbers"}, hstd::ext::unidata::VerifyCbList{hstd::ext::unidata::VerifyCb{&__check_numbers_numbers_check}}}
      }};
  return &checks;
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::MessageChecks::__check_record_format_message(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::MessageChecks const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::MessageChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // eq typed_as='bool'
  //     get_field typed_as='int64' str_val='number'
  //         this typed_as='MessageChecks'
  //     const_int typed_as='int64' int_val=6
  //
  auto const& expr0 = (this_obj);
  int64_t const& expr1 = expr0.Field(&expr0.get()->number, "number");
  int64_t const& expr2 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(6), "6");
  bool const& expr3 = ud::eval_eq<bool>(expr1, expr2);
  if (expr3) {
    return ud::VerifyResult::Ok();
  } else {
    int64_t const& expr4 = expr0.Field(&expr0.get()->number, "number");
    double const& expr5 = expr0.Field(&expr0.get()->real, "real");
    double const& expr6 = expr0.Field(&expr0.get()->real, "real");
    int64_t const& expr7 = expr0.Field(&expr0.get()->number, "number");
    int64_t const& expr8 = expr0.Field(&expr0.get()->number, "number");
    bool const& expr9 = expr0.Field(&expr0.get()->flag, "flag");
    hstd::Str const& expr10 = expr0.Field(&expr0.get()->text, "text");
    hstd::Vec<int64_t> const& expr11 = expr0.Field(&expr0.get()->numbers, "numbers");
    hstd::UnorderedMap<hstd::Str, int64_t> const& expr12 = expr0.Field(&expr0.get()->details, "details");
    hstd::Str const& expr13 = ud::UniValue<ud::StaticT<hstd::Str>>::FromConst(static_cast<hstd::Str>("detail"), "detail");
    int64_t const& expr14 = ud::eval_map_get<int64_t>(expr12, expr13);
    hstd::Str const& expr15 = ud::eval_str_format(ud::eval_str_pattern("n=%d real=%f sci=%e hex=%x oct=%o flag=%b text=%s list=%s lookup=%d %%"), expr4, expr5, expr6, expr7, expr8, expr9, expr10, expr11, expr14);
    return ud::VerifyResult::Error(*expr15.get());
  }
}
hstd::ext::unidata::VerifyCheckCollection const* hstd::unidata_dsl::test::MessageChecks::get_unidata_checks() {
  static hstd::ext::unidata::VerifyCheckCollection checks
   = {{
      {hstd::ext::unidata::VerifyKey{"MessageChecks", std::nullopt}, hstd::ext::unidata::VerifyCbList{hstd::ext::unidata::VerifyCb{&__check_record_format_message}}}
      }};
  return &checks;
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::Graph::__check_record_graph_unique_node_ids(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::Graph const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::Graph>>::RootValue(this_obj_ptr, ctx->getPath());
  // all typed_as='bool' binders=('group',)
  //     map_values typed_as='list<list<Node>>'
  //         group_by typed_as='map<string, list<Node>>' binders=('node',)
  //             filter_map typed_as='list<Node>' binders=('node_any',)
  //                 walk typed_as='list<dyn<Graph>>'
  //                     this typed_as='Graph'
  //                 type_cond typed_as='optional<Node>' bool_val=True
  //                     var typed_as='dyn<Graph>' str_val='node_any'
  //                     type_case typed_as='Node' type_val='Node' binders=('node',)
  //                         var typed_as='Node' str_val='node'
  //             get_field typed_as='string' str_val='id'
  //                 var typed_as='Node' str_val='node'
  //     le typed_as='bool'
  //         list_size typed_as='int64'
  //             var typed_as='list<Node>' str_val='group'
  //         const_int typed_as='int64' int_val=1
  //
  hstd::ext::unidata::EvalRuntime expression_runtime = hstd::ext::unidata::EvalRuntime{ctx};
  auto const& expr0 = (this_obj);
  hstd::Vec<DynamicT> const& expr1 = ud::eval_walk(expression_runtime, expr0);
  auto callback5 = [&](auto const& item2) {
                   std::optional<hstd::unidata_dsl::test::Node> result3 = std::nullopt;
                   if (!(result3.has_value())) {
                     auto const* candidate4 = expression_runtime.try_as<hstd::unidata_dsl::test::Node>(item2);
                     if (candidate4 != nullptr) {
                       result3.emplace((*candidate4));
                     }
                   }
                   return result3;
                   };
  hstd::Vec<hstd::unidata_dsl::test::Node> const& expr6 = ud::eval_filter_map<hstd::Vec<hstd::unidata_dsl::test::Node>>(expr1, callback5);
  auto callback9 = [&](auto const& item7) {
                   hstd::Str const& expr8 = item7.Field(&item7.get()->id, "id");
                   return expr8;
                   };
  hstd::UnorderedMap<hstd::Str, hstd::Vec<hstd::unidata_dsl::test::Node>> const& expr10 = ud::eval_group_by<hstd::UnorderedMap<hstd::Str, hstd::Vec<hstd::unidata_dsl::test::Node>>>(expr6, callback9);
  hstd::Vec<hstd::Vec<hstd::unidata_dsl::test::Node>> const& expr11 = ud::eval_map_values<hstd::Vec<hstd::Vec<hstd::unidata_dsl::test::Node>>>(expr10);
  auto callback16 = [&](auto const& item12) {
                    int64_t const& expr13 = ud::eval_list_size<int64_t>(item12);
                    int64_t const& expr14 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(1), "1");
                    bool const& expr15 = ud::eval_le<bool>(expr13, expr14);
                    return expr15;
                    };
  bool const& expr17 = ud::eval_all(expr11, callback16);
  if (expr17) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Vec<DynamicT> const& expr18 = ud::eval_walk(expression_runtime, expr0);
    auto callback22 = [&](auto const& item19) {
                      std::optional<hstd::unidata_dsl::test::Node> result20 = std::nullopt;
                      if (!(result20.has_value())) {
                        auto const* candidate21 = expression_runtime.try_as<hstd::unidata_dsl::test::Node>(item19);
                        if (candidate21 != nullptr) {
                          result20.emplace((*candidate21));
                        }
                      }
                      return result20;
                      };
    hstd::Vec<hstd::unidata_dsl::test::Node> const& expr23 = ud::eval_filter_map<hstd::Vec<hstd::unidata_dsl::test::Node>>(expr18, callback22);
    auto callback26 = [&](auto const& item24) {
                      hstd::Str const& expr25 = item24.Field(&item24.get()->id, "id");
                      return expr25;
                      };
    hstd::UnorderedMap<hstd::Str, hstd::Vec<hstd::unidata_dsl::test::Node>> const& expr27 = ud::eval_group_by<hstd::UnorderedMap<hstd::Str, hstd::Vec<hstd::unidata_dsl::test::Node>>>(expr23, callback26);
    hstd::Vec<hstd::Vec<hstd::unidata_dsl::test::Node>> const& expr28 = ud::eval_map_values<hstd::Vec<hstd::Vec<hstd::unidata_dsl::test::Node>>>(expr27);
    auto callback33 = [&](auto const& item29) {
                      int64_t const& expr30 = ud::UniValue<ud::StaticT<int64_t>>::FromConst(static_cast<int64_t>(1), "1");
                      int64_t const& expr31 = ud::eval_list_size<int64_t>(item29);
                      bool const& expr32 = ud::eval_lt<bool>(expr30, expr31);
                      return expr32;
                      };
    hstd::Vec<hstd::Vec<hstd::unidata_dsl::test::Node>> const& expr34 = ud::eval_filter<hstd::Vec<hstd::unidata_dsl::test::Node>>(expr28, callback33);
    auto callback40 = [&](auto const& item35) {
                      auto callback38 = [&](auto const& item36) {
                                        hstd::ext::unidata::UniPath const& expr37 = ud::eval_path_of<hstd::ext::unidata::UniPath>(item36);
                                        return expr37;
                                        };
                      hstd::Vec<hstd::ext::unidata::UniPath> const& expr39 = ud::eval_map<hstd::ext::unidata::UniPath>(item35, callback38);
                      return expr39;
                      };
    hstd::Vec<hstd::Vec<hstd::ext::unidata::UniPath>> const& expr41 = ud::eval_map<hstd::Vec<hstd::ext::unidata::UniPath>>(expr34, callback40);
    hstd::Str const& expr42 = ud::eval_str_format(ud::eval_str_pattern("duplicate node ids at %s"), expr41);
    return ud::VerifyResult::Error(*expr42.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::Graph::__check_record_graph_no_dangling_edges(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::Graph const*>(value);
  auto this_obj = ud::UniValue<ud::StaticT<hstd::unidata_dsl::test::Graph>>::RootValue(this_obj_ptr, ctx->getPath());
  // let typed_as='bool' binders=('ids',)
  //     map typed_as='list<string>' binders=('node',)
  //         filter_map typed_as='list<Node>' binders=('node_any',)
  //             walk typed_as='list<dyn<Graph>>'
  //                 this typed_as='Graph'
  //             type_cond typed_as='optional<Node>' bool_val=True
  //                 var typed_as='dyn<Graph>' str_val='node_any'
  //                 type_case typed_as='Node' type_val='Node' binders=('node',)
  //                     var typed_as='Node' str_val='node'
  //         get_field typed_as='string' str_val='id'
  //             var typed_as='Node' str_val='node'
  //     all typed_as='bool' binders=('edge',)
  //         get_field typed_as='list<Edge>' str_val='edges'
  //             this typed_as='Graph'
  //         and typed_as='bool'
  //             list_contains typed_as='bool'
  //                 var typed_as='list<string>' str_val='ids'
  //                 get_field typed_as='string' str_val='source'
  //                     var typed_as='Edge' str_val='edge'
  //             list_contains typed_as='bool'
  //                 var typed_as='list<string>' str_val='ids'
  //                 get_field typed_as='string' str_val='target'
  //                     var typed_as='Edge' str_val='edge'
  //
  hstd::ext::unidata::EvalRuntime expression_runtime = hstd::ext::unidata::EvalRuntime{ctx};
  auto const& expr0 = (this_obj);
  hstd::Vec<DynamicT> const& expr1 = ud::eval_walk(expression_runtime, expr0);
  auto callback5 = [&](auto const& item2) {
                   std::optional<hstd::unidata_dsl::test::Node> result3 = std::nullopt;
                   if (!(result3.has_value())) {
                     auto const* candidate4 = expression_runtime.try_as<hstd::unidata_dsl::test::Node>(item2);
                     if (candidate4 != nullptr) {
                       result3.emplace((*candidate4));
                     }
                   }
                   return result3;
                   };
  hstd::Vec<hstd::unidata_dsl::test::Node> const& expr6 = ud::eval_filter_map<hstd::Vec<hstd::unidata_dsl::test::Node>>(expr1, callback5);
  auto callback9 = [&](auto const& item7) {
                   hstd::Str const& expr8 = item7.Field(&item7.get()->id, "id");
                   return expr8;
                   };
  hstd::Vec<hstd::Str> const& expr10 = ud::eval_map<hstd::Str>(expr6, callback9);
  hstd::Vec<hstd::unidata_dsl::test::Edge> const& expr11 = expr0.Field(&expr0.get()->edges, "edges");
  auto callback18 = [&](auto const& item12) {
                    auto condition13 = ud::UniValue<ud::StaticT<bool>>::FromConst(true, "true");
                    if (*condition13.get()) {
                      hstd::Str const& expr14 = item12.Field(&item12.get()->source, "source");
                      bool const& expr15 = ud::eval_list_contains<bool>(expr10, expr14);
                      condition13 = expr15;
                    }
                    if (*condition13.get()) {
                      hstd::Str const& expr16 = item12.Field(&item12.get()->target, "target");
                      bool const& expr17 = ud::eval_list_contains<bool>(expr10, expr16);
                      condition13 = expr17;
                    }
                    return *condition13.get();
                    };
  bool const& expr19 = ud::eval_all(expr11, callback18);
  if (expr19) {
    return ud::VerifyResult::Ok();
  } else {
    hstd::Vec<DynamicT> const& expr20 = ud::eval_walk(expression_runtime, expr0);
    auto callback24 = [&](auto const& item21) {
                      std::optional<hstd::unidata_dsl::test::Node> result22 = std::nullopt;
                      if (!(result22.has_value())) {
                        auto const* candidate23 = expression_runtime.try_as<hstd::unidata_dsl::test::Node>(item21);
                        if (candidate23 != nullptr) {
                          result22.emplace((*candidate23));
                        }
                      }
                      return result22;
                      };
    hstd::Vec<hstd::unidata_dsl::test::Node> const& expr25 = ud::eval_filter_map<hstd::Vec<hstd::unidata_dsl::test::Node>>(expr20, callback24);
    auto callback28 = [&](auto const& item26) {
                      hstd::Str const& expr27 = item26.Field(&item26.get()->id, "id");
                      return expr27;
                      };
    hstd::Vec<hstd::Str> const& expr29 = ud::eval_map<hstd::Str>(expr25, callback28);
    hstd::Vec<hstd::unidata_dsl::test::Edge> const& expr30 = expr0.Field(&expr0.get()->edges, "edges");
    auto callback38 = [&](auto const& item31) {
                      auto condition32 = ud::UniValue<ud::StaticT<bool>>::FromConst(true, "true");
                      if (*condition32.get()) {
                        hstd::Str const& expr33 = item31.Field(&item31.get()->source, "source");
                        bool const& expr34 = ud::eval_list_contains<bool>(expr29, expr33);
                        condition32 = expr34;
                      }
                      if (*condition32.get()) {
                        hstd::Str const& expr35 = item31.Field(&item31.get()->target, "target");
                        bool const& expr36 = ud::eval_list_contains<bool>(expr29, expr35);
                        condition32 = expr36;
                      }
                      bool const& expr37 = ud::eval_not<bool>((*condition32.get()));
                      return expr37;
                      };
    hstd::Vec<hstd::unidata_dsl::test::Edge> const& expr39 = ud::eval_filter<hstd::unidata_dsl::test::Edge>(expr30, callback38);
    auto callback42 = [&](auto const& item40) {
                      hstd::ext::unidata::UniPath const& expr41 = ud::eval_path_of<hstd::ext::unidata::UniPath>(item40);
                      return expr41;
                      };
    hstd::Vec<hstd::ext::unidata::UniPath> const& expr43 = ud::eval_map<hstd::ext::unidata::UniPath>(expr39, callback42);
    hstd::Str const& expr44 = ud::eval_str_format(ud::eval_str_pattern("dangling edges at %s"), expr43);
    return ud::VerifyResult::Error(*expr44.get());
  }
}
hstd::ext::unidata::VerifyCheckCollection const* hstd::unidata_dsl::test::Graph::get_unidata_checks() {
  static hstd::ext::unidata::VerifyCheckCollection checks
   = {{
      {hstd::ext::unidata::VerifyKey{"Graph", std::nullopt}, hstd::ext::unidata::VerifyCbList{hstd::ext::unidata::VerifyCb{&__check_record_graph_unique_node_ids}, hstd::ext::unidata::VerifyCb{&__check_record_graph_no_dangling_edges}}}
      }};
  return &checks;
}
/* clang-format on */