#pragma once

#include <QAbstractItemModel>
#include <QObject>
#include <memory>
#include <vector>
#include <unordered_map>
#include <haxorg/sem/ImmOrg.hpp>
#include <src/utils/log_graph_tracker.hpp>
#include <src/utils/common.hpp>

struct OrgDiagramNode
    : public QObject
    , public std::enable_shared_from_this<OrgDiagramNode> {
    Q_OBJECT

  public:
    org::imm::ImmUniqId                          id;
    std::vector<std::shared_ptr<OrgDiagramNode>> subnodes;
    std::weak_ptr<OrgDiagramNode>                parent;

    std::string formatToString() const { return hstd::fmt("id:{}", id); }

    OrgDiagramNode(org::imm::ImmUniqId const& id) : id{id} {}

    void addSubnode(std::shared_ptr<OrgDiagramNode> node);
    void removeSubnode(int index);
    void updateData();

  signals:
    void subnodeAdded(int index);
    void subnodeAboutToBeRemoved(int index);
    void subnodeRemoved();
    void dataChanged();
};

struct OrgDiagramModel : public QAbstractItemModel {
    Q_OBJECT

  private:
    std::shared_ptr<OrgDiagramNode>                              rootNode;
    mutable std::unordered_map<org::imm::ImmUniqId, QModelIndex> nodeMap;

  public:
    explicit OrgDiagramModel(
        std::shared_ptr<OrgDiagramNode> root,
        QObject*                        parent = nullptr);

    QModelIndex index(
        int                row,
        int                column,
        const QModelIndex& parent = QModelIndex{}) const override;

    QModelIndex parent(const QModelIndex& index) const override;

    int rowCount(
        const QModelIndex& parent = QModelIndex{}) const override {
        if (parent.column() > 0) { return 0; }

        OrgDiagramNode* parentNode{};
        if (!parent.isValid()) {
            parentNode = rootNode.get();
        } else {
            parentNode = static_cast<OrgDiagramNode*>(
                parent.internalPointer());
        }

        return static_cast<int>(parentNode->subnodes.size());
    }

    int columnCount(
        const QModelIndex& parent = QModelIndex{}) const override {
        return 1;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)
        const override {
        if (!index.isValid()) { return QVariant{}; }

        if (role == Qt::DisplayRole) {
            OrgDiagramNode* node = static_cast<OrgDiagramNode*>(
                index.internalPointer());
            return std::format("Node {}", node->id.id.format()).c_str();
        }

        return QVariant{};
    }

    bool insertRows(
        int                row,
        int                count,
        const QModelIndex& parent = QModelIndex{}) override;

    bool removeRows(
        int                row,
        int                count,
        const QModelIndex& parent = QModelIndex{}) override;

    void addNodeToParent(
        std::shared_ptr<OrgDiagramNode> node,
        const QModelIndex&              parentIndex);

    QModelIndex getIndexForId(const org::imm::ImmUniqId& id) const {
        auto it = nodeMap.find(id);
        if (it != nodeMap.end() && it->second.isValid()) {
            OrgDiagramNode* node = static_cast<OrgDiagramNode*>(
                it->second.internalPointer());
            if (node && node->id == id) { return it->second; }
        }

        QModelIndex foundIndex = findIndexForId(id, QModelIndex{});
        if (foundIndex.isValid()) {
            nodeMap.insert_or_assign(id, foundIndex);
        }
        return foundIndex;
    }


  private slots:
    void onSubnodeAdded(int index) {
        TRACKED_SLOT(onSubnodeAdded, index);
        OrgDiagramNode* senderNode = qobject_cast<OrgDiagramNode*>(
            sender());
        QModelIndex parentIndex = getIndexForNode(senderNode);
        beginInsertRows(parentIndex, index, index);
        connectNode(senderNode->subnodes.at(index));
        invalidateNodeMapAfterIndex(parentIndex, index);
        endInsertRows();
    }

    void onSubnodeAboutToBeRemoved(int index) {
        TRACKED_SLOT(onSubnodeAboutToBeRemoved, index);
        OrgDiagramNode* senderNode = qobject_cast<OrgDiagramNode*>(
            sender());
        QModelIndex parentIndex  = getIndexForNode(senderNode);
        auto        nodeToRemove = senderNode->subnodes.at(index);
        removeFromNodeMap(nodeToRemove);
        disconnectNode(nodeToRemove);
        beginRemoveRows(parentIndex, index, index);
    }

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

    void removeFromNodeMap(std::shared_ptr<OrgDiagramNode> node) {
        nodeMap.erase(node->id);
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

    void connectNode(std::shared_ptr<OrgDiagramNode> node);

    void disconnectNode(std::shared_ptr<OrgDiagramNode> node) {
        disconnect(node.get(), nullptr, this, nullptr);
        for (auto& subnode : node->subnodes) { disconnectNode(subnode); }
    }

    QModelIndex getIndexForNode(OrgDiagramNode* node) const {
        if (node == rootNode.get()) { return QModelIndex{}; }

        return getIndexForId(node->id);
    }
};
