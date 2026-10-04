cmake_minimum_required(VERSION 3.28)

project(hstd_cpp_text_layout_test_package LANGUAGES CXX)

find_package(hstd_cpp_text_layout CONFIG REQUIRED)

add_executable(hstd_cpp_text_layout_test_package test_package.cpp)

target_compile_features(hstd_cpp_text_layout_test_package PRIVATE cxx_std_23)

target_link_libraries(
    hstd_cpp_text_layout_test_package
    PRIVATE
        hstd::hstd_cpp_text_layout
)
