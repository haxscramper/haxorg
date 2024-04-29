cmake_minimum_required(VERSION 3.16)

project(
  editor
  VERSION 0.1
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Core Test Widgets)
find_package(KF6ItemModels REQUIRED)
add_subdirectory("${DEPS_DIR}/lexbor" "${CMAKE_BINARY_DIR}/lexbor_build")

qt_standard_project_setup()
enable_testing(true)
set(EDITOR_DIR "${BASE}/src/editor")
message("[DBG] EDITOR_DIR = ${EDITOR_DIR}")

qt_add_library(editor_lib)
glob_add_sources2(editor_lib "${EDITOR_DIR}/editor_lib.*" "${BASE}")
haxorg_target_setup(editor_lib)

target_link_libraries(
  editor_lib
  PUBLIC hstd
         perfetto
         haxorg
         Qt6::Test
         Qt6::Core
         Qt6::Widgets
         KF6::ItemModels)

target_include_directories(
  editor_lib PUBLIC "${BASE}/thirdparty/immer" "${BASE}/thirdparty/lager"
                    "${BASE}/src")

qt_add_executable(editor_app)
glob_add_sources2(editor_app "${EDITOR_DIR}/editor_app.*" "${BASE}")
haxorg_target_setup(editor_app)
target_link_libraries(editor_app PUBLIC editor_lib)

qt_add_executable(editor_test)
glob_add_sources2(editor_test "${EDITOR_DIR}/editor_test.*" "${BASE}")
haxorg_target_setup(editor_test)
target_link_libraries(editor_test PUBLIC editor_lib)
