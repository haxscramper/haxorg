#pragma once

#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Time.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Func.hpp>
#include <parse/OrgTypes.hpp>

#include <boost/describe.hpp>
#include <hstd/system/macros.hpp>
#include <functional>

#include <QDateTime>

#include <sem/SemOrgBase.hpp>

//#include <sem/SemOrgTypes_old.hpp>
#include <sem/SemOrgTypes.hpp>


namespace sem {

template <typename T>
struct KindStore {
    using NodeType = T;
    Vec<T> values;

    int size() const { return values.size(); }


    T* getForIndex(SemId::NodeIndexT index) {
        Q_ASSERT(0 <= index && index < values.size());
        return &values.at(index);
    }

    SemId create(
        SemId::StoreIndexT selfIndex,
        SemId              parent,
        Opt<OrgAdapter>    original) {
        SemId result = SemId(
            selfIndex,
            T::staticKind,
            static_cast<SemId::NodeIndexT>(values.size()));
        if (original) {
            values.emplace_back(parent, *original);
        } else {
            values.emplace_back(parent);
        }
        return result;
    }

    using StoreVisitor = Func<
        void(SemId::StoreIndexT selfIndex, KindStore<T>* store)>;

    using NodeVisitor = Func<void(SemIdT<T> node)>;

    generator<SemIdT<T>> nodes(SemId::StoreIndexT selfIndex) {
        for (SemId::NodeIndexT node = 0; node < values.size(); ++node) {
            co_yield SemIdT<T>(SemId(selfIndex, T::staticKind, node));
        }
    }

    void eachNode(SemId::StoreIndexT selfIndex, CR<NodeVisitor> cb) {
        for (const auto& id : nodes(selfIndex)) {
            cb(id);
        }
    }
};

#define __id(I) , sem::KindStore<sem::I>*
/// \brief Global variant of all sem node derivations
using OrgKindStorePtrVariant = std::variant<EACH_SEM_ORG_KIND_CSV(__id)>;
#undef __id


struct LocalStore {
#define _kind(__Kind) KindStore<__Kind> store##__Kind;
    EACH_SEM_ORG_KIND(_kind)
#undef _kind

    Org*  get(OrgSemKind kind, SemId::NodeIndexT index);
    SemId create(
        SemId::StoreIndexT selfIndex,
        OrgSemKind         kind,
        SemId              parent,
        Opt<OrgAdapter>    original = std::nullopt);

    using StoreVisitor = Func<
        void(SemId::StoreIndexT selfIndex, OrgKindStorePtrVariant store)>;

    using NodeVisitor = Func<void(OrgVariant node)>;

    void eachStore(SemId::StoreIndexT selfIndex, StoreVisitor cb);
    void eachNode(SemId::StoreIndexT selfIndex, NodeVisitor cb);
};

/// \brief Global group of stores that all nodes are written to
struct GlobalStore {
    static GlobalStore& getInstance();

    /// \brief Get reference to a local store by index
    LocalStore& getStoreByIndex(SemId::StoreIndexT index);

    /// \brief Create new sem node of the specified kind in the local store
    /// with `index`
    static SemId createIn(
        SemId::StoreIndexT index,
        OrgSemKind         kind,
        SemId              parent,
        Opt<OrgAdapter>    original = std::nullopt);


    /// \brief Create new sem node of the specified kind in the same local
    /// store as the `existing` node
    static SemId createInSame(
        SemId           existing,
        OrgSemKind      kind,
        SemId           parent,
        Opt<OrgAdapter> original = std::nullopt);


    LocalStore store;


    void eachStore(LocalStore::StoreVisitor cb);
    void eachNode(LocalStore::NodeVisitor cb);

    GlobalStore() {}
    GlobalStore(const GlobalStore&)            = delete;
    GlobalStore& operator=(const GlobalStore&) = delete;
};

template <typename T>
concept NotOrg = !(
    std::derived_from<typename remove_smart_pointer<T>::type, sem::Org>
    || std::derived_from<T, SemId>);

/// \brief  Compile-time check whether the element is an org-mode node or
/// an org-mode ID
template <typename T>
concept IsOrg = std::derived_from<
                    typename remove_smart_pointer<T>::type,
                    sem::Org>
             || std::derived_from<T, SemId>;
}; // namespace sem

template <>
struct std::hash<sem::SemId> {
    std::size_t operator()(sem::SemId const& s) const noexcept {
        return qHash(s.id);
    }
};

#undef DECL_KIND
#undef DECL_FIELDS
