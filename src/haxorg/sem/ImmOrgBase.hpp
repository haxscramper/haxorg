#pragma once
#pragma clang diagnostic ignored "-Wunknown-attributes"

#include <hstd/stdlib/dod_base.hpp>
#include <haxorg/sem/SemOrgBase.hpp>
#include <hstd/stdlib/Time.hpp>

#include <immer/vector.hpp>
#include <immer/box.hpp>
#include <immer/map.hpp>

template <typename T>
using ImmVec = immer::vector<T>;

template <typename T>
using ImmBox = immer::box<T>;

template <typename K, typename V>
using ImmMap = immer::map<K, V>;

namespace org {

#define forward_declare(__Kind) struct Imm##__Kind;
EACH_SEM_ORG_KIND(forward_declare)
#undef forward_declare

struct ContextStore;
struct ImmOrg;

template <typename T>
struct ImmIdT;

static const u64 ImmIdMaskSize = 4 * 6;
using ImmIdBase                = dod::
    Id<u64, u64, std::integral_constant<u64, ImmIdMaskSize>>;

struct ImmId : ImmIdBase {
    using IdType          = u64;
    using NodeIdxT        = u32;
    using StoreIdxT       = u32;
    ContextStore* context = nullptr;

    static const u64 NodeIdxMask    = 0x000000FFFFFFFFFF; // >>0*0=0,
    static const u64 NodeIdxOffset  = 0;
    static const u64 NodeKindMask   = 0x000FFF0000000000; // >>10*4=40
    static const u64 NodeKindOffset = 40;
    static const u64 StoreIdxMask   = 0xFFF0000000000000; // >>13*4=52
    static const u64 StoreIdxOffset = 52;

    // clang-format off
    static StoreIdxT  getStoreIndex(IdType id) { return StoreIdxT((id & StoreIdxMask) >> StoreIdxOffset); }
    static NodeIdxT   getNodeIdx(IdType id)    { return NodeIdxT((id & NodeIdxMask) >> NodeIdxOffset); }
    static OrgSemKind getKind(IdType id)       { return OrgSemKind((id & NodeKindMask) >> NodeKindOffset); }
    // clang-format on

    static IdType combineIdxValue(
        StoreIdxT  store,
        OrgSemKind kind,
        NodeIdxT   node) {
        return (u64(kind) << NodeKindOffset) & (~NodeKindMask)
            || (u64(store) << StoreIdxOffset) & (~StoreIdxMask)
            || (u64(node) << NodeIdxOffset) & (~NodeIdxMask);
    }

    static ImmId Nil() {
        auto res = ImmId(0, OrgSemKind(0), 0, nullptr);
        return res;
    }

    ImmId(
        StoreIdxT     storeIndex,
        OrgSemKind    kind,
        NodeIdxT      nodeIndex,
        ContextStore* _store)
        : ImmIdBase{combineIdxValue(storeIndex, kind, nodeIndex)}
        , context(_store) {}

    OrgSemKind getKind() const { return ImmId::getKind(value); }
    bool       is(OrgSemKind kind) const;

    /// \brief Get index of the node in associated kind store. NOTE: The
    /// node must not be nil
    NodeIdxT getNodeIndex() const { return ImmId::getNodeIdx(value); }

    /// \brief Get index of an associated local store
    StoreIdxT getStoreIndex() const { return ImmId::getStoreIndex(value); }

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
    ImmOrg const* get() const;
    ImmOrg const* operator->() const { return get(); }

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
    void push_back(ImmId sub);

    /// \brief Convert this node to one with specified kind
    template <typename T>
    ImmIdT<T> as() const;

    /// \brief Get parent node ID for the node pointed to by this ID
    ImmId      getParent() const;
    Vec<ImmId> getParentChain(bool withSelf = false) const;

    /// \brief non-nil nodes are converter to `true`
    operator bool() const { return !isNil(); }


    using SubnodeVisitor = Func<void(ImmId)>;
    /// \brief Recursively visit each subnode in the tree and apply the
    /// provided callback
    void eachSubnodeRec(SubnodeVisitor cb);

    std::string getReadableId() const {
        if (isNil()) {
            return "nil";
        } else {
            return std::format(
                "{}_{}_{}", getStoreIndex(), getKind(), getNodeIndex());
        }
    }
};

template <typename T>
struct ImmIdT : public ImmId {
    ImmId toId() const { return *this; }
    ImmIdT(ImmId base) : ImmId(base) {}

    T*       operator->() { return get(); }
    T const* operator->() const { return get(); }
    T*       get() { return static_cast<T*>(ImmId::get()); }
    T const* get() const { return static_cast<T const*>(ImmId::get()); }
    static ImmIdT<T> Nil() { return ImmIdT<T>(ImmId::Nil()); }
};

struct ImmOrg {
    Opt<ImmId>         parent;
    ImmVec<ImmId>      nested;
    virtual OrgSemKind getKind() const = 0;
};


} // namespace org
