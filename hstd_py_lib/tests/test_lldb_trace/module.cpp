#include "fixture.hpp"

#include <nanobind/nanobind.h>

NB_MODULE(hstd_py_lldb_fixture_extension, module) {
    module.def("run", &trace_fixture::hidden_frame);
    module.def("abort_process", &trace_fixture::abort_process);
}
