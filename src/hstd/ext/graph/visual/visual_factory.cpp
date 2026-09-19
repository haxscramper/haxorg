#if ORG_BUILD_WITH_PROTOBUF

#    include "visual_factory.hpp"
#    include "hstd/ext/graph/visual/graph_graphviz.hpp"
#    include "hstd/ext/graph/visual/graph_kiwi.hpp"
#    include "hstd/system/exceptions.hpp"
#    include <hstd/ext/hstd_serde.hpp>
#    include <hstd/stdlib/VecFormatter.hpp>


using namespace hstd::ext::graph;

namespace {
std::string unexpected_payload_kind_msg(
    ::google::protobuf::Any const& payload,
    std::string const&             stable_id,
    std::string const&             msg,
    hstd::Vec<std::string> const&  expected_payloads) {
    return hstd::fmt(
        "Unexpected payload URL for vertex '{}': '{}'. {}Expected payloads:\n{}",
        stable_id,
        payload.type_url(),
        msg,
        hstd::join(
            "\n"_str_view,
            expected_payloads.map<std::string>(
                [](std::string const& value) -> std::string {
                    return hstd::fmt("type.googleapis.com/{}", value);
                })));
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
    return std::visit(
        hstd::overloaded{
            [&](proto::TrivialVertexPayload const& pl) -> hstd::SPtr<IVertex> {
                return std::make_shared<TrivialVertex>(in->stable_id());
            },
        },
        hstd::serde::unpackVariantT<proto::TrivialVertexPayload>(
            in->payload(),
            in->stable_id(),
            "Cannot read serial data for the graph vertex. "));
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

    auto get_vertex_attribute = [&]<typename AttrType, typename PayloadType>(
                                    PayloadType const& pl, std::string const& message) {
        auto target = hstd::validated_dynamic_cast<IGraphObjectBase>(attr_object);
        LOGIC_ASSERTION_CHECK_FMT(
            !pl.parent_stable_id().empty(),
            "Graph object '{}' has empty parent stable ID. {}",
            target->getStableId(),
            message);

        std::string const& id     = pl.parent_stable_id();
        auto               vertex = graph->getVertex(graph->getVertexIDByStableId(id));

        LOGIC_ASSERTION_CHECK_FMT(
            vertex->hasOptionalAttribute<AttrType>(),
            "Cannot get attribute {} from ID {} when building attribute for {}",
            hstd::value_metadata<AttrType>::typeName(),
            id,
            target->getStableId());

        return vertex->getUniqueAttribute<AttrType>();
    };

    auto payload = serde::unpackVariant<VisualAttributePayloadTypes>(
        in->payload(),
        stable_id.value_or("attribute"),
        "Cannot read serial data for the graph object attribute. ");

    auto overload = hstd::overloaded{
        // group attribute payloads
        [&](gv::proto::GroupAttributePayload const& pl) -> hstd::SPtr<IAttribute> {
            auto vertex = hstd::validated_dynamic_cast<IVertex>(attr_object);
            if (pl.has_parent_stable_id()) {
                auto group = get_vertex_attribute.operator()<gv::GraphGroup>(
                    pl,
                    "To create a top-level graphivz layout group, fully omit ID "
                    "field. "
                    "Existing but empty ID field is interpreted as invalid graphviz "
                    "cluster.");
                return group->newSubgraph(vertex->getStableId());
            } else {
                return gv::GraphGroup::newRootGraph(run, vertex->getStableId());
            }
        },
        [&](kw::proto::KiwiGroupVisualAttributePayload const& pl)
            -> hstd::SPtr<IAttribute> {
            auto vertex = hstd::validated_dynamic_cast<IVertex>(attr_object);

            hstd::SPtr<layout::IGroupVisualAttribute> result;
            if (pl.has_parent_stable_id()) {
                auto group = get_vertex_attribute.operator()<kw::KiwiGroup>(
                    pl,
                    //
                    "To create a top-level kiwi layout group, fully omit ID field. "
                    "Existing but empty ID field is interpreted as invalid kiwi "
                    "cluster.");

                auto parent_group_id = graph->getVertexIDByStableId(
                    pl.parent_stable_id());
                auto this_vertex_id = graph->getVertexIDByStableId(vertex->getStableId());
                auto nesting_edge_id = run->getGroups()->getNestingEdgeID(
                    parent_group_id, this_vertex_id);

                return group->addNewNativeSubgroup(nesting_edge_id);
            } else {
                return kw::KiwiGroup::newRootGraph(run);
            }
        },
        // node payloads
        [&](gv::proto::NodeAttributePayload const& pl) -> hstd::SPtr<IAttribute> {
            auto vertex = hstd::validated_dynamic_cast<IVertex>(attr_object);
            return get_vertex_attribute
                .operator()<gv::GraphGroup>(
                    pl,
                    "Parent ID cannot be set to empty, parent ID must be present in "
                    "the "
                    "attribute")
                ->node(vertex->getStableId());
        },
        [&](kw::proto::KiwiVertexVisualAttributePayload const& pl)
            -> hstd::SPtr<IAttribute> {
            auto vertex = hstd::validated_dynamic_cast<IVertex>(attr_object);

            auto group = get_vertex_attribute.operator()<kw::KiwiGroup>(
                pl,
                "Parent ID cannot be set to empty, parent ID must be present in the "
                "attribute");

            auto parent_group_id = graph->getVertexIDByStableId(pl.parent_stable_id());
            auto this_vertex_id  = graph->getVertexIDByStableId(vertex->getStableId());
            auto nesting_edge_id = run->getGroups()->getNestingEdgeID(
                parent_group_id, this_vertex_id);

            return group->addVertex(
                nesting_edge_id, geometry::Size(pl.rect().x0(), pl.rect().y0()));
        },
        // edge payloads
        [&](gv::proto::EdgeAttributePayload const& pl) -> hstd::SPtr<IAttribute> {
            auto edge  = hstd::validated_dynamic_cast<IEdge>(attr_object);
            auto group = get_vertex_attribute.operator()<gv::GraphGroup>(
                pl,
                "Parent ID cannot be set to empty, parent ID must be present in the "
                "attribute");

            auto edge_id = graph->getEdgeIDByStableId(edge->getStableId());

            // get the existing parent attribute object and assign edges to it.
            // the parent vertex attribute should already be created.
            return group->edge(
                *graph->getVertex(graph->getSource(edge_id))
                     ->getUniqueAttribute<gv::NodeAttribute>(),
                *graph->getVertex(graph->getTarget(edge_id))
                     ->getUniqueAttribute<gv::NodeAttribute>());
        },
        [&](kw::proto::KiwiEdgeVisualAttributePayload const& pl)
            -> hstd::SPtr<IAttribute> {
            auto edge = hstd::validated_dynamic_cast<IEdge>(attr_object);

            auto group = get_vertex_attribute.operator()<kw::KiwiGroup>(
                pl,
                "Parent ID cannot be set to empty, parent ID must be present in the "
                "attribute");

            return group->addEdge(graph->getEdgeIDByStableId(edge->getStableId()));
        },
    };

    return std::visit(overload, payload);
}


hstd::SPtr<hstd::ext::graph::IPortCollection> hstd::ext::graph::VisualFactory::
    newPortCollection(proto::IPortCollection const* in) {
    LOGIC_ASSERTION_CHECK_FMT(
        in->has_payload(),
        "De-serialization input does not have payload object {}",
        serde::getJString(*in));
    OP_TRACER_MESSAGE(this, "URL {}", in->payload().type_url());
    return std::visit(
        hstd::overloaded{
            [&](proto::TrivialPortCollectionPayload const& pl)
                -> hstd::SPtr<hstd::ext::graph::IPortCollection> {
                return std::make_shared<hstd::ext::graph::TrivialPortCollection>();
            },
        },
        hstd::serde::unpackVariantT<proto::TrivialPortCollectionPayload>(
            in->payload(),
            "port-collection",
            "Cannot read serial data for edge collection. "));
}

hstd::SPtr<hstd::ext::graph::IEdgeCollection> hstd::ext::graph::VisualFactory::
    newEdgeCollection(proto::IEdgeCollection const* in) {
    LOGIC_ASSERTION_CHECK_FMT(
        in->has_payload(),
        "No payload for edge collection '{}': {}",
        in->stable_id(),
        serde::getJString(*in));
    OP_TRACER_MESSAGE(this, "URL {}", in->payload().type_url());
    return std::visit(
        hstd::overloaded{
            [&](proto::TrivialEdgeCollectionPayload const& pl)
                -> hstd::SPtr<IEdgeCollection> {
                return std::make_shared<TrivialEdgeCollection>(
                    EdgeCollectionID{static_cast<hstd::u16>(in->collection_id())});
            },
        },
        hstd::serde::unpackVariantT<proto::TrivialEdgeCollectionPayload>(
            in->payload(),
            hstd::fmt("{}", in->collection_id()),
            "Cannot read serial data for edge collection. "));
}

hstd::SPtr<hstd::ext::graph::IVertexHierarchy> hstd::ext::graph::VisualFactory::
    newVertexHierarchy(proto::IVertexHierarchy const* in) {
    LOGIC_ASSERTION_CHECK_FMT(
        in->has_payload(),
        "No payload for vertex hierarchy '{}': {}",
        in->stable_id(),
        serde::getJString(*in));
    OP_TRACER_MESSAGE(this, "URL {}", in->payload().type_url());
    return std::visit(
        hstd::overloaded{
            [&](proto::TrivialVertexHierarchyPayload const& pl)
                -> hstd::SPtr<IVertexHierarchy> {
                return std::make_shared<TrivialHierarchy>();
            },
        },
        hstd::serde::unpackVariantT<proto::TrivialVertexHierarchyPayload>(
            in->payload(),
            in->stable_id(),
            "Cannot read serial data for vertex hierarchy. "));
}

hstd::SPtr<layout::IConstraint> hstd::ext::graph::VisualFactory::newConstraint(
    proto::IConstraint const* in) {
    LOGIC_ASSERTION_CHECK_FMT(
        in->has_payload(),
        "De-serialization input does not have payload object {}",
        serde::getJString(*in));
    OP_TRACER_MESSAGE(this, "URL {}", in->payload().type_url());
    namespace kp = kw::proto;
    return std::visit(
        hstd::overloaded{
            [&](kp::KiwiAlignConstraintPayload const& pl)
                -> hstd::SPtr<layout::IConstraint> {
                return std::make_shared<kw::AlignConstraint>(run);
            },
            [&](kp::KiwiSeparateConstraintPayload const& pl)
                -> hstd::SPtr<layout::IConstraint> {
                return std::make_shared<kw::SeparateConstraint>(run);
            },
            [&](kp::KiwiMultiSeparateConstraintPayload const& pl)
                -> hstd::SPtr<layout::IConstraint> {
                return std::make_shared<kw::MultiSeparateConstraint>(run);
            },
            [&](kp::KiwiLinearConstraintPayload const& pl)
                -> hstd::SPtr<layout::IConstraint> {
                return std::make_shared<kw::LinearConstraint>(run);
            },
            [&](kp::KiwiRelativeConstraintPayload const& pl)
                -> hstd::SPtr<layout::IConstraint> {
                return std::make_shared<kw::RelativeConstraint>(run);
            },
            [&](kp::KiwiEvenGapConstraintPayload const& pl)
                -> hstd::SPtr<layout::IConstraint> {
                return std::make_shared<kw::EvenGapConstraint>(run);
            },
        },
        hstd::serde::unpackVariant<ConstraintPayloadTypes>(
            in->payload(),
            "payload",
            "Cannot read serial data for constraint payload. "));
}

hstd::SPtr<hstd::ext::graph::IEdge> hstd::ext::graph::VisualFactory::newEdge(
    proto::IEdge const* edge) {
    LOGIC_ASSERTION_CHECK_FMT(
        edge->has_payload(),
        "De-serialization input does not have payload object {}",
        serde::getJString(*edge));

    return std::visit(
        hstd::overloaded{
            [&](proto::TrivialEdgePayload const& pl) -> hstd::SPtr<IEdge> {
                return std::make_shared<TrivialEdge>(edge->stable_id());
            },
        },
        hstd::serde::unpackVariantT<proto::TrivialEdgePayload>(
            edge->payload(),
            edge->stable_id(),
            "Cannot read serial data for the graph edge. "));
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


#    include "visual_factory.hpp"

#endif
