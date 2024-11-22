#pragma once

#include <GLFW/glfw3.h>
#include <hstd/stdlib/Vec.hpp>
#include <imgui.h>
#include <ScintillaMessages.h>

void run_scintilla_editor_widget_test(GLFWwindow* window);

class ScEditor;

namespace ImGui {
ScEditor* ScInputText(
    const char*   label,
    ImVec2 const& size = ImVec2{0, 0});
}
