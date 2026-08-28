#include "export_ctx.hpp"

#include "haxorg/exporters/ExporterJson.hpp"
#include "haxorg/exporters/exporteryaml.hpp"
#include "src/haxorg/imm/ImmOrgGraph.pb.h"
#include "src/haxorg/serde/OrgApiProto.pb.h"
#include "src/haxorg/serde/SemOrgProto.pb.h"
#include <google/protobuf/util/json_util.h>
#include <haxorg/imm/ImmOrgGraph.hpp>
#include <hstd/ext/logger.hpp>


org::parse::OrgParseParameters::Ptr org::cli::ExportCommandContext::paramsForPath(
    SharedContext&     shared,
    std::string const& path) {
    auto params = org::parse::OrgParseParameters::shared();

    params->onDiagnosticsCollected = std::bind_front(
        &ExportCommandContext::onDiagnosticsCollected, this, std::ref(shared));

    if (std::holds_alternative<EO::Token>(cmd.data)) {
        params->onTokenizerDone = std::bind_front(
            &ExportCommandContext::onTokenizerDone, this, path);
    } else if (std::holds_alternative<EO::BaseToken>(cmd.data)) {
        params->onBaseTokenizeDone = std::bind_front(
            &ExportCommandContext::onBaseTokenizerDone, this, path);
    } else if (std::holds_alternative<EO::ParseNode>(cmd.data)) {
        params->onParseDone = std::bind_front(
            &ExportCommandContext::onParseDone, this, path);
    }

    return params;
}

void org::cli::ExportCommandContext::writeProtoJson(
    google::protobuf::Message const& result) const {
    std::string jsonOutput;

    google::protobuf::json::PrintOptions options;
    options.add_whitespace = true;

    auto status = google::protobuf::util::MessageToJsonString(
        result, &jsonOutput, options);

    hstd::writeFile(cmd.output, jsonOutput, true);
}

void org::cli::ExportCommandContext::exportJson(
    org::sem::SemId<org::sem::Org> const& node,
    EO::Json const&                       options) const {
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
    EO::Yaml const&                       options) const {
    org::algo::ExporterYaml exporter;
    exporter.skipNullFields  = options.skipNullFields;
    exporter.skipFalseFields = options.skipFalseFields;
    exporter.skipZeroFields  = options.skipZeroFields;
    exporter.skipLocation    = options.skipLocation;
    exporter.skipId          = options.skipId;

    auto result = exporter.evalTop(node);
    hstd::writeFile(cmd.output, fmt::format("{}\n", result), true);
}

void org::cli::runExportCommand(
    SharedContext&        shared,
    ExportCommandContext& exportContext) {
    using EO = CliOpts::ExportOpts;

    exportContext.configure(shared);

    // TODO: Support multiple inputs and unify all parsed nodes into a single group.
    hstd::fs::path input{exportContext.cmd.input.at(0)};

    auto node = hstd::fs::is_directory(input)
                  ? shared.parseContext->parseDirectoryOpts(
                        input, exportContext.directoryParams)
                  : (shared.opts.withIncludes
                         ? shared.parseContext->parseFileWithIncludes(
                               input, exportContext.directoryParams)
                         : shared.parseContext->parseFileOpts(
                               input,
                               exportContext.paramsForPath(shared, input.string())));

    LOGIC_ASSERTION_CHECK_FMT(node.has_value(), "Failed to parse input {}", input);

    std::visit(
        hstd::overloaded{
            [&](EO::Json const& options) {
                exportContext.exportJson(node.value(), options);
            },
            [&](EO::Yaml const& options) {
                exportContext.exportYaml(node.value(), options);
            },
            [&](EO::Token const&) { exportContext.exportIrReprs(); },
            [&](EO::BaseToken const&) { exportContext.exportIrReprs(); },
            [&](EO::ParseNode const&) { exportContext.exportIrReprs(); },
#if ORG_BUILD_WITH_PROTOBUF
            [&](EO::Proto const& options) {
                exportContext.exportProto(shared, node.value(), options);
            },
            [&](EO::Map const& options) {
                exportContext.exportMap(shared, node.value(), options);
            },
#endif
        },
        exportContext.cmd.data);
}


#if ORG_BUILD_WITH_PROTOBUF
void org::cli::ExportCommandContext::exportProto(
    SharedContext&                        shared,
    org::sem::SemId<org::sem::Org> const& node,
    EO::Proto const&                      options) const {
    HSLOG_INFO("Converting parse result to protobuf");

    orgproto::ParseResult result;
    hstd::serde::write_serde(result.mutable_node(), node);
    hstd::serde::write_serde(result.mutable_sources(), *shared.parseContext->source);
    hstd::serde::write_serde(result.mutable_reports(), reports);

    HSLOG_INFO("Serializing protobuf result to output file");
    writeProtoResult(result, options.format);
}

void org::cli::ExportCommandContext::exportMap(
    SharedContext&                        shared,
    org::sem::SemId<org::sem::Org> const& node,
    EO::Map const&                        options) const {
    auto config = org::graph::MapConfig::shared();
    auto store  = org::imm::ImmAstContext::init_start_context();

    HSLOG_INFO("Converting to immutable AST");
    org::imm::ImmAstVersion version = store->addRoot(node);

    auto state   = org::graph::MapGraphState::shared(version.context);
    auto adapter = version.getRootAdapter();

    HSLOG_INFO("Building immutable AST graph");
    state->addNodeRec(adapter.ctx.lock(), adapter, config);

    HSLOG_INFO("Writing graph to protobuf data");
    org::graph::proto::GraphResult result;
    result.set_allocated_graph(state->graph->get_serial().release());

    hstd::serde::write_serde(result.mutable_sources(), *shared.parseContext->source);
    hstd::serde::write_serde(result.mutable_reports(), reports);

    HSLOG_INFO("Serializing protobuf result to output file");
    writeProtoResult(result, options.format);
}
#endif
