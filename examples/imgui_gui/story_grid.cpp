#include "story_grid.hpp"

#include <haxorg/sem/ImmOrgEdit.hpp>
#include "block_graph.hpp"
#include "imgui_internal.h"
#include "imgui_utils.hpp"
#include "misc/cpp/imgui_stdlib.h"
#include "imgui.h"
#include "gui_perfetto.hpp"
#include <queue>
#include <sys/inotify.h>
#include <haxorg/sem/SemBaseApi.hpp>

#include <fontconfig/fontconfig.h>
#include <haxorg/sem/ImmOrgGraphBoost.hpp>


Opt<Str> get_fontconfig_path(std::string const& fontname) {
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

Vec<Str> split_wrap_text(std::string const& unwrapped, int width) {
    Vec<Str>    result;
    const char* text = unwrapped.c_str();
    while (*text) {
        const char* line_start = text;
        float       line_width = 0.0f;
        while (*text && line_width < width) {
            uint        __out_char = 0;
            auto        size = ImTextCharFromUtf8(&__out_char, text, NULL);
            const char* next = text + size;
            if (next == text) { break; }
            auto width = ImGui::CalcTextSize(text, next).x;
            line_width += width;
            text = next;
        }
        result.emplace_back(line_start, text - line_start);
    }

    return result;
}

#define CTX_MSG(...)                                                      \
    if (ctx.OperationsTracer::TraceState) { ctx.message(__VA_ARGS__); }

#define CTX_MSG_ALL(...) ctx.message(__VA_ARGS__);


void render_debug_rect(ImVec2 const& size, int border = 2) {
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() - border);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() - border);
    ImVec2 p0 = ImGui::GetCursorScreenPos();
    ImVec2 p1 = ImVec2(
        p0.x + size.x + (2 * border), p0.y + size.y + (2 * border));
    ImGui::GetWindowDrawList()->AddRect(
        p0, p1, IM_COL32(255, 255, 255, 255));
}


bool render_editable_text(
    std::string&             value,
    std::string&             edit_buffer,
    bool&                    is_editing,
    int                      height,
    int                      width,
    TreeGridColumn::EditMode edit) {
    auto cell_prefix = fmt("{:p}", static_cast<const void*>(value.data()));

    if (edit == TreeGridColumn::EditMode::Multiline) {
        if (is_editing) {
            ImGui::InputTextMultiline(
                fmt("##{}_edit", cell_prefix).c_str(),
                &edit_buffer,
                ImVec2(width, height + 10),
                ImGuiInputTextFlags_None);


            if (ImGui::Button("done")) {
                value             //
                    = edit_buffer //
                    | rv::remove_if(
                          [](char c) { return c == '\n' || c == '\r'; })
                    | rs::to<std::string>;
                is_editing = false;
                return true;
            } else if (ImGui::SameLine(); ImGui::Button("cancel")) {
                is_editing = false;
                return false;
            } else {
                return false;
            }


        } else {
            {
                ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
                ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0);
                ImGui::PushStyleVar(
                    ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
                ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + width);
                // NOTE: Using ID with runtime formatting here because
                // there is more than one cell that might potentially be
                // edited.
                ImGui::BeginChild(
                    fmt("##{}_wrap", cell_prefix).c_str(),
                    ImVec2(width, height),
                    false,
                    ImGuiWindowFlags_NoScrollbar);
                ImGui::PushID(fmt("##{}_view", cell_prefix).c_str());
                ImGui::TextWrapped("%s", value.c_str());
                ImGui::PopID();
                ImGui::EndChild();
                ImGui::PopTextWrapPos();
                ImGui::PopStyleVar(3);
            }
            if (ImGui::IsItemClicked()) {
                is_editing = true;
                edit_buffer.clear();
                edit_buffer = join("\n", split_wrap_text(value, width));
            }
            return false;
        }
    } else {
        if (is_editing) {
            if (ImGui::Button("OK")) {
                value      = edit_buffer;
                is_editing = false;
                return true;
            } else if (ImGui::SameLine(0.0f, 0.0f); ImGui::Button("X")) {
                is_editing = false;
                return false;
            }
            ImGui::SameLine(0.0f, 0.0f);
            ImGui::SetNextItemWidth(width);
            ImGui::InputText(
                fmt("##{}_edit", cell_prefix).c_str(), &edit_buffer);
            return false;

        } else {
            ImGui::Text("%s", value.c_str());
            if (ImGui::IsItemClicked()) {
                is_editing  = true;
                edit_buffer = value;
            }
            return false;
        }
    }
}

bool render_editable_cell(
    TreeGridCell&         cell,
    StoryGridContext&     ctx,
    TreeGridColumn const& col) {
    auto& val = cell.getValue();
    return render_editable_text(
        val.value,
        val.edit_buffer,
        val.is_editing,
        cell.height,
        cell.width,
        col.edit);
}


Opt<GridAction> render_cell(
    TreeGridCell&         cell,
    StoryGridContext&     ctx,
    TreeGridColumn const& col) {
    Opt<GridAction> result;

    if (render_editable_cell(cell, ctx, col)) {
        result = GridAction{GridAction::EditCell{
            .cell    = cell,
            .updated = cell.getValue().value,
        }};
    }

    return result;
}

