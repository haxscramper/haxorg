#include "common.hpp"

#include <parse/OrgParser.hpp>

struct MockParser : public OrgParser {
    OrgTokenGroup       tokens;
    OrgNodeGroup        nodes;
    Lexer<OrgTokenKind> lex;
    MockParser(Vec<OrgTokenKind> kinds = {})
        : OrgParser(&nodes), nodes(nullptr), lex(&tokens) {
        nodes.tokens = &tokens;
        for (const auto k : kinds) {
            tokens.add(Token(k));
        }
    }

    void add(Vec<OrgTokenKind> kinds) {
        for (const auto k : kinds) {
            tokens.add(Token(k));
        }
    }

    void add(OrgTokenKind k) { tokens.add(Token(k)); }
};

TEST_CASE("Parser", "[parse]") {
    MockParser p;
    SECTION("Test") {
        p.add(OTkBracketTime);
        p.parseTime(p.lex);
    }
}
