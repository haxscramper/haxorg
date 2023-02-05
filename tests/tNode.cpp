#include "common.hpp"
#include <lexbase/Node.hpp>
#include <hstd/system/reflection.hpp>

enum class NodeKind : u8
{
    N1,
    N2,
    N3
};

enum class TokenKind : u8
{
    T1,
    T2,
    T3
};

BOOST_DESCRIBE_ENUM(TokenKind, T1, T2, T3);
BOOST_DESCRIBE_ENUM(NodeKind, N1, N2, N3);

TEST_CASE("General node API", "[node]") {
    using NodeT  = Node<NodeKind, TokenKind>;
    using NIdT   = NodeId<NodeKind, TokenKind>;
    using TIdT   = TokenId<TokenKind>;
    using TokenT = Token<TokenKind>;
    TokenGroup<TokenKind>          tokens;
    NodeGroup<NodeKind, TokenKind> nodes(&tokens);

    SECTION("Subnode with two levels of nesting") {
        // [ T                         ]
        // [   A       B       C       ]
        // [     A1 A2   B1 B2   C1 C2 ]
        // {     T1 T2   T3 T4   T5 T6 }
        // [ 0 1 2  3  4 5  6  7 8  9  ]

        //! [nested tree construction]

        // Create toplevel node, stack of pending nodes now contains one
        // element
        NIdT top = nodes.startTree(NodeT(NodeKind::N1));
        for (int i = 0; i < 3; ++i) {
            // Create one more nested node, stack has two elements
            NIdT sub = nodes.startTree(NodeT(NodeKind::N2));
            // Add two terminal subnodes
            (void)nodes.token(
                NodeT(NodeKind::N3, tokens.add(TokenT(TokenKind::T1))));
            (void)nodes.token(
                NodeT(NodeKind::N3, tokens.add(TokenT(TokenKind::T2))));
            // Close pending tree
            (void)nodes.endTree();
            // Now (sub ("K1" "K2")) have been pushed to the node store
            // together with associted tokens
        }
        // Close toplevel tree
        (void)nodes.endTree();
        //! [nested tree construction]

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

    SECTION("Flat subnode with no deep nesting") {
        NIdT top = nodes.startTree(NodeT(NodeKind::N1));
        (void)nodes.token(
            NodeT(NodeKind::N2, tokens.add(TokenT(TokenKind::T1))));
        (void)nodes.token(
            NodeT(NodeKind::N2, tokens.add(TokenT(TokenKind::T2))));
        (void)nodes.token(
            NodeT(NodeKind::N2, tokens.add(TokenT(TokenKind::T3))));
        (void)nodes.endTree();
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
        REQUIRE(tokens.at(subtoks.at(0)).kind == TokenKind::T1);
    }
}
