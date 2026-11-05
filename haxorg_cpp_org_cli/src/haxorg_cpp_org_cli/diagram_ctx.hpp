#pragma once

#include <haxorg_cpp_org_cli/cli_opts.hpp>
#include <haxorg_cpp_org_cli/common_ctx.hpp>


namespace org::cli {
struct DiagramCommandContext {
    CliOpts::DiagramOpts const& cmd;

    explicit DiagramCommandContext(CliOpts::DiagramOpts const& command) : cmd{command} {}

    static void                 getSubcommand(argparse::ArgumentParser& diagram_cmd);
    static CliOpts::DiagramOpts parseCommand(argparse::ArgumentParser& diagram_cmd);

    void run(SharedContext& shared);
};


} // namespace org::cli
