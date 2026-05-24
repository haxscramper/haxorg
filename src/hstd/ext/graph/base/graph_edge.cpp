#include "graph_edge.hpp"
#include <hstd/stdlib/Ranges.hpp>


using namespace hstd::ext::graph;


std::size_t IEdge::getHash() const {
    std::size_t result = 0;
    return result;
}

bool IEdge::isEqual(IGraphObjectBase const* other) const {
    auto other_edge = dynamic_cast<IEdge const*>(other);
    return other->isInstance<IEdge>();
}


EdgeIDSet IEdgeCollection::getOutgoing(VertexID const& vert) const {
    EdgeIDSet result;
    if (incidence.contains(vert)) {
        for (const auto& [target, edges] : incidence.at(vert)) {
            for (const auto& edge : edges) { result.incl(edge); }
        }
    }
    return result;
}

EdgeIDSet IEdgeCollection::getIncoming(VertexID const& vert) const {
    EdgeIDSet result;
    if (incoming_from.contains(vert)) {
        for (const auto& source : incoming_from.at(vert)) {
            if (incidence.contains(source)
                && incidence.at(source).contains(vert)) {
                for (const auto& edge : incidence.at(source).at(vert)) {
                    result.incl(edge);
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
    EdgeIDSet edgesToRemove;

    if (incidence.contains(vert)) {
        for (const auto& [target, edges] : incidence.at(vert)) {
            for (const auto& edge : edges) { edgesToRemove.incl(edge); }
        }
    }

    if (incoming_from.contains(vert)) {
        for (const auto& source : incoming_from.at(vert)) {
            if (incidence.contains(source)
                && incidence.at(source).contains(vert)) {
                for (const auto& edge : incidence.at(source).at(vert)) {
                    edgesToRemove.incl(edge);
                }
            }
        }
    }

    for (const auto& edge : edgesToRemove) { untrackEdge(edge); }

    incidence.erase(vert);
    incoming_from.erase(vert);
    return DependantDeletion{.vertices = {vert}, .edges = edgesToRemove};
}


void hstd::ext::graph::IEdgeCollection::trackEdge(
    EdgeID const&   id,
    VertexID const& source,
    VertexID const& target) {
    LOGIC_ASSERTION_CHECK_FMT(
        hasEdge(id),
        "Edge incidence tracking must be done after the edge ID is "
        "already associated with an object in the edge collection. "
        "hasEdge({}) = false",
        id);

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

    source_target.insert_or_assign(
        id, hstd::Pair<VertexID, VertexID>{source, target});
}


void IEdgeCollection::untrackEdge(EdgeID const& id) {
    VertexID source = getSource(id);
    VertexID target = getTarget(id);

    if (incidence.contains(source)
        && incidence.at(source).contains(target)) {
        auto& edges = incidence.at(source).at(target);
        std::erase(edges, id);
        if (edges.empty()) {
            incidence.at(source).erase(target);
            if (incidence.at(source).empty()) { incidence.erase(source); }
        }
    }

    if (incoming_from.contains(target)) {
        auto& sources = incoming_from.at(target);
        std::erase(sources, source);
        if (sources.empty()) { incoming_from.erase(target); }
    }
}

std::string IEdgeProvider::getStableID() const {
    return hstd::fmt("EdgeProvider-{}", getCollectionID().t);
}

hstd::ext::graph::VertexIDSet hstd::ext::graph::IEdgeProvider::getOutNodes(
    VertexID id) const {
    return VertexIDSet::FromIterable(
        hstd::own_view(getOutgoing(id))
        | hstd::rv::transform(
            [&](EdgeID e) -> VertexID { return getTarget(e); }));
}
hstd::ext::graph::VertexIDSet hstd::ext::graph::IEdgeProvider::getInNodes(
    VertexID id) const {
    return VertexIDSet::FromIterable(
        hstd::own_view(getIncoming(id))
        | hstd::rv::transform(
            [&](EdgeID e) -> VertexID { return getTarget(e); }));
}

EdgeCollectionID IEdgeProvider::edgeCategoryFromEdge(EdgeID const& id) {
    return EdgeCollectionID(hstd::u16(id.getMask()));
}

EdgeCollectionID IEdgeProvider::hierarchyIdFromEdge(EdgeID const& id) {
    return EdgeCollectionID(hstd::u16(id.getMask()));
}

EdgeIDSet IEdgeCollection::getEdges() const {
    EdgeIDSet result;
    for (const auto& [source, targets] : incidence) {
        for (const auto& [target, edges] : targets) {
            for (const auto& edge : edges) { result.incl(edge); }
        }
    }
    return result;
}
