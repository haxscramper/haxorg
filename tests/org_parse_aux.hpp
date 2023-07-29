#pragma once

#include <sem/SemOrg.hpp>
#include <sem/SemConvert.hpp>
#include <parse/OrgSpec.hpp>
#include <lexbase/NodeIO.hpp>

using org = OrgNodeKind;
using otk = OrgTokenKind;

struct MockFull {
    OrgTokenGroup       tokens;
    SPtr<OrgTokenizer>  tokenizer;
    OrgNodeGroup        nodes;
    QString             base;
    Lexer<OrgTokenKind> lex;
    SPtr<OrgParser>     parser;
    LineColInfo         info;

    Func<LineCol(CR<PosStr>)> locationResolver;

    MockFull() : tokenizer(), nodes(nullptr), lex(&tokens) {
        parser       = OrgParser::initImpl(&nodes, false);
        tokenizer    = OrgTokenizer::initImpl(&tokens, false);
        nodes.tokens = &tokens;

        locationResolver = [&](CR<PosStr> str) -> LineCol {
            Slice<int> absolute = tokens.toAbsolute(str.view);
            return {
                info.whichLine(absolute.first + str.pos) + 1,
                info.whichColumn(absolute.first + str.pos),
                absolute.first + str.pos,
            };
        };

        tokenizer->setLocationResolver(locationResolver);
        parser->setLocationResolver(locationResolver);
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
        info = LineColInfo{base};
        tokens.base = base.data();
        PosStr str{base};
        ((*tokenizer).*lexMethod)(str);
    }

    void parse(ParserMethod parseMethod) {
        ((*parser).*parseMethod)(this->lex);
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

    void jsonRepr() { std::cout << ::jsonRepr(*OrgSpecInstance::get(), a(0)) << "\n"; }

    void yamlRepr(bool withNames = true) {
        if (withNames) {
            std::cout << ::yamlRepr(*OrgSpecInstance::get(), a(0)) << "\n";
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
