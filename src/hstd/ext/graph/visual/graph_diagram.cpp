#include "graph_diagram.hpp"
#include <hstd/ext/geometry/hstd_geometry_serde.hpp>
#include <hstd/ext/hstd_serde.hpp>
#include <hstd/ext/hstd_serde_dispatch.hpp>
#include <hstd/stdlib/VecFormatter.hpp>

#include <hstd/ext/graph/visual/visual_factory.hpp>

#pragma clang diagnostic error "-Wswitch"

namespace {

using namespace hstd::ext::graph;

enum struct LayoutKind
{
    Graphviz,
    Kiwi,
};

template <typename Message>
void appendAttribute(
    google::protobuf::RepeatedPtrField<proto::IAttribute>* attributes,
    Message const&                                         message) {
    proto::IAttribute* attribute  = attributes->Add();
    *attribute->mutable_payload() = hstd::serde::packMessage(message);
}

void appendConstraint(
    google::protobuf::RepeatedPtrField<proto::IConstraint>* constraints,
    diagram::proto::DiaConstraint const&                    source,
    std::string const&                                      clusterId) {
    proto::IConstraint* result = constraints->Add();

    switch (source.kind_case()) {
        case diagram::proto::DiaConstraint::kKwAlign:
            *result->mutable_payload() = hstd::serde::packMessage(source.kw_align());
            break;

        case diagram::proto::DiaConstraint::kKwSeparate:
            *result->mutable_payload() = hstd::serde::packMessage(source.kw_separate());
            break;

        case diagram::proto::DiaConstraint::kKwMultiSeparate:
            *result->mutable_payload() = hstd::serde::packMessage(
                source.kw_multi_separate());
            break;

        case diagram::proto::DiaConstraint::kKwRelative:
            *result->mutable_payload() = hstd::serde::packMessage(source.kw_relative());
            break;

        case diagram::proto::DiaConstraint::kKwLinear:
            *result->mutable_payload() = hstd::serde::packMessage(source.kw_linear());
            break;

        case diagram::proto::DiaConstraint::KIND_NOT_SET:
            throw std::invalid_argument{
                hstd::fmt("Constraint in cluster '{}' has no payload", clusterId)};
    }
}

void appendDiaConstraint(
    google::protobuf::RepeatedPtrField<diagram::proto::DiaConstraint>* constraints,
    proto::IConstraint const&                                          source,
    std::string const&                                                 clusterId) {
    diagram::proto::DiaConstraint* result  = constraints->Add();
    google::protobuf::Any const&   payload = source.payload();

    std::visit(
        hstd::overloaded{
            [&](kw::proto::KiwiAlignConstraintPayload const& pl) {
                *result->mutable_kw_align() = pl;
            },
            [&](kw::proto::KiwiSeparateConstraintPayload const& pl) {
                *result->mutable_kw_separate() = pl;
            },
            [&](kw::proto::KiwiMultiSeparateConstraintPayload const& pl) {
                *result->mutable_kw_multi_separate() = pl;
            },
            [&](kw::proto::KiwiRelativeConstraintPayload const& pl) {
                *result->mutable_kw_relative() = pl;
            },
            [&](kw::proto::KiwiLinearConstraintPayload const& pl) {
                *result->mutable_kw_linear() = pl;
            },
        },
        hstd::serde::unpackVariant<ConstraintPayloadTypes>(payload, clusterId));
}

diagram::proto::DiaCluster* findMutableCluster(
    diagram::proto::DiaCluster* cluster,
    std::string const&          id) {
    if (cluster->id() == id) { return cluster; }

    for (diagram::proto::DiaCluster& nested : *cluster->mutable_nested()) {
        if (diagram::proto::DiaCluster* result = findMutableCluster(&nested, id)) {
            return result;
        }
    }

    return nullptr;
}

std::optional<std::string> graphvizEdgeParent(proto::IEdge const& edge) {
    std::optional<gv::proto::EdgeAttributePayload>
        payload = hstd::serde::findOne<gv::proto::EdgeAttributePayload>(
            edge.attributes(), hstd::fmt("edge '{}'", edge.stable_id()));

    if (payload.has_value() && !payload->parent_stable_id().empty()) {
        return payload->parent_stable_id();
    }

    return std::nullopt;
}

std::string commonCluster(
    std::string const&                                  source,
    std::string const&                                  target,
    std::unordered_map<std::string, std::string> const& nodeParents,
    std::unordered_map<std::string, std::string> const& clusterParents,
    std::string const&                                  edgeId) {
    auto sourcePosition = nodeParents.find(source);
    auto targetPosition = nodeParents.find(target);

    if (sourcePosition == nodeParents.end()) {
        throw std::invalid_argument{hstd::fmt(
            "Edge '{}' references source vertex '{}' which is not a diagram node",
            edgeId,
            source)};
    }

    if (targetPosition == nodeParents.end()) {
        throw std::invalid_argument{hstd::fmt(
            "Edge '{}' references target vertex '{}' which is not a diagram node",
            edgeId,
            target)};
    }

    std::unordered_set<std::string> sourceAncestors{};
    std::string                     current = sourcePosition->second;

    while (true) {
        sourceAncestors.insert(current);
        auto parent = clusterParents.find(current);

        if (parent == clusterParents.end()) { break; }

        current = parent->second;
    }

    current = targetPosition->second;

    while (!sourceAncestors.contains(current)) {
        auto parent = clusterParents.find(current);

        if (parent == clusterParents.end()) {
            throw std::invalid_argument{hstd::fmt(
                "Edge '{}' connects vertices '{}' and '{}' from disconnected hierarchies",
                edgeId,
                source,
                target)};
        }

        current = parent->second;
    }

    return current;
}

} // namespace

