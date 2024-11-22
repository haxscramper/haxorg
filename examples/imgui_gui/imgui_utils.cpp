#include "imgui_utils.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <hstd/system/Formatter.hpp>

#include <fontconfig/fontconfig.h>

void frame_start() {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void frame_end(GLFWwindow* window) {
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS
        && glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void fullscreen_window_begin() {
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    ImGui::Begin(
        "Fullscreen Window",
        nullptr,
        ImGuiWindowFlags_NoDecoration
            | ImGuiWindowFlags_NoBringToFrontOnFocus
            | ImGuiWindowFlags_NoNav);
}

int push_frameless_window_vars() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
    ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    return 3;
}

void render_debug_rect(const ImVec2& size, int border, ImU32 const& col) {
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() - border);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() - border);
    ImVec2 p0 = ImGui::GetCursorScreenPos();
    ImVec2 p1 = ImVec2(
        p0.x + size.x + (2 * border), p0.y + size.y + (2 * border));
    ImGui::GetForegroundDrawList()->AddRect(p0, p1, col);
}

Opt<Str> get_fontconfig_path(Str const& fontname) {
    FcInit();
    FcPattern* pattern = FcNameParse((const FcChar8*)fontname.c_str());
    FcConfigSubstitute(nullptr, pattern, FcMatchPattern);
    FcDefaultSubstitute(pattern);

    FcResult   result;
    FcPattern* match = FcFontMatch(nullptr, pattern, &result);

    FcChar8* font_path = nullptr;
    if (match) { FcPatternGetString(match, FC_FILE, 0, &font_path); }
    Opt<Str> opt_result;
    if (font_path != nullptr) { opt_result = (char const*)font_path; }
    FcPatternDestroy(pattern);
    FcPatternDestroy(match);
    FcFini();
    return opt_result;
}
