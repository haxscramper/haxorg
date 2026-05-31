#include "graph_attribute.hpp"

void hstd::ext::graph::IAttribute::readSerial(
    proto::IAttribute const*   in,
    IGraph const*              graph,
    IGraphSerialReaderFactory* factory,
    IAttributeObject const*    vertex) {};

void hstd::ext::graph::IAttribute::writeSerial(
    proto::IAttribute* out,
    IGraph const*      graph) const {};

hstd::Vec<hstd::Str> hstd::ext::graph::IAttributeObject::getAttributeRepr()
    const {
    hstd::Vec<hstd::Str> result;
    for (auto const& a : getAttributes()) {
        result.push_back(a->getRepr());
    }
    return result;
}

void hstd::ext::graph::IAttributeObject::writeSerial(
    ::google::protobuf::RepeatedPtrField<proto::IAttribute>* out,
    IGraph const*                                            graph) const {
    for (auto const& attr : getAttributes()) {
        attr->writeSerial(out->Add(), graph);
    }
}

void hstd::ext::graph::IAttributeObject::readSerial(
    ::google::protobuf::RepeatedPtrField<
        ::hstd::ext::graph::proto::IAttribute> const* in,
    IGraph const*                                     graph,
    IGraphSerialReaderFactory*                        factory,
    IAttributeObject const*                           vertex) {
    OP_TRACER_MESSAGE_SCOPE(factory, "IAttributeObject::readSerial");
    hstd::Vec<hstd::SPtr<IAttribute>> attrs;
    for (auto const& a : *in) {
        auto attr = factory->newAttribute(&a, graph, vertex);
        attr->readSerial(&a, graph, factory, vertex);
        attrs.push_back(attr);
    }
    OP_TRACER_MESSAGE(factory, "Read {} attributes", attrs.size());
    setAttributes(attrs);
}
