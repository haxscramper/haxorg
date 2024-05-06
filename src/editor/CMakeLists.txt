include(ExternalProject)

set(COLA_CXX_FLAGS "$<$<CONFIG:Debug>:-O0 -g ${CMAKE_CXX_FLAGS}>$<$<CONFIG:Release>:-O3 -DNDEBUG ${CMAKE_CXX_FLAGS}>")
set(COLA_INSTALL_DIR "${CMAKE_BINARY_DIR}/libcola/install")

ExternalProject_Add(libcola
    SOURCE_DIR "${DEPS_DIR}/adaptagrams/cola"
    PREFIX "${CMAKE_BINARY_DIR}/libcola"
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND
        mkdir -p <SOURCE_DIR>/m4
    COMMAND
        autoreconf --install --verbose
    COMMAND
        ./configure --prefix=${COLA_INSTALL_DIR}
        CXXFLAGS=${COLA_CXX_FLAGS}
        CC=${CMAKE_C_COMPILER}
        CXX=${CMAKE_CXX_COMPILER}
    BUILD_COMMAND make
    INSTALL_COMMAND make install
)

add_library(libcola_external INTERFACE)

set_property(TARGET libcola_external PROPERTY INTERFACE_LINK_LIBRARIES
    "${COLA_INSTALL_DIR}/lib/libavoid.a"
    "${COLA_INSTALL_DIR}/lib/libcola.a"
    "${COLA_INSTALL_DIR}/lib/libdialect.a"
    "${COLA_INSTALL_DIR}/lib/libtopology.a"
    "${COLA_INSTALL_DIR}/lib/libvpsc.a"
)

set_property(TARGET libcola_external
    PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${DEPS_DIR}/adaptagrams"
)

find_package(Qt6 6.2 REQUIRED COMPONENTS Core Test Widgets)
add_subdirectory("${DEPS_DIR}/lexbor" "${CMAKE_BINARY_DIR}/lexbor_build")


qt_policy(SET QTP0003 NEW)

qt_standard_project_setup()
enable_testing(true)
set(EDITOR_DIR "${BASE}/src/editor")
message("[DBG] EDITOR_DIR = ${EDITOR_DIR}")

qt_add_library(editor_lib)
glob_add_sources2(editor_lib "${EDITOR_DIR}/editor_lib.*" "${BASE}")
haxorg_target_setup(editor_lib)

add_dependencies(editor_lib libcola)

target_link_libraries(
  editor_lib
  PUBLIC hstd
         perfetto
         haxorg
         Qt6::Test
         Qt6::Core
         Qt6::Widgets
         libcola_external)

target_include_directories(
  editor_lib PUBLIC "${BASE}/thirdparty/immer" "${BASE}/thirdparty/lager"
                    "${BASE}/src")

qt_add_executable(editor_app)
glob_add_sources2(editor_app "${EDITOR_DIR}/editor_app.*" "${BASE}")
haxorg_target_setup(editor_app)
target_link_libraries(editor_app PUBLIC editor_lib)

qt_add_library(editor_test_lib)
glob_add_sources2(editor_test_lib "${EDITOR_DIR}/editor_test.*" "${BASE}")
haxorg_target_setup(editor_test_lib)
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
    haxorg_target_setup(${TEST_EXECUTABLE_NAME})
    target_link_libraries(${TEST_EXECUTABLE_NAME} PUBLIC editor_test_lib)
endfunction()

execute_process(
    COMMAND jq -r ".[] | .class_name, .path" "${EDITOR_DIR}/editor_test/test_config.json"
    OUTPUT_VARIABLE jq_output
)


string(REPLACE "\n" ";" class_list ${jq_output})
list(LENGTH class_list list_length)
math(EXPR num_items "${list_length} / 2")

foreach(idx RANGE 0 ${num_items} 2)
    list(GET class_list ${idx} class_name)
    math(EXPR path_idx "${idx} + 1")
    list(GET class_list ${path_idx} path)
    create_target(${class_name} ${path})
endforeach()
