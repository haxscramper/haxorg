cmake_minimum_required(VERSION 3.10)

project(ConvertConstRef)

# Specify the path to the LLVM toolchain
set(LLVM_DIR "${CMAKE_SOURCE_DIR}/../../toolchain/llvm/lib/cmake/llvm")
set(Clang_DIR "${CMAKE_SOURCE_DIR}/../../toolchain/llvm/lib/cmake/clang")
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
add_executable(convert_const_ref convert_const_ref.cpp)

# Link against LLVM libraries
llvm_map_components_to_libnames(llvm_libs support core irreader)
target_link_libraries(
    convert_const_ref
    ${llvm_libs}
    clangBasic
    clangASTMatchers
    clangTooling # Add more Clang components as needed
)
message(INFO ${llvm_libs})

# Set the C++ standard
set_target_properties(convert_const_ref PROPERTIES CXX_STANDARD 20)
