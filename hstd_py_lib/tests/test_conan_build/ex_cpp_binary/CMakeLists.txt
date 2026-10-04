cmake_minimum_required(VERSION 3.28)

project(ex_cpp_binary VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

find_package(ex_cpp_library CONFIG REQUIRED)

add_executable(ex_cpp_binary src/ex_cpp_binary/main.cpp)
target_link_libraries(ex_cpp_binary PRIVATE ex::ex_cpp_library)

enable_testing()

if(BUILD_TESTING)
    add_executable(test_ex_cpp_binary tests/test_binary.cpp)
    target_link_libraries(test_ex_cpp_binary PRIVATE ex::ex_cpp_library)

    add_test(
        NAME ex_cpp_binary_behavior
        COMMAND
            test_ex_cpp_binary "$<TARGET_FILE:ex_cpp_binary>"
    )
endif()
