#ifndef PY_HAXORG_COMPILING

#    undef slots
#    include <nanobind/nanobind.h>
#    include <haxorg/sem/SemOrg.hpp>

#    include "pyhaxorg_manual_impl.hpp"

nanobind::module_& m = *((nanobind::module_*)nullptr);

#endif

init_py_manual_api(m);
