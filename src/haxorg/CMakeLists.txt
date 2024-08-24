add_library(haxorg)
set_common_files(haxorg)

glob_add_sources2(TARGET haxorg LS_REGEX "${BASE}/src/haxorg/exporters/.*" SEARCH_BASE "${BASE}")
glob_add_sources2(TARGET haxorg LS_REGEX "${BASE}/src/haxorg/annotators/.*" SEARCH_BASE "${BASE}")
glob_add_sources2(TARGET haxorg LS_REGEX "${BASE}/src/haxorg/lexbase/.*" SEARCH_BASE "${BASE}")
glob_add_sources2(TARGET haxorg LS_REGEX "${BASE}/src/haxorg/parse/.*" SEARCH_BASE "${BASE}")
glob_add_sources2(TARGET haxorg LS_REGEX "${BASE}/src/haxorg/sem/.*" SEARCH_BASE "${BASE}")
glob_add_sources2(TARGET haxorg LS_REGEX "${BASE}/src/haxorg/tools/.*" SEARCH_BASE "${BASE}")
glob_add_sources2(TARGET haxorg LS_REGEX "${BASE}/src/haxorg/types/.*" SEARCH_BASE "${BASE}")
glob_add_sources2(TARGET haxorg LS_REGEX "${BASE}/src/haxorg/base_lexer/.*" SEARCH_BASE "${BASE}")
glob_add_sources2(TARGET haxorg LS_REGEX "${BASE}/src/haxorg/test/.*" SEARCH_BASE "${BASE}")

set_target_output(haxorg)
set_target_flags(haxorg)

find_library(GRAPHVIZ_CGRAPH_LIBRARY cgraph)
find_library(GRAPHVIZ_GVC_LIBRARY gvc)

protobuf_generate(
  LANGUAGE
  cpp
  OUT_VAR
  ORG_PROTO_GENERATED_FILES
  IMPORT_DIRS
  "${BASE}/src/haxorg/sem"
  PROTOS
  "${BASE}/src/haxorg/sem/SemOrgProto.proto"
  "${BASE}/src/haxorg/sem/SemOrgProtoManual.proto"
  PROTOC_OUT_DIR
  "${CMAKE_CURRENT_BINARY_DIR}")

target_sources(haxorg PRIVATE "${ORG_PROTO_GENERATED_FILES}")

target_link_libraries(
  haxorg
  PUBLIC ${GRAPHVIZ_CGRAPH_LIBRARY}
         ${GRAPHVIZ_GVC_LIBRARY}
         hstd
         Reflex::ReflexLibStatic
         range-v3::range-v3
         protobuf::libprotobuf
         protobuf::libprotoc
         absl::base
         absl::log
         nlohmann_json::nlohmann_json)

if(${ORG_USE_PERFETTO})
  target_link_libraries(haxorg PUBLIC Perfetto::perfetto)
endif()

target_include_directories(haxorg PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
                                         $<INSTALL_INTERFACE:include>)

add_executable(tests_org)
target_link_libraries(tests_org PUBLIC haxorg)
set_common_files(tests_org)
set_target_output(tests_org)
set_target_flags(tests_org)
glob_add_sources2(TARGET tests_org LS_REGEX "${BASE}/tests/org/.*" SEARCH_BASE "${BASE}")

add_custom_command(
  TARGET tests_org
  POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E create_symlink "${CMAKE_BINARY_DIR}"
          "${CMAKE_SOURCE_DIR}/build/haxorg")

target_sources(tests_org PRIVATE "${BASE}/tests/testprofiler.cpp")
target_link_libraries(tests_org PUBLIC haxorg GTest::gtest)

target_include_directories(tests_org PUBLIC "${BASE}/thirdparty/immer" "${BASE}/thirdparty/lager")

add_executable(specrunner_org)
set_common_files(specrunner_org)
set_target_output(specrunner_org)
set_target_flags(specrunner_org)
glob_add_sources2(TARGET specrunner_org LS_REGEX "${BASE}/tests/specrunner/.*" SEARCH_BASE
                  "${BASE}")
target_link_libraries(specrunner_org PUBLIC haxorg)
