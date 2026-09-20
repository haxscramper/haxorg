cmake_minimum_required(VERSION 3.28)

project(
    haxorg_c_lib_wrap
    VERSION 0.1.0
    LANGUAGES
        C
        CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(CTest)
include(CMakePackageConfigHelpers)

find_package(hstd CONFIG REQUIRED)
find_package(HaxorgCppOrgLib CONFIG REQUIRED)

set(BASE "${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(src)

install(DIRECTORY src/ DESTINATION include FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")

install(
    EXPORT HaxorgCHaxorgTargets
    FILE HaxorgCHaxorgTargets.cmake
    NAMESPACE haxorg::
    DESTINATION lib/cmake/HaxorgCHaxorg
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/HaxorgCHaxorgConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/HaxorgCHaxorgConfig.cmake"
    INSTALL_DESTINATION lib/cmake/HaxorgCHaxorg
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/HaxorgCHaxorgConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/HaxorgCHaxorgConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/HaxorgCHaxorgConfigVersion.cmake"
    DESTINATION lib/cmake/HaxorgCHaxorg
)
