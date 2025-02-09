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

TEST(ManualFileRun, TestDoc1) {
    {
        fs::path file{"/home/haxscramper/tmp/doc1.org"};
        if (fs::exists(file)) {
            std::string content = readFile(file);
            auto        spec = ParseSpec::FromSource(std::move(content));
            spec.debug.traceAll               = true;
            spec.debug.maxBaseLexUnknownCount = 0;
            gtest_run_spec(TestParams{
                .spec = spec,
                .file = "doc1",
            });

            auto start = org::ImmAstContext::init_start_context();
            auto n     = start->init(sem::parseString(content));

            writeFile(
                "/tmp/TestDoc1_clean.txt",
                n.getRootAdapter()
                    .treeRepr(org::ImmAdapter::TreeReprConf{
                        .withAuxFields = true,
                    })
                    .toString(false));

            writeFile(
                "/tmp/TestDoc1_refl.txt",
                n.getRootAdapter()
                    .treeRepr(org::ImmAdapter::TreeReprConf{
                        .withAuxFields  = true,
                        .withReflFields = true,
                    })
                    .toString(false));
        }
    }
    LOG(INFO) << "doc1.org ok";
    {
        fs::path file{"/home/haxscramper/tmp/doc2.org"};
        if (fs::exists(file)) {
            std::string content = readFile(file);
            auto        spec = ParseSpec::FromSource(std::move(content));
            spec.debug.maxBaseLexUnknownCount = 0;
            spec.debug.doFormatReparse        = false;
            // spec.debug.printSemToFile         = true;
            spec.debug.debugOutDir = "/tmp/doc2_run";
            gtest_run_spec(TestParams{
                .spec = spec,
                .file = "doc2",
            });

            auto start = org::ImmAstContext::init_start_context();
            auto n     = start->init(sem::parseString(content));
        }
    }
}

TEST(ManualFileRun, TestDir1) {
    fs::path dir{"/home/haxscramper/tmp/org_test_dir"};
    if (fs::exists(dir)) {
        sem::OrgDirectoryParseParameters opts;

        opts.getParsedNode = [&](std::string const& path) {
            return sem::parseFile(path, sem::OrgParseParameters{});
        };

        opts.shouldProcessPath = [](std::string const& path) -> bool {
            if (path.contains(".git") || path.contains(".trunk")) {
                return false;
            } else {
                return true;
            }
        };

        auto parse = sem::parseDirectoryOpts(dir, opts);
        auto ctx   = org::ImmAstContext::init_start_context();
        auto root  = ctx->addRoot(parse.value());

        org::graph::MapConfig     conf;
        org::graph::MapGraphState graph{ctx};
        org::graph::addNodeRec(graph, root.getRootAdapter(), conf);
        auto gv = graph.graph.toGraphviz(
            ctx,
            org::graph::MapGraph::GvConfig{
                .acceptNode =
                    [&](org::graph::MapNode const& node) -> bool {
                    return true;
                    // return 0 < graph.graph.inDegree(node)
                    //     || 0 < graph.graph.outDegree(node);
                },
            });
        Graphviz gvc;
        gv.setRankDirection(Graphviz::Graph::RankDirection::LR);
        gvc.writeFile("/tmp/TestDir.dot", gv);
        gvc.renderToFile(
            "/tmp/TestDir.png",
            gv,
            Graphviz::RenderFormat::PNG,
            Graphviz::LayoutType::Sfdp);
    }
}
