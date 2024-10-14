#include "block_graph.hpp"
#include <hstd/wrappers/adaptagrams_wrap/adaptagrams_ir.hpp>
#include <hstd/stdlib/Enumerate.hpp>
#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/Ranges.hpp>
#include <hstd/stdlib/Debug.hpp>
#include "imgui_utils.hpp"

using GC = GraphNodeConstraint;

GC::Align::Spec spec(int rect) { return GC::Align::Spec{.node = rect}; }

DocLayout to_layout(DocGraph const& g) {
    DocLayout lyt;

    Vec<GC::Align>       laneAlignments;
    Vec<GC::Align::Spec> topLaneAlign;
    for (auto const& [lane_idx, lane] : enumerate(g.lanes)) {
        Slice<int> visibleBlocks = lane.getVisibleBlocks(
            slice<int>(0, int(g.visible.height())));
        if (visibleBlocks.first == visibleBlocks.last
            && visibleBlocks.first == -1) {
            continue;
        }

        Opt<GC::Align::Spec> first;
        for (int row : visibleBlocks) {
            DocNode node{.lane = lane_idx, .row = row};
            lyt.ir.rectangles.push_back(GraphSize{
                .w = static_cast<double>(lane.blocks.at(row).width),
                .h = static_cast<double>(lane.blocks.at(row).height),
            });

            int idx = lyt.ir.rectangles.high();
            lyt.rectMap.insert_or_assign(node, idx);
            if (!first) {
                first = GC::Align::Spec{
                    .node   = idx,
                    .offset = static_cast<double>(
                        lane.getBlockHeightStart(row)),
                };
            }
        }

        if (first) { topLaneAlign.push_back(first.value()); }

        GC::Align align;

        for (auto const& row : visibleBlocks) {
            DocNode node{.lane = lane_idx, .row = row};
            align.nodes.push_back(
                GC::Align::Spec{.node = lyt.rectMap.at(node)});

            auto next_row = row + 1;
            if (visibleBlocks.contains(next_row)) {
                DocNode next{.lane = lane_idx, .row = next_row};
                lyt.ir.nodeConstraints.push_back(GraphNodeConstraint{GC::Separate{
                    .left = GC::
                        Align{.nodes = Vec{spec(lyt.rectMap.at(node))}, .dimension = GraphDimension::YDIM},
                    .right = GC::
                        Align{.nodes = Vec{spec(lyt.rectMap.at(next))}, .dimension = GraphDimension::YDIM},
                    .separationDistance //
                    = float(
                        float(
                            lane.blocks.at(row).height
                            + lane.blocks.at(next_row).height)
                            / 2.0f
                        + lane.blocks.at(row).bottomMargin
                        + lane.blocks.at(next_row).topMargin),
                    .isExactSeparation = true,
                    .dimension         = GraphDimension::YDIM,
                }});
            }
        }

        align.dimension = GraphDimension::XDIM;
        laneAlignments.push_back(align);
    }

    _dbg(topLaneAlign);
    lyt.ir.nodeConstraints.push_back(GraphNodeConstraint{GC::Align{
        .nodes     = topLaneAlign,
        .dimension = GraphDimension::YDIM,
    }});

    for (auto const& [lane_idx, lane] : enumerate(g.lanes)) {
        if (lane_idx < g.lanes.high()) {
            int         next_idx = lane_idx + 1;
            auto const& next     = g.lanes.at(next_idx);

            float lane_width //
                = rs::max(
                    lane.blocks | rv::transform([](DocBlock const& b) {
                        return float(b.width);
                    }));

            float next_width //
                = rs::max(
                    next.blocks | rv::transform([](DocBlock const& b) {
                        return float(b.width);
                    }));

            lyt.ir.nodeConstraints.push_back(
                GraphNodeConstraint{GC::Separate{
                    .left  = laneAlignments.at(lane_idx),
                    .right = laneAlignments.at(next_idx),
                    .separationDistance //
                    = float(
                        float(lane_width + next_width) / 2.0f
                        + lane.rightMargin + next.leftMargin),
                    .isExactSeparation = true,
                    .dimension         = GraphDimension::XDIM,
                }});
        }
    }

    for (auto const& lane : enumerator(g.lanes)) {
        for (auto const& row : lane.value().visibleRange) {
            DocNode source{.lane = lane.index(), .row = row};
            for (auto const& target : g.at(source).outEdges) {
                if (lyt.rectMap.contains(source)
                    && lyt.rectMap.contains(target)) {
                    GraphEdge edge{
                        lyt.rectMap.at(source),
                        lyt.rectMap.at(target),
                    };
                    lyt.ir.edges.push_back(edge);
                    lyt.ir.edgeConstraints.insert_or_assign(
                        edge,
                        GraphEdgeConstraint{
                            .sourcePort = GraphEdgeConstraint::Port::East,
                            .targetPort = GraphEdgeConstraint::Port::West,
                        });
                }
            }
        }
    }

    return lyt;
}

DocNode n(int lane, int row) { return DocNode{.lane = lane, .row = row}; }

void render_point(const GraphPoint& point, ImVec2 const& shift) {
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    draw_list->AddCircleFilled(
        ImVec2(point.x, point.y) + shift, 3.0f, IM_COL32(255, 0, 0, 255));
}

