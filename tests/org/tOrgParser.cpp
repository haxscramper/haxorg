#include <gtest/gtest.h>
#include <parse/OrgParser.hpp>

struct MockParser {
    OrgTokenGroup                tokens;
    OrgNodeGroup                 nodes;
    SPtr<OrgParser>              parser;
    Lexer<OrgTokenKind, OrgFill> lex;
    MockParser(Vec<OrgTokenKind> kinds = {})
        : nodes(nullptr), lex(&tokens) {
        parser       = std::make_shared<OrgParser>(&nodes);
        nodes.tokens = &tokens;
        for (const auto k : kinds) { (void)tokens.add(OrgToken(k)); }
    }

    void add(Vec<OrgTokenKind> kinds) {
        for (const auto k : kinds) { (void)tokens.add(OrgToken(k)); }
    }

    void         add(OrgTokenKind k) { (void)tokens.add(OrgToken(k)); }
    OrgNode&     operator[](int idx) { return nodes.at(OrgId(idx)); }
    Vec<OrgNode> flat() const {
        Vec<OrgNode> res;
        for (const auto& n : nodes.nodes.items()) { res.push_back(*n); }
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

using onk = OrgNodeKind;
using otk = OrgTokenKind;

struct TmpTree {
    OrgNode      head;
    Vec<TmpTree> sub;
    Vec<OrgNode> flatten() const {
        Vec<OrgNode> flatSub;
        flatSub.push_back(head);
        for (const auto& s : sub) { flatSub.append(s.flatten()); }
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

class ParserTest : public ::testing::Test {
  protected:
    MockParser p;
};
