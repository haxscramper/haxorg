#include "haxorg/exporters/Exporter.hpp"
#include "haxorg/sem/ImmOrgEdit.hpp"
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
#include <haxorg/sem/perfetto_org.hpp>

#include <boost/mp11/list.hpp>
#include <boost/mp11/algorithm.hpp>
#include <type_traits>

const u64 org::ImmId::NodeIdxMask    = 0x000000FFFFFFFFFF; // >>0*0=0,
const u64 org::ImmId::NodeIdxOffset  = 0;
const u64 org::ImmId::NodeKindMask   = 0x000FFF0000000000; // >>10*4=40
const u64 org::ImmId::NodeKindOffset = 40;

const org::ParentPathMap               EmptyParentPathMap;
UnorderedMap<org::ImmReflFieldId, Str> org::ImmReflFieldId::fieldNames;

std::size_t std::hash<org::ImmReflFieldId>::operator()(
    org::ImmReflFieldId const& it) const noexcept {
    std::size_t result = 0;
    hax_hash_combine(result, it.field);
    return result;
}

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
    switch_node_kind(index, [&, index]<typename K>(org::ImmIdT<K> id) {
        res = getStore<K>()->at(index);
        LOGIC_ASSERTION_CHECK(
            res->getKind() == index.getKind(),
            "index kind {} does not match result node kind {}",
            index.getKind(),
            res->getKind());
    });
    return res;
}


void org::eachSubnodeRec(ImmAdapter id, bool withPath, SubnodeVisitor cb) {
    cb(id);
    for (auto const& sub : id.getAllSubnodes(id.path, withPath)) {
        eachSubnodeRec(sub, withPath, cb);
    }
}


namespace {
struct ImmTreeReprContext {
    int                           level;
    Vec<int>                      path;
    org::ImmAdapter::TreeReprConf conf;
    ImmAstContext::WPtr           ctx;

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
    os << fmt("{} {}", id->getKind(), id.id.getReadableId());
    if (!ctx.path.empty()) { os << fmt(" PATH:{}", ctx.path); }

