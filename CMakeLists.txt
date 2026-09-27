cmake_minimum_required(VERSION 3.28)
project(
    haxorg_workspace
    LANGUAGES
        C
        CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)

# Required by projects that import hstd_cpp_lib's .proto files.
set(hstd_cpp_lib_PROTO_IMPORT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/hstd_cpp_lib/proto")

# Diagram and org protobuf sources depend on hstd's protobuf support.
set(HSTD_CPP_BUILD_WITH_PROTOBUF ON CACHE BOOL "Build hstd protobuf support")

add_subdirectory(hstd_cpp_lib)
add_subdirectory(hstd_cpp_text_layout)
add_subdirectory(hstd_cpp_diagram_lib)
add_subdirectory(haxorg_cpp_org_lib)
add_subdirectory(haxorg_cpp_org_cli)
add_subdirectory(haxorg_cpp_c_wrap)
add_subdirectory(haxdex_cpp_refl_read)

add_subdirectory(hstd_py_text_layout)
add_subdirectory(haxorg_cpp_py_wrap)
