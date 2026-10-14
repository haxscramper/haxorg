#pragma once

#include <hstd_cpp_diagram_lib/graph_visual.hpp>
#include <hstd_cpp_lib/graph/graph_common.hpp>
#include <hstd_cpp_lib/proto_serde/hstd_serde_dispatch.hpp>
#include <hstd_cpp_lib/stdlib/formatting/specializations/MapFormatter.hpp>
#include <hstd_cpp_lib/stdlib/formatting/specializations/OptFormatter.hpp>
#include <hstd_cpp_lib/stdlib/formatting/specializations/VariantFormatter.hpp>
#include <hstd_cpp_lib/stdlib/formatting/specializations/VecFormatter.hpp>

#include <hstd_cpp_diagram_lib/graph_avoid.pb.h>
#include <hstd_cpp_diagram_lib/graph_graphviz.pb.h>
#include <hstd_cpp_diagram_lib/graph_kiwi.pb.h>
#include <hstd_cpp_lib/proto_serde/hstd_serde_dispatch.hpp>

namespace hstd::serde {

template <>
struct DispatchProtoPayload<hstd::ext::graph::proto::IAttribute> {
    static google::protobuf::Any const& getPayload(
        hstd::ext::graph::proto::IAttribute const& value) {
        return value.payload();
    }
};

} // namespace hstd::serde

namespace hstd::ext::graph {

using EdgeLayoutAttributePayloadTypes = boost::mp11::mp_list<
    // graphviz
    hstd::ext::graph::layout::proto::IEdgeLayoutAttributePayload,
    // kiwi, top-level unbound edges
    hstd::ext::graph::avoid::proto::EdgeLayoutAttributePayload
    //
    >;

using NodeVisualAttributePayloadTypes = boost::mp11::mp_list<
    hstd::ext::graph::gv::proto::NodeAttributePayload,
    hstd::ext::graph::kw::proto::KiwiVertexVisualAttributePayload
    //
    >;

using EdgeVisualAttributePayloadTypes = boost::mp11::mp_list<
    hstd::ext::graph::gv::proto::EdgeAttributePayload,
    hstd::ext::graph::kw::proto::KiwiEdgeVisualAttributePayload
    //
    >;

using GroupVisualAttributePayloadTypes = boost::mp11::mp_list<
    hstd::ext::graph::gv::proto::GroupAttributePayload,
    hstd::ext::graph::kw::proto::KiwiGroupVisualAttributePayload
    //
    >;

using VisualAttributePayloadTypes = boost::mp11::mp_append<
    EdgeVisualAttributePayloadTypes,
    NodeVisualAttributePayloadTypes,
    GroupVisualAttributePayloadTypes
    //
    >;


using ConstraintPayloadTypes = boost::mp11::mp_list<
    kw::proto::KiwiAlignConstraintPayload,
    kw::proto::KiwiSeparateConstraintPayload,
    kw::proto::KiwiMultiSeparateConstraintPayload,
    kw::proto::KiwiRelativeConstraintPayload,
    kw::proto::KiwiLinearConstraintPayload,
    kw::proto::KiwiEvenGapConstraintPayload
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
