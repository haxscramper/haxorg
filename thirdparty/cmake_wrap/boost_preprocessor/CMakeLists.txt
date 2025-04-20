cmake_minimum_required(VERSION 3.5...3.16)
project(PreprocessorWrapper)

# Path to the original boost_preprocessor CMake project
set(BOOST_PREPROCESSOR_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../preprocessor")

# Add the subdirectory containing the boost_preprocessor CMakeLists.txt
add_subdirectory("${BOOST_PREPROCESSOR_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/boost_preprocessor")

# Include helper for creating package configurations
include(CMakePackageConfigHelpers)

# Create the package config file
configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/BoostPreprocessorConfig.cmake"
  INSTALL_DESTINATION lib/cmake/BoostPreprocessor)

# Install the library target
install(
  TARGETS boost_preprocessor
  EXPORT BoostPreprocessorTargets
  INCLUDES
  DESTINATION include)

# Install the headers from boost_preprocessor
install(DIRECTORY ${BOOST_PREPROCESSOR_DIR}/include/ DESTINATION include)

# Export the targets
install(
  EXPORT BoostPreprocessorTargets
  FILE BoostPreprocessorTargets.cmake
  NAMESPACE Boost::
  DESTINATION lib/cmake/BoostPreprocessor)

# Install the generated package config file
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/BoostPreprocessorConfig.cmake"
        DESTINATION lib/cmake/BoostPreprocessor)
