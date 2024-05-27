#pragma once
#include <QSortFilterProxyModel>
#include <QAbstractItemModel>

#include <editor/editor_lib/store/org_document_store.hpp>

#include <hstd/stdlib/Filesystem.hpp>

inline std::string to_std(QString const& value) {
    QByteArray tmp = value.toLatin1();
    return std::string{tmp.data(), static_cast<size_t>(tmp.size())};
}


struct OrgDocumentModel : public QAbstractItemModel {
  private:
    Q_OBJECT

  public:
    OrgTreeNode* root;
    OrgStore*    store;

    sem::SemId<sem::Org> toNode() const { return root->toNode(); }

    OrgTreeNode* tree(CR<QModelIndex> index) const;

    explicit OrgDocumentModel(OrgStore* store, QObject* parent = nullptr);

    ~OrgDocumentModel() override = default;


    void        loadFile(fs::path const& path);
    QModelIndex parent(const QModelIndex& index) const override;
    QVariant    data(const QModelIndex& index, int role) const override;
    QModelIndex index(int row, int column, const QModelIndex& parent)
        const override;

    /// \brief Get model index corresponding for the element with specified
    /// box ID.
    QModelIndex getTreeIndex(CR<OrgBoxId> id) const;
    QModelIndex getTreeIndex(CVec<int> path) const;


    /// Change nesting level of the tree, promoting or demoting it.
    void changeLevel(CR<QModelIndex> index, int level, bool recursive);
    void changePosition(CR<QModelIndex> index, int offset);

    void moveSubtree(
        CR<QModelIndex> moved_index,
        CR<QModelIndex> new_parent,
        int             parent_position);

    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(
        const QModelIndex& parent = QModelIndex()) const override {
        return 1;
    }

    virtual bool setData(
        const QModelIndex& index,
        const QVariant&    value,
        int                role) override;

    bool isMatchingTree(CR<OrgBoxId> params) const {
        return store->getOrgTree(params)->root() == this->root;
    }

    virtual QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> result;
        result[Qt::DisplayRole]   = "DisplayRole";
        result[Qt::WhatsThisRole] = "WhatsThisRole";
        return result;
    }


  public slots:
    void onBeginNodeMove(OrgTreeNode::MoveParams params);
    void onEndNodeMove(OrgTreeNode::MoveParams params);

    void onBeginNodeInsert(OrgTreeNode::InsertParams params);
    void onEndNodeInsert(OrgTreeNode::InsertParams params);
};


struct OrgDocumentSearchFilter : public QSortFilterProxyModel {
    OrgDocumentSearchFilter(OrgDocumentModel* baseModel, QObject* parent)
        : QSortFilterProxyModel(parent) {
        setSourceModel(baseModel);
    }

    OrgBoxId getNode(QModelIndex const& source_index) const {
        OrgBoxId* data = static_cast<OrgBoxId*>(
            source_index.internalPointer());
        return *data;
    }

    OrgBoxId getNode(int source_row, const QModelIndex& source_parent)
        const {
        QModelIndex index = sourceModel()->index(
            source_row, 0, source_parent);
        return getNode(index);
    }

    Func<bool(OrgBoxId)>           acceptNode;
    Func<bool(OrgBoxId, OrgBoxId)> nodeLessThan;

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
    OrgSubtreeSearchModel(
        OrgDocumentModel* baseModel,
        QObject*          parent,
        OrgStore*         store);

    SPtr<OrgDocumentSearchFilter> filter;
    UnorderedMap<u64, int>        scoreCache;
    std::string                   pattern;
    OrgStore*                     store;
    int                           getScore(OrgBoxId arg);

    Q_INVOKABLE void setPattern(CR<QString> pattern);
    Q_INVOKABLE void setScoreSorted(bool sorted);
};
