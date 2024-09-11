#include "ImmOrgEdit.hpp"


using namespace org;

ImmAstReplace org::setSubnode(
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

ImmAstReplace org::insertSubnode(
    ImmId              target,
    ImmId              add,
    int                position,
    ImmAstEditContext& ctx) {
    AST_EDIT_MSG(fmt("Insert {}[{}] = {}", target, position, add));
    return setSubnodes(
        target, ctx.ctx->at(target)->subnodes.insert(position, add), ctx);
}

ImmAstReplace org::insertSubnodes(
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

ImmAstReplace org::appendSubnode(
    ImmId              target,
    ImmId              add,
    ImmAstEditContext& ctx) {
    return insertSubnode(
        target, add, ctx->at(target)->subnodes.size(), ctx);
}

ImmAstReplace org::dropSubnode(
    ImmId              target,
    int                position,
    ImmAstEditContext& ctx) {
    AST_EDIT_MSG(fmt("Drop subnode {}[{}]", target, position));
    return setSubnodes(
        target, ctx.ctx->at(target)->subnodes.take(position), ctx);
}

ImmAstReplace org::dropSubnode(
    ImmId              target,
    ImmId              subnode,
    ImmAstEditContext& ctx) {
    int idx = ctx->at(target)->indexOf(subnode);
    LOGIC_ASSERTION_CHECK(
        idx != -1, "Cannot remove subnode {} from {}", target, subnode);
    return dropSubnode(target, idx, ctx);
}

Pair<ImmAstReplace, ImmId> org::popSubnode(
    ImmId              target,
    int                position,
    ImmAstEditContext& ctx) {
    auto pop    = ctx.ctx->at(target)->subnodes.at(position);
    auto update = dropSubnode(target, position, ctx);

    return {update, pop};
}

ImmAstReplaceGroup org::demoteSubtree(
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
            auto update  = ctx.store().updateNode<org::ImmSubtree>(
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

        auto update = ctx.store().updateNode<org::ImmSubtree>(
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
