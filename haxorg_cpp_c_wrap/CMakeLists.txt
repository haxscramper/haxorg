cmake_minimum_required(VERSION 3.28)

project(
    haxorg_cpp_c_wrap
    VERSION 0.1.0
    LANGUAGES
        C
        CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

include(CTest)
enable_testing()

if(NOT TARGET hstd::hstd_cpp_lib)
    find_package(hstd_cpp_lib CONFIG REQUIRED)
endif()

if(NOT TARGET haxorg::haxorg_cpp_org_lib)
    find_package(haxorg_cpp_org_lib CONFIG REQUIRED)
endif()

haxorg_add_library(haxorg_cpp_c_wrap)

haxorg_glob_add_sources2(
    TARGET haxorg_cpp_c_wrap
    LS_REGEX "${CMAKE_CURRENT_SOURCE_DIR}/src/haxorg_cpp_c_wrap/.*"
    SEARCH_BASE "${CMAKE_CURRENT_SOURCE_DIR}"
    EXTENSIONS
        "hpp;cpp;c;h"
)

haxorg_set_target_output(haxorg_cpp_c_wrap)
haxorg_set_target_flags(haxorg_cpp_c_wrap)

target_link_libraries(haxorg_cpp_c_wrap PUBLIC haxorg::haxorg_cpp_org_lib)

target_include_directories(
    haxorg_cpp_c_wrap
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
)

add_library(haxorg::haxorg_cpp_c_wrap ALIAS haxorg_cpp_c_wrap)
