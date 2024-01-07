#pragma once

#include "org_parse_aux.hpp"


#include <string>

#include <lexbase/NodeTest.hpp>
#include <hstd/wrappers/textlayouter.hpp>

inline bool useQFormat() {
    return getenv("IN_QT_RUN")
        && getenv("IN_QT_RUN") == std::string("true");
}

class CorpusRunner {
  public:
    // Define environment variable in the QT app run environment to get
    // better-formatted test diff output.


    void writeFileOrStdout(
        const fs::path&    target,
        std::string const& content,
        bool               useFile);

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
        struct CompareBase {
            bool    isOk = false;
            ColText failDescribe;
        };

        struct NodeCompare : CompareBase {};
        struct LexCompare : CompareBase {};
        struct BaseLexCompare : CompareBase {};
        struct SemCompare : CompareBase {};

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
            BaseLexCompare,
            ExportCompare);

        RunResult() {}
        RunResult(CR<Data> data) : data(data) {}
        Data data;

        bool isOk() const {
            return std::visit(
                overloaded{
                    [](CR<CompareBase> n) { return n.isOk; },
                    [](CR<ExportCompare> e) { return e.isOk(); },
                    [](CR<None> n) { return true; },
                },
                data);
        }
    };


    RunResult::NodeCompare compareNodes(
        CR<OrgNodeGroup> parsed,
        CR<OrgNodeGroup> expected);


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
