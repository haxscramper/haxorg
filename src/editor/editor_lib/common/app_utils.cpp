#include <editor/editor_lib/common/app_utils.hpp>
#include <hstd/stdlib/Enumerate.hpp>
#include <hstd/stdlib/Map.hpp>
#include <haxorg/exporters/ExporterUltraplain.hpp>
#include <haxorg/exporters/ExporterJson.hpp>
#include <hstd/stdlib/algorithms.hpp>
#include <QMainWindow>
#include <QApplication>
#include <QScreen>
#include <QWindow>
#include <boost/stacktrace.hpp>
#include <sys/ptrace.h>

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

        // Proxy model might potentially create indices that are not backed
        // by any source model elements.
        if (currentIndex.internalPointer() == nullptr) {
            break;
        } else {
            currentIndex = currentProxyModel->mapToSource(currentIndex);
            currentProxyModel = qobject_cast<QSortFilterProxyModel const*>(
                currentProxyModel->sourceModel());
        }
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


namespace {
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

void recurse_tree(
    CR<QModelIndex>                        index,
    int                                    level,
    QHash<int, QByteArray> const&          role_names,
    Vec<ModelLevelRecord>&                 records,
    bool                                   ignoreExceptions,
    const QAbstractItemModel*              model,
    Opt<Func<ColText(QModelIndex const&)>> toString,
    Opt<int>                               maxDepth) {
    if (maxDepth && *maxDepth < level) { return; }

    ModelLevelRecord record{.depth = level};

    QModelIndex currentIndex = index;
    auto currentProxyModel   = qobject_cast<QSortFilterProxyModel const*>(
        index.model());
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

        if (ignoreExceptions) {
            try {
                act();
            } catch (std::exception& ex) {
                repr.roleValue = fmt(
                    "Exception {} {}", typeid(ex).name(), ex.what());
                record.roles.push_back(repr);
            }
        } else {
            act();
        }
    }

    auto add_proxy = [&](CR<QModelIndex> index) {
        record.proxies.push_back(ModelProxyRecord{.index = index});
    };

    add_proxy(currentIndex);

    while (currentProxyModel) {
        Q_ASSERT(currentIndex.model() != nullptr);
        Q_ASSERT(currentProxyModel->sourceModel() != nullptr);
        if (!currentProxyModel->sourceModel()->hasIndex(
                currentIndex.row(), currentIndex.column())) {
            break;
        }

        auto mapped = currentProxyModel->mapToSource(currentIndex);
        if (mapped.isValid()) {
            currentIndex = mapped;
            add_proxy(currentIndex);
            currentProxyModel = qobject_cast<QSortFilterProxyModel const*>(
                currentProxyModel->sourceModel());
        } else {
            break;
        }
    }

    if (toString) { record.finalRepr = (*toString)(index); }
    records.push_back(record);

    int rowCount = model->rowCount(index);
    for (int row = 0; row < rowCount; ++row) {
        QModelIndex sub = model->index(row, 0, index);
        recurse_tree(
            sub,
            level + 1,
            role_names,
            records,
            ignoreExceptions,
            model,
            toString,
            maxDepth);
    }
}

ColText format_records(CVec<ModelLevelRecord> records) {
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

} // namespace

ColText printModelTree(
    const QAbstractItemModel*              model,
    const QModelIndex&                     parent,
    Opt<Func<ColText(QModelIndex const&)>> toString,
    bool                                   ignoreExceptions,
    Opt<int>                               maxDepth) {
    if (!model) { return ColText{""}; }


    QHash<int, QByteArray> role_names = model->roleNames();

    for (auto const& it : role_names.keys()) {
        if (it != Qt::DisplayRole      //
            && it != Qt::WhatsThisRole //
            && it < Qt::UserRole) {
            role_names.remove(it);
        }
    }

    Vec<ModelLevelRecord> records;

    recurse_tree(
        parent,
        0,
        role_names,
        records,
        ignoreExceptions,
        model,
        toString,
        maxDepth);

    return format_records(records);
}

Func<ColText(const QModelIndex&)> store_index_printer(
    OrgStore const* store,
    int             role) {
    return [store, role](QModelIndex const& idx) -> ColText {
        OrgBoxId box = qvariant_cast<OrgBoxId>(idx.data(role));
        if (store->data.contains(box)) {
            auto    node   = store->getBoxedNode(box);
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

QPixmap save_screenshot(
    QWidget*       widget,
    const QString& filePath,
    qreal          scaleFactor) {
    QPixmap pixmap(widget->size() * scaleFactor);
    pixmap.setDevicePixelRatio(scaleFactor);
    widget->render(&pixmap);
    pixmap.save(filePath);
    return pixmap;
}

QPixmap save_screenshot(const QString& filePath) {
    QScreen*       screen = QGuiApplication::primaryScreen();
    const QWindow* window = QApplication::focusWindow();
    Q_ASSERT(window != nullptr);
    QPixmap pixmap = screen->grabWindow(window->winId());
    pixmap.save(filePath);
    return pixmap;
}

void perf_accept_signal(CR<Str> signal, int extraId) {
    __perf_trace(
        "qt_signals",
        signal.c_str(),
        perfetto::TerminatingFlow::ProcessScoped(
            getSignalId(signal, extraId)));
}

void perf_emit_signal(CR<Str> signal, int extraId) {
    __perf_trace(
        "qt_signals",
        signal.c_str(),
        perfetto::Flow::ProcessScoped(getSignalId(signal, extraId)));
}

int getSignalId(CR<Str> signal, int extraId) {
    std::size_t result;
    boost::hash_combine(result, signal);
    boost::hash_combine(result, extraId);
    return static_cast<int>(result);
}

bool isDebuggerPresent() {
    // Try to trace the process
    if (ptrace(PTRACE_TRACEME, 0, nullptr, 0) == -1) {
        return true; // If tracing fails, it means the process is already
                     // being traced (i.e., under a debugger)
    } else {
        // Detach from the process to clean up
        ptrace(PTRACE_DETACH, 0, nullptr, 0);
        return false; // If tracing succeeds, the process is not being
                      // traced by a debugger
    }
}

void break_if_debugger() {
    if (isDebuggerPresent()) { __builtin_debugtrap(); }
}
