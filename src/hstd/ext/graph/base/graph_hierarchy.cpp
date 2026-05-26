#include "graph_hierarchy.hpp"
#include "graph_base.hpp"
#include <hstd/stdlib/Ranges.hpp>


namespace {
constexpr char const* vertex_not_found_msg{
    "{}vertex {} not found. Missing call to `registerVertex`?"};
} // namespace

using namespace hstd::ext::graph;


IEdgeProvider::DependantDeletion IVertexHierarchy::untrackVertex(
    VertexID const& id) {
    DependantDeletion result;
    if (!vertexIDs.contains(id)) {
        throw graph_error::init(std::format(vertex_not_found_msg, "", id));
    }

    std::function<void(VertexID const&)> collect =
        [&](VertexID const& current) {
            result.vertices.incl(current);
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


void IVertexHierarchy::trackVertex(VertexID const& id) {
    if (vertexIDs.contains(id)) {
        throw graph_error::init(
            std::format(
                "Vertex {} already registered in hierarchy {}",
                id,
                getStableID()));
    }
    vertexIDs.insert(id);
    rootVertices.insert(id);
}

void IVertexHierarchy::trackSubVertexRelation(
    EdgeID const&   edge,
    VertexID const& parent,
    VertexID const& sub) {

    LOGIC_ASSERTION_CHECK_FMT(
        hasEdge(edge),
        "Edge nesting tracking must be done after the edge ID is "
        "already associated with an object in the edge collection. "
        "hasEdge({}) = false",
        edge);


    if (!vertexIDs.contains(parent)) {
        throw graph_error::init(
            std::format(vertex_not_found_msg, "parent ", parent));
    }

    if (!vertexIDs.contains(sub)) {
        throw graph_error::init(
            std::format(vertex_not_found_msg, "sub ", sub));
    }

    if (parentMap.contains(sub)) {
        throw graph_error::init(
            std::format("Vertex {} already has a parent", sub));
    }

    parentMap.insert_or_assign(sub, parent);
    if (!nestedInMap.contains(parent)) {
        nestedInMap.insert_or_assign(
            parent, hstd::UnorderedSet<VertexID>{});
    }

    nestedInMap.at(parent).insert(sub);
    if (rootVertices.contains(sub)) { rootVertices.erase(sub); }
    edgeTracker.add_unique({parent, sub}, edge);
}


EdgeID hstd::ext::graph::IVertexHierarchy::getNestingEdgeID(
    VertexID const& parent,
    VertexID const& sub) {
    if (!vertexIDs.contains(parent)) {
        throw graph_error::init(
            std::format(vertex_not_found_msg, "Parent ", parent));
    }
    if (!vertexIDs.contains(sub)) {
        throw graph_error::init(
            std::format(vertex_not_found_msg, "Sub ", sub));
    }

    return EdgeID::FromMasked(
        hstd::hash_bits<48>(parent.value, sub.value), getCollectionID());
}


void IVertexHierarchy::untrackSubVertexRelation(
    VertexID const& parent,
    VertexID const& sub) {
    if (!vertexIDs.contains(parent)) {
        throw graph_error::init(
            std::format(vertex_not_found_msg, "Parent ", parent));
    }
    if (!vertexIDs.contains(sub)) {
        throw graph_error::init(
            std::format(vertex_not_found_msg, "Sub ", sub));
    }
    if (!parentMap.contains(sub) || parentMap.at(sub) != parent) {
        throw graph_error::init(
            std::format("Vertex {} is not a child of {}", sub, parent));
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
        for (auto const& sub_id : nestedInMap.at(id)) {
            result.incl(sub_id);
        }
    }
    return result;
}

hstd::Opt<VertexID> IVertexHierarchy::getParentVertex(
    VertexID const& id) const {
    if (parentMap.contains(id)) { return parentMap.at(id); }
    return hstd::Opt<VertexID>{};
}

void hstd::ext::graph::IVertexHierarchy::write_serial(
    proto::IVertexHierarchy* out,
    IGraph const*            graph) const {
    out->set_stable_id(getStableID());
    for (auto const& v : rootVertices) {
        out->add_root_vertex_ids(graph->getStableId(v));
    }

    for (auto const& [nested, parent] : parentMap) {
        (*out->mutable_parent_map())[graph->getStableId(
            nested)] = graph->getStableId(parent);
    }

    for (auto const& [parent, sub_vertices] : nestedInMap) {
        auto& ref = (*out->mutable_nested_in_map())[graph->getStableId(
            parent)];
        for (auto const& sub : sub_vertices) {
            ref.add_vertices(graph->getStableId(sub));
        }
    }
}

std::optional<VertexID> hstd::ext::graph::IVertexHierarchy::
    getCommonAncestor(VertexIDSet const& ids) const {
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
            if (currentSet.contains(ancestor)) {
                nextCommon.push_back(ancestor);
            }
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

hstd::Vec<VertexID> hstd::ext::graph::IVertexHierarchy::
    getParentChainUntil(VertexID const& start, VertexID const& finish)
        const {
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
    for (auto const& [it, value] : edgeTracker.get_map()) {
        result.incl(value);
    }
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


hstd::ext::graph::EdgeIDVec hstd::ext::graph::AutoSegmentingCollection::
    getSegments(EdgeID const& edge) const {
    auto res = segments_to_edges.get_left(edge);
    hstd::rs::sort(
        res, [this](EdgeID const& lhs, EdgeID const& rhs) -> bool {
            return segment_index.at(lhs) < segment_index.at(rhs);
        });
    return res;
}

void hstd::ext::graph::AutoSegmentingCollection::addEdge(
    EdgeID const& original) {
    auto crossings = hierarchy->getHierarchyCrossings(
        graph->getSource(original), graph->getTarget(original));
    crossings.insert(0, graph->getSource(original));
    crossings.push_back(graph->getTarget(original));
    // ports and segments are arranged in the same order as the
    // original vertex, [source] ---> (port) ---> (port) ---> [target]
    for (auto const& [idx, it] : hstd::rv::zip(
             hstd::rv::iota(0, crossings.size()),
             crossings | hstd::rv::sliding(2))) {
        auto segment_edge = segmented_edges->addEdge(it[0], it[1]);
        segments_to_edges.add_unique(segment_edge, original);
        segment_index.insert_or_assign(segment_edge, idx);
    }

    for (auto const& it :
         hstd::own_view(getSegments(original)) | hstd::rv::sliding(2)) {
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

hstd::Vec<PortID> hstd::ext::graph::AutoSegmentingCollection::
    getSegmentationPorts(EdgeID const& original) {
    return hstd::own_view(getSegments(original)) //
         | hstd::rv::sliding(2)
         | hstd::rv::transform([this](auto const& it) -> PortID {
               return segments_to_ports.at_right({it[0], it[1]});
           })
         | hstd::rs::to<Vec>();
}

EdgeID TrivialHierarchy::trackSubVertexRelation(
    VertexID const&               parent,
    VertexID const&               sub,
    hstd::Opt<TrivialEdge> const& init_vertex) {
    auto id = getNestingEdgeID(parent, sub);
    edgeStore.insert_or_assign(
        id,
        init_vertex.has_value()
            ? init_vertex.value()
            : TrivialEdge{hstd::fmt("{}-{}", parent, sub)});

    IVertexHierarchy::trackSubVertexRelation(id, parent, sub);

    return id;
}
