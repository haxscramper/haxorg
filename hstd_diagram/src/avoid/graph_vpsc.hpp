#pragma once

#if ORG_BUILD_WITH_ADAPTAGRAMS
#    include <hstd/ext/bimap_wrap.hpp>
#    include <hstd/ext/graph/base/graph_base.hpp>
#    include <hstd/ext/graph/visual/adaptagrams_common.hpp>
#    include <hstd/ext/graph/visual/graph_visual.hpp>
#    include <hstd/ext/logger.hpp>
#    include <hstd/stdlib/algorithms.hpp>
#    include <libdialect/hola.h>

namespace hstd::ext::graph::cst {

class VpscRectTracker {
  public:
    hstd::ext::Unordered1to1Bimap<VertexID, int> rectMap;
    hstd::Vec<hstd::SPtr<vpsc::Rectangle>>       rectStore;
    DESC_FIELDS(VpscRectTracker, (rectMap, rectStore));

    int getVertexIdx(VertexID const& id) const { return rectMap.at_right(id); }

    std::pair<int, int> getEdgeIdx(EdgeID const& id, hstd::SPtr<layout::LayoutRun> run)
        const {
        return {
            getVertexIdx(run->getGraph()->getSource(id)),
            getVertexIdx(run->getGraph()->getTarget(id)),
        };
    }

    int addVertex(VertexID const& id, geometry::Rect const& rect) {
        int result = rectStore.size();
        rectStore.push_back(
            std::make_shared<vpsc::Rectangle>(
                rect.min_x(), rect.max_x(), rect.min_y(), rect.max_y()));

        HSLOG_DEBUG("Adding vertex {} rect {}", id, rect);
        rectMap.add_unique(id, result);
        return result;
    }

    bool hasRect(VertexID const& id) const { return rectMap.contains_left(id); }

    hstd::SPtr<vpsc::Rectangle> getRect(VertexID const& id) const {
        LOGIC_ASSERTION_CHECK_FMT(
            rectMap.contains_left(id), "rect map is missing ID {}", id);

        return rectStore.at(rectMap.at_right(id));
    }

    VertexIDVec getAllVertexIDsSorted() const {
        VertexIDVec res;
        for (auto const& [rect, _] : enumerate(rectStore)) {
            res.push_back(rectMap.at_left(rect));
        }
        return res;
    }


    /// \brief Get all rectangles for the problem in a consistent
    /// sorting order.
    ///
    /// \warning This method will sort the vertices based on their IDs.
    /// This function should onyl be called after all the vertex
    /// elements are inserted **in the layout problem** the list of
    /// vertex rectangles is shared globally across all cola groups on
    /// the same layer.
    std::vector<vpsc::Rectangle*> getAllRectanglesSorted() const {
        std::vector<vpsc::Rectangle*> res;
        for (auto const& rect : rectStore) { res.push_back(rect.get()); }
        return res;
    }

    /// \brief Get all shape IDs in the problem. Sorting order matches
    /// \ref getAllRectanglesSorted
    std::vector<unsigned> getAllShapeIdsSorted() const {
        std::vector<unsigned> res;
        for (int i = 0; i < rectStore.size(); ++i) { res.push_back(i); }
        return res;
    }
};

} // namespace hstd::ext::graph::cst
#endif
