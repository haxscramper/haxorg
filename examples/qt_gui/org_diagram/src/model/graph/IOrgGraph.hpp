#pragma once

#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/stdlib/dod_base.hpp>
#include <boost/serialization/strong_typedef.hpp>
#include <hstd/ext/bimap_wrap.hpp>
#include <hstd/ext/graphviz.hpp>
#include <hstd/stdlib/Set.hpp>
#include <hstd/stdlib/JsonSerde.hpp>

namespace hstd {
template <typename ID, typename T>
struct UnorderedStore {
    hstd::ext::Unordered1to1Bimap<ID, T> store;

    ID add(
        T const&                                 value,
        std::optional<typename ID::id_mask_type> mask = std::nullopt) {
        LOGIC_ASSERTION_CHECK_FMT(
            !store.contains_right(value),
            "Store already contains value {}",
            hstd::fmt1_maybe(value));

        int  current_size = size();
        auto result       = mask.has_value()
                              ? ID::FromMaskedIdx(current_size, mask.value())
                              : ID::FromIndex(current_size);
        store.add_unique(result, value);
        return result;
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
} // namespace hstd

namespace org::graph {
BOOST_STRONG_TYPEDEF(hstd::u16, EdgeCategoryID);
BOOST_STRONG_TYPEDEF(hstd::u16, PropertyTrackerID);
} // namespace org::graph

template <>
struct std::hash<org::graph::EdgeCategoryID> {
    std::size_t operator()(
        org::graph::EdgeCategoryID const& it) const noexcept {
        std::size_t result = 0;
        hstd::hax_hash_combine(result, it.t);
        return result;
    }
};

template <>
struct std::hash<org::graph::PropertyTrackerID> {
    std::size_t operator()(
        org::graph::PropertyTrackerID const& it) const noexcept {
        std::size_t result = 0;
        hstd::hax_hash_combine(result, it.t);
        return result;
    }
};


namespace org::graph {

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

    virtual json getSerialNonRecursive(IGraph const* graph, org::graph::VertexID const& id) const = 0;
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
    virtual bool isEqual(const IGraphObjectBase* other) const override;
    virtual json getSerialNonRecursive(
        IGraph const*             graph,
        org::graph::EdgeID const& id) const;
    virtual std::string getRepr() const override {
        return hstd::fmt1(*this);
    }
};

struct IPort : public IGraphObjectBase {
    using id_type = PortID;
    DESC_FIELDS(IPort, ());
};
} // namespace org::graph

template <org::graph::IsGraphObject T>
struct std::hash<T> {
    std::size_t operator()(T const& it) const noexcept {
        return it.getHash();
    }
};

namespace org::graph {
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

class IEdgeCollection {
    hstd::UnorderedMap<
        VertexID,
        hstd::UnorderedMap<VertexID, hstd::Vec<EdgeID>>>
        incidence;

    hstd::UnorderedMap<VertexID, hstd::Vec<VertexID>> incoming_from;


  public:
    /// \brief Get list of all outgoing edges for the target vertex
    hstd::Vec<EdgeID> getOutgoing(VertexID const& vert) const;

    hstd::Vec<EdgeID> getIncoming(VertexID const& vert) const;

    /// \brief Add the vertex to the edge collection without any of the
    /// incoming/outgoing edges.
    void trackVertex(VertexID const& vert);
    /// \brief Remove the vertex from the collection including any outgoing
    /// edges. Edge removal is done using `untrackEdge`.
    void untrackVertex(VertexID const& vert);
    /// \brief Track the new edge in the collection. Associated
    /// `IEdge`-derived object should already be accessible through the
    /// `getEdge()` virtual method override.
    void trackEdge(EdgeID const& id);
    /// \brief Remove the edge from the collection. This method is called
    /// by the `untrackVertex`.
    void untrackEdge(EdgeID const& id);

    /// \brief Get the full list of edges stored in the collection
    hstd::Vec<EdgeID> getEdges() const;
    /// \brief Remove the vertex from teh collection and remove all
    /// incident edges.
    void delVertex(VertexID const& id);

    /// \brief Return edge category for this collection, uniquely
    /// identifying this specific one collection.
    virtual EdgeCategoryID getCategory() const = 0;

    /// \brief Get already constructed edge object from the store.
    virtual IEdge const& getEdge(EdgeID const& id) const = 0;

    /// \brief Add all edges outgoing from the `id`. The vertex itself
    /// should already be registered with `trackVertex`.
    ///
    /// \note The override of this method should make use of `trackEdge` to
    /// populate the edge collection tracker tables. The returned list of
    /// edges is used
    virtual hstd::Vec<EdgeID> addAllOutgoing(VertexID const& id) = 0;

