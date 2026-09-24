cmake_minimum_required(VERSION 3.28)
project(test_package LANGUAGES CXX)

find_package(hstd_cpp_diagram_lib CONFIG REQUIRED)

add_executable(test_package main.cpp)
target_compile_features(test_package PRIVATE cxx_std_23)
target_link_libraries(test_package PRIVATE hstd_cpp_diagram_lib::hstd_cpp_diagram_lib)
