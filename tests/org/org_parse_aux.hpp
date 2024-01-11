#pragma once

#include <sem/SemOrg.hpp>
#include <sem/SemConvert.hpp>
#include <parse/OrgSpec.hpp>
#include <lexbase/NodeIO.hpp>

using org = OrgNodeKind;
using otk = OrgTokenKind;

struct MockFull {
    OrgTokenGroup                tokens;
    SPtr<OrgTokenizer>           tokenizer;
    OrgNodeGroup                 nodes;
    std::string                  base;
    Lexer<OrgTokenKind, OrgFill> lex;
    SPtr<OrgParser>              parser;
    UPtr<OrgSpec>                spec;
    BaseTokenGroup               baseTokens;

    MockFull(bool tracedParser, bool tracedLexer)
        : tokenizer(), nodes(nullptr), lex(&tokens) {
        spec                  = getOrgSpec();
        parser                = std::make_shared<OrgParser>(&nodes);
        parser->TraceState    = tracedParser;
        tokenizer             = std::make_shared<OrgTokenizer>(&tokens);
        tokenizer->TraceState = tracedLexer;
        nodes.tokens          = &tokens;
    }

    OrgAdapter a(int idx) { return OrgAdapter(&nodes, OrgId(idx)); }
    OrgAdapter a(OrgId id) { return OrgAdapter(&nodes, id); }

    OrgNode&    n(int idx) { return nodes.at(OrgId(idx)); }
    OrgToken&   t(int idx) { return tokens.at(OrgTokenId(idx)); }
    OrgNodeKind k(int idx) { return n(idx).kind; }

    void tokenize(
        CR<std::string> content,
        bool            full  = true,
        std::ostream*   trace = nullptr) {

        baseTokens = ::tokenize(content.data(), content.size(), trace);
        if (full) { tokenizer->convert(baseTokens); }
    }

    void parse() { (void)parser->parseFull(lex); }

    void run(CR<std::string> content) {
        tokenize(content);
        parse();
    }


    void treeRepr() {
        ColStream os{std::cout};
        nodes.treeRepr(os, OrgId(0), 0);
        std::cout << std::endl;
    }
};

using T = OrgTokenizer;
using P = OrgParser;
