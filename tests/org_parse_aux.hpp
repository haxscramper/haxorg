#pragma once

#include <sem/SemOrg.hpp>
#include <sem/SemConvert.hpp>

using org = OrgNodeKind;
using otk = OrgTokenKind;

struct MockFull : public OrgParser {
    OrgTokenGroup       tokens;
    OrgTokenizer        tokenizer;
    OrgNodeGroup        nodes;
    std::string         base;
    Lexer<OrgTokenKind> lex;

    MockFull()
        : tokenizer(nullptr)
        , OrgParser(&nodes)
        , nodes(nullptr)
        , lex(&tokens) {
        nodes.tokens  = &tokens;
        tokenizer.out = &tokens;
    }

    using LexerMethod  = void (OrgTokenizer::*)(PosStr&);
    using ParserMethod = OrgId (OrgParser::*)(OrgLexer&);

    OrgAdapter a(int idx) { return OrgAdapter(&nodes, OrgId(idx)); }

    OrgNode&    n(int idx) { return nodes.at(OrgId(idx)); }
    OrgToken&   t(int idx) { return tokens.at(OrgTokenId(idx)); }
    OrgNodeKind k(int idx) { return n(idx).kind; }

    std::string s(int idx) {
        if (nodes.at(OrgId(idx)).isTerminal()) {
            return nodes.strVal(OrgId(idx));
        } else {
            return "";
        }
    }

    void tokenize(CR<std::string> content, LexerMethod lexMethod) {
        base = content;
        PosStr str{base};
        (tokenizer.*lexMethod)(str);
    }

    void parse(ParserMethod parseMethod) {
        (this->*parseMethod)(this->lex);
    }

    void run(
        CR<std::string> content,
        LexerMethod     lexMethod,
        ParserMethod    parseMethod) {
        tokenize(content, lexMethod);
        parse(parseMethod);
    }
    void treeRepr() {
        std::cout << "\n";
        nodes.treeRepr(std::cout, OrgId(0), 0, {.fullBase = base.data()});
        std::cout << std::endl;
    }

    void tokenRepr() {
        for (const auto& [idx, tok] : tokens.tokens.pairs()) {
            std::cout << left_aligned(to_string(idx), 16) << " | " << *tok
                      << std::endl;
        }
    }
};

using T = OrgTokenizer;
using P = OrgParser;
