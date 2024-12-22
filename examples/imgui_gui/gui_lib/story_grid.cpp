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

void StoryNode::Text::render(
    StoryGridModel&        model,
    const StoryNodeId&     id,
    StoryGridConfig const& conf) {
    auto& ctx = model.ctx;

    ImGui::PushStyleColor(ImGuiCol_WindowBg, conf.annotationNodeWindowBg);
    auto frameless_vars = push_frameless_window_vars();
    ImGui::SetNextWindowPos(model.graph.getPosition(id) + model.shift);
    ImGui::SetNextWindowSize(getSize());
    if (IM_FN_BEGIN(
            Begin,
            c_fmt("##text_node_window_{}", id),
            nullptr,
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize)) {
        ImGui::BringWindowToDisplayFront(ImGui::GetCurrentWindow());

        auto res = text.render(
            getSize(),
            EditableOrgText::Mode::Multiline,
            fmt("text_node_{}", id));

        if (res) {
            CTX_MSG(fmt("Text edit result {}", res.value()));
            ctx.action(GridAction::EditNodeText{
                .edit = res.value(),
                .id   = id,
            });
        }

        IM_FN_END(End);
    }

    ImGui::PopStyleVar(frameless_vars);
    ImGui::PopStyleColor();
}

void StoryNode::LinkList::render(
    StoryGridModel&        model,
    StoryNodeId const&     id,
    StoryGridConfig const& conf) {
    auto frameless_vars = push_frameless_window_vars();
    ImGui::SetNextWindowPos(model.graph.getPosition(id) + model.shift);
    ImGui::SetNextWindowSize(getSize());
    if (IM_FN_BEGIN(
            Begin,
            c_fmt("##list_{}", id),
            nullptr,
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize)) {
        if (ImGui::IsWindowHovered(
                ImGuiHoveredFlags_RootAndChildWindows
                | ImGuiHoveredFlags_AllowWhenBlockedByPopup
                | ImGuiHoveredFlags_AllowWhenBlockedByActiveItem)
            && ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
            isSelected = !isSelected;
            model.ctx.action(GridAction::LinkListClick{});
        }

        if (IM_FN_BEGIN(
                BeginTable,
                c_fmt("##table_list{}", id),
                1,
                ImGuiTableFlags_Borders              //
                    | ImGuiTableFlags_RowBg          //
                    | ImGuiTableFlags_SizingFixedFit //
                    | ImGuiTableFlags_NoHostExtendX)) {
            ImGui::TableSetupColumn(
                "List", ImGuiTableColumnFlags_WidthFixed, getWidth());

            for (auto& item : items) {
                ImGui::TableNextRow(ImGuiTableRowFlags_None, item.height);
                bool edit = false;
                item.text.render(
                    ImVec2(item.height, item.width),
                    EditableOrgText::Mode::Multiline,
                    fmt("list_{}", id));
            }
            IM_FN_END(EndTable);
        }
        IM_FN_END(End);
    }

    ImGui::PopStyleVar(frameless_vars);
}


void run_story_grid_annotated_cycle(
    StoryGridModel&        model,
    StoryGridConfig const& conf) {
    __perf_trace("gui", "grid model render");
    for (auto const& [node_id, node] : model.graph.getStoryNodes()) {
        LaneNodePos selfPos = model.graph.getBlockPos(node_id).value();
        switch (node->getKind()) {
            case StoryNode::Kind::TreeGrid: {
                node->getTreeGrid().render(model, node_id, conf);
                break;
            }
            case StoryNode::Kind::Text: {
                node->getText().render(model, node_id, conf);
                break;
            }
            case StoryNode::Kind::LinkList: {
                node->getLinkList().render(model, node_id, conf);
                break;
            }
        }
    }

    for (auto const& [key, edge] :
         model.graph.positionStore.lyt.layout.lines) {
        render_edge(edge, model.shift, true, conf.blockGraphConf);
    }
}


