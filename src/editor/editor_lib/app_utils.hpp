#pragma once

#include <string>
#include <QAbstractItemModel>
#include <hstd/stdlib/Func.hpp>
#include <editor/editor_lib/org_document_model.hpp>
#include <QEvent>
#include <boost/preprocessor.hpp>
#include <QLoggingCategory>

using osk = OrgSemKind;

/// Top-level logs for all editor logging that does not fit into any
/// specific categories
Q_DECLARE_LOGGING_CATEGORY(editor);
/// Logging related to the editable document model in the tree or outline
Q_DECLARE_LOGGING_CATEGORY(editor_model);
/// Logging for operations and diagnostics with files -- opening, closing,
/// parsing etc.
Q_DECLARE_LOGGING_CATEGORY(editor_files);

/// Model roles shared between qbstract item models working with the
/// org-mode tree representation.
enum SharedModelRoles
{
    IndexBoxRole = Qt::UserRole + 1,

    __LAST__,
};

ColText printModelTree(
    const QAbstractItemModel*         model,
    const QModelIndex&                parent,
    Func<ColText(QModelIndex const&)> toString);

Func<ColText(QModelIndex const&)> store_index_printer(
    const OrgStore* store,
    int             role = SharedModelRoles::IndexBoxRole);

Str debug(sem::OrgArg);

#define _QDBG_PRINT(z, n, data)                                           \
    << BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(n, data)) << "=" << BOOST_PP_TUPLE_ELEM(n, data) << ","
#define _QDBG_ARG_COUNT(...) BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)

#define _QDBG_DISPATCHER(count, ...)                                      \
    BOOST_PP_REPEAT(count, _QDBG_PRINT, (__VA_ARGS__))

#define _qdbg(...)                                                        \
    qDebug() << __LINE__ _QDBG_DISPATCHER(                                \
        _QDBG_ARG_COUNT(__VA_ARGS__), __VA_ARGS__);


template <typename T>
std::string qdebug_to_str(T const& index) {
    QString output;
    QDebug(&output).noquote().nospace() << index;
    return output.toStdString();
}

inline QDebug operator<<(QDebug debug, const std::string& str) {
    debug.nospace() << QString::fromStdString(str);
    return debug.space();
}

template <DescribedEnum E>
inline QDebug operator<<(QDebug debug, E const& str) {
    debug.nospace() << enum_serde<E>::to_string(str);
    return debug.space();
}


QModelIndex mapToNestedSource(QModelIndex const& index);
QModelIndex mapToNestedProxy(
    QModelIndex const&          index,
    Vec<QSortFilterProxyModel*> proxies);


inline QModelIndex index(
    QAbstractItemModel*        model,
    Vec<Pair<int, int>> const& path) {
    QModelIndex result = model->index(path.at(0).first, path.at(0).second);
    for (int i = 1; i < path.size(); ++i) {
        result = model->index(path.at(i).first, path.at(i).second, result);
    }

    return result;
}

inline QModelIndex index(
    QAbstractItemModel* model,
    Vec<int> const&     path,
    int                 alwaysColumn = 0) {
    QModelIndex result = model->index(path.at(0), alwaysColumn);
    for (int i = 1; i < path.size(); ++i) {
        result = model->index(path.at(i), alwaysColumn, result);
    }

    return result;
}


class DebugEventFilter : public QObject {
  public:
    DebugEventFilter(QObject* parent) : QObject(parent) {}

  protected:
    bool eventFilter(QObject* obj, QEvent* event) override {
        qCDebug(editor_model).noquote().nospace()
            << "Object: '" << obj->metaObject()->className()
            << "::" << obj->objectName() << //
            "' Type: " << event->type() <<  //
            " Event: " << event <<          //
            " Receiver: " << obj;
        return false;
    }

    static void add(QObject* obj) {
        obj->installEventFilter(new DebugEventFilter(obj));
    }

    static finally scoped(QObject* obj) {
        SPtr<DebugEventFilter> filter = std::make_shared<DebugEventFilter>(
            obj);

        obj->installEventFilter(filter.get());
        return finally(
            [filter, obj]() { obj->removeEventFilter(filter.get()); });
    }
};

inline void qt_assert_x(
    std::string const& where,
    std::string const& what,
    const char*        file,
    int                line) noexcept {
    qt_assert_x(strdup(where.c_str()), strdup(what.c_str()), file, line);
}

template <typename T>
T qvariant_get(QVariant const& var) {
    Q_ASSERT(var.isValid());
    Q_ASSERT_X(
        var.typeId() == qMetaTypeId<T>(),
        "qvariant_get",
        fmt("Expected and given variant types differ. {} ({}) != {} "
            "({}):",
            var.typeId(),
            var.typeName() ? var.typeName() : "<unnamed>",
            qMetaTypeId<T>(),
            QMetaType::fromType<T>().name()
                ? QMetaType::fromType<T>().name()
                : "<unnamed>"));

    return qvariant_cast<T>(var);
}

template <typename T>
T qindex_get(QModelIndex const& index, int role) {
    Q_ASSERT(index.model() != nullptr);
    QVariant result = index.data(role);
    Q_ASSERT_X(
        result.isValid(),
        "qindex_get",
        fmt("Getting index {} for role {} in model {} failed: qvariant is "
            "invalid",
            qdebug_to_str(index),
            index.model()->roleNames().contains(role)
                ? index.model()->roleNames().value(role).toStdString()
                : fmt("<unnamed {}>", role),
            qdebug_to_str(index.model())));

    return qvariant_get<T>(result);
}
