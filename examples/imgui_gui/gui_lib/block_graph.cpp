#include "block_graph.hpp"
#include <adaptagrams/adaptagrams_ir.hpp>
#include <hstd/stdlib/Enumerate.hpp>
#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/Ranges.hpp>
#include <hstd/stdlib/Debug.hpp>
#include "imgui_utils.hpp"
#include <hstd/ext/logger.hpp>

using namespace hstd;
using namespace hstd::ext;

using GC = GraphNodeConstraint;


namespace {
hstd::log::log_builder gr_log(
    hstd::log::severity_level __severity,
    int                       line     = __builtin_LINE(),
    char const*               function = __builtin_FUNCTION(),
    char const*               file     = __builtin_FILE()) {
    return std::move(::hstd::log::log_builder{}
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
    HSLOG_DEPTH_SCOPE_ANON();
    for (auto const& [lane_idx, lane] : enumerate(g.lanes)) {
        gr_log(hstd::log::l_trace)
            .fmt_message(
                "Lane index {} size {}, scroll is {}",
                lane_idx,
                lane.blocks.size(),
                lane.scrollOffset);

        HSLOG_DEPTH_SCOPE_ANON();

        int maxRow = lane.blocks.high();

        Opt<GC::Align::Spec> first;
        for (int row = 0; row <= maxRow; ++row) {
            LaneNodePos node{.lane = lane_idx, .row = row};
            GraphSize   size{
                  .w = static_cast<double>(lane.blocks.at(row).width),
                  .h = static_cast<double>(lane.blocks.at(row).height),
            };

            lyt.ir.rectangles.push_back(size);


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
        for (int row = 0; row <= maxRow; ++row) {
            LaneNodePos node{.lane = lane_idx, .row = row};
            align.nodes.push_back(spec(lyt.rectMap.at(node)));

            auto next_row = row + 1;
            if (next_row <= maxRow) {
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
    HSLOG_DEPTH_SCOPE_ANON();


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
    HSLOG_DEPTH_SCOPE_ANON();
    int                               edgeId = 0;
    UnorderedMap<Pair<int, int>, int> inLaneCheckpoints;
    for (auto const& lane : enumerator(g.lanes)) {
        for (auto const& [block_idx, block] :
             enumerate(lane.value().blocks)) {
            LaneNodePos source{
                .lane = lane.index(),
                .row  = block_idx,
            };
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
                        LOGIC_ASSERTION_CHECK_FMT(
                            offset <= full, "{} !<= {}", offset, full);
                        ec.targetOffset     = float(offset) / float(full);
                        ec.targetCheckpoint = base + step * inLaneEdge;
                    }

                    if (target.sourceOffset) {
                        auto full   = g.at(source).height;
                        auto offset = target.sourceOffset.value();
                        LOGIC_ASSERTION_CHECK_FMT(
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

int LaneBlockStack::getBlockHeightStart(int blockIdx) const {
    int start = scrollOffset;
    for (int i = 0; i < blockIdx; ++i) {
        start += blocks.at(i).fullHeight();
    }
    return start;
}

bool LaneBlockStack::inSpan(int blockIdx, Slice<int> heightRange) const {
    auto span = blocks.at(blockIdx).heightSpan(
        getBlockHeightStart(blockIdx));
    bool result = heightRange.overlap(span).has_value();
    // gr_log(hstd::log::l_debug).message(
    //     _dfmt_expr(span, heightRange, blockIdx, result,
    //     scrollOffset));
    return result;
}

Vec<int> LaneBlockStack::getVisibleBlocks(Slice<int> heightRange) const {
    Vec<int> res;
    if (!blocks.empty()) {
        for (int block : slice1(0, blocks.high())) {
            if (inSpan(block, heightRange)) { res.push_back(block); }
        }

        std::sort(res.begin(), res.end());
    }


    return res;
}

int LaneBlockStack::addBlock(
    int                         laneIndex,
    const ImVec2&               size,
    const LaneBlockGraphConfig& conf) {

    LOGIC_ASSERTION_CHECK_FMT(
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

ColaConstraintDebug LaneBlockLayout::getConstraintDebug() const {
    ColaConstraintDebug res;

    using D = ColaConstraintDebug;
    using C = ColaConstraintDebug::Constraint;

    auto get_rect_center = [&](int idx) {
        return get_center(layout.fixed.at(idx));
    };

    auto add_align_line = [&](GraphNodeConstraint::Align const& a) {
        bool           x = a.dimension == GraphDimension::XDIM;
        Vec<C::Point>  centers;
        Vec<C::Offset> offsets;
        for (auto const& rect : a.nodes) {
            ImVec2 center = get_rect_center(rect.node);
            ImVec2 offset = (x ? ImVec2(rect.offset, 0) : ImVec2(0, rect.offset));
            centers.push_back(C::Point{center - offset, {rect.node}});
            offsets.push_back(C::Offset{
                .offset = -offset,
                .start  = C::Point{center, {rect.node}},
            });
        }

        std::sort(
            centers.begin(),
            centers.end(),
            [&](C::Point const& lhs, C::Point const& rhs) {
                return x ? (lhs.pos.y < rhs.pos.y)
                         : (lhs.pos.x < rhs.pos.x);
            });

        C::Point start = centers.at(0);
        C::Point end   = centers.at(1_B);

        return C::Align{
            .start   = start,
            .end     = end,
            .offsets = offsets,
            .rects   = a.nodes
                   | rv::transform(get_field_get(
                       &GraphNodeConstraint::Align::Spec::node))
                   | rs::to<Vec>(),
        };
    };

    for (auto const& [rect_idx, rect] : enumerate(layout.fixed)) {
        res.constraints.push_back(C{C::RectPosition{
            .pos  = ImVec2(rect.left, rect.top),
            .rect = rect_idx,
        }});
    }


    for (auto const& c : ir.nodeConstraints) {
        switch (c.getKind()) {
            case GraphNodeConstraint::Kind::Align: {
                res.constraints.push_back(C{add_align_line(c.getAlign())});
                break;
            }
            case GraphNodeConstraint::Kind::Separate: {
                auto const& s     = c.getSeparate();
                auto        left  = add_align_line(s.left);
                auto        right = add_align_line(s.right);

                ImVec2 offset = //
                    s.dimension == GraphDimension::XDIM
                        ? ImVec2(right.start.pos.x - left.start.pos.x, 0)
                        : ImVec2(0, right.start.pos.y - left.start.pos.y);


                C::Offset offsetSpec{
                    .offset = offset,
                    .start  = left.start,
                };

                C::Separate sep{
                    .left   = left,
                    .right  = right,
                    .offset = offsetSpec,
                };

                res.constraints.push_back(C{sep});
                break;
            }
            default: {
                _dbg(c.getKind());
            }
        }
    }

    return res;
}

void render_debug(
    const ColaConstraintDebug&   debug,
    ImVec2 const&                shift,
    GraphLayoutIR::Result const& ir) {
    ImDrawList* dl = ImGui::GetForegroundDrawList();
    using C        = ColaConstraintDebug::Constraint;

    auto alignAxisColor      = IM_COL32(255, 0, 0, 255);
    auto rectCenterColor     = IM_COL32(255, 0, 0, 255);
    auto rectBoundaryColor   = IM_COL32(255, 0, 0, 255);
    auto alignOffsetColor    = IM_COL32(0, 255, 0, 255);
    auto separateOffsetColor = IM_COL32(211, 255, 0, 255);

    auto text = [&](ImVec2 const& pos, std::string const& t) {
        AddTextWithBackground(dl, pos, IM_COL32(0, 0, 0, 255), t);
    };

    auto point = [&](const C::Point& point) {
        dl->AddCircleFilled(point.pos + shift, 3.0f, rectCenterColor);
        if (!point.rectOrigin.empty()) {
            text(point.pos + shift, fmt("{}", point.rectOrigin));
        }
    };

    for (auto const& r : ir.fixed) {
        dl->AddRect(
            ImVec2(r.left, r.top) + shift,
            ImVec2(r.left + r.width, r.top + r.height) + shift,
            rectBoundaryColor,
            0.0f,
            0,
            line_width);
    }

    auto render_offset = [&](C::Offset const& offset, ImU32 color) {
        if (offset.isEmpty()) { return; }
        if (int(offset.offset.x) != 0) {
            text(
                offset.start.pos + shift + (offset.offset / 2),
                fmt("x{:.1f}", offset.offset.x));
        } else if (int(offset.offset.y) != 0) {
            text(
                offset.start.pos + shift + (offset.offset / 2),
                fmt("y{:.1f}", offset.offset.y));
        }

        dl->AddLine(
            offset.start.pos + shift,
            offset.start.pos + shift + offset.offset,
            color,
            2.0f);
    };

    auto render_align_line = [&](C::Align const& a) {
        point(a.start);
        point(a.end);
        dl->AddLine(
            a.start.pos + shift, a.end.pos + shift, alignAxisColor, 2.0f);
        for (auto const& offset : a.offsets) {
            render_offset(offset, alignOffsetColor);
        }
    };

    for (auto const& c : debug.constraints) {
        switch (c.getKind()) {
            case C::Kind::Align: {
                render_align_line(c.getAlign());
                break;
            }
            case C::Kind::Separate: {
                auto const& s = c.getSeparate();
                render_align_line(s.left);
                render_align_line(s.right);
                render_offset(s.offset, separateOffsetColor);
                break;
            }
            case C::Kind::RectPosition: {
                auto const& r = c.getRectPosition();
                text(r.pos, fmt("[{}] {}", r.rect, r.pos));
                break;
            }
        }
    }
}

void LaneBlockGraph::addScrolling(
    const ImVec2& graphPos,
    float         direction) {
    gr_log(hstd::log::l_trace)
        .fmt_message(
            "Graph position {}, direction {}", graphPos, direction);
    HSLOG_DEPTH_SCOPE_ANON();
    auto spans = getLaneSpans();
    for (auto const& [idx, span] : enumerate(spans)) {
        if (span.contains(graphPos.x)) {
            lanes.at(idx).scrollOffset += direction;
            gr_log(hstd::log::l_trace)
                .fmt_message(
                    "Lane {} x span is {}, adding scroll offset {}, "
                    "current "
                    "scroll is {}",
                    idx,
                    span,
                    direction,
                    lanes.at(idx).scrollOffset);
        } else {
            gr_log(hstd::log::l_trace)
                .fmt_message("Lane {} x span {}, no match", idx, span);
        }
    }
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

        gr_log(hstd::log::l_debug).fmt_message("{}", sl);
        laneSpans.resize_at(lane_idx) = sl;
        laneStartX += lane.getFullWidth();
    }
    return laneSpans;
}


LaneBlockLayout LaneBlockGraph::getLayout() const {
    LOGIC_ASSERTION_CHECK_FMT(
        int(visible.h) != 0 && int(visible.w) != 0, "{}", visible);
    gr_log(hstd::log::l_info)
        .fmt_message("Create block layout, {} lanes", lanes.size());

    {
        auto rec = gr_log(hstd::log::l_info).get_record();
        for (auto const& [idx, lane] : enumerate(lanes)) {
            rec.fmt_message(" [{}] scroll:{}", idx, lane.scrollOffset);
        }
        rec.end();
    }

    for (auto const& [idx, lane] : enumerate(lanes)) {
        LOGIC_ASSERTION_CHECK_FMT(
            !lane.blocks.empty(),
            "lane {} has 0 blocks, not supported for layout",
            idx);
    }

    HSLOG_DEPTH_SCOPE_ANON();

    for (auto const& [pos, block] : getBlocks()) {
        LOGIC_ASSERTION_CHECK_FMT(
            block.width != 0 && block.height != 0,
            "Cannot compute layout size with block size of 0. Block node "
            "at position {} has dimensions {}x{}",
            pos,
            block.height,
            block.width);

        // gr_log(hstd::log::l_info).fmt_message("Pos {} block {}", pos,
        // block);
    }


    LaneBlockLayout res;

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
    connect_vertical_constraints(res, laneAlignments, topLaneAlign, *this);

    res.ir.nodeConstraints.push_back(GraphNodeConstraint{GC::Align{
        .nodes     = topLaneAlign,
        .dimension = GraphDimension::YDIM,
    }});

    connect_inter_lane_constraints(res, laneAlignments, *this);

    connect_edges(res, *this);

    // All elements in the adaptagrams layout are placed in the positive
    // quadrant of the coordinates and without any gaps from the layout
    // canvas sides. So negative vertical offsets and left layout margin is
    // added after the fact.
    int leftPad = lanes.at(0).leftMargin;
    int topPad  = std::clamp<int>(
        rs::min(
            lanes
            | rv::transform(get_field_get(&LaneBlockStack::scrollOffset))),
        value_domain<int>::low(),
        0);

    res.ir.height = 10000;
    res.ir.width  = 10000;
    auto cola     = res.ir.doColaLayout();
    res.layout    = cola.convert();

    gr_log(hstd::log::l_info)
        .fmt_message("left-pad:{} top-pad:{}", leftPad, topPad);

    for (auto const& [key, edge] : res.layout.lines) {
        for (auto& path : res.layout.lines.at(key).paths) {
            for (auto& point : path.points) {
                point.y += topPad;
                point.x += leftPad;
            }
        }
    }

    for (auto& rect : res.layout.fixed) {
        rect.top += topPad;
        rect.left += leftPad;
    }

    return res;
}

Vec<LaneBlockLayout::RectSpec> LaneBlockLayout::getRectangles(
    LaneBlockGraph const& blockGraph) const {
    Vec<RectSpec> res;
    for (auto const& [blockId, lane_idx] : blockGraph.idToPos) {
        if (auto layout_index = rectMap.get(lane_idx)) {
            auto pos     = layout.fixed.at(layout_index.value()).topLeft();
            auto size    = layout.fixed.at(layout_index.value()).size();
            auto im_size = ImVec2(size.width(), size.height());
            auto im_pos  = ImVec2(pos.x, pos.y);
            // `getLayout()` adjusts vertical positions for the lanes to
            // account for differences in the adaptagram data model and
            // what the more constrained story grid expects. Because of
            // this adjustment some blocks can either be placed too high
            // relative to the visible viewport, or below it. They are
            // marked as invisible.
            res.push_back(RectSpec{
                .lanePos   = lane_idx,
                .blockId   = blockId,
                .size      = im_size,
                .pos       = im_pos,
                .isVisible = !(
                    (im_pos.y + im_size.y < 0)
                    || (blockGraph.visible.height() < im_pos.y)),
            });
        } else {
            res.push_back(RectSpec{
                .lanePos   = lane_idx,
                .blockId   = blockId,
                .isVisible = false,
            });
        }
    }
    return res;
}

void ColaConstraintDebug::toString(ColStream& os) const {
    using C = Constraint;

    auto write_2_point = [&](C::Point const& p1, C::Point const& p2) {
        if (int(p1.pos.x) == int(p2.pos.x)) {
            os << fmt("x:{} y:{}-{}", p1.pos.x, p1.pos.y, p2.pos.y);
        } else if (int(p1.pos.y) == int(p2.pos.y)) {
            os << fmt("x:{}-{} y:{}", p1.pos.x, p2.pos.x, p1.pos.y);
        } else {
            os << fmt(
                "x:{}-{} y:{}-{}", p1.pos.x, p2.pos.x, p1.pos.y, p2.pos.y);
        }

        if (p1.rectOrigin != p2.rectOrigin) {
            os << fmt(" <{}><{}>", p1.rectOrigin, p2.rectOrigin);
        } else {
            os << fmt(" <{}>", p1.rectOrigin);
        }
    };

    auto write_offset = [&](C::Offset const& o) {
        if (int(o.offset.x) == 0) {
            os << fmt("{}->+{}y", o.start.pos, o.offset.y);
        } else if (int(o.offset.y) == 0) {
            os << fmt("{}->+{}x", o.start.pos, o.offset.x);
        } else {
            os << fmt("{}->+{}", o.start.pos, o.offset);
        }
    };

    auto write_align = [&](C::Align const& a, int depth) {
        os.indent(depth * 2);
        os << fmt("Align {} ", a.rects);
        write_2_point(a.start, a.end);
        auto existing_offsets //
            = a.offsets
            | rv::filter(get_method_filter(&C::Offset::isEmpty))
            | rs::to<Vec>();

        if (existing_offsets.size() == 1) {
            os << " ";
            write_offset(existing_offsets.front());
        } else {
            for (auto const& o : existing_offsets) {
                os << "\n";
                os.indent(2 * (depth + 1));
                write_offset(o);
            }
        }
    };

    for (auto const& c : constraints) {
        if (c.isAlign()) {
            write_align(c.getAlign(), 0);
            os << "\n";
        } else if (c.isSeparate()) {
            auto const& s = c.getSeparate();
            os << "Sep ";
            write_offset(s.offset);
            os << "\n";
            write_align(s.left, 1);
            os << "\n";
            write_align(s.right, 1);
            os << "\n";
        }
    }
}
