/**

\file graph_base.hpp
\brief Provide base classes for the graph and visualization.

High-level overview of the design:

- All graph elements follow the DOD-like design, with the values accessible
  both using ID and the pointers. The value itself is managed by the
derived classes, this file mainly provides virtual methods to `get*` or
`add*`.
- The grap stores a single collection of vertices, but the edges are split
  into different collections, with explicit distinction between "hierarchy"
  edge collections (acyclic tree with a set of starting/parent nodes) and
  general collection (adjacency list with no constraints).

Terminology used

- **semantic** or **structural** refer  to the classes dedicated to
  managing the vertices, edges and ports and that are not concerned with
  the visualization details.
  - \ref hstd::ext::graph::IGraph
  - \ref hstd::ext::graph::IVertex
  - \ref hstd::ext::graph::IEdge
  - \ref hstd::ext::graph::IPort this one might have dual use for visual
    and for semantic.
  - \ref hstd::ext::graph::IAttribute dual use for visual and semantic.
    For visual it will use \ref hstd::ext::graph::layout::IVisualAttribute
    and \ref hstd::ext::graph::layout::ILayoutAttribute
- **visual** refer to the classes for the graph layout and visualization
  - \ref hstd::ext::graph::layout::LayoutRun
  - \ref hstd::ext::graph::layout::IConstraint
  - \ref hstd::ext::graph::layout::IGroup
  - \ref hstd::ext::graph::layout::IPlacementAlgorithm
- **tracker** refer to classes derived from the \ref
  hstd::ext::graph::IAttributeTracker

*/

#pragma once

#include <hstd/stdlib/dod_base.hpp>
#include <boost/serialization/strong_typedef.hpp>
#include <hstd/stdlib/JsonSerde.hpp>
#include <hstd/stdlib/Set.hpp>
#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/ext/bimap_wrap.hpp>
#include <hstd/stdlib/OptFormatter.hpp>
#include "hstd/stdlib/TraceBase.hpp"
#include <hstd/ext/geometry/hstd_geometry.hpp>
#include <hstd/ext/geometry/hstd_visual.hpp>
#include <boost/bimap.hpp>
#include <boost/bimap/unordered_multiset_of.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/composite_key.hpp>

