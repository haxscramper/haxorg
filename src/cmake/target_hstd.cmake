add_library(hstd)
set_common_files(hstd)
glob_add_sources2(hstd "${BASE}/src/system/.*")
glob_add_sources2(hstd "${BASE}/src/hstd/.*")
set_target_output(hstd)
set_target_flags(hstd)

find_library(GRAPHVIZ_CGRAPH_LIBRARY cgraph)
find_library(GRAPHVIZ_GVC_LIBRARY gvc)


target_link_libraries(
    hstd
    PUBLIC
    ${GRAPHVIZ_CGRAPH_LIBRARY}
    ${GRAPHVIZ_GVC_LIBRARY}
    yaml-cpp
    absl::base
    absl::log
    absl::flags
    perfetto
    range-v3
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
    absl::flags
    absl::flags_parse
)
