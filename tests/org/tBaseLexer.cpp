#include <haxorg/imm/ImmOrgGraph.hpp>
#include <gtest/gtest.h>
#include <haxorg/base_lexer/base_token.hpp>
#include <hstd/stdlib/Json.hpp>
#include <absl/log/log.h>
#include <haxorg/parse/OrgTokenizer.hpp>
#include <haxorg/parse/OrgParser.hpp>
#include <haxorg/sem/SemConvert.hpp>
#include <haxorg/exporters/exporteryaml.hpp>
#include <haxorg/test/corpusrunner.hpp>
#include <haxorg/imm/ImmOrg.hpp>
#include <haxorg/api/SemBaseApi.hpp>
#include <haxorg/serde/SemOrgCereal.hpp>
#include <haxorg/sem/perfetto_org.hpp>
#include "../common.hpp"
#include "hstd/ext/logger.hpp"
#include "tOrgTestCommon.hpp"
#include <hstd/stdlib/VariantFormatter.hpp>
#include <hstd/stdlib/VecFormatter.hpp>
#include <hstd/stdlib/OptFormatter.hpp>
#include <hstd/stdlib/MapFormatter.hpp>


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
        gtest_run_spec(
            TestParams{
                .spec = spec,
                .file = "coverall",
            },
            getDebugDir());

        org::parse::ParseContext ctx;
        auto start = imm::ImmAstContext::init_start_context();
        auto n     = start->init(ctx.parseString(content, file));

        writeFile(
            getDebugFile("imm_repr_subnodes_only.txt"),
            n.getRootAdapter()
                .treeRepr(imm::ImmAdapter::TreeReprConf{})
                .toString(false));


        writeFile(
            getDebugFile("imm_repr_clean.txt"),
            n.getRootAdapter()
                .treeRepr(
                    imm::ImmAdapter::TreeReprConf{
                        .withAuxFields = true,
                    })
                .toString(false));

        writeFile(
            getDebugFile("imm_repr_refl.txt"),
            n.getRootAdapter()
                .treeRepr(
                    imm::ImmAdapter::TreeReprConf{
                        .withAuxFields  = true,
                        .withReflFields = true,
                    })
                .toString(false));

        {
            imm::ImmAdapter::TreeReprConf conf{};
#define __visit_fields(                                                   \
    __field_type,                                                         \
    __field_lowercase,                                                    \
    __field_uppercase,                                                    \
    __parent_qual_type,                                                   \
    __parent_name)                                                        \
    conf.with_field(                                                      \
        &BOOST_PP_REMOVE_PARENS __parent_qual_type::__field_lowercase);

#define __visit_kind(__Kind)                                              \
    EACH_SEM_ORG_##__Kind##_FIELD_WITH_BASE_FIELDS(__visit_fields)

            EACH_SEM_ORG_KIND(__visit_kind);

#undef __visit_kind
#undef __visit_fields

            auto __log_scoped = HSLOG_SINK_FACTORY_SCOPED([&]() {
                return ::hstd::log::init_file_sink(
                    getDebugFile("all_fields.log").native());
            });

            writeFile(
                getDebugFile("imm_repr_with_all_fields.txt"),
                n.getRootAdapter().treeRepr(conf).toString(false));
        }
    }
}

TEST(ManualFileRun, TestDoc1) {
    fs::path file{"/home/haxscramper/tmp/doc1.org"};
    if (fs::exists(file)) {
        auto __log_scoped = HSLOG_SINK_FACTORY_SCOPED([]() {
            return ::hstd::log::init_file_sink(
                getDebugFile("execution_trace.log").native());
        });

        HSLOG_INFO("Send initial message");

        std::string content = readFile(file);
        auto        spec    = ParseSpec::FromSource(std::move(content));
        spec.debug.traceAll = true;
        spec.debug.doFormatReparse = false;
        gtest_run_spec(
            TestParams{
                .spec = spec,
                .file = "doc1",
            },
            getDebugDir());

        auto start = imm::ImmAstContext::init_start_context();
        org::parse::ParseContext ctx;
        auto n = start->init(ctx.parseString(content, file));

        writeFile(
            getDebugFile("TestDoc1_clean.txt"),
            n.getRootAdapter()
                .treeRepr(
                    imm::ImmAdapter::TreeReprConf{
                        .withAuxFields = true,
                    })
                .toString(false));

        writeFile(
            getDebugFile("TestDoc1_refl.txt"),
            n.getRootAdapter()
                .treeRepr(
                    imm::ImmAdapter::TreeReprConf{
                        .withAuxFields  = true,
                        .withReflFields = true,
                    })
                .toString(false));

        writeFile(
            "/tmp/cereal_dump.bin", org::imm::serializeToText(n.context));
    }
}

TEST(ManualFileRun, TestDoc2) {
    fs::path file{"/home/haxscramper/tmp/doc2.org"};
    if (fs::exists(file)) {
        std::string content = readFile(file);
        auto        spec    = ParseSpec::FromSource(std::move(content));
        spec.debug.doFormatReparse = false;
        // spec.debug.printSemToFile         = true;
        spec.debug.debugOutDir = "/tmp/doc2_run";
        gtest_run_spec(
            TestParams{
                .spec = spec,
                .file = "doc2",
            },
            getDebugDir());

        auto start = imm::ImmAstContext::init_start_context();
        org::parse::ParseContext ctx;
        auto n = start->init(ctx.parseString(content, file));
    }
}

