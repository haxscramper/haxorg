
#include "../testprofiler.hpp"
#include "../common_main.hpp"

#include <haxorg/sem/perfetto_org.hpp>
#include <hstd/ext/perfetto_aux_impl_template.hpp>
#include <hstd/ext/logger.hpp>

FILE* trace_out;

const char* __asan_default_options() {
    return "verbosity=1:detect_leaks=0";
}


int main(int argc, char** argv) {
    hstd::log::clear_sink_backends();
    hstd::log::push_sink(
        hstd::log::init_file_sink("/tmp/t_common_main.log"));
#ifdef ORG_USE_PERFETTO
    std::unique_ptr<perfetto::TracingSession>
        tracing_session = StartProcessTracing("Perfetto track example");

    hstd::finally end_trace{[&]() {
        StopTracing(
            std::move(tracing_session),
            "/tmp/t_common_main_perfetto_trace.pftrace");
    }};
#endif

    init_gtest_tests(argc, argv);

    auto result = RUN_ALL_TESTS();

    json          records = TestProfiler::getJsonRecords();
    std::ofstream test_records{"/tmp/compact_records.json"};
    test_records << hstd::to_compact_json(records);


    return result;
}
