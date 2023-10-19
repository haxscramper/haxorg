#include <hstd/stdlib/Vec.hpp>
#include <gtest/gtest.h>

TEST(VectorTest, SliceAndIndexingOperators) {
    Vec<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Test slice operator with positive indices
    std::span<int> slice1 = v[slice(3, 5)];
    ASSERT_EQ(slice1.size(), 3);
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(slice1[i], v[i + 3]);
    }

    // Test slice operator with backwards indices
    std::span<int> slice2 = v[slice(3, 3_B)];
    ASSERT_EQ(slice2.size(), 5);
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(slice2[i], v[i + 3]);
    }

    // Test slice operator with out-of-bounds indices, raise is
    // guaranteed
    // EXPECT_THROW(v.at(slice(0, 11)), std::out_of_range);
    // EXPECT_THROW(v.at(slice(12, 14)), std::out_of_range);
    // EXPECT_THROW(v.at(slice(1, 20_B)), std::out_of_range);

    // Test indexing operator with positive index
    EXPECT_EQ(v[3], 3);

    EXPECT_EQ(v[3_B], 7);
    EXPECT_EQ(v[v.size() - 3], 7);

    EXPECT_THROW(v.at(10), std::out_of_range);
    EXPECT_THROW(v.at(11_B), std::out_of_range);
}

TEST(VectorTest, VectorAlloc) {
    {
        std::vector<int> v{0, 0, 0, 0, 0};
        CHECK(v.data() != nullptr);
        EXPECT_EQ(v[0], 0);
    }
    {
        Vec<int> v{0, 0, 0, 0, 0};
        CHECK(v.data() != nullptr);
        EXPECT_EQ(v[0], 0);
    }
}

TEST(VectorTest, EditDataViaSpanView) {
    Vec<int> v{0, 0, 0, 0, 0};

    // Test modification using slice operator
    std::span<int> span = v[slice(1, 3)];
    CHECK(span.data() != nullptr);
    for (int& x : span) {
        x = 42;
    }
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
