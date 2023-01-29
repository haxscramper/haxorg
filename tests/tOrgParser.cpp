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

    void         add(OrgTokenKind k) { tokens.add(Token(k)); }
    OrgNode&     operator[](int idx) { return nodes.at(OrgId(idx)); }
    Vec<OrgNode> flat() const {
        Vec<OrgNode> res;
        for (const auto& n : nodes.nodes.items()) {
            res.push_back(*n);
        }
        return res;
    }
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

struct TmpTree {
    OrgNode      head;
    Vec<TmpTree> sub;
    Vec<OrgNode> flatten() const {
        Vec<OrgNode> flatSub;
        flatSub.push_back(head);
        for (const auto& s : sub) {
            flatSub.append(s.flatten());
        }
        if (flatSub[0].isNonTerminal()) {
            flatSub[0].extend(flatSub.size() - 1);
        }
        return flatSub;
    }
};

TmpTree t(OrgNodeKind k, CR<Vec<TmpTree>> sub = {}) {
    return TmpTree{OrgNode(k, 0), sub};
}

TmpTree t(OrgNodeKind k, int index) { return TmpTree{tok(k, index)}; }
TmpTree t(OrgNode node) { return TmpTree{node}; }

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

    SECTION("Compare time range with flattened tree") {
        p.add({otk::BracketTime, otk::TimeDash, otk::BracketTime});
        p.parseTime(p.lex);
        auto tree = t(org::TimeRange,
                      {t(org::TimeStamp, 0),
                       t(org::TimeStamp, 2),
                       t(empty())})
                        .flatten();
        REQUIRE(p.flat() == tree);
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
