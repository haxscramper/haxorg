#include "QtOrgAstModel.hpp"


#include "QtOrgAstModel.moc"

QModelIndex OrgDiagramModel::parent(const QModelIndex& index) const {
    if (!index.isValid()) { return QModelIndex{}; }

    DiagramTreeNode* childNode = static_cast<DiagramTreeNode*>(
        index.internalPointer());
    auto parentPtr = childNode->parent.lock();

    if (!parentPtr || parentPtr == rootNode) { return QModelIndex{}; }

    auto grandParentPtr = parentPtr->parent.lock();
    if (!grandParentPtr) { return QModelIndex{}; }

    auto it = std::find_if(
        grandParentPtr->subnodes.begin(),
        grandParentPtr->subnodes.end(),
        [&parentPtr](const std::shared_ptr<DiagramTreeNode>& node) {
            return node->id == parentPtr->id;
        });

    if (it != grandParentPtr->subnodes.end()) {
        int row = static_cast<int>(
            std::distance(grandParentPtr->subnodes.begin(), it));
        QModelIndex parentIndex = createIndex(row, 0, parentPtr.get());
        nodeMap.insert_or_assign(parentPtr->uniq(), parentIndex);
        return parentIndex;
    }

    return QModelIndex{};
}

DiaAdapter OrgDiagramModel::getNode(const QModelIndex& index) const {
    DiaAdapter parentNode{};
    if (index.isValid()) {
        return static_cast<ModelData>(index.internalPointer());
    } else {
        return rootNode;
    }
}

int OrgDiagramModel::rowCount(const QModelIndex& parent) const {
    return getNode(parent).size();
}

QVariant OrgDiagramModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) { return QVariant{}; }

    if (role == Qt::DisplayRole) {
        DiaAdapter node = getNode(index);
        return std::format("Node {}", node.id.format()).c_str();
    }

    return QVariant{};
}

OrgDiagramModel::OrgDiagramModel(const DiaAdapter& root, QObject* parent)
    : QAbstractItemModel{parent}, rootNode{root} {
    TRACKED_FUNCTION(OrgDiagramModel);
}

void OrgDiagramModel::setRoot(const DiaAdapter& root) {}

hstd::ColText OrgDiagramModel::format() {
    return ::printModelTree(
        this,
        QModelIndex{},
        [this](QModelIndex const& index) -> hstd::ColText {
            hstd::ColStream os;
            if (index.isValid()) {
                auto node = getNode(index);
                os << hstd::fmt1(node.id);
            }
            return os;
        });
}

QModelIndex OrgDiagramModel::index(
    int                row,
    int                column,
    const QModelIndex& parent) const {
    if (!hasIndex(row, column, parent)) { return QModelIndex{}; }

    DiaAdapter parentNode = getNode(parent);
    if (row < static_cast<int>(parentNode.get()->subnodes.size())) {
        QModelIndex newIndex = indexForData(row, column);
        nodeMap.insert_or_assign(
            parentNode->subnodes.at(row)->uniq(), newIndex);
        return newIndex;
    }
    return QModelIndex{};
}
