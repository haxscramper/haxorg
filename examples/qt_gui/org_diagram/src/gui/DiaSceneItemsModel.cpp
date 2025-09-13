#include "DiaSceneItemsModel.hpp"

QModelIndex DiaSceneItemsModel::index(
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
QModelIndex DiaSceneItemsModel::parent(const QModelIndex& index) const {
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
QVariant DiaSceneItemsModel::data(const QModelIndex& index, int role)
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
QModelIndex DiaSceneItemsModel::findNodeIndex(
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
