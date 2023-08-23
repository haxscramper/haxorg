#include "corpusrunner.hpp"

#include <parse/OrgParser.hpp>
#include <parse/OrgTokenizer.hpp>
#include <lexbase/NodeIO.hpp>
#include <lexbase/NodeTest.hpp>
#include <sem/ErrorWrite.hpp>
#include <gtest/gtest.h>
#include <QDirIterator>
#include <QCoreApplication>

#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/Debug.hpp>
#include <sem/SemConvert.hpp>
#include <exporters/exporternlp.hpp>
#include <exporters/exporterlangtool.hpp>

#include <fnmatch.h>
#include <ranges>

namespace rs = std::views;

// std::string corpusGlob = "*text.yaml";
std::string corpusGlob = "";

struct BaseHttpContext {
    MockFull          parser;
    sem::ContextStore store;
    sem::OrgConverter converter;

    sem::SemId             node = sem::SemId::Nil();
    QFileInfo              jsonCacheLocation;
    SPtr<HttpDataProvider> http;

    BaseHttpContext(bool a, bool b, QFileInfo path)
        : parser(a, b), converter(&store), jsonCacheLocation(path) {}

    void setup(QString data) {
        parser.run(data, &OrgTokenizer::lexGlobal, &OrgParser::parseFull);

        node = converter.toDocument(OrgAdapter(&parser.nodes, OrgId(0)));

        http                 = std::make_shared<HttpDataProvider>();
        http->isCacheEnabled = true;

        if (http->isCacheEnabled && jsonCacheLocation.exists()) {
            http->addCache(
                json::parse(readFile(jsonCacheLocation).toStdString()));
        }
    }

    void finish() {
        if (http->isCacheEnabled) {
            writeFile(
                jsonCacheLocation,
                QString::fromStdString(
                    to_compact_json(http->toJsonCache())));
        }
    }
};

struct NlpTestContext : BaseHttpContext {
    ExporterNLP nlp;

    NlpTestContext()
        : BaseHttpContext(
            false,
            false,
            QFileInfo{__CURRENT_FILE_DIR__ / "corpus/nlp-cache.json"_qs})
        , nlp{QUrl("http://localhost:9000")} {}


    void runWith(QString data) {
        char*            argv[] = {""};
        int              argc   = 1;
        QCoreApplication app(argc, argv);

        setup(data);

        nlp.visitTop(node);
        nlp.executeRequests(http);

        finish();
    }
};

struct LangtoolTestContext : BaseHttpContext {
    ExporterLangtool lang;

    LangtoolTestContext()
        : BaseHttpContext(
            false,
            false,
            QFileInfo{
                __CURRENT_FILE_DIR__ / "corpus/langtool-cache.json"_qs}) {}


    void runWith(QString data) {
        char*            argv[] = {""};
        int              argc   = 1;
        QCoreApplication app(argc, argv);

        setup(data);

        lang.visitTop(node);
        lang.executeRequests(QUrl("http://localhost:8081/v2/check"), http);

        finish();
    }
};

TEST(NLP, BaseMockApi) {
    NlpTestContext ctx;
    ctx.runWith(
        "In this example, we create three nodes n1, n2, and n3 in the "
        "main graph g. We then create a subgraph subg and set its "
        "rank attribute to same. Afterward, we add the existing nodes n1 "
        "and n2 to the subgraph.");
    Graphviz gvc;

    NLP::SenGraph& graph = ctx.nlp.exchange.at(0).second.parsed;
    auto gv = graph.toGraphviz(NLP::SenGraph::GvFormat::DependenciesOnly);
    gvc.renderToFile("/tmp/sentence.png", gv);
    gvc.renderToFile("/tmp/sentence.gv", gv, Graphviz::RenderFormat::DOT);

    using namespace NLP::builder;
    using POS = NLP::SenNode::PosTag;
    using REL = NLP::SenEdge::DepKind;

    auto result = graph.findMatches(
        rel::Dir(Tag(POS::VBP), Tag(POS::PRP), REL::nsubj));
    qDebug() << "Resfsd";
}

TEST(NLP, LangtoolTestContextBaseApi) {
    LangtoolTestContext ctx;
    ctx.runWith(
        "In this example, we create three nodes n1, n2, and n3 in the "
        "main graph g. We then create a subgraph subg and set its "
        "rank attribute to same. Afterward, we add the existing nodes n1 "
        "and n2 to the subgraph.");

    qDebug() << "Resfsd";
}

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
    TestParams params      = GetParam();
    auto&      spec        = params.spec;
    spec.debug.debugOutDir = "/tmp/corpus_runs/" + params.testName();
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

        for (auto& exporter : spec.exporters) {
            exporter.doTrace     = true;
            exporter.print       = true;
            exporter.printToFile = true;
        }

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
