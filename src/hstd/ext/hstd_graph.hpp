#pragma once

#include <hstd/stdlib/dod_base.hpp>
#include <boost/serialization/strong_typedef.hpp>
#include <hstd/stdlib/JsonSerde.hpp>
#include <hstd/stdlib/Set.hpp>
#include <hstd/stdlib/Ptrs.hpp>

namespace hstd::ext::graph {
BOOST_STRONG_TYPEDEF(hstd::u16, EdgeCollectionID);
BOOST_STRONG_TYPEDEF(hstd::u16, PropertyTrackerID);
BOOST_STRONG_TYPEDEF(hstd::u16, GraphHierarchyID);
} // namespace hstd::ext::graph

template <>
struct std::hash<hstd::ext::graph::EdgeCollectionID> {
    std::size_t operator()(
        hstd::ext::graph::EdgeCollectionID const& it) const noexcept {
        std::size_t result = 0;
        hstd::hax_hash_combine(result, it.t);
        return result;
    }
};

template <>
struct std::hash<hstd::ext::graph::PropertyTrackerID> {
    std::size_t operator()(
        hstd::ext::graph::PropertyTrackerID const& it) const noexcept {
        std::size_t result = 0;
        hstd::hax_hash_combine(result, it.t);
        return result;
    }
};

template <>
struct std::hash<hstd::ext::graph::GraphHierarchyID> {
    std::size_t operator()(
        hstd::ext::graph::GraphHierarchyID const& it) const noexcept {
        std::size_t result = 0;
        hstd::hax_hash_combine(result, it.t);
        return result;
    }
};

namespace hstd::ext::graph {

/// \brief Base class for all graph entries: edges, vertices, groups.
/// Container classes (vertex hierarchies, edge collections) are not graph
/// objects.
class IGraphObjectBase {
  public:
    virtual std::size_t getHash() const                              = 0;
    virtual bool        isEqual(IGraphObjectBase const* other) const = 0;
    virtual std::string getRepr() const                              = 0;
    virtual std::string getStableId() const;

    virtual ~IGraphObjectBase() = default;

    template <typename T>
    bool isInstance() const {
        return dynamic_cast<T const*>(this) != nullptr;
    }
};

template <typename T>
concept IsGraphObject = std::derived_from<T, IGraphObjectBase>;

DECL_ID_TYPE_MASKED(IVertex, VertexID, hstd::u64, 16);
DECL_ID_TYPE_MASKED(IEdge, EdgeID, hstd::u64, 16);
/// \brief Categorize the in/out edge connections between vertices.
///
/// The concept of the node port is linked with the layout, but the the
/// abstract graph interface it is also used to group different connections
/// of edge to the vertices.
DECL_ID_TYPE(IPort, PortID, hstd::u64);

class IGraph;

struct IVertex : public IGraphObjectBase {
    using id_type = VertexID;
    DESC_FIELDS(IVertex, ());

    virtual json getSerialNonRecursive(
        IGraph const*                     graph,
        hstd::ext::graph::VertexID const& id) const = 0;
};

struct IEdge : public IGraphObjectBase {
    using id_type = EdgeID;

    VertexID          source;
    VertexID          target;
    int               bundleIndex = -1;
    hstd::Opt<PortID> sourcePort  = std::nullopt;
    hstd::Opt<PortID> targetPort  = std::nullopt;
    DESC_FIELDS(
        IEdge,
        (source, target, bundleIndex, sourcePort, targetPort));

    IEdge(VertexID const& source, VertexID const& target)
        : source{source}, target{target} {}

    struct SerialSchema {
        std::string            edgeId;
        std::string            sourceId;
        std::string            targetId;
        int                    bundleIndex;
        hstd::Opt<std::string> sourcePortId;
        hstd::Opt<std::string> targetPortId;
        DESC_FIELDS(
            SerialSchema,
            (edgeId,
             sourceId,
             targetId,
             bundleIndex,
             sourcePortId,
             targetPortId));
    };

    bool operator==(IEdge const& other) const {
        return this->isEqual(&other);
    }

    VertexID getSource() const { return source; }
    VertexID getTarget() const { return target; }

    virtual std::size_t getHash() const override;
    virtual bool isEqual(IGraphObjectBase const* other) const override;
    virtual json getSerialNonRecursive(
        IGraph const*                   graph,
        hstd::ext::graph::EdgeID const& id) const;
    virtual std::string getRepr() const override {
        return hstd::fmt1(*this);
    }
};

struct IPort : public IGraphObjectBase {
    using id_type = PortID;
    DESC_FIELDS(IPort, ());
};

} // namespace hstd::ext::graph

