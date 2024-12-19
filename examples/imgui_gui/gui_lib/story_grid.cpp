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
    TreeGridRow::Ptr      row,
    TreeGridCell&         cell,
    StoryGridContext&     ctx,
    TreeGridColumn const& col,
    ImVec2 const&         pos,
    StoryNodeId           documentNodeIdx) {

    IM_FN_PRINT("Cell", fmt("pos:{} size:{}", pos, cell.getSize()));
    auto frameless_vars = push_frameless_window_vars();
    ImGui::SetNextWindowPos(pos);
    if (IM_FN_BEGIN(
            BeginChild,
            c_fmt("cell_{}_{}", row->flatIdx, col.name),
            cell.getSize(),
            ImGuiChildFlags_Borders,
            ImGuiWindowFlags_NoScrollbar)) {
        auto res = render_editable_cell(
            cell,
            ctx,
            col,
            fmt("cell_{}_{}_{}", documentNodeIdx, row->flatIdx, col.name));
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
    TreeGridRow::Ptr  row,
    TreeGridDocument& doc,
    StoryGridContext& ctx,
    StoryNodeId       documentNodeIdx,
    ImVec2 const&     gridStart) {
    auto __scope = ctx.scopeLevel();
    int  colIdx  = 1;
    for (auto const& col : doc.columns) {
        if (row->columns.contains(col.name)) {
            auto __scope = ctx.scopeLevel();
            render_cell(
                row,
                row->columns.at(col.name),
                ctx,
                col,
                gridStart + doc.getCellPos(row->flatIdx, col.name),
                documentNodeIdx);
        }
        ++colIdx;
    }
}

void render_tree_row(
    TreeGridRow::Ptr       row,
    TreeGridDocument&      doc,
    StoryGridContext&      ctx,
    StoryGridConfig const& conf,
    StoryNodeId            documentNodeIdx,
    ImVec2 const&          gridStart) {
    // row is completely invisible, including its nested sub-rows
    if (!row->isVisible) { return; }
    bool skipped = false;
    auto __scope = ctx.scopeLevel();

    if (skipped && row->nested.empty()) { return; };

    auto __im_scope = IM_SCOPE_BEGIN(
        "Tree row", fmt("row [{}]", row->flatIdx));

    if (!row->nested.empty()) {
        render_tree_columns(row, doc, ctx, documentNodeIdx, gridStart);
        if (row->isOpen) {
            for (auto& sub : row->nested) {
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
                doc.getRowYPos(row) + row->getHeight().value_or(0)));

    if (cell_rect.Contains(ImGui::GetMousePos())) {
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
            ImGui::OpenPopup(fmt("ctx_{}", row->origin.id).c_str());
        }
    }

    if (ImGui::BeginPopup(fmt("ctx_{}", row->origin.id).c_str())) {
        if (ImGui::MenuItem("Copy")) {
            if (row->origin->treeId.get().has_value()) {
                ImGui::SetClipboardText(
                    row->origin->treeId->value().c_str());
            }
        }
        ImGui::EndPopup();
    }

    ImVec2 cell_max  = cell_rect.Max;
    ImVec2 rect_size = ImVec2(
        std::ceil(
            ((6 - row->origin->level) / 6.0f)
            * (cell_rect.Max.x - cell_rect.Min.x)),
        cell_rect.Max.y - cell_rect.Min.y);
    float  pad      = 2.0f;
    ImVec2 rect_min = cell_max - rect_size + ImVec2(pad, pad);
    ImVec2 rect_max = cell_max - ImVec2(pad, pad);

    if (ImGui::IsMouseHoveringRect(cell_rect.Min, cell_rect.Max)) {
        ImGui::GetWindowDrawList()->AddRect(
            rect_min,
            rect_max,
            row->isOpen ? conf.foldCellHoverBackground_Open
                        : conf.foldCellHoverBackground_Closed,
            0.0f,
            0,
            1.0f);
        if (ImGui::IsMouseClicked(0)) {
            row->isOpen = !row->isOpen;
            ctx.action(GridAction::RowFolding{
                .isOpen          = row->isOpen,
                .flatIdx         = row->flatIdx,
                .documentNodeIdx = documentNodeIdx,
            });
        }
    }

    ImGui::GetWindowDrawList()->AddRectFilled(
        rect_min,
        rect_max,
        row->isOpen ? conf.foldCellForeground_Open
                    : conf.foldCellForeground_Closed);
}

void render_text_node(
    StoryGridModel&        model,
    StoryNode::Text&       text,
    LaneNodePos const&     selfPos,
    StoryGridConfig const& conf) {
    auto& ctx = model.ctx;


    ImGui::PushStyleColor(ImGuiCol_WindowBg, conf.annotationNodeWindowBg);
    auto frameless_vars = push_frameless_window_vars();
    ImGui::SetNextWindowPos(
        model.rectGraph.getPosition(selfPos) + model.shift);
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
    StoryGridModel&      model,
    StoryNode::LinkList& list,
    LaneNodePos const&   selfPos) {
    auto frameless_vars = push_frameless_window_vars();
    ImGui::SetNextWindowPos(
        model.rectGraph.getPosition(selfPos) + model.shift);
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
    StoryGridModel&        model,
    StoryNode::TreeGrid&   grid,
    StoryGridConfig const& conf,
    StoryNodeId            documentNodeIdx,
    LaneNodePos const&     selfPos) {
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
    ImGui::SetNextWindowPos(
        ImVec2(model.rectGraph.getPosition(selfPos) + model.shift));
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
    StoryGridModel&        model,
    StoryNode::TreeGrid&   grid,
    StoryGridConfig const& conf,
    StoryNodeId            documentNodeIdx,
    LaneNodePos const&     selfPos) {

    auto& ctx = model.ctx;
    auto& doc = grid.node;

    ImGui::SetNextWindowPos(
        model.rectGraph.getPosition(selfPos) + model.shift);
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
        render_table(model, grid, conf, documentNodeIdx, selfPos);

        IM_FN_END(End);
    }
    ImGui::PopStyleVar(frameless_vars);
}

