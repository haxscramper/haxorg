#pragma once

#include <GLFW/glfw3.h>
#include <hstd/system/reflection.hpp>
#include "imgui.h"
#include "imgui_internal.h"

void frame_start();
void frame_end(GLFWwindow* window);
void fullscreen_window_begin();
int  push_frameless_window_vars();

BOOST_DESCRIBE_STRUCT(ImVec2, (), (x, y));
BOOST_DESCRIBE_STRUCT(ImVec4, (), (x, y, z, w));
BOOST_DESCRIBE_STRUCT(ImRect, (), (Min, Max));


inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) {
    return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y);
}

inline void operator+=(ImVec2& lhs, const ImVec2& rhs) { lhs = lhs + rhs; }

inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) {
    return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y);
}


inline ImVec2 operator*(const ImVec2& lhs, float mult) {
    return ImVec2(lhs.x * mult, lhs.y * mult);
}
