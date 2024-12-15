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
#include <gui_lib/im_org_ui_common.hpp>

#define CTX_MSG(...)                                                      \
    if (ctx.OperationsTracer::TraceState) { ctx.message(__VA_ARGS__); }

#define CTX_MSG_ALL(...) ctx.message(__VA_ARGS__);


#define SGR_LOG_ROOT(__cat, __severity)                                   \
    ::org_logging::log_builder{}.set_callsite().category(__cat).severity( \
        __severity)


EditableOrgText::Result render_editable_cell(
    TreeGridCell&         cell,
    StoryGridContext&     ctx,
    TreeGridColumn const& col,
    std::string const&    id) {
    auto& val = cell.getValue();
    return val.value.render(cell.getSize(), col.edit, id);
}


void render_cell(
    TreeGridRow&          row,
    TreeGridCell&         cell,
    StoryGridContext&     ctx,
    TreeGridColumn const& col,
    ImVec2 const&         pos,
    int                   documentNodeIdx) {

    IM_FN_PRINT("Cell", fmt("pos:{} size:{}", pos, cell.getSize()));
    auto frameless_vars = push_frameless_window_vars();
    ImGui::SetNextWindowPos(pos);
    if (IM_FN_BEGIN(
            BeginChild,
            c_fmt("cell_{}_{}", row.flatIdx, col.name),
            cell.getSize(),
            ImGuiChildFlags_Borders,
            ImGuiWindowFlags_NoScrollbar)) {
        auto res = render_editable_cell(
            cell,
            ctx,
            col,
            fmt("cell_{}_{}_{}", documentNodeIdx, row.flatIdx, col.name));
        switch (res) {
            case EditableOrgText::Result::Changed: {
                ctx.action(GridAction::EditCell{
                    .cell    = cell,
                    .updated = cell.getValue().value.getFinalValue(),
                });
                [[fallthrough]];
            }
            case EditableOrgText::Result::CancelledEditing:
                [[fallthrough]];
            case EditableOrgText::Result::StartedEditing: {
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
    ImGui::PopStyleVar(frameless_vars);
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
            row.isOpen ? conf.foldCellHoverBackground_Open
                       : conf.foldCellHoverBackground_Closed,
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
        rect_min,
        rect_max,
        row.isOpen ? conf.foldCellForeground_Open
                   : conf.foldCellForeground_Closed);
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
            c_fmt("##text_node_window_{}", selfPos.getImId()),
            nullptr,
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize)) {
        ImGui::BringWindowToDisplayFront(ImGui::GetCurrentWindow());

        auto res = text.text.render(
            text.getSize(),
            EditableOrgText::Mode::Multiline,
            fmt("text_node_{}", selfPos.getImId()));

        if (res != EditableOrgText::Result::None) {
            CTX_MSG(fmt("Text edit result {}", res));
        }

        switch (res) {
            case EditableOrgText::Result::Changed: {
                ctx.action(GridAction::EditNodeText{
                    .pos     = selfPos,
                    .updated = text.text.value,
                });
                [[fallthrough]];
            }
            case EditableOrgText::Result::CancelledEditing:
                [[fallthrough]];
            case EditableOrgText::Result::StartedEditing: {
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
    StoryGridNode::LinkList& list,
    LaneNodePos const&       selfPos) {
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
                item.text.render(
                    ImVec2(item.height, item.width),
                    EditableOrgText::Mode::Multiline,
                    fmt("list_{}", selfPos.getImId()));
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
        auto&       node    = model.rectGraph.nodes.at(i);
        auto const& selfPos = model.rectGraph.getIrNode(i);
        if (node.isVisible) {
            switch (node.getKind()) {
                case StoryGridNode::Kind::TreeGrid: {
                    render_table_node(model, node.getTreeGrid(), conf, i);
                    break;
                }
                case StoryGridNode::Kind::Text: {
                    render_text_node(model, node.getText(), selfPos, conf);
                    break;
                }
                case StoryGridNode::Kind::LinkList: {

                    render_list_node(model, node.getLinkList(), selfPos);
                    break;
                }
            }
        }
    }

    for (auto const& [key, edge] : model.rectGraph.ir.layout.lines) {
        render_edge(edge, model.shift, true, conf.blockGraphConf);
    }
}

Opt<json> story_grid_loop(
    GLFWwindow*        window,
    std::string const& file,
    const Opt<json>&   in_state,
    StoryGridConfig&   conf) {
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

    StoryGridModel model;
    auto           start = org::ImmAstContext::init_start_context();
    model.history.push_back(StoryGridHistory{
        .ast = start->init(sem::parseString(readFile(file))),
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
                .ast = start->init(sem::parseString(readFile(file))),
            });
            model.updateNeeded.incl(StoryGridModel::UpdateNeeded::Graph);
            model.updateNeeded.incl(StoryGridModel::UpdateNeeded::Scroll);
            model.updateDocument(conf);
        }

        frame_start();

        auto frameless_vars = push_frameless_window_vars();
        fullscreen_window_begin();

        if (first) {
            first             = false;
            conf.gridViewport = ImGui::GetMainViewport()->Size;
            model.updateNeeded.incl(StoryGridModel::UpdateNeeded::Graph);
            model.updateNeeded.incl(StoryGridModel::UpdateNeeded::Scroll);
            model.updateDocument(conf);
        }

        if (model.debug) {
            render_debug(model.debug.value(), model.shift);
        }

        run_story_grid_cycle(model, conf);

        ImGui::End();
        ImGui::PopStyleVar(frameless_vars);

        frame_end(window);

        model.applyChanges(conf);
        quit_on_q(window);
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

TreeGridCell build_editable_cell(
    org::ImmAdapter       adapter,
    TreeGridColumn const& col) {
    TreeGridCell result{TreeGridCell::Value{}};
    auto&        v = result.getValue();
    v.value        = EditableOrgText::from_adapter(adapter);
    v.origin       = adapter;
    result.width   = col.width;
    result.height  = v.value.get_expected_height(col.width, col.edit);
    return result;
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

        auto target = link->ctx.lock()->currentTrack->footnotes.get(
            link.value()->target.getFootnote().target);

        if (!target) { continue; }

        for (auto const& targetPath :
             link->ctx.lock()->getPathsFor(target.value())) {
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
                    link->ctx.lock()->adapt(targetPath).id));

            add_footnote_annotation_node(
                visited,
                targetPath,
                link->ctx.lock()->adapt(targetPath),
                graph,
                ctx);
        }
    }
};

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
            listItem.text   = EditableOrgText::from_adapter(item);
            listItem.height = listItem.text.get_expected_height(
                listItem.width, EditableOrgText::Mode::Multiline);

            text.items.push_back(listItem);
        }

        LaneNodePos annotation = res.ir.ir.addNode(
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
        res.ir.add(res.nodes.high(), annotation);

        return annotation;

    } else {
        StoryGridNode::Text text{
            .origin = node,
            .text   = EditableOrgText::from_adapter(node),
        };

        int width  = conf.annotationNodeWidth;
        int height = text.text.get_expected_height(
            width, EditableOrgText::Mode::Multiline);
        text.size.x = width;
        text.size.y = height;

        res.nodes.push_back(StoryGridNode{text});
        LaneNodePos annotation = res.ir.ir.addNode(
            lane, ImVec2(width, height), conf.blockGraphConf);
        CTX_MSG(
            fmt("Text node {} mapped to IR node {}", node.id, annotation));
        res.orgToId.insert_or_assign(node.uniq(), annotation);

        res.ir.add(res.nodes.high(), annotation);

        return annotation;
    }
};

