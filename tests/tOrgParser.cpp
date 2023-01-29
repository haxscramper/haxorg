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

    void     add(OrgTokenKind k) { tokens.add(Token(k)); }
    OrgNode& operator[](int idx) { return nodes.at(OrgId(idx)); }
};

OrgNode tree(OrgNodeKind kind, int extent) {
    return OrgNode(kind, extent);
}

OrgNode empty() { return OrgNode(OrgNodeKind::Empty, 0); }

OrgNode tok(OrgNodeKind kind, int id) {
    return OrgNode(kind, OrgTokenId(id));
}

using org = OrgNodeKind;
using otk = OrgTokenKind;

TEST_CASE("Parser", "[parse]") {
    MockParser p;
    SECTION("Parse single time entry") {
        p.add(otk::BracketTime);
        p.parseTime(p.lex);
        REQUIRE(p[0] == tok(org::TimeStamp, 0));
    }

    SECTION("Parse time range") {
        p.add({otk::BracketTime, otk::TimeDash, otk::BracketTime});
        p.parseTime(p.lex);
        REQUIRE(p[0] == tree(org::TimeRange, 3));
        // start of the time range extent, two elements
        REQUIRE(p[1] == tok(org::TimeStamp, 0));
        // Time dash token is skipped
        REQUIRE(p[2] == tok(org::TimeStamp, 2));
        REQUIRE(p[3] == empty());
        std::cout << to_string(org::TimeStamp) << std::endl;
    }

    SECTION("Parse time with arrow") {
        p.add(
            {otk::BracketTime,
             otk::TimeDash,
             otk::BracketTime,
             otk::TimeArrow,
             otk::TimeDuration});
        p.parseTime(p.lex);
    }
}
