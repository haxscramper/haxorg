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
find_package(hstd CONFIG REQUIRED)
find_package(HstdCppTextLayout CONFIG REQUIRED)

set(BASE "${CMAKE_CURRENT_SOURCE_DIR}")

nanobind_add_module(
    hstd_py_text_layout
    "${BASE}/src/py_textlayout.cpp"
)

haxorg_set_target_output(hstd_py_text_layout)
haxorg_set_target_flags(hstd_py_text_layout)

set_target_properties(
    hstd_py_text_layout
    PROPERTIES
        OUTPUT_NAME
            "py_textlayout_cpp"
)

target_include_directories(hstd_py_text_layout PRIVATE "${BASE}/src")

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
    EXPORT HstdPyTextLayoutTargets
    LIBRARY
        DESTINATION "."
    RUNTIME
        DESTINATION "."
)

install(
    EXPORT HstdPyTextLayoutTargets
    FILE HstdPyTextLayoutTargets.cmake
    NAMESPACE hstd::
    DESTINATION lib/cmake/HstdPyTextLayout
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/HstdPyTextLayoutConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/HstdPyTextLayoutConfig.cmake"
    INSTALL_DESTINATION lib/cmake/HstdPyTextLayout
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/HstdPyTextLayoutConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/HstdPyTextLayoutConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/HstdPyTextLayoutConfigVersion.cmake"
    DESTINATION lib/cmake/HstdPyTextLayout
)
