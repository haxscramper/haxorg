#include "common.hpp"

#include <parse/OrgParser.hpp>

struct MockParser : public OrgParser {
    OrgTokenGroup       tokens;
    OrgNodeGroup        nodes;
    Lexer<OrgTokenKind> lex;
    MockParser(Vec<OrgTokenKind> kinds = {})
        : nodes(nullptr), lex(&tokens) {
        initImpl(&nodes, false);
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
        p.add(
            {otk::InactiveTimeBegin,
             otk::StaticTimeDatePart,
             otk::InactiveTimeEnd});
        p.parseTimeStamp(p.lex);
        REQUIRE(p[0] == tok(org::StaticInactiveTime, 0));
    }

    SECTION("Parse time range") {
        p.add({
            otk::InactiveTimeBegin,
            otk::StaticTimeDatePart,
            otk::InactiveTimeEnd,
            otk::TimeDash,
            otk::InactiveTimeBegin,
            otk::StaticTimeDatePart,
            otk::InactiveTimeEnd,
        });
        p.parseTimeRange(p.lex);
        REQUIRE(p[0].kind == org::TimeRange);
        // start of the time range extent, two elements
        REQUIRE(p[1].kind == org::StaticInactiveTime);
        // Time dash token is skipped
        REQUIRE(p[6].kind == org::StaticInactiveTime);
    }
}
