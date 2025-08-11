haxorg_add_library(hstd)
glob_add_sources2(TARGET hstd LS_REGEX "${BASE}/src/hstd/stdlib/.*" SEARCH_BASE "${BASE}")
glob_add_sources2(TARGET hstd LS_REGEX "${BASE}/src/hstd/system/.*" SEARCH_BASE "${BASE}")
glob_add_sources2(TARGET hstd LS_REGEX "${BASE}/src/hstd/ext/.*" SEARCH_BASE "${BASE}")

find_library(GRAPHVIZ_CGRAPH_LIBRARY cgraph)
find_library(GRAPHVIZ_GVC_LIBRARY gvc)

target_link_libraries(hstd PUBLIC yaml-cpp::yaml-cpp range-v3::range-v3
                                  nlohmann_json::nlohmann_json cctz::cctz)

if(NOT ${ORG_EMCC_BUILD})
  target_link_libraries(hstd PUBLIC ${GRAPHVIZ_CGRAPH_LIBRARY} ${GRAPHVIZ_GVC_LIBRARY} Boost::log
                                    cpptrace::cpptrace)
endif()

if(${ORG_DEPS_USE_ADAPTAGRAMS} AND NOT ${ORG_EMCC_BUILD})
  target_link_libraries(hstd PUBLIC adaptagrams)
endif()

if(${ORG_DEPS_USE_PACKAGED_BOOST})
  target_link_libraries(hstd PUBLIC Boost::boost_describe Boost::boost_preprocessor)
endif()

if(${ORG_USE_PERFETTO} AND NOT ${ORG_EMCC_BUILD})
  target_link_libraries(hstd PUBLIC Perfetto::perfetto)
endif()

if(${ORG_USE_TRACY} AND NOT ${ORG_EMCC_BUILD})
  target_link_libraries(hstd PUBLIC Tracy::TracyClient)
endif()

target_include_directories(hstd PUBLIC "$<BUILD_INTERFACE:${BASE}/thirdparty/immer>"
                                       "$<BUILD_INTERFACE:${BASE}/thirdparty/lager>")

if(${ORG_BUILD_TESTS} AND NOT ${ORG_EMCC_BUILD})
  haxorg_add_executable(tests_hstd)
  glob_add_sources2(TARGET tests_hstd LS_REGEX "${BASE}/tests/hstd/.*" SEARCH_BASE "${BASE}")
  target_link_libraries(tests_hstd PUBLIC GTest::gtest GTest::gmock hstd absl::flags
                                          absl::flags_parse immer)
  add_test(NAME hstd_tests COMMAND tests_hstd)

  haxorg_add_executable(benchmark_hstd)
  glob_add_sources2(TARGET benchmark_hstd LS_REGEX "${BASE}/benchmark/hstd/.*" SEARCH_BASE
                    "${BASE}")
  target_link_libraries(benchmark_hstd PUBLIC benchmark::benchmark hstd immer)
  add_test(NAME hstd_benchmark COMMAND benchmark_hstd)
endif()
