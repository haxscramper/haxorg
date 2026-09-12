#include "visual_factory.hpp"
#include "hstd/ext/graph/visual/graph_graphviz.hpp"
#include "hstd/ext/graph/visual/graph_kiwi.hpp"
#include "hstd/system/exceptions.hpp"
#include <hstd/ext/hstd_serde.hpp>
#include <hstd/stdlib/VecFormatter.hpp>
#include <src/hstd/ext/graph/visual/graph_graphviz.pb.h>
#include <src/hstd/ext/graph/visual/graph_kiwi.pb.h>

using namespace hstd::ext::graph;

namespace {
std::string unexpected_payload_kind_msg(
    ::google::protobuf::Any const& payload,
    std::string const&             stable_id,
    std::string const&             msg,
    hstd::Vec<std::string> const&  expected_payloads) {
    return hstd::fmt(
        "Unexpected payload URL for vertex '{}': '{}'. {}Expected payloads {}",
        stable_id,
        payload.type_url(),
        msg,
        expected_payloads.map<std::string>([](std::string const& value) -> std::string {
            return hstd::fmt("type.googleapis.com/{}", value);
        }));
}
} // namespace

hstd::SPtr<hstd::ext::graph::IVertex> hstd::ext::graph::VisualFactory::newVertex(
    proto::IVertex const* in) {
    LOGIC_ASSERTION_CHECK_FMT(
        in->has_payload(),
        "De-serialization input does not have payload object {}",
        serde::getJString(*in));
    OP_TRACER_MESSAGE(
        this,
        "VisualFactory::newVertex ID {} URL {}",
        in->stable_id(),
        in->payload().type_url());
    hstd::SPtr<IVertex> res;
    if (in->payload().Is<proto::TrivialVertexPayload>()) {
        res = std::make_shared<TrivialVertex>(in->stable_id());
    } else {
        throw hstd::logic_unhandled_kind_error::init(unexpected_payload_kind_msg(
            in->payload(),
            in->stable_id(),
            "Cannot read serial data for the graph vertex. ",
            {
                std::string{proto::TrivialVertexPayload::descriptor()->full_name()},
            }));
    }

    return res;
}

