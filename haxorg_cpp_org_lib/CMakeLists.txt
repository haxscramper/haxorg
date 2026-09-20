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
    if(HAXORG_WITH_PROTOVALIDATE)
        find_package(protovalidate_cc CONFIG REQUIRED)
    endif()
endif()

if(HAXORG_WITH_PERFETTO)
    find_package(Perfetto CONFIG REQUIRED)
endif()

if(BUILD_TESTING)
    find_package(GTest CONFIG REQUIRED)
    find_package(absl CONFIG REQUIRED)
endif()

haxorg_add_library(haxorg_cpp_org_lib)

haxorg_glob_add_sources2(
    TARGET haxorg_cpp_org_lib
    LS_REGEX "${CMAKE_CURRENT_LIST_DIR}/src/haxorg/.*"
    SEARCH_BASE "${CMAKE_CURRENT_LIST_DIR}"
)

haxorg_set_target_output(haxorg_cpp_org_lib)
haxorg_set_target_flags(haxorg_cpp_org_lib)

target_link_libraries(
    haxorg_cpp_org_lib
    PUBLIC
        hstd::hstd_cpp_lib
        hstd::hstd_cpp_text_layout
        range-v3::range-v3
        nlohmann_json::nlohmann_json
        foonathan::lexy
        immer::immer
)

target_include_directories(
    haxorg_cpp_org_lib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
        $<INSTALL_INTERFACE:include>
)

target_compile_definitions(
    haxorg_cpp_org_lib
    PUBLIC
        ORG_BUILD_WITH_PROTOBUF=$<BOOL:${HAXORG_WITH_PROTOBUF}>
        ORG_BUILD_WITH_PROTOVALIDATE=$<BOOL:${HAXORG_WITH_PROTOVALIDATE}>
        ORG_BUILD_WITH_PERFETTO=$<BOOL:${HAXORG_WITH_PERFETTO}>
)

if(HAXORG_WITH_PROTOBUF)
    set(HAXORG_PROTO_PUBLIC_LIBRARIES)
    set(HAXORG_PROTO_IMPORT_DIRS "${CMAKE_CURRENT_LIST_DIR}/proto")
    list(APPEND HAXORG_PROTO_IMPORT_DIRS "${hstd_cpp_lib_PROTO_IMPORT_DIR}")

    if(HAXORG_WITH_PROTOVALIDATE)
        list(APPEND HAXORG_PROTO_PUBLIC_LIBRARIES protovalidate_cc::protovalidate_cc)
        list(APPEND HAXORG_PROTO_IMPORT_DIRS "${protovalidate_cc_PROTO_IMPORT_DIR}")
    endif()

    haxorg_add_protobuf(
        TARGET haxorg_cpp_org_lib
        UNIQUE_TARGET haxorg_sem_protobuf
        IMPORT_DIRS
            ${HAXORG_PROTO_IMPORT_DIRS}
        PROTO_SOURCES
            "${CMAKE_CURRENT_LIST_DIR}/proto/haxorg_cpp_org_lib/SemOrgProto.proto"
            "${CMAKE_CURRENT_LIST_DIR}/proto/haxorg_cpp_org_lib/SemOrgProtoManual.proto"
            "${CMAKE_CURRENT_LIST_DIR}/proto/haxorg_cpp_org_lib/OrgApiProto.proto"
            "${CMAKE_CURRENT_LIST_DIR}/proto/haxorg_cpp_org_lib/ImmOrgGraph.proto"
        PUBLIC_LIBRARIES
            ${HAXORG_PROTO_PUBLIC_LIBRARIES}
    )
endif()

if(HAXORG_WITH_PERFETTO)
    target_link_libraries(haxorg_cpp_org_lib PUBLIC Perfetto::perfetto)
endif()

add_library(haxorg::haxorg_cpp_org_lib ALIAS haxorg_cpp_org_lib)

install(
    TARGETS
        haxorg_cpp_org_lib
    EXPORT HaxorgCppOrgLibTargets
    LIBRARY
        DESTINATION lib
    ARCHIVE
        DESTINATION lib
    RUNTIME
        DESTINATION bin
    INCLUDES DESTINATION
        include
)

if(BUILD_TESTING)
    add_executable(haxorg_cpp_org_tests)

    haxorg_glob_add_sources2(
        TARGET haxorg_cpp_org_tests
        LS_REGEX "${CMAKE_CURRENT_LIST_DIR}/tests/.*"
        SEARCH_BASE "${CMAKE_CURRENT_LIST_DIR}"
    )

    target_link_libraries(
        haxorg_cpp_org_tests
        PRIVATE
            haxorg_cpp_org_lib
            GTest::gtest
            absl::base
            absl::log
            absl::flags
    )

    haxorg_set_target_output(haxorg_cpp_org_tests)
    haxorg_set_target_flags(haxorg_cpp_org_tests)

    add_test(NAME haxorg_cpp_org_tests COMMAND haxorg_cpp_org_tests)
endif()

install(
    DIRECTORY
        src/
    DESTINATION include
    FILES_MATCHING
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
