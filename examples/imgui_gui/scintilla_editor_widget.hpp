#pragma once

#include <GLFW/glfw3.h>
#include <hstd/stdlib/Vec.hpp>
#include <imgui.h>
#include <ScintillaMessages.h>

void run_scintilla_editor_widget_test(GLFWwindow* window);

class ScEditor;

namespace ImGui {
ScEditor* ScInputText(
    const char* label,
    float       xSize,
    float       ySize,
    void (*callback)(void*),
    void* userData);
}
