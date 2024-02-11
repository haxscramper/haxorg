#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <sem/SemBaseApi.hpp>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <any>
#include <absl/log/log.h>

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
};

class OrgDocumentModel : public QAbstractItemModel {
  public:
    enum OrgNodeItemRole
    {
        KindRole = Qt::UserRole + 1,
        LastExplicitRole,
    };

    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roles;
        for (auto const& [idx, name] : fieldRoles) {
            // qt has some very weird relationship with the std-string
            // related converters (linker errors due to ABI differences
            // with stdc++ from llvm), so converting from raw data here
            roles[idx] = QByteArray::fromRawData(
                name.byteData.data(), name.byteData.size());
        }
        roles[KindRole] = "kind";
        return roles;
    }

    struct OrgFieldExpose {
        OrgSemKind  typeKind;
        Str         fieldName;
        std::any    fieldPtr;
        std::string byteData;
    };

    UnorderedMap<int, OrgFieldExpose> fieldRoles;

    explicit OrgDocumentModel(
        const sem::SemId<sem::Org>& rootData,
        QObject*                    parent = nullptr)
        : QAbstractItemModel(parent)
        , rootItem(std::make_unique<OrgNodeItem>(rootData, nullptr)) {
        setupModelData(rootItem, rootData);

#define _case(__Kind)                                                     \
    {                                                                     \
        int fieldIdx = 0;                                                 \
        for_each_field_with_bases<sem::__Kind>([&](auto const& field) {   \
            int roleIdx = OrgNodeItemRole::LastExplicitRole + 1           \
                        + (int)(OrgSemKind::__Kind) * 100 + fieldIdx;     \
            std::string value = fmt(                                      \
                "{}_{}", OrgSemKind::__Kind, field.name);                 \
                                                                          \
            fieldRoles[roleIdx] = OrgFieldExpose{                         \
                OrgSemKind::__Kind,                                       \
                field.name,                                               \
                std::any{field.pointer},                                  \
                value,                                                    \
            };                                                            \
            ++fieldIdx;                                                   \
        });                                                               \
    }

        EACH_SEM_ORG_KIND(_case)
#undef _case
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
            default: {
                if (fieldRoles.contains(role)) {
                    auto const& expose = fieldRoles.at(role);

                    QVariant result{};

                    auto aux = [&]<typename T>(sem::SemId<T> node) {
                        for_each_field_with_bases<T>([&](auto const&
                                                             field) {
                            using FieldType = decltype(field.pointer);
                            if (typeid(FieldType) == expose.fieldPtr.type()
                                && field.pointer
                                       == std::any_cast<FieldType>(
                                           expose.fieldPtr)) {
                                auto fieldValue = static_cast<T*>(
                                                      node.get())
                                                      ->*field.pointer;
                                using FieldValueType = std::remove_cvref_t<
                                    decltype(fieldValue)>;
                                if constexpr (std::is_convertible_v<
                                                  FieldValueType,
                                                  QVariant>) {
                                    result = fieldValue;
                                } else if constexpr (std::is_same_v<
                                                         FieldValueType,
                                                         Str>) {
                                    result = QString::fromStdString(
                                        fieldValue);
                                }
                            }
                        });
                    };

                    switch (expose.typeKind) {
#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: {                                            \
        if (item->node->is(expose.typeKind)) {                            \
            aux(item->node.as<sem::__Kind>());                            \
        } else {                                                          \
            LOG(ERROR) << fmt(                                            \
                "Requesting invalid role for type {}.{}",                 \
                expose.typeKind,                                          \
                expose.fieldName);                                        \
        }                                                                 \
        break;                                                            \
    }

                        EACH_SEM_ORG_KIND(_case)
#undef _case
                    }

                    if (result.isValid()) {
                        return result;
                    } else {
                        return QVariant();
                    }


                } else {
                    return QVariant();
                }
            }
        }
    }

  private:
    UPtr<OrgNodeItem> rootItem;
};

int main(int argc, char* argv[]) {
    auto document = org::parseString(
        readFile("/home/haxscramper/tmp/doc1.org"));

    QGuiApplication       app(argc, argv);
    QQmlApplicationEngine engine;
    OrgDocumentModel      model{document};
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
