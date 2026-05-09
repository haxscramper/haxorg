#pragma once

#include <hstd/ext/graph/graph_base.hpp>
#include <hstd/ext/graph/adaptagrams_common.hpp>
#include <libdialect/hola.h>
#include <hstd/ext/bimap_wrap.hpp>
#include <hstd/stdlib/algorithms.hpp>
#include <hstd/ext/logger.hpp>
#include <hstd/ext/graph/graph_vpsc.hpp>
namespace hstd::ext::graph::cst {

class AvoidPort : public IPort {
  public:
    std::size_t getHash() const override { return 0; }

    bool isEqual(IGraphObjectBase const* other) const override {
        return true;
    }

    std::string getRepr() const override { return ""; }

    hstd::Vec<hstd::SPtr<IAttribute>> attrs;

    hstd::Vec<hstd::SPtr<IAttribute>> getAttributes() const override {
        return attrs;
    }

    void addAttribute(hstd::SPtr<IAttribute> const& attr) override {
        attrs.push_back(attr);
    }

    void setAttributes(
        hstd::Vec<hstd::SPtr<IAttribute>> const& attrs) override {
        this->attrs = attrs;
    }
};

class AvoidPortVisualAttribute : public layout::IPortVisualAttribute {
  public:
    DECL_DESCRIBED_ENUM(VisibilityDirection, Left, Right, Top, Bottom);
    VisibilityDirection visibility;
    hstd::Opt<double>   edgeOffset;
};

class AvoidEdgeLayoutAttribute : public layout::IEdgeLayoutAttribute {
  public:
    geometry::Path path;
    AvoidEdgeLayoutAttribute(geometry::Path const& path) : path{path} {}
    Path getPath() const override { return path; }
};

class AvoidPortLayoutAttribute : public layout::IPortLayoutAttribute {
  public:
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
    using VisibilityDirection = AvoidPortVisualAttribute::
        VisibilityDirection;
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
    PortCollectionID getCategory() const override {
        return hstd::ext::graph::PortCollectionID(
            hstd::hash_bits<15>(typeid(this).hash_code()));
    }

    const IPort* getPort(PortID pid) const override {
        return &portStore.at(pid);
    }

    PortID addPort(VertexID vertex, EdgeID edge, bool is_start) {
        auto id = portStore.add(AvoidPort{});
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
    VpscRectTracker* rects;
    // layout::IGroupVisualAttribute const* group;
    /// \brief List of edges for layout
    EdgeIDSet edge_set;
    /// \brief Set of vertices to take into account as obstacles for layout
    VertexIDSet        vertex_set;
    layout::LayoutRun* run;
    /// \brief Output value for edge routing: write write the value out to
    /// this.
    layout::IPlacementAlgorithm::Result* intermediate_placement;

    /// \brief Store the list of shapes created during the edge routing
    /// process, the shapes are managed by the avoid router object
    hstd::UnorderedMap<VertexID, Avoid::ShapeRef*> shapes;
    /// \brief List of connections for routing, created during routing
    /// process
    hstd::UnorderedMap<EdgeID, Avoid::ConnRef*> connections;
    hstd::SPtr<Avoid::Router>                   router;

    struct Result {
        hstd::SPtr<AvoidPortCollection> layoutPorts;
    };

    Result routeEdges();
};
} // namespace hstd::ext::graph::cst
