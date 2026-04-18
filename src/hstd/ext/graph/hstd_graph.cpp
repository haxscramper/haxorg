#include "hstd_graph.hpp"

#include <hstd/stdlib/algorithms.hpp>
#include <stack>
#include <hstd/stdlib/OptFormatter.hpp>

using namespace hstd::ext::graph;

namespace {
constexpr char const* vertex_not_found_msg{
    "{}Vertex {} not found. Missing call to `registerVertex`?"};
} // namespace

IEdgeProvider::DependantDeletion IVertexHierarchy::untrackVertex(
    VertexID const& id) {
    DependantDeletion result;
    if (!vertexIDs.contains(id)) {
        throw org_graph_error::init(
            std::format(vertex_not_found_msg, "", id));
    }

    std::function<void(VertexID const&)> collect =
        [&](VertexID const& current) {
            result.vertices.push_back(current);
            if (nestedInMap.contains(current)) {
                for (auto const& sub : nestedInMap.at(current)) {
                    collect(sub);
                }
            }
        };

    collect(id);

    for (auto const& vertex_id : result.vertices) {
        if (parentMap.contains(vertex_id)) {
            auto parent = parentMap.at(vertex_id);
            parentMap.erase(vertex_id);
            if (nestedInMap.contains(parent)) {
                nestedInMap.at(parent).erase(vertex_id);
                if (nestedInMap.at(parent).empty()) {
                    nestedInMap.erase(parent);
                }
            }
        }

        if (nestedInMap.contains(vertex_id)) {
            auto nested = nestedInMap.at(vertex_id);
            for (auto const& sub : nested) {
                parentMap.erase(sub);
                rootVertices.insert(sub);
            }
            nestedInMap.erase(vertex_id);
        }

        rootVertices.erase(vertex_id);
        vertexIDs.erase(vertex_id);
    }

    return result;
}