void render_tree_columns(
    TreeGridRow&      row,
    Vec<GridAction>&  result,
    TreeGridDocument& doc,
    StoryGridContext& ctx) {
    auto __scope = ctx.scopeLevel();
    int  colIdx  = 1;
    for (auto const& col : doc.columns) {
        if (row.columns.contains(col.name)) {
            ImGui::TableSetColumnIndex(colIdx);
            // CTX_MSG(fmt("{}", col.name));
            auto __scope = ctx.scopeLevel();
            render_cell(row.columns.at(col.name), ctx, col);
        }
        ++colIdx;
    }
}

float tree_fold_column = 120.0f;

void render_tree_row(
    TreeGridRow&      row,
    Vec<GridAction>&  result,
    TreeGridDocument& doc,
    StoryGridContext& ctx) {
    // row is completely invisible, including its nested sub-rows
    if (!row.isVisible) { return; }
    bool skipped = false;
    auto __scope = ctx.scopeLevel();

    if (skipped && row.nested.empty()) { return; };

    ImGui::TableNextRow(
        ImGuiTableRowFlags_None, row.getHeight().value_or(20));
    // CTX_MSG(fmt("row {}", ImGui::TableGetRowIndex()));
    if (!row.nested.empty()) {
        switch (row.origin->level) {
            case 1:
                ImGui::TableSetBgColor(
                    ImGuiTableBgTarget_RowBg0,
                    IM_COL32(255, 200, 200, 128));
                break;
            case 2:
                ImGui::TableSetBgColor(
                    ImGuiTableBgTarget_RowBg0,
                    IM_COL32(200, 255, 200, 128));
                break;
            case 3:
                ImGui::TableSetBgColor(
                    ImGuiTableBgTarget_RowBg0,
                    IM_COL32(200, 200, 255, 128));
                break;
            default: {
            }
        }
    }

    ImGui::TableSetColumnIndex(0);
    int this_index = ImGui::TableGetRowIndex();

    if (!row.nested.empty()) {
        ImGui::PushID(fmt("{}", row.origin.id).c_str());
        ImGui::SetNextItemOpen(true, ImGuiCond_Once);
        bool node_open = ImGui::TreeNodeEx(
            fmt("[{}]", row.origin->level).c_str(),
            ImGuiTreeNodeFlags_SpanFullWidth);
        ImGui::PopID();
        render_tree_columns(row, result, doc, ctx);
        if (node_open) {
            for (auto& sub : row.nested) {
                render_tree_row(sub, result, doc, ctx);
            }

            ImGui::TreePop();
        }
    } else if (!skipped) {
        render_tree_columns(row, result, doc, ctx);
    }

    ImGui::TableSetColumnIndex(0);
    if (ImGui::TableGetRowIndex() == this_index) {
        ImRect cell_rect = ImGui::TableGetCellBgRect(
            ImGui::GetCurrentTable(), 0);
        ImVec2 cell_max  = cell_rect.Max;
        ImVec2 rect_size = ImVec2(
            std::ceil(
                ((6 - row.origin->level) / 6.0f)
                * (cell_rect.Max.x - cell_rect.Min.x)),
            cell_rect.Max.y - cell_rect.Min.y);
        float  pad      = 2.0f;
        ImVec2 rect_min = cell_max - rect_size + ImVec2(pad, pad);
        ImVec2 rect_max = cell_max - ImVec2(pad, pad);

        ImGui::GetWindowDrawList()->AddRectFilled(
            rect_min, rect_max, IM_COL32(255, 0, 0, 128));
        if (false) {
            ImGui::GetWindowDrawList()->AddRect(
                rect_min,
                rect_max,
                IM_COL32(0, 255, 255, 255),
                0.0f,
                0,
                1.0f);
        }
    }
}

Vec<GridAction> render_text_node(
    StoryGridModel&      model,
    StoryGridNode::Text& grid) {
    Vec<GridAction> result;
    auto&           ctx = model.conf;


    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
    ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::SetNextWindowPos(grid.pos + model.shift);
    ImGui::SetNextWindowSize(grid.size);
    ImGui::Begin(
        fmt("##{:p}", static_cast<const void*>(grid.text.data())).c_str(),
        nullptr,
        ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize);

    bool edit = false;
    render_editable_text(
        grid.text,
        grid.text,
        edit,
        grid.size.y,
        grid.size.x,
        TreeGridColumn::EditMode::Multiline);

    ImGui::End();

    ImGui::PopStyleVar(3);

    return result;
}

Vec<GridAction> render_list_node(
    StoryGridModel&          model,
    StoryGridNode::LinkList& list) {
    Vec<GridAction> result;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
    ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::SetNextWindowPos(list.pos + model.shift);
    ImGui::SetNextWindowSize(list.size);
    if (ImGui::Begin(
            fmt("##{:p}", static_cast<const void*>(&list)).c_str(),
            nullptr,
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize)) {

        if (ImGui::IsWindowHovered(
                ImGuiHoveredFlags_RootAndChildWindows
                | ImGuiHoveredFlags_AllowWhenBlockedByPopup
                | ImGuiHoveredFlags_AllowWhenBlockedByActiveItem)
            && ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
            list.isSelected = !list.isSelected;
            result.push_back(GridAction{GridAction::LinkListClick{}});
        }

        if (ImGui::BeginTable(
                fmt("##{:p}", static_cast<const void*>(&list)).c_str(),
                1,
                ImGuiTableFlags_Borders              //
                    | ImGuiTableFlags_RowBg          //
                    | ImGuiTableFlags_SizingFixedFit //
                    | ImGuiTableFlags_NoHostExtendX)) {

            ImGui::TableSetupColumn(
                "List", ImGuiTableColumnFlags_WidthFixed, list.getWidth());

            for (auto& item : list.items) {
                ImGui::TableNextRow(ImGuiTableRowFlags_None, item.height);
                bool edit = false;
                render_editable_text(
                    item.text,
                    item.text,
                    edit,
                    item.height,
                    item.width,
                    TreeGridColumn::EditMode::Multiline);
            }
            ImGui::EndTable();
        }
        ImGui::End();
    }

    ImGui::PopStyleVar(3);

    return result;
}

