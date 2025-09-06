#include "QtOrgAstModel.hpp"


#include "QtOrgAstModel.moc"

QModelIndex OrgDiagramModel::parent(const QModelIndex& index) const {
    if (index.isValid()) {
        DiaAdapter node = getNode(index);
        return getParentIndex(node.id).value_or(QModelIndex{});
    } else {
        return QModelIndex{};
    }
}

DiaAdapter OrgDiagramModel::getNode(const QModelIndex& index) const {
    DiaAdapter parentNode{};
    if (index.isValid()) {
        return DiaAdapter{
            static_cast<IndexData*>(index.internalPointer())->uniq,
            rootNode.ctx};
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
        return std::format("Node {}", node.id.id.format()).c_str();
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
        return indexForData(row, column, parentNode.at(row, true));
    } else {
        return QModelIndex{};
    }
}
