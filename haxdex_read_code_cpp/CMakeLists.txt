cmake_minimum_required(VERSION 3.28)

project(
    haxdex_read_code_cpp
    VERSION 0.1.0
    LANGUAGES
        CXX
        C
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

if(NOT TARGET hstd::hstd_cpp_lib)
    find_package(hstd_cpp_lib CONFIG REQUIRED QUIET)
endif()

if(NOT TARGET haxdex::haxdex_read_code_cpp_common)
    find_package(haxdex_read_code_cpp_common CONFIG REQUIRED QUIET)
endif()

find_package(LLVM REQUIRED CONFIG QUIET)
find_package(Clang REQUIRED CONFIG QUIET)

haxorg_add_executable(haxdex_read_code_cpp)
add_executable(haxdex::haxdex_read_code_cpp ALIAS haxdex_read_code_cpp)

haxorg_glob_add_sources2(
    TARGET haxdex_read_code_cpp
    LS_REGEX "${CMAKE_CURRENT_LIST_DIR}/src/haxdex_read_code_cpp/.*"
    SEARCH_BASE "${CMAKE_CURRENT_LIST_DIR}"
    RECURSE ON
)

target_include_directories(
    haxdex_read_code_cpp
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/src"
        ${LLVM_INCLUDE_DIRS}
        ${CLANG_INCLUDE_DIRS}
)

target_compile_definitions(haxdex_read_code_cpp PRIVATE ${LLVM_DEFINITIONS})

target_link_libraries(
    haxdex_read_code_cpp
    PRIVATE
        hstd::hstd_cpp_lib
        haxdex::haxdex_read_code_cpp_common
        LLVM
        clang-cpp
)
