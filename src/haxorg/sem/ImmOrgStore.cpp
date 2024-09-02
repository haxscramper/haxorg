#include <haxorg/sem/ImmOrg.hpp>
#include <haxorg/sem/ImmOrgHash.hpp>
#include <hstd/stdlib/Enumerate.hpp>
#include <immer/vector_transient.hpp>
#include <immer/set_transient.hpp>
#include <immer/map_transient.hpp>

using namespace org;

struct store_error : CRTP_hexception<store_error> {};

#define _kind(__Kind)                                                     \
    template <>                                                           \
    KindStore<Imm##__Kind>* ParseUnitStore::getStore() {                  \
        return &store##__Kind;                                            \
    }
EACH_SEM_ORG_KIND(_kind)
#undef _kind


ImmId ParseUnitStore::setSubnodes(
    ImmId         target,
    ImmVec<ImmId> subnodes,
    ContextStore* ctx) {
    logic_assertion_check(
        !target.isNil(), "cannot set subnodes to nil node");
    org::ImmId result_node = org::ImmId::Nil();
    switch (target.getKind()) {
#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: {                                            \
        using ImmType   = org::Imm##__Kind;                               \
        ImmType result  = *ctx->at_t<ImmType>(target);                    \
        result.subnodes = subnodes;                                       \
        result_node     = getStore<ImmType>()->add(                       \
            target.getStoreIndex(), result, ctx);                     \
        break;                                                            \
    }
        EACH_SEM_ORG_KIND(_case)
    }

#undef _case

    logic_assertion_check(
        !result_node.isNil(), "added node must not be nil");

    for (auto const& sub : subnodes) {
        if (hasParent(sub)) { setParent(sub, result_node); }
    }

    return result_node;
}


ImmId ParseUnitStore::add(
    ImmId::StoreIdxT     selfIndex,
    sem::SemId<sem::Org> data,
    ContextStore*        context) {
    org::ImmId result = org::ImmId::Nil();

    switch (data->getKind()) {
#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: {                                            \
        result = store##__Kind.add(selfIndex, data, context);             \
        break;                                                            \
    }

        EACH_SEM_ORG_KIND(_case)
#undef _case
    }

    if (result.isNil()) {
        throw logic_unreachable_error::init(
            fmt("Unhandled node kind for automatic creation {}",
                data->getKind()));
    } else {
        for (auto const& sub : at(result)->subnodes) {
            parents.insert({sub, result});
        }
        return result;
    }
}

sem::SemId<sem::Org> ParseUnitStore::get(ImmId id, ContextStore* context) {
    sem::SemId<sem::Org> result;
    switch (id.getKind()) {
#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: {                                            \
        result = store##__Kind.get(id, context);                          \
        break;                                                            \
    }

        EACH_SEM_ORG_KIND(_case)
#undef _case
        default: {
            throw logic_unreachable_error::init(
                fmt("Unhandled node kind for automatic creation {}",
                    id.getKind()));
        }
    }

    return result;
}

const ImmOrg* ContextStore::at(ImmId id) const {
    logic_assertion_check(
        id.getStoreIndex() == 0, "{}", id.getStoreIndex());
    u64 kind     = static_cast<u64>(id.getKind());
    u64 kindLow  = static_cast<u64>(value_domain<OrgSemKind>::low());
    u64 kindHigh = static_cast<u64>(value_domain<OrgSemKind>::high());

    logic_assertion_check(
        kindLow <= kind && kind <= kindHigh,
        "ID kind value out of range: ID int value is: {} (bin: {:032b}, "
        "hex: {:032X}), low {} high {}",
        kind,
        kind,
        kind,
        kindLow,
        kindHigh);

    ImmOrg const* res = getStoreByIndex(id.getStoreIndex()).at(id);
    CHECK(res->getKind() == id.getKind());
    return res;
}

template <org::IsImmOrgValueType T>
void KindStore<T>::format(
    ColStream&                        os,
    const UnorderedMap<ImmId, ImmId>& parents,
    const std::string&                linePrefix) const {
    bool       isFirst = true;
    Vec<ImmId> ids;
    for (auto const& it : values.id_map) { ids.push_back(it.second); }

    rs::sort(ids);

    for (auto const& id : ids) {
        if (!isFirst) { os << "\n"; }
        isFirst = false;
        os << fmt(
            "{}[{}] (parent {}): {}",
            linePrefix,
            id.getReadableId(),
            parents.get(id),
            values.at(id));
    }
}


