#include "hstd/stdlib/Set.hpp"
#include "hstd/stdlib/algorithms.hpp"
#include <haxorg/sem/ImmOrg.hpp>
#include <haxorg/sem/ImmOrgHash.hpp>
#include <hstd/stdlib/Enumerate.hpp>
#include <immer/vector_transient.hpp>
#include <immer/set_transient.hpp>
#include <immer/map_transient.hpp>
#include <immer/flex_vector_transient.hpp>
#include <immer/flex_vector.hpp>

using namespace org;

struct store_error : CRTP_hexception<store_error> {};

#define _kind(__Kind)                                                     \
    template <>                                                           \
    ImmAstKindStore<Imm##__Kind> const* ImmAstStore::getStoreImpl()       \
        const {                                                           \
        return &store##__Kind;                                            \
    }
EACH_SEM_ORG_KIND(_kind)
#undef _kind


ImmAstReplace ImmAstStore::setSubnodes(
    ImmId              target,
    ImmVec<ImmId>      subnodes,
    ImmAstEditContext& ctx) {
    LOGIC_ASSERTION_CHECK(
        !target.isNil(), "cannot set subnodes to nil node");
    ImmAstReplace result;
    switch_node_value(target, *ctx.ctx, [&]<typename N>(N node) {
        node.subnodes = subnodes;
        result        = setNode(target, node, ctx);
    });

    return result;
}


template <org::IsImmOrgValueType T>
ImmAstReplace ImmAstStore::setNode(
    ImmId              target,
    const T&           value,
    ImmAstEditContext& ctx) {
    ImmId result_node = getStore<T>()->add(value, ctx);

    LOGIC_ASSERTION_CHECK(
        !result_node.isNil(), "added node must not be nil");
    result_node.assertValid();

    // Remove all original subnode mapping.
    for (auto const& sub :
         allSubnodes<T>(ctx.ctx->value<T>(target), *ctx.ctx)) {
        ctx.parents.removeParent(sub);
    }

    for (auto const& sub : allSubnodes<T>(value, *ctx.ctx)) {
        ctx.parents.setParent(sub, result_node);
    }

    AST_EDIT_MSG(fmt(
        "Original ID:{:<16} {}", fmt1(target), ctx.ctx->value<T>(target)));
    AST_EDIT_MSG(fmt("Replaced ID:{:<16} {}", fmt1(result_node), value));

    return ImmAstReplace{.replaced = result_node, .original = target};
}


ImmAstReplace ImmAstStore::setSubnode(
    ImmId              target,
    ImmId              newSubnode,
    int                position,
    ImmAstEditContext& ctx) {
    AST_EDIT_MSG(fmt("Set {}[{}] = {}", target, position, newSubnode));
    return setSubnodes(
        target,
        ctx.ctx->at(target)->subnodes.set(position, newSubnode),
        ctx);
}

ImmAstReplace ImmAstStore::insertSubnode(
    ImmId              target,
    ImmId              add,
    int                position,
    ImmAstEditContext& ctx) {
    AST_EDIT_MSG(fmt("Insert {}[{}] = {}", target, position, add));
    return setSubnodes(
        target, ctx.ctx->at(target)->subnodes.insert(position, add), ctx);
}

ImmAstReplace ImmAstStore::insertSubnodes(
    ImmId              target,
    Vec<ImmId>         add,
    int                position,
    ImmAstEditContext& ctx) {
    Vec<ImmId> u;
    LOGIC_ASSERTION_CHECK(0 <= position, "{}", position);


    auto tmp = ctx.ctx->at(target)->subnodes;
    AST_EDIT_MSG(fmt("Insert {} at {} in {}", add, position, tmp));
    for (int i = 0; i < position; ++i) { u.push_back(tmp.at(i)); }
    for (auto const& a : add) { u.push_back(a); }
    for (int i = position; i < tmp.size(); ++i) { u.push_back(tmp.at(i)); }
    return setSubnodes(target, ImmVec<ImmId>{u.begin(), u.end()}, ctx);
}

