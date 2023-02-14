#include <parse/OrgTokenizer.hpp>
#include "common.hpp"

TEST_CASE("Basic lexer", "[lex]") {
    OrgTokenGroup res;
    OrgTokenizer  lexer{&res};
    std::string   base{"word"};
    PosStr        str{base};

    lexer.lexText(str);
}
