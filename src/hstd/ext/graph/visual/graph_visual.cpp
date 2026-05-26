#include "graph_visual.hpp"

#include <hstd/stdlib/algorithms.hpp>

using namespace hstd::ext::graph;

hstd::ext::graph::EdgeIDSet hstd::ext::graph::layout::LayoutRun::
    getLayoutLayerNestedEdges(VertexID const& id) const {
    VertexIDSet noSwitch;
    auto        aux = [&](this auto&& self, VertexID const& id) -> void {
        for (auto const& sub : getSubGroupsNoLayoutSwitch(id)) {
            noSwitch.incl(sub);
            self(sub);
        }

        noSwitch.incl(getDirectVertices(id));
    };

    aux(id);

    return edges->getFullyIncludedEdges(noSwitch);
}

hstd::ext::graph::EdgeID hstd::ext::graph::layout::LayoutRun::
    addNestedGroup(
        VertexID const&                          parent,
        VertexID const&                          nested,
        hstd::SPtr<IGroupVisualAttribute> const& attr) {

    LOGIC_ASSERTION_CHECK(
        !getGraph()
             ->getVertex(nested)
             ->getOptionalAttribute<IVertexVisualAttribute>()
             .has_value(),
        "Cannot assign group visual attribute to a vertex that "
        "already has vertex visual attribute.");

    groups->trackVertex(nested);
    auto res = groups->trackSubVertexRelation(parent, nested);
    graph->getMVertex(nested)->addUniqueAttribute(attr);

    return res;
}

hstd::ext::graph::EdgeID hstd::ext::graph::layout::LayoutRun::
    addNestedVertex(
        VertexID const&                           parent,
        VertexID const&                           nested,
        hstd::SPtr<IVertexVisualAttribute> const& attr) {

    LOGIC_ASSERTION_CHECK(
        isGroupVertex(parent),
        "Cannot assign non-group visual attribute to the vertex "
        "already "
        "annotated with the group visual attribute.");

    LOGIC_ASSERTION_CHECK(
        std::dynamic_pointer_cast<IGroupVisualAttribute>(attr) == nullptr,
        "Cannot use group visual attribute in the vertex. Classes "
        "derived from the IVertexVisualAttribute should be managed by "
        "the addNewNativeSubgroup method");

    getGraph()->getMVertex(nested)->addUniqueAttribute(attr);
    hstd::logic_assertion_check_not_nil(groups);
    groups->trackVertex(nested);
    return groups->trackSubVertexRelation(parent, nested);
}

hstd::ext::graph::PortID hstd::ext::graph::layout::LayoutRun::addPort(
    VertexID const&                   v,
    EdgeID const&                     e,
    bool                              is_start,
    std::optional<std::string> const& stable_id) {
    if (is_start) {
        LOGIC_ASSERTION_CHECK_FMT(
            edges->getSource(e) == v,
            "Mismatch between provided vertex and edge source: "
            "start({}) is {}, attempting to use {}",
            getDebug(e),
            getDebug(edges->getSource(e)),
            getDebug(v));
    } else {
        LOGIC_ASSERTION_CHECK_FMT(
            edges->getTarget(e) == v,
            "Mismatch between provided vertex and target source: "
            "target({}) is {}, attempting to use {}",
            getDebug(e),
            getDebug(edges->getTarget(e)),
            getDebug(v));
    }

    return ports->addPort(v, e, is_start, stable_id);
}


hstd::Vec<hstd::ext::visual::VisGroup> layout::LayoutRun::getVisual()
    const {
    hstd::Vec<hstd::ext::visual::VisGroup> res;
    EdgeIteration                          iter{this};
    auto aux = [&](this auto&& self,
                   VertexID    id) -> hstd::ext::visual::VisGroup {
        auto                        group  = getGroup(id);
        auto                        attr   = getLayout(id);
        hstd::ext::visual::VisGroup result = getLayout(id)->getVisual(id);

        for (auto const& sub : hstd::sorted(getSubGroups(id).items())) {
            auto visual          = self(sub);
            visual.original_id   = sub.getValue();
            visual.original_type = (int)ILayoutAttribute::Kind::Group;
            result.subgroups.push_back(visual);
        }

        for (auto const& it :
             hstd::sorted(getDirectVertices(id).items())) {
            auto const& attr   = getLayout(it);
            auto        visual = attr->getVisual(it);
            LOGIC_ASSERTION_CHECK_FMT(
                visual.offset == attr->getBBox().upper_left(),
                "Vertex visualization group must use the group offset for "
                "the element placement. The visual group offset is {}, "
                "bounding box offset {}",
                visual.offset,
                attr->getBBox().upper_left());

            visual.original_id   = it.getValue();
            visual.original_type = (int)ILayoutAttribute::Kind::Vertex;
            visual.custom.title  = graph->getDebug(it);

            for (auto const& port :
                 hstd::sorted(ports->getPortsForVertex(it).items())) {
                auto const& attr        = getLayout(port);
                auto        port_visual = attr->getVisual(port);
                visual.subgroups.push_back(port_visual);

                LOGIC_ASSERTION_CHECK_FMT(
                    port_visual.offset == attr->getBBox().upper_left(),
                    "Vertex port_visualization group must use the group "
                    "offset for the element placement. The port_visual "
                    "group offset is {}, bounding box offset {}",
                    visual.offset,
                    attr->getBBox().upper_left());
            }

            result.subgroups.push_back(visual);
        }

        for (auto const& it :
             hstd::sorted(iter.getEdgesForGroup(id).items())) {
            auto const& attr     = getLayout(it);
            auto        visual   = attr->getVisual(it);
            visual.original_id   = it.getValue();
            visual.original_type = (int)ILayoutAttribute::Kind::Edge;
            visual.custom.title  = graph->getDebug(it);
            result.subgroups.push_back(visual);
        }

        return result;
    };

    for (auto const& rg : groups->getRootVertices()) {
        res.push_back(aux(rg));
    }

    iter.validateLeftoverEdges();

    hstd::ext::visual::VisGroup unbound_edge_overlay;

    for (auto const& it : this->getAllUnboundEdges()) {
        auto const& attr     = getLayout(it);
        auto        visual   = attr->getVisual(it);
        visual.original_id   = it.getValue();
        visual.original_type = (int)ILayoutAttribute::Kind::Edge;
        visual.custom.title  = graph->getDebug(it);
        unbound_edge_overlay.subgroups.push_back(visual);
    }

    res.push_back(unbound_edge_overlay);

    return res;
}


