#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <sem/SemBaseApi.hpp>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <absl/log/log.h>
#include <org_qml.hpp>
#include "org_qml_node_edit.hpp"




class OrgDocumentModel : public QAbstractItemModel {
  public:
    enum OrgNodeItemRole
    {
        KindRole = Qt::UserRole + 1,
        DataRole,
        RichTextRole,
        LastExplicitRole,
    };

    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roles;
        roles[KindRole]     = "kind";
        roles[DataRole]     = "data";
        roles[RichTextRole] = "rich";
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
                OrgNodeCursor* item = static_cast<OrgNodeCursor*>(
                    index.internalPointer());
                return item->data(index.column());
            }

            case OrgNodeItemRole::KindRole: {
                return QString::fromStdString(fmt1(item->node->getKind()));
            }

            case OrgNodeItemRole::RichTextRole: {
                return item->getNodeRich();
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


int main(int argc, char* argv[]) {
    OrgBackend backend;
    backend.document = org::parseString(
        readFile("/home/haxscramper/tmp/doc1.org"));

    QGuiApplication       app(argc, argv);
    QQmlApplicationEngine engine;
    OrgDocumentModel      model{backend.document};
    engine.rootContext()->setContextProperty("documentModel", &model);
    engine.rootContext()->setContextProperty("backend", &backend);

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
