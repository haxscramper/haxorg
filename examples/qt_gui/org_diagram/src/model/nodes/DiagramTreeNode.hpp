#pragma once

#include "src/utils/common.hpp"
#include <hstd/stdlib/Vec.hpp>
#include <QObject>
#include <haxorg/sem/ImmOrg.hpp>
#include <src/model/HistoryManager.hpp>

#define _cat "model.diagram"

#pragma clang diagnostic ignored "-Wdeprecated-declarations"

DECL_DESCRIBED_ENUM_STANDALONE(DiaNodeKind, Layer, Canvas, Group, Item);

#define EACH_DIAGRAM_KIND(__impl)                                         \
    __impl(Layer) __impl(Canvas) __impl(Group) __impl(Item)

#define SKIP_FIRST_ARG_AUX(op, ...) __VA_ARGS__
#define SKIP_FIRST_ARG(op, ...) SKIP_FIRST_ARG_AUX(op)

#define EACH_DIAGRAM_KIND_CSV(__CMD)                                      \
    SKIP_FIRST_ARG(EACH_DIAGRAM_KIND(__CMD))

template <typename T>
struct DiaIdT;

static const hstd::u64 DiaIdMaskSize   = 4 * 6;
static const hstd::u64 DiaIdMaskOffset = 8 * 8 - DiaIdMaskSize;
using DiaIdBase                        = hstd::dod::Id<
                           hstd::u64,
                           hstd::u64,
                           std::integral_constant<hstd::u64, DiaIdMaskSize>>;

struct DiaPropertyNames {
    inline static const std::string diagramPosition
        = "HAXORG_DIAGRAM_POSITION";

    inline static const std::string isDiagramNode = "HAXORG_DIAGRAM_NODE";
};


struct [[refl]] DiaId : DiaIdBase {
    BOOST_DESCRIBE_CLASS(DiaId, (DiaIdBase), (), (), ());
    using IdType   = hstd::u64;
    using NodeIdxT = hstd::u32;

    static const hstd::u64 NodeIdxMask;
    static const hstd::u64 NodeIdxOffset;
    static const hstd::u64 NodeKindMask;
    static const hstd::u64 NodeKindOffset;

    // clang-format off
    static NodeIdxT   getNodeIdx(IdType id)    { return NodeIdxT((id & NodeIdxMask) >> NodeIdxOffset); }
    static DiaNodeKind getKind(IdType id)       { return DiaNodeKind((id & NodeKindMask) >> NodeKindOffset); }
    // clang-format on
    static IdType combineMask(DiaNodeKind kind) {
        return ((hstd::u64(kind) << NodeKindOffset) & NodeKindMask)
            >> DiaIdMaskOffset;
    }

    static IdType combineFullValue(DiaNodeKind kind, NodeIdxT node);

    static DiaId Nil() {
        auto res = DiaId::FromValue(0);
        return res;
    }

    DiaId() : DiaIdBase{0} {};
    static DiaId FromValue(hstd::u64 value) {
        return DiaId{DiaIdBase::FromValue(value)};
    }
    DiaId(DiaIdBase const& base) : DiaIdBase{base} {};

    DiaId(DiaNodeKind kind, NodeIdxT nodeIndex)
        : DiaIdBase{combineFullValue(kind, nodeIndex)} {}

    [[refl]] DiaNodeKind getKind() const { return DiaId::getKind(value); }
    [[refl]] bool is(DiaNodeKind kind) const { return getKind() == kind; }

    /// \brief Get index of the node in associated kind store. NOTE: The
    /// node must not be nil
    [[refl]] NodeIdxT getNodeIndex() const {
        return DiaId::getNodeIdx(value);
    }

    /// \brief Convert this node to one with specified kind
    template <typename T>
    DiaIdT<T> as() const {
        if constexpr (!std::is_abstract_v<T>) {
            if (T::staticKind != getKind()) {
                throw std::logic_error(hstd::fmt(
                    "Kind for type T '{}' != ID kind '{}'",
                    T::staticKind,
                    getKind()));
            }
        }

        return DiaIdT<T>{*this};
    }

    /// \brief non-nil nodes are converter to `true`
    operator bool() const { return !isNil(); }

    void assertValid() const;

    bool operator<(Id other) const noexcept {
        return getValue() < other.getValue();
    }

    bool operator<=(Id other) const noexcept {
        return getValue() <= other.getValue();
    }

