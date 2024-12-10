#pragma once

#include <gui_lib/block_graph.hpp>

struct NodeGridGraph {
    LaneBlockGraph                 ir;
    UnorderedMap<int, LaneNodePos> gridNodeToNode;
    UnorderedMap<LaneNodePos, int> nodeToGridNode;
    LaneBlockLayout                lyt;
    GraphLayoutIR::Result          layout;

    void setVisible(ImVec2 const& viewport) {
        ir.visible.h = viewport.y;
        ir.visible.w = viewport.x;
    }

    int& at(LaneNodePos const& pos) { return nodeToGridNode.at(pos); }
    LaneNodePos& at(int const& pos) { return gridNodeToNode.at(pos); }

    Vec<LaneBlockStack>& getLanes() { return ir.lanes; }

    void syncSize(Func<Opt<ImVec2>(int)> const& getSizeForFlat) {
        for (auto const& [flat_idx, lane_idx] : gridNodeToNode) {
            auto size = getSizeForFlat(flat_idx);
            if (size) {
                ir.at(lane_idx).width  = size->x;
                ir.at(lane_idx).height = size->y;
            }
        }
    }

    void syncPosition(Func<void(ImVec2, int)> const& setPosAtIndex) {}

    Opt<int> getFlat(LaneNodePos const& pos) const {
        return nodeToGridNode.get(pos);
    }

    Opt<LaneNodePos> getGrid(int node) const {
        return gridNodeToNode.get(node);
    }

    void add(int flatIdx, LaneNodePos const& irNode) {
        gridNodeToNode.insert_or_assign(flatIdx, irNode);
        nodeToGridNode.insert_or_assign(irNode, flatIdx);
    }

    void syncLayout() {
        int pad       = ir.lanes.at(0).leftMargin;
        lyt           = to_layout(ir);
        lyt.ir.height = 10000;
        lyt.ir.width  = 10000;
        auto cola     = lyt.ir.doColaLayout();
        layout        = cola.convert();

        for (auto const& [key, edge] : layout.lines) {
            for (auto& path : layout.lines.at(key).paths) {
                for (auto& point : path.points) { point.x += pad; }
            }
        }

        for (auto& rect : layout.fixed) { rect.left += pad; }
    }

    struct RectSpec {
        LaneNodePos lanePos;
        int         flatPos;
        ImVec2      size;
        ImVec2      pos;
        bool        isVisible = true;
        DESC_FIELDS(RectSpec, (lanePos, flatPos, size, pos, isVisible));
    };

    generator<RectSpec> getRectangles() {
        for (auto const& [flat_idx, lane_idx] : gridNodeToNode) {
            if (lyt.rectMap.contains(lane_idx)) {
                auto pos  = layout.fixed.at(flat_idx).topLeft();
                auto size = layout.fixed.at(flat_idx).size();
                co_yield RectSpec{
                    .lanePos   = lane_idx,
                    .flatPos   = flat_idx,
                    .size      = ImVec2(size.width(), size.height()),
                    .pos       = ImVec2(pos.x, pos.y),
                    .isVisible = true,
                };
            } else {
                co_yield RectSpec{
                    .lanePos   = lane_idx,
                    .flatPos   = flat_idx,
                    .isVisible = false,
                };
            }
        }
    }
};
