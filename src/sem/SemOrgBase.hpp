#pragma once

#include <hstd/system/basic_typedefs.hpp>
#include <sem/SemOrgEnums.hpp>

namespace sem {

struct Org;

template <typename T>
struct SemIdT;

struct SemId {
    using IdType      = u64;
    using NodeIndexT  = u32;
    using StoreIndexT = u32;

    IdType id = 0;
    bool   isNil() const { return id == 0; }

    bool operator==(SemId const& other) const { return id == other.id; }

    static SemId Nil() {
        auto res = SemId(0, OrgSemKind(0), 0);
        res.id   = 0;
        return res;
    }

    SemId(StoreIndexT storeIndex, OrgSemKind kind, NodeIndexT nodeIndex) {
        setStoreIndex(storeIndex);
        setKind(kind);
        setNodeIndex(nodeIndex);
    }

    OrgSemKind getKind() const { return OrgSemKind((id >> 32) & 0xFF); }
    bool       is(OrgSemKind kind) const;

    /// \brief Get index of the node in associated kind store. NOTE: The
    /// node must not be nil
    NodeIndexT getNodeIndex() const {
        assert(!isNil());
        return (id & 0xFFFFFFFF) - 1;
    }

    /// \brief Get index of an associated local store
    StoreIndexT getStoreIndex() const { return id >> 40; }

    /// \brief Set store index for ID.
    ///
    /// Should only be used if two stores are to be merged and nested IDs
    /// updated, in other cases store is considered fixed.
    void setStoreIndex(StoreIndexT storeIndex) {
        id = (id & 0x000000FFFFFFFFFF) | ((IdType)storeIndex << 40);
    }

    void setKind(OrgSemKind kind) {
        id = (id & 0xFFFFFF00FFFFFFFF) | ((IdType)kind << 32);
    }

    void setNodeIndex(NodeIndexT nodeIndex) {
        id = (id & 0xFFFFFFFF00000000) | (nodeIndex + 1);
    }

    /// \name Get pointer to the associated sem org node from ID
    ///
    /// \warning Resulting pointers are *not* stable -- underlying store
    /// content is subject to relocation and as such pointers are bound to
    /// be invalidated if the new nodes are added. The pattern of `ptr =
    /// node.get() ... add nodes ... ptr->something` will lead to subtle
    /// bugs with dangling pointers and should be avoided. Instead
    /// `node->whatever ... add nodes ... node->whatever` must be used. For
    /// the same reason storing pointers in containers is discouraged.
    ///
    /// {@
    Org*       get();
    Org const* get() const;
    Org*       operator->() { return get(); }
    Org const* operator->() const { return get(); }

    template <typename T>
    T* getAs() {
        return dynamic_cast<T*>(get());
    }

    template <typename T>
    T const* getAs() const {
        return dynamic_cast<T const*>(get());
    }
    /// @}

    /// \brief Add new subnode
    ///
    /// \note This method *must* be used instead of the
    /// `id->push_back(convert())` and similar because otherwise it might
    /// cause dangling pointers due to the following sequence: (1) `->` is
    /// evaluated, (2) `convert()` is evaluated, (3) `push_back` is called
    /// on the pointer created earlier, which might be invalidated due to
    /// relocation in p2
    void push_back(SemId sub);

    /// \brief Convert this node to one with specified kind
    template <typename T>
    SemIdT<T> as() const;

    /// \brief Convert the node to corresponding variant type.
    ///
    /// Intented to be used with custom `std::visit` solutions instead of
    /// relying on the more heavyweight CRTP visitator.
    OrgVariant asVariant();


    /// \brief Get parent node ID for the node pointed to by this ID
    SemId      getParent() const;
    Vec<SemId> getParentChain(bool withSelf = false) const;

    /// \brief non-nil nodes are converter to `true`
    operator bool() const { return !isNil(); }


    using SubnodeVisitor = Func<void(SemId)>;
    /// \brief Recursively visit each subnode in the tree and apply the
    /// provided callback
    void eachSubnodeRec(SubnodeVisitor cb);
};


/// \brief Print `store:kind:index` triple
QTextStream& operator<<(QTextStream& os, SemId const& value);

/// \brief Derived node for more explicit APIs
///
/// This node is supposed to be used as a mechanism for CRTP overloading
/// (each node has its own ID) and for providing more explicit interfaces.
/// Otherwise it is a thin wrapper on top of the baseline sem ID
/// functionality.
template <typename T>
struct SemIdT : public SemId {
    SemId toId() const { return *this; }
    SemIdT(SemId base) : SemId(base) {}

    T*       operator->() { return get(); }
    T const* operator->() const { return get(); }
    T*       get() { return static_cast<T*>(SemId::get()); }
    T const* get() const { return static_cast<T const*>(SemId::get()); }
    static SemIdT<T> Nil() { return SemIdT<T>(SemId::Nil()); }
};


}; // namespace sem