Vec<GridAction> render_table_node(
    StoryGridModel&          model,
    StoryGridNode::TreeGrid& grid) {
    Vec<GridAction> result;
    auto&           ctx = model.conf;
    auto&           doc = grid.node;
    CTX_MSG(fmt("doc rows {}", doc.rows.size()));

    ImGui::SetNextWindowPos(grid.pos + model.shift);
    ImGui::SetNextWindowSize(grid.size);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
    ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    if (ImGui::Begin(
            "Standalone Table Window",
            nullptr,
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize)) {
        if (ImGui::BeginTable(
                "TreeTable",
                1 + doc.columns.size(),
                ImGuiTableFlags_Borders              //
                    | ImGuiTableFlags_RowBg          //
                    | ImGuiTableFlags_SizingFixedFit //
                    | ImGuiTableFlags_NoHostExtendX)) {

            ImGui::TableSetupColumn(
                "Tree",
                ImGuiTableColumnFlags_WidthFixed,
                tree_fold_column);
            for (auto const& col : doc.columns) {
                // CTX_MSG(fmt("{} {}", col.name, col.width));
                ImGui::TableSetupColumn(
                    col.name.c_str(),
                    ImGuiTableColumnFlags_WidthFixed,
                    col.width);
            }
            ImGui::TableSetupScrollFreeze(0, 1);
            ImGui::TableHeadersRow();

            for (auto& sub : doc.rows) {
                render_tree_row(sub, result, doc, ctx);
            }

            // ImGui::TableNextRow(ImGuiTableRowFlags_None, 800.0f);
            // ImGui::TableNextColumn();

            ImGui::EndTable();
        }

        ImGui::End();
    }
    ImGui::PopStyleVar(3);

    return result;
}

Vec<GridAction> render_story_grid(StoryGridModel& model) {
    __perf_trace("gui", "grid model render");
    Vec<GridAction> result;
    for (int i = 0; i < model.rectGraph.nodes.size(); ++i) {
        auto& node = model.rectGraph.nodes.at(i);
        if (node.isVisible) {
            switch (node.getKind()) {
                case StoryGridNode::Kind::TreeGrid: {
                    result.append(
                        render_table_node(model, node.getTreeGrid()));
                    break;
                }
                case StoryGridNode::Kind::Text: {
                    result.append(render_text_node(model, node.getText()));
                    break;
                }
                case StoryGridNode::Kind::LinkList: {
                    result.append(
                        render_list_node(model, node.getLinkList()));
                    break;
                }
            }
        }
    }

    for (auto const& [key, edge] : model.layout.lines) {
        render_edge(edge, model.shift, false);
    }


    return result;
}

void story_grid_loop(GLFWwindow* window, std::string const& file) {
    int inotify_fd = inotify_init1(IN_NONBLOCK);
    if (inotify_fd < 0) {
        throw std::system_error(
            errno,
            std::generic_category(),
            "Failed to initialize inotify");
    }

    int watch_descriptor = inotify_add_watch(
        inotify_fd, file.c_str(), IN_MODIFY);
    if (watch_descriptor < 0) {
        throw std::system_error(
            errno, std::generic_category(), "Failed to add inotify watch");
    }

    std::string buffer(1024, '\0');

    sem::SemId<sem::Org> node;

    StoryGridModel     model;
    org::ImmAstContext start;
    model.history.push_back(StoryGridState{
        .ast = start.init(sem::parseString(readFile(file))),
    });


    model.conf.setTraceFile("/tmp/story_grid_trace.txt");


    bool first = true;

    auto font_path = get_fontconfig_path("Iosevka");
    if (font_path) {
        LOG(INFO) << fmt("Using font file {}", *font_path);
        ImGuiIO& io = ImGui::GetIO();
        io.Fonts->AddFontFromFileTTF(font_path->c_str(), 16);
    } else {
        LOG(ERROR) << "Could not load font path";
    }

    while (!glfwWindowShouldClose(window)) {
        int inotify_change = read(inotify_fd, &buffer[0], buffer.size());
        if (0 < inotify_change) {
            LOG(INFO) << "File change, reloading the model";
            model.history.clear();
            model.history.push_back(StoryGridState{
                .ast = start.init(sem::parseString(readFile(file))),
            });
            model.updateNeeded.incl(StoryGridModel::UpdateNeeded::Graph);
            model.updateNeeded.incl(StoryGridModel::UpdateNeeded::Scroll);
            model.updateDocument();
        }

        frame_start();

        fullscreen_window_begin();

        if (first) {
            first = false;
            model.updateNeeded.incl(StoryGridModel::UpdateNeeded::Graph);
            model.updateNeeded.incl(StoryGridModel::UpdateNeeded::Scroll);
            model.updateDocument();
        }

        if (model.debug) {
            render_debug(model.debug.value(), model.shift);
        }

        Vec<GridAction> updates = render_story_grid(model);

        ImGuiIO& io            = ImGui::GetIO();
        float    scroll_amount = io.MouseWheel;
        if (scroll_amount != 0.0f) {
            updates.push_back(GridAction{GridAction::Scroll{
                .pos       = io.MousePos,
                .direction = scroll_amount,
            }});
        }

        if (ImGui::IsKeyPressed(ImGuiKey_PageUp)) {
            updates.push_back(GridAction{GridAction::Scroll{
                .pos       = io.MousePos,
                .direction = 20,
            }});
        }

        if (ImGui::IsKeyPressed(ImGuiKey_PageDown)) {
            updates.push_back(GridAction{GridAction::Scroll{
                .pos       = io.MousePos,
                .direction = -20,
            }});
        }

        ImGui::End();

        frame_end(window);
        if (!updates.empty()) {
            model.conf.OperationsTracer::TraceState = true;
            for (auto const& update : updates) { model.apply(update); }
            model.updateDocument();
        }

        model.conf.OperationsTracer::TraceState = false;
    }

    inotify_rm_watch(inotify_fd, watch_descriptor);
    close(inotify_fd);
}


