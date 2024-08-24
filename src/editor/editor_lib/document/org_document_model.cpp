#include "org_document_model.hpp"
#include <hstd/stdlib/diffs.hpp>
#include <haxorg/exporters/ExporterUltraplain.hpp>
#include <haxorg/sem/SemBaseApi.hpp>
#include <QLabel>
#include <QDebug>
#include <hstd/stdlib/Enumerate.hpp>
#include <editor/editor_lib/common/app_utils.hpp>

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
        auto const& node     = this->store->getBoxedNode(arg);
        bool        score_ok = pattern.empty() || -1 < getScore(arg);
        bool        result   = node->is(OrgSemKind::Document)
                   || (node->is(OrgSemKind::Subtree) && score_ok);
        return result;
    };

    setScoreSorted(true);
}

int OrgSubtreeSearchModel::getScore(OrgBoxId arg) {
    auto const& node = store->getBoxedNode(arg);
    u64         addr = (u64)node.get();
    if (!scoreCache.contains(addr)) {
        FuzzyMatcher matcher;
        std::string  title = ExporterUltraplain::toStr(
            node.as<sem::Subtree>()->title);
        // scoreCache[addr] = matcher.get_score(title, pattern);
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

OrgTreeNode* OrgDocumentModel::tree(CR<QModelIndex> index) const {
    return static_cast<OrgTreeNode*>(
        mapToNestedSource(index).internalPointer());
}

OrgDocumentModel::OrgDocumentModel(OrgStore* store, QObject* parent)
    : QAbstractItemModel(parent), store(store) {
    Q_ASSERT(connect(
        store,
        &OrgStore::beginNodeMove,
        this,
        &OrgDocumentModel::onBeginNodeMove,
        Qt::UniqueConnection));
    Q_ASSERT(connect(
        store,
        &OrgStore::endNodeMove,
        this,
        &OrgDocumentModel::onEndNodeMove,
        Qt::UniqueConnection));

    Q_ASSERT(connect(
        store,
        &OrgStore::beginNodeInsert,
        this,
        &OrgDocumentModel::onBeginNodeInsert,
        Qt::UniqueConnection));
    Q_ASSERT(connect(
        store,
        &OrgStore::endNodeInsert,
        this,
        &OrgDocumentModel::onEndNodeInsert,
        Qt::UniqueConnection));
}

void OrgDocumentModel::loadFile(const fs::path& path) {
    auto document = sem::parseFile(path, sem::OrgParseParameters{});
    this->root    = store->addRoot(document);
}


QModelIndex OrgDocumentModel::index(
    int                row,
    int                column,
    const QModelIndex& parent) const {
    if (hasIndex(row, column, parent)) {
        if (parent.isValid()) {
            auto node = tree(parent)->at(row);
            Q_ASSERT(node != nullptr);
            return createIndex(row, column, node);
        } else {
            return createIndex(row, column, root);
        }
    } else {
        return QModelIndex();
    }
}

QModelIndex OrgDocumentModel::getTreeIndex(CR<OrgBoxId> id) const {
    auto path = store->getOrgTree(id)->selfPath();
    return getTreeIndex(path);
}

QModelIndex OrgDocumentModel::getTreeIndex(CVec<int> path) const {
    QModelIndex result = index(0, 0, QModelIndex());
    for (int i : path) {
        Q_ASSERT(i < rowCount(result));
        result = index(i, 0, result);
        Q_ASSERT(result.isValid());
    }

    Q_ASSERT(result.isValid());
    return result;
}

void OrgDocumentModel::changeLevel(
    CR<QModelIndex> index,
    int             level,
    bool            recursive) {
    if (recursive) {
        QModelIndex targetParent    = index;
        int         targetParentRow = 0;
        int         levelChange     = 0;

        // TODO change for the tree kind
        if (0 < level) {
            int abs_level = -level;
            if (index.row() == 0) {
                // Current subtree is the first one in the list, promotion
                // will not introduce any parents
                qCDebug(editor_model) << fmt(
                    "index {} is at row 0, demoting without movement",
                    qdebug_to_str(index));
                ++levelChange;
            } else {
                targetParent    = index.siblingAtRow(index.row() - 1);
                targetParentRow = rowCount(targetParent);
                qCDebug(editor_model) << fmt(
                    "index {} is not first, parent {} target row {}",
                    qdebug_to_str(index),
                    qdebug_to_str(targetParent),
                    targetParentRow);
                ++levelChange;

                for (int i = 1; i < abs_level; ++i) {
                    targetParent = this->index(
                        rowCount(targetParent) - 1, 0, targetParent);
                    targetParentRow = rowCount(targetParent);

                    qCDebug(editor_model)
                        << fmt("nesting level {} under {} target row {}",
                               i,
                               qdebug_to_str(targetParent),
                               targetParentRow);
                    ++levelChange;
                }
            }

        } else if (level < 0) {
            for (int i = 0; i < level; ++i) {
                if (targetParent.parent().isValid()) {
                    qCDebug(editor_model)
                        << fmt("{} has valid parent {}, parent row is {}",
                               qdebug_to_str(targetParent),
                               qdebug_to_str(targetParent.parent()),
                               targetParent.row());

                    targetParentRow = targetParent.row();
                    targetParent    = targetParent.parent();
                    --levelChange;
                } else {
                    break;
                }
            }
        } else {
            return;
        }

        moveSubtree(index, targetParent, targetParentRow);
        if (levelChange != 0) {
            Func<void(QModelIndex const&)> aux;
            aux = [&](QModelIndex const& parent) {
                if (store->getBoxedNode(tree(parent)->boxId)
                        ->is(OrgSemKind::Subtree)) {
                    OrgTreeNode* node = tree(parent);
                    node->boxId       = store->update<sem::Subtree>(
                        node->boxId, [&](sem::Subtree& subtree) {
                            subtree.level = subtree.level + levelChange;
                        });
                }

                for (int i = 0; i < rowCount(parent); ++i) {
                    auto nested = this->index(i, 0, parent);
                    aux(nested);
                }
            };

            aux(index);
        }
    } else {
        qFatal("Change tree in a non-recursive manner");
    }
}

void OrgDocumentModel::changePosition(CR<QModelIndex> index, int offset) {
    auto moved = tree(index);
    moved->apply(moved->getShiftParams(offset));
}


void OrgDocumentModel::moveSubtree(
    CR<QModelIndex> moved_index,
    CR<QModelIndex> new_parent,
    int             parent_position) {

    auto moved = tree(moved_index);
    moved->apply(moved->getMoveParams(tree(new_parent), parent_position));
}

QModelIndex OrgDocumentModel::parent(const QModelIndex& index) const {
    if (!index.isValid()) { return QModelIndex(); }

    OrgTreeNode* childNode = static_cast<OrgTreeNode*>(
        index.internalPointer());
    OrgTreeNode* parentNode = childNode->parent;

    if (parentNode == nullptr) {
        return QModelIndex();
    } else {
        int row = parentNode->parent
                    ? std::find_if(
                          parentNode->parent->subnodes.begin(),
                          parentNode->parent->subnodes.end(),
                          [&](CR<UPtr<OrgTreeNode>> node) {
                              return node.get() == parentNode;
                          })
                          - parentNode->parent->subnodes.begin()
                    : 0;
        return createIndex(row, 0, parentNode);
    }
}

int OrgDocumentModel::rowCount(const QModelIndex& parent) const {
    if (0 < parent.column()) {
        return 0;
    } else if (parent.isValid()) {
        OrgTreeNode* parentNode = tree(parent);
        Q_ASSERT(parentNode != nullptr);
        auto const& t      = *parentNode;
        auto        result = parentNode->subnodes.size();
        Q_ASSERT(0 <= result);
        return result;
    } else {
        return 1;
    }
}

QVariant OrgDocumentModel::data(const QModelIndex& index, int role) const {
    if (role == Qt::WhatsThisRole) {
        if (index.isValid()) {
            OrgTreeNode* node = static_cast<OrgTreeNode*>(
                index.internalPointer());
            if (node == nullptr) {
                return QString::fromStdString(
                    fmt("nullptr internal node:{}", qdebug_to_str(index)));
            } else {
                return QString::fromStdString(
                    fmt("index:{}, self-path:{}, self-row:{}",
                        qdebug_to_str(index),
                        node->selfPath(),
                        node->selfRow()));
            }
            return QVariant::fromValue(node->boxId);
        } else {
            return QString::fromStdString(
                fmt("invalid index:{}", qdebug_to_str(index)));
        }
    } else if (index.isValid()) {
        Q_ASSERT(index.internalPointer() != nullptr);
        OrgTreeNode* node = static_cast<OrgTreeNode*>(
            index.internalPointer());
        return QVariant::fromValue(node->boxId);
    } else {
        return QVariant();
    }
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
        OrgTreeNode* node = tree(index);
        if (value.typeId() == QMetaType::type("OrgBoxId")) {
            node->boxId = qvariant_cast<OrgBoxId>(value);
        } else {
            QString text = value.toString();
            if (text.isEmpty()) {
                qCDebug(editor_model)
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

void OrgDocumentModel::onBeginNodeMove(OrgTreeNode::MoveParams params) {
    if (isMatchingTree(params.sourceParent)
        && isMatchingTree(params.destinationParent)) {
        QModelIndex destinationParent = getTreeIndex(
            params.destinationParent);
        QModelIndex sourceParent = getTreeIndex(params.sourceParent);
        Q_ASSERT(sourceParent.isValid());
        Q_ASSERT(destinationParent.isValid());
        Q_ASSERT_X(
            beginMoveRows(
                sourceParent,
                params.sourceFirst,
                params.sourceLast,
                destinationParent,
                params.destinationRow),
            "onBeginNodeMove",
            fmt("Could not execute subtree move with provided "
                "parameters "
                "destinationChild = {} "
                "params.sourceFirst = {} "
                "params.sourceLast = {} "
                "destinationParent = {}",
                params.destinationRow,
                params.sourceFirst,
                params.sourceLast,
                qdebug_to_str(destinationParent)));
    } else {
        _qfmt("move params mismatched:{}", params);
    }
}

void OrgDocumentModel::onEndNodeMove(OrgTreeNode::MoveParams params) {
    if (isMatchingTree(params.sourceParent)
        && isMatchingTree(params.destinationParent)) {
        endMoveRows();
    } else {
        _qfmt("move params mismatched:{}", params);
    }
}

void OrgDocumentModel::onBeginNodeInsert(
    OrgTreeNode::InsertParams params) {
    if (isMatchingTree(params.parent)) {
        beginInsertRows(
            getTreeIndex(params.parent), params.first, params.last);
    }
}

void OrgDocumentModel::onEndNodeInsert(OrgTreeNode::InsertParams params) {
    if (isMatchingTree(params.parent)) { endInsertRows(); }
}
