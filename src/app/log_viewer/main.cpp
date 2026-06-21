#include "trace_log_viewer.hpp"
#include <hstd/stdlib/JsonCLIParser.hpp>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <hstd/stdlib/Debug.hpp>
#include <hstd/stdlib/VecFormatter.hpp>

struct Conf {
    Str  file;
    int  width;
    int  height;
    bool fullscreen;
    DESC_FIELDS(Conf, (file, width, height, fullscreen));
};

// TODO: Extract in common utility, remove duplicated code with org_imgui
void frame_end(GLFWwindow* window) {
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
}

// TODO: Extract in common utility, remove duplicated code with org_imgui
void frame_start() {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

// TODO: Extract in common utility, remove duplicated code with org_imgui
void quit_on_q(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}


int main(int argc, char* argv[]) {
    auto conf = hstd::parse_json_argc<Conf>(argc, argv);

    std::istringstream in{hstd::readFile(conf.file.toBase())};
    std::string        line;

    Vec<TraceEvent> events;
    while (std::getline(in, line)) {
        events.push_back(load_event_variant_from_json(json::parse(line)));
    }

    TraceLogViewer tlv;
    tlv.set_events(events);

    // TODO: Extract in common utility, remove duplicated code with
    // org_imgui

    // BEGIN copy-pasted
    if (!glfwInit()) { return 1; }

    GLFWmonitor*       monitor = glfwGetPrimaryMonitor();
    GLFWvidmode const* mode    = glfwGetVideoMode(monitor);

    GLFWwindow* window = glfwCreateWindow(
        conf.fullscreen ? mode->width : 1280,
        conf.fullscreen ? mode->height : 720,
        "log viewer",
        NULL,
        NULL);

    if (window == NULL) { return 1; }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    // END copy-pasted

    while (!glfwWindowShouldClose(window)) {
        frame_start();
        tlv.draw();
        frame_end(window);
    }
}
