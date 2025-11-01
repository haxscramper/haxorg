#include "DiaGraph.hpp"

hstd::Vec<org::graph::Edge> DiaHierarchyEdgeCollection::getOutgoing(
    const org::graph::VertexID& vert) {
    hstd::Vec<org::graph::Edge> res;
    for (auto const& sub :
         DiaAdapter{graph->getVertex(vert).uniq, tree_context}.sub(true)) {
        res.push_back(
            org::graph::Edge(vert, graph->getID(sub.uniq()), 0));
    }
    return res;
}
