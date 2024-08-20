project(imgui_gui LANGUAGES CXX)
cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CXX_STANDARD 23)

add_executable(main main.cpp)

set(BASE "${CMAKE_SOURCE_DIR}")

find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

file(GLOB IMGUI_SOURCES "${BASE}/imgui/*.cpp")
add_library(imgui STATIC
    ${IMGUI_SOURCES}
    "${BASE}/imgui/backends/imgui_impl_glfw.cpp"
    "${BASE}/imgui/backends/imgui_impl_opengl3.cpp"
)
target_link_libraries(imgui PUBLIC SDL2)
target_include_directories(imgui PUBLIC "${BASE}/imgui" "${BASE}/imgui/backends")


target_link_libraries(main PRIVATE imgui glfw OpenGL::GL SDL2::SDL2)

