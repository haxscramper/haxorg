cmake_minimum_required(VERSION 3.28)

project(hstd_py_text_layout VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(CMakePackageConfigHelpers)

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
find_package(hstd_cpp_text_layout CONFIG REQUIRED)

nanobind_add_module(
    hstd_py_text_layout
    "${CMAKE_CURRENT_SOURCE_DIR}/src/py_textlayout.cpp"
)

haxorg_set_target_output(hstd_py_text_layout)
haxorg_set_target_flags(hstd_py_text_layout)

set_target_properties(
    hstd_py_text_layout
    PROPERTIES
        OUTPUT_NAME
            "py_textlayout_cpp"
)

target_include_directories(hstd_py_text_layout PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(
    hstd_py_text_layout
    PRIVATE
        hstd::hstd_cpp_lib
        hstd::hstd_cpp_text_layout
)

add_library(hstd::hstd_py_text_layout ALIAS hstd_py_text_layout)

install(
    TARGETS
        hstd_py_text_layout
    EXPORT hstd_py_text_layout-targets
    LIBRARY
        DESTINATION "."
    RUNTIME
        DESTINATION "."
)

install(
    EXPORT hstd_py_text_layout-targets
    FILE hstd_py_text_layout-targets.cmake
    NAMESPACE hstd::
    DESTINATION lib/cmake/hstd_py_text_layout
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/hstd_py_text_layout-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/hstd_py_text_layout-config.cmake"
    INSTALL_DESTINATION lib/cmake/hstd_py_text_layout
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/hstd_py_text_layout-config-version.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/hstd_py_text_layout-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/hstd_py_text_layout-config-version.cmake"
    DESTINATION lib/cmake/hstd_py_text_layout
)
