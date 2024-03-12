function(add_google_deps BASE)
  set(DEPS_DIR "${BASE}/thirdparty")
  add_subdirectory("${DEPS_DIR}/abseil-cpp" "${CMAKE_BINARY_DIR}/abseil_build")

  set(protobuf_INSTALL OFF)
  set(protobuf_BUILD_TESTS OFF)
  set(utf8_range_ENABLE_TESTS OFF)
  set(utf8_range_ENABLE_INSTALL OFF)

  set(PROTOBUF_BINARY "${CMAKE_BINARY_DIR}/protobuf_build")
  add_subdirectory("${DEPS_DIR}/protobuf" "${PROTOBUF_BINARY}")
endfunction()
