cmake_minimum_required(VERSION 3.10)

project(GoogleDepsWrap)

set(BASE "${CMAKE_SOURCE_DIR}/../../../..")
set(DEPS_DIR "${BASE}/thirdparty")

add_subdirectory("${DEPS_DIR}/abseil-cpp" "${CMAKE_BINARY_DIR}/abseil")
add_subdirectory("${DEPS_DIR}/googletest" "${CMAKE_BINARY_DIR}/googletest")

set(protobuf_INSTALL OFF)
set(protobuf_BUILD_TESTS OFF)
set(utf8_range_ENABLE_TESTS OFF)
set(utf8_range_ENABLE_INSTALL OFF)
add_subdirectory("${DEPS_DIR}/protobuf" "${CMAKE_BINARY_DIR}/protobuf")

add_library(absl_all STATIC "${CMAKE_SOURCE_DIR}/absl_deps.cpp")
target_link_libraries(absl_all PUBLIC absl::log absl::base absl::flags
                                      absl::flags_parse)

install(
  TARGETS absl_all
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
