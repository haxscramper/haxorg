cmake_minimum_required(VERSION 3.16)

project(
  editor
  VERSION 0.1
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Quick Core Test QuickTest Widgets)
add_subdirectory("${DEPS_DIR}/lexbor" "${CMAKE_BINARY_DIR}/lexbor_build")

qt_standard_project_setup()
enable_testing(true)
set(EDITOR_DIR "${BASE}/src/editor")
message("[DBG] EDITOR_DIR = ${EDITOR_DIR}")

qt_add_executable(editor_app)
target_link_libraries(
  editor_app
  PUBLIC hstd
         perfetto
         haxorg
         Qt6::Test
         Qt6::QuickTest
         Qt6::Quick
         Qt6::Core
         Qt6::Widgets)

glob_add_sources2(editor_app "${EDITOR_DIR}/.*" "${BASE}")
set_common_files(editor_app)
set_target_output(editor_app)
set_target_flags(editor_app)
