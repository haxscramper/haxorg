#include <hstd/stdlib/Vec.hpp>
#include <gtest/gtest.h>
#include <hstd/stdlib/Ranges.hpp>

template <typename T>
class IntVecTypedTest : public ::testing::Test {};
using IntVecTestTypes = ::testing::Types<Vec<int>, SmallVec<int, 10>>;
TYPED_TEST_SUITE(IntVecTypedTest, IntVecTestTypes);

template <typename T>
class StrVecTypedTest : public ::testing::Test {};
using StrVecTestTypes = ::testing::
    Types<Vec<std::string>, SmallVec<std::string, 10>>;
TYPED_TEST_SUITE(StrVecTypedTest, StrVecTestTypes);

TEST(BackwardsIndexTest, BackwardsIndexFormat) {
    std::string f1 = std::format("{}", 1_B);
    ASSERT_EQ(f1, "^1");
}

TYPED_TEST(IntVecTypedTest, Formatter) {
    EXPECT_EQ((std::format("{}", TypeParam{})), "[]");
    EXPECT_EQ((std::format("{}", TypeParam{1})), "[1]");
    EXPECT_EQ((std::format("{}", TypeParam{1, 2})), "[1, 2]");
}

TYPED_TEST(StrVecTypedTest, Formatter) {
    TypeParam v{
        std::string{"first"},
        std::string{"second"},
    };
    std::string fmt = std::format("{}", v);
    EXPECT_EQ(fmt, "[first, second]");
}

TEST(VectorTest, ContainsFind) {
    EXPECT_EQ(Vec<int>{}.indexOf(1), -1);
    EXPECT_EQ((Vec<int>{1, 2}.indexOf(1)), 0);
    EXPECT_EQ((Vec<int>{0, 1}.indexOf(2)), -1);
}

TYPED_TEST(IntVecTypedTest, SliceAndIndexingOperators) {
    TypeParam v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Test slice operator with positive indices
    std::span<int> slice1 = v[slice(3, 5)];
    ASSERT_EQ(slice1.size(), 3);
    for (int i = 0; i < 3; ++i) { EXPECT_EQ(slice1[i], v[i + 3]); }

    // Test slice operator with backwards indices
    std::span<int> slice2 = v[slice(3, 3_B)];
    ASSERT_EQ(slice2.size(), 5);
    for (int i = 0; i < 3; ++i) { EXPECT_EQ(slice2[i], v[i + 3]); }

    // Test slice operator with out-of-bounds indices, raise is
    // guaranteed
    // EXPECT_THROW(v.at(slice(0, 11)), std::out_of_range);
    // EXPECT_THROW(v.at(slice(12, 14)), std::out_of_range);
    // EXPECT_THROW(v.at(slice(1, 20_B)), std::out_of_range);

    // Test indexing operator with positive index
    EXPECT_EQ(v[3], 3);

    EXPECT_EQ(v[3_B], 7);
    EXPECT_EQ(v[v.size() - 3], 7);

    EXPECT_THROW((void)v.at(10), out_of_range_error);
    EXPECT_THROW(v.at(11_B), out_of_range_error);
}

TYPED_TEST(IntVecTypedTest, VectorAlloc) {
    {
        std::vector<int> v{0, 0, 0, 0, 0};
        CHECK(v.data() != nullptr);
        EXPECT_EQ(v[0], 0);
    }
    {
        TypeParam v{0, 0, 0, 0, 0};
        CHECK(v.data() != nullptr);
        EXPECT_EQ(v[0], 0);
    }
}

TYPED_TEST(IntVecTypedTest, SpanViews) {
    {
        const TypeParam v{0, 1, 2, 3, 4};
        std::span<int>  span = v.at(slice(1, 1));
        EXPECT_EQ(span[0], 1);
        EXPECT_EQ(span[1], 2);
    }
    {
        TypeParam v{0, 0, 0, 0, 0};
        // Test modification using slice operator
        std::span<int> span = v[slice(1, 3)];
        CHECK(span.data() != nullptr);
        for (int& x : span) { x = 42; }
        EXPECT_EQ(v[0], 0);
        EXPECT_EQ(v[1], 42);
        EXPECT_EQ(v[2], 42);
        EXPECT_EQ(v[3], 42);
        EXPECT_EQ(v[4], 0);

        // Test modification using indexing operator
        v[1] = 0;
        v[2] = 0;
        v[3] = 0;
        EXPECT_EQ(v[0], 0);
        EXPECT_EQ(v[1], 0);
        EXPECT_EQ(v[2], 0);
        EXPECT_EQ(v[3], 0);
        EXPECT_EQ(v[4], 0);
    }
}

