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

set(SCRIPT_DIR "${BASE}/src/scripts")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-attributes")

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
option(ORG_EMCC_BUILD "Building for emscripten target" OFF)

option(ORG_DEPS_INSTALL_ROOT "Root path for custom dependency installation root" OFF)
option(ORG_DEPS_USE_PROTOBUF "Include protobuf functionality in the build" ON)
option(ORG_DEPS_USE_ADAPTAGRAMS "Enable adaptagrams-based features (graph layout and utilities)" ON)
option(ORG_BUILD_IS_DEVELOP "Don't build and configure internal development dependencies" ON)
option(ORG_BUILD_USE_GOLD_WRAPPER "Link profilng" OFF)
option(ORG_BUILD_TESTS "" ON)
option(ORG_BUILD_ASSUME_CLANG "Assume clang++ compiler for the build" ON)
option(ORG_DEPS_USE_PACKAGED_BOOST "Use boost library headers from the third-party" ON)
option(ORG_DEPS_USE_PYTHON_VERSION "" "3.13")
option(ORG_BUILD_USE_NAPI_WRAPPER "" ON)

message(STATUS "ORG_USE_SANITIZER = ${ORG_USE_SANITIZER}")

set(DEPS_DIR "${BASE}/thirdparty")
message(STATUS "ORG_DEPS_INSTALL_ROOT = '${ORG_DEPS_INSTALL_ROOT}'")

if(ORG_DEPS_INSTALL_ROOT STREQUAL "OFF")
  set(DEPS_INSTALL "${BASE}/build/deps_install")
else()
  set(DEPS_INSTALL "${ORG_DEPS_INSTALL_ROOT}")
endif()

message(STATUS "DEPS_INSTALL = ${DEPS_INSTALL}")

list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/yaml/share/cmake/yaml-cpp")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/yaml/lib/cmake/yaml-cpp")
if(${ORG_BUILD_IS_DEVELOP})
  list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/SQLiteCpp/lib/cmake/SQLiteCpp")
endif()
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/range-v3/lib/cmake/range-v3")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/pybind11/share/cmake/pybind11")
if(${ORG_DEPS_USE_PROTOBUF})
  list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/protobuf/lib/cmake/protobuf")
endif()
if(${ORG_DEPS_USE_PACKAGED_BOOST})
  list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/mp11/lib/cmake/boost_mp11-1.85.0")
endif()
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/lager/lib/cmake/Lager")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/immer/lib/cmake/Immer")
if(${ORG_BUILD_TESTS})
  list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/googletest/lib/cmake/GTest")
endif()
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/abseil/lib/cmake/absl")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/json/share/cmake/nlohmann_json")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/reflex/lib/cmake/reflex")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/perfetto/lib/cmake/Perfetto")
if(${ORG_DEPS_USE_PACKAGED_BOOST})
  list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/describe/lib/cmake/BoostDescribe")
endif()
if(${ORG_DEPS_USE_ADAPTAGRAMS})
  list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/adaptagrams/lib/cmake/Adaptagrams")
endif()
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/utf8_range/lib/cmake/utf8_range")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/lexy/lib/cmake/lexy")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/cpptrace/lib/cmake/cpptrace")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/cpptrace/lib/cmake/libdwarf")

if(${ORG_BUILD_IS_DEVELOP})
  set(ENV{PKG_CONFIG_PATH} "${DEPS_INSTALL}/libgit2/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}")
endif()

find_package(PkgConfig)
if(NOT ${ORG_EMCC_BUILD})
  pkg_check_modules(CAIROMM REQUIRED cairomm-1.0)
endif()

if(${ORG_BUILD_IS_DEVELOP} AND NOT ${ORG_EMCC_BUILD})
  pkg_check_modules(LIBGIT2 REQUIRED libgit2)
endif()

find_package(yaml-cpp CONFIG REQUIRED)
if(${ORG_DEPS_USE_PYTHON_VERSION})
  set(PYBIND11_PYTHON_VERSION ${ORG_DEPS_USE_PYTHON_VERSION})
  set(PYTHON_VERSION ${ORG_DEPS_USE_PYTHON_VERSION})
else()
  set(PYBIND11_PYTHON_VERSION 3.13)
  set(PYTHON_VERSION 3.13)
