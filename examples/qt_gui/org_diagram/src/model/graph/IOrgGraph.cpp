#include "IOrgGraph.hpp"


void org::graph::IPropertyTracker::addVertex(
    const hstd::value_ptr<IProperty>& property,
    const hstd::value_ptr<IVertexID>& vertex) {
    map[property].push_back(vertex);
}

const hstd::Vec<org::graph::IVertexID::Val>& org::graph::IPropertyTracker::
    getVertices(IProperty::Val const& prop) {
    LOGIC_ASSERTION_CHECK(map.contains(prop), "{}", prop->getRepr());
    return map.at(prop);
}

void org::graph::IGraph::addVertex(const IVertexID::Val& id) {
    for (auto& collection : edges) { collection->addVertex(id); }
}

void org::graph::IGraph::delVertex(const IVertexID::Val& id) {
    for (auto& collection : edges) { collection->delVertex(id); }
}

void org::graph::IEdgeCollection::addEdge(const IEdgeID::Val& id) {
    edges[IVertexID::Val(id->getSource())][IVertexID::Val(id->getTarget())]
        .push_back(id);
}

void org::graph::IEdgeCollection::delEdge(const IEdgeID::Val& id) {
    auto& vec = edges.at(IVertexID::Val(id->getSource()))
                    .at(IVertexID::Val(id->getTarget()));
    auto it = vec.indexOf(id);
    LOGIC_ASSERTION_CHECK(it != -1, "{}", id->getRepr());
    vec.erase(vec.begin() + it);
}
