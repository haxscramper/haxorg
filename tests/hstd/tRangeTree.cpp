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
    Vec<SequenceSegmentGroup> groups;
    auto                      result = annotateSequence(groups, 0, 10);
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
    SequenceSegmentGroup group1{.kind = 1, .segments = {segment1}};
    SequenceSegment      segment2{.kind = 2, .first = 3, .last = 7};
    SequenceSegmentGroup group2{.kind = 2, .segments = {segment2}};
    auto result = annotateSequence({group1, group2}, 0, 10);
    // Checking annotations for segments [0, 2], [3, 5], [6, 7]
    // Expected:
    // Annotated:  |---|  |---| |---|
    ASSERT_EQ(result.size(), 3);

    // Annotated segment [0, 2]
    ASSERT_EQ(result[0].first, 0);
    ASSERT_EQ(result[0].last, 2);
    ASSERT_EQ(result[0].annotations.size(), 1);
    EXPECT_TRUE(result[0].isAnnotatedWith(1, 1));

    // Annotated segment [3, 5]
    ASSERT_EQ(result[1].first, 3);
    ASSERT_EQ(result[1].last, 5);
    ASSERT_EQ(result[1].annotations.size(), 2);
    EXPECT_TRUE(result[1].isAnnotatedWith(1, 1));
    EXPECT_TRUE(result[1].isAnnotatedWith(2, 2));

    // Annotated segment [6, 7]
    ASSERT_EQ(result[2].first, 6);
    ASSERT_EQ(result[2].last, 7);
    ASSERT_EQ(result[2].annotations.size(), 1);
    EXPECT_TRUE(result[2].isAnnotatedWith(2, 2));
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
    EXPECT_EQ(result[0].isAnnotatedWith(1, 1), 1);

    // Annotated segment [4, 5]
    ASSERT_EQ(result[1].first, 4);
    ASSERT_EQ(result[1].last, 5);
    ASSERT_EQ(result[1].annotations.size(), 2);
    EXPECT_TRUE(result[1].isAnnotatedWith(1, 1));
    EXPECT_TRUE(result[1].isAnnotatedWith(2, 1));

    // Annotated segment [6, 9]
    ASSERT_EQ(result[2].first, 6);
    ASSERT_EQ(result[2].last, 9);
    ASSERT_EQ(result[2].annotations.size(), 1);
    EXPECT_TRUE(result[2].isAnnotatedWith(2, 1));
}


TEST(RangeAlgorithmsTest, FullyOverlappingSegments) {
    // Test case:
    // Group1:  |-----------|
    // Group2:  |-----------|
    SequenceSegment      segment1{.kind = 1, .first = 0, .last = 9};
    SequenceSegmentGroup group1{.kind = 1, .segments = {segment1}};
    SequenceSegment      segment2{.kind = 2, .first = 0, .last = 9};
    SequenceSegmentGroup group2{.kind = 2, .segments = {segment2}};
    auto                 result = annotateSequence({group1, group2}, 0, 9);
    // Expected:
    // Annotated:  |-----------|
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0].first, 0);
    EXPECT_EQ(result[0].last, 9);
    ASSERT_EQ(result[0].annotations.size(), 2);
    EXPECT_TRUE(result[0].isAnnotatedWith(1, 1));
    EXPECT_TRUE(result[0].isAnnotatedWith(2, 2));
}

TEST(RangeAlgorithmsTest, SegmentSpansWholeRange) {
    // Test case:
    // Group1:  |-----------|
    SequenceSegment      segment{.kind = 1, .first = 0, .last = 9};
    SequenceSegmentGroup group{.kind = 1, .segments = {segment}};
    auto                 result = annotateSequence({group}, 0, 9);
    // Expected:
    // Annotated:  |-----------|
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0].first, 0);
    EXPECT_EQ(result[0].last, 9);
    ASSERT_EQ(result[0].annotations.size(), 1);
    EXPECT_TRUE(result[0].isAnnotatedWith(1, 1));
}

TEST(RangeAlgorithmsTest, SegmentLargerThanRange) {
    // Test case:
    // Group1:  |-----------------|
    SequenceSegment      segment{.kind = 1, .first = 0, .last = 15};
    SequenceSegmentGroup group{.kind = 1, .segments = {segment}};
    auto                 result = annotateSequence({group}, 0, 10);
    // Expected:
    // Annotated:  |-----------|
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0].first, 0);
    EXPECT_EQ(result[0].last, 10);
    ASSERT_EQ(result[0].annotations.size(), 1);
    EXPECT_TRUE(result[0].isAnnotatedWith(1, 1));
}

TEST(RangeAlgorithmsTest, SegmentSmallerThanRange) {
    // Test case:
    // Group1:     |--------|
    // Range: |-------------------|
    SequenceSegment      segment{.kind = 1, .first = 12, .last = 20};
    SequenceSegmentGroup group{.kind = 1, .segments = {segment}};
    auto                 result = annotateSequence({group}, 0, 30);
    // Expected:
    // Annotated:  |-----------|
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0].first, 12);
    EXPECT_EQ(result[0].last, 20);
    ASSERT_EQ(result[0].annotations.size(), 1);
    EXPECT_TRUE(result[0].isAnnotatedWith(1, 1));
}

TEST(RangeAlgorithmsTest, SegmentStandaloneRanges) {
    // Test case:
    // Group1:     |--------|   |----------|
    // Range: |--------------------------------|
    SequenceSegmentGroup group{
        .kind     = 1,
        .segments = {
            SequenceSegment{.kind = 1, .first = 12, .last = 20},
            SequenceSegment{.kind = 1, .first = 30, .last = 40},
        }};
    auto result = annotateSequence({group}, 0, 60);
    // Expected:
    // Annotated:  |-----------|
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0].first, 12);
    EXPECT_EQ(result[0].last, 20);
    ASSERT_EQ(result[0].annotations.size(), 1);
    EXPECT_TRUE(result[0].isAnnotatedWith(1, 1));
    EXPECT_EQ(result[1].first, 30);
    EXPECT_EQ(result[1].last, 40);
    ASSERT_EQ(result[1].annotations.size(), 1);
    EXPECT_TRUE(result[1].isAnnotatedWith(1, 1));
}