    bool operator==(Id other) const noexcept {
        return getValue() == other.getValue();
    }

    bool operator!=(Id other) const noexcept {
        return getValue() != other.getValue();
    }
};

template <typename T>
struct DiaIdT : public DiaId {
    BOOST_DESCRIBE_CLASS(DiaIdT, (DiaId), (), (), ());
    DiaId toId() const { return *this; }
    DiaIdT(DiaId base) : DiaId(base) {}
    DiaIdT() : DiaId(DiaId::Nil()) {}

    static DiaIdT<T> Nil() { return DiaIdT<T>(DiaId::Nil()); }
};

struct DiaReflFieldId;

struct DiaReflPathTag {
    using field_name_type = DiaReflFieldId;
};

using DiaReflPathItemBase = hstd::ReflPathItem<DiaReflPathTag>;
using DiaReflPathBase     = hstd::ReflPath<DiaReflPathTag>;

template <typename T, typename Tag>
struct hstd::ReflVisitor<immer::vector<T>, Tag>
    : ReflVisitorIndexed<T, immer::vector<T>, Tag> {};

struct DiaReflFieldId {
    hstd::Str getName() const {
        if (typeId.has_value()) {
            return hstd::get_registered_field_name(typeId.value(), index);
        } else {
            return hstd::fmt("field_{}", index);
        }
    }

    using offset_type = std::uint32_t;

    std::optional<std::type_index> typeId;
    offset_type                    index;

    DiaReflFieldId() = default;

    static DiaReflFieldId FromIdParts(
        std::optional<std::type_index> typeId,
        offset_type                    index) {
        DiaReflFieldId res{};
        res.typeId = typeId;
        res.index  = index;
        return res;
    }

    template <typename T, typename F>
    static DiaReflFieldId FromTypeField(F T::*fieldPtr) {
        return DiaReflFieldId::FromIdParts(
            typeid(T), hstd::get_total_field_index_by_ptr(fieldPtr));
    }

    bool operator==(DiaReflFieldId const& other) const {
        return index == other.index;
    }

    bool operator<(DiaReflFieldId const& other) const {
        return index < other.index;
    }

    std::uint64_t getSerializableId() const { return index; }

    static DiaReflFieldId fromSerializableId(std::uint64_t id) {
        return DiaReflFieldId::FromIdParts(
            std::nullopt, static_cast<offset_type>(id & 0xFFFFFFFF));
    }
};

template <>
struct std::formatter<DiaReflFieldId> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const DiaReflFieldId& p, FormatContext& ctx) const {
        return fmt_ctx(p.getName(), ctx);
    }
};

template <>
struct hstd::ReflTypeTraits<DiaReflPathTag> {
    using AnyTypeTuple     = std::tuple<Str>;
    using AnyFormatterType = AnyFormatter<Str>;
    using AnyHasherType    = AnyHasher<Str>;
    using AnyEqualType     = AnyEqual<Str>;

    using ReflPathStoreType = immer::vector<ReflPathItem<DiaReflPathTag>>;

    template <typename T>
    static DiaReflPathTag::field_name_type InitFieldName(
        T const&    value,
        auto const& field) {
        return DiaReflFieldId::FromTypeField<T>(field.pointer);
    }

    static ReflPath<DiaReflPathTag> AddPathItem(
        ReflPath<DiaReflPathTag>     res,
        ReflPathItem<DiaReflPathTag> item) {
        return ReflPath<DiaReflPathTag>{res.path.push_back(item)};
    }
};


struct [[refl]] DiaPathStep {
    DiaReflPathBase path;
    DESC_FIELDS(DiaPathStep, (path));
    bool operator==(DiaPathStep const& other) const {
        return path == other.path;
    }

    static DiaPathStep FieldIdx(DiaReflFieldId const& field, int idx) {
        return DiaPathStep{DiaReflPathBase{{
            DiaReflPathItemBase::FromFieldName(field),
            DiaReflPathItemBase::FromIndex(idx),
        }}};
    }

    static DiaPathStep Field(DiaReflFieldId const& field) {
        return DiaPathStep{DiaReflPathBase{{
            DiaReflPathItemBase::FromFieldName(field),
        }}};
    }

    static DiaPathStep FieldDeref(DiaReflFieldId const& field) {
        return DiaPathStep{DiaReflPathBase{{
            DiaReflPathItemBase::FromFieldName(field),
            DiaReflPathItemBase::FromDeref(),
        }}};
    }

