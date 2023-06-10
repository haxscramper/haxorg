#include <sem/SemOrg.hpp>

using namespace sem;

Org& LocalStore::get(OrgSemKind kind, int index) {
    switch (kind) {

#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: return store##__Kind.getForIndex(index);
        EACH_SEM_ORG_KIND(_case)
#undef _case
    }
}


SemId LocalStore::create(
    int             selfIndex,
    OrgSemKind      kind,
    SemId           parent,
    Opt<OrgAdapter> original) {
    switch (kind) {

#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind:                                              \
        return store##__Kind.create(selfIndex, parent, original);

        EACH_SEM_ORG_KIND(_case)
#undef _case
    }
}

#define _create(__Kind)                                                   \
    SemIdT<sem::__Kind> sem::__Kind::create(                              \
        SemId parent, Opt<OrgAdapter> original) {                         \
        return GlobalStore::createIn(                                     \
            0, OrgSemKind::__Kind, parent, original);                     \
    }

EACH_SEM_ORG_KIND(_create)
#undef _create

Org& SemId::get() {
    return GlobalStore::getInstance()
        .getStoreByIndex(getStoreIndex())
        .get(getKind(), getNodeIndex());
}

Org const& SemId::get() const {
    return GlobalStore::getInstance()
        .getStoreByIndex(getStoreIndex())
        .get(getKind(), getNodeIndex());
}

LocalStore& GlobalStore::getStoreByIndex(int index) {
    if (stores.size() <= index) {
        stores.resize(index + 1);
    }

    return stores.at(index);
}


SemId GlobalStore::createIn(
    int             index,
    OrgSemKind      kind,
    SemId           parent,
    Opt<OrgAdapter> original) {
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
