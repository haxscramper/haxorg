cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

set(ADAPTAGRAMS_VERSION
    "0.0.20251029"
    CACHE STRING
    "Version of this adaptagrams package snapshot"
)

project(adaptagrams VERSION "${ADAPTAGRAMS_VERSION}" LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(ADAPTAGRAMS_SOURCE_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/upstream"
    CACHE PATH
    "Root of the upstream adaptagrams checkout"
)

get_filename_component(
    ADAPTAGRAMS_SOURCE_DIR
    "${ADAPTAGRAMS_SOURCE_DIR}"
    ABSOLUTE
    BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
)

set(COLA_DIR "${ADAPTAGRAMS_SOURCE_DIR}/cola")

if(NOT EXISTS "${COLA_DIR}/libcola/cola.h")
    message(
        FATAL_ERROR
        "ADAPTAGRAMS_SOURCE_DIR must point to the upstream adaptagrams "
        "repository root. Expected: ${COLA_DIR}/libcola/cola.h"
    )
endif()

# This wrapper deliberately builds static libraries only.
if(BUILD_SHARED_LIBS)
    message(FATAL_ERROR "This wrapper currently supports static libraries only.")
endif()

# Default to PIC, but respect a value supplied by Conan or the caller.
if(NOT DEFINED CMAKE_POSITION_INDEPENDENT_CODE)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

# Require relative installation directories so the exports stay relocatable.
foreach(_dir CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_LIBDIR CMAKE_INSTALL_BINDIR)
    if(IS_ABSOLUTE "${${_dir}}")
        message(FATAL_ERROR "${_dir} must be relative to CMAKE_INSTALL_PREFIX.")
    endif()
endforeach()

# Do not allow a previous Autotools configuration to override our generated
# configuration through a source-relative #include.
if(EXISTS "${COLA_DIR}/libcola/config.h")
    message(
        FATAL_ERROR
        "Found ${COLA_DIR}/libcola/config.h from another build. "
        "Use a clean checkout, or move that generated file out of the source "
        "tree before configuring this wrapper."
    )
endif()

set(ADAPTAGRAMS_GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
file(MAKE_DIRECTORY "${ADAPTAGRAMS_GENERATED_DIR}/libcola")

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cola_config.h.in"
    "${ADAPTAGRAMS_GENERATED_DIR}/libcola/config.h"
    @ONLY
)

function(add_adaptagrams_library name)
    file(GLOB _sources CONFIGURE_DEPENDS "${COLA_DIR}/lib${name}/*.cpp")

    add_library(${name} STATIC ${_sources})
    add_library(adaptagrams::${name} ALIAS ${name})

    target_compile_features(${name} PUBLIC cxx_std_11)

    # Keep filenames consistent with the Conan component metadata, including
    # when the caller has configured a global debug postfix.
    set_target_properties(
        ${name}
        PROPERTIES
            OUTPUT_NAME
                "${name}"
            DEBUG_POSTFIX
                ""
    )

    target_include_directories(
        ${name}
        PUBLIC
            "$<BUILD_INTERFACE:${ADAPTAGRAMS_GENERATED_DIR}>"
            "$<BUILD_INTERFACE:${COLA_DIR}>"
            "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
        PRIVATE
            "${ADAPTAGRAMS_GENERATED_DIR}/libcola"
    )

    target_compile_definitions(${name} PRIVATE HAVE_CONFIG_H)

    if(MSVC)
        target_compile_definitions(
            ${name}
            PRIVATE
                _USE_MATH_DEFINES
                _CRT_SECURE_NO_WARNINGS
        )
    endif()

    file(GLOB _headers CONFIGURE_DEPENDS "${COLA_DIR}/lib${name}/*.h")

    # Our generated configuration is installed separately.
    list(FILTER _headers EXCLUDE REGEX "/config\\.h$")

    install(FILES ${_headers} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/lib${name}")
endfunction()

add_adaptagrams_library(vpsc)
add_adaptagrams_library(avoid)
add_adaptagrams_library(cola)
add_adaptagrams_library(topology)
add_adaptagrams_library(dialect)

# Upstream libavoid otherwise uses dllimport declarations under MSVC.
# This must reach consumers as well as the library's own compilation.
target_compile_definitions(avoid PUBLIC LIBAVOID_NO_DLL)

# Static-library dependencies must propagate to the final executable.
target_link_libraries(cola PUBLIC vpsc)
target_link_libraries(
    topology
    PUBLIC
        avoid
        cola
        vpsc
)
target_link_libraries(
    dialect
    PUBLIC
        avoid
        cola
        vpsc
)

# Convenience target matching Conan's aggregate target.
add_library(adaptagrams INTERFACE)
add_library(adaptagrams::adaptagrams ALIAS adaptagrams)

target_link_libraries(
    adaptagrams
    INTERFACE
        dialect
        topology
        cola
        avoid
        vpsc
)

install(
    FILES
        "${ADAPTAGRAMS_GENERATED_DIR}/libcola/config.h"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/libcola"
)

install(
    TARGETS
        vpsc
        avoid
        cola
        topology
        dialect
        adaptagrams
    EXPORT adaptagrams_targets
    ARCHIVE
        DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    LIBRARY
        DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME
        DESTINATION "${CMAKE_INSTALL_BINDIR}"
)

set(ADAPTAGRAMS_CMAKE_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/adaptagrams")

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/adaptagrams-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/adaptagrams-config.cmake"
    INSTALL_DESTINATION "${ADAPTAGRAMS_CMAKE_INSTALL_DIR}"
)

# Snapshot versions do not imply compatibility with other snapshots.
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/adaptagrams-config-version.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY ExactVersion
)

install(
    EXPORT adaptagrams_targets
    FILE adaptagrams_targets.cmake
    NAMESPACE adaptagrams::
    DESTINATION "${ADAPTAGRAMS_CMAKE_INSTALL_DIR}"
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/adaptagrams-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/adaptagrams-config-version.cmake"
    DESTINATION "${ADAPTAGRAMS_CMAKE_INSTALL_DIR}"
)
