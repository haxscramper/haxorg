#include "hstd/stdlib/Set.hpp"
#include <haxorg/sem/ImmOrg.hpp>
#include <hstd/stdlib/Exception.hpp>
#include <immer/vector_transient.hpp>
#include <immer/map_transient.hpp>
#include <hstd/stdlib/Enumerate.hpp>
#include <boost/mp11.hpp>
#include <boost/preprocessor.hpp>
#include <haxorg/sem/ImmOrgHash.hpp>

const u64 org::ImmId::NodeIdxMask    = 0x000000FFFFFFFFFF; // >>0*0=0,
const u64 org::ImmId::NodeIdxOffset  = 0;
const u64 org::ImmId::NodeKindMask   = 0x000FFF0000000000; // >>10*4=40
const u64 org::ImmId::NodeKindOffset = 40;

org::ImmId::IdType org::ImmId::combineMask(OrgSemKind kind) {
    auto res = (u64(kind) << NodeKindOffset) & NodeKindMask;

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
    OrgSemKind kind,
    NodeIdxT   node) {
    return (combineMask(kind) << ImmIdMaskOffset)
         | (u64(node) << NodeIdxOffset) & NodeIdxMask;
}


std::string org::ImmId::getReadableId() const {
    if (isNil()) {
        return "nil";
    } else {
        try {
            return std::format("{}_{}", getKind(), getNodeIndex());
        } catch (std::domain_error const& err) {
            return std::format(
                "ERR {} MASK:{:016b} IDX:{:032b}",
                err.what(),
                static_cast<u64>(getKind()),
                static_cast<u64>(getNodeIndex()));
        }
    }
}

void org::ImmId::assertValid() const {
    u64 kind     = static_cast<u64>(getKind());
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


using namespace org;


const ImmOrg* ImmAstStore::at(ImmId index) const {
    switch (index.getKind()) {

#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: {                                            \
        org::Imm##__Kind const* res = store##__Kind.at(index);            \
        logic_assertion_check(                                            \
            res->getKind() == index.getKind(),                            \
            "index kind {} does not match result node kind {}",           \
            index.getKind(),                                              \
            res->getKind());                                              \
        return res;                                                       \
    }
        EACH_SEM_ORG_KIND(_case)
#undef _case
    }

    throw logic_unreachable_error::init(
        fmt("Cannot get node for index {}", index));
}

