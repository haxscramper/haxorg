add_library(hstd)
set_common_files(hstd)
glob_add_sources(hstd *.cpp "${BASE}/src/system/.*")
glob_add_sources(hstd *.cpp "${BASE}/src/hstd/.*")
glob_add_sources(hstd *.hpp "${BASE}/src/system/.*")
glob_add_sources(hstd *.hpp "${BASE}/src/hstd/.*")
set_target_output(hstd)
set_target_flags(hstd)

find_library(GRAPHVIZ_CGRAPH_LIBRARY cgraph)
find_library(GRAPHVIZ_GVC_LIBRARY gvc)


target_link_libraries(
    hstd
    PUBLIC
    ${GRAPHVIZ_CGRAPH_LIBRARY}
    ${GRAPHVIZ_GVC_LIBRARY}
    yaml_lib
    absl::base
    absl::log
    perfetto_lib
)

add_executable(tests_hstd)
set_common_files(tests_hstd)
set_target_output(tests_hstd)
set_target_flags(tests_hstd)
glob_add_sources2(tests_hstd "${BASE}/tests/hstd/.*")

target_link_libraries(
    tests_hstd PUBLIC
    gtest
    hstd
)

include_directories("${BASE}/deps/fuzztest")

link_fuzztest(tests_hstd)
