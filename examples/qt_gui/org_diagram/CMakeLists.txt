cmake_minimum_required(VERSION 3.16)

project(
  org_diagram
  VERSION 0.1
  LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CXX_STANDARD 23)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Test)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Test)

include("../org_example_config.cmake")

# Options
option(ORG_USE_COVERAGE "Enable test coverage" OFF)

# Coverage flags
if(${ORG_USE_COVERAGE})
  set(COVERAGE_COMPILE_FLAGS "-fprofile-instr-generate -fcoverage-mapping")
  set(COVERAGE_LINK_FLAGS "-lgcov --coverage -fprofile-instr-generate -fcoverage-mapping")
endif()

# Library configuration
file(GLOB_RECURSE LIB_SOURCES "${PROJ_ROOT}/src/*.?pp")
qt_add_library(org_diagram_lib STATIC ${LIB_SOURCES})

set_target_properties(
  org_diagram_lib
  PROPERTIES AUTOMOC ON
             AUTOUIC ON
             AUTORCC ON)

target_compile_definitions(org_diagram_lib PUBLIC ORG_USE_QT=1)
target_compile_options(org_diagram_lib PUBLIC "-ftemplate-backtrace-limit=0")
target_compile_options(org_diagram_lib PUBLIC "-Werror=implicit-fallthrough")
target_compile_options(org_diagram_lib PUBLIC "-fsanitize=undefined,address")
target_compile_options(org_diagram_lib PUBLIC "-shared-libasan")
target_compile_options(org_diagram_lib PUBLIC "-Werror=sometimes-uninitialized")
target_compile_options(org_diagram_lib PUBLIC "-Werror=conditional-uninitialized")
target_link_options(org_diagram_lib PUBLIC "-fsanitize=undefined,address")

target_include_directories(
  org_diagram_lib
  PUBLIC $<BUILD_INTERFACE:${PROJ_ROOT}> $<INSTALL_INTERFACE:include>
  PRIVATE ${PROJ_ROOT}/lib/src)

target_link_libraries(org_diagram_lib PUBLIC Qt6::Core Qt6::Gui Qt6::Test Qt6::Widgets
                                             haxorg::haxorg haxorg::hstd)

if(${ORG_USE_COVERAGE})
  target_compile_options(org_diagram_lib PRIVATE ${COVERAGE_COMPILE_FLAGS})
  target_link_options(org_diagram_lib PRIVATE ${COVERAGE_LINK_FLAGS})
endif()

add_library(org_diagram::lib ALIAS org_diagram_lib)

# Application configuration
file(GLOB APP_SOURCES "${PROJ_ROOT}/app/*.?pp")

qt_add_executable(org_diagram MANUAL_FINALIZATION ${APP_SOURCES})

set_target_properties(
  org_diagram
  PROPERTIES AUTOMOC ON
             AUTOUIC ON
             AUTORCC ON
             ${BUNDLE_ID_OPTION} MACOSX_BUNDLE_BUNDLE_VERSION
             ${PROJECT_VERSION} MACOSX_BUNDLE_SHORT_VERSION_STRING
             ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR} MACOSX_BUNDLE
             TRUE WIN32_EXECUTABLE
             TRUE)

target_link_libraries(org_diagram PRIVATE org_diagram::lib)

if(${ORG_USE_COVERAGE})
  target_compile_options(org_diagram PRIVATE ${COVERAGE_COMPILE_FLAGS})
  target_link_options(org_diagram PRIVATE ${COVERAGE_LINK_FLAGS})
endif()

include(GNUInstallDirs)
install(
  TARGETS org_diagram
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

qt_finalize_executable(org_diagram)

enable_testing()

function(add_qt_test TEST_FILE_PATH TEST_CLASS)
  get_filename_component(TEST_CLASS ${TEST_FILE_PATH} NAME_WE)

  qt_add_executable(${TEST_CLASS} "${PROJ_ROOT}/tests/${TEST_FILE_PATH}")

  set_target_properties(
    ${TEST_CLASS}
    PROPERTIES AUTOMOC ON
               AUTOUIC ON
               AUTORCC ON)

  target_link_libraries(${TEST_CLASS} PRIVATE org_diagram::lib Qt6::Test)

  if(${ORG_USE_COVERAGE})
    target_compile_options(${TEST_CLASS} PRIVATE ${COVERAGE_COMPILE_FLAGS})
    target_link_options(${TEST_CLASS} PRIVATE ${COVERAGE_LINK_FLAGS})
  endif()

  add_test(NAME ${TEST_CLASS} COMMAND ${TEST_CLASS})
  set_tests_properties(${TEST_CLASS} PROPERTIES ENVIRONMENT "QT_QPA_PLATFORM=offscreen")

  qt_finalize_executable(${TEST_CLASS})
endfunction()

add_qt_test("tDiaContextStoreTreeSwitchingTest.cpp" "DiaContextStoreTreeSwitchingTest")
add_qt_test("tDebugTarget.cpp" "DebugTarget")
add_qt_test("tDiaNodeTreeModel_Standalone.cpp" "DiaNodeTreeModel_StandaloneTest")
add_qt_test("tDiaNodeTest.cpp" "DiaNodeTest")
add_qt_test("tDiaSceneItemModelTest.cpp" "DiaSceneItemModelTest")
add_qt_test("tDiaContextStoreIncomingEditTest.cpp" "DiaContextStoreIncomingEditTest")
