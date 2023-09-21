cmake_minimum_required(VERSION 3.5)

#include(conda_toolchain.cmake)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CXX_STANDARD 23)

project(haxorg LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
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
include(functions_aux.cmake)
include(functions_setup.cmake)

# TODO enable and use
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -ggdb")

conan_basic_setup()

option(USE_PCH "Use precompiled headers" ON)
option(TRACE_INSTRUMENT "Generate instrumentation trace")
option(USE_SINGLE_FILE_CATCH "Use single-file catch2 or installed one")
option(TEST_COVERAGE "Enable test coverage")
option(MAX_COMPILE_ERRORS
       "Max number of compilation errors before compiler stops")

option(USE_PERFETTO "Enable perfetto profiling")
option(PROFILE_GENERATE "Compile binary with profile data generation")
option(PROFILE_USE "Compile binary using profile data generation")
option(USE_XRAY "Use LLVM XRay instrumentation for profiling")
option(USE_SANITIZER "Use sanitizers" ON)

find_package(fmt REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(Qt6 COMPONENTS Gui Core Network REQUIRED)

include(target_hstd.cmake)
include(target_codegen.cmake)
include(target_lib.cmake)

include(target_tests.cmake)
include(target_cli.cmake)

target_sources(cli
  PRIVATE
    src/py_libs/pyhaxorg/pyhaxorg_manual.cpp
)
include(target_pyhaxorg.cmake)


