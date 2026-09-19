#include "graph_hierarchy.hpp"
#include "graph_base.hpp"
#include <hstd/stdlib/Ranges.hpp>


namespace {
constexpr char const* vertex_not_found_msg{
    "{}vertex {} not found. Missing call to `trackVertex`?"};
} // namespace

using namespace hstd::ext::graph;


IEdgeProvider::DependantDeletion IVertexHierarchy::untrackVertex(VertexID const& id) {
    DependantDeletion result;
    if (!vertexIDs.contains(id)) {
        throw graph_error::init(fmt::format(vertex_not_found_msg, "", id));
    }

    std::function<void(VertexID const&)> collect = [&](VertexID const& current) {
        result.vertices.incl(current);
        if (nestedInMap.contains(current)) {
            for (auto const& sub : nestedInMap.at(current)) { collect(sub); }
        }
    };

    collect(id);

    for (auto const& vertex_id : result.vertices) {
        if (parentMap.contains(vertex_id)) {
            auto parent = parentMap.at(vertex_id);
            parentMap.erase(vertex_id);
            if (nestedInMap.contains(parent)) {
                nestedInMap.at(parent).erase(vertex_id);
                if (nestedInMap.at(parent).empty()) { nestedInMap.erase(parent); }
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


void IVertexHierarchy::trackVertex(VertexID const& id) {
    if (vertexIDs.contains(id)) {
        throw graph_error::init(
            fmt::format(
                "Vertex {} already registered in hierarchy {}", id, getStableID()));
    }
    vertexIDs.insert(id);
    rootVertices.insert(id);
}

void IVertexHierarchy::trackSubVertexRelation(
    EdgeID const&   edge,
    VertexID const& parent,
    VertexID const& sub) {

    if (!vertexIDs.contains(parent)) {
        throw graph_error::init(fmt::format(vertex_not_found_msg, "parent ", parent));
    }

    if (!vertexIDs.contains(sub)) {
        throw graph_error::init(fmt::format(vertex_not_found_msg, "sub ", sub));
    }


    LOGIC_ASSERTION_CHECK_FMT(
        hasEdge(edge),
        "Edge nesting tracking must be done after the edge ID is "
        "already associated with an object in the edge collection. "
        "hasEdge({}) = false",
        edge);

    if (parentMap.contains(sub)) {
        throw graph_error::init(fmt::format("Vertex {} already has a parent", sub));
    }

    parentMap.insert_or_assign(sub, parent);
    if (!nestedInMap.contains(parent)) {
        nestedInMap.insert_or_assign(parent, hstd::UnorderedSet<VertexID>{});
    }

    nestedInMap.at(parent).insert(sub);
    if (rootVertices.contains(sub)) { rootVertices.erase(sub); }
    edgeTracker.add_unique({parent, sub}, edge);

    stableIdMap.insert_or_assign(getEdge(edge)->getStableId(), edge);
}


EdgeID hstd::ext::graph::IVertexHierarchy::getNestingEdgeID(
    VertexID const& parent,
    VertexID const& sub) {
    if (!vertexIDs.contains(parent)) {
        throw graph_error::init(fmt::format(vertex_not_found_msg, "Parent ", parent));
    }
    if (!vertexIDs.contains(sub)) {
        throw graph_error::init(fmt::format(vertex_not_found_msg, "Sub ", sub));
    }

    return EdgeID::FromMasked(
        hstd::hash_bits<48>(parent.value, sub.value), getCollectionID());
}


void IVertexHierarchy::untrackSubVertexRelation(
    VertexID const& parent,
    VertexID const& sub) {
    if (!vertexIDs.contains(parent)) {
        throw graph_error::init(fmt::format(vertex_not_found_msg, "Parent ", parent));
    }
    if (!vertexIDs.contains(sub)) {
        throw graph_error::init(fmt::format(vertex_not_found_msg, "Sub ", sub));
    }
    if (!parentMap.contains(sub) || parentMap.at(sub) != parent) {
        throw graph_error::init(
            fmt::format("Vertex {} is not a child of {}", sub, parent));
    }

    parentMap.erase(sub);
    if (nestedInMap.contains(parent)) {
        nestedInMap.at(parent).erase(sub);
        if (nestedInMap.at(parent).empty()) { nestedInMap.erase(parent); }
    }
    rootVertices.insert(sub);
}

VertexIDSet IVertexHierarchy::getAllVertices() const {
    VertexIDSet result;
    for (auto const& id : vertexIDs) { result.incl(id); }
    return result;
}

VertexIDSet IVertexHierarchy::getRootVertices() const {
    VertexIDSet result;
    for (auto const& id : rootVertices) { result.incl(id); }
    return result;
}

VertexIDSet IVertexHierarchy::getSubVertices(VertexID const& id) const {
    VertexIDSet result;
    if (nestedInMap.contains(id)) {
        for (auto const& sub_id : nestedInMap.at(id)) { result.incl(sub_id); }
    }
    return result;
}

hstd::Opt<VertexID> IVertexHierarchy::getParentVertex(VertexID const& id) const {
    if (parentMap.contains(id)) { return parentMap.at(id); }
    return hstd::Opt<VertexID>{};
}

#if ORG_BUILD_WITH_PROTOBUF
void hstd::ext::graph::IVertexHierarchy::writeSerial(
    proto::IVertexHierarchy* out,
    IGraph const*            graph) const {
    out->set_stable_id(getStableID());
    for (auto const& v : rootVertices) {
        out->add_root_vertex_ids(graph->getStableId(v));
    }

    for (auto const& [nested, parent] : parentMap) {
        (*out->mutable_parent_map())[graph->getStableId(nested)] = graph->getStableId(
            parent);
    }

    for (auto const& [parent, sub_vertices] : nestedInMap) {
        auto& ref = (*out->mutable_nested_in_map())[graph->getStableId(parent)];
        for (auto const& sub : sub_vertices) {
            ref.add_vertices(graph->getStableId(sub));
        }
    }
}

namespace {
void validate_nesting_map(proto::IVertexHierarchy const* in) {

    using vertex_pair = std::pair<std::string, std::string>;

    std::map<std::string, vertex_pair> by_edge_id;
    std::map<vertex_pair, std::string> by_source_target;

    for (auto const& e : in->edges()) {
        std::string source_id = e.source_vertex_id();
        std::string target_id = e.target_vertex_id();
        std::string edge_id   = e.stable_id();

        if (auto existing = by_edge_id.find(edge_id); existing != by_edge_id.end()) {
            auto const& [existing_source_id, existing_target_id] = existing->second;

            throw serde_error::init(
                hstd::fmt(
                    "Edge ID '{}' is not unique: it is used by both '{} -> {}' "
                    "and '{} -> {}'",
                    edge_id,
                    existing_source_id,
                    existing_target_id,
                    source_id,
                    target_id));
        }

        vertex_pair endpoints{source_id, target_id};

        if (auto existing = by_source_target.find(endpoints);
            existing != by_source_target.end()) {
            throw serde_error::init(
                hstd::fmt(
                    "Source-target pair '{} -> {}' is not unique: edge IDs '{}' "
                    "and '{}' use the same pair",
                    source_id,
                    target_id,
                    existing->second,
                    edge_id));
        }

        by_edge_id.emplace(edge_id, endpoints);
        by_source_target.emplace(std::move(endpoints), std::move(edge_id));
    }

    std::set<vertex_pair> nested_pairs;

    for (auto const& [source_id, nested_list] : in->nested_in_map()) {
        for (auto const& target_id : nested_list.vertices()) {
            vertex_pair endpoints{source_id, target_id};

            if (!nested_pairs.insert(endpoints).second) {
                throw serde_error::init(
                    hstd::fmt(
                        "Nested input map contains duplicate mapping '{} -> {}'",
                        source_id,
                        target_id));
            }

            if (!by_source_target.contains(endpoints)) {
                throw serde_error::init(
                    hstd::fmt(
                        "Nested input map contains mapping '{} -> {}', but no edge "
                        "with this source-target pair exists. Hierarchy nesting is "
                        "considered an edge from the parent node to the nested node, "
                        "and must contain a dedicated edge object in the hierarchy.",
                        source_id,
                        target_id));
            }
        }
    }

    for (auto const& [edge_id, endpoints] : by_edge_id) {
        auto const& [source_id, target_id] = endpoints;

        if (!nested_pairs.contains(endpoints)) {
            throw serde_error::init(
                hstd::fmt(
                    "Edge '{}' with mapping '{} -> {}' is missing from the nested "
                    "input map",
                    edge_id,
                    source_id,
                    target_id));
        }
    }
}
} // namespace

void hstd::ext::graph::IVertexHierarchy::readSerial(
    proto::IVertexHierarchy const* in,
    IGraph const*                  graph,
    IGraphSerialReaderFactory*     factory) {
    OP_TRACER_MESSAGE_SCOPE(factory, "IVertexHierarchy::readSerial");
    VertexIDSet has_parent;

    validate_nesting_map(in);

    // create a mirror of the existing vertex hierarchy tracking fields
    // and populate those. The root hierarchy must be called for the validation,
    // but it will not create any associations, since it does not have
    // a way to construct the derived edge object properly.
    // Sub-classes must call the `trackSubVertexRelation` with the ID of the
    // edge after it has been constructed and inserted.
    //
    // Note: the sub-class registraty specifically concerns the edges because the
    // hierarchy owns the edge objects. `trackVertex` and vertex presence tracking
    // is done in this method, see at the very end.
    hstd::UnorderedMap<VertexID, hstd::UnorderedSet<VertexID>> tmp_nesting_map;
    hstd::UnorderedMap<VertexID, VertexID>                     tmp_parent_map;
    hstd::UnorderedSet<VertexID>                               tmp_root_vertices;
    hstd::UnorderedSet<VertexID>                               tmp_vertex_ids;

    for (auto const& [parent_vertex, nested_list] : in->nested_in_map()) {
        auto  parent_id = graph->getVertexIDByStableId(parent_vertex);
        auto& ref       = tmp_nesting_map[parent_id];
        tmp_vertex_ids.incl(parent_id);
        for (auto const& nested : nested_list.vertices()) {
            auto nested_id = graph->getVertexIDByStableId(nested);
            has_parent.incl(nested_id);
            ref.incl(nested_id);
            tmp_parent_map.insert_unqiue(nested_id, parent_id);
            OP_TRACER_MESSAGE(
                factory,
                "{} ({}) -> {} ({})",
                nested_id,
                nested,
                parent_id,
                parent_vertex);

            tmp_vertex_ids.incl(nested_id);
        }
    }

    tmp_root_vertices = tmp_vertex_ids - has_parent;

    char const* deser_note
        = "Note: vertex hierarchy is "
          "de-serialized based on the nesting map structure, "
          "and `vertex_set` is redundant and can be left empty. "
          "All vertices must be referenced in the nesting map";

    for (auto const& v : in->vertex_set()) {
        auto id = graph->getVertexIDByStableId(v.first);
        if (!tmp_nesting_map.contains(id)) {
            throw serde_error::init(
                hstd::fmt(
                    "vertex hierarchy vertex_set contains ID not present "
                    "in the nesting map: '{}'. {}",
                    v.first,
                    deser_note));
        }
    }


    for (auto const& root : in->root_vertex_ids()) {
        auto id = graph->getVertexIDByStableId(root);
        if (!tmp_nesting_map.contains(id)) {
            throw serde_error::init(
                hstd::fmt(
                    "vertex hierarchy root_vertex_ids contains ID not "
                    "present in the nesting map: '{}'. {}.",
                    root,
                    deser_note));
        }

        if (tmp_parent_map.contains(id)) {
            throw serde_error::init(
                hstd::fmt(
                    "vertex hierarchy root_vertex_ids contains ID that "
                    "has a parent ID in the nesting map: '{}' has a "
                    "parent '{}'. '{}' has sub-vertices '{}'. {}.",
                    root,
                    tmp_parent_map.at(id),
                    tmp_parent_map.at(id),
                    in->nested_in_map().at(root).vertices() | hstd::rs::to<Vec>(),
                    deser_note));
        }
    }


    for (auto const& [sub_vertex, parent_vertex] : in->parent_map()) {
        auto sub_vertex_id    = graph->getVertexIDByStableId(sub_vertex);
        auto parent_vertex_id = graph->getVertexIDByStableId(parent_vertex);
        if (!tmp_parent_map.contains(sub_vertex_id)) {
            throw serde_error::init(
                hstd::fmt(
                    "vertex hierarchy contains unexpected parent map "
                    "field parent-of({}) = {}. Nesting map specified "
                    "sub-vertices for '{}' as {}. {}.",
                    sub_vertex,
                    parent_vertex,
                    parent_vertex,
                    in->nested_in_map().at(parent_vertex).vertices()
                        | hstd::rs::to<Vec>(),
                    deser_note));
        }
    }

    for (auto const& v : tmp_vertex_ids) { trackVertex(v); }
}


void hstd::ext::graph::TrivialHierarchy::writeSerial(
    proto::IVertexHierarchy* out,
    IGraph const*            graph) const {
    IVertexHierarchy::writeSerial(out, graph);
}

void TrivialHierarchy::readSerial(
    proto::IVertexHierarchy const* in,
    IGraph const*                  graph,
    IGraphSerialReaderFactory*     factory) {
    IVertexHierarchy::readSerial(in, graph, factory);

    for (auto const& e : in->edges()) {
        auto out_edge = factory->newEdge(&e);
        OP_TRACER_MESSAGE(
            factory,
            "Reading nesting {} -> {} :: {}",
            e.source_vertex_id(),
            e.target_vertex_id(),
            e.stable_id());

        auto id = trackSubVertexRelation(
            graph->getVertexIDByStableId(e.source_vertex_id()),
            graph->getVertexIDByStableId(e.target_vertex_id()),
            *hstd::validated_dynamic_cast<TrivialEdge>(out_edge));

        edgeStore.at(id).readSerial(&e, graph, factory);
    }

    for (auto const& e : in->edges()) { getEdgeIDByStableId(e.stable_id()); }
}


#endif

std::optional<VertexID> hstd::ext::graph::IVertexHierarchy::getCommonAncestor(
    VertexIDSet const& ids) const {
    if (ids.empty()) { return std::nullopt; }

    auto                it     = ids.begin();
    hstd::Vec<VertexID> common = getParentChain(*it);
    common.push_back(*it);
    ++it;

    for (; it != ids.end(); ++it) {
        hstd::Vec<VertexID> chain = getParentChain(*it);
        chain.push_back(*it);

        VertexIDSet         currentSet(chain.begin(), chain.end());
        hstd::Vec<VertexID> nextCommon;
        nextCommon.reserve(common.size());

        for (VertexID const& ancestor : common) {
            if (currentSet.contains(ancestor)) { nextCommon.push_back(ancestor); }
        }

        common = std::move(nextCommon);
        if (common.empty()) { return std::nullopt; }
    }

    return common.front();
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

hstd::Vec<VertexID> IVertexHierarchy::getParentChain(VertexID const& id) const {
    hstd::Vec<VertexID> result;
    auto                current = id;
    while (auto parent = getParentVertex(current)) {
        result.push_back(parent.value());
        current = parent.value();
    }
    return result;
}

hstd::Vec<VertexID> hstd::ext::graph::IVertexHierarchy::getParentChainUntil(
    VertexID const& start,
    VertexID const& finish) const {
    hstd::Vec<VertexID> result;
    auto                current = start;
    for (; auto parent = getParentVertex(current);
         parent.has_value() && parent != finish) {
        result.push_back(parent.value());
        current = parent.value();
    }
    return result;
}


EdgeIDSet IVertexHierarchy::getEdges() const {
    EdgeIDSet result;
    for (auto const& [it, value] : edgeTracker.get_map()) { result.incl(value); }
    return result;
}

EdgeIDSet IVertexHierarchy::getOutgoing(VertexID const& vert) const {
    EdgeIDSet result;
    for (auto const& sub_vertex : getSubVertices(vert)) {
        result.incl(edgeTracker.at_right({vert, sub_vertex}));
    }
    return result;
}

EdgeIDSet IVertexHierarchy::getIncoming(VertexID const& vert) const {
    if (auto parent = getParentVertex(vert)) {
        return {edgeTracker.at_right({parent.value(), vert})};
    } else {
        return {};
    }
}


hstd::ext::graph::EdgeIDVec hstd::ext::graph::AutoSegmentingCollection::getSegments(
    EdgeID const& edge) const {
    auto res = segments_to_edges.get_left(edge);
    hstd::rs::sort(res, [this](EdgeID const& lhs, EdgeID const& rhs) -> bool {
        return segment_index.at(lhs) < segment_index.at(rhs);
    });
    return res;
}

void hstd::ext::graph::AutoSegmentingCollection::addEdge(EdgeID const& original) {
    auto crossings = hierarchy->getHierarchyCrossings(
        graph->getSource(original), graph->getTarget(original));
    crossings.insert(0, graph->getSource(original));
    crossings.push_back(graph->getTarget(original));
    // ports and segments are arranged in the same order as the
    // original vertex, [source] ---> (port) ---> (port) ---> [target]
    for (auto const& [idx, it] : hstd::rv::zip(
             hstd::rv::iota(0, crossings.size()), crossings | hstd::rv::sliding(2))) {
        auto segment_edge = segmented_edges->addEdge(it[0], it[1]);
        segments_to_edges.add_unique(segment_edge, original);
        segment_index.insert_or_assign(segment_edge, idx);
    }

    for (auto const& it : hstd::own_view(getSegments(original)) | hstd::rv::sliding(2)) {
        LOGIC_ASSERTION_CHECK_FMT(
            graph->getTarget(it[0]) == graph->getSource(it[1]),
            "logic error, segment {}-{} created from edge {} should "
            "have the target of the first segment match the source fo "
            "the second segment",
            graph->getDebug(it[0]),
            graph->getDebug(it[1]),
            graph->getDebug(original));

        PortID port = connection_ports->addPort(graph->getTarget(it[0]));
        connection_ports->addEdgeToPort(port, it[0], true);
        connection_ports->addEdgeToPort(port, it[1], false);
        segments_to_ports.add_unique({it[0], it[1]}, port);
    }
}

hstd::Vec<PortID> hstd::ext::graph::AutoSegmentingCollection::getSegmentationPorts(
    EdgeID const& original) {
    return hstd::own_view(getSegments(original)) //
         | hstd::rv::sliding(2) | hstd::rv::transform([this](auto const& it) -> PortID {
               return segments_to_ports.at_right({it[0], it[1]});
           })
         | hstd::rs::to<Vec>();
}

void hstd::ext::graph::TrivialHierarchy::addEdge(
    EdgeID const&      id,
    TrivialEdge const& init_vertex) {
    edgeStore.insert_or_assign(id, init_vertex);
}

EdgeID TrivialHierarchy::trackSubVertexRelation(
    VertexID const&               parent,
    VertexID const&               sub,
    hstd::Opt<TrivialEdge> const& init_vertex) {
    auto id = getNestingEdgeID(parent, sub);
    addEdge(
        id,
        init_vertex.has_value() ? init_vertex.value()
                                : TrivialEdge{hstd::fmt("{}-{}", parent, sub)});
    IVertexHierarchy::trackSubVertexRelation(id, parent, sub);
    return id;
}
