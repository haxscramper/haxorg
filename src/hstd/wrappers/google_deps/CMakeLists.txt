cmake_minimum_required(VERSION 3.10)

project(GoogleDepsWrap)

set(BASE "${CMAKE_SOURCE_DIR}/../../../..")
set(DEPS_DIR "${BASE}/thirdparty")

set(ABSEIL_BINARY_DIR "${CMAKE_BINARY_DIR}/abseil")
add_subdirectory("${DEPS_DIR}/abseil-cpp" "${ABSEIL_BINARY_DIR}")

set(GOOGLETEST_BINARY_DIR "${CMAKE_BINARY_DIR}/googletest")
add_subdirectory("${DEPS_DIR}/googletest" "${GOOGLETEST_BINARY_DIR}")

set(protobuf_INSTALL OFF)
set(protobuf_BUILD_TESTS OFF)
set(utf8_range_ENABLE_TESTS OFF)
set(utf8_range_ENABLE_INSTALL OFF)

set(PROTOBUF_BINARY_DIR "${CMAKE_BINARY_DIR}/protobuf")
add_subdirectory("${DEPS_DIR}/protobuf" "${PROTOBUF_BINARY_DIR}")
