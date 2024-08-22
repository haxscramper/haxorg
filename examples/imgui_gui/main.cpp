#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <sem/SemBaseApi.hpp>
#include <hstd/stdlib/Filesystem.hpp>

int main() {
    if (!glfwInit()) { return 1; }

    GLFWwindow* window = glfwCreateWindow(
        1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
    if (window == NULL) { return 1; }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    auto file = readFile("~/tmp/doc1.org");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Fullscreen window
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        // ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::Begin(
            "Fullscreen Window",
            nullptr,
            ImGuiWindowFlags_NoDecoration
                | ImGuiWindowFlags_NoBringToFrontOnFocus
                | ImGuiWindowFlags_NoNav);

        ImGui::Text("This is a fullscreen window.");

        ImGui::End();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
