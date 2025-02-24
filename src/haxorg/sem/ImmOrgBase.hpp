#pragma once
#pragma clang diagnostic ignored "-Wunknown-attributes"

#include <hstd/stdlib/dod_base.hpp>
#include <haxorg/sem/SemOrgBase.hpp>
#include <hstd/stdlib/Time.hpp>

#include <immer/vector.hpp>
#include <immer/box.hpp>
#include <immer/map.hpp>
#include <immer/set.hpp>
#include <immer/flex_vector.hpp>
#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/reflection_visitor.hpp>
#include <haxorg/sem/SemOrgTypes.hpp>
#include <hstd/stdlib/Array.hpp>

namespace org::imm {
struct ImmReflFieldId;
}

template <>
struct std::hash<org::imm::ImmReflFieldId> {
    std::size_t operator()(
        org::imm::ImmReflFieldId const& it) const noexcept;
};


namespace hstd::ext {
template <typename T>
using ImmVec = immer::flex_vector<T>;

template <typename T>
using ImmBox = immer::box<T>;
} // namespace hstd::ext

template <typename T>
struct std::hash<hstd::ext::ImmVec<T>>
    : hstd::std_indexable_hash<hstd::ext::ImmVec<T>> {};

template <typename T>
struct std::hash<immer::vector<T>>
    : hstd::std_indexable_hash<immer::vector<T>> {};

template <typename T>
struct std::formatter<immer::vector<T>>
    : hstd::std_item_iterator_formatter<T, immer::vector<T>> {};

template <typename T>
struct std::formatter<hstd::ext::ImmVec<T>>
    : hstd::std_item_iterator_formatter<T, hstd::ext::ImmVec<T>> {};

namespace hstd::ext {
template <typename K, typename V>
struct ImmMap : immer::map<K, V> {
    using base = immer::map<K, V>;
    using base::at;
    using base::base;
    using base::find;

    ImmMap(base const& val) : base{val} {}

    Opt<V> get(K const& key) const {
        if (auto val = find(key)) {
            return *val;
        } else {
            return std::nullopt;
        }
    }

    bool contains(K const& key) const { return find(key) != nullptr; }
};

template <typename T>
using ImmSet = immer::set<T>;
} // namespace hstd::ext


namespace org::imm {


struct ImmReflPathTag {
    using field_name_type = ImmReflFieldId;
};

using ImmReflPathItemBase = hstd::ReflPathItem<ImmReflPathTag>;
using ImmReflPathBase     = hstd::ReflPath<ImmReflPathTag>;

struct ImmReflFieldId {
    struct R {
        int f;
    };

    static const int member_ptr_size = sizeof(&R::f);
    using member_ptr_store = hstd::Array<hstd::u8, member_ptr_size>;
    member_ptr_store field;

    static hstd::UnorderedMap<ImmReflFieldId, hstd::Str> fieldNames;

    hstd::Str getName() const {
        return fieldNames.get(*this).value_or("<none>");
    }

    template <typename T, typename F>
    static ImmReflFieldId FromTypeField(F T::*fieldPtr) {
        ImmReflFieldId result{};
        std::memcpy(result.field.data(), &fieldPtr, member_ptr_size);
        return result;
    }

    template <typename T, typename F>
    static ImmReflFieldId FromTypeFieldName(
        char const* name,
        F T::*fieldPtr) {
        auto result = FromTypeField(fieldPtr);
        if (!fieldNames.contains(result)) {
            fieldNames.insert_or_assign(result, name);
        }
        return result;
    }

    bool operator==(ImmReflFieldId const& other) const {
        return std::memcmp(
                   other.field.data(), field.data(), member_ptr_size)
            == 0;
    }

    bool operator<(ImmReflFieldId const& other) const {
        return std::memcmp(
                   other.field.data(), field.data(), member_ptr_size)
             < 0;
    }
};


} // namespace org::imm

template <>
struct std::formatter<org::imm::ImmReflFieldId>
    : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const org::imm::ImmReflFieldId& p, FormatContext& ctx)
        const {
        return fmt_ctx(p.getName(), ctx);
    }
};

template <>
struct std::hash<org::imm::ImmReflFieldId::member_ptr_store> {
    size_t operator()(const org::imm::ImmReflFieldId::member_ptr_store&
                          arr) const noexcept {
        size_t result = 0;
        for (const auto& byte : arr) {
            hstd::hax_hash_combine(result, byte);
        }
        return result;
    }
};


template <>
struct hstd::ReflTypeTraits<org::imm::ImmReflPathTag> {
    using AnyFormatterType = AnyFormatter<Str>;
    using AnyHasherType    = AnyHasher<Str>;
    using AnyEqualType     = AnyEqual<Str>;

