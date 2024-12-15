#include "block_graph.hpp"
#include <hstd/wrappers/adaptagrams_wrap/adaptagrams_ir.hpp>
#include <hstd/stdlib/Enumerate.hpp>
#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/Ranges.hpp>
#include <hstd/stdlib/Debug.hpp>
#include "imgui_utils.hpp"
#include <gui_lib/org_logger.hpp>


using GC = GraphNodeConstraint;


namespace {
org_logging::log_builder gr_log(
    org_logging::severity_level __severity,
    int                         line     = __builtin_LINE(),
    char const*                 function = __builtin_FUNCTION(),
    char const*                 file     = __builtin_FILE()) {
    return std::move(::org_logging::log_builder{}
                         .set_callsite(line, function, file)
                         .severity(__severity)
                         .source_scope({"gui", "logic", "block_graph"}));
}

GC::Align::Spec spec(int rect, int offset = 0) {
    return GC::Align::Spec{
        .node   = rect,
        .offset = static_cast<double>(offset),
    };
}

void connect_vertical_constraints(
    LaneBlockLayout&      lyt,
    Vec<GC::Align>&       laneAlignments,
    Vec<GC::Align::Spec>& topLaneAlign,
    LaneBlockGraph const& g) {
    OLOG_DEPTH_SCOPE_ANON();
    for (auto const& [lane_idx, lane] : enumerate(g.lanes)) {
        gr_log(ol_trace).fmt_message(
            "Lane index {} size {}, scroll is {}",
            lane_idx,
            lane.blocks.size(),
            lane.scrollOffset);

        auto     visibleSlice  = slice<int>(0, int(g.visible.height()));
        Vec<int> visibleBlocks = lane.getVisibleBlocks(visibleSlice);
        if (visibleBlocks.empty()) {
            gr_log(ol_trace).fmt_message(
                "No blocks in visible range {}", visibleSlice);
            continue;
        } else {
            gr_log(ol_trace).fmt_message(
                "Blocks {} are visible in range {}",
                visibleBlocks,
                visibleSlice);
        }

        Opt<GC::Align::Spec> first;
        for (int row : visibleBlocks) {
            LaneNodePos node{.lane = lane_idx, .row = row};
            GraphSize   size{
                  .w = static_cast<double>(lane.blocks.at(row).width),
                  .h = static_cast<double>(lane.blocks.at(row).height),
            };

            lyt.ir.rectangles.push_back(size);


            int idx = lyt.ir.rectangles.high();
            lyt.rectMap.insert_or_assign(node, idx);

            // gr_log(ol_trace).fmt_message(
            //     "Row {} rect {} size {}", row, idx, size);

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
}

void connect_inter_lane_constraints(
    LaneBlockLayout&      lyt,
    Vec<GC::Align>&       laneAlignments,
    LaneBlockGraph const& g) {
    OLOG_DEPTH_SCOPE_ANON();


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
}

void connect_edges(LaneBlockLayout& lyt, LaneBlockGraph const& g) {
    OLOG_DEPTH_SCOPE_ANON();
    int                               edgeId = 0;
    UnorderedMap<Pair<int, int>, int> inLaneCheckpoints;
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

                    int step = 12;
                    int base = 6;

                    auto pairing = std::make_pair(
                        source.lane, target.target.lane);
                    if (inLaneCheckpoints.contains(pairing)) {
                        ++inLaneCheckpoints.at(pairing);
                    } else {
                        inLaneCheckpoints.insert_or_assign(pairing, 0);
                    }

                    int inLaneEdge = inLaneCheckpoints.at(pairing);

                    if (target.targetOffset) {
                        auto full   = g.at(target.target).height;
                        auto offset = target.targetOffset.value();
                        LOGIC_ASSERTION_CHECK(
                            offset <= full, "{} !<= {}", offset, full);
                        ec.targetOffset     = float(offset) / float(full);
                        ec.targetCheckpoint = base + step * inLaneEdge;
                    }

                    if (target.sourceOffset) {
                        auto full   = g.at(source).height;
                        auto offset = target.sourceOffset.value();
                        LOGIC_ASSERTION_CHECK(
                            offset <= full, "{} !<= {}", offset, full);
                        ec.sourceOffset     = float(offset) / float(full);
                        ec.sourceCheckpoint = base + step * inLaneEdge;
                    }

                    lyt.ir.edgeConstraints.insert_or_assign(edge, ec);
                }
            }
        }
    }
}

} // namespace


