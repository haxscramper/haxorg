/* clang-format off */
#include "tUnidataDSLModel.hpp"


hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::TrivialText::__check_text_textcheck(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::TrivialText const*>(value);
  auto const& expr0 = (*(&this_obj->text));
  auto const& expr1 = static_cast<int64_t>(0);
  auto const& expr2 = hstd::ext::unidata::eval_str_size(&expr0);
  auto const& expr3 = (expr1 < expr2);
  if (expr3) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr4 = hstd::Str{"text must not be empty"};
    return hstd::ext::unidata::VerifyResult::Error(expr4);
  }
}
hstd::ext::unidata::VerifyCheckCollection const* hstd::unidata_dsl::test::TrivialText::get_unidata_checks() {
  static hstd::ext::unidata::VerifyCheckCollection checks
   = {{
      {hstd::ext::unidata::VerifyKey{"TrivialText", "text"}, hstd::ext::unidata::VerifyCbList{hstd::ext::unidata::VerifyCb{&__check_text_textcheck}}}
      }};
  return &checks;
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::Base::__check_record_basepositiveid(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::Base const*>(value);
  auto const& expr0 = (*(this_obj));
  auto const& expr1 = static_cast<int64_t>(0);
  auto const& expr2 = expr0.id;
  auto const& expr3 = (expr1 < expr2);
  if (expr3) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr4 = hstd::Str{"base id must be positive"};
    return hstd::ext::unidata::VerifyResult::Error(expr4);
  }
}
hstd::ext::unidata::VerifyCheckCollection const* hstd::unidata_dsl::test::Base::get_unidata_checks() {
  static hstd::ext::unidata::VerifyCheckCollection checks
   = {{
      {hstd::ext::unidata::VerifyKey{"Base", std::nullopt}, hstd::ext::unidata::VerifyCbList{hstd::ext::unidata::VerifyCb{&__check_record_basepositiveid}}}
      }};
  return &checks;
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::Derived::__check_record_derivedpositiveweight(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::Derived const*>(value);
  auto const& expr0 = (*(this_obj));
  auto const& expr1 = static_cast<int64_t>(0);
  auto const& expr2 = expr0.weight;
  auto const& expr3 = (expr1 < expr2);
  if (expr3) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr4 = hstd::Str{"derived weight must be positive"};
    return hstd::ext::unidata::VerifyResult::Error(expr4);
  }
}
hstd::ext::unidata::VerifyCheckCollection const* hstd::unidata_dsl::test::Derived::get_unidata_checks() {
  static hstd::ext::unidata::VerifyCheckCollection checks
   = {{
      {hstd::ext::unidata::VerifyKey{"Derived", std::nullopt}, hstd::ext::unidata::VerifyCbList{hstd::ext::unidata::VerifyCb{&__check_record_derivedpositiveweight}}}
      }};
  return &checks;
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.eq(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Eq);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.number;
    auto const& expr6 = static_cast<int64_t>(6);
    auto const& expr7 = hstd::ext::unidata::eval_equal(expr5, expr6);
    condition1 = expr7;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr8 = hstd::Str{"poc.Eq"};
    return hstd::ext::unidata::VerifyResult::Error(expr8);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.ne(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Ne);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.number;
    auto const& expr6 = static_cast<int64_t>(8);
    auto const& expr7 = !(hstd::ext::unidata::eval_equal(expr5, expr6));
    condition1 = expr7;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr8 = hstd::Str{"poc.Ne"};
    return hstd::ext::unidata::VerifyResult::Error(expr8);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.lt(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Lt);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.number;
    auto const& expr6 = static_cast<int64_t>(7);
    auto const& expr7 = (expr5 < expr6);
    condition1 = expr7;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr8 = hstd::Str{"poc.Lt"};
    return hstd::ext::unidata::VerifyResult::Error(expr8);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.le(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Le);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.number;
    auto const& expr6 = static_cast<int64_t>(6);
    auto const& expr7 = (expr5 <= expr6);
    condition1 = expr7;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr8 = hstd::Str{"poc.Le"};
    return hstd::ext::unidata::VerifyResult::Error(expr8);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.add(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Add);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.number;
    auto const& expr6 = static_cast<int64_t>(3);
    auto const& expr7 = static_cast<int64_t>((expr5 + expr6));
    auto const& expr8 = static_cast<int64_t>(9);
    auto const& expr9 = hstd::ext::unidata::eval_equal(expr7, expr8);
    condition1 = expr9;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr10 = hstd::Str{"poc.Add"};
    return hstd::ext::unidata::VerifyResult::Error(expr10);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.sub(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Sub);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.number;
    auto const& expr6 = static_cast<int64_t>(3);
    auto const& expr7 = static_cast<int64_t>((expr5 - expr6));
    auto const& expr8 = static_cast<int64_t>(3);
    auto const& expr9 = hstd::ext::unidata::eval_equal(expr7, expr8);
    condition1 = expr9;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr10 = hstd::Str{"poc.Sub"};
    return hstd::ext::unidata::VerifyResult::Error(expr10);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.mul(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Mul);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.number;
    auto const& expr6 = static_cast<int64_t>(3);
    auto const& expr7 = static_cast<int64_t>((expr5 * expr6));
    auto const& expr8 = static_cast<int64_t>(18);
    auto const& expr9 = hstd::ext::unidata::eval_equal(expr7, expr8);
    condition1 = expr9;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr10 = hstd::Str{"poc.Mul"};
    return hstd::ext::unidata::VerifyResult::Error(expr10);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.div(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Div);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.number;
    auto const& expr6 = static_cast<int64_t>(3);
    auto const& expr7 = static_cast<int64_t>((static_cast<int64_t>(expr5) / static_cast<int64_t>(expr6)));
    auto const& expr8 = static_cast<int64_t>(2);
    auto const& expr9 = hstd::ext::unidata::eval_equal(expr7, expr8);
    condition1 = expr9;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr10 = hstd::Str{"poc.Div"};
    return hstd::ext::unidata::VerifyResult::Error(expr10);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.constfloat(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::ConstFloat);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    bool condition5 = true;
    if (condition5) {
      auto const& expr6 = expr0.real;
      auto const& expr7 = static_cast<double>(2.5);
      auto const& expr8 = hstd::ext::unidata::eval_equal(expr6, expr7);
      condition5 = expr8;
    }
    if (condition5) {
      auto const& expr9 = expr0.real;
      auto const& expr10 = static_cast<double>(2.0);
      auto const& expr11 = static_cast<double>((static_cast<double>(expr9) / static_cast<double>(expr10)));
      auto const& expr12 = static_cast<double>(1.25);
      auto const& expr13 = hstd::ext::unidata::eval_equal(expr11, expr12);
      condition5 = expr13;
    }
    if (condition5) {
      auto const& expr14 = expr0.real;
      auto const& expr15 = static_cast<double>(2.0);
      auto const& expr16 = static_cast<double>((expr14 * expr15));
      auto const& expr17 = static_cast<double>(5.0);
      auto const& expr18 = hstd::ext::unidata::eval_equal(expr16, expr17);
      condition5 = expr18;
    }
    if (condition5) {
      auto const& expr19 = expr0.real;
      auto const& expr20 = static_cast<double>(0.5);
      auto const& expr21 = static_cast<double>((expr19 - expr20));
      auto const& expr22 = static_cast<double>(2.0);
      auto const& expr23 = hstd::ext::unidata::eval_equal(expr21, expr22);
      condition5 = expr23;
    }
    if (condition5) {
      auto const& expr24 = expr0.real;
      auto const& expr25 = static_cast<double>(0.5);
      auto const& expr26 = static_cast<double>((expr24 + expr25));
      auto const& expr27 = static_cast<double>(3.0);
      auto const& expr28 = hstd::ext::unidata::eval_equal(expr26, expr27);
      condition5 = expr28;
    }
    condition1 = condition5;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr29 = hstd::Str{"poc.ConstFloat"};
    return hstd::ext::unidata::VerifyResult::Error(expr29);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.constbool(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::ConstBool);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.flag;
    auto const& expr6 = true;
    auto const& expr7 = hstd::ext::unidata::eval_equal(expr5, expr6);
    condition1 = expr7;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr8 = hstd::Str{"poc.ConstBool"};
    return hstd::ext::unidata::VerifyResult::Error(expr8);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.and(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::And);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    bool condition5 = true;
    if (condition5) {
      auto const& expr6 = expr0.flag;
      condition5 = expr6;
    }
    if (condition5) {
      auto const& expr7 = expr0.number;
      auto const& expr8 = static_cast<int64_t>(6);
      auto const& expr9 = hstd::ext::unidata::eval_equal(expr7, expr8);
      condition5 = expr9;
    }
    if (condition5) {
      auto const& expr10 = expr0.mapping;
      auto const& expr11 = hstd::Str{"a"};
      auto const& expr12 = expr10.at(expr11);
      auto const& expr13 = static_cast<int64_t>(1);
      auto const& expr14 = hstd::ext::unidata::eval_equal(expr12, expr13);
      condition5 = expr14;
    }
    condition1 = condition5;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr15 = hstd::Str{"poc.And"};
    return hstd::ext::unidata::VerifyResult::Error(expr15);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.or(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Or);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    bool condition5 = false;
    if (!(condition5)) {
      auto const& expr6 = false;
      condition5 = expr6;
    }
    if (!(condition5)) {
      auto const& expr7 = expr0.number;
      auto const& expr8 = static_cast<int64_t>(6);
      auto const& expr9 = hstd::ext::unidata::eval_equal(expr7, expr8);
      condition5 = expr9;
    }
    if (!(condition5)) {
      auto const& expr10 = expr0.mapping;
      auto const& expr11 = hstd::Str{"a"};
      auto const& expr12 = expr10.at(expr11);
      auto const& expr13 = static_cast<int64_t>(99);
      auto const& expr14 = hstd::ext::unidata::eval_equal(expr12, expr13);
      condition5 = expr14;
    }
    condition1 = condition5;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr15 = hstd::Str{"poc.Or"};
    return hstd::ext::unidata::VerifyResult::Error(expr15);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.not(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Not);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.number;
    auto const& expr6 = static_cast<int64_t>(6);
    auto const& expr7 = !(hstd::ext::unidata::eval_equal(expr5, expr6));
    auto const& expr8 = !(expr7);
    condition1 = expr8;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr9 = hstd::Str{"poc.Not"};
    return hstd::ext::unidata::VerifyResult::Error(expr9);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.cond(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Cond);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.number;
    auto const& expr6 = static_cast<int64_t>(6);
    auto const& expr7 = hstd::ext::unidata::eval_equal(expr5, expr6);
    std::optional<hstd::Str> result11 = std::nullopt;
    if (expr7) {
      auto const& expr8 = expr0.text;
      result11.emplace(expr8);
    } else {
      auto const& expr9 = expr0.number;
      auto const& expr10 = hstd::ext::unidata::eval_str_format("other-%d", expr9);
      result11.emplace(expr10);
    }
    auto const& expr12 = hstd::Str{"six"};
    auto const& expr13 = hstd::ext::unidata::eval_equal(result11.value(), expr12);
    condition1 = expr13;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr14 = hstd::Str{"poc.Cond"};
    return hstd::ext::unidata::VerifyResult::Error(expr14);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.condlazy(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::CondLazy);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.flag;
    std::optional<int64_t> result12 = std::nullopt;
    if (expr5) {
      auto const& expr6 = expr0.mapping;
      auto const& expr7 = hstd::Str{"a"};
      auto const& expr8 = expr6.at(expr7);
      result12.emplace(expr8);
    } else {
      auto const& expr9 = expr0.mapping;
      auto const& expr10 = hstd::Str{"absent"};
      auto const& expr11 = expr9.at(expr10);
      result12.emplace(expr11);
    }
    auto const& expr13 = static_cast<int64_t>(1);
    auto const& expr14 = hstd::ext::unidata::eval_equal(result12.value(), expr13);
    condition1 = expr14;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr15 = hstd::Str{"poc.CondLazy"};
    return hstd::ext::unidata::VerifyResult::Error(expr15);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.all(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::All);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.numbers;
    auto callback9 = [&](auto const& item6) {
                     auto const& expr7 = static_cast<int64_t>(4);
                     auto const& expr8 = (item6 < expr7);
                     return expr8;
                     };
    auto const& expr10 = hstd::ext::unidata::eval_all(expr5, callback9);
    condition1 = expr10;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr11 = hstd::Str{"poc.All"};
    return hstd::ext::unidata::VerifyResult::Error(expr11);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.exists(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Exists);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.numbers;
    auto callback9 = [&](auto const& item6) {
                     auto const& expr7 = static_cast<int64_t>(3);
                     auto const& expr8 = hstd::ext::unidata::eval_equal(item6, expr7);
                     return expr8;
                     };
    auto const& expr10 = hstd::ext::unidata::eval_exists(expr5, callback9);
    condition1 = expr10;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr11 = hstd::Str{"poc.Exists"};
    return hstd::ext::unidata::VerifyResult::Error(expr11);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.existsone(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::ExistsOne);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.numbers;
    auto callback9 = [&](auto const& item6) {
                     auto const& expr7 = static_cast<int64_t>(3);
                     auto const& expr8 = hstd::ext::unidata::eval_equal(item6, expr7);
                     return expr8;
                     };
    auto const& expr10 = hstd::ext::unidata::eval_exists_one(expr5, callback9);
    condition1 = expr10;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr11 = hstd::Str{"poc.ExistsOne"};
    return hstd::ext::unidata::VerifyResult::Error(expr11);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.map(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Map);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.numbers;
    auto callback9 = [&](auto const& item6) {
                     auto const& expr7 = static_cast<int64_t>(2);
                     auto const& expr8 = static_cast<int64_t>((item6 * expr7));
                     return expr8;
                     };
    auto const& expr10 = hstd::ext::unidata::eval_map<hstd::Vec<int64_t>>(expr5, callback9);
    auto const& expr11 = static_cast<int64_t>(2);
    auto const& expr12 = expr10.at(expr11);
    auto const& expr13 = static_cast<int64_t>(6);
    auto const& expr14 = hstd::ext::unidata::eval_equal(expr12, expr13);
    condition1 = expr14;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr15 = hstd::Str{"poc.Map"};
    return hstd::ext::unidata::VerifyResult::Error(expr15);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.filter(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Filter);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.numbers;
    auto callback9 = [&](auto const& item6) {
                     auto const& expr7 = static_cast<int64_t>(1);
                     auto const& expr8 = (expr7 < item6);
                     return expr8;
                     };
    auto const& expr10 = hstd::ext::unidata::eval_filter<hstd::Vec<int64_t>>(expr5, callback9);
    auto const& expr11 = static_cast<int64_t>(expr10.size());
    auto const& expr12 = static_cast<int64_t>(2);
    auto const& expr13 = hstd::ext::unidata::eval_equal(expr11, expr12);
    condition1 = expr13;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr14 = hstd::Str{"poc.Filter"};
    return hstd::ext::unidata::VerifyResult::Error(expr14);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.filtermap(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::FilterMap);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.optionals;
    auto callback7 = [&](auto const& item6) {
                     return item6;
                     };
    auto const& expr8 = hstd::ext::unidata::eval_filter_map<hstd::Vec<int64_t>>(expr5, callback7);
    bool condition9 = true;
    if (condition9) {
      auto const& expr10 = static_cast<int64_t>(expr8.size());
      auto const& expr11 = static_cast<int64_t>(2);
      auto const& expr12 = hstd::ext::unidata::eval_equal(expr10, expr11);
      condition9 = expr12;
    }
    if (condition9) {
      auto const& expr13 = static_cast<int64_t>(0);
      auto const& expr14 = expr8.at(expr13);
      auto const& expr15 = static_cast<int64_t>(1);
      auto const& expr16 = hstd::ext::unidata::eval_equal(expr14, expr15);
      condition9 = expr16;
    }
    if (condition9) {
      auto const& expr17 = static_cast<int64_t>(1);
      auto const& expr18 = expr8.at(expr17);
      auto const& expr19 = static_cast<int64_t>(3);
      auto const& expr20 = hstd::ext::unidata::eval_equal(expr18, expr19);
      condition9 = expr20;
    }
    condition1 = condition9;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr21 = hstd::Str{"poc.FilterMap"};
    return hstd::ext::unidata::VerifyResult::Error(expr21);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.takewhile(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::TakeWhile);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.numbers;
    auto callback9 = [&](auto const& item6) {
                     auto const& expr7 = static_cast<int64_t>(3);
                     auto const& expr8 = (item6 < expr7);
                     return expr8;
                     };
    auto const& expr10 = hstd::ext::unidata::eval_take_while<hstd::Vec<int64_t>>(expr5, callback9);
    auto const& expr11 = static_cast<int64_t>(expr10.size());
    auto const& expr12 = static_cast<int64_t>(2);
    auto const& expr13 = hstd::ext::unidata::eval_equal(expr11, expr12);
    condition1 = expr13;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr14 = hstd::Str{"poc.TakeWhile"};
    return hstd::ext::unidata::VerifyResult::Error(expr14);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.groupby(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::GroupBy);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.numbers;
    auto callback9 = [&](auto const& item6) {
                     auto const& expr7 = static_cast<int64_t>(3);
                     auto const& expr8 = (item6 < expr7);
                     return expr8;
                     };
    auto const& expr10 = hstd::ext::unidata::eval_group_by<hstd::UnorderedMap<bool, hstd::Vec<int64_t>>>(expr5, callback9);
    bool condition11 = true;
    if (condition11) {
      auto const& expr12 = static_cast<int64_t>(expr10.size());
      auto const& expr13 = static_cast<int64_t>(2);
      auto const& expr14 = hstd::ext::unidata::eval_equal(expr12, expr13);
      condition11 = expr14;
    }
    if (condition11) {
      auto const& expr15 = hstd::ext::unidata::eval_map_values<hstd::Vec<hstd::Vec<int64_t>>>(expr10);
      auto const& expr16 = static_cast<int64_t>(0);
      auto const& expr17 = expr15.at(expr16);
      auto const& expr18 = static_cast<int64_t>(0);
      auto const& expr19 = expr17.at(expr18);
      auto const& expr20 = expr0.numbers;
      auto const& expr21 = static_cast<int64_t>(0);
      auto const& expr22 = expr20.at(expr21);
      auto const& expr23 = hstd::ext::unidata::eval_equal(expr19, expr22);
      condition11 = expr23;
    }
    condition1 = condition11;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr24 = hstd::Str{"poc.GroupBy"};
    return hstd::ext::unidata::VerifyResult::Error(expr24);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.fold(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Fold);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.numbers;
    auto const& expr6 = static_cast<int64_t>(0);
    auto callback7 = [&](auto const& item8, auto const& item9) {
                     auto const& expr10 = static_cast<int64_t>((item8 + item9));
                     return expr10;
                     };
    auto const& expr11 = hstd::ext::unidata::eval_fold<int64_t>(expr5, expr6, callback7);
    auto const& expr12 = static_cast<int64_t>(6);
    auto const& expr13 = hstd::ext::unidata::eval_equal(expr11, expr12);
    condition1 = expr13;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr14 = hstd::Str{"poc.Fold"};
    return hstd::ext::unidata::VerifyResult::Error(expr14);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.walk(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  hstd::ext::unidata::EvalRuntime expression_runtime = hstd::ext::unidata::EvalRuntime{ctx};
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
  expression_runtime.register_type<hstd::unidata_dsl::test::Status>("Status");
  expression_runtime.register_type<hstd::unidata_dsl::test::CheckKind>("CheckKind");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::Kind>("Choice::Kind");
  expression_runtime.register_base<hstd::unidata_dsl::test::Derived, hstd::unidata_dsl::test::Base>();
  expression_runtime.index((*this_obj));
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Walk);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.derived;
    auto const& expr6 = hstd::ext::unidata::eval_walk<hstd::Vec<hstd::ext::unidata::EvalDynamic>>(expression_runtime, expr5);
    auto callback11 = [&](auto const& item7) {
                      std::optional<int64_t> result8 = std::nullopt;
                      if (!(result8.has_value())) {
                        auto const* candidate9 = expression_runtime.try_as<hstd::unidata_dsl::test::Derived>(item7);
                        if (candidate9 != nullptr) {
                          auto const& expr10 = (*candidate9).id;
                          result8.emplace(expr10);
                        }
                      }
                      return result8;
                      };
    auto const& expr12 = hstd::ext::unidata::eval_filter_map<hstd::Vec<int64_t>>(expr6, callback11);
    bool condition13 = true;
    if (condition13) {
      auto const& expr14 = static_cast<int64_t>(expr12.size());
      auto const& expr15 = static_cast<int64_t>(1);
      auto const& expr16 = hstd::ext::unidata::eval_equal(expr14, expr15);
      condition13 = expr16;
    }
    if (condition13) {
      auto const& expr17 = static_cast<int64_t>(0);
      auto const& expr18 = expr12.at(expr17);
      auto const& expr19 = static_cast<int64_t>(6);
      auto const& expr20 = hstd::ext::unidata::eval_equal(expr18, expr19);
      condition13 = expr20;
    }
    condition1 = condition13;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr21 = hstd::Str{"poc.Walk"};
    return hstd::ext::unidata::VerifyResult::Error(expr21);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.sum(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Sum);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.numbers;
    auto const& expr6 = hstd::ext::unidata::eval_sum<int64_t>(expr5);
    auto const& expr7 = static_cast<int64_t>(6);
    auto const& expr8 = hstd::ext::unidata::eval_equal(expr6, expr7);
    condition1 = expr8;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr9 = hstd::Str{"poc.Sum"};
    return hstd::ext::unidata::VerifyResult::Error(expr9);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.min(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Min);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.numbers;
    auto const& expr6 = hstd::ext::unidata::eval_min<int64_t>(expr5);
    auto const& expr7 = static_cast<int64_t>(1);
    auto const& expr8 = hstd::ext::unidata::eval_equal(expr6, expr7);
    condition1 = expr8;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr9 = hstd::Str{"poc.Min"};
    return hstd::ext::unidata::VerifyResult::Error(expr9);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.max(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::Max);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.numbers;
    auto const& expr6 = hstd::ext::unidata::eval_max<int64_t>(expr5);
    auto const& expr7 = static_cast<int64_t>(3);
    auto const& expr8 = hstd::ext::unidata::eval_equal(expr6, expr7);
    condition1 = expr8;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr9 = hstd::Str{"poc.Max"};
    return hstd::ext::unidata::VerifyResult::Error(expr9);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.strsize(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::StrSize);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.text;
    auto const& expr6 = hstd::ext::unidata::eval_str_size(&expr5);
    auto const& expr7 = static_cast<int64_t>(3);
    auto const& expr8 = hstd::ext::unidata::eval_equal(expr6, expr7);
    condition1 = expr8;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr9 = hstd::Str{"poc.StrSize"};
    return hstd::ext::unidata::VerifyResult::Error(expr9);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.strmatches(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::StrMatches);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.text;
    auto const& expr6 = hstd::ext::unidata::eval_str_matches(expr5, "^s[a-z]{2}$");
    condition1 = expr6;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr7 = hstd::Str{"poc.StrMatches"};
    return hstd::ext::unidata::VerifyResult::Error(expr7);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.strformat(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::StrFormat);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.text;
    auto const& expr6 = expr0.number;
    auto const& expr7 = hstd::ext::unidata::eval_str_format("%s:%d", expr5, expr6);
    auto const& expr8 = hstd::Str{"six:6"};
    auto const& expr9 = hstd::ext::unidata::eval_equal(expr7, expr8);
    condition1 = expr9;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr10 = hstd::Str{"poc.StrFormat"};
    return hstd::ext::unidata::VerifyResult::Error(expr10);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.listsize(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::ListSize);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.numbers;
    auto const& expr6 = static_cast<int64_t>(expr5.size());
    auto const& expr7 = static_cast<int64_t>(3);
    auto const& expr8 = hstd::ext::unidata::eval_equal(expr6, expr7);
    condition1 = expr8;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr9 = hstd::Str{"poc.ListSize"};
    return hstd::ext::unidata::VerifyResult::Error(expr9);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.listcontains(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::ListContains);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.numbers;
    auto const& expr6 = static_cast<int64_t>(3);
    auto const& expr7 = hstd::ext::unidata::eval_list_contains(expr5, expr6);
    condition1 = expr7;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr8 = hstd::Str{"poc.ListContains"};
    return hstd::ext::unidata::VerifyResult::Error(expr8);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.listat(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::ListAt);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.numbers;
    auto const& expr6 = static_cast<int64_t>(2);
    auto const& expr7 = expr5.at(expr6);
    auto const& expr8 = static_cast<int64_t>(3);
    auto const& expr9 = hstd::ext::unidata::eval_equal(expr7, expr8);
    condition1 = expr9;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr10 = hstd::Str{"poc.ListAt"};
    return hstd::ext::unidata::VerifyResult::Error(expr10);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.listslice(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::ListSlice);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.numbers;
    auto const& expr6 = static_cast<int64_t>(1);
    auto const& expr7 = static_cast<int64_t>(3);
    auto const& expr8 = hstd::ext::unidata::eval_list_slice<hstd::Vec<int64_t>>(expr5, expr6, expr7);
    bool condition9 = true;
    if (condition9) {
      auto const& expr10 = static_cast<int64_t>(expr8.size());
      auto const& expr11 = static_cast<int64_t>(2);
      auto const& expr12 = hstd::ext::unidata::eval_equal(expr10, expr11);
      condition9 = expr12;
    }
    if (condition9) {
      auto const& expr13 = static_cast<int64_t>(0);
      auto const& expr14 = expr8.at(expr13);
      auto const& expr15 = static_cast<int64_t>(2);
      auto const& expr16 = hstd::ext::unidata::eval_equal(expr14, expr15);
      condition9 = expr16;
    }
    if (condition9) {
      auto const& expr17 = static_cast<int64_t>(1);
      auto const& expr18 = expr8.at(expr17);
      auto const& expr19 = static_cast<int64_t>(3);
      auto const& expr20 = hstd::ext::unidata::eval_equal(expr18, expr19);
      condition9 = expr20;
    }
    condition1 = condition9;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr21 = hstd::Str{"poc.ListSlice"};
    return hstd::ext::unidata::VerifyResult::Error(expr21);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.listslicebounds(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::ListSliceBounds);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.numbers;
    auto const& expr6 = static_cast<int64_t>(-2);
    auto const& expr7 = static_cast<int64_t>(100);
    auto const& expr8 = hstd::ext::unidata::eval_list_slice<hstd::Vec<int64_t>>(expr5, expr6, expr7);
    bool condition9 = true;
    if (condition9) {
      auto const& expr10 = static_cast<int64_t>(expr8.size());
      auto const& expr11 = static_cast<int64_t>(2);
      auto const& expr12 = hstd::ext::unidata::eval_equal(expr10, expr11);
      condition9 = expr12;
    }
    if (condition9) {
      auto const& expr13 = static_cast<int64_t>(0);
      auto const& expr14 = expr8.at(expr13);
      auto const& expr15 = static_cast<int64_t>(2);
      auto const& expr16 = hstd::ext::unidata::eval_equal(expr14, expr15);
      condition9 = expr16;
    }
    if (condition9) {
      auto const& expr17 = static_cast<int64_t>(1);
      auto const& expr18 = expr8.at(expr17);
      auto const& expr19 = static_cast<int64_t>(3);
      auto const& expr20 = hstd::ext::unidata::eval_equal(expr18, expr19);
      condition9 = expr20;
    }
    condition1 = condition9;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr21 = hstd::Str{"poc.ListSliceBounds"};
    return hstd::ext::unidata::VerifyResult::Error(expr21);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.listconcat(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::ListConcat);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.numbers;
    auto const& expr6 = expr0.numbers;
    auto const& expr7 = hstd::ext::unidata::eval_list_concat<hstd::Vec<int64_t>>(expr5, expr6);
    bool condition8 = true;
    if (condition8) {
      auto const& expr9 = static_cast<int64_t>(expr7.size());
      auto const& expr10 = static_cast<int64_t>(6);
      auto const& expr11 = hstd::ext::unidata::eval_equal(expr9, expr10);
      condition8 = expr11;
    }
    if (condition8) {
      auto const& expr12 = static_cast<int64_t>(3);
      auto const& expr13 = expr7.at(expr12);
      auto const& expr14 = expr0.numbers;
      auto const& expr15 = static_cast<int64_t>(0);
      auto const& expr16 = expr14.at(expr15);
      auto const& expr17 = hstd::ext::unidata::eval_equal(expr13, expr16);
      condition8 = expr17;
    }
    condition1 = condition8;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr18 = hstd::Str{"poc.ListConcat"};
    return hstd::ext::unidata::VerifyResult::Error(expr18);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.listempty(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::ListEmpty);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = hstd::Vec<int64_t>{};
    auto const& expr6 = static_cast<int64_t>(expr5.size());
    auto const& expr7 = static_cast<int64_t>(0);
    auto const& expr8 = hstd::ext::unidata::eval_equal(expr6, expr7);
    condition1 = expr8;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr9 = hstd::Str{"poc.ListEmpty"};
    return hstd::ext::unidata::VerifyResult::Error(expr9);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.mapsize(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::MapSize);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.mapping;
    auto const& expr6 = static_cast<int64_t>(expr5.size());
    auto const& expr7 = static_cast<int64_t>(2);
    auto const& expr8 = hstd::ext::unidata::eval_equal(expr6, expr7);
    condition1 = expr8;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr9 = hstd::Str{"poc.MapSize"};
    return hstd::ext::unidata::VerifyResult::Error(expr9);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.mapcontains(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::MapContains);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.mapping;
    auto const& expr6 = hstd::Str{"a"};
    auto const& expr7 = expr5.contains(expr6);
    condition1 = expr7;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr8 = hstd::Str{"poc.MapContains"};
    return hstd::ext::unidata::VerifyResult::Error(expr8);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.mapget(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::MapGet);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.mapping;
    auto const& expr6 = hstd::Str{"a"};
    auto const& expr7 = expr5.at(expr6);
    auto const& expr8 = static_cast<int64_t>(1);
    auto const& expr9 = hstd::ext::unidata::eval_equal(expr7, expr8);
    condition1 = expr9;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr10 = hstd::Str{"poc.MapGet"};
    return hstd::ext::unidata::VerifyResult::Error(expr10);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.mapinsert(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::MapInsert);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.mapping;
    auto const& expr6 = hstd::Str{"c"};
    auto const& expr7 = static_cast<int64_t>(3);
    auto const& expr8 = hstd::ext::unidata::eval_map_insert<hstd::UnorderedMap<hstd::Str, int64_t>>(expr5, expr6, expr7);
    bool condition9 = true;
    if (condition9) {
      auto const& expr10 = static_cast<int64_t>(expr8.size());
      auto const& expr11 = static_cast<int64_t>(3);
      auto const& expr12 = hstd::ext::unidata::eval_equal(expr10, expr11);
      condition9 = expr12;
    }
    if (condition9) {
      auto const& expr13 = hstd::Str{"c"};
      auto const& expr14 = expr8.at(expr13);
      auto const& expr15 = static_cast<int64_t>(3);
      auto const& expr16 = hstd::ext::unidata::eval_equal(expr14, expr15);
      condition9 = expr16;
    }
    if (condition9) {
      auto const& expr17 = expr0.mapping;
      auto const& expr18 = hstd::Str{"c"};
      auto const& expr19 = expr17.contains(expr18);
      auto const& expr20 = !(expr19);
      condition9 = expr20;
    }
    condition1 = condition9;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr21 = hstd::Str{"poc.MapInsert"};
    return hstd::ext::unidata::VerifyResult::Error(expr21);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.mapreplace(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::MapReplace);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.mapping;
    auto const& expr6 = hstd::Str{"a"};
    auto const& expr7 = static_cast<int64_t>(9);
    auto const& expr8 = hstd::ext::unidata::eval_map_insert<hstd::UnorderedMap<hstd::Str, int64_t>>(expr5, expr6, expr7);
    bool condition9 = true;
    if (condition9) {
      auto const& expr10 = static_cast<int64_t>(expr8.size());
      auto const& expr11 = expr0.mapping;
      auto const& expr12 = static_cast<int64_t>(expr11.size());
      auto const& expr13 = hstd::ext::unidata::eval_equal(expr10, expr12);
      condition9 = expr13;
    }
    if (condition9) {
      auto const& expr14 = hstd::Str{"a"};
      auto const& expr15 = expr8.at(expr14);
      auto const& expr16 = static_cast<int64_t>(9);
      auto const& expr17 = hstd::ext::unidata::eval_equal(expr15, expr16);
      condition9 = expr17;
    }
    if (condition9) {
      auto const& expr18 = expr0.mapping;
      auto const& expr19 = hstd::Str{"a"};
      auto const& expr20 = expr18.at(expr19);
      auto const& expr21 = static_cast<int64_t>(1);
      auto const& expr22 = hstd::ext::unidata::eval_equal(expr20, expr21);
      condition9 = expr22;
    }
    condition1 = condition9;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr23 = hstd::Str{"poc.MapReplace"};
    return hstd::ext::unidata::VerifyResult::Error(expr23);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.mapkeys(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::MapKeys);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.mapping;
    auto const& expr6 = hstd::ext::unidata::eval_map_keys<hstd::Vec<hstd::Str>>(expr5);
    bool condition7 = true;
    if (condition7) {
      auto const& expr8 = static_cast<int64_t>(expr6.size());
      auto const& expr9 = static_cast<int64_t>(2);
      auto const& expr10 = hstd::ext::unidata::eval_equal(expr8, expr9);
      condition7 = expr10;
    }
    if (condition7) {
      auto const& expr11 = hstd::Str{"a"};
      auto const& expr12 = hstd::ext::unidata::eval_list_contains(expr6, expr11);
      condition7 = expr12;
    }
    if (condition7) {
      auto const& expr13 = hstd::Str{"b"};
      auto const& expr14 = hstd::ext::unidata::eval_list_contains(expr6, expr13);
      condition7 = expr14;
    }
    condition1 = condition7;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr15 = hstd::Str{"poc.MapKeys"};
    return hstd::ext::unidata::VerifyResult::Error(expr15);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.mapvalues(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::MapValues);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.mapping;
    auto const& expr6 = hstd::ext::unidata::eval_map_values<hstd::Vec<int64_t>>(expr5);
    bool condition7 = true;
    if (condition7) {
      auto const& expr8 = static_cast<int64_t>(expr6.size());
      auto const& expr9 = static_cast<int64_t>(2);
      auto const& expr10 = hstd::ext::unidata::eval_equal(expr8, expr9);
      condition7 = expr10;
    }
    if (condition7) {
      auto const& expr11 = static_cast<int64_t>(1);
      auto const& expr12 = hstd::ext::unidata::eval_list_contains(expr6, expr11);
      condition7 = expr12;
    }
    if (condition7) {
      auto const& expr13 = static_cast<int64_t>(2);
      auto const& expr14 = hstd::ext::unidata::eval_list_contains(expr6, expr13);
      condition7 = expr14;
    }
    condition1 = condition7;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr15 = hstd::Str{"poc.MapValues"};
    return hstd::ext::unidata::VerifyResult::Error(expr15);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.mapempty(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::MapEmpty);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = hstd::UnorderedMap<hstd::Str, int64_t>{};
    auto const& expr6 = static_cast<int64_t>(expr5.size());
    auto const& expr7 = static_cast<int64_t>(0);
    auto const& expr8 = hstd::ext::unidata::eval_equal(expr6, expr7);
    condition1 = expr8;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr9 = hstd::Str{"poc.MapEmpty"};
    return hstd::ext::unidata::VerifyResult::Error(expr9);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.opthasvalue(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::OptHasValue);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.optional;
    auto const& expr6 = expr5.has_value();
    condition1 = expr6;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr7 = hstd::Str{"poc.OptHasValue"};
    return hstd::ext::unidata::VerifyResult::Error(expr7);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.optvalue(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::OptValue);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    bool condition5 = true;
    if (condition5) {
      auto const& expr6 = expr0.optional;
      auto const& expr7 = expr6.has_value();
      condition5 = expr7;
    }
    if (condition5) {
      auto const& expr8 = expr0.optional;
      auto const& expr9 = expr8.value();
      auto const& expr10 = static_cast<int64_t>(3);
      auto const& expr11 = hstd::ext::unidata::eval_equal(expr9, expr10);
      condition5 = expr11;
    }
    condition1 = condition5;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr12 = hstd::Str{"poc.OptValue"};
    return hstd::ext::unidata::VerifyResult::Error(expr12);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.caseis(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::CaseIs);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.choice;
    auto const& expr6 = expr5.data;
    auto const& expr7 = std::holds_alternative<hstd::unidata_dsl::test::Choice::First>(expr6);
    condition1 = expr7;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr8 = hstd::Str{"poc.CaseIs"};
    return hstd::ext::unidata::VerifyResult::Error(expr8);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.casewhich(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::CaseWhich);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.choice;
    auto const& expr6 = expr5.data;
    auto const& expr7 = static_cast<hstd::unidata_dsl::test::Choice::Kind>(expr6.index());
    auto const& expr8 = (expr7 == hstd::unidata_dsl::test::Choice::Kind::First);
    condition1 = expr8;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr9 = hstd::Str{"poc.CaseWhich"};
    return hstd::ext::unidata::VerifyResult::Error(expr9);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.casefield(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::CaseField);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.choice;
    auto const& expr6 = expr5.data;
    auto const& expr7 = std::holds_alternative<hstd::unidata_dsl::test::Choice::First>(expr6);
    std::optional<int64_t> result12 = std::nullopt;
    if (expr7) {
      auto const& expr8 = expr0.choice;
      auto const& expr9 = expr8.data;
      auto const& expr10 = hstd::ext::unidata::eval_get_field<int64_t>(expr9, "value");
      result12.emplace(expr10);
    } else {
      auto const& expr11 = static_cast<int64_t>(-1);
      result12.emplace(expr11);
    }
    auto const& expr13 = static_cast<int64_t>(6);
    auto const& expr14 = hstd::ext::unidata::eval_equal(result12.value(), expr13);
    condition1 = expr14;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr15 = hstd::Str{"poc.CaseField"};
    return hstd::ext::unidata::VerifyResult::Error(expr15);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.enumis(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::EnumIs);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.status;
    auto const& expr6 = (expr5 == hstd::unidata_dsl::test::Status::Ready);
    condition1 = expr6;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr7 = hstd::Str{"poc.EnumIs"};
    return hstd::ext::unidata::VerifyResult::Error(expr7);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.nthget(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::NthGet);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    bool condition5 = true;
    if (condition5) {
      auto const& expr6 = expr0.coords;
      auto const& expr7 = std::get<0>(expr6);
      auto const& expr8 = static_cast<int64_t>(6);
      auto const& expr9 = hstd::ext::unidata::eval_equal(expr7, expr8);
      condition5 = expr9;
    }
    if (condition5) {
      auto const& expr10 = expr0.coords;
      auto const& expr11 = std::get<1>(expr10);
      auto const& expr12 = hstd::Str{"six"};
      auto const& expr13 = hstd::ext::unidata::eval_equal(expr11, expr12);
      condition5 = expr13;
    }
    condition1 = condition5;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr14 = hstd::Str{"poc.NthGet"};
    return hstd::ext::unidata::VerifyResult::Error(expr14);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.isderived(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  hstd::ext::unidata::EvalRuntime expression_runtime = hstd::ext::unidata::EvalRuntime{ctx};
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
  expression_runtime.register_type<hstd::unidata_dsl::test::Status>("Status");
  expression_runtime.register_type<hstd::unidata_dsl::test::CheckKind>("CheckKind");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::Kind>("Choice::Kind");
  expression_runtime.register_base<hstd::unidata_dsl::test::Derived, hstd::unidata_dsl::test::Base>();
  expression_runtime.index((*this_obj));
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::IsDerived);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    bool condition5 = true;
    if (condition5) {
      auto const& expr6 = expr0.derived;
      auto const& expr7 = (expression_runtime.try_as<hstd::unidata_dsl::test::Base>(expr6) != nullptr);
      condition5 = expr7;
    }
    if (condition5) {
      auto const& expr8 = expr0.base;
      auto const& expr9 = (expression_runtime.try_as<hstd::unidata_dsl::test::Derived>(expr8) != nullptr);
      auto const& expr10 = !(expr9);
      condition5 = expr10;
    }
    condition1 = condition5;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr11 = hstd::Str{"poc.IsDerived"};
    return hstd::ext::unidata::VerifyResult::Error(expr11);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.typecond(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  hstd::ext::unidata::EvalRuntime expression_runtime = hstd::ext::unidata::EvalRuntime{ctx};
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
  expression_runtime.register_type<hstd::unidata_dsl::test::Status>("Status");
  expression_runtime.register_type<hstd::unidata_dsl::test::CheckKind>("CheckKind");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::Kind>("Choice::Kind");
  expression_runtime.register_base<hstd::unidata_dsl::test::Derived, hstd::unidata_dsl::test::Base>();
  expression_runtime.index((*this_obj));
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::TypeCond);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.derived;
    auto const& expr6 = hstd::ext::unidata::eval_walk<hstd::Vec<hstd::ext::unidata::EvalDynamic>>(expression_runtime, expr5);
    auto const& expr7 = static_cast<int64_t>(0);
    auto const& expr8 = expr6.at(expr7);
    std::optional<int64_t> result9 = std::nullopt;
    if (!(result9.has_value())) {
      auto const* candidate10 = expression_runtime.try_as<hstd::unidata_dsl::test::Base>(expr8);
      if (candidate10 != nullptr) {
        auto const& expr11 = (*candidate10).id;
        result9.emplace(expr11);
      }
    }
    if (!(result9.has_value())) {
      auto const* candidate12 = expression_runtime.try_as<hstd::unidata_dsl::test::Derived>(expr8);
      if (candidate12 != nullptr) {
        auto const& expr13 = static_cast<int64_t>(-1);
        result9.emplace(expr13);
      }
    }
    if (!(result9.has_value())) {
      throw std::runtime_error{"No type case matched at hstd_test_model.py:504; expected one of: Base, Derived"};
    }
    auto const& expr14 = static_cast<int64_t>(6);
    auto const& expr15 = hstd::ext::unidata::eval_equal(result9.value(), expr14);
    condition1 = expr15;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr16 = hstd::Str{"poc.TypeCond"};
    return hstd::ext::unidata::VerifyResult::Error(expr16);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.typecondoptional(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  hstd::ext::unidata::EvalRuntime expression_runtime = hstd::ext::unidata::EvalRuntime{ctx};
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
  expression_runtime.register_type<hstd::unidata_dsl::test::Status>("Status");
  expression_runtime.register_type<hstd::unidata_dsl::test::CheckKind>("CheckKind");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::Kind>("Choice::Kind");
  expression_runtime.register_base<hstd::unidata_dsl::test::Derived, hstd::unidata_dsl::test::Base>();
  expression_runtime.index((*this_obj));
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::TypeCondOptional);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    bool condition5 = true;
    if (condition5) {
      auto const& expr6 = expr0.base;
      auto const& expr7 = hstd::ext::unidata::eval_walk<hstd::Vec<hstd::ext::unidata::EvalDynamic>>(expression_runtime, expr6);
      auto const& expr8 = static_cast<int64_t>(0);
      auto const& expr9 = expr7.at(expr8);
      std::optional<int64_t> result10 = std::nullopt;
      if (!(result10.has_value())) {
        auto const* candidate11 = expression_runtime.try_as<hstd::unidata_dsl::test::Derived>(expr9);
        if (candidate11 != nullptr) {
          auto const& expr12 = (*candidate11).id;
          result10.emplace(expr12);
        }
      }
      auto const& expr13 = result10.has_value();
      auto const& expr14 = !(expr13);
      condition5 = expr14;
    }
    if (condition5) {
      auto const& expr15 = expr0.derived;
      auto const& expr16 = hstd::ext::unidata::eval_walk<hstd::Vec<hstd::ext::unidata::EvalDynamic>>(expression_runtime, expr15);
      auto const& expr17 = static_cast<int64_t>(0);
      auto const& expr18 = expr16.at(expr17);
      std::optional<int64_t> result19 = std::nullopt;
      if (!(result19.has_value())) {
        auto const* candidate20 = expression_runtime.try_as<hstd::unidata_dsl::test::Derived>(expr18);
        if (candidate20 != nullptr) {
          auto const& expr21 = (*candidate20).id;
          result19.emplace(expr21);
        }
      }
      auto const& expr22 = result19.value();
      auto const& expr23 = static_cast<int64_t>(6);
      auto const& expr24 = hstd::ext::unidata::eval_equal(expr22, expr23);
      condition5 = expr24;
    }
    condition1 = condition5;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr25 = hstd::Str{"poc.TypeCondOptional"};
    return hstd::ext::unidata::VerifyResult::Error(expr25);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.typeof(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  hstd::ext::unidata::EvalRuntime expression_runtime = hstd::ext::unidata::EvalRuntime{ctx};
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
  expression_runtime.register_type<hstd::unidata_dsl::test::Status>("Status");
  expression_runtime.register_type<hstd::unidata_dsl::test::CheckKind>("CheckKind");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::Kind>("Choice::Kind");
  expression_runtime.register_base<hstd::unidata_dsl::test::Derived, hstd::unidata_dsl::test::Base>();
  expression_runtime.index((*this_obj));
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::TypeOf);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    auto const& expr5 = expr0.derived;
    auto const& expr6 = hstd::ext::unidata::eval_walk<hstd::Vec<hstd::ext::unidata::EvalDynamic>>(expression_runtime, expr5);
    auto const& expr7 = static_cast<int64_t>(0);
    auto const& expr8 = expr6.at(expr7);
    std::optional<hstd::Str> result9 = std::nullopt;
    if (!(result9.has_value())) {
      auto const* candidate10 = expression_runtime.try_as<hstd::unidata_dsl::test::Base>(expr8);
      if (candidate10 != nullptr) {
        auto const& expr11 = expression_runtime.type_of((*candidate10));
        result9.emplace(expr11);
      }
    }
    if (!(result9.has_value())) {
      throw std::runtime_error{"No type case matched at hstd_test_model.py:545; expected one of: Base"};
    }
    auto const& expr12 = hstd::Str{"Derived"};
    auto const& expr13 = hstd::ext::unidata::eval_equal(result9.value(), expr12);
    condition1 = expr13;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr14 = hstd::Str{"poc.TypeOf"};
    return hstd::ext::unidata::VerifyResult::Error(expr14);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.pathof(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  hstd::ext::unidata::EvalRuntime expression_runtime = hstd::ext::unidata::EvalRuntime{ctx};
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
  expression_runtime.register_type<hstd::unidata_dsl::test::Status>("Status");
  expression_runtime.register_type<hstd::unidata_dsl::test::CheckKind>("CheckKind");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::Kind>("Choice::Kind");
  expression_runtime.register_base<hstd::unidata_dsl::test::Derived, hstd::unidata_dsl::test::Base>();
  expression_runtime.index((*this_obj));
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::PathOf);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    bool condition5 = true;
    if (condition5) {
      auto const& expr6 = expr0.number;
      auto const& expr7 = expression_runtime.path_of(expr6);
      auto const& expr8 = hstd::ext::unidata::eval_str_format("%s", expr7);
      auto const& expr9 = hstd::Str{"/number"};
      auto const& expr10 = hstd::ext::unidata::eval_equal(expr8, expr9);
      condition5 = expr10;
    }
    if (condition5) {
      auto const& expr11 = expr0.numbers;
      auto callback15 = [&](auto const& item12) {
                        auto const& expr13 = expression_runtime.path_of(item12);
                        auto const& expr14 = hstd::ext::unidata::eval_str_format("%s", expr13);
                        return expr14;
                        };
      auto const& expr16 = hstd::ext::unidata::eval_map<hstd::Vec<hstd::Str>>(expr11, callback15);
      auto const& expr17 = static_cast<int64_t>(0);
      auto const& expr18 = expr16.at(expr17);
      auto const& expr19 = hstd::Str{"/numbers/0"};
      auto const& expr20 = hstd::ext::unidata::eval_equal(expr18, expr19);
      condition5 = expr20;
    }
    if (condition5) {
      auto const& expr21 = expr0.derived;
      auto const& expr22 = hstd::ext::unidata::eval_walk<hstd::Vec<hstd::ext::unidata::EvalDynamic>>(expression_runtime, expr21);
      auto const& expr23 = static_cast<int64_t>(0);
      auto const& expr24 = expr22.at(expr23);
      std::optional<hstd::Str> result25 = std::nullopt;
      if (!(result25.has_value())) {
        auto const* candidate26 = expression_runtime.try_as<hstd::unidata_dsl::test::Base>(expr24);
        if (candidate26 != nullptr) {
          auto const& expr27 = expression_runtime.path_of((*candidate26));
          auto const& expr28 = hstd::ext::unidata::eval_str_format("%s", expr27);
          result25.emplace(expr28);
        }
      }
      if (!(result25.has_value())) {
        throw std::runtime_error{"No type case matched at hstd_test_model.py:565; expected one of: Base"};
      }
      auto const& expr29 = hstd::Str{"/derived"};
      auto const& expr30 = hstd::ext::unidata::eval_equal(result25.value(), expr29);
      condition5 = expr30;
    }
    condition1 = condition5;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr31 = hstd::Str{"poc.PathOf"};
    return hstd::ext::unidata::VerifyResult::Error(expr31);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::OperationChecks::__check_record_poc.emptycollections(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::OperationChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  bool condition1 = false;
  if (!(condition1)) {
    auto const& expr2 = expr0.operation;
    auto const& expr3 = (expr2 == hstd::unidata_dsl::test::CheckKind::EmptyCollections);
    auto const& expr4 = !(expr3);
    condition1 = expr4;
  }
  if (!(condition1)) {
    bool condition5 = true;
    if (condition5) {
      auto const& expr6 = hstd::Vec<int64_t>{};
      auto callback10 = [&](auto const& item7) {
                        auto const& expr8 = static_cast<int64_t>(0);
                        auto const& expr9 = (expr8 < item7);
                        return expr9;
                        };
      auto const& expr11 = hstd::ext::unidata::eval_all(expr6, callback10);
      condition5 = expr11;
    }
    if (condition5) {
      auto const& expr12 = hstd::Vec<int64_t>{};
      auto callback16 = [&](auto const& item13) {
                        auto const& expr14 = static_cast<int64_t>(0);
                        auto const& expr15 = (expr14 < item13);
                        return expr15;
                        };
      auto const& expr17 = hstd::ext::unidata::eval_exists(expr12, callback16);
      auto const& expr18 = !(expr17);
      condition5 = expr18;
    }
    if (condition5) {
      auto const& expr19 = hstd::Vec<int64_t>{};
      auto callback23 = [&](auto const& item20) {
                        auto const& expr21 = static_cast<int64_t>(0);
                        auto const& expr22 = (expr21 < item20);
                        return expr22;
                        };
      auto const& expr24 = hstd::ext::unidata::eval_exists_one(expr19, callback23);
      auto const& expr25 = !(expr24);
      condition5 = expr25;
    }
    if (condition5) {
      auto const& expr26 = hstd::Vec<int64_t>{};
      auto const& expr27 = hstd::ext::unidata::eval_sum<int64_t>(expr26);
      auto const& expr28 = static_cast<int64_t>(0);
      auto const& expr29 = hstd::ext::unidata::eval_equal(expr27, expr28);
      condition5 = expr29;
    }
    if (condition5) {
      auto const& expr30 = hstd::Vec<int64_t>{};
      auto callback35 = [&](auto const& item31) {
                        auto const& expr32 = expr0.mapping;
                        auto const& expr33 = hstd::Str{"absent"};
                        auto const& expr34 = expr32.at(expr33);
                        return expr34;
                        };
      auto const& expr36 = hstd::ext::unidata::eval_map<hstd::Vec<int64_t>>(expr30, callback35);
      auto const& expr37 = static_cast<int64_t>(expr36.size());
      auto const& expr38 = static_cast<int64_t>(0);
      auto const& expr39 = hstd::ext::unidata::eval_equal(expr37, expr38);
      condition5 = expr39;
    }
    if (condition5) {
      auto const& expr40 = hstd::Vec<int64_t>{};
      auto callback46 = [&](auto const& item41) {
                        auto const& expr42 = expr0.optional;
                        auto const& expr43 = expr42.value();
                        auto const& expr44 = static_cast<int64_t>(0);
                        auto const& expr45 = hstd::ext::unidata::eval_equal(expr43, expr44);
                        return expr45;
                        };
      auto const& expr47 = hstd::ext::unidata::eval_filter<hstd::Vec<int64_t>>(expr40, callback46);
      auto const& expr48 = static_cast<int64_t>(expr47.size());
      auto const& expr49 = static_cast<int64_t>(0);
      auto const& expr50 = hstd::ext::unidata::eval_equal(expr48, expr49);
      condition5 = expr50;
    }
    if (condition5) {
      auto const& expr51 = hstd::Vec<int64_t>{};
      auto callback54 = [&](auto const& item52) {
                        auto const& expr53 = expr0.optional;
                        return expr53;
                        };
      auto const& expr55 = hstd::ext::unidata::eval_filter_map<hstd::Vec<int64_t>>(expr51, callback54);
      auto const& expr56 = static_cast<int64_t>(expr55.size());
      auto const& expr57 = static_cast<int64_t>(0);
      auto const& expr58 = hstd::ext::unidata::eval_equal(expr56, expr57);
      condition5 = expr58;
    }
    if (condition5) {
      auto const& expr59 = hstd::Vec<int64_t>{};
      auto callback65 = [&](auto const& item60) {
                        auto const& expr61 = expr0.optional;
                        auto const& expr62 = expr61.value();
                        auto const& expr63 = static_cast<int64_t>(0);
                        auto const& expr64 = hstd::ext::unidata::eval_equal(expr62, expr63);
                        return expr64;
                        };
      auto const& expr66 = hstd::ext::unidata::eval_take_while<hstd::Vec<int64_t>>(expr59, callback65);
      auto const& expr67 = static_cast<int64_t>(expr66.size());
      auto const& expr68 = static_cast<int64_t>(0);
      auto const& expr69 = hstd::ext::unidata::eval_equal(expr67, expr68);
      condition5 = expr69;
    }
    if (condition5) {
      auto const& expr70 = hstd::Vec<int64_t>{};
      auto callback75 = [&](auto const& item71) {
                        auto const& expr72 = expr0.mapping;
                        auto const& expr73 = hstd::Str{"absent"};
                        auto const& expr74 = expr72.at(expr73);
                        return expr74;
                        };
      auto const& expr76 = hstd::ext::unidata::eval_group_by<hstd::UnorderedMap<int64_t, hstd::Vec<int64_t>>>(expr70, callback75);
      auto const& expr77 = static_cast<int64_t>(expr76.size());
      auto const& expr78 = static_cast<int64_t>(0);
      auto const& expr79 = hstd::ext::unidata::eval_equal(expr77, expr78);
      condition5 = expr79;
    }
    if (condition5) {
      auto const& expr80 = hstd::Vec<int64_t>{};
      auto const& expr81 = static_cast<int64_t>(9);
      auto callback82 = [&](auto const& item83, auto const& item84) {
                        auto const& expr85 = expr0.mapping;
                        auto const& expr86 = hstd::Str{"absent"};
                        auto const& expr87 = expr85.at(expr86);
                        return expr87;
                        };
      auto const& expr88 = hstd::ext::unidata::eval_fold<int64_t>(expr80, expr81, callback82);
      auto const& expr89 = static_cast<int64_t>(9);
      auto const& expr90 = hstd::ext::unidata::eval_equal(expr88, expr89);
      condition5 = expr90;
    }
    if (condition5) {
      auto const& expr91 = hstd::Vec<int64_t>{};
      auto const& expr92 = hstd::Vec<int64_t>{};
      auto const& expr93 = hstd::ext::unidata::eval_list_concat<hstd::Vec<int64_t>>(expr91, expr92);
      auto const& expr94 = static_cast<int64_t>(expr93.size());
      auto const& expr95 = static_cast<int64_t>(0);
      auto const& expr96 = hstd::ext::unidata::eval_equal(expr94, expr95);
      condition5 = expr96;
    }
    if (condition5) {
      auto const& expr97 = true;
      std::optional<int64_t> result101 = std::nullopt;
      if (expr97) {
        auto const& expr98 = static_cast<int64_t>(42);
        result101.emplace(expr98);
      } else {
        auto const& expr99 = hstd::Vec<int64_t>{};
        auto const& expr100 = hstd::ext::unidata::eval_min<int64_t>(expr99);
        result101.emplace(expr100);
      }
      auto const& expr102 = static_cast<int64_t>(42);
      auto const& expr103 = hstd::ext::unidata::eval_equal(result101.value(), expr102);
      condition5 = expr103;
    }
    if (condition5) {
      auto const& expr104 = true;
      std::optional<int64_t> result108 = std::nullopt;
      if (expr104) {
        auto const& expr105 = static_cast<int64_t>(42);
        result108.emplace(expr105);
      } else {
        auto const& expr106 = hstd::Vec<int64_t>{};
        auto const& expr107 = hstd::ext::unidata::eval_max<int64_t>(expr106);
        result108.emplace(expr107);
      }
      auto const& expr109 = static_cast<int64_t>(42);
      auto const& expr110 = hstd::ext::unidata::eval_equal(result108.value(), expr109);
      condition5 = expr110;
    }
    condition1 = condition5;
  }
  if (condition1) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr111 = hstd::Str{"poc.EmptyCollections"};
    return hstd::ext::unidata::VerifyResult::Error(expr111);
  }
}
hstd::ext::unidata::VerifyCheckCollection const* hstd::unidata_dsl::test::OperationChecks::get_unidata_checks() {
  static hstd::ext::unidata::VerifyCheckCollection checks
   = {{
      {hstd::ext::unidata::VerifyKey{"OperationChecks", std::nullopt}, hstd::ext::unidata::VerifyCbList{hstd::ext::unidata::VerifyCb{&__check_record_poc.eq}, hstd::ext::unidata::VerifyCb{&__check_record_poc.ne}, hstd::ext::unidata::VerifyCb{&__check_record_poc.lt}, hstd::ext::unidata::VerifyCb{&__check_record_poc.le}, hstd::ext::unidata::VerifyCb{&__check_record_poc.add}, hstd::ext::unidata::VerifyCb{&__check_record_poc.sub}, hstd::ext::unidata::VerifyCb{&__check_record_poc.mul}, hstd::ext::unidata::VerifyCb{&__check_record_poc.div}, hstd::ext::unidata::VerifyCb{&__check_record_poc.constfloat}, hstd::ext::unidata::VerifyCb{&__check_record_poc.constbool}, hstd::ext::unidata::VerifyCb{&__check_record_poc.and}, hstd::ext::unidata::VerifyCb{&__check_record_poc.or}, hstd::ext::unidata::VerifyCb{&__check_record_poc.not}, hstd::ext::unidata::VerifyCb{&__check_record_poc.cond}, hstd::ext::unidata::VerifyCb{&__check_record_poc.condlazy}, hstd::ext::unidata::VerifyCb{&__check_record_poc.all}, hstd::ext::unidata::VerifyCb{&__check_record_poc.exists}, hstd::ext::unidata::VerifyCb{&__check_record_poc.existsone}, hstd::ext::unidata::VerifyCb{&__check_record_poc.map}, hstd::ext::unidata::VerifyCb{&__check_record_poc.filter}, hstd::ext::unidata::VerifyCb{&__check_record_poc.filtermap}, hstd::ext::unidata::VerifyCb{&__check_record_poc.takewhile}, hstd::ext::unidata::VerifyCb{&__check_record_poc.groupby}, hstd::ext::unidata::VerifyCb{&__check_record_poc.fold}, hstd::ext::unidata::VerifyCb{&__check_record_poc.walk}, hstd::ext::unidata::VerifyCb{&__check_record_poc.sum}, hstd::ext::unidata::VerifyCb{&__check_record_poc.min}, hstd::ext::unidata::VerifyCb{&__check_record_poc.max}, hstd::ext::unidata::VerifyCb{&__check_record_poc.strsize}, hstd::ext::unidata::VerifyCb{&__check_record_poc.strmatches}, hstd::ext::unidata::VerifyCb{&__check_record_poc.strformat}, hstd::ext::unidata::VerifyCb{&__check_record_poc.listsize}, hstd::ext::unidata::VerifyCb{&__check_record_poc.listcontains}, hstd::ext::unidata::VerifyCb{&__check_record_poc.listat}, hstd::ext::unidata::VerifyCb{&__check_record_poc.listslice}, hstd::ext::unidata::VerifyCb{&__check_record_poc.listslicebounds}, hstd::ext::unidata::VerifyCb{&__check_record_poc.listconcat}, hstd::ext::unidata::VerifyCb{&__check_record_poc.listempty}, hstd::ext::unidata::VerifyCb{&__check_record_poc.mapsize}, hstd::ext::unidata::VerifyCb{&__check_record_poc.mapcontains}, hstd::ext::unidata::VerifyCb{&__check_record_poc.mapget}, hstd::ext::unidata::VerifyCb{&__check_record_poc.mapinsert}, hstd::ext::unidata::VerifyCb{&__check_record_poc.mapreplace}, hstd::ext::unidata::VerifyCb{&__check_record_poc.mapkeys}, hstd::ext::unidata::VerifyCb{&__check_record_poc.mapvalues}, hstd::ext::unidata::VerifyCb{&__check_record_poc.mapempty}, hstd::ext::unidata::VerifyCb{&__check_record_poc.opthasvalue}, hstd::ext::unidata::VerifyCb{&__check_record_poc.optvalue}, hstd::ext::unidata::VerifyCb{&__check_record_poc.caseis}, hstd::ext::unidata::VerifyCb{&__check_record_poc.casewhich}, hstd::ext::unidata::VerifyCb{&__check_record_poc.casefield}, hstd::ext::unidata::VerifyCb{&__check_record_poc.enumis}, hstd::ext::unidata::VerifyCb{&__check_record_poc.nthget}, hstd::ext::unidata::VerifyCb{&__check_record_poc.isderived}, hstd::ext::unidata::VerifyCb{&__check_record_poc.typecond}, hstd::ext::unidata::VerifyCb{&__check_record_poc.typecondoptional}, hstd::ext::unidata::VerifyCb{&__check_record_poc.typeof}, hstd::ext::unidata::VerifyCb{&__check_record_poc.pathof}, hstd::ext::unidata::VerifyCb{&__check_record_poc.emptycollections}}}
      }};
  return &checks;
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::FieldChecks::__check_text_textcheck(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::FieldChecks const*>(value);
  auto const& expr0 = (*(&this_obj->text));
  auto const& expr1 = static_cast<int64_t>(0);
  auto const& expr2 = hstd::ext::unidata::eval_str_size(&expr0);
  auto const& expr3 = (expr1 < expr2);
  if (expr3) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr4 = hstd::ext::unidata::eval_str_size(&expr0);
    auto const& expr5 = hstd::ext::unidata::eval_str_format("text length is %d", expr4);
    return hstd::ext::unidata::VerifyResult::Error(expr5);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::FieldChecks::__check_numbers_numberscheck(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::FieldChecks const*>(value);
  auto const& expr0 = (*(&this_obj->numbers));
  auto callback4 = [&](auto const& item1) {
                   auto const& expr2 = static_cast<int64_t>(0);
                   auto const& expr3 = (expr2 < item1);
                   return expr3;
                   };
  auto const& expr5 = hstd::ext::unidata::eval_all(expr0, callback4);
  if (expr5) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr6 = hstd::ext::unidata::eval_str_format("values=%s", expr0);
    return hstd::ext::unidata::VerifyResult::Error(expr6);
  }
}
hstd::ext::unidata::VerifyCheckCollection const* hstd::unidata_dsl::test::FieldChecks::get_unidata_checks() {
  static hstd::ext::unidata::VerifyCheckCollection checks
   = {{
      {hstd::ext::unidata::VerifyKey{"FieldChecks", "text"}, hstd::ext::unidata::VerifyCbList{hstd::ext::unidata::VerifyCb{&__check_text_textcheck}}},
      {hstd::ext::unidata::VerifyKey{"FieldChecks", "numbers"}, hstd::ext::unidata::VerifyCbList{hstd::ext::unidata::VerifyCb{&__check_numbers_numberscheck}}}
      }};
  return &checks;
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::MessageChecks::__check_record_formatmessage(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::MessageChecks const*>(value);
  auto const& expr0 = (*(this_obj));
  auto const& expr1 = expr0.number;
  auto const& expr2 = static_cast<int64_t>(6);
  auto const& expr3 = hstd::ext::unidata::eval_equal(expr1, expr2);
  if (expr3) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr4 = expr0.number;
    auto const& expr5 = expr0.real;
    auto const& expr6 = expr0.real;
    auto const& expr7 = expr0.number;
    auto const& expr8 = expr0.number;
    auto const& expr9 = expr0.flag;
    auto const& expr10 = expr0.text;
    auto const& expr11 = expr0.numbers;
    auto const& expr12 = expr0.details;
    auto const& expr13 = hstd::Str{"detail"};
    auto const& expr14 = expr12.at(expr13);
    auto const& expr15 = hstd::ext::unidata::eval_str_format("n=%d real=%f sci=%e hex=%x oct=%o flag=%b text=%s list=%s lookup=%d %%", expr4, expr5, expr6, expr7, expr8, expr9, expr10, expr11, expr14);
    return hstd::ext::unidata::VerifyResult::Error(expr15);
  }
}
hstd::ext::unidata::VerifyCheckCollection const* hstd::unidata_dsl::test::MessageChecks::get_unidata_checks() {
  static hstd::ext::unidata::VerifyCheckCollection checks
   = {{
      {hstd::ext::unidata::VerifyKey{"MessageChecks", std::nullopt}, hstd::ext::unidata::VerifyCbList{hstd::ext::unidata::VerifyCb{&__check_record_formatmessage}}}
      }};
  return &checks;
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::Graph::__check_record_graphuniquenodeids(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::Graph const*>(value);
  hstd::ext::unidata::EvalRuntime expression_runtime = hstd::ext::unidata::EvalRuntime{ctx};
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
  expression_runtime.register_type<hstd::unidata_dsl::test::Status>("Status");
  expression_runtime.register_type<hstd::unidata_dsl::test::CheckKind>("CheckKind");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::Kind>("Choice::Kind");
  expression_runtime.register_base<hstd::unidata_dsl::test::Derived, hstd::unidata_dsl::test::Base>();
  expression_runtime.index((*this_obj));
  auto const& expr0 = (*(this_obj));
  auto const& expr1 = hstd::ext::unidata::eval_walk<hstd::Vec<hstd::ext::unidata::EvalDynamic>>(expression_runtime, expr0);
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
  auto const& expr6 = hstd::ext::unidata::eval_filter_map<hstd::Vec<hstd::unidata_dsl::test::Node>>(expr1, callback5);
  auto callback9 = [&](auto const& item7) {
                   auto const& expr8 = item7.id;
                   return expr8;
                   };
  auto const& expr10 = hstd::ext::unidata::eval_group_by<hstd::UnorderedMap<hstd::Str, hstd::Vec<hstd::unidata_dsl::test::Node>>>(expr6, callback9);
  auto const& expr11 = hstd::ext::unidata::eval_map_values<hstd::Vec<hstd::Vec<hstd::unidata_dsl::test::Node>>>(expr10);
  auto callback16 = [&](auto const& item12) {
                    auto const& expr13 = static_cast<int64_t>(item12.size());
                    auto const& expr14 = static_cast<int64_t>(1);
                    auto const& expr15 = (expr13 <= expr14);
                    return expr15;
                    };
  auto const& expr17 = hstd::ext::unidata::eval_all(expr11, callback16);
  if (expr17) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr18 = hstd::ext::unidata::eval_walk<hstd::Vec<hstd::ext::unidata::EvalDynamic>>(expression_runtime, expr0);
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
    auto const& expr23 = hstd::ext::unidata::eval_filter_map<hstd::Vec<hstd::unidata_dsl::test::Node>>(expr18, callback22);
    auto callback26 = [&](auto const& item24) {
                      auto const& expr25 = item24.id;
                      return expr25;
                      };
    auto const& expr27 = hstd::ext::unidata::eval_group_by<hstd::UnorderedMap<hstd::Str, hstd::Vec<hstd::unidata_dsl::test::Node>>>(expr23, callback26);
    auto const& expr28 = hstd::ext::unidata::eval_map_values<hstd::Vec<hstd::Vec<hstd::unidata_dsl::test::Node>>>(expr27);
    auto callback33 = [&](auto const& item29) {
                      auto const& expr30 = static_cast<int64_t>(1);
                      auto const& expr31 = static_cast<int64_t>(item29.size());
                      auto const& expr32 = (expr30 < expr31);
                      return expr32;
                      };
    auto const& expr34 = hstd::ext::unidata::eval_filter<hstd::Vec<hstd::Vec<hstd::unidata_dsl::test::Node>>>(expr28, callback33);
    auto callback40 = [&](auto const& item35) {
                      auto callback38 = [&](auto const& item36) {
                                        auto const& expr37 = expression_runtime.path_of(item36);
                                        return expr37;
                                        };
                      auto const& expr39 = hstd::ext::unidata::eval_map<hstd::Vec<std::filesystem::path>>(item35, callback38);
                      return expr39;
                      };
    auto const& expr41 = hstd::ext::unidata::eval_map<hstd::Vec<hstd::Vec<std::filesystem::path>>>(expr34, callback40);
    auto const& expr42 = hstd::ext::unidata::eval_str_format("duplicate node ids at %s", expr41);
    return hstd::ext::unidata::VerifyResult::Error(expr42);
  }
}
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::Graph::__check_record_graphnodanglingedges(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::Graph const*>(value);
  hstd::ext::unidata::EvalRuntime expression_runtime = hstd::ext::unidata::EvalRuntime{ctx};
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
  expression_runtime.register_type<hstd::unidata_dsl::test::Status>("Status");
  expression_runtime.register_type<hstd::unidata_dsl::test::CheckKind>("CheckKind");
  expression_runtime.register_type<hstd::unidata_dsl::test::Choice::Kind>("Choice::Kind");
  expression_runtime.register_base<hstd::unidata_dsl::test::Derived, hstd::unidata_dsl::test::Base>();
  expression_runtime.index((*this_obj));
  auto const& expr0 = (*(this_obj));
  auto const& expr1 = hstd::ext::unidata::eval_walk<hstd::Vec<hstd::ext::unidata::EvalDynamic>>(expression_runtime, expr0);
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
  auto const& expr6 = hstd::ext::unidata::eval_filter_map<hstd::Vec<hstd::unidata_dsl::test::Node>>(expr1, callback5);
  auto callback9 = [&](auto const& item7) {
                   auto const& expr8 = item7.id;
                   return expr8;
                   };
  auto const& expr10 = hstd::ext::unidata::eval_map<hstd::Vec<hstd::Str>>(expr6, callback9);
  auto const& expr11 = expr0.edges;
  auto callback18 = [&](auto const& item12) {
                    bool condition13 = true;
                    if (condition13) {
                      auto const& expr14 = item12.source;
                      auto const& expr15 = hstd::ext::unidata::eval_list_contains(expr10, expr14);
                      condition13 = expr15;
                    }
                    if (condition13) {
                      auto const& expr16 = item12.target;
                      auto const& expr17 = hstd::ext::unidata::eval_list_contains(expr10, expr16);
                      condition13 = expr17;
                    }
                    return condition13;
                    };
  auto const& expr19 = hstd::ext::unidata::eval_all(expr11, callback18);
  if (expr19) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    auto const& expr20 = hstd::ext::unidata::eval_walk<hstd::Vec<hstd::ext::unidata::EvalDynamic>>(expression_runtime, expr0);
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
    auto const& expr25 = hstd::ext::unidata::eval_filter_map<hstd::Vec<hstd::unidata_dsl::test::Node>>(expr20, callback24);
    auto callback28 = [&](auto const& item26) {
                      auto const& expr27 = item26.id;
                      return expr27;
                      };
    auto const& expr29 = hstd::ext::unidata::eval_map<hstd::Vec<hstd::Str>>(expr25, callback28);
    auto const& expr30 = expr0.edges;
    auto callback38 = [&](auto const& item31) {
                      bool condition32 = true;
                      if (condition32) {
                        auto const& expr33 = item31.source;
                        auto const& expr34 = hstd::ext::unidata::eval_list_contains(expr29, expr33);
                        condition32 = expr34;
                      }
                      if (condition32) {
                        auto const& expr35 = item31.target;
                        auto const& expr36 = hstd::ext::unidata::eval_list_contains(expr29, expr35);
                        condition32 = expr36;
                      }
                      auto const& expr37 = !(condition32);
                      return expr37;
                      };
    auto const& expr39 = hstd::ext::unidata::eval_filter<hstd::Vec<hstd::unidata_dsl::test::Edge>>(expr30, callback38);
    auto callback42 = [&](auto const& item40) {
                      auto const& expr41 = expression_runtime.path_of(item40);
                      return expr41;
                      };
    auto const& expr43 = hstd::ext::unidata::eval_map<hstd::Vec<std::filesystem::path>>(expr39, callback42);
    auto const& expr44 = hstd::ext::unidata::eval_str_format("dangling edges at %s", expr43);
    return hstd::ext::unidata::VerifyResult::Error(expr44);
  }
}
hstd::ext::unidata::VerifyCheckCollection const* hstd::unidata_dsl::test::Graph::get_unidata_checks() {
  static hstd::ext::unidata::VerifyCheckCollection checks
   = {{
      {hstd::ext::unidata::VerifyKey{"Graph", std::nullopt}, hstd::ext::unidata::VerifyCbList{hstd::ext::unidata::VerifyCb{&__check_record_graphuniquenodeids}, hstd::ext::unidata::VerifyCb{&__check_record_graphnodanglingedges}}}
      }};
  return &checks;
}
/* clang-format on */