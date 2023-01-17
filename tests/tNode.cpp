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
    SECTION("Random") {
        using NodeT  = Node<NodeKind, TokenKind>;
        using NIdT   = NodeId<NodeKind, TokenKind>;
        using TokenT = Token<TokenKind>;
        NodeGroup<NodeKind, TokenKind> nodes;
        TokenGroup<TokenKind>          tokens;

        NIdT top = nodes.startTree(NodeT(NodeKind::K1));
        nodes.token(
            NodeT(NodeKind::K2, tokens.add(TokenT(TokenKind::K1))));
        nodes.token(
            NodeT(NodeKind::K2, tokens.add(TokenT(TokenKind::K2))));
        nodes.token(
            NodeT(NodeKind::K2, tokens.add(TokenT(TokenKind::K3))));
        nodes.endTree();
        REQUIRE(nodes.at(top).getExtent() == 3);
    }
}