TreeGridCell build_editable_cell(
    org::ImmAdapter       adapter,
    TreeGridColumn const& col);

TreeGridRow build_row(
    org::ImmAdapterT<org::ImmSubtree> tree,
    TreeGridDocument&                 doc,
    int&                              flatIdx) {
    TreeGridRow result;
    result.columns["title"] = build_editable_cell(
        tree.getTitle(), doc.getColumn("title"));
    result.origin  = tree;
    result.flatIdx = flatIdx;
    ++flatIdx;
    for (auto const& sub : tree.subAs<org::ImmList>()) {
        if (sub.isDescriptionList()) {
            for (auto const& item : sub.subAs<org::ImmListItem>()) {
                auto flat = flatWords(item.getHeader().value());
                for (auto const& word : flat) {
                    if (word.starts_with("story_")) {
                        auto column            = word.dropPrefix("story_");
                        result.columns[column] = build_editable_cell(
                            item.at(0), doc.getColumn(column));
                    }
                }
            }
        }
    }

    for (auto const& sub : tree.subAs<org::ImmSubtree>()) {
        if (!sub->isComment && !sub->isArchived) {
            result.nested.push_back(build_row(sub, doc, flatIdx));
        }
    }

    return result;
}

Vec<TreeGridRow> build_rows(org::ImmAdapter root, TreeGridDocument& doc) {
    Vec<TreeGridRow> result;
    int              idx = 0;
    for (auto const& tree : root.subAs<org::ImmSubtree>()) {
        result.push_back(build_row(tree, doc, idx));
    }

    return result;
}

int get_text_height(
    std::string const&       text,
    int                      width,
    TreeGridColumn::EditMode edit) {
    Vec<Str>    wrapped = split_wrap_text(text, width);
    std::string _tmp{"Tt"};
    char const* _tmp_begin = _tmp.c_str();
    char const* _tmp_end   = _tmp_begin + _tmp.length();
    ImVec2      text_size  = ImGui::CalcTextSize(
        _tmp_begin, _tmp_end, false, width);

    if (edit == TreeGridColumn::EditMode::SingleLine) {
        return text_size.y;
    } else {
        return 0 < wrapped.size() ? text_size.y * (wrapped.size() + 1)
                                  : text_size.y;
    }
}

TreeGridCell build_editable_cell(
    org::ImmAdapter       adapter,
    TreeGridColumn const& col) {
    TreeGridCell result{TreeGridCell::Value{}};
    auto&        v = result.getValue();
    v.value        = join(" ", flatWords(adapter));
    v.origin       = adapter;
    result.width   = col.width;
    result.height  = get_text_height(v.value, col.width, col.edit);
    return result;
}


Vec<Vec<DocAnnotation>> partition_graph_nodes(
    const Vec<org::graph::MapNode>& initial_nodes,
    const org::graph::MapGraph&     graph) {
    __perf_trace("gui", "partition graph by distance");

    Vec<Vec<DocAnnotation>>                result;
    UnorderedMap<org::graph::MapNode, int> distances;
    std::queue<org::graph::MapNode>        q;

    for (const auto& node : initial_nodes) {
        distances[node] = 0;
        q.push(node);
    }

    while (!q.empty()) {
        org::graph::MapNode current = q.front();
        q.pop();
        int current_distance = distances[current];

        if (current_distance >= result.size()) {
            result.resize(current_distance + 1);
        }

        UnorderedSet<org::graph::MapNode> adjacent;
        for (org::graph::MapNode const& adj : graph.adjList.at(current)) {
            if (!adjacent.contains(adj) && !distances.contains(adj)) {
                distances[adj] = current_distance + 1;
                q.push(adj);
                result[current_distance].push_back(DocAnnotation{
                    .source = current,
                    .target = adj,
                });
            }

            adjacent.incl(adj);
        }

        for (org::graph::MapNode const& adj : graph.inNodes.at(current)) {
            if (!adjacent.contains(adj) && !distances.contains(adj)) {
                distances[adj] = current_distance + 1;
                q.push(adj);
                result[current_distance].push_back(DocAnnotation{
                    .source = adj,
                    .target = current,
                });
            }
            adjacent.incl(adj);
        }
    }

    return result;
}

int rowPadding = 6;