TYPED_TEST(IntVecTypedTest, Indexing) {
    using V = TypeParam;
    {
        EXPECT_THROW(TypeParam{}.back(), out_of_range_error);
        EXPECT_EQ(TypeParam{1}.back(), 1);
        EXPECT_EQ((TypeParam{2, 1}.back()), 1);

        EXPECT_THROW(TypeParam{}.pop_back(), out_of_range_error);
        EXPECT_THROW(TypeParam{}.pop_back_v(), out_of_range_error);
    }

    auto v = V{1, 2};
    EXPECT_TRUE(v.has(0));
    EXPECT_FALSE(v.has(90));
    EXPECT_TRUE(v.has(1_B));
    EXPECT_FALSE(v.has(19_B));

    EXPECT_TRUE(v.get(0).has_value());
    EXPECT_FALSE(v.get(90).has_value());
    EXPECT_TRUE(v.get(1_B).has_value());
    EXPECT_FALSE(v.get(19_B).has_value());

    EXPECT_EQ(v.get(0).value(), 1);
    EXPECT_EQ(v.get(1_B).value(), 2);

    EXPECT_EQ(v.index(1_B), 1);
    EXPECT_EQ(v.index(2_B), 0);
}

TYPED_TEST(IntVecTypedTest, ResizeAt) {
    TypeParam vec;
    EXPECT_EQ(vec.size(), 0);
    vec.resize_at(0) = 12;
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec.at(0), 12);
    vec.resize_at(4) = 89;
    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec.at(0), 12);
    EXPECT_EQ(vec.at(1), 0);
    EXPECT_EQ(vec.at(2), 0);
    EXPECT_EQ(vec.at(4), 89);


    vec.resize_at(8, 19) = 189;
    EXPECT_EQ(vec.size(), 9);
    EXPECT_EQ(vec.at(0), 12);
    EXPECT_EQ(vec.at(1), 0);
    EXPECT_EQ(vec.at(2), 0);
    EXPECT_EQ(vec.at(4), 89);
    EXPECT_EQ(vec.at(5), 19);
    EXPECT_EQ(vec.at(6), 19);
    EXPECT_EQ(vec.at(7), 19);
    EXPECT_EQ(vec.at(8), 189);
}

TYPED_TEST(IntVecTypedTest, FindElement) {
    TypeParam vec{0, 1, 2, 3, 9};
    EXPECT_EQ(vec.indexOf(0), 0);
    EXPECT_EQ(vec.indexOf(90), -1);
    EXPECT_EQ(vec.indexOf(9), 4);
    EXPECT_TRUE(vec.contains(0));
    EXPECT_TRUE(vec.contains(1));
    EXPECT_FALSE(vec.contains(99));
}

TYPED_TEST(StrVecTypedTest, FindElement) {
    Vec<std::string> vec{"zero", "one", "two", "three", "nine"};
    EXPECT_EQ(vec.indexOf("zero"), 0);
    EXPECT_EQ(vec.indexOf("one"), 1);
    EXPECT_EQ(vec.indexOf("missing"), -1);
    EXPECT_TRUE(vec.contains("zero"));
    EXPECT_TRUE(vec.contains("nine"));
    EXPECT_FALSE(vec.contains("missing"));
}

TEST(VectorTest, VectorSplicing) {
    using V = Vec<int>;

    {
        auto v = V::Splice(1, 2, 3);
        EXPECT_EQ(v.size(), 3);
        EXPECT_EQ(v.at(0), 1);
        EXPECT_EQ(v.at(2), 3);
    }

    {
        auto v = V::Splice(1, V{2, 3, 4});
        EXPECT_EQ(v.size(), 4);
        EXPECT_EQ(v.at(0), 1);
        EXPECT_EQ(v.at(1), 2);
        EXPECT_EQ(v.at(3), 4);
    }

    {
        auto tmp = V{1, 2, 3};
        auto v   = V::Splice(1, tmp | rv::transform([](int arg) -> int {
                                  return arg + 1;
                              }));

        EXPECT_EQ(v.size(), 4);
        EXPECT_EQ(v.at(0), 1);
        EXPECT_EQ(v.at(1), 2);
        EXPECT_EQ(v.at(3), 4);
    }
}


TYPED_TEST(IntVecTypedTest, VectorCompare) {
    using V = TypeParam;
    EXPECT_EQ((V{1, 2}), (V{1, 2}));
    EXPECT_NE((V{1, 2}), (V{1, 4}));
    EXPECT_NE((V{1, 2}), (V{1}));
    EXPECT_EQ((Vec<char>{'1', '2'}), std::string{"12"});
}

TYPED_TEST(IntVecTypedTest, VectorFormatting) {
    EXPECT_EQ(fmt1(TypeParam{1, 2}), std::string{"[1, 2]"});
    EXPECT_EQ(fmt1(TypeParam{}), std::string{"[]"});
    EXPECT_EQ(fmt1(std::vector<int>{1, 2}), std::string{"[1, 2]"});
    EXPECT_EQ(fmt1(std::vector<int>{}), std::string{"[]"});
}
