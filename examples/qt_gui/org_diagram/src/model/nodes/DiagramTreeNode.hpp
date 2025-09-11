#pragma once

#include "src/utils/common.hpp"
#include <hstd/stdlib/Vec.hpp>
#include <QObject>
#include <haxorg/sem/ImmOrg.hpp>
#include <src/model/HistoryManager.hpp>
#include <hstd/ext/graphviz.hpp>

#define _cat "model.diagram"

#pragma clang diagnostic ignored "-Wdeprecated-declarations"

template <typename Tag>
struct hstd::ReflVisitor<unsigned long long, Tag>
    : hstd::ReflVisitorLeafType<unsigned long long, Tag> {};


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

template <>
struct std::formatter<org::imm::ImmReflPathItemBase::Index>
    : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(
        const org::imm::ImmReflPathItemBase::Index& p,
        FormatContext&                              ctx) const {
        return hstd::fmt_ctx(hstd::fmt("[{}]", p.index), ctx);
    }
};

template <>
struct std::formatter<org::imm::ImmReflPathItemBase::FieldName>
    : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(
        const org::imm::ImmReflPathItemBase::FieldName& p,
        FormatContext&                                  ctx) const {
        return hstd::fmt_ctx(hstd::fmt(".{}", p.name.getName()), ctx);
    }
};

template <>
struct std::formatter<org::imm::ImmReflPathItemBase::Deref>
    : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(
        const org::imm::ImmReflPathItemBase::Deref& p,
        FormatContext&                              ctx) const {
        return hstd::fmt_ctx(hstd::fmt("*"), ctx);
    }
};


struct [[refl]] DiaId : DiaIdBase {
    BOOST_DESCRIBE_CLASS(DiaId, (DiaIdBase), (), (), ());
    using IdType   = hstd::u64;
    using NodeIdxT = hstd::u32;


    inline static const hstd::u64 NodeIdxMask = 0x000000FFFFFFFFFF; // >>0*0=0,
    inline static const hstd::u64 NodeIdxOffset = 0;
    inline static const hstd::u64 NodeKindMask = 0x000FFF0000000000; // >>10*4=40
    inline static const hstd::u64 NodeKindOffset = 40;

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

struct [[refl]] DiaUniqId {
    DiaId             id;
    org::imm::ImmPath path;
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

    bool operator==(DiaNode const& other) const {
        return id.id == other.id.id;
    }

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


    DESC_FIELDS(DiaNode, (subnodes));
};

struct DiaNodeLayer : DiaNode {
    bool operator==(DiaNodeLayer const& other) const {
        return DiaNode::operator==(other);
    }
    inline static const DiaNodeKind staticKind = DiaNodeKind::Layer;
    DiaNodeKind getKind() const override { return staticKind; }
    BOOST_DESCRIBE_CLASS(DiaNodeLayer, (DiaNode), (), (), ());
};

struct DiaNodeCanvas : DiaNode {
    bool operator==(DiaNodeCanvas const& other) const {
        return DiaNode::operator==(other);
    }
    inline static const DiaNodeKind staticKind = DiaNodeKind::Canvas;
    DiaNodeKind getKind() const override { return staticKind; }
    BOOST_DESCRIBE_CLASS(DiaNodeCanvas, (DiaNode), (), (), ());
};

struct DiaNodeGroup : DiaNode {
    bool operator==(DiaNodeGroup const& other) const {
        return DiaNode::operator==(other);
    }
    inline static const DiaNodeKind staticKind = DiaNodeKind::Group;
    DiaNodeKind getKind() const override { return staticKind; }
    BOOST_DESCRIBE_CLASS(DiaNodeGroup, (DiaNode), (), (), ());
};

struct DiaNodeItem : DiaNode {
    bool operator==(DiaNodeItem const& other) const {
        return DiaNode::operator==(other);
    }

    inline static const DiaNodeKind staticKind = DiaNodeKind::Item;

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
    hstd::hax_hash_combine(result, value.id.id);
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
        auto mask = DiaId::combineMask(T::staticKind);
        return values.add(value, mask);
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

    template <typename T>
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

    DiaContext() { store = std::make_shared<DiaNodeStore>(); }

