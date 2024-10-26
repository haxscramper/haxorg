#include "block_graph.hpp"
#include <hstd/wrappers/adaptagrams_wrap/adaptagrams_ir.hpp>
#include <hstd/stdlib/Enumerate.hpp>
#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/Ranges.hpp>
#include <hstd/stdlib/Debug.hpp>
#include "imgui_utils.hpp"

using GC = GraphNodeConstraint;

GC::Align::Spec spec(int rect, int offset = 0) {
    return GC::Align::Spec{
        .node   = rect,
        .offset = static_cast<double>(offset),
    };
}

LaneBlockLayout to_layout(LaneBlockGraph const& g) {
    LaneBlockLayout lyt;

    Vec<GC::Align>       laneAlignments;
    Vec<GC::Align::Spec> topLaneAlign;
    for (auto const& [lane_idx, lane] : enumerate(g.lanes)) {
        Vec<int> visibleBlocks = lane.getVisibleBlocks(
            slice<int>(0, int(g.visible.height())));
        // _dfmt(lane_idx, visibleBlocks);
        if (visibleBlocks.empty()) { continue; }

        Opt<GC::Align::Spec> first;
        for (int row : visibleBlocks) {
            LaneNodePos node{.lane = lane_idx, .row = row};
            lyt.ir.rectangles.push_back(GraphSize{
                .w = static_cast<double>(lane.blocks.at(row).width),
                .h = static_cast<double>(lane.blocks.at(row).height),
            });

            int idx = lyt.ir.rectangles.high();
            lyt.rectMap.insert_or_assign(node, idx);
            if (!first) {
                first = GC::Align::Spec{
                    .node   = idx,
                    .offset = lane.blocks.at(row).fullHeight() / 2.0f
                            + lane.scrollOffset,
                };
            }
        }

        if (first) { topLaneAlign.push_back(first.value()); }

        GC::Align align;

        for (auto const& row : visibleBlocks) {
            LaneNodePos node{.lane = lane_idx, .row = row};
            align.nodes.push_back(spec(lyt.rectMap.at(node)));

            auto next_row = row + 1;
            if (visibleBlocks.contains(next_row)) {
                LaneNodePos next{.lane = lane_idx, .row = next_row};
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

    // _dbg(topLaneAlign);
    lyt.ir.nodeConstraints.push_back(GraphNodeConstraint{GC::Align{
        .nodes     = topLaneAlign,
        .dimension = GraphDimension::YDIM,
    }});

    for (auto const& [lane_idx, lane] : enumerate(g.lanes)) {
        if (lane_idx < g.lanes.high()) {
            int         next_idx = lane_idx + 1;
            auto const& next     = g.lanes.at(next_idx);

            if (!laneAlignments.has(next_idx)) { continue; }

            float lane_width = lane.getWidth();
            float next_width = next.getWidth();

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

    int edgeId = 0;
    for (auto const& lane : enumerator(g.lanes)) {
        for (auto const& row : lane.value().visibleRange) {
            LaneNodePos source{.lane = lane.index(), .row = row};
            if (!g.edges.contains(source)) { continue; }
            for (LaneNodeEdge const& target : g.edges.at(source)) {
                if (lyt.rectMap.contains(source)
                    && lyt.rectMap.contains(target.target)) {
                    GraphEdge edge{
                        .source = lyt.rectMap.at(source),
                        .target = lyt.rectMap.at(target.target),
                        .bundle = ++edgeId,
                    };
                    lyt.ir.edges.push_back(edge);
                    GraphEdgeConstraint ec{
                        .sourcePort = target.sourcePort,
                        .targetPort = target.targetPort,
                    };


                    if (target.targetOffset) {
                        auto full   = g.at(target.target).height;
                        auto offset = target.targetOffset.value();
                        LOGIC_ASSERTION_CHECK(
                            offset <= full, "{} !<= {}", offset, full);
                        ec.sourceOffset = float(offset) / float(full);
                        int step        = 6;
                        ec.targetCheckpoint //
                            = (g.lanes.at(target.target.lane).blocks.size()
                               * step)
                            - (target.target.row * step);
                    }

                    if (target.sourceOffset) {
                        auto full   = g.at(source).height;
                        auto offset = target.sourceOffset.value();
                        LOGIC_ASSERTION_CHECK(
                            offset <= full, "{} !<= {}", offset, full);
                        ec.sourceOffset = float(offset) / float(full);
                        int step        = 6;
                        ec.sourceCheckpoint //
                            = (g.lanes.at(target.target.lane).blocks.size()
                               * step)
                            - (target.target.row * step);
                    }

                    lyt.ir.edgeConstraints.insert_or_assign(edge, ec);
                }
            }
        }
    }

    return lyt;
}


float line_width = 4.0f;

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
            line_width);
    }
}


void render_bezier_path(const GraphPath& path, ImVec2 const& shift) {
    if (path.points.size() < 2) { return; }

    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    std::vector<ImVec2> base_points;
    base_points.reserve(path.points.size());
    for (const auto& p : path.points) {
        base_points.push_back(ImVec2(p.x, p.y));
    }

    ImVec2 bezier_start_offset = ImVec2(120, 0);
    ImVec2 bezier_end_offset   = ImVec2(-120, 0);


    auto draw_offset_curve =
        [&](float y_offset, ImU32 color, float thickness) {
            std::vector<ImVec2> offset_points = base_points;
            for (auto& p : offset_points) {
                p.y += y_offset;
                p += shift;
            }

            if (offset_points.size() == 4) {
                draw_list->AddBezierCubic(
                    offset_points[0],
                    offset_points[1] + bezier_start_offset,
                    offset_points[2] + bezier_end_offset,
                    offset_points[3],
                    color,
                    thickness);
            } else {
                draw_list->AddBezierCubic(
                    offset_points[0],
                    offset_points[1],
                    offset_points[2],
                    offset_points[3],
                    color,
                    thickness);

                for (size_t i = 3; i < offset_points.size(); i += 3) {
                    size_t remaining = offset_points.size() - i;
                    if (4 <= remaining) {
                        draw_list->AddBezierCubic(
                            offset_points[i],
                            offset_points[i + 1],
                            offset_points[i + 2],
                            offset_points[i + 3],
                            color,
                            thickness);
                    }
                }
            }
        };

    const float width = 4.0f;
    draw_offset_curve(-width + 1.0f, IM_COL32(255, 255, 255, 200), 1.0f);
    draw_offset_curve(0, IM_COL32(128, 128, 128, 128), width - 2.0f);
    draw_offset_curve(+width - 1.0f, IM_COL32(255, 255, 255, 200), 1.0f);
}

void render_rect(const GraphRect& rect, ImVec2 const& shift) {
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    draw_list->AddRect(
        ImVec2(rect.left, rect.top) + shift,
        ImVec2(rect.left + rect.width, rect.top + rect.height) + shift,
        IM_COL32(0, 0, 255, 255),
        0.0f,
        0,
        line_width);
}

void render_edge(
    const GraphLayoutIR::Edge& edge,
    ImVec2 const&              shift,
    bool                       bezier) {
    for (const auto& path : edge.paths) {
        if (bezier) {
            render_bezier_path(path, shift);
        } else {
            render_path(path, shift);
        }
    }
    if (edge.labelRect.has_value()) {
        render_rect(edge.labelRect.value(), shift);
    }
}

void render_result(GraphLayoutIR::Result const& res, ImVec2 const& shift) {
    for (auto const& rect : res.fixed) { render_rect(rect, shift); }
    for (auto const& [key, path] : res.lines) {
        render_edge(path, shift, true);
    }
}

void graph_render_loop(LaneBlockGraph const& g, GLFWwindow* window) {
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


LaneNodeEdge e(int lane, int row) {
    return LaneNodeEdge{.target = LaneNodePos{.lane = lane, .row = row}};
}

LaneNodePos n(int lane, int row) {
    return LaneNodePos{.lane = lane, .row = row};
}

void run_block_graph_test(GLFWwindow* window) {
    int  w     = 75;
    int  h     = 50;
    auto lane0 = Vec<LaneBlockNode>{
        LaneBlockNode{.width = w, .height = h}, // 0.0
        LaneBlockNode{.width = w, .height = h}, // 0.1
        LaneBlockNode{.width = w, .height = h}, // 0.2
    };

    auto lane1 = Vec<LaneBlockNode>{
        LaneBlockNode{.width = w, .height = h}, // 1.0
        LaneBlockNode{.width = w, .height = h}, // 1.1
        LaneBlockNode{.width = w, .height = h}, // 1.2
        LaneBlockNode{.width = w, .height = h}, // 1.3
        LaneBlockNode{.width = w, .height = h}, // 1.4
    };

    auto lane2 = Vec<LaneBlockNode>{
        LaneBlockNode{.width = w, .height = h}, // 2.0
        LaneBlockNode{.width = w, .height = h}, // 2.1
        LaneBlockNode{.width = w, .height = h}, // 2.2
        LaneBlockNode{.width = w, .height = h}, // 2.3
    };

    LaneBlockGraph g{
        .lanes
        = {LaneBlockStack{.blocks = lane0, .visibleRange = slice(0, 2)},
           LaneBlockStack{.blocks = lane1, .visibleRange = slice(0, 4)},
           LaneBlockStack{.blocks = lane2, .visibleRange = slice(0, 3)}},
        .visible = GraphSize{.w = 1200, .h = 1200}};

    g.addEdge(n(0, 0), e(1, 0));

    g.addEdge(n(0, 1), e(1, 1));
    g.addEdge(n(0, 1), e(1, 2));
    g.addEdge(n(0, 1), e(1, 3));

    g.addEdge(n(0, 2), e(1, 4));

    g.addEdge(n(1, 0), e(2, 0));
    g.addEdge(n(1, 1), e(2, 0));
    g.addEdge(n(1, 1), e(2, 1));

    g.addEdge(n(1, 2), e(2, 1));

    g.addEdge(n(1, 3), e(2, 1));
    g.addEdge(n(1, 3), e(2, 2));
    g.addEdge(n(1, 4), e(2, 1));
    g.addEdge(n(1, 4), e(2, 3));

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

int LaneBlockStack::getBlockHeightStart(int blockIdx) const {
    int start = scrollOffset;
    for (int i = 0; i < blockIdx; ++i) {
        start += blocks.at(i).fullHeight();
    }
    return start;
}

bool LaneBlockStack::inSpan(int blockIdx, Slice<int> heightRange) const {
    if (blocks.at(blockIdx).isVisible) {
        auto span = blocks.at(blockIdx).heightSpan(
            getBlockHeightStart(blockIdx));
        bool result = heightRange.overlap(span).has_value();
        // _dfmt(span, heightRange, blockIdx, result, scrollOffset);
        return result;
    } else {
        return false;
    }
}

Vec<int> LaneBlockStack::getVisibleBlocks(Slice<int> heightRange) const {
    Vec<int> res;
    for (int block : visibleRange) {
        if (inSpan(block, heightRange)) { res.push_back(block); }
    }

    std::sort(res.begin(), res.end());

    return res;
}

ImVec2 get_center(const GraphRect& rect) {
    return ImVec2(
        rect.left + rect.width / 2.0, rect.top + rect.height / 2.0);
}

ColaConstraintDebug to_constraints(
    const LaneBlockLayout&       lyt,
    const LaneBlockGraph&        g,
    GraphLayoutIR::Result const& final) {
    ColaConstraintDebug res;

    auto add_align_line = [&](GraphNodeConstraint::Align const& a) {
        bool        x = a.dimension == GraphDimension::XDIM;
        Vec<ImVec2> centers;
        for (auto const& rect : a.nodes) {
            centers.push_back(
                get_center(final.fixed.at(rect.node))
                - (x ? ImVec2(rect.offset, 0) : ImVec2(0, rect.offset)));
        }
        std::sort(
            centers.begin(),
            centers.end(),
            [&](ImVec2 const& lhs, ImVec2 const& rhs) {
                return x ? (lhs.y < rhs.y) : (lhs.x < rhs.x);
            });

        ImVec2 start = centers.at(0);
        ImVec2 end   = centers.at(1_B);

        res.constraints.push_back(ColaConstraintDebug::Constraint{
            ColaConstraintDebug::Constraint::Align{
                .start = start,
                .end   = end,
            }});
    };


    for (auto const& c : lyt.ir.nodeConstraints) {
        switch (c.getKind()) {
            case GraphNodeConstraint::Kind::Align: {
                add_align_line(c.getAlign());
                break;
            }
            case GraphNodeConstraint::Kind::Separate: {
                add_align_line(c.getSeparate().left);
                add_align_line(c.getSeparate().right);
                break;
            }
            default: {
                _dbg(c.getKind());
            }
        }
    }

    return res;
}

void render_debug(const ColaConstraintDebug& debug, ImVec2 const& shift) {
    ImDrawList* draw_list = ImGui::GetForegroundDrawList();
    using C               = ColaConstraintDebug::Constraint;

    auto color = IM_COL32(255, 0, 0, 255);

    auto point = [&](const GraphPoint& point) {
        draw_list->AddCircleFilled(
            ImVec2(point.x, point.y) + shift, 3.0f, color);
    };

    for (auto const& r : debug.ir->fixed) {
        draw_list->AddRect(
            ImVec2(r.left, r.top) + shift,
            ImVec2(r.left + r.width, r.top + r.height) + shift,
            color,
            0.0f,
            0,
            line_width);
    }

    for (auto const& c : debug.constraints) {
        switch (c.getKind()) {
            case C::Kind::Align: {
                auto const& a = c.getAlign();
                point(GraphPoint{a.start.x, a.start.y});
                point(GraphPoint{a.end.x, a.end.y});
                draw_list->AddLine(
                    ImVec2(a.start.x, a.start.y) + shift,
                    ImVec2(a.end.x, a.end.y) + shift,
                    color,
                    2.0f);
                break;
            }
        }
    }
}
