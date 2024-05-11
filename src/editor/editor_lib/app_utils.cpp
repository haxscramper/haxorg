#include <editor/editor_lib/app_utils.hpp>
#include <hstd/stdlib/Enumerate.hpp>
#include <hstd/stdlib/Map.hpp>
#include <exporters/ExporterUltraplain.hpp>
#include <exporters/ExporterJson.hpp>
#include <hstd/stdlib/algorithms.hpp>

Q_LOGGING_CATEGORY(editor, "editor");
/// Logging related to the editable document model in the tree or outline
Q_LOGGING_CATEGORY(editor_model, "editor.model");
/// Logging for operations and diagnostics with files -- opening, closing,
/// parsing etc.
Q_LOGGING_CATEGORY(editor_files, "editor.files");


QModelIndex mapToNestedSource(const QModelIndex& index) {
    QModelIndex currentIndex = index;
    auto currentProxyModel   = qobject_cast<QSortFilterProxyModel const*>(
        index.model());

    while (currentProxyModel) {
        Q_ASSERT_X(
            currentIndex.model() == currentProxyModel,
            "mapToNestedSource",
            fmt("Index to wrong model passed to mapToSource: index is {}, "
                "model is {}",
                qdebug_to_str(currentIndex),
                qdebug_to_str(currentProxyModel)));

        currentIndex      = currentProxyModel->mapToSource(currentIndex);
        currentProxyModel = qobject_cast<QSortFilterProxyModel const*>(
            currentProxyModel->sourceModel());
    }

    return currentIndex;
}

QModelIndex mapToNestedProxy(
    const QModelIndex&          index,
    Vec<QSortFilterProxyModel*> proxies) {
    QModelIndex currentIndex = index;

    for (QSortFilterProxyModel* proxyModel : proxies) {
        currentIndex = proxyModel->mapFromSource(currentIndex);
    }

    return currentIndex;
}

inline ColText escape_literal(ColText const& in) {
    ColText res;
    res.reserve(in.size() + 2);
    res.append(ColText{"«"});
    for (ColRune const& c : in) {
        if (c.rune == "\n") {
            res.append({"␤"});

        } else {
            res.append(c);
        }
    }

    res.append(ColText{"»"});

    return res;
}

