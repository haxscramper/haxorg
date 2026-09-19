include(functions_setup)
include(functions_aux)

if(${ORG_BUILD_WITH_QT})
  find_package(
    Qt6
    COMPONENTS
    REQUIRED Core)

  qt_add_library(hstd_cpp_lib STATIC)
  set_common_files(hstd_cpp_lib)
  set_target_output(hstd_cpp_lib)
  set_target_flags(hstd_cpp_lib)

  target_link_libraries(hstd_cpp_lib PUBLIC Qt6::Core)
  target_compile_definitions(hstd_cpp_lib PUBLIC ORG_BUILD_WITH_QT=1)

  set_target_properties(
    hstd_cpp_lib
    PROPERTIES AUTOMOC ON
               AUTOUIC ON
               AUTORCC ON)
else()
  haxorg_add_library(hstd_cpp_lib)

endif()

haxorg_glob_add_sources2(TARGET hstd_cpp_lib LS_REGEX "${BASE}/src/hstd/stdlib/.*" SEARCH_BASE
                         "${BASE}")
haxorg_glob_add_sources2(TARGET hstd_cpp_lib LS_REGEX "${BASE}/src/hstd/system/.*" SEARCH_BASE
                         "${BASE}")
haxorg_glob_add_sources2(TARGET hstd_cpp_lib LS_REGEX "${BASE}/src/hstd/ext/.*" SEARCH_BASE
                         "${BASE}")

target_link_libraries(
  hstd_cpp_lib
  PUBLIC yaml-cpp::yaml-cpp
         range-v3::range-v3
         nlohmann_json::nlohmann_json
         cctz::cctz
         fmt::fmt
         Boost::boost_describe
         Boost::boost_preprocessor
         Boost::headers)

if(NOT ${ORG_BUILD_EMCC})
  target_link_libraries(hstd_cpp_lib PUBLIC Boost::log cpptrace::cpptrace)
endif()

# Tracing
if(${ORG_BUILD_WITH_PERFETTO})
  target_link_libraries(hstd_cpp_lib PUBLIC Perfetto::perfetto)
endif()

if(${ORG_BUILD_WITH_TRACY})
  target_link_libraries(hstd_cpp_lib PUBLIC Tracy::TracyClient)
endif()

if(${ORG_BUILD_WITH_PROTOBUF})
  haxorg_add_protobuf(
    TARGET
    hstd_cpp_lib
    UNIQUE_TARGET
    hstd_proto_base_graph
    IMPORT_DIRS
    "${BASE}"
    PROTO_SOURCES
    "${BASE}/src/hstd/ext/graph/base/graph_base.proto"
    "${BASE}/src/hstd/ext/graph/visual/graph_visual.proto"
    "${BASE}/src/hstd/ext/geometry/hstd_geometry.proto"
    "${BASE}/src/hstd/ext/geometry/hstd_geometry_test_ir.proto"
    "${BASE}/src/hstd/ext/graph/visual/graph_diagram_validate.proto"
    "${BASE}/src/hstd/ext/geometry/hstd_visual.proto")

  haxorg_add_protobuf(
    TARGET
    hstd
    UNIQUE_TARGET
    hstd_proto_error_write
    IMPORT_DIRS
    "${BASE}"
    PROTO_SOURCES
    "${BASE}/src/hstd/ext/error_write.proto")
endif()

target_include_directories(hstd_cpp_lib PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
                                               $<INSTALL_INTERFACE:src>)
target_include_directories(hstd_cpp_lib PUBLIC "$<BUILD_INTERFACE:${BASE}/thirdparty/immer>"
                                               "$<BUILD_INTERFACE:${BASE}/thirdparty/lager>")

if(${ORG_BUILD_TESTS})
  haxorg_add_executable(hstd_cpp_tests)

  if(${ORG_BUILD_WITH_QT})
    target_compile_definitions(hstd_cpp_tests PUBLIC ORG_BUILD_WITH_QT=1)
  endif()

  haxorg_glob_add_sources2(TARGET hstd_cpp_tests LS_REGEX "${BASE}/tests/hstd/.*" SEARCH_BASE
                           "${BASE}")
  target_sources(hstd_cpp_tests PRIVATE "${BASE}/tests/common.cpp")
  target_link_libraries(hstd_cpp_tests PUBLIC GTest::gtest GTest::gmock hstd absl::flags
                                              absl::flags_parse immer::immer)

  add_test(NAME hstd_tests COMMAND hstd_cpp_tests)

  haxorg_add_executable(hstd_cpp_benchmark)
  haxorg_glob_add_sources2(TARGET hstd_cpp_benchmark LS_REGEX "${BASE}/benchmark/hstd/.*"
                           SEARCH_BASE "${BASE}")
  target_link_libraries(hstd_cpp_benchmark PUBLIC benchmark::benchmark hstd immer::immer)
  add_test(NAME hstd_benchmark COMMAND hstd_cpp_benchmark)
endif()
