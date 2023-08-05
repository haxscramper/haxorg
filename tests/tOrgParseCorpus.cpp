#include "org_parse_aux.hpp"
#include "corpusrunner.hpp"

#include <parse/OrgParser.hpp>
#include <parse/OrgTokenizer.hpp>
#include <lexbase/NodeIO.hpp>
#include <lexbase/NodeTest.hpp>
#include <sem/ErrorWrite.hpp>
#include <gtest/gtest.h>
#include <QDirIterator>

#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/Debug.hpp>
#include <sem/SemConvert.hpp>

#include <fnmatch.h>
#include <ranges>

namespace rs = std::views;

// std::string corpusGlob = "*text.yaml";
std::string corpusGlob = "";

struct TestParams {
    ParseSpec spec;
    QFileInfo file;

    QString testName() const {
        QString final;
        for (QChar const& ch : fullName()) {
            if (ch.isDigit() || ch.isLetter() || ch == '_') {
                final.push_back(ch);
            } else {
                final.push_back('_');
            }
        }

        return final;
    }

    QString fullName() const {
        return "$# at $#:$#:$#"
             % to_string_vec(
                   spec.name.has_value() ? spec.name.value()
                                         : QString("<spec>"),
                   file.fileName(),
                   spec.specLocation.line,
                   spec.specLocation.column);
    }

    // Provide a friend overload.
    friend void PrintTo(const TestParams& point, std::ostream* os) {
        *os << point.fullName().toStdString();
    }
};

class ParseFile : public ::testing::TestWithParam<TestParams> {};

Vec<TestParams> generateTestRuns() {
    Vec<TestParams> results;
    QDirIterator    it(
        __CURRENT_FILE_DIR__ / "corpus"_qs, QDirIterator::Subdirectories);

    auto addSpecs = [&](QFileInfo const& path) {
        try {
            YAML::Node group = YAML::LoadFile(
                path.filePath().toStdString());
            ParseSpecGroup parsed{group, path.filePath()};
            for (const auto& spec : parsed.specs) {
                results.push_back({spec, path});
            }
        } catch (YAML::Exception& ex) {
            qFatal() << ex.what() << "at" << path.filePath();
        }
    };

    while (it.hasNext()) {
        QFileInfo path{it.next()};
        if (path.isFile() && path.fileName().endsWith(".yaml")) {
            std::string p = path.filePath().toStdString();
            if (corpusGlob.empty()) {
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


std::string getTestName(
    const testing::TestParamInfo<ParseFile::ParamType>& info) {
    return info.param.testName().toStdString();
}

TEST_P(ParseFile, CorpusAll) {
    TestParams   params = GetParam();
    auto&        spec   = params.spec;
    CorpusRunner runner;
    using RunResult  = CorpusRunner::RunResult;
    RunResult result = runner.runSpec(spec, params.file.filePath());

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

        RunResult fail = runner.runSpec(spec, params.file.filePath());
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
                   << os.toString(false).toStdString();
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
