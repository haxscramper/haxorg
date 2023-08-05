#pragma once

#include "org_parse_aux.hpp"

#include <cstdlib>
#include <QString>

#include <lexbase/NodeTest.hpp>
#include <hstd/wrappers/textlayouter.hpp>

struct QFileInfo;



class CorpusRunner {
  public:
    // Define environment variable in the QT app run environment to get
    // better-formatted test diff output.
    bool useQFormat() { return getenv("IN_QT_RUN") == "true"; }

    void writeFileOrStdout(
        QFileInfo const& target,
        QString const&   content,
        bool             useFile);

    MockFull::ParserMethod getParser(CR<Str> name);
    MockFull::LexerMethod  getLexer(CR<Str> name);

    struct ExportResult {
        struct Plaintext {
            QString text;
        };

        struct Text {
            json textLyt;
        };

        struct Structured {
            json data;
        };

        SUB_VARIANTS(
            Kind,
            Data,
            data,
            getKind,
            Plaintext,
            Text,
            Structured);

        ExportResult() {}
        ExportResult(CR<Data> data) : data(data) {}
        Data                      data;
        ParseSpec::ExporterExpect expected;
    };

    json toTextLyt(
        layout::Block::Ptr        block,
        Func<Str(layout::LytStr)> getStr);

    ExportResult runExporter(
        sem::SemId                       top,
        ParseSpec::ExporterExpect const& exp);

    struct RunResult {
        struct NodeCompare {
            bool    isOk = false;
            ColText failDescribe;
        };

        struct LexCompare {
            bool    isOk = false;
            ColText failDescribe;
        };

        struct SemCompare {
            bool    isOk = false;
            ColText failDescribe;
        };

        struct ExportCompare {
            struct Run {
                ColText failDescribe;
                bool    isOk;
            };

            Vec<Run> run;

            bool isOk() const {
                return std::all_of(run.begin(), run.end(), [](CR<Run> r) {
                    return r.isOk;
                });
            }
        };

        struct None {};

        SUB_VARIANTS(
            Kind,
            Data,
            data,
            getKind,
            None,
            NodeCompare,
            LexCompare,
            SemCompare,
            ExportCompare);

        RunResult() {}
        RunResult(CR<Data> data) : data(data) {}
        Data data;

        bool isOk() const {
            return std::visit(
                overloaded{
                    [](CR<NodeCompare> n) { return n.isOk; },
                    [](CR<LexCompare> n) { return n.isOk; },
                    [](CR<SemCompare> n) { return n.isOk; },
                    [](CR<ExportCompare> e) { return e.isOk(); },
                    [](CR<None> n) { return true; },
                },
                data);
        }
    };

    RunResult::LexCompare compareTokens(
        CR<TokenGroup<OrgTokenKind>> lexed,
        CR<TokenGroup<OrgTokenKind>> expected,
        ParseSpec::Conf::MatchMode   match);

    RunResult::NodeCompare compareNodes(
        CR<NodeGroup<OrgNodeKind, OrgTokenKind>> parsed,
        CR<NodeGroup<OrgNodeKind, OrgTokenKind>> expected);


    RunResult::SemCompare compareSem(
        CR<ParseSpec> spec,
        sem::SemId    node,
        json          expected);

    RunResult runSpec(CR<ParseSpec> spec, CR<QString> from) {
        MockFull::LexerMethod lexCb = getLexer(spec.lexImplName);
        MockFull              p(spec.debug.traceParse, spec.debug.traceLex);

        { // Input source
            if (spec.debug.printSource) {
                writeFile(spec.debugFile("source.org"), spec.source);
            }
        }


        { // Lexing
            if (spec.debug.doLex) {
                p.tokenizer->trace = spec.debug.traceLex;
                if (spec.debug.lexToFile) {
                    p.tokenizer->setTraceFile(
                        spec.debugFile("trace_lex.txt"));
                }

                p.tokenize(spec.source, lexCb);
            } else {
                return RunResult{};
            }

            if (spec.debug.printLexed) {
                writeFileOrStdout(
                    spec.debugFile("lexed.yaml"),
                    to_string(yamlRepr(p.tokens)) + "\n",
                    spec.debug.printLexedToFile);
            }

            if (spec.tokens.has_value()) {
                Str                   buffer;
                RunResult::LexCompare result = compareTokens(
                    p.tokens,
                    fromFlatTokens<OrgTokenKind>(
                        spec.tokens.value(), buffer),
                    spec.conf.tokenMatch);
                if (!result.isOk) {
                    return RunResult(result);
                }
            }
        }

        { // Parsing
            if (spec.debug.doParse) {
                p.parser->trace = spec.debug.traceParse;
                if (spec.debug.parseToFile) {
                    p.parser->setTraceFile(
                        spec.debugFile("trace_parse.txt"));
                }

                MockFull::ParserMethod parseCb = getParser(
                    spec.parseImplName);

                p.parse(parseCb);

                if (spec.debug.printParsed) {
                    writeFileOrStdout(
                        spec.debugFile("parsed.yaml"),
                        to_string(yamlRepr(p.nodes)) + "\n",
                        spec.debug.printParsedToFile);
                }
            } else {
                return RunResult{};
            }

            if (spec.subnodes.has_value()) {
                Str           buffer;
                OrgNodeGroup  nodes;
                OrgTokenGroup tokens;

                if (spec.tokens.has_value()) {
                    tokens = fromFlatTokens<OrgTokenKind>(
                        spec.tokens.value(), buffer);
                }

                if (spec.subnodes.has_value()) {
                    nodes = fromFlatNodes<OrgNodeKind, OrgTokenKind>(
                        spec.subnodes.value());
                }

                nodes.tokens = &tokens;

                RunResult::NodeCompare result = compareNodes(
                    p.nodes, nodes);
                if (!result.isOk) {
                    return RunResult(result);
                }
            }
        }


        { // Sem conversion
            if (spec.debug.doSem) {
                sem::OrgConverter converter;

                converter.trace = spec.debug.traceParse;
                if (spec.debug.parseToFile) {
                    converter.setTraceFile(
                        spec.debugFile("trace_sem.txt"));
                }

                auto document = converter.toDocument(
                    OrgAdapter(&p.nodes, OrgId(0)));

                if (spec.sem.has_value()) {
                    RunResult::SemCompare result = compareSem(
                        spec, document, spec.sem.value());

                    if (!result.isOk) {
                        return RunResult(result);
                    }
                }
            } else {
                return RunResult{};
            }
        }

        return RunResult();
    }
};
