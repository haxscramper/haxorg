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
  set("${ARG_OUT}" "${TMP}" PARENT_SCOPE)
endfunction()

function(glob_add_sources_v2)
  cmake_parse_arguments(ARG "" "RECURSE;TARGET;EXT_GLOB;LS_REGEX" "" "${ARGN}")
  list_filter_files_v2(OUT SRC_FILES GLOB ${ARG_EXT_GLOB} REGEX "${ARG_LS_REGEX}" RECURSE ${ARG_RECURSE})
  target_sources("${ARG_TARGET}" PRIVATE "${SRC_FILES}")
endfunction()

function(glob_add_sources_2_v2)
  set(ARG_EXTENSIONS "hpp;cpp")
  cmake_parse_arguments(ARG "" "RECURSE;TARGET;LS_REGEX;SEARCH_BASE" "EXTENSIONS" "${ARGN}")
  if(ARG_RECURSE)
      set(EXT_GLOB_BASE "${ARG_SEARCH_BASE}/**")
  else()
      set(EXT_GLOB_BASE "${ARG_SEARCH_BASE}")
  endif()

  foreach(EXT IN LISTS ARG_EXTENSIONS)
      glob_add_sources_v2(TARGET "${ARG_TARGET}" EXT_GLOB "${EXT_GLOB_BASE}/*.${EXT}" LS_REGEX "${ARG_LS_REGEX}" RECURSE ${ARG_RECURSE})
  endforeach()
endfunction()


function(add_cola_library cola_name)
    set(cola_fullname "cola_${cola_name}")
    add_library("${cola_fullname}")
    glob_add_sources_2_v2(
        TARGET "${cola_fullname}"
        LS_REGEX "${COLA_DIR}/lib${cola_name}/.*"
        SEARCH_BASE "${COLA_DIR}/lib${cola_name}"
        EXTENSIONS "hpp;cpp;h"
        RECURSE OFF
    )

    target_include_directories(${cola_fullname} PUBLIC "${COLA_DIR}")
endfunction()


configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cola_autoconf_config.h" "${COLA_DIR}/libcola/config.h")

add_cola_library(avoid)
add_cola_library(cola)
add_cola_library(dialect)
add_cola_library(topology)
add_cola_library(vpsc)

find_package(PkgConfig)
pkg_check_modules(CAIROMM REQUIRED cairomm-1.0)

target_link_libraries(cola_cola PUBLIC ${CAIROMM_LIBRARIES})
target_include_directories(cola_cola PUBLIC ${CAIROMM_INCLUDE_DIRS})
