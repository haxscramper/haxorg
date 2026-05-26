#pragma once

#include <hstd/ext/graph/base/graph_base.hpp>
#include "hstd/stdlib/TraceBase.hpp"

namespace hstd::ext::graph {

/// \brief Generic interface to perform mixed-layout graph visualization
///
/// Interface classes in this namespace define a generic algorithm for
/// graph layout with support for multiple layout solutions in the same
/// visualization.
///
/// Terminology used
///
/// - **backend** refers to the particular set of derived classes intended
///   to wrap a graph visualization library/tool like graphviz, ELK,
///   Adaptagrams
namespace layout {

struct layout_error : public hstd::CRTP_hexception<layout_error> {};

struct constraint_error
    : public hstd::CRTP_hexception<constraint_error, layout_error> {};

/// \brief Base class for configuring individual edge objects for layout
///
/// Each layout group type will have its own set of visual attributes
/// derived. The attributes may hold any inforamtion, including additional
/// internal data structures necessary to perform layout. For example,
/// graphviz visual attributes will hold the `agnode_t`, `agedge_t` etc
/// objets. The `agraph_t` is held by the `IGroup`-derived object -- there
/// is no visual attribute subclass for a group, as the group itself only
/// exists for the visualization configuration.
///
/// \see ILayoutAttribute for attributes created after the layout is
/// complete.
class IVisualAttribute : public IAttribute {};

class IVertexVisualAttribute : public IVisualAttribute {};
class IEdgeVisualAttribute : public IVisualAttribute {};
class IPortVisualAttribute : public IVisualAttribute {};

/// \brief Base class for all attributes describing post-layout placement
/// and shape information for the graph elements.
class ILayoutAttribute : public IAttribute {
  public:
    /// \brief Original type of the layout element, used for the \refP
    /// VisGroup::original_type field in the \ref LayoutRun::getVisual
    DECL_DESCRIBED_ENUM(Kind, Port, Edge, Vertex, Group);
};

class IPortLayoutAttribute : public ILayoutAttribute {
  public:
    /// \brief position + size relative to parent.
    virtual Rect             getBBox() const = 0;
    virtual visual::VisGroup getVisual(PortID const& selfId) const {
        visual::VisGroup res;
        auto             bb = getBBox();
        res.offset          = bb.upper_left();
        res.custom.setAttr(
            "inkscape:label", hstd::fmt("BASE PORT:{}", selfId));
        res.elements.push_back(
            visual::VisElement{visual::VisElement::RectShape{
                geometry::Rect::FromSize(bb.size())}});
        return res;
    }
};

class IEdgeLayoutAttribute : public ILayoutAttribute {
  public:
    virtual Path             getPath() const = 0;
    virtual visual::VisGroup getVisual(EdgeID const& selfId) const {
        visual::VisGroup result;
        result.elements.push_back(
            visual::VisElement{visual::VisElement::PathShape{getPath()}});
        result.custom.setAttr(
            "inkscape:label", hstd::fmt("BASE EDGE:{}", selfId));
        return result;
    }
};

class IVertexLayoutAttribute : public ILayoutAttribute {
  public:
    /// \brief Vertex bounding box + position relative to the parent
    virtual Rect             getBBox() const = 0;
    virtual visual::VisGroup getVisual(VertexID const& selfId) const {
        visual::VisGroup res;
        res.elements.push_back(
            visual::VisElement{visual::VisElement::RectShape{getBBox()}});
        res.elements.push_back(
            visual::VisElement::FromText(
                hstd::fmt("{}", selfId), getBBox().upper_left()));
        res.custom.setAttr(
            "inkscape:label", hstd::fmt("BASE VERTEX:{}", selfId));
        return res;
    }
};

class IGroupLayoutAttribute : public IVertexLayoutAttribute {
  public:
    /// \brief Change the bounding box of the group layout. Used by the
    /// layout algorithm to move the bounding box when the parent group
    /// re-arranges the placement.
    virtual void setBBox(geometry::Rect const& bbox) = 0;
};


class IGroupVisualAttribute;
class LayoutRun;

class IPlacementAlgorithm {
  public:
    static constexpr hstd::u16 TemporaryLayoutVertexMask = 0b1111'1111;
    /// \brief Result of the placement algorithm execution
    struct Result {
        hstd::UnorderedMap<EdgeID, hstd::SPtr<IEdgeLayoutAttribute>> edges;
        hstd::UnorderedMap<VertexID, hstd::SPtr<IVertexLayoutAttribute>>
            vertices;
        hstd::UnorderedMap<PortID, hstd::SPtr<IPortLayoutAttribute>> ports;
    };

