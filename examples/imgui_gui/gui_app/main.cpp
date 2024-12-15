#define NDEBUG 0

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <haxorg/sem/SemBaseApi.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <haxorg/exporters/ExporterUltraplain.hpp>
#include <hstd/stdlib/Set.hpp>

#include <gui_lib/sem_tree_render.hpp>
#include <gui_lib/story_grid.hpp>
#include <gui_lib/imgui_utils.hpp>
#include <gui_lib/block_graph.hpp>
#include <gui_lib/ascii_editor.hpp>
#include <gui_lib/scintilla_editor_widget.hpp>
#include <gui_lib/doc_editor.hpp>

#include <gui_lib/gui_perfetto.hpp>
#include <hstd/wrappers/hstd_extra/perfetto_aux_impl_template.hpp>


struct Config {
    DECL_DESCRIBED_ENUM(
        Mode,
        SemTree,
        Outline,
        StoryGrid,
        Test,
        StoryGridAnnotated,
        ScintillaEditorTest,
        AsciiEditorTest,
        DocEditor);

    Str      file;
    Mode     mode = Mode::SemTree;
    Opt<Str> appstate;
    bool     fullscreen = false;
    Opt<Str> log_file   = std::nullopt;

    DESC_FIELDS(Config, (file, mode, appstate, fullscreen, log_file));
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
    float                          content_height,
    float                          scroll_y) {

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
            switch (log->head.getLogKind()) {
                case sem::SubtreeLogHead::Kind::Clock: {
                    auto const& clock = log->head.getClock();
                    if (clock.to) {
                        full_duration += GetTimeDelta(
                            clock.from, clock.to.value());
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


void fps_window_begin() {

    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos(
        ImVec2(io.DisplaySize.x - 250, 10), ImGuiCond_Once);
    ImGui::Begin("FPS", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Text("%.2f FPS", io.Framerate);
}

void sem_tree_loop(GLFWwindow* window, sem::SemId<sem::Org> node) {
    VisualExporterConfig sem_tree_config;
    while (!glfwWindowShouldClose(window)) {
        frame_start();
        render_sem_tree(node, sem_tree_config);
        {
            fps_window_begin();
            ImGui::Checkbox("Show nullopt", &sem_tree_config.showNullopt);
            ImGui::Checkbox("Show space", &sem_tree_config.showSpace);
            ImGui::End();
        }
        frame_end(window);
    }
}

void outline_tree_loop(GLFWwindow* window, sem::SemId<sem::Org> node) {
    OutlineConfig outline_config;
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
        frame_start();
        float  content_height = 0.0f;
        float  scroll_y       = 0.0f;
        ImVec2 mini_map_size;

        {
            fullscreen_window_begin();
            render_outline(node, outline_config, content_height);

            if (row_scroll) {
                float scroll = static_cast<float>(row_scroll.value())
                             / static_cast<float>(subtree_count)
                             * content_height;
                ImGui::SetScrollY(scroll);
            }

            mini_map_size = ImVec2(
                max_level * minimap_indent_size + 10.0f,
                ImGui::GetWindowHeight());

            scroll_y = ImGui::GetScrollY();

            ImGui::End();
        }

        {
            ImGuiIO& io = ImGui::GetIO();
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
                content_height,
                scroll_y);

            ImGui::End();
        }

        {
            fps_window_begin();
            ImGui::Checkbox("Show done", &outline_config.showDone);
            for (auto const& it : priorities) {
                bool shown = outline_config.priorities.contains(it);
                bool start = shown;
                ImGui::Checkbox(fmt("Priority '{}'", it).c_str(), &shown);
                if (start != shown) {
                    if (shown) {
                        outline_config.priorities.incl(it);
                    } else {
                        outline_config.priorities.excl(it);
                    }
                }
            }
            ImGui::End();
        }

        frame_end(window);
    }
}

int main(int argc, char** argv) {
    auto conf_file = fs::path{argv[1]};
    CHECK(fs::is_regular_file(conf_file)) << conf_file;
    auto conf_text = readFile(conf_file);
    auto conf_json = json::parse(conf_text);
    auto conf      = from_json_eval<Config>(conf_json);

    org_logging::clear_sink_backends();
    if (conf.log_file) {
        org_logging::push_sink(
            org_logging::init_file_sink(conf.log_file.value()));
    }

#ifdef ORG_USE_PERFETTO
    std::unique_ptr<perfetto::TracingSession>
        tracing_session = StartProcessTracing("Perfetto track example");

    finally end_trace{[&]() {
        StopTracing(std::move(tracing_session), "/tmp/story_grid.pftrace");
    }};
#endif

    if (!glfwInit()) { return 1; }


    GLFWmonitor*       monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode    = glfwGetVideoMode(monitor);

    GLFWwindow* window = glfwCreateWindow(
        conf.fullscreen ? mode->width : 1280,
        conf.fullscreen ? mode->height : 720,
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


    auto text = readFile(fs::path{conf.file.toBase()});

    Opt<json> appstate;
    if (conf.appstate.has_value()
        && fs::is_regular_file(conf.appstate.value().toBase())) {
        appstate = json::parse(
            readFile(fs::path{conf.appstate.value().toBase()}));
    }

    switch (conf.mode) {
        case Config::Mode::SemTree: {
            auto node = sem::parseString(text);
            sem_tree_loop(window, node);
            break;
        }
        case Config::Mode::Outline: {
            auto node = sem::parseString(text);
            outline_tree_loop(window, node);
            break;
        }
        case Config::Mode::DocEditor: {
            auto node = sem::parseString(text);
            doc_editor_loop(window, node);
            break;
        }

        case Config::Mode::StoryGridAnnotated:
        case Config::Mode::StoryGrid: {
            StoryGridConfig storyGridConf;
            using Col                   = TreeGridColumn;
            storyGridConf.getDefaultDoc = []() -> TreeGridDocument {
                TreeGridDocument doc;
                doc.columns = {
                    Col{.name = "title", .width = 200},
                    Col{.name = "event", .width = 400},
                    Col{.name = "note", .width = 400},
                    Col{.name = "turning_point", .width = 300},
                    Col{.name = "value", .width = 200},
                    Col{
                        .name  = "location",
                        .width = 240,
                        .edit  = EditableOrgText::Mode::SingleLine,
                    },
                    Col{.name = "pov", .width = 100},
                };
                return doc;
            };


            storyGridConf.mouseScrollMultiplier = 20;
            storyGridConf.annotated             = true;

            appstate = story_grid_loop(
                window, conf.file, appstate, storyGridConf);
            break;
        }
        case Config::Mode::Test: {
            run_block_graph_test(window);
            break;
        }
        case Config::Mode::ScintillaEditorTest: {
            run_scintilla_editor_widget_test(window);
            break;
        }
        case Config::Mode::AsciiEditorTest: {
            run_ascii_editor_widget_test(window);
            break;
        }
    }

    if (appstate && conf.appstate.has_value()) {
        writeFile(
            fs::path{conf.appstate.value().toBase()},
            appstate.value().dump(2));
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