hstd::Vec<VertexID> IVertexHierarchy::getHierarchyCrossings(
    VertexID const& source,
    VertexID const& target) const {
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

void IGraph::addTracker(hstd::SPtr<IAttributeTracker> const& tracker) {
    trackers.insert_or_assign(tracker->getTrackerID(), tracker);
}

void IGraph::delTracker(hstd::SPtr<IAttributeTracker> const& tracker) {
    trackers.erase(tracker->getTrackerID());
}

void IGraph::addCollection(hstd::SPtr<IEdgeCollection> const& collection) {
    LOGIC_ASSERTION_CHECK_FMT(
        !collections.contains(collection->getCategory()),
        "Collection with category ID {} already exists in the graph "
        "tracker",
        collection->getCategory().t);

    for (auto const& coll : collections) {
        LOGIC_ASSERTION_CHECK_FMT(
            (coll.second->getStableID() != collection->getStableID()),
            "Collection with stable {} ID already existsin in the graph "
            "tracker",
            collection->getStableID());
    }

    collections.insert_or_assign(collection->getCategory(), collection);
}

void IGraph::delCollection(hstd::SPtr<IEdgeCollection> const& collection) {
    collections.erase(collection->getCategory());
}

void IGraph::addHierarchy(hstd::SPtr<IVertexHierarchy> const& hierarchy) {
    LOGIC_ASSERTION_CHECK_FMT(
        IEdgeProvider::hierarchyUsesMask(hierarchy->getHierarchyId()),
        "Hierarchy ID {} must have the hierarchy edge mask bit set",
        hierarchy->getHierarchyId().t);

    LOGIC_ASSERTION_CHECK_FMT(
        !hierarchies.contains(hierarchy->getHierarchyId()),
        "Hierarchy with ID {} already exists in the graph tracker",
        hierarchy->getHierarchyId().t);

    for (auto const& [_, existing] : hierarchies) {
        LOGIC_ASSERTION_CHECK_FMT(
            existing->getStableID() != hierarchy->getStableID(),
            "Hierarchy with stable {} ID already exists in the graph "
            "tracker",
            hierarchy->getStableID());
    }

    hierarchies.insert_or_assign(hierarchy->getHierarchyId(), hierarchy);
}

void IGraph::delHierarchy(hstd::SPtr<IVertexHierarchy> const& hierarchy) {
    hierarchies.erase(hierarchy->getHierarchyId());
}

hstd::Vec<IEdgeProvider*> IGraph::getEdgeProviders() {
    hstd::Vec<IEdgeProvider*> result;
    for (auto const& [id, collection] : collections) {
        result.push_back(collection.get());
    }
    for (auto const& [id, hierarchy] : hierarchies) {
        result.push_back(hierarchy.get());
    }
    return result;
}

hstd::Vec<IGraph::Crossing> IGraph::getHierarchyCrossings(
    EdgeID const& edge_id) const {
    hstd::Vec<Crossing> result;

    auto edge = getEdge(edge_id);
    for (auto const& [hierarchy_id, hierarchy] : hierarchies) {
        auto crossings = hierarchy->getHierarchyCrossings(
            edge->getSource(), edge->getTarget());
        if (!crossings.empty()) {
            result.push_back(
                Crossing{
                    .hierarchy = hierarchy_id,
                    .crossings = crossings,
                });
        }
    }

    return result;
}

hstd::Vec<EdgeID> IGraph::trackSubVertexRelation(
    GraphHierarchyID const& hierarchy,
    VertexID const&         parent,
    VertexID const&         sub) {
    if (!vertexIDs.contains(parent)) {
        throw org_graph_error::init(
            std::format(vertex_not_found_msg, "Parent ", parent));
    }
    if (!vertexIDs.contains(sub)) {
        throw org_graph_error::init(
            std::format(vertex_not_found_msg, "Sub ", sub));
    }

    hstd::Vec<EdgeID> result;
    result.push_back(
        hierarchies.at(hierarchy)->trackSubVertexRelation(parent, sub));
    return result;
}

void IGraph::untrackSubVertexRelation(
    GraphHierarchyID const& hierarchy,
    VertexID const&         parent,
    VertexID const&         sub) {
    hierarchies.at(hierarchy)->untrackSubVertexRelation(parent, sub);
}

void hstd::ext::graph::IGraph::trackVertex(VertexID const& id) {
    if (vertexIDs.contains(id)) {
        throw org_graph_error::init(
            std::format("Vertex {} already registered", id));
    }
    vertexIDs.insert(id);

    for (auto& track : trackers) { track.second->trackVertex(id); }

    for (auto& collection : getEdgeProviders()) {
        collection->trackVertex(id);
    }

    for (auto& collection : getEdgeProviders()) {
        collection->addAllOutgoing(id);
    }
}

hstd::UnorderedMap<GraphHierarchyID, IEdgeCollection::DependantDeletion> hstd::
    ext::graph::IGraph::untrackVertex(VertexID const& id) {
    if (!vertexIDs.contains(id)) {
        throw org_graph_error::init(
            std::format(vertex_not_found_msg, "", id));
    }

    hstd::UnorderedMap<GraphHierarchyID, IEdgeProvider::DependantDeletion>
        result;

    for (auto const& [hierarchy_id, hierarchy] : hierarchies) {
        auto deleted_by_provider = hierarchy->untrackVertex(id);
        result.insert_or_assign(hierarchy_id, deleted_by_provider);
    }

    for (auto const& [collection_id, collection] : collections) {
        collection->untrackVertex(id);
    }

    for (auto& collection : getEdgeProviders()) {
        collection->untrackVertex(id);
    }

    for (auto& track : trackers) { track.second->untrackVertex(id); }

    vertexIDs.erase(id);
    return result;
}

hstd::Vec<VertexID> IGraph::getAllVertices() const {
    hstd::Vec<VertexID> result;
    for (const auto& id : vertexIDs) { result.push_back(id); }
    return result;
}

hstd::Vec<VertexID> IGraph::getRootVertices(
    GraphHierarchyID const& hierarchy) const {
    return hierarchies.at(hierarchy)->getRootVertices();
}

hstd::Vec<VertexID> IGraph::getSubVertices(
    GraphHierarchyID const& hierarchy,
    VertexID const&         id) const {
    return hierarchies.at(hierarchy)->getSubVertices(id);
}

hstd::Opt<VertexID> IGraph::getParentVertex(
    GraphHierarchyID const& hierarchy,
    VertexID const&         id) const {
    return hierarchies.at(hierarchy)->getParentVertex(id);
}

const IEdge* IGraph::getEdge(EdgeID const& id) const {
    if (IEdgeProvider::isHierarchyEdge(id)) {
        auto id1 = IEdgeProvider::hierarchyIdFromEdge(id);
        LOGIC_ASSERTION_CHECK_FMT(
            hierarchies.contains(id1),
            "Graph does not contain hierarchy with ID {} for edge ID {}",
            id1.t,
            id.format());
        return hierarchies.at(id1)->getEdge(id);
    } else {
        auto id2 = IEdgeProvider::edgeCategoryFromEdge(id);
        LOGIC_ASSERTION_CHECK_FMT(
            collections.contains(id2),
            "Graph does not contain edge collection with ID {} for edge "
            "ID {}",
            id2.t,
            id.format());
        return collections.at(id2)->getEdge(id);
    }
}

int IGraph::getMaxNestingLevel(GraphHierarchyID const& hierarchy) const {
    return hierarchies.at(hierarchy)->getMaxNestingLevel();
}

hstd::Vec<VertexID> IGraph::getParentChain(
    GraphHierarchyID const& hierarchy,
    VertexID const&         id) const {
    return hierarchies.at(hierarchy)->getParentChain(id);
}

void IVertexHierarchy::trackVertex(VertexID const& id) {
    if (vertexIDs.contains(id)) {
        throw org_graph_error::init(
            std::format("Vertex {} already registered in hierarchy", id));
    }
    vertexIDs.insert(id);
    rootVertices.insert(id);
}

EdgeID IVertexHierarchy::trackSubVertexRelation(
    VertexID const& parent,
    VertexID const& sub) {
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
    EdgeID result = EdgeID::FromMaskedIdx(
        hstd::hash_bits<48>(parent.value, sub.value), getHierarchyId().t);

    edgeTracker.insert_or_assign({parent, sub}, result);
    return result;
}

void IVertexHierarchy::untrackSubVertexRelation(
    VertexID const& parent,
    VertexID const& sub) {
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

hstd::Vec<VertexID> IVertexHierarchy::getAllVertices() const {
    hstd::Vec<VertexID> result;
    for (auto const& id : vertexIDs) { result.push_back(id); }
    return result;
}

hstd::Vec<VertexID> IVertexHierarchy::getRootVertices() const {
    hstd::Vec<VertexID> result;
    for (auto const& id : rootVertices) { result.push_back(id); }
    return result;
}

hstd::Vec<VertexID> IVertexHierarchy::getSubVertices(
    VertexID const& id) const {
    hstd::Vec<VertexID> result;
    if (nestedInMap.contains(id)) {
        for (auto const& sub_id : nestedInMap.at(id)) {
            result.push_back(sub_id);
        }
    }
    return result;
}

hstd::Opt<VertexID> IVertexHierarchy::getParentVertex(
    VertexID const& id) const {
    if (parentMap.contains(id)) { return parentMap.at(id); }
    return hstd::Opt<VertexID>{};
}


int IVertexHierarchy::getMaxNestingLevel() const {
    auto aux = [&](VertexID const& id, auto&& self) -> int {
        auto nested = getSubVertices(id);
        if (nested.empty()) {
            return 1;
        } else {
            int result = 0;
            for (auto const& sub : nested) {
                result = std::max<int>(result, self(sub, self));
            }
            return result + 1;
        }
    };

    int result = 0;
    for (auto const& root : getRootVertices()) {
        result = std::max<int>(result, aux(root, aux));
    }

    return result;
}

hstd::Vec<VertexID> IVertexHierarchy::getParentChain(
    VertexID const& id) const {
    hstd::Vec<VertexID> result;
    auto                current = id;
    while (auto parent = getParentVertex(current)) {
        result.push_back(parent.value());
        current = parent.value();
    }
    return result;
}

hstd::Vec<EdgeID> IVertexHierarchy::getEdges() const {
    hstd::Vec<EdgeID> result;
    for (auto const& [it, value] : edgeTracker) {
        result.push_back(value);
    }
    return result;
}

hstd::Vec<EdgeID> IVertexHierarchy::getOutgoing(
    VertexID const& vert) const {
    hstd::Vec<EdgeID> result;
    for (auto const& sub_vertex : getSubVertices(vert)) {
        result.push_back(edgeTracker.at({vert, sub_vertex}));
    }
    return result;
}

hstd::Vec<EdgeID> IVertexHierarchy::getIncoming(
    VertexID const& vert) const {
    if (auto parent = getParentVertex(vert)) {
        return {edgeTracker.at({parent.value(), vert})};
    } else {
        return {};
    }
}


template <typename K, typename V, typename MapType>
struct JsonSerdeMapApiAsObject {
    static json to_json(MapType const& it) {
        auto result = json::object();
        for (auto const& [key, val] : it) {
            result[hstd::JsonSerde<K>::to_json(key)
                       .template get<std::string>()] = hstd::JsonSerde<V>::
                to_json(val);
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
                collection->getEdge(edge)->getSerialNonRecursive(
                    this, edge));

            auto& cross = category.hierarchyEdgeCrossings
                              [collection->getEdge(edge)->getStableId()];
            for (auto const& item : getHierarchyCrossings(edge)) {
                SerialSchema::EdgeCategory::HierarchyCrossing crossing;
                crossing.hierarchyName = hierarchies.at(item.hierarchy)
                                             ->getStableID();
                for (auto const& c : item.crossings) {
                    crossing.crossings.push_back(
                        getVertex(c)->getStableId());
                }
                cross.push_back(crossing);
            }
        }

        res.edges.insert_or_assign(category.categoryName, category);
    }

    for (auto const& vertex : hstd::sorted(
             hstd::Vec<VertexID>{vertexIDs.begin(), vertexIDs.end()})) {
        res.flatVertexIDs.push_back(getVertex(vertex)->getStableId());
    }

    for (auto const& [hierarchy_id, hierarchy] : hierarchies) {
        SerialSchema::Hierarchy serial_hierarchy;
        serial_hierarchy.hierarchyName   = hierarchy->getStableID();
        serial_hierarchy.maxNestingLevel = hierarchy->getMaxNestingLevel();

        for (auto const& vertex :
             hstd::sorted(hierarchy->getRootVertices())) {
            serial_hierarchy.rootVertexIDs.push_back(
                getVertex(vertex)->getStableId());
        }

        for (auto const& parent : hierarchy->getAllVertices()) {
            auto nested = hierarchy->getSubVertices(parent);
            if (!nested.empty()) {
                auto& arr = serial_hierarchy.vertexNestingMap
                                [getVertex(parent)->getStableId()];
                for (auto const& it : nested) {
                    arr.push_back(getVertex(it)->getStableId());
                }
            }
        }

        for (auto const& nested : hierarchy->getAllVertices()) {
            if (auto parent = hierarchy->getParentVertex(nested)) {
                serial_hierarchy.vertexParentMap
                    [getVertex(nested)
                         ->getStableId()] = getVertex(parent.value())
                                                ->getStableId();
            }
        }

        res.hierarchies.insert_or_assign(
            hierarchy->getStableID(), serial_hierarchy);
    }

    for (auto const& vertex : vertexIDs) {
        json this_serial = getVertex(vertex)->getSerialNonRecursive(
            this, vertex);
        res.vertices[getVertex(vertex)->getStableId()] = this_serial;
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

bool IEdge::isEqual(IGraphObjectBase const* other) const {
    auto other_edge = dynamic_cast<IEdge const*>(other);
    return other->isInstance<IEdge>()         //
        && this->source == other_edge->source //
        && this->target == other_edge->target
        && this->bundleIndex == other_edge->bundleIndex
        && this->sourcePort == other_edge->sourcePort
        && this->targetPort == other_edge->targetPort;
}

json IEdge::getSerialNonRecursive(IGraph const* graph, EdgeID const& id)
    const {

    SerialSchema res{
        .edgeId      = getStableId(),
        .sourceId    = graph->getVertex(source)->getStableId(),
        .targetId    = graph->getVertex(target)->getStableId(),
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

IEdgeProvider::DependantDeletion IEdgeCollection::untrackVertex(
    VertexID const& vert) {
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
    return DependantDeletion{.vertices = {vert}, .edges = edgesToRemove};
}

void IEdgeCollection::trackEdge(EdgeID const& id) {
    IEdge const* edge   = getEdge(id);
    VertexID     source = edge->getSource();
    VertexID     target = edge->getTarget();

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
    IEdge const* edge   = getEdge(id);
    VertexID     source = edge->getSource();
    VertexID     target = edge->getTarget();

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

std::string IEdgeProvider::getStableID() const {
    return hstd::fmt("EdgeProvider-{}", getCategory().t);
}

bool IEdgeProvider::isHierarchyEdge(EdgeID const& id) {
    return (id.getMask() & HierarchyCategoryMaskBit) != 0;
}

EdgeCollectionID IEdgeProvider::edgeCategoryFromEdge(EdgeID const& id) {
    return EdgeCollectionID(hstd::u16(id.getMask()));
}

GraphHierarchyID IEdgeProvider::hierarchyIdFromEdge(EdgeID const& id) {
    return GraphHierarchyID(hstd::u16(id.getMask()));
}

bool IEdgeProvider::hierarchyUsesMask(GraphHierarchyID const& id) {
    return (id.t & HierarchyCategoryMaskBit) != 0;
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

void layout::LayoutRun::runFullLayout() {
    message(
        hstd::fmt(
            "run full layout for the graph with root IDs {}", rootGroups));

    auto aux = [&](this auto&& self, GroupID const& id) -> void {
        message(hstd::fmt("running layout for group ID {}", id));
        auto __scope = scopeLevel();
        auto group   = getGroup(id);
        for (auto const& sub : hstd::sorted(group->subGroups.items())) {
            self(sub);
        }

        for (auto const& sub : hstd::sorted(group->subGroups.items())) {
            if (getGroup(sub)->hasAlgorithm()) {
                LOGIC_ASSERTION_CHECK_FMT(
                    result.groups.contains(sub),
                    "Sub-group '{}' has algorithm specified, but "
                    "recursive walk for layout did not assign the "
                    "bounding box to it. The `runSingleLayout` for a "
                    "group must create a bounding box for result.",
                    getGroup(sub)->getStableId());
            }
        }

        if (group->hasAlgorithm()) {
            auto sub_res = group->getAlgorithm()->runSingleLayout(id);

            LOGIC_ASSERTION_CHECK_FMT(
                sub_res.groups.contains(id),
                "Running layout for {} ('{}') should set the bounding box "
                "for this group.",
                id,
                getGroup(id)->getStableId());

            // Use of `insert_or_assign` here is deliberate -- running
            // layout on the current group might overwrite the positioning
            // of the nested nodes or edges if necessary.
            for (auto const& [id, attr] : sub_res.groups) {
                result.groups.insert_or_assign(id, attr);
            }

            for (auto const& [id, attr] : sub_res.vertices) {
                result.vertices.insert_or_assign(id, attr);
            }

            for (auto const& [id, attr] : sub_res.edges) {
                result.edges.insert_or_assign(id, attr);
            }
        }
    };

    for (auto const& root : rootGroups) { aux(root); }
}

hstd::Vec<hstd::ext::visual::VisGroup> layout::LayoutRun::getVisual()
    const {
    hstd::Vec<hstd::ext::visual::VisGroup> res;
    auto aux = [&](this auto&& self,
                   GroupID     id) -> hstd::ext::visual::VisGroup {
        auto                        group  = getGroup(id);
        hstd::ext::visual::VisGroup result = getLayout(id)->getVisual();

        for (auto const& sub : group->subGroups) {
            auto visual          = self(sub);
            visual.original_id   = sub.getValue();
            visual.original_type = (int)ILayoutAttribute::Kind::Group;
            result.subgroups.push_back(visual);
        }

        for (auto const& it : group->getVertices()) {
            auto const& attr     = getLayout(it);
            auto        visual   = attr->getVisual();
            visual.original_id   = it.getValue();
            visual.original_type = (int)ILayoutAttribute::Kind::Vertex;
            result.subgroups.push_back(visual);
        }

        for (auto const& it : group->getEdges()) {
            auto const& attr     = getLayout(it);
            auto        visual   = attr->getVisual();
            visual.original_id   = it.getValue();
            visual.original_type = (int)ILayoutAttribute::Kind::Edge;
            result.subgroups.push_back(visual);
        }

        return result;
    };

    for (auto const& rg : rootGroups) { res.push_back(aux(rg)); }

    return res;
}
