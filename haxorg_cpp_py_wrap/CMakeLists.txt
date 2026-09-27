cmake_minimum_required(VERSION 3.28)

project(haxorg_cpp_py_wrap VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(CMakePackageConfigHelpers)

find_package(
    Python
    COMPONENTS
        Interpreter
        Development.Module
    REQUIRED
)

find_package(nanobind CONFIG REQUIRED)
if(NOT TARGET hstd::hstd_cpp_lib)
    find_package(hstd_cpp_lib CONFIG REQUIRED)
endif()

if(NOT TARGET haxorg::haxorg_cpp_org_lib)
    find_package(haxorg_cpp_org_lib CONFIG REQUIRED)
endif()

nanobind_add_module(
    haxorg_py_haxorg
    "${CMAKE_CURRENT_SOURCE_DIR}/src/pyhaxorg/pyhaxorg.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/py_type_casters.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/py_type_casters.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/pyhaxorg/pyhaxorg_manual_impl.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/pyhaxorg/pyhaxorg_manual_refl.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/pyhaxorg/pyhaxorg_manual_impl.hpp"
)

haxorg_set_target_output(haxorg_py_haxorg)
haxorg_set_target_flags(haxorg_py_haxorg)

set_target_properties(
    haxorg_py_haxorg
    PROPERTIES
        OUTPUT_NAME
            "pyhaxorg"
)

target_include_directories(haxorg_py_haxorg PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(haxorg_py_haxorg PRIVATE haxorg::haxorg_cpp_lib)

add_library(haxorg::haxorg_py_haxorg ALIAS haxorg_py_haxorg)

install(
    TARGETS
        haxorg_py_haxorg
    EXPORT haxorg_py_haxorg_targets
    LIBRARY
        DESTINATION "."
    RUNTIME
        DESTINATION "."
)

install(
    EXPORT haxorg_py_haxorg_targets
    FILE haxorg_py_haxorg_targets.cmake
    NAMESPACE haxorg::
    DESTINATION lib/cmake/haxorg_py_haxorg
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/haxorg_py_haxorg_config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/haxorg_py_haxorg_config.cmake"
    INSTALL_DESTINATION lib/cmake/haxorg_py_haxorg
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/haxorg_py_haxorg_config_version.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/haxorg_py_haxorg_config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/haxorg_py_haxorg_config_version.cmake"
    DESTINATION lib/cmake/haxorg_py_haxorg
)
