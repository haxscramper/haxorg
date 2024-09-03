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
    ImmAstKindStore<Imm##__Kind>* ImmAstStore::getStore() {               \
        return &store##__Kind;                                            \
    }
EACH_SEM_ORG_KIND(_kind)
#undef _kind


ImmId ImmAstStore::setSubnodes(
    ImmId              target,
    ImmVec<ImmId>      subnodes,
    ImmAstEditContext& ctx) {
    logic_assertion_check(
        !target.isNil(), "cannot set subnodes to nil node");
    org::ImmId result_node = org::ImmId::Nil();
    switch (target.getKind()) {
#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: {                                            \
        using ImmType   = org::Imm##__Kind;                               \
        ImmType result  = ctx.ctx->value<ImmType>(target);                \
        result.subnodes = subnodes;                                       \
        result_node     = getStore<ImmType>()->add(result, ctx);          \
        break;                                                            \
    }
        EACH_SEM_ORG_KIND(_case)
    }

#undef _case

    logic_assertion_check(
        !result_node.isNil(), "added node must not be nil");

    for (auto const& sub : subnodes) {
        ctx.parents.setParent(sub, result_node);
    }

    return result_node;
}

ImmAstReplaceEpoch ImmAstStore::setSubnode(
    ImmId              target,
    ImmId              newSubnode,
    int                position,
    ImmAstEditContext& ctx) {
    ImmId replaced = setSubnodes(
        target,
        ctx.ctx->at(target)->subnodes.set(position, newSubnode),
        ctx);
    return cascadeUpdate(
        {ImmAstReplace{
            .original = target,
            .replaced = replaced,
        }},
        ctx);
}

ImmAstReplaceEpoch ImmAstStore::cascadeUpdate(
    const Vec<ImmAstReplace>& replace,
    ImmAstEditContext&        ctx) {
    Vec<ImmAstReplaceCascade> result;
    for (auto const& act : replace) {
        auto original       = act.original;
        auto originalParent = ctx.ctx->getParent(original);
        auto replaced       = act.replaced;

        ImmAstReplaceCascade cascade{.chain = {act}};
        while (originalParent) {
            ImmId replacedParent = setSubnodes(
                *originalParent,
                ctx.ctx->at(*originalParent)
                    ->subnodes.set(
                        ctx.ctx->at(*originalParent)->indexOf(original),
                        replaced),
                ctx);

            cascade.chain.push_back(ImmAstReplace{
                .original = *originalParent,
                .replaced = replacedParent,
            });

            ctx.parents.removeParent(original);

            replaced       = replacedParent;
            original       = *originalParent;
            originalParent = ctx.ctx->getParent(original);
        }

        result.push_back(cascade);
    }

    return {result};
}


ImmId ImmAstStore::add(sem::SemId<sem::Org> data, ImmAstEditContext& ctx) {
    org::ImmId result = org::ImmId::Nil();

    switch (data->getKind()) {
#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: {                                            \
        result = store##__Kind.add(data, ctx);                            \
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
            ctx.parents.setParent(sub, result);
        }
        return result;
    }
}

