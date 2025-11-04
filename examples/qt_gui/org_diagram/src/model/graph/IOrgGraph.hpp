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


BOOST_STRONG_TYPEDEF(hstd::u16, EdgeCategory);

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

    virtual json getSerialNonRecursive(IGraph const* graph) const = 0;
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

    virtual std::size_t getHash() const override;
    virtual bool isEqual(const IGraphObjectBase* other) const override;
    virtual json getSerialNonRecursive(IGraph const* graph) const;
    virtual std::string getRepr() const override {
        return hstd::fmt1(*this);
    }
};

struct IPort : public IGraphObjectBase {
    using id_type = PortID;
    DESC_FIELDS(IPort, ());
};
} // namespace org::graph

template <>
struct std::hash<org::graph::IEdge> {
    std::size_t operator()(org::graph::IEdge const& it) const noexcept {
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

  protected:
    virtual EdgeID addEdge(IEdge const& id);
    virtual void   delEdge(EdgeID const& id);
    EdgeID         getID(IEdge const& edge) const;

  public:
    /// \brief Get the full list of edges stored in the collection
    hstd::Vec<EdgeID> getEdges() const;
    /// \brief Add the vertex to the collection and register all new
    /// outgoing edges.
    hstd::Vec<EdgeID> addVertex(VertexID const& id);
    /// \brief Remove the vertex from teh collection and remove all
    /// incident edges.
    void delVertex(VertexID const& id);

    /// \brief Get already constructed edge object from the store.
    virtual IEdge const&      getEdge(EdgeID const& id) const   = 0;
    virtual hstd::Vec<EdgeID> getOutgoing(VertexID const& vert) = 0;
    virtual EdgeCategory      getCategory() const               = 0;
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
    void addTracker(IPropertyTracker::Ptr const& tracker) {
        trackers.push_back(tracker);
    }

    void addCollection(IEdgeCollection::Ptr const& collection) {
        collections.push_back(collection);
    }

    virtual IVertex const& getVertex(VertexID const& id) const = 0;


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
        hstd::Vec<json>                              vertices;
        hstd::Vec<json>                              edges;
        hstd::Vec<std::string>                       flatVertexIDs;
        hstd::Vec<std::string>                       rootVertixIDs;
        hstd::UnorderedMap<std::string, std::string> vertexParentMap;
        hstd::UnorderedMap<std::string, hstd::Vec<std::string>>
            vertexNestingMap;

        DESC_FIELDS(
            SerialSchema,
            (vertices,
             edges,
             flatVertexIDs,
             rootVertixIDs,
             vertexParentMap,
             vertexNestingMap));
    };

    virtual json getGraphSerial() const;
};
} // namespace org::graph
