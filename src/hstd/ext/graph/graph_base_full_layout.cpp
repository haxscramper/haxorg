#include "graph_base.hpp"

#include <hstd/stdlib/algorithms.hpp>
#include <hstd/ext/graph/graph_avoid.hpp>
#include <hstd/ext/graph/graph_vpsc.hpp>

using namespace hstd::ext::graph;

namespace {
void layout_run_full_layout(layout::LayoutRun* run) {
    auto __scope = run->scopeLevelMsg(
        hstd::fmt(
            "run full layout for the graph with root IDs {}",
            run->groups->getRootVertices()),
        "full-aux");

    auto aux = [&](this auto&& self, VertexID const& id) -> void {
        auto __scope = run->scopeLevelMsg(
            hstd::fmt("running layout for group ID {}", id));
        auto group = run->getGroup(id);
        for (auto const& sub :
             hstd::sorted(run->getSubGroups(id).items())) {
            self(sub);
        }

        for (auto const& sub :
             hstd::sorted(run->getSubGroups(id).items())) {
            if (run->getGroup(sub)->hasAlgorithm()) {
                LOGIC_ASSERTION_CHECK_FMT(
                    run->result.vertices.contains(sub),
                    "Sub-group '{}' has algorithm specified, but "
                    "recursive walk for layout did not assign the "
                    "bounding box to it. The `runSingleLayout` for a "
                    "group must create a bounding box for result.",
                    run->getGroup(sub)->getStableId());
            }
        }

        if (group->hasAlgorithm()) {
            auto sub_res = group->getAlgorithm()->runSingleLayout(id);

            LOGIC_ASSERTION_CHECK_FMT(
                sub_res.vertices.contains(id),
                "Running layout for {} ('{}') should set the bounding box "
                "for this group.",
                id,
                run->getGroup(id)->getStableId());

            // Use of `insert_or_assign` here is deliberate -- running
            // layout on the current group might overwrite the positioning
            // of the nested nodes or edges if necessary.
            for (auto const& [id, attr] : sub_res.vertices) {
                run->result.vertices.insert_or_assign(id, attr);
            }

            for (auto const& [id, attr] : sub_res.edges) {
                run->result.edges.insert_or_assign(id, attr);
            }
        }
    };

    for (auto const& root : run->groups->getRootVertices()) { aux(root); }
}

void layout_run_unbound_edge_placement(layout::LayoutRun* run) {
    auto __scope = run->scopeLevelMsg(
        "unbound edge placement", "unbound-edge");
    cst::VpscRectTracker                tracker;
    cst::AvoidRouterAlgorithm           router;
    layout::IPlacementAlgorithm::Result placement;
    router.rects                  = &tracker;
    router.intermediate_placement = &placement;
    router.run                    = run;

    for (auto const& vert : run->graph->getAllVertices()) {
        tracker.addVertex(vert, run->getAbsoluteBBox(vert));
        router.vertex_set.incl(vert);
    }

    for (auto const& edge : run->getAllUnboundEdges()) {
        router.edge_set.incl(edge);
    }

    router.routeEdges();
}

} // namespace

void layout::LayoutRun::runFullLayout() {
    layout_run_full_layout(this);
    layout_run_unbound_edge_placement(this);
}