template <hstd::ext::graph::IsGraphObject T>
struct std::hash<T> {
    std::size_t operator()(T const& it) const noexcept {
        return it.getHash();
    }
};

namespace hstd::ext::graph {

struct IProperty {
  public:
    virtual std::size_t getHash() const                       = 0;
    virtual bool        isEqual(IProperty const* other) const = 0;
    virtual std::string getRepr() const                       = 0;
    virtual ~IProperty()                                      = default;

    template <typename T>
    bool isInstance() const {
        return dynamic_cast<T const*>(this) != nullptr;
    }
};

class IPropertyTracker {
  public:
    virtual void                trackVertex(VertexID const& vertex)   = 0;
    virtual void                untrackVertex(VertexID const& vertex) = 0;
    virtual hstd::Vec<VertexID> getVertices(IProperty const& prop)    = 0;
    virtual PropertyTrackerID   getTrackerID() const                  = 0;
};

/// \brief Base class for the collections that provide the edges in the
/// graph.
class IEdgeProvider {
  public:
    virtual ~IEdgeProvider() = default;
    /// \brief Return edge category for this collection, uniquely
    /// identifying this specific one collection.
    virtual EdgeCollectionID getCategory() const = 0;

    /// \brief Get already constructed edge object from the store.
    virtual IEdge const& getEdge(EdgeID const& id) const = 0;

    /// \brief Add all edges outgoing from the `id`. The vertex itself
    /// should already be registered with `trackVertex`.
    ///
    /// \note The override of this method should make use of `trackEdge` or
    /// `trackSubVertexRelation` to populate the edge collection tracker
    /// tables. The returned list of edges is used
    virtual hstd::Vec<EdgeID> addAllOutgoing(VertexID const& id) = 0;

    /// \brief Return stable identifier for this edge collection.
    virtual std::string getStableID() const = 0;

    /// \brief Get the full list of edges stored in the collection
    virtual hstd::Vec<EdgeID> getEdges() const = 0;

    /// \brief Add the vertex to the edge collection without any of the
    /// incoming/outgoing edges.
    virtual void trackVertex(VertexID const& vert) = 0;

    struct DependantDeletion {
        hstd::Vec<VertexID> vertices;
        hstd::Vec<EdgeID>   edges;
    };

    /// \brief Remove the vertex from the collection including any outgoing
    /// edges. Edge removal is done using `untrackEdge`.
    virtual DependantDeletion untrackVertex(VertexID const& vert) = 0;


    /// \brief Get list of all outgoing edges for the target vertex
    virtual hstd::Vec<EdgeID> getOutgoing(VertexID const& vert) const = 0;

    /// \brief Get list of all incoming edges for the target vertex
    virtual hstd::Vec<EdgeID> getIncoming(VertexID const& vert) const = 0;
};

class IEdgeCollection : public IEdgeProvider {
    hstd::UnorderedMap<
        VertexID,
        hstd::UnorderedMap<VertexID, hstd::Vec<EdgeID>>>
        incidence;

    hstd::UnorderedMap<VertexID, hstd::Vec<VertexID>> incoming_from;


  public:
    hstd::Vec<EdgeID> getEdges() const override;
    hstd::Vec<EdgeID> getOutgoing(VertexID const& vert) const override;
    hstd::Vec<EdgeID> getIncoming(VertexID const& vert) const override;
    void              trackVertex(VertexID const& vert) override;
    DependantDeletion untrackVertex(VertexID const& vert) override;

    /// \brief Track the new edge in the collection. Associated
    /// `IEdge`-derived object should already be accessible through the
    /// `getEdge()` virtual method override.
    virtual void trackEdge(EdgeID const& id);
    /// \brief Remove the edge from the collection. This method is called
    /// by the `untrackVertex`.
    virtual void untrackEdge(EdgeID const& id);


    /// \brief Hierachy category should have the first bit set to 1.
    static constexpr hstd::u16 HierarchyCategoryMask    = 0b1111'1111;
    static constexpr hstd::u16 HierarchyCategoryMaskBit = 0b1000'0000;
    /// \brief Regular edge collection should have the first bit set to 0.
    static constexpr hstd::u16 CollectionCategoryMask = 0b0111'1111;

    static bool isHierarchyEdge(EdgeID const& id);

    static EdgeCollectionID edgeCategoryFromEdge(EdgeID const& id);

