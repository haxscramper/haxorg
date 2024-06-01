#include <gtest/gtest.h>
#include <string>
#include <absl/log/log.h>
#include <hstd/stdlib/RangeTree.hpp>
#include <hstd/stdlib/Debug.hpp>
#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/RangeSegmentation.hpp>

bool operator==(Slice<int> lhs, Slice<int> rhs) {
    return lhs.operator==(rhs);
}

TEST(RangeAlgorithmsTest, Queries) {
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


TEST(RangeAlgorithmsTest, EmptyGroups) {
    // Test case: No segments provided
    std::vector<SequenceSegmentGroup> groups;
    auto result = annotateSequence(groups, 0, 10);
    EXPECT_TRUE(result.empty());
}

TEST(RangeAlgorithmsTest, SingleSegmentGroupSingleSegment) {
    // Test case:
    // Group1:  |-----|
    SequenceSegment      segment{1, 0, 5};
    SequenceSegmentGroup group{1, {segment}};
    auto                 result = annotateSequence({group}, 0, 5);
    // Checking annotation for the segment [0, 5]
    // Expected:
    // Annotated:  |-----|
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0].first, 0);
    EXPECT_EQ(result[0].last, 5);
    ASSERT_EQ(result[0].annotations.size(), 1);
    EXPECT_EQ(result[0].annotations[0].groupKind, 1);
    EXPECT_EQ(result[0].annotations[0].segmentKind, 1);
}

TEST(RangeAlgorithmsTest, MultipleSegmentGroups) {
    // Test case:
    // Group1:  |-----|
    // Group2:      |-----|
    SequenceSegment      segment1{.kind = 1, .first = 0, .last = 5};
    SequenceSegmentGroup group1{1, {segment1}};
    SequenceSegment      segment2{.kind = 2, .first = 3, .last = 7};
    SequenceSegmentGroup group2{2, {segment2}};
    auto result = annotateSequence({group1, group2}, 0, 10);
    // Checking annotations for segments [0, 2], [3, 5], [6, 7]
    // Expected:
    // Annotated:  |---|  |---| |---|
    ASSERT_EQ(result.size(), 3);

    // Annotated segment [0, 2]
    ASSERT_EQ(result[0].first, 0);
    ASSERT_EQ(result[0].last, 2);
    ASSERT_EQ(result[0].annotations.size(), 1);
    EXPECT_EQ(result[0].annotations[0].groupKind, 1);
    EXPECT_EQ(result[0].annotations[0].segmentKind, 1);

    // Annotated segment [3, 5]
    ASSERT_EQ(result[1].first, 3);
    ASSERT_EQ(result[1].last, 5);
    ASSERT_EQ(result[1].annotations.size(), 2);
    EXPECT_EQ(result[1].annotations[0].groupKind, 1);
    EXPECT_EQ(result[1].annotations[0].segmentKind, 1);
    EXPECT_EQ(result[1].annotations[1].groupKind, 2);
    EXPECT_EQ(result[1].annotations[1].segmentKind, 2);

    // Annotated segment [6, 7]
    ASSERT_EQ(result[2].first, 6);
    ASSERT_EQ(result[2].last, 7);
    ASSERT_EQ(result[2].annotations.size(), 1);
    EXPECT_EQ(result[2].annotations[0].groupKind, 2);
    EXPECT_EQ(result[2].annotations[0].segmentKind, 2);
}

TEST(RangeAlgorithmsTest, OverlappingSegments) {
    // Test case:
    // Group1:  |-----|
    // Group2:      |---------|
    SequenceSegment      segment1{1, 0, 5};
    SequenceSegmentGroup group1{1, {segment1}};
    SequenceSegment      segment2{1, 4, 9};
    SequenceSegmentGroup group2{2, {segment2}};
    auto                 result = annotateSequence({group1, group2}, 0, 9);
    // Checking annotations for segments [0, 3], [4, 5], [6, 9]
    // Expected:
    // Annotated:  |---|  |---|  |-----|
    ASSERT_EQ(result.size(), 3);

    // Annotated segment [0, 3]
    ASSERT_EQ(result[0].first, 0);
    ASSERT_EQ(result[0].last, 3);
    ASSERT_EQ(result[0].annotations.size(), 1);
    EXPECT_EQ(result[0].annotations[0].groupKind, 1);
    EXPECT_EQ(result[0].annotations[0].segmentKind, 1);

    // Annotated segment [4, 5]
    ASSERT_EQ(result[1].first, 4);
    ASSERT_EQ(result[1].last, 5);
    ASSERT_EQ(result[1].annotations.size(), 2);
    EXPECT_EQ(result[1].annotations[0].groupKind, 1);
    EXPECT_EQ(result[1].annotations[0].segmentKind, 1);
    EXPECT_EQ(result[1].annotations[1].groupKind, 2);
    EXPECT_EQ(result[1].annotations[1].segmentKind, 1);

    // Annotated segment [6, 9]
    ASSERT_EQ(result[2].first, 6);
    ASSERT_EQ(result[2].last, 9);
    ASSERT_EQ(result[2].annotations.size(), 1);
    EXPECT_EQ(result[2].annotations[0].groupKind, 2);
    EXPECT_EQ(result[2].annotations[0].segmentKind, 1);
}
