#include <app/org_cli/cli_opts.hpp>
#include <fstream>
#include <hstd/stdlib/VecFormatter.hpp>

namespace org::cli {

CliOpts::ExportOpts buildExportOpts(argparse::ArgumentParser& export_cmd) {
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
#if ORG_BUILD_WITH_PROTOBUF
    } else if (export_cmd.is_subcommand_used(lower_enum(EK::Proto))) {
        auto&     sub = export_cmd.at<argparse::ArgumentParser>(lower_enum(EK::Proto));
        EO::Proto res;
        OPT_GET_ENUM(sub, res, format, EO::ProtoFormat);
        opts.data = res;
    } else if (export_cmd.is_subcommand_used(lower_enum(EK::Map))) {
        auto&   sub = export_cmd.at<argparse::ArgumentParser>(lower_enum(EK::Map));
        EO::Map res;
        OPT_GET_ENUM(sub, res, format, EO::ProtoFormat);
        opts.data = res;
#endif
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
CliOpts org::cli::parseCli(int argc, char** argv) {
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

    argparse::ArgumentParser parse_cmd("parse");
    parse_cmd.add_description("parse input file or directory");
    parse_cmd.add_argument(PO::input_opt).help("input file or directory");
    parse_cmd.add_argument(PO::baseTokenTracePath_opt)
        .help("base token trace output path");
    parse_cmd.add_argument(PO::tokenTracePath_opt).help("token trace output path");
    parse_cmd.add_argument(PO::parseTracePath_opt).help("parse trace output path");
    parse_cmd.add_argument(PO::semTracePath_opt).help("sem trace output path");
    parse_cmd.add_argument(PO::baseTokenDumpPath_opt).help("base token dump output path");
    parse_cmd.add_argument(PO::tokenDumpPath_opt).help("token dump output path");
    parse_cmd.add_argument(PO::parseDumpPath_opt).help("parse dump output path");
    parse_cmd.add_argument(PO::semDumpPath_opt).help("sem dump output path");
    parse_cmd.add_argument(PO::immDumpPath_opt).help("Non-verbose dump of immutable AST");
    parse_cmd.add_argument(PO::immAstTracePath_opt).help("Trace imm ast construct");
    parse_cmd.add_argument(PO::immVerboseDumpPath_opt)
        .help("Verbose dump of immutable AST");
    parse_cmd.add_argument(PO::immTrackingDumpPath_opt)
        .help("Dump of immutable AST tracking information");
    parse_cmd.add_argument(PO::validateBaseTokens_opt)
        .help(
            "Whether to check the base tokens for consistency. This is a dev/debug "
            "option");
    parse_cmd.add_argument(PO::lastStage_opt)
        .help(
            "Stop parsing at the specified stage, this is a primarily for "
            "debugging/profiling individual stages, unless the last stage is set to "
            "SemConvert, the parser will not try to collect any diagnostics or return "
            "any values. Allowed values "
            + describe_enum<org::parse::OrgParseParameters::LastParseStage>());

    program.add_subparser(parse_cmd);

    argparse::ArgumentParser export_cmd("export");
    export_cmd.add_description(
        "export parsed document; pick a target: " + describe_subcommands<EK>());
    export_cmd.add_argument(EO::input_opt)
        .help("input org file (repeatable)")
        .required()
        .append();
    export_cmd.add_argument(EO::output_opt).help("output file").required();
    export_cmd.add_argument(EO::exportTrace_opt).help("export trace path");

    argparse::ArgumentParser json_cmd(lower_enum(EK::Json));
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

    argparse::ArgumentParser yaml_cmd(lower_enum(EK::Yaml));
    yaml_cmd.add_description("export to yaml");
    addBoolOpt(yaml_cmd, EO::Yaml::skipNullFields_opt, "skip null fields", true);
    addBoolOpt(yaml_cmd, EO::Yaml::skipFalseFields_opt, "skip false fields", true);
    addBoolOpt(yaml_cmd, EO::Yaml::skipZeroFields_opt, "skip zero fields", true);
    addBoolOpt(yaml_cmd, EO::Yaml::skipLocation_opt, "skip location fields", true);
    addBoolOpt(yaml_cmd, EO::Yaml::skipId_opt, "skip id fields", true);
    export_cmd.add_subparser(yaml_cmd);

    argparse::ArgumentParser token_cmd(lower_enum(EK::Token));
    token_cmd.add_description("export tokenizer result");
    export_cmd.add_subparser(token_cmd);

    argparse::ArgumentParser basetoken_cmd(lower_enum(EK::BaseToken));
    basetoken_cmd.add_description("export base tokenizer result");
    export_cmd.add_subparser(basetoken_cmd);

    argparse::ArgumentParser parsenode_cmd(lower_enum(EK::ParseNode));
    parsenode_cmd.add_description("export parse node result");
    export_cmd.add_subparser(parsenode_cmd);

#if ORG_BUILD_WITH_PROTOBUF
    argparse::ArgumentParser proto_cmd(lower_enum(EK::Proto));
    proto_cmd.add_description("export to protobuf");
    proto_cmd.add_argument(EO::Proto::format_opt)
        .help("set protobuf export format: " + describe_enum<EO::ProtoFormat>());
    export_cmd.add_subparser(proto_cmd);

    argparse::ArgumentParser map_cmd(lower_enum(EK::Map));
    map_cmd.add_description("export to map");
    map_cmd.add_argument(EO::Map::format_opt)
        .help("set map export format: " + describe_enum<EO::ProtoFormat>());
    map_cmd.add_argument(EO::Map::graphTrace_opt).help("graph trace output path");
    export_cmd.add_subparser(map_cmd);
#endif

    program.add_subparser(export_cmd);


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
        CliOpts::ParseOpts opts;
        opts.input = parse_cmd.get<std::string>(PO::input_opt);
        OPT_GET(parse_cmd, opts, baseTokenTracePath, std::string);
        OPT_GET(parse_cmd, opts, tokenTracePath, std::string);
        OPT_GET(parse_cmd, opts, parseTracePath, std::string);
        OPT_GET(parse_cmd, opts, semTracePath, std::string);
        OPT_GET(parse_cmd, opts, baseTokenDumpPath, std::string);
        OPT_GET(parse_cmd, opts, tokenDumpPath, std::string);
        OPT_GET(parse_cmd, opts, parseDumpPath, std::string);
        OPT_GET(parse_cmd, opts, semDumpPath, std::string);
        OPT_GET(parse_cmd, opts, immDumpPath, std::string);
        OPT_GET(parse_cmd, opts, immVerboseDumpPath, std::string);
        OPT_GET(parse_cmd, opts, immAstTracePath, std::string);
        OPT_GET(parse_cmd, opts, immTrackingDumpPath, std::string);
        if (auto v = parse_cmd.present<std::string>(opts.validateBaseTokens_opt)) {
            // TODO: boost lexical cast fails here, but writing a template function that
            // extracts the user-provided varibles in a sensible manner (e.g. interpreting
            // "true" string as `true` value, which is pretty fucking obvious IMO).
            opts.validateBaseTokens = v.value() == "true";
        }
        OPT_GET_ENUM(
            parse_cmd, opts, lastStage, org::parse::OrgParseParameters::LastParseStage);
        result.cmd = opts;
    } else if (program.is_subcommand_used("export")) {
        result.cmd = buildExportOpts(export_cmd);
    } else {
        std::cerr << "missing command (expected 'parse' or 'export')\n" << program;
        std::exit(1);
    }

    return result;
}

} // namespace org::cli
