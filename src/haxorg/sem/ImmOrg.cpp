#include <haxorg/sem/ImmOrg.hpp>
#include <hstd/stdlib/Exception.hpp>
#include <immer/vector_transient.hpp>
#include <hstd/stdlib/Enumerate.hpp>
#include <boost/mp11.hpp>
#include <boost/preprocessor.hpp>

const u64 org::ImmId::NodeIdxMask    = 0x000000FFFFFFFFFF; // >>0*0=0,
const u64 org::ImmId::NodeIdxOffset  = 0;
const u64 org::ImmId::NodeKindMask   = 0x000FFF0000000000; // >>10*4=40
const u64 org::ImmId::NodeKindOffset = 40;
const u64 org::ImmId::StoreIdxMask   = 0xFFF0000000000000; // >>13*4=52
const u64 org::ImmId::StoreIdxOffset = 52;

org::ImmId::IdType org::ImmId::combineMask(
    StoreIdxT  store,
    OrgSemKind kind) {
    auto res = (u64(kind) << NodeKindOffset) & NodeKindMask
             | (u64(store) << StoreIdxOffset) & StoreIdxMask;

    auto t = ImmId{ImmId::FromMaskedIdx(0, res >> ImmIdMaskOffset)};
    CHECK(t.getKind() == kind) << fmt(
        R"(
kind:    {0:016X} {0:064b} {1}
kind<<:  {2:016X} {2:064b}
mask:    {3:016X} {3:064b}
t.kind:  {4:016X} {4:064b}
t.kind<<:{5:016X} {5:064b}
t.value: {6:016X} {6:064b}
res:     {7:016X} {7:064b})",
        u64(kind),
        kind,
        u64(kind) << NodeKindOffset,
        NodeKindMask,
        u64(t.getKind()),
        u64(t.getKind()) << NodeKindOffset,
        t.value,
        res >> ImmIdMaskOffset);


    return res >> ImmIdMaskOffset;
}

org::ImmId::IdType org::ImmId::combineFullValue(
    StoreIdxT  store,
    OrgSemKind kind,
    NodeIdxT   node) {
    return (combineMask(store, kind) << ImmIdMaskOffset)
         | (u64(node) << NodeIdxOffset) & NodeIdxMask;
}

#define _define_static(__Kind)                                            \
    const OrgSemKind org::Imm##__Kind::staticKind = OrgSemKind::__Kind;

EACH_SEM_ORG_KIND(_define_static)
#undef _define_static

#define _eq_method(__QualType, _)                                         \
    bool org::Imm##__QualType::operator==(                                \
        org::Imm##__QualType const& other) const {                        \
        bool result = true;                                               \
        for_each_field_with_bases<org::Imm##__QualType>(                  \
            [&](auto const& field) {                                      \
                if (result) {                                             \
                    result &= this->*field.pointer                        \
                           == other.*field.pointer;                       \
                }                                                         \
            });                                                           \
        return result;                                                    \
    }

EACH_SEM_ORG_RECORD(_eq_method)
#undef _eq_method

template <typename T>
std::size_t get_std_hash(T const& it) {
    return std::hash<T>{}(it);
}

template <typename T>
struct std::hash<ImmBox<T>> {
    std::size_t operator()(ImmBox<T> const& it) const noexcept {
        return std::hash<T>{}(it);
    }
};

template <typename T>
struct std::hash<ImmVec<T>> {
    std::size_t operator()(ImmVec<T> const& it) const noexcept {
        std::size_t result = 0;
        for (auto const& val : it) {
            boost::hash_combine(result, get_std_hash<T>(val));
        }
        return result;
    }
};

template <typename K, typename V>
struct std::hash<ImmMap<K, V>> {
    std::size_t operator()(ImmMap<K, V> const& it) const noexcept {
        std::size_t result = 0;
        Vec<K>      keys;
        for (auto const& [key, _] : it) { keys.push_back(key); }
        rs::sort(keys);
        for (auto const& key : keys) {
            boost::hash_combine(result, get_std_hash<K>(key));
            boost::hash_combine(result, get_std_hash<V>(it[key]));
        }
        return result;
    }
};

