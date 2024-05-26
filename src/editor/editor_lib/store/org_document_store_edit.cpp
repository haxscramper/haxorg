#include <editor/editor_lib/store/org_document_store.hpp>
#include <editor/editor_lib/common/app_utils.hpp>

int computeDestinationChild(
    OrgTreeNode* moved_index,
    OrgTreeNode* new_parent,
    int          parent_position) {
    if (moved_index == nullptr) {
        throw std::invalid_argument("Invalid moved_index provided");
    }

    if (new_parent == moved_index->parent) {
        if (parent_position <= moved_index->selfRow()) {
            return parent_position;
        } else {
            return parent_position + 1;
        }
    } else {
        return parent_position;
    }
}


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

    int destinationChild = computeDestinationChild(this, parent, index);

    return MoveParams{
        .destinationParent = parent->id(),
        .sourceParent      = this->parent->id(),
        .destinationRow    = destinationChild,
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
    _qfmt("params:{}", params);

    Q_ASSERT(this->parent != nullptr);

    auto& parent_nodes = this->parent->subnodes;
    int   self_row     = this->selfRow().value();

    for (auto const& sub : parent_nodes) {
        Q_ASSERT(sub.get() != nullptr);
    }

    std::unique_ptr<OrgTreeNode> moved_tree = std::move(
        parent_nodes[self_row]);

    auto start_size = parent_nodes.size();
    parent_nodes.erase(parent_nodes.begin() + self_row);

    Q_ASSERT(parent_nodes.size() + 1 == start_size);

    for (auto const& sub : parent_nodes) {
        Q_ASSERT(sub.get() != nullptr);
    }

    auto destinationParent = tree(params.destinationParent);

    destinationParent->subnodes.insert(
        destinationParent->subnodes.begin() + params.destinationRow,
        std::move(moved_tree));

    emit store->endNodeMove(params);
}
