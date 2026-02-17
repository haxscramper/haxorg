cmake_minimum_required(VERSION 3.15)
project(conan_test_package_project CXX)

find_package(haxorg REQUIRED)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(cpptrace CONFIG REQUIRED)
find_package(Immer CONFIG REQUIRED)
find_package(Lager CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS ALL)

add_executable(conan_test_package main.cpp)
target_link_libraries(conan_test_package PUBLIC haxorg::haxorg)

# target_link_libraries(conan_test_package PUBLIC nlohmann_json::nlohmann_json)
