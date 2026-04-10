#include <gtest/gtest.h>
#include <absl/flags/parse.h>

#include <haxorg/sem/perfetto_org.hpp>
#include "../common_main.hpp"

#include <hstd/ext/perfetto_aux_impl_template.hpp>
#include "hstd_tests_common.hpp"
#include <hstd/stdlib/reflection_visitor.hpp>

HSTD_REGISTER_TYPE_FIELD_NAMES(reflection_test::reflection_named);

void enable_full_trace_on_cli() {}

int main(int argc, char** argv) {
    hstd::log::clear_sink_backends();
    hstd::log::push_sink(
        hstd::log::init_file_sink("/tmp/t_hstd_test.log"));
#ifdef ORG_BUILD_WITH_PERFETTO
    std::unique_ptr<perfetto::TracingSession>
        tracing_session = StartProcessTracing("Perfetto track example");

    hstd::finally end_trace{[&]() {
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
