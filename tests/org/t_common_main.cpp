#include <gtest/gtest.h>
#include <hstd/system/aux_utils.hpp>
#include <iostream>
#include <hstd/system/string_convert.hpp>
#include <hstd/stdlib/Debug.hpp>
#include <fstream>
#include "../testprofiler.hpp"
#include <absl/strings/str_split.h>
#include <absl/log/log_sink_registry.h>
#include <absl/log/initialize.h>
#include <absl/log/internal/globals.h>
#include <fuzztest/init_fuzztest.h>

#ifdef ORG_USE_PERFETTO
#    include <hstd/wrappers/perfetto_aux.hpp>
#endif

FILE* trace_out;

extern "C" __attribute__((no_instrument_function)) void __cyg_profile_func_enter(
    void* this_fn,
    void* call_site) {
    if (trace_out != nullptr) {
        fprintf(trace_out, "> %p %p\n", this_fn, call_site);
    }
}

extern "C" __attribute__((no_instrument_function)) void __cyg_profile_func_exit(
    void* this_fn,
    void* call_site) {
    if (trace_out != nullptr) {
        fprintf(trace_out, "< %p %p\n", this_fn, call_site);
    }
}

// TestParameters testParameters;

const char* __asan_default_options() {
    return "verbosity=1:detect_leaks=0";
}

class LinePrinterLogSink : public absl::LogSink {
  public:
    LinePrinterLogSink(const char* path) : file(path) {}
    void Send(const absl::LogEntry& entry) override {
        for (absl::string_view line : absl::StrSplit(
                 entry.text_message_with_prefix(), absl::ByChar('\n'))) {
            // Overprint severe entries for emphasis:
            for (int i = static_cast<int>(absl::LogSeverity::kInfo);
                 i <= static_cast<int>(entry.log_severity());
                 i++) {
                file << line << std::endl;
            }
        }
    }

  private:
    std::ofstream file;
};

int main(int argc, char** argv) {
    // LinePrinterLogSink Sink("/tmp/test_log.log");
    // absl::AddLogSink(&Sink);
    // absl::log_internal::SetTimeZone(absl::LocalTimeZone());
    // absl::log_internal::SetInitialized();

#ifdef ORG_USE_PERFETTO
    StartProcessTracing("Perfetto track example");
#endif

    ::testing::InitGoogleTest(&argc, argv);
    ::fuzztest::InitFuzzTest(&argc, &argv);
    auto result = RUN_ALL_TESTS();

    json          records = TestProfiler::getJsonRecords();
    std::ofstream test_records{"/tmp/compact_records.json"};
    test_records << to_compact_json(records);

#ifdef ORG_USE_PERFETTO
    StopTracing(std::move(tracing_session));
#endif

    return result;
}
