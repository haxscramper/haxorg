#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <sem/SemBaseApi.hpp>
#include <hstd/stdlib/Filesystem.hpp>

#include "sem_tree_render.hpp"


struct Config {
    DECL_DESCRIBED_ENUM(Mode, SemTree, Outline);

    Str  file;
    Mode mode = Mode::SemTree;

    DESC_FIELDS(Config, (file, mode));
};

void render_outline(sem::SemId<sem::Org> const& org) {
    switch (org->getKind()) {
        case OrgSemKind::Document: {
            if (ImGui::TreeNode("Document")) {
                for (auto const& sub : org->subnodes) {
                    render_outline(sub);
                }
                ImGui::TreePop();
            }
            break;
        }
        case OrgSemKind::Subtree: {
            if (ImGui::TreeNode("Subtree")) {
                for (auto const& sub : org->subnodes) {
                    render_outline(sub);
                }
                ImGui::TreePop();
            }
            break;
        }
        default: {
        }
    }
}

int main(int argc, char** argv) {
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


    auto conf_file = fs::path{argv[1]};
    CHECK(fs::is_regular_file(conf_file)) << conf_file;
    auto conf_text = readFile(conf_file);
    auto conf_json = json::parse(conf_text);
    auto conf      = from_json_eval<Config>(conf_json);

    auto file = readFile(fs::path{conf.file.toBase()});
    auto node = sem::parseString(file);

    bool doTrace = true;

    VisualExporterConfig config;

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


        switch (conf.mode) {
            case Config::Mode::SemTree: {
                render_sem_tree(node, config);
                break;
            }
            case Config::Mode::Outline: {
                render_outline(node);
                break;
            }
        }


        ImGui::End();
        ImGuiIO& io = ImGui::GetIO();
        ImGui::SetNextWindowPos(
            ImVec2(io.DisplaySize.x - 250, 10), ImGuiCond_Always);
        ImGui::Begin(
            "FPS",
            nullptr,
            ImGuiWindowFlags_NoDecoration
                | ImGuiWindowFlags_AlwaysAutoResize
                | ImGuiWindowFlags_NoSavedSettings
                | ImGuiWindowFlags_NoFocusOnAppearing
                | ImGuiWindowFlags_NoNav);
        ImGui::Text("%.2f FPS", io.Framerate);

        switch (conf.mode) {
            case Config::Mode::SemTree: {
                ImGui::Checkbox("Show nullopt", &config.showNullopt);
                ImGui::Checkbox("Show space", &config.showSpace);
                break;
            }
            default: {
            }
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
