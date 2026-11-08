cmake_minimum_required(VERSION 3.25)
project(hstd_cpp_souffle_serde LANGUAGES CXX)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(OpenMP REQUIRED COMPONENTS CXX)
find_program(SOUFFLE_EXECUTABLE souffle REQUIRED)
find_path(SOUFFLE_INCLUDE_DIR souffle/SouffleFunctor.h REQUIRED)

execute_process(
    COMMAND
        "${SOUFFLE_EXECUTABLE}" --version
    OUTPUT_VARIABLE SOUFFLE_VERSION
    COMMAND_ERROR_IS_FATAL ANY
)
string(
    REGEX MATCH "Word size: (32|64) bits"
    DOMAIN_MATCH
    "${SOUFFLE_VERSION}"
)
if(NOT DOMAIN_MATCH)
    message(
        FATAL_ERROR
        "Cannot determine Souffle RAM domain width from: ${SOUFFLE_VERSION}"
    )
endif()
set(SOUFFLE_DOMAIN_SIZE "${CMAKE_MATCH_1}")
if(NOT SOUFFLE_VERSION MATCHES "Options enabled:[^\n]*sqlite")
    message(FATAL_ERROR "The installed Souffle must be built with SQLite support")
endif()
if(NOT SOUFFLE_VERSION MATCHES "Options enabled:[^\n]*ffi")
    message(
        FATAL_ERROR
        "The installed Souffle interpreter must be built with libffi support"
    )
endif()

add_library(hstd_cpp_souffle_serde SHARED src/hstd_cpp_souffle_serde/serde.cpp)
target_compile_features(hstd_cpp_souffle_serde PRIVATE cxx_std_23)
set_target_properties(
    hstd_cpp_souffle_serde
    PROPERTIES
        CXX_EXTENSIONS
            OFF
        RUNTIME_OUTPUT_DIRECTORY
            "${CMAKE_BINARY_DIR}/bin"
        LIBRARY_OUTPUT_DIRECTORY
            "${CMAKE_BINARY_DIR}/lib"
        ARCHIVE_OUTPUT_DIRECTORY
            "${CMAKE_BINARY_DIR}/lib"
)

target_compile_definitions(
    hstd_cpp_souffle_serde
    PRIVATE
        RAM_DOMAIN_SIZE=${SOUFFLE_DOMAIN_SIZE}
)
target_include_directories(hstd_cpp_souffle_serde PRIVATE "${SOUFFLE_INCLUDE_DIR}")
target_link_libraries(
    hstd_cpp_souffle_serde
    PRIVATE
        nlohmann_json::nlohmann_json
        fmt::fmt
        OpenMP::OpenMP_CXX
)
