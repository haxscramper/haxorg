cmake_minimum_required(VERSION 3.5)

#include(conda_toolchain.cmake)

set(ABSL_CC_LIB_COPTS "-fPIC")
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)


project(haxorg LANGUAGES CXX)

set(BASE "${CMAKE_SOURCE_DIR}")
message(INFO "CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
set(LLVM_DIR "${BASE}/toolchain/llvm")

set(DEPS_DIR "${BASE}/build/dependencies/conan")
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
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -I${LLVM_STD_INCLUDE} -I${LLVM_GNU_INCLUDE} -L${LLVM_DIR}/lib -ftemplate-backtrace-limit=0")

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

if (${USE_SANITIZER})
    # Enable the sanitizer options. They are set globally primarity for the
    # in-source dependencies like google fuzztest, ABSL and so on -- if there
    # is a way to set them in a more focused manner they should be moved to the
    # respective consumers of these flags.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined,address")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=undefined,address")
endif()


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
include(src/cmake/target_bench.cmake)

include(src/cmake/target_pyhaxorg.cmake)
include(src/cmake/target_lsp.cmake)

add_subdirectory(scripts/cxx_repository)
