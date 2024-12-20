#pragma once

#include <GLFW/glfw3.h>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/wrappers/adaptagrams_wrap/adaptagrams_ir.hpp>
#include "imgui.h"
#include "imgui_internal.h"
#include <hstd/stdlib/Ranges.hpp>

struct LaneNodePos {
    int  lane;
    int  row;
    bool operator==(LaneNodePos const& other) const {
        return lane == other.lane && row == other.row;
    }

    std::string getImId() const { return fmt("{}_{}", row, lane); }

    DESC_FIELDS(LaneNodePos, (lane, row));
};

struct LaneNodeEdge {
    LaneNodePos               target;
    Opt<int>                  targetOffset;
    Opt<int>                  sourceOffset;
    GraphEdgeConstraint::Port targetPort = GraphEdgeConstraint::Port::East;
    GraphEdgeConstraint::Port sourcePort = GraphEdgeConstraint::Port::West;
    DESC_FIELDS(
        LaneNodeEdge,
        (target, targetOffset, sourceOffset, targetPort, sourcePort));
};

struct LaneBlockNode {
    int  width;
    int  height;
    int  topMargin    = 5;
    int  bottomMargin = 5;
    bool isVisible    = true;
    /// \brief Horizontal offset from the lane alignment center
    int horizontalCenterOffset = 0;
    /// \brief If block has fixed vertical offset it will be arranged
    /// relative to the top baseline alignment.
    Opt<int> fixedVerticalOffset = std::nullopt;

    /// \brief Get full vertical space occupied by the doc block, including
    /// top and bottom margins.
    int fullHeight() const { return height + topMargin + bottomMargin; }

    Slice<int> heightSpan(int start) const {
        return slice(start, start + fullHeight());
    }

    DESC_FIELDS(
        LaneBlockNode,
        (width,
         height,
         topMargin,
         bottomMargin,
         isVisible,
         horizontalCenterOffset));
};

struct LaneBlockGraphConfig {
    ImU32 edgeBorderColor      = IM_COL32(255, 255, 255, 200);
    ImU32 edgeCenterColor      = IM_COL32(128, 128, 128, 128);
    float edgeCurveWidth       = 4;
    float edgeCurveBorderWidth = 1;

    Func<Pair<int, int>(int lane)> getDefaultLaneMargin =
        [](int lane) -> Pair<int, int> { return {50, 50}; };

    Func<Pair<int, int>(LaneNodePos const& pos)> getDefaultBlockMargin =
        [](LaneNodePos const& pos) -> Pair<int, int> { return {5, 5}; };

    DESC_FIELDS(
        LaneBlockGraphConfig,
        (edgeBorderColor,
         edgeCenterColor,
         edgeCurveWidth,
         edgeCurveBorderWidth));
};


struct LaneBlockStack {
    Vec<LaneBlockNode> blocks;
    Slice<int>         visibleRange;
    int                scrollOffset = 0;
    int                leftMargin   = 50;
    int                rightMargin  = 50;
    DESC_FIELDS(
        LaneBlockStack,
        (blocks, visibleRange, scrollOffset, leftMargin, rightMargin));
    int  getBlockHeightStart(int blockIdx) const;
    void resetVisibleRange() { visibleRange = slice(0, blocks.high()); }
    bool inSpan(int blockIdx, Slice<int> heightRange) const;
    Vec<int> getVisibleBlocks(Slice<int> heightRange) const;
    int      addBlock(
             int                         laneIndex,
             ImVec2 const&               size,
             LaneBlockGraphConfig const& conf);

    int getWidth() const {
        return rs::max(blocks | rv::transform([](LaneBlockNode const& b) {
                           return float(b.width);
                       }));
    }

    int getFullWidth() const {
        return getWidth() + leftMargin + rightMargin;
    }
};

template <>
struct std::hash<LaneNodePos> {
    std::size_t operator()(LaneNodePos const& it) const noexcept {
        std::size_t result = 0;
        hax_hash_combine(result, it.lane);
        hax_hash_combine(result, it.row);
        return result;
    }
};


