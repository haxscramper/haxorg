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

    EXPECT_TRUE(s1.startsWith("He"));
    EXPECT_FALSE(s1.startsWith("Wo"));
    EXPECT_TRUE(s1.endsWith("lo"));
    EXPECT_FALSE(s1.endsWith("or"));
    EXPECT_EQ(s1.size(), 5);
    EXPECT_FALSE(s1.empty());
    EXPECT_TRUE(empty.empty());
    EXPECT_EQ(s1[1], 'e');
    // String slices are inclusive
    EXPECT_EQ((s1[Slice<int>{1, 3}]), QString("ell"));
    EXPECT_EQ((s1 + s2), QString("HelloWorld"));
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
