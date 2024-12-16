#pragma once

#include <gui_lib/block_graph.hpp>

struct NodeGridGraph {
    /// \brief Lane block graph structure with the block positions and
    /// other data.
    LaneBlockGraph ir;
    /// \brief Map external node index to the lane node position. Changed
    /// in `add` method.
    UnorderedMap<int, LaneNodePos> gridNodeToNode;
    /// \brief Reverse map to get external node index based on the lane
    /// node position. Updated in the `add` method.
    UnorderedMap<LaneNodePos, int> nodeToGridNode;
    /// \brief Intermediate storage for the adaptagrapms graph layout IR.
    /// Updated in the `syncLayout` method, together with the `layout`
    /// field.
    LaneBlockLayout       lyt;
    GraphLayoutIR::Result layout;

    DESC_FIELDS(
        NodeGridGraph,
        (ir, gridNodeToNode, nodeToGridNode, lyt, layout));

    void setVisible(ImVec2 const& viewport) {
        ir.visible.h = viewport.y;
        ir.visible.w = viewport.x;
    }

    int& at(LaneNodePos const& pos) { return nodeToGridNode.at(pos); }
    LaneNodePos& at(int const& pos) { return gridNodeToNode.at(pos); }

    LaneBlockNode& getNode(int pos) { return ir.at(at(pos)); }

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

    /// \brief Update visibility status on all rectangles. Callback can
    /// return true/false or nullopt. In the latter case visibility of the
    /// rectangle will remain unchanged.
    void syncVisibility(Func<Opt<bool>(int)> const& cb) {
        for (auto const& [flat_idx, lane_idx] : gridNodeToNode) {
            auto visibility = cb(flat_idx);
            if (visibility.has_value()) {
                ir.at(lane_idx).isVisible = visibility.value();
            }
        }
    }

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

    void syncLayout();

    struct RectSpec {
        /// \brief Block lane graph position of the rectangle
        LaneNodePos lanePos;
        /// \brief Flat index of the original external block (note: this is
        /// not directly related to the `layout.fixed` and similar fields,
        /// but `lyt.rectMap` still can be used to get the original index
        /// through `lanePos`)
        int flatPos;
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
        DESC_FIELDS(RectSpec, (lanePos, flatPos, size, pos, isVisible));
    };

    /// \brief Get information on all previously provided rectangles.
    ///
    /// \warning If any changes were made to the rectangle list it is
    /// necessary to run `syncLayout` again to update the layout data.
    Vec<RectSpec> getRectangles();
};
