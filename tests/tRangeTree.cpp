#include "common.hpp"
#include <QString>
#include <QDebug>
#include <hstd/stdlib/RangeTree.hpp>
#include <hstd/stdlib/Debug.hpp>
#include <hstd/stdlib/Map.hpp>
#include <lexbase/Token.hpp>

bool operator==(Slice<int> lhs, Slice<int> rhs) {
    return lhs.operator==(rhs);
}

TEST_CASE("RangeTree queries", "[RangeTree]") {
    RangeTree<int> tree{
        Vec<Slice<int>>{slice(1, 5), slice(6, 8), slice(10, 12)}};

    SECTION("Query within range") {
        REQUIRE(tree.query(3).value() == slice(1, 5));
        REQUIRE(tree.query(7).value() == slice(6, 8));
        REQUIRE(tree.query(11).value() == slice(10, 12));
    }

    SECTION("Query outside range") {
        REQUIRE(!tree.query(0).has_value());
        REQUIRE(!tree.query(9).has_value());
        REQUIRE(!tree.query(13).has_value());
    }

    SECTION("Query on range boundary") {
        REQUIRE(tree.query(1).value() == slice(1, 5));
        REQUIRE(tree.query(5).value() == slice(1, 5));
        REQUIRE(tree.query(6).value() == slice(6, 8));
        REQUIRE(tree.query(8).value() == slice(6, 8));
        REQUIRE(tree.query(10).value() == slice(10, 12));
        REQUIRE(tree.query(12).value() == slice(10, 12));
    }

    RangeTree<int> overlapping(
        Vec<Slice<int>>{slice(1, 5), slice(3, 8), slice(7, 12)});

    SECTION("Query within range") {
        REQUIRE(overlapping.query(3).value() == slice(3, 8));
        REQUIRE(overlapping.query(7).value() == slice(3, 8));
        REQUIRE(overlapping.query(10).value() == slice(7, 12));
    }

    SECTION("Query outside range") {
        REQUIRE(!overlapping.query(0).has_value());
        REQUIRE(!overlapping.query(13).has_value());
    }

    SECTION("Query on range boundary") {
        REQUIRE(overlapping.query(1).value() == slice(1, 5));
        REQUIRE(overlapping.query(5).value() == slice(3, 8));
        REQUIRE(overlapping.query(7).value() == slice(3, 8));
        REQUIRE(overlapping.query(12).value() == slice(7, 12));
    }
}


TEST_CASE("Line and column information using range tree", "[RangeTree]") {
    auto rangeInfo = [](QString const& text) -> LineColInfo {
        return LineColInfo(text);
    };

    SECTION("Line range information from empty string") {
        auto lineInfo = rangeInfo("");
    }

    SECTION("Line range information") {
        auto info = rangeInfo("0");
        REQUIRE(info.whichLine(0) == 0);
        REQUIRE(info.whichColumn(0) == 0);
    }

    SECTION("Two lines") {
        auto info = rangeInfo("0123\n576");
        REQUIRE(info.whichLine(0) == 0);
        REQUIRE(info.whichColumn(1) == 1);
        REQUIRE(info.whichLine(5) == 1);
        REQUIRE(info.whichColumn(5) == 0);
    }
}
