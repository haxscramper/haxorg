#include "org_document_model.hpp"
#include <hstd/stdlib/diffs.hpp>
#include <exporters/ExporterUltraplain.hpp>
#include <sem/SemBaseApi.hpp>
#include <QLabel>


OrgSubtreeSearchModel::OrgSubtreeSearchModel(
    OrgDocumentModel* baseModel,
    QObject*          parent,
    OrgStore*         store)
    : QObject(parent)
    , filter(
          std::make_shared<OrgDocumentSearchFilter>(baseModel, parent)) {
    filter->acceptNode = [this](OrgBoxId arg) -> bool {
        auto const& node     = this->store->node(arg);
        bool        score_ok = pattern.empty() || -1 < getScore(arg);
        bool        result   = node->is(OrgSemKind::Document)
                   || (node->is(OrgSemKind::Subtree) && score_ok);
        return result;
    };

    setScoreSorted(true);
}

int OrgSubtreeSearchModel::getScore(OrgBoxId arg) {
    auto const& node = store->node(arg);
    u64         addr = (u64)node.get();
    if (!scoreCache.contains(addr)) {
        FuzzyMatcher<char const> matcher;
        std::string              title = ExporterUltraplain::toStr(
            node.as<sem::Subtree>()->title);
        scoreCache[addr] = matcher.get_score(title, pattern);
    }

    return scoreCache[addr];
}

void OrgSubtreeSearchModel::setPattern(CR<QString> pattern) {
    filter->invalidate();
    this->pattern = to_std(pattern);
    scoreCache.clear();
}

void OrgSubtreeSearchModel::setScoreSorted(bool sorted) {
    if (sorted) {
        filter->nodeLessThan = [this](OrgBoxId lhs, OrgBoxId rhs) -> bool {
            return getScore(lhs) < getScore(rhs);
        };
    } else {
        filter->nodeLessThan = nullptr;
    }
}

void OrgDocumentModel::loadFile(const fs::path& path) {
    auto document = sem::parseFile(path, sem::OrgParseParameters{});
    this->root = std::make_unique<TreeNode>(store->add(document), nullptr);
    buildTree(this->root.get());
}

void OrgDocumentModel::buildTree(TreeNode* parentNode) {
    auto const& node = store->node(parentNode->boxId);
    if (SemSet{
            OrgSemKind::Subtree,
            OrgSemKind::Document,
            OrgSemKind::List,
            OrgSemKind::ListItem,
            OrgSemKind::StmtList,
        }
            .contains(node->getKind())) {
        for (auto& subnodeId : node->subnodes) {
            parentNode->children.push_back(std::make_unique<TreeNode>(
                store->add(subnodeId), parentNode));
            buildTree(parentNode->children.back().get());
        }
    }
}

QModelIndex OrgDocumentModel::index(
    int                row,
    int                column,
    const QModelIndex& parent) const {
    if (!hasIndex(row, column, parent)) { return QModelIndex(); }

    TreeNode* parentNode = !parent.isValid() ? root.get()
                                             : static_cast<TreeNode*>(
                                                 parent.internalPointer());
    TreeNode* childNode  = parentNode->children.at(row).get();
    if (childNode) { return createIndex(row, column, childNode); }
    return QModelIndex();
}

QModelIndex OrgDocumentModel::parent(const QModelIndex& index) const {
    if (!index.isValid()) { return QModelIndex(); }

    TreeNode* childNode  = static_cast<TreeNode*>(index.internalPointer());
    TreeNode* parentNode = childNode->parent;

    if (parentNode == root.get()) { return QModelIndex(); }

    int row = parentNode->parent
                ? std::find_if(
                      parentNode->parent->children.begin(),
                      parentNode->parent->children.end(),
                      [&](CR<UPtr<TreeNode>> node) {
                          return node.get() == parentNode;
                      })
                      - parentNode->parent->children.begin()
                : 0;
    return createIndex(row, 0, parentNode);
}

int OrgDocumentModel::rowCount(const QModelIndex& parent) const {
    if (parent.column() > 0) { return 0; }

    TreeNode* parentNode = !parent.isValid() ? root.get()
                                             : static_cast<TreeNode*>(
                                                 parent.internalPointer());
    return parentNode->children.size();
}

static QString tree_node_mime{"application/vnd.myapp.treenode"};

