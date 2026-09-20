#pragma once

#include <app/org_cli/cli_opts.hpp>
#include <app/org_cli/common_ctx.hpp>
#include <haxorg_cpp_org_lib/api/ParseContext.hpp>
#include <haxorg_cpp_org_lib/api/SemBaseApi.hpp>

namespace org::cli {
struct ParseCommandContext {
    CliOpts::ParseOpts const&                    cmd;
    org::parse::OrgParseParameters::Ptr          params;
    org::parse::OrgDirectoryParseParameters::Ptr directoryParams;

    explicit ParseCommandContext(CliOpts::ParseOpts const& command)
        : cmd{command}
        , params{org::parse::OrgParseParameters::shared()}
        , directoryParams{org::parse::OrgDirectoryParseParameters::shared()} {}

    void configure(SharedContext& shared);

    void onDiagnosticsCollected(
        SharedContext&                      shared,
        hstd::Vec<hstd::ext::Report> const& reports,
        std::optional<int>                  fragmentIndex);

    void onBaseTokenizeDone(
        org::parse::OrgTokenGroup const& tokens,
        std::optional<int>               fragmentIndex);

    void onTokenizerDone(
        org::parse::OrgTokenGroup const& tokens,
        std::optional<int>               fragmentIndex);

    void onParseDone(
        org::parse::OrgNodeGroup const& nodes,
        org::parse::OrgId               id,
        std::optional<int>              fragmentIndex);

    org::sem::SemId<org::sem::Org> parsePath(
        SharedContext&     shared,
        std::string const& path);

    void writeImmutableDumps(org::sem::SemId<org::sem::Org> const& node) const;

    static void               getSubcommand(argparse::ArgumentParser& parse_cmd);
    static CliOpts::ParseOpts parseCommand(argparse::ArgumentParser& parse_cmd);

    void run(SharedContext& shared);
};


} // namespace org::cli
