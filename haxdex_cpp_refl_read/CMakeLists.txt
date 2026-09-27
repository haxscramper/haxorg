cmake_minimum_required(VERSION 3.28)

project(
    haxdex_cpp_refl_read
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

haxorg_add_executable(haxdex_cpp_refl_read)
add_executable(haxdex::haxdex_cpp_refl_read ALIAS haxdex_cpp_refl_read)

haxorg_glob_add_sources2(
    TARGET haxdex_cpp_refl_read
    LS_REGEX "${CMAKE_CURRENT_LIST_DIR}/src/haxdex_cpp_refl_read/.*"
    SEARCH_BASE "${CMAKE_CURRENT_LIST_DIR}"
    RECURSE ON
)

target_include_directories(
    haxdex_cpp_refl_read
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/src"
        ${LLVM_INCLUDE_DIRS}
        ${CLANG_INCLUDE_DIRS}
)

target_compile_definitions(haxdex_cpp_refl_read PRIVATE ${LLVM_DEFINITIONS})

target_link_libraries(
    haxdex_cpp_refl_read
    PRIVATE
        hstd::hstd_cpp_lib
        SQLiteCpp
        TBB::tbb
        LLVM
        clang-cpp
)

haxorg_add_protobuf(
    TARGET haxdex_cpp_refl_read
    PROTO_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/proto/haxdex_cpp_refl_read/reflection_defs.proto"
)