    bool operator<(DiaPathStep const& other) const {
        return path.lessThan(
            other.path, hstd::ReflPathComparator<DiaReflPathTag>{});
    }
};

struct DiaPath {
    using Store = immer::flex_vector<DiaPathStep>;
    DiaId root;
    Store path;

    DESC_FIELDS(DiaPath, (root, path));

    bool empty() const { return path.empty(); }

    DiaPath() : root{DiaId::Nil()} {}
    DiaPath(DiaId root) : root{root} {};
    DiaPath(DiaId root, DiaReflPathBase const& step0)
        : root{root}, path{DiaPathStep{step0}} {}
    DiaPath(DiaId root, DiaPathStep const& step0)
        : root{root}, path{{step0}} {}
    DiaPath(DiaId root, Store const& path) : root{root}, path{path} {}
    DiaPath(DiaId root, hstd::Span<DiaPathStep> const& span)
        : root{root}, path{span.begin(), span.end()} {}


    hstd::generator<immer::flex_vector<DiaPathStep>> pathSpans(
        bool leafStart = true) const {
        if (leafStart) {
            for (int i = path.size() - 1; 0 <= i; --i) {
                co_yield path.take(i);
            }
        } else {
            for (int i = 0; i < path.size(); ++i) {
                co_yield path.take(i);
            }
        }
    }

    DiaPath pop() const {
        return DiaPath{root, path.erase(path.size() - 1)};
    }

    DiaPath add(DiaPathStep const& it) const {
        return DiaPath{root, path.push_back(it)};
    }

    bool operator==(DiaPath const& other) const {
        return root == other.root && path.operator==(other.path);
    }

    bool operator<(DiaPath const& other) const {
        return root < other.root
            && hstd::itemwise_less_than(
                   path, other.path, std::less<DiaPathStep>{});
    }
};

struct [[refl]] DiaUniqId {
    DiaId   id;
    DiaPath path;
    DESC_FIELDS(DiaUniqId, (id, path));

    DiaUniqId update(DiaId id) const {
        auto res = *this;
        res.id   = id;
        return res;
    }

    bool operator==(DiaUniqId const& it) const {
        return id == it.id && path == it.path;
    }

    bool operator<(DiaUniqId const& it) const {
        return id < it.id && path < it.path;
    }
};

template <>
struct std::hash<DiaReflFieldId> {
    std::size_t operator()(DiaReflFieldId const& step) const noexcept {
        hstd::AnyHasher<hstd::Str> hasher;
        std::size_t                result = 0;
        hstd::hax_hash_combine(result, step.index);
        return result;
    }
};

template <>
struct std::hash<DiaPathStep> {
    std::size_t operator()(DiaPathStep const& step) const noexcept {
        hstd::AnyHasher<hstd::Str> hasher;
        std::size_t                result = 0;
        for (int i = 0; i < step.path.path.size(); ++i) {
            DiaReflPathItemBase const& it = step.path.path.at(i);
            hstd::hax_hash_combine(result, i);
            hstd::hax_hash_combine(result, it);
        }
        return result;
    }
};

template <>
struct std::hash<DiaPath> {
    std::size_t operator()(DiaPath const& it) const noexcept {
        std::size_t result = 0;
        hstd::hax_hash_combine(result, it.root);
        hstd::hax_hash_combine(result, it.path);
        return result;
    }
};


template <>
struct std::hash<DiaUniqId> {
    std::size_t operator()(DiaUniqId const& it) const noexcept {
        std::size_t result = 0;
        hstd::hax_hash_combine(result, it.id);
        hstd::hax_hash_combine(result, it.path);
        return result;
    }
};

struct DiaNode {
    virtual DiaNodeKind      getKind() const = 0;
    hstd::ext::ImmVec<DiaId> subnodes;
    org::imm::ImmAdapter     id;

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


    DESC_FIELDS(DiaNode, (subnodes, id));
};

struct DiaNodeLayer : DiaNode {
    static const DiaNodeKind staticKind = DiaNodeKind::Layer;
    DiaNodeKind getKind() const override { return staticKind; }
    BOOST_DESCRIBE_CLASS(DiaNodeLayer, (DiaNode), (), (), ());
};

struct DiaNodeCanvas : DiaNode {
    static const DiaNodeKind staticKind = DiaNodeKind::Canvas;
    DiaNodeKind getKind() const override { return staticKind; }
    BOOST_DESCRIBE_CLASS(DiaNodeCanvas, (DiaNode), (), (), ());
};

