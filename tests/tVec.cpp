#include "common.hpp"
#include <hstd/stdlib/Vec.hpp>

TEST_CASE("Vector") {
    SECTION("Slice and indexing operators") {
        Vec<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

        // Test slice operator with positive indices
        std::span<int> slice1 = v[slice(3, 5)];
        REQUIRE(slice1.size() == 3);
        for (int i = 0; i < 3; ++i) {
            CHECK(slice1[i] == v[i + 3]);
        }

        // Test slice operator with backwards indices
        std::span<int> slice2 = v[slice(3, 3_B)];
        REQUIRE(slice2.size() == 5);
        for (int i = 0; i < 3; ++i) {
            CHECK(slice2[i] == v[i + 3]);
        }

        // Test slice operator with out-of-bounds indices, raise is
        // guaranteed
        REQUIRE_THROWS_AS(v.at(slice(0, 11)), std::out_of_range);
        REQUIRE_THROWS_AS(v.at(slice(12, 14)), std::out_of_range);
        REQUIRE_THROWS_AS(v.at(slice(1, 20_B)), std::out_of_range);

        // Test indexing operator with positive index
        REQUIRE(v[3] == 3);

        REQUIRE(v[3_B] == 7);
        REQUIRE(v[v.size() - 3] == 7);

        REQUIRE_THROWS_AS(v.at(10), std::out_of_range);
        REQUIRE_THROWS_AS(v.at(11_B), std::out_of_range);
    }

    SECTION("Edit data via span view") {
        Vec<int> v(5, 0);

        // Test modification using slice operator
        std::span<int> span = v[slice(1, 3)];
        for (int& x : span) {
            x = 42;
        }
        REQUIRE(v[0] == 0);
        REQUIRE(v[1] == 42);
        REQUIRE(v[2] == 42);
        REQUIRE(v[3] == 42);
        REQUIRE(v[4] == 0);

        // Test modification using indexing operator
        v[1] = 0;
        v[2] = 0;
        v[3] = 0;
        REQUIRE(v[0] == 0);
        REQUIRE(v[1] == 0);
        REQUIRE(v[2] == 0);
        REQUIRE(v[3] == 0);
        REQUIRE(v[4] == 0);
    }
}

#include "common_main.hpp"
