#pragma once

#include "org_parse_aux.hpp"

#include <cstdlib>
#include <string>

#include <lexbase/NodeTest.hpp>
#include <hstd/wrappers/textlayouter.hpp>

struct QFileInfo;


class CorpusRunner {
  public:
    // Define environment variable in the QT app run environment to get
    // better-formatted test diff output.
    bool useQFormat() { return getenv("IN_QT_RUN") == "true"; }

    void writeFileOrStdout(
        QFileInfo const&   target,
        std::string const& content,
        bool               useFile);

    MockFull::ParserMethod getParser(CR<Str> name);
    MockFull::LexerMethod  getLexer(CR<Str> name);

    struct ExportResult {
        struct Plaintext {
            std::string text;
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
        layout::BlockStore&       b,
        layout::BlockId           block,
        Func<Str(layout::LytStr)> getStr);


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
                return run.empty()
                    || std::all_of(run.begin(), run.end(), [](CR<Run> r) {
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

    RunResult runSpec(CR<ParseSpec> spec, CR<std::string> from);

    ExportResult runExporter(
        ParseSpec const&                 spec,
        sem::SemId                       top,
        ParseSpec::ExporterExpect const& exp);

    RunResult::ExportCompare::Run compareExport(
        ParseSpec::ExporterExpect const& exp,
        ExportResult const&              result);
};
