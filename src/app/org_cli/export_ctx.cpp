#include "export_ctx.hpp"

#include "haxorg/exporters/ExporterJson.hpp"
#include "haxorg/exporters/exporteryaml.hpp"
#include "src/haxorg/imm/ImmOrgGraph.pb.h"
#include "src/haxorg/serde/OrgApiProto.pb.h"
#include "src/haxorg/serde/SemOrgProto.pb.h"
#include <google/protobuf/util/json_util.h>
#include <haxorg/imm/ImmOrgGraph.hpp>
#include <haxorg/sem/perfetto_org.hpp>
#include <hstd/ext/logger.hpp>


org::parse::OrgParseParameters::Ptr org::cli::ExportCommandContext::paramsForPath(
    SharedContext&     shared,
    std::string const& path) {
    auto params = org::parse::OrgParseParameters::shared();

    params->onDiagnosticsCollected = std::bind_front(
        &ExportCommandContext::onDiagnosticsCollected, this, std::ref(shared));

    if (std::holds_alternative<CliOpts::ExportOpts::Token>(cmd.data)) {
        params->onTokenizerDone = std::bind_front(
            &ExportCommandContext::onTokenizerDone, this, path);
    } else if (std::holds_alternative<CliOpts::ExportOpts::BaseToken>(cmd.data)) {
        params->onBaseTokenizeDone = std::bind_front(
            &ExportCommandContext::onBaseTokenizerDone, this, path);
    } else if (std::holds_alternative<CliOpts::ExportOpts::ParseNode>(cmd.data)) {
        params->onParseDone = std::bind_front(
            &ExportCommandContext::onParseDone, this, path);
    }

    return params;
}


void org::cli::ExportCommandContext::exportJson(
    org::sem::SemId<org::sem::Org> const& node,
    CliOpts::ExportOpts::Json const&      options) const {
    org::algo::ExporterJson exporter;
    exporter.skipEmptyLists  = options.skipEmptyLists;
    exporter.skipId          = options.skipId;
    exporter.skipLocation    = options.skipLocation;
    exporter.skipNullFields  = options.skipNullFields;
    exporter.normalizeSpaces = options.normalizeSpaces;

    auto result = exporter.evalTop(node);
    hstd::writeFile(cmd.output, result.dump(2), true);
}

void org::cli::ExportCommandContext::exportYaml(
    org::sem::SemId<org::sem::Org> const& node,
    CliOpts::ExportOpts::Yaml const&      options) const {
    org::algo::ExporterYaml exporter;
    exporter.skipNullFields  = options.skipNullFields;
    exporter.skipFalseFields = options.skipFalseFields;
    exporter.skipZeroFields  = options.skipZeroFields;
    exporter.skipLocation    = options.skipLocation;
    exporter.skipId          = options.skipId;

    auto result = exporter.evalTop(node);
    hstd::writeFile(cmd.output, fmt::format("{}\n", result), true);
}

void org::cli::ExportCommandContext::run(SharedContext& shared) {
    __perf_trace("cli", "run export command");
    using EO = CliOpts::ExportOpts;

    configure(shared);

    // TODO: Support multiple inputs and unify all parsed nodes into a single group.
    hstd::fs::path input{cmd.input.at(0)};

    auto node = hstd::fs::is_directory(input)
                  ? shared.parseContext->parseDirectoryOpts(input, directoryParams)
                  : (shared.opts.withIncludes
                         ? shared.parseContext->parseFileWithIncludes(
                               input, directoryParams)
                         : shared.parseContext->parseFileOpts(
                               input, paramsForPath(shared, input.string())));

    LOGIC_ASSERTION_CHECK_FMT(node.has_value(), "Failed to parse input {}", input);

    std::visit(
        hstd::overloaded{
            [&](EO::Json const& options) { exportJson(node.value(), options); },
            [&](EO::Yaml const& options) { exportYaml(node.value(), options); },
            [&](EO::Token const&) { exportIrReprs(); },
            [&](EO::BaseToken const&) { exportIrReprs(); },
            [&](EO::ParseNode const&) { exportIrReprs(); },
#if ORG_BUILD_WITH_PROTOBUF
            [&](EO::Proto const& options) { exportProto(shared, node.value(), options); },
            [&](EO::Map const& options) { exportMap(shared, node.value(), options); },
#endif
        },
        cmd.data);
}


