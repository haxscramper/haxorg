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
message(INFO "CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
set(LLVM_DIR "${BASE}/toolchain/llvm")

set(AUTOGEN_BUILD_DIR "${BASE}/build/autogen")
set(SCRIPT_DIR "${BASE}/src/scripts")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


## Describe relative paths to the shared and header libraries packaged with LLVM
## in order for the code to compile, link and execute correctly. Note that runtime
## execution will use these library paths as well

# Directory with clang-related runtime libraries such as asan that are shipped 
# with LLVM
set(LLVM_GNU_CLANG_DIR "${LLVM_DIR}/lib/clang/17/lib/x86_64-unknown-linux-gnu")
# Standard library, libc++.so and other things
set(LLVM_STD_DIRS "${LLVM_DIR}/lib/x86_64-unknown-linux-gnu")
# Declare variable for the asan library path, it is used in target setups, this
# is not some specific variable that is implicitly consumed, just declared it here
set(LLVM_ASAN_LIBRARY "${LLVM_GNU_CLANG_DIR}/libclang_rt.asan.so")
# Headers that standard library apparently uses to interface with the system?
set(LLVM_GNU_INCLUDE "${LLVM_DIR}/include/x86_64-unknown-linux-gnu/c++/v1")
# Standard library headers
set(LLVM_STD_INCLUDE "${LLVM_DIR}/include/c++/v1/")

# Globally configure compiler flags with all necessary flags etc., this will be shared 
# down to all sub-components and dependencies. 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -Wno-unused-command-line-argument -I${LLVM_STD_INCLUDE} -I${LLVM_GNU_INCLUDE} -L${LLVM_DIR}/lib -ftemplate-backtrace-limit=0")
# It is important to specify linker flags globally for the whole project here -- benchmark
# subdirectory depends on the cxx_feature_check which fails if the shared parts of the standard
# library are not found. Regex check compiles test code, everything is ok, but running
# would fail without adding stdc++ runtime search paths
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,${LLVM_GNU_CLANG_DIR},-rpath,${LLVM_STD_DIRS}")

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
option(ORG_USE_FUZZER "User fuzzer compilation" OFF)

if (${ORG_USE_SANITIZER})
    # Enable the sanitizer options. They are set globally primarity for the
    # in-source dependencies like google fuzztest, ABSL and so on -- if there
    # is a way to set them in a more focused manner they should be moved to the
    # respective consumers of these flags.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined,address")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=undefined,address")
endif()



set(DEPS_DIR "${BASE}/thirdparty")
set(DEPS_BINARY "${CMAKE_BINARY_DIR}/deps")
message(INFO "Binary directory for dependencies ${DEPS_BINARY}")

add_subdirectory("${DEPS_DIR}/yaml-cpp")

add_library(perfetto STATIC "${DEPS_DIR}/perfetto/sdk/perfetto.cc")
target_include_directories(perfetto PUBLIC "${DEPS_DIR}/perfetto/sdk")

add_subdirectory("${DEPS_DIR}/range-v3")

add_library(immer_lib INTERFACE)
target_include_directories(immer_lib INTERFACE "${DEPS_DIR}/immer")

add_library(lager_lib INTERFACE)
target_include_directories(lager_lib INTERFACE "${DEPS_DIR}/lager")

add_subdirectory("${DEPS_DIR}/fuzztest")
add_subdirectory("${DEPS_DIR}/pybind11")
set(protobuf_BUILD_TESTS OFF)
add_subdirectory("${DEPS_DIR}/protobuf")
include("${DEPS_DIR}/protobuf/cmake/protobuf-generate.cmake")

set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(thirdparty/json)

if(${ORG_USE_FUZZER})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${LLVM_GNU_CLANG_DIR} -lclang_rt.fuzzer_no_main")
endif()

include_directories("${BASE}/deps/fuzztest")

if(${ORG_USE_FUZZER})
    fuzztest_setup_fuzzing_flags()
endif()


include(src/cmake/target_hstd.cmake)
include(src/cmake/target_codegen.cmake)
include(src/cmake/target_lib.cmake)
include(src/cmake/target_bench.cmake)
include(src/cmake/target_pyhaxorg.cmake)
include(src/cmake/target_lsp.cmake)

add_subdirectory(scripts/cxx_repository)




