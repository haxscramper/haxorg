cmake_minimum_required(VERSION 3.28)

project(haxdex_cpp_refl_read VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CMakePackageConfigHelpers)

find_package(hstd CONFIG REQUIRED)
find_package(protobuf CONFIG REQUIRED)
find_package(SQLiteCpp CONFIG REQUIRED)
find_package(TBB CONFIG REQUIRED)

# LLVM and Clang remain system/toolchain dependencies.
find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

set(BASE "${CMAKE_CURRENT_SOURCE_DIR}")
set(REFL_PROTOC_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")

file(MAKE_DIRECTORY "${REFL_PROTOC_OUT_DIR}")

protobuf_generate(
    LANGUAGE cpp
    OUT_VAR HAXDEX_PROTO_GENERATED_FILES
    PROTOS
        "${BASE}/src/reflection_defs.proto"
    PROTOC_OUT_DIR "${REFL_PROTOC_OUT_DIR}"
)

add_executable(haxdex_cpp_refl_read ${HAXDEX_PROTO_GENERATED_FILES})

haxorg_glob_add_sources2(
    TARGET haxdex_cpp_refl_read
    LS_REGEX "${BASE}/src/.*"
    SEARCH_BASE "${BASE}"
)

haxorg_set_target_output(haxdex_cpp_refl_read)
haxorg_set_target_flags(haxdex_cpp_refl_read)

target_include_directories(
    haxdex_cpp_refl_read
    PRIVATE
        "${BASE}/src"
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
        protobuf::libprotobuf
        protobuf::libprotoc
)

add_executable(haxdex::haxdex_cpp_refl_read ALIAS haxdex_cpp_refl_read)

install(
    TARGETS
        haxdex_cpp_refl_read
    EXPORT HaxdexCppReflReadTargets
    RUNTIME
        DESTINATION bin
)

install(
    EXPORT HaxdexCppReflReadTargets
    FILE HaxdexCppReflReadTargets.cmake
    NAMESPACE haxdex::
    DESTINATION lib/cmake/HaxdexCppReflRead
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/HaxdexCppReflReadConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/HaxdexCppReflReadConfig.cmake"
    INSTALL_DESTINATION lib/cmake/HaxdexCppReflRead
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/HaxdexCppReflReadConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/HaxdexCppReflReadConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/HaxdexCppReflReadConfigVersion.cmake"
    DESTINATION lib/cmake/HaxdexCppReflRead
)