LaneBlockLayout to_layout(LaneBlockGraph const& g) {
    LOGIC_ASSERTION_CHECK(
        int(g.visible.h) != 0 && int(g.visible.w) != 0, "{}", g.visible);
    gr_log(ol_info).fmt_message(
        "Create block layout, {} lanes", g.lanes.size());

    {
        auto rec = gr_log(ol_info).get_record();
        for (auto const& [idx, lane] : enumerate(g.lanes)) {
            rec.fmt_message(" [{}] scroll:{}", idx, lane.scrollOffset);
        }
        rec.end();
    }

    OLOG_DEPTH_SCOPE_ANON();

    for (auto const& [pos, block] : g.getBlocks()) {
        LOGIC_ASSERTION_CHECK(
            block.width != 0 && block.height != 0,
            "Cannot compute layout size with block size of 0. Block node "
            "at position {} has dimensions {}x{}",
            pos,
            block.height,
            block.width);

        // gr_log(ol_info).fmt_message("Pos {} block {}", pos, block);
    }


    LaneBlockLayout lyt;

    Vec<GC::Align>       laneAlignments;
    Vec<GC::Align::Spec> topLaneAlign;

    // Compose lane alignment axis by constraining nodes pairwise. The
    // `first` node in the lane is also constrainted with the top
    // horizontal axis (top lane align), and then every other block on
    // the lane is transitively constrained to it.
    //
    // ──────────── topLaneAlign
    // align   align
    //   ┌─┐   ┌╶┐
    //   └┼┘   └│┘
    //    │     │
    //   ┌┼┐   ┌│┐
    //   └┼┘   └│┘
    //    │     │
    //   ┌┼┐   ┌│┐
    //   └─┘   └╶┘
    connect_vertical_constraints(lyt, laneAlignments, topLaneAlign, g);

    lyt.ir.nodeConstraints.push_back(GraphNodeConstraint{GC::Align{
        .nodes     = topLaneAlign,
        .dimension = GraphDimension::YDIM,
    }});

    connect_inter_lane_constraints(lyt, laneAlignments, g);

    connect_edges(lyt, g);
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


void render_bezier_path(
    const GraphPath&            path,
    ImVec2 const&               shift,
    LaneBlockGraphConfig const& conf) {
    if (path.points.size() < 2) { return; }

    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    std::vector<ImVec2> base_points;
    base_points.reserve(path.points.size());
    for (const auto& p : path.points) {
        base_points.push_back(ImVec2(p.x, p.y));
    }

    auto draw_offset_curve =
        [&](float y_offset, ImU32 color, float thickness) {
            std::vector<ImVec2> offset_points = base_points;
            for (auto& p : offset_points) {
                p.y += y_offset;
                p += shift;
            }

            if (offset_points.size() == 4) {
                float  dist = (offset_points[0].x - offset_points[3].x);
                ImVec2 bezier_start_offset = ImVec2(-dist, 0);
                ImVec2 bezier_end_offset   = ImVec2(dist, 0);

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

    draw_offset_curve(
        -conf.edgeCurveWidth + conf.edgeCurveBorderWidth,
        conf.edgeBorderColor,
        conf.edgeCurveBorderWidth);
    draw_offset_curve(0, conf.edgeCenterColor, conf.edgeCurveWidth - 2.0f);
    draw_offset_curve(
        +conf.edgeCurveWidth - conf.edgeCurveBorderWidth,
        conf.edgeBorderColor,
        conf.edgeCurveBorderWidth);
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
    const GraphLayoutIR::Edge&  edge,
    ImVec2 const&               shift,
    bool                        bezier,
    const LaneBlockGraphConfig& style) {
    for (const auto& path : edge.paths) {
        if (bezier) {
            render_bezier_path(path, shift, style);
        } else {
            render_path(path, shift);
        }
    }
    if (edge.labelRect.has_value()) {
        render_rect(edge.labelRect.value(), shift);
    }
}

void render_result(
    GraphLayoutIR::Result const& res,
    ImVec2 const&                shift,
    LaneBlockGraphConfig const&  style) {
    for (auto const& rect : res.fixed) { render_rect(rect, shift); }
    for (auto const& [key, path] : res.lines) {
        render_edge(path, shift, true, style);
    }
}

void graph_render_loop(
    LaneBlockGraph const&       g,
    GLFWwindow*                 window,
    LaneBlockGraphConfig const& style) {
    auto lyt  = to_layout(g);
    auto col  = lyt.ir.doColaLayout();
    auto conv = col.convert();

    ImVec2 shift{20, 20};

    while (!glfwWindowShouldClose(window)) {
        frame_start();
        fullscreen_window_begin();
        render_result(conv, shift, style);
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

    graph_render_loop(g, window, LaneBlockGraphConfig{});
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
        gr_log(ol_debug).message(
            _dfmt_expr(span, heightRange, blockIdx, result, scrollOffset));
        return result;
    } else {
        gr_log(ol_debug).message(_dfmt_expr(blockIdx, heightRange));
        return false;
    }
}

Vec<int> LaneBlockStack::getVisibleBlocks(Slice<int> heightRange) const {
    Vec<int> res;
    for (int block : slice1(0, blocks.high())) {
        if (inSpan(block, heightRange)) { res.push_back(block); }
    }

    std::sort(res.begin(), res.end());

    return res;
}

int LaneBlockStack::addBlock(
    int                         laneIndex,
    const ImVec2&               size,
    const LaneBlockGraphConfig& conf) {

    LOGIC_ASSERTION_CHECK(
        size.x != 0 && size.y != 0, "Cannot create block with no size");

    auto [top, bottom] = conf.getDefaultBlockMargin(LaneNodePos{
        .lane = laneIndex,
        .row  = blocks.size(),
    });

    blocks.push_back(LaneBlockNode{
        .width        = static_cast<int>(size.x),
        .height       = static_cast<int>(size.y),
        .topMargin    = top,
        .bottomMargin = bottom,
    });

    return blocks.high();
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

void LaneBlockGraph::addScrolling(
    const ImVec2& graphPos,
    float         direction) {
    gr_log(ol_trace).fmt_message(
        "Graph position {}, direction {}", graphPos, direction);
    OLOG_DEPTH_SCOPE_ANON();
    auto spans = getLaneSpans();
    for (auto const& [idx, span] : enumerate(spans)) {
        if (span.contains(graphPos.x)) {
            lanes.at(idx).scrollOffset += direction;
            gr_log(ol_trace).fmt_message(
                "Lane {} x span is {}, adding scroll offset {}, current "
                "scroll is {}",
                idx,
                span,
                direction,
                lanes.at(idx).scrollOffset);
        } else {
            gr_log(ol_trace).fmt_message(
                "Lane {} x span {}, no match", idx, span);
        }
    }
}

void LaneBlockGraph::resetVisibility() {
    for (auto& lane : lanes) {
        for (auto& rect : lane.blocks) { rect.isVisible = true; }
    }

    for (auto& stack : lanes) { stack.resetVisibleRange(); }
}

generator<Pair<LaneNodePos, LaneBlockNode>> LaneBlockGraph::getBlocks()
    const {
    for (int lane_idx = 0; lane_idx < lanes.size(); ++lane_idx) {
        for (int row_idx = 0; row_idx < lanes.at(lane_idx).blocks.size();
             ++row_idx) {
            co_yield std::make_pair(
                LaneNodePos{
                    .lane = lane_idx,
                    .row  = row_idx,
                },
                lanes.at(lane_idx).blocks.at(row_idx));
        }
    }
}

Vec<Slice<int>> LaneBlockGraph::getLaneSpans() const {
    Vec<Slice<int>> laneSpans;
    int             laneStartX = 0;
    for (auto const& [lane_idx, lane] : enumerate(lanes)) {
        Slice<int> sl = slice1<int>(
            laneStartX + lane.leftMargin,
            laneStartX + lane.leftMargin + lane.getWidth());

        gr_log(ol_debug).fmt_message("{}", sl);
        laneSpans.resize_at(lane_idx) = sl;
        laneStartX += lane.getFullWidth();
    }
    return laneSpans;
}
