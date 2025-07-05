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

#include <gui_lib/gui_perfetto.hpp>
#include <hstd/ext/perfetto_aux_impl_template.hpp>
#include <hstd/ext/logger.hpp>

extern void RegisterApptests(ImGuiTestEngine* engine);

int main(int argc, char** argv) {
    if (!glfwInit()) { return 1; }

    hstd::log::clear_sink_backends();
    hstd::log::push_sink(
        hstd::log::init_file_sink("/tmp/imgui_tests_sink.log"));

    GLFWmonitor*       monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode    = glfwGetVideoMode(monitor);

    bool fullscreen = true;

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
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigDebugIsDebuggerPresent = ImOsIsDebuggerPresent();

    // Setup test engine
    ImGuiTestEngine*   engine         = ImGuiTestEngine_CreateContext();
    ImGuiTestEngineIO& test_io        = ImGuiTestEngine_GetIO(engine);
    test_io.ConfigVerboseLevel        = ImGuiTestVerboseLevel_Info;
    test_io.ConfigVerboseLevelOnError = ImGuiTestVerboseLevel_Debug;
    test_io.ConfigRunSpeed            = ImGuiTestRunSpeed_Normal;

    // Start test engine
    ImGuiTestEngine_Start(engine, ImGui::GetCurrentContext());
    ImGuiTestEngine_InstallDefaultCrashHandler();

    // Register tests
    RegisterApptests(engine);

    ImGuiTestEngine_QueueTests(
        engine,
        ImGuiTestGroup_Tests,
        nullptr,
        ImGuiTestRunFlags_RunFromGui);

    bool aborted = false;
    while (!aborted) {
        if (!aborted && glfwWindowShouldClose(window)) { aborted = true; }

        if (aborted && ImGuiTestEngine_TryAbortEngine(engine)) { break; }

        frame_start();

        ImGui::ShowDemoWindow();
        ImGuiTestEngine_ShowTestEngineWindows(engine, NULL);

        frame_end(window);

        ImGuiTestEngine_PostSwap(engine);
        quit_on_q(window);
    }

    ImGuiTestEngine_Stop(engine);
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    ImGuiTestEngine_DestroyContext(engine);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
