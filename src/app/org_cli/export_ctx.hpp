#pragma once

#include <app/org_cli/cli_opts.hpp>
#include <app/org_cli/common_ctx.hpp>
#include <haxorg/api/ParseContext.hpp>
#include <haxorg/api/SemBaseApi.hpp>
#include <haxorg/lexbase/NodeIO.hpp>
#include <hstd/stdlib/JsonUse.hpp>

namespace org::cli {
struct ExportCommandContext {
    using EO = CliOpts::ExportOpts;

    EO const&                                    cmd;
    org::parse::OrgDirectoryParseParameters::Ptr directoryParams;
    json                                         irReprs{};
    hstd::Vec<ParseReports>                      reports;

    explicit ExportCommandContext(EO const& command)
        : cmd{command}
        , directoryParams{org::parse::OrgDirectoryParseParameters::shared()} {}

    void configure(SharedContext& shared) {
        directoryParams->shouldProcessPath = std::bind_front(
            &SharedContext::shouldProcessPath, &shared);

        directoryParams->getParsedNode = std::bind_front(
            &ExportCommandContext::parsePath, this, std::ref(shared));
    }

    void onDiagnosticsCollected(
        SharedContext&                      shared,
        hstd::Vec<hstd::ext::Report> const& collected,
        std::optional<int>                  fragmentIndex) {
        auto cache = shared.parseContext->getDiagnosticStrings();

        for (auto const& report : collected) {
            reports.push_back(
                ParseReports{
                    .formatted = report.to_string(*cache, false),
                    .report    = report,
                });
        }
    }

    template <typename Group>
    json groupJsonRepresentation(
        std::string const& path,
        Group const&       group,
        std::optional<int> fragmentIndex) const {
        return json::object({
            {"path", path},
            {"group", org::test::jsonRepr(group)},
            {
                "fragment_index",
                fragmentIndex.has_value() ? json{fragmentIndex.value()} : json{},
            },
        });
    }

    void onTokenizerDone(
        std::string const&               path,
        org::parse::OrgTokenGroup const& tokens,
        std::optional<int>               fragmentIndex) {
        irReprs["tokenizer_export"].push_back(
            groupJsonRepresentation(path, tokens, fragmentIndex));
    }

    void onBaseTokenizerDone(
        std::string const&               path,
        org::parse::OrgTokenGroup const& tokens,
        std::optional<int>               fragmentIndex) {
        irReprs["base_tokenizer_export"].push_back(
            groupJsonRepresentation(path, tokens, fragmentIndex));
    }

    void onParseDone(
        std::string const&              path,
        org::parse::OrgNodeGroup const& nodes,
        org::parse::OrgId               id,
        std::optional<int>              fragmentIndex) {
        irReprs["parse_export"].push_back(
            groupJsonRepresentation(path, nodes, fragmentIndex));
    }

    org::parse::OrgParseParameters::Ptr paramsForPath(
        SharedContext&     shared,
        std::string const& path);

    org::sem::SemId<org::sem::Org> parsePath(
        SharedContext&     shared,
        std::string const& path) {
        return shared.parseContext->parseFileOpts(path, paramsForPath(shared, path));
    }

    void writeProtoJson(google::protobuf::Message const& result) const;

    void writeProtoBinary(google::protobuf::Message const& result) const {
        std::ofstream output{cmd.output, std::ios::binary};
        result.SerializeToOstream(&output);
    }

    void writeProtoXml(google::protobuf::Message const& result) const {
        auto          mapper = make_proto_xml_mapper();
        std::ofstream output{cmd.output};
        mapper.map(result).serialize(output);
    }

    void writeProtoResult(google::protobuf::Message const& result, EO::ProtoFormat format)
        const;

    void exportJson(org::sem::SemId<org::sem::Org> const& node, EO::Json const& options)
        const;

    void exportYaml(org::sem::SemId<org::sem::Org> const& node, EO::Yaml const& options)
        const;

    void exportIrReprs() const { hstd::writeFile(cmd.output, irReprs.dump(2), true); }

#if ORG_BUILD_WITH_PROTOBUF
    void exportProto(
        SharedContext&                        shared,
        org::sem::SemId<org::sem::Org> const& node,
        EO::Proto const&                      options) const;

    void exportMap(
        SharedContext&                        shared,
        org::sem::SemId<org::sem::Org> const& node,
        EO::Map const&                        options) const;
#endif
};


void runExportCommand(SharedContext& shared, ExportCommandContext& exportContext);
} // namespace org::cli
