#include "parse_ctx.hpp"
#include <haxorg/sem/perfetto_org.hpp>

void org::cli::ParseCommandContext::configure(SharedContext& shared) {
    params->parseTracePath     = cmd.parseTracePath;
    params->baseTokenTracePath = cmd.baseTokenTracePath;
    params->tokenTracePath     = cmd.tokenTracePath;
    params->semTracePath       = cmd.semTracePath;
    params->lastStage          = cmd.lastStage;
    params->validateBaseTokens = cmd.validateBaseTokens;

    params->onDiagnosticsCollected = std::bind_front(
        &ParseCommandContext::onDiagnosticsCollected, this, std::ref(shared));

    params->onParseDone = std::bind_front(&ParseCommandContext::onParseDone, this);

    directoryParams->shouldProcessPath = std::bind_front(
        &SharedContext::shouldProcessPath, &shared);

    directoryParams->getParsedNode = std::bind_front(
        &ParseCommandContext::parsePath, this, std::ref(shared));
}

void org::cli::ParseCommandContext::onDiagnosticsCollected(
    SharedContext&                      shared,
    hstd::Vec<hstd::ext::Report> const& reports,
    std::optional<int>                  fragmentIndex) {
    auto cache = shared.parseContext->getDiagnosticStrings();

    for (auto const& report : reports) {
        auto copy = report;
        *shared.diagnosticsOut << copy.to_string(*cache, false) << std::endl;
    }
}

void org::cli::ParseCommandContext::onParseDone(
    org::parse::OrgNodeGroup const& nodes,
    org::parse::OrgId               id,
    std::optional<int>              fragmentIndex) {
    if (cmd.parseDumpPath) {
        hstd::writeFile(cmd.parseDumpPath.value(), nodes.treeRepr(id), true);
    }
}

org::sem::SemId<org::sem::Org> org::cli::ParseCommandContext::parsePath(
    SharedContext&     shared,
    std::string const& path) {
    return shared.parseContext->parseFileOpts(path, params);
}

void org::cli::ParseCommandContext::writeImmutableDumps(
    org::sem::SemId<org::sem::Org> const& node) const {
    auto store = org::imm::ImmAstContext::init_start_context();

    if (cmd.immAstTracePath) { store->debug->setTraceFile(cmd.immAstTracePath.value()); }

    auto version = store->init(node);
    auto immNode = version.getRootAdapter();

    if (cmd.immDumpPath) {
        hstd::writeFile(
            cmd.immDumpPath.value(),
            immNode.treeRepr(org::imm::ImmAdapter::TreeReprConf{}).toString(false),
            true);
    }

    if (cmd.immVerboseDumpPath) {
        hstd::writeFile(
            cmd.immVerboseDumpPath.value(),
            immNode
                .treeRepr(
                    org::imm::ImmAdapter::TreeReprConf{
                        .withAuxFields  = true,
                        .withReflFields = true,
                    })
                .toString(false),
            true);
    }

    if (cmd.immTrackingDumpPath) {
        hstd::writeFile(
            cmd.immTrackingDumpPath.value(),
            version.getContext()->currentTrack->toString().toString(false),
            true);
    }
}

org::cli::CliOpts::ParseOpts org::cli::ParseCommandContext::parseCommand(
    argparse::ArgumentParser& parse_cmd) {
    CliOpts::ParseOpts opts;
    opts.input = parse_cmd.get<std::string>(CliOpts::ParseOpts::input_opt);
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
    return opts;
}

void org::cli::ParseCommandContext::getSubcommand(argparse::ArgumentParser& parse_cmd) {
    using PO = CliOpts::ParseOpts;
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
}

void org::cli::runParseCommand(SharedContext& shared, ParseCommandContext& parseContext) {
    __perf_trace("cli", "run parse command");
    parseContext.configure(shared);

    hstd::fs::path                 input{parseContext.cmd.input};
    org::sem::SemId<org::sem::Org> node;

    if (hstd::fs::is_directory(input)) {
        node = shared.parseContext
                   ->parseDirectoryOpts(input, parseContext.directoryParams)
                   .value();
    } else if (shared.opts.withIncludes) {
        node = shared.parseContext->parseFileWithIncludes(
            input, parseContext.directoryParams);
    } else {
        node = shared.parseContext->parseFileOpts(input, parseContext.params);
    }

    if (parseContext.cmd.lastStage
        == org::parse::OrgParseParameters::LastParseStage::ImmConvert) {
        parseContext.writeImmutableDumps(node);
    }
}
