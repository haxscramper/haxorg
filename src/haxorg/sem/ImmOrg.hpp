#pragma once

#include <haxorg/sem/ImmOrgBase.hpp>
#include <haxorg/sem/ImmOrgTypes.hpp>
#include <haxorg/sem/SemOrg.hpp>
#include <hstd/stdlib/ColText.hpp>


#define _declare_hash(__kind)                                             \
    template <>                                                           \
    struct std::hash<org::Imm##__kind> {                                  \
        std::size_t operator()(                                           \
            org::Imm##__kind const& it) const noexcept;                   \
    };

EACH_SEM_ORG_KIND(_declare_hash)


namespace org {


template <typename T>
struct KindStore {
    ContextStore* context;
    using NodeType = T;
    dod::InternStore<org::ImmId, T> values;

    int size() const { return values.size(); }

    KindStore(ContextStore* context) : context(context) {}
    void format(ColStream& os, std::string const& linePrefix = "") const;

    bool     empty() const { return values.empty(); }
    T const* at(org::ImmId id) const { return &values.at(id); }
    ImmId    add(
           ImmId::StoreIdxT     selfIndex,
           sem::SemId<sem::Org> data,
           ContextStore*        context);
};

#define __id(I) , org::KindStore<org::Imm##I>*
/// \brief Global variant of all sem node derivations
using OrgKindStorePtrVariant = std::variant<EACH_SEM_ORG_KIND_CSV(__id)>;
#undef __id


struct ParseUnitStore {
    UnorderedMap<org::ImmId, org::ImmId> parents;

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

    void format(ColStream& os, std::string const& prefix = "") const;

    Opt<ImmId> getParent(ImmId id) const { return parents.get(id); }

    Vec<ImmId> getParentChain(ImmId id, bool withSelf = true) const {
        Vec<ImmId> result;
        Opt<ImmId> tmp = id;
        while (tmp) {
            if (withSelf && tmp == id) { result.push_back(tmp.value()); }
            tmp = getParent(tmp.value());
        }
        return result;
    }

    ImmOrg const* at(ImmId index) const;
    ImmId         add(
                ImmId::StoreIdxT     selfIndex,
                sem::SemId<sem::Org> data,
                ContextStore*        context);

    using StoreVisitor = Func<
        void(ImmId::StoreIdxT selfIndex, OrgKindStorePtrVariant store)>;
};

/// \brief Global group of stores that all nodes are written to
struct ContextStore {
    /// \brief Get reference to a local store by index
    ParseUnitStore&       getStoreByIndex(ImmId::StoreIdxT index);
    ParseUnitStore const& getStoreByIndex(ImmId::StoreIdxT index) const;
    ParseUnitStore&       getStoreByIndex(ImmId id) {
        return getStoreByIndex(id.getStoreIndex());
    }

    ParseUnitStore const& getStoreByIndex(ImmId id) const {
        return getStoreByIndex(id.getStoreIndex());
    }

    Vec<ImmId> getParentChain(ImmId id, bool withSelf = true) const {
        return getStoreByIndex(id).getParentChain(id, withSelf);
    }

    void ensureStoreForIndex(ImmId::StoreIdxT index);

    /// \brief Create new sem node of the specified kind in the local store
    /// with `index`
    ImmId add(ImmId::StoreIdxT index, sem::SemId<sem::Org> data);

    ImmOrg const* at(ImmId id) const;

    template <typename T>
    T const* at_t(ImmId id) const {
        return at(id)->template as<T>();
    }

    template <typename T>
    T const* at(ImmIdT<T> id) const {
        return at(id)->template as<T>();
    }

    void format(ColStream& os, std::string const& prefix = "") const;

    Vec<ParseUnitStore> stores;

    ContextStore() {}
    ContextStore(const ContextStore&)            = delete;
    ContextStore& operator=(const ContextStore&) = delete;
};

} // namespace org
