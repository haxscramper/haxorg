set(COLA_DIR "${DEPS_DIR}/adaptagrams/cola")
include(CMakeParseArguments)

function(list_filter_files_v2)
  cmake_parse_arguments(ARG "" "RECURSE;OUT;GLOB;REGEX" "" "${ARGN}")
  if(ARG_RECURSE)
    set(GLOB_COMMAND "GLOB_RECURSE")
  else()
    set(GLOB_COMMAND "GLOB")
  endif()
  file(${GLOB_COMMAND} TMP ${ARG_GLOB})
  list(FILTER TMP INCLUDE REGEX "${ARG_REGEX}")
  set("${ARG_OUT}"
      "${TMP}"
      PARENT_SCOPE)
endfunction()

function(glob_add_sources_v2)
  cmake_parse_arguments(ARG "" "RECURSE;TARGET;EXT_GLOB;LS_REGEX" "" "${ARGN}")
  list_filter_files_v2(
    OUT
    SRC_FILES
    GLOB
    ${ARG_EXT_GLOB}
    REGEX
    "${ARG_LS_REGEX}"
    RECURSE
    ${ARG_RECURSE})
  # message(STATUS "TARGET = ${ARG_TARGET} RECURSE = ${ARG_RECURSE} EXT_GLOB = ${ARG_EXT_GLOB}
  # LS_REGEX = ${ARG_LS_REGEX}")
  target_sources("${ARG_TARGET}" PRIVATE "${SRC_FILES}")
endfunction()

function(glob_add_sources_2_v2)
  cmake_parse_arguments(ARG "" "RECURSE;TARGET;LS_REGEX;SEARCH_BASE" "EXTENSIONS" "${ARGN}")
  if(NOT ARG_EXTENSIONS)
    set(ARG_EXTENSIONS "hpp;cpp")
  endif()

  if(ARG_RECURSE)
    set(EXT_GLOB_BASE "${ARG_SEARCH_BASE}/**")
  else()
    set(EXT_GLOB_BASE "${ARG_SEARCH_BASE}")
  endif()

  # message(STATUS "ARG_EXTENSIONS = ${ARG_EXTENSIONS} TARGET = ${ARG_TARGET}")
  foreach(EXT IN LISTS ARG_EXTENSIONS)
    glob_add_sources_v2(
      TARGET
      "${ARG_TARGET}"
      EXT_GLOB
      "${EXT_GLOB_BASE}/*.${EXT}"
      LS_REGEX
      "${ARG_LS_REGEX}"
      RECURSE
      ${ARG_RECURSE})
  endforeach()
endfunction()

function(haxorg_target_setup_v2)
  cmake_parse_arguments(ARG "" "TARGET;FORCE_NO_ASAN" "" "${ARGN}")
  set_common_files("${ARG_TARGET}")
  set_target_output("${ARG_TARGET}")
  set_target_flags_impl(TARGET "${ARG_TARGET}" FORCE_NO_ASAN "${ARG_FORCE_NO_ASAN}")
endfunction()

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

target_include_directories(adaptagrams PUBLIC "${COLA_DIR}")

glob_add_sources_2_v2(
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
target_link_libraries(py_adaptagrams PRIVATE hstd ${PYTHON_LIBRARIES} ubsan haxorg
                                             Perfetto::perfetto adaptagrams)

set_target_properties(
  py_adaptagrams
  PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
             LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
             ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