namespace {
void eachSubnodeRecImpl(
    CR<org::SubnodeVisitor> visitor,
    ImmId                   org,
    bool                    originalBase,
    org::ImmAstContext*     ctx);

template <typename T>
struct Visitor {};


#define placeholder_visitor(__Type)                                       \
    template <>                                                           \
    struct Visitor<__Type> {                                              \
        static void visitField(                                           \
            CR<org::SubnodeVisitor> visitor,                              \
            __Type const&           tmp,                                  \
            org::ImmAstContext*     ctx) {}                                   \
    };

placeholder_visitor(Str);
placeholder_visitor(int);
placeholder_visitor(bool);
placeholder_visitor(absl::Time);
placeholder_visitor(UserTime);
placeholder_visitor(std::string);
placeholder_visitor(sem::BigIdent);
placeholder_visitor(org::ImmIdT<sem::BigIdent>);
placeholder_visitor(Vec<sem::SemId<sem::Org>>);

#undef placeholder_visitor


template <IsEnum T>
struct Visitor<T> {
    static void visitField(
        CR<org::SubnodeVisitor> visitor,
        T const&                tree,
        org::ImmAstContext*     ctx) {}
};

template <typename T>
struct Visitor<ImmIdT<T>> {
    static void visitField(
        CR<org::SubnodeVisitor> visitor,
        ImmIdT<T>               tree,
        org::ImmAstContext*     ctx) {

        if (tree.isNil()) { return; }
        visitor(ImmAdapter{tree.toId(), ctx});

        for_each_field_with_bases<T>([&](auto const& field) {
            Visitor<std::remove_cvref_t<
                decltype(ctx->at(tree)->*field.pointer)>>::
                visitField(visitor, ctx->at(tree)->*field.pointer, ctx);
        });
    }
};

template <DescribedRecord T>
struct Visitor<T> {
    static void visitField(
        CR<org::SubnodeVisitor> visitor,
        T const&                obj,
        org::ImmAstContext*     ctx) {
        for_each_field_with_bases<T>([&](auto const& field) {
            Visitor<std::remove_cvref_t<decltype(obj.*field.pointer)>>::
                visitField(visitor, obj.*field.pointer, ctx);
        });
    }
};


template <>
struct Visitor<ImmId> {
    static void visitField(
        CR<org::SubnodeVisitor> visitor,
        ImmId                   org,
        org::ImmAstContext*     ctx) {
        switch (ctx->at(org)->getKind()) {


#define __case(__Kind)                                                    \
    case OrgSemKind::__Kind: {                                            \
        Visitor<org::ImmIdT<org::Imm##__Kind>>::visitField(               \
            visitor, org.as<org::Imm##__Kind>(), ctx);                    \
        break;                                                            \
    }
            EACH_SEM_ORG_KIND(__case)
#undef __case
        }
    }
};


template <sem::IsOrg T>
struct Visitor<T> {
    static void visitField(
        CR<org::SubnodeVisitor> visitor,
        CR<T>                   node,
        org::ImmAstContext*     ctx) {
        Visitor<ImmId>::visitField(visitor, node.asOrg(), ctx);
    }
};

template <IsVariant T>
struct Visitor<T> {
    static void visitField(
        CR<org::SubnodeVisitor> visitor,
        CR<T>                   node,
        org::ImmAstContext*     ctx) {
        std::visit(
            [&](auto const& it) {
                Visitor<std::remove_cvref_t<decltype(it)>>::visitField(
                    visitor, it, ctx);
            },
            node);
    }
};


template <typename T>
struct Visitor<ImmVec<T>> {
    static void visitField(
        CR<org::SubnodeVisitor> visitor,
        ImmVec<T> const&        value,
        org::ImmAstContext*     ctx) {
        for (const auto& it : value) {
            Visitor<T>::visitField(visitor, it, ctx);
        }
    }
};

template <typename K, typename V>
struct Visitor<ImmMap<K, V>> {
    static void visitField(
        CR<org::SubnodeVisitor> visitor,
        ImmMap<K, V> const&     value,
        org::ImmAstContext*     ctx) {
        for (const auto& [key, value] : value) {
            Visitor<V>::visitField(visitor, value, ctx);
        }
    }
};


template <typename T>
struct Visitor<ImmBox<T>> {
    static void visitField(
        CR<org::SubnodeVisitor> visitor,
        CR<ImmBox<T>>           value,
        org::ImmAstContext*     ctx) {
        Visitor<T>::visitField(visitor, value.get(), ctx);
    }
};

template <typename T>
struct Visitor<Opt<T>> {
    static void visitField(
        CR<org::SubnodeVisitor> visitor,
        CR<Opt<T>>              value,
        org::ImmAstContext*     ctx) {
        if (value) { Visitor<T>::visitField(visitor, *value, ctx); }
    }
};

} // namespace


void org::eachSubnodeRec(ImmAdapter id, SubnodeVisitor cb) {
    Visitor<ImmId>::visitField(cb, id.id, id.ctx);
}


namespace {
struct ImmTreeReprContext {
    int                           level;
    Vec<int>                      path;
    org::ImmAdapter::TreeReprConf conf;
    ImmAstContext*                ctx;

    ImmTreeReprContext addPath(int diff) const {
        ImmTreeReprContext result = *this;
        result.path.push_back(diff);
        return result;
    }

