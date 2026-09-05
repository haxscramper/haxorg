#include "diagram_ctx.hpp"

using DO = org::cli::CliOpts::DiagramOpts;

org::cli::CliOpts::DiagramOpts org::cli::DiagramCommandContext::parseCommand(
    argparse::ArgumentParser& diagram_cmd) {
    CliOpts::DiagramOpts opts;
    OPT_GET(diagram_cmd, opts, input, std::string);
    OPT_GET(diagram_cmd, opts, output, std::string);
    OPT_GET_ENUM(diagram_cmd, opts, format, CliOpts::ProtoFormat);
    OPT_GET_ENUM(diagram_cmd, opts, input_format, CliOpts::DiagramOpts::InputFormat);
    return opts;
}

void org::cli::DiagramCommandContext::getSubcommand(
    argparse::ArgumentParser& diagram_cmd) {
    diagram_cmd.add_argument(DO::input_opt).help("input protobuf diagram file");
    diagram_cmd.add_argument(DO::output_opt).help("output diagram file");
    diagram_cmd.add_argument(DO::format_opt)
        .help("set diagram export format: " + describe_enum<CliOpts::ProtoFormat>());
    diagram_cmd.add_argument(DO::input_format_opt)
        .help(
            "set diagram import format: "
            + describe_enum<CliOpts::DiagramOpts::InputFormat>());
}

void org::cli::runDiagramCommand(
    SharedContext&         shared,
    DiagramCommandContext& parseContext) {}
