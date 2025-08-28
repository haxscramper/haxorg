#pragma once

#include <QAbstractItemModel>
#include <src/gui/DiagramNode.hpp>
#include <src/gui/DiagramNodeVisual.hpp>

#include <src/utils/common.hpp>

#pragma clang diagnostic ignored "-Wmacro-redefined"
#define _cat "model.tree"


struct DiagramTreeModel : public QAbstractItemModel {
    Q_OBJECT

  public:
    DiagramNode* rootNode{};

    DiagramTreeModel(DiagramNode* root, QObject* parent = nullptr)
        : QAbstractItemModel{parent}, rootNode{root} {}

    QModelIndex index(
        int                row,
        int                column,
        const QModelIndex& parent = QModelIndex{}) const override {
        if (!hasIndex(row, column, parent)) { return QModelIndex{}; }

        DiagramNode* parentNode{};
        if (!parent.isValid()) {
            parentNode = rootNode;
        } else {
            parentNode = static_cast<DiagramNode*>(
                parent.internalPointer());
        }

        if (row < static_cast<int>(parentNode->children.size())) {
            return createIndex(row, column, parentNode->children.at(row));
        }

        return QModelIndex{};
    }

    QModelIndex parent(const QModelIndex& index) const override {
        if (!index.isValid()) { return QModelIndex{}; }

        DiagramNode* childNode = static_cast<DiagramNode*>(
            index.internalPointer());
        DiagramNode* parentNode = childNode->parent;

        if (parentNode == rootNode) { return QModelIndex{}; }

        DiagramNode* grandParent = parentNode->parent;
        if (!grandParent) { return QModelIndex{}; }

        for (int i = 0; i < static_cast<int>(grandParent->children.size());
             ++i) {
            if (grandParent->children.at(i) == parentNode) {
                return createIndex(i, 0, parentNode);
            }
        }

        return QModelIndex{};
    }

    DiagramNode* getNode(QModelIndex const& node) const {
        if (node.isValid()) {
            return static_cast<DiagramNode*>(node.internalPointer());
        } else {
            return rootNode;
        }
    }

    int rowCount(
        const QModelIndex& parent = QModelIndex{}) const override {
        return static_cast<int>(getNode(parent)->children.size());
    }

    int columnCount(
        const QModelIndex& parent = QModelIndex{}) const override {
        return 1;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)
        const override {
        if (!index.isValid()) { return QVariant{}; }

        if (role == Qt::DisplayRole) {
            DiagramNode* node = static_cast<DiagramNode*>(
                index.internalPointer());
            return node->name;
        }

        return QVariant{};
    }

    void refresh() {
        beginResetModel();
        endResetModel();
    }

  public slots:
    void selectNodes(const QList<DiagramNodeVisual*>& visualNodes) {
        HSLOG_TRACKED_SLOT(get_tracker(), "selectNodes", visualNodes);
        emit layoutAboutToBeChanged();

        // Convert visual nodes to model indexes
        QList<QModelIndex> indexes;
        for (DiagramNodeVisual* visualNode : visualNodes) {
            QModelIndex index = getIndexForNode(visualNode);
            if (index.isValid()) { indexes.append(index); }
        }

        emit layoutChanged();
        emit nodesSelected(indexes);
    }

  signals:
    void nodesSelected(const QList<QModelIndex>& indexes);

  private:
    QModelIndex getIndexForNode(DiagramNode* targetNode) const {
        return findNodeIndex(QModelIndex{}, targetNode);
    }

    QModelIndex findNodeIndex(
        const QModelIndex& parent,
        DiagramNode*       targetNode) const {
        DiagramNode* parentNode = parent.isValid()
                                    ? static_cast<DiagramNode*>(
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
};
