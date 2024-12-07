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
#include <haxorg/sem/ImmOrg.hpp>
#include <haxorg/sem/SemOrgFormat.hpp>
#include "org_logger.hpp"

#include <haxorg/sem/ImmOrgGraphBoost.hpp>
#include <gui_lib/scintilla_editor_widget.hpp>

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


DECL_DESCRIBED_ENUM_STANDALONE(
    EditableTextResult,
    None,
    Changed,
    StartedEditing,
    CancelledEditing);

EditableTextResult render_editable_text(
    std::string&             value,
    std::string&             edit_buffer,
    bool&                    is_editing,
    ImVec2 const&            size,
    TreeGridColumn::EditMode edit) {
    auto __scope = IM_SCOPE_BEGIN(
        "Editable text",
        fmt("size:{} editing:{} buffer:{}",
            size,
            is_editing,
            escape_literal(edit_buffer)));

    auto cell_prefix = fmt("{:p}", static_cast<const void*>(value.data()));

    auto get_editor = [&](const ImVec2& size) {
        auto res = ImGui::ScInputText(c_fmt(
            "sci_editor_{:p}", static_cast<const void*>(value.data())));
        res->Resize(size);
        return res;
    };

    if (edit == TreeGridColumn::EditMode::Multiline) {
        if (is_editing) {
            auto this_size = size - ImVec2(0, 40);
            render_debug_rect(this_size, IM_COL32(255, 0, 0, 255));
            auto ed = get_editor(this_size);
            ed->HandleInput();
            ed->Render();
            IM_FN_PRINT("Render done", "");

            if (IM_FN_EXPR(Button, "done")) {
                value      = ed->GetText();
                is_editing = false;
                return EditableTextResult::Changed;
            } else if (ImGui::SameLine(); IM_FN_EXPR(Button, "cancel")) {
                is_editing = false;
                return EditableTextResult::CancelledEditing;
            } else {
                return EditableTextResult::None;
            }


        } else {
            auto frameless_vars = push_frameless_window_vars();
            ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + size.x);
            // NOTE: Using ID with runtime formatting here because
            // there is more than one cell that might potentially be
            // edited.
            if (IM_FN_BEGIN(
                    BeginChild,
                    fmt("##{}_wrap", cell_prefix).c_str(),
                    size,
                    ImGuiChildFlags_None,
                    ImGuiWindowFlags_NoScrollbar)) {
                IM_FN_PRINT("Child", fmt("size:{}", size));
                ImGui::PushID(fmt("##{}_view", cell_prefix).c_str());
                IM_FN_STMT(TextWrapped, "%s", value.c_str());
                IM_FN_PRINT("Wrapped text", value);
                ImGui::PopID();
            }

            IM_FN_END(EndChild);

            ImGui::PopTextWrapPos();
            ImGui::PopStyleVar(frameless_vars);

            if (ImGui::IsItemClicked()) {
                is_editing = true;
                auto ed    = get_editor(size);
                ed->WrapOnChar();
                ed->HideAllMargins();
                ed->SetText(value);
                return EditableTextResult::StartedEditing;
            } else {
                return EditableTextResult::None;
            }
        }
    } else {
        if (is_editing) {
            if (ImGui::Button("OK")) {
                value      = edit_buffer;
                is_editing = false;
                return EditableTextResult::Changed;
            } else if (ImGui::SameLine(0.0f, 0.0f); ImGui::Button("X")) {
                is_editing = false;
                return EditableTextResult::CancelledEditing;
            } else {
                ImGui::SameLine(0.0f, 0.0f);
                ImGui::SetNextItemWidth(size.x);
                ImGui::InputText(
                    fmt("##{}_edit", cell_prefix).c_str(), &edit_buffer);
                return EditableTextResult::None;
            }

        } else {
            IM_FN_STMT(Text, "%s", value.c_str());
            IM_FN_PRINT("Text render", value);
            if (ImGui::IsItemClicked()) {
                is_editing  = true;
                edit_buffer = value;
                return EditableTextResult::StartedEditing;
            } else {
                return EditableTextResult::None;
            }
        }
    }
}

EditableTextResult render_editable_cell(
    TreeGridCell&         cell,
    StoryGridContext&     ctx,
    TreeGridColumn const& col) {
    auto& val = cell.getValue();
    return render_editable_text(
        val.value,
        val.edit_buffer,
        val.is_editing,
        cell.getSize(),
        col.edit);
}


void render_cell(
    TreeGridRow&          row,
    TreeGridCell&         cell,
    StoryGridContext&     ctx,
    TreeGridColumn const& col,
    ImVec2 const&         pos,
    int                   documentNodeIdx) {

    IM_FN_PRINT("Cell", fmt("pos:{} size:{}", pos, cell.getSize()));
    ImGui::SetNextWindowPos(pos);
    if (IM_FN_BEGIN(
            BeginChild,
            c_fmt("cell_{}_{}", row.flatIdx, col.name),
            cell.getSize(),
            ImGuiChildFlags_Borders,
            ImGuiWindowFlags_NoScrollbar)) {
        auto res = render_editable_cell(cell, ctx, col);
        switch (res) {
            case EditableTextResult::Changed: {
                ctx.action(GridAction::EditCell{
                    .cell    = cell,
                    .updated = cell.getValue().value,
                });
                [[fallthrough]];
            }
            case EditableTextResult::CancelledEditing: [[fallthrough]];
            case EditableTextResult::StartedEditing: {
                ctx.action(GridAction::EditCellChanged{
                    .cell            = cell,
                    .documentNodeIdx = documentNodeIdx,
                });
                break;
            }
            default: {
            };
        }
    }

    IM_FN_END(EndChild);
}

