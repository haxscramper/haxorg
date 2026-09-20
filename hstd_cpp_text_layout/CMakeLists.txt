cmake_minimum_required(VERSION 3.28)

project(hstd_cpp_text_layout VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)
include(CMakePackageConfigHelpers)

find_package(hstd_cpp_lib CONFIG REQUIRED)

set(BASE "${CMAKE_CURRENT_SOURCE_DIR}")

haxorg_add_library(hstd_cpp_text_layout)

haxorg_glob_add_sources2(
    TARGET hstd_cpp_text_layout
    LS_REGEX "${BASE}/src/.*"
    SEARCH_BASE "${BASE}"
)

haxorg_set_target_output(hstd_cpp_text_layout)
haxorg_set_target_flags(hstd_cpp_text_layout)

target_link_libraries(hstd_cpp_text_layout PUBLIC hstd::hstd_cpp_lib)

target_include_directories(
    hstd_cpp_text_layout
    PUBLIC
        $<BUILD_INTERFACE:${BASE}/src>
        $<INSTALL_INTERFACE:include>
)

add_library(hstd::hstd_cpp_text_layout ALIAS hstd_cpp_text_layout)

install(
    TARGETS
        hstd_cpp_text_layout
    EXPORT HstdCppTextLayoutTargets
    LIBRARY
        DESTINATION lib
    ARCHIVE
        DESTINATION lib
    RUNTIME
        DESTINATION bin
    INCLUDES DESTINATION
        include
)

install(
    DIRECTORY
        src/
    DESTINATION include
    FILES_MATCHING
    PATTERN "*.h"
    PATTERN "*.hpp"
    PATTERN "*.tcc"
)

install(
    EXPORT HstdCppTextLayoutTargets
    FILE HstdCppTextLayoutTargets.cmake
    NAMESPACE hstd::
    DESTINATION lib/cmake/HstdCppTextLayout
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/HstdCppTextLayoutConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/HstdCppTextLayoutConfig.cmake"
    INSTALL_DESTINATION lib/cmake/HstdCppTextLayout
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/HstdCppTextLayoutConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/HstdCppTextLayoutConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/HstdCppTextLayoutConfigVersion.cmake"
    DESTINATION lib/cmake/HstdCppTextLayout
)
