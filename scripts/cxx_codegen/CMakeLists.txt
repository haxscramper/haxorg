cmake_minimum_required(VERSION 3.10)

project(ConvertConstRef)

set(BASE "${CMAKE_SOURCE_DIR}")
message(STATUS "BASE(cxx_codegen) = ${BASE}")
# Specify the path to the LLVM toolchain
set(TOOLCHAIN "${BASE}/toolchain")

# Find the LLVM package. This also defines a lot of variables, see:
# https://llvm.org/docs/CMake.html#embedding-llvm-in-your-project
find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

# Adding LLVM definitions and include directories
add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${CLANG_INCLUDE_DIRS})

add_subdirectory(reflection_tool)
add_subdirectory(profdata_merger)
