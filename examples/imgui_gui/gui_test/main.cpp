#include <imgui/imgui_internal.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <gui_lib/imgui_utils.hpp>

#include "imgui_test_engine/imgui_te_engine.h"
#include "imgui_test_engine/imgui_te_ui.h"
#include "imgui_test_engine/imgui_te_utils.h"

extern void RegisterApptests(ImGuiTestEngine* engine);

int main(int argc, char** argv) {
    if (!glfwInit()) { return 1; }


    GLFWmonitor*       monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode    = glfwGetVideoMode(monitor);

    bool fullscreen = false;

    GLFWwindow* window = glfwCreateWindow(
        fullscreen ? mode->width : 1280,
        fullscreen ? mode->height : 720,
        "Dear ImGui GLFW+OpenGL3 example",
        NULL,
        NULL);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);


    // Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable
                                                          // Keyboard
                                                          // Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad
                                                          // Controls
    io.ConfigDebugIsDebuggerPresent = ImOsIsDebuggerPresent();

    // Setup test engine
    ImGuiTestEngine*   engine         = ImGuiTestEngine_CreateContext();
    ImGuiTestEngineIO& test_io        = ImGuiTestEngine_GetIO(engine);
    test_io.ConfigVerboseLevel        = ImGuiTestVerboseLevel_Info;
    test_io.ConfigVerboseLevelOnError = ImGuiTestVerboseLevel_Debug;
    test_io.ConfigRunSpeed = ImGuiTestRunSpeed_Cinematic; // Default to
                                                          // slowest mode
                                                          // in this demo

    // Optional: save test output in junit-compatible XML format.
    // test_io.ExportResultsFile = "./results.xml";
    // test_io.ExportResultsFormat = ImGuiTestEngineExportFormat_JUnitXml;

    // Start test engine
    ImGuiTestEngine_Start(engine, ImGui::GetCurrentContext());
    ImGuiTestEngine_InstallDefaultCrashHandler();

    // Register tests
    RegisterApptests(engine);

    // Main loop
    bool aborted = false;
    while (!aborted) {
        if (!aborted && glfwWindowShouldClose(window)) { aborted = true; }

        if (aborted && ImGuiTestEngine_TryAbortEngine(engine)) { break; }

        frame_start();

        // Show windows
        ImGui::ShowDemoWindow();
        ImGuiTestEngine_ShowTestEngineWindows(engine, NULL);

        frame_end(window);

        // Post-swap handler is REQUIRED in order to support screen capture
        ImGuiTestEngine_PostSwap(engine);
    }

    // Shutdown
    ImGuiTestEngine_Stop(engine);
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // IMPORTANT: we need to destroy the ImGui context BEFORE the test
    // engine context, so .ini data may be saved.
    ImGuiTestEngine_DestroyContext(engine);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
