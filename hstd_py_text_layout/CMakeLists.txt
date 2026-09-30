cmake_minimum_required(VERSION 3.28)

project(hstd_cpp_text_layout_py_wrap VERSION 0.1.0 LANGUAGES CXX)

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
    hstd_cpp_text_layout_py_wrap
    "${CMAKE_CURRENT_SOURCE_DIR}/src/hstd_cpp_text_layout_py_wrap/py_textlayout.cpp"
)

haxorg_set_target_output(hstd_cpp_text_layout_py_wrap)
haxorg_set_target_flags(hstd_cpp_text_layout_py_wrap)

set_target_properties(
    hstd_cpp_text_layout_py_wrap
    PROPERTIES
        OUTPUT_NAME
            "py_textlayout_cpp"
)

target_include_directories(
    hstd_cpp_text_layout_py_wrap
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(
    hstd_cpp_text_layout_py_wrap
    PRIVATE
        hstd::hstd_cpp_lib
        hstd::hstd_cpp_text_layout
)

add_library(hstd::hstd_cpp_text_layout_py_wrap ALIAS hstd_cpp_text_layout_py_wrap)

install(
    TARGETS
        hstd_cpp_text_layout_py_wrap
    EXPORT hstd_cpp_text_layout_py_wrap-targets
    LIBRARY
        DESTINATION "."
    RUNTIME
        DESTINATION "."
)

install(
    EXPORT hstd_cpp_text_layout_py_wrap-targets
    FILE hstd_cpp_text_layout_py_wrap-targets.cmake
    NAMESPACE hstd::
    DESTINATION lib/cmake/hstd_cpp_text_layout_py_wrap
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/hstd_cpp_text_layout_py_wrap-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/hstd_cpp_text_layout_py_wrap-config.cmake"
    INSTALL_DESTINATION lib/cmake/hstd_cpp_text_layout_py_wrap
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/hstd_cpp_text_layout_py_wrap-config-version.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/hstd_cpp_text_layout_py_wrap-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/hstd_cpp_text_layout_py_wrap-config-version.cmake"
    DESTINATION lib/cmake/hstd_cpp_text_layout_py_wrap
)
