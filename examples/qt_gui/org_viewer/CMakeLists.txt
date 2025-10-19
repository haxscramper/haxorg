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

include("../org_example_config.cmake")

file(GLOB PROJECT_SOURCES "${PROJ_ROOT}/*.?pp")

qt_add_executable(org_viewer MANUAL_FINALIZATION ${PROJECT_SOURCES})

target_compile_options(org_viewer PUBLIC "-Wno-deprecated-declarations")

option(ORG_USE_COVERAGE "Enable test coverage" OFF)
if(${ORG_USE_COVERAGE})
  target_compile_options(org_viewer PRIVATE -fprofile-instr-generate -fcoverage-mapping)
  target_link_options(org_viewer PRIVATE -lgcov --coverage -fprofile-instr-generate
                      -fcoverage-mapping)
endif()

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
