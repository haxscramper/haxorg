# Find the LLVM package. This also defines a lot of variables, see:
# https://llvm.org/docs/CMake.html#embedding-llvm-in-your-project
find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

set(REFL_DIR "${BASE}/scripts/cxx_codegen")
set(REFL_PROTOC_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")

protobuf_generate(
  LANGUAGE
  cpp
  OUT_VAR
  ORG_PROTO_GENERATED_FILES
  PROTOS
  "${REFL_DIR}/reflection_defs.proto"
  PROTOC_OUT_DIR
  ${REFL_PROTOC_OUT_DIR})

add_executable(reflection_tool ${ORG_PROTO_GENERATED_FILES})

glob_add_sources2(TARGET reflection_tool LS_REGEX "${BASE}/scripts/cxx_codegen/.*" SEARCH_BASE
                  "${BASE}")
haxorg_target_setup_v2(TARGET reflection_tool)

if(${ORG_USE_PERFETTO})
  target_link_libraries(reflection_tool PUBLIC Perfetto::perfetto)
  target_compile_definitions(reflection_tool PUBLIC ORG_USE_PERFETTO)
endif()

if(${ORG_USE_TRACY})
  target_link_libraries(reflection_tool PRIVATE Tracy::TracyClient)
endif()

target_include_directories(
  reflection_tool
  PUBLIC ${REFL_PROTOC_OUT_DIR}
         "${DEPS_DIR}/protobuf/src"
         "${DEPS_DIR}/abseil-cpp"
         "${BASE}/src"
         "${BASE}/build/haxorg/scripts/cxx_codegen"
         "${BASE}/scripts/cxx_codegen"
         ${LLVM_INCLUDE_DIRS}
         ${CLANG_INCLUDE_DIRS})

target_link_libraries(
  reflection_tool
  PUBLIC SQLiteCpp
         LLVM
         clang-cpp
         sqlite3
         tbb
         hstd
         ${PROTOBUF_LIBRARIES}
         protobuf::libprotobuf
         protobuf::libprotoc)

target_compile_definitions(reflection_tool PUBLIC ${LLVM_DEFINITIONS})

add_custom_command(
  TARGET reflection_tool
  POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E create_symlink "${CMAKE_BINARY_DIR}" "${BASE}/build/utils")
