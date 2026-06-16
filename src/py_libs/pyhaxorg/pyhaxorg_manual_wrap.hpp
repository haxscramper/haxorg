#ifndef PY_HAXORG_COMPILING

#    undef slots
#    include <haxorg/sem/SemOrg.hpp>
#    include <nanobind/nanobind.h>

#    include "pyhaxorg_manual_impl.hpp"

nanobind::module_& m = *((nanobind::module_*)nullptr);

#endif

init_py_manual_api(m);
