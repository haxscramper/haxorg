#pragma once

#include <gtest/gtest.h>
#include <hstd/system/aux_utils.hpp>
#include <iostream>
#include <hstd/system/string_convert.hpp>
#include <hstd/stdlib/Debug.hpp>
#include <fstream>
#include "../testprofiler.hpp"

#ifdef USE_PERFETTO
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

int main(int argc, char** argv) {
#ifdef USE_PERFETTO
    qInfo() << "Compiled with perfetto trace enabled, starting perfetto";
    InitializePerfetto();
    auto tracing_session = StartTracing();

    // Give a custom name for the traced process.
    perfetto::ProcessTrack process_track = perfetto::ProcessTrack::
        Current();
    perfetto::protos::gen::TrackDescriptor desc = process_track
                                                      .Serialize();
    desc.mutable_process()->set_process_name("Example");
    perfetto::TrackEvent::SetTrackDescriptor(process_track, desc);
#endif

    ::testing::InitGoogleTest(&argc, argv);
    auto result = RUN_ALL_TESTS();

    json          records = TestProfiler::getJsonRecords();
    std::ofstream test_records{"/tmp/compact_records.json"};
    test_records << to_compact_json(records);

#ifdef USE_PERFETTO
    StopTracing(std::move(tracing_session));
#endif

    return result;
}