    hstd::SPtr<LayoutRun> run;

    /// \brief Execute single layout run on the input group. If the group
    /// contains sub-groups with different layout algorithms, their
    /// placement should already be present in the \ref
    /// LayoutRun::result.
    virtual Result runSingleLayout(VertexID const& group) = 0;

    IPlacementAlgorithm(hstd::SPtr<LayoutRun> run) : run{run} {}
};

class IConstraint {
  public:
    virtual hstd::Vec<VertexID> getAllVertices() const = 0;
};


class IGroupVisualAttribute : public IVertexVisualAttribute {
  protected:
    hstd::Opt<hstd::SPtr<IPlacementAlgorithm>> algorithm;


  public:
    /// \brief Optional instance of the layout algorithm to be executed on
    /// the current group.
    hstd::Vec<hstd::SPtr<IConstraint>> constraints;
    hstd::SPtr<LayoutRun>              run;


    virtual void setOuterPadding(geometry::Padding const& pad)   = 0;
    virtual hstd::Opt<geometry::Padding> getOuterPadding() const = 0;

    hstd::SPtr<IGraph> getGraph() const;

    template <typename T = IPlacementAlgorithm>
    hstd::SPtr<T> getAlgorithm() const {
        auto result = std::dynamic_pointer_cast<T>(algorithm.value());
        hstd::logic_assertion_check_not_nil(result);
        return result;
    }

    template <typename T, typename... Args>
    std::shared_ptr<T> addConstraint(Args&&... args) {
        auto res = std::make_shared<T>(std::forward<Args>(args)...);
        constraints.push_back(res);
        return res;
    }

    bool hasAlgorithm() const { return algorithm.has_value(); }

    virtual std::string getStableId() const = 0;

    IGroupVisualAttribute(hstd::SPtr<LayoutRun> run) : run{run} {}
};

class UnboundEdgeVisualAttribute : public IEdgeVisualAttribute {
  public:
    void write_serial(proto::IAttribute* out) const override {}
};

class UnboundEdgeLayoutAttribute : public IEdgeLayoutAttribute {
  public:
    void write_serial(proto::IAttribute* out) const override {}