    ImmTreeReprContext addLevel(int diff) const {
        ImmTreeReprContext result = *this;
        result.level += diff;
        return result;
    }
};

template <typename T>
struct ImmTreeReprVisitor {};


template <typename T>
struct ImmTreeReprVisitor<org::ImmAdapterT<T>> {
    static void visit(
        org::ImmAdapterT<T>       id,
        ColStream&                os,
        ImmTreeReprContext const& ctx);
};

#define IMM_TREE_REPR_IMPL(__TemplateArgs, __VisitorTypeSpecification)    \
    DEFINE_VISITOR_BASE_ALL(                                              \
        /*Typename=*/ImmTreeReprVisitor,                                  \
        /*TemplateArgs=*/__TemplateArgs,                                  \
        /*SharedArgs=*/(ColStream & os, ImmTreeReprContext const& ctx),   \
        /*TypeSpecification=*/__VisitorTypeSpecification,                 \
        /*ResultType=*/(void),                                            \
        /*MethodName=*/visit)

IMM_TREE_REPR_IMPL((typename T), (ImmBox<T>)) {
    ImmTreeReprVisitor<T>::visit(arg.get(), os, ctx);
}

IMM_TREE_REPR_IMPL((typename T), (Opt<T>)) {
    if (arg) { ImmTreeReprVisitor<T>::visit(arg.value(), os, ctx); }
}

IMM_TREE_REPR_IMPL((typename T), (ImmVec<T>)) {
    int subIdx = 0;
    for (auto const& sub : arg) {
        os << "\n";
        ImmTreeReprVisitor<T>::visit(sub, os, ctx.addLevel(1));
    }
}

IMM_TREE_REPR_IMPL((), (org::ImmAdapter)) {
    switch (arg->getKind()) {
#define __case(__Kind)                                                    \
    case OrgSemKind::__Kind: {                                            \
        auto id_t = arg.as<org::Imm##__Kind>();                           \
        ImmTreeReprVisitor<org::ImmAdapterT<org::Imm##__Kind>>::visit(    \
            id_t, os, ctx);                                               \
        break;                                                            \
    }
        EACH_SEM_ORG_KIND(__case)
#undef __case
        default: {
            os.indent(ctx.level * 2);
            os << fmt(
                "ERR Invalid kind value {0:064b} {0:064X}",
                arg.id.getValue());
        }
    }
}

IMM_TREE_REPR_IMPL((), (Vec<sem::SemId<sem::Org>>)) {}
IMM_TREE_REPR_IMPL((typename T), (ImmMap<Str, T>)) {}
IMM_TREE_REPR_IMPL((), (absl::Time)) {}
IMM_TREE_REPR_IMPL((), (absl::TimeZone)) {}

IMM_TREE_REPR_IMPL((), (std::string)) {
    os << os.indent(ctx.level * 2) << fmt(" {}", escape_literal(arg));
}

IMM_TREE_REPR_IMPL((), (Str)) {
    os << os.indent(ctx.level * 2) << fmt(" {}", escape_literal(arg));
}

IMM_TREE_REPR_IMPL((), (bool)) {
    os << os.indent(ctx.level * 2) << fmt(" {}", arg);
}

IMM_TREE_REPR_IMPL((), (int)) {
    os << os.indent(ctx.level * 2) << fmt(" {}", arg);
}

IMM_TREE_REPR_IMPL((IsEnum E), (E)) {}

IMM_TREE_REPR_IMPL((DescribedRecord R), (R)) {
    for_each_field_with_bases<R>([&](auto const& f) {
        using F = DESC_FIELD_TYPE(f);
        ImmTreeReprVisitor<F>::visit(arg.*f.pointer, os, ctx);
    });
}

IMM_TREE_REPR_IMPL((IsVariant T), (T)) {
    std::visit(
        [&]<typename V>(V const& var) {
            ImmTreeReprVisitor<V>::visit(var, os, ctx);
        },
        arg);
}


