#pragma once

#include <hstd/ext/graph/base/graph_common.hpp>
#include <hstd/ext/graph/visual/graph_visual.hpp>
#include <hstd/stdlib/MapFormatter.hpp>
#include <hstd/stdlib/OptFormatter.hpp>
#include <hstd/stdlib/VariantFormatter.hpp>
#include <hstd/stdlib/VecFormatter.hpp>

namespace hstd::ext::graph {
class VisualFactory : public IGraphSerialReaderFactory {
  public:
    hstd::SPtr<layout::LayoutRun> run;
    hstd::SPtr<IGraph>            graph;

    VisualFactory(hstd::SPtr<IGraph> const& graph);

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