void update_row_positions(TreeGridDocument& doc) {
    __perf_trace("gui", "update row positions");
    int offset = 0;
    for (auto const& row : doc.flatRows(true)) {
        doc.rowPositions.resize_at(row->flatIdx) = offset;
        doc.rowOrigins.insert_or_assign(row->origin.uniq(), row->flatIdx);
        offset += row->getHeight(rowPadding).value_or(0);
    }
}

void add_description_list_node(
    StoryGridGraph&                       res,
    TreeGridDocument&                     doc,
    org::ImmAdapterT<org::ImmList> const& list,
    org::graph::MapGraph&                 graph,
    StoryGridContext&                     ctx) {
    org::graph::MapNode listNode{list.uniq()};
    for (auto const& item : list.subAs<org::ImmListItem>()) {
        graph.addNode(item.uniq());
        for (auto const& link : item.getHeader()->subAs<org::ImmLink>()) {
            if (link->isId()) {
                auto target = link.ctx->track->subtrees.get(
                    link.value().getId().text);
                for (auto const& targetPath :
                     link.ctx->getPathsFor(target.value())) {
                    CTX_MSG(fmt(
                        "List link {} -> {}", item.uniq(), targetPath));

                    res.annotationParents.insert_or_assign(
                        item.uniq(), list.uniq());
                    graph.addEdge(
                        org::graph::MapEdge{
                            .source = item.uniq(),
                            .target = org::graph::MapNode{targetPath},
                        },
                        org::graph::MapEdgeProp{});
                }
            }
        }
    }
}

void addFootnotes(
    UnorderedSet<org::ImmUniqId> visited,
    org::ImmUniqId const&        origin,
    org::ImmAdapter const&       node,
    org::graph::MapGraph&        graph,
    StoryGridContext&            ctx) {
    if (visited.contains(node.uniq())) {
        return;
    } else {
        visited.incl(node.uniq());
    }
    auto __scope = ctx.scopeLevel();
    for (auto const& recSub : node.getAllSubnodesDFS(node.path)) {
        Opt<org::ImmAdapterT<org::ImmLink>>
            link = recSub.asOpt<org::ImmLink>();

        if (!(link && link.value()->isFootnote())) { continue; }

        auto target = link->ctx->track->footnotes.get(
            link.value()->getFootnote().target);

        if (!target) { continue; }

        for (auto const& targetPath :
             link->ctx->getPathsFor(target.value())) {
            graph.addNode(targetPath);
            graph.addEdge(
                org::graph::MapEdge{
                    .source = origin,
                    .target = org::graph::MapNode{targetPath},
                },
                org::graph::MapEdgeProp{});

            addFootnotes(
                visited,
                targetPath,
                link->ctx->adapt(targetPath),
                graph,
                ctx);
        }
    }
};

void add_annotation_nodes(
    StoryGridGraph&       res,
    TreeGridDocument&     doc,
    org::graph::MapGraph& graph,
    StoryGridContext&     ctx) {

    for (auto const& row : doc.flatRows(true)) {
        org::graph::MapNode subtreeNode{row->origin.uniq()};
        graph.addNode(subtreeNode);
    }

    for (auto const& row : doc.flatRows(true)) {
        for (auto const& nested :
             row->origin.subAs<org::ImmBlockComment>()) {
            org::graph::MapNode subtreeNode{row->origin.uniq()};
            org::graph::MapNode commentNode{nested.uniq()};
            graph.addNode(commentNode);
            graph.addEdge(
                org::graph::MapEdge{
                    .source = subtreeNode,
                    .target = commentNode,
                },
                org::graph::MapEdgeProp{});

            UnorderedSet<org::ImmUniqId> visited;
            addFootnotes(visited, commentNode.id, nested, graph, ctx);
        }

        for (auto const& list : row->origin.subAs<org::ImmList>()) {
            if (list.isDescriptionList()
                && org::graph::isLinkedDescriptionList(list)) {
                add_description_list_node(res, doc, list, graph, ctx);
            }
        }
    }
}


int add_root_grid_node(StoryGridGraph& res, org::ImmAdapter const& node) {
    TreeGridDocument doc;
    doc.getColumn("title").width         = 200;
    doc.getColumn("event").width         = 400;
    doc.getColumn("note").width          = 200;
    doc.getColumn("turning_point").width = 300;
    doc.getColumn("value").width         = 200;
    doc.getColumn("location").width      = 240;
    doc.getColumn("location").edit = TreeGridColumn::EditMode::SingleLine;
    __perf_trace_begin("gui", "build doc rows");
    doc.rows = build_rows(node, doc);
    __perf_trace_end("gui");
    update_row_positions(doc);

    StoryGridNode::TreeGrid grid{
        .pos  = ImVec2(0, 0),
        .size = ImVec2(
            doc.getWidth(rowPadding), doc.getHeight(rowPadding)),
        .node = doc,
    };

    int flatIdx = res.addNode(0, grid.size, StoryGridNode{.data = grid});

    for (auto const& row : doc.flatRows(true)) {
        res.orgToId.insert_or_assign(
            row->origin.uniq(), res.getIrNode(flatIdx));
    }

    return flatIdx;
}

