#include <haxorg_cpp_org_lib/sem/perfetto_org.hpp>
#include <hstd_cpp_lib/extra/error_format/gtest_utils.hpp>
#include <hstd_cpp_lib/logger/logger.hpp>
#include <hstd_cpp_lib/logger/perfetto_aux_impl_template.hpp>

#include <hstd_cpp_lib/stdlib/algorithms/reflection/reflection_visitor.hpp>
#include <hstd_cpp_lib/stdlib/serde/JsonUse.hpp>

const char* __asan_default_options() { return "verbosity=1:detect_leaks=0"; }

int main(int argc, char** argv) {
    hstd::log::clear_sink_backends();
    hstd::log::push_sink(hstd::log::init_file_sink("/tmp/t_common_main.log"));
#if ORG_BUILD_WITH_PERFETTO
    std::unique_ptr<perfetto::TracingSession> tracing_session = StartProcessTracing(
        "Perfetto track example");

    hstd::finally end_trace{[&]() {
        StopTracing(
            std::move(tracing_session), "/tmp/t_common_main_perfetto_trace.pftrace");
    }};
#endif

    init_gtest_tests(argc, argv);

    return RUN_ALL_TESTS();
}
