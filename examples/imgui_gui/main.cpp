#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <sem/SemBaseApi.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <exporters/ExporterUltraplain.hpp>
#include <hstd/stdlib/Set.hpp>

#include "sem_tree_render.hpp"


struct Config {
    DECL_DESCRIBED_ENUM(Mode, SemTree, Outline);

    Str  file;
    Mode mode = Mode::SemTree;

    DESC_FIELDS(Config, (file, mode));
};

struct OutlineConfig {
    bool              showDone = false;
    UnorderedSet<Str> priorities;
    DESC_FIELDS(OutlineConfig, (showDone));
};

long GetTimeDelta(CR<UserTime> from, CR<UserTime> to) {
    auto from_utc = absl::ToCivilSecond(
        from.time, from.zone ? *from.zone : absl::TimeZone{});
    auto to_utc = absl::ToCivilSecond(
        to.time, to.zone ? *to.zone : absl::TimeZone{});
    return to_utc - from_utc;
}

std::string FormatTimeDelta(long delta_seconds) {
    long delta   = delta_seconds / 60;
    long hours   = delta / 60;
    long minutes = delta % 60;
    return std::format("{}:{:02}", hours, minutes);
}

namespace {
float minimap_rect_height = 5.0f;
float minimap_top_offset  = 10.0f;
float minimap_indent_size = 5.0f;
} // namespace

Opt<int> render_mini_map(
    CVec<sem::SemId<sem::Subtree>> tree,
    float                          mini_map_height,
    ImVec2                         size,
    float                          content_height) {

    ImGui::InvisibleButton("MiniMap", size);
    ImVec2 window_pos = ImGui::GetWindowPos();
    std::function<void(const sem::SemId<sem::Subtree>&)> render_node;

    int      dfs_idx = 0;
    Opt<int> out_idx;

    render_node = [&](const sem::SemId<sem::Subtree>& node) {
        const float node_y = minimap_top_offset + window_pos.y
                           + (dfs_idx * minimap_rect_height);


        ++dfs_idx;
        ImVec2 rect_pos = ImVec2(
            window_pos.x + node->level * minimap_indent_size, node_y);
        ImVec2 rect_end = ImVec2(
            rect_pos.x + size.x - node->level * minimap_indent_size,
            rect_pos.y + minimap_rect_height);

        ImU32 rect_color = ImGui::ColorConvertFloat4ToU32(
            color((ColorName)((int)ColorName::Red + node->level - 1)));
        ImGui::GetWindowDrawList()->AddRectFilled(
            rect_pos, rect_end, rect_color);

        if (ImGui::IsMouseHoveringRect(rect_pos, rect_end)) {
            ImGui::GetWindowDrawList()->AddRect(
                rect_pos,
                rect_end,
                IM_COL32(0, 255, 255, 255),
                0.0f,
                0,
                2.0f);
            if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
                out_idx = dfs_idx;
            }
        }

        for (const auto& subnode : node.subAs<sem::Subtree>()) {
            render_node(subnode);
        }
    };

    for (const auto& node : tree) { render_node(node); }

    return out_idx;
}


void render_outline_subtree(
    sem::SemId<sem::Subtree> const& org,
    OutlineConfig const&            conf,
    float&                          content_height) {


    auto const nested = org.subAs<sem::Subtree>();

    bool skipped //
        = (!conf.showDone && org->todo
           && (org->todo == "DONE" || org->todo == "COMPLETED"))
       || (org->priority.has_value()
           && !conf.priorities.contains(org->priority.value()))
       || (!org->priority.has_value() && !conf.priorities.contains(""));

    if (!skipped || !nested.empty()) {
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
    }

    auto render_tree_columns = [&]() {
        ImGui::TableSetColumnIndex(1);
        ImGui::PushTextWrapPos(
            ImGui::GetCursorPos().x + ImGui::GetContentRegionAvail().x);
        ImGui::Text(
            "%s", ExporterUltraplain::toStr(org->title.asOrg()).c_str());
        ImGui::PopTextWrapPos();

        if (org->priority) {
            ImGui::TableSetColumnIndex(2);
            ImGui::TextColored(
                color(ColorName::Red),
                "%s",
                org->priority.value().c_str());
        }


        if (org->todo) {
            ImGui::TableSetColumnIndex(3);
            ImGui::TextColored(
                color(ColorName::Yellow), "%s", org->todo.value().c_str());
        }

        long full_duration = 0;
        for (auto const& log : org->logbook) {
            switch (log->getLogKind()) {
                case sem::SubtreeLog::Kind::Clock: {
                    auto const& clock = log->getClock();
                    if (clock.to && clock.from) {
                        full_duration += GetTimeDelta(
                            clock.from->getStatic().time,
                            clock.to.value()->getStatic().time);
                    }
                    break;
                }
                default: {
                }
            }
        }

        if (full_duration != 0) {
            ImGui::TableSetColumnIndex(4);
            ImGui::Text("%s", FormatTimeDelta(full_duration).c_str());
        }

        content_height += ImGui::GetTextLineHeightWithSpacing();
    };

    if (!nested.empty()) {
        ImGui::PushID(
            fmt("{:p}", static_cast<const void*>(org.value.get()))
                .c_str());

        if (org->level < 3) {
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);
        }
        bool node_open = ImGui::TreeNodeEx(
            fmt("[{}]", org->level).c_str(),
            ImGuiTreeNodeFlags_SpanFullWidth);
        ImGui::PopID();

        render_tree_columns();

        if (node_open) {
            for (auto const& sub : nested) {
                render_outline_subtree(sub, conf, content_height);
            }
            ImGui::TreePop();
        }
    } else if (!skipped) {
        render_tree_columns();
    }
}

