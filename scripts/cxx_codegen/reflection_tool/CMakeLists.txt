# Create the executable target

# Link against LLVM libraries
llvm_map_components_to_libnames(llvm_libs support core)

set(REFL_DIR "${BASE}/scripts/cxx_codegen/reflection_tool")

protobuf_generate(
  LANGUAGE
  cpp
  OUT_VAR
  ORG_PROTO_GENERATED_FILES
  PROTOS
  "${REFL_DIR}/reflection_defs.proto"
  PROTOC_OUT_DIR
  "${CMAKE_CURRENT_BINARY_DIR}")

# Shared logic for reflection collector implementation

add_library(
  reflection_lib STATIC
  "${REFL_DIR}/clang_reflection_lib.cpp" "${REFL_DIR}/clang_reflection_demangler.cpp"
  "${REFL_DIR}/clang_reflection_lib.hpp" ${ORG_PROTO_GENERATED_FILES})

target_include_directories(
  reflection_lib
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR} "${DEPS_DIR}/protobuf/src" "${DEPS_DIR}/abseil-cpp"
         "${BASE}/src" "${BASE}/build/haxorg/scripts/cxx_codegen/reflection_tool")

llvm_map_components_to_libnames(
  reflection_lib_llvm_libs
  Core
  Support
  Object
  Demangle
  DebugInfoDWARF
  Target
  MC
  AsmParser
  AsmPrinter
  native)

target_link_libraries(reflection_lib PUBLIC hstd)
target_link_libraries(reflection_lib PRIVATE ${reflection_lib_llvm_libs})

target_link_libraries(reflection_lib ${PROTOBUF_LIBRARIES})
target_compile_options(reflection_lib PRIVATE "-fPIC")
set_target_properties(reflection_lib PROPERTIES CXX_STANDARD 20)

# Binary can be used as a separate tool
add_executable(reflection_tool clang_reflection_tool.cpp)
set_target_properties(reflection_tool PROPERTIES CXX_STANDARD 20)
# FIXME Not clear why, but specified library parameters cause missing symbol errors in some of the
# protobuf libraries. Specifically missing is
# _ZN4absl12lts_2023012512log_internal10LogMessagelsImLi0EEERS2_RKT_, commonly googled as
# absl::lts_20230125 (yes, this is a common issue, but no working solution). ATTW the 'solved'
# responses indicate that it has something to do with new dependency on abseil library in the
# protobuf, but it did not work here.

# https://github.com/rui314/mold/issues/530#issuecomment-1870903572 -- mold ignores this option
# target_link_options(reflection_tool PRIVATE "-Wl,--copy-dt-needed-entries")

target_link_libraries(
  reflection_tool
  PRIVATE reflection_lib
          ${llvm_libs}
          clangBasic
          clangASTMatchers
          clangTooling
          absl::base
          protobuf::libprotobuf
          protobuf::libprotoc)

add_custom_command(
  TARGET reflection_tool
  POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E create_symlink "${CMAKE_BINARY_DIR}" "${BASE}/build/utils")

# Shared library can be loaded as clang plugin

# NOTE: Not linking any LVM libraries here as it will cause LLVM ERROR: inconsistency in registered
# CommandLine options due to duplicate symbols that are loaded in clang and then in shared library.
add_library(reflection_plugin SHARED clang_reflection_plugin.cpp)
set_target_properties(reflection_plugin PROPERTIES CXX_STANDARD 20)
target_link_libraries(reflection_plugin PRIVATE reflection_lib)

add_custom_command(
  TARGET reflection_plugin
  POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E create_symlink "${CMAKE_BINARY_DIR}" "${BASE}/build/utils")

add_custom_command(
  TARGET reflection_plugin
  POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E create_symlink "${PROTOBUF_BINARY}/protoc"
          "${BASE}/build/utils/protoc")
