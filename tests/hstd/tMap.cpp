#include "hstd/stdlib/Debug.hpp"
#include <gtest/gtest.h>
#include <hstd/wrappers/hstd_extra/bimap_wrap.hpp>

TEST(BimapTest, AddUnique) {
    Unordered1to1Bimap<int, std::string> bimap;
    bimap.add_unique(1, "one");
    EXPECT_TRUE(bimap.contains_left(1));
    EXPECT_TRUE(bimap.contains_right("one"));
    EXPECT_EQ(bimap.at_right(1), "one");
    EXPECT_EQ(bimap.at_left("one"), 1);

    EXPECT_THROW(bimap.add_unique(1, "one"), std::runtime_error);
    EXPECT_THROW(bimap.add_unique(2, "one"), std::runtime_error);
}


TEST(BimapTest, Contains) {
    Unordered1to1Bimap<int, std::string> bimap;
    bimap.add_unique(1, "one");
    EXPECT_TRUE(bimap.contains_left(1));
    EXPECT_FALSE(bimap.contains_left(2));
    EXPECT_TRUE(bimap.contains_right("one"));
    EXPECT_FALSE(bimap.contains_right("two"));
}


TEST(BimapTest, LeftKeysAndRightKeys) {
    Unordered1to1Bimap<int, std::string> bimap;
    bimap.add_unique(1, "one");
    bimap.add_unique(2, "two");

    auto leftKeys  = bimap.left_keys();
    auto rightKeys = bimap.right_keys();

    EXPECT_EQ(leftKeys.size(), 2);
    EXPECT_EQ(rightKeys.size(), 2);
    EXPECT_NE(
        std::find(leftKeys.begin(), leftKeys.end(), 1), leftKeys.end());
    EXPECT_NE(
        std::find(rightKeys.begin(), rightKeys.end(), "one"),
        rightKeys.end());
}
