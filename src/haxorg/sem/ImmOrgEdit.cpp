#include "ImmOrgEdit.hpp"


using namespace org;

ImmAstReplace org::setSubnode(
    CR<ImmAdapter>     node,
    ImmId              newSubnode,
    int                position,
    ImmAstEditContext& ctx) {
    AST_EDIT_MSG(fmt("Set {}[{}] = {}", node, position, newSubnode));
    return setSubnodes(
        node, node->subnodes.set(position, newSubnode), ctx);
}

ImmAstReplace org::insertSubnode(
    CR<ImmAdapter>     node,
    ImmId              add,
    int                position,
    ImmAstEditContext& ctx) {
    AST_EDIT_MSG(fmt("Insert {}[{}] = {}", node, position, add));
    return setSubnodes(node, node->subnodes.insert(position, add), ctx);
}

ImmAstReplace org::insertSubnodes(
    CR<ImmAdapter>     node,
    Vec<ImmId>         add,
    int                position,
    ImmAstEditContext& ctx) {
    AST_EDIT_MSG(fmt("Insert {} at {} in {}", add, position, node));
    Vec<ImmId> u;
    LOGIC_ASSERTION_CHECK(0 <= position, "{}", position);


    auto tmp = node->subnodes;
    for (int i = 0; i < position; ++i) { u.push_back(tmp.at(i)); }
    for (auto const& a : add) { u.push_back(a); }
    for (int i = position; i < tmp.size(); ++i) { u.push_back(tmp.at(i)); }
    return setSubnodes(node, ImmVec<ImmId>{u.begin(), u.end()}, ctx);
}

ImmAstReplace org::appendSubnode(
    CR<ImmAdapter>     node,
    ImmId              add,
    ImmAstEditContext& ctx) {
    return insertSubnode(node, add, node->size(), ctx);
}

ImmAstReplace org::dropSubnode(
    CR<ImmAdapter>     node,
    int                position,
    ImmAstEditContext& ctx) {
    AST_EDIT_MSG(fmt("Drop subnode {}[{}]", node, position));
    return setSubnodes(node, node->subnodes.take(position), ctx);
}

ImmAstReplace org::dropSubnode(
    CR<ImmAdapter>     node,
    ImmId              subnode,
    ImmAstEditContext& ctx) {
    int idx = node->indexOf(subnode);
    LOGIC_ASSERTION_CHECK(
        idx != -1, "Cannot remove subnode {} from {}", node, subnode);
    return dropSubnode(node, idx, ctx);
}

Pair<ImmAstReplace, ImmId> org::popSubnode(
    CR<ImmAdapter>     node,
    int                position,
    ImmAstEditContext& ctx) {
    auto pop    = node->subnodes.at(position);
    auto update = dropSubnode(node, position, ctx);

    return {update, pop};
}

ImmAstReplaceGroup org::demoteSubtree(
    CR<ImmAdapter>     node,
    SubtreeMove        move,
    ImmAstEditContext& ctx) {
    LOGIC_ASSERTION_CHECK(node.is(OrgSemKind::Subtree), "");
    ImmAstReplaceGroup edits;

    if (move == SubtreeMove::EnsureLevels
        || move == SubtreeMove::ForceLevels) {

        AST_EDIT_MSG(fmt("Demote subtree {}", node));
        Func<ImmAstReplace(CR<ImmAdapter>)> aux;
        aux = [&](CR<ImmAdapter> target) -> ImmAstReplace {
            for (auto const& sub : target.sub()) {
                auto __scope = ctx.debug.scopeLevel();
                aux(sub);
            }

            auto update = ctx.store().updateNode<org::ImmSubtree>(
                target, ctx, [&](org::ImmSubtree value) {
                    value.subnodes = edits.newSubnodes(value.subnodes);
                    value.level += 1;
                    return value;
                });

            edits.incl(update);
            return update;
        };

        auto update   = aux(node);
        auto parent   = node.getParent();
        auto adjacent = node.getAdjacentNode(-1);

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
                        node));

                auto __scope = ctx.debug.scopeLevel();
                edits.incl(dropSubnode(*parent, node.id, ctx));
                edits.incl(
                    appendSubnode(*adjacent, update.replaced.id, ctx));
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
        AST_EDIT_MSG(fmt("Physical demote subtree {}", node));
        Vec<ImmId> demotedSubnodes;
        Vec<ImmId> reparentedSubnodes;
        auto       tree  = node.as<org::ImmSubtree>();
        int        level = tree->level;
        for (auto const& sub : tree.sub()) {
            if (auto subtree = sub.asOpt<org::ImmSubtree>(); subtree) {
                if (subtree.value()->level < level + 1) {
                    demotedSubnodes.push_back(subtree->id);
                } else {
                    reparentedSubnodes.push_back(subtree->id);
                }
            } else {
                demotedSubnodes.push_back(sub.id);
            }
        }

        AST_EDIT_MSG(fmt("New subnode list {}", demotedSubnodes));
        AST_EDIT_MSG(fmt("Move subnode list {}", reparentedSubnodes));


        {
            auto __scope = ctx.debug.scopeLevel();
            auto update  = ctx.store().updateNode<org::ImmSubtree>(
                node, ctx, [&](org::ImmSubtree value) {
                    value.subnodes = edits.newSubnodes(ImmVec<ImmId>{
                        demotedSubnodes.begin(), demotedSubnodes.end()});
                    value.level += 1;
                    return value;
                });

            AST_EDIT_MSG(fmt("Update subtree {}", update));
            edits.incl(update);

            if (!reparentedSubnodes.empty()) {

                auto parent            = tree.getParent().value();
                auto newParentSubnodes = edits.newSubnodes(Vec<ImmId>{
                    parent->subnodes.begin(), parent->subnodes.end()});
                AST_EDIT_MSG(fmt("Tree {} parent {}", tree, parent));

                reparentedSubnodes = edits.newSubnodes(reparentedSubnodes);
                newParentSubnodes.insert(
                    newParentSubnodes.begin() + tree.getSelfIndex(),
                    reparentedSubnodes.begin(),
                    reparentedSubnodes.end());

                auto update = setSubnodes(
                    parent,
                    {newParentSubnodes.begin(), newParentSubnodes.end()},
                    ctx);
                AST_EDIT_MSG(fmt("Update subnode list {}", update));
                edits.incl(update);
            }
        }
    }


    return edits;
}

Opt<ImmAstReplace> org::moveSubnode(
    CR<ImmAdapter>     node,
    int                position,
    int                offset,
    ImmAstEditContext& ctx,
    bool               bounded) {
    int targetPosition = position + offset;

    LOGIC_ASSERTION_CHECK(
        0 <= position && position < node.size(),
        "Node {} has no subnode at position {}",
        node,
        position);

    if (bounded) {
        LOGIC_ASSERTION_CHECK(
            0 <= targetPosition && targetPosition < node.size(),
            "Cannot move subnode {} of node {} to offset {} (position {} "
            "is out of subnode bounds)",
            position,
            node,
            offset,
            targetPosition);
    }

    targetPosition = std::clamp(targetPosition, 0, node.size() - 1);

    if (targetPosition == position) { return std::nullopt; }

    auto subnodes = node->subnodes;
    auto inserted = subnodes.at(position);
    inserted.assertValid();
    subnodes = subnodes.erase(position);
    subnodes = subnodes.insert(targetPosition, inserted);

    AST_EDIT_MSG(
        fmt("Move subnodes {}[{} + {} => {}] -> {} -> {}",
            node,
            position,
            offset,
            targetPosition,
            node->subnodes,
            subnodes));

    return setSubnodes(node, subnodes, ctx);
}
