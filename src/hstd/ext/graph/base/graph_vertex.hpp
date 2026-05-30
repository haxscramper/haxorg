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
        proto::IVertex const* in,
        IGraph const*         graph) = 0;
#endif
};

struct TrivialVertex : public IVertex {
    explicit TrivialVertex(std::string const& _stable_id)
        : IVertex{_stable_id} {}

    std::string getRepr() const override {
        return hstd::fmt("IVertex({})", getStableId());
    }

    void writeSerial(
        proto::IVertex* out,
        IGraph const*   graph,
        VertexID const& id) const override {
        out->set_type("trivial-vertex");
        out->set_stable_id(getStableId());
        IAttributeObject::writeSerial(out->mutable_attributes(), graph);
    }

    void readSerial(proto::IVertex const* in, IGraph const* graph)
        override {}

    hstd::Vec<hstd::SPtr<IAttribute>> attrs;

    hstd::Vec<hstd::SPtr<IAttribute>> getAttributes() const override {
        return attrs;
    }

    void addAttribute(hstd::SPtr<IAttribute> const& attr) override {
        attrs.push_back(attr);
    }

  public:
    void setAttributes(
        hstd::Vec<hstd::SPtr<IAttribute>> const& attrs) override {
        this->attrs = attrs;
    }
};


} // namespace hstd::ext::graph
