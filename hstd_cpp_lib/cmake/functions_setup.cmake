function(haxorg_add_bool_compile_definitions target)
    foreach(option IN LISTS ARGN)
        if(${option})
            set(value 1)
        else()
            set(value 0)
        endif()

        target_compile_definitions(${target} PUBLIC "${option}=${value}")
    endforeach()
endfunction()

function(haxorg_set_target_flags_impl)
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
            "-sNO_DISABLE_EXCEPTION_CATCHING"
        )

        if(${HSTD_CPP_BUILD_WITH_PERFETTO})
            list(APPEND EMSCRIPTEN_FLAGS "-s INITIAL_HEAP=600MB")
        endif()

        list(APPEND EMSCRIPTEN_FLAGS "-s EXCEPTION_DEBUG=1")

        if(ORG_USE_SANITIZERS)
            list(
                APPEND EMSCRIPTEN_FLAGS
                "-fsanitize=undefined,address"
                "-sSAFE_HEAP"
            )
            list(APPEND EMSCRIPTEN_FLAGS "-s SAFE_HEAP_LOG=1")
        endif()

        string(JOIN " " EMSCRIPTEN_FLAGS_STR ${EMSCRIPTEN_FLAGS})

        haxorg_add_target_property(${ARG_TARGET} LINK_FLAGS "${EMSCRIPTEN_FLAGS_STR}")
    endif()

    if(NOT ${ORG_BUILD_INTERNAL_TOOLS})
        if(${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
            haxorg_add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-w")
            haxorg_add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-fmax-errors=1")
        endif()
        if(${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
            haxorg_add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-w")
        endif()
    endif()

    if(${ORG_USE_SARIF})
        # Specify output file for the sarif report
        haxorg_add_target_property(
            ${ARG_TARGET}
            COMPILE_OPTIONS
            "-fdiagnostics-format=sarif"
        )
    endif()

    if(${ORG_DISABLE_WARNINGS})
        haxorg_add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-Wno-everything")
    elseif(${ORG_BUILD_ASSUME_CLANG})
        # FIXME: Adding attribute configurations here does not propagate them to the compiler.
    endif()
    haxorg_add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-Wdangling")
    haxorg_add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-Wno-c99-designator")
    haxorg_add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-Werror=dangling")
    haxorg_add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-Xclang")
    haxorg_add_target_property(
        ${ARG_TARGET}
        COMPILE_OPTIONS
        "-fexperimental-lifetime-safety"
    )
    haxorg_add_target_property(
        ${ARG_TARGET}
        COMPILE_OPTIONS
        "-Wexperimental-lifetime-safety"
    )
    haxorg_add_target_property(
        ${ARG_TARGET}
        COMPILE_OPTIONS
        "-Werror=experimental-lifetime-safety"
    )
    haxorg_add_target_property(
        ${ARG_TARGET}
        COMPILE_OPTIONS
        "-Werror=implicit-fallthrough"
    )
    set_target_properties(
        "${ARG_TARGET}"
        PROPERTIES
            CMAKE_CXX_STANDARD
                20
            CXX_STANDARD
                20
    )

    set_target_properties(
        ${ARG_TARGET}
        PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY
                "${CMAKE_BINARY_DIR}"
            LIBRARY_OUTPUT_DIRECTORY
                "${CMAKE_BINARY_DIR}"
            ARCHIVE_OUTPUT_DIRECTORY
                "${CMAKE_BINARY_DIR}"
    )

    if(${ORG_INSTRUMENT_TRACE})
        haxorg_add_target_property(${ARG_TARGET} COMPILE_OPTIONS -finstrument-functions)
    endif()

    target_compile_features(${ARG_TARGET} PUBLIC cxx_std_23)

    if(${ORG_BUILD_ASSUME_CLANG})
        haxorg_add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-ftime-trace")
        haxorg_add_target_property(${ARG_TARGET} LINK_OPTIONS "-ftime-trace")
        find_program(MOLD_LINKER "mold")
        if(MOLD_LINKER)
            haxorg_add_target_property(${ARG_TARGET} LINK_OPTIONS "-fuse-ld=mold")
        endif()
    endif()

    if(${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
        if(ORG_WARNING_SUPPRESSIONS)
            target_compile_options(
                "${ARG_TARGET}"
                PRIVATE
                    "$<$<COMPILE_LANGUAGE:CXX>:--warning-suppression-mappings=${ORG_WARNING_SUPPRESSIONS}>"
            )
        endif()

        # Avoid getting flooded with compilation errors set(CMAKE_CXX_COMPILER clang++)
        haxorg_add_target_property(
            ${ARG_TARGET}
            COMPILE_OPTIONS
            "-fno-omit-frame-pointer"
        )
        haxorg_add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-fPIC")
        haxorg_add_target_property(
            ${ARG_TARGET}
            COMPILE_OPTIONS
            "-ftemplate-backtrace-limit=0"
        )

        if(${ORG_USE_SANITIZER})
            if(NOT ${ARG_FORCE_NO_ASAN})
                haxorg_add_target_property(
                    ${ARG_TARGET}
                    COMPILE_OPTIONS
                    "-fsanitize=undefined,address"
                )
                # LLVM ships with sanitizer runtime and I could not figure out how to compile it in
                # statically nor do I know whether this is really necessary or not
                haxorg_add_target_property(
                    ${ARG_TARGET}
                    COMPILE_OPTIONS
                    "-shared-libasan"
                )
                haxorg_add_target_property(
                    ${ARG_TARGET}
                    COMPILE_OPTIONS
                    "-fsanitize-ignorelist=${CMAKE_CURRENT_SOURCE_DIR}/ignorelist.txt"
                )
                haxorg_add_target_property(
                    ${ARG_TARGET}
                    LINK_OPTIONS
                    "-fsanitize-ignorelist=${CMAKE_CURRENT_SOURCE_DIR}/ignorelist.txt"
                )
                haxorg_add_target_property(
                    ${ARG_TARGET}
                    LINK_OPTIONS
                    "-fsanitize=undefined,address"
                )
                target_link_libraries(${ARG_TARGET} PRIVATE ${ASAN_LIBRARY})
            endif()
        endif()

        if(${ORG_USE_XRAY})
            haxorg_add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-fxray-instrument")
            haxorg_add_target_property(${ARG_TARGET} LINK_OPTIONS "-fxray-instrument")
            haxorg_add_target_property(
                ${ARG_TARGET}
                COMPILE_OPTIONS
                "-fxray-instruction-threshold=50"
            )
            haxorg_add_target_property(
                ${ARG_TARGET}
                COMPILE_OPTIONS
                "-fxray-attr-list=${CMAKE_CURRENT_SOURCE_DIR}/scripts/cxx_repository/xray_list.txt"
            )
        endif()

        haxorg_add_target_property(${ARG_TARGET} COMPILE_DEFINITIONS IMMER_TAGGED_NODE=0)

        if(${ORG_USE_XRAY})
            haxorg_add_target_property(${ARG_TARGET} COMPILE_DEFINITIONS ORG_USE_XRAY)
        endif()

        if(${ORG_USE_PGO})
            haxorg_add_target_property(${ARG_TARGET} COMPILE_DEFINITIONS ORG_USE_PGO)
            haxorg_add_target_property(
                ${ARG_TARGET}
                COMPILE_OPTIONS
                "-fprofile-instr-generate"
            )
            haxorg_add_target_property(
                ${ARG_TARGET}
                LINK_OPTIONS
                "-fprofile-instr-generate"
            )
            haxorg_add_target_property(${ARG_TARGET} COMPILE_OPTIONS "-fcoverage-mapping")
            haxorg_add_target_property(${ARG_TARGET} LINK_OPTIONS "-fcoverage-mapping")
        endif()

        haxorg_add_target_property(${ARG_TARGET} COMPILE_DEFINITIONS QT_FORCE_ASSERTS)

        if(${PROFILE_USE})
            haxorg_add_target_property(
                ${ARG_TARGET}
                COMPILE_OPTIONS
                "-fprofile-use=${CMAKE_CURRENT_SOURCE_DIR}/haxorg-compile.profdata"
            )
        endif()

        if(${ORG_USE_COVERAGE})
            # https://reviews.llvm.org/D52034 https://reviews.llvm.org/D52033
            set(PROFILE_FILTER_FLAG
                --coverage
                "-fprofile-filter-files=thirdparty" #
                --coverage
                "-fprofile-filter-files=base_lexer_gen" #
                --coverage
                "-fprofile-filter-files=pb\\.(cc|cpp|h|hpp)$" #
            )

            target_compile_options(
                ${ARG_TARGET}
                PRIVATE
                    -fprofile-instr-generate
                    -fcoverage-mapping
                    -ftest-coverage
                    "${PROFILE_FILTER_FLAG}"
            )

            target_link_options(
                ${ARG_TARGET}
                PRIVATE
                    -lgcov
                    --coverage
                    -fprofile-instr-generate
                    -fcoverage-mapping
            )
        endif()
    endif()
endfunction()

function(haxorg_split_debug_info target)
    if(${ORG_SEPARATE_DEBUG_SYMBOLS})
        add_custom_command(
            TARGET ${target}
            POST_BUILD
            COMMAND
                ${CMAKE_OBJCOPY} --only-keep-debug $<TARGET_FILE:${target}>
                $<TARGET_FILE:${target}>.debug
            COMMAND
                ${CMAKE_OBJCOPY} --strip-debug $<TARGET_FILE:${target}>
            COMMAND
                ${CMAKE_OBJCOPY} --add-gnu-debuglink=$<TARGET_FILE:${target}>.debug
                $<TARGET_FILE:${target}>
            COMMENT "Splitting debug info for ${target}"
        )
    endif()
endfunction()

function(haxorg_set_target_flags TARGET)
    haxorg_set_target_flags_impl(TARGET "${TARGET}")
endfunction()

function(haxorg_target_setup_v2)
    cmake_parse_arguments(ARG "" "TARGET;FORCE_NO_ASAN" "" "${ARGN}")
    haxorg_set_target_output("${ARG_TARGET}")
    haxorg_set_target_flags_impl(
        TARGET "${ARG_TARGET}"
        FORCE_NO_ASAN "${ARG_FORCE_NO_ASAN}"
    )
endfunction()

function(haxorg_add_executable TARGET)
    add_executable("${TARGET}")
    haxorg_set_target_output("${TARGET}")
    haxorg_set_target_flags("${TARGET}")
endfunction()

function(haxorg_add_library TARGET)
    add_library("${TARGET}")
    haxorg_set_target_output("${TARGET}")
    haxorg_set_target_flags("${TARGET}")
endfunction()

function(haxorg_opt_1_excludes_opt_2 opt1 opt2)
    if(${opt1} AND ${opt2})
        message(FATAL_ERROR "${opt2} cannot be enabled when ${opt1} is enabled")
    endif()
endfunction()

include(GNUInstallDirs)

function(haxorg_add_protobuf)
    cmake_parse_arguments(
        HAP
        ""
        "TARGET"
        "IMPORT_DIRS;PROTO_SOURCES;PUBLIC_LIBRARIES;PRIVATE_LIBRARIES"
        ${ARGN}
    )

    if(HAP_UNPARSED_ARGUMENTS)
        message(
            FATAL_ERROR
            "haxorg_add_protobuf(): unknown arguments: ${HAP_UNPARSED_ARGUMENTS}"
        )
    endif()

    if(NOT TARGET "${HAP_TARGET}")
        message(
            FATAL_ERROR
            "haxorg_add_protobuf(): target '${HAP_TARGET}' does not exist"
        )
    endif()

    if(NOT HAP_PROTO_SOURCES)
        message(FATAL_ERROR "haxorg_add_protobuf(): PROTO_SOURCES is required")
    endif()

    set(HAP_OWN_PROTO_ROOT "${PROJECT_SOURCE_DIR}/proto")
    foreach(HAP_SOURCE IN LISTS HAP_PROTO_SOURCES)
        cmake_path(
            IS_PREFIX
            HAP_OWN_PROTO_ROOT
            "${HAP_SOURCE}"
            NORMALIZE
            HAP_IS_OWN
        )
        cmake_path(GET HAP_SOURCE PARENT_PATH HAP_SOURCE_DIR)
        if(
            NOT HAP_IS_OWN
            OR NOT HAP_SOURCE_DIR
                STREQUAL
                "${HAP_OWN_PROTO_ROOT}/${HAXORG_PACKAGE_NAME}"
        )
            message(
                FATAL_ERROR
                "haxorg_add_protobuf(): '${HAP_SOURCE}' must be located in "
                "'${HAP_OWN_PROTO_ROOT}/${HAXORG_PACKAGE_NAME}/'"
            )
        endif()
    endforeach()

    set(HAP_PROTO_OUT_DIR "${CMAKE_BINARY_DIR}/generated/proto")
    file(MAKE_DIRECTORY "${HAP_PROTO_OUT_DIR}")

    set(HAP_EFFECTIVE_IMPORT_DIRS
        "${HAP_OWN_PROTO_ROOT}"
        ${HAXORG_DEPS_PROTO_IMPORT_DIRS}
        ${HAP_IMPORT_DIRS}
    )
    if(DEFINED protovalidate_cc_PROTO_IMPORT_DIR)
        list(APPEND HAP_EFFECTIVE_IMPORT_DIRS "${protovalidate_cc_PROTO_IMPORT_DIR}")
    endif()
    list(REMOVE_DUPLICATES HAP_EFFECTIVE_IMPORT_DIRS)

    protobuf_generate(
        LANGUAGE cpp
        OUT_VAR HAP_GENERATED_FILES
        IMPORT_DIRS
            ${HAP_EFFECTIVE_IMPORT_DIRS}
        PROTOS
            ${HAP_PROTO_SOURCES}
        PROTOC_OUT_DIR "${HAP_PROTO_OUT_DIR}"
    )

    target_sources("${HAP_TARGET}" PRIVATE ${HAP_GENERATED_FILES})
    target_include_directories(
        "${HAP_TARGET}"
        PUBLIC
            "$<BUILD_INTERFACE:${HAP_PROTO_OUT_DIR}>"
    )
    target_link_libraries(
        "${HAP_TARGET}"
        PUBLIC
            protobuf::libprotobuf
            ${HAP_PUBLIC_LIBRARIES}
        PRIVATE
            ${HAP_PRIVATE_LIBRARIES}
    )
endfunction()
