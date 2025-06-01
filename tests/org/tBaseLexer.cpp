#include <haxorg/sem/ImmOrgGraph.hpp>
#include <gtest/gtest.h>
#include <haxorg/base_lexer/base_token.hpp>
#include <hstd/stdlib/Json.hpp>
#include <absl/log/log.h>
#include <haxorg/parse/OrgTokenizer.hpp>
#include <haxorg/parse/OrgParser.hpp>
#include <haxorg/sem/SemConvert.hpp>
#include <haxorg/exporters/exporteryaml.hpp>
#include <haxorg/test/corpusrunner.hpp>
#include <haxorg/sem/ImmOrg.hpp>
#include <haxorg/sem/SemBaseApi.hpp>
#include <haxorg/sem/SemOrgCereal.hpp>
#include <haxorg/sem/perfetto_org.hpp>

using namespace hstd;
using namespace org::test;
using namespace org;

TEST(ManualFileRun, TestCoverallOrg) {
    {
        fs::path file{
            __CURRENT_FILE_DIR__ / "corpus" / "org"
            / "py_validated_all.org"};
        std::string content = readFile(file);
        auto        spec    = ParseSpec::FromSource(std::move(content));
        spec.debug.traceAll = true;
        spec.debug.doFormatReparse = false;
        gtest_run_spec(TestParams{
            .spec = spec,
            .file = "coverall",
        });

        auto start = imm::ImmAstContext::init_start_context();
        auto n     = start->init(org::parseString(content));

        writeFile(
            "/tmp/TestDoc1_clean.txt",
            n.getRootAdapter()
                .treeRepr(imm::ImmAdapter::TreeReprConf{
                    .withAuxFields = true,
                })
                .toString(false));

        writeFile(
            "/tmp/TestDoc1_refl.txt",
            n.getRootAdapter()
                .treeRepr(imm::ImmAdapter::TreeReprConf{
                    .withAuxFields  = true,
                    .withReflFields = true,
                })
                .toString(false));
    }
}

TEST(ManualFileRun, TestDoc1) {
    {
        fs::path file{"/home/haxscramper/tmp/doc1.org"};
        if (fs::exists(file)) {
            std::string content = readFile(file);
            auto        spec = ParseSpec::FromSource(std::move(content));
            spec.debug.traceAll        = true;
            spec.debug.doFormatReparse = false;
            gtest_run_spec(TestParams{
                .spec = spec,
                .file = "doc1",
            });

            auto start = imm::ImmAstContext::init_start_context();
            auto n     = start->init(org::parseString(content));

            writeFile(
                "/tmp/TestDoc1_clean.txt",
                n.getRootAdapter()
                    .treeRepr(imm::ImmAdapter::TreeReprConf{
                        .withAuxFields = true,
                    })
                    .toString(false));

            writeFile(
                "/tmp/TestDoc1_refl.txt",
                n.getRootAdapter()
                    .treeRepr(imm::ImmAdapter::TreeReprConf{
                        .withAuxFields  = true,
                        .withReflFields = true,
                    })
                    .toString(false));

            writeFile(
                "/tmp/cereal_dump.bin",
                org::imm::serializeToText(n.context));
        }
    }
    LOG(INFO) << "doc1.org ok";
    {
        fs::path file{"/home/haxscramper/tmp/doc2.org"};
        if (fs::exists(file)) {
            std::string content = readFile(file);
            auto        spec = ParseSpec::FromSource(std::move(content));
            spec.debug.doFormatReparse = false;
            // spec.debug.printSemToFile         = true;
            spec.debug.debugOutDir = "/tmp/doc2_run";
            gtest_run_spec(TestParams{
                .spec = spec,
                .file = "doc2",
            });

            auto start = imm::ImmAstContext::init_start_context();
            auto n     = start->init(org::parseString(content));
        }
    }
}

TEST(ManualFileRun, TestMain1) {
    fs::path file{"/home/haxscramper/tmp/org_test_dir/main/main.org"};
    if (fs::exists(file)) {
        auto opts = OrgDirectoryParseParameters::shared();

        opts->getParsedNode = [&](std::string const& path) {
            return parseFile(path, org::OrgParseParameters::shared());
        };

        auto parsed = parseFileWithIncludes(file, opts);
    }
}


TEST(ManualFileRun, TestDir1) {
    fs::path dir{"/home/haxscramper/tmp/org_test_dir"};
    if (fs::exists(dir)) {
        auto opts = org::OrgDirectoryParseParameters::shared();

        opts->getParsedNode = [&](std::string const& path) {
            return org::parseFile(path, org::OrgParseParameters::shared());
        };

        opts->shouldProcessPath = [](std::string const& path) -> bool {
            if (path.contains(".git") || path.contains(".trunk")) {
                return false;
            } else {
                return true;
            }
        };

        LOG(INFO) << "Parse directory content";
        auto parse           = org::parseDirectoryOpts(dir, opts);
        auto initial_context = imm::ImmAstContext::init_start_context();
        auto root            = initial_context->addRoot(parse.value());

        LOG(INFO) << "Write tracking debug";
        writeFile(
            "/tmp/TestDirTracking.txt",
            root.context->currentTrack->toString().toString(false));

        LOG(INFO) << "Generating mind map";
        auto conf = org::graph::MapConfig::shared();
        // conf.setTraceFile("/tmp/TestDirMindMapTrace.log");
        auto graph = org::graph::MapGraphState::FromAstContext(
            root.context);
        graph->addNodeRec(root.context, root.getRootAdapter(), conf);
        auto gv = graph->graph->toGraphviz(
            root.context,
            org::graph::MapGraph::GvConfig{
                .acceptNode =
                    [&](org::graph::MapNode const& node) -> bool {
                    // return true;
                    return 0 < graph->graph->inDegree(node)
                        || 0 < graph->graph->outDegree(node);
                },
            });

        {
            __perf_trace("cli", "Serialize initial context to container");
            writeFile(
                "/tmp/dir1_msgpack.bin",
                org::imm::serializeToText(initial_context));
        }

        {
            __perf_trace("cli", "Serialize mind map to container");
            writeFile(
                "/tmp/dir1_graph_msgpack.bin",
                org::imm::serializeToText(graph->graph));

            _dfmt(graph->graph->nodeCount(), graph->graph->edgeCount());

            auto graph_tmp = org::graph::MapGraphState::FromAstContext(
                root.context);
            org::imm::serializeFromText(
                readFile("/tmp/dir1_graph_msgpack.bin"), graph_tmp->graph);
        }

        {
            __perf_trace("cli", "Export mind map as graphviz");
            hstd::ext::Graphviz gvc;
            gv.setRankDirection(
                hstd::ext::Graphviz::Graph::RankDirection::LR);
            gvc.writeFile("/tmp/TestDir.dot", gv);
            gvc.renderToFile(
                "/tmp/TestDir.png",
                gv,
                hstd::ext::Graphviz::RenderFormat::PNG,
                hstd::ext::Graphviz::LayoutType::Dot);
        }
    }
}
