#include <haxorg/sem/ImmOrg.hpp>
#include <hstd/stdlib/Exception.hpp>

#define _define_static(__Kind)                                            \
    const OrgSemKind org::Imm##__Kind::staticKind = OrgSemKind::__Kind;

EACH_SEM_ORG_KIND(_define_static)

#undef _define_static


using namespace org;

struct store_error : CRTP_hexception<store_error> {};

ImmOrg* ParseUnitStore::get(OrgSemKind kind, ImmId::NodeIdxT index) {
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


ImmId ParseUnitStore::add(
    ImmId::StoreIndexT   selfIndex,
    sem::SemId<sem::Org> data,
    ImmId                parent,
    ContextStore*        context) {
    switch (data->getKind()) {

#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: {                                            \
        auto result = store##__Kind.add(                                  \
            selfIndex, data, parent, context);                            \
        return result;                                                    \
    }

        EACH_SEM_ORG_KIND(_case)
#undef _case
    }

    LOG(FATAL)
        << ("Unhandled node kind for automatic creation $#"
            % to_string_vec(data->getKind()));
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


ImmId ContextStore::add(
    ImmId::StoreIndexT   index,
    sem::SemId<sem::Org> data,
    ImmId                parent) {
    return getStoreByIndex(index).add(index, data, parent, this);
}

template <typename Mut>
struct imm_to_sem_map {};

#define _gen_map(__Kind)                                                  \
    template <>                                                           \
    struct imm_to_sem_map<org::Imm##__Kind> {                             \
        using sem_type = sem::__Kind;                                     \
    };
EACH_SEM_ORG_KIND(_gen_map)
#undef _gen_map


template <typename T>
org::ImmId org::KindStore<T>::add(
    ImmId::StoreIndexT   selfIndex,
    sem::SemId<sem::Org> data,
    ImmId                parent,
    ContextStore*        context) {


    using SemType = imm_to_sem_map<T>::sem_type;
    if (!data->is(SemType::staticKind)) {
        throw store_error::init(fmt(
            "Cannot create store value of kind {} from node of kind {}",
            T::staticKind,
            data->getKind()));
    }

    // for_each_field_with_bases<SemType>(data);

    T value;

    ImmId result = ImmId(
        selfIndex,
        T::staticKind,
        static_cast<ImmId::NodeIdxT>(values.size()),
        context);

    values.push_back(value);

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
