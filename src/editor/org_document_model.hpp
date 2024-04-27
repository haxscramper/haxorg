#pragma once
#include <QSortFilterProxyModel>
#include <QAbstractItemModel>
#include <sem/SemOrg.hpp>
#include <immer/box.hpp>
#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/Filesystem.hpp>

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

    sem::SemId<sem::Org> node(CR<OrgBoxId> id) {
        return data.at(id).node();
    }

    UnorderedMap<OrgBoxId, OrgBox> data{};
    OrgStore() {}
};

struct OrgDocumentModel : public QAbstractItemModel {
    OrgStore* store;

    struct TreeNode {
        OrgBoxId            boxId;
        Vec<UPtr<TreeNode>> children;
        TreeNode*           parent;

        TreeNode(OrgBoxId id, TreeNode* pParent = nullptr)
            : boxId(id), parent(pParent) {}
    };

    UPtr<TreeNode> root;

    explicit OrgDocumentModel(OrgStore* store, QObject* parent = nullptr)
        : QAbstractItemModel(parent), store(store) {}

    ~OrgDocumentModel() override = default;

    void loadFile(fs::path const& path);

    void buildTree(TreeNode* parentNode) {
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

    QModelIndex index(int row, int column, const QModelIndex& parent)
        const override {
        if (!hasIndex(row, column, parent)) { return QModelIndex(); }

        TreeNode* parentNode = !parent.isValid()
                                 ? root.get()
                                 : static_cast<TreeNode*>(
                                     parent.internalPointer());
        TreeNode* childNode  = parentNode->children.at(row).get();
        if (childNode) { return createIndex(row, column, childNode); }
        return QModelIndex();
    }

    QModelIndex parent(const QModelIndex& index) const override {
        if (!index.isValid()) { return QModelIndex(); }

        TreeNode* childNode = static_cast<TreeNode*>(
            index.internalPointer());
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

    int rowCount(
        const QModelIndex& parent = QModelIndex()) const override {
        if (parent.column() > 0) { return 0; }

        TreeNode* parentNode = !parent.isValid()
                                 ? root.get()
                                 : static_cast<TreeNode*>(
                                     parent.internalPointer());
        return parentNode->children.size();
    }

    int columnCount(
        const QModelIndex& parent = QModelIndex()) const override {
        return 1;
    }

    QVariant data(const QModelIndex& index, int role) const override;
};


struct OrgDocumentSearchFilter : public QSortFilterProxyModel {
    OrgDocumentSearchFilter(OrgDocumentModel* baseModel, QObject* parent)
        : QSortFilterProxyModel(parent) {
        setSourceModel(baseModel);
    }

    virtual ~OrgDocumentSearchFilter() { __builtin_debugtrap(); };

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
