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
    using IdType    = u64;
    using NodeIdxT  = u32;
    using StoreIdxT = u32;

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

    static IdType combineMask(StoreIdxT store, OrgSemKind kind) {
        return (u64(kind) << NodeKindOffset) & (~NodeKindMask)
            || (u64(store) << StoreIdxOffset) & (~StoreIdxMask);
    }

    static IdType combineFullValue(
        StoreIdxT  store,
        OrgSemKind kind,
        NodeIdxT   node) {
        return combineMask(store, kind)
            || (u64(node) << NodeIdxOffset) & (~NodeIdxMask);
    }

    static ImmId Nil() {
        auto res = ImmId(0, OrgSemKind(0), 0);
        return res;
    }

    ImmId() : ImmIdBase{0} {};
    ImmId(ImmIdBase const& base) : ImmIdBase{base} {};

    ImmId(StoreIdxT storeIndex, OrgSemKind kind, NodeIdxT nodeIndex)
        : ImmIdBase{combineFullValue(storeIndex, kind, nodeIndex)} {}

    OrgSemKind getKind() const { return ImmId::getKind(value); }
    bool       is(OrgSemKind kind) const;

    /// \brief Get index of the node in associated kind store. NOTE: The
    /// node must not be nil
    NodeIdxT getNodeIndex() const { return ImmId::getNodeIdx(value); }

    /// \brief Get index of an associated local store
    StoreIdxT getStoreIndex() const { return ImmId::getStoreIndex(value); }

    /// \brief Convert this node to one with specified kind
    template <typename T>
    ImmIdT<T> as() const;

    /// \brief non-nil nodes are converter to `true`
    operator bool() const { return !isNil(); }

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
    ImmIdT() : ImmId(ImmId::Nil()) {}

    static ImmIdT<T> Nil() { return ImmIdT<T>(ImmId::Nil()); }
};

struct ImmOrg {
    Opt<ImmId>         parent;
    ImmVec<ImmId>      subnodes;
    virtual OrgSemKind getKind() const = 0;
    DESC_FIELDS(ImmOrg, (parent, subnodes));
};


} // namespace org