TEST(ManualFileRun, TestMain1) {
    fs::path file{"/home/haxscramper/tmp/org_test_dir/main/main.org"};
    if (fs::exists(file)) {
        org::parse::ParseContext ctx;
        auto opts = org::parse::OrgDirectoryParseParameters::shared();

        opts->getParsedNode = [&](std::string const& path) {
            return ctx.parseFile(path);
        };

        auto parsed = ctx.parseFileWithIncludes(file, opts);
    }
}


void test_dir_parsing(fs::path const& dir, bool trace) {
    LOGIC_ASSERTION_CHECK_FMT(fs::exists(dir), "{}", fs::absolute(dir));

    org::parse::ParseContext ctx;
    auto opts = org::parse::OrgDirectoryParseParameters::shared();

    opts->getParsedNode = [&](std::string const& path) {
        fs::path relative = fs::relative(path, dir);
        auto     params   = org::parse::OrgParseParameters::shared();
        if (trace) {
            params->parseTracePath = getDebugFile(
                (relative / "parse_trace.log").native());
            params->baseTokenTracePath = getDebugFile(
                (relative / "base_token_trace.log").native());
            params->tokenTracePath = getDebugFile(
                (relative / "token_trace_path.log").native());
            params->semTracePath = getDebugFile(
                (relative / "sem_trace_path.log").native());
        }

        auto node = ctx.parseFile(path);

        if (trace) {
            writeTreeRepr(
                node, getDebugFile((relative / "node.yaml").native()));

            writeTreeRepr(
                node, getDebugFile((relative / "node.txt").native()));
        }

        return node;
    };

    opts->shouldProcessPath = [](std::string const& path) -> bool {
        if (path.contains(".git") || path.contains(".trunk")) {
            return false;
        } else {
            return true;
        }
    };

    LOG(INFO) << "Parse directory content";
    auto parse = ctx.parseDirectoryOpts(dir, opts);

    if (trace) {
        writeTreeRepr(parse.value(), getDebugFile("parse_sem.yaml"));
    }

    auto initial_context = imm::ImmAstContext::init_start_context();
    auto initial_version = initial_context->addRoot(parse.value());

    if (trace) {
        writeTreeRepr(
            initial_version.getRootAdapter(),
            getDebugFile("parse_imm.txt"));
    }

    LOG(INFO) << "Write tracking debug";
    if (trace) {
        writeFile(
            getDebugFile("graph_tracking.txt"),
            initial_version.getContext()
                ->currentTrack->toString()
                .toString(false));
    }

    LOG(INFO) << "Generating mind map";
    auto conf = org::graph::MapConfig::shared();
    if (trace) { conf->dbg.setTraceFile(getDebugFile("graph_trace.log")); }

    auto graph = org::graph::MapGraphState::FromAstContext(
        initial_version.getContext());
    graph->addNodeRec(
        initial_version.getContext(),
        initial_version.getRootAdapter(),
        conf);
    auto gv = graph->graph->toGraphviz(
        initial_version.getContext(),
        org::graph::MapGraph::GvConfig{
            .acceptNode = [&](org::graph::MapNode const& node) -> bool {
                // return true;
                return 0 < graph->graph->inDegree(node)
                    || 0 < graph->graph->outDegree(node);
            },
        });

    auto const context_path = getDebugFile("context.bin");
    auto const graph_path   = getDebugFile("graph.bin");
    auto const epoch_path   = getDebugFile("epoch.bin");

    {
        __perf_trace("cli", "Serialize initial context to container");
        writeFile(
            context_path,
            org::imm::serializeToText(initial_version.getContext()));
    }

    {
        __perf_trace("cli", "Serialize mind map to container");
        writeFile(graph_path, org::imm::serializeToText(graph->graph));
    }

    {
        __perf_trace("cli", "Serialize current epoch to container");
        writeFile(
            epoch_path,
            org::imm::serializeToText(initial_version.getEpoch()));
    }

    auto deserialized_context = imm::ImmAstContext::init_start_context();
    auto deserialized_version = deserialized_context->getEmptyVersion();

    {
        org::imm::serializeFromText(
            readFile(context_path), deserialized_version.getContext());
    }

    {
        org::imm::serializeFromText(
            readFile(epoch_path), deserialized_version.getEpoch());
    }

    {
        auto graph_tmp = org::graph::MapGraphState::FromAstContext(
            deserialized_context);
        org::imm::serializeFromText(
            readFile(graph_path), graph_tmp->graph);

        EXPECT_EQ(
            graph->graph->edgeCount(), graph_tmp->graph->edgeCount());
        EXPECT_EQ(
            graph->graph->nodeCount(), graph_tmp->graph->nodeCount());
    }

    if (trace) {
        __perf_trace("cli", "Export mind map as graphviz");
        hstd::ext::Graphviz gvc;
        gv.setRankDirection(hstd::ext::Graphviz::Graph::RankDirection::LR);
        gvc.writeFile(getDebugFile("mind_map.dot"), gv);
        gvc.renderToFile(
            getDebugFile("mind_map.png"),
            gv,
            hstd::ext::Graphviz::RenderFormat::PNG,
            hstd::ext::Graphviz::LayoutType::Dot);
    }
}

TEST(ManualFileRun, TestDirCorpus) {
    test_dir_parsing(__CURRENT_FILE_DIR__ / "corpus", true);
}


TEST(ManualFileRun, TestDir1) {
    fs::path dir{"/home/haxscramper/tmp/org_test_dir"};
    if (fs::exists(dir)) {
        test_dir_parsing(dir, is_full_trace_on_cli_enabled());
    }
}
