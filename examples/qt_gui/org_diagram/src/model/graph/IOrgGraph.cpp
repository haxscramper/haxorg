#include "IOrgGraph.hpp"
#include <hstd/stdlib/algorithms.hpp>

using namespace org::graph;

void IGraph::registerVertex(const VertexID& id) {
    if (vertexIDs.contains(id)) {
        throw org_graph_error::init(
            std::format("Vertex {} already registered", id));
    }
    vertexIDs.insert(id);
    rootVertices.insert(id);
}

namespace {
constexpr char const* vertex_not_found_msg{
    "{}Vertex {} not found. Missing call to `registerVertex`?"};
}

void org::graph::IGraph::unregisterVertex(const VertexID& id) {
    if (!vertexIDs.contains(id)) {
        throw org_graph_error::init(
            std::format(vertex_not_found_msg, "", id));
    }

    hstd::Vec<VertexID> toRemove;
    hstd::Vec<VertexID> toUntrack;

    std::function<void(const VertexID&)> collectVertices =
        [&](const VertexID& vertexId) {
            toRemove.push_back(vertexId);
            toUntrack.push_back(vertexId);
            if (nestedInMap.contains(vertexId)) {
                for (const auto& subVertex : nestedInMap.at(vertexId)) {
                    collectVertices(subVertex);
                }
            }
        };

    collectVertices(id);

    untrackVertexList(toUntrack);

    for (const auto& vertexId : toRemove) {
        if (parentMap.contains(vertexId)) {
            VertexID parent = parentMap.at(vertexId);
            parentMap.erase(vertexId);
            if (nestedInMap.contains(parent)) {
                nestedInMap.at(parent).erase(vertexId);
                if (nestedInMap.at(parent).empty()) {
                    nestedInMap.erase(parent);
                }
            }
        }

        if (nestedInMap.contains(vertexId)) {
            nestedInMap.erase(vertexId);
        }

        vertexIDs.erase(vertexId);
        rootVertices.erase(vertexId);
    }
}

void org::graph::IGraph::trackVertexList(const hstd::Vec<VertexID>& ids) {
    for (const auto& id : ids) {
        if (!vertexIDs.contains(id)) {
            throw org_graph_error::init(
                std::format(vertex_not_found_msg, "", id));
        }
    }

    for (const auto& id : ids) {
        for (auto& track : trackers) { track->trackVertex(id); }
    }

    for (const auto& id : ids) {
        for (auto& collection : collections) { collection->addVertex(id); }
    }
}

void org::graph::IGraph::untrackVertexList(
    const hstd::Vec<VertexID>& ids) {
    for (const auto& id : ids) {
        if (!vertexIDs.contains(id)) {
            throw org_graph_error::init(
                std::format(vertex_not_found_msg, "", id));
        }
    }

    for (const auto& id : ids) {
        for (auto& collection : collections) { collection->delVertex(id); }
    }

    for (const auto& id : ids) {
        for (auto& track : trackers) { track->untrackVertex(id); }
    }
}

void IGraph::trackSubVertexRelation(
    const VertexID& parent,
    const VertexID& sub) {
    if (!vertexIDs.contains(parent)) {
        throw org_graph_error::init(
            std::format(vertex_not_found_msg, "Parent ", parent));
    }
    if (!vertexIDs.contains(sub)) {
        throw org_graph_error::init(
            std::format(vertex_not_found_msg, "Sub ", sub));
    }
    if (parentMap.contains(sub)) {
        throw org_graph_error::init(
            std::format("Vertex {} already has a parent", sub));
    }

    parentMap.insert_or_assign(sub, parent);
    if (!nestedInMap.contains(parent)) {
        nestedInMap.insert_or_assign(
            parent, hstd::UnorderedSet<VertexID>{});
    }
    nestedInMap.at(parent).insert(sub);
    rootVertices.erase(sub);
}

void IGraph::untrackSubVertexRelation(
    const VertexID& parent,
    const VertexID& sub) {
    if (!vertexIDs.contains(parent)) {
        throw org_graph_error::init(
            std::format(vertex_not_found_msg, "Parent ", parent));
    }
    if (!vertexIDs.contains(sub)) {
        throw org_graph_error::init(
            std::format(vertex_not_found_msg, "Sub ", sub));
    }
    if (!parentMap.contains(sub) || parentMap.at(sub) != parent) {
        throw org_graph_error::init(
            std::format("Vertex {} is not a child of {}", sub, parent));
    }

    parentMap.erase(sub);
    if (nestedInMap.contains(parent)) {
        nestedInMap.at(parent).erase(sub);
        if (nestedInMap.at(parent).empty()) { nestedInMap.erase(parent); }
    }
    rootVertices.insert(sub);
}

