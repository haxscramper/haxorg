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

void hstd::ext::graph::layout::LayoutRun::setNestedGroupAttribute(
    EdgeID const&                            edge,
    hstd::SPtr<IGroupVisualAttribute> const& attr) {

    getGroups()->assertTrackingEdge(edge);
    auto [parent, nested] = getGroups()->getParentAndNested(edge);

    // LOGIC_ASSERTION_CHECK(
    //     !getGraph()
    //          ->getVertex(nested)
    //          ->getOptionalAttribute<IVertexVisualAttribute>()
    //          .has_value(),
    //     "Cannot assign group visual attribute to a vertex that "
    //     "already has vertex visual attribute.");

    graph->getMVertex(nested)->addUniqueAttribute(attr);
}

void hstd::ext::graph::layout::LayoutRun::setNestedVertexAttribute(
    EdgeID const&                             edge,
    hstd::SPtr<IVertexVisualAttribute> const& attr) {

    getGroups()->assertTrackingEdge(edge);
    auto [parent, nested] = getGroups()->getParentAndNested(edge);

    // LOGIC_ASSERTION_CHECK(
    //     isGroupVertex(parent),
    //     "Cannot assign non-group visual attribute to the vertex "
    //     "already annotated with the group visual attribute.");

    LOGIC_ASSERTION_CHECK(
        std::dynamic_pointer_cast<IGroupVisualAttribute>(attr) == nullptr,
        "Cannot use group visual attribute in the vertex. Classes "
        "derived from the IVertexVisualAttribute should be managed by "
        "the addNewNativeSubgroup method");


    getGraph()->getMVertex(nested)->addUniqueAttribute(attr);
}

