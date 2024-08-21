add_library(haxorg)
set_common_files(haxorg)

glob_add_sources2(haxorg "${BASE}/src/exporters/.*" "${BASE}")
glob_add_sources2(haxorg "${BASE}/src/annotators/.*" "${BASE}")
glob_add_sources2(haxorg "${BASE}/src/lexbase/.*" "${BASE}")
glob_add_sources2(haxorg "${BASE}/src/parse/.*" "${BASE}")
glob_add_sources2(haxorg "${BASE}/src/sem/.*" "${BASE}")
glob_add_sources2(haxorg "${BASE}/src/tools/.*" "${BASE}")
glob_add_sources2(haxorg "${BASE}/src/types/.*" "${BASE}")
glob_add_sources2(haxorg "${BASE}/src/base_lexer/.*" "${BASE}")
glob_add_sources2(haxorg "${BASE}/src/test/.*" "${BASE}")

set_target_output(haxorg)
set_target_flags(haxorg)

find_library(GRAPHVIZ_CGRAPH_LIBRARY cgraph)
find_library(GRAPHVIZ_GVC_LIBRARY gvc)

protobuf_generate(
    LANGUAGE cpp
    OUT_VAR ORG_PROTO_GENERATED_FILES
    IMPORT_DIRS "${BASE}/src/sem"
    PROTOS "${BASE}/src/sem/SemOrgProto.proto" "${BASE}/src/sem/SemOrgProtoManual.proto"
    PROTOC_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}"
)

target_sources(haxorg PRIVATE "${ORG_PROTO_GENERATED_FILES}")

# Use re-flex static library as a direct dependency here so it would be compiled
# and linked with right sanitizer options (otherwise it triggers lots of false 
# positives)
# add_subdirectory("${BASE}/thirdparty/RE-flex")

target_link_libraries(haxorg PUBLIC
    ${GRAPHVIZ_CGRAPH_LIBRARY}
    ${GRAPHVIZ_GVC_LIBRARY}
    hstd
    Reflex::ReflexLibStatic
    range-v3
    # protobuf::protobuf-lite
    protobuf::libprotobuf
    protobuf::libprotoc
    absl::base
    absl::log
    perfetto
    nlohmann_json
)

# target_link_directories(haxorg PUBLIC "${BASE}/toolchain/RE-flex/lib")
target_include_directories(haxorg PUBLIC "${CMAKE_CURRENT_BINARY_DIR}")
# target_link_options(haxorg PRIVATE "-Wl,--copy-dt-needed-entries")

add_executable(tests_org)
target_link_libraries(tests_org PUBLIC haxorg)
set_common_files(tests_org)
set_target_output(tests_org)
set_target_flags(tests_org)
glob_add_sources2(tests_org "${BASE}/tests/org/.*" "${BASE}")

add_custom_command(
    TARGET tests_org
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E create_symlink "${CMAKE_BINARY_DIR}"
            "${CMAKE_SOURCE_DIR}/build/haxorg")

target_sources(tests_org PRIVATE "${BASE}/tests/testprofiler.cpp")
target_link_libraries(tests_org PUBLIC haxorg gtest)

target_include_directories(tests_org PUBLIC
    "${BASE}/thirdparty/immer"
    "${BASE}/thirdparty/lager"
)



add_executable(specrunner_org)
set_common_files(specrunner_org)
set_target_output(specrunner_org)
set_target_flags(specrunner_org)
glob_add_sources2(specrunner_org "${BASE}/tests/specrunner/.*" "${BASE}")
target_link_libraries(specrunner_org PUBLIC haxorg)
