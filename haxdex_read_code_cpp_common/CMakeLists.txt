cmake_minimum_required(VERSION 3.28)

project(
    haxdex_read_code_cpp_common
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

find_package(Protobuf CONFIG REQUIRED QUIET)
find_package(LLVM REQUIRED CONFIG QUIET)

haxorg_add_library(haxdex_read_code_cpp_common)
add_library(haxdex::haxdex_read_code_cpp_common ALIAS haxdex_read_code_cpp_common)

haxorg_glob_add_sources2(
    TARGET haxdex_read_code_cpp_common
    LS_REGEX "${CMAKE_CURRENT_LIST_DIR}/src/haxdex_read_code_cpp_common/.*"
    SEARCH_BASE "${CMAKE_CURRENT_LIST_DIR}"
    RECURSE ON
)

target_include_directories(
    haxdex_read_code_cpp_common
    PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}/src"
        ${LLVM_INCLUDE_DIRS}
)

target_compile_definitions(haxdex_read_code_cpp_common PUBLIC ${LLVM_DEFINITIONS})

target_link_libraries(
    haxdex_read_code_cpp_common
    PUBLIC
        hstd::hstd_cpp_lib
        protobuf::libprotobuf
        LLVM
)

haxorg_add_protobuf(
    TARGET haxdex_read_code_cpp_common
    PROTO_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/proto/haxdex_read_code_cpp_common/reflection_defs.proto"
    PACKAGE_NAME "haxdex_read_code_cpp_common"
)
