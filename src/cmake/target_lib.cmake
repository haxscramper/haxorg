add_library(haxorg)
set_common_files(haxorg)

glob_add_sources2(haxorg "${BASE}/src/exporters/.*")
glob_add_sources2(haxorg "${BASE}/src/annotators/.*")
glob_add_sources2(haxorg "${BASE}/src/lexbase/.*")
glob_add_sources2(haxorg "${BASE}/src/parse/.*")
glob_add_sources2(haxorg "${BASE}/src/sem/.*")
glob_add_sources2(haxorg "${BASE}/src/tools/.*")
glob_add_sources2(haxorg "${BASE}/src/types/.*")
glob_add_sources2(haxorg "${BASE}/src/base_lexer/.*")

set_target_output(haxorg)
set_target_flags(haxorg)

find_library(GRAPHVIZ_CGRAPH_LIBRARY cgraph)
find_library(GRAPHVIZ_GVC_LIBRARY gvc)
find_package(Protobuf REQUIRED)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS "${BASE}/src/sem/SemOrgProto.proto" "${BASE}/src/sem/SemOrgProtoManual.proto")
list(GET PROTO_HDRS 0 PROTO_HDR_FIRST)
get_filename_component(PROTO_HDR_DIR ${PROTO_HDR_FIRST} DIRECTORY)
message("PROTO_HDR_DIR = '${PROTO_HDR_DIR}' PROTO_HDR_FIRST = '${PROTO_HDR_FIRST}' PROTO_HDRS = '${PROTO_HDRS}'")
target_sources(haxorg PRIVATE "${PROTO_SRCS}")

if (${ORG_USE_PCH})
    target_precompile_headers(haxorg PRIVATE
      <string>
      <format>
      <nlohmann/json.hpp>
      <optional>
      <vector>
      <boost/mp11.hpp>
      <boost/describe.hpp>
      <sem/SemOrg.hpp>
    )
endif()

# Use re-flex static library as a direct dependency here so it would be compiled
# and linked with right sanitizer options (otherwise it triggers lots of false 
# positives)
add_subdirectory("${BASE}/toolchain/RE-flex")

target_link_libraries(haxorg PUBLIC
    ${GRAPHVIZ_CGRAPH_LIBRARY}
    ${GRAPHVIZ_GVC_LIBRARY}
    hstd
    ReflexLibStatic
    range-v3
    # protobuf::protobuf-lite
    protobuf::libprotobuf
    protobuf::libprotoc
    absl::base
    absl::log
)

target_link_directories(haxorg PUBLIC "${BASE}/toolchain/RE-flex/lib")
target_include_directories(haxorg PUBLIC "${BASE}/toolchain/RE-flex/include" "${PROTO_HDR_DIR}")
target_link_options(haxorg PRIVATE "-Wl,--copy-dt-needed-entries")

add_executable(tests_org)
target_link_libraries(tests_org PUBLIC haxorg)
set_common_files(tests_org)
set_target_output(tests_org)
set_target_flags(tests_org)
glob_add_sources2(tests_org "${BASE}/tests/org/.*")


target_sources(tests_org PRIVATE "${BASE}/tests/testprofiler.cpp")
target_link_libraries(tests_org PUBLIC haxorg gtest)

