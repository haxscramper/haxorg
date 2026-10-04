#include <nanobind/nanobind.h>

#include <ex_cpp_library/value.hpp>

NB_MODULE(ex_cpp_nanobind, module) { module.def("value", &ex_fixture::value); }
