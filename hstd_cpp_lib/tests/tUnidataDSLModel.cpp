/* clang-format off */
#include "tUnidataDSLModel.hpp"
#include <hstd_cpp_lib/proto_serde/hstd_unidata_ops.hpp>
namespace ud = hstd::ext::unidata;


void hstd::unidata_dsl::test::TrivialText::__populate_expression_runtime(hstd::ext::unidata::EvalRuntime& expression_runtime) {
  expression_runtime.register_type<hstd::unidata_dsl::test::TrivialText>("TrivialText");
  expression_runtime.register_type<hstd::unidata_dsl::test::Base>("Base");
  expression_runtime.register_type<hstd::unidata_dsl::test::Derived>("Derived");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::First>("Choice::First");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::Second>("Choice::Second");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice>("Choice");
  expression_runtime.register_type<hstd::unidata_dsl::test::OperationChecks>("OperationChecks");
  expression_runtime.register_type<hstd::unidata_dsl::test::FieldChecks>("FieldChecks");
  expression_runtime.register_type<hstd::unidata_dsl::test::MessageChecks>("MessageChecks");
  expression_runtime.register_type<hstd::unidata_dsl::test::Node>("Node");
  expression_runtime.register_type<hstd::unidata_dsl::test::Edge>("Edge");
  expression_runtime.register_type<hstd::unidata_dsl::test::Graph>("Graph");
  expression_runtime.register_type<hstd::unidata_dsl::test::MultiValueCond>("MultiValueCond");
  expression_runtime.register_type<hstd::unidata_dsl::test::Status>("Status");
  expression_runtime.register_type<hstd::unidata_dsl::test::CheckKind>("CheckKind");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::Kind>("Choice::Kind");
  expression_runtime.register_base<hstd::unidata_dsl::test::Derived, hstd::unidata_dsl::test::Base>();
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::TrivialText::__check_text_text_check(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::TrivialText const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::TrivialText>::RootValue(this_obj_ptr, ctx->getPath());
  // lt typed_as='bool'
  //     const_int typed_as='int64' int_val=0
  //     str_size typed_as='int64'
  //         this typed_as='string'
  //
  auto const& expr0 = (this_obj.Field(&this_obj.get()->text, "text"));
  ud::S<int64_t> const& expr1 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
  ud::S<int64_t> const& expr2 = ud::eval_op<ud::OpId::STR_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 40), expr0);
  ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 40), expr1, expr2);
  if (ud::get_stored_value(expr3)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr4 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("text must not be empty"), "text must not be empty");
    return ud::VerifyResult::Error(ud::get_stored_value(expr4));
  }
}
hstd::ext::unidata::VerifyCheckCollection const* hstd::unidata_dsl::test::TrivialText::get_unidata_checks() {
  static hstd::ext::unidata::VerifyCheckCollection checks
   = {{{hstd::ext::unidata::VerifyKey{"TrivialText", "text"},
        hstd::ext::unidata::VerifyCbList{
        hstd::ext::unidata::VerifyCb{&__check_text_text_check}
        }}}};
  return &checks;
}
void hstd::unidata_dsl::test::Base::__populate_expression_runtime(hstd::ext::unidata::EvalRuntime& expression_runtime) {
  expression_runtime.register_type<hstd::unidata_dsl::test::TrivialText>("TrivialText");
  expression_runtime.register_type<hstd::unidata_dsl::test::Base>("Base");
  expression_runtime.register_type<hstd::unidata_dsl::test::Derived>("Derived");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::First>("Choice::First");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::Second>("Choice::Second");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice>("Choice");
  expression_runtime.register_type<hstd::unidata_dsl::test::OperationChecks>("OperationChecks");
  expression_runtime.register_type<hstd::unidata_dsl::test::FieldChecks>("FieldChecks");
  expression_runtime.register_type<hstd::unidata_dsl::test::MessageChecks>("MessageChecks");
  expression_runtime.register_type<hstd::unidata_dsl::test::Node>("Node");
  expression_runtime.register_type<hstd::unidata_dsl::test::Edge>("Edge");
  expression_runtime.register_type<hstd::unidata_dsl::test::Graph>("Graph");
  expression_runtime.register_type<hstd::unidata_dsl::test::MultiValueCond>("MultiValueCond");
  expression_runtime.register_type<hstd::unidata_dsl::test::Status>("Status");
  expression_runtime.register_type<hstd::unidata_dsl::test::CheckKind>("CheckKind");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::Kind>("Choice::Kind");
  expression_runtime.register_base<hstd::unidata_dsl::test::Derived, hstd::unidata_dsl::test::Base>();
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::Base::__check_record_base_positive_id(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::Base const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::Base>::RootValue(this_obj_ptr, ctx->getPath());
  // lt typed_as='bool'
  //     const_int typed_as='int64' int_val=0
  //     get_field typed_as='int64' str_val='id'
  //         this typed_as='Base'
  //
  auto const& expr0 = (this_obj);
  ud::S<int64_t> const& expr1 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
  ud::S<int64_t> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 118), expr0, "id");
  ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 118), expr1, expr2);
  if (ud::get_stored_value(expr3)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr4 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("base id must be positive"), "base id must be positive");
    return ud::VerifyResult::Error(ud::get_stored_value(expr4));
  }
}
hstd::ext::unidata::VerifyCheckCollection const* hstd::unidata_dsl::test::Base::get_unidata_checks() {
  static hstd::ext::unidata::VerifyCheckCollection checks
   = {{{hstd::ext::unidata::VerifyKey{"Base", std::nullopt},
        hstd::ext::unidata::VerifyCbList{
        hstd::ext::unidata::VerifyCb{&__check_record_base_positive_id}
        }}}};
  return &checks;
}
void hstd::unidata_dsl::test::Derived::__populate_expression_runtime(hstd::ext::unidata::EvalRuntime& expression_runtime) {
  expression_runtime.register_type<hstd::unidata_dsl::test::TrivialText>("TrivialText");
  expression_runtime.register_type<hstd::unidata_dsl::test::Base>("Base");
  expression_runtime.register_type<hstd::unidata_dsl::test::Derived>("Derived");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::First>("Choice::First");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::Second>("Choice::Second");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice>("Choice");
  expression_runtime.register_type<hstd::unidata_dsl::test::OperationChecks>("OperationChecks");
  expression_runtime.register_type<hstd::unidata_dsl::test::FieldChecks>("FieldChecks");
  expression_runtime.register_type<hstd::unidata_dsl::test::MessageChecks>("MessageChecks");
  expression_runtime.register_type<hstd::unidata_dsl::test::Node>("Node");
  expression_runtime.register_type<hstd::unidata_dsl::test::Edge>("Edge");
  expression_runtime.register_type<hstd::unidata_dsl::test::Graph>("Graph");
  expression_runtime.register_type<hstd::unidata_dsl::test::MultiValueCond>("MultiValueCond");
  expression_runtime.register_type<hstd::unidata_dsl::test::Status>("Status");
  expression_runtime.register_type<hstd::unidata_dsl::test::CheckKind>("CheckKind");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::Kind>("Choice::Kind");
  expression_runtime.register_base<hstd::unidata_dsl::test::Derived, hstd::unidata_dsl::test::Base>();
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::Derived::__check_record_derived_positive_weight(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::Derived const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::Derived>::RootValue(this_obj_ptr, ctx->getPath());
  // lt typed_as='bool'
  //     const_int typed_as='int64' int_val=0
  //     get_field typed_as='int64' str_val='weight'
  //         this typed_as='Derived'
  //
  auto const& expr0 = (this_obj);
  ud::S<int64_t> const& expr1 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
  ud::S<int64_t> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 128), expr0, "weight");
  ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 128), expr1, expr2);
  if (ud::get_stored_value(expr3)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr4 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("derived weight must be positive"), "derived weight must be positive");
    return ud::VerifyResult::Error(ud::get_stored_value(expr4));
  }
}
hstd::ext::unidata::VerifyCheckCollection const* hstd::unidata_dsl::test::Derived::get_unidata_checks() {
  static hstd::ext::unidata::VerifyCheckCollection checks
   = {{{hstd::ext::unidata::VerifyKey{"Derived", std::nullopt},
        hstd::ext::unidata::VerifyCbList{
        hstd::ext::unidata::VerifyCb{&__check_record_derived_positive_weight}
        }}}};
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
void hstd::unidata_dsl::test::OperationChecks::__populate_expression_runtime(hstd::ext::unidata::EvalRuntime& expression_runtime) {
  expression_runtime.register_type<hstd::unidata_dsl::test::TrivialText>("TrivialText");
  expression_runtime.register_type<hstd::unidata_dsl::test::Base>("Base");
  expression_runtime.register_type<hstd::unidata_dsl::test::Derived>("Derived");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::First>("Choice::First");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::Second>("Choice::Second");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice>("Choice");
  expression_runtime.register_type<hstd::unidata_dsl::test::OperationChecks>("OperationChecks");
  expression_runtime.register_type<hstd::unidata_dsl::test::FieldChecks>("FieldChecks");
  expression_runtime.register_type<hstd::unidata_dsl::test::MessageChecks>("MessageChecks");
  expression_runtime.register_type<hstd::unidata_dsl::test::Node>("Node");
  expression_runtime.register_type<hstd::unidata_dsl::test::Edge>("Edge");
  expression_runtime.register_type<hstd::unidata_dsl::test::Graph>("Graph");
  expression_runtime.register_type<hstd::unidata_dsl::test::MultiValueCond>("MultiValueCond");
  expression_runtime.register_type<hstd::unidata_dsl::test::Status>("Status");
  expression_runtime.register_type<hstd::unidata_dsl::test::CheckKind>("CheckKind");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::Kind>("Choice::Kind");
  expression_runtime.register_base<hstd::unidata_dsl::test::Derived, hstd::unidata_dsl::test::Base>();
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Eq(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::Eq);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 185, ud::OpId::EQ);
    ud::S<int64_t> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 185), expr0, "number");
    ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
    ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 185), expr5, expr6);
    ud::set_value(condition1, expr7);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr8 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.Eq"), "poc.Eq");
    return ud::VerifyResult::Error(ud::get_stored_value(expr8));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Ne(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::Ne);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 186, ud::OpId::NE);
    ud::S<int64_t> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 186), expr0, "number");
    ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(8), "8");
    ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::NE, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 186), expr5, expr6);
    ud::set_value(condition1, expr7);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr8 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.Ne"), "poc.Ne");
    return ud::VerifyResult::Error(ud::get_stored_value(expr8));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Lt(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::Lt);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 187, ud::OpId::LT);
    ud::S<int64_t> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 187), expr0, "number");
    ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(7), "7");
    ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 187), expr5, expr6);
    ud::set_value(condition1, expr7);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr8 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.Lt"), "poc.Lt");
    return ud::VerifyResult::Error(ud::get_stored_value(expr8));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Le(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::Le);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 188, ud::OpId::LE);
    ud::S<int64_t> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 188), expr0, "number");
    ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
    ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::LE, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 188), expr5, expr6);
    ud::set_value(condition1, expr7);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr8 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.Le"), "poc.Le");
    return ud::VerifyResult::Error(ud::get_stored_value(expr8));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Add(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::Add);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 189, ud::OpId::EQ);
    ud::S<int64_t> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 189), expr0, "number");
    ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
    ud::S<int64_t> const& expr7 = ud::eval_op<ud::OpId::ADD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 189), expr5, expr6);
    ud::S<int64_t> const& expr8 = ud::S<int64_t>::FromConst(static_cast<int64_t>(9), "9");
    ud::S<bool> const& expr9 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 189), expr7, expr8);
    ud::set_value(condition1, expr9);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr10 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.Add"), "poc.Add");
    return ud::VerifyResult::Error(ud::get_stored_value(expr10));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Sub(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::Sub);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 190, ud::OpId::EQ);
    ud::S<int64_t> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 190), expr0, "number");
    ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
    ud::S<int64_t> const& expr7 = ud::eval_op<ud::OpId::SUB, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 190), expr5, expr6);
    ud::S<int64_t> const& expr8 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
    ud::S<bool> const& expr9 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 190), expr7, expr8);
    ud::set_value(condition1, expr9);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr10 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.Sub"), "poc.Sub");
    return ud::VerifyResult::Error(ud::get_stored_value(expr10));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Mul(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::Mul);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 191, ud::OpId::EQ);
    ud::S<int64_t> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 191), expr0, "number");
    ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
    ud::S<int64_t> const& expr7 = ud::eval_op<ud::OpId::MUL, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 191), expr5, expr6);
    ud::S<int64_t> const& expr8 = ud::S<int64_t>::FromConst(static_cast<int64_t>(18), "18");
    ud::S<bool> const& expr9 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 191), expr7, expr8);
    ud::set_value(condition1, expr9);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr10 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.Mul"), "poc.Mul");
    return ud::VerifyResult::Error(ud::get_stored_value(expr10));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Div(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::Div);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 192, ud::OpId::EQ);
    ud::S<int64_t> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 192), expr0, "number");
    ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
    ud::S<int64_t> const& expr7 = ud::eval_op<ud::OpId::DIV, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 192), expr5, expr6);
    ud::S<int64_t> const& expr8 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
    ud::S<bool> const& expr9 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 192), expr7, expr8);
    ud::set_value(condition1, expr9);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr10 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.Div"), "poc.Div");
    return ud::VerifyResult::Error(ud::get_stored_value(expr10));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ConstFloat(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::ConstFloat);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 195, ud::OpId::AND);
    auto condition5 = ud::S<bool>::FromConst(true, "true");
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 196, ud::OpId::EQ);
      ud::S<double> const& expr6 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<double>>(ud::get_context(ctx, "hstd_test_model.py", 196), expr0, "real");
      ud::S<double> const& expr7 = ud::S<double>::FromConst(static_cast<double>(2.5), "2.5");
      ud::S<bool> const& expr8 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 196), expr6, expr7);
      ud::set_value(condition5, expr8);
    }
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 197, ud::OpId::EQ);
      ud::S<double> const& expr9 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<double>>(ud::get_context(ctx, "hstd_test_model.py", 197), expr0, "real");
      ud::S<double> const& expr10 = ud::S<double>::FromConst(static_cast<double>(2.0), "2.0");
      ud::S<double> const& expr11 = ud::eval_op<ud::OpId::DIV, ud::S<double>>(ud::get_context(ctx, "hstd_test_model.py", 197), expr9, expr10);
      ud::S<double> const& expr12 = ud::S<double>::FromConst(static_cast<double>(1.25), "1.25");
      ud::S<bool> const& expr13 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 197), expr11, expr12);
      ud::set_value(condition5, expr13);
    }
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 198, ud::OpId::EQ);
      ud::S<double> const& expr14 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<double>>(ud::get_context(ctx, "hstd_test_model.py", 198), expr0, "real");
      ud::S<double> const& expr15 = ud::S<double>::FromConst(static_cast<double>(2.0), "2.0");
      ud::S<double> const& expr16 = ud::eval_op<ud::OpId::MUL, ud::S<double>>(ud::get_context(ctx, "hstd_test_model.py", 198), expr14, expr15);
      ud::S<double> const& expr17 = ud::S<double>::FromConst(static_cast<double>(5.0), "5.0");
      ud::S<bool> const& expr18 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 198), expr16, expr17);
      ud::set_value(condition5, expr18);
    }
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 199, ud::OpId::EQ);
      ud::S<double> const& expr19 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<double>>(ud::get_context(ctx, "hstd_test_model.py", 199), expr0, "real");
      ud::S<double> const& expr20 = ud::S<double>::FromConst(static_cast<double>(0.5), "0.5");
      ud::S<double> const& expr21 = ud::eval_op<ud::OpId::SUB, ud::S<double>>(ud::get_context(ctx, "hstd_test_model.py", 199), expr19, expr20);
      ud::S<double> const& expr22 = ud::S<double>::FromConst(static_cast<double>(2.0), "2.0");
      ud::S<bool> const& expr23 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 199), expr21, expr22);
      ud::set_value(condition5, expr23);
    }
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 200, ud::OpId::EQ);
      ud::S<double> const& expr24 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<double>>(ud::get_context(ctx, "hstd_test_model.py", 200), expr0, "real");
      ud::S<double> const& expr25 = ud::S<double>::FromConst(static_cast<double>(0.5), "0.5");
      ud::S<double> const& expr26 = ud::eval_op<ud::OpId::ADD, ud::S<double>>(ud::get_context(ctx, "hstd_test_model.py", 200), expr24, expr25);
      ud::S<double> const& expr27 = ud::S<double>::FromConst(static_cast<double>(3.0), "3.0");
      ud::S<bool> const& expr28 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 200), expr26, expr27);
      ud::set_value(condition5, expr28);
    }
    ud::set_value(condition1, condition5);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr29 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.ConstFloat"), "poc.ConstFloat");
    return ud::VerifyResult::Error(ud::get_stored_value(expr29));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ConstBool(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::ConstBool);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 203, ud::OpId::EQ);
    ud::S<bool> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 203), expr0, "flag");
    ud::S<bool> const& expr6 = ud::S<bool>::FromConst(static_cast<bool>(true), "true");
    ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 203), expr5, expr6);
    ud::set_value(condition1, expr7);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr8 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.ConstBool"), "poc.ConstBool");
    return ud::VerifyResult::Error(ud::get_stored_value(expr8));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_And(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::And);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 206, ud::OpId::AND);
    auto condition5 = ud::S<bool>::FromConst(true, "true");
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 207, ud::OpId::GET_FIELD);
      ud::S<bool> const& expr6 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 207), expr0, "flag");
      ud::set_value(condition5, expr6);
    }
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 208, ud::OpId::EQ);
      ud::S<int64_t> const& expr7 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 208), expr0, "number");
      ud::S<int64_t> const& expr8 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
      ud::S<bool> const& expr9 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 208), expr7, expr8);
      ud::set_value(condition5, expr9);
    }
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 209, ud::OpId::EQ);
      ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr10 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 209), expr0, "mapping");
      ud::S<hstd::Str> const& expr11 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("a"), "a");
      ud::S<int64_t> const& expr12 = ud::eval_op<ud::OpId::MAP_GET, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 209), expr10, expr11);
      ud::S<int64_t> const& expr13 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
      ud::S<bool> const& expr14 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 209), expr12, expr13);
      ud::set_value(condition5, expr14);
    }
    ud::set_value(condition1, condition5);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr15 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.And"), "poc.And");
    return ud::VerifyResult::Error(ud::get_stored_value(expr15));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Or(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::Or);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 214, ud::OpId::OR);
    auto condition5 = ud::S<bool>::FromConst(false, "false");
    if (!(ud::get_stored_value(condition5))) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 214, ud::OpId::CONST_BOOL);
      ud::S<bool> const& expr6 = ud::S<bool>::FromConst(static_cast<bool>(false), "false");
      ud::set_value(condition5, expr6);
    }
    if (!(ud::get_stored_value(condition5))) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 214, ud::OpId::EQ);
      ud::S<int64_t> const& expr7 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 214), expr0, "number");
      ud::S<int64_t> const& expr8 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
      ud::S<bool> const& expr9 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 214), expr7, expr8);
      ud::set_value(condition5, expr9);
    }
    if (!(ud::get_stored_value(condition5))) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 214, ud::OpId::EQ);
      ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr10 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 214), expr0, "mapping");
      ud::S<hstd::Str> const& expr11 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("a"), "a");
      ud::S<int64_t> const& expr12 = ud::eval_op<ud::OpId::MAP_GET, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 214), expr10, expr11);
      ud::S<int64_t> const& expr13 = ud::S<int64_t>::FromConst(static_cast<int64_t>(99), "99");
      ud::S<bool> const& expr14 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 214), expr12, expr13);
      ud::set_value(condition5, expr14);
    }
    ud::set_value(condition1, condition5);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr15 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.Or"), "poc.Or");
    return ud::VerifyResult::Error(ud::get_stored_value(expr15));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Not(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::Not);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 216, ud::OpId::NOT);
    ud::S<int64_t> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 216), expr0, "number");
    ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
    ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::NE, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 216), expr5, expr6);
    ud::S<bool> const& expr8 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 216), (expr7));
    ud::set_value(condition1, expr8);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr9 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.Not"), "poc.Not");
    return ud::VerifyResult::Error(ud::get_stored_value(expr9));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Cond(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  //             str_format typed_as='string' str_val='other-{}'
  //                 get_field typed_as='int64' str_val='number'
  //                     this typed_as='OperationChecks'
  //         const_str typed_as='string' str_val='six'
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::Cond);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 219, ud::OpId::EQ);
    ud::S<int64_t> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 220), expr0, "number");
    ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
    ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 220), expr5, expr6);
    ud::S<ud::UniOpt<ud::S<hstd::Str>>> result11 = ud::S<ud::UniOpt<ud::S<hstd::Str>>>::FromConst(std::nullopt, "std::nullopt");
    if (ud::get_stored_value(expr7)) {
      ud::S<hstd::Str> const& expr8 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 220), expr0, "text");
      ud::set_value(result11, expr8);
    } else {
      ud::S<int64_t> const& expr9 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 221), expr0, "number");
      ud::S<hstd::Str> const& expr10 = ud::eval_op<ud::OpId::STR_FORMAT, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 221), eval_str_pattern("other-{}"), expr9);
      ud::set_value(result11, expr10);
    }
    ud::S<hstd::Str> const& expr12 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("six"), "six");
    ud::S<bool> const& expr13 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 219), ud::get_value_ref(result11), expr12);
    ud::set_value(condition1, expr13);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr14 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.Cond"), "poc.Cond");
    return ud::VerifyResult::Error(ud::get_stored_value(expr14));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_CondLazy(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::CondLazy);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 227, ud::OpId::EQ);
    ud::S<bool> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 228), expr0, "flag");
    ud::S<ud::UniOpt<ud::S<int64_t>>> result12 = ud::S<ud::UniOpt<ud::S<int64_t>>>::FromConst(std::nullopt, "std::nullopt");
    if (ud::get_stored_value(expr5)) {
      ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr6 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 228), expr0, "mapping");
      ud::S<hstd::Str> const& expr7 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("a"), "a");
      ud::S<int64_t> const& expr8 = ud::eval_op<ud::OpId::MAP_GET, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 228), expr6, expr7);
      ud::set_value(result12, expr8);
    } else {
      ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr9 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 229), expr0, "mapping");
      ud::S<hstd::Str> const& expr10 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("absent"), "absent");
      ud::S<int64_t> const& expr11 = ud::eval_op<ud::OpId::MAP_GET, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 229), expr9, expr10);
      ud::set_value(result12, expr11);
    }
    ud::S<int64_t> const& expr13 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
    ud::S<bool> const& expr14 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 227), ud::get_value_ref(result12), expr13);
    ud::set_value(condition1, expr14);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr15 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.CondLazy"), "poc.CondLazy");
    return ud::VerifyResult::Error(ud::get_stored_value(expr15));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Let(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='Let'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         let typed_as='int64' binders='bound'[int64]
  //             get_field typed_as='int64' str_val='number'
  //                 this typed_as='OperationChecks'
  //             let typed_as='int64' binders='bound2'[int64]
  //                 add typed_as='int64'
  //                     var typed_as='int64' str_val='bound'
  //                     const_int typed_as='int64' int_val=1
  //                 var typed_as='int64' str_val='bound2'
  //         const_int typed_as='int64' int_val=7
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::Let);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 235, ud::OpId::EQ);
    ud::S<int64_t> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 237), expr0, "number");
    ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
    ud::S<int64_t> const& expr7 = ud::eval_op<ud::OpId::ADD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 240), expr5, expr6);
    ud::S<int64_t> const& expr8 = ud::S<int64_t>::FromConst(static_cast<int64_t>(7), "7");
    ud::S<bool> const& expr9 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 235), expr7, expr8);
    ud::set_value(condition1, expr9);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr10 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.Let"), "poc.Let");
    return ud::VerifyResult::Error(ud::get_stored_value(expr10));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_All(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='All'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     all typed_as='bool' binders='number'[int64]
  //         get_field typed_as='list<int64>' str_val='numbers'
  //             this typed_as='OperationChecks'
  //         lt typed_as='bool'
  //             var typed_as='int64' str_val='number'
  //             const_int typed_as='int64' int_val=4
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::All);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 246, ud::OpId::ALL);
    ud::S<hstd::Vec<ud::S<int64_t>>> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 246), expr0, "numbers");
    auto callback9 = [&](ud::S<int64_t> const& item6) -> ud::S<bool> {
                     // lt typed_as='bool'
                     //     var typed_as='int64' str_val='number'
                     //     const_int typed_as='int64' int_val=4
                     //
                     ud::S<int64_t> const& expr7 = ud::S<int64_t>::FromConst(static_cast<int64_t>(4), "4");
                     ud::S<bool> const& expr8 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 246), item6, expr7);
                     return expr8;
                     };
    ud::S<bool> const& expr10 = ud::eval_op<ud::OpId::ALL, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 246), expr5, callback9);
    ud::set_value(condition1, expr10);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr11 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.All"), "poc.All");
    return ud::VerifyResult::Error(ud::get_stored_value(expr11));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Exists(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='Exists'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     exists typed_as='bool' binders='number'[int64]
  //         get_field typed_as='list<int64>' str_val='numbers'
  //             this typed_as='OperationChecks'
  //         eq typed_as='bool'
  //             var typed_as='int64' str_val='number'
  //             const_int typed_as='int64' int_val=3
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::Exists);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 247, ud::OpId::EXISTS);
    ud::S<hstd::Vec<ud::S<int64_t>>> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 247), expr0, "numbers");
    auto callback9 = [&](ud::S<int64_t> const& item6) -> ud::S<bool> {
                     // eq typed_as='bool'
                     //     var typed_as='int64' str_val='number'
                     //     const_int typed_as='int64' int_val=3
                     //
                     ud::S<int64_t> const& expr7 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
                     ud::S<bool> const& expr8 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 247), item6, expr7);
                     return expr8;
                     };
    ud::S<bool> const& expr10 = ud::eval_op<ud::OpId::EXISTS, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 247), expr5, callback9);
    ud::set_value(condition1, expr10);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr11 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.Exists"), "poc.Exists");
    return ud::VerifyResult::Error(ud::get_stored_value(expr11));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ExistsOne(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='ExistsOne'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     exists_one typed_as='bool' binders='number'[int64]
  //         get_field typed_as='list<int64>' str_val='numbers'
  //             this typed_as='OperationChecks'
  //         eq typed_as='bool'
  //             var typed_as='int64' str_val='number'
  //             const_int typed_as='int64' int_val=3
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::ExistsOne);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 248, ud::OpId::EXISTS_ONE);
    ud::S<hstd::Vec<ud::S<int64_t>>> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 248), expr0, "numbers");
    auto callback9 = [&](ud::S<int64_t> const& item6) -> ud::S<bool> {
                     // eq typed_as='bool'
                     //     var typed_as='int64' str_val='number'
                     //     const_int typed_as='int64' int_val=3
                     //
                     ud::S<int64_t> const& expr7 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
                     ud::S<bool> const& expr8 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 248), item6, expr7);
                     return expr8;
                     };
    ud::S<bool> const& expr10 = ud::eval_op<ud::OpId::EXISTS_ONE, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 248), expr5, callback9);
    ud::set_value(condition1, expr10);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr11 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.ExistsOne"), "poc.ExistsOne");
    return ud::VerifyResult::Error(ud::get_stored_value(expr11));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Map(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='Map'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         list_at typed_as='int64'
  //             map typed_as='list<int64>' binders='number'[int64]
  //                 get_field typed_as='list<int64>' str_val='numbers'
  //                     this typed_as='OperationChecks'
  //                 mul typed_as='int64'
  //                     var typed_as='int64' str_val='number'
  //                     const_int typed_as='int64' int_val=2
  //             const_int typed_as='int64' int_val=2
  //         const_int typed_as='int64' int_val=6
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::Map);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 251, ud::OpId::EQ);
    ud::S<hstd::Vec<ud::S<int64_t>>> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 251), expr0, "numbers");
    auto callback9 = [&](ud::S<int64_t> const& item6) -> ud::S<int64_t> {
                     // mul typed_as='int64'
                     //     var typed_as='int64' str_val='number'
                     //     const_int typed_as='int64' int_val=2
                     //
                     ud::S<int64_t> const& expr7 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
                     ud::S<int64_t> const& expr8 = ud::eval_op<ud::OpId::MUL, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 251), item6, expr7);
                     return expr8;
                     };
    ud::S<hstd::Vec<ud::S<int64_t>>> const& expr10 = ud::eval_op<ud::OpId::MAP, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 251), expr5, callback9);
    ud::S<int64_t> const& expr11 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
    ud::S<int64_t> const& expr12 = ud::eval_op<ud::OpId::LIST_AT, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 251), expr10, expr11);
    ud::S<int64_t> const& expr13 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
    ud::S<bool> const& expr14 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 251), expr12, expr13);
    ud::set_value(condition1, expr14);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr15 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.Map"), "poc.Map");
    return ud::VerifyResult::Error(ud::get_stored_value(expr15));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Filter(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='Filter'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         list_size typed_as='int64'
  //             filter typed_as='list<int64>' binders='number'[int64]
  //                 get_field typed_as='list<int64>' str_val='numbers'
  //                     this typed_as='OperationChecks'
  //                 lt typed_as='bool'
  //                     const_int typed_as='int64' int_val=1
  //                     var typed_as='int64' str_val='number'
  //         const_int typed_as='int64' int_val=2
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::Filter);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 255, ud::OpId::EQ);
    ud::S<hstd::Vec<ud::S<int64_t>>> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 255), expr0, "numbers");
    auto callback9 = [&](ud::S<int64_t> const& item6) -> ud::S<bool> {
                     // lt typed_as='bool'
                     //     const_int typed_as='int64' int_val=1
                     //     var typed_as='int64' str_val='number'
                     //
                     ud::S<int64_t> const& expr7 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
                     ud::S<bool> const& expr8 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 255), expr7, item6);
                     return expr8;
                     };
    ud::S<hstd::Vec<ud::S<int64_t>>> const& expr10 = ud::eval_op<ud::OpId::FILTER, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 255), expr5, callback9);
    ud::S<int64_t> const& expr11 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 255), expr10);
    ud::S<int64_t> const& expr12 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
    ud::S<bool> const& expr13 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 255), expr11, expr12);
    ud::set_value(condition1, expr13);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr14 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.Filter"), "poc.Filter");
    return ud::VerifyResult::Error(ud::get_stored_value(expr14));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_FilterMap(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='FilterMap'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     let typed_as='bool' binders='present'[list<int64>]
  //         filter_map typed_as='list<int64>' binders='optional'[optional<int64>]
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::FilterMap);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 260, ud::OpId::LET);
    ud::S<hstd::Vec<ud::S<hstd::Opt<ud::S<int64_t>>>>> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Vec<ud::S<hstd::Opt<ud::S<int64_t>>>>>>(ud::get_context(ctx, "hstd_test_model.py", 263), expr0, "optionals");
    auto callback7 = [&](ud::S<hstd::Opt<ud::S<int64_t>>> const& item6) -> ud::S<hstd::Opt<ud::S<int64_t>>> {
                     // var typed_as='optional<int64>' str_val='optional'
                     //
                     return item6;
                     };
    ud::S<hstd::Vec<ud::S<int64_t>>> const& expr8 = ud::eval_op<ud::OpId::FILTER_MAP, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 262), expr5, callback7);
    auto condition9 = ud::S<bool>::FromConst(true, "true");
    if (ud::get_stored_value(condition9)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 268, ud::OpId::EQ);
      ud::S<int64_t> const& expr10 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 268), expr8);
      ud::S<int64_t> const& expr11 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
      ud::S<bool> const& expr12 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 268), expr10, expr11);
      ud::set_value(condition9, expr12);
    }
    if (ud::get_stored_value(condition9)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 269, ud::OpId::EQ);
      ud::S<int64_t> const& expr13 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
      ud::S<int64_t> const& expr14 = ud::eval_op<ud::OpId::LIST_AT, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 269), expr8, expr13);
      ud::S<int64_t> const& expr15 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
      ud::S<bool> const& expr16 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 269), expr14, expr15);
      ud::set_value(condition9, expr16);
    }
    if (ud::get_stored_value(condition9)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 270, ud::OpId::EQ);
      ud::S<int64_t> const& expr17 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
      ud::S<int64_t> const& expr18 = ud::eval_op<ud::OpId::LIST_AT, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 270), expr8, expr17);
      ud::S<int64_t> const& expr19 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
      ud::S<bool> const& expr20 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 270), expr18, expr19);
      ud::set_value(condition9, expr20);
    }
    ud::set_value(condition1, condition9);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr21 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.FilterMap"), "poc.FilterMap");
    return ud::VerifyResult::Error(ud::get_stored_value(expr21));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_TakeWhile(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='TakeWhile'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         list_size typed_as='int64'
  //             take_while typed_as='list<int64>' binders='number'[int64]
  //                 get_field typed_as='list<int64>' str_val='numbers'
  //                     this typed_as='OperationChecks'
  //                 lt typed_as='bool'
  //                     var typed_as='int64' str_val='number'
  //                     const_int typed_as='int64' int_val=3
  //         const_int typed_as='int64' int_val=2
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::TakeWhile);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 276, ud::OpId::EQ);
    ud::S<hstd::Vec<ud::S<int64_t>>> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 277), expr0, "numbers");
    auto callback9 = [&](ud::S<int64_t> const& item6) -> ud::S<bool> {
                     // lt typed_as='bool'
                     //     var typed_as='int64' str_val='number'
                     //     const_int typed_as='int64' int_val=3
                     //
                     ud::S<int64_t> const& expr7 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
                     ud::S<bool> const& expr8 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 279), item6, expr7);
                     return expr8;
                     };
    ud::S<hstd::Vec<ud::S<int64_t>>> const& expr10 = ud::eval_op<ud::OpId::TAKE_WHILE, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 276), expr5, callback9);
    ud::S<int64_t> const& expr11 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 280), expr10);
    ud::S<int64_t> const& expr12 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
    ud::S<bool> const& expr13 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 276), expr11, expr12);
    ud::set_value(condition1, expr13);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr14 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.TakeWhile"), "poc.TakeWhile");
    return ud::VerifyResult::Error(ud::get_stored_value(expr14));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_GroupBy(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='GroupBy'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     let typed_as='bool' binders='groups'[map<bool, list<int64>>]
  //         group_by typed_as='map<bool, list<int64>>' binders='number'[int64]
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::GroupBy);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 285, ud::OpId::LET);
    ud::S<hstd::Vec<ud::S<int64_t>>> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 288), expr0, "numbers");
    auto callback9 = [&](ud::S<int64_t> const& item6) -> ud::S<bool> {
                     // lt typed_as='bool'
                     //     var typed_as='int64' str_val='number'
                     //     const_int typed_as='int64' int_val=3
                     //
                     ud::S<int64_t> const& expr7 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
                     ud::S<bool> const& expr8 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 290), item6, expr7);
                     return expr8;
                     };
    ud::S<hstd::UnorderedMap<ud::S<bool>, ud::S<hstd::Vec<ud::S<int64_t>>>>> const& expr10 = ud::eval_op<ud::OpId::GROUP_BY, ud::S<hstd::UnorderedMap<ud::S<bool>, ud::S<hstd::Vec<ud::S<int64_t>>>>>>(ud::get_context(ctx, "hstd_test_model.py", 287), expr5, callback9);
    auto condition11 = ud::S<bool>::FromConst(true, "true");
    if (ud::get_stored_value(condition11)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 293, ud::OpId::EQ);
      ud::S<int64_t> const& expr12 = ud::eval_op<ud::OpId::MAP_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 293), expr10);
      ud::S<int64_t> const& expr13 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
      ud::S<bool> const& expr14 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 293), expr12, expr13);
      ud::set_value(condition11, expr14);
    }
    if (ud::get_stored_value(condition11)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 294, ud::OpId::EQ);
      ud::S<hstd::Vec<ud::S<hstd::Vec<ud::S<int64_t>>>>> const& expr15 = ud::eval_op<ud::OpId::MAP_VALUES, ud::S<hstd::Vec<ud::S<hstd::Vec<ud::S<int64_t>>>>>>(ud::get_context(ctx, "hstd_test_model.py", 294), expr10);
      ud::S<int64_t> const& expr16 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
      ud::S<hstd::Vec<ud::S<int64_t>>> const& expr17 = ud::eval_op<ud::OpId::LIST_AT, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 294), expr15, expr16);
      ud::S<int64_t> const& expr18 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
      ud::S<int64_t> const& expr19 = ud::eval_op<ud::OpId::LIST_AT, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 294), expr17, expr18);
      ud::S<hstd::Vec<ud::S<int64_t>>> const& expr20 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 295), expr0, "numbers");
      ud::S<int64_t> const& expr21 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
      ud::S<int64_t> const& expr22 = ud::eval_op<ud::OpId::LIST_AT, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 295), expr20, expr21);
      ud::S<bool> const& expr23 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 294), expr19, expr22);
      ud::set_value(condition11, expr23);
    }
    ud::set_value(condition1, condition11);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr24 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.GroupBy"), "poc.GroupBy");
    return ud::VerifyResult::Error(ud::get_stored_value(expr24));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Fold(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='Fold'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         fold typed_as='int64' binders='acc'[int64], 'number'[int64]
  //             get_field typed_as='list<int64>' str_val='numbers'
  //                 this typed_as='OperationChecks'
  //             const_int typed_as='int64' int_val=0
  //             add typed_as='int64'
  //                 var typed_as='int64' str_val='acc'
  //                 var typed_as='int64' str_val='number'
  //         const_int typed_as='int64' int_val=6
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::Fold);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 301, ud::OpId::EQ);
    ud::S<hstd::Vec<ud::S<int64_t>>> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 302), expr0, "numbers");
    ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
    auto callback7 = [&](ud::S<int64_t> const& item8, ud::S<int64_t> const& item9) -> ud::S<int64_t> {
                     // add typed_as='int64'
                     //     var typed_as='int64' str_val='acc'
                     //     var typed_as='int64' str_val='number'
                     //
                     ud::S<int64_t> const& expr10 = ud::eval_op<ud::OpId::ADD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 306), item8, item9);
                     return expr10;
                     };
    ud::S<int64_t> const& expr11 = ud::eval_op<ud::OpId::FOLD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 301), expr5, expr6, callback7);
    ud::S<int64_t> const& expr12 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
    ud::S<bool> const& expr13 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 301), expr11, expr12);
    ud::set_value(condition1, expr13);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr14 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.Fold"), "poc.Fold");
    return ud::VerifyResult::Error(ud::get_stored_value(expr14));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Walk(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='Walk'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     let typed_as='bool' binders='ids'[list<int64>]
  //         filter_map typed_as='list<int64>' binders='walk_value'[dyn<Derived>]
  //             walk typed_as='list<dyn<Derived>>'
  //                 get_field typed_as='Derived' str_val='derived'
  //                     this typed_as='OperationChecks'
  //             type_cond typed_as='optional<int64>' bool_val=True
  //                 var typed_as='dyn<Derived>' str_val='walk_value'
  //                 type_case typed_as='int64' type_val='Derived' binders='derived'[Derived]
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
  __populate_expression_runtime(expression_runtime);
  auto const& expr0 = (this_obj);
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::Walk);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 312, ud::OpId::LET);
    ud::S<hstd::unidata_dsl::test::Derived> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Derived>>(ud::get_context(ctx, "hstd_test_model.py", 314), expr0, "derived");
    ud::S<hstd::Vec<ud::UniDynamic>> const& expr6 = ud::eval_op<ud::OpId::WALK, ud::S<hstd::Vec<ud::UniDynamic>>>(ud::get_context(ctx, "hstd_test_model.py", 154), expression_runtime, expr5);
    auto callback11 = [&](ud::UniDynamic const& item7) -> ud::S<hstd::Opt<ud::S<int64_t>>> {
                      // type_cond typed_as='optional<int64>' bool_val=True
                      //     var typed_as='dyn<Derived>' str_val='walk_value'
                      //     type_case typed_as='int64' type_val='Derived' binders='derived'[Derived]
                      //         get_field typed_as='int64' str_val='id'
                      //             var typed_as='Derived' str_val='derived'
                      //
                      ud::S<ud::UniOpt<ud::S<int64_t>>> result8 = ud::S<ud::UniOpt<ud::S<int64_t>>>::FromConst(std::nullopt, "std::nullopt");
                      if (!ud::get_stored_as_bool(result8)) {
                        hstd::Opt<ud::S<hstd::unidata_dsl::test::Derived>> candidate9 = expression_runtime.try_as<hstd::unidata_dsl::test::Derived>(item7);
                        if (candidate9.has_value()) {
                          ud::S<int64_t> const& expr10 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 161), (*candidate9), "id");
                          ud::set_value(result8, expr10);
                        }
                      }
                      return result8;
                      };
    ud::S<hstd::Vec<ud::S<int64_t>>> const& expr12 = ud::eval_op<ud::OpId::FILTER_MAP, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 153), expr6, callback11);
    auto condition13 = ud::S<bool>::FromConst(true, "true");
    if (ud::get_stored_value(condition13)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 316, ud::OpId::EQ);
      ud::S<int64_t> const& expr14 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 316), expr12);
      ud::S<int64_t> const& expr15 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
      ud::S<bool> const& expr16 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 316), expr14, expr15);
      ud::set_value(condition13, expr16);
    }
    if (ud::get_stored_value(condition13)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 317, ud::OpId::EQ);
      ud::S<int64_t> const& expr17 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
      ud::S<int64_t> const& expr18 = ud::eval_op<ud::OpId::LIST_AT, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 317), expr12, expr17);
      ud::S<int64_t> const& expr19 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
      ud::S<bool> const& expr20 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 317), expr18, expr19);
      ud::set_value(condition13, expr20);
    }
    ud::set_value(condition1, condition13);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr21 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.Walk"), "poc.Walk");
    return ud::VerifyResult::Error(ud::get_stored_value(expr21));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Sum(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::Sum);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 321, ud::OpId::EQ);
    ud::S<hstd::Vec<ud::S<int64_t>>> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 321), expr0, "numbers");
    ud::S<int64_t> const& expr6 = ud::eval_op<ud::OpId::SUM, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 321), expr5);
    ud::S<int64_t> const& expr7 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
    ud::S<bool> const& expr8 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 321), expr6, expr7);
    ud::set_value(condition1, expr8);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr9 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.Sum"), "poc.Sum");
    return ud::VerifyResult::Error(ud::get_stored_value(expr9));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Min(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::Min);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 322, ud::OpId::EQ);
    ud::S<hstd::Vec<ud::S<int64_t>>> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 322), expr0, "numbers");
    ud::S<int64_t> const& expr6 = ud::eval_op<ud::OpId::MIN, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 322), expr5);
    ud::S<int64_t> const& expr7 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
    ud::S<bool> const& expr8 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 322), expr6, expr7);
    ud::set_value(condition1, expr8);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr9 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.Min"), "poc.Min");
    return ud::VerifyResult::Error(ud::get_stored_value(expr9));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Max(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::Max);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 323, ud::OpId::EQ);
    ud::S<hstd::Vec<ud::S<int64_t>>> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 323), expr0, "numbers");
    ud::S<int64_t> const& expr6 = ud::eval_op<ud::OpId::MAX, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 323), expr5);
    ud::S<int64_t> const& expr7 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
    ud::S<bool> const& expr8 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 323), expr6, expr7);
    ud::set_value(condition1, expr8);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr9 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.Max"), "poc.Max");
    return ud::VerifyResult::Error(ud::get_stored_value(expr9));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_StrSize(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::StrSize);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 324, ud::OpId::EQ);
    ud::S<hstd::Str> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 324), expr0, "text");
    ud::S<int64_t> const& expr6 = ud::eval_op<ud::OpId::STR_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 324), expr5);
    ud::S<int64_t> const& expr7 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
    ud::S<bool> const& expr8 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 324), expr6, expr7);
    ud::set_value(condition1, expr8);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr9 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.StrSize"), "poc.StrSize");
    return ud::VerifyResult::Error(ud::get_stored_value(expr9));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_StrMatches(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::StrMatches);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 325, ud::OpId::STR_MATCHES);
    ud::S<hstd::Str> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 325), expr0, "text");
    ud::S<bool> const& expr6 = ud::eval_op<ud::OpId::STR_MATCHES, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 325), expr5, "^s[a-z]{2}$");
    ud::set_value(condition1, expr6);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr7 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.StrMatches"), "poc.StrMatches");
    return ud::VerifyResult::Error(ud::get_stored_value(expr7));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_StrFormat(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='StrFormat'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     eq typed_as='bool'
  //         str_format typed_as='string' str_val='{}:{}'
  //             get_field typed_as='string' str_val='text'
  //                 this typed_as='OperationChecks'
  //             get_field typed_as='int64' str_val='number'
  //                 this typed_as='OperationChecks'
  //         const_str typed_as='string' str_val='six:6'
  //
  auto const& expr0 = (this_obj);
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::StrFormat);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 328, ud::OpId::EQ);
    ud::S<hstd::Str> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 328), expr0, "text");
    ud::S<int64_t> const& expr6 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 328), expr0, "number");
    ud::S<hstd::Str> const& expr7 = ud::eval_op<ud::OpId::STR_FORMAT, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 328), eval_str_pattern("{}:{}"), expr5, expr6);
    ud::S<hstd::Str> const& expr8 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("six:6"), "six:6");
    ud::S<bool> const& expr9 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 328), expr7, expr8);
    ud::set_value(condition1, expr9);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr10 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.StrFormat"), "poc.StrFormat");
    return ud::VerifyResult::Error(ud::get_stored_value(expr10));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ListSize(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::ListSize);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 330, ud::OpId::EQ);
    ud::S<hstd::Vec<ud::S<int64_t>>> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 330), expr0, "numbers");
    ud::S<int64_t> const& expr6 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 330), expr5);
    ud::S<int64_t> const& expr7 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
    ud::S<bool> const& expr8 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 330), expr6, expr7);
    ud::set_value(condition1, expr8);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr9 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.ListSize"), "poc.ListSize");
    return ud::VerifyResult::Error(ud::get_stored_value(expr9));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ListContains(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::ListContains);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 331, ud::OpId::LIST_CONTAINS);
    ud::S<hstd::Vec<ud::S<int64_t>>> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 331), expr0, "numbers");
    ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
    ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::LIST_CONTAINS, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 331), expr5, expr6);
    ud::set_value(condition1, expr7);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr8 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.ListContains"), "poc.ListContains");
    return ud::VerifyResult::Error(ud::get_stored_value(expr8));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ListAt(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::ListAt);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 332, ud::OpId::EQ);
    ud::S<hstd::Vec<ud::S<int64_t>>> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 332), expr0, "numbers");
    ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
    ud::S<int64_t> const& expr7 = ud::eval_op<ud::OpId::LIST_AT, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 332), expr5, expr6);
    ud::S<int64_t> const& expr8 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
    ud::S<bool> const& expr9 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 332), expr7, expr8);
    ud::set_value(condition1, expr9);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr10 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.ListAt"), "poc.ListAt");
    return ud::VerifyResult::Error(ud::get_stored_value(expr10));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ListSlice(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='ListSlice'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     let typed_as='bool' binders='slice'[list<int64>]
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::ListSlice);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 335, ud::OpId::LET);
    ud::S<hstd::Vec<ud::S<int64_t>>> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 337), expr0, "numbers");
    ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
    ud::S<int64_t> const& expr7 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
    ud::S<hstd::Vec<ud::S<int64_t>>> const& expr8 = ud::eval_op<ud::OpId::LIST_SLICE, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 337), expr5, expr6, expr7);
    auto condition9 = ud::S<bool>::FromConst(true, "true");
    if (ud::get_stored_value(condition9)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 339, ud::OpId::EQ);
      ud::S<int64_t> const& expr10 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 339), expr8);
      ud::S<int64_t> const& expr11 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
      ud::S<bool> const& expr12 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 339), expr10, expr11);
      ud::set_value(condition9, expr12);
    }
    if (ud::get_stored_value(condition9)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 340, ud::OpId::EQ);
      ud::S<int64_t> const& expr13 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
      ud::S<int64_t> const& expr14 = ud::eval_op<ud::OpId::LIST_AT, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 340), expr8, expr13);
      ud::S<int64_t> const& expr15 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
      ud::S<bool> const& expr16 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 340), expr14, expr15);
      ud::set_value(condition9, expr16);
    }
    if (ud::get_stored_value(condition9)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 341, ud::OpId::EQ);
      ud::S<int64_t> const& expr17 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
      ud::S<int64_t> const& expr18 = ud::eval_op<ud::OpId::LIST_AT, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 341), expr8, expr17);
      ud::S<int64_t> const& expr19 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
      ud::S<bool> const& expr20 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 341), expr18, expr19);
      ud::set_value(condition9, expr20);
    }
    ud::set_value(condition1, condition9);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr21 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.ListSlice"), "poc.ListSlice");
    return ud::VerifyResult::Error(ud::get_stored_value(expr21));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ListSliceBounds(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='ListSliceBounds'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     let typed_as='bool' binders='slice'[list<int64>]
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::ListSliceBounds);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 347, ud::OpId::LET);
    ud::S<hstd::Vec<ud::S<int64_t>>> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 349), expr0, "numbers");
    ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(-2), "-2");
    ud::S<int64_t> const& expr7 = ud::S<int64_t>::FromConst(static_cast<int64_t>(100), "100");
    ud::S<hstd::Vec<ud::S<int64_t>>> const& expr8 = ud::eval_op<ud::OpId::LIST_SLICE, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 349), expr5, expr6, expr7);
    auto condition9 = ud::S<bool>::FromConst(true, "true");
    if (ud::get_stored_value(condition9)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 351, ud::OpId::EQ);
      ud::S<int64_t> const& expr10 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 351), expr8);
      ud::S<int64_t> const& expr11 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
      ud::S<bool> const& expr12 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 351), expr10, expr11);
      ud::set_value(condition9, expr12);
    }
    if (ud::get_stored_value(condition9)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 352, ud::OpId::EQ);
      ud::S<int64_t> const& expr13 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
      ud::S<int64_t> const& expr14 = ud::eval_op<ud::OpId::LIST_AT, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 352), expr8, expr13);
      ud::S<int64_t> const& expr15 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
      ud::S<bool> const& expr16 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 352), expr14, expr15);
      ud::set_value(condition9, expr16);
    }
    if (ud::get_stored_value(condition9)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 353, ud::OpId::EQ);
      ud::S<int64_t> const& expr17 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
      ud::S<int64_t> const& expr18 = ud::eval_op<ud::OpId::LIST_AT, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 353), expr8, expr17);
      ud::S<int64_t> const& expr19 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
      ud::S<bool> const& expr20 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 353), expr18, expr19);
      ud::set_value(condition9, expr20);
    }
    ud::set_value(condition1, condition9);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr21 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.ListSliceBounds"), "poc.ListSliceBounds");
    return ud::VerifyResult::Error(ud::get_stored_value(expr21));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ListConcat(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='ListConcat'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     let typed_as='bool' binders='joined'[list<int64>]
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::ListConcat);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 359, ud::OpId::LET);
    ud::S<hstd::Vec<ud::S<int64_t>>> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 361), expr0, "numbers");
    ud::S<hstd::Vec<ud::S<int64_t>>> const& expr6 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 361), expr0, "numbers");
    ud::S<hstd::Vec<ud::S<int64_t>>> const& expr7 = ud::eval_op<ud::OpId::LIST_CONCAT, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 361), expr5, expr6);
    auto condition8 = ud::S<bool>::FromConst(true, "true");
    if (ud::get_stored_value(condition8)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 363, ud::OpId::EQ);
      ud::S<int64_t> const& expr9 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 363), expr7);
      ud::S<int64_t> const& expr10 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
      ud::S<bool> const& expr11 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 363), expr9, expr10);
      ud::set_value(condition8, expr11);
    }
    if (ud::get_stored_value(condition8)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 364, ud::OpId::EQ);
      ud::S<int64_t> const& expr12 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
      ud::S<int64_t> const& expr13 = ud::eval_op<ud::OpId::LIST_AT, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 364), expr7, expr12);
      ud::S<hstd::Vec<ud::S<int64_t>>> const& expr14 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 364), expr0, "numbers");
      ud::S<int64_t> const& expr15 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
      ud::S<int64_t> const& expr16 = ud::eval_op<ud::OpId::LIST_AT, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 364), expr14, expr15);
      ud::S<bool> const& expr17 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 364), expr13, expr16);
      ud::set_value(condition8, expr17);
    }
    ud::set_value(condition1, condition8);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr18 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.ListConcat"), "poc.ListConcat");
    return ud::VerifyResult::Error(ud::get_stored_value(expr18));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ListEmpty(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::ListEmpty);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 368, ud::OpId::EQ);
    ud::S<hstd::Vec<ud::S<int64_t>>> const& expr5 = ud::eval_op<ud::OpId::LIST_EMPTY, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 368));
    ud::S<int64_t> const& expr6 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 368), expr5);
    ud::S<int64_t> const& expr7 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
    ud::S<bool> const& expr8 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 368), expr6, expr7);
    ud::set_value(condition1, expr8);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr9 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.ListEmpty"), "poc.ListEmpty");
    return ud::VerifyResult::Error(ud::get_stored_value(expr9));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapSize(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::MapSize);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 369, ud::OpId::EQ);
    ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 369), expr0, "mapping");
    ud::S<int64_t> const& expr6 = ud::eval_op<ud::OpId::MAP_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 369), expr5);
    ud::S<int64_t> const& expr7 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
    ud::S<bool> const& expr8 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 369), expr6, expr7);
    ud::set_value(condition1, expr8);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr9 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.MapSize"), "poc.MapSize");
    return ud::VerifyResult::Error(ud::get_stored_value(expr9));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapContains(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::MapContains);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 370, ud::OpId::MAP_CONTAINS);
    ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 370), expr0, "mapping");
    ud::S<hstd::Str> const& expr6 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("a"), "a");
    ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::MAP_CONTAINS, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 370), expr5, expr6);
    ud::set_value(condition1, expr7);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr8 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.MapContains"), "poc.MapContains");
    return ud::VerifyResult::Error(ud::get_stored_value(expr8));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapGet(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::MapGet);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 371, ud::OpId::EQ);
    ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 371), expr0, "mapping");
    ud::S<hstd::Str> const& expr6 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("a"), "a");
    ud::S<int64_t> const& expr7 = ud::eval_op<ud::OpId::MAP_GET, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 371), expr5, expr6);
    ud::S<int64_t> const& expr8 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
    ud::S<bool> const& expr9 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 371), expr7, expr8);
    ud::set_value(condition1, expr9);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr10 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.MapGet"), "poc.MapGet");
    return ud::VerifyResult::Error(ud::get_stored_value(expr10));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapInsert(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='MapInsert'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     let typed_as='bool' binders='updated'[map<string, int64>]
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::MapInsert);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 374, ud::OpId::LET);
    ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 376), expr0, "mapping");
    ud::S<hstd::Str> const& expr6 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("c"), "c");
    ud::S<int64_t> const& expr7 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
    ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr8 = ud::eval_op<ud::OpId::MAP_INSERT, ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 376), expr5, expr6, expr7);
    auto condition9 = ud::S<bool>::FromConst(true, "true");
    if (ud::get_stored_value(condition9)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 378, ud::OpId::EQ);
      ud::S<int64_t> const& expr10 = ud::eval_op<ud::OpId::MAP_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 378), expr8);
      ud::S<int64_t> const& expr11 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
      ud::S<bool> const& expr12 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 378), expr10, expr11);
      ud::set_value(condition9, expr12);
    }
    if (ud::get_stored_value(condition9)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 379, ud::OpId::EQ);
      ud::S<hstd::Str> const& expr13 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("c"), "c");
      ud::S<int64_t> const& expr14 = ud::eval_op<ud::OpId::MAP_GET, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 379), expr8, expr13);
      ud::S<int64_t> const& expr15 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
      ud::S<bool> const& expr16 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 379), expr14, expr15);
      ud::set_value(condition9, expr16);
    }
    if (ud::get_stored_value(condition9)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 380, ud::OpId::NOT);
      ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr17 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 380), expr0, "mapping");
      ud::S<hstd::Str> const& expr18 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("c"), "c");
      ud::S<bool> const& expr19 = ud::eval_op<ud::OpId::MAP_CONTAINS, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 380), expr17, expr18);
      ud::S<bool> const& expr20 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 380), (expr19));
      ud::set_value(condition9, expr20);
    }
    ud::set_value(condition1, condition9);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr21 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.MapInsert"), "poc.MapInsert");
    return ud::VerifyResult::Error(ud::get_stored_value(expr21));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapReplace(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='MapReplace'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     let typed_as='bool' binders='updated'[map<string, int64>]
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::MapReplace);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 386, ud::OpId::LET);
    ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 388), expr0, "mapping");
    ud::S<hstd::Str> const& expr6 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("a"), "a");
    ud::S<int64_t> const& expr7 = ud::S<int64_t>::FromConst(static_cast<int64_t>(9), "9");
    ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr8 = ud::eval_op<ud::OpId::MAP_INSERT, ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 388), expr5, expr6, expr7);
    auto condition9 = ud::S<bool>::FromConst(true, "true");
    if (ud::get_stored_value(condition9)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 390, ud::OpId::EQ);
      ud::S<int64_t> const& expr10 = ud::eval_op<ud::OpId::MAP_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 390), expr8);
      ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr11 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 390), expr0, "mapping");
      ud::S<int64_t> const& expr12 = ud::eval_op<ud::OpId::MAP_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 390), expr11);
      ud::S<bool> const& expr13 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 390), expr10, expr12);
      ud::set_value(condition9, expr13);
    }
    if (ud::get_stored_value(condition9)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 391, ud::OpId::EQ);
      ud::S<hstd::Str> const& expr14 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("a"), "a");
      ud::S<int64_t> const& expr15 = ud::eval_op<ud::OpId::MAP_GET, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 391), expr8, expr14);
      ud::S<int64_t> const& expr16 = ud::S<int64_t>::FromConst(static_cast<int64_t>(9), "9");
      ud::S<bool> const& expr17 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 391), expr15, expr16);
      ud::set_value(condition9, expr17);
    }
    if (ud::get_stored_value(condition9)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 392, ud::OpId::EQ);
      ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr18 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 392), expr0, "mapping");
      ud::S<hstd::Str> const& expr19 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("a"), "a");
      ud::S<int64_t> const& expr20 = ud::eval_op<ud::OpId::MAP_GET, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 392), expr18, expr19);
      ud::S<int64_t> const& expr21 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
      ud::S<bool> const& expr22 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 392), expr20, expr21);
      ud::set_value(condition9, expr22);
    }
    ud::set_value(condition1, condition9);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr23 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.MapReplace"), "poc.MapReplace");
    return ud::VerifyResult::Error(ud::get_stored_value(expr23));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapKeys(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='MapKeys'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     let typed_as='bool' binders='keys'[list<string>]
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::MapKeys);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 398, ud::OpId::LET);
    ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 400), expr0, "mapping");
    ud::S<hstd::Vec<ud::S<hstd::Str>>> const& expr6 = ud::eval_op<ud::OpId::MAP_KEYS, ud::S<hstd::Vec<ud::S<hstd::Str>>>>(ud::get_context(ctx, "hstd_test_model.py", 400), expr5);
    auto condition7 = ud::S<bool>::FromConst(true, "true");
    if (ud::get_stored_value(condition7)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 402, ud::OpId::EQ);
      ud::S<int64_t> const& expr8 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 402), expr6);
      ud::S<int64_t> const& expr9 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
      ud::S<bool> const& expr10 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 402), expr8, expr9);
      ud::set_value(condition7, expr10);
    }
    if (ud::get_stored_value(condition7)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 403, ud::OpId::LIST_CONTAINS);
      ud::S<hstd::Str> const& expr11 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("a"), "a");
      ud::S<bool> const& expr12 = ud::eval_op<ud::OpId::LIST_CONTAINS, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 403), expr6, expr11);
      ud::set_value(condition7, expr12);
    }
    if (ud::get_stored_value(condition7)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 404, ud::OpId::LIST_CONTAINS);
      ud::S<hstd::Str> const& expr13 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("b"), "b");
      ud::S<bool> const& expr14 = ud::eval_op<ud::OpId::LIST_CONTAINS, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 404), expr6, expr13);
      ud::set_value(condition7, expr14);
    }
    ud::set_value(condition1, condition7);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr15 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.MapKeys"), "poc.MapKeys");
    return ud::VerifyResult::Error(ud::get_stored_value(expr15));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapValues(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='MapValues'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     let typed_as='bool' binders='values'[list<int64>]
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::MapValues);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 410, ud::OpId::LET);
    ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 412), expr0, "mapping");
    ud::S<hstd::Vec<ud::S<int64_t>>> const& expr6 = ud::eval_op<ud::OpId::MAP_VALUES, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 412), expr5);
    auto condition7 = ud::S<bool>::FromConst(true, "true");
    if (ud::get_stored_value(condition7)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 414, ud::OpId::EQ);
      ud::S<int64_t> const& expr8 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 414), expr6);
      ud::S<int64_t> const& expr9 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
      ud::S<bool> const& expr10 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 414), expr8, expr9);
      ud::set_value(condition7, expr10);
    }
    if (ud::get_stored_value(condition7)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 415, ud::OpId::LIST_CONTAINS);
      ud::S<int64_t> const& expr11 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
      ud::S<bool> const& expr12 = ud::eval_op<ud::OpId::LIST_CONTAINS, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 415), expr6, expr11);
      ud::set_value(condition7, expr12);
    }
    if (ud::get_stored_value(condition7)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 416, ud::OpId::LIST_CONTAINS);
      ud::S<int64_t> const& expr13 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
      ud::S<bool> const& expr14 = ud::eval_op<ud::OpId::LIST_CONTAINS, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 416), expr6, expr13);
      ud::set_value(condition7, expr14);
    }
    ud::set_value(condition1, condition7);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr15 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.MapValues"), "poc.MapValues");
    return ud::VerifyResult::Error(ud::get_stored_value(expr15));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapEmpty(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::MapEmpty);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 420, ud::OpId::EQ);
    ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr5 = ud::eval_op<ud::OpId::MAP_EMPTY, ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 420));
    ud::S<int64_t> const& expr6 = ud::eval_op<ud::OpId::MAP_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 420), expr5);
    ud::S<int64_t> const& expr7 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
    ud::S<bool> const& expr8 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 420), expr6, expr7);
    ud::set_value(condition1, expr8);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr9 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.MapEmpty"), "poc.MapEmpty");
    return ud::VerifyResult::Error(ud::get_stored_value(expr9));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_OptHasValue(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::OptHasValue);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 421, ud::OpId::OPT_HAS_VALUE);
    ud::S<hstd::Opt<ud::S<int64_t>>> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Opt<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 421), expr0, "optional");
    ud::S<bool> const& expr6 = ud::eval_op<ud::OpId::OPT_HAS_VALUE, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 421), expr5);
    ud::set_value(condition1, expr6);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr7 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.OptHasValue"), "poc.OptHasValue");
    return ud::VerifyResult::Error(ud::get_stored_value(expr7));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_OptValue(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::OptValue);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 424, ud::OpId::AND);
    auto condition5 = ud::S<bool>::FromConst(true, "true");
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 425, ud::OpId::OPT_HAS_VALUE);
      ud::S<hstd::Opt<ud::S<int64_t>>> const& expr6 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Opt<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 425), expr0, "optional");
      ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::OPT_HAS_VALUE, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 425), expr6);
      ud::set_value(condition5, expr7);
    }
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 426, ud::OpId::EQ);
      ud::S<hstd::Opt<ud::S<int64_t>>> const& expr8 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Opt<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 426), expr0, "optional");
      ud::S<int64_t> const& expr9 = ud::eval_op<ud::OpId::OPT_VALUE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 426), expr8);
      ud::S<int64_t> const& expr10 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
      ud::S<bool> const& expr11 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 426), expr9, expr10);
      ud::set_value(condition5, expr11);
    }
    ud::set_value(condition1, condition5);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr12 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.OptValue"), "poc.OptValue");
    return ud::VerifyResult::Error(ud::get_stored_value(expr12));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_CaseIs(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::CaseIs);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 437, ud::OpId::CASE_IS);
    ud::S<hstd::unidata_dsl::test::Choice> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Choice>>(ud::get_context(ctx, "hstd_test_model.py", 437), expr0, "choice");
    ud::S<hstd::unidata_dsl::test::Choice::Data> const& expr6 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Choice::Data>>(ud::get_context(ctx, "hstd_test_model.py", 437), expr5, "data");
    ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::CASE_IS, ud::S<bool>, hstd::unidata_dsl::test::Choice::First>(ud::get_context(ctx, "hstd_test_model.py", 437), expr6);
    ud::set_value(condition1, expr7);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr8 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.CaseIs"), "poc.CaseIs");
    return ud::VerifyResult::Error(ud::get_stored_value(expr8));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_CaseWhich(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::CaseWhich);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 440, ud::OpId::ENUM_IS);
    ud::S<hstd::unidata_dsl::test::Choice> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Choice>>(ud::get_context(ctx, "hstd_test_model.py", 440), expr0, "choice");
    ud::S<hstd::unidata_dsl::test::Choice::Data> const& expr6 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Choice::Data>>(ud::get_context(ctx, "hstd_test_model.py", 440), expr5, "data");
    ud::S<hstd::unidata_dsl::test::Choice::Kind> const& expr7 = ud::eval_op<ud::OpId::CASE_WHICH, ud::S<hstd::unidata_dsl::test::Choice::Kind>>(ud::get_context(ctx, "hstd_test_model.py", 440), expr6);
    ud::S<bool> const& expr8 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 440), expr7, hstd::unidata_dsl::test::Choice::Kind::First);
    ud::set_value(condition1, expr8);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr9 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.CaseWhich"), "poc.CaseWhich");
    return ud::VerifyResult::Error(ud::get_stored_value(expr9));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_CaseField(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::CaseField);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 444, ud::OpId::EQ);
    ud::S<hstd::unidata_dsl::test::Choice> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Choice>>(ud::get_context(ctx, "hstd_test_model.py", 446), expr0, "choice");
    ud::S<hstd::unidata_dsl::test::Choice::Data> const& expr6 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Choice::Data>>(ud::get_context(ctx, "hstd_test_model.py", 446), expr5, "data");
    ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::CASE_IS, ud::S<bool>, hstd::unidata_dsl::test::Choice::First>(ud::get_context(ctx, "hstd_test_model.py", 446), expr6);
    ud::S<ud::UniOpt<ud::S<int64_t>>> result12 = ud::S<ud::UniOpt<ud::S<int64_t>>>::FromConst(std::nullopt, "std::nullopt");
    if (ud::get_stored_value(expr7)) {
      ud::S<hstd::unidata_dsl::test::Choice> const& expr8 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Choice>>(ud::get_context(ctx, "hstd_test_model.py", 447), expr0, "choice");
      ud::S<hstd::unidata_dsl::test::Choice::Data> const& expr9 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Choice::Data>>(ud::get_context(ctx, "hstd_test_model.py", 447), expr8, "data");
      ud::S<int64_t> const& expr10 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 447), expr9, "value");
      ud::set_value(result12, expr10);
    } else {
      ud::S<int64_t> const& expr11 = ud::S<int64_t>::FromConst(static_cast<int64_t>(-1), "-1");
      ud::set_value(result12, expr11);
    }
    ud::S<int64_t> const& expr13 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
    ud::S<bool> const& expr14 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 444), ud::get_value_ref(result12), expr13);
    ud::set_value(condition1, expr14);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr15 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.CaseField"), "poc.CaseField");
    return ud::VerifyResult::Error(ud::get_stored_value(expr15));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_EnumIs(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::EnumIs);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 453, ud::OpId::ENUM_IS);
    ud::S<hstd::unidata_dsl::test::Status> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Status>>(ud::get_context(ctx, "hstd_test_model.py", 453), expr0, "status");
    ud::S<bool> const& expr6 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 453), expr5, hstd::unidata_dsl::test::Status::Ready);
    ud::set_value(condition1, expr6);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr7 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.EnumIs"), "poc.EnumIs");
    return ud::VerifyResult::Error(ud::get_stored_value(expr7));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_NthGet(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::NthGet);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 456, ud::OpId::AND);
    auto condition5 = ud::S<bool>::FromConst(true, "true");
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 457, ud::OpId::EQ);
      ud::S<hstd::Tuple<ud::S<int64_t>, ud::S<hstd::Str>>> const& expr6 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Tuple<ud::S<int64_t>, ud::S<hstd::Str>>>>(ud::get_context(ctx, "hstd_test_model.py", 457), expr0, "coords");
      ud::S<int64_t> const& expr7 = ud::eval_op<ud::OpId::NTH_GET, ud::S<int64_t>, 0>(ud::get_context(ctx, "hstd_test_model.py", 457), expr6);
      ud::S<int64_t> const& expr8 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
      ud::S<bool> const& expr9 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 457), expr7, expr8);
      ud::set_value(condition5, expr9);
    }
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 458, ud::OpId::EQ);
      ud::S<hstd::Tuple<ud::S<int64_t>, ud::S<hstd::Str>>> const& expr10 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Tuple<ud::S<int64_t>, ud::S<hstd::Str>>>>(ud::get_context(ctx, "hstd_test_model.py", 458), expr0, "coords");
      ud::S<hstd::Str> const& expr11 = ud::eval_op<ud::OpId::NTH_GET, ud::S<hstd::Str>, 1>(ud::get_context(ctx, "hstd_test_model.py", 458), expr10);
      ud::S<hstd::Str> const& expr12 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("six"), "six");
      ud::S<bool> const& expr13 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 458), expr11, expr12);
      ud::set_value(condition5, expr13);
    }
    ud::set_value(condition1, condition5);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr14 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.NthGet"), "poc.NthGet");
    return ud::VerifyResult::Error(ud::get_stored_value(expr14));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_IsDerived(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  __populate_expression_runtime(expression_runtime);
  auto const& expr0 = (this_obj);
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::IsDerived);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 463, ud::OpId::AND);
    auto condition5 = ud::S<bool>::FromConst(true, "true");
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 464, ud::OpId::IS_DERIVED);
      ud::S<hstd::unidata_dsl::test::Derived> const& expr6 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Derived>>(ud::get_context(ctx, "hstd_test_model.py", 464), expr0, "derived");
      ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::IS_DERIVED, ud::S<bool>, hstd::unidata_dsl::test::Base>(ud::get_context(ctx, "hstd_test_model.py", 464), expression_runtime, expr6);
      ud::set_value(condition5, expr7);
    }
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 465, ud::OpId::NOT);
      ud::S<hstd::unidata_dsl::test::Base> const& expr8 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Base>>(ud::get_context(ctx, "hstd_test_model.py", 465), expr0, "base");
      ud::S<bool> const& expr9 = ud::eval_op<ud::OpId::IS_DERIVED, ud::S<bool>, hstd::unidata_dsl::test::Derived>(ud::get_context(ctx, "hstd_test_model.py", 465), expression_runtime, expr8);
      ud::S<bool> const& expr10 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 465), (expr9));
      ud::set_value(condition5, expr10);
    }
    ud::set_value(condition1, condition5);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr11 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.IsDerived"), "poc.IsDerived");
    return ud::VerifyResult::Error(ud::get_stored_value(expr11));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_TypeCond(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  //             type_case typed_as='int64' type_val='Base' binders='record'[Base]
  //                 get_field typed_as='int64' str_val='id'
  //                     var typed_as='Base' str_val='record'
  //             type_case typed_as='int64' type_val='Derived' binders='record'[Derived]
  //                 const_int typed_as='int64' int_val=-1
  //         const_int typed_as='int64' int_val=6
  //
  hstd::ext::unidata::EvalRuntime expression_runtime = hstd::ext::unidata::EvalRuntime{ctx};
  __populate_expression_runtime(expression_runtime);
  auto const& expr0 = (this_obj);
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::TypeCond);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 470, ud::OpId::EQ);
    ud::S<hstd::unidata_dsl::test::Derived> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Derived>>(ud::get_context(ctx, "hstd_test_model.py", 471), expr0, "derived");
    ud::S<hstd::Vec<ud::UniDynamic>> const& expr6 = ud::eval_op<ud::OpId::WALK, ud::S<hstd::Vec<ud::UniDynamic>>>(ud::get_context(ctx, "hstd_test_model.py", 471), expression_runtime, expr5);
    ud::S<int64_t> const& expr7 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
    ud::UniDynamic const& expr8 = ud::eval_op<ud::OpId::LIST_AT, ud::UniDynamic>(ud::get_context(ctx, "hstd_test_model.py", 471), expr6, expr7);
    ud::S<ud::UniOpt<ud::S<int64_t>>> result9 = ud::S<ud::UniOpt<ud::S<int64_t>>>::FromConst(std::nullopt, "std::nullopt");
    if (!ud::get_stored_as_bool(result9)) {
      hstd::Opt<ud::S<hstd::unidata_dsl::test::Base>> candidate10 = expression_runtime.try_as<hstd::unidata_dsl::test::Base>(expr8);
      if (candidate10.has_value()) {
        ud::S<int64_t> const& expr11 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 475), (*candidate10), "id");
        ud::set_value(result9, expr11);
      }
    }
    if (!ud::get_stored_as_bool(result9)) {
      hstd::Opt<ud::S<hstd::unidata_dsl::test::Derived>> candidate12 = expression_runtime.try_as<hstd::unidata_dsl::test::Derived>(expr8);
      if (candidate12.has_value()) {
        ud::S<int64_t> const& expr13 = ud::S<int64_t>::FromConst(static_cast<int64_t>(-1), "-1");
        ud::set_value(result9, expr13);
      }
    }
    if (!ud::get_stored_as_bool(result9)) {
      throw std::runtime_error{"No type case matched at hstd_test_model.py:470; expected one of: Base, Derived"};
    }
    ud::S<int64_t> const& expr14 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
    ud::S<bool> const& expr15 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 470), ud::get_value_ref(result9), expr14);
    ud::set_value(condition1, expr15);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr16 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.TypeCond"), "poc.TypeCond");
    return ud::VerifyResult::Error(ud::get_stored_value(expr16));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_TypeCondOptional(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  //                     type_case typed_as='int64' type_val='Derived' binders='record'[Derived]
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
  //                     type_case typed_as='int64' type_val='Derived' binders='record'[Derived]
  //                         get_field typed_as='int64' str_val='id'
  //                             var typed_as='Derived' str_val='record'
  //             const_int typed_as='int64' int_val=6
  //
  hstd::ext::unidata::EvalRuntime expression_runtime = hstd::ext::unidata::EvalRuntime{ctx};
  __populate_expression_runtime(expression_runtime);
  auto const& expr0 = (this_obj);
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::TypeCondOptional);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 487, ud::OpId::AND);
    auto condition5 = ud::S<bool>::FromConst(true, "true");
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 488, ud::OpId::NOT);
      ud::S<hstd::unidata_dsl::test::Base> const& expr6 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Base>>(ud::get_context(ctx, "hstd_test_model.py", 489), expr0, "base");
      ud::S<hstd::Vec<ud::UniDynamic>> const& expr7 = ud::eval_op<ud::OpId::WALK, ud::S<hstd::Vec<ud::UniDynamic>>>(ud::get_context(ctx, "hstd_test_model.py", 489), expression_runtime, expr6);
      ud::S<int64_t> const& expr8 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
      ud::UniDynamic const& expr9 = ud::eval_op<ud::OpId::LIST_AT, ud::UniDynamic>(ud::get_context(ctx, "hstd_test_model.py", 489), expr7, expr8);
      ud::S<ud::UniOpt<ud::S<int64_t>>> result10 = ud::S<ud::UniOpt<ud::S<int64_t>>>::FromConst(std::nullopt, "std::nullopt");
      if (!ud::get_stored_as_bool(result10)) {
        hstd::Opt<ud::S<hstd::unidata_dsl::test::Derived>> candidate11 = expression_runtime.try_as<hstd::unidata_dsl::test::Derived>(expr9);
        if (candidate11.has_value()) {
          ud::S<int64_t> const& expr12 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 493), (*candidate11), "id");
          ud::set_value(result10, expr12);
        }
      }
      ud::S<bool> const& expr13 = ud::eval_op<ud::OpId::OPT_HAS_VALUE, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 496), result10);
      ud::S<bool> const& expr14 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 488), (expr13));
      ud::set_value(condition5, expr14);
    }
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 497, ud::OpId::EQ);
      ud::S<hstd::unidata_dsl::test::Derived> const& expr15 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Derived>>(ud::get_context(ctx, "hstd_test_model.py", 498), expr0, "derived");
      ud::S<hstd::Vec<ud::UniDynamic>> const& expr16 = ud::eval_op<ud::OpId::WALK, ud::S<hstd::Vec<ud::UniDynamic>>>(ud::get_context(ctx, "hstd_test_model.py", 498), expression_runtime, expr15);
      ud::S<int64_t> const& expr17 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
      ud::UniDynamic const& expr18 = ud::eval_op<ud::OpId::LIST_AT, ud::UniDynamic>(ud::get_context(ctx, "hstd_test_model.py", 498), expr16, expr17);
      ud::S<ud::UniOpt<ud::S<int64_t>>> result19 = ud::S<ud::UniOpt<ud::S<int64_t>>>::FromConst(std::nullopt, "std::nullopt");
      if (!ud::get_stored_as_bool(result19)) {
        hstd::Opt<ud::S<hstd::unidata_dsl::test::Derived>> candidate20 = expression_runtime.try_as<hstd::unidata_dsl::test::Derived>(expr18);
        if (candidate20.has_value()) {
          ud::S<int64_t> const& expr21 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 499), (*candidate20), "id");
          ud::set_value(result19, expr21);
        }
      }
      ud::S<int64_t> const& expr22 = ud::eval_op<ud::OpId::OPT_VALUE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 501), result19);
      ud::S<int64_t> const& expr23 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
      ud::S<bool> const& expr24 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 497), expr22, expr23);
      ud::set_value(condition5, expr24);
    }
    ud::set_value(condition1, condition5);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr25 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.TypeCondOptional"), "poc.TypeCondOptional");
    return ud::VerifyResult::Error(ud::get_stored_value(expr25));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_TypeOf(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
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
  //             type_case typed_as='string' type_val='Base' binders='record'[Base]
  //                 type_of typed_as='string'
  //                     var typed_as='Base' str_val='record'
  //         const_str typed_as='string' str_val='Base'
  //
  hstd::ext::unidata::EvalRuntime expression_runtime = hstd::ext::unidata::EvalRuntime{ctx};
  __populate_expression_runtime(expression_runtime);
  auto const& expr0 = (this_obj);
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::TypeOf);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 511, ud::OpId::EQ);
    ud::S<hstd::unidata_dsl::test::Derived> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Derived>>(ud::get_context(ctx, "hstd_test_model.py", 512), expr0, "derived");
    ud::S<hstd::Vec<ud::UniDynamic>> const& expr6 = ud::eval_op<ud::OpId::WALK, ud::S<hstd::Vec<ud::UniDynamic>>>(ud::get_context(ctx, "hstd_test_model.py", 512), expression_runtime, expr5);
    ud::S<int64_t> const& expr7 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
    ud::UniDynamic const& expr8 = ud::eval_op<ud::OpId::LIST_AT, ud::UniDynamic>(ud::get_context(ctx, "hstd_test_model.py", 512), expr6, expr7);
    ud::S<ud::UniOpt<ud::S<hstd::Str>>> result9 = ud::S<ud::UniOpt<ud::S<hstd::Str>>>::FromConst(std::nullopt, "std::nullopt");
    if (!ud::get_stored_as_bool(result9)) {
      hstd::Opt<ud::S<hstd::unidata_dsl::test::Base>> candidate10 = expression_runtime.try_as<hstd::unidata_dsl::test::Base>(expr8);
      if (candidate10.has_value()) {
        ud::S<hstd::Str> const& expr11 = ud::eval_op<ud::OpId::TYPE_OF, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 513), expression_runtime, (*candidate10));
        ud::set_value(result9, expr11);
      }
    }
    if (!ud::get_stored_as_bool(result9)) {
      throw std::runtime_error{"No type case matched at hstd_test_model.py:511; expected one of: Base"};
    }
    ud::S<hstd::Str> const& expr12 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("Base"), "Base");
    ud::S<bool> const& expr13 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 511), ud::get_value_ref(result9), expr12);
    ud::set_value(condition1, expr13);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr14 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.TypeOf"), "poc.TypeOf");
    return ud::VerifyResult::Error(ud::get_stored_value(expr14));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_PathOf(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='PathOf'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     and typed_as='bool'
  //         eq typed_as='bool'
  //             str_format typed_as='string' str_val='{}'
  //                 path_of typed_as='path'
  //                     get_field typed_as='int64' str_val='number'
  //                         this typed_as='OperationChecks'
  //             const_str typed_as='string' str_val='/number'
  //         eq typed_as='bool'
  //             list_at typed_as='string'
  //                 map typed_as='list<string>' binders='number'[int64]
  //                     get_field typed_as='list<int64>' str_val='numbers'
  //                         this typed_as='OperationChecks'
  //                     str_format typed_as='string' str_val='{}'
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
  //                 type_case typed_as='string' type_val='Base' binders='record'[Base]
  //                     str_format typed_as='string' str_val='{}'
  //                         path_of typed_as='path'
  //                             var typed_as='Base' str_val='record'
  //             const_str typed_as='string' str_val='/derived'
  //
  hstd::ext::unidata::EvalRuntime expression_runtime = hstd::ext::unidata::EvalRuntime{ctx};
  __populate_expression_runtime(expression_runtime);
  auto const& expr0 = (this_obj);
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::PathOf);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 519, ud::OpId::AND);
    auto condition5 = ud::S<bool>::FromConst(true, "true");
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 520, ud::OpId::EQ);
      ud::S<int64_t> const& expr6 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 520), expr0, "number");
      ud::S<hstd::ext::unidata::UniPath> const& expr7 = ud::eval_op<ud::OpId::PATH_OF, ud::S<hstd::ext::unidata::UniPath>>(ud::get_context(ctx, "hstd_test_model.py", 520), expression_runtime, expr6);
      ud::S<hstd::Str> const& expr8 = ud::eval_op<ud::OpId::STR_FORMAT, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 520), eval_str_pattern("{}"), expr7);
      ud::S<hstd::Str> const& expr9 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("/number"), "/number");
      ud::S<bool> const& expr10 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 520), expr8, expr9);
      ud::set_value(condition5, expr10);
    }
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 521, ud::OpId::EQ);
      ud::S<hstd::Vec<ud::S<int64_t>>> const& expr11 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 522), expr0, "numbers");
      auto callback15 = [&](ud::S<int64_t> const& item12) -> ud::S<hstd::Str> {
                        // str_format typed_as='string' str_val='{}'
                        //     path_of typed_as='path'
                        //         var typed_as='int64' str_val='number'
                        //
                        ud::S<hstd::ext::unidata::UniPath> const& expr13 = ud::eval_op<ud::OpId::PATH_OF, ud::S<hstd::ext::unidata::UniPath>>(ud::get_context(ctx, "hstd_test_model.py", 524), expression_runtime, item12);
                        ud::S<hstd::Str> const& expr14 = ud::eval_op<ud::OpId::STR_FORMAT, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 524), eval_str_pattern("{}"), expr13);
                        return expr14;
                        };
      ud::S<hstd::Vec<ud::S<hstd::Str>>> const& expr16 = ud::eval_op<ud::OpId::MAP, ud::S<hstd::Vec<ud::S<hstd::Str>>>>(ud::get_context(ctx, "hstd_test_model.py", 521), expr11, callback15);
      ud::S<int64_t> const& expr17 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
      ud::S<hstd::Str> const& expr18 = ud::eval_op<ud::OpId::LIST_AT, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 525), expr16, expr17);
      ud::S<hstd::Str> const& expr19 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("/numbers/0"), "/numbers/0");
      ud::S<bool> const& expr20 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 521), expr18, expr19);
      ud::set_value(condition5, expr20);
    }
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 527, ud::OpId::EQ);
      ud::S<hstd::unidata_dsl::test::Derived> const& expr21 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Derived>>(ud::get_context(ctx, "hstd_test_model.py", 528), expr0, "derived");
      ud::S<hstd::Vec<ud::UniDynamic>> const& expr22 = ud::eval_op<ud::OpId::WALK, ud::S<hstd::Vec<ud::UniDynamic>>>(ud::get_context(ctx, "hstd_test_model.py", 528), expression_runtime, expr21);
      ud::S<int64_t> const& expr23 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
      ud::UniDynamic const& expr24 = ud::eval_op<ud::OpId::LIST_AT, ud::UniDynamic>(ud::get_context(ctx, "hstd_test_model.py", 528), expr22, expr23);
      ud::S<ud::UniOpt<ud::S<hstd::Str>>> result25 = ud::S<ud::UniOpt<ud::S<hstd::Str>>>::FromConst(std::nullopt, "std::nullopt");
      if (!ud::get_stored_as_bool(result25)) {
        hstd::Opt<ud::S<hstd::unidata_dsl::test::Base>> candidate26 = expression_runtime.try_as<hstd::unidata_dsl::test::Base>(expr24);
        if (candidate26.has_value()) {
          ud::S<hstd::ext::unidata::UniPath> const& expr27 = ud::eval_op<ud::OpId::PATH_OF, ud::S<hstd::ext::unidata::UniPath>>(ud::get_context(ctx, "hstd_test_model.py", 532), expression_runtime, (*candidate26));
          ud::S<hstd::Str> const& expr28 = ud::eval_op<ud::OpId::STR_FORMAT, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 532), eval_str_pattern("{}"), expr27);
          ud::set_value(result25, expr28);
        }
      }
      if (!ud::get_stored_as_bool(result25)) {
        throw std::runtime_error{"No type case matched at hstd_test_model.py:527; expected one of: Base"};
      }
      ud::S<hstd::Str> const& expr29 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("/derived"), "/derived");
      ud::S<bool> const& expr30 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 527), ud::get_value_ref(result25), expr29);
      ud::set_value(condition5, expr30);
    }
    ud::set_value(condition1, condition5);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr31 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.PathOf"), "poc.PathOf");
    return ud::VerifyResult::Error(ud::get_stored_value(expr31));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_EmptyCollections(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::OperationChecks>::RootValue(this_obj_ptr, ctx->getPath());
  // or typed_as='bool'
  //     not typed_as='bool'
  //         enum_is typed_as='bool' str_val='EmptyCollections'
  //             get_field typed_as='CheckKind' str_val='operation'
  //                 this typed_as='OperationChecks'
  //     and typed_as='bool'
  //         all typed_as='bool' binders='number'[int64]
  //             list_empty typed_as='list<int64>' type_val='list<int64>'
  //             lt typed_as='bool'
  //                 const_int typed_as='int64' int_val=0
  //                 var typed_as='int64' str_val='number'
  //         not typed_as='bool'
  //             exists typed_as='bool' binders='number'[int64]
  //                 list_empty typed_as='list<int64>' type_val='list<int64>'
  //                 lt typed_as='bool'
  //                     const_int typed_as='int64' int_val=0
  //                     var typed_as='int64' str_val='number'
  //         not typed_as='bool'
  //             exists_one typed_as='bool' binders='number'[int64]
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
  //                 map typed_as='list<int64>' binders='unused'[int64]
  //                     list_empty typed_as='list<int64>' type_val='list<int64>'
  //                     map_get typed_as='int64'
  //                         get_field typed_as='map<string, int64>' str_val='mapping'
  //                             this typed_as='OperationChecks'
  //                         const_str typed_as='string' str_val='absent'
  //             const_int typed_as='int64' int_val=0
  //         eq typed_as='bool'
  //             list_size typed_as='int64'
  //                 filter typed_as='list<int64>' binders='unused'[int64]
  //                     list_empty typed_as='list<int64>' type_val='list<int64>'
  //                     eq typed_as='bool'
  //                         opt_value typed_as='int64'
  //                             get_field typed_as='optional<int64>' str_val='optional'
  //                                 this typed_as='OperationChecks'
  //                         const_int typed_as='int64' int_val=0
  //             const_int typed_as='int64' int_val=0
  //         eq typed_as='bool'
  //             list_size typed_as='int64'
  //                 filter_map typed_as='list<int64>' binders='unused'[int64]
  //                     list_empty typed_as='list<int64>' type_val='list<int64>'
  //                     get_field typed_as='optional<int64>' str_val='optional'
  //                         this typed_as='OperationChecks'
  //             const_int typed_as='int64' int_val=0
  //         eq typed_as='bool'
  //             list_size typed_as='int64'
  //                 take_while typed_as='list<int64>' binders='unused'[int64]
  //                     list_empty typed_as='list<int64>' type_val='list<int64>'
  //                     eq typed_as='bool'
  //                         opt_value typed_as='int64'
  //                             get_field typed_as='optional<int64>' str_val='optional'
  //                                 this typed_as='OperationChecks'
  //                         const_int typed_as='int64' int_val=0
  //             const_int typed_as='int64' int_val=0
  //         eq typed_as='bool'
  //             map_size typed_as='int64'
  //                 group_by typed_as='map<int64, list<int64>>' binders='unused'[int64]
  //                     list_empty typed_as='list<int64>' type_val='list<int64>'
  //                     map_get typed_as='int64'
  //                         get_field typed_as='map<string, int64>' str_val='mapping'
  //                             this typed_as='OperationChecks'
  //                         const_str typed_as='string' str_val='absent'
  //             const_int typed_as='int64' int_val=0
  //         eq typed_as='bool'
  //             fold typed_as='int64' binders='acc'[int64], 'unused'[int64]
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
  auto condition1 = ud::S<bool>::FromConst(false, "false");
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 146, ud::OpId::NOT);
    ud::S<hstd::unidata_dsl::test::CheckKind> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr0, "operation");
    ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), expr2, hstd::unidata_dsl::test::CheckKind::EmptyCollections);
    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 146), (expr3));
    ud::set_value(condition1, expr4);
  }
  if (!(ud::get_stored_value(condition1))) {
    UNIDATA_SCOPE(ctx, "hstd_test_model.py", 540, ud::OpId::AND);
    auto condition5 = ud::S<bool>::FromConst(true, "true");
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 541, ud::OpId::ALL);
      ud::S<hstd::Vec<ud::S<int64_t>>> const& expr6 = ud::eval_op<ud::OpId::LIST_EMPTY, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 542));
      auto callback10 = [&](ud::S<int64_t> const& item7) -> ud::S<bool> {
                        // lt typed_as='bool'
                        //     const_int typed_as='int64' int_val=0
                        //     var typed_as='int64' str_val='number'
                        //
                        ud::S<int64_t> const& expr8 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                        ud::S<bool> const& expr9 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 544), expr8, item7);
                        return expr9;
                        };
      ud::S<bool> const& expr11 = ud::eval_op<ud::OpId::ALL, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 541), expr6, callback10);
      ud::set_value(condition5, expr11);
    }
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 546, ud::OpId::NOT);
      ud::S<hstd::Vec<ud::S<int64_t>>> const& expr12 = ud::eval_op<ud::OpId::LIST_EMPTY, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 547));
      auto callback16 = [&](ud::S<int64_t> const& item13) -> ud::S<bool> {
                        // lt typed_as='bool'
                        //     const_int typed_as='int64' int_val=0
                        //     var typed_as='int64' str_val='number'
                        //
                        ud::S<int64_t> const& expr14 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                        ud::S<bool> const& expr15 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 549), expr14, item13);
                        return expr15;
                        };
      ud::S<bool> const& expr17 = ud::eval_op<ud::OpId::EXISTS, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 546), expr12, callback16);
      ud::S<bool> const& expr18 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 546), (expr17));
      ud::set_value(condition5, expr18);
    }
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 551, ud::OpId::NOT);
      ud::S<hstd::Vec<ud::S<int64_t>>> const& expr19 = ud::eval_op<ud::OpId::LIST_EMPTY, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 552));
      auto callback23 = [&](ud::S<int64_t> const& item20) -> ud::S<bool> {
                        // lt typed_as='bool'
                        //     const_int typed_as='int64' int_val=0
                        //     var typed_as='int64' str_val='number'
                        //
                        ud::S<int64_t> const& expr21 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                        ud::S<bool> const& expr22 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 554), expr21, item20);
                        return expr22;
                        };
      ud::S<bool> const& expr24 = ud::eval_op<ud::OpId::EXISTS_ONE, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 551), expr19, callback23);
      ud::S<bool> const& expr25 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 551), (expr24));
      ud::set_value(condition5, expr25);
    }
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 556, ud::OpId::EQ);
      ud::S<hstd::Vec<ud::S<int64_t>>> const& expr26 = ud::eval_op<ud::OpId::LIST_EMPTY, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 556));
      ud::S<int64_t> const& expr27 = ud::eval_op<ud::OpId::SUM, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 556), expr26);
      ud::S<int64_t> const& expr28 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
      ud::S<bool> const& expr29 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 556), expr27, expr28);
      ud::set_value(condition5, expr29);
    }
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 557, ud::OpId::EQ);
      ud::S<hstd::Vec<ud::S<int64_t>>> const& expr30 = ud::eval_op<ud::OpId::LIST_EMPTY, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 558));
      auto callback35 = [&](ud::S<int64_t> const& item31) -> ud::S<int64_t> {
                        // map_get typed_as='int64'
                        //     get_field typed_as='map<string, int64>' str_val='mapping'
                        //         this typed_as='OperationChecks'
                        //     const_str typed_as='string' str_val='absent'
                        //
                        ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr32 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 560), expr0, "mapping");
                        ud::S<hstd::Str> const& expr33 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("absent"), "absent");
                        ud::S<int64_t> const& expr34 = ud::eval_op<ud::OpId::MAP_GET, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 560), expr32, expr33);
                        return expr34;
                        };
      ud::S<hstd::Vec<ud::S<int64_t>>> const& expr36 = ud::eval_op<ud::OpId::MAP, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 557), expr30, callback35);
      ud::S<int64_t> const& expr37 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 561), expr36);
      ud::S<int64_t> const& expr38 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
      ud::S<bool> const& expr39 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 557), expr37, expr38);
      ud::set_value(condition5, expr39);
    }
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 563, ud::OpId::EQ);
      ud::S<hstd::Vec<ud::S<int64_t>>> const& expr40 = ud::eval_op<ud::OpId::LIST_EMPTY, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 564));
      auto callback46 = [&](ud::S<int64_t> const& item41) -> ud::S<bool> {
                        // eq typed_as='bool'
                        //     opt_value typed_as='int64'
                        //         get_field typed_as='optional<int64>' str_val='optional'
                        //             this typed_as='OperationChecks'
                        //     const_int typed_as='int64' int_val=0
                        //
                        ud::S<hstd::Opt<ud::S<int64_t>>> const& expr42 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Opt<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 566), expr0, "optional");
                        ud::S<int64_t> const& expr43 = ud::eval_op<ud::OpId::OPT_VALUE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 566), expr42);
                        ud::S<int64_t> const& expr44 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                        ud::S<bool> const& expr45 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 566), expr43, expr44);
                        return expr45;
                        };
      ud::S<hstd::Vec<ud::S<int64_t>>> const& expr47 = ud::eval_op<ud::OpId::FILTER, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 563), expr40, callback46);
      ud::S<int64_t> const& expr48 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 567), expr47);
      ud::S<int64_t> const& expr49 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
      ud::S<bool> const& expr50 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 563), expr48, expr49);
      ud::set_value(condition5, expr50);
    }
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 569, ud::OpId::EQ);
      ud::S<hstd::Vec<ud::S<int64_t>>> const& expr51 = ud::eval_op<ud::OpId::LIST_EMPTY, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 570));
      auto callback54 = [&](ud::S<int64_t> const& item52) -> ud::S<hstd::Opt<ud::S<int64_t>>> {
                        // get_field typed_as='optional<int64>' str_val='optional'
                        //     this typed_as='OperationChecks'
                        //
                        ud::S<hstd::Opt<ud::S<int64_t>>> const& expr53 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Opt<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 572), expr0, "optional");
                        return expr53;
                        };
      ud::S<hstd::Vec<ud::S<int64_t>>> const& expr55 = ud::eval_op<ud::OpId::FILTER_MAP, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 569), expr51, callback54);
      ud::S<int64_t> const& expr56 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 573), expr55);
      ud::S<int64_t> const& expr57 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
      ud::S<bool> const& expr58 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 569), expr56, expr57);
      ud::set_value(condition5, expr58);
    }
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 575, ud::OpId::EQ);
      ud::S<hstd::Vec<ud::S<int64_t>>> const& expr59 = ud::eval_op<ud::OpId::LIST_EMPTY, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 576));
      auto callback65 = [&](ud::S<int64_t> const& item60) -> ud::S<bool> {
                        // eq typed_as='bool'
                        //     opt_value typed_as='int64'
                        //         get_field typed_as='optional<int64>' str_val='optional'
                        //             this typed_as='OperationChecks'
                        //     const_int typed_as='int64' int_val=0
                        //
                        ud::S<hstd::Opt<ud::S<int64_t>>> const& expr61 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Opt<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 578), expr0, "optional");
                        ud::S<int64_t> const& expr62 = ud::eval_op<ud::OpId::OPT_VALUE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 578), expr61);
                        ud::S<int64_t> const& expr63 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                        ud::S<bool> const& expr64 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 578), expr62, expr63);
                        return expr64;
                        };
      ud::S<hstd::Vec<ud::S<int64_t>>> const& expr66 = ud::eval_op<ud::OpId::TAKE_WHILE, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 575), expr59, callback65);
      ud::S<int64_t> const& expr67 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 579), expr66);
      ud::S<int64_t> const& expr68 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
      ud::S<bool> const& expr69 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 575), expr67, expr68);
      ud::set_value(condition5, expr69);
    }
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 581, ud::OpId::EQ);
      ud::S<hstd::Vec<ud::S<int64_t>>> const& expr70 = ud::eval_op<ud::OpId::LIST_EMPTY, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 582));
      auto callback75 = [&](ud::S<int64_t> const& item71) -> ud::S<int64_t> {
                        // map_get typed_as='int64'
                        //     get_field typed_as='map<string, int64>' str_val='mapping'
                        //         this typed_as='OperationChecks'
                        //     const_str typed_as='string' str_val='absent'
                        //
                        ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr72 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 584), expr0, "mapping");
                        ud::S<hstd::Str> const& expr73 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("absent"), "absent");
                        ud::S<int64_t> const& expr74 = ud::eval_op<ud::OpId::MAP_GET, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 584), expr72, expr73);
                        return expr74;
                        };
      ud::S<hstd::UnorderedMap<ud::S<int64_t>, ud::S<hstd::Vec<ud::S<int64_t>>>>> const& expr76 = ud::eval_op<ud::OpId::GROUP_BY, ud::S<hstd::UnorderedMap<ud::S<int64_t>, ud::S<hstd::Vec<ud::S<int64_t>>>>>>(ud::get_context(ctx, "hstd_test_model.py", 581), expr70, callback75);
      ud::S<int64_t> const& expr77 = ud::eval_op<ud::OpId::MAP_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 585), expr76);
      ud::S<int64_t> const& expr78 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
      ud::S<bool> const& expr79 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 581), expr77, expr78);
      ud::set_value(condition5, expr79);
    }
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 587, ud::OpId::EQ);
      ud::S<hstd::Vec<ud::S<int64_t>>> const& expr80 = ud::eval_op<ud::OpId::LIST_EMPTY, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 588));
      ud::S<int64_t> const& expr81 = ud::S<int64_t>::FromConst(static_cast<int64_t>(9), "9");
      auto callback82 = [&](ud::S<int64_t> const& item83, ud::S<int64_t> const& item84) -> ud::S<int64_t> {
                        // map_get typed_as='int64'
                        //     get_field typed_as='map<string, int64>' str_val='mapping'
                        //         this typed_as='OperationChecks'
                        //     const_str typed_as='string' str_val='absent'
                        //
                        ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr85 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 592), expr0, "mapping");
                        ud::S<hstd::Str> const& expr86 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("absent"), "absent");
                        ud::S<int64_t> const& expr87 = ud::eval_op<ud::OpId::MAP_GET, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 592), expr85, expr86);
                        return expr87;
                        };
      ud::S<int64_t> const& expr88 = ud::eval_op<ud::OpId::FOLD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 587), expr80, expr81, callback82);
      ud::S<int64_t> const& expr89 = ud::S<int64_t>::FromConst(static_cast<int64_t>(9), "9");
      ud::S<bool> const& expr90 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 587), expr88, expr89);
      ud::set_value(condition5, expr90);
    }
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 595, ud::OpId::EQ);
      ud::S<hstd::Vec<ud::S<int64_t>>> const& expr91 = ud::eval_op<ud::OpId::LIST_EMPTY, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 596));
      ud::S<hstd::Vec<ud::S<int64_t>>> const& expr92 = ud::eval_op<ud::OpId::LIST_EMPTY, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 597));
      ud::S<hstd::Vec<ud::S<int64_t>>> const& expr93 = ud::eval_op<ud::OpId::LIST_CONCAT, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 595), expr91, expr92);
      ud::S<int64_t> const& expr94 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 598), expr93);
      ud::S<int64_t> const& expr95 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
      ud::S<bool> const& expr96 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 595), expr94, expr95);
      ud::set_value(condition5, expr96);
    }
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 600, ud::OpId::EQ);
      ud::S<bool> const& expr97 = ud::S<bool>::FromConst(static_cast<bool>(true), "true");
      ud::S<ud::UniOpt<ud::S<int64_t>>> result101 = ud::S<ud::UniOpt<ud::S<int64_t>>>::FromConst(std::nullopt, "std::nullopt");
      if (ud::get_stored_value(expr97)) {
        ud::S<int64_t> const& expr98 = ud::S<int64_t>::FromConst(static_cast<int64_t>(42), "42");
        ud::set_value(result101, expr98);
      } else {
        ud::S<hstd::Vec<ud::S<int64_t>>> const& expr99 = ud::eval_op<ud::OpId::LIST_EMPTY, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 602));
        ud::S<int64_t> const& expr100 = ud::eval_op<ud::OpId::MIN, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 602), expr99);
        ud::set_value(result101, expr100);
      }
      ud::S<int64_t> const& expr102 = ud::S<int64_t>::FromConst(static_cast<int64_t>(42), "42");
      ud::S<bool> const& expr103 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 600), ud::get_value_ref(result101), expr102);
      ud::set_value(condition5, expr103);
    }
    if (ud::get_stored_value(condition5)) {
      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 605, ud::OpId::EQ);
      ud::S<bool> const& expr104 = ud::S<bool>::FromConst(static_cast<bool>(true), "true");
      ud::S<ud::UniOpt<ud::S<int64_t>>> result108 = ud::S<ud::UniOpt<ud::S<int64_t>>>::FromConst(std::nullopt, "std::nullopt");
      if (ud::get_stored_value(expr104)) {
        ud::S<int64_t> const& expr105 = ud::S<int64_t>::FromConst(static_cast<int64_t>(42), "42");
        ud::set_value(result108, expr105);
      } else {
        ud::S<hstd::Vec<ud::S<int64_t>>> const& expr106 = ud::eval_op<ud::OpId::LIST_EMPTY, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 607));
        ud::S<int64_t> const& expr107 = ud::eval_op<ud::OpId::MAX, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 607), expr106);
        ud::set_value(result108, expr107);
      }
      ud::S<int64_t> const& expr109 = ud::S<int64_t>::FromConst(static_cast<int64_t>(42), "42");
      ud::S<bool> const& expr110 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 605), ud::get_value_ref(result108), expr109);
      ud::set_value(condition5, expr110);
    }
    ud::set_value(condition1, condition5);
  }
  if (ud::get_stored_value(condition1)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr111 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.EmptyCollections"), "poc.EmptyCollections");
    return ud::VerifyResult::Error(ud::get_stored_value(expr111));
  }
}
hstd::ext::unidata::VerifyCheckCollection const* hstd::unidata_dsl::test::OperationChecks::get_unidata_checks() {
  static hstd::ext::unidata::VerifyCheckCollection checks
   = {{{hstd::ext::unidata::VerifyKey{"OperationChecks", std::nullopt},
        hstd::ext::unidata::VerifyCbList{
        hstd::ext::unidata::VerifyCb{&__check_record_poc_Eq},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_Ne},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_Lt},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_Le},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_Add},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_Sub},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_Mul},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_Div},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_ConstFloat},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_ConstBool},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_And},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_Or},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_Not},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_Cond},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_CondLazy},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_Let},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_All},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_Exists},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_ExistsOne},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_Map},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_Filter},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_FilterMap},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_TakeWhile},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_GroupBy},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_Fold},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_Walk},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_Sum},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_Min},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_Max},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_StrSize},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_StrMatches},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_StrFormat},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_ListSize},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_ListContains},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_ListAt},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_ListSlice},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_ListSliceBounds},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_ListConcat},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_ListEmpty},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_MapSize},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_MapContains},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_MapGet},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_MapInsert},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_MapReplace},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_MapKeys},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_MapValues},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_MapEmpty},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_OptHasValue},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_OptValue},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_CaseIs},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_CaseWhich},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_CaseField},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_EnumIs},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_NthGet},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_IsDerived},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_TypeCond},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_TypeCondOptional},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_TypeOf},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_PathOf},
        hstd::ext::unidata::VerifyCb{&__check_record_poc_EmptyCollections}
        }}}};
  return &checks;
}
void hstd::unidata_dsl::test::FieldChecks::__populate_expression_runtime(hstd::ext::unidata::EvalRuntime& expression_runtime) {
  expression_runtime.register_type<hstd::unidata_dsl::test::TrivialText>("TrivialText");
  expression_runtime.register_type<hstd::unidata_dsl::test::Base>("Base");
  expression_runtime.register_type<hstd::unidata_dsl::test::Derived>("Derived");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::First>("Choice::First");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::Second>("Choice::Second");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice>("Choice");
  expression_runtime.register_type<hstd::unidata_dsl::test::OperationChecks>("OperationChecks");
  expression_runtime.register_type<hstd::unidata_dsl::test::FieldChecks>("FieldChecks");
  expression_runtime.register_type<hstd::unidata_dsl::test::MessageChecks>("MessageChecks");
  expression_runtime.register_type<hstd::unidata_dsl::test::Node>("Node");
  expression_runtime.register_type<hstd::unidata_dsl::test::Edge>("Edge");
  expression_runtime.register_type<hstd::unidata_dsl::test::Graph>("Graph");
  expression_runtime.register_type<hstd::unidata_dsl::test::MultiValueCond>("MultiValueCond");
  expression_runtime.register_type<hstd::unidata_dsl::test::Status>("Status");
  expression_runtime.register_type<hstd::unidata_dsl::test::CheckKind>("CheckKind");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::Kind>("Choice::Kind");
  expression_runtime.register_base<hstd::unidata_dsl::test::Derived, hstd::unidata_dsl::test::Base>();
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::FieldChecks::__check_text_text_check(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::FieldChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::FieldChecks>::RootValue(this_obj_ptr, ctx->getPath());
  // lt typed_as='bool'
  //     const_int typed_as='int64' int_val=0
  //     str_size typed_as='int64'
  //         this typed_as='string'
  //
  auto const& expr0 = (this_obj.Field(&this_obj.get()->text, "text"));
  ud::S<int64_t> const& expr1 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
  ud::S<int64_t> const& expr2 = ud::eval_op<ud::OpId::STR_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 625), expr0);
  ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 625), expr1, expr2);
  if (ud::get_stored_value(expr3)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<int64_t> const& expr4 = ud::eval_op<ud::OpId::STR_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 626), expr0);
    ud::S<hstd::Str> const& expr5 = ud::eval_op<ud::OpId::STR_FORMAT, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 626), eval_str_pattern("text length is {}"), expr4);
    return ud::VerifyResult::Error(ud::get_stored_value(expr5));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::FieldChecks::__check_numbers_numbers_check(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::FieldChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::FieldChecks>::RootValue(this_obj_ptr, ctx->getPath());
  // all typed_as='bool' binders='number'[int64]
  //     this typed_as='list<int64>'
  //     lt typed_as='bool'
  //         const_int typed_as='int64' int_val=0
  //         var typed_as='int64' str_val='number'
  //
  auto const& expr0 = (this_obj.Field(&this_obj.get()->numbers, "numbers"));
  auto callback4 = [&](ud::S<int64_t> const& item1) -> ud::S<bool> {
                   // lt typed_as='bool'
                   //     const_int typed_as='int64' int_val=0
                   //     var typed_as='int64' str_val='number'
                   //
                   ud::S<int64_t> const& expr2 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                   ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 629), expr2, item1);
                   return expr3;
                   };
  ud::S<bool> const& expr5 = ud::eval_op<ud::OpId::ALL, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 629), expr0, callback4);
  if (ud::get_stored_value(expr5)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr6 = ud::eval_op<ud::OpId::STR_FORMAT, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 630), eval_str_pattern("values={}"), expr0);
    return ud::VerifyResult::Error(ud::get_stored_value(expr6));
  }
}
hstd::ext::unidata::VerifyCheckCollection const* hstd::unidata_dsl::test::FieldChecks::get_unidata_checks() {
  static hstd::ext::unidata::VerifyCheckCollection checks
   = {{{hstd::ext::unidata::VerifyKey{"FieldChecks", "text"},
        hstd::ext::unidata::VerifyCbList{
        hstd::ext::unidata::VerifyCb{&__check_text_text_check}
        }},
       {hstd::ext::unidata::VerifyKey{"FieldChecks", "numbers"},
        hstd::ext::unidata::VerifyCbList{
        hstd::ext::unidata::VerifyCb{&__check_numbers_numbers_check}
        }}}};
  return &checks;
}
void hstd::unidata_dsl::test::MessageChecks::__populate_expression_runtime(hstd::ext::unidata::EvalRuntime& expression_runtime) {
  expression_runtime.register_type<hstd::unidata_dsl::test::TrivialText>("TrivialText");
  expression_runtime.register_type<hstd::unidata_dsl::test::Base>("Base");
  expression_runtime.register_type<hstd::unidata_dsl::test::Derived>("Derived");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::First>("Choice::First");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::Second>("Choice::Second");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice>("Choice");
  expression_runtime.register_type<hstd::unidata_dsl::test::OperationChecks>("OperationChecks");
  expression_runtime.register_type<hstd::unidata_dsl::test::FieldChecks>("FieldChecks");
  expression_runtime.register_type<hstd::unidata_dsl::test::MessageChecks>("MessageChecks");
  expression_runtime.register_type<hstd::unidata_dsl::test::Node>("Node");
  expression_runtime.register_type<hstd::unidata_dsl::test::Edge>("Edge");
  expression_runtime.register_type<hstd::unidata_dsl::test::Graph>("Graph");
  expression_runtime.register_type<hstd::unidata_dsl::test::MultiValueCond>("MultiValueCond");
  expression_runtime.register_type<hstd::unidata_dsl::test::Status>("Status");
  expression_runtime.register_type<hstd::unidata_dsl::test::CheckKind>("CheckKind");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::Kind>("Choice::Kind");
  expression_runtime.register_base<hstd::unidata_dsl::test::Derived, hstd::unidata_dsl::test::Base>();
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::MessageChecks::__check_record_format_message(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::MessageChecks const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::MessageChecks>::RootValue(this_obj_ptr, ctx->getPath());
  // eq typed_as='bool'
  //     get_field typed_as='int64' str_val='number'
  //         this typed_as='MessageChecks'
  //     const_int typed_as='int64' int_val=6
  //
  auto const& expr0 = (this_obj);
  ud::S<int64_t> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 644), expr0, "number");
  ud::S<int64_t> const& expr2 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
  ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 644), expr1, expr2);
  if (ud::get_stored_value(expr3)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<int64_t> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 647), expr0, "number");
    ud::S<double> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<double>>(ud::get_context(ctx, "hstd_test_model.py", 648), expr0, "real");
    ud::S<double> const& expr6 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<double>>(ud::get_context(ctx, "hstd_test_model.py", 649), expr0, "real");
    ud::S<int64_t> const& expr7 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 650), expr0, "number");
    ud::S<int64_t> const& expr8 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 651), expr0, "number");
    ud::S<bool> const& expr9 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 652), expr0, "flag");
    ud::S<hstd::Str> const& expr10 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 653), expr0, "text");
    ud::S<hstd::Vec<ud::S<int64_t>>> const& expr11 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Vec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 654), expr0, "numbers");
    ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr12 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 655), expr0, "details");
    ud::S<hstd::Str> const& expr13 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("detail"), "detail");
    ud::S<int64_t> const& expr14 = ud::eval_op<ud::OpId::MAP_GET, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 655), expr12, expr13);
    ud::S<hstd::Str> const& expr15 = ud::eval_op<ud::OpId::STR_FORMAT, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 645), eval_str_pattern("n={} real={} sci={:e} hex={} oct={} flag={} text={} list={} lookup={}"), expr4, expr5, expr6, expr7, expr8, expr9, expr10, expr11, expr14);
    return ud::VerifyResult::Error(ud::get_stored_value(expr15));
  }
}
hstd::ext::unidata::VerifyCheckCollection const* hstd::unidata_dsl::test::MessageChecks::get_unidata_checks() {
  static hstd::ext::unidata::VerifyCheckCollection checks
   = {{{hstd::ext::unidata::VerifyKey{"MessageChecks", std::nullopt},
        hstd::ext::unidata::VerifyCbList{
        hstd::ext::unidata::VerifyCb{&__check_record_format_message}
        }}}};
  return &checks;
}
void hstd::unidata_dsl::test::Graph::__populate_expression_runtime(hstd::ext::unidata::EvalRuntime& expression_runtime) {
  expression_runtime.register_type<hstd::unidata_dsl::test::TrivialText>("TrivialText");
  expression_runtime.register_type<hstd::unidata_dsl::test::Base>("Base");
  expression_runtime.register_type<hstd::unidata_dsl::test::Derived>("Derived");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::First>("Choice::First");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::Second>("Choice::Second");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice>("Choice");
  expression_runtime.register_type<hstd::unidata_dsl::test::OperationChecks>("OperationChecks");
  expression_runtime.register_type<hstd::unidata_dsl::test::FieldChecks>("FieldChecks");
  expression_runtime.register_type<hstd::unidata_dsl::test::MessageChecks>("MessageChecks");
  expression_runtime.register_type<hstd::unidata_dsl::test::Node>("Node");
  expression_runtime.register_type<hstd::unidata_dsl::test::Edge>("Edge");
  expression_runtime.register_type<hstd::unidata_dsl::test::Graph>("Graph");
  expression_runtime.register_type<hstd::unidata_dsl::test::MultiValueCond>("MultiValueCond");
  expression_runtime.register_type<hstd::unidata_dsl::test::Status>("Status");
  expression_runtime.register_type<hstd::unidata_dsl::test::CheckKind>("CheckKind");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::Kind>("Choice::Kind");
  expression_runtime.register_base<hstd::unidata_dsl::test::Derived, hstd::unidata_dsl::test::Base>();
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::Graph::__check_record_graph_unique_node_ids(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::Graph const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::Graph>::RootValue(this_obj_ptr, ctx->getPath());
  // all typed_as='bool' binders='group'[list<Node>]
  //     map_values typed_as='list<list<Node>>'
  //         group_by typed_as='map<string, list<Node>>' binders='node'[Node]
  //             filter_map typed_as='list<Node>' binders='node_any'[dyn<Graph>]
  //                 walk typed_as='list<dyn<Graph>>'
  //                     this typed_as='Graph'
  //                 type_cond typed_as='optional<Node>' bool_val=True
  //                     var typed_as='dyn<Graph>' str_val='node_any'
  //                     type_case typed_as='Node' type_val='Node' binders='node'[Node]
  //                         var typed_as='Node' str_val='node'
  //             get_field typed_as='string' str_val='id'
  //                 var typed_as='Node' str_val='node'
  //     le typed_as='bool'
  //         list_size typed_as='int64'
  //             var typed_as='list<Node>' str_val='group'
  //         const_int typed_as='int64' int_val=1
  //
  hstd::ext::unidata::EvalRuntime expression_runtime = hstd::ext::unidata::EvalRuntime{ctx};
  __populate_expression_runtime(expression_runtime);
  auto const& expr0 = (this_obj);
  ud::S<hstd::Vec<ud::UniDynamic>> const& expr1 = ud::eval_op<ud::OpId::WALK, ud::S<hstd::Vec<ud::UniDynamic>>>(ud::get_context(ctx, "hstd_test_model.py", 672), expression_runtime, expr0);
  auto callback5 = [&](ud::UniDynamic const& item2) -> ud::S<hstd::Opt<ud::S<hstd::unidata_dsl::test::Node>>> {
                   // type_cond typed_as='optional<Node>' bool_val=True
                   //     var typed_as='dyn<Graph>' str_val='node_any'
                   //     type_case typed_as='Node' type_val='Node' binders='node'[Node]
                   //         var typed_as='Node' str_val='node'
                   //
                   ud::S<ud::UniOpt<ud::S<hstd::unidata_dsl::test::Node>>> result3 = ud::S<ud::UniOpt<ud::S<hstd::unidata_dsl::test::Node>>>::FromConst(std::nullopt, "std::nullopt");
                   if (!ud::get_stored_as_bool(result3)) {
                     hstd::Opt<ud::S<hstd::unidata_dsl::test::Node>> candidate4 = expression_runtime.try_as<hstd::unidata_dsl::test::Node>(item2);
                     if (candidate4.has_value()) {
                       ud::set_value(result3, (*candidate4));
                     }
                   }
                   return result3;
                   };
  ud::S<hstd::Vec<ud::S<hstd::unidata_dsl::test::Node>>> const& expr6 = ud::eval_op<ud::OpId::FILTER_MAP, ud::S<hstd::Vec<ud::S<hstd::unidata_dsl::test::Node>>>>(ud::get_context(ctx, "hstd_test_model.py", 671), expr1, callback5);
  auto callback9 = [&](ud::S<hstd::unidata_dsl::test::Node> const& item7) -> ud::S<hstd::Str> {
                   // get_field typed_as='string' str_val='id'
                   //     var typed_as='Node' str_val='node'
                   //
                   ud::S<hstd::Str> const& expr8 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 704), item7, "id");
                   return expr8;
                   };
  ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<hstd::Vec<ud::S<hstd::unidata_dsl::test::Node>>>>> const& expr10 = ud::eval_op<ud::OpId::GROUP_BY, ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<hstd::Vec<ud::S<hstd::unidata_dsl::test::Node>>>>>>(ud::get_context(ctx, "hstd_test_model.py", 701), expr6, callback9);
  ud::S<hstd::Vec<ud::S<hstd::Vec<ud::S<hstd::unidata_dsl::test::Node>>>>> const& expr11 = ud::eval_op<ud::OpId::MAP_VALUES, ud::S<hstd::Vec<ud::S<hstd::Vec<ud::S<hstd::unidata_dsl::test::Node>>>>>>(ud::get_context(ctx, "hstd_test_model.py", 705), expr10);
  auto callback16 = [&](ud::S<hstd::Vec<ud::S<hstd::unidata_dsl::test::Node>>> const& item12) -> ud::S<bool> {
                    // le typed_as='bool'
                    //     list_size typed_as='int64'
                    //         var typed_as='list<Node>' str_val='group'
                    //     const_int typed_as='int64' int_val=1
                    //
                    ud::S<int64_t> const& expr13 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 726), item12);
                    ud::S<int64_t> const& expr14 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
                    ud::S<bool> const& expr15 = ud::eval_op<ud::OpId::LE, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 726), expr13, expr14);
                    return expr15;
                    };
  ud::S<bool> const& expr17 = ud::eval_op<ud::OpId::ALL, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 723), expr11, callback16);
  if (ud::get_stored_value(expr17)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Vec<ud::UniDynamic>> const& expr18 = ud::eval_op<ud::OpId::WALK, ud::S<hstd::Vec<ud::UniDynamic>>>(ud::get_context(ctx, "hstd_test_model.py", 672), expression_runtime, expr0);
    auto callback22 = [&](ud::UniDynamic const& item19) -> ud::S<hstd::Opt<ud::S<hstd::unidata_dsl::test::Node>>> {
                      // type_cond typed_as='optional<Node>' bool_val=True
                      //     var typed_as='dyn<Graph>' str_val='node_any'
                      //     type_case typed_as='Node' type_val='Node' binders='node'[Node]
                      //         var typed_as='Node' str_val='node'
                      //
                      ud::S<ud::UniOpt<ud::S<hstd::unidata_dsl::test::Node>>> result20 = ud::S<ud::UniOpt<ud::S<hstd::unidata_dsl::test::Node>>>::FromConst(std::nullopt, "std::nullopt");
                      if (!ud::get_stored_as_bool(result20)) {
                        hstd::Opt<ud::S<hstd::unidata_dsl::test::Node>> candidate21 = expression_runtime.try_as<hstd::unidata_dsl::test::Node>(item19);
                        if (candidate21.has_value()) {
                          ud::set_value(result20, (*candidate21));
                        }
                      }
                      return result20;
                      };
    ud::S<hstd::Vec<ud::S<hstd::unidata_dsl::test::Node>>> const& expr23 = ud::eval_op<ud::OpId::FILTER_MAP, ud::S<hstd::Vec<ud::S<hstd::unidata_dsl::test::Node>>>>(ud::get_context(ctx, "hstd_test_model.py", 671), expr18, callback22);
    auto callback26 = [&](ud::S<hstd::unidata_dsl::test::Node> const& item24) -> ud::S<hstd::Str> {
                      // get_field typed_as='string' str_val='id'
                      //     var typed_as='Node' str_val='node'
                      //
                      ud::S<hstd::Str> const& expr25 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 704), item24, "id");
                      return expr25;
                      };
    ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<hstd::Vec<ud::S<hstd::unidata_dsl::test::Node>>>>> const& expr27 = ud::eval_op<ud::OpId::GROUP_BY, ud::S<hstd::UnorderedMap<ud::S<hstd::Str>, ud::S<hstd::Vec<ud::S<hstd::unidata_dsl::test::Node>>>>>>(ud::get_context(ctx, "hstd_test_model.py", 701), expr23, callback26);
    ud::S<hstd::Vec<ud::S<hstd::Vec<ud::S<hstd::unidata_dsl::test::Node>>>>> const& expr28 = ud::eval_op<ud::OpId::MAP_VALUES, ud::S<hstd::Vec<ud::S<hstd::Vec<ud::S<hstd::unidata_dsl::test::Node>>>>>>(ud::get_context(ctx, "hstd_test_model.py", 705), expr27);
    auto callback33 = [&](ud::S<hstd::Vec<ud::S<hstd::unidata_dsl::test::Node>>> const& item29) -> ud::S<bool> {
                      // lt typed_as='bool'
                      //     const_int typed_as='int64' int_val=1
                      //     list_size typed_as='int64'
                      //         var typed_as='list<Node>' str_val='group'
                      //
                      ud::S<int64_t> const& expr30 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
                      ud::S<int64_t> const& expr31 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 713), item29);
                      ud::S<bool> const& expr32 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 713), expr30, expr31);
                      return expr32;
                      };
    ud::S<hstd::Vec<ud::S<hstd::Vec<ud::S<hstd::unidata_dsl::test::Node>>>>> const& expr34 = ud::eval_op<ud::OpId::FILTER, ud::S<hstd::Vec<ud::S<hstd::Vec<ud::S<hstd::unidata_dsl::test::Node>>>>>>(ud::get_context(ctx, "hstd_test_model.py", 710), expr28, callback33);
    auto callback40 = [&](ud::S<hstd::Vec<ud::S<hstd::unidata_dsl::test::Node>>> const& item35) -> ud::S<hstd::Vec<ud::S<hstd::ext::unidata::UniPath>>> {
                      // map typed_as='list<path>' binders='node'[Node]
                      //     var typed_as='list<Node>' str_val='group'
                      //     path_of typed_as='path'
                      //         var typed_as='Node' str_val='node'
                      //
                      auto callback38 = [&](ud::S<hstd::unidata_dsl::test::Node> const& item36) -> ud::S<hstd::ext::unidata::UniPath> {
                                        // path_of typed_as='path'
                                        //     var typed_as='Node' str_val='node'
                                        //
                                        ud::S<hstd::ext::unidata::UniPath> const& expr37 = ud::eval_op<ud::OpId::PATH_OF, ud::S<hstd::ext::unidata::UniPath>>(ud::get_context(ctx, "hstd_test_model.py", 736), expression_runtime, item36);
                                        return expr37;
                                        };
                      ud::S<hstd::Vec<ud::S<hstd::ext::unidata::UniPath>>> const& expr39 = ud::eval_op<ud::OpId::MAP, ud::S<hstd::Vec<ud::S<hstd::ext::unidata::UniPath>>>>(ud::get_context(ctx, "hstd_test_model.py", 733), item35, callback38);
                      return expr39;
                      };
    ud::S<hstd::Vec<ud::S<hstd::Vec<ud::S<hstd::ext::unidata::UniPath>>>>> const& expr41 = ud::eval_op<ud::OpId::MAP, ud::S<hstd::Vec<ud::S<hstd::Vec<ud::S<hstd::ext::unidata::UniPath>>>>>>(ud::get_context(ctx, "hstd_test_model.py", 730), expr34, callback40);
    ud::S<hstd::Str> const& expr42 = ud::eval_op<ud::OpId::STR_FORMAT, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 728), eval_str_pattern("duplicate node ids at {}"), expr41);
    return ud::VerifyResult::Error(ud::get_stored_value(expr42));
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::Graph::__check_record_graph_no_dangling_edges(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::Graph const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::Graph>::RootValue(this_obj_ptr, ctx->getPath());
  // let typed_as='bool' binders='ids'[list<string>]
  //     map typed_as='list<string>' binders='node'[Node]
  //         filter_map typed_as='list<Node>' binders='node_any'[dyn<Graph>]
  //             walk typed_as='list<dyn<Graph>>'
  //                 this typed_as='Graph'
  //             type_cond typed_as='optional<Node>' bool_val=True
  //                 var typed_as='dyn<Graph>' str_val='node_any'
  //                 type_case typed_as='Node' type_val='Node' binders='node'[Node]
  //                     var typed_as='Node' str_val='node'
  //         get_field typed_as='string' str_val='id'
  //             var typed_as='Node' str_val='node'
  //     all typed_as='bool' binders='edge'[Edge]
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
  __populate_expression_runtime(expression_runtime);
  auto const& expr0 = (this_obj);
  ud::S<hstd::Vec<ud::UniDynamic>> const& expr1 = ud::eval_op<ud::OpId::WALK, ud::S<hstd::Vec<ud::UniDynamic>>>(ud::get_context(ctx, "hstd_test_model.py", 672), expression_runtime, expr0);
  auto callback5 = [&](ud::UniDynamic const& item2) -> ud::S<hstd::Opt<ud::S<hstd::unidata_dsl::test::Node>>> {
                   // type_cond typed_as='optional<Node>' bool_val=True
                   //     var typed_as='dyn<Graph>' str_val='node_any'
                   //     type_case typed_as='Node' type_val='Node' binders='node'[Node]
                   //         var typed_as='Node' str_val='node'
                   //
                   ud::S<ud::UniOpt<ud::S<hstd::unidata_dsl::test::Node>>> result3 = ud::S<ud::UniOpt<ud::S<hstd::unidata_dsl::test::Node>>>::FromConst(std::nullopt, "std::nullopt");
                   if (!ud::get_stored_as_bool(result3)) {
                     hstd::Opt<ud::S<hstd::unidata_dsl::test::Node>> candidate4 = expression_runtime.try_as<hstd::unidata_dsl::test::Node>(item2);
                     if (candidate4.has_value()) {
                       ud::set_value(result3, (*candidate4));
                     }
                   }
                   return result3;
                   };
  ud::S<hstd::Vec<ud::S<hstd::unidata_dsl::test::Node>>> const& expr6 = ud::eval_op<ud::OpId::FILTER_MAP, ud::S<hstd::Vec<ud::S<hstd::unidata_dsl::test::Node>>>>(ud::get_context(ctx, "hstd_test_model.py", 671), expr1, callback5);
  auto callback9 = [&](ud::S<hstd::unidata_dsl::test::Node> const& item7) -> ud::S<hstd::Str> {
                   // get_field typed_as='string' str_val='id'
                   //     var typed_as='Node' str_val='node'
                   //
                   ud::S<hstd::Str> const& expr8 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 687), item7, "id");
                   return expr8;
                   };
  ud::S<hstd::Vec<ud::S<hstd::Str>>> const& expr10 = ud::eval_op<ud::OpId::MAP, ud::S<hstd::Vec<ud::S<hstd::Str>>>>(ud::get_context(ctx, "hstd_test_model.py", 684), expr6, callback9);
  ud::S<hstd::Vec<ud::S<hstd::unidata_dsl::test::Edge>>> const& expr11 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Vec<ud::S<hstd::unidata_dsl::test::Edge>>>>(ud::get_context(ctx, "hstd_test_model.py", 748), expr0, "edges");
  auto callback18 = [&](ud::S<hstd::unidata_dsl::test::Edge> const& item12) -> ud::S<bool> {
                    // and typed_as='bool'
                    //     list_contains typed_as='bool'
                    //         var typed_as='list<string>' str_val='ids'
                    //         get_field typed_as='string' str_val='source'
                    //             var typed_as='Edge' str_val='edge'
                    //     list_contains typed_as='bool'
                    //         var typed_as='list<string>' str_val='ids'
                    //         get_field typed_as='string' str_val='target'
                    //             var typed_as='Edge' str_val='edge'
                    //
                    auto condition13 = ud::S<bool>::FromConst(true, "true");
                    if (ud::get_stored_value(condition13)) {
                      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 694, ud::OpId::LIST_CONTAINS);
                      ud::S<hstd::Str> const& expr14 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 694), item12, "source");
                      ud::S<bool> const& expr15 = ud::eval_op<ud::OpId::LIST_CONTAINS, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 694), expr10, expr14);
                      ud::set_value(condition13, expr15);
                    }
                    if (ud::get_stored_value(condition13)) {
                      UNIDATA_SCOPE(ctx, "hstd_test_model.py", 695, ud::OpId::LIST_CONTAINS);
                      ud::S<hstd::Str> const& expr16 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 695), item12, "target");
                      ud::S<bool> const& expr17 = ud::eval_op<ud::OpId::LIST_CONTAINS, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 695), expr10, expr16);
                      ud::set_value(condition13, expr17);
                    }
                    return condition13;
                    };
  ud::S<bool> const& expr19 = ud::eval_op<ud::OpId::ALL, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 747), expr11, callback18);
  if (ud::get_stored_value(expr19)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Vec<ud::UniDynamic>> const& expr20 = ud::eval_op<ud::OpId::WALK, ud::S<hstd::Vec<ud::UniDynamic>>>(ud::get_context(ctx, "hstd_test_model.py", 672), expression_runtime, expr0);
    auto callback24 = [&](ud::UniDynamic const& item21) -> ud::S<hstd::Opt<ud::S<hstd::unidata_dsl::test::Node>>> {
                      // type_cond typed_as='optional<Node>' bool_val=True
                      //     var typed_as='dyn<Graph>' str_val='node_any'
                      //     type_case typed_as='Node' type_val='Node' binders='node'[Node]
                      //         var typed_as='Node' str_val='node'
                      //
                      ud::S<ud::UniOpt<ud::S<hstd::unidata_dsl::test::Node>>> result22 = ud::S<ud::UniOpt<ud::S<hstd::unidata_dsl::test::Node>>>::FromConst(std::nullopt, "std::nullopt");
                      if (!ud::get_stored_as_bool(result22)) {
                        hstd::Opt<ud::S<hstd::unidata_dsl::test::Node>> candidate23 = expression_runtime.try_as<hstd::unidata_dsl::test::Node>(item21);
                        if (candidate23.has_value()) {
                          ud::set_value(result22, (*candidate23));
                        }
                      }
                      return result22;
                      };
    ud::S<hstd::Vec<ud::S<hstd::unidata_dsl::test::Node>>> const& expr25 = ud::eval_op<ud::OpId::FILTER_MAP, ud::S<hstd::Vec<ud::S<hstd::unidata_dsl::test::Node>>>>(ud::get_context(ctx, "hstd_test_model.py", 671), expr20, callback24);
    auto callback28 = [&](ud::S<hstd::unidata_dsl::test::Node> const& item26) -> ud::S<hstd::Str> {
                      // get_field typed_as='string' str_val='id'
                      //     var typed_as='Node' str_val='node'
                      //
                      ud::S<hstd::Str> const& expr27 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 687), item26, "id");
                      return expr27;
                      };
    ud::S<hstd::Vec<ud::S<hstd::Str>>> const& expr29 = ud::eval_op<ud::OpId::MAP, ud::S<hstd::Vec<ud::S<hstd::Str>>>>(ud::get_context(ctx, "hstd_test_model.py", 684), expr25, callback28);
    ud::S<hstd::Vec<ud::S<hstd::unidata_dsl::test::Edge>>> const& expr30 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Vec<ud::S<hstd::unidata_dsl::test::Edge>>>>(ud::get_context(ctx, "hstd_test_model.py", 760), expr0, "edges");
    auto callback38 = [&](ud::S<hstd::unidata_dsl::test::Edge> const& item31) -> ud::S<bool> {
                      // not typed_as='bool'
                      //     and typed_as='bool'
                      //         list_contains typed_as='bool'
                      //             var typed_as='list<string>' str_val='ids'
                      //             get_field typed_as='string' str_val='source'
                      //                 var typed_as='Edge' str_val='edge'
                      //         list_contains typed_as='bool'
                      //             var typed_as='list<string>' str_val='ids'
                      //             get_field typed_as='string' str_val='target'
                      //                 var typed_as='Edge' str_val='edge'
                      //
                      auto condition32 = ud::S<bool>::FromConst(true, "true");
                      if (ud::get_stored_value(condition32)) {
                        UNIDATA_SCOPE(ctx, "hstd_test_model.py", 694, ud::OpId::LIST_CONTAINS);
                        ud::S<hstd::Str> const& expr33 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 694), item31, "source");
                        ud::S<bool> const& expr34 = ud::eval_op<ud::OpId::LIST_CONTAINS, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 694), expr29, expr33);
                        ud::set_value(condition32, expr34);
                      }
                      if (ud::get_stored_value(condition32)) {
                        UNIDATA_SCOPE(ctx, "hstd_test_model.py", 695, ud::OpId::LIST_CONTAINS);
                        ud::S<hstd::Str> const& expr35 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 695), item31, "target");
                        ud::S<bool> const& expr36 = ud::eval_op<ud::OpId::LIST_CONTAINS, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 695), expr29, expr35);
                        ud::set_value(condition32, expr36);
                      }
                      ud::S<bool> const& expr37 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 762), (condition32));
                      return expr37;
                      };
    ud::S<hstd::Vec<ud::S<hstd::unidata_dsl::test::Edge>>> const& expr39 = ud::eval_op<ud::OpId::FILTER, ud::S<hstd::Vec<ud::S<hstd::unidata_dsl::test::Edge>>>>(ud::get_context(ctx, "hstd_test_model.py", 759), expr30, callback38);
    auto callback42 = [&](ud::S<hstd::unidata_dsl::test::Edge> const& item40) -> ud::S<hstd::ext::unidata::UniPath> {
                      // path_of typed_as='path'
                      //     var typed_as='Edge' str_val='edge'
                      //
                      ud::S<hstd::ext::unidata::UniPath> const& expr41 = ud::eval_op<ud::OpId::PATH_OF, ud::S<hstd::ext::unidata::UniPath>>(ud::get_context(ctx, "hstd_test_model.py", 765), expression_runtime, item40);
                      return expr41;
                      };
    ud::S<hstd::Vec<ud::S<hstd::ext::unidata::UniPath>>> const& expr43 = ud::eval_op<ud::OpId::MAP, ud::S<hstd::Vec<ud::S<hstd::ext::unidata::UniPath>>>>(ud::get_context(ctx, "hstd_test_model.py", 758), expr39, callback42);
    ud::S<hstd::Str> const& expr44 = ud::eval_op<ud::OpId::STR_FORMAT, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 756), eval_str_pattern("dangling edges at {}"), expr43);
    return ud::VerifyResult::Error(ud::get_stored_value(expr44));
  }
}
hstd::ext::unidata::VerifyCheckCollection const* hstd::unidata_dsl::test::Graph::get_unidata_checks() {
  static hstd::ext::unidata::VerifyCheckCollection checks
   = {{{hstd::ext::unidata::VerifyKey{"Graph", std::nullopt},
        hstd::ext::unidata::VerifyCbList{
        hstd::ext::unidata::VerifyCb{&__check_record_graph_unique_node_ids},
        hstd::ext::unidata::VerifyCb{&__check_record_graph_no_dangling_edges}
        }}}};
  return &checks;
}
void hstd::unidata_dsl::test::MultiValueCond::__populate_expression_runtime(hstd::ext::unidata::EvalRuntime& expression_runtime) {
  expression_runtime.register_type<hstd::unidata_dsl::test::TrivialText>("TrivialText");
  expression_runtime.register_type<hstd::unidata_dsl::test::Base>("Base");
  expression_runtime.register_type<hstd::unidata_dsl::test::Derived>("Derived");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::First>("Choice::First");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::Second>("Choice::Second");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice>("Choice");
  expression_runtime.register_type<hstd::unidata_dsl::test::OperationChecks>("OperationChecks");
  expression_runtime.register_type<hstd::unidata_dsl::test::FieldChecks>("FieldChecks");
  expression_runtime.register_type<hstd::unidata_dsl::test::MessageChecks>("MessageChecks");
  expression_runtime.register_type<hstd::unidata_dsl::test::Node>("Node");
  expression_runtime.register_type<hstd::unidata_dsl::test::Edge>("Edge");
  expression_runtime.register_type<hstd::unidata_dsl::test::Graph>("Graph");
  expression_runtime.register_type<hstd::unidata_dsl::test::MultiValueCond>("MultiValueCond");
  expression_runtime.register_type<hstd::unidata_dsl::test::Status>("Status");
  expression_runtime.register_type<hstd::unidata_dsl::test::CheckKind>("CheckKind");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::Kind>("Choice::Kind");
  expression_runtime.register_base<hstd::unidata_dsl::test::Derived, hstd::unidata_dsl::test::Base>();
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::MultiValueCond::__check_field_field_check(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj_ptr = static_cast<hstd::unidata_dsl::test::MultiValueCond const*>(value);
  auto this_obj = ud::S<hstd::unidata_dsl::test::MultiValueCond>::RootValue(this_obj_ptr, ctx->getPath());
  // cond typed_as='bool'
  //     eq typed_as='bool'
  //         this typed_as='int64'
  //         const_int typed_as='int64' int_val=1
  //     const_bool typed_as='bool' bool_val=True
  //     cond typed_as='bool'
  //         ne typed_as='bool'
  //             this typed_as='int64'
  //             const_int typed_as='int64' int_val=1
  //         const_bool typed_as='bool' bool_val=False
  //         const_bool typed_as='bool' bool_val=True
  //
  auto const& expr0 = (this_obj.Field(&this_obj.get()->field, "field"));
  ud::S<int64_t> const& expr1 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
  ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 775), expr0, expr1);
  ud::S<ud::UniOpt<ud::S<bool>>> result9 = ud::S<ud::UniOpt<ud::S<bool>>>::FromConst(std::nullopt, "std::nullopt");
  if (ud::get_stored_value(expr2)) {
    ud::S<bool> const& expr3 = ud::S<bool>::FromConst(static_cast<bool>(true), "true");
    ud::set_value(result9, expr3);
  } else {
    ud::S<int64_t> const& expr4 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
    ud::S<bool> const& expr5 = ud::eval_op<ud::OpId::NE, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 776), expr0, expr4);
    ud::S<ud::UniOpt<ud::S<bool>>> result8 = ud::S<ud::UniOpt<ud::S<bool>>>::FromConst(std::nullopt, "std::nullopt");
    if (ud::get_stored_value(expr5)) {
      ud::S<bool> const& expr6 = ud::S<bool>::FromConst(static_cast<bool>(false), "false");
      ud::set_value(result8, expr6);
    } else {
      ud::S<bool> const& expr7 = ud::S<bool>::FromConst(static_cast<bool>(true), "true");
      ud::set_value(result8, expr7);
    }
    ud::set_value(result9, ud::get_value_ref(result8));
  }
  if (ud::get_stored_value(ud::get_value_ref(result9))) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<int64_t> const& expr10 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
    ud::S<bool> const& expr11 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 781), expr0, expr10);
    ud::S<ud::UniOpt<ud::S<hstd::Str>>> result29 = ud::S<ud::UniOpt<ud::S<hstd::Str>>>::FromConst(std::nullopt, "std::nullopt");
    if (ud::get_stored_value(expr11)) {
      ud::S<hstd::Str> const& expr12 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("field bad: value two"), "field bad: value two");
      ud::set_value(result29, expr12);
    } else {
      auto condition13 = ud::S<bool>::FromConst(true, "true");
      if (ud::get_stored_value(condition13)) {
        UNIDATA_SCOPE(ctx, "hstd_test_model.py", 785, ud::OpId::LT);
        ud::S<int64_t> const& expr14 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
        ud::S<bool> const& expr15 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 785), expr14, expr0);
        ud::set_value(condition13, expr15);
      }
      if (ud::get_stored_value(condition13)) {
        UNIDATA_SCOPE(ctx, "hstd_test_model.py", 785, ud::OpId::LT);
        ud::S<int64_t> const& expr16 = ud::S<int64_t>::FromConst(static_cast<int64_t>(10), "10");
        ud::S<bool> const& expr17 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 785), expr0, expr16);
        ud::set_value(condition13, expr17);
      }
      ud::S<ud::UniOpt<ud::S<hstd::Str>>> result28 = ud::S<ud::UniOpt<ud::S<hstd::Str>>>::FromConst(std::nullopt, "std::nullopt");
      if (ud::get_stored_value(condition13)) {
        ud::S<hstd::Str> const& expr18 = ud::eval_op<ud::OpId::STR_FORMAT, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 786), eval_str_pattern("mid-range invalid value: {}"), expr0);
        ud::set_value(result28, expr18);
      } else {
        ud::S<int64_t> const& expr19 = ud::S<int64_t>::FromConst(static_cast<int64_t>(10), "10");
        ud::S<bool> const& expr20 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 789), expr0, expr19);
        ud::S<ud::UniOpt<ud::S<hstd::Str>>> result27 = ud::S<ud::UniOpt<ud::S<hstd::Str>>>::FromConst(std::nullopt, "std::nullopt");
        if (ud::get_stored_value(expr20)) {
          ud::S<hstd::Str> const& expr21 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("10, special-case number"), "10, special-case number");
          ud::set_value(result27, expr21);
        } else {
          ud::S<int64_t> const& expr22 = ud::S<int64_t>::FromConst(static_cast<int64_t>(10), "10");
          ud::S<bool> const& expr23 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 793), expr22, expr0);
          ud::S<ud::UniOpt<ud::S<hstd::Str>>> result26 = ud::S<ud::UniOpt<ud::S<hstd::Str>>>::FromConst(std::nullopt, "std::nullopt");
          if (ud::get_stored_value(expr23)) {
            ud::S<hstd::Str> const& expr24 = ud::eval_op<ud::OpId::STR_FORMAT, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 794), eval_str_pattern("very large invalid value: {}"), expr0);
            ud::set_value(result26, expr24);
          } else {
            ud::S<hstd::Str> const& expr25 = ud::eval_op<ud::OpId::STR_FORMAT, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 796), eval_str_pattern("unexpected range of invalid-ness {}"), expr0);
            ud::set_value(result26, expr25);
          }
          ud::set_value(result27, ud::get_value_ref(result26));
        }
        ud::set_value(result28, ud::get_value_ref(result27));
      }
      ud::set_value(result29, ud::get_value_ref(result28));
    }
    return ud::VerifyResult::Error(ud::get_stored_value(ud::get_value_ref(result29)));
  }
}
hstd::ext::unidata::VerifyCheckCollection const* hstd::unidata_dsl::test::MultiValueCond::get_unidata_checks() {
  static hstd::ext::unidata::VerifyCheckCollection checks
   = {{{hstd::ext::unidata::VerifyKey{"MultiValueCond", "field"},
        hstd::ext::unidata::VerifyCbList{
        hstd::ext::unidata::VerifyCb{&__check_field_field_check}
        }}}};
  return &checks;
}
/* clang-format on */