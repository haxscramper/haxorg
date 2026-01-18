cmake_minimum_required(VERSION 3.16)

find_package(Java 17 REQUIRED COMPONENTS Runtime Development)
find_package(JNI REQUIRED)

# Print Java information for debugging
message(STATUS "Java version: ${Java_VERSION}")
message(STATUS "Java executable: ${Java_JAVA_EXECUTABLE}")
message(STATUS "Java compiler: ${Java_JAVAC_EXECUTABLE}")
message(STATUS "JNI include dirs: ${JNI_INCLUDE_DIRS}")
message(STATUS "JNI libraries: ${JNI_LIBRARIES}")

# Ensure we have Java 17 or later
if(Java_VERSION VERSION_LESS "17")
  message(FATAL_ERROR "Java 17 or later is required. Found version: ${Java_VERSION}")
endif()

# Set JAVA_HOME environment variable for Gradle
get_filename_component(JAVA_HOME "${Java_JAVA_EXECUTABLE}" DIRECTORY)
get_filename_component(JAVA_HOME "${JAVA_HOME}" DIRECTORY)
message(STATUS "Setting JAVA_HOME to: ${JAVA_HOME}")

# Find system Gradle for wrapper generation
find_program(SYSTEM_GRADLE_COMMAND gradle)
if(NOT SYSTEM_GRADLE_COMMAND)
  message(FATAL_ERROR "System gradle not found. Please install gradle to generate wrapper.")
endif()

set(GRADLE_WRAPPER "${CMAKE_CURRENT_SOURCE_DIR}/gradlew")
set(GRADLE_WRAPPER_JAR "${CMAKE_CURRENT_SOURCE_DIR}/gradle/wrapper/gradle-wrapper.jar")
set(GRADLE_WRAPPER_PROPERTIES
    "${CMAKE_CURRENT_SOURCE_DIR}/gradle/wrapper/gradle-wrapper.properties")

