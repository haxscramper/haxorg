#include "visual_factory.hpp"
#include "hstd/ext/graph/visual/graph_graphviz.hpp"
#include "src/hstd/ext/graph/visual/graph_graphviz.pb.h"
#include <hstd/ext/hstd_serde.hpp>

using namespace hstd::ext::graph;

hstd::SPtr<hstd::ext::graph::IVertex> hstd::ext::graph::VisualFactory::newVertex(
    proto::IVertex const* in) {
    LOGIC_ASSERTION_CHECK_FMT(
        in->has_payload(),
        "De-serialization input does not have payload object {}",
        serde::getJString(*in));
    OP_TRACER_MESSAGE(this, "URL {}", in->payload().type_url());
    hstd::SPtr<IVertex> res;
    if (in->payload().Is<proto::TrivialVertexPayload>()) {
        res = std::make_shared<TrivialVertex>(in->stable_id());
    } else {
        throw hstd::logic_unhandled_kind_error::init(in->payload().type_url());
    }

    return res;
}

hstd::SPtr<hstd::ext::graph::IAttribute> hstd::ext::graph::VisualFactory::newAttribute(
    proto::IAttribute const* in,
    IGraph const*            graph,
    IAttributeObject const*  parent) {
    LOGIC_ASSERTION_CHECK_FMT(
        in->has_payload(),
        "De-serialization input does not have payload object {}",
        serde::getJString(*in));
    OP_TRACER_MESSAGE(this, "URL {}", in->payload().type_url());

    if (in->payload().Is<gv::proto::GroupAttributePayload>()) {
        auto vertex = hstd::validated_dynamic_cast<IVertex>(parent);
        gv::proto::GroupAttributePayload pl;
        in->payload().UnpackTo(&pl);

        if (pl.has_parent_stable_id()) {
            return graph->getVertex(graph->getVertexIDByStableId(pl.parent_stable_id()))
                ->getUniqueAttribute<gv::GraphGroup>()
                ->newSubgraph(vertex->getStableId());
        } else {
            return gv::GraphGroup::newRootGraph(run, vertex->getStableId());
        }
    } else if (in->payload().Is<gv::proto::NodeAttributePayload>()) {
        auto vertex = hstd::validated_dynamic_cast<IVertex>(parent);
        gv::proto::NodeAttributePayload pl;
        in->payload().UnpackTo(&pl);
        LOGIC_ASSERTION_CHECK_FMT(
            !pl.parent_stable_id().empty(),
            "Parent stable ID cannot be set to empty, graphviz "
            "attribute for node '{}' must have the parent ID "
            "specified",
            vertex->getStableId());

        return graph->getVertex(graph->getVertexIDByStableId(pl.parent_stable_id()))
            ->getUniqueAttribute<gv::GraphGroup>()
            ->node(vertex->getStableId());
    } else if (in->payload().Is<gv::proto::EdgeAttributePayload>()) {
        auto vertex = hstd::validated_dynamic_cast<IEdge>(parent);
        gv::proto::EdgeAttributePayload pl;
        in->payload().UnpackTo(&pl);
        LOGIC_ASSERTION_CHECK_FMT(
            !pl.parent_stable_id().empty(),
            "Parent stable ID cannot be set to empty, graphviz "
            "attribute for node '{}' must have the parent ID "
            "specified",
            vertex->getStableId());

        auto edge_id = graph->getEdgeIDByStableId(vertex->getStableId());

        return graph->getVertex(graph->getVertexIDByStableId(pl.parent_stable_id()))
            ->getUniqueAttribute<gv::GraphGroup>()
            ->edge(
                *graph->getVertex(graph->getSource(edge_id))
                     ->getUniqueAttribute<gv::NodeAttribute>(),
                *graph->getVertex(graph->getTarget(edge_id))
                     ->getUniqueAttribute<gv::NodeAttribute>());
    } else {
        throw hstd::logic_unhandled_kind_error::init(in->payload().type_url());
    }
}

