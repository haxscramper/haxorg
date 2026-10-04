cmake_minimum_required(VERSION 3.15)
project(test_package LANGUAGES C)

find_package(graphviz REQUIRED CONFIG)

add_executable(test_package test_package.c)
target_link_libraries(
    test_package
    PRIVATE
        graphviz::cgraph
        graphviz::gvc
)
set_target_properties(
    test_package
    PROPERTIES
        C_STANDARD
            99
)