    geometry::Path path;
    UnboundEdgeLayoutAttribute(geometry::Path const& path) : path{path} {}
    Path getPath() const override { return path; }
};

class LayoutRun
    : public OperationsTracer
    , public hstd::SharedPtrApi<LayoutRun> {
  public:
    // TODO: Instead of storing or creating edge/port collections for the
    // layout run, the constructor should require the input graph to store
    // the objects with specific IDs instead. Constructor then can call
    // `graph.getCollection()` to assign to the collection field.
    hstd::SPtr<IGraph>                graph;
    hstd::SPtr<IdOnlyHierarchy>       groups;
    hstd::SPtr<TrivialEdgeCollection> edges;
    hstd::SPtr<TrivialPortCollection> ports;

    LayoutRun(
        hstd::SPtr<IGraph>                graph,
        hstd::SPtr<TrivialEdgeCollection> _edges = nullptr,
        hstd::SPtr<TrivialPortCollection> _ports = nullptr,
        EdgeCollectionID edges_id                = EdgeCollectionID{9999});

    void runFullLayout();

    /// \brief Full store for the layout results of all recursive runs.
    IPlacementAlgorithm::Result result;

    hstd::SPtr<UnboundEdgeVisualAttribute> addUnboundEdge(
        EdgeID const& id) {
        auto attr = std::make_shared<UnboundEdgeVisualAttribute>();
        setEdgeAttribute(id, attr);
        return attr;
    }

    EdgeIDSet getAllUnboundEdges() const;

    template <typename T = IVertex>
        requires std::derived_from<T, IVertex>
    T const* getVertex(VertexID const& id) const {
        hstd::logic_assertion_check_not_nil(graph);
        return hstd::validated_dynamic_cast<T>(graph->getVertex(id));
    }

    template <typename T = IVertex>
        requires std::derived_from<T, IVertex>
    T* getMVertex(VertexID const& id) {
        return hstd::validated_dynamic_cast<T>(graph->getMVertex(id));
    }

    template <typename T = IEdge>
        requires std::derived_from<T, IEdge>
    T const* getEdge(EdgeID const& id) const {
        hstd::logic_assertion_check_not_nil(graph);
        return hstd::validated_dynamic_cast<T>(graph->getEdge(id));
    }

    template <typename T = IEdge>
        requires std::derived_from<T, IEdge>
    T* getMEdge(EdgeID const& id) {
        return hstd::validated_dynamic_cast<T>(graph->getMEdge(id));
    }

    template <typename T = IPort>
        requires std::derived_from<T, IPort>
    T const* getPort(PortID const& id) const {
        hstd::logic_assertion_check_not_nil(graph);
        return hstd::validated_dynamic_cast<T>(ports->getPort(id));
    }

    template <typename T = IPort>
        requires std::derived_from<T, IPort>
    T* getMPort(PortID const& id) {
        return hstd::validated_dynamic_cast<T>(ports->getMPort(id));
    }

    template <typename T = IGroupVisualAttribute>
        requires std::derived_from<T, IGroupVisualAttribute>
    hstd::SPtr<T> getGroup(VertexID const& id) const {
        return graph->getVertex(id)->getUniqueAttribute<T>(
            graph->getDebug(id));
    }

    template <typename T = IEdgeVisualAttribute>
        requires std::derived_from<T, IEdgeVisualAttribute>
    hstd::SPtr<T> getEdgeVisualAttribute(EdgeID const& id) const {
        return graph->getEdge(id)->getUniqueAttribute<T>(
            graph->getDebug(id));
    }

    template <typename T = IVertexVisualAttribute>
        requires std::derived_from<T, IVertexVisualAttribute>
    hstd::SPtr<T> getVertexVisualAttribute(VertexID const& id) const {
        return graph->getVertex(id)->getUniqueAttribute<T>(
            graph->getDebug(id));
    }

    template <typename T = IPortVisualAttribute>
        requires std::derived_from<T, IPortVisualAttribute>
    hstd::SPtr<T> getPortVisualAttribute(PortID const& id) const {
        return graph->getPort(id)->getUniqueAttribute<T>(
            graph->getDebug(id));
    }

    template <typename T = IAttribute>
        requires std::derived_from<T, IAttribute>
    void setAttribute(EdgeID const& id, hstd::SPtr<T> const& attr) const {
        graph->getEdge(id)->addOrResetUniqueAttribute<T>(id, attr);
    }

    template <typename T = IAttribute>
        requires std::derived_from<T, IAttribute>
    void setAttribute(VertexID const& id, hstd::SPtr<T> const& attr)
        const {
        graph->getVertex(id)->addOrResetUniqueAttribute<T>(id, attr);
    }


    template <typename T = IGroupVisualAttribute>
        requires std::derived_from<T, IGroupVisualAttribute>
    bool isGroupVertex(VertexID const& id) const {
        bool res = graph->getVertex(id)->hasOptionalAttribute<T>();
        if (!res) {
            LOGIC_ASSERTION_CHECK_FMT(
                groups->getSubVertices(id).empty(),
                "vertex {} is not a group, but it contains sub-vertices "
                "{}",
                getDebug(id),
                getDebug(groups->getSubVertices(id)));
        }
        return res;
    }

    PortIDSet getDirectPorts(VertexID const& id) const {
        PortIDSet res;
        for (auto const& v : getDirectVertices(id)) {
            res.incl(ports->getPortsForVertex(v));
        }
        return res;
    }

    VertexIDSet getDirectVertices(VertexID const& id) const;

    VertexIDSet getRootGroups() const {
        VertexIDSet res;
        for (auto const& sub : groups->getRootVertices()) {
            if (isGroupVertex(sub)) { res.incl(sub); }
        }
        return res;
    }

    VertexIDSet getSubGroups(VertexID const& id) const;

    /// \brief Get all nested groups that don't switch layout
    VertexIDSet getSubGroupsNoLayoutSwitch(VertexID const& id) const;

    EdgeIDSet getDirectlyNestedEdges(VertexID const& id) const {
        LOGIC_ASSERTION_CHECK(
            isGroupVertex(id), "Cannot get nested edges from non-group");
        return edges->getFullyIncludedEdges(getDirectVertices(id));
    }

    EdgeIDSet getPartiallyNestedEdges(VertexID const& id) const {
        LOGIC_ASSERTION_CHECK(
            isGroupVertex(id), "Cannot get nested edges from non-group");
        return edges->getPartiallyIncludedEdges(getDirectVertices(id));
    }

    EdgeIDSet getGroupIncidentEdges(VertexID const& id) const {
        LOGIC_ASSERTION_CHECK(
            isGroupVertex(id), "Cannot get incident edges from non-group");
        return edges->getPartiallyIncludedEdges({id});
    }

    struct EdgeIteration {
      private:
        EdgeIDSet                leftover_edges;
        EdgeIDSet                processed_edges;
        layout::LayoutRun const* run;

      public:
        EdgeIteration(layout::LayoutRun const* run) : run{run} {}

        /// \brief Get set of edges that are fully nested in a given group
        /// but have not been processed by any other group.
        ///
        /// \warning This method mutates the list of leftover and processed
        /// edges and must be called exactly once for every ID.
        EdgeIDSet getEdgesForGroup(VertexID const& id);

        EdgeIDSet getLeftoverEdges() { return leftover_edges; }

        void validateLeftoverEdges() {
            LOGIC_ASSERTION_CHECK_FMT(
                leftover_edges.size() == 0,
                "edge iteration layout could not place the edges within "
                "the single layour run space: {}. These edges must be "
                "placed as unbound edges on the overall graph and routed "
                "after the main layout.",
                run->getDebug(leftover_edges));
        }
    };

    /// \brief Return all the edges nested in the target group and its
    /// sub-groups, excluding the edges that are at least partially
    /// crossing the algorithm switch boundary
    EdgeIDSet getLayoutLayerNestedEdges(VertexID const& id) const;

    void addRootGroup(
        VertexID const&                          id,
        hstd::SPtr<IGroupVisualAttribute> const& attr) {
        groups->trackVertex(id);
        graph->getMVertex(id)->addUniqueAttribute(attr);
    }

    EdgeID addNestedGroup(
        VertexID const&                          parent,
        VertexID const&                          nested,
        hstd::SPtr<IGroupVisualAttribute> const& attr);

    EdgeID addNestedVertex(
        VertexID const&                           parent,
        VertexID const&                           nested,
        hstd::SPtr<IVertexVisualAttribute> const& attr);

    // TODO: Document this function and related operations for adding the
    // elements to the layout run. Update the implementation so the layout
    // run itself is not used to construct the semantic structure of the
    // graph: the layout run should expect all the elements to already be
    // added in the required ports and edges.
    void setEdgeAttribute(
        EdgeID const&                           id,
        hstd::SPtr<IEdgeVisualAttribute> const& attr);

    PortID addPort(
        VertexID const&                   v,
        EdgeID const&                     e,
        bool                              is_start,
        std::optional<std::string> const& stable_id);

    PortID addPort(
        VertexID const&                         v,
        EdgeID const&                           e,
        bool                                    is_start,
        std::optional<std::string> const&       stable_id,
        hstd::SPtr<IPortVisualAttribute> const& attr) {
        auto res  = addPort(v, e, is_start, stable_id);
        auto edge = getGraph()->getMPort(res);
        edge->addUniqueAttribute(attr);
        return res;
    }

    hstd::SPtr<IGraph> getGraph() const {
        hstd::logic_assertion_check_not_nil(graph);
        return graph;
    }


    IVertex const* at(VertexID const& id) const {
        return graph->getVertex(id);
    }

    template <typename T = IPortLayoutAttribute>
        requires std::derived_from<T, IPortLayoutAttribute>
    hstd::SPtr<T> getLayout(PortID const& id) const {
        LOGIC_ASSERTION_CHECK_FMT(
            result.ports.contains(id),
            "No layout attribute specified for Port {}",
            graph->getDebug(id));

        return hstd::validated_dynamic_cast<T>(result.ports.at(id));
    }

    template <typename T = IEdgeLayoutAttribute>
        requires std::derived_from<T, IEdgeLayoutAttribute>
    hstd::SPtr<T> getLayout(EdgeID const& id) const {
        LOGIC_ASSERTION_CHECK_FMT(
            result.edges.contains(id),
            "No layout attribute specified for edge {}",
            graph->getDebug(id));

        return hstd::validated_dynamic_cast<T>(result.edges.at(id));
    }

    template <typename T = IVertexLayoutAttribute>
        requires std::derived_from<T, IVertexLayoutAttribute>
    hstd::SPtr<T> getLayout(VertexID const& id) const {
        LOGIC_ASSERTION_CHECK_FMT(
            result.vertices.contains(id),
            "No layout attribute specified for vertex ID {}. Have "
            "vertices {}",
            getDebug(id),
            getDebug(result.vertices.keys()));

        return hstd::validated_dynamic_cast<T>(result.vertices.at(id));
    }

    bool hasLayout(VertexID const& id) const {
        return result.vertices.contains(id);
    }

    bool hasLayout(PortID const& id) const {
        return result.ports.contains(id);
    }

    bool hasLayout(EdgeID const& id) const {
        return result.edges.contains(id);
    }

    hstd::Opt<VertexID> getParent(VertexID const& id) const {
        return groups->getParentVertex(id);
    }

    hstd::Vec<VertexID> getParentChain(VertexID const& id) const {
        return groups->getParentChain(id);
    }

    geometry::Rect getRelativeBBox(PortID const& id) const {
        return getLayout(id)->getBBox();
    }

    geometry::Rect getRelativeBBox(VertexID const& id) const {
        return getLayout(id)->getBBox();
    }


    geometry::Rect getAbsoluteBBox(VertexID const& id) const {
        auto start = getRelativeBBox(id);

        geometry::Point offset{0, 0};
        for (auto const& parent : getParentChain(id)) {
            offset += getRelativeBBox(parent).upper_left();
        }

        return start.move(offset);
    }

    geometry::Rect getAbsoluteBBox(PortID const& id) const {
        auto parent_offset = getRelativeBBox(ports->getVertexForPort(id))
                                 .upper_left();
        return getRelativeBBox(id).move(parent_offset);
    }

    hstd::Vec<visual::VisGroup> getVisual() const;

    visual::VisGroup getVisual(PortID const& id) const {
        return getLayout(id)->getVisual(id);
    }

    visual::VisGroup getVisual(EdgeID const& id) const {
        return getLayout(id)->getVisual(id);
    }

    visual::VisGroup getVisual(VertexID const& id) const {
        return getLayout(id)->getVisual(id);
    }

    struct TreeReprConf {};

    void treeRepr(hstd::ColStream& os, TreeReprConf const& conf) const;

    hstd::ColText treeRepr(TreeReprConf const& conf) {
        hstd::ColStream os;
        treeRepr(os, conf);
        return os.getBuffer();
    }

    hstd::ColText treeRepr() { return treeRepr(TreeReprConf{}); }

    std::string getDebug(EdgeID const& edge) const {
        return getGraph()->getDebug(edge);
    }
    std::string getDebug(EdgeIDSet const& vert) const {
        return getGraph()->getDebug(vert);
    }
    std::string getDebug(EdgeIDVec const& vert) const {
        return getGraph()->getDebug(vert);
    }
    std::string getDebug(VertexIDSet const& vert) const {
        return getGraph()->getDebug(vert);
    }
    std::string getDebug(VertexIDVec const& vert) const {
        return getGraph()->getDebug(vert);
    }
    std::string getDebug(VertexID const& vert) const {
        return getGraph()->getDebug(vert);
    }
    std::string getDebug(PortIDSet const& vert) const {
        return getGraph()->getDebug(vert);
    }
    std::string getDebug(PortIDVec const& vert) const {
        return getGraph()->getDebug(vert);
    }
    std::string getDebug(PortID const& vert) const {
        return getGraph()->getDebug(vert);
    }
};


} // namespace layout

} // namespace hstd::ext::graph