sem::SemId<sem::Org> ImmAstStore::get(ImmId id, const ImmAstContext& ctx) {
    sem::SemId<sem::Org> result;
    switch (id.getKind()) {
#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: {                                            \
        result = store##__Kind.get(id, ctx);                              \
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

const ImmOrg* ImmAstContext::at(ImmId id) const {
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

    ImmOrg const* res = store->at(id);
    CHECK(res->getKind() == id.getKind());
    return res;
}

template <org::IsImmOrgValueType T>
void ImmAstKindStore<T>::format(
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


void ImmAstStore::format(ColStream& os, const std::string& prefix) const {
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

Vec<int> ImmAstParentMap::getPath(ImmId id, const ImmAstContext& ctx)
    const {
    Vec<int>   result;
    Opt<ImmId> parent = getParent(id);
    while (parent) {
        int selfIndex = -1;
        int idx       = 0;
        for (auto const& it : ctx.at(*parent)->subnodes) {
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

Vec<ImmId> ImmAstParentMap::getParentChain(ImmId id, bool withSelf) const {
    Vec<ImmId> result;
    Opt<ImmId> tmp = id;
    while (tmp) {
        if (withSelf || tmp != id) { result.push_back(tmp.value()); }
        tmp = getParent(tmp.value());
    }
    return result;
}


void ImmAstContext::format(ColStream& os, const std::string& prefix)
    const {
    os << fmt("{}ImmAstStore\n", prefix);
    store->format(os, prefix + "  ");
}


ImmAstContext ImmAstContext::finishEdit(ImmAstEditContext& ctx) {
    ImmAstContext result = *this;
    result.parents       = ctx.parents.persistent();
    return result;
}


ImmAstVersion ImmAstContext::finishEdit(
    ImmAstEditContext&        ctx,
    const ImmAstReplaceEpoch& epoch) {
    auto newContext = finishEdit(ctx);
    return ImmAstVersion{.context = newContext, .epoch = epoch};
}

ImmId ImmAstContext::add(
    sem::SemId<sem::Org> data,
    ImmAstEditContext&   ctx) {
    return store->add(data, ctx);
}

ImmRootAddResult ImmAstContext::addRoot(sem::SemId<sem::Org> data) {
    auto edit = getEditContext();
    auto root = add(data, edit);
    return ImmRootAddResult{.root = root, .context = edit.finish()};
}

ImmAstVersion ImmAstContext::init(sem::SemId<sem::Org> root) {
    auto [store, imm_root] = addRoot(root);
    ImmAstReplace replace{
        .original = ImmId::Nil(),
        .replaced = imm_root,
    };

    ImmAstVersion result{.context = store};
    result.epoch.replaced.push_back(ImmAstReplaceCascade{{replace}});

    return result;
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
    ImmAstContext* store;
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
    static ImmId_t to_immer(SemId_t const& id, ImmAstEditContext& ctx) {
        return ctx.ctx->store->add(id, ctx);
    }

    static SemId_t from_immer(
        ImmId_t const&       id,
        ImmAstContext const& ctx) {
        return ctx.store->get(id, ctx);
    }
};

template <typename SemType, typename ImmType>
struct ImmSemSerde<sem::SemId<SemType>, org::ImmIdT<ImmType>> {
    static org::ImmIdT<ImmType> to_immer(
        sem::SemId<SemType> const& id,
        ImmAstEditContext&         ctx) {
        return ctx.ctx->store->add(id.asOrg(), ctx).template as<ImmType>();
    }

    static sem::SemId<SemType> from_immer(
        org::ImmIdT<ImmType> const& id,
        ImmAstContext const&        ctx) {
        return ctx.store->get(id, ctx).template as<SemType>();
    }
};


template <IsEnum SemType, IsEnum ImmType>
struct ImmSemSerde<SemType, ImmType> {
    static ImmType to_immer(SemType const& value, ImmAstEditContext& ctx) {
        return static_cast<ImmType>(value);
    }

    static SemType from_immer(
        ImmType const&       value,
        ImmAstContext const& ctx) {
        return static_cast<SemType>(value);
    }
};


template <IsVariant SemType, IsVariant ImmType>
struct ImmSemSerde<SemType, ImmType> {
    static ImmType to_immer(SemType const& value, ImmAstEditContext& ctx) {
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
        ImmType const&       value,
        ImmAstContext const& ctx) {
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
        ImmAstEditContext&                    ctx) {
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
        ImmAstContext const&            ctx) {
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
        ImmAstEditContext&  ctx) {
        Opt<ImmType> base{};
        if (value) {
            base = ImmSemSerde<SemType, ImmType>::to_immer(
                value.value(), ctx);
        }
        return base;
    }

    static Opt<SemType> from_immer(
        Opt<ImmType> const&  value,
        ImmAstContext const& ctx) {
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
        ImmAstEditContext&  ctx) {
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
        ImmAstContext const&   ctx) {
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
        static __T to_immer(__T const& value, ImmAstEditContext& ctx) {   \
            return value;                                                 \
        }                                                                 \
                                                                          \
        static __T from_immer(                                            \
            __T const&           value,                                   \
            ImmAstContext const& ctx) {                                   \
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
        SemType const&     value,
        ImmAstEditContext& ctx) {
        return ImmSemSerde<SemType, ImmType>::to_immer(value, ctx);
    }

    static SemType from_immer(
        ImmBox<ImmType> const& value,
        ImmAstContext const&   ctx) {
        return ImmSemSerde<SemType, ImmType>::from_immer(value.get(), ctx);
    }
};


template <typename SemType, typename ImmType>
void assign_immer_field(
    ImmType&           field,
    SemType const&     value,
    ImmAstEditContext& ctx) {
    field = ImmSemSerde<SemType, ImmType>::to_immer(value, ctx);
}

template <typename SemType, typename ImmType>
void assign_sem_field(
    SemType&             field,
    ImmType const&       value,
    ImmAstContext const& ctx) {
    field = ImmSemSerde<SemType, ImmType>::from_immer(value, ctx);
}


#include "ImmOrgSerde.tcc"

sem::SemId<sem::Org> ImmAstContext::get(ImmId id) {
    return store->get(id, *this);
}

template <org::IsImmOrgValueType ImmType>
ImmId_t org::ImmAstKindStore<ImmType>::add(
    SemId_t            data,
    ImmAstEditContext& ctx) {


    using SemType = imm_to_sem_map<ImmType>::sem_type;
    if (!data->is(SemType::staticKind)) {
        throw store_error::init(fmt(
            "Cannot create store value of kind {} from node of kind {}",
            ImmType::staticKind,
            data->getKind()));
    }


    ImmType value = ImmSemSerde<SemType, ImmType>::to_immer(
        *data.as<SemType>(), ctx);

    CHECK(data->getKind() == ImmType::staticKind);
    return add(value, ctx);
}

template <org::IsImmOrgValueType T>
ImmId ImmAstKindStore<T>::add(const T& value, ImmAstEditContext& ctx) {
    auto  mask   = ImmId::combineMask(T::staticKind);
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
sem::SemId<sem::Org> ImmAstKindStore<T>::get(
    ImmId                id,
    const ImmAstContext& ctx) {
    if (id.isNil()) {
        return sem::SemId<sem::Org>::Nil();
    } else {
        using SemType = imm_to_sem_map<T>::sem_type;
        auto result   = sem::SemId<SemType>::New();
        *result.value = ImmSemSerde<SemType, T>::from_immer(
            ctx.value<T>(id), ctx);

        return result.asOrg();
    }
}


#define forward_declare(__Kind)                                           \
    template class org::ImmAstKindStore<org::Imm##__Kind>;

EACH_SEM_ORG_KIND(forward_declare)
#undef forward_declare
