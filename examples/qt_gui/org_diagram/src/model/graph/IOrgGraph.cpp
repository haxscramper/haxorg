#include "IOrgGraph.hpp"
#include <hstd/stdlib/algorithms.hpp>
#include <stack>

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

void IGraph::delCollection(const hstd::SPtr<IEdgeCollection>& collection) {
    collections.erase(collection->getCategory());
}

hstd::Vec<VertexID> IGraph::getHierarchyCrossings(const EdgeID& id) const {
    auto findLCA = [this](VertexID u, VertexID v) -> VertexID {
        hstd::UnorderedSet<VertexID> parents{};
        while (true) {
            parents.insert(u);
            u = parentMap.contains(u) ? parentMap.at(u) : u;
            if (parents.contains(v)) { return v; }
            if (!parentMap.contains(v)) { break; }
            v = parentMap.at(v);
        }
        return u;
    };

    auto const& edge   = getEdge(id);
    auto        source = edge.getSource();
    auto        target = edge.getTarget();

    bool sourceHasParent = parentMap.contains(source);
    bool targetHasParent = parentMap.contains(target);

    if (!sourceHasParent && !targetHasParent) { return {}; }
    if (sourceHasParent && targetHasParent
        && parentMap.at(source) == parentMap.at(target)) {
        return {};
    }

    auto lca = findLCA(source, target);

    hstd::Vec<VertexID> path{};

    if (lca == source || lca == target) {
        // source is the ancestor of the target
        if (lca == source) {
            VertexID current = target;
            while (current != lca) {
                if (current != target) { path.emplace_back(current); }
                current = parentMap.at(current);
            }
        } else {
            VertexID current = source;
            while (current != lca) {
                if (current != source) { path.emplace_back(current); }
                current = parentMap.at(current);
            }
        }
    } else {
        VertexID current = source;
        while (current != lca) {
            if (current != source) { path.emplace_back(current); }
            current = parentMap.at(current);
        }

        current = target;
        std::stack<VertexID> temp{};

        while (current != lca) {
            temp.push(current);
            current = parentMap.at(current);
        }

        while (!temp.empty()) {
            if (temp.top() != target) { path.emplace_back(temp.top()); }
            temp.pop();
        }
    }


    return path;
}

void IGraph::addTracker(hstd::SPtr<IPropertyTracker> const& tracker) {
    trackers.insert_or_assign(tracker->getTrackerID(), tracker);
}

void IGraph::delTracker(hstd::SPtr<IPropertyTracker> const& tracker) {
    trackers.erase(tracker->getTrackerID());
}

void IGraph::addCollection(hstd::SPtr<IEdgeCollection> const& collection) {
    LOGIC_ASSERTION_CHECK(
        !collections.contains(collection->getCategory()),
        "Collection with category ID {} already exists in the graph "
        "tracker",
        collection->getCategory().t);

    for (auto const& coll : collections) {
        LOGIC_ASSERTION_CHECK(
            (coll.second->getStableID() != collection->getStableID()),
            "Collection with stable {} ID already existsin in the graph "
            "tracker",
            collection->getStableID());
    }

    collections.insert_or_assign(collection->getCategory(), collection);
}