void ParseUnitStore::format(ColStream& os, const std::string& prefix)
    const {
#define _kind(__Kind)                                                     \
    if (!store##__Kind.empty()) {                                         \
        os << fmt(                                                        \
            "\n{0}[{1:-<16}] {2:016X}\n",                                 \
            prefix,                                                       \
            #__Kind,                                                      \
            u64(OrgSemKind::__Kind));                                     \
        store##__Kind.format(os, parents, prefix + "  ");                 \
    }

    EACH_SEM_ORG_KIND(_kind)
#undef _kind
}

Vec<int> ParseUnitStore::getPath(ImmId id) const {
    Vec<int>   result;
    Opt<ImmId> parent = getParent(id);
    while (parent) {
        int selfIndex = -1;
        int idx       = 0;
        for (auto const& it : at(*parent)->subnodes) {
            if (it == id) {
                selfIndex = idx;
                break;
            }
            ++idx;
        }
        logic_assertion_check(selfIndex != -1, "");
        result.push_back(selfIndex);
        id     = parent.value();
        parent = getParent(id);
    }

    rv::reverse(result);
    return result;
}

Vec<ImmId> ParseUnitStore::getParentChain(ImmId id, bool withSelf) const {
    Vec<ImmId> result;
    Opt<ImmId> tmp = id;
    while (tmp) {
        if (withSelf || tmp != id) { result.push_back(tmp.value()); }
        tmp = getParent(tmp.value());
    }
    return result;
}


void ContextStore::format(ColStream& os, const std::string& prefix) const {
    for (auto const& it : enumerator(stores)) {
        os << fmt("{}ParseUnitStore [{}]\n", prefix, it.index());
        it.value().format(os, prefix + "  ");
    }
}


ParseUnitStore& ContextStore::getStoreByIndex(ImmId::StoreIdxT index) {
    ensureStoreForIndex(index);
    return stores.at(index);
}

ParseUnitStore const& ContextStore::getStoreByIndex(
    ImmId::StoreIdxT index) const {
    return stores.at(index);
}

void ContextStore::ensureStoreForIndex(ImmId::StoreIdxT index) {
    int diff = index - stores.size();
    CHECK(diff < 120000); // Debugging assertion

    while (!(index < stores.size())) { stores.emplace_back(this); }
}


ImmId ContextStore::add(
    ImmId::StoreIdxT     index,
    sem::SemId<sem::Org> data) {
    return getStoreByIndex(index).add(index, data, this);
}


template <typename Mut>
struct imm_to_sem_map {};

template <typename Mut>
struct sem_to_imm_map {};

#define _gen_map(__Kind)                                                  \
    template <>                                                           \
    struct imm_to_sem_map<org::Imm##__Kind> {                             \
        using sem_type = sem::__Kind;                                     \
    };                                                                    \
    template <>                                                           \
    struct sem_to_imm_map<sem::__Kind> {                                  \
        using imm_type = org::Imm##__Kind;                                \
    };
EACH_SEM_ORG_KIND(_gen_map)
#undef _gen_map


struct AddContext {
    ContextStore*    store;
    ImmId::StoreIdxT idx = 0;
};

template <>
struct SerdeDefaultProvider<org::ImmSubtreeLog::Priority> {
    static org::ImmSubtreeLog::Priority get() {
        return org::ImmSubtreeLog::Priority{};
    }
};

template <>
struct SerdeDefaultProvider<org::ImmBlockCode::Switch::LineStart> {
    static org::ImmBlockCode::Switch::LineStart get() {
        return org::ImmBlockCode::Switch::LineStart{};
    }
};

template <>
struct SerdeDefaultProvider<org::ImmBlockCode::Switch> {
    static org::ImmBlockCode::Switch get() {
        return org::ImmBlockCode::Switch{
            org::ImmBlockCode::Switch::LineStart{}};
    }
};

template <typename Sem, typename Imm>
struct ImmSemSerde {};

using SemId_t = sem::SemId<sem::Org>;
using ImmId_t = org::ImmId;

template <>
struct ImmSemSerde<SemId_t, ImmId_t> {
    static ImmId_t to_immer(SemId_t const& id, AddContext const& ctx) {
        return ctx.store->getStoreByIndex(ctx.idx).add(
            ctx.idx, id, ctx.store);
    }

    static SemId_t from_immer(ImmId_t const& id, AddContext const& ctx) {
        return ctx.store->getStoreByIndex(ctx.idx).get(id, ctx.store);
    }
};

