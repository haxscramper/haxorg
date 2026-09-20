cmake_minimum_required(VERSION 3.28)
project(hstd)

set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

include(functions_setup.cmake)
include(functions_aux.cmake)

find_package(yaml-cpp CONFIG REQUIRED)
find_package(range-v3 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(cctz CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(Boost CONFIG REQUIRED)
find_package(cpptrace CONFIG REQUIRED)

if(ORG_BUILD_WITH_PROTOBUF)
    find_package(Protobuf CONFIG REQUIRED)
endif()

if(ORG_BUILD_WITH_PROTOVALIDATE)
    find_package(re2 CONFIG REQUIRED)
    find_package(protovalidate_cc CONFIG REQUIRED)

    if(NOT DEFINED protovalidate_cc_PROTO_IMPORT_DIR)
        message(
            FATAL_ERROR
            "protovalidate_cc did not expose "
            "protovalidate_cc_PROTO_IMPORT_DIR"
        )
    endif()
endif()

if(ORG_BUILD_WITH_PERFETTO)
    find_package(Perfetto CONFIG REQUIRED)
endif()

if(ORG_BUILD_WITH_TRACY)
    find_package(Tracy CONFIG REQUIRED)
endif()

if(ORG_BUILD_TESTS)
    find_package(GTest CONFIG REQUIRED)
    find_package(benchmark CONFIG REQUIRED)
    find_package(absl CONFIG REQUIRED)
    find_package(immer CONFIG REQUIRED)

    set_property(
        TARGET
            immer::immer
        PROPERTY
            SYSTEM
                TRUE
    )
    set_property(
        TARGET
            GTest::gmock
        PROPERTY
            SYSTEM
                TRUE
    )
    set_property(
        TARGET
            GTest::gtest
        PROPERTY
            SYSTEM
                TRUE
    )
endif()

if(ORG_BUILD_WITH_QT)
    find_package(Qt6 COMPONENTS REQUIRED Core)

    qt_add_library(hstd_cpp_lib STATIC)
    haxorg_set_target_output(hstd_cpp_lib)
    haxorg_set_target_flags(hstd_cpp_lib)

    target_link_libraries(hstd_cpp_lib PUBLIC Qt6::Core)
    target_compile_definitions(hstd_cpp_lib PUBLIC ORG_BUILD_WITH_QT=1)

    set_target_properties(
        hstd_cpp_lib
        PROPERTIES
            AUTOMOC
                ON
            AUTOUIC
                ON
            AUTORCC
                ON
    )
else()
    haxorg_add_library(hstd_cpp_lib)
endif()

add_library(hstd::hstd_cpp_lib ALIAS hstd_cpp_lib)

haxorg_glob_add_sources2(
    TARGET hstd_cpp_lib
    LS_REGEX
        "${CMAKE_CURRENT_LIST_DIR}/src/hstd_cpp_lib/(extra|geometry|graph|logger|proto_serde|stdlib|system)/.*"
    SEARCH_BASE "${CMAKE_CURRENT_LIST_DIR}"
)

target_include_directories(hstd_cpp_lib PUBLIC "${CMAKE_CURRENT_LIST_DIR}")

target_link_libraries(
    hstd_cpp_lib
    PUBLIC
        yaml-cpp::yaml-cpp
        range-v3::range-v3
        nlohmann_json::nlohmann_json
        cctz::cctz
        fmt::fmt
        Boost::headers
)

if(NOT ORG_BUILD_EMCC)
    target_link_libraries(
        hstd_cpp_lib
        PUBLIC
            Boost::log
            cpptrace::cpptrace
    )
endif()

# Tracing
if(ORG_BUILD_WITH_PERFETTO)
    target_link_libraries(hstd_cpp_lib PUBLIC Perfetto::perfetto)
endif()

if(ORG_BUILD_WITH_TRACY)
    target_link_libraries(hstd_cpp_lib PUBLIC Tracy::TracyClient)
endif()

if(ORG_BUILD_WITH_PROTOBUF)
    set(HSTD_PROTO_PUBLIC_LIBRARIES)
    set(HSTD_PROTO_IMPORT_DIRS "${CMAKE_CURRENT_LIST_DIR}/proto")

    if(ORG_BUILD_WITH_PROTOVALIDATE)
        list(APPEND HSTD_PROTO_PUBLIC_LIBRARIES protovalidate_cc::protovalidate_cc)
        list(APPEND HSTD_PROTO_IMPORT_DIRS "${protovalidate_cc_PROTO_IMPORT_DIR}")
    endif()

    haxorg_add_protobuf(
        TARGET hstd_cpp_lib
        UNIQUE_TARGET hstd_proto_base_graph
        IMPORT_DIRS
            ${HSTD_PROTO_IMPORT_DIRS}
        PROTO_SOURCES
            "${CMAKE_CURRENT_LIST_DIR}/proto/hstd_cpp_lib/graph_base.proto"
            "${CMAKE_CURRENT_LIST_DIR}/proto/hstd_cpp_lib/error_write.proto"
            "${CMAKE_CURRENT_LIST_DIR}/proto/hstd_cpp_lib/hstd_geometry_test_ir.proto"
            "${CMAKE_CURRENT_LIST_DIR}/proto/hstd_cpp_lib/hstd_geometry.proto"
            "${CMAKE_CURRENT_LIST_DIR}/proto/hstd_cpp_lib/hstd_visual.proto"
        PUBLIC_LIBRARIES
            ${HSTD_PROTO_PUBLIC_LIBRARIES}
    )
endif()

target_include_directories(
    hstd_cpp_lib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:src>
)

if(ORG_BUILD_TESTS)
    enable_testing()
    haxorg_add_executable(hstd_cpp_tests)

    if(ORG_BUILD_WITH_QT)
        target_compile_definitions(hstd_cpp_tests PUBLIC ORG_BUILD_WITH_QT=1)
    endif()

    haxorg_glob_add_sources2(
        TARGET hstd_cpp_tests
        LS_REGEX "${CMAKE_CURRENT_LIST_DIR}/tests/.*"
        SEARCH_BASE "${CMAKE_CURRENT_LIST_DIR}"
    )
    target_link_libraries(
        hstd_cpp_tests
        PRIVATE
            GTest::gtest
            GTest::gmock
            hstd_cpp_lib
            absl::flags
            absl::flags_parse
            immer::immer
    )
    add_test(NAME hstd_tests COMMAND hstd_cpp_tests)
endif()

set_target_properties(
    hstd_cpp_lib
    PROPERTIES
        OUTPUT_NAME
            hstd
        EXPORT_NAME
            hstd
)

target_include_directories(
    hstd_cpp_lib
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>"
        "$<INSTALL_INTERFACE:include>"
)

install(
    TARGETS
        hstd_cpp_lib
    EXPORT hstdTargets
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
    DIRECTORY
        "${CMAKE_CURRENT_SOURCE_DIR}/src/"
    DESTINATION include/hstd_cpp_lib
    FILES_MATCHING
    PATTERN "*.hpp"
)
