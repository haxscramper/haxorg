#pragma once

#include <QAbstractItemModel>
#include <QObject>
#include <memory>
#include <vector>
#include <unordered_map>
#include <haxorg/sem/ImmOrg.hpp>

struct OrgDiagramNode
    : public QObject
    , public std::enable_shared_from_this<OrgDiagramNode> {
    Q_OBJECT

  public:
    org::imm::ImmUniqId                          id;
    std::vector<std::shared_ptr<OrgDiagramNode>> subnodes;
    std::weak_ptr<OrgDiagramNode>                parent;

    OrgDiagramNode(org::imm::ImmUniqId const& id) : id{id} {}

    void addSubnode(std::shared_ptr<OrgDiagramNode> node) {
        node->parent = shared_from_this();
        subnodes.push_back(node);
        emit subnodeAdded(static_cast<int>(subnodes.size()) - 1);
    }

    void removeSubnode(int index) {
        if (index >= 0 && index < static_cast<int>(subnodes.size())) {
            subnodes.at(index)->parent.reset();
            emit subnodeAboutToBeRemoved(index);
            subnodes.erase(subnodes.begin() + index);
            emit subnodeRemoved();
        }
    }

    void updateData() { emit dataChanged(); }

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
        QObject*                        parent = nullptr)
        : QAbstractItemModel{parent}, rootNode{root} {
        buildNodeMap();
        connectNode(rootNode);
    }

    QModelIndex index(
        int                row,
        int                column,
        const QModelIndex& parent = QModelIndex{}) const override {
        if (!hasIndex(row, column, parent)) { return QModelIndex{}; }

        OrgDiagramNode* parentNode{};
        if (!parent.isValid()) {
            parentNode = rootNode.get();
        } else {
            parentNode = static_cast<OrgDiagramNode*>(
                parent.internalPointer());
        }

        if (row < static_cast<int>(parentNode->subnodes.size())) {
            QModelIndex newIndex = createIndex(
                row, column, parentNode->subnodes.at(row).get());
            nodeMap.insert_or_assign(
                parentNode->subnodes.at(row)->id, newIndex);
            return newIndex;
        }
        return QModelIndex{};
    }

    QModelIndex parent(const QModelIndex& index) const override {
        if (!index.isValid()) { return QModelIndex{}; }

        OrgDiagramNode* childNode = static_cast<OrgDiagramNode*>(
            index.internalPointer());
        auto parentPtr = childNode->parent.lock();

        if (!parentPtr || parentPtr == rootNode) { return QModelIndex{}; }

        auto grandParentPtr = parentPtr->parent.lock();
        if (!grandParentPtr) { return QModelIndex{}; }

        auto it = std::find_if(
            grandParentPtr->subnodes.begin(),
            grandParentPtr->subnodes.end(),
            [&parentPtr](const std::shared_ptr<OrgDiagramNode>& node) {
                return node->id == parentPtr->id;
            });

        if (it != grandParentPtr->subnodes.end()) {
            int row = static_cast<int>(
                std::distance(grandParentPtr->subnodes.begin(), it));
            QModelIndex parentIndex = createIndex(row, 0, parentPtr.get());
            nodeMap.insert_or_assign(parentPtr->id, parentIndex);
            return parentIndex;
        }

        return QModelIndex{};
    }

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
        const QModelIndex& parent = QModelIndex{}) override {
        OrgDiagramNode* parentNode{};
        if (!parent.isValid()) {
            parentNode = rootNode.get();
        } else {
            parentNode = static_cast<OrgDiagramNode*>(
                parent.internalPointer());
        }

        beginInsertRows(parent, row, row + count - 1);

        for (int i = 0; i < count; ++i) {
            auto newNode = std::make_shared<OrgDiagramNode>(
                org::imm::ImmUniqId{org::imm::ImmId::Nil()});
            connectNode(newNode);
            newNode->parent = parentNode->shared_from_this();
            parentNode->subnodes.insert(
                parentNode->subnodes.begin() + row + i, newNode);
        }

        invalidateNodeMapAfterIndex(parent, row);
        endInsertRows();
        return true;
    }

    bool removeRows(
        int                row,
        int                count,
        const QModelIndex& parent = QModelIndex{}) override {
        OrgDiagramNode* parentNode{};
        if (!parent.isValid()) {
            parentNode = rootNode.get();
        } else {
            parentNode = static_cast<OrgDiagramNode*>(
                parent.internalPointer());
        }

        if (row < 0
            || row + count
                   > static_cast<int>(parentNode->subnodes.size())) {
            return false;
        }

        beginRemoveRows(parent, row, row + count - 1);

        for (int i = 0; i < count; ++i) {
            auto nodeToRemove = parentNode->subnodes.at(row);
            removeFromNodeMap(nodeToRemove);
            disconnectNode(nodeToRemove);
            nodeToRemove->parent.reset();
            parentNode->subnodes.erase(parentNode->subnodes.begin() + row);
        }

        invalidateNodeMapAfterIndex(parent, row);
        endRemoveRows();
        return true;
    }

    void addNodeToParent(
        std::shared_ptr<OrgDiagramNode> node,
        const QModelIndex&              parentIndex) {
        OrgDiagramNode* parentNode{};
        if (!parentIndex.isValid()) {
            parentNode = rootNode.get();
        } else {
            parentNode = static_cast<OrgDiagramNode*>(
                parentIndex.internalPointer());
        }

        int row = static_cast<int>(parentNode->subnodes.size());
        beginInsertRows(parentIndex, row, row);
        connectNode(node);
        parentNode->addSubnode(node);
        endInsertRows();
    }

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
        OrgDiagramNode* senderNode = qobject_cast<OrgDiagramNode*>(
            sender());
        QModelIndex parentIndex = getIndexForNode(senderNode);
        beginInsertRows(parentIndex, index, index);
        connectNode(senderNode->subnodes.at(index));
        invalidateNodeMapAfterIndex(parentIndex, index);
        endInsertRows();
    }

    void onSubnodeAboutToBeRemoved(int index) {
        OrgDiagramNode* senderNode = qobject_cast<OrgDiagramNode*>(
            sender());
        QModelIndex parentIndex  = getIndexForNode(senderNode);
        auto        nodeToRemove = senderNode->subnodes.at(index);
        removeFromNodeMap(nodeToRemove);
        disconnectNode(nodeToRemove);
        beginRemoveRows(parentIndex, index, index);
    }

    void onSubnodeRemoved() { endRemoveRows(); }

    void onDataChanged() {
        OrgDiagramNode* senderNode = qobject_cast<OrgDiagramNode*>(
            sender());
        QModelIndex nodeIndex = getIndexForNode(senderNode);
        if (nodeIndex.isValid()) {
            emit dataChanged(nodeIndex, nodeIndex);
        }
    }

  private:
    void buildNodeMap() const {
        nodeMap.clear();
        buildNodeMapRecursive(QModelIndex{});
    }

    void buildNodeMapRecursive(const QModelIndex& parent) const {
        int rows = rowCount(parent);
        for (int i = 0; i < rows; ++i) {
            QModelIndex childIndex = index(i, 0, parent);
            if (childIndex.isValid()) {
                OrgDiagramNode* node = static_cast<OrgDiagramNode*>(
                    childIndex.internalPointer());
                nodeMap.insert_or_assign(node->id, childIndex);
                buildNodeMapRecursive(childIndex);
            }
        }
    }

    void removeFromNodeMap(std::shared_ptr<OrgDiagramNode> node) {
        nodeMap.erase(node->id);
        for (auto& subnode : node->subnodes) {
            removeFromNodeMap(subnode);
        }
    }

    void invalidateNodeMapAfterIndex(
        const QModelIndex& parent,
        int                startRow) {
        OrgDiagramNode* parentNode{};
        if (!parent.isValid()) {
            parentNode = rootNode.get();
        } else {
            parentNode = static_cast<OrgDiagramNode*>(
                parent.internalPointer());
        }

        for (int i = startRow;
             i < static_cast<int>(parentNode->subnodes.size());
             ++i) {
            removeFromNodeMap(parentNode->subnodes.at(i));
        }
    }

    QModelIndex findIndexForId(
        const org::imm::ImmUniqId& id,
        const QModelIndex&         parent) const {
        int rows = rowCount(parent);
        for (int i = 0; i < rows; ++i) {
            QModelIndex childIndex = index(i, 0, parent);
            if (childIndex.isValid()) {
                OrgDiagramNode* node = static_cast<OrgDiagramNode*>(
                    childIndex.internalPointer());
                if (node->id == id) { return childIndex; }
                QModelIndex foundIndex = findIndexForId(id, childIndex);
                if (foundIndex.isValid()) { return foundIndex; }
            }
        }
        return QModelIndex{};
    }

    void connectNode(std::shared_ptr<OrgDiagramNode> node) {
        connect(
            node.get(),
            &OrgDiagramNode::subnodeAdded,
            this,
            &OrgDiagramModel::onSubnodeAdded);
        connect(
            node.get(),
            &OrgDiagramNode::subnodeAboutToBeRemoved,
            this,
            &OrgDiagramModel::onSubnodeAboutToBeRemoved);
        connect(
            node.get(),
            &OrgDiagramNode::subnodeRemoved,
            this,
            &OrgDiagramModel::onSubnodeRemoved);
        connect(
            node.get(),
            &OrgDiagramNode::dataChanged,
            this,
            &OrgDiagramModel::onDataChanged);
    }

    void disconnectNode(std::shared_ptr<OrgDiagramNode> node) {
        disconnect(node.get(), nullptr, this, nullptr);
        for (auto& subnode : node->subnodes) { disconnectNode(subnode); }
    }

    QModelIndex getIndexForNode(OrgDiagramNode* node) const {
        if (node == rootNode.get()) { return QModelIndex{}; }

        return getIndexForId(node->id);
    }
};
