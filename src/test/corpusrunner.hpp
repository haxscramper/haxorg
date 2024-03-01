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

    void writeFile(CR<ParseSpec> spec, CR<Str> name, CR<Str> content) {
        files.push_back(TestResult::File{
            .path  = name,
            .rerun = inRerun,
        });
        ::writeFile(spec.debugFile(name), content);
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

    RunResult runSpec(CR<ParseSpec> spec, CR<std::string> from);
    RunResult::LexCompare  runSpecBaseLex(MockFull& p, CR<ParseSpec> spec);
    RunResult::LexCompare  runSpecLex(MockFull& p, CR<ParseSpec> spec);
    RunResult::NodeCompare runSpecParse(MockFull& p, CR<ParseSpec> spec);
    RunResult::SemCompare  runSpecSem(MockFull& p, CR<ParseSpec> spec);
};

struct TestParams {
    ParseSpec spec;
    fs::path  file;

    std::string testName() const {
        std::string final;
        for (char const& ch :
             fmt("{} at {}",
                 spec.name.has_value() ? spec.name.value()
                                       : std::string("<spec>"),
                 file.stem())) {
            if (std::isalnum(ch) || ch == '_') {
                final.push_back(ch);
            } else {
                final.push_back('_');
            }
        }

        return final;
    }

    std::string fullName() const {
        return "$# at $#:$#:$#"
             % to_string_vec(
                   spec.name.has_value() ? spec.name.value()
                                         : std::string("<spec>"),
                   file.stem(),
                   spec.specLocation.line,
                   spec.specLocation.column);
    }

    // Provide a friend overload.
    friend void PrintTo(const TestParams& point, std::ostream* os) {
        json loc;
        loc["path"] = point.file.native();
        loc["line"] = point.spec.specLocation.line;
        loc["col"]  = point.spec.specLocation.column;
        json dump;
        dump["loc"]  = loc;
        dump["name"] = point.spec.name ? json{*point.spec.name} : json{};
        *os << dump.dump();
    }
};


TestResult gtest_run_spec(CR<TestParams> params);