namespace {

void appendNoAlgorithmCluster(
    diagram::proto::DiaCluster const& cluster,
    std::string const&                parentId,
    LayoutKind                        kind,
    proto::IVertex*                   vertex,
    diagram::proto::DiaGraphMetadata* metadata) {
    metadata->mutable_no_algorithm_cluster_ids()->insert({cluster.id(), true});

    switch (kind) {
        case LayoutKind::Graphviz: {
            if (!cluster.constraints().empty()) {
                throw std::invalid_argument{hstd::fmt(
                    "Graphviz-inheriting cluster '{}' cannot contain Kiwi "
                    "constraints",
                    cluster.id())};
            }

            gv::proto::GroupAttributePayload payload{};
            payload.set_parent_stable_id(parentId);

            if (cluster.has_outer_padding()) {
                *payload.mutable_base()->mutable_outer_padding() = cluster
                                                                       .outer_padding();
            }

            appendAttribute(vertex->mutable_attributes(), payload);
            break;
        }

        case LayoutKind::Kiwi: {
            kw::proto::KiwiGroupVisualAttributePayload payload{};
            payload.set_parent_stable_id(parentId);

            for (diagram::proto::DiaConstraint const& constraint :
                 cluster.constraints()) {
                appendConstraint(
                    payload.mutable_base()->mutable_constraints(),
                    constraint,
                    cluster.id());
            }

            if (cluster.has_outer_padding()) {
                *payload.mutable_base()->mutable_outer_padding() = cluster
                                                                       .outer_padding();
            }

            appendAttribute(vertex->mutable_attributes(), payload);
            break;
        }

        default: logic_todo_impl();
    }
}

void appendClusterKind(
    diagram::proto::DiaCluster const& cluster,
    std::optional<std::string> const& parentId,
    std::optional<LayoutKind>         parentKind,
    proto::IVertex*                   vertex,
    diagram::proto::DiaGraphMetadata* metadata,
    LayoutKind&                       kind,
    bool&                             inherited) {
    switch (cluster.kind_case()) {
        // TODO: Support ELK cluster conversions.
        case diagram::proto::DiaCluster::kGraphviz: {
            kind                                     = LayoutKind::Graphviz;
            gv::proto::GroupAttributePayload payload = cluster.graphviz();
            payload.clear_parent_stable_id();

            if (cluster.has_outer_padding()) {
                *payload.mutable_base()->mutable_outer_padding() = cluster
                                                                       .outer_padding();
            }

            appendAttribute(vertex->mutable_attributes(), payload);
            break;
        }

        case diagram::proto::DiaCluster::kKiwi: {
            kind                                               = LayoutKind::Kiwi;
            kw::proto::KiwiGroupVisualAttributePayload payload = cluster.kiwi();
            payload.clear_parent_stable_id();
            payload.mutable_base()->clear_constraints();
            if (cluster.has_outer_padding()) {
                *payload.mutable_base()->mutable_outer_padding() = cluster
                                                                       .outer_padding();
            }

            for (diagram::proto::DiaConstraint const& constraint :
                 cluster.constraints()) {
                appendConstraint(
                    payload.mutable_base()->mutable_constraints(),
                    constraint,
                    cluster.id());
            }

            appendAttribute(vertex->mutable_attributes(), payload);
            break;
        }

        case diagram::proto::DiaCluster::kElk: {
            logic_todo_impl();
        }

        case diagram::proto::DiaCluster::kNoAlgorithm: {
            if (!parentId.has_value() || !parentKind.has_value()) {
                throw std::invalid_argument{hstd::fmt(
                    "Root cluster '{}' must specify a layout algorithm", cluster.id())};
            }

            inherited = true;
            kind      = *parentKind;

            appendNoAlgorithmCluster(cluster, *parentId, kind, vertex, metadata);
            break;
        }

        case diagram::proto::DiaCluster::KIND_NOT_SET:
            break; // guaranteed by protovalidate
    }
}

void appendClusterNode(
    diagram::proto::DiaNode const&    node,
    diagram::proto::DiaCluster const& cluster,
    LayoutKind                        kind,
    proto::IGraph*                    graph,
    proto::VertexIDVec*               nestedIds,
    std::unordered_set<std::string>*  vertexIds) {
    if (!vertexIds->insert(node.id()).second) {
        throw std::invalid_argument{
            hstd::fmt("Diagram contains duplicate vertex ID '{}'", node.id())};
    }

    nestedIds->add_vertices(node.id());

    proto::IVertex* nodeVertex = graph->add_vertices();
    nodeVertex->set_stable_id(node.id());
    *nodeVertex->mutable_payload() = hstd::serde::packMessage(
        proto::TrivialVertexPayload{});

    switch (kind) {
        case LayoutKind::Graphviz: {
            gv::proto::NodeAttributePayload payload = node.graphviz();
            payload.set_parent_stable_id(cluster.id());
            appendAttribute(nodeVertex->mutable_attributes(), payload);
            break;
        }

        case LayoutKind::Kiwi: {
            kw::proto::KiwiVertexVisualAttributePayload payload = node.kiwi();
            payload.set_parent_stable_id(cluster.id());
            appendAttribute(nodeVertex->mutable_attributes(), payload);
            break;
        }
    }
}

void appendClusterEdge(
    diagram::proto::DiaEdge const&         edge,
    diagram::proto::DiaCluster const&      cluster,
    LayoutKind                             kind,
    proto::IEdgeCollection*                collection,
    diagram::proto::DiaGraphMetadata*      metadata,
    std::unordered_set<std::string> const& vertexIds,
    std::unordered_set<std::string>*       edgeIds) {
    if (!edgeIds->insert(edge.id()).second) {
        throw std::invalid_argument{
            hstd::fmt("Diagram contains duplicate edge ID '{}'", edge.id())};
    }

    if (!vertexIds.contains(edge.source())) {
        throw std::invalid_argument{hstd::fmt(
            "Edge '{}' references source vertex '{}' before it is defined",
            edge.id(),
            edge.source())};
    }

    if (!vertexIds.contains(edge.target())) {
        throw std::invalid_argument{hstd::fmt(
            "Edge '{}' references target vertex '{}' before it is defined",
            edge.id(),
            edge.target())};
    }

    metadata->mutable_edge_parent_cluster_ids()->insert({edge.id(), cluster.id()});

    proto::IEdge* graphEdge = collection->add_edges();
    graphEdge->set_stable_id(edge.id());
    graphEdge->set_source_vertex_id(edge.source());
    graphEdge->set_target_vertex_id(edge.target());
    *graphEdge->mutable_payload() = hstd::serde::packMessage(proto::TrivialEdgePayload{});

    switch (kind) {
        case LayoutKind::Graphviz: {
            gv::proto::EdgeAttributePayload payload = edge.graphviz();
            payload.set_parent_stable_id(cluster.id());
            appendAttribute(graphEdge->mutable_attributes(), payload);
            break;
        }

        case LayoutKind::Kiwi: {
            kw::proto::KiwiEdgeVisualAttributePayload payload = edge.kiwi();
            payload.set_parent_stable_id(cluster.id());
            appendAttribute(graphEdge->mutable_attributes(), payload);
            break;
        }
    }
}

void appendCluster(
    diagram::proto::DiaCluster const& cluster,
    std::optional<std::string> const& parentId,
    std::optional<LayoutKind>         parentKind,
    proto::IGraph*                    graph,
    proto::IEdgeCollection*           collection,
    proto::IVertexHierarchy*          hierarchy,
    diagram::proto::DiaGraphMetadata* metadata,
    std::unordered_set<std::string>*  vertexIds,
    std::unordered_set<std::string>*  edgeIds) {
    if (!vertexIds->insert(cluster.id()).second) {
        throw std::invalid_argument{
            hstd::fmt("Diagram contains duplicate vertex ID '{}'", cluster.id())};
    }

    LayoutKind      kind{};
    bool            inherited = false;
    proto::IVertex* vertex    = graph->add_vertices();
    vertex->set_stable_id(cluster.id());
    *vertex->mutable_payload() = hstd::serde::packMessage(proto::TrivialVertexPayload{});

    appendClusterKind(cluster, parentId, parentKind, vertex, metadata, kind, inherited);

    proto::VertexIDVec nestedIds{};

    for (diagram::proto::DiaNode const& node : cluster.nodes()) {
        appendClusterNode(node, cluster, kind, graph, &nestedIds, vertexIds);
    }

    // edges: same — kind mismatch and empty-ID checks removed, endpoint
    // reference and duplicate-ID checks kept.
    for (diagram::proto::DiaEdge const& edge : cluster.edges()) {
        appendClusterEdge(edge, cluster, kind, collection, metadata, *vertexIds, edgeIds);
    }

    for (diagram::proto::DiaCluster const& nested : cluster.nested()) {
        nestedIds.add_vertices(nested.id());
    }

    hierarchy->mutable_nested_in_map()->insert({cluster.id(), nestedIds});

    for (auto const& aux_edge : nestedIds.vertices()) {
        auto edge = hierarchy->add_edges();
        edge->set_source_vertex_id(cluster.id());
        edge->set_target_vertex_id(aux_edge);
        edge->set_stable_id(hstd::fmt("__nesting_cluster_{}_{}", cluster.id(), aux_edge));
        *edge->mutable_payload() = hstd::serde::packMessage(proto::TrivialEdgePayload{});
    }

    for (diagram::proto::DiaCluster const& nested : cluster.nested()) {
        appendCluster(
            nested,
            cluster.id(),
            inherited ? parentKind : std::optional<LayoutKind>{kind},
            graph,
            collection,
            hierarchy,
            metadata,
            vertexIds,
            edgeIds);
    }
}

diagram::proto::DiaCluster buildCluster(
    std::string const&                                     clusterId,
    proto::IVertexHierarchy const&                         hierarchy,
    diagram::proto::DiaGraphMetadata const&                metadata,
    std::unordered_map<std::string, IVertex const*> const& vertices,
    std::unordered_set<std::string> const&                 clusterIds,
    std::unordered_set<std::string>*                       visited,
    bool                                                   preserveOrigin);


void appendNestedVertex(
    diagram::proto::DiaCluster*                                   result,
    std::string const&                                            nestedId,
    std::unordered_map<std::string, proto::IVertex const*> const& vertices,
    bool                                                          preserveOrigin) {


    proto::IVertex const&    nodeVertex = *vertices.at(nestedId);
    diagram::proto::DiaNode* node       = result->add_nodes();
    node->set_id(nestedId);

    std::string owner = hstd::fmt("node '{}'", nestedId);

    auto visual = hstd::serde::findUniqueRequired<NodeVisualAttributePayloadTypes>(
        nodeVertex.attributes(), owner);

    std::visit(
        hstd::overloaded{
            [&](gv::proto::NodeAttributePayload const& pl) {
                if (preserveOrigin) { *node->mutable_graphviz() = pl; }
                *node->mutable_bbox() = //
                    hstd::serde::findOneRequired<
                        hstd::ext::graph::layout::proto::IVertexLayoutAttributePayload>(
                        nodeVertex.attributes(), owner)
                        .bbox();
            },
            [&](kw::proto::KiwiVertexVisualAttributePayload const& pl) {
                if (preserveOrigin) { *node->mutable_kiwi() = pl; }
                *node->mutable_bbox() = //
                    hstd::serde::findOneRequired<
                        hstd::ext::graph::kw::proto::KiwiVertexLayoutAttributePayload>(
                        nodeVertex.attributes(), owner)
                        .base()
                        .bbox();
            },
        },
        visual);
}

diagram::proto::DiaCluster buildCluster(
    std::string const&                                            clusterId,
    hstd::ext::graph::proto::IVertexHierarchy const&              hierarchy,
    diagram::proto::DiaGraphMetadata const&                       metadata,
    std::unordered_map<std::string, proto::IVertex const*> const& vertices,
    std::unordered_set<std::string> const&                        clusterIds,
    std::unordered_set<std::string>*                              visited,
    bool                                                          preserveOrigin) {
    if (!vertices.contains(clusterId)) {
        throw std::invalid_argument{
            hstd::fmt("Hierarchy references missing cluster vertex '{}'", clusterId)};
    }

    if (!visited->insert(clusterId).second) {
        throw std::invalid_argument{hstd::fmt(
            "Hierarchy contains a cycle or repeated cluster reference at '{}'",
            clusterId)};
    }

    proto::IVertex const&      vertex = *vertices.at(clusterId);
    diagram::proto::DiaCluster result{};
    result.set_id(clusterId);

    std::string owner = hstd::fmt("cluster '{}'", clusterId);

    auto visual = hstd::serde::findUnique<GroupVisualAttributePayloadTypes>(
        vertex.attributes(), owner);

    bool noAlgorithm = metadata.no_algorithm_cluster_ids().find(clusterId)
                    != metadata.no_algorithm_cluster_ids().end();

    if (!noAlgorithm && visual.has_value()) {
        if (auto const* graphviz = std::get_if<gv::proto::GroupAttributePayload>(
                &*visual)) {
            if (graphviz->layout_case()
                    == gv::proto::GroupAttributePayload::LAYOUT_NOT_SET
                && !graphviz->parent_stable_id().empty()) {
                noAlgorithm = true;
            }
        }
    }

    if (noAlgorithm || !visual.has_value()) {
        result.set_no_algorithm(google::protobuf::NULL_VALUE);
    } else {
        auto overload = hstd::overloaded{
            [&](gv::proto::GroupAttributePayload const& pl) {
                if (preserveOrigin) { *result.mutable_graphviz() = pl; }
                *result.mutable_bbox() = //
                    hstd::serde::findOneRequired<
                        hstd::ext::graph::layout::proto::IGroupLayoutAttributePayload>(
                        vertex.attributes(), owner)
                        .bbox();
            },
            [&](kw::proto::KiwiGroupVisualAttributePayload const& pl) {
                if (preserveOrigin) { *result.mutable_kiwi() = pl; }
                *result.mutable_bbox() = //
                    hstd::serde::findOneRequired<
                        hstd::ext::graph::kw::proto::KiwiGroupLayoutAttributePayload>(
                        vertex.attributes(), owner)
                        .base()
                        .bbox();

                result.mutable_kiwi()->mutable_base()->clear_constraints();

                if (preserveOrigin) {
                    for (proto::IConstraint const& constraint : pl.base().constraints()) {
                        appendDiaConstraint(
                            result.mutable_constraints(), constraint, clusterId);
                    }
                }
            },
        };
        std::visit(overload, *visual);
    }


    auto nestedPosition = hierarchy.nested_in_map().find(clusterId);

    if (nestedPosition != hierarchy.nested_in_map().end()) {
        for (std::string const& nestedId : nestedPosition->second.vertices()) {
            if (clusterIds.contains(nestedId)) {
                *result.add_nested() = buildCluster(
                    nestedId,
                    hierarchy,
                    metadata,
                    vertices,
                    clusterIds,
                    visited,
                    preserveOrigin);
                continue;
            }

            appendNestedVertex(&result, nestedId, vertices, preserveOrigin);
        }
    }

    return result;
}

void appendDiaEdge(
    diagram::proto::DiaCluster*                         result,
    proto::IEdge const&                                 source,
    diagram::proto::DiaGraphMetadata const&             metadata,
    std::unordered_map<std::string, std::string> const& nodeParents,
    std::unordered_map<std::string, std::string> const& clusterParents,
    bool                                                preserveOrigin) {
    std::string parentId{};

    auto metadataParent = metadata.edge_parent_cluster_ids().find(source.stable_id());

    if (metadataParent != metadata.edge_parent_cluster_ids().end()) {
        parentId = metadataParent->second;
    } else if (std::optional<std::string> graphvizParent = graphvizEdgeParent(source)) {
        parentId = *graphvizParent;
    } else {
        parentId = commonCluster(
            source.source_vertex_id(),
            source.target_vertex_id(),
            nodeParents,
            clusterParents,
            source.stable_id());
    }

    diagram::proto::DiaCluster* parent = findMutableCluster(result, parentId);

    if (parent == nullptr) {
        throw std::invalid_argument{hstd::fmt(
            "Edge '{}' references missing parent cluster '{}'",
            source.stable_id(),
            parentId)};
    }

    diagram::proto::DiaEdge* edge = parent->add_edges();
    edge->set_id(source.stable_id());
    edge->set_source(source.source_vertex_id());
    edge->set_target(source.target_vertex_id());

    std::string owner = hstd::fmt("edge '{}'", source.stable_id());


    if (preserveOrigin) {
        auto visual = hstd::serde::findUnique<EdgeVisualAttributePayloadTypes>(
            source.attributes(), owner);
        if (visual) {
            std::visit(
                hstd::overloaded{
                    [&](gv::proto::EdgeAttributePayload const& pl) {
                        *edge->mutable_graphviz() = pl;
                    },
                    [&](kw::proto::KiwiEdgeVisualAttributePayload const& pl) {
                        *edge->mutable_kiwi() = pl;
                    },
                },
                *visual);
        }
    }

    auto layout = hstd::serde::findUniqueRequired<
        hstd::ext::graph::EdgeLayoutAttributePayloadTypes>(source.attributes(), owner);

    std::visit(
        hstd::overloaded{
            [&](avoid::proto::EdgeLayoutAttributePayload const& pl) {
                *edge->mutable_path() = pl.base().path();
            },
            [&](layout::proto::IEdgeLayoutAttributePayload const& pl) {
                *edge->mutable_path() = pl.path();
            },
        },
        layout);
}

} // namespace

