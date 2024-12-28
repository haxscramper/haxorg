#pragma once

#include <GLFW/glfw3.h>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/wrappers/adaptagrams_wrap/adaptagrams_ir.hpp>
#include "imgui.h"
#include "imgui_internal.h"
#include <hstd/stdlib/Ranges.hpp>
#include <hstd/stdlib/dod_base.hpp>

struct LaneNodePos {
    int  lane;
    int  row;
    bool operator==(LaneNodePos const& other) const {
        return lane == other.lane && row == other.row;
    }

    std::string getImId() const { return fmt("{}_{}", row, lane); }

    DESC_FIELDS(LaneNodePos, (lane, row));
};

template <>
struct std::formatter<LaneNodePos> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const LaneNodePos& p, FormatContext& ctx) const {
        fmt_ctx("[", ctx);
        fmt_ctx(p.lane, ctx);
        fmt_ctx("@", ctx);
        fmt_ctx(p.row, ctx);
        return fmt_ctx("]", ctx);
    }
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
    int width        = 0;
    int height       = 0;
    int topMargin    = 5;
    int bottomMargin = 5;
    /// \brief Horizontal offset from the lane alignment center
    int horizontalCenterOffset = 0;
    /// \brief If block has fixed vertical offset it will be arranged
    /// relative to the top baseline alignment.
    Opt<int> fixedVerticalOffset = std::nullopt;

    /// \brief Get full vertical space occupied by the doc block, including
    /// top and bottom margins.
    int fullHeight() const { return height + topMargin + bottomMargin; }

    int getWidth() const {
        LOGIC_ASSERTION_CHECK(
            width != 0, "Depleted block, has width 0, block is invalid.");
        return width;
    }

    Slice<int> heightSpan(int start) const {
        return slice(start, start + fullHeight());
    }

    DESC_FIELDS(
        LaneBlockNode,
        (width, height, topMargin, bottomMargin, horizontalCenterOffset));
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
    int                scrollOffset = 0;
    int                leftMargin   = 50;
    int                rightMargin  = 50;
    DESC_FIELDS(
        LaneBlockStack,
        (blocks, scrollOffset, leftMargin, rightMargin));
    int      getBlockHeightStart(int blockIdx) const;
    bool     inSpan(int blockIdx, Slice<int> heightRange) const;
    Vec<int> getVisibleBlocks(Slice<int> heightRange) const;
    int      addBlock(
             int                         laneIndex,
             ImVec2 const&               size,
             LaneBlockGraphConfig const& conf);

    int getWidth() const {
        return rs::max(
            blocks | rv::transform([](LaneBlockNode const& b) -> int {
                return b.getWidth();
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

// block node ID does not have an associated value and is used as a
// strongly typed integer.
DECL_ID_TYPE(___BlockNode, BlockNodeId, std::size_t);

struct ColaConstraintDebug {
    struct Constraint {
        struct Point {
            ImVec2   pos;
            Vec<int> rectOrigin;
            DESC_FIELDS(Point, (pos, rectOrigin));
        };

        struct Offset {
            ImVec2 offset;
            Point  start;
            bool   isEmpty() const {
                return int(offset.x) == 0 && int(offset.y) == 0;
            }
            DESC_FIELDS(Offset, (offset, start));
        };

        struct RectPosition {
            ImVec2 pos;
            int    rect;
            DESC_FIELDS(RectPosition, (pos, rect));
        };

        struct Align {
            Point       start;
            Point       end;
            Vec<Offset> offsets;
            Vec<int>    rects;
            DESC_FIELDS(Align, (start, end, offsets, rects));
        };

        struct Separate {
            Align  left;
            Align  right;
            Offset offset;
            DESC_FIELDS(Separate, (left, right, offset));
        };

        SUB_VARIANTS(
            Kind,
            Data,
            data,
            getKind,
            Align,
            Separate,
            RectPosition);
        Data data;
        DESC_FIELDS(Constraint, (data));
    };

    void    toString(ColStream& os) const;
    ColText toString() const {
        ColStream os;
        toString(os);
        return os.getBuffer();
    }

    Vec<Constraint> constraints;
    DESC_FIELDS(ColaConstraintDebug, (constraints));
};


struct LaneBlockGraph;
struct LaneBlockLayout {
    /// \brief Finalized set of graph layout constraints, ready to be
    /// solved for final layout.
    GraphLayoutIR ir;
    /// \brief Store mapping between the block graph nodes and the final
    /// fixed layout rectangles. Adaptagrams IR will only have nodes that
    /// are actually laid out, so this will create a full new set of
    /// indices that are specific to the final
    /// `GraphLayoutIR::Result::fixed` field (final data for fully
    /// positioned nodes) or `GraphLayoutIR::rectangles` field
    /// (intermediate data for not-yet-positioned rectangle sizes)
    UnorderedMap<LaneNodePos, int> rectMap;

    /// \brief Intermediate storage for the adaptagrapms graph layout IR.
    /// Updated in the `syncLayout` method, together with the `layout`
    /// field.
    GraphLayoutIR::Result layout;

    DESC_FIELDS(LaneBlockLayout, (ir, rectMap));

    struct RectSpec {
        /// \brief Block lane graph position of the rectangle
        LaneNodePos lanePos;
        /// \brief Flat index of the original external block (note: this is
        /// not directly related to the `layout.fixed` and similar fields,
        /// but `lyt.rectMap` still can be used to get the original index
        /// through `lanePos`)
        BlockNodeId blockId;
        /// \brief Size of the layout rectangle. If rectangle is invisible
        /// the data is not filled.
        ImVec2 size;
        /// \brief Position of the upper left corner of the rectangle. If
        /// rectangle is invisible the data is not filled.
        ImVec2 pos;
        /// \brief If the rectangle was not added to the `lyt` it is marked
        /// as invisible. Rectangle might be missing from the `lyt` if (1)
        /// `syncLayout` did not run yet, (2) the rectangle is out of the
        /// scroll window and was cut off from layout.
        bool isVisible = true;
        DESC_FIELDS(RectSpec, (lanePos, blockId, size, pos, isVisible));
    };

    /// \brief Get information on all previously provided rectangles.
    ///
    /// \warning If any changes were made to the rectangle list it is
    /// necessary to run `syncLayout` again to update the layout data.
    Vec<RectSpec> getRectangles(LaneBlockGraph const& blockGraph) const;
    ColaConstraintDebug getConstraintDebug() const;
};


struct LaneBlockGraph {
    Vec<LaneBlockStack>                          lanes;
    UnorderedMap<LaneNodePos, Vec<LaneNodeEdge>> edges;
    GraphSize                                    visible;
    /// \brief Map external node index to the lane node position. Changed
    /// in `add` method.
    UnorderedMap<BlockNodeId, LaneNodePos> idToPos;
    /// \brief Reverse map to get external node index based on the lane
    /// node position. Updated in the `add` method.
    UnorderedMap<LaneNodePos, BlockNodeId> posToId;

    DESC_FIELDS(LaneBlockGraph, (lanes, visible, edges, idToPos, posToId));

    void setVisible(ImVec2 const& viewport) {
        visible.h = viewport.y;
        visible.w = viewport.x;
    }


    void syncSize(Func<Opt<ImVec2>(BlockNodeId)> const& getSizeForFlat) {
        for (auto const& [flat_idx, lane_idx] : idToPos) {
            auto size = getSizeForFlat(flat_idx);
            if (size) {
                at(lane_idx).width  = size->x;
                at(lane_idx).height = size->y;
            }
        }
    }

    Opt<BlockNodeId> getBlockId(LaneNodePos const& pos) const {
        return posToId.get(pos);
    }

    Opt<LaneNodePos> getBlockPos(BlockNodeId node) const {
        return idToPos.get(node);
    }

    void add(BlockNodeId blockId, LaneNodePos const& blockPos) {
        idToPos.insert_or_assign(blockId, blockPos);
        posToId.insert_or_assign(blockPos, blockId);
    }

    LaneNodePos addNode(
        int                         lane,
        BlockNodeId                 id,
        ImVec2 const&               size,
        LaneBlockGraphConfig const& conf) {
        auto res = LaneNodePos{
            .lane = lane,
            .row  = this->lane(lane, conf).addBlock(lane, size, conf),
        };

        add(id, res);
        return res;
    }

    void addScrolling(ImVec2 const& graphPos, float direction);

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

    LaneBlockStack const& getExistingLane(int lane) const {
        return lanes.at(lane);
    }

    LaneBlockNode& at(BlockNodeId const& id) {
        return at(getBlockPos(id).value());
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

    generator<Pair<LaneNodePos, LaneBlockNode>> getBlocks() const;

    Vec<Slice<int>> getLaneSpans() const;

    /// \brief Convert lane block graph into adaptagrams block layout IR.
    /// This function does not perform any node positioning, only creates a
    /// set of constraints for later layout.
    LaneBlockLayout getLayout() const;
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
void render_debug(
    ColaConstraintDebug const&   debug,
    const ImVec2&                shift,
    const GraphLayoutIR::Result& ir);
