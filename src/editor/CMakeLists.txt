cmake_minimum_required(VERSION 3.16)

project(editor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Core Test QuickTest)

qt_standard_project_setup()
enable_testing(true)

#tag org_editor_lib
qt_add_library(org_editor_lib STATIC)
file(GLOB_RECURSE QML_GUI_SOURCES RELATIVE "${BASE}/src/editor" "${BASE}/src/editor/gui_lib/*.qml")
qt_add_qml_module(org_editor_lib URI org_editor_lib VERSION 1.0 QML_FILES ${QML_GUI_SOURCES})

glob_add_sources2(org_editor_lib "${BASE}/src/editor/gui_lib/.*")
add_subdirectory("${DEPS_DIR}/lexbor" "${CMAKE_BINARY_DIR}/lexbor_build")

target_link_libraries(org_editor_lib PUBLIC Qt6::Quick Qt6::Core range-v3 haxorg lexbor_static)
set_common_files(org_editor_lib)
set_target_output(org_editor_lib)
set_target_flags(org_editor_lib)
target_compile_definitions(org_editor_lib PUBLIC QT_QML_DEBUG)

include(GNUInstallDirs)
install(TARGETS org_editor_lib
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


#tag org_editor_tests
qt_add_executable(org_editor_tests)
file(GLOB_RECURSE QML_TEST_SOURCES RELATIVE "${BASE}/src/editor" "${BASE}/src/editor/tests/*.qml")
qt_add_qml_module(org_editor_tests URI org_editor_tests VERSION 1.0 QML_FILES ${QML_TEST_SOURCES})
target_link_libraries(org_editor_tests PUBLIC haxorg Qt6::Test Qt6::QuickTest Qt6::Quick Qt6::Core org_editor_libplugin)
set_target_properties(org_editor_tests PROPERTIES OUTPUT_NAME "gui_tests")

set_common_files(org_editor_tests)
set_target_output(org_editor_tests)
set_target_flags(org_editor_tests)
glob_add_sources2(org_editor_tests "${BASE}/src/editor/tests/.*")

target_include_directories(org_editor_tests PUBLIC "${BASE}/sem/editor")

install(TARGETS org_editor_tests
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

#tag org_editor_app
qt_add_executable(org_editor_app)
file(GLOB_RECURSE QML_APP_SOURCES RELATIVE "${BASE}/src/editor" "${BASE}/src/editor/gui_app/*.qml")
qt_add_qml_module(org_editor_app URI org_editor_app VERSION 1.0 QML_FILES ${QML_APP_SOURCES})
target_link_libraries(org_editor_app PUBLIC haxorg Qt6::Quick Qt6::Core org_editor_libplugin)

set_common_files(org_editor_app)
set_target_output(org_editor_app)
set_target_flags(org_editor_app)
glob_add_sources2(org_editor_app "${BASE}/src/editor/gui_app/.*")

target_include_directories(org_editor_app PUBLIC "${BASE}/sem/editor")
set_target_properties(org_editor_app PROPERTIES OUTPUT_NAME "org-editor")

install(TARGETS org_editor_app
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
