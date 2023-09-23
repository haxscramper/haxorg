cmake_minimum_required(VERSION 3.10)

project(ConvertConstRef)

# Specify the path to the LLVM toolchain
set(TOOLCHAIN "${CMAKE_SOURCE_DIR}/../../toolchain")
set(LLVM_DIR "${TOOLCHAIN}/llvm/lib/cmake/llvm")
set(Clang_DIR "${TOOLCHAIN}/llvm/lib/cmake/clang")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")


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
llvm_map_components_to_libnames(llvm_libs support core irreader)

add_executable(convert_const_ref convert_const_ref.cpp)
target_link_libraries(
    convert_const_ref
    ${llvm_libs}
    clangBasic
    clangASTMatchers
    clangTooling # Add more Clang components as needed
)

find_package(Protobuf REQUIRED)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS reflection_defs.proto)
get_filename_component(PROTO_HDR_DIR ${PROTO_HDRS} DIRECTORY)


# Set the C++ standard
set_target_properties(convert_const_ref PROPERTIES CXX_STANDARD 20)


# NOTE: Not linking any LVM libraries here as it will cause
# LLVM ERROR: inconsistency in registered CommandLine options due
# to duplicate symbols that are loaded in clang and then in shared
# library.
add_library(reflection_plugin SHARED clang_reflection_plugin.cpp ${PROTO_SRCS} ${PROTO_HDRS})
set_target_properties(reflection_plugin PROPERTIES CXX_STANDARD 20)
target_link_libraries(reflection_plugin ${PROTOBUF_LIBRARIES})
target_include_directories(reflection_plugin PRIVATE ${PROTO_HDR_DIR})
target_precompile_headers(
    reflection_plugin
    PRIVATE
    <clang/AST/ASTConsumer.h>
    <clang/AST/RecursiveASTVisitor.h>
    <clang/Frontend/FrontendPluginRegistry.h>
    <clang/Frontend/CompilerInstance.h>
    <clang/Sema/Sema.h>
)

set(BASE "${CMAKE_SOURCE_DIR}")
add_custom_command(
    TARGET reflection_plugin POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${BASE}/lib"
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:reflection_plugin> "${BASE}/lib"
)
