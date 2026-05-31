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

if(${ORG_DEPS_USE_PACKAGED_BOOST})
  target_link_libraries(hstd PUBLIC Boost::boost_describe Boost::boost_preprocessor)
endif()

if(NOT ${ORG_BUILD_EMCC})
  target_link_libraries(hstd PUBLIC Boost::log cpptrace::cpptrace)
endif()

# Tracing
if(${ORG_BUILD_WITH_PERFETTO})
  target_link_libraries(hstd PUBLIC Perfetto::perfetto)
endif()

if(${ORG_BUILD_WITH_TRACY})
  target_link_libraries(hstd PUBLIC Tracy::TracyClient)
endif()

if(${ORG_BUILD_WITH_KIWI})
  target_link_libraries(hstd PUBLIC kiwi::kiwi)
endif()

# Graph processing and visualization
if(${ORG_BUILD_WITH_GRAPH_VISUAL})
  if(${ORG_BUILD_WITH_ELK})
    add_subdirectory("${BASE}/src/hstd/ext/graph/jni_elk")
    target_link_libraries(hstd PUBLIC jni_elk_lib)
  endif()

  if(${ORG_BUILD_WITH_CGRAPH})
    find_package(graphviz REQUIRED)
    target_link_libraries(hstd PUBLIC graphviz::cgraph graphviz::gvc)
  endif()

  if(${ORG_BUILD_WITH_ADAPTAGRAMS})
    target_link_libraries(hstd PUBLIC adaptagrams)
  endif()

  haxorg_add_protobuf(
    TARGET
    hstd
    UNIQUE_TARGET
    hstd_proto_base_graph
    IMPORT_DIRS
    "${BASE}"
    PROTO_SOURCES
    "${BASE}/src/hstd/ext/graph/base/graph_base.proto"
    "${BASE}/src/hstd/ext/graph/visual/graph_visual.proto"
    "${BASE}/src/hstd/ext/geometry/hstd_geometry.proto"
    "${BASE}/src/hstd/ext/geometry/hstd_visual.proto")

  haxorg_add_protobuf(
    TARGET
    hstd
    UNIQUE_TARGET
    hstd_proto_graphviz_graph
    IMPORT_DIRS
    "${BASE}"
    PROTO_SOURCES
    "${BASE}/src/hstd/ext/graph/visual/graph_graphviz.proto")

endif()

target_include_directories(hstd PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
                                       $<INSTALL_INTERFACE:src>)
target_include_directories(hstd PUBLIC "$<BUILD_INTERFACE:${BASE}/thirdparty/immer>"
                                       "$<BUILD_INTERFACE:${BASE}/thirdparty/lager>")

if(${ORG_BUILD_TESTS})
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
