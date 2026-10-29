/* clang-format off */
#include "tUnidataDSLModel.hpp"
hstd::ext::unidata::VerifyResult hstd::unidata_dsl::test::TrivialText::__check_text_text_check(hstd::ext::unidata::VerifyContext const* ctx, void const* value) {
  auto const* this_obj = static_cast<hstd::unidata_dsl::test::TrivialText const*>(value);
  if (0 < hstd::ext::unidata::eval_str_size(&this_obj->text)) {
    return hstd::ext::unidata::VerifyResult::Ok();
  } else {
    return hstd::ext::unidata::VerifyResult::Error("text must not be empty");
  }
}
hstd::ext::unidata::VerifyCheckCollection const* hstd::unidata_dsl::test::TrivialText::get_unidata_checks() {
  static
  hstd::ext::unidata::VerifyCheckCollection checks
   =
  {
  {
  {
  hstd::ext::unidata::VerifyKey{"TrivialText", "text"}, hstd::ext::unidata::VerifyCbList{hstd::ext::unidata::VerifyCb{&__check_text_text_check}}
  }
  }
  }
  ;
  return &checks;
}
/* clang-format on */
