cmake_minimum_required(VERSION 3.28)

project(haxorg_cpp_org_lib VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)
include(CMakePackageConfigHelpers)

option(HAXORG_WITH_PROTOBUF "Build protobuf serialization support" ON)
option(HAXORG_WITH_PROTOVALIDATE "Build protobuf validation support" OFF)
option(HAXORG_WITH_PERFETTO "Build Perfetto instrumentation support" OFF)

if(HAXORG_WITH_PROTOVALIDATE AND NOT HAXORG_WITH_PROTOBUF)
    message(FATAL_ERROR "HAXORG_WITH_PROTOVALIDATE requires HAXORG_WITH_PROTOBUF")
endif()

find_package(hstd_cpp_lib CONFIG REQUIRED)
find_package(hstd_cpp_text_layout CONFIG REQUIRED)

find_package(range-v3 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(lexy CONFIG REQUIRED)
find_package(Immer CONFIG REQUIRED)

if(HAXORG_WITH_PROTOBUF)
    find_package(protobuf CONFIG REQUIRED)
endif()

if(HAXORG_WITH_PROTOVALIDATE)
    find_package(protovalidate_cc CONFIG REQUIRED)
endif()

if(HAXORG_WITH_PERFETTO)
    find_package(Perfetto CONFIG REQUIRED)
endif()

if(BUILD_TESTING)
    find_package(GTest CONFIG REQUIRED)
    find_package(absl CONFIG REQUIRED)
endif()

set(BASE "${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(src)

install(
    DIRECTORY
        src/
    DESTINATION include
    FILES_MATCHING
    PATTERN "*.h"
    PATTERN "*.hpp"
    PATTERN "*.tcc"
    PATTERN "*Exporter.cpp"
)

install(
    DIRECTORY
        "${CMAKE_CURRENT_BINARY_DIR}/"
    DESTINATION include
    FILES_MATCHING
    PATTERN "*.pb.h"
)

install(
    EXPORT HaxorgCppOrgLibTargets
    FILE HaxorgCppOrgLibTargets.cmake
    NAMESPACE haxorg::
    DESTINATION lib/cmake/HaxorgCppOrgLib
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/HaxorgCppOrgLibConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/HaxorgCppOrgLibConfig.cmake"
    INSTALL_DESTINATION lib/cmake/HaxorgCppOrgLib
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/HaxorgCppOrgLibConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/HaxorgCppOrgLibConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/HaxorgCppOrgLibConfigVersion.cmake"
    DESTINATION lib/cmake/HaxorgCppOrgLib
)
