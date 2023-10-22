#pragma once

#include <sem/SemOrg.hpp>
#include <sem/SemConvert.hpp>
#include <parse/OrgSpec.hpp>
#include <lexbase/NodeIO.hpp>

using org = OrgNodeKind;
using otk = OrgTokenKind;

struct MockFull {
    OrgTokenGroup                  tokens;
    SPtr<OrgTokenizer>             tokenizer;
    OrgNodeGroup                   nodes;
    std::string                    base;
    Lexer<OrgTokenKind, BaseToken> lex;
    SPtr<OrgParser>                parser;
    UPtr<OrgSpec>                  spec;

    MockFull(bool tracedParser, bool tracedLexer)
        : tokenizer(), nodes(nullptr), lex(&tokens) {
        spec         = getOrgSpec();
        parser       = OrgParser::initImpl(&nodes, tracedParser);
        tokenizer    = OrgTokenizer::initImpl(&tokens, tracedLexer);
        nodes.tokens = &tokens;
    }

    using LexerMethod  = bool (OrgTokenizer::*)(BaseLexer&);
    using ParserMethod = OrgId (OrgParser::*)(OrgLexer&);

    OrgAdapter a(int idx) { return OrgAdapter(&nodes, OrgId(idx)); }
    OrgAdapter a(OrgId id) { return OrgAdapter(&nodes, id); }

    OrgNode&    n(int idx) { return nodes.at(OrgId(idx)); }
    OrgToken&   t(int idx) { return tokens.at(OrgTokenId(idx)); }
    OrgNodeKind k(int idx) { return n(idx).kind; }

    void tokenize(CR<std::string> content, LexerMethod lexMethod) {
        //        base = content;
        //        PosStr str{base};
        //        ((*tokenizer).*lexMethod)(str);
    }

    void parse(ParserMethod parseMethod) {
        ((*parser).*parseMethod)(this->lex);
    }

    void run(
        CR<std::string> content,
        LexerMethod     lexMethod,
        ParserMethod    parseMethod) {
        tokenize(content, lexMethod);
        parse(parseMethod);
    }


    void treeRepr() {
        ColStream os{std::cout};
        nodes.treeRepr(os, OrgId(0), 0);
        std::cout << std::endl;
    }
};

using T = OrgTokenizer;
using P = OrgParser;