    static GraphHierarchyID hierarchyIdFromEdge(EdgeID const& id);

    static bool hierarchyUsesMask(GraphHierarchyID const& id);
};

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
    hstd::UnorderedMap<hstd::Pair<VertexID, VertexID>, EdgeID> edgeTracker;


  public:
    virtual ~IVertexHierarchy() = default;

    /// \brief Return hierarchy identifier used in edge masks.
    virtual GraphHierarchyID getHierarchyId() const = 0;

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
    /// vertices.
    ///
    /// \warning After the vertex has been registered in the main graph
    /// this method needs to be called to record additional structural
    /// information about the sub-vertices.
    EdgeID trackSubVertexRelation(
        VertexID const& parent,
        VertexID const& sub);

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
    hstd::Vec<VertexID> getAllVertices() const;

    /// \brief Return all root vertices tracked by this hierarchy.
    hstd::Vec<VertexID> getRootVertices() const;

    /// \brief Return direct sub-vertices for `id`.
    hstd::Vec<VertexID> getSubVertices(VertexID const& id) const;

    /// \brief Return parent vertex for `id` if present.
    hstd::Opt<VertexID> getParentVertex(VertexID const& id) const;

    /// \brief Return full parent chain for `id`, from immediate parent up
    /// to the root.
    hstd::Vec<VertexID> getParentChain(VertexID const& id) const;

    hstd::Vec<EdgeID> getEdges() const override;
    hstd::Vec<EdgeID> getOutgoing(VertexID const& vert) const override;
    hstd::Vec<EdgeID> getIncoming(VertexID const& vert) const override;

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

struct org_graph_error : public hstd::CRTP_hexception<org_graph_error> {};

/// \brief Single set of vertices and a collection of associated edge sets.
///
/// A graph directly stores all vertices in the store, and indirectly
/// stores additional sets of edges managed by the `IVertexHierarchy` and
/// `IEdgeCollection`. Vertices are stored as opaque IDs -- mapping ID to
/// the specific object is done by the derived classes.
class IGraph {
  protected:
    hstd::UnorderedMap<EdgeCollectionID, hstd::SPtr<IEdgeCollection>>
        collections;
    hstd::UnorderedMap<PropertyTrackerID, hstd::SPtr<IPropertyTracker>>
        trackers;
    hstd::UnorderedMap<GraphHierarchyID, hstd::SPtr<IVertexHierarchy>>
        hierarchies;

    /// \brief Full set of all vertices in the graph
    hstd::UnorderedSet<VertexID> vertexIDs;

  protected:
    /// \brief Add the vertex to the graph collection. Will not
    /// automatically register all nested vertices and recursive data.
    /// After the base vertex is registered, provide additional structural
    /// information using `trackSubVertexRelation`.
    void registerVertex(VertexID const& id);

    /// \brief Remove vertex from the graph collection and recursively drop
    /// all the elements from the hierarchies.
    ///
    /// \note No follow-up calls to `untrackSubVertexRelation` is
    /// necessary to match the `trackSubVertexRelation` -- hierarchy
    /// deletion is done by this method.
    ///
    /// \warning Calling this method will RECURSIVELY DROP ALL SUB-VERTICES
    /// under `id` if they are also deleted in all hierarchies.
    ///
    /// \return Map of the dependant deletions in the graph hierarchies.
    /// Un-registering vertex *does not delete sub-vertices from the
    /// graph*, it only removes invalid edges. The returned value from this
    /// function contains a mapping from the hierarchy ID to the list of
    /// sub-vertex deletions for this hierarchy. It is possible to delete
    /// all the nested vertices with `untrackVertexList` for each set of
    /// vertices in the dependant deletion.
    hstd::UnorderedMap<GraphHierarchyID, IEdgeCollection::DependantDeletion> unregisterVertex(
        VertexID const& id);

  public:
    struct Crossing {
        GraphHierarchyID    hierarchy;
        hstd::Vec<VertexID> crossings;
        DESC_FIELDS(Crossing, (hierarchy, crossings));
    };

    void addTracker(hstd::SPtr<IPropertyTracker> const& tracker);
    void delTracker(hstd::SPtr<IPropertyTracker> const& tracker);
    void addCollection(hstd::SPtr<IEdgeCollection> const& collection);
    void delCollection(hstd::SPtr<IEdgeCollection> const& collection);
    void addHierarchy(hstd::SPtr<IVertexHierarchy> const& hierarchy);
    void delHierarchy(hstd::SPtr<IVertexHierarchy> const& hierarchy);

