#include <hstd/stdlib/Str.hpp>
#include "common.hpp"

TEST_CASE("String operations", "[str]") {
    SECTION("Basic operations") {
        Str s1{"Hello"};
        Str s2{"World"};
        Str empty;

        REQUIRE(s1.startsWith("He"));
        REQUIRE_FALSE(s1.startsWith("Wo"));
        REQUIRE(s1.endsWith("lo"));
        REQUIRE_FALSE(s1.endsWith("or"));
        REQUIRE(s1.size() == 5);
        REQUIRE_FALSE(s1.empty());
        REQUIRE(empty.empty());
        REQUIRE(s1[1] == 'e');
        // String slices are inclusive
        REQUIRE(s1[Slice<int>{1, 3}] == "ell");
        REQUIRE((s1 + s2) == "HelloWorld");
    }

    SECTION("String mutations") {
        Str s1{"01234"};
        Str s2{"World"};
        Str empty;

        // Change the first character of s1 to 'J'
        s1[0] = '!';
        REQUIRE(s1 == "!1234");
        // Try to change the first character of empty to 'X'
        REQUIRE_THROWS_AS((empty.at(0) = 'X'), std::out_of_range);
        // Try to change the last two characters of empty to "zz" using the
        // slice operator
        REQUIRE_THROWS_AS((empty.at(Slice<int>{1, 2})), std::out_of_range);
    }
}

#include "common_main.hpp"
