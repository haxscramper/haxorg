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


namespace org_qml {
#define _case(__Kind)                                                     \
    template <>                                                           \
    struct serde<::org_qml::__Kind, ::sem::SemId<::sem::__Kind>> {        \
        using qml_type = ::org_qml::__Kind;                               \
        using cxx_type = ::sem::SemId<::sem::__Kind>;                     \
        static qml_type cxx_to_qml(cxx_type value) {                      \
            return qml_type{value};                                       \
        }                                                                 \
        static cxx_type qml_to_cxx(qml_type value) {                      \
            return value.__data.as<::sem::__Kind>();                      \
        }                                                                 \
    };

EACH_SEM_ORG_KIND(_case)
#undef _case
} // namespace org_qml


class OrgNodeItem {
  public:
    explicit OrgNodeItem(
        const sem::SemId<sem::Org>& data,
        OrgNodeItem*                parent)
        : node(data), parent(parent) {}

    void push_back(UPtr<OrgNodeItem>&& item) {
        subnodes.push_back(std::move(item));
    }

    OrgNodeItem* at(int row) { return subnodes.at(row).get(); }
    int          size() const { return subnodes.size(); }
    int          columnCount() const { return 1; }

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

    OrgNodeItem* getparent() { return parent; }

    std::vector<UPtr<OrgNodeItem>> subnodes;
    sem::SemId<sem::Org>           node;
    OrgNodeItem*                   parent;

    QVariant getNodeRich() {
        return QVariant::fromValue(OrgNodeTextWrapper{node});
    }

    QVariant getNodeHandle() {
        switch (node->getKind()) {
#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind:                                              \
        return QVariant::fromValue(                                       \
            org_qml::serde<org_qml::__Kind, sem::SemId<sem::__Kind>>::    \
                cxx_to_qml(node.as<sem::__Kind>()));

            EACH_SEM_ORG_KIND(_case)
#undef _case
        }
    }
};

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
        , rootItem(std::make_unique<OrgNodeItem>(rootData, nullptr)) {
        setupModelData(rootItem, rootData);
    }

    void setupModelData(
        UPtr<OrgNodeItem>&   parent,
        sem::SemId<sem::Org> orgData) {
        for (const auto& subnode : orgData->subnodes) {
            auto& sub = parent->subnodes.emplace_back(
                std::make_unique<OrgNodeItem>(subnode, parent.get()));
            setupModelData(sub, subnode);
        }
    }

    ~OrgDocumentModel() override = default;

    QModelIndex index(
        int                row,
        int                column,
        const QModelIndex& parent = QModelIndex()) const override {
        if (!hasIndex(row, column, parent)) {
            return QModelIndex();
        } else {
            OrgNodeItem* itemParent = parent.isValid()
                                        ? static_cast<OrgNodeItem*>(
                                            parent.internalPointer())
                                        : rootItem.get();

            OrgNodeItem* childItem = itemParent->at(row);
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
            OrgNodeItem* parent = static_cast<OrgNodeItem*>(
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
        OrgNodeItem* itemParent;
        if (parent.column() > 0) {
            return 0;
        } else {
            return parent.isValid()
                     ? static_cast<OrgNodeItem*>(parent.internalPointer())
                           ->size()
                     : rootItem.get()->size();
        }
    }

    int columnCount(
        const QModelIndex& parent = QModelIndex()) const override {
        if (parent.isValid()) {
            return static_cast<OrgNodeItem*>(parent.internalPointer())
                ->columnCount();
        } else {
            return rootItem->columnCount();
        }
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)
        const override {

        if (!index.isValid()) { return QVariant(); }

        OrgNodeItem* item = static_cast<OrgNodeItem*>(
            index.internalPointer());

        switch (role) {
            case Qt::DisplayRole: {
                OrgNodeItem* item = static_cast<OrgNodeItem*>(
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
    UPtr<OrgNodeItem> rootItem;
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