void render_outline(
    sem::SemId<sem::Org> const& org,
    OutlineConfig const&        conf,
    float&                      content_height) {
    if (ImGui::BeginTable(
            "TreeTable",
            5,
            ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg
                | ImGuiTableFlags_SizingFixedFit)) {

        ImGui::TableSetupColumn(
            "Tree", ImGuiTableColumnFlags_WidthFixed, 120.0f);
        ImGui::TableSetupColumn(
            "Title", ImGuiTableColumnFlags_WidthFixed, 400.0f);
        ImGui::TableSetupColumn(
            "Prio", ImGuiTableColumnFlags_WidthFixed, 50.0f);
        ImGui::TableSetupColumn(
            "TODO", ImGuiTableColumnFlags_WidthFixed, 120.0f);
        ImGui::TableSetupColumn(
            "Duration", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableHeadersRow();

        for (auto const& sub : org.subAs<sem::Subtree>()) {
            render_outline_subtree(sub, conf, content_height);
        }

        ImGui::EndTable();
    }
}

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

    if (window == NULL) { return 1; }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

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

    VisualExporterConfig sem_tree_config;
    OutlineConfig        outline_config;
    outline_config.priorities.incl("");

    Vec<Str> priorities{""};
    int      subtree_count = 0;
    int      max_level     = 0;
    sem::eachSubnodeRec(node, [&](sem::SemId<sem::Org> it) {
        if (auto tree = it.asOpt<sem::Subtree>()) {
            ++subtree_count;
            max_level = std::max(tree->level, max_level);
            if (tree->priority
                && priorities.indexOf(tree->priority.value()) == -1) {
                priorities.push_back(tree->priority.value());
            }
        }
    });

    rs::sort(priorities);
    Opt<int> row_scroll;
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Fullscreen window
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        float scroll_y       = 0.0f;
        float content_height = 0.0f;
        ImGui::Begin(
            "Fullscreen Window",
            nullptr,
            ImGuiWindowFlags_NoDecoration
                | ImGuiWindowFlags_NoBringToFrontOnFocus
                | ImGuiWindowFlags_NoNav);


        switch (conf.mode) {
            case Config::Mode::SemTree: {
                render_sem_tree(node, sem_tree_config);
                break;
            }
            case Config::Mode::Outline: {
                render_outline(node, outline_config, content_height);
                break;
            }
        }

        if (row_scroll) {
            float scroll = static_cast<float>(row_scroll.value())
                         / static_cast<float>(subtree_count)
                         * content_height;
            ImGui::SetScrollY(scroll);
        }

        ImVec2 mini_map_size = ImVec2(
            max_level * minimap_indent_size + 10.0f,
            ImGui::GetWindowHeight());

        ImGui::End();

        ImGui::SetNextWindowPos(
            ImVec2(io.DisplaySize.x - mini_map_size.x, 0));
        ImGui::SetNextWindowSize(mini_map_size);
        ImGui::Begin(
            "Map",
            nullptr,
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav);


        row_scroll = render_mini_map(
            node.subAs<sem::Subtree>(),
            mini_map_size.y,
            mini_map_size,
            content_height);

        ImGui::End();


        ImGuiIO& io = ImGui::GetIO();
        ImGui::SetNextWindowPos(
            ImVec2(io.DisplaySize.x - 250, 10), ImGuiCond_Once);
        ImGui::Begin("FPS", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("%.2f FPS", io.Framerate);

        switch (conf.mode) {
            case Config::Mode::SemTree: {
                ImGui::Checkbox(
                    "Show nullopt", &sem_tree_config.showNullopt);
                ImGui::Checkbox("Show space", &sem_tree_config.showSpace);
                break;
            }
            case Config::Mode::Outline: {
                ImGui::Checkbox("Show done", &outline_config.showDone);
                for (auto const& it : priorities) {
                    bool shown = outline_config.priorities.contains(it);
                    bool start = shown;
                    ImGui::Checkbox(
                        fmt("Priority '{}'", it).c_str(), &shown);
                    if (start != shown) {
                        if (shown) {
                            outline_config.priorities.incl(it);
                        } else {
                            outline_config.priorities.excl(it);
                        }
                    }
                }
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

        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