QMimeData* OrgDocumentModel::mimeData(
    const QModelIndexList& indexes) const {
    QMimeData*  mimeData = new QMimeData();
    QByteArray  encodedData;
    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    for (const QModelIndex& index : indexes) {
        if (index.isValid()) { stream << index.data(Qt::EditRole); }
    }

    mimeData->setData(tree_node_mime, encodedData);
    return mimeData;
}

bool OrgDocumentModel::dropMimeData(
    const QMimeData*   data,
    Qt::DropAction     action,
    int                row,
    int                column,
    const QModelIndex& parent) {
    if (data->hasFormat(tree_node_mime)) {
        if (action == Qt::IgnoreAction) { return true; }

        int beginRow;
        if (row != -1) {
            beginRow = row;
        } else if (parent.isValid()) {
            beginRow = rowCount(parent);
        } else {
            beginRow = rowCount(QModelIndex());
        }

        QByteArray  encodedData = data->data(tree_node_mime);
        QDataStream stream(&encodedData, QIODevice::ReadOnly);
        QVariant    id;
        while (!stream.atEnd()) {
            stream >> id;
            insertRow(beginRow, parent);
            QModelIndex idx = index(beginRow, 0, parent);
            setData(idx, id, Qt::EditRole);
        }
        return true;
    } else {
        return false;
    }
}


QVariant OrgDocumentModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) { return QVariant(); }
    TreeNode* node = static_cast<TreeNode*>(index.internalPointer());
    return QVariant::fromValue(node->boxId);
}

Qt::ItemFlags OrgDocumentModel::flags(const QModelIndex& index) const {
    if (index.isValid()) {
        return Qt::ItemIsDragEnabled //
             | Qt::ItemIsDropEnabled //
             | Qt::ItemIsEditable    //
             | QAbstractItemModel::flags(index);
    } else {
        return Qt::NoItemFlags;
    }
}

bool OrgDocumentModel::moveRows(
    const QModelIndex& sourceParent,
    int                sourceRow,
    int                count,
    const QModelIndex& destinationParent,
    int                destinationChild) {
    TreeNode* srcParentNode  = sourceParent.isValid()
                                 ? static_cast<TreeNode*>(
                                    sourceParent.internalPointer())
                                 : root.get();
    TreeNode* destParentNode = destinationParent.isValid()
                                 ? static_cast<TreeNode*>(
                                     destinationParent.internalPointer())
                                 : root.get();

    if (sourceRow + count <= srcParentNode->children.size()
        && destinationChild <= destParentNode->children.size()) {
        beginMoveRows(
            sourceParent,
            sourceRow,
            sourceRow + count - 1,
            destinationParent,
            destinationChild);
        std::vector<std::unique_ptr<TreeNode>> movedNodes;
        for (int i = 0; i < count; ++i) {
            movedNodes.push_back(
                std::move(srcParentNode->children[sourceRow]));
            srcParentNode->children.erase(
                srcParentNode->children.begin() + sourceRow);
        }
        if (destinationChild > srcParentNode->children.size()) {
            destinationChild = destParentNode->children.size();
        }
        for (auto& node : movedNodes) {
            destParentNode->children.insert(
                destParentNode->children.begin() + destinationChild,
                std::move(node));
            node->parent = destParentNode;
            ++destinationChild;
        }
        endMoveRows();
        return true;
    }
    return false;
}

sem::SemId<sem::Org> copy(sem::OrgArg node) {
    switch (node->getKind()) {
#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: {                                            \
        sem::SemId<sem::__Kind> new_id = sem::SemId<sem::__Kind>::New();  \
        *new_id.get()                  = *node.getAs<sem::__Kind>();      \
        return new_id.asOrg();                                            \
    }
        EACH_SEM_ORG_KIND(_case)
#undef _case
    }
}

bool OrgDocumentModel::setData(
    const QModelIndex& index,
    const QVariant&    value,
    int                role) {
    if (!index.isValid()) { return false; }
    if (role == Qt::EditRole) {
        TreeNode* node = static_cast<TreeNode*>(index.internalPointer());

        if (value.typeId() == QMetaType::type("OrgBoxId")) {
            node->boxId = qvariant_cast<OrgBoxId>(value);
        } else {
            QString text = value.toString();
            if (text.isEmpty()) {
                qDebug()
                    << "Setting model data with empty text -- removing row"
                    << index;
                removeRow(index.row(), index.parent());
            } else {
                auto document = sem::parseString(text.toStdString());
                node->boxId   = store->add(document->at(0));
            }
        }

        return true;

    } else {
        return false;
    }
}