hstd::SPtr<hstd::ext::graph::IPortCollection> hstd::ext::graph::VisualFactory::
    newPortCollection(proto::IPortCollection const* in) {
    LOGIC_ASSERTION_CHECK_FMT(
        in->has_payload(),
        "De-serialization input does not have payload object {}",
        serde::getJString(*in));
    OP_TRACER_MESSAGE(this, "URL {}", in->payload().type_url());
    // if (in->payload().Is<org::graph::proto::MapNodePayload>()) {
    // } else
    { throw hstd::logic_unhandled_kind_error::init(in->payload().type_url()); }
}

hstd::SPtr<hstd::ext::graph::IEdgeCollection> hstd::ext::graph::VisualFactory::
    newEdgeCollection(proto::IEdgeCollection const* in) {
    LOGIC_ASSERTION_CHECK_FMT(
        in->has_payload(),
        "De-serialization input does not have payload object {}",
        serde::getJString(*in));
    OP_TRACER_MESSAGE(this, "URL {}", in->payload().type_url());
    if (in->payload().Is<proto::TrivialEdgeCollectionPayload>()) {
        return std::make_shared<TrivialEdgeCollection>(
            EdgeCollectionID{static_cast<hstd::u16>(in->collection_id())});
    } else {
        throw hstd::logic_unhandled_kind_error::init(in->payload().type_url());
    }
}

hstd::ext::graph::VisualFactory::VisualFactory(hstd::SPtr<IGraph> const& graph)
    : graph{graph} {
    if (graph->getPorts().empty()) {
        graph->addPorts(std::make_shared<TrivialPortCollection>());
    }

    run = std::make_shared<layout::LayoutRun>(
        graph,
        graph->getCollections().at(0)->getCollectionID(),
        graph->getPorts().at(0)->getCollectionID(),
        graph->getHierarchies().at(0)->getCollectionID());
}


hstd::SPtr<hstd::ext::graph::IVertexHierarchy> hstd::ext::graph::VisualFactory::
    newVertexHierarchy(proto::IVertexHierarchy const* in) {
    LOGIC_ASSERTION_CHECK_FMT(
        in->has_payload(),
        "De-serialization input does not have payload object {}",
        serde::getJString(*in));
    OP_TRACER_MESSAGE(this, "URL {}", in->payload().type_url());
    if (in->payload().Is<proto::TrivialVertexHierarchyPayload>()) {
        return std::make_shared<TrivialHierarchy>();
    } else {
        throw hstd::logic_unhandled_kind_error::init(in->payload().type_url());
    }
}

hstd::SPtr<layout::IConstraint> hstd::ext::graph::VisualFactory::newConstraint(
    proto::IConstraint const* in) {
    LOGIC_ASSERTION_CHECK_FMT(
        in->has_payload(),
        "De-serialization input does not have payload object {}",
        serde::getJString(*in));
    OP_TRACER_MESSAGE(this, "URL {}", in->payload().type_url());
    hstd::SPtr<layout::IConstraint> res;
    if (false) {
    } else {
        throw hstd::logic_unhandled_kind_error::init(in->payload().type_url());
    }

    return res;
}

hstd::SPtr<hstd::ext::graph::IEdge> hstd::ext::graph::VisualFactory::newEdge(
    proto::IEdge const* edge) {
    LOGIC_ASSERTION_CHECK_FMT(
        edge->has_payload(),
        "De-serialization input does not have payload object {}",
        serde::getJString(*edge));

    if (edge->payload().Is<proto::TrivialEdgePayload>()) {
        return std::make_shared<TrivialEdge>(edge->stable_id());
    } else {
        throw hstd::logic_unhandled_kind_error::init(edge->payload().type_url());
    }
}

hstd::SPtr<IPort> hstd::ext::graph::VisualFactory::newPort(proto::IPort const* port) {
    LOGIC_ASSERTION_CHECK_FMT(
        port->has_payload(),
        "De-serialization input does not have payload object {}",
        serde::getJString(*port));

    // if (port->payload().Is<org::graph::proto::MapNodePayload>()) {
    // } else
    { throw hstd::logic_unhandled_kind_error::init(port->payload().type_url()); }
}


#include "visual_factory.hpp"
