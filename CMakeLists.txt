cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(haxorg LANGUAGES CXX)
set(BASE "${CMAKE_SOURCE_DIR}")

set(DEPS_DIR ${BASE}/build/dependencies/conan)
list(PREPEND CMAKE_MODULE_PATH ${DEPS_DIR})
include(${DEPS_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

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
  set_target_properties(
    ${TARGET}
    PROPERTIES # Easier to ignore in git
               SUFFIX ".bin"
               # Output binary into the same directory, add extension to it
               RUNTIME_OUTPUT_DIRECTORY "${BASE}")
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

option(TRACE_INSTRUMENT "Generate instrumentation trace")
option(USE_SINGLE_FILE_CATCH "Use single-file catch2 or installed one")
option(TEST_COVERAGE "Enable test coverage")
option(MAX_COMPILE_ERRORS
       "Max number of compilation errors before compiler stops" 1)

function(set_target_flags TARGET)
  # add_target_property(${TARGET} COMPILE_OPTIONS -w)
  add_target_property(${TARGET} COMPILE_OPTIONS
                      @${BASE}/scripts/warning_config.txt)

  if(${TRACE_INSTRUMENT})
    add_target_property(${TARGET} COMPILE_OPTIONS -finstrument-functions)
  endif()
  if(${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    # Avoid getting flooded with compilation errors
    set(CMAKE_CXX_COMPILER clang++)
    add_target_property(${TARGET} COMPILE_OPTIONS
                        "-ferror-limit=${MAX_COMPILE_ERRORS}")

    if(${TEST_COVERAGE})
      message(INFO " Test coverage enabled")
      target_compile_options(
        ${TARGET} PRIVATE -fprofile-instr-generate -fcoverage-mapping
                          -ftest-coverage)
      target_link_options(${TARGET} PRIVATE -lgcov --coverage
                          -fprofile-instr-generate -fcoverage-mapping)

    endif()
  endif()

  if(${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
    # Same configuration option for g++ compiler
    set(CMAKE_CXX_COMPILER g++)
    add_target_property(${TARGET} COMPILE_OPTIONS
                        "-fmax-errors=${MAX_COMPILE_ERRORS}")

    if(${TEST_COVERAGE})
      message(INFO " Test coverage enabled")
      target_compile_options(${TARGET} PRIVATE --coverage)
      target_link_options(${TARGET} PRIVATE -lgcov --coverage)
    endif()

  endif()
endfunction()

function(list_filter_files OUT GLOB REGEX)
  file(GLOB_RECURSE TMP ${GLOB})
  list(FILTER TMP INCLUDE REGEX "${REGEX}")
  set("${OUT}"
      "${TMP}"
      PARENT_SCOPE)
endfunction()

function(tmp TARGET PROPERTY VALUE)
  set_property(
    TARGET "${TARGET}"
    APPEND
    PROPERTY "${PROPERTY}" "${VALUE}")
endfunction()

find_package(antlr4-runtime REQUIRED)
find_package(antlr4-generator REQUIRED)
find_package(fmt REQUIRED)
find_package(yaml-cpp REQUIRED)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
trace(">>>>>>>>> ${QT_VERSION_MAJOR}")

function(set_common_files TARGET)
  list_filter_files(SRC_FILES *.cpp "${BASE}/src/.*")
  list_filter_files(HEADER_FILES *.hpp "${BASE}/src/.*")
  add_target_property("${TARGET}" SOURCES "${SRC_FILES}")
  add_target_property("${TARGET}" SOURCES "${HEADER_FILES}")
  add_target_property("${TARGET}" INCLUDE_DIRECTORIES "${BASE}/src")
  add_target_property("${TARGET}" LINK_LIBRARIES dw)
endfunction()

function(add_antlr_base TARGET)
  # add directories for generated include files
  add_target_property(${TARGET} INCLUDE_DIRECTORIES ${ANTLR4_INCLUDE_DIR})
  add_target_property(${TARGET} LINK_LIBRARIES antlr4_shared)
endfunction()

add_executable(tests)
set_common_files(tests)
set_target_output(tests)
set_target_flags(tests)
list_filter_files(TEST_FILES "t*.cpp" "${BASE}/tests/.*")
add_target_property(tests SOURCES "${TEST_FILES}")
add_antlr_base(tests)
target_link_libraries(tests PUBLIC fmt::fmt yaml-cpp::yaml-cpp
                                   "Qt${QT_VERSION_MAJOR}::Core")

if(${USE_SINGLE_FILE_CATCH})
  add_target_property(tests SOURCES
                      "${BASE}/deps/catch2/catch_amalgamated.cpp")
  add_target_property(tests INCLUDE_DIRECTORIES "${BASE}/deps/catch2")
  add_target_property(tests COMPILE_DEFINITIONS
                      "HAXORG_USE_SINGLE_FILE_CATCH")
  add_target_property(tests COMPILE_DEFINITIONS
                      "CATCH_AMALGAMATED_CUSTOM_MAIN")
  add_target_property(tests COMPILE_DEFINITIONS
                      "CATCH_CONFIG_DISABLE_EXCEPTIONS")
else()
  find_package(Catch2 3 REQUIRED)
  add_target_property(tests LINK_LIBRARIES Catch2::Catch2)
endif()

set(AUTOGEN_BUILD_DIR ${BASE}/build/autogen)
file(MAKE_DIRECTORY ${AUTOGEN_BUILD_DIR})
set(SCRIPT_DIR "${BASE}/src/scripts")

add_custom_command(
  OUTPUT ${AUTOGEN_BUILD_DIR}/enum.json
  COMMAND "${SCRIPT_DIR}/generate_type_info.py"
          "${BASE}/src/types/enums.hpp" "${AUTOGEN_BUILD_DIR}/enum.json"
  DEPENDS "${SCRIPT_DIR}/generate_type_info.py"
          "${BASE}/src/types/enums.hpp"
  COMMENT "Generating enum reflection information")

add_custom_command(
  OUTPUT "${AUTOGEN_BUILD_DIR}/autogen_enum_help.hpp"
         "${AUTOGEN_BUILD_DIR}/autogen_enum_help.cpp"
  COMMAND
    "${SCRIPT_DIR}/generate_type_aux.py" #
    "${AUTOGEN_BUILD_DIR}/enum.json" #
    "${AUTOGEN_BUILD_DIR}/autogen_enum_help.hpp" #
    "${AUTOGEN_BUILD_DIR}/autogen_enum_help.cpp" #
  DEPENDS "${SCRIPT_DIR}/generate_type_aux.py"
          "${AUTOGEN_BUILD_DIR}/enum.json"
  COMMENT "Generating enum reflection wrappers")

add_custom_target(
  enum_reflection DEPENDS "${AUTOGEN_BUILD_DIR}/autogen_enum_help.hpp"
                          "${AUTOGEN_BUILD_DIR}/autogen_enum_help.cpp")

add_dependencies(tests enum_reflection)
add_target_property(tests INCLUDE_DIRECTORIES "${AUTOGEN_BUILD_DIR}")

# generate parser set(ANTLR4_JAR_LOCATION
# "/usr/share/java/antlr-complete.jar") antlr4_generate(plantuml
# "${BASE}/src/grammars/PLantUML.g4" BOTH FALSE TRUE)

# add_target_property(tests SOURCES "${ANTLR4_SRC_FILES_plantuml}")
