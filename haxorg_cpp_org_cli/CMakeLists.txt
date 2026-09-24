cmake_minimum_required(VERSION 3.28)

project(haxorg_cpp_org_cli VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CMakePackageConfigHelpers)

find_package(hstd_cpp_lib CONFIG REQUIRED)
find_package(haxorg_cpp_org_lib CONFIG REQUIRED)
find_package(absl CONFIG REQUIRED)
find_package(argparse CONFIG REQUIRED)

add_executable(haxorg_cpp_org_cli)

haxorg_glob_add_sources2(
    TARGET haxorg_cpp_org_cli
    LS_REGEX "${CMAKE_CURRENT_SOURCE_DIR}/src/.*"
    SEARCH_BASE "${CMAKE_CURRENT_SOURCE_DIR}"
    DEBUG ON
    RECURSE ON
)

haxorg_set_target_output(haxorg_cpp_org_cli)
haxorg_set_target_flags(haxorg_cpp_org_cli)

target_link_libraries(
    haxorg_cpp_org_cli
    PRIVATE
        haxorg::haxorg_cpp_lib
        absl::base
        absl::log
        absl::flags
        argparse::argparse
)

add_executable(haxorg::haxorg_cpp_cli ALIAS haxorg_cpp_org_cli)

install(
    TARGETS
        haxorg_cpp_org_cli
    EXPORT haxorg_cpp_org_cli_targets
    RUNTIME
        DESTINATION bin
)

install(
    EXPORT haxorg_cpp_org_cli_targets
    FILE haxorg_cpp_org_cli_targets.cmake
    NAMESPACE haxorg::
    DESTINATION lib/cmake/HaxorgCppOrgCli
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/HaxorgCppOrgCli_config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/HaxorgCppOrgCliConfig.cmake"
    INSTALL_DESTINATION lib/cmake/HaxorgCppOrgCli
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/HaxorgCppOrgCliConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/HaxorgCppOrgCliConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/HaxorgCppOrgCliConfigVersion.cmake"
    DESTINATION lib/cmake/HaxorgCppOrgCli
)
