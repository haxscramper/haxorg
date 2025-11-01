#pragma once

#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/stdlib/dod_base.hpp>
#include <boost/serialization/strong_typedef.hpp>
#include <hstd/ext/bimap_wrap.hpp>
#include <hstd/ext/graphviz.hpp>

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

class IGraph {
  protected:
    hstd::Vec<IEdgeCollection::Ptr>  collections;
    hstd::Vec<IPropertyTracker::Ptr> trackers;

  public:
    void addTracker(IPropertyTracker::Ptr const& tracker) {
        trackers.push_back(tracker);
    }

    void addCollection(IEdgeCollection::Ptr const& collection) {
        collections.push_back(collection);
    }

    virtual void trackVertex(VertexID const& id);
    virtual void untrackVertex(VertexID const& id);

    virtual void trackVertexList(hstd::Vec<VertexID> const& ids);
    virtual void untrackVertexList(hstd::Vec<VertexID> const& ids);

    virtual json getVertexSerial(VertexID const& id) const = 0;
    virtual hstd::Vec<VertexID> getVertices() const        = 0;


    struct SerialSchema {
        hstd::Vec<json> vertices;
        hstd::Vec<json> edges;
        DESC_FIELDS(SerialSchema, (vertices, edges));
    };

    virtual json getGraphSerial() const;
};
} // namespace org::graph
