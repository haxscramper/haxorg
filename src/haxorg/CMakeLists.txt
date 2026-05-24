add_library(haxorg)
set_common_files(haxorg)

glob_add_sources2(TARGET haxorg LS_REGEX "${BASE}/src/haxorg/.*" SEARCH_BASE "${BASE}")

set_target_output(haxorg)
set_target_flags(haxorg)

if(${ORG_BUILD_WITH_PROTOBUF})
  haxorg_add_protobuf(
    TARGET
    haxorg
    UNIQUE_TARGET
    haxorg_sem_protobuf
    IMPORT_DIRS
    "${BASE}/src/haxorg/serde"
    PROTO_SOURCES
    "${BASE}/src/haxorg/serde/SemOrgProto.proto"
    "${BASE}/src/haxorg/serde/SemOrgProtoManual.proto")

  haxorg_add_protobuf(
    TARGET
    haxorg
    UNIQUE_TARGET
    haxorg_imm_graph_protobuf
    IMPORT_DIRS
    "${BASE}/src/haxorg/serde"
    "${BASE}/src/haxorg/imm"
    PROTO_SOURCES
    "${BASE}/src/haxorg/imm/ImmOrgGraph.proto")
endif()

target_link_libraries(haxorg PUBLIC hstd range-v3::range-v3 nlohmann_json::nlohmann_json
                                    foonathan::lexy immer::immer)

if(${ORG_BUILD_WITH_CGRAPH})
  find_package(graphviz REQUIRED)
  target_link_libraries(haxorg PUBLIC graphviz::cgraph graphviz::gvc)
endif()

if(${ORG_BUILD_WITH_PERFETTO})
  target_link_libraries(haxorg PUBLIC Perfetto::perfetto)
endif()

if(${ORG_BUILD_WITH_TRACY})
  target_link_libraries(haxorg PUBLIC Tracy::TracyClient)
endif()

target_include_directories(haxorg PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
                                         $<INSTALL_INTERFACE:src>)

if(${ORG_BUILD_TESTS})
  add_executable(tests_org)
  target_link_libraries(tests_org PUBLIC haxorg absl::base absl::log absl::flags)
  set_common_files(tests_org)
  set_target_output(tests_org)
  set_target_flags(tests_org)
  glob_add_sources2(TARGET tests_org LS_REGEX "${BASE}/tests/org/.*" SEARCH_BASE "${BASE}")

  add_custom_command(
    TARGET tests_org
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E create_symlink "${CMAKE_BINARY_DIR}"
            "${CMAKE_SOURCE_DIR}/build/haxorg")

  target_sources(tests_org PRIVATE "${BASE}/tests/common.cpp")
  target_sources(tests_org PRIVATE "${BASE}/tests/testprofiler.cpp")
  target_link_libraries(tests_org PUBLIC haxorg GTest::gtest)

  if(${ORG_BUILD_WRAPPERS_C})
    target_link_libraries(tests_org PUBLIC haxorg_c)
  endif()

  target_include_directories(tests_org PUBLIC "${BASE}/thirdparty/immer" "${BASE}/thirdparty/lager")

  add_executable(specrunner_org)
  set_common_files(specrunner_org)
  set_target_output(specrunner_org)
  set_target_flags(specrunner_org)
  glob_add_sources2(TARGET specrunner_org LS_REGEX "${BASE}/tests/specrunner/.*" SEARCH_BASE
                    "${BASE}")
  target_link_libraries(specrunner_org PUBLIC haxorg)
endif()