Opt<json> story_grid_loop(
    GLFWwindow*      window,
    Vec<Str> const&  file,
    const Opt<json>& in_state,
    StoryGridConfig& conf) {
    auto                start = org::ImmAstContext::init_start_context();
    EditableOrgDocGroup docs{start};
    StoryGridModel      model{&docs};
    model.ctx.setTraceFile("/tmp/story_grid_trace.log");
    for (auto const& f : file) {
        auto doc = docs.addRoot(sem::parseString(readFile(f.toBase())));
        model.documents = docs.migrate(model.documents).value();
        model.addDocument(doc);
        model.ctx.message(fmt("added file {}", f));
        for (auto const& h : docs.history) {
            model.ctx.message(fmt("> {}", h));
        }
    }

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
        frame_start();

        auto frameless_vars = push_frameless_window_vars();
        fullscreen_window_begin();

        if (first) {
            first             = false;
            conf.gridViewport = ImGui::GetMainViewport()->Size;
            model.rebuild(conf);
        }

        if (model.graph.positionStore.debug) {
            render_debug(
                model.graph.positionStore.debug.value(),
                model.shift,
                model.graph.positionStore.lyt.layout);
        }

        run_story_grid_cycle(model, conf);

        ImGui::End();
        ImGui::PopStyleVar(frameless_vars);

        frame_end(window);

        model.applyChanges(conf);
        quit_on_q(window);
    }

    return to_json_eval(model.state);
}


TreeGridCell build_editable_cell(
    org::ImmAdapter       adapter,
    TreeGridColumn const& col,
    StoryGridContext&     ctx);

TreeGridRow::Ptr build_row(
    org::ImmAdapterT<org::ImmSubtree> tree,
    TreeGridDocument&                 doc,
    int&                              flatIdx,
    StoryGridContext&                 ctx) {
    auto result     = TreeGridRow::shared();
    auto title_cell = build_editable_cell(
        tree.getTitle(), doc.getColumn("title"), ctx);

    STORY_GRID_MSG_SCOPE(
        ctx,
        fmt("Story grid row from {}, '{}'",
            tree.id,
            title_cell.getFinalTextValue()));

    result->columns["title"] = title_cell;

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
                            item.at(0), doc.getColumn(column), ctx);
                    }
                }
            }
        }
    }

    for (auto const& sub : tree.subAs<org::ImmSubtree>()) {
        if (!sub->isComment && !sub->isArchived) {
            result->addNested(build_row(sub, doc, flatIdx, ctx));
        }
    }

    return result;
}

Vec<TreeGridRow::Ptr> build_rows(
    org::ImmAdapter   root,
    TreeGridDocument& doc,
    StoryGridContext& ctx) {
    STORY_GRID_MSG_SCOPE(ctx, "Build grid document rows");
    Vec<TreeGridRow::Ptr> result;
    int                   idx = 0;
    for (auto const& tree : root.subAs<org::ImmSubtree>()) {
        result.push_back(build_row(tree, doc, idx, ctx));
    }

    return result;
}

TreeGridCell build_editable_cell(
    org::ImmAdapter       adapter,
    TreeGridColumn const& col,
    StoryGridContext&     ctx) {
    TreeGridCell result{TreeGridCell::Value{}};
    auto&        v = result.getValue();
    v.value        = EditableOrgTextEntry::from_adapter(
        adapter, col.width, col.edit);
    return result;
}