template <IsVariant T>
struct std::hash<T> {
    std::size_t operator()(T const& it) const noexcept {
        std::size_t result = 0;
        boost::hash_combine(result, get_std_hash(it.index()));
        std::visit(
            [&](auto const& var) {
                boost::hash_combine(result, get_std_hash(var));
            },
            it);
        return result;
    }
};


namespace {

template <typename T>
std::size_t imm_hash_build(T const& value) {
    std::size_t result = 0;
    for_each_field_with_bases<T>([&](auto const& field) {
        boost::hash_combine(
            result,
            std::hash<
                std::remove_cvref_t<decltype(value.*field.pointer)>>{}(
                value.*field.pointer));
    });
    return result;
}
} // namespace

#define _declare_hash(__parent, __qual, _)                                \
    template <>                                                           \
    struct std::hash<org::Imm##__parent::__qual> {                        \
        std::size_t operator()(                                           \
            org::Imm##__parent::__qual const& it) const noexcept {        \
            return imm_hash_build(it);                                    \
        }                                                                 \
    };

EACH_SEM_ORG_RECORD_NESTED(_declare_hash)
#undef _declare_hash

#undef _define_static
#define _define_hash(__kind)                                              \
    std::size_t std::hash<org::Imm##__kind>::operator()(                  \
        org::Imm##__kind const& it) const noexcept {                      \
        return imm_hash_build(it);                                        \
    }

EACH_SEM_ORG_KIND(_define_hash)
#undef _define_hash


using namespace org;

struct store_error : CRTP_hexception<store_error> {};

const ImmOrg* ParseUnitStore::at(ImmId index) const {
    switch (index.getKind()) {

#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: {                                            \
        org::Imm##__Kind const* res = store##__Kind.at(index);            \
        CHECK(res->getKind() == index.getKind());                         \
        return res;                                                       \
    }
        EACH_SEM_ORG_KIND(_case)
#undef _case
    }
}


ImmId ParseUnitStore::add(
    ImmId::StoreIdxT     selfIndex,
    sem::SemId<sem::Org> data,
    ContextStore*        context) {
    switch (data->getKind()) {

#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: {                                            \
        auto result = store##__Kind.add(selfIndex, data, context);        \
        return result;                                                    \
    }

        EACH_SEM_ORG_KIND(_case)
#undef _case
    }

    LOG(FATAL)
        << ("Unhandled node kind for automatic creation $#"
            % to_string_vec(data->getKind()));
}

const ImmOrg* ContextStore::at(ImmId id) const {
    ImmOrg const* res = getStoreByIndex(id.getStoreIndex()).at(id);
    CHECK(res->getKind() == id.getKind());
    return res;
}

template <typename T>
void KindStore<T>::format(ColStream& os, const std::string& linePrefix)
    const {
    bool       isFirst = true;
    Vec<ImmId> ids;
    for (auto const& it : values.id_map) { ids.push_back(it.second); }

    rs::sort(ids);

    for (auto const& id : ids) {
        if (!isFirst) { os << "\n"; }
        isFirst = false;
        os << fmt(
            "{}[{}]: {}", linePrefix, id.getReadableId(), values.at(id));
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
        store##__Kind.format(os, prefix + "  ");                          \
    }

    EACH_SEM_ORG_KIND(_kind)
#undef _kind
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

#define _gen_map(__Kind)                                                  \
    template <>                                                           \
    struct imm_to_sem_map<org::Imm##__Kind> {                             \
        using sem_type = sem::__Kind;                                     \
    };
EACH_SEM_ORG_KIND(_gen_map)
#undef _gen_map


struct AddContext {
    ContextStore*    store;
    ImmId            currentAdd = ImmId::Nil();
    ImmId::StoreIdxT idx        = 0;
};

template <typename Sem, typename Imm>
struct ImmSemSerde {
    static Imm to_immer(Sem const& value, AddContext const& ctx) {
        throw store_error::init(
            fmt("Implement store conversion for value {}",
                demangle(typeid(value).name())));
        return Imm{};
    }
    static Sem from_immer(AddContext const& ctx, Imm const& value) {
        return Sem{};
    }
};

using SemId_t = sem::SemId<sem::Org>;
using ImmId_t = org::ImmId;

template <>
struct ImmSemSerde<SemId_t, ImmId_t> {
    static ImmId_t to_immer(SemId_t const& id, AddContext const& ctx) {
        return ctx.store->getStoreByIndex(ctx.idx).add(
            ctx.idx, id, ctx.store);
    }
};

