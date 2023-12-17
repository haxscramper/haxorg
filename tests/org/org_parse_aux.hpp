#pragma once

#include <sem/SemOrg.hpp>
#include <sem/SemConvert.hpp>
#include <parse/OrgSpec.hpp>
#include <lexbase/NodeIO.hpp>

using org = OrgNodeKind;
using otk = OrgTokenKind;

// added comment

namespace YAML {
template <>
struct convert<BaseFill> {
    static Node encode(BaseFill const& str) {
        Node result;
        result["text"] = str.text;
        result["line"] = str.line;
        result["col"]  = str.col;
        return result;
    }
    static bool decode(Node const& in, BaseFill& out) {
        if (in["text"]) {
            out.text = in["text"].as<Str>();
        }

        if (in["line"]) {
            out.line = in["line"].as<int>();
        }

        if (in["col"]) {
            out.col = in["col"].as<int>();
        }

        return true;
    }
};

template <>
struct convert<OrgFill> {
    static Node encode(OrgFill const& str) {
        Node result;
        if (str.base) {
            result["base"] = convert<BaseFill>::encode(*str.base);
        }
        return result;
    }
    static bool decode(Node const& in, OrgFill& out) {
        if (in["str"]) {
            out.base = BaseFill{.text = in["str"].as<Str>()};
        } else if (in["base"]) {
            out.base = in["base"].as<BaseFill>();
        }
        return true;
    }
};

template <>
struct convert<OrgToken> {
    static Node encode(OrgToken const& str) {
        Node result;
        result["kind"] = fmt1(str.kind);
        result["str"]  = str->base->text;
        return result;
    }
    static bool decode(Node const& in, OrgToken& out) {
        LOG(INFO) << fmt1(in);
        if (in["str"]) {
            out->base = BaseFill{.text = in["str"].as<Str>()};
        }
        out.kind = enum_serde<OrgTokenKind>::from_string(
                       in["kind"].as<std::string>())
                       .value();
        return true;
    }
};

} // namespace YAML


struct MockFull {
    OrgTokenGroup                tokens;
    SPtr<OrgTokenizer>           tokenizer;
    OrgNodeGroup                 nodes;
    std::string                  base;
    Lexer<OrgTokenKind, OrgFill> lex;
    SPtr<OrgParser>              parser;
    UPtr<OrgSpec>                spec;

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

    void tokenize(CR<std::string> content) {
        BaseTokenGroup tokens = ::tokenize(content.data(), content.size());
        OrgTokenizer   tok(&this->tokens);
        tok.convert(tokens);
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
