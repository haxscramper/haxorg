#pragma once

#include "graph_common.hpp"
#include "graph_attribute.hpp"

namespace hstd::ext::graph {

struct IVertex
    : public IGraphObjectBase
    , public virtual IAttributeObject {
    using id_type = VertexID;
    DESC_FIELDS(IVertex, ());

    using IGraphObjectBase::IGraphObjectBase;

#ifdef ORG_BUILD_WITH_PROTOBUF
    virtual void writeSerial(
        proto::IVertex* out,
        IGraph const*   graph,
        VertexID const& self_id) const;

    virtual void readSerial(
        proto::IVertex const*      in,
        IGraph const*              graph,
        IGraphSerialReaderFactory* factory) = 0;
#endif
};

struct TrivialVertex
    : public IVertex
    , public virtual TrivialAttributeObject {
    explicit TrivialVertex(std::string const& _stable_id)
        : IVertex{_stable_id} {}

    std::string getRepr() const override {
        return hstd::fmt("IVertex({})", getStableId());
    }

#if ORG_BUILD_WITH_PROTOBUF
    void writeSerial(
        proto::IVertex* out,
        IGraph const*   graph,
        VertexID const& id) const override {
        IVertex::writeSerial(out, graph, id);
        out->mutable_payload()->PackFrom(proto::TrivialVertexPayload{});
    }

    void readSerial(
        proto::IVertex const*      in,
        IGraph const*              graph,
        IGraphSerialReaderFactory* factory) override {
        IVertex::readSerial(in, graph, factory);
    }
#endif
};


} // namespace hstd::ext::graph
