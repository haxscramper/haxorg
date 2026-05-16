#include "graph_base.hpp"

#include <hstd/stdlib/algorithms.hpp>
#include <hstd/ext/graph/graph_avoid.hpp>
#include <hstd/ext/graph/graph_vpsc.hpp>
#include <hstd/ext/geometry/hstd_geometry.hpp>

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
            hstd::fmt(
                "running layout for group ID {}", run->getDebug(id)));
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

            run->message(
                hstd::fmt(
                    "sub res ports: {} overall ports {}",
                    run->getDebug(sub_res.ports.keys()),
                    run->getDebug(run->getDirectPorts(id))));

            LOGIC_ASSERTION_CHECK_FMT(
                sub_res.vertices.contains(id),
                "Running layout for {} should set the bounding box "
                "for this group.",
                run->getDebug(id));

            auto missing_vertex_layout = run->getDirectVertices(id)
                                       - VertexIDSet::FromVec(
                                             sub_res.vertices.keys());
            run->message(
                hstd::fmt(
                    "generated layout for {}",
                    run->getDebug(sub_res.vertices.keys())));

            LOGIC_ASSERTION_CHECK_FMT(
                missing_vertex_layout.empty(),
                "Running layout for {} should provide the vertex "
                "layout for {}",
                run->getDebug(id),
                run->getDebug(missing_vertex_layout));

            auto missing_port_layout = run->getDirectPorts(id)
                                     - PortIDSet::FromVec(
                                           sub_res.ports.keys());
            LOGIC_ASSERTION_CHECK_FMT(
                missing_port_layout.empty(),
                "Running layout for {} should provide the port "
                "layout for {}",
                run->getDebug(id),
                run->getDebug(missing_port_layout));

            // Use of `insert_or_assign` here is deliberate -- running
            // layout on the current group might overwrite the positioning
            // of the nested nodes or edges if necessary.
            for (auto const& [id, attr] : sub_res.vertices) {
                run->result.vertices.insert_or_assign(id, attr);
            }

            for (auto const& [id, attr] : sub_res.edges) {
                // All edges must be present in the layout run, if this
                // conflicts with internal logic for some of the layout
                // algorithms, the filtering must be done on the
                // `runSingleLayout` side.
                LOGIC_ASSERTION_CHECK_FMT(
                    run->edges->hasEdge(id)
                        && run->edges->isTrackingEdge(id),
                    "Layout run returned layout information for edge not "
                    "included in the overall layout run collection: {}",
                    run->getDebug(id));

                run->result.edges.insert_or_assign(id, attr);
            }

            for (auto const& [id, attr] : sub_res.ports) {
                run->result.ports.insert_or_assign(id, attr);
            }
        }
    };

    for (auto const& root : run->groups->getRootVertices()) { aux(root); }

    VertexIDSet all_layout_vertices = VertexIDSet::FromVec(
        run->result.vertices.keys());

    VertexIDSet hierarchy_vertices         = run->groups->getAllVertices();
    VertexIDSet missing_hierarchy_vertices = hierarchy_vertices
                                           - all_layout_vertices;
    LOGIC_ASSERTION_CHECK_FMT(
        missing_hierarchy_vertices.empty(),
        "Full layout run did not provide layout attributes for all "
        "vertices included in hierarchies. Layout information is missing "
        "for {}",
        run->getDebug(missing_hierarchy_vertices));

    // VertexIDSet graph_vertices         =
    // run->getGraph()->getAllVertices(); VertexIDSet
    // missing_graph_vertices = graph_vertices
    //                                    - all_layout_vertices;

    // LOGIC_ASSERTION_CHECK_FMT(
    //     missing_graph_vertices.empty(),
    //     "Full layout run did not provide layout attributes for all "
    //     "vertices included in graph. Layout information is missing "
    //     "for {}",
    //     run->getDebug(missing_graph_vertices));
}

void run_placement_with_subset(
    layout::LayoutRun* run,
    EdgeIDSet const&   edge_set,
    VertexIDSet const& vertex_set,
    hstd::Str          placement_run_name) {
    // cst::VpscRectTracker                tracker;
    cst::AvoidRouterAlgorithm router;
    router.routing_run_name = placement_run_name;
    layout::IPlacementAlgorithm::Result placement;
    // router.rects = &tracker;
    // router.intermediate_placement = &placement;
    router.run        = run;
    router.edge_set   = edge_set;
    router.vertex_set = vertex_set;

    auto g = run->getGraph();
    for (auto const& e : edge_set) {
        LOGIC_ASSERTION_CHECK_FMT(
            vertex_set.contains(g->getSource(e)),
            "Edge {} source is not in the vertex set",
            g->getDebugEdgeFormat(e));
        LOGIC_ASSERTION_CHECK_FMT(
            vertex_set.contains(g->getTarget(e)),
            "Edge {} target is not in the vertex set",
            g->getDebugEdgeFormat(e));
    }

    for (auto const& vert : vertex_set) {
        if (run->hasLayout(vert)) {
            router.rects.insert_or_assign(
                vert, run->getAbsoluteBBox(vert));
        }
    }

    auto res = router.routeEdges();

    for (auto const& [edge, attr] : res.edges) {
        run->result.edges.insert_or_assign(edge, attr);
    }
}

void layout_run_unbound_edge_placement(layout::LayoutRun* run) {
    auto __scope = run->scopeLevelMsg(
        "unbound edge placement", "unbound-edge");
    EdgeIDSet   vertex_vertex_edges;
    EdgeIDSet   group_vertex_edges;
    VertexIDSet vertex_set;
    VertexIDSet group_set;

    for (auto const& vert : run->graph->getAllVertices()) {
        if (run->isGroupVertex(vert)) {
            group_set.incl(vert);
        } else {
            vertex_set.incl(vert);
        }
    }

    run->message(hstd::fmt("vertex_set:\n{}", run->getDebug(vertex_set)));

    for (auto const& edge : run->getAllUnboundEdges()) {
        if (vertex_set.contains(run->edges->getSource(edge))
            && vertex_set.contains(run->edges->getTarget(edge))) {
            vertex_vertex_edges.incl(edge);
        } else {
            group_vertex_edges.incl(edge);
        }
    }

    hstd::logic_assertion_check_not_nil(run);
    run_placement_with_subset(
        run, vertex_vertex_edges, vertex_set, "vertex_only_routing");

    run_placement_with_subset(
        run,
        group_vertex_edges,
        group_set + vertex_set,
        "vertex_and_group_routing");
}

} // namespace

void layout::LayoutRun::runFullLayout() {
    layout_run_full_layout(this);
    layout_run_unbound_edge_placement(this);
}
