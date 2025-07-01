cmake_minimum_required(VERSION 3.16)

project(
  org_viewer
  VERSION 0.1
  LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CXX_STANDARD 23)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

set(PROJ_ROOT "${CMAKE_SOURCE_DIR}")
set(REPO_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../..")
set(DEPS_INSTALL "${REPO_ROOT}/build/deps_bin/install")
message(STATUS "${DEPS_INSTALL}")

include("${DEPS_INSTALL}/paths.cmake")
list(INSERT CMAKE_PREFIX_PATH 0 "${REPO_ROOT}/build/install")

find_package(Immer CONFIG REQUIRED)
find_package(Lager CONFIG REQUIRED)
find_package(absl CONFIG REQUIRED)
find_package(protobuf CONFIG REQUIRED)
find_package(boost_mp11 CONFIG REQUIRED)
find_package(BoostDescribe CONFIG REQUIRED)
find_package(range-v3 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Perfetto CONFIG REQUIRED)
find_package(lexy CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(cctz REQUIRED)
find_package(msgpack-cxx CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS ALL)
find_package(cpptrace CONFIG REQUIRED)
find_package(BoostDescribe CONFIG REQUIRED)
find_package(BoostPreprocessor CONFIG REQUIRED)
find_package(Haxorg CONFIG REQUIRED)

file(GLOB PROJECT_SOURCES "${PROJ_ROOT}/*.?pp")

qt_add_executable(org_viewer MANUAL_FINALIZATION ${PROJECT_SOURCES})

set_target_properties(org_viewer PROPERTIES AUTOMOC ON)
target_link_libraries(org_viewer PRIVATE Qt6::Widgets haxorg::haxorg haxorg::hstd)

set_target_properties(
  org_viewer
  PROPERTIES ${BUNDLE_ID_OPTION} MACOSX_BUNDLE_BUNDLE_VERSION
             ${PROJECT_VERSION} MACOSX_BUNDLE_SHORT_VERSION_STRING
             ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR} MACOSX_BUNDLE
             TRUE WIN32_EXECUTABLE
             TRUE)

include(GNUInstallDirs)
install(
  TARGETS org_viewer
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

qt_finalize_executable(org_viewer)