    /// \brief Get list of all edge providers in the graph: vertex
    /// hierarchies and general edge collections.
    hstd::Vec<IEdgeProvider*> getEdgeProviders();

    /// \brief Get vertex object associated with the edge ID.
    virtual IVertex const& getVertex(VertexID const& id) const = 0;

    /// \brief For id with given ID, compute the list of vertex
    /// boundaries it crossed in each tracked hierarchy between the source
    /// and the target.
    hstd::Vec<Crossing> getHierarchyCrossings(EdgeID const& edge_id) const;

    /// \brief Provide additional information about the vertex nesting
    /// relation for a specific hierarchy.
    ///
    /// \return List of newly added edges in all hierarchies.
    hstd::Vec<EdgeID> trackSubVertexRelation(
        GraphHierarchyID const& hierarchy,
        VertexID const&         parent,
        VertexID const&         sub);

    /// \brief Remove the vertex nesting information from a specific
    /// hierarchy.
    void untrackSubVertexRelation(
        GraphHierarchyID const& hierarchy,
        VertexID const&         parent,
        VertexID const&         sub);


    /// \brief Track properties and edge information in the graph
    ///
    /// \warning Call after the vertex has been registered. Should be
    /// called with the full list of vertices to track: this method will
    /// not attempt to expand the set of vertices to include nested ones.
    void trackVertexList(hstd::Vec<VertexID> const& ids);

    /// \brief Un-track properties and edge information
    ///
    /// \note See `trackVertexList`
    void untrackVertexList(hstd::Vec<VertexID> const& ids);

    /// \brief Get list of all vertices stored in the graph
    hstd::Vec<VertexID> getAllVertices() const;
    /// \brief Get root vertices for the specified hierarchy
    hstd::Vec<VertexID> getRootVertices(
        GraphHierarchyID const& hierarchy) const;
    /// \brief Get sub vertices for the specified hierarchy
    hstd::Vec<VertexID> getSubVertices(
        GraphHierarchyID const& hierarchy,
        VertexID const&         id) const;
    /// \brief Get parent vertices for the specified hierarchy
    hstd::Opt<VertexID> getParentVertex(
        GraphHierarchyID const& hierarchy,
        VertexID const&         id) const;
    IEdge const& getEdge(EdgeID const& id) const;

    /// \brief Return the highest level of nesting in the hierarchy.
    int getMaxNestingLevel(GraphHierarchyID const& hierarchy) const;

    /// \brief Return full parent chain for vertex in the selected
    /// hierarchy.
    hstd::Vec<VertexID> getParentChain(
        GraphHierarchyID const& hierarchy,
        VertexID const&         id) const;

    struct SerialSchema {
        struct EdgeCategory {
            hstd::Vec<json> edges;
            std::string     categoryName;

            struct HierarchyCrossing {
                std::string            hierarchyName;
                hstd::Vec<std::string> crossings;
                DESC_FIELDS(HierarchyCrossing, (hierarchyName, crossings));
            };

            /// \brief EdgeId -> List of Vertex IDs for parent hierarchies
            /// it has crossed. See `getHierarchyCrossings` method for more
            /// details.
            hstd::UnorderedMap<std::string, hstd::Vec<HierarchyCrossing>>
                hierarchyEdgeCrossings;

            DESC_FIELDS(
                EdgeCategory,
                (edges, categoryName, hierarchyEdgeCrossings));
        };

        struct Hierarchy {
            std::string                                  hierarchyName;
            hstd::Vec<std::string>                       rootVertexIDs;
            hstd::UnorderedMap<std::string, std::string> vertexParentMap;
            hstd::UnorderedMap<std::string, hstd::Vec<std::string>>
                vertexNestingMap;
            int maxNestingLevel = 0;
            DESC_FIELDS(
                Hierarchy,
                (hierarchyName,
                 rootVertexIDs,
                 vertexParentMap,
                 vertexNestingMap,
                 maxNestingLevel));
        };

        hstd::UnorderedMap<std::string, json>         vertices;
        hstd::UnorderedMap<std::string, EdgeCategory> edges;
        hstd::UnorderedMap<std::string, Hierarchy>    hierarchies;
        hstd::Vec<std::string>                        flatVertexIDs;

        DESC_FIELDS(
            SerialSchema,
            (vertices, edges, hierarchies, flatVertexIDs));
    };

    virtual json getGraphSerial() const;
};

} // namespace hstd::ext::graph
