#pragma once

#include "common.hpp"

#include <absl/strings/str_split.h>
#include <absl/log/log_sink_registry.h>
#include <absl/log/initialize.h>
#include <absl/log/internal/globals.h>
#include <sys/resource.h>

#include <gtest/gtest.h>
#include <hstd/system/aux_utils.hpp>
#include <iostream>
#include <hstd/system/string_convert.hpp>
#include <hstd/stdlib/Debug.hpp>
#include <fstream>

extern void enable_full_trace_on_cli();

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
            std::cout << ::hstd::fmt(
                "{} in {}:{}\n{}\n",
                test_part_result.failed() ? "*** Failure" : "Success",
                test_part_result.file_name() ? test_part_result.file_name()
                                             : "<none>",
                test_part_result.line_number(),
                test_part_result.summary());
        }
    }
};


void init_gtest_tests(int& argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    std::vector<char*> new_argv;
    new_argv.push_back(argv[0]);

    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--hax_vscode_run") {
            // Removes the default console output listener from the list so
            // it will not receive events from Google Test and won't print
            // any output.
            ::testing::TestEventListeners& listeners //
                = ::testing::UnitTest::GetInstance()->listeners();

            // Adds a listener to the end. Google Test takes the ownership.
            delete listeners.Release(listeners.default_result_printer());
            listeners.Append(new QuietTestPrinter());
        } else if (std::string(argv[i]) == "--trace_all_test") {
            enable_full_trace_on_cli();
        } else {
            new_argv.push_back(argv[i]);
        }
    }

    argc = static_cast<int>(new_argv.size());
    for (int i = 0; i < argc; ++i) { argv[i] = new_argv[i]; }
}
