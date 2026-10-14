#include <hstd_cpp_lib/stdlib/Filesystem.hpp>

#undef emit
#undef slots

#include <clang/Tooling/CommonOptionsParser.h>
#include <filesystem>
#include <hstd_cpp_lib/logger/logger.hpp>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/JSON.h>

#include <haxdex_read_code_cpp_common/reflection_cli_parse.hpp>
#include <haxdex_read_code_cpp_common/reflection_perf.hpp>
#include <hstd_cpp_lib/logger/perfetto_aux_impl_template.hpp>

#include <haxdex_read_code_cpp/reflection_collector.hpp>
#include <haxdex_read_code_cpp/reflection_collector_frontend.hpp>


static clang::ParsedAttrInfoRegistry::Add<ReflAttrInfo> ReflectionCollectorDef(
    "refl",
    "reflection attribute");

int main(int argc, char const** argv) {
    ReflectionCLI cli = parse_reflection_cli(argc, argv);

    std::unique_ptr<perfetto::TracingSession> perfetto_session;
    if (cli.perf_path) { perfetto_session = StartProcessTracing("haxdex_read_code_cpp"); }

    switch (cli.mode) {
        case ReflectionCLI::Mode::AllTargetedFiles: [[fallthrough]];
        case ReflectionCLI::Mode::AllMainSymbolsInCompilationDb: [[fallthrough]];
        case ReflectionCLI::Mode::AllAnotatedSymbols:
            run_semantic_symbols_collection(cli);
            break;

        default:
            throw hstd::invalid_argument::init(
                fmt::format(
                    "Mode {} is not handled by the haxdex_read_code_cpp binary",
                    cli.mode));
    }

    if (cli.perf_path) {
        hstd::fs::path out_path{cli.perf_path.value()};
        StopTracing(std::move(perfetto_session), out_path);
    }

    return 0;
}
