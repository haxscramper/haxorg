#include "graph_base.hpp"

#include <hstd/stdlib/Debug.hpp>
#include <hstd/stdlib/OptFormatter.hpp>
#include <hstd/stdlib/Ranges.hpp>
#include <hstd/stdlib/VecFormatter.hpp>
#include <hstd/stdlib/algorithms.hpp>
#include <stack>

using namespace hstd::ext::graph;

namespace {
constexpr char const* vertex_not_found_msg{
    "{}vertex {} not found. Missing call to `registerVertex`?"};
} // namespace

IGraph::IGraph(
    Vec<hstd::SPtr<IEdgeCollection>>   collections,
    Vec<hstd::SPtr<IPortCollection>>   ports,
    Vec<hstd::SPtr<IVertexHierarchy>>  hierarchies,
    Vec<hstd::SPtr<IAttributeTracker>> trackers) {
    for (auto const& c : collections) { addCollection(c); }
    for (auto const& h : hierarchies) { addHierarchy(h); }
    for (auto const& p : ports) { addPorts(p); }
    for (auto const& t : trackers) { addTracker(t); }
}

void IGraph::addTracker(hstd::SPtr<IAttributeTracker> const& tracker) {
    trackers.insert_or_assign(tracker->getTrackerID(), tracker);
}

void IGraph::delTracker(hstd::SPtr<IAttributeTracker> const& tracker) {
    trackers.erase(tracker->getTrackerID());
}

void IGraph::addCollection(hstd::SPtr<IEdgeCollection> const& collection) {

    if (auto coll = collections.get(collection->getCollectionID()); coll.has_value()) {
        collection->getCollectionID().assert_is_collection();
    }


    for (auto const& coll : collections) {
        LOGIC_ASSERTION_CHECK_FMT(
            (coll.second->getStableID() != collection->getStableID()),
            "Collection with stable {} ID already existsin in the graph "
            "tracker",
            collection->getStableID());
    }

    collections.insert_or_assign(collection->getCollectionID(), collection);
}

void IGraph::delCollection(hstd::SPtr<IEdgeCollection> const& collection) {
    collections.erase(collection->getCollectionID());
}

void IGraph::addHierarchy(hstd::SPtr<IVertexHierarchy> const& hierarchy) {
    hierarchy->getCollectionID().assert_is_hierarchy();

    LOGIC_ASSERTION_CHECK_FMT(
        !hierarchies.contains(hierarchy->getCollectionID()),
        "Hierarchy with ID {} already exists in the graph tracker",
        hierarchy->getCollectionID().t);

    for (auto const& [_, existing] : hierarchies) {
        LOGIC_ASSERTION_CHECK_FMT(
            existing->getStableID() != hierarchy->getStableID(),
            "Hierarchy with stable {} ID already exists in the graph "
            "tracker",
            hierarchy->getStableID());
    }

    hierarchies.insert_or_assign(hierarchy->getCollectionID(), hierarchy);
}

void IGraph::delHierarchy(hstd::SPtr<IVertexHierarchy> const& hierarchy) {
    hierarchies.erase(hierarchy->getCollectionID());
}

void hstd::ext::graph::IGraph::delPorts(hstd::SPtr<IPortCollection> const& collection) {
    ports.erase(collection->getCollectionID());
}

void hstd::ext::graph::IGraph::addPorts(hstd::SPtr<IPortCollection> const& collection) {
    ports.insert_unqiue(collection->getCollectionID(), collection);
}


bool hstd::ext::graph::IGraph::hasCollection(
    hstd::SPtr<IEdgeCollection> const& collection) {
    return collections.contains(collection->getCollectionID());
}

bool hstd::ext::graph::IGraph::hasHierarchy(
    hstd::SPtr<IVertexHierarchy> const& hierarchy) {
    return hierarchies.contains(hierarchy->getCollectionID());
}

bool hstd::ext::graph::IGraph::hasPorts(hstd::SPtr<IPortCollection> const& hierarchy) {
    return ports.contains(hierarchy->getCollectionID());
}


hstd::Vec<IEdgeProvider*> IGraph::getEdgeProviders() const {
    hstd::Vec<IEdgeProvider*> result;
    for (auto const& [id, collection] : collections) {
        result.push_back(collection.get());
    }
    for (auto const& [id, hierarchy] : hierarchies) { result.push_back(hierarchy.get()); }
    return result;
}