void org::graph::IGraph::trackVertexList(const hstd::Vec<VertexID>& ids) {
    for (const auto& id : ids) {
        if (!vertexIDs.contains(id)) {
            throw org_graph_error::init(
                std::format(vertex_not_found_msg, "", id));
        }
    }

    for (const auto& id : ids) {
        for (auto& track : trackers) { track.second->trackVertex(id); }
    }

    for (auto const& id : ids) {
        for (auto& collection : collections) {
            collection.second->trackVertex(id);
        }
    }

    for (const auto& id : ids) {
        for (auto& collection : collections) {
            collection.second->addAllOutgoing(id);
        }
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
        for (auto& collection : collections) {
            collection.second->delVertex(id);
        }
    }

    for (const auto& id : ids) {
        for (auto& track : trackers) { track.second->untrackVertex(id); }
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

const IEdge& IGraph::getEdge(const EdgeID& id) const {
    return collections.at(EdgeCategoryID(id.getMask()))->getEdge(id);
}


template <typename K, typename V, typename MapType>
struct JsonSerdeMapApiAsObject {
    static json to_json(MapType const& it) {
        auto result = json::object();
        for (auto const& [key, val] : it) {
            result[hstd::JsonSerde<K>::to_json(key).template get<std::string>()] = hstd::
                JsonSerde<V>::to_json(val);
        }

        return result;
    }
    static MapType from_json(json const& j) {
        MapType result;
        for (auto const& it : j.get<json::object_t>()) {
            result[it.first] = hstd::JsonSerde<V>::from_json(it.second);
        }
        return result;
    }
};

template <typename V>
struct hstd::JsonSerde<hstd::UnorderedMap<std::string, V>>
    : public JsonSerdeMapApiAsObject<
          std::string,
          V,
          hstd::UnorderedMap<std::string, V>> {};


json IGraph::getGraphSerial() const {
    IGraph::SerialSchema res{};
    for (auto const& [_, collection] : collections) {
        SerialSchema::EdgeCategory category;
        category.categoryName = collection->getStableID();
        for (auto const& edge : collection->getEdges()) {
            category.edges.push_back(
                collection->getEdge(edge).getSerialNonRecursive(
                    this, edge));

            auto& cross = category.hierarchyEdgeCrossings
                              [collection->getEdge(edge).getStableId()];
            hstd::Vec<VertexID> crossings = getHierarchyCrossings(edge);
            for (auto const& c : crossings) {
                cross.push_back(getVertex(c).getStableId());
            }
        }

        res.edges.insert_or_assign(category.categoryName, category);
    }

    for (auto const& vertex : hstd::sorted(
             hstd::Vec<VertexID>{vertexIDs.begin(), vertexIDs.end()})) {
        res.flatVertexIDs.push_back(getVertex(vertex).getStableId());
    }

    for (auto const& vertex : hstd::sorted(
             hstd::Vec<VertexID>{rootVertices.begin(), vertexIDs.end()})) {
        res.rootVertexIDs.push_back(getVertex(vertex).getStableId());
    }

    for (auto const& [parent, nested] : nestedInMap) {
        auto& arr = res.vertexNestingMap[getVertex(parent).getStableId()];
        for (auto const& it : nested) {
            arr.push_back(getVertex(it).getStableId());
        }
    }

    for (auto const& [nested, parent] : parentMap) {
        res.vertexParentMap[getVertex(parent).getStableId()] //
            = getVertex(parent).getStableId();
    }

    for (auto const& vertex : vertexIDs) {
        json this_serial = getVertex(vertex).getSerialNonRecursive(
            this, vertex);
        res.vertices[getVertex(vertex).getStableId()] = this_serial;
    }

    return hstd::to_json_eval(res);
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

json IEdge::getSerialNonRecursive(const IGraph* graph, const EdgeID& id)
    const {

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


hstd::Vec<EdgeID> IEdgeCollection::getOutgoing(
    VertexID const& vert) const {
    hstd::Vec<EdgeID> result;
    if (incidence.contains(vert)) {
        for (const auto& [target, edges] : incidence.at(vert)) {
            for (const auto& edge : edges) { result.push_back(edge); }
        }
    }
    return result;
}

hstd::Vec<EdgeID> IEdgeCollection::getIncoming(
    VertexID const& vert) const {
    hstd::Vec<EdgeID> result;
    if (incoming_from.contains(vert)) {
        for (const auto& source : incoming_from.at(vert)) {
            if (incidence.contains(source)
                && incidence.at(source).contains(vert)) {
                for (const auto& edge : incidence.at(source).at(vert)) {
                    result.push_back(edge);
                }
            }
        }
    }
    return result;
}

void IEdgeCollection::trackVertex(VertexID const& vert) {
    if (!incidence.contains(vert)) {
        incidence.insert_or_assign(
            vert, hstd::UnorderedMap<VertexID, hstd::Vec<EdgeID>>{});
    }
    if (!incoming_from.contains(vert)) {
        incoming_from.insert_or_assign(vert, hstd::Vec<VertexID>{});
    }
}

void IEdgeCollection::untrackVertex(VertexID const& vert) {
    hstd::Vec<EdgeID> edgesToRemove;

    if (incidence.contains(vert)) {
        for (const auto& [target, edges] : incidence.at(vert)) {
            for (const auto& edge : edges) {
                edgesToRemove.push_back(edge);
            }
        }
    }

    if (incoming_from.contains(vert)) {
        for (const auto& source : incoming_from.at(vert)) {
            if (incidence.contains(source)
                && incidence.at(source).contains(vert)) {
                for (const auto& edge : incidence.at(source).at(vert)) {
                    edgesToRemove.push_back(edge);
                }
            }
        }
    }

    for (const auto& edge : edgesToRemove) { untrackEdge(edge); }

    incidence.erase(vert);
    incoming_from.erase(vert);
}

void IEdgeCollection::trackEdge(EdgeID const& id) {
    const IEdge& edge   = getEdge(id);
    VertexID     source = edge.getSource();
    VertexID     target = edge.getTarget();

    if (!incidence.contains(source)) {
        incidence.insert_or_assign(
            source, hstd::UnorderedMap<VertexID, hstd::Vec<EdgeID>>{});
    }
    if (!incidence.at(source).contains(target)) {
        incidence.at(source).insert_or_assign(target, hstd::Vec<EdgeID>{});
    }
    incidence.at(source).at(target).push_back(id);

    if (!incoming_from.contains(target)) {
        incoming_from.insert_or_assign(target, hstd::Vec<VertexID>{});
    }
    incoming_from.at(target).push_back(source);
}

void IEdgeCollection::untrackEdge(EdgeID const& id) {
    const IEdge& edge   = getEdge(id);
    VertexID     source = edge.getSource();
    VertexID     target = edge.getTarget();

    if (incidence.contains(source)
        && incidence.at(source).contains(target)) {
        auto& edges = incidence.at(source).at(target);
        edges.erase(
            std::remove(edges.begin(), edges.end(), id), edges.end());
        if (edges.empty()) {
            incidence.at(source).erase(target);
            if (incidence.at(source).empty()) { incidence.erase(source); }
        }
    }

    if (incoming_from.contains(target)) {
        auto& sources = incoming_from.at(target);
        sources.erase(
            std::remove(sources.begin(), sources.end(), source),
            sources.end());
        if (sources.empty()) { incoming_from.erase(target); }
    }
}

hstd::Vec<EdgeID> IEdgeCollection::getEdges() const {
    hstd::Vec<EdgeID> result;
    for (const auto& [source, targets] : incidence) {
        for (const auto& [target, edges] : targets) {
            for (const auto& edge : edges) { result.push_back(edge); }
        }
    }
    return result;
}

void IEdgeCollection::delVertex(VertexID const& id) { untrackVertex(id); }
