cmake_minimum_required(VERSION 3.28)

project(haxorg_cpp_org_cli VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

include(CMakePackageConfigHelpers)

if(NOT TARGET hstd::hstd_cpp_lib)
    find_package(hstd_cpp_lib CONFIG REQUIRED)
endif()

if(NOT TARGET haxorg::haxorg_cpp_org_lib)
    find_package(haxorg_cpp_org_lib CONFIG REQUIRED)
endif()

if(NOT TARGET hstd::hstd_cpp_diagram_lib)
    find_package(hstd_cpp_diagram_lib CONFIG REQUIRED)
endif()

find_package(absl CONFIG REQUIRED)
find_package(argparse CONFIG REQUIRED)

add_executable(haxorg_cpp_org_cli)

haxorg_glob_add_sources2(
    TARGET haxorg_cpp_org_cli
    LS_REGEX "${CMAKE_CURRENT_SOURCE_DIR}/src/haxorg_cpp_org_cli/.*"
    SEARCH_BASE "${CMAKE_CURRENT_SOURCE_DIR}"
    RECURSE ON
)

haxorg_set_target_output(haxorg_cpp_org_cli)
haxorg_set_target_flags(haxorg_cpp_org_cli)

target_link_libraries(
    haxorg_cpp_org_cli
    PRIVATE
        haxorg::haxorg_cpp_org_lib
        hstd::hstd_cpp_diagram_lib
        absl::base
        absl::log
        absl::flags
        argparse::argparse
)

target_include_directories(
    haxorg_cpp_org_cli
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>"
)

add_executable(haxorg::haxorg_cpp_org_cli ALIAS haxorg_cpp_org_cli)

install(
    TARGETS
        haxorg_cpp_org_cli
    EXPORT haxorg_cpp_org_cli_targets
    RUNTIME
        DESTINATION bin
)

install(
    EXPORT haxorg_cpp_org_cli_targets
    FILE haxorg_cpp_org_cli-targets.cmake
    NAMESPACE haxorg::
    DESTINATION lib/cmake/haxorg_cpp_org_cli
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/haxorg_cpp_org_cli-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/haxorg_cpp_org_cli-config.cmake"
    INSTALL_DESTINATION lib/cmake/haxorg_cpp_org_cli
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/haxorg_cpp_org_cli-config-version.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/haxorg_cpp_org_cli-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/haxorg_cpp_org_cli-config-version.cmake"
    DESTINATION lib/cmake/haxorg_cpp_org_cli
)
