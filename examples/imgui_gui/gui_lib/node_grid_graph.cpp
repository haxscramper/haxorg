#include "node_grid_graph.hpp"

void NodeGridGraph::syncLayout() {
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

Vec<NodeGridGraph::RectSpec> NodeGridGraph::getRectangles() {
    Vec<RectSpec> res;
    for (auto const& [flat_idx, lane_idx] : gridNodeToNode) {
        if (auto layout_index = lyt.rectMap.get(lane_idx)) {
            auto pos  = layout.fixed.at(layout_index.value()).topLeft();
            auto size = layout.fixed.at(layout_index.value()).size();
            res.push_back(RectSpec{
                .lanePos   = lane_idx,
                .flatPos   = flat_idx,
                .size      = ImVec2(size.width(), size.height()),
                .pos       = ImVec2(pos.x, pos.y),
                .isVisible = true,
            });
        } else {
            res.push_back(RectSpec{
                .lanePos   = lane_idx,
                .flatPos   = flat_idx,
                .isVisible = false,
            });
        }
    }
    return res;
}
