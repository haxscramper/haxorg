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
    "${BASE}"
    PROTO_SOURCES
    "${BASE}/src/haxorg/serde/SemOrgProto.proto"
    "${BASE}/src/haxorg/serde/SemOrgProtoManual.proto")

  haxorg_add_protobuf(
    TARGET
    haxorg
    UNIQUE_TARGET
    haxorg_imm_graph_protobuf
    IMPORT_DIRS
    "${BASE}"
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
  add_executable(haxorg_cpp_org_tests)
  target_link_libraries(haxorg_cpp_org_tests PUBLIC haxorg absl::base absl::log absl::flags)
  set_common_files(haxorg_cpp_org_tests)
  set_target_output(haxorg_cpp_org_tests)
  set_target_flags(haxorg_cpp_org_tests)
  glob_add_sources2(TARGET haxorg_cpp_org_tests LS_REGEX "${BASE}/tests/org/.*" SEARCH_BASE
                    "${BASE}")

  add_custom_command(
    TARGET haxorg_cpp_org_tests
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E create_symlink "${CMAKE_BINARY_DIR}"
            "${CMAKE_SOURCE_DIR}/build/haxorg")

  target_sources(haxorg_cpp_org_tests PRIVATE "${BASE}/tests/common.cpp")
  target_sources(haxorg_cpp_org_tests PRIVATE "${BASE}/tests/testprofiler.cpp")
  target_link_libraries(haxorg_cpp_org_tests PUBLIC haxorg GTest::gtest)

  if(${ORG_BUILD_WRAPPERS_C})
    target_link_libraries(haxorg_cpp_org_tests PUBLIC haxorg_c)
  endif()

  target_include_directories(haxorg_cpp_org_tests PUBLIC "${BASE}/thirdparty/immer"
                                                         "${BASE}/thirdparty/lager")

  add_executable(haxorg_cpp_org_specrunner)
  set_common_files(haxorg_cpp_org_specrunner)
  set_target_output(haxorg_cpp_org_specrunner)
  set_target_flags(haxorg_cpp_org_specrunner)
  glob_add_sources2(TARGET haxorg_cpp_org_specrunner LS_REGEX "${BASE}/tests/specrunner/.*"
                    SEARCH_BASE "${BASE}")
  target_link_libraries(haxorg_cpp_org_specrunner PUBLIC haxorg)
endif()
