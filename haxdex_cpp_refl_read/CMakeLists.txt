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

include(CMakePackageConfigHelpers)

find_package(hstd_cpp_lib CONFIG REQUIRED)
find_package(SQLiteCpp CONFIG REQUIRED)
find_package(TBB CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)

# LLVM and Clang remain system/toolchain dependencies.
find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

add_executable(haxdex_cpp_refl_read ${HAXDEX_PROTO_GENERATED_FILES})

haxorg_glob_add_sources2(
    TARGET haxdex_cpp_refl_read
    LS_REGEX "${CMAKE_CURRENT_SOURCE_DIR}/src/.*"
    SEARCH_BASE "${CMAKE_CURRENT_SOURCE_DIR}"
)

haxorg_set_target_output(haxdex_cpp_refl_read)
haxorg_set_target_flags(haxdex_cpp_refl_read)

target_include_directories(
    haxdex_cpp_refl_read
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        "${REFL_PROTOC_OUT_DIR}"
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
    UNIQUE_TARGET haxdex_cpp_refl_read_proto
    IMPORT_DIRS
        "${CMAKE_CURRENT_LIST_DIR}/proto"
    PROTO_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/proto/haxdex_cpp_refl_read/reflection_defs.proto"
)

add_executable(haxdex::haxdex_cpp_refl_read ALIAS haxdex_cpp_refl_read)

install(
    TARGETS
        haxdex_cpp_refl_read
    EXPORT haxdex_cpp_refl_read_targets
    RUNTIME
        DESTINATION bin
)

set(HAXDEX_CMAKE_INSTALL_DIR "lib/cmake/haxdex-cpp-refl-read")

install(
    EXPORT haxdex_cpp_refl_read_targets
    FILE haxdex-cpp-refl-read-targets.cmake
    NAMESPACE haxdex::
    DESTINATION "${HAXDEX_CMAKE_INSTALL_DIR}"
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/haxdex_cpp_refl_read_config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/haxdex-cpp-refl-read-config.cmake"
    INSTALL_DESTINATION "${HAXDEX_CMAKE_INSTALL_DIR}"
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/haxdex-cpp-refl-read-config-version.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/haxdex-cpp-refl-read-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/haxdex-cpp-refl-read-config-version.cmake"
    DESTINATION "${HAXDEX_CMAKE_INSTALL_DIR}"
)