    template <typename T>
    DiaId add(T const& t) {
        hstd::logic_assertion_check_not_nil(store);
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


    DiaId at(DiaId node, const org::imm::ImmPathStep& item) const {
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

    DiaId at(const org::imm::ImmPath& item) const {
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

    template <typename T>
    T const* as() const {
        return get()->dyn_cast<T>();
    }

    DiaAdapter at(DiaId const& at_id, org::imm::ImmPathStep const& step)
        const {
        return DiaAdapter{DiaUniqId{at_id, id.path.add(step)}, ctx};
    }

    static DiaAdapter Root(DiaId const& id, DiaContext::Ptr const& ctx) {
        return DiaAdapter{
            DiaUniqId{id, org::imm::ImmPath{ctx->at(id)->id.id}}, ctx};
    }

    struct TreeReprConf {
        DESC_FIELDS(TreeReprConf, ());
    };

    hstd::Vec<DiaAdapter> sub(bool withPath) const {
        hstd::Vec<DiaAdapter> result;
        for (int i = 0; i < size(); ++i) {
            result.push_back(at(i, withPath));
        }
        return result;
    }

    hstd::ColText format(TreeReprConf const& conf) const;
    hstd::ColText format() const { return format(TreeReprConf{}); }

    DiaNodeKind getKind() const { return get()->getKind(); }

    DiaAdapter(org::imm::ImmPath const& path, DiaContext::Ptr ctx)
        : id{ctx->at(path)}, ctx{ctx} {}

    DiaAdapter(DiaUniqId id, DiaContext::Ptr ctx) : id{id}, ctx{ctx} {}

    DiaAdapter(
        DiaId                    id,
        DiaContext::Ptr          ctx,
        org::imm::ImmPath const& path)
        : id{id}, ctx{ctx} {}

    DiaAdapter(DiaAdapter const& other) : id{other.id}, ctx{other.ctx} {}

    DiaAdapter() : id{DiaId::Nil()}, ctx{} {}

    DiaAdapter at(int idx, bool withPath) const {
        if (withPath) {
            return at(
                ctx->at(id)->subnodes.at(idx),
                org::imm::ImmPathStep::FieldIdx(
                    org::imm::ImmReflFieldId::FromTypeField<DiaNode>(
                        &DiaNode::subnodes),
                    idx));
        } else {
            return DiaAdapter{ctx->at(id)->subnodes.at(idx), ctx, {}};
        }
    }
};

template <>
struct std::formatter<DiaUniqId> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const DiaUniqId& p, FormatContext& ctx) const {
        return hstd::fmt_ctx(hstd::fmt("{}{}", p.id, p.path), ctx);
    }
};

template <>
struct std::formatter<DiaAdapter> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const DiaAdapter& p, FormatContext& ctx) const {
        return hstd::fmt_ctx(
            hstd::fmt("{}({} {})", p.getKind(), p.id.id, p.id.path), ctx);
    }
};

DiaAdapter FromDocument(
    hstd::SPtr<DiaContext> const&                       context,
    org::imm::ImmAdapterT<org::imm::ImmDocument> const& root);

struct DiaEdit {
    struct Insert {
        DiaAdapter dstNode;
        int        dstIndex;
        DESC_FIELDS(Insert, (dstNode, dstIndex));
    };

    struct Delete {
        DiaAdapter srcNode;
        int        srcIndex;
        DESC_FIELDS(Delete, (srcNode, srcIndex));
    };

    struct Move {
        DiaAdapter srcNode;
        DiaAdapter dstNode;
        int        srcIndex;
        int        dstIndex;
        DESC_FIELDS(Move, (srcNode, dstNode, srcIndex, dstIndex));
    };

    struct Update {
        DiaAdapter srcNode;
        DiaAdapter dstNode;
        int        srcIndex;
        int        dstIndex;
        DESC_FIELDS(Update, (srcNode, dstNode, srcIndex, dstIndex));
    };

    bool hasSrc() const { return isDelete() || isMove() || isUpdate(); }
    bool hasDst() const { return isInsert() || isMove() || isUpdate(); }

    DiaAdapter getDstAffected() const {
        if (isInsert()) {
            return getInsert().dstNode;
        } else if (isMove()) {
            return getMove().dstNode;
        } else if (isUpdate()) {
            return getUpdate().dstNode;
        } else {
            throw hstd::logic_assertion_error::init(
                "delete node has no source counterpart");
        }
    }

    DiaAdapter getSrcAffected() const {
        if (isDelete()) {
            return getDelete().srcNode;
        } else if (isMove()) {
            return getMove().srcNode;
        } else if (isUpdate()) {
            return getUpdate().srcNode;
        } else {
            throw hstd::logic_assertion_error::init(
                "insert node has no source counterpart");
        }
    }


    SUB_VARIANTS(Kind, Data, data, getKind, Delete, Insert, Update, Move);
    Data data;
    DESC_FIELDS(DiaEdit, (data));
};

struct DiaEditConf {
    DESC_FIELDS(DiaEditConf, ());
};

std::vector<DiaEdit> getEdits(
    DiaAdapter const&  srcRoot,
    DiaAdapter const&  dstRoot,
    DiaEditConf const& confi);

struct DiaEditMappingGraphvizConf {};

hstd::ext::Graphviz::Graph getEditMappingGraphviz(
    DiaAdapter const&           src,
    DiaAdapter const&           dst,
    std::vector<DiaEdit> const& edits);