void StoryGridGraph::SemGraphStore::addFootnoteAnnotationNode(
    UnorderedSet<org::ImmUniqId>& visited,
    org::ImmUniqId const&         origin,
    org::ImmAdapter const&        node,
    StoryGridContext&             ctx) {
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
            addStoryNode(targetPath);

            graph.addEdge(
                org::graph::MapEdge{
                    .source = origin,
                    .target = org::graph::MapNode{targetPath},
                },
                org::graph::MapEdgeProp{});

            // CTX_MSG(
            //     fmt("Found recursive target, {} is targeting {}",
            //         targetPath.id,
            //         link->ctx.lock()->adapt(targetPath).id));

            addFootnoteAnnotationNode(
                visited,
                targetPath,
                link->ctx.lock()->adapt(targetPath),
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
    for (auto const& node : semGraph.graphGroupRoots) {
        res.add(semGraph.ctx->adapt(node), conf, ctx);
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
                setOrgNodeOrigin(t.node.origin.uniq(), idx);
                for (auto const& row : t.node.flatRows(true)) {
                    setOrgNodeOrigin(row->origin.uniq(), idx);
                }
            },
            [&](StoryNode::Text const& t) {
                setOrgNodeOrigin(t.origin.uniq(), idx);
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

    partition = inPartition;
    STORY_GRID_MSG_SCOPE(
        ctx, fmt("Grid annotation from {}", inPartition.size()));

    auto addToLaneCached = [&](int lane, StoryNodeId id) -> LaneNodePos {
        if (auto pos = ir.getBlockPos(toBlock(id))) {
            return pos.value();
        } else {
            return addToLane(lane, id, conf, storyNodes);
        }
    };

    for (auto const& [group_idx, group] : enumerate(partition)) {
        STORY_GRID_MSG_SCOPE(
            ctx,
            fmt("Partition {} has {} items", group_idx, group.size()));
        for (auto const& [node_idx, node] : enumerate(group)) {
            org::ImmUniqId source_adapter = node.source.id;
            org::ImmUniqId source_root = semGraph.getRoot(node.source.id);
            StoryNodeId    source_id //
                = storyNodes.getStoryNodeId(source_root).value();
            LaneNodePos source_node //
                = addToLaneCached(node.sourceLane, source_id);

            // Annotation only has a source block, but no outgoing target
            // nodes.
            if (!node.target.has_value()) { continue; }

            org::ImmUniqId target_adapter = node.target->id;
            org::ImmUniqId target_root = semGraph.getRoot(node.target->id);
            StoryNodeId    target_id //
                = storyNodes.getStoryNodeId(target_root).value();

            LaneNodePos target_node //
                = addToLaneCached(node.targetLane.value(), target_id);

            CTX_MSG(
                fmt("Partition node [{}][{}] source:{}->{} target:{}->{} "
                    "is placed as nodes source:{} target:{}",
                    node.sourceLane,
                    node_idx,
                    source_adapter.id,
                    source_root.id,
                    target_adapter.id,
                    target_root.id,
                    source_node,
                    target_node));

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
                            // if (overlap) {
                            //     ir.at(pos).isVisible = true;
                            // } else {
                            //     ir.at(pos).isVisible = false;
                            // }
                        }
                    }
                }
            }
        }
    }
}

void StoryGridGraph::BlockGraphStore::updateBlockState(
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
    updateBlockNodes(conf, ctx, storyNodes);
    updateHiddenRowConnection(conf, ctx, semGraph, storyNodes);
}

