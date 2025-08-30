#pragma once

#include <QAbstractItemModel>
#include <QObject>
#include <memory>
#include <unordered_map>
#include <haxorg/sem/ImmOrg.hpp>
#include <src/utils/log_graph_tracker.hpp>
#include <src/utils/common.hpp>
#include <src/model/nodes/DiagramTreeNode.hpp>


struct OrgDiagramModel : public QAbstractItemModel {
    Q_OBJECT

  private:
    hstd::SPtr<DiagramTreeNode>                                   rootNode;
    mutable std::unordered_map<org::imm::ImmUniqId, QModelIndex> nodeMap;

  public:
    explicit OrgDiagramModel(
        std::shared_ptr<DiagramTreeNode> root,
        QObject*                        parent = nullptr);

    hstd::ColText format();

    QModelIndex index(
        int                row,
        int                column,
        const QModelIndex& parent = QModelIndex{}) const override;

    QModelIndex parent(const QModelIndex& index) const override;

    DiagramTreeNode* getNode(QModelIndex const& index) const;

    int rowCount(const QModelIndex& parent = QModelIndex{}) const override;

    int columnCount(
        const QModelIndex& parent = QModelIndex{}) const override {
        return getNode(parent)->getColumnCount();
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)
        const override;

    bool insertRows(
        int                row,
        int                count,
        const QModelIndex& parent = QModelIndex{}) override;

    bool removeRows(
        int                row,
        int                count,
        const QModelIndex& parent = QModelIndex{}) override;

    void addNodeToParent(
        std::shared_ptr<DiagramTreeNode> node,
        const QModelIndex&              parentIndex);

    QModelIndex getIndexForId(const org::imm::ImmUniqId& id) const;


  private slots:
    void onSubnodeAdded(int index);

    void onSubnodeAboutToBeRemoved(int index);

    void onSubnodeRemoved() {
        TRACKED_SLOT(onSubnodeRemoved);
        endRemoveRows();
    }

    void onDataChanged();

  private:
    void buildNodeMap() const {
        nodeMap.clear();
        buildNodeMapRecursive(QModelIndex{});
    }

    void buildNodeMapRecursive(const QModelIndex& parent) const;

    void removeFromNodeMap(std::shared_ptr<DiagramTreeNode> node) {
        nodeMap.erase(node->id.uniq());
        for (auto& subnode : node->subnodes) {
            removeFromNodeMap(subnode);
        }
    }

    void invalidateNodeMapAfterIndex(
        const QModelIndex& parent,
        int                startRow);

    QModelIndex findIndexForId(
        const org::imm::ImmUniqId& id,
        const QModelIndex&         parent) const;

    void connectNode(std::shared_ptr<DiagramTreeNode> node);

    void disconnectNode(std::shared_ptr<DiagramTreeNode> node) {
        disconnect(node.get(), nullptr, this, nullptr);
        for (auto& subnode : node->subnodes) { disconnectNode(subnode); }
    }

    QModelIndex getIndexForNode(DiagramTreeNode* node) const {
        if (node == rootNode.get()) { return QModelIndex{}; }

        return getIndexForId(node->id.uniq());
    }
};
