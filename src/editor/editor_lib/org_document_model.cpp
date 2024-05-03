#include "org_document_model.hpp"
#include <hstd/stdlib/diffs.hpp>
#include <exporters/ExporterUltraplain.hpp>
#include <sem/SemBaseApi.hpp>
#include <QLabel>
#include <QDebug>
#include <hstd/stdlib/Enumerate.hpp>
#include <editor/editor_lib/app_utils.hpp>

#define _qdbg(expr) qDebug() << #expr << "=" << expr;

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
        for (auto& sub : node->subnodes) {
            if (!sub->is(OrgSemKind::Newline)) {
                parentNode->subnodes.push_back(std::make_unique<TreeNode>(
                    store->add(sub), parentNode));
                buildTree(parentNode->subnodes.back().get());
            }
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
    if (childNode) {
        return createIndex(row, column, childNode);
    } else {
        return QModelIndex();
    }
}

void OrgDocumentModel::changeLevel(CR<QModelIndex> index, int level) {
    QModelIndex targetParent    = index;
    int         targetParentRow = 0;
    // TODO change for the tree kind
    if (0 < level) {
        for (int i = 0; i < level; ++i) {
            if (targetParent.parent().isValid()) {
                targetParent    = targetParent.parent();
                targetParentRow = targetParent.row();
            } else {
                break;
            }
        }
    } else if (0 < level) {
        qFatal("TODO Implement tree demotion");
    }

    moveSubtree(targetParent, index, targetParentRow);
    // TODO after moving the tree, change the ID and/or  values of the
    // respective fields to account for the new parenting level (for
    // subtrees)
}

void OrgDocumentModel::changePosition(CR<QModelIndex> index, int offset) {
    _qdbg(index);
    _qdbg(offset);
    int move_position = std::clamp<int>(
        index.row() + offset, 0, rowCount(index.parent()) - 1);
    _qdbg(move_position);
    Q_ASSERT(0 <= move_position);
    moveSubtree(index, index.parent(), move_position);
}

void OrgDocumentModel::moveSubtree(
    CR<QModelIndex> moved_index,
    CR<QModelIndex> new_parent,
    int             parent_position) {

    if (new_parent == moved_index.parent()
        && parent_position == moved_index.row()) {
        return;
    }
    qDebug() << "----";
    _qdbg(new_parent);
    _qdbg(moved_index.parent());
    _qdbg(moved_index);
    _qdbg(parent_position);
    _qdbg(moved_index.row());

    Q_ASSERT(0 <= parent_position);

    beginMoveRows(
        moved_index.parent(),
        moved_index.row(),
        moved_index.row(),
        new_parent,
        parent_position);

    Q_ASSERT(moved_index.isValid());
    auto current_parent = tree(moved_index.parent());
    Q_ASSERT(current_parent != nullptr);
    std::unique_ptr<TreeNode> moved_tree = std::move(
        current_parent->subnodes[moved_index.row()]);

    current_parent->subnodes.erase(
        current_parent->subnodes.begin() + moved_index.row());

    auto target_parent = tree(new_parent);
    target_parent->subnodes.insert(
        target_parent->subnodes.begin() + parent_position,
        std::move(moved_tree));

    endMoveRows();
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
    if (0 < parent.column()) {
        return 0;
    } else {
        TreeNode* parentNode = parent.isValid() ? tree(parent)
                                                : root.get();
        Q_ASSERT(parentNode != nullptr);
        auto const& t      = *parentNode;
        auto        result = parentNode->subnodes.size();
        Q_ASSERT(0 <= result);
        return result;
    }
}

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

sem::SemId<sem::Org> OrgDocumentModel::TreeNode::toNode(
    OrgStore* store) const {
    auto base = store->node(this->boxId);
    if (NestedNodes.contains(base->getKind())) {
        auto result = copy(base);
        result->subnodes.clear();
        for (auto const& it : enumerator(subnodes)) {
            auto it_node = store->node(it.value()->boxId);
            result->subnodes.push_back(it.value()->toNode(store));
            if (!it.is_last()) {
                if (it_node->is(OrgSemKind::Paragraph)) {
                    auto nl  = sem::SemId<sem::Newline>::New();
                    nl->text = "\n\n";
                    result->subnodes.push_back(nl);
                }
            }
        }
        return result;
    } else {
        return base;
    }
}