hstd::SPtr<hstd::ext::graph::IAttribute> hstd::ext::graph::VisualFactory::newAttribute(
    proto::IAttribute const* in,
    IGraph const*            graph,
    IAttributeObject const*  attr_object) {

    hstd::Opt<std::string> stable_id;
    if (auto ptr = dynamic_cast<IGraphObjectBase const*>(attr_object)) {
        stable_id = ptr->getStableId();
    }

    LOGIC_ASSERTION_CHECK_FMT(
        in->has_payload(),
        "De-serialization input does not have payload object, "
        "cannot determine the runtime type{}\n{}",
        stable_id ? hstd::fmt(" '{}':", stable_id.value()) : ":",
        serde::getJString(*in));

    OP_TRACER_MESSAGE(this, "URL {}", in->payload().type_url());

    // Layout run becomes becessary only when creating the layout attributes, they hold
    // backend-specific data that might rely on the common layout context. The attributes
    // themselves are converted after the main collections are already created, see
    // `IGraph::readSerial` for the detailed order of the data reads and conversions.
    if (!run) {
        auto tg = this->graph;
        if (tg->getPorts().empty()) {
            tg->addPorts(std::make_shared<TrivialPortCollection>());
        }

        LOGIC_ASSERTION_CHECK(
            0 < tg->getCollections().size() && 0 < tg->getPorts().size()
                && 0 < tg->getHierarchies().size(),
            "Not all collections were initialized in the serial data. "
            "Visual factory cannot create attribute with missing collections. "
            "Input must contain at least one edge, port and hierarchy collections. ");

        run = std::make_shared<layout::LayoutRun>(
            tg,
            tg->getCollections().at(0)->getCollectionID(),
            tg->getPorts().at(0)->getCollectionID(),
            tg->getHierarchies().at(0)->getCollectionID());
    }

    auto unpack_as = [&in, &attr_object]<typename ProtoType, typename GraphInterface>()
        -> hstd::Pair<hstd::Opt<ProtoType>, GraphInterface const*> {
        if (in->payload().Is<ProtoType>()) {
            ProtoType pl;
            in->payload().UnpackTo(&pl);
            auto target = hstd::validated_dynamic_cast<GraphInterface>(attr_object);
            return {std::move(pl), target};
        } else {
            return {std::nullopt, nullptr};
        }
    };

    auto get_vertex_attribute = [&]<typename AttrType>(std::string const& id) {
        auto vertex = graph->getVertex(graph->getVertexIDByStableId(id));
        auto target = hstd::validated_dynamic_cast<IGraphObjectBase>(attr_object);
        LOGIC_ASSERTION_CHECK_FMT(
            vertex->hasOptionalAttribute<AttrType>(),
            "Cannot get attribute {} from ID {} when building attribute for {}",
            hstd::value_metadata<AttrType>::typeName(),
            id,
            target->getStableId());

        return vertex->getUniqueAttribute<AttrType>();
    };

    // group attribute payloads
    if (auto const& [pl, vertex] = unpack_as.operator()<
                                   gv::proto::GroupAttributePayload,
                                   IVertex>();
        pl) {
        if (pl->has_parent_stable_id()) {
            LOGIC_ASSERTION_CHECK_FMT(
                !pl->parent_stable_id().empty(),
                "Graphviz group vertex '{}' has empty parent stable ID. "
                "To create a top-level graphivz layout group, fully omit ID field. "
                "Existing but empty ID field is interpreted as graphviz cluster.",
                vertex->getStableId());
            return get_vertex_attribute
                .operator()<gv::GraphGroup>(pl->parent_stable_id())
                ->newSubgraph(vertex->getStableId());
        } else {
            return gv::GraphGroup::newRootGraph(run, vertex->getStableId());
        }

    } else if (
        auto const& [pl, vertex] = unpack_as.operator()<
                                   kw::proto::KiwiGroupVisualAttributePayload,
                                   IVertex>();
        pl) {

        hstd::SPtr<layout::IGroupVisualAttribute> result;
        if (pl->has_parent_stable_id()) {
            auto parent_group_id = graph->getVertexIDByStableId(pl->parent_stable_id());
            auto this_vertex_id  = graph->getVertexIDByStableId(vertex->getStableId());
            auto nesting_edge_id = run->getGroups()->getNestingEdgeID(
                parent_group_id, this_vertex_id);

            result = get_vertex_attribute
                         .operator()<kw::KiwiGroup>(pl->parent_stable_id())
                         ->addNewNativeSubgroup(nesting_edge_id);

        } else {
            result = kw::KiwiGroup::newRootGraph(run);
        }

        for (auto const& c : pl->base().constraints()) {
            auto new_constraint = newConstraint(&c);
            new_constraint->readSerial(&c, graph);
            result->addConstraint(new_constraint);
        }

        return result;


        // node payloads
    } else if (
        auto const& [pl, vertex] = unpack_as.
                                   operator()<gv::proto::NodeAttributePayload, IVertex>();
        pl) {
        LOGIC_ASSERTION_CHECK_FMT(
            !pl->parent_stable_id().empty(),
            "Parent stable ID cannot be set to empty, graphviz "
            "attribute for node '{}' must have the parent ID "
            "specified",
            vertex->getStableId());

        return get_vertex_attribute.operator()<gv::GraphGroup>(pl->parent_stable_id())
            ->node(vertex->getStableId());

    } else if (
        auto const& [pl, vertex] = unpack_as.operator()<
                                   kw::proto::KiwiVertexVisualAttributePayload,
                                   IVertex>();
        pl) {

        auto parent_group_id = graph->getVertexIDByStableId(pl->parent_stable_id());
        auto this_vertex_id  = graph->getVertexIDByStableId(vertex->getStableId());
        auto nesting_edge_id = run->getGroups()->getNestingEdgeID(
            parent_group_id, this_vertex_id);

        return get_vertex_attribute.operator()<kw::KiwiGroup>(pl->parent_stable_id())
            ->addVertex(
                nesting_edge_id, geometry::Size(pl->rect().x0(), pl->rect().y0()));

        // edge payloads
    } else if (
        auto const& [pl, edge] = unpack_as.
                                 operator()<gv::proto::EdgeAttributePayload, IEdge>();
        pl) {
        LOGIC_ASSERTION_CHECK_FMT(
            !pl->parent_stable_id().empty(),
            "Parent stable ID cannot be set to empty, graphviz "
            "attribute for node '{}' must have the parent ID "
            "specified",
            edge->getStableId());

        auto edge_id = graph->getEdgeIDByStableId(edge->getStableId());

        // get the existing parent attribute object and assign edges to it.
        // the parent vertex attribute should already be created.
        return get_vertex_attribute.operator()<gv::GraphGroup>(pl->parent_stable_id())
            ->edge(
                *graph->getVertex(graph->getSource(edge_id))
                     ->getUniqueAttribute<gv::NodeAttribute>(),
                *graph->getVertex(graph->getTarget(edge_id))
                     ->getUniqueAttribute<gv::NodeAttribute>());


    } else {
        throw hstd::logic_unhandled_kind_error::init(unexpected_payload_kind_msg(
            in->payload(),
            stable_id.value_or("attribute"),
            "Cannot read serial data for the graph object attribute. ",
            {
                std::string{gv::proto::GroupAttributePayload::descriptor()->full_name()},
                std::string{gv::proto::NodeAttributePayload::descriptor()->full_name()},
                std::string{gv::proto::EdgeAttributePayload::descriptor()->full_name()},
                std::string{kw::proto::KiwiVertexVisualAttributePayload::descriptor()
                                ->full_name()},
                std::string{kw::proto::KiwiGroupVisualAttributePayload::descriptor()
                                ->full_name()},
            }));
    }
}

