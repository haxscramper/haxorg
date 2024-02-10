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
#include <sys/resource.h>

bool SetStackSize(rlim_t stackSize) {
    struct rlimit rl;
    int           result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0) {
        if (rl.rlim_cur < stackSize) {
            rl.rlim_cur = stackSize;
            result      = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0) { return false; }
        }
    }

    return true;
}


#include <sem/perfetto_org.hpp>
#include <hstd/wrappers/perfetto_aux_impl_template.hpp>


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

class QuietTestPrinter : public ::testing::EmptyTestEventListener {
    // Called after a failed assertion or a SUCCESS().
    void OnTestPartResult(
        const ::testing::TestPartResult& test_part_result) override {
        if (test_part_result.failed()) {
            std::cout << fmt(
                "{} in {}:{}\n{}\n",
                test_part_result.failed() ? "*** Failure" : "Success",
                test_part_result.file_name() ? test_part_result.file_name()
                                             : "<none>",
                test_part_result.line_number(),
                test_part_result.summary());
        }
    }
};


int main(int argc, char** argv) {
    // LinePrinterLogSink Sink("/tmp/test_log.log");
    // absl::AddLogSink(&Sink);
    // absl::log_internal::SetTimeZone(absl::LocalTimeZone());
    // absl::log_internal::SetInitialized();

    // Org-mode structure fuzzing had to be implemented as a set of
    // recursive functions and not recursive domain builder, so in order to
    // accomodate for the document depth increased stack limit is required.
    SetStackSize(32 * 1024 * 1024);


#ifdef ORG_USE_PERFETTO
    std::unique_ptr<perfetto::TracingSession>
        tracing_session = StartProcessTracing("Perfetto track example");

    finally end_trace{[&]() {
        StopTracing(
            std::move(tracing_session),
            "/tmp/t_common_main_perfetto_trace.pftrace");
    }};
#endif


    ::testing::InitGoogleTest(&argc, argv);

    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--hax_vscode_run") {
            // Removes the default console output listener from the list so
            // it will not receive events from Google Test and won't print
            // any output.
            ::testing::TestEventListeners& listeners = ::testing::UnitTest::
                                                           GetInstance()
                                                               ->listeners();

            // Adds a listener to the end. Google Test takes the ownership.
            delete listeners.Release(listeners.default_result_printer());
            listeners.Append(new QuietTestPrinter());
        }
    }

    auto result = RUN_ALL_TESTS();

    json          records = TestProfiler::getJsonRecords();
    std::ofstream test_records{"/tmp/compact_records.json"};
    test_records << to_compact_json(records);


    return result;
}
