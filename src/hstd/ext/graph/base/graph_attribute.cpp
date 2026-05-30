#include "graph_attribute.hpp"

void hstd::ext::graph::IAttribute::readSerial(
    proto::IAttribute const*   in,
    IGraph const*              graph,
    IGraphSerialReaderFactory* factory,
    IAttributeObject const*    vertex) {};

void hstd::ext::graph::IAttribute::writeSerial(
    proto::IAttribute* out,
    IGraph const*      graph) const {};