    virtual std::string getStableID() const = 0;
};

struct org_graph_error : public hstd::CRTP_hexception<org_graph_error> {};

class IGraph {
  protected:
    hstd::UnorderedMap<EdgeCategoryID, hstd::SPtr<IEdgeCollection>>
        collections;
    hstd::UnorderedMap<PropertyTrackerID, hstd::SPtr<IPropertyTracker>>
        trackers;

    /// \brief Full set of all vertices in the graph
    hstd::UnorderedSet<VertexID> vertexIDs;
    /// \brief Parent -> List of Sub-Vertices mapping
    hstd::UnorderedMap<VertexID, hstd::UnorderedSet<VertexID>> nestedInMap;
    /// \brief Sub-Vertex -> Parent mapping
    hstd::UnorderedMap<VertexID, VertexID> parentMap;
    /// \brief Set of vertices that don't have parent items in the map.
    hstd::UnorderedSet<VertexID> rootVertices;

  protected:
    /// \brief Add the vertex to the graph collection. Will not
    /// automatically register all nested vertices and recursive data.
    /// After the base vertex is registered, provide additional structural
    /// information using `trackSubVertexRelation`.
    void registerVertex(VertexID const& id);

    /// \brief Remove vertex from the graph collection and recursively drop
    /// all the nested vertices from the graph to correct the invalid
    /// state.
    ///
    /// \note No follow-up calls to `untrackSubVertexRelation` is
    /// necessary to match the `trackSubVertexRelation`.
    ///
    /// \warning Calling this method will RECURSIVELY DROP ALL SUB-VERTICES
    /// under `id`.
    void unregisterVertex(VertexID const& id);

  public:
    void addTracker(hstd::SPtr<IPropertyTracker> const& tracker);
    void delTracker(hstd::SPtr<IPropertyTracker> const& tracker);
    void addCollection(hstd::SPtr<IEdgeCollection> const& collection);
    void delCollection(hstd::SPtr<IEdgeCollection> const& collection);

    virtual IVertex const& getVertex(VertexID const& id) const = 0;


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
    hstd::Vec<VertexID> getHierarchyCrossings(EdgeID const& id) const;


    /// \brief Provide additional information about the vertex nesting
    /// relation.
    ///
    /// The vertex can only be nested under one parent and
    /// present in the graph once. Both parent and sub must be existing
    /// vertices.
    ///
    /// \warning After the vertex has been register this method needs to be
    /// called to record additional structural information about the
    /// sub-vertices.
    void trackSubVertexRelation(
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

    hstd::Vec<VertexID> getAllVertices() const;
    hstd::Vec<VertexID> getRootVertices() const;
    hstd::Vec<VertexID> getSubVertices(VertexID const& id) const;
    hstd::Opt<VertexID> getParentVertex(VertexID const& id) const;
    IEdge const&        getEdge(EdgeID const& id) const;

    /// \brief Return the highest level of nesting in the graph
    int getMaxNestingLevel() const;

    hstd::Vec<VertexID> getParentChain(VertexID const& id) const;


    struct SerialSchema {
        struct EdgeCategory {
            hstd::Vec<json> edges;
            std::string     categoryName;
            /// \brief EdgeId -> List of Vertex IDs for parent hierarchies
            /// it has crossed. See `getHierarchyCrossings` method for more
            /// details.
            hstd::UnorderedMap<std::string, hstd::Vec<std::string>>
                hierarchyEdgeCrossings;
            DESC_FIELDS(
                EdgeCategory,
                (edges, categoryName, hierarchyEdgeCrossings));
        };


        hstd::UnorderedMap<std::string, json>         vertices;
        hstd::UnorderedMap<std::string, EdgeCategory> edges;
        hstd::Vec<std::string>                        flatVertexIDs;
        hstd::Vec<std::string>                        rootVertexIDs;
        hstd::UnorderedMap<std::string, std::string>  vertexParentMap;
        hstd::UnorderedMap<std::string, hstd::Vec<std::string>>
            vertexNestingMap;

        int maxNestingLevel = 0;

        DESC_FIELDS(
            SerialSchema,
            (vertices,
             edges,
             flatVertexIDs,
             rootVertexIDs,
             vertexParentMap,
             vertexNestingMap,
             maxNestingLevel));
    };

    virtual json getGraphSerial() const;
};


} // namespace org::graph
