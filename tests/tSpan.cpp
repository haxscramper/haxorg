#include "common.hpp"
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Str.hpp>

TEST_CASE("Span mutation API") {
    Vec<int>   data{0, 1, 2, 3, 4, 5, 6, 7, 8};
    int const* end = &data.back();
    SECTION("Span from vector") {
        auto span = data.toSpan();
        // Starting size of a span is the same as underlying data
        REQUIRE(span.size() == data.size());
        // Start position of a span can be moved forward
        span.moveStart(1, end);
        // By default move does not affect the end position so the span
        // size shrinks
        REQUIRE(span.size() == data.size() - 1);
        // End position can be moved as well, provided it doesn't go over
        // the end of the range
        span.moveEnd(1, end);
        // Can't move past end, `size()` stays the same
        REQUIRE(span.size() == data.size() - 1);
        // Irrespective of a number of forward steps
        span.moveEnd(100000, end);
        REQUIRE(span.size() == data.size() - 1);
        // End position can be moved back as well
        span.moveEnd(-1, end);
        // In this case span size changes as well
        REQUIRE(span.size() == data.size() - 2);
        REQUIRE(span[0] == data[1]);
        REQUIRE(span[1_B] == data[2_B]);

        span.moveEnd(-1000000, end);
        REQUIRE(span.size() == 0);
        REQUIRE(!span.hasData());
    }
}
