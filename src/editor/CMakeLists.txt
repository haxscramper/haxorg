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

qt_add_executable(editor_test)
glob_add_sources2(editor_test "${EDITOR_DIR}/editor_test.*" "${BASE}")
haxorg_target_setup(editor_test)
target_link_libraries(editor_test PUBLIC editor_lib)
