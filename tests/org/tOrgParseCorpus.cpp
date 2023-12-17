#include "corpusrunner.hpp"

import org.parse.OrgParser;
import org.parse.OrgTokenizer;
import org.lexbase.NodeIO;
import org.lexbase.NodeTest;
import org.sem.ErrorWrite;
#include <gtest/gtest.h>

import hstd.stdlib.Filesystem;
import hstd.stdlib.Debug;
import org.sem.SemConvert;

#include <fnmatch.h>
#include "../testprofiler.hpp"

import std.wrappers.perfetto_aux;

// std::string corpusGlob = "*text.yaml";
std::string corpusGlob = "";

struct TestParams {
    ParseSpec spec;
    fs::path  file;

    std::string testName() const {
        std::string final;
        for (char const& ch : fullName()) {
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
        *os << point.fullName();
    }
};

Vec<TestParams> generateTestRuns() {
    Vec<TestParams> results;

    auto addSpecs = [&](fs::path const& path) {
        try {
            YAML::Node     group = YAML::LoadFile(path.native());
            ParseSpecGroup parsed{
                group, path.native(), __CURRENT_FILE_DIR__ / "corpus"};
            for (const auto& spec : parsed.specs) {
                results.push_back({spec, path});
            }
        } catch (YAML::Exception& ex) {
            LOG(ERROR) << ex.what() << "at" << path.native();
        }
    };

    LOG(INFO) << "Searching for corpus tests in " << __CURRENT_FILE_DIR__;

    for (fs::directory_entry const& it : fs::recursive_directory_iterator(
             __CURRENT_FILE_DIR__ / "corpus")) {
        fs::path path{it.path()};
        if (fs::is_regular_file(path)
            && path.native().ends_with(".yaml")) {
            std::string p = path.native();
            if (corpusGlob.empty()) {
                LOG(INFO) << "Adding " << p;
                addSpecs(path);
            } else {
                int matchRes = fnmatch(
                    corpusGlob.c_str(), p.c_str(), FNM_EXTMATCH);
                if (!(matchRes == FNM_NOMATCH)) {
                    addSpecs(path);
                }
            }
        }
    }

    for (auto& spec : results) {
        if (spec.spec.debug.debugOutDir.size() == 0) {
            spec.spec.debug.debugOutDir = "/tmp/corpus_runs/"
                                        + spec.testName();
        }
    }

    return results;
}

class ParseFile : public ::testing::TestWithParam<TestParams> {
  protected:
    Opt<TestProfiler> profiler;


    void SetUp() override {
        profiler = TestProfiler{
            ("/tmp/" + GetParam().testName() + "_xray"),
            ("/tmp/" + GetParam().testName() + "_pgo"),
            json::object({
                {"meta", GetParam().fullName()},
            })};
        profiler->SetUp();
    }
    void TearDown() override { profiler->TearDown(); }
};


std::string getTestName(
    const testing::TestParamInfo<ParseFile::ParamType>& info) {
    return info.param.testName();
}


TEST_P(ParseFile, CorpusAll) {
    TestParams params      = GetParam();
    auto&      spec        = params.spec;
    spec.debug.debugOutDir = "/tmp/corpus_runs/" + params.testName();
    CorpusRunner runner;
    using RunResult  = CorpusRunner::RunResult;
    RunResult result = runner.runSpec(spec, params.file.native());

    if (result.isOk()
        && !(spec.debug.doLex && spec.debug.doParse && spec.debug.doSem)) {
        GTEST_SKIP() << "Partially covered test: "
                     << (spec.debug.doLex ? "" : "lex is disabled ")     //
                     << (spec.debug.doParse ? "" : "parse is disabled ") //
                     << (spec.debug.doSem ? "" : "sem is disabled ");
    } else if (result.isOk()) {
        SUCCEED();
    } else {
        spec.debug = ParseSpec::Dbg{
            .debugOutDir       = "/tmp/corpus_runs/" + params.testName(),
            .traceLex          = true,
            .traceParse        = true,
            .traceSem          = true,
            .lexToFile         = true,
            .parseToFile       = true,
            .semToFile         = true,
            .printLexed        = true,
            .printParsed       = true,
            .printSource       = true,
            .printLexedToFile  = true,
            .printParsedToFile = true,
            .printSemToFile    = true,
        };

        for (auto& exporter : spec.exporters) {
            exporter.doTrace     = true;
            exporter.print       = true;
            exporter.printToFile = true;
        }

        RunResult fail = runner.runSpec(spec, params.file.native());
        ColText   os;

        std::visit(
            overloaded{
                [&](RunResult::NodeCompare const& node) {
                    os = node.failDescribe;
                },
                [&](RunResult::LexCompare const& node) {
                    os = node.failDescribe;
                },
                [&](RunResult::SemCompare const& node) {
                    os = node.failDescribe;
                },
                [&](RunResult::ExportCompare const& node) {
                    for (auto const& exp : node.run) {
                        os.append(exp.failDescribe);
                        os.append(ColText("\n"));
                    }
                },
                [&](RunResult::None const& node) {},
            },
            fail.data);

        writeFile(spec.debugFile("failure.txt"), os.toString(false));

        // for copy-pasting to the run parameters in qt creator
        writeFile(
            spec.debugFile("qt_run.txt"),
            "--gtest_filter='CorpusAllParametrized/ParseFile.CorpusAll/"
                + params.testName() + "'");

        if (runner.useQFormat()) {
            FAIL() << params.fullName() << "failed, wrote debug to"
                   << spec.debug.debugOutDir << "\n"
                   << os.toString(false);
        } else {
            FAIL() << params.fullName() << " failed, , wrote debug to "
                   << spec.debug.debugOutDir;
        }
    }
}

INSTANTIATE_TEST_CASE_P(
    CorpusAllParametrized,
    ParseFile,
    ::testing::ValuesIn(generateTestRuns()),
    getTestName);
