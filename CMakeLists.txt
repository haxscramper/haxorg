cmake_minimum_required(VERSION 3.28)

cmake_policy(SET CMP0135 NEW)
cmake_policy(SET CMP0148 OLD) # or NEW
cmake_policy(SET CMP0155 NEW)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

#include(conda_toolchain.cmake)

set(ABSL_CC_LIB_COPTS "-fPIC")
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

project(haxorg LANGUAGES CXX)

set(BASE "${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
set(LLVM_DIR "${BASE}/toolchain/llvm")
set(TOOLCHAIN_DIR "${BASE}/toolchain")

set(AUTOGEN_BUILD_DIR "${BASE}/build/autogen")
set(SCRIPT_DIR "${BASE}/src/scripts")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)


## Describe relative paths to the shared and header libraries packaged with LLVM
## in order for the code to compile, link and execute correctly. Note that runtime
## execution will use these library paths as well

# Directory with clang-related runtime libraries such as asan that are shipped 
# with LLVM
set(LLVM_GNU_CLANG_DIR "${LLVM_DIR}/lib/clang/18/lib/x86_64-unknown-linux-gnu")
# Declare variable for the asan library path, it is used in target setups, this
# is not some specific variable that is implicitly consumed, just declared it here
set(LLVM_ASAN_LIBRARY "${LLVM_GNU_CLANG_DIR}/libclang_rt.asan.so")
set(PACKAGED_STD_VERSION "14")

message(STATUS "[DBG] LLVM_STD_INCLUDE = ${LLVM_STD_INCLUDE}")
message(STATUS "[DBG] LLVM_GNU_CLANG_DIR = ${LLVM_GNU_CLANG_DIR}")

file(MAKE_DIRECTORY ${AUTOGEN_BUILD_DIR})
list(PREPEND CMAKE_MODULE_PATH ${DEPS_DIR})
include(src/cmake/functions_aux.cmake)
include(src/cmake/functions_setup.cmake)

option(ORG_USE_PCH "Use precompiled headers" ON)
option(ORG_INSTRUMENT_TRACE "Generate instrumentation trace" OFF)
option(ORG_USE_COVERAGE "Enable test coverage" OFF)
option(MAX_COMPILE_ERRORS "Max number of compilation errors before compiler stops")
option(ORG_USE_PERFETTO "Enable perfetto profiling" OFF)
option(ORG_USE_PGO_GENERATION "Compile binary with profile data generation" OFF)
option(ORG_USE_PGO_READER "Compile binary using profile data generation" OFF)
option(ORG_USE_XRAY "Use LLVM XRay instrumentation for profiling" OFF)
option(ORG_USE_SANITIZER "Use sanitizers" ON) 
# Adaptagrams in the editor project uses libtooling for compilation and does not react
# well to the changes in the main environment. Sometimes it does not build or does not
# rebuild things. By default this option forces the dependency to be configured for all
# builds.
option(ORG_FORCE_ADAPTAGRAMS_BUILD "Force update and build of the external adaptagrams library" ON)

message(STATUS "ORG_USE_SANITIZER = ${ORG_USE_SANITIZER}")



# if (${ORG_USE_SANITIZER})
#     # Enable the sanitizer options. They are set globally primarity for the
#     # in-source dependencies like google fuzztest, ABSL and so on -- if there
#     # is a way to set them in a more focused manner they should be moved to the
#     # respective consumers of these flags.
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined,address")
#     set(VAR_ORG_SANITIZER_LINK_FLAGS "-fsanitize=undefined,address -L${ASAN_RT_PATH} -Wl,-rpath,${ASAN_RT_PATH}")
#     set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${VAR_ORG_SANITIZER_LINK_FLAGS}")
#     set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${VAR_ORG_SANITIZER_LINK_FLAGS}")
# endif()



set(DEPS_DIR "${BASE}/thirdparty")
set(DEPS_BINARY "${CMAKE_BINARY_DIR}/deps")
message(STATUS "Binary directory for dependencies ${DEPS_BINARY}")

add_subdirectory("${DEPS_DIR}/yaml-cpp")

add_library(perfetto STATIC "${DEPS_DIR}/perfetto/sdk/perfetto.cc")
target_include_directories(perfetto PUBLIC "${DEPS_DIR}/perfetto/sdk")

add_subdirectory("${DEPS_DIR}/range-v3")

add_library(immer_lib INTERFACE)
target_include_directories(immer_lib INTERFACE "${DEPS_DIR}/immer")

add_library(lager_lib INTERFACE)
target_include_directories(lager_lib INTERFACE "${DEPS_DIR}/lager")

set(SQLITECPP_RUN_CPPLINT OFF)

add_subdirectory("${DEPS_DIR}/pybind11")

add_subdirectory("${DEPS_DIR}/abseil-cpp")
add_subdirectory("${DEPS_DIR}/googletest")
add_subdirectory("${DEPS_DIR}/SQLiteCpp")


set(protobuf_INSTALL OFF)
set(protobuf_BUILD_TESTS OFF)
set(utf8_range_ENABLE_TESTS OFF)
set(utf8_range_ENABLE_INSTALL OFF)
add_subdirectory("${DEPS_DIR}/protobuf")
include("${DEPS_DIR}/protobuf/cmake/protobuf-generate.cmake")

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(thirdparty/json)
add_subdirectory(thirdparty/mp11)
add_subdirectory(thirdparty/describe)
add_subdirectory(src/hstd)

add_subdirectory(src/hstd/wrappers/adaptagrams_wrap)

include(src/cmake/target_codegen.cmake)
include(src/cmake/target_lib.cmake)
include(src/cmake/target_pyhaxorg.cmake)

add_subdirectory(scripts/cxx_repository)
add_subdirectory(scripts/cxx_codegen)
add_subdirectory("${BASE}/src/editor")
