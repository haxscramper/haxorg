cmake_minimum_required(VERSION 3.10)

project(ConvertConstRef)

set(BASE "${CMAKE_SOURCE_DIR}")
message(STATUS "BASE(cxx_codegen) = ${BASE}")
# Specify the path to the LLVM toolchain
set(TOOLCHAIN "${BASE}/toolchain")
# Set the LLVM_DIR to the location of LLVMConfig.cmake
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

add_subdirectory(profdata_merger)
add_subdirectory(reflection_tool)

add_executable(convert_const_ref convert_const_ref.cpp)
target_link_libraries(
  convert_const_ref ${llvm_libs} clangBasic clangASTMatchers clangTooling # Add more Clang
                                                                          # components as neede
)

set_target_properties(convert_const_ref PROPERTIES CXX_STANDARD 20)
