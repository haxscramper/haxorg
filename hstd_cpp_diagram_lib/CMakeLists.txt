cmake_minimum_required(VERSION 3.28)

project(hstd_cpp_diagram_lib VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

find_package(Protobuf CONFIG REQUIRED)
find_package(kiwi CONFIG REQUIRED)
find_package(graphviz CONFIG REQUIRED)
find_package(Adaptagrams CONFIG REQUIRED)
find_package(re2 CONFIG REQUIRED)
find_package(protovalidate_cc CONFIG REQUIRED)

if(NOT TARGET hstd::hstd_cpp_lib)
    find_package(hstd_cpp_lib CONFIG REQUIRED)
endif()

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

add_subdirectory(jni_elk)

haxorg_set_target_output(jni_elk_lib)
haxorg_set_target_flags(jni_elk_lib)

haxorg_add_library(hstd_cpp_diagram_lib)

haxorg_glob_add_sources2(
    TARGET hstd_cpp_diagram_lib
    LS_REGEX "${CMAKE_CURRENT_SOURCE_DIR}/src/hstd_cpp_diagram_lib/.*"
    SEARCH_BASE "${CMAKE_CURRENT_SOURCE_DIR}/src"
    RECURSE ON
)

haxorg_set_target_output(hstd_cpp_diagram_lib)
haxorg_set_target_flags(hstd_cpp_diagram_lib)

target_link_libraries(
    hstd_cpp_diagram_lib
    PUBLIC
        hstd::hstd_cpp_lib
        kiwi::kiwi
        graphviz::cgraph
        graphviz::gvc
        adaptagrams::adaptagrams
        jni_elk_lib
)

haxorg_add_protobuf(
    TARGET hstd_cpp_diagram_lib
    IMPORT_DIRS
        "${CMAKE_CURRENT_SOURCE_DIR}/proto"
        ${HAXORG_DEPS_PROTO_IMPORT_DIRS}
        "${protovalidate_cc_PROTO_IMPORT_DIR}"
    PROTO_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/proto/hstd_cpp_diagram_lib/graph_graphviz.proto"
        "${CMAKE_CURRENT_SOURCE_DIR}/proto/hstd_cpp_diagram_lib/graph_avoid.proto"
        "${CMAKE_CURRENT_SOURCE_DIR}/proto/hstd_cpp_diagram_lib/graph_elk.proto"
        "${CMAKE_CURRENT_SOURCE_DIR}/proto/hstd_cpp_diagram_lib/kiwi_ir.proto"
        "${CMAKE_CURRENT_SOURCE_DIR}/proto/hstd_cpp_diagram_lib/graph_kiwi.proto"
        "${CMAKE_CURRENT_SOURCE_DIR}/proto/hstd_cpp_diagram_lib/graph_diagram.proto"
        "${CMAKE_CURRENT_SOURCE_DIR}/proto/hstd_cpp_diagram_lib/graph_diagram_validate.proto"
        "${CMAKE_CURRENT_SOURCE_DIR}/proto/hstd_cpp_diagram_lib/graph_visual.proto"
)

target_include_directories(
    hstd_cpp_diagram_lib
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated/proto>"
        "$<INSTALL_INTERFACE:include>"
)

add_library(hstd::hstd_cpp_diagram_lib ALIAS hstd_cpp_diagram_lib)

if(BUILD_TESTING)
    enable_testing()

    haxorg_add_executable(hstd_cpp_diagram_lib_tests)

    haxorg_glob_add_sources2(
        TARGET hstd_cpp_diagram_lib_tests
        LS_REGEX "${CMAKE_CURRENT_SOURCE_DIR}/tests/.*"
        SEARCH_BASE "${CMAKE_CURRENT_SOURCE_DIR}"
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
