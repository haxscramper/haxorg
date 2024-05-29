#include <editor/editor_lib/store/org_document_store.hpp>
#include <editor/editor_lib/common/app_utils.hpp>

Opt<OrgTreeNode::MoveParams> OrgTreeNode::getMoveParams(
    OrgTreeNode* parent,
    int          index) {
    if ((parent == this->parent && index == this->selfRow().value())
        || (this == parent)) {
        return std::nullopt;
    }

    Q_ASSERT(0 <= index);

    for (auto p = parent->parent; p != nullptr; p = p->parent) {
        Q_ASSERT_X(
            this != p,
            "moveSubtree",
            fmt("Moved index {} is ancestor of the new parent {} -- move "
                "is invalid",
                qdebug_to_str(this),
                qdebug_to_str(parent)));
    }

    int destinationRow = index;

    // _qfmt(
    //     "parent_position:{} moved_index->selfRow():{}",
    //     destinationRow,
    //     this->selfRow());

    if (parent == this->parent && selfRow().value() < destinationRow) {
        // If moving row forward in the same parent, it is going to be
        // first inserted into the target position and then replaced. See
        // `beginMoveRows` docs in qt for example diagram.
        destinationRow += 1;
    }


    return MoveParams{
        .destinationParent = parent->id(),
        .sourceParent      = this->parent->id(),
        .destinationRow    = destinationRow,
        .sourceLast        = this->selfRow().value(),
        .sourceFirst       = this->selfRow().value(),
    };
}

Opt<OrgTreeNode::MoveParams> OrgTreeNode::getShiftParams(int offset) {
    int move_position = std::clamp<int>(
        this->selfRow().value() + offset, 0, parent->subnodes.size() - 1);
    Q_ASSERT(0 <= move_position);
    return getMoveParams(this->parent, move_position);
}

void OrgTreeNode::apply(CR<MoveParams> params) {
    emit store->beginNodeMove(params);

    Q_ASSERT(this->parent != nullptr);

    auto& parentNodes = this->parent->subnodes;

    for (auto const& sub : parentNodes) { Q_ASSERT(sub.get() != nullptr); }

    // Release the unique pointer content but leave the pointer itself in
    // the array
    OrgTreeNode* movedTree = parentNodes[params.sourceFirst].release();

    auto destinationParent = tree(params.destinationParent);

    // Construct the new pointer at specified destination row
    destinationParent->subnodes.emplace(
        destinationParent->subnodes.begin() + params.destinationRow,
        movedTree);

    // Erase the original content at the last step, this matches how qt
    // computes row begin/end movements.
    parentNodes.erase(parentNodes.begin() + parentNodes.indexOf(nullptr));

    for (auto const& sub : parentNodes) { Q_ASSERT(sub.get() != nullptr); }

    emit store->endNodeMove(params);
}

void OrgTreeNode::apply(
    CR<InsertParams>         params,
    Vec<UPtr<OrgTreeNode>>&& inserted) {
    InsertParams tmp = params;
    tmp.last         = tmp.first + inserted.high();

    emit store->beginNodeInsert(tmp);

    OrgTreeNode* node = tree(params.parent);

    auto parent_node = node->getBoxedNode();

    for (auto const& sub : inserted) {
        Q_ASSERT(sub->getBoxedNode()->getKind() != osk::Document);
        if (auto added_subtree = sub->getBoxedNode()
                                     .asOpt<sem::Subtree>()) {
            if (auto parent_subtree = parent_node.asOpt<sem::Subtree>()) {
                Q_ASSERT_X(
                    parent_subtree->level < added_subtree->level,
                    "apply insert",
                    fmt("Cannot insert subtree with level {} under "
                        "subtree "
                        "level {}",
                        added_subtree->level,
                        parent_subtree->level));
            }
        }
    }


    std::copy(
        std::make_move_iterator(inserted.begin()),
        std::make_move_iterator(inserted.end()),
        std::insert_iterator<Vec<UPtr<OrgTreeNode>>>(
            node->subnodes, node->subnodes.begin() + params.first));

    for (int i = params.first; i <= params.last; ++i) {
        node->subnodes.at(i)->parent = node;
    }

    for (auto const& sub : node->subnodes) {
        Q_ASSERT(sub->parent == node);
    }


    emit store->endNodeInsert(tmp);
}

ColText OrgTreeNode::treeRepr() const {
    Func<void(OrgTreeNode const* sub, int level)> aux;
    ColStream                                     os;

    aux = [&](OrgTreeNode const* node, int level) {
        os << os.indent(level * 2)
           << fmt1(node->getBoxedNode()->getKind());
        for (auto const& sub : node->subnodes) {
            os << "\n";
            aux(sub.get(), level + 1);
        }
    };

    aux(this, 0);
    return os.getBuffer();
}

OrgTreeNode::InsertParams OrgTreeNode::getInsertAfter() {
    return InsertParams{
        .parent = opt_value(parentId(), "cannot insert after root node"),
        .first  = selfRow().value() + 1,
        .last   = selfRow().value() + 1,
    };
}

OrgTreeNode::InsertParams OrgTreeNode::getInsertBefore() {
    return InsertParams{
        .parent = opt_value(parentId(), "cannot insert before root node"),
        .first  = selfRow().value(),
        .last   = selfRow().value(),
    };
}

OrgTreeNode::InsertParams OrgTreeNode::getInsertFirstUnder() {
    return InsertParams{
        .parent = id(),
        .first  = 0,
        .last   = 0,
    };
}

OrgTreeNode::InsertParams OrgTreeNode::getInsertLastUnder() {
    return InsertParams{
        .parent = id(),
        .first  = subnodes.size(),
        .last   = subnodes.size(),
    };
}
