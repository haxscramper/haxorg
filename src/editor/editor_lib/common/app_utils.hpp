#pragma once

#include <string>
#include <QAbstractItemModel>
#include <hstd/stdlib/Func.hpp>
#include <editor/editor_lib/document/org_document_model.hpp>
#include <QEvent>
#include <boost/preprocessor.hpp>
#include <QLoggingCategory>
#include <hstd/stdlib/Exception.hpp>

#include <QCoreApplication>
#include <QObject>
#include <QDebug>
#include <QMetaMethod>
#include <QMetaObject>
#include <QPixmap>

#include <hstd/wrappers/hstd_extra/perfetto_aux.hpp>

#ifdef ORG_USE_PERFETTO
// The set of track event categories that the example is using.
PERFETTO_DEFINE_CATEGORIES(
    perfetto::Category("qt_signals")
        .SetDescription("Flow events for signal processing"),
    perfetto::Category("mind_map").SetDescription("Mind map operations")
    //
);
#endif

int  getSignalId(CR<Str> signal, int extraId);
void perf_emit_signal(CR<Str> signal, int extraId);
void perf_accept_signal(CR<Str> signal, int extraId);

#define PERF_MMAP(...) __perf_trace("mind_map" __VA_OPT__(, ) __VA_ARGS__)
#define PERF_MMAP_BEGIN(...)                                              \
    __perf_trace_begin("mind_map" __VA_OPT__(, ) __VA_ARGS__)
#define PERF_MMAP_END(...)                                                \
    __perf_trace_end("mind_map" __VA_OPT__(, ) __VA_ARGS__)

class QWindow;

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
enum class SharedModelRoles
{
    IndexBox = (int)Qt::UserRole + 1,

    __LAST__,
};

ColText printModelTree(
    const QAbstractItemModel*              model,
    const QModelIndex&                     parent,
    Opt<Func<ColText(QModelIndex const&)>> toString         = std::nullopt,
    bool                                   ignoreExceptions = false,
    Opt<int>                               maxDepth = std::nullopt);

inline ColText printIndex(QModelIndex const& index) {
    return printModelTree(index.model(), index, std::nullopt, false, 1);
}


Func<ColText(QModelIndex const&)> store_index_printer(
    const OrgStore* store,
    int             role = (int)SharedModelRoles::IndexBox);

Str debug(sem::OrgArg);

#define _QDBG_PRINT(z, n, data)                                           \
    << BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(n, data)) << "=" << BOOST_PP_TUPLE_ELEM(n, data) << ","
#define _QDBG_ARG_COUNT(...) BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)

#define _QDBG_DISPATCHER(count, ...)                                      \
    BOOST_PP_REPEAT(count, _QDBG_PRINT, (__VA_ARGS__))

#define _qdbg(...)                                                        \
    qDebug() << __LINE__ _QDBG_DISPATCHER(                                \
        _QDBG_ARG_COUNT(__VA_ARGS__), __VA_ARGS__);

#define _qfmt(...)                                                        \
    qDebug().noquote().nospace()                                          \
        << fmt("[qfmt] [{}:{}]", __FUNCTION__, __LINE__)                  \
        << fmt(__VA_ARGS__);

#define Q_DECLARE_FMT_METATYPE(Type)                                      \
    inline QDebug operator<<(QDebug debug, Type const& t) {               \
        QDebugStateSaver saver(debug);                                    \
        debug.nospace() << fmt1(t);                                       \
        return debug;                                                     \
    }                                                                     \
                                                                          \
    Q_DECLARE_METATYPE(Type);


#define Q_DECLARE_REFL_METATYPE(Type)                                     \
    inline QDebug operator<<(QDebug debug, Type const& t) {               \
        QDebugStateSaver saver(debug);                                    \
        debug.nospace() << #Type << described_class_printer<Type>(t);     \
        return debug;                                                     \
    }                                                                     \
                                                                          \
    Q_DECLARE_METATYPE(Type);

#define DECL_QDEBUG_FORMATTER(Type)                                       \
    template <>                                                           \
    struct std::formatter<Type> : std::formatter<std::string> {           \
        template <typename FormatContext>                                 \
        FormatContext::iterator format(Type const& p, FormatContext& ctx) \
            const {                                                       \
            return fmt_ctx(qdebug_to_str(p), ctx);                        \
        }                                                                 \
    };


