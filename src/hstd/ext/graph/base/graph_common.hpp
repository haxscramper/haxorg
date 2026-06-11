#pragma once

#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Map.hpp>
#include <hstd/ext/bimap_wrap.hpp>
#include <hstd/ext/geometry/hstd_geometry.hpp>
#include <boost/serialization/strong_typedef.hpp>
#include <hstd/stdlib/dod_base.hpp>
#include <hstd/stdlib/JsonSerde.hpp>
#include <hstd/stdlib/Set.hpp>
#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/stdlib/OptFormatter.hpp>
#include <hstd/ext/geometry/hstd_visual.hpp>
#include <boost/bimap.hpp>
#include "hstd/stdlib/TraceBase.hpp"
#if ORG_BUILD_WITH_PROTOBUF
#    include "src/hstd/ext/graph/base/graph_base.pb.h"
#endif

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
            hstd::fmt1_maybe(result));

        insert_or_assign(result, value);
    }
};
} // namespace hstd

namespace hstd::ext::graph {


using namespace hstd::ext::geometry;
/// \name Collection ID groups
/// @{


/// \brief 16-bit ID to track edge collection. Used as a mask in the
/// `EdgeID`.
///
/// Collection ID is created by the IEdgeCollection::getCollectionId
BOOST_STRONG_TYPEDEF(hstd::u16, EdgeCollectionIDBase);

struct EdgeCollectionID : public EdgeCollectionIDBase {
    /// hierarchy ID if <ID> & HierarchyCategoryMaskBit != 0
    static constexpr hstd::u16 CollectionTypeMask = 0b1000'0000'0000'0000;
    static constexpr hstd::u16 IsHierarchyMask    = 0b1000'0000'0000'0000;
    static constexpr hstd::u16 IsCollectionMask   = 0b0000'0000'0000'0000;

    using EdgeCollectionIDBase::EdgeCollectionIDBase;
    bool isHierarchy() const {
        return hstd::masked_equals(t, CollectionTypeMask, IsHierarchyMask);
    }
    bool isCollection() const {
        return hstd::masked_equals(
            t, CollectionTypeMask, IsCollectionMask);
    }

    static EdgeCollectionID FromHierarchy(hstd::u16 base) {
        return EdgeCollectionID(
            hstd::assign_masked(
                base, CollectionTypeMask, IsHierarchyMask));
    }

    static EdgeCollectionID FromCollection(hstd::u16 base) {
        // first bit must not be set
        return EdgeCollectionID(
            hstd::assign_masked(
                base, CollectionTypeMask, IsCollectionMask));
    }

    void assert_is_collection() const {
        LOGIC_ASSERTION_CHECK_FMT(
            isCollection(),
            "Collection ID has category {} ({}) which matches the "
            "hierarchy mask: {}",
            t,
            hstd::format_integer_bits(t, 'b'),
            hstd::format_integer_bits(IsHierarchyMask, 'b'));
    }

    void assert_is_hierarchy() const {
        LOGIC_ASSERTION_CHECK_FMT(
            isHierarchy(),
            "Hierarchy ID has category {} ({}) which matches the "
            "collection mask: {}",
            t,
            hstd::format_integer_bits(t, 'b'),
            hstd::format_integer_bits(IsCollectionMask, 'b'));
    }

    /// \brief Default implementation of the hierarchy ID constructoir.
    ///
    /// It creates an ID based on the type, which is sufficient if there is
    /// only one instance of the hierarchy type in a graph.
    template <typename T>
    static EdgeCollectionID FromHierarchyTypePointer(T const* self) {
        return FromHierarchy(
            hstd::hash_bits<15>(typeid(self).hash_code()));
    }

    /// \brief Default implementation of the collection ID constructoir.
    template <typename T>
    static EdgeCollectionID FromCollectionTypePointer(T const* self) {
        return FromCollection(
            hstd::hash_bits<15>(typeid(self).hash_code()));
    }
};

/// \brief 16-bit ID to identify the attribute tracker.
BOOST_STRONG_TYPEDEF(hstd::u16, AttributeTrackerID);
BOOST_STRONG_TYPEDEF(hstd::u16, PortCollectionID);


/// @}


struct graph_error : public hstd::CRTP_hexception<graph_error> {};

struct serde_error
    : public hstd::CRTP_hexception<serde_error, graph_error> {};

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

/// \brief Base class for all graph entries: edges, vertices, groups.
/// Container classes (vertex hierarchies, edge collections) are not graph
/// objects.
class IGraphObjectBase {
    std::string stable_id;

