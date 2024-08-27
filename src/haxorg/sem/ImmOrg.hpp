#pragma once

#include <haxorg/sem/ImmOrgBase.hpp>
#include <haxorg/sem/ImmOrgTypes.hpp>
#include <haxorg/sem/SemOrg.hpp>

namespace org {


template <typename T>
struct KindStore {
    ContextStore* context;
    using NodeType = T;
    Vec<T> values;

    int size() const { return values.size(); }

    KindStore(ContextStore* context) : context(context) {}

    T* getForIndex(ImmId::NodeIndexT index) {
        CHECK(0 <= index && index < values.size());
        return &values.at(index);
    }

    ImmId create(
        ImmId::StoreIndexT   selfIndex,
        ImmId                parent,
        sem::SemId<sem::Org> data,
        ContextStore*        context);

    using StoreVisitor = Func<
        void(ImmId::StoreIndexT selfIndex, KindStore<T>* store)>;

    using NodeVisitor = Func<void(ImmIdT<T> node)>;

    generator<ImmIdT<T>> nodes(ImmId::StoreIndexT selfIndex) {
        for (ImmId::NodeIndexT node = 0; node < values.size(); ++node) {
            co_yield ImmIdT<T>(
                ImmId(selfIndex, T::staticKind, node, context));
        }
    }

    void eachNode(ImmId::StoreIndexT selfIndex, CR<NodeVisitor> cb) {
        for (const auto& id : nodes(selfIndex)) { cb(id); }
    }
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

    ImmOrg* get(OrgSemKind kind, ImmId::NodeIndexT index);
    ImmId   create(
          ImmId::StoreIndexT   selfIndex,
          OrgSemKind           kind,
          ImmId                parent,
          ContextStore*        context,
          sem::SemId<sem::Org> data);

    using StoreVisitor = Func<
        void(ImmId::StoreIndexT selfIndex, OrgKindStorePtrVariant store)>;
};

/// \brief Global group of stores that all nodes are written to
struct ContextStore {
    /// \brief Get reference to a local store by index
    ParseUnitStore& getStoreByIndex(ImmId::StoreIndexT index);
    void            ensureStoreForIndex(ImmId::StoreIndexT index);

    /// \brief Create new sem node of the specified kind in the local store
    /// with `index`
    ImmId createIn(
        ImmId::StoreIndexT   index,
        OrgSemKind           kind,
        ImmId                parent,
        sem::SemId<sem::Org> data);


    /// \brief Create new sem node of the specified kind in the same local
    /// store as the `existing` node
    ImmId createInSame(
        ImmId                existing,
        OrgSemKind           kind,
        ImmId                parent,
        sem::SemId<sem::Org> data);


    Vec<ParseUnitStore> stores;

    ContextStore() {}
    ContextStore(const ContextStore&)            = delete;
    ContextStore& operator=(const ContextStore&) = delete;
};

} // namespace org
