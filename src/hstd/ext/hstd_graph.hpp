#pragma once

#include <hstd/stdlib/dod_base.hpp>
#include <boost/serialization/strong_typedef.hpp>
#include <hstd/stdlib/JsonSerde.hpp>
#include <hstd/stdlib/Set.hpp>
#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/ext/bimap_wrap.hpp>
#include <hstd/stdlib/OptFormatter.hpp>
#include "hstd/stdlib/TraceBase.hpp"
#include "hstd_geometry.hpp"

namespace hstd {
template <typename ID, typename T>
struct UnorderedInternStore {
    hstd::ext::Unordered1to1Bimap<ID, T> store;

    ID add(
        T const&                                 value,
        std::optional<typename ID::id_mask_type> mask = std::nullopt) {
        LOGIC_ASSERTION_CHECK_FMT(
            !store.contains_right(value),
            "Store already contains value {}",
            hstd::fmt1_maybe(value));

        int  current_size = size();
        auto result = mask.has_value()
                        ? ID::FromMaskedIdx(current_size, mask.value())
                        : ID::FromIndex(current_size);
        store.add_unique(result, value);
        return result;
    }

    void add_with_id(T const& value, ID const& result) {
        LOGIC_ASSERTION_CHECK_FMT(
            !store.contains_right(value),
            "Store already contains value {}",
            hstd::fmt1_maybe(value));

        store.add_unique(result, value);
    }

    hstd::Vec<ID> keys() const {
        hstd::Vec<ID> res;
        for (auto const& it : store.get_map()) { res.push_back(it.first); }
        return res;
    }

    ID del(T const& value) {
        ID res = store.at_left(value);
        store.erase_right(value);
        return res;
    }

    T const&  at(ID const& id) const { return store.at_right(id); }
    ID const& at(T const& value) const { return store.at_left(value); }
    int       size() const { return store.get_map().size(); }
};

template <typename ID, typename T>
struct UnorderedIncrementalStore : hstd::UnorderedMap<ID, T> {
  public:
    using Base = hstd::UnorderedMap<ID, T>;
    using Base::at;
    using Base::contains;
    using Base::insert_or_assign;
    using Base::keys;
    using Base::size;

    ID getNextId(
        std::optional<typename ID::id_mask_type> mask = std::nullopt)
        const {
        int  current_size = size();
        auto id = mask.has_value()
                    ? ID::FromMaskedIdx(current_size, mask.value())
                    : ID::FromIndex(current_size);
        return id;
    }

    ID add(
        T const&                                 value,
        std::optional<typename ID::id_mask_type> mask = std::nullopt) {
        auto id = getNextId(mask);
        add_with_id(value, id);
        return id;
    }

    void add_with_id(T const& value, ID const& result) {
        LOGIC_ASSERTION_CHECK_FMT(
            !contains(result),
            "Store already contains value {}",
            hstd::fmt1_maybe(value));

        insert_or_assign(result, value);
    }
};
} // namespace hstd

