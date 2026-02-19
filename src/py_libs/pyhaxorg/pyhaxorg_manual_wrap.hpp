#ifndef PY_HAXORG_COMPILING

#    undef slots
#    include <pybind11/pybind11.h>
#    include <haxorg/sem/SemOrg.hpp>
#    include <pybind11/stl.h>

#    include "pyhaxorg_manual_impl.hpp"

nanobind::module_& m = *((nanobind::module_*)nullptr);

#endif

init_py_manual_api(m);
