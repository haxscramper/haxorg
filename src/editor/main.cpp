#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <sem/SemBaseApi.hpp>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QQmlApplicationEngine>
#include <QQmlContext>

class TreeItem {
  public:
    explicit TreeItem(const sem::SemId<sem::Org>& data, TreeItem* parent)
        : node(data), parent(parent) {}

    void push_back(UPtr<TreeItem>&& item) {
        subnodes.push_back(std::move(item));
    }

    TreeItem* at(int row) { return subnodes.at(row).get(); }
    int       size() const { return subnodes.size(); }
    int       columnCount() const { return 1; }

    QVariant data(int column) const {
        if (column == 0) {
            return QString::fromStdString(fmt1(node->getKind()));
        } else {
            return QVariant();
        }
    }

    int row() const {
        if (parent) {
            for (int idx = 0; idx < parent->subnodes.size(); ++idx) {
                if (parent->subnodes[idx]->node.get()
                    == this->node.get()) {
                    return idx;
                }
            }
            return 0;
        } else {
            return 0;
        }
    }

    TreeItem* getparent() { return parent; }

    std::vector<UPtr<TreeItem>> subnodes;
    sem::SemId<sem::Org>        node;
    TreeItem*                   parent;
};

class TreeModel : public QAbstractItemModel {
  public:
    explicit TreeModel(
        const sem::SemId<sem::Org>& rootData,
        QObject*                    parent = nullptr)
        : QAbstractItemModel(parent)
        , rootItem(std::make_unique<TreeItem>(rootData, nullptr)) {
        setupModelData(rootItem, rootData);
    }

    void setupModelData(
        UPtr<TreeItem>&      parent,
        sem::SemId<sem::Org> orgData) {
        for (const auto& subnode : orgData->subnodes) {
            auto& sub = parent->subnodes.emplace_back(
                std::make_unique<TreeItem>(subnode, parent.get()));
            setupModelData(sub, subnode);
        }
    }

    ~TreeModel() override = default;

    QModelIndex index(
        int                row,
        int                column,
        const QModelIndex& parent = QModelIndex()) const override {
        if (!hasIndex(row, column, parent)) {
            return QModelIndex();
        } else {
            TreeItem* itemParent = parent.isValid()
                                     ? static_cast<TreeItem*>(
                                         parent.internalPointer())
                                     : rootItem.get();

            TreeItem* childItem = itemParent->at(row);
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
            TreeItem* parent = static_cast<TreeItem*>(
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
        TreeItem* itemParent;
        if (parent.column() > 0) {
            return 0;
        } else {
            return parent.isValid()
                     ? static_cast<TreeItem*>(parent.internalPointer())
                           ->size()
                     : rootItem.get()->size();
        }
    }

    int columnCount(
        const QModelIndex& parent = QModelIndex()) const override {
        if (parent.isValid()) {
            return static_cast<TreeItem*>(parent.internalPointer())
                ->columnCount();
        } else {
            return rootItem->columnCount();
        }
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)
        const override {
        if (!index.isValid()) {
            return QVariant();
        } else if (role != Qt::DisplayRole) {
            return QVariant();
        } else {
            TreeItem* item = static_cast<TreeItem*>(
                index.internalPointer());
            return item->data(index.column());
        }
    }

  private:
    UPtr<TreeItem> rootItem;
};

int main(int argc, char* argv[]) {
    auto document = org::parseString(
        readFile("/home/haxscramper/tmp/doc1.org"));

    QGuiApplication       app(argc, argv);
    QQmlApplicationEngine engine;
    TreeModel             model{document};
    engine.rootContext()->setContextProperty("documentModel", &model);

    const QUrl url(u"qrc:/editor/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
