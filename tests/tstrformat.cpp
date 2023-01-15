#include <hstd/stdlib/strformat.hpp>
#include "common.hpp"

TEST_CASE("String formatting", "[str]") {
    SECTION("Plaintext") { REQUIRE("A" % to_string_vec("a") == "A"); }

    SECTION("Basic interpolation fragment parsing") {
        {
            auto f = addfFragments("${A}+${B}");
            REQUIRE(f.size() == 3);
            REQUIRE(f[0].text == "A");
            REQUIRE(f[0].kind == addfExpr);
            REQUIRE(f[1].kind == addfText);
            REQUIRE(f[1].text == "+");
            REQUIRE(f[2].kind == addfExpr);
            REQUIRE(f[2].text == "B");
        }
        {
            auto f = addfFragments("A");
            REQUIRE(f.size() == 1);
            REQUIRE(f[0].kind == addfText);
            REQUIRE(f[0].text == "A");
        }
        {
            auto f = addfFragments("$A");
            REQUIRE(f.size() == 1);
            REQUIRE(f[0].kind == addfVar);
            REQUIRE(f[0].text == "A");
        }
        {
            auto f = addfFragments("${A}");
            REQUIRE(f.size() == 1);
            REQUIRE(f[0].kind == addfExpr);
            REQUIRE(f[0].text == "A");
        }
    }

    SECTION("Interpolate values by index") {
        REQUIRE(to_string_vec("#") == std::vector<std::string>({"#"}));
        REQUIRE("$1" % to_string_vec("#") == "#");
        REQUIRE("$1+$2" % to_string_vec("@", "@") == "@+@");
        // If interpolation placeholder starts with integer value it won't
        // be treated as a name
        REQUIRE("$1A" % to_string_vec("@") == "@A");
        // If you want to make a name that starts with an integer use `${}`
        REQUIRE("${1A}" % to_string_vec("1A", "VALUE") == "VALUE");
        // If element at the required index is not found
        // `FormatStringError` exception is raised. Note that elements use
        // zero-based indexing.
        REQUIRE_THROWS_MATCHES(
            "$1000" % to_string_vec(),
            FormatStringError,
            Message(
                "Argument index out of bounds. Accessed [999], but only "
                "0 arguments were supplied"));
    }

    SECTION("Interpolate values by names") {
        REQUIRE("$name" % to_string_vec("name", "VALUE") == "VALUE");
        REQUIRE("${name}" % to_string_vec("name", "VALUE") == "VALUE");
        REQUIRE(
            "${name}*${name}" % to_string_vec("name", "VALUE")
            == "VALUE*VALUE");

        REQUIRE_THROWS_MATCHES(
            "${RANDOM}" % to_string_vec(),
            FormatStringError,
            Message("No interpolation argument named 'RANDOM'"));
    }
}
