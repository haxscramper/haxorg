#include <lexbase/PosStr.hpp>
//#include "common.hpp"
#include <gtest/gtest.h>

#define __init(text)                                                      \
    std::string base{text};                                                   \
    PosStr  str{base};


TEST(
    PositionalStringCursorMovementsTest,
    CheckForCharactersOnPositionAhead) {
    std::string base{"01234"};
    PosStr  str{base};

    EXPECT_TRUE(str.at(QChar('0')));
    EXPECT_TRUE(str.at(QChar('1'), 1));
    EXPECT_TRUE(str.at(QChar('2'), 2));
}

TEST(
    PositionalStringCursorMovementsTest,
    CheckForCharacterSetOnPositionAhead) {
    std::string base{"01234"};
    PosStr  str{base};

    EXPECT_TRUE(str.at({slice(QChar('0'), QChar('9'))}));
    EXPECT_TRUE(str.at(charsets::Digits));
    EXPECT_FALSE(str.at(charsets::Letters));
}

TEST(PositionalStringCursorMovementsTest, SkipWhileSingleCharacter) {
    std::string base{"01234"};
    PosStr  str{base};

    str.skipZeroOrMore(QChar('0'));
    EXPECT_TRUE(str.at(QChar('1')));
}

TEST(PositionalStringCursorMovementsTest, SkipWhileCharacterSet) {
    std::string base{"01234"};
    PosStr  str{base};

    EXPECT_TRUE(str.at(QChar('0')));
    str.skipZeroOrMore(CharSet{QChar('0'), QChar('1'), QChar('2')});
    EXPECT_TRUE(str.at(QChar('3')));
}

TEST(PositionalStringCursorMovementsTest, SkipBeforeCharacter) {
    std::string base{"01234"};
    PosStr  str{base};

    str.skipBefore(QChar('3'));
    EXPECT_TRUE(str.at(QChar('2')));
}

TEST(PositionalStringCursorMovementsTest, SkipToCharacter) {
    std::string base{"01234"};
    PosStr  str{base};

    str.skipTo(QChar('3'));
    EXPECT_TRUE(str.at(QChar('3')));
}

TEST(PositionalStringCursorMovementsTest, SkipUntilOneOfCharacters) {
    std::string base{"01234"};
    PosStr  str{base};

    str.skipBefore(CharSet{QChar('3'), QChar('4')});
    EXPECT_TRUE(str.at(QChar('2')));
}

TEST(PositionalStringCursorMovementsTest, SkipUntilStringIsFound) {
    std::string base{"01234"};
    PosStr  str{base};

    str.skipBefore("34");
    EXPECT_TRUE(str.at(QChar('2')));
}

TEST(PositionalStringApiTest, ColumnAtStartOfText) {
    __init("* Random");
    EXPECT_EQ(str.getColumn(), 0);
    str.next();
    EXPECT_EQ(str.getColumn(), 1);
}

TEST(PositionalStringApiTest, ColumnComputeAndNewlines) {
    __init("\n\n\n");
    EXPECT_EQ(str.getColumn(), 0);
    str.next();
    EXPECT_EQ(str.getColumn(), 0);
    str.next();
    EXPECT_EQ(str.getColumn(), 0);
}

TEST(PositionalStringApiTest, ColumnComputeAndSplitText) {
    __init("0\n1\n2\n");
    EXPECT_EQ(str.getColumn(), 0);
    EXPECT_EQ(str.get(), '0');
    str.next();
    EXPECT_EQ(str.getColumn(), 1);
    EXPECT_EQ(str.get(), '\n');
}
