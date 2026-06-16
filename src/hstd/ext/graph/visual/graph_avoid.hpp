#pragma once

#if ORG_BUILD_WITH_ADAPTAGRAMS

#    include "hstd/ext/hstd_serde.hpp"
#    include "hstd/system/exceptions.hpp"
#    include <hstd/ext/bimap_wrap.hpp>
#    include <hstd/ext/graph/base/graph_base.hpp>
#    include <hstd/ext/graph/visual/adaptagrams_common.hpp>
#    include <hstd/ext/graph/visual/graph_visual.hpp>
#    include <hstd/ext/graph/visual/graph_vpsc.hpp>
#    include <hstd/ext/logger.hpp>
#    include <hstd/stdlib/algorithms.hpp>

#    include "src/hstd/ext/graph/visual/graph_avoid.pb.h"
#    include <hstd/ext/geometry/hstd_geometry_serde.hpp>
#    include <hstd/ext/geometry/hstd_visual_serde.hpp>

namespace hstd::ext::graph::cst {

class AvoidPort
    : public IPort
    , public virtual TrivialAttributeObject {
  public:
    using IPort::IPort;
};

class AvoidPortVisualAttribute : public layout::IPortVisualAttribute {
  public:
#    if ORG_BUILD_WITH_PROTOBUF
    void writeSerial(proto::IAttribute* out, IGraph const* graph) const override {
        hstd::ext::graph::avoid::proto::PortVisualAttributePayload load;
        load.set_visibility(static_cast<avoid::proto::EdgeVisibility>(visibility));
        if (edgeOffset) { load.set_edge_offset(edgeOffset.value()); }
        out->mutable_payload()->PackFrom(load);
    }

    void readSerial(
        proto::IAttribute const*   in,
        IGraph const*              graph,
        IGraphSerialReaderFactory* factory,
        IAttributeObject const*    vertex) override {
        hstd::ext::graph::avoid::proto::PortVisualAttributePayload load;
        in->payload().UnpackTo(&load);
        visibility = static_cast<VisibilityDirection>(load.visibility());
        if (load.has_edge_offset()) { edgeOffset = load.edge_offset(); }
    }
#    endif

    DECL_DESCRIBED_ENUM(VisibilityDirection, Left, Right, Top, Bottom);
    VisibilityDirection visibility;
    hstd::Opt<double>   edgeOffset;
};

class AvoidEdgeLayoutAttribute : public layout::IEdgeLayoutAttribute {
  public:
    std::string getRepr() const override { return "AvoidEdgeLayoutAttribute"; }

    void writeSerial(proto::IAttribute* out, IGraph const* graph) const override {
        avoid::proto::EdgeLayoutAttributePayload load;
        hstd::serde::write_serde(
            load.mutable_base()->mutable_group(),
            // TODO: See [[nil-visual-id-for-serialization]]
            getVisual(EdgeID::Nil()));

        hstd::serde::write_serde(load.mutable_base()->mutable_path(), getPath());

        out->mutable_payload()->PackFrom(load);
    }

    void readSerial(
        proto::IAttribute const*   in,
        IGraph const*              graph,
        IGraphSerialReaderFactory* factory,
        IAttributeObject const*    vertex) override {
        logic_todo_impl();
    }

    geometry::Path path;
    AvoidEdgeLayoutAttribute(geometry::Path const& path) : path{path} {}
    Path getPath() const override { return path; }
};

class AvoidPortLayoutAttribute : public layout::IPortLayoutAttribute {
  public:
    std::string getRepr() const override { return "AvoidPortLayoutAttribute"; }

    void writeSerial(proto::IAttribute* out, IGraph const* graph) const override {
        avoid::proto::PortLayoutAttributePayload load;

        hstd::serde::write_serde(
            load.mutable_base()->mutable_group(),
            getVisual(
                // FIXME: using port ID Nil as a temporary replacement. Not
                // clear if attribute serialization has any reason to know
                // the parent element ID in the first place. Additionally,
                // this will mess up the signature of the writeSerial
                // method for the attribute: I either need to pass a
                // Variant of different ID types, or erase types, or do
                // something similar. It is a mess. The port ID in the
                // visualization is primarily intended to be used for
                // debugging purposes, to know which ID is being shown.
                // <<nil-visual-id-for-serialization>>
                PortID::Nil()));
        out->mutable_payload()->PackFrom(load);
    }

    void readSerial(
        proto::IAttribute const*   in,
        IGraph const*              graph,
        IGraphSerialReaderFactory* factory,
        IAttributeObject const*    vertex) override {
        logic_todo_impl();
    };

    Rect getBBox() const override {
        return Rect::FromCenterWH(Point(xOffset, yOffset), width, height);
    }

    visual::VisGroup getVisual(PortID const& id) const override {
        visual::VisGroup res;
        res.elements.push_back(
            visual::VisElement{visual::VisElement::RectShape{getBBox()}});
        return res;
    }

    DECL_DESCRIBED_ENUM(Placement, Unspecified, Proportional, Absolute);
    using VisibilityDirection = AvoidPortVisualAttribute::VisibilityDirection;
    VisibilityDirection visibility;
    Placement           placement;
    double              xOffset;
    double              yOffset;
    double              width  = 1;
    double              height = 1;

    Avoid::ConnEnd             connection;
    Avoid::ShapeConnectionPin* pin;
};


class AvoidPortCollection : public IPortCollection {
    hstd::UnorderedIncrementalStore<PortID, AvoidPort> portStore;

  public:
    PortCollectionID getCollectionID() const override {
        return hstd::ext::graph::PortCollectionID(
            hstd::hash_bits<15>(typeid(this).hash_code()));
    }

    const IPort* getPort(PortID pid) const override { return &portStore.at(pid); }

    PortID addPort(VertexID vertex, EdgeID edge, bool is_start) {
        auto id = portStore.add(AvoidPort{hstd::fmt1(portStore.getNextId())});
        IPortCollection::addPort(vertex, edge, is_start, id);
        return id;
    }
};

class AvoidRouterAlgorithm {
    // TODO: support additional list of obstacle rectangles for layout.

    // TODO: checkpoint creation for edges, using absolute manual placement
    // and by creating intersection points along some edges (like
    // orthogonal line from the bottom of some rectangle and the line's
    // intersection with the surrounding subgroup).
  public:
    /// \brief put a fake buffer around each shape so the edges would not
    /// run perfectly flush against the nodes.
    hstd::Opt<int> shapeBufferDistance = 1;
    /// \brief Shared list of rectangles for avoidance. Rectangles are
    /// placed on the flat canvas and are not moved or altered during edge
    /// routing.
    /// \brief List of edges for layout
    EdgeIDSet edge_set;
    /// \brief Set of vertices to take into account as obstacles for layout
    VertexIDSet                                  vertex_set;
    layout::LayoutRun*                           run;
    hstd::UnorderedMap<VertexID, geometry::Rect> rects;

    /// \brief Store the list of shapes created during the edge routing
    /// process, the shapes are managed by the avoid router object
    hstd::UnorderedMap<VertexID, Avoid::ShapeRef*> shapes;
    /// \brief List of connections for routing, created during routing
    /// process
    hstd::UnorderedMap<EdgeID, Avoid::ConnRef*> connections;
    hstd::SPtr<Avoid::Router>                   router;

    hstd::Str routing_run_name;

    struct Result {
        hstd::SPtr<AvoidPortCollection>                                      layoutPorts;
        hstd::UnorderedMap<EdgeID, hstd::SPtr<layout::IEdgeLayoutAttribute>> edges;
    };

    Result routeEdges();
};
} // namespace hstd::ext::graph::cst
#endif
