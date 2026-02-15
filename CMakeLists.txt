cmake_minimum_required(VERSION 3.28)

cmake_policy(SET CMP0135 NEW)
cmake_policy(SET CMP0148 OLD) # or NEW
cmake_policy(SET CMP0155 NEW)
if(POLICY CMP0167)
  cmake_policy(SET CMP0167 NEW)
endif()

set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

# include(conda_toolchain.cmake)

set(ABSL_CC_LIB_COPTS "-fPIC")
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

project(haxorg LANGUAGES CXX C)
enable_testing()

set(BASE "${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
set(LLVM_DIR "${BASE}/toolchain/llvm")
set(TOOLCHAIN_DIR "${BASE}/toolchain")

set(SCRIPT_DIR "${BASE}/src/scripts")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-attributes")
set(CMAKE_LINKER "ld.lld")

# Describe relative paths to the shared and header libraries packaged with LLVM in order for the
# code to compile, link and execute correctly. Note that runtime execution will use these library
# paths as well

list(PREPEND CMAKE_MODULE_PATH ${DEPS_DIR})
include(src/cmake/functions_aux.cmake)
include(src/cmake/functions_setup.cmake)

option(ORG_DEPS_INSTALL_ROOT "Root path for custom dependency installation root" "")

# Adaptagrams in the editor project uses libtooling for compilation and does not react well to the
# changes in the main environment. Sometimes it does not build or does not rebuild things. By
# default this option forces the dependency to be configured for all builds.
option(ORG_FORCE_ADAPTAGRAMS_BUILD "Force update and build of the external adaptagrams library" ON)
option(ORG_DISABLE_WARNINGS "Disable warnings in the build" OFF)
option(ORG_USE_SARIF "Enable SARIF reporting for build" OFF)
option(ORG_SEPARATE_DEBUG_SYMBOLS "Strip debug symbols into separate `.debug` file" OFF)

option(ORG_DEPS_USE_PACKAGED_BOOST "Use boost library headers from the third-party" OFF)

option(ORG_INSTRUMENT_TRACE "Generate instrumentation trace" OFF)
option(ORG_USE_COVERAGE "Enable test coverage" OFF)
option(MAX_COMPILE_ERRORS "Max number of compilation errors before compiler stops")
option(ORG_USE_PERFETTO "Enable perfetto profiling" OFF)
option(ORG_USE_TRACY "Enable performance profiling using tracy" OFF)
option(ORG_USE_PGO_GENERATION "Compile binary with profile data generation" OFF)
option(ORG_USE_PGO_READER "Compile binary using profile data generation" OFF)
option(ORG_USE_XRAY "Use LLVM XRay instrumentation for profiling" OFF)
option(ORG_USE_SANITIZER "Use sanitizers" ON)
option(ORG_USE_QT "Enable Qt-related features and API" OFF)
option(ORG_USE_IMGUI "Build imgui apps and API" OFF)

# Optional features in the haxorg library
option(ORG_BUILD_WITH_PROTOBUF "Include protobuf functionality in the build" ON)
option(ORG_BUILD_WITH_MSGPACK "Include msgpack serialization functionality in the build" ON)
option(ORG_BUILD_WITH_ADAPTAGRAMS "Enable adaptagrams-based features (graph layout and utilities)"
       OFF)

# Optional targets for the build
option(ORG_BUILD_EMCC "Building for emscripten target" OFF)
option(ORG_BUILD_PYHAXORG_BINDINGS "Build py-haxorg module library" ON)
option(ORG_BUILD_INTERNAL_TOOLS "The build and configure internal development tools" ON)
option(ORG_BUILD_TEXT_LAYOUTER_BINDINGS "Build text layouter python module library" ON)
option(ORG_BUILD_TESTS "Build cmake tests and benchmarks" OFF)
option(ORG_BUILD_ASSUME_CLANG "Assume clang++ compiler for the build" ON)

option(ORG_USE_CONAN_INSTALL "Auto-install dependencies by calling conan from cmake" OFF)
option(ORG_IS_CONAN_BUILD "The project is being built by conan" OFF)
option(ORG_IS_WHEEL_BUILD "The project is being built by the python wheel distribution")

if(${ORG_USE_TRACY} AND ${ORG_USE_PERFETTO})
  message(
    FATAL_ERROR
      "Tracy and perfetto profiling are mutually exclusive. Enable either ORG_USE_TRACY or ORG_USE_PERFETTO but not both"
  )
endif()

message(STATUS "ORG_USE_SANITIZER = ${ORG_USE_SANITIZER}")

if(${ORG_BUILD_EMCC})
  if(NOT CMAKE_SIZEOF_VOID_P STREQUAL "4")
    message(
      FATAL_ERROR
        "CMAKE_SIZEOF_VOID_P is not '4' (set to '${CMAKE_SIZEOF_VOID_P}') -- wasm build expects 32-bit compile"
    )
  endif()

endif()

set(DEPS_DIR "${BASE}/thirdparty")
message(STATUS "ORG_DEPS_INSTALL_ROOT = '${ORG_DEPS_INSTALL_ROOT}'")

if(${ORG_IS_CONAN_BUILD} AND ${ORG_USE_CONAN_INSTALL})
  add_definitions(-DORG_USE_CONAN_INSTALL=1)
  set(CONAN_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/.conan_install")
  set(CONAN_TOOLCHAIN
      "${CONAN_OUTPUT_DIR}/build/${CMAKE_BUILD_TYPE}/generators/conan_toolchain.cmake")

  if(NOT EXISTS "${CONAN_TOOLCHAIN}")
    message(STATUS "Running Conan install...")

    execute_process(
      COMMAND conan install ${CMAKE_SOURCE_DIR} --output-folder=${CONAN_OUTPUT_DIR}
              -pr:h=${BASE}/conanprofile.txt --build=missing -s build_type=${CMAKE_BUILD_TYPE}
      WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
      RESULT_VARIABLE CONAN_RESULT
      OUTPUT_VARIABLE CONAN_STDOUT
      ERROR_VARIABLE CONAN_STDERR
      OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_STRIP_TRAILING_WHITESPACE)

    if(NOT CONAN_RESULT EQUAL 0)
      message(
        FATAL_ERROR "Conan install failed (exit code: ${CONAN_RESULT})\n"
                    "---- stdout ----\n${CONAN_STDOUT}\n" "---- stderr ----\n${CONAN_STDERR}\n")
    endif()
  endif()

  include("${CONAN_TOOLCHAIN}")
elseif(NOT ORG_DEPS_INSTALL_ROOT OR ORG_DEPS_INSTALL_ROOT STREQUAL "OFF")
  add_definitions(-DORG_USE_CONAN_INSTALL=0)
  message(STATUS "No dependency path specified, will be using system-provided deps")
else()
  add_definitions(-DORG_USE_CONAN_INSTALL=0)
  include("${ORG_DEPS_INSTALL_ROOT}/paths.cmake")
endif()

message(STATUS "lexy_DIR = ${lexy_DIR}")

if(${ORG_BUILD_INTERNAL_TOOLS})
  set(ENV{PKG_CONFIG_PATH} "${ORG_DEPS_INSTALL_ROOT}/libgit2/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}")
endif()

find_package(PkgConfig)
if(NOT ${ORG_BUILD_EMCC})
  pkg_check_modules(CAIROMM REQUIRED cairomm-1.0)
endif()

if(${ORG_BUILD_INTERNAL_TOOLS} AND NOT ${ORG_BUILD_EMCC})
  pkg_check_modules(LIBGIT2 REQUIRED libgit2)
endif()

find_package(cctz REQUIRED)

find_package(zstd QUIET CONFIG)

if(zstd_FOUND)
  message(STATUS "Found zstd via CMake config")
  # zstd::zstd target should be available
else()
  # Fallback to pkg-config
  message(STATUS "zstd CMake config not found, trying pkg-config")
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(ZSTD REQUIRED libzstd)

  # Create an imported target to match the CONFIG mode interface
  add_library(zstd::zstd INTERFACE IMPORTED)
  set_target_properties(
    zstd::zstd
    PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${ZSTD_INCLUDE_DIRS}"
               INTERFACE_LINK_LIBRARIES "${ZSTD_LIBRARIES}"
               INTERFACE_LINK_DIRECTORIES "${ZSTD_LIBRARY_DIRS}")
endif()

if(NOT ${ORG_BUILD_EMCC})
  find_package(
    Python
    COMPONENTS Interpreter Development
    REQUIRED)
  find_package(pybind11 CONFIG REQUIRED)
endif()

if(${ORG_USE_TRACY})
  find_package(Tracy CONFIG REQUIRED)
endif()

find_package(range-v3 CONFIG REQUIRED)
find_package(Immer CONFIG REQUIRED)
if(NOT TARGET immer::immer)
  if(TARGET immer AND NOT TARGET immer::immer)
    add_library(immer::immer ALIAS immer)
  endif()
endif()

find_package(Lager CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)

if(${ORG_BUILD_WITH_MSGPACK})
  add_definitions(-DORG_BUILD_WITH_MSGPACK=1)
  find_package(msgpack-cxx CONFIG REQUIRED)
else()
  add_definitions(-DORG_BUILD_WITH_MSGPACK=0)
endif()

if(${ORG_BUILD_INTERNAL_TOOLS} AND NOT ${ORG_BUILD_EMCC})
  find_package(SQLiteCpp CONFIG REQUIRED)
endif()

if(NOT ${ORG_BUILD_EMCC})
  find_package(absl CONFIG REQUIRED)
endif()

if(${ORG_BUILD_TESTS} AND NOT ${ORG_BUILD_EMCC})
  find_package(GTest CONFIG REQUIRED)
  find_package(benchmark CONFIG REQUIRED)
endif()
if(${ORG_DEPS_USE_PACKAGED_BOOST})
  message(STATUS "ORG_DEPS_TMP_TOGGLE = ${ORG_DEPS_TMP_TOGGLE}")
  find_package(boost_mp11 CONFIG REQUIRED)
endif()
find_package(nlohmann_json CONFIG REQUIRED)

find_package(lexy CONFIG REQUIRED)
if(${ORG_USE_PERFETTO} AND NOT ${ORG_BUILD_EMCC})
  find_package(Perfetto CONFIG REQUIRED)
endif()
if(${ORG_DEPS_USE_PACKAGED_BOOST})
  find_package(BoostDescribe CONFIG REQUIRED)
  find_package(BoostPreprocessor CONFIG REQUIRED)
endif()
if(${ORG_BUILD_WITH_ADAPTAGRAMS} AND NOT ${ORG_BUILD_EMCC})
  find_package(Adaptagrams CONFIG REQUIRED)
endif()
if(NOT ${ORG_BUILD_EMCC})
  find_package(cpptrace CONFIG REQUIRED)
endif()

if(NOT ${ORG_BUILD_EMCC})
  find_package(Boost REQUIRED COMPONENTS ALL)
endif()

if(${ORG_BUILD_EMCC})
  add_definitions(-DORG_BUILD_EMCC=1)
else()
  add_definitions(-DORG_BUILD_EMCC=0)
endif()

if(${ORG_BUILD_WITH_PROTOBUF} AND NOT ${ORG_BUILD_EMCC})
  find_package(protobuf CONFIG REQUIRED)
  add_definitions(-DORG_BUILD_WITH_PROTOBUF=1)
  if(NOT ${ORG_IS_CONAN_BUILD})
    include("${DEPS_DIR}/protobuf/cmake/protobuf-generate.cmake")
  endif()
else()
  add_definitions(-DORG_BUILD_WITH_PROTOBUF=0)
endif()

message(STATUS "Python_LIBRARIES = ${Python_LIBRARIES}")

set(JSON_BuildTests
    OFF
    CACHE INTERNAL "")

add_subdirectory(src/hstd)
if(${ORG_BUILD_WITH_ADAPTAGRAMS})
  add_definitions(-DORG_BUILD_WITH_ADAPTAGRAMS)
  add_subdirectory(src/adaptagrams)
endif()
add_subdirectory(src/haxorg)
if(NOT ${ORG_BUILD_EMCC})
  add_subdirectory(src/py_libs)
endif()

if(${ORG_BUILD_INTERNAL_TOOLS} AND NOT ${ORG_BUILD_EMCC})
  add_subdirectory(scripts/cxx_repository)
  add_subdirectory(scripts/cxx_codegen)
endif()

if(${ORG_BUILD_EMCC})
  add_subdirectory(src/wrappers/js)
endif()

if(${ORG_USE_QT})
  add_subdirectory(src/app/org_viewer)
  add_subdirectory(src/app/org_diagram)
endif()

if(${ORG_USE_IMGUI})
  add_subdirectory(src/app/org_imgui)
endif()

# Build the list of "CMake package" targets (no pyhaxorg here)
if(${ORG_BUILD_WITH_ADAPTAGRAMS} AND NOT ${ORG_BUILD_EMCC})
  set(ORG_INSTALL_TARGET_LIST haxorg hstd adaptagrams)
else()
  set(ORG_INSTALL_TARGET_LIST haxorg hstd)
endif()

# Install normal libs into lib/, export them, etc.
install(
  TARGETS ${ORG_INSTALL_TARGET_LIST}
  EXPORT HaxorgTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES
  DESTINATION include)

# Install the Python extension into the *platlib root* (site-packages/)
if(${ORG_BUILD_PYHAXORG_BINDINGS} AND NOT ${ORG_BUILD_EMCC})
  install(TARGETS pyhaxorg py_textlayout_cpp LIBRARY DESTINATION ".")
endif()

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
