#pragma once

#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/stdlib/dod_base.hpp>
#include <boost/serialization/strong_typedef.hpp>
#include <hstd/ext/bimap_wrap.hpp>
#include <hstd/ext/graphviz.hpp>
#include <hstd/stdlib/Set.hpp>

namespace hstd {
template <typename ID, typename T>
struct UnorderedStore {
    hstd::ext::Unordered1to1Bimap<ID, T> store;

    ID add(
        T const&                                 value,
        std::optional<typename ID::id_mask_type> mask = std::nullopt) {
        LOGIC_ASSERTION_CHECK(
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

BOOST_STRONG_TYPEDEF(hstd::u16, EdgeCategory);

DECL_ID_TYPE_MASKED(Vertex, VertexID, hstd::u64, 16);
DECL_ID_TYPE_MASKED(Edge, EdgeID, hstd::u64, 16);
/// \brief Categorize the in/out edge connections between vertices.
///
/// The concept of the node port is linked with the layout, but the the
/// abstract graph interface it is also used to group different connections
/// of edge to the vertices.
DECL_ID_TYPE(Port, PortID, hstd::u64);

struct Vertex {
    using id_type = VertexID;
    DESC_FIELDS(Vertex, ());
};

struct Edge {
    using id_type = EdgeID;

    VertexID          source;
    VertexID          target;
    int               bundleIndex = -1;
    hstd::Opt<PortID> sourcePort  = std::nullopt;
    hstd::Opt<PortID> targetPort  = std::nullopt;
    DESC_FIELDS(
        Edge,
        (source, target, bundleIndex, sourcePort, targetPort));

    bool operator==(Edge const& other) const {
        return this->source == other.source //
            && this->target == other.target
            && this->bundleIndex == other.bundleIndex
            && this->sourcePort == other.sourcePort
            && this->targetPort == other.targetPort;
    }
};

struct Port {
    using id_type = PortID;
    DESC_FIELDS(Port, ());
};
} // namespace org::graph

template <>
struct std::hash<org::graph::Edge> {
    std::size_t operator()(org::graph::Edge const& it) const noexcept {
        std::size_t result = 0;
        hstd::hax_hash_combine(result, it.source);
        hstd::hax_hash_combine(result, it.target);
        hstd::hax_hash_combine(result, it.bundleIndex);
        hstd::hax_hash_combine(result, it.sourcePort);
        hstd::hax_hash_combine(result, it.targetPort);
        return result;
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


class IPropertyTracker : public hstd::SharedPtrApi<IPropertyTracker> {
  public:
    virtual void                trackVertex(VertexID const& vertex)   = 0;
    virtual void                untrackVertex(VertexID const& vertex) = 0;
    virtual hstd::Vec<VertexID> getVertices(IProperty const& prop)    = 0;
};

class IEdgeCollection : public hstd::SharedPtrApi<IEdgeCollection> {
    hstd::UnorderedMap<
        VertexID,
        hstd::UnorderedMap<VertexID, hstd::Vec<EdgeID>>>
        incidence;

    hstd::UnorderedMap<VertexID, hstd::Vec<VertexID>> incoming_from;
    hstd::ext::Unordered1to1Bimap<EdgeID, Edge>       edges;


  protected:
    virtual EdgeID addEdge(Edge const& id);
    virtual void   delEdge(EdgeID const& id);
    Edge const&    getEdge(EdgeID const& id) const;
    EdgeID         getID(Edge const& edge) const;

  public:
    hstd::Vec<EdgeID> getEdges() const {
        hstd::Vec<EdgeID> res;
        for (auto const& e : edges.get_map()) { res.push_back(e.first); }
        return res;
    }

    virtual hstd::Vec<EdgeID> addVertex(VertexID const& id);
    virtual void              delVertex(VertexID const& id);

    virtual hstd::Vec<Edge> getOutgoing(VertexID const& vert) = 0;
    virtual EdgeCategory    getCategory() const               = 0;

    virtual json getEdgeSerial(EdgeID const& id) const = 0;
};

struct org_graph_error : public hstd::CRTP_hexception<org_graph_error> {};

class IGraph {
  protected:
    hstd::Vec<IEdgeCollection::Ptr>  collections;
    hstd::Vec<IPropertyTracker::Ptr> trackers;

    /// \brief Full set of all vertices in the graph
    hstd::UnorderedSet<VertexID> vertexIDs;
    /// \brief Parent -> List of Sub-Vertices mapping
    hstd::UnorderedMap<VertexID, hstd::UnorderedSet<VertexID>> nestedInMap;
    /// \brief Sub-Vertex -> Parent mapping
    hstd::UnorderedMap<VertexID, VertexID> parentMap;
    /// \brief Set of vertices that don't have parent items in the map.
    hstd::UnorderedSet<VertexID> rootVertices;


  public:
    void addTracker(IPropertyTracker::Ptr const& tracker) {
        trackers.push_back(tracker);
    }

    void addCollection(IEdgeCollection::Ptr const& collection) {
        collections.push_back(collection);
    }

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


    virtual json getVertexSerialNonRecursive(VertexID const& id) const = 0;
    struct SerialSchema {
        hstd::Vec<json> vertices;
        hstd::Vec<json> edges;
        DESC_FIELDS(SerialSchema, (vertices, edges));
    };

    virtual json getGraphSerial() const;
};
} // namespace org::graph
