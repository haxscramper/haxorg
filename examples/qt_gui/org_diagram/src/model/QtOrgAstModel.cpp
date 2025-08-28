#include "QtOrgAstModel.hpp"


#include "QtOrgAstModel.moc"

QModelIndex OrgDiagramModel::parent(const QModelIndex& index) const {
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

OrgDiagramNode* OrgDiagramModel::getNode(const QModelIndex& index) const {
    OrgDiagramNode* parentNode{};
    if (index.isValid()) {
        return static_cast<OrgDiagramNode*>(index.internalPointer());
    } else {
        return rootNode.get();
    }
}

int OrgDiagramModel::rowCount(const QModelIndex& parent) const {
    return getNode(parent)->subnodes.size();
}

QVariant OrgDiagramModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) { return QVariant{}; }

    if (role == Qt::DisplayRole) {
        OrgDiagramNode* node = static_cast<OrgDiagramNode*>(
            index.internalPointer());
        return std::format("Node {}", node->id.id.format()).c_str();
    }

    return QVariant{};
}

bool OrgDiagramModel::insertRows(
    int                row,
    int                count,
    const QModelIndex& parent) {
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

bool OrgDiagramModel::removeRows(
    int                row,
    int                count,
    const QModelIndex& parent) {
    OrgDiagramNode* parentNode{};
    if (!parent.isValid()) {
        parentNode = rootNode.get();
    } else {
        parentNode = static_cast<OrgDiagramNode*>(
            parent.internalPointer());
    }

    if (row < 0
        || row + count > static_cast<int>(parentNode->subnodes.size())) {
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

void OrgDiagramModel::addNodeToParent(
    std::shared_ptr<OrgDiagramNode> node,
    const QModelIndex&              parentIndex) {
    TRACKED_FUNCTION(addNodeToParent);
    OrgDiagramNode* parentNode{};
    if (!parentIndex.isValid()) {
        parentNode = rootNode.get();
    } else {
        parentNode = static_cast<OrgDiagramNode*>(
            parentIndex.internalPointer());
    }

    connectNode(node);
    parentNode->addSubnode(node);
}

QModelIndex OrgDiagramModel::getIndexForId(
    const org::imm::ImmUniqId& id) const {
    auto it = nodeMap.find(id);
    if (it != nodeMap.end() && it->second.isValid()) {
        OrgDiagramNode* node = static_cast<OrgDiagramNode*>(
            it->second.internalPointer());
        if (node && node->id == id) { return it->second; }
    }

    QModelIndex foundIndex = findIndexForId(id, QModelIndex{});
    if (foundIndex.isValid()) { nodeMap.insert_or_assign(id, foundIndex); }
    return foundIndex;
}

void OrgDiagramModel::onDataChanged() {
    TRACKED_SLOT(onDataChanged);
    OrgDiagramNode* senderNode = qobject_cast<OrgDiagramNode*>(sender());
    QModelIndex     nodeIndex  = getIndexForNode(senderNode);
    if (nodeIndex.isValid()) {
        TRACKED_EMIT(dataChanged, nodeIndex, nodeIndex);
    } else {
        HSLOG_WARNING(
            "gui",
            "Invalid sender node",
            hstd::log::formatQtToString(nodeIndex),
            senderNode->formatToString());
    }
}

void OrgDiagramModel::buildNodeMapRecursive(
    const QModelIndex& parent) const {
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

void OrgDiagramModel::invalidateNodeMapAfterIndex(
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

QModelIndex OrgDiagramModel::findIndexForId(
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

void OrgDiagramModel::connectNode(std::shared_ptr<OrgDiagramNode> node) {
    TRACKED_FUNCTION(connectNode);
    TRACKED_CONNECT(
        node.get(),
        &OrgDiagramNode::subnodeAdded,
        this,
        &OrgDiagramModel::onSubnodeAdded,
        Qt::UniqueConnection);
    TRACKED_CONNECT(
        node.get(),
        &OrgDiagramNode::subnodeAboutToBeRemoved,
        this,
        &OrgDiagramModel::onSubnodeAboutToBeRemoved,
        Qt::UniqueConnection);
    TRACKED_CONNECT(
        node.get(),
        &OrgDiagramNode::subnodeRemoved,
        this,
        &OrgDiagramModel::onSubnodeRemoved,
        Qt::UniqueConnection);
    TRACKED_CONNECT(
        node.get(),
        &OrgDiagramNode::dataChanged,
        this,
        &OrgDiagramModel::onDataChanged,
        Qt::UniqueConnection);

    for (auto const& it : node->subnodes) { connectNode(it); }
}


OrgDiagramModel::OrgDiagramModel(
    std::shared_ptr<OrgDiagramNode> root,
    QObject*                        parent)
    : QAbstractItemModel{parent}, rootNode{root} {
    TRACKED_FUNCTION(OrgDiagramModel);
    buildNodeMap();
    connectNode(rootNode);
}

QModelIndex OrgDiagramModel::index(
    int                row,
    int                column,
    const QModelIndex& parent) const {
    if (!hasIndex(row, column, parent)) { return QModelIndex{}; }

    OrgDiagramNode* parentNode = getNode(parent);
    if (row < static_cast<int>(parentNode->subnodes.size())) {
        QModelIndex newIndex = createIndex(
            row, column, parentNode->subnodes.at(row).get());
        nodeMap.insert_or_assign(
            parentNode->subnodes.at(row)->id, newIndex);
        return newIndex;
    }
    return QModelIndex{};
}

int OrgDiagramNode::getColumnCount() const {
    int result{};
    org::imm::switch_node_kind(
        id.id, [&result]<typename T>(org::imm::ImmIdT<T> const& typed) {
            result = hstd::get_total_field_count<T>();
        });
    return result;
}


void OrgDiagramNode::addSubnode(std::shared_ptr<OrgDiagramNode> node) {
    node->parent = shared_from_this();
    subnodes.push_back(node);
    HSLOG_TRACKED_EMIT(
        get_tracker(),
        subnodeAdded,
        static_cast<int>(subnodes.size()) - 1);
}

void OrgDiagramNode::removeSubnode(int index) {
    if (index >= 0 && index < static_cast<int>(subnodes.size())) {
        subnodes.at(index)->parent.reset();
        HSLOG_TRACKED_EMIT(get_tracker(), subnodeAboutToBeRemoved, index);
        subnodes.erase(subnodes.begin() + index);
        HSLOG_TRACKED_EMIT(get_tracker(), subnodeRemoved);
    }
}

void OrgDiagramNode::updateData() {
    HSLOG_TRACKED_EMIT(get_tracker(), dataChanged);
}

OrgDiagramNode::OrgDiagramNode(org::imm::ImmUniqId const& id) : id{id} {}

void OrgDiagramModel::onSubnodeAdded(int index) {
    TRACKED_SLOT(onSubnodeAdded, index);
    OrgDiagramNode* senderNode  = qobject_cast<OrgDiagramNode*>(sender());
    QModelIndex     parentIndex = getIndexForNode(senderNode);
    beginInsertRows(parentIndex, index, index);
    connectNode(senderNode->subnodes.at(index));
    invalidateNodeMapAfterIndex(parentIndex, index);
    endInsertRows();
}

void OrgDiagramModel::onSubnodeAboutToBeRemoved(int index) {
    TRACKED_SLOT(onSubnodeAboutToBeRemoved, index);
    OrgDiagramNode* senderNode   = qobject_cast<OrgDiagramNode*>(sender());
    QModelIndex     parentIndex  = getIndexForNode(senderNode);
    auto            nodeToRemove = senderNode->subnodes.at(index);
    removeFromNodeMap(nodeToRemove);
    disconnectNode(nodeToRemove);
    beginRemoveRows(parentIndex, index, index);
}
