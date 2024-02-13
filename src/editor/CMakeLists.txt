cmake_minimum_required(VERSION 3.16)

project(editor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Core)

qt_standard_project_setup()

qt_add_executable(org_editor)

qt_add_qml_module(org_editor
    URI editor
    VERSION 1.0
    QML_FILES Main.qml
)

glob_add_sources2(org_editor "${BASE}/src/editor/.*")

add_subdirectory("${DEPS_DIR}/lexbor" "${CMAKE_BINARY_DIR}/lexbor_build")

target_link_libraries(org_editor PUBLIC haxorg lexbor_static)
set_common_files(org_editor)
set_target_output(org_editor)
set_target_flags(org_editor)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider sett5ing an
# explicit, fixed bundle identifier manually though.
set_target_properties(org_editor PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.org_editor
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(org_editor
    PRIVATE Qt6::Quick Qt6::Core
)

target_compile_definitions(org_editor PRIVATE QT_QML_DEBUG)

include(GNUInstallDirs)
install(TARGETS org_editor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

