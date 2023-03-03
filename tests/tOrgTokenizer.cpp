#include <parse/OrgTokenizer.hpp>
#include "common.hpp"

TEST_CASE("Basic lexer", "[lex]") {
    OrgTokenGroup res;
    OrgTokenizer  lexer{&res};
    QString       base{"word"};
    PosStr        str{base};

    lexer.lexText(str);
}