hstd::Vec<VertexID> IGraph::getAllVertices() const {
    hstd::Vec<VertexID> result;
    for (const auto& id : vertexIDs) { result.push_back(id); }
    return result;
}

hstd::Vec<VertexID> IGraph::getRootVertices() const {
    hstd::Vec<VertexID> result;
    for (const auto& id : rootVertices) { result.push_back(id); }
    return result;
}

hstd::Vec<VertexID> IGraph::getSubVertices(const VertexID& id) const {
    hstd::Vec<VertexID> result;
    if (nestedInMap.contains(id)) {
        for (const auto& subId : nestedInMap.at(id)) {
            result.push_back(subId);
        }
    }
    return result;
}

hstd::Opt<VertexID> IGraph::getParentVertex(const VertexID& id) const {
    if (parentMap.contains(id)) { return parentMap.at(id); }
    return hstd::Opt<VertexID>{};
}


json IGraph::getGraphSerial() const {
    IGraph::SerialSchema res{};
    for (auto const& collection : collections) {
        for (auto const& edge : collection->getEdges()) {
            res.edges.push_back(
                collection->getEdge(edge).getSerialNonRecursive(this));
        }
    }

    for (auto const& vertex :
         hstd::sorted(hstd::Vec{vertexIDs.begin(), vertexIDs.end()})) {
        // res.flatVertexIDs.push_back(vertex.get);
    }

    for (auto const& vertex : getRootVertices()) {


        json this_serial = getVertexSerialNonRecursive(vertex);

        res.vertices.push_back(this_serial);
    }

    return hstd::to_json_eval(res);
}

EdgeID IEdgeCollection::addEdge(const IEdge& id) {
    auto res_id = EdgeID::FromMaskedIdx(
        edges.get_map().size(), getCategory().t);
    edges.add_unique(res_id, id);
    incidence[id.source][id.target].push_back(res_id);
    return res_id;
}

void IEdgeCollection::delEdge(const EdgeID& id) {
    auto  edge = getEdge(id);
    auto& vec  = incidence.at(edge.source).at(edge.target);
    auto  it   = vec.indexOf(id);
    LOGIC_ASSERTION_CHECK(it != -1, "{}", edge);
    vec.erase(vec.begin() + it);
}

EdgeID IEdgeCollection::getID(const IEdge& edge) const {
    return edges.at_left(edge);
}

hstd::Vec<EdgeID> IEdgeCollection::getEdges() const {
    hstd::Vec<EdgeID> res;
    for (auto const& e : edges.get_map()) { res.push_back(e.first); }
    return res;
}

const IEdge& IEdgeCollection::getEdge(const EdgeID& id) const {
    return edges.at_right(id);
}


hstd::Vec<EdgeID> IEdgeCollection::addVertex(const VertexID& id) {
    hstd::Vec<EdgeID> res;
    for (auto const& e : getOutgoing(id)) { res.push_back(addEdge(e)); }
    return res;
}

void IEdgeCollection::delVertex(const VertexID& id) {
    for (auto const& e : getOutgoing(id)) { delEdge(getID(e)); }
}

std::string IGraphObjectBase::getStableId() const {
    return std::format("IGraphObjectBase-{}", getHash());
}

std::size_t IEdge::getHash() const {
    std::size_t result = 0;
    hstd::hax_hash_combine(result, source);
    hstd::hax_hash_combine(result, target);
    hstd::hax_hash_combine(result, bundleIndex);
    hstd::hax_hash_combine(result, sourcePort);
    hstd::hax_hash_combine(result, targetPort);
    return result;
}

bool IEdge::isEqual(const IGraphObjectBase* other) const {
    auto other_edge = dynamic_cast<IEdge const*>(other);
    return other->isInstance<IEdge>()         //
        && this->source == other_edge->source //
        && this->target == other_edge->target
        && this->bundleIndex == other_edge->bundleIndex
        && this->sourcePort == other_edge->sourcePort
        && this->targetPort == other_edge->targetPort;
}

json IEdge::getSerialNonRecursive(const IGraph* graph) const {
    SerialSchema res{
        .edgeId      = getStableId(),
        .sourceId    = graph->getVertex(source).getStableId(),
        .targetId    = graph->getVertex(target).getStableId(),
        .bundleIndex = bundleIndex,
    };

    if (sourcePort) {
        // res.sourcePortId = graph->get
    }

    return hstd::to_json_eval(res);
}
