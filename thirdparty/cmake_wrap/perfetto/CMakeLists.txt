cmake_minimum_required(VERSION 3.5)
project(PerfettoLibrary)

# Assuming DEPS_DIR is set to this directory, adjust if necessary
set(DEPS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../")

# Add the library
add_library(perfetto STATIC "${DEPS_DIR}/perfetto/sdk/perfetto.cc")

# Include directories
target_include_directories(perfetto PUBLIC
    "$<BUILD_INTERFACE:${DEPS_DIR}/perfetto/sdk>"
    "$<INSTALL_INTERFACE:include>"
)

# Include helper for creating package configurations
include(CMakePackageConfigHelpers)

# Generate the config file that includes the exported targets
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/PerfettoConfig.cmake"
    INSTALL_DESTINATION lib/cmake/Perfetto
)

# Install the library
install(TARGETS perfetto
    EXPORT PerfettoTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

# Install the header files
install(DIRECTORY ${DEPS_DIR}/perfetto/sdk/
    DESTINATION include/perfetto
    FILES_MATCHING PATTERN "*.h"
)

# Export the targets to a script
install(EXPORT PerfettoTargets
    FILE PerfettoTargets.cmake
    NAMESPACE Perfetto::
    DESTINATION lib/cmake/Perfetto
)

# Install the generated config file
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/PerfettoConfig.cmake"
    DESTINATION lib/cmake/Perfetto
)
