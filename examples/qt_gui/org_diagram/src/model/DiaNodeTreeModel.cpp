#include "DiaNodeTreeModel.hpp"


#include "DiaNodeTreeModel.moc"

QModelIndex DiaNodeTreeModel::parent(const QModelIndex& index) const {
    if (index.isValid()) {
        DiaAdapter node = getNode(index);
        return getParentIndex(node.id).value_or(QModelIndex{});
    } else {
        return QModelIndex{};
    }
}

DiaAdapter DiaNodeTreeModel::getNode(const QModelIndex& index) const {
    DiaAdapter parentNode{};
    if (index.isValid()) {
        return DiaAdapter{
            static_cast<IndexData*>(index.internalPointer())->uniq,
            rootNode.ctx};
    } else {
        return rootNode;
    }
}

int DiaNodeTreeModel::rowCount(const QModelIndex& parent) const {
    return getNode(parent).size();
}

QVariant DiaNodeTreeModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) { return QVariant{}; }

    if (role == Qt::DisplayRole) {
        DiaAdapter node = getNode(index);
        return std::format("Node {}", node.getDiaId().format()).c_str();
    }

    return QVariant{};
}

DiaNodeTreeModel::DiaNodeTreeModel(const DiaAdapter& root, QObject* parent)
    : QAbstractItemModel{parent}, rootNode{root} {
    TRACKED_FUNCTION(OrgDiagramModel);
}

void DiaNodeTreeModel::setNewRoot(
    const DiaAdapter&           root,
    const hstd::Vec<DiaEdit>& edits) {}

hstd::ColText DiaNodeTreeModel::format() {
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


QModelIndex DiaNodeTreeModel::index(
    int                row,
    int                column,
    const QModelIndex& parent) const {
    if (!hasIndex(row, column, parent)) { return QModelIndex{}; }

    DiaAdapter parentNode = getNode(parent);
    if (row < static_cast<int>(parentNode->subnodes.size())) {
        return indexForData(row, column, parentNode.at(row, true));
    } else {
        return QModelIndex{};
    }
}