void render_tree_columns(
    TreeGridRow&      row,
    TreeGridDocument& doc,
    StoryGridContext& ctx,
    int               documentNodeIdx,
    ImVec2 const&     gridStart) {
    auto __scope = ctx.scopeLevel();
    int  colIdx  = 1;
    for (auto const& col : doc.columns) {
        if (row.columns.contains(col.name)) {
            auto __scope = ctx.scopeLevel();
            render_cell(
                row,
                row.columns.at(col.name),
                ctx,
                col,
                gridStart + doc.getCellPos(row.flatIdx, col.name),
                documentNodeIdx);
        }
        ++colIdx;
    }
}

void render_tree_row(
    TreeGridRow&           row,
    TreeGridDocument&      doc,
    StoryGridContext&      ctx,
    StoryGridConfig const& conf,
    int                    documentNodeIdx,
    ImVec2 const&          gridStart) {
    // row is completely invisible, including its nested sub-rows
    if (!row.isVisible) { return; }
    bool skipped = false;
    auto __scope = ctx.scopeLevel();

    if (skipped && row.nested.empty()) { return; };

    auto __im_scope = IM_SCOPE_BEGIN(
        "Tree row", fmt("row [{}]", row.flatIdx));

    if (!row.nested.empty()) {
        render_tree_columns(row, doc, ctx, documentNodeIdx, gridStart);
        if (row.isOpen) {
            for (auto& sub : row.nested) {
                render_tree_row(
                    sub, doc, ctx, conf, documentNodeIdx, gridStart);
            }
        }
    } else if (!skipped) {
        render_tree_columns(row, doc, ctx, documentNodeIdx, gridStart);
    }

    ImRect cell_rect = ImRect(
        gridStart + ImVec2(0, doc.getRowYPos(row)),
        gridStart
            + ImVec2(
                doc.treeFoldWidth,
                doc.getRowYPos(row) + row.getHeight().value_or(0)));

    if (cell_rect.Contains(ImGui::GetMousePos())) {
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
            ImGui::OpenPopup(fmt("ctx_{}", row.origin.id).c_str());
        }
    }

    if (ImGui::BeginPopup(fmt("ctx_{}", row.origin.id).c_str())) {
        if (ImGui::MenuItem("Copy")) {
            if (row.origin->treeId.get().has_value()) {
                ImGui::SetClipboardText(
                    row.origin->treeId->value().c_str());
            }
        }
        ImGui::EndPopup();
    }

    ImVec2 cell_max  = cell_rect.Max;
    ImVec2 rect_size = ImVec2(
        std::ceil(
            ((6 - row.origin->level) / 6.0f)
            * (cell_rect.Max.x - cell_rect.Min.x)),
        cell_rect.Max.y - cell_rect.Min.y);
    float  pad      = 2.0f;
    ImVec2 rect_min = cell_max - rect_size + ImVec2(pad, pad);
    ImVec2 rect_max = cell_max - ImVec2(pad, pad);

    if (ImGui::IsMouseHoveringRect(cell_rect.Min, cell_rect.Max)) {
        ImGui::GetWindowDrawList()->AddRect(
            rect_min,
            rect_max,
            conf.foldCellHoverBackground,
            0.0f,
            0,
            1.0f);
        if (ImGui::IsMouseClicked(0)) {
            row.isOpen = !row.isOpen;
            ctx.action(GridAction::RowFolding{
                .isOpen          = row.isOpen,
                .flatIdx         = row.flatIdx,
                .documentNodeIdx = documentNodeIdx,
            });
        }
    }

    ImGui::GetWindowDrawList()->AddRectFilled(
        rect_min, rect_max, conf.foldCellBackground);
}

void render_text_node(
    StoryGridModel&        model,
    StoryGridNode::Text&   text,
    LaneNodePos const&     selfPos,
    StoryGridConfig const& conf) {
    auto& ctx = model.ctx;


    ImGui::PushStyleColor(ImGuiCol_WindowBg, conf.annotationNodeWindowBg);
    auto frameless_vars = push_frameless_window_vars();
    ImGui::SetNextWindowPos(text.pos + model.shift);
    ImGui::SetNextWindowSize(text.getSize());
    if (IM_FN_BEGIN(
            Begin,
            fmt("##{:p}", static_cast<const void*>(text.text.data()))
                .c_str(),
            nullptr,
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize)) {
        ImGui::BringWindowToDisplayFront(ImGui::GetCurrentWindow());

        auto res = render_editable_text(
            text.text,
            text.edit_buffer,
            text.edit,
            text.getSize(),
            TreeGridColumn::EditMode::Multiline);

        if (res != EditableTextResult::None) {
            CTX_MSG(fmt("Text edit result {}", res));
        }

        switch (res) {
            case EditableTextResult::Changed: {
                ctx.action(GridAction::EditNodeText{
                    .pos     = selfPos,
                    .updated = text.text,
                });
                [[fallthrough]];
            }
            case EditableTextResult::CancelledEditing: [[fallthrough]];
            case EditableTextResult::StartedEditing: {
                ctx.action(GridAction::EditNodeChanged{
                    .pos = selfPos,
                });
                break;
            }
            default: {
            };
        }

        IM_FN_END(End);
    }

    ImGui::PopStyleVar(frameless_vars);
    ImGui::PopStyleColor();
}

