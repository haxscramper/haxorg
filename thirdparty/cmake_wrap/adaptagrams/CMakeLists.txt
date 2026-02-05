cmake_minimum_required(VERSION 3.5)
project(AdaptagramsLibrary)

# Assuming DEPS_DIR is set to this directory, adjust if necessary
set(DEPS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../")
set(COLA_DIR "${DEPS_DIR}/adaptagrams/cola")

# Add the library

function(add_cola_library cola_name)
  file(GLOB _HEADERS "${COLA_DIR}/lib${cola_name}/*.h")
  file(GLOB _SOURCES "${COLA_DIR}/lib${cola_name}/*.cpp")
  add_library(${cola_name} STATIC ${_HEADERS} ${_SOURCES})
  target_compile_options(${cola_name} PRIVATE -w)
  target_include_directories(${cola_name} PUBLIC "$<BUILD_INTERFACE:${COLA_DIR}>"
                                                 "$<INSTALL_INTERFACE:include>")

  install(
    DIRECTORY "${COLA_DIR}/lib${cola_name}"
    DESTINATION "include/lib${cola_name}"
    FILES_MATCHING
    PATTERN "*.h")
endfunction()

add_cola_library(avoid)
add_cola_library(cola)
add_cola_library(dialect)
add_cola_library(topology)
add_cola_library(vpsc)

find_package(PkgConfig)
pkg_check_modules(CAIROMM REQUIRED cairomm-1.0)

target_link_libraries(cola PUBLIC ${CAIROMM_LIBRARIES})
target_include_directories(cola PUBLIC ${CAIROMM_INCLUDE_DIRS})

# Include helper for creating package configurations
include(CMakePackageConfigHelpers)

# Generate the config file that includes the exported targets
configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in "${CMAKE_CURRENT_BINARY_DIR}/AdaptagramsConfig.cmake"
  INSTALL_DESTINATION lib/cmake/Adaptagrams)

# Install the library
install(
  TARGETS cola avoid dialect topology vpsc
  EXPORT AdaptagramsTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES
  DESTINATION include)

# Export the targets to a script
install(
  EXPORT AdaptagramsTargets
  FILE AdaptagramsTargets.cmake
  NAMESPACE Adaptagrams::
  DESTINATION lib/cmake/Adaptagrams)

# Install the generated config file
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/AdaptagramsConfig.cmake"
        DESTINATION lib/cmake/Adaptagrams)
