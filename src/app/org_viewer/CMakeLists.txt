set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(org_viewer MANUAL_FINALIZATION)
glob_add_sources2(TARGET org_viewer LS_REGEX "${BASE}/src/app/org_viewer/.*" SEARCH_BASE "${BASE}")
set_common_files(org_viewer)
set_target_flags(org_viewer)

set_target_properties(org_viewer PROPERTIES AUTOMOC ON)
target_link_libraries(org_viewer PRIVATE Qt6::Widgets haxorg hstd)

if(${ORG_USE_PERFETTO})
  target_link_libraries(org_viewer PUBLIC Perfetto::perfetto)
  target_compile_definitions(org_viewer PUBLIC ORG_USE_PERFETTO)
endif()

qt_finalize_executable(org_viewer)