template <typename SemType, typename ImmType>
void copy_field(
    ImmType&          field,
    SemType const&    value,
    AddContext const& ctx) {
    field = ImmSemSerde<SemType, ImmType>::to_immer(value, ctx);
}

template <IsVariant SemType, IsVariant ImmType>
struct ImmSemSerde<Vec<SemType>, ImmVec<ImmType>> {
    static ImmVec<ImmType> to_immer(
        SemType const&    value,
        AddContext const& ctx) {
        ImmType result = variant_from_index(value.index());
        std::visit(
            [&](auto& out) {
                using ImmVariantItem = std::remove_cvref_t<decltype(out)>;
                using SemVariantItem = std::variant_alternative_t<
                    boost::mp11::mp_find<ImmType, ImmVariantItem>::value,
                    SemType>;

                out = ImmSemSerde<SemType, ImmType>::to_immer(
                    std::get<SemVariantItem>(value), ctx);
            },
            result);
        return result;
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
};

template <>
struct ImmSemSerde<sem::Word, org::ImmWord> {
    static org::ImmWord to_immer(
        sem::Word const&  value,
        AddContext const& ctx) {
        org::ImmWord result;
        copy_field(result.text, value.text, ctx);
        return result;
    }
};

template <>
struct ImmSemSerde<sem::Newline, org::ImmNewline> {
    static org::ImmNewline to_immer(
        sem::Newline const& value,
        AddContext const&   ctx) {
        org::ImmNewline result;
        copy_field(result.text, value.text, ctx);
        return result;
    }
};

template <>
struct ImmSemSerde<int, int> {
    static int to_immer(int const& value, AddContext const& ctx) {
        return value;
    }
};

template <>
struct ImmSemSerde<sem::Paragraph, org::ImmParagraph> {
    static org::ImmParagraph to_immer(
        sem::Paragraph const& value,
        AddContext const&     ctx) {
        org::ImmParagraph result;
        copy_field(result.subnodes, value.subnodes, ctx);
        return result;
    }
};


template <>
struct ImmSemSerde<sem::Verbatim, org::ImmVerbatim> {
    static org::ImmVerbatim to_immer(
        sem::Verbatim const& value,
        AddContext const&    ctx) {
        org::ImmVerbatim result;
        copy_field(result.subnodes, value.subnodes, ctx);
        return result;
    }
};


template <>
struct ImmSemSerde<sem::Document, org::ImmDocument> {
    static org::ImmDocument to_immer(
        sem::Document const& value,
        AddContext const&    ctx) {
        org::ImmDocument result;
        copy_field(result.subnodes, value.subnodes, ctx);
        return result;
    }
};

template <>
struct ImmSemSerde<sem::Subtree::Property, org::ImmSubtree::Property> {
    static org::ImmSubtree::Property to_immer(
        sem::Subtree::Property const& value,
        AddContext const&             ctx) {
        org::ImmSubtree::Property result;
        copy_field(result.data, value.data, ctx);
        return result;
    }
};

template <>
struct ImmSemSerde<sem::Subtree, org::ImmSubtree> {
    static org::ImmSubtree to_immer(
        sem::Subtree const& value,
        AddContext const&   ctx) {
        org::ImmSubtree result;
        copy_field(result.level, value.level, ctx);
        copy_field(result.subnodes, value.subnodes, ctx);
        copy_field(result.title, value.title, ctx);
        copy_field(result.deadline, value.deadline, ctx);
        copy_field(result.properties, value.properties, ctx);
        return result;
    }
};

template <typename ImmType>
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
    auto  mask   = ImmId::combineMask(selfIndex, ImmType::staticKind);
    ImmId result = values.add(value, mask);

    CHECK(result.getKind() == data->getKind())
        << fmt(R"(
result.getValue(): {:064b}
result.getKind():  {:064b}
data->getKind():   {:064b}
mask:              {:064b}
)",
               result.getValue(),
               u64(result.getKind()),
               u64(data->getKind()),
               mask);

    return result;
}

#define forward_declare(__Kind)                                           \
    template class org::KindStore<org::Imm##__Kind>;
EACH_SEM_ORG_KIND(forward_declare)
#undef forward_declare
