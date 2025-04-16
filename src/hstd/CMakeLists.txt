add_library(hstd)
set_common_files(hstd)
glob_add_sources2(TARGET hstd LS_REGEX "${BASE}/src/hstd/stdlib/.*" SEARCH_BASE "${BASE}")
glob_add_sources2(TARGET hstd LS_REGEX "${BASE}/src/hstd/system/.*" SEARCH_BASE "${BASE}")
glob_add_sources2(TARGET hstd LS_REGEX "${BASE}/src/hstd/ext/.*" SEARCH_BASE "${BASE}")
set_target_output(hstd)
set_target_flags(hstd)

find_library(GRAPHVIZ_CGRAPH_LIBRARY cgraph)
find_library(GRAPHVIZ_GVC_LIBRARY gvc)

target_link_libraries(hstd PUBLIC yaml-cpp range-v3::range-v3 nlohmann_json::nlohmann_json)

if(NOT ${ORG_EMCC_BUILD})
  target_link_libraries(
    hstd
    PUBLIC ${GRAPHVIZ_CGRAPH_LIBRARY}
           ${GRAPHVIZ_GVC_LIBRARY}
           Boost::log
           absl::base
           absl::log
           absl::flags
           cpptrace::cpptrace)
endif()

if(${ORG_DEPS_USE_PACKAGED_BOOST})
  target_link_libraries(hstd PUBLIC Boost::boost_describe)
endif()

if(${ORG_USE_PERFETTO})
  target_link_libraries(hstd PUBLIC Perfetto::perfetto)
endif()

target_include_directories(hstd PUBLIC "$<BUILD_INTERFACE:${BASE}/thirdparty/immer>"
                                       "$<BUILD_INTERFACE:${BASE}/thirdparty/lager>")

if(${ORG_BUILD_TESTS} AND NOT ${ORG_EMCC_BUILD})
  add_executable(tests_hstd)
  set_common_files(tests_hstd)
  set_target_output(tests_hstd)
  set_target_flags(tests_hstd)
  glob_add_sources2(TARGET tests_hstd LS_REGEX "${BASE}/tests/hstd/.*" SEARCH_BASE "${BASE}")
  target_link_libraries(tests_hstd PUBLIC GTest::gtest hstd absl::flags absl::flags_parse)
  if(${ORG_DEPS_USE_ADAPTAGRAMS})
    target_link_libraries(tests_hstd PUBLIC adaptagrams)
  endif()
endif()
