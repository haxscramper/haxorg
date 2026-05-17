/* clang-format off */
#undef slots
#include <adaptagrams/adaptagrams_ir.hpp>
#include <py_libs/nanobind_utils.hpp>
#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/map.h>
#include <nanobind/stl/array.h>
#include <nanobind/stl/filesystem.h>
#include <nanobind/stl/function.h>
#include <nanobind/stl/map.h>
#include <nanobind/stl/optional.h>
#include <nanobind/stl/set.h>
#include <nanobind/stl/shared_ptr.h>
#include <nanobind/stl/string_view.h>
#include <nanobind/stl/tuple.h>
#include <nanobind/stl/unique_ptr.h>
#include <nanobind/stl/unordered_map.h>
#include <nanobind/stl/variant.h>
#include <nanobind/operators.h>
#include <nanobind/make_iterator.h>
#include <nanobind/ndarray.h>
NB_MODULE(py_adaptagrams, m) {
  org::bind::python::PyTypeRegistryGuard type_registry_guard{};
  nanobind::set_leak_warnings(false);
}
/* clang-format on */