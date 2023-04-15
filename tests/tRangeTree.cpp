#include <gtest/gtest.h>
#include <QString>
#include <QDebug>
#include <hstd/stdlib/RangeTree.hpp>
#include <hstd/stdlib/Debug.hpp>
#include <hstd/stdlib/Map.hpp>
#include <lexbase/Token.hpp>

bool operator==(Slice<int> lhs, Slice<int> rhs) {
    return lhs.operator==(rhs);
}

TEST(RangeTreeTest, Queries) {
    RangeTree<int> tree{
        Vec<Slice<int>>{slice(1, 5), slice(6, 8), slice(10, 12)}};

    // Query within range
    EXPECT_EQ(tree.query(3).value(), slice(1, 5));
    EXPECT_EQ(tree.query(7).value(), slice(6, 8));
    EXPECT_EQ(tree.query(11).value(), slice(10, 12));

    // Query outside range
    EXPECT_FALSE(tree.query(0).has_value());
    EXPECT_FALSE(tree.query(9).has_value());
    EXPECT_FALSE(tree.query(13).has_value());

    // Query on range boundary
    EXPECT_EQ(tree.query(1).value(), slice(1, 5));
    EXPECT_EQ(tree.query(5).value(), slice(1, 5));
    EXPECT_EQ(tree.query(6).value(), slice(6, 8));
    EXPECT_EQ(tree.query(8).value(), slice(6, 8));
    EXPECT_EQ(tree.query(10).value(), slice(10, 12));
    EXPECT_EQ(tree.query(12).value(), slice(10, 12));

    RangeTree<int> overlapping(
        Vec<Slice<int>>{slice(1, 5), slice(3, 8), slice(7, 12)});

    // Query within range
    EXPECT_EQ(overlapping.query(3).value(), slice(3, 8));
    EXPECT_EQ(overlapping.query(7).value(), slice(3, 8));
    EXPECT_EQ(overlapping.query(10).value(), slice(7, 12));

    // Query outside range
    EXPECT_FALSE(overlapping.query(0).has_value());
    EXPECT_FALSE(overlapping.query(13).has_value());

    // Query on range boundary
    EXPECT_EQ(overlapping.query(1).value(), slice(1, 5));
    EXPECT_EQ(overlapping.query(5).value(), slice(3, 8));
    EXPECT_EQ(overlapping.query(7).value(), slice(3, 8));
    EXPECT_EQ(overlapping.query(12).value(), slice(7, 12));
}

TEST(LineAndColumnInfoTest, RangeTree) {
    auto rangeInfo = [](QString const& text) -> LineColInfo {
        return LineColInfo(text);
    };

    // Line range information from empty string
    { auto lineInfo = rangeInfo(""); }

    // Line range information
    {
        auto info = rangeInfo("0");
        EXPECT_EQ(info.whichLine(0), 0);
        EXPECT_EQ(info.whichColumn(0), 0);
    }

    // Two lines
    {
        auto info = rangeInfo("0123\n576");
        EXPECT_EQ(info.whichLine(0), 0);
        EXPECT_EQ(info.whichColumn(1), 1);
        EXPECT_EQ(info.whichLine(5), 1);
        EXPECT_EQ(info.whichColumn(5), 0);
    }
}
