function(set_target_flags TARGET)
  # add_target_property(${TARGET} COMPILE_OPTIONS -w)
  add_target_property(${TARGET} COMPILE_OPTIONS
                      @${BASE}/scripts/warning_config.txt)

  if(${TRACE_INSTRUMENT})
    add_target_property(${TARGET} COMPILE_OPTIONS -finstrument-functions)
  endif()
  if(${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    message(INFO "Using clang compiler")
    # Avoid getting flooded with compilation errors
    set(CMAKE_CXX_COMPILER clang++)
#    if(NOT ${MAX_COMPILE_ERRORS} MATCHES ON)
#        add_target_property(${TARGET} COMPILE_OPTIONS
#                            "-ferror-limit=${MAX_COMPILE_ERRORS}")
#    endif()

    # add_target_property(${TARGET} COMPILE_OPTIONS "-v")

    # add_target_property(${TARGET} COMPILE_OPTIONS
    #                     "-fdiagnostics-format=sarif")

    add_target_property(${TARGET} COMPILE_OPTIONS
                        "-Wdocumentation")

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

function(set_common_files TARGET)
  set_target_properties("${TARGET}"
      PROPERTIES
      CMAKE_CXX_STANDARD 20
      CXX_STANDARD 20)
  add_target_property("${TARGET}" SOURCES "${SRC_FILES}")
  add_target_property("${TARGET}" SOURCES "${HEADER_FILES}")
  add_target_property("${TARGET}" INCLUDE_DIRECTORIES "${BASE}/src")
  add_target_property("${TARGET}" LINK_LIBRARIES dw)
  add_target_property("${TARGET}" INCLUDE_DIRECTORIES "${AUTOGEN_BUILD_DIR}")


  # target_precompile_headers(
  #   "${TARGET}"
  #   PRIVATE
  #   src/lexbase/PosStr.hpp
  #   src/lexbase/Node.hpp
  #   src/lexbase/Token.hpp
  # )

endfunction()
