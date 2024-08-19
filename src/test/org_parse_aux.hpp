#pragma once

#include <sem/SemOrg.hpp>
#include <sem/SemConvert.hpp>
#include <parse/OrgSpec.hpp>
#include <lexbase/NodeIO.hpp>

using onk = OrgNodeKind;
using otk = OrgTokenKind;

struct MockFull {
    OrgTokenGroup                tokens;
    SPtr<OrgTokenizer>           tokenizer;
    OrgNodeGroup                 nodes;
    std::string                  base;
    Lexer<OrgTokenKind, OrgFill> lex;
    SPtr<OrgParser>              parser;
    UPtr<OrgSpec>                spec;
    OrgTokenGroup                baseTokens;
    Opt<int>                     maxUnknownBaseTokens;
    sem::SemId<sem::Org>         node;

    MockFull(bool tracedParser = false, bool tracedLexer = false)
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

    void tokenizeBase(CR<std::string> content, LexerParams const& p) {
        baseTokens = ::tokenize(content.data(), content.size(), p);
    }

    void tokenizeConvert() { tokenizer->convert(baseTokens); }

    void parse() { (void)parser->parseFull(lex); }

    void run(
        CR<std::string>    content,
        LexerParams const& p = LexerParams{}) {
        tokenizeBase(content, p);
        tokenizeConvert();
        parse();
    }

    sem::SemId<sem::Org> toNode() {
        sem::OrgConverter converter{};
        return converter.toDocument(OrgAdapter(&nodes, OrgId(0)));
    }


    void treeRepr() {
        ColStream os{std::cout};
        nodes.treeRepr(os, OrgId(0), 0);
        std::cout << std::endl;
    }
};

using T = OrgTokenizer;
using P = OrgParser;