void render_list_node(
    StoryGridModel&          model,
    StoryGridNode::LinkList& list) {
    auto frameless_vars = push_frameless_window_vars();
    ImGui::SetNextWindowPos(list.pos + model.shift);
    ImGui::SetNextWindowSize(list.getSize());
    if (IM_FN_BEGIN(
            Begin,
            fmt("##{:p}", static_cast<const void*>(&list)).c_str(),
            nullptr,
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize)) {

        if (ImGui::IsWindowHovered(
                ImGuiHoveredFlags_RootAndChildWindows
                | ImGuiHoveredFlags_AllowWhenBlockedByPopup
                | ImGuiHoveredFlags_AllowWhenBlockedByActiveItem)
            && ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
            list.isSelected = !list.isSelected;
            model.ctx.action(GridAction::LinkListClick{});
        }

        if (IM_FN_BEGIN(
                BeginTable,
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
                    ImVec2(item.height, item.width),
                    TreeGridColumn::EditMode::Multiline);
            }
            IM_FN_END(EndTable);
        }
        IM_FN_END(End);
    }

    ImGui::PopStyleVar(frameless_vars);
}

void render_table(
    StoryGridModel&          model,
    StoryGridNode::TreeGrid& grid,
    StoryGridConfig const&   conf,
    int                      documentNodeIdx) {
    auto& doc       = grid.node;
    auto& ctx       = model.ctx;
    auto  gridStart = ImGui::GetCursorScreenPos();
    auto  gridSize  = doc.getSize();

    // Table for the story grid node is drawn as a small floating window
    // that is overlaid exactly on top of the existing bar. I have no
    // fucking idea how to make the table header stick while scrolling
    // (yes, I saw the github replies etc., they don't work). Floating
    // window obviously solves this issue, as it is positioned completely
    // independently of the content in the grid table itself.
    ImGui::SetNextWindowPos(ImVec2(grid.pos + model.shift));
    ImGui::SetNextWindowSize(ImVec2(grid.node.getWidth(), 20));
    auto frameless_vars = push_frameless_window_vars();
    if (IM_FN_BEGIN(
            Begin,
            "HeaderOverlay",
            nullptr,
            ImGuiWindowFlags_NoDecoration
                | ImGuiWindowFlags_AlwaysAutoResize
                | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize
                | ImGuiWindowFlags_NoScrollbar
                | ImGuiWindowFlags_NoScrollWithMouse)) {
        ImGui::BringWindowToDisplayFront(ImGui::GetCurrentWindow());
        for (auto const& [idx, col] : enumerate(doc.columns)) {
            ImGui::GetWindowDrawList()->AddText(
                gridStart + ImVec2(doc.colPositions.at(idx), 0),
                IM_COL32(255, 255, 255, 255),
                col.name.data(),
                col.name.data() + col.name.size());
        }

        IM_FN_END(End);
    }
    ImGui::PopStyleVar(frameless_vars);

    // render_debug_rect(ImRect(gridStart, gridStart + gridSize));
    ImGui::SetNextWindowPos(gridStart);
    if (IM_FN_BEGIN(
            BeginChild,
            "table_ch",
            gridSize,
            ImGuiChildFlags_Borders,
            ImGuiWindowFlags_NoScrollbar
                | ImGuiWindowFlags_NoBackground)) {
        for (auto& sub : doc.rows) {
            render_tree_row(
                sub, doc, ctx, conf, documentNodeIdx, gridStart);
        }
    }
    IM_FN_END(EndChild);
}

void render_table_node(
    StoryGridModel&          model,
    StoryGridNode::TreeGrid& grid,
    StoryGridConfig const&   conf,
    int                      documentNodeIdx) {

    auto& ctx = model.ctx;
    auto& doc = grid.node;

    ImGui::SetNextWindowPos(grid.pos + model.shift);
    ImGui::SetNextWindowSize(
        grid.node.getSize() + ImVec2(0, doc.tableHeaderHeight));
    auto frameless_vars = push_frameless_window_vars();
    // Table is drawn in a separate window so it could have the widgets
    // inside, but otherwise is positioned completely independently on the
    // screen.
    if (IM_FN_BEGIN(
            Begin,
            "Standalone Table Window",
            nullptr,
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize)) {
        ImGui::BringWindowToDisplayFront(ImGui::GetCurrentWindow());
        render_table(model, grid, conf, documentNodeIdx);

        IM_FN_END(End);
    }
    ImGui::PopStyleVar(frameless_vars);
}

void run_story_grid_annotated_cycle(
    StoryGridModel&        model,
    StoryGridConfig const& conf) {
    __perf_trace("gui", "grid model render");
    for (int i = 0; i < model.rectGraph.nodes.size(); ++i) {
        auto& node = model.rectGraph.nodes.at(i);
        if (node.isVisible) {
            switch (node.getKind()) {
                case StoryGridNode::Kind::TreeGrid: {
                    render_table_node(model, node.getTreeGrid(), conf, i);
                    break;
                }
                case StoryGridNode::Kind::Text: {
                    render_text_node(
                        model,
                        node.getText(),
                        model.rectGraph.gridNodeToNode.at(i),
                        conf);
                    break;
                }
                case StoryGridNode::Kind::LinkList: {

                    render_list_node(model, node.getLinkList());
                    break;
                }
            }
        }
    }

    for (auto const& [key, edge] : model.layout.lines) {
        render_edge(edge, model.shift, true, conf.blockGraphConf);
    }
}

