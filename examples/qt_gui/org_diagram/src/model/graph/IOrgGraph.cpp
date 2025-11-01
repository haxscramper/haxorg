#include "IOrgGraph.hpp"


void org::graph::IGraph::trackVertex(const VertexID& id) {
    for (auto& collection : collections) { collection->addVertex(id); }
}

void org::graph::IGraph::untrackVertex(const VertexID& id) {
    for (auto& collection : collections) { collection->delVertex(id); }
}

void org::graph::IGraph::trackVertexList(const hstd::Vec<VertexID>& ids) {
    for (auto const& id : ids) {
        for (auto& track : trackers) { track->addVertex(id); }
    }

    for (auto const& id : ids) {
        for (auto& collection : collections) { collection->addVertex(id); }
    }
}

void org::graph::IGraph::untrackVertexList(
    const hstd::Vec<VertexID>& ids) {

    for (auto const& id : ids) {
        for (auto& collection : collections) { collection->delVertex(id); }
    }

    for (auto const& id : ids) {
        for (auto& track : trackers) { track->delVertex(id); }
    }
}

json org::graph::IGraph::getGraphSerial() const {
    IGraph::SerialSchema res{};
    for (auto const& collection : collections) {
        for (auto const& edge : collection->getEdges()) {
            res.edges.push_back(collection->getEdgeSerial(edge));
        }
    }

    for (auto const& vertex : getVertices()) {
        res.vertices.push_back(getVertexSerial(vertex));
    }

    return hstd::to_json_eval(res);
}

org::graph::EdgeID org::graph::IEdgeCollection::addEdge(const Edge& id) {
    auto res_id = EdgeID::FromMaskedIdx(
        edges.get_map().size(), getCategory().t);
    edges.add_unique(res_id, id);
    incidence[id.source][id.target].push_back(res_id);
    return res_id;
}

void org::graph::IEdgeCollection::delEdge(const EdgeID& id) {
    auto  edge = getEdge(id);
    auto& vec  = incidence.at(edge.source).at(edge.target);
    auto  it   = vec.indexOf(id);
    LOGIC_ASSERTION_CHECK(it != -1, "{}", edge);
    vec.erase(vec.begin() + it);
}

org::graph::EdgeID org::graph::IEdgeCollection::getID(
    const Edge& edge) const {
    return edges.at_left(edge);
}

const org::graph::Edge& org::graph::IEdgeCollection::getEdge(
    const EdgeID& id) const {
    return edges.at_right(id);
}


hstd::Vec<org::graph::EdgeID> org::graph::IEdgeCollection::addVertex(
    const VertexID& id) {
    hstd::Vec<org::graph::EdgeID> res;
    for (auto const& e : getOutgoing(id)) { res.push_back(addEdge(e)); }
    return res;
}

void org::graph::IEdgeCollection::delVertex(const VertexID& id) {
    for (auto const& e : getOutgoing(id)) { delEdge(getID(e)); }
}