LaneNodePos get_partition_node(
    StoryGridGraph&        res,
    int                    lane,
    org::ImmAdapter const& node) {
    if (res.orgToId.contains(node.uniq())) {
        return res.orgToId.at(node.uniq());
    } else if (auto list = node.asOpt<org::ImmList>();
               list && list->isDescriptionList()
               && org::graph::isLinkedDescriptionList(node)) {
        StoryGridNode::LinkList text{};

        int width = 200;
        for (auto const& item : list->subAs<org::ImmListItem>()) {
            StoryGridNode::LinkList::Item listItem;
            listItem.node   = item;
            listItem.width  = width;
            listItem.text   = join(" ", org::flatWords(item));
            listItem.height = get_text_height(
                listItem.text,
                listItem.width,
                TreeGridColumn::EditMode::Multiline);
            text.items.push_back(listItem);
        }

        LaneNodePos annotation = res.ir.addNode(
            lane,
            ImVec2{
                static_cast<float>(text.getWidth() + rowPadding * 2),
                static_cast<float>(text.getHeight(rowPadding)),
            });

        for (auto const& item : text.items) {
            res.orgToId.insert_or_assign(item.node.uniq(), annotation);
        }

        res.orgToId.insert_or_assign(node.uniq(), annotation);
        res.nodes.push_back(StoryGridNode{text});
        res.addIrNode(res.nodes.high(), annotation);

        return annotation;

    } else {
        StoryGridNode::Text text{
            .node = node,
            .text = join(" ", flatWords(node)),
        };

        int width  = 200;
        int height = get_text_height(
            text.text, width, TreeGridColumn::EditMode::Multiline);
        text.size.x = width;
        text.size.y = height;

        res.nodes.push_back(StoryGridNode{text});
        LaneNodePos annotation = res.ir.addNode(
            lane, ImVec2(width, height));
        res.orgToId.insert_or_assign(node.uniq(), annotation);

        res.addIrNode(res.nodes.high(), annotation);

        return annotation;
    }
};

void connect_partition_edges(
    StoryGridGraph&                res,
    StoryGridState&                state,
    Vec<Vec<DocAnnotation>> const& partition,
    StoryGridContext&              ctx) {
    res.ir.edges.clear();
    for (auto const& [group_idx, group] : enumerate(partition)) {
        for (auto const& node : group) {
            org::ImmAdapter source = state.ast.context.adapt(
                node.source.id);
            org::ImmAdapter target = state.ast.context.adapt(
                node.target.id);

            LaneNodePos source_node = get_partition_node(
                res,
                group_idx + 1,
                state.ast.context.adapt(
                    res.annotationParents.get(node.source.id)
                        .value_or(node.source.id)));

            LaneNodePos target_node = get_partition_node(
                res, group_idx + 1, target);

            StoryGridNode const& source_flat = res.getDocNode(source_node);
            StoryGridNode const& target_flat = res.getDocNode(target_node);

            using GEC = GraphEdgeConstraint;

            LaneNodeEdge edge;
            edge.target = target_node;
            if (source_node.lane == target_node.lane) {
                edge.targetPort = GEC::Port::West;
                edge.sourcePort = GEC::Port::West;
            } else if (source_node.lane < target_node.lane) {
                edge.sourcePort = GEC::Port::East;
                edge.targetPort = GEC::Port::West;
            } else {
                edge.sourcePort = GEC::Port::West;
                edge.targetPort = GEC::Port::East;
            }

            auto get_connector_offset =
                [&ctx](
                    StoryGridNode const&   flat,
                    org::ImmAdapter const& node) -> Opt<int> {
                if (flat.isTreeGrid()) {
                    int row_idx = flat.getTreeGrid()
                                      .node.getRow(node.uniq())
                                      .value();
                    auto offset = flat.getTreeGrid()
                                      .node.getRowCenterOffset(row_idx);
                    return offset;
                } else if (flat.isLinkList()) {
                    // CTX_MSG(
                    //     fmt("node {} source parent {} target parent {}",
                    //         node,
                    //         doc.annotationParents.get(node.source.id),
                    //         doc.annotationParents.get(node.target.id)));
                    return flat.getLinkList().getRowOffset(node.uniq());

                    // CTX_MSG(fmt("edge {} -> {}", source_node, edge));
                } else {
                    return std::nullopt;
                }
            };


            edge.sourceOffset = get_connector_offset(source_flat, source);
            edge.targetOffset = get_connector_offset(target_flat, target);

            if (source_flat.isLinkList() || target_flat.isLinkList()) {
                CTX_MSG(fmt("{}", edge));
            }

            if (source_flat.isTreeGrid()
                && !res.isVisible(source.uniq())) {
                // pass
            } else {
                res.ir.addEdge(source_node, edge);
            }
        }
    }
}

void update_lane_offsets(
    LaneBlockGraph&  ir,
    ImVec2 const&    viewport,
    Vec<Slice<int>>& laneSpans,
    Vec<float>&      laneOffsets) {
    ir.visible.h = viewport.y;
    ir.visible.w = viewport.x;
    for (auto& stack : ir.lanes) { stack.resetVisibleRange(); }
    for (auto const& [lane_idx, offset] : enumerate(laneOffsets)) {
        if (ir.lanes.has(lane_idx)) {
            ir.lanes.at(lane_idx).scrollOffset = offset;
        }
    }

    int laneStartX = 0;
    for (auto const& [lane_idx, lane] : enumerate(ir.lanes)) {
        laneSpans.resize_at(lane_idx) = slice(
            laneStartX + lane.leftMargin,
            laneStartX + lane.leftMargin + lane.getWidth());
        laneStartX += lane.getFullWidth();
    }
}