hstd::Vec<hstd::ext::visual::VisGroup> layout::LayoutRun::getVisual() const {
    hstd::Vec<hstd::ext::visual::VisGroup> res;
    EdgeIteration                          iter{this};
    auto aux = [&](this auto&& self, VertexID id) -> hstd::ext::visual::VisGroup {
        auto                        group  = getGroup(id);
        auto                        attr   = getLayout(id);
        hstd::ext::visual::VisGroup result = getLayout(id)->getVisual(id);

        for (auto const& sub : hstd::sorted(getSubGroups(id).items())) {
            auto visual          = self(sub);
            visual.original_id   = sub.getValue();
            visual.original_type = (int)ILayoutAttribute::Kind::Group;
            result.subgroups.push_back(visual);
        }

        for (auto const& it : hstd::sorted(getDirectVertices(id).items())) {
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

            for (auto const& port : hstd::sorted(ports->getPortsForVertex(it).items())) {
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

        for (auto const& it : hstd::sorted(iter.getEdgesForGroup(id).items())) {
            auto const& attr     = getLayout(it);
            auto        visual   = attr->getVisual(it);
            visual.original_id   = it.getValue();
            visual.original_type = (int)ILayoutAttribute::Kind::Edge;
            visual.custom.title  = graph->getDebug(it);
            result.subgroups.push_back(visual);
        }

        return result;
    };

    for (auto const& rg : groups->getRootVertices()) { res.push_back(aux(rg)); }

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


layout::LayoutRun::LayoutRun(
    hstd::SPtr<IGraph> const& graph,
    EdgeCollectionID          edge_id,
    PortCollectionID          port_id,
    EdgeCollectionID          hierarchy_id)
    : graph{graph}
    , groups{graph->getHierarchy(hierarchy_id)}
    , edges{graph->getEdgeCollection(edge_id)}
    , ports{graph->getPortCollection(port_id)} {
    hstd::logic_assertion_check_not_nil(graph);
}

EdgeIDSet layout::LayoutRun::getAllUnboundEdges() const {
    EdgeIDSet res;
    auto      el = edges->getEdges();
    for (auto const& edge : el) {
        auto vattr = getEdgeVisualAttribute(edge);
        if (std::dynamic_pointer_cast<UnboundEdgeVisualAttribute>(vattr)) {
            res.incl(edge);
        }
    }
    return res;
}

VertexIDSet layout::LayoutRun::getDirectVertices(VertexID const& id) const {
    LOGIC_ASSERTION_CHECK(isGroupVertex(id), "Cannot get nested vertices from non-group");
    VertexIDSet res;
    for (auto const& sub : groups->getSubVertices(id)) {
        if (!isGroupVertex(sub)) { res.incl(sub); }
    }
    return res;
}

VertexIDSet layout::LayoutRun::getSubGroups(VertexID const& id) const {
    LOGIC_ASSERTION_CHECK(isGroupVertex(id), "Cannot get nested groups from non-group");
    VertexIDSet res;
    for (auto const& sub : groups->getSubVertices(id)) {
        if (isGroupVertex(sub)) { res.incl(sub); }
    }
    return res;
}

VertexIDSet layout::LayoutRun::getSubGroupsNoLayoutSwitch(VertexID const& id) const {
    VertexIDSet noSwitch;
    for (auto const& sub : getSubGroups(id)) {
        if (!getGroup(sub)->hasAlgorithm()) { noSwitch.incl(sub); }
    }
    return noSwitch;
}

void layout::LayoutRun::setEdgeAttribute(
    EdgeID const&                           id,
    hstd::SPtr<IEdgeVisualAttribute> const& attr) {
    LOGIC_ASSERTION_CHECK_FMT(
        edges->hasEdge(id),
        "Layout run edge collection must have the edge registered "
        "before adding the attribute, id: {}",
        id);

    auto edge = getGraph()->getMEdge(id);
    LOGIC_ASSERTION_CHECK(edge != nullptr, "");
    edge->addUniqueAttribute(attr);
    // edges->trackEdge(id, graph->getSource(id),
    // graph->getTarget(id));
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


    auto aux = [&](this auto&& self, VertexID const& id, int depth) -> void {
        if (isGroupVertex(id)) {
            auto visual = getGroup(id);
            os.indent(depth * 2);
            os << hstd::fmt("GROUP {}", g->getDebug(id));
            if (visual->hasAlgorithm()) { os << " algo"; }

            if (hasLayout(id)) {
                auto layout = getLayout<IGroupLayoutAttribute>(id);
                os << hstd::fmt(" layout {}", layout->getBBox());
            }

            for (auto const& sub : hstd::sorted(getDirectVertices(id).items())) {
                os.newline();
                self(sub, depth + 1);
            }


            for (auto const& sub : hstd::sorted(iter.getEdgesForGroup(id).items())) {
                os.newline();
                aux_edge(sub, depth + 1);
            }


            for (auto const& sub : hstd::sorted(getSubGroups(id).items())) {
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

    for (auto const& g : hstd::sorted(groups->getRootVertices().items())) { aux(g, 0); }

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

hstd::SPtr<IGraph> hstd::ext::graph::layout::IGroupVisualAttribute::getGraph() const {
    return run->getGraph();
}

#if ORG_BUILD_WITH_PROTOBUF
void layout::IGroupVisualAttribute::writeSerialConstraints(
    google::protobuf::RepeatedPtrField<hstd::ext::graph::proto::IConstraint>* out,
    IGraph const* graph) const {
    for (auto const& c : constraints) { c->writeSerial(out->Add(), graph); }
}

void layout::IGroupVisualAttribute::readSerialConstraints(
    google::protobuf::RepeatedField<proto::IConstraint> const* in,
    IGraph const*                                              graph,
    IGraphSerialReaderFactory*                                 factory,
    IAttributeObject const*                                    vertex) {
    for (auto const& c : *in) {
        auto new_constraint = factory->newConstraint(&c);
        new_constraint->readSerial(&c, graph);
        constraints.push_back(new_constraint);
    }
}
#endif

hstd::ext::graph::EdgeIDSet hstd::ext::graph::layout::LayoutRun::EdgeIteration::
    getEdgesForGroup(VertexID const& id) {
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
        auto common_parent = run->getGroups()->getCommonAncestor({
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
