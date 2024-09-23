#include "hstd/stdlib/Set.hpp"
#include <haxorg/sem/ImmOrg.hpp>
#include <hstd/stdlib/Exception.hpp>
#include <immer/vector_transient.hpp>
#include <immer/flex_vector_transient.hpp>
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

    LOGIC_ASSERTION_CHECK(
        kindLow <= kind && kind <= kindHigh,
        "ID kind value out of range: ID int value is: {} (bin: {:032b}, "
        "hex: {:032X}), low {} high {}",
        kind,
        kind,
        kind,
        kindLow,
        kindHigh);

    if (!isNil()) {
        LOGIC_ASSERTION_CHECK(
            getKind() != OrgSemKind::None,
            "Valid ID must have a kind different from 'None'");
    }
}

#define _define_static(__Kind)                                            \
    const OrgSemKind org::Imm##__Kind::staticKind = OrgSemKind::__Kind;

EACH_SEM_ORG_KIND(_define_static)
#undef _define_static


using namespace org;


const ImmOrg* ImmAstStore::at(ImmId index) const {
    ImmOrg const* res;
    switch_node_kind(index, [&]<typename K>(org::ImmIdT<K> id) {
        res = getStore<K>()->at(index);
        LOGIC_ASSERTION_CHECK(
            res->getKind() == index.getKind(),
            "index kind {} does not match result node kind {}",
            index.getKind(),
            res->getKind());
    });
    return res;
}


namespace {
void eachSubnodeRecImpl(
    CR<org::SubnodeVisitor>   visitor,
    ImmId                     org,
    bool                      originalBase,
    org::ImmAstContext const& ctx);

template <typename T>
struct SubnodeRecVisitor {};


#define placeholder_visitor(__Type)                                       \
    template <>                                                           \
    struct SubnodeRecVisitor<__Type> {                                    \
        static void visitField(                                           \
            CR<org::SubnodeVisitor>   visitor,                            \
            __Type const&             tmp,                                \
            org::ImmAstContext const& ctx) {}                             \
    };

placeholder_visitor(Str);
placeholder_visitor(int);
placeholder_visitor(bool);
placeholder_visitor(absl::Time);
placeholder_visitor(UserTime);
placeholder_visitor(std::string);
placeholder_visitor(sem::BigIdent);
placeholder_visitor(org::ImmIdT<sem::BigIdent>);
placeholder_visitor(sem::CmdArgumentValue);
placeholder_visitor(Vec<sem::SemId<sem::Org>>);

#undef placeholder_visitor


template <IsEnum T>
struct SubnodeRecVisitor<T> {
    static void visitField(
        CR<org::SubnodeVisitor>   visitor,
        T const&                  tree,
        org::ImmAstContext const& ctx) {}
};

template <typename T>
struct SubnodeRecVisitor<ImmIdT<T>> {
    static void visitField(
        CR<org::SubnodeVisitor>   visitor,
        ImmIdT<T>                 tree,
        org::ImmAstContext const& ctx) {

        if (tree.isNil()) { return; }
        visitor(ImmAdapter{tree.toId(), ctx, org::ImmPath{tree.toId()}});

        for_each_field_with_bases<T>([&](auto const& field) {
            SubnodeRecVisitor<std::remove_cvref_t<
                decltype(ctx.at(tree)->*field.pointer)>>::
                visitField(visitor, ctx.at(tree)->*field.pointer, ctx);
        });
    }
};

template <DescribedRecord T>
struct SubnodeRecVisitor<T> {
    static void visitField(
        CR<org::SubnodeVisitor>   visitor,
        T const&                  obj,
        org::ImmAstContext const& ctx) {
        for_each_field_with_bases<T>([&](auto const& field) {
            SubnodeRecVisitor<
                std::remove_cvref_t<decltype(obj.*field.pointer)>>::
                visitField(visitor, obj.*field.pointer, ctx);
        });
    }
};


template <>
struct SubnodeRecVisitor<ImmId> {
    static void visitField(
        CR<org::SubnodeVisitor>   visitor,
        ImmId                     org,
        org::ImmAstContext const& ctx) {
        switch_node_value(org, ctx, [&]<typename N>(N const& value) {
            SubnodeRecVisitor<org::ImmIdT<N>>::visitField(
                visitor, org.as<N>(), ctx);
        });
    }
};


template <sem::IsOrg T>
struct SubnodeRecVisitor<T> {
    static void visitField(
        CR<org::SubnodeVisitor>   visitor,
        CR<T>                     node,
        org::ImmAstContext const& ctx) {
        SubnodeRecVisitor<ImmId>::visitField(visitor, node.asOrg(), ctx);
    }
};

template <IsVariant T>
struct SubnodeRecVisitor<T> {
    static void visitField(
        CR<org::SubnodeVisitor>   visitor,
        CR<T>                     node,
        org::ImmAstContext const& ctx) {
        std::visit(
            [&](auto const& it) {
                SubnodeRecVisitor<std::remove_cvref_t<decltype(it)>>::
                    visitField(visitor, it, ctx);
            },
            node);
    }
};

template <typename T>
struct SubnodeRecVisitor<Vec<T>> {
    static void visitField(
        CR<org::SubnodeVisitor>   visitor,
        Vec<T> const&             value,
        org::ImmAstContext const& ctx) {
        for (const auto& it : value) {
            SubnodeRecVisitor<T>::visitField(visitor, it, ctx);
        }
    }
};


template <typename T>
struct SubnodeRecVisitor<ImmVec<T>> {
    static void visitField(
        CR<org::SubnodeVisitor>   visitor,
        ImmVec<T> const&          value,
        org::ImmAstContext const& ctx) {
        for (const auto& it : value) {
            SubnodeRecVisitor<T>::visitField(visitor, it, ctx);
        }
    }
};

template <typename K, typename V>
struct SubnodeRecVisitor<UnorderedMap<K, V>> {
    static void visitField(
        CR<org::SubnodeVisitor>   visitor,
        UnorderedMap<K, V> const& value,
        org::ImmAstContext const& ctx) {
        for (const auto& [key, value] : value) {
            SubnodeRecVisitor<V>::visitField(visitor, value, ctx);
        }
    }
};


template <typename K, typename V>
struct SubnodeRecVisitor<ImmMap<K, V>> {
    static void visitField(
        CR<org::SubnodeVisitor>   visitor,
        ImmMap<K, V> const&       value,
        org::ImmAstContext const& ctx) {
        for (const auto& [key, value] : value) {
            SubnodeRecVisitor<V>::visitField(visitor, value, ctx);
        }
    }
};


template <typename T>
struct SubnodeRecVisitor<ImmBox<T>> {
    static void visitField(
        CR<org::SubnodeVisitor>   visitor,
        CR<ImmBox<T>>             value,
        org::ImmAstContext const& ctx) {
        SubnodeRecVisitor<T>::visitField(visitor, value.get(), ctx);
    }
};

template <typename T>
struct SubnodeRecVisitor<Opt<T>> {
    static void visitField(
        CR<org::SubnodeVisitor>   visitor,
        CR<Opt<T>>                value,
        org::ImmAstContext const& ctx) {
        if (value) {
            SubnodeRecVisitor<T>::visitField(visitor, *value, ctx);
        }
    }
};

} // namespace