    using ReflPathStoreType = immer::vector<
        ReflPathItem<org::imm::ImmReflPathTag>>;

    template <typename T>
    static org::imm::ImmReflPathTag::field_name_type InitFieldName(
        T const&    value,
        auto const& field) {
        return org::imm::ImmReflFieldId::FromTypeFieldName<T>(
            field.name, field.pointer);
    }

    static ReflPath<org::imm::ImmReflPathTag> AddPathItem(
        ReflPath<org::imm::ImmReflPathTag>     res,
        ReflPathItem<org::imm::ImmReflPathTag> item) {
        return ReflPath<org::imm::ImmReflPathTag>{
            res.path.push_back(item)};
    }
};


template <typename K, typename V, typename Tag>
struct hstd::ReflVisitor<immer::map<K, V>, Tag>
    : ReflVisitorKeyValue<K, V, immer::map<K, V>, Tag> {};


template <typename K, typename V, typename Tag>
struct hstd::ReflVisitor<hstd::ext::ImmMap<K, V>, Tag>
    : ReflVisitorKeyValue<K, V, hstd::ext::ImmMap<K, V>, Tag> {};

template <typename T, typename Tag>
struct hstd::ReflVisitor<immer::set<T>, Tag>
    : ReflVisitorUnorderedIndexed<T, immer::set<T>, Tag> {};

template <typename T, typename Tag>
struct hstd::ReflVisitor<immer::flex_vector<T>, Tag>
    : ReflVisitorIndexed<T, immer::flex_vector<T>, Tag> {};


template <typename T, typename Tag>
struct hstd::ReflVisitor<hstd::ext::ImmBox<T>, Tag> {
    /// \brief Apply callback to passed value if the path points to it,
    /// otherwise follow the path down the data structure.
    template <typename Func>
    static void visit(
        hstd::ext::ImmBox<T> const& value,
        ReflPathItem<Tag> const&    step,
        Func const&                 cb) {
        LOGIC_ASSERTION_CHECK(step.isDeref(), "{}", step.getKind());
        cb(value.get());
    }


    static Vec<ReflPathItem<Tag>> subitems(
        hstd::ext::ImmBox<T> const& value) {
        Vec<ReflPathItem<Tag>> result;
        result.push_back(ReflPathItem<Tag>::FromDeref());
        return result;
    }
};

template <typename T>
struct std::formatter<hstd::ext::ImmBox<T>> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const hstd::ext::ImmBox<T>& p, FormatContext& ctx) const {
        hstd::fmt_ctx("Box{", ctx);
        hstd::fmt_ctx(p.get(), ctx);
        return hstd::fmt_ctx("}", ctx);
    }
};

template <>
struct std::formatter<hstd::ext::ImmBox<std::string>>
    : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(
        const hstd::ext::ImmBox<std::string>& p,
        FormatContext&                        ctx) const {
        hstd::fmt_ctx("Box{", ctx);
        hstd::fmt_ctx(hstd::escape_literal(p.get()), ctx);
        return hstd::fmt_ctx("}", ctx);
    }
};

template <>
struct std::formatter<hstd::ext::ImmBox<hstd::Str>>
    : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const hstd::ext::ImmBox<hstd::Str>& p, FormatContext& ctx)
        const {
        hstd::fmt_ctx("Box{", ctx);
        hstd::fmt_ctx(hstd::escape_literal(p.get()), ctx);
        return hstd::fmt_ctx("}", ctx);
    }
};

template <typename T>
struct hstd::JsonSerde<hstd::ext::ImmBox<T>> {
    static json to_json(hstd::ext::ImmBox<T> const& it) {
        return JsonSerde<T>::to_json(it.get());
    }
    static hstd::ext::ImmBox<T> from_json(json const& j) {
        return hstd::ext::ImmBox<T>{JsonSerde<T>::from_json(j)};
    }
};

template <typename T>
struct hstd::JsonSerde<hstd::ext::ImmVec<T>> {
    static json to_json(hstd::ext::ImmVec<T> const& it) {
        auto result = json::array();
        for (auto const& i : it) {
            result.push_back(JsonSerde<T>::to_json(i));
        }

        return result;
    }
    static hstd::ext::ImmVec<T> from_json(json const& j) {
        hstd::ext::ImmVec<T> result;
        auto                 tmp = result.transient();
        for (auto const& i : j) {
            tmp.push_back(JsonSerde<T>::from_json(i));
        }
        return tmp.persistent();
    }
};