void StoryGridModel::connectPartitionEdges(
    Vec<Vec<StoryGridAnnotation>> const& partition,
    StoryGridConfig const&               conf) {
    auto& res   = rectGraph;
    auto& state = getLastHistory();

    CTX_MSG("Connecting partition edges");
    auto __scope = ctx.scopeLevel();
    for (auto const& p : partition) {
        CTX_MSG(fmt("Partition {}", p.size()));
    }

    res.ir.ir.edges.clear();
    for (auto const& [group_idx, group] : enumerate(partition)) {
        for (auto const& node : group) {
            org::ImmAdapter source = state.ast.context->adapt(
                node.source.id);
            org::ImmAdapter target = state.ast.context->adapt(
                node.target.id);

            auto source_parent = state.ast.context->adapt(
                res.annotationParents.get(node.source.id)
                    .value_or(node.source.id));

            LaneNodePos source_node = get_partition_node(
                state.ast, res, group_idx + 1, source_parent, conf, ctx);

            LaneNodePos target_node = get_partition_node(
                state.ast, res, group_idx + 1, target, conf, ctx);

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
                [&](StoryGridNode const&   flat,
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
                res.ir.ir.addEdge(source_node, edge);
            }
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


void StoryGridModel::updateHiddenRowConnection(
    StoryGridConfig const& conf) {
    auto& ir = rectGraph.ir;

    Slice<int> viewportRange = slice1<int>(0, conf.gridViewport.y);
    auto&      lanes         = rectGraph.ir.getLanes();
    for (auto const& [lane_idx, lane] : enumerate(lanes)) {
        for (auto const& [block_idx, block] : enumerate(lane.blocks)) {
            LaneNodePos   lanePos{.lane = lane_idx, .row = block_idx};
            StoryGridNode storyNode = rectGraph.getDocNode(lanePos);
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
                            + (lanes.has(lane_idx)
                                   ? lanes.at(lane_idx).scrollOffset
                                   : 0),
                        treeDoc.getRowYPos(*row)
                            + (lanes.has(lane_idx)
                                   ? lanes.at(lane_idx).scrollOffset
                                   : 0)
                            + row->getHeight().value());
                    org::ImmUniqId rowId = row->origin.uniq();
                    UnorderedSet<org::graph::MapNode> adjacent;
                    for (auto const& n : rectGraph.graph.inNodes(rowId)) {
                        adjacent.incl(n);
                    }

                    for (auto const& n : rectGraph.graph.outNodes(rowId)) {
                        adjacent.incl(n);
                    }

                    auto overlap = rowRange.overlap(viewportRange);

                    for (auto const& n : adjacent) {
                        Opt<LaneNodePos> targetNodePos = rectGraph.orgToId
                                                             .get(n.id);

                        if (targetNodePos) {
                            auto const& t = targetNodePos.value();

                            if (overlap) {
                                rectGraph.at(t).isVisible = true;
                            } else {
                                rectGraph.at(t).isVisible = false;
                            }
                        }
                    }
                }
            }
        }
    }
}

