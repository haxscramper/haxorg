cmake_minimum_required(VERSION 3.28)
project(imgui_gui LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CXX_STANDARD 23)

set(BASE "${CMAKE_CURRENT_SOURCE_DIR}/../..")
set(DEPS_INSTALL "${BASE}/build/deps_install")

list(INSERT CMAKE_PREFIX_PATH 0 "${BASE}/build/install")
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
find_package(Haxorg CONFIG REQUIRED)

add_executable(main main.cpp sem_tree_render.hpp sem_tree_render.cpp story_grid.hpp story_grid.cpp)

set(BASE "${CMAKE_SOURCE_DIR}")

file(GLOB IMGUI_SOURCES "${BASE}/imgui/*.cpp")
add_library(imgui STATIC ${IMGUI_SOURCES} "${BASE}/imgui/backends/imgui_impl_glfw.cpp"
                         "${BASE}/imgui/backends/imgui_impl_opengl3.cpp")
target_link_libraries(imgui PUBLIC SDL2)
target_include_directories(imgui PUBLIC "${BASE}/imgui" "${BASE}/imgui/backends")

target_link_libraries(
  main
  PRIVATE imgui
          glfw
          OpenGL::GL
          absl::log
          absl::base
          absl::flags
          haxorg::haxorg
          haxorg::hstd
          range-v3::range-v3)
