#include "tOrgTestCommon.hpp"
#include <haxorg/exporters/exporteryaml.hpp>
#include <haxorg/test/corpusrunner.hpp>

void writeTreeRepr(
    imm::ImmAdapter               n,
    const Str                     suffix,
    imm::ImmAdapter::TreeReprConf conf) {
    writeFile(getDebugFile(suffix), n.treeRepr(conf).toString(false));
}


void writeTreeRepr(sem::SemId<sem::Org> node, CR<Str> full) {
    if (full.ends_with("yaml")) {
        org::algo::ExporterYaml exp{};
        auto                    yaml_result = exp.eval(node);
        writeFile(full.toBase(), fmt1(yaml_result));
    } else if (full.ends_with("json")) {
        org::algo::ExporterJson exp{};
        auto                    json_result = exp.eval(node);
        writeFile(full.toBase(), json_result.dump(2));
    } else {
        writeFile(
            full.toBase(),
            org::algo::ExporterTree::treeRepr(node).toString(false));
    }
}


sem::SemId<sem::Org> testParseString(
    const std::string&         text,
    std::optional<std::string> debug) {
    org::test::MockFull     p{debug.has_value(), debug.has_value()};
    sem::OrgConverter       converter{};
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
        p.tokenizeBase(text, params);

        writeFile(
            fs::path{debug.value() + "_base_lexed.yaml"},
            std::format("{}", org::test::yamlRepr(p.baseTokens)));
    } else {
        p.tokenizeBase(text, params);
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
                   .convertDocument(org::parse::OrgAdapter(
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
    for (auto const& it : out) {
        std::string ctx = it.context
                        | rv::transform(
                              [](compare_context const& c) -> std::string {
                                  return fmt("{}.{}", c.type, c.field);
                              })
                        | rv::intersperse("->") //
                        | rv::join              //
                        | rs::to<std::string>();

        ADD_FAILURE() << fmt(
            "{} failed: original != parsed {}", ctx, it.message);
    }
}
