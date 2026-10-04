cmake_minimum_required(VERSION 3.28)

project(ex_cpp_library VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(ex_cpp_library STATIC src/ex_cpp_library/value.cpp)
add_library(ex::ex_cpp_library ALIAS ex_cpp_library)

target_include_directories(ex_cpp_library PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

enable_testing()

if(BUILD_TESTING)
    add_executable(test_ex_cpp_library tests/test_value.cpp)
    target_link_libraries(test_ex_cpp_library PRIVATE ex_cpp_library)
    add_test(NAME ex_cpp_library_value COMMAND test_ex_cpp_library)
endif()