void StoryGridModel::updateGridState() {
    Vec<org::graph::MapNode> docNodes;
    for (auto const& [_, node] : graph.getStoryNodes()) {
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

Vec<Vec<StoryGridAnnotation>> StoryGridGraph::FlatNodeStore::getPartition(
    StoryGridContext&    ctx,
    SemGraphStore const& semGraph) const {

    using org::graph::MapNode;
    __perf_trace("gui", "partition graph by distance");
    auto initial_nodes = getInitialNodes(ctx, semGraph);
    {
        STORY_GRID_MSG_SCOPE(
            ctx, fmt("Partition graph nodes, initial nodes:"));
        for (auto const& i : initial_nodes) {
            CTX_MSG(fmt(
                "{} {} parent {}", i.id.id, i, semGraph.getRoot(i.id).id));
        }
    }

    STORY_GRID_MSG_SCOPE(ctx, "Partition flat node");

    LOGIC_ASSERTION_CHECK(
        !initial_nodes.empty(),
        "Cannot partition graph with no initial nodes");

    // Graph partition uses nodes found by the sem graph, without
    // converting to the parent nodes. This way `setPartition` can compute
    // specific offsets for tree and list item rows.
    Vec<Vec<StoryGridAnnotation>> result;


    // Construct partition mapping using simple DFS pre-visit traversal.
    // Starting nodes will go to the visit lane 0, their target nodes will
    // go to lane 1 etc.
    Func<void(MapNode const&, int)> dfsPartition;
    UnorderedSet<MapNode>           visited;
    UnorderedMap<MapNode, int>      lanePlacementRedirect;

    // auto get_final_lane = [&](){};

    auto add_annotation = [&](int                 distance,
                              StoryGridAnnotation annotation) {
        int idx = result.resize_at(distance).push_back_idx(annotation);
        CTX_MSG(
            fmt("Set [{}][{}] = [{}] -> [{}] {}->{}",
                distance,
                idx,
                annotation.sourceLane,
                annotation.targetLane,
                annotation.source.id.id,
                annotation.target.value_or(MapNode{}).id.id));
    };

    dfsPartition = [&](MapNode const& current, int distance) {
        STORY_GRID_MSG_SCOPE(
            ctx,
            fmt("DFS node {} at depth {}, parent is {}",
                current.id.id,
                distance,
                semGraph.getRoot(current.id).id));
        if (visited.contains(current)) {
            return;
        } else {
            visited.incl(current);
            bool addedCurrent = false;
            for (MapNode const& adj : semGraph.graph.outNodes(current)) {
                if (!visited.contains(adj)) {
                    add_annotation(
                        distance,
                        StoryGridAnnotation{
                            .sourceLane = distance,
                            .targetLane = distance + 1,
                            .source     = current.id,
                            .target     = adj.id,
                        });
                    addedCurrent = true;
                }
                dfsPartition(adj, distance + 1);
            }

            for (MapNode const& adj : semGraph.graph.inNodes(current)) {
                if (!visited.contains(adj)) {
                    add_annotation(
                        distance,
                        StoryGridAnnotation{
                            .sourceLane = distance,
                            // If the distnace is equal to 0, it means DFS
                            // is currently visiting one of the initial
                            // nodes. Initial nodes are always placed as
                            // the leftmost items, so `distance + 1` is the
                            // corner to ensure correct placement.
                            .targetLane = distance <= 1 ? distance + 1
                                                        : distance - 1,
                            .source     = adj.id,
                            .target     = current.id,
                        });
                    addedCurrent = true;
                }
                dfsPartition(adj, distance + 1);
            }

            // if the current node does not have any outgoing elements it
            // still must be added to the graph.
            if (!addedCurrent) {
                result.resize_at(distance).push_back(StoryGridAnnotation{
                    .sourceLane = distance,
                    .source     = current.id,
                });
            }
        }
    };

    for (const auto& node : initial_nodes) { dfsPartition(node, 0); }


    std::string partition_debug //
        = result
        | rv::transform(
              [&](Vec<StoryGridAnnotation> const& p) -> std::string {
                  return p
                       | rv::transform(
                             [&](StoryGridAnnotation const& p)
                                 -> std::string {
                                 if (p.target) {
                                     return fmt(
                                         "[{}->{}]@{}",
                                         p.source.id.id,
                                         p.target->id.id,
                                         semGraph.getRoot(p.source.id).id);
                                 } else {
                                     return fmt(
                                         "[{}]@{}",
                                         p.source.id.id,
                                         semGraph.getRoot(p.source.id).id);
                                 }
                             })
                       | rv::intersperse(" - - ") //
                       | rv::join                 //
                       | rs::to<std::string>();
              })
        | rv::intersperse("\n") //
        | rv::join              //
        | rs::to<std::string>();

    CTX_MSG(
        fmt("Created partition with {} lanes. Root node partition "
            "placement:\n{}",
            result.size(),
            partition_debug));

    return result;
}

Vec<org::graph::MapNode> StoryGridGraph::FlatNodeStore::getInitialNodes(
    StoryGridContext&    ctx,
    SemGraphStore const& semGraph) const {
    Vec<org::graph::MapNode> docNodes;
    for (auto const& node : nodes.items()) {
        if (node->isTreeGrid()) {
            bool foundLinkedSubtree = false;
            auto flat = node->getTreeGrid().node.flatRows(true);
            for (const TreeGridRow::Ptr& row : flat) {

                auto tree = row->origin.uniq();
                if (!semGraph.graph.adjList.at(tree).empty()
                    || !semGraph.graph.inNodes(tree).empty()) {
                    foundLinkedSubtree = true;
                    docNodes.push_back(tree);
                }
            }

            // If the document has no annotations it still needs to be
            // shown as a story grid entry.
            if (!foundLinkedSubtree) {
                docNodes.push_back(flat.at(0)->origin.uniq());
            }
        }
    }

    return sorted(docNodes);
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
        CTX_MSG(
            fmt("Text node {} mapped to Text node {}, \"{}\"",
                node.id,
                annotation,
                escape_literal(text.text.getFinalValue())));

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

    auto __log_diff = OLOG_SINK_FACTORY_SCOPED(
        ::org_logging::log_differential_sink_factory{
            "/tmp/story_grid_model_apply.diff"});


    auto as_sem_list = [](sem::OrgArg doc) -> Vec<sem::SemId<sem::Org>> {
        if (doc->is(OrgSemKind::Document)) {
            return Vec<sem::SemId<sem::Org>>{doc.begin(), doc.end()};
        } else {
            return {doc};
        }
    };

    switch (act.getKind()) {
        case GridAction::Kind::EditCell: {
            auto edit = act.getEditCell().edit;
            if (edit.isChanged()) {
                auto ast = history->replaceNode(
                    edit.origin, edit.value.value());
                history->extendHistory(ast);
                rebuild(conf);
            } else {
                graph.cascadeGeometryUpdate(
                    act.getEditCell().id, ctx, conf);
            }
            break;
        }

        case GridAction::Kind::EditNodeText: {
            auto edit = act.getEditNodeText();
            if (edit.edit.isChanged()) {
                auto text = edit.edit.value.value();
                CTX_MSG(fmt(
                    "Updated edit node text {}", escape_literal(text)));
                auto ast = history->replaceNode(
                    graph.getStoryNode(edit.id).getText().origin, text);
                history->extendHistory(ast);
                rebuild(conf);
            } else {
                graph.cascadeGeometryUpdate(
                    act.getEditCell().id, ctx, conf);
            }
            break;
        }

        case GridAction::Kind::Scroll: {
            auto const& scroll = act.getScroll();
            graph.cascadeScrollingUpdate(
                scroll.pos, scroll.direction, ctx, conf);
            break;
        }

        case GridAction::Kind::LinkListClick: {
            graph.focusLinkListTargetRows(ctx);
            graph.cascadeBlockGraphUpdate(ctx, conf);
            break;
        }

        case GridAction::Kind::RowFolding: {
            auto const& f    = act.getRowFolding();
            auto&       g    = graph.getStoryNode(f.id).getTreeGrid();
            auto        row  = g.node.getRow(f.flatIdx);
            auto&       map  = state.folded[f.id.getIndex()];
            auto        path = row->getOriginPath();
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
            graph.getStoryNode(f.id).getTreeGrid().node.updatePositions();
            // Row folding will change edge connector positions in the
            // block graph. Changed edge connectors mean the whole document
            // layout needs to be updated.
            graph.updateNodeLanePlacement(ctx, conf);
            graph.updateNodePositions(ctx, conf);
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
                     return columns.at(col).getSize().y;
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
            !model.graph.storyNodes.nodes.empty(),
            "Cannot render non-annotated story grid with empty graph "
            "nodes");
        auto  id = StoryNodeId::FromValue(0);
        auto& g  = model.graph.storyNodes.nodes.at(id).getTreeGrid();
        g.render(model, id, conf);
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
    Vec<org::ImmAdapter> const& root,
    StoryGridConfig const&      conf,
    StoryGridContext&           ctx) {
    LOGIC_ASSERTION_CHECK(
        !root.empty(),
        "Cannot update story grid graph with empty list of nodes");
    STORY_GRID_MSG_SCOPE(ctx, "Semantic graph init store");
    SemGraphStore res;

    res.ctx = root.front().ctx.lock();
    for (auto const& r : root) {
        STORY_GRID_MSG_SCOPE(ctx, fmt("Add root node {} {}", r.id, r));
        res.addDocNode(r, conf, ctx);
    }

    {
        auto     gv = res.graph.toGraphviz(res.ctx);
        Graphviz gvc;
        gv.setRankDirection(Graphviz::Graph::RankDirection::LR);
        gvc.renderToFile(
            "/tmp/sem_graph.png",
            gv,
            Graphviz::RenderFormat::PNG,
            Graphviz::LayoutType::Fdp);

        gvc.writeFile("/tmp/sem_graph.dot", gv);
    }

    STORY_GRID_MSG_SCOPE(ctx, "Created semantic graph");
    {
        STORY_GRID_MSG_SCOPE(ctx, "Explicit roots in the graph");
        for (auto const& r : res.graphGroupRoots) {
            CTX_MSG(fmt("{}", r.id));
        }
    }

    {
        STORY_GRID_MSG_SCOPE(
            ctx, "Adjacency list with annotation parents");
        for (auto const& r : sorted(res.graph.adjList.keys())) {
            Vec<std::string> dbg //
                = own_view(
                      sorted(res.graph.adjNodes(org::graph::MapNode{r})))
                | rv::transform(
                      [](org::graph::MapNode const& n) -> std::string {
                          return fmt1(n.id.id);
                      })
                | rs::to<Vec>();
            auto parent = res.annotationParents.get(r.id);
            CTX_MSG(
                fmt("{} (-> {} parent) -> {}",
                    r.id.id,
                    parent ? fmt1(parent.value().id) : "nil",
                    dbg));
        }
    }


    return res;
}


TreeGridDocument TreeGridDocument::from_root(
    const org::ImmAdapter& node,
    const StoryGridConfig& conf,
    StoryGridContext&      ctx) {
    TreeGridDocument doc = conf.getDefaultDoc();
    doc.origin           = node.as<org::ImmDocument>();
    __perf_trace_begin("gui", "build doc rows");
    doc.rows = build_rows(node, doc, ctx);
    __perf_trace_end("gui");


    UnorderedSet<Str> emptyColumns;
    for (auto const& it : doc.columns) { emptyColumns.incl(it.name); }

    for (auto const& row : doc.flatRows(true)) {
        for (auto const& [col, cell] : row->columns) {
            emptyColumns.excl(col);
        }
    }

    while (!emptyColumns.empty()) {
        Str  toRemove = *emptyColumns.begin();
        auto iter     = std::find_if(
            doc.columns.begin(),
            doc.columns.end(),
            [&](TreeGridColumn const& col) {
                return col.name == toRemove;
            });

        if (iter != doc.columns.end()) {
            CTX_MSG(
                fmt("Column '{}' has no cells, dropping empty column",
                    toRemove));
            doc.columns.erase(iter);
        }

        emptyColumns.erase(toRemove);
    }

    doc.updatePositions();
    return doc;
}

void StoryGridGraph::SemGraphStore::addDocNode(
    const org::ImmAdapter& node,
    const StoryGridConfig& conf,
    StoryGridContext&      ctx) {

    auto doc  = TreeGridDocument::from_root(node, conf, ctx);
    auto flat = doc.flatRows(true);
    if (!flat.empty()) {
        addStoryNode(node.uniq());
        for (auto const& row : flat) {
            setParent(row->origin.uniq(), node.uniq());
        }

        CTX_MSG(
            fmt("Add root node to the document, grid size={} "
                "row-count={} col-count={} columns={}",
                doc.getSize(),
                doc.rowPositions.size(),
                doc.columns.size(),
                doc.columns));


        addGridAnnotationNodes(doc, ctx);
    }
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

            addStoryNode(commentNode.id);
            addFootnoteAnnotationNode(commentNode.id, nested, ctx);
        }

        for (auto const& list : row->origin.subAs<org::ImmList>()) {
            if (list.isDescriptionList()
                && org::graph::isAttachedDescriptionList(list)) {
                addDescriptionListNodes(list, ctx);
            }
        }
    }
}

void StoryGridGraph::SemGraphStore::addDescriptionListNodes(
    const org::ImmAdapterT<org::ImmList>& list,
    StoryGridContext&                     ctx) {

    if (!rs::any_of(
            list.subAs<org::ImmListItem>(),
            [&](org::ImmAdapterT<org::ImmListItem> const& item) {
                return org::graph::isLinkedDescriptionItemNode(item);
            })) {
        return;
    }

    org::graph::MapNode listNode{list.uniq()};
    addStoryNode(list.uniq());
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

                    setParent(item.uniq(), list.uniq());
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
    STORY_GRID_MSG_SCOPE(ctx, "Update block graph store");
    BlockGraphStore res;
    res.ir.setVisible(conf.gridViewport);
    auto partition = storyNodes.getPartition(ctx, semGraph);
    res.setPartition(partition, storyNodes, semGraph, conf, ctx);
    res.updateBlockState(conf, ctx, semGraph, storyNodes);
    return res;
}


StoryGridGraph::NodePositionStore StoryGridGraph::NodePositionStore::init(
    StoryGridContext&      ctx,
    BlockGraphStore const& blockGraph) {
    STORY_GRID_MSG_SCOPE(ctx, "Init node position store");
    NodePositionStore res;
    LOGIC_ASSERTION_CHECK(
        !blockGraph.ir.idToPos.empty(),
        "Block graph has empty ID to position mapping, nothing to "
        "position on the graph");
    {
        STORY_GRID_MSG_SCOPE(ctx, "Create graph layout");
        for (auto const& [id, pos] : blockGraph.ir.idToPos) {
            CTX_MSG(fmt("Id {} pos {}", id, pos));
        }
        res.lyt = blockGraph.ir.getLayout();
        CTX_MSG(fmt("Layout for {} rectangles", res.lyt.rectMap.size()));
    }

    for (LaneBlockLayout::RectSpec const& rect :
         res.lyt.getRectangles(blockGraph.ir)) {
        CTX_MSG(fmt("Node position {}", rect));
        if (rect.isVisible) {
            res.nodePositions.insert_or_assign(
                blockGraph.toStory(rect.blockId), rect.pos);
        }
    }

    res.debug = res.lyt.getConstraintDebug();

    CTX_MSG(fmt(
        "Constraint debug:\n{}", res.debug->toString().toString(false)));

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

void StoryGridGraph::cascadeScrollingUpdate(
    const ImVec2&          graphPos,
    float                  direction,
    StoryGridContext&      ctx,
    const StoryGridConfig& conf) {
    {
        STORY_GRID_MSG_SCOPE(ctx, "Add scrolling to graph");
        blockGraph.ir.addScrolling(
            graphPos, -direction * conf.mouseScrollMultiplier);
    }
    cascadeNodePositionsUpdate(ctx, conf);
}

void StoryGridGraph::cascadeSemanticUpdate(
    const Vec<org::ImmAdapter>& root,
    StoryGridContext&           ctx,
    const StoryGridConfig&      conf) {
    {
        STORY_GRID_MSG_SCOPE(ctx, "Semantic update");
        updateSemanticGraph(root, ctx, conf);
    }
    cascadeStoryNodeUpdate(ctx, conf);
}

void StoryGridGraph::cascadeStoryNodeUpdate(
    StoryGridContext&      ctx,
    const StoryGridConfig& conf) {
    {
        STORY_GRID_MSG_SCOPE(ctx, "Story node update");
        updateStoryNodes(ctx, conf);
    }
    cascadeBlockGraphUpdate(ctx, conf);
}

void StoryGridGraph::cascadeBlockGraphUpdate(
    StoryGridContext&      ctx,
    const StoryGridConfig& conf) {
    {
        STORY_GRID_MSG_SCOPE(ctx, "Block graph update");
        updateNodeLanePlacement(ctx, conf);
    }
    cascadeNodePositionsUpdate(ctx, conf);
}

void StoryGridGraph::cascadeNodePositionsUpdate(
    StoryGridContext&      ctx,
    const StoryGridConfig& conf) {
    {
        STORY_GRID_MSG_SCOPE(ctx, "Node positions update");
        updateNodePositions(ctx, conf);
    }
}

void StoryGridGraph::cascadeGeometryUpdate(
    const StoryNodeId&     id,
    StoryGridContext&      ctx,
    const StoryGridConfig& conf) {
    {
        STORY_GRID_MSG_SCOPE(ctx, fmt("Geometry update for {}", id));
        updateGeometry(id);
    }
    cascadeNodePositionsUpdate(ctx, conf);
}
