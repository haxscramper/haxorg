cmake_minimum_required(VERSION 3.15)
project(conan_test_package_project CXX)

find_package(haxorg REQUIRED)

find_library(GRAPHVIZ_CGRAPH_LIBRARY cgraph)
find_library(GRAPHVIZ_GVC_LIBRARY gvc)

add_executable(conan_test_package main.cpp)

target_link_libraries(conan_test_package PUBLIC ${GRAPHVIZ_CGRAPH_LIBRARY} ${GRAPHVIZ_GVC_LIBRARY})
target_link_libraries(conan_test_package PUBLIC haxorg::haxorg)
