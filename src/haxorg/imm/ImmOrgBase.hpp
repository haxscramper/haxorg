#pragma once
#pragma clang diagnostic ignored "-Wunknown-attributes"

#include <hstd/stdlib/dod_base.hpp>
#include <haxorg/sem/SemOrgBase.hpp>
#include <hstd/stdlib/Time.hpp>

#include <hstd/ext/immer.hpp>
#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/reflection_visitor.hpp>
#include <haxorg/sem/SemOrgTypes.hpp>
#include <hstd/stdlib/Array.hpp>
#include <hstd/stdlib/ColText.hpp>
#include <hstd/stdlib/ColTextHShow.hpp>

namespace org::imm {
struct ImmReflFieldId;
}

template <>
struct std::hash<org::imm::ImmReflFieldId> {
    std::size_t operator()(org::imm::ImmReflFieldId const& it) const noexcept;
};


namespace org::imm {


struct ImmReflPathTag {
    using field_name_type = ImmReflFieldId;
};

using ImmReflPathItemBase = hstd::ReflPathItem<ImmReflPathTag>;
using ImmReflPathBase     = hstd::ReflPath<ImmReflPathTag>;

struct [[refl]] ImmReflFieldId {
    [[refl]] hstd::Str getName() const;

    using offset_type = std::uint32_t;

    std::optional<std::type_index> typeId;
    offset_type                    index;

    ImmReflFieldId() = default;

    static ImmReflFieldId FromIdParts(
        std::optional<std::type_index> typeId,
        offset_type                    index);

    template <typename T, typename F>
    static ImmReflFieldId FromTypeField(F T::* fieldPtr) {
        return ImmReflFieldId::FromIdParts(
            typeid(T), hstd::get_total_field_index_by_ptr(fieldPtr));
    }

    bool operator==(ImmReflFieldId const& other) const { return index == other.index; }

    bool operator<(ImmReflFieldId const& other) const { return index < other.index; }

    std::uint64_t getSerializableId() const { return index; }

    static ImmReflFieldId fromSerializableId(std::uint64_t id);
};


} // namespace org::imm

template <>
struct fmt::formatter<org::imm::ImmReflFieldId> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(org::imm::ImmReflFieldId const& p, fmt::format_context& ctx)
        const {
        return fmt_ctx(p.getName(), ctx);
    }
};

template <>
struct hstd::ReflTypeTraits<org::imm::ImmReflPathTag> {
    using AnyTypeTuple     = std::tuple<Str>;
    using AnyFormatterType = AnyFormatter<Str>;
    using AnyHasherType    = AnyHasher<Str>;
    using AnyEqualType     = AnyEqual<Str>;

    using ReflPathStoreType = immer::vector<ReflPathItem<org::imm::ImmReflPathTag>>;

    template <typename T>
    static org::imm::ImmReflPathTag::field_name_type InitFieldName(
        T const&    value,
        auto const& field) {
        return org::imm::ImmReflFieldId::FromTypeField<T>(field.pointer);
    }

    static ReflPath<org::imm::ImmReflPathTag> AddPathItem(
        ReflPath<org::imm::ImmReflPathTag>     res,
        ReflPathItem<org::imm::ImmReflPathTag> item) {
        return ReflPath<org::imm::ImmReflPathTag>{res.path.push_back(item)};
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
        LOGIC_ASSERTION_CHECK(step.isDeref(), hstd::enum_to_string(step.getKind()));
        cb(value.get());
    }


    static Vec<ReflPathItem<Tag>> subitems(hstd::ext::ImmBox<T> const& value) {
        Vec<ReflPathItem<Tag>> result;
        result.push_back(ReflPathItem<Tag>::FromDeref());
        return result;
    }
};

template <typename T>
struct fmt::formatter<hstd::ext::ImmBox<T>> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(hstd::ext::ImmBox<T> const& p, fmt::format_context& ctx) const {
        hstd::fmt_ctx("Box{", ctx);
        hstd::fmt_ctx(p.get(), ctx);
        return hstd::fmt_ctx("}", ctx);
    }
};

template <>
struct fmt::formatter<hstd::ext::ImmBox<std::string>> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(
        hstd::ext::ImmBox<std::string> const& p,
        fmt::format_context&                  ctx) const;
};

template <>
struct fmt::formatter<hstd::ext::ImmBox<hstd::Str>> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(hstd::ext::ImmBox<hstd::Str> const& p, fmt::format_context& ctx)
        const;
};


