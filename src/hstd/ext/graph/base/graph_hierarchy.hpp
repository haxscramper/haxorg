#pragma once

#include "graph_common.hpp"
#include "graph_edge.hpp"
#include "graph_port.hpp"

namespace hstd::ext::graph {


/// \brief Hierarchical arrangement of vertices that forms a forest
/// structure, with one or more root nodes and a collection of subnodes.
///
/// - Each vertex has zero (root vertices) or one (nested vertices) parents
/// - Deleting a vertex from hierarchy drops all the nested vertices and
///   edges
/// - Edge direction is from the parent vertex down to the nested vertices
/// - Hierarchy might not include all vertices in an associated graph --
///   it represents a structured sub-set of the overall vertices. If
///   something does not fit in the hierarchy, the vertex is not included.
class IVertexHierarchy : public IEdgeProvider {
  protected:
    /// \brief Parent -> List of Sub-Vertices mapping
    hstd::UnorderedMap<VertexID, hstd::UnorderedSet<VertexID>> nestedInMap;
    /// \brief Sub-Vertex -> Parent mapping
    hstd::UnorderedMap<VertexID, VertexID> parentMap;
    /// \brief Set of vertices that don't have parent items in the map.
    hstd::UnorderedSet<VertexID> rootVertices;
    /// \brief Full set of all vertices tracked by this hierarchy.
    hstd::UnorderedSet<VertexID> vertexIDs;

    /// \brief Track `(parent, sub-vertex) -> edge ID`. Edges are added and
    /// removed automatically based on the hierarchy.
    hstd::ext::Unordered1to1Bimap<hstd::Pair<VertexID, VertexID>, EdgeID>
        edgeTracker;


  public:
    virtual ~IVertexHierarchy() = default;

    virtual void writeSerial(
        proto::IVertexHierarchy* out,
        IGraph const*            graph) const;

    void readSerial(
        proto::IVertexHierarchy const* in,
        IGraph const*                  graph,
        IGraphSerialReaderFactory*     factory);

    int getVertexCount() const { return vertexIDs.size(); }

    using IEdgeProvider::hasEdge;
    bool hasEdge(VertexID const& source, VertexID const& target)
        const override {
        return edgeTracker.contains_left({source, target});
    }

    bool isTrackingEdge(EdgeID const& id) const override {
        return edgeTracker.contains_right(id);
    }

    void assertHasEdge(EdgeID const& id) const {
        LOGIC_ASSERTION_CHECK_FMT(
            hasEdge(id),
            "Vertex hierarchy {} must have the object associated with ID "
            "{}, but hasEdge({}) = false",
            getStableID(),
            id,
            id);
    }

    void assertTrackingEdge(EdgeID const& id) const {
        // Edge tracking must be done after the edge object is already
        // registered, and all tracked edges must have object associated
        // with them.
        assertHasEdge(id);
        LOGIC_ASSERTION_CHECK_FMT(
            isTrackingEdge(id),
            "Vertex hierarchy {} must be tracking edge {} ({}), but "
            "isTrackingEdge({}) = false",
            getStableID(),
            id,
            getEdge(id) ? getEdge(id)->getStableId() : "<null>",
            id);
    }

    void assertKnownVertex(VertexID const& id) {}

    bool isTrackingVertex(VertexID const& id) const {
        return vertexIDs.contains(id);
    }

    /// \brief Add the vertex to the hierarchy collection without nesting
    /// relations.
    void trackVertex(VertexID const& id) override;

    /// \brief Remove the vertex from the hierarchy together with all
    /// nested sub-vertices tracked under it.
    ///
    /// \returns List of deleted vertex ids including `id`.
    DependantDeletion untrackVertex(VertexID const& id) override;