hstd::ext::graph::proto::IGraph hstd::ext::graph::diagram::diaClusterToGraph(
    hstd::ext::graph::diagram::proto::DiaCluster const& root) {
    hstd::serde::protovalidate_message(root);

    LOGIC_ASSERTION_CHECK_FMT(
        !root.has_no_algorithm() && root.kind_case() != proto::DiaCluster::KIND_NOT_SET,
        "Root cluster must specify the layout algorith, {} has no algorithm",
        root.id());

    graph::proto::IGraph             graph{};
    diagram::proto::DiaGraphMetadata metadata{};
    std::unordered_set<std::string>  vertexIds{};
    std::unordered_set<std::string>  edgeIds{};

    auto* collection = graph.add_collections();
    collection->set_stable_id("diagram-edges");
    collection->set_collection_id(0);
    *collection->mutable_payload() = hstd::serde::packMessage(
        graph::proto::TrivialEdgeCollectionPayload{});

    auto* hierarchy = graph.add_hierarchies();
    hierarchy->set_stable_id("diagram-hierarchy");
    *hierarchy->mutable_payload() = hstd::serde::packMessage(
        graph::proto::TrivialVertexHierarchyPayload{});

    auto* ports               = graph.add_ports();
    *ports->mutable_payload() = hstd::serde::packMessage(
        graph::proto::TrivialPortCollectionPayload{});


    appendCluster(
        root,
        std::nullopt,
        std::nullopt,
        &graph,
        collection,
        hierarchy,
        &metadata,
        &vertexIds,
        &edgeIds);

    *graph.mutable_payload() = hstd::serde::packMessage(metadata);
    return graph;
}

