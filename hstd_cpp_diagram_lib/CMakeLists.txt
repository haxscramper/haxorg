cmake_minimum_required(VERSION 3.28)
project(hstd_cpp_diagram_lib LANGUAGES CXX)

set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

include(CMakePackageConfigHelpers)

find_package(Protobuf CONFIG REQUIRED)
find_package(kiwi CONFIG REQUIRED)
find_package(cgraph CONFIG REQUIRED)
find_package(Adaptagrams CONFIG REQUIRED)

find_package(hstd_cpp_lib CONFIG REQUIRED)
if(NOT DEFINED hstd_cpp_lib_PROTO_IMPORT_DIR)
    message(
        FATAL_ERROR
        "hstd_cpp_lib did not expose "
        "hstd_cpp_lib_PROTO_IMPORT_DIR"
    )
endif()

find_package(re2 CONFIG REQUIRED)
find_package(protovalidate_cc CONFIG REQUIRED)

if(NOT DEFINED protovalidate_cc_PROTO_IMPORT_DIR)
    message(
        FATAL_ERROR
        "protovalidate_cc did not expose "
        "protovalidate_cc_PROTO_IMPORT_DIR"
    )
endif()

if(BUILD_TESTING)
    find_package(GTest CONFIG REQUIRED)

    set_property(
        TARGET
            GTest::gmock
            GTest::gtest
        PROPERTY
            SYSTEM
                TRUE
    )
endif()

haxorg_add_library(hstd_cpp_diagram_lib)
add_library(hstd_cpp_diagram_lib::hstd_cpp_diagram_lib ALIAS hstd_cpp_diagram_lib)

haxorg_glob_add_sources2(
    TARGET hstd_cpp_diagram_lib
    LS_REGEX "${CMAKE_CURRENT_LIST_DIR}/src/.*"
    SEARCH_BASE "${CMAKE_CURRENT_LIST_DIR}"
    RECURSE ON
)

add_subdirectory(jni_elk)

target_link_libraries(
    hstd_cpp_diagram_lib
    PUBLIC
        hstd::hstd_cpp_lib
        kiwi::kiwi
        cgraph::cgraph
        adaptagrams::adaptagrams
        jni_elk_lib
)

haxorg_add_protobuf(
    TARGET hstd_cpp_diagram_lib
    UNIQUE_TARGET hstd_cpp_diagram_lib_proto
    IMPORT_DIRS
        "${CMAKE_CURRENT_LIST_DIR}/proto"
        "${hstd_cpp_lib_PROTO_IMPORT_DIR}"
        "${protovalidate_cc_PROTO_IMPORT_DIR}"
    PROTO_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/proto/hstd_cpp_diagram_lib/graph_graphviz.proto"
        "${CMAKE_CURRENT_LIST_DIR}/proto/hstd_cpp_diagram_lib/graph_avoid.proto"
        "${CMAKE_CURRENT_LIST_DIR}/proto/hstd_cpp_diagram_lib/graph_elk.proto"
        "${CMAKE_CURRENT_LIST_DIR}/proto/hstd_cpp_diagram_lib/kiwi_ir.proto"
        "${CMAKE_CURRENT_LIST_DIR}/proto/hstd_cpp_diagram_lib/graph_kiwi.proto"
        "${CMAKE_CURRENT_LIST_DIR}/proto/hstd_cpp_diagram_lib/graph_diagram.proto"
        "${CMAKE_CURRENT_LIST_DIR}/proto/hstd_cpp_diagram_lib/graph_visual.proto"
)

target_include_directories(
    hstd_cpp_diagram_lib
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>"
        "$<INSTALL_INTERFACE:include>"
)

set_target_properties(
    hstd_cpp_diagram_lib
    PROPERTIES
        OUTPUT_NAME
            hstd_cpp_diagram_lib
        EXPORT_NAME
            hstd_cpp_diagram_lib
)

if(BUILD_TESTING)
    enable_testing()
    haxorg_add_executable(hstd_cpp_diagram_lib_tests)

    haxorg_glob_add_sources2(
        TARGET hstd_cpp_diagram_lib_tests
        LS_REGEX "${CMAKE_CURRENT_LIST_DIR}/tests/.*"
        SEARCH_BASE "${CMAKE_CURRENT_LIST_DIR}"
    )

    target_link_libraries(
        hstd_cpp_diagram_lib_tests
        PRIVATE
            GTest::gtest
            GTest::gmock
            GTest::gtest_main
            hstd_cpp_diagram_lib
    )
    add_test(NAME hstd_cpp_diagram_lib_tests COMMAND hstd_cpp_diagram_lib_tests)
endif()

set(HSTD_CPP_DIAGRAM_LIB_CMAKE_DIR "lib/cmake/hstd_cpp_diagram_lib")

install(
    TARGETS
        hstd_cpp_diagram_lib
        jni_elk_lib
    EXPORT hstd_cpp_diagram_lib_targets
    ARCHIVE
        DESTINATION lib
    LIBRARY
        DESTINATION lib
    RUNTIME
        DESTINATION bin
    INCLUDES DESTINATION
        include
)

install(
    EXPORT hstd_cpp_diagram_lib_targets
    NAMESPACE hstd_cpp_diagram_lib::
    FILE hstd_cpp_diagram_lib-targets.cmake
    DESTINATION "${HSTD_CPP_DIAGRAM_LIB_CMAKE_DIR}"
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/hstd_cpp_diagram_lib-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/hstd_cpp_diagram_lib-config.cmake"
    INSTALL_DESTINATION "${HSTD_CPP_DIAGRAM_LIB_CMAKE_DIR}"
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/hstd_cpp_diagram_lib-config.cmake"
    DESTINATION "${HSTD_CPP_DIAGRAM_LIB_CMAKE_DIR}"
)

install(
    DIRECTORY
        "${CMAKE_CURRENT_SOURCE_DIR}/src/"
    DESTINATION include/
    FILES_MATCHING
    PATTERN "*.hpp"
)

install(
    DIRECTORY
        "${CMAKE_CURRENT_BINARY_DIR}/"
    DESTINATION include/
    FILES_MATCHING
    PATTERN "*.pb.h"
    PATTERN "CMakeFiles"
        EXCLUDE
)

install(
    DIRECTORY
        "${CMAKE_CURRENT_SOURCE_DIR}/proto/"
    DESTINATION "share/hstd_cpp_diagram_lib/proto"
    FILES_MATCHING
    PATTERN "*.proto"
)
