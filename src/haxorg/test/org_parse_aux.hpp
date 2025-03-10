#pragma once

#include <haxorg/sem/SemOrg.hpp>
#include <haxorg/sem/SemConvert.hpp>
#include <haxorg/parse/OrgSpec.hpp>
#include <haxorg/lexbase/NodeIO.hpp>

namespace org::test {

using onk = OrgNodeKind;
using otk = OrgTokenKind;


struct MockFull {
    org::parse::OrgTokenGroup            tokens;
    hstd::SPtr<org::parse::OrgTokenizer> tokenizer;
    org::parse::OrgNodeGroup             nodes;
    std::string                          base;
    hstd::SPtr<org::parse::OrgParser>    parser;
    hstd::UPtr<OrgSpec>                  spec;
    org::parse::OrgTokenGroup            baseTokens;
    hstd::Opt<int>                       maxUnknownBaseTokens;
    sem::SemId<sem::Org>                 node;

    org::parse::Lexer<OrgTokenKind, org::parse::OrgFill> lex;

    MockFull(bool tracedParser = false, bool tracedLexer = false)
        : tokenizer(), nodes(nullptr), lex(&tokens) {
        spec   = getOrgSpec();
        parser = std::make_shared<org::parse::OrgParser>(&nodes);
        parser->TraceState = tracedParser;
        tokenizer = std::make_shared<org::parse::OrgTokenizer>(&tokens);
        tokenizer->TraceState = tracedLexer;
        nodes.tokens          = &tokens;
    }

    org::parse::OrgAdapter a(int idx) {
        return org::parse::OrgAdapter(&nodes, org::parse::OrgId(idx));
    }
    org::parse::OrgAdapter a(org::parse::OrgId id) {
        return org::parse::OrgAdapter(&nodes, id);
    }

    org::parse::OrgNode& n(int idx) {
        return nodes.at(org::parse::OrgId(idx));
    }
    org::parse::OrgToken& t(int idx) {
        return tokens.at(org::parse::OrgTokenId(idx));
    }
    OrgNodeKind k(int idx) { return n(idx).kind; }

    void tokenizeBase(
        hstd::CR<std::string>          content,
        org::parse::LexerParams const& p) {
        baseTokens = org::parse::tokenize(
            content.data(), content.size(), p);
    }

    void tokenizeConvert() { tokenizer->convert(baseTokens); }

    void parse() { (void)parser->parseFull(lex); }

    void run(
        hstd::CR<std::string>          content,
        org::parse::LexerParams const& p = org::parse::LexerParams{}) {
        tokenizeBase(content, p);
        tokenizeConvert();
        parse();
    }

    sem::SemId<sem::Org> toNode() {
        sem::OrgConverter converter{};
        return converter
            .convertDocument(
                org::parse::OrgAdapter(&nodes, org::parse::OrgId(0)))
            .unwrap();
    }


    void treeRepr() {
        hstd::ColStream os{std::cout};
        nodes.treeRepr(os, org::parse::OrgId(0), 0);
        std::cout << std::endl;
    }
};

} // namespace org::test
