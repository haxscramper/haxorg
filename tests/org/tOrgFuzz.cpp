#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/Yaml.hpp>
#include "tOrgFuzzUtils.hpp"
#include "tOrgFuzzDomains.hpp"
#include "corpusrunner.hpp"
#include <exporters/ExporterJson.hpp>


void CheckAnyNodeFail(prt::AnyNode const& node) {
    LOG(INFO) << "Run node";
    {
        gpb::util::JsonPrintOptions options;
        options.add_whitespace = true;
        std::string jsonFormatStr;
        std::string textFormatStr = PrintWithTypeName(node);
        (void)gpb::util::MessageToJsonString(
            node, &jsonFormatStr, options);
        writeFile("/tmp/protobuf_dump.json", jsonFormatStr);
        writeFile("/tmp/protobuf_dump.txt", textFormatStr);
    }
    sem::ContextStore generated_context;
    sem::SemId        generated_node = sem::SemId::Nil();
    proto_serde<orgproto::AnyNode, sem::SemId>::read(
        &generated_context,
        node,
        proto_write_accessor<sem::SemId>::for_ref(generated_node));

    sem::Formatter      formatter;
    sem::Formatter::Res generated_layout = formatter.toString(
        generated_node);
    std::string generated_text = formatter.store.toString(
        generated_layout);

    ExporterJson exporter;
    json         converted = exporter.evalTop(generated_node);

    writeFile("/tmp/formatted.org", generated_text);
    ParseSpec spec;
    spec.sem    = converted;
    spec.name   = "fuzz";
    spec.source = generated_text;
    TestParams params{.spec = spec, .file = "<fuzz>"};
    // gtest_run_spec(params);
}

auto seedCorpus = __CURRENT_FILE_DIR__ / "tOrgFuzzSeeds.yaml";
std::vector<std::tuple<prt::AnyNode>> LoadFuzzSeeds() {
    yaml content = YAML::LoadFile(seedCorpus.native());
    std::vector<std::tuple<prt::AnyNode>> result;
    for (auto const& it : content) {
        prt::AnyNode out;
        gpb::TextFormat::ParseFromString(it.as<std::string>(), &out);
        result.push_back({out});
    }
    return result;
}

TEST(OrgParseFuzz, CheckDeterministic) {
    for (auto const& it : LoadFuzzSeeds()) {
        CheckAnyNodeFail(std::get<0>(it));
    }
}

// FUZZ_TEST(OrgParseFuzz, CheckAnyNodeFail)
//     //
//     .WithDomains(GenerateDocumentNode(
//         GenerateNodeContext{}.withOptsUpdate([](GenerateNodeOptions
//         opts) {
//             // opts.enableTrace = true;
//             return opts;
//         })))
//     // .WithSeeds(LoadFuzzSeeds())
//     //
//     ;
