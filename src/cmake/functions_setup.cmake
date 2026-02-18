function(set_target_flags_impl)
  cmake_parse_arguments(ARG "" "TARGET;FORCE_NO_ASAN" "" "${ARGN}")

  if(${ORG_BUILD_EMCC})
    set(EMSCRIPTEN_FLAGS
        "-g4"
        "-gsource-map"
        "-s WASM=1"
        "-s STACK_SIZE=200MB"
        "-s ALLOW_MEMORY_GROWTH=1"
        "-s MODULARIZE=1"
        "-s ASSERTIONS=1"
        "-s EXPORT_NAME='haxorg_wasm'"
        "-s USE_PTHREADS=0"
        "--bind"
        "-sNO_DISABLE_EXCEPTION_CATCHING")

    if(${ORG_BUILD_WITH_PERFETTO})
      list(APPEND EMSCRIPTEN_FLAGS "-s INITIAL_HEAP=600MB")
    endif()

    list(APPEND EMSCRIPTEN_FLAGS "-s EXCEPTION_DEBUG=1")

    if(ORG_USE_SANITIZERS)
      list(APPEND EMSCRIPTEN_FLAGS "-fsanitize=undefined,address" "-sSAFE_HEAP")
      list(APPEND EMSCRIPTEN_FLAGS "-s SAFE_HEAP_LOG=1")
    endif()

    string(JOIN " " EMSCRIPTEN_FLAGS_STR ${EMSCRIPTEN_FLAGS})

    add_target_property(${ARG_TARGET} LINK_FLAGS "${EMSCRIPTEN_FLAGS_STR}")
  endif()

  if(NOT ${ORG_BUILD_INTERNAL_TOOLS})
    if(${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
      add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-w")
      add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-fmax-errors=1")
    endif()
    if(${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
      add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-w")
    endif()
  endif()

  if(${ORG_USE_SARIF})
    # Specify output file for the sarif report
    add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-fdiagnostics-format=sarif")
  endif()

  if(${ORG_BUILD_WITH_CGRAPH})
    add_target_property(${ARG_TARGET} COMPILE_DEFINITIONS ORG_BUILD_WITH_CGRAPH=1)
  else()
    add_target_property(${ARG_TARGET} COMPILE_DEFINITIONS ORG_BUILD_WITH_CGRAPH=0)
  endif()

  if(${ORG_DISABLE_WARNINGS})
    add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-Wno-everything")
  elseif(${ORG_BUILD_ASSUME_CLANG})
    add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-Wno-reorder-init-list")
    add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-Wno-c99-designator")
    add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-Wno-deprecated-declarations")
    add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-Wno-unknown-attributes")
    add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-Wno-macro-redefined")
    add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-Wno-unused-command-line-argument")
    add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-Wno-defaulted-function-deleted")
    add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-Wno-ambiguous-reversed-operator")
    add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-Qunused-arguments")
  endif()
  add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-Werror=implicit-fallthrough")

  set_target_properties(
    ${ARG_TARGET}
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
               LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
               ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

  if(${ORG_INSTRUMENT_TRACE})
    add_target_property(${ARG_TARGET} COMPILE_OPTIONS -finstrument-functions)
  endif()

  target_compile_features(${ARG_TARGET} PUBLIC cxx_std_23)

  if(${ORG_BUILD_ASSUME_CLANG})
    add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-ftime-trace")
    add_target_property(${ARG_TARGET} LINK_OPTIONS "-ftime-trace")
    find_program(MOLD_LINKER "mold")
    if(MOLD_LINKER)
      add_target_property(${ARG_TARGET} LINK_OPTIONS "-fuse-ld=mold")
    endif()
  endif()

  if(${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    # Avoid getting flooded with compilation errors set(CMAKE_CXX_COMPILER clang++)

    add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-fno-omit-frame-pointer")
    add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-fPIC")
    add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-ftemplate-backtrace-limit=0")

    if(${ORG_USE_SANITIZER})
      if(NOT ${ARG_FORCE_NO_ASAN})
        add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-fsanitize=undefined,address")
        # LLVM ships with sanitizer runtime and I could not figure out how to compile it in
        # statically nor do I know whether this is really necessary or not
        add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-shared-libasan")
        add_target_property(${ARG_TARGET} COMPILE_OPTIONS
                            "-fsanitize-ignorelist=${BASE}/ignorelist.txt")
        add_target_property(${ARG_TARGET} LINK_OPTIONS
                            "-fsanitize-ignorelist=${BASE}/ignorelist.txt")
        add_target_property(${ARG_TARGET} LINK_OPTIONS "-fsanitize=undefined,address")
        target_link_libraries(${ARG_TARGET} PRIVATE ${ASAN_LIBRARY})
      endif()
    endif()

    if(${ORG_USE_XRAY})
      add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-fxray-instrument")
      add_target_property(${ARG_TARGET} LINK_OPTIONS "-fxray-instrument")
      add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-fxray-instruction-threshold=50")
      add_target_property(${ARG_TARGET} COMPILE_OPTIONS
                          "-fxray-attr-list=${BASE}/scripts/cxx_repository/xray_list.txt")
    endif()

    add_target_property(${ARG_TARGET} COMPILE_DEFINITIONS IMMER_TAGGED_NODE=0)

    if(${ORG_BUILD_WITH_PERFETTO})
      add_target_property(${ARG_TARGET} COMPILE_DEFINITIONS ORG_BUILD_WITH_PERFETTO)
    endif()

    if(${ORG_BUILD_WITH_TRACY})
      add_target_property(${ARG_TARGET} COMPILE_DEFINITIONS ORG_BUILD_WITH_TRACY)
    endif()

    if(${ORG_USE_XRAY})
      add_target_property(${ARG_TARGET} COMPILE_DEFINITIONS ORG_USE_XRAY)
    endif()

    if(${ORG_USE_PGO})
      add_target_property(${ARG_TARGET} COMPILE_DEFINITIONS ORG_USE_PGO)
      add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-fprofile-instr-generate")
      add_target_property(${ARG_TARGET} LINK_OPTIONS "-fprofile-instr-generate")
      add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-fcoverage-mapping")
      add_target_property(${ARG_TARGET} LINK_OPTIONS "-fcoverage-mapping")
    endif()

    add_target_property(${ARG_TARGET} COMPILE_DEFINITIONS QT_FORCE_ASSERTS)

    if(${PROFILE_USE})
      add_target_property(${ARG_TARGET} COMPILE_OPTIONS
                          "-fprofile-use=${BASE}/haxorg-compile.profdata")
    endif()

    if(${ORG_USE_COVERAGE})
      # https://reviews.llvm.org/D52034 https://reviews.llvm.org/D52033
      set(PROFILE_FILTER_FLAG
          --coverage "-fprofile-filter-files=thirdparty" #
          --coverage "-fprofile-filter-files=base_lexer_gen" #
          --coverage "-fprofile-filter-files=pb\\.(cc|cpp|h|hpp)$" #
      )

      target_compile_options(${ARG_TARGET} PRIVATE -fprofile-instr-generate -fcoverage-mapping
                                                   -ftest-coverage "${PROFILE_FILTER_FLAG}")

      target_link_options(${ARG_TARGET} PRIVATE -lgcov --coverage -fprofile-instr-generate
                          -fcoverage-mapping)

    endif()
  endif()
endfunction()

function(split_debug_info target)
  if(${ORG_SEPARATE_DEBUG_SYMBOLS})
    add_custom_command(
      TARGET ${target}
      POST_BUILD
      COMMAND ${CMAKE_OBJCOPY} --only-keep-debug $<TARGET_FILE:${target}>
              $<TARGET_FILE:${target}>.debug
      COMMAND ${CMAKE_OBJCOPY} --strip-debug $<TARGET_FILE:${target}>
      COMMAND ${CMAKE_OBJCOPY} --add-gnu-debuglink=$<TARGET_FILE:${target}>.debug
              $<TARGET_FILE:${target}>
      COMMENT "Splitting debug info for ${target}")
  endif()
endfunction()

function(set_target_flags TARGET)
  set_target_flags_impl(TARGET "${TARGET}")
endfunction()

function(set_common_files TARGET)
  set_target_properties("${TARGET}" PROPERTIES CMAKE_CXX_STANDARD 20 CXX_STANDARD 20)

  add_target_property("${TARGET}" SOURCES "${SRC_FILES}")
  add_target_property("${TARGET}" SOURCES "${HEADER_FILES}")
  add_target_property("${TARGET}" INCLUDE_DIRECTORIES "${BASE}/src")
  # add_target_property("${TARGET}" LINK_LIBRARIES dw)
  add_target_property("${TARGET}" INCLUDE_DIRECTORIES "${AUTOGEN_BUILD_DIR}")
endfunction()

function(haxorg_target_setup_v2)
  cmake_parse_arguments(ARG "" "TARGET;FORCE_NO_ASAN" "" "${ARGN}")
  set_common_files("${ARG_TARGET}")
  set_target_output("${ARG_TARGET}")
  set_target_flags_impl(TARGET "${ARG_TARGET}" FORCE_NO_ASAN "${ARG_FORCE_NO_ASAN}")
endfunction()

function(haxorg_add_executable TARGET)
  add_executable("${TARGET}")
  set_common_files("${TARGET}")
  set_target_output("${TARGET}")
  set_target_flags("${TARGET}")
endfunction()

function(haxorg_add_library TARGET)
  add_library("${TARGET}")
  set_common_files("${TARGET}")
  set_target_output("${TARGET}")
  set_target_flags("${TARGET}")
endfunction()
