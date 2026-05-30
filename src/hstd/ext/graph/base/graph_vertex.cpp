#include "graph_vertex.hpp"

void hstd::ext::graph::IVertex::writeSerial(
    proto::IVertex* out,
    IGraph const*   graph,
    VertexID const& self_id) const {
    out->set_stable_id(getStableId());
    IAttributeObject::writeSerial(out->mutable_attributes(), graph);
}

void hstd::ext::graph::IVertex::readSerial(
    proto::IVertex const*      in,
    IGraph const*              graph,
    IGraphSerialReaderFactory* factory) {
    IAttributeObject::readSerial(&in->attributes(), graph, factory, this);
}
