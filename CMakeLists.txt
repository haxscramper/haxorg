cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CXX_STANDARD 23)

project(haxorg LANGUAGES CXX)

set(BASE "${CMAKE_SOURCE_DIR}")
set(DEPS_DIR "${BASE}/build/dependencies/conan")
set(AUTOGEN_BUILD_DIR "${BASE}/build/autogen")
set(SCRIPT_DIR "${BASE}/src/scripts")

file(MAKE_DIRECTORY ${AUTOGEN_BUILD_DIR})
list(PREPEND CMAKE_MODULE_PATH ${DEPS_DIR})
include(${DEPS_DIR}/conanbuildinfo.cmake)
include(functions_aux.cmake)
include(functions_setup.cmake)

conan_basic_setup()

option(TRACE_INSTRUMENT "Generate instrumentation trace")
option(USE_SINGLE_FILE_CATCH "Use single-file catch2 or installed one")
option(TEST_COVERAGE "Enable test coverage")
option(MAX_COMPILE_ERRORS
       "Max number of compilation errors before compiler stops")



find_package(fmt REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)


include(target_lib.cmake)
include(autogen_enums.cmake)

add_dependencies(haxorg autogen_enums)

include(target_tests.cmake)
include(target_cli.cmake)


