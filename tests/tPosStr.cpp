#include <lexbase/PosStr.hpp>
#include "common.hpp"

TEST_CASE("Positional string cursor movements", "[str]") {
    std::string base{"01234"};
    PosStr      str{base};
    SECTION("Check for characters on the position ahead") {
        REQUIRE(str.at('0'));
        REQUIRE(str.at('1', 1));
        REQUIRE(str.at('2', 2));
    }

    SECTION("Check for character set on the position ahead") {
        REQUIRE(str.at({slice('0', '9')}));
        REQUIRE(str.at(charsets::Digits));
        REQUIRE(!str.at(charsets::Letters));
    }

    SECTION("Skip while single character") {
        str.skipZeroOrMore('0');
        REQUIRE(str.at('1'));
    }

    SECTION("Skip while character set") {
        REQUIRE(str.at('0'));
        str.skipZeroOrMore(CharSet{'0', '1', '2'});
        REQUIRE(str.at('3'));
    }

    SECTION("Skip before a character") {
        str.skipBefore('3');
        REQUIRE(str.at('2'));
    }

    SECTION("Skip to a character") {
        str.skipTo('3');
        REQUIRE(str.at('3'));
    }

    SECTION("Skip until one of the caracters") {
        str.skipBefore(CharSet{'3', '4'});
        REQUIRE(str.at('2'));
    }

    SECTION("Skip until a string is found") {
        str.skipBefore("34");
        REQUIRE(str.at('2'));
    }
}
