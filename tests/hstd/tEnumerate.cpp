#include <hstd/stdlib/Enumerate.hpp>
#include <gtest/gtest.h>

TEST(EnumerateTests, BasicEnumeration) {
    std::vector<int> v            = {1, 2, 3, 4};
    size_t           expected_idx = 0;
    for (auto const& item : enumerator(v)) {
        EXPECT_EQ(item.index(), expected_idx);
        EXPECT_EQ(item.value(), v[expected_idx]);
        ++expected_idx;
    }
    EXPECT_EQ(expected_idx, v.size());
}

TEST(EnumerateTests, SkipFirstElements) {
    std::vector<int> v            = {1, 2, 3, 4};
    size_t           expected_idx = 2;
    for (auto const& item : enumerator(v).skip_first(2)) {
        EXPECT_EQ(item.base_index(), expected_idx);
        EXPECT_EQ(item.index(), expected_idx - 2);
        EXPECT_EQ(item.value(), v[expected_idx]);
        ++expected_idx;
    }
    EXPECT_EQ(expected_idx, v.size());
}

TEST(EnumerateTests, SkipLastElements) {
    std::vector<int> v            = {1, 2, 3, 4};
    size_t           expected_idx = 0;
    for (auto const& item : enumerator(v).skip_last(2)) {
        EXPECT_EQ(item.index(), expected_idx);
        EXPECT_EQ(item.value(), v[expected_idx]);
        ++expected_idx;
    }
    EXPECT_EQ(expected_idx, v.size() - 2);
}

TEST(EnumerateTests, EmptyContainer) {
    std::vector<int> v;
    for (auto const& item : enumerator(v)) {
        FAIL() << "This should not be executed, the container is empty.";
    }
}

TEST(EnumerateTests, SkipMoreElementsThanSize) {
    std::vector<int> v = {1, 2, 3};
    for (auto const& item : enumerator(v).skip_first(5)) {
        FAIL() << "This should not be executed, we are skipping more "
                  "elements than the container size.";
    }
}

TEST(EnumerateTests, PositionPredicates) {
    std::vector<int> v{0, 1, 2};
    auto             e  = enumerator(v);
    auto             it = e.begin();
    {
        auto n = *it;
        EXPECT_EQ(n.base_index(), 0);
        EXPECT_EQ(n.is_first(), true);
        EXPECT_EQ(n.is_last(), false);
        EXPECT_EQ(n.value(), 0);
    }

    {
        ++it;
        auto n = *it;
        EXPECT_EQ(n.base_index(), 1);
        EXPECT_EQ(n.is_first(), false);
        EXPECT_EQ(n.is_last(), false);
        EXPECT_EQ(n.value(), 1);
    }

    {
        ++it;
        auto n = *it;
        EXPECT_EQ(n.base_index(), 2);
        EXPECT_EQ(n.is_first(), false);
        EXPECT_EQ(n.is_last(), true);
        EXPECT_EQ(n.value(), 2);
    }
}

TEST(EnumerateTests, PositionPredicatesWithSkip) {
    std::vector<int> v{0, 1, 2};
    auto             e  = enumerator(v).skip_first(1);
    auto             it = e.begin();

    {
        auto n = *it;
        EXPECT_EQ(n.base_index(), 1);
        EXPECT_EQ(n.index(), 0);
        EXPECT_EQ(n.is_first(), true);
        EXPECT_EQ(n.is_last(), false);
        EXPECT_EQ(n.value(), 1);
    }

    {
        ++it;
        auto n = *it;
        EXPECT_EQ(n.base_index(), 2);
        EXPECT_EQ(n.index(), 1);
        EXPECT_EQ(n.is_first(), false);
        EXPECT_EQ(n.is_last(), true);
        EXPECT_EQ(n.value(), 2);
    }
}