struct LaneBlockGraph {
    Vec<LaneBlockStack>                          lanes;
    UnorderedMap<LaneNodePos, Vec<LaneNodeEdge>> edges;
    GraphSize                                    visible;
    DESC_FIELDS(LaneBlockGraph, (lanes, visible, edges));
    LaneNodePos addNode(
        int                         lane,
        ImVec2 const&               size,
        LaneBlockGraphConfig const& conf) {
        return LaneNodePos{
            .lane = lane,
            .row  = this->lane(lane, conf).addBlock(lane, size, conf),
        };
    }

    void addEdge(LaneNodePos const& source, LaneNodeEdge const& target) {
        edges[source].push_back(target);
    }

    LaneBlockStack& lane(int lane, LaneBlockGraphConfig const& conf) {
        if (lanes.has(lane)) {
            return lanes.at(lane);
        } else {
            auto [left, right] = conf.getDefaultLaneMargin(lane);
            auto& l            = lanes.resize_at(lane);
            l.leftMargin       = left;
            l.rightMargin      = right;
            return l;
        }
    }

    LaneBlockNode& at(LaneNodePos const& node) {
        return lanes.at(node.lane).blocks.at(node.row);
    }

    LaneBlockNode const& at(LaneNodePos const& node) const {
        return lanes.at(node.lane).blocks.at(node.row);
    }

    LaneBlockNode const& getLaneNode(LaneNodePos const& pos) {
        return lanes.at(pos.lane).blocks.at(pos.row);
    }

    generator<Pair<LaneNodePos, LaneBlockNode>> getBlocks() const {
        for (int lane_idx = 0; lane_idx < lanes.size(); ++lane_idx) {
            for (int row_idx = 0;
                 row_idx < lanes.at(lane_idx).blocks.size();
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

    Vec<Slice<int>> getLaneSpans() const {
        Vec<Slice<int>> laneSpans;
        int             laneStartX = 0;
        for (auto const& [lane_idx, lane] : enumerate(lanes)) {
            laneSpans.resize_at(lane_idx) = slice(
                laneStartX + lane.leftMargin,
                laneStartX + lane.leftMargin + lane.getWidth());
            laneStartX += lane.getFullWidth();
        }
        return laneSpans;
    }
};


struct LaneBlockLayout {
    GraphLayoutIR                  ir;
    UnorderedMap<LaneNodePos, int> rectMap;
    DESC_FIELDS(LaneBlockLayout, (ir, rectMap));
};

struct ColaConstraintDebug {
    struct Constraint {
        struct Align {
            ImVec2 start;
            ImVec2 end;
            DESC_FIELDS(Align, (start, end));
        };

        SUB_VARIANTS(Kind, Data, data, getKind, Align);
        Data data;
        DESC_FIELDS(Constraint, (data));
    };

    GraphLayoutIR::Result const* ir;
    Vec<Constraint>              constraints;
    DESC_FIELDS(ColaConstraintDebug, (constraints));
};

ColaConstraintDebug to_constraints(
    LaneBlockLayout const&       lyt,
    LaneBlockGraph const&        g,
    const GraphLayoutIR::Result& final);

void render_point(const GraphPoint& point, ImVec2 const& shift);
void render_path(const GraphPath& path, ImVec2 const& shift);
void render_bezier_path(
    const GraphPath&            path,
    ImVec2 const&               shift,
    const LaneBlockGraphConfig& conf);
void render_rect(const GraphRect& rect, ImVec2 const& shift);
void render_edge(
    const GraphLayoutIR::Edge&  edge,
    ImVec2 const&               shift,
    bool                        bezier,
    LaneBlockGraphConfig const& style);
void render_result(
    GraphLayoutIR::Result const& res,
    ImVec2 const&                shift,
    const LaneBlockGraphConfig&  style);
void render_debug(ColaConstraintDebug const& debug, const ImVec2& shift);

LaneBlockLayout to_layout(LaneBlockGraph const& g);
void            run_block_graph_test(GLFWwindow* window);
