#include "IOrgGraph.hpp"


void org::graph::IPropertyTracker::addVertex(
    const hstd::value_ptr<IProperty>& property,
    const hstd::value_ptr<IVertexID>& vertex) {
    if (map.contains(property)) {
        map.at(property).push_back(vertex.copy());
    } else {
        map[property.copy()].push_back(vertex.copy());
    }
}

const hstd::Vec<org::graph::IVertexID::Val>& org::graph::IPropertyTracker::
    getVertices(IProperty::Val const& prop) {
    LOGIC_ASSERTION_CHECK(map.contains(prop), "{}", prop->getRepr());
    return map.at(prop);
}

void org::graph::IGraph::addVertex(const IVertexID::Val& id) {
    for (auto& collection : collections) { collection->addVertex(id); }
}

void org::graph::IGraph::delVertex(const IVertexID::Val& id) {
    for (auto& collection : collections) { collection->delVertex(id); }
}

void org::graph::IGraph::addVertexList(
    const hstd::Vec<IVertexID::Val>& ids) {
    for (auto const& id : ids) {
        for (auto& track : trackers) { track->addVertex(id); }
    }

    for (auto const& id : ids) {
        for (auto& collection : collections) { collection->addVertex(id); }
    }
}

void org::graph::IGraph::delVertexList(
    const hstd::Vec<IVertexID::Val>& ids) {

    for (auto const& id : ids) {
        for (auto& collection : collections) { collection->delVertex(id); }
    }

    for (auto const& id : ids) {
        for (auto& track : trackers) { track->delVertex(id); }
    }
}

void org::graph::IEdgeCollection::addEdge(const IEdgeID::Val& id) {
    auto source = IVertexID::Val(id->getSource());
    auto target = IVertexID::Val(id->getTarget());
    if (!edges.contains(source)) { edges[source.copy()]; }
    if (!edges.at(source).contains(target)) {
        edges.at(source)[target.copy()];
    }

    edges.at(source).at(target).push_back(id);
}

void org::graph::IEdgeCollection::delEdge(const IEdgeID::Val& id) {
    auto& vec = edges.at(IVertexID::Val(id->getSource()))
                    .at(IVertexID::Val(id->getTarget()));
    auto it = vec.indexOf(id);
    LOGIC_ASSERTION_CHECK(it != -1, "{}", id->getRepr());
    vec.erase(vec.begin() + it);
}

void org::graph::IEdgeCollection::addVertex(const IVertexID::Val& id) {
    for (auto const& e : getOutgoing(id)) { addEdge(e); }
}

void org::graph::IEdgeCollection::delVertex(const IVertexID::Val& id) {
    for (auto const& e : getOutgoing(id)) { delEdge(e); }
}
