#pragma once

#include "src/model/nodes/DiagramTreeNode.hpp"
#include <QAbstractItemModel>
#include <src/gui/items/DiaSceneItem.hpp>
#include <src/gui/items/DiaSceneItemVisual.hpp>

#include <src/utils/common.hpp>

#pragma clang diagnostic ignored "-Wmacro-redefined"
#define _cat "model.tree"


struct DiaSceneItemModel : public QAbstractItemModel {
    Q_OBJECT

  public:
    DiaSceneItem* rootNode{};

    bool hasScene() const { return rootNode != nullptr; }

    DiaSceneItemModel(QObject* parent = nullptr)
        : QAbstractItemModel{parent} {}


    hstd::Opt<QModelIndex> indexAtPath(hstd::Vec<int> const& path) const {
        QModelIndex result;
        for (auto const& i : path) {
            if (i < rowCount(result)) {
                result = index(i, 0, result);
            } else {
                return std::nullopt;
            }
        }
        return result;
    }

    QModelIndex index(
        int                row,
        int                column,
        const QModelIndex& parent = QModelIndex{}) const override;

    QModelIndex parent(const QModelIndex& index) const override;

    DiaSceneItem* getNode(QModelIndex const& node) const {
        if (node.isValid()) {
            return static_cast<DiaSceneItem*>(node.internalPointer());
        } else {
            return rootNode;
        }
    }

    int rowCount(
        const QModelIndex& parent = QModelIndex{}) const override {
        if (hasScene()) {
            return static_cast<int>(getNode(parent)->subnodes.size());
        } else {
            return 0;
        }
    }

    int columnCount(
        const QModelIndex& parent = QModelIndex{}) const override {
        return 1;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)
        const override;

    void refresh() {
        beginResetModel();
        endResetModel();
    }


    void beginEditApply(DiaEdit const& edit);
    void endEditApply(DiaEdit const& edit);

  public slots:
    void selectNodes(const QList<DiaSceneItemVisual*>& visualNodes) {
        hstd::logic_assertion_check_not_nil(rootNode);
        HSLOG_TRACKED_SLOT(get_tracker(), "selectNodes", visualNodes);
        emit layoutAboutToBeChanged();

        // Convert visual nodes to model indexes
        QList<QModelIndex> indexes;
        for (DiaSceneItemVisual* visualNode : visualNodes) {
            QModelIndex index = getIndexForNode(visualNode);
            if (index.isValid()) { indexes.append(index); }
        }

        emit layoutChanged();
        emit nodesSelected(indexes);
    }

  signals:
    void nodesSelected(const QList<QModelIndex>& indexes);

  private:
    QModelIndex getIndexForNode(DiaSceneItem* targetNode) const {
        hstd::logic_assertion_check_not_nil(rootNode);
        return findNodeIndex(QModelIndex{}, targetNode);
    }

    QModelIndex findNodeIndex(
        const QModelIndex& parent,
        DiaSceneItem*      targetNode) const;
};
