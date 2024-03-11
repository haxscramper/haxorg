function(add_google_deps BASE)

  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(GOOGLE_DEPS_BUILD_DIR "${BASE}/build/google_deps_debug")
  else()
    set(GOOGLE_DEPS_BUILD_DIR "${BASE}/build/google_deps_release")
  endif()

  set(PROTOBUF_BINARY_DIR "${GOOGLE_DEPS_BUILD_DIR}/protobuf")
  set(ABSEIL_BINARY_DIR "${GOOGLE_DEPS_BUILD_DIR}/abseil")
  set(GOOGLETEST_BINARY_DIR "${GOOGLE_DEPS_BUILD_DIR}/gtest")

  set(GOOGLE_DEPS_DIR "${BASE}/thirdparty")

  ExternalProject_Add(
    external_google
    SOURCE_DIR "${BASE}/src/hstd/wrappers/google_deps"
    BINARY_DIR "${GOOGLE_DEPS_BUILD_DIR}"
    CMAKE_ARGS
      -DCMAKE_INSTALL_PREFIX="${GOOGLE_DEPS_BUILD_DIR}"
      -DCMAKE_GENERATOR=Ninja
      # https://stackoverflow.com/questions/54866067/cmake-and-ninja-missing-and-no-known-rule-to-make-it#comment96512321_54866067
      # tl;dr, external project with ninja build (if the parent -- haxorg -- is
      # built with ninja) requires explicit listing of all relevant compilation
      # results, otherwise it fails with `libabsl_flags_parse.a', needed by
      # 'tests_hstd', missing and no known rule to make it`
    BUILD_BYPRODUCTS
      "${ABSEIL_BINARY_DIR}/libabsl_flags.a"
      "${ABSEIL_BINARY_DIR}/libabsl_log.a"
      "${ABSEIL_BINARY_DIR}/libabsl_base.a"
      "${ABSEIL_BINARY_DIR}/libabsl_flags_parse.a"
      "${PROTOBUF_BINARY_DIR}/libprotobuf.a"
      "${PROTOBUF_BINARY_DIR}/libprotoc.a"
      "${GOOGLETEST_BINARY_DIR}/libgtest.a"
      #
  )

  function(use_absl_library LIB_NAME)
    add_library(absl::${LIB_NAME} STATIC IMPORTED)
    set_target_properties(
      absl::${LIB_NAME}
      PROPERTIES IMPORTED_LOCATION "${ABSEIL_BINARY_DIR}/libabsl_${LIB_NAME}.a"
                 INTERFACE_INCLUDE_DIRECTORIES "${GOOGLE_DEPS_DIR}/abseil-cpp")
  endfunction()

  use_absl_library("base")
  use_absl_library("flags")
  use_absl_library("log")
  use_absl_library("flags_parse")

  add_library(protobuf::libprotobuf STATIC IMPORTED)
  set_target_properties(
    protobuf::libprotobuf PROPERTIES IMPORTED_LOCATION
                                     "${PROTOBUF_BINARY_DIR}/libprotobuf.a")

  add_library(protobuf::libprotoc STATIC IMPORTED)
  set_target_properties(
    protobuf::libprotoc PROPERTIES IMPORTED_LOCATION
                                   "${PROTOBUF_BINARY_DIR}/libprotoc.a")

  add_executable(protobuf::protoc IMPORTED GLOBAL)
  set_target_properties(
    protobuf::protoc PROPERTIES IMPORTED_LOCATION
                                "${PROTOBUF_BINARY_DIR}/protoc")

  add_library(gtest STATIC IMPORTED)
  set_target_properties(
    gtest
    PROPERTIES IMPORTED_LOCATION "${GOOGLETEST_BINARY_DIR}/libgtest.a"
               INTERFACE_INCLUDE_DIRECTORIES
               "${GOOGLE_DEPS_DIR}/googletest/googletest/include")

endfunction()
