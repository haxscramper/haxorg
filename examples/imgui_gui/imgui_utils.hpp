#pragma once

#include <GLFW/glfw3.h>
#include <string>

void frame_start();
void frame_end(GLFWwindow* window);
void fullscreen_window_begin();
void push_ptr_id(void* id, std::string const& suffix = std::string{});
