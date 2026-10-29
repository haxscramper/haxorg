/* clang-format off */
#pragma once
#include <hstd_cpp_lib/system/basic_templates.hpp>
#include <hstd_cpp_lib/system/reflection.hpp>
#include <hstd_cpp_lib/stdlib/containers/Opt.hpp>
#include <hstd_cpp_lib/stdlib/containers/Vec.hpp>
#include <hstd_cpp_lib/stdlib/containers/Map.hpp>
#include <hstd_cpp_lib/proto_serde/hstd_unidata_validate.hpp>
struct TrivialText {
  BOOST_DESCRIBE_CLASS(TrivialText, (), (), (), (text));
  hstd::Str text;
  static hstd::ext::unidata::VerifyResult __check_text_text_check(hstd::ext::unidata::VerifyContext ctx, void const* value);
};

/* clang-format on */
