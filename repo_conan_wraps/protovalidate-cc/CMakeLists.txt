cmake_minimum_required(VERSION 3.24)
project(protovalidate_cc_wrap)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(FetchContent)

set(PROTOVALIDATE_CC_ENABLE_VENDORING OFF)
set(PROTOVALIDATE_CC_ENABLE_INSTALL OFF)
set(PROTOVALIDATE_CC_ENABLE_TESTS OFF)
set(PROTOVALIDATE_CC_ENABLE_CONFORMANCE OFF)

set(PROTOVALIDATE_CC_UPSTREAM_DIR "${CMAKE_CURRENT_SOURCE_DIR}/_source")
set(PROTOVALIDATE_CC_SCHEMA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/_schema")
set(PROTOVALIDATE_CC_CONFIG_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/protovalidate_cc")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory("${PROTOVALIDATE_CC_UPSTREAM_DIR}")

foreach(
    var
    IN
    ITEMS
        PROTOVALIDATE_CC_EXPORT_TARGETS
        PROTOVALIDATE_CC_FIND_DEPENDENCIES
        PROTOVALIDATE_PROTO_GEN_DIR
)
    get_directory_property(
        ${var}
        DIRECTORY "${PROTOVALIDATE_CC_UPSTREAM_DIR}"
        DEFINITION ${var}
    )
endforeach()

FetchContent_GetProperties(cel_cpp)

# Upstream exposes a raw build-tree include path, which install(EXPORT) rejects.
get_target_property(_cel_spec_includes cel_cpp_spec_proto INTERFACE_INCLUDE_DIRECTORIES)

foreach(include_dir IN LISTS _cel_spec_includes)
    install(
        DIRECTORY
            "${include_dir}/"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING
        PATTERN "*.h"
    )
endforeach()

list(TRANSFORM _cel_spec_includes PREPEND "$<BUILD_INTERFACE:")
list(TRANSFORM _cel_spec_includes APPEND ">")
set_target_properties(
    cel_cpp_spec_proto
    PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES
            "${_cel_spec_includes};$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

set(PROTOVALIDATE_CC_TARGETS
    protovalidate_cc
    ${PROTOVALIDATE_CC_EXPORT_TARGETS}
    cel_cpp_empty_descriptor_set
    cel_cpp_spec_proto
)

install(
    TARGETS
        ${PROTOVALIDATE_CC_TARGETS}
    EXPORT protovalidate_cc-targets
    ARCHIVE
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME
        DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT protovalidate_cc-targets
    NAMESPACE protovalidate_cc::
    FILE protovalidate_cc-targets.cmake
    DESTINATION "${PROTOVALIDATE_CC_CONFIG_DIR}"
)

export(
    EXPORT protovalidate_cc-targets
    NAMESPACE protovalidate_cc::
    FILE "${CMAKE_CURRENT_BINARY_DIR}/protovalidate_cc-targets.cmake"
)

foreach(
    header_dir
    IN
    ITEMS
        "${PROTOVALIDATE_CC_UPSTREAM_DIR}/buf"
        "${PROTOVALIDATE_PROTO_GEN_DIR}/buf"
        "${cel_cpp_SOURCE_DIR}/"
)
    install(
        DIRECTORY
            "${header_dir}"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING
        PATTERN "*.h"
    )
endforeach()

install(
    DIRECTORY
        "${PROTOVALIDATE_CC_SCHEMA_DIR}/"
    DESTINATION res/proto
    FILES_MATCHING
    PATTERN "*.proto"
)

list(JOIN PROTOVALIDATE_CC_FIND_DEPENDENCIES "\n" PROTOVALIDATE_CC_FIND_DEPENDENCIES_STR)

# Build-tree config, used by editable/workspace consumers
set(PROTOVALIDATE_CC_CONFIG_PROTO_IMPORT_DIR "${PROTOVALIDATE_CC_SCHEMA_DIR}")
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/protovalidate_cc-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/protovalidate_cc-config.cmake"
    @ONLY
)

# Install-tree config
set(PROTOVALIDATE_CC_CONFIG_PROTO_IMPORT_DIR
    "\${CMAKE_CURRENT_LIST_DIR}/../../../res/proto"
)
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/protovalidate_cc-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/install-config/protovalidate_cc-config.cmake"
    @ONLY
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/protovalidate_cc-config-version.cmake"
    VERSION "${PROTOVALIDATE_CC_VERSION}"
    COMPATIBILITY AnyNewerVersion
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/install-config/protovalidate_cc-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/protovalidate_cc-config-version.cmake"
    DESTINATION "${PROTOVALIDATE_CC_CONFIG_DIR}"
)