template <typename T>
struct hstd::JsonSerde<hstd::ext::ImmSet<T>> {
    static json to_json(hstd::ext::ImmSet<T> const& it) {
        auto result = json::array();
        for (auto const& i : it) {
            result.push_back(JsonSerde<T>::to_json(i));
        }

        return result;
    }
    static hstd::ext::ImmSet<T> from_json(json const& j) {
        hstd::ext::ImmSet<T> result;
        auto                 tmp = result.transient();
        for (auto const& i : j) {
            result.insert(JsonSerde<T>::from_json(i));
        }
        return tmp.persistent();
    }
};

template <typename T>
struct std::formatter<hstd::ext::ImmSet<T>> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        hstd::ext::ImmSet<T> const& p,
        FormatContext&              ctx) const {
        std::formatter<std::string> fmt;
        fmt.format("{", ctx);
        fmt.format(join(", ", p), ctx);
        return fmt.format("}", ctx);
    }
};

template <typename K, typename V>
using ImmMapTransientDefault = immer::map_transient<
    K,
    V,
    /*Hash        =*/std::hash<K>,
    /*Equal       =*/std::equal_to<K>,
    /*MemoryPolicy=*/immer::default_memory_policy,
    /*B           =*/immer::default_bits>;


template <typename K, typename V>
struct std::formatter<ImmMapTransientDefault<K, V>>
    : hstd::std_kv_tuple_iterator_formatter<
          K,
          V,
          ImmMapTransientDefault<K, V>> {};

template <typename K, typename V>
struct std::formatter<hstd::ext::ImmMap<K, V>>
    : hstd::
          std_kv_tuple_iterator_formatter<K, V, hstd::ext::ImmMap<K, V>> {
};

template <typename K, typename V>
struct std::formatter<immer::map<K, V>>
    : hstd::std_kv_tuple_iterator_formatter<K, V, immer::map<K, V>> {};


template <typename K, typename V>
struct hstd::JsonSerde<immer::map<K, V>> {
    static json to_json(immer::map<K, V> const& it) {
        auto result = json::array();
        for (auto const& [key, val] : it) {
            result.push_back(json::object({
                {"key", JsonSerde<K>::to_json(key)},
                {"value", JsonSerde<V>::to_json(val)},
            }));
        }

        return result;
    }
    static immer::map<K, V> from_json(json const& j) {
        immer::map<K, V> result;
        auto             tmp = result.transient();
        for (auto const& i : j) {
            result.insert(
                JsonSerde<K>::from_json(i["key"]),
                JsonSerde<V>::from_json(i["value"]));
        }
        return tmp.persistent();
    }
};

template <typename K, typename V>
struct hstd::JsonSerde<hstd::ext::ImmMap<K, V>> {
    static json to_json(hstd::ext::ImmMap<K, V> const& it) {
        return JsonSerde<immer::map<K, V>>::to_json(it);
    }
    static hstd::ext::ImmMap<K, V> from_json(json const& j) {
        return JsonSerde<immer::map<K, V>>::from_json(j);
    }
};


namespace org::imm {

#define forward_declare(__Kind) struct Imm##__Kind;
EACH_SEM_ORG_KIND(forward_declare)
#undef forward_declare

struct ImmAstContext;
struct ImmOrg;

template <typename T>
struct ImmIdT;

static const hstd::u64 ImmIdMaskSize   = 4 * 6;
static const hstd::u64 ImmIdMaskOffset = 8 * 8 - ImmIdMaskSize;
using ImmIdBase                        = hstd::dod::Id<
                           hstd::u64,
                           hstd::u64,
                           std::integral_constant<hstd::u64, ImmIdMaskSize>>;

struct ImmId : ImmIdBase {
    using IdType   = hstd::u64;
    using NodeIdxT = hstd::u32;

    static const hstd::u64 NodeIdxMask;
    static const hstd::u64 NodeIdxOffset;
    static const hstd::u64 NodeKindMask;
    static const hstd::u64 NodeKindOffset;

    // clang-format off
    static NodeIdxT   getNodeIdx(IdType id)    { return NodeIdxT((id & NodeIdxMask) >> NodeIdxOffset); }
    static OrgSemKind getKind(IdType id)       { return OrgSemKind((id & NodeKindMask) >> NodeKindOffset); }
    // clang-format on

    static IdType combineMask(OrgSemKind kind);

    static IdType combineFullValue(OrgSemKind kind, NodeIdxT node);

    static ImmId Nil() {
        auto res = ImmId::FromValue(0);
        return res;
    }

    ImmId() : ImmIdBase{0} {};
    static ImmId FromValue(hstd::u64 value) {
        return ImmId{ImmIdBase::FromValue(value)};
    }
    ImmId(ImmIdBase const& base) : ImmIdBase{base} {};