    /// \brief Provide additional information about the vertex nesting
    /// relation.
    ///
    /// The vertex can only be nested under one parent and
    /// present in the graph once. Both parent and sub must be existing
    /// vertices. This method will create a new edge ID based on the parent
    /// and sub-vertex IDs.
    ///
    /// \warning After the vertex has been registered in the main graph
    /// this method needs to be called to record additional structural
    /// information about the sub-vertices.
    ///
    /// \note The function has a default implementation, but the
    /// derived hierarchy classes may override the sub-vertex tracking or
    /// write a code around it to actually create an edge object.
    virtual void trackSubVertexRelation(
        EdgeID const&   edge,
        VertexID const& parent,
        VertexID const& sub);

    EdgeID getNestingEdgeID(VertexID const& parent, VertexID const& sub);

    VertexID getSource(EdgeID const& edge) const override {
        return edgeTracker.at_left(edge).first;
    }

    VertexID getTarget(EdgeID const& edge) const override {
        return edgeTracker.at_left(edge).second;
    }

    hstd::Pair<VertexID, VertexID> getParentAndNested(
        EdgeID const& edge) const {
        return {getSource(edge), getTarget(edge)};
    }

    /// \brief Remove the vertex nesting information. As `sub` can only be
    /// nested under one vertex -- `parent`, this makes both `sub` and
    /// `parent` a root vertices again.
    ///
    /// This does not remove the vertices
    /// from the graph. If `sub` contains its own sub-vertices, they will
    /// remain under `sub`. If `parent` contains more sub-vertices they
    /// will also remain where they are.
    ///
    /// \note This method will be automatically called on the
    /// `unregisterVertex`, to prevent malformed graph structure, but it is
    /// also safe to call this method manually, if the graph nesting
    /// relations must be edited.
    void untrackSubVertexRelation(
        VertexID const& parent,
        VertexID const& sub);

    /// \brief Return all vertices tracked by this hierarchy.
    VertexIDSet getAllVertices() const;

    /// \brief Return all root vertices tracked by this hierarchy.
    VertexIDSet getRootVertices() const;

    /// \brief Return direct sub-vertices for `id`.
    VertexIDSet getSubVertices(VertexID const& id) const;

    /// \brief Return parent vertex for `id` if present.
    hstd::Opt<VertexID> getParentVertex(VertexID const& id) const;

    std::optional<VertexID> getCommonAncestor(
        VertexIDSet const& ids) const;

    /// \brief Return full parent chain for `id`, from immediate parent up
    /// to the root.
    hstd::Vec<VertexID> getParentChain(VertexID const& id) const;
    /// \brief Get parent chain from the start to finish node, excluding
    /// these two nodes.
    hstd::Vec<VertexID> getParentChainUntil(
        VertexID const& start,
        VertexID const& finish) const;

    EdgeIDSet getEdges() const override;
    EdgeIDSet getOutgoing(VertexID const& vert) const override;
    EdgeIDSet getIncoming(VertexID const& vert) const override;

    /// \brief Return the highest level of nesting in the hierarchy.
    int getMaxNestingLevel() const;

    /// \brief For id with given ID, compute the list of vertex
    /// boundaries it crossed between the source and the target.
    ///
    /// - If the source and target of the id are under the same parent
    ///   vertex, hen no hierarchy crossings happened.
    /// - If the source and target are under different parents, then the
    ///   hierarcy crossings is computed by first starting at source and
    ///   getting to the common parent of the source and target and then
    ///   traversing down to teh target vertex.
    ///
    /// \par Example:
    /// The graph hierarchy is `(a (b c d) (e (f g) h)`
    /// where each letter represents one vertex and `()` represents a
    /// hierarchy group. So `g` is under the group with `f` as a parent
    /// vertex, which is under `e`, which in turn is under `a`.
    ///
    /// \par
    /// - Edge `c-d` will have **0** crossings -- source and target
    ///   are both placed under the same parent
    /// - Edge `c-a` will have **1** crossing -- source and target
    ///   are placed under the different parent.
    /// - Edge `c-b` will have **0** crossings -- the id is counted
    ///   as one inside of the group for `b`.
    /// - Edge `c-g` will have **3** crossings
    ///   - traverse `g->e` -- one "up" crossing
    ///   - traverse `e->a` -- one "up" crossing
    ///   - traverse `a->b` -- one "down" crossing.
    ///
    /// \returns List of crossings for the provided id.
    hstd::Vec<VertexID> getHierarchyCrossings(
        VertexID const& source,
        VertexID const& target) const;
};

struct TrivialHierarchy : public IVertexHierarchy {
    hstd::UnorderedMap<EdgeID, TrivialEdge> edgeStore;

