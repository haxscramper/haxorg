#include "DiaSceneItemModel.hpp"

QModelIndex DiaSceneItemModel::index(
    int                row,
    int                column,
    const QModelIndex& parent) const {
    hstd::logic_assertion_check_not_nil(rootNode);
    if (!hasIndex(row, column, parent)) { return QModelIndex{}; }

    DiaSceneItem* parentNode{};
    if (!parent.isValid()) {
        parentNode = rootNode;
    } else {
        parentNode = static_cast<DiaSceneItem*>(parent.internalPointer());
    }

    if (row < static_cast<int>(parentNode->children.size())) {
        return createIndex(row, column, parentNode->children.at(row));
    }

    return QModelIndex{};
}
QModelIndex DiaSceneItemModel::parent(const QModelIndex& index) const {
    if (!index.isValid()) { return QModelIndex{}; }

    DiaSceneItem* childNode = static_cast<DiaSceneItem*>(
        index.internalPointer());
    DiaSceneItem* parentNode = childNode->parent;

    if (parentNode == rootNode) { return QModelIndex{}; }

    DiaSceneItem* grandParent = parentNode->parent;
    if (!grandParent) { return QModelIndex{}; }

    for (int i = 0; i < static_cast<int>(grandParent->children.size());
         ++i) {
        if (grandParent->children.at(i) == parentNode) {
            return createIndex(i, 0, parentNode);
        }
    }

    return QModelIndex{};
}
QVariant DiaSceneItemModel::data(const QModelIndex& index, int role)
    const {
    hstd::logic_assertion_check_not_nil(rootNode);
    if (!index.isValid()) { return QVariant{}; }

    if (role == Qt::DisplayRole) {
        DiaSceneItem* node = static_cast<DiaSceneItem*>(
            index.internalPointer());
        return node->name;
    }

    return QVariant{};
}
QModelIndex DiaSceneItemModel::findNodeIndex(
    const QModelIndex& parent,
    DiaSceneItem*      targetNode) const {
    hstd::logic_assertion_check_not_nil(rootNode);
    DiaSceneItem* parentNode = parent.isValid()
                                 ? static_cast<DiaSceneItem*>(
                                       parent.internalPointer())
                                 : rootNode;
    if (!parentNode) { return QModelIndex{}; }

    // Check direct children
    for (int i = 0; i < parentNode->children.size(); ++i) {
        if (parentNode->children[i] == targetNode) {
            return index(i, 0, parent);
        }
    }

    // Search recursively in children
    for (int i = 0; i < parentNode->children.size(); ++i) {
        QModelIndex childIndex = index(i, 0, parent);
        QModelIndex found      = findNodeIndex(childIndex, targetNode);
        if (found.isValid()) { return found; }
    }

    HSLOG_WARNING(
        _cat,
        "Could not find index for target node ",
        targetNode->name.toStdString());

    return QModelIndex{};
}


void DiaSceneItemModel::beginEditApply(const DiaEdit& edit) {
    TRACKED_FUNCTION("beginEditApply");
    switch (edit.getKind()) {
        case DiaEdit::Kind::Delete: {
            auto parent = indexAtPath(
                edit.getSrc().getParentPathFromRoot());
            LOGIC_ASSERTION_CHECK(
                parent.has_value(),
                "Rows cannot be removed from non-existent parent");
            beginRemoveRows(
                parent.value(),
                edit.getDelete().srcIndex,
                edit.getDelete().srcIndex);
        }
    }
}

void DiaSceneItemModel::endEditApply(const DiaEdit& edit) {
    TRACKED_FUNCTION("endEditApply");
    switch (edit.getKind()) {
        case DiaEdit::Kind::Delete: {
            endRemoveRows();
        }
    }
}
