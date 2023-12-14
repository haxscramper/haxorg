function(set_target_flags TARGET)
  add_target_property(${TARGET} COMPILE_OPTIONS "-Wno-reorder-init-list")
  add_target_property(${TARGET} COMPILE_OPTIONS "-Qunused-arguments")
  # add_target_property(${TARGET} COMPILE_OPTIONS
  #                     @${BASE}/scripts/cxx_repository/warning_config.txt)

  if(${TRACE_INSTRUMENT})
    add_target_property(${TARGET} COMPILE_OPTIONS -finstrument-functions)
  endif()

  if(${USE_XRAY})

  else()
      add_target_property(${TARGET} COMPILE_OPTIONS "-fuse-ld=mold")
      add_target_property(${TARGET} LINK_OPTIONS "-fuse-ld=mold")
  endif()


  target_compile_features(${TARGET} PUBLIC cxx_std_23)

  add_target_property(${TARGET} COMPILE_OPTIONS "-ftime-trace")
  add_target_property(${TARGET} LINK_OPTIONS "-ftime-trace")

  if(${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    # Avoid getting flooded with compilation errors
    set(CMAKE_CXX_COMPILER clang++)
#    if(NOT ${MAX_COMPILE_ERRORS} MATCHES ON)
#        add_target_property(${TARGET} COMPILE_OPTIONS
#                            "-ferror-limit=${MAX_COMPILE_ERRORS}")
#    endif()

    # add_target_property(${TARGET} COMPILE_OPTIONS "-v")

    # add_target_property(${TARGET} COMPILE_OPTIONS
    #                     "-fdiagnostics-format=sarif")

    add_target_property(${TARGET} COMPILE_OPTIONS "-fno-omit-frame-pointer")
    add_target_property(${TARGET} COMPILE_OPTIONS "-fPIC")

    if(${USE_SANITIZER})
        add_target_property(${TARGET} COMPILE_OPTIONS "-fsanitize=undefined,address")
        # LLVM ships with sanitizer runtime and I could not figure out how to compile it 
        # in statically nor do I know whether this is really necessary or not
        add_target_property(${TARGET} COMPILE_OPTIONS "-shared-libasan")
        add_target_property(${TARGET} COMPILE_OPTIONS "-fsanitize-ignorelist=${BASE}/ignorelist.txt")
        add_target_property(${TARGET} LINK_OPTIONS "-fsanitize-ignorelist=${BASE}/ignorelist.txt")
        add_target_property(${TARGET} LINK_OPTIONS "-fsanitize=undefined,address")
        add_target_property(${TARGET} LINK_OPTIONS "-shared-libasan")
        target_link_libraries(${TARGET} PRIVATE ${ASAN_LIBRARY})
    endif()
        
    # Specify runtime search paths for the libraries so created binaries did not have to 
    # depend on the LD_PRELOAD_PATH being set up correctly. 
    add_target_property(${TARGET} LINK_OPTIONS "-Wl,-rpath,${LLVM_GNU_CLANG_DIR},-rpath,${LLVM_STD_DIRS}")

    if(${USE_XRAY})
        add_target_property(${TARGET} COMPILE_OPTIONS "-fxray-instrument")
        add_target_property(${TARGET} LINK_OPTIONS "-fxray-instrument")
        add_target_property(${TARGET} COMPILE_OPTIONS "-fxray-instruction-threshold=50")
        add_target_property(${TARGET} COMPILE_OPTIONS "-fxray-attr-list=${BASE}/scripts/cxx_repository/xray_list.txt")
    endif()

    if(${USE_PERFETTO})
        add_target_property(${TARGET} COMPILE_DEFINITIONS USE_PERFETTO)
    endif()

    if(${USE_XRAY})
        add_target_property(${TARGET} COMPILE_DEFINITIONS USE_XRAY)
    endif()

    if(${USE_PGO})
        add_target_property(${TARGET} COMPILE_DEFINITIONS USE_PGO)
        add_target_property(${TARGET} COMPILE_OPTIONS "-fprofile-instr-generate")
        add_target_property(${TARGET} LINK_OPTIONS "-fprofile-instr-generate")
        add_target_property(${TARGET} COMPILE_OPTIONS "-fcoverage-mapping")
        add_target_property(${TARGET} LINK_OPTIONS "-fcoverage-mapping")
    endif()

    add_target_property(${TARGET} COMPILE_DEFINITIONS QT_FORCE_ASSERTS)



    if(${PROFILE_USE})
        add_target_property(${TARGET} COMPILE_OPTIONS
            "-fprofile-use=${BASE}/haxorg-compile.profdata")
    endif()

    if(${TEST_COVERAGE})
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


    if(${USE_PERFETTO})
        add_target_property(${TARGET} PRECOMPILE_HEADERS <perfetto.h>)
    endif()

endfunction()
