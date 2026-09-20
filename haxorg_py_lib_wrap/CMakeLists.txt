cmake_minimum_required(VERSION 3.28)

project(haxorg_py_lib_wrap VERSION 0.1.0 LANGUAGES CXX)

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
find_package(hstd CONFIG REQUIRED)
find_package(HaxorgCppOrgLib CONFIG REQUIRED)

set(BASE "${CMAKE_CURRENT_SOURCE_DIR}")

nanobind_add_module(
    haxorg_py_haxorg
    "${BASE}/src/pyhaxorg/pyhaxorg.cpp"
    "${BASE}/src/py_type_casters.hpp"
    "${BASE}/src/py_type_casters.cpp"
    "${BASE}/src/pyhaxorg/pyhaxorg_manual_impl.cpp"
    "${BASE}/src/pyhaxorg/pyhaxorg_manual_refl.cpp"
    "${BASE}/src/pyhaxorg/pyhaxorg_manual_impl.hpp"
)

haxorg_set_target_output(haxorg_py_haxorg)
haxorg_set_target_flags(haxorg_py_haxorg)

set_target_properties(
    haxorg_py_haxorg
    PROPERTIES
        OUTPUT_NAME
            "pyhaxorg"
)

target_include_directories(haxorg_py_haxorg PRIVATE "${BASE}/src")

target_link_libraries(haxorg_py_haxorg PRIVATE haxorg::haxorg_cpp_lib)

add_library(haxorg::haxorg_py_haxorg ALIAS haxorg_py_haxorg)

install(
    TARGETS
        haxorg_py_haxorg
    EXPORT HaxorgPyHaxorgTargets
    LIBRARY
        DESTINATION "."
    RUNTIME
        DESTINATION "."
)

install(
    EXPORT HaxorgPyHaxorgTargets
    FILE HaxorgPyHaxorgTargets.cmake
    NAMESPACE haxorg::
    DESTINATION lib/cmake/HaxorgPyHaxorg
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/HaxorgPyHaxorgConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/HaxorgPyHaxorgConfig.cmake"
    INSTALL_DESTINATION lib/cmake/HaxorgPyHaxorg
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/HaxorgPyHaxorgConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/HaxorgPyHaxorgConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/HaxorgPyHaxorgConfigVersion.cmake"
    DESTINATION lib/cmake/HaxorgPyHaxorg
)
