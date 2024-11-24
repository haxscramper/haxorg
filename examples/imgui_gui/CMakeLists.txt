cmake_minimum_required(VERSION 3.28)
project(imgui_gui LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CXX_STANDARD 23)

set(REPO_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../..")
set(DEPS_INSTALL "${REPO_ROOT}/build/deps_install")
set(SCINT_DEPS "${REPO_ROOT}/thirdparty/scintilla/scintilla")
set(LEXLL_DEPS "${REPO_ROOT}/thirdparty/scintilla/lexilla")

option(ORG_USE_PERFETTO "Enable perfetto profiling" OFF)

list(INSERT CMAKE_PREFIX_PATH 0 "${REPO_ROOT}/build/install")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/reflex/lib/cmake/reflex")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/protobuf/lib/cmake/protobuf")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/abseil/lib/cmake/absl")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/perfetto/lib/cmake/Perfetto")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/describe/lib/cmake/BoostDescribe")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/mp11/lib/cmake/boost_mp11-1.85.0")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/range-v3/lib/cmake/range-v3")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/json/share/cmake/nlohmann_json")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/lager/lib/cmake/Lager")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/immer/lib/cmake/Immer")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/adaptagrams/lib/cmake/Adaptagrams")
list(INSERT CMAKE_PREFIX_PATH 0 "${DEPS_INSTALL}/lexy/lib/cmake/lexy")

find_package(Immer CONFIG REQUIRED)
find_package(Lager CONFIG REQUIRED)
find_package(Reflex CONFIG REQUIRED)
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
find_package(Haxorg CONFIG REQUIRED)
find_package(Adaptagrams CONFIG REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FONTCONFIG REQUIRED fontconfig)

add_executable(
  main
  main.cpp
  sem_tree_render.hpp
  sem_tree_render.cpp
  story_grid.hpp
  story_grid.cpp
  imgui_utils.cpp
  imgui_utils.hpp
  gui_perfetto.cpp
  gui_perfetto.hpp
  ascii_editor.cpp
  ascii_editor.hpp
  block_graph.cpp
  block_graph.hpp
  scintilla_editor_widget.hpp
  scintilla_editor_widget.cpp)

set(PROJ_ROOT "${CMAKE_SOURCE_DIR}")

file(GLOB IMGUI_SOURCES "${PROJ_ROOT}/imgui/*.cpp")
add_library(
  imgui STATIC
  ${IMGUI_SOURCES} "${PROJ_ROOT}/imgui/backends/imgui_impl_glfw.cpp"
  "${PROJ_ROOT}/imgui/misc/cpp/imgui_stdlib.cpp" #
  "${PROJ_ROOT}/imgui/backends/imgui_impl_opengl3.cpp")

target_link_libraries(imgui PUBLIC "${FONTCONFIG_LIBRARIES}")
target_include_directories(imgui PUBLIC "${PROJ_ROOT}/imgui" "${PROJ_ROOT}/imgui/backends"
                                        "${FONTCONFIG_INCLUDE_DIRS}")

if(${ORG_USE_PERFETTO})
  target_link_libraries(main PUBLIC Perfetto::perfetto)
endif()

if(${ORG_USE_PERFETTO})
  target_compile_definitions(main PUBLIC ORG_USE_PERFETTO)
endif()

target_link_directories(main PUBLIC "${SCINT_DEPS}/bin" "${LEXLL_DEPS}/bin")
target_include_directories(main PUBLIC "${LEXLL_DEPS}/include" "${SCINT_DEPS}/include"
                                       "${REPO_ROOT}/thirdparty/scintilla")
target_link_libraries(
  main
  PRIVATE imgui
          glfw
          scintilla
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
          range-v3::range-v3)
