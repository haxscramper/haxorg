#include <parse/OrgLexer.hpp>
#include "common.hpp"

TEST_CASE("Basic lexer", "[lex]") {
    OrgTokenGroup res;
    OrgLexer      lexer{&res};
    std::string   base{"word"};
    PosStr        str{base};

    lexer.lexText(str);
    std::cout << res.tokens.size() << std::endl;
    std::cout << res.tokens.atIndex(0) << std::endl;
}