#if ORG_BUILD_WITH_PROTOBUF
void org::cli::ExportCommandContext::exportProto(
    SharedContext&                        shared,
    org::sem::SemId<org::sem::Org> const& node,
    CliOpts::ExportOpts::Proto const&     options) const {
    __perf_trace("cli", "export protobuf");
    HSLOG_INFO("Converting parse result to protobuf");

    orgproto::ParseResult result;
    hstd::serde::write_serde(result.mutable_node(), node);
    hstd::serde::write_serde(result.mutable_sources(), *shared.parseContext->source);
    hstd::serde::write_serde(result.mutable_reports(), reports);

    HSLOG_INFO("Serializing protobuf result to output file");
    shared.writeProtoResult(cmd.output, result, options.format);
}

void org::cli::ExportCommandContext::exportMap(
    SharedContext&                        shared,
    org::sem::SemId<org::sem::Org> const& node,
    CliOpts::ExportOpts::Map const&       options) const {
    __perf_trace("cli", "export map");
    auto config = org::graph::MapConfig::shared();
    auto store  = org::imm::ImmAstContext::init_start_context();

    HSLOG_INFO("Converting to immutable AST");
    __perf_trace_begin("cli", "Convert to immutable AST");
    org::imm::ImmAstVersion version = store->addRoot(node);
    __perf_trace_end("cli");

    auto state   = org::graph::MapGraphState::shared(version.context);
    auto adapter = version.getRootAdapter();

    HSLOG_INFO("Building immutable AST graph");
    __perf_trace_begin("cli", "Convert to graph");
    state->addNodeRec(adapter.ctx.lock(), adapter, config);
    __perf_trace_end("cli");

    HSLOG_INFO("Writing graph to protobuf data");

    org::graph::proto::GraphResult result;
    __perf_trace_begin("cli", "Convert graph to protobuf");
    result.set_allocated_graph(state->graph->get_serial().release());
    __perf_trace_end("cli");

    hstd::serde::write_serde(result.mutable_sources(), *shared.parseContext->source);
    hstd::serde::write_serde(result.mutable_reports(), reports);

    HSLOG_INFO("Serializing protobuf result to output file");
    __perf_trace_begin("cli", "Write protobuf out");
    shared.writeProtoResult(cmd.output, result, options.format);
    __perf_trace_end("cli");
}

void org::cli::ExportCommandContext::getSubcommand(
    CommandStore&             store,
    argparse::ArgumentParser& export_cmd) {
    using EO = CliOpts::ExportOpts;
    using EK = EO::Kind;
    export_cmd.add_description(
        "export parsed document; pick a target: " + describe_subcommands<EK>());
    export_cmd.add_argument(EO::input_opt)
        .help("input org file (repeatable)")
        .required()
        .append();
    export_cmd.add_argument(EO::output_opt).help("output file").required();
    export_cmd.add_argument(EO::exportTrace_opt).help("export trace path");

    argparse::ArgumentParser& json_cmd = store.addSubcommand(
        export_cmd, lower_enum(EK::Json));
    json_cmd.add_description("export to json");
    addBoolOpt(
        json_cmd, EO::Json::skipEmptyLists_opt, "skip empty lists on export", true);
    addBoolOpt(json_cmd, EO::Json::skipLocation_opt, "skip location fields", true);
    addBoolOpt(json_cmd, EO::Json::skipId_opt, "skip id fields", true);
    addBoolOpt(json_cmd, EO::Json::skipNullFields_opt, "skip null fields", true);
    addBoolOpt(
        json_cmd,
        EO::Json::normalizeSpaces_opt,
        "replace multi-character space with a single one",
        true);
    export_cmd.add_subparser(json_cmd);

    argparse::ArgumentParser& yaml_cmd = store.addSubcommand(
        export_cmd, lower_enum(EK::Yaml));
    yaml_cmd.add_description("export to yaml");
    addBoolOpt(yaml_cmd, EO::Yaml::skipNullFields_opt, "skip null fields", true);
    addBoolOpt(yaml_cmd, EO::Yaml::skipFalseFields_opt, "skip false fields", true);
    addBoolOpt(yaml_cmd, EO::Yaml::skipZeroFields_opt, "skip zero fields", true);
    addBoolOpt(yaml_cmd, EO::Yaml::skipLocation_opt, "skip location fields", true);
    addBoolOpt(yaml_cmd, EO::Yaml::skipId_opt, "skip id fields", true);
    export_cmd.add_subparser(yaml_cmd);

    argparse::ArgumentParser& token_cmd = store.addSubcommand(
        export_cmd, lower_enum(EK::Token));
    token_cmd.add_description("export tokenizer result");
    export_cmd.add_subparser(token_cmd);

    argparse::ArgumentParser& basetoken_cmd = store.addSubcommand(
        export_cmd, lower_enum(EK::BaseToken));
    basetoken_cmd.add_description("export base tokenizer result");
    export_cmd.add_subparser(basetoken_cmd);

    argparse::ArgumentParser& parsenode_cmd = store.addSubcommand(
        export_cmd, lower_enum(EK::ParseNode));
    parsenode_cmd.add_description("export parse node result");
    export_cmd.add_subparser(parsenode_cmd);

#    if ORG_BUILD_WITH_PROTOBUF
    argparse::ArgumentParser& proto_cmd = store.addSubcommand(
        export_cmd, lower_enum(EK::Proto));
    proto_cmd.add_description("export to protobuf");
    proto_cmd.add_argument(EO::Proto::format_opt)
        .help("set protobuf export format: " + describe_enum<CliOpts::ProtoFormat>());
    export_cmd.add_subparser(proto_cmd);

    argparse::ArgumentParser& map_cmd = store.addSubcommand(
        export_cmd, lower_enum(EK::Map));
    map_cmd.add_description("export to map");
    map_cmd.add_argument(EO::Map::format_opt)
        .help("set map export format: " + describe_enum<CliOpts::ProtoFormat>());
    map_cmd.add_argument(EO::Map::graphTrace_opt).help("graph trace output path");
    export_cmd.add_subparser(map_cmd);
#    endif
}

