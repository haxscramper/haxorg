#pragma once

#include "common.hpp"
#include <hstd/system/aux_utils.hpp>


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

int main(int argc, const char** argv) {
    trace_out = fopen("/tmp/cyg_profile_trace.log", "w");
    finally close{[]() { fclose(trace_out); }};
    return Catch::Session().run(argc, argv);
}
