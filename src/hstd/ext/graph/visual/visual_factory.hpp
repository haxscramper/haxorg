#pragma once

#include <hstd/ext/graph/base/graph_common.hpp>
#include <hstd/ext/graph/visual/graph_visual.hpp>
#include <hstd/ext/hstd_serde_dispatch.hpp>
#include <hstd/stdlib/MapFormatter.hpp>
#include <hstd/stdlib/OptFormatter.hpp>
#include <hstd/stdlib/VariantFormatter.hpp>
#include <hstd/stdlib/VecFormatter.hpp>

#include <hstd/ext/hstd_serde_dispatch.hpp>
#include <src/hstd/ext/graph/visual/graph_graphviz.pb.h>
#include <src/hstd/ext/graph/visual/graph_kiwi.pb.h>

namespace hstd::serde {

//
}

namespace hstd::ext::graph {

using VisualAttributePayloadTypes = boost::mp11::mp_list<
    hstd::ext::graph::gv::proto::GroupAttributePayload,
    hstd::ext::graph::gv::proto::EdgeAttributePayload,
    hstd::ext::graph::gv::proto::NodeAttributePayload,
    hstd::ext::graph::kw::proto::KiwiVertexVisualAttributePayload,
    hstd::ext::graph::kw::proto::KiwiGroupVisualAttributePayload,
    hstd::ext::graph::kw::proto::KiwiEdgeVisualAttributePayload
    //
    >;


class VisualFactory : public IGraphSerialReaderFactory {
  public:
    hstd::SPtr<layout::LayoutRun> run;
    hstd::SPtr<IGraph>            graph;

    VisualFactory(hstd::SPtr<IGraph> const& graph) : graph{graph} {}

    hstd::SPtr<IVertexHierarchy> newVertexHierarchy(
        proto::IVertexHierarchy const* in) override;

    hstd::SPtr<IEdgeCollection> newEdgeCollection(
        proto::IEdgeCollection const* in) override;

    hstd::SPtr<IPortCollection> newPortCollection(
        proto::IPortCollection const* in) override;

    hstd::SPtr<IAttribute> newAttribute(
        proto::IAttribute const* in,
        IGraph const*            graph,
        IAttributeObject const*  parent) override;

    hstd::SPtr<IVertex> newVertex(proto::IVertex const* in) override;

    hstd::SPtr<layout::IConstraint> newConstraint(proto::IConstraint const* in) override;

    hstd::SPtr<IEdge> newEdge(proto::IEdge const* edge) override;

    hstd::SPtr<IPort> newPort(proto::IPort const* port) override;
};

} // namespace hstd::ext::graph