namespace bmi = boost::multi_index;

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

    T const& at(ID const& id) const {
        LOGIC_ASSERTION_CHECK_FMT(contains(id), "Id {} not stored", id);
        return Base::at(id);
    }

    T& at(ID const& id) {
        LOGIC_ASSERTION_CHECK_FMT(contains(id), "Id {} not stored", id);
        return Base::at(id);
    }

    ID getNextId(
        std::optional<typename ID::id_mask_type> mask = std::nullopt)
        const {
        int  current_size = size();
        auto id = mask.has_value()
                    ? ID::FromMaskedIdx(current_size, mask.value())
                    : ID::FromIndex(current_size);
        return ID(id);
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

/// \brief graph structure and visualization
namespace hstd::ext::graph {

struct graph_error : public hstd::CRTP_hexception<graph_error> {};

struct structure_error
    : public hstd::CRTP_hexception<structure_error, graph_error> {};

struct port_structure_error
    : public hstd::CRTP_hexception<port_structure_error, structure_error> {
};

struct edge_structure_error
    : public hstd::CRTP_hexception<edge_structure_error, structure_error> {
};

struct vertex_structure_error
    : public hstd::
          CRTP_hexception<vertex_structure_error, structure_error> {};

using namespace hstd::ext::geometry;
/// \brief 16-bit ID to track edge collection. Used as a mask in the
/// `EdgeID`.
///
/// Collection ID is created by the IEdgeCollection::getCollectionId
BOOST_STRONG_TYPEDEF(hstd::u16, EdgeCollectionID);
/// \brief 16-bit ID to identify the attribute tracker.
BOOST_STRONG_TYPEDEF(hstd::u16, AttributeTrackerID);
BOOST_STRONG_TYPEDEF(hstd::u16, PortCollectionID);
/// \brief 16-bit ID to track the graph hierarchies. Used as a mask in the
/// `EdgeID`.
BOOST_STRONG_TYPEDEF(hstd::u16, GraphHierarchyID);
} // namespace hstd::ext::graph

template <>
struct std::formatter<hstd::ext::graph::EdgeCollectionID>
    : public hstd::std_strong_typedef_formatter<
          hstd::ext::graph::EdgeCollectionID> {};

template <>
struct std::formatter<hstd::ext::graph::PortCollectionID>
    : public hstd::std_strong_typedef_formatter<
          hstd::ext::graph::PortCollectionID> {};

template <>
struct std::formatter<hstd::ext::graph::AttributeTrackerID>
    : public hstd::std_strong_typedef_formatter<
          hstd::ext::graph::AttributeTrackerID> {};

template <>
struct std::formatter<hstd::ext::graph::GraphHierarchyID>
    : public hstd::std_strong_typedef_formatter<
          hstd::ext::graph::GraphHierarchyID> {};

template <>
struct std::hash<hstd::ext::graph::EdgeCollectionID>
    : public hstd::strong_typedef_hash<
          hstd::ext::graph::EdgeCollectionID> {};

template <>
struct std::hash<hstd::ext::graph::PortCollectionID>
    : public hstd::strong_typedef_hash<
          hstd::ext::graph::PortCollectionID> {};

template <>
struct std::hash<hstd::ext::graph::AttributeTrackerID>
    : public hstd::strong_typedef_hash<
          hstd::ext::graph::AttributeTrackerID> {};

template <>
struct std::hash<hstd::ext::graph::GraphHierarchyID>
    : public hstd::strong_typedef_hash<
          hstd::ext::graph::GraphHierarchyID> {};

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
DECL_ID_TYPE_MASKED(IPort, PortID, hstd::u64, 16);

using VertexIDSet = hstd::UnorderedSet<VertexID>;
using EdgeIDSet   = hstd::UnorderedSet<EdgeID>;
using PortIDSet   = hstd::UnorderedSet<PortID>;

class IGraph;

/// \brief Base class for all attributes associated with vertices. The
/// attribute might be an individual value, or a complex composite object,
/// depending on the use case.
struct IAttribute {
  public:
    virtual ~IAttribute() = default;

    virtual std::string getRepr() const { return ""; }

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
    virtual void setAttributes(
        hstd::Vec<hstd::SPtr<IAttribute>> const& attrs) = 0;

    /// \brief Get first instance of the attribute with dynamic type `T`.
    template <typename T>
        requires std::derived_from<T, IAttribute>
    hstd::Opt<hstd::SPtr<T>> getOptionalAttribute() const {
        for (auto const& attr : getAttributes()) {
            if (attr->isInstance<T>()) {
                return std::dynamic_pointer_cast<T>(attr);
            }
        }

        return std::nullopt;
    }

    template <typename T>
        requires std::derived_from<T, IAttribute>
    bool hasOptionalAttribute() const {
        return getOptionalAttribute<T>().has_value();
    }

    /// \brief Get all attributes with dynamic type T
    template <typename T>
        requires std::derived_from<T, IAttribute>
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
        requires std::derived_from<T, IAttribute>
    hstd::SPtr<T> getUniqueAttribute(
        std::string const& err_ctx = "") const {
        hstd::SPtr<T> result;
        for (auto const& attr : getAttributes()) {
            if (attr->isInstance<T>()) {
                if (result == nullptr) {
                    result = std::dynamic_pointer_cast<T>(attr);
                } else {
                    throw graph_error::init(
                        hstd::fmt(
                            "Graph object is expected to have exactly one "
                            "attribute of type {}, but found two. {}",
                            hstd::value_metadata<T>::typeName(),
                            err_ctx));
                }
            }
        }

        if (result == nullptr) {
            throw graph_error::init(
                hstd::fmt(
                    "Graph object is expected to have exactly one "
                    "attribute of type {}, but found none. {}",
                    hstd::value_metadata<T>::typeName(),
                    err_ctx));
        }

        return result;
    }

    template <typename T = IAttribute>
        requires std::derived_from<T, IAttribute>
    void addUniqueAttribute(
        hstd::SPtr<T> const& attr,
        std::string const&   err_ctx = "") {
        for (auto const& existing : getAttributes()) {
            if (typeid(attr.get()) == typeid(existing.get())) {
                throw graph_error::init(
                    hstd::fmt(
                        "Graph object is required to have only one "
                        "attribute of type {}, but the code is attempting "
                        "to add a new instance. {}",
                        typeid(attr.get()).name(),
                        err_ctx));
            }
        }

        addAttribute(attr);
    }

    template <typename T = IAttribute>
        requires std::derived_from<T, IAttribute>
    void addOrResetUniqueAttribute(hstd::SPtr<T> const& attr) {
        hstd::Vec<hstd::SPtr<IAttribute>> new_list;
        for (auto const& existing : getAttributes()) {
            if (typeid(attr.get()) == typeid(existing.get())) {
                new_list.push_back(attr);
            } else {
                new_list.push_back(existing);
            }
        }
        setAttributes(new_list);
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

struct TrivialVertex : public IVertex {
    VertexID             selfId;
    hstd::Opt<hstd::Str> stableIdOverride;

    TrivialVertex(VertexID selfId) : selfId{selfId} {}

    std::string getStableId() const override {
        if (stableIdOverride) {
            return stableIdOverride.value();
        } else {
            return IVertex::getStableId();
        }
    }

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

  public:
    void setAttributes(
        hstd::Vec<hstd::SPtr<IAttribute>> const& attrs) override {
        this->attrs = attrs;
    }
};


struct IEdge
    : public IGraphObjectBase
    , public IAttributeObject {
    using id_type = EdgeID;

    DESC_FIELDS(IEdge, ());

    struct SerialSchema {
        std::string edgeId;
        DESC_FIELDS(SerialSchema, (edgeId));
    };

    bool operator==(IEdge const& other) const {
        return this->isEqual(&other);
    }

    virtual std::size_t getHash() const override;
    virtual bool isEqual(IGraphObjectBase const* other) const override;
    virtual json getSerialNonRecursive(
        IGraph const*                   graph,
        hstd::ext::graph::EdgeID const& id) const;
    virtual std::string getRepr() const override {
        return hstd::fmt1(*this);
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

  public:
    void setAttributes(
        hstd::Vec<hstd::SPtr<IAttribute>> const& attrs) override {
        this->attrs = attrs;
    }
};

/// \brief Connection port or edge grouping port
///
/// \note For visualizatino purposes ports might be independently managed
/// by the layout run. Semantic graph
struct IPort
    : public IGraphObjectBase
    , public IAttributeObject {
    using id_type = PortID;
    DESC_FIELDS(IPort, ());
};


class IPortCollection {
    struct PortEntry {
        VertexID vertex;
        EdgeID   edge;
        /// \brief To distinguish edge ports in case of self-loops.
        bool   is_source;
        PortID port;
    };

    // Tags for each index
    struct ByCompositeKey {};
    struct ByPortID {};
    struct ByVertexID {};
    struct ByEdgeID {};

    using PortContainer = bmi::multi_index_container<
        PortEntry,
        bmi::indexed_by<
            // Unique: (vertex, edge, is_start) — the "left" side of the
            // bimap
            bmi::ordered_unique<
                bmi::tag<ByCompositeKey>,
                bmi::composite_key<
                    PortEntry,
                    bmi::member<PortEntry, VertexID, &PortEntry::vertex>,
                    bmi::member<PortEntry, EdgeID, &PortEntry::edge>,
                    bmi::member<PortEntry, bool, &PortEntry::is_source>>>,
            // Unique: port — the "right" side of the bimap
            bmi::ordered_unique<
                bmi::tag<ByPortID>,
                bmi::member<PortEntry, PortID, &PortEntry::port>>,
            // Non-unique: vertex — range query for "ports of vertex"
            bmi::ordered_non_unique<
                bmi::tag<ByVertexID>,
                bmi::member<PortEntry, VertexID, &PortEntry::vertex>>,
            // Non-unique: edge — range query for "ports of edge"
            bmi::ordered_non_unique<
                bmi::tag<ByEdgeID>,
                bmi::member<PortEntry, EdgeID, &PortEntry::edge>>>>;

  protected:
    PortContainer ports;


    auto getPortIterator(PortID const& pid) const {
        auto& idx = ports.get<ByPortID>();
        auto  it  = idx.find(pid);
        if (it == idx.end()) {
            throw port_structure_error::init(
                hstd::fmt(
                    "port {} is not registered in the collection", pid));
        }
        return it;
    }

    /// \brief Base method to add ports to the collection, derived classes
    /// should provide the storage implementation that will generate port
    /// ID, and provide a method that will require only
    /// vertex+edge+is-start.
    void addPort(VertexID vertex, EdgeID edge, bool is_start, PortID pid) {
        auto& idx = ports.get<ByCompositeKey>();
        if (idx.find(std::make_tuple(vertex, edge, is_start))
            != idx.end()) {
            throw port_structure_error::init(
                hstd::fmt(
                    "Port for vertex {} edge {} {} already exists",
                    vertex,
                    edge,
                    is_start ? "start" : "end"));
        }
        ports.insert(PortEntry{vertex, edge, is_start, pid});
    }


  public:
    virtual ~IPortCollection() = default;

    /// \brief Check if the collection has port
    virtual PortCollectionID getCategory() const       = 0;
    virtual IPort const*     getPort(PortID pid) const = 0;

    IPort* getmPort(PortID pid) {
        return const_cast<IPort*>(std::as_const(*this).getPort(pid));
    }

    EdgeID getEdgeForPort(PortID pid) const {
        return getPortIterator(pid)->edge;
    }

    VertexID getVertexForPort(PortID pid) const {
        return getPortIterator(pid)->vertex;
    }

    bool isSourcePort(PortID pid) const {
        return getPortIterator(pid)->is_source;
    }

    hstd::Vec<PortID> getPortsForVertex(VertexID vid) const {
        auto& idx         = ports.get<ByVertexID>();
        auto [begin, end] = idx.equal_range(vid);
        hstd::Vec<PortID> result;
        for (; begin != end; ++begin) { result.push_back(begin->port); }
        return result;
    }

    hstd::Pair<PortID, PortID> getPortsForEdge(EdgeID eid) const {
        auto& idx                     = ports.get<ByEdgeID>();
        auto [begin, end]             = idx.equal_range(eid);
        std::pair<PortID, PortID> res = {PortID::Nil(), PortID::Nil()};
        res.first                     = begin->port;
        ++begin;
        res.second = begin->port;
        return res;
    }

    bool hasPortConnection(VertexID vid, EdgeID eid, bool is_start) const {
        auto& idx = ports.get<ByCompositeKey>();
        auto  it  = idx.find(std::make_tuple(vid, eid, is_start));
        return it != idx.end();
    }

    bool hasSourcePort(VertexID vid, EdgeID eid) const {
        return hasPortConnection(vid, eid, true);
    }

    bool hasTargetPort(VertexID vid, EdgeID eid) const {
        return hasPortConnection(vid, eid, false);
    }

    PortID getPortForConnection(VertexID vid, EdgeID eid, bool is_start)
        const {
        auto& idx = ports.get<ByCompositeKey>();
        auto  it  = idx.find(std::make_tuple(vid, eid, is_start));
        if (it == idx.end()) {
            throw port_structure_error::init(
                hstd::fmt(
                    "No {} connection between vertex {} and edge {}",
                    is_start ? "start" : "end",
                    vid,
                    eid));
        }
        return it->port;
    }

    PortID getSourcePort(VertexID vid, EdgeID eid) const {
        return getPortForConnection(vid, eid, true);
    }

    PortID getTargetPort(VertexID vid, EdgeID eid) const {
        return getPortForConnection(vid, eid, false);
    }

    void delPort(PortID pid) {
        auto it = getPortIterator(pid);
        ports.get<ByPortID>().erase(it);
    }
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
    virtual IEdge const* getEdge(EdgeID const& id) const   = 0;
    virtual VertexID     getSource(EdgeID const& id) const = 0;
    virtual VertexID     getTarget(EdgeID const& id) const = 0;

    /// \brief Return stable identifier for this edge collection.
    virtual std::string getStableID() const;

    /// \brief Get the full list of edges stored in the collection
    virtual EdgeIDSet getEdges() const = 0;

    /// \brief Add the vertex to the edge collection without any of the
    /// incoming/outgoing edges.
    virtual void trackVertex(VertexID const& vert) = 0;

    struct DependantDeletion {
        VertexIDSet vertices;
        EdgeIDSet   edges;
    };

    /// \brief Remove the vertex from the collection including any outgoing
    /// edges. Edge removal is done using `untrackEdge`.
    virtual DependantDeletion untrackVertex(VertexID const& vert) = 0;


    /// \brief Get list of all outgoing edges for the target vertex
    virtual EdgeIDSet getOutgoing(VertexID const& vert) const = 0;

    /// \brief Get list of all incoming edges for the target vertex
    virtual EdgeIDSet getIncoming(VertexID const& vert) const = 0;
    virtual bool      hasEdge(EdgeID const& id) const         = 0;

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
    hstd::UnorderedMap<EdgeID, hstd::Pair<VertexID, VertexID>>
        source_target;

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
    EdgeIDSet         getEdges() const override;
    EdgeIDSet         getOutgoing(VertexID const& vert) const override;
    EdgeIDSet         getIncoming(VertexID const& vert) const override;
    void              trackVertex(VertexID const& vert) override;
    DependantDeletion untrackVertex(VertexID const& vert) override;

    VertexID getSource(EdgeID const& id) const override {
        return source_target.at(id).first;
    }

    VertexID getTarget(EdgeID const& id) const override {
        return source_target.at(id).second;
    }

    /// \brief Get list of edges in a specific sub-set of the stored
    /// vertices. Both source and target must be in the subset.
    hstd::UnorderedSet<EdgeID> getFullyIncludedEdges(
        hstd::UnorderedSet<VertexID> const& subset) const {
        hstd::UnorderedSet<EdgeID> res;
        for (auto const& id : getEdges()) {
            if (subset.contains(getSource(id))
                && subset.contains(getTarget(id))) {
                res.incl(id);
            }
        }

        return res;
    }

    /// \brief Get list of edges that are at least partially included in
    /// the subset: at least source or target must be in the subset.
    hstd::UnorderedSet<EdgeID> getPartiallyIncludedEdges(
        hstd::UnorderedSet<VertexID> const& subset) const {
        hstd::UnorderedSet<EdgeID> res;
        for (auto const& id : getEdges()) {
            if (subset.contains(getSource(id))
                || subset.contains(getTarget(id))) {
                res.incl(id);
            }
        }

        return res;
    }

    virtual void trackEdge(
        EdgeID const&   id,
        VertexID const& source,
        VertexID const& target);
    /// \brief Remove the edge from the collection. This method is called
    /// by the `untrackVertex`.
    virtual void untrackEdge(EdgeID const& id);
};


struct TrivialEdgeCollection : public IEdgeCollection {
  public:
    hstd::UnorderedIncrementalStore<EdgeID, TrivialEdge> edgeStore;

    EdgeCollectionID collection_id = EdgeCollectionID{};

    bool hasEdge(EdgeID const& id) const override {
        return edgeStore.contains(id);
    }

    EdgeID addEdge(VertexID const& source, VertexID const& target) {
        auto res = edgeStore.add(TrivialEdge{}, getCategory());
        trackEdge(res, source, target);
        return res;
    }

    TrivialEdgeCollection(EdgeCollectionID const& id)
        : collection_id{id} {}

    EdgeCollectionID getCategory() const override { return collection_id; }

    const IEdge* getEdge(EdgeID const& id) const override {
        return &edgeStore.at(id);
    }
};

struct IdOnlyEdgeCollection : public IEdgeCollection {
  public:
    hstd::UnorderedSet<EdgeID> edgeStore;

    EdgeCollectionID collection_id = EdgeCollectionID{};

    bool hasEdge(EdgeID const& id) const override {
        return edgeStore.contains(id);
    }

    IdOnlyEdgeCollection(EdgeCollectionID const& id) : collection_id{id} {}

    EdgeCollectionID getCategory() const override { return collection_id; }

    const IEdge* getEdge(EdgeID const& id) const override {
        return nullptr;
    }
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
    hstd::ext::Unordered1to1Bimap<hstd::Pair<VertexID, VertexID>, EdgeID>
        edgeTracker;

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
    virtual EdgeID trackSubVertexRelation(
        VertexID const& parent,
        VertexID const& sub);

    VertexID getSource(EdgeID const& edge) const override {
        return edgeTracker.at_left(edge).first;
    }

    VertexID getTarget(EdgeID const& edge) const override {
        return edgeTracker.at_left(edge).first;
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

    /// \brief Return full parent chain for `id`, from immediate parent up
    /// to the root.
    hstd::Vec<VertexID> getParentChain(VertexID const& id) const;

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
    EdgeCollectionID getCategory() const override {
        return EdgeCollectionID(getHierarchyId());
    }

    const IEdge* getEdge(EdgeID const& id) const override {
        return &edgeStore.at(id);
    }

    bool hasEdge(EdgeID const& id) const override {
        return edgeStore.contains(id);
    }

    GraphHierarchyID getHierarchyId() const override {
        return getHierarchyIdImpl(this);
    }

    EdgeID trackSubVertexRelation(
        VertexID const& parent,
        VertexID const& sub) override {
        auto id = IVertexHierarchy::trackSubVertexRelation(parent, sub);
        edgeStore.insert_or_assign(id, TrivialEdge{});
        return id;
    }
};

struct IdOnlyHierarchy : public IVertexHierarchy {
    hstd::UnorderedSet<EdgeID> edgeStore;

  public:
    EdgeCollectionID getCategory() const override {
        return EdgeCollectionID(getHierarchyId());
    }

    const IEdge* getEdge(EdgeID const& id) const override {
        return nullptr;
    }

    bool hasEdge(EdgeID const& id) const override {
        return edgeStore.contains(id);
    }

    GraphHierarchyID getHierarchyId() const override {
        return getHierarchyIdImpl(this);
    }
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

  public:
    struct Crossing {
        GraphHierarchyID    hierarchy;
        hstd::Vec<VertexID> crossings;
        DESC_FIELDS(Crossing, (hierarchy, crossings));
    };

    /// \name IGraph tracker/provider operations
    /// @{
    void addTracker(hstd::SPtr<IAttributeTracker> const& tracker);
    void delTracker(hstd::SPtr<IAttributeTracker> const& tracker);
    void addCollection(hstd::SPtr<IEdgeCollection> const& collection);
    void delCollection(hstd::SPtr<IEdgeCollection> const& collection);
    void addHierarchy(hstd::SPtr<IVertexHierarchy> const& hierarchy);
    void delHierarchy(hstd::SPtr<IVertexHierarchy> const& hierarchy);

    bool hasCollection(hstd::SPtr<IEdgeCollection> const& collection);
    bool hasHierarchy(hstd::SPtr<IVertexHierarchy> const& hierarchy);

    /// \brief Get list of all edge providers in the graph: vertex
    /// hierarchies and general edge collections.
    hstd::Vec<IEdgeProvider*> getEdgeProviders();
    /// @}

    /// \name Vertices
    /// @{
    /// \brief Get vertex object associated with the edge ID.
    virtual IVertex const* getVertex(VertexID const& id) const = 0;
    virtual IVertex*       getMVertex(VertexID const& id) const {
        return const_cast<IVertex*>(getVertex(id));
    }

    template <typename T = IVertex>
        requires std::derived_from<T, IVertex>
    T const* getCastVertex(VertexID const& id) const {
        return hstd::validated_dynamic_cast<T>(getVertex(id));
    }

    template <typename T = IVertex>
        requires std::derived_from<T, IVertex>
    T* getCastMVertex(VertexID const& id) const {
        return hstd::validated_dynamic_cast<T>(getMVertex(id));
    }

    /// \brief Track attributes and edge information in the graph
    ///
    /// Add the vertex to the graph collection. Will not
    /// automatically register all nested vertices and recursive data.
    /// After the base vertex is registered, provide additional structural
    /// information using `trackSubVertexRelation`.
    ///
    /// \warning Should be called with the full list of vertices to
    /// track: this method will not attempt to expand the set of vertices
    /// to include nested ones.
    void trackVertex(VertexID const& ids);
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
    hstd::UnorderedMap<GraphHierarchyID, IEdgeCollection::DependantDeletion> untrackVertex(
        VertexID const& id);
    /// @}

    /// \name Vertex hierarchies
    /// @{
    /// \brief Get list of all vertices stored in the graph
    VertexIDSet getAllVertices() const;
    /// \brief Get root vertices for the specified hierarchy
    VertexIDSet getRootVertices(GraphHierarchyID const& hierarchy) const;
    /// \brief Get sub vertices for the specified hierarchy
    VertexIDSet getSubVertices(
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

    /// \brief For id with given ID, compute the list of vertex
    /// boundaries it crossed in each tracked hierarchy between the source
    /// and the target.
    hstd::Vec<Crossing> getHierarchyCrossings(EdgeID const& edge_id) const;
    /// @}

    /// \name Edges
    /// @{
    /// \brief Get the edge from the collection/hierarchy. Use the edge ID
    /// mask to determine which collection the edge comes from.
    virtual IEdge const* getEdge(EdgeID const& id) const {
        return getEdgeProvider(id)->getEdge(id);
    }

    virtual IEdge* getMEdge(EdgeID const& id) {
        return const_cast<IEdge*>(getEdge(id));
    }

    GraphHierarchyID getHierarchyID(EdgeID const& id) const;
    EdgeCollectionID getCollectionID(EdgeID const& id) const;

    hstd::SPtr<IVertexHierarchy> getHierarchy(EdgeID const& id) const {
        return hierarchies.at(getHierarchyID(id));
    }

    hstd::SPtr<IEdgeCollection> getEdgeCollection(EdgeID const& id) const {
        return collections.at(getCollectionID(id));
    }

    hstd::SPtr<IEdgeProvider> getEdgeProvider(EdgeID const& id) const {
        if (IEdgeProvider::isHierarchyEdge(id)) {
            return getHierarchy(id);
        } else {
            return getEdgeCollection(id);
        }
    }

    virtual VertexID getSource(EdgeID const& id) const;
    virtual VertexID getTarget(EdgeID const& id) const;
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
    /// @}

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

    std::string getDebugVertexFormat(VertexID const& vert) const {
        return hstd::fmt(
            "vertex {} ({})", vert, getVertex(vert)->getStableId());
    }

    std::string getDebugEdgeFormat(EdgeID const& edge) const {
        return hstd::fmt(
            "edge {} ({}) from {} to {}",
            edge,
            getEdge(edge) ? getEdge(edge)->getStableId() : "nullptr",
            getDebugVertexFormat(getSource(edge)),
            getDebugVertexFormat(getSource(edge)));
    }
};


struct TrivialGraph : public IGraph {
    hstd::UnorderedIncrementalStore<VertexID, TrivialVertex> vertexStore;
    hstd::SPtr<TrivialEdgeCollection>                        edges;

    TrivialGraph()
        : edges{std::make_shared<TrivialEdgeCollection>(
              EdgeCollectionID{1})} {
        addCollection(edges);
    }

    VertexID addVertex() {
        auto result = vertexStore.add(
            TrivialVertex{vertexStore.getNextId()});
        trackVertex(result);
        return result;
    }

    const IVertex* getVertex(VertexID const& id) const override {
        return &vertexStore.at(id);
    }

    EdgeID addEdge(VertexID const& source, VertexID const& target) {
        return edges->addEdge(source, target);
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
        res.elements.push_back(
            visual::VisElement{visual::VisElement::RectShape{getBBox()}});
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
        return res;
    }
};

class IGroupLayoutAttribute : public IVertexLayoutAttribute {};


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

class LayoutRun : public OperationsTracer {
  public:
    hstd::SPtr<IGraph>               graph;
    hstd::SPtr<IdOnlyHierarchy>      groups;
    hstd::SPtr<IdOnlyEdgeCollection> edges;

    LayoutRun(
        hstd::SPtr<IGraph> graph,
        EdgeCollectionID   edges_id = EdgeCollectionID{9999})
        : graph{graph}
        , groups{std::make_shared<IdOnlyHierarchy>()}
        , edges{std::make_shared<IdOnlyEdgeCollection>(edges_id)} {
        graph->addCollection(edges);
        graph->addHierarchy(groups);
        hstd::logic_assertion_check_not_nil(graph);
        hstd::logic_assertion_check_not_nil(groups);
        hstd::logic_assertion_check_not_nil(edges);
    }

    void runFullLayout();

    /// \brief Full store for the layout results of all recursive runs.
    IPlacementAlgorithm::Result result;

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

    template <typename T = IGroupVisualAttribute>
        requires std::derived_from<T, IGroupVisualAttribute>
    hstd::SPtr<T> getGroup(VertexID const& id) const {
        return graph->getVertex(id)->getUniqueAttribute<T>(
            graph->getDebugVertexFormat(id));
    }

    template <typename T = IEdgeVisualAttribute>
        requires std::derived_from<T, IEdgeVisualAttribute>
    hstd::SPtr<T> getEdgeVisualAttribute(EdgeID const& id) const {
        return graph->getEdge(id)->getUniqueAttribute<T>(
            graph->getDebugEdgeFormat(id));
    }

    template <typename T = IVertexVisualAttribute>
        requires std::derived_from<T, IVertexVisualAttribute>
    hstd::SPtr<T> getVertexVisualAttribute(VertexID const& id) const {
        return graph->getVertex(id)->getUniqueAttribute<T>(
            graph->getDebugVertexFormat(id));
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
        return graph->getVertex(id)->hasOptionalAttribute<T>();
    }

    VertexIDSet getVertices(VertexID const& id) const {
        LOGIC_ASSERTION_CHECK(
            isGroupVertex(id),
            "Cannot get nested vertices from non-group");
        VertexIDSet res;
        for (auto const& sub : groups->getSubVertices(id)) {
            if (!isGroupVertex(sub)) { res.incl(sub); }
        }
        return res;
    }

    VertexIDSet getRootGroups() const {
        VertexIDSet res;
        for (auto const& sub : groups->getRootVertices()) {
            if (isGroupVertex(sub)) { res.incl(sub); }
        }
        return res;
    }

    VertexIDSet getSubGroups(VertexID const& id) const {
        LOGIC_ASSERTION_CHECK(
            isGroupVertex(id), "Cannot get nested groups from non-group");
        VertexIDSet res;
        for (auto const& sub : groups->getSubVertices(id)) {
            if (isGroupVertex(sub)) { res.incl(sub); }
        }
        return res;
    }

    /// \brief Get all nested groups that don't switch layout
    VertexIDSet getSubGroupsNoLayoutSwitch(VertexID const& id) const {
        VertexIDSet noSwitch;
        for (auto const& sub : getSubGroups(id)) {
            if (!getGroup(sub)->hasAlgorithm()) { noSwitch.incl(sub); }
        }
        return noSwitch;
    }

    VertexIDSet getDirectVertices(VertexID const& id) const {
        return groups->getSubVertices(id);
    }

    EdgeIDSet getDirectlyNestedEdges(VertexID const& id) const {
        LOGIC_ASSERTION_CHECK(
            isGroupVertex(id), "Cannot get nested edges from non-group");
        return edges->getFullyIncludedEdges(getDirectVertices(id));
    }

    /// \brief Return all the edges nested in the target group and its
    /// sub-groups, excluding the edges that are at least partially
    /// crossing the algorithm switch boundary
    EdgeIDSet getLayoutLayerNestedEdges(VertexID const& id) const {
        VertexIDSet noSwitch;
        auto aux = [&](this auto&& self, VertexID const& id) -> void {
            for (auto const& sub : getSubGroupsNoLayoutSwitch(id)) {
                noSwitch.incl(sub);
                self(sub);
            }

            noSwitch.incl(getDirectVertices(id));
        };

        aux(id);

        return edges->getFullyIncludedEdges(noSwitch);
    }

    void addRootGroup(
        VertexID const&                          id,
        hstd::SPtr<IGroupVisualAttribute> const& attr) {
        groups->trackVertex(id);
        graph->getMVertex(id)->addUniqueAttribute(attr);
    }

    EdgeID addNestedGroup(
        VertexID const&                          parent,
        VertexID const&                          nested,
        hstd::SPtr<IGroupVisualAttribute> const& attr) {

        LOGIC_ASSERTION_CHECK(
            !getGraph()
                 ->getVertex(nested)
                 ->getOptionalAttribute<IVertexVisualAttribute>()
                 .has_value(),
            "Cannot assign group visual attribute to a vertex that "
            "already has vertex visual attribute.");

        groups->trackVertex(nested);
        auto res = groups->trackSubVertexRelation(parent, nested);
        graph->getMVertex(nested)->addUniqueAttribute(attr);

        return res;
    }

    EdgeID addNestedVertex(
        VertexID const&                           parent,
        VertexID const&                           nested,
        hstd::SPtr<IVertexVisualAttribute> const& attr) {
        LOGIC_ASSERTION_CHECK(
            isGroupVertex(parent),
            "Cannot assign non-group visual attribute to the vertex "
            "already "
            "annotated with the group visual attribute.");

        LOGIC_ASSERTION_CHECK(
            std::dynamic_pointer_cast<IGroupVisualAttribute>(attr)
                == nullptr,
            "Cannot use group visual attribute in the vertex. Classes "
            "derived from the IVertexVisualAttribute should be managed by "
            "the addNewNativeSubgroup method");

        getGraph()->getMVertex(nested)->addUniqueAttribute(attr);
        groups->trackVertex(nested);
        return groups->trackSubVertexRelation(parent, nested);
    }


    void addEdge(
        EdgeID const&                           id,
        hstd::SPtr<IEdgeVisualAttribute> const& attr) {
        auto edge = getGraph()->getMEdge(id);
        edge->addUniqueAttribute(attr);
        edges->trackEdge(id, graph->getSource(id), graph->getTarget(id));
    }

    hstd::SPtr<IGraph> getGraph() const { return graph; }


    IVertex const* at(VertexID const& id) const {
        return graph->getVertex(id);
    }

    template <typename T = IEdgeLayoutAttribute>
        requires std::derived_from<T, IEdgeLayoutAttribute>
    hstd::SPtr<T> getLayout(EdgeID const& id) const {
        LOGIC_ASSERTION_CHECK_FMT(
            result.edges.contains(id),
            "No layout attribute specified for edge {}",
            graph->getDebugEdgeFormat(id));

        return hstd::validated_dynamic_cast<T>(result.edges.at(id));
    }

    template <typename T = IVertexLayoutAttribute>
        requires std::derived_from<T, IVertexLayoutAttribute>
    hstd::SPtr<T> getLayout(VertexID const& id) const {
        LOGIC_ASSERTION_CHECK_FMT(
            result.vertices.contains(id),
            "No layout attribute specified for vertex ID {}",
            graph->getDebugVertexFormat(id));

        return hstd::validated_dynamic_cast<T>(result.vertices.at(id));
    }

    geometry::Rect getRelativeBBox(VertexID const& id) const {
        return getLayout(id)->getBBox();
    }

    hstd::Vec<visual::VisGroup> getVisual() const;

    visual::VisGroup getVisual(EdgeID const& id) const {
        return getLayout(id)->getVisual(id);
    }

    visual::VisGroup getVisual(VertexID const& id) const {
        return getLayout(id)->getVisual(id);
    }
};


} // namespace layout

} // namespace hstd::ext::graph