TreeGridDocument getInitRootDoc(StoryGridConfig const& conf) {
    TreeGridDocument doc;
    for (auto const& column : conf.defaultColumns) {
        if (column.width) {
            doc.getColumn(column.name).width = column.width.value();
        }

        if (column.edit) {
            doc.getColumn(column.name).edit = column.edit.value();
        }
    }

    return doc;
}

Opt<json> story_grid_loop(
    GLFWwindow*            window,
    std::string const&     file,
    const Opt<json>&       in_state,
    StoryGridConfig const& conf) {
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
    model.history.push_back(StoryGridHistory{
        .ast = start.init(sem::parseString(readFile(file))),
    });

    model.ctx.setTraceFile("/tmp/story_grid_trace.txt");
    if (in_state) {
        model.state = from_json_eval<StoryGridState>(in_state.value());
    }


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
            model.history.push_back(StoryGridHistory{
                .ast = start.init(sem::parseString(readFile(file))),
            });
            model.updateNeeded.incl(StoryGridModel::UpdateNeeded::Graph);
            model.updateNeeded.incl(StoryGridModel::UpdateNeeded::Scroll);
            model.updateDocument(getInitRootDoc(conf), conf);
        }

        frame_start();

        auto frameless_vars = push_frameless_window_vars();
        fullscreen_window_begin();

        if (first) {
            first = false;
            model.updateNeeded.incl(StoryGridModel::UpdateNeeded::Graph);
            model.updateNeeded.incl(StoryGridModel::UpdateNeeded::Scroll);
            model.updateDocument(getInitRootDoc(conf), conf);
        }

        if (model.debug) {
            render_debug(model.debug.value(), model.shift);
        }

        run_story_grid_cycle(model, conf);

        ImGui::End();
        ImGui::PopStyleVar(frameless_vars);

        frame_end(window);

        apply_story_grid_changes(model, getInitRootDoc(conf), conf);
    }

    inotify_rm_watch(inotify_fd, watch_descriptor);
    close(inotify_fd);

    return to_json_eval(model.state);
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
    const org::graph::MapGraph&     graph,
    StoryGridContext&               ctx) {
    __perf_trace("gui", "partition graph by distance");
    CTX_MSG(fmt("Partition graph nodes, initial nodes {}", initial_nodes));
    auto __scope = ctx.scopeLevel();


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

        for (org::graph::MapNode const& adj : graph.inNodes(current)) {
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

    Vec<int> partition_debug //
        = result
        | rv::transform([](auto const& p) -> int { return p.size(); })
        | rs::to<Vec>();

    CTX_MSG(
        fmt("Created partition with {} lanes {} nodes",
            partition_debug.size(),
            partition_debug));

    return result;
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
            if (link->target.isId()) {
                auto target = link.ctx->track->subtrees.get(
                    link.value().target.getId().text);
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

void add_footnote_annotation_node(
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
    CTX_MSG(fmt("Footnotes from {}", origin.id));
    auto __scope = ctx.scopeLevel();
    for (auto const& recSub : node.getAllSubnodesDFS(node.path)) {
        Opt<org::ImmAdapterT<org::ImmLink>>
            link = recSub.asOpt<org::ImmLink>();

        if (!(link && link.value()->target.isFootnote())) { continue; }

        auto target = link->ctx->track->footnotes.get(
            link.value()->target.getFootnote().target);

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

            CTX_MSG(
                fmt("Found recursive target, {} is targeting {}",
                    targetPath.id,
                    link->ctx->adapt(targetPath).id));

            add_footnote_annotation_node(
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
    CTX_MSG("Add annotation nodes to document");
    auto __scope = ctx.scopeLevel();

    for (auto const& row : doc.flatRows(true)) {
        org::graph::MapNode subtreeNode{row->origin.uniq()};
        graph.addNode(subtreeNode);
    }

    for (auto const& row : doc.flatRows(true)) {
        CTX_MSG(fmt("Nested elements for row {}", row->origin));
        for (auto const& sub : row->origin.sub()) {
            CTX_MSG(fmt("- Nested {}", sub));
        }
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
            add_footnote_annotation_node(
                visited, commentNode.id, nested, graph, ctx);
        }

        for (auto const& list : row->origin.subAs<org::ImmList>()) {
            if (list.isDescriptionList()
                && org::graph::isLinkedDescriptionList(list)) {
                add_description_list_node(res, doc, list, graph, ctx);
            }
        }
    }
}


int add_root_grid_node(
    StoryGridGraph&         res,
    org::ImmAdapter const&  node,
    TreeGridDocument const& init_doc,
    StoryGridContext&       ctx,
    StoryGridConfig const&  conf) {
    TreeGridDocument doc = init_doc;
    __perf_trace_begin("gui", "build doc rows");
    doc.rows = build_rows(node, doc);
    __perf_trace_end("gui");
    doc.resetGridStatics();


    CTX_MSG(
        fmt("Add root node to the document, grid size={} "
            "row-count={} col-count={} columns={}",
            doc.getSize(),
            doc.rowPositions.size(),
            doc.columns.size(),
            doc.columns));

    StoryGridNode::TreeGrid grid{
        .pos  = ImVec2(0, 0),
        .node = doc,
    };

    int flatIdx = res.addNode(
        0,
        doc.getSize(),
        StoryGridNode{.data = grid},
        conf.blockGraphConf);

    for (auto const& row : doc.flatRows(true)) {
        res.orgToId.insert_or_assign(
            row->origin.uniq(), res.getIrNode(flatIdx));
    }

    return flatIdx;
}

LaneNodePos get_partition_node(
    org::ImmAstVersion const& ast,
    StoryGridGraph&           res,
    int                       lane,
    org::ImmAdapter const&    node,
    StoryGridConfig const&    conf,
    StoryGridContext&         ctx) {
    if (res.orgToId.contains(node.uniq())) {
        auto annotation = res.orgToId.at(node.uniq());
        CTX_MSG(fmt("Node {} already mapped to {}", node.id, annotation));
        return annotation;
    } else if (auto list = node.asOpt<org::ImmList>();
               list && list->isDescriptionList()
               && org::graph::isLinkedDescriptionList(node)) {
        StoryGridNode::LinkList text{};

        for (auto const& item : list->subAs<org::ImmListItem>()) {
            StoryGridNode::LinkList::Item listItem;
            listItem.node   = item;
            listItem.width  = conf.annotationNodeWidth;
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
                static_cast<float>(
                    text.getWidth() + conf.laneRowPadding * 2),
                static_cast<float>(text.getHeight()),
            },
            conf.blockGraphConf);

        CTX_MSG(fmt("List {} mapped to IR node {}", node.id, annotation));

        for (auto const& item : text.items) {
            res.orgToId.insert_or_assign(item.node.uniq(), annotation);
        }

        res.orgToId.insert_or_assign(node.uniq(), annotation);
        res.nodes.push_back(StoryGridNode{text});
        res.addIrNode(res.nodes.high(), annotation);

        return annotation;

    } else {

        sem::SemId<sem::Org> sem_ast = org::sem_from_immer(
            node.id, ast.context);

        StoryGridNode::Text text{
            .origin = node,
            .text   = sem::Formatter::format(sem_ast),
        };

        int width  = conf.annotationNodeWidth;
        int height = get_text_height(
            text.text, width, TreeGridColumn::EditMode::Multiline);
        text.size.x = width;
        text.size.y = height;

        res.nodes.push_back(StoryGridNode{text});
        LaneNodePos annotation = res.ir.addNode(
            lane, ImVec2(width, height), conf.blockGraphConf);
        CTX_MSG(
            fmt("Text node {} mapped to IR node {}", node.id, annotation));
        res.orgToId.insert_or_assign(node.uniq(), annotation);

        res.addIrNode(res.nodes.high(), annotation);

        return annotation;
    }
};

void connect_partition_edges(
    StoryGridModel&                model,
    Vec<Vec<DocAnnotation>> const& partition,
    StoryGridConfig const&         conf) {
    auto& res   = model.rectGraph;
    auto& state = model.getLastHistory();
    auto& ctx   = model.ctx;


    CTX_MSG("Connecting partition edges");
    auto __scope = ctx.scopeLevel();
    for (auto const& p : partition) {
        CTX_MSG(fmt("Partition {}", p.size()));
    }

    res.ir.edges.clear();
    for (auto const& [group_idx, group] : enumerate(partition)) {
        for (auto const& node : group) {
            org::ImmAdapter source = state.ast.context.adapt(
                node.source.id);
            org::ImmAdapter target = state.ast.context.adapt(
                node.target.id);

            auto source_parent = state.ast.context.adapt(
                res.annotationParents.get(node.source.id)
                    .value_or(node.source.id));

            LaneNodePos source_node = get_partition_node(
                state.ast,
                res,
                group_idx + 1,
                source_parent,
                conf,
                model.ctx);

            LaneNodePos target_node = get_partition_node(
                state.ast, res, group_idx + 1, target, conf, model.ctx);

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
                    return flat.getLinkList().getRowCenterOffset(
                        flat.getLinkList().getRow(node.uniq()));

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

void update_node_sizes(StoryGridGraph& rectGraph) {
    for (int i = 0; i < rectGraph.nodes.size(); ++i) {
        auto& node = rectGraph.nodes.at(i);
        if (node.isTreeGrid()) {
            int         height = node.getTreeGrid().node.getHeight();
            int         width  = node.getTreeGrid().node.getWidth();
            LaneNodePos pos    = rectGraph.getIrNode(i);
            rectGraph.ir.at(pos).height = height;
            rectGraph.ir.at(pos).width  = width;
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
            row.isVisible = false;
            if (targets.contains(row.origin.uniq())) {
                row.isVisible = true;
            }

            for (auto& sub : row.nested) {
                if (aux(sub)) { row.isVisible = true; }
            }

            return row.isVisible;
        };

        for (auto& node : rectGraph.nodes) {
            if (node.isTreeGrid()) {
                for (auto& row : node.getTreeGrid().node.rows) {
                    aux(row);
                }
                node.getTreeGrid().node.resetGridStatics();
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
                node.getTreeGrid().node.resetGridStatics();
            }
        }
    }
}

void update_graph_layout(StoryGridModel& model) {
    __perf_trace_begin("gui", "to doc layout");
    auto& rectGraph = model.rectGraph;

    for (auto const& [flat_idx, lane_idx] : rectGraph.gridNodeToNode) {
        auto size = rectGraph.nodes.at(flat_idx).getSize();
        rectGraph.ir.at(lane_idx).width  = size.x;
        rectGraph.ir.at(lane_idx).height = size.y;
    }

    LaneBlockLayout lyt = to_layout(rectGraph.ir);
    __perf_trace_end("gui");
    // writeFile("/tmp/tmp_dump.json", to_json_eval(lyt).dump(2));
    lyt.ir.height = 10000;
    lyt.ir.width  = 10000;
    __perf_trace_begin("gui", "do cola layout");
    auto cola = lyt.ir.doColaLayout();
    __perf_trace_end("gui");
    __perf_trace_begin("gui", "do cola convert");
    model.layout = cola.convert();
    __perf_trace_end("gui");

    // writeFile("/tmp/lyt_dump.json",
    // to_json_eval(this->layout).dump(2));

    int pad = rectGraph.ir.lanes.at(0).leftMargin;

    for (auto const& [key, edge] : model.layout.lines) {
        for (auto& path : model.layout.lines.at(key).paths) {
            for (auto& point : path.points) { point.x += pad; }
        }
    }

    for (int i = 0; i < rectGraph.nodes.size(); ++i) {
        StoryGridNode&     node = rectGraph.nodes.at(i);
        LaneNodePos const& pos  = rectGraph.getIrNode(i);
        if (lyt.rectMap.contains(pos)) {
            node.isVisible  = true;
            auto const& rec = model.layout.fixed.at(lyt.rectMap.at(pos));
            switch (node.getKind()) {
                case StoryGridNode::Kind::TreeGrid: {
                    node.getTreeGrid().pos.x = rec.left + pad;
                    node.getTreeGrid().pos.y = rec.top;
                    break;
                }
                case StoryGridNode::Kind::Text: {
                    node.getText().pos.x = rec.left + pad;
                    node.getText().pos.y = rec.top;
                    break;
                }
                case StoryGridNode::Kind::LinkList: {
                    node.getLinkList().pos.x = rec.left + pad;
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

void update_hidden_row_connections(
    StoryGridModel&        model,
    StoryGridConfig const& conf) {
    auto& ir = model.rectGraph.ir;

    Slice<int> viewportRange = slice1<int>(0, conf.gridViewport.y);
    for (auto const& [lane_idx, lane] :
         enumerate(model.rectGraph.ir.lanes)) {
        for (auto const& [block_idx, block] : enumerate(lane.blocks)) {
            LaneNodePos   lanePos{.lane = lane_idx, .row = block_idx};
            StoryGridNode storyNode = model.rectGraph.getDocNode(lanePos);
            // if individual node is a story grid it can have edges
            // connected at any part of the shape, and they might be
            // scrolled out of the view even if the grid itself is
            // partially visible.
            if (storyNode.isTreeGrid()) {
                TreeGridDocument treeDoc = storyNode.getTreeGrid().node;
                // so the code goes over each visible row, collecting the
                // positions relative to the *block graph layout basis*
                for (auto const& row : treeDoc.flatRows(false)) {
                    Slice<int> rowRange = slice1<int>(
                        treeDoc.getRowYPos(*row)
                            + (ir.lanes.has(lane_idx)
                                   ? ir.lanes.at(lane_idx).scrollOffset
                                   : 0),
                        treeDoc.getRowYPos(*row)
                            + (ir.lanes.has(lane_idx)
                                   ? ir.lanes.at(lane_idx).scrollOffset
                                   : 0)
                            + row->getHeight().value());
                    org::ImmUniqId rowId = row->origin.uniq();
                    UnorderedSet<org::graph::MapNode> adjacent;
                    for (auto const& n :
                         model.rectGraph.graph.inNodes(rowId)) {
                        adjacent.incl(n);
                    }

                    for (auto const& n :
                         model.rectGraph.graph.outNodes(rowId)) {
                        adjacent.incl(n);
                    }

                    auto overlap = rowRange.overlap(viewportRange);

                    for (auto const& n : adjacent) {
                        Opt<LaneNodePos> targetNodePos = model.rectGraph
                                                             .orgToId.get(
                                                                 n.id);

                        if (targetNodePos) {
                            auto const& t = targetNodePos.value();

                            if (overlap) {
                                model.rectGraph.ir.at(t).isVisible = true;
                            } else {
                                model.rectGraph.ir.at(t).isVisible = false;
                            }
                        }
                    }
                }
            }
        }
    }
}

void update_document_scroll(
    StoryGridModel&        model,
    StoryGridConfig const& conf) {
    auto& ctx = model.ctx;
    auto& ir  = model.rectGraph.ir;

    {
        Vec<int> offsets //
            = ir.lanes
            | rv::transform([](LaneBlockStack const& lane) -> int {
                  return lane.scrollOffset;
              })
            | rs::to<Vec>();

        CTX_MSG(fmt("Update document scrolling, offsets: {}", offsets));
    }

    ir.visible.h = conf.gridViewport.y;
    ir.visible.w = conf.gridViewport.x;

    for (auto& lane : ir.lanes) {
        for (auto& rect : lane.blocks) { rect.isVisible = true; }
    }

    for (auto& stack : ir.lanes) { stack.resetVisibleRange(); }

    // use first line as a basis for arranging all other node positions.
    if (ir.lanes.has(0)) { model.shift.y = ir.lanes.at(0).scrollOffset; }

    update_graph_layout(model);
    update_hidden_row_connections(model, conf);
    update_graph_layout(model);
}

void update_document_graph(
    StoryGridModel&         model,
    StoryGridConfig const&  conf,
    TreeGridDocument const& init_doc) {
    __perf_trace("gui", "add grid nodes");
    model.rectGraph = StoryGridGraph{};
    auto& rg        = model.rectGraph;
    auto& ctx       = model.ctx;

    rg.graph.clear();

    auto __log_scoped = OLOG_SINK_FACTORY_SCOPED([counter = 0]() mutable {
        auto file = fmt(
            "/tmp/connect_partition_edges_log_{}.log", ++counter);
        LOG(INFO) << "Created scoped file in " << file;
        return ::org_logging::init_file_sink(file);
    });

    CTX_MSG("Update document graph");
    auto __scope = ctx.scopeLevel();

    int docNodeIndex = add_root_grid_node(
        rg,
        model.getLastHistory().ast.getRootAdapter(),
        init_doc,
        model.ctx,
        conf);

    add_annotation_nodes(
        rg,
        rg.nodes.at(docNodeIndex).getTreeGrid().node,
        rg.graph,
        model.ctx);

    CTX_MSG(fmt("Graph with {} nodes", rg.nodes.size()));
    CTX_MSG(fmt("Graph adjacency list {}", rg.graph.adjList));
    CTX_MSG(fmt("Graph adjacency list in {}", rg.graph.adjListIn));


    Vec<org::graph::MapNode> docNodes;
    for (TreeGridRow* row :
         rg.nodes.at(docNodeIndex).getTreeGrid().node.flatRows(true)) {
        if (model.state.folded.contains(docNodeIndex)) {
            auto path = row->getOriginPath();
            if (model.state.folded.at(docNodeIndex).contains(path)) {
                row->isOpen = model.state.folded.at(docNodeIndex).at(path);
            }
        }
        auto tree = row->origin.uniq();
        if (!rg.graph.adjList.at(tree).empty()
            || !rg.graph.inNodes(tree).empty()) {
            docNodes.push_back(tree);
        }
    }

    rg.partition = partition_graph_nodes(docNodes, rg.graph, ctx);

    connect_partition_edges(model, rg.partition, conf);

    {
        int ir_nodes = 0;
        for (auto const& lane : rg.ir.lanes) {
            ir_nodes += lane.blocks.size();
        }

        CTX_MSG(fmt("IR graph {}", ir_nodes));
    }
}

void StoryGridModel::updateDocument(
    TreeGridDocument const& init_doc,
    StoryGridConfig const&  conf) {
    __perf_trace("gui", "update grid model");
    CTX_MSG("Update story grid document");
    auto __scope = ctx.scopeLevel();
    if (updateNeeded.contains(UpdateNeeded::Graph)) {
        update_document_graph(*this, conf, init_doc);
    }

    if (updateNeeded.contains(UpdateNeeded::LinkListClick)) {
        update_link_list_target_rows(rectGraph);
        connect_partition_edges(*this, rectGraph.partition, conf);
        update_node_sizes(rectGraph);
    }

    if (updateNeeded.contains(UpdateNeeded::Scroll)) {
        update_document_scroll(*this, conf);
    }

    // writeFile("/tmp/debug_dump.json",
    // to_json_eval(this->debug).dump(2));
    updateNeeded.clear();
}

void StoryGridModel::apply(
    const GridAction&      act,
    StoryGridConfig const& conf) {
    __perf_trace("model", "Apply grid action");
    CTX_MSG(fmt("Apply story grid action {}", act));
    auto __scope = ctx.scopeLevel();

    auto replaceNode = [&](org::ImmAdapter const& origin,
                           sem::SemId<sem::Org>   replace) {
        org::ImmAstVersion vNext = getLastHistory().ast.getEditVersion(
            [&](org::ImmAstContext&     ast,
                org::ImmAstEditContext& ctx) -> org::ImmAstReplaceGroup {
                org::ImmAstReplaceGroup result;
                result.incl(
                    org::replaceNode(origin, ast.add(replace, ctx), ctx));
                return result;
            });
        history.push_back(StoryGridHistory{
            .ast = vNext,
        });
    };

    switch (act.getKind()) {
        case GridAction::Kind::EditCell: {
            updateNeeded.incl(UpdateNeeded::Graph);
            updateNeeded.incl(UpdateNeeded::Scroll);
            auto edit = act.getEditCell();
            replaceNode(
                edit.cell.getValue().origin,
                sem::asOneNode(sem::parseString(edit.updated)));
            break;
        }

        case GridAction::Kind::EditNodeText: {
            updateNeeded.incl(UpdateNeeded::Graph);
            updateNeeded.incl(UpdateNeeded::Scroll);
            auto edit = act.getEditNodeText();
            replaceNode(
                rectGraph.getDocNode(edit.pos).getText().origin,
                sem::asOneNode(sem::parseString(edit.updated)));
            break;
        }

        case GridAction::Kind::EditCellChanged: {
            rectGraph.nodes.at(act.getEditCellChanged().documentNodeIdx)
                .getTreeGrid()
                .node.resetGridStatics();
            break;
        }

        case GridAction::Kind::EditNodeChanged: {
            updateNeeded.incl(UpdateNeeded::Scroll);
            break;
        }

        case GridAction::Kind::Scroll: {
            updateNeeded.incl(UpdateNeeded::Scroll);
            auto const& scroll = act.getScroll();
            auto        spans  = rectGraph.ir.getLaneSpans();
            for (auto const& [lane_idx, span] : enumerate(spans)) {
                if (span.contains(scroll.pos.x)) {
                    CTX_MSG(
                        fmt("Lane {} span {} does matches position {} "
                            "Updating scroll offset direction "
                            "{} multiplier {}",
                            lane_idx,
                            span,
                            scroll.pos,
                            scroll.direction,
                            conf.mouseScrollMultiplier));

                    rectGraph.ir.lane(lane_idx, conf.blockGraphConf)
                        .scrollOffset //
                        += scroll.direction * conf.mouseScrollMultiplier;
                } else {
                    CTX_MSG(
                        fmt("Lane {} span {} does not match position {}",
                            lane_idx,
                            span,
                            scroll.pos));
                }
            }
            break;
        }

        case GridAction::Kind::LinkListClick: {
            updateNeeded.incl(UpdateNeeded::LinkListClick);
            updateNeeded.incl(UpdateNeeded::Scroll);
            break;
        }

        case GridAction::Kind::RowFolding: {
            auto const& f = act.getRowFolding();
            auto& g = rectGraph.nodes.at(f.documentNodeIdx).getTreeGrid();
            auto  row  = g.node.getRow(f.flatIdx);
            auto& map  = state.folded[f.documentNodeIdx];
            auto  path = row->getOriginPath();
            if (map.contains(path)) {
                if (f.isOpen) {
                    map.erase(path);
                } else {
                    map.insert_or_assign(path, row->isOpen);
                }
            } else {
                map.insert_or_assign(path, row->isOpen);
            }

            rectGraph.nodes.at(f.documentNodeIdx)
                .getTreeGrid()
                .node.resetGridStatics();
            break;
        }
    }
}

void StoryGridContext::message(
    const std::string& value,
    int                line,
    const char*        function,
    const char*        file) const {
    OLOG_BUILDER()
        .set_callsite(line, function, file)
        .message(value)
        .depth(activeLevel)
        .category("story-grid")
        .severity(ol_info)
        .source_scope({"gui", "feature", "story_grid"});

    OperationsTracer::message(value, activeLevel, line, function, file);
}

Vec<TreeGridRow*> TreeGridRow::flatThisNested(bool withInvisible) {
    Vec<TreeGridRow*> result;
    if (withInvisible || isVisible) {
        result.push_back(this);
        if (isOpen) {
            for (auto& sub : nested) {
                result.append(sub.flatThisNested(withInvisible));
            }
        }
    }

    return result;
}

int TreeGridRow::getHeightDirect(int padding) const {
    return rs::max(
               own_view(columns.keys())
               | rv::transform([&](Str const& col) -> int {
                     return columns.at(col).getHeight();
                 }))
         + padding;
}

Opt<int> TreeGridRow::getHeight(int padding) const {
    if (isVisible) {
        return getHeightDirect(padding);
    } else {
        return std::nullopt;
    }
}

int TreeGridRow::getHeightRecDirect(int padding) const {
    return getHeight(padding).value()
         + rs::fold_left(
               nested | rv::transform([&](TreeGridRow const& r) -> int {
                   return r.getHeightRecDirect(padding);
               }),
               0,
               [](int lhs, int rhs) { return lhs + rhs; });
}

Opt<int> TreeGridRow::getHeightRec(int padding) const {
    if (isVisible) {
        return getHeight(padding).value()
             + rs::fold_left(
                   nested
                       | rv::transform([&](TreeGridRow const& r) -> int {
                             return r.getHeightRec(padding).value_or(0);
                         }),
                   0,
                   [](int lhs, int rhs) { return lhs + rhs; });
    } else {
        return std::nullopt;
    }
}

void TreeGridDocument::resetGridStatics() {
    __perf_trace("gui", "reset table row positions");
    int                            offset = tableHeaderHeight;
    int                            index  = 0;
    Func<void(TreeGridRow&, bool)> aux;
    aux = [&, this](TreeGridRow& row, bool isVisible) {
        this->rowOrigins.insert_or_assign(row.origin.uniq(), index);
        this->rowPositions.resize_at(index) = offset;
        row.flatIdx                         = index;

        if (isVisible) {
            offset += this->rowPadding;
            offset += row.getHeight().value();
        }
        ++index;

        for (auto& sub : row.nested) { aux(sub, isVisible && row.isOpen); }
    };

    for (auto& row : rows) { aux(row, row.isVisible); }


    int colOffset = treeFoldWidth;
    colPositions.clear();
    for (auto const& [index, col] : enumerate(columns)) {
        colPositions.resize_at(index) = colOffset;
        colOffset += col.width + colPadding;
    }
}

void run_story_grid_cycle(
    StoryGridModel&        model,
    StoryGridConfig const& conf) {
    if (conf.annotated) {
        auto p = ImGui::GetCursorScreenPos();
        ImGui::GetForegroundDrawList()->AddRect(
            p, p + conf.gridViewport, IM_COL32(255, 0, 0, 255));

        run_story_grid_annotated_cycle(model, conf);

        ImGuiIO& io  = ImGui::GetIO();
        auto&    ctx = model.ctx;
        if (io.MouseWheel != 0.0f) {
            CTX_MSG(fmt("Mouse scrolling"));
            model.ctx.action(GridAction::Scroll{
                .pos       = io.MousePos,
                .direction = io.MouseWheel,
            });
        }

        if (ImGui::IsKeyPressed(ImGuiKey_PageUp)) {
            model.ctx.action(GridAction::Scroll{
                .pos       = io.MousePos,
                .direction = static_cast<float>(conf.pageUpScrollStep),
            });
        }

        if (ImGui::IsKeyPressed(ImGuiKey_PageDown)) {
            model.ctx.action(GridAction::Scroll{
                .pos       = io.MousePos,
                .direction = static_cast<float>(conf.pageDownScrollStep),
            });
        }
    } else {
        auto& g = model.rectGraph.nodes.at(0).getTreeGrid();
        render_table(model, g, conf, 0);
    }
}

void apply_story_grid_changes(
    StoryGridModel&         model,
    TreeGridDocument const& init_doc,
    StoryGridConfig const&  conf) {
    if (!model.ctx.actions.empty()) {
        for (auto const& update : model.ctx.actions) {
            model.apply(update, conf);
        }
        model.updateDocument(init_doc, conf);
        model.ctx.actions.clear();
    }
}