  public:
    virtual std::size_t getHash() const;
    virtual bool        isEqual(IGraphObjectBase const* other) const;
    virtual std::string getRepr() const;
    virtual std::string getStableId() const;

    IGraphObjectBase(std::string const& _stable_id)
        : stable_id{_stable_id} {}

    virtual ~IGraphObjectBase() = default;

    template <typename T>
    bool isInstance() const {
        return dynamic_cast<T const*>(this) != nullptr;
    }
};

template <typename T>
concept IsGraphObject = std::derived_from<T, IGraphObjectBase>;

DECL_ID_TYPE_MASKED(IVertex, VertexID, hstd::u64, 16);
DECL_ID_TYPE_MASKED(IEdge, EdgeIDBase, hstd::u64, 16);

struct EdgeID : public EdgeIDBase {
    using EdgeIDBase::EdgeIDBase;

    EdgeID(EdgeIDBase base) : EdgeIDBase{base} {}

    bool isHierarchyEdge() const {
        return EdgeCollectionID(getMask()).isHierarchy();
    }

    bool isCollectionEdge() const {
        return EdgeCollectionID(getMask()).isCollection();
    }

    static EdgeID FromMasked(hstd::u64 value, EdgeCollectionID mask) {
        return EdgeID(FromMaskedIdx(value, mask.t));
    }

    static EdgeID FromMasked(EdgeID base, EdgeCollectionID mask) {
        return EdgeID(FromMaskedIdx(base.getIndex(), mask.t));
    }


    DESC_FIELDS(EdgeID, ());
};

static_assert(dod::IsIdType<EdgeID>);

/// \brief Categorize the in/out edge connections between vertices.
///
/// The concept of the node port is linked with the layout, but the the
/// abstract graph interface it is also used to group different connections
/// of edge to the vertices.
DECL_ID_TYPE_MASKED(IPort, PortID, hstd::u64, 16);

using VertexIDSet = hstd::UnorderedSet<VertexID>;
using EdgeIDSet   = hstd::UnorderedSet<EdgeID>;
using PortIDSet   = hstd::UnorderedSet<PortID>;
using VertexIDVec = hstd::Vec<VertexID>;
using EdgeIDVec   = hstd::Vec<EdgeID>;
using PortIDVec   = hstd::Vec<PortID>;

class IGraph;
class IVertexHierarchy;
class IEdgeCollection;
class IPortCollection;
class IAttribute;
class IVertex;
class IAttributeObject;

namespace layout {
class IConstraint;
}

#if ORG_BUILD_WITH_PROTOBUF
class IGraphSerialReaderFactory : public hstd::OperationsTracer {
  public:
    virtual hstd::SPtr<IVertexHierarchy> newVertexHierarchy(
        proto::IVertexHierarchy const* in) = 0;
    virtual hstd::SPtr<IEdgeCollection> newEdgeCollection(
        proto::IEdgeCollection const* in) = 0;
    virtual hstd::SPtr<IPortCollection> newPortCollection(
        proto::IPortCollection const* in) = 0;
    virtual hstd::SPtr<IAttribute> newAttribute(
        proto::IAttribute const* in,
        IGraph const*            graph,
        IAttributeObject const*  vertex) = 0;

    virtual hstd::SPtr<IVertex> newVertex(proto::IVertex const* in) = 0;
    virtual hstd::SPtr<IEdge>   newEdge(proto::IEdge const* edge)   = 0;
    virtual hstd::SPtr<IPort>   newPort(proto::IPort const* port)   = 0;
    virtual hstd::SPtr<layout::IConstraint> newConstraint(
        proto::IConstraint const* constraint) = 0;
};
#endif

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


template <hstd::ext::graph::IsGraphObject T>
struct std::hash<T> {
    std::size_t operator()(T const& it) const noexcept {
        return it.getHash();
    }
};
