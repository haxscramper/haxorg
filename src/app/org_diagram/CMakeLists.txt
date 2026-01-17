find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Test)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Test)

# Library configuration
qt_add_library(org_diagram_lib STATIC ${LIB_SOURCES})
glob_add_sources2(TARGET org_diagram_lib LS_REGEX "${BASE}/src/app/org_diagram/src/.*" SEARCH_BASE
                  "${BASE}")

add_subdirectory(jni_elk)
target_link_libraries(org_diagram_lib PUBLIC jni_elk_lib)

set_target_properties(
  org_diagram_lib
  PROPERTIES AUTOMOC ON
             AUTOUIC ON
             AUTORCC ON)

target_include_directories(org_diagram_lib PUBLIC "${BASE}/src/app")

target_link_libraries(org_diagram_lib PUBLIC Qt6::Core Qt6::Gui Qt6::Test Qt6::Widgets haxorg hstd)

set_target_flags(org_diagram_lib)
set_common_files(org_diagram_lib)

qt_add_executable(org_diagram MANUAL_FINALIZATION)
glob_add_sources2(TARGET org_diagram LS_REGEX "${BASE}/src/app/org_diagram/app/.*" SEARCH_BASE
                  "${BASE}")
set_common_files(org_diagram)
set_target_flags(org_diagram)

set_target_properties(
  org_diagram
  PROPERTIES AUTOMOC ON
             AUTOUIC ON
             AUTORCC ON)

target_link_libraries(org_diagram PRIVATE org_diagram_lib)

if(${ORG_USE_PERFETTO})
  target_link_libraries(org_diagram PUBLIC Perfetto::perfetto)
  target_compile_definitions(org_diagram PUBLIC ORG_USE_PERFETTO)
endif()

qt_finalize_executable(org_diagram)

enable_testing()

function(add_qt_test TEST_FILE_PATH TEST_CLASS)
  get_filename_component(TEST_CLASS ${TEST_FILE_PATH} NAME_WE)

  qt_add_executable(${TEST_CLASS} MANUAL_FINALIZATION
                    "${BASE}/src/app/org_diagram/tests/${TEST_FILE_PATH}")

  set_target_properties(
    ${TEST_CLASS}
    PROPERTIES AUTOMOC ON
               AUTOUIC ON
               AUTORCC ON)

  target_link_libraries(${TEST_CLASS} PRIVATE org_diagram_lib Qt6::Test)
  set_target_flags(${TEST_CLASS})
  set_common_files(${TEST_CLASS})

  add_test(NAME ${TEST_CLASS} COMMAND ${TEST_CLASS})
  set_tests_properties(${TEST_CLASS} PROPERTIES ENVIRONMENT "QT_QPA_PLATFORM=offscreen")

  if(${ORG_USE_PERFETTO})
    target_link_libraries(${TEST_CLASS} PUBLIC Perfetto::perfetto)
    target_compile_definitions(${TEST_CLASS} PUBLIC ORG_USE_PERFETTO)
  endif()

  qt_finalize_executable(${TEST_CLASS})
endfunction()

add_qt_test("tDiaContextStoreTreeSwitchingTest.cpp" "DiaContextStoreTreeSwitchingTest")
add_qt_test("tDebugTarget.cpp" "DebugTarget")
add_qt_test("tDiaNodeTreeModel_Standalone.cpp" "DiaNodeTreeModel_StandaloneTest")
add_qt_test("tDiaNodeTest.cpp" "DiaNodeTest")
add_qt_test("tDiaSceneItemModelTest.cpp" "DiaSceneItemModelTest")
add_qt_test("tDiaContextStoreIncomingEditTest.cpp" "DiaContextStoreIncomingEditTest")
add_qt_test("tDiaNodeLayout.cpp" "DiaNodeLayout")
