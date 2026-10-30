/* clang-format off */
#include "tUnidataDSLModel.hpp"
namespace ud = hstd::ext::unidata


hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::TrivialText::__check_text_text_check(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::TrivialText const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::TrivialText>>::RootValue(this_obj_ptr, ctx->getPath());
  // lt typed_as='bool'
  //     const_int typed_as='int64' int_val=0
  //     str_size typed_as='int64'
  //         this typed_as='string'
  //
  auto const& expr0 = (this_obj.Field(&this_obj.get()->text, "text"));
  ud::int64_t const& expr1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
  ud::int64_t const& expr2 = hstd::ext::unidata::eval_str_size<hstd::ext::unidata::int64_t>(expr0);
  ud::bool const& expr3 = hstd::ext::unidata::eval_lt<hstd::ext::unidata::bool>(expr1, expr2);
  if (expr3) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr4 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("text must not be empty"), "text must not be empty");
    return hstd::ext::unidata::VerifyResult::Error(*expr4.get());
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
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::Base>>::RootValue(this_obj_ptr, ctx->getPath());
  // lt typed_as='bool'
  //     const_int typed_as='int64' int_val=0
  //     get_field typed_as='int64' str_val='id'
  //         this typed_as='Base'
  //
  auto const& expr0 = (this_obj);
  ud::int64_t const& expr1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
  ud::int64_t const& expr2 = expr0.Field(&expr0.get()->id, "id");
  ud::bool const& expr3 = hstd::ext::unidata::eval_lt<hstd::ext::unidata::bool>(expr1, expr2);
  if (expr3) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr4 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("base id must be positive"), "base id must be positive");
    return hstd::ext::unidata::VerifyResult::Error(*expr4.get());
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
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::Derived>>::RootValue(this_obj_ptr, ctx->getPath());
  // lt typed_as='bool'
  //     const_int typed_as='int64' int_val=0
  //     get_field typed_as='int64' str_val='weight'
  //         this typed_as='Derived'
  //
  auto const& expr0 = (this_obj);
  ud::int64_t const& expr1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
  ud::int64_t const& expr2 = expr0.Field(&expr0.get()->weight, "weight");
  ud::bool const& expr3 = hstd::ext::unidata::eval_lt<hstd::ext::unidata::bool>(expr1, expr2);
  if (expr3) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr4 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("derived weight must be positive"), "derived weight must be positive");
    return hstd::ext::unidata::VerifyResult::Error(*expr4.get());
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
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::Eq);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::int64_t const& expr5 = expr0.Field(&expr0.get()->number, "number");
    ud::int64_t const& expr6 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(6), "6");
    ud::bool const& expr7 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr5, expr6);
    condition1 = expr7;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr8 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.Eq"), "poc.Eq");
    return hstd::ext::unidata::VerifyResult::Error(*expr8.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Ne(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::Ne);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::int64_t const& expr5 = expr0.Field(&expr0.get()->number, "number");
    ud::int64_t const& expr6 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(8), "8");
    ud::bool const& expr7 = hstd::ext::unidata::eval_ne<hstd::ext::unidata::bool>(expr5, expr6);
    condition1 = expr7;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr8 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.Ne"), "poc.Ne");
    return hstd::ext::unidata::VerifyResult::Error(*expr8.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Lt(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::Lt);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::int64_t const& expr5 = expr0.Field(&expr0.get()->number, "number");
    ud::int64_t const& expr6 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(7), "7");
    ud::bool const& expr7 = hstd::ext::unidata::eval_lt<hstd::ext::unidata::bool>(expr5, expr6);
    condition1 = expr7;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr8 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.Lt"), "poc.Lt");
    return hstd::ext::unidata::VerifyResult::Error(*expr8.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Le(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::Le);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::int64_t const& expr5 = expr0.Field(&expr0.get()->number, "number");
    ud::int64_t const& expr6 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(6), "6");
    ud::bool const& expr7 = hstd::ext::unidata::eval_le<hstd::ext::unidata::bool>(expr5, expr6);
    condition1 = expr7;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr8 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.Le"), "poc.Le");
    return hstd::ext::unidata::VerifyResult::Error(*expr8.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Add(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::Add);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::int64_t const& expr5 = expr0.Field(&expr0.get()->number, "number");
    ud::int64_t const& expr6 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(3), "3");
    ud::int64_t const& expr7 = hstd::ext::unidata::eval_add<hstd::ext::unidata::int64_t>(expr5, expr6);
    ud::int64_t const& expr8 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(9), "9");
    ud::bool const& expr9 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr7, expr8);
    condition1 = expr9;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr10 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.Add"), "poc.Add");
    return hstd::ext::unidata::VerifyResult::Error(*expr10.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Sub(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::Sub);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::int64_t const& expr5 = expr0.Field(&expr0.get()->number, "number");
    ud::int64_t const& expr6 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(3), "3");
    ud::int64_t const& expr7 = hstd::ext::unidata::eval_sub<hstd::ext::unidata::int64_t>(expr5, expr6);
    ud::int64_t const& expr8 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(3), "3");
    ud::bool const& expr9 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr7, expr8);
    condition1 = expr9;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr10 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.Sub"), "poc.Sub");
    return hstd::ext::unidata::VerifyResult::Error(*expr10.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Mul(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::Mul);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::int64_t const& expr5 = expr0.Field(&expr0.get()->number, "number");
    ud::int64_t const& expr6 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(3), "3");
    ud::int64_t const& expr7 = hstd::ext::unidata::eval_mul<hstd::ext::unidata::int64_t>(expr5, expr6);
    ud::int64_t const& expr8 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(18), "18");
    ud::bool const& expr9 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr7, expr8);
    condition1 = expr9;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr10 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.Mul"), "poc.Mul");
    return hstd::ext::unidata::VerifyResult::Error(*expr10.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Div(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::Div);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::int64_t const& expr5 = expr0.Field(&expr0.get()->number, "number");
    ud::int64_t const& expr6 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(3), "3");
    ud::int64_t const& expr7 = hstd::ext::unidata::eval_div<hstd::ext::unidata::int64_t>(expr5, expr6);
    ud::int64_t const& expr8 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(2), "2");
    ud::bool const& expr9 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr7, expr8);
    condition1 = expr9;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr10 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.Div"), "poc.Div");
    return hstd::ext::unidata::VerifyResult::Error(*expr10.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ConstFloat(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::ConstFloat);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    auto condition5 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(true, "true");
    if (*condition5.get()) {
      ud::double const& expr6 = expr0.Field(&expr0.get()->real, "real");
      ud::double const& expr7 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::double>>::FromConst(static_cast<hstd::ext::unidata::double>(2.5), "2.5");
      ud::bool const& expr8 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr6, expr7);
      condition5 = expr8;
    }
    if (*condition5.get()) {
      ud::double const& expr9 = expr0.Field(&expr0.get()->real, "real");
      ud::double const& expr10 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::double>>::FromConst(static_cast<hstd::ext::unidata::double>(2.0), "2.0");
      ud::double const& expr11 = hstd::ext::unidata::eval_div<hstd::ext::unidata::double>(expr9, expr10);
      ud::double const& expr12 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::double>>::FromConst(static_cast<hstd::ext::unidata::double>(1.25), "1.25");
      ud::bool const& expr13 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr11, expr12);
      condition5 = expr13;
    }
    if (*condition5.get()) {
      ud::double const& expr14 = expr0.Field(&expr0.get()->real, "real");
      ud::double const& expr15 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::double>>::FromConst(static_cast<hstd::ext::unidata::double>(2.0), "2.0");
      ud::double const& expr16 = hstd::ext::unidata::eval_mul<hstd::ext::unidata::double>(expr14, expr15);
      ud::double const& expr17 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::double>>::FromConst(static_cast<hstd::ext::unidata::double>(5.0), "5.0");
      ud::bool const& expr18 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr16, expr17);
      condition5 = expr18;
    }
    if (*condition5.get()) {
      ud::double const& expr19 = expr0.Field(&expr0.get()->real, "real");
      ud::double const& expr20 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::double>>::FromConst(static_cast<hstd::ext::unidata::double>(0.5), "0.5");
      ud::double const& expr21 = hstd::ext::unidata::eval_sub<hstd::ext::unidata::double>(expr19, expr20);
      ud::double const& expr22 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::double>>::FromConst(static_cast<hstd::ext::unidata::double>(2.0), "2.0");
      ud::bool const& expr23 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr21, expr22);
      condition5 = expr23;
    }
    if (*condition5.get()) {
      ud::double const& expr24 = expr0.Field(&expr0.get()->real, "real");
      ud::double const& expr25 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::double>>::FromConst(static_cast<hstd::ext::unidata::double>(0.5), "0.5");
      ud::double const& expr26 = hstd::ext::unidata::eval_add<hstd::ext::unidata::double>(expr24, expr25);
      ud::double const& expr27 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::double>>::FromConst(static_cast<hstd::ext::unidata::double>(3.0), "3.0");
      ud::bool const& expr28 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr26, expr27);
      condition5 = expr28;
    }
    condition1 = *condition5.get();
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr29 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.ConstFloat"), "poc.ConstFloat");
    return hstd::ext::unidata::VerifyResult::Error(*expr29.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ConstBool(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::ConstBool);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::bool const& expr5 = expr0.Field(&expr0.get()->flag, "flag");
    ud::bool const& expr6 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::bool>>::FromConst(static_cast<hstd::ext::unidata::bool>(true), "true");
    ud::bool const& expr7 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr5, expr6);
    condition1 = expr7;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr8 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.ConstBool"), "poc.ConstBool");
    return hstd::ext::unidata::VerifyResult::Error(*expr8.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_And(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::And);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    auto condition5 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(true, "true");
    if (*condition5.get()) {
      ud::bool const& expr6 = expr0.Field(&expr0.get()->flag, "flag");
      condition5 = expr6;
    }
    if (*condition5.get()) {
      ud::int64_t const& expr7 = expr0.Field(&expr0.get()->number, "number");
      ud::int64_t const& expr8 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(6), "6");
      ud::bool const& expr9 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr7, expr8);
      condition5 = expr9;
    }
    if (*condition5.get()) {
      ud::UniMap<ud::Str, ud::int64_t> const& expr10 = expr0.Field(&expr0.get()->mapping, "mapping");
      ud::Str const& expr11 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("a"), "a");
      ud::int64_t const& expr12 = hstd::ext::unidata::eval_map_get<hstd::ext::unidata::int64_t>(expr10, expr11);
      ud::int64_t const& expr13 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(1), "1");
      ud::bool const& expr14 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr12, expr13);
      condition5 = expr14;
    }
    condition1 = *condition5.get();
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr15 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.And"), "poc.And");
    return hstd::ext::unidata::VerifyResult::Error(*expr15.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Or(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::Or);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    auto condition5 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
    if (!(*condition5.get())) {
      ud::bool const& expr6 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::bool>>::FromConst(static_cast<hstd::ext::unidata::bool>(false), "false");
      condition5 = expr6;
    }
    if (!(*condition5.get())) {
      ud::int64_t const& expr7 = expr0.Field(&expr0.get()->number, "number");
      ud::int64_t const& expr8 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(6), "6");
      ud::bool const& expr9 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr7, expr8);
      condition5 = expr9;
    }
    if (!(*condition5.get())) {
      ud::UniMap<ud::Str, ud::int64_t> const& expr10 = expr0.Field(&expr0.get()->mapping, "mapping");
      ud::Str const& expr11 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("a"), "a");
      ud::int64_t const& expr12 = hstd::ext::unidata::eval_map_get<hstd::ext::unidata::int64_t>(expr10, expr11);
      ud::int64_t const& expr13 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(99), "99");
      ud::bool const& expr14 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr12, expr13);
      condition5 = expr14;
    }
    condition1 = *condition5.get();
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr15 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.Or"), "poc.Or");
    return hstd::ext::unidata::VerifyResult::Error(*expr15.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Not(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::Not);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::int64_t const& expr5 = expr0.Field(&expr0.get()->number, "number");
    ud::int64_t const& expr6 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(6), "6");
    ud::bool const& expr7 = hstd::ext::unidata::eval_ne<hstd::ext::unidata::bool>(expr5, expr6);
    ud::bool const& expr8 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr7));
    condition1 = expr8;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr9 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.Not"), "poc.Not");
    return hstd::ext::unidata::VerifyResult::Error(*expr9.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Cond(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::Cond);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::int64_t const& expr5 = expr0.Field(&expr0.get()->number, "number");
    ud::int64_t const& expr6 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(6), "6");
    ud::bool const& expr7 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr5, expr6);
    std::optional<hstd::ext::unidata::Str> result11 = std::nullopt;
    if (expr7) {
      ud::Str const& expr8 = expr0.Field(&expr0.get()->text, "text");
      result11.emplace(expr8);
    } else {
      ud::int64_t const& expr9 = expr0.Field(&expr0.get()->number, "number");
      ud::Str const& expr10 = hstd::ext::unidata::eval_str_format(hstd::ext::unidata::eval_str_pattern("other-%d"), expr9);
      result11.emplace(expr10);
    }
    ud::Str const& expr12 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("six"), "six");
    ud::bool const& expr13 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(result11.value(), expr12);
    condition1 = expr13;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr14 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.Cond"), "poc.Cond");
    return hstd::ext::unidata::VerifyResult::Error(*expr14.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_CondLazy(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::CondLazy);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::bool const& expr5 = expr0.Field(&expr0.get()->flag, "flag");
    std::optional<hstd::ext::unidata::int64_t> result12 = std::nullopt;
    if (expr5) {
      ud::UniMap<ud::Str, ud::int64_t> const& expr6 = expr0.Field(&expr0.get()->mapping, "mapping");
      ud::Str const& expr7 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("a"), "a");
      ud::int64_t const& expr8 = hstd::ext::unidata::eval_map_get<hstd::ext::unidata::int64_t>(expr6, expr7);
      result12.emplace(expr8);
    } else {
      ud::UniMap<ud::Str, ud::int64_t> const& expr9 = expr0.Field(&expr0.get()->mapping, "mapping");
      ud::Str const& expr10 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("absent"), "absent");
      ud::int64_t const& expr11 = hstd::ext::unidata::eval_map_get<hstd::ext::unidata::int64_t>(expr9, expr10);
      result12.emplace(expr11);
    }
    ud::int64_t const& expr13 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(1), "1");
    ud::bool const& expr14 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(result12.value(), expr13);
    condition1 = expr14;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr15 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.CondLazy"), "poc.CondLazy");
    return hstd::ext::unidata::VerifyResult::Error(*expr15.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_All(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::All);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::UniVec<ud::int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    auto callback9 = [&](auto const& item6) {
                     ud::int64_t const& expr7 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(4), "4");
                     ud::bool const& expr8 = hstd::ext::unidata::eval_lt<hstd::ext::unidata::bool>(item6, expr7);
                     return expr8;
                     };
    ud::bool const& expr10 = hstd::ext::unidata::eval_all(expr5, callback9);
    condition1 = expr10;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr11 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.All"), "poc.All");
    return hstd::ext::unidata::VerifyResult::Error(*expr11.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Exists(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::Exists);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::UniVec<ud::int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    auto callback9 = [&](auto const& item6) {
                     ud::int64_t const& expr7 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(3), "3");
                     ud::bool const& expr8 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(item6, expr7);
                     return expr8;
                     };
    ud::bool const& expr10 = hstd::ext::unidata::eval_exists(expr5, callback9);
    condition1 = expr10;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr11 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.Exists"), "poc.Exists");
    return hstd::ext::unidata::VerifyResult::Error(*expr11.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ExistsOne(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::ExistsOne);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::UniVec<ud::int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    auto callback9 = [&](auto const& item6) {
                     ud::int64_t const& expr7 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(3), "3");
                     ud::bool const& expr8 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(item6, expr7);
                     return expr8;
                     };
    ud::bool const& expr10 = hstd::ext::unidata::eval_exists_one(expr5, callback9);
    condition1 = expr10;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr11 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.ExistsOne"), "poc.ExistsOne");
    return hstd::ext::unidata::VerifyResult::Error(*expr11.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Map(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::Map);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::UniVec<ud::int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    auto callback9 = [&](auto const& item6) {
                     ud::int64_t const& expr7 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(2), "2");
                     ud::int64_t const& expr8 = hstd::ext::unidata::eval_mul<hstd::ext::unidata::int64_t>(item6, expr7);
                     return expr8;
                     };
    ud::UniVec<ud::int64_t> const& expr10 = hstd::ext::unidata::eval_map<hstd::ext::unidata::int64_t>(expr5, callback9);
    ud::int64_t const& expr11 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(2), "2");
    ud::int64_t const& expr12 = hstd::ext::unidata::eval_list_at<hstd::ext::unidata::int64_t>(expr10, expr11);
    ud::int64_t const& expr13 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(6), "6");
    ud::bool const& expr14 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr12, expr13);
    condition1 = expr14;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr15 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.Map"), "poc.Map");
    return hstd::ext::unidata::VerifyResult::Error(*expr15.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Filter(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::Filter);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::UniVec<ud::int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    auto callback9 = [&](auto const& item6) {
                     ud::int64_t const& expr7 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(1), "1");
                     ud::bool const& expr8 = hstd::ext::unidata::eval_lt<hstd::ext::unidata::bool>(expr7, item6);
                     return expr8;
                     };
    ud::UniVec<ud::int64_t> const& expr10 = hstd::ext::unidata::eval_filter<hstd::ext::unidata::int64_t>(expr5, callback9);
    ud::int64_t const& expr11 = hstd::ext::unidata::eval_list_size<hstd::ext::unidata::int64_t>(expr10);
    ud::int64_t const& expr12 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(2), "2");
    ud::bool const& expr13 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr11, expr12);
    condition1 = expr13;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr14 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.Filter"), "poc.Filter");
    return hstd::ext::unidata::VerifyResult::Error(*expr14.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_FilterMap(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::FilterMap);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::UniVec<ud::UniOpt<ud::int64_t>> const& expr5 = expr0.Field(&expr0.get()->optionals, "optionals");
    auto callback7 = [&](auto const& item6) {
                     return item6;
                     };
    ud::UniVec<ud::int64_t> const& expr8 = hstd::ext::unidata::eval_filter_map<hstd::Vec<hstd::ext::unidata::int64_t>>(expr5, callback7);
    auto condition9 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(true, "true");
    if (*condition9.get()) {
      ud::int64_t const& expr10 = hstd::ext::unidata::eval_list_size<hstd::ext::unidata::int64_t>(expr8);
      ud::int64_t const& expr11 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(2), "2");
      ud::bool const& expr12 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr10, expr11);
      condition9 = expr12;
    }
    if (*condition9.get()) {
      ud::int64_t const& expr13 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
      ud::int64_t const& expr14 = hstd::ext::unidata::eval_list_at<hstd::ext::unidata::int64_t>(expr8, expr13);
      ud::int64_t const& expr15 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(1), "1");
      ud::bool const& expr16 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr14, expr15);
      condition9 = expr16;
    }
    if (*condition9.get()) {
      ud::int64_t const& expr17 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(1), "1");
      ud::int64_t const& expr18 = hstd::ext::unidata::eval_list_at<hstd::ext::unidata::int64_t>(expr8, expr17);
      ud::int64_t const& expr19 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(3), "3");
      ud::bool const& expr20 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr18, expr19);
      condition9 = expr20;
    }
    condition1 = *condition9.get();
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr21 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.FilterMap"), "poc.FilterMap");
    return hstd::ext::unidata::VerifyResult::Error(*expr21.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_TakeWhile(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::TakeWhile);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::UniVec<ud::int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    auto callback9 = [&](auto const& item6) {
                     ud::int64_t const& expr7 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(3), "3");
                     ud::bool const& expr8 = hstd::ext::unidata::eval_lt<hstd::ext::unidata::bool>(item6, expr7);
                     return expr8;
                     };
    ud::UniVec<ud::int64_t> const& expr10 = hstd::ext::unidata::eval_take_while<hstd::Vec<hstd::ext::unidata::int64_t>>(expr5, callback9);
    ud::int64_t const& expr11 = hstd::ext::unidata::eval_list_size<hstd::ext::unidata::int64_t>(expr10);
    ud::int64_t const& expr12 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(2), "2");
    ud::bool const& expr13 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr11, expr12);
    condition1 = expr13;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr14 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.TakeWhile"), "poc.TakeWhile");
    return hstd::ext::unidata::VerifyResult::Error(*expr14.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_GroupBy(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::GroupBy);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::UniVec<ud::int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    auto callback9 = [&](auto const& item6) {
                     ud::int64_t const& expr7 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(3), "3");
                     ud::bool const& expr8 = hstd::ext::unidata::eval_lt<hstd::ext::unidata::bool>(item6, expr7);
                     return expr8;
                     };
    ud::UniMap<ud::bool, ud::UniVec<ud::int64_t>> const& expr10 = hstd::ext::unidata::eval_group_by<hstd::UnorderedMap<hstd::ext::unidata::bool, hstd::Vec<hstd::ext::unidata::int64_t>>>(expr5, callback9);
    auto condition11 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(true, "true");
    if (*condition11.get()) {
      ud::int64_t const& expr12 = hstd::ext::unidata::eval_map_size<hstd::ext::unidata::int64_t>(expr10);
      ud::int64_t const& expr13 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(2), "2");
      ud::bool const& expr14 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr12, expr13);
      condition11 = expr14;
    }
    if (*condition11.get()) {
      ud::UniVec<ud::UniVec<ud::int64_t>> const& expr15 = hstd::ext::unidata::eval_map_values<hstd::Vec<hstd::Vec<hstd::ext::unidata::int64_t>>>(expr10);
      ud::int64_t const& expr16 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
      ud::UniVec<ud::int64_t> const& expr17 = hstd::ext::unidata::eval_list_at<hstd::Vec<hstd::ext::unidata::int64_t>>(expr15, expr16);
      ud::int64_t const& expr18 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
      ud::int64_t const& expr19 = hstd::ext::unidata::eval_list_at<hstd::ext::unidata::int64_t>(expr17, expr18);
      ud::UniVec<ud::int64_t> const& expr20 = expr0.Field(&expr0.get()->numbers, "numbers");
      ud::int64_t const& expr21 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
      ud::int64_t const& expr22 = hstd::ext::unidata::eval_list_at<hstd::ext::unidata::int64_t>(expr20, expr21);
      ud::bool const& expr23 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr19, expr22);
      condition11 = expr23;
    }
    condition1 = *condition11.get();
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr24 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.GroupBy"), "poc.GroupBy");
    return hstd::ext::unidata::VerifyResult::Error(*expr24.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Fold(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::Fold);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::UniVec<ud::int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    ud::int64_t const& expr6 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
    auto callback7 = [&](auto const& item8, auto const& item9) {
                     ud::int64_t const& expr10 = hstd::ext::unidata::eval_add<hstd::ext::unidata::int64_t>(item8, item9);
                     return expr10;
                     };
    ud::int64_t const& expr11 = hstd::ext::unidata::eval_fold<hstd::ext::unidata::int64_t>(expr5, expr6, callback7);
    ud::int64_t const& expr12 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(6), "6");
    ud::bool const& expr13 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr11, expr12);
    condition1 = expr13;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr14 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.Fold"), "poc.Fold");
    return hstd::ext::unidata::VerifyResult::Error(*expr14.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Walk(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::Walk);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::Derived const& expr5 = expr0.Field(&expr0.get()->derived, "derived");
    ud::UniVec<ud::DynamicT> const& expr6 = hstd::ext::unidata::eval_walk(expression_runtime, expr5);
    auto callback11 = [&](auto const& item7) {
                      std::optional<hstd::ext::unidata::int64_t> result8 = std::nullopt;
                      if (!(result8.has_value())) {
                        auto const* candidate9 = expression_runtime.try_as<hstd::ext::unidata::Derived>(item7);
                        if (candidate9 != nullptr) {
                          ud::int64_t const& expr10 = (*candidate9).Field(&(*candidate9).get()->id, "id");
                          result8.emplace(expr10);
                        }
                      }
                      return result8;
                      };
    ud::UniVec<ud::int64_t> const& expr12 = hstd::ext::unidata::eval_filter_map<hstd::Vec<hstd::ext::unidata::int64_t>>(expr6, callback11);
    auto condition13 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(true, "true");
    if (*condition13.get()) {
      ud::int64_t const& expr14 = hstd::ext::unidata::eval_list_size<hstd::ext::unidata::int64_t>(expr12);
      ud::int64_t const& expr15 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(1), "1");
      ud::bool const& expr16 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr14, expr15);
      condition13 = expr16;
    }
    if (*condition13.get()) {
      ud::int64_t const& expr17 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
      ud::int64_t const& expr18 = hstd::ext::unidata::eval_list_at<hstd::ext::unidata::int64_t>(expr12, expr17);
      ud::int64_t const& expr19 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(6), "6");
      ud::bool const& expr20 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr18, expr19);
      condition13 = expr20;
    }
    condition1 = *condition13.get();
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr21 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.Walk"), "poc.Walk");
    return hstd::ext::unidata::VerifyResult::Error(*expr21.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Sum(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::Sum);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::UniVec<ud::int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    ud::int64_t const& expr6 = hstd::ext::unidata::eval_sum<hstd::ext::unidata::int64_t>(expr5);
    ud::int64_t const& expr7 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(6), "6");
    ud::bool const& expr8 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr6, expr7);
    condition1 = expr8;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr9 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.Sum"), "poc.Sum");
    return hstd::ext::unidata::VerifyResult::Error(*expr9.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Min(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::Min);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::UniVec<ud::int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    ud::int64_t const& expr6 = hstd::ext::unidata::eval_min<hstd::ext::unidata::int64_t>(expr5);
    ud::int64_t const& expr7 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(1), "1");
    ud::bool const& expr8 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr6, expr7);
    condition1 = expr8;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr9 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.Min"), "poc.Min");
    return hstd::ext::unidata::VerifyResult::Error(*expr9.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Max(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::Max);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::UniVec<ud::int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    ud::int64_t const& expr6 = hstd::ext::unidata::eval_max<hstd::ext::unidata::int64_t>(expr5);
    ud::int64_t const& expr7 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(3), "3");
    ud::bool const& expr8 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr6, expr7);
    condition1 = expr8;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr9 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.Max"), "poc.Max");
    return hstd::ext::unidata::VerifyResult::Error(*expr9.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_StrSize(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::StrSize);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::Str const& expr5 = expr0.Field(&expr0.get()->text, "text");
    ud::int64_t const& expr6 = hstd::ext::unidata::eval_str_size<hstd::ext::unidata::int64_t>(expr5);
    ud::int64_t const& expr7 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(3), "3");
    ud::bool const& expr8 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr6, expr7);
    condition1 = expr8;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr9 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.StrSize"), "poc.StrSize");
    return hstd::ext::unidata::VerifyResult::Error(*expr9.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_StrMatches(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::StrMatches);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::Str const& expr5 = expr0.Field(&expr0.get()->text, "text");
    ud::bool const& expr6 = hstd::ext::unidata::eval_str_matches(expr5, "^s[a-z]{2}$");
    condition1 = expr6;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr7 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.StrMatches"), "poc.StrMatches");
    return hstd::ext::unidata::VerifyResult::Error(*expr7.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_StrFormat(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::StrFormat);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::Str const& expr5 = expr0.Field(&expr0.get()->text, "text");
    ud::int64_t const& expr6 = expr0.Field(&expr0.get()->number, "number");
    ud::Str const& expr7 = hstd::ext::unidata::eval_str_format(hstd::ext::unidata::eval_str_pattern("%s:%d"), expr5, expr6);
    ud::Str const& expr8 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("six:6"), "six:6");
    ud::bool const& expr9 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr7, expr8);
    condition1 = expr9;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr10 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.StrFormat"), "poc.StrFormat");
    return hstd::ext::unidata::VerifyResult::Error(*expr10.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ListSize(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::ListSize);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::UniVec<ud::int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    ud::int64_t const& expr6 = hstd::ext::unidata::eval_list_size<hstd::ext::unidata::int64_t>(expr5);
    ud::int64_t const& expr7 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(3), "3");
    ud::bool const& expr8 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr6, expr7);
    condition1 = expr8;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr9 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.ListSize"), "poc.ListSize");
    return hstd::ext::unidata::VerifyResult::Error(*expr9.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ListContains(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::ListContains);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::UniVec<ud::int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    ud::int64_t const& expr6 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(3), "3");
    ud::bool const& expr7 = hstd::ext::unidata::eval_list_contains<hstd::ext::unidata::bool>(expr5, expr6);
    condition1 = expr7;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr8 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.ListContains"), "poc.ListContains");
    return hstd::ext::unidata::VerifyResult::Error(*expr8.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ListAt(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::ListAt);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::UniVec<ud::int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    ud::int64_t const& expr6 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(2), "2");
    ud::int64_t const& expr7 = hstd::ext::unidata::eval_list_at<hstd::ext::unidata::int64_t>(expr5, expr6);
    ud::int64_t const& expr8 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(3), "3");
    ud::bool const& expr9 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr7, expr8);
    condition1 = expr9;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr10 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.ListAt"), "poc.ListAt");
    return hstd::ext::unidata::VerifyResult::Error(*expr10.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ListSlice(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::ListSlice);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::UniVec<ud::int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    ud::int64_t const& expr6 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(1), "1");
    ud::int64_t const& expr7 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(3), "3");
    ud::UniVec<ud::int64_t> const& expr8 = hstd::ext::unidata::eval_list_slice<hstd::Vec<hstd::ext::unidata::int64_t>>(expr5, expr6, expr7);
    auto condition9 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(true, "true");
    if (*condition9.get()) {
      ud::int64_t const& expr10 = hstd::ext::unidata::eval_list_size<hstd::ext::unidata::int64_t>(expr8);
      ud::int64_t const& expr11 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(2), "2");
      ud::bool const& expr12 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr10, expr11);
      condition9 = expr12;
    }
    if (*condition9.get()) {
      ud::int64_t const& expr13 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
      ud::int64_t const& expr14 = hstd::ext::unidata::eval_list_at<hstd::ext::unidata::int64_t>(expr8, expr13);
      ud::int64_t const& expr15 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(2), "2");
      ud::bool const& expr16 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr14, expr15);
      condition9 = expr16;
    }
    if (*condition9.get()) {
      ud::int64_t const& expr17 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(1), "1");
      ud::int64_t const& expr18 = hstd::ext::unidata::eval_list_at<hstd::ext::unidata::int64_t>(expr8, expr17);
      ud::int64_t const& expr19 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(3), "3");
      ud::bool const& expr20 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr18, expr19);
      condition9 = expr20;
    }
    condition1 = *condition9.get();
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr21 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.ListSlice"), "poc.ListSlice");
    return hstd::ext::unidata::VerifyResult::Error(*expr21.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ListSliceBounds(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::ListSliceBounds);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::UniVec<ud::int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    ud::int64_t const& expr6 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(-2), "-2");
    ud::int64_t const& expr7 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(100), "100");
    ud::UniVec<ud::int64_t> const& expr8 = hstd::ext::unidata::eval_list_slice<hstd::Vec<hstd::ext::unidata::int64_t>>(expr5, expr6, expr7);
    auto condition9 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(true, "true");
    if (*condition9.get()) {
      ud::int64_t const& expr10 = hstd::ext::unidata::eval_list_size<hstd::ext::unidata::int64_t>(expr8);
      ud::int64_t const& expr11 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(2), "2");
      ud::bool const& expr12 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr10, expr11);
      condition9 = expr12;
    }
    if (*condition9.get()) {
      ud::int64_t const& expr13 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
      ud::int64_t const& expr14 = hstd::ext::unidata::eval_list_at<hstd::ext::unidata::int64_t>(expr8, expr13);
      ud::int64_t const& expr15 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(2), "2");
      ud::bool const& expr16 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr14, expr15);
      condition9 = expr16;
    }
    if (*condition9.get()) {
      ud::int64_t const& expr17 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(1), "1");
      ud::int64_t const& expr18 = hstd::ext::unidata::eval_list_at<hstd::ext::unidata::int64_t>(expr8, expr17);
      ud::int64_t const& expr19 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(3), "3");
      ud::bool const& expr20 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr18, expr19);
      condition9 = expr20;
    }
    condition1 = *condition9.get();
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr21 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.ListSliceBounds"), "poc.ListSliceBounds");
    return hstd::ext::unidata::VerifyResult::Error(*expr21.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ListConcat(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::ListConcat);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::UniVec<ud::int64_t> const& expr5 = expr0.Field(&expr0.get()->numbers, "numbers");
    ud::UniVec<ud::int64_t> const& expr6 = expr0.Field(&expr0.get()->numbers, "numbers");
    ud::UniVec<ud::int64_t> const& expr7 = hstd::ext::unidata::eval_list_concat<hstd::Vec<hstd::ext::unidata::int64_t>>(expr5, expr6);
    auto condition8 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(true, "true");
    if (*condition8.get()) {
      ud::int64_t const& expr9 = hstd::ext::unidata::eval_list_size<hstd::ext::unidata::int64_t>(expr7);
      ud::int64_t const& expr10 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(6), "6");
      ud::bool const& expr11 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr9, expr10);
      condition8 = expr11;
    }
    if (*condition8.get()) {
      ud::int64_t const& expr12 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(3), "3");
      ud::int64_t const& expr13 = hstd::ext::unidata::eval_list_at<hstd::ext::unidata::int64_t>(expr7, expr12);
      ud::UniVec<ud::int64_t> const& expr14 = expr0.Field(&expr0.get()->numbers, "numbers");
      ud::int64_t const& expr15 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
      ud::int64_t const& expr16 = hstd::ext::unidata::eval_list_at<hstd::ext::unidata::int64_t>(expr14, expr15);
      ud::bool const& expr17 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr13, expr16);
      condition8 = expr17;
    }
    condition1 = *condition8.get();
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr18 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.ListConcat"), "poc.ListConcat");
    return hstd::ext::unidata::VerifyResult::Error(*expr18.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ListEmpty(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::ListEmpty);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::UniVec<ud::int64_t> const& expr5 = hstd::ext::unidata::eval_list_empty<hstd::Vec<hstd::ext::unidata::int64_t>>();
    ud::int64_t const& expr6 = hstd::ext::unidata::eval_list_size<hstd::ext::unidata::int64_t>(expr5);
    ud::int64_t const& expr7 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
    ud::bool const& expr8 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr6, expr7);
    condition1 = expr8;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr9 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.ListEmpty"), "poc.ListEmpty");
    return hstd::ext::unidata::VerifyResult::Error(*expr9.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapSize(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::MapSize);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::UniMap<ud::Str, ud::int64_t> const& expr5 = expr0.Field(&expr0.get()->mapping, "mapping");
    ud::int64_t const& expr6 = hstd::ext::unidata::eval_map_size<hstd::ext::unidata::int64_t>(expr5);
    ud::int64_t const& expr7 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(2), "2");
    ud::bool const& expr8 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr6, expr7);
    condition1 = expr8;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr9 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.MapSize"), "poc.MapSize");
    return hstd::ext::unidata::VerifyResult::Error(*expr9.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapContains(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::MapContains);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::UniMap<ud::Str, ud::int64_t> const& expr5 = expr0.Field(&expr0.get()->mapping, "mapping");
    ud::Str const& expr6 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("a"), "a");
    ud::bool const& expr7 = hstd::ext::unidata::eval_map_contains<hstd::ext::unidata::bool>(expr5, expr6);
    condition1 = expr7;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr8 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.MapContains"), "poc.MapContains");
    return hstd::ext::unidata::VerifyResult::Error(*expr8.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapGet(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::MapGet);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::UniMap<ud::Str, ud::int64_t> const& expr5 = expr0.Field(&expr0.get()->mapping, "mapping");
    ud::Str const& expr6 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("a"), "a");
    ud::int64_t const& expr7 = hstd::ext::unidata::eval_map_get<hstd::ext::unidata::int64_t>(expr5, expr6);
    ud::int64_t const& expr8 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(1), "1");
    ud::bool const& expr9 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr7, expr8);
    condition1 = expr9;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr10 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.MapGet"), "poc.MapGet");
    return hstd::ext::unidata::VerifyResult::Error(*expr10.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapInsert(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::MapInsert);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::UniMap<ud::Str, ud::int64_t> const& expr5 = expr0.Field(&expr0.get()->mapping, "mapping");
    ud::Str const& expr6 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("c"), "c");
    ud::int64_t const& expr7 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(3), "3");
    ud::UniMap<ud::Str, ud::int64_t> const& expr8 = hstd::ext::unidata::eval_map_insert<hstd::UnorderedMap<hstd::ext::unidata::Str, hstd::ext::unidata::int64_t>>(expr5, expr6, expr7);
    auto condition9 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(true, "true");
    if (*condition9.get()) {
      ud::int64_t const& expr10 = hstd::ext::unidata::eval_map_size<hstd::ext::unidata::int64_t>(expr8);
      ud::int64_t const& expr11 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(3), "3");
      ud::bool const& expr12 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr10, expr11);
      condition9 = expr12;
    }
    if (*condition9.get()) {
      ud::Str const& expr13 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("c"), "c");
      ud::int64_t const& expr14 = hstd::ext::unidata::eval_map_get<hstd::ext::unidata::int64_t>(expr8, expr13);
      ud::int64_t const& expr15 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(3), "3");
      ud::bool const& expr16 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr14, expr15);
      condition9 = expr16;
    }
    if (*condition9.get()) {
      ud::UniMap<ud::Str, ud::int64_t> const& expr17 = expr0.Field(&expr0.get()->mapping, "mapping");
      ud::Str const& expr18 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("c"), "c");
      ud::bool const& expr19 = hstd::ext::unidata::eval_map_contains<hstd::ext::unidata::bool>(expr17, expr18);
      ud::bool const& expr20 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr19));
      condition9 = expr20;
    }
    condition1 = *condition9.get();
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr21 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.MapInsert"), "poc.MapInsert");
    return hstd::ext::unidata::VerifyResult::Error(*expr21.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapReplace(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::MapReplace);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::UniMap<ud::Str, ud::int64_t> const& expr5 = expr0.Field(&expr0.get()->mapping, "mapping");
    ud::Str const& expr6 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("a"), "a");
    ud::int64_t const& expr7 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(9), "9");
    ud::UniMap<ud::Str, ud::int64_t> const& expr8 = hstd::ext::unidata::eval_map_insert<hstd::UnorderedMap<hstd::ext::unidata::Str, hstd::ext::unidata::int64_t>>(expr5, expr6, expr7);
    auto condition9 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(true, "true");
    if (*condition9.get()) {
      ud::int64_t const& expr10 = hstd::ext::unidata::eval_map_size<hstd::ext::unidata::int64_t>(expr8);
      ud::UniMap<ud::Str, ud::int64_t> const& expr11 = expr0.Field(&expr0.get()->mapping, "mapping");
      ud::int64_t const& expr12 = hstd::ext::unidata::eval_map_size<hstd::ext::unidata::int64_t>(expr11);
      ud::bool const& expr13 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr10, expr12);
      condition9 = expr13;
    }
    if (*condition9.get()) {
      ud::Str const& expr14 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("a"), "a");
      ud::int64_t const& expr15 = hstd::ext::unidata::eval_map_get<hstd::ext::unidata::int64_t>(expr8, expr14);
      ud::int64_t const& expr16 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(9), "9");
      ud::bool const& expr17 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr15, expr16);
      condition9 = expr17;
    }
    if (*condition9.get()) {
      ud::UniMap<ud::Str, ud::int64_t> const& expr18 = expr0.Field(&expr0.get()->mapping, "mapping");
      ud::Str const& expr19 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("a"), "a");
      ud::int64_t const& expr20 = hstd::ext::unidata::eval_map_get<hstd::ext::unidata::int64_t>(expr18, expr19);
      ud::int64_t const& expr21 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(1), "1");
      ud::bool const& expr22 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr20, expr21);
      condition9 = expr22;
    }
    condition1 = *condition9.get();
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr23 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.MapReplace"), "poc.MapReplace");
    return hstd::ext::unidata::VerifyResult::Error(*expr23.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapKeys(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::MapKeys);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::UniMap<ud::Str, ud::int64_t> const& expr5 = expr0.Field(&expr0.get()->mapping, "mapping");
    ud::UniVec<ud::Str> const& expr6 = hstd::ext::unidata::eval_map_keys<hstd::Vec<hstd::ext::unidata::Str>>(expr5);
    auto condition7 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(true, "true");
    if (*condition7.get()) {
      ud::int64_t const& expr8 = hstd::ext::unidata::eval_list_size<hstd::ext::unidata::int64_t>(expr6);
      ud::int64_t const& expr9 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(2), "2");
      ud::bool const& expr10 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr8, expr9);
      condition7 = expr10;
    }
    if (*condition7.get()) {
      ud::Str const& expr11 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("a"), "a");
      ud::bool const& expr12 = hstd::ext::unidata::eval_list_contains<hstd::ext::unidata::bool>(expr6, expr11);
      condition7 = expr12;
    }
    if (*condition7.get()) {
      ud::Str const& expr13 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("b"), "b");
      ud::bool const& expr14 = hstd::ext::unidata::eval_list_contains<hstd::ext::unidata::bool>(expr6, expr13);
      condition7 = expr14;
    }
    condition1 = *condition7.get();
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr15 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.MapKeys"), "poc.MapKeys");
    return hstd::ext::unidata::VerifyResult::Error(*expr15.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapValues(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::MapValues);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::UniMap<ud::Str, ud::int64_t> const& expr5 = expr0.Field(&expr0.get()->mapping, "mapping");
    ud::UniVec<ud::int64_t> const& expr6 = hstd::ext::unidata::eval_map_values<hstd::Vec<hstd::ext::unidata::int64_t>>(expr5);
    auto condition7 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(true, "true");
    if (*condition7.get()) {
      ud::int64_t const& expr8 = hstd::ext::unidata::eval_list_size<hstd::ext::unidata::int64_t>(expr6);
      ud::int64_t const& expr9 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(2), "2");
      ud::bool const& expr10 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr8, expr9);
      condition7 = expr10;
    }
    if (*condition7.get()) {
      ud::int64_t const& expr11 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(1), "1");
      ud::bool const& expr12 = hstd::ext::unidata::eval_list_contains<hstd::ext::unidata::bool>(expr6, expr11);
      condition7 = expr12;
    }
    if (*condition7.get()) {
      ud::int64_t const& expr13 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(2), "2");
      ud::bool const& expr14 = hstd::ext::unidata::eval_list_contains<hstd::ext::unidata::bool>(expr6, expr13);
      condition7 = expr14;
    }
    condition1 = *condition7.get();
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr15 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.MapValues"), "poc.MapValues");
    return hstd::ext::unidata::VerifyResult::Error(*expr15.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapEmpty(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::MapEmpty);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::UniMap<ud::Str, ud::int64_t> const& expr5 = hstd::ext::unidata::eval_map_empty<hstd::UnorderedMap<hstd::ext::unidata::Str, hstd::ext::unidata::int64_t>>();
    ud::int64_t const& expr6 = hstd::ext::unidata::eval_map_size<hstd::ext::unidata::int64_t>(expr5);
    ud::int64_t const& expr7 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
    ud::bool const& expr8 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr6, expr7);
    condition1 = expr8;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr9 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.MapEmpty"), "poc.MapEmpty");
    return hstd::ext::unidata::VerifyResult::Error(*expr9.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_OptHasValue(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::OptHasValue);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::UniOpt<ud::int64_t> const& expr5 = expr0.Field(&expr0.get()->optional, "optional");
    ud::bool const& expr6 = hstd::ext::unidata::eval_opt_has_value<hstd::ext::unidata::bool>(expr5);
    condition1 = expr6;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr7 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.OptHasValue"), "poc.OptHasValue");
    return hstd::ext::unidata::VerifyResult::Error(*expr7.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_OptValue(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::OptValue);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    auto condition5 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(true, "true");
    if (*condition5.get()) {
      ud::UniOpt<ud::int64_t> const& expr6 = expr0.Field(&expr0.get()->optional, "optional");
      ud::bool const& expr7 = hstd::ext::unidata::eval_opt_has_value<hstd::ext::unidata::bool>(expr6);
      condition5 = expr7;
    }
    if (*condition5.get()) {
      ud::UniOpt<ud::int64_t> const& expr8 = expr0.Field(&expr0.get()->optional, "optional");
      ud::int64_t const& expr9 = hstd::ext::unidata::eval_opt_value<hstd::ext::unidata::int64_t>(expr8);
      ud::int64_t const& expr10 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(3), "3");
      ud::bool const& expr11 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr9, expr10);
      condition5 = expr11;
    }
    condition1 = *condition5.get();
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr12 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.OptValue"), "poc.OptValue");
    return hstd::ext::unidata::VerifyResult::Error(*expr12.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_CaseIs(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::CaseIs);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::Choice const& expr5 = expr0.Field(&expr0.get()->choice, "choice");
    ud::Data const& expr6 = expr5.Field(&expr5.get()->data, "data");
    ud::bool const& expr7 = std::holds_alternative<hstd::unidata_dsl::test::Choice::First>(expr6);
    condition1 = expr7;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr8 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.CaseIs"), "poc.CaseIs");
    return hstd::ext::unidata::VerifyResult::Error(*expr8.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_CaseWhich(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::CaseWhich);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::Choice const& expr5 = expr0.Field(&expr0.get()->choice, "choice");
    ud::Data const& expr6 = expr5.Field(&expr5.get()->data, "data");
    ud::Kind const& expr7 = static_cast<hstd::ext::unidata::Kind>(expr6.index());
    ud::bool const& expr8 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr7, hstd::unidata_dsl::test::Choice::Kind::First);
    condition1 = expr8;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr9 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.CaseWhich"), "poc.CaseWhich");
    return hstd::ext::unidata::VerifyResult::Error(*expr9.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_CaseField(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::CaseField);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::Choice const& expr5 = expr0.Field(&expr0.get()->choice, "choice");
    ud::Data const& expr6 = expr5.Field(&expr5.get()->data, "data");
    ud::bool const& expr7 = std::holds_alternative<hstd::unidata_dsl::test::Choice::First>(expr6);
    std::optional<hstd::ext::unidata::int64_t> result12 = std::nullopt;
    if (expr7) {
      ud::Choice const& expr8 = expr0.Field(&expr0.get()->choice, "choice");
      ud::Data const& expr9 = expr8.Field(&expr8.get()->data, "data");
      ud::int64_t const& expr10 = hstd::ext::unidata::eval_get_field<hstd::ext::unidata::int64_t>(expr9, "value");
      result12.emplace(expr10);
    } else {
      ud::int64_t const& expr11 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(-1), "-1");
      result12.emplace(expr11);
    }
    ud::int64_t const& expr13 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(6), "6");
    ud::bool const& expr14 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(result12.value(), expr13);
    condition1 = expr14;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr15 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.CaseField"), "poc.CaseField");
    return hstd::ext::unidata::VerifyResult::Error(*expr15.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_EnumIs(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::EnumIs);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::Status const& expr5 = expr0.Field(&expr0.get()->status, "status");
    ud::bool const& expr6 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr5, hstd::unidata_dsl::test::Status::Ready);
    condition1 = expr6;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr7 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.EnumIs"), "poc.EnumIs");
    return hstd::ext::unidata::VerifyResult::Error(*expr7.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_NthGet(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::NthGet);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    auto condition5 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(true, "true");
    if (*condition5.get()) {
      ud::UniTuple<ud::int64_t, ud::Str> const& expr6 = expr0.Field(&expr0.get()->coords, "coords");
      ud::int64_t const& expr7 = hstd::ext::unidata::eval_nth_get<0>(expr6);
      ud::int64_t const& expr8 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(6), "6");
      ud::bool const& expr9 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr7, expr8);
      condition5 = expr9;
    }
    if (*condition5.get()) {
      ud::UniTuple<ud::int64_t, ud::Str> const& expr10 = expr0.Field(&expr0.get()->coords, "coords");
      ud::Str const& expr11 = hstd::ext::unidata::eval_nth_get<1>(expr10);
      ud::Str const& expr12 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("six"), "six");
      ud::bool const& expr13 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr11, expr12);
      condition5 = expr13;
    }
    condition1 = *condition5.get();
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr14 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.NthGet"), "poc.NthGet");
    return hstd::ext::unidata::VerifyResult::Error(*expr14.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_IsDerived(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::IsDerived);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    auto condition5 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(true, "true");
    if (*condition5.get()) {
      ud::Derived const& expr6 = expr0.Field(&expr0.get()->derived, "derived");
      ud::bool const& expr7 = hstd::ext::unidata::eval_is_derived<hstd::ext::unidata::Base>(expr6);
      condition5 = expr7;
    }
    if (*condition5.get()) {
      ud::Base const& expr8 = expr0.Field(&expr0.get()->base, "base");
      ud::bool const& expr9 = hstd::ext::unidata::eval_is_derived<hstd::ext::unidata::Derived>(expr8);
      ud::bool const& expr10 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr9));
      condition5 = expr10;
    }
    condition1 = *condition5.get();
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr11 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.IsDerived"), "poc.IsDerived");
    return hstd::ext::unidata::VerifyResult::Error(*expr11.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_TypeCond(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::TypeCond);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::Derived const& expr5 = expr0.Field(&expr0.get()->derived, "derived");
    ud::UniVec<ud::DynamicT> const& expr6 = hstd::ext::unidata::eval_walk(expression_runtime, expr5);
    ud::int64_t const& expr7 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
    ud::DynamicT const& expr8 = hstd::ext::unidata::eval_list_at<hstd::ext::unidata::EvalDynamic>(expr6, expr7);
    std::optional<hstd::ext::unidata::int64_t> result9 = std::nullopt;
    if (!(result9.has_value())) {
      auto const* candidate10 = expression_runtime.try_as<hstd::ext::unidata::Base>(expr8);
      if (candidate10 != nullptr) {
        ud::int64_t const& expr11 = (*candidate10).Field(&(*candidate10).get()->id, "id");
        result9.emplace(expr11);
      }
    }
    if (!(result9.has_value())) {
      auto const* candidate12 = expression_runtime.try_as<hstd::ext::unidata::Derived>(expr8);
      if (candidate12 != nullptr) {
        ud::int64_t const& expr13 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(-1), "-1");
        result9.emplace(expr13);
      }
    }
    if (!(result9.has_value())) {
      throw std::runtime_error{"No type case matched at hstd_test_model.py:504; expected one of: Base, Derived"};
    }
    ud::int64_t const& expr14 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(6), "6");
    ud::bool const& expr15 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(result9.value(), expr14);
    condition1 = expr15;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr16 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.TypeCond"), "poc.TypeCond");
    return hstd::ext::unidata::VerifyResult::Error(*expr16.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_TypeCondOptional(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::TypeCondOptional);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    auto condition5 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(true, "true");
    if (*condition5.get()) {
      ud::Base const& expr6 = expr0.Field(&expr0.get()->base, "base");
      ud::UniVec<ud::DynamicT> const& expr7 = hstd::ext::unidata::eval_walk(expression_runtime, expr6);
      ud::int64_t const& expr8 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
      ud::DynamicT const& expr9 = hstd::ext::unidata::eval_list_at<hstd::ext::unidata::EvalDynamic>(expr7, expr8);
      std::optional<hstd::ext::unidata::int64_t> result10 = std::nullopt;
      if (!(result10.has_value())) {
        auto const* candidate11 = expression_runtime.try_as<hstd::ext::unidata::Derived>(expr9);
        if (candidate11 != nullptr) {
          ud::int64_t const& expr12 = (*candidate11).Field(&(*candidate11).get()->id, "id");
          result10.emplace(expr12);
        }
      }
      ud::bool const& expr13 = hstd::ext::unidata::eval_opt_has_value<hstd::ext::unidata::bool>(result10);
      ud::bool const& expr14 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr13));
      condition5 = expr14;
    }
    if (*condition5.get()) {
      ud::Derived const& expr15 = expr0.Field(&expr0.get()->derived, "derived");
      ud::UniVec<ud::DynamicT> const& expr16 = hstd::ext::unidata::eval_walk(expression_runtime, expr15);
      ud::int64_t const& expr17 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
      ud::DynamicT const& expr18 = hstd::ext::unidata::eval_list_at<hstd::ext::unidata::EvalDynamic>(expr16, expr17);
      std::optional<hstd::ext::unidata::int64_t> result19 = std::nullopt;
      if (!(result19.has_value())) {
        auto const* candidate20 = expression_runtime.try_as<hstd::ext::unidata::Derived>(expr18);
        if (candidate20 != nullptr) {
          ud::int64_t const& expr21 = (*candidate20).Field(&(*candidate20).get()->id, "id");
          result19.emplace(expr21);
        }
      }
      ud::int64_t const& expr22 = hstd::ext::unidata::eval_opt_value<hstd::ext::unidata::int64_t>(result19);
      ud::int64_t const& expr23 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(6), "6");
      ud::bool const& expr24 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr22, expr23);
      condition5 = expr24;
    }
    condition1 = *condition5.get();
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr25 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.TypeCondOptional"), "poc.TypeCondOptional");
    return hstd::ext::unidata::VerifyResult::Error(*expr25.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_TypeOf(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::TypeOf);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    ud::Derived const& expr5 = expr0.Field(&expr0.get()->derived, "derived");
    ud::UniVec<ud::DynamicT> const& expr6 = hstd::ext::unidata::eval_walk(expression_runtime, expr5);
    ud::int64_t const& expr7 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
    ud::DynamicT const& expr8 = hstd::ext::unidata::eval_list_at<hstd::ext::unidata::EvalDynamic>(expr6, expr7);
    std::optional<hstd::ext::unidata::Str> result9 = std::nullopt;
    if (!(result9.has_value())) {
      auto const* candidate10 = expression_runtime.try_as<hstd::ext::unidata::Base>(expr8);
      if (candidate10 != nullptr) {
        ud::Str const& expr11 = hstd::ext::unidata::eval_type_of<hstd::ext::unidata::Str>((*candidate10));
        result9.emplace(expr11);
      }
    }
    if (!(result9.has_value())) {
      throw std::runtime_error{"No type case matched at hstd_test_model.py:545; expected one of: Base"};
    }
    ud::Str const& expr12 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("Derived"), "Derived");
    ud::bool const& expr13 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(result9.value(), expr12);
    condition1 = expr13;
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr14 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.TypeOf"), "poc.TypeOf");
    return hstd::ext::unidata::VerifyResult::Error(*expr14.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_PathOf(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::PathOf);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    auto condition5 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(true, "true");
    if (*condition5.get()) {
      ud::int64_t const& expr6 = expr0.Field(&expr0.get()->number, "number");
      ud::UniPath const& expr7 = hstd::ext::unidata::eval_path_of<hstd::ext::unidata::UniPath>(expr6);
      ud::Str const& expr8 = hstd::ext::unidata::eval_str_format(hstd::ext::unidata::eval_str_pattern("%s"), expr7);
      ud::Str const& expr9 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("/number"), "/number");
      ud::bool const& expr10 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr8, expr9);
      condition5 = expr10;
    }
    if (*condition5.get()) {
      ud::UniVec<ud::int64_t> const& expr11 = expr0.Field(&expr0.get()->numbers, "numbers");
      auto callback15 = [&](auto const& item12) {
                        ud::UniPath const& expr13 = hstd::ext::unidata::eval_path_of<hstd::ext::unidata::UniPath>(item12);
                        ud::Str const& expr14 = hstd::ext::unidata::eval_str_format(hstd::ext::unidata::eval_str_pattern("%s"), expr13);
                        return expr14;
                        };
      ud::UniVec<ud::Str> const& expr16 = hstd::ext::unidata::eval_map<hstd::ext::unidata::Str>(expr11, callback15);
      ud::int64_t const& expr17 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
      ud::Str const& expr18 = hstd::ext::unidata::eval_list_at<hstd::ext::unidata::Str>(expr16, expr17);
      ud::Str const& expr19 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("/numbers/0"), "/numbers/0");
      ud::bool const& expr20 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr18, expr19);
      condition5 = expr20;
    }
    if (*condition5.get()) {
      ud::Derived const& expr21 = expr0.Field(&expr0.get()->derived, "derived");
      ud::UniVec<ud::DynamicT> const& expr22 = hstd::ext::unidata::eval_walk(expression_runtime, expr21);
      ud::int64_t const& expr23 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
      ud::DynamicT const& expr24 = hstd::ext::unidata::eval_list_at<hstd::ext::unidata::EvalDynamic>(expr22, expr23);
      std::optional<hstd::ext::unidata::Str> result25 = std::nullopt;
      if (!(result25.has_value())) {
        auto const* candidate26 = expression_runtime.try_as<hstd::ext::unidata::Base>(expr24);
        if (candidate26 != nullptr) {
          ud::UniPath const& expr27 = hstd::ext::unidata::eval_path_of<hstd::ext::unidata::UniPath>((*candidate26));
          ud::Str const& expr28 = hstd::ext::unidata::eval_str_format(hstd::ext::unidata::eval_str_pattern("%s"), expr27);
          result25.emplace(expr28);
        }
      }
      if (!(result25.has_value())) {
        throw std::runtime_error{"No type case matched at hstd_test_model.py:565; expected one of: Base"};
      }
      ud::Str const& expr29 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("/derived"), "/derived");
      ud::bool const& expr30 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(result25.value(), expr29);
      condition5 = expr30;
    }
    condition1 = *condition5.get();
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr31 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.PathOf"), "poc.PathOf");
    return hstd::ext::unidata::VerifyResult::Error(*expr31.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_EmptyCollections(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::OperationChecks>>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(false, "false");
  if (!(*condition1.get())) {
    ud::CheckKind const& expr2 = expr0.Field(&expr0.get()->operation, "operation");
    ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr2, hstd::unidata_dsl::test::CheckKind::EmptyCollections);
    ud::bool const& expr4 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr3));
    condition1 = expr4;
  }
  if (!(*condition1.get())) {
    auto condition5 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(true, "true");
    if (*condition5.get()) {
      ud::UniVec<ud::int64_t> const& expr6 = hstd::ext::unidata::eval_list_empty<hstd::Vec<hstd::ext::unidata::int64_t>>();
      auto callback10 = [&](auto const& item7) {
                        ud::int64_t const& expr8 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
                        ud::bool const& expr9 = hstd::ext::unidata::eval_lt<hstd::ext::unidata::bool>(expr8, item7);
                        return expr9;
                        };
      ud::bool const& expr11 = hstd::ext::unidata::eval_all(expr6, callback10);
      condition5 = expr11;
    }
    if (*condition5.get()) {
      ud::UniVec<ud::int64_t> const& expr12 = hstd::ext::unidata::eval_list_empty<hstd::Vec<hstd::ext::unidata::int64_t>>();
      auto callback16 = [&](auto const& item13) {
                        ud::int64_t const& expr14 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
                        ud::bool const& expr15 = hstd::ext::unidata::eval_lt<hstd::ext::unidata::bool>(expr14, item13);
                        return expr15;
                        };
      ud::bool const& expr17 = hstd::ext::unidata::eval_exists(expr12, callback16);
      ud::bool const& expr18 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr17));
      condition5 = expr18;
    }
    if (*condition5.get()) {
      ud::UniVec<ud::int64_t> const& expr19 = hstd::ext::unidata::eval_list_empty<hstd::Vec<hstd::ext::unidata::int64_t>>();
      auto callback23 = [&](auto const& item20) {
                        ud::int64_t const& expr21 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
                        ud::bool const& expr22 = hstd::ext::unidata::eval_lt<hstd::ext::unidata::bool>(expr21, item20);
                        return expr22;
                        };
      ud::bool const& expr24 = hstd::ext::unidata::eval_exists_one(expr19, callback23);
      ud::bool const& expr25 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((expr24));
      condition5 = expr25;
    }
    if (*condition5.get()) {
      ud::UniVec<ud::int64_t> const& expr26 = hstd::ext::unidata::eval_list_empty<hstd::Vec<hstd::ext::unidata::int64_t>>();
      ud::int64_t const& expr27 = hstd::ext::unidata::eval_sum<hstd::ext::unidata::int64_t>(expr26);
      ud::int64_t const& expr28 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
      ud::bool const& expr29 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr27, expr28);
      condition5 = expr29;
    }
    if (*condition5.get()) {
      ud::UniVec<ud::int64_t> const& expr30 = hstd::ext::unidata::eval_list_empty<hstd::Vec<hstd::ext::unidata::int64_t>>();
      auto callback35 = [&](auto const& item31) {
                        ud::UniMap<ud::Str, ud::int64_t> const& expr32 = expr0.Field(&expr0.get()->mapping, "mapping");
                        ud::Str const& expr33 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("absent"), "absent");
                        ud::int64_t const& expr34 = hstd::ext::unidata::eval_map_get<hstd::ext::unidata::int64_t>(expr32, expr33);
                        return expr34;
                        };
      ud::UniVec<ud::int64_t> const& expr36 = hstd::ext::unidata::eval_map<hstd::ext::unidata::int64_t>(expr30, callback35);
      ud::int64_t const& expr37 = hstd::ext::unidata::eval_list_size<hstd::ext::unidata::int64_t>(expr36);
      ud::int64_t const& expr38 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
      ud::bool const& expr39 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr37, expr38);
      condition5 = expr39;
    }
    if (*condition5.get()) {
      ud::UniVec<ud::int64_t> const& expr40 = hstd::ext::unidata::eval_list_empty<hstd::Vec<hstd::ext::unidata::int64_t>>();
      auto callback46 = [&](auto const& item41) {
                        ud::UniOpt<ud::int64_t> const& expr42 = expr0.Field(&expr0.get()->optional, "optional");
                        ud::int64_t const& expr43 = hstd::ext::unidata::eval_opt_value<hstd::ext::unidata::int64_t>(expr42);
                        ud::int64_t const& expr44 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
                        ud::bool const& expr45 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr43, expr44);
                        return expr45;
                        };
      ud::UniVec<ud::int64_t> const& expr47 = hstd::ext::unidata::eval_filter<hstd::ext::unidata::int64_t>(expr40, callback46);
      ud::int64_t const& expr48 = hstd::ext::unidata::eval_list_size<hstd::ext::unidata::int64_t>(expr47);
      ud::int64_t const& expr49 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
      ud::bool const& expr50 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr48, expr49);
      condition5 = expr50;
    }
    if (*condition5.get()) {
      ud::UniVec<ud::int64_t> const& expr51 = hstd::ext::unidata::eval_list_empty<hstd::Vec<hstd::ext::unidata::int64_t>>();
      auto callback54 = [&](auto const& item52) {
                        ud::UniOpt<ud::int64_t> const& expr53 = expr0.Field(&expr0.get()->optional, "optional");
                        return expr53;
                        };
      ud::UniVec<ud::int64_t> const& expr55 = hstd::ext::unidata::eval_filter_map<hstd::Vec<hstd::ext::unidata::int64_t>>(expr51, callback54);
      ud::int64_t const& expr56 = hstd::ext::unidata::eval_list_size<hstd::ext::unidata::int64_t>(expr55);
      ud::int64_t const& expr57 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
      ud::bool const& expr58 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr56, expr57);
      condition5 = expr58;
    }
    if (*condition5.get()) {
      ud::UniVec<ud::int64_t> const& expr59 = hstd::ext::unidata::eval_list_empty<hstd::Vec<hstd::ext::unidata::int64_t>>();
      auto callback65 = [&](auto const& item60) {
                        ud::UniOpt<ud::int64_t> const& expr61 = expr0.Field(&expr0.get()->optional, "optional");
                        ud::int64_t const& expr62 = hstd::ext::unidata::eval_opt_value<hstd::ext::unidata::int64_t>(expr61);
                        ud::int64_t const& expr63 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
                        ud::bool const& expr64 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr62, expr63);
                        return expr64;
                        };
      ud::UniVec<ud::int64_t> const& expr66 = hstd::ext::unidata::eval_take_while<hstd::Vec<hstd::ext::unidata::int64_t>>(expr59, callback65);
      ud::int64_t const& expr67 = hstd::ext::unidata::eval_list_size<hstd::ext::unidata::int64_t>(expr66);
      ud::int64_t const& expr68 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
      ud::bool const& expr69 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr67, expr68);
      condition5 = expr69;
    }
    if (*condition5.get()) {
      ud::UniVec<ud::int64_t> const& expr70 = hstd::ext::unidata::eval_list_empty<hstd::Vec<hstd::ext::unidata::int64_t>>();
      auto callback75 = [&](auto const& item71) {
                        ud::UniMap<ud::Str, ud::int64_t> const& expr72 = expr0.Field(&expr0.get()->mapping, "mapping");
                        ud::Str const& expr73 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("absent"), "absent");
                        ud::int64_t const& expr74 = hstd::ext::unidata::eval_map_get<hstd::ext::unidata::int64_t>(expr72, expr73);
                        return expr74;
                        };
      ud::UniMap<ud::int64_t, ud::UniVec<ud::int64_t>> const& expr76 = hstd::ext::unidata::eval_group_by<hstd::UnorderedMap<hstd::ext::unidata::int64_t, hstd::Vec<hstd::ext::unidata::int64_t>>>(expr70, callback75);
      ud::int64_t const& expr77 = hstd::ext::unidata::eval_map_size<hstd::ext::unidata::int64_t>(expr76);
      ud::int64_t const& expr78 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
      ud::bool const& expr79 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr77, expr78);
      condition5 = expr79;
    }
    if (*condition5.get()) {
      ud::UniVec<ud::int64_t> const& expr80 = hstd::ext::unidata::eval_list_empty<hstd::Vec<hstd::ext::unidata::int64_t>>();
      ud::int64_t const& expr81 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(9), "9");
      auto callback82 = [&](auto const& item83, auto const& item84) {
                        ud::UniMap<ud::Str, ud::int64_t> const& expr85 = expr0.Field(&expr0.get()->mapping, "mapping");
                        ud::Str const& expr86 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("absent"), "absent");
                        ud::int64_t const& expr87 = hstd::ext::unidata::eval_map_get<hstd::ext::unidata::int64_t>(expr85, expr86);
                        return expr87;
                        };
      ud::int64_t const& expr88 = hstd::ext::unidata::eval_fold<hstd::ext::unidata::int64_t>(expr80, expr81, callback82);
      ud::int64_t const& expr89 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(9), "9");
      ud::bool const& expr90 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr88, expr89);
      condition5 = expr90;
    }
    if (*condition5.get()) {
      ud::UniVec<ud::int64_t> const& expr91 = hstd::ext::unidata::eval_list_empty<hstd::Vec<hstd::ext::unidata::int64_t>>();
      ud::UniVec<ud::int64_t> const& expr92 = hstd::ext::unidata::eval_list_empty<hstd::Vec<hstd::ext::unidata::int64_t>>();
      ud::UniVec<ud::int64_t> const& expr93 = hstd::ext::unidata::eval_list_concat<hstd::Vec<hstd::ext::unidata::int64_t>>(expr91, expr92);
      ud::int64_t const& expr94 = hstd::ext::unidata::eval_list_size<hstd::ext::unidata::int64_t>(expr93);
      ud::int64_t const& expr95 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
      ud::bool const& expr96 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr94, expr95);
      condition5 = expr96;
    }
    if (*condition5.get()) {
      ud::bool const& expr97 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::bool>>::FromConst(static_cast<hstd::ext::unidata::bool>(true), "true");
      std::optional<hstd::ext::unidata::int64_t> result101 = std::nullopt;
      if (expr97) {
        ud::int64_t const& expr98 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(42), "42");
        result101.emplace(expr98);
      } else {
        ud::UniVec<ud::int64_t> const& expr99 = hstd::ext::unidata::eval_list_empty<hstd::Vec<hstd::ext::unidata::int64_t>>();
        ud::int64_t const& expr100 = hstd::ext::unidata::eval_min<hstd::ext::unidata::int64_t>(expr99);
        result101.emplace(expr100);
      }
      ud::int64_t const& expr102 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(42), "42");
      ud::bool const& expr103 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(result101.value(), expr102);
      condition5 = expr103;
    }
    if (*condition5.get()) {
      ud::bool const& expr104 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::bool>>::FromConst(static_cast<hstd::ext::unidata::bool>(true), "true");
      std::optional<hstd::ext::unidata::int64_t> result108 = std::nullopt;
      if (expr104) {
        ud::int64_t const& expr105 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(42), "42");
        result108.emplace(expr105);
      } else {
        ud::UniVec<ud::int64_t> const& expr106 = hstd::ext::unidata::eval_list_empty<hstd::Vec<hstd::ext::unidata::int64_t>>();
        ud::int64_t const& expr107 = hstd::ext::unidata::eval_max<hstd::ext::unidata::int64_t>(expr106);
        result108.emplace(expr107);
      }
      ud::int64_t const& expr109 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(42), "42");
      ud::bool const& expr110 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(result108.value(), expr109);
      condition5 = expr110;
    }
    condition1 = *condition5.get();
  }
  if (*condition1.get()) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr111 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("poc.EmptyCollections"), "poc.EmptyCollections");
    return hstd::ext::unidata::VerifyResult::Error(*expr111.get());
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
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::FieldChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // lt typed_as='bool'
  //     const_int typed_as='int64' int_val=0
  //     str_size typed_as='int64'
  //         this typed_as='string'
  //
  auto const& expr0 = (this_obj.Field(&this_obj.get()->text, "text"));
  ud::int64_t const& expr1 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
  ud::int64_t const& expr2 = hstd::ext::unidata::eval_str_size<hstd::ext::unidata::int64_t>(expr0);
  ud::bool const& expr3 = hstd::ext::unidata::eval_lt<hstd::ext::unidata::bool>(expr1, expr2);
  if (expr3) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::int64_t const& expr4 = hstd::ext::unidata::eval_str_size<hstd::ext::unidata::int64_t>(expr0);
    ud::Str const& expr5 = hstd::ext::unidata::eval_str_format(hstd::ext::unidata::eval_str_pattern("text length is %d"), expr4);
    return hstd::ext::unidata::VerifyResult::Error(*expr5.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::FieldChecks::__check_numbers_numbers_check(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::FieldChecks const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::FieldChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // all typed_as='bool' binders=('number',)
  //     this typed_as='list<int64>'
  //     lt typed_as='bool'
  //         const_int typed_as='int64' int_val=0
  //         var typed_as='int64' str_val='number'
  //
  auto const& expr0 = (this_obj.Field(&this_obj.get()->numbers, "numbers"));
  auto callback4 = [&](auto const& item1) {
                   ud::int64_t const& expr2 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(0), "0");
                   ud::bool const& expr3 = hstd::ext::unidata::eval_lt<hstd::ext::unidata::bool>(expr2, item1);
                   return expr3;
                   };
  ud::bool const& expr5 = hstd::ext::unidata::eval_all(expr0, callback4);
  if (expr5) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::Str const& expr6 = hstd::ext::unidata::eval_str_format(hstd::ext::unidata::eval_str_pattern("values=%s"), expr0);
    return hstd::ext::unidata::VerifyResult::Error(*expr6.get());
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
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::MessageChecks>>::RootValue(this_obj_ptr, ctx->getPath());
  // eq typed_as='bool'
  //     get_field typed_as='int64' str_val='number'
  //         this typed_as='MessageChecks'
  //     const_int typed_as='int64' int_val=6
  //
  auto const& expr0 = (this_obj);
  ud::int64_t const& expr1 = expr0.Field(&expr0.get()->number, "number");
  ud::int64_t const& expr2 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(6), "6");
  ud::bool const& expr3 = hstd::ext::unidata::eval_eq<hstd::ext::unidata::bool>(expr1, expr2);
  if (expr3) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::int64_t const& expr4 = expr0.Field(&expr0.get()->number, "number");
    ud::double const& expr5 = expr0.Field(&expr0.get()->real, "real");
    ud::double const& expr6 = expr0.Field(&expr0.get()->real, "real");
    ud::int64_t const& expr7 = expr0.Field(&expr0.get()->number, "number");
    ud::int64_t const& expr8 = expr0.Field(&expr0.get()->number, "number");
    ud::bool const& expr9 = expr0.Field(&expr0.get()->flag, "flag");
    ud::Str const& expr10 = expr0.Field(&expr0.get()->text, "text");
    ud::UniVec<ud::int64_t> const& expr11 = expr0.Field(&expr0.get()->numbers, "numbers");
    ud::UniMap<ud::Str, ud::int64_t> const& expr12 = expr0.Field(&expr0.get()->details, "details");
    ud::Str const& expr13 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::Str>>::FromConst(static_cast<hstd::ext::unidata::Str>("detail"), "detail");
    ud::int64_t const& expr14 = hstd::ext::unidata::eval_map_get<hstd::ext::unidata::int64_t>(expr12, expr13);
    ud::Str const& expr15 = hstd::ext::unidata::eval_str_format(hstd::ext::unidata::eval_str_pattern("n=%d real=%f sci=%e hex=%x oct=%o flag=%b text=%s list=%s lookup=%d %%"), expr4, expr5, expr6, expr7, expr8, expr9, expr10, expr11, expr14);
    return hstd::ext::unidata::VerifyResult::Error(*expr15.get());
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
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::Graph>>::RootValue(this_obj_ptr, ctx->getPath());
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
  ud::UniVec<ud::DynamicT> const& expr1 = hstd::ext::unidata::eval_walk(expression_runtime, expr0);
  auto callback5 = [&](auto const& item2) {
                   std::optional<hstd::ext::unidata::Node> result3 = std::nullopt;
                   if (!(result3.has_value())) {
                     auto const* candidate4 = expression_runtime.try_as<hstd::ext::unidata::Node>(item2);
                     if (candidate4 != nullptr) {
                       result3.emplace((*candidate4));
                     }
                   }
                   return result3;
                   };
  ud::UniVec<ud::Node> const& expr6 = hstd::ext::unidata::eval_filter_map<hstd::Vec<hstd::ext::unidata::Node>>(expr1, callback5);
  auto callback9 = [&](auto const& item7) {
                   ud::Str const& expr8 = item7.Field(&item7.get()->id, "id");
                   return expr8;
                   };
  ud::UniMap<ud::Str, ud::UniVec<ud::Node>> const& expr10 = hstd::ext::unidata::eval_group_by<hstd::UnorderedMap<hstd::ext::unidata::Str, hstd::Vec<hstd::ext::unidata::Node>>>(expr6, callback9);
  ud::UniVec<ud::UniVec<ud::Node>> const& expr11 = hstd::ext::unidata::eval_map_values<hstd::Vec<hstd::Vec<hstd::ext::unidata::Node>>>(expr10);
  auto callback16 = [&](auto const& item12) {
                    ud::int64_t const& expr13 = hstd::ext::unidata::eval_list_size<hstd::ext::unidata::int64_t>(item12);
                    ud::int64_t const& expr14 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(1), "1");
                    ud::bool const& expr15 = hstd::ext::unidata::eval_le<hstd::ext::unidata::bool>(expr13, expr14);
                    return expr15;
                    };
  ud::bool const& expr17 = hstd::ext::unidata::eval_all(expr11, callback16);
  if (expr17) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::UniVec<ud::DynamicT> const& expr18 = hstd::ext::unidata::eval_walk(expression_runtime, expr0);
    auto callback22 = [&](auto const& item19) {
                      std::optional<hstd::ext::unidata::Node> result20 = std::nullopt;
                      if (!(result20.has_value())) {
                        auto const* candidate21 = expression_runtime.try_as<hstd::ext::unidata::Node>(item19);
                        if (candidate21 != nullptr) {
                          result20.emplace((*candidate21));
                        }
                      }
                      return result20;
                      };
    ud::UniVec<ud::Node> const& expr23 = hstd::ext::unidata::eval_filter_map<hstd::Vec<hstd::ext::unidata::Node>>(expr18, callback22);
    auto callback26 = [&](auto const& item24) {
                      ud::Str const& expr25 = item24.Field(&item24.get()->id, "id");
                      return expr25;
                      };
    ud::UniMap<ud::Str, ud::UniVec<ud::Node>> const& expr27 = hstd::ext::unidata::eval_group_by<hstd::UnorderedMap<hstd::ext::unidata::Str, hstd::Vec<hstd::ext::unidata::Node>>>(expr23, callback26);
    ud::UniVec<ud::UniVec<ud::Node>> const& expr28 = hstd::ext::unidata::eval_map_values<hstd::Vec<hstd::Vec<hstd::ext::unidata::Node>>>(expr27);
    auto callback33 = [&](auto const& item29) {
                      ud::int64_t const& expr30 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::ext::unidata::int64_t>>::FromConst(static_cast<hstd::ext::unidata::int64_t>(1), "1");
                      ud::int64_t const& expr31 = hstd::ext::unidata::eval_list_size<hstd::ext::unidata::int64_t>(item29);
                      ud::bool const& expr32 = hstd::ext::unidata::eval_lt<hstd::ext::unidata::bool>(expr30, expr31);
                      return expr32;
                      };
    ud::UniVec<ud::UniVec<ud::Node>> const& expr34 = hstd::ext::unidata::eval_filter<hstd::Vec<hstd::ext::unidata::Node>>(expr28, callback33);
    auto callback40 = [&](auto const& item35) {
                      auto callback38 = [&](auto const& item36) {
                                        ud::UniPath const& expr37 = hstd::ext::unidata::eval_path_of<hstd::ext::unidata::UniPath>(item36);
                                        return expr37;
                                        };
                      ud::UniVec<ud::UniPath> const& expr39 = hstd::ext::unidata::eval_map<hstd::ext::unidata::UniPath>(item35, callback38);
                      return expr39;
                      };
    ud::UniVec<ud::UniVec<ud::UniPath>> const& expr41 = hstd::ext::unidata::eval_map<hstd::Vec<hstd::ext::unidata::UniPath>>(expr34, callback40);
    ud::Str const& expr42 = hstd::ext::unidata::eval_str_format(hstd::ext::unidata::eval_str_pattern("duplicate node ids at %s"), expr41);
    return hstd::ext::unidata::VerifyResult::Error(*expr42.get());
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::Graph::__check_record_graph_no_dangling_edges(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::Graph const*>(value);
  auto this_obj = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<hstd::unidata_dsl::test::Graph>>::RootValue(this_obj_ptr, ctx->getPath());
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
  ud::UniVec<ud::DynamicT> const& expr1 = hstd::ext::unidata::eval_walk(expression_runtime, expr0);
  auto callback5 = [&](auto const& item2) {
                   std::optional<hstd::ext::unidata::Node> result3 = std::nullopt;
                   if (!(result3.has_value())) {
                     auto const* candidate4 = expression_runtime.try_as<hstd::ext::unidata::Node>(item2);
                     if (candidate4 != nullptr) {
                       result3.emplace((*candidate4));
                     }
                   }
                   return result3;
                   };
  ud::UniVec<ud::Node> const& expr6 = hstd::ext::unidata::eval_filter_map<hstd::Vec<hstd::ext::unidata::Node>>(expr1, callback5);
  auto callback9 = [&](auto const& item7) {
                   ud::Str const& expr8 = item7.Field(&item7.get()->id, "id");
                   return expr8;
                   };
  ud::UniVec<ud::Str> const& expr10 = hstd::ext::unidata::eval_map<hstd::ext::unidata::Str>(expr6, callback9);
  ud::UniVec<ud::Edge> const& expr11 = expr0.Field(&expr0.get()->edges, "edges");
  auto callback18 = [&](auto const& item12) {
                    auto condition13 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(true, "true");
                    if (*condition13.get()) {
                      ud::Str const& expr14 = item12.Field(&item12.get()->source, "source");
                      ud::bool const& expr15 = hstd::ext::unidata::eval_list_contains<hstd::ext::unidata::bool>(expr10, expr14);
                      condition13 = expr15;
                    }
                    if (*condition13.get()) {
                      ud::Str const& expr16 = item12.Field(&item12.get()->target, "target");
                      ud::bool const& expr17 = hstd::ext::unidata::eval_list_contains<hstd::ext::unidata::bool>(expr10, expr16);
                      condition13 = expr17;
                    }
                    return *condition13.get();
                    };
  ud::bool const& expr19 = hstd::ext::unidata::eval_all(expr11, callback18);
  if (expr19) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    ud::UniVec<ud::DynamicT> const& expr20 = hstd::ext::unidata::eval_walk(expression_runtime, expr0);
    auto callback24 = [&](auto const& item21) {
                      std::optional<hstd::ext::unidata::Node> result22 = std::nullopt;
                      if (!(result22.has_value())) {
                        auto const* candidate23 = expression_runtime.try_as<hstd::ext::unidata::Node>(item21);
                        if (candidate23 != nullptr) {
                          result22.emplace((*candidate23));
                        }
                      }
                      return result22;
                      };
    ud::UniVec<ud::Node> const& expr25 = hstd::ext::unidata::eval_filter_map<hstd::Vec<hstd::ext::unidata::Node>>(expr20, callback24);
    auto callback28 = [&](auto const& item26) {
                      ud::Str const& expr27 = item26.Field(&item26.get()->id, "id");
                      return expr27;
                      };
    ud::UniVec<ud::Str> const& expr29 = hstd::ext::unidata::eval_map<hstd::ext::unidata::Str>(expr25, callback28);
    ud::UniVec<ud::Edge> const& expr30 = expr0.Field(&expr0.get()->edges, "edges");
    auto callback38 = [&](auto const& item31) {
                      auto condition32 = hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<bool>>::FromConst(true, "true");
                      if (*condition32.get()) {
                        ud::Str const& expr33 = item31.Field(&item31.get()->source, "source");
                        ud::bool const& expr34 = hstd::ext::unidata::eval_list_contains<hstd::ext::unidata::bool>(expr29, expr33);
                        condition32 = expr34;
                      }
                      if (*condition32.get()) {
                        ud::Str const& expr35 = item31.Field(&item31.get()->target, "target");
                        ud::bool const& expr36 = hstd::ext::unidata::eval_list_contains<hstd::ext::unidata::bool>(expr29, expr35);
                        condition32 = expr36;
                      }
                      ud::bool const& expr37 = hstd::ext::unidata::eval_not<hstd::ext::unidata::bool>((*condition32.get()));
                      return expr37;
                      };
    ud::UniVec<ud::Edge> const& expr39 = hstd::ext::unidata::eval_filter<hstd::ext::unidata::Edge>(expr30, callback38);
    auto callback42 = [&](auto const& item40) {
                      ud::UniPath const& expr41 = hstd::ext::unidata::eval_path_of<hstd::ext::unidata::UniPath>(item40);
                      return expr41;
                      };
    ud::UniVec<ud::UniPath> const& expr43 = hstd::ext::unidata::eval_map<hstd::ext::unidata::UniPath>(expr39, callback42);
    ud::Str const& expr44 = hstd::ext::unidata::eval_str_format(hstd::ext::unidata::eval_str_pattern("dangling edges at %s"), expr43);
    return hstd::ext::unidata::VerifyResult::Error(*expr44.get());
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