#include "DiaGraph.hpp"

hstd::Vec<org::graph::Edge> DiaHierarchyEdgeCollection::getOutgoing(
    const org::graph::VertexID& vert) {
    hstd::Vec<org::graph::Edge> res;
    for (auto const& sub :
         DiaAdapter{graph->getVertex(vert).uniq, tree_context}.sub(true)) {
        res.push_back(org::graph::Edge(vert, graph->getID(sub.uniq()), 0));
    }
    HSLOG_DEBUG("get outgoing {}", res);
    return res;
}

json DiaHierarchyEdgeCollection::getEdgeSerial(
    const org::graph::EdgeID& id) const {
    auto const& e = getEdge(id);
    return hstd::to_json_eval(SerialSchema{
        .edgeId      = std::format("{}", std::hash<org::graph::Edge>{}(e)),
        .sourceId    = graph->getVertex(e.source).getStableId(),
        .targetId    = graph->getVertex(e.target).getStableId(),
        .bundleIndex = e.bundleIndex,
    });
}

json DiaGraph::getVertexSerial(const org::graph::VertexID& id) const {
    return hstd::to_json_eval(DiaGraph::SerialSchema{
        .vertexId = getVertex(id).getStableId(),
    });
}