endif()
message(STATUS "XXXX PYBIND11_PYTHON_VERSION = ${PYBIND11_PYTHON_VERSION} ")
find_package(pybind11 CONFIG REQUIRED)
find_package(absl CONFIG REQUIRED)
find_package(range-v3 CONFIG REQUIRED)
find_package(Immer CONFIG REQUIRED)
find_package(Lager CONFIG REQUIRED)
if(${ORG_BUILD_IS_DEVELOP})
  find_package(SQLiteCpp CONFIG REQUIRED)
endif()
if(${ORG_BUILD_TESTS})
  find_package(GTest CONFIG REQUIRED)
endif()
if(${ORG_DEPS_USE_PACKAGED_BOOST})
  message(STATUS "ORG_DEPS_TMP_TOGGLE = ${ORG_DEPS_TMP_TOGGLE}")
  find_package(boost_mp11 CONFIG REQUIRED)
endif()
find_package(nlohmann_json CONFIG REQUIRED)
# Protobuf is necessary for reflection library, so it is enabled unconditionally
find_package(protobuf CONFIG REQUIRED)
find_package(Reflex CONFIG REQUIRED)
find_package(lexy CONFIG REQUIRED)
if(${ORG_USE_PERFETTO})
  find_package(Perfetto CONFIG REQUIRED)
endif()
if(${ORG_DEPS_USE_PACKAGED_BOOST})
  find_package(BoostDescribe CONFIG REQUIRED)
endif()
find_package(PythonLibs 3.13)
if(${ORG_DEPS_USE_ADAPTAGRAMS})
  find_package(Adaptagrams CONFIG REQUIRED)
endif()
find_package(cpptrace CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS log)

if(${ORG_DEPS_USE_PROTOBUF})
  add_definitions(-DORG_DEPS_USE_PROTOBUF)
endif()
include("${DEPS_DIR}/protobuf/cmake/protobuf-generate.cmake")
message(STATUS "PYTHON_LIBRARIES = ${PYTHON_LIBRARIES}")

set(JSON_BuildTests
    OFF
    CACHE INTERNAL "")

add_subdirectory(src/hstd)
if(${ORG_DEPS_USE_ADAPTAGRAMS})
  add_definitions(-DORG_DEPS_USE_ADAPTAGRAMS)
  add_subdirectory(src/adaptagrams)
endif()
add_subdirectory(src/haxorg)
add_subdirectory(src/py_libs)

if(${ORG_BUILD_IS_DEVELOP})
  add_subdirectory(scripts/cxx_repository)
  add_subdirectory(scripts/cxx_codegen)
endif()

if(${ORG_BUILD_USE_NAPI_WRAPPER})
  add_subdirectory(src/wrappers/js)
endif()

if(${ORG_DEPS_USE_ADAPTAGRAMS})
  set(ORG_INSTALL_TARGET_LIST haxorg hstd adaptagrams)
else()
  set(ORG_INSTALL_TARGET_LIST haxorg hstd)
endif()

install(
  TARGETS ${ORG_INSTALL_TARGET_LIST}
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

set(CPACK_SOURCE_IGNORE_FILES
    "\\.mypy_cache"
    "\\.git"
    "\\.mepo"
    "\\.venv"
    "/build.*/"
    "/install.*/"
    "/toolchain/"
    "/thirdparty/"
    "\\.cache"
    "examples"
    "htmlcov"
    "\\.hypothesis"
    "docs"
    "scripts"
    "\\.trunk"
    "node_modules"
    "__pycache__"
    "_CPack_Packages"
    "html"
    "\\.xmake"
    "\\.idea"
    "\\.py"
    "\\.coverage"
    "latex"
    "\\.vscode"
    ".*\\.zip"
    "\\.profraw$"
    "perf\\..*"
    "/\\..*"
    "/dist/")

option(ORG_CPACK_PACKAGE_VERSION "Package version for cpack export" "1.0.0")
option(ORG_CPACK_PACKAGE_NAME "Package name for cpack export" "haxorg")

set(CPACK_PACKAGE_NAME "${ORG_CPACK_PACKAGE_NAME}")
set(CPACK_PACKAGE_VERSION "${ORG_CPACK_PACKAGE_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "C++ parser for org-mode language")

set(CPACK_COMPONENTS_ALL hstd)
set(CPACK_SOURCE_GENERATOR "ZIP")

include(CPack)