void update_node_sizes(StoryGridGraph& rectGraph) {
    for (int i = 0; i < rectGraph.nodes.size(); ++i) {
        auto& node = rectGraph.nodes.at(i);
        if (node.isTreeGrid()) {
            int height = node.getTreeGrid().node.getHeight(rowPadding);
            int width  = node.getTreeGrid().node.getWidth(rowPadding);
            LaneNodePos pos             = rectGraph.getIrNode(i);
            rectGraph.ir.at(pos).height = height;
            rectGraph.ir.at(pos).width  = width;
            node.getTreeGrid().size     = ImVec2{
                static_cast<float>(width),
                static_cast<float>(height),
            };
        }
    }
}

void update_link_list_target_rows(StoryGridGraph& rectGraph) {
    if (rs::any_of(rectGraph.nodes, [](CR<StoryGridNode> n) {
            return n.isLinkList() && n.getLinkList().isSelected;
        })) {
        UnorderedSet<org::ImmUniqId> targets;
        for (auto const& node : rectGraph.nodes) {
            if (node.isLinkList() && node.getLinkList().isSelected) {
                for (auto const& item : node.getLinkList().items) {
                    for (auto const& target :
                         rectGraph.graph.adjList.at(item.node.uniq())) {
                        targets.incl(target.id);
                    }
                }
            }
        }

        Func<bool(TreeGridRow&)> aux;
        aux = [&](TreeGridRow& row) -> bool {
            if (targets.contains(row.origin.uniq())) {
                row.isVisible = true;
                return true;
            } else {
                bool hasVisibleNested = false;
                for (auto& sub : row.nested) {
                    if (aux(sub)) { hasVisibleNested = true; }
                }

                row.isVisible = hasVisibleNested;
                return hasVisibleNested;
            }
        };

        for (auto& node : rectGraph.nodes) {
            if (node.isTreeGrid()) {
                for (auto& row : node.getTreeGrid().node.rows) {
                    aux(row);
                }
                update_row_positions(node.getTreeGrid().node);
            }
        }
    } else {
        Func<void(TreeGridRow&)> aux;
        aux = [&](TreeGridRow& row) {
            row.isVisible = true;
            for (auto& sub : row.nested) { aux(sub); }
        };

        for (auto& node : rectGraph.nodes) {
            if (node.isTreeGrid()) {
                for (auto& row : node.getTreeGrid().node.rows) {
                    aux(row);
                }
                update_row_positions(node.getTreeGrid().node);
            }
        }
    }
}

void update_graph_layout(
    StoryGridGraph&           rectGraph,
    GraphLayoutIR::Result&    thisLayout,
    Opt<ColaConstraintDebug>& debug) {
    __perf_trace_begin("gui", "to doc layout");
    LaneBlockLayout lyt = to_layout(rectGraph.ir);
    __perf_trace_end("gui");
    // writeFile("/tmp/tmp_dump.json", to_json_eval(lyt).dump(2));
    lyt.ir.height = 10000;
    lyt.ir.width  = 10000;
    __perf_trace_begin("gui", "do cola layout");
    auto cola = lyt.ir.doColaLayout();
    __perf_trace_end("gui");
    __perf_trace_begin("gui", "do cola convert");
    thisLayout = cola.convert();
    __perf_trace_end("gui");

    cola.router->outputInstanceToSVG("/tmp/update_graph_layout");

    // writeFile("/tmp/lyt_dump.json",
    // to_json_eval(this->layout).dump(2));

    for (int i = 0; i < rectGraph.nodes.size(); ++i) {
        StoryGridNode&     node = rectGraph.nodes.at(i);
        LaneNodePos const& pos  = rectGraph.getIrNode(i);
        if (lyt.rectMap.contains(pos)) {
            node.isVisible  = true;
            auto const& rec = thisLayout.fixed.at(lyt.rectMap.at(pos));
            switch (node.getKind()) {
                case StoryGridNode::Kind::TreeGrid: {
                    node.getTreeGrid().pos.x = rec.left;
                    node.getTreeGrid().pos.y = rec.top;
                    break;
                }
                case StoryGridNode::Kind::Text: {
                    node.getText().pos.x = rec.left;
                    node.getText().pos.y = rec.top;
                    break;
                }
                case StoryGridNode::Kind::LinkList: {
                    node.getLinkList().pos.x = rec.left;
                    node.getLinkList().pos.y = rec.top;
                    break;
                }
            }
        } else {
            node.isVisible = false;
        }
    }


    // debug     = to_constraints(lyt, rectGraph.ir, thisLayout);
    // debug->ir = &thisLayout;
}

