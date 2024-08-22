#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <sem/SemBaseApi.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <exporters/ExporterBase.hpp>
#include <cstdlib>
#include <exporters/Exporter.cpp>


fs::path get_home() { return fs::path{std::getenv("HOME")}; }

struct ExporterVisual : public Exporter<ExporterVisual, int> {
    using Base = Exporter<ExporterVisual, int>;
#define __ExporterBase Base
    EXPORTER_USING()
#undef __ExporterBase

    bool ImOrgTree(char const* name) {
        ImGui::SetNextItemOpen(true, ImGuiCond_Once);
        return ImGui::TreeNode(name);
    }

    void visitField(int&, const char* name, Str const& value) {
        ImGui::Text("%s = %s", name, value.c_str());
    }

    template <typename T>
    void visitField(int&, const char* name, CR<T> field) {
        ImGui::Text(name);
    }

    void visitSubtree(int& j, sem::SemId<sem::Subtree> tree) {
        if (ImOrgTree("Subtree")) {
            for (auto const& sub : tree->subnodes) { visit(j, sub); }
            ImGui::TreePop();
        }
    }

    void visitDocument(int& j, sem::SemId<sem::Document> doc) {
        if (ImOrgTree("Document")) {
            for (auto const& sub : doc->subnodes) { visit(j, sub); }
            ImGui::TreePop();
        }
    }
};


template class Exporter<ExporterVisual, int>;

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

    auto file = readFile(get_home() / "tmp/doc1.org");
    auto node = sem::parseString(file);

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

        ExporterVisual exp;
        exp.evalTop(node);

        { // show FPS
            ImGuiIO& io = ImGui::GetIO();
            ImGui::SetNextWindowPos(
                ImVec2(io.DisplaySize.x - 100, 10), ImGuiCond_Always);
            ImGui::Begin(
                "FPS",
                nullptr,
                ImGuiWindowFlags_NoDecoration
                    | ImGuiWindowFlags_AlwaysAutoResize
                    | ImGuiWindowFlags_NoSavedSettings
                    | ImGuiWindowFlags_NoFocusOnAppearing
                    | ImGuiWindowFlags_NoNav);
            ImGui::Text("%.2f FPS", io.Framerate);
            ImGui::End();
        }

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
