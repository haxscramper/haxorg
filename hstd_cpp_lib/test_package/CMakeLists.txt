cmake_minimum_required(VERSION 3.24)
project(hstd_cpp_lib_package_test LANGUAGES CXX)

find_package(hstd_cpp_lib CONFIG REQUIRED)

add_executable(hstd_cpp_lib_package_test hstd_test_package_main.cpp)

target_compile_features(hstd_cpp_lib_package_test PRIVATE cxx_std_20)

target_link_libraries(hstd_cpp_lib_package_test PRIVATE hstd::hstd_cpp_lib)
