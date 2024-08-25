add_library(hstd)
set_common_files(hstd)
glob_add_sources2(TARGET hstd LS_REGEX "${BASE}/src/hstd/stdlib/.*" SEARCH_BASE "${BASE}")
glob_add_sources2(TARGET hstd LS_REGEX "${BASE}/src/hstd/system/.*" SEARCH_BASE "${BASE}")
glob_add_sources2(TARGET hstd LS_REGEX "${BASE}/src/hstd/wrappers/hstd_extra.*" SEARCH_BASE
                  "${BASE}")
set_target_output(hstd)
set_target_flags(hstd)

find_library(GRAPHVIZ_CGRAPH_LIBRARY cgraph)
find_library(GRAPHVIZ_GVC_LIBRARY gvc)

target_link_libraries(
  hstd
  PUBLIC ${GRAPHVIZ_CGRAPH_LIBRARY}
         ${GRAPHVIZ_GVC_LIBRARY}
         yaml-cpp
         absl::base
         absl::log
         absl::flags
         range-v3::range-v3
         nlohmann_json::nlohmann_json
         Boost::boost_describe)

if(${ORG_USE_PERFETTO})
  target_link_libraries(hstd PUBLIC Perfetto::perfetto)
endif()

add_executable(tests_hstd)
set_common_files(tests_hstd)
set_target_output(tests_hstd)
set_target_flags(tests_hstd)
glob_add_sources2(TARGET tests_hstd LS_REGEX "${BASE}/tests/hstd/.*" SEARCH_BASE "${BASE}")

target_link_libraries(tests_hstd PUBLIC GTest::gtest hstd absl::flags absl::flags_parse adaptagrams)
