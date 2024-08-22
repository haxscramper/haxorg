project(imgui_gui LANGUAGES CXX)
cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CXX_STANDARD 23)

set(BASE "${CMAKE_CURRENT_SOURCE_DIR}/../..")
set(DEPS_INSTALL "${BASE}/build/deps_install")

list(APPEND CMAKE_PREFIX_PATH "${BASE}/build/install")
list(APPEND CMAKE_PREFIX_PATH "${DEPS_INSTALL}/reflex/lib/cmake/reflex")
list(APPEND CMAKE_PREFIX_PATH "${DEPS_INSTALL}/protobuf/lib/cmake/protobuf")
list(APPEND CMAKE_PREFIX_PATH "${DEPS_INSTALL}/abseil/lib/cmake/absl")
list(APPEND CMAKE_PREFIX_PATH "${DEPS_INSTALL}/perfetto/lib/cmake/Perfetto")
list(APPEND CMAKE_PREFIX_PATH "${DEPS_INSTALL}/describe/lib/cmake/BoostDescribe")
list(APPEND CMAKE_PREFIX_PATH "${DEPS_INSTALL}/mp11/lib/cmake/boost_mp11-1.85.0")
list(APPEND CMAKE_PREFIX_PATH "${DEPS_INSTALL}/range-v3/lib/cmake/range-v3")

find_package(Reflex CONFIG REQUIRED)
find_package(absl CONFIG REQUIRED)
find_package(protobuf CONFIG REQUIRED)
find_package(Perfetto CONFIG REQUIRED)
find_package(boost_mp11 CONFIG REQUIRED)
find_package(BoostDescribe CONFIG REQUIRED)
find_package(range-v3 CONFIG REQUIRED)
find_package(Haxorg CONFIG REQUIRED)

add_executable(main main.cpp)

set(BASE "${CMAKE_SOURCE_DIR}")

find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(Haxorg CONFIG REQUIRED)

file(GLOB IMGUI_SOURCES "${BASE}/imgui/*.cpp")
add_library(imgui STATIC
    ${IMGUI_SOURCES}
    "${BASE}/imgui/backends/imgui_impl_glfw.cpp"
    "${BASE}/imgui/backends/imgui_impl_opengl3.cpp"
)
target_link_libraries(imgui PUBLIC SDL2)
target_include_directories(imgui PUBLIC "${BASE}/imgui" "${BASE}/imgui/backends")


target_link_libraries(main PRIVATE imgui glfw OpenGL::GL SDL2::SDL2 haxorg::haxorg haxorg::hstd range-v3::range-v3)

