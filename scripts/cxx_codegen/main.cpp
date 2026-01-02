#include <hstd/stdlib/Filesystem.hpp>


#include <llvm/Support/CommandLine.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <filesystem>
#include <llvm/Support/JSON.h>
#include <hstd/ext/logger.hpp>

#include "reflection_perf.hpp" // IWYU pragma: keep
#include <hstd/ext/perfetto_aux_impl_template.hpp>

#include "reflection_collector_frontend.hpp"
#include "profdata_merger.hpp"


int main(int argc, const char** argv) {
    std::string json_parameters;
    if (std::string{argv[1]}.starts_with("/")) {
        if (!hstd::fs::exists(argv[1])) {
            throw std::logic_error(
                std::format(
                    "Input configuration file '{}' does not exist",
                    argv[1]));
        }
        json_parameters = hstd::readFile(argv[1]);
    } else {
        json_parameters = std::string{argv[1]};
    }

    auto cli = hstd::JsonSerde<ReflectionCLI>::from_json(
        json::parse(json_parameters));

    if (cli.log_path) {
        hstd::log::push_sink(
            hstd::log::init_file_sink(cli.log_path.value()));
    }


#ifdef ORG_USE_PERFETTO
    std::unique_ptr<perfetto::TracingSession> perfetto_session;
    if (cli.perf_path) {
        perfetto_session = StartProcessTracing("profdata_merger");
    }
#endif

    switch (cli.mode) {
        case ReflectionCLI::Mode::RunProfileMerge:
            build_run_coverage_merge(cli);
            break;
        case ReflectionCLI::Mode::BuildProfileMerge:
            build_build_coverage_merge(cli);
            break;

        case ReflectionCLI::Mode::FullTranslationUnit: [[fallthrough]];
        case ReflectionCLI::Mode::AllMainSymbolsInCompilationDb:
            [[fallthrough]];
        case ReflectionCLI::Mode::AllAnotatedSymbols:
            run_semantic_symbols_collection(cli);
            break;

        case ReflectionCLI::Mode::BinarySymbols:
            run_binary_symbols_collection(cli);
            break;
    }


    if (cli.perf_path) {
        hstd::fs::path out_path{cli.perf_path.value()};
#ifdef ORG_USE_PERFETTO
        StopTracing(std::move(perfetto_session), out_path);
#endif
    }

    return 0;
}
