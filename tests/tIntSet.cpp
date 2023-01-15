#include <hstd/stdlib/IntSet.hpp>
#include "common.hpp"

TEST_CASE("Test integral set operations", "[contains]") {
    IntSet<char> s;
    IntSet<char> other;
    SECTION("Initial set content") {
        // Default-initialized set does not contain any values and has
        // `.size()` zero
        REQUIRE(s.size() == 0);
        // You can include values to the set using `.incl` method
        s.incl('a');
        // `.size()` shows the number of values included in the set
        REQUIRE(s.size() == 1);
    }

    SECTION("Contains for a single item") {
        // Presence of specific element can be tested using `.contains()`
        // value
        REQUIRE(!s.contains('c'));
        // Elements can be added
        s.incl('c');
        // Tested again
        REQUIRE(s.contains('c'));
        // Then excluded
        s.excl('c');
        // And then tested again, now for absence
        REQUIRE(!s.contains('c'));
    }

    SECTION("Contains for set operations") {
        // You can check for subset relation as well. Default (empty)  sets
        // are subset of each other
        REQUIRE(s.contains(other));
        REQUIRE(other.contains(s));
        // Since they both have the same elements
        REQUIRE(other.size() == 0);
        REQUIRE(s.size() == 0);
        // After adding element to the set  this no longer holds
        s.incl('s');
        REQUIRE(s.contains(other));
        REQUIRE(!other.contains(s));
        // You can test for subset relation using `<` operator: it tests
        // for proper subset
        REQUIRE(other < s);
        // You can also test for a regular subset operation, using `<=`
        // operator which is analogous to the `s.contains(other)`
        REQUIRE(other <= s);
        other.incl('s');
        // After including the same element in the set `<` no longer holds
        REQUIRE(!(other < s));
        // But regular subset check is ok
        REQUIRE(other <= s);
        // And it now works in both directions again
        REQUIRE(s <= other);
    }


    SECTION("Set operations") {
        REQUIRE((s + other).size() == 0);
        REQUIRE((s - other).size() == 0);
        REQUIRE(s < (s + IntSet<char>{'1'}));
        REQUIRE(s < (s | IntSet<char>{'1'}));
        REQUIRE(s == (s & IntSet<char>{'1'}));
    }

    SECTION("Integer set operators") {
        IntSet<i8> s1{1_i8, 2_i8, 3_i8};
        IntSet<i8> s2{2_i8, 3_i8, 4_i8};
        IntSet<i8> s3{4_i8, 5_i8, 6_i8};
        IntSet<i8> empty;

        // Check that the union of s1 and s2 is {1, 2, 3, 4}
        REQUIRE((s1 + s2) == IntSet<i8>{1_i8, 2_i8, 3_i8, 4_i8});
        // Check that the intersection of s1 and s2 is {2, 3}
        REQUIRE((s1 & s2) == IntSet<i8>{2_i8, 3_i8});
        // Check that the difference between s1 and s2 is {1}
        REQUIRE((s1 - s2) == IntSet<i8>{1_i8});
        // Check that the symmetric difference between s1 and s2 is {1, 4}
        REQUIRE((s1 ^ s2) == IntSet<i8>{1_i8, 4_i8});
        // Check that the union of s1 and s3 is {1, 2, 3, 4, 5, 6}
        REQUIRE(
            (s1 + s3) == IntSet<i8>{1_i8, 2_i8, 3_i8, 4_i8, 5_i8, 6_i8});
        // Check that the intersection of s1 and s3 is empty
        REQUIRE((s1 & s3).empty());
        // Check that the difference between s1 and s3 is {1, 2, 3}
        REQUIRE((s1 - s3) == s1);
        // Check that the symmetric difference between s1 and s3 is {1, 2,
        // 3, 4, 5, 6}
        REQUIRE((s1 ^ s3) == (s1 + s3));
        // Check that the union of empty and s1 is {1, 2, 3}
        REQUIRE((empty + s1) == s1);
        // Check that the intersection of empty and s1 is empty
        REQUIRE((empty & s1).empty());
        // Check that the difference between empty and s1 is empty
        REQUIRE((empty - s1).empty());
        // Check that the symmetric difference between empty and s1 is {1,
        // 2, 3}
        REQUIRE((empty ^ s1) == s1);
    }
}
