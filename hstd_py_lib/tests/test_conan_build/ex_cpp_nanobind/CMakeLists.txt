cmake_minimum_required(VERSION 3.28)

project(ex_cpp_nanobind VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

find_package(
    Python
    COMPONENTS
        Interpreter
        Development.Module
    REQUIRED
)
find_package(nanobind CONFIG REQUIRED QUIET)
find_package(ex_cpp_library CONFIG REQUIRED QUIET)

nanobind_add_module(ex_cpp_nanobind src/ex_cpp_nanobind/module.cpp)

target_link_libraries(ex_cpp_nanobind PRIVATE ex::ex_cpp_library)

install(TARGETS ex_cpp_nanobind LIBRARY DESTINATION lib)
