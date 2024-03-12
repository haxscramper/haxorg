add_library(hstd)
add_dependencies(hstd external_google)
set_common_files(hstd)
glob_add_sources2(hstd "${BASE}/src/system/.*")
glob_add_sources2(hstd "${BASE}/src/hstd/.*")
set_target_output(hstd)
set_target_flags(hstd)

find_library(GRAPHVIZ_CGRAPH_LIBRARY cgraph)
find_library(GRAPHVIZ_GVC_LIBRARY gvc)

target_link_libraries(
  hstd
  PUBLIC ${GRAPHVIZ_CGRAPH_LIBRARY}
         ${GRAPHVIZ_GVC_LIBRARY}
         yaml-cpp
         absl_all
         perfetto
         range-v3
         nlohmann_json
         boost_describe)

add_executable(tests_hstd)
add_dependencies(tests_hstd external_google)
set_common_files(tests_hstd)
set_target_output(tests_hstd)
set_target_flags(tests_hstd)
glob_add_sources2(tests_hstd "${BASE}/tests/hstd/.*")

target_link_libraries(tests_hstd PUBLIC gtest hstd absl_all)
