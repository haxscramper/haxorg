cmake_minimum_required(VERSION 3.28)

project(haxorg_cpp_py_wrap VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(
    Python
    COMPONENTS
        Interpreter
        Development.Module
    REQUIRED
)

find_package(nanobind CONFIG REQUIRED)

if(NOT TARGET hstd::hstd_cpp_lib)
    find_package(hstd_cpp_lib CONFIG REQUIRED)
endif()

if(NOT TARGET haxorg::haxorg_cpp_org_lib)
    find_package(haxorg_cpp_org_lib CONFIG REQUIRED)
endif()

set(HAXORG_CPP_PY_WRAP_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/haxorg_cpp_py_wrap")

nanobind_add_module(
    haxorg_cpp_py_wrap
    "${HAXORG_CPP_PY_WRAP_SOURCE_DIR}/pyhaxorg.cpp"
    "${HAXORG_CPP_PY_WRAP_SOURCE_DIR}/pyhaxorg_manual_impl.cpp"
    "${HAXORG_CPP_PY_WRAP_SOURCE_DIR}/pyhaxorg_manual_refl.cpp"
    "${HAXORG_CPP_PY_WRAP_SOURCE_DIR}/pyhaxorg_manual_impl.hpp"
)

haxorg_set_target_flags(haxorg_cpp_py_wrap)

set_target_properties(
    haxorg_cpp_py_wrap
    PROPERTIES
        OUTPUT_NAME
            "haxorg_cpp_py_wrap"
        LIBRARY_OUTPUT_DIRECTORY
            "${CMAKE_CURRENT_BINARY_DIR}/python"
        RUNTIME_OUTPUT_DIRECTORY
            "${CMAKE_CURRENT_BINARY_DIR}/python"
)

target_include_directories(haxorg_cpp_py_wrap PRIVATE "${HAXORG_CPP_PY_WRAP_SOURCE_DIR}")

target_link_libraries(haxorg_cpp_py_wrap PRIVATE haxorg::haxorg_cpp_org_lib)

add_library(haxorg::haxorg_cpp_py_wrap ALIAS haxorg_cpp_py_wrap)

install(TARGETS haxorg_cpp_py_wrap LIBRARY DESTINATION python RUNTIME DESTINATION python)