org::cli::CliOpts::ExportOpts org::cli::ExportCommandContext::parseCommand(
    argparse::ArgumentParser& export_cmd) {
    using EO = CliOpts::ExportOpts;
    using EK = EO::Kind;

    CliOpts::ExportOpts opts;
    opts.input  = export_cmd.get<std::vector<std::string>>(EO::input_opt);
    opts.output = export_cmd.get<std::string>(EO::output_opt);

    if (auto v = export_cmd.present<std::string>(EO::exportTrace_opt)) {
        opts.exportTrace = *v;
    }

    if (export_cmd.is_subcommand_used(lower_enum(EK::Json))) {
        auto&    sub = export_cmd.at<argparse::ArgumentParser>(lower_enum(EK::Json));
        EO::Json json;
        OPT_GET(sub, json, skipEmptyLists, bool);
        OPT_GET(sub, json, skipLocation, bool);
        OPT_GET(sub, json, skipId, bool);
        OPT_GET(sub, json, skipNullFields, bool);
        OPT_GET(sub, json, normalizeSpaces, bool);
        opts.data = json;
    } else if (export_cmd.is_subcommand_used(lower_enum(EK::Yaml))) {
        auto&    sub = export_cmd.at<argparse::ArgumentParser>(lower_enum(EK::Yaml));
        EO::Yaml yaml;
        OPT_GET(sub, yaml, skipNullFields, bool);
        OPT_GET(sub, yaml, skipFalseFields, bool);
        OPT_GET(sub, yaml, skipZeroFields, bool);
        OPT_GET(sub, yaml, skipLocation, bool);
        OPT_GET(sub, yaml, skipId, bool);
        opts.data = yaml;
#    if ORG_BUILD_WITH_PROTOBUF
    } else if (export_cmd.is_subcommand_used(lower_enum(EK::Proto))) {
        auto&     sub = export_cmd.at<argparse::ArgumentParser>(lower_enum(EK::Proto));
        EO::Proto res;
        OPT_GET_ENUM(sub, res, format, CliOpts::ProtoFormat);
        opts.data = res;
    } else if (export_cmd.is_subcommand_used(lower_enum(EK::Map))) {
        auto&   sub = export_cmd.at<argparse::ArgumentParser>(lower_enum(EK::Map));
        EO::Map res;
        OPT_GET_ENUM(sub, res, format, CliOpts::ProtoFormat);
        opts.data = res;
#    endif
    } else if (export_cmd.is_subcommand_used(lower_enum(EK::Token))) {
        opts.data = EO::Token{};
    } else if (export_cmd.is_subcommand_used(lower_enum(EK::BaseToken))) {
        opts.data = EO::BaseToken{};
    } else if (export_cmd.is_subcommand_used(lower_enum(EK::ParseNode))) {
        opts.data = EO::ParseNode{};
    } else {
        exitWithError(
            "export: missing export type subcommand, expected: "
            + describe_subcommands<EK>());
    }

    return opts;
}
#endif