void StoryGridModel::updateDocument() {
    __perf_trace("gui", "update grid model");
    auto& ctx = conf;


    if (updateNeeded.contains(UpdateNeeded::Graph)) {
        __perf_trace("gui", "add grid nodes");
        rectGraph = StoryGridGraph{};

        int flat = add_root_grid_node(
            rectGraph, getCurrentState().ast.getRootAdapter());

        add_annotation_nodes(
            rectGraph,
            rectGraph.nodes.at(flat).getTreeGrid().node,
            rectGraph.graph,
            ctx);

        Vec<org::graph::MapNode> docNodes;
        for (auto const& row :
             rectGraph.nodes.at(flat).getTreeGrid().node.flatRows(true)) {
            auto tree = row->origin.uniq();
            if (!rectGraph.graph.adjList.at(tree).empty()
                || !rectGraph.graph.inNodes.at(tree).empty()) {
                docNodes.push_back(tree);
            }
        }

        rectGraph.partition = partition_graph_nodes(
            docNodes, rectGraph.graph);

        connect_partition_edges(
            rectGraph, getCurrentState(), rectGraph.partition, ctx);
    }

    if (updateNeeded.contains(UpdateNeeded::LinkListClick)) {
        update_link_list_target_rows(rectGraph);
        connect_partition_edges(
            rectGraph, getCurrentState(), rectGraph.partition, ctx);
        update_node_sizes(rectGraph);
    }

    if (updateNeeded.contains(UpdateNeeded::Scroll)) {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();


        for (auto& lane : rectGraph.ir.lanes) {
            for (auto& rect : lane.blocks) { rect.isVisible = true; }
        }


        update_lane_offsets(
            rectGraph.ir, viewport->WorkSize, laneSpans, laneOffsets);

        if (laneOffsets.has(0)) { shift.y = 20 + laneOffsets.at(0); }

        update_graph_layout(rectGraph, this->layout, this->debug);

        Slice<int> viewportRange = slice1<int>(0, viewport->WorkSize.y);
        for (auto const& [lane_idx, lane] :
             enumerate(rectGraph.ir.lanes)) {
            for (auto const& [block_idx, block] : enumerate(lane.blocks)) {
                LaneNodePos   lanePos{.lane = lane_idx, .row = block_idx};
                StoryGridNode storyNode = rectGraph.getDocNode(lanePos);
                if (storyNode.isTreeGrid()) {
                    TreeGridDocument treeDoc = storyNode.getTreeGrid()
                                                   .node;
                    for (auto const& row : treeDoc.flatRows(false)) {
                        Slice<int> rowRange = slice1<int>(
                            treeDoc.rowPositions.at(row->flatIdx)
                                + (laneOffsets.has(lane_idx)
                                       ? laneOffsets.at(lane_idx)
                                       : 0),
                            treeDoc.rowPositions.at(row->flatIdx)
                                + (laneOffsets.has(lane_idx)
                                       ? laneOffsets.at(lane_idx)
                                       : 0)
                                + row->getHeight().value());
                        org::ImmUniqId rowId = row->origin.uniq();
                        UnorderedSet<org::graph::MapNode> adjacent;
                        for (auto const& n :
                             rectGraph.graph.inNodes.at(rowId)) {
                            adjacent.incl(n);
                        }

                        for (auto const& n :
                             rectGraph.graph.adjList.at(rowId)) {
                            adjacent.incl(n);
                        }

                        auto overlap = rowRange.overlap(viewportRange);

                        for (auto const& n : adjacent) {
                            Opt<LaneNodePos>
                                targetNodePos = rectGraph.orgToId.get(
                                    n.id);

                            if (targetNodePos) {
                                auto const& t = targetNodePos.value();

                                if (overlap) {
                                    rectGraph.ir.at(t).isVisible = true;
                                } else {
                                    rectGraph.ir.at(t).isVisible = false;
                                }
                            }
                        }
                    }
                }
            }
        }

        update_graph_layout(rectGraph, this->layout, this->debug);
    }

    // writeFile("/tmp/debug_dump.json",
    // to_json_eval(this->debug).dump(2));
    updateNeeded.clear();
}

void StoryGridModel::apply(const GridAction& act) {
    switch (act.getKind()) {
        case GridAction::Kind::EditCell: {
            updateNeeded.incl(UpdateNeeded::Graph);
            updateNeeded.incl(UpdateNeeded::Scroll);
            auto edit = act.getEditCell();
            org::ImmAstVersion vNext = getCurrentState().ast.getEditVersion(
                [&](org::ImmAstContext& ast, org::ImmAstEditContext& ctx)
                    -> org::ImmAstReplaceGroup {
                    org::ImmAstReplaceGroup result;
                    result.incl(org::replaceNode(
                        edit.cell.getValue().origin,
                        ast.add(
                            sem::asOneNode(sem::parseString(edit.updated)),
                            ctx),
                        ctx));
                    return result;
                });
            history.push_back(StoryGridState{
                .ast = vNext,
            });
            break;
        }

        case GridAction::Kind::Scroll: {
            updateNeeded.incl(UpdateNeeded::Scroll);
            auto const& scroll = act.getScroll();
            for (auto const& [lane_idx, span] : enumerate(laneSpans)) {
                if (span.contains(scroll.pos.x)) {
                    laneOffsets.resize_at(lane_idx, 0.0f) //
                        += scroll.direction * 10;
                }
            }
            break;
        }

        case GridAction::Kind::LinkListClick: {
            updateNeeded.incl(UpdateNeeded::LinkListClick);
            updateNeeded.incl(UpdateNeeded::Scroll);
            break;
        }
    }
}

void StoryGridContext::message(
    const std::string& value,
    int                line,
    const char*        function,
    const char*        file) const {
    OperationsTracer::message(value, activeLevel, line, function, file);
}

Opt<int> TreeGridRow::getHeight(int padding) const {
    if (isVisible) {
        return rs::max(
                   own_view(columns.keys())
                   | rv::transform([&](Str const& col) {
                         return columns.at(col).height;
                     }))
             + padding;
    } else {
        return std::nullopt;
    }
}

Opt<int> TreeGridRow::getHeightRec(int padding) const {
    if (isVisible) {
        return getHeight(padding).value()
             + rs::fold_left(
                   nested | rv::transform([&](TreeGridRow const& r) {
                       return r.getHeightRec(padding).value_or(0);
                   }),
                   0,
                   [](int lhs, int rhs) { return lhs + rhs; });
    } else {
        return std::nullopt;
    }
}
