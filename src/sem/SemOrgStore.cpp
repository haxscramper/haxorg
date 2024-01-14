#include <sem/SemOrg.hpp>

using namespace sem;

void ParseUnitStore::eachStore(
    SemId::StoreIndexT selfIndex,
    StoreVisitor       cb) {

#define _store(__Kind) cb(selfIndex, &store##__Kind);

    EACH_SEM_ORG_KIND(_store)

#undef _store
}

void ParseUnitStore::eachNode(
    SemId::StoreIndexT selfIndex,
    NodeVisitor        cb) {
#define _store(__Kind)                                                    \
    store##__Kind.eachNode(selfIndex, [&](SemIdT<__Kind> id) { cb(id); });

    EACH_SEM_ORG_KIND(_store)

#undef _store
}

void ContextStore::eachStore(ParseUnitStore::StoreVisitor cb) {
    for (int i = 0; i < stores.size(); ++i) { stores[i].eachStore(i, cb); }
}

void ContextStore::eachNode(ParseUnitStore::NodeVisitor cb) {
    for (int i = 0; i < stores.size(); ++i) { stores[i].eachNode(i, cb); }
}

Org* ParseUnitStore::get(OrgSemKind kind, SemId::NodeIndexT index) {
    switch (kind) {

#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: {                                            \
        sem::__Kind* res = store##__Kind.getForIndex(index);              \
        CHECK(res->getKind() == kind);                                    \
        return res;                                                       \
    }
        EACH_SEM_ORG_KIND(_case)
#undef _case
    }
}


SemId ParseUnitStore::create(
    SemId::StoreIndexT selfIndex,
    OrgSemKind         kind,
    SemId              parent,
    ContextStore*      context,
    Opt<OrgAdapter>    original) {
    switch (kind) {

#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: {                                            \
        auto result = store##__Kind.create(                               \
            selfIndex, parent, original, context);                        \
        CHECK(result.getKind() == kind)                                   \
            << "create node in local store"                               \
            << fmt1(result.getKind()) + " != " + fmt1(kind);              \
        return result;                                                    \
    }

        EACH_SEM_ORG_KIND(_case)
#undef _case
    }

    LOG(FATAL)
        << ("Unhandled node kind for automatic creation $#"
            % to_string_vec(kind));
}

#define _create(__Kind)                                                   \
    SemIdT<sem::__Kind> sem::__Kind::create(                              \
        SemId parent, Opt<OrgAdapter> original) {                         \
        return parent.context->createIn(                                  \
            parent.getStoreIndex(),                                       \
            OrgSemKind::__Kind,                                           \
            parent,                                                       \
            original);                                                    \
    }

EACH_SEM_ORG_KIND(_create)
#undef _create

Org* SemId::get() {
    CHECK(!isNil());
    CHECK(context != nullptr);
    return context->getStoreByIndex(getStoreIndex())
        .get(getKind(), getNodeIndex());
}

Org const* SemId::get() const {
    Org const* res = context->getStoreByIndex(getStoreIndex())
                         .get(getKind(), getNodeIndex());
    CHECK(res->getKind() == getKind());
    return res;
}

void SemId::push_back(SemId sub) { get()->push_back(sub); }

ParseUnitStore& ContextStore::getStoreByIndex(SemId::StoreIndexT index) {
    ensureStoreForIndex(index);
    return stores.at(index);
}

void ContextStore::ensureStoreForIndex(SemId::StoreIndexT index) {
    int diff = index - stores.size();
    CHECK(diff < 120000); // Debugging assertion

    while (!(index < stores.size())) { stores.emplace_back(this); }
}


SemId ContextStore::createIn(
    SemId::StoreIndexT index,
    OrgSemKind         kind,
    SemId              parent,
    Opt<OrgAdapter>    original) {
    return getStoreByIndex(index).create(
        index, kind, parent, this, original);
}

SemId ContextStore::createInSame(
    SemId           existing,
    OrgSemKind      kind,
    SemId           parent,
    Opt<OrgAdapter> original) {
    return createIn(existing.getStoreIndex(), kind, parent, original);
}

template <typename T>
sem::SemId sem::KindStore<T>::create(
    SemId::StoreIndexT selfIndex,
    SemId              parent,
    Opt<OrgAdapter>    original,
    ContextStore*      context) {
    SemId result = SemId(
        selfIndex,
        T::staticKind,
        static_cast<SemId::NodeIndexT>(values.size()),
        context);

    if (original) {
        values.push_back(T{parent, *original});
    } else {
        values.push_back(T{parent});
    }

    if (false /*T::staticKind == OrgSemKind::HashTag*/) {
        LOG(INFO) << fmt(
            "Push back of values {}, values:{:x}, this:{:x} data:{:x} "
            "size:{} capacity:{}",
            T::staticKind,
            reinterpret_cast<u64>(&values),
            reinterpret_cast<u64>(this),
            reinterpret_cast<u64>(values.data()),
            values.size(),
            values.capacity());
    }


    return result;
}

#define forward_declare(__Kind) template class sem::KindStore<sem::__Kind>;
EACH_SEM_ORG_KIND(forward_declare)
#undef forward_declare
