#include <app/org_cli/cli_opts.hpp>
#include <app/org_cli/common_ctx.hpp>
#include <app/org_cli/diagram_ctx.hpp>
#include <app/org_cli/export_ctx.hpp>
#include <app/org_cli/parse_ctx.hpp>
#include <haxorg/sem/perfetto_org.hpp>
#include <hstd_cpp_lib/ext/logger.hpp>
#include <hstd_cpp_lib/ext/perfetto_aux_impl_template.hpp>
#include <hstd_cpp_lib/stdlib/IntSetSerde.hpp>
#include <hstd_cpp_lib/stdlib/JsonCLIParser.hpp>
#include <hstd_cpp_lib/stdlib/OptFormatter.hpp>
#include <hstd_cpp_lib/stdlib/VariantSerde.hpp>
#include <hstd_cpp_lib/stdlib/VecFormatter.hpp>

int main(int argc, char* argv[]) {
    org::cli::CommandStore store;

    auto opts //
        = argc == 2 && std::string{argv[1]}.starts_with("/")
            ? hstd::parse_json_argc<org::cli::CliOpts>(argc, argv)
            : org::cli::parseCli(argc, argv, store);

    hstd::log::clear_sink_backends();

    if (opts.loggingFlags.contains(org::cli::CliOpts::LoggingFlags::LogToFile)) {
        LOGIC_ASSERTION_CHECK(opts.logFile.has_value(), "Expected value for log file");

        hstd::log::push_sink(
            hstd::log::init_file_sink(opts.logFile.value(), opts.logStructured));
    }

    if (opts.loggingFlags.contains(org::cli::CliOpts::LoggingFlags::LogToStdout)) {
        hstd::log::push_sink(hstd::log::init_stdout_sink(opts.logStructured));
    }

    HSLOG_INFO("starting");
    HSLOG_TRACE("CLI opts: {}", opts);

    org::cli::SharedContext shared{std::move(opts)};

#ifdef ORG_BUILD_WITH_PERFETTO
    std::unique_ptr<perfetto::TracingSession>
        tracingSession = shared.opts.perfFile
                           ? StartProcessTracing("haxorg_cpp_org_cli")
                           : std::unique_ptr<perfetto::TracingSession>{};

#endif

    __perf_trace("cli", "run subcommands");
    if (auto command = std::get_if<org::cli::CliOpts::ParseOpts>(&shared.opts.cmd)) {
        org::cli::ParseCommandContext ctx{*command};
        ctx.run(shared);
    } else if (
        auto command = std::get_if<org::cli::CliOpts::DiagramOpts>(&shared.opts.cmd)) {
        org::cli::DiagramCommandContext ctx{*command};
        ctx.run(shared);
    } else if (
        auto command = std::get_if<org::cli::CliOpts::ExportOpts>(&shared.opts.cmd)) {
        org::cli::ExportCommandContext ctx{*command};
        ctx.run(shared);
    } else {
        throw hstd::logic_unhandled_kind_error::init("Unexpected CLI subcommand variant");
    }

    HSLOG_INFO("Done file processing");

#ifdef ORG_BUILD_WITH_PERFETTO
    if (shared.opts.perfFile) {
        StopTracing(std::move(tracingSession), shared.opts.perfFile.value());
    }
#endif
}