    ImmId(OrgSemKind kind, NodeIdxT nodeIndex)
        : ImmIdBase{combineFullValue(kind, nodeIndex)} {}

    OrgSemKind getKind() const { return ImmId::getKind(value); }
    bool       is(OrgSemKind kind) const { return getKind() == kind; }

    /// \brief Get index of the node in associated kind store. NOTE: The
    /// node must not be nil
    NodeIdxT getNodeIndex() const { return ImmId::getNodeIdx(value); }

    /// \brief Convert this node to one with specified kind
    template <typename T>
    ImmIdT<T> as() const {
        if constexpr (!std::is_abstract_v<T>) {
            if (T::staticKind != getKind()) {
                throw std::logic_error(hstd::fmt(
                    "Kind for type T '{}' != ID kind '{}'",
                    T::staticKind,
                    getKind()));
            }
        }

        return ImmIdT<T>{*this};
    }

    /// \brief non-nil nodes are converter to `true`
    operator bool() const { return !isNil(); }

    std::string getReadableId() const;

    void assertValid() const;
};

template <typename T>
struct ImmIdT : public ImmId {
    ImmId toId() const { return *this; }
    ImmIdT(ImmId base) : ImmId(base) {}
    ImmIdT() : ImmId(ImmId::Nil()) {}

    static ImmIdT<T> Nil() { return ImmIdT<T>(ImmId::Nil()); }
};


struct ImmOrg {
    hstd::ext::ImmVec<ImmId>       subnodes;
    hstd::Opt<org::parse::LineCol> loc             = std::nullopt;
    virtual OrgSemKind             getKind() const = 0;

    ImmId at(int pos) const { return subnodes.at(pos); }
    auto  begin() const { return subnodes.begin(); }
    auto  end() const { return subnodes.end(); }
    int   size() const { return subnodes.size(); }
    int   indexOf(org::imm::ImmId subnode) const {
        for (int i = 0; i < subnodes.size(); ++i) {
            if (subnodes.at(i) == subnode) { return i; }
        }
        return -1;
    }

    bool is(SemSet const& kind) const { return kind.contains(getKind()); }
    bool is(OrgSemKind kind) const { return getKind() == kind; }

    template <typename T>
    T const* dyn_cast() const {
        return dynamic_cast<T const*>(this);
    }

    template <typename T>
    T const* as() const {
        auto res = dyn_cast<T>();
        if (res == nullptr) {
            if constexpr (std::is_abstract_v<T>) {
                throw std::logic_error(hstd::fmt(
                    "Cannot cast node of kind {}", this->getKind()));
            } else {
                throw std::logic_error(hstd::fmt(
                    "Cannot cast node of kind {} to kind {}",
                    this->getKind(),
                    T::staticKind));
            }
        }
        return res;
    }

    DESC_FIELDS(ImmOrg, (subnodes, loc));
};

} // namespace org::imm

template <>
struct std::formatter<org::imm::ImmId> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const org::imm::ImmId& p, FormatContext& ctx) const {
        return fmt_ctx(p.getReadableId(), ctx);
    }
};


template <>
struct hstd::JsonSerde<org::imm::ImmId> {
    static json to_json(org::imm::ImmId const& it) {
        return json::object(
            {{"number", it.getValue()}, {"format", it.getReadableId()}});
    }
    static org::imm::ImmId from_json(json const& j) {
        return org::imm::ImmId::FromValue(
            j["number"].get<unsigned long long>());
    }
};

template <typename T>
struct hstd::JsonSerde<org::imm::ImmIdT<T>> {
    static json to_json(org::imm::ImmIdT<T> const& it) {
        return JsonSerde<org::imm::ImmId>::to_json(it.toId());
    }
    static org::imm::ImmIdT<T> from_json(json const& j) {
        return org::imm::ImmIdT<T>{
            JsonSerde<org::imm::ImmId>::from_json(j)};
    }
};

template <>
struct hstd::ReflVisitor<org::imm::ImmId, org::imm::ImmReflPathTag>
    : hstd::
          ReflVisitorLeafType<org::imm::ImmId, org::imm::ImmReflPathTag> {
};

template <typename T>
struct hstd::ReflVisitor<org::imm::ImmIdT<T>, org::imm::ImmReflPathTag>
    : hstd::ReflVisitorLeafType<
          org::imm::ImmIdT<T>,
          org::imm::ImmReflPathTag> {};


template <>
struct hstd::hshow<org::imm::ImmId> {
    static void format(
        hstd::ColStream&        s,
        org::imm::ImmId const&  value,
        hstd::hshow_opts const& opts) {
        auto copy = opts;
        copy.with_use_quotes(false);
        hshow_ctx(s, value.format(), copy);
    }
};