EdgeID IGraph::getEdgeIDByStableId(Str const& id) const {
    for (auto const& pr : getEdgeProviders()) {
        if (pr->hasEdgeStableId(id)) { return pr->getEdgeIDByStableId(id); }
    }
    throw edge_structure_error::init(
        hstd::fmt("No edge is associated with the stable ID '{}'", id));
}

VertexID IGraph::getVertexIDByStableId(Str const& id) const {
    LOGIC_ASSERTION_CHECK(!id.empty(), "stable ID cannot be empty");
    if (auto res = stableIdMap.get(id)) {
        return res.value();
    } else {
        throw graph_error::init(
            hstd::fmt("Could not find key '{}' in the vertex graph", id));
    }
}

hstd::Vec<IGraph::Crossing> IGraph::getHierarchyCrossings(EdgeID const& edge_id) const {
    hstd::Vec<Crossing> result;

    for (auto const& [hierarchy_id, hierarchy] : hierarchies) {
        auto crossings = hierarchy->getHierarchyCrossings(
            getSource(edge_id), getTarget(edge_id));
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
    EdgeCollectionID const& hierarchy,
    EdgeID const&           edge,
    VertexID const&         parent,
    VertexID const&         sub) {
    if (!vertexIDs.contains(parent)) {
        throw graph_error::init(fmt::format(vertex_not_found_msg, "parent ", parent));
    }
    if (!vertexIDs.contains(sub)) {
        throw graph_error::init(fmt::format(vertex_not_found_msg, "sub ", sub));
    }

    hstd::Vec<EdgeID> result;
    result.push_back(edge);
    hierarchies.at(hierarchy)->trackSubVertexRelation(edge, parent, sub);
    return result;
}

void IGraph::untrackSubVertexRelation(
    EdgeCollectionID const& hierarchy,
    VertexID const&         parent,
    VertexID const&         sub) {
    hierarchies.at(hierarchy)->untrackSubVertexRelation(parent, sub);
}

void IGraph::validatePortArguments(VertexID const& v, EdgeID const& e, bool is_start) {
    if (is_start) {
        LOGIC_ASSERTION_CHECK_FMT(
            getSource(e) == v,
            "Mismatch between provided vertex and edge source: "
            "start({}) is {}, attempting to use {}",
            getDebug(e),
            getDebug(getSource(e)),
            getDebug(v));
    } else {
        LOGIC_ASSERTION_CHECK_FMT(
            getTarget(e) == v,
            "Mismatch between provided vertex and target source: "
            "target({}) is {}, attempting to use {}",
            getDebug(e),
            getDebug(getTarget(e)),
            getDebug(v));
    }
}

hstd::ext::graph::PortCollectionID hstd::ext::graph::IGraph::getPortCollectionID(
    PortID const& id) const {
    return PortCollectionID{hstd::u16(id.getMask())};
}


void hstd::ext::graph::IGraph::trackVertex(VertexID const& id) {
    if (vertexIDs.contains(id)) {
        throw graph_error::init(fmt::format("Vertex {} already registered", id));
    }
    vertexIDs.insert(id);
    stableIdMap.insert_unqiue(getVertex(id)->getStableId(), id);

    for (auto& track : trackers) { track.second->trackVertex(id); }
}

hstd::UnorderedMap<EdgeCollectionID, IEdgeCollection::DependantDeletion> hstd::ext::
    graph::IGraph::untrackVertex(VertexID const& id) {
    if (!vertexIDs.contains(id)) {
        throw graph_error::init(fmt::format(vertex_not_found_msg, "", id));
    }

    hstd::UnorderedMap<EdgeCollectionID, IEdgeProvider::DependantDeletion> result;

    for (auto const& [hierarchy_id, hierarchy] : hierarchies) {
        auto deleted_by_provider = hierarchy->untrackVertex(id);
        result.insert_or_assign(hierarchy_id, deleted_by_provider);
    }

    for (auto const& [collection_id, collection] : collections) {
        collection->untrackVertex(id);
    }

    for (auto& collection : getEdgeProviders()) { collection->untrackVertex(id); }

    for (auto& track : trackers) { track.second->untrackVertex(id); }

    vertexIDs.erase(id);
    return result;
}

VertexIDSet IGraph::getAllVertices() const {
    VertexIDSet result;
    for (const auto& id : vertexIDs) { result.incl(id); }
    return result;
}

VertexIDSet IGraph::getRootVertices(EdgeCollectionID const& hierarchy) const {
    return hierarchies.at(hierarchy)->getRootVertices();
}

VertexIDSet IGraph::getSubVertices(EdgeCollectionID const& hierarchy, VertexID const& id)
    const {
    return hierarchies.at(hierarchy)->getSubVertices(id);
}

hstd::Opt<VertexID> IGraph::getParentVertex(
    EdgeCollectionID const& hierarchy,
    VertexID const&         id) const {
    return hierarchies.at(hierarchy)->getParentVertex(id);
}

namespace {
auto format_collection //
    = hstd::rv::transform(
          [](auto const& pair) -> std::string { return pair.second->getStableID(); })
    | hstd::rs::to<hstd::Vec>();
} // namespace


hstd::ext::graph::VertexID hstd::ext::graph::IGraph::getSource(EdgeID const& id) const {
    return getEdgeProvider(id)->getSource(id);
}

hstd::ext::graph::VertexID hstd::ext::graph::IGraph::getTarget(EdgeID const& id) const {
    return getEdgeProvider(id)->getTarget(id);
}

int IGraph::getMaxNestingLevel(EdgeCollectionID const& hierarchy) const {
    return hierarchies.at(hierarchy)->getMaxNestingLevel();
}

hstd::Vec<VertexID> IGraph::getParentChain(
    EdgeCollectionID const& hierarchy,
    VertexID const&         id) const {
    return hierarchies.at(hierarchy)->getParentChain(id);
}


template <typename K, typename V, typename MapType>
struct JsonSerdeMapApiAsObject {
    static json to_json(MapType const& it) {
        auto result = json::object();
        for (auto const& [key, val] : it) {
            result[hstd::JsonSerde<K>::to_json(key)
                       .template get<std::string>()] = hstd::JsonSerde<V>::to_json(val);
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
    : public JsonSerdeMapApiAsObject<std::string, V, hstd::UnorderedMap<std::string, V>> {
};


#if ORG_BUILD_WITH_PROTOBUF
void IGraph::writeSerial(proto::IGraphProto* out) const {
    for (auto const& [_, collection] : collections) {
        collection->writeSerial(out->add_collections(), this);
    }

    for (auto const& [_, hierarchy] : hierarchies) {
        hierarchy->writeSerial(out->add_hierarchies(), this);
    }

    for (auto const& vertex :
         hstd::sorted(hstd::Vec<VertexID>{vertexIDs.begin(), vertexIDs.end()})) {
        getVertex(vertex)->writeSerial(out->add_vertices(), this, vertex);
    }
}
#endif

#if ORG_BUILD_WITH_PROTOBUF
void IGraph::readSerial(
    proto::IGraphProto const*  in,
    IGraphSerialReaderFactory* factory) {
    OP_TRACER_MESSAGE_SCOPE(factory, "IGraph read serial");

    hstd::Vec<hstd::SPtr<IEdgeCollection>>  collection_list;
    hstd::Vec<hstd::SPtr<IVertexHierarchy>> hierarchy_list;
    hstd::Vec<hstd::SPtr<IPortCollection>>  ports_list;

    for (auto const& coll : in->collections()) {
        auto new_collection = factory->newEdgeCollection(&coll);
        collection_list.push_back(new_collection);
        addCollection(new_collection);
    }

    for (auto const& coll : in->hierarchies()) {
        auto new_collection = factory->newVertexHierarchy(&coll);
        hierarchy_list.push_back(new_collection);
        addHierarchy(new_collection);
    }

    for (auto const& coll : in->ports()) {
        auto new_collection = factory->newPortCollection(&coll);
        ports_list.push_back(new_collection);
        addPorts(new_collection);
    }


    // order of data de-serialization is important. Vertices are loaded
    // first because they don't depend on any other graph elements. Then
    // the edges are loaded since an edge needs a source and a target node.
    // Finally, ports are loaded last since they are defined at an
    // intersection of the vertex and edge.
    for (auto const& v : in->vertices()) {
        auto new_vertex = factory->newVertex(&v);
        new_vertex->readSerial(&v, this, factory);
        std::ignore = addVertex(new_vertex);
    }

    // split the collection content reading and the collection object
    // construction so objects could access full set of collections if
    // necessary.
    for (auto const& [coll, entry] : hstd::rv::zip(in->collections(), collection_list)) {
        entry->readSerial(&coll, this, factory);
    }

    for (auto const& [coll, entry] : hstd::rv::zip(in->hierarchies(), hierarchy_list)) {
        entry->readSerial(&coll, this, factory);
    }

    for (auto const& [coll, entry] : hstd::rv::zip(in->ports(), ports_list)) {
        entry->readSerial(&coll, this, factory);
    }
}
#endif

#if ORG_BUILD_WITH_PROTOBUF
std::unique_ptr<proto::IGraphProto> IGraph::get_serial() const {
    auto result = std::make_unique<proto::IGraphProto>();
    writeSerial(result.get());
    return std::move(result);
}
#endif

std::string hstd::ext::graph::IGraph::getDebug(VertexIDSet const& vert) const {
    return hstd::fmt1(
        hstd::own_view(hstd::sorted(vert.items()))
        | hstd::rv::transform(
            [&](VertexID const& id) -> std::string { return getDebug(id); })
        | hstd::rs::to<hstd::Vec>());
}

std::string hstd::ext::graph::IGraph::getDebug(VertexIDVec const& vert) const {
    return hstd::fmt1(
        vert | hstd::rv::transform([&](VertexID const& id) -> std::string {
            return getDebug(id);
        })
        | hstd::rs::to<hstd::Vec>());
}

std::string hstd::ext::graph::IGraph::getDebug(EdgeIDSet const& vert) const {
    return getDebug(hstd::sorted(vert.items()));
}

std::string hstd::ext::graph::IGraph::getDebug(EdgeIDVec const& vert) const {
    return hstd::fmt1(
        vert | hstd::rv::transform([&](EdgeID const& id) -> std::string {
            return getDebug(id);
        })
        | hstd::rs::to<hstd::Vec>());
}


std::string hstd::ext::graph::IGraph::getDebug(PortIDVec const& vert) const {
    return hstd::fmt1(
        vert | hstd::rv::transform([&](PortID const& id) -> std::string {
            return getDebug(id);
        })
        | hstd::rs::to<hstd::Vec>());
}

std::string hstd::ext::graph::IGraph::getDebug(PortIDSet const& vert) const {
    return getDebug(hstd::sorted(vert.items()));
}

std::string hstd::ext::graph::IGraph::getDebug(VertexID const& vert) const {
    return hstd::fmt("vertex {} ({})", vert, getVertex(vert)->getStableId());
}

std::string hstd::ext::graph::IGraph::getDebug(EdgeID const& edge) const {
    return hstd::fmt(
        "edge {} ({}) from {} to {}",
        edge,
        getEdge(edge) ? getEdge(edge)->getStableId() : "nullptr",
        getDebug(getSource(edge)),
        getDebug(getTarget(edge)));
}

std::string hstd::ext::graph::IGraph::getDebug(PortID const& port) const {
    auto coll = getPortCollection(port);
    return hstd::fmt(
        "port {} ({}) connecting {} to {} as {}",
        port,
        getPort(port) ? getPort(port)->getStableId() : "nullptr",
        getDebug(coll->getEdgeForPort(port)),
        getDebug(coll->getVertexForPort(port)),
        coll->isSourcePort(port) ? "start" : "end");
}


hstd::ext::graph::EdgeCollectionID hstd::ext::graph::IGraph::getHierarchyID(
    EdgeID const& id) const {
    auto id1 = IEdgeProvider::hierarchyIdFromEdge(id);
    LOGIC_ASSERTION_CHECK_FMT(
        hierarchies.contains(id1),
        "Graph does not contain hierarchy with ID {} for edge ID {}. "
        "Have collections {}, stable IDs {}",
        id1.t,
        id.format(),
        hierarchies.keys(),
        hierarchies | format_collection);
    return id1;
}

hstd::ext::graph::EdgeCollectionID hstd::ext::graph::IGraph::getCollectionID(
    EdgeID const& id) const {
    auto id2 = IEdgeProvider::edgeCategoryFromEdge(id);
    LOGIC_ASSERTION_CHECK_FMT(
        collections.contains(id2),
        "Graph does not contain edge collection with ID {} for edge "
        "ID {}. Have collections {}, stable IDs {}",
        id2.t,
        id.format(),
        collections.keys(),
        collections | format_collection);
    return id2;
}

VertexID TrivialGraphBase::addVertex(std::optional<std::string> const& stable_id) {
    return addVertex(
        TrivialVertex{
            stable_id.value_or(hstd::fmt1(vertexStore.getNextId())),
        });
}

VertexID TrivialGraphBase::addVertex(hstd::SPtr<IVertex> const& vertex) {
    return addVertex(*hstd::validated_dynamic_cast<TrivialVertex>(vertex));
}

VertexID TrivialGraphBase::addVertex(TrivialVertex const& vertex) {
    auto result = vertexStore.add(vertex);
    trackVertex(result);
    return result;
}