template <typename T>
struct fmt::formatter<hstd::ext::ImmSet<T>> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(hstd::ext::ImmSet<T> const& p, fmt::format_context& ctx) const {
        hstd::fmt_ctx("{", ctx);
        hstd::fmt_ctx(join(", ", p), ctx);
        return hstd::fmt_ctx("}", ctx);
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
struct fmt::formatter<ImmMapTransientDefault<K, V>>
    : hstd::std_kv_tuple_iterator_formatter<K, V, ImmMapTransientDefault<K, V>> {};

template <typename K, typename V>
struct fmt::formatter<hstd::ext::ImmMap<K, V>>
    : hstd::std_kv_tuple_iterator_formatter<K, V, hstd::ext::ImmMap<K, V>> {};

template <typename K, typename V>
struct fmt::formatter<immer::map<K, V>>
    : hstd::std_kv_tuple_iterator_formatter<K, V, immer::map<K, V>> {};


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
using ImmIdBase                        = hstd::dod::
    Id<hstd::u64, hstd::u64, std::integral_constant<hstd::u64, ImmIdMaskSize>>;

struct [[refl]] ImmId : ImmIdBase {
    BOOST_DESCRIBE_CLASS(ImmId, (ImmIdBase), (), (), ());
    [[refl]] typedef hstd::u64 IdType;
    [[refl]] typedef hstd::u32 NodeIdxT;

    static const hstd::u64 NodeIdxMask;
    static const hstd::u64 NodeIdxOffset;
    static const hstd::u64 NodeKindMask;
    static const hstd::u64 NodeKindOffset;

    static NodeIdxT getNodeIdx(IdType id);

    static OrgSemKind getKind(IdType id);

    static IdType combineMask(OrgSemKind kind);

    static IdType combineFullValue(OrgSemKind kind, NodeIdxT node);

    static ImmId Nil() {
        auto res = ImmId::FromValue(0);
        return res;
    }

    ImmId() : ImmIdBase{0} {};
    static ImmId FromValue(hstd::u64 value);
    ImmId(ImmIdBase const& base) : ImmIdBase{base} {};

    ImmId(OrgSemKind kind, NodeIdxT nodeIndex)
        : ImmIdBase{combineFullValue(kind, nodeIndex)} {}

    [[refl]] OrgSemKind getKind() const;
    [[refl]] bool       is(OrgSemKind kind) const;

    /// \brief Get index of the node in associated kind store. NOTE: The
    /// node must not be nil
    [[refl]] NodeIdxT getNodeIndex() const;

    /// \brief Convert this node to one with specified kind
    template <typename T>
    ImmIdT<T> as() const {
        if constexpr (!std::is_abstract_v<T>) {
            if (T::staticKind != getKind()) {
                throw std::logic_error(
                    hstd::fmt(
                        "Kind for type T '{}' != ID kind '{}'",
                        T::staticKind,
                        getKind()));
            }
        }

        return ImmIdT<T>{*this};
    }

    /// \brief non-nil nodes are converter to `true`
    operator bool() const { return !isNil(); }

    [[refl]] std::string getReadableId() const;

    void assertValid() const;

    bool operator<(Id other) const noexcept;
    bool operator<=(Id other) const noexcept;
    bool operator==(Id other) const noexcept;
    bool operator!=(Id other) const noexcept;
};

template <typename T>
struct ImmIdT : public ImmId {
    BOOST_DESCRIBE_CLASS(ImmIdT, (ImmId), (), (), ());
    ImmId toId() const { return *this; }
    ImmIdT(ImmId base) : ImmId(base) {}
    ImmIdT() : ImmId(ImmId::Nil()) {}

    static ImmIdT<T> Nil() { return ImmIdT<T>(ImmId::Nil()); }
};

struct [[refl]] ImmOrg {
    hstd::ext::ImmVec<ImmId>         subnodes;
    hstd::Opt<org::parse::SourceLoc> loc             = std::nullopt;
    virtual OrgSemKind               getKind() const = 0;
    virtual ~ImmOrg()                                = default;

    ImmId                              at(int pos) const;
    hstd::ext::ImmVec<ImmId>::iterator begin() const;
    hstd::ext::ImmVec<ImmId>::iterator end() const;
    int                                size() const;
    int                                indexOf(org::imm::ImmId subnode) const;

    bool is(SemSet const& kind) const;
    bool is(OrgSemKind kind) const;

    template <typename T>
    T const* dyn_cast() const;

    template <typename T>
    T const* as() const;

    DESC_FIELDS(ImmOrg, (subnodes, loc));
};

} // namespace org::imm

template <>
struct fmt::formatter<org::imm::ImmId> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(org::imm::ImmId const& p, fmt::format_context& ctx) const {
        return hstd::fmt_ctx(p.getReadableId(), ctx);
    }
};


template <>
struct hstd::ReflVisitor<org::imm::ImmId, org::imm::ImmReflPathTag>
    : hstd::ReflVisitorLeafType<org::imm::ImmId, org::imm::ImmReflPathTag> {};

template <typename T>
struct hstd::ReflVisitor<org::imm::ImmIdT<T>, org::imm::ImmReflPathTag>
    : hstd::ReflVisitorLeafType<org::imm::ImmIdT<T>, org::imm::ImmReflPathTag> {};


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
