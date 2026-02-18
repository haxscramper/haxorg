option(ORG_BUILD_WITH_PERFETTO "Enable perfetto profiling" OFF)
option(ORG_USE_SYSTEM_DEPS "Find packages in the system instead of using thirdparty" OFF)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Test)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FONTCONFIG REQUIRED fontconfig)

set(IMGUI_ORG_ROOT "${BASE}/src/app/org_imgui")
set(IMGUI_DEP_ROOT "${DEPS_DIR}/imgui")
message(STATUS "IMGUI_ORG_ROOT = ${IMGUI_ORG_ROOT}")

# external dependency for imgui library

set(IMCONFIG_TEMPLATE_PATH "${IMGUI_ORG_ROOT}/imconfig.h")
set(IMCONFIG_FILE_PATH "${IMGUI_DEP_ROOT}/imconfig.h")

configure_file("${IMCONFIG_TEMPLATE_PATH}" "${IMCONFIG_FILE_PATH}" @ONLY)

file(GLOB IMGUI_SOURCES "${IMGUI_DEP_ROOT}/*.cpp")

add_library(
  imgui STATIC
  ${IMGUI_SOURCES} "${IMGUI_DEP_ROOT}/backends/imgui_impl_glfw.cpp"
  "${IMGUI_DEP_ROOT}/misc/cpp/imgui_stdlib.cpp" #
  "${IMGUI_DEP_ROOT}/backends/imgui_impl_opengl3.cpp" #
)

target_link_libraries(imgui PUBLIC "${FONTCONFIG_LIBRARIES}")
target_include_directories(
  imgui
  PUBLIC "${IMGUI_ORG_ROOT}" "${DEPS_DIR}" "${IMGUI_DEP_ROOT}" "${IMGUI_DEP_ROOT}/backends"
         "${FONTCONFIG_INCLUDE_DIRS}" "${BASE}/thirdparty/imgui_test_engine/imgui_test_engine")

# imgui test engine

file(GLOB IMGUI_TEST_ENGINE_SOURCES "${BASE}/thirdparty/imgui_test_engine/imgui_test_engine/*.cpp")
add_library(imgui_test_engine STATIC "${IMGUI_TEST_ENGINE_SOURCES}")
target_include_directories(
  imgui_test_engine PUBLIC "${IMGUI_DEP_ROOT}" "${BASE}/thirdparty/imgui_test_engine"
                           "${BASE}/thirdparty/imgui_test_engine/imgui_test_engine")

# main part of app setup

file(GLOB ORG_IMGUI_LIB_FILES "${IMGUI_ORG_ROOT}/gui_lib/*.?pp")
add_library(org_imgui_lib ${ORG_IMGUI_LIB_FILES})
set_target_flags(org_imgui_lib)
set_common_files(org_imgui_lib)

if(${ORG_BUILD_WITH_PERFETTO})
  target_link_libraries(org_imgui_lib PUBLIC Perfetto::perfetto)
  target_compile_definitions(org_imgui_lib PUBLIC ORG_BUILD_WITH_PERFETTO)
endif()

target_include_directories(org_imgui_lib PUBLIC "${BASE}/src/app")
target_link_libraries(
  org_imgui_lib
  PUBLIC imgui
         imgui_test_engine
         glfw
         Boost::log
         OpenGL::GL
         absl::log
         absl::base
         absl::flags
         haxorg
         hstd
         cpptrace::cpptrace
         range-v3::range-v3)

if(${ORG_BUILD_WITH_ADAPTAGRAMS})
  target_link_libraries(org_imgui_lib PUBLIC adaptagrams)
endif()

file(GLOB ORG_IMGUI_APP_FILES "${IMGUI_ORG_ROOT}/gui_app/*.?pp")
add_executable(org_imgui_app ${ORG_IMGUI_APP_FILES})
target_link_libraries(org_imgui_app PUBLIC org_imgui_lib)
set_target_flags(org_imgui_app)
set_common_files(org_imgui_app)

file(GLOB ORG_IMGUI_GUI_TEST_FILES "${IMGUI_ORG_ROOT}/gui_test/*.?pp")
add_executable(org_imgui_test ${ORG_IMGUI_GUI_TEST_FILES})
target_link_libraries(org_imgui_test PUBLIC org_imgui_lib imgui_test_engine)
set_target_flags(org_imgui_test)
set_common_files(org_imgui_test)

file(GLOB ORG_IMGUI_LOGIC_TEST_FILES "${IMGUI_ORG_ROOT}/logic_test/*.?pp")
add_executable(org_imgui_logic_test ${ORG_IMGUI_LOGIC_TEST_FILES})
target_link_libraries(org_imgui_logic_test PUBLIC org_imgui_lib)
set_target_flags(org_imgui_logic_test)
set_common_files(org_imgui_logic_test)
