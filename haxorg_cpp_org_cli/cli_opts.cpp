#include <app/org_cli/cli_opts.hpp>
#include <app/org_cli/common_ctx.hpp>
#include <app/org_cli/diagram_ctx.hpp>
#include <app/org_cli/export_ctx.hpp>
#include <app/org_cli/parse_ctx.hpp>
#include <fstream>
#include <hstd_cpp_lib/stdlib/VecFormatter.hpp>

namespace org::cli {

argparse::ArgumentParser& org::cli::CommandStore::addSubcommand(
    argparse::ArgumentParser& parent,
    std::string               name) {
    auto  parser = std::make_shared<argparse::ArgumentParser>(std::move(name));
    auto& result = *parser;

    subcommands.push_back(std::move(parser));
    parent.add_subparser(result);

    return result;
}


static std::vector<std::string> expandAtFiles(int argc, char** argv) {
    std::vector<std::string> args;
    args.reserve(argc);
    for (int i = 0; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.size() > 1 && arg[0] == '@') {
            std::ifstream in{arg.substr(1)};
            if (!in) {
                throw std::runtime_error{"cannot open response file: " + arg.substr(1)};
            }
            std::string tok;
            while (in >> tok) { args.push_back(std::move(tok)); }
        } else {
            args.push_back(std::move(arg));
        }
    }
    return args;
}


void addBoolOpt(
    argparse::ArgumentParser& p,
    char const*               name,
    char const*               help,
    bool                      def) {
    p.add_argument(name).help(help).default_value(def).action(
        [](std::string const& v) -> bool { return v == "true" || v == "1"; });
}

CliOpts org::cli::parseCli(int argc, char** argv, CommandStore& store) {
    using EO = CliOpts::ExportOpts;
    using EK = EO::Kind;
    using PO = CliOpts::ParseOpts;

    argparse::ArgumentParser program("haxorg");
    program.add_epilog(
        hstd::fmt("ORG_BUILD_WITH_PROTOBUF = {}", ORG_BUILD_WITH_PROTOBUF));

    addBoolOpt(program, CliOpts::withIncludes_opt, "parse input with all includes", true);
    program.add_argument(CliOpts::loggingFlags_opt)
        .help("set logging flag values")
        .append();
    program.add_argument(CliOpts::logFile_opt)
        .help(
            "main log file for the CLI. It will contain all the internal messages "
            "(debug, tracing -- everything that the end user most likely not interested "
            "in)");
    program.add_argument(CliOpts::diagnosticsFile_opt)
        .help(
            "Optional file to write parse diagnostics (errors, warnings -- all sorts of "
            "user-facing messages) to.");
    program.add_argument(CliOpts::perfFile_opt)
        .help(
            "Optional file to write perfetto profiling diagnostics to (the code must be "
            "compiled with perfetto enabled)");

    argparse::ArgumentParser parse_cmd{"parse"};
    ParseCommandContext::getSubcommand(parse_cmd);
    program.add_subparser(parse_cmd);

    argparse::ArgumentParser export_cmd{"export"};
    ExportCommandContext::getSubcommand(store, export_cmd);
    program.add_subparser(export_cmd);

    argparse::ArgumentParser diagram_cmd{"diagram"};
    DiagramCommandContext::getSubcommand(diagram_cmd);
    program.add_subparser(diagram_cmd);


    auto expanded = expandAtFiles(argc, argv);
    try {
        std::vector<char*> expandedPtrs;
        expandedPtrs.reserve(expanded.size());
        for (auto& s : expanded) { expandedPtrs.push_back(s.data()); }

        program.parse_args(expandedPtrs.size(), expandedPtrs.data());
    } catch (std::exception const& e) {
        std::cerr << hstd::fmt(
            R"({}
{}
Full argument list was:
{})",
            e.what(),
            program.help().str(),
            expanded);

        std::exit(1);
    }

    CliOpts result;
    result.withIncludes = program.get<bool>(CliOpts::withIncludes_opt);

    if (auto flags = program.present<std::vector<std::string>>(
            CliOpts::loggingFlags_opt)) {
        result.loggingFlags = hstd::IntSet<CliOpts::LoggingFlags>{};
        for (auto const& value : *flags) {
            result.loggingFlags.incl(
                readEnumValue<CliOpts::LoggingFlags>(value, "logging flag"));
        }
    }

    if (auto f = program.present<std::string>(CliOpts::logFile_opt)) {
        result.logFile = *f;
    }

    if (auto f = program.present<std::string>(CliOpts::diagnosticsFile_opt)) {
        result.diagnosticsFile = *f;
    }

    if (auto f = program.present<std::string>(CliOpts::perfFile_opt)) {
        result.perfFile = *f;
    }

    if (program.is_subcommand_used("parse")) {
        result.cmd = ParseCommandContext::parseCommand(parse_cmd);
    } else if (program.is_subcommand_used("export")) {
        result.cmd = ExportCommandContext::parseCommand(export_cmd);
    } else if (program.is_subcommand_used("diagram")) {
        result.cmd = DiagramCommandContext::parseCommand(diagram_cmd);
    } else {
        std::cerr << "missing command (expected 'parse' or 'export')\n" << program;
        std::exit(1);
    }

    return result;
}

} // namespace org::cli
