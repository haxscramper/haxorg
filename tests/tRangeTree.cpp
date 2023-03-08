#include "common.hpp"
#include <hstd/stdlib/RangeTree.hpp>

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
