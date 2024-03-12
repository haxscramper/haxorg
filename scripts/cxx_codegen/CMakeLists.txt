cmake_minimum_required(VERSION 3.10)

project(ConvertConstRef)

set(BASE "${CMAKE_SOURCE_DIR}/../..")
# Specify the path to the LLVM toolchain
set(TOOLCHAIN "${BASE}/toolchain")
# Set the LLVM_DIR to the location of LLVMConfig.cmake
set(LLVM_DIR "${TOOLCHAIN}/llvm/lib/cmake/llvm")
set(Clang_DIR "${TOOLCHAIN}/llvm/lib/cmake/clang")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

set(DEPS_DIR "${BASE}/thirdparty")

add_subdirectory("${DEPS_DIR}/abseil-cpp" "${CMAKE_BINARY_DIR}/abseil_build")

include("${BASE}/src/hstd/wrappers/google_deps/google_deps.cmake")
add_google_deps("${BASE}")

include("${DEPS_DIR}/protobuf/cmake/protobuf-generate.cmake")

set(LLVM_LIB_DIR "${TOOLCHAIN}/llvm/lib")

# Find the LLVM package. This also defines a lot of variables, see:
# https://llvm.org/docs/CMake.html#embedding-llvm-in-your-project
find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

# Adding LLVM definitions and include directories
add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${CLANG_INCLUDE_DIRS})

# Create the executable target

# Link against LLVM libraries
llvm_map_components_to_libnames(llvm_libs support core)

add_executable(convert_const_ref convert_const_ref.cpp)
target_link_libraries(
  convert_const_ref ${llvm_libs} clangBasic clangASTMatchers
  clangTooling # Add more Clang components as neede
)

protobuf_generate(
  LANGUAGE
  cpp
  OUT_VAR
  ORG_PROTO_GENERATED_FILES
  PROTOS
  "${BASE}/scripts/cxx_codegen/reflection_defs.proto"
  PROTOC_OUT_DIR
  "${CMAKE_CURRENT_BINARY_DIR}")

set_target_properties(convert_const_ref PROPERTIES CXX_STANDARD 20)

# Shared logic for reflection collector implementation

add_library(
  reflection_lib STATIC clang_reflection_lib.cpp clang_reflection_lib.hpp
                        ${ORG_PROTO_GENERATED_FILES})

target_include_directories(
  reflection_lib PUBLIC ${CMAKE_CURRENT_BINARY_DIR} "${DEPS_DIR}/protobuf/src"
                        "${DEPS_DIR}/abseil-cpp")

target_link_libraries(reflection_lib ${PROTOBUF_LIBRARIES})
target_compile_options(reflection_lib PRIVATE "-fPIC")
set_target_properties(reflection_lib PROPERTIES CXX_STANDARD 20)
target_precompile_headers(
  reflection_lib
  PRIVATE
  <clang/AST/ASTConsumer.h>
  <clang/AST/RecursiveASTVisitor.h>
  <clang/Frontend/FrontendPluginRegistry.h>
  <clang/Frontend/CompilerInstance.h>
  <clang/Sema/Sema.h>)

# Binary can be used as a separate tool
add_executable(reflection_tool clang_reflection_tool.cpp)
set_target_properties(reflection_tool PROPERTIES CXX_STANDARD 20)
# FIXME Not clear why, but specified library parameters cause missing symbol
# errors in some of the protobuf libraries. Specifically missing is
# _ZN4absl12lts_2023012512log_internal10LogMessagelsImLi0EEERS2_RKT_, commonly
# googled as absl::lts_20230125 (yes, this is a common issue, but no working
# solution). ATTW the 'solved' responses indicate that it has something to do
# with new dependency on abseil library in the protobuf, but it did not work
# here.

# https://github.com/rui314/mold/issues/530#issuecomment-1870903572 -- mold
# ignores this option target_link_options(reflection_tool PRIVATE
# "-Wl,--copy-dt-needed-entries")

target_link_libraries(
  reflection_tool
  PRIVATE reflection_lib
          ${llvm_libs}
          clangBasic
          clangASTMatchers
          clangTooling
          absl_all
          protobuf::libprotobuf
          protobuf::libprotoc)

add_custom_command(
  TARGET reflection_tool
  POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E create_symlink "${CMAKE_BINARY_DIR}"
          "${BASE}/build/utils")

# Shared library can be loaded as clang plugin

# NOTE: Not linking any LVM libraries here as it will cause LLVM ERROR:
# inconsistency in registered CommandLine options due to duplicate symbols that
# are loaded in clang and then in shared library.
add_library(reflection_plugin SHARED clang_reflection_plugin.cpp)
set_target_properties(reflection_plugin PROPERTIES CXX_STANDARD 20)
target_link_libraries(reflection_plugin PRIVATE reflection_lib)

add_custom_command(
  TARGET reflection_plugin
  POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E create_symlink "${CMAKE_BINARY_DIR}"
          "${BASE}/build/utils")

add_custom_command(
  TARGET reflection_plugin
  POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E create_symlink "${PROTOBUF_BINARY}/protoc"
          "${BASE}/build/utils/protoc")