ColText printModelTree(
    const QAbstractItemModel*         model,
    const QModelIndex&                parent,
    Func<ColText(QModelIndex const&)> toString,
    bool                              ignoreExceptions) {
    if (!model) { return ColText{""}; }

    struct ModelProxyRecord {
        QModelIndex index;
    };

    struct IndexRoleRepr {
        Str roleName;
        Str roleValue;
    };

    struct ModelLevelRecord {
        int                   depth;
        Vec<ModelProxyRecord> proxies;
        ColText               finalRepr;
        Vec<IndexRoleRepr>    roles;
    };

    Vec<ModelLevelRecord> records;

    QHash<int, QByteArray> role_names = model->roleNames();

    for (auto const& it : role_names.keys()) {
        if (it != Qt::DisplayRole && it < Qt::UserRole) {
            role_names.remove(it);
        }
    }

    Func<void(CR<QModelIndex> index, int level)> aux;
    aux = [&](CR<QModelIndex> index, int level) -> void {
        ModelLevelRecord record{.depth = level};

        QModelIndex currentIndex      = index;
        auto        currentProxyModel = qobject_cast<
                   QSortFilterProxyModel const*>(index.model());
        Vec<int> roles = sorted(
            role_names.keys() | rs::to<Vec>(), std::less_equal<int>{});


        for (int role : roles) {
            QByteArray    role_name = role_names[role];
            IndexRoleRepr repr;
            repr.roleName = role_name.toStdString();
            auto act      = [&]() {
                QVariant value = index.data(role);
                if (value.isValid()) {

                    if (value.typeName() == "QString"_ss) {
                        repr.roleValue = value.toString().toStdString();
                    } else {
                        repr.roleValue = qdebug_to_str(value);
                    }
                    record.roles.push_back(repr);
                }
            };

            try {
                if (ignoreExceptions) {
                    try {
                        act();
                    } catch (std::exception& ex) {
                        repr.roleValue = fmt(
                            "Exception {} {}",
                            typeid(ex).name(),
                            ex.what());
                        record.roles.push_back(repr);
                    }
                } else {
                    act();
                }
            } catch (model_role_not_implemented const& ex) {
                repr.roleValue = fmt("Role not implemented {}", ex.what());
                record.roles.push_back(repr);
            }
        }

        auto add_proxy = [&](CR<QModelIndex> index) {
            record.proxies.push_back(ModelProxyRecord{.index = index});
        };

        add_proxy(currentIndex);

        while (currentProxyModel) {
            auto mapped  = currentProxyModel->mapToSource(currentIndex);
            currentIndex = mapped;
            add_proxy(currentIndex);
            currentProxyModel = qobject_cast<QSortFilterProxyModel const*>(
                currentProxyModel->sourceModel());
        }

        record.finalRepr = toString(index);
        records.push_back(record);

        int rowCount = model->rowCount(index);
        for (int row = 0; row < rowCount; ++row) {
            QModelIndex sub = model->index(row, 0, index);
            aux(sub, level + 1);
        }
    };

    aux(parent, 0);

    ColStream os;

    UnorderedMap<QAbstractItemModel const*, Str> model_names;
    for (auto const& level : records) {
        for (auto const& proxy : level.proxies) {
            if (!model_names.contains(proxy.index.model())) {
                if (proxy.index.model() == nullptr) {
                    model_names.insert_or_assign(
                        proxy.index.model(), "0x0");
                } else if (proxy.index.model()->objectName().isEmpty()) {
                    model_names.insert_or_assign(
                        proxy.index.model(),
                        fmt("M{}", model_names.size()));
                } else {
                    model_names.insert_or_assign(
                        proxy.index.model(),
                        proxy.index.model()->objectName().toStdString());
                }
            }
        }
    }

    for (auto const& level : enumerator(records)) {
        auto const& l = level.value();
        os << std::string(l.depth * 2, ' ');
        for (auto const& proxy : enumerator(l.proxies)) {
            if (proxy.is_first()) {
                os << " ";
            } else {
                os << "->";
            }

            auto const& p = proxy.value();
            os << "["
               //
               << os.cyan() << fmt1(p.index.row()) << os.end() << ":"
               << os.cyan() << fmt1(p.index.column()) << os.end()
               << ","
               //
               << os.green() << fmt("@{:p}", p.index.internalPointer())
               << os.end()
               //
               << ", " << os.red() << model_names.at(p.index.model())
               << os.end() << "]";
            ;
        }

        os << " " << ColText{escape_literal(l.finalRepr)};

        for (auto const& role : l.roles) {
            os << "\n";
            os << std::string(l.depth * 2 + 3, ' ');
            os << os.green() << role.roleName << os.end() << " = ";
            if (role.roleValue.contains("\n")) {
                os << "\n";
                auto lines = role.roleValue.split("\n");
                for (auto const& line : enumerator(lines)) {
                    os << Str(" ").repeated(l.depth * 2 + 3) << "| "
                       << os.yellow() << line.value() << os.end();
                    if (!line.is_last()) { os << "\n"; }
                }
            } else {
                os << os.yellow() << role.roleValue << os.end();
            }
        }

        if (!level.is_last()) { os << "\n"; }
    }

    return os.getBuffer();
}

Func<ColText(const QModelIndex&)> store_index_printer(
    OrgStore const* store,
    int             role) {
    return [store, role](QModelIndex const& idx) -> ColText {
        OrgBoxId box = qvariant_cast<OrgBoxId>(idx.data(role));
        if (store->data.contains(box)) {
            auto    node   = store->node(box);
            ColText result = fmt("{}", node->getKind());
            if (node->is(OrgSemKind::Paragraph)) {
                result.append(ColText{" '"});
                auto str = ExporterUltraplain::toStr(node);
                result.append(ColText{
                    str.substr(0, std::clamp<int>(40, 0, str.size()))});
                if (40 < str.size()) { result.append(ColText{"..."}); }
                result.append(ColText{"'"});
            }

            return result;
        } else {
            return fmt("[err:{}]", box.value);
        }
    };
}

Str debug(sem::OrgArg arg) {
    ExporterJson exporter;
    exporter.skipEmptyLists = true;
    exporter.skipNullFields = true;
    json converted          = exporter.evalTop(arg);
    filterFields(converted, {"loc"});
    return converted.dump();
}

std::string qdebug_obj(const QObject* obj) {
    std::stringstream os;
    os << fmt("QObj{:p}", (void*)obj);
    if (!obj->objectName().isEmpty()) {
        os << " name:" << obj->objectName().toStdString();
    }

    return os.str();
}
