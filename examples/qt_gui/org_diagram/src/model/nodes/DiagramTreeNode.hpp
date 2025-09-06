#pragma once

#include "src/utils/common.hpp"
#include <hstd/stdlib/Vec.hpp>
#include <QObject>
#include <haxorg/sem/ImmOrg.hpp>
#include <src/model/HistoryManager.hpp>

#define _cat "model.diagram"

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


using DiaUniqId = DiaId;

struct DiaNode {
    virtual DiaNodeKind      getKind() const = 0;
    hstd::ext::ImmVec<DiaId> subnodes;
    org::imm::ImmAdapter     id;
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
        if (std::is_same_v<org::imm::ImmAdapter, FieldType>
            && field.name == "id") {
            hstd::hax_hash_combine(value.*field.pointer.uniq());
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


struct DiaContext {
    std::shared_ptr<DiaNodeStore> store;

    DESC_FIELDS(DiaContext, (store));

    DiaNode const* at(DiaId const& id) const { return store->at(id); }

    template <typename T>
    DiaId add(T const& t) {
        return store->add(t);
    }
};

struct DiaAdapter {
    DiaUniqId                   id;
    std::shared_ptr<DiaContext> context;

    int size() const { return context->at(id)->subnodes.size(); }
    DiaNode const* get() const { return context->at(id); }
};

DiaId FromDocument(
    hstd::SPtr<DiaContext> const&                       context,
    org::imm::ImmAdapterT<org::imm::ImmDocument> const& root);
