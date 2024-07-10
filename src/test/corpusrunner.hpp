#pragma once

#include "org_parse_aux.hpp"


#include <string>

#include <test/NodeTest.hpp>
#include <hstd/wrappers/textlayouter.hpp>

/// Whole result of the specification test run
struct TestResult {
    struct File {
        Str  path;
        bool rerun = false;
        BOOST_DESCRIBE_CLASS(File, (), (path, rerun), (), ());
    };

    struct Skip {
        Str msg;
        BOOST_DESCRIBE_CLASS(Skip, (), (msg), (), ());
    };

    struct Fail {
        Str msg;
        BOOST_DESCRIBE_CLASS(Fail, (), (msg), (), ());
    };

    struct Success {
        Str msg;
        BOOST_DESCRIBE_CLASS(Success, (), (msg), (), ());
    };

    Vec<File> debugFiles;

    SUB_VARIANTS(Kind, Data, data, getKind, Skip, Fail, Success);
    Data data;

    BOOST_DESCRIBE_CLASS(TestResult, (), (debugFiles, data), (), ());
};

struct RunContext {};


class CorpusRunner {
  public:
    // Define environment variable in the QT app run environment to get
    // better-formatted test diff output.

    Vec<TestResult::File> files;
    bool                  inRerun = false;

    void writeFile(
        CR<ParseSpec> spec,
        CR<Str>       name,
        CR<Str>       content,
        CR<Str>       relDebug) {
        files.push_back(TestResult::File{
            .path  = name,
            .rerun = inRerun,
        });
        ::writeFile(spec.debugFile(name, relDebug), content);
    }

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
        struct SemCompare : CompareBase {};
        struct Skip {};
        struct None {};

        SUB_VARIANTS(
            Kind,
            Data,
            data,
            getKind,
            None,
            Skip,
            NodeCompare,
            LexCompare,
            SemCompare);

        RunResult() {}
        RunResult(CR<Data> data) : data(data) {}
        Data data;

        bool isSkip() const { return std::holds_alternative<Skip>(data); }

        bool isOk() const {
            return std::visit(
                overloaded{
                    [](CR<CompareBase> n) { return n.isOk; },
                    [](CR<Skip> n) { return true; },
                    [](CR<None> n) { return true; },
                },
                data);
        }
    };


    RunResult::NodeCompare compareNodes(
        CR<OrgNodeGroup> parsed,
        CR<OrgNodeGroup> expected);


    RunResult::SemCompare compareSem(
        CR<ParseSpec>        spec,
        sem::SemId<sem::Org> node,
        json                 expected);

    RunResult runSpec(
        CR<ParseSpec>   spec,
        CR<std::string> from,
        CR<Str>         relDebug);
    RunResult::LexCompare runSpecBaseLex(
        MockFull&     p,
        CR<ParseSpec> spec,
        CR<Str>       relDebug);
    RunResult::LexCompare runSpecLex(
        MockFull&     p,
        CR<ParseSpec> spec,
        CR<Str>       relDebug);
    RunResult::NodeCompare runSpecParse(
        MockFull&     p,
        CR<ParseSpec> spec,
        CR<Str>       relDebug);
    RunResult::SemCompare runSpecSem(
        MockFull&     p,
        CR<ParseSpec> spec,
        CR<Str>       relDebug);
};

struct TestParams {
    ParseSpec   spec;
    fs::path    file;
    std::string testName() const;
    std::string fullName() const;
    void        PrintToImpl(std::ostream* os) const;
    friend void PrintTo(const TestParams& point, std::ostream* os) {
        point.PrintToImpl(os);
    }
};


TestResult gtest_run_spec(CR<TestParams> params);
