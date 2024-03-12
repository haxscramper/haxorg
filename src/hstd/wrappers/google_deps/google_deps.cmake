function(add_google_deps BASE)

  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(GOOGLE_DEPS_BUILD_DIR "${BASE}/build/google_deps_debug")
  else()
    set(GOOGLE_DEPS_BUILD_DIR "${BASE}/build/google_deps_release")
  endif()

  set(PROTOBUF_BINARY_DIR "${GOOGLE_DEPS_BUILD_DIR}/protobuf")
  set(ABSEIL_BINARY_DIR "${GOOGLE_DEPS_BUILD_DIR}/abseil")
  message(STATUS "GOOGLE_DEPS_BUILD_DIR = ${GOOGLE_DEPS_BUILD_DIR}")

  set(GOOGLE_DEPS_DIR "${BASE}/thirdparty")

  ExternalProject_Add(
    external_google
    SOURCE_DIR "${BASE}/src/hstd/wrappers/google_deps"
    BINARY_DIR "${GOOGLE_DEPS_BUILD_DIR}"
    CMAKE_ARGS
      # NOTE: The quotes cannot be used in this parameter, otherwise it genrates
      # invalid cmake install prefix in the `cmake_install.cmake` file for
      # abseil.
      -DCMAKE_INSTALL_PREFIX=${GOOGLE_DEPS_BUILD_DIR}
      -DCMAKE_GENERATOR=Ninja
      # By default top-level installation targets from absl are not compiled
      # into final binaries
      -DABSL_ENABLE_INSTALL=ON
      -DABSL_BUILD_TESTING=OFF
      # https://stackoverflow.com/questions/54866067/cmake-and-ninja-missing-and-no-known-rule-to-make-it#comment96512321_54866067
      # tl;dr, external project with ninja build (if the parent -- haxorg -- is
      # built with ninja) requires explicit listing of all relevant compilation
      # results, otherwise it fails with `libabsl_flags_parse.a', needed by
      # 'tests_hstd', missing and no known rule to make it`
    BUILD_BYPRODUCTS
      "${GOOGLE_DEPS_BUILD_DIR}/lib/libabsl_all.a"
      "${PROTOBUF_BINARY_DIR}/libprotobuf.a"
      "${PROTOBUF_BINARY_DIR}/libprotoc.a"
      "${GOOGLE_DEPS_BUILD_DIR}/lib/libgtest.a"
      #
  )

  add_library(absl_all STATIC IMPORTED)
  set_target_properties(
    absl_all
    PROPERTIES IMPORTED_LOCATION "${GOOGLE_DEPS_BUILD_DIR}/lib/libabsl_all.a"
               INTERFACE_INCLUDE_DIRECTORIES "${GOOGLE_DEPS_DIR}/abseil-cpp")

  add_library(protobuf::libprotobuf STATIC IMPORTED)
  set_target_properties(
    protobuf::libprotobuf
    PROPERTIES IMPORTED_LOCATION "${PROTOBUF_BINARY_DIR}/libprotobuf.a"
               INTERFACE_INCLUDE_DIRECTORIES "${GOOGLE_DEPS_DIR}/protobuf/src")

  add_library(protobuf::libprotoc STATIC IMPORTED)
  set_target_properties(
    protobuf::libprotoc
    PROPERTIES IMPORTED_LOCATION "${PROTOBUF_BINARY_DIR}/libprotoc.a"
               INTERFACE_INCLUDE_DIRECTORIES "${GOOGLE_DEPS_DIR}/protobuf/src")

  add_executable(protobuf::protoc IMPORTED GLOBAL)
  set_target_properties(
    protobuf::protoc PROPERTIES IMPORTED_LOCATION
                                "${PROTOBUF_BINARY_DIR}/protoc")

  add_library(gtest STATIC IMPORTED)
  set_target_properties(
    gtest
    PROPERTIES IMPORTED_LOCATION "${GOOGLE_DEPS_BUILD_DIR}/lib/libgtest.a"
               INTERFACE_INCLUDE_DIRECTORIES
               "${GOOGLE_DEPS_DIR}/googletest/googletest/include")

endfunction()
