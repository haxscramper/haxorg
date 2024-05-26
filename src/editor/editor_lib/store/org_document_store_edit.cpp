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

void OrgTreeNode::doMove(CR<MoveParams> params) {
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
