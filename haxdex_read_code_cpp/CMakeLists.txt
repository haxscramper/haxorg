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

find_package(hstd_cpp_lib CONFIG REQUIRED)
find_package(SQLiteCpp CONFIG REQUIRED)
find_package(TBB CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)

# LLVM and Clang remain system/toolchain dependencies.
find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

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
        SQLiteCpp
        TBB::tbb
        LLVM
        clang-cpp
)

haxorg_add_protobuf(
    TARGET haxdex_read_code_cpp
    PROTO_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/proto/haxdex_read_code_cpp/reflection_defs.proto"
)
