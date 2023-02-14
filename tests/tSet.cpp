#include "common.hpp"
#include <hstd/stdlib/Set.hpp>
#include <hstd/stdlib/Str.hpp>

TEST_CASE("UnorderedSet<T> operations are correct", "[unordered_set]") {
    using S = UnorderedSet<Str>;
    S set1{"1"};
    S set2{"2"};

    // Test incl method
    SECTION("Incl method") {
        set1.incl("10");
        set2.incl("20");
        REQUIRE(set1.contains("10"));
        REQUIRE(set2.contains("20"));
    }

    // Test excl method
    SECTION("Excl method") {
        set1.excl("1");
        REQUIRE(!set1.contains("1"));
        REQUIRE(set2.contains("2"));
    }

    // Test addition operator
    SECTION("Addition operator") {
        S tmp;
        tmp.incl("2");
        REQUIRE(tmp.contains("2"));
        tmp.incl(S{"3", "4"});
        REQUIRE(tmp.contains("3"));
        REQUIRE(tmp.contains("4"));
        S set3 = S{"2"} + S{"3", "4"};
        REQUIRE(set3.contains("2"));
        REQUIRE(set3.contains("3"));
        REQUIRE(set3.contains("4"));
    }

    // Test subtraction operator
    SECTION("Subtraction operator") {
        S q = S{"2", "3", "4"};
        REQUIRE(q.contains("2"));
        REQUIRE(q.contains("3"));
        REQUIRE(q.contains("4"));
        q.excl("2");
        REQUIRE(!q.contains("2"));
        q.incl("2");
        S set3 = q - S{"3", "4"};
        REQUIRE(set3.contains("2"));
        REQUIRE(!set3.contains("3"));
        REQUIRE(!set3.contains("4"));
    }

    // Test symmetric difference operator
    SECTION("Symmetric difference operator") {
        S set3 = S{"2", "3", "4"} ^ S { "2" };
        REQUIRE(!set3.contains("2"));
        REQUIRE(set3.contains("3"));
        REQUIRE(set3.contains("4"));
    }

    // Test intersection operator
    SECTION("Intersection operator") {
        S set3 = S{"2", "0", "9"} & S{"2", "1", "3"};
        REQUIRE(set3.contains("2"));
        REQUIRE(!set3.contains("1"));
        REQUIRE(!set3.contains("3"));
    }
}
