cmake_minimum_required(VERSION 3.28)

project(ex_cpp_library_test_package LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

find_package(ex_cpp_library CONFIG REQUIRED)

add_executable(test_library src/main.cpp)
target_link_libraries(test_library PRIVATE ex::ex_cpp_library)
