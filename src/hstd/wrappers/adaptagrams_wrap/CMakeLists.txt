set(COLA_DIR "${DEPS_DIR}/adaptagrams/cola")
include(CMakeParseArguments)

add_library(adaptagrams)
haxorg_target_setup_v2(TARGET adaptagrams FORCE_NO_ASAN ON)
target_link_libraries(
  adaptagrams
  PUBLIC Adaptagrams::cola
         Adaptagrams::avoid
         Adaptagrams::dialect
         Adaptagrams::topology
         Adaptagrams::vpsc
         hstd
         absl::log
         absl::base)

target_include_directories(adaptagrams PUBLIC "${COLA_DIR}")

glob_add_sources2(
  TARGET
  "adaptagrams"
  LS_REGEX
  "${CMAKE_CURRENT_SOURCE_DIR}/.*"
  SEARCH_BASE
  "${CMAKE_CURRENT_SOURCE_DIR}"
  RECURSE
  OFF)

pybind11_add_module(py_adaptagrams "${BASE}/src/py_libs/py_adaptagrams/adaptagrams_py_wrap.cpp"
                    "${BASE}/src/py_libs/py_adaptagrams/adaptagrams_ir_refl_target.cpp")

set_target_properties(py_adaptagrams PROPERTIES OUTPUT_NAME "py_adaptagrams" SUFFIX ".so")

haxorg_target_setup_v2(TARGET py_adaptagrams FORCE_NO_ASAN ON)
target_link_libraries(py_adaptagrams PRIVATE hstd ${PYTHON_LIBRARIES} ubsan haxorg
                                             Perfetto::perfetto adaptagrams)

set_target_properties(
  py_adaptagrams
  PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
             LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
             ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