hstd::SPtr<hstd::ext::graph::IPortCollection> hstd::ext::graph::VisualFactory::
    newPortCollection(proto::IPortCollection const* in) {
    LOGIC_ASSERTION_CHECK_FMT(
        in->has_payload(),
        "De-serialization input does not have payload object {}",
        serde::getJString(*in));
    OP_TRACER_MESSAGE(this, "URL {}", in->payload().type_url());
    if (in->payload().Is<proto::TrivialPortCollectionPayload>()) {
        return std::make_shared<hstd::ext::graph::TrivialPortCollection>();
    } else {
        throw hstd::logic_unhandled_kind_error::init(unexpected_payload_kind_msg(
            in->payload(),
            "port-collection",
            "Cannot read serial data for edge collection. ",
            {
                std::string{
                    proto::TrivialPortCollectionPayload::descriptor()->full_name()},
            }));
    }
}

hstd::SPtr<hstd::ext::graph::IEdgeCollection> hstd::ext::graph::VisualFactory::
    newEdgeCollection(proto::IEdgeCollection const* in) {
    LOGIC_ASSERTION_CHECK_FMT(
        in->has_payload(),
        "No payload for edge collection '{}': {}",
        in->stable_id(),
        serde::getJString(*in));
    OP_TRACER_MESSAGE(this, "URL {}", in->payload().type_url());
    if (in->payload().Is<proto::TrivialEdgeCollectionPayload>()) {
        return std::make_shared<TrivialEdgeCollection>(
            EdgeCollectionID{static_cast<hstd::u16>(in->collection_id())});
    } else {
        throw hstd::logic_unhandled_kind_error::init(unexpected_payload_kind_msg(
            in->payload(),
            hstd::fmt("{}", in->collection_id()),
            "Cannot read serial data for edge collection. ",
            {
                std::string{
                    proto::TrivialEdgeCollectionPayload::descriptor()->full_name()},
            }));
    }
}

