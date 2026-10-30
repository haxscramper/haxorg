/* clang-format off */
#include "tUnidataDSLModel.hpp"


hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::TrivialText::__check_text_text_check(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::TrivialText const*>(value);
  auto const& expr0 = (*(&this_obj->text));
  // const_int[int64](int_val=0)
  auto const& expr1 = static_cast<int64_t>(0);
  // str_size[int64](this[string]())
  auto const& expr2 = hstd::ext::unidata::eval_str_size(&expr0);
  // const_int[int64](int_val=0) < str_size[int64](this[string]())
  auto const& expr3 = (expr1 < expr2);
  if (expr3) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="text must not be empty")
    auto const& expr4 = hstd::Str{"text must not be empty"};
    return hstd::ext::unidata::VerifyResult::Error(expr4);
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
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::Base const*>(value);
  auto const& expr0 = (*(this_obj));
  // const_int[int64](int_val=0)
  auto const& expr1 = static_cast<int64_t>(0);
  // get_field[int64](this[Base](), str_val="id")
  auto const& expr2 = expr0.id;
  // const_int[int64](int_val=0) < get_field[int64](this[Base](), str_val="id")
  auto const& expr3 = (expr1 < expr2);
  if (expr3) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="base id must be positive")
    auto const& expr4 = hstd::Str{"base id must be positive"};
    return hstd::ext::unidata::VerifyResult::Error(expr4);
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
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::Derived const*>(value);
  auto const& expr0 = (*(this_obj));
  // const_int[int64](int_val=0)
  auto const& expr1 = static_cast<int64_t>(0);
  // get_field[int64](this[Derived](), str_val="weight")
  auto const& expr2 = expr0.weight;
  // const_int[int64](int_val=0) < get_field[int64](this[Derived](), str_val="weight")
  auto const& expr3 = (expr1 < expr2);
  if (expr3) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="derived weight must be positive")
    auto const& expr4 = hstd::Str{"derived weight must be positive"};
    return hstd::ext::unidata::VerifyResult::Error(expr4);
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
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Eq"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Eq);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Eq"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[int64](this[OperationChecks](), str_val="number")
    auto const& expr5 = expr0.number;
    // const_int[int64](int_val=6)
    auto const& expr6 = static_cast<int64_t>(6);
    // get_field[int64](this[OperationChecks](), str_val="number") == const_int[int64](int_val=6)
    auto const& expr7 = hstd::ext::unidata::eval_equal(expr5, expr6);
    condition1 = expr7;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.Eq")
    auto const& expr8 = hstd::Str{"poc.Eq"};
    return hstd::ext::unidata::VerifyResult::Error(expr8);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Ne(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Ne"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Ne);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Ne"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[int64](this[OperationChecks](), str_val="number")
    auto const& expr5 = expr0.number;
    // const_int[int64](int_val=8)
    auto const& expr6 = static_cast<int64_t>(8);
    // get_field[int64](this[OperationChecks](), str_val="number") != const_int[int64](int_val=8)
    auto const& expr7 = !(hstd::ext::unidata::eval_equal(expr5, expr6));
    condition1 = expr7;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.Ne")
    auto const& expr8 = hstd::Str{"poc.Ne"};
    return hstd::ext::unidata::VerifyResult::Error(expr8);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Lt(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Lt"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Lt);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Lt"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[int64](this[OperationChecks](), str_val="number")
    auto const& expr5 = expr0.number;
    // const_int[int64](int_val=7)
    auto const& expr6 = static_cast<int64_t>(7);
    // get_field[int64](this[OperationChecks](), str_val="number") < const_int[int64](int_val=7)
    auto const& expr7 = (expr5 < expr6);
    condition1 = expr7;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.Lt")
    auto const& expr8 = hstd::Str{"poc.Lt"};
    return hstd::ext::unidata::VerifyResult::Error(expr8);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Le(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Le"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Le);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Le"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[int64](this[OperationChecks](), str_val="number")
    auto const& expr5 = expr0.number;
    // const_int[int64](int_val=6)
    auto const& expr6 = static_cast<int64_t>(6);
    // get_field[int64](this[OperationChecks](), str_val="number") <= const_int[int64](int_val=6)
    auto const& expr7 = (expr5 <= expr6);
    condition1 = expr7;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.Le")
    auto const& expr8 = hstd::Str{"poc.Le"};
    return hstd::ext::unidata::VerifyResult::Error(expr8);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Add(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Add"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Add);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Add"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[int64](this[OperationChecks](), str_val="number")
    auto const& expr5 = expr0.number;
    // const_int[int64](int_val=3)
    auto const& expr6 = static_cast<int64_t>(3);
    // get_field[int64](this[OperationChecks](), str_val="number") + const_int[int64](int_val=3)
    auto const& expr7 = static_cast<int64_t>((expr5 + expr6));
    // const_int[int64](int_val=9)
    auto const& expr8 = static_cast<int64_t>(9);
    // get_field[int64](this[OperationChecks](), str_val="number") + const_int[int64](
    //     int_val=3
    // ) == const_int[int64](int_val=9)
    auto const& expr9 = hstd::ext::unidata::eval_equal(expr7, expr8);
    condition1 = expr9;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.Add")
    auto const& expr10 = hstd::Str{"poc.Add"};
    return hstd::ext::unidata::VerifyResult::Error(expr10);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Sub(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Sub"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Sub);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Sub"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[int64](this[OperationChecks](), str_val="number")
    auto const& expr5 = expr0.number;
    // const_int[int64](int_val=3)
    auto const& expr6 = static_cast<int64_t>(3);
    // get_field[int64](this[OperationChecks](), str_val="number") - const_int[int64](int_val=3)
    auto const& expr7 = static_cast<int64_t>((expr5 - expr6));
    // const_int[int64](int_val=3)
    auto const& expr8 = static_cast<int64_t>(3);
    // get_field[int64](this[OperationChecks](), str_val="number") - const_int[int64](
    //     int_val=3
    // ) == const_int[int64](int_val=3)
    auto const& expr9 = hstd::ext::unidata::eval_equal(expr7, expr8);
    condition1 = expr9;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.Sub")
    auto const& expr10 = hstd::Str{"poc.Sub"};
    return hstd::ext::unidata::VerifyResult::Error(expr10);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Mul(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Mul"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Mul);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Mul"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[int64](this[OperationChecks](), str_val="number")
    auto const& expr5 = expr0.number;
    // const_int[int64](int_val=3)
    auto const& expr6 = static_cast<int64_t>(3);
    // get_field[int64](this[OperationChecks](), str_val="number") * const_int[int64](int_val=3)
    auto const& expr7 = static_cast<int64_t>((expr5 * expr6));
    // const_int[int64](int_val=18)
    auto const& expr8 = static_cast<int64_t>(18);
    // get_field[int64](this[OperationChecks](), str_val="number") * const_int[int64](
    //     int_val=3
    // ) == const_int[int64](int_val=18)
    auto const& expr9 = hstd::ext::unidata::eval_equal(expr7, expr8);
    condition1 = expr9;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.Mul")
    auto const& expr10 = hstd::Str{"poc.Mul"};
    return hstd::ext::unidata::VerifyResult::Error(expr10);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Div(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Div"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Div);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Div"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[int64](this[OperationChecks](), str_val="number")
    auto const& expr5 = expr0.number;
    // const_int[int64](int_val=3)
    auto const& expr6 = static_cast<int64_t>(3);
    // get_field[int64](this[OperationChecks](), str_val="number") / const_int[int64](int_val=3)
    auto const& expr7 = static_cast<int64_t>((static_cast<int64_t>(expr5) / static_cast<int64_t>(expr6)));
    // const_int[int64](int_val=2)
    auto const& expr8 = static_cast<int64_t>(2);
    // get_field[int64](this[OperationChecks](), str_val="number") / const_int[int64](
    //     int_val=3
    // ) == const_int[int64](int_val=2)
    auto const& expr9 = hstd::ext::unidata::eval_equal(expr7, expr8);
    condition1 = expr9;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.Div")
    auto const& expr10 = hstd::Str{"poc.Div"};
    return hstd::ext::unidata::VerifyResult::Error(expr10);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ConstFloat(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="ConstFloat",
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::ConstFloat);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="ConstFloat",
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    bool condition5 = true;
    if (condition5) {
      // get_field[float64](this[OperationChecks](), str_val="real")
      auto const& expr6 = expr0.real;
      // const_float[float64](float_val=2.5)
      auto const& expr7 = static_cast<double>(2.5);
      // get_field[float64](this[OperationChecks](), str_val="real") == const_float[float64](
      //     float_val=2.5
      // )
      auto const& expr8 = hstd::ext::unidata::eval_equal(expr6, expr7);
      condition5 = expr8;
    }
    if (condition5) {
      // get_field[float64](this[OperationChecks](), str_val="real")
      auto const& expr9 = expr0.real;
      // const_float[float64](float_val=2.0)
      auto const& expr10 = static_cast<double>(2.0);
      // get_field[float64](this[OperationChecks](), str_val="real") / const_float[float64](
      //     float_val=2.0
      // )
      auto const& expr11 = static_cast<double>((static_cast<double>(expr9) / static_cast<double>(expr10)));
      // const_float[float64](float_val=1.25)
      auto const& expr12 = static_cast<double>(1.25);
      // get_field[float64](this[OperationChecks](), str_val="real") / const_float[float64](
      //     float_val=2.0
      // ) == const_float[float64](float_val=1.25)
      auto const& expr13 = hstd::ext::unidata::eval_equal(expr11, expr12);
      condition5 = expr13;
    }
    if (condition5) {
      // get_field[float64](this[OperationChecks](), str_val="real")
      auto const& expr14 = expr0.real;
      // const_float[float64](float_val=2.0)
      auto const& expr15 = static_cast<double>(2.0);
      // get_field[float64](this[OperationChecks](), str_val="real") * const_float[float64](
      //     float_val=2.0
      // )
      auto const& expr16 = static_cast<double>((expr14 * expr15));
      // const_float[float64](float_val=5.0)
      auto const& expr17 = static_cast<double>(5.0);
      // get_field[float64](this[OperationChecks](), str_val="real") * const_float[float64](
      //     float_val=2.0
      // ) == const_float[float64](float_val=5.0)
      auto const& expr18 = hstd::ext::unidata::eval_equal(expr16, expr17);
      condition5 = expr18;
    }
    if (condition5) {
      // get_field[float64](this[OperationChecks](), str_val="real")
      auto const& expr19 = expr0.real;
      // const_float[float64](float_val=0.5)
      auto const& expr20 = static_cast<double>(0.5);
      // get_field[float64](this[OperationChecks](), str_val="real") - const_float[float64](
      //     float_val=0.5
      // )
      auto const& expr21 = static_cast<double>((expr19 - expr20));
      // const_float[float64](float_val=2.0)
      auto const& expr22 = static_cast<double>(2.0);
      // get_field[float64](this[OperationChecks](), str_val="real") - const_float[float64](
      //     float_val=0.5
      // ) == const_float[float64](float_val=2.0)
      auto const& expr23 = hstd::ext::unidata::eval_equal(expr21, expr22);
      condition5 = expr23;
    }
    if (condition5) {
      // get_field[float64](this[OperationChecks](), str_val="real")
      auto const& expr24 = expr0.real;
      // const_float[float64](float_val=0.5)
      auto const& expr25 = static_cast<double>(0.5);
      // get_field[float64](this[OperationChecks](), str_val="real") + const_float[float64](
      //     float_val=0.5
      // )
      auto const& expr26 = static_cast<double>((expr24 + expr25));
      // const_float[float64](float_val=3.0)
      auto const& expr27 = static_cast<double>(3.0);
      // get_field[float64](this[OperationChecks](), str_val="real") + const_float[float64](
      //     float_val=0.5
      // ) == const_float[float64](float_val=3.0)
      auto const& expr28 = hstd::ext::unidata::eval_equal(expr26, expr27);
      condition5 = expr28;
    }
    condition1 = condition5;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.ConstFloat")
    auto const& expr29 = hstd::Str{"poc.ConstFloat"};
    return hstd::ext::unidata::VerifyResult::Error(expr29);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ConstBool(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="ConstBool",
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::ConstBool);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="ConstBool",
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[bool](this[OperationChecks](), str_val="flag")
    auto const& expr5 = expr0.flag;
    // const_bool[bool](bool_val=True)
    auto const& expr6 = true;
    // get_field[bool](this[OperationChecks](), str_val="flag") == const_bool[bool](
    //     bool_val=True
    // )
    auto const& expr7 = hstd::ext::unidata::eval_equal(expr5, expr6);
    condition1 = expr7;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.ConstBool")
    auto const& expr8 = hstd::Str{"poc.ConstBool"};
    return hstd::ext::unidata::VerifyResult::Error(expr8);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_And(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="And"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::And);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="And"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    bool condition5 = true;
    if (condition5) {
      // get_field[bool](this[OperationChecks](), str_val="flag")
      auto const& expr6 = expr0.flag;
      condition5 = expr6;
    }
    if (condition5) {
      // get_field[int64](this[OperationChecks](), str_val="number")
      auto const& expr7 = expr0.number;
      // const_int[int64](int_val=6)
      auto const& expr8 = static_cast<int64_t>(6);
      // get_field[int64](this[OperationChecks](), str_val="number") == const_int[int64](int_val=6)
      auto const& expr9 = hstd::ext::unidata::eval_equal(expr7, expr8);
      condition5 = expr9;
    }
    if (condition5) {
      // get_field[map[string, int64]](this[OperationChecks](), str_val="mapping")
      auto const& expr10 = expr0.mapping;
      // const_str[string](str_val="a")
      auto const& expr11 = hstd::Str{"a"};
      // map_get[int64](
      //     get_field[map[string, int64]](this[OperationChecks](), str_val="mapping"),
      //     const_str[string](str_val="a"),
      // )
      auto const& expr12 = expr10.at(expr11);
      // const_int[int64](int_val=1)
      auto const& expr13 = static_cast<int64_t>(1);
      // map_get[int64](
      //     get_field[map[string, int64]](this[OperationChecks](), str_val="mapping"),
      //     const_str[string](str_val="a"),
      // ) == const_int[int64](int_val=1)
      auto const& expr14 = hstd::ext::unidata::eval_equal(expr12, expr13);
      condition5 = expr14;
    }
    condition1 = condition5;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.And")
    auto const& expr15 = hstd::Str{"poc.And"};
    return hstd::ext::unidata::VerifyResult::Error(expr15);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Or(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Or"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Or);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Or"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    bool condition5 = false;
    if (!(condition5)) {
      // const_bool[bool](bool_val=False)
      auto const& expr6 = false;
      condition5 = expr6;
    }
    if (!(condition5)) {
      // get_field[int64](this[OperationChecks](), str_val="number")
      auto const& expr7 = expr0.number;
      // const_int[int64](int_val=6)
      auto const& expr8 = static_cast<int64_t>(6);
      // get_field[int64](this[OperationChecks](), str_val="number") == const_int[int64](int_val=6)
      auto const& expr9 = hstd::ext::unidata::eval_equal(expr7, expr8);
      condition5 = expr9;
    }
    if (!(condition5)) {
      // get_field[map[string, int64]](this[OperationChecks](), str_val="mapping")
      auto const& expr10 = expr0.mapping;
      // const_str[string](str_val="a")
      auto const& expr11 = hstd::Str{"a"};
      // map_get[int64](
      //     get_field[map[string, int64]](this[OperationChecks](), str_val="mapping"),
      //     const_str[string](str_val="a"),
      // )
      auto const& expr12 = expr10.at(expr11);
      // const_int[int64](int_val=99)
      auto const& expr13 = static_cast<int64_t>(99);
      // map_get[int64](
      //     get_field[map[string, int64]](this[OperationChecks](), str_val="mapping"),
      //     const_str[string](str_val="a"),
      // ) == const_int[int64](int_val=99)
      auto const& expr14 = hstd::ext::unidata::eval_equal(expr12, expr13);
      condition5 = expr14;
    }
    condition1 = condition5;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.Or")
    auto const& expr15 = hstd::Str{"poc.Or"};
    return hstd::ext::unidata::VerifyResult::Error(expr15);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Not(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Not"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Not);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Not"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[int64](this[OperationChecks](), str_val="number")
    auto const& expr5 = expr0.number;
    // const_int[int64](int_val=6)
    auto const& expr6 = static_cast<int64_t>(6);
    // get_field[int64](this[OperationChecks](), str_val="number") != const_int[int64](int_val=6)
    auto const& expr7 = !(hstd::ext::unidata::eval_equal(expr5, expr6));
    // not get_field[int64](this[OperationChecks](), str_val="number") != const_int[int64](
    //     int_val=6
    // )
    auto const& expr8 = !(expr7);
    condition1 = expr8;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.Not")
    auto const& expr9 = hstd::Str{"poc.Not"};
    return hstd::ext::unidata::VerifyResult::Error(expr9);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Cond(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Cond"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Cond);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Cond"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[int64](this[OperationChecks](), str_val="number")
    auto const& expr5 = expr0.number;
    // const_int[int64](int_val=6)
    auto const& expr6 = static_cast<int64_t>(6);
    // get_field[int64](this[OperationChecks](), str_val="number") == const_int[int64](int_val=6)
    auto const& expr7 = hstd::ext::unidata::eval_equal(expr5, expr6);
    std::optional<hstd::Str> result11 = std::nullopt;
    if (expr7) {
      // get_field[string](this[OperationChecks](), str_val="text")
      auto const& expr8 = expr0.text;
      result11.emplace(expr8);
    } else {
      // get_field[int64](this[OperationChecks](), str_val="number")
      auto const& expr9 = expr0.number;
      // str_format[string](
      //     get_field[int64](this[OperationChecks](), str_val="number"), str_val="other-%d"
      // )
      auto const& expr10 = hstd::ext::unidata::eval_str_format(hstd::ext::unidata::eval_str_pattern("other-%d"), expr9);
      result11.emplace(expr10);
    }
    // const_str[string](str_val="six")
    auto const& expr12 = hstd::Str{"six"};
    // cond[string](
    //     get_field[int64](this[OperationChecks](), str_val="number")
    //     == const_int[int64](int_val=6),
    //     get_field[string](this[OperationChecks](), str_val="text"),
    //     str_format[string](
    //         get_field[int64](this[OperationChecks](), str_val="number"), str_val="other-%d"
    //     ),
    // ) == const_str[string](str_val="six")
    auto const& expr13 = hstd::ext::unidata::eval_equal(result11.value(), expr12);
    condition1 = expr13;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.Cond")
    auto const& expr14 = hstd::Str{"poc.Cond"};
    return hstd::ext::unidata::VerifyResult::Error(expr14);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_CondLazy(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="CondLazy"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::CondLazy);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="CondLazy"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[bool](this[OperationChecks](), str_val="flag")
    auto const& expr5 = expr0.flag;
    std::optional<int64_t> result12 = std::nullopt;
    if (expr5) {
      // get_field[map[string, int64]](this[OperationChecks](), str_val="mapping")
      auto const& expr6 = expr0.mapping;
      // const_str[string](str_val="a")
      auto const& expr7 = hstd::Str{"a"};
      // map_get[int64](
      //     get_field[map[string, int64]](this[OperationChecks](), str_val="mapping"),
      //     const_str[string](str_val="a"),
      // )
      auto const& expr8 = expr6.at(expr7);
      result12.emplace(expr8);
    } else {
      // get_field[map[string, int64]](this[OperationChecks](), str_val="mapping")
      auto const& expr9 = expr0.mapping;
      // const_str[string](str_val="absent")
      auto const& expr10 = hstd::Str{"absent"};
      // map_get[int64](
      //     get_field[map[string, int64]](this[OperationChecks](), str_val="mapping"),
      //     const_str[string](str_val="absent"),
      // )
      auto const& expr11 = expr9.at(expr10);
      result12.emplace(expr11);
    }
    // const_int[int64](int_val=1)
    auto const& expr13 = static_cast<int64_t>(1);
    // cond[int64](
    //     get_field[bool](this[OperationChecks](), str_val="flag"),
    //     map_get[int64](
    //         get_field[map[string, int64]](this[OperationChecks](), str_val="mapping"),
    //         const_str[string](str_val="a"),
    //     ),
    //     map_get[int64](
    //         get_field[map[string, int64]](this[OperationChecks](), str_val="mapping"),
    //         const_str[string](str_val="absent"),
    //     ),
    // ) == const_int[int64](int_val=1)
    auto const& expr14 = hstd::ext::unidata::eval_equal(result12.value(), expr13);
    condition1 = expr14;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.CondLazy")
    auto const& expr15 = hstd::Str{"poc.CondLazy"};
    return hstd::ext::unidata::VerifyResult::Error(expr15);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_All(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="All"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::All);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="All"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[list[int64]](this[OperationChecks](), str_val="numbers")
    auto const& expr5 = expr0.numbers;
    auto callback9 = [&](auto const& item6) {
                     // const_int[int64](int_val=4)
                     auto const& expr7 = static_cast<int64_t>(4);
                     // var[int64](str_val="number") < const_int[int64](int_val=4)
                     auto const& expr8 = (item6 < expr7);
                     return expr8;
                     };
    // all[bool](
    //     ("number",),
    //     get_field[list[int64]](this[OperationChecks](), str_val="numbers"),
    //     var[int64](str_val="number") < const_int[int64](int_val=4),
    // )
    auto const& expr10 = hstd::ext::unidata::eval_all(expr5, callback9);
    condition1 = expr10;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.All")
    auto const& expr11 = hstd::Str{"poc.All"};
    return hstd::ext::unidata::VerifyResult::Error(expr11);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Exists(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Exists"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Exists);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Exists"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[list[int64]](this[OperationChecks](), str_val="numbers")
    auto const& expr5 = expr0.numbers;
    auto callback9 = [&](auto const& item6) {
                     // const_int[int64](int_val=3)
                     auto const& expr7 = static_cast<int64_t>(3);
                     // var[int64](str_val="number") == const_int[int64](int_val=3)
                     auto const& expr8 = hstd::ext::unidata::eval_equal(item6, expr7);
                     return expr8;
                     };
    // exists[bool](
    //     ("number",),
    //     get_field[list[int64]](this[OperationChecks](), str_val="numbers"),
    //     var[int64](str_val="number") == const_int[int64](int_val=3),
    // )
    auto const& expr10 = hstd::ext::unidata::eval_exists(expr5, callback9);
    condition1 = expr10;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.Exists")
    auto const& expr11 = hstd::Str{"poc.Exists"};
    return hstd::ext::unidata::VerifyResult::Error(expr11);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ExistsOne(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="ExistsOne",
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::ExistsOne);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="ExistsOne",
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[list[int64]](this[OperationChecks](), str_val="numbers")
    auto const& expr5 = expr0.numbers;
    auto callback9 = [&](auto const& item6) {
                     // const_int[int64](int_val=3)
                     auto const& expr7 = static_cast<int64_t>(3);
                     // var[int64](str_val="number") == const_int[int64](int_val=3)
                     auto const& expr8 = hstd::ext::unidata::eval_equal(item6, expr7);
                     return expr8;
                     };
    // exists_one[bool](
    //     ("number",),
    //     get_field[list[int64]](this[OperationChecks](), str_val="numbers"),
    //     var[int64](str_val="number") == const_int[int64](int_val=3),
    // )
    auto const& expr10 = hstd::ext::unidata::eval_exists_one(expr5, callback9);
    condition1 = expr10;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.ExistsOne")
    auto const& expr11 = hstd::Str{"poc.ExistsOne"};
    return hstd::ext::unidata::VerifyResult::Error(expr11);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Map(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Map"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Map);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Map"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[list[int64]](this[OperationChecks](), str_val="numbers")
    auto const& expr5 = expr0.numbers;
    auto callback9 = [&](auto const& item6) {
                     // const_int[int64](int_val=2)
                     auto const& expr7 = static_cast<int64_t>(2);
                     // var[int64](str_val="number") * const_int[int64](int_val=2)
                     auto const& expr8 = static_cast<int64_t>((item6 * expr7));
                     return expr8;
                     };
    // map[list[int64]](
    //     ("number",),
    //     get_field[list[int64]](this[OperationChecks](), str_val="numbers"),
    //     var[int64](str_val="number") * const_int[int64](int_val=2),
    // )
    auto const& expr10 = hstd::ext::unidata::eval_map<int64_t>(expr5, callback9);
    // const_int[int64](int_val=2)
    auto const& expr11 = static_cast<int64_t>(2);
    // list_at[int64](
    //     map[list[int64]](
    //         ("number",),
    //         get_field[list[int64]](this[OperationChecks](), str_val="numbers"),
    //         var[int64](str_val="number") * const_int[int64](int_val=2),
    //     ),
    //     const_int[int64](int_val=2),
    // )
    auto const& expr12 = expr10.at(expr11);
    // const_int[int64](int_val=6)
    auto const& expr13 = static_cast<int64_t>(6);
    // list_at[int64](
    //     map[list[int64]](
    //         ("number",),
    //         get_field[list[int64]](this[OperationChecks](), str_val="numbers"),
    //         var[int64](str_val="number") * const_int[int64](int_val=2),
    //     ),
    //     const_int[int64](int_val=2),
    // ) == const_int[int64](int_val=6)
    auto const& expr14 = hstd::ext::unidata::eval_equal(expr12, expr13);
    condition1 = expr14;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.Map")
    auto const& expr15 = hstd::Str{"poc.Map"};
    return hstd::ext::unidata::VerifyResult::Error(expr15);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Filter(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Filter"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Filter);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Filter"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[list[int64]](this[OperationChecks](), str_val="numbers")
    auto const& expr5 = expr0.numbers;
    auto callback9 = [&](auto const& item6) {
                     // const_int[int64](int_val=1)
                     auto const& expr7 = static_cast<int64_t>(1);
                     // const_int[int64](int_val=1) < var[int64](str_val="number")
                     auto const& expr8 = (expr7 < item6);
                     return expr8;
                     };
    // filter[list[int64]](
    //     ("number",),
    //     get_field[list[int64]](this[OperationChecks](), str_val="numbers"),
    //     const_int[int64](int_val=1) < var[int64](str_val="number"),
    // )
    auto const& expr10 = hstd::ext::unidata::eval_filter<int64_t>(expr5, callback9);
    // list_size[int64](
    //     filter[list[int64]](
    //         ("number",),
    //         get_field[list[int64]](this[OperationChecks](), str_val="numbers"),
    //         const_int[int64](int_val=1) < var[int64](str_val="number"),
    //     )
    // )
    auto const& expr11 = static_cast<int64_t>(expr10.size());
    // const_int[int64](int_val=2)
    auto const& expr12 = static_cast<int64_t>(2);
    // list_size[int64](
    //     filter[list[int64]](
    //         ("number",),
    //         get_field[list[int64]](this[OperationChecks](), str_val="numbers"),
    //         const_int[int64](int_val=1) < var[int64](str_val="number"),
    //     )
    // ) == const_int[int64](int_val=2)
    auto const& expr13 = hstd::ext::unidata::eval_equal(expr11, expr12);
    condition1 = expr13;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.Filter")
    auto const& expr14 = hstd::Str{"poc.Filter"};
    return hstd::ext::unidata::VerifyResult::Error(expr14);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_FilterMap(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="FilterMap",
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::FilterMap);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="FilterMap",
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[list[optional[int64]]](this[OperationChecks](), str_val="optionals")
    auto const& expr5 = expr0.optionals;
    auto callback7 = [&](auto const& item6) {
                     return item6;
                     };
    // filter_map[list[int64]](
    //     ("optional",),
    //     get_field[list[optional[int64]]](this[OperationChecks](), str_val="optionals"),
    //     var[optional[int64]](str_val="optional"),
    // )
    auto const& expr8 = hstd::ext::unidata::eval_filter_map<hstd::Vec<int64_t>>(expr5, callback7);
    bool condition9 = true;
    if (condition9) {
      // list_size[int64](var[list[int64]](str_val="present"))
      auto const& expr10 = static_cast<int64_t>(expr8.size());
      // const_int[int64](int_val=2)
      auto const& expr11 = static_cast<int64_t>(2);
      // list_size[int64](var[list[int64]](str_val="present")) == const_int[int64](int_val=2)
      auto const& expr12 = hstd::ext::unidata::eval_equal(expr10, expr11);
      condition9 = expr12;
    }
    if (condition9) {
      // const_int[int64](int_val=0)
      auto const& expr13 = static_cast<int64_t>(0);
      // list_at[int64](var[list[int64]](str_val="present"), const_int[int64](int_val=0))
      auto const& expr14 = expr8.at(expr13);
      // const_int[int64](int_val=1)
      auto const& expr15 = static_cast<int64_t>(1);
      // list_at[int64](
      //     var[list[int64]](str_val="present"), const_int[int64](int_val=0)
      // ) == const_int[int64](int_val=1)
      auto const& expr16 = hstd::ext::unidata::eval_equal(expr14, expr15);
      condition9 = expr16;
    }
    if (condition9) {
      // const_int[int64](int_val=1)
      auto const& expr17 = static_cast<int64_t>(1);
      // list_at[int64](var[list[int64]](str_val="present"), const_int[int64](int_val=1))
      auto const& expr18 = expr8.at(expr17);
      // const_int[int64](int_val=3)
      auto const& expr19 = static_cast<int64_t>(3);
      // list_at[int64](
      //     var[list[int64]](str_val="present"), const_int[int64](int_val=1)
      // ) == const_int[int64](int_val=3)
      auto const& expr20 = hstd::ext::unidata::eval_equal(expr18, expr19);
      condition9 = expr20;
    }
    condition1 = condition9;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.FilterMap")
    auto const& expr21 = hstd::Str{"poc.FilterMap"};
    return hstd::ext::unidata::VerifyResult::Error(expr21);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_TakeWhile(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="TakeWhile",
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::TakeWhile);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="TakeWhile",
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[list[int64]](this[OperationChecks](), str_val="numbers")
    auto const& expr5 = expr0.numbers;
    auto callback9 = [&](auto const& item6) {
                     // const_int[int64](int_val=3)
                     auto const& expr7 = static_cast<int64_t>(3);
                     // var[int64](str_val="number") < const_int[int64](int_val=3)
                     auto const& expr8 = (item6 < expr7);
                     return expr8;
                     };
    // take_while[list[int64]](
    //     ("number",),
    //     get_field[list[int64]](this[OperationChecks](), str_val="numbers"),
    //     var[int64](str_val="number") < const_int[int64](int_val=3),
    // )
    auto const& expr10 = hstd::ext::unidata::eval_take_while<hstd::Vec<int64_t>>(expr5, callback9);
    // list_size[int64](
    //     take_while[list[int64]](
    //         ("number",),
    //         get_field[list[int64]](this[OperationChecks](), str_val="numbers"),
    //         var[int64](str_val="number") < const_int[int64](int_val=3),
    //     )
    // )
    auto const& expr11 = static_cast<int64_t>(expr10.size());
    // const_int[int64](int_val=2)
    auto const& expr12 = static_cast<int64_t>(2);
    // list_size[int64](
    //     take_while[list[int64]](
    //         ("number",),
    //         get_field[list[int64]](this[OperationChecks](), str_val="numbers"),
    //         var[int64](str_val="number") < const_int[int64](int_val=3),
    //     )
    // ) == const_int[int64](int_val=2)
    auto const& expr13 = hstd::ext::unidata::eval_equal(expr11, expr12);
    condition1 = expr13;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.TakeWhile")
    auto const& expr14 = hstd::Str{"poc.TakeWhile"};
    return hstd::ext::unidata::VerifyResult::Error(expr14);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_GroupBy(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="GroupBy"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::GroupBy);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="GroupBy"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[list[int64]](this[OperationChecks](), str_val="numbers")
    auto const& expr5 = expr0.numbers;
    auto callback9 = [&](auto const& item6) {
                     // const_int[int64](int_val=3)
                     auto const& expr7 = static_cast<int64_t>(3);
                     // var[int64](str_val="number") < const_int[int64](int_val=3)
                     auto const& expr8 = (item6 < expr7);
                     return expr8;
                     };
    // group_by[map[bool, list[int64]]](
    //     ("number",),
    //     get_field[list[int64]](this[OperationChecks](), str_val="numbers"),
    //     var[int64](str_val="number") < const_int[int64](int_val=3),
    // )
    auto const& expr10 = hstd::ext::unidata::eval_group_by<hstd::UnorderedMap<bool, hstd::Vec<int64_t>>>(expr5, callback9);
    bool condition11 = true;
    if (condition11) {
      // map_size[int64](var[map[bool, list[int64]]](str_val="groups"))
      auto const& expr12 = static_cast<int64_t>(expr10.size());
      // const_int[int64](int_val=2)
      auto const& expr13 = static_cast<int64_t>(2);
      // map_size[int64](var[map[bool, list[int64]]](str_val="groups")) == const_int[int64](
      //     int_val=2
      // )
      auto const& expr14 = hstd::ext::unidata::eval_equal(expr12, expr13);
      condition11 = expr14;
    }
    if (condition11) {
      // map_values[list[list[int64]]](var[map[bool, list[int64]]](str_val="groups"))
      auto const& expr15 = hstd::ext::unidata::eval_map_values<hstd::Vec<hstd::Vec<int64_t>>>(expr10);
      // const_int[int64](int_val=0)
      auto const& expr16 = static_cast<int64_t>(0);
      // list_at[list[int64]](
      //     map_values[list[list[int64]]](var[map[bool, list[int64]]](str_val="groups")),
      //     const_int[int64](int_val=0),
      // )
      auto const& expr17 = expr15.at(expr16);
      // const_int[int64](int_val=0)
      auto const& expr18 = static_cast<int64_t>(0);
      // list_at[int64](
      //     list_at[list[int64]](
      //         map_values[list[list[int64]]](var[map[bool, list[int64]]](str_val="groups")),
      //         const_int[int64](int_val=0),
      //     ),
      //     const_int[int64](int_val=0),
      // )
      auto const& expr19 = expr17.at(expr18);
      // get_field[list[int64]](this[OperationChecks](), str_val="numbers")
      auto const& expr20 = expr0.numbers;
      // const_int[int64](int_val=0)
      auto const& expr21 = static_cast<int64_t>(0);
      // list_at[int64](
      //     get_field[list[int64]](this[OperationChecks](), str_val="numbers"),
      //     const_int[int64](int_val=0),
      // )
      auto const& expr22 = expr20.at(expr21);
      // list_at[int64](
      //     list_at[list[int64]](
      //         map_values[list[list[int64]]](var[map[bool, list[int64]]](str_val="groups")),
      //         const_int[int64](int_val=0),
      //     ),
      //     const_int[int64](int_val=0),
      // ) == list_at[int64](
      //     get_field[list[int64]](this[OperationChecks](), str_val="numbers"),
      //     const_int[int64](int_val=0),
      // )
      auto const& expr23 = hstd::ext::unidata::eval_equal(expr19, expr22);
      condition11 = expr23;
    }
    condition1 = condition11;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.GroupBy")
    auto const& expr24 = hstd::Str{"poc.GroupBy"};
    return hstd::ext::unidata::VerifyResult::Error(expr24);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Fold(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Fold"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Fold);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Fold"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[list[int64]](this[OperationChecks](), str_val="numbers")
    auto const& expr5 = expr0.numbers;
    // const_int[int64](int_val=0)
    auto const& expr6 = static_cast<int64_t>(0);
    auto callback7 = [&](auto const& item8, auto const& item9) {
                     // var[int64](str_val="acc") + var[int64](str_val="number")
                     auto const& expr10 = static_cast<int64_t>((item8 + item9));
                     return expr10;
                     };
    // fold[int64](
    //     ("acc", "number"),
    //     get_field[list[int64]](this[OperationChecks](), str_val="numbers"),
    //     const_int[int64](int_val=0),
    //     var[int64](str_val="acc") + var[int64](str_val="number"),
    // )
    auto const& expr11 = hstd::ext::unidata::eval_fold<int64_t>(expr5, expr6, callback7);
    // const_int[int64](int_val=6)
    auto const& expr12 = static_cast<int64_t>(6);
    // fold[int64](
    //     ("acc", "number"),
    //     get_field[list[int64]](this[OperationChecks](), str_val="numbers"),
    //     const_int[int64](int_val=0),
    //     var[int64](str_val="acc") + var[int64](str_val="number"),
    // ) == const_int[int64](int_val=6)
    auto const& expr13 = hstd::ext::unidata::eval_equal(expr11, expr12);
    condition1 = expr13;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.Fold")
    auto const& expr14 = hstd::Str{"poc.Fold"};
    return hstd::ext::unidata::VerifyResult::Error(expr14);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Walk(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  hstd::ext::unidata::EvalRuntime expression_runtime = hstd::ext::unidata::EvalRuntime{ctx};
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Walk"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Walk);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Walk"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[Derived](this[OperationChecks](), str_val="derived")
    auto const& expr5 = expr0.derived;
    // walk[list[dyn[Derived]]](get_field[Derived](this[OperationChecks](), str_val="derived"))
    auto const& expr6 = hstd::ext::unidata::eval_walk(expression_runtime, expr5);
    auto callback11 = [&](auto const& item7) {
                      std::optional<int64_t> result8 = std::nullopt;
                      if (!(result8.has_value())) {
                        auto const* candidate9 = expression_runtime.try_as<hstd::unidata_dsl::test::Derived>(item7);
                        if (candidate9 != nullptr) {
                          // get_field[int64](var[Derived](str_val="derived"), str_val="id")
                          auto const& expr10 = (*candidate9).id;
                          result8.emplace(expr10);
                        }
                      }
                      return result8;
                      };
    // filter_map[list[int64]](
    //     ("walk_value",),
    //     walk[list[dyn[Derived]]](
    //         get_field[Derived](this[OperationChecks](), str_val="derived")
    //     ),
    //     type_cond[optional[int64]](
    //         var[dyn[Derived]](str_val="walk_value"),
    //         type_case[int64](
    //             ("derived",),
    //             get_field[int64](var[Derived](str_val="derived"), str_val="id"),
    //             type_val=Derived,
    //         ),
    //         bool_val=True,
    //     ),
    // )
    auto const& expr12 = hstd::ext::unidata::eval_filter_map<hstd::Vec<int64_t>>(expr6, callback11);
    bool condition13 = true;
    if (condition13) {
      // list_size[int64](var[list[int64]](str_val="ids"))
      auto const& expr14 = static_cast<int64_t>(expr12.size());
      // const_int[int64](int_val=1)
      auto const& expr15 = static_cast<int64_t>(1);
      // list_size[int64](var[list[int64]](str_val="ids")) == const_int[int64](int_val=1)
      auto const& expr16 = hstd::ext::unidata::eval_equal(expr14, expr15);
      condition13 = expr16;
    }
    if (condition13) {
      // const_int[int64](int_val=0)
      auto const& expr17 = static_cast<int64_t>(0);
      // list_at[int64](var[list[int64]](str_val="ids"), const_int[int64](int_val=0))
      auto const& expr18 = expr12.at(expr17);
      // const_int[int64](int_val=6)
      auto const& expr19 = static_cast<int64_t>(6);
      // list_at[int64](var[list[int64]](str_val="ids"), const_int[int64](int_val=0)) == const_int[
      //     int64
      // ](int_val=6)
      auto const& expr20 = hstd::ext::unidata::eval_equal(expr18, expr19);
      condition13 = expr20;
    }
    condition1 = condition13;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.Walk")
    auto const& expr21 = hstd::Str{"poc.Walk"};
    return hstd::ext::unidata::VerifyResult::Error(expr21);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Sum(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Sum"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Sum);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Sum"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[list[int64]](this[OperationChecks](), str_val="numbers")
    auto const& expr5 = expr0.numbers;
    // sum[int64](get_field[list[int64]](this[OperationChecks](), str_val="numbers"))
    auto const& expr6 = hstd::ext::unidata::eval_sum<int64_t>(expr5);
    // const_int[int64](int_val=6)
    auto const& expr7 = static_cast<int64_t>(6);
    // sum[int64](
    //     get_field[list[int64]](this[OperationChecks](), str_val="numbers")
    // ) == const_int[int64](int_val=6)
    auto const& expr8 = hstd::ext::unidata::eval_equal(expr6, expr7);
    condition1 = expr8;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.Sum")
    auto const& expr9 = hstd::Str{"poc.Sum"};
    return hstd::ext::unidata::VerifyResult::Error(expr9);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Min(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Min"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Min);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Min"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[list[int64]](this[OperationChecks](), str_val="numbers")
    auto const& expr5 = expr0.numbers;
    // min[int64](get_field[list[int64]](this[OperationChecks](), str_val="numbers"))
    auto const& expr6 = hstd::ext::unidata::eval_min<int64_t>(expr5);
    // const_int[int64](int_val=1)
    auto const& expr7 = static_cast<int64_t>(1);
    // min[int64](
    //     get_field[list[int64]](this[OperationChecks](), str_val="numbers")
    // ) == const_int[int64](int_val=1)
    auto const& expr8 = hstd::ext::unidata::eval_equal(expr6, expr7);
    condition1 = expr8;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.Min")
    auto const& expr9 = hstd::Str{"poc.Min"};
    return hstd::ext::unidata::VerifyResult::Error(expr9);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_Max(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Max"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Max);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="Max"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[list[int64]](this[OperationChecks](), str_val="numbers")
    auto const& expr5 = expr0.numbers;
    // max[int64](get_field[list[int64]](this[OperationChecks](), str_val="numbers"))
    auto const& expr6 = hstd::ext::unidata::eval_max<int64_t>(expr5);
    // const_int[int64](int_val=3)
    auto const& expr7 = static_cast<int64_t>(3);
    // max[int64](
    //     get_field[list[int64]](this[OperationChecks](), str_val="numbers")
    // ) == const_int[int64](int_val=3)
    auto const& expr8 = hstd::ext::unidata::eval_equal(expr6, expr7);
    condition1 = expr8;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.Max")
    auto const& expr9 = hstd::Str{"poc.Max"};
    return hstd::ext::unidata::VerifyResult::Error(expr9);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_StrSize(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="StrSize"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::StrSize);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="StrSize"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[string](this[OperationChecks](), str_val="text")
    auto const& expr5 = expr0.text;
    // str_size[int64](get_field[string](this[OperationChecks](), str_val="text"))
    auto const& expr6 = hstd::ext::unidata::eval_str_size(&expr5);
    // const_int[int64](int_val=3)
    auto const& expr7 = static_cast<int64_t>(3);
    // str_size[int64](get_field[string](this[OperationChecks](), str_val="text")) == const_int[
    //     int64
    // ](int_val=3)
    auto const& expr8 = hstd::ext::unidata::eval_equal(expr6, expr7);
    condition1 = expr8;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.StrSize")
    auto const& expr9 = hstd::Str{"poc.StrSize"};
    return hstd::ext::unidata::VerifyResult::Error(expr9);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_StrMatches(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="StrMatches",
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::StrMatches);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="StrMatches",
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[string](this[OperationChecks](), str_val="text")
    auto const& expr5 = expr0.text;
    // str_matches[bool](
    //     get_field[string](this[OperationChecks](), str_val="text"), str_val="^s[a-z]{2}$"
    // )
    auto const& expr6 = hstd::ext::unidata::eval_str_matches(expr5, "^s[a-z]{2}$");
    condition1 = expr6;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.StrMatches")
    auto const& expr7 = hstd::Str{"poc.StrMatches"};
    return hstd::ext::unidata::VerifyResult::Error(expr7);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_StrFormat(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="StrFormat",
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::StrFormat);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="StrFormat",
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[string](this[OperationChecks](), str_val="text")
    auto const& expr5 = expr0.text;
    // get_field[int64](this[OperationChecks](), str_val="number")
    auto const& expr6 = expr0.number;
    // str_format[string](
    //     get_field[string](this[OperationChecks](), str_val="text"),
    //     get_field[int64](this[OperationChecks](), str_val="number"),
    //     str_val="%s:%d",
    // )
    auto const& expr7 = hstd::ext::unidata::eval_str_format(hstd::ext::unidata::eval_str_pattern("%s:%d"), expr5, expr6);
    // const_str[string](str_val="six:6")
    auto const& expr8 = hstd::Str{"six:6"};
    // str_format[string](
    //     get_field[string](this[OperationChecks](), str_val="text"),
    //     get_field[int64](this[OperationChecks](), str_val="number"),
    //     str_val="%s:%d",
    // ) == const_str[string](str_val="six:6")
    auto const& expr9 = hstd::ext::unidata::eval_equal(expr7, expr8);
    condition1 = expr9;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.StrFormat")
    auto const& expr10 = hstd::Str{"poc.StrFormat"};
    return hstd::ext::unidata::VerifyResult::Error(expr10);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ListSize(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="ListSize"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::ListSize);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="ListSize"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[list[int64]](this[OperationChecks](), str_val="numbers")
    auto const& expr5 = expr0.numbers;
    // list_size[int64](get_field[list[int64]](this[OperationChecks](), str_val="numbers"))
    auto const& expr6 = static_cast<int64_t>(expr5.size());
    // const_int[int64](int_val=3)
    auto const& expr7 = static_cast<int64_t>(3);
    // list_size[int64](
    //     get_field[list[int64]](this[OperationChecks](), str_val="numbers")
    // ) == const_int[int64](int_val=3)
    auto const& expr8 = hstd::ext::unidata::eval_equal(expr6, expr7);
    condition1 = expr8;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.ListSize")
    auto const& expr9 = hstd::Str{"poc.ListSize"};
    return hstd::ext::unidata::VerifyResult::Error(expr9);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ListContains(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="ListContains",
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::ListContains);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="ListContains",
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[list[int64]](this[OperationChecks](), str_val="numbers")
    auto const& expr5 = expr0.numbers;
    // const_int[int64](int_val=3)
    auto const& expr6 = static_cast<int64_t>(3);
    // list_contains[bool](
    //     get_field[list[int64]](this[OperationChecks](), str_val="numbers"),
    //     const_int[int64](int_val=3),
    // )
    auto const& expr7 = hstd::ext::unidata::eval_list_contains(expr5, expr6);
    condition1 = expr7;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.ListContains")
    auto const& expr8 = hstd::Str{"poc.ListContains"};
    return hstd::ext::unidata::VerifyResult::Error(expr8);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ListAt(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="ListAt"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::ListAt);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="ListAt"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[list[int64]](this[OperationChecks](), str_val="numbers")
    auto const& expr5 = expr0.numbers;
    // const_int[int64](int_val=2)
    auto const& expr6 = static_cast<int64_t>(2);
    // list_at[int64](
    //     get_field[list[int64]](this[OperationChecks](), str_val="numbers"),
    //     const_int[int64](int_val=2),
    // )
    auto const& expr7 = expr5.at(expr6);
    // const_int[int64](int_val=3)
    auto const& expr8 = static_cast<int64_t>(3);
    // list_at[int64](
    //     get_field[list[int64]](this[OperationChecks](), str_val="numbers"),
    //     const_int[int64](int_val=2),
    // ) == const_int[int64](int_val=3)
    auto const& expr9 = hstd::ext::unidata::eval_equal(expr7, expr8);
    condition1 = expr9;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.ListAt")
    auto const& expr10 = hstd::Str{"poc.ListAt"};
    return hstd::ext::unidata::VerifyResult::Error(expr10);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ListSlice(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="ListSlice",
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::ListSlice);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="ListSlice",
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[list[int64]](this[OperationChecks](), str_val="numbers")
    auto const& expr5 = expr0.numbers;
    // const_int[int64](int_val=1)
    auto const& expr6 = static_cast<int64_t>(1);
    // const_int[int64](int_val=3)
    auto const& expr7 = static_cast<int64_t>(3);
    // list_slice[list[int64]](
    //     get_field[list[int64]](this[OperationChecks](), str_val="numbers"),
    //     const_int[int64](int_val=1),
    //     const_int[int64](int_val=3),
    // )
    auto const& expr8 = hstd::ext::unidata::eval_list_slice<hstd::Vec<int64_t>>(expr5, expr6, expr7);
    bool condition9 = true;
    if (condition9) {
      // list_size[int64](var[list[int64]](str_val="slice"))
      auto const& expr10 = static_cast<int64_t>(expr8.size());
      // const_int[int64](int_val=2)
      auto const& expr11 = static_cast<int64_t>(2);
      // list_size[int64](var[list[int64]](str_val="slice")) == const_int[int64](int_val=2)
      auto const& expr12 = hstd::ext::unidata::eval_equal(expr10, expr11);
      condition9 = expr12;
    }
    if (condition9) {
      // const_int[int64](int_val=0)
      auto const& expr13 = static_cast<int64_t>(0);
      // list_at[int64](var[list[int64]](str_val="slice"), const_int[int64](int_val=0))
      auto const& expr14 = expr8.at(expr13);
      // const_int[int64](int_val=2)
      auto const& expr15 = static_cast<int64_t>(2);
      // list_at[int64](
      //     var[list[int64]](str_val="slice"), const_int[int64](int_val=0)
      // ) == const_int[int64](int_val=2)
      auto const& expr16 = hstd::ext::unidata::eval_equal(expr14, expr15);
      condition9 = expr16;
    }
    if (condition9) {
      // const_int[int64](int_val=1)
      auto const& expr17 = static_cast<int64_t>(1);
      // list_at[int64](var[list[int64]](str_val="slice"), const_int[int64](int_val=1))
      auto const& expr18 = expr8.at(expr17);
      // const_int[int64](int_val=3)
      auto const& expr19 = static_cast<int64_t>(3);
      // list_at[int64](
      //     var[list[int64]](str_val="slice"), const_int[int64](int_val=1)
      // ) == const_int[int64](int_val=3)
      auto const& expr20 = hstd::ext::unidata::eval_equal(expr18, expr19);
      condition9 = expr20;
    }
    condition1 = condition9;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.ListSlice")
    auto const& expr21 = hstd::Str{"poc.ListSlice"};
    return hstd::ext::unidata::VerifyResult::Error(expr21);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ListSliceBounds(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="ListSliceBounds",
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::ListSliceBounds);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="ListSliceBounds",
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[list[int64]](this[OperationChecks](), str_val="numbers")
    auto const& expr5 = expr0.numbers;
    // const_int[int64](int_val=-2)
    auto const& expr6 = static_cast<int64_t>(-2);
    // const_int[int64](int_val=100)
    auto const& expr7 = static_cast<int64_t>(100);
    // list_slice[list[int64]](
    //     get_field[list[int64]](this[OperationChecks](), str_val="numbers"),
    //     const_int[int64](int_val=-2),
    //     const_int[int64](int_val=100),
    // )
    auto const& expr8 = hstd::ext::unidata::eval_list_slice<hstd::Vec<int64_t>>(expr5, expr6, expr7);
    bool condition9 = true;
    if (condition9) {
      // list_size[int64](var[list[int64]](str_val="slice"))
      auto const& expr10 = static_cast<int64_t>(expr8.size());
      // const_int[int64](int_val=2)
      auto const& expr11 = static_cast<int64_t>(2);
      // list_size[int64](var[list[int64]](str_val="slice")) == const_int[int64](int_val=2)
      auto const& expr12 = hstd::ext::unidata::eval_equal(expr10, expr11);
      condition9 = expr12;
    }
    if (condition9) {
      // const_int[int64](int_val=0)
      auto const& expr13 = static_cast<int64_t>(0);
      // list_at[int64](var[list[int64]](str_val="slice"), const_int[int64](int_val=0))
      auto const& expr14 = expr8.at(expr13);
      // const_int[int64](int_val=2)
      auto const& expr15 = static_cast<int64_t>(2);
      // list_at[int64](
      //     var[list[int64]](str_val="slice"), const_int[int64](int_val=0)
      // ) == const_int[int64](int_val=2)
      auto const& expr16 = hstd::ext::unidata::eval_equal(expr14, expr15);
      condition9 = expr16;
    }
    if (condition9) {
      // const_int[int64](int_val=1)
      auto const& expr17 = static_cast<int64_t>(1);
      // list_at[int64](var[list[int64]](str_val="slice"), const_int[int64](int_val=1))
      auto const& expr18 = expr8.at(expr17);
      // const_int[int64](int_val=3)
      auto const& expr19 = static_cast<int64_t>(3);
      // list_at[int64](
      //     var[list[int64]](str_val="slice"), const_int[int64](int_val=1)
      // ) == const_int[int64](int_val=3)
      auto const& expr20 = hstd::ext::unidata::eval_equal(expr18, expr19);
      condition9 = expr20;
    }
    condition1 = condition9;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.ListSliceBounds")
    auto const& expr21 = hstd::Str{"poc.ListSliceBounds"};
    return hstd::ext::unidata::VerifyResult::Error(expr21);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ListConcat(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="ListConcat",
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::ListConcat);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="ListConcat",
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[list[int64]](this[OperationChecks](), str_val="numbers")
    auto const& expr5 = expr0.numbers;
    // get_field[list[int64]](this[OperationChecks](), str_val="numbers")
    auto const& expr6 = expr0.numbers;
    // list_concat[list[int64]](
    //     get_field[list[int64]](this[OperationChecks](), str_val="numbers"),
    //     get_field[list[int64]](this[OperationChecks](), str_val="numbers"),
    // )
    auto const& expr7 = hstd::ext::unidata::eval_list_concat<hstd::Vec<int64_t>>(expr5, expr6);
    bool condition8 = true;
    if (condition8) {
      // list_size[int64](var[list[int64]](str_val="joined"))
      auto const& expr9 = static_cast<int64_t>(expr7.size());
      // const_int[int64](int_val=6)
      auto const& expr10 = static_cast<int64_t>(6);
      // list_size[int64](var[list[int64]](str_val="joined")) == const_int[int64](int_val=6)
      auto const& expr11 = hstd::ext::unidata::eval_equal(expr9, expr10);
      condition8 = expr11;
    }
    if (condition8) {
      // const_int[int64](int_val=3)
      auto const& expr12 = static_cast<int64_t>(3);
      // list_at[int64](var[list[int64]](str_val="joined"), const_int[int64](int_val=3))
      auto const& expr13 = expr7.at(expr12);
      // get_field[list[int64]](this[OperationChecks](), str_val="numbers")
      auto const& expr14 = expr0.numbers;
      // const_int[int64](int_val=0)
      auto const& expr15 = static_cast<int64_t>(0);
      // list_at[int64](
      //     get_field[list[int64]](this[OperationChecks](), str_val="numbers"),
      //     const_int[int64](int_val=0),
      // )
      auto const& expr16 = expr14.at(expr15);
      // list_at[int64](
      //     var[list[int64]](str_val="joined"), const_int[int64](int_val=3)
      // ) == list_at[int64](
      //     get_field[list[int64]](this[OperationChecks](), str_val="numbers"),
      //     const_int[int64](int_val=0),
      // )
      auto const& expr17 = hstd::ext::unidata::eval_equal(expr13, expr16);
      condition8 = expr17;
    }
    condition1 = condition8;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.ListConcat")
    auto const& expr18 = hstd::Str{"poc.ListConcat"};
    return hstd::ext::unidata::VerifyResult::Error(expr18);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_ListEmpty(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="ListEmpty",
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::ListEmpty);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="ListEmpty",
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // list_empty[list[int64]](type_val=list[int64])
    auto const& expr5 = hstd::Vec<int64_t>{};
    // list_size[int64](list_empty[list[int64]](type_val=list[int64]))
    auto const& expr6 = static_cast<int64_t>(expr5.size());
    // const_int[int64](int_val=0)
    auto const& expr7 = static_cast<int64_t>(0);
    // list_size[int64](list_empty[list[int64]](type_val=list[int64])) == const_int[int64](
    //     int_val=0
    // )
    auto const& expr8 = hstd::ext::unidata::eval_equal(expr6, expr7);
    condition1 = expr8;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.ListEmpty")
    auto const& expr9 = hstd::Str{"poc.ListEmpty"};
    return hstd::ext::unidata::VerifyResult::Error(expr9);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapSize(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="MapSize"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::MapSize);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="MapSize"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[map[string, int64]](this[OperationChecks](), str_val="mapping")
    auto const& expr5 = expr0.mapping;
    // map_size[int64](get_field[map[string, int64]](this[OperationChecks](), str_val="mapping"))
    auto const& expr6 = static_cast<int64_t>(expr5.size());
    // const_int[int64](int_val=2)
    auto const& expr7 = static_cast<int64_t>(2);
    // map_size[int64](
    //     get_field[map[string, int64]](this[OperationChecks](), str_val="mapping")
    // ) == const_int[int64](int_val=2)
    auto const& expr8 = hstd::ext::unidata::eval_equal(expr6, expr7);
    condition1 = expr8;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.MapSize")
    auto const& expr9 = hstd::Str{"poc.MapSize"};
    return hstd::ext::unidata::VerifyResult::Error(expr9);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapContains(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="MapContains",
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::MapContains);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="MapContains",
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[map[string, int64]](this[OperationChecks](), str_val="mapping")
    auto const& expr5 = expr0.mapping;
    // const_str[string](str_val="a")
    auto const& expr6 = hstd::Str{"a"};
    // map_contains[bool](
    //     get_field[map[string, int64]](this[OperationChecks](), str_val="mapping"),
    //     const_str[string](str_val="a"),
    // )
    auto const& expr7 = expr5.contains(expr6);
    condition1 = expr7;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.MapContains")
    auto const& expr8 = hstd::Str{"poc.MapContains"};
    return hstd::ext::unidata::VerifyResult::Error(expr8);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapGet(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="MapGet"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::MapGet);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="MapGet"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[map[string, int64]](this[OperationChecks](), str_val="mapping")
    auto const& expr5 = expr0.mapping;
    // const_str[string](str_val="a")
    auto const& expr6 = hstd::Str{"a"};
    // map_get[int64](
    //     get_field[map[string, int64]](this[OperationChecks](), str_val="mapping"),
    //     const_str[string](str_val="a"),
    // )
    auto const& expr7 = expr5.at(expr6);
    // const_int[int64](int_val=1)
    auto const& expr8 = static_cast<int64_t>(1);
    // map_get[int64](
    //     get_field[map[string, int64]](this[OperationChecks](), str_val="mapping"),
    //     const_str[string](str_val="a"),
    // ) == const_int[int64](int_val=1)
    auto const& expr9 = hstd::ext::unidata::eval_equal(expr7, expr8);
    condition1 = expr9;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.MapGet")
    auto const& expr10 = hstd::Str{"poc.MapGet"};
    return hstd::ext::unidata::VerifyResult::Error(expr10);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapInsert(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="MapInsert",
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::MapInsert);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="MapInsert",
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[map[string, int64]](this[OperationChecks](), str_val="mapping")
    auto const& expr5 = expr0.mapping;
    // const_str[string](str_val="c")
    auto const& expr6 = hstd::Str{"c"};
    // const_int[int64](int_val=3)
    auto const& expr7 = static_cast<int64_t>(3);
    // map_insert[map[string, int64]](
    //     get_field[map[string, int64]](this[OperationChecks](), str_val="mapping"),
    //     const_str[string](str_val="c"),
    //     const_int[int64](int_val=3),
    // )
    auto const& expr8 = hstd::ext::unidata::eval_map_insert<hstd::UnorderedMap<hstd::Str, int64_t>>(expr5, expr6, expr7);
    bool condition9 = true;
    if (condition9) {
      // map_size[int64](var[map[string, int64]](str_val="updated"))
      auto const& expr10 = static_cast<int64_t>(expr8.size());
      // const_int[int64](int_val=3)
      auto const& expr11 = static_cast<int64_t>(3);
      // map_size[int64](var[map[string, int64]](str_val="updated")) == const_int[int64](int_val=3)
      auto const& expr12 = hstd::ext::unidata::eval_equal(expr10, expr11);
      condition9 = expr12;
    }
    if (condition9) {
      // const_str[string](str_val="c")
      auto const& expr13 = hstd::Str{"c"};
      // map_get[int64](var[map[string, int64]](str_val="updated"), const_str[string](str_val="c"))
      auto const& expr14 = expr8.at(expr13);
      // const_int[int64](int_val=3)
      auto const& expr15 = static_cast<int64_t>(3);
      // map_get[int64](
      //     var[map[string, int64]](str_val="updated"), const_str[string](str_val="c")
      // ) == const_int[int64](int_val=3)
      auto const& expr16 = hstd::ext::unidata::eval_equal(expr14, expr15);
      condition9 = expr16;
    }
    if (condition9) {
      // get_field[map[string, int64]](this[OperationChecks](), str_val="mapping")
      auto const& expr17 = expr0.mapping;
      // const_str[string](str_val="c")
      auto const& expr18 = hstd::Str{"c"};
      // map_contains[bool](
      //     get_field[map[string, int64]](this[OperationChecks](), str_val="mapping"),
      //     const_str[string](str_val="c"),
      // )
      auto const& expr19 = expr17.contains(expr18);
      // not map_contains[bool](
      //     get_field[map[string, int64]](this[OperationChecks](), str_val="mapping"),
      //     const_str[string](str_val="c"),
      // )
      auto const& expr20 = !(expr19);
      condition9 = expr20;
    }
    condition1 = condition9;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.MapInsert")
    auto const& expr21 = hstd::Str{"poc.MapInsert"};
    return hstd::ext::unidata::VerifyResult::Error(expr21);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapReplace(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="MapReplace",
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::MapReplace);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="MapReplace",
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[map[string, int64]](this[OperationChecks](), str_val="mapping")
    auto const& expr5 = expr0.mapping;
    // const_str[string](str_val="a")
    auto const& expr6 = hstd::Str{"a"};
    // const_int[int64](int_val=9)
    auto const& expr7 = static_cast<int64_t>(9);
    // map_insert[map[string, int64]](
    //     get_field[map[string, int64]](this[OperationChecks](), str_val="mapping"),
    //     const_str[string](str_val="a"),
    //     const_int[int64](int_val=9),
    // )
    auto const& expr8 = hstd::ext::unidata::eval_map_insert<hstd::UnorderedMap<hstd::Str, int64_t>>(expr5, expr6, expr7);
    bool condition9 = true;
    if (condition9) {
      // map_size[int64](var[map[string, int64]](str_val="updated"))
      auto const& expr10 = static_cast<int64_t>(expr8.size());
      // get_field[map[string, int64]](this[OperationChecks](), str_val="mapping")
      auto const& expr11 = expr0.mapping;
      // map_size[int64](get_field[map[string, int64]](this[OperationChecks](), str_val="mapping"))
      auto const& expr12 = static_cast<int64_t>(expr11.size());
      // map_size[int64](var[map[string, int64]](str_val="updated")) == map_size[int64](
      //     get_field[map[string, int64]](this[OperationChecks](), str_val="mapping")
      // )
      auto const& expr13 = hstd::ext::unidata::eval_equal(expr10, expr12);
      condition9 = expr13;
    }
    if (condition9) {
      // const_str[string](str_val="a")
      auto const& expr14 = hstd::Str{"a"};
      // map_get[int64](var[map[string, int64]](str_val="updated"), const_str[string](str_val="a"))
      auto const& expr15 = expr8.at(expr14);
      // const_int[int64](int_val=9)
      auto const& expr16 = static_cast<int64_t>(9);
      // map_get[int64](
      //     var[map[string, int64]](str_val="updated"), const_str[string](str_val="a")
      // ) == const_int[int64](int_val=9)
      auto const& expr17 = hstd::ext::unidata::eval_equal(expr15, expr16);
      condition9 = expr17;
    }
    if (condition9) {
      // get_field[map[string, int64]](this[OperationChecks](), str_val="mapping")
      auto const& expr18 = expr0.mapping;
      // const_str[string](str_val="a")
      auto const& expr19 = hstd::Str{"a"};
      // map_get[int64](
      //     get_field[map[string, int64]](this[OperationChecks](), str_val="mapping"),
      //     const_str[string](str_val="a"),
      // )
      auto const& expr20 = expr18.at(expr19);
      // const_int[int64](int_val=1)
      auto const& expr21 = static_cast<int64_t>(1);
      // map_get[int64](
      //     get_field[map[string, int64]](this[OperationChecks](), str_val="mapping"),
      //     const_str[string](str_val="a"),
      // ) == const_int[int64](int_val=1)
      auto const& expr22 = hstd::ext::unidata::eval_equal(expr20, expr21);
      condition9 = expr22;
    }
    condition1 = condition9;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.MapReplace")
    auto const& expr23 = hstd::Str{"poc.MapReplace"};
    return hstd::ext::unidata::VerifyResult::Error(expr23);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapKeys(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="MapKeys"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::MapKeys);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="MapKeys"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[map[string, int64]](this[OperationChecks](), str_val="mapping")
    auto const& expr5 = expr0.mapping;
    // map_keys[list[string]](
    //     get_field[map[string, int64]](this[OperationChecks](), str_val="mapping")
    // )
    auto const& expr6 = hstd::ext::unidata::eval_map_keys<hstd::Vec<hstd::Str>>(expr5);
    bool condition7 = true;
    if (condition7) {
      // list_size[int64](var[list[string]](str_val="keys"))
      auto const& expr8 = static_cast<int64_t>(expr6.size());
      // const_int[int64](int_val=2)
      auto const& expr9 = static_cast<int64_t>(2);
      // list_size[int64](var[list[string]](str_val="keys")) == const_int[int64](int_val=2)
      auto const& expr10 = hstd::ext::unidata::eval_equal(expr8, expr9);
      condition7 = expr10;
    }
    if (condition7) {
      // const_str[string](str_val="a")
      auto const& expr11 = hstd::Str{"a"};
      // list_contains[bool](var[list[string]](str_val="keys"), const_str[string](str_val="a"))
      auto const& expr12 = hstd::ext::unidata::eval_list_contains(expr6, expr11);
      condition7 = expr12;
    }
    if (condition7) {
      // const_str[string](str_val="b")
      auto const& expr13 = hstd::Str{"b"};
      // list_contains[bool](var[list[string]](str_val="keys"), const_str[string](str_val="b"))
      auto const& expr14 = hstd::ext::unidata::eval_list_contains(expr6, expr13);
      condition7 = expr14;
    }
    condition1 = condition7;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.MapKeys")
    auto const& expr15 = hstd::Str{"poc.MapKeys"};
    return hstd::ext::unidata::VerifyResult::Error(expr15);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapValues(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="MapValues",
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::MapValues);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="MapValues",
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[map[string, int64]](this[OperationChecks](), str_val="mapping")
    auto const& expr5 = expr0.mapping;
    // map_values[list[int64]](
    //     get_field[map[string, int64]](this[OperationChecks](), str_val="mapping")
    // )
    auto const& expr6 = hstd::ext::unidata::eval_map_values<hstd::Vec<int64_t>>(expr5);
    bool condition7 = true;
    if (condition7) {
      // list_size[int64](var[list[int64]](str_val="values"))
      auto const& expr8 = static_cast<int64_t>(expr6.size());
      // const_int[int64](int_val=2)
      auto const& expr9 = static_cast<int64_t>(2);
      // list_size[int64](var[list[int64]](str_val="values")) == const_int[int64](int_val=2)
      auto const& expr10 = hstd::ext::unidata::eval_equal(expr8, expr9);
      condition7 = expr10;
    }
    if (condition7) {
      // const_int[int64](int_val=1)
      auto const& expr11 = static_cast<int64_t>(1);
      // list_contains[bool](var[list[int64]](str_val="values"), const_int[int64](int_val=1))
      auto const& expr12 = hstd::ext::unidata::eval_list_contains(expr6, expr11);
      condition7 = expr12;
    }
    if (condition7) {
      // const_int[int64](int_val=2)
      auto const& expr13 = static_cast<int64_t>(2);
      // list_contains[bool](var[list[int64]](str_val="values"), const_int[int64](int_val=2))
      auto const& expr14 = hstd::ext::unidata::eval_list_contains(expr6, expr13);
      condition7 = expr14;
    }
    condition1 = condition7;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.MapValues")
    auto const& expr15 = hstd::Str{"poc.MapValues"};
    return hstd::ext::unidata::VerifyResult::Error(expr15);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_MapEmpty(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="MapEmpty"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::MapEmpty);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="MapEmpty"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // map_empty[map[string, int64]](type_val=map[string, int64])
    auto const& expr5 = hstd::UnorderedMap<hstd::Str, int64_t>{};
    // map_size[int64](map_empty[map[string, int64]](type_val=map[string, int64]))
    auto const& expr6 = static_cast<int64_t>(expr5.size());
    // const_int[int64](int_val=0)
    auto const& expr7 = static_cast<int64_t>(0);
    // map_size[int64](map_empty[map[string, int64]](type_val=map[string, int64])) == const_int[
    //     int64
    // ](int_val=0)
    auto const& expr8 = hstd::ext::unidata::eval_equal(expr6, expr7);
    condition1 = expr8;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.MapEmpty")
    auto const& expr9 = hstd::Str{"poc.MapEmpty"};
    return hstd::ext::unidata::VerifyResult::Error(expr9);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_OptHasValue(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="OptHasValue",
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::OptHasValue);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="OptHasValue",
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[optional[int64]](this[OperationChecks](), str_val="optional")
    auto const& expr5 = expr0.optional;
    // opt_has_value[bool](
    //     get_field[optional[int64]](this[OperationChecks](), str_val="optional")
    // )
    auto const& expr6 = expr5.has_value();
    condition1 = expr6;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.OptHasValue")
    auto const& expr7 = hstd::Str{"poc.OptHasValue"};
    return hstd::ext::unidata::VerifyResult::Error(expr7);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_OptValue(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="OptValue"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::OptValue);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="OptValue"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    bool condition5 = true;
    if (condition5) {
      // get_field[optional[int64]](this[OperationChecks](), str_val="optional")
      auto const& expr6 = expr0.optional;
      // opt_has_value[bool](
      //     get_field[optional[int64]](this[OperationChecks](), str_val="optional")
      // )
      auto const& expr7 = expr6.has_value();
      condition5 = expr7;
    }
    if (condition5) {
      // get_field[optional[int64]](this[OperationChecks](), str_val="optional")
      auto const& expr8 = expr0.optional;
      // opt_value[int64](get_field[optional[int64]](this[OperationChecks](), str_val="optional"))
      auto const& expr9 = expr8.value();
      // const_int[int64](int_val=3)
      auto const& expr10 = static_cast<int64_t>(3);
      // opt_value[int64](
      //     get_field[optional[int64]](this[OperationChecks](), str_val="optional")
      // ) == const_int[int64](int_val=3)
      auto const& expr11 = hstd::ext::unidata::eval_equal(expr9, expr10);
      condition5 = expr11;
    }
    condition1 = condition5;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.OptValue")
    auto const& expr12 = hstd::Str{"poc.OptValue"};
    return hstd::ext::unidata::VerifyResult::Error(expr12);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_CaseIs(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="CaseIs"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::CaseIs);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="CaseIs"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[Choice](this[OperationChecks](), str_val="choice")
    auto const& expr5 = expr0.choice;
    // get_field[variant[Choice.data]](
    //     get_field[Choice](this[OperationChecks](), str_val="choice"), str_val="data"
    // )
    auto const& expr6 = expr5.data;
    // case_is[bool](
    //     get_field[variant[Choice.data]](
    //         get_field[Choice](this[OperationChecks](), str_val="choice"), str_val="data"
    //     ),
    //     str_val="First",
    // )
    auto const& expr7 = std::holds_alternative<hstd::unidata_dsl::test::Choice::First>(expr6);
    condition1 = expr7;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.CaseIs")
    auto const& expr8 = hstd::Str{"poc.CaseIs"};
    return hstd::ext::unidata::VerifyResult::Error(expr8);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_CaseWhich(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="CaseWhich",
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::CaseWhich);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="CaseWhich",
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[Choice](this[OperationChecks](), str_val="choice")
    auto const& expr5 = expr0.choice;
    // get_field[variant[Choice.data]](
    //     get_field[Choice](this[OperationChecks](), str_val="choice"), str_val="data"
    // )
    auto const& expr6 = expr5.data;
    // case_which[Choice.Kind](
    //     get_field[variant[Choice.data]](
    //         get_field[Choice](this[OperationChecks](), str_val="choice"), str_val="data"
    //     )
    // )
    auto const& expr7 = static_cast<hstd::unidata_dsl::test::Choice::Kind>(expr6.index());
    // enum_is[bool](
    //     case_which[Choice.Kind](
    //         get_field[variant[Choice.data]](
    //             get_field[Choice](this[OperationChecks](), str_val="choice"), str_val="data"
    //         )
    //     ),
    //     str_val="First",
    // )
    auto const& expr8 = (expr7 == hstd::unidata_dsl::test::Choice::Kind::First);
    condition1 = expr8;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.CaseWhich")
    auto const& expr9 = hstd::Str{"poc.CaseWhich"};
    return hstd::ext::unidata::VerifyResult::Error(expr9);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_CaseField(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="CaseField",
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::CaseField);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="CaseField",
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[Choice](this[OperationChecks](), str_val="choice")
    auto const& expr5 = expr0.choice;
    // get_field[variant[Choice.data]](
    //     get_field[Choice](this[OperationChecks](), str_val="choice"), str_val="data"
    // )
    auto const& expr6 = expr5.data;
    // case_is[bool](
    //     get_field[variant[Choice.data]](
    //         get_field[Choice](this[OperationChecks](), str_val="choice"), str_val="data"
    //     ),
    //     str_val="First",
    // )
    auto const& expr7 = std::holds_alternative<hstd::unidata_dsl::test::Choice::First>(expr6);
    std::optional<int64_t> result12 = std::nullopt;
    if (expr7) {
      // get_field[Choice](this[OperationChecks](), str_val="choice")
      auto const& expr8 = expr0.choice;
      // get_field[variant[Choice.data]](
      //     get_field[Choice](this[OperationChecks](), str_val="choice"), str_val="data"
      // )
      auto const& expr9 = expr8.data;
      // get_field[int64](
      //     get_field[variant[Choice.data]](
      //         get_field[Choice](this[OperationChecks](), str_val="choice"), str_val="data"
      //     ),
      //     str_val="value",
      // )
      auto const& expr10 = hstd::ext::unidata::eval_get_field<int64_t>(expr9, "value");
      result12.emplace(expr10);
    } else {
      // const_int[int64](int_val=-1)
      auto const& expr11 = static_cast<int64_t>(-1);
      result12.emplace(expr11);
    }
    // const_int[int64](int_val=6)
    auto const& expr13 = static_cast<int64_t>(6);
    // cond[int64](
    //     case_is[bool](
    //         get_field[variant[Choice.data]](
    //             get_field[Choice](this[OperationChecks](), str_val="choice"), str_val="data"
    //         ),
    //         str_val="First",
    //     ),
    //     get_field[int64](
    //         get_field[variant[Choice.data]](
    //             get_field[Choice](this[OperationChecks](), str_val="choice"), str_val="data"
    //         ),
    //         str_val="value",
    //     ),
    //     const_int[int64](int_val=-1),
    // ) == const_int[int64](int_val=6)
    auto const& expr14 = hstd::ext::unidata::eval_equal(result12.value(), expr13);
    condition1 = expr14;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.CaseField")
    auto const& expr15 = hstd::Str{"poc.CaseField"};
    return hstd::ext::unidata::VerifyResult::Error(expr15);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_EnumIs(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="EnumIs"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::EnumIs);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="EnumIs"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[Status](this[OperationChecks](), str_val="status")
    auto const& expr5 = expr0.status;
    // enum_is[bool](
    //     get_field[Status](this[OperationChecks](), str_val="status"), str_val="Ready"
    // )
    auto const& expr6 = (expr5 == hstd::unidata_dsl::test::Status::Ready);
    condition1 = expr6;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.EnumIs")
    auto const& expr7 = hstd::Str{"poc.EnumIs"};
    return hstd::ext::unidata::VerifyResult::Error(expr7);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_NthGet(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="NthGet"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::NthGet);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="NthGet"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    bool condition5 = true;
    if (condition5) {
      // get_field[tuple[int64, string]](this[OperationChecks](), str_val="coords")
      auto const& expr6 = expr0.coords;
      // nth_get[int64](
      //     get_field[tuple[int64, string]](this[OperationChecks](), str_val="coords"), int_val=0
      // )
      auto const& expr7 = std::get<0>(expr6);
      // const_int[int64](int_val=6)
      auto const& expr8 = static_cast<int64_t>(6);
      // nth_get[int64](
      //     get_field[tuple[int64, string]](this[OperationChecks](), str_val="coords"), int_val=0
      // ) == const_int[int64](int_val=6)
      auto const& expr9 = hstd::ext::unidata::eval_equal(expr7, expr8);
      condition5 = expr9;
    }
    if (condition5) {
      // get_field[tuple[int64, string]](this[OperationChecks](), str_val="coords")
      auto const& expr10 = expr0.coords;
      // nth_get[string](
      //     get_field[tuple[int64, string]](this[OperationChecks](), str_val="coords"), int_val=1
      // )
      auto const& expr11 = std::get<1>(expr10);
      // const_str[string](str_val="six")
      auto const& expr12 = hstd::Str{"six"};
      // nth_get[string](
      //     get_field[tuple[int64, string]](this[OperationChecks](), str_val="coords"), int_val=1
      // ) == const_str[string](str_val="six")
      auto const& expr13 = hstd::ext::unidata::eval_equal(expr11, expr12);
      condition5 = expr13;
    }
    condition1 = condition5;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.NthGet")
    auto const& expr14 = hstd::Str{"poc.NthGet"};
    return hstd::ext::unidata::VerifyResult::Error(expr14);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_IsDerived(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  hstd::ext::unidata::EvalRuntime expression_runtime = hstd::ext::unidata::EvalRuntime{ctx};
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="IsDerived",
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::IsDerived);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="IsDerived",
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    bool condition5 = true;
    if (condition5) {
      // get_field[Derived](this[OperationChecks](), str_val="derived")
      auto const& expr6 = expr0.derived;
      // is_derived[bool](
      //     get_field[Derived](this[OperationChecks](), str_val="derived"), type_val=Base
      // )
      auto const& expr7 = (expression_runtime.try_as<hstd::unidata_dsl::test::Base>(expr6) != nullptr);
      condition5 = expr7;
    }
    if (condition5) {
      // get_field[Base](this[OperationChecks](), str_val="base")
      auto const& expr8 = expr0.base;
      // is_derived[bool](
      //     get_field[Base](this[OperationChecks](), str_val="base"), type_val=Derived
      // )
      auto const& expr9 = (expression_runtime.try_as<hstd::unidata_dsl::test::Derived>(expr8) != nullptr);
      // not is_derived[bool](
      //     get_field[Base](this[OperationChecks](), str_val="base"), type_val=Derived
      // )
      auto const& expr10 = !(expr9);
      condition5 = expr10;
    }
    condition1 = condition5;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.IsDerived")
    auto const& expr11 = hstd::Str{"poc.IsDerived"};
    return hstd::ext::unidata::VerifyResult::Error(expr11);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_TypeCond(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  hstd::ext::unidata::EvalRuntime expression_runtime = hstd::ext::unidata::EvalRuntime{ctx};
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="TypeCond"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::TypeCond);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="TypeCond"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[Derived](this[OperationChecks](), str_val="derived")
    auto const& expr5 = expr0.derived;
    // walk[list[dyn[Derived]]](get_field[Derived](this[OperationChecks](), str_val="derived"))
    auto const& expr6 = hstd::ext::unidata::eval_walk(expression_runtime, expr5);
    // const_int[int64](int_val=0)
    auto const& expr7 = static_cast<int64_t>(0);
    // list_at[dyn[Derived]](
    //     walk[list[dyn[Derived]]](
    //         get_field[Derived](this[OperationChecks](), str_val="derived")
    //     ),
    //     const_int[int64](int_val=0),
    // )
    auto const& expr8 = expr6.at(expr7);
    std::optional<int64_t> result9 = std::nullopt;
    if (!(result9.has_value())) {
      auto const* candidate10 = expression_runtime.try_as<hstd::unidata_dsl::test::Base>(expr8);
      if (candidate10 != nullptr) {
        // get_field[int64](var[Base](str_val="record"), str_val="id")
        auto const& expr11 = (*candidate10).id;
        result9.emplace(expr11);
      }
    }
    if (!(result9.has_value())) {
      auto const* candidate12 = expression_runtime.try_as<hstd::unidata_dsl::test::Derived>(expr8);
      if (candidate12 != nullptr) {
        // const_int[int64](int_val=-1)
        auto const& expr13 = static_cast<int64_t>(-1);
        result9.emplace(expr13);
      }
    }
    if (!(result9.has_value())) {
      throw std::runtime_error{"No type case matched at hstd_test_model.py:504; expected one of: Base, Derived"};
    }
    // const_int[int64](int_val=6)
    auto const& expr14 = static_cast<int64_t>(6);
    // type_cond[int64](
    //     list_at[dyn[Derived]](
    //         walk[list[dyn[Derived]]](
    //             get_field[Derived](this[OperationChecks](), str_val="derived")
    //         ),
    //         const_int[int64](int_val=0),
    //     ),
    //     type_case[int64](
    //         ("record",),
    //         get_field[int64](var[Base](str_val="record"), str_val="id"),
    //         type_val=Base,
    //     ),
    //     type_case[int64](("record",), const_int[int64](int_val=-1), type_val=Derived),
    //     bool_val=False,
    // ) == const_int[int64](int_val=6)
    auto const& expr15 = hstd::ext::unidata::eval_equal(result9.value(), expr14);
    condition1 = expr15;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.TypeCond")
    auto const& expr16 = hstd::Str{"poc.TypeCond"};
    return hstd::ext::unidata::VerifyResult::Error(expr16);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_TypeCondOptional(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  hstd::ext::unidata::EvalRuntime expression_runtime = hstd::ext::unidata::EvalRuntime{ctx};
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="TypeCondOptional",
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::TypeCondOptional);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="TypeCondOptional",
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    bool condition5 = true;
    if (condition5) {
      // get_field[Base](this[OperationChecks](), str_val="base")
      auto const& expr6 = expr0.base;
      // walk[list[dyn[Base]]](get_field[Base](this[OperationChecks](), str_val="base"))
      auto const& expr7 = hstd::ext::unidata::eval_walk(expression_runtime, expr6);
      // const_int[int64](int_val=0)
      auto const& expr8 = static_cast<int64_t>(0);
      // list_at[dyn[Base]](
      //     walk[list[dyn[Base]]](get_field[Base](this[OperationChecks](), str_val="base")),
      //     const_int[int64](int_val=0),
      // )
      auto const& expr9 = expr7.at(expr8);
      std::optional<int64_t> result10 = std::nullopt;
      if (!(result10.has_value())) {
        auto const* candidate11 = expression_runtime.try_as<hstd::unidata_dsl::test::Derived>(expr9);
        if (candidate11 != nullptr) {
          // get_field[int64](var[Derived](str_val="record"), str_val="id")
          auto const& expr12 = (*candidate11).id;
          result10.emplace(expr12);
        }
      }
      // opt_has_value[bool](
      //     type_cond[optional[int64]](
      //         list_at[dyn[Base]](
      //             walk[list[dyn[Base]]](
      //                 get_field[Base](this[OperationChecks](), str_val="base")
      //             ),
      //             const_int[int64](int_val=0),
      //         ),
      //         type_case[int64](
      //             ("record",),
      //             get_field[int64](var[Derived](str_val="record"), str_val="id"),
      //             type_val=Derived,
      //         ),
      //         bool_val=True,
      //     )
      // )
      auto const& expr13 = result10.has_value();
      // not opt_has_value[bool](
      //     type_cond[optional[int64]](
      //         list_at[dyn[Base]](
      //             walk[list[dyn[Base]]](
      //                 get_field[Base](this[OperationChecks](), str_val="base")
      //             ),
      //             const_int[int64](int_val=0),
      //         ),
      //         type_case[int64](
      //             ("record",),
      //             get_field[int64](var[Derived](str_val="record"), str_val="id"),
      //             type_val=Derived,
      //         ),
      //         bool_val=True,
      //     )
      // )
      auto const& expr14 = !(expr13);
      condition5 = expr14;
    }
    if (condition5) {
      // get_field[Derived](this[OperationChecks](), str_val="derived")
      auto const& expr15 = expr0.derived;
      // walk[list[dyn[Derived]]](get_field[Derived](this[OperationChecks](), str_val="derived"))
      auto const& expr16 = hstd::ext::unidata::eval_walk(expression_runtime, expr15);
      // const_int[int64](int_val=0)
      auto const& expr17 = static_cast<int64_t>(0);
      // list_at[dyn[Derived]](
      //     walk[list[dyn[Derived]]](
      //         get_field[Derived](this[OperationChecks](), str_val="derived")
      //     ),
      //     const_int[int64](int_val=0),
      // )
      auto const& expr18 = expr16.at(expr17);
      std::optional<int64_t> result19 = std::nullopt;
      if (!(result19.has_value())) {
        auto const* candidate20 = expression_runtime.try_as<hstd::unidata_dsl::test::Derived>(expr18);
        if (candidate20 != nullptr) {
          // get_field[int64](var[Derived](str_val="record"), str_val="id")
          auto const& expr21 = (*candidate20).id;
          result19.emplace(expr21);
        }
      }
      // opt_value[int64](
      //     type_cond[optional[int64]](
      //         list_at[dyn[Derived]](
      //             walk[list[dyn[Derived]]](
      //                 get_field[Derived](this[OperationChecks](), str_val="derived")
      //             ),
      //             const_int[int64](int_val=0),
      //         ),
      //         type_case[int64](
      //             ("record",),
      //             get_field[int64](var[Derived](str_val="record"), str_val="id"),
      //             type_val=Derived,
      //         ),
      //         bool_val=True,
      //     )
      // )
      auto const& expr22 = result19.value();
      // const_int[int64](int_val=6)
      auto const& expr23 = static_cast<int64_t>(6);
      // opt_value[int64](
      //     type_cond[optional[int64]](
      //         list_at[dyn[Derived]](
      //             walk[list[dyn[Derived]]](
      //                 get_field[Derived](this[OperationChecks](), str_val="derived")
      //             ),
      //             const_int[int64](int_val=0),
      //         ),
      //         type_case[int64](
      //             ("record",),
      //             get_field[int64](var[Derived](str_val="record"), str_val="id"),
      //             type_val=Derived,
      //         ),
      //         bool_val=True,
      //     )
      // ) == const_int[int64](int_val=6)
      auto const& expr24 = hstd::ext::unidata::eval_equal(expr22, expr23);
      condition5 = expr24;
    }
    condition1 = condition5;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.TypeCondOptional")
    auto const& expr25 = hstd::Str{"poc.TypeCondOptional"};
    return hstd::ext::unidata::VerifyResult::Error(expr25);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_TypeOf(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  hstd::ext::unidata::EvalRuntime expression_runtime = hstd::ext::unidata::EvalRuntime{ctx};
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="TypeOf"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::TypeOf);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="TypeOf"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    // get_field[Derived](this[OperationChecks](), str_val="derived")
    auto const& expr5 = expr0.derived;
    // walk[list[dyn[Derived]]](get_field[Derived](this[OperationChecks](), str_val="derived"))
    auto const& expr6 = hstd::ext::unidata::eval_walk(expression_runtime, expr5);
    // const_int[int64](int_val=0)
    auto const& expr7 = static_cast<int64_t>(0);
    // list_at[dyn[Derived]](
    //     walk[list[dyn[Derived]]](
    //         get_field[Derived](this[OperationChecks](), str_val="derived")
    //     ),
    //     const_int[int64](int_val=0),
    // )
    auto const& expr8 = expr6.at(expr7);
    std::optional<hstd::Str> result9 = std::nullopt;
    if (!(result9.has_value())) {
      auto const* candidate10 = expression_runtime.try_as<hstd::unidata_dsl::test::Base>(expr8);
      if (candidate10 != nullptr) {
        // type_of[string](var[Base](str_val="record"))
        auto const& expr11 = expression_runtime.type_of((*candidate10));
        result9.emplace(expr11);
      }
    }
    if (!(result9.has_value())) {
      throw std::runtime_error{"No type case matched at hstd_test_model.py:545; expected one of: Base"};
    }
    // const_str[string](str_val="Derived")
    auto const& expr12 = hstd::Str{"Derived"};
    // type_cond[string](
    //     list_at[dyn[Derived]](
    //         walk[list[dyn[Derived]]](
    //             get_field[Derived](this[OperationChecks](), str_val="derived")
    //         ),
    //         const_int[int64](int_val=0),
    //     ),
    //     type_case[string](
    //         ("record",), type_of[string](var[Base](str_val="record")), type_val=Base
    //     ),
    //     bool_val=False,
    // ) == const_str[string](str_val="Derived")
    auto const& expr13 = hstd::ext::unidata::eval_equal(result9.value(), expr12);
    condition1 = expr13;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.TypeOf")
    auto const& expr14 = hstd::Str{"poc.TypeOf"};
    return hstd::ext::unidata::VerifyResult::Error(expr14);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_PathOf(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  hstd::ext::unidata::EvalRuntime expression_runtime = hstd::ext::unidata::EvalRuntime{ctx};
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="PathOf"
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::PathOf);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"), str_val="PathOf"
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    bool condition5 = true;
    if (condition5) {
      // get_field[int64](this[OperationChecks](), str_val="number")
      auto const& expr6 = expr0.number;
      // path_of[path](get_field[int64](this[OperationChecks](), str_val="number"))
      auto const& expr7 = expression_runtime.path_of(expr6);
      // str_format[string](
      //     path_of[path](get_field[int64](this[OperationChecks](), str_val="number")),
      //     str_val="%s",
      // )
      auto const& expr8 = hstd::ext::unidata::eval_str_format(hstd::ext::unidata::eval_str_pattern("%s"), expr7);
      // const_str[string](str_val="/number")
      auto const& expr9 = hstd::Str{"/number"};
      // str_format[string](
      //     path_of[path](get_field[int64](this[OperationChecks](), str_val="number")),
      //     str_val="%s",
      // ) == const_str[string](str_val="/number")
      auto const& expr10 = hstd::ext::unidata::eval_equal(expr8, expr9);
      condition5 = expr10;
    }
    if (condition5) {
      // get_field[list[int64]](this[OperationChecks](), str_val="numbers")
      auto const& expr11 = expr0.numbers;
      auto callback15 = [&](auto const& item12) {
                        // path_of[path](var[int64](str_val="number"))
                        auto const& expr13 = expression_runtime.path_of(item12);
                        // str_format[string](path_of[path](var[int64](str_val="number")), str_val="%s")
                        auto const& expr14 = hstd::ext::unidata::eval_str_format(hstd::ext::unidata::eval_str_pattern("%s"), expr13);
                        return expr14;
                        };
      // map[list[string]](
      //     ("number",),
      //     get_field[list[int64]](this[OperationChecks](), str_val="numbers"),
      //     str_format[string](path_of[path](var[int64](str_val="number")), str_val="%s"),
      // )
      auto const& expr16 = hstd::ext::unidata::eval_map<hstd::Str>(expr11, callback15);
      // const_int[int64](int_val=0)
      auto const& expr17 = static_cast<int64_t>(0);
      // list_at[string](
      //     map[list[string]](
      //         ("number",),
      //         get_field[list[int64]](this[OperationChecks](), str_val="numbers"),
      //         str_format[string](path_of[path](var[int64](str_val="number")), str_val="%s"),
      //     ),
      //     const_int[int64](int_val=0),
      // )
      auto const& expr18 = expr16.at(expr17);
      // const_str[string](str_val="/numbers/0")
      auto const& expr19 = hstd::Str{"/numbers/0"};
      // list_at[string](
      //     map[list[string]](
      //         ("number",),
      //         get_field[list[int64]](this[OperationChecks](), str_val="numbers"),
      //         str_format[string](path_of[path](var[int64](str_val="number")), str_val="%s"),
      //     ),
      //     const_int[int64](int_val=0),
      // ) == const_str[string](str_val="/numbers/0")
      auto const& expr20 = hstd::ext::unidata::eval_equal(expr18, expr19);
      condition5 = expr20;
    }
    if (condition5) {
      // get_field[Derived](this[OperationChecks](), str_val="derived")
      auto const& expr21 = expr0.derived;
      // walk[list[dyn[Derived]]](get_field[Derived](this[OperationChecks](), str_val="derived"))
      auto const& expr22 = hstd::ext::unidata::eval_walk(expression_runtime, expr21);
      // const_int[int64](int_val=0)
      auto const& expr23 = static_cast<int64_t>(0);
      // list_at[dyn[Derived]](
      //     walk[list[dyn[Derived]]](
      //         get_field[Derived](this[OperationChecks](), str_val="derived")
      //     ),
      //     const_int[int64](int_val=0),
      // )
      auto const& expr24 = expr22.at(expr23);
      std::optional<hstd::Str> result25 = std::nullopt;
      if (!(result25.has_value())) {
        auto const* candidate26 = expression_runtime.try_as<hstd::unidata_dsl::test::Base>(expr24);
        if (candidate26 != nullptr) {
          // path_of[path](var[Base](str_val="record"))
          auto const& expr27 = expression_runtime.path_of((*candidate26));
          // str_format[string](path_of[path](var[Base](str_val="record")), str_val="%s")
          auto const& expr28 = hstd::ext::unidata::eval_str_format(hstd::ext::unidata::eval_str_pattern("%s"), expr27);
          result25.emplace(expr28);
        }
      }
      if (!(result25.has_value())) {
        throw std::runtime_error{"No type case matched at hstd_test_model.py:565; expected one of: Base"};
      }
      // const_str[string](str_val="/derived")
      auto const& expr29 = hstd::Str{"/derived"};
      // type_cond[string](
      //     list_at[dyn[Derived]](
      //         walk[list[dyn[Derived]]](
      //             get_field[Derived](this[OperationChecks](), str_val="derived")
      //         ),
      //         const_int[int64](int_val=0),
      //     ),
      //     type_case[string](
      //         ("record",),
      //         str_format[string](path_of[path](var[Base](str_val="record")), str_val="%s"),
      //         type_val=Base,
      //     ),
      //     bool_val=False,
      // ) == const_str[string](str_val="/derived")
      auto const& expr30 = hstd::ext::unidata::eval_equal(result25.value(), expr29);
      condition5 = expr30;
    }
    condition1 = condition5;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.PathOf")
    auto const& expr31 = hstd::Str{"poc.PathOf"};
    return hstd::ext::unidata::VerifyResult::Error(expr31);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc_EmptyCollections(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    // get_field[CheckKind](this[OperationChecks](), str_val="operation")
    auto const& expr2 = expr0.operation;
    // enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="EmptyCollections",
    // )
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::EmptyCollections);
    // not enum_is[bool](
    //     get_field[CheckKind](this[OperationChecks](), str_val="operation"),
    //     str_val="EmptyCollections",
    // )
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    bool condition5 = true;
    if (condition5) {
      // list_empty[list[int64]](type_val=list[int64])
      auto const& expr6 = hstd::Vec<int64_t>{};
      auto callback10 = [&](auto const& item7) {
                        // const_int[int64](int_val=0)
                        auto const& expr8 = static_cast<int64_t>(0);
                        // const_int[int64](int_val=0) < var[int64](str_val="number")
                        auto const& expr9 = (expr8 < item7);
                        return expr9;
                        };
      // all[bool](
      //     ("number",),
      //     list_empty[list[int64]](type_val=list[int64]),
      //     const_int[int64](int_val=0) < var[int64](str_val="number"),
      // )
      auto const& expr11 = hstd::ext::unidata::eval_all(expr6, callback10);
      condition5 = expr11;
    }
    if (condition5) {
      // list_empty[list[int64]](type_val=list[int64])
      auto const& expr12 = hstd::Vec<int64_t>{};
      auto callback16 = [&](auto const& item13) {
                        // const_int[int64](int_val=0)
                        auto const& expr14 = static_cast<int64_t>(0);
                        // const_int[int64](int_val=0) < var[int64](str_val="number")
                        auto const& expr15 = (expr14 < item13);
                        return expr15;
                        };
      // exists[bool](
      //     ("number",),
      //     list_empty[list[int64]](type_val=list[int64]),
      //     const_int[int64](int_val=0) < var[int64](str_val="number"),
      // )
      auto const& expr17 = hstd::ext::unidata::eval_exists(expr12, callback16);
      // not exists[bool](
      //     ("number",),
      //     list_empty[list[int64]](type_val=list[int64]),
      //     const_int[int64](int_val=0) < var[int64](str_val="number"),
      // )
      auto const& expr18 = !(expr17);
      condition5 = expr18;
    }
    if (condition5) {
      // list_empty[list[int64]](type_val=list[int64])
      auto const& expr19 = hstd::Vec<int64_t>{};
      auto callback23 = [&](auto const& item20) {
                        // const_int[int64](int_val=0)
                        auto const& expr21 = static_cast<int64_t>(0);
                        // const_int[int64](int_val=0) < var[int64](str_val="number")
                        auto const& expr22 = (expr21 < item20);
                        return expr22;
                        };
      // exists_one[bool](
      //     ("number",),
      //     list_empty[list[int64]](type_val=list[int64]),
      //     const_int[int64](int_val=0) < var[int64](str_val="number"),
      // )
      auto const& expr24 = hstd::ext::unidata::eval_exists_one(expr19, callback23);
      // not exists_one[bool](
      //     ("number",),
      //     list_empty[list[int64]](type_val=list[int64]),
      //     const_int[int64](int_val=0) < var[int64](str_val="number"),
      // )
      auto const& expr25 = !(expr24);
      condition5 = expr25;
    }
    if (condition5) {
      // list_empty[list[int64]](type_val=list[int64])
      auto const& expr26 = hstd::Vec<int64_t>{};
      // sum[int64](list_empty[list[int64]](type_val=list[int64]))
      auto const& expr27 = hstd::ext::unidata::eval_sum<int64_t>(expr26);
      // const_int[int64](int_val=0)
      auto const& expr28 = static_cast<int64_t>(0);
      // sum[int64](list_empty[list[int64]](type_val=list[int64])) == const_int[int64](int_val=0)
      auto const& expr29 = hstd::ext::unidata::eval_equal(expr27, expr28);
      condition5 = expr29;
    }
    if (condition5) {
      // list_empty[list[int64]](type_val=list[int64])
      auto const& expr30 = hstd::Vec<int64_t>{};
      auto callback35 = [&](auto const& item31) {
                        // get_field[map[string, int64]](this[OperationChecks](), str_val="mapping")
                        auto const& expr32 = expr0.mapping;
                        // const_str[string](str_val="absent")
                        auto const& expr33 = hstd::Str{"absent"};
                        // map_get[int64](
                        //     get_field[map[string, int64]](this[OperationChecks](), str_val="mapping"),
                        //     const_str[string](str_val="absent"),
                        // )
                        auto const& expr34 = expr32.at(expr33);
                        return expr34;
                        };
      // map[list[int64]](
      //     ("unused",),
      //     list_empty[list[int64]](type_val=list[int64]),
      //     map_get[int64](
      //         get_field[map[string, int64]](this[OperationChecks](), str_val="mapping"),
      //         const_str[string](str_val="absent"),
      //     ),
      // )
      auto const& expr36 = hstd::ext::unidata::eval_map<int64_t>(expr30, callback35);
      // list_size[int64](
      //     map[list[int64]](
      //         ("unused",),
      //         list_empty[list[int64]](type_val=list[int64]),
      //         map_get[int64](
      //             get_field[map[string, int64]](this[OperationChecks](), str_val="mapping"),
      //             const_str[string](str_val="absent"),
      //         ),
      //     )
      // )
      auto const& expr37 = static_cast<int64_t>(expr36.size());
      // const_int[int64](int_val=0)
      auto const& expr38 = static_cast<int64_t>(0);
      // list_size[int64](
      //     map[list[int64]](
      //         ("unused",),
      //         list_empty[list[int64]](type_val=list[int64]),
      //         map_get[int64](
      //             get_field[map[string, int64]](this[OperationChecks](), str_val="mapping"),
      //             const_str[string](str_val="absent"),
      //         ),
      //     )
      // ) == const_int[int64](int_val=0)
      auto const& expr39 = hstd::ext::unidata::eval_equal(expr37, expr38);
      condition5 = expr39;
    }
    if (condition5) {
      // list_empty[list[int64]](type_val=list[int64])
      auto const& expr40 = hstd::Vec<int64_t>{};
      auto callback46 = [&](auto const& item41) {
                        // get_field[optional[int64]](this[OperationChecks](), str_val="optional")
                        auto const& expr42 = expr0.optional;
                        // opt_value[int64](get_field[optional[int64]](this[OperationChecks](), str_val="optional"))
                        auto const& expr43 = expr42.value();
                        // const_int[int64](int_val=0)
                        auto const& expr44 = static_cast<int64_t>(0);
                        // opt_value[int64](
                        //     get_field[optional[int64]](this[OperationChecks](), str_val="optional")
                        // ) == const_int[int64](int_val=0)
                        auto const& expr45 = hstd::ext::unidata::eval_equal(expr43, expr44);
                        return expr45;
                        };
      // filter[list[int64]](
      //     ("unused",),
      //     list_empty[list[int64]](type_val=list[int64]),
      //     opt_value[int64](
      //         get_field[optional[int64]](this[OperationChecks](), str_val="optional")
      //     )
      //     == const_int[int64](int_val=0),
      // )
      auto const& expr47 = hstd::ext::unidata::eval_filter<int64_t>(expr40, callback46);
      // list_size[int64](
      //     filter[list[int64]](
      //         ("unused",),
      //         list_empty[list[int64]](type_val=list[int64]),
      //         opt_value[int64](
      //             get_field[optional[int64]](this[OperationChecks](), str_val="optional")
      //         )
      //         == const_int[int64](int_val=0),
      //     )
      // )
      auto const& expr48 = static_cast<int64_t>(expr47.size());
      // const_int[int64](int_val=0)
      auto const& expr49 = static_cast<int64_t>(0);
      // list_size[int64](
      //     filter[list[int64]](
      //         ("unused",),
      //         list_empty[list[int64]](type_val=list[int64]),
      //         opt_value[int64](
      //             get_field[optional[int64]](this[OperationChecks](), str_val="optional")
      //         )
      //         == const_int[int64](int_val=0),
      //     )
      // ) == const_int[int64](int_val=0)
      auto const& expr50 = hstd::ext::unidata::eval_equal(expr48, expr49);
      condition5 = expr50;
    }
    if (condition5) {
      // list_empty[list[int64]](type_val=list[int64])
      auto const& expr51 = hstd::Vec<int64_t>{};
      auto callback54 = [&](auto const& item52) {
                        // get_field[optional[int64]](this[OperationChecks](), str_val="optional")
                        auto const& expr53 = expr0.optional;
                        return expr53;
                        };
      // filter_map[list[int64]](
      //     ("unused",),
      //     list_empty[list[int64]](type_val=list[int64]),
      //     get_field[optional[int64]](this[OperationChecks](), str_val="optional"),
      // )
      auto const& expr55 = hstd::ext::unidata::eval_filter_map<hstd::Vec<int64_t>>(expr51, callback54);
      // list_size[int64](
      //     filter_map[list[int64]](
      //         ("unused",),
      //         list_empty[list[int64]](type_val=list[int64]),
      //         get_field[optional[int64]](this[OperationChecks](), str_val="optional"),
      //     )
      // )
      auto const& expr56 = static_cast<int64_t>(expr55.size());
      // const_int[int64](int_val=0)
      auto const& expr57 = static_cast<int64_t>(0);
      // list_size[int64](
      //     filter_map[list[int64]](
      //         ("unused",),
      //         list_empty[list[int64]](type_val=list[int64]),
      //         get_field[optional[int64]](this[OperationChecks](), str_val="optional"),
      //     )
      // ) == const_int[int64](int_val=0)
      auto const& expr58 = hstd::ext::unidata::eval_equal(expr56, expr57);
      condition5 = expr58;
    }
    if (condition5) {
      // list_empty[list[int64]](type_val=list[int64])
      auto const& expr59 = hstd::Vec<int64_t>{};
      auto callback65 = [&](auto const& item60) {
                        // get_field[optional[int64]](this[OperationChecks](), str_val="optional")
                        auto const& expr61 = expr0.optional;
                        // opt_value[int64](get_field[optional[int64]](this[OperationChecks](), str_val="optional"))
                        auto const& expr62 = expr61.value();
                        // const_int[int64](int_val=0)
                        auto const& expr63 = static_cast<int64_t>(0);
                        // opt_value[int64](
                        //     get_field[optional[int64]](this[OperationChecks](), str_val="optional")
                        // ) == const_int[int64](int_val=0)
                        auto const& expr64 = hstd::ext::unidata::eval_equal(expr62, expr63);
                        return expr64;
                        };
      // take_while[list[int64]](
      //     ("unused",),
      //     list_empty[list[int64]](type_val=list[int64]),
      //     opt_value[int64](
      //         get_field[optional[int64]](this[OperationChecks](), str_val="optional")
      //     )
      //     == const_int[int64](int_val=0),
      // )
      auto const& expr66 = hstd::ext::unidata::eval_take_while<hstd::Vec<int64_t>>(expr59, callback65);
      // list_size[int64](
      //     take_while[list[int64]](
      //         ("unused",),
      //         list_empty[list[int64]](type_val=list[int64]),
      //         opt_value[int64](
      //             get_field[optional[int64]](this[OperationChecks](), str_val="optional")
      //         )
      //         == const_int[int64](int_val=0),
      //     )
      // )
      auto const& expr67 = static_cast<int64_t>(expr66.size());
      // const_int[int64](int_val=0)
      auto const& expr68 = static_cast<int64_t>(0);
      // list_size[int64](
      //     take_while[list[int64]](
      //         ("unused",),
      //         list_empty[list[int64]](type_val=list[int64]),
      //         opt_value[int64](
      //             get_field[optional[int64]](this[OperationChecks](), str_val="optional")
      //         )
      //         == const_int[int64](int_val=0),
      //     )
      // ) == const_int[int64](int_val=0)
      auto const& expr69 = hstd::ext::unidata::eval_equal(expr67, expr68);
      condition5 = expr69;
    }
    if (condition5) {
      // list_empty[list[int64]](type_val=list[int64])
      auto const& expr70 = hstd::Vec<int64_t>{};
      auto callback75 = [&](auto const& item71) {
                        // get_field[map[string, int64]](this[OperationChecks](), str_val="mapping")
                        auto const& expr72 = expr0.mapping;
                        // const_str[string](str_val="absent")
                        auto const& expr73 = hstd::Str{"absent"};
                        // map_get[int64](
                        //     get_field[map[string, int64]](this[OperationChecks](), str_val="mapping"),
                        //     const_str[string](str_val="absent"),
                        // )
                        auto const& expr74 = expr72.at(expr73);
                        return expr74;
                        };
      // group_by[map[int64, list[int64]]](
      //     ("unused",),
      //     list_empty[list[int64]](type_val=list[int64]),
      //     map_get[int64](
      //         get_field[map[string, int64]](this[OperationChecks](), str_val="mapping"),
      //         const_str[string](str_val="absent"),
      //     ),
      // )
      auto const& expr76 = hstd::ext::unidata::eval_group_by<hstd::UnorderedMap<int64_t, hstd::Vec<int64_t>>>(expr70, callback75);
      // map_size[int64](
      //     group_by[map[int64, list[int64]]](
      //         ("unused",),
      //         list_empty[list[int64]](type_val=list[int64]),
      //         map_get[int64](
      //             get_field[map[string, int64]](this[OperationChecks](), str_val="mapping"),
      //             const_str[string](str_val="absent"),
      //         ),
      //     )
      // )
      auto const& expr77 = static_cast<int64_t>(expr76.size());
      // const_int[int64](int_val=0)
      auto const& expr78 = static_cast<int64_t>(0);
      // map_size[int64](
      //     group_by[map[int64, list[int64]]](
      //         ("unused",),
      //         list_empty[list[int64]](type_val=list[int64]),
      //         map_get[int64](
      //             get_field[map[string, int64]](this[OperationChecks](), str_val="mapping"),
      //             const_str[string](str_val="absent"),
      //         ),
      //     )
      // ) == const_int[int64](int_val=0)
      auto const& expr79 = hstd::ext::unidata::eval_equal(expr77, expr78);
      condition5 = expr79;
    }
    if (condition5) {
      // list_empty[list[int64]](type_val=list[int64])
      auto const& expr80 = hstd::Vec<int64_t>{};
      // const_int[int64](int_val=9)
      auto const& expr81 = static_cast<int64_t>(9);
      auto callback82 = [&](auto const& item83, auto const& item84) {
                        // get_field[map[string, int64]](this[OperationChecks](), str_val="mapping")
                        auto const& expr85 = expr0.mapping;
                        // const_str[string](str_val="absent")
                        auto const& expr86 = hstd::Str{"absent"};
                        // map_get[int64](
                        //     get_field[map[string, int64]](this[OperationChecks](), str_val="mapping"),
                        //     const_str[string](str_val="absent"),
                        // )
                        auto const& expr87 = expr85.at(expr86);
                        return expr87;
                        };
      // fold[int64](
      //     ("acc", "unused"),
      //     list_empty[list[int64]](type_val=list[int64]),
      //     const_int[int64](int_val=9),
      //     map_get[int64](
      //         get_field[map[string, int64]](this[OperationChecks](), str_val="mapping"),
      //         const_str[string](str_val="absent"),
      //     ),
      // )
      auto const& expr88 = hstd::ext::unidata::eval_fold<int64_t>(expr80, expr81, callback82);
      // const_int[int64](int_val=9)
      auto const& expr89 = static_cast<int64_t>(9);
      // fold[int64](
      //     ("acc", "unused"),
      //     list_empty[list[int64]](type_val=list[int64]),
      //     const_int[int64](int_val=9),
      //     map_get[int64](
      //         get_field[map[string, int64]](this[OperationChecks](), str_val="mapping"),
      //         const_str[string](str_val="absent"),
      //     ),
      // ) == const_int[int64](int_val=9)
      auto const& expr90 = hstd::ext::unidata::eval_equal(expr88, expr89);
      condition5 = expr90;
    }
    if (condition5) {
      // list_empty[list[int64]](type_val=list[int64])
      auto const& expr91 = hstd::Vec<int64_t>{};
      // list_empty[list[int64]](type_val=list[int64])
      auto const& expr92 = hstd::Vec<int64_t>{};
      // list_concat[list[int64]](
      //     list_empty[list[int64]](type_val=list[int64]),
      //     list_empty[list[int64]](type_val=list[int64]),
      // )
      auto const& expr93 = hstd::ext::unidata::eval_list_concat<hstd::Vec<int64_t>>(expr91, expr92);
      // list_size[int64](
      //     list_concat[list[int64]](
      //         list_empty[list[int64]](type_val=list[int64]),
      //         list_empty[list[int64]](type_val=list[int64]),
      //     )
      // )
      auto const& expr94 = static_cast<int64_t>(expr93.size());
      // const_int[int64](int_val=0)
      auto const& expr95 = static_cast<int64_t>(0);
      // list_size[int64](
      //     list_concat[list[int64]](
      //         list_empty[list[int64]](type_val=list[int64]),
      //         list_empty[list[int64]](type_val=list[int64]),
      //     )
      // ) == const_int[int64](int_val=0)
      auto const& expr96 = hstd::ext::unidata::eval_equal(expr94, expr95);
      condition5 = expr96;
    }
    if (condition5) {
      // const_bool[bool](bool_val=True)
      auto const& expr97 = true;
      std::optional<int64_t> result101 = std::nullopt;
      if (expr97) {
        // const_int[int64](int_val=42)
        auto const& expr98 = static_cast<int64_t>(42);
        result101.emplace(expr98);
      } else {
        // list_empty[list[int64]](type_val=list[int64])
        auto const& expr99 = hstd::Vec<int64_t>{};
        // min[int64](list_empty[list[int64]](type_val=list[int64]))
        auto const& expr100 = hstd::ext::unidata::eval_min<int64_t>(expr99);
        result101.emplace(expr100);
      }
      // const_int[int64](int_val=42)
      auto const& expr102 = static_cast<int64_t>(42);
      // cond[int64](
      //     const_bool[bool](bool_val=True),
      //     const_int[int64](int_val=42),
      //     min[int64](list_empty[list[int64]](type_val=list[int64])),
      // ) == const_int[int64](int_val=42)
      auto const& expr103 = hstd::ext::unidata::eval_equal(result101.value(), expr102);
      condition5 = expr103;
    }
    if (condition5) {
      // const_bool[bool](bool_val=True)
      auto const& expr104 = true;
      std::optional<int64_t> result108 = std::nullopt;
      if (expr104) {
        // const_int[int64](int_val=42)
        auto const& expr105 = static_cast<int64_t>(42);
        result108.emplace(expr105);
      } else {
        // list_empty[list[int64]](type_val=list[int64])
        auto const& expr106 = hstd::Vec<int64_t>{};
        // max[int64](list_empty[list[int64]](type_val=list[int64]))
        auto const& expr107 = hstd::ext::unidata::eval_max<int64_t>(expr106);
        result108.emplace(expr107);
      }
      // const_int[int64](int_val=42)
      auto const& expr109 = static_cast<int64_t>(42);
      // cond[int64](
      //     const_bool[bool](bool_val=True),
      //     const_int[int64](int_val=42),
      //     max[int64](list_empty[list[int64]](type_val=list[int64])),
      // ) == const_int[int64](int_val=42)
      auto const& expr110 = hstd::ext::unidata::eval_equal(result108.value(), expr109);
      condition5 = expr110;
    }
    condition1 = condition5;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // const_str[string](str_val="poc.EmptyCollections")
    auto const& expr111 = hstd::Str{"poc.EmptyCollections"};
    return hstd::ext::unidata::VerifyResult::Error(expr111);
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
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::FieldChecks const*>(value);
  auto const& expr0 = (*(&this_obj->text));
  // const_int[int64](int_val=0)
  auto const& expr1 = static_cast<int64_t>(0);
  // str_size[int64](this[string]())
  auto const& expr2 = hstd::ext::unidata::eval_str_size(&expr0);
  // const_int[int64](int_val=0) < str_size[int64](this[string]())
  auto const& expr3 = (expr1 < expr2);
  if (expr3) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // str_size[int64](this[string]())
    auto const& expr4 = hstd::ext::unidata::eval_str_size(&expr0);
    // str_format[string](str_size[int64](this[string]()), str_val="text length is %d")
    auto const& expr5 = hstd::ext::unidata::eval_str_format(hstd::ext::unidata::eval_str_pattern("text length is %d"), expr4);
    return hstd::ext::unidata::VerifyResult::Error(expr5);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::FieldChecks::__check_numbers_numbers_check(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::FieldChecks const*>(value);
  auto const& expr0 = (*(&this_obj->numbers));
  auto callback4 = [&](auto const& item1) {
                   // const_int[int64](int_val=0)
                   auto const& expr2 = static_cast<int64_t>(0);
                   // const_int[int64](int_val=0) < var[int64](str_val="number")
                   auto const& expr3 = (expr2 < item1);
                   return expr3;
                   };
  // all[bool](
  //     ("number",),
  //     this[list[int64]](),
  //     const_int[int64](int_val=0) < var[int64](str_val="number"),
  // )
  auto const& expr5 = hstd::ext::unidata::eval_all(expr0, callback4);
  if (expr5) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // str_format[string](this[list[int64]](), str_val="values=%s")
    auto const& expr6 = hstd::ext::unidata::eval_str_format(hstd::ext::unidata::eval_str_pattern("values=%s"), expr0);
    return hstd::ext::unidata::VerifyResult::Error(expr6);
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
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::MessageChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  // get_field[int64](this[MessageChecks](), str_val="number")
  auto const& expr1 = expr0.number;
  // const_int[int64](int_val=6)
  auto const& expr2 = static_cast<int64_t>(6);
  // get_field[int64](this[MessageChecks](), str_val="number") == const_int[int64](int_val=6)
  auto const& expr3 = hstd::ext::unidata::eval_equal(expr1, expr2);
  if (expr3) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // get_field[int64](this[MessageChecks](), str_val="number")
    auto const& expr4 = expr0.number;
    // get_field[float64](this[MessageChecks](), str_val="real")
    auto const& expr5 = expr0.real;
    // get_field[float64](this[MessageChecks](), str_val="real")
    auto const& expr6 = expr0.real;
    // get_field[int64](this[MessageChecks](), str_val="number")
    auto const& expr7 = expr0.number;
    // get_field[int64](this[MessageChecks](), str_val="number")
    auto const& expr8 = expr0.number;
    // get_field[bool](this[MessageChecks](), str_val="flag")
    auto const& expr9 = expr0.flag;
    // get_field[string](this[MessageChecks](), str_val="text")
    auto const& expr10 = expr0.text;
    // get_field[list[int64]](this[MessageChecks](), str_val="numbers")
    auto const& expr11 = expr0.numbers;
    // get_field[map[string, int64]](this[MessageChecks](), str_val="details")
    auto const& expr12 = expr0.details;
    // const_str[string](str_val="detail")
    auto const& expr13 = hstd::Str{"detail"};
    // map_get[int64](
    //     get_field[map[string, int64]](this[MessageChecks](), str_val="details"),
    //     const_str[string](str_val="detail"),
    // )
    auto const& expr14 = expr12.at(expr13);
    // str_format[string](
    //     get_field[int64](this[MessageChecks](), str_val="number"),
    //     get_field[float64](this[MessageChecks](), str_val="real"),
    //     get_field[float64](this[MessageChecks](), str_val="real"),
    //     get_field[int64](this[MessageChecks](), str_val="number"),
    //     get_field[int64](this[MessageChecks](), str_val="number"),
    //     get_field[bool](this[MessageChecks](), str_val="flag"),
    //     get_field[string](this[MessageChecks](), str_val="text"),
    //     get_field[list[int64]](this[MessageChecks](), str_val="numbers"),
    //     map_get[int64](
    //         get_field[map[string, int64]](this[MessageChecks](), str_val="details"),
    //         const_str[string](str_val="detail"),
    //     ),
    //     str_val="n=%d real=%f sci=%e hex=%x oct=%o flag=%b text=%s list=%s lookup=%d %%",
    // )
    auto const& expr15 = hstd::ext::unidata::eval_str_format(hstd::ext::unidata::eval_str_pattern("n=%d real=%f sci=%e hex=%x oct=%o flag=%b text=%s list=%s lookup=%d %%"), expr4, expr5, expr6, expr7, expr8, expr9, expr10, expr11, expr14);
    return hstd::ext::unidata::VerifyResult::Error(expr15);
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
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::Graph const*>(value);
  hstd::ext::unidata::EvalRuntime expression_runtime = hstd::ext::unidata::EvalRuntime{ctx};
  auto const& expr0 = (*(this_obj));
  // walk[list[dyn[Graph]]](this[Graph]())
  auto const& expr1 = hstd::ext::unidata::eval_walk(expression_runtime, expr0);
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
  // filter_map[list[Node]](
  //     ("node_any",),
  //     walk[list[dyn[Graph]]](this[Graph]()),
  //     type_cond[optional[Node]](
  //         var[dyn[Graph]](str_val="node_any"),
  //         type_case[Node](("node",), var[Node](str_val="node"), type_val=Node),
  //         bool_val=True,
  //     ),
  // )
  auto const& expr6 = hstd::ext::unidata::eval_filter_map<hstd::Vec<hstd::unidata_dsl::test::Node>>(expr1, callback5);
  auto callback9 = [&](auto const& item7) {
                   // get_field[string](var[Node](str_val="node"), str_val="id")
                   auto const& expr8 = item7.id;
                   return expr8;
                   };
  // group_by[map[string, list[Node]]](
  //     ("node",),
  //     filter_map[list[Node]](
  //         ("node_any",),
  //         walk[list[dyn[Graph]]](this[Graph]()),
  //         type_cond[optional[Node]](
  //             var[dyn[Graph]](str_val="node_any"),
  //             type_case[Node](("node",), var[Node](str_val="node"), type_val=Node),
  //             bool_val=True,
  //         ),
  //     ),
  //     get_field[string](var[Node](str_val="node"), str_val="id"),
  // )
  auto const& expr10 = hstd::ext::unidata::eval_group_by<hstd::UnorderedMap<hstd::Str, hstd::Vec<hstd::unidata_dsl::test::Node>>>(expr6, callback9);
  // map_values[list[list[Node]]](
  //     group_by[map[string, list[Node]]](
  //         ("node",),
  //         filter_map[list[Node]](
  //             ("node_any",),
  //             walk[list[dyn[Graph]]](this[Graph]()),
  //             type_cond[optional[Node]](
  //                 var[dyn[Graph]](str_val="node_any"),
  //                 type_case[Node](("node",), var[Node](str_val="node"), type_val=Node),
  //                 bool_val=True,
  //             ),
  //         ),
  //         get_field[string](var[Node](str_val="node"), str_val="id"),
  //     )
  // )
  auto const& expr11 = hstd::ext::unidata::eval_map_values<hstd::Vec<hstd::Vec<hstd::unidata_dsl::test::Node>>>(expr10);
  auto callback16 = [&](auto const& item12) {
                    // list_size[int64](var[list[Node]](str_val="group"))
                    auto const& expr13 = static_cast<int64_t>(item12.size());
                    // const_int[int64](int_val=1)
                    auto const& expr14 = static_cast<int64_t>(1);
                    // list_size[int64](var[list[Node]](str_val="group")) <= const_int[int64](int_val=1)
                    auto const& expr15 = (expr13 <= expr14);
                    return expr15;
                    };
  // all[bool](
  //     ("group",),
  //     map_values[list[list[Node]]](
  //         group_by[map[string, list[Node]]](
  //             ("node",),
  //             filter_map[list[Node]](
  //                 ("node_any",),
  //                 walk[list[dyn[Graph]]](this[Graph]()),
  //                 type_cond[optional[Node]](
  //                     var[dyn[Graph]](str_val="node_any"),
  //                     type_case[Node](("node",), var[Node](str_val="node"), type_val=Node),
  //                     bool_val=True,
  //                 ),
  //             ),
  //             get_field[string](var[Node](str_val="node"), str_val="id"),
  //         )
  //     ),
  //     list_size[int64](var[list[Node]](str_val="group")) <= const_int[int64](int_val=1),
  // )
  auto const& expr17 = hstd::ext::unidata::eval_all(expr11, callback16);
  if (expr17) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // walk[list[dyn[Graph]]](this[Graph]())
    auto const& expr18 = hstd::ext::unidata::eval_walk(expression_runtime, expr0);
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
    // filter_map[list[Node]](
    //     ("node_any",),
    //     walk[list[dyn[Graph]]](this[Graph]()),
    //     type_cond[optional[Node]](
    //         var[dyn[Graph]](str_val="node_any"),
    //         type_case[Node](("node",), var[Node](str_val="node"), type_val=Node),
    //         bool_val=True,
    //     ),
    // )
    auto const& expr23 = hstd::ext::unidata::eval_filter_map<hstd::Vec<hstd::unidata_dsl::test::Node>>(expr18, callback22);
    auto callback26 = [&](auto const& item24) {
                      // get_field[string](var[Node](str_val="node"), str_val="id")
                      auto const& expr25 = item24.id;
                      return expr25;
                      };
    // group_by[map[string, list[Node]]](
    //     ("node",),
    //     filter_map[list[Node]](
    //         ("node_any",),
    //         walk[list[dyn[Graph]]](this[Graph]()),
    //         type_cond[optional[Node]](
    //             var[dyn[Graph]](str_val="node_any"),
    //             type_case[Node](("node",), var[Node](str_val="node"), type_val=Node),
    //             bool_val=True,
    //         ),
    //     ),
    //     get_field[string](var[Node](str_val="node"), str_val="id"),
    // )
    auto const& expr27 = hstd::ext::unidata::eval_group_by<hstd::UnorderedMap<hstd::Str, hstd::Vec<hstd::unidata_dsl::test::Node>>>(expr23, callback26);
    // map_values[list[list[Node]]](
    //     group_by[map[string, list[Node]]](
    //         ("node",),
    //         filter_map[list[Node]](
    //             ("node_any",),
    //             walk[list[dyn[Graph]]](this[Graph]()),
    //             type_cond[optional[Node]](
    //                 var[dyn[Graph]](str_val="node_any"),
    //                 type_case[Node](("node",), var[Node](str_val="node"), type_val=Node),
    //                 bool_val=True,
    //             ),
    //         ),
    //         get_field[string](var[Node](str_val="node"), str_val="id"),
    //     )
    // )
    auto const& expr28 = hstd::ext::unidata::eval_map_values<hstd::Vec<hstd::Vec<hstd::unidata_dsl::test::Node>>>(expr27);
    auto callback33 = [&](auto const& item29) {
                      // const_int[int64](int_val=1)
                      auto const& expr30 = static_cast<int64_t>(1);
                      // list_size[int64](var[list[Node]](str_val="group"))
                      auto const& expr31 = static_cast<int64_t>(item29.size());
                      // const_int[int64](int_val=1) < list_size[int64](var[list[Node]](str_val="group"))
                      auto const& expr32 = (expr30 < expr31);
                      return expr32;
                      };
    // filter[list[list[Node]]](
    //     ("group",),
    //     map_values[list[list[Node]]](
    //         group_by[map[string, list[Node]]](
    //             ("node",),
    //             filter_map[list[Node]](
    //                 ("node_any",),
    //                 walk[list[dyn[Graph]]](this[Graph]()),
    //                 type_cond[optional[Node]](
    //                     var[dyn[Graph]](str_val="node_any"),
    //                     type_case[Node](("node",), var[Node](str_val="node"), type_val=Node),
    //                     bool_val=True,
    //                 ),
    //             ),
    //             get_field[string](var[Node](str_val="node"), str_val="id"),
    //         )
    //     ),
    //     const_int[int64](int_val=1) < list_size[int64](var[list[Node]](str_val="group")),
    // )
    auto const& expr34 = hstd::ext::unidata::eval_filter<hstd::Vec<hstd::unidata_dsl::test::Node>>(expr28, callback33);
    auto callback40 = [&](auto const& item35) {
                      auto callback38 = [&](auto const& item36) {
                                        // path_of[path](var[Node](str_val="node"))
                                        auto const& expr37 = expression_runtime.path_of(item36);
                                        return expr37;
                                        };
                      // map[list[path]](
                      //     ("node",), var[list[Node]](str_val="group"), path_of[path](var[Node](str_val="node"))
                      // )
                      auto const& expr39 = hstd::ext::unidata::eval_map<std::filesystem::path>(item35, callback38);
                      return expr39;
                      };
    // map[list[list[path]]](
    //     ("group",),
    //     filter[list[list[Node]]](
    //         ("group",),
    //         map_values[list[list[Node]]](
    //             group_by[map[string, list[Node]]](
    //                 ("node",),
    //                 filter_map[list[Node]](
    //                     ("node_any",),
    //                     walk[list[dyn[Graph]]](this[Graph]()),
    //                     type_cond[optional[Node]](
    //                         var[dyn[Graph]](str_val="node_any"),
    //                         type_case[Node](
    //                             ("node",), var[Node](str_val="node"), type_val=Node
    //                         ),
    //                         bool_val=True,
    //                     ),
    //                 ),
    //                 get_field[string](var[Node](str_val="node"), str_val="id"),
    //             )
    //         ),
    //         const_int[int64](int_val=1) < list_size[int64](var[list[Node]](str_val="group")),
    //     ),
    //     map[list[path]](
    //         ("node",),
    //         var[list[Node]](str_val="group"),
    //         path_of[path](var[Node](str_val="node")),
    //     ),
    // )
    auto const& expr41 = hstd::ext::unidata::eval_map<hstd::Vec<std::filesystem::path>>(expr34, callback40);
    // str_format[string](
    //     map[list[list[path]]](
    //         ("group",),
    //         filter[list[list[Node]]](
    //             ("group",),
    //             map_values[list[list[Node]]](
    //                 group_by[map[string, list[Node]]](
    //                     ("node",),
    //                     filter_map[list[Node]](
    //                         ("node_any",),
    //                         walk[list[dyn[Graph]]](this[Graph]()),
    //                         type_cond[optional[Node]](
    //                             var[dyn[Graph]](str_val="node_any"),
    //                             type_case[Node](
    //                                 ("node",), var[Node](str_val="node"), type_val=Node
    //                             ),
    //                             bool_val=True,
    //                         ),
    //                     ),
    //                     get_field[string](var[Node](str_val="node"), str_val="id"),
    //                 )
    //             ),
    //             const_int[int64](int_val=1)
    //             < list_size[int64](var[list[Node]](str_val="group")),
    //         ),
    //         map[list[path]](
    //             ("node",),
    //             var[list[Node]](str_val="group"),
    //             path_of[path](var[Node](str_val="node")),
    //         ),
    //     ),
    //     str_val="duplicate node ids at %s",
    // )
    auto const& expr42 = hstd::ext::unidata::eval_str_format(hstd::ext::unidata::eval_str_pattern("duplicate node ids at %s"), expr41);
    return hstd::ext::unidata::VerifyResult::Error(expr42);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::Graph::__check_record_graph_no_dangling_edges(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::Graph const*>(value);
  hstd::ext::unidata::EvalRuntime expression_runtime = hstd::ext::unidata::EvalRuntime{ctx};
  auto const& expr0 = (*(this_obj));
  // walk[list[dyn[Graph]]](this[Graph]())
  auto const& expr1 = hstd::ext::unidata::eval_walk(expression_runtime, expr0);
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
  // filter_map[list[Node]](
  //     ("node_any",),
  //     walk[list[dyn[Graph]]](this[Graph]()),
  //     type_cond[optional[Node]](
  //         var[dyn[Graph]](str_val="node_any"),
  //         type_case[Node](("node",), var[Node](str_val="node"), type_val=Node),
  //         bool_val=True,
  //     ),
  // )
  auto const& expr6 = hstd::ext::unidata::eval_filter_map<hstd::Vec<hstd::unidata_dsl::test::Node>>(expr1, callback5);
  auto callback9 = [&](auto const& item7) {
                   // get_field[string](var[Node](str_val="node"), str_val="id")
                   auto const& expr8 = item7.id;
                   return expr8;
                   };
  // map[list[string]](
  //     ("node",),
  //     filter_map[list[Node]](
  //         ("node_any",),
  //         walk[list[dyn[Graph]]](this[Graph]()),
  //         type_cond[optional[Node]](
  //             var[dyn[Graph]](str_val="node_any"),
  //             type_case[Node](("node",), var[Node](str_val="node"), type_val=Node),
  //             bool_val=True,
  //         ),
  //     ),
  //     get_field[string](var[Node](str_val="node"), str_val="id"),
  // )
  auto const& expr10 = hstd::ext::unidata::eval_map<hstd::Str>(expr6, callback9);
  // get_field[list[Edge]](this[Graph](), str_val="edges")
  auto const& expr11 = expr0.edges;
  auto callback18 = [&](auto const& item12) {
                    bool condition13 = true;
                    if (condition13) {
                      // get_field[string](var[Edge](str_val="edge"), str_val="source")
                      auto const& expr14 = item12.source;
                      // list_contains[bool](
                      //     var[list[string]](str_val="ids"),
                      //     get_field[string](var[Edge](str_val="edge"), str_val="source"),
                      // )
                      auto const& expr15 = hstd::ext::unidata::eval_list_contains(expr10, expr14);
                      condition13 = expr15;
                    }
                    if (condition13) {
                      // get_field[string](var[Edge](str_val="edge"), str_val="target")
                      auto const& expr16 = item12.target;
                      // list_contains[bool](
                      //     var[list[string]](str_val="ids"),
                      //     get_field[string](var[Edge](str_val="edge"), str_val="target"),
                      // )
                      auto const& expr17 = hstd::ext::unidata::eval_list_contains(expr10, expr16);
                      condition13 = expr17;
                    }
                    return condition13;
                    };
  // all[bool](
  //     ("edge",),
  //     get_field[list[Edge]](this[Graph](), str_val="edges"),
  //     list_contains[bool](
  //         var[list[string]](str_val="ids"),
  //         get_field[string](var[Edge](str_val="edge"), str_val="source"),
  //     )
  //     and list_contains[bool](
  //         var[list[string]](str_val="ids"),
  //         get_field[string](var[Edge](str_val="edge"), str_val="target"),
  //     ),
  // )
  auto const& expr19 = hstd::ext::unidata::eval_all(expr11, callback18);
  if (expr19) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    // walk[list[dyn[Graph]]](this[Graph]())
    auto const& expr20 = hstd::ext::unidata::eval_walk(expression_runtime, expr0);
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
    // filter_map[list[Node]](
    //     ("node_any",),
    //     walk[list[dyn[Graph]]](this[Graph]()),
    //     type_cond[optional[Node]](
    //         var[dyn[Graph]](str_val="node_any"),
    //         type_case[Node](("node",), var[Node](str_val="node"), type_val=Node),
    //         bool_val=True,
    //     ),
    // )
    auto const& expr25 = hstd::ext::unidata::eval_filter_map<hstd::Vec<hstd::unidata_dsl::test::Node>>(expr20, callback24);
    auto callback28 = [&](auto const& item26) {
                      // get_field[string](var[Node](str_val="node"), str_val="id")
                      auto const& expr27 = item26.id;
                      return expr27;
                      };
    // map[list[string]](
    //     ("node",),
    //     filter_map[list[Node]](
    //         ("node_any",),
    //         walk[list[dyn[Graph]]](this[Graph]()),
    //         type_cond[optional[Node]](
    //             var[dyn[Graph]](str_val="node_any"),
    //             type_case[Node](("node",), var[Node](str_val="node"), type_val=Node),
    //             bool_val=True,
    //         ),
    //     ),
    //     get_field[string](var[Node](str_val="node"), str_val="id"),
    // )
    auto const& expr29 = hstd::ext::unidata::eval_map<hstd::Str>(expr25, callback28);
    // get_field[list[Edge]](this[Graph](), str_val="edges")
    auto const& expr30 = expr0.edges;
    auto callback38 = [&](auto const& item31) {
                      bool condition32 = true;
                      if (condition32) {
                        // get_field[string](var[Edge](str_val="edge"), str_val="source")
                        auto const& expr33 = item31.source;
                        // list_contains[bool](
                        //     var[list[string]](str_val="ids"),
                        //     get_field[string](var[Edge](str_val="edge"), str_val="source"),
                        // )
                        auto const& expr34 = hstd::ext::unidata::eval_list_contains(expr29, expr33);
                        condition32 = expr34;
                      }
                      if (condition32) {
                        // get_field[string](var[Edge](str_val="edge"), str_val="target")
                        auto const& expr35 = item31.target;
                        // list_contains[bool](
                        //     var[list[string]](str_val="ids"),
                        //     get_field[string](var[Edge](str_val="edge"), str_val="target"),
                        // )
                        auto const& expr36 = hstd::ext::unidata::eval_list_contains(expr29, expr35);
                        condition32 = expr36;
                      }
                      // not (
                      //     list_contains[bool](
                      //         var[list[string]](str_val="ids"),
                      //         get_field[string](var[Edge](str_val="edge"), str_val="source"),
                      //     )
                      //     and list_contains[bool](
                      //         var[list[string]](str_val="ids"),
                      //         get_field[string](var[Edge](str_val="edge"), str_val="target"),
                      //     )
                      // )
                      auto const& expr37 = !(condition32);
                      return expr37;
                      };
    // filter[list[Edge]](
    //     ("edge",),
    //     get_field[list[Edge]](this[Graph](), str_val="edges"),
    //     not (
    //         list_contains[bool](
    //             var[list[string]](str_val="ids"),
    //             get_field[string](var[Edge](str_val="edge"), str_val="source"),
    //         )
    //         and list_contains[bool](
    //             var[list[string]](str_val="ids"),
    //             get_field[string](var[Edge](str_val="edge"), str_val="target"),
    //         )
    //     ),
    // )
    auto const& expr39 = hstd::ext::unidata::eval_filter<hstd::unidata_dsl::test::Edge>(expr30, callback38);
    auto callback42 = [&](auto const& item40) {
                      // path_of[path](var[Edge](str_val="edge"))
                      auto const& expr41 = expression_runtime.path_of(item40);
                      return expr41;
                      };
    // map[list[path]](
    //     ("edge",),
    //     filter[list[Edge]](
    //         ("edge",),
    //         get_field[list[Edge]](this[Graph](), str_val="edges"),
    //         not (
    //             list_contains[bool](
    //                 var[list[string]](str_val="ids"),
    //                 get_field[string](var[Edge](str_val="edge"), str_val="source"),
    //             )
    //             and list_contains[bool](
    //                 var[list[string]](str_val="ids"),
    //                 get_field[string](var[Edge](str_val="edge"), str_val="target"),
    //             )
    //         ),
    //     ),
    //     path_of[path](var[Edge](str_val="edge")),
    // )
    auto const& expr43 = hstd::ext::unidata::eval_map<std::filesystem::path>(expr39, callback42);
    // str_format[string](
    //     map[list[path]](
    //         ("edge",),
    //         filter[list[Edge]](
    //             ("edge",),
    //             get_field[list[Edge]](this[Graph](), str_val="edges"),
    //             not (
    //                 list_contains[bool](
    //                     var[list[string]](str_val="ids"),
    //                     get_field[string](var[Edge](str_val="edge"), str_val="source"),
    //                 )
    //                 and list_contains[bool](
    //                     var[list[string]](str_val="ids"),
    //                     get_field[string](var[Edge](str_val="edge"), str_val="target"),
    //                 )
    //             ),
    //         ),
    //         path_of[path](var[Edge](str_val="edge")),
    //     ),
    //     str_val="dangling edges at %s",
    // )
    auto const& expr44 = hstd::ext::unidata::eval_str_format(hstd::ext::unidata::eval_str_pattern("dangling edges at %s"), expr43);
    return hstd::ext::unidata::VerifyResult::Error(expr44);
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