void org::eachSubnodeRec(ImmAdapter id, SubnodeVisitor cb) {
    SubnodeRecVisitor<ImmId>::visitField(cb, id.id, id.ctx);
}


namespace {
struct ImmTreeReprContext {
    int                           level;
    Vec<int>                      path;
    org::ImmAdapter::TreeReprConf conf;
    ImmAstContext const&          ctx;

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

void treeReprRec(
    org::ImmAdapter           id,
    ColStream&                os,
    ImmTreeReprContext const& ctx) {
    os.indent(ctx.level * 2);
    os << fmt(
        "{} {} PATH:{}", id->getKind(), id.id.getReadableId(), ctx.path);

    if (ctx.conf.withAuxFields) {
        switch_node_value(id.id, id.ctx, [&]<typename N>(N const& node) {
            os << " " << fmt1(node);
        });
    }

    os << "\n";

    int idx = 0;
    for (auto const& it : id.sub()) {
        treeReprRec(it, os, ctx.addLevel(1).addPath(idx));
        ++idx;
    }
}
} // namespace

void ImmAdapter::treeRepr(ColStream& os, const TreeReprConf& conf) const {
    treeReprRec(
        *this,
        os,
        ImmTreeReprContext{
            .conf  = conf,
            .level = 0,
            .ctx   = this->ctx,
        });
}

Opt<ImmAdapter> ImmAdapter::getAdjacentNode(int offset) const {
    auto parent = getParent();
    if (parent) {
        int pos = getSelfIndex() + offset;
        if (0 <= pos && pos < parent->size()) {
            return parent->at(pos);
        } else {
            return std::nullopt;
        }
    } else {
        return std::nullopt;
    }
}

Opt<ImmAdapter> ImmAdapter::getParentSubtree() const {
    auto parent = getParent();
    while (parent) {
        if (parent->is(OrgSemKind::Subtree)) {
            return parent;
        } else {
            parent = parent->getParent();
        }
    }
    return std::nullopt;
}

Vec<ImmAdapter> ImmAdapter::getAllSubnodes(Opt<ImmPath> rootPath) const {
    Vec<ImmAdapter>           result;
    auto                      root = *this;
    ReflRecursiveVisitContext visitCtx;

    auto add_id = [&](ReflPath const& parent, ImmId const& id) {
        ImmPath path;
        if (rootPath) {
            path = *rootPath;
        } else {
            path.root = this->id;
        }
        path.path.push_back(ImmPathStep{parent});
        result.push_back(root.pass(id, path));
    };

    switch_node_value(id, ctx, [&]<typename T>(T const& value) {
        reflVisitAll<T>(
            value,
            {},
            visitCtx,
            overloaded{
                [&](ReflPath const& parent, ImmId const& id) {
                    add_id(parent, id);
                },
                [&]<typename K>(
                    ReflPath const& parent, ImmIdT<K> const& id) {
                    add_id(parent, id.toId());
                },
                [&](ReflPath const& parent, auto const& other) {},
            });
    });
    return result;
}

Vec<ImmAdapter> ImmAdapter::getAllSubnodesDFS(
    Opt<ImmPath> rootPath) const {
    Vec<ImmAdapter>                                    result;
    Func<void(ImmAdapter const&, ImmPath const& root)> aux;
    aux = [&](ImmAdapter const& it, ImmPath const& root) {
        result.push_back(it);
        for (auto const& sub : it.getAllSubnodes(root)) {
            aux(sub, sub.path);
        }
    };
    for (auto const& it : getAllSubnodes(rootPath)) { aux(it, it.path); }
    return result;
}

ImmAstTrackingMap ImmAstTrackingMapTransient::persistent() {
    return ImmAstTrackingMap{
        .footnotes     = footnotes.persistent(),
        .subtrees      = subtrees.persistent(),
        .radioTargets  = radioTargets.persistent(),
        .anchorTargets = anchorTargets.persistent(),
    };
}

ImmAstContext ImmAstEditContext::finish() {
    return ctx->finishEdit(*this);
}

ImmAstStore& ImmAstEditContext::store() { return *ctx->store; }

void ImmAstEditContext::message(
    const std::string& value,
    const char*        function,
    int                line,
    const char*        file) {
    ctx->message(value, debug.activeLevel, function, line, file);
}


template <typename T>
struct value_metadata<ImmVec<T>> {
    static bool isEmpty(ImmVec<T> const& value) { return value.empty(); }
};


template <typename T>
struct value_metadata<ImmSet<T>> {
    static bool isEmpty(ImmSet<T> const& value) { return value.empty(); }
};


template <typename T>
struct value_metadata<ImmBox<Opt<T>>> {
    static bool isEmpty(ImmBox<Opt<T>> const& value) {
        return value.impl() == nullptr || !value.get().has_value();
    }
};

template <typename T>
struct value_metadata<ImmBox<T>> {
    static bool isEmpty(ImmBox<T> const& value) {
        return value.impl() == nullptr;
    }
};


Graphviz::Graph org::toGraphviz(
    const Vec<ImmAstVersion>& history,
    ImmAstGraphvizConf const& conf) {
    Graphviz::Graph g{"g"_ss};
    g.setBackgroundColor("beige");

    UnorderedSet<ImmId>                              visited;
    UnorderedMap<ImmId, Graphviz::Node>              gvNodes;
    UnorderedMap<Pair<ImmId, ImmId>, Graphviz::Edge> gvEdges;
    Vec<Graphviz::Graph>                             gvClusters;
    ImmAstContext ctx = history.front().context;

    auto get_graph = [&](int epoch) -> Graphviz::Graph& {
        if (conf.withEpochClusters && epoch < history.size()) {
            if (!gvClusters.has(epoch)) {
                auto sub = g.newSubgraph(fmt("epoch_{}", epoch));
                sub.setLabel(fmt("Epoch {}", epoch));
                gvClusters.resize_at(epoch, sub);
            }

            return gvClusters.at(epoch);
        } else {
            return g;
        }
    };

    auto get_node = [&](ImmId id, int idx) -> Opt<Graphviz::Node> {
        if (conf.skippedKinds.contains(id.getKind()) || id.isNil()) {
            return std::nullopt;
        } else {
            if (!gvNodes.contains(id)) {
                auto node = get_graph(idx).node(id.getReadableId());
                if (auto color = conf.epochColors.get(idx); color) {
                    node.setColor(*color);
                }
                node.setShape(Graphviz::Node::Shape::rectangle);
                gvNodes.insert_or_assign(id, node);
                Vec<Str> label;
                int      maxFieldWidth = 0;

                auto field = [&]<typename T>(
                                 Str const& name, T const& value) {
                    label.push_back(
                        fmt("{}: {}",
                            left_aligned(name, maxFieldWidth),
                            value));
                };


                switch_node_fields(
                    id,
                    ctx,
                    [&]<typename F>(Str const& name, F const& value) {
                        maxFieldWidth = std::max<int>(
                            maxFieldWidth, name.size());
                    });

                field("ID", id);
                switch_node_fields(
                    id,
                    ctx,
                    [&]<typename F>(Str const& name, F const& value) {
                        if (auto skipped = conf.skippedFields.get(
                                fmt1(id.getKind()));
                            skipped && skipped->contains(name)) {
                            return;
                        } else if (value_metadata<F>::isEmpty(value)) {
                            return;
                        } else {
                            field(name, value);
                        }
                    });

                node.setLabel(join("\n", label));
            }

            return gvNodes.at(id);
        }
    };


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
                    Pair<ImmId, ImmId> pair{id, it.value()};
                    if (!gvEdges.contains(pair)) {
                        auto edge = g.edge(*node, *sub_imm);
                        edge.setColor(conf.epochColors.at(idx));
                        edge.setLabel(fmt1(it.index()));
                        gvEdges.insert_or_assign(pair, edge);
                    }
                }
            }
        }
    };

    for (auto const& [idx, epoch] : enumerate(history)) {
        aux(epoch.epoch.getRoot(), idx);
    }

    if (conf.withAuxNodes) {
        for (ImmId id : ctx.store->all_ids()) {
            if (!gvNodes.contains(id)) { aux(id, history.size()); }
        }
    }

    if (conf.withEditHistory) {
        for (auto const& epoch : history) {
            for (auto const& act :
                 epoch.epoch.replaced.allReplacements()) {
                auto const& src = gvNodes.get(act.original->id);
                auto const& dst = gvNodes.get(act.replaced.id);
                if (src && dst) {
                    auto edge = g.edge(*src, *dst);
                    edge.setConstraint(false);
                    edge.setStyle("dashed");
                    edge.setColor("darkgreen");
                }
            }
        }
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
    return Vec<ImmId>{arg.toId()};
}

