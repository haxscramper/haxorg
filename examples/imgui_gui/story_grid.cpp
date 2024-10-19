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
    std::string&         value,
    std::string&         edit_buffer,
    bool&                is_editing,
    int                  height,
    int                  width,
    GridColumn::EditMode edit) {
    auto cell_prefix = fmt("{:p}", static_cast<const void*>(value.data()));

    if (edit == GridColumn::EditMode::Multiline) {
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
    GridCell&         cell,
    GridContext&      ctx,
    GridColumn const& col) {
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
    GridCell&         cell,
    GridContext&      ctx,
    GridColumn const& col) {
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
    GridRow&         row,
    Vec<GridAction>& result,
    GridNode&        doc,
    GridContext&     ctx) {
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
    GridRow&         row,
    Vec<GridAction>& result,
    GridNode&        doc,
    GridContext&     ctx) {
    bool skipped = false;
    auto __scope = ctx.scopeLevel();

    if (skipped && row.nested.empty()) { return; };

    ImGui::TableNextRow(ImGuiTableRowFlags_None, row.getHeight());
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
    GridModel&          model,
    DocumentNode::Text& grid) {
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
        GridColumn::EditMode::Multiline);

    ImGui::End();

    ImGui::PopStyleVar(3);

    return result;
}

Vec<GridAction> render_table_node(
    GridModel&          model,
    DocumentNode::Grid& grid) {
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

Vec<GridAction> render_story_grid(GridModel& model) {
    __perf_trace("gui", "grid model render");
    Vec<GridAction> result;
    for (auto& node : model.document.nodes) {
        if (node.isGrid()) {
            result.append(render_table_node(model, node.getGrid()));
        } else {
            result.append(render_text_node(model, node.getText()));
        }
    }

    for (auto const& [key, edge] : model.layout.lines) {
        render_edge(edge, model.shift);
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

    GridModel          model;
    org::ImmAstContext start;
    model.history.push_back(GridState{
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
            model.history.push_back(GridState{
                .ast = start.init(sem::parseString(readFile(file))),
            });
            model.updateDocument();
        }

        frame_start();

        fullscreen_window_begin();

        if (first) {
            first = false;
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


GridCell build_editable_cell(
    org::ImmAdapter   adapter,
    GridColumn const& col);

GridRow build_row(
    org::ImmAdapterT<org::ImmSubtree> tree,
    GridNode&                         doc,
    int&                              flatIdx) {
    GridRow result;
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

Vec<GridRow> build_rows(org::ImmAdapter root, GridNode& doc) {
    Vec<GridRow> result;
    int          idx = 0;
    for (auto const& tree : root.subAs<org::ImmSubtree>()) {
        result.push_back(build_row(tree, doc, idx));
    }

    return result;
}

int get_text_height(
    std::string const&   text,
    int                  width,
    GridColumn::EditMode edit) {
    Vec<Str>    wrapped = split_wrap_text(text, width);
    std::string _tmp{"Tt"};
    char const* _tmp_begin = _tmp.c_str();
    char const* _tmp_end   = _tmp_begin + _tmp.length();
    ImVec2      text_size  = ImGui::CalcTextSize(
        _tmp_begin, _tmp_end, false, width);

    if (edit == GridColumn::EditMode::SingleLine) {
        return text_size.y;
    } else {
        return 0 < wrapped.size() ? text_size.y * wrapped.size()
                                  : text_size.y;
    }
}

GridCell build_editable_cell(
    org::ImmAdapter   adapter,
    GridColumn const& col) {
    GridCell result{GridCell::Value{}};
    auto&    v    = result.getValue();
    v.value       = join(" ", flatWords(adapter));
    v.origin      = adapter;
    result.width  = col.width;
    result.height = get_text_height(v.value, col.width, col.edit);


    return result;
}

struct DocAnnotation {
    org::graph::MapNode source;
    org::graph::MapNode target;
    DESC_FIELDS(DocAnnotation, (source, target));
};

Vec<Vec<DocAnnotation>> partition_graph_by_distance(
    const Vec<org::graph::MapNode>& initial_nodes,
    const org::graph::MapGraph&     graph) {

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

void updateRowPositions(int rowPadding, GridNode& doc) {
    int offset = 0;
    for (auto const& row : doc.flatRows()) {
        doc.rowPositions.resize_at(row->flatIdx) = offset;
        doc.rowOrigins.insert_or_assign(row->origin.uniq(), row->flatIdx);
        offset += row->getHeight(rowPadding);
    }
}

void addLinkedDescriptionList(
    org::ImmAdapterT<org::ImmList> const& list,
    org::graph::MapGraph&                 graph,
    GridContext&                          ctx) {
    org::graph::MapNode listNode{list.uniq()};
    graph.addNode(listNode);
    for (auto const& item : list.subAs<org::ImmListItem>()) {
        for (auto const& link : item.getHeader()->subAs<org::ImmLink>()) {
            if (link->isId()) {
                auto target = link.ctx->track->subtrees.get(
                    link.value().getId().text);
                for (auto const& targetPath :
                     link.ctx->getPathsFor(target.value())) {
                    graph.addEdge(
                        org::graph::MapEdge{
                            .source = listNode,
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
    GridContext&                 ctx) {
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

void addGridNodes(
    GridNode&             doc,
    org::graph::MapGraph& graph,
    GridContext&          ctx) {

    for (auto const& row : doc.flatRows()) {
        org::graph::MapNode subtreeNode{row->origin.uniq()};
        graph.addNode(subtreeNode);
    }

    for (auto const& row : doc.flatRows()) {
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
                addLinkedDescriptionList(list, graph, ctx);
            }
        }
    }
}

struct GraphPartitionIR {
    DocGraph                   ir;
    UnorderedMap<int, DocNode> gridNodeToNode;
    UnorderedMap<DocNode, int> nodeToGridNode;
    DocumentGraph*             graph;

    void addIrNode(int flatIdx, DocNode const& irNode) {
        gridNodeToNode.insert_or_assign(flatIdx, irNode);
        nodeToGridNode.insert_or_assign(irNode, flatIdx);
    }

    DocumentNode const& getDocNode(int idx) const {
        return graph->nodes.at(idx);
    }

    DocumentNode const& getDocNode(DocNode const& idx) const {
        return getDocNode(getFlatIdx(idx));
    }

    DocNode const& getIrNode(int idx) const {
        return gridNodeToNode.at(idx);
    }

    int const& getFlatIdx(DocNode const& node) const {
        return nodeToGridNode.at(node);
    }
};

GraphPartitionIR addGraphPartitions(
    int                            rowPadding,
    GridNode&                      doc,
    DocumentGraph&                 document,
    Vec<Vec<DocAnnotation>> const& partition,
    GridState&                     state,
    ImVec2 const&                  viewport,
    Vec<Slice<int>>&               laneSpans,
    Vec<float>&                    laneOffsets) {

    UnorderedMap<org::ImmUniqId, DocNode> orgToId;
    GraphPartitionIR                      res;
    res.graph = &document;


    DocumentNode::Grid grid{
        .pos  = ImVec2(0, 0),
        .size = ImVec2(
            doc.getWidth(rowPadding), doc.getHeight(rowPadding)),
        .node = doc,
    };
    document.nodes.clear();
    document.nodes.push_back(DocumentNode{.data = grid});
    auto root = res.ir.addNode(0, grid.size);
    res.addIrNode(document.nodes.high(), root);

    for (auto const& row : doc.flatRows()) {
        orgToId.insert_or_assign(row->origin.uniq(), root);
    }

    auto get_node = [&](int lane, org::ImmAdapter const& node) -> DocNode {
        if (orgToId.contains(node.uniq())) {
            return orgToId.at(node.uniq());
        } else {
            DocumentNode::Text text{
                .node = node,
                .text = join(" ", flatWords(node)),
            };

            int width  = 200;
            int height = get_text_height(
                text.text, width, GridColumn::EditMode::Multiline);
            text.size.x = width;
            text.size.y = height;

            document.nodes.push_back(DocumentNode{text});
            DocNode annotation = res.ir.addNode(
                lane, ImVec2(width, height));
            orgToId.insert_or_assign(node.uniq(), annotation);

            res.addIrNode(document.nodes.high(), annotation);

            return annotation;
        }
    };

    for (auto const& [group_idx, group] : enumerate(partition)) {
        for (auto const& node : group) {
            org::ImmAdapter source = state.ast.context.adapt(
                node.source.id);
            org::ImmAdapter target = state.ast.context.adapt(
                node.target.id);

            DocNode source_node = get_node(group_idx + 1, source);
            DocNode target_node = get_node(group_idx + 1, target);
            DocumentNode const& source_flat = res.getDocNode(source_node);
            DocumentNode const& target_flat = res.getDocNode(target_node);

            if (source_flat.isGrid()) {
                res.ir.addEdge(
                    source_node,
                    DocOutEdge{
                        .target = target_node,
                        .heightOffset //
                        = source_flat.getGrid().node.getRowCenterOffset(
                            source_flat.getGrid().node.rowOrigins.at(
                                source.uniq())),
                    });
            } else {
                res.ir.addEdge(
                    source_node, DocOutEdge{.target = target_node});
            }
        }
    }

    res.ir.visible.h = viewport.y;
    res.ir.visible.w = viewport.x;
    for (auto& stack : res.ir.lanes) { stack.resetVisibleRange(); }
    for (auto const& [lane_idx, offset] : enumerate(laneOffsets)) {
        if (res.ir.lanes.has(lane_idx)) {
            res.ir.lanes.at(lane_idx).scrollOffset = offset;
        }
    }

    int laneStartX = 0;
    for (auto const& [lane_idx, lane] : enumerate(res.ir.lanes)) {
        laneSpans.resize_at(lane_idx) = slice(
            laneStartX + lane.leftMargin,
            laneStartX + lane.leftMargin + lane.getWidth());
        laneStartX += lane.getFullWidth();
    }

    return res;
}

void GridModel::updateDocument() {
    __perf_trace("gui", "update grid model");
    GridNode doc;
    auto&    ctx = conf;

    doc.getColumn("title").width = 200;
    doc.getColumn("event").width = 200;
    doc.getColumn("note").width  = 200;
    // doc.getColumn("turning_point").width = 300;
    // doc.getColumn("value").width         = 200;
    doc.getColumn("location").width = 240;
    doc.getColumn("location").edit  = GridColumn::EditMode::SingleLine;
    doc.rows = build_rows(getCurrentState().ast.getRootAdapter(), doc);
    document.nodes.clear();

    int rowPadding = 5;

    graph.adjList.clear();
    graph.nodeProps.clear();
    graph.edgeProps.clear();
    graph.inNodes.clear();

    updateRowPositions(rowPadding, doc);
    addGridNodes(doc, graph, ctx);


    // auto gv = graph.toGraphviz(
    //     getCurrentState().ast.context,
    //     org::graph::MapGraph::GvConfig{});

    // Graphviz gvc;
    // gv.setRankDirection(Graphviz::Graph::RankDirection::LR);
    // gvc.renderToFile("/tmp/ReplaceSubnodeAtPath.png", gv);
    // gvc.writeFile("/tmp/ReplaceSubnodeAtPath.dot", gv);

    Vec<org::graph::MapNode> docNodes;
    for (auto const& row : doc.flatRows()) {
        auto tree = row->origin.uniq();
        if (!graph.adjList.at(tree).empty()
            || !graph.inNodes.at(tree).empty()) {
            docNodes.push_back(tree);
        }
    }

    Vec<Vec<DocAnnotation>> partition = partition_graph_by_distance(
        docNodes, graph);


    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    GraphPartitionIR     ir       = addGraphPartitions(
        rowPadding,
        doc,
        document,
        partition,
        getCurrentState(),
        viewport->WorkSize,
        laneSpans,
        laneOffsets);


    // writeFile("/tmp/ir_dump.json", to_json_eval(ir).dump(2));


    __perf_trace_begin("gui", "to doc layout");
    DocLayout lyt = to_layout(ir.ir);
    __perf_trace_end("gui");
    // writeFile("/tmp/tmp_dump.json", to_json_eval(lyt).dump(2));
    lyt.ir.height = 10000;
    lyt.ir.width  = 10000;
    __perf_trace_begin("gui", "do cola layout");
    auto cola = lyt.ir.doColaLayout();
    __perf_trace_end("gui");
    __perf_trace_begin("gui", "do cola convert");
    this->layout = cola.convert();
    __perf_trace_end("gui");

    // writeFile("/tmp/lyt_dump.json", to_json_eval(this->layout).dump(2));

    for (auto const& [idx, rec] : enumerate(this->layout.fixed)) {
        auto& node = document.nodes.at(idx);
        if (node.isGrid()) {
            node.getGrid().pos.x = rec.left;
            node.getGrid().pos.y = rec.top;
        } else if (node.isText()) {
            node.getText().pos.x = rec.left;
            node.getText().pos.y = rec.top;
        }
    }

    this->debug     = to_constraints(lyt, ir.ir, this->layout);
    this->debug->ir = &this->layout;
    // writeFile("/tmp/debug_dump.json",
    // to_json_eval(this->debug).dump(2));
}

void GridModel::apply(const GridAction& act) {
    switch (act.getKind()) {
        case GridAction::Kind::EditCell: {
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
            history.push_back(GridState{
                .ast = vNext,
            });
            break;
        }

        case GridAction::Kind::Scroll: {
            auto const& scroll = act.getScroll();
            for (auto const& [lane_idx, span] : enumerate(laneSpans)) {
                if (span.contains(scroll.pos.x)) {
                    laneOffsets.resize_at(lane_idx, 0.0f) //
                        += scroll.direction * 10;
                }
            }
            break;
        }
    }
}

void GridContext::message(
    const std::string& value,
    int                line,
    const char*        function,
    const char*        file) const {
    OperationsTracer::message(value, activeLevel, line, function, file);
}

int GridRow::getHeight(int padding) const {
    return rs::max(
               own_view(columns.keys())
               | rv::transform(
                   [&](Str const& col) { return columns.at(col).height; }))
         + padding;
}

int GridRow::getHeightRec(int padding) const {
    return getHeight(padding)
         + rs::fold_left(
               nested | rv::transform([&](GridRow const& r) {
                   return r.getHeightRec(padding);
               }),
               0,
               [](int lhs, int rhs) { return lhs + rhs; });
}