namespace hstd::ext::graph {


struct org_graph_error : public hstd::CRTP_hexception<org_graph_error> {};

using namespace hstd::ext::geometry;
/// \brief 16-bit ID to track edge collection. Used as a mask in the
/// `EdgeID`.
///
/// Collection ID is created by the IEdgeCollection::getCollectionId
BOOST_STRONG_TYPEDEF(hstd::u16, EdgeCollectionID);
/// \brief 16-bit ID to identify the attribute tracker.
BOOST_STRONG_TYPEDEF(hstd::u16, AttributeTrackerID);
/// \brief 16-bit ID to track the graph hierarchies. Used as a mask in the
/// `EdgeID`.
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
struct std::hash<hstd::ext::graph::AttributeTrackerID> {
    std::size_t operator()(
        hstd::ext::graph::AttributeTrackerID const& it) const noexcept {
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

/// \brief Base class for all attributes associated with vertices. The
/// attribute might be an individual value, or a complex composite object,
/// depending on the use case.
struct IAttribute {
  public:
    virtual ~IAttribute() = default;

    template <typename T>
    bool isInstance() const {
        return dynamic_cast<T const*>(this) != nullptr;
    }
};

/// \brief Base class for trackers implementing reverse lookup for
/// attribute values.
class IAttributeTracker {
  public:
    virtual void                trackVertex(VertexID const& vertex)   = 0;
    virtual void                untrackVertex(VertexID const& vertex) = 0;
    virtual hstd::Vec<VertexID> getVertices(IAttribute const& prop)   = 0;
    virtual AttributeTrackerID  getTrackerID() const                  = 0;
};

class IAttributeObject {
  public:
    virtual hstd::Vec<hstd::SPtr<IAttribute>> getAttributes() const = 0;
    virtual void addAttribute(hstd::SPtr<IAttribute> const& attr)   = 0;

    /// \brief Get first instance of the attribute with dynamic type `T`.
    template <typename T>
    hstd::SPtr<T> getOptionalAttribute() const {
        for (auto const& attr : getAttributes()) {
            if (attr->isInstance<T>()) {
                return std::dynamic_pointer_cast<T>(attr);
            }
        }

        return std::nullopt;
    }

    /// \brief Get all attributes with dynamic type T
    template <typename T>
    hstd::Vec<hstd::SPtr<T>> getAllAttributes() const {
        hstd::Vec<hstd::SPtr<T>> result;
        for (auto const& attr : getAttributes()) {
            if (attr->isInstance<T>()) {
                result.push_back(std::dynamic_pointer_cast<T>(attr));
            }
        }

        return result;
    }

    /// \brief Get one attribute with dynamic type T, the attribute is
    /// expected to be unique.
    template <typename T>
    hstd::SPtr<T> getUniqueAttribute() const {
        hstd::SPtr<T> result;
        for (auto const& attr : getAttributes()) {
            if (attr->isInstance<T>()) {
                if (result == nullptr) {
                    result = std::dynamic_pointer_cast<T>(attr);
                } else {
                    throw org_graph_error::init(
                        hstd::fmt(
                            "Graph object is expected to have exactly one "
                            "attribute of type {}, but found two.",
                            hstd::value_metadata<T>::typeName()));
                }
            }
        }

        if (result == nullptr) {
            throw org_graph_error::init(
                hstd::fmt(
                    "Graph object is expected to have exactly one "
                    "attribute of type {}, but found none.",
                    hstd::value_metadata<T>::typeName()));
        }

        return result;
    }
};


struct IVertex
    : public IGraphObjectBase
    , public IAttributeObject {
    using id_type = VertexID;
    DESC_FIELDS(IVertex, ());

    virtual json getSerialNonRecursive(
        IGraph const*                     graph,
        hstd::ext::graph::VertexID const& id) const = 0;
};

struct IEdge
    : public IGraphObjectBase
    , public IAttributeObject {
    using id_type = EdgeID;

    VertexID source;
    VertexID target;
    /// \brief In case of a multi-edge collection, bundle index allows to
    /// identify the specific edge among the several entries in the
    /// `(source, target)` pair.
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


/// \brief Base class for the collections that provide the edges in the
/// graph.
class IEdgeProvider {
  public:
    virtual ~IEdgeProvider() = default;
    /// \brief Return edge category for this collection, uniquely
    /// identifying this specific one collection.
    virtual EdgeCollectionID getCategory() const = 0;

    /// \brief Get already constructed edge object from the store.
    virtual IEdge const* getEdge(EdgeID const& id) const = 0;

    /// \brief Add all edges outgoing from the `id`. The vertex itself
    /// should already be registered with `trackVertex`.
    ///
    /// \note The class derived from the edge collection or vertex
    /// hierarchy should make use  `trackEdge` or `trackSubVertexRelation`
    /// to populate the edge collection tracker tables.
    virtual hstd::Vec<EdgeID> addAllOutgoing(VertexID const& id) = 0;

    /// \brief Return stable identifier for this edge collection.
    virtual std::string getStableID() const;

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

    // static API for masking the edge IDs.

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

class IEdgeCollection : public IEdgeProvider {
    hstd::UnorderedMap<
        VertexID,
        hstd::UnorderedMap<VertexID, hstd::Vec<EdgeID>>>
        incidence;

    hstd::UnorderedMap<VertexID, hstd::Vec<VertexID>> incoming_from;

  protected:
    /// \brief Default implementation of the hierarchy ID constructoir.
    ///
    /// It creates an ID based on the type, which is sufficient if there is
    /// only one instance of the hierarchy type in a graph.
    template <typename T>
    EdgeCollectionID getCollectionIdImpl(T const* self) const {
        return hstd::ext::graph::EdgeCollectionID(
            hstd::hash_bits<15>(typeid(self).hash_code())
            & CollectionCategoryMask);
    }


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

    /// \brief Default implementation of the hierarchy ID constructoir.
    ///
    /// It creates an ID based on the type, which is sufficient if there is
    /// only one instance of the hierarchy type in a graph.
    template <typename T>
    GraphHierarchyID getHierarchyIdImpl(T const* self) const {
        return hstd::ext::graph::GraphHierarchyID(
            hstd::hash_bits<15>(typeid(self).hash_code())
            & HierarchyCategoryMask);
    }


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


/// \brief Single set of vertices and a collection of associated edge sets.
///
/// A graph tracks all vertices in the store, and indirectly
/// tracks additional sets of edges managed by the `IVertexHierarchy` and
/// `IEdgeCollection`. Vertices are stored as opaque IDs -- mapping ID to
/// the specific object is done by the derived classes.
///
/// \note Classes derived from graph are not required to *store* the
/// vertices -- graph API is designed to track which vertex IDs exist, and
/// map the vertex ID to the vertex object. Most graphs will store the
/// vertices directly, but it is also suitable for adapting already
/// existing graphs.
class IGraph {
  protected:
    hstd::UnorderedMap<EdgeCollectionID, hstd::SPtr<IEdgeCollection>>
        collections;
    hstd::UnorderedMap<AttributeTrackerID, hstd::SPtr<IAttributeTracker>>
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

    void addTracker(hstd::SPtr<IAttributeTracker> const& tracker);
    void delTracker(hstd::SPtr<IAttributeTracker> const& tracker);
    void addCollection(hstd::SPtr<IEdgeCollection> const& collection);
    void delCollection(hstd::SPtr<IEdgeCollection> const& collection);
    void addHierarchy(hstd::SPtr<IVertexHierarchy> const& hierarchy);
    void delHierarchy(hstd::SPtr<IVertexHierarchy> const& hierarchy);

    /// \brief Get list of all edge providers in the graph: vertex
    /// hierarchies and general edge collections.
    hstd::Vec<IEdgeProvider*> getEdgeProviders();

    /// \brief Get vertex object associated with the edge ID.
    virtual IVertex const* getVertex(VertexID const& id) const = 0;

    /// \brief Get the edge from the collection/hierarchy. Use the edge ID
    /// mask to determine which collection the edge comes from.
    virtual IEdge const* getEdge(EdgeID const& id) const;

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


    /// \brief Track attributes and edge information in the graph
    ///
    /// \warning Call after the vertex has been registered. Should be
    /// called with the full list of vertices to track: this method will
    /// not attempt to expand the set of vertices to include nested ones.
    void trackVertexList(hstd::Vec<VertexID> const& ids);

    /// \brief Un-track attributes and edge information
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


struct TrivialVertex : public IVertex {
    VertexID selfId;
    TrivialVertex(VertexID selfId) : selfId{selfId} {}

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

    json getSerialNonRecursive(IGraph const* graph, VertexID const& id)
        const override {
        return json{};
    }

    hstd::Vec<hstd::SPtr<IAttribute>> attrs;

    hstd::Vec<hstd::SPtr<IAttribute>> getAttributes() const override {
        return attrs;
    }

    void addAttribute(hstd::SPtr<IAttribute> const& attr) override {
        attrs.push_back(attr);
    }
};


struct TrivialEdge : public IEdge {
    using IEdge::IEdge;

    hstd::Vec<hstd::SPtr<IAttribute>> attrs;

    hstd::Vec<hstd::SPtr<IAttribute>> getAttributes() const override {
        return attrs;
    }

    void addAttribute(hstd::SPtr<IAttribute> const& attr) override {
        attrs.push_back(attr);
    }
};

struct TrivialEdgeCollection : public IEdgeCollection {
  public:
    hstd::UnorderedIncrementalStore<EdgeID, TrivialEdge> edgeStore;

    EdgeCollectionID getCategory() const override {
        return getCollectionIdImpl(this);
    }

    const IEdge* getEdge(EdgeID const& id) const override {
        return &edgeStore.at(id);
    }

    hstd::Vec<EdgeID> addAllOutgoing(VertexID const& id) override {
        return {};
    }
};

struct TrivialGraph : public IGraph {
    hstd::UnorderedIncrementalStore<VertexID, TrivialVertex> vertexStore;
    hstd::SPtr<TrivialEdgeCollection>                        edges;

    TrivialGraph() : edges{std::make_shared<TrivialEdgeCollection>()} {}

    VertexID addVertex() {
        return vertexStore.add(TrivialVertex{vertexStore.getNextId()});
    }

    const IVertex* getVertex(VertexID const& id) const override {
        return &vertexStore.at(id);
    }

    EdgeID addEdge(VertexID const& source, VertexID const& target) {
        return edges->edgeStore.add(TrivialEdge{source, target});
    }
};


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
class ILayoutAttribute : public IAttribute {};

class IPortLayoutAttribute : public ILayoutAttribute {
  public:
    /// \brief position + size relative to parent.
    virtual Rect getBBox() const = 0;
};

class IEdgeLayoutAttribute : public ILayoutAttribute {
  public:
    virtual Path getPath() const = 0;
};

class IVertexLayoutAttribute : public ILayoutAttribute {
  public:
    /// \brief Vertex bounding box + position relative to the parent
    virtual Rect getBBox() const = 0;
    virtual hstd::SPtr<hstd::SPtr<IPortLayoutAttribute>> getPorts()
        const = 0;
};

class IGroupLayoutAttribute : public ILayoutAttribute {
  public:
    /// \brief Bounding box of the group, size is absolute, position is
    /// relative to the parent group.
    virtual Rect getBBox() const = 0;
    virtual hstd::SPtr<hstd::SPtr<IPortLayoutAttribute>> getPorts()
        const = 0;
};


DECL_ID_TYPE(IGroup, GroupID, hstd::u64);

class IGroup;
class LayoutRun;

class IPlacementAlgorithm {
  public:
    static constexpr hstd::u16 TemporaryLayoutVertexMask = 0b1111'1111;


    /// \brief Result of the placement algorithm execution
    struct Result {
        hstd::UnorderedMap<GroupID, hstd::SPtr<IGroupLayoutAttribute>>
            groups;
        hstd::UnorderedMap<EdgeID, hstd::SPtr<IEdgeLayoutAttribute>> edges;
        hstd::UnorderedMap<VertexID, hstd::SPtr<IVertexLayoutAttribute>>
            vertices;
    };

    hstd::SPtr<LayoutRun> run;

    /// \brief Execute single layout run on the input group. If the group
    /// contains sub-groups with different layout algorithms, their
    /// placement should already be present in the \ref
    /// LayoutRun::result.
    virtual Result runSingleLayout(layout::GroupID const& group) = 0;

    IPlacementAlgorithm(hstd::SPtr<LayoutRun> run) : run{run} {}
};

class IConstraint {};


/// \brief Non-structural collection of vertices, edges, constraints and
/// sub-groups.
class IGroup {
  public:
    hstd::Vec<GroupID> subGroups;
    /// \brief Optional instance of the layout algorithm to be executed on
    /// the current group.
    hstd::Opt<hstd::SPtr<IPlacementAlgorithm>> algorithm;
    hstd::Vec<hstd::SPtr<IConstraint>>         constraints;
    hstd::SPtr<LayoutRun>                      run;

    virtual hstd::Vec<VertexID> getVertices() const = 0;
    virtual hstd::Vec<EdgeID>   getEdges() const    = 0;

    /// \brief Add the new vertex to this group, and return
    /// backend-specific attributes.
    virtual hstd::SPtr<IVertexVisualAttribute> addVertex(
        VertexID const& id) = 0;

    virtual hstd::SPtr<IEdgeVisualAttribute> addEdge(EdgeID const& id) = 0;

    /// \brief Create a new group object without own layout algorithm and
    /// add it as a sub-group for the current one. It will insert a new
    /// group object in the overall layout run map.
    virtual GroupID addNewSubgroup() = 0;

    /// \brief Add a layout groupt that already exists in the layout run.
    virtual void addExistingSubgroup(GroupID const&) = 0;

    IGroup(hstd::SPtr<LayoutRun> run) : run{run} {}
};

class LayoutRun : public OperationsTracer {
  public:
    hstd::UnorderedIncrementalStore<GroupID, hstd::SPtr<IGroup>> groups;

    hstd::SPtr<IGraph> graph;
    hstd::Vec<GroupID> rootGroups;

    LayoutRun(hstd::SPtr<IGraph> graph) : graph{graph} {}

    void runFullLayout();

    /// \brief Full store for the layout results of all recursive runs.
    IPlacementAlgorithm::Result result;

    IVertex const* getVertex(VertexID const& id) const {
        return graph->getVertex(id);
    }

    IEdge const* getEdge(VertexID const& id) const {
        return graph->getEdge(id);
    }

    hstd::SPtr<IGroup> const& getGroup(GroupID const& id) const {
        return groups.at(id);
    }

    GroupID addGroup(hstd::SPtr<IGroup> const& group) {
        return groups.add(group);
    }

    GroupID addRootGroup(hstd::SPtr<IGroup> const& group) {
        auto result = groups.add(group);
        rootGroups.push_back(result);
        return result;
    }

    hstd::SPtr<IGroup> at(GroupID const& id) const {
        return groups.at(id);
    }

    IGroupLayoutAttribute const& getLayout(GroupID const& id) const {
        return *result.groups.at(id);
    }

    IEdgeLayoutAttribute const& getLayout(EdgeID const& id) const {
        return *result.edges.at(id);
    }

    IVertexLayoutAttribute const& getLayout(VertexID const& id) const {
        return *result.vertices.at(id);
    }
};


} // namespace layout

} // namespace hstd::ext::graph