IMM_SUBNODE_COLLECTOR((), (ImmId)) { return Vec<ImmId>{arg}; }
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


ImmAdapter ImmAstVersion::getRootAdapter() const {
    return org::ImmAdapter{
        epoch.getRoot(),
        context,
        ImmPath{epoch.getRoot()},
    };
}

ImmAstVersion ImmAstVersion::getEditVersion(
    Func<ImmAstReplaceGroup(ImmAstContext&, ImmAstEditContext&)> cb) {
    return context.getEditVersion(getRootAdapter(), cb);
}

void ImmAstReplaceGroup::set(const ImmAstReplace& replace) {
    LOGIC_ASSERTION_CHECK(replace.original.has_value(), "");
    LOGIC_ASSERTION_CHECK(
        replace.original != replace.replaced,
        "Identical original and replaced node: {}",
        replace);
    replace.original->id.assertValid();
    replace.replaced.id.assertValid();

    nodeReplaceMap.insert_or_assign(
        replace.original->id, replace.replaced.id);
    map.insert_or_assign(*replace.original, replace.replaced);
}

void ImmAstReplaceGroup::incl(const ImmAstReplace& replace) {
    LOGIC_ASSERTION_CHECK(
        !map.contains(replace.original.value()),
        "replacement group cannot contain duplicate nodes. {0} -> {1} "
        "is already added, {0} -> {2} cannot be included",
        /*0*/ replace.original,
        /*1*/ map.at(replace.original.value()),
        /*2*/ replace.replaced);
    set(replace);
}

ImmVec<ImmId> ImmAstReplaceGroup::newSubnodes(
    ImmVec<ImmId> oldSubnodes) const {
    ImmVec<ImmId> result;
    auto          tmp = result.transient();
    for (auto const& it : oldSubnodes) {
        if (auto update = nodeReplaceMap.get(it); update) {
            tmp.push_back(*update);
        } else {
            tmp.push_back(it);
        }
    }

    for (auto const& it : tmp) { it.assertValid(); }

    return tmp.persistent();
}

Vec<ImmId> ImmAstReplaceGroup::newSubnodes(Vec<ImmId> oldSubnodes) const {
    auto tmp = newSubnodes(
        ImmVec<ImmId>{oldSubnodes.begin(), oldSubnodes.end()});
    return Vec<ImmId>{tmp.begin(), tmp.end()};
}
