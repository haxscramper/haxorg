#include <parse/OrgTokenizer.hpp>
//#include "common.hpp"
#include <gtest/gtest.h>

TEST(BasicLexerTest, Lex) {
    OrgTokenGroup res;
    OrgTokenizer  lexer;
    lexer.initImpl(&res, false);
    QString base{"word"};
    PosStr  str{base};

    lexer.lexText(str);
}
