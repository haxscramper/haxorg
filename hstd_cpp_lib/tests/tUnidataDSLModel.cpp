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
  ud::S<int64_t> const& expr2 = ud::eval_op<ud::OpId::STR_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 42), expr0);
  ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 42), expr1, expr2);
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
  ud::S<int64_t> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 120), expr0, "id");
  ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 120), expr1, expr2);
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
  ud::S<int64_t> const& expr2 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 130), expr0, "weight");
  ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 130), expr1, expr2);
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
  auto const& expr7 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                        ud::get_context(ctx, "hstd_test_model.py", 147),
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                          ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::Eq);
                          ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                          return expr3;
                        },
                        [&]() -> ud::S<bool> {
                          ud::S<int64_t> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 193), expr0, "number");
                          ud::S<int64_t> const& expr5 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
                          ud::S<bool> const& expr6 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 193), expr4, expr5);
                          return expr6;
                        }
                      );
  if (ud::get_stored_value(expr7)) {
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
  auto const& expr7 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                        ud::get_context(ctx, "hstd_test_model.py", 147),
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                          ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::Ne);
                          ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                          return expr3;
                        },
                        [&]() -> ud::S<bool> {
                          ud::S<int64_t> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 194), expr0, "number");
                          ud::S<int64_t> const& expr5 = ud::S<int64_t>::FromConst(static_cast<int64_t>(8), "8");
                          ud::S<bool> const& expr6 = ud::eval_op<ud::OpId::NE, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 194), expr4, expr5);
                          return expr6;
                        }
                      );
  if (ud::get_stored_value(expr7)) {
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
  auto const& expr7 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                        ud::get_context(ctx, "hstd_test_model.py", 147),
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                          ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::Lt);
                          ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                          return expr3;
                        },
                        [&]() -> ud::S<bool> {
                          ud::S<int64_t> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 195), expr0, "number");
                          ud::S<int64_t> const& expr5 = ud::S<int64_t>::FromConst(static_cast<int64_t>(7), "7");
                          ud::S<bool> const& expr6 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 195), expr4, expr5);
                          return expr6;
                        }
                      );
  if (ud::get_stored_value(expr7)) {
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
  auto const& expr7 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                        ud::get_context(ctx, "hstd_test_model.py", 147),
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                          ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::Le);
                          ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                          return expr3;
                        },
                        [&]() -> ud::S<bool> {
                          ud::S<int64_t> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 196), expr0, "number");
                          ud::S<int64_t> const& expr5 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
                          ud::S<bool> const& expr6 = ud::eval_op<ud::OpId::LE, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 196), expr4, expr5);
                          return expr6;
                        }
                      );
  if (ud::get_stored_value(expr7)) {
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
  auto const& expr9 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                        ud::get_context(ctx, "hstd_test_model.py", 147),
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                          ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::Add);
                          ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                          return expr3;
                        },
                        [&]() -> ud::S<bool> {
                          ud::S<int64_t> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 197), expr0, "number");
                          ud::S<int64_t> const& expr5 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
                          ud::S<int64_t> const& expr6 = ud::eval_op<ud::OpId::ADD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 197), expr4, expr5);
                          ud::S<int64_t> const& expr7 = ud::S<int64_t>::FromConst(static_cast<int64_t>(9), "9");
                          ud::S<bool> const& expr8 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 197), expr6, expr7);
                          return expr8;
                        }
                      );
  if (ud::get_stored_value(expr9)) {
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
  auto const& expr9 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                        ud::get_context(ctx, "hstd_test_model.py", 147),
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                          ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::Sub);
                          ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                          return expr3;
                        },
                        [&]() -> ud::S<bool> {
                          ud::S<int64_t> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 198), expr0, "number");
                          ud::S<int64_t> const& expr5 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
                          ud::S<int64_t> const& expr6 = ud::eval_op<ud::OpId::SUB, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 198), expr4, expr5);
                          ud::S<int64_t> const& expr7 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
                          ud::S<bool> const& expr8 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 198), expr6, expr7);
                          return expr8;
                        }
                      );
  if (ud::get_stored_value(expr9)) {
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
  auto const& expr9 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                        ud::get_context(ctx, "hstd_test_model.py", 147),
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                          ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::Mul);
                          ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                          return expr3;
                        },
                        [&]() -> ud::S<bool> {
                          ud::S<int64_t> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 199), expr0, "number");
                          ud::S<int64_t> const& expr5 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
                          ud::S<int64_t> const& expr6 = ud::eval_op<ud::OpId::MUL, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 199), expr4, expr5);
                          ud::S<int64_t> const& expr7 = ud::S<int64_t>::FromConst(static_cast<int64_t>(18), "18");
                          ud::S<bool> const& expr8 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 199), expr6, expr7);
                          return expr8;
                        }
                      );
  if (ud::get_stored_value(expr9)) {
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
  auto const& expr9 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                        ud::get_context(ctx, "hstd_test_model.py", 147),
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                          ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::Div);
                          ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                          return expr3;
                        },
                        [&]() -> ud::S<bool> {
                          ud::S<int64_t> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 200), expr0, "number");
                          ud::S<int64_t> const& expr5 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
                          ud::S<int64_t> const& expr6 = ud::eval_op<ud::OpId::DIV, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 200), expr4, expr5);
                          ud::S<int64_t> const& expr7 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
                          ud::S<bool> const& expr8 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 200), expr6, expr7);
                          return expr8;
                        }
                      );
  if (ud::get_stored_value(expr9)) {
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
  auto const& expr28 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                         ud::get_context(ctx, "hstd_test_model.py", 147),
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                           ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::ConstFloat);
                           ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                           return expr3;
                         },
                         [&]() -> ud::S<bool> {
                           auto const& expr27 = ud::eval_op<ud::OpId::AND, ud::S<bool>>(
                                                  ud::get_context(ctx, "hstd_test_model.py", 203),
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<double> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<double>>(ud::get_context(ctx, "hstd_test_model.py", 204), expr0, "real");
                                                    ud::S<double> const& expr5 = ud::S<double>::FromConst(static_cast<double>(2.5), "2.5");
                                                    ud::S<bool> const& expr6 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 204), expr4, expr5);
                                                    return expr6;
                                                  },
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<double> const& expr7 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<double>>(ud::get_context(ctx, "hstd_test_model.py", 205), expr0, "real");
                                                    ud::S<double> const& expr8 = ud::S<double>::FromConst(static_cast<double>(2.0), "2.0");
                                                    ud::S<double> const& expr9 = ud::eval_op<ud::OpId::DIV, ud::S<double>>(ud::get_context(ctx, "hstd_test_model.py", 205), expr7, expr8);
                                                    ud::S<double> const& expr10 = ud::S<double>::FromConst(static_cast<double>(1.25), "1.25");
                                                    ud::S<bool> const& expr11 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 205), expr9, expr10);
                                                    return expr11;
                                                  },
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<double> const& expr12 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<double>>(ud::get_context(ctx, "hstd_test_model.py", 206), expr0, "real");
                                                    ud::S<double> const& expr13 = ud::S<double>::FromConst(static_cast<double>(2.0), "2.0");
                                                    ud::S<double> const& expr14 = ud::eval_op<ud::OpId::MUL, ud::S<double>>(ud::get_context(ctx, "hstd_test_model.py", 206), expr12, expr13);
                                                    ud::S<double> const& expr15 = ud::S<double>::FromConst(static_cast<double>(5.0), "5.0");
                                                    ud::S<bool> const& expr16 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 206), expr14, expr15);
                                                    return expr16;
                                                  },
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<double> const& expr17 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<double>>(ud::get_context(ctx, "hstd_test_model.py", 207), expr0, "real");
                                                    ud::S<double> const& expr18 = ud::S<double>::FromConst(static_cast<double>(0.5), "0.5");
                                                    ud::S<double> const& expr19 = ud::eval_op<ud::OpId::SUB, ud::S<double>>(ud::get_context(ctx, "hstd_test_model.py", 207), expr17, expr18);
                                                    ud::S<double> const& expr20 = ud::S<double>::FromConst(static_cast<double>(2.0), "2.0");
                                                    ud::S<bool> const& expr21 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 207), expr19, expr20);
                                                    return expr21;
                                                  },
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<double> const& expr22 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<double>>(ud::get_context(ctx, "hstd_test_model.py", 208), expr0, "real");
                                                    ud::S<double> const& expr23 = ud::S<double>::FromConst(static_cast<double>(0.5), "0.5");
                                                    ud::S<double> const& expr24 = ud::eval_op<ud::OpId::ADD, ud::S<double>>(ud::get_context(ctx, "hstd_test_model.py", 208), expr22, expr23);
                                                    ud::S<double> const& expr25 = ud::S<double>::FromConst(static_cast<double>(3.0), "3.0");
                                                    ud::S<bool> const& expr26 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 208), expr24, expr25);
                                                    return expr26;
                                                  }
                                                );
                           return expr27;
                         }
                       );
  if (ud::get_stored_value(expr28)) {
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
  auto const& expr7 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                        ud::get_context(ctx, "hstd_test_model.py", 147),
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                          ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::ConstBool);
                          ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                          return expr3;
                        },
                        [&]() -> ud::S<bool> {
                          ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 211), expr0, "flag");
                          ud::S<bool> const& expr5 = ud::S<bool>::FromConst(static_cast<bool>(true), "true");
                          ud::S<bool> const& expr6 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 211), expr4, expr5);
                          return expr6;
                        }
                      );
  if (ud::get_stored_value(expr7)) {
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
  auto const& expr14 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                         ud::get_context(ctx, "hstd_test_model.py", 147),
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                           ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::And);
                           ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                           return expr3;
                         },
                         [&]() -> ud::S<bool> {
                           auto const& expr13 = ud::eval_op<ud::OpId::AND, ud::S<bool>>(
                                                  ud::get_context(ctx, "hstd_test_model.py", 214),
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 215), expr0, "flag");
                                                    return expr4;
                                                  },
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<int64_t> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 216), expr0, "number");
                                                    ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
                                                    ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 216), expr5, expr6);
                                                    return expr7;
                                                  },
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr8 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 217), expr0, "mapping");
                                                    ud::S<hstd::Str> const& expr9 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("a"), "a");
                                                    ud::S<int64_t> const& expr10 = ud::eval_op<ud::OpId::MAP_GET, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 217), expr8, expr9);
                                                    ud::S<int64_t> const& expr11 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
                                                    ud::S<bool> const& expr12 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 217), expr10, expr11);
                                                    return expr12;
                                                  }
                                                );
                           return expr13;
                         }
                       );
  if (ud::get_stored_value(expr14)) {
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
  auto const& expr14 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                         ud::get_context(ctx, "hstd_test_model.py", 147),
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                           ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::Or);
                           ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                           return expr3;
                         },
                         [&]() -> ud::S<bool> {
                           auto const& expr13 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                                                  ud::get_context(ctx, "hstd_test_model.py", 222),
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<bool> const& expr4 = ud::S<bool>::FromConst(static_cast<bool>(false), "false");
                                                    return expr4;
                                                  },
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<int64_t> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 222), expr0, "number");
                                                    ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
                                                    ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 222), expr5, expr6);
                                                    return expr7;
                                                  },
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr8 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 222), expr0, "mapping");
                                                    ud::S<hstd::Str> const& expr9 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("a"), "a");
                                                    ud::S<int64_t> const& expr10 = ud::eval_op<ud::OpId::MAP_GET, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 222), expr8, expr9);
                                                    ud::S<int64_t> const& expr11 = ud::S<int64_t>::FromConst(static_cast<int64_t>(99), "99");
                                                    ud::S<bool> const& expr12 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 222), expr10, expr11);
                                                    return expr12;
                                                  }
                                                );
                           return expr13;
                         }
                       );
  if (ud::get_stored_value(expr14)) {
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
  auto const& expr8 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                        ud::get_context(ctx, "hstd_test_model.py", 147),
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                          ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::Not);
                          ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                          return expr3;
                        },
                        [&]() -> ud::S<bool> {
                          ud::S<int64_t> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 224), expr0, "number");
                          ud::S<int64_t> const& expr5 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
                          ud::S<bool> const& expr6 = ud::eval_op<ud::OpId::NE, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 224), expr4, expr5);
                          ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 224), (expr6));
                          return expr7;
                        }
                      );
  if (ud::get_stored_value(expr8)) {
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
  auto const& expr13 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                         ud::get_context(ctx, "hstd_test_model.py", 147),
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                           ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::Cond);
                           ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                           return expr3;
                         },
                         [&]() -> ud::S<bool> {
                           auto const& expr10 = ud::eval_op<ud::OpId::COND, ud::S<hstd::Str>>(
                                                  ud::get_context(ctx, "hstd_test_model.py", 227),
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<int64_t> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 228), expr0, "number");
                                                    ud::S<int64_t> const& expr5 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
                                                    ud::S<bool> const& expr6 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 228), expr4, expr5);
                                                    return expr6;
                                                  },
                                                  [&]() -> ud::S<hstd::Str> {
                                                    ud::S<hstd::Str> const& expr7 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 228), expr0, "text");
                                                    return expr7;
                                                  },
                                                  [&]() -> ud::S<hstd::Str> {
                                                    ud::S<int64_t> const& expr8 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 229), expr0, "number");
                                                    ud::S<hstd::Str> const& expr9 = ud::eval_op<ud::OpId::STR_FORMAT, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 229), eval_str_pattern("other-{}"), expr8);
                                                    return expr9;
                                                  }
                                                );
                           ud::S<hstd::Str> const& expr11 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("six"), "six");
                           ud::S<bool> const& expr12 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 227), expr10, expr11);
                           return expr12;
                         }
                       );
  if (ud::get_stored_value(expr13)) {
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
  auto const& expr14 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                         ud::get_context(ctx, "hstd_test_model.py", 147),
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                           ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::CondLazy);
                           ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                           return expr3;
                         },
                         [&]() -> ud::S<bool> {
                           auto const& expr11 = ud::eval_op<ud::OpId::COND, ud::S<int64_t>>(
                                                  ud::get_context(ctx, "hstd_test_model.py", 235),
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<bool> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 236), expr0, "flag");
                                                    return expr4;
                                                  },
                                                  [&]() -> ud::S<int64_t> {
                                                    ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 236), expr0, "mapping");
                                                    ud::S<hstd::Str> const& expr6 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("a"), "a");
                                                    ud::S<int64_t> const& expr7 = ud::eval_op<ud::OpId::MAP_GET, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 236), expr5, expr6);
                                                    return expr7;
                                                  },
                                                  [&]() -> ud::S<int64_t> {
                                                    ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr8 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 237), expr0, "mapping");
                                                    ud::S<hstd::Str> const& expr9 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("absent"), "absent");
                                                    ud::S<int64_t> const& expr10 = ud::eval_op<ud::OpId::MAP_GET, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 237), expr8, expr9);
                                                    return expr10;
                                                  }
                                                );
                           ud::S<int64_t> const& expr12 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
                           ud::S<bool> const& expr13 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 235), expr11, expr12);
                           return expr13;
                         }
                       );
  if (ud::get_stored_value(expr14)) {
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
  auto const& expr9 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                        ud::get_context(ctx, "hstd_test_model.py", 147),
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                          ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::Let);
                          ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                          return expr3;
                        },
                        [&]() -> ud::S<bool> {
                          ud::S<int64_t> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 245), expr0, "number");
                          ud::S<int64_t> const& expr5 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
                          ud::S<int64_t> const& expr6 = ud::eval_op<ud::OpId::ADD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 248), expr4, expr5);
                          ud::S<int64_t> const& expr7 = ud::S<int64_t>::FromConst(static_cast<int64_t>(7), "7");
                          ud::S<bool> const& expr8 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 243), expr6, expr7);
                          return expr8;
                        }
                      );
  if (ud::get_stored_value(expr9)) {
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
  auto const& expr10 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                         ud::get_context(ctx, "hstd_test_model.py", 147),
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                           ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::All);
                           ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                           return expr3;
                         },
                         [&]() -> ud::S<bool> {
                           ud::S<ud::UniVec<ud::S<int64_t>>> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 254), expr0, "numbers");
                           auto callback8 = [&](ud::S<int64_t> const& item5) -> ud::S<bool> {
                                              // lt typed_as='bool'
                                              //     var typed_as='int64' str_val='number'
                                              //     const_int typed_as='int64' int_val=4
                                              //
                                              ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(4), "4");
                                              ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 254), item5, expr6);
                                              return expr7;
                                            };
                           ud::S<bool> const& expr9 = ud::eval_op<ud::OpId::ALL, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 254), expr4, callback8);
                           return expr9;
                         }
                       );
  if (ud::get_stored_value(expr10)) {
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
  auto const& expr10 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                         ud::get_context(ctx, "hstd_test_model.py", 147),
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                           ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::Exists);
                           ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                           return expr3;
                         },
                         [&]() -> ud::S<bool> {
                           ud::S<ud::UniVec<ud::S<int64_t>>> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 255), expr0, "numbers");
                           auto callback8 = [&](ud::S<int64_t> const& item5) -> ud::S<bool> {
                                              // eq typed_as='bool'
                                              //     var typed_as='int64' str_val='number'
                                              //     const_int typed_as='int64' int_val=3
                                              //
                                              ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
                                              ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 255), item5, expr6);
                                              return expr7;
                                            };
                           ud::S<bool> const& expr9 = ud::eval_op<ud::OpId::EXISTS, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 255), expr4, callback8);
                           return expr9;
                         }
                       );
  if (ud::get_stored_value(expr10)) {
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
  auto const& expr10 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                         ud::get_context(ctx, "hstd_test_model.py", 147),
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                           ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::ExistsOne);
                           ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                           return expr3;
                         },
                         [&]() -> ud::S<bool> {
                           ud::S<ud::UniVec<ud::S<int64_t>>> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 256), expr0, "numbers");
                           auto callback8 = [&](ud::S<int64_t> const& item5) -> ud::S<bool> {
                                              // eq typed_as='bool'
                                              //     var typed_as='int64' str_val='number'
                                              //     const_int typed_as='int64' int_val=3
                                              //
                                              ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
                                              ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 256), item5, expr6);
                                              return expr7;
                                            };
                           ud::S<bool> const& expr9 = ud::eval_op<ud::OpId::EXISTS_ONE, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 256), expr4, callback8);
                           return expr9;
                         }
                       );
  if (ud::get_stored_value(expr10)) {
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
  auto const& expr14 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                         ud::get_context(ctx, "hstd_test_model.py", 147),
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                           ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::Map);
                           ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                           return expr3;
                         },
                         [&]() -> ud::S<bool> {
                           ud::S<ud::UniVec<ud::S<int64_t>>> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 259), expr0, "numbers");
                           auto callback8 = [&](ud::S<int64_t> const& item5) -> ud::S<int64_t> {
                                              // mul typed_as='int64'
                                              //     var typed_as='int64' str_val='number'
                                              //     const_int typed_as='int64' int_val=2
                                              //
                                              ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
                                              ud::S<int64_t> const& expr7 = ud::eval_op<ud::OpId::MUL, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 259), item5, expr6);
                                              return expr7;
                                            };
                           ud::S<ud::UniVec<ud::S<int64_t>>> const& expr9 = ud::eval_op<ud::OpId::MAP, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 259), expr4, callback8);
                           ud::S<int64_t> const& expr10 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
                           ud::S<int64_t> const& expr11 = ud::eval_op<ud::OpId::LIST_AT, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 259), expr9, expr10);
                           ud::S<int64_t> const& expr12 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
                           ud::S<bool> const& expr13 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 259), expr11, expr12);
                           return expr13;
                         }
                       );
  if (ud::get_stored_value(expr14)) {
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
  auto const& expr13 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                         ud::get_context(ctx, "hstd_test_model.py", 147),
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                           ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::Filter);
                           ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                           return expr3;
                         },
                         [&]() -> ud::S<bool> {
                           ud::S<ud::UniVec<ud::S<int64_t>>> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 263), expr0, "numbers");
                           auto callback8 = [&](ud::S<int64_t> const& item5) -> ud::S<bool> {
                                              // lt typed_as='bool'
                                              //     const_int typed_as='int64' int_val=1
                                              //     var typed_as='int64' str_val='number'
                                              //
                                              ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
                                              ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 263), expr6, item5);
                                              return expr7;
                                            };
                           ud::S<ud::UniVec<ud::S<int64_t>>> const& expr9 = ud::eval_op<ud::OpId::FILTER, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 263), expr4, callback8);
                           ud::S<int64_t> const& expr10 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 263), expr9);
                           ud::S<int64_t> const& expr11 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
                           ud::S<bool> const& expr12 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 263), expr10, expr11);
                           return expr12;
                         }
                       );
  if (ud::get_stored_value(expr13)) {
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
  auto const& expr20 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                         ud::get_context(ctx, "hstd_test_model.py", 147),
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                           ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::FilterMap);
                           ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                           return expr3;
                         },
                         [&]() -> ud::S<bool> {
                           ud::S<ud::UniVec<ud::S<ud::UniOpt<ud::S<int64_t>>>>> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniVec<ud::S<ud::UniOpt<ud::S<int64_t>>>>>>(ud::get_context(ctx, "hstd_test_model.py", 271), expr0, "optionals");
                           auto callback6 = [&](ud::S<ud::UniOpt<ud::S<int64_t>>> const& item5) -> ud::S<ud::UniOpt<ud::S<int64_t>>> {
                                              // var typed_as='optional<int64>' str_val='optional'
                                              //
                                              return item5;
                                            };
                           ud::S<ud::UniVec<ud::S<int64_t>>> const& expr7 = ud::eval_op<ud::OpId::FILTER_MAP, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 270), expr4, callback6);
                           auto const& expr19 = ud::eval_op<ud::OpId::AND, ud::S<bool>>(
                                                  ud::get_context(ctx, "hstd_test_model.py", 275),
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<int64_t> const& expr8 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 276), expr7);
                                                    ud::S<int64_t> const& expr9 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
                                                    ud::S<bool> const& expr10 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 276), expr8, expr9);
                                                    return expr10;
                                                  },
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<int64_t> const& expr11 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                                                    ud::S<int64_t> const& expr12 = ud::eval_op<ud::OpId::LIST_AT, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 277), expr7, expr11);
                                                    ud::S<int64_t> const& expr13 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
                                                    ud::S<bool> const& expr14 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 277), expr12, expr13);
                                                    return expr14;
                                                  },
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<int64_t> const& expr15 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
                                                    ud::S<int64_t> const& expr16 = ud::eval_op<ud::OpId::LIST_AT, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 278), expr7, expr15);
                                                    ud::S<int64_t> const& expr17 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
                                                    ud::S<bool> const& expr18 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 278), expr16, expr17);
                                                    return expr18;
                                                  }
                                                );
                           return expr19;
                         }
                       );
  if (ud::get_stored_value(expr20)) {
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
  auto const& expr13 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                         ud::get_context(ctx, "hstd_test_model.py", 147),
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                           ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::TakeWhile);
                           ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                           return expr3;
                         },
                         [&]() -> ud::S<bool> {
                           ud::S<ud::UniVec<ud::S<int64_t>>> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 285), expr0, "numbers");
                           auto callback8 = [&](ud::S<int64_t> const& item5) -> ud::S<bool> {
                                              // lt typed_as='bool'
                                              //     var typed_as='int64' str_val='number'
                                              //     const_int typed_as='int64' int_val=3
                                              //
                                              ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
                                              ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 287), item5, expr6);
                                              return expr7;
                                            };
                           ud::S<ud::UniVec<ud::S<int64_t>>> const& expr9 = ud::eval_op<ud::OpId::TAKE_WHILE, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 284), expr4, callback8);
                           ud::S<int64_t> const& expr10 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 288), expr9);
                           ud::S<int64_t> const& expr11 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
                           ud::S<bool> const& expr12 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 284), expr10, expr11);
                           return expr12;
                         }
                       );
  if (ud::get_stored_value(expr13)) {
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
  auto const& expr23 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                         ud::get_context(ctx, "hstd_test_model.py", 147),
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                           ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::GroupBy);
                           ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                           return expr3;
                         },
                         [&]() -> ud::S<bool> {
                           ud::S<ud::UniVec<ud::S<int64_t>>> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 296), expr0, "numbers");
                           auto callback8 = [&](ud::S<int64_t> const& item5) -> ud::S<bool> {
                                              // lt typed_as='bool'
                                              //     var typed_as='int64' str_val='number'
                                              //     const_int typed_as='int64' int_val=3
                                              //
                                              ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
                                              ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 298), item5, expr6);
                                              return expr7;
                                            };
                           ud::S<ud::UniMap<ud::S<bool>, ud::S<ud::UniVec<ud::S<int64_t>>>>> const& expr9 = ud::eval_op<ud::OpId::GROUP_BY, ud::S<ud::UniMap<ud::S<bool>, ud::S<ud::UniVec<ud::S<int64_t>>>>>>(ud::get_context(ctx, "hstd_test_model.py", 295), expr4, callback8);
                           auto const& expr22 = ud::eval_op<ud::OpId::AND, ud::S<bool>>(
                                                  ud::get_context(ctx, "hstd_test_model.py", 300),
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<int64_t> const& expr10 = ud::eval_op<ud::OpId::MAP_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 301), expr9);
                                                    ud::S<int64_t> const& expr11 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
                                                    ud::S<bool> const& expr12 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 301), expr10, expr11);
                                                    return expr12;
                                                  },
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<ud::UniVec<ud::S<ud::UniVec<ud::S<int64_t>>>>> const& expr13 = ud::eval_op<ud::OpId::MAP_VALUES, ud::S<ud::UniVec<ud::S<ud::UniVec<ud::S<int64_t>>>>>>(ud::get_context(ctx, "hstd_test_model.py", 302), expr9);
                                                    ud::S<int64_t> const& expr14 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                                                    ud::S<ud::UniVec<ud::S<int64_t>>> const& expr15 = ud::eval_op<ud::OpId::LIST_AT, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 302), expr13, expr14);
                                                    ud::S<int64_t> const& expr16 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                                                    ud::S<int64_t> const& expr17 = ud::eval_op<ud::OpId::LIST_AT, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 302), expr15, expr16);
                                                    ud::S<ud::UniVec<ud::S<int64_t>>> const& expr18 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 303), expr0, "numbers");
                                                    ud::S<int64_t> const& expr19 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                                                    ud::S<int64_t> const& expr20 = ud::eval_op<ud::OpId::LIST_AT, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 303), expr18, expr19);
                                                    ud::S<bool> const& expr21 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 302), expr17, expr20);
                                                    return expr21;
                                                  }
                                                );
                           return expr22;
                         }
                       );
  if (ud::get_stored_value(expr23)) {
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
  auto const& expr13 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                         ud::get_context(ctx, "hstd_test_model.py", 147),
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                           ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::Fold);
                           ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                           return expr3;
                         },
                         [&]() -> ud::S<bool> {
                           ud::S<ud::UniVec<ud::S<int64_t>>> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 310), expr0, "numbers");
                           ud::S<int64_t> const& expr5 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                           auto callback6 = [&](ud::S<int64_t> const& item7, ud::S<int64_t> const& item8) -> ud::S<int64_t> {
                                              // add typed_as='int64'
                                              //     var typed_as='int64' str_val='acc'
                                              //     var typed_as='int64' str_val='number'
                                              //
                                              ud::S<int64_t> const& expr9 = ud::eval_op<ud::OpId::ADD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 314), item7, item8);
                                              return expr9;
                                            };
                           ud::S<int64_t> const& expr10 = ud::eval_op<ud::OpId::FOLD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 309), expr4, expr5, callback6);
                           ud::S<int64_t> const& expr11 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
                           ud::S<bool> const& expr12 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 309), expr10, expr11);
                           return expr12;
                         }
                       );
  if (ud::get_stored_value(expr13)) {
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
  auto const& expr20 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                         ud::get_context(ctx, "hstd_test_model.py", 147),
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                           ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::Walk);
                           ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                           return expr3;
                         },
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::Derived> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Derived>>(ud::get_context(ctx, "hstd_test_model.py", 322), expr0, "derived");
                           ud::S<ud::UniVec<ud::UniDynamic>> const& expr5 = ud::eval_op<ud::OpId::WALK, ud::S<ud::UniVec<ud::UniDynamic>>>(ud::get_context(ctx, "hstd_test_model.py", 156), expression_runtime, expr4);
                           auto callback10 = [&](ud::UniDynamic const& item6) -> ud::S<ud::UniOpt<ud::S<int64_t>>> {
                                               // type_cond typed_as='optional<int64>' bool_val=True
                                               //     var typed_as='dyn<Derived>' str_val='walk_value'
                                               //     type_case typed_as='int64' type_val='Derived' binders='derived'[Derived]
                                               //         get_field typed_as='int64' str_val='id'
                                               //             var typed_as='Derived' str_val='derived'
                                               //
                                               ud::S<ud::UniOpt<ud::S<int64_t>>> result7 = ud::S<ud::UniOpt<ud::S<int64_t>>>::FromConst(std::nullopt, "std::nullopt");
                                               if (!ud::get_stored_as_bool(result7)) {
                                                 hstd::Opt<ud::S<hstd::unidata_dsl::test::Derived>> candidate8 = expression_runtime.try_as<hstd::unidata_dsl::test::Derived>(item6);
                                                 if (candidate8.has_value()) {
                                                   ud::S<int64_t> const& expr9 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 163), (*candidate8), "id");
                                                   ud::set_value(result7, expr9);
                                                 }
                                               }
                                               return result7;
                                             };
                           ud::S<ud::UniVec<ud::S<int64_t>>> const& expr11 = ud::eval_op<ud::OpId::FILTER_MAP, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 155), expr5, callback10);
                           auto const& expr19 = ud::eval_op<ud::OpId::AND, ud::S<bool>>(
                                                  ud::get_context(ctx, "hstd_test_model.py", 323),
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<int64_t> const& expr12 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 324), expr11);
                                                    ud::S<int64_t> const& expr13 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
                                                    ud::S<bool> const& expr14 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 324), expr12, expr13);
                                                    return expr14;
                                                  },
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<int64_t> const& expr15 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                                                    ud::S<int64_t> const& expr16 = ud::eval_op<ud::OpId::LIST_AT, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 325), expr11, expr15);
                                                    ud::S<int64_t> const& expr17 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
                                                    ud::S<bool> const& expr18 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 325), expr16, expr17);
                                                    return expr18;
                                                  }
                                                );
                           return expr19;
                         }
                       );
  if (ud::get_stored_value(expr20)) {
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
  auto const& expr8 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                        ud::get_context(ctx, "hstd_test_model.py", 147),
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                          ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::Sum);
                          ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                          return expr3;
                        },
                        [&]() -> ud::S<bool> {
                          ud::S<ud::UniVec<ud::S<int64_t>>> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 329), expr0, "numbers");
                          ud::S<int64_t> const& expr5 = ud::eval_op<ud::OpId::SUM, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 329), expr4);
                          ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
                          ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 329), expr5, expr6);
                          return expr7;
                        }
                      );
  if (ud::get_stored_value(expr8)) {
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
  auto const& expr8 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                        ud::get_context(ctx, "hstd_test_model.py", 147),
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                          ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::Min);
                          ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                          return expr3;
                        },
                        [&]() -> ud::S<bool> {
                          ud::S<ud::UniVec<ud::S<int64_t>>> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 330), expr0, "numbers");
                          ud::S<int64_t> const& expr5 = ud::eval_op<ud::OpId::MIN, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 330), expr4);
                          ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
                          ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 330), expr5, expr6);
                          return expr7;
                        }
                      );
  if (ud::get_stored_value(expr8)) {
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
  auto const& expr8 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                        ud::get_context(ctx, "hstd_test_model.py", 147),
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                          ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::Max);
                          ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                          return expr3;
                        },
                        [&]() -> ud::S<bool> {
                          ud::S<ud::UniVec<ud::S<int64_t>>> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 331), expr0, "numbers");
                          ud::S<int64_t> const& expr5 = ud::eval_op<ud::OpId::MAX, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 331), expr4);
                          ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
                          ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 331), expr5, expr6);
                          return expr7;
                        }
                      );
  if (ud::get_stored_value(expr8)) {
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
  auto const& expr8 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                        ud::get_context(ctx, "hstd_test_model.py", 147),
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                          ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::StrSize);
                          ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                          return expr3;
                        },
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::Str> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 332), expr0, "text");
                          ud::S<int64_t> const& expr5 = ud::eval_op<ud::OpId::STR_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 332), expr4);
                          ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
                          ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 332), expr5, expr6);
                          return expr7;
                        }
                      );
  if (ud::get_stored_value(expr8)) {
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
  auto const& expr6 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                        ud::get_context(ctx, "hstd_test_model.py", 147),
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                          ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::StrMatches);
                          ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                          return expr3;
                        },
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::Str> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 333), expr0, "text");
                          ud::S<bool> const& expr5 = ud::eval_op<ud::OpId::STR_MATCHES, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 333), expr4, "^s[a-z]{2}$");
                          return expr5;
                        }
                      );
  if (ud::get_stored_value(expr6)) {
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
  auto const& expr9 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                        ud::get_context(ctx, "hstd_test_model.py", 147),
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                          ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::StrFormat);
                          ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                          return expr3;
                        },
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::Str> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 336), expr0, "text");
                          ud::S<int64_t> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 336), expr0, "number");
                          ud::S<hstd::Str> const& expr6 = ud::eval_op<ud::OpId::STR_FORMAT, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 336), eval_str_pattern("{}:{}"), expr4, expr5);
                          ud::S<hstd::Str> const& expr7 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("six:6"), "six:6");
                          ud::S<bool> const& expr8 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 336), expr6, expr7);
                          return expr8;
                        }
                      );
  if (ud::get_stored_value(expr9)) {
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
  auto const& expr8 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                        ud::get_context(ctx, "hstd_test_model.py", 147),
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                          ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::ListSize);
                          ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                          return expr3;
                        },
                        [&]() -> ud::S<bool> {
                          ud::S<ud::UniVec<ud::S<int64_t>>> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 338), expr0, "numbers");
                          ud::S<int64_t> const& expr5 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 338), expr4);
                          ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
                          ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 338), expr5, expr6);
                          return expr7;
                        }
                      );
  if (ud::get_stored_value(expr8)) {
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
  auto const& expr7 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                        ud::get_context(ctx, "hstd_test_model.py", 147),
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                          ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::ListContains);
                          ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                          return expr3;
                        },
                        [&]() -> ud::S<bool> {
                          ud::S<ud::UniVec<ud::S<int64_t>>> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 339), expr0, "numbers");
                          ud::S<int64_t> const& expr5 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
                          ud::S<bool> const& expr6 = ud::eval_op<ud::OpId::LIST_CONTAINS, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 339), expr4, expr5);
                          return expr6;
                        }
                      );
  if (ud::get_stored_value(expr7)) {
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
  auto const& expr9 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                        ud::get_context(ctx, "hstd_test_model.py", 147),
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                          ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::ListAt);
                          ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                          return expr3;
                        },
                        [&]() -> ud::S<bool> {
                          ud::S<ud::UniVec<ud::S<int64_t>>> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 340), expr0, "numbers");
                          ud::S<int64_t> const& expr5 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
                          ud::S<int64_t> const& expr6 = ud::eval_op<ud::OpId::LIST_AT, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 340), expr4, expr5);
                          ud::S<int64_t> const& expr7 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
                          ud::S<bool> const& expr8 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 340), expr6, expr7);
                          return expr8;
                        }
                      );
  if (ud::get_stored_value(expr9)) {
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
  auto const& expr20 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                         ud::get_context(ctx, "hstd_test_model.py", 147),
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                           ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::ListSlice);
                           ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                           return expr3;
                         },
                         [&]() -> ud::S<bool> {
                           ud::S<ud::UniVec<ud::S<int64_t>>> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 345), expr0, "numbers");
                           ud::S<int64_t> const& expr5 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
                           ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
                           ud::S<ud::UniVec<ud::S<int64_t>>> const& expr7 = ud::eval_op<ud::OpId::LIST_SLICE, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 345), expr4, expr5, expr6);
                           auto const& expr19 = ud::eval_op<ud::OpId::AND, ud::S<bool>>(
                                                  ud::get_context(ctx, "hstd_test_model.py", 346),
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<int64_t> const& expr8 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 347), expr7);
                                                    ud::S<int64_t> const& expr9 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
                                                    ud::S<bool> const& expr10 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 347), expr8, expr9);
                                                    return expr10;
                                                  },
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<int64_t> const& expr11 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                                                    ud::S<int64_t> const& expr12 = ud::eval_op<ud::OpId::LIST_AT, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 348), expr7, expr11);
                                                    ud::S<int64_t> const& expr13 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
                                                    ud::S<bool> const& expr14 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 348), expr12, expr13);
                                                    return expr14;
                                                  },
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<int64_t> const& expr15 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
                                                    ud::S<int64_t> const& expr16 = ud::eval_op<ud::OpId::LIST_AT, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 349), expr7, expr15);
                                                    ud::S<int64_t> const& expr17 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
                                                    ud::S<bool> const& expr18 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 349), expr16, expr17);
                                                    return expr18;
                                                  }
                                                );
                           return expr19;
                         }
                       );
  if (ud::get_stored_value(expr20)) {
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
  auto const& expr20 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                         ud::get_context(ctx, "hstd_test_model.py", 147),
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                           ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::ListSliceBounds);
                           ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                           return expr3;
                         },
                         [&]() -> ud::S<bool> {
                           ud::S<ud::UniVec<ud::S<int64_t>>> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 357), expr0, "numbers");
                           ud::S<int64_t> const& expr5 = ud::S<int64_t>::FromConst(static_cast<int64_t>(-2), "-2");
                           ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(100), "100");
                           ud::S<ud::UniVec<ud::S<int64_t>>> const& expr7 = ud::eval_op<ud::OpId::LIST_SLICE, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 357), expr4, expr5, expr6);
                           auto const& expr19 = ud::eval_op<ud::OpId::AND, ud::S<bool>>(
                                                  ud::get_context(ctx, "hstd_test_model.py", 358),
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<int64_t> const& expr8 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 359), expr7);
                                                    ud::S<int64_t> const& expr9 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
                                                    ud::S<bool> const& expr10 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 359), expr8, expr9);
                                                    return expr10;
                                                  },
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<int64_t> const& expr11 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                                                    ud::S<int64_t> const& expr12 = ud::eval_op<ud::OpId::LIST_AT, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 360), expr7, expr11);
                                                    ud::S<int64_t> const& expr13 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
                                                    ud::S<bool> const& expr14 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 360), expr12, expr13);
                                                    return expr14;
                                                  },
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<int64_t> const& expr15 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
                                                    ud::S<int64_t> const& expr16 = ud::eval_op<ud::OpId::LIST_AT, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 361), expr7, expr15);
                                                    ud::S<int64_t> const& expr17 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
                                                    ud::S<bool> const& expr18 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 361), expr16, expr17);
                                                    return expr18;
                                                  }
                                                );
                           return expr19;
                         }
                       );
  if (ud::get_stored_value(expr20)) {
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
  auto const& expr17 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                         ud::get_context(ctx, "hstd_test_model.py", 147),
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                           ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::ListConcat);
                           ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                           return expr3;
                         },
                         [&]() -> ud::S<bool> {
                           ud::S<ud::UniVec<ud::S<int64_t>>> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 369), expr0, "numbers");
                           ud::S<ud::UniVec<ud::S<int64_t>>> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 369), expr0, "numbers");
                           ud::S<ud::UniVec<ud::S<int64_t>>> const& expr6 = ud::eval_op<ud::OpId::LIST_CONCAT, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 369), expr4, expr5);
                           auto const& expr16 = ud::eval_op<ud::OpId::AND, ud::S<bool>>(
                                                  ud::get_context(ctx, "hstd_test_model.py", 370),
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<int64_t> const& expr7 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 371), expr6);
                                                    ud::S<int64_t> const& expr8 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
                                                    ud::S<bool> const& expr9 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 371), expr7, expr8);
                                                    return expr9;
                                                  },
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<int64_t> const& expr10 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
                                                    ud::S<int64_t> const& expr11 = ud::eval_op<ud::OpId::LIST_AT, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 372), expr6, expr10);
                                                    ud::S<ud::UniVec<ud::S<int64_t>>> const& expr12 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 372), expr0, "numbers");
                                                    ud::S<int64_t> const& expr13 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                                                    ud::S<int64_t> const& expr14 = ud::eval_op<ud::OpId::LIST_AT, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 372), expr12, expr13);
                                                    ud::S<bool> const& expr15 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 372), expr11, expr14);
                                                    return expr15;
                                                  }
                                                );
                           return expr16;
                         }
                       );
  if (ud::get_stored_value(expr17)) {
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
  auto const& expr8 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                        ud::get_context(ctx, "hstd_test_model.py", 147),
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                          ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::ListEmpty);
                          ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                          return expr3;
                        },
                        [&]() -> ud::S<bool> {
                          ud::S<ud::UniVec<ud::S<int64_t>>> const& expr4 = ud::eval_op<ud::OpId::LIST_EMPTY, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 376));
                          ud::S<int64_t> const& expr5 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 376), expr4);
                          ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                          ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 376), expr5, expr6);
                          return expr7;
                        }
                      );
  if (ud::get_stored_value(expr8)) {
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
  auto const& expr8 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                        ud::get_context(ctx, "hstd_test_model.py", 147),
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                          ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::MapSize);
                          ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                          return expr3;
                        },
                        [&]() -> ud::S<bool> {
                          ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 377), expr0, "mapping");
                          ud::S<int64_t> const& expr5 = ud::eval_op<ud::OpId::MAP_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 377), expr4);
                          ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
                          ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 377), expr5, expr6);
                          return expr7;
                        }
                      );
  if (ud::get_stored_value(expr8)) {
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
  auto const& expr7 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                        ud::get_context(ctx, "hstd_test_model.py", 147),
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                          ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::MapContains);
                          ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                          return expr3;
                        },
                        [&]() -> ud::S<bool> {
                          ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 378), expr0, "mapping");
                          ud::S<hstd::Str> const& expr5 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("a"), "a");
                          ud::S<bool> const& expr6 = ud::eval_op<ud::OpId::MAP_CONTAINS, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 378), expr4, expr5);
                          return expr6;
                        }
                      );
  if (ud::get_stored_value(expr7)) {
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
  auto const& expr9 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                        ud::get_context(ctx, "hstd_test_model.py", 147),
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                          ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::MapGet);
                          ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                          return expr3;
                        },
                        [&]() -> ud::S<bool> {
                          ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 379), expr0, "mapping");
                          ud::S<hstd::Str> const& expr5 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("a"), "a");
                          ud::S<int64_t> const& expr6 = ud::eval_op<ud::OpId::MAP_GET, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 379), expr4, expr5);
                          ud::S<int64_t> const& expr7 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
                          ud::S<bool> const& expr8 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 379), expr6, expr7);
                          return expr8;
                        }
                      );
  if (ud::get_stored_value(expr9)) {
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
  auto const& expr20 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                         ud::get_context(ctx, "hstd_test_model.py", 147),
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                           ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::MapInsert);
                           ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                           return expr3;
                         },
                         [&]() -> ud::S<bool> {
                           ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 384), expr0, "mapping");
                           ud::S<hstd::Str> const& expr5 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("c"), "c");
                           ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
                           ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr7 = ud::eval_op<ud::OpId::MAP_INSERT, ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 384), expr4, expr5, expr6);
                           auto const& expr19 = ud::eval_op<ud::OpId::AND, ud::S<bool>>(
                                                  ud::get_context(ctx, "hstd_test_model.py", 385),
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<int64_t> const& expr8 = ud::eval_op<ud::OpId::MAP_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 386), expr7);
                                                    ud::S<int64_t> const& expr9 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
                                                    ud::S<bool> const& expr10 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 386), expr8, expr9);
                                                    return expr10;
                                                  },
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<hstd::Str> const& expr11 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("c"), "c");
                                                    ud::S<int64_t> const& expr12 = ud::eval_op<ud::OpId::MAP_GET, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 387), expr7, expr11);
                                                    ud::S<int64_t> const& expr13 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
                                                    ud::S<bool> const& expr14 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 387), expr12, expr13);
                                                    return expr14;
                                                  },
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr15 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 388), expr0, "mapping");
                                                    ud::S<hstd::Str> const& expr16 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("c"), "c");
                                                    ud::S<bool> const& expr17 = ud::eval_op<ud::OpId::MAP_CONTAINS, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 388), expr15, expr16);
                                                    ud::S<bool> const& expr18 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 388), (expr17));
                                                    return expr18;
                                                  }
                                                );
                           return expr19;
                         }
                       );
  if (ud::get_stored_value(expr20)) {
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
  auto const& expr22 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                         ud::get_context(ctx, "hstd_test_model.py", 147),
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                           ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::MapReplace);
                           ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                           return expr3;
                         },
                         [&]() -> ud::S<bool> {
                           ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 396), expr0, "mapping");
                           ud::S<hstd::Str> const& expr5 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("a"), "a");
                           ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(9), "9");
                           ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr7 = ud::eval_op<ud::OpId::MAP_INSERT, ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 396), expr4, expr5, expr6);
                           auto const& expr21 = ud::eval_op<ud::OpId::AND, ud::S<bool>>(
                                                  ud::get_context(ctx, "hstd_test_model.py", 397),
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<int64_t> const& expr8 = ud::eval_op<ud::OpId::MAP_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 398), expr7);
                                                    ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr9 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 398), expr0, "mapping");
                                                    ud::S<int64_t> const& expr10 = ud::eval_op<ud::OpId::MAP_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 398), expr9);
                                                    ud::S<bool> const& expr11 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 398), expr8, expr10);
                                                    return expr11;
                                                  },
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<hstd::Str> const& expr12 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("a"), "a");
                                                    ud::S<int64_t> const& expr13 = ud::eval_op<ud::OpId::MAP_GET, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 399), expr7, expr12);
                                                    ud::S<int64_t> const& expr14 = ud::S<int64_t>::FromConst(static_cast<int64_t>(9), "9");
                                                    ud::S<bool> const& expr15 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 399), expr13, expr14);
                                                    return expr15;
                                                  },
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr16 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 400), expr0, "mapping");
                                                    ud::S<hstd::Str> const& expr17 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("a"), "a");
                                                    ud::S<int64_t> const& expr18 = ud::eval_op<ud::OpId::MAP_GET, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 400), expr16, expr17);
                                                    ud::S<int64_t> const& expr19 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
                                                    ud::S<bool> const& expr20 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 400), expr18, expr19);
                                                    return expr20;
                                                  }
                                                );
                           return expr21;
                         }
                       );
  if (ud::get_stored_value(expr22)) {
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
  auto const& expr14 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                         ud::get_context(ctx, "hstd_test_model.py", 147),
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                           ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::MapKeys);
                           ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                           return expr3;
                         },
                         [&]() -> ud::S<bool> {
                           ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 408), expr0, "mapping");
                           ud::S<ud::UniVec<ud::S<hstd::Str>>> const& expr5 = ud::eval_op<ud::OpId::MAP_KEYS, ud::S<ud::UniVec<ud::S<hstd::Str>>>>(ud::get_context(ctx, "hstd_test_model.py", 408), expr4);
                           auto const& expr13 = ud::eval_op<ud::OpId::AND, ud::S<bool>>(
                                                  ud::get_context(ctx, "hstd_test_model.py", 409),
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<int64_t> const& expr6 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 410), expr5);
                                                    ud::S<int64_t> const& expr7 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
                                                    ud::S<bool> const& expr8 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 410), expr6, expr7);
                                                    return expr8;
                                                  },
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<hstd::Str> const& expr9 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("a"), "a");
                                                    ud::S<bool> const& expr10 = ud::eval_op<ud::OpId::LIST_CONTAINS, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 411), expr5, expr9);
                                                    return expr10;
                                                  },
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<hstd::Str> const& expr11 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("b"), "b");
                                                    ud::S<bool> const& expr12 = ud::eval_op<ud::OpId::LIST_CONTAINS, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 412), expr5, expr11);
                                                    return expr12;
                                                  }
                                                );
                           return expr13;
                         }
                       );
  if (ud::get_stored_value(expr14)) {
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
  auto const& expr14 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                         ud::get_context(ctx, "hstd_test_model.py", 147),
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                           ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::MapValues);
                           ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                           return expr3;
                         },
                         [&]() -> ud::S<bool> {
                           ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 420), expr0, "mapping");
                           ud::S<ud::UniVec<ud::S<int64_t>>> const& expr5 = ud::eval_op<ud::OpId::MAP_VALUES, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 420), expr4);
                           auto const& expr13 = ud::eval_op<ud::OpId::AND, ud::S<bool>>(
                                                  ud::get_context(ctx, "hstd_test_model.py", 421),
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<int64_t> const& expr6 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 422), expr5);
                                                    ud::S<int64_t> const& expr7 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
                                                    ud::S<bool> const& expr8 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 422), expr6, expr7);
                                                    return expr8;
                                                  },
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<int64_t> const& expr9 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
                                                    ud::S<bool> const& expr10 = ud::eval_op<ud::OpId::LIST_CONTAINS, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 423), expr5, expr9);
                                                    return expr10;
                                                  },
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<int64_t> const& expr11 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
                                                    ud::S<bool> const& expr12 = ud::eval_op<ud::OpId::LIST_CONTAINS, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 424), expr5, expr11);
                                                    return expr12;
                                                  }
                                                );
                           return expr13;
                         }
                       );
  if (ud::get_stored_value(expr14)) {
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
  auto const& expr8 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                        ud::get_context(ctx, "hstd_test_model.py", 147),
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                          ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::MapEmpty);
                          ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                          return expr3;
                        },
                        [&]() -> ud::S<bool> {
                          ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr4 = ud::eval_op<ud::OpId::MAP_EMPTY, ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 428));
                          ud::S<int64_t> const& expr5 = ud::eval_op<ud::OpId::MAP_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 428), expr4);
                          ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                          ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 428), expr5, expr6);
                          return expr7;
                        }
                      );
  if (ud::get_stored_value(expr8)) {
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
  auto const& expr6 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                        ud::get_context(ctx, "hstd_test_model.py", 147),
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                          ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::OptHasValue);
                          ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                          return expr3;
                        },
                        [&]() -> ud::S<bool> {
                          ud::S<ud::UniOpt<ud::S<int64_t>>> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniOpt<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 429), expr0, "optional");
                          ud::S<bool> const& expr5 = ud::eval_op<ud::OpId::OPT_HAS_VALUE, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 429), expr4);
                          return expr5;
                        }
                      );
  if (ud::get_stored_value(expr6)) {
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
  auto const& expr11 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                         ud::get_context(ctx, "hstd_test_model.py", 147),
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                           ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::OptValue);
                           ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                           return expr3;
                         },
                         [&]() -> ud::S<bool> {
                           auto const& expr10 = ud::eval_op<ud::OpId::AND, ud::S<bool>>(
                                                  ud::get_context(ctx, "hstd_test_model.py", 432),
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<ud::UniOpt<ud::S<int64_t>>> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniOpt<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 433), expr0, "optional");
                                                    ud::S<bool> const& expr5 = ud::eval_op<ud::OpId::OPT_HAS_VALUE, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 433), expr4);
                                                    return expr5;
                                                  },
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<ud::UniOpt<ud::S<int64_t>>> const& expr6 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniOpt<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 434), expr0, "optional");
                                                    ud::S<int64_t> const& expr7 = ud::eval_op<ud::OpId::OPT_VALUE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 434), expr6);
                                                    ud::S<int64_t> const& expr8 = ud::S<int64_t>::FromConst(static_cast<int64_t>(3), "3");
                                                    ud::S<bool> const& expr9 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 434), expr7, expr8);
                                                    return expr9;
                                                  }
                                                );
                           return expr10;
                         }
                       );
  if (ud::get_stored_value(expr11)) {
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
  auto const& expr7 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                        ud::get_context(ctx, "hstd_test_model.py", 147),
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                          ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::CaseIs);
                          ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                          return expr3;
                        },
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::Choice> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Choice>>(ud::get_context(ctx, "hstd_test_model.py", 445), expr0, "choice");
                          ud::S<hstd::unidata_dsl::test::Choice::Data> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Choice::Data>>(ud::get_context(ctx, "hstd_test_model.py", 445), expr4, "data");
                          ud::S<bool> const& expr6 = ud::eval_op<ud::OpId::CASE_IS, ud::S<bool>, hstd::unidata_dsl::test::Choice::First>(ud::get_context(ctx, "hstd_test_model.py", 445), expr5);
                          return expr6;
                        }
                      );
  if (ud::get_stored_value(expr7)) {
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
  auto const& expr8 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                        ud::get_context(ctx, "hstd_test_model.py", 147),
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                          ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::CaseWhich);
                          ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                          return expr3;
                        },
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::Choice> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Choice>>(ud::get_context(ctx, "hstd_test_model.py", 448), expr0, "choice");
                          ud::S<hstd::unidata_dsl::test::Choice::Data> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Choice::Data>>(ud::get_context(ctx, "hstd_test_model.py", 448), expr4, "data");
                          ud::S<hstd::unidata_dsl::test::Choice::Kind> const& expr6 = ud::eval_op<ud::OpId::CASE_WHICH, ud::S<hstd::unidata_dsl::test::Choice::Kind>>(ud::get_context(ctx, "hstd_test_model.py", 448), expr5);
                          ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 448), expr6, hstd::unidata_dsl::test::Choice::Kind::First);
                          return expr7;
                        }
                      );
  if (ud::get_stored_value(expr8)) {
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
  auto const& expr14 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                         ud::get_context(ctx, "hstd_test_model.py", 147),
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                           ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::CaseField);
                           ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                           return expr3;
                         },
                         [&]() -> ud::S<bool> {
                           auto const& expr11 = ud::eval_op<ud::OpId::COND, ud::S<int64_t>>(
                                                  ud::get_context(ctx, "hstd_test_model.py", 452),
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<hstd::unidata_dsl::test::Choice> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Choice>>(ud::get_context(ctx, "hstd_test_model.py", 454), expr0, "choice");
                                                    ud::S<hstd::unidata_dsl::test::Choice::Data> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Choice::Data>>(ud::get_context(ctx, "hstd_test_model.py", 454), expr4, "data");
                                                    ud::S<bool> const& expr6 = ud::eval_op<ud::OpId::CASE_IS, ud::S<bool>, hstd::unidata_dsl::test::Choice::First>(ud::get_context(ctx, "hstd_test_model.py", 454), expr5);
                                                    return expr6;
                                                  },
                                                  [&]() -> ud::S<int64_t> {
                                                    ud::S<hstd::unidata_dsl::test::Choice> const& expr7 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Choice>>(ud::get_context(ctx, "hstd_test_model.py", 455), expr0, "choice");
                                                    ud::S<hstd::unidata_dsl::test::Choice::Data> const& expr8 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Choice::Data>>(ud::get_context(ctx, "hstd_test_model.py", 455), expr7, "data");
                                                    ud::S<int64_t> const& expr9 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 455), expr8, "value");
                                                    return expr9;
                                                  },
                                                  [&]() -> ud::S<int64_t> {
                                                    ud::S<int64_t> const& expr10 = ud::S<int64_t>::FromConst(static_cast<int64_t>(-1), "-1");
                                                    return expr10;
                                                  }
                                                );
                           ud::S<int64_t> const& expr12 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
                           ud::S<bool> const& expr13 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 452), expr11, expr12);
                           return expr13;
                         }
                       );
  if (ud::get_stored_value(expr14)) {
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
  auto const& expr6 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                        ud::get_context(ctx, "hstd_test_model.py", 147),
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                          ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::EnumIs);
                          ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                          return expr3;
                        },
                        [&]() -> ud::S<bool> {
                          ud::S<hstd::unidata_dsl::test::Status> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Status>>(ud::get_context(ctx, "hstd_test_model.py", 461), expr0, "status");
                          ud::S<bool> const& expr5 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 461), expr4, hstd::unidata_dsl::test::Status::Ready);
                          return expr5;
                        }
                      );
  if (ud::get_stored_value(expr6)) {
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
  auto const& expr13 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                         ud::get_context(ctx, "hstd_test_model.py", 147),
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                           ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::NthGet);
                           ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                           return expr3;
                         },
                         [&]() -> ud::S<bool> {
                           auto const& expr12 = ud::eval_op<ud::OpId::AND, ud::S<bool>>(
                                                  ud::get_context(ctx, "hstd_test_model.py", 464),
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<ud::UniTuple<ud::S<int64_t>, ud::S<hstd::Str>>> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniTuple<ud::S<int64_t>, ud::S<hstd::Str>>>>(ud::get_context(ctx, "hstd_test_model.py", 465), expr0, "coords");
                                                    ud::S<int64_t> const& expr5 = ud::eval_op<ud::OpId::NTH_GET, ud::S<int64_t>, 0>(ud::get_context(ctx, "hstd_test_model.py", 465), expr4);
                                                    ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
                                                    ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 465), expr5, expr6);
                                                    return expr7;
                                                  },
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<ud::UniTuple<ud::S<int64_t>, ud::S<hstd::Str>>> const& expr8 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniTuple<ud::S<int64_t>, ud::S<hstd::Str>>>>(ud::get_context(ctx, "hstd_test_model.py", 466), expr0, "coords");
                                                    ud::S<hstd::Str> const& expr9 = ud::eval_op<ud::OpId::NTH_GET, ud::S<hstd::Str>, 1>(ud::get_context(ctx, "hstd_test_model.py", 466), expr8);
                                                    ud::S<hstd::Str> const& expr10 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("six"), "six");
                                                    ud::S<bool> const& expr11 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 466), expr9, expr10);
                                                    return expr11;
                                                  }
                                                );
                           return expr12;
                         }
                       );
  if (ud::get_stored_value(expr13)) {
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
  auto const& expr10 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                         ud::get_context(ctx, "hstd_test_model.py", 147),
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                           ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::IsDerived);
                           ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                           return expr3;
                         },
                         [&]() -> ud::S<bool> {
                           auto const& expr9 = ud::eval_op<ud::OpId::AND, ud::S<bool>>(
                                                 ud::get_context(ctx, "hstd_test_model.py", 471),
                                                 [&]() -> ud::S<bool> {
                                                   ud::S<hstd::unidata_dsl::test::Derived> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Derived>>(ud::get_context(ctx, "hstd_test_model.py", 472), expr0, "derived");
                                                   ud::S<bool> const& expr5 = ud::eval_op<ud::OpId::IS_DERIVED, ud::S<bool>, hstd::unidata_dsl::test::Base>(ud::get_context(ctx, "hstd_test_model.py", 472), expression_runtime, expr4);
                                                   return expr5;
                                                 },
                                                 [&]() -> ud::S<bool> {
                                                   ud::S<hstd::unidata_dsl::test::Base> const& expr6 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Base>>(ud::get_context(ctx, "hstd_test_model.py", 473), expr0, "base");
                                                   ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::IS_DERIVED, ud::S<bool>, hstd::unidata_dsl::test::Derived>(ud::get_context(ctx, "hstd_test_model.py", 473), expression_runtime, expr6);
                                                   ud::S<bool> const& expr8 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 473), (expr7));
                                                   return expr8;
                                                 }
                                               );
                           return expr9;
                         }
                       );
  if (ud::get_stored_value(expr10)) {
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
  auto const& expr15 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                         ud::get_context(ctx, "hstd_test_model.py", 147),
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                           ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::TypeCond);
                           ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                           return expr3;
                         },
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::Derived> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Derived>>(ud::get_context(ctx, "hstd_test_model.py", 479), expr0, "derived");
                           ud::S<ud::UniVec<ud::UniDynamic>> const& expr5 = ud::eval_op<ud::OpId::WALK, ud::S<ud::UniVec<ud::UniDynamic>>>(ud::get_context(ctx, "hstd_test_model.py", 479), expression_runtime, expr4);
                           ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                           ud::UniDynamic const& expr7 = ud::eval_op<ud::OpId::LIST_AT, ud::UniDynamic>(ud::get_context(ctx, "hstd_test_model.py", 479), expr5, expr6);
                           ud::S<ud::UniOpt<ud::S<int64_t>>> result8 = ud::S<ud::UniOpt<ud::S<int64_t>>>::FromConst(std::nullopt, "std::nullopt");
                           if (!ud::get_stored_as_bool(result8)) {
                             hstd::Opt<ud::S<hstd::unidata_dsl::test::Base>> candidate9 = expression_runtime.try_as<hstd::unidata_dsl::test::Base>(expr7);
                             if (candidate9.has_value()) {
                               ud::S<int64_t> const& expr10 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 483), (*candidate9), "id");
                               ud::set_value(result8, expr10);
                             }
                           }
                           if (!ud::get_stored_as_bool(result8)) {
                             hstd::Opt<ud::S<hstd::unidata_dsl::test::Derived>> candidate11 = expression_runtime.try_as<hstd::unidata_dsl::test::Derived>(expr7);
                             if (candidate11.has_value()) {
                               ud::S<int64_t> const& expr12 = ud::S<int64_t>::FromConst(static_cast<int64_t>(-1), "-1");
                               ud::set_value(result8, expr12);
                             }
                           }
                           if (!ud::get_stored_as_bool(result8)) {
                             throw std::runtime_error{"No type case matched at hstd_test_model.py:478; expected one of: Base, Derived"};
                           }
                           ud::S<int64_t> const& expr13 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
                           ud::S<bool> const& expr14 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 478), ud::get_value_ref(result8), expr13);
                           return expr14;
                         }
                       );
  if (ud::get_stored_value(expr15)) {
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
  auto const& expr24 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                         ud::get_context(ctx, "hstd_test_model.py", 147),
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                           ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::TypeCondOptional);
                           ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                           return expr3;
                         },
                         [&]() -> ud::S<bool> {
                           auto const& expr23 = ud::eval_op<ud::OpId::AND, ud::S<bool>>(
                                                  ud::get_context(ctx, "hstd_test_model.py", 495),
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<hstd::unidata_dsl::test::Base> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Base>>(ud::get_context(ctx, "hstd_test_model.py", 497), expr0, "base");
                                                    ud::S<ud::UniVec<ud::UniDynamic>> const& expr5 = ud::eval_op<ud::OpId::WALK, ud::S<ud::UniVec<ud::UniDynamic>>>(ud::get_context(ctx, "hstd_test_model.py", 497), expression_runtime, expr4);
                                                    ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                                                    ud::UniDynamic const& expr7 = ud::eval_op<ud::OpId::LIST_AT, ud::UniDynamic>(ud::get_context(ctx, "hstd_test_model.py", 497), expr5, expr6);
                                                    ud::S<ud::UniOpt<ud::S<int64_t>>> result8 = ud::S<ud::UniOpt<ud::S<int64_t>>>::FromConst(std::nullopt, "std::nullopt");
                                                    if (!ud::get_stored_as_bool(result8)) {
                                                      hstd::Opt<ud::S<hstd::unidata_dsl::test::Derived>> candidate9 = expression_runtime.try_as<hstd::unidata_dsl::test::Derived>(expr7);
                                                      if (candidate9.has_value()) {
                                                        ud::S<int64_t> const& expr10 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 501), (*candidate9), "id");
                                                        ud::set_value(result8, expr10);
                                                      }
                                                    }
                                                    ud::S<bool> const& expr11 = ud::eval_op<ud::OpId::OPT_HAS_VALUE, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 504), result8);
                                                    ud::S<bool> const& expr12 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 496), (expr11));
                                                    return expr12;
                                                  },
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<hstd::unidata_dsl::test::Derived> const& expr13 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Derived>>(ud::get_context(ctx, "hstd_test_model.py", 506), expr0, "derived");
                                                    ud::S<ud::UniVec<ud::UniDynamic>> const& expr14 = ud::eval_op<ud::OpId::WALK, ud::S<ud::UniVec<ud::UniDynamic>>>(ud::get_context(ctx, "hstd_test_model.py", 506), expression_runtime, expr13);
                                                    ud::S<int64_t> const& expr15 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                                                    ud::UniDynamic const& expr16 = ud::eval_op<ud::OpId::LIST_AT, ud::UniDynamic>(ud::get_context(ctx, "hstd_test_model.py", 506), expr14, expr15);
                                                    ud::S<ud::UniOpt<ud::S<int64_t>>> result17 = ud::S<ud::UniOpt<ud::S<int64_t>>>::FromConst(std::nullopt, "std::nullopt");
                                                    if (!ud::get_stored_as_bool(result17)) {
                                                      hstd::Opt<ud::S<hstd::unidata_dsl::test::Derived>> candidate18 = expression_runtime.try_as<hstd::unidata_dsl::test::Derived>(expr16);
                                                      if (candidate18.has_value()) {
                                                        ud::S<int64_t> const& expr19 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 507), (*candidate18), "id");
                                                        ud::set_value(result17, expr19);
                                                      }
                                                    }
                                                    ud::S<int64_t> const& expr20 = ud::eval_op<ud::OpId::OPT_VALUE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 509), result17);
                                                    ud::S<int64_t> const& expr21 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
                                                    ud::S<bool> const& expr22 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 505), expr20, expr21);
                                                    return expr22;
                                                  }
                                                );
                           return expr23;
                         }
                       );
  if (ud::get_stored_value(expr24)) {
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
  //                 type_text typed_as='string'
  //                     type_of typed_as='run_type'
  //                         var typed_as='Base' str_val='record'
  //         const_str typed_as='string' str_val='Derived'
  //
  hstd::ext::unidata::EvalRuntime expression_runtime = hstd::ext::unidata::EvalRuntime{ctx};
  __populate_expression_runtime(expression_runtime);
  auto const& expr0 = (this_obj);
  auto const& expr14 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                         ud::get_context(ctx, "hstd_test_model.py", 147),
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                           ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::TypeOf);
                           ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                           return expr3;
                         },
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::Derived> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Derived>>(ud::get_context(ctx, "hstd_test_model.py", 520), expr0, "derived");
                           ud::S<ud::UniVec<ud::UniDynamic>> const& expr5 = ud::eval_op<ud::OpId::WALK, ud::S<ud::UniVec<ud::UniDynamic>>>(ud::get_context(ctx, "hstd_test_model.py", 520), expression_runtime, expr4);
                           ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                           ud::UniDynamic const& expr7 = ud::eval_op<ud::OpId::LIST_AT, ud::UniDynamic>(ud::get_context(ctx, "hstd_test_model.py", 520), expr5, expr6);
                           ud::S<ud::UniOpt<ud::S<hstd::Str>>> result8 = ud::S<ud::UniOpt<ud::S<hstd::Str>>>::FromConst(std::nullopt, "std::nullopt");
                           if (!ud::get_stored_as_bool(result8)) {
                             hstd::Opt<ud::S<hstd::unidata_dsl::test::Base>> candidate9 = expression_runtime.try_as<hstd::unidata_dsl::test::Base>(expr7);
                             if (candidate9.has_value()) {
                               ud::S<hstd::ext::unidata::UniType> const& expr10 = ud::eval_op<ud::OpId::TYPE_OF, ud::S<hstd::ext::unidata::UniType>>(ud::get_context(ctx, "hstd_test_model.py", 522), expression_runtime, (*candidate9));
                               ud::S<hstd::Str> const& expr11 = ud::eval_op<ud::OpId::TYPE_TEXT, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 522), expr10);
                               ud::set_value(result8, expr11);
                             }
                           }
                           if (!ud::get_stored_as_bool(result8)) {
                             throw std::runtime_error{"No type case matched at hstd_test_model.py:519; expected one of: Base"};
                           }
                           ud::S<hstd::Str> const& expr12 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("Derived"), "Derived");
                           ud::S<bool> const& expr13 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 519), ud::get_value_ref(result8), expr12);
                           return expr13;
                         }
                       );
  if (ud::get_stored_value(expr14)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr15 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("poc.TypeOf"), "poc.TypeOf");
    return ud::VerifyResult::Error(ud::get_stored_value(expr15));
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
  auto const& expr30 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                         ud::get_context(ctx, "hstd_test_model.py", 147),
                         [&]() -> ud::S<bool> {
                           ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                           ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::PathOf);
                           ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                           return expr3;
                         },
                         [&]() -> ud::S<bool> {
                           auto const& expr29 = ud::eval_op<ud::OpId::AND, ud::S<bool>>(
                                                  ud::get_context(ctx, "hstd_test_model.py", 529),
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<int64_t> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 530), expr0, "number");
                                                    ud::S<hstd::ext::unidata::UniPath> const& expr5 = ud::eval_op<ud::OpId::PATH_OF, ud::S<hstd::ext::unidata::UniPath>>(ud::get_context(ctx, "hstd_test_model.py", 530), expression_runtime, expr4);
                                                    ud::S<hstd::Str> const& expr6 = ud::eval_op<ud::OpId::STR_FORMAT, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 530), eval_str_pattern("{}"), expr5);
                                                    ud::S<hstd::Str> const& expr7 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("/number"), "/number");
                                                    ud::S<bool> const& expr8 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 530), expr6, expr7);
                                                    return expr8;
                                                  },
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<ud::UniVec<ud::S<int64_t>>> const& expr9 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 532), expr0, "numbers");
                                                    auto callback13 = [&](ud::S<int64_t> const& item10) -> ud::S<hstd::Str> {
                                                                        // str_format typed_as='string' str_val='{}'
                                                                        //     path_of typed_as='path'
                                                                        //         var typed_as='int64' str_val='number'
                                                                        //
                                                                        ud::S<hstd::ext::unidata::UniPath> const& expr11 = ud::eval_op<ud::OpId::PATH_OF, ud::S<hstd::ext::unidata::UniPath>>(ud::get_context(ctx, "hstd_test_model.py", 534), expression_runtime, item10);
                                                                        ud::S<hstd::Str> const& expr12 = ud::eval_op<ud::OpId::STR_FORMAT, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 534), eval_str_pattern("{}"), expr11);
                                                                        return expr12;
                                                                      };
                                                    ud::S<ud::UniVec<ud::S<hstd::Str>>> const& expr14 = ud::eval_op<ud::OpId::MAP, ud::S<ud::UniVec<ud::S<hstd::Str>>>>(ud::get_context(ctx, "hstd_test_model.py", 531), expr9, callback13);
                                                    ud::S<int64_t> const& expr15 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                                                    ud::S<hstd::Str> const& expr16 = ud::eval_op<ud::OpId::LIST_AT, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 535), expr14, expr15);
                                                    ud::S<hstd::Str> const& expr17 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("/numbers/0"), "/numbers/0");
                                                    ud::S<bool> const& expr18 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 531), expr16, expr17);
                                                    return expr18;
                                                  },
                                                  [&]() -> ud::S<bool> {
                                                    ud::S<hstd::unidata_dsl::test::Derived> const& expr19 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::Derived>>(ud::get_context(ctx, "hstd_test_model.py", 538), expr0, "derived");
                                                    ud::S<ud::UniVec<ud::UniDynamic>> const& expr20 = ud::eval_op<ud::OpId::WALK, ud::S<ud::UniVec<ud::UniDynamic>>>(ud::get_context(ctx, "hstd_test_model.py", 538), expression_runtime, expr19);
                                                    ud::S<int64_t> const& expr21 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                                                    ud::UniDynamic const& expr22 = ud::eval_op<ud::OpId::LIST_AT, ud::UniDynamic>(ud::get_context(ctx, "hstd_test_model.py", 538), expr20, expr21);
                                                    ud::S<ud::UniOpt<ud::S<hstd::Str>>> result23 = ud::S<ud::UniOpt<ud::S<hstd::Str>>>::FromConst(std::nullopt, "std::nullopt");
                                                    if (!ud::get_stored_as_bool(result23)) {
                                                      hstd::Opt<ud::S<hstd::unidata_dsl::test::Base>> candidate24 = expression_runtime.try_as<hstd::unidata_dsl::test::Base>(expr22);
                                                      if (candidate24.has_value()) {
                                                        ud::S<hstd::ext::unidata::UniPath> const& expr25 = ud::eval_op<ud::OpId::PATH_OF, ud::S<hstd::ext::unidata::UniPath>>(ud::get_context(ctx, "hstd_test_model.py", 542), expression_runtime, (*candidate24));
                                                        ud::S<hstd::Str> const& expr26 = ud::eval_op<ud::OpId::STR_FORMAT, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 542), eval_str_pattern("{}"), expr25);
                                                        ud::set_value(result23, expr26);
                                                      }
                                                    }
                                                    if (!ud::get_stored_as_bool(result23)) {
                                                      throw std::runtime_error{"No type case matched at hstd_test_model.py:537; expected one of: Base"};
                                                    }
                                                    ud::S<hstd::Str> const& expr27 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("/derived"), "/derived");
                                                    ud::S<bool> const& expr28 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 537), ud::get_value_ref(result23), expr27);
                                                    return expr28;
                                                  }
                                                );
                           return expr29;
                         }
                       );
  if (ud::get_stored_value(expr30)) {
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
  auto const& expr110 = ud::eval_op<ud::OpId::OR, ud::S<bool>>(
                          ud::get_context(ctx, "hstd_test_model.py", 147),
                          [&]() -> ud::S<bool> {
                            ud::S<hstd::unidata_dsl::test::CheckKind> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::unidata_dsl::test::CheckKind>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr0, "operation");
                            ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), expr1, hstd::unidata_dsl::test::CheckKind::EmptyCollections);
                            ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 148), (expr2));
                            return expr3;
                          },
                          [&]() -> ud::S<bool> {
                            auto const& expr109 = ud::eval_op<ud::OpId::AND, ud::S<bool>>(
                                                    ud::get_context(ctx, "hstd_test_model.py", 550),
                                                    [&]() -> ud::S<bool> {
                                                      ud::S<ud::UniVec<ud::S<int64_t>>> const& expr4 = ud::eval_op<ud::OpId::LIST_EMPTY, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 552));
                                                      auto callback8 = [&](ud::S<int64_t> const& item5) -> ud::S<bool> {
                                                                         // lt typed_as='bool'
                                                                         //     const_int typed_as='int64' int_val=0
                                                                         //     var typed_as='int64' str_val='number'
                                                                         //
                                                                         ud::S<int64_t> const& expr6 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                                                                         ud::S<bool> const& expr7 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 554), expr6, item5);
                                                                         return expr7;
                                                                       };
                                                      ud::S<bool> const& expr9 = ud::eval_op<ud::OpId::ALL, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 551), expr4, callback8);
                                                      return expr9;
                                                    },
                                                    [&]() -> ud::S<bool> {
                                                      ud::S<ud::UniVec<ud::S<int64_t>>> const& expr10 = ud::eval_op<ud::OpId::LIST_EMPTY, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 557));
                                                      auto callback14 = [&](ud::S<int64_t> const& item11) -> ud::S<bool> {
                                                                          // lt typed_as='bool'
                                                                          //     const_int typed_as='int64' int_val=0
                                                                          //     var typed_as='int64' str_val='number'
                                                                          //
                                                                          ud::S<int64_t> const& expr12 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                                                                          ud::S<bool> const& expr13 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 559), expr12, item11);
                                                                          return expr13;
                                                                        };
                                                      ud::S<bool> const& expr15 = ud::eval_op<ud::OpId::EXISTS, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 556), expr10, callback14);
                                                      ud::S<bool> const& expr16 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 556), (expr15));
                                                      return expr16;
                                                    },
                                                    [&]() -> ud::S<bool> {
                                                      ud::S<ud::UniVec<ud::S<int64_t>>> const& expr17 = ud::eval_op<ud::OpId::LIST_EMPTY, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 562));
                                                      auto callback21 = [&](ud::S<int64_t> const& item18) -> ud::S<bool> {
                                                                          // lt typed_as='bool'
                                                                          //     const_int typed_as='int64' int_val=0
                                                                          //     var typed_as='int64' str_val='number'
                                                                          //
                                                                          ud::S<int64_t> const& expr19 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                                                                          ud::S<bool> const& expr20 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 564), expr19, item18);
                                                                          return expr20;
                                                                        };
                                                      ud::S<bool> const& expr22 = ud::eval_op<ud::OpId::EXISTS_ONE, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 561), expr17, callback21);
                                                      ud::S<bool> const& expr23 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 561), (expr22));
                                                      return expr23;
                                                    },
                                                    [&]() -> ud::S<bool> {
                                                      ud::S<ud::UniVec<ud::S<int64_t>>> const& expr24 = ud::eval_op<ud::OpId::LIST_EMPTY, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 566));
                                                      ud::S<int64_t> const& expr25 = ud::eval_op<ud::OpId::SUM, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 566), expr24);
                                                      ud::S<int64_t> const& expr26 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                                                      ud::S<bool> const& expr27 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 566), expr25, expr26);
                                                      return expr27;
                                                    },
                                                    [&]() -> ud::S<bool> {
                                                      ud::S<ud::UniVec<ud::S<int64_t>>> const& expr28 = ud::eval_op<ud::OpId::LIST_EMPTY, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 568));
                                                      auto callback33 = [&](ud::S<int64_t> const& item29) -> ud::S<int64_t> {
                                                                          // map_get typed_as='int64'
                                                                          //     get_field typed_as='map<string, int64>' str_val='mapping'
                                                                          //         this typed_as='OperationChecks'
                                                                          //     const_str typed_as='string' str_val='absent'
                                                                          //
                                                                          ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr30 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 570), expr0, "mapping");
                                                                          ud::S<hstd::Str> const& expr31 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("absent"), "absent");
                                                                          ud::S<int64_t> const& expr32 = ud::eval_op<ud::OpId::MAP_GET, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 570), expr30, expr31);
                                                                          return expr32;
                                                                        };
                                                      ud::S<ud::UniVec<ud::S<int64_t>>> const& expr34 = ud::eval_op<ud::OpId::MAP, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 567), expr28, callback33);
                                                      ud::S<int64_t> const& expr35 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 571), expr34);
                                                      ud::S<int64_t> const& expr36 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                                                      ud::S<bool> const& expr37 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 567), expr35, expr36);
                                                      return expr37;
                                                    },
                                                    [&]() -> ud::S<bool> {
                                                      ud::S<ud::UniVec<ud::S<int64_t>>> const& expr38 = ud::eval_op<ud::OpId::LIST_EMPTY, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 574));
                                                      auto callback44 = [&](ud::S<int64_t> const& item39) -> ud::S<bool> {
                                                                          // eq typed_as='bool'
                                                                          //     opt_value typed_as='int64'
                                                                          //         get_field typed_as='optional<int64>' str_val='optional'
                                                                          //             this typed_as='OperationChecks'
                                                                          //     const_int typed_as='int64' int_val=0
                                                                          //
                                                                          ud::S<ud::UniOpt<ud::S<int64_t>>> const& expr40 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniOpt<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 576), expr0, "optional");
                                                                          ud::S<int64_t> const& expr41 = ud::eval_op<ud::OpId::OPT_VALUE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 576), expr40);
                                                                          ud::S<int64_t> const& expr42 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                                                                          ud::S<bool> const& expr43 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 576), expr41, expr42);
                                                                          return expr43;
                                                                        };
                                                      ud::S<ud::UniVec<ud::S<int64_t>>> const& expr45 = ud::eval_op<ud::OpId::FILTER, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 573), expr38, callback44);
                                                      ud::S<int64_t> const& expr46 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 577), expr45);
                                                      ud::S<int64_t> const& expr47 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                                                      ud::S<bool> const& expr48 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 573), expr46, expr47);
                                                      return expr48;
                                                    },
                                                    [&]() -> ud::S<bool> {
                                                      ud::S<ud::UniVec<ud::S<int64_t>>> const& expr49 = ud::eval_op<ud::OpId::LIST_EMPTY, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 580));
                                                      auto callback52 = [&](ud::S<int64_t> const& item50) -> ud::S<ud::UniOpt<ud::S<int64_t>>> {
                                                                          // get_field typed_as='optional<int64>' str_val='optional'
                                                                          //     this typed_as='OperationChecks'
                                                                          //
                                                                          ud::S<ud::UniOpt<ud::S<int64_t>>> const& expr51 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniOpt<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 582), expr0, "optional");
                                                                          return expr51;
                                                                        };
                                                      ud::S<ud::UniVec<ud::S<int64_t>>> const& expr53 = ud::eval_op<ud::OpId::FILTER_MAP, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 579), expr49, callback52);
                                                      ud::S<int64_t> const& expr54 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 583), expr53);
                                                      ud::S<int64_t> const& expr55 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                                                      ud::S<bool> const& expr56 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 579), expr54, expr55);
                                                      return expr56;
                                                    },
                                                    [&]() -> ud::S<bool> {
                                                      ud::S<ud::UniVec<ud::S<int64_t>>> const& expr57 = ud::eval_op<ud::OpId::LIST_EMPTY, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 586));
                                                      auto callback63 = [&](ud::S<int64_t> const& item58) -> ud::S<bool> {
                                                                          // eq typed_as='bool'
                                                                          //     opt_value typed_as='int64'
                                                                          //         get_field typed_as='optional<int64>' str_val='optional'
                                                                          //             this typed_as='OperationChecks'
                                                                          //     const_int typed_as='int64' int_val=0
                                                                          //
                                                                          ud::S<ud::UniOpt<ud::S<int64_t>>> const& expr59 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniOpt<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 588), expr0, "optional");
                                                                          ud::S<int64_t> const& expr60 = ud::eval_op<ud::OpId::OPT_VALUE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 588), expr59);
                                                                          ud::S<int64_t> const& expr61 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                                                                          ud::S<bool> const& expr62 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 588), expr60, expr61);
                                                                          return expr62;
                                                                        };
                                                      ud::S<ud::UniVec<ud::S<int64_t>>> const& expr64 = ud::eval_op<ud::OpId::TAKE_WHILE, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 585), expr57, callback63);
                                                      ud::S<int64_t> const& expr65 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 589), expr64);
                                                      ud::S<int64_t> const& expr66 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                                                      ud::S<bool> const& expr67 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 585), expr65, expr66);
                                                      return expr67;
                                                    },
                                                    [&]() -> ud::S<bool> {
                                                      ud::S<ud::UniVec<ud::S<int64_t>>> const& expr68 = ud::eval_op<ud::OpId::LIST_EMPTY, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 592));
                                                      auto callback73 = [&](ud::S<int64_t> const& item69) -> ud::S<int64_t> {
                                                                          // map_get typed_as='int64'
                                                                          //     get_field typed_as='map<string, int64>' str_val='mapping'
                                                                          //         this typed_as='OperationChecks'
                                                                          //     const_str typed_as='string' str_val='absent'
                                                                          //
                                                                          ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr70 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 594), expr0, "mapping");
                                                                          ud::S<hstd::Str> const& expr71 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("absent"), "absent");
                                                                          ud::S<int64_t> const& expr72 = ud::eval_op<ud::OpId::MAP_GET, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 594), expr70, expr71);
                                                                          return expr72;
                                                                        };
                                                      ud::S<ud::UniMap<ud::S<int64_t>, ud::S<ud::UniVec<ud::S<int64_t>>>>> const& expr74 = ud::eval_op<ud::OpId::GROUP_BY, ud::S<ud::UniMap<ud::S<int64_t>, ud::S<ud::UniVec<ud::S<int64_t>>>>>>(ud::get_context(ctx, "hstd_test_model.py", 591), expr68, callback73);
                                                      ud::S<int64_t> const& expr75 = ud::eval_op<ud::OpId::MAP_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 595), expr74);
                                                      ud::S<int64_t> const& expr76 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                                                      ud::S<bool> const& expr77 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 591), expr75, expr76);
                                                      return expr77;
                                                    },
                                                    [&]() -> ud::S<bool> {
                                                      ud::S<ud::UniVec<ud::S<int64_t>>> const& expr78 = ud::eval_op<ud::OpId::LIST_EMPTY, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 598));
                                                      ud::S<int64_t> const& expr79 = ud::S<int64_t>::FromConst(static_cast<int64_t>(9), "9");
                                                      auto callback80 = [&](ud::S<int64_t> const& item81, ud::S<int64_t> const& item82) -> ud::S<int64_t> {
                                                                          // map_get typed_as='int64'
                                                                          //     get_field typed_as='map<string, int64>' str_val='mapping'
                                                                          //         this typed_as='OperationChecks'
                                                                          //     const_str typed_as='string' str_val='absent'
                                                                          //
                                                                          ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr83 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 602), expr0, "mapping");
                                                                          ud::S<hstd::Str> const& expr84 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("absent"), "absent");
                                                                          ud::S<int64_t> const& expr85 = ud::eval_op<ud::OpId::MAP_GET, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 602), expr83, expr84);
                                                                          return expr85;
                                                                        };
                                                      ud::S<int64_t> const& expr86 = ud::eval_op<ud::OpId::FOLD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 597), expr78, expr79, callback80);
                                                      ud::S<int64_t> const& expr87 = ud::S<int64_t>::FromConst(static_cast<int64_t>(9), "9");
                                                      ud::S<bool> const& expr88 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 597), expr86, expr87);
                                                      return expr88;
                                                    },
                                                    [&]() -> ud::S<bool> {
                                                      ud::S<ud::UniVec<ud::S<int64_t>>> const& expr89 = ud::eval_op<ud::OpId::LIST_EMPTY, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 606));
                                                      ud::S<ud::UniVec<ud::S<int64_t>>> const& expr90 = ud::eval_op<ud::OpId::LIST_EMPTY, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 607));
                                                      ud::S<ud::UniVec<ud::S<int64_t>>> const& expr91 = ud::eval_op<ud::OpId::LIST_CONCAT, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 605), expr89, expr90);
                                                      ud::S<int64_t> const& expr92 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 608), expr91);
                                                      ud::S<int64_t> const& expr93 = ud::S<int64_t>::FromConst(static_cast<int64_t>(0), "0");
                                                      ud::S<bool> const& expr94 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 605), expr92, expr93);
                                                      return expr94;
                                                    },
                                                    [&]() -> ud::S<bool> {
                                                      auto const& expr99 = ud::eval_op<ud::OpId::COND, ud::S<int64_t>>(
                                                                             ud::get_context(ctx, "hstd_test_model.py", 610),
                                                                             [&]() -> ud::S<bool> {
                                                                               ud::S<bool> const& expr95 = ud::S<bool>::FromConst(static_cast<bool>(true), "true");
                                                                               return expr95;
                                                                             },
                                                                             [&]() -> ud::S<int64_t> {
                                                                               ud::S<int64_t> const& expr96 = ud::S<int64_t>::FromConst(static_cast<int64_t>(42), "42");
                                                                               return expr96;
                                                                             },
                                                                             [&]() -> ud::S<int64_t> {
                                                                               ud::S<ud::UniVec<ud::S<int64_t>>> const& expr97 = ud::eval_op<ud::OpId::LIST_EMPTY, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 612));
                                                                               ud::S<int64_t> const& expr98 = ud::eval_op<ud::OpId::MIN, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 612), expr97);
                                                                               return expr98;
                                                                             }
                                                                           );
                                                      ud::S<int64_t> const& expr100 = ud::S<int64_t>::FromConst(static_cast<int64_t>(42), "42");
                                                      ud::S<bool> const& expr101 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 610), expr99, expr100);
                                                      return expr101;
                                                    },
                                                    [&]() -> ud::S<bool> {
                                                      auto const& expr106 = ud::eval_op<ud::OpId::COND, ud::S<int64_t>>(
                                                                              ud::get_context(ctx, "hstd_test_model.py", 615),
                                                                              [&]() -> ud::S<bool> {
                                                                                ud::S<bool> const& expr102 = ud::S<bool>::FromConst(static_cast<bool>(true), "true");
                                                                                return expr102;
                                                                              },
                                                                              [&]() -> ud::S<int64_t> {
                                                                                ud::S<int64_t> const& expr103 = ud::S<int64_t>::FromConst(static_cast<int64_t>(42), "42");
                                                                                return expr103;
                                                                              },
                                                                              [&]() -> ud::S<int64_t> {
                                                                                ud::S<ud::UniVec<ud::S<int64_t>>> const& expr104 = ud::eval_op<ud::OpId::LIST_EMPTY, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 617));
                                                                                ud::S<int64_t> const& expr105 = ud::eval_op<ud::OpId::MAX, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 617), expr104);
                                                                                return expr105;
                                                                              }
                                                                            );
                                                      ud::S<int64_t> const& expr107 = ud::S<int64_t>::FromConst(static_cast<int64_t>(42), "42");
                                                      ud::S<bool> const& expr108 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 615), expr106, expr107);
                                                      return expr108;
                                                    }
                                                  );
                            return expr109;
                          }
                        );
  if (ud::get_stored_value(expr110)) {
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
  ud::S<int64_t> const& expr2 = ud::eval_op<ud::OpId::STR_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 635), expr0);
  ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 635), expr1, expr2);
  if (ud::get_stored_value(expr3)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<int64_t> const& expr4 = ud::eval_op<ud::OpId::STR_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 636), expr0);
    ud::S<hstd::Str> const& expr5 = ud::eval_op<ud::OpId::STR_FORMAT, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 636), eval_str_pattern("text length is {}"), expr4);
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
                     ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 639), expr2, item1);
                     return expr3;
                   };
  ud::S<bool> const& expr5 = ud::eval_op<ud::OpId::ALL, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 639), expr0, callback4);
  if (ud::get_stored_value(expr5)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<hstd::Str> const& expr6 = ud::eval_op<ud::OpId::STR_FORMAT, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 640), eval_str_pattern("values={}"), expr0);
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
  ud::S<int64_t> const& expr1 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 654), expr0, "number");
  ud::S<int64_t> const& expr2 = ud::S<int64_t>::FromConst(static_cast<int64_t>(6), "6");
  ud::S<bool> const& expr3 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 654), expr1, expr2);
  if (ud::get_stored_value(expr3)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<int64_t> const& expr4 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 657), expr0, "number");
    ud::S<double> const& expr5 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<double>>(ud::get_context(ctx, "hstd_test_model.py", 658), expr0, "real");
    ud::S<double> const& expr6 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<double>>(ud::get_context(ctx, "hstd_test_model.py", 659), expr0, "real");
    ud::S<int64_t> const& expr7 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 660), expr0, "number");
    ud::S<int64_t> const& expr8 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 661), expr0, "number");
    ud::S<bool> const& expr9 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 662), expr0, "flag");
    ud::S<hstd::Str> const& expr10 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 663), expr0, "text");
    ud::S<ud::UniVec<ud::S<int64_t>>> const& expr11 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniVec<ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 664), expr0, "numbers");
    ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>> const& expr12 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<int64_t>>>>(ud::get_context(ctx, "hstd_test_model.py", 665), expr0, "details");
    ud::S<hstd::Str> const& expr13 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("detail"), "detail");
    ud::S<int64_t> const& expr14 = ud::eval_op<ud::OpId::MAP_GET, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 665), expr12, expr13);
    ud::S<hstd::Str> const& expr15 = ud::eval_op<ud::OpId::STR_FORMAT, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 655), eval_str_pattern("n={} real={} sci={:e} hex={} oct={} flag={} text={} list={} lookup={}"), expr4, expr5, expr6, expr7, expr8, expr9, expr10, expr11, expr14);
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
  ud::S<ud::UniVec<ud::UniDynamic>> const& expr1 = ud::eval_op<ud::OpId::WALK, ud::S<ud::UniVec<ud::UniDynamic>>>(ud::get_context(ctx, "hstd_test_model.py", 682), expression_runtime, expr0);
  auto callback5 = [&](ud::UniDynamic const& item2) -> ud::S<ud::UniOpt<ud::S<hstd::unidata_dsl::test::Node>>> {
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
  ud::S<ud::UniVec<ud::S<hstd::unidata_dsl::test::Node>>> const& expr6 = ud::eval_op<ud::OpId::FILTER_MAP, ud::S<ud::UniVec<ud::S<hstd::unidata_dsl::test::Node>>>>(ud::get_context(ctx, "hstd_test_model.py", 681), expr1, callback5);
  auto callback9 = [&](ud::S<hstd::unidata_dsl::test::Node> const& item7) -> ud::S<hstd::Str> {
                     // get_field typed_as='string' str_val='id'
                     //     var typed_as='Node' str_val='node'
                     //
                     ud::S<hstd::Str> const& expr8 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 714), item7, "id");
                     return expr8;
                   };
  ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<ud::UniVec<ud::S<hstd::unidata_dsl::test::Node>>>>> const& expr10 = ud::eval_op<ud::OpId::GROUP_BY, ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<ud::UniVec<ud::S<hstd::unidata_dsl::test::Node>>>>>>(ud::get_context(ctx, "hstd_test_model.py", 711), expr6, callback9);
  ud::S<ud::UniVec<ud::S<ud::UniVec<ud::S<hstd::unidata_dsl::test::Node>>>>> const& expr11 = ud::eval_op<ud::OpId::MAP_VALUES, ud::S<ud::UniVec<ud::S<ud::UniVec<ud::S<hstd::unidata_dsl::test::Node>>>>>>(ud::get_context(ctx, "hstd_test_model.py", 715), expr10);
  auto callback16 = [&](ud::S<ud::UniVec<ud::S<hstd::unidata_dsl::test::Node>>> const& item12) -> ud::S<bool> {
                      // le typed_as='bool'
                      //     list_size typed_as='int64'
                      //         var typed_as='list<Node>' str_val='group'
                      //     const_int typed_as='int64' int_val=1
                      //
                      ud::S<int64_t> const& expr13 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 736), item12);
                      ud::S<int64_t> const& expr14 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
                      ud::S<bool> const& expr15 = ud::eval_op<ud::OpId::LE, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 736), expr13, expr14);
                      return expr15;
                    };
  ud::S<bool> const& expr17 = ud::eval_op<ud::OpId::ALL, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 733), expr11, callback16);
  if (ud::get_stored_value(expr17)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<ud::UniVec<ud::UniDynamic>> const& expr18 = ud::eval_op<ud::OpId::WALK, ud::S<ud::UniVec<ud::UniDynamic>>>(ud::get_context(ctx, "hstd_test_model.py", 682), expression_runtime, expr0);
    auto callback22 = [&](ud::UniDynamic const& item19) -> ud::S<ud::UniOpt<ud::S<hstd::unidata_dsl::test::Node>>> {
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
    ud::S<ud::UniVec<ud::S<hstd::unidata_dsl::test::Node>>> const& expr23 = ud::eval_op<ud::OpId::FILTER_MAP, ud::S<ud::UniVec<ud::S<hstd::unidata_dsl::test::Node>>>>(ud::get_context(ctx, "hstd_test_model.py", 681), expr18, callback22);
    auto callback26 = [&](ud::S<hstd::unidata_dsl::test::Node> const& item24) -> ud::S<hstd::Str> {
                        // get_field typed_as='string' str_val='id'
                        //     var typed_as='Node' str_val='node'
                        //
                        ud::S<hstd::Str> const& expr25 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 714), item24, "id");
                        return expr25;
                      };
    ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<ud::UniVec<ud::S<hstd::unidata_dsl::test::Node>>>>> const& expr27 = ud::eval_op<ud::OpId::GROUP_BY, ud::S<ud::UniMap<ud::S<hstd::Str>, ud::S<ud::UniVec<ud::S<hstd::unidata_dsl::test::Node>>>>>>(ud::get_context(ctx, "hstd_test_model.py", 711), expr23, callback26);
    ud::S<ud::UniVec<ud::S<ud::UniVec<ud::S<hstd::unidata_dsl::test::Node>>>>> const& expr28 = ud::eval_op<ud::OpId::MAP_VALUES, ud::S<ud::UniVec<ud::S<ud::UniVec<ud::S<hstd::unidata_dsl::test::Node>>>>>>(ud::get_context(ctx, "hstd_test_model.py", 715), expr27);
    auto callback33 = [&](ud::S<ud::UniVec<ud::S<hstd::unidata_dsl::test::Node>>> const& item29) -> ud::S<bool> {
                        // lt typed_as='bool'
                        //     const_int typed_as='int64' int_val=1
                        //     list_size typed_as='int64'
                        //         var typed_as='list<Node>' str_val='group'
                        //
                        ud::S<int64_t> const& expr30 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
                        ud::S<int64_t> const& expr31 = ud::eval_op<ud::OpId::LIST_SIZE, ud::S<int64_t>>(ud::get_context(ctx, "hstd_test_model.py", 723), item29);
                        ud::S<bool> const& expr32 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 723), expr30, expr31);
                        return expr32;
                      };
    ud::S<ud::UniVec<ud::S<ud::UniVec<ud::S<hstd::unidata_dsl::test::Node>>>>> const& expr34 = ud::eval_op<ud::OpId::FILTER, ud::S<ud::UniVec<ud::S<ud::UniVec<ud::S<hstd::unidata_dsl::test::Node>>>>>>(ud::get_context(ctx, "hstd_test_model.py", 720), expr28, callback33);
    auto callback40 = [&](ud::S<ud::UniVec<ud::S<hstd::unidata_dsl::test::Node>>> const& item35) -> ud::S<ud::UniVec<ud::S<hstd::ext::unidata::UniPath>>> {
                        // map typed_as='list<path>' binders='node'[Node]
                        //     var typed_as='list<Node>' str_val='group'
                        //     path_of typed_as='path'
                        //         var typed_as='Node' str_val='node'
                        //
                        auto callback38 = [&](ud::S<hstd::unidata_dsl::test::Node> const& item36) -> ud::S<hstd::ext::unidata::UniPath> {
                                            // path_of typed_as='path'
                                            //     var typed_as='Node' str_val='node'
                                            //
                                            ud::S<hstd::ext::unidata::UniPath> const& expr37 = ud::eval_op<ud::OpId::PATH_OF, ud::S<hstd::ext::unidata::UniPath>>(ud::get_context(ctx, "hstd_test_model.py", 746), expression_runtime, item36);
                                            return expr37;
                                          };
                        ud::S<ud::UniVec<ud::S<hstd::ext::unidata::UniPath>>> const& expr39 = ud::eval_op<ud::OpId::MAP, ud::S<ud::UniVec<ud::S<hstd::ext::unidata::UniPath>>>>(ud::get_context(ctx, "hstd_test_model.py", 743), item35, callback38);
                        return expr39;
                      };
    ud::S<ud::UniVec<ud::S<ud::UniVec<ud::S<hstd::ext::unidata::UniPath>>>>> const& expr41 = ud::eval_op<ud::OpId::MAP, ud::S<ud::UniVec<ud::S<ud::UniVec<ud::S<hstd::ext::unidata::UniPath>>>>>>(ud::get_context(ctx, "hstd_test_model.py", 740), expr34, callback40);
    ud::S<hstd::Str> const& expr42 = ud::eval_op<ud::OpId::STR_FORMAT, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 738), eval_str_pattern("duplicate node ids at {}"), expr41);
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
  ud::S<ud::UniVec<ud::UniDynamic>> const& expr1 = ud::eval_op<ud::OpId::WALK, ud::S<ud::UniVec<ud::UniDynamic>>>(ud::get_context(ctx, "hstd_test_model.py", 682), expression_runtime, expr0);
  auto callback5 = [&](ud::UniDynamic const& item2) -> ud::S<ud::UniOpt<ud::S<hstd::unidata_dsl::test::Node>>> {
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
  ud::S<ud::UniVec<ud::S<hstd::unidata_dsl::test::Node>>> const& expr6 = ud::eval_op<ud::OpId::FILTER_MAP, ud::S<ud::UniVec<ud::S<hstd::unidata_dsl::test::Node>>>>(ud::get_context(ctx, "hstd_test_model.py", 681), expr1, callback5);
  auto callback9 = [&](ud::S<hstd::unidata_dsl::test::Node> const& item7) -> ud::S<hstd::Str> {
                     // get_field typed_as='string' str_val='id'
                     //     var typed_as='Node' str_val='node'
                     //
                     ud::S<hstd::Str> const& expr8 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 697), item7, "id");
                     return expr8;
                   };
  ud::S<ud::UniVec<ud::S<hstd::Str>>> const& expr10 = ud::eval_op<ud::OpId::MAP, ud::S<ud::UniVec<ud::S<hstd::Str>>>>(ud::get_context(ctx, "hstd_test_model.py", 694), expr6, callback9);
  ud::S<ud::UniVec<ud::S<hstd::unidata_dsl::test::Edge>>> const& expr11 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniVec<ud::S<hstd::unidata_dsl::test::Edge>>>>(ud::get_context(ctx, "hstd_test_model.py", 758), expr0, "edges");
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
                      auto const& expr17 = ud::eval_op<ud::OpId::AND, ud::S<bool>>(
                                             ud::get_context(ctx, "hstd_test_model.py", 703),
                                             [&]() -> ud::S<bool> {
                                               ud::S<hstd::Str> const& expr13 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 704), item12, "source");
                                               ud::S<bool> const& expr14 = ud::eval_op<ud::OpId::LIST_CONTAINS, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 704), expr10, expr13);
                                               return expr14;
                                             },
                                             [&]() -> ud::S<bool> {
                                               ud::S<hstd::Str> const& expr15 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 705), item12, "target");
                                               ud::S<bool> const& expr16 = ud::eval_op<ud::OpId::LIST_CONTAINS, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 705), expr10, expr15);
                                               return expr16;
                                             }
                                           );
                      return expr17;
                    };
  ud::S<bool> const& expr19 = ud::eval_op<ud::OpId::ALL, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 757), expr11, callback18);
  if (ud::get_stored_value(expr19)) {
    return ud::VerifyResult::Ok();
  } else {
    ud::S<ud::UniVec<ud::UniDynamic>> const& expr20 = ud::eval_op<ud::OpId::WALK, ud::S<ud::UniVec<ud::UniDynamic>>>(ud::get_context(ctx, "hstd_test_model.py", 682), expression_runtime, expr0);
    auto callback24 = [&](ud::UniDynamic const& item21) -> ud::S<ud::UniOpt<ud::S<hstd::unidata_dsl::test::Node>>> {
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
    ud::S<ud::UniVec<ud::S<hstd::unidata_dsl::test::Node>>> const& expr25 = ud::eval_op<ud::OpId::FILTER_MAP, ud::S<ud::UniVec<ud::S<hstd::unidata_dsl::test::Node>>>>(ud::get_context(ctx, "hstd_test_model.py", 681), expr20, callback24);
    auto callback28 = [&](ud::S<hstd::unidata_dsl::test::Node> const& item26) -> ud::S<hstd::Str> {
                        // get_field typed_as='string' str_val='id'
                        //     var typed_as='Node' str_val='node'
                        //
                        ud::S<hstd::Str> const& expr27 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 697), item26, "id");
                        return expr27;
                      };
    ud::S<ud::UniVec<ud::S<hstd::Str>>> const& expr29 = ud::eval_op<ud::OpId::MAP, ud::S<ud::UniVec<ud::S<hstd::Str>>>>(ud::get_context(ctx, "hstd_test_model.py", 694), expr25, callback28);
    ud::S<ud::UniVec<ud::S<hstd::unidata_dsl::test::Edge>>> const& expr30 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<ud::UniVec<ud::S<hstd::unidata_dsl::test::Edge>>>>(ud::get_context(ctx, "hstd_test_model.py", 770), expr0, "edges");
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
                        auto const& expr36 = ud::eval_op<ud::OpId::AND, ud::S<bool>>(
                                               ud::get_context(ctx, "hstd_test_model.py", 703),
                                               [&]() -> ud::S<bool> {
                                                 ud::S<hstd::Str> const& expr32 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 704), item31, "source");
                                                 ud::S<bool> const& expr33 = ud::eval_op<ud::OpId::LIST_CONTAINS, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 704), expr29, expr32);
                                                 return expr33;
                                               },
                                               [&]() -> ud::S<bool> {
                                                 ud::S<hstd::Str> const& expr34 = ud::eval_op<ud::OpId::GET_FIELD, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 705), item31, "target");
                                                 ud::S<bool> const& expr35 = ud::eval_op<ud::OpId::LIST_CONTAINS, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 705), expr29, expr34);
                                                 return expr35;
                                               }
                                             );
                        ud::S<bool> const& expr37 = ud::eval_op<ud::OpId::NOT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 772), (expr36));
                        return expr37;
                      };
    ud::S<ud::UniVec<ud::S<hstd::unidata_dsl::test::Edge>>> const& expr39 = ud::eval_op<ud::OpId::FILTER, ud::S<ud::UniVec<ud::S<hstd::unidata_dsl::test::Edge>>>>(ud::get_context(ctx, "hstd_test_model.py", 769), expr30, callback38);
    auto callback42 = [&](ud::S<hstd::unidata_dsl::test::Edge> const& item40) -> ud::S<hstd::ext::unidata::UniPath> {
                        // path_of typed_as='path'
                        //     var typed_as='Edge' str_val='edge'
                        //
                        ud::S<hstd::ext::unidata::UniPath> const& expr41 = ud::eval_op<ud::OpId::PATH_OF, ud::S<hstd::ext::unidata::UniPath>>(ud::get_context(ctx, "hstd_test_model.py", 775), expression_runtime, item40);
                        return expr41;
                      };
    ud::S<ud::UniVec<ud::S<hstd::ext::unidata::UniPath>>> const& expr43 = ud::eval_op<ud::OpId::MAP, ud::S<ud::UniVec<ud::S<hstd::ext::unidata::UniPath>>>>(ud::get_context(ctx, "hstd_test_model.py", 768), expr39, callback42);
    ud::S<hstd::Str> const& expr44 = ud::eval_op<ud::OpId::STR_FORMAT, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 766), eval_str_pattern("dangling edges at {}"), expr43);
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
  auto const& expr9 = ud::eval_op<ud::OpId::COND, ud::S<bool>>(
                        ud::get_context(ctx, "hstd_test_model.py", 784),
                        [&]() -> ud::S<bool> {
                          ud::S<int64_t> const& expr1 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
                          ud::S<bool> const& expr2 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 785), expr0, expr1);
                          return expr2;
                        },
                        [&]() -> ud::S<bool> {
                          ud::S<bool> const& expr3 = ud::S<bool>::FromConst(static_cast<bool>(true), "true");
                          return expr3;
                        },
                        [&]() -> ud::S<bool> {
                          auto const& expr8 = ud::eval_op<ud::OpId::COND, ud::S<bool>>(
                                                ud::get_context(ctx, "hstd_test_model.py", 784),
                                                [&]() -> ud::S<bool> {
                                                  ud::S<int64_t> const& expr4 = ud::S<int64_t>::FromConst(static_cast<int64_t>(1), "1");
                                                  ud::S<bool> const& expr5 = ud::eval_op<ud::OpId::NE, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 786), expr0, expr4);
                                                  return expr5;
                                                },
                                                [&]() -> ud::S<bool> {
                                                  ud::S<bool> const& expr6 = ud::S<bool>::FromConst(static_cast<bool>(false), "false");
                                                  return expr6;
                                                },
                                                [&]() -> ud::S<bool> {
                                                  ud::S<bool> const& expr7 = ud::S<bool>::FromConst(static_cast<bool>(true), "true");
                                                  return expr7;
                                                }
                                              );
                          return expr8;
                        }
                      );
  if (ud::get_stored_value(expr9)) {
    return ud::VerifyResult::Ok();
  } else {
    auto const& expr29 = ud::eval_op<ud::OpId::COND, ud::S<hstd::Str>>(
                           ud::get_context(ctx, "hstd_test_model.py", 789),
                           [&]() -> ud::S<bool> {
                             ud::S<int64_t> const& expr10 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
                             ud::S<bool> const& expr11 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 791), expr0, expr10);
                             return expr11;
                           },
                           [&]() -> ud::S<hstd::Str> {
                             ud::S<hstd::Str> const& expr12 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("field bad: value two"), "field bad: value two");
                             return expr12;
                           },
                           [&]() -> ud::S<hstd::Str> {
                             auto const& expr28 = ud::eval_op<ud::OpId::COND, ud::S<hstd::Str>>(
                                                    ud::get_context(ctx, "hstd_test_model.py", 789),
                                                    [&]() -> ud::S<bool> {
                                                      auto const& expr17 = ud::eval_op<ud::OpId::AND, ud::S<bool>>(
                                                                             ud::get_context(ctx, "hstd_test_model.py", 795),
                                                                             [&]() -> ud::S<bool> {
                                                                               ud::S<int64_t> const& expr13 = ud::S<int64_t>::FromConst(static_cast<int64_t>(2), "2");
                                                                               ud::S<bool> const& expr14 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 795), expr13, expr0);
                                                                               return expr14;
                                                                             },
                                                                             [&]() -> ud::S<bool> {
                                                                               ud::S<int64_t> const& expr15 = ud::S<int64_t>::FromConst(static_cast<int64_t>(10), "10");
                                                                               ud::S<bool> const& expr16 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 795), expr0, expr15);
                                                                               return expr16;
                                                                             }
                                                                           );
                                                      return expr17;
                                                    },
                                                    [&]() -> ud::S<hstd::Str> {
                                                      ud::S<hstd::Str> const& expr18 = ud::eval_op<ud::OpId::STR_FORMAT, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 796), eval_str_pattern("mid-range invalid value: {}"), expr0);
                                                      return expr18;
                                                    },
                                                    [&]() -> ud::S<hstd::Str> {
                                                      auto const& expr27 = ud::eval_op<ud::OpId::COND, ud::S<hstd::Str>>(
                                                                             ud::get_context(ctx, "hstd_test_model.py", 789),
                                                                             [&]() -> ud::S<bool> {
                                                                               ud::S<int64_t> const& expr19 = ud::S<int64_t>::FromConst(static_cast<int64_t>(10), "10");
                                                                               ud::S<bool> const& expr20 = ud::eval_op<ud::OpId::EQ, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 799), expr0, expr19);
                                                                               return expr20;
                                                                             },
                                                                             [&]() -> ud::S<hstd::Str> {
                                                                               ud::S<hstd::Str> const& expr21 = ud::S<hstd::Str>::FromConst(static_cast<hstd::Str>("10, special-case number"), "10, special-case number");
                                                                               return expr21;
                                                                             },
                                                                             [&]() -> ud::S<hstd::Str> {
                                                                               auto const& expr26 = ud::eval_op<ud::OpId::COND, ud::S<hstd::Str>>(
                                                                                                      ud::get_context(ctx, "hstd_test_model.py", 789),
                                                                                                      [&]() -> ud::S<bool> {
                                                                                                        ud::S<int64_t> const& expr22 = ud::S<int64_t>::FromConst(static_cast<int64_t>(10), "10");
                                                                                                        ud::S<bool> const& expr23 = ud::eval_op<ud::OpId::LT, ud::S<bool>>(ud::get_context(ctx, "hstd_test_model.py", 803), expr22, expr0);
                                                                                                        return expr23;
                                                                                                      },
                                                                                                      [&]() -> ud::S<hstd::Str> {
                                                                                                        ud::S<hstd::Str> const& expr24 = ud::eval_op<ud::OpId::STR_FORMAT, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 804), eval_str_pattern("very large invalid value: {}"), expr0);
                                                                                                        return expr24;
                                                                                                      },
                                                                                                      [&]() -> ud::S<hstd::Str> {
                                                                                                        ud::S<hstd::Str> const& expr25 = ud::eval_op<ud::OpId::STR_FORMAT, ud::S<hstd::Str>>(ud::get_context(ctx, "hstd_test_model.py", 806), eval_str_pattern("unexpected range of invalid-ness {}"), expr0);
                                                                                                        return expr25;
                                                                                                      }
                                                                                                    );
                                                                               return expr26;
                                                                             }
                                                                           );
                                                      return expr27;
                                                    }
                                                  );
                             return expr28;
                           }
                         );
    return ud::VerifyResult::Error(ud::get_stored_value(expr29));
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