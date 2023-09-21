#ifndef PY_HAXORG_COMPILING

#undef slots
#include <pybind11/pybind11.h>
#include <sem/SemOrg.hpp>
#include <pybind11/stl.h>

#include "pyhaxorg_manual_impl.hpp"

pybind11::module& m = *((pybind11::module*)nullptr);

#endif

init_py_manual_api(m);