template <typename SemType, typename ImmType>
struct ImmSemSerde<sem::SemId<SemType>, org::ImmIdT<ImmType>> {
    static org::ImmIdT<ImmType> to_immer(
        sem::SemId<SemType> const& id,
        AddContext const&          ctx) {
        return ctx.store->getStoreByIndex(ctx.idx)
            .add(ctx.idx, id.asOrg(), ctx.store)
            .template as<ImmType>();
    }

    static sem::SemId<SemType> from_immer(
        org::ImmIdT<ImmType> const& id,
        AddContext const&           ctx) {
        return ctx.store->getStoreByIndex(ctx.idx)
            .get(id, ctx.store)
            .template as<SemType>();
    }
};


template <IsEnum SemType, IsEnum ImmType>
struct ImmSemSerde<SemType, ImmType> {
    static ImmType to_immer(SemType const& value, AddContext const& ctx) {
        return static_cast<ImmType>(value);
    }

    static SemType from_immer(
        ImmType const&    value,
        AddContext const& ctx) {
        return static_cast<SemType>(value);
    }
};


template <IsVariant SemType, IsVariant ImmType>
struct ImmSemSerde<SemType, ImmType> {
    static ImmType to_immer(SemType const& value, AddContext const& ctx) {
        ImmType result = variant_from_index<ImmType>(value.index());
        std::visit(
            [&](auto& out) {
                using ImmVariantItem = std::remove_cvref_t<decltype(out)>;
                // get the incoming variant type the `value.index()`
                using SemVariantItem = std::variant_alternative_t<
                    boost::mp11::mp_find<ImmType, ImmVariantItem>::value,
                    SemType>;

                out = ImmSemSerde<SemVariantItem, ImmVariantItem>::
                    to_immer(std::get<SemVariantItem>(value), ctx);
            },
            result);
        return result;
    }

    static SemType from_immer(
        ImmType const&    value,
        AddContext const& ctx) {
        SemType result = variant_from_index<SemType>(value.index());
        std::visit(
            [&](auto& out) {
                using SemVariantItem = std::remove_cvref_t<decltype(out)>;
                using ImmVariantItem = std::variant_alternative_t<
                    boost::mp11::mp_find<SemType, SemVariantItem>::value,
                    ImmType>;

                out = ImmSemSerde<SemVariantItem, ImmVariantItem>::
                    from_immer(std::get<ImmVariantItem>(value), ctx);
            },
            result);
        return result;
    }
};

template <
    typename SemKey,
    typename SemValue,
    typename ImmKey,
    typename ImmValue>
struct ImmSemSerde<
    UnorderedMap<SemKey, SemValue>,
    ImmMap<ImmKey, ImmValue>> {
    static ImmMap<ImmKey, ImmValue> to_immer(
        UnorderedMap<SemKey, SemValue> const& value,
        AddContext const&                     ctx) {
        ImmMap<ImmKey, ImmValue> result;
        auto                     tmp = result.transient();
        for (auto const& [key, value] : value) {
            tmp.insert({
                ImmSemSerde<SemKey, ImmKey>::to_immer(key, ctx),
                ImmSemSerde<SemValue, ImmValue>::to_immer(value, ctx),
            });
        }
        return tmp.persistent();
    }

    static UnorderedMap<SemKey, SemValue> from_immer(
        ImmMap<ImmKey, ImmValue> const& value,
        AddContext const&               ctx) {
        UnorderedMap<SemKey, SemValue> result;
        for (auto const& [key, value] : value) {
            result.insert({
                ImmSemSerde<SemKey, ImmKey>::from_immer(key, ctx),
                ImmSemSerde<SemValue, ImmValue>::from_immer(value, ctx),
            });
        }
        return result;
    }
};

template <typename SemType, typename ImmType>
struct ImmSemSerde<Opt<SemType>, Opt<ImmType>> {
    static Opt<ImmType> to_immer(
        Opt<SemType> const& value,
        AddContext const&   ctx) {
        Opt<ImmType> base{};
        if (value) {
            base = ImmSemSerde<SemType, ImmType>::to_immer(
                value.value(), ctx);
        }
        return base;
    }

    static Opt<SemType> from_immer(
        Opt<ImmType> const& value,
        AddContext const&   ctx) {
        Opt<SemType> base{};
        if (value) {
            base = ImmSemSerde<SemType, ImmType>::from_immer(
                value.value(), ctx);
        }
        return base;
    }
};