struct DiaNodeGroup : DiaNode {
    static const DiaNodeKind staticKind = DiaNodeKind::Group;
    DiaNodeKind getKind() const override { return staticKind; }
    BOOST_DESCRIBE_CLASS(DiaNodeGroup, (DiaNode), (), (), ());
};

struct DiaNodeItem : DiaNode {
    static const DiaNodeKind staticKind = DiaNodeKind::Item;

    struct Pos {
        int x;
        int y;
        DESC_FIELDS(Pos, (x, y));
    };


    org::imm::ImmAdapterT<org::imm::ImmSubtree> getSubtree() const {
        return id.as<org::imm::ImmSubtree>();
    }

    Pos getPos() const {
        return getStructuredProperty<Pos>(
                   getSubtree(), DiaPropertyNames::diagramPosition)
            .value();
    }


    DiaNodeKind getKind() const override { return staticKind; }
    BOOST_DESCRIBE_CLASS(DiaNodeItem, (DiaNode), (), (), ());
};

template <typename Func>
void switch_dia_ptr(DiaNode const* node, Func const& cb) {
    switch (node->getKind()) {
#define _case(__Kind)                                                     \
    case DiaNodeKind::__Kind: {                                           \
        cb(dynamic_cast<DiaNode##__Kind const*>(node));                   \
        break;                                                            \
    }

        EACH_DIAGRAM_KIND(_case)
#undef _case
    }
}

template <typename Func>
void switch_dia_id(DiaId node, Func const& cb) {
    switch (node.getKind()) {
#define _case(__Kind)                                                     \
    case DiaNodeKind::__Kind: {                                           \
        cb(node.as<DiaNode##__Kind>());                                   \
        break;                                                            \
    }

        EACH_DIAGRAM_KIND(_case)
#undef _case
    }
}

template <typename T>
std::size_t dia_hash_build(T const& value) {
    std::size_t result = 0;
    hstd::for_each_field_with_bases<T>([&](auto const& field) {
        using FieldType = DESC_FIELD_TYPE(field);
        if constexpr (std::is_same_v<org::imm::ImmAdapter, FieldType>) {
            hstd::hax_hash_combine(result, (value.*field.pointer).uniq());
        } else {
            auto hash_value = std::hash<
                std::remove_cvref_t<decltype(value.*field.pointer)>>{}(
                value.*field.pointer);
            auto tmp_result = result;
            hstd::hax_hash_combine(result, hash_value);
        }
    });

    return result;
}


template <>
struct std::hash<DiaNodeLayer> {
    std::size_t operator()(DiaNodeLayer const& it) const noexcept {
        return dia_hash_build(it);
    }
};

template <>
struct std::hash<DiaNodeCanvas> {
    std::size_t operator()(DiaNodeCanvas const& it) const noexcept {
        return dia_hash_build(it);
    }
};

template <>
struct std::hash<DiaNodeGroup> {
    std::size_t operator()(DiaNodeGroup const& it) const noexcept {
        return dia_hash_build(it);
    }
};

template <>
struct std::hash<DiaNodeItem> {
    std::size_t operator()(DiaNodeItem const& it) const noexcept {
        return dia_hash_build(it);
    }
};

template <>
struct std::hash<DiaNode> {
    std::size_t operator()(DiaNode const& it) const noexcept {
        return dia_hash_build(it);
    }
};

template <typename T>
struct DiaNodeKindStore {
    using NodeType = T;
    hstd::dod::InternStore<DiaId, T> values;
    DESC_FIELDS(DiaNodeKindStore, (values));

    int size() const { return values.size(); }

    DiaNodeKindStore() {}
    void format(hstd::ColStream& os, std::string const& linePrefix = "")
        const;

    bool     empty() const { return values.empty(); }
    T const* at(DiaId id) const { return &values.at(id); }

    DiaId add(T const& value) {
        auto  mask   = DiaId::combineMask(T::staticKind);
        DiaId result = values.add(value, mask);
    }
};

struct DiaNodeStore {
    template <typename T>
    DiaNodeKindStore<T> const* getStoreImpl() const;

    template <typename T>
    DiaNodeKindStore<T> const* getStore() const {
        return getStoreImpl<T>();
    }

    template <typename T>
    DiaNodeKindStore<T>* getStore() {
        return const_cast<DiaNodeKindStore<T>*>(getStoreImpl<T>());
    }

#define _kind(__Kind) DiaNodeKindStore<DiaNode##__Kind> store##__Kind;
    EACH_DIAGRAM_KIND(_kind)
#undef _kind


    DiaNodeStore()
        :
#define _kind(__Kind) , store##__Kind()
        EACH_DIAGRAM_KIND_CSV(_kind)
#undef _kind
    {
    }

    template <org::imm::IsImmOrgValueType T>
    DiaId add(T const& value) {
        return getStore<T>()->add(value);
    }

    DiaNode const* at(DiaId const& id) const {
        DiaNode const* res;
        switch_dia_id(id, [&]<typename K>(DiaIdT<K> id) {
            res = getStore<K>()->at(id);
            LOGIC_ASSERTION_CHECK(
                res->getKind() == id.getKind(),
                "id kind {} does not match result node kind {}",
                id.getKind(),
                res->getKind());
        });

        return res;
    }
};


struct DiaContext : hstd::SharedPtrApi<DiaContext> {
    std::shared_ptr<DiaNodeStore> store;

    DESC_FIELDS(DiaContext, (store));

    DiaNode const* at(DiaId const& id) const { return store->at(id); }
    DiaNode const* at(DiaUniqId const& id) const { return at(id.id); }

    template <typename T>
    DiaId add(T const& t) {
        return store->add(t);
    }

    template <typename T>
    T const& value(DiaId id) const {
        LOGIC_ASSERTION_CHECK(!id.isNil(), "cannot get value for nil ID");
        return *at_t<T>(id);
    }

    template <typename T>
    T const* at_t(DiaId id) const {
        return at(id)->template as<T>();
    }


    DiaId at(DiaId node, const DiaPathStep& item) const {
        node.assertValid();
        if (item.path.isSingle() && item.path.first().isIndex()) {
            return value<DiaNode>(node).subnodes.at(
                item.path.first().getIndex().index);
        } else {
            hstd::Opt<DiaId> result;
            switch_dia_ptr(at(node), [&]<typename T>(T const* ptr) {
                hstd::logic_assertion_check_not_nil(ptr);
                reflVisitPath<T>(
                    *ptr,
                    item.path,
                    hstd::overloaded{
                        [&](DiaId const& id) { result = id; },
                        [&]<typename K>(DiaIdT<K> const& id) {
                            result = id.toId();
                        },
                        [&](auto const& other) {
                            LOGIC_ASSERTION_CHECK(
                                false,
                                "Path {} does not point to a field "
                                "with ID, resolved to {}",
                                hstd::fmt1_maybe(item),
                                hstd::fmt1_maybe(other));
                        },
                    });
            });
            return result.value();
        }
    }

    DiaId at(const DiaPath& item) const {
        auto result = item.root;
        for (auto const& step : item.path) { result = at(result, step); }
        return result;
    }
};

struct DiaAdapter {
    DiaUniqId                   id;
    std::shared_ptr<DiaContext> ctx;

    int            size() const { return ctx->at(id)->subnodes.size(); }
    DiaNode const* get() const { return ctx->at(id); }

    DiaAdapter at(DiaId const& at_id, DiaPathStep const& step) const {
        return DiaAdapter{DiaUniqId{at_id, id.path.add(step)}, ctx};
    }

    DiaAdapter(DiaPath const& path, DiaContext::Ptr ctx)
        : id{ctx->at(path)}, ctx{ctx} {}

    DiaAdapter(DiaUniqId id, DiaContext::Ptr ctx) : id{id}, ctx{ctx} {}

    DiaAdapter(DiaId id, DiaContext::Ptr ctx, DiaPath const& path)
        : id{id}, ctx{ctx} {}

    DiaAdapter(DiaAdapter const& other) : id{other.id}, ctx{other.ctx} {}

    DiaAdapter() : id{DiaId::Nil()}, ctx{} {}

    DiaAdapter at(int idx, bool withPath) const {
        if (withPath) {
            return at(
                ctx->at(id)->subnodes.at(idx),
                DiaPathStep::FieldIdx(
                    DiaReflFieldId::FromTypeField<DiaNode>(
                        &DiaNode::subnodes),
                    idx));
        } else {
            return DiaAdapter{ctx->at(id)->subnodes.at(idx), ctx, {}};
        }
    }
};

DiaId FromDocument(
    hstd::SPtr<DiaContext> const&                       context,
    org::imm::ImmAdapterT<org::imm::ImmDocument> const& root);
