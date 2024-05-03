#include "org_document_model.hpp"
#include <hstd/stdlib/diffs.hpp>
#include <exporters/ExporterUltraplain.hpp>
#include <sem/SemBaseApi.hpp>
#include <QLabel>
#include <QDebug>
#include <hstd/stdlib/Enumerate.hpp>


OrgSubtreeSearchModel::OrgSubtreeSearchModel(
    OrgDocumentModel* baseModel,
    QObject*          parent,
    OrgStore*         store)
    : QObject(parent)
    , filter(std::make_shared<OrgDocumentSearchFilter>(baseModel, parent))
    , store(store)
//
{
    filter->acceptNode = [this, store](OrgBoxId arg) -> bool {
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

namespace {
SemSet NestedNodes{
    OrgSemKind::Subtree,
    OrgSemKind::Document,
    OrgSemKind::List,
    OrgSemKind::ListItem,
    OrgSemKind::StmtList,
};
}

void OrgDocumentModel::buildTree(TreeNode* parentNode) {
    auto const& node = store->node(parentNode->boxId);
    if (NestedNodes.contains(node->getKind())) {
        for (auto& subnodeId : node->subnodes) {
            parentNode->subnodes.push_back(std::make_unique<TreeNode>(
                store->add(subnodeId), parentNode));
            buildTree(parentNode->subnodes.back().get());
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
    TreeNode* childNode  = parentNode->subnodes.at(row).get();
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
                      parentNode->parent->subnodes.begin(),
                      parentNode->parent->subnodes.end(),
                      [&](CR<UPtr<TreeNode>> node) {
                          return node.get() == parentNode;
                      })
                      - parentNode->parent->subnodes.begin()
                : 0;
    return createIndex(row, 0, parentNode);
}

int OrgDocumentModel::rowCount(const QModelIndex& parent) const {
    if (parent.column() > 0) { return 0; }

    TreeNode* parentNode = !parent.isValid() ? root.get()
                                             : static_cast<TreeNode*>(
                                                 parent.internalPointer());
    return parentNode->subnodes.size();
}

QString tree_node_mime{"application/vnd.myapp.treenode"};

QVariant OrgDocumentModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) { return QVariant(); }
    TreeNode* node = static_cast<TreeNode*>(index.internalPointer());
    return QVariant::fromValue(node->boxId);
}

Qt::ItemFlags OrgDocumentModel::flags(const QModelIndex& index) const {
    if (index.isValid()) {
        return Qt::ItemIsEditable //
             | QAbstractItemModel::flags(index);
    } else {
        return Qt::NoItemFlags;
    }
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

QModelIndex mapToNestedSource(const QModelIndex& index) {
    QModelIndex currentIndex = index;
    auto currentProxyModel   = qobject_cast<QSortFilterProxyModel const*>(
        index.model());

    while (currentProxyModel) {
        currentIndex      = currentProxyModel->mapToSource(currentIndex);
        currentProxyModel = qobject_cast<QSortFilterProxyModel const*>(
            currentProxyModel->sourceModel());
    }

    return currentIndex;
}

QModelIndex mapToNestedProxy(
    const QModelIndex&          index,
    Vec<QSortFilterProxyModel*> proxies) {
    QModelIndex currentIndex = index;

    for (QSortFilterProxyModel* proxyModel : proxies) {
        currentIndex = proxyModel->mapFromSource(currentIndex);
    }

    return currentIndex;
}

sem::SemId<sem::Org> OrgDocumentModel::TreeNode::toNode(
    OrgStore* store) const {
    auto base = store->node(this->boxId);
    if (NestedNodes.contains(base->getKind())) {
        auto result = copy(base);
        result->subnodes.clear();
        for (auto const& it : enumerator(subnodes)) {
            result->subnodes.push_back(it.value()->toNode(store));
        }
        return result;
    } else {
        return base;
    }
}
