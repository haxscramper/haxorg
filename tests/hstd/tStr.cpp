#include <hstd/stdlib/Str.hpp>
#include <gtest/gtest.h>
#include <hstd/stdlib/strutils.hpp>
#include <hstd/stdlib/ColText.hpp>
#include <hstd/stdlib/ColTextHShow.hpp>

#include "../common.hpp"

using namespace hstd;

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


struct DescField {
    int                    f1;
    int                    f2;
    std::string            f3;
    char                   f4 = 'q';
    std::vector<DescField> sub;

    DESC_FIELDS(DescField, (f1, f2, f3, f4, sub));
};

TEST(Hshow, Instantiations) {
    auto dbg = [&]<typename T>(T const& v) {
        std::cout << fmt1(v) << std::endl;
        std::cout << hshow1(v).toString(true) << std::endl;
    };

    dbg(12);
    dbg("test");
    dbg(Vec<int>{123, 33});
    dbg(Vec<std::string>{"123", "33"});
    dbg(DescField{.sub = {DescField{}}});
}


TEST(WrapTextTest, SingleShortWord) {
    Vec<Str> words  = {"Hello"};
    Str      result = wrap_text(words, 10, false);
    EXPECT_EQ(result.toBase(), "Hello");
}

TEST(WrapTextTest, MultipleShortWordsSingleLine) {
    Vec<Str> words  = {"Hello", "world"};
    Str      result = wrap_text(words, 20, false);
    EXPECT_EQ(result.toBase(), "Hello world");
}

TEST(WrapTextTest, WrapWordsToMultipleLines) {
    Vec<Str> words = {"This", "is", "a", "test", "of", "text", "wrapping"};
    Str      result = wrap_text(words, 10, false);
    EXPECT_EQ(result.toBase(), "This is a\ntest of\ntext\nwrapping");
}

TEST(WrapTextTest, JustifiedText) {
    Vec<Str> words = {
        "This", "is", "a", "test", "of", "justified", "text"};
    Str result = wrap_text(words, 20, true);
    EXPECT_EQ(
        result.toBase(), "This  is  a  test of\njustified       text");
}

TEST(WrapTextTest, LastLineNotJustified) {
    Vec<Str> words  = {"One", "last", "line", "example", "here"};
    Str      result = wrap_text(words, 15, true);
    EXPECT_EQ(result.toBase(), "One  last  line\nexample    here");
}

TEST(WrapTextTest, WordsExceedingMaxWidth) {
    Vec<Str> words  = {"Extraordinarily", "long", "word", "here"};
    Str      result = wrap_text(words, 10, false);
    EXPECT_EQ(result.toBase(), "Extraordinarily\nlong word\nhere");
}

TEST(WrapTextTest, EmptyInput) {
    Vec<Str> words  = {};
    Str      result = wrap_text(words, 10, false);
    EXPECT_EQ(result.toBase(), "");
}

TEST(WrapTextTest, SingleWordExceedingMaxWidth) {
    Vec<Str> words  = {"Supercalifragilisticexpialidocious"};
    Str      result = wrap_text(words, 10, false);
    EXPECT_EQ(result.toBase(), "Supercalifragilisticexpialidocious");
}