void StoryGridModel::updateDocumentLayout(StoryGridConfig const& conf) {
    CTX_MSG("Update document layout");
    auto  __scope = ctx.scopeLevel();
    auto& ir      = rectGraph.ir;

    {
        Vec<int> offsets //
            = ir.getLanes()
            | rv::transform([](LaneBlockStack const& lane) -> int {
                  return lane.scrollOffset;
              })
            | rs::to<Vec>();

        CTX_MSG(fmt("Update document scrolling, offsets: {}", offsets));
    }

    ir.setVisible(conf.gridViewport);

    ir.ir.resetVisibility();

    // use first line as a basis for arranging all other node positions.
    if (ir.getLanes().has(0)) {
        shift.y = ir.getLanes().at(0).scrollOffset;
    }

    updateDocumentNodePositions(conf);
    updateHiddenRowConnection(conf);
    updateDocumentNodePositions(conf);
}

void StoryGridModel::updateDocumentGraph(StoryGridConfig const& conf) {
    __perf_trace("gui", "add grid nodes");
    rectGraph = StoryGridGraph{};
    rectGraph.graph.clear();

    auto __log_scoped = OLOG_SINK_FACTORY_SCOPED([]() {
        return ::org_logging::init_file_sink(
            "/tmp/connect_partition_edges_log.log");
    });

    CTX_MSG("Update document graph");
    auto __scope = ctx.scopeLevel();

    docNodeIndex = rectGraph.addRootGrid(
        getLastHistory().ast.getRootAdapter(), conf, ctx);

    rectGraph.addGridAnnotationNodes(
        rectGraph.nodes.at(docNodeIndex).getTreeGrid().node, ctx);

    CTX_MSG(fmt("Graph with {} nodes", rectGraph.nodes.size()));
    CTX_MSG(fmt("Graph adjacency list {}", rectGraph.graph.adjList));
    CTX_MSG(fmt("Graph adjacency list in {}", rectGraph.graph.adjListIn));

    rectGraph.partition = getGraphPartition();

    connectPartitionEdges(rectGraph.partition, conf);

    {
        int ir_nodes = 0;
        for (auto const& lane : rectGraph.ir.getLanes()) {
            ir_nodes += lane.blocks.size();
        }

        CTX_MSG(fmt("IR graph {}", ir_nodes));
    }
}

void StoryGridModel::updateDocumentNodePositions(
    const StoryGridConfig& conf) {
    rectGraph.ir.setVisible(conf.gridViewport);
    rectGraph.ir.syncSize([&](int flat_idx) -> ImVec2 {
        return rectGraph.nodes.at(flat_idx).getSize();
    });

    rectGraph.ir.syncLayout();

    CTX_MSG("Updating graph layout positions");
    auto __scope = ctx.scopeLevel();


    for (NodeGridGraph::RectSpec const& rect :
         rectGraph.ir.getRectangles()) {
        StoryGridNode& node = rectGraph.nodes.at(rect.flatPos);
        CTX_MSG(fmt("Rect {}", rect));

        if (rect.isVisible) {
            node.isVisible = true;
            node.setPos(rect.pos);
        } else {
            node.isVisible = false;
        }
    }

    // debug     = to_constraints(lyt, rectGraph.ir, thisLayout);
    // debug->ir = &thisLayout;
}

