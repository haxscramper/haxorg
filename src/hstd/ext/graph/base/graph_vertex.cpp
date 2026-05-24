#include "graph_vertex.hpp"

void hstd::ext::graph::IVertex::write_serial(
    proto::IVertex* out,
    IGraph const*   graph,
    VertexID const& self_id) const {
    out->set_stable_id(getStableId());
}
