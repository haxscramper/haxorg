#include "graph_vertex.hpp"

#if ORG_BUILD_WITH_PROTOBUF
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
    OP_TRACER_MESSAGE_SCOPE(factory, "IVertex::readSerial");
    IAttributeObject::readSerial(&in->attributes(), graph, factory, this);
    OP_TRACER_MESSAGE(factory, "read {} attributes", getAttributes().size());
}

#endif