void render_path(const GraphPath& path, ImVec2 const& shift) {
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    for (size_t i = 0; i < path.points.size() - 1; ++i) {
        const GraphPoint& p1 = path.points[i];
        const GraphPoint& p2 = path.points[i + 1];
        draw_list->AddLine(
            ImVec2(p1.x, p1.y) + shift,
            ImVec2(p2.x, p2.y) + shift,
            IM_COL32(0, 255, 0, 255),
            2.0f);
    }
}

void render_rect(const GraphRect& rect, ImVec2 const& shift) {
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    draw_list->AddRect(
        ImVec2(rect.left, rect.top) + shift,
        ImVec2(rect.left + rect.width, rect.top + rect.height) + shift,
        IM_COL32(0, 0, 255, 255),
        0.0f,
        0,
        2.0f);
}

void render_edge(const GraphLayoutIR::Edge& edge, ImVec2 const& shift) {
    for (const auto& path : edge.paths) { render_path(path, shift); }
    if (edge.labelRect.has_value()) {
        render_rect(edge.labelRect.value(), shift);
    }
}

void render_result(GraphLayoutIR::Result const& res, ImVec2 const& shift) {
    for (auto const& rect : res.fixed) { render_rect(rect, shift); }
    for (auto const& [key, path] : res.lines) { render_edge(path, shift); }
}

void graph_render_loop(DocGraph const& g, GLFWwindow* window) {
    auto lyt  = to_layout(g);
    auto col  = lyt.ir.doColaLayout();
    auto conv = col.convert();

    ImVec2 shift{20, 20};

    while (!glfwWindowShouldClose(window)) {
        frame_start();
        fullscreen_window_begin();
        render_result(conv, shift);
        ImGui::End();
        frame_end(window);
    }
}

void run_block_graph_test(GLFWwindow* window) {
    int  w     = 75;
    int  h     = 50;
    auto lane0 = Vec<DocBlock>{
        // 0.0
        DocBlock{.width = w, .height = h, .outEdges = {n(1, 0)}},
        // 0.1
        DocBlock{
            .width    = w,
            .height   = h,
            .outEdges = {n(1, 1), n(1, 2), n(1, 3)}},
        // 0.2
        DocBlock{.width = w, .height = h, .outEdges = {n(1, 4)}},
    };

    auto lane1 = Vec<DocBlock>{
        // 1.0
        DocBlock{.width = w, .height = h, .outEdges = {n(2, 0)}},
        // 1.1
        DocBlock{.width = w, .height = h, .outEdges = {n(2, 0), n(2, 1)}},
        // 1.2
        DocBlock{.width = w, .height = h, .outEdges = {n(2, 1)}},
        // 1.3
        DocBlock{.width = w, .height = h, .outEdges = {n(2, 1), n(2, 2)}},
        // 1.4
        DocBlock{.width = w, .height = h, .outEdges = {n(2, 1), n(2, 3)}},
    };

    auto lane2 = Vec<DocBlock>{
        // 2.0
        DocBlock{.width = w, .height = h},
        // 2.1
        DocBlock{.width = w, .height = h},
        // 2.2
        DocBlock{.width = w, .height = h},
        // 2.3
        DocBlock{.width = w, .height = h},
    };

    DocGraph g{
        .lanes
        = {DocBlockStack{
               .blocks       = lane0,
               .visibleRange = slice(0, 2),
           },
           DocBlockStack{
               .blocks       = lane1,
               .visibleRange = slice(0, 4),
           },
           DocBlockStack{
               .blocks       = lane2,
               .visibleRange = slice(0, 3),
           }},
        .visible = GraphSize{
            .w = 1200,
            .h = 1200,
        }};

    g.lanes.at(1).scrollOffset -= 100;
    for (int i = 0; i < 5; ++i) {
        auto lyt = to_layout(g);
        g.lanes.at(1).scrollOffset += 100;
        lyt.ir.height = 10000;
        lyt.ir.width  = 10000;
        auto col      = lyt.ir.doColaLayout();
        col.router->outputInstanceToSVG(
            fmt("/tmp/run_block_graph_test_{}", i));
    }

    graph_render_loop(g, window);
}

int DocBlockStack::getBlockHeightStart(int blockIdx) const {
    int start = scrollOffset;
    for (int i = 0; i < blockIdx; ++i) {
        start += blocks.at(i).fullHeight();
    }
    return start;
}

bool DocBlockStack::inSpan(int blockIdx, Slice<int> heightRange) const {
    auto span = blocks.at(blockIdx).heightSpan(
        getBlockHeightStart(blockIdx));
    return heightRange.overlap(span).has_value();
}

Slice<int> DocBlockStack::getVisibleBlocks(Slice<int> heightRange) const {
    Slice<int> res;
    res.first = -1;
    res.last  = -1;
    for (int block : visibleRange) {
        if (inSpan(block, heightRange)) {
            if (res.last == -1) {
                res.last = block;
            } else {
                res.last = std::max(block, res.last);
            }

            if (res.first == -1) {
                res.first = block;
            } else {
                res.first = std::min(block, res.first);
            }
        }
    }

    return res;
}
