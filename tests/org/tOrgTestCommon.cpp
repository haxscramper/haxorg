#include "tOrgTestCommon.hpp"

Str getDebugFile(const Str& suffix) {
    auto dir = fs::path{
        fmt("/tmp/haxorg_tests/{}",
            ::testing::UnitTest::GetInstance()
                ->current_test_info()
                ->test_suite_name())};
    if (!fs::is_directory(dir)) { createDirectory(dir); }
    return fmt(
        "{}/{}/{}",
        dir.native(),
        ::testing::UnitTest::GetInstance()->current_test_info()->name(),
        suffix);
}

void writeTreeRepr(
    org::ImmAdapter               n,
    const Str                     suffix,
    org::ImmAdapter::TreeReprConf conf) {
    writeFile(getDebugFile(suffix), n.treeRepr(conf).toString(false));
}

sem::SemId<sem::Org> testParseString(
    const std::string&         text,
    std::optional<std::string> debug) {
    MockFull          p{debug.has_value(), debug.has_value()};
    sem::OrgConverter converter{};
    LexerParams       params;
    params.maxUnknown = 1;
    if (debug) {
        fs::path tokenizer_trace{debug.value() + "_tokenizer_trace.txt"};
        fs::path parser_trace{debug.value() + "_parser_trace.txt"};
        fs::path sem_trace{debug.value() + "_sem_trace.txt"};
        fs::path lex_trace{debug.value() + "_lex_trace.txt"};
        p.tokenizer->setTraceFile(tokenizer_trace);
        p.parser->setTraceFile(parser_trace);
        converter.setTraceFile(sem_trace);
        p.parser->traceColored    = false;
        p.tokenizer->traceColored = false;
        std::ofstream fileTrace{lex_trace.c_str()};

        params.traceStream = &fileTrace;
        p.tokenizeBase(text, params);
    } else {
        p.tokenizeBase(text, params);
    }

    p.tokenizeConvert();
    p.parse();

    if (debug) {
        std::stringstream buffer;
        ColStream         os{buffer};
        os.colored = false;
        OrgAdapter(&p.nodes, OrgId(0))
            .treeRepr(os, 0, OrgNodeGroup::TreeReprConf{});

        writeFile(
            fs::path{debug.value() + "_parse_tree.txt"}, buffer.str());
    }

    auto res = converter.toDocument(OrgAdapter(&p.nodes, OrgId(0)));

    if (debug) {
        ColStream    os;
        ExporterTree tree{os};
        tree.conf.withLineCol     = true;
        tree.conf.withOriginalId  = true;
        tree.conf.skipEmptyFields = false;
        tree.evalTop(res);

        writeFile(
            fs::path{debug.value()} + "_sem_tree.txt", os.toString(false));
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
