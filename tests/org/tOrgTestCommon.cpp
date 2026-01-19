#include "tOrgTestCommon.hpp"
#include <haxorg/exporters/exporteryaml.hpp>
#include <haxorg/test/corpusrunner.hpp>
#include <hstd/stdlib/VariantFormatter.hpp>
#include <hstd/stdlib/VecFormatter.hpp>
#include <hstd/stdlib/OptFormatter.hpp>
#include <hstd/stdlib/MapFormatter.hpp>

bool enableFullTraceOnCli = false;
void enable_full_trace_on_cli() { enableFullTraceOnCli = true; }
bool is_full_trace_on_cli_enabled() { return enableFullTraceOnCli; }


void writeTreeRepr(
    imm::ImmAdapter               n,
    fs::path const&               path,
    imm::ImmAdapter::TreeReprConf conf) {
    writeFile(path, n.treeRepr(conf).toString(false));
}


void writeTreeRepr(sem::SemId<sem::Org> node, fs::path const& full) {
    if (full.native().ends_with("yaml")) {
        org::algo::ExporterYaml exp{};
        auto                    yaml_result = exp.eval(node);
        writeFile(full, fmt1(yaml_result));
    } else if (full.native().ends_with("json")) {
        org::algo::ExporterJson exp{};
        auto                    json_result = exp.eval(node);
        writeFile(full, json_result.dump(2));
    } else {
        writeFile(
            full, org::algo::ExporterTree::treeRepr(node).toString(false));
    }
}


sem::SemId<sem::Org> testParseString(
    const std::string&         text,
    std::optional<std::string> debug) {
    org::test::MockFull p{"<test>", debug.has_value(), debug.has_value()};
    sem::OrgConverter   converter{};
    org::parse::LexerParams params;
    if (debug) {
        p.tokenizer->setTraceFile(
            fs::path{debug.value() + "_tokenizer_trace.log"});
        p.parser->setTraceFile(
            fs::path{debug.value() + "_parser_trace.log"});
        converter.setTraceFile(fs::path{debug.value() + "_sem_trace.log"});
        p.parser->traceColored    = false;
        p.tokenizer->traceColored = false;
        params.setTraceFile(fs::path{debug.value() + "_lex_trace.log"});
        p.tokenizeBase(
            text,
            params,
            p.parseContext->addSource("<mock-full-run>", text));

        writeFile(
            fs::path{debug.value() + "_base_lexed.yaml"},
            std::format("{}", org::test::yamlRepr(p.baseTokens)));
    } else {
        p.tokenizeBase(
            text,
            params,
            p.parseContext->addSource("<mock-full-run>", text));
    }

    p.tokenizeConvert();

    if (debug) {
        writeFile(
            fs::path{debug.value() + "_lexed.yaml"},
            std::format("{}", org::test::yamlRepr(p.tokens)));
    }

    p.parse();

    if (debug) {
        std::stringstream buffer;
        ColStream         os{buffer};
        os.colored = false;

        auto writeImpl = org::test::getOrgParseWriteParams(
            p.spec.get(), &p.nodes, nullptr);

        org::parse::OrgAdapter(&p.nodes, org::parse::OrgId(0))
            .treeRepr(
                os,
                0,
                org::parse::OrgNodeGroup::TreeReprConf{
                    .customWrite = writeImpl});

        writeFile(
            fs::path{debug.value() + "_parse_tree.txt"}, buffer.str());
    }

    auto res = converter
                   .convertDocument(
                       org::parse::OrgAdapter(
                           &p.nodes, org::parse::OrgId(0)))
                   .value();

    if (debug) {
        ColStream               os;
        org::algo::ExporterTree tree{os};
        tree.conf.withLineCol     = true;
        tree.conf.withOriginalId  = true;
        tree.conf.skipEmptyFields = false;
        tree.evalTop(res);

        writeFile(
            fs::path{debug.value()} + "_sem_tree.txt", os.toString(false));

        org::algo::ExporterYaml exp{};
        auto                    yaml_result = exp.eval(res);
        writeFile(
            fs::path{debug.value()} + "_sem_tree.yaml", fmt1(yaml_result));
    }

    return res;
}

void show_compare_reports(const Vec<compare_report>& out) {
    std::string buffer;
    for (auto const& it : out) {
        std::string ctx = it.context
                        | rv::transform(
                              [](compare_context const& c) -> std::string {
                                  return fmt("{}.{}", c.type, c.field);
                              })
                        | rv::intersperse("->") //
                        | rv::join              //
                        | rs::to<std::string>();

        buffer += fmt(
            "{} failed: original != parsed\n{}\n",
            ctx,
            hstd::indent(it.message, 2));
    }

    if (!out.empty()) {
        auto path = getDebugFile("changes.txt");
        ADD_FAILURE() << "Found differences in value wrote report to "
                      << path;
        writeFile(path, buffer);
    }
}