hstd::ext::graph::diagram::proto::DiaCluster hstd::ext::graph::diagram::graphToDiaCluster(
    hstd::ext::graph::proto::IGraph const& graph,
    bool                                   preserveOrigin) {
    if (graph.hierarchies_size() != 1) {
        throw std::invalid_argument{hstd::fmt(
            "Diagram conversion requires exactly one vertex hierarchy, but the graph "
            "contains {}",
            graph.hierarchies_size())};
    }

    graph::proto::IVertexHierarchy const& hierarchy = graph.hierarchies(0);

    if (hierarchy.root_vertex_ids_size() != 1) {
        throw std::invalid_argument{hstd::fmt(
            "Diagram conversion requires exactly one root vertex, but hierarchy '{}' "
            "contains {}",
            hierarchy.stable_id(),
            hierarchy.root_vertex_ids_size())};
    }

    diagram::proto::DiaGraphMetadata metadata{};

    if (graph.payload().Is<diagram::proto::DiaGraphMetadata>()) {
        metadata = hstd::serde::unpackMessage<diagram::proto::DiaGraphMetadata>(
            graph.payload(), "graph");
    }

    std::unordered_map<std::string, graph::proto::IVertex const*> vertices{};
    std::unordered_map<std::string, graph::proto::IEdge const*>   edges{};

    for (graph::proto::IVertex const& vertex : graph.vertices()) {
        if (vertex.stable_id().empty()) {
            throw std::invalid_argument{
                "Graph contains a vertex with an empty stable ID"};
        }

        if (vertices.contains(vertex.stable_id())) {
            throw std::invalid_argument{
                hstd::fmt("Graph contains duplicate vertex ID '{}'", vertex.stable_id())};
        }

        vertices.insert_or_assign(vertex.stable_id(), &vertex);
    }

    for (auto const& collection : graph.collections()) {
        for (graph::proto::IEdge const& edge : collection.edges()) {
            if (edge.stable_id().empty()) {
                throw std::invalid_argument{hstd::fmt(
                    "Edge collection '{}' contains an edge with an empty stable ID",
                    collection.stable_id())};
            }

            if (edges.contains(edge.stable_id())) {
                throw std::invalid_argument{
                    hstd::fmt("Graph contains duplicate edge ID '{}'", edge.stable_id())};
            }

            edges.insert_or_assign(edge.stable_id(), &edge);
        }
    }

    std::unordered_set<std::string>              clusterIds{};
    std::unordered_map<std::string, std::string> clusterParents{};
    std::unordered_map<std::string, std::string> nodeParents{};

    clusterIds.insert(hierarchy.root_vertex_ids(0));

    for (auto const& entry : hierarchy.nested_in_map()) {
        clusterIds.insert(entry.first);
    }

    for (graph::proto::IVertex const& vertex : graph.vertices()) {
        auto visual = hstd::serde::findUnique<GroupVisualAttributePayloadTypes>(
            vertex.attributes(), hstd::fmt("vertex '{}'", vertex.stable_id()));

        if (visual) {
            std::visit(
                hstd::overloaded{
                    [&](gv::proto::GroupAttributePayload const& pl) {
                        clusterIds.insert(vertex.stable_id());
                    },
                    [&](kw::proto::KiwiGroupVisualAttributePayload const& pl) {
                        clusterIds.insert(vertex.stable_id());
                    },
                },
                *visual);
        }
    }

    for (auto const& entry : hierarchy.nested_in_map()) {
        std::string const& parentId = entry.first;

        if (!vertices.contains(parentId)) {
            throw std::invalid_argument{hstd::fmt(
                "Hierarchy '{}' references missing cluster vertex '{}'",
                hierarchy.stable_id(),
                parentId)};
        }

        for (std::string const& nestedId : entry.second.vertices()) {
            if (!vertices.contains(nestedId)) {
                throw std::invalid_argument{hstd::fmt(
                    "Cluster '{}' references missing nested vertex '{}'",
                    parentId,
                    nestedId)};
            }

            if (clusterIds.contains(nestedId)) {
                if (clusterParents.contains(nestedId)) {
                    throw std::invalid_argument{hstd::fmt(
                        "Cluster '{}' is nested in both '{}' and '{}'",
                        nestedId,
                        clusterParents.at(nestedId),
                        parentId)};
                }

                clusterParents.insert_or_assign(nestedId, parentId);
            } else {
                if (nodeParents.contains(nestedId)) {
                    throw std::invalid_argument{hstd::fmt(
                        "Node '{}' is nested in both '{}' and '{}'",
                        nestedId,
                        nodeParents.at(nestedId),
                        parentId)};
                }

                nodeParents.insert_or_assign(nestedId, parentId);
            }
        }
    }

    std::unordered_set<std::string> visited{};

    diagram::proto::DiaCluster result = buildCluster(
        hierarchy.root_vertex_ids(0),
        hierarchy,
        metadata,
        vertices,
        clusterIds,
        &visited,
        preserveOrigin);

    for (auto const& entry : vertices) {
        if (!visited.contains(entry.first) && !nodeParents.contains(entry.first)) {
            throw std::invalid_argument{hstd::fmt(
                "Vertex '{}' is not reachable from root cluster '{}'",
                entry.first,
                result.id())};
        }
    }

    for (auto const& entry : edges) {
        appendDiaEdge(
            &result,
            *entry.second,
            metadata,
            nodeParents,
            clusterParents,
            preserveOrigin);
    }

    return result;
}
