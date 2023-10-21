cmake_minimum_required(VERSION 3.5)

#include(conda_toolchain.cmake)



project(haxorg LANGUAGES CXX)

set(BASE "${CMAKE_SOURCE_DIR}")
message(INFO "CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
set(LLVM_DIR "${BASE}/toolchain/llvm")

set(DEPS_DIR "${BASE}/build/dependencies/conan")
set(AUTOGEN_BUILD_DIR "${BASE}/build/autogen")
set(SCRIPT_DIR "${BASE}/src/scripts")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(MAKE_DIRECTORY ${AUTOGEN_BUILD_DIR})
list(PREPEND CMAKE_MODULE_PATH ${DEPS_DIR})
include(${DEPS_DIR}/conanbuildinfo.cmake)
include(src/cmake/functions_aux.cmake)
include(src/cmake/functions_setup.cmake)

conan_basic_setup(TARGETS)

option(USE_PCH "Use precompiled headers" ON)
option(TRACE_INSTRUMENT "Generate instrumentation trace")
option(TEST_COVERAGE "Enable test coverage")
option(MAX_COMPILE_ERRORS "Max number of compilation errors before compiler stops")
option(USE_PERFETTO "Enable perfetto profiling")
option(USE_PGO "Compile binary with profile data generation")
option(PROFILE_USE "Compile binary using profile data generation")
option(USE_XRAY "Use LLVM XRay instrumentation for profiling")
option(USE_SANITIZER "Use sanitizers" ON)


find_package(fmt REQUIRED MODULE)
find_package(yaml-cpp REQUIRED MODULE)
find_package(benchmark REQUIRED MODULE)
find_package(PythonLibs 3.11 MODULE)
find_package(pybind11 REQUIRED MODULE)
find_package(perfetto REQUIRED MODULE)

#add_subdirectory("${BASE}/deps/abseil-cpp")
add_subdirectory("${BASE}/deps/fuzztest")

include(src/cmake/target_hstd.cmake)
include(src/cmake/target_codegen.cmake)
include(src/cmake/target_lib.cmake)

include(src/cmake/target_tests.cmake)
include(src/cmake/target_tests_hstd.cmake)
include(src/cmake/target_bench.cmake)


include(src/cmake/target_pyhaxorg.cmake)


