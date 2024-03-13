cmake_minimum_required(VERSION 3.16)

project(editor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Quick Core Test QuickTest)
add_subdirectory("${DEPS_DIR}/lexbor" "${CMAKE_BINARY_DIR}/lexbor_build")

qt_standard_project_setup()
enable_testing(true)
set(EDITOR_DIR "${BASE}/src/editor")

#tag org_editor_lib
qt_add_library(org_editor_lib STATIC)
file(GLOB_RECURSE QML_GUI_SOURCES RELATIVE "${EDITOR_DIR}" "${EDITOR_DIR}/gui_lib/*.qml")
qt_add_qml_module(org_editor_lib
    URI org_editor_lib
    VERSION 1.0
    OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/org_editor_lib
    QML_FILES ${QML_GUI_SOURCES})
target_link_libraries(org_editor_lib PUBLIC Qt6::Quick Qt6::Core range-v3 haxorg lexbor_static perfetto )
target_compile_definitions(org_editor_lib PUBLIC QT_QML_DEBUG)
target_include_directories(org_editor_lib PUBLIC "${BASE}/sem/editor")

set_common_files(org_editor_lib)
set_target_output(org_editor_lib)
set_target_flags(org_editor_lib)
glob_add_sources2(org_editor_lib "${EDITOR_DIR}/gui_lib/.*")

#tag org_editor_tests
qt_add_executable(org_editor_tests)
file(GLOB_RECURSE QML_TEST_SOURCES RELATIVE "${EDITOR_DIR}" "${EDITOR_DIR}/tests/*.qml")
qt_add_qml_module(org_editor_tests URI org_editor_tests VERSION 1.0 QML_FILES ${QML_TEST_SOURCES})
target_link_libraries(org_editor_tests PUBLIC haxorg Qt6::Test Qt6::QuickTest Qt6::Quick Qt6::Core org_editor_libplugin perfetto)
set_target_properties(org_editor_tests PROPERTIES OUTPUT_NAME "gui_tests")
target_include_directories(org_editor_tests PUBLIC "${BASE}/sem/editor")
target_compile_definitions(org_editor_tests PUBLIC QT_QML_DEBUG)

set_common_files(org_editor_tests)
set_target_output(org_editor_tests)
set_target_flags(org_editor_tests)
glob_add_sources2(org_editor_tests "${EDITOR_DIR}/tests/.*")


#tag org_editor_app
qt_add_executable(org_editor_app)
file(GLOB_RECURSE QML_APP_SOURCES RELATIVE "${EDITOR_DIR}" "${EDITOR_DIR}/gui_app/*.qml")
qt_add_qml_module(org_editor_app URI org_editor_app VERSION 1.0 QML_FILES ${QML_APP_SOURCES})
target_link_libraries(org_editor_app PUBLIC haxorg Qt6::Quick Qt6::Core org_editor_libplugin perfetto)
set_target_properties(org_editor_app PROPERTIES OUTPUT_NAME "org-editor")
target_include_directories(org_editor_app PUBLIC "${BASE}/sem/editor")
target_compile_definitions(org_editor_app PUBLIC QT_QML_DEBUG)

set_common_files(org_editor_app)
set_target_output(org_editor_app)
set_target_flags(org_editor_app)
glob_add_sources2(org_editor_app "${EDITOR_DIR}/gui_app/.*")


