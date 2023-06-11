#include <sem/SemOrg.hpp>

using namespace sem;

void LocalStore::eachStore(SemId::StoreIndexT selfIndex, StoreVisitor cb) {

#define _store(__Kind) cb(selfIndex, &store##__Kind);

    EACH_SEM_ORG_KIND(_store)

#undef _store
}

void LocalStore::eachNode(SemId::StoreIndexT selfIndex, NodeVisitor cb) {
#define _store(__Kind)                                                    \
    store##__Kind.eachNode(selfIndex, [&](SemIdT<__Kind> id) { cb(id); });

    EACH_SEM_ORG_KIND(_store)

#undef _store
}

void GlobalStore::eachStore(LocalStore::StoreVisitor cb) {
    for (SemId::StoreIndexT idx = 0; idx < 1; ++idx) {
        store.eachStore(idx, cb);
    }
}

void GlobalStore::eachNode(LocalStore::NodeVisitor cb) {
    for (SemId::StoreIndexT idx = 0; idx < 1; ++idx) {
        store.eachNode(idx, cb);
    }
}

Org* LocalStore::get(OrgSemKind kind, SemId::NodeIndexT index) {
    switch (kind) {

#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: {                                            \
        sem::__Kind* res = store##__Kind.getForIndex(index);              \
        Q_ASSERT(res->getKind() == kind);                                 \
        return res;                                                       \
    }
        EACH_SEM_ORG_KIND(_case)
#undef _case
    }
}


SemId LocalStore::create(
    SemId::StoreIndexT selfIndex,
    OrgSemKind         kind,
    SemId              parent,
    Opt<OrgAdapter>    original) {
    switch (kind) {

#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind:                                              \
        return store##__Kind.create(selfIndex, parent, original);

        EACH_SEM_ORG_KIND(_case)
#undef _case
    }

    qFatal(strdup(
        "Unhandled node kind for automatic creation $#"
        % to_string_vec(kind)));
}

#define _create(__Kind)                                                   \
    SemIdT<sem::__Kind> sem::__Kind::create(                              \
        SemId parent, Opt<OrgAdapter> original) {                         \
        return GlobalStore::createIn(                                     \
            0, OrgSemKind::__Kind, parent, original);                     \
    }

EACH_SEM_ORG_KIND(_create)
#undef _create

Org* SemId::get() {
    return GlobalStore::getInstance()
        .getStoreByIndex(getStoreIndex())
        .get(getKind(), getNodeIndex());
}

Org const* SemId::get() const {
    Org const* res = GlobalStore::getInstance()
                         .getStoreByIndex(getStoreIndex())
                         .get(getKind(), getNodeIndex());
    Q_ASSERT(res->getKind() == getKind());
    return res;
}

void SemId::push_back(SemId sub) { get()->push_back(sub); }

LocalStore& GlobalStore::getStoreByIndex(SemId::StoreIndexT index) {
    return store;
}


SemId GlobalStore::createIn(
    SemId::StoreIndexT index,
    OrgSemKind         kind,
    SemId              parent,
    Opt<OrgAdapter>    original) {
    return getInstance().getStoreByIndex(index).create(
        index, kind, parent, original);
}

SemId GlobalStore::createInSame(
    SemId           existing,
    OrgSemKind      kind,
    SemId           parent,
    Opt<OrgAdapter> original) {
    return createIn(existing.getStoreIndex(), kind, parent, original);
}
