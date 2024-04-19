cmake_minimum_required(VERSION 3.10)

project(ConvertConstRef)

# Specify the path to the LLVM toolchain
set(TOOLCHAIN "${BASE}/toolchain")
# Set the LLVM_DIR to the location of LLVMConfig.cmake
set(LLVM_DIR "${TOOLCHAIN}/llvm/lib/cmake/llvm")
set(Clang_DIR "${TOOLCHAIN}/llvm/lib/cmake/clang")

set(DEPS_DIR "${BASE}/thirdparty")
set(LLVM_LIB_DIR "${TOOLCHAIN}/llvm/lib")

# Find the LLVM package. This also defines a lot of variables, see:
# https://llvm.org/docs/CMake.html#embedding-llvm-in-your-project
find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

# LLVM libraries, quite surprisingly, cannot be linked with the LLVM standard library build, 
# mainly due to the `std::string` ABI issues for functions that use this class. So I need to
# revert to the baseline global state of the cmake flags here (which was necessary for abseil
# library). Also drop RTTI as the LLVM libs were compiled without it. 
set(CMAKE_EXE_LINKER_FLAGS_TMP "${CMAKE_EXE_LINKER_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS_BASE}")

set(CMAKE_CXX_FLAGS_TMP "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_EXE_LINKER_FLAGS_BASE} -fno-rtti")

add_subdirectory(profdata_merger)
add_subdirectory(reflection_tool)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_TMP}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS_TMP}")
