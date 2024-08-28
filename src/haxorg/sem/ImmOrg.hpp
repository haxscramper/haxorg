#pragma once

#include <haxorg/sem/ImmOrgBase.hpp>
#include <haxorg/sem/ImmOrgTypes.hpp>
#include <haxorg/sem/SemOrg.hpp>


#define _declare_hash(__kind)                                             \
    template <>                                                           \
    struct std::hash<org::Imm##__kind> {                                  \
        std::size_t operator()(                                           \
            org::Imm##__kind const& it) const noexcept;                   \
    };

EACH_SEM_ORG_KIND(_declare_hash)
#undef _declare_hash

#define _declare_hash(__parent, __qual, _)                                \
    template <>                                                           \
    struct std::hash<org::Imm##__parent::__qual> {                        \
        std::size_t operator()(                                           \
            org::Imm##__parent::__qual const& it) const noexcept;         \
    };

EACH_SEM_ORG_RECORD_NESTED(_declare_hash)
#undef _declare_hash

namespace org {


template <typename T>
struct KindStore {
    ContextStore* context;
    using NodeType = T;
    dod::InternStore<org::ImmId, T> values;

    int size() const { return values.size(); }

    KindStore(ContextStore* context) : context(context) {}

    T const* at(org::ImmId id) const { return &values.at(id); }
    ImmId    add(
           ImmId::StoreIdxT     selfIndex,
           sem::SemId<sem::Org> data,
           ImmId                parent,
           ContextStore*        context);
};

#define __id(I) , org::KindStore<org::Imm##I>*
/// \brief Global variant of all sem node derivations
using OrgKindStorePtrVariant = std::variant<EACH_SEM_ORG_KIND_CSV(__id)>;
#undef __id


struct ParseUnitStore {
#define _kind(__Kind) KindStore<Imm##__Kind> store##__Kind;
    EACH_SEM_ORG_KIND(_kind)
#undef _kind


    ParseUnitStore(ContextStore* context)
        :
#define _kind(__Kind) , store##__Kind(context)
        EACH_SEM_ORG_KIND_CSV(_kind)
#undef _kind
    {
    }

    ImmOrg const* at(ImmId index) const;
    ImmId         add(
                ImmId::StoreIdxT     selfIndex,
                sem::SemId<sem::Org> data,
                ImmId                parent,
                ContextStore*        context);

    using StoreVisitor = Func<
        void(ImmId::StoreIdxT selfIndex, OrgKindStorePtrVariant store)>;
};

/// \brief Global group of stores that all nodes are written to
struct ContextStore {
    /// \brief Get reference to a local store by index
    ParseUnitStore&       getStoreByIndex(ImmId::StoreIdxT index);
    ParseUnitStore const& getStoreByIndex(ImmId::StoreIdxT index) const;
    void                  ensureStoreForIndex(ImmId::StoreIdxT index);

    /// \brief Create new sem node of the specified kind in the local store
    /// with `index`
    ImmId add(
        ImmId::StoreIdxT     index,
        sem::SemId<sem::Org> data,
        ImmId                parent);

    ImmOrg const* at(ImmId id) const;

    Vec<ParseUnitStore> stores;

    ContextStore() {}
    ContextStore(const ContextStore&)            = delete;
    ContextStore& operator=(const ContextStore&) = delete;
};

} // namespace org
