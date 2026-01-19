if(NOT ${ORG_EMCC_BUILD})

  set(COLA_DIR "${DEPS_DIR}/adaptagrams/cola")
  include(CMakeParseArguments)

  add_library(adaptagrams)
  haxorg_target_setup_v2(TARGET adaptagrams FORCE_NO_ASAN ON)
  target_link_libraries(
    adaptagrams
    PUBLIC Adaptagrams::cola
           Adaptagrams::avoid
           Adaptagrams::dialect
           Adaptagrams::topology
           Adaptagrams::vpsc
           hstd
           absl::log
           absl::base)

  target_include_directories(adaptagrams PUBLIC $<BUILD_INTERFACE:${COLA_DIR}>
                                                $<INSTALL_INTERFACE:include>)

  install(
    DIRECTORY ${COLA_DIR}/
    DESTINATION include
    FILES_MATCHING
    PATTERN "*.h")

  glob_add_sources2(
    TARGET
    "adaptagrams"
    LS_REGEX
    "${CMAKE_CURRENT_SOURCE_DIR}/.*"
    SEARCH_BASE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    RECURSE
    OFF)

  pybind11_add_module(py_adaptagrams "${BASE}/src/py_libs/py_adaptagrams/adaptagrams_py_wrap.cpp"
                      "${BASE}/src/py_libs/py_adaptagrams/adaptagrams_ir_refl_target.cpp")

  set_target_properties(py_adaptagrams PROPERTIES OUTPUT_NAME "py_adaptagrams" SUFFIX ".so")

  haxorg_target_setup_v2(TARGET py_adaptagrams FORCE_NO_ASAN ON)
  target_link_libraries(py_adaptagrams PRIVATE hstd ${Python_LIBRARIES} haxorg adaptagrams)
  if(${ORG_USE_SANITIZER})
    target_link_libraries(py_adaptagrams PRIVATE ubsan)
  endif()

  if(${ORG_USE_PERFETTO})
    target_link_libraries(py_adaptagrams PRIVATE Perfetto::perfetto)
  endif()

  if(${ORG_USE_TRACY})
    target_link_libraries(py_adaptagrams PUBLIC Tracy::TracyClient)
  endif()
endif()