ImmAstReplace ImmAstStore::appendSubnode(
    ImmId              target,
    ImmId              add,
    ImmAstEditContext& ctx) {
    return insertSubnode(
        target, add, ctx->at(target)->subnodes.size(), ctx);
}

ImmAstReplace ImmAstStore::dropSubnode(
    ImmId              target,
    int                position,
    ImmAstEditContext& ctx) {
    AST_EDIT_MSG(fmt("Drop subnode {}[{}]", target, position));
    return setSubnodes(
        target, ctx.ctx->at(target)->subnodes.take(position), ctx);
}

ImmAstReplace ImmAstStore::dropSubnode(
    ImmId              target,
    ImmId              subnode,
    ImmAstEditContext& ctx) {
    int idx = ctx->at(target)->indexOf(subnode);
    LOGIC_ASSERTION_CHECK(
        idx != -1, "Cannot remove subnode {} from {}", target, subnode);
    return dropSubnode(target, idx, ctx);
}

Pair<ImmAstReplace, ImmId> ImmAstStore::popSubnode(
    ImmId              target,
    int                position,
    ImmAstEditContext& ctx) {
    auto pop    = ctx.ctx->at(target)->subnodes.at(position);
    auto update = dropSubnode(target, position, ctx);

    return {update, pop};
}

ImmAstReplaceGroup ImmAstStore::demoteSubtree(
    ImmId              mainTarget,
    SubtreeMove        move,
    ImmAstEditContext& ctx) {
    LOGIC_ASSERTION_CHECK(mainTarget.is(OrgSemKind::Subtree), "");
    ImmAstReplaceGroup edits;

    if (move == SubtreeMove::EnsureLevels
        || move == SubtreeMove::ForceLevels) {

        AST_EDIT_MSG(fmt("Demote subtree {}", mainTarget));
        Func<ImmAstReplace(ImmId)> aux;
        aux = [&](ImmId target) -> ImmAstReplace {
            for (auto const& sub : ctx->adapt(target)) {
                auto __scope = ctx.debug.scopeLevel();
                aux(sub.id);
            }

            auto __scope = ctx.debug.scopeLevel();
            auto update  = updateNode<org::ImmSubtree>(
                target, ctx, [&](org::ImmSubtree value) {
                    value.subnodes = edits.newSubnodes(value.subnodes);
                    value.level += 1;
                    return value;
                });

            edits.incl(update);
            return update;
        };

        auto update        = aux(mainTarget);
        auto targetAdapter = ctx->adapt(mainTarget);
        auto parent        = targetAdapter.getParent();
        auto adjacent      = targetAdapter.getAdjacentNode(-1);

        if (parent && adjacent && adjacent->is(OrgSemKind::Subtree)) {
            auto adjacentTree = adjacent.value().as<org::ImmSubtree>();
            auto replacedTree = ctx->adapt(update.replaced)
                                    .as<org::ImmSubtree>();
            if (adjacentTree->level < replacedTree->level) {
                // Demoting subtree caused reparenting, removing the
                // node from the old subtree.
                AST_EDIT_MSG(
                    fmt("Subtree demote reparenting. Adjacent:{}, "
                        "replaced:{}, "
                        "target drop:{}",
                        adjacent->id,
                        update.replaced,
                        mainTarget));

                auto __scope = ctx.debug.scopeLevel();
                edits.incl(dropSubnode(parent->id, mainTarget, ctx));
                edits.incl(
                    appendSubnode(adjacent->id, update.replaced, ctx));
            } else {
                AST_EDIT_MSG(
                    fmt("Subtree demote, no reparenting, levels are "
                        "ok. "
                        "Adjacent:{}, replaced:{}",
                        adjacentTree->level,
                        replacedTree->level));
            }
        } else {
            AST_EDIT_MSG(
                fmt("Subtree demote, no reparenting parent:{} "
                    "adjacent:{}",
                    parent,
                    adjacent));
        }
    } else {
        AST_EDIT_MSG(fmt("Physical demote subtree {}", mainTarget));
        Vec<ImmId> newSubnodes;
        Vec<ImmId> moveSubnodes;
        auto       tree  = ctx->adapt(mainTarget).as<org::ImmSubtree>();
        int        level = tree->level;
        for (auto const& sub : tree.sub()) {
            if (auto subtree = sub.asOpt<org::ImmSubtree>(); subtree) {
                if (subtree.value()->level < level + 1) {
                    newSubnodes.push_back(subtree->id);
                } else {
                    moveSubnodes.push_back(subtree->id);
                }
            } else {
                newSubnodes.push_back(sub.id);
            }
        }

        AST_EDIT_MSG(fmt("New subnode list {}", newSubnodes));
        AST_EDIT_MSG(fmt("Move subnode list {}", moveSubnodes));

        auto update = updateNode<org::ImmSubtree>(
            mainTarget, ctx, [&](org::ImmSubtree value) {
                value.subnodes = ImmVec<ImmId>{
                    newSubnodes.begin(), newSubnodes.end()};
                value.level += 1;
                return value;
            });

        edits.incl(update);

        if (!moveSubnodes.empty()) {
            auto parent = tree.getParent();
            auto update = insertSubnodes(
                parent->id, moveSubnodes, tree.getSelfIndex(), ctx);
            edits.incl(update);
        }
    }


    return edits;
}