struct model_role_not_implemented
    : public CRTP_hexception<model_role_not_implemented> {
    QAbstractItemModel const* model;
};

template <typename T>
std::string qdebug_to_str(T const& index) {
    QString output;
    QDebug(&output).noquote().nospace() << index;
    return output.toStdString();
}

std::string qdebug_obj(QObject const* obj);

void break_if_debugger();

inline QDebug operator<<(QDebug debug, const std::string& str) {
    debug.nospace() << QString::fromStdString(str);
    return debug.space();
}

template <DescribedEnum E>
inline QDebug operator<<(QDebug debug, E const& str) {
    debug.nospace() << enum_serde<E>::to_string(str);
    return debug.space();
}


DECL_QDEBUG_FORMATTER(QModelIndex);
DECL_QDEBUG_FORMATTER(QPersistentModelIndex);
DECL_QDEBUG_FORMATTER(QObject const*);
DECL_QDEBUG_FORMATTER(QRect);
DECL_QDEBUG_FORMATTER(QPoint);
DECL_QDEBUG_FORMATTER(QPointF);
DECL_QDEBUG_FORMATTER(QSize);

template <typename T>
struct std::formatter<QList<T>> : std::formatter<std::string> {
    using FmtType = QList<T>;
    template <typename FormatContext>
    FormatContext::iterator format(FmtType const& p, FormatContext& ctx)
        const {
        std::formatter<std::string> fmt;
        fmt.format("[", ctx);
        fmt.format(join(", ", p), ctx);
        return fmt.format("]", ctx);
    }
};


template <>
struct std::formatter<QString> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(QString const& p, FormatContext& ctx)
        const {
        return fmt_ctx(p.toStdString(), ctx);
    }
};

QModelIndex mapToNestedSource(QModelIndex const& index);
QModelIndex mapToNestedProxy(
    QModelIndex const&          index,
    Vec<QSortFilterProxyModel*> proxies);


inline QModelIndex getAtQModelPath(
    QAbstractItemModel*        model,
    Vec<Pair<int, int>> const& path) {
    QModelIndex result = model->index(path.at(0).first, path.at(0).second);
    for (int i = 1; i < path.size(); ++i) {
        result = model->index(path.at(i).first, path.at(i).second, result);
    }

    return result;
}

inline QModelIndex getAtQModelPath(
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
bool is_of_type(QVariant const& var) {
    return var.typeId() == qMetaTypeId<T>();
}

template <typename T>
T qvariant_get(QVariant const& var) {
    Q_ASSERT(var.isValid());
    Q_ASSERT_X(
        is_of_type<T>(var),
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
Opt<T> qvariant_opt(QVariant const& var) {
    if (is_of_type<T>(var)) {
        return qvariant_get<T>(var);
    } else {
        return std::nullopt;
    }
}

template <typename T>
T qindex_get(QModelIndex const& index, int role) {
    Q_ASSERT(index.model() != nullptr);
    QVariant result = index.data(role);

    if (!result.isValid()) {
        Str fail = fmt(
            "Getting index {} for role {} in model {} failed: qvariant is "
            "invalid",
            qdebug_to_str(index),
            index.model()->roleNames().contains(role)
                ? index.model()->roleNames().value(role).toStdString()
                : fmt("<unnamed {}>", role),
            qdebug_to_str(index.model()));

        break_if_debugger();
        auto model = index.model();
        model->data(index, role);

        Q_ASSERT_X(result.isValid(), "qindex_get", fail);
    }


    return qvariant_get<T>(result);
}

template <typename T, IsEnum E>
T qindex_get(QModelIndex const& index, E role) {
    return qindex_get<T>(index, (int)role);
}


QPixmap save_screenshot(const QString& filePath);

QPixmap save_screenshot(
    QWidget*       widget,
    const QString& filePath,
    qreal          scaleFactor = 1.0);

inline Func<QPixmap(CR<Str>)> make_shot(QWidget* window, CR<Str> name) {
    return [name, window](CR<Str> text) -> QPixmap {
        return save_screenshot(
            window,
            QString::fromStdString(fmt("/tmp/{}_{}.png", name, text)),
            2);
    };
}


/// \brief CRTP method injection for debugging methods
template <typename Derived>
struct CRTP_qdebug : CRTP_this_method<Derived> {
    using CRTP_this_method<Derived>::_this;
};
