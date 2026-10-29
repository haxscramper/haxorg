#include <gtest/gtest.h>
#include <hstd_cpp_lib/extra/error_format/gtest_utils.hpp>

#include "hstd_cpp_lib/proto_serde/hstd_unidata_validate.hpp"
#include "tUnidataDSLModel.hpp"
using namespace hstd;

namespace M = hstd::unidata_dsl::test;

TEST(UnidataDSL, TrivialStringField) {
    {
        M::TrivialText text{.text = "non-empty"};
        auto           verify = ext::unidata::verify_all(text).getFail();
        EXPECT_EQ(verify.size(), 0) << hstd::fmt1(verify);
    }
    {
        M::TrivialText text{.text = ""};
        auto           verify = ext::unidata::verify_all(text).getFail();
        EXPECT_EQ(verify.size(), 1) << hstd::fmt1(verify);
    }
}
