function(add_google_deps BASE)

  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(GOOGLE_DEPS_BUILD_DIR "${BASE}/build/google_deps_debug")
  else()
    set(GOOGLE_DEPS_BUILD_DIR "${BASE}/build/google_deps_release")
  endif()

  set(DEPS_DIR "${BASE}/thirdparty")
  
  add_subdirectory("${DEPS_DIR}/abseil-cpp" "${GOOGLE_DEPS_BUILD_DIR}/abseil")
  add_subdirectory("${DEPS_DIR}/googletest" "${GOOGLE_DEPS_BUILD_DIR}/googletest")
  
  set(protobuf_INSTALL OFF)
  set(protobuf_BUILD_TESTS OFF)
  set(utf8_range_ENABLE_TESTS OFF)
  set(utf8_range_ENABLE_INSTALL OFF)
  add_subdirectory("${DEPS_DIR}/protobuf" "${GOOGLE_DEPS_BUILD_DIR}/protobuf")
endfunction()
