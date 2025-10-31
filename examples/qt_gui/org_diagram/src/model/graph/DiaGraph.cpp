#include "DiaGraph.hpp"

hstd::Vec<org::graph::IEdgeID::Val> DiaHierarchyEdgeCollection::
    getOutgoing(const org::graph::IVertexID::Val& vert) {
    auto dia_vert = vert.cast<DiaGraphVertex>();
    hstd::Vec<org::graph::IEdgeID::Val> res;
    if (dia_vert) {
        for (auto const& sub :
             DiaAdapter{vert.cast_raw<DiaGraphVertex>()->id, tree_context}
                 .sub(true)) {
            res.push_back(org::graph::IEdgeID::Val::init_as<DiaGraphEdge>(
                dia_vert, DiaGraphVertex(sub.uniq()), 0));
        }
    }
    return res;
}
