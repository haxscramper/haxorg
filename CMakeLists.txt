cmake_minimum_required(VERSION 3.28)

cmake_policy(SET CMP0135 NEW)
cmake_policy(SET CMP0148 OLD) # or NEW
cmake_policy(SET CMP0155 NEW)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

# include(conda_toolchain.cmake)

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

# Describe relative paths to the shared and header libraries packaged with LLVM in order for the
# code to compile, link and execute correctly. Note that runtime execution will use these library
# paths as well

# Directory with clang-related runtime libraries such as asan that are shipped with LLVM
set(LLVM_GNU_CLANG_DIR "${LLVM_DIR}/lib/clang/18/lib/x86_64-unknown-linux-gnu")
# Declare variable for the asan library path, it is used in target setups, this is not some specific
# variable that is implicitly consumed, just declared it here
set(LLVM_ASAN_LIBRARY "${LLVM_GNU_CLANG_DIR}/libclang_rt.asan.so")
set(PACKAGED_STD_VERSION "14")

message(STATUS "[DBG] LLVM_STD_INCLUDE = ${LLVM_STD_INCLUDE}")
message(STATUS "[DBG] LLVM_GNU_CLANG_DIR = ${LLVM_GNU_CLANG_DIR}")

file(MAKE_DIRECTORY ${AUTOGEN_BUILD_DIR})
list(PREPEND CMAKE_MODULE_PATH ${DEPS_DIR})
include(src/cmake/functions_aux.cmake)
include(src/cmake/functions_setup.cmake)

option(ORG_INSTRUMENT_TRACE "Generate instrumentation trace" OFF)
option(ORG_USE_COVERAGE "Enable test coverage" OFF)
option(MAX_COMPILE_ERRORS "Max number of compilation errors before compiler stops")
option(ORG_USE_PERFETTO "Enable perfetto profiling" OFF)
option(ORG_USE_PGO_GENERATION "Compile binary with profile data generation" OFF)
option(ORG_USE_PGO_READER "Compile binary using profile data generation" OFF)
option(ORG_USE_XRAY "Use LLVM XRay instrumentation for profiling" OFF)
option(ORG_USE_SANITIZER "Use sanitizers" ON)
# Adaptagrams in the editor project uses libtooling for compilation and does not react well to the
# changes in the main environment. Sometimes it does not build or does not rebuild things. By
# default this option forces the dependency to be configured for all builds.
option(ORG_FORCE_ADAPTAGRAMS_BUILD "Force update and build of the external adaptagrams library" ON)

message(STATUS "ORG_USE_SANITIZER = ${ORG_USE_SANITIZER}")

set(DEPS_DIR "${BASE}/thirdparty")
set(DEPS_BINARY "${CMAKE_BINARY_DIR}/deps")
message(STATUS "Binary directory for dependencies ${DEPS_BINARY}")

set(DEPS_INSTALL "${BASE}/build/deps_install")
message(STATUS "DEPS_INSTALL = ${DEPS_INSTALL}")

list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/yaml/share/cmake/yaml-cpp")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/SQLiteCpp/lib/cmake/SQLiteCpp")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/range-v3/lib/cmake/range-v3")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/pybind11/share/cmake/pybind11")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/protobuf/lib/cmake/protobuf")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/mp11/lib/cmake/boost_mp11-1.85.0")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/lager/lib/cmake/Lager")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/immer/lib/cmake/Immer")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/googletest/lib/cmake/GTest")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/abseil/lib/cmake/absl")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/json/share/cmake/nlohmann_json")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/reflex/lib/cmake/reflex")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/perfetto/lib/cmake/Perfetto")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/describe/lib/cmake/BoostDescribe")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/adaptagrams/lib/cmake/Adaptagrams")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/utf8_range/lib/cmake/utf8_range")

set(ENV{PKG_CONFIG_PATH} "${DEPS_INSTALL}/libgit2/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}")

find_package(PkgConfig)
pkg_check_modules(CAIROMM REQUIRED cairomm-1.0)
pkg_check_modules(LIBGIT2 REQUIRED libgit2)

find_package(yaml-cpp CONFIG REQUIRED)
find_package(pybind11 CONFIG REQUIRED)
find_package(absl CONFIG REQUIRED)
find_package(range-v3 CONFIG REQUIRED)
find_package(Immer CONFIG REQUIRED)
find_package(Lager CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(SQLiteCpp CONFIG REQUIRED)
find_package(boost_mp11 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(protobuf CONFIG REQUIRED)
find_package(Reflex CONFIG REQUIRED)
if(${ORG_USE_PERFETTO})
  find_package(Perfetto CONFIG REQUIRED)
endif()
find_package(BoostDescribe CONFIG REQUIRED)
find_package(PythonLibs 3.11)
find_package(Adaptagrams CONFIG REQUIRED)

include("${DEPS_DIR}/protobuf/cmake/protobuf-generate.cmake")

set(JSON_BuildTests
    OFF
    CACHE INTERNAL "")

add_subdirectory(src/hstd)
add_subdirectory(src/hstd/wrappers/adaptagrams_wrap)
add_subdirectory(src/haxorg)
add_subdirectory(src/py_libs)

add_subdirectory(scripts/cxx_repository)
add_subdirectory(scripts/cxx_codegen)
add_subdirectory("${BASE}/src/editor")

install(
  TARGETS haxorg hstd
  EXPORT HaxorgTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES
  DESTINATION include)

install(
  DIRECTORY src/
  DESTINATION include
  FILES_MATCHING
  PATTERN "*.hpp"
  PATTERN "*.tcc"
  PATTERN "*Exporter.cpp")

install(
  DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/
  DESTINATION include
  FILES_MATCHING
  PATTERN "*.pb.h")

install(
  EXPORT HaxorgTargets
  FILE HaxorgTargets.cmake
  NAMESPACE haxorg::
  DESTINATION lib/cmake/haxorg)

include(CMakePackageConfigHelpers)

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/HaxorgConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/HaxorgConfig.cmake" INSTALL_DESTINATION lib/cmake/haxorg)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/HaxorgConfigVersion.cmake"
  VERSION "0.3.7"
  COMPATIBILITY AnyNewerVersion)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/HaxorgConfig.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/HaxorgConfigVersion.cmake" DESTINATION lib/cmake/haxorg)

add_library(haxorg::haxorg ALIAS haxorg)
add_library(haxorg::hstd ALIAS hstd)
