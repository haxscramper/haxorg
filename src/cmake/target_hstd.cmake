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


add_target_property(hstd INCLUDE_DIRECTORIES "/usr/include/enchant-2")

target_link_libraries(
    hstd
    PUBLIC
    ${GRAPHVIZ_CGRAPH_LIBRARY}
    ${GRAPHVIZ_GVC_LIBRARY}
    fmt::fmt
    yaml-cpp::yaml-cpp
    absl::base
    absl::raw_logging_internal
    absl::log_severity
    perfetto
)
