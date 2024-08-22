cmake_minimum_required(VERSION 3.5...3.16)
project(DescribeWrapper)

# Path to the original boost_describe CMake project
set(BOOST_DESCRIBE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../describe")

# Add the subdirectory containing the boost_describe CMakeLists.txt
add_subdirectory("${BOOST_DESCRIBE_DIR}"
                 "${CMAKE_CURRENT_BINARY_DIR}/boost_describe")

# Include helper for creating package configurations
include(CMakePackageConfigHelpers)

# Create the package config file
configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/BoostDescribeConfig.cmake"
  INSTALL_DESTINATION lib/cmake/BoostDescribe)

# Install the library target
install(
  TARGETS boost_describe
  EXPORT BoostDescribeTargets
  INCLUDES
  DESTINATION include)

# Install the headers from boost_describe
install(DIRECTORY ${BOOST_DESCRIBE_DIR}/include/ DESTINATION include)

# Export the targets
install(
  EXPORT BoostDescribeTargets
  FILE BoostDescribeTargets.cmake
  NAMESPACE Boost::
  DESTINATION lib/cmake/BoostDescribe)

# Install the generated package config file
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/BoostDescribeConfig.cmake"
        DESTINATION lib/cmake/BoostDescribe)
