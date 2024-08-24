#include <gtest/gtest.h>
#include <absl/flags/parse.h>

#include <haxorg/sem/perfetto_org.hpp>
#include "../common_main.hpp"

void enable_full_trace_on_cli() {}

int main(int argc, char** argv) {
#ifdef ORG_USE_PERFETTO
    std::unique_ptr<perfetto::TracingSession>
        tracing_session = StartProcessTracing("Perfetto track example");

    finally end_trace{[&]() {
        StopTracing(
            std::move(tracing_session),
            "/tmp/t_hstd_main_perfetto_trace.pftrace");
    }};
#endif


    init_gtest_tests(argc, argv);

    ::absl::ParseCommandLine(argc, argv);

    auto result = RUN_ALL_TESTS();


    return result;
}
