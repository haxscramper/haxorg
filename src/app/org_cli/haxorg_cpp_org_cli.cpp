#include <app/org_cli/cli_opts.hpp>
#include <app/org_cli/common_ctx.hpp>
#include <app/org_cli/export_ctx.hpp>
#include <app/org_cli/parse_ctx.hpp>
#include <haxorg/sem/perfetto_org.hpp>
#include <hstd/ext/logger.hpp>
#include <hstd/ext/perfetto_aux_impl_template.hpp>
#include <hstd/stdlib/IntSetSerde.hpp>
#include <hstd/stdlib/JsonCLIParser.hpp>
#include <hstd/stdlib/OptFormatter.hpp>
#include <hstd/stdlib/VariantSerde.hpp>
#include <hstd/stdlib/VecFormatter.hpp>

int main(int argc, char* argv[]) {
    auto opts //
        = argc == 2 && std::string{argv[1]}.starts_with("/")
            ? hstd::parse_json_argc<org::cli::CliOpts>(argc, argv)
            : org::cli::parseCli(argc, argv);

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
                           ? StartProcessTracingWithImmediateFlush(
                                 "haxorg_cpp_org_cli",
                                 shared.opts.perfFile.value(),
                                 std::chrono::milliseconds{5000})
                           : std::unique_ptr<perfetto::TracingSession>{};

#endif

    __perf_trace("cli", "run subcommands");
    if (std::holds_alternative<org::cli::CliOpts::ParseOpts>(shared.opts.cmd)) {
        auto const& command = std::get<org::cli::CliOpts::ParseOpts>(shared.opts.cmd);

        org::cli::ParseCommandContext parseContext{command};
        runParseCommand(shared, parseContext);
    } else {
        auto const& command = std::get<org::cli::CliOpts::ExportOpts>(shared.opts.cmd);

        org::cli::ExportCommandContext exportContext{command};
        runExportCommand(shared, exportContext);
    }

    HSLOG_INFO("Done file processing");
}
