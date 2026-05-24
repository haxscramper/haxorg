#pragma once

#include "graph_common.hpp"
#include "graph_attribute.hpp"

namespace hstd::ext::graph {

struct IVertex
    : public IGraphObjectBase
    , public virtual IAttributeObject {
    using id_type = VertexID;
    DESC_FIELDS(IVertex, ());

#ifdef ORG_BUILD_WITH_PROTOBUF
    virtual void write_serial(
        proto::IVertex* out,
        IGraph const*   graph,
        VertexID const& self_id) const = 0;
#endif
};

struct TrivialVertex : public IVertex {
    VertexID selfId;

    TrivialVertex(VertexID selfId) : selfId{selfId} {}

    hstd::Opt<hstd::Str> stableIdOverride;
    std::string          getStableId() const override {
        if (stableIdOverride) {
            return stableIdOverride.value();
        } else {
            return hstd::fmt("IVertex-{}", selfId);
        }
    }

    std::size_t getHash() const override {
        std::size_t result;
        hstd::hax_hash_combine(result, selfId);
        return result;
    }

    bool isEqual(IGraphObjectBase const* other) const override {
        return this->selfId
            == dynamic_cast<TrivialVertex const*>(other)->selfId;
    }

    std::string getRepr() const override {
        return hstd::fmt("IVertex({})", selfId);
    }

    void write_serial(
        proto::IVertex* out,
        IGraph const*   graph,
        VertexID const& id) const override {
        out->set_type("trivial-vertex");
        out->set_stable_id(getStableId());
        IAttributeObject::write_serial(out->mutable_attributes());
    }

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