IMM_TREE_REPR_IMPL((), (org::ImmId)) {
    ImmTreeReprVisitor<org::ImmAdapter>::visit(
        org::ImmAdapter{arg, ctx.ctx}, os, ctx);
}


IMM_TREE_REPR_IMPL((typename T), (org::ImmIdT<T>)) {
    ImmTreeReprVisitor<org::ImmAdapterT<T>>::visit(
        org::ImmAdapter{arg, ctx.ctx}.as<T>(), os, ctx);
}

template <typename T>
void ImmTreeReprVisitor<org::ImmAdapterT<T>>::visit(
    org::ImmAdapterT<T>       id,
    ColStream&                os,
    ImmTreeReprContext const& ctx) {
    os.indent(ctx.level * 2);
    os << fmt(
        "{} {} PATH:{}", id->getKind(), id.id.getReadableId(), ctx.path);

    for_each_field_with_bases<T>([&](auto const& f) {
        auto const& fieldValue = id.get()->*f.pointer;
        using FieldType        = std::remove_cvref_t<decltype(fieldValue)>;
        auto subctx            = ctx.addLevel(1);
        if (f.name == "subnodes"_ss) {
            if constexpr (std::is_same_v<ImmVec<org::ImmId>, FieldType>) {
                for (int i = 0; i < fieldValue.size(); ++i) {
                    os << "\n";
                    ImmTreeReprVisitor<typename FieldType::value_type>::
                        visit(fieldValue.at(i), os, subctx.addPath(i));
                }
            } else {
                throw logic_unreachable_error::init(
                    "subnodes field is a vector of imm ID");
            }
        } else if (ctx.conf.withAuxFields) {
            os << "\n";
            os.indent((ctx.level + 1) * 2);
            os << f.name;
            os << "\n";
            ImmTreeReprVisitor<FieldType>::visit(
                fieldValue, os, subctx.addLevel(1));
        }
    });
}


} // namespace

void ImmAdapter::treeRepr(ColStream& os, const TreeReprConf& conf) const {
    ImmTreeReprVisitor<org::ImmAdapter>::visit(
        *this,
        os,
        ImmTreeReprContext{
            .conf  = conf,
            .level = 0,
            .ctx   = this->ctx,
        });
}

ImmAstParentMap ImmAstParentMapTransient::persistent() {
    return ImmAstParentMap{.parents = parents.persistent()};
}

ImmAstContext ImmAstEditContext::finish() {
    return ctx->finishEdit(*this);
}

Graphviz::Graph org::toGraphviz(
    const Vec<ImmAstVersion>& history,
    ImmAstGraphvizConf const& conf) {
    Graphviz::Graph                     g{"g"_ss};
    UnorderedSet<ImmId>                 visited;
    UnorderedMap<ImmId, Graphviz::Node> gvNodes;

    auto get_node = [&](ImmId id, int idx) -> Opt<Graphviz::Node> {
        if (conf.skippedKinds.contains(id.getKind())) {
            return std::nullopt;
        } else {
            if (!gvNodes.contains(id)) {
                auto node = g.node(id.getReadableId());
                node.setColor(conf.epochColors.at(idx));
                node.setShape(Graphviz::Node::Shape::rectangle);
                gvNodes.insert_or_assign(id, node);
            }

            return gvNodes.at(id);
        }
    };

    ImmAstContext ctx = history.front().context;

    Func<void(ImmId, int)> aux;
    aux = [&](ImmId id, int idx) {
        auto node = get_node(id, idx);
        if (node) {
            auto subnodes = allSubnodes(id, ctx);
            for (auto const& it : enumerator(subnodes)) {
                it.value().assertValid();
                aux(it.value(), idx);
                auto sub_imm = get_node(it.value(), idx);
                if (sub_imm) {
                    auto edge = g.edge(*node, *sub_imm);
                    edge.setColor(conf.epochColors.at(idx));
                    edge.setLabel(fmt1(it.index()));
                }
            }
        }
    };

    for (auto const& [idx, epoch] : enumerate(history)) {
        aux(epoch.epoch.getRoot(), idx);
    }

    return g;
}


