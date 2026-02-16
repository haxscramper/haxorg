cmake_minimum_required(VERSION 3.15)
project(conan_test_package_project CXX)

find_package(haxorg REQUIRED)

add_executable(conan_test_package main.cpp)
target_link_libraries(conan_test_package PUBLIC haxorg::haxorg)
