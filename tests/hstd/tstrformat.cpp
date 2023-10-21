#include <hstd/stdlib/strformat.hpp>
//#include "common.hpp"
#include <gtest/gtest.h>
#include <absl/log/check.h>


TEST(StringFormatting, Plaintext) {
    EXPECT_EQ("A" % to_string_vec("a"), "A");
}

TEST(StringFormatting, BasicInterpolationFragmentParsing) {
    {
        auto f = addfFragments("${A}+${B}");
        EXPECT_EQ(f.size(), 3);
        EXPECT_EQ(f[0].text, "A");
        EXPECT_EQ(f[0].kind, AddfFragmentKind::Expr);
        EXPECT_EQ(f[1].kind, AddfFragmentKind::Text);
        EXPECT_EQ(f[1].text, "+");
        EXPECT_EQ(f[2].kind, AddfFragmentKind::Expr);
        EXPECT_EQ(f[2].text, "B");
    }
    {
        auto f = addfFragments("A");
        EXPECT_EQ(f.size(), 1);
        EXPECT_EQ(f[0].kind, AddfFragmentKind::Text);
        EXPECT_EQ(f[0].text, "A");
    }
    {
        auto f = addfFragments("$A");
        EXPECT_EQ(f.size(), 1);
        EXPECT_EQ(f[0].kind, AddfFragmentKind::Var);
        EXPECT_EQ(f[0].text, "A");
    }
    {
        auto f = addfFragments("${A}");
        EXPECT_EQ(f.size(), 1);
        EXPECT_EQ(f[0].kind, AddfFragmentKind::Expr);
        EXPECT_EQ(f[0].text, "A");
    }
}

#define EXPECT_THROW_WITH_MESSAGE(stmt, etype, whatstring)                \
    try {                                                                 \
        stmt;                                                             \
        FAIL() << "Expected " << #etype << " with message \""             \
               << whatstring << "\"";                                     \
    } catch (const etype& e) {                                            \
        EXPECT_EQ(std::string(e.what()), std::string(whatstring));        \
    } catch (...) {                                                       \
        FAIL() << "Expected " << #etype << " with message \""             \
               << whatstring << "\"";                                     \
    }


TEST(StringFormatting, InterpolateValuesByIndex) {
    EXPECT_EQ(to_string_vec("#"), std::vector<std::string>({"#"}));
    EXPECT_EQ("$1" % to_string_vec("#"), "#");
    EXPECT_EQ("$1+$2" % to_string_vec("@", "@"), "@+@");
    EXPECT_EQ("$1A" % to_string_vec("@"), "@A");
    EXPECT_EQ("${1A}" % to_string_vec("1A", "VALUE"), "VALUE");
}

TEST(StringFormatting, InterpolateValuesByNames) {
    EXPECT_EQ("$name" % to_string_vec("name", "VALUE"), "VALUE");
    EXPECT_EQ("${name}" % to_string_vec("name", "VALUE"), "VALUE");
}
