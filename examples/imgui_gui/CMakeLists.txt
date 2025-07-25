cmake_minimum_required(VERSION 3.28)
project(imgui_gui LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CXX_STANDARD 23)

set(REPO_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../..")
set(DEPS_INSTALL "${REPO_ROOT}/build/deps_bin/install")

option(ORG_USE_PERFETTO "Enable perfetto profiling" OFF)
option(ORG_USE_SYSTEM_DEPS "Find packages in the system instead of using thirdparty" OFF)

if(NOT ${ORG_USE_SYSTEM_DEPS})
  include("${DEPS_INSTALL}/paths.cmake")
endif()

list(INSERT CMAKE_PREFIX_PATH 0 "${REPO_ROOT}/build/install")

find_package(Immer CONFIG REQUIRED)
find_package(Lager CONFIG REQUIRED)
find_package(absl CONFIG REQUIRED)
find_package(protobuf CONFIG REQUIRED)
find_package(boost_mp11 CONFIG REQUIRED)
find_package(BoostDescribe CONFIG REQUIRED)
find_package(range-v3 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Perfetto CONFIG REQUIRED)
find_package(lexy CONFIG REQUIRED)
find_package(cctz REQUIRED)
find_package(BoostPreprocessor CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(Haxorg CONFIG REQUIRED)
find_package(msgpack-cxx CONFIG REQUIRED)
find_package(Adaptagrams CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS ALL)
find_package(cpptrace CONFIG REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FONTCONFIG REQUIRED fontconfig)

add_definitions(-DORG_DEPS_USE_ADAPTAGRAMS)
add_definitions(-DORG_LIB_DEBUG_BUILD=1)

set(PROJ_ROOT "${CMAKE_SOURCE_DIR}")

# external dependency for imgui library

set(IMCONFIG_TEMPLATE_PATH "${PROJ_ROOT}/imconfig.h")
set(IMCONFIG_FILE_PATH "${PROJ_ROOT}/imgui/imconfig.h")

configure_file("${IMCONFIG_TEMPLATE_PATH}" "${IMCONFIG_FILE_PATH}" @ONLY)

file(GLOB IMGUI_SOURCES "${PROJ_ROOT}/imgui/*.cpp")

add_library(
  imgui STATIC
  ${IMGUI_SOURCES} "${PROJ_ROOT}/imgui/backends/imgui_impl_glfw.cpp"
  "${PROJ_ROOT}/imgui/misc/cpp/imgui_stdlib.cpp" #
  "${PROJ_ROOT}/imgui/backends/imgui_impl_opengl3.cpp")

target_link_libraries(imgui PUBLIC "${FONTCONFIG_LIBRARIES}")
target_include_directories(
  imgui PUBLIC "${PROJ_ROOT}/imgui" "${PROJ_ROOT}/imgui/backends" "${FONTCONFIG_INCLUDE_DIRS}"
               "${REPO_ROOT}/thirdparty/imgui_test_engine/imgui_test_engine")

# imgui test engine

file(GLOB IMGUI_TEST_ENGINE_SOURCES
     "${REPO_ROOT}/thirdparty/imgui_test_engine/imgui_test_engine/*.cpp")
add_library(imgui_test_engine STATIC "${IMGUI_TEST_ENGINE_SOURCES}")
target_include_directories(
  imgui_test_engine PUBLIC "${PROJ_ROOT}/imgui" "${REPO_ROOT}/thirdparty/imgui_test_engine"
                           "${REPO_ROOT}/thirdparty/imgui_test_engine/imgui_test_engine")

# main part of app setup

file(GLOB IMGUI_EXAMPLE_LIB_FILES "${PROJ_ROOT}/gui_lib/*.?pp")
add_library(imgui_example_lib ${IMGUI_EXAMPLE_LIB_FILES})

option(ORG_USE_COVERAGE "Enable test coverage" OFF)
if(${ORG_USE_COVERAGE})
  target_compile_options(imgui_example_lib PUBLIC -fprofile-instr-generate -fcoverage-mapping)
  target_link_options(imgui_example_lib PUBLIC -lgcov --coverage -fprofile-instr-generate
                      -fcoverage-mapping)
endif()

if(${ORG_USE_PERFETTO})
  target_link_libraries(imgui_example_lib PUBLIC Perfetto::perfetto)
endif()

if(${ORG_USE_PERFETTO})
  target_compile_definitions(imgui_example_lib PUBLIC ORG_USE_PERFETTO)
endif()

target_compile_options(imgui_example_lib PUBLIC "-Wno-ambiguous-reversed-operator")

target_link_directories(imgui_example_lib PUBLIC "${SCINT_DEPS}/bin" "${LEXLL_DEPS}/bin")
target_include_directories(imgui_example_lib PUBLIC "${LEXLL_DEPS}/include" "${SCINT_DEPS}/include"
                                                    "${PROJ_ROOT}")
target_link_libraries(
  imgui_example_lib
  PUBLIC imgui
         imgui_test_engine
         glfw
         Boost::log
         OpenGL::GL
         absl::log
         absl::base
         absl::flags
         Adaptagrams::dialect
         Adaptagrams::cola
         Adaptagrams::avoid
         Adaptagrams::topology
         Adaptagrams::vpsc
         haxorg::adaptagrams
         haxorg::haxorg
         haxorg::hstd
         cpptrace::cpptrace
         range-v3::range-v3)

file(GLOB IMGUI_EXAMPLE_APP_FILES "${PROJ_ROOT}/gui_app/*.?pp")
add_executable(IMGUI_EXAMPLE_APP ${IMGUI_EXAMPLE_APP_FILES})
target_link_libraries(IMGUI_EXAMPLE_APP PUBLIC imgui_example_lib)

file(GLOB IMGUI_EXAMPLE_GUI_TEST_FILES "${PROJ_ROOT}/gui_test/*.?pp")
add_executable(IMGUI_EXAMPLE_GUI_TEST ${IMGUI_EXAMPLE_GUI_TEST_FILES})
target_link_libraries(IMGUI_EXAMPLE_GUI_TEST PUBLIC imgui_example_lib imgui_test_engine)

file(GLOB IMGUI_EXAMPLE_LOGIC_TEST_FILES "${PROJ_ROOT}/logic_test/*.?pp")
add_executable(IMGUI_EXAMPLE_LOGIC_TEST ${IMGUI_EXAMPLE_LOGIC_TEST_FILES})
target_link_libraries(IMGUI_EXAMPLE_LOGIC_TEST PUBLIC imgui_example_lib)
