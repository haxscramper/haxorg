#include <hstd/stdlib/Str.hpp>
#include <gtest/gtest.h>


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

    // FIXME enable exceptions
    // try {
    //     // Try to change the first character of empty to 'X'
    //     empty.at(0);
    //     FAIL() << "Expected std::out_of_range";
    // } catch (std::out_of_range& ex) {
    //     // Out of range error for empty string access
    // }

    // try {
    //     // Try to change the last two characters of empty to "zz" using
    //     // the slice operator
    //     empty.at(Slice<int>{1, 2});
    //     FAIL() << "Expected std::out_of_range";
    // } catch (std::out_of_range& ex) {
    //     // Out of range error for empty string access
    // }
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
