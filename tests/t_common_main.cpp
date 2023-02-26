#pragma once

#include "common.hpp"
#include <hstd/system/aux_utils.hpp>
#include <iostream>


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

TestParameters testParameters;

using namespace Catch::Clara;


int main(int argc, const char** argv) {
    setlocale(LC_ALL, "en_US.utf8");

    trace_out = fopen("/tmp/cyg_profile_trace.log", "w");
    finally        close{[]() { fclose(trace_out); }};
    Catch::Session session;

    auto cli = session.cli()
             | Opt(testParameters.corpusGlob,
                   "Glob pattern")["--corpus-glob"]("Corpus glob pattern");
    session.cli(cli);
    auto ret = session.applyCommandLine(argc, argv);
    if (ret) {
        return ret;
    }
    auto result = session.run(argc, argv);
    std::cout << "Done test execution" << std::endl;
    return result;
}
