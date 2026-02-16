if(${ORG_BUILD_WITH_QT})
  find_package(
    Qt6
    COMPONENTS
    REQUIRED Core)

  qt_add_library(hstd STATIC)
  set_common_files(hstd)
  set_target_output(hstd)
  set_target_flags(hstd)

  target_link_libraries(hstd PUBLIC Qt6::Core)
  target_compile_definitions(hstd PUBLIC ORG_BUILD_WITH_QT=1)

  set_target_properties(
    hstd
    PROPERTIES AUTOMOC ON
               AUTOUIC ON
               AUTORCC ON)
else()
  haxorg_add_library(hstd)

endif()

glob_add_sources2(TARGET hstd LS_REGEX "${BASE}/src/hstd/stdlib/.*" SEARCH_BASE "${BASE}")
glob_add_sources2(TARGET hstd LS_REGEX "${BASE}/src/hstd/system/.*" SEARCH_BASE "${BASE}")
glob_add_sources2(TARGET hstd LS_REGEX "${BASE}/src/hstd/ext/.*" SEARCH_BASE "${BASE}")

target_link_libraries(hstd PUBLIC yaml-cpp::yaml-cpp range-v3::range-v3
                                  nlohmann_json::nlohmann_json cctz::cctz)

if(NOT ${ORG_BUILD_EMCC})
  target_link_libraries(hstd PUBLIC Boost::log cpptrace::cpptrace)

  if(${ORG_BUILD_WITH_CGRAPH})
    find_library(GRAPHVIZ_CGRAPH_LIBRARY cgraph)
    find_library(GRAPHVIZ_GVC_LIBRARY gvc)
    target_link_libraries(hstd PUBLIC ${GRAPHVIZ_CGRAPH_LIBRARY} ${GRAPHVIZ_GVC_LIBRARY})
  endif()
endif()

if(${ORG_BUILD_WITH_ADAPTAGRAMS} AND NOT ${ORG_BUILD_EMCC})
  target_link_libraries(hstd PUBLIC adaptagrams)
endif()

if(${ORG_DEPS_USE_PACKAGED_BOOST})
  target_link_libraries(hstd PUBLIC Boost::boost_describe Boost::boost_preprocessor)
endif()

if(${ORG_BUILD_WITH_PERFETTO} AND NOT ${ORG_BUILD_EMCC})
  target_link_libraries(hstd PUBLIC Perfetto::perfetto)
endif()

if(${ORG_BUILD_WITH_TRACY} AND NOT ${ORG_BUILD_EMCC})
  target_link_libraries(hstd PUBLIC Tracy::TracyClient)
endif()

target_include_directories(hstd PUBLIC "$<BUILD_INTERFACE:${BASE}/thirdparty/immer>"
                                       "$<BUILD_INTERFACE:${BASE}/thirdparty/lager>")

if(${ORG_BUILD_TESTS} AND NOT ${ORG_BUILD_EMCC})
  haxorg_add_executable(tests_hstd)

  if(${ORG_BUILD_WITH_QT})
    target_compile_definitions(tests_hstd PUBLIC ORG_BUILD_WITH_QT=1)
  endif()

  glob_add_sources2(TARGET tests_hstd LS_REGEX "${BASE}/tests/hstd/.*" SEARCH_BASE "${BASE}")
  target_sources(tests_hstd PRIVATE "${BASE}/tests/common.cpp")
  target_link_libraries(tests_hstd PUBLIC GTest::gtest GTest::gmock hstd absl::flags
                                          absl::flags_parse immer::immer)

  add_test(NAME hstd_tests COMMAND tests_hstd)

  haxorg_add_executable(benchmark_hstd)
  glob_add_sources2(TARGET benchmark_hstd LS_REGEX "${BASE}/benchmark/hstd/.*" SEARCH_BASE
                    "${BASE}")
  target_link_libraries(benchmark_hstd PUBLIC benchmark::benchmark hstd immer::immer)
  add_test(NAME hstd_benchmark COMMAND benchmark_hstd)
endif()
