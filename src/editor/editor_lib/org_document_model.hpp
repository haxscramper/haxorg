#pragma once
#include <QSortFilterProxyModel>
#include <QAbstractItemModel>
#include <sem/SemOrg.hpp>
#include <immer/box.hpp>
#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <QMimeData>
#include <QIODevice>

inline std::string to_std(QString const& value) {
    QByteArray tmp = value.toLatin1();
    return std::string{tmp.data(), static_cast<size_t>(tmp.size())};
}

struct OrgBox {
    immer::box<sem::SemId<sem::Org>> boxed;
    OrgBox(sem::SemId<sem::Org> node) : boxed(node) {}

    sem::Org const&      operator*() { return *boxed.get().get(); }
    sem::Org const*      operator->() { return boxed.get().get(); }
    sem::SemId<sem::Org> node() const { return boxed.get(); }
    OrgBox() : boxed(sem::SemId<sem::Org>::Nil()) {}
};

struct OrgBoxId {
    int      value = 0;
    OrgBoxId next() const { return OrgBoxId{value + 1}; }
    OrgBoxId(int value = 0) : value(value){};

    bool operator==(OrgBoxId const& other) const {
        return this->value == other.value;
    }
};


inline QDataStream& operator<<(QDataStream& out, const OrgBoxId& myObj) {
    return out << myObj.value;
}

inline QDataStream& operator>>(QDataStream& in, OrgBoxId& myObj) {
    return in >> myObj.value;
}

Q_DECLARE_METATYPE(OrgBoxId);

template <>
struct std::hash<OrgBoxId> {
    std::size_t operator()(OrgBoxId const& it) const noexcept {
        std::size_t result = 0;
        boost::hash_combine(result, it.value);
        return result;
    }
};


sem::SemId<sem::Org> copy(sem::OrgArg node);

struct OrgStore {
    OrgBoxId lastId{0};
    OrgBoxId add(sem::OrgArg node) {
        auto id  = lastId.next();
        data[id] = OrgBox{node};
        lastId   = id;
        return id;
    }

    sem::SemId<sem::Org> node(CR<OrgBoxId> id) const {
        return data.at(id).node();
    }

    UnorderedMap<OrgBoxId, OrgBox> data{};
    OrgStore() {}
};

struct OrgDocumentModel : public QAbstractItemModel {
    struct TreeNode {
        OrgBoxId            boxId{};
        Vec<UPtr<TreeNode>> subnodes;
        TreeNode*           parent;

        TreeNode(OrgBoxId id, TreeNode* pParent = nullptr)
            : boxId(id), parent(pParent) {}

        sem::SemId<sem::Org> toNode(OrgStore* store) const;
    };

    UPtr<TreeNode> root;
    OrgStore*      store;

    sem::SemId<sem::Org> toNode() const { return root->toNode(store); }

    TreeNode* tree(CR<QModelIndex> index) const {
        return static_cast<TreeNode*>(index.internalPointer());
    }

    explicit OrgDocumentModel(OrgStore* store, QObject* parent = nullptr)
        : QAbstractItemModel(parent), store(store) {}

    ~OrgDocumentModel() override = default;


    void        loadFile(fs::path const& path);
    void        buildTree(TreeNode* parentNode);
    QModelIndex parent(const QModelIndex& index) const override;
    QVariant    data(const QModelIndex& index, int role) const override;
    QModelIndex index(int row, int column, const QModelIndex& parent)
        const override;

    /// Change nesting level of the tree, promoting or demoting it.
    void changeLevel(CR<QModelIndex> index, int level);

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
