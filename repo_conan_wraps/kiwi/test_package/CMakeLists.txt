cmake_minimum_required(VERSION 3.15)
project(kiwi_package_test LANGUAGES CXX)

find_package(kiwi CONFIG REQUIRED)

add_executable(kiwi_package_test test.cpp)
target_link_libraries(kiwi_package_test PRIVATE kiwi::kiwi)