void StoryGridModel::updateDocument(StoryGridConfig const& conf) {
    __perf_trace("gui", "update grid model");
    CTX_MSG("Update story grid document");
    auto __scope = ctx.scopeLevel();
    if (updateNeeded.contains(UpdateNeeded::Graph)) {
        updateDocumentGraph(conf);
    }

    if (updateNeeded.contains(UpdateNeeded::LinkListClick)) {
        update_link_list_target_rows(rectGraph);
        connectPartitionEdges(rectGraph.partition, conf);
    }

    if (updateNeeded.contains(UpdateNeeded::Scroll)) {
        updateDocumentLayout(conf);
    }

    // writeFile("/tmp/debug_dump.json",
    // to_json_eval(this->debug).dump(2));
    updateNeeded.clear();
}

void StoryGridModel::updateGridState() {
    Vec<org::graph::MapNode> docNodes;
    for (TreeGridRow* row : rectGraph.nodes.at(docNodeIndex)
                                .getTreeGrid()
                                .node.flatRows(true)) {
        if (state.folded.contains(docNodeIndex)) {
            auto path = row->getOriginPath();
            if (state.folded.at(docNodeIndex).contains(path)) {
                row->isOpen = state.folded.at(docNodeIndex).at(path);
            }
        }
    }
}