hstd::SPtr<hstd::ext::graph::IVertexHierarchy> hstd::ext::graph::VisualFactory::
    newVertexHierarchy(proto::IVertexHierarchy const* in) {
    LOGIC_ASSERTION_CHECK_FMT(
        in->has_payload(),
        "No payload for vertex hierarchy '{}': {}",
        in->stable_id(),
        serde::getJString(*in));
    OP_TRACER_MESSAGE(this, "URL {}", in->payload().type_url());
    if (in->payload().Is<proto::TrivialVertexHierarchyPayload>()) {
        return std::make_shared<TrivialHierarchy>();
    } else {
        throw hstd::logic_unhandled_kind_error::init(unexpected_payload_kind_msg(
            in->payload(),
            in->stable_id(),
            "Cannot read serial data for vertex hierarchy. ",
            {
                std::string{
                    proto::TrivialVertexHierarchyPayload::descriptor()->full_name()},
            }));
    }
}

hstd::SPtr<layout::IConstraint> hstd::ext::graph::VisualFactory::newConstraint(
    proto::IConstraint const* in) {
    LOGIC_ASSERTION_CHECK_FMT(
        in->has_payload(),
        "De-serialization input does not have payload object {}",
        serde::getJString(*in));
    OP_TRACER_MESSAGE(this, "URL {}", in->payload().type_url());
    namespace kp = kw::proto;
    hstd::SPtr<layout::IConstraint> res;
    if (auto kiwi_align = try_payload<kp::KiwiAlignConstraintPayload>(in->payload())) {
        return std::make_shared<kw::AlignConstraint>(run);
    } else if (
        auto kiwi_align = try_payload<kp::KiwiSeparateConstraintPayload>(in->payload())) {
        return std::make_shared<kw::SeparateConstraint>(run);
    } else if (
        auto kiwi_align = try_payload<kp::KiwiMultiSeparateConstraintPayload>(
            in->payload())) {
        return std::make_shared<kw::MultiSeparateConstraint>(run);
    } else if (
        auto kiwi_align = try_payload<kp::KiwiLinearConstraintPayload>(in->payload())) {
        return std::make_shared<kw::LinearConstraint>(run);
    } else if (
        auto kiwi_align = try_payload<kp::KiwiRelativeConstraintPayload>(in->payload())) {
        return std::make_shared<kw::RelativeConstraint>(run);
    } else {
        throw hstd::logic_unhandled_kind_error::init(unexpected_payload_kind_msg(
            in->payload(),
            "payload",
            "Cannot read serial data for constraint payload. ",
            {
                std::string{kp::KiwiAlignConstraintPayload::descriptor()->full_name()},
                std::string{kp::KiwiRelativeConstraintPayload::descriptor()->full_name()},
                std::string{kp::KiwiSeparateConstraintPayload::descriptor()->full_name()},
                std::string{
                    kp::KiwiMultiSeparateConstraintPayload::descriptor()->full_name()},
                std::string{kp::KiwiLinearConstraintPayload::descriptor()->full_name()},
            }));
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
        throw hstd::logic_unhandled_kind_error::init(unexpected_payload_kind_msg(
            edge->payload(),
            edge->stable_id(),
            "Cannot read serial data for the graph edge. ",
            {
                std::string{proto::TrivialEdgePayload::descriptor()->full_name()},
            }));
    }
}

hstd::SPtr<IPort> hstd::ext::graph::VisualFactory::newPort(proto::IPort const* port) {
    LOGIC_ASSERTION_CHECK_FMT(
        port->has_payload(),
        "De-serialization input does not have payload object {}",
        serde::getJString(*port));

    // if (port->payload().Is<org::graph::proto::MapNodePayload>()) {
    // } else
    {
        throw hstd::logic_unhandled_kind_error::init(unexpected_payload_kind_msg(
            port->payload(),
            port->port_id(),
            "Cannot read serial data for the graph port. ",
            {
                std::string{proto::TrivialEdgePayload::descriptor()->full_name()},
            }));
    }
}


#include "visual_factory.hpp"