  public:
    EdgeCollectionID getCollectionID() const override {
        return EdgeCollectionID::FromHierarchyTypePointer(this);
    }

    const IEdge* getEdge(EdgeID const& id) const override {
        return &edgeStore.at(id);
    }

    bool hasEdge(EdgeID const& id) const override {
        return edgeStore.contains(id);
    }

    void addEdge(EdgeID const& id, TrivialEdge const& init_vertex);

    EdgeID trackSubVertexRelation(
        VertexID const&               parent,
        VertexID const&               sub,
        hstd::Opt<TrivialEdge> const& init_vertex = std::nullopt);
};

struct IdOnlyHierarchy : public IVertexHierarchy {
    hstd::UnorderedSet<EdgeID> edgeStore;

  public:
    EdgeCollectionID getCollectionID() const override {
        return EdgeCollectionID::FromHierarchyTypePointer(this);
    }

    const IEdge* getEdge(EdgeID const& id) const override {
        return nullptr;
    }

    bool hasEdge(EdgeID const& id) const override {
        return edgeStore.contains(id);
    }

    EdgeID trackSubVertexRelation(
        VertexID const&               parent,
        VertexID const&               sub,
        hstd::Opt<TrivialEdge> const& init_vertex = std::nullopt) {
        auto id = getNestingEdgeID(parent, sub);
        edgeStore.incl(id);
        IVertexHierarchy::trackSubVertexRelation(id, parent, sub);
        return id;
    }
};


class AutoSegmentingCollection : public IEdgeCollection {
    TrivialEdgeCollection*  segmented_edges;
    TrivialPortCollection*  connection_ports;
    IVertexHierarchy const* hierarchy;
    IGraph const*           graph;

    hstd::ext::UnorderedNto1Bimap<hstd::Pair<EdgeID, EdgeID>, PortID>
                                                  segments_to_ports;
    hstd::ext::UnorderedNto1Bimap<EdgeID, EdgeID> segments_to_edges;
    hstd::UnorderedMap<EdgeID, int>               segment_index;

  public:
    AutoSegmentingCollection(
        TrivialEdgeCollection*  segmented_edges,
        TrivialPortCollection*  connection_ports,
        IVertexHierarchy const* hierarchy,
        IGraph const*           graph)
        : segmented_edges{segmented_edges}
        , connection_ports{connection_ports}
        , hierarchy{hierarchy}
        , graph{graph} {}

    EdgeIDVec getSegments(EdgeID const& edge) const;

    EdgeID getOriginalEdge(EdgeID const& segment) const {
        return segments_to_edges.get_right(segment).value();
    }

    void addEdge(EdgeID const& original);

    hstd::Vec<PortID> getSegmentationPorts(EdgeID const& original);

    EdgeCollectionID getCollectionID() const override {
        return segmented_edges->getCollectionID();
    }

    const IEdge* getEdge(EdgeID const& id) const override {
        return segmented_edges->getEdge(id);
    }

    bool hasEdge(EdgeID const& id) const override {
        return segmented_edges->hasEdge(id);
    }

    void writeSerial(proto::IEdgeCollection* out, IGraph const* graph)
        const override {
        IEdgeCollection::writeSerial(out, graph);
        proto::AutoSegmentingCollectioneCollection tag;
        out->mutable_payload()->PackFrom(tag);
    }

    void readSerial(
        proto::IEdgeCollection const* in,
        IGraph const*                 graph,
        IGraphSerialReaderFactory*    factory) override {
        IEdgeCollection::readSerial(in, graph, factory);
    }
};

} // namespace hstd::ext::graph
