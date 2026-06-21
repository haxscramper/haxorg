#include "graph_common.hpp"
#include <hstd/system/bit_utils.hpp>
#include <hstd/stdlib/strutils.hpp>

using namespace hstd::ext::graph;

std::size_t IGraphObjectBase::getHash() const {
    std::size_t res;
    hstd::hax_hash_combine(res, stable_id);
    return res;
}

bool IGraphObjectBase::isEqual(IGraphObjectBase const* other) const {
    return this->stable_id == other->stable_id;
}

std::string IGraphObjectBase::getRepr() const { return stable_id; }

std::string IGraphObjectBase::getStableId() const { return stable_id; }

bool EdgeCollectionID::isHierarchy() const {
    return hstd::masked_equals(t, CollectionTypeMask, IsHierarchyMask);
}

bool EdgeCollectionID::isCollection() const {
    return hstd::masked_equals(t, CollectionTypeMask, IsCollectionMask);
}

EdgeCollectionID EdgeCollectionID::FromHierarchy(u16 base) {
    return EdgeCollectionID(
        hstd::assign_masked(base, CollectionTypeMask, IsHierarchyMask));
}

EdgeCollectionID EdgeCollectionID::FromCollection(u16 base) {
    // first bit must not be set
    return EdgeCollectionID(
        hstd::assign_masked(base, CollectionTypeMask, IsCollectionMask));
}

void EdgeCollectionID::assert_is_collection() const {
    LOGIC_ASSERTION_CHECK_FMT(
        isCollection(),
        "Collection ID has category {} ({}) which matches the "
        "hierarchy mask: {}",
        t,
        hstd::format_integer_bits(t, 'b'),
        hstd::format_integer_bits(IsHierarchyMask, 'b'));
}

void EdgeCollectionID::assert_is_hierarchy() const {
    LOGIC_ASSERTION_CHECK_FMT(
        isHierarchy(),
        "Hierarchy ID has category {} ({}) which matches the "
        "collection mask: {}",
        t,
        hstd::format_integer_bits(t, 'b'),
        hstd::format_integer_bits(IsCollectionMask, 'b'));
}

EdgeID EdgeID::FromMasked(u64 value, EdgeCollectionID mask) {
    return EdgeID(FromMaskedIdx(value, mask.t));
}

EdgeID EdgeID::FromMasked(EdgeID base, EdgeCollectionID mask) {
    return EdgeID(FromMaskedIdx(base.getIndex(), mask.t));
}
