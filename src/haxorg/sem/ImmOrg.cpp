#include <haxorg/sem/ImmOrg.hpp>

using namespace org;

ImmOrg* ParseUnitStore::get(OrgSemKind kind, ImmId::NodeIndexT index) {
    switch (kind) {

#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: {                                            \
        org::Imm##__Kind* res = store##__Kind.getForIndex(index);         \
        CHECK(res->getKind() == kind);                                    \
        return res;                                                       \
    }
        EACH_SEM_ORG_KIND(_case)
#undef _case
    }
}


ImmId ParseUnitStore::create(
    ImmId::StoreIndexT   selfIndex,
    OrgSemKind           kind,
    ImmId                parent,
    ContextStore*        context,
    sem::SemId<sem::Org> data) {
    switch (kind) {

#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: {                                            \
        auto result = store##__Kind.create(                               \
            selfIndex, parent, data, context);                            \
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

// #define _create(__Kind)                                                   \
//     ImmIdT<org::Imm##__Kind> org::Imm##__Kind::create(                    \
//         ImmId parent, sem::SemId<sem::Org> data) {                        \
//         return parent.context->createIn(                                  \
//             parent.getStoreIndex(), OrgSemKind::__Kind, parent, data);    \
//     }

// EACH_SEM_ORG_KIND(_create)
// #undef _create

ImmOrg const* ImmId::get() const {
    ImmOrg const* res = context->getStoreByIndex(getStoreIndex())
                            .get(getKind(), getNodeIndex());
    CHECK(res->getKind() == getKind());
    return res;
}

ParseUnitStore& ContextStore::getStoreByIndex(ImmId::StoreIndexT index) {
    ensureStoreForIndex(index);
    return stores.at(index);
}

void ContextStore::ensureStoreForIndex(ImmId::StoreIndexT index) {
    int diff = index - stores.size();
    CHECK(diff < 120000); // Debugging assertion

    while (!(index < stores.size())) { stores.emplace_back(this); }
}


ImmId ContextStore::createIn(
    ImmId::StoreIndexT   index,
    OrgSemKind           kind,
    ImmId                parent,
    sem::SemId<sem::Org> data) {
    return getStoreByIndex(index).create(index, kind, parent, this, data);
}

ImmId ContextStore::createInSame(
    ImmId                existing,
    OrgSemKind           kind,
    ImmId                parent,
    sem::SemId<sem::Org> data) {
    return createIn(existing.getStoreIndex(), kind, parent, data);
}

template <typename Mut>
struct sem_to_imm_map {};

#define _gen_map(__Kind)                                                  \
    template <>                                                           \
    sem_to_imm_map<sem::__Kind> {                                         \
        using imm_type = org::Imm##__Kind;                                \
    };
EACH_SEM_ORG_KIND(_gen_map)
#undef _gen_map


template <typename T>
org::ImmId org::KindStore<T>::create(
    ImmId::StoreIndexT   selfIndex,
    ImmId                parent,
    sem::SemId<sem::Org> data,
    ContextStore*        context) {
    ImmId result = ImmId(
        selfIndex,
        T::staticKind,
        static_cast<ImmId::NodeIndexT>(values.size()),
        context);

    using ImmType = typename sem_to_imm_map<T>::imm_type;
    ImmType value;
    for_each_field_with_bases<T>();

    if (false) {
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

#define forward_declare(__Kind)                                           \
    template class org::KindStore<org::Imm##__Kind>;
EACH_SEM_ORG_KIND(forward_declare)
#undef forward_declare
