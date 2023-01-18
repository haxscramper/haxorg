#include "common.hpp"
#include <lexbase/Node.hpp>

enum class NodeKind : u8
{
    K1,
    K2,
    K3
};

enum class TokenKind : u8
{
    K1,
    K2,
    K3
};

TEST_CASE("General node API", "[node]") {
    using NodeT  = Node<NodeKind, TokenKind>;
    using NIdT   = NodeId<NodeKind, TokenKind>;
    using TIdT   = TokenId<TokenKind>;
    using TokenT = Token<TokenKind>;
    NodeGroup<NodeKind, TokenKind> nodes;
    TokenGroup<TokenKind>          tokens;

    SECTION("Flat subnode with no deep nesting") {
        NIdT top = nodes.startTree(NodeT(NodeKind::K1));
        nodes.token(
            NodeT(NodeKind::K2, tokens.add(TokenT(TokenKind::K1))));
        nodes.token(
            NodeT(NodeKind::K2, tokens.add(TokenT(TokenKind::K2))));
        nodes.token(
            NodeT(NodeKind::K2, tokens.add(TokenT(TokenKind::K3))));
        nodes.endTree();
        REQUIRE(nodes.at(top).getExtent() == 3);

        auto [begin, end] = nodes.subnodesOf(top);
        Vec<TIdT> subtoks;
        for (; begin != end; ++begin) {
            subtoks.push_back(nodes.at(*begin).getToken());
        }
        REQUIRE(nodes.size(top) == 3);
        REQUIRE(subtoks.size() == 3);
        REQUIRE(subtoks.at(0).getIndex() == 0);
        REQUIRE(subtoks.at(2).getIndex() == 2);
        REQUIRE(tokens.at(subtoks.at(0)).kind == TokenKind::K1);
    }

    SECTION("Subnode with two levels of nesting") {
        // [ T                         ]
        // [   A       B       C       ]
        // [     A1 A2   B1 B2   C1 C2 ]
        // {     T1 T2   T3 T4   T5 T6 }
        // [ 0 1 2  3  4 5  6  7 8  9  ]

        NIdT top = nodes.startTree(NodeT(NodeKind::K1));
        for (int i = 0; i < 3; ++i) {
            NIdT sub = nodes.startTree(NodeT(NodeKind::K2));
            nodes.token(
                NodeT(NodeKind::K2, tokens.add(TokenT(TokenKind::K1))));
            nodes.token(
                NodeT(NodeKind::K2, tokens.add(TokenT(TokenKind::K2))));
            nodes.endTree();
        }
        nodes.endTree();

        REQUIRE(nodes.size(top) == 3);

        NIdT A = nodes.subnode(top, 0);
        NIdT B = nodes.subnode(top, 1);
        NIdT C = nodes.subnode(top, 2);

        REQUIRE(A.getIndex() == 1);
        REQUIRE(B.getIndex() == 4);
        REQUIRE(C.getIndex() == 7);
        REQUIRE(nodes.size(A) == 2);
        REQUIRE(nodes.size(B) == 2);

        NIdT A1 = nodes.subnode(A, 0);
        NIdT A2 = nodes.subnode(A, 1);

        REQUIRE(A1.getIndex() == 2);
        REQUIRE(A2.getIndex() == 3);

        REQUIRE(nodes.parent(top).isNil());
        REQUIRE(nodes.parent(A) == top);
        REQUIRE(nodes.parent(A1) == A);

        REQUIRE(size(nodes.allSubnodesOf(A1)) == 1);
        REQUIRE(size(nodes.allSubnodesOf(A)) == 2);
        REQUIRE(size(nodes.allSubnodesOf(top)) == 9);
    }
}