Vec<Vec<StoryGridAnnotation>> StoryGridModel::getGraphPartition() {
    __perf_trace("gui", "partition graph by distance");
    auto initial_nodes = getDocNodes();
    CTX_MSG(fmt("Partition graph nodes, initial nodes {}", initial_nodes));
    auto __scope = ctx.scopeLevel();


    Vec<Vec<StoryGridAnnotation>>          result;
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
        for (org::graph::MapNode const& adj :
             rectGraph.graph.adjList.at(current)) {
            if (!adjacent.contains(adj) && !distances.contains(adj)) {
                distances[adj] = current_distance + 1;
                q.push(adj);
                result[current_distance].push_back(StoryGridAnnotation{
                    .source = current,
                    .target = adj,
                });
            }

            adjacent.incl(adj);
        }

        for (org::graph::MapNode const& adj :
             rectGraph.graph.inNodes(current)) {
            if (!adjacent.contains(adj) && !distances.contains(adj)) {
                distances[adj] = current_distance + 1;
                q.push(adj);
                result[current_distance].push_back(StoryGridAnnotation{
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

Vec<org::graph::MapNode> StoryGridModel::getDocNodes() {
    Vec<org::graph::MapNode> docNodes;
    for (TreeGridRow* row : rectGraph.nodes.at(docNodeIndex)
                                .getTreeGrid()
                                .node.flatRows(true)) {

        auto tree = row->origin.uniq();
        if (!rectGraph.graph.adjList.at(tree).empty()
            || !rectGraph.graph.inNodes(tree).empty()) {
            docNodes.push_back(tree);
        }
    }
    return docNodes;
}

void StoryGridModel::apply(
    const GridAction&      act,
    StoryGridConfig const& conf) {
    __perf_trace("model", "Apply grid action");
    CTX_MSG(fmt("Apply story grid action {}", act));
    auto __scope = ctx.scopeLevel();

    auto replaceNode = [&](org::ImmAdapter const&    origin,
                           Vec<sem::SemId<sem::Org>> replace) {
        org::ImmAstVersion vNext = getLastHistory().ast.getEditVersion(
            [&](org::ImmAstContext::Ptr ast,
                org::ImmAstEditContext& ast_ctx)
                -> org::ImmAstReplaceGroup {
                org::ImmAstReplaceGroup result;

                if (replace.size() == 1) {
                    result.incl(org::replaceNode(
                        origin,
                        ast->add(replace.at(0), ast_ctx),
                        ast_ctx));
                } else {
                    auto parent = origin.getParent().value();
                    LOGIC_ASSERTION_CHECK(
                        parent.isDirectParentOf(origin),
                        "Origin node is {}, computed parent is {}",
                        origin,
                        parent);

                    int index = origin.getSelfIndex();


                    LOGIC_ASSERTION_CHECK(
                        index != -1,
                        "Failed to compute self-index for origin node {}",
                        origin);


                    Vec<org::ImmId> new_nodes;

                    for (int i = 0; i < index; ++i) {
                        new_nodes.push_back(parent.at(i).id);
                    }

                    for (auto const& it : replace) {
                        new_nodes.push_back(ast->add(it, ast_ctx));
                    }

                    for (int i = index + 1; i < parent.size(); ++i) {
                        new_nodes.push_back(parent.at(i).id);
                    }

                    CTX_MSG(
                        fmt("Replacing parent subnodes {} with {}, origin "
                            "node had index {}",
                            parent->subnodes,
                            new_nodes,
                            index));

                    result.incl(org::setSubnodes(
                        parent,
                        {new_nodes.begin(), new_nodes.end()},
                        ast_ctx));
                }


                return result;
            });
        history.push_back(StoryGridHistory{
            .ast = vNext,
        });
    };

    auto as_sem_list = [](sem::OrgArg doc) -> Vec<sem::SemId<sem::Org>> {
        if (doc->is(OrgSemKind::Document)) {
            return Vec<sem::SemId<sem::Org>>{doc.begin(), doc.end()};
        } else {
            return {doc};
        }
    };

    switch (act.getKind()) {
        case GridAction::Kind::EditCell: {
            updateNeeded.incl(UpdateNeeded::Graph);
            updateNeeded.incl(UpdateNeeded::Scroll);
            auto edit = act.getEditCell();
            replaceNode(
                edit.cell.getValue().origin,
                as_sem_list(sem::parseString(edit.updated)));
            break;
        }

        case GridAction::Kind::EditNodeText: {
            updateNeeded.incl(UpdateNeeded::Graph);
            updateNeeded.incl(UpdateNeeded::Scroll);
            auto edit = act.getEditNodeText();
            CTX_MSG(
                fmt("Updated edit node text {}",
                    escape_literal(edit.updated)));
            replaceNode(
                rectGraph.getDocNode(edit.pos).getText().origin,
                as_sem_list(sem::parseString(edit.updated)));
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
            auto        spans  = rectGraph.ir.ir.getLaneSpans();
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

                    rectGraph.ir.ir.lane(lane_idx, conf.blockGraphConf)
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
        LOGIC_ASSERTION_CHECK(
            !model.rectGraph.nodes.empty(),
            "Cannot render non-annotated story grid with empty graph "
            "nodes");
        auto& g = model.rectGraph.nodes.at(0).getTreeGrid();
        render_table(model, g, conf, 0);
    }
}

void StoryGridModel::applyChanges(StoryGridConfig const& conf) {
    if (!ctx.actions.empty()) {
        for (auto const& update : ctx.actions) { apply(update, conf); }
        updateDocument(conf);
        ctx.actions.clear();
    }
}

int StoryGridGraph::addRootGrid(
    const org::ImmAdapter& node,
    const StoryGridConfig& conf,
    StoryGridContext&      ctx) {
    TreeGridDocument doc = conf.getDefaultDoc();
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

    int flatIdx = addNode(
        0,
        doc.getSize(),
        StoryGridNode{.data = grid},
        conf.blockGraphConf);

    for (auto const& row : doc.flatRows(true)) {
        orgToId.insert_or_assign(row->origin.uniq(), getIrNode(flatIdx));
    }

    return flatIdx;
}

void StoryGridGraph::addGridAnnotationNodes(
    TreeGridDocument& doc,
    StoryGridContext& ctx) {
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
                addDescriptionListNodes(doc, list, ctx);
            }
        }
    }
}

void StoryGridGraph::addDescriptionListNodes(
    TreeGridDocument&                     doc,
    const org::ImmAdapterT<org::ImmList>& list,
    StoryGridContext&                     ctx) {
    org::graph::MapNode listNode{list.uniq()};
    for (auto const& item : list.subAs<org::ImmListItem>()) {
        graph.addNode(item.uniq());
        for (auto const& link : item.getHeader()->subAs<org::ImmLink>()) {
            if (link->target.isId()) {
                auto target = link.ctx.lock()->currentTrack->subtrees.get(
                    link.value().target.getId().text);
                for (auto const& targetPath :
                     link.ctx.lock()->getPathsFor(target.value())) {
                    CTX_MSG(fmt(
                        "List link {} -> {}", item.uniq(), targetPath));

                    annotationParents.insert_or_assign(
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

bool StoryGridGraph::isVisible(const org::ImmUniqId& id) const {
    auto lane_pos = orgToId.get(id);
    if (!lane_pos) { return false; }
    auto node = ir.getFlat(lane_pos.value());
    if (!node) { return false; }
    if (!nodes.at(node.value()).isTreeGrid()) { return false; }
    auto origin = nodes.at(node.value())
                      .getTreeGrid()
                      .node.rowOrigins.get(id);
    if (!origin) { return false; }
    return nodes.at(node.value())
        .getTreeGrid()
        .node.getRow(origin.value())
        ->isVisible;
}
