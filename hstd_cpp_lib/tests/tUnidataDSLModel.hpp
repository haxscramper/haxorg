/* clang-format off */
#pragma once
#include <hstd_cpp_lib/system/basic_templates.hpp>
#include <hstd_cpp_lib/system/reflection.hpp>
#include <hstd_cpp_lib/stdlib/containers/Opt.hpp>
#include <hstd_cpp_lib/stdlib/containers/Vec.hpp>
#include <hstd_cpp_lib/stdlib/containers/Map.hpp>
#include <hstd_cpp_lib/proto_serde/hstd_unidata_validate.hpp>
namespace hstd::unidata_dsl::test {
struct TrivialText {
  BOOST_DESCRIBE_CLASS(TrivialText, (), (), (), (text, unidata_id));
  hstd::Str text;
  static constexpr std::string const unidata_id = "TrivialText";
  static hstd::ext::unidata::VerifyResult __check_text_text_check(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyCheckCollection const* get_unidata_checks();
};

}
/* clang-format on */
