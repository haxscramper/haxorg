#pragma once

#include <sem/SemOrg.hpp>
#include <sem/SemConvert.hpp>
#include <parse/OrgSpec.hpp>
#include <lexbase/NodeIO.hpp>

using org = OrgNodeKind;
using otk = OrgTokenKind;

struct MockFull : public OrgParser {
    OrgTokenGroup       tokens;
    OrgTokenizer        tokenizer;
    OrgNodeGroup        nodes;
    QString             base;
    Lexer<OrgTokenKind> lex;

    MockFull()
        : tokenizer(), OrgParser(), nodes(nullptr), lex(&tokens) {
        this->initImpl(&nodes, false);
        tokenizer.initImpl(&tokens, false);
        nodes.tokens  = &tokens;
    }

    using LexerMethod  = bool (OrgTokenizer::*)(PosStr&);
    using ParserMethod = OrgId (OrgParser::*)(OrgLexer&);

    OrgAdapter a(int idx) { return OrgAdapter(&nodes, OrgId(idx)); }
    OrgAdapter a(OrgId id) { return OrgAdapter(&nodes, id); }

    OrgNode&    n(int idx) { return nodes.at(OrgId(idx)); }
    OrgToken&   t(int idx) { return tokens.at(OrgTokenId(idx)); }
    OrgNodeKind k(int idx) { return n(idx).kind; }

    QString s(int idx) {
        if (nodes.at(OrgId(idx)).isTerminal()) {
            return nodes.strVal(OrgId(idx));
        } else {
            return "";
        }
    }

    void tokenize(CR<QString> content, LexerMethod lexMethod) {
        base = content;
        PosStr str{base};
        (tokenizer.*lexMethod)(str);
    }

    void parse(ParserMethod parseMethod) {
        (this->*parseMethod)(this->lex);
    }

    void run(
        CR<QString>  content,
        LexerMethod  lexMethod,
        ParserMethod parseMethod) {
        tokenize(content, lexMethod);
        parse(parseMethod);
    }

    void treeRepr() {
        std::cout << "\n";
        ColStream os{qcout};
        nodes.treeRepr(os, OrgId(0), 0);
        std::cout << std::endl;
    }

    void jsonRepr() { std::cout << ::jsonRepr(spec, a(0)) << "\n"; }

    void yamlRepr(bool withNames = true) {
        if (withNames) {
            std::cout << ::yamlRepr(spec, a(0)) << "\n";
        } else {
            std::cout << ::yamlRepr(a(0)) << "\n";
        }
    }

    void tokenRepr() {
        for (const auto& [idx, tok] : tokens.tokens.pairs()) {
            qcout << left_aligned(to_string(idx), 16) << " | " << *tok
                  << Qt::endl;
        }
    }
};

using T = OrgTokenizer;
using P = OrgParser;