ImmAstReplaceEpoch ImmAstStore::cascadeUpdate(
    ImmAstReplaceGroup const& replace,
    ImmAstEditContext&        ctx) {
    AST_EDIT_MSG("Start cascade update");
    auto __scope = ctx.debug.scopeLevel();

    UnorderedMap<ImmId, Vec<ImmId>> editDependencies;
    UnorderedSet<ImmId>             editParents;

    for (auto const& act : replace.allReplacements()) {
        for (auto const& parent :
             ctx->getParentChain(act.original, false)) {
            editParents.incl(parent);
            if (replace.map.contains(parent)) {
                editDependencies[parent].push_back(act.original);
            }
        }
    }

    AST_EDIT_MSG("Edit replaces");
    {
        auto __scope = ctx.debug.scopeLevel();
        for (auto const& key : replace.allReplacements()) {
            AST_EDIT_MSG(fmt("[{}] -> {}", key.original, key.replaced));
        }
    }

    AST_EDIT_MSG("Edit dependencies");
    {
        auto __scope = ctx.debug.scopeLevel();
        for (auto const& key : sorted(editDependencies.keys())) {
            AST_EDIT_MSG(fmt("[{}] -> {}", key, editDependencies.at(key)));
        }
    }

    Func<ImmId(ImmAdapter node)> aux;
    ImmAstReplaceEpoch           result;

    aux = [&](ImmAdapter node) -> ImmId {
        auto __scope = ctx.debug.scopeLevel();
        if (editParents.contains(node.id)) {
            // The node is a parent subnode for some edit.
            Opt<ImmId> edit = replace.map.get(node.id);
            AST_EDIT_MSG(fmt("Node {} direct edit:{}", node.id, edit));

            Vec<ImmId> updatedSubnodes;
            ImmId      updateTarget = edit ? edit.value() : node.id;

            for (auto const& sub : ctx->adapt(updateTarget).sub()) {
                updatedSubnodes.push_back(aux(sub));
            }


            if (false) {
                auto replaced = ctx->adapt(*edit);
                auto original = ctx->adapt(node.id);
                LOGIC_ASSERTION_CHECK(
                    replaced->subnodes == original->subnodes
                        || replaced->subnodes == updatedSubnodes,
                    "Node {0} was replaced with {1} and the list of "
                    "subnodes differs: (replaced != original) {2} != {3} "
                    "and (replaced != updated) {2} != {5}. The node {0} "
                    "is a parent for edits {4} in this batch, meaning it "
                    "will have the subnodes replaced, and the original "
                    "subnode changes will be lost. To avoid this issue, "
                    "separate the `.subnode` field update and nested node "
                    "edits into two different batches of updates.",
                    /*0*/ node.id,
                    /*1*/ *edit,
                    /*2*/ original->subnodes,
                    /*3*/ replaced->subnodes,
                    /*4*/ editDependencies.at(node.id),
                    /*5*/ updatedSubnodes);

                result.replaced.incl({node.id, edit.value()});
            }


            // List of subnodes can be updated together with the original
            // edits. In this case there is no need to insert the same list
            // of subnodes.
            if (updatedSubnodes != ctx->adapt(updateTarget)->subnodes) {
                AST_EDIT_MSG(
                    fmt("Updated subnodes changed: updated:{} != "
                        "target({}):{}",
                        updatedSubnodes,
                        updateTarget,
                        ctx->adapt(updateTarget)->subnodes));

                ImmAstReplace act = setSubnodes(
                    updateTarget,
                    ImmVec<ImmId>{
                        updatedSubnodes.begin(),
                        updatedSubnodes.end(),
                    },
                    ctx);

                result.replaced.set(act);

                return act.replaced;
            } else {
                return updateTarget;
            }
        } else {
            // The node is not a parent for any other replacement. If it
            // was updated, return a new version, otherwise return the same
            // node.
            if (auto edit = replace.map.get(node.id); edit) {
                result.replaced.incl({node.id, *edit});
                return *edit;
            } else {
                AST_EDIT_MSG(fmt("No changes in {}", node.id));
                return node.id;
            }
        }
    };


    ImmId root = ImmId::Nil();
    for (auto const& act : replace.allReplacements()) {
        auto original = ctx->adapt(act.original);
        auto doc      = original.getParentChain(false).back().id;
        if (root.isNil()) {
            root = doc;
        } else {
            LOGIC_ASSERTION_CHECK(
                doc == root, "doc:{} != root:{}", doc, root);
        }
    }

    AST_EDIT_MSG(fmt("Main root {}", root));
    result.root = aux(ctx->adapt(root));
    return result;
}


