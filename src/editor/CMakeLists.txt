find_package(Qt6 6.2 REQUIRED COMPONENTS Core Test Widgets)

qt_standard_project_setup()
enable_testing(true)
set(EDITOR_DIR "${BASE}/src/editor")
message("[DBG] EDITOR_DIR = ${EDITOR_DIR}")

qt_add_library(editor_lib STATIC)
glob_add_sources2(TARGET editor_lib LS_REGEX "${EDITOR_DIR}/editor_lib.*" SEARCH_BASE "${BASE}")
haxorg_target_setup_v2(TARGET editor_lib)

target_link_libraries(
  editor_lib
  PUBLIC hstd
         haxorg
         Qt6::Test
         Qt6::Core
         Qt6::Widgets
         ${CAIROMM_LIBRARIES}
         adaptagrams)

if(${ORG_USE_PERFETTO})
  target_link_libraries(editor_lib PUBLIC Perfetto::perfetto)
endif()

target_include_directories(editor_lib PUBLIC "${BASE}/thirdparty/immer" "${BASE}/thirdparty/lager"
                                             "${BASE}/src" ${CAIROMM_INCLUDE_DIRS})

qt_add_executable(editor_app)
glob_add_sources2(TARGET editor_app LS_REGEX "${EDITOR_DIR}/editor_app.*" SEARCH_BASE "${BASE}")
haxorg_target_setup_v2(TARGET editor_app)
target_link_libraries(editor_app PUBLIC editor_lib)

qt_add_executable(editor_driver)
glob_add_sources2(TARGET editor_driver LS_REGEX "${EDITOR_DIR}/editor_driver.*" SEARCH_BASE
                  "${BASE}")
haxorg_target_setup_v2(TARGET editor_driver)
target_link_libraries(editor_driver PUBLIC editor_lib)

qt_add_library(editor_test_lib STATIC)
glob_add_sources2(TARGET editor_test_lib LS_REGEX "${EDITOR_DIR}/editor_test.*" SEARCH_BASE
                  "${BASE}")
haxorg_target_setup_v2(TARGET editor_test_lib)
target_link_libraries(editor_test_lib PUBLIC editor_lib)

function(create_target class_name path)
  message(STATUS "AUTO CREATE TEST TARGET class_name = ${class_name} path = ${path}")
  set(source_file "${CMAKE_BINARY_DIR}/auto_impl_${path}.cpp")
  set(TEST_CLASS_NAME "${class_name}")
  set(TEST_FILE_NAME "${path}")
  configure_file("${EDITOR_DIR}/editor_test/test_editor_main.cpp.in" ${source_file} @ONLY)
  set(TEST_EXECUTABLE_NAME "${class_name}_test")
  qt_add_executable(${TEST_EXECUTABLE_NAME} ${source_file})
  target_include_directories(${TEST_EXECUTABLE_NAME} PRIVATE ${CMAKE_BINARY_DIR})
  haxorg_target_setup_v2(TARGET ${TEST_EXECUTABLE_NAME})
  target_link_libraries(${TEST_EXECUTABLE_NAME} PUBLIC editor_test_lib)
endfunction()

execute_process(COMMAND jq -r ".[] | .class_name, .path"
                        "${EDITOR_DIR}/editor_test/test_config.json" OUTPUT_VARIABLE jq_output)

message(STATUS "jq_output = ${jq_output}")

string(REPLACE "\n" ";" class_list ${jq_output})
list(LENGTH class_list list_length)
math(EXPR num_items "${list_length} / 2")

foreach(idx RANGE 0 ${num_items} 2)
  list(GET class_list ${idx} class_name)
  math(EXPR path_idx "${idx} + 1")
  list(GET class_list ${path_idx} path)
  create_target(${class_name} ${path})
endforeach()
