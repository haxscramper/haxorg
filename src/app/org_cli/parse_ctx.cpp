#include "parse_ctx.hpp"

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

void org::cli::runParseCommand(SharedContext& shared, ParseCommandContext& parseContext) {
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