# Define Gradle build directory in CMake binary directory
set(GRADLE_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/gradle-build")
set(JAR_OUTPUT_PATH "${GRADLE_BUILD_DIR}/libs/elk-wrapper.jar")

# Generate Gradle wrapper if it doesn't exist
add_custom_command(
  OUTPUT ${GRADLE_WRAPPER} ${GRADLE_WRAPPER_JAR} ${GRADLE_WRAPPER_PROPERTIES}
  COMMAND ${CMAKE_COMMAND} -E env "JAVA_HOME=${JAVA_HOME}" "PATH=${JAVA_HOME}/bin:$ENV{PATH}"
          ${SYSTEM_GRADLE_COMMAND} wrapper --gradle-version 8.5
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/build.gradle
  COMMENT "Generating Gradle wrapper"
  VERBATIM)

add_custom_target(gradle_wrapper DEPENDS ${GRADLE_WRAPPER} ${GRADLE_WRAPPER_JAR}
                                         ${GRADLE_WRAPPER_PROPERTIES})

# Build the JAR file using Gradle wrapper with custom build directory
add_custom_command(
  OUTPUT ${JAR_OUTPUT_PATH}
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/lib
  COMMAND
    ${CMAKE_COMMAND} -E env "JAVA_HOME=${JAVA_HOME}" "PATH=${JAVA_HOME}/bin:$ENV{PATH}"
    ${GRADLE_WRAPPER} --info clean build -PbuildDir=${GRADLE_BUILD_DIR}
    --project-dir=${CMAKE_CURRENT_SOURCE_DIR}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  DEPENDS gradle_wrapper ${CMAKE_CURRENT_SOURCE_DIR}/build.gradle
          ${CMAKE_CURRENT_SOURCE_DIR}/src/main/java/com/example/elk/ElkLayoutWrapper.java
  COMMENT
    "Building ELK wrapper JAR with Gradle wrapper and Java ${Java_VERSION} in ${GRADLE_BUILD_DIR}"
  VERBATIM)

add_custom_target(elk_jar ALL DEPENDS ${JAR_OUTPUT_PATH})

# Create the JNI wrapper library
add_library(jni_elk_lib STATIC src/elk_jni_wrapper.cpp include/elk_jni_wrapper.hpp)
set_target_flags(jni_elk_lib)

target_include_directories(jni_elk_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
                                              ${JNI_INCLUDE_DIRS})

target_compile_definitions(
  jni_elk_lib PUBLIC JNI_ELK_LIB_JAR_PATH="${CMAKE_CURRENT_BINARY_DIR}/lib/elk-wrapper.jar")

target_link_libraries(jni_elk_lib PUBLIC ${JNI_LIBRARIES})
message(STATUS "JNI_LIBRARIES = ${JNI_LIBRARIES}")

set(JVM_LIB_DIRS "")
foreach(lib ${JNI_LIBRARIES})
  get_filename_component(lib_dir "${lib}" DIRECTORY)
  list(APPEND JVM_LIB_DIRS "${lib_dir}")
endforeach()

list(REMOVE_DUPLICATES JVM_LIB_DIRS)

string(REPLACE ";" ":" JVM_RPATH "${JVM_LIB_DIRS}")

set_target_properties(jni_elk_lib PROPERTIES INSTALL_RPATH "${JVM_RPATH}" BUILD_WITH_INSTALL_RPATH
                                                                          TRUE)

foreach(lib_dir ${JVM_LIB_DIRS})
  message(STATUS "JNI ELK LIB RPATH: ${lib_dir}")
  target_link_options(jni_elk_lib PUBLIC "LINKER:-rpath,${lib_dir}")
endforeach()

# Add compiler definitions for JNI version compatibility
target_compile_definitions(jni_elk_lib PRIVATE JNI_VERSION_1_8=0x00010008 JNI_VERSION_9=0x00090000
                                               JNI_VERSION_10=0x000a0000)

add_dependencies(jni_elk_lib elk_jar)

# Copy JAR to binary directory for runtime
add_custom_command(
  TARGET jni_elk_lib
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:jni_elk_lib>/lib
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${JAR_OUTPUT_PATH}
          ${CMAKE_CURRENT_BINARY_DIR}/lib/elk-wrapper.jar
  COMMENT "Copying JAR to runtime directory")

# Debug targets
add_custom_target(
  debug_java
  COMMAND ${CMAKE_COMMAND} -E echo "=== Java Environment Debug ==="
  COMMAND ${CMAKE_COMMAND} -E echo "JAVA_HOME: ${JAVA_HOME}"
  COMMAND ${CMAKE_COMMAND} -E echo "Java executable: ${Java_JAVA_EXECUTABLE}"
  COMMAND ${CMAKE_COMMAND} -E echo "Java version: ${Java_VERSION}"
  COMMAND ${CMAKE_COMMAND} -E echo "JNI include dirs: ${JNI_INCLUDE_DIRS}"
  COMMAND ${CMAKE_COMMAND} -E echo "System Gradle: ${SYSTEM_GRADLE_COMMAND}"
  COMMAND ${CMAKE_COMMAND} -E echo "Gradle wrapper: ${GRADLE_WRAPPER}"
  COMMAND ${CMAKE_COMMAND} -E echo "Gradle build dir: ${GRADLE_BUILD_DIR}"
  COMMAND ${CMAKE_COMMAND} -E echo "=== Available Java versions ==="
  COMMAND bash -c "update-alternatives --list java 2>/dev/null || echo 'No alternatives found'"
  COMMAND ${CMAKE_COMMAND} -E echo "=== Current Java version ==="
  COMMAND ${Java_JAVA_EXECUTABLE} -version
  VERBATIM)

add_custom_target(
  debug_gradle
  COMMAND ${CMAKE_COMMAND} -E echo "=== Gradle Environment Debug ==="
  COMMAND ${CMAKE_COMMAND} -E echo "System Gradle: ${SYSTEM_GRADLE_COMMAND}"
  COMMAND ${CMAKE_COMMAND} -E echo "Gradle build dir: ${GRADLE_BUILD_DIR}"
  COMMAND ${CMAKE_COMMAND} -E echo "JAR output path: ${JAR_OUTPUT_PATH}"
  COMMAND ${CMAKE_COMMAND} -E echo
          "Gradle wrapper exists: $<IF:$<BOOL:${CMAKE_CURRENT_SOURCE_DIR}/gradlew>,YES,NO>"
  COMMAND
    bash -c
    "if [ -f '${GRADLE_WRAPPER}' ]; then echo 'Wrapper version:'; ${GRADLE_WRAPPER} --version; else echo 'Wrapper not found'; fi"
  VERBATIM)

# Clean target that also removes Gradle build artifacts
add_custom_target(
  clean_all
  COMMAND ${CMAKE_COMMAND} -E echo "Cleaning Gradle build artifacts..."
  COMMAND
    bash -c
    "if [ -f '${GRADLE_WRAPPER}' ]; then ${GRADLE_WRAPPER} clean -PbuildDir=${GRADLE_BUILD_DIR} --project-dir=${CMAKE_CURRENT_SOURCE_DIR}; else echo 'No Gradle wrapper found'; fi"
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${GRADLE_BUILD_DIR}
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}/lib
  COMMENT "Cleaning all build artifacts including Gradle")