void hstd::ext::graph::layout::LayoutRun::treeRepr(
    hstd::ColStream&    os,
    TreeReprConf const& conf) const {
    auto g = getGraph();

    EdgeIteration iter{this};

    auto aux_edge = [&](EdgeID const& id, int depth) {
        auto visual = getEdgeVisualAttribute(id);
        os.indent(depth * 2);
        os << hstd::fmt("EDGE {}", g->getDebug(id));
    };


    auto aux =
        [&](this auto&& self, VertexID const& id, int depth) -> void {
        if (isGroupVertex(id)) {
            auto visual = getGroup(id);
            os.indent(depth * 2);
            os << hstd::fmt("GROUP {}", g->getDebug(id));
            if (visual->hasAlgorithm()) { os << " algo"; }

            if (hasLayout(id)) {
                auto layout = getLayout<IGroupLayoutAttribute>(id);
                os << hstd::fmt(" layout {}", layout->getBBox());
            }

            for (auto const& sub :
                 hstd::sorted(getDirectVertices(id).items())) {
                os.newline();
                self(sub, depth + 1);
            }


            for (auto const& sub :
                 hstd::sorted(iter.getEdgesForGroup(id).items())) {
                os.newline();
                aux_edge(sub, depth + 1);
            }


            for (auto const& sub :
                 hstd::sorted(getSubGroups(id).items())) {
                os.newline();
                self(sub, depth + 1);
            }

        } else {
            auto visual = getVertexVisualAttribute(id);
            os.indent(depth * 2);
            os << hstd::fmt("VERTEX {}", g->getDebug(id));

            if (hasLayout(id)) {
                auto layout = getLayout<IVertexLayoutAttribute>(id);
                os << hstd::fmt(" layout {}", layout->getBBox());
            }
        }
    };

    for (auto const& g : hstd::sorted(groups->getRootVertices().items())) {
        aux(g, 0);
    }

    for (auto const& e : hstd::sorted(iter.getLeftoverEdges().items())) {
        os.newline();
        aux_edge(e, 0);
        os << " leftover";
    }

    for (auto const& e : hstd::sorted(getAllUnboundEdges().items())) {
        os.newline();
        aux_edge(e, 0);
        os << " unbound";
    }
}

hstd::SPtr<IGraph> hstd::ext::graph::layout::IGroupVisualAttribute::
    getGraph() const {
    return run->graph;
}

hstd::ext::graph::EdgeIDSet hstd::ext::graph::layout::LayoutRun::
    EdgeIteration::getEdgesForGroup(VertexID const& id) {
    // collect list of edges between explicit sub-vertices for a
    // group.
    auto direct_edges = run->getDirectlyNestedEdges(id);
    // edges with source/target vertex in the group, or edges
    // incident to the group itself.
    auto indirect_edges = run->getPartiallyNestedEdges(id)
                        + run->getGroupIncidentEdges(id);

    EdgeIDSet result = direct_edges;

    // collating the list of edges that are not explicitly nested.
    leftover_edges.incl(
        indirect_edges
        - direct_edges
        // indirect edges set will, by definition, encounter and
        // edge twice: for source entry and for target group.
        - processed_edges);

    EdgeIDSet to_drop;
    // for each leftover edge, try to find the common parent, and
    // check if the current group matches.
    for (auto const& edge : leftover_edges) {
        auto common_parent = run->groups->getCommonAncestor({
            run->getGraph()->getSource(edge),
            run->getGraph()->getTarget(edge),
        });

        if (common_parent.has_value() && common_parent.value() == id) {
            result.incl(edge);
            to_drop.incl(edge);
        }
    }

    leftover_edges.excl(to_drop);
    processed_edges.incl(result);

    return result;
}