void run_story_grid_annotated_cycle(
    StoryGridModel&        model,
    StoryGridConfig const& conf) {
    __perf_trace("gui", "grid model render");
    for (auto const& [node_id, node] : model.rectGraph.getStoryNodes()) {
        LaneNodePos selfPos = model.rectGraph.getBlockPos(node_id).value();
        if (node->isVisible) {
            switch (node->getKind()) {
                case StoryNode::Kind::TreeGrid: {
                    render_table_node(
                        model,
                        node->getTreeGrid(),
                        conf,
                        node_id,
                        selfPos);
                    break;
                }
                case StoryNode::Kind::Text: {
                    render_text_node(
                        model, node->getText(), selfPos, conf);
                    break;
                }
                case StoryNode::Kind::LinkList: {
                    render_list_node(model, node->getLinkList(), selfPos);
                    break;
                }
            }
        }
    }

    for (auto const& [key, edge] :
         model.rectGraph.positionStore.lyt.layout.lines) {
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
            model.updateDocument(conf);
        }

        frame_start();

        auto frameless_vars = push_frameless_window_vars();
        fullscreen_window_begin();

        if (first) {
            first             = false;
            conf.gridViewport = ImGui::GetMainViewport()->Size;
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

TreeGridRow::Ptr build_row(
    org::ImmAdapterT<org::ImmSubtree> tree,
    TreeGridDocument&                 doc,
    int&                              flatIdx) {
    auto result              = TreeGridRow::shared();
    result->columns["title"] = build_editable_cell(
        tree.getTitle(), doc.getColumn("title"));
    result->origin  = tree;
    result->flatIdx = flatIdx;
    ++flatIdx;
    for (auto const& sub : tree.subAs<org::ImmList>()) {
        if (sub.isDescriptionList()) {
            for (auto const& item : sub.subAs<org::ImmListItem>()) {
                auto flat = flatWords(item.getHeader().value());
                for (auto const& word : flat) {
                    if (word.starts_with("story_")) {
                        auto column = word.dropPrefix("story_");
                        result->columns[column] = build_editable_cell(
                            item.at(0), doc.getColumn(column));
                    }
                }
            }
        }
    }

    for (auto const& sub : tree.subAs<org::ImmSubtree>()) {
        if (!sub->isComment && !sub->isArchived) {
            result->addNested(build_row(sub, doc, flatIdx));
        }
    }

    return result;
}

Vec<TreeGridRow::Ptr> build_rows(
    org::ImmAdapter   root,
    TreeGridDocument& doc) {
    Vec<TreeGridRow::Ptr> result;
    int                   idx = 0;
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

StoryGridGraph::FlatNodeStore StoryGridGraph::FlatNodeStore::init(
    const SemGraphStore&   semGraph,
    StoryGridContext&      ctx,
    const StoryGridConfig& conf) {
    STORY_GRID_MSG_SCOPE(ctx, "Flat grid init store");
    FlatNodeStore res;
    for (auto const& [node, adjacent] : semGraph.graph.adjList) {
        res.add(semGraph.ctx->adapt(node.id), conf, ctx);
    }
    return res;
}


void StoryGridGraph::FlatNodeStore::setOrgNodeOrigin(
    StoryNode const& n,
    StoryNodeId      idx) {
    std::visit(
        overloaded{
            [&](StoryNode::LinkList const& l) {
                for (auto const& item : l.items) {
                    setOrgNodeOrigin(item.node.uniq(), idx);
                }

                setOrgNodeOrigin(l.origin.uniq(), idx);
            },
            [&](StoryNode::TreeGrid const& t) {
                for (auto const& row : t.node.flatRows(true)) {
                    setOrgNodeOrigin(row->origin.uniq(), idx);
                }
            },
            [&](StoryNode::Text const& t) {

            },
        },
        n.data);
}

LaneNodePos StoryGridGraph::BlockGraphStore::addToLane(
    int                    laneIdx,
    StoryNodeId            id,
    const StoryGridConfig& conf,
    FlatNodeStore const&   nodes) {
    return ir.addNode(
        laneIdx,
        toBlock(id),
        nodes.getStoryNode(id).getSize(),
        conf.blockGraphConf);
}

void StoryGridGraph::BlockGraphStore::setPartition(
    const Vec<Vec<StoryGridAnnotation>>& inPartition,
    FlatNodeStore const&                 storyNodes,
    SemGraphStore const&                 semGraph,
    StoryGridConfig const&               conf,
    StoryGridContext&                    ctx) {

    CTX_MSG("Update block graph IR");
    auto __scope = ctx.scopeLevel();

    for (auto const& [group_idx, group] : enumerate(partition)) {
        CTX_MSG(fmt("Partition {} has {} items", group_idx, group.size()));
        auto __scope = ctx.scopeLevel();
        for (auto const& node : group) {
            org::ImmUniqId source_adapter = node.source.id;
            org::ImmUniqId target_adapter = node.target.id;

            auto source_parent = semGraph.annotationParents
                                     .get(node.source.id)
                                     .value_or(node.source.id);

            StoryNodeId source_id = storyNodes
                                        .getStoryNodeId(source_parent)
                                        .value();
            StoryNodeId target_id = storyNodes
                                        .getStoryNodeId(target_adapter)
                                        .value();

            LaneNodePos source_node = addToLane(
                group_idx + 1, source_id, conf, storyNodes);
            LaneNodePos target_node = addToLane(
                group_idx + 1, target_id, conf, storyNodes);

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
                [&](StoryNode const&      flat,
                    org::ImmUniqId const& node) -> Opt<int> {
                if (flat.isTreeGrid()) {
                    int row_idx = flat.getTreeGrid()
                                      .node.getRow(node)
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
                        flat.getLinkList().getRow(node));

                    // CTX_MSG(fmt("edge {} -> {}", source_node, edge));
                } else {
                    return std::nullopt;
                }
            };

            StoryNode const& source = storyNodes.getStoryNode(source_id);
            StoryNode const& target = storyNodes.getStoryNode(target_id);

            edge.sourceOffset = get_connector_offset(
                source, source_adapter);
            edge.targetOffset = get_connector_offset(
                target, target_adapter);

            if (source.isLinkList() || target.isLinkList()) {
                CTX_MSG(fmt("{}", edge));
            }

            ir.addEdge(source_node, edge);
        }
    }
}


void StoryGridGraph::FlatNodeStore::focusLinkListTargetRows(
    StoryGridContext&    ctx,
    SemGraphStore const& semGraph) {
    if (rs::any_of(gen_view(nodes.items()), [](StoryNode* n) {
            return n->isLinkList() && n->getLinkList().isSelected;
        })) {
        UnorderedSet<org::ImmUniqId> targets;
        for (auto const& node : items()) {
            if (node->isLinkList() && node->getLinkList().isSelected) {
                for (auto const& item : node->getLinkList().items) {
                    for (auto const& target :
                         semGraph.graph.adjList.at(item.node.uniq())) {
                        targets.incl(target.id);
                    }
                }
            }
        }

        Func<bool(TreeGridRow::Ptr)> aux;
        aux = [&](TreeGridRow::Ptr row) -> bool {
            row->isVisible = false;
            if (targets.contains(row->origin.uniq())) {
                row->isVisible = true;
            }

            for (auto& sub : row->nested) {
                if (aux(sub)) { row->isVisible = true; }
            }

            return row->isVisible;
        };

        for (auto& node : items()) {
            if (node->isTreeGrid()) {
                for (auto& row : node->getTreeGrid().node.rows) {
                    aux(row);
                }
                node->getTreeGrid().node.updatePositions();
            }
        }
    } else {
        Func<void(TreeGridRow::Ptr)> aux;
        aux = [&](TreeGridRow::Ptr row) {
            row->isVisible = true;
            for (auto& sub : row->nested) { aux(sub); }
        };

        for (auto& node : items()) {
            if (node->isTreeGrid()) {
                for (auto& row : node->getTreeGrid().node.rows) {
                    aux(row);
                }
                node->getTreeGrid().node.updatePositions();
            }
        }
    }
}


void StoryGridGraph::BlockGraphStore::updateHiddenRowConnection(
    StoryGridConfig const& conf,
    StoryGridContext&      ctx,
    SemGraphStore const&   semGraph,
    FlatNodeStore const&   storyNodes) {
    CTX_MSG("Update hiddent row connections");
    auto       __scope       = ctx.scopeLevel();
    Slice<int> viewportRange = slice1<int>(0, conf.gridViewport.y);
    for (auto const& [lane_idx, lane] : enumerate(ir.lanes)) {
        for (auto const& [block_idx, block] : enumerate(lane.blocks)) {
            LaneNodePos      lanePos{.lane = lane_idx, .row = block_idx};
            StoryNode const& storyNode = storyNodes.getStoryNode(
                getStoryNodeId(lanePos).value());
            // if individual node is a story grid it can have edges
            // connected at any part of the shape, and they might be
            // scrolled out of the view even if the grid itself is
            // partially visible.
            if (storyNode.isTreeGrid()) {
                CTX_MSG(fmt("Block at {} is story grid", lanePos));
                TreeGridDocument treeDoc = storyNode.getTreeGrid().node;
                // so the code goes over each visible row, collecting the
                // positions relative to the *block graph layout basis*
                for (auto const& row : treeDoc.flatRows(false)) {
                    Slice<int> rowRange = slice1<int>(
                        treeDoc.getRowYPos(row)
                            + (ir.lanes.has(lane_idx)
                                   ? ir.lanes.at(lane_idx).scrollOffset
                                   : 0),
                        treeDoc.getRowYPos(row)
                            + (ir.lanes.has(lane_idx)
                                   ? ir.lanes.at(lane_idx).scrollOffset
                                   : 0)
                            + row->getHeight().value());

                    org::ImmUniqId rowId = row->origin.uniq();
                    auto adjacent        = semGraph.graph.adjNodes(rowId);
                    auto overlap         = rowRange.overlap(viewportRange);

                    if (!adjacent.empty()) {
                        CTX_MSG(
                            fmt("Row {}, adjacent nodes {} row range {} "
                                "viewport range {}",
                                row->flatIdx,
                                adjacent,
                                rowRange,
                                viewportRange));
                    }

                    auto __scope = ctx.scopeLevel();
                    for (auto const& n : adjacent) {
                        Opt<StoryNodeId>
                            targetNodeId = storyNodes.getStoryNodeId(n.id);
                        CTX_MSG(
                            fmt("N {} target {} overlap {}",
                                n.id.id,
                                targetNodeId,
                                overlap));
                        if (targetNodeId) {
                            auto const& t   = targetNodeId.value();
                            LaneNodePos pos = getBlockPos(t).value();
                            if (overlap) {
                                ir.at(pos).isVisible = true;
                            } else {
                                ir.at(pos).isVisible = false;
                            }
                        }
                    }
                }
            }
        }
    }
}

StoryGridGraph::NodePositionStore StoryGridGraph::BlockGraphStore::
    updateDocumentLayout(
        StoryGridConfig const& conf,
        StoryGridContext&      ctx,
        SemGraphStore const&   semGraph,
        FlatNodeStore const&   storyNodes) {
    CTX_MSG("Update document layout");
    auto __scope = ctx.scopeLevel();

    {
        Vec<int> offsets //
            = ir.lanes
            | rv::transform([](LaneBlockStack const& lane) -> int {
                  return lane.scrollOffset;
              })
            | rs::to<Vec>();

        CTX_MSG(fmt("Update document scrolling, offsets: {}", offsets));
    }

    ir.setVisible(conf.gridViewport);
    ir.resetVisibility();

    auto positions0 = NodePositionStore::init(ctx, *this);
    updateHiddenRowConnection(conf, ctx, semGraph, storyNodes);
    return NodePositionStore::init(ctx, *this);
}

void StoryGridModel::updateGridState() {
    Vec<org::graph::MapNode> docNodes;
    for (auto const& [_, node] : rectGraph.getStoryNodes()) {
        if (node->isTreeGrid()) {
            for (TreeGridRow::Ptr const& row :
                 node->getTreeGrid().node.flatRows(true)) {
                if (state.folded.contains(docNodeIndex)) {
                    auto path = row->getOriginPath();
                    if (state.folded.at(docNodeIndex).contains(path)) {
                        row->isOpen = state.folded.at(docNodeIndex)
                                          .at(path);
                    }
                }
            }
        }
    }
}

Vec<Vec<StoryGridAnnotation>> StoryGridGraph::FlatNodeStore::
    getGraphPartition(StoryGridContext& ctx, SemGraphStore const& semGraph)
        const {
    __perf_trace("gui", "partition graph by distance");
    auto initial_nodes = getInitialNodes(ctx, semGraph);
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
             semGraph.graph.adjList.at(current)) {
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
             semGraph.graph.inNodes(current)) {
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

Vec<org::graph::MapNode> StoryGridGraph::FlatNodeStore::getInitialNodes(
    StoryGridContext&    ctx,
    SemGraphStore const& semGraph) const {
    Vec<org::graph::MapNode> docNodes;
    for (auto const& node : nodes.items()) {
        if (node->isTreeGrid()) {
            for (const TreeGridRow::Ptr& row :
                 node->getTreeGrid().node.flatRows(true)) {

                auto tree = row->origin.uniq();
                if (!semGraph.graph.adjList.at(tree).empty()
                    || !semGraph.graph.inNodes(tree).empty()) {
                    docNodes.push_back(tree);
                }
            }
        }
    }

    return docNodes;
}

StoryNodeId StoryGridGraph::FlatNodeStore::add(
    const org::ImmAdapter& node,
    const StoryGridConfig& conf,
    StoryGridContext&      ctx) {
    if (orgToFlatIdx.contains(node.uniq())) {
        auto annotation = orgToFlatIdx.at(node.uniq());
        CTX_MSG(
            fmt("Node {} already mapped to id {}", node.id, annotation));
        return annotation;
    } else if (auto doc = node.asOpt<org::ImmDocument>()) {
        auto grid = TreeGridDocument::from_root(doc.value(), conf, ctx);
        StoryNodeId res = add(
            StoryNode{StoryNode::TreeGrid{.node = grid}});
        CTX_MSG(fmt(
            "Document node  {} mapped to Document node {}", node.id, res));
        return res;
    } else if (auto list = node.asOpt<org::ImmList>();
               list && list->isDescriptionList()
               && org::graph::isLinkedDescriptionList(node)) {
        StoryNode::LinkList text{};

        for (auto const& item : list->subAs<org::ImmListItem>()) {
            StoryNode::LinkList::Item listItem;
            listItem.node   = item;
            listItem.width  = conf.annotationNodeWidth;
            listItem.text   = EditableOrgText::from_adapter(item);
            listItem.height = listItem.text.get_expected_height(
                listItem.width, EditableOrgText::Mode::Multiline);

            text.items.push_back(listItem);
        }

        StoryNodeId annotation = add(StoryNode{text});
        CTX_MSG(fmt(
            "List {} mapped to LinkList node {}", node.id, annotation));
        return annotation;
    } else {
        StoryNode::Text text{
            .origin = node,
            .text   = EditableOrgText::from_adapter(node),
        };

        int width  = conf.annotationNodeWidth;
        int height = text.text.get_expected_height(
            width, EditableOrgText::Mode::Multiline);
        text.size.x = width;
        text.size.y = height;

        StoryNodeId annotation = add(StoryNode{text});
        CTX_MSG(fmt(
            "Text node {} mapped to Text node {}", node.id, annotation));
        return annotation;
    }
}

void StoryGridModel::apply(
    const GridAction&      act,
    StoryGridConfig const& conf) {
    __perf_trace("model", "Apply grid action");
    CTX_MSG(fmt("Apply story grid action {}", act));
    auto __scope = ctx.scopeLevel();

    auto __log_scoped = OLOG_SINK_FACTORY_SCOPED([]() {
        return ::org_logging::init_file_sink(
            "/tmp/story_grid_model_apply.log");
    });

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
            auto edit = act.getEditCell();
            replaceNode(
                edit.cell.getValue().origin,
                as_sem_list(sem::parseString(edit.updated)));
            updateDocument(conf);
            break;
        }

        case GridAction::Kind::EditNodeText: {
            auto edit = act.getEditNodeText();
            CTX_MSG(
                fmt("Updated edit node text {}",
                    escape_literal(edit.updated)));
            replaceNode(
                rectGraph.getStoryNode(edit.pos).getText().origin,
                as_sem_list(sem::parseString(edit.updated)));
            updateDocument(conf);
            break;
        }

        case GridAction::Kind::EditCellChanged: {
            rectGraph.updateGeometry(
                act.getEditCellChanged().documentNodeIdx);
            break;
        }

        case GridAction::Kind::EditNodeChanged: {
            rectGraph.updateNodePositions(ctx, conf);
            break;
        }

        case GridAction::Kind::Scroll: {
            auto const& scroll = act.getScroll();
            rectGraph.blockGraph.ir.addScrolling(
                scroll.pos, scroll.direction);
            updateDocumentLayout(conf);
            break;
        }

        case GridAction::Kind::LinkListClick: {
            rectGraph.focusLinkListTargetRows(ctx);
            updateDocumentLayout(conf);
            break;
        }

        case GridAction::Kind::RowFolding: {
            auto const& f = act.getRowFolding();
            auto&       g = rectGraph.getStoryNode(f.documentNodeIdx)
                          .getTreeGrid();
            auto  row  = g.node.getRow(f.flatIdx);
            auto& map  = state.folded[f.documentNodeIdx.getIndex()];
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

            // folding row will change vertical offsets for the targeted
            // tree grid.
            rectGraph.getStoryNode(f.documentNodeIdx)
                .getTreeGrid()
                .node.updatePositions();
            // Row folding will change edge connector positions in the
            // block graph
            updateDocumentBlockGraph(conf);
            // Changed edge connectors mean the whole document layout needs
            // to be updated.
            updateDocumentLayout(conf);
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

Vec<TreeGridRow::Ptr> TreeGridRow::flatThisNested(
    bool withInvisible) const {
    Vec<TreeGridRow::Ptr> result;
    if (withInvisible || isVisible) {
        result.push_back(mshared_from_this());
        if (isOpen) {
            for (auto& sub : nested) {
                result.append(sub->flatThisNested(withInvisible));
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
               nested
                   | rv::transform([&](TreeGridRow::Ptr const& r) -> int {
                         return r->getHeightRecDirect(padding);
                     }),
               0,
               [](int lhs, int rhs) { return lhs + rhs; });
}

Opt<int> TreeGridRow::getHeightRec(int padding) const {
    if (isVisible) {
        return getHeight(padding).value()
             + rs::fold_left(
                   nested
                       | rv::transform(
                           [&](TreeGridRow::Ptr const& r) -> int {
                               return r->getHeightRec(padding).value_or(0);
                           }),
                   0,
                   [](int lhs, int rhs) { return lhs + rhs; });
    } else {
        return std::nullopt;
    }
}

void TreeGridDocument::updatePositions() {
    __perf_trace("gui", "reset table row positions");
    int offset = tableHeaderHeight;
    int index  = 0;

    Func<void(TreeGridRow::Ptr, bool)> aux;
    aux = [&, this](TreeGridRow::Ptr row, bool isVisible) {
        this->rowOrigins.insert_or_assign(row->origin.uniq(), index);
        this->rowPositions.resize_at(index) = offset;
        row->flatIdx                        = index;

        if (isVisible) {
            offset += this->rowPadding;
            offset += row->getHeight().value();
        }
        ++index;

        for (auto& sub : row->nested) {
            aux(sub, isVisible && row->isOpen);
        }
    };

    for (auto& row : rows) { aux(row, row->isVisible); }


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
            !model.rectGraph.storyNodes.nodes.empty(),
            "Cannot render non-annotated story grid with empty graph "
            "nodes");
        auto  id = StoryNodeId::FromValue(0);
        auto& g  = model.rectGraph.storyNodes.nodes.at(id).getTreeGrid();
        render_table(model, g, conf, id, LaneNodePos{0, 0});
    }
}

void StoryGridModel::applyChanges(StoryGridConfig const& conf) {
    if (!ctx.actions.empty()) {
        for (auto const& update : ctx.actions) { apply(update, conf); }
        ctx.actions.clear();
    }
}

void StoryGridGraph::resetBlockLanes(const StoryGridConfig& conf) {}

StoryGridGraph::SemGraphStore StoryGridGraph::SemGraphStore::init(
    const org::ImmAdapter& root,
    StoryGridConfig const& conf,
    StoryGridContext&      ctx) {
    STORY_GRID_MSG_SCOPE(ctx, "Semantic graph init store");
    SemGraphStore res;

    auto doc = TreeGridDocument::from_root(root, conf, ctx);
    res.ctx  = root.ctx.lock();
    res.addGridAnnotationNodes(doc, ctx);
    {
        auto     gv = res.graph.toGraphviz(res.ctx);
        Graphviz gvc;
        gvc.renderToFile("/tmp/sem_graph.png", gv);
        gvc.writeFile("/tmp/sem_graph.dot", gv);
    }

    return res;
}


TreeGridDocument TreeGridDocument::from_root(
    const org::ImmAdapter& node,
    const StoryGridConfig& conf,
    StoryGridContext&      ctx) {
    TreeGridDocument doc = conf.getDefaultDoc();
    __perf_trace_begin("gui", "build doc rows");
    doc.rows = build_rows(node, doc);
    __perf_trace_end("gui");
    doc.updatePositions();

    CTX_MSG(
        fmt("Add root node to the document, grid size={} "
            "row-count={} col-count={} columns={}",
            doc.getSize(),
            doc.rowPositions.size(),
            doc.columns.size(),
            doc.columns));

    return doc;
}

void StoryGridGraph::SemGraphStore::addGridAnnotationNodes(
    TreeGridDocument const& doc,
    StoryGridContext&       ctx) {
    CTX_MSG("Add annotation nodes to document");
    auto __scope = ctx.scopeLevel();

    for (auto const& row : doc.flatRows(true)) {
        org::graph::MapNode subtreeNode{row->origin.uniq()};
        graph.addNode(subtreeNode);
    }

    for (auto const& row : doc.flatRows(true)) {
        // CTX_MSG(fmt("Nested elements for row {}", row->origin));
        // for (auto const& sub : row->origin.sub()) {
        //     CTX_MSG(fmt("- Nested {}", sub));
        // }
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
                addDescriptionListNodes(list, ctx);
            }
        }
    }
}

void StoryGridGraph::SemGraphStore::addDescriptionListNodes(
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

bool StoryGridGraph::FlatNodeStore::isVisible(
    const org::ImmUniqId& id) const {
    Opt<StoryNodeId> node = getStoryNodeId(id);
    if (!node) { return false; }
    if (!nodes.at(node.value()).isTreeGrid()) { return false; }
    Opt<int> origin = nodes.at(node.value())
                          .getTreeGrid()
                          .node.rowOrigins.get(id);
    if (!origin) { return false; }
    return nodes.at(node.value())
        .getTreeGrid()
        .node.getRow(origin.value())
        ->isVisible;
}

StoryGridGraph::BlockGraphStore StoryGridGraph::BlockGraphStore::init(
    const SemGraphStore&   semGraph,
    FlatNodeStore&         storyNodes,
    StoryGridContext&      ctx,
    const StoryGridConfig& conf) {
    STORY_GRID_MSG_SCOPE(ctx, "Update block graph stor");
    BlockGraphStore res;
    res.ir.setVisible(conf.gridViewport);
    auto partition = storyNodes.getGraphPartition(ctx, semGraph);
    res.setPartition(partition, storyNodes, semGraph, conf, ctx);
    res.updateDocumentLayout(conf, ctx, semGraph, storyNodes);
    return res;
}


StoryGridGraph::NodePositionStore StoryGridGraph::NodePositionStore::init(
    StoryGridContext&      ctx,
    BlockGraphStore const& blockGraph) {
    STORY_GRID_MSG_SCOPE(ctx, "Update node positions");
    NodePositionStore res;
    res.lyt = blockGraph.ir.toLayout();

    for (LaneBlockLayout::RectSpec const& rect :
         res.lyt.getRectangles(blockGraph.ir)) {
        res.nodePositions.insert_or_assign(
            blockGraph.toStory(rect.blockId), rect.pos);
    }
    return res;
}

void StoryGridGraph::BlockGraphStore::updateBlockNodes(
    const StoryGridConfig& conf,
    StoryGridContext&      ctx,
    const FlatNodeStore&   storyNodes) {
    ir.syncSize([&](BlockNodeId id) -> ImVec2 {
        return storyNodes
            .getStoryNode(StoryNodeId::FromIndex(id.getIndex()))
            .getSize();
    });
}