    if (ctx.conf.withReflFields) {
        if (ctx.conf.withAuxFields) {
            switch_node_value(
                id.id, id.ctx.lock(), [&]<typename N>(N const& node) {
                    os << " " << fmt1(node);
                });
        }
        os << "\n";
        for (auto const& sub : id.getAllSubnodes(std::nullopt)) {
            os.indent((ctx.level + 1) * 2);
            os << fmt("{}", sub.path);
            os << "\n";
            treeReprRec(sub, os, ctx.addLevel(2));
        }
    } else {
        if (ctx.conf.withAuxFields) {
            switch_node_value(
                id.id, id.ctx.lock(), [&]<typename N>(N const& node) {
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
}
} // namespace

Str ImmAdapter::selfSelect() const {
    Str result = "root";
    for (ImmPathStep const& step : path.path) {
        auto const& i = step.path.path;
        if (i.size() == 2 && i.at(0).isFieldName() && i.at(1).isIndex()
            && i.at(0).getFieldName().name.getName() == "subnodes") {
            result += fmt(".at({})", i.at(1).getIndex().index);
        } else if (
            i.size() == 2 && i.at(0).isFieldName() && i.at(1).isAnyKey()) {
            result += fmt(
                R"(.{}.at("{}"))",
                i.at(0).getFieldName().name.getName(),
                i.at(1).getAnyKey().get<Str>());
        } else if (i.size() == 1 && i.at(0).isFieldName()) {
            return fmt(".{}", i.at(0).getFieldName().name.getName());
        } else if (
            i.size() == 2 && i.at(0).isFieldName() && i.at(1).isIndex()) {
            result += fmt(
                ".{}.at({})",
                i.at(0).getFieldName().name.getName(),
                i.at(1).getIndex().index);
        } else {
            result += fmt1(i);
        }
    }

    return result;
}

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

bool ImmAdapter::isDirectParentOf(const ImmAdapter& other) const {
    if (auto parent = other.getParent(); parent) {
        return parent->id == this->id;
    } else {
        return false;
    }
}

bool ImmAdapter::isIndirectParentOf(const ImmAdapter& other) const {
    for (auto const& parent : other.getParentChain(false)) {
        if (parent.id == this->id) { return true; }
    }

    return false;
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

Vec<ImmAdapter> ImmAdapter::getAllSubnodes(
    Opt<ImmPath> const& rootPath,
    bool                withPath) const {
    Vec<ImmAdapter>           result;
    auto                      root = *this;
    ReflRecursiveVisitContext visitCtx;

    auto add_id = [&](org::ImmReflPathBase const& parent,
                      ImmId const&                id) {
        if (withPath) {
            ImmPath path;
            if (rootPath) {
                path = *rootPath;
            } else {
                path.root = this->id;
            }
            path.path = path.path.push_back(ImmPathStep{parent});
            result.push_back(root.pass(id, path));
        } else {
            result.push_back(root.ctx.lock()->adaptUnrooted(id));
        }
    };

    switch_node_value(id, ctx.lock(), [&]<typename T>(T const& value) {
        reflVisitAll<T, org::ImmReflPathTag>(
            value,
            {},
            visitCtx,
            overloaded{
                [&](org::ImmReflPathBase const& parent, ImmId const& id) {
                    add_id(parent, id);
                },
                [&]<typename K>(
                    org::ImmReflPathBase const& parent,
                    ImmIdT<K> const& id) { add_id(parent, id.toId()); },
                [&](org::ImmReflPathBase const& parent,
                    auto const&                 other) {},
            });
    });
    return result;
}

Vec<ImmAdapter> ImmAdapter::getAllSubnodesDFS(
    Opt<ImmPath> const&                     rootPath,
    bool                                    withPath,
    const Opt<Func<bool(org::ImmAdapter)>>& acceptFilter) const {
    Vec<ImmAdapter>                                    result;
    Func<void(ImmAdapter const&, ImmPath const& root)> aux;
    aux = [&](ImmAdapter const& it, ImmPath const& root) {
        if (!acceptFilter.has_value() || acceptFilter.value()(it)) {
            result.push_back(it);
            for (auto const& sub : it.getAllSubnodes(root, withPath)) {
                aux(sub, sub.path);
            }
        }
    };
    for (auto const& it : getAllSubnodes(rootPath, withPath)) {
        aux(it, it.path);
    }
    return result;
}

Vec<ImmPathStep> ImmAdapter::getRelativeSubnodePaths(
    const ImmId& subnode) const {
    Vec<ImmPathStep> result;
    for (auto const& sub : getAllSubnodes(std::nullopt)) {
        LOGIC_ASSERTION_CHECK(sub.path.path.size() == 1, "");
        if (sub.id == subnode) { result.push_back(sub.path.path.at(0)); }
    }

    return result;
}

Vec<ImmAdapter> ImmAdapter::getParentChain(bool withSelf) const {
    Vec<ImmAdapter> result;
    for (auto const& span : path.pathSpans()) {
        result.push_back(ImmAdapter{
            ImmPath{path.root, span},
            ctx,
        });
    }
    result.push_back(ImmAdapter{ImmPath{path.root}, ctx});
    return result;
}

ImmAdapter ImmAdapter::at(int idx, bool withPath) const {
    if (withPath) {
        return at(
            ctx.lock()->at(id)->subnodes.at(idx),
            ImmPathStep::FieldIdx(
                org::ImmReflFieldId::FromTypeField<org::ImmOrg>(
                    &org::ImmOrg::subnodes),
                idx));
    } else {
        return ImmAdapter{ctx.lock()->at(id)->subnodes.at(idx), ctx, {}};
    }
}

Vec<ImmAdapter> ImmAdapter::sub(bool withPath) const {
    Vec<ImmAdapter> result;
    for (int i = 0; i < size(); ++i) { result.push_back(at(i, withPath)); }
    return result;
}

void ImmAstTrackingMapTransient::setAsParentOf(
    const ImmId& parent,
    const ImmId& target) {
    __perf_trace("imm", "setAsParentOf");
    auto const* newParent = parents.find(target);
    if (newParent == nullptr) { parents.set(target, ImmParentIdVec{}); }

    if (!parents.at(target).contains(parent)) {
        __perf_trace("imm", "update list of parents");
        parents.update(target, [&](ImmParentIdVec value) {
            value.push_back(parent);
            return value;
        });
    }
}

SemSet FastTrackNodes{
    OrgSemKind::Word,
    OrgSemKind::Space,
    OrgSemKind::Punctuation,
    OrgSemKind::Time,
};

void ImmAstTrackingMapTransient::removeAllSubnodesOf(
    const ImmAdapter& parent) {
    if (!isTrackingParent(parent)) { return; }
    __perf_trace("imm", "removeAllSubnodesOf");
    for (auto const& sub : parent.getAllSubnodes(std::nullopt, false)) {
        auto subParents = parents.find(sub.id);
        if (isTrackingParent(sub) && subParents != nullptr) {
            if (subParents->contains(parent.id)) {
                __perf_trace("imm", "update list of parents");
                parents.update(sub.id, [&](ImmParentIdVec value) {
                    value.erase(value.begin() + value.indexOf(parent.id));
                    return value;
                });
            }
        }
    }
}

void ImmAstTrackingMapTransient::insertAllSubnodesOf(
    const ImmAdapter& parent) {
    if (!isTrackingParent(parent)) { return; }
    __perf_trace("imm", "insertAllSubnodesOf");
    for (auto const& sub : parent.getAllSubnodes(std::nullopt, false)) {
        if (isTrackingParent(sub)) { setAsParentOf(parent.id, sub.id); }
    }
}

ImmAstTrackingMap ImmAstTrackingMapTransient::persistent() {
    return ImmAstTrackingMap{
        .footnotes        = footnotes.persistent(),
        .subtrees         = subtrees.persistent(),
        .radioTargets     = radioTargets.persistent(),
        .anchorTargets    = anchorTargets.persistent(),
        .parents          = parents.persistent(),
        .names            = names.persistent(),
        .isTrackingParent = isTrackingParentImpl,
    };
}

SPtr<ImmAstContext> ImmAstEditContext::finish() {
    return ctx.lock()->finishEdit(*this);
}

ImmAstStore& ImmAstEditContext::store() { return *ctx.lock()->store; }

template <org::IsImmOrgValueType T>
struct imm_api_type {
    using api_type = typename org::ImmAdapterT<T>::api_type;
};

template <typename T, typename API>
concept ProvidesImmApi //
    = std::is_base_of_v<API, typename imm_api_type<T>::api_type>
   || std::is_same_v<API, typename imm_api_type<T>::api_type>;

void ImmAstEditContext::updateTracking(const ImmId& node, bool add) {
    __perf_trace("imm", "updateTracking");
    auto search_radio_targets = [&](org::ImmAdapter const& id) {
        __perf_trace("imm", "search radio targets");
        for (auto const& target : id.subAs<org::ImmRadioTarget>(false)) {
            if (ctx.lock()->debug->TraceState) {
                message(
                    fmt("Node {} contains radio target {}",
                        node,
                        target.getText()));
            }
            if (add) {
                transientTrack.radioTargets.set(target.getText(), node);
            } else {
                transientTrack.radioTargets.erase(target.getText());
            }
        }
    };

    switch_node_value(
        node,
        ctx.lock(),
        overloaded{
            [&]<typename N>(N const& nodeValue)
                requires(ProvidesImmApi<N, ImmAdapterStmtAPI>)
                        {
                            auto adapter = ctx.lock()
                                               ->adaptUnrooted(node)
                                               .as<N>();
                            __perf_trace("imm", "track names");
                            for (auto const& name : adapter.getName()) {
                                if (ctx.lock()->debug->TraceState) {
                                    message(fmt(
                                        "Tracking name '{}' for node {}",
                                        name,
                                        node));
                                }
                                if (add) {
                                    transientTrack.names.set(name, node);
                                } else {
                                    transientTrack.names.erase(name);
                                }
                            }
                        },
                        [&]<typename N>(N const& nodeValue)
                            requires(!ProvidesImmApi<N, ImmAdapterStmtAPI>)
            { /*_dfmt(node, nodeValue); */ },
        });

    if (!SemSet{OrgSemKind::Subtree, OrgSemKind::Paragraph}.contains(
            node.getKind())) {
        return;
    }

    switch_node_value(
        node,
        ctx.lock(),
        overloaded{
            [&](org::ImmSubtree const& subtree) {
                __perf_trace("imm", "track subtree");
                if (auto id = subtree.treeId.get(); id) {
                    if (ctx.lock()->debug->TraceState) {
                        message(fmt("Subtree ID {}", id.value()));
                    }
                    if (add) {
                        transientTrack.subtrees.set(*id, node);
                    } else {
                        transientTrack.subtrees.erase(*id);
                    }
                }
            },
            [&](org::ImmParagraph const&) {
                __perf_trace("imm", "track paragraph");
                auto par = ctx.lock()
                               ->adaptUnrooted(node)
                               .as<org::ImmParagraph>();
                if (par.isFootnoteDefinition()) {
                    auto id = par.getFootnoteName().value();
                    if (ctx.lock()->debug->TraceState) {
                        message(fmt("Footnote ID {}", id));
                    }
                    if (add) {
                        transientTrack.footnotes.set(id, node);
                    } else {
                        transientTrack.footnotes.erase(id);
                    }
                }
                search_radio_targets(ctx.lock()->adaptUnrooted(node));
            },
            [&](auto const& nodeValue) {},
        });
}

void ImmAstEditContext::message(
    const std::string& value,
    const char*        function,
    int                line,
    const char*        file) {
    ctx.lock()->message(value, debug.activeLevel, function, line, file);
}

finally ImmAstEditContext::collectAbslLogs() {
    return ctx.lock()->debug->collectAbslLogs(&debug);
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
    ImmAstContext::Ptr ctx = history.front().context;

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
        for (ImmId id : ctx->store->all_ids()) {
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
Vec<ImmId> org::allSubnodes(T const& value, const SharedPtrApi::Ptr& ctx) {
    Vec<ImmId> subnodes;
    for_each_field_with_bases<T>([&](auto const& f) {
        using FieldType = DESC_FIELD_TYPE(f);
        auto tmp = ImmSubnodeCollectionVisitor<FieldType>::getSubnodes(
            value.*f.pointer, ctx);
        subnodes.append(tmp);
    });
    return subnodes;
}


Vec<ImmId> org::allSubnodes(
    const ImmId&             value,
    const SharedPtrApi::Ptr& ctx) {
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
        &context,
        ImmPath{epoch.getRoot()},
    };
}

ImmAstVersion ImmAstVersion::getEditVersion(
    Func<ImmAstReplaceGroup(ImmAstContext&, ImmAstEditContext&)> cb) {
    return context.getEditVersion(getRootAdapter(), cb);
}

void ImmAstReplaceGroup::set(const ImmAstReplace& replace) {
    LOGIC_ASSERTION_CHECK(replace.original.has_value(), "");
    for (auto const& it :
         Vec<ImmUniqId>{replace.original.value(), replace.replaced}) {
        bool check = it.id.is(OrgSemKind::Document)
                  || it.id.is(OrgSemKind::DocumentGroup)
                  || !it.path.empty();
        LOGIC_ASSERTION_CHECK(
            check,
            "Replace group origina/replaced ID must either be a tree root "
            "-- document or a document group -- or have a non-empty path, "
            "but {} does not match the requirement. Kind is {}, path is "
            "{}",
            replace,
            it.id.getKind(),
            it.path);
    }
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

ImmParentIdVec EmptyImmParentIdVec;

const ImmParentIdVec& ImmAstTrackingMap::getParentIds(
    const ImmId& it) const {
    if (parents.contains(it)) {
        return parents.at(it);
    } else {
        return EmptyImmParentIdVec;
    }
}

ParentPathMap ImmAstTrackingMap::getParentsFor(
    const ImmId&         it,
    ImmAstContext const* ctx) const {
    if (parents.contains(it)) {
        ParentPathMap result;
        for (auto const& parent : parents.at(it)) {
            for (auto const& relative :
                 ctx->adaptUnrooted(parent).getRelativeSubnodePaths(it)) {
                if (!result.contains(parent)) {
                    result.insert_or_assign(parent, ImmParentPathVec{});
                }

                result.at(parent).push_back(relative);
            }
        }

        return result;
    } else {
        return EmptyParentPathMap;
    }
}

Vec<ImmUniqId> ImmAstTrackingMap::getPathsFor(
    const ImmId&         it,
    const ImmAstContext* ctx) const {
    Func<Vec<ImmPath>(ImmId const& id)> aux;
    aux = [&](ImmId const& id) -> Vec<ImmPath> {
        Vec<ImmPath> result;
        for (auto const& [parentId, parentPaths] :
             getParentsFor(id, ctx)) {
            auto auxRes = aux(parentId);
            if (auxRes.empty()) {
                for (auto const& full : parentPaths) {
                    ImmPath path;
                    path.root = parentId;
                    path.path = path.path.push_back(full);
                    result.push_back(path);
                }
            } else {
                for (auto const& added : auxRes) {
                    for (auto const& full : parentPaths) {
                        ImmPath path = added;
                        path.path    = path.path.push_back(full);
                        result.push_back(path);
                    }
                }
            }
        }
        return result;
    };

    Vec<ImmUniqId> result;
    for (auto const& path : aux(it)) {
        result.push_back(ImmUniqId{.path = path, .id = it});
    }

    std::sort(result.begin(), result.end());
    return result;
}

Vec<ImmAdapter> ImmAstContext::getAdaptersFor(const ImmId& it) const {
    Vec<ImmAdapter> result;
    for (auto const& id : getPathsFor(it)) { result.push_back(adapt(id)); }
    return result;
}

ImmAstEditContext ImmAstContext::getEditContext() {
    return ImmAstEditContext{
        .transientTrack = currentTrack->transient(this),
        .ctx            = this,
        .debug          = OperationsScope{
                     .TraceState  = &debug->TraceState,
                     .activeLevel = 0,
        }};
}

bool org::isTrackingParentDefault(const ImmAdapter& node) {
    return !SemSet{
        OrgSemKind::Space,
        OrgSemKind::Word,
        OrgSemKind::BigIdent,
        OrgSemKind::Time,
        OrgSemKind::Punctuation,
        OrgSemKind::Newline,
    }
                .contains(node.getKind());
}
