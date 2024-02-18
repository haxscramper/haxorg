#pragma once
#include "org_qml_node_edit.hpp"
#include <QSortFilterProxyModel>


class OrgDocumentModel : public QAbstractItemModel {
  public:
    enum OrgNodeItemRole
    {
        KindRole = Qt::UserRole + 1,
        DataRole,
        LastExplicitRole,
    };

    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roles;
        roles[KindRole] = "kind";
        roles[DataRole] = "data";
        return roles;
    }

    explicit OrgDocumentModel(
        const sem::SemId<sem::Org>& rootData,
        QObject*                    parent = nullptr)
        : QAbstractItemModel(parent)
        , rootItem(std::make_unique<OrgNodeCursor>(rootData, nullptr)) {}

    ~OrgDocumentModel() override = default;

    QModelIndex index(
        int                row,
        int                column,
        const QModelIndex& parent = QModelIndex()) const override {
        if (!hasIndex(row, column, parent)) {
            return QModelIndex();
        } else {
            OrgNodeCursor* itemParent = parent.isValid()
                                          ? static_cast<OrgNodeCursor*>(
                                              parent.internalPointer())
                                          : rootItem.get();

            OrgNodeCursor* childItem = itemParent->at(row);
            if (childItem) {
                return createIndex(row, column, childItem);
            } else {
                return QModelIndex();
            }
        }
    }

    QModelIndex parent(const QModelIndex& index) const override {
        if (!index.isValid()) {
            return QModelIndex();
        } else {
            OrgNodeCursor* parent = static_cast<OrgNodeCursor*>(
                                        index.internalPointer())
                                        ->getparent();

            if (parent == rootItem.get()) {
                return QModelIndex();
            } else {
                return createIndex(parent->row(), 0, parent);
            }
        }
    }

    int rowCount(
        const QModelIndex& parent = QModelIndex()) const override {
        OrgNodeCursor* itemParent;
        if (parent.column() > 0) {
            return 0;
        } else {
            return parent.isValid() ? static_cast<OrgNodeCursor*>(
                                          parent.internalPointer())
                                          ->size()
                                    : rootItem.get()->size();
        }
    }

    int columnCount(
        const QModelIndex& parent = QModelIndex()) const override {
        if (parent.isValid()) {
            return static_cast<OrgNodeCursor*>(parent.internalPointer())
                ->columnCount();
        } else {
            return rootItem->columnCount();
        }
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)
        const override {

        if (!index.isValid()) { return QVariant(); }

        OrgNodeCursor* item = static_cast<OrgNodeCursor*>(
            index.internalPointer());

        switch (role) {
            case Qt::DisplayRole: {
                return item->data(index.column());
            }

            case OrgNodeItemRole::KindRole: {
                return QString::fromStdString(fmt1(item->node->getKind()));
            }

            case OrgNodeItemRole::DataRole: {
                return item->getNodeHandle();
            }

            default: {
                return QVariant();
            }
        }
    }

  private:
    UPtr<OrgNodeCursor> rootItem;
};


struct OrgDocumentSearchFilter : public QSortFilterProxyModel {
    OrgDocumentSearchFilter(OrgDocumentModel* baseModel) {
        setSourceModel(baseModel);
    }

    sem::SemId<sem::Org> getNode(QModelIndex const& source_index) const {
        OrgNodeCursor* data = static_cast<OrgNodeCursor*>(
            source_index.internalPointer());
        return data->node;
    }

    sem::SemId<sem::Org> getNode(
        int                source_row,
        const QModelIndex& source_parent) const {
        QModelIndex index = sourceModel()->index(
            source_row, 0, source_parent);
        return getNode(index);
    }

    Func<bool(sem::OrgArg)>              acceptNode;
    Func<bool(sem::OrgArg, sem::OrgArg)> nodeLessThan;

    bool lessThan(
        const QModelIndex& source_left,
        const QModelIndex& source_right) const override {
        if (nodeLessThan) {
            return source_left.row() < source_right.row();
        } else {
            return nodeLessThan(
                getNode(source_left), getNode(source_right));
        }
    }

    virtual bool filterAcceptsRow(
        int                source_row,
        const QModelIndex& source_parent) const override {
        if (acceptNode) {
            return acceptNode(getNode(source_row, source_parent));
        } else {
            return true;
        }
    }
};

struct OrgSubtreeSearchModel : QObject {
    Q_OBJECT

  public:
    OrgSubtreeSearchModel(OrgDocumentModel* baseModel);

    OrgDocumentSearchFilter filter;
    UnorderedMap<u64, int>  scoreCache;
    std::string             pattern;
    int                     getScore(sem::OrgArg arg);

    Q_INVOKABLE void setPattern(CR<QString> pattern);
    Q_INVOKABLE void setScoreSorted(bool sorted);
};
