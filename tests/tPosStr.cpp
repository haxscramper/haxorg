#include <lexbase/PosStr.hpp>
#include "common.hpp"

#define __init(text)                                                      \
    QString base{text};                                                   \
    PosStr  str{base};

TEST_CASE("Positional string cursor movements", "[str]") {
    QString base{"01234"};
    PosStr  str{base};
    SECTION("Check for characters on the position ahead") {
        REQUIRE(str.at(QChar('0')));
        REQUIRE(str.at(QChar('1'), 1));
        REQUIRE(str.at(QChar('2'), 2));
    }

    SECTION("Check for character set on the position ahead") {
        REQUIRE(str.at({slice(QChar('0'), QChar('9'))}));
        REQUIRE(str.at(charsets::Digits));
        REQUIRE(!str.at(charsets::Letters));
    }

    SECTION("Skip while single character") {
        str.skipZeroOrMore(QChar('0'));
        REQUIRE(str.at(QChar('1')));
    }

    SECTION("Skip while character set") {
        REQUIRE(str.at(QChar('0')));
        str.skipZeroOrMore(CharSet{QChar('0'), QChar('1'), QChar('2')});
        REQUIRE(str.at(QChar('3')));
    }

    SECTION("Skip before a character") {
        str.skipBefore(QChar('3'));
        REQUIRE(str.at(QChar('2')));
    }

    SECTION("Skip to a character") {
        str.skipTo(QChar('3'));
        REQUIRE(str.at(QChar('3')));
    }

    SECTION("Skip until one of the caracters") {
        str.skipBefore(CharSet{QChar('3'), QChar('4')});
        REQUIRE(str.at(QChar('2')));
    }

    SECTION("Skip until a string is found") {
        str.skipBefore("34");
        REQUIRE(str.at(QChar('2')));
    }
}

TEST_CASE("Positional string API", "[str]") {
    SECTION("Column at the start of the text") {
        __init("* Random");
        REQUIRE(str.getColumn() == 0);
        str.next();
        REQUIRE(str.getColumn() == 1);
    }

    SECTION("Column compute and newlines") {
        __init("\n\n\n");
        REQUIRE(str.getColumn() == 0);
        str.next();
        REQUIRE(str.getColumn() == 0);
        str.next();
        REQUIRE(str.getColumn() == 0);
    }

    SECTION("Column compute and split text") {
        __init("0\n1\n2\n");
        REQUIRE(str.getColumn() == 0);
        REQUIRE(str.get() == '0');
        str.next();
        REQUIRE(str.getColumn() == 1);
        REQUIRE(str.get() == '\n');
    }
}
