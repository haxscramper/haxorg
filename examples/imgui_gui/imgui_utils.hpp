#pragma once

#include <GLFW/glfw3.h>
#include <hstd/system/reflection.hpp>
#include "imgui.h"

void frame_start();
void frame_end(GLFWwindow* window);
void fullscreen_window_begin();

BOOST_DESCRIBE_STRUCT(ImVec2, (), (x, y));
BOOST_DESCRIBE_STRUCT(ImVec4, (), (x, y, z, w));