template <typename SemType, typename ImmType>
struct ImmSemSerde<Vec<SemType>, ImmVec<ImmType>> {
    static ImmVec<ImmType> to_immer(
        Vec<SemType> const& value,
        AddContext const&   ctx) {
        ImmVec<ImmType> base{};
        auto            tmp = base.transient();
        for (auto const& sub : value) {
            tmp.push_back(
                ImmSemSerde<SemType, ImmType>::to_immer(sub, ctx));
        }
        return tmp.persistent();
    }

    static Vec<SemType> from_immer(
        ImmVec<ImmType> const& value,
        AddContext const&      ctx) {
        Vec<SemType> tmp{};
        for (auto const& sub : value) {
            tmp.push_back(
                ImmSemSerde<SemType, ImmType>::from_immer(sub, ctx));
        }
        return tmp;
    }
};

#define __same_type(__T)                                                  \
    template <>                                                           \
    struct ImmSemSerde<__T, __T> {                                        \
        static __T to_immer(__T const& value, AddContext const& ctx) {    \
            return value;                                                 \
        }                                                                 \
                                                                          \
        static __T from_immer(__T const& value, AddContext const& ctx) {  \
            return value;                                                 \
        }                                                                 \
    };

__same_type(int);
__same_type(Str);
__same_type(float);
__same_type(bool);
__same_type(std::string);
__same_type(UserTime);

template <typename SemType, typename ImmType>
struct ImmSemSerde<SemType, ImmBox<ImmType>> {
    static ImmBox<ImmType> to_immer(
        SemType const&    value,
        AddContext const& ctx) {
        return ImmSemSerde<SemType, ImmType>::to_immer(value, ctx);
    }

    static SemType from_immer(
        ImmBox<ImmType> const& value,
        AddContext const&      ctx) {
        return ImmSemSerde<SemType, ImmType>::from_immer(value.get(), ctx);
    }
};


template <typename SemType, typename ImmType>
void assign_immer_field(
    ImmType&          field,
    SemType const&    value,
    AddContext const& ctx) {
    field = ImmSemSerde<SemType, ImmType>::to_immer(value, ctx);
}

template <typename SemType, typename ImmType>
void assign_sem_field(
    SemType&          field,
    ImmType const&    value,
    AddContext const& ctx) {
    field = ImmSemSerde<SemType, ImmType>::from_immer(value, ctx);
}


#include "ImmOrgSerde.tcc"

sem::SemId<sem::Org> ContextStore::get(ImmId id) {
    return getStoreByIndex(id.getStoreIndex()).get(id, this);
}

template <org::IsImmOrgValueType ImmType>
ImmId_t org::KindStore<ImmType>::add(
    ImmId::StoreIdxT selfIndex,
    SemId_t          data,
    ContextStore*    context) {


    using SemType = imm_to_sem_map<ImmType>::sem_type;
    if (!data->is(SemType::staticKind)) {
        throw store_error::init(fmt(
            "Cannot create store value of kind {} from node of kind {}",
            ImmType::staticKind,
            data->getKind()));
    }


    ImmType value = ImmSemSerde<SemType, ImmType>::to_immer(
        *data.as<SemType>(),
        AddContext{
            .store = context,
            .idx   = selfIndex,
        });

    CHECK(data->getKind() == ImmType::staticKind);
    return add(selfIndex, value, context);
}

template <org::IsImmOrgValueType T>
ImmId KindStore<T>::add(
    ImmId::StoreIdxT selfIndex,
    const T&         value,
    ContextStore*    context) {
    auto  mask   = ImmId::combineMask(selfIndex, T::staticKind);
    ImmId result = values.add(value, mask);

    CHECK(result.getKind() == value.getKind())
        << fmt(R"(
result.getValue(): {:064b}
result.getKind():  {:064b}
data->getKind():   {:064b}
mask:              {:064b}
)",
               result.getValue(),
               u64(result.getKind()),
               u64(value.getKind()),
               mask);

    return result;
}


template <org::IsImmOrgValueType T>
sem::SemId<sem::Org> KindStore<T>::get(ImmId id, ContextStore* context) {
    if (id.isNil()) {
        return sem::SemId<sem::Org>::Nil();
    } else {
        using SemType = imm_to_sem_map<T>::sem_type;
        auto result   = sem::SemId<SemType>::New();
        *result.value = ImmSemSerde<SemType, T>::from_immer(
            *context->at_t<T>(id),
            AddContext{
                .store = context,
                .idx   = id.getStoreIndex(),
            });

        return result.asOrg();
    }
}


#define forward_declare(__Kind)                                           \
    template class org::KindStore<org::Imm##__Kind>;

EACH_SEM_ORG_KIND(forward_declare)
#undef forward_declare
