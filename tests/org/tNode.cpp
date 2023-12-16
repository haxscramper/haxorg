#include <lexbase/Node.hpp>
#include <lexbase/Node.cpp>
import std.system.reflection;
#include <gtest/gtest.h>

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

TEST(GeneralNodeAPITest, SubnodeWithTwoLevelsOfNesting) {
    using NodeT  = Node<NodeKind, TokenKind, char>;
    using NIdT   = NodeId<NodeKind, TokenKind, char>;
    using TIdT   = TokenId<TokenKind, char>;
    using TokenT = Token<TokenKind, char>;
    TokenGroup<TokenKind, char>          tokens;
    NodeGroup<NodeKind, TokenKind, char> nodes(&tokens);

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

    EXPECT_EQ(nodes.size(top), 3);

    NIdT A = nodes.subnode(top, 0);
    NIdT B = nodes.subnode(top, 1);
    NIdT C = nodes.subnode(top, 2);

    EXPECT_EQ(A.getIndex(), 1);
    EXPECT_EQ(B.getIndex(), 4);
    EXPECT_EQ(C.getIndex(), 7);
    EXPECT_EQ(nodes.size(A), 2);
    EXPECT_EQ(nodes.size(B), 2);

    NIdT A1 = nodes.subnode(A, 0);
    NIdT A2 = nodes.subnode(A, 1);

    EXPECT_EQ(A1.getIndex(), 2);
    EXPECT_EQ(A2.getIndex(), 3);

    EXPECT_TRUE(nodes.parent(top).isNil());
    EXPECT_EQ(nodes.parent(A), top);
    EXPECT_EQ(nodes.parent(A1), A);

    EXPECT_FALSE(nodes.allSubnodesOf(A1).has_value());
    EXPECT_EQ(size(nodes.allSubnodesOf(A).value()), 2);
    EXPECT_EQ(size(nodes.allSubnodesOf(top).value()), 9);
}

TEST(GeneralNodeAPITest, FlatSubnodeWithNoDeepNesting) {
    using NodeT  = Node<NodeKind, TokenKind, char>;
    using NIdT   = NodeId<NodeKind, TokenKind, char>;
    using TIdT   = TokenId<TokenKind, char>;
    using TokenT = Token<TokenKind, char>;
    TokenGroup<TokenKind, char>          tokens;
    NodeGroup<NodeKind, TokenKind, char> nodes(&tokens);

    NIdT top = nodes.startTree(NodeT(NodeKind::N1));
    (void)nodes.token(
        NodeT(NodeKind::N2, tokens.add(TokenT(TokenKind::T1))));
    (void)nodes.token(
        NodeT(NodeKind::N2, tokens.add(TokenT(TokenKind::T2))));
    (void)nodes.token(
        NodeT(NodeKind::N2, tokens.add(TokenT(TokenKind::T3))));
    (void)nodes.endTree();
    EXPECT_EQ(nodes.at(top).getExtent(), 3);

    auto [begin, end] = nodes.subnodesOf(top).value();
    Vec<TIdT> subtoks;
    for (; begin != end; ++begin) {
        subtoks.push_back(nodes.at(*begin).getToken());
    }
    EXPECT_EQ(nodes.size(top), 3);
    EXPECT_EQ(subtoks.size(), 3);
    EXPECT_EQ(subtoks.at(0).getIndex(), 0);
    EXPECT_EQ(subtoks.at(2).getIndex(), 2);
    EXPECT_EQ(tokens.at(subtoks.at(0)).kind, TokenKind::T1);
}
