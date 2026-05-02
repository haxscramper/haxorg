#include <gtest/gtest.h>
#include <hstd/ext/geometry/hstd_geometry_test.hpp>

namespace hg = hstd::ext::geometry;

TEST(GeometryChecks, RelativeDirectionalChecksUseStationaryFirst) {
    //             12,0─┐
    //              │   │
    //              │   │
    //              │   │
    //              └───┘
    //            10,10────┐
    //            │        │
    // 0,12─┐     │        │    25,12┐
    //  │   │     │        │     │   │
    //  │   │     │        │     │   │
    //  │   │     │  15,15─┐     │   │
    //  └───┘     │    │   │     └───┘
    //            │    │   │
    //            │    │   │
    //            └────└───┘
    //             12,25┐
    //              │   │
    //              │   │
    //              │   │
    //              └───┘

    hg::Rect stationary(10, 10, 10, 10);

    hg::Rect relativeLeft(0, 12, 5, 5);
    hg::Rect relativeRight(25, 12, 5, 5);
    hg::Rect relativeAbove(12, 0, 5, 5);
    hg::Rect relativeBelow(12, 25, 5, 5);
    hg::Rect relativeOverlap(15, 15, 5, 5);

    EXPECT_TRUE(
        static_cast<bool>(hg::checkLeftOf(stationary, relativeLeft)));
    EXPECT_FALSE(
        static_cast<bool>(hg::checkLeftOf(stationary, relativeOverlap)));

    EXPECT_TRUE(
        static_cast<bool>(hg::checkRightOf(stationary, relativeRight)));
    EXPECT_FALSE(
        static_cast<bool>(hg::checkRightOf(stationary, relativeOverlap)));

    EXPECT_TRUE(
        static_cast<bool>(hg::checkAbove(stationary, relativeAbove)));
    EXPECT_FALSE(
        static_cast<bool>(hg::checkAbove(stationary, relativeOverlap)));

    EXPECT_TRUE(
        static_cast<bool>(hg::checkBelow(stationary, relativeBelow)));
    EXPECT_FALSE(
        static_cast<bool>(hg::checkBelow(stationary, relativeOverlap)));
}

TEST(GeometryChecks, PartiallyAboveAndCoveringChecks) {
    hg::Rect stationary(10, 10, 10, 10);
    hg::Rect relativePartiallyAbove(12, 8, 4, 10);
    hg::Rect container(0, 0, 40, 40);
    hg::Rect nested(10, 10, 5, 5);

    EXPECT_TRUE(
        static_cast<bool>(hg::checkPartiallyAbove(
            stationary, relativePartiallyAbove, 80.0)));
    EXPECT_FALSE(
        static_cast<bool>(hg::checkPartiallyAbove(
            stationary, relativePartiallyAbove, 79.0)));

    EXPECT_TRUE(
        static_cast<bool>(hg::checkFullyCovers(container, nested)));
    EXPECT_FALSE(
        static_cast<bool>(hg::checkFullyCovers(nested, container)));
}

TEST(GeometryChecks, AlignmentDistanceAndSizeChecks) {
    hg::Rect a(0, 0, 10, 10);
    hg::Rect bAlignedHoriz(20, 0, 10, 10);
    hg::Rect bAlignedVert(0, 20, 10, 10);
    hg::Rect bFar(30, 0, 10, 10);
    hg::Rect cSameSize(50, 50, 10, 10);
    hg::Rect dDifferent(50, 50, 12, 9);

    EXPECT_TRUE(
        static_cast<bool>(hg::checkAlignedHorizontally(a, bAlignedHoriz)));
    EXPECT_TRUE(
        static_cast<bool>(hg::checkAlignedVertically(a, bAlignedVert)));

    EXPECT_TRUE(static_cast<bool>(hg::checkMinDistance(a, bFar, 20.0)));
    EXPECT_FALSE(
        static_cast<bool>(hg::checkMinDistance(a, bAlignedHoriz, 20.0)));

    EXPECT_TRUE(
        static_cast<bool>(hg::checkMaxDistance(a, bAlignedHoriz, 10.0)));
    EXPECT_FALSE(static_cast<bool>(hg::checkMaxDistance(a, bFar, 10.0)));

    EXPECT_TRUE(static_cast<bool>(hg::checkSameWidth(a, cSameSize)));
    EXPECT_TRUE(static_cast<bool>(hg::checkSameHeight(a, cSameSize)));
    EXPECT_TRUE(static_cast<bool>(hg::checkSameSize(a, cSameSize)));

    EXPECT_FALSE(static_cast<bool>(hg::checkSameWidth(a, dDifferent)));
    EXPECT_FALSE(static_cast<bool>(hg::checkSameHeight(a, dDifferent)));
    EXPECT_FALSE(static_cast<bool>(hg::checkSameSize(a, dDifferent)));
}

TEST(GeometryChecks, IntersectionsAndEquidistantChecks) {
    hg::Point p1(5, 5);
    hg::Point p2(5, 5);
    hg::Point p3(6, 5);
    hg::Rect  rect(0, 0, 10, 10);

    hg::Path path1;
    path1.moveTo(0, 0).lineTo(10, 10);

    hg::Path path2;
    path2.moveTo(0, 10).lineTo(10, 0);

    hg::Path path3;
    path3.moveTo(20, 20).lineTo(30, 30);

    EXPECT_TRUE(static_cast<bool>(hg::checkIntersects(p1, p2)));
    EXPECT_FALSE(static_cast<bool>(hg::checkIntersects(p1, p3)));

    EXPECT_TRUE(static_cast<bool>(hg::checkIntersects(p1, rect)));
    EXPECT_TRUE(static_cast<bool>(hg::checkIntersects(rect, p1)));

    EXPECT_TRUE(static_cast<bool>(hg::checkIntersects(p1, path1)));
    EXPECT_TRUE(static_cast<bool>(hg::checkIntersects(rect, path1)));
    EXPECT_TRUE(static_cast<bool>(hg::checkIntersects(path1, path2)));
    EXPECT_FALSE(static_cast<bool>(hg::checkIntersects(path1, path3)));

    hstd::Vec<hg::Rect> equidistantOk = {
        hg::Rect(0, 0, 2, 2),
        hg::Rect(10, 0, 2, 2),
        hg::Rect(20, 0, 2, 2),
    };

    hstd::Vec<hg::Rect> equidistantBad = {
        hg::Rect(0, 0, 2, 2),
        hg::Rect(9, 0, 2, 2),
        hg::Rect(20, 0, 2, 2),
    };

    EXPECT_TRUE(
        static_cast<bool>(hg::checkEquidistant(equidistantOk, 0.0)));
    EXPECT_FALSE(
        static_cast<bool>(hg::checkEquidistant(equidistantBad, 0.0)));
}