ImmId ImmAstStore::add(sem::SemId<sem::Org> data, ImmAstEditContext& ctx) {
    org::ImmId result = org::ImmId::Nil();
    switch_node_kind(
        org::ImmId{data->getKind(), 0},
        [&]<typename K>(org::ImmIdT<K> id) {
            result = getStore<K>()->add(data, ctx);
        });

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
    switch_node_kind(id, [&]<typename K>(org::ImmIdT<K> id) {
        result = getStore<K>()->get(id, ctx);
    });

    return result;
}

const ImmOrg* ImmAstContext::at(ImmId id) const {
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

Opt<Vec<int>> ImmAstParentMap::getPath(ImmId id, const ImmAstContext& ctx)
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
        if (selfIndex == -1) { return std::nullopt; }
        result.push_back(selfIndex);
        id     = parent.value();
        parent = getParent(id);
    }

    reverse(result);
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


ImmAstVersion ImmAstContext::getEditVersion(
    Func<ImmAstReplaceGroup(ImmAstContext& ast, ImmAstEditContext&)> cb) {
    auto ctx     = getEditContext();
    auto replace = cb(*this, ctx);
    return finishEdit(ctx, ctx.store().cascadeUpdate(replace, ctx));
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

    ImmAstVersion result{
        .context = store,
        .epoch   = ImmAstReplaceEpoch{.root = imm_root},
    };

    result.epoch.replaced.incl(replace);
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

ImmAdapter ImmAstContext::adapt(ImmId id) { return ImmAdapter{id, this}; }

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
