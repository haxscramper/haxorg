haxorg_add_library(haxorg_cpp_lib)

haxorg_glob_add_sources2(
    TARGET haxorg_cpp_lib
    LS_REGEX "${BASE}/src/haxorg/.*"
    SEARCH_BASE "${BASE}"
)

haxorg_set_target_output(haxorg_cpp_lib)
haxorg_set_target_flags(haxorg_cpp_lib)

target_link_libraries(
    haxorg_cpp_lib
    PUBLIC
        hstd::hstd_cpp_lib
        hstd::hstd_cpp_text_layout
        range-v3::range-v3
        nlohmann_json::nlohmann_json
        foonathan::lexy
        immer::immer
)

target_include_directories(
    haxorg_cpp_lib
    PUBLIC
        $<BUILD_INTERFACE:${BASE}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
        $<INSTALL_INTERFACE:include>
)

target_compile_definitions(
    haxorg_cpp_lib
    PUBLIC
        ORG_BUILD_WITH_PROTOBUF=$<BOOL:${HAXORG_WITH_PROTOBUF}>
        ORG_BUILD_WITH_PROTOVALIDATE=$<BOOL:${HAXORG_WITH_PROTOVALIDATE}>
        ORG_BUILD_WITH_PERFETTO=$<BOOL:${HAXORG_WITH_PERFETTO}>
        ORG_BUILD_WITH_CGRAPH=0
        ORG_BUILD_WITH_ADAPTAGRAMS=0
        ORG_BUILD_WITH_KIWI=0
        ORG_BUILD_WITH_ELK=0
        ORG_BUILD_WITH_TRACY=0
)

if(HAXORG_WITH_PROTOBUF)
    set(HAXORG_PROTO_PUBLIC_LIBRARIES)
    set(HAXORG_PROTO_IMPORT_DIRS "${BASE}")

    if(HAXORG_WITH_PROTOVALIDATE)
        list(APPEND HAXORG_PROTO_PUBLIC_LIBRARIES protovalidate_cc::protovalidate_cc)
        list(APPEND HAXORG_PROTO_IMPORT_DIRS "${protovalidate_cc_PROTO_IMPORT_DIR}")
    endif()

    haxorg_add_protobuf(
        TARGET haxorg_cpp_lib
        UNIQUE_TARGET haxorg_sem_protobuf
        IMPORT_DIRS
            ${HAXORG_PROTO_IMPORT_DIRS}
        PROTO_SOURCES
            "${BASE}/src/haxorg/serde/SemOrgProto.proto"
            "${BASE}/src/haxorg/serde/SemOrgProtoManual.proto"
            "${BASE}/src/haxorg/serde/OrgApiProto.proto"
        PUBLIC_LIBRARIES
            ${HAXORG_PROTO_PUBLIC_LIBRARIES}
    )

    haxorg_add_protobuf(
        TARGET haxorg_cpp_lib
        UNIQUE_TARGET haxorg_imm_graph_protobuf
        IMPORT_DIRS
            ${HAXORG_PROTO_IMPORT_DIRS}
        PROTO_SOURCES
            "${BASE}/src/haxorg/imm/ImmOrgGraph.proto"
        PUBLIC_LIBRARIES
            ${HAXORG_PROTO_PUBLIC_LIBRARIES}
    )
endif()

if(HAXORG_WITH_PERFETTO)
    target_link_libraries(haxorg_cpp_lib PUBLIC Perfetto::perfetto)
endif()

add_library(haxorg::haxorg_cpp_lib ALIAS haxorg_cpp_lib)

install(
    TARGETS
        haxorg_cpp_lib
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
        LS_REGEX "${BASE}/tests/org/.*"
        SEARCH_BASE "${BASE}"
    )

    target_sources(
        haxorg_cpp_org_tests
        PRIVATE
            "${BASE}/tests/common.cpp"
            "${BASE}/tests/testprofiler.cpp"
    )

    target_link_libraries(
        haxorg_cpp_org_tests
        PRIVATE
            haxorg_cpp_lib
            GTest::gtest
            absl::base
            absl::log
            absl::flags
    )

    haxorg_set_target_output(haxorg_cpp_org_tests)
    haxorg_set_target_flags(haxorg_cpp_org_tests)

    add_test(NAME haxorg_cpp_org_tests COMMAND haxorg_cpp_org_tests)

    add_executable(haxorg_cpp_org_specrunner)

    haxorg_glob_add_sources2(
        TARGET haxorg_cpp_org_specrunner
        LS_REGEX "${BASE}/tests/specrunner/.*"
        SEARCH_BASE "${BASE}"
    )

    target_link_libraries(haxorg_cpp_org_specrunner PRIVATE haxorg_cpp_lib)

    haxorg_set_target_output(haxorg_cpp_org_specrunner)
    haxorg_set_target_flags(haxorg_cpp_org_specrunner)
endif()
