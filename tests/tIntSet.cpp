#include <hstd/stdlib/IntSet.hpp>
#include <hstd/stdlib/charsets.hpp>
#include <gtest/gtest.h>

TEST(TestIntegralSetOperations, InitialSetContent) {
    CharSet s;
    CharSet other;
    // Default-initialized set does not contain any values and has
    // `.size()` zero
    EXPECT_EQ(s.size(), 0);
    // You can include values to the set using `.incl` method
    s.incl('a');
    // `.size()` shows the number of values included in the set
    EXPECT_EQ(s.size(), 1);
}

TEST(TestIntegralSetOperations, ContainsForSingleItem) {
    CharSet s;
    CharSet other;
    // Presence of specific element can be tested using `.contains()`
    // value
    EXPECT_FALSE(s.contains('c'));
    // Elements can be added
    s.incl('c');
    // Tested again
    EXPECT_TRUE(s.contains('c'));
    // Then excluded
    s.excl('c');
    // And then tested again, now for absence
    EXPECT_FALSE(s.contains('c'));
}

TEST(TestIntegralSetOperations, ContainsForSetOperations) {
    CharSet s;
    CharSet other;
    // You can check for subset relation as well. Default (empty)  sets
    // are subset of each other
    EXPECT_TRUE(s.contains(other));
    EXPECT_TRUE(other.contains(s));
    // Since they both have the same elements
    EXPECT_EQ(other.size(), 0);
    EXPECT_EQ(s.size(), 0);
    // After adding element to the set  this no longer holds
    s.incl('s');
    EXPECT_TRUE(s.contains(other));
    EXPECT_FALSE(other.contains(s));
    // You can test for subset relation using `<` operator: it tests
    // for proper subset
    EXPECT_TRUE(other < s);
    // You can also test for a regular subset operation, using `<=`
    // operator which is analogous to the `s.contains(other)`
    EXPECT_TRUE(other <= s);
    other.incl('s');
    // After including the same element in the set `<` no longer holds
    EXPECT_FALSE(other < s);
    // But regular subset check is ok
    EXPECT_TRUE(other <= s);
    // And it now works in both directions again
    EXPECT_TRUE(s <= other);
}

TEST(TestIntegralSetOperations, SetOperations) {
    CharSet s;
    CharSet other;
    EXPECT_EQ((s + other).size(), 0);
    EXPECT_EQ((s - other).size(), 0);
    EXPECT_TRUE(s < (s + CharSet{'1'}));
    EXPECT_TRUE(s < (s | CharSet{'1'}));
    EXPECT_TRUE(s == (s & CharSet{'1'}));
}

TEST(TestIntegralSetOperations, IntegerSetOperators) {
    IntSet<i8> s1{1_i8, 2_i8, 3_i8};
    IntSet<i8> s2{2_i8, 3_i8, 4_i8};
    IntSet<i8> s3{4_i8, 5_i8, 6_i8};
    IntSet<i8> empty;

    // Check that the union of s1 and s2 is {1, 2, 3, 4}
    EXPECT_EQ((s1 + s2), (IntSet<i8>{1_i8, 2_i8, 3_i8, 4_i8}));
    // Check that the intersection of s1 and s2 is {2, 3}
    EXPECT_EQ((s1 & s2), (IntSet<i8>{2_i8, 3_i8}));
    // Check that the difference between s1 and s2 is {1}
    EXPECT_EQ((s1 - s2), IntSet<i8>{1_i8});
    // Check that the symmetric difference between s1 and s2 is {1, 4}
    EXPECT_EQ((s1 ^ s2), (IntSet<i8>{1_i8, 4_i8}));
    // Check that the union of s1 and s3 is {1, 2, 3, 4, 5, 6}
    EXPECT_EQ((s1 + s3), (IntSet<i8>{1_i8, 2_i8, 3_i8, 4_i8, 5_i8, 6_i8}));
    // Check that the intersection of s1 and s3 is empty
    EXPECT_TRUE((s1 & s3).empty());
    // Check that the difference between s1 and s3 is {1, 2, 3}
    EXPECT_EQ((s1 - s3), s1);
    // Check that the symmetric difference between s1 and s3 is {1, 2, 3,
    // 4, 5, 6}
    EXPECT_EQ((s1 ^ s3), (s1 + s3));
    // Check that the union of empty and s1 is {1, 2, 3}
    EXPECT_EQ((empty + s1), s1);
    // Check that the intersection of empty and s1 is empty
    EXPECT_TRUE((empty & s1).empty());
    // Check that the difference between empty and s1 is empty
    EXPECT_TRUE((empty - s1).empty());
    // Check that the symmetric difference between empty and s1 is {1, 2,
    // 3}
    EXPECT_EQ((empty ^ s1), s1);
}
