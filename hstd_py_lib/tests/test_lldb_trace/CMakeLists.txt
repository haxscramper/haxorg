cmake_minimum_required(VERSION 3.28)

project(hstd_py_lldb_fixture LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

find_package(
    Python
    COMPONENTS
        Interpreter
        Development.Module
    REQUIRED
)
find_package(nanobind CONFIG REQUIRED)

add_executable(hstd_py_lldb_fixture native.cpp)
set_target_properties(
    hstd_py_lldb_fixture
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY
            "${CMAKE_BINARY_DIR}/bin"
)

nanobind_add_module(hstd_py_lldb_fixture_extension module.cpp)
set_target_properties(
    hstd_py_lldb_fixture_extension
    PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY
            "${CMAKE_BINARY_DIR}/python"
)

target_compile_options(
    hstd_py_lldb_fixture
    PRIVATE
        -O0
        -g
)
target_compile_options(
    hstd_py_lldb_fixture_extension
    PRIVATE
        -O0
        -g
)