template <typename T>
struct ImmSubnodeCollectionVisitor {};

#define IMM_SUBNODE_COLLECTOR(__TemplateArgs, __VisitorTypeSpecification) \
    DEFINE_VISITOR_BASE_ALL(                                              \
        /*Typename=*/ImmSubnodeCollectionVisitor,                         \
        /*TemplateArgs=*/__TemplateArgs,                                  \
        /*SharedArgs=*/(org::ImmAstContext const& ctx),                   \
        /*TypeSpecification=*/__VisitorTypeSpecification,                 \
        /*ResultType=*/(Vec<ImmId>),                                      \
        /*MethodName=*/getSubnodes)

IMM_SUBNODE_COLLECTOR((typename T), (ImmIdT<T>)) {
    arg.toId().assertValid();
    return Vec<ImmId>{arg.toId()};
}

IMM_SUBNODE_COLLECTOR((), (ImmId)) {
    arg.assertValid();
    return Vec<ImmId>{arg};
}
IMM_SUBNODE_COLLECTOR((), (Str)) { return {}; }
IMM_SUBNODE_COLLECTOR((), (bool)) { return {}; }
IMM_SUBNODE_COLLECTOR((), (int)) { return {}; }
IMM_SUBNODE_COLLECTOR((IsEnum E), (E)) { return {}; }
IMM_SUBNODE_COLLECTOR((DescribedRecord R), (R)) { return {}; }
IMM_SUBNODE_COLLECTOR((typename K, typename V), (ImmMap<K, V>)) {
    Vec<ImmId> result;
    for (auto const& [key, value] : arg) {
        result.append(
            ImmSubnodeCollectionVisitor<V>::getSubnodes(value, ctx));
    }
    return result;
}

IMM_SUBNODE_COLLECTOR((typename T), (ImmVec<T>)) {
    Vec<ImmId> result{};
    for (auto const& it : arg) {
        result.append(
            ImmSubnodeCollectionVisitor<T>::getSubnodes(it, ctx));
    }
    return result;
}


IMM_SUBNODE_COLLECTOR((IsVariant T), (T)) {
    return std::visit(
        [&]<typename VarT>(VarT const& it) {
            return ImmSubnodeCollectionVisitor<VarT>::getSubnodes(it, ctx);
        },
        arg);
}


IMM_SUBNODE_COLLECTOR((typename T), (ImmBox<T>)) {
    if (arg.impl() == nullptr) {
        return {};
    } else {
        return ImmSubnodeCollectionVisitor<T>::getSubnodes(arg.get(), ctx);
    }
}

IMM_SUBNODE_COLLECTOR((typename T), (Opt<T>)) {
    if (arg) {
        return ImmSubnodeCollectionVisitor<T>::getSubnodes(
            arg.value(), ctx);
    } else {
        return {};
    }
}

template <org::IsImmOrgValueType T>
Vec<ImmId> org::allSubnodes(
    T const&                  value,
    org::ImmAstContext const& ctx) {
    Vec<ImmId> subnodes;
    for_each_field_with_bases<T>([&](auto const& f) {
        using FieldType = DESC_FIELD_TYPE(f);
        auto tmp = ImmSubnodeCollectionVisitor<FieldType>::getSubnodes(
            value.*f.pointer, ctx);
        for (auto const& it : tmp) { it.assertValid(); }
        subnodes.append(tmp);
    });
    return subnodes;
}


Vec<ImmId> org::allSubnodes(const ImmId& value, const ImmAstContext& ctx) {
    value.assertValid();
    switch (value.getKind()) {
#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: {                                            \
        return allSubnodes(ctx.value<org::Imm##__Kind>(value), ctx);      \
    }
        EACH_SEM_ORG_KIND(_case)
    }

#undef _case
}
