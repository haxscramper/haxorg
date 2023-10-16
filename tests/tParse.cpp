//#include "common.hpp"
#include <lexbase/Node.hpp>
#include <lexbase/Token.hpp>
#include <lexbase/PosStr.hpp>
#include <gtest/gtest.h>

#include <boost/describe/enum.hpp>

enum NodeKind : u8
{
    N1,
    N2,
    N3,
    N4
};


enum TokenKind : u8
{
    T1,
    T2,
    T3,
    T4
};

BOOST_DESCRIBE_ENUM(TokenKind, T1, T2, T3, T4);
BOOST_DESCRIBE_ENUM(NodeKind, N1, N2, N3, N4);

struct L : public Tokenizer<TokenKind> {
    // using Lexer::Lexer;
    L(TokenGroup<TokenKind>* out) : Tokenizer<TokenKind>(out) {}
    void lex_1(PosStr& str) { push(str.tok(T1, skipCount, 1)); }
    void lex_br(PosStr& str) {
        if (str.at('{')) {
            push(str.tok(T2, skipCount, 1));
        } else {
            push(str.tok(T3, skipCount, 1));
        }
    }

    void lex(PosStr& str) {
        while (!str.finished()) {
            switch (str.get().unicode()) {
                case '{':
                case '}': lex_br(str); break;
                default: lex_1(str);
            }
        }
    }
};

NodeId<NodeKind, TokenKind> parse(
    NodeGroup<NodeKind, TokenKind>& nodes,
    Lexer<TokenKind>&               lex) {
    if (lex.at(TokenKind::T2)) {
        lex.next();
        auto top = nodes.startTree(N2);
        while (!lex.at(T3)) {
            (void)parse(nodes, lex);
        }
        lex.skip(T3);
        return nodes.endTree();
    } else {
        return nodes.token(N1, lex.pop());
    }
}

TEST(CoreLinearlizedASTParserTest, Node) {
    std::string               base{"{{{{{{DDD}{WEWE}{VVVV}}}{EEEE}}}}"};
    TokenGroup<TokenKind> tokens;
    PosStr                str(base);
    L                     tokenizer(&tokens);
    tokenizer.lex(str);
    Lexer<TokenKind>               lexer(&tokens);
    NodeGroup<NodeKind, TokenKind> nodes(&tokens);
    auto                           top = parse(nodes, lexer);

    ASSERT_EQ(tokens.tokens.size(), base.size());
    // nodes.lispRepr(std::cout, top, {.fullBase = base.data()});
    // std::cout << "\n";
    // nodes.treeRepr(std::cout, top, 0, {.fullBase = base.data()});
    // std::cout << "\n";
}
