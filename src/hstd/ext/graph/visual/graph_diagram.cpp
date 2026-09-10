#include "graph_diagram.hpp"
#include <hstd/ext/geometry/hstd_geometry_serde.hpp>
#include <hstd/ext/hstd_serde.hpp>
#include <hstd/stdlib/VecFormatter.hpp>

namespace {

using namespace hstd::ext::graph::diagram::proto;
using namespace hstd::ext::graph::gv::proto;
using namespace hstd::ext::graph::kw::proto;
using namespace hstd::ext::graph::proto;

enum struct LayoutKind
{
    Graphviz,
    Kiwi,
};

template <typename Message>
std::optional<Message> findAttribute(
    google::protobuf::RepeatedPtrField<IAttribute> const& attributes,
    std::string const&                                    owner) {
    std::optional<Message> result{};

    for (IAttribute const& attribute : attributes) {
        if (attribute.payload().Is<Message>()) {
            if (result.has_value()) {
                throw std::invalid_argument{fmt::format(
                    "'{}' contains multiple '{}' attributes",
                    owner,
                    Message::descriptor()->full_name())};
            }

            result = hstd::serde::unpackMessage<Message>(attribute.payload(), owner);
        }
    }

    return result;
}

template <typename Message, typename Value>
Message findRequiredAttribute(Value const& value, std::string const& owner) {
    auto result = findAttribute<Message>(value.attributes(), owner);
    if (result) {
        return result.value();
    } else {
        hstd::Vec<hstd::Str> types;
        for (IAttribute const& attribute : value.attributes()) {
            types.push_back(attribute.payload().type_url());
        }

        throw hstd::serde::read_error::init(
            hstd::fmt(
                "Could not find required attribute of type '{}' in {}. Has attributes {}",
                Message::descriptor()->full_name(),
                owner,
                types));
    }
}

template <typename Message>
void appendAttribute(
    google::protobuf::RepeatedPtrField<IAttribute>* attributes,
    Message const&                                  message) {
    IAttribute* attribute         = attributes->Add();
    *attribute->mutable_payload() = hstd::serde::packMessage(message);
}

void appendConstraint(
    google::protobuf::RepeatedPtrField<IConstraint>* constraints,
    DiaConstraint const&                             source,
    std::string const&                               clusterId) {
    IConstraint* result = constraints->Add();

    switch (source.kind_case()) {
        case DiaConstraint::kKwAlign:
            *result->mutable_payload() = hstd::serde::packMessage(source.kw_align());
            break;

        case DiaConstraint::kKwSeparate:
            *result->mutable_payload() = hstd::serde::packMessage(source.kw_separate());
            break;

        case DiaConstraint::kKwMultiSeparate:
            *result->mutable_payload() = hstd::serde::packMessage(
                source.kw_multi_separate());
            break;

        case DiaConstraint::kKwRelative:
            *result->mutable_payload() = hstd::serde::packMessage(source.kw_relative());
            break;

        case DiaConstraint::kKwLinear:
            *result->mutable_payload() = hstd::serde::packMessage(source.kw_linear());
            break;

        case DiaConstraint::KIND_NOT_SET:
            throw std::invalid_argument{
                hstd::fmt("Constraint in cluster '{}' has no payload", clusterId)};
    }
}

void appendDiaConstraint(
    google::protobuf::RepeatedPtrField<DiaConstraint>* constraints,
    IConstraint const&                                 source,
    std::string const&                                 clusterId) {
    DiaConstraint*               result  = constraints->Add();
    google::protobuf::Any const& payload = source.payload();

    if (payload.Is<KiwiAlignConstraintPayload>()) {
        *result->mutable_kw_align() = hstd::serde::unpackMessage<
            KiwiAlignConstraintPayload>(payload, clusterId);
    } else if (payload.Is<KiwiSeparateConstraintPayload>()) {
        *result->mutable_kw_separate() = hstd::serde::unpackMessage<
            KiwiSeparateConstraintPayload>(payload, clusterId);
    } else if (payload.Is<KiwiMultiSeparateConstraintPayload>()) {
        *result->mutable_kw_multi_separate() = hstd::serde::unpackMessage<
            KiwiMultiSeparateConstraintPayload>(payload, clusterId);
    } else if (payload.Is<KiwiRelativeConstraintPayload>()) {
        *result->mutable_kw_relative() = hstd::serde::unpackMessage<
            KiwiRelativeConstraintPayload>(payload, clusterId);
    } else if (payload.Is<KiwiLinearConstraintPayload>()) {
        *result->mutable_kw_linear() = hstd::serde::unpackMessage<
            KiwiLinearConstraintPayload>(payload, clusterId);
    } else {
        throw std::invalid_argument{hstd::fmt(
            "Cluster '{}' contains unsupported constraint payload '{}'",
            clusterId,
            payload.type_url())};
    }
}

DiaCluster* findMutableCluster(DiaCluster* cluster, std::string const& id) {
    if (cluster->id() == id) { return cluster; }

    for (DiaCluster& nested : *cluster->mutable_nested()) {
        if (DiaCluster* result = findMutableCluster(&nested, id)) { return result; }
    }

    return nullptr;
}

std::optional<std::string> graphvizEdgeParent(IEdge const& edge) {
    std::optional<EdgeAttributePayload> payload = findAttribute<EdgeAttributePayload>(
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
    DiaCluster const&  cluster,
    std::string const& parentId,
    LayoutKind         kind,
    IVertex*           vertex,
    DiaGraphMetadata*  metadata) {
    metadata->mutable_no_algorithm_cluster_ids()->insert({cluster.id(), true});

    switch (kind) {
        case LayoutKind::Graphviz: {
            if (!cluster.constraints().empty()) {
                throw std::invalid_argument{hstd::fmt(
                    "Graphviz-inheriting cluster '{}' cannot contain Kiwi "
                    "constraints",
                    cluster.id())};
            }

            GroupAttributePayload payload{};
            payload.set_parent_stable_id(parentId);
            appendAttribute(vertex->mutable_attributes(), payload);
            break;
        }

        case LayoutKind::Kiwi: {
            KiwiGroupVisualAttributePayload payload{};
            payload.set_parent_stable_id(parentId);

            for (DiaConstraint const& constraint : cluster.constraints()) {
                appendConstraint(
                    payload.mutable_base()->mutable_constraints(),
                    constraint,
                    cluster.id());
            }

            appendAttribute(vertex->mutable_attributes(), payload);
            break;
        }
    }
}

void appendClusterKind(
    DiaCluster const&                 cluster,
    std::optional<std::string> const& parentId,
    std::optional<LayoutKind>         parentKind,
    IVertex*                          vertex,
    DiaGraphMetadata*                 metadata,
    LayoutKind&                       kind,
    bool&                             inherited) {
    switch (cluster.kind_case()) {
        case DiaCluster::kGraphviz: {
            kind                          = LayoutKind::Graphviz;
            GroupAttributePayload payload = cluster.graphviz();
            payload.clear_parent_stable_id();
            appendAttribute(vertex->mutable_attributes(), payload);
            break;
        }

        case DiaCluster::kKiwi: {
            kind                                    = LayoutKind::Kiwi;
            KiwiGroupVisualAttributePayload payload = cluster.kiwi();
            payload.clear_parent_stable_id();
            payload.mutable_base()->clear_constraints();

            for (DiaConstraint const& constraint : cluster.constraints()) {
                appendConstraint(
                    payload.mutable_base()->mutable_constraints(),
                    constraint,
                    cluster.id());
            }

            appendAttribute(vertex->mutable_attributes(), payload);
            break;
        }

        case DiaCluster::kNoAlgorithm: {
            if (!parentId.has_value() || !parentKind.has_value()) {
                throw std::invalid_argument{hstd::fmt(
                    "Root cluster '{}' must specify a layout algorithm", cluster.id())};
            }

            inherited = true;
            kind      = *parentKind;

            appendNoAlgorithmCluster(cluster, *parentId, kind, vertex, metadata);
            break;
        }

        case DiaCluster::KIND_NOT_SET: break; // guaranteed by protovalidate
    }
}

void appendClusterNode(
    DiaNode const&                   node,
    DiaCluster const&                cluster,
    LayoutKind                       kind,
    IGraph*                          graph,
    VertexIDVec*                     nestedIds,
    std::unordered_set<std::string>* vertexIds) {
    if (!vertexIds->insert(node.id()).second) {
        throw std::invalid_argument{
            hstd::fmt("Diagram contains duplicate vertex ID '{}'", node.id())};
    }

    nestedIds->add_vertices(node.id());

    IVertex* nodeVertex = graph->add_vertices();
    nodeVertex->set_stable_id(node.id());
    *nodeVertex->mutable_payload() = hstd::serde::packMessage(TrivialVertexPayload{});

    switch (kind) {
        case LayoutKind::Graphviz: {
            NodeAttributePayload payload = node.graphviz();
            payload.set_parent_stable_id(cluster.id());
            appendAttribute(nodeVertex->mutable_attributes(), payload);
            break;
        }

        case LayoutKind::Kiwi: {
            KiwiVertexVisualAttributePayload payload = node.kiwi();
            payload.set_parent_stable_id(cluster.id());
            appendAttribute(nodeVertex->mutable_attributes(), payload);
            break;
        }
    }
}

void appendClusterEdge(
    DiaEdge const&                         edge,
    DiaCluster const&                      cluster,
    LayoutKind                             kind,
    IEdgeCollection*                       collection,
    DiaGraphMetadata*                      metadata,
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

    IEdge* graphEdge = collection->add_edges();
    graphEdge->set_stable_id(edge.id());
    graphEdge->set_source_vertex_id(edge.source());
    graphEdge->set_target_vertex_id(edge.target());
    *graphEdge->mutable_payload() = hstd::serde::packMessage(TrivialEdgePayload{});

    switch (kind) {
        case LayoutKind::Graphviz: {
            EdgeAttributePayload payload = edge.graphviz();
            payload.set_parent_stable_id(cluster.id());
            appendAttribute(graphEdge->mutable_attributes(), payload);
            break;
        }

        case LayoutKind::Kiwi: {
            appendAttribute(graphEdge->mutable_attributes(), edge.kiwi());
            break;
        }
    }
}

void appendCluster(
    DiaCluster const&                 cluster,
    std::optional<std::string> const& parentId,
    std::optional<LayoutKind>         parentKind,
    IGraph*                           graph,
    IEdgeCollection*                  collection,
    IVertexHierarchy*                 hierarchy,
    DiaGraphMetadata*                 metadata,
    std::unordered_set<std::string>*  vertexIds,
    std::unordered_set<std::string>*  edgeIds) {
    if (!vertexIds->insert(cluster.id()).second) {
        throw std::invalid_argument{
            hstd::fmt("Diagram contains duplicate vertex ID '{}'", cluster.id())};
    }

    LayoutKind kind{};
    bool       inherited = false;
    IVertex*   vertex    = graph->add_vertices();
    vertex->set_stable_id(cluster.id());
    *vertex->mutable_payload() = hstd::serde::packMessage(TrivialVertexPayload{});

    appendClusterKind(cluster, parentId, parentKind, vertex, metadata, kind, inherited);

    VertexIDVec nestedIds{};

    for (DiaNode const& node : cluster.nodes()) {
        appendClusterNode(node, cluster, kind, graph, &nestedIds, vertexIds);
    }

    // edges: same — kind mismatch and empty-ID checks removed, endpoint
    // reference and duplicate-ID checks kept.
    for (DiaEdge const& edge : cluster.edges()) {
        appendClusterEdge(edge, cluster, kind, collection, metadata, *vertexIds, edgeIds);
    }

    for (DiaCluster const& nested : cluster.nested()) {
        nestedIds.add_vertices(nested.id());
    }

    hierarchy->mutable_nested_in_map()->insert({cluster.id(), nestedIds});

    for (auto const& aux_edge : nestedIds.vertices()) {
        auto edge = hierarchy->add_edges();
        edge->set_source_vertex_id(cluster.id());
        edge->set_target_vertex_id(aux_edge);
        edge->set_stable_id(hstd::fmt("__nesting_cluster_{}_{}", cluster.id(), aux_edge));
        *edge->mutable_payload() = hstd::serde::packMessage(TrivialEdgePayload{});
    }

    for (DiaCluster const& nested : cluster.nested()) {
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

DiaCluster buildCluster(
    std::string const&                                     clusterId,
    IVertexHierarchy const&                                hierarchy,
    DiaGraphMetadata const&                                metadata,
    std::unordered_map<std::string, IVertex const*> const& vertices,
    std::unordered_set<std::string> const&                 clusterIds,
    std::unordered_set<std::string>*                       visited,
    bool                                                   preserveOrigin);


void appendNestedVertex(
    DiaCluster*                                            result,
    std::string const&                                     nestedId,
    std::unordered_map<std::string, IVertex const*> const& vertices,
    bool                                                   preserveOrigin) {


    IVertex const& nodeVertex = *vertices.at(nestedId);
    DiaNode*       node       = result->add_nodes();
    node->set_id(nestedId);

    std::string owner = hstd::fmt("node '{}'", nestedId);

    std::optional<NodeAttributePayload>
        graphvizNode = findAttribute<NodeAttributePayload>(
            nodeVertex.attributes(), owner);
    std::optional<KiwiVertexVisualAttributePayload>
        kiwiNode = findAttribute<KiwiVertexVisualAttributePayload>(
            nodeVertex.attributes(), owner);

    if (graphvizNode.has_value() && kiwiNode.has_value()) {
        throw std::invalid_argument{
            hstd::fmt("Node '{}' contains both Graphviz and Kiwi attributes", nestedId)};
    }

    if (graphvizNode.has_value()) {
        if (preserveOrigin) { *node->mutable_graphviz() = *graphvizNode; }
        auto l = findRequiredAttribute<
            hstd::ext::graph::layout::proto::IVertexLayoutAttributePayload>(
            nodeVertex, owner);

        *node->mutable_bbox() = l.bbox();
    } else if (kiwiNode.has_value()) {
        if (preserveOrigin) { *node->mutable_kiwi() = *kiwiNode; }
        *node->mutable_bbox() = //
            findRequiredAttribute<
                hstd::ext::graph::kw::proto::KiwiVertexLayoutAttributePayload>(
                nodeVertex, owner)
                .base()
                .bbox();
    } else {
        throw std::invalid_argument{hstd::fmt(
            "Node '{}' contains neither a Graphviz nor a Kiwi attribute", nestedId)};
    }
}

DiaCluster buildCluster(
    std::string const&                                     clusterId,
    IVertexHierarchy const&                                hierarchy,
    DiaGraphMetadata const&                                metadata,
    std::unordered_map<std::string, IVertex const*> const& vertices,
    std::unordered_set<std::string> const&                 clusterIds,
    std::unordered_set<std::string>*                       visited,
    bool                                                   preserveOrigin) {
    if (!vertices.contains(clusterId)) {
        throw std::invalid_argument{
            hstd::fmt("Hierarchy references missing cluster vertex '{}'", clusterId)};
    }

    if (!visited->insert(clusterId).second) {
        throw std::invalid_argument{hstd::fmt(
            "Hierarchy contains a cycle or repeated cluster reference at '{}'",
            clusterId)};
    }

    IVertex const& vertex = *vertices.at(clusterId);
    DiaCluster     result{};
    result.set_id(clusterId);

    std::string owner = hstd::fmt("cluster '{}'", clusterId);

    std::optional<GroupAttributePayload> graphviz = findAttribute<GroupAttributePayload>(
        vertex.attributes(), owner);
    std::optional<KiwiGroupVisualAttributePayload>
        kiwi = findAttribute<KiwiGroupVisualAttributePayload>(vertex.attributes(), owner);

    if (graphviz.has_value() && kiwi.has_value()) {
        throw std::invalid_argument{hstd::fmt(
            "Cluster '{}' contains both Graphviz and Kiwi group attributes", clusterId)};
    }

    bool noAlgorithm = metadata.no_algorithm_cluster_ids().find(clusterId)
                    != metadata.no_algorithm_cluster_ids().end();


    if (!noAlgorithm && graphviz.has_value()
        && graphviz->layout_case() == GroupAttributePayload::LAYOUT_NOT_SET
        && !graphviz->parent_stable_id().empty()) {
        noAlgorithm = true;
    }

    if (noAlgorithm || (!graphviz.has_value() && !kiwi.has_value())) {
        result.set_no_algorithm(google::protobuf::NULL_VALUE);
    } else if (graphviz.has_value()) {
        if (preserveOrigin) { *result.mutable_graphviz() = *graphviz; }
        *result.mutable_bbox() = //
            findRequiredAttribute<
                hstd::ext::graph::layout::proto::IVertexLayoutAttributePayload>(
                vertex, owner)
                .bbox();


    } else {
        if (preserveOrigin) { *result.mutable_kiwi() = *kiwi; }
        *result.mutable_bbox() = //
            findRequiredAttribute<
                hstd::ext::graph::kw::proto::KiwiGroupLayoutAttributePayload>(
                vertex, owner)
                .base()
                .bbox();

        result.mutable_kiwi()->mutable_base()->clear_constraints();

        if (preserveOrigin) {
            for (IConstraint const& constraint : kiwi->base().constraints()) {
                appendDiaConstraint(result.mutable_constraints(), constraint, clusterId);
            }
        }
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
    DiaCluster*                                         result,
    IEdge const&                                        source,
    DiaGraphMetadata const&                             metadata,
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

    DiaCluster* parent = findMutableCluster(result, parentId);

    if (parent == nullptr) {
        throw std::invalid_argument{hstd::fmt(
            "Edge '{}' references missing parent cluster '{}'",
            source.stable_id(),
            parentId)};
    }

    DiaEdge* edge = parent->add_edges();
    edge->set_id(source.stable_id());
    edge->set_source(source.source_vertex_id());
    edge->set_target(source.target_vertex_id());

    std::string owner = hstd::fmt("edge '{}'", source.stable_id());

    std::optional<EdgeAttributePayload> graphviz = findAttribute<EdgeAttributePayload>(
        source.attributes(), owner);
    std::optional<KiwiEdgeVisualAttributePayload>
        kiwi = findAttribute<KiwiEdgeVisualAttributePayload>(source.attributes(), owner);

    if (graphviz.has_value() && kiwi.has_value()) {
        throw hstd::serde::read_error::init(
            hstd::fmt(
                "Edge '{}' contains both Graphviz and Kiwi attributes",
                source.stable_id()));
    }

    if (graphviz.has_value()) {
        if (preserveOrigin) { *edge->mutable_graphviz() = *graphviz; }
        *edge->mutable_path() = //
            findRequiredAttribute<
                hstd::ext::graph::layout::proto::IEdgeLayoutAttributePayload>(
                source, owner)
                .path();
    } else if (kiwi.has_value()) {
        if (preserveOrigin) { *edge->mutable_kiwi() = *kiwi; }
        *edge->mutable_path() = //
            findRequiredAttribute<
                hstd::ext::graph::layout::proto::IEdgeLayoutAttributePayload>(
                source, owner)
                .path();
    } else {
        throw std::invalid_argument{hstd::fmt(
            "Edge '{}' contains neither a Graphviz nor a Kiwi attribute",
            source.stable_id())};
    }
}

} // namespace

hstd::ext::graph::proto::IGraph hstd::ext::graph::diagram::diaClusterToGraph(
    hstd::ext::graph::diagram::proto::DiaCluster const& root) {
    hstd::serde::protovalidate_message(root);
    IGraph                          graph{};
    DiaGraphMetadata                metadata{};
    std::unordered_set<std::string> vertexIds{};
    std::unordered_set<std::string> edgeIds{};

    auto* collection = graph.add_collections();
    collection->set_stable_id("diagram-edges");
    collection->set_collection_id(0);
    *collection->mutable_payload() = hstd::serde::packMessage(
        TrivialEdgeCollectionPayload{});

    auto* hierarchy = graph.add_hierarchies();
    hierarchy->set_stable_id("diagram-hierarchy");
    *hierarchy->mutable_payload() = hstd::serde::packMessage(
        TrivialVertexHierarchyPayload{});

    auto* ports               = graph.add_ports();
    *ports->mutable_payload() = hstd::serde::packMessage(TrivialPortCollectionPayload{});

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

    IVertexHierarchy const& hierarchy = graph.hierarchies(0);

    if (hierarchy.root_vertex_ids_size() != 1) {
        throw std::invalid_argument{hstd::fmt(
            "Diagram conversion requires exactly one root vertex, but hierarchy '{}' "
            "contains {}",
            hierarchy.stable_id(),
            hierarchy.root_vertex_ids_size())};
    }

    DiaGraphMetadata metadata{};

    if (graph.payload().Is<DiaGraphMetadata>()) {
        metadata = hstd::serde::unpackMessage<DiaGraphMetadata>(graph.payload(), "graph");
    }

    std::unordered_map<std::string, IVertex const*> vertices{};
    std::unordered_map<std::string, IEdge const*>   edges{};

    for (IVertex const& vertex : graph.vertices()) {
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
        for (IEdge const& edge : collection.edges()) {
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

    for (IVertex const& vertex : graph.vertices()) {
        if (findAttribute<GroupAttributePayload>(
                vertex.attributes(), hstd::fmt("vertex '{}'", vertex.stable_id()))
                .has_value()) {
            clusterIds.insert(vertex.stable_id());
        }

        if (findAttribute<KiwiGroupVisualAttributePayload>(
                vertex.attributes(), hstd::fmt("vertex '{}'", vertex.stable_id()))
                .has_value()) {
            clusterIds.insert(vertex.stable_id());
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

    DiaCluster result = buildCluster(
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
