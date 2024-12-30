#include <hstd/stdlib/Str.hpp>
#include <gtest/gtest.h>
#include <hstd/stdlib/strutils.hpp>
#include <hstd/stdlib/strformat.hpp>
#include <hstd/stdlib/ColText.hpp>


TEST(StringOperationsTest, StringViews) {
    Str  base{"test"};
    auto span = base.toSpan();
    EXPECT_EQ(span[0], base[0]);
    EXPECT_EQ(span.size(), base.size());
    EXPECT_EQ(span.size(), 4);
    EXPECT_EQ(base, Str(span));
}

TEST(StringOperationsTest, BasicOperations) {
    Str s1{"Hello"};
    Str s2{"World"};
    Str empty;

    EXPECT_TRUE(s1.starts_with("He"));
    EXPECT_FALSE(s1.starts_with("Wo"));
    EXPECT_TRUE(s1.ends_with("lo"));
    EXPECT_FALSE(s1.ends_with("or"));
    EXPECT_EQ(s1.size(), 5);
    EXPECT_FALSE(s1.empty());
    EXPECT_TRUE(empty.empty());
    EXPECT_EQ(s1[1], 'e');
    // String slices are inclusive
    EXPECT_EQ((s1[Slice<int>{1, 3}]), std::string("ell"));
    EXPECT_EQ((s1 + s2), std::string("HelloWorld"));
}

TEST(StringOperationsTest, StringMutations) {
    Str s1{"01234"};
    Str s2{"World"};
    Str empty;

    // Change the first character of s1 to 'J'
    s1[0] = '!';
    EXPECT_EQ(s1, "!1234");
}

TEST(StringOperationsTest, StringApi) {
    Str pref1 = Str("?$??").dropPrefix("?");
    EXPECT_EQ(pref1, "$??");

    Str pref2 = Str("XXXX").dropPrefix("YYY");
    EXPECT_EQ(pref2, "XXXX");

    Str suff1 = Str("??$?").dropSuffix("?");
    EXPECT_EQ(suff1, "??$");

    Str suff2 = Str("XXXX").dropSuffix("YYY");
    EXPECT_EQ(suff2, "XXXX");

    EXPECT_EQ(Str("0").at(0), '0');
    EXPECT_THROW(Str("0").at(120), std::out_of_range);

    EXPECT_EQ((Str("").replaceAll("0", "1")), Str(""));
    EXPECT_EQ((Str("0").replaceAll("0", "1")), Str("1"));
    EXPECT_EQ((Str("0000").replaceAll("0", "1")), Str("1111"));
    EXPECT_EQ((Str("0000").replaceAll("000", "1")), Str("10"));
    EXPECT_EQ(
        (Str("0-0-0").split("-")),
        (Vec<Str>{Str("0"), Str("0"), Str("0")}));
    EXPECT_EQ(
        (Str("0-0-0").split('-')),
        (Vec<Str>{Str("0"), Str("0"), Str("0")}));
    EXPECT_EQ(Str("1").repeated(4), Str("1111"));

    EXPECT_EQ(Str("1").toInt(), 1);
    EXPECT_FLOAT_EQ(Str("1").toFloat(), 1);
    EXPECT_FLOAT_EQ(Str("1").toDouble(), 1);
    EXPECT_EQ(Str("0").at(1_B), '0');
}


TEST(StringOperationsTest, UnicodeLength) {
    {
        Str a = "añyóng";
        EXPECT_EQ(a.runeLen(), 6);
        EXPECT_NE(a.length(), 6);
        EXPECT_EQ(a.length(), 8);
    }
    {
        Str b = "Hello";
        EXPECT_EQ(b.runeLen(), 5);
        EXPECT_EQ(b.length(), 5);
    }
    {
        Str c = "";
        EXPECT_EQ(c.runeLen(), 0);
        EXPECT_EQ(c.length(), 0);
    }
}

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

    {}
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
    EXPECT_EQ("$$" % to_string_vec("1"), "$");
    EXPECT_EQ("$1" % to_string_vec("1", "9"), "1");
    EXPECT_EQ("${1}" % to_string_vec("1", "9"), "1");
    EXPECT_EQ("${-1}" % to_string_vec("1", "9"), "9");
    EXPECT_THROW("$-1" % to_string_vec("1", "9"), FormatStringError);
    EXPECT_EQ("$2" % to_string_vec("1", "9"), "9");
    EXPECT_EQ("$#" % to_string_vec("1", "9"), "1");
    EXPECT_THROW("$9" % to_string_vec("1"), FormatStringError);
}

TEST(StringFormatting, InterpolateValuesByNames) {
    EXPECT_EQ("$name" % to_string_vec("name", "VALUE"), "VALUE");
    EXPECT_EQ("${name}" % to_string_vec("name", "VALUE"), "VALUE");
    EXPECT_THROW(
        "${missing}" % to_string_vec("provided", "VALUE"),
        FormatStringError);
}


TEST(Strutils, Mappings) {
    EXPECT_EQ(visibleName('\x00').second, "[NUL]");
    EXPECT_EQ(visibleName('\x00').first.runeLen(), 1);
    EXPECT_EQ(indent("", 0), "");
    EXPECT_EQ(indent("", 2), "");
    EXPECT_EQ(indent("-", 2), "  -");
    EXPECT_EQ(normalize("aAz+1!"), std::string("aaz1"));
    EXPECT_EQ(left_aligned("", 2), "  ");
    EXPECT_EQ(left_aligned("X", 2), "X ");
    EXPECT_EQ(right_aligned("X", 2), " X");
    EXPECT_EQ(right_aligned("", 2), "  ");
}


TEST(Hshow, Instantiations) {
    auto dbg = [&]<typename T>(T const& v) {
        std::cout << fmt1(v) << std::endl;
        std::cout << hshow1(v).toString(true) << std::endl;
    };

    dbg(12);
    dbg("test");
}
