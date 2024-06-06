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

Slice<int> query1(RangeTree<int> const& tree, int point) {
    auto ranges = tree.getRanges(point);
    EXPECT_EQ(ranges.size(), 1);
    return ranges.at(0).range;
}

bool query0(RangeTree<int> const& tree, int point) {
    auto ranges = tree.getRanges(point);
    return ranges.size() == 0;
}

TEST(RangeAlgorithmsTest, Queries) {
    for (auto const& list : Vec<Vec<Slice<int>>>{
             Vec<Slice<int>>{slice(1, 5), slice(6, 8), slice(10, 12)},
             Vec<Slice<int>>{slice(6, 8), slice(1, 5), slice(10, 12)},
         }) {

        RangeTree<int> tree{list};

        // Query within range
        EXPECT_EQ(query1(tree, 3), slice(1, 5));
        EXPECT_EQ(query1(tree, 7), slice(6, 8));
        EXPECT_EQ(query1(tree, 11), slice(10, 12));

        // Query outside range
        EXPECT_FALSE(query0(tree, 0));
        EXPECT_FALSE(query0(tree, 9));
        EXPECT_FALSE(query0(tree, 13));

        // Query on range boundary
        EXPECT_EQ(query1(tree, 1), slice(1, 5));
        EXPECT_EQ(query1(tree, 5), slice(1, 5));
        EXPECT_EQ(query1(tree, 6), slice(6, 8));
        EXPECT_EQ(query1(tree, 8), slice(6, 8));
        EXPECT_EQ(query1(tree, 10), slice(10, 12));
        EXPECT_EQ(query1(tree, 12), slice(10, 12));
    }

    RangeTree<int> overlapping(
        Vec<Slice<int>>{slice(1, 5), slice(3, 8), slice(7, 12)});

    // Query within range
    EXPECT_EQ(query1(overlapping, 3), slice(3, 8));
    EXPECT_EQ(query1(overlapping, 7), slice(3, 8));
    EXPECT_EQ(query1(overlapping, 10), slice(7, 12));

    // Query outside range
    EXPECT_FALSE(query0(overlapping, 0));
    EXPECT_FALSE(query0(overlapping, 13));

    // Query on range boundary
    EXPECT_EQ(query1(overlapping, 1), slice(1, 5));
    EXPECT_EQ(query1(overlapping, 5), slice(3, 8));
    EXPECT_EQ(query1(overlapping, 7), slice(3, 8));
    EXPECT_EQ(query1(overlapping, 12), slice(7, 12));
}


TEST(RangeAlgorithmsTest, NestedTreeSegments) {
    RangeTree<int> tree{Vec<Slice<int>>{
        /* */ slice(0, 1),
        /* */ slice(2, 13),
        /*    */ slice(3, 6),
        /*       */ slice(4, 5),
        /*    */ slice(7, 12),
        /*       */ slice(8, 9),
        /*       */ slice(10, 11),
        /* */ slice(14, 15),
    }};

    LOG(INFO) << fmt1(tree);

    {
        auto it = tree.getNodes(0);
        EXPECT_EQ(it.size(), 1);
    }
    {
        auto it = tree.getNodes(-1);
        EXPECT_EQ(it.size(), 0);
    }
    {
        auto it = tree.getNodes(2);
        EXPECT_EQ(it.size(), 1);
    }
    {
        auto it = tree.getNodes(3);
        EXPECT_EQ(it.size(), 2);
    }
    {
        auto it = tree.getNodes(4);
        EXPECT_EQ(it.size(), 3);
    }
    {
        auto it = tree.getNodes(5);
        EXPECT_EQ(it.size(), 3);
    }
    {
        auto it = tree.getNodes(6);
        EXPECT_EQ(it.size(), 2);
    }
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
