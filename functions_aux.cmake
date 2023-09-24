if(NOT WIN32)
  string(ASCII 27 Esc)
  set(cColorReset "${Esc}[m")
  set(cColorBold "${Esc}[1m")
  set(c0 "${Esc}[m")
  set(cRed "${Esc}[31m")
  set(cGreen "${Esc}[32m")
  set(cYellow "${Esc}[33m")
  set(cBlue "${Esc}[34m")
  set(cMagenta "${Esc}[35m")
  set(cCyan "${Esc}[36m")
  set(cWhite "${Esc}[37m")
  set(cBoldRed "${Esc}[1;31m")
  set(cBoldGreen "${Esc}[1;32m")
  set(cBoldYellow "${Esc}[1;33m")
  set(cBoldBlue "${Esc}[1;34m")
  set(cBoldMagenta "${Esc}[1;35m")
  set(cBoldCyan "${Esc}[1;36m")
  set(cBoldWhite "${Esc}[1;37m")
endif()

function(set_target_output TARGET)
    # Set target output suffix and location relative to the cmake sorce
    # directory
    get_target_property(target_type ${TARGET} TYPE)
    message(INFO "Outputting ${TARGET} to ${BASE}/(bin|lib) (type is ${target_type}")

    add_custom_command(TARGET ${TARGET} POST_BUILD
                       COMMAND "${CMAKE_COMMAND}" -E create_symlink
                               "${CMAKE_BINARY_DIR}" "${CMAKE_SOURCE_DIR}/build/haxorg")

endfunction()

function(pad_string output str padchar length operation)
  string(LENGTH "${str}" _strlen)
  math(EXPR _strlen "${length} - ${_strlen}")

  if(_strlen GREATER 0)
    if(${CMAKE_VERSION} VERSION_LESS "3.14")
      unset(_pad)
      foreach(_i RANGE 1 ${_strlen}) # inclusive
        string(${operation} _pad ${padchar})
      endforeach()
    else()
      string(REPEAT ${padchar} ${_strlen} _pad)
    endif()
    string(${operation} str ${_pad})
  endif()

  set(${output}
      "${str}"
      PARENT_SCOPE)
endfunction()

function(trace ARGS)
  # TODO print current line location, {CMAKE_CURRENT_LIST_LINE} prints the
  # same value
  message(DEBUG "${ARGV}${cColorReset}")
endfunction()

function(print_list LIST)
  trace("> ${cRed}List")
  foreach(item ${LIST})
    trace("  - ${item}")
  endforeach()
endfunction()

function(print_target_property TARGET PROPERTY)
  # Print target property either as a single item or as a list
  get_target_property(TMP ${TARGET} ${PROPERTY})
  list(LENGTH TMP LEN)
  if(${LEN} LESS 2)
    trace("'${cRed}${PROPERTY}${c0}' of '${cBlue}${TARGET}${c0}' "
          "is set to ${TMP}")
  else()
    trace("'${cRed}${PROPERTY}${c0}' of '${cBlue}${TARGET}${c0}' "
          "is set to list of lenth ${LEN}")
    foreach(item ${TMP})
      trace("  - ${item}")
    endforeach()
  endif()
endfunction()

function(add_target_property TARGET PROPERTY VALUE)
  set_property(
    TARGET "${TARGET}"
    APPEND
    PROPERTY "${PROPERTY}" "${VALUE}")
endfunction()


function(list_filter_files OUT GLOB REGEX)
  file(GLOB_RECURSE TMP ${GLOB})
  list(FILTER TMP INCLUDE REGEX "${REGEX}")
  set("${OUT}"
      "${TMP}"
      PARENT_SCOPE)
endfunction()

function(glob_add_sources TARGET EXT_GLOB LS_REGEX)
    list_filter_files(SRC_FILES ${EXT_GLOB} "${LS_REGEX}")
    add_target_property("${TARGET}" SOURCES "${SRC_FILES}")
endfunction()

function(glob_add_sources2 TARGET LS_REGEX)
    glob_add_sources("${TARGET}" *.cpp "${LS_REGEX}")
    glob_add_sources("${TARGET}" *.hpp "${LS_REGEX}")
endfunction()